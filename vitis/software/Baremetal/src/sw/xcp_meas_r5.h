/******************************************************************************
 * xcp_meas_r5.h
 *
 * R5-side writer for the XCPlite Phase 3 MEAS image.
 *
 * Call xcp_meas_r5_update() once per ISR_Control cycle (before
 * JavaScope_update) to seqlock-write the current measurement snapshot into
 * OCM bank 1 so the A53 can read it via XCPlite DAQ.
 *
 * Enable by setting XCP_MEAS_IMAGE_ENABLE 1 in
 * vitis/software/Baremetal/src/defines.h.
 *
 * Copyright 2024 Eyke Liegmann — Apache-2.0
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../globalData.h"

/*---------------------------------------------------------------------------
 * xcp_meas_r5_update
 *
 * Write the current DS_Data measurement snapshot into the MEAS image in
 * OCM bank 1 using a seqlock.  Flushes the D-cache after writing so the
 * A53 sees a coherent image when the IPI arrives.
 *
 * Must be called from ISR_Control before JavaScope_update() and before
 * XIpiPsu_TriggerIpi() so the write is complete before the A53 wakes.
 *
 * @param data  Pointer to the global DS_Data struct (must not be NULL).
 *--------------------------------------------------------------------------*/
void xcp_meas_r5_update(const DS_Data *data);

#ifdef __cplusplus
}
#endif
