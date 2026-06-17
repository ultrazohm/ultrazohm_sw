/******************************************************************************
 * xcp_cal_image_a53.h
 *
 * XCPlite Phase 4 — CAL image design scaffold (A53 side).
 *
 * This file documents the double-buffer calibration protocol between the
 * CANape XCP master, the A53 (XCPlite slave), and the R5 (parameter consumer).
 * It is intentionally header-only for Phase 4 bring-up.  The implementation
 * lives in xcp_cal_image_a53.c (to be created) and the R5 adopt-point in
 * Baremetal/src/sw/xcp_meas_r5.c (or a new xcp_cal_r5.c).
 *
 * PREREQUISITE: Phase 3 must be working before enabling Phase 4.
 * Enable by setting both XCP_CAL_IMAGE_ENABLE in both defines.h files.
 *
 * Copyright 2024 Eyke Liegmann — Apache-2.0
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "APU_RPU_shared.h"

/*===========================================================================
 * Double-buffer CAL protocol
 *
 * OCM bank 2 (A53→R5, XCP_CAL_IMAGE_BASE) layout:
 *
 *   struct xcp_cal_image_t {
 *       volatile uint32_t      active_page;  // 0 or 1; R5 reads page[active_page]
 *       struct xcp_cal_page_t  page[2];      // double buffer
 *   };
 *
 *   struct xcp_cal_page_t {
 *       uint32_t magic;     // 0xCA1CA1CA when page is valid and fully written
 *       float    param[16]; // calibration parameters
 *   };
 *
 * Write sequence (A53, triggered by ApplXcpWriteMemory XCPlite hook):
 *
 *   1. Determine inactive_page = 1 - image->active_page
 *   2. Write param[] into page[inactive_page] (no DSB needed yet)
 *   3. page[inactive_page].magic = XCP_CAL_PAGE_MAGIC  (marks page valid)
 *   4. __asm volatile ("dsb" ::: "memory")              (fence before flip)
 *   5. image->active_page = inactive_page               (atomic flip)
 *   6. __asm volatile ("dsb" ::: "memory")              (fence after flip)
 *   7. Xil_DCacheFlushRange(XCP_CAL_IMAGE_BASE, XCP_CAL_IMAGE_SIZE)
 *
 * Read sequence (R5, at a deterministic "safe point" in its control cycle):
 *
 *   1. Xil_DCacheInvalidateRange(XCP_CAL_IMAGE_BASE, XCP_CAL_IMAGE_SIZE)
 *   2. uint32_t pg = image->active_page   (must be 0 or 1; validate)
 *   3. if (image->page[pg].magic != XCP_CAL_PAGE_MAGIC) → skip this cycle
 *   4. Copy param[] into R5-local shadow struct
 *   5. Apply shadow struct to running control parameters
 *
 * Safety notes for motor-control context:
 *   - The R5 must NEVER apply calibration mid-vector-computation.  The safe
 *     point is after PWM latch and before the next ADC read — i.e., the very
 *     start of ISR_Control, after uz_SystemTime_ISR_Tic().
 *   - Rate-limit CANape write bursts in the A2L (set MAX_BLOCK_SIZE to a
 *     value that fits inside one IPI interval) so the A53 does not flip the
 *     page mid-burst.
 *   - Consider a rollback policy: if magic is invalid for N consecutive
 *     cycles, revert to ROM defaults.  Implement in the R5 adopt-point.
 *   - Review required before enabling in a high-voltage motor test bench.
 *     Get sign-off from the safety-responsible engineer.
 *
 *=========================================================================*/

