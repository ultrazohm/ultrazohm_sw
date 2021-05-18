#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"

uz_FOC_CurrentControl_config config_CurrentControl = {0};

void test_uz_FOC_CurrentControl_init_instances(void){
    uz_FOC_CurrentControl_config config_CurrentControl2 = config_CurrentControl;
    TEST_ASSERT_PASS_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl2));
}


//  void test_uz_FOC_CurrentControl_init_Kp_id_correct(void){
//      uz_FOC_CurrentControl_parameters* container = uz_FOC_CurrentControl_init(config_CurrentControl);
//      TEST_ASSERT_EQUAL_FLOAT(config_CurrentControl.Ld_mH * 20000, 10000);
// }

//--------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------//
//
//                      Speed Control
//
//--------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------//

uz_FOC_SpeedControl_config config_SpeedControl = {0};

void test_uz_FOC_SpeedControl_init_instances(void){
    uz_FOC_SpeedControl_config config_SpeedControl2 = config_SpeedControl;
    TEST_ASSERT_PASS_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl2));
}


#endif // TEST
