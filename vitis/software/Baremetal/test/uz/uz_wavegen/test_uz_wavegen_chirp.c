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
        .duration_sec = 5.0f,
        .initial_delay_sec = 1.0f,
        .offset = 1.0f
};

void test_uz_wavegen_chirp_init_successful(void){    
    float sample_time = 1.0f/10.0e3f;
    uz_wavegen_chirp* chirp_instance=uz_wavegen_chirp_init(config_chirp);
    //uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05f);
    uz_wavegen_chirp_sample(chirp_instance, sample_time);
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
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_sample(NULL, 0.0f));
}

// Old Test
// void test_uz_wavegen_chirp_output_delay(void){
//     //tests, if the initial_delay of the chirp works
//     float sample_time = 1.0f/10.0e3f;
//     uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
//     uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(1.5f);
//     uz_wavegen_chirp_sample(test_chirp, sample_time);
//     uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(2.0f);
//     TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_wavegen_chirp_sample(test_chirp, sample_time));
// }

// New Test
void test_uz_wavegen_chirp_output_delay(void){
    //tests, if the initial_delay of the chirp works
    config_chirp.amplitude = 2.0f;
    config_chirp.start_frequency_Hz = 1.0f;
    config_chirp.end_frequency_Hz = 10.0f;
    config_chirp.duration_sec = 5.0f;
    config_chirp.initial_delay_sec = 1.0f;
    config_chirp.offset = 1.0f;
    float sample_time = 1.0f/100.0f;
    float results[1000] = {0.0}; 
    uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
    for (int i=0; i<99; i++){
    results[i] = uz_wavegen_chirp_sample(test_chirp, sample_time);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_wavegen_chirp_sample(test_chirp, sample_time));  
}

// Old Test
// void test_uz_wavegen_chirp_output_end(void){
//     //tests, if the sine wave after the chirp duration works
//     float sample_time = 1.0f/10.0e3f;
//     uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
//     uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.0f);
//     uz_wavegen_chirp_sample(test_chirp, sample_time);
//     uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(3.025f);
//     TEST_ASSERT_EQUAL_FLOAT(3.0f, uz_wavegen_chirp_sample(test_chirp, sample_time));
// }

void test_uz_wavegen_chirp_output_reset(void){
    //tests, if the reset of the chirp works
    config_chirp.amplitude = 2.0f;
    config_chirp.start_frequency_Hz = 1.0f;
    config_chirp.end_frequency_Hz = 10.0f;
    config_chirp.duration_sec = 5.0f;
    config_chirp.initial_delay_sec = 1.0f;
    config_chirp.offset = 1.0f;
    float sample_time = 1.0f/100.0f;
    float results[1000] = {0.0}; 
    uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
    for (int i=0; i<600; i++){
    results[i] = uz_wavegen_chirp_sample(test_chirp, sample_time);
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_wavegen_chirp_sample(test_chirp, sample_time));  
}

void test_uz_wavegen_chirp_output_samples(void){
    //tests, if the chirp is actually a chirp
    config_chirp.amplitude = 2.0f;
    config_chirp.start_frequency_Hz = 1.0f;
    config_chirp.end_frequency_Hz = 10.0f;
    config_chirp.duration_sec = 5.0f;
    config_chirp.initial_delay_sec = 1.0f;
    config_chirp.offset = 1.0f;
    float sample_time = 1.0f/100.0f;
    uz_wavegen_chirp* test_chirp = uz_wavegen_chirp_init(config_chirp);
    for (int i=0; i<101; i++){
    uz_wavegen_chirp_sample(test_chirp, sample_time);
    }
    //TEST_ASSERT_EQUAL_FLOAT(1.1267f, uz_wavegen_chirp_sample(test_chirp, sample_time)); 
    TEST_ASSERT_FLOAT_WITHIN(0.005f, 1.126f, uz_wavegen_chirp_sample(test_chirp, sample_time));
    for (int i=0; i<123; i++){
    uz_wavegen_chirp_sample(test_chirp, sample_time);
    }
    //TEST_ASSERT_EQUAL_FLOAT(-0.6629f, uz_wavegen_chirp_sample(test_chirp, sample_time)); 
    TEST_ASSERT_FLOAT_WITHIN(0.005f, -0.662f, uz_wavegen_chirp_sample(test_chirp, sample_time));
    for (int i=0; i<246; i++){
    uz_wavegen_chirp_sample(test_chirp, sample_time);
    }
    //TEST_ASSERT_EQUAL_FLOAT(2.7795f, uz_wavegen_chirp_sample(test_chirp, sample_time)); 
    TEST_ASSERT_FLOAT_WITHIN(0.005f, 2.779f, uz_wavegen_chirp_sample(test_chirp, sample_time));
    for (int i=0; i<84; i++){
    uz_wavegen_chirp_sample(test_chirp, sample_time);
    }
    //TEST_ASSERT_EQUAL_FLOAT(1.5124f, uz_wavegen_chirp_sample(test_chirp, sample_time)); 
    TEST_ASSERT_FLOAT_WITHIN(0.005f, 2.488f, uz_wavegen_chirp_sample(test_chirp, sample_time));
}

void test_uz_wavegen_chirp_init_max_instances(void){    
    //MAX_INSTANCES was set to 13 for the test
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_chirp_init(config_chirp));
}

#endif