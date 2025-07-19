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

namespace SysPlatform {

class  SysCpuControl
{
public:

enum class ShutdownMode : int {
    NONE,
    HALT,
    REBOOT
};

static int halt(void);
static int reboot(void);
static void yield(void);

static void disableIrqs();
static void enableIrqs();

static void AudioNoInterrupts();
static void AudioInterrupts();
static void AudioTriggerInterrupt();
static void AudioSetInterruptPriority(int priority);
static void AudioAttachInterruptVector(void (*function)(void));

static void SysDataSyncBarrier();

static void shutdownUsb();

static void disableWdt();
static void enableWdt();

};

}
