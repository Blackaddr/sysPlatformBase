#include "sysPlatform/SysTypes.h"
#include "sysPlatform/SysMutex.h"

#if defined(STD_MUTEX_MISSING)
namespace std {

Mutex::mutex();
Mutex::~mutex();
void Mutex::lock();
void Mutex::unlock();

}

#endif
