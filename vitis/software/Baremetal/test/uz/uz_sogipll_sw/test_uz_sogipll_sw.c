#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_sogipll_sw.h"
#include "uz_integrator.h"
#include "uz_Transformation.h"
#include "uz_signals.h"
#include "uz_piController.h"
#include "uz_global_configuration.h"
#include "export_struct_to_csv.h"
#include <math.h>

// Set to 1 to export the tracking test; create the output directory first.
#define CSV_EXPORT 0
#define TRACKING_SAMPLES 5000U

#if CSV_EXPORT
#define TRACKING_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_sogipll_sw/tracking_50_hz.csv"

static float tracking_inputs[TRACKING_SAMPLES];
struct tracking_output_t {
    struct uz_sogipll_sw_outputs_t estimated;
    float actual_omega_rad_per_s;
    float actual_theta_rad;
    float theta_error_rad;
};

static struct tracking_output_t tracking_outputs[TRACKING_SAMPLES];

static const struct csv_field_descriptor_t input_fields[] = {
    {"voltage_in_V", 0U, CSV_FIELD_FLOAT}
};

static const struct csv_field_descriptor_t output_fields[] = {
    {"voltage_estimate_in_pu", offsetof(struct tracking_output_t, estimated) + offsetof(struct uz_sogipll_sw_outputs_t, voltage_estimate), CSV_FIELD_FLOAT},
    {"quadrature_voltage_estimate_in_pu", offsetof(struct tracking_output_t, estimated) + offsetof(struct uz_sogipll_sw_outputs_t, quadrature_voltage_estimate), CSV_FIELD_FLOAT},
    {"voltage_d_in_pu", offsetof(struct tracking_output_t, estimated) + offsetof(struct uz_sogipll_sw_outputs_t, voltage_d), CSV_FIELD_FLOAT},
    {"voltage_q_in_pu", offsetof(struct tracking_output_t, estimated) + offsetof(struct uz_sogipll_sw_outputs_t, voltage_q), CSV_FIELD_FLOAT},
    {"theta_in_rad", offsetof(struct tracking_output_t, estimated) + offsetof(struct uz_sogipll_sw_outputs_t, theta_rad), CSV_FIELD_FLOAT},
    {"omega_in_rad_per_s", offsetof(struct tracking_output_t, estimated) + offsetof(struct uz_sogipll_sw_outputs_t, omega_rad_per_s), CSV_FIELD_FLOAT},
    {"actual_omega_in_rad_per_s", offsetof(struct tracking_output_t, actual_omega_rad_per_s), CSV_FIELD_FLOAT},
    {"actual_theta_in_rad", offsetof(struct tracking_output_t, actual_theta_rad), CSV_FIELD_FLOAT},
    {"theta_error_in_rad", offsetof(struct tracking_output_t, theta_error_rad), CSV_FIELD_FLOAT}
};
#endif

#define TEST_TWO_PI 6.2831853071795864769f

static struct uz_sogipll_sw_config_t config = {0};
static uint32_t allocated_instances = 0U;

static uz_sogipll_sw_t *successful_init(void);
static void check_voltage_output_rescaling(float voltage_scaling);

void setUp(void)
{
    config.sample_time_s = 0.0001f;
    config.omega_feedforward_rad_per_s = 2.0f;
    config.sogi_gain = 1.0f;
    config.proportional_gain = 0.0f;
    config.integral_gain = 0.0f;
    config.voltage_scaling = 2.0f;
    config.rescale_voltage_outputs = false;
}

void tearDown(void)
{
}

static uz_sogipll_sw_t *successful_init(void)
{
    uz_sogipll_sw_t *instance = uz_sogipll_sw_init(config);
    TEST_ASSERT_NOT_NULL(instance);
    allocated_instances++;
    return instance;
}

void test_uz_sogipll_sw_init_zero_states(void)
{
    uz_sogipll_sw_t *instance = successful_init();
    struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(instance, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.voltage_estimate);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.quadrature_voltage_estimate);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.voltage_d);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.voltage_q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.theta_rad);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, output.omega_rad_per_s);
}

