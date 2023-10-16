#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "uz_ParaID_ElectricalID_6ph.h"
#include "ElectricalID_6ph_codegen.h"
#include "rt_hypotf.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_ElectricalID_6ph_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_ElectricalID_6ph_init());
}

void test_uz_FluxMapID_6ph_step_not_NULL(void) {
    uz_ParaID_ElectricalIDConfig_t ID_config = {0};
    uz_ParaID_ActualValues_t av = {0};
    uz_ParaID_GlobalConfig_t gc = {0};
    uz_ParaID_ControlFlags_t flags = {0};
    uz_ParaID_ElectricalID_fft_in_t fft_in = {0};
    uz_ParaID_ElectricalID_offset_estimation_t offset_est_in = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_6ph_step(NULL, ID_config, av, gc, flags, fft_in, offset_est_in));
}

void test_uz_ElectricalID_6ph_get_enteredElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_entered(NULL));
}

void test_uz_ElectricalID_6ph_get_finishedElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_finished(NULL));
}

void test_uz_ElectricalID_6ph_get_FOC_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_FOCoutput(NULL));
}

void test_uz_ElectricalID_6ph_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_output(NULL));
}

void test_uz_get_ElectricalID_6ph_fft_out(void){
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_fft_out(NULL, NULL));
}

void test_uz_get_ElectricalID_6ph_finished_voltage_measurement(void){
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_finished_voltage_measurement(NULL));
}

#endif // TEST
