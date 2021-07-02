#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PI_controller.h"


void test_uz_PI_Controller_Dead_Zone_input_greather_than_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(10.0f,uz_PI_Controller_Dead_Zone(20.0f, 10.0f, -10.0f));
}

void test_uz_PI_Controller_Dead_Zone_input_smaller_than_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(-10.0f,uz_PI_Controller_Dead_Zone(-20.0f, 10.0f, -10.0f));
}

void test_uz_PI_Controller_Dead_Zone_input_inside_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(0.0f,uz_PI_Controller_Dead_Zone(3.0f, 10.0f, -10.0f));
}

void test_uz_PI_Controller_get_sign_of_value_input_positive(void){
TEST_ASSERT_EQUAL_FLOAT(1,uz_PI_Controller_get_sign_of_value(20.0f));
}

void test_uz_PI_Controller_get_sign_of_value_input_negative(void){
TEST_ASSERT_EQUAL_FLOAT(-1,uz_PI_Controller_get_sign_of_value(-20.0f));
}

void test_uz_PI_Controller_get_sign_of_value_input_zero(void){
TEST_ASSERT_EQUAL_FLOAT(0,uz_PI_Controller_get_sign_of_value(0.0f));
}

void test_uz_PI_Controller_Clamping_Circuit_activate_clamping_false(void){
 TEST_ASSERT_EQUAL_FLOAT(false,uz_PI_Controller_Clamping_Circuit(-0.03f,-0.05f, 10.0f, -10.0f));   
}

void test_uz_PI_Controller_Clamping_Circuit_activate_clamping_true(void){
 TEST_ASSERT_EQUAL_FLOAT(true,uz_PI_Controller_Clamping_Circuit(-30.0f,-25.0f, 10.0f, -10.0f));   
}

uz_PI_Controller_config config = {
    .Kp = 10.0f,
    .Ki = 10.0f,
    .samplingTime_sec = 0.001f,
    .d_y_max = 10.0f,
    .d_y_min = -10.0f
};

void test_uz_PI_Controller_init_Ki_negative(void){
    config.Ki = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_Ki_zero(void){
    config.Ki = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.Ki = 2000.0f;
}

void test_uz_PI_Controller_init_Kp_negative(void){
    config.Kp = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_Kp_zero(void){
    config.Kp = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.Kp = 6.75f;
}

void test_uz_PI_Controller_init_samplingTime_negative(void){
    config.samplingTime_sec = -0.0001f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
}

void test_uz_PI_Controller_init_samplingTime_zero(void){
    config.samplingTime_sec = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_init(config));
    config.samplingTime_sec = 0.00001f;
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

void test_uz_PI_Controller_reset_NULL(void){
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

void test_uz_PI_Controller_set_Ki_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Ki(NULL, 10.0f));
}

void test_uz_PI_Controller_set_Ki_negative(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Ki(variables, -10.0f));
}

void test_uz_PI_Controller_set_Ki_zero(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Ki(variables, 0.0f));
}

void test_uz_PI_Controller_set_Kp_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Kp(NULL, 10.0f));
}

void test_uz_PI_Controller_set_Kp_negative(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Kp(variables, -10.0f));
}

void test_uz_PI_Controller_set_Kp_zero(void){
    uz_PI_Controller* variables = uz_PI_Controller_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_PI_Controller_set_Kp(variables, 0.0f));
}
    #endif // TEST
