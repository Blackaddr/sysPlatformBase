#include "sysPlatform/SysTypes.h"
#include "sysPlatform/SysLogger.h"

namespace SysPlatform {

SysLogger sysLogger;

SysLogger::SysLogger()
{

}

SysLogger::~SysLogger()
{

}

void SysLogger::begin()
{

}

void SysLogger::begin(unsigned baudRate)
{

}

void SysLogger::getSeverityStr(LogSeverity severity, char* str)
{

}


int SysLogger::printf(const char *fmt, ...)
{
    return 0;
}

int SysLogger::vprintf(const char * format, va_list arg)
{
    // return Serial.vprintf(format, arg);
    return 0;
}

void SysLogger::log(const char *pMessage, ...)
{

}

void SysLogger::log(const char *pSource, LogSeverity severity, const char *pMessage, ...)
{

}

unsigned SysLogger::available() {
    return 0;
}

int SysLogger::read()
{
    return SYS_SUCCESS;
}

int SysLogger::printf(const char *fmt, ...)
{
    int result = 0;
    va_list args;

    va_start(args, fmt);
    //result = printf(fmt, args);
    va_end(args);

    return result;
}

SysLogger::operator bool() const
{
    return static_cast<bool>(Serial);
}

void SysLogger::flush()
{

}

}
