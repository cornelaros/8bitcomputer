#include <inttypes.h>
#include <Arduino.h>

#include "bus.h"

Bus::Bus(uint8_t we,
         uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3, uint8_t r4, uint8_t r5, uint8_t r6, uint8_t r7,
         uint8_t w0, uint8_t w1, uint8_t w2, uint8_t w3, uint8_t w4, uint8_t w5, uint8_t w6, uint8_t w7)
{
  init(0, we, r0, r1, r2, r3, r4, r5, r6, r7, w0, w1, w2, w3, w4, w5, w6, w7);
}

Bus::Bus(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3, uint8_t r4, uint8_t r5, uint8_t r6, uint8_t r7)
{
  init(0, 255, r0, r1, r2, r3, r4, r5, r6, r7, 0, 0, 0, 0, 0, 0, 0, 0);
}

Bus::Bus(uint8_t we,
         uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3,
         uint8_t w0, uint8_t w1, uint8_t w2, uint8_t w3)
{
  init(1, we, r0, r1, r2, r3, 0, 0, 0, 0, w0, w1, w2, w3, 0, 0, 0, 0);
}

Bus::Bus(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3)
{
  init(1, 255, r0, r1, r2, r3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void Bus::init(uint8_t fourbitmode, uint8_t we,
               uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3, uint8_t r4, uint8_t r5, uint8_t r6, uint8_t r7,
               uint8_t w0, uint8_t w1, uint8_t w2, uint8_t w3, uint8_t w4, uint8_t w5, uint8_t w6, uint8_t w7)
{
  _bus_write_enable_pin = we;
  
  _bus_read_pins[0] = r0;
  _bus_read_pins[1] = r1;
  _bus_read_pins[2] = r2;
  _bus_read_pins[3] = r3;
  _bus_read_pins[4] = r4;
  _bus_read_pins[5] = r5;
  _bus_read_pins[6] = r6;
  _bus_read_pins[7] = r7;
  
  _bus_write_pins[0] = w0;
  _bus_write_pins[1] = w1;
  _bus_write_pins[2] = w2;
  _bus_write_pins[3] = w3;
  _bus_write_pins[4] = w4;
  _bus_write_pins[5] = w5;
  _bus_write_pins[6] = w6;
  _bus_write_pins[7] = w7;

  if(_bus_write_enable_pin != 255){
    pinMode(_bus_write_enable_pin, OUTPUT);
  }  
  
  if(fourbitmode){
    _number_of_bits = 4;
  } else {
    _number_of_bits = 8;
  }
  
  for(uint8_t i = 0; i < _number_of_bits; i++){
    pinMode(_bus_read_pins[i], INPUT_PULLUP);
    pinMode(_bus_write_pins[i], OUTPUT);
  }
}

uint8_t Bus::GetContent()
{
  _bus_content = 0b00000000;
  
  // reading the bits one by one rightmost bit first
  for(uint8_t b = 0; b < _number_of_bits; b++){
    uint8_t bit = digitalRead(_bus_read_pins[b]);
    bitWrite(_bus_content, b, bit);
  }

  return _bus_content;
}

void Bus::SetContent(uint8_t byte)
{
  _bus_content = byte;
  if(_bus_write_enable_pin != 255){
    digitalWrite(_bus_write_enable_pin, 0);   // active low enable on 74LS245
  }

  // writing the bits one by one rightmost bit first
  for(uint8_t b = 0; b < _number_of_bits; b++){
    uint8_t bit = bitRead(_bus_content, b);
    digitalWrite(_bus_write_pins[b], bit);
  }
}

void Bus::DisconnectWrite()
{
  if(_bus_write_enable_pin != 255){
    digitalWrite(_bus_write_enable_pin, 1);   // active low enable on 74LS245
  }
}