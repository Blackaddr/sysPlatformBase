#include <vector>
#include "sysPlatform/SysTypes.h"
#include "sysPlatform/SysThreads.h"

namespace SysPlatform {

SysThreads sysThreads;

class ThreadTask {
public:
    ThreadTask() = delete;
    ThreadTask(SysThreads::ThreadFunction functionToRunIn, void* argIn, int stackSizeIn, void *stackIn)
      // for some reason, using the non-default constructor for CTask results in the task not starting
      //: CTask(stackSize),
      : functionToRun(functionToRunIn), argPtr(argIn), stackSize(stackSizeIn), stack(stackIn)
      {

      }

    SysThreads::ThreadFunction functionToRun;
    void* argPtr;
    int stackSize;
    void* stack = nullptr;
};

struct SysThreads::_impl {
    std::vector<std::shared_ptr<ThreadTask>> threadsVec;
};

SysThreads::SysThreads()
{

}

SysThreads::~SysThreads()
{

}

int SysThreads::addThread(ThreadFunction p, void * arg, int stack_size, void *stack)
{
    return SYS_FAILURE;
}

int SysThreads::getState(int id)
{
    return NOT_STARTED;
}

int SysThreads::setState(int id, int state) {
    return SYS_SUCCESS;
}

int SysThreads::suspend(int id)
{
    return SYS_SUCCESS;
}

int SysThreads::restart(int id)
{
    return SYS_SUCCESS;
}

int SysThreads::setTimeSlice(int id, unsigned ticks)
{
    return SYS_FAILURE;
}

int SysThreads::setTimeSliceUs(int id, unsigned microseconds)
{
    return SYS_FAILURE;
}

int SysThreads::id() {
    return SYS_FAILURE;
}

void SysThreads::yield()
{
    return;
}

void SysThreads::delay(int millisecond)
{
    return;
}

}