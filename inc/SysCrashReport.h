#pragma once

#ifndef SYSPLATFORM_SYSCRASHREPORT_H_
#define SYSPLATFORM_SYSCRASHREPORT_H_

#include <cstdint>
#include <cstddef>

namespace SysPlatform {

class SysCrashReport {
public:
    static constexpr unsigned NUM_BREADCRUMBS         = 6;

    static constexpr unsigned SETUP_ID                 = 1;
    static constexpr unsigned AUDIO_EFFECT_UPDATE_ID   = 2;
    static constexpr unsigned PRESET_MANAGER_SETPARAM  = 3;
    static constexpr unsigned PRESET_MANAGER_SETPRESET = 4;

	static constexpr uint32_t START_MASK         = 0x8000'0000U;
	static constexpr uint32_t DONE_MASK          = 0x4000'0000U;
	static constexpr uint32_t INVALID_BREADCRUMB = 0xFFFF'FFFFU;

	operator bool();

	static void reset();
	static void disable();
	static void enable();
	static void clear();

	static void setBreadcrumb(unsigned num, uint32_t mask, uint32_t value);

	void   sendReport() const;
	size_t printReport() const;

	static void breadcrumbRaw(unsigned num, unsigned value);

	static uint32_t getBreadcrumb(unsigned num);
	static uint32_t checksum(volatile const void *data, int len);

private:
	static bool m_enabled;
};

extern SysCrashReport sysCrashReport;

}

#endif
