#include <inttypes.h>
#include <Arduino.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "cpu.h"

// CPU constructor
CentralProcessingUnit::CentralProcessingUnit(Bus& b, ControlBus& cb, RingCounter& rc) :
    _bus(b), _control_bus(cb), _ring_counter(rc){}

// Resetting the CPU will also reset the connected hardware components
void CentralProcessingUnit::Reset()
{
  _ring_counter.Reset();
  _bus.SetContent(0x00);
  _control_bus.SetControlWord(MI|II|AI|BI|OI|J|FI); // all registers in
}

// Running the computer will start the program from RAM
void CentralProcessingUnit::Run()
{
  _clock_state = _ring_counter.GetClkState();
  _t_state = _ring_counter.GetTState();
  
  // Test program:
  if(_clock_state == 0)
  {
    // Low state: set controlword, write to databus
    switch(_t_state)
    {
      case 1:
        _control_bus.SetControlWord(CE);
        _bus.SetContent(_t_state);
        break;
      case 2:
        _control_bus.SetControlWord(NOP);
        _bus.SetContent(_t_state);
        break;
      case 3:
        _control_bus.SetControlWord(NOP);
        _bus.SetContent(_t_state);
        break;
      case 4:
        _control_bus.SetControlWord(NOP);
        _bus.SetContent(_t_state);
        break;
      case 5:
        _control_bus.SetControlWord(NOP);
        _bus.SetContent(_t_state);
        break;
    }

    // When done: rise (will only work for internal ringcounter)
    _ring_counter.Rise();
  }
  else if(_clock_state == 1)
  {
    // High state: read from databus
    switch(_t_state)
    {
      case 1:
        Serial.println(_bus.GetContent(), BIN);
        break;
      case 3:
        Serial.println(_bus.GetContent(), BIN);
        break;
      default:
        break;
    }

    // When done: fall (will only work for internal ringcounter)
    _ring_counter.Fall();
  }
}