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

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

#define SYS_SUCCESS 0
#define SYS_FAILURE -1

// make sure setup and loop are using C symbols
#ifdef __cplusplus
extern "C" {
#endif
void setup(void);
void loop(void);
#ifdef __cplusplus
} // extern "C"
#endif

///////////////////////////
// Platform specific code
///////////////////////////
// The code below is for items that must be in a public header and cannot be
// wrapped or extracted. Examples are platform critical defines.
#if defined(ARDUINO_TEENSY_MICROMOD)

#ifndef DMAMEM
#define DMAMEM __attribute__ ((section(".dmabuffers"), used))  // puts variables into RAM2 for DMA
#endif

#ifndef PROGMEM
#define PROGMEM __attribute__((section(".progmem")))  // puts variables in flash memory
#endif

#ifndef FLASHMEM
#define FLASHMEM __attribute__((section(".flashmem")))  // puts functions in flash memory
#endif

#elif defined(RASPPI4) || defined(RASPPI5)

#include <algorithm>
#include <cmath>

// TODO: I think we might need to really apply attributes for DMAMEM on RPI
#ifndef DMAMEM
#define DMAMEM
#endif

#ifndef PROGMEM
#define PROGMEM
#endif

#ifndef FLASHMEM
#define FLASHMEM
#endif

 namespace std {
     float nanf(const char* arg);
     float roundf(float val);
     float clamp(float val, float minVal, float maxVal);
}

#else
#error "SysTypes.h: no valid hardware platfrom defined"

#endif
