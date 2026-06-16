/******************************************************************************
 * xcp_cal_image_a53.c
 *
 * XCPlite Phase 4 -- CAL image double-buffer (A53 side).
 *
 * The A53 maintains two calibration pages in OCM bank 2.  CANape writes
 * parameters via XCP DOWNLOAD commands; the ApplXcpWriteMemory hook in
 * xcp_server_uz.c redirects those writes here.  On commit (end of a DOWNLOAD
 * burst), the inactive page is flipped to active atomically.  The R5 reads
 * the active page at a safe point in its control cycle.
 *
 * Double-buffer write protocol (A53, called from ApplXcpWriteMemory):
 *   1. Determine inactive_page = 1 - image->active_page
 *   2. Copy bytes into page[inactive_page].param[] at the given offset
 *   3. On commit: set page[inactive_page].magic = XCP_CAL_PAGE_MAGIC
 *   4. DSB before page flip
 *   5. image->active_page = inactive_page  (atomic flip)
 *   6. DSB after page flip
 *   7. Xil_DCacheFlushRange over entire image
 *
 * The R5 adopt-point (Baremetal/src/sw/isr.c or a new xcp_cal_r5.c):
 *   1. Xil_DCacheInvalidateRange(XCP_CAL_IMAGE_BASE, XCP_CAL_IMAGE_SIZE)
 *   2. pg = image->active_page  (validate: must be 0 or 1)
 *   3. if page[pg].magic != XCP_CAL_PAGE_MAGIC -> skip
 *   4. Copy param[] to R5-local shadow; apply to control loop
 *
 * PREREQUISITES:
 *   - Phase 3 working (IPI + MEAS path verified).
 *   - XCP_CAL_IMAGE_ENABLE 1 in both defines.h files.
 *   - OPTION_CAL_SEGMENTS defined in xcplib_uz_cfg.h (already set).
 *   - Safety review completed (see xcp_cal_image_a53.h).
 *
 * Copyright 2024 Eyke Liegmann -- Apache-2.0
 ******************************************************************************/

#include "xcp_cal_image_a53.h"
#include "APU_RPU_shared.h"

#include "xil_cache.h"
#include "xil_assert.h"

#include <string.h>    /* memset, memcpy */
#include <stddef.h>    /* offsetof, size_t */
#include <stdint.h>
#include <stdbool.h>   /* bool, used in ApplXcpWriteMemory */

/*---------------------------------------------------------------------------
 * Internal helpers
 *--------------------------------------------------------------------------*/

/** Return a typed pointer to the CAL image in OCM bank 2.
 *
 * The address is routed through a volatile uintptr_t so the optimiser cannot
 * assume the literal XCP_CAL_IMAGE_BASE points to a zero-sized object: under
 * -O3 that triggers a -Warray-bounds on the full-image memset and could let
 * GCC elide the writes to this fixed OCM region. */
static inline struct xcp_cal_image_t volatile *cal_image(void)
{
    static uintptr_t volatile base = (uintptr_t)XCP_CAL_IMAGE_BASE;
    return (struct xcp_cal_image_t volatile *)base;
}

/** Return the index of the page that is NOT currently active. */
static inline uint32_t inactive_page(void)
{
    uint32_t ap = cal_image()->active_page;
    /* Guard against corruption: if active_page is neither 0 nor 1, default
     * to page 1 as inactive so we overwrite the unknown/bad state. */
    return (ap == 0u) ? 1u : 0u;
}

/*---------------------------------------------------------------------------
 * xcp_cal_image_a53_init
 *--------------------------------------------------------------------------*/
int xcp_cal_image_a53_init(void)
{
    struct xcp_cal_image_t volatile * const img = cal_image();

    /* Zero both pages to start from a clean state. */
    memset((void *)img, 0, sizeof(struct xcp_cal_image_t));

    /* Mark page 0 as valid with ROM defaults (all-zero params).
     * R5 will adopt page 0 on first invalidate. */
    img->page[0].magic = XCP_CAL_PAGE_MAGIC;
    img->active_page   = 0u;

    /* Flush so R5 sees initialised state before the first IPI. */
    __asm volatile ("dsb sy" ::: "memory");
    Xil_DCacheFlushRange(XCP_CAL_IMAGE_BASE, XCP_CAL_IMAGE_SIZE);

    return 0;
}

/*---------------------------------------------------------------------------
 * xcp_cal_image_a53_write
 *
 * Writes `len` bytes from `src` into the inactive page at byte offset
 * `offset_in_param` within page[].param[].
 *
 * Called from ApplXcpWriteMemory for each DOWNLOAD_NEXT chunk.
 * Do NOT flip the page here; call xcp_cal_image_a53_flip() after the
 * final chunk.
 *--------------------------------------------------------------------------*/
