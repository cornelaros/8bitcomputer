#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "cpu.h"
#include "memory.h"

RingCounter RINGCOUNTER;
uint8_t clock_state = 0;
uint8_t prev_clock_state = 0;
uint8_t t_state = 0;
Bus BUS(3,
        22, 24, 26, 28, 30, 32, 34, 36,
        23, 25, 27, 29, 31, 33, 35, 37);
Bus INSTRUCTION_REGISTER(4, 5, 6, 7);
ControlBus CONTROLBUS(38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53);
CentralProcessingUnit CPU(BUS, INSTRUCTION_REGISTER, CONTROLBUS, RINGCOUNTER);
Memory MEM(BUS, CONTROLBUS, RINGCOUNTER);

void Run()
{
  clock_state = RINGCOUNTER.GetClkState();
  t_state = RINGCOUNTER.GetTState();
  if(clock_state != prev_clock_state){
    prev_clock_state = clock_state;
    CPU.Run(clock_state, t_state);
    MEM.Run(clock_state);
  }

  // Make sure we disconnect the bus when not outputting
  // Currently, only memory outputs are configured
  // So, disconnect when RO is not set
  if (!(CONTROLBUS.GetControlWord() & RO)) {
    BUS.DisconnectWrite();
  }
}

void setup()
{
  CPU.Reset();
  MEM.Reset();
  RINGCOUNTER.AttachExternal(2);
}

void loop()
{
  Run();
}