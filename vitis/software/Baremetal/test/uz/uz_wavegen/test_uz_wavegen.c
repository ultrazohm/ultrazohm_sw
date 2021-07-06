#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "test_assert_with_exception.h"

void test_uz_wavegen_sine_negative_input_frequency(void){
    float a=-10;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(1,a));
}

void test_uz_wavegen_sine_zero_input_frequency(void){
    float a=0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(1,a));
}

void test_uz_wavegen_sine_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(0,5));
}

void test_uz_wavegen_sine_output(void){
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05);
    float output = uz_wavegen_sine(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(amplitude,output); 
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
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05);
    float output = uz_wavegen_sine_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(amplitude + offset, output); 
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
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.5);
    float output = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.5 * amplitude, output); 
}

void test_uz_wavegen_sawtooth_offset_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_with_offset(1,-10,0));
}

void test_uz_wavegen_sawtooth_offset_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_with_offset(1,0,0));
}

void test_uz_wavegen_sawtooth_offset_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_with_offset(0,5,0));
}

void test_uz_wavegen_sawtooth_offset_output(void){
    float amplitude = -5.0f;
    float frequency_Hz = 10.0f;
    float offset = 1.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.15);
    float output = uz_wavegen_sawtooth_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(0.5 * amplitude + offset, output); 
}

void test_uz_wavegen_pulse_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1,-10,0.5));
}

void test_uz_wavegen_pulse_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1,0,0.5));
}

void test_uz_wavegen_pulse_negative_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1,10,-0.5));
}

void test_uz_wavegen_pulse_too_high_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1,10,2.0));
}


void test_uz_wavegen_pulse_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(0,5,0.5));
}

void test_uz_wavegen_pulse_output(void){
    float amplitude = 8.0f;
    float frequency_Hz = 10.0f;
    float duty_cycle = 0.5f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.04);
    float output = uz_wavegen_pulse(amplitude, frequency_Hz, duty_cycle);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output); 
}

void test_uz_wavegen_square_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1,-10,0.5));
}

void test_uz_wavegen_square_negative_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1,10,-0.5));
}

void test_uz_wavegen_square_too_high_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1,10,2.0));
}
void test_uz_wavegen_square_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1,0,0.5));
}

void test_uz_wavegen_square_output(void){
    float amplitude = 6.0f;
    float frequency_Hz = 20.0f;
    float duty_cycle = 0.5f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.02);
    float output = uz_wavegen_square(amplitude, frequency_Hz, duty_cycle);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output); 
}

void test_uz_wavegen_triangle_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle(1,-10));
}

void test_uz_wavegen_triangle_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle(1,0));
}

void test_uz_wavegen_triangle_output(void){
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.025);
    float output = uz_wavegen_triangle(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.25 * amplitude, output); 
}

void test_uz_wavegen_triangle_offset_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_with_offset(1,-10,1.0));
}

void test_uz_wavegen_triangle_offset_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_with_offset(1,0,1.0));
}

void test_uz_wavegen_triangle_offset_output(void){
    float amplitude = 6.0f;
    float frequency_Hz = 5.0f;
    float offset = -5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05);
    float output = uz_wavegen_triangle_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(0.5 * amplitude + offset, output); 
}

void test_uz_wavegen_white_noise_zero_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_white_noise(0));
}



#endif // TEST