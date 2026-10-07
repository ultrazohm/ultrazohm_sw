#ifdef TEST
#include <math.h>
#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_im_observer.h"
TEST_SOURCE_FILE("uz_IM_config.c")
TEST_SOURCE_FILE("uz_signals.c")
TEST_SOURCE_FILE("uz_pos_to_speed_pll.c")
TEST_SOURCE_FILE("uz_codegen_pos_to_speed_pll.c")
TEST_SOURCE_FILE("uz_Transformation.c")

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


static struct uz_im_observer_config config = {
    .sample_time_s = 0.0001f,
    .kalman_process_noise_A2_per_s = 0.1f,
    .kalman_measurement_noise_A2 = 0.05f,
    .kalman_flux_process_noise_Vs2_per_s = 1.0e-3f,
    .minimum_observer_flux_Vs = 0.01f,
    .maximum_flux_angle_step_rad = 0.25f,
    .maximum_phase_current_sum_A = 1.0f,
    .maximum_slip_frequency_Hz = 5.0f,
    .observer_pll_kp = 628.3185f,
    .observer_pll_ki = 98696.0f,
    .observer = uz_im_control_observer_kalman_rotor_flux_model
};
static struct uz_im_observer_input input = {
    .i_abc_A = {.a = 1.0f, .b = -0.5f, .c = -0.5f}
};
void setUp(void) {}
void tearDown(void) {}

void test_uz_im_observer_tustin_first_step_matches_analytic_solution(void) {
    struct uz_im_observer_config c = config;
    c.observer = uz_im_control_observer_rotor_flux_model;
    uz_im_observer_t *self = uz_im_observer_init(c, machine_config);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    float inverse_tau = machine_config.Rr_Ohm / uz_IM_config_get_Lr(machine_config);
    float expected = c.sample_time_s * machine_config.Lm_Henry * inverse_tau
        / (1.0f + 0.5f * c.sample_time_s * inverse_tau);
    const struct uz_im_observer_diagnostics_t *d = uz_im_observer_get_diagnostics(self);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-8f, expected, d->deterministic_flux_alpha_Vs);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-8f, 0.0f, d->deterministic_flux_beta_Vs);
}

void test_uz_im_observer_scalar_kalman_uses_noise_times_sample_time(void) {
    struct uz_im_observer_config c = config;
    c.observer = uz_im_control_observer_filtered_rotor_flux_model;
    uz_im_observer_t *self = uz_im_observer_init(c, machine_config);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    float p = 1.0f + c.kalman_process_noise_A2_per_s * c.sample_time_s;
    float gain = p / (p + c.kalman_measurement_noise_A2);
    const struct uz_im_observer_diagnostics_t *d = uz_im_observer_get_diagnostics(self);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-6f, gain, d->simplified_current_alpha_A);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-6f, p * (1.0f - gain), d->simplified_current_covariance_alpha_A2);
}

void test_uz_im_observer_voltage_is_consumed_without_an_extra_delay(void) {
    uz_im_observer_t *self = uz_im_observer_init(config, machine_config);
    struct uz_im_observer_input in = {.v_abc_V = {.a = 10.0f, .b = -5.0f, .c = -5.0f}};
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, in));
    const struct uz_im_observer_diagnostics_t *d = uz_im_observer_get_diagnostics(self);
    TEST_ASSERT_TRUE(d->innovation[0] < 0.0f);
    TEST_ASSERT_TRUE(d->state[0] > 0.0f);
    TEST_ASSERT_TRUE(d->innovation_covariance[0][0] > 0.0f);
}

void test_uz_im_observer_same_selection_retains_state_and_switch_resets(void) {
    uz_im_observer_t *self = uz_im_observer_init(config, machine_config);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    float state = uz_im_observer_get_diagnostics(self)->state[0];
    TEST_ASSERT_TRUE(state > 0.0f);
    uz_im_observer_set_mode(self, config.observer);
    TEST_ASSERT_EQUAL_FLOAT(state, uz_im_observer_get_diagnostics(self)->state[0]);
    uz_im_observer_set_mode(self, uz_im_control_observer_filtered_rotor_flux_model);
    const struct uz_im_observer_diagnostics_t *d = uz_im_observer_get_diagnostics(self);
    for (unsigned i = 0; i < 4; ++i) {
        TEST_ASSERT_EQUAL_FLOAT(0.0f, d->state[i]);
        for (unsigned j = 0; j < 4; ++j) TEST_ASSERT_EQUAL_FLOAT(i == j ? 1.0f : 0.0f, d->covariance[i][j]);
    }
    TEST_ASSERT_EQUAL_FLOAT(1.0f, d->simplified_current_covariance_alpha_A2);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_im_observer_get_output(self)->rotor_flux_valid);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    float filtered = d->simplified_current_alpha_A;
    uz_im_observer_reset(self);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    TEST_ASSERT_EQUAL_FLOAT(filtered, d->simplified_current_alpha_A);
}

void test_uz_im_observer_numerical_failure_reports_false_and_reset_recovers(void) {
    uz_im_observer_t *self = uz_im_observer_init(config, machine_config);
    struct uz_im_observer_input invalid = input;
    invalid.rotor_speed_rpm = NAN;
    TEST_ASSERT_FALSE(uz_im_observer_sample(self, invalid));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_im_observer_get_output(self)->rotor_flux_valid);
    uz_im_observer_reset(self);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    TEST_ASSERT_TRUE(isfinite(uz_im_observer_get_diagnostics(self)->state[0]));
}

void test_uz_im_observer_runtime_settings_preserve_states_and_validate(void) {
    uz_im_observer_t *self = uz_im_observer_init(config, machine_config);
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    float state = uz_im_observer_get_diagnostics(self)->state[0];
    uz_im_observer_set_process_noise(self, 0.2f);
    uz_im_observer_set_measurement_noise(self, 0.1f);
    uz_im_observer_set_minimum_flux(self, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(state, uz_im_observer_get_diagnostics(self)->state[0]);
    TEST_ASSERT_FAIL_ASSERT(uz_im_observer_set_process_noise(self, -1.0f));
    TEST_ASSERT_FAIL_ASSERT(uz_im_observer_set_measurement_noise(self, 0.0f));
    TEST_ASSERT_FAIL_ASSERT(uz_im_observer_set_minimum_flux(self, 0.0f));
    TEST_ASSERT_TRUE(uz_im_observer_sample(self, input));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_im_observer_get_output(self)->rotor_flux_valid);
}
#endif

