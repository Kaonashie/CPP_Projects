#include "pch.h"
#include <Windows.h>

struct GameOffsets
{
    DWORD Player = 0xDC14BC;
    DWORD Jump = 0x528790C;
    DWORD Flags = 0x104;
}Offsets;

struct values
{
    DWORD LocalPlayer;
    DWORD GameModule;
    BYTE Flag;
}val;


void main()
{
    val.GameModule = (DWORD)GetModuleHandle(L"client.dll");
    val.LocalPlayer = *(DWORD*)(val.GameModule + Offsets.Player);

    if (val.LocalPlayer == NULL)
        while (val.LocalPlayer == NULL)
            val.LocalPlayer = *(DWORD*)(val.GameModule + Offsets.Player);

    while (true)
    {
        val.Flag = *(BYTE*)(val.LocalPlayer + Offsets.Flags);

        if (GetAsyncKeyState(VK_SPACE) && val.Flag & (1 << 0))
        	*(DWORD*)(val.GameModule + Offsets.Jump) = 6;
    }
}




BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
	    }

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

