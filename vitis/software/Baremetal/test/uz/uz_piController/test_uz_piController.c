#ifdef TEST

#include "unity.h"

#include "uz_piController.h"
#include "test_assert_with_exception.h"
#include "../uz_signals/uz_signals.h"

struct uz_PI_Controller_config config = {0};
void setUp(void)
{
    config.Kp = 10.0f;
    config.Ki = 10.0f;
    config.samplingTime_sec = 0.001f;
    config.upper_limit = 10.0f;
    config.lower_limit = -10.0f;
    config.type = UZ_PI_PARALLEL;
}

void test_uz_PI_Controller_init_assert_Ki_negative(void){
    config.Ki = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_assert_Kp_negative(void){
    config.Kp = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_assert_samplingTime_negative(void){
    config.samplingTime_sec = -0.0001f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_assert_samplingTime_zero(void){
    config.samplingTime_sec = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_assert_upper_lower_threshold(void){
    config.upper_limit = -10.2f;
    config.lower_limit = 3.4f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}
void test_uz_PI_Controller_sample_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_sample(NULL, 1.0f, 2.0f, false));
}

//Tests if proportional part of the controller outputs the expected values
void test_uz_PI_Controller_sample_output_with_Ki_zero(void){
    config.Ki = 0.0f;
    config.Kp = 11.54f;
    config.upper_limit = 100.0f;
    config.lower_limit = -100.0f;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue[4] = {2.54f, 5.0f, -1.45f, -1.23f};
    float actualValue[4] = {1.62f, 6.5f, -3.25f, 2.54f};
    for(int i=0;i<4;i++){
        TEST_ASSERT_EQUAL_FLOAT(config.Kp * ( referenceValue[i] - actualValue[i] ),uz_PI_Controller_sample(variables, referenceValue[i], actualValue[i], false));
    }  
}

//Tests if the output limitation of the controller functions as expected
void test_uz_PI_Controller_sample_output_limitation_with_Ki_zero(void){
    config.upper_limit = 10.0f;
    config.lower_limit = -10.0f;
    config.Ki = 0.0f;
    config.Kp = 11.54f;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue[4] = {5.54f, 10.32f, -9.45f, -15.23f};
    float actualValue[4] = {1.62f, 6.5f, -3.25f, 2.54f};
    float output[4] = {config.upper_limit, config.upper_limit, config.lower_limit, config.lower_limit};
    for(int i=0;i<4;i++){
        TEST_ASSERT_EQUAL_FLOAT(output[i],uz_PI_Controller_sample(variables, referenceValue[i], actualValue[i], false));
    }  
}

//Tests if the integrator of the controller outputs the expected values. 
void test_uz_PI_Controller_sample_output_with_Kp_zero(void){
    config.Ki = 1.0f;
    config.Kp = 0.0f;
    config.upper_limit = 100.0f;
    config.lower_limit = -100.0f;
    config.samplingTime_sec = 1.0f;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue = 2.0f;
    float actualValue = 1.0f;
    for(int i=0;i<10;i++){
        TEST_ASSERT_EQUAL_FLOAT( (float)i * ( referenceValue - actualValue ),uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    } 
    //Test with negative error
    uz_PI_Controller_reset(variables);
    referenceValue = 1.0f;
    actualValue = 2.0f;
    for(int i=0;i<10;i++){
        TEST_ASSERT_EQUAL_FLOAT( (float)i * ( referenceValue - actualValue ),uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    } 
}

//Test the limitation&clamping for I-part
void test_uz_PI_Controller_sample_output_limitation_with_Kp_zero(void){
    config.upper_limit = 5.0f;
    config.lower_limit = -5.0f;
    config.Ki = 1.0f;
    config.Kp = 0.0f;
    config.samplingTime_sec = 1.0f;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue = 2.0f;
    float actualValue = 1.0f;
    float output[10] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};
    for(int i=0;i<10;i++){
        TEST_ASSERT_EQUAL_FLOAT(output[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }  
    referenceValue = 1.0f;
    actualValue = 2.0f;
    //Tests if integrator was clamped during limitation
    TEST_ASSERT_EQUAL_FLOAT(5.0f, uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    //Tests with negative error
    uz_PI_Controller_reset(variables); 
    referenceValue = 1.0f;
    actualValue = 2.0f;
    float output2[10] = {-0.0f, -1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -5.0f, -5.0f, -5.0f, -5.0f};
    for(int i=0;i<10;i++){
        TEST_ASSERT_EQUAL_FLOAT(output2[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }  
    referenceValue = 2.0f;
    actualValue = 1.0f;
    //Tests if integrator was clamped during limitation
    TEST_ASSERT_EQUAL_FLOAT(-5.0f, uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    TEST_ASSERT_EQUAL_FLOAT(-5.0f, uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
}

void test_uz_PI_Controller_sample_output(void){
    config.samplingTime_sec = 1.0f;
    config.Ki = 1.0f;
    config.Kp = 11.54f;
    config.upper_limit = 20.0f;
    config.lower_limit = -20.0f;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue = 12.0f;
    float actualValue = 2.0f;
    float output[5] = {20.0f, 20.0f, 20.0f, 20.0f, 20.0f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }
    //Tests if clamping was active during limitation
    actualValue = 12.1f;
    float output2[5] = {-1.154f, -1.254f, -1.354f, -1.454f, -1.554f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output2[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }

    //Tests the same but with negative error at start
    uz_PI_Controller_reset(variables);
    referenceValue = 2.0f;
    actualValue = 12.0f;
    float output3[5] = {-20.0f, -20.0f, -20.0f, -20.0f, -20.0f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output3[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }
    //Tests if clamping was active during limitation
    actualValue = 1.9f;
    float output4[5] = {1.154f, 1.254f, 1.354f, 1.454f, 1.554f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output4[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }
}

void test_uz_PI_Controller_sample_ideal_output(void){
    config.samplingTime_sec = 1.0f;
    config.Ki = 0.086655113f;
    config.Kp = 11.54f;
    config.upper_limit = 20.0f;
    config.lower_limit = -20.0f;
    config.type = UZ_PI_IDEAL;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue = 12.0f;
    float actualValue = 2.0f;
    float output[5] = {20.0f, 20.0f, 20.0f, 20.0f, 20.0f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }
    //Tests if clamping was active during limitation
    actualValue = 12.1f;
    float output2[5] = {-1.154f, -1.254f, -1.354f, -1.454f, -1.554f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output2[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }

    //Tests the same but with negative error at start
    uz_PI_Controller_reset(variables);
    referenceValue = 2.0f;
    actualValue = 12.0f;
    float output3[5] = {-20.0f, -20.0f, -20.0f, -20.0f, -20.0f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output3[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }
    //Tests if clamping was active during limitation
    actualValue = 1.9f;
    float output4[5] = {1.154f, 1.254f, 1.354f, 1.454f, 1.554f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT(output4[i], uz_PI_Controller_sample(variables, referenceValue, actualValue, false));
    }
}

//Tests if the external clamping signal stops the integrator from rising
void test_uz_PI_Controller_sample_ext_clamping(void){
    config.samplingTime_sec = 1.0f;
    config.Ki = 1.0f;
    config.Kp = 1.154f;
    config.upper_limit = 20.0f;
    config.lower_limit = -20.0f;
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float referenceValue = 12.0f;
    float actualValue[5] = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f};
    for(int i=0;i<5;i++){
        TEST_ASSERT_EQUAL_FLOAT((referenceValue - actualValue[i]) * config.Kp, uz_PI_Controller_sample(variables, referenceValue, actualValue[i], true));
    }
}
void test_uz_PI_Controller_reset_assert_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_reset(NULL));
}

void test_uz_PI_Controller_set_Ki_assert_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Ki(NULL, 10.0f));
}

void test_uz_PI_Controller_set_Ki_assert_Ki_negative(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Ki(variables, -10.0f));
}

void test_uz_PI_Controller_set_Kp_assert_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Kp(NULL, 10.0f));
}

void test_uz_PI_Controller_set_Kp_assert_Kp_negative(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Kp(variables, -10.0f));
}

void test_uz_PI_Controller_update_limits_NULL(void){
    float upper_limit = 10.0f;
    float lower_limit = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_update_limits(NULL, upper_limit, lower_limit));
}

void test_uz_PI_Controller_update_limits_assert_limits(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    float upper_limit = 10.0f;
    float lower_limit = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_update_limits(variables, lower_limit, upper_limit));
}

void test_uz_PI_Controller_assert_type_selection(void){
    config.type = 3U;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}
#endif // TEST
