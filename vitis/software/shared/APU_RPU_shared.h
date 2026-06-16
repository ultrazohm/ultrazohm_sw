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

/*===========================================================================
 * XCPlite Phase 3 — MEAS image (R5 → A53, OCM bank 1)
 *
 * Placed at offset 0x100 into bank 1 to leave the first 256 bytes for the
 * existing RPU_to_APU_user_data_t and future handshake fields.
 *
 * Coherency protocol (seqlock, write side = R5 ISR):
 *   1. seq++ (now odd — signals write in progress; DSB before data writes)
 *   2. Write all signal fields
 *   3. seq++ (now even — signals write complete; DSB after data writes)
 *   4. Xil_DCacheFlushRange(XCP_MEAS_IMAGE_BASE, XCP_MEAS_IMAGE_SIZE)
 *   5. XIpiPsu_TriggerIpi()  ← existing IPI; A53 handles immediately
 *
 * Read side (A53 IPI ISR, after Xil_DCacheInvalidateRange):
 *   1. uint32_t s = image->seq;
 *   2. if (s & 1u) → write in progress, skip this sample
 *   3. Read signal fields into A53-local buffer
 *   4. if (image->seq != s) → torn read, discard
 *   5. Else → valid; post to xcp_meas_event_task via semaphore
 *
 * Since R5 polls for IPI ACK before issuing the next IPI, torn reads are
 * extremely rare in practice; the seqlock is defensive insurance.
 *
 * Phase 3 bring-up steps:
 *   - Replace the placeholder signal[] array below with actual R5 control
 *     signals (currents, voltages, speed, angle, …)
 *   - Add the corresponding MEASUREMENT blocks to the A2L (or regenerate)
 *   - On R5: call xcp_meas_r5_update() in ISR_Control before JavaScope_update
 *=========================================================================*/

#define XCP_MEAS_IMAGE_BASE   (MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU + 0x100U)
#define XCP_MEAS_IMAGE_SIGNALS  8U   /* number of float measurement channels */

struct xcp_meas_image_t
{
	volatile uint32_t seq;                           /* seqlock counter (odd=writing) */
	volatile uint32_t timestamp_us;                  /* R5 ISR timestamp in µs        */
	volatile float    signal[XCP_MEAS_IMAGE_SIGNALS];/* replace with real signal names */
};

#define XCP_MEAS_IMAGE_SIZE   sizeof(struct xcp_meas_image_t)

/*===========================================================================
 * XCPlite Phase 4 — CAL image (A53 → R5, OCM bank 2)
 *
 * Double-buffered: A53 calibration handler (ApplXcpWriteMemory hook) writes
 * to the inactive page, then atomically flips the active-page index.
 * R5 reads the active page at a deterministic safe point in its control cycle.
 *
 * Safety note: review required before enabling in motor-control context.
 * Set XCP_CAL_IMAGE_ENABLE in both defines.h (A53) and Baremetal defines.h
 * (R5) only after the R5 adopt-point and rollback policy have been reviewed.
 *
 * See xcp_cal_image_a53.h for the full design and the ApplXcpWriteMemory
 * hook prototype.
 *=========================================================================*/

#define XCP_CAL_IMAGE_BASE    (MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU + 0x100U)

struct xcp_cal_page_t
{
	uint32_t magic;     /* sanity sentinel: 0xCA1CA1CA when page is valid  */
	float    param[16]; /* calibration parameters; expand as needed         */
};

struct xcp_cal_image_t
{
	volatile uint32_t       active_page; /* 0 or 1; R5 reads page[active_page] */
	struct xcp_cal_page_t   page[2];
};

#define XCP_CAL_IMAGE_SIZE    sizeof(struct xcp_cal_image_t)
#define XCP_CAL_PAGE_MAGIC    (0xCA1CA1CAU)


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


