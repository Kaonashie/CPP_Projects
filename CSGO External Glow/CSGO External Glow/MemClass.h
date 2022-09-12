#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <cstdint>
#include <string_view>


class MemClass
{
private:
	std::uintptr_t ProcessID = 0; 
	void* ProcessHandle = nullptr;

public: 
	MemClass(const std::string_view  ProcessName)
	{
		::PROCESSENTRY32 Entry = { };
		Entry.dwSize = sizeof(::PROCESSENTRY32);
		const auto SnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (SnapShot != INVALID_HANDLE_VALUE)

			while (::Process32Next(SnapShot, &Entry))
			{
				if (!ProcessName.compare(Entry.szExeFile))
				{
					ProcessID = Entry.th32ProcessID;
					ProcessHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID); 
					break;
				}
			}
		if (SnapShot) ::CloseHandle(SnapShot);
	}


	~MemClass()
	{
		if (ProcessHandle)
			::CloseHandle(ProcessHandle);
	}

	const std::uintptr_t GetModuleAddress(const std::string_view ModuleName) const noexcept
	{
		::MODULEENTRY32 Entry = { };
		Entry.dwSize = sizeof(::MODULEENTRY32);
		const auto SnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID); 
		std::uintptr_t Result = 0; 
		if (SnapShot != INVALID_HANDLE_VALUE)
			while (::Module32Next(SnapShot, &Entry))
			{
				if (!ModuleName.compare(Entry.szModule))
				{
					Result = reinterpret_cast<std::uintptr_t>(Entry.modBaseAddr);
					break;
				}
			}
		if (SnapShot)
			::CloseHandle(SnapShot);

		return Result;
	}


	// Read Process Memory
	template <typename T>
	constexpr const T Read(const std::uintptr_t& Address) const noexcept
	{
		T Value = { };
		::ReadProcessMemory(ProcessHandle, reinterpret_cast<const void*>(Address), &Value, sizeof(T), NULL);
		return Value; 
	}

	// Write Process Memory

	template <typename T>
	constexpr void Write(const std::uintptr_t& Address, const T& Value) const noexcept
	{
		::WriteProcessMemory(ProcessHandle, reinterpret_cast<void*>(Address), &Value, sizeof(T), NULL); 
	}

};