void test_uz_sogipll_sw_phase_stays_in_range_over_multiple_turns(void)
{
    config.sample_time_s = 0.25f;
    config.omega_feedforward_rad_per_s = 80.0f;
    uz_sogipll_sw_t *instance = successful_init();
    for (uint32_t i = 0U; i < 100U; i++) {
        struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(instance, 0.0f);
        TEST_ASSERT_TRUE(output.theta_rad >= 0.0f);
        TEST_ASSERT_TRUE(output.theta_rad < TEST_TWO_PI);
        TEST_ASSERT_EQUAL_FLOAT(config.omega_feedforward_rad_per_s, output.omega_rad_per_s);
        TEST_ASSERT_EQUAL_FLOAT(0.0f, output.voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(0.0f, output.quadrature_voltage_estimate);
    }
}

void test_uz_sogipll_sw_phase_wraps_negative_frequency(void)
{
    config.sample_time_s = 0.25f;
    config.proportional_gain = 100.0f;
    uz_sogipll_sw_t *instance = successful_init();
    struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(instance, 1.0f);
    output = uz_sogipll_sw_sample(instance, 1.0f);
    TEST_ASSERT_TRUE(output.omega_rad_per_s < 0.0f);
    output = uz_sogipll_sw_sample(instance, 1.0f);
    TEST_ASSERT_TRUE(output.theta_rad >= 0.0f);
    TEST_ASSERT_TRUE(output.theta_rad < TEST_TWO_PI);
}

void test_uz_sogipll_sw_phase_wraps_exact_turn(void)
{
    config.omega_feedforward_rad_per_s = TEST_TWO_PI;
    config.sample_time_s = 1.0f;
    uz_sogipll_sw_t *instance = successful_init();
    struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(instance, 0.0f);
    output = uz_sogipll_sw_sample(instance, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.theta_rad);
}

void test_uz_sogipll_sw_negative_scaling_matches_inverted_input(void)
{
    uz_sogipll_sw_t *positive_scaling = successful_init();
    config.voltage_scaling = -config.voltage_scaling;
    uz_sogipll_sw_t *negative_scaling = successful_init();
    for (uint32_t i = 0U; i < 10U; i++) {
        struct uz_sogipll_sw_outputs_t expected = uz_sogipll_sw_sample(positive_scaling, -1.0f);
        struct uz_sogipll_sw_outputs_t actual = uz_sogipll_sw_sample(negative_scaling, 1.0f);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_estimate, actual.voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(expected.quadrature_voltage_estimate, actual.quadrature_voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_d, actual.voltage_d);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_q, actual.voltage_q);
        TEST_ASSERT_EQUAL_FLOAT(expected.theta_rad, actual.theta_rad);
        TEST_ASSERT_EQUAL_FLOAT(expected.omega_rad_per_s, actual.omega_rad_per_s);
    }
}

void test_uz_sogipll_sw_reset_behaves_like_fresh_instance(void)
{
    config.proportional_gain = 3.0f;
    config.integral_gain = 4.0f;
    uz_sogipll_sw_t *instance = successful_init();
    uz_sogipll_sw_t *fresh_instance = successful_init();
    for (uint32_t i = 0U; i < 3U; i++) {
        (void)uz_sogipll_sw_sample(instance, 1.0f);
    }
    uz_sogipll_sw_reset(instance);
    for (uint32_t i = 0U; i < 3U; i++) {
        struct uz_sogipll_sw_outputs_t expected = uz_sogipll_sw_sample(fresh_instance, 1.0f);
        struct uz_sogipll_sw_outputs_t actual = uz_sogipll_sw_sample(instance, 1.0f);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_estimate, actual.voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(expected.quadrature_voltage_estimate, actual.quadrature_voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_d, actual.voltage_d);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_q, actual.voltage_q);
        TEST_ASSERT_EQUAL_FLOAT(expected.theta_rad, actual.theta_rad);
        TEST_ASSERT_EQUAL_FLOAT(expected.omega_rad_per_s, actual.omega_rad_per_s);
    }
}

void test_uz_sogipll_sw_instances_are_independent(void)
{
    uz_sogipll_sw_t *first = successful_init();
    config.omega_feedforward_rad_per_s = 4.0f;
    uz_sogipll_sw_t *second = successful_init();
    TEST_ASSERT_NOT_EQUAL(first, second);
    struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(first, 1.0f);
    output = uz_sogipll_sw_sample(second, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.voltage_estimate);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, output.omega_rad_per_s);
    output = uz_sogipll_sw_sample(first, 1.0f);
    TEST_ASSERT_TRUE(output.voltage_estimate > 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, output.omega_rad_per_s);
}

