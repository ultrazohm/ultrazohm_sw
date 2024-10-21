#include "../include/init_ebm_on_d1.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_ebm = {
    .current_conversion_factors = {
        .a = 12.223f,
        .b = 12.3123f,
        .c = 12.4303f},
    .current_offsets = {.a = +0.0164f, .b = +0.0161f, .c = -0.0184f},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 2.910038f, // Manual: 3.000038f, second try: 3.020038
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = D1_IS_PRIME_MOVER,
    .speed_controller_max_torque = 0.3f,
    .speed_controller_kp = 0.005f,
    .speed_controller_ki = 0.01f,
    .current_controller_d_kp = 1.4667f,
    .current_controller_d_ki = 700.0f,
    .current_controller_q_kp = 1.4667f,
    .current_controller_q_ki = 700.0f,
    .setpoint_lower_bound_i_d_in_A = -15.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -15.0f,
    .setpoint_upper_bound_i_q_in_A = 15.0f,
    .setpoint_upper_bound_speed_in_rpm = 2500.0f,
    .setpoint_lower_bound_speed_in_rpm = -2500.0f,
    .error_upper_bound_speed_in_rpm = 3500.0f,
    .error_lower_bound_speed_in_rpm = -3500.0f,
    .disturbance_input_lower_bound_in_Nm = 0.0f, // disable disturbance input for now
    .disturbance_input_upper_bound_in_Nm = 0.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 100.0f,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .use_rlcc = false,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t config_PMSM_ebm = {
    .R_ph_Ohm = 0.21f,
    .Ld_Henry = 0.00044f,
    .Lq_Henry = 0.00044f,
    .Psi_PM_Vs = 0.0116f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000084f,
    .I_max_Ampere = 15.0f};
float PMSM_rated_current_ebm = 8.6f;

struct uz_PMSM_flux_fitting_parameter_config_t ebm_fitting = {0};

void init_ebm_on_d1(void)
{
    Global_Data.objects.d1_controller = uz_pmsm_control_init(config_ebm, config_PMSM_ebm, ebm_fitting);

    if (D1_IS_PRIME_MOVER)
    {
        Global_Data.prime_mover.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d1_controller);
        Global_Data.prime_mover.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d1_controller);
        Global_Data.prime_mover.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d1_controller);
    }
    else
    {
        Global_Data.dut.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d1_controller);
        Global_Data.dut.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d1_controller);
        Global_Data.dut.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d1_controller);
        Global_Data.dut.torque_constant=3.0f/2.0f*config_PMSM_ebm.polePairs*config_PMSM_ebm.Psi_PM_Vs;
    }
}
