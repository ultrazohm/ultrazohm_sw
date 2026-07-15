#include "../include/control_init.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"
#include "../globalData.h"
extern DS_Data Global_Data;

static struct uz_PMSM_t Beckhoff_AM8071_0R01 = {
    .R_ph_Ohm = 0.08f,
    .Ld_Henry = 0.0011f,
    .Lq_Henry = 0.0011f,
    .Psi_PM_Vs = 0.1092f,
    .polePairs = 5.0f,
    .J_kg_m_squared = 0.00683f,
    .I_max_Ampere = 81.8f};

static struct uz_pmsm_control_configuration_t config_Beckhoff_AM8071 = {
    .theta_el_offset = 0.0f, // adjust!
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = true,
    .speed_controller_kp = 0.097f, // 0.122 adjust!
    .speed_controller_ki = 0.567f, // 1.107 adjust!
    .current_controller_d_kp = 3.667f,
    .current_controller_d_ki = 266.667f,
    .current_controller_q_kp = 3.667f,
    .current_controller_q_ki = 266.667f,
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 78.0f, .lower_bound = -78.0f},
        .i_d_in_A = {.upper_bound = 17.6f, .lower_bound = -17.6f},
        .i_q_in_A = {.upper_bound = 17.6f, .lower_bound = -17.6f},
        .speed_in_rpm = {.upper_bound = 4000.0f, .lower_bound = -4000.0f},
        .disturbance_input_in_Nm = {.upper_bound = 10.0f, .lower_bound = -10.0f}},
    .safe_operating_region = {
        .speed_in_rpm = {.upper_bound = 1500.0f, .lower_bound = -1500.0f},
        .i_d_in_A = {.upper_bound = 30.0f, .lower_bound = -30.0f},
        .i_q_in_A = {.upper_bound = 30.0f, .lower_bound = -30.0f},
        .i_abc_in_A = {.upper_bound = 30.0f, .lower_bound = -30.0f},
        .v_dc_in_V = {.upper_bound = 600.0f, .lower_bound = 530.0f},
        .i_dc_in_A = {.upper_bound = 80.0f, .lower_bound = -85.0f}},
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.0f,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .theta_sampling_compensation = 0.0f,
    .theta_svm_delay_compensation = 1.5f,
    .voltage_theta_shift = 0.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f}};

void init_control_Beckhoff_AM8071(void) {
	Global_Data.objects.pmsm_control_Beckhoff_AM8071 = uz_pmsm_control_init(config_Beckhoff_AM8071, Beckhoff_AM8071_0R01);
    uz_pmsm_control_current_control_tune_magnitude_optimum(Global_Data.objects.pmsm_control_Beckhoff_AM8071, 0.5f * config_Beckhoff_AM8071.sample_time);
    uz_pmsm_control_enable(Global_Data.objects.pmsm_control_Beckhoff_AM8071, true);
}

