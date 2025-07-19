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

#include <cstdint>
#include <cstddef>

namespace SysPlatform {

class SysSHA256 {
public:
   SysSHA256();
   virtual ~SysSHA256();

    void reset();
    void update(const void *data, size_t len);
    void finalize(void *hash, size_t len);

};

class SysEd25519 {
public:
    static bool verify(const uint8_t signature[64], const uint8_t publicKey[32],
                       const void *message, size_t len);
};

}
