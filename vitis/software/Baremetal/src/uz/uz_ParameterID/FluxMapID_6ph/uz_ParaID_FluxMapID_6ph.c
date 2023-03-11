#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"
#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

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

void uz_FluxMapID_6ph_step(uz_ParaID_FluxMapID_6ph_t* self, uz_ParaID_FluxMapIDConfig_t ID_config, uz_ParaID_ActualValues_t actual, uz_ParaID_GlobalConfig_t global_config, uz_ParaID_ControlFlags_t flags, bool feedback_printed){
    self->input.FluxMapIDConfig=ID_config;
    self->input.ActualValues=actual;
    self->input.GlobalConfig_out=global_config;
    self->input.ControlFlags=flags;
    self->input.feedback_printed=feedback_printed;
    FluxMapID_6ph_codegen_step(self->PtrToModelData);
}

bool uz_get_FluxMapID_6ph_entered(uz_ParaID_FluxMapID_6ph_t* self){
    return self->output.enteredFluxMapID;
}

bool uz_get_FluxMapID_6ph_finished(uz_ParaID_FluxMapID_6ph_t* self){
    return self->output.finishedFluxMapID;
}

uz_ParaID_Controller_Parameters_output_t* uz_get_FluxMapID_6ph_FOCoutput(uz_ParaID_FluxMapID_6ph_t* self){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_FOC_output);
}

uz_ParaID_FluxMapID_output_t* uz_get_FluxMapID_6ph_output(uz_ParaID_FluxMapID_6ph_t* self){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(&self->output.FluxMapID_output);
}

uz_ParaID_FluxMapID_extended_controller_output_t* uz_get_FluxMapID_6ph_extended_controller_output(uz_ParaID_FluxMapID_6ph_t* self){
	uz_assert_not_NULL(self);
		uz_assert(self->is_ready);
		return(&self->output.extended_controller_output);
}

