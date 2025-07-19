#pragma once

#include "sysPlatform/SysMutex.h"
#include "sysPlatform/SysLogger.h"

namespace SysPlatform {

void sysEnableDebugPrint();
void sysDisableDebugPrint();
bool isSysDebugPrintEnabled();

extern std::mutex g_sysSerialLock;
extern volatile bool g_sysDebugPrintEnable;

}

#ifdef NO_PRINTF
#define SYS_DEBUG_PRINT(x)
#else
#define SYS_DEBUG_PRINT(x) {if (SysPlatform::g_sysDebugPrintEnable) { std::lock_guard<std::mutex> lck(SysPlatform::g_sysSerialLock); x;}}
#endif
