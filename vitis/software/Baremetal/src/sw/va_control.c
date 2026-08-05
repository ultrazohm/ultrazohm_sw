#include "../include/va_control.h"
#include "../uz/uz_global_configuration.h"
#include <float.h>

/* VA machine and controller data taken from the local VA test-bench branch. */
static const uz_PMSM_t va_machine = {
    .R_ph_Ohm = 0.157f,
    .Ld_Henry = 585.0e-6f,
    .Lq_Henry = 770.0e-6f,
    .Psi_PM_Vs = 0.0167f,
    .polePairs = 4.0f,
    .I_max_Ampere = 12.0f,
    .J_kg_m_squared = 0.000108f,
};

static const struct uz_pmsm_control_configuration_t va_control_config = {
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 8.0f, .lower_bound = -8.0f},
        .i_d_in_A = {.upper_bound = 12.0f, .lower_bound = -12.0f},
        .i_q_in_A = {.upper_bound = 12.0f, .lower_bound = -12.0f},
        .speed_in_rpm = {.upper_bound = VA_PROTECTION_MAX_SPEED_RPM, .lower_bound = -VA_PROTECTION_MAX_SPEED_RPM},
        .disturbance_input_in_Nm = {.upper_bound = 8.0f, .lower_bound = -8.0f},
    },
    .safe_operating_region = {
        .speed_in_rpm = {.upper_bound = VA_PROTECTION_MAX_SPEED_RPM, .lower_bound = -VA_PROTECTION_MAX_SPEED_RPM},
        .i_d_in_A = {.upper_bound = VA_PROTECTION_MAX_DQ_CURRENT_A, .lower_bound = -VA_PROTECTION_MAX_DQ_CURRENT_A},
        .i_q_in_A = {.upper_bound = VA_PROTECTION_MAX_DQ_CURRENT_A, .lower_bound = -VA_PROTECTION_MAX_DQ_CURRENT_A},
        .i_abc_in_A = {.upper_bound = VA_PROTECTION_MAX_PHASE_CURRENT_A, .lower_bound = -VA_PROTECTION_MAX_PHASE_CURRENT_A},
        .v_dc_in_V = {.upper_bound = VA_PROTECTION_MAX_DC_VOLTAGE_V, .lower_bound = VA_PROTECTION_MIN_DC_VOLTAGE_V},
        .i_dc_in_A = {.upper_bound = FLT_MAX, .lower_bound = -FLT_MAX},
    },
    .theta_el_offset = 0.0f,
    .sample_time = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / UZ_PWM_FREQUENCY,
    .enable_speed_control = false,
    .speed_controller_kp = 0.2f,
    .speed_controller_ki = 2.0f,
    .current_controller_d_kp = 0.585e-3f * UZ_PWM_FREQUENCY / 2.0f,
    .current_controller_d_ki = 0.157f * UZ_PWM_FREQUENCY / 2.0f,
    .current_controller_q_kp = 0.770e-3f * UZ_PWM_FREQUENCY / 2.0f,
    .current_controller_q_ki = 0.157f * UZ_PWM_FREQUENCY / 2.0f,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.5f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .decoupling_method = no_decoupling,
    .motor_type = IPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.01f,
    .theta_sampling_compensation = 1.0f,
    .theta_svm_delay_compensation = 0.5f,
    .voltage_theta_shift = 0.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f},
};

uz_pmsm_control_t *va_control_init(void)
{
    return uz_pmsm_control_init(va_control_config, va_machine);
}
