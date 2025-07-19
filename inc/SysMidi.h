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

#include <cstddef>
#include <cstdint>
#include <memory>

namespace SysPlatform {

enum class MidiMessageType : unsigned {
    InvalidType           = 0x00,    ///< For notifying errors
    NoteOff               = 0x80,    ///< Channel Message - Note Off
    NoteOn                = 0x90,    ///< Channel Message - Note On
    AfterTouchPoly        = 0xA0,    ///< Channel Message - Polyphonic AfterTouch
    ControlChange         = 0xB0,    ///< Channel Message - Control Change / Channel Mode
    ProgramChange         = 0xC0,    ///< Channel Message - Program Change
    AfterTouchChannel     = 0xD0,    ///< Channel Message - Channel (monophonic) AfterTouch
    PitchBend             = 0xE0,    ///< Channel Message - Pitch Bend
    SystemExclusive       = 0xF0,    ///< System Exclusive
	SystemExclusiveStart  = SystemExclusive,   ///< System Exclusive Start
    TimeCodeQuarterFrame  = 0xF1,    ///< System Common - MIDI Time Code Quarter Frame
    SongPosition          = 0xF2,    ///< System Common - Song Position Pointer
    SongSelect            = 0xF3,    ///< System Common - Song Select
    Undefined_F4          = 0xF4,
    Undefined_F5          = 0xF5,
    TuneRequest           = 0xF6,    ///< System Common - Tune Request
	SystemExclusiveEnd    = 0xF7,    ///< System Exclusive End
    Clock                 = 0xF8,    ///< System Real Time - Timing Clock
    Undefined_F9          = 0xF9,
    Tick                  = Undefined_F9, ///< System Real Time - Timing Tick (1 tick = 10 milliseconds)
    Start                 = 0xFA,    ///< System Real Time - Start
    Continue              = 0xFB,    ///< System Real Time - Continue
    Stop                  = 0xFC,    ///< System Real Time - Stop
    Undefined_FD          = 0xFD,
    ActiveSensing         = 0xFE,    ///< System Real Time - Active Sensing
    SystemReset           = 0xFF,    ///< System Real Time - System Reset
};

class SysMidiBase {
public:
    SysMidiBase();
    virtual ~SysMidiBase();

    virtual void init() = 0;
    bool isInitialized() { return m_isInitialized; }

    virtual bool read() = 0; // returns true if new MIDI message is available
    virtual MidiMessageType getType() = 0; // returns the type of the last MIDI message
    virtual bool putMsg(uint8_t msg[4]) = 0;

    virtual uint8_t* getSysExArray() = 0;
    virtual size_t   getSysExArrayLength() = 0;
    virtual uint8_t  getChannel() = 0;
    virtual uint8_t  getData1() = 0;
    virtual uint8_t  getData2() = 0;

    virtual void sendSysEx(size_t sysExDataLength, uint8_t* sysExData) = 0;
    virtual void sendProgramChange(unsigned program, unsigned channel) = 0;
    virtual void sendMidiMessage(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2);
protected:
    bool m_isInitialized = false;
};

#if defined(PROCESS_SERIAL_MIDI)
class SysSerialMidi : public SysMidiBase {
public:
    SysSerialMidi();
    virtual ~SysSerialMidi();

    void init() override;

    bool read() override; // returns true if new MIDI message is available
    MidiMessageType getType() override; // returns the type of the last MIDI message
    bool putMsg(uint8_t msg[4]);

    uint8_t* getSysExArray() override;
    size_t   getSysExArrayLength() override;
    uint8_t  getChannel() override;
    uint8_t  getData1() override;
    uint8_t  getData2() override;

    void sendSysEx(size_t sysExDataLength, uint8_t* sysExData) override;
    void sendProgramChange(unsigned program, unsigned channel) override;
    void sendMidiMessage(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2) override;
private:
    class _impl;
    std::unique_ptr<_impl> m_pimpl;
};
extern SysSerialMidi sysSerialMidi;
#endif

#if defined(PROCESS_USB_MIDI)
class SysUsbMidi : public SysMidiBase {
public:
    SysUsbMidi();
    virtual ~SysUsbMidi();

    void init() override;

    bool read() override; // returns true if new MIDI message is available
    MidiMessageType getType() override; // returns the type of the last MIDI message
    bool putMsg(uint8_t msg[4]);

    uint8_t* getSysExArray() override;
    size_t   getSysExArrayLength() override;
    uint8_t  getChannel() override;
    uint8_t  getData1() override;
    uint8_t  getData2() override;

    void sendSysEx(size_t sysExDataLength, uint8_t* sysExData) override;
    void sendProgramChange(unsigned program, unsigned channel) override;
    void sendMidiMessage(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2) override;
private:
    class _impl;
    std::unique_ptr<_impl> m_pimpl;
};
extern SysUsbMidi sysUsbMidi;
#endif

}