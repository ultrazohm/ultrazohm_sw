#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"

uz_FOC_CurrentControl_config config_CurrentControl = {
    .Rs_mOhm = 80.0f,
    .Ld_mH = 0.5f,
    .Lq_mH = 0.5f,
    .Psi_PM_mVs = 7.5f,
    .polePairs = 2.0f,
    .iq_target_Ampere = 1.0f,
    .id_target_Ampere = 0.0f,
};

void test_uz_FOC_CurrentControl_init_instances(void){
    uz_FOC_CurrentControl_config config_CurrentControl2 = config_CurrentControl;
    TEST_ASSERT_PASS_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl2));
}

void test_uz_FOC_CurrentControl_init_Rs_valid(void){
    config_CurrentControl.Rs_mOhm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    config_CurrentControl.Rs_mOhm = 80.0f;
}

void test_uz_FOC_CurrentControl_init_Ld_valid(void){
    config_CurrentControl.Ld_mH = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    config_CurrentControl.Ld_mH = 0.5f;
}

void test_uz_FOC_CurrentControl_init_Lq_valid(void){
    config_CurrentControl.Lq_mH = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    config_CurrentControl.Lq_mH = 0.5f;
}

void test_uz_FOC_CurrentControl_init_Psi_PM_valid(void){
    config_CurrentControl.Psi_PM_mVs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    config_CurrentControl.Psi_PM_mVs = 7.5f;
}

void test_uz_FOC_CurrentControl_init_polePairs_valid(void){
    config_CurrentControl.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_CurrentControl_init(config_CurrentControl));
    config_CurrentControl.polePairs = 0.2f;
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

uz_FOC_SpeedControl_config config_SpeedControl = {
    .Rs_mOhm = 80.0f,
    .Ld_mH = 0.5f,
    .Lq_mH = 0.5f,
    .Psi_PM_mVs = 7.5f,
    .polePairs = 2.0f,
    .rotorInertia = 10.0f,
    .dampingFactor = 1000.0f,
    .n_target_rpm = 1000.0f,
};

void test_uz_FOC_SpeedControl_init_instances(void){
    uz_FOC_SpeedControl_config config_SpeedControl2 = config_SpeedControl;
    TEST_ASSERT_PASS_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl2));
}

void test_uz_FOC_SpeedControl_init_Rs_valid(void){
    config_SpeedControl.Rs_mOhm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.Rs_mOhm = 80.0f;
}

void test_uz_FOC_SpeedControl_init_Ld_valid(void){
    config_SpeedControl.Ld_mH = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.Ld_mH = 0.5f;
}

void test_uz_FOC_SpeedControl_init_Lq_valid(void){
    config_SpeedControl.Lq_mH = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.Lq_mH = 0.5f;
}

void test_uz_FOC_SpeedControl_init_Psi_PM_valid(void){
    config_SpeedControl.Psi_PM_mVs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.Psi_PM_mVs = 7.5f;
}

void test_uz_FOC_SpeedControl_init_polePairs_valid(void){
    config_SpeedControl.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.polePairs = 0.2f;
}

void test_uz_FOC_SpeedControl_init_dampingFactor_valid(void){
    config_SpeedControl.dampingFactor = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.dampingFactor = 1000.0f;
}

void test_uz_FOC_SpeedControl_init_rotorInertia_valid(void){
    config_SpeedControl.rotorInertia = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.rotorInertia = 10.0f;
}

void test_uz_FOC_SpeedControl_init_n_target_rpm_valid(void){
    config_SpeedControl.n_target_rpm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpeedControl_init(config_SpeedControl));
    config_SpeedControl.n_target_rpm = 1000.0f;
}


#endif // TEST