int xcp_cal_image_a53_write(size_t offset_in_param, const void *src,
                            size_t len)
{
    const size_t param_bytes = sizeof(cal_image()->page[0].param);

    if (src == NULL || (offset_in_param + len) > param_bytes) {
        return -1;
    }

    uint32_t ip = inactive_page();
    uint8_t *dst = (uint8_t *)(&cal_image()->page[ip].param[0]) + offset_in_param;
    memcpy(dst, src, len);

    return 0;
}

/*---------------------------------------------------------------------------
 * xcp_cal_image_a53_flip
 *
 * Stamps the inactive page as valid and atomically flips active_page.
 * Called from ApplXcpWriteMemory after the final DOWNLOAD chunk.
 *--------------------------------------------------------------------------*/
void xcp_cal_image_a53_flip(void)
{
    struct xcp_cal_image_t volatile * const img = cal_image();
    uint32_t ip = inactive_page();

    /* Mark the inactive page as fully written. */
    img->page[ip].magic = XCP_CAL_PAGE_MAGIC;

    /* Ensure all param writes and the magic stamp complete before the
     * page flip becomes visible to the R5. */
    __asm volatile ("dsb sy" ::: "memory");

    /* Atomic page flip: R5 observes the new active_page after its next
     * Xil_DCacheInvalidateRange call. */
    img->active_page = ip;

    /* Ensure active_page is written to cache before flush. */
    __asm volatile ("dsb sy" ::: "memory");

    /* Push the entire CAL image to main memory so R5 sees a coherent view
     * after its DCacheInvalidateRange. */
    Xil_DCacheFlushRange(XCP_CAL_IMAGE_BASE, XCP_CAL_IMAGE_SIZE);
}

/*---------------------------------------------------------------------------
 * ApplXcpWriteMemory  (XCPlite callback override)
 *
 * XCPlite calls this for every XCP DOWNLOAD / DOWNLOAD_NEXT command.
 * Signature from xcplite.h:
 *   uint8_t ApplXcpWriteMemory(uint32_t dst, uint8_t size,
 *                              const uint8_t *src);
 *
 * Strategy (Option A -- intercept by address range):
 *   - If dst falls in the CAL param range, redirect to the inactive page.
 *   - Otherwise fall through to direct memcpy (Phase 1/3 demo vars, etc.).
 *
 * Enable by defining XCP_CAL_IMAGE_ENABLE 1 in both defines.h files AND
 * enabling OPTION_CAL_SEGMENTS in xcplib_uz_cfg.h.
 *
 * NOTE: xcpappl.c provides a default ApplXcpWriteMemory that calls a
 * registered callback.  We override it here by providing our own definition;
 * xcpappl.c's version is compiled but unreachable when the linker prefers
 * the first strong definition (this file is listed earlier in the build).
 * Alternatively, call ApplXcpRegisterWriteCallback() from
 * xcp_server_uz_start() to install a function pointer instead.
 *--------------------------------------------------------------------------*/
#if XCP_CAL_IMAGE_ENABLE

/* Base address of the calibration parameter region exposed to XCPlite.
 * CANape writes to XCP addresses in [XCP_CAL_PARAM_BASE,
 * XCP_CAL_PARAM_BASE + XCP_CAL_PARAM_BYTES). */
#define XCP_CAL_PARAM_BASE  ((uint32_t)XCP_CAL_IMAGE_BASE \
                             + offsetof(struct xcp_cal_image_t, page[0].param))
#define XCP_CAL_PARAM_BYTES ((uint32_t)sizeof(cal_image()->page[0].param))

/* Track whether we are inside a multi-packet DOWNLOAD burst.
 * A burst starts on the first DOWNLOAD_NEXT and ends on DOWNLOAD (or any
 * call where dst is outside the CAL range). */
static bool s_cal_burst_active = false;

uint8_t ApplXcpWriteMemory(uint32_t dst, uint8_t size, const uint8_t *src)
{
    /* Check if the write targets the CAL parameter region. */
    if (dst >= XCP_CAL_PARAM_BASE &&
        (dst + size) <= (XCP_CAL_PARAM_BASE + XCP_CAL_PARAM_BYTES))
    {
        size_t offset = (size_t)(dst - XCP_CAL_PARAM_BASE);
        if (xcp_cal_image_a53_write(offset, src, (size_t)size) != 0) {
            return 1u; /* CRC_OUT_OF_RANGE */
        }
        s_cal_burst_active = true;
        /* Flip after every DOWNLOAD packet.  For multi-packet bursts
         * (DOWNLOAD_NEXT) the last packet calls this too, so this is always
         * safe.  The R5 simply adopts the last fully-written state. */
        xcp_cal_image_a53_flip();
        s_cal_burst_active = false;
        return 0u; /* CRC_CMD_OK */
    }

    /* Outside CAL range: direct write (demo vars, event tables, etc.). */
    if (s_cal_burst_active) {
        /* Burst ended without hitting CAL range -- commit whatever was staged. */
        xcp_cal_image_a53_flip();
        s_cal_burst_active = false;
    }
    memcpy((void *)(uintptr_t)dst, src, (size_t)size);
    return 0u;
}

#endif /* XCP_CAL_IMAGE_ENABLE */
