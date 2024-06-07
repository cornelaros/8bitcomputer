#ifndef cpu_h
#define cpu_h

#include <inttypes.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"

class CentralProcessingUnit
{
  public:
    CentralProcessingUnit(Bus& b, Bus& ir, ControlBus& cb, RingCounter& rc);
    void Reset();
    void Run(uint8_t clk, uint8_t t);

  private:
    Bus& _bus;
    Bus& _instruction_register;
    ControlBus& _control_bus;
    RingCounter& _ring_counter;
    uint8_t _clock_state;
    uint8_t  _t_state;
    uint8_t  _flags;
    uint8_t  _instruction;
    uint16_t _control_word;
};

#endif