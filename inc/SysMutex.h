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
#ifndef SYSPLATFORM_SYSMUTEX_H_H
#define SYSPLATFORM_SYSMUTEX_H_H

//#define STD_MUTEX_MISSING  // uncomment if std::mutex is not available from compiler

// If you need this library to provide a wrapper and implementation for std::mutex, define
// SYSPLATFORM_STD_MUTEX
#if defined(SYSPLATFORM_STD_MUTEX)
#include <atomic>
namespace std {

class mutex {
public:
    mutex();
    virtual ~mutex();
    void lock();
    void unlock();
    bool try_lock();
private:
    void* mxPtr;
    std::atomic<bool> m_locked;  // optional, handy when underlying lock query isn't supported
};

template <class TMutex> class lock_guard {
private:
    TMutex *r;
public:
    explicit lock_guard(TMutex& m) { r = &m; r->lock(); }
    ~lock_guard() { r->unlock(); }
};

}

// If std::mutex will be provided by some other external library,
// define STD_MUTEX_EXTERNAL such that it includes the necessary header.
// E.g. STD_MUTEZX_EXTERNAL=#include "MyMutex.h"
#elif defined(STD_MUTEX_EXTERNAL)
#include STD_MUTEX_EXTERNAL

// else if your compiler provides std::mutex, do not define anything
#else
#include <mutex>
#endif

#endif
