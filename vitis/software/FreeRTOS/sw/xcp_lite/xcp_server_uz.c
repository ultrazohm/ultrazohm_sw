/******************************************************************************
 * xcp_server_uz.c
 *
 * UltraZohm (A53 / FreeRTOS / lwIP) XCPlite integration layer.
 *
 * Provides:
 *   - ApplXcpGetClock64()  — 64-bit 1 us clock via Xilinx global timer
 *   - xcp_server_uz_start() — init + Phase 1 demo DAQ task
 *
 * Phase 1 demo: two static volatile variables (counter + sine) sampled at
 * 1 ms and streamed via XCP-over-UDP on port 5556.  The A2L tool finds them
 * by scanning this source file; no runtime A2L generation needed.
 *
 * Phase 3: xcp_meas_image_a53_init() sets up the IPI-driven MEAS event;
 *          the event task (xcp_meas_event_task) is started here too.
 *
 * API verified against XCPlite v2.1.1 (commit 4fe34e4).
 *
 * Copyright 2024 Eyke Liegmann -- Apache-2.0
 ******************************************************************************/

#include "xcp_server_uz.h"
#include "xcp_meas_image_a53.h"

/* XCPlite public API */
#include "xcplib.h"       /* XcpInit, XcpCreateEvent, XcpEvent, XcpEthServerInit */
#include "xcplite.h"      /* ApplXcpSetBaseAddr, ApplXcpRegisterGetClockCallback */

/* Xilinx / FreeRTOS */
#include "xtime_l.h"      /* XTime_GetTime, COUNTS_PER_SECOND */
#include "FreeRTOS.h"
#include "task.h"

#include <math.h>         /* sinf */
#include <stdint.h>

/*---------------------------------------------------------------------------
 * XCP clock: 1 us ticks via Xilinx global timer (~100 MHz on A53).
 *
 * XCPlite calls this via the registered callback (xcpappl.c).
 * Returns a uint64_t so it never wraps during a measurement session.
 *--------------------------------------------------------------------------*/
static uint64_t uz_xcp_get_clock_us(void)
{
    XTime counts;
    XTime_GetTime(&counts);
    /* COUNTS_PER_SECOND is the timer frequency; divide to get microseconds. */
    return (uint64_t)(counts / (COUNTS_PER_SECOND / 1000000ULL));
}

/*---------------------------------------------------------------------------
 * Phase 1 demo measurement variables.
 * Declared static volatile so:
 *   - the compiler does not optimise them away, and
 *   - the offline A2L tool (bintool) finds them by name in this TU.
 * Replace / extend with real signals before Phase 3 activation.
 *--------------------------------------------------------------------------*/
static volatile uint32_t xcp_demo_counter = 0u;
static volatile float    xcp_demo_sine    = 0.0f;

/*---------------------------------------------------------------------------
 * XCPlite event handles.
 * xcp_demo_event_handle  -- Phase 1 1 ms demo DAQ event.
 * xcp_meas_event_handle  -- Phase 3 IPI-driven MEAS event (defined in
 *                           xcp_meas_image_a53.c; set here before the task).
 *--------------------------------------------------------------------------*/
static tXcpEventId xcp_demo_event_handle  = 0u;
/* xcp_meas_event_handle is defined in xcp_meas_image_a53.c and declared extern
 * via xcp_meas_image_a53.h; xcp_server_uz_start() only assigns it below. */

/*---------------------------------------------------------------------------
 * xcp_daq_task
 *
 * Phase 1 demo: periodic loop at the finest period the FreeRTOS tick allows.
 * Increments the counter, computes a ~1 Hz sine, triggers the DAQ event.
 * XCPlite reads xcp_demo_counter and xcp_demo_sine directly from memory
 * (the A2L links their addresses; no explicit "register" call needed).
 *
 * NOTE: the UZ FreeRTOS tick is coarse (configTICK_RATE_HZ = 100 → 10 ms).
 * pdMS_TO_TICKS(1) truncates to 0 ticks, and a 0-tick period makes
 * vTaskDelayUntil() assert (tasks.c configASSERT xTimeIncrement > 0). So the
 * period is clamped to >= 1 tick, and the sine rate is derived from the actual
 * sample rate instead of assuming 1 kHz.
 *--------------------------------------------------------------------------*/
