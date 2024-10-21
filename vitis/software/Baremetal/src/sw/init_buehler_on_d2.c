#include "../include/init_buehler_on_d2.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_buehler = {
    .current_conversion_factors = {
        .a = 12.2889f,
        .b = 11.8330f,
        .c = 11.7894f},
    .current_offsets = {.a = 0.0164f, .b = 0.0161f, .c = 0.0184f},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 2.251070, // 2.151070f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = D2_IS_PRIME_MOVER,
    .speed_controller_max_torque = 0.3f,
    .speed_controller_kp = 0.005f,
    .speed_controller_ki = 0.01f,
    .current_controller_d_kp = 0.83333f,
    .current_controller_d_ki = 283.33f,
    .current_controller_q_kp = 0.83333f,
    .current_controller_q_ki = 283.33f,
    .setpoint_lower_bound_i_d_in_A = -5.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -5.0f,
    .setpoint_upper_bound_i_q_in_A = 5.0f,
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
    .nonlinear_machine = false,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .use_rlcc = false,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t config_PMSM_buehler = {
    .R_ph_Ohm = 0.085f,
    .Ld_Henry = 0.00025f,
    .Lq_Henry = 0.00025f,
    .Psi_PM_Vs = 0.006f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 15.0f};

float PMSM_rated_current_buehler= 15.0f;

struct uz_PMSM_flux_fitting_parameter_config_t buehler_fitting = {0};

void init_buehler_on_d2(void)
{
    Global_Data.objects.d2_controller = uz_pmsm_control_init(config_buehler, config_PMSM_buehler, buehler_fitting);

    if (D2_IS_PRIME_MOVER)
    {
        Global_Data.prime_mover.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
        Global_Data.prime_mover.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
        Global_Data.prime_mover.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
    }
    else
    {
        Global_Data.dut.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
        Global_Data.dut.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
        Global_Data.dut.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
    }
}
