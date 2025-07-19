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
#include <memory>

namespace SysPlatform {

extern const size_t NVSTORAGE_SIZE_BYTES;

class NvStorage {
public:
    NvStorage();
    virtual ~NvStorage();
    uint8_t read(int idx );
    void write(int idx, uint8_t val);
    void update(int idx, uint8_t in);
    void flush();  // for EEPROM sim, this is used to actually trigger the write

private:
    class _impl;
    std::shared_ptr<_impl> m_pimpl;
};

extern NvStorage sysNvStorage;

}