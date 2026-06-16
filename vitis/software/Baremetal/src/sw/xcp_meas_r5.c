/******************************************************************************
 * xcp_meas_r5.c
 *
 * R5-side writer for the XCPlite Phase 3 MEAS image.
 *
 * Seqlock write protocol (must match the read protocol in
 * xcp_meas_image_a53_on_ipi()):
 *
 *   1. seq++ → odd  (signals write in progress)
 *   2. DSB   (ensures seq is visible before data writes begin)
 *   3. Write image fields
 *   4. DSB   (ensures data writes complete before seq becomes even)
 *   5. seq++ → even (signals write complete)
 *   6. Xil_DCacheFlushRange → A53 sees coherent data on cache-invalidate
 *
 * The IPI trigger that follows in JavaScope_update() / ipc_ARM.c then
 * causes the A53 APU_IPI_ISR to invalidate its cache and read the image.
 *
 * Copyright 2024 Eyke Liegmann — Apache-2.0
 ******************************************************************************/

#include "xcp_meas_r5.h"
#include "APU_RPU_shared.h"

#include "xil_cache.h"
#include "xil_assert.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"

/*---------------------------------------------------------------------------
 * Signal mapping — Phase 3 placeholder.
 *
 * TODO: Replace the generic ADC/encoder fields below with the actual
 * control signals measured in ISR_Control once Phase 3 is activated
 * (XCP_MEAS_IMAGE_ENABLE 1).  Update the corresponding
 * DaqCreateEventVar() calls in xcp_server_uz.c to use descriptive names
 * that match the A2L.  The number of entries must not exceed
 * XCP_MEAS_IMAGE_SIGNALS (currently 8).
 *--------------------------------------------------------------------------*/
static void xcp_meas_fill_signals(struct xcp_meas_image_t volatile *img,
                                  const DS_Data *data)
{
    /* Phase 3 placeholder — maps the first 8 ADC channels from card 1.
     * Replace with meaningful control-loop signals before production use. */
    img->signal[0] = data->av.I_L1;
    img->signal[1] = data->av.I_L2;
    img->signal[2] = data->av.I_L3;
    img->signal[3] = data->av.U_ZK;
    img->signal[4] = data->av.mechanicalRotorSpeed;
    img->signal[5] = data->av.I_d;
    img->signal[6] = data->av.I_q;
    img->signal[7] = data->av.U_d;
}

/*---------------------------------------------------------------------------
 * xcp_meas_r5_update
 *--------------------------------------------------------------------------*/
void xcp_meas_r5_update(const DS_Data *data)
{
    Xil_AssertVoid(data != NULL);

    struct xcp_meas_image_t volatile * const img =
        (struct xcp_meas_image_t volatile *)XCP_MEAS_IMAGE_BASE;

    /* --- seqlock write begin ------------------------------------------- */
    img->seq++;                     /* → odd: signals write in progress */
    __asm volatile ("dsb" ::: "memory"); /* data barrier: seq visible before data */

    img->timestamp_us = (uint32_t)uz_SystemTime_GetUptimeInUs();
    xcp_meas_fill_signals(img, data);

    __asm volatile ("dsb" ::: "memory"); /* data barrier: data visible before seq */
    img->seq++;                     /* → even: signals write complete */
    /* --- seqlock write end --------------------------------------------- */

    /* Flush so the A53 sees the update after its Xil_DCacheInvalidateRange. */
    Xil_DCacheFlushRange(XCP_MEAS_IMAGE_BASE, XCP_MEAS_IMAGE_SIZE);
}
