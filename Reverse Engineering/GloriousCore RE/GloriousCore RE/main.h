#pragma once

#pragma comment(lib, "Hid.lib")
#pragma comment(lib, "SetupAPI.lib")

#include <Windows.h>
#include <iostream>
#include <hidsdi.h>
#include <SetupAPI.h>


#define LOG(x) std::cout << x << std::endl;