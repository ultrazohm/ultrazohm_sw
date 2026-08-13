#include "../include/testbenchsetup.h"
#include "../uz/uz_HAL.h"

struct testbenchsetup_im_t testbenchsetup_create_im(float sample_time_s)
{
    uz_assert(sample_time_s > 0.0f);

    struct testbenchsetup_im_t setup = {
        .machine = {
            .Rs_Ohm = MOTOR_Rs_Ohm,
            .Rr_Ohm = MOTOR_Rr_Ohm,
            .Lsigma_s_Henry = MOTOR_Lsigma_s_H,
            .Lsigma_r_Henry = MOTOR_Lsigma_r_H,
            .Lm_Henry = MOTOR_Lm_H,
            .polePairs = MOTOR_PolePairs,
            .J_kg_m_squared = MOTOR_J_kgm2,
            .I_max_Ampere = MOTOR_Control_current_max_A,
            .Psi_rated_Vs = MOTOR_Psi_rated_Vs,
        },
    };
    float const sigma_ls = uz_IM_config_get_sigma(setup.machine) * uz_IM_config_get_Ls(setup.machine);
    float const current_kp = MOTOR_Current_Kp_scale * sigma_ls / (2.0f * sample_time_s);
    float const current_ki = MOTOR_Current_Ki_scale * setup.machine.Rs_Ohm / (2.0f * sample_time_s);

    setup.control = (struct uz_im_control_configuration_t){
        .sample_time_s = sample_time_s,
        .current_controller_d_kp = current_kp,
        .current_controller_d_ki = current_ki,
        .current_controller_q_kp = current_kp,
        .current_controller_q_ki = current_ki,
        .speed_controller_kp = MOTOR_Speed_Kp,
        .speed_controller_ki = MOTOR_Speed_Ki,
        .u_f_ratio_V_per_Hz = MOTOR_UF_ratio_V_per_Hz,
        .u_f_boost_voltage_V = MOTOR_UF_boost_voltage_V,
        .u_f_max_frequency_Hz = MOTOR_UF_max_frequency_Hz,
        .u_f_max_voltage_V = MOTOR_UF_max_voltage_V,
        .u_f_frequency_ramp_Hz_per_s = MOTOR_UF_frequency_ramp_Hz_per_s,
        .kalman_process_noise_A2_per_s = MOTOR_KF_Q_i,
        .kalman_measurement_noise_A2 = MOTOR_KF_R_i,
        .minimum_observer_flux_Vs = MOTOR_Minimum_observer_flux_Vs,
        .resonant_gain_d = MOTOR_Resonant_gain_scale * current_kp,
        .resonant_gain_q = MOTOR_Resonant_gain_scale * current_kp,
        .resonant_harmonic_order = MOTOR_Resonant_harmonic_order,
        .resonant_antiwindup_gain = MOTOR_Resonant_antiwindup_gain,
        .resonant_voltage_limit_V = MOTOR_Resonant_voltage_limit_V,
        .default_duty_cycle = {
            .DutyCycle_A = MOTOR_Default_duty_cycle,
            .DutyCycle_B = MOTOR_Default_duty_cycle,
            .DutyCycle_C = MOTOR_Default_duty_cycle,
        },
        .setpoint_limits = {
            .speed_controller_torque_in_Nm = {.upper_bound = MOTOR_Speed_controller_torque_max_Nm, .lower_bound = -MOTOR_Speed_controller_torque_max_Nm},
            .i_d_in_A = {.upper_bound = MOTOR_Control_current_max_A, .lower_bound = -MOTOR_Control_current_max_A},
            .i_q_in_A = {.upper_bound = MOTOR_Control_current_max_A, .lower_bound = -MOTOR_Control_current_max_A},
            .speed_in_rpm = {.upper_bound = MOTOR_Speed_max_rpm, .lower_bound = -MOTOR_Speed_max_rpm},
        },
        .safe_operating_region = {
            .speed_in_rpm = {.upper_bound = MOTOR_SOR_speed_upper_rpm, .lower_bound = MOTOR_SOR_speed_lower_rpm},
            .i_d_in_A = {.upper_bound = MOTOR_SOR_i_d_upper_A, .lower_bound = MOTOR_SOR_i_d_lower_A},
            .i_q_in_A = {.upper_bound = MOTOR_SOR_i_q_upper_A, .lower_bound = MOTOR_SOR_i_q_lower_A},
            .i_abc_in_A = {.upper_bound = MOTOR_SOR_i_abc_upper_A, .lower_bound = MOTOR_SOR_i_abc_lower_A},
            .v_dc_in_V = {.upper_bound = MOTOR_SOR_v_dc_upper_V, .lower_bound = MOTOR_SOR_v_dc_lower_V},
            .i_dc_in_A = {.upper_bound = MOTOR_SOR_i_dc_upper_A, .lower_bound = MOTOR_SOR_i_dc_lower_A},
        },
        .setpoint_filter_i_dq_cutoff_frequency = MOTOR_Setpoint_filter_i_dq_cutoff_Hz,
        .setpoint_filter_speed_cutoff_frequency = MOTOR_Setpoint_filter_speed_cutoff_Hz,
        .speed_actual_value_filter_cutoff_frequency = MOTOR_Speed_actual_filter_cutoff_Hz,
        .enable_speed_control = false,
        .enable_resonant_control = false,
        .observer = uz_im_control_observer_rotor_flux_model,
    };
    return setup;
}
