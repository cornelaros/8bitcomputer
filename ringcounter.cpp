#include "ringcounter.h"
#include <inttypes.h>
#include <Arduino.h>

void RingCounter::AttachExternal(uint8_t clk)
{
  _external_clock = 1;
  _clk_pin = clk;
  pinMode(_clk_pin, INPUT);
}

void RingCounter::AttachInternal(uint8_t clk)
{
  _external_clock = 0;
  _clk_pin = clk;
  pinMode(_clk_pin, OUTPUT);
}

void RingCounter::Reset()
{
  _clk_state = 0;
  _prev_clk_state = 0;
  _t_state = 1;
}

void RingCounter::Pulse()
{
  if(_external_clock == 1){
    return;
  }
  _clk_state = 0;
  digitalWrite(_clk_pin, _clk_state);
  delay(25);

  _clk_state = 1;
  digitalWrite(_clk_pin, _clk_state);
  delay(25);

  _clk_state = 0;
  _t_state < _max_t_state ? _t_state += 1 : _t_state = 1;
  digitalWrite(_clk_pin, _clk_state);
}

uint8_t RingCounter::GetTState()
{
  // when clock goes low, increment t-state up to max t-state
  // when using internal clock, the prev clock state stays 0
  // and the t_state gets incremented in the Pulse function
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