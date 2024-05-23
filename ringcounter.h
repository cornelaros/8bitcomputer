#ifndef ringcounter_h
#define ringcounter_h

#include <inttypes.h>

class RingCounter
{
  public:
    RingCounter;
    void AttachExternal(uint8_t clk);
    void AttachInternal(uint8_t clk);
    void Pulse();
    void Reset();
    
    uint8_t GetTState();
    uint8_t GetClkState();

  private:
    uint8_t _external_clock;

    uint8_t _clk_pin;
    uint8_t _invclk_pin;

    uint8_t _clk_state = 0;
    uint8_t _prev_clk_state = 0;
    uint8_t _t_state = 1;
    const uint8_t _max_t_state = 5;
};

#endif