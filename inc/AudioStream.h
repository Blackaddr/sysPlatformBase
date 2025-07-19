/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SYSPLATFORM_AUDIOSTREAM_H_
#define SYSPLATFORM_AUDIOSTREAM_H_

#ifndef __ASSEMBLER__
#include <stdio.h>  // for NULL
#include <string.h> // for memcpy
#include <atomic>
#include "SysTypes.h"
#include "SysMutex.h"
#include "AudioSampleRate.h"
#include "SysCpuTelemetry.h"

#endif

#ifndef AUDIO_BLOCK_SAMPLES
#define AUDIO_BLOCK_SAMPLES  128
#endif

#ifndef AUDIO_SAMPLE_RATE_EXACT
#define AUDIO_SAMPLE_RATE_EXACT AUDIO_SAMPLE_RATE_HZ_F
#endif

#ifndef AUDIO_SAMPLES_PER_BLOCK_MIN
#define AUDIO_SAMPLES_PER_BLOCK_MIN 32  // min possible audio block size in samples
#endif

#ifndef AUDIO_SAMPLES_PER_BLOCK_MAX
#define AUDIO_SAMPLES_PER_BLOCK_MAX 256  // max possible audio block size in samples
#endif

#define AUDIO_SAMPLE_RATE AUDIO_SAMPLE_RATE_EXACT

#define noAUDIO_DEBUG_CLASS // disable this class by default

#ifndef __ASSEMBLER__
class AudioStream;
class AudioConnection;

extern const unsigned AUDIO_SAMPLES_PER_BLOCK;
extern const float    AUDIO_SAMPLE_RATE_HZ;
extern const float    AUDIO_SAMPLE_PERIOD_SEC;

constexpr size_t MAX_TRAVERSAL_BYTES=100;
extern std::atomic<bool> audioIsrInProgress;
extern volatile int8_t    audio_traversal_array[MAX_TRAVERSAL_BYTES];

// audio_block_struct stores control information, the actual
// data buffer is allocated separately
constexpr uint8_t NO_INPLACE_CONVERT_MASK = 0x80U;
constexpr uint8_t FLOAT_MASK              = 0x40U;
constexpr uint8_t DOUBLE_MASK             = 0x20U;

typedef struct audio_block_struct {
	uint8_t  ref_count;
	uint8_t  flags;
	uint16_t memory_pool_index;
	int16_t *data;
} audio_block_t;

struct audio_block_float32_t {
	uint8_t  ref_count;
	uint8_t  flags;
	uint16_t memory_pool_index;
	float *data;
};

class AudioConnection
{
public:
	AudioConnection(AudioStream &source, AudioStream &destination);
	AudioConnection(AudioStream &source, unsigned char sourceOutput,
		AudioStream &destination, unsigned char destinationInput);
	friend class AudioStream;
	~AudioConnection();
	int disconnect(void);
	int connect(void);
	int connect(AudioStream &source, AudioStream &destination) {return connect(source,0,destination,0);};
	int connect(AudioStream &source, unsigned char sourceOutput,
		AudioStream &destination, unsigned char destinationInput);
protected:
	AudioStream* src;	// can't use references as...
	AudioStream* dst;	// ...they can't be re-assigned!
	unsigned char src_index;
	unsigned char dest_index;
	AudioConnection *next_dest; // linked list of connections from one source
	bool isConnected;
};

// Create the array of num audio_block_t for control.
// Create a DMA 32-byte aligned contiguous block of memory of the required size.
// Call the initialize_memory() function to finish setting up the audio buffer pool
#define AudioMemory(num) ({ \
	static DMAMEM audio_block_float32_t data[num]; \
	DMAMEM __attribute__((aligned(32))) static float dataBuffers[AUDIO_BLOCK_SAMPLES*num]; \
	AudioStream::initialize_memory(data, num, dataBuffers); \
})

