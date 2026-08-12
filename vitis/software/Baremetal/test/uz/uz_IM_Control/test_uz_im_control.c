#ifdef TEST
#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_im_control.h"

static uz_IM_t machine_config = {
    .Rs_Ohm = 2.0f,
    .Rr_Ohm = 1.5f,
    .Lsigma_s_Henry = 0.01f,
    .Lsigma_r_Henry = 0.01f,
    .Lm_Henry = 0.2f,
    .polePairs = 2.0f,
    .J_kg_m_squared = 0.01f,
    .I_max_Ampere = 10.0f,
    .Psi_rated_Vs = 0.5f
};

static struct uz_im_control_configuration_t control_config = {
    .sample_time_s = 0.0001f,
    .current_controller_d_kp = 1.0f,
    .current_controller_d_ki = 10.0f,
    .current_controller_q_kp = 1.0f,
    .current_controller_q_ki = 10.0f,
    .speed_controller_kp = 0.1f,
    .speed_controller_ki = 1.0f,
    .speed_controller_iq_limit_A = 5.0f,
    .u_f_ratio_V_per_Hz = 4.0f,
    .u_f_boost_voltage_V = 2.0f,
    .u_f_max_frequency_Hz = 50.0f,
    .u_f_max_voltage_V = 200.0f,
    .u_f_frequency_ramp_Hz_per_s = 10.0f,
    .kalman_process_noise_A2_per_s = 0.1f,
    .kalman_measurement_noise_A2 = 0.05f,
    .minimum_observer_flux_Vs = 0.01f,
    .default_duty_cycle = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f},
    .safe_operating_region = {.speed_abs_max_rpm = 3000.0f, .phase_current_abs_max_A = 10.0f, .dc_link_voltage_min_V = 10.0f, .dc_link_voltage_max_V = 400.0f},
    .enable_speed_control = true,
    .observer = uz_im_control_observer_kalman_rotor_flux_model
};

void setUp(void) {}
void tearDown(void) {}

void test_uz_im_control_init(void) {
    TEST_ASSERT_NOT_NULL(uz_im_control_init(control_config, machine_config));
}

void test_uz_im_control_disabled_returns_default_duty(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    struct uz_im_measurement_values m = {.v_dc_V = 100.0f};
    struct uz_DutyCycle_t duty = uz_im_control_sample_duty(self, m, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_C);
}

void test_uz_im_control_detects_dc_link_violation(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values m = {.v_dc_V = 500.0f};
    uz_im_control_sample_duty(self, m, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    TEST_ASSERT_EQUAL(uz_im_control_dc_link_voltage_violation, uz_im_control_get_safe_operating_area_violation(self));
}

void test_uz_im_control_u_f_ramps_frequency(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    uz_im_control_set_mode(self, uz_im_control_mode_u_f);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values m = {.v_dc_V = 100.0f};
    uz_im_control_sample_duty(self, m, 0.0f, (uz_3ph_dq_t){0}, 20.0f);
    TEST_ASSERT_TRUE(uz_im_control_get_actual_data(self)->u_f_applied_voltage_V > 0.0f);
}

void test_uz_im_control_actual_frequency_units_are_consistent(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values measurements = {
        .v_dc_V = 100.0f,
        .rotor_speed_rpm = 600.0f,
        .rotor_mechanical_angle_rad = 0.25f
    };
    uz_im_control_sample_duty(self, measurements, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    const struct uz_im_actual_data *actual = uz_im_control_get_actual_data(self);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-5f, actual->rotor_electrical_angular_speed_rad_per_s / (2.0f * 3.14159265358979323846f), actual->rotor_electrical_frequency_Hz);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-5f, actual->slip_angular_frequency_rad_per_s / (2.0f * 3.14159265358979323846f), actual->slip_frequency_Hz);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-5f, actual->stator_angular_frequency_rad_per_s / (2.0f * 3.14159265358979323846f), actual->stator_frequency_Hz);
}
#endif
