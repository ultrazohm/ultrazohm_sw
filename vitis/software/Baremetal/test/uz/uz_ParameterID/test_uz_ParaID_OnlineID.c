#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_OnlineID.h"
#include "uz_ParaID_AutoRefCurrents.h"
#include "uz_ParaID_CleanPsiArray.h"
#include "uz_ParaID_InterpMeshGrid.h"
#include "AutoRefCurrents_codegen.h"
#include "CleanPsiArray_codegen.h"
#include "InterpMeshGrid_codegen.h"
#include "OnlineID_codegen.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_OnlineID_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_OnlineID_init());
}

void test_uz_OnlineID_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_step(NULL));
}

void test_uz_OnlineID_set_Config_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_Config(NULL, ParaID_Data.OnlineID_Config));
}

void test_uz_OnlineID_set_ActualValues_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_ActualValues(NULL, ParaID_Data.ActualValues));
}

void test_uz_OnlineID_set_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_GlobalConfig(NULL, ParaID_Data.GlobalConfig));
}

void test_uz_OnlineID_set_ControlFlags_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_ControlFlags(NULL, ParaID_Data.ControlFlags));
}

void test_uz_OnlineID_set_cleaned_psi_array_not_NULL(void) {
    float test[600] = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_cleaned_psi_array(NULL, test));
}

void test_uz_OnlineID_get_enteredOnlineID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_get_enteredOnlineID(NULL));
}

void test_uz_OnlineID_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_get_output(NULL));
}

void test_uz_OnlineID_CleanPsiArray_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_CleanPsiArray(NULL, &ParaID_Data));
}

void test_uz_OnlineID_CleanPsiArray_Data_not_NULL(void) {
    uz_ParaID_OnlineID_t* instance = uz_OnlineID_init();
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_CleanPsiArray(instance, NULL));
}

void test_uz_OnlineID_CalcFluxMaps_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_CalcFluxMaps(NULL, &ParaID_Data));
}

void test_uz_OnlineID_CalcFluxMaps_Data_not_NULL(void) {
    uz_ParaID_OnlineID_t* instance = uz_OnlineID_init();
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_CalcFluxMaps(instance, NULL));
}

void test_uz_OnlineID_AutoRefCurrents_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_AutoRefCurrents_step(NULL, &ParaID_Data));
}

void test_uz_OnlineID_AutoRefCurrents_step_Data_not_NULL(void) {
    uz_ParaID_OnlineID_t* instance = uz_OnlineID_init();
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_AutoRefCurrents_step(instance, NULL));
}

void test_uz_OnlineID_set_AutoRefCurrents_Config_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_AutoRefCurrents_Config(NULL, ParaID_Data.AutoRefCurrents_Config));
}

void test_uz_OnlineID_set_AutoRefCurrents_GlobalConfig_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_AutoRefCurrents_GlobalConfig(NULL, ParaID_Data.GlobalConfig));
}

void test_uz_OnlineID_set_AutoRefCurrents_ControlFlags_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_set_AutoRefCurrents_ControlFlags(NULL, ParaID_Data.ControlFlags));
}

void test_uz_OnlineID_get_InterpMeshGrid_FluxMapData_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_OnlineID_get_InterpMeshGrid_FluxMapData(NULL));
}

#endif