#define CYCLE_COUNTER_APPROX_PERCENT(n) (((float)((uint32_t)(n) * 6400u) * (float)(AUDIO_SAMPLE_RATE_EXACT / AUDIO_BLOCK_SAMPLES)) / (float)(SysPlatform::SysCpuTelemetry::getCpuFreqHz()))

#define AudioProcessorUsage() (CYCLE_COUNTER_APPROX_PERCENT(AudioStream::cpu_cycles_total))
#define AudioProcessorUsageMax() (CYCLE_COUNTER_APPROX_PERCENT(AudioStream::cpu_cycles_total_max))
#define AudioProcessorUsageMaxReset() (AudioStream::cpu_cycles_total_max = AudioStream::cpu_cycles_total)
#define AudioMemoryUsage() (AudioStream::memory_used)
#define AudioMemoryUsageMax() (AudioStream::memory_used_max)
#define AudioMemoryUsageMaxReset() (AudioStream::memory_used_max = AudioStream::memory_used)

class AudioStream
{
public:
	AudioStream(unsigned char ninput, audio_block_t **iqueue) :
	    AudioStream(ninput, (audio_block_float32_t**)iqueue) {}
	AudioStream(unsigned char ninput, audio_block_float32_t **iqueue) :
		num_inputs(ninput), inputQueue(iqueue) {
			active = false;
			destination_list = NULL;
			for (int i=0; i < num_inputs; i++) {
				inputQueue[i] = NULL;
			}
			// add to a simple list, for update_all
			// TODO: replace with a proper data flow analysis in update_all
			if (first_update == NULL) {
				first_update = this;
			} else {
				AudioStream *p;
				for (p=first_update; p->next_update; p = p->next_update) ;
				p->next_update = this;
			}
			next_update = NULL;
			cpu_cycles = 0;
			cpu_cycles_max = 0;
			numConnections = 0;
		}
	static void initialize_memory(audio_block_float32_t *data, unsigned int num, float *dataBuffers=nullptr);
	static void releaseAll();
	float processorUsage(void) { return CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles); }
	float processorUsageMax(void) { return CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles_max); }
	void processorUsageMaxReset(void) { cpu_cycles_max = cpu_cycles; }
	bool isActive(void) { return active; }
	uint16_t cpu_cycles;
	uint16_t cpu_cycles_max;
	static uint16_t cpu_cycles_total;
	static uint16_t cpu_cycles_total_max;
	static uint16_t memory_used;
	static uint16_t memory_used_max;
	static uint16_t num_buffers;

    void setId(int identifier) { id = identifier; }
	int  getId() { return id; }
	static void setOrderedUpdate(bool orderedUpdate);
	static constexpr int UPDATE_STEP_OBJECT_ID = 1024;
	static bool use_ordered_update;
	static void update_all(void);
	virtual void update(void) = 0;
protected:
	bool active;
	unsigned char num_inputs;
	static audio_block_t * allocate(void);
	static audio_block_float32_t * allocateFloat(void);
	static void release(audio_block_t* block);
	static void release(audio_block_t** block);
	static void release(audio_block_float32_t* block);
	static void release(audio_block_float32_t** block);
	void transmit(audio_block_t *block, unsigned char index = 0);
	void transmit(audio_block_float32_t *block, unsigned char index = 0);
	audio_block_t * receiveReadOnly(unsigned int index = 0);
	audio_block_float32_t * receiveReadOnlyFloat(unsigned int index = 0);
	audio_block_t * receiveWritable(unsigned int index = 0);
	audio_block_float32_t * receiveWritableFloat(unsigned int index = 0);
	static bool update_setup(void);
	static void update_stop(void);
	friend void software_isr(void);
	friend class AudioConnection;
	uint8_t numConnections;
private:
	static AudioConnection* unused; // linked list of unused but not destructed connections
	AudioConnection *destination_list;
	audio_block_float32_t** inputQueue;
	static bool update_scheduled;
	virtual void updateIndex(int index) {}
	static AudioStream *first_update; // for update_all
	AudioStream *next_update; // for update_all
	static audio_block_float32_t *memory_pool;
	static uint32_t memory_pool_available_mask[];
	static uint16_t memory_pool_first_mask;
	static AudioStream* step_update_object;
	static AudioStream** ordered_update_array;
	int id = -1;
};

