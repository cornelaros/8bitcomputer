#include <inttypes.h>
#include <Arduino.h>

#include "memory.h"
#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"

Memory::Memory(Bus& b, ControlBus& cb, RingCounter& rc) :
    _bus(b), _control_bus(cb), _ring_counter(rc){}

void Memory::Reset()
{
  _memory_address = 0;
}

void Memory::Run(uint8_t clk)
{
  _clock_state = clk;
  _control_word = _control_bus.GetControlWord();

  if(_clock_state == 0){
    if (_control_word & RO) {
      _bus.SetContent(_memory_content[_memory_address]);
    }
  }

  else if(_clock_state == 1){
    if (_control_word & MI) {
      _memory_address = _bus.GetContent();
    }
    if (_control_word & RI) {
      _memory_content[_memory_address] = _bus.GetContent();
    }
  }
}