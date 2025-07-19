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

class SysOTP {
public:
    static int      begin();
    static uint64_t getUidLower();
    static uint64_t getUidUpper();
    static uint32_t getDevicePBKHLower();
    static uint32_t getDevicePBKHUpper();
    static uint32_t getDevelPBKHLower();
    static uint32_t getDevelPBKHUpper();
    static uint32_t getEUIDHLower();
    static uint32_t getEUIDHUpper();
    static uint16_t getProductId();
    static uint32_t getLocks();

};

}