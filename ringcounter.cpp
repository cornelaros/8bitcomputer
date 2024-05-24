#include <inttypes.h>
#include <Arduino.h>

#include "ringcounter.h"

void RingCounter::AttachExternal(uint8_t clk)
{
  _external_clock = 1;
  _clk_pin = clk;
  pinMode(_clk_pin, INPUT);
}

void RingCounter::AttachInternal(uint8_t clk, uint8_t delay)
{
  _external_clock = 0;
  _clk_pin = clk;
  pinMode(_clk_pin, OUTPUT);
  _delay = delay;
}

void RingCounter::Reset()
{
  _clk_state = 0;
  _prev_clk_state = 0;
  _t_state = 1;
}

void RingCounter::Rise()
{
  _clk_state = 1;
  if(_external_clock == 0){
    digitalWrite(_clk_pin, _clk_state);
    delay(_delay);
  }
}

void RingCounter::Fall()
{
  _clk_state = 0;
  if(_external_clock == 0){
    digitalWrite(_clk_pin, _clk_state);
    delay(_delay);
  }
}

uint8_t RingCounter::GetTState()
{
  // when clock goes low, increment t-state up to max t-state
  if(_clk_state != _prev_clk_state && _clk_state == 0){
    _t_state < _max_t_state ? _t_state += 1 : _t_state = 1;
  }
  _prev_clk_state = _clk_state;
  return _t_state;
}

uint8_t RingCounter::GetClkState()
{
  _external_clock == 0 ? _clk_state : _clk_state = digitalRead(_clk_pin);
  return _clk_state;
}