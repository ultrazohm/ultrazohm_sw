
#include <stdint.h>
#include <stdbool.h>

#include "xil_cache.h"
#include "../uz/uz_SystemTime/uz_AxiTimer64Bit.h"
#include "xcp_R5.h"

//--------------------------------------------------------------------
// Configuration
// -------------------------------------------------------------------
#define XCP_MEAS_R5_ADDR        0xFFFC0400
#define XCP_MEAS_R5_LEN            0x00000400
#define XCP_STIM_R5_ADDR        0xFFFC0800
#define XCP_STIM_R5_LEN            0x00000400

#define SECTION_XCP_TS       __attribute__ ((section (".section_xcp_timestamp")))
#define SECTION_XCP_MEAS    __attribute__ ((section (".section_xcp_meas")))
#define SECTION_XCP_STIM    __attribute__ ((section (".section_xcp_stim")))

//--------------------------------------------------------------------
// Types
// -------------------------------------------------------------------
typedef enum {
    tmeas_isr,
    tmeas_systeTimeFunction,
    tmeas_getADC,
    tmeas_control_step,
    tmeas_setPWM,
    tmeas_javascope,
    tmeas_dummy,
    tmeas_tmeas,
    tmeas_cnt // Must be last!
} time_measurement_t;

typedef struct {
    uint32_t start_ns[tmeas_cnt];
    uint32_t now_ns[tmeas_cnt];
    uint32_t max_last3s_ns[tmeas_cnt];
    uint32_t temp_last3s_ns[tmeas_cnt];
} tmeas_t;
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

typedef struct _timing_R5_t {
    float isr_period_us;                    // measured period of interrupt in micro seconds
    float isr_execution_time_us;            // measured execution time of interrupt service routine (isr)
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
uint32_t xcp_timestamp_R5 SECTION_XCP_TS = 0;

/* All variables that shall be measured/stimulated via XCP must be placed in
 * an special section. Use the above define
 * - SECTION_XCP_MEAS for data that shall be measured via XCP
 * - SECTION_XCP_STIM for data that shall be stimulated via XCP
 */
xcp_stim_t xcp_stim SECTION_XCP_STIM = {0};
tmeas_t tmeas SECTION_XCP_MEAS = {0};
xcp_meas_t xcp_meas SECTION_XCP_MEAS = {0};


uint8_t xcp_80Byte_u8[DUMMY_LEN] SECTION_XCP_MEAS = {0};
uint32_t xcp_80Byte_u32[DUMMY_LEN/4] SECTION_XCP_MEAS = {0};

timing_R5_t timing_R5 SECTION_XCP_MEAS = {0};

//--------------------------------------------------------------------
// Global functions
// -------------------------------------------------------------------
void xcp_R5_cache_flush_stimulate(void)
{
    uint32_t ts_start = uz_AxiTimer64Bit_getTimestamp_u32();
    Xil_DCacheFlushRange(XCP_STIM_R5_ADDR, XCP_STIM_R5_LEN);
    timing_R5.xcp_cache_flush_stim_us = (uz_AxiTimer64Bit_getTimestamp_u32() - ts_start) / 100.0f;
}

void xcp_R5_cache_flush_measure(void)
{
    uint32_t ts_start = uz_AxiTimer64Bit_getTimestamp_u32();
    Xil_DCacheFlushRange(XCP_MEAS_R5_ADDR, XCP_MEAS_R5_LEN);
    timing_R5.xcp_cache_flush_meas_us = (uz_AxiTimer64Bit_getTimestamp_u32() - ts_start) / 100.0f;
}

void xcp_R5_set_timestamp(void)
{
    /* Timestamp used for XCP as basis.
     * XCP must be configured according to the frequency of this counter
     * via define 'kXcpDaqTimestampTicksPerUnit' in file 'xcp_cfg.h'. */
    xcp_timestamp_R5 = uz_AxiTimer64Bit_getTimestamp_u32();
}

// TODO remove!
void xcp_dummy_calculations(void)
{
    // Set measured timings to read it via XCP
    extern float uz_SystemTime_GetIsrExectionTimeInUs();
    timing_R5.isr_execution_time_us = uz_SystemTime_GetIsrExectionTimeInUs();
    extern float uz_SystemTime_GetIsrPeriodInUs();
    timing_R5.isr_period_us = uz_SystemTime_GetIsrPeriodInUs();

    static int init_once = 1;
    if (init_once) {
        init_once = 0;
        for (int i = 0; i < DUMMY_LEN; i++)
            xcp_80Byte_u8[i] = i;
        for (int i = 0; i < DUMMY_LEN/4; i++)
            xcp_80Byte_u32[i] = i;
    }

    for (int i = 0; i < DUMMY_LEN; i++)
        xcp_80Byte_u8[i] += 1;
    for (int i = 0; i < DUMMY_LEN/4; i++)
        xcp_80Byte_u32[i] += 1;

    if (xcp_stim.disable_calculation == 0) {
        static int div_cnt = 0;
        if (++div_cnt >= 40) {
            div_cnt = 0;
            xcp_meas.saw_u8++;
        }
        float arg_2pi = (float) xcp_meas.saw_u8 * (float)M_PI * 2 / 255;

        xcp_meas.sin_f = sinf(arg_2pi);
        xcp_meas.cos_f = cosf(arg_2pi);
        xcp_meas.saw_f = (float)xcp_meas.saw_u8 / 255;

        xcp_meas.sin_u8 = xcp_meas.sin_f * 127;
        xcp_meas.cos_u8 = sinf(arg_2pi + (float)M_PI / 2) * 127;
    }
}
