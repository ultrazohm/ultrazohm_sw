#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "uz_Transformation.h"
#include "test_assert_with_exception.h"

TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen.c")
TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen_sine.c")
TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen_sawtooth.c")
TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen_pulse.c")
TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen_square.c")
TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen_triangle.c")
TEST_SOURCE_FILE("src/uz/uz_wavegen/uz_wavegen_three_phase.c")

void setUp(void) { }
void tearDown(void) { }

/* ------------------------------- sine ---------------------------------- */

void test_uz_wavegen_sine_negative_input_frequency(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_sample(inst, 1.0f, -10.0f));
}

void test_uz_wavegen_sine_zero_input_frequency(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_sample(inst, 1.0f, 0.0f));
}

void test_uz_wavegen_sine_zero_input_amplitude(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_sample(inst, 0.0f, 5.0f));
}

void test_uz_wavegen_sine_output(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_sine_sample(inst, amplitude, frequency_Hz);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(50000U);
    float output = uz_wavegen_sine_sample(inst, amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output);
}

void test_uz_wavegen_sine_output_after_long_uptime_uses_microsecond_delta(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(5345782500ULL);
    (void)uz_wavegen_sine_sample(inst, 1.0f, 10.0f);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(5345782600ULL);
    float output = uz_wavegen_sine_sample(inst, 1.0f, 10.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 0.00628314f, output);
}

void test_uz_wavegen_sine_offset_negative_input_frequency(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_sample_with_offset(inst, 1.0f, -10.0f, 0.0f));
}

void test_uz_wavegen_sine_offset_zero_input_frequency(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_sample_with_offset(inst, 1.0f, 0.0f, 0.0f));
}

void test_uz_wavegen_sine_offset_zero_input_amplitude(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_sample_with_offset(inst, 0.0f, 5.0f, 2.0f));
}

void test_uz_wavegen_sine_offset_output(void) {
    uz_wavegen_sine_t* inst = uz_wavegen_sine_init();
    float amplitude = -5.0f;
    float frequency_Hz = 5.0f;
    float offset = 1.0f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_sine_sample_with_offset(inst, amplitude, frequency_Hz, offset);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(50000U);
    float output = uz_wavegen_sine_sample_with_offset(inst, amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(amplitude + offset, output);
}

/* ----------------------------- sawtooth -------------------------------- */

void test_uz_wavegen_sawtooth_negative_input_frequency(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_sample(inst, 1.0f, -10.0f));
}

void test_uz_wavegen_sawtooth_zero_input_frequency(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_sample(inst, 1.0f, 0.0f));
}

void test_uz_wavegen_sawtooth_zero_input_amplitude(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_sample(inst, 0.0f, 5.0f));
}

void test_uz_wavegen_sawtooth_output(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_sawtooth_sample(inst, amplitude, frequency_Hz);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(100000U);
    float output = uz_wavegen_sawtooth_sample(inst, amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.5f * amplitude, output);
}

void test_uz_wavegen_sawtooth_offset_negative_input_frequency(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_sample_with_offset(inst, 1.0f, -10.0f, 0.0f));
}

void test_uz_wavegen_sawtooth_offset_zero_input_frequency(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_sample_with_offset(inst, 1.0f, 0.0f, 0.0f));
}

void test_uz_wavegen_sawtooth_offset_zero_input_amplitude(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_sample_with_offset(inst, 0.0f, 5.0f, 0.0f));
}

void test_uz_wavegen_sawtooth_offset_output(void) {
    uz_wavegen_sawtooth_t* inst = uz_wavegen_sawtooth_init();
    float amplitude = -5.0f;
    float frequency_Hz = 10.0f;
    float offset = 1.0f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_sawtooth_sample_with_offset(inst, amplitude, frequency_Hz, offset);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(50000U);
    float output = uz_wavegen_sawtooth_sample_with_offset(inst, amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(0.5f * amplitude + offset, output);
}

/* ------------------------------- pulse --------------------------------- */

void test_uz_wavegen_pulse_negative_input_frequency(void) {
    uz_wavegen_pulse_t* inst = uz_wavegen_pulse_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse_sample(inst, 1.0f, -10.0f, 0.5f));
}

void test_uz_wavegen_pulse_zero_input_frequency(void) {
    uz_wavegen_pulse_t* inst = uz_wavegen_pulse_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse_sample(inst, 1.0f, 0.0f, 0.5f));
}

