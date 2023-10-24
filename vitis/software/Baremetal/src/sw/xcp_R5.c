
#include <stdint.h>
#include <stdbool.h>

#include "xil_cache.h"
#include "../uz/uz_SystemTime/uz_AxiTimer64Bit.h"
#include "xcp_R5.h"

//--------------------------------------------------------------------
// Configuration
// -------------------------------------------------------------------
#define XCP_MEAS_R5_ADDR        0xFFFC0400
#define XCP_MEAS_R5_LEN         0x00001400

//--------------------------------------------------------------------
// Types
// -------------------------------------------------------------------
//typedef enum {
//    tmeas_isr,
//    tmeas_systeTimeFunction,
//    tmeas_getADC,
//    tmeas_control_step,
//    tmeas_setPWM,
//    tmeas_javascope,
//    tmeas_dummy,
//    tmeas_tmeas,
//    tmeas_cnt // Must be last!
//} time_measurement_t;
//
//typedef struct {
//    uint32_t start_ns[tmeas_cnt];
//    uint32_t now_ns[tmeas_cnt];
//    uint32_t max_last3s_ns[tmeas_cnt];
//    uint32_t temp_last3s_ns[tmeas_cnt];
//} tmeas_t;
//
//#define TMEAS_START(_tmeas) \
//        tmeas.start_ns[_tmeas] = timestamp_get();
//
//#define TMEAS_END(_tmeas) \
//    do { \
//        tmeas.now_ns[_tmeas] = timestamp_calculate_delta_ns(tmeas.start_ns[_tmeas], timestamp_get()); \
//        if (trigger_3s_passed) { \
//            tmeas.max_last3s_ns[_tmeas] = tmeas.temp_last3s_ns[_tmeas]; \
//            tmeas.temp_last3s_ns[_tmeas] = 0; \
//        } \
//        if (tmeas.now_ns[_tmeas] > tmeas.temp_last3s_ns[_tmeas]) \
//        tmeas.temp_last3s_ns[_tmeas] = tmeas.now_ns[_tmeas]; \
//    } while (0)

typedef struct {
    float xcp_cache_flush_stim_us;
    float xcp_cache_flush_meas_us;
} timing_R5_t;

//--------------------------------------------------------------------
// Variables
// -------------------------------------------------------------------
/* This timestamp is the basis for the XCP measurements.
 * It is created here in the R5 and placed in the OCM like the other XCP data
 * that is exchanged with the A53 core.
 * It is placed in an own section to have it at a fixed address. So it can be
 * read and interpreted by the A53 as timebase.
 */
static volatile uint32_t xcp_timestamp_R5 SECTION_XCP_TS = 0;

static volatile timing_R5_t xcp_timing_R5 SECTION_XCP_MEAS = {0};

//--------------------------------------------------------------------
// Global functions
// -------------------------------------------------------------------
void xcp_R5_cache_flush_stimulate(void)
{
    uint32_t ts_start = uz_AxiTimer64Bit_getTimestamp_u32();
    Xil_DCacheFlushRange(XCP_MEAS_R5_ADDR, XCP_MEAS_R5_LEN);
    xcp_timing_R5.xcp_cache_flush_stim_us = (uz_AxiTimer64Bit_getTimestamp_u32() - ts_start) / 100.0f;
}

void xcp_R5_cache_flush_measure(void)
{
    uint32_t ts_start = uz_AxiTimer64Bit_getTimestamp_u32();
    Xil_DCacheFlushRange(XCP_MEAS_R5_ADDR, XCP_MEAS_R5_LEN);
    xcp_timing_R5.xcp_cache_flush_meas_us = (uz_AxiTimer64Bit_getTimestamp_u32() - ts_start) / 100.0f;
}

void xcp_R5_set_timestamp(void)
{
    /* Timestamp used for XCP as basis.
     * XCP must be configured according to the frequency of this counter
     * via define 'kXcpDaqTimestampTicksPerUnit' in file 'xcp_cfg.h'. */
    xcp_timestamp_R5 = uz_AxiTimer64Bit_getTimestamp_u32();
}
