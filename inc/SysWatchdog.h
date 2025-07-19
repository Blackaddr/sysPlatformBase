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

namespace SysPlatform {

class SysWatchdog {
public:
    SysWatchdog();
    virtual ~SysWatchdog();

    void begin(float seconds = 0.5f);
    bool isStarted();

    void feed();
    void longFeed();  // feed with an extra long time, useful during startup, etc.
    void reset();
private:
    bool m_isStarted = false;
};

extern SysWatchdog sysWatchdog;

}