#include "SysAudio.h"

namespace SysPlatform {

/////////////////////
// SysAudioInputUsb
/////////////////////
struct SysAudioInputUsb::_impl {
    int dummy;
};

SysAudioInputUsb::SysAudioInputUsb(void)
: AudioStream(0, NULL), m_pimpl(std::make_unique<_impl>())
{

}

SysAudioInputUsb::~SysAudioInputUsb()
{

}

void SysAudioInputUsb::update(void)
{

}

void SysAudioInputUsb::begin(void)
{

}

/////////////////////
// SysAudioOutputUsb
/////////////////////
struct SysAudioOSysAudioOutputUsbutputI2S::_impl {
    int dummy;
};

SysAudioOutputUsb::SysAudioOutputUsb(void)
: AudioStream(2, inputQueueArray), m_pimpl(std::make_unique<_impl>())
{

}

SysAudioOutputUsb::~SysAudioOutputUsb()
{

}

void SysAudioOutputUsb::update(void)
{

}

void SysAudioOutputUsb::begin(void)
{
    
}

}