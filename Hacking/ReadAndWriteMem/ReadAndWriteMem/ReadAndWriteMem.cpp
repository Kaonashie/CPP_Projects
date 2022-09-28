#include "procid.h"

/*
	Functions from procid module.

 	DWORD GetProcessID(const char* ProcessName);

	uintptr_t GetModuleBaseAddress(DWORD ProcessID, const char* ModuleName);
 
 */


int main()
{
    DWORD ProcessID = GetProcessID("notepad.exe");
    if (!ProcessID)
    {
        return 1; // Code No process ID found 
    }

	uintptr_t ModuleBase = GetModuleBaseAddress(ProcessID, "user32.dll");

    HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
    LPVOID mem{};
    ReadProcessMemory(ProcessHandle, (LPVOID)ModuleBase, &mem, sizeof(mem), nullptr);
    std::cout << "Module Base Address Value : " << std::hex << mem << std::endl;
    
}

