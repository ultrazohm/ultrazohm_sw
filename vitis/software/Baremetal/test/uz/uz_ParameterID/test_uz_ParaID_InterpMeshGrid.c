#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_InterpMeshGrid.h"
#include "InterpMeshGrid_codegen.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_InterpMeshGrid_init_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_InterpMeshGrid_init());
}

void test_uz_InterpMeshGrid_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_InterpMeshGrid_step(NULL));
}

void test_uz_InterpMeshGrid_set_psi_array_not_NULL(void) {
    float data[600] = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_InterpMeshGrid_set_psi_array(NULL, data));
}

void test_uz_InterpMeshGrid_set_i_rat_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_InterpMeshGrid_set_i_rat(NULL, 0.5f));
}

void test_uz_InterpMeshGrid_set_OnlineID_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_InterpMeshGrid_set_OnlineID_output(NULL, ParaID_Data.OnlineID_Output));
}

void test_uz_InterpMeshGrid_get_FluxMapData_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_InterpMeshGrid_get_FluxMapData(NULL));
}

#endif