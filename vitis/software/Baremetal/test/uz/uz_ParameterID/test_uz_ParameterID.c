#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_PWM_SS_2L_hw.h"
#include "uz_ParameterID.h"
#include "uz_PID_ControlState.h"
#include "uz_PID_ElectricalID.h"
#include "uz_PID_TwoMassID.h"
#include "uz_PID_FrictionID.h"
#include "uz_PID_FluxMapID.h"
#include "uz_PID_OnlineID.h"
#include "uz_PID_CleanPsiArray.h"
#include "uz_PID_AutoRefCurrents.h"
#include "uz_PID_InterpMeshGrid.h"
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
#include "uz_FOC.h"
#include "uz_speedcontrol.h"
#include "uz_PWM_SS_2L.h" 
#include "uz_piController.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "uz_signals.h"


uz_ParameterID_Data_t PID_Data = { 0 };
void setUp(void)
{

}

void test_uz_ParameterID_step_NULL(void){
    uz_ParameterID_t* ParameterID = uz_ParameterID_init(&PID_Data);
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_step(NULL, &PID_Data));
}

void test_uz_ParameterID_step_Data_NULL(void){
    uz_ParameterID_t* ParameterID = uz_ParameterID_init(&PID_Data);
    TEST_ASSERT_FAIL_ASSERT(uz_ParameterID_step(ParameterID, NULL));
}

#endif