/******************************************************************************
 * xcp_meas_image_a53.c
 *
 * A53-side handler for the XCPlite Phase 3 shared MEAS image.
 *
 * Call sequence per R5 ISR cycle:
 *   1. R5 seqlock-writes its MEAS image to OCM bank 1 + flushes D-cache.
 *   2. R5 triggers IPI.
 *   3. A53 APU_IPI_ISR fires → calls xcp_meas_image_a53_on_ipi().
 *      - Invalidates D-cache for the MEAS image region.
 *      - Seqlock-validates and copies into xcp_meas_local_* buffers.
 *      - Gives xcp_meas_semaphore from ISR context.
 *   4. xcp_meas_event_task wakes, calls XcpEvent(xcp_meas_event_handle).
 *
 * Copyright 2024 Eyke Liegmann — Apache-2.0
 ******************************************************************************/

#include "xcp_meas_image_a53.h"
#include "APU_RPU_shared.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "xil_cache.h"

/* XCPlite public API — available once upstream sources are vendored. */
#include "xcplite.h"   /* XcpEvent() */

/*---------------------------------------------------------------------------
 * Module-private state
 *--------------------------------------------------------------------------*/
static SemaphoreHandle_t xcp_meas_semaphore = NULL;

/*---------------------------------------------------------------------------
 * A53-local measurement snapshot (written by ISR, read by event task).
 * Declared volatile so the compiler does not cache these across the
 * semaphore boundary.
 *--------------------------------------------------------------------------*/
volatile uint32_t xcp_meas_local_timestamp_us                   = 0u;
volatile float    xcp_meas_local_signal[XCP_MEAS_IMAGE_SIGNALS] = {0.0f};

/*---------------------------------------------------------------------------
 * XCPlite event handle — set by xcp_server_uz_start() before tasks run.
 *--------------------------------------------------------------------------*/
uint16_t xcp_meas_event_handle = 0u;

/*---------------------------------------------------------------------------
 * xcp_meas_image_a53_init
 *--------------------------------------------------------------------------*/
int xcp_meas_image_a53_init(void)
{
    xcp_meas_semaphore = xSemaphoreCreateBinary();
    if (xcp_meas_semaphore == NULL) {
        return -1;
    }
    return 0;
}

/*---------------------------------------------------------------------------
 * xcp_meas_image_a53_on_ipi
 *
 * Called from APU_IPI_ISR under LOGGING_PATH_XCP_LITE.
 * Must execute quickly — no blocking calls allowed.
 *--------------------------------------------------------------------------*/
void xcp_meas_image_a53_on_ipi(BaseType_t *pxHigherPriorityTaskWoken)
{
    /* Pointer to the MEAS image in OCM bank 1. */
    struct xcp_meas_image_t volatile * const img =
        (struct xcp_meas_image_t volatile *)XCP_MEAS_IMAGE_BASE;

    /* Invalidate A53 D-cache lines covering the MEAS image so we see
     * the data written by R5 (which flushed its cache before the IPI). */
    Xil_DCacheInvalidateRange(XCP_MEAS_IMAGE_BASE, XCP_MEAS_IMAGE_SIZE);

    /* Seqlock read — abort if R5 is mid-write (seq is odd). */
    uint32_t seq0 = img->seq;
    if (seq0 & 1u) {
        /* R5 write in progress — skip this sample rather than read torn data. */
        return;
    }

    /* Compiler / memory barrier: ensure all reads of signal[] happen after
     * reading seq0.  The portMEMORY_BARRIER patch in FreeRTOSConfig.h
     * defines this as an asm volatile ("" ::: "memory") fence. */
    portMEMORY_BARRIER();

    /* Copy the snapshot into the A53-local buffer. */
    xcp_meas_local_timestamp_us = img->timestamp_us;
    for (uint32_t i = 0u; i < XCP_MEAS_IMAGE_SIGNALS; i++) {
        xcp_meas_local_signal[i] = img->signal[i];
    }

    portMEMORY_BARRIER();

    /* Validate: if seq changed, R5 wrote concurrently — discard this sample. */
    if (img->seq != seq0) {
        return;
    }

    /* Valid snapshot — wake the event task. */
    if (xcp_meas_semaphore != NULL) {
        xSemaphoreGiveFromISR(xcp_meas_semaphore, pxHigherPriorityTaskWoken);
    }
}

/*---------------------------------------------------------------------------
 * xcp_meas_event_task
 *
 * Blocks forever on the binary semaphore.  One successful take = one DAQ
 * sample pushed into XCPlite's event queue.
 *--------------------------------------------------------------------------*/
void xcp_meas_event_task(void *pvParameters)
{
    (void)pvParameters;

    for (;;) {
        /* Block until the ISR posts a valid snapshot. */
        if (xSemaphoreTake(xcp_meas_semaphore, portMAX_DELAY) == pdTRUE) {
            /* Trigger XCPlite DAQ measurement for the MEAS event.
             * XCPlite reads the measurement variables registered via
             * DaqCreateEventVar() — for Phase 3 those point into
             * xcp_meas_local_timestamp_us and xcp_meas_local_signal[]. */
            XcpEvent(xcp_meas_event_handle);
        }
    }
}
