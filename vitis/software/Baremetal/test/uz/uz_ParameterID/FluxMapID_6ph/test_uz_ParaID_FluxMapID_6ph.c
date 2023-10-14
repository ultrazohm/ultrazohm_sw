#ifdef TEST

#include "unity.h"

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

void test_FluxMap_6ph_NeedToImplement(void)
{
    uz_FluxMapID_6ph_init();
}


#endif // TEST