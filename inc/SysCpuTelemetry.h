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

#ifndef SYSPLATFORM_SYSCPU_TELEMETRY_H_
#define SYSPLATFORM_SYSCPU_TELEMETRY_H_

#include <cstddef>

namespace SysPlatform {

class  SysCpuTelemetry
{
public:
    static unsigned getCpuFreqHz();
    static float    getTemperatureCelcius();

    static void   markUnusedStack();
    static size_t getStackSizeBytes();
    static size_t getStackUsedBytes();
    static size_t getStackFreeBytes();
    static float  getStackUsageRatio();

    static size_t getHeapSizeBytes();
    static size_t getHeapUsedBytes();
    static size_t getHeapFreeBytes();
    static float  getHeapUsageRatio();

    static size_t getRam0Size();
    static float  getRam0UsageRatio();
    static size_t getRam1Size();
    static float  getRam1UsageRatio();

    static void debugShowMemoryConfig();
};

}

#endif // SYSPLATFORM_SYSCPU_TELEMETRY_H_