#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"

uz_FOC_config config = {
	.Kp_id = 0.0f,
	.Kp_iq = 0.0f,
	.Kp_n = 0.0f,
	.Ki_id = 0.0f,
	.Ki_iq = 0.0f,
	.Ki_n = 0.0f,
	.iq_ref_Ampere = 0.0f,
	.id_ref_Ampere = 0.0f,
	.n_ref_rpm = 0.0f,
	.d_y_max = 0.0f,
	.d_y_min = 0.0f,
	.FOC_Select = false,
	.ResetIntegrators = false,
};
void test_uz_FOC_Dead_Zone_min_greater_than_max(void){
config.d_y_max=-10.0f;
config.d_y_min=10.0f;
TEST_ASSERT_FAIL_ASSERT(uz_FOC_Dead_Zone(2.0f,config));
config.d_y_max=10.0f;
config.d_y_min=-10.0f;
}

void test_uz_FOC_Dead_Zone_input_greather_than_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(10.0f,uz_FOC_Dead_Zone(20.0f,config));
}

void test_uz_FOC_Dead_Zone_input_smaller_than_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(-10.0f,uz_FOC_Dead_Zone(-20.0f,config));
}

void test_uz_FOC_Dead_Zone_input_inside_deadzone(void){
TEST_ASSERT_EQUAL_FLOAT(0.0f,uz_FOC_Dead_Zone(3.0f,config));
}

void test_FOC_get_sign_of_value_input_positive(void){
TEST_ASSERT_EQUAL_FLOAT(1,uz_FOC_get_sign_of_value(20.0f));
}

void test_FOC_get_sign_of_value_input_negative(void){
TEST_ASSERT_EQUAL_FLOAT(-1,uz_FOC_get_sign_of_value(-20.0f));
}

void test_FOC_get_sign_of_value_input_zero(void){
TEST_ASSERT_EQUAL_FLOAT(0,uz_FOC_get_sign_of_value(0.0f));
}

void test_uz_FOC_Clamping_Circuit_activate_clamping_false(void){
 TEST_ASSERT_EQUAL_FLOAT(false,uz_FOC_Clamping_Circuit(-0.03f,-0.05f,config));   
}

void test_uz_FOC_Clamping_Circuit_activate_clamping_true(void){
 TEST_ASSERT_EQUAL_FLOAT(true,uz_FOC_Clamping_Circuit(-30.0f,-25.0f,config));   
}
#endif // TEST