uz_6ph_dq_t uz_FluxMapID_6ph_step_controllers(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2)
{
    // assert input pointers
        uz_assert_not_NULL(CC_instance_1);
        uz_assert_not_NULL(CC_instance_2);
        uz_assert_not_NULL(resonant_1);
        uz_assert_not_NULL(resonant_2);

    // Initialize output struct
        static uz_6ph_dq_t out = {0};

    // Splitting up the six-phase struct to subsystem structs
        // actual stationary 2nd reference frame
        uz_3ph_alphabeta_t actual_xy_stationary = {
            .alpha = Data->ActualValues.i_dq_6ph.x,
            .beta = Data->ActualValues.i_dq_6ph.y};
        // actual rotating 2nd reference frame
        uz_3ph_dq_t actual_xy_rotating = uz_transformation_3ph_alphabeta_to_dq(actual_xy_stationary, -1.0f*Data->ActualValues.theta_el);

    // calculate resonant controller gains
        static uint16_t initialized_controllers = 0U;
        static float tau_sum = 2*0.0001f;

    // map outputs and step resonant controllers depending on current state inside FluxMapID
    switch(Data->FluxmapID_extended_controller_Output->selected_subsystem)
    {
        case 1: // control alpha beta system
        {
            uz_3ph_dq_t cc_out_ab_rotating = uz_CurrentControl_sample(CC_instance_1, Data->FluxmapID_extended_controller_Output->ab_i_dq_PI_ref, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
            uz_3ph_dq_t cc_out_xy_rotating = uz_CurrentControl_sample(CC_instance_2, Data->FluxmapID_extended_controller_Output->xy_i_dq_PI_ref, actual_xy_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);

            // update resonant controller gain and harmonic order if it is not correct yet
            if(initialized_controllers != 1U)
            {
                // reset all
                uz_CurrentControl_reset(CC_instance_1);
                uz_CurrentControl_reset(CC_instance_2);
                uz_resonantController_reset(resonant_1);
                uz_resonantController_reset(resonant_2);
                // set cc1
                uz_CurrentControl_set_Kp_id(CC_instance_1, Data->GlobalConfig.PMSM_config.Ld_Henry/(2.0f*tau_sum));
                uz_CurrentControl_set_Kp_iq(CC_instance_1, Data->GlobalConfig.PMSM_config.Lq_Henry/(2.0f*tau_sum));
                uz_CurrentControl_set_Ki_id(CC_instance_1, Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
                uz_CurrentControl_set_Ki_iq(CC_instance_1, Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
                // set cc2
                uz_CurrentControl_set_Kp_id(CC_instance_2, Data->GlobalConfig.PMSM_config.Ld_Henry/(2.0f*tau_sum)/2.0f);
                uz_CurrentControl_set_Kp_iq(CC_instance_2, Data->GlobalConfig.PMSM_config.Lq_Henry/(2.0f*tau_sum)/2.0f);
                uz_CurrentControl_set_Ki_id(CC_instance_2, Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
                uz_CurrentControl_set_Ki_iq(CC_instance_2, Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
                //set resonant
                uz_resonantController_set_gain(resonant_1, Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
                uz_resonantController_set_harmonic_order(resonant_1, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
                uz_resonantController_set_gain(resonant_2, Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
                uz_resonantController_set_harmonic_order(resonant_2, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
                initialized_controllers = 1U;
            }
            // assign to output
            out.d = cc_out_ab_rotating.d + uz_resonantController_step(resonant_1, 0.0f, Data->ActualValues.i_dq_6ph.d, Data->ActualValues.omega_el);
            out.q = cc_out_ab_rotating.q + uz_resonantController_step(resonant_2, 0.0f, Data->ActualValues.i_dq_6ph.q, Data->ActualValues.omega_el);
            uz_3ph_alphabeta_t cc_out_xy_stationary = uz_transformation_3ph_dq_to_alphabeta(cc_out_xy_rotating, -1.0f*Data->ActualValues.theta_el);
            out.x = cc_out_xy_stationary.alpha;
            out.y = cc_out_xy_stationary.beta;
            break;
        }
        default:
        {
            initialized_controllers = 0U;
            out.d = 0.0f;
            out.q = 0.0f;
            out.x = 0.0f;
            out.y = 0.0f;
            out.z1 = 0.0f;
            out.z2 = 0.0f;
    		uz_CurrentControl_reset(CC_instance_1);
            uz_CurrentControl_reset(CC_instance_2);
            uz_resonantController_reset(resonant_1);
            uz_resonantController_reset(resonant_2);
            break;
        }
    }
    return out;

}
/*{
    // assert input pointers
        uz_assert_not_NULL(CC_instance_1);
        uz_assert_not_NULL(CC_instance_2);
        uz_assert_not_NULL(resonant_1);
        uz_assert_not_NULL(resonant_2);

    // Initialize output struct
        static uz_6ph_dq_t out = {0};

    // Splitting up the six-phase struct to subsystem structs
        // actual rotating 1st reference frame
        uz_3ph_dq_t actual_ab_rotating = {
            .d = Data->ActualValues.i_dq_6ph.d,
            .q = Data->ActualValues.i_dq_6ph.q};
        // actual stationary 2nd reference frame
        uz_3ph_alphabeta_t actual_xy_stationary = {
            .alpha = Data->ActualValues.i_dq_6ph.x,
            .beta = Data->ActualValues.i_dq_6ph.y};
        // actual rotating 2nd reference frame
        uz_3ph_dq_t actual_xy_rotating = uz_transformation_3ph_alphabeta_to_dq(actual_xy_stationary, -1.0f*Data->ActualValues.theta_el);
    
    // calculate resonant controller gains
        a_c_squared = (0.1f*2.0f*UZ_PIf*Data->GlobalConfig.sampleTimeISR)*(0.1f*2.0f*UZ_PIf*Data->GlobalConfig.sampleTimeISR);
        kr_d = 0.1f*a_c_squared*Data->GlobalConfig.PMSM_config.Ld_Henry;
        kr_q = 0.1f*a_c_squared*Data->GlobalConfig.PMSM_config.Lq_Henry;
        kr_x = 0.1f*a_c_squared*Data->GlobalConfig.PMSM_6ph_inductances.x;
        kr_y = 0.1f*a_c_squared*Data->GlobalConfig.PMSM_6ph_inductances.y;
        static uint16_t initialized_res_controller = 0U;

    // step PI controllers
    uz_3ph_dq_t cc_out_ab_rotating = uz_CurrentControl_sample(CC_instance_1, Data->FluxmapID_extended_controller_Output->ab_i_dq_PI_ref, actual_ab_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
    uz_3ph_dq_t cc_out_xy_rotating = uz_CurrentControl_sample(CC_instance_2, Data->FluxmapID_extended_controller_Output->xy_i_dq_PI_ref, actual_xy_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);

    // map outputs and step resonant controllers depending on current state inside FluxMapID
    switch(Data->FluxmapID_extended_controller_Output->selected_subsystem)
    {
        case 1: // control alpha beta system
        {
            // update resonant controller gain and harmonic order if it is not correct yet
            if(initialized_res_controller != 1U)
            {
                uz_resonantController_set_gain(resonant_1, kr_d);
                uz_resonantController_set_harmonic_order(resonant_1, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
                uz_resonantController_set_gain(resonant_2, kr_q);
                uz_resonantController_set_harmonic_order(resonant_2, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
                initialized_res_controller = 1U;
            }
            // assign to output
            out.d = cc_out_ab_rotating.d + uz_resonantController_step(resonant_1, 0.0f, Data->ActualValues.i_dq_6ph.d, Data->ActualValues.omega_el);
            out.q = cc_out_ab_rotating.q + uz_resonantController_step(resonant_2, 0.0f, Data->ActualValues.i_dq_6ph.q, Data->ActualValues.omega_el);
            uz_3ph_alphabeta_t cc_out_xy_stationary = uz_transformation_3ph_dq_to_alphabeta(cc_out_xy_rotating, -1.0f*Data->ActualValues.theta_el);
            out.x = cc_out_xy_stationary.alpha;
            out.y = cc_out_xy_stationary.beta;
            break;
        }
        case 2: // control xy system
        {
            // update resonant controller gain and harmonic order if it is not correct yet
            if(initialized_res_controller != 2U)
            {
                uz_resonantController_set_gain(resonant_1, kr_x);
                uz_resonantController_set_harmonic_order(resonant_1, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
                uz_resonantController_set_gain(resonant_2, kr_y);
                uz_resonantController_set_harmonic_order(resonant_2, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
                initialized_res_controller = 2U;
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
            initialized_res_controller = 0U;
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
}*/

bool uz_FluxMapID_6ph_transmit_calculated_values(uz_ParaID_FluxMapID_extended_controller_output_t data, bool meas_flag){
    static bool old_finished_calculation = false;
    static bool feedback = false;
    if(data.finished_calculation && !old_finished_calculation)
    {
        if(printf("%f, %f, %f, %f\n", data.psi_array[0], data.psi_array[1], data.psi_array[2], data.psi_array[3]) > 0)
        {
            feedback = true;
        }  
    }
    if(!meas_flag)
    	feedback = false;
    old_finished_calculation = data.finished_calculation;
    return feedback;
}

#endif