#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "cpu.h"
#include "memory.h"

// Define hardware interfaces
RingCounter RINGCOUNTER;
Bus BUS(7,
        22, 24, 26, 28, 30, 32, 34, 36,
        23, 25, 27, 29, 31, 33, 35, 37);
ControlBus CONTROLBUS(38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53);

// Create CPU object
CentralProcessingUnit CPU(BUS, CONTROLBUS, RINGCOUNTER);

// Create memory object
Memory MEM(BUS, CONTROLBUS, RINGCOUNTER);

void Run()
{
  CPU.Run();
  MEM.Run();

  // Make sure we disconnect the bus when not outputting
  // Currently, only memory outputs are configured
  // So, disconnect when RO is not set
  if (!(CONTROLBUS.GetControlWord() & RO)) {
    BUS.DisconnectWrite();
  }
}

void setup()
{
  // First, reset CPU and RAM
  CPU.Reset();
  MEM.Reset();

  // Lastly, attach ring counter
  RINGCOUNTER.AttachExternal(2);

  // For debugging purposes
  Serial.begin(9600);
}

void loop()
{
  Run();
}