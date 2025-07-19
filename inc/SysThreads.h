/**************************************************************************//**
 *  @file
 *  @author Steve Lascos
 *  @company Blackaddr Audio
 *
 *  @copyright This software is proprietary and confidential. It may not be
 *  used for any purpose without prior written permission from Blackaddr Audio.
 *  [2020] - [2024] Blackaddr Audio
 *  All Rights Reserved.
 *
 *  NOTICE:  All information contained herein is, and remains the property of
 *  Blackaddr Audio and its suppliers, if any.  The intellectual and technical
 *  concepts contained herein are proprietary to Blackaddr Audio and its
 *  suppliers and may be covered by U.S. and Foreign Patents, patents in
 *  process, and are protected by trade secret or copyright law.
 *  Dissemination of this information or reproduction of this material is
 *  strictly forbidden unless prior written permission is obtained from
 *  Blackaddr Audio.
 *****************************************************************************/

#pragma once

#include <memory>

namespace SysPlatform {

class SysThreads {
public:

    SysThreads();
    virtual ~SysThreads();

    typedef void (*SysThreadFunction)(void*);

    enum {
        NOT_STARTED = 0,
        RUNNING,
        SUSPENDED,
        OTHER
    };

    int addThread(SysThreadFunction p, void * arg=0, int stackSize=-1, void *stack=0);

    int getState(int id);

    int setState(int id, int state);

    int suspend(int id);
    // Restart a suspended thread.
    int restart(int id);

    // Set the slice length time in CPU ticks for a thread
    int setTimeSlice(int id, unsigned ticks);
    int setTimeSliceUs(int id, unsigned microseconds);

    // Get the id of the currently running thread
    int id();

    // Yield current thread's remaining time slice to the next thread, causing immediate
    // context switch
    void yield();

    // Wait for milliseconds using yield(), giving other slices your wait time
    void delay(int milliseconds);

private:
    class _impl; //forward declare
    std::unique_ptr<_impl> m_pimpl;
};

extern SysThreads sysThreads;

}