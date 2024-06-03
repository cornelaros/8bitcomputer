#include <inttypes.h>

#include "controlbus.h"

const uint8_t NOP = 0b0000;
const uint8_t LDA = 0b0001;
const uint8_t ADD = 0b0010;
const uint8_t SUB = 0b0011;
const uint8_t STA = 0b0100;
const uint8_t LDI = 0b0101;
const uint8_t JMP = 0b0110;
const uint8_t JC  = 0b0111;
const uint8_t JZ  = 0b1000;
const uint8_t OUT = 0b1110;
const uint8_t HLT = 0b1111;

static const uint16_t ucode[16][8]
{
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 0000 - NOP
  { MI|CO,  RO|II|CE,  IO|MI,  RO|AI,  0,           0, 0, 0 },   // 0001 - LDA
  { MI|CO,  RO|II|CE,  IO|MI,  RO|BI,  EO|AI|FI,    0, 0, 0 },   // 0010 - ADD
  { MI|CO,  RO|II|CE,  IO|MI,  RO|BI,  EO|AI|SU|FI, 0, 0, 0 },   // 0011 - SUB
  { MI|CO,  RO|II|CE,  IO|MI,  AO|RI,  0,           0, 0, 0 },   // 0100 - STA
  { MI|CO,  RO|II|CE,  IO|AI,  0,      0,           0, 0, 0 },   // 0101 - LDI
  { MI|CO,  RO|II|CE,  IO|J,   0,      0,           0, 0, 0 },   // 0110 - JMP
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 0111 - JC
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1000 - JZ
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1001
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1010
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1011
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1100
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1101
  { MI|CO,  RO|II|CE,  AO|OI,  0,      0,           0, 0, 0 },   // 1110 - OUT
  { MI|CO,  RO|II|CE,  CH,     0,      0,           0, 0, 0 },   // 1111 - HLT
};