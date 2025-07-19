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

extern const size_t SYS_SPI_MEM_SIZE;
constexpr unsigned NUM_MEM_SLOTS = 1;

class SysSpiSettings {
public:
    SysSpiSettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {}
    SysSpiSettings() {}
};

class SysSpi {
public:
    SysSpi() = delete;
    SysSpi(bool useDma = true);
    virtual ~SysSpi();

    void beginTransaction(SysSpiSettings settings);
    uint8_t transfer(uint8_t data);
    uint16_t transfer16(uint16_t data);
    void transfer(void *buf, size_t count);
    void endTransaction(void);

    /// initialize and configure the SPI peripheral
	void begin();

	/// write a single 8-bit word to the specified address
	/// @param address the address in the SPI RAM to write to
	/// @param data the value to write
	void write(size_t address, uint8_t data);

	/// Write a block of 8-bit data to the specified address. Be check
    /// isWriteBusy() before sending the next DMA transfer.
	/// @param address the address in the SPI RAM to write to
	/// @param src pointer to the source data block
	/// @param numBytes size of the data block in bytes
	void write(size_t address, uint8_t *src, size_t numBytes);

	/// Write a block of zeros to the specified address. Be check
    /// isWriteBusy() before sending the next DMA transfer.
	/// @param address the address in the SPI RAM to write to
	/// @param numBytes size of the data block in bytes
	void zero(size_t address, size_t numBytes);

	/// write a single 16-bit word to the specified address
	/// @param address the address in the SPI RAM to write to
	/// @param data the value to write
	void write16(size_t address, uint16_t data);

	/// Write a block of 16-bit data to the specified address. Be check
	/// isWriteBusy() before sending the next DMA transfer.
	/// @param address the address in the SPI RAM to write to
	/// @param src pointer to the source data block
	/// @param numWords size of the data block in 16-bit words
	void write16(size_t address, uint16_t *src, size_t numWords);

	/// Write a block of 16-bit zeros to the specified address. Be check
    /// isWriteBusy() before sending the next DMA transfer.
	/// @param address the address in the SPI RAM to write to
	/// @param numWords size of the data block in 16-bit words
	void zero16(size_t address, size_t numWords);

	/// read a single 8-bit data word from the specified address
	/// @param address the address in the SPI RAM to read from
	/// @return the data that was read
	uint8_t read(size_t address);

	/// Read a block of 8-bit data from the specified address. Be check
    /// isReadBusy() before sending the next DMA transfer.
	/// @param address the address in the SPI RAM to write to
	/// @param dest pointer to the destination
	/// @param numBytes size of the data block in bytes
	void read(size_t address, uint8_t *dest, size_t numBytes);

	/// read a single 16-bit data word from the specified address
	/// @param address the address in the SPI RAM to read from
	/// @return the data that was read
	uint16_t read16(size_t address);

	/// read a block 16-bit data word from the specified address. Be check
    /// isReadBusy() before sending the next DMA transfer.
	/// @param address the address in the SPI RAM to read from
	/// @param dest the pointer to the destination
	/// @param numWords the number of 16-bit words to transfer
	void read16(size_t address, uint16_t *dest, size_t numWords);

	/// Check if a DMA write is in progress
	/// @returns true if a write DMA is in progress, else false
	bool isWriteBusy() const;

	/// Check if a DMA read is in progress
	/// @returns true if a read DMA is in progress, else false
	bool isReadBusy() const;

	/// Readout the 8-bit contents of the DMA storage buffer to the specified destination
	/// @param dest pointer to the destination
	/// @param numBytes number of bytes to read out
	/// @param byteOffset, offset from the start of the DMA buffer in bytes to begin reading
	void readBufferContents(uint8_t *dest,  size_t numBytes, size_t byteOffset = 0);

	/// Readout the 8-bit contents of the DMA storage buffer to the specified destination
	/// @param dest pointer to the destination
	/// @param numWords number of 16-bit words to read out
	/// @param wordOffset, offset from the start of the DMA buffer in words to begin reading
	void readBufferContents(uint16_t *dest, size_t numWords, size_t wordOffset = 0);

	/// Creates and allocates an intermediate copy buffer that is suitable for DMA transfers. It is up to the
	/// user to ensure they never request a read/write larger than the size of this buffer when using this
	/// feature.
	/// @details In some use cases you may want to DMA to/from memory buffers that are in memory regions that
	/// are not directly usable for DMA. Specifying a non-zero copy buffer size will create an intermediate
	/// DMA-compatible buffer. By default, the size is zero and an intermediate copy is not performed.
	/// DMA requires the user data be in a DMA accessible region and that it be aligned to the
	/// the size of a cache line, and that the cache line isn't shared with any other data that might
	/// be used on a different thread. Best practice is for a DMA buffer to start on a cache-line
	/// boundary and be exactly sized to an integer multiple of cache lines.
	/// @param numBytes the number of bytes to allocate for the intermediate copy buffer.
	/// @returns true on success, false on failure
	bool setDmaCopyBufferSize(size_t numBytes);

	/// get the current size of the DMA copy buffer. Zero size means no intermediate copy is performed.
	/// @returns the size of the intermediate copy buffer in bytes.
	size_t getDmaCopyBufferSize(void);

	/// Check if the class has been configured by a previous begin() call
	/// @returns true if initialized, false if not yet initialized
    bool isStarted() const;

	bool isStopped() const;

	void stop(bool waitForStop = false);
    void start(bool waitForStart = false);

private:
    bool m_useDma = true;
    class _impl; //forward declare
    std::unique_ptr<_impl> m_pimpl;
};

}