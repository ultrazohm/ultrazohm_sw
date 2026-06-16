/******************************************************************************
 * xcp_meas_image_a53.h
 *
 * A53-side handler for the XCPlite Phase 3 shared MEAS image.
 *
 * The IPI ISR calls xcp_meas_image_a53_on_ipi() once per control cycle
 * to copy the R5-written MEAS image into an A53-local buffer under seqlock
 * validation, then signals xcp_meas_event_task via a binary semaphore.
 * The task calls XcpEvent() to push the snapshot into the XCPlite DAQ queue.
 *
 * Enable by setting LOGGING_PATH_XCP_LITE 1 in
 * vitis/software/FreeRTOS/defines.h.
 *
 * Copyright 2024 Eyke Liegmann — Apache-2.0
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include <stdint.h>

/*---------------------------------------------------------------------------
 * A53-local copy of the MEAS image, populated once per IPI.
 * Only the xcp_meas_event_task reads this after taking the semaphore;
 * only xcp_meas_image_a53_on_ipi() (called from the IPI ISR) writes it.
 * No additional locking is needed because the IPI protocol is synchronous
 * (R5 blocks on ACK before issuing the next IPI, so there is at most one
 * write in flight at any time).
 *--------------------------------------------------------------------------*/
extern volatile uint32_t xcp_meas_local_timestamp_us;
extern volatile float    xcp_meas_local_signal[8]; /* mirrors XCP_MEAS_IMAGE_SIGNALS */

/*---------------------------------------------------------------------------
 * xcp_meas_image_a53_init
 *
 * Create the binary semaphore used between the IPI ISR and the event task.
 * Call once from xcp_server_uz_start(), before XcpEthServerInit().
 * Returns 0 on success, non-zero on failure.
 *--------------------------------------------------------------------------*/
int xcp_meas_image_a53_init(void);

/*---------------------------------------------------------------------------
 * xcp_meas_image_a53_on_ipi
 *
 * Called from APU_IPI_ISR (FreeRTOS/sw/isr.c) under LOGGING_PATH_XCP_LITE.
 * Invalidates the MEAS image cache line, reads the image under seqlock
 * validation, copies valid data to the A53-local buffer, and gives the
 * semaphore to wake xcp_meas_event_task.
 *
 * pxHigherPriorityTaskWoken — pass the caller's existing variable; set to
 * pdTRUE if the event task was woken and should be scheduled.
 *--------------------------------------------------------------------------*/
void xcp_meas_image_a53_on_ipi(BaseType_t *pxHigherPriorityTaskWoken);

/*---------------------------------------------------------------------------
 * xcp_meas_event_task
 *
 * FreeRTOS task entry point.  Blocks on the binary semaphore, then calls
 * XcpEvent(xcp_meas_event_handle) to push the local buffer snapshot into
 * the XCPlite DAQ queue.
 *
 * xcp_meas_event_handle must be set by the caller (xcp_server_uz_start)
 * before this task runs.  Stack and priority are defined in xcplib_uz_cfg.h.
 *--------------------------------------------------------------------------*/
void xcp_meas_event_task(void *pvParameters);

/* Handle set by xcp_server_uz_start before the task is created. */
extern uint16_t xcp_meas_event_handle;

#ifdef __cplusplus
}
#endif
