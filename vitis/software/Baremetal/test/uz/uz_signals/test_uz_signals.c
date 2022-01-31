#ifdef TEST

#include "unity.h"

#include "uz_signals.h"
#include "test_assert_with_exception.h"

struct uz_Filter_1st_config config = { 0 };
void setUp(void)
{
    config.selection = LowPass;
    config.cutoff_frequency_Hz = 200.0f;
    config.sample_frequency_Hz = 20000.0f;
}

void tearDown(void)
{
}

void test_uz_signals_dead_zone_return_zero_if_in_dead_zone(void)
{
    float input=1.1f;
    float upper_limit=10.1f;
    float lower_limit=-10.0f;
    TEST_ASSERT_EQUAL_FLOAT(0.0f,uz_signals_dead_zone(input, upper_limit, lower_limit)); // Test positive input
    TEST_ASSERT_EQUAL_FLOAT(0.0f,uz_signals_dead_zone(-input, upper_limit, lower_limit)); // Test negative input
}

void test_uz_signals_dead_zone_return_when_input_greater_than_deadzone(void){
    float input=20.0f;
    float upper_limit=10.0f;
    float lower_limit=-10.0f;
    TEST_ASSERT_EQUAL_FLOAT(input-upper_limit,uz_signals_dead_zone(input, upper_limit, lower_limit));
}

void test_uz_signals_dead_zone_return_when_input_lower_than_deadzone(void){
    float input=-20.0f;
    float upper_limit=10.0f;
    float lower_limit=-10.0f;
    TEST_ASSERT_EQUAL_FLOAT(input-lower_limit,uz_signals_dead_zone(input, upper_limit, lower_limit));
}

void test_uz_signals_dead_zone_return_when_both_thresholds_negative(void){
    float input=-30.0f;
    float upper_limit=-10.0f;
    float lower_limit=-20.0f;
    TEST_ASSERT_EQUAL_FLOAT(input-lower_limit,uz_signals_dead_zone(input, upper_limit, lower_limit));
}

void test_uz_signals_dead_zone_assert_if_lower_threshold_is_greater_then_upper(void){
    float input=1.0f;
    float upper_limit=1.0f;
    float lower_limit=2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_dead_zone(input,upper_limit,lower_limit));
}

void test_uz_signals_get_sign_of_value_input_positive(void){
    float input = 20.5f;
    TEST_ASSERT_EQUAL_FLOAT(1,uz_signals_get_sign_of_value(input));
}

void test_uz_signals_get_sign_of_value_input_negative(void){
    float input = -20.5f;
    TEST_ASSERT_EQUAL_FLOAT(-1,uz_signals_get_sign_of_value(input));
}

void test_uz_signals_get_sign_of_value_input_zero(void){
    float input = 0.0f;
    TEST_ASSERT_EQUAL_FLOAT(0,uz_signals_get_sign_of_value(input));
}

void test_uz_signals_saturation_limit(void){
    float input = 1.1f;
    float upper_limit = 0.5f;
    float lower_limit = 1.6f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_saturation(input, upper_limit, lower_limit));
}

void test_uz_signals_saturation_output(void){
    float input = 2.1f;
    float upper_limit = 0.5f;
    float lower_limit = 0.2f;    
    TEST_ASSERT_EQUAL_FLOAT(upper_limit, uz_signals_saturation(input, upper_limit, lower_limit)); 
    input = -0.7f;
    TEST_ASSERT_EQUAL_FLOAT(lower_limit, uz_signals_saturation(input, upper_limit, lower_limit)); 
}

void test_uz_signals_Filter_1st_init_assert_sample_Freq(void) {
    config.sample_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Filter_1st_init(config));
    config.sample_frequency_Hz = -20.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Filter_1st_init(config));
}

void test_uz_signals_Filter_1st_init_assert_cutoff_Freq(void) {
    config.cutoff_frequency_Hz = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Filter_1st_init(config));
    config.cutoff_frequency_Hz = -20.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Filter_1st_init(config));
}

void test_uz_signals_Filter_1st_init_assert_sample_Freq_higher_than_cutoff_Freq(void) {
    config.cutoff_frequency_Hz = 10000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Filter_1st_init(config));
    config.cutoff_frequency_Hz = 30000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_Filter_1st_init(config));
    //sample=20k->because of Nyquist–Shannon filter max 10k
    config.cutoff_frequency_Hz = 9999.0f;
    TEST_ASSERT_PASS_ASSERT(uz_Filter_1st_init(config));
}

void test_uz_signals_Filter_1st_sample_NULL_pointer(void) {
    float input = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_signals_Filter_1st_sample(NULL, input));
}

#endif // TEST
