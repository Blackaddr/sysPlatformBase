#include "sysPlatform/SysMidi.h"

namespace SysPlatform {

SysMidiBase::SysMidiBase() = default;
SysMidiBase::~SysMidiBase() = default;

bool SysMidiBase::putMsg(uint8_t msg[4]) { return false; }

////////////////
// SERIAL MIDI
////////////////
#if defined(PROCESS_SERIAL_MIDI)
SysSerialMidi sysSerialMidi;

struct SysSerialMidi::_impl {

};

SysSerialMidi::SysSerialMidi()
: m_pimpl(nullptr)
{

}

SysSerialMidi::~SysSerialMidi()
{

}

void SysSerialMidi::init()
{

}

bool SysSerialMidi::read()
{
    return false;
}

MidiMessageType SysSerialMidi::getType()
{
    return MidiMessageType::InvalidType;
}

uint8_t* SysSerialMidi::getSysExArray()
{
    return nullptr;
}

size_t   SysSerialMidi::getSysExArrayLength()
{
    return 0;
}

uint8_t SysSerialMidi::getChannel()
{
    return 0;
}

uint8_t  SysSerialMidi::getData1()
{
    return 0;
}

uint8_t  SysSerialMidi::getData2()
{
    return 0;
}

void SysSerialMidi::sendSysEx(size_t sysExDataLength, uint8_t* sysExData)
{

}

void SysSerialMidi::sendProgramChange(unsigned program, unsigned channel)
{

}

void SysSerialMidi::sendMidiMessage(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2)
{

}
#endif

/////////////
// USB MIDI
/////////////
#if defined(PROCESS_USB_MIDI)
SysUsbMidi sysUsbMidi;

struct SysUsbMidi::_impl {

};

SysUsbMidi::SysUsbMidi()
: m_pimpl(nullptr)
{

}

SysUsbMidi::~SysUsbMidi()
{

}

bool SysUsbMidi::read()
{
    return false;
}

MidiMessageType SysUsbMidi::getType()
{
    return MidiMessageType::NO_MESSAGE;
}

uint8_t* SysUsbMidi::getSysExArray()
{
    return nullptr;
}

size_t   SysUsbMidi::getSysExArrayLength()
{
    return 0;
}

uint8_t SysUsbMidi::getChannel()
{
    return 0;
}

uint8_t  SysUsbMidi::getData1()
{
    return 0;
}

uint8_t  SysUsbMidi::getData2()
{
    return 0;
}

void SysUsbMidi::sendSysEx(size_t sysExDataLength, uint8_t* sysExData)
{

}

void SysUsbMidi::sendProgramChange(unsigned program, unsigned channel)
{

}

void SysUsbMidi::sendMidiMessage(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2)
{

}
#endif

}