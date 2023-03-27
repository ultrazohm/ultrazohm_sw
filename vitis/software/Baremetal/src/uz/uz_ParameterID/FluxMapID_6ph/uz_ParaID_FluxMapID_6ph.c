#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"
#include "uz_ParaID_FluxMapID_6ph.h"
#include "FluxMapID_6ph_codegen.h"

#include "../../uz_SystemTime/uz_SystemTime.h"


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
static void uz_FluxMapID_6ph_set_controller_parameter(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2);

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

uz_6ph_dq_t uz_FluxMapID_6ph_step_controllers(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2, uz_IIR_Filter_t* filter_1,  uz_IIR_Filter_t* filter_2, uz_IIR_Filter_t* filter_3, uz_IIR_Filter_t* filter_4)
{
    // assert input pointers
        uz_assert_not_NULL(CC_instance_1);
        uz_assert_not_NULL(CC_instance_2);
        uz_assert_not_NULL(resonant_1);
        uz_assert_not_NULL(resonant_2);

    // Initialize output struct
        static uz_6ph_dq_t out = {0};

    // calculate resonant controller gains
        static uint16_t initialized_controllers = 0U;

    // step PI controller
        uz_3ph_dq_t setp_filtered_dq;
        uz_3ph_dq_t setp_filtered_xy;
        setp_filtered_dq.d = uz_signals_IIR_Filter_sample(filter_1, Data->FluxmapID_extended_controller_Output->ab_i_dq_PI_ref.d);
        setp_filtered_dq.q = uz_signals_IIR_Filter_sample(filter_2, Data->FluxmapID_extended_controller_Output->ab_i_dq_PI_ref.q);
        setp_filtered_xy.d = uz_signals_IIR_Filter_sample(filter_3, Data->FluxmapID_extended_controller_Output->xy_i_dq_PI_ref.d);
        setp_filtered_xy.q = uz_signals_IIR_Filter_sample(filter_4, Data->FluxmapID_extended_controller_Output->xy_i_dq_PI_ref.q);
        uz_3ph_dq_t cc_out_ab_rotating = uz_CurrentControl_sample(CC_instance_1, setp_filtered_dq, Data->ActualValues.i_dq, Data->ActualValues.V_DC, Data->ActualValues.omega_el);
        uz_3ph_dq_t cc_out_xy_rotating = uz_CurrentControl_sample(CC_instance_2, setp_filtered_xy, Data->ActualValues.i_xy_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);

    // map outputs and step resonant controllers depending on current state inside FluxMapID
    switch(Data->FluxmapID_extended_controller_Output->selected_subsystem)
    {
        case 1: // control alpha beta system
        {
            // update controllers if it was not done yet
            if(initialized_controllers != 1U)
            {
                printf("\nIdentify Psi dq\ni_d,i_q,psi_d,psi_q\n");
                //uz_FluxMapID_6ph_set_controller_parameter(Data, CC_instance_1, CC_instance_2, resonant_1, resonant_2);
                uz_resonantController_set_harmonic_order(resonant_1, PARAMETERID6PH_FLUXMAP_RES_ORDER_AB);
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
        case 2: // control xy system
        {
            // update controllers if it was not done yet
            if(initialized_controllers != 2U)
            {
                printf("\nIdentify Psi xy\ni_d,i_q,psi_d,psi_q\n");
                //uz_FluxMapID_6ph_set_controller_parameter(Data, CC_instance_1, CC_instance_2, resonant_1, resonant_2);
                uz_resonantController_reset(resonant_1);
				uz_resonantController_reset(resonant_2);
                uz_resonantController_set_harmonic_order(resonant_1, PARAMETERID6PH_FLUXMAP_RES_ORDER_XY);
                uz_resonantController_set_harmonic_order(resonant_2, PARAMETERID6PH_FLUXMAP_RES_ORDER_XY);
                initialized_controllers = 2U;
            }

            // assign to output
            out.d = cc_out_ab_rotating.d;
            out.q = cc_out_ab_rotating.q;
            cc_out_xy_rotating.d = cc_out_xy_rotating.d + uz_resonantController_step(resonant_1, 0.0f, Data->ActualValues.i_xy_rotating.d, Data->ActualValues.omega_el);
            cc_out_xy_rotating.q = cc_out_xy_rotating.q + uz_resonantController_step(resonant_2, 0.0f, Data->ActualValues.i_xy_rotating.q, Data->ActualValues.omega_el);
            uz_3ph_alphabeta_t cc_out_xy_stationary = uz_transformation_3ph_dq_to_alphabeta(cc_out_xy_rotating, -1.0f*Data->ActualValues.theta_el);
            out.x = cc_out_xy_stationary.alpha;
            out.y = cc_out_xy_stationary.beta;
            break;
        }
        case 3: // control zero system
        {
            // update controllers if it was not done yet
            if(initialized_controllers != 3U)
            {
                printf("\nIdentify Psi zero\ni_d,i_q,psi_d,psi_q\n");
                uz_FluxMapID_6ph_set_controller_parameter(Data, CC_instance_1, CC_instance_2, resonant_1, resonant_2);
                uz_resonantController_set_harmonic_order(resonant_1, PARAMETERID6PH_FLUXMAP_RES_ORDER_XY);
                uz_resonantController_set_harmonic_order(resonant_2, PARAMETERID6PH_FLUXMAP_RES_ORDER_XY);
                initialized_controllers = 3U;
            }

            // step PI controller
            uz_3ph_dq_t cc_out_zero_rotating = uz_CurrentControl_sample(CC_instance_2, Data->FluxmapID_extended_controller_Output->zero_i_dq_PI_ref, Data->ActualValues.i_zero_rotating, Data->ActualValues.V_DC, Data->ActualValues.omega_el);

            // assign to output
            cc_out_zero_rotating.d = uz_resonantController_step(resonant_1, 0.0f, Data->ActualValues.i_zero_rotating.d, Data->ActualValues.omega_el);
            cc_out_zero_rotating.q = uz_resonantController_step(resonant_2, 0.0f, Data->ActualValues.i_zero_rotating.q, Data->ActualValues.omega_el);
            uz_3ph_alphabeta_t cc_out_zero_stationary = uz_transformation_3ph_dq_to_alphabeta(cc_out_zero_rotating, 3.0f*Data->ActualValues.theta_el);
            out.z1 = cc_out_zero_stationary.alpha;
            out.z2 = cc_out_zero_stationary.beta;
            break;
        }
        default:
        {
            initialized_controllers = 0U;
    		uz_CurrentControl_reset(CC_instance_1);
            uz_CurrentControl_reset(CC_instance_2);
            uz_resonantController_reset(resonant_1);
            uz_resonantController_reset(resonant_2);
            break;
        }
    }
    return out;

}

uint8_t uz_FluxMapID_6ph_transmit_calculated_values(uz_ParaID_FluxMapID_extended_controller_output_t data, bool meas_flag){
    static bool old_finished_calculation = false;
    static uint8_t feedback = 0U;
    static float time = 0.0f;
    
    if(data.finished_calculation && !old_finished_calculation && !(feedback & 0x02)){
		time = uz_SystemTime_GetGlobalTimeInSec();
    	feedback = feedback | 0x02;
    }else if((feedback & 0x02) && ((uz_SystemTime_GetGlobalTimeInSec() - time) > 0.005f)){
    	feedback = feedback & 0xFD;
		feedback = feedback | 0x01;
    }
    if(!meas_flag)
    	feedback = feedback & 0xFE;
    old_finished_calculation = data.finished_calculation;
    return feedback;
}

static void uz_FluxMapID_6ph_set_controller_parameter(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2){
    //float tau_sum = Data->GlobalConfig.sampleTimeISR*2.0f;
    // reset all
    //uz_CurrentControl_reset(CC_instance_1);
    //uz_CurrentControl_reset(CC_instance_2);
    uz_resonantController_reset(resonant_1);
    uz_resonantController_reset(resonant_2);
    // set cc1
   uz_CurrentControl_set_Kp_id(CC_instance_1, 10.0f);//Data->GlobalConfig.PMSM_config.Ld_Henry/(2.0f*tau_sum));
    uz_CurrentControl_set_Kp_iq(CC_instance_1, 10.0f);//Data->GlobalConfig.PMSM_config.Lq_Henry/(2.0f*tau_sum));
    uz_CurrentControl_set_Ki_id(CC_instance_1, 1500.0f);//Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
    uz_CurrentControl_set_Ki_iq(CC_instance_1, 1500.0f);//Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
    // set cc2
    uz_CurrentControl_set_Kp_id(CC_instance_2, 15.0f);//Data->GlobalConfig.PMSM_config.Ld_Henry/(2.0f*tau_sum)/2.0f);
    uz_CurrentControl_set_Kp_iq(CC_instance_2, 15.0f);//Data->GlobalConfig.PMSM_config.Lq_Henry/(2.0f*tau_sum)/2.0f);
    uz_CurrentControl_set_Ki_id(CC_instance_2, 500.0f);//Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
    uz_CurrentControl_set_Ki_iq(CC_instance_2, 500.0f);//Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
    //set resonant
    uz_resonantController_set_gain(resonant_1, 1000.0f);//1.0f*Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
    uz_resonantController_set_gain(resonant_2, 1000.0f);//2.0f*Data->GlobalConfig.PMSM_config.R_ph_Ohm/(2.0f*tau_sum));
}
#endif
