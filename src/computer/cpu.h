#ifndef cpu_h
#define cpu_h

#include <inttypes.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"

class CentralProcessingUnit
{
  public:
    CentralProcessingUnit(Bus& b, Bus& ir, ControlBus& cb, RingCounter& rc, uint8_t zf, uint8_t cf);
    void Reset();
    void Run(uint8_t clk, uint8_t t);

  private:
    Bus& _bus;
    Bus& _instruction_register;
    ControlBus& _control_bus;
    RingCounter& _ring_counter;
    uint8_t _zero_flag_pin;
    uint8_t _carry_flag_pin;
    uint8_t _zero_flag;
    uint8_t _carry_flag;
    uint8_t _clock_state;
    uint8_t  _t_state;
    uint8_t  _instruction;
    uint16_t _control_word;
};

#endif