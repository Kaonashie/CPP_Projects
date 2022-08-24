#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

DWORD GetProcessID(const char* ProcessName);

uintptr_t GetModuleBaseAddress(DWORD ProcessID, const char* ModuleName);