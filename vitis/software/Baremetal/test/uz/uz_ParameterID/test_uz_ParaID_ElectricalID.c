#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_ElectricalID.h"
#include "ElectricalID_codegen.h"
#include "uz_Transformation.h"
#include "rt_hypotf.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_ElectricalID_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_ElectricalID_init());
}

void test_uz_ElectricalID_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_step(NULL));
}

void test_uz_ElectricalID_set_Config_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_set_Config(NULL, ParaID_Data.ElectricalID_Config));
}

void test_uz_ElectricalID_set_ActualValues_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_set_ActualValues(NULL, ParaID_Data.ActualValues));
}

void test_uz_ElectricalID_set_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_set_GlobalConfig(NULL, ParaID_Data.GlobalConfig));
}

void test_uz_ElectricalID_set_ControlFlags_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_set_ControlFlags(NULL, ParaID_Data.ControlFlags));
}

void test_uz_ElectricalID_get_enteredElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_get_enteredElectricalID(NULL));
}

void test_uz_ElectricalID_get_finishedElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_get_finishedElectricalID(NULL));
}

void test_uz_ElectricalID_get_FOC_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_get_FOC_output(NULL));
}

void test_uz_ElectricalID_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ElectricalID_get_output(NULL));
}

#endif