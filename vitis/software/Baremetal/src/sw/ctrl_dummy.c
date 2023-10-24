
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "xcp_R5.h"

//--------------------------------------------------------------------
// Configuration
// -------------------------------------------------------------------
#define DUMMY_LEN            80

//--------------------------------------------------------------------
// Types
// -------------------------------------------------------------------
typedef struct {
    float isr_period_us;         // measured period of interrupt in micro seconds
    float isr_execution_time_us; // measured execution time of interrupt service routine (isr)
} timing_control_t;

typedef struct xcp_stim_t_ {
    bool button_enable_system;
    bool button_enable_control;
    bool disable_calculation;
} xcp_stim_t;

typedef struct {
    int8_t sin_u8;
    int8_t cos_u8;
    int8_t saw_u8;
    float sin_f;
    float cos_f;
    float saw_f;
} xcp_meas_t;

//--------------------------------------------------------------------
// Variables
// -------------------------------------------------------------------
/* All variables that shall be measured/stimulated via XCP must be placed in
 * an special section. Use the above define
 * - SECTION_XCP_MEAS for data that shall be measured via XCP
 * - SECTION_XCP_STIM for data that shall be stimulated via XCP
 */
static xcp_stim_t ctrl_stim SECTION_XCP_MEAS = {0};
static xcp_meas_t ctrl_meas SECTION_XCP_MEAS = {0};

static uint8_t ctrl_80Byte_u8[DUMMY_LEN] SECTION_XCP_MEAS = {0};
static uint32_t ctrl_80Byte_u32[DUMMY_LEN/4] SECTION_XCP_MEAS = {0};

static volatile timing_control_t ctrl_timing SECTION_XCP_MEAS = {0};

//--------------------------------------------------------------------
// Global functions
// -------------------------------------------------------------------
void xcp_ctrl_dummy(void)
{
    // Set measured timings to read it via XCP
    extern float uz_SystemTime_GetIsrExectionTimeInUs();
    ctrl_timing.isr_execution_time_us = uz_SystemTime_GetIsrExectionTimeInUs();
    extern float uz_SystemTime_GetIsrPeriodInUs();
    ctrl_timing.isr_period_us = uz_SystemTime_GetIsrPeriodInUs();

    static int init_once = 1;
    if (init_once) {
        init_once = 0;
        for (int i = 0; i < DUMMY_LEN; i++)
            ctrl_80Byte_u8[i] = i;
        for (int i = 0; i < DUMMY_LEN/4; i++)
            ctrl_80Byte_u32[i] = i;
    }

    for (int i = 0; i < DUMMY_LEN; i++)
        ctrl_80Byte_u8[i] += 1;
    for (int i = 0; i < DUMMY_LEN/4; i++)
        ctrl_80Byte_u32[i] += 1;

    if (ctrl_stim.disable_calculation == 0) {
        static int div_cnt = 0;
        if (++div_cnt >= 40) {
            div_cnt = 0;
            ctrl_meas.saw_u8++;
        }
        float arg_2pi = (float) ctrl_meas.saw_u8 * (float)M_PI * 2 / 255;

        ctrl_meas.sin_f = sinf(arg_2pi);
        ctrl_meas.cos_f = cosf(arg_2pi);
        ctrl_meas.saw_f = (float)ctrl_meas.saw_u8 / 255;

        ctrl_meas.sin_u8 = ctrl_meas.sin_f * 127;
        ctrl_meas.cos_u8 = sinf(arg_2pi + (float)M_PI / 2) * 127;
    }
}
