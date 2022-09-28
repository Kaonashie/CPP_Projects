#pragma once
#include <iostream>
#include <Windows.h>
#include <SetupAPI.h>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>

#pragma comment(lib, "SetupApi.lib")
#pragma comment(lib, "Dxva2.lib")

HMONITOR GetPrimaryMonitorHandle();
HANDLE GetPhysicalMonitor();
void SetPrimaryMonitorBrightness();

class MonitorBackend
{
private: 

    HMONITOR p_primaryMonitorHandle; 
    LPPHYSICAL_MONITOR p_physicalMonitors;
    HANDLE p_goodHandle;
    POINT p_ptZero;
    HMONITOR p_hHandle;
    DWORD p_numPhysicalMonitors;
    BOOL p_numPhysicalMonitorsBool; 
    BOOL p_pOK;
    BOOL p_bOK;
    int x; 
    
public: 

    DWORD min, cur, max;
    MonitorBackend()
        : p_physicalMonitors{NULL}, p_goodHandle{NULL},
         p_ptZero{NULL},  
         p_numPhysicalMonitors{NULL}, 
         p_pOK{NULL}, p_bOK{NULL}, p_primaryMonitorHandle{NULL},
         min{0}, cur{0}, max{0}
         {
            // Main constructor
            p_ptZero = { 0, 0 }; 
            p_hHandle = MonitorFromPoint(p_ptZero, MONITOR_DEFAULTTOPRIMARY);
            p_numPhysicalMonitorsBool = GetNumberOfPhysicalMonitorsFromHMONITOR(p_hHandle, &p_numPhysicalMonitors);
            p_physicalMonitors = (LPPHYSICAL_MONITOR)malloc(p_numPhysicalMonitors * sizeof(PHYSICAL_MONITOR));
            if (p_physicalMonitors)
            {
                p_pOK = GetPhysicalMonitorsFromHMONITOR(p_hHandle, p_numPhysicalMonitors, p_physicalMonitors);
                if (p_pOK)
                    p_goodHandle = p_physicalMonitors[0].hPhysicalMonitor;
            }
         }

    void SetPrimMonitorBrightness()
    {
        GetInput(); 
        p_bOK = SetMonitorBrightness(p_goodHandle, x);
        if (p_bOK)
            std::cout << "work" << std::endl;
        else
            std::cout << "no work" << std::endl;
    }

    void GetPrimaryMonitorBrightness()
    {
        GetMonitorBrightness(p_goodHandle, &min, &cur, &max); 
        std::cout << "Current Brightness : " << cur << std::endl; 
    }

    void DestroyMonitors()
    {
        DestroyPhysicalMonitors(p_numPhysicalMonitors, p_physicalMonitors); 
        DestroyPhysicalMonitor(p_physicalMonitors); 
        free(p_physicalMonitors);
    }

    void GetInput()
    {
        std::cin >> x; 
        if (x < 0 || x > 100)
        {
            std::cout << "Number not between 0 and 100. Using default 100" << std::endl;
            std::cin.get(); 
            x = 100; 
        }
    }
};