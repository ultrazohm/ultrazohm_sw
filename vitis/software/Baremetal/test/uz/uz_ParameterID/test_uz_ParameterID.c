#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_PWM_SS_2L_hw.h"
#include "uz_ParameterID.h"
#include "uz_ParaID_ControlState.h"
#include "uz_ParaID_ElectricalID.h"
#include "uz_ParaID_TwoMassID.h"
#include "uz_ParaID_FrictionID.h"
#include "uz_ParaID_FluxMapID.h"
#include "uz_ParaID_OnlineID.h"
#include "uz_ParaID_CleanPsiArray.h"
#include "uz_ParaID_AutoRefCurrents.h"
#include "uz_ParaID_InterpMeshGrid.h"
#include "ControlState_codegen.h"
#include "ElectricalID_codegen.h"
#include "TwoMassID_codegen.h"
#include "FrictionID_codegen.h"
#include "FluxMapID_codegen.h"
#include "OnlineID_codegen.h"
#include "AutoRefCurrents_codegen.h"
#include "CleanPsiArray_codegen.h"
#include "InterpMeshGrid_codegen.h"
#include "uz_Transformation.h"
#include "uz_CurrentControl.h"
#include "uz_speedcontrol.h"
#include "uz_setpoint.h"
#include "uz_PWM_SS_2L.h" 
#include "uz_piController.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "uz_signals.h"
#include "uz_newton_raphson.h"
#include "uz_space_vector_modulation.h"
#include "rt_nonfinite.h"
#include "eye_6olvtp5i.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

uz_ParameterID_Data_t ParaID_Data = { 0 };
struct uz_CurrentControl_config config = {0};
struct uz_SpeedControl_config config_n = {0};
struct uz_SetPoint_config config_sp = {0};
void setUp(void)
{
    //Have to be set to init FOC%SpeedControl to check individual asserts later. 
    //Therefore the init-functions have to be called
    config.config_id.samplingTime_sec = 0.00001f;
    config.config_id.upper_limit = 10.0f;
    config.config_id.lower_limit = -10.0f;
    config.config_iq.samplingTime_sec = 0.00001f;
    config.config_iq.upper_limit = 10.0f;
    config.config_iq.lower_limit = -10.0f;
    config.decoupling_select = no_decoupling;
    config.max_modulation_index = (1.0f / sqrtf(3.0f));
    config_n.config_controller.samplingTime_sec = 0.00001f;
    config_n.config_controller.upper_limit = 10.0f;
    config_n.config_controller.lower_limit = -10.0f;
    config_sp.config_PMSM.Ld_Henry = 0.1f;
    config_sp.config_PMSM.Lq_Henry = 0.1f;
    config_sp.config_PMSM.polePairs = 4.0f;
    config_sp.config_PMSM.I_max_Ampere = 10.0f;
    config_sp.config_PMSM.R_ph_Ohm = 0.3f;

}

void test_uz_ParameterID_step_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_step(NULL, &ParaID_Data));
}

void test_uz_ParameterID_step_Data_NULL(void){
    uz_ParameterID_t* ParameterID = uz_ParameterID_init(&ParaID_Data);
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_step(ParameterID, NULL));
}

void test_uz_ParameterID_init_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_init(NULL));
}

void test_uz_ParameterID_generate_DutyCycle_Data_NULL(void) {
    //ParaID_Data null pointer will be asserted first, therefore PWM can stay NULL too
    uz_3ph_dq_t input = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_generate_DutyCycle(NULL, input, NULL));
}

void test_uz_ParameterID_generate_DutyCycle_PWM_NULL(void) {
    uz_3ph_dq_t input = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_generate_DutyCycle(&ParaID_Data, input, NULL));
}

void test_uz_ParameterID_Controller_Data_NULL(void) {
    struct uz_ParameterID_controller obj = {
        .CC_instance_dq = uz_CurrentControl_init(config),
        .SC_instance = uz_SpeedControl_init(config_n),
        .SP_instance = uz_SetPoint_init(config_sp)};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_Controller(NULL, obj));
}

void test_uz_ParameterID_Controller_FOC_NULL(void) {
        struct uz_ParameterID_controller obj = {
        .CC_instance_dq = NULL,
        .SC_instance = uz_SpeedControl_init(config_n),
        .SP_instance = uz_SetPoint_init(config_sp)};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_Controller(&ParaID_Data, obj));
}

void test_uz_ParameterID_Controller_SC_NULL(void) {
        struct uz_ParameterID_controller obj = {
        .CC_instance_dq = uz_CurrentControl_init(config),
        .SC_instance = NULL,
        .SP_instance = uz_SetPoint_init(config_sp)};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_Controller(&ParaID_Data, obj));
}

void test_uz_ParameterID_Controller_SP_NULL(void) {
        struct uz_ParameterID_controller obj = {
        .CC_instance_dq = uz_CurrentControl_init(config),
        .SC_instance = uz_SpeedControl_init(config_n),
        .SP_instance = NULL};
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_Controller(&ParaID_Data, obj));
}

void test_uz_ParameterID_CleanPsiArray_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_CleanPsiArray(NULL, &ParaID_Data));
}

void test_uz_ParameterID_CleanPsiArray_Data_NULL(void) {
    uz_ParameterID_t* ParameterID = uz_ParameterID_init(&ParaID_Data);
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_CleanPsiArray(ParameterID, NULL));
}

void test_uz_ParameterID_CalcFluxMaps_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_CalcFluxMaps(NULL, &ParaID_Data));
}

void test_uz_ParameterID_CalcFluxMaps_Data_NULL(void) {
    uz_ParameterID_t* ParameterID = uz_ParameterID_init(&ParaID_Data);
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_CalcFluxMaps(ParameterID, NULL));
}

void test_uz_ParameterID_update_transmit_values_Data_NULL(void) {
    float activeState = 0.0f;
    float FluxMapCounter = 0.0f;
    float ArrayCounter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_update_transmit_values(NULL, &activeState, &FluxMapCounter, &ArrayCounter));
}

void test_uz_ParameterID_update_transmit_values_activeState_NULL(void) {
    float FluxMapCounter = 0.0f;
    float ArrayCounter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_update_transmit_values(&ParaID_Data, NULL, &FluxMapCounter, &ArrayCounter));
}

void test_uz_ParameterID_update_transmit_values_FluxCounter_NULL(void) {
    float activeState = 0.0f;
    float ArrayCounter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_update_transmit_values(&ParaID_Data, &activeState, NULL, &ArrayCounter));
}

void test_uz_ParameterID_update_transmit_values_ArrayCounter_NULL(void) {
    float activeState = 0.0f;
    float FluxMapCounter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_update_transmit_values(&ParaID_Data, &activeState, &FluxMapCounter, NULL));
}
#endif