#ifndef ringcounter_h
#define ringcounter_h

#include <inttypes.h>

class RingCounter
{
  public:
    RingCounter;
    void AttachExternal(uint8_t clk);
    void AttachInternal(uint8_t clk, uint8_t delay);
    
    void Reset();

    void Rise();
    void Fall();
    
    uint8_t GetTState();
    uint8_t GetClkState();

  private:
    uint8_t _external_clock;

    uint8_t _clk_pin;
    uint8_t _invclk_pin;

    uint8_t _clk_state = 0;
    uint8_t _prev_clk_state = 0;
    uint8_t _t_state = 0;
    uint8_t _max_t_state = 4;

    uint8_t _delay = 1;
};

#endif