static void xcp_daq_task(void *pvParameters)
{
    (void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    TickType_t xPeriod = pdMS_TO_TICKS(10u);
    if (xPeriod == 0u) {
        xPeriod = 1u;
    }
    /* samples per second at the actual period; guard against divide-by-zero */
    uint32_t samples_per_s = (uint32_t)configTICK_RATE_HZ / (uint32_t)xPeriod;
    if (samples_per_s == 0u) {
        samples_per_s = 1u;
    }

    for (;;) {
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
        xcp_demo_counter++;
        /* ~1 Hz sine: one full period every samples_per_s samples */
        xcp_demo_sine = sinf(2.0f * 3.14159265f *
                             (float)(xcp_demo_counter % samples_per_s) /
                             (float)samples_per_s);
        XcpEvent(xcp_demo_event_handle);
    }
}

/*---------------------------------------------------------------------------
 * xcp_server_uz_start
 *
 * Call from network_bringup_thread / main_thread (main.c) once IP is up,
 * under LOGGING_PATH_XCP_LITE.
 *
 * Returns 0 on success, non-zero on error.
 *--------------------------------------------------------------------------*/
int xcp_server_uz_start(void)
{
    /* --- Clock callback ------------------------------------------------- */
    /* Register our 1 us clock so xcpappl.c forwards ApplXcpGetClock64(). */
    ApplXcpRegisterGetClockCallback(uz_xcp_get_clock_us);

    /* --- Address mapping ------------------------------------------------- */
    /* Base address 0 → XCP address == A53 virtual address (identity map).
     * This is correct for OCM regions and for A53 static variables. */
    ApplXcpSetBaseAddr((const uint8_t *)0);

    /* --- XCPlite protocol layer ----------------------------------------- */
    if (!XcpInit("UltraZohm_XCP", "1.0", XCP_MODE_LOCAL)) {
        return -1;
    }

    /* --- Phase 1 demo event (1 ms, normal priority) --------------------- */
    /* cycle_time_ns = 1000000 (1 ms in nanoseconds) */
    xcp_demo_event_handle = XcpCreateEvent("DAQ_1ms", 1000000u, 0u);

    /* --- Phase 1 DAQ task (CORE: must come up for the demo/test) -------- */
    if (xTaskCreate(xcp_daq_task, "xcp_daq",
                    configMINIMAL_STACK_SIZE * 4u,
                    NULL, 2u, NULL) != pdPASS) {
        return -3;
    }

    /* --- Phase 3 MEAS path (BEST-EFFORT: never blocks the Phase 1 demo) -
     * The IPI-driven shared-image measurement is optional for the A53-only
     * bring-up.  If its semaphore/event/task cannot be created we log and
     * continue so the demo DAQ and the UDP server still come up and can be
     * tested (CANape / xcp_poll.py) without the R5 side being ready. */
    if (xcp_meas_image_a53_init() == 0) {
        xcp_meas_event_handle = (uint16_t)XcpCreateEvent("MEAS_ipi", 0u, 0u);
        if (xTaskCreate(xcp_meas_event_task, "xcp_meas",
                        configMINIMAL_STACK_SIZE * 4u,
                        NULL, 2u, NULL) != pdPASS) {
            DBG_PRINT_WARNING("xcp_server_uz: MEAS event task create failed; "
                              "Phase 3 path disabled, Phase 1 demo unaffected\n");
        }
    } else {
        DBG_PRINT_WARNING("xcp_server_uz: MEAS image init failed; Phase 3 path "
                          "disabled, Phase 1 demo unaffected\n");
    }

    /* --- XCPlite Ethernet server (UDP, port 5556) ----------------------- */
    /* measurement_queue_size: bytes for the DAQ transport queue.
     * 32 KB is sufficient for 64 signals at 1 kHz with one queue flush
     * per lwIP tick (default 250 Hz). */
    if (!XcpEthServerInit(NULL, XCP_UDP_PORT, false, 32u * 1024u)) {
        return -5;
    }

    return 0;
}
