#include <inttypes.h>
#include <Arduino.h>

#include "programmer.h"
#include "memory.h"
#include "ucode.h"

Programmer::Programmer(Memory& m) :
    _memory(m){}

void Programmer::Reset()
{
  _text_index = 0;
  Serial.begin(9600);
  Serial.println("\\");   // wozmon, anyone?
}

void Programmer::OutputToSerial(){
  Serial.println();
  if(_read_mode && _verbose_read){
    for(uint8_t k = _line_num; k<=_stop_line_num; k++){
      Serial.print(k, DEC);
      Serial.print(":\t");
      uint8_t _memory_content = _memory.GetMemoryContent(k);
      _op_code = _memory_content>>4;
      _argument = _memory_content&0b00001111;
      Serial.print(ucodeLookupTable[_op_code]);
      Serial.print(" ");
      Serial.println(_argument, DEC);
    }
  }
  else if(_read_mode && !_verbose_read){
    for(uint8_t k = _line_num; k<=_stop_line_num; k++){
      Serial.print(k, BIN);
      Serial.print(":\t");
      Serial.println(_memory.GetMemoryContent(k), BIN);
    }
  }
  else if(!_read_mode){
    Serial.print(_line_num, BIN);
    Serial.print(":\t");
    Serial.println(_op_code, BIN);
    _memory.SetMemoryContent(_line_num, _op_code);
  }
}

uint8_t Programmer::LookupOpCode(String _string){
  for(uint8_t i=0; i<16; i++){
    if(_string == ucodeLookupTable[i]){
      return i<<4;
    }
  }
}

void Programmer::HandleSpecialChar(char _c)
{
  switch(_c){
    case 0x0D:  // CR
      // handle non empty parsebuffer
      if(_parse_buffer != "" && _read_mode){
        _stop_line_num = _parse_buffer.toInt();
        if(!_block_read) {
          _line_num = _stop_line_num;
        }
      }
      if(_parse_buffer != "" && !_read_mode){
        if(_has_argument){
          _argument = _parse_buffer.toInt();
          _op_code = _op_code|_argument;
        } else {
          _op_code = LookupOpCode(_parse_buffer);
        }
      }
      // then, output
      OutputToSerial();
      break;
    case 0x3A:  // ":"
      _read_mode = false;
      _line_num = _parse_buffer.toInt();
      _parse_buffer = "";
      break;
    case 0x2E:  // "."
      _read_mode = true;
      _block_read = true;
      _line_num = _parse_buffer.toInt();
      _parse_buffer = "";
      break;
    case 0x20:  // " ", space
      _has_argument = true;
      _op_code = LookupOpCode(_parse_buffer);
      _parse_buffer = "";
      break;
    case 0x76:  // "v"
      _verbose_read = true;
    default:
      break;
  }
}

void Programmer::ParseString()
{
  // set defaults
  _parse_buffer = "";
  _line_num = 0;
  _stop_line_num = 0;
  _op_code = 0;
  _argument = 0;
  _read_mode = true;
  _block_read = false;
  _verbose_read = false;
  _has_argument = false;

  // loop over text buffer
  for(uint8_t i=0; i<_text_index; i++){
    char _next_char = _text_buffer[i];
    
    // add normal chars to buffer
    if((_next_char >= 0x30 && _next_char <= 0x39) ||   // 0..9
       (_next_char >= 0x41 && _next_char <= 0x5A)      // A..Z
    ){
      _parse_buffer += _next_char;
    }
    
    // handle special chars
    else{
      HandleSpecialChar(_next_char);
    }
  }
}

void Programmer::WaitForSerial()
{
  while (Serial.available() == 0){};   // loop until char
  char _in = Serial.read();
  _text_buffer[_text_index] = _in;
  _text_index++;

  // actions for special chars
  switch(_in){
    case 0x0D:          // CR
      ParseString();
      _text_index = 0;
      break;
    case 0x08:          // Backspace
      _text_index--;
      break;
    case 0x1B:          // ESC
      Reset();
      break;
  }

  Serial.write(_in);
}