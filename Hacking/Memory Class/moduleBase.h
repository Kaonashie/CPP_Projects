#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

class ModuleBackend
{
private:
    HANDLE p_pSnap;
    HANDLE p_mSnap; 
    
    MODULEENTRY32 p_modEntry;
    PROCESSENTRY32 p_processEntry; 
    
    const wchar_t* p_procName; 
     
public:
    HANDLE processHandle;
    DWORD procID; 
    uintptr_t modBaseAddress;

    ModuleBackend()
        : processHandle{NULL}, p_pSnap{NULL}, p_modEntry{NULL},
         procID{NULL}, p_procName{NULL}, p_processEntry{NULL},
         modBaseAddress{NULL}, p_mSnap{NULL}
        
        {
            p_pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (p_pSnap != INVALID_HANDLE_VALUE)
            {
                p_processEntry.dwSize = sizeof(p_processEntry); 
            }

        }

    void GetProcID(const char* procName)
    {
        if (Process32First(p_pSnap, &p_processEntry))
        {
            do 
            {
                if (!_stricmp(p_processEntry.szExeFile, procName))
                {
                    procID = p_processEntry.th32ProcessID;
                    std::cout << "Process ID: " << procID << std::endl; 
                    break;
                }
            }while (Process32Next(p_pSnap, &p_processEntry));
        }
        CloseHandle(p_pSnap); 
    }
    
    void GetModuleBaseAddress(DWORD procID, const char* modName)
    {
        p_mSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
        if (p_mSnap != INVALID_HANDLE_VALUE)
        {
            p_modEntry.dwSize = sizeof(p_modEntry);
            if (Module32First(p_mSnap, &p_modEntry))
            {
                do 
                {
                    if (!_stricmp(p_modEntry.szModule, modName))
                    {
                        modBaseAddress = (uintptr_t)p_modEntry.modBaseAddr;
                        std::cout << "Module base address: " << &modBaseAddress << std::endl; 
                        break;
                    }
                }while (Module32Next(p_mSnap, &p_modEntry));
            }
        }
        CloseHandle(p_mSnap); 
    }

    void GetProcessHandle(DWORD procID)
    {
        processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);
    }

    void ReadProcMemory(HANDLE procHandle, uintptr_t addr)
    {
        ReadProcessMemory(procHandle, (BYTE*)addr, &addr, sizeof(addr), 0);
        std::cout << addr << std::endl; 
    }

};