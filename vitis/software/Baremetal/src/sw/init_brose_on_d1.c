#include "../include/init_brose_on_d1.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_brose = {
    .current_conversion_factors = {
        .a = 12.223f,
        .b = 12.3123f,
        .c = 12.4303f},
    .current_offsets = {.a = +0.0164f, .b = +0.0161f, .c = -0.0184f},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 1.642250f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = D1_IS_PRIME_MOVER,
    .speed_controller_max_torque = 0.5f,
    .speed_controller_kp = 0.1f,
    .speed_controller_ki = 1.0f,
    .current_controller_d_kp = 0.1f,
    .current_controller_d_ki = 76.0f,
    .current_controller_q_kp = 0.2f,
    .current_controller_q_ki = 76.0f,
    .setpoint_lower_bound_i_d_in_A = -15.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -15.0f,
    .setpoint_upper_bound_i_q_in_A = 15.0f,
    .setpoint_upper_bound_speed_in_rpm = 1100.0f,
    .setpoint_lower_bound_speed_in_rpm = -1100.0f,
    .error_upper_bound_speed_in_rpm = 1500.0f,
    .error_lower_bound_speed_in_rpm = -1500.0f,
    .disturbance_input_lower_bound_in_Nm = 0.0f, // disable disturbance input for now
    .disturbance_input_upper_bound_in_Nm = 0.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.0f,
    .motor_type = IPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .nonlinear_machine = false,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .use_rlcc = false,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t config_PMSM_brose = {
    .R_ph_Ohm = 0.023f,
    .Ld_Henry = 3e-5f,
    .Lq_Henry = 6e-5f,
    .Psi_PM_Vs = 0.007f,
    .polePairs = 5.0f,
    .J_kg_m_squared = 0.000084f,
    .I_max_Ampere = 35.0f};
float PMSM_rated_current_brose = 28.3f;

struct uz_PMSM_flux_fitting_parameter_config_t brose_fitting = {0};

void init_brose_on_d1(void)
{
    Global_Data.objects.d1_controller = uz_pmsm_control_init(config_brose, config_PMSM_brose, brose_fitting);

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
        Global_Data.dut.torque_constant = 3.0f / 2.0f * config_PMSM_brose.polePairs * config_PMSM_brose.Psi_PM_Vs;
    }
}
