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

enum class PinMode {
    SYS_INPUT_PIN=0,
    SYS_OUTPUT_PIN,
    SYS_INPUT_PULLUP_PIN
};

class SysIO {
public:
    SysIO();
    virtual ~SysIO();

    int  begin();
    bool scanInputs();

protected:
    bool m_isInitialized = false;
    class _impl;
    std::unique_ptr<_impl> m_pimpl;
};

class SysBounce {
public:
    SysBounce();
    SysBounce(int id, PinMode mode);
    SysBounce(const SysBounce& sysBounce);  // copy constructor, needed because of _impl
    virtual ~SysBounce();

    void setupPin(int id, PinMode mode = PinMode::SYS_INPUT_PIN);
    void debounceIntervalMs(int milliseconds);
    bool read();
    bool update(); // read pin and return true if it's state changed
    bool rose();
    bool fell();
    bool changed();
protected:
    class _impl;
    std::unique_ptr<_impl> m_pimpl;
};

class SysButton : public SysBounce {
public:
    SysButton();
    SysButton(int id, PinMode mode);
    virtual ~SysButton();

    void setPressedState(bool state);
    bool getPressedState();
    bool isPressed();
    bool pressed();
    bool released();
private:
    bool m_stateForPressed = 1;
};

class SysEncoder {
public:
    SysEncoder() = delete;
    SysEncoder(int id);
    SysEncoder(const SysEncoder& sysEncoder);  // copy constructor, needed because of _impl
    virtual ~SysEncoder();

    int read();
private:
    class _impl;
    std::unique_ptr<_impl> m_pimpl;
};

class SysOutput {
public:
    SysOutput();
    SysOutput(int id);

    void setPin(int id);
    void setValue(bool value);
private:
    int m_mappedId = 1;
};

class SysAnalogInput {
public:
    SysAnalogInput();
    SysAnalogInput(int id);

    void setPin(int id);
    int  getValueInt();
private:
    int m_mappedId = 1;
};

int sysAnalogReadInt(int id);


extern SysIO sysIO;

// The following defines set the default control config for Avalon. You can override them
// by defining them at the compilation stage.
#ifndef AVALON_NUM_SW
constexpr uint8_t AVALON_NUM_SW       = 2;
#endif

#ifndef AVALON_NUM_ENCODERS
constexpr uint8_t AVALON_NUM_ENCODERS = 4;
#endif

#ifndef AVALON_NUM_POTS
constexpr uint8_t AVALON_NUM_POTS     = 4;
#endif

#ifndef AVALON_NUM_LEDS
constexpr uint8_t AVALON_NUM_LEDS     = 2;
#endif

extern const int   POT_CALIB_MIN;
extern const int   POT_CALIB_MAX;
extern const bool  POT_SWAP_DIRECTION;
extern const float POT_THRESHOLD;

extern const int   EXP_CALIB_MIN;
extern const int   EXP_CALIB_MAX;
extern const bool  EXP_SWAP_DIRECTION;
extern const float EXP_THRESHOLD;

}
