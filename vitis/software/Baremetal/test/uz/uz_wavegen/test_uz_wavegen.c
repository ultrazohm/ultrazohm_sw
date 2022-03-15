#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"
#include "uz_Transformation.h"
#include "test_assert_with_exception.h"

void test_uz_wavegen_sine_negative_input_frequency(void){
    float a=-10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(1.0f,a));
}

void test_uz_wavegen_sine_zero_input_frequency(void){
    float a=0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(1.0f,a));
}

void test_uz_wavegen_sine_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine(0.0f,5.0f));
}

void test_uz_wavegen_sine_output(void){
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05f);
    float output = uz_wavegen_sine(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(amplitude,output); 
}

void test_uz_wavegen_sine_offset_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_with_offset(1.0f,-10.0f,0.0f));
}

void test_uz_wavegen_sine_offset_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_with_offset(1.0f,0.0f,0.0f));
}

void test_uz_wavegen_sine_offset_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sine_with_offset(0.0f,5.0f,2.0f));
}

void test_uz_wavegen_sine_offset_output(void){
    float amplitude = -5.0f;
    float frequency_Hz = 5.0f;
    float offset = 1.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05f);
    float output = uz_wavegen_sine_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(amplitude + offset, output); 
}

void test_uz_wavegen_sawtooth_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth(1.0f,-10.0f));
}

void test_uz_wavegen_sawtooth_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth(1.0f,0.0f));
}

void test_uz_wavegen_sawtooth_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth(0.0f,5.0f));
}

void test_uz_wavegen_sawtooth_output(void){
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.5f);
    float output = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.5f * amplitude, output); 
}

void test_uz_wavegen_sawtooth_offset_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_with_offset(1.0f,-10.0f,0.0f));
}

void test_uz_wavegen_sawtooth_offset_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_with_offset(1.0f,0.0f,0.0f));
}

void test_uz_wavegen_sawtooth_offset_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_sawtooth_with_offset(0.0f,5.0f,0.0f));
}

void test_uz_wavegen_sawtooth_offset_output(void){
    float amplitude = -5.0f;
    float frequency_Hz = 10.0f;
    float offset = 1.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.15f);
    float output = uz_wavegen_sawtooth_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(0.5f * amplitude + offset, output); 
}

void test_uz_wavegen_pulse_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1.0f,-10.0f,0.5f));
}

void test_uz_wavegen_pulse_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1.0f,0.0f,0.5f));
}

void test_uz_wavegen_pulse_negative_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1.0f,10.0f,-0.5f));
}

void test_uz_wavegen_pulse_too_high_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(1.0f,10.0f,2.0f));
}


void test_uz_wavegen_pulse_zero_input_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_pulse(0.0f,5.0f,0.5f));
}

void test_uz_wavegen_pulse_output(void){
    float amplitude = 8.0f;
    float frequency_Hz = 10.0f;
    float duty_cycle = 0.5f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.04f);
    float output = uz_wavegen_pulse(amplitude, frequency_Hz, duty_cycle);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output); 
}

void test_uz_wavegen_square_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1.0f,-10.0f,0.5f));
}

void test_uz_wavegen_square_negative_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1.0f,10.0f,-0.5f));
}

void test_uz_wavegen_square_too_high_DutyCycle(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1.0f,10.0f,2.0f));
}
void test_uz_wavegen_square_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_square(1.0f,0.0f,0.5f));
}

void test_uz_wavegen_square_output(void){
    float amplitude = 6.0f;
    float frequency_Hz = 20.0f;
    float duty_cycle = 0.5f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.02f);
    float output = uz_wavegen_square(amplitude, frequency_Hz, duty_cycle);
    TEST_ASSERT_EQUAL_FLOAT(amplitude, output); 
}

void test_uz_wavegen_triangle_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle(1.0f,-10.0f));
}

void test_uz_wavegen_triangle_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle(1.0f,0.0f));
}

void test_uz_wavegen_triangle_output(void){
    float amplitude = 10.0f;
    float frequency_Hz = 5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.025f);
    float output = uz_wavegen_triangle(amplitude, frequency_Hz);
    TEST_ASSERT_EQUAL_FLOAT(0.25f * amplitude, output); 
}

void test_uz_wavegen_triangle_offset_negative_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_with_offset(1.0f,-10.0f,1.0f));
}

void test_uz_wavegen_triangle_offset_zero_input_frequency(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_triangle_with_offset(1.0f,0.0f,1.0f));
}

void test_uz_wavegen_triangle_offset_output(void){
    float amplitude = 6.0f;
    float frequency_Hz = 5.0f;
    float offset = -5.0f;
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.05f);
    float output = uz_wavegen_triangle_with_offset(amplitude, frequency_Hz, offset);
    TEST_ASSERT_EQUAL_FLOAT(0.5f * amplitude + offset, output); 
}

void test_uz_wavegen_white_noise_zero_amplitude(void){
    TEST_ASSERT_FAIL_ASSERT(uz_wavegen_white_noise(0.0f));
}

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
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(0.15f);
    uz_3ph_abc_t three_phase_sine = uz_wavegen_three_phase_sample(amplitude, frequency, offset);

    TEST_ASSERT_EQUAL_FLOAT(-1.0f, three_phase_sine.a);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, three_phase_sine.b);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, three_phase_sine.c);
}

#endif // TEST