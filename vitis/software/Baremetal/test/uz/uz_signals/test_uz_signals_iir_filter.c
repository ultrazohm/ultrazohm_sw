#ifdef TEST

#include "unity.h"

#include "uz_signals.h"
#include "test_assert_with_exception.h"
TEST_FILE("uz_signals_iir_filter.c")

struct uz_IIR_Filter_config config = { 0 };
void setUp(void)
{
    config.selection = LowPass_first_order;
    config.cutoff_frequency_Hz = 200.0f;
    config.pass_frequency_Hz = 200.0f;
    config.sample_frequency_Hz = 20000.0f;
    config.damping = 0.05f;
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

void test_uz_signals_IIR_Filter_init_assert_pass_Freq(void) {
    config.selection = BandPass_second_order;
    config.pass_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    config.pass_frequency_Hz = -20.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
}

void test_uz_signals_IIR_Filter_init_assert_cutoff_Freq_higher_than_sample_Freq(void) {
    config.cutoff_frequency_Hz = 10000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    config.cutoff_frequency_Hz = 30000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    //sample=20k->because of Nyquist–Shannon filter max 10k
    config.cutoff_frequency_Hz = 9999.0f;
    TEST_ASSERT_PASS_ASSERT(uz_signals_IIR_Filter_init(config));
}

void test_uz_signals_IIR_Filter_init_assert_pass_Freq_higher_than_sample_Freq(void) {
    config.pass_frequency_Hz = 10000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    config.pass_frequency_Hz = 30000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_init(config));
    //sample=20k->because of Nyquist–Shannon filter max 10k
    config.pass_frequency_Hz = 9999.0f;
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
    float input_array[20] = {0.0379f, 2.2678f, 0.6551f,-1.3192f, 0.7978f, 
                             2.9265f, 1.1755f,-1.0237f, 0.6599f, 2.2902f,
                            -0.0473f,-2.3340f,-0.5630f, 1.3410f,-0.8848f,
                            -2.8566f,-1.0677f, 0.9698f,-0.6236f,-2.4335f};

    float expected_filtered_array[20] = {0.0379f, 1.1198f, 0.8943f,-0.1797f, 0.2946f,
                                         1.5716f, 1.3794f, 0.2134f, 0.4301f, 1.3326f,
                                         0.6631f,-0.7911f,-0.6804f, 0.3004f,-0.2747f,
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
    float input_array[20] = {0.0379f, 2.2678f, 0.6551f,-1.3192f, 0.7978f, 
                             2.9265f, 1.1755f,-1.0237f, 0.6599f, 2.2902f,
                            -0.0473f,-2.3340f,-0.5630f, 1.3410f,-0.8848f,
                            -2.8566f,-1.0677f, 0.9698f,-0.6236f,-2.4335f};

    float expected_filtered_array[20] = {0.0379f, 1.1675f,-0.2292f,-1.1343f, 0.5059f,
                                         1.3563f,-0.2032f,-1.2368f, 0.2300f, 0.9577f,
                                        -0.7103f,-1.5429f, 0.1174f, 1.0406f,-0.6101f,
                                        -1.3292f, 0.2366f, 1.1708f,-0.2176f,-1.0438f};

    float filtered_array[20] = {0};
    config.cutoff_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.selection = HighPass_first_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}

void test_uz_signals_IIR_Filter_bandpass_output(void) {
    float input_array[20] = {0.0379f, 2.2678f, 0.6551f,-1.3192f, 0.7978f,
                             2.9265f, 1.1755f,-1.0237f, 0.6599f, 2.2902f,
                            -0.0473f,-2.3340f,-0.5630f, 1.3410f,-0.8848f,
                            -2.8566f,-1.0677f, 0.9698f,-0.6236f,-2.4335f};
    float expected_filtered_array[20] = {0.0379f, 2.2678f, 2.7679f, 1.1605f,-1.1344f,
                                        -2.3073f,-1.7643f,-0.1735f, 1.4015f, 2.0017f, 
                                         1.1301f,-0.6393f,-1.8491f,-1.5385f,-0.1861f,
                                         1.0402f, 1.4407f, 0.9452f,-0.1585f,-1.1957f};
    float filtered_array[20] = {0};
    config.pass_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.damping = 0.05f;
    config.selection = BandPass_second_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}

void test_uz_signals_IIR_Filter_lowpass_reverse_output(void) {
    float expected_filtered_array[20] = {0.0379f, 2.2678f, 0.6551f,-1.3192f, 0.7978f, 
                                         2.9265f, 1.1755f,-1.0237f, 0.6599f, 2.2902f,
                                        -0.0473f,-2.3340f,-0.5630f, 1.3410f,-0.8848f,
                                        -2.8566f,-1.0677f, 0.9698f,-0.6236f, -2.4335f};

    float input_array[20] = {0.0379f, 1.1198f, 0.8943f,-0.1797f, 0.2946f,
                             1.5716f, 1.3794f, 0.2134f, 0.4301f, 1.3326f,
                             0.6631f,-0.7911f,-0.6804f, 0.3004f,-0.2747f,
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
    float expected_filtered_array[20] = {0.0379f, 2.2678f, 0.6551f,-1.3192f, 0.7978f, 
                                         2.9265f, 1.1755f,-1.0237f, 0.6599f, 2.2902f,
                                        -0.0473f,-2.3340f,-0.5630f, 1.3410f,-0.8848f,
                                        -2.8566f,-1.0677f, 0.9698f,-0.6236f,-2.4335f};

    float input_array[20] = {0.0379f, 1.1675f,-0.2292f,-1.1343f, 0.5059f,
                             1.3563f,-0.2032f,-1.2368f, 0.2300f, 0.9577f,
                            -0.7103f,-1.5429f, 0.1174f, 1.0406f,-0.6101f,
                            -1.3292f, 0.2366f, 1.1708f,-0.2176f,-1.0438f};
    float filtered_array[20] = {0};
    config.cutoff_frequency_Hz = 150.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.selection = HighPass_first_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_reverse_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
    }
}

void test_uz_signals_IIR_Filter_set_lowpass_assert_cutoff_Freq(void) {
    config.sample_frequency_Hz = 1000.0f;
    config.selection = LowPass_first_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    float cutoff_frequency_Hz = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_set_lowpass(test_instance, cutoff_frequency_Hz));
    cutoff_frequency_Hz = 500.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_set_lowpass(test_instance, cutoff_frequency_Hz));
    cutoff_frequency_Hz = 499.9f;
    TEST_ASSERT_PASS_ASSERT(uz_signals_IIR_Filter_set_lowpass(test_instance, cutoff_frequency_Hz));
}

