#pragma once
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

#define DUT_IQ_REFERENCE_MIN_A (-12.0f)
#define DUT_IQ_REFERENCE_MAX_A (12.0f)

/* Independent of the measurement source and output hardware. */
uz_pmsm_control_t* initialize_dut(float sample_time_s);

/* Electromagnetic torque estimate from measured dq currents and identified parameters. */
float dut_estimate_torque_Nm(uz_3ph_dq_t currents_A);

/* Application-maintained q-axis Kp in V/A. Route DUT Kp changes through this helper.
 * It tracks applied settings; it is not a readback of the controller internals. */
bool dut_set_Kp_iq(uz_pmsm_control_t *dut, float Kp_iq_V_per_A);
float dut_get_Kp_iq(void);