void test_uz_sogipll_sw_tracks_50_hz_sine_from_49_hz_feedforward(void)
{
    config.sample_time_s = 0.0001f;
    config.omega_feedforward_rad_per_s = 49.0f * TEST_TWO_PI;
    config.sogi_gain = 1.41421356f;
    config.proportional_gain = 100.0f;
    config.integral_gain = 1000.0f;
    config.voltage_scaling = 0.0002f;
    uz_sogipll_sw_t *instance = successful_init();
    // Run for 0.5 s and check tracking throughout the final 50 Hz period.
    for (uint32_t i = 0U; i < TRACKING_SAMPLES; i++) {
        float time_s = (float)i * config.sample_time_s;
        float actual_omega_rad_per_s = 50.0f * TEST_TWO_PI;
        float signal_phase_rad = actual_omega_rad_per_s * time_s;
        float voltage_V = 5000.0f * sinf(signal_phase_rad);
        struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(instance, voltage_V);
#if CSV_EXPORT
        tracking_inputs[i] = voltage_V;
        tracking_outputs[i].estimated = output;
        tracking_outputs[i].actual_omega_rad_per_s = actual_omega_rad_per_s;
        // Park's direct axis uses cosine: sin(phi) = cos(phi - pi/2).
        float actual_theta_rad = uz_signals_wrap(signal_phase_rad - (0.25f * TEST_TWO_PI), TEST_TWO_PI);
        tracking_outputs[i].actual_theta_rad = actual_theta_rad;
        tracking_outputs[i].theta_error_rad = actual_theta_rad - output.theta_rad;
#endif
        TEST_ASSERT_TRUE(output.theta_rad >= 0.0f);
        TEST_ASSERT_TRUE(output.theta_rad < TEST_TWO_PI);
        if (i >= 4800U) {
            float frequency_Hz = output.omega_rad_per_s / TEST_TWO_PI;
            TEST_ASSERT_FLOAT_WITHIN(0.2f, 50.0f, frequency_Hz);
            TEST_ASSERT_FLOAT_WITHIN(0.05f, 1.0f, output.voltage_d);
            TEST_ASSERT_FLOAT_WITHIN(0.02f, 0.0f, output.voltage_q);
        }
    }
#if CSV_EXPORT
    export_input_output_arrays_to_csv(TRACKING_CSV_PATH,
        tracking_inputs, sizeof(tracking_inputs[0]), input_fields, sizeof(input_fields) / sizeof(input_fields[0]),
        tracking_outputs, sizeof(tracking_outputs[0]), output_fields, sizeof(output_fields) / sizeof(output_fields[0]),
        TRACKING_SAMPLES, config.sample_time_s);
#endif
}

static void check_voltage_output_rescaling(float voltage_scaling)
{
    config.voltage_scaling = voltage_scaling;
    config.proportional_gain = 3.0f;
    config.integral_gain = 4.0f;
    uz_sogipll_sw_t *normalized = successful_init();
    config.rescale_voltage_outputs = true;
    uz_sogipll_sw_t *rescaled = successful_init();
    for (uint32_t i = 0U; i < 100U; i++) {
        struct uz_sogipll_sw_outputs_t expected = uz_sogipll_sw_sample(normalized, 10.0f);
        struct uz_sogipll_sw_outputs_t actual = uz_sogipll_sw_sample(rescaled, 10.0f);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_estimate / voltage_scaling, actual.voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(expected.quadrature_voltage_estimate / voltage_scaling, actual.quadrature_voltage_estimate);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_d / voltage_scaling, actual.voltage_d);
        TEST_ASSERT_EQUAL_FLOAT(expected.voltage_q / voltage_scaling, actual.voltage_q);
        TEST_ASSERT_EQUAL_FLOAT(expected.theta_rad, actual.theta_rad);
        TEST_ASSERT_EQUAL_FLOAT(expected.omega_rad_per_s, actual.omega_rad_per_s);
        if (i == 49U) {
            uz_sogipll_sw_reset(normalized);
            uz_sogipll_sw_reset(rescaled);
        }
    }
}

void test_uz_sogipll_sw_rescales_all_voltage_outputs(void)
{
    check_voltage_output_rescaling(0.5f);
}

void test_uz_sogipll_sw_rescales_negative_voltage_scaling(void)
{
    check_voltage_output_rescaling(-0.5f);
}

void test_uz_sogipll_sw_quadrature_responds_with_in_phase_state(void)
{
    uz_sogipll_sw_t *instance = successful_init();
    (void)uz_sogipll_sw_sample(instance, 1.0f);
    struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(instance, 0.0f);
    TEST_ASSERT_TRUE(output.voltage_estimate > 0.0f);
    TEST_ASSERT_TRUE(output.quadrature_voltage_estimate > 0.0f);
}

void test_uz_sogipll_sw_init_with_zero_sample_time_s(void)
{
    config.sample_time_s = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_negative_sample_time_s(void)
{
    config.sample_time_s = -0.01f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_zero_omega_feedforward_rad_per_s(void)
{
    config.omega_feedforward_rad_per_s = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_negative_omega_feedforward_rad_per_s(void)
{
    config.omega_feedforward_rad_per_s = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_zero_sogi_gain(void)
{
    config.sogi_gain = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_negative_sogi_gain(void)
{
    config.sogi_gain = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_negative_proportional_gain(void)
{
    config.proportional_gain = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_negative_integral_gain(void)
{
    config.integral_gain = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_init_with_zero_voltage_scaling(void)
{
    config.voltage_scaling = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

void test_uz_sogipll_sw_sample_with_null_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_sample(NULL, 1.0f));
}

void test_uz_sogipll_sw_reset_with_null_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_reset(NULL));
}

// Last because the production allocator has no deallocation operation.
void test_uz_sogipll_sw_init_with_exhausted_pool(void)
{
    while (allocated_instances < UZ_SOGIPLL_SW_MAX_INSTANCES) {
        TEST_ASSERT_NOT_NULL(successful_init());
    }
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_sw_init(config));
}

#endif // TEST