void test_uz_signals_IIR_Filter_set_lowpass(void){
    float input_array[20] = {0.5000f, 1.6861f, 3.0182f, 4.9286f, 5.1446f,
                             4.2553f, 4.0071f, 2.8133f, 0.2222f,-1.3980f,
                            -2.4389f,-4.3761f,-5.3159f,-4.5069f,-4.0671f,
                            -3.4389f,-1.0889f, 1.0312f, 2.0043f, 3.6981f};
    float expected_filtered_array[20] = {0.5000f, 1.2750f, 2.4140f, 4.0570f, 4.7676f,
                                         4.4329f, 4.1547f, 3.2782f, 1.2815f,-0.4692f,
                                        -1.7562f,-2.4735f,-3.2517f,-3.5953f,-3.7245f,
                                        -3.6463f,-2.9462f,-1.8573f,-0.8001f, 0.4314f};
    float filtered_array[20] = { 0 };
    config.cutoff_frequency_Hz = 300.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.selection = LowPass_first_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
        if (i == 10)
        {
            float cutoff_frequency_Hz = 60.0f;
            uz_signals_IIR_Filter_set_lowpass(test_instance, cutoff_frequency_Hz);
        }
    }
}

void test_uz_signals_IIR_Filter_set_bandpass_assert_pass_Freq_and_damping(void){
    config.sample_frequency_Hz = 1000.0f;
    config.selection = BandPass_second_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    float pass_frequency_Hz = -10.0f;
    float damping = 0.05f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_set_bandpass(test_instance, pass_frequency_Hz, damping));
    pass_frequency_Hz = 500.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_set_bandpass(test_instance, pass_frequency_Hz, damping));
    pass_frequency_Hz = 499.9f;
    TEST_ASSERT_PASS_ASSERT(uz_signals_IIR_Filter_set_bandpass(test_instance, pass_frequency_Hz, damping));
    damping = -0.05f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_set_bandpass(test_instance, pass_frequency_Hz, damping));
}

void test_uz_signals_IIR_Filter_set_bandpass(void){
    float input_array[20] = {0.5000f, 1.6861f, 3.0182f, 4.9286f, 5.1446f,
                             4.2553f, 4.0071f, 2.8133f, 0.2222f,-1.3980f,
                            -2.4389f,-4.3761f,-5.3159f,-4.5069f,-4.0671f,
                            -3.4389f,-1.0889f, 1.0312f, 2.0043f, 3.6981f};
    float expected_filtered_array[20] = {0.5000f, 1.6861f,-0.1427f,-1.3877f, 0.0738f,
                                         1.2321f, 0.0180f,-1.1815f,-0.3294f, 0.8318f,
                                         0.2654f,-0.4010f,-1.0686f,-1.5523f,-1.7526f,
                                        -1.6692f,-1.2661f,-0.5665f, 0.2675f, 1.1012f};
    float filtered_array[20] = { 0 };
    config.pass_frequency_Hz = 300.0f;
    config.sample_frequency_Hz = 1000.0f;
    config.damping = 0.05f;
    config.selection = BandPass_second_order;
    uz_IIR_Filter_t* test_instance = uz_signals_IIR_Filter_init(config);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_signals_IIR_Filter_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, expected_filtered_array[i], filtered_array[i]);
        if (i == 10)
        {
            float pass_frequency_Hz = 60.0f;
            float damping = 0.1f;
            uz_signals_IIR_Filter_set_bandpass(test_instance, pass_frequency_Hz, damping);
        }
    }
}

#endif // TEST
