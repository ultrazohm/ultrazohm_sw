#ifdef TEST

#include "unity.h"

#include "uz_piController.h"
#include "test_assert_with_exception.h"
TEST_FILE("uz_signals.c")

uz_PI_Controller_config config = {
    .Kp = 10.0f,
    .Ki = 10.0f,
    .samplingTime_sec = 0.001f,
    .upper_limit = 10.0f,
    .lower_limit = -10.0f
};

void test_uz_PI_Controller_init_assert_Ki_negative(void){
    config.Ki = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.Ki = 2000.0f;
}

void test_uz_PI_Controller_init_assert_Kp_negative(void){
    config.Kp = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.Kp = 6.75f;
}

void test_uz_PI_Controller_init_assert_samplingTime_negative(void){
    config.samplingTime_sec = -0.0001f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_assert_samplingTime_zero(void){
    config.samplingTime_sec = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.samplingTime_sec = 0.00001f;
}

void test_uz_PI_Controller_init_assert_upper_lower_threshold(void){
    config.upper_limit = -10.2f;
    config.lower_limit = 3.4f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.upper_limit = 10.0f;
    config.lower_limit = -10.0f;

}
void test_uz_PI_Controller_sample_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_sample(NULL, 1.0f, 2.0f, false));
}

void test_uz_PI_Controller_sample_output(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
	//Compare values with Simulink Simulation
	float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_output[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
	for(int i=0;i<11;i++){
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_PI_Controller_sample(variables,1.0f,values_id[i],false)*100)/100);
	}
}

void test_uz_PI_Controller_sample_ext_clamping_output(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
	//Compare values with Simulink Simulation
	float values_iq[11]={1.042f, 1.042f, 1.042f, 1.042f, 1.042f, 1.042f, 1.042f, 1.042f, 1.042f, 1.042f, 1.042f};
	float values_output[11]={4.44f, 4.44f, 4.44f, 4.44f, 4.44f, 4.44f, 4.44f, 4.44f, 4.44f, 4.44f, 4.44f};
	bool ext_clamping[11] = {true, true, true, true, true, true, true, true, true, true, true};
    for(int i=0;i<11;i++){
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_PI_Controller_sample(variables,1.7f,values_iq[i],ext_clamping[i])*100)/100);
	}
}

void test_uz_PI_Controller_reset_assert_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_reset(NULL));
}

void test_uz_PI_Controller_sample_output_Reset(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
	//Compare values with Simulink Simulation
	float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_output[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
	for(int i=0;i<11;i++){
		TEST_ASSERT_EQUAL_FLOAT(values_output[i],roundf(uz_PI_Controller_sample(variables,1.0f,values_id[i],false)*100)/100);
	}
    uz_PI_Controller_reset(variables);
    TEST_ASSERT_EQUAL_FLOAT(0.32f,roundf(uz_PI_Controller_sample(variables,1.0f,0.953f,false)*100)/100);
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

#endif // TEST
