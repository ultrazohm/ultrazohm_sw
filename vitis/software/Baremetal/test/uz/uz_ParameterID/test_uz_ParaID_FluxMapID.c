#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_FluxMapID.h"
#include "FluxMapID_codegen.h"
#include "uz_Transformation.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_FluxMapID_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_FluxMapID_init());
}

void test_uz_FluxMapID_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_step(NULL));
}

void test_uz_FluxMapID_set_Config_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_set_Config(NULL, ParaID_Data.FluxMapID_Config));
}

void test_uz_FluxMapID_set_ActualValues_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_set_ActualValues(NULL, ParaID_Data.ActualValues));
}

void test_uz_FluxMapID_set_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_set_GlobalConfig(NULL, ParaID_Data.GlobalConfig));
}

void test_uz_FluxMapID_set_ControlFlags_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_set_ControlFlags(NULL, ParaID_Data.ControlFlags));
}

void test_uz_FluxMapID_get_enteredFluxMapID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_get_enteredFluxMapID(NULL));
}

void test_uz_FluxMapID_get_finishedFluxMapID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_get_finishedFluxMapID(NULL));
}

void test_uz_FluxMapID_get_FOC_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_get_FOC_output(NULL));
}

void test_uz_FluxMapID_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_get_output(NULL));
}

#endif