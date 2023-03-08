#ifdef TEST

#include "unity.h"

#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"
#include "FluxMapID_6ph_codegen.c"

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

#include "mean_GqoxPyM9.h"



uz_ParaID_GlobalConfig_t GlobalConfig = {
    .PMSM_config.Ld_Henry = 0.001f,
    .PMSM_config.Lq_Henry = 0.002f,
    .PMSM_config.R_ph_Ohm = 0.1f,
    .PMSM_config.Psi_PM_Vs = 0.1f,
    .sampleTimeISR = 0.00001f,
    .PMSM_6ph_inductances.x = 0.001f,
    .PMSM_6ph_inductances.y = 0.003f
};

uz_ParaID_ActualValues_t ActualValues = {
    .i_dq_6ph.d = 1.0f,
    .i_dq_6ph.q = -1.0f,
    .i_dq_6ph.x = 1.0f,
    .i_dq_6ph.y = -1.0f,
    .i_dq_6ph.z1 = 1.0f,
    .i_dq_6ph.z2 = 1.0f,
    .V_DC = 100.0f,
    .theta_el = 0.0f,
    .omega_el = 100.0f,
};

uz_3ph_dq_t ref_pi = {0};

uz_ParaID_FluxMapID_extended_controller_output_t FluxmapID_extended_controller_Output = { 
    .ab_i_dq_PI_ref.d = 0.0f,
    .ab_i_dq_PI_ref.q = 0.0f,
    .ab_i_dq_PI_ref.zero = 0.0f,
    .xy_i_dq_PI_ref.d = 0.0f,
    .xy_i_dq_PI_ref.q = 0.0f,
    .xy_i_dq_PI_ref.zero = 0.0f,
    .selected_subsystem = 0
};

uz_ParameterID_Data_t ParaID_Data = { 0 };

uz_CurrentControl_t* CC_instance_1 = NULL;
uz_CurrentControl_t* CC_instance_2 = NULL;
uz_resonantController_t* res_instance_1 = NULL;
uz_resonantController_t* res_instance_2 = NULL;


void setUp(void)
{   
    ParaID_Data.GlobalConfig = GlobalConfig;
    ParaID_Data.FluxmapID_extended_controller_Output = &FluxmapID_extended_controller_Output;
    ParaID_Data.ActualValues = ActualValues;

    struct uz_CurrentControl_config cc_config = {
        	        .decoupling_select = no_decoupling,
        	        .config_id.Ki = ParaID_Data.GlobalConfig.Ki_id,
        	        .config_id.Kp = ParaID_Data.GlobalConfig.Kp_id,
        	        .config_id.samplingTime_sec = ParaID_Data.GlobalConfig.sampleTimeISR,
        	        .config_iq.Ki = ParaID_Data.GlobalConfig.Ki_iq,
        	        .config_iq.Kp = ParaID_Data.GlobalConfig.Kp_iq,
        	        .config_iq.samplingTime_sec = ParaID_Data.GlobalConfig.sampleTimeISR,
        	        .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config};
    struct uz_resonantController_config resonant_config = {
            .sampling_time = ParaID_Data.GlobalConfig.sampleTimeISR,
            .gain = 0.0f,
            .harmonic_order = 1.0f,
            .fundamental_frequency = 1.0f,
            .lower_limit = -10.0f,
            .upper_limit = 10.0f,
            .antiwindup_gain = 0.0f,
            .in_reference_value = 0.0f,
            .in_measured_value = 0.0f};
    CC_instance_1 = uz_CurrentControl_init(cc_config);
    CC_instance_2 = uz_CurrentControl_init(cc_config);
    res_instance_1 = uz_resonantController_init(resonant_config);
    res_instance_2 = uz_resonantController_init(resonant_config);
}

void tearDown(void)
{
}

void test_uz_FluxMapID_6ph_step_controllers(void)
{
    uz_6ph_dq_t flux_map_controller = uz_FluxMapID_6ph_step_controllers(&ParaID_Data, CC_instance_1, CC_instance_2, res_instance_1, res_instance_2);
}

#endif // TEST