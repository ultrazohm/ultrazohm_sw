#ifdef TEST


#include "unity.h"
#include "test_assert_with_exception.h"

#include "uz_ParameterID_6ph.h"
#include "uz_ParameterID.h"

#include "uz_ParaID_ControlState.h"
#include "ControlState_codegen.h"

#include "uz_ParaID_TwoMassID.h"
#include "TwoMassID_codegen.h"

#include "uz_ParaID_FrictionID.h"
#include "FrictionID_codegen.h"

#include "uz_ParaID_ElectricalID_6ph.h"
#include "ElectricalID_6ph_codegen.h"

#include "uz_ParaID_ElectricalID.h"
#include "ElectricalID_codegen.h"

#include "uz_ParaID_Frequency_Analysis.h"
#include "FFTImplementationCallback.h"

#include "FFTRecordedVoltage.h"
#include "uz_complex.h"

#include "uz_ParaID_OnlineID.h"
#include "uz_ParaID_CleanPsiArray.h"
#include "uz_ParaID_AutoRefCurrents.h"
#include "uz_ParaID_InterpMeshGrid.h"
#include "OnlineID_codegen.h"
#include "AutoRefCurrents_codegen.h"
#include "CleanPsiArray_codegen.h"
#include "InterpMeshGrid_codegen.h"

#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

#include "uz_ParaID_FluxMapID.h"
#include "FluxMapID_codegen.h"

#include "uz_ParaID_AutoRefCurrents.h"
#include "uz_ParaID_CleanPsiArray.h"
#include "uz_ParaID_InterpMeshGrid.h"
#include "AutoRefCurrents_codegen.h"
#include "CleanPsiArray_codegen.h"
#include "InterpMeshGrid_codegen.h"

#include "uz_ParaID_OnlineID.h"
#include "OnlineID_codegen.h"

#include "uz_newton_raphson.h"
#include "uz_piController.h"
#include "uz_CurrentControl.h"
#include "uz_speedcontrol.h"
#include "uz_setpoint.h"
#include "uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "mock_uz_PWM_SS_2L_hw.h"
#include "uz_PWM_SS_2L.h" 
#include "mock_uz_AXI.h" 
#include "uz_space_vector_modulation.h"
#include "uz_spwm.h"
#include "uz_controller_setpoint_filter.h"

#include "uz_subspace_resonant_control.h"
#include "uz_resonant_controller.h"
#include "uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"

#include "rt_hypotf.h"
#include "eye_6olvtp5i.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "mean_GqoxPyM9.h"
#include "rtGetNaN.h"
#include "rtGetInf.h"

#include "uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"
#include "mock_uz_SystemTime.h"
#include "uz_filter_cumulativeavg.h"
#include "uz_signals.h"

#include "uz_signals_iir_filter.c"



uz_ParameterID_Data_t Data_struct = {0};


void setUp(void)
{
}

void tearDown(void)
{
}

// tests for uz_ParameterID_6ph_init

void test_uz_ParameterID_6ph_init(void)
{
    uz_ParameterID_6ph_t* ParameterID_6ph_obj = uz_ParameterID_6ph_init(&Data_struct);
    TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj);
}

void test_uz_ParameterID_6ph_init_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_init(NULL));
}

// tests for uz_ParameterID_6ph_step

void test_uz_ParameterID_6ph_step_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_step(NULL, &Data_struct));
}

void test_uz_ParameterID_6ph_step_Data_NULL(void){
    uz_ParameterID_6ph_t* ParameterID = uz_ParameterID_6ph_init(&Data_struct);
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_step(ParameterID, NULL));
}

// init others
void test_uz_ParameterID_6ph_initialize_encoder_offset_estimation(void){
    float ptr;
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_initialize_encoder_offset_estimation(&Data_struct, NULL));
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_initialize_encoder_offset_estimation(NULL, &ptr));
}

void test_uz_ParameterID_6ph_initialize_filter(void){
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_initialize_filter(NULL, 0.1f));
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_initialize_filter(&Data_struct, 0.0f));
}

// other
void test_uz_uz_ParameterID_6ph_process_actual_values(void){
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_process_actual_values(NULL, 0.0f, 0.0f));
}

void test_uz_ParameterID_generate_DutyCycle_Data_NULL(void) {
    uz_6ph_dq_t input = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_generate_DutyCycle(NULL, input));
}

void test_uz_ParameterID_6ph_calculate_PsiPMs_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_calculate_PsiPMs(NULL, NULL, NULL));
}

void test_uz_ParameterID_6ph_Controller_NULL(void) {
    struct uz_ParameterID_controller object = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_Controller(NULL, object));
}

// tests for uz_ParameterID_6ph_update_transmit_values
void test_uz_ParameterID_6ph_update_transmit_values_Data_NULL(void) {
    float activeState = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_update_transmit_values(NULL, &activeState));
}

void test_uz_ParameterID_6ph_update_transmit_values_activeState_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_6ph_update_transmit_values(&Data_struct, NULL));
}

#endif