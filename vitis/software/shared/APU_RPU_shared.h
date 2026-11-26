//APU_RPU_shared.h
#pragma once
// OCM map, shared by the R5 and the A53 (256 KB at 0xFFFC0000, four banks of 64 KB).
// See UG1085 v2.4 table 18-1 OCM Mapping Summary (https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm)
//   bank 0      0xFFFC0000  boot handshakes (below), the rest is free
//   bank 1      0xFFFD0000  r5->a53 user data (first half)
//               0xFFFD8000  a53->r5 user data (second half)
//   bank 2 + 3  0xFFFE0000  logging path, either
//                           JavaScope: one sample at 0xFFFF0000 (MEM_SHARED_START_OCM_BANK_3_JAVASCOPE)
//                           XCP: the R5 <-> A53 rings (ocm_xcp_ring.h)
// Every address that one core writes and the other reads starts its own
// 64-byte cache line (A53 line size; the R5 uses 32 bytes).
#define MEM_SHARED_START_OCM_HANDSHAKE 	        0xFFFC0000 // bank 0: boot handshakes
#define MEM_SHARED_START_OCM_RPU_TO_APU 	    0xFFFD0000 // bank 1, first half: r5->a53 user data
#define MEM_SHARED_START_OCM_APU_TO_RPU 	    0xFFFD8000 // bank 1, second half: a53->r5 user data
#define MEM_SHARED_START_OCM_BANK_3_JAVASCOPE 	0xFFFF0000 // JavaScope path: r5->a53 sample
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

// Boot handshakes in OCM bank 0, one cache line each. Both cores use them
// only during their initialisation (before the control ISR and the logging
// paths run); the A53 reads the logging-path word once when its network is up.
//   +0x00  A53 version word (A53 writes, R5 reads)
//   +0x40  R5 version word  (R5 writes, A53 reads)
//   +0x80  R5 logging path  (R5 writes, A53 reads)
#include "xil_cache.h"
#include "uz_logging_path.h"

#define UZ_HANDSHAKE_APU_VERSION_ADDR (MEM_SHARED_START_OCM_HANDSHAKE + 0x00U)
#define UZ_HANDSHAKE_RPU_VERSION_ADDR (MEM_SHARED_START_OCM_HANDSHAKE + 0x40U)

// Logging path handshake: the R5 publishes the UZ_LOGGING_PATH it was built with
// (magic in the upper 24 bits) at boot, the A53 compares it with its own build
// before it starts the logging server and warns on the serial console when the
// two applications disagree (one of them was not rebuilt or not flashed).
#define UZ_LOGGING_PATH_WORD_ADDR  (MEM_SHARED_START_OCM_HANDSHAKE + 0x80U)
#define UZ_LOGGING_PATH_WORD_MAGIC (0x555A4C00U) /* "UZL" + path in the low byte */

static inline void write_rpu_logging_path(void){
    uint32_t volatile *word = (uint32_t *)(uintptr_t)UZ_LOGGING_PATH_WORD_ADDR;
    *word = UZ_LOGGING_PATH_WORD_MAGIC | (uint32_t)UZ_LOGGING_PATH;
    Xil_DCacheFlushRange((uintptr_t)word, sizeof(uint32_t));
}

static inline uint32_t read_rpu_logging_path(void){
    uint32_t volatile *word = (uint32_t *)(uintptr_t)UZ_LOGGING_PATH_WORD_ADDR;
    Xil_DCacheInvalidateRange((uintptr_t)word, sizeof(uint32_t));
    return *word;
}

static inline uint32_t read_rpu_version(void){
    uint32_t volatile *rpu_version = (uint32_t *)(uintptr_t)UZ_HANDSHAKE_RPU_VERSION_ADDR;
    Xil_DCacheInvalidateRange((uintptr_t)rpu_version, sizeof(uint32_t));
    return *rpu_version;
}

static inline uint32_t read_apu_version(void){
    uint32_t volatile *apu_version = (uint32_t *)(uintptr_t)UZ_HANDSHAKE_APU_VERSION_ADDR;
    Xil_DCacheInvalidateRange((uintptr_t)apu_version, sizeof(uint32_t));
    return *apu_version;
}

static inline void write_apu_version(uint32_t version){
    uint32_t volatile *apu_version = (uint32_t *)(uintptr_t)UZ_HANDSHAKE_APU_VERSION_ADDR;
    *apu_version=version;
    Xil_DCacheFlushRange((uintptr_t)apu_version, sizeof(uint32_t));
}

static inline void write_rpu_version(uint32_t version){
    uint32_t volatile *rpu_version = (uint32_t *)(uintptr_t)UZ_HANDSHAKE_RPU_VERSION_ADDR;
    *rpu_version=version;
    Xil_DCacheFlushRange((uintptr_t)rpu_version, sizeof(uint32_t));
}


