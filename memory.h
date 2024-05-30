#ifndef memory_h
#define memory_h

#include <inttypes.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"

class Memory
{
  public:
    Memory(Bus& b, ControlBus& cb, RingCounter& rc);
    void Reset();
    void Run();
      
  private:
    Bus& _bus;
    ControlBus& _control_bus;
    RingCounter& _ring_counter;

    uint8_t _bus_content;
    uint16_t _control_word;
    uint8_t _clock_state;

    uint8_t _memory_address;
    uint8_t _memory_content[16]{
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,
      11,
      12,
      13,
      14,
      15
    };
};

#endif