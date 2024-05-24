#include "bus.h"
#include "controlbus.h"
#include "ringcounter.h"

// Define hardware interfaces
RingCounter RINGCOUNTER;
Bus BUS(4,
        22, 24, 26, 28, 30, 32, 34, 36,
        23, 25, 27, 29, 31, 33, 35, 37);
ControlBus CONTROLBUS(38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53);

// CPU emulator
struct CentralProcessingUnit
{
  public:
    // Resetting the CPU will also reset the connected hardware components
    void Reset()
    {
      RINGCOUNTER.Reset();
      BUS.SetContent(0x00);
      CONTROLBUS.SetControlWord(MI|II|AI|BI|OI|J|FI); // all registers in
    }

    // Running the computer will start the program from RAM
    void Run()
    {
      uint8_t t = RINGCOUNTER.GetTState();
      
      // test program
      switch(t)
      {
        case 1:
          CONTROLBUS.SetControlWord(CO);
          Serial.println(BUS.GetContent(), BIN);
          break;
        case 2:
          CONTROLBUS.SetControlWord(CE);
          break;
        case 3:
          CONTROLBUS.SetControlWord(NOP);
          break;
        case 4:
          CONTROLBUS.SetControlWord(NOP);
          break;
        case 5:
          CONTROLBUS.SetControlWord(NOP);
          break;
      }

      RINGCOUNTER.Pulse();
    }

  private:
    // private variables and functions
};

// Create CPU object
CentralProcessingUnit CPU;

void setup()
{
  Serial.begin(9600);
  RINGCOUNTER.AttachInternal(2);
  CPU.Reset();
}

void loop()
{
  CPU.Run();
}