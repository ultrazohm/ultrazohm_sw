//// Configuration of PMSM 2 (Brose PMSM)

//
//// Configuration FOC
//struct uz_SpeedControl_config SC_config_2 = {
//    .config_controller.Kp = 0.1f, //
//    .config_controller.Ki = 2.0f,
//    .config_controller.samplingTime_sec = 0.0001f,
//    .config_controller.upper_limit = 2.0f,
//    .config_controller.lower_limit = -2.0f,
//    .config_controller.type = parallel};
//struct uz_SetPoint_config SP_config_2 = {
//    .config_PMSM = config_PMSM_beckhoff,
//    .control_type = FOC,
//    .motor_type = SMPMSM,
//    .is_field_weakening_enabled = false,
//    .id_ref_Ampere = 0.0f,
//    .relative_torque_tolerance = 0.1f};
//struct uz_PI_Controller_config config_id_2 = {
//    .Kp = 6.67f,   // nach BO
//    .Ki = 1700.0f, // nach BO
//    .samplingTime_sec = 0.0001f,
//    .upper_limit = 15.0f,
//    .lower_limit = -15.0f};
//struct uz_PI_Controller_config config_iq_2 = {
//    .Kp = 6.67f,   // nach BO
//    .Ki = 1700.0f, // nach BO
//    .samplingTime_sec = 0.0001f,
//    .upper_limit = 15.0f,
//    .lower_limit = -15.0f};
//struct uz_CurrentControl_config CC_config_2 = {
//    .decoupling_select = linear_decoupling,
//    .config_PMSM = config_PMSM_beckhoff,
//    .config_id = config_id_2,
//    .config_iq = config_iq_2,
//    .max_modulation_index = 1.0f / sqrtf(3.0f)};

#include "../uz/uz_pmsm_control/uz_pmsm_control.h"
#include "../globalData.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_hoerner_beckhoff = {
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
    .enable_speed_control = true,
    .speed_controller_max_torque = 2.0f,
    .speed_controller_kp = 0.02f,
    .speed_controller_ki = 0.5f,
    .current_controller_d_kp = 1.1f,
    .current_controller_d_ki = 622.5f,
    .current_controller_q_kp = 6.125f,
    .current_controller_q_ki = 622.5f,
    .setpoint_lower_bound_i_d_in_A = -5.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -5.0f,
    .setpoint_upper_bound_i_q_in_A = 5.0f,
    .setpoint_upper_bound_speed_in_rpm = 1100.0f,
    .setpoint_lower_bound_speed_in_rpm = -1100.0f,
    .error_upper_bound_speed_in_rpm = 1500.0f,
    .error_lower_bound_speed_in_rpm = -1500.0f,
    .disturbance_input_lower_bound_in_Nm = 0.0f, // disable disturbance input for now
    .disturbance_input_upper_bound_in_Nm = 0.0f,
    .decoupling_method = static_nonlinear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 100.0f,
    .motor_type = IPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .nonlinear_machine = true,
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

float PMSM_rated_current_hoerner = 15.0f;

struct uz_PMSM_flux_fitting_parameter_config_t beckhoff_fitting = {0};

void init_hoerner_controller()
{
    Global_Data.objects.d2_controller = uz_pmsm_control_init(config_hoerner_controller, config_PMSM_beckhoff, beckhoff_fitting);
    // Global_Data.buehler_actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.buehler_controller);
    // Global_Data.buehler_reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.buehler_controller);
    // Global_Data.buehler_measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.buehler_controller);
}
