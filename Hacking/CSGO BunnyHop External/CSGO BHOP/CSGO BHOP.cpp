#include "procid.h"
/*
DWORD GetProcessID(const char* ProcessName);

uintptr_t GetModuleBaseAddress(DWORD ProcessID, const char* ModuleName);

uintptr_t PointerChainResolver(HANDLE ProcessHandle, uintptr_t Pointer, std::vector<unsigned int> Offsets);

 */

struct GameOffsets
{
	DWORD Player = 0xDC14BC;
	DWORD Jump = 0x528790C;
	DWORD Flags = 0x104;
}Offsets;



int main()
{
	DWORD ProcessID = GetProcessID("csgo.exe");
	uintptr_t ModuleBase = GetModuleBaseAddress(ProcessID, "client.dll");
	HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	DWORD PlayerOffset = ModuleBase + 0xDC14BC;
	DWORD LocalPlayer{};
	ReadProcessMemory(ProcessHandle, (BYTE*)PlayerOffset, &LocalPlayer, sizeof(DWORD), nullptr);

	while (true)
	{
		DWORD FlagOffset = LocalPlayer + 0x104;
		BYTE Flag{};
		ReadProcessMemory(ProcessHandle, (BYTE*)FlagOffset, &Flag, sizeof(Flag), 0);

		if (GetAsyncKeyState(VK_SPACE) && Flag & (1 << 0))
		{
			DWORD JumpOffset = ModuleBase + 0x528790C;
			BYTE Jump{6};

			WriteProcessMemory(ProcessHandle, (BYTE*)JumpOffset, &Jump, sizeof(Jump), 0);
		}
		Sleep(1);
	}

	return 0; 
}