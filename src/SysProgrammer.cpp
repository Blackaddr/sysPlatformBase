#include "sysPlatform/SysTypes.h"
#include "sysPlatform/SysProgrammer.h"

namespace SysPlatform {

SysProgrammer sysProgrammer;

SysProgrammer::SysProgrammer()
{

}

SysProgrammer::~SysProgrammer()
{

}

void SysProgrammer::begin()
{
    
}

bool SysProgrammer::isXferInProgress()
{
    return false;
}

bool SysProgrammer::isNewProgrammingReceived()
{
    return false;
}

}
