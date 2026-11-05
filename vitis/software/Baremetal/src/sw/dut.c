#include "../include/dut.h"
#include <math.h>

static float dut_Kp_iq_V_per_A;

/* Machine parameters match pmsm_cil. Limits are commissioning defaults;
 * validate them against the machine/inverter before using physical hardware.
 */
static const uz_PMSM_t dut_machine_data = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.00175f,
    .Lq_Henry = 0.00175f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 12.0f
};

uz_pmsm_control_t* initialize_dut(float sample_time_s)
{
    struct uz_pmsm_control_configuration_t config = {
        .sample_time = sample_time_s,
        .enable_speed_control = false,
        .setpoint_limits = {
            .speed_controller_torque_in_Nm = {.lower_bound = -2.5f, .upper_bound = 2.5f},
            .i_d_in_A = {.lower_bound = -12.0f, .upper_bound = 12.0f},
            .i_q_in_A = {.lower_bound = DUT_IQ_REFERENCE_MIN_A, .upper_bound = DUT_IQ_REFERENCE_MAX_A},
            .speed_in_rpm = {.lower_bound = -1100.0f, .upper_bound = 1100.0f},
            .disturbance_input_in_Nm = {.lower_bound = -2.5f, .upper_bound = 2.5f}
        },
        .safe_operating_region = {
            .speed_in_rpm = {.lower_bound = -3000.0f, .upper_bound = 3000.0f},
            .i_d_in_A = {.lower_bound = -24.0f, .upper_bound = 24.0f},
            .i_q_in_A = {.lower_bound = -24.0f, .upper_bound = 24.0f},
            .i_abc_in_A = {.lower_bound = -30.0f, .upper_bound = 30.0f},
            .v_dc_in_V = {.lower_bound = 12.0f, .upper_bound = 60.0f},
            .i_dc_in_A = {.lower_bound = -10.0f, .upper_bound = 10.0f}
        },
        .decoupling_method = linear_decoupling,
        .motor_type = SMPMSM,
        .enable_field_weakening = false,
        .relative_torque_tolerance = 0.01f,
        /* Filters, speed PI gains, offsets and angle compensation start at zero.
         * Zero angle compensation is required by the dq-only CIL adapter.
         */
        .default_duty_cycle = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f}
    };
    uz_pmsm_control_t* dut = uz_pmsm_control_init(config, dut_machine_data);
    // Initial bandwidth about 800 Hz. The existing tuning function uses Kp_q = Lq * bandwidth.
    const float bandwidth_rad_per_sec = 5026.0f;
    uz_pmsm_control_current_control_tune_bandwidth(dut, bandwidth_rad_per_sec);
    dut_set_Kp_iq(dut, dut_machine_data.Lq_Henry * bandwidth_rad_per_sec);
    return dut;
}

float dut_estimate_torque_Nm(uz_3ph_dq_t currents_A)
{
    return 1.5f * dut_machine_data.polePairs *
        (dut_machine_data.Psi_PM_Vs + (dut_machine_data.Ld_Henry - dut_machine_data.Lq_Henry) * currents_A.d) * currents_A.q;
}

bool dut_set_Kp_iq(uz_pmsm_control_t *dut, float Kp_iq_V_per_A)
{
    if (!isfinite(Kp_iq_V_per_A) || Kp_iq_V_per_A < 0.0f)
        return false;
    uz_pmsm_control_current_control_set_Kp_iq(dut, Kp_iq_V_per_A);
    dut_Kp_iq_V_per_A = Kp_iq_V_per_A;
    return true;
}

float dut_get_Kp_iq(void)
{
    return dut_Kp_iq_V_per_A;
}
