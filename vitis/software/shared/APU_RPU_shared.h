//APU_RPU_shared.h
#pragma once
// OCM Bank Addresses
// See UG1085 v2.4 table 18-1 OCM Mapping Summary (https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm)
#define MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU 	0xFFFD0000 // bank 1 is for r5->a53 user data
#define MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU 	0xFFFE0000 // bank 2 is for a53->r5 user data
#define MEM_SHARED_START_OCM_BANK_3_JAVASCOPE 	0xFFFF0000 // bank 3 is for r5->a53 javascope
#define JS_CHANNELS 		20
#define JAVASCOPE_DATA_SIZE sizeof(struct javascope_data_t)

// Experimental feature - read docs before use
#define USE_A53_AS_ACCELERATOR_FOR_R5_ISR		FALSE

struct javascope_data_t
{
	uint32_t    status;
	float	    slowDataContent;
	uint32_t    slowDataID;
	float       scope_ch[JS_CHANNELS];
};

// --- R5 -> A53 JavaScope sample ring buffer (shared OCM bank 3) -------------
// The first 128 bytes of bank 3 stay reserved for the version handshake
// (read_/write_apu/rpu_version below, at offsets 0 and 64); the ring follows.
#define JAVASCOPE_RING_META_BYTES   128U
#define MEM_SHARED_START_OCM_BANK_3_JAVASCOPE_RING \
        (MEM_SHARED_START_OCM_BANK_3_JAVASCOPE + JAVASCOPE_RING_META_BYTES)

#define JAVASCOPE_RING_SLOTS        512U                        // power of two
#define JAVASCOPE_RING_MASK         (JAVASCOPE_RING_SLOTS - 1U)

// Samples per APU interrupt: the R5 triggers an IPI every Nth frame (or
// immediately when the ring fills), decimating the A53 interrupt rate.
// 1 == notify every frame (previous behavior). Tune on hardware.
#define JAVASCOPE_RING_NOTIFY_DECIM 16U

// Header split so the R5-owned (write_idx/dropped) and A53-owned (read_idx)
// fields occupy separate 64-byte cache lines (avoids false sharing).
struct javascope_ring_t
{
	volatile uint32_t write_idx;     // R5 writes, A53 reads
	volatile uint32_t dropped;       // R5 writes (frames dropped when ring full)
	uint8_t  _pad0[64U - 2U * sizeof(uint32_t)];
	volatile uint32_t read_idx;      // A53 writes, R5 reads
	uint8_t  _pad1[64U - sizeof(uint32_t)];
	// NOTE: sizeof(javascope_data_t) == 92 B is NOT a multiple of the cache-line
	// size (R5 32 B / A53 64 B), so adjacent slots share cache lines.  This is
	// safe for this single-producer/single-consumer ring: the R5 writes slots
	// sequentially and flushes each by range, the A53 invalidates each slot by
	// range before reading, and producer and consumer never touch the same slot
	// concurrently.  Padding each slot to 64 B would push 512 slots past the
	// 64 KB of OCM bank 3, so the unaligned layout is intentional.
	struct javascope_data_t slots[JAVASCOPE_RING_SLOTS];
};

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert((JAVASCOPE_RING_NOTIFY_DECIM >= 1U) && (JAVASCOPE_RING_NOTIFY_DECIM < JAVASCOPE_RING_SLOTS),
               "JAVASCOPE_RING_NOTIFY_DECIM must be in [1, JAVASCOPE_RING_SLOTS).");
_Static_assert((JAVASCOPE_RING_META_BYTES + sizeof(struct javascope_ring_t)) <= (64U * 1024U),
               "JavaScope ring does not fit in OCM bank 3.");
#endif

struct APU_to_RPU_t
{
	uint32_t id;
	float value;
};

struct APU_to_RPU_user_data_t
{
	// create variables that you want to share from A53 to R5
	uint32_t slowDataCounter;
};

struct RPU_to_APU_user_data_t
{
	// create variables that you want to share from R5 to A53
	uint32_t slowDataCounter;
};


// Used for communicating the ultrazohm revision between RPU default define and what APU reads from EEPROM is present
#include "xil_cache.h"

static inline uint32_t read_rpu_version(void){
    uint32_t volatile *rpu_version = (uint32_t *)((uint8_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE + 64U);
    Xil_DCacheInvalidateRange((uintptr_t)rpu_version, sizeof(uint32_t));
    return *rpu_version;
}

static inline uint32_t read_apu_version(void){
    uint32_t volatile *apu_version = (uint32_t *)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
    Xil_DCacheInvalidateRange((uintptr_t)apu_version, sizeof(uint32_t));
    return *apu_version;
}

static inline void write_apu_version(uint32_t version){
    uint32_t volatile *apu_version = (uint32_t *)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
    *apu_version=version;
    Xil_DCacheFlushRange((uintptr_t)apu_version, sizeof(uint32_t));
}

static inline void write_rpu_version(uint32_t version){
    uint32_t volatile *rpu_version = (uint32_t *)((uint8_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE + 64U);
    *rpu_version=version;
    Xil_DCacheFlushRange((uintptr_t)rpu_version, sizeof(uint32_t));
}


