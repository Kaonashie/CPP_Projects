#include "moduleBase.h"

int main()
{
    ModuleBackend MB; 
    MB.GetProcID("VampireSurvivors.exe");
    MB.GetModuleBaseAddress(MB.procID, "VampireSurvivors.exe");
    MB.GetProcessHandle(MB.procID); 
    MB.ReadProcMemory(MB.processHandle, 0x1FAA1334);


    return 0; 
}