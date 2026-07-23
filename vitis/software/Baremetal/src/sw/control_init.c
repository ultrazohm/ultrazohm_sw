#include "../include/control_init.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"
#include "../IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "../globalData.h"
extern DS_Data Global_Data;

const struct uz_PMSM_t Beckhoff_AM8071_0R01 = {
	.machine_id = 0U,
    .R_ph_Ohm = 0.08f,
    .Ld_Henry = 0.0011f,
    .Lq_Henry = 0.0011f,
    .Psi_PM_Vs = 0.1092f,
    .polePairs = 5.0f,
    .J_kg_m_squared = 0.00683f,
    .I_max_Ampere = 81.8f,
	.I_rated_Ampere = 17.6f,
	.Torque_rated_Nm = 18.0f,
	.Torque_max_Nm = 78.0f,
	.Torque_min_Nm = 0.0f,
	.speed_rated_rpm = 4000.0f,
	.speed_max_rpm = 5000.0f,
	.speed_min_rpm = 0.0f,
	.V_dc_nominal_V = 565.0f,
	.I_d_max_A = 81.8f,
	.I_d_min_A = -81.8f,
	.I_q_max_A = 81.8f,
	.I_q_min_A = -81.8f};

static struct uz_pmsm_control_configuration_t config_Beckhoff_AM8071 = {
    .theta_el_offset = 0.0f, // adjust!
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = false,
    .speed_controller_kp = 0.122, //adjust!
    .speed_controller_ki = 0.0, //1.107, // adjust!
    .current_controller_d_kp = 3.667f,
    .current_controller_d_ki = 266.667f,
    .current_controller_q_kp = 3.667f,
    .current_controller_q_ki = 266.667f,
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 2.0f, .lower_bound = -2.0f},
        .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .speed_in_rpm = {.upper_bound = 500.0f, .lower_bound = -500.0f},
        .disturbance_input_in_Nm = {.upper_bound = 1.0f, .lower_bound = -1.0f}},
    .safe_operating_region = {
        .speed_in_rpm = {.upper_bound = 500.0f, .lower_bound = -500.0f},
        .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .i_abc_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .v_dc_in_V = {.upper_bound = 50.0f, .lower_bound = -1.0f},
        .i_dc_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f}},
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 1.45f,
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
    uz_pmsm_control_current_control_tune_magnitude_optimum(Global_Data.objects.pmsm_control_Beckhoff_AM8071, 1.5f * config_Beckhoff_AM8071.sample_time);
    uz_pmsm_control_enable(Global_Data.objects.pmsm_control_Beckhoff_AM8071, false);
}

struct uz_pmsmModel_config_t pmsm_ip_config_Beckhoff={
    .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
    .ip_core_frequency_Hz=100000000,
    .simulate_mechanical_system = true,
    .r_1 = Beckhoff_AM8071_0R01.R_ph_Ohm,
    .L_d = Beckhoff_AM8071_0R01.Ld_Henry,
    .L_q = Beckhoff_AM8071_0R01.Lq_Henry,
    .psi_pm = Beckhoff_AM8071_0R01.Psi_PM_Vs,
    .polepairs = Beckhoff_AM8071_0R01.polePairs,
    .inertia = Beckhoff_AM8071_0R01.J_kg_m_squared,
    .coulomb_friction_constant = 0.01f,
    .friction_coefficient = 0.001f};

uz_pmsmModel_t* init_pmsm_cil_Beckhoff(void) {
	return(uz_pmsmModel_init(pmsm_ip_config_Beckhoff));
 	}
