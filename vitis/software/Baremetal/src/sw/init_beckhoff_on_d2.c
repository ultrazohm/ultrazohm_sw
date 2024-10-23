#include "../include/init_beckhoff_on_d2.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_beckhoff = {
    .current_conversion_factors = {
        .a = 12.2889f,
        .b = 11.8330f,
        .c = 11.7894f},
    .current_offsets = {.a = 0.0164f, .b = 0.0161f, .c = 0.0184f},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 0.0f, // Offset handled in resolver IP core
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = D2_IS_PRIME_MOVER,
    .speed_controller_max_torque = 2.0f,
    .speed_controller_kp = 0.01f,
    .speed_controller_ki = 0.05f,
    .current_controller_d_kp = 6.67f,
    .current_controller_d_ki = 1700.0f,
    .current_controller_q_kp = 6.67,
    .current_controller_q_ki = 1700.0f,
    .setpoint_lower_bound_i_d_in_A = -5.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -5.0f,
    .setpoint_upper_bound_i_q_in_A = 5.0f,
    .setpoint_upper_bound_speed_in_rpm = 1100.0f,
    .setpoint_lower_bound_speed_in_rpm = -1100.0f,
    .error_upper_bound_speed_in_rpm = 1500.0f,
    .error_lower_bound_speed_in_rpm = -1500.0f,
    .disturbance_input_lower_bound_in_Nm = -10.0f,
    .disturbance_input_upper_bound_in_Nm = 10.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = PRIME_MOVER_SETPOINT_FILTER_CUTTOFF_FREQUENCY,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .nonlinear_machine = false,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .use_rlcc = false,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t config_PMSM_beckhoff = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.002f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 12.0f};

float PMSM_rated_current_beckhoff= 15.0f;

struct uz_PMSM_flux_fitting_parameter_config_t beckhoff_fitting = {0};

void init_beckhoff_on_d2(void)
{
    Global_Data.objects.d2_controller = uz_pmsm_control_init(config_beckhoff, config_PMSM_beckhoff, beckhoff_fitting);

    if (D2_IS_PRIME_MOVER){
        Global_Data.prime_mover.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
        Global_Data.prime_mover.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
        Global_Data.prime_mover.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
    }else{
        Global_Data.dut.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
        Global_Data.dut.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
        Global_Data.dut.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
        Global_Data.dut.torque_constant = 3.0f / 2.0f * config_PMSM_beckhoff.polePairs * config_PMSM_beckhoff.Psi_PM_Vs;
        Global_Data.profile.id_scale_in_A = 1.0f/4.2f;
        Global_Data.profile.iq_scale_in_A = 1.0f;
        Global_Data.profile.speed_scale_in_rpm = 1000.0f;
    }
}
