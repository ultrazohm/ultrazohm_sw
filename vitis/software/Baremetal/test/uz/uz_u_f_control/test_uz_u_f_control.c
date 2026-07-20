#ifdef TEST

#include "unity.h"
#include "uz_u_f_control.h"
#include "uz_math_constants.h"
#include "test_assert_with_exception.h"
#include "mock_uz_space_vector_modulation.h"

static struct uz_u_f_control_config_t config;

static struct uz_DutyCycle_t neutral_duty(void)
{
    return (struct uz_DutyCycle_t){.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f};
}

void setUp(void)
{
    config = (struct uz_u_f_control_config_t){
        .frequency_setpoint_Hz = 10.0f,
        .max_frequency_Hz = 50.0f,
        .frequency_ramp_Hz_per_s = 100.0f,
        .ratio_V_per_Hz = 2.0f,
        .boost_voltage_V = 1.0f,
        .max_voltage_V = 100.0f,
        .minimum_pulse_width = 0.05f,
        .dc_link_voltage_lower_bound_V = 10.0f,
        .dc_link_voltage_upper_bound_V = 450.0f,
        .default_duty_cycle = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f}};
}

void tearDown(void) {}

void test_uz_u_f_control_init_and_get_data(void)
{
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    const struct uz_u_f_control_data_t *data = uz_u_f_control_get_data(self);
    TEST_ASSERT_NOT_NULL(self);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, data->frequency_command_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, data->electrical_phase_rad);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, data->applied_voltage_magnitude_V);
}

void test_uz_u_f_control_ramps_frequency_and_applies_characteristic(void)
{
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(neutral_duty());
    (void)uz_u_f_control_sample(self, 400.0f, 0.01f);
    const struct uz_u_f_control_data_t *data = uz_u_f_control_get_data(self);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data->frequency_command_Hz);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data->applied_voltage_magnitude_V);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-6f, 0.02f * UZ_PIf, data->electrical_phase_rad);
}

void test_uz_u_f_control_limits_frequency_and_voltage(void)
{
    config.frequency_setpoint_Hz = 100.0f;
    config.frequency_ramp_Hz_per_s = 1000.0f;
    config.ratio_V_per_Hz = 10.0f;
    config.max_voltage_V = 20.0f;
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(neutral_duty());
    (void)uz_u_f_control_sample(self, 400.0f, 1.0f);
    const struct uz_u_f_control_data_t *data = uz_u_f_control_get_data(self);
    TEST_ASSERT_EQUAL_FLOAT(50.0f, data->frequency_command_Hz);
    TEST_ASSERT_EQUAL_FLOAT(20.0f, data->applied_voltage_magnitude_V);
}

void test_uz_u_f_control_setpoint_can_ramp_down(void)
{
    config.frequency_ramp_Hz_per_s = 10.0f;
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(neutral_duty());
    (void)uz_u_f_control_sample(self, 400.0f, 1.0f);
    uz_u_f_control_set_frequency(self, 0.0f);
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(neutral_duty());
    (void)uz_u_f_control_sample(self, 400.0f, 0.25f);
    TEST_ASSERT_EQUAL_FLOAT(7.5f, uz_u_f_control_get_data(self)->frequency_command_Hz);
}

void test_uz_u_f_control_zero_frequency_has_no_boost(void)
{
    config.frequency_setpoint_Hz = 0.0f;
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(neutral_duty());
    struct uz_DutyCycle_t duty = uz_u_f_control_sample(self, 24.0f, 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_u_f_control_get_data(self)->applied_voltage_magnitude_V);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_C);
}

void test_uz_u_f_control_reset_clears_state(void)
{
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(neutral_duty());
    (void)uz_u_f_control_sample(self, 400.0f, 0.1f);
    uz_u_f_control_reset(self);
    const struct uz_u_f_control_data_t *data = uz_u_f_control_get_data(self);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, data->frequency_command_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, data->electrical_phase_rad);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, data->applied_voltage_magnitude_V);
}

void test_uz_u_f_control_rejects_invalid_minimum_pulse_width(void)
{
    config.minimum_pulse_width = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_u_f_control_init(config));
}

void test_uz_u_f_control_latches_dc_link_undervoltage(void)
{
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    struct uz_DutyCycle_t duty = uz_u_f_control_sample(self, 9.0f, 0.001f);
    TEST_ASSERT_EQUAL(uz_u_f_control_dc_link_voltage_violation_lower, uz_u_f_control_get_safe_operating_area_violation(self));
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_A);

    duty = uz_u_f_control_sample(self, 400.0f, 0.001f);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_A);
    TEST_ASSERT_EQUAL(uz_u_f_control_dc_link_voltage_violation_lower, uz_u_f_control_get_safe_operating_area_violation(self));
}

void test_uz_u_f_control_acknowledges_fault_only_with_valid_voltage(void)
{
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    (void)uz_u_f_control_sample(self, 500.0f, 0.001f);
    uz_u_f_control_acknowledge_and_reset_error(self, 500.0f);
    TEST_ASSERT_EQUAL(uz_u_f_control_dc_link_voltage_violation_upper, uz_u_f_control_get_safe_operating_area_violation(self));
    uz_u_f_control_acknowledge_and_reset_error(self, 400.0f);
    TEST_ASSERT_EQUAL(uz_u_f_control_no_violation, uz_u_f_control_get_safe_operating_area_violation(self));
}

void test_uz_u_f_control_replaces_invalid_svm_duty_with_safe_default(void)
{
    uz_u_f_control_t *self = uz_u_f_control_init(config);
    struct uz_DutyCycle_t invalid_duty = {.DutyCycle_A = 0.96f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f};
    uz_Space_Vector_Modulation_ExpectAnyArgsAndReturn(invalid_duty);
    struct uz_DutyCycle_t duty = uz_u_f_control_sample(self, 400.0f, 0.001f);
    TEST_ASSERT_EQUAL(uz_u_f_control_duty_cycle_violation_upper, uz_u_f_control_get_safe_operating_area_violation(self));
    TEST_ASSERT_EQUAL_FLOAT(0.5f, duty.DutyCycle_A);
}

#endif
