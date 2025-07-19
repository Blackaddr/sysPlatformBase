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

#ifndef SYSPLATFORM_SYSLOGGER_H_
#define SYSPLATFORM_SYSLOGGER_H_

#include <cstdarg>
#include <sysPlatform/SysDebugPrint.h>

namespace SysPlatform {

class SysLogger {
public:
    SysLogger();
    virtual ~SysLogger();

    enum LogSeverity {
        LogPanic,	///< Halt the system after processing this message
        LogError,	///< Severe error in this component, system may continue to work
        LogWarning,	///< Non-severe problem, component continues to work
        LogNotice,	///< Informative message, which is interesting for the system user
        LogDebug	///< Message, which is only interesting for debugging this component
    };

    void begin();
    void begin(unsigned baudRate);

    void getSeverityStr(LogSeverity severity, char* str);

    int printf(const char *fmt, ...);
    int vprintf(const char * format, va_list arg);

    void log(const char *pMessage, ...);
    void log(const char *pSource, LogSeverity severity, const char *pMessage, ...);

    unsigned available();
    int      read();
    void     flush();

    explicit operator bool() const;
};

extern SysLogger sysLogger;

}

#endif // SYSPLATFORM_SYSLOGGER_H_