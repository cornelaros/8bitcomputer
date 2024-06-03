#include <inttypes.h>
#include <Arduino.h>

#include "cpu.h"
#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "ucode.h"

// CPU constructor
CentralProcessingUnit::CentralProcessingUnit(Bus& b, Bus& ir, ControlBus& cb, RingCounter& rc) :
    _bus(b), _instruction_register(ir), _control_bus(cb), _ring_counter(rc){}

// Resetting the CPU will also reset the connected hardware components
void CentralProcessingUnit::Reset()
{
  // Reset all hardware components
  _ring_counter.Reset();
  _bus.SetContent(0x00);
  _control_bus.SetControlWord(MI|II|AI|BI|OI|J|FI); // all registers in
  delay(100); // give hardware some time to receive and handle the control word

  // Hand over control to void Run()
  _control_bus.SetControlWord(NUL);
  _bus.DisconnectWrite();
}

// Running the computer will start the program from RAM
void CentralProcessingUnit::Run()
{
  _clock_state = _ring_counter.GetClkState();
  _t_state     = _ring_counter.GetTState();
  _flags       = 0b00;
  _instruction = _instruction_register.GetContent();

  if(_clock_state == 0)
  {
    _control_word = ucode[_instruction][_t_state];
    _control_bus.SetControlWord(_control_word);
    _ring_counter.Rise();
  }
  else if (_clock_state == 1)
  {
    _ring_counter.Fall();
  }
}