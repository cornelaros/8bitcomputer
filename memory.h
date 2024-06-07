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
      NOP,      // 0000  0
      JMP|13,   // 0001  1
      NOP,      // 0010  2
      JMP|10,   // 0011  3
      JMP|6,    // 0100  4
      0,        // 0101  5
      JMP|15,   // 0110  6
      JMP|2,    // 0111  7
      0,        // 1000  8
      0,        // 1001  9
      NOP,      // 1010 10
      NOP,      // 1011 11
      JMP|0,    // 1100 12
      JMP|4,    // 1101 13
      0,        // 1110 14
      JMP|7     // 1111 15
    };
};

#endif