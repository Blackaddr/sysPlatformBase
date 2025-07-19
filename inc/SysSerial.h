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
#include <cstddef>
#include <cstdarg>

namespace SysPlatform {

class SysSerial {
public:
    SysSerial(unsigned busId = 0);
    virtual ~SysSerial();

    void begin(uint32_t baud = 115200);
    int available();
    int read();
    size_t write(uint8_t dataByte); // blocking call
    size_t write(uint8_t* buffer, size_t bufferSizeBytes);
    void flush(void);

    int printf(const char *fmt, ...);
    //int printf(const char* str, const char *fmt, ...);

    // This allows you use check if the serial port is valid with if (sysSerial), etc.
    explicit operator bool();
    // operator bool() const {
    //     return false;
    // }
};

extern SysSerial sysSerial;

}
