#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "test_assert_with_exception.h"

void test_uz_wavegen_sine_negative_input_frequency(void){
    float a=-10;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(0,a));
}

void test_uz_wavegen_sine_zero_input_frequency(void){
    float a=0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(0,a));
}

void test_uz_wavegen_sine_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(0,5));
}

void test_uz_wavegen_sine_output(void){
    float amplitude = -5.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.25);
    float t_Sec = 0.25f;
    float output = uz_wavegen_sine(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(amplitude * sinf(2.0f * M_PI * t_Sec * frequency_Hz),output); 
}

void test_uz_wavegen_sine_offset_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_with_offset(1,-10,0));
}

void test_uz_wavegen_sine_offset_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_with_offset(1,0,0));
}

void test_uz_wavegen_sine_offset_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_with_offset(0,5,2));
}

void test_uz_wavegen_sine_offset_output(void){
    float amplitude = -5.0f;
    float frequency_Hz = 5.0f;
    float offset = 1.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.25);
    float t_Sec = 0.25f;
    float output = uz_wavegen_sine_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(amplitude * sinf(2.0f * M_PI * t_Sec * frequency_Hz) + offset,output); 
}

void test_uz_wavegen_sawtooth_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth(1,-10));
}

void test_uz_wavegen_sawtooth_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth(1,0));
}

void test_uz_wavegen_sawtooth_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth(0,5));
}

void test_uz_wavegen_sawtooth_output(void){
    float amplitude = -5.0f;
    float frequency_Hz = 5.0f;
    float offset = 1.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.25);
    float t_Sec = 0.25f;
	float sample = fmodf(t_Sec, 1 / frequency_Hz);
    float output = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(sample * amplitude * frequency_Hz, output); 
}

#endif // TEST
