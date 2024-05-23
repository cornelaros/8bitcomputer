#include "controlbus.h"
#include <inttypes.h>
#include <Arduino.h>

ControlBus::ControlBus(uint8_t hlt,
                       uint8_t mi, uint8_t ri, uint8_t ro,
                       uint8_t ii, uint8_t io,
                       uint8_t ai, uint8_t ao,
                       uint8_t su, uint8_t eo,
                       uint8_t bi,
                       uint8_t oi,
                       uint8_t j, uint8_t ce, uint8_t co,
                       uint8_t fi)
{
  init(hlt, mi, ri, ro, ii, io, ai, ao, su, eo, bi, oi, j, ce, co, fi);
}

void ControlBus::init(uint8_t hlt,
                      uint8_t mi, uint8_t ri, uint8_t ro,
                      uint8_t ii, uint8_t io,
                      uint8_t ai, uint8_t ao,
                      uint8_t su, uint8_t eo,
                      uint8_t bi,
                      uint8_t oi,
                      uint8_t j, uint8_t ce, uint8_t co,
                      uint8_t fi)
{
  // since the word is read from right to left, halt pin is at 15 and flags in at 0
  _control_bus_pins[15] = hlt;
  _control_bus_pins[14] = mi;
  _control_bus_pins[13] = ri;
  _control_bus_pins[12] = ro;
  _control_bus_pins[11] = ii;
  _control_bus_pins[10] = io;
  _control_bus_pins[9] = ai;
  _control_bus_pins[8] = ao;
  _control_bus_pins[7] = su;
  _control_bus_pins[6] = eo;
  _control_bus_pins[5] = bi;
  _control_bus_pins[4] = oi;
  _control_bus_pins[3] = j;
  _control_bus_pins[2] = ce;
  _control_bus_pins[1] = co;
  _control_bus_pins[0] = fi;

  for(uint8_t i; i <= 15; i++){
    pinMode(_control_bus_pins[i], OUTPUT);
  }
}

void ControlBus::SetControlWord(uint16_t word)
{
  _control_word = word;

  // writing the bits one by one rightmost bit first
  for(uint8_t b = 0; b <= 15; b++){
    uint8_t bit = bitRead(_control_word, b);
    digitalWrite(_control_bus_pins[b], bit);
  }
}