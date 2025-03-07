#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_AutoRefCurrents.h"
#include "AutoRefCurrents_codegen.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_AutoRefCurrents_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_AutoRefCurrents_init());
}

void test_uz_AutoRefCurrents_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_AutoRefCurrents_step(NULL));
}

void test_uz_AutoRefCurrents_set_Config_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_AutoRefCurrents_set_Config(NULL, ParaID_Data.AutoRefCurrents_Config));
}

void test_uz_AutoRefCurrents_set_ActualValues_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_AutoRefCurrents_set_ActualValues(NULL, ParaID_Data.ActualValues));
}

void test_uz_AutoRefCurrents_set_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_AutoRefCurrents_set_GlobalConfig(NULL, ParaID_Data.GlobalConfig));
}

void test_uz_AutoRefCurrents_set_ControlFlags_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_AutoRefCurrents_set_ControlFlags(NULL, ParaID_Data.ControlFlags));
}

void test_uz_AutoRefCurrents_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_AutoRefCurrents_get_output(NULL));
}

#endif