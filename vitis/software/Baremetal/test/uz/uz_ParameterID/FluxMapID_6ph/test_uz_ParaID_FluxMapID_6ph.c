#ifdef TEST

#include "unity.h"

#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

#include "uz_ParameterID_data.h"


#include "uz_resonant_controller.h"
#include "../../../src/uz/uz_ResonantController/Resonant_Controller_ert_rtw/Resonant_Controller.h"
#include "uz_piController.h"
#include "uz_CurrentControl.h"
#include "uz_speedcontrol.h"
#include "uz_setpoint.h"
#include "uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "uz_signals.h"
#include "uz_newton_raphson.h"

uz_ParaID_GlobalConfig_t GlobalConfig = {
    .PMSM_config.Ld_Henry = 0.001f,
    .PMSM_config.Lq_Henry = 0.002f,
    .PMSM_config.R_ph_Ohm = 0.1f,
    .sampleTimeISR = 0.00001f,
    .PMSM_6ph_inductances.x = 0.001f,
    .PMSM_6ph_inductances.y = 0.003f
};

void setUp(void)
{   
}

void tearDown(void)
{
}

void test_uz_FluxMapID_6ph_init_controllers(void)
{
    uz_CurrentControl_t* CC_instance_1 = NULL;
    uz_CurrentControl_t* CC_instance_2 = NULL;
    uz_resonantController_t* resonant_1 = NULL;
    uz_resonantController_t* resonant_2 = NULL;
    uz_FluxMapID_6ph_init_controllers(GlobalConfig, &CC_instance_1, &CC_instance_2, &resonant_1, &resonant_2);
    TEST_ASSERT_NOT_NULL(CC_instance_1);
    TEST_ASSERT_NOT_NULL(CC_instance_2);
    TEST_ASSERT_NOT_NULL(resonant_1);
    TEST_ASSERT_NOT_NULL(resonant_2);
}

#endif // TEST
