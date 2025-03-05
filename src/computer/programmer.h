#ifndef programmer_h
#define programmer_h

#include <inttypes.h>
#include <Arduino.h>

#include "memory.h"

class Programmer {
  public:
    Programmer(Memory& m);
    void Reset();
    void WaitForSerial();
    void ParseString();
    void HandleSpecialChar(char _c);
    uint8_t LookupOpCode(String _string);
    void OutputToSerial();

  private:
    Memory& _memory;

    static const uint8_t _text_buffer_size = 16;
    int8_t _text_buffer[_text_buffer_size];
    uint8_t _text_index;

    String _parse_buffer;
    uint8_t _line_num;
    uint8_t _stop_line_num;
    uint8_t _op_code;
    uint8_t _argument;
    bool _read_mode;
    bool _block_read;
    bool _verbose_read;
    bool _has_argument;
};

#endif