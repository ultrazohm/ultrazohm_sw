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
    .PMSM_config.R_ph_Ohm = 0.003f
};

uz_3ph_dq_t i_reference_Ampere = {0};
uz_3ph_dq_t i_actual_Ampere = {
    .d = 3,
    .q = 3};
float V_dc_volts = 100;
float omega_el_rad_per_sec = 100;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_FluxMapID_6ph_init_controllers(void)
{
    struct uz_CurrentControl_config cc_config_1 = {
        .config_id.samplingTime_sec = 0.1f,
        .config_id.type = parallel,
        .config_iq.samplingTime_sec = 0.1f,
        .config_iq.type = parallel};
    uz_3ph_dq_t out = {0};
    uz_CurrentControl_t* CC_instance_1 = NULL;
    uz_CurrentControl_t* CC_instance_2 = NULL;
    uz_resonantController_t* resonant_1 = NULL;
    uz_resonantController_t* resonant_2 = NULL;
    uz_FluxMapID_6ph_init_controllers(GlobalConfig, &CC_instance_1, &CC_instance_2, &resonant_1, &resonant_2);
//    TEST_ASSERT_NOT_NULL(&CC_instance_1);
    CC_instance_1 = uz_CurrentControl_init(cc_config_1);
    TEST_ASSERT_NOT_NULL(CC_instance_1);
    out = uz_CurrentControl_sample(CC_instance_1, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    printf("\nout-d: %f, out-q: %f\n", out.d, out.q);
}

#endif // TEST
