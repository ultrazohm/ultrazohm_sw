#ifdef TEST
#include <math.h>
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
    .u_f_ratio_V_per_Hz = 4.0f,
    .u_f_boost_voltage_V = 2.0f,
    .u_f_max_frequency_Hz = 50.0f,
    .u_f_max_voltage_V = 200.0f,
    .u_f_frequency_ramp_Hz_per_s = 10.0f,
    .kalman_process_noise_A2_per_s = 0.1f,
    .kalman_measurement_noise_A2 = 0.05f,
    .minimum_observer_flux_Vs = 0.01f,
    .maximum_slip_frequency_Hz = 5.0f,
    .maximum_flux_angle_step_rad = 0.25f,
    .maximum_phase_current_sum_A = 1.0f,
    .resonant_gain_d = 0.1f,
    .resonant_gain_q = 0.1f,
    .resonant_harmonic_order = 6.0f,
    .resonant_antiwindup_gain = 1.0f,
    .resonant_voltage_limit_V = 20.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f},
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 20.0f, .lower_bound = -20.0f},
        .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .speed_in_rpm = {.upper_bound = 2500.0f, .lower_bound = -2500.0f}},
    .safe_operating_region = {
        .speed_in_rpm = {.upper_bound = 3000.0f, .lower_bound = -3000.0f},
        .i_d_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
        .i_q_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
        .i_abc_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
        .v_dc_in_V = {.upper_bound = 400.0f, .lower_bound = 10.0f},
        .i_dc_in_A = {.upper_bound = 20.0f, .lower_bound = -20.0f}},
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.0f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .enable_speed_control = true,
    .enable_resonant_control = false,
    .enable_voltage_vector_limiting = true,
    .observer = uz_im_control_observer_kalman_rotor_flux_model
};

void setUp(void) {}
void tearDown(void) {}

void test_uz_im_control_init(void) {
    TEST_ASSERT_NOT_NULL(uz_im_control_init(control_config, machine_config));
}

void test_uz_im_control_rejects_reversed_setpoint_limit(void) {
    struct uz_im_control_configuration_t invalid = control_config;
    invalid.setpoint_limits.i_q_in_A.lower_bound = invalid.setpoint_limits.i_q_in_A.upper_bound + 1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_im_control_init(invalid, machine_config));
}

void test_uz_im_control_rejects_negative_filter_frequency(void) {
    struct uz_im_control_configuration_t invalid = control_config;
    invalid.setpoint_filter_speed_cutoff_frequency = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_im_control_init(invalid, machine_config));
}

void test_uz_im_control_limits_current_and_speed_references(void) {
    struct uz_im_control_configuration_t config = control_config;
    config.enable_speed_control = false;
    uz_im_control_t *self = uz_im_control_init(config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values measurements = {.v_dc_V = 100.0f};
    uz_im_control_sample_dq(self, measurements, 4000.0f, (uz_3ph_dq_t){.d = 8.0f, .q = -8.0f});
    const struct uz_im_reference_values *references = uz_im_control_get_reference_values(self);
    TEST_ASSERT_EQUAL_FLOAT(2500.0f, references->speed_rpm);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, references->i_dq_A.d);
    TEST_ASSERT_EQUAL_FLOAT(-5.0f, references->i_dq_A.q);
}

