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

void test_uz_ElectricalID_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_ElectricalID_6ph_init());
}


void test_uz_ElectricalID_get_enteredElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_entered(NULL));
}

void test_uz_ElectricalID_get_finishedElectricalID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_finished(NULL));
}

void test_uz_ElectricalID_get_FOC_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_FOCoutput(NULL));
}

void test_uz_ElectricalID_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_output(NULL));
}

void test_uz_get_ElectricalID_6ph_fft_out(void){
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_fft_out(NULL, NULL));
}

void test_uz_get_ElectricalID_6ph_finished_voltage_measurement(void){
    TEST_ASSERT_FAIL_ASSERT(uz_get_ElectricalID_6ph_finished_voltage_measurement(NULL));
}

#endif // TEST
