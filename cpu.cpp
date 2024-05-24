#include <inttypes.h>
#include <Arduino.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "cpu.h"

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
  
  if(_clock_state == 0)
  {
    // Low state: set controlword, write to databus
    switch(_t_state)
    {
      case 1:
        _control_bus.SetControlWord(CO);
        break;
      case 2:
        _control_bus.SetControlWord(CE);
        break;
      case 3:
        _control_bus.SetControlWord(NOP);
        break;
      case 4:
        _control_bus.SetControlWord(NOP);
        break;
      case 5:
        _control_bus.SetControlWord(NOP);
        break;
    }

    // When done: rise
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
      default:
        break;
    }

    // When done: fall
    _ring_counter.Fall();
  }
}