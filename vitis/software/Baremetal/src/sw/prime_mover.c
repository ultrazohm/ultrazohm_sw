#include "../include/prime_mover.h"

/* Separate prime-mover machine configuration: same machine type as the DUT. Limits are commissioning defaults;
 * validate them against the machine/inverter before using physical hardware.
 */
static const uz_PMSM_t prime_mover_machine_data = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.00175f,
    .Lq_Henry = 0.00175f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 12.0f
};

uz_pmsm_control_t* initialize_prime_mover(float sample_time_s)
{
    struct uz_pmsm_control_configuration_t config = {
        .sample_time = sample_time_s,
        .enable_speed_control = true,
        // Selected PLL-feedback gains after frequency-response and load-step evaluation.
        // Units: Nm/(rad/s) and Nm/rad.
        .speed_controller_kp = 0.06f,
        .speed_controller_ki = 1.5f,
        .setpoint_limits = {
            .speed_controller_torque_in_Nm = {.lower_bound = -2.5f, .upper_bound = 2.5f},
            .i_d_in_A = {.lower_bound = -12.0f, .upper_bound = 12.0f},
            .i_q_in_A = {.lower_bound = -12.0f, .upper_bound = 12.0f},
            .speed_in_rpm = {.lower_bound = -1100.0f, .upper_bound = 1100.0f},
            .disturbance_input_in_Nm = {.lower_bound = -2.5f, .upper_bound = 2.5f}
        },
        .safe_operating_region = {
            .speed_in_rpm = {.lower_bound = -3000.0f, .upper_bound = 3000.0f},
            .i_d_in_A = {.lower_bound = -15.0f, .upper_bound = 15.0f},
            .i_q_in_A = {.lower_bound = -15.0f, .upper_bound = 15.0f},
            .i_abc_in_A = {.lower_bound = -15.0f, .upper_bound = 15.0f},
            .v_dc_in_V = {.lower_bound = 12.0f, .upper_bound = 60.0f},
            .i_dc_in_A = {.lower_bound = -10.0f, .upper_bound = 10.0f}
        },
        .decoupling_method = linear_decoupling,
        .motor_type = SMPMSM,
        .enable_field_weakening = false,
        .relative_torque_tolerance = 0.01f,
        // One control period for the update delay plus half a period for the PWM hold.
        .theta_svm_delay_compensation = 1.5f,
        // Filters, controller angle offset and sampling compensation remain zero.
        // Resolver alignment is configured separately in the D5 adapter initialization.
        .default_duty_cycle = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f}
    };
    uz_pmsm_control_t* prime_mover = uz_pmsm_control_init(config, prime_mover_machine_data);
    /* Initial 1000 rad/s bandwidth (~159 Hz), allowing for the ISR command delay.
     * Validate the response on target before increasing bandwidth.
     */
    uz_pmsm_control_current_control_tune_bandwidth(prime_mover, 5026.5f);
    return prime_mover;
}
