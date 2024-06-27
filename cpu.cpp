#include <inttypes.h>
#include <Arduino.h>

#include "cpu.h"
#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "ucode.h"

// CPU constructor
CentralProcessingUnit::CentralProcessingUnit(Bus& b, Bus& ir, ControlBus& cb, RingCounter& rc, uint8_t zf, uint8_t cf) :
    _bus(b), _instruction_register(ir), _control_bus(cb), _ring_counter(rc), _zero_flag_pin(zf), _carry_flag_pin(cf){}

// Resetting the CPU will also reset the connected hardware components
void CentralProcessingUnit::Reset()
{
  // Reset all hardware components
  pinMode(_zero_flag_pin, INPUT);
  pinMode(_carry_flag_pin, INPUT);
  _bus.SetContent(0x00);
  _control_bus.SetControlWord(MI|II|AI|BI|OI|J|FI); // all registers in
  _ring_counter.AttachInternal(2, 100);
  _ring_counter.Rise();
  _ring_counter.Fall();
  _ring_counter.Reset();
  
  // Hand over control to void Run()
  _control_bus.SetControlWord(NUL);
  _bus.DisconnectWrite();
}

// Running the computer will start the program from RAM
void CentralProcessingUnit::Run(uint8_t clk, uint8_t t)
{
  _clock_state = clk;
  _t_state     = t;
  if(_clock_state == 0)
  {
    // read instruction and flags
    _instruction = _instruction_register.GetContent();
    _zero_flag = digitalRead(_zero_flag_pin);
    _carry_flag = digitalRead(_carry_flag_pin);
    
    // set instruction to NOP if flag not set
    if(_instruction == 0b1000 && _zero_flag  == 0){_instruction = NOP;}
    if(_instruction == 0b0111 && _carry_flag == 0){_instruction = NOP;}

    // set controlword from microcode
    _control_word = ucode[_instruction][_t_state];
    _control_bus.SetControlWord(_control_word);
  }
}