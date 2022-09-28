#include "procid.h"


DWORD GetProcessID(const char* ProcessName)
{
    DWORD ProcessID = 0;
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 ProcessEntry32;
        ProcessEntry32.dwSize = sizeof(ProcessEntry32);
        if (Process32First(hProcessSnap, &ProcessEntry32))
        {
            do
            {
                if (!_stricmp(ProcessEntry32.szExeFile, ProcessName))
                {
                    ProcessID = ProcessEntry32.th32ProcessID;
                    std::cout << "Process Name : " << ProcessEntry32.szExeFile << '\n'
                        << "Process ID : " << ProcessID << std::endl;
                    break;
                }
            } while (Process32Next(hProcessSnap, &ProcessEntry32));
        }
    }
    CloseHandle(hProcessSnap);

    if (!ProcessID)
    {
        std::cout << "Could not find a process with that name...";
        return 0;
    }

    return ProcessID;
}


uintptr_t GetModuleBaseAddress(DWORD ProcessID, const char* ModuleName)
{
    uintptr_t ModuleBaseAddress = 0;
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hModuleSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 ModuleEntry;
        ModuleEntry.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hModuleSnap, &ModuleEntry))
        {
            do
            {
                if (!_stricmp(ModuleEntry.szModule, ModuleName))
                {
                    ModuleBaseAddress = (uintptr_t)ModuleEntry.modBaseAddr;
                    std::cout << "Module Name : " << ModuleEntry.szModule << '\n'
                        << "Module Base Address : " << std::hex << ModuleBaseAddress << std::endl;
                    break;
                }
            } while (Module32Next(hModuleSnap, &ModuleEntry));
        }
    }
    CloseHandle(hModuleSnap);
    return ModuleBaseAddress;
}
