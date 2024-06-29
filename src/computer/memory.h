#ifndef memory_h
#define memory_h

#include <inttypes.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "ucode.h"

class Memory
{
  public:
    Memory(Bus& b, ControlBus& cb, RingCounter& rc);
    void Reset();
    void Run(uint8_t clk);
      
  private:
    Bus& _bus;
    ControlBus& _control_bus;
    RingCounter& _ring_counter;

    uint8_t _bus_content;
    uint16_t _control_word;
    uint8_t _clock_state;

    uint8_t _memory_address;
    
    uint8_t _memory_content[16]{
      JMP|2,
      NOP,
      JMP|4,
      NOP,
      JMP|6,
      NOP,
      JMP|8,
      NOP,
      JMP|10,
      NOP,
      JMP|12,
      NOP,
      JMP|14,
      NOP,
      JMP|0,
      NOP
    };
};

#endif