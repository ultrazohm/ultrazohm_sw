#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"
#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

#ifdef TEST
#define INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE	1U
#define UZ_PWM_FREQUENCY                        10.0e3f
#endif

#define PARAMETERID6PH_FLUXMAP_LIMIT_PI 15.0f
#define PARAMETERID6PH_FLUXMAP_BANDWITH_CC 1000.0f
#define PARAMETERID6PH_FLUXMAP_RES_ORDER_AB 2.0f
#define PARAMETERID6PH_FLUXMAP_RES_ORDER_XY 6.0f
#define PARAMETERID6PH_FLUXMAP_ISR_FREQUENCY (UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)
#define PARAMETERID6PH_FLUXMAP_AC_SQUARED ((0.1f*2.0f*UZ_PIf*PARAMETERID6PH_FLUXMAP_ISR_FREQUENCY)*(0.1f*2.0f*UZ_PIf*PARAMETERID6PH_FLUXMAP_ISR_FREQUENCY))

struct uz_ParaID_FluxMapID_6ph_t {
    bool is_ready;
    ExtY_FluxMapID_6ph_codegen_t output;
    ExtU_FluxMapID_6ph_codegen_t input;
    DW_FluxMapID_6ph_codegen_t rtDW;
    RT_MODEL_FluxMapID_6ph_codege_t modelData;
    RT_MODEL_FluxMapID_6ph_codege_t *PtrToModelData;
};

static struct uz_resonantController_config resonant_config_1 = {
        .sampling_time = 1.0f,
        .gain = 0.0f,
        .harmonic_order = 1.0f,
        .fundamental_frequency = 1.0f,
        .lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .antiwindup_gain = 0.0f,
        .in_reference_value = 0.0f,
        .in_measured_value = 0.0f};
static struct uz_resonantController_config resonant_config_2 = {
        .sampling_time = 1.0f,
        .gain = 0.0f,
        .harmonic_order = 1.0f,
        .fundamental_frequency = 1.0f,
        .lower_limit = -1.0f*PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .upper_limit = PARAMETERID6PH_FLUXMAP_LIMIT_PI,
        .antiwindup_gain = 0.0f,
        .in_reference_value = 0.0f,
        .in_measured_value = 0.0f};

// resonant controller gain
static float kr_d = 0.0f;
static float kr_q = 0.0f;
static float kr_x = 0.0f;
static float kr_y = 0.0f;

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

void uz_FluxMapID_6ph_init_controllers(uz_ParaID_GlobalConfig_t GlobalConfig, uz_CurrentControl_t** CC_instance_1, uz_CurrentControl_t** CC_instance_2, uz_resonantController_t** res_instance_1, uz_resonantController_t** res_instance_2)
{
    // config for PI controller
    struct uz_CurrentControl_config cc_config_1 = {
        .decoupling_select = no_decoupling,
        .config_id.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*GlobalConfig.PMSM_config.Ld_Henry,
        .config_id.Kp = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*GlobalConfig.PMSM_config.R_ph_Ohm,
        .config_id.samplingTime_sec = GlobalConfig.sampleTimeISR,
        .config_iq.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*GlobalConfig.PMSM_config.Lq_Henry,
        .config_iq.Kp = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*GlobalConfig.PMSM_config.R_ph_Ohm,
        .config_iq.samplingTime_sec = GlobalConfig.sampleTimeISR,
        .config_PMSM = GlobalConfig.PMSM_config};

    // copy and adapt config of xy system PI controller
    struct uz_CurrentControl_config cc_config_2 = cc_config_1;

    // set sampletime to resontant controller config
    resonant_config_1.sampling_time = GlobalConfig.sampleTimeISR;
    resonant_config_2.sampling_time = GlobalConfig.sampleTimeISR;

    // set correct Ki for XY system
    cc_config_2.config_id.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*GlobalConfig.PMSM_6ph_inductances.x;
    cc_config_2.config_iq.Ki = PARAMETERID6PH_FLUXMAP_BANDWITH_CC*GlobalConfig.PMSM_6ph_inductances.y;

    // calculate resonant controller gains
    kr_d = 0.1f*PARAMETERID6PH_FLUXMAP_AC_SQUARED*GlobalConfig.PMSM_config.Ld_Henry;
    kr_q = 0.1f*PARAMETERID6PH_FLUXMAP_AC_SQUARED*GlobalConfig.PMSM_config.Lq_Henry;
    kr_x = 0.1f*PARAMETERID6PH_FLUXMAP_AC_SQUARED*GlobalConfig.PMSM_6ph_inductances.x;
    kr_y = 0.1f*PARAMETERID6PH_FLUXMAP_AC_SQUARED*GlobalConfig.PMSM_6ph_inductances.y;

    // initialize controllers
    *CC_instance_1 = uz_CurrentControl_init(cc_config_1);
    *CC_instance_2 = uz_CurrentControl_init(cc_config_2);
    *res_instance_1 = uz_resonantController_init(resonant_config_1);
    *res_instance_2 = uz_resonantController_init(resonant_config_2);
    uz_assert_not_NULL(*CC_instance_1);
    uz_assert_not_NULL(*CC_instance_2);
    uz_assert_not_NULL(*res_instance_1);
    uz_assert_not_NULL(*res_instance_2);
}