void test_uz_wavegen_pulse_negative_DutyCycle(void) {
    uz_wavegen_pulse_t* inst = uz_wavegen_pulse_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse_sample(inst, 1.0f, 10.0f, -0.5f));
}

void test_uz_wavegen_pulse_too_high_DutyCycle(void) {
    uz_wavegen_pulse_t* inst = uz_wavegen_pulse_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse_sample(inst, 1.0f, 10.0f, 2.0f));
}

void test_uz_wavegen_pulse_zero_input_amplitude(void) {
    uz_wavegen_pulse_t* inst = uz_wavegen_pulse_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse_sample(inst, 0.0f, 5.0f, 0.5f));
}

void test_uz_wavegen_pulse_output(void) {
    uz_wavegen_pulse_t* inst = uz_wavegen_pulse_init();
    float amplitude = 8.0f;
    float frequency_Hz = 10.0f;
    float duty_cycle = 0.5f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_pulse_sample(inst, amplitude, frequency_Hz, duty_cycle);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(40000U);
    float output = uz_wavegen_pulse_sample(inst, amplitude, frequency_Hz, duty_cycle);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output);
}

/* ------------------------------- square -------------------------------- */

void test_uz_wavegen_square_negative_input_frequency(void) {
    uz_wavegen_square_t* inst = uz_wavegen_square_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square_sample(inst, 1.0f, -10.0f, 0.5f));
}

void test_uz_wavegen_square_negative_DutyCycle(void) {
    uz_wavegen_square_t* inst = uz_wavegen_square_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square_sample(inst, 1.0f, 10.0f, -0.5f));
}

void test_uz_wavegen_square_too_high_DutyCycle(void) {
    uz_wavegen_square_t* inst = uz_wavegen_square_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square_sample(inst, 1.0f, 10.0f, 2.0f));
}

void test_uz_wavegen_square_zero_input_frequency(void) {
    uz_wavegen_square_t* inst = uz_wavegen_square_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square_sample(inst, 1.0f, 0.0f, 0.5f));
}

void test_uz_wavegen_square_output(void) {
    uz_wavegen_square_t* inst = uz_wavegen_square_init();
    float amplitude = 6.0f;
    float frequency_Hz = 20.0f;
    float duty_cycle = 0.5f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_square_sample(inst, amplitude, frequency_Hz, duty_cycle);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(20000U);
    float output = uz_wavegen_square_sample(inst, amplitude, frequency_Hz, duty_cycle);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output);
}

/* ------------------------------ triangle ------------------------------- */

void test_uz_wavegen_triangle_negative_input_frequency(void) {
    uz_wavegen_triangle_t* inst = uz_wavegen_triangle_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_sample(inst, 1.0f, -10.0f));
}

void test_uz_wavegen_triangle_zero_input_frequency(void) {
    uz_wavegen_triangle_t* inst = uz_wavegen_triangle_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_sample(inst, 1.0f, 0.0f));
}

void test_uz_wavegen_triangle_output(void) {
    uz_wavegen_triangle_t* inst = uz_wavegen_triangle_init();
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_triangle_sample(inst, amplitude, frequency_Hz);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(25000U);
    float output = uz_wavegen_triangle_sample(inst, amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.25f * amplitude, output);
}

void test_uz_wavegen_triangle_offset_negative_input_frequency(void) {
    uz_wavegen_triangle_t* inst = uz_wavegen_triangle_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_sample_with_offset(inst, 1.0f, -10.0f, 1.0f));
}

void test_uz_wavegen_triangle_offset_zero_input_frequency(void) {
    uz_wavegen_triangle_t* inst = uz_wavegen_triangle_init();
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_sample_with_offset(inst, 1.0f, 0.0f, 1.0f));
}

void test_uz_wavegen_triangle_offset_output(void) {
    uz_wavegen_triangle_t* inst = uz_wavegen_triangle_init();
    float amplitude = 6.0f;
    float frequency_Hz = 5.0f;
    float offset = -5.0f;
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(0U);
    (void)uz_wavegen_triangle_sample_with_offset(inst, amplitude, frequency_Hz, offset);
    uz_SystemTime_GetUptimeInUs_ExpectAndReturn(50000U);
    float output = uz_wavegen_triangle_sample_with_offset(inst, amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(0.5f * amplitude + offset, output);
}

/* ----------------------------- white noise ----------------------------- */

void test_uz_wavegen_white_noise_zero_amplitude(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_white_noise(0.0f));
}

#endif // TEST
