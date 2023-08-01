#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParaID_CleanPsiArray.h"
#include "CleanPsiArray_codegen.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };

void setUp(void)
{


}

void test_uz_CleanPsiArray_init_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_CleanPsiArray_init());
}

void test_uz_CleanPsiArray_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CleanPsiArray_step(NULL));
}

void test_uz_CleanPsiArray_set_OnlineID_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CleanPsiArray_set_OnlineID_output(NULL, ParaID_Data.OnlineID_Output));
}

void test_uz_CleanPsiArray_set_eta_c_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CleanPsiArray_set_eta_c(NULL, 0.5f));
}

void test_uz_CleanPsiArray_get_psi_array_out_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CleanPsiArray_get_psi_array_out(NULL));
}

void test_uz_CleanPsiArray_get_array_cleaned_flag_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CleanPsiArray_get_array_cleaned_flag(NULL));
}

void test_uz_CleanPsiArray_get_n_flux_points_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CleanPsiArray_get_n_flux_points(NULL));
}

#endif