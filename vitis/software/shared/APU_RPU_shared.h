//APU_RPU_shared.h
#pragma once
#include <stdint.h>
// OCM Bank Addresses
// See UG1085 v2.4 table 18-1 OCM Mapping Summary (https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm)
#define MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU 	0xFFFD0000 // bank 1 is for r5->a53 user data
#define MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU 	0xFFFE0000 // bank 2 is for a53->r5 user data
#define MEM_SHARED_START_OCM_BANK_3_JAVASCOPE 	0xFFFF0000 // bank 3 is for r5->a53 javascope
#define JS_CHANNELS 		20
#define JAVASCOPE_DATA_SIZE sizeof(struct javascope_data_t)

// Experimental feature - read docs before use
#ifndef UZ_FSD_A53_BENCHMARK_ENABLE
#define UZ_FSD_A53_BENCHMARK_ENABLE 0U
#endif
#ifndef UZ_FSD_A53_BENCHMARK_VARIANT
#define UZ_FSD_A53_BENCHMARK_VARIANT 0U
#endif
#ifndef UZ_FSD_YANG_EXPERIMENT_ENABLE
#define UZ_FSD_YANG_EXPERIMENT_ENABLE 0U
#endif
#if UZ_FSD_A53_BENCHMARK_VARIANT > 8U
#error UZ_FSD_A53_BENCHMARK_VARIANT must be 0..8
#endif
#if UZ_FSD_A53_BENCHMARK_VARIANT >= 6U && !UZ_FSD_YANG_EXPERIMENT_ENABLE
#error Experimental Yang benchmark requires UZ_FSD_YANG_EXPERIMENT_ENABLE=1
#endif
#if UZ_FSD_A53_BENCHMARK_ENABLE
#define USE_A53_AS_ACCELERATOR_FOR_R5_ISR TRUE
#else
#define USE_A53_AS_ACCELERATOR_FOR_R5_ISR FALSE
#endif

#define UZ_FSD_A53_REQUEST_NONE 0U
#define UZ_FSD_A53_REQUEST_INIT 1U
#define UZ_FSD_A53_REQUEST_STEP 2U

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
#if UZ_FSD_A53_BENCHMARK_ENABLE
	uint32_t fsd_kind;
	uint32_t fsd_sequence;
	uint32_t fsd_status;
	uint32_t fsd_update_count;
	float fsd_duty[3];
	uint64_t fsd_compute_ticks;
	uint64_t fsd_timer_hz;
	uint32_t fsd_suitable_mask;
	uint32_t fsd_formulation_count;
	uint32_t fsd_qp_solve_count;
#endif
};

struct RPU_to_APU_user_data_t
{
	// create variables that you want to share from R5 to A53
	uint32_t slowDataCounter;
#if UZ_FSD_A53_BENCHMARK_ENABLE
	uint32_t fsd_kind;
	uint32_t fsd_sequence;
	uint32_t fsd_variant;
	float fsd_input[8];
#endif
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


