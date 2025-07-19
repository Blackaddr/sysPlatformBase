#include "sysPlatform/SysWatchdog.h"

namespace SysPlatform {

SysWatchDog sysWatchDog;

SysWatchDog::SysWatchDog()
{

}

SysWatchdog::~SysWatchDog()
{

}

void SysWatchdog::begin(float seconds)
{


bool SysWatchdog::isStarted()
{
    return false;
}

void SysWatchdog::feed()
{

}

void SysWatchdog::longFeed()
{

}

void SysWatchdog::reset()
{

}


}