/*---------------------------------------------------------------------------
 * ApplXcpWriteMemory — XCPlite hook prototype
 *
 * XCPlite calls this function whenever the XCP master (CANape) sends a
 * DOWNLOAD or DOWNLOAD_NEXT command targeting the calibration address range.
 *
 * The default XCPlite implementation does a direct memcpy into the target
 * address.  For Phase 4 we override it to redirect writes into the inactive
 * CAL page and then flip the page atomically.
 *
 * Implementation strategy (two options):
 *
 *   Option A — Intercept by address range:
 *     If addr falls within [XCP_CAL_IMAGE_BASE, XCP_CAL_IMAGE_BASE +
 *     XCP_CAL_IMAGE_SIZE), redirect the write to the inactive page at the
 *     same offset within param[].  For addresses outside this range, fall
 *     through to the default memcpy.
 *
 *   Option B — Dedicated CAL segment:
 *     Define a separate XCP segment/page via XcpCreateCalPage() so CANape
 *     only sends writes to the calibration segment.  This is cleaner but
 *     requires A2L MEMORY_SEGMENT setup.
 *
 * Start with Option A during bring-up; migrate to Option B for production.
 *
 * Signature (from xcplite.h, verify against vendored version):
 *
 *   uint8_t ApplXcpWriteMemory(void *dst, const void *src, uint16_t len);
 *   Returns 0 on success, non-zero to signal a write error to the master.
 *--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * xcp_cal_image_a53_init
 *
 * Initialize the CAL image in OCM bank 2:
 *   - Zero both pages.
 *   - Set active_page = 0.
 *   - Write XCP_CAL_PAGE_MAGIC to page[0] (marks ROM defaults as loaded).
 *   - Flush D-cache.
 *
 * Call once from xcp_server_uz_start(), after xcp_meas_image_a53_init().
 * Returns 0 on success.
 *--------------------------------------------------------------------------*/
int xcp_cal_image_a53_init(void);

/*---------------------------------------------------------------------------
 * xcp_cal_image_a53_write
 *
 * Write `len` bytes from `src` into the inactive CAL page at byte offset
 * `offset_in_param` (relative to page[].param[0]).  After writing all bytes
 * for a calibration transaction, call xcp_cal_image_a53_flip() to commit.
 *
 * CANape issues writes as a burst of DOWNLOAD_NEXT packets followed by a
 * final DOWNLOAD.  Buffer all writes in the inactive page; flip only on the
 * final DOWNLOAD (when XCPlite calls ApplXcpWriteMemory for the last chunk).
 *
 * @param offset_in_param  byte offset into page[].param[]
 * @param src              source buffer (from XCP packet payload)
 * @param len              number of bytes to write (≤ sizeof(page[].param))
 * Returns 0 on success, -1 if offset+len would overflow param[].
 *--------------------------------------------------------------------------*/
int xcp_cal_image_a53_write(size_t offset_in_param, const void *src,
                            size_t len);

/*---------------------------------------------------------------------------
 * xcp_cal_image_a53_flip
 *
 * Atomically flip active_page to make the just-written inactive page live.
 * Flushes D-cache after the flip.
 *
 * Call from ApplXcpWriteMemory after the final write in a DOWNLOAD burst.
 *--------------------------------------------------------------------------*/
void xcp_cal_image_a53_flip(void);

/*---------------------------------------------------------------------------
 * Phase 4 bring-up checklist
 *
 *  [ ] Set XCP_CAL_IMAGE_ENABLE 1 in FreeRTOS/defines.h
 *  [ ] Set XCP_CAL_IMAGE_ENABLE 1 in Baremetal/src/defines.h
 *  [ ] Implement xcp_cal_image_a53.c with _init, _write, _flip
 *  [ ] Override ApplXcpWriteMemory in xcp_server_uz.c (Option A or B above)
 *  [ ] Enable XCPLIB_ENABLE_CAL 1 in xcplib_uz_cfg.h
 *  [ ] Add R5 adopt-point: read active_page and copy param[] to local shadow
 *      in ISR_Control, at the safe point after uz_SystemTime_ISR_Tic()
 *  [ ] Validate rollback policy (what happens if magic is invalid?)
 *  [ ] Regenerate A2L with calibration CHARACTERISTIC blocks
 *  [ ] Safety review before enabling on motor test bench
 *--------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
