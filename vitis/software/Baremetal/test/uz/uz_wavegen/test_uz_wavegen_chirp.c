#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include "mock_uz_SystemTime.h"
#include "test_assert_with_exception.h"
TEST_FILE("uz_wavegen_chirp.c")

void setUp(void)
{
}

void tearDown(void)
{
}

struct uz_wavegen_chirp_config config_chirp = {
        .amplitude = 2.0f,
        .start_frequency_Hz = 1.0f,
        .end_frequency_Hz = 10.0f,
        .duration_sec = 10.0f,
        .initial_delay_sec = 0.0f,
        .offset = 1.0f
};

void test_uz_wavegen_chirp_init_successful(void){    
    uz_wavegen_chirp* chirp_instance=uz_wavegen_chirp_init(config_chirp);
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05f);
    uz_wavegen_chirp_sample(chirp_instance);
}

void test_uz_wavegen_chirp_init_zero_amplitude(void){ 
    config_chirp.amplitude = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
    config_chirp.amplitude = 2.0f;
}

void test_uz_wavegen_chirp_init_negative_start_frequency(void){ 
    config_chirp.start_frequency_Hz = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
}

void test_uz_wavegen_chirp_init_zero_start_frequency(void){ 
    config_chirp.start_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
    config_chirp.start_frequency_Hz = 10.0f;
}

void test_uz_wavegen_chirp_init_negative_end_frequency(void){ 
    config_chirp.end_frequency_Hz = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
}

void test_uz_wavegen_chirp_init_zero_end_frequency(void){ 
    config_chirp.end_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
}

void test_uz_wavegen_chirp_init_end_smaller_than_start_frequency(void){ 
    config_chirp.end_frequency_Hz = 5.0f;
    config_chirp.start_frequency_Hz = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
    config_chirp.start_frequency_Hz = 2.0f;
    config_chirp.end_frequency_Hz = 10.0f;
}

void test_uz_wavegen_chirp_init_negative_delay(void){ 
    config_chirp.initial_delay_sec = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
    config_chirp.initial_delay_sec = 1.0f;
}

void test_uz_wavegen_chirp_init_negative_duration(void){ 
    config_chirp.duration_sec = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
}

void test_uz_wavegen_chirp_init_zero_duration(void){ 
    config_chirp.duration_sec = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
    config_chirp.duration_sec = 2.0f;
}

void test_uz_wavegen_chirp_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_reset(NULL));
}

void test_uz_wavegen_chirp_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_sample(NULL));
}

void test_uz_wavegen_chirp_output_delay(void){
    //tests, if the initial_delay of the chirp works
    uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(1.5f);
    uz_wavegen_chirp_sample(test_chirp);
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(2.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_wavegen_chirp_sample(test_chirp));
}

void test_uz_wavegen_chirp_output_end(void){
    //tests, if the sine wave after the chirp duration works
    uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.0f);
    uz_wavegen_chirp_sample(test_chirp);
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(3.025f);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_wavegen_chirp_sample(test_chirp));
}

void test_uz_wavegen_chirp_init_max_instances(void){    
    //MAX_INSTANCES was set to 13 for the test
    TEST_ASSERT_PASS_ASSERT(uz_wavegen_chirp_init(config_chirp));
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
}

#endif