#ifdef TEST

#include "unity.h"

#include "uz_signals.h"
#include "test_assert_with_exception.h"
TEST_FILE("uz_signals_iir_filter.c")

struct uz_IIR_Filter_config config = { 0 };
void setUp(void)
{
    config.selection = LowPass;
    config.cutoff_frequency_Hz = 200.0f;
    config.sample_frequency_Hz = 20000.0f;
}

void tearDown(void)
{
}

void test_uz_signals_IIR_Filter_init_assert_sample_Freq(void) {
    config.sample_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    config.sample_frequency_Hz = -20.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
}

void test_uz_signals_IIR_Filter_init_assert_cutoff_Freq(void) {
    config.cutoff_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    config.cutoff_frequency_Hz = -20.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
}

void test_uz_signals_IIR_Filter_init_assert_sample_Freq_higher_than_cutoff_Freq(void) {
    config.cutoff_frequency_Hz = 10000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    config.cutoff_frequency_Hz = 30000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    //sample=20k->because of Nyquist–Shannon filter max 10k
    config.cutoff_frequency_Hz = 9999.0f;
    TEST_ASSERT_PASS_ASSERT(uz_signals_IIR_Filter_init(config));
}

void test_uz_signals_IIR_Filter_sample_NULL_pointer(void) {
    float input = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_sample(NULL, input));
}

void test_uz_signals_IIR_Filter_reverse_sample_NULL_pointer(void) {
    float input = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_reverse_sample(NULL, input));
}

void test_uz_signals_IIR_Filter_lowpass_output(void) {
    float input_array[20] = {0.0379f,2.2678f, 0.6551f, -1.3192f, 0.7978f, 
    2.9265f, 1.1755f, -1.0237f, 0.6599f, 2.2902f, -0.0473f, -2.3340f, -0.5630f, 1.3410f,
    -0.8848f, -2.8566f, -1.0677f, 0.9698f, -0.6236f, -2.4335f};
    float expected_filtered_array[20] = {0.0379f,1.1198f,0.8943f,-0.1797f,0.2946f,1.5716f,
    1.3794f,0.2134f,0.4301f,1.3326f,0.6631f,-0.7911f,-0.6804f,0.3004f,-0.2747f,
    -1.5274f,-1.3044f,-0.2010f,-0.4060f,-1.3897f};
    float filtered_array[20] = {0};
    config.cutoff_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}

void test_uz_signals_IIR_Filter_highpass_output(void) {
    float input_array[20] = {0.0379f,2.2678f, 0.6551f, -1.3192f, 0.7978f, 
    2.9265f, 1.1755f, -1.0237f, 0.6599f, 2.2902f, -0.0473f, -2.3340f, -0.5630f, 1.3410f,
    -0.8848f, -2.8566f, -1.0677f, 0.9698f, -0.6236f, -2.4335f};
    float expected_filtered_array[20] = {0.0379f,1.1675f,-0.2292f,-1.1343f,0.5059f,1.3563f,
    -0.2032f,-1.2368f,0.2300f,0.9577f,-0.7103f,-1.5429f,0.1174f,1.0406f,-0.6101f,
    -1.3292f,0.2366f,1.1708f,-0.2176f,-1.0438f};
    float filtered_array[20] = {0};
    config.cutoff_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.selection = HighPass;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}

void test_uz_signals_IIR_Filter_lowpass_reverse_output(void) {
    float expected_filtered_array[20] = {0.0379f,2.2678f, 0.6551f, -1.3192f, 0.7978f, 
    2.9265f, 1.1755f, -1.0237f, 0.6599f, 2.2902f, -0.0473f, -2.3340f, -0.5630f, 1.3410f,
    -0.8848f, -2.8566f, -1.0677f, 0.9698f, -0.6236f, -2.4335f};
    float input_array[20] = {0.0379f,1.1198f,0.8943f,-0.1797f,0.2946f,1.5716f,
    1.3794f,0.2134f,0.4301f,1.3326f,0.6631f,-0.7911f,-0.6804f,0.3004f,-0.2747f,
    -1.5274f,-1.3044f,-0.2010f,-0.4060f,-1.3897f};
    float filtered_array[20] = {0};
    config.cutoff_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_reverse_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}

void test_uz_signals_Filter_1st_highpass_reverse_output(void) {
    float expected_filtered_array[20] = {0.0379f,2.2678f, 0.6551f, -1.3192f, 0.7978f, 
    2.9265f, 1.1755f, -1.0237f, 0.6599f, 2.2902f, -0.0473f, -2.3340f, -0.5630f, 1.3410f,
    -0.8848f, -2.8566f, -1.0677f, 0.9698f, -0.6236f, -2.4335f};
    float input_array[20] = {0.0379f,1.1675f,-0.2292f,-1.1343f,0.5059f,1.3563f,
    -0.2032f,-1.2368f,0.2300f,0.9577f,-0.7103f,-1.5429f,0.1174f,1.0406f,-0.6101f,
    -1.3292f,0.2366f,1.1708f,-0.2176f,-1.0438f};
    float filtered_array[20] = {0};
    config.cutoff_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.selection = HighPass;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_reverse_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}
#endif // TEST
