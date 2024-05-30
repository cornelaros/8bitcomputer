#ifndef controlbus_h
#define controlbus_h

#include <inttypes.h>

const uint16_t NUL = 0b0000000000000000;
const uint16_t CH  = 0b1000000000000000;
const uint16_t MI  = 0b0100000000000000;
const uint16_t RI  = 0b0010000000000000;
const uint16_t RO  = 0b0001000000000000;
const uint16_t II  = 0b0000100000000000;
const uint16_t IO  = 0b0000010000000000;
const uint16_t AI  = 0b0000001000000000;
const uint16_t AO  = 0b0000000100000000;
const uint16_t SU  = 0b0000000010000000;
const uint16_t EO  = 0b0000000001000000;
const uint16_t BI  = 0b0000000000100000;
const uint16_t OI  = 0b0000000000010000;
const uint16_t J   = 0b0000000000001000;
const uint16_t CE  = 0b0000000000000100;
const uint16_t CO  = 0b0000000000000010;
const uint16_t FI  = 0b0000000000000001;

class ControlBus
{
  public:
    ControlBus(uint8_t ch,                          // clock halt
               uint8_t mi, uint8_t ri, uint8_t ro,  // mem address in, ram in, ram out
               uint8_t ii, uint8_t io,              // instruction reg in, out
               uint8_t ai, uint8_t ao,              // accumulator in, out
               uint8_t su, uint8_t eo,              // subtract, alu out
               uint8_t bi,                          // b reg out
               uint8_t oi,                          // output reg in
               uint8_t j, uint8_t ce, uint8_t co,   // jump, count enable, counter out
               uint8_t fi);                         // flags reg in

    void init(uint8_t ch,
              uint8_t mi, uint8_t ri, uint8_t ro,
              uint8_t ii, uint8_t io,
              uint8_t ai, uint8_t ao,
              uint8_t su, uint8_t eo,
              uint8_t bi,
              uint8_t oi,
              uint8_t j, uint8_t ce, uint8_t co,
              uint8_t fi);

    void SetControlWord(uint16_t word);
  
  private:
    uint16_t _control_word;
    uint8_t _control_bus_pins[16];
};

#endif