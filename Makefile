# Library version.  Must use Semantic Versioning 'x.y.z'.  E.g. '1.5.2'
LIB_MAJOR_VER ?= 0
LIB_MINOR_VER ?= 0
LIB_PATCH_VER ?= 0
LIB_VER = $(LIB_MAJOR_VER).$(LIB_MINOR_VER).$(LIB_PATCH_VER)

# Name of the library (do not prefix with 'lib'), e.g. MyUtil
TARGET_NAME = sysPlatform

DOC_PATH_DOXYGEN =

# List of source files (do not include extentions.  E.g. 'MyClass', not 'MyClass.cpp')
#CPP_SRC_LIST = $(subst /$(TARGET_NAME)/,/, $(subst .cpp,,$(wildcard ./$(TARGET_NAME)/*.cpp)))
#CPP_SRC_LIST += $(subst /$(TARGET_NAME)/,/, $(subst .cpp,,$(wildcard ./$(TARGET_NAME)/utility/*.cpp)))
CPP_SRC_LIST += \
    AudioStream \
    SysAudio \
    SysCpuControl \
    SysCpuTelemetry \
    SysCrypto \
    SysDisplay \
    SysInitialize \
    SysIO \
    SysLogger \
    SysMidi \
    SysMutex \
    SysNvStorage \
    SysOTP \
    SysProgrammer \
    SysSerial \
    SysSpi \
    SysThreads \
    SysTimer \
    SysTwoWire \
    SysWatchdog

# Do not include $(TARGET_NAME).h in API_HEADER LIST. This file is required and handled separately.
API_HEADER_LIST += \
    SysTypes \
    SysPlatform \
    AudioSampleRate \
    AudioStream \
    SysAudio \
    SysCpuControl \
    SysCpuTelemetry \
    SysCrypto \
    SysDisplay \
    SysInitialize \
    SysIO \
    SysLogger \
    SysMidi \
    SysMutex \
    SysNvStorage \
    SysOTP \
    SysProgrammer \
    SysSerial \
    SysSpi \
    SysThreads \
    SysTimer \
    SysTwoWire \
    SysWatchdog \
    DMAChannel
    

# List of Git-repo dependencies
DEP_BUILD_LIST =

MAKEFILE_NAME ?= Makefile

# Check if build engine location has already been defined
export LIB_BUILD_ENGINE_LOC ?= $(CURDIR)/scripts/avalon_lib_build_engine/
include $(LIB_BUILD_ENGINE_LOC)/Makefile.inc