uz_6ph_dq_t uz_FluxMapID_6ph_step_controllers(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2)
{
    // Initialize output struct
        static uz_6ph_dq_t out = {0};

    // Splitting up the six-phase struct to subsystem structs
        // actual rotating 1st reference frame
        uz_3ph_dq_t actual_ab_rotating = {
            .d = Data->ActualValues.v_dq_6ph.d,
            .q = Data->ActualValues.v_dq_6ph.q};
        // actual stationary 2nd reference frame
        uz_3ph_alphabeta_t actual_xy_stationary = {
            .alpha = Data->ActualValues.v_dq_6ph.x,
            .beta = Data->ActualValues.v_dq_6ph.y};
        // actual rotating 2nd reference frame
        uz_3ph_dq_t actual_xy_rotating = uz_transformation_3ph_alphabeta_to_dq(actual_xy_stationary, -1.0f*Data->ActualValues.theta_el);

    // step PI controllers
    uz_3ph_dq_t cc_out_ab_rotating = uz_CurrentControl_sample(CC_instance_1, Data->FluxmapID_extended_controller_Output->ab_i_dq_PI_ref, actual_ab_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
    uz_3ph_dq_t cc_out_xy_rotating = uz_CurrentControl_sample(CC_instance_2, Data->FluxmapID_extended_controller_Output->xy_i_dq_PI_ref, actual_xy_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);

    // map outputs and step resonant controllers depending on current state inside FluxMapID
    switch(Data->FluxmapID_extended_controller_Output->selected_subsystem)
    {
        case 1: // control alpha beta system
        {
            // update resonant controller gain and harmonic order if it is not correct yet
            if((resonant_config_1.gain != kr_d) || (resonant_config_2.gain != kr_q) || (resonant_config_1.harmonic_order != PARAMETERID6PH_FLUXMAP_RES_ORDER_AB) || (resonant_config_2.harmonic_order != PARAMETERID6PH_FLUXMAP_RES_ORDER_AB))
            {
                resonant_config_1.gain = kr_d;
                resonant_config_1.harmonic_order = PARAMETERID6PH_FLUXMAP_RES_ORDER_AB;
                resonant_config_2.gain = kr_q;
                resonant_config_2.harmonic_order = PARAMETERID6PH_FLUXMAP_RES_ORDER_AB;
                uz_resonantController_set_config(resonant_1, resonant_config_1);
                uz_resonantController_set_config(resonant_2, resonant_config_2);
            }
            // assign to output
            out.d = cc_out_ab_rotating.d + uz_resonantController_step(resonant_1, 0.0f, Data->ActualValues.v_dq_6ph.d, Data->ActualValues.omega_el);
            out.q = cc_out_ab_rotating.q + uz_resonantController_step(resonant_2, 0.0f, Data->ActualValues.v_dq_6ph.q, Data->ActualValues.omega_el);
            uz_3ph_alphabeta_t cc_out_xy_stationary = uz_transformation_3ph_dq_to_alphabeta(cc_out_xy_rotating, -1.0f*Data->ActualValues.theta_el);
            out.x = cc_out_xy_stationary.alpha;
            out.y = cc_out_xy_stationary.beta;
            break;
        }
        case 2: // control xy system
        {
            // update resonant controller gain and harmonic order if it is not correct yet
            if((resonant_config_1.gain != kr_x) || (resonant_config_2.gain != kr_y) || (resonant_config_1.harmonic_order != PARAMETERID6PH_FLUXMAP_RES_ORDER_XY) || (resonant_config_2.harmonic_order != PARAMETERID6PH_FLUXMAP_RES_ORDER_XY))
            {
                resonant_config_1.gain = kr_x;
                resonant_config_1.harmonic_order = PARAMETERID6PH_FLUXMAP_RES_ORDER_XY;
                resonant_config_2.gain = kr_y;
                resonant_config_2.harmonic_order = PARAMETERID6PH_FLUXMAP_RES_ORDER_XY;
                uz_resonantController_set_config(resonant_1, resonant_config_1);
                uz_resonantController_set_config(resonant_2, resonant_config_2);
            }
            // assign to output
            out.d = cc_out_ab_rotating.d;
            out.q = cc_out_ab_rotating.q;
            cc_out_xy_rotating.d = cc_out_xy_rotating.d + uz_resonantController_step(resonant_1, 0.0f, actual_xy_rotating.d, Data->ActualValues.omega_el);
            cc_out_xy_rotating.q = cc_out_xy_rotating.q + uz_resonantController_step(resonant_2, 0.0f, actual_xy_rotating.q, Data->ActualValues.omega_el);
            uz_3ph_alphabeta_t cc_out_xy_stationary = uz_transformation_3ph_dq_to_alphabeta(cc_out_xy_rotating, -1.0f*Data->ActualValues.theta_el);
            out.x = cc_out_xy_stationary.alpha;
            out.y = cc_out_xy_stationary.beta;
            break;
        }
        default:
        {
            out.d = 0.0f;
            out.q = 0.0f;
            out.x = 0.0f;
            out.y = 0.0f;
            out.z1 = 0.0f;
            out.z2 = 0.0f;
            break;
        }
    } 
    return out;
}

#endif