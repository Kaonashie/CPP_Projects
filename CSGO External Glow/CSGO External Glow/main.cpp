#include "main.h"
#include "MemClass.h"
#include <thread>

namespace Offsets
{
	// client.dll 
	constexpr auto LocalPlayer = 0xDC14CC;
	constexpr auto EntityList = 0x4DDD91C;
	constexpr auto GlowObjectManager = 0x53265D0;

	// Entity
	constexpr auto TeamNumber = 0xF4;
	constexpr auto GlowIndex = 0x10488; 
}

int main()
{
	auto mem = MemClass{ "csgo.exe" };
	const auto client = mem.GetModuleAddress("client.dll");

	while (true)
	{
		const auto LocalPlayer = mem.Read<std::uintptr_t>(client + Offsets::LocalPlayer);
		const auto GlowObjectManager = mem.Read<std::uintptr_t>(client + Offsets::GlowObjectManager);

		for (auto i = 0; i < 32; ++i)
		{
			const auto Entity = mem.Read<std::uintptr_t>(client + Offsets::EntityList + i * 0x10); 

			if (mem.Read<std::uintptr_t>(Entity + Offsets::TeamNumber) == mem.Read<std::uintptr_t>(LocalPlayer + Offsets::TeamNumber))
				continue; 

			const auto GlowIndex = mem.Read<std::int32_t>(Entity + Offsets::GlowIndex); 

			mem.Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0x8, 1.f);	// R
			mem.Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0xC, 0.f);	// G
			mem.Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0x10, 0.f);	// B
			mem.Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0x14, 1.f);	// A
			
			
			mem.Write<bool>(GlowObjectManager + (GlowIndex * 0x38) + 0x27, true);	
			mem.Write<bool>(GlowObjectManager + (GlowIndex * 0x38) + 0x28, true);	
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
	}
	return 0; 
}