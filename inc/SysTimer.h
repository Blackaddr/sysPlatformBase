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

#include <cstdint>
#include <atomic>

namespace SysPlatform {

class SysTimer {
public:
// milliseconds since program start
static uint32_t millis();

// microseonds since program start
static uint32_t micros();

// CPU cycle counts since program start
static uint32_t cycleCnt32();
static uint64_t cycleCnt64();

static void delayMilliseconds(unsigned x); // delay in milliseconds
static void delayMicroseconds(unsigned x);

};

using SysIntervalTimerCallback_t = void (*)(void);
class SysIntervalTimer {
public:
    SysIntervalTimer() = default;
    virtual ~SysIntervalTimer() = default;

    template <typename period_t>
    void begin(SysIntervalTimerCallback_t funct, period_t period) {}
};

class ElapsedMicros
{
private:
    std::atomic<unsigned long> us{0};
public:
	ElapsedMicros(void) { us = SysTimer::micros(); }
	ElapsedMicros(unsigned long val) { us = SysTimer::micros() - val; }
	ElapsedMicros(const ElapsedMicros &orig) {unsigned long tmp = orig.us; us = tmp; }
	operator volatile unsigned long () const { return SysTimer::micros() - (volatile unsigned long)us; }
	ElapsedMicros & operator = (const ElapsedMicros &rhs) { unsigned long tmp = rhs.us; us = tmp; return *this; }
	ElapsedMicros & operator = (unsigned long val) { us = SysTimer::micros() - val; return *this; }
	ElapsedMicros & operator -= (unsigned long val)      { us += val ; return *this; }
	ElapsedMicros & operator += (unsigned long val)      { us -= val ; return *this; }
	ElapsedMicros operator - (int val) const           { ElapsedMicros r(*this); r.us += val; return r; }
	ElapsedMicros operator - (unsigned int val) const  { ElapsedMicros r(*this); r.us += val; return r; }
	ElapsedMicros operator - (long val) const          { ElapsedMicros r(*this); r.us += val; return r; }
	ElapsedMicros operator - (unsigned long val) const { ElapsedMicros r(*this); r.us += val; return r; }
	ElapsedMicros operator + (int val) const           { ElapsedMicros r(*this); r.us -= val; return r; }
	ElapsedMicros operator + (unsigned int val) const  { ElapsedMicros r(*this); r.us -= val; return r; }
	ElapsedMicros operator + (long val) const          { ElapsedMicros r(*this); r.us -= val; return r; }
	ElapsedMicros operator + (unsigned long val) const { ElapsedMicros r(*this); r.us -= val; return r; }
};

class ElapsedMillis
{
private:
    std::atomic<unsigned long> ms{0};
public:
	ElapsedMillis(void) { ms = SysTimer::millis(); }
	ElapsedMillis(unsigned long val) { ms = SysTimer::millis() - val; }
	ElapsedMillis(const ElapsedMillis &orig) { unsigned long tmp = orig.ms; ms = tmp; }
	operator volatile unsigned long () const { return SysTimer::millis() - (volatile unsigned long)ms; }
	ElapsedMillis & operator = (const ElapsedMillis &rhs) { unsigned long tmp = rhs.ms; ms = tmp; return *this; }
	ElapsedMillis & operator = (unsigned long val) { ms = SysTimer::millis() - val; return *this; }
	ElapsedMillis & operator -= (unsigned long val)      { ms += val ; return *this; }
	ElapsedMillis & operator += (unsigned long val)      { ms -= val ; return *this; }
	ElapsedMillis operator - (int val) const           { ElapsedMillis r(*this); r.ms += val; return r; }
	ElapsedMillis operator - (unsigned int val) const  { ElapsedMillis r(*this); r.ms += val; return r; }
	ElapsedMillis operator - (long val) const          { ElapsedMillis r(*this); r.ms += val; return r; }
	ElapsedMillis operator - (unsigned long val) const { ElapsedMillis r(*this); r.ms += val; return r; }
	ElapsedMillis operator + (int val) const           { ElapsedMillis r(*this); r.ms -= val; return r; }
	ElapsedMillis operator + (unsigned int val) const  { ElapsedMillis r(*this); r.ms -= val; return r; }
	ElapsedMillis operator + (long val) const          { ElapsedMillis r(*this); r.ms -= val; return r; }
	ElapsedMillis operator + (unsigned long val) const { ElapsedMillis r(*this); r.ms -= val; return r; }
};

class ElapsedSeconds
{
private:
    std::atomic<unsigned long> s{0};
public:
	ElapsedSeconds(void) { s = SysTimer::millis()/1000; }
	ElapsedSeconds(unsigned long val) { s = SysTimer::millis()/1000 - val; }
	ElapsedSeconds(const ElapsedSeconds &orig) { unsigned long tmp = orig.s; s = tmp; }
	operator volatile unsigned long () const { return SysTimer::millis()/1000 - (volatile unsigned long)s; }
	ElapsedSeconds & operator = (const ElapsedSeconds &rhs) {unsigned long tmp = rhs.s; s = tmp; return *this; }
	ElapsedSeconds & operator = (unsigned long val) { s = SysTimer::millis()/1000 - val; return *this; }
	ElapsedSeconds & operator -= (unsigned long val)      { s += val ; return *this; }
	ElapsedSeconds & operator += (unsigned long val)      { s -= val ; return *this; }
	ElapsedSeconds operator - (int val) const           { ElapsedSeconds r(*this); r.s += val; return r; }
	ElapsedSeconds operator - (unsigned int val) const  { ElapsedSeconds r(*this); r.s += val; return r; }
	ElapsedSeconds operator - (long val) const          { ElapsedSeconds r(*this); r.s += val; return r; }
	ElapsedSeconds operator - (unsigned long val) const { ElapsedSeconds r(*this); r.s += val; return r; }
	ElapsedSeconds operator + (int val) const           { ElapsedSeconds r(*this); r.s -= val; return r; }
	ElapsedSeconds operator + (unsigned int val) const  { ElapsedSeconds r(*this); r.s -= val; return r; }
	ElapsedSeconds operator + (long val) const          { ElapsedSeconds r(*this); r.s -= val; return r; }
	ElapsedSeconds operator + (unsigned long val) const { ElapsedSeconds r(*this); r.s -= val; return r; }
};

}
