#include "sysPlatform/SysTypes.h"
#include "sysPlatform/SysCpuControl.h"

namespace SysPlatform {


int  SysCpuControl::halt(void)
{
    return SYS_SUCCESS;
}

int  SysCpuControl::reboot(void)
{
    return SYS_SUCCESS;
}

void  SysCpuControl::yield(void) {
    return;
}

void SysCpuControl::disableIrqs()
{

}

void SysCpuControl::enableIrqs()
{

}

void SysCpuControl::AudioNoInterrupts()
{

}

void SysCpuControl::AudioInterrupts()
{

}

void SysCpuControl::AudioTriggerInterrupt()
{

}

void SysCpuControl::AudioSetInterruptPriority(int priority)
{

}

void SysCpuControl::AudioAttachInterruptVector(void (*function)(void))
{

}

void SysCpuControl::SysDataSyncBarrier()
{

}

void SysCpuControl::shutdownUsb()
{

}

void SysCpuControl::disableWdt()
{

}

void SysCpuControl::enableWdt()
{

}


}