#define TEENSY_AUDIO_BLOCK {0xBA, 0xAA, 0x20, 0x20, 0x51, 0xFF, 0x4A, 0xEC, 0x29, 0xCD, 0xBA, 0xAB, 0xF2, 0xFB, 0xE3, 0x46, 0x7C, 0xC2, 0x54, 0xF8, 0x1B, 0xE8, 0xE7, 0x8D, 0x76, 0x5A, 0x2E, 0x63, 0x33, 0x9F, 0xC9, 0x9A, 0x66, 0x32, 0x0D, 0xB7, 0x31, 0x58, 0xA3, 0x5A, 0x25, 0x5D, 0x05, 0x17, 0x58, 0xE9, 0x5E, 0xD4, 0xAB, 0xB2, 0xCD, 0xC6, 0x9B, 0xB4, 0x54, 0x11, 0x0E, 0x82, 0x74, 0x41, 0x21, 0x3D, 0xDC, 0x87, 0x70, 0xE9, 0x3E, 0xA1, 0x41, 0xE1, 0xFC, 0x67, 0x3E, 0x01, 0x7E, 0x97, 0xEA, 0xDC, 0x6B, 0x96, 0x8F, 0x38, 0x5C, 0x2A, 0xEC, 0xB0, 0x3B, 0xFB, 0x32, 0xAF, 0x3C, 0x54, 0xEC, 0x18, 0xDB, 0x5C, 0x02, 0x1A, 0xFE, 0x43, 0xFB, 0xFA, 0xAA, 0x3A, 0xFB, 0x29, 0xD1, 0xE6, 0x05, 0x3C, 0x7C, 0x94, 0x75, 0xD8, 0xBE, 0x61, 0x89, 0xF9, 0x5C, 0xBB, 0xA8, 0x99, 0x0F, 0x95, 0xB1, 0xEB, 0xF1, 0xB3, 0x05, 0xEF, 0xF7, 0x00, 0xE9, 0xA1, 0x3A, 0xE5, 0xCA, 0x0B, 0xCB, 0xD0, 0x48, 0x47, 0x64, 0xBD, 0x1F, 0x23, 0x1E, 0xA8, 0x1C, 0x7B, 0x64, 0xC5, 0x14, 0x73, 0x5A, 0xC5, 0x5E, 0x4B, 0x79, 0x63, 0x3B, 0x70, 0x64, 0x24, 0x11, 0x9E, 0x09, 0xDC, 0xAA, 0xD4, 0xAC, 0xF2, 0x1B, 0x10, 0xAF, 0x3B, 0x33, 0xCD, 0xE3, 0x50, 0x48, 0x47, 0x15, 0x5C, 0xBB, 0x6F, 0x22, 0x19, 0xBA, 0x9B, 0x7D, 0xF5, 0x0B, 0xE1, 0x1A, 0x1C, 0x7F, 0x23, 0xF8, 0x29, 0xF8, 0xA4, 0x1B, 0x13, 0xB5, 0xCA, 0x4E, 0xE8, 0x98, 0x32, 0x38, 0xE0, 0x79, 0x4D, 0x3D, 0x34, 0xBC, 0x5F, 0x4E, 0x77, 0xFA, 0xCB, 0x6C, 0x05, 0xAC, 0x86, 0x21, 0x2B, 0xAA, 0x1A, 0x55, 0xA2, 0xBE, 0x70, 0xB5, 0x73, 0x3B, 0x04, 0x5C, 0xD3, 0x36, 0x94, 0xB3, 0xAF, 0xE2, 0xF0, 0xE4, 0x9E, 0x4F, 0x32, 0x15, 0x49, 0xFD, 0x82, 0x4E, 0xA9}

#endif // __ASSEMBLER__
#endif // SYSPLATFORM_AUDIOSTREAM_H_
