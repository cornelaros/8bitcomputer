#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"
#include "cpu.h"

// Define hardware interfaces
RingCounter RINGCOUNTER;
Bus BUS(7,
        22, 24, 26, 28, 30, 32, 34, 36,
        23, 25, 27, 29, 31, 33, 35, 37);
ControlBus CONTROLBUS(38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53);

// Create CPU
CentralProcessingUnit CPU(BUS, CONTROLBUS, RINGCOUNTER);

void setup()
{
  // First, reset CPU  
  CPU.Reset();

  // Lastly, attach ring counter
  RINGCOUNTER.AttachExternal(2);
}

void loop()
{
  CPU.Run();
}