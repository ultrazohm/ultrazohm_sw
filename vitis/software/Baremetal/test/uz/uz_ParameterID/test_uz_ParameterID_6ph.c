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

#include "uz_resonant_controller.h"
#include "../../../src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"

#include "uz_signals.h"
#include "rt_hypotf.h"

uz_ParameterID_Data_t Data_struct = {0};


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_ParameterID_6ph_init(void)
{
    uz_ParameterID_6ph_t* ParameterID_6ph_obj = uz_ParameterID_6ph_init(&Data_struct);
}

#endif