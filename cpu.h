#ifndef cpu_h
#define cpu_h

#include <inttypes.h>

#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"

class CentralProcessingUnit
{
  public:
    CentralProcessingUnit(Bus& b, ControlBus& cb, RingCounter& rc);
    void Reset();
    void Run();

  private:
    Bus& _bus;
    ControlBus& _control_bus;
    RingCounter& _ring_counter;
    uint8_t _clock_state;
    uint8_t _t_state;
};

#endif