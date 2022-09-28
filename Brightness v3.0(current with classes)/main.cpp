#include "MonitorBackend.h"


int main() 
{
    MonitorBackend* MB = new MonitorBackend;
    MB->GetPrimaryMonitorBrightness();
    MB->SetPrimMonitorBrightness();
    MB->DestroyMonitors();
    

    std::cin.get(); 
}
