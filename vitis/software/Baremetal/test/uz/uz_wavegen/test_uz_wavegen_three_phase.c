#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "test_assert_with_exception.h"
#include "uz_Transformation.h"
TEST_FILE("uz_wavegen_three_phase.c")

void test_uz_wavegen_three_phase_negative_frequency(void)
{
    float amplitude = 10.1f;
    float frequency = -5.4f;
    float offset = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_sample(amplitude, frequency, offset));
}

void test_uz_wavegen_three_phase_init_zero_start_frequency(void)
{
    float amplitude = 10.1f;
    float frequency = 0.0f;
    float offset = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_sample(amplitude, frequency, offset));
}

void test_uz_wavegen_three_phase_output(void)
{
    float amplitude = 2.0f;
    float frequency = 5.0f;
    float offset = 1.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.6f);
    uz_3ph_abc_t three_phase_sine = uz_wavegen_three_phase_sample(amplitude, frequency, offset);

    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.0f, three_phase_sine.a);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.7321f, three_phase_sine.b);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.7321f, three_phase_sine.c);
}

#endif