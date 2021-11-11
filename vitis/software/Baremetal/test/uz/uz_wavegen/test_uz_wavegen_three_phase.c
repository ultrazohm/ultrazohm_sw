#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "test_assert_with_exception.h"
TEST_FILE("uz_wavegen_three_phase.c")

struct uz_wavegen_three_phase_config config_three = {
        .amplitude = 2.0f,
        .frequency_Hz = 1.0f,
        .offset = 1.0f
};

void test_uz_wavegen_three_phase_init_zero_amplitude(void){ 
    config_three.amplitude = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
    config_three.amplitude = 2.0f;
}

void test_uz_wavegen_three_phase_init_negative_start_frequency(void){ 
    config_three.frequency_Hz = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
}

void test_uz_wavegen_three_phase_init_zero_start_frequency(void){ 
    config_three.frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
    config_three.frequency_Hz = 5.0f;
}

void test_uz_wavegen_three_phase_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_sample(NULL));
}

void test_uz_wavegen_three_phase_get_phaseU_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_get_phaseU(NULL));
}

void test_uz_wavegen_three_phase_get_phaseV_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_get_phaseV(NULL));
}

void test_uz_wavegen_three_phase_get_phaseW_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_get_phaseW(NULL));
}

void test_uz_wavegen_three_phase_output(void){
    uz_wavegen_three_phase* three_test = uz_wavegen_three_phase_init(config_three);
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.15f);
    uz_wavegen_three_phase_sample(three_test);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, uz_wavegen_three_phase_get_phaseU(three_test));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_wavegen_three_phase_get_phaseV(three_test));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, uz_wavegen_three_phase_get_phaseW(three_test));
}

void test_uz_wavegen_three_phase_instances(void){
    //MAX_INSTANCES was set to 5 for the test
    TEST_ASSERT_PASS_ASSERT(uz_wavegen_three_phase_init(config_three));
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_three_phase_init(config_three));
}
#endif