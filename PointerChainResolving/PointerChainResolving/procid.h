#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>


DWORD GetProcessID(const char* ProcessName);

uintptr_t GetModuleBaseAddress(DWORD ProcessID, const char* ModuleName);

uintptr_t PointerChainResolver(HANDLE ProcessHandle, uintptr_t Pointer, std::vector<unsigned int> Offsets);
