#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "uz_ParameterID_6ph.h"

#include "uz_ParaID_ControlState.h"
#include "ControlState_codegen.h"

#include "uz_ParaID_TwoMassID.h"
#include "TwoMassID_codegen.h"

#include "uz_ParaID_FrictionID.h"
#include "FrictionID_codegen.h"

#include "uz_ParaID_ElectricalID_6ph.h"
#include "ElectricalID_6ph_codegen.h"

#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

#include "AutoRefCurrents_codegen.h"
#include "CleanPsiArray_codegen.h"
#include "InterpMeshGrid_codegen.h"

#include "uz_ParaID_OnlineID.h"
#include "OnlineID_codegen.h"

#include "uz_FOC.h"
#include "uz_speedcontrol.h"
#include "uz_piController.h"
#include "uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "uz_signals.h"

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