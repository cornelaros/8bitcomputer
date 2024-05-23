#ifndef bus_h
#define bus_h

#include <inttypes.h>

class Bus
{
  public:
    Bus(uint8_t we,   // write enable
        uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3, uint8_t r4, uint8_t r5, uint8_t r6, uint8_t r7,   // read pins
        uint8_t w0, uint8_t w1, uint8_t w2, uint8_t w3, uint8_t w4, uint8_t w5, uint8_t w6, uint8_t w7);  // write pins

    void init(uint8_t we,
              uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3, uint8_t r4, uint8_t r5, uint8_t r6, uint8_t r7,
              uint8_t w0, uint8_t w1, uint8_t w2, uint8_t w3, uint8_t w4, uint8_t w5, uint8_t w6, uint8_t w7);

    void SetContent(uint8_t byte);
    uint8_t GetContent();

  private:
    uint8_t _bus_content;
    uint8_t _bus_write_enable_pin;
    uint8_t _bus_read_pins[8];
    uint8_t _bus_write_pins[8];
};

#endif