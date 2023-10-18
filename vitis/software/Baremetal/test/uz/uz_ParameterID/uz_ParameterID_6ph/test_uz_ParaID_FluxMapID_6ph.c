#ifdef TEST

#include "unity.h"

#include "test_assert_with_exception.h"

#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"
#include "FluxMapID_6ph_codegen.c"

#include "uz_ParameterID_data.h"


#include "uz_resonant_controller.h"
#include "Resonant_Controller.h"
#include "uz_piController.h"
#include "uz_CurrentControl.h"
#include "uz_speedcontrol.h"
#include "uz_setpoint.h"
#include "uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "uz_signals.h"
#include "uz_newton_raphson.h"

#include "mean_GqoxPyM9.h"






void setUp(void)
{   
}

void tearDown(void)
{
}

void test_uz_FluxMapID_6ph_init(void) {
    TEST_ASSERT_PASS_ASSERT(uz_FluxMapID_6ph_init());
}

void test_uz_FluxMapID_6ph_step_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_6ph_step(NULL));
}

void test_uz_FluxMapID_6ph_set_Config(void){
    uz_ParaID_FluxMapIDConfig_t Config = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_6ph_set_Config(NULL, Config));
}

void test_uz_FluxMapID_6ph_set_ActualValues(void){
    uz_ParaID_ActualValues_t ActualValues = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_6ph_set_ActualValues(NULL, ActualValues));
}

void test_uz_FluxMapID_6ph_set_GlobalConfig(void){
    uz_ParaID_GlobalConfig_t Config = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_6ph_set_GlobalConfig(NULL, Config));
}

void test_uz_FluxMapID_6ph_set_ControlFlags(void){
    TEST_ASSERT_FAIL_ASSERT(uz_FluxMapID_6ph_set_ControlFlags(NULL, NULL));
}

void test_uz_FluxMapID_6ph_get_enteredFluxMapID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_FluxMapID_6ph_entered(NULL));
}

void test_uz_FluxMapID_6ph_get_finishedFluxMapID_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_FluxMapID_6ph_finished(NULL));
}

void test_uz_FluxMapID_6ph_get_FOC_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_FluxMapID_6ph_FOCoutput(NULL));
}

void test_uz_FluxMapID_6ph_get_output_not_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_get_FluxMapID_6ph_output(NULL));
}

#endif // TEST