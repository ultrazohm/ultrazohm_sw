#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_ControlState.h"
#include "ControlState_codegen.h"
#include "uz_Transformation.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_ControlState_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_ControlState_init());
}

void test_uz_ControlState_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_step(NULL));
}

void test_uz_ControlState_set_finishedFrictionID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_finishedFrictionID(NULL, true));
}

void test_uz_ControlState_set_finishedElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_finishedElectricalID(NULL, true));
}

void test_uz_ControlState_set_finishedTwoMassID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_finishedTwoMassID(NULL, true));
}


void test_uz_ControlState_set_finishedFluxMapID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_finishedFluxMapID(NULL, true));
}

void test_uz_ControlState_set_enteredFrictionID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_enteredFrictionID(NULL, true));
}

void test_uz_ControlState_set_enteredFluxMapID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_enteredFluxMapID(NULL, true));
}

void test_uz_ControlState_set_enteredTwoMassID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_enteredTwoMassID(NULL, true));
}

void test_uz_ControlState_set_enteredElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_enteredElectricalID(NULL, true));
}

void test_uz_ControlState_set_enteredOnlineID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_enteredOnlineID(NULL, true));
}

void test_uz_ControlState_set_ElectricalID_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_ElectricalID_output(NULL, ParaID_Data.ElectricalID_Output));
}

void test_uz_ControlState_set_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_GlobalConfig(NULL, ParaID_Data.GlobalConfig));
}

void test_uz_ControlState_set_ElectricalID_FOC_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_set_ElectricalID_FOC_output(NULL, ParaID_Data.Controller_Parameters));
}

void test_uz_ControlState_get_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_get_GlobalConfig(NULL));
}

void test_uz_ControlState_get_ControlFlags_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ControlState_get_ControlFlags(NULL));
}
#endif