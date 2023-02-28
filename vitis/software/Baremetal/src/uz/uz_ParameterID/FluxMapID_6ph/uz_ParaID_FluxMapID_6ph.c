#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"
#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

struct uz_ParaID_FluxMapID_6ph_t {
    bool is_ready;
    ExtY_FluxMapID_6ph_codegen_t output;
    ExtU_FluxMapID_6ph_codegen_t input;
    DW_FluxMapID_6ph_codegen_t rtDW;
    RT_MODEL_FluxMapID_6ph_codege_t modelData;
    RT_MODEL_FluxMapID_6ph_codege_t *PtrToModelData;
};

static uint32_t instance_counter = 0U;
static uz_ParaID_FluxMapID_6ph_t instances[UZ_PARAMETERID_6PH_MAX_INSTANCES] = { 0 };

static uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_allocation(void);

static uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_6PH_MAX_INSTANCES);
    uz_ParaID_FluxMapID_6ph_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_init(void) {
    uz_ParaID_FluxMapID_6ph_t* self = uz_FluxMapID_6ph_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->dwork=&self->rtDW;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    FluxMapID_6ph_codegen_initialize(self->PtrToModelData);
    return (self);
    return (self);
}

void uz_FluxMapID_6ph_step(uz_ParaID_FluxMapID_6ph_t* self, uz_ParaID_FluxMapIDConfig_t ID_config, uz_ParaID_ActualValues_t actual, uz_ParaID_GlobalConfig_t global_config, uz_ParaID_ControlFlags_t flags){
    self->input.FluxMapIDConfig=ID_config;
    self->input.ActualValues=actual;
    self->input.GlobalConfig_out=global_config;
    self->input.ControlFlags=flags;
    FluxMapID_6ph_codegen_step(self->PtrToModelData);
}

bool uz_get_FluxMapID_6ph_entered(uz_ParaID_FluxMapID_6ph_t* self)
{
    return self->output.enteredFluxMapID;
}

bool uz_get_FluxMapID_6ph_finished(uz_ParaID_FluxMapID_6ph_t* self)
{
    return self->output.finishedFluxMapID;
}

uz_ParaID_Controller_Parameters_output_t* uz_get_FluxMapID_6ph_FOCoutput(uz_ParaID_FluxMapID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_FOC_output);
}

uz_ParaID_FluxMapID_output_t* uz_get_FluxMapID_6ph_output(uz_ParaID_FluxMapID_6ph_t* self)
{
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_output);
}

void uz_FluxMapID_6ph_init_controllers(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* res_instance_1, uz_resonantController_t* res_instance_2)
{
    struct uz_CurrentControl_config cc_config_1 = {
        .decoupling_select = no_decoupling,
        .config_id.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.PMSM_config.Ld_Henry,
        .config_id.Kp = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.PMSM_config.R_ph_Ohm,
        .config_id.samplingTime_sec = Data->GlobalConfig.sampleTimeISR,
        .config_id.type = parallel,
        .config_id.lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .config_id.upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .config_iq.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.PMSM_config.Lq_Henry,
        .config_iq.Kp = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.PMSM_config.R_ph_Ohm,
        .config_iq.samplingTime_sec = Data->GlobalConfig.sampleTimeISR,
        .config_iq.type = parallel,
        .config_iq.lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .config_iq.upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI};
    struct uz_CurrentControl_config cc_config_2 = {
        .decoupling_select = no_decoupling,
        //.config_id.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.Lx_Henry,
        .config_id.Kp = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.PMSM_config.R_ph_Ohm,
        .config_id.samplingTime_sec = Data->GlobalConfig.sampleTimeISR,
        .config_id.type = parallel,
        .config_id.lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .config_id.upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        //.config_iq.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.Ly_Henry,
        .config_iq.Kp = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*Data->GlobalConfig.PMSM_config.R_ph_Ohm,
        .config_iq.samplingTime_sec = Data->GlobalConfig.sampleTimeISR,
        .config_iq.type = parallel,
        .config_iq.lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .config_iq.upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI};
    struct uz_resonantController_config resonant_config_1 = {
        .sampling_time = Data->GlobalConfig.sampleTimeISR,
        //.gain = 1.0f,
        //.harmonic_order = 99.0f,
        .fundamental_frequency = 1.0f
        .lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        //.antiwindup_gain = 1.0f,
        .in_reference_value = 0.0f,
        .in_measured_value = 0.0f};
    struct uz_resonantController_config resonant_config_2 = {0};
    CC_instance_1 = uz_CurrentControl_init(cc_config_1);
    CC_instance_2 = uz_CurrentControl_init(cc_config_2);
    res_instance_1 = uz_resonantController_init(resonant_config_1);
    res_instance_2 = uz_resonantController_init(resonant_config_2);
}

uz_6ph_dq_t uz_FluxMapID_6ph_step_controllers(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2)
{
    // output struct
    uz_6ph_dq_t out = {0};
    // struct holding controller output for 1st and 2nd reference frames
    uz_3ph_dq_t cc_out_ab = {0};
    uz_3ph_dq_t cc_out_xy = {0};
    float res_out_1 = 0.0f;
    float res_out_2 = 0.0f;
    // actual rotating 1st reference frame
    uz_3ph_dq_t actual_ab = {
        .d = Data->ActualValues.v_dq_6ph.d,
        .q = Data->ActualValues.v_dq_6ph.q};
    // actual stationary 2nd reference frame
    uz_3ph_alphabeta_t actual_xy_stationary = {
        .alpha = Data->ActualValues.v_dq_6ph.x,
        .beta = Data->ActualValues.v_dq_6ph.y};
    // actual rotating 2nd reference frame
    uz_3ph_dq_t actual_xy = uz_transformation_3ph_alphabeta_to_dq(actual_xy_stationary, -1.0f*Data->ActualValues.theta_el);
    switch(Data->FluxmapID_extended_controller_Output->selected_subsystem)
    {
        // control alpha beta system
        case 1:
        {
            cc_out_ab = uz_CurrentControl_sample(CC_instance_1, Data->FluxmapID_extended_controller_Output->ab_i_dq_PI_ref, actual_ab, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
            cc_out_xy = uz_CurrentControl_sample(CC_instance_2, Data->FluxmapID_extended_controller_Output->xy_i_dq_PI_ref, actual_xy, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
            res_out_1 = uz_resonantController_step(resonant_1, 0.0f, Data->ActualValues.v_dq_6ph.alpha?, Data->ActualValues.omega_el);
            res_out_2 = uz_resonantController_step(resonant_2, 0.0f, Data->ActualValues.v_dq_6ph.alpha?, Data->ActualValues.omega_el);
            break;
        }
        default:
            break:
    }
}

#endif