void test_uz_im_control_filters_setpoints_and_measured_speed(void) {
    struct uz_im_control_configuration_t config = control_config;
    config.enable_speed_control = false;
    config.setpoint_filter_i_dq_cutoff_frequency = 100.0f;
    config.setpoint_filter_speed_cutoff_frequency = 100.0f;
    config.speed_actual_value_filter_cutoff_frequency = 100.0f;
    uz_im_control_t *self = uz_im_control_init(config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values measurements = {.v_dc_V = 100.0f, .rotor_speed_rpm = 1000.0f};
    uz_im_control_sample_dq(self, measurements, 1000.0f, (uz_3ph_dq_t){.d = 4.0f, .q = 4.0f});
    const struct uz_im_reference_values *references = uz_im_control_get_reference_values(self);
    const struct uz_im_measurement_values *filtered_measurements = uz_im_control_get_im_measurement_values(self);
    TEST_ASSERT_TRUE((references->speed_rpm > 0.0f) && (references->speed_rpm < 1000.0f));
    TEST_ASSERT_TRUE((references->i_dq_A.d > 0.0f) && (references->i_dq_A.d < 4.0f));
    TEST_ASSERT_TRUE((references->i_dq_A.q > 0.0f) && (references->i_dq_A.q < 4.0f));
    TEST_ASSERT_TRUE((filtered_measurements->rotor_speed_rpm > 0.0f) && (filtered_measurements->rotor_speed_rpm < 1000.0f));
}

void test_uz_im_control_initializes_and_enables_resonant_control(void) {
    struct uz_im_control_configuration_t config = control_config;
    config.enable_speed_control = false;
    config.enable_resonant_control = true;
    config.current_controller_d_kp = 1000.0f;
    config.current_controller_q_kp = 1000.0f;
    config.minimum_observer_flux_Vs = 1.0e-7f;
    uz_im_control_t *self = uz_im_control_init(config, machine_config);
    uz_im_control_set_mode(self, uz_im_control_mode_u_f);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values measurements = {
        .v_dc_V = 100.0f,
        .i_abc_A = {.a = 1.0f, .b = -0.5f, .c = -0.5f},
    };
    uz_im_control_sample_duty(self, measurements, 0.0f, (uz_3ph_dq_t){0}, 10.0f);
    float const flux_before = uz_im_control_get_actual_data(self)->rotor_flux_magnitude_Vs;
    uz_im_control_set_mode(self, uz_im_control_mode_foc);
    TEST_ASSERT_EQUAL_FLOAT(flux_before, uz_im_control_get_actual_data(self)->rotor_flux_magnitude_Vs);
    uz_3ph_dq_t const voltage = uz_im_control_sample_dq(self, measurements, 0.0f,
        (uz_3ph_dq_t){.d = 10.0f, .q = 10.0f});
    const struct uz_im_actual_data *actual = uz_im_control_get_actual_data(self);
    TEST_ASSERT_TRUE(isfinite(actual->resonant_voltage_dq_V.d));
    TEST_ASSERT_TRUE(isfinite(actual->resonant_voltage_dq_V.q));
    TEST_ASSERT_TRUE(hypotf(voltage.d, voltage.q) <= (100.0f / sqrtf(3.0f)) + 1.0e-4f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual->voltage_vector_saturated);
    uz_im_control_enable_resonant_control(self, false);
}

void test_uz_im_control_disabled_returns_default_duty(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    struct uz_im_measurement_values m = {.v_dc_V = 100.0f};
    struct uz_DutyCycle_t duty = uz_im_control_sample_duty(self, m, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_C);
    uz_im_control_enable(self, true);
    uz_im_control_sample_dq(self, m, 0.0f, (uz_3ph_dq_t){.d = 1.0f, .q = 2.0f});
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_im_control_get_reference_values(self)->i_dq_A.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_im_control_get_actual_data(self)->rotor_flux_valid);
    m.i_abc_A = (uz_3ph_abc_t){.a = 1.0f, .b = 1.0f, .c = 1.0f};
    uz_im_control_sample_dq(self, m, 0.0f, (uz_3ph_dq_t){0});
    TEST_ASSERT_EQUAL_FLOAT(1.0f, uz_im_control_get_actual_data(self)->phase_current_sum_violation);
}

void test_uz_im_control_detects_dc_link_violation(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values m = {.v_dc_V = 500.0f};
    uz_im_control_sample_duty(self, m, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    TEST_ASSERT_EQUAL(uz_im_control_dc_overvoltage, uz_im_control_get_safe_operating_area_violation(self));
    TEST_ASSERT_EQUAL_UINT32(3U, uz_im_control_get_actual_data(self)->safe_operating_region_status);
}

void test_uz_im_control_sor_code_decodes_overspeed(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values measurements = {.v_dc_V = 100.0f, .rotor_speed_rpm = 3100.0f};
    uz_im_control_sample_duty(self, measurements, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    TEST_ASSERT_EQUAL(uz_im_control_overspeed, uz_im_control_get_safe_operating_area_violation(self));
    TEST_ASSERT_EQUAL_UINT32(2U, uz_im_control_get_actual_data(self)->safe_operating_region_status);
}

void test_uz_im_control_sor_code_decodes_dc_undervoltage(void) {
    uz_im_control_t *self = uz_im_control_init(control_config, machine_config);
    uz_im_control_enable(self, true);
    struct uz_im_measurement_values measurements = {.v_dc_V = 5.0f};
    uz_im_control_sample_duty(self, measurements, 0.0f, (uz_3ph_dq_t){0}, 0.0f);
    TEST_ASSERT_EQUAL(uz_im_control_dc_undervoltage, uz_im_control_get_safe_operating_area_violation(self));
    TEST_ASSERT_EQUAL_UINT32(4U, uz_im_control_get_actual_data(self)->safe_operating_region_status);
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
