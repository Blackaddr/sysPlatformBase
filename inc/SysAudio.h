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
#include "sysPlatform/AudioStream.h"

namespace SysPlatform {

class SysCodec {
public:
    SysCodec();
    virtual ~SysCodec();

    void begin(void);

    /// Mute and power down the codec.
    void disable(void);

    /// First disable, then cleanly power up and unmute the codec.
    virtual void enable(void);

    bool isEnabled();

    // When enabled, the gain controls are locked
    void setGainLock(bool lockEnabled);

    /// Set the input gain of the codec's PGA for the left (TRS Tip) channel.
    /// @param val an interger value from 31 = +12dB . . 1.5dB steps down to 0 = -34.5dB
    void setLeftInputGain(int val);
    int getLeftInputGain();

    /// Set the input gain of the codec's PGA for the right (TRS Ring) channel.
    /// @param val an interger value from 31 = +12dB . . 1.5dB steps down to 0 = -34.5dB
    void setRightInputGain(int val);
    int getRightInputGain();

    /// Mute/unmute the Left (TRS Tip) channel at the ADC input.
    /// @param val when true, channel is muted, when false, channel is unmuted
    void setLeftInMute(bool val);

    /// Mute/unmute the Right (TRS Ring) channel at the ADC input.
    /// @param val when true, channel is muted, when false, channel is unmuted
    void setRightInMute(bool val);

    /// Links the Left/Right channel contols for mute and input gain.
    /// @details when true, changing either the left or right gain/mute controls will
    /// affect both channels.
    /// @param val when true, channels are linked, when false, they are controlled separately
    void setLinkLeftRightIn(bool val);

    /// Swaps the left and right channels in the codec.
    /// @param val when true, channels are swapped, else normal.
    /// @returns true when successful, false if not supported
    bool setLeftRightSwap(bool val);

    /// Set the volume for the codec's built-in headphone amp
    /// @param volume the input volume level from 0.0f to 1.0f;
    /// @returns true if successful, false if not supported
    bool setHeadphoneVolume(float volume);

    /// Mute/unmute the output DAC, affects both Left and Right output channels.
    /// @param when true, output DAC is muted, when false, unmuted.
    /// @returns true if successful, false if not supported
    bool setDacMute(bool val);

    /// ADC Bypass control.
    /// @details This permits the analog audio from the Codec's PGA to bypass the ADC
    /// and go directly to the analog output of the codec, bypassing the digital domain
    /// entirely.
    /// @param val when true, analog ADC input is fed directly to codec analog output
    /// @param returns true if successful, false if not supported.
    bool setAdcBypass(bool val);

    /// Soft-reset the codec.
    /// @details This will cause the codec to reset its internal registers to default values.
    void resetCodec(void);

    /// Recalibrate the DC offset removal
    /// @details This function will temporarily mute the inputs, enable the CODEC's
    /// HPF in order to calculate the DC offset (which is subtracted out). Then the filter
    /// is disabled.
    /// @returns true if successful, false if not supported
    bool recalibrateDcOffset(void);

    /// Write a custom command to the codec via I2C control interface.
    /// @details See WM8731 datasheet for register map details.
    /// @param addr The register address you wish to write to, range 0 to 15.
    /// @param val the 9-bit data value you wish to write at the address specifed.
    bool writeI2C(unsigned int addr, unsigned int val);

    static SysCodec& getCodec();

private:
	struct _impl;
	std::unique_ptr<_impl> m_pimpl;
};

class SysAudioIO {
public:
    virtual void enable() = 0;
    virtual void disable() = 0;
protected:
    bool m_enable = false;
};

class SysAudioGlobalBypass : public SysAudioIO
{
public:
    SysAudioGlobalBypass(void);
    virtual ~SysAudioGlobalBypass();
    void enable() override;
    void disable() override;
    virtual void bypass(bool byp);
    static SysAudioGlobalBypass& getGlobalBypass();
protected:
    struct _impl;
    std::unique_ptr<_impl> m_pimpl;
};

class SysAudioInputI2S : public AudioStream, public SysAudioIO
{
public:
    SysAudioInputI2S(void);
    virtual ~SysAudioInputI2S();
    virtual void update(void);
    void begin(void);
    void enable() override;
    void disable() override;
protected:
    bool m_isInitialized = false;
    struct _impl;
    std::unique_ptr<_impl> m_pimpl;
};

class SysAudioOutputI2S : public AudioStream, public SysAudioIO
{
public:
    SysAudioOutputI2S(void);
    virtual ~SysAudioOutputI2S();

    virtual void update(void);
    void begin(void);
    void enable() override;
    void disable() override;
    friend class SysAudioInputI2S;

protected:
    bool m_isInitialized = false;
    audio_block_t *inputQueueArray[2];

    struct _impl;
    std::unique_ptr<_impl> m_pimpl;
};

class SysAudioInputUsbImpl;
class SysAudioInputUsb : public AudioStream, public SysAudioIO
{
public:
    SysAudioInputUsb(void);
    virtual ~SysAudioInputUsb();
    virtual void update(void);
    void begin(void);
    void enable() override;
    void disable() override;
    float volume(void);
protected:
	bool m_isInitialized = false;
    struct _impl;
	std::unique_ptr<_impl> m_pimpl;
    friend SysAudioInputUsbImpl;
};

class SysAudioOutputUsbImpl;
class SysAudioOutputUsb : public AudioStream, public SysAudioIO
{
public:
    SysAudioOutputUsb(void);
    virtual ~SysAudioOutputUsb();

    virtual void update(void);
    void begin(void);
    void enable() override;
    void disable() override;
    friend class SysAudioInputUsb;

protected:
	bool m_isInitialized = false;
	audio_block_t *inputQueueArray[2];

	struct _impl;
	std::unique_ptr<_impl> m_pimpl;
    friend SysAudioOutputUsbImpl;
};

extern SysCodec sysCodec;
extern SysAudioGlobalBypass sysAudioGlobalBypass;

}
