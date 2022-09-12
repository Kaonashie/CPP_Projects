#include "procid.h"





int main()
{
    DWORD ProcessID = GetProcessID("ac_client.exe");
    if (!ProcessID)
    {
        return 1; // Code No process ID found 
    }

    uintptr_t ModuleBase = GetModuleBaseAddress(ProcessID, "ac_client.exe");

    HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);

    uintptr_t DynamicPlayerPointer = ModuleBase + 0x17E0A8;
    std::vector<unsigned int> AmmoOffsets = { 0x140, 0x0 };
    std::vector<unsigned int> XAngleOffset = { 0x38 , 0x0 };



    while (ProcessHandle)
    {
        uintptr_t AmmoValue = PointerChainResolver(ProcessHandle, DynamicPlayerPointer, AmmoOffsets);
        std::cout << "\r" << "Ammo Value : "<< std::dec << (uint16_t)AmmoValue << " ";
        Sleep(100);
    }
    return 0;

}
