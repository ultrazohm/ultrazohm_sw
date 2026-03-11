/******************************************************************************
 * Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);


#define PHASE_CURRENT_CONV_A1	12.555f
#define PHASE_CURRENT_CONV_B1	12.564f
#define PHASE_CURRENT_CONV_C1	12.552f
#define PHASE_CURRENT_CONV_A2	12.547f
#define PHASE_CURRENT_CONV_B2	12.551f
#define PHASE_CURRENT_CONV_C2	12.544f
#define DC_CURRENT_CONV 		12.5f

#define PHASE_CURRENT_OFFSET_A1	0.0078201f
#define PHASE_CURRENT_OFFSET_B1	0.0029715f
#define PHASE_CURRENT_OFFSET_C1	-0.011468f
#define PHASE_CURRENT_OFFSET_A2	-0.014776f
#define PHASE_CURRENT_OFFSET_B2	-0.0052169f
#define PHASE_CURRENT_OFFSET_C2	-0.0027063f

#define PHASE_VOLT_CONV_A1	12.01f
#define PHASE_VOLT_CONV_B1	12.005f
#define PHASE_VOLT_CONV_C1	12.008f
#define PHASE_VOLT_CONV_A2	11.925f
#define PHASE_VOLT_CONV_B2	11.996f
#define PHASE_VOLT_CONV_C2	12.002f
#define DC_VOLT_CONV		12.0f

#define PHASE_VOLT_OFFSET_A1 	0.037846f
#define PHASE_VOLT_OFFSET_B1	0.058787f
#define PHASE_VOLT_OFFSET_C1	0.051362f
#define PHASE_VOLT_OFFSET_A2	-0.30423f
#define PHASE_VOLT_OFFSET_B2	0.073247f
#define PHASE_VOLT_OFFSET_C2	0.04081f

enum ControllerApplication ConApplication;
enum ControllerSelection ConSelection;
float ts = 1.0f / UZ_CONTROL_FREQUENCY;
float Observation[7] = {0};
bool ext_clamping = 0.0f;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    switch(ConApplication) {
    case CIL:
    	uz_pmsmModel_trigger_input_strobe(Global_Data.objects.PMSM_Model);
    	uz_pmsmModel_trigger_output_strobe(Global_Data.objects.PMSM_Model);
    	Global_Data.av.PMSM_outputs				= uz_pmsmModel_get_outputs(Global_Data.objects.PMSM_Model);
    	Global_Data.av.i_dq_DUT.d 				= Global_Data.av.PMSM_outputs.i_d_A;
    	Global_Data.av.i_dq_DUT.q 				= Global_Data.av.PMSM_outputs.i_q_A;
    	Global_Data.av.omega_mech_DUT			= Global_Data.av.PMSM_outputs.omega_mech_1_s;
    	Global_Data.av.Torque_DUT				= Global_Data.av.PMSM_outputs.torque_Nm;
    	Global_Data.av.mechanicalRotorSpeed_DUT = Global_Data.av.omega_mech_DUT * 30.0f / UZ_PIf;
    	Global_Data.av.omega_elec_DUT 			= Global_Data.av.omega_mech_DUT * Global_Data.rasv.PMSM_DUT_config.polePairs;
    	Global_Data.av.v_dc_DUT					= Global_Data.rasv.PMSM_DUT_config.V_DC_Volts;
    	Global_Data.av.current_angle_degree_DUT = atan2f(Global_Data.av.i_dq_DUT.q,Global_Data.av.i_dq_DUT.d) /UZ_PIf * 180.0f;
    	Global_Data.av.is_DUT					= sqrtf((Global_Data.av.i_dq_DUT.d * Global_Data.av.i_dq_DUT.d) + (Global_Data.av.i_dq_DUT.q * Global_Data.av.i_dq_DUT.q));
    	Global_Data.av.v_dq_DUT.d				= Global_Data.av.PMSM_inputs.v_d_V;
    	Global_Data.av.v_dq_DUT.q				= Global_Data.av.PMSM_inputs.v_q_V;
    	break;

    case REAL:
	    //Read/Calculate Angle
	    update_speed_and_position_of_encoder_on_D5(&Global_Data);//get theta_elec and omega_mech
    	Global_Data.av.theta_elec_DUT 			= Global_Data.av.theta_elec_DUT - Global_Data.av.theta_offset_DUT;
    	Global_Data.av.theta_mech_DUT 			= Global_Data.av.theta_elec_DUT / Global_Data.rasv.PMSM_DUT_config.polePairs;
    	Global_Data.av.omega_elec_DUT			= Global_Data.av.omega_mech_DUT * Global_Data.rasv.PMSM_DUT_config.polePairs;
    	Global_Data.av.mechanicalRotorSpeed_DUT = Global_Data.av.omega_mech_DUT * 30.0f / UZ_PIf;
		Global_Data.av.theta_elec_advanced_DUT  = Global_Data.av.theta_elec_DUT + ((1.5f * Global_Data.av.omega_elec_DUT) / UZ_CONTROL_FREQUENCY);
	    Global_Data.av.resolver_outputs_Load	= uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_IP);
	    Global_Data.av.theta_elec_Load 			= Global_Data.av.resolver_outputs_Load.position_el_2pi;
	    Global_Data.av.theta_mech_Load			= Global_Data.av.resolver_outputs_Load.position_mech_2pi;
	    Global_Data.av.omega_mech_Load			= Global_Data.av.resolver_outputs_Load.omega_mech_rad_s;
	    Global_Data.av.omega_elec_Load			= Global_Data.av.omega_mech_Load * Global_Data.rasv.PMSM_Load_config.polePairs;
	    Global_Data.av.theta_elec_advanced_Load = Global_Data.av.theta_elec_Load + ((1.5f * Global_Data.av.omega_elec_Load) / UZ_CONTROL_FREQUENCY);
	    Global_Data.av.mechanicalRotorSpeed_Load= Global_Data.av.omega_mech_Load * 30.0f / UZ_PIf;


		//Measurements
    	Global_Data.av.i_abc_DUT.a 				= (Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1) + PHASE_CURRENT_OFFSET_A1;
    	Global_Data.av.i_abc_DUT.b 				= (Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1) + PHASE_CURRENT_OFFSET_B1;
    	Global_Data.av.i_abc_DUT.c 				= (Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1) + PHASE_CURRENT_OFFSET_C1;
    	Global_Data.av.i_dc_DUT					= (Global_Data.aa.A1.me.ADC_B5 * DC_CURRENT_CONV);
		Global_Data.av.v_abc_DUT.a 				= (Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_A1) + PHASE_VOLT_OFFSET_A1;
		Global_Data.av.v_abc_DUT.b 				= (Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_B1) + PHASE_VOLT_OFFSET_B1;
		Global_Data.av.v_abc_DUT.c 				= (Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_C1) + PHASE_VOLT_OFFSET_C1;
		Global_Data.av.v_dc_DUT 				= (Global_Data.aa.A1.me.ADC_A1 * DC_VOLT_CONV);
    	Global_Data.av.i_abc_Load.a 			= (Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2) + PHASE_CURRENT_OFFSET_A2;
    	Global_Data.av.i_abc_Load.b 			= (Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2) + PHASE_CURRENT_OFFSET_B2;
    	Global_Data.av.i_abc_Load.c 			= (Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2) + PHASE_CURRENT_OFFSET_C2;
    	Global_Data.av.i_dc_Load				= (Global_Data.aa.A2.me.ADC_B5 * DC_CURRENT_CONV);
		Global_Data.av.v_abc_Load.a 			= (Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_A2) + PHASE_VOLT_OFFSET_A2;
		Global_Data.av.v_abc_Load.b 			= (Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_B2) + PHASE_VOLT_OFFSET_B2;
		Global_Data.av.v_abc_Load.c 			= (Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_C2) + PHASE_VOLT_OFFSET_C2;
		Global_Data.av.v_dc_Load 				= (Global_Data.aa.A2.me.ADC_A1 * DC_VOLT_CONV);

		//TODO ADC Measurement of Torque

		 //Read out inverter temp
		 Global_Data.av.temp_VSI_DUT = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d1_DUT.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d1_DUT.ChipTempDegreesCelsius_L1,
				 Global_Data.av.inverter_outputs_d1_DUT.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d1_DUT.ChipTempDegreesCelsius_L2,
				 Global_Data.av.inverter_outputs_d1_DUT.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d1_DUT.ChipTempDegreesCelsius_L3);
		 Global_Data.av.temp_VSI_Load = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d2_Load.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d2_Load.ChipTempDegreesCelsius_L1,
				 	 Global_Data.av.inverter_outputs_d2_Load.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d2_Load.ChipTempDegreesCelsius_L2,
					 Global_Data.av.inverter_outputs_d2_Load.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d2_Load.ChipTempDegreesCelsius_L3);

		 //Safety checks
		 float V_Limit = Global_Data.rasv.PMSM_DUT_config.V_DC_Volts * 1.03f;//allow 3 percent higher VDC before error
	    if((Global_Data.av.i_abc_DUT.a > Global_Data.rasv.PMSM_DUT_config.I_max_Ampere) || (Global_Data.av.i_abc_DUT.b > Global_Data.rasv.PMSM_DUT_config.I_max_Ampere) || (Global_Data.av.i_abc_DUT.c > Global_Data.rasv.PMSM_DUT_config.I_max_Ampere)
	    		|| (Global_Data.av.i_dc_DUT > Global_Data.rasv.PMSM_DUT_config.I_max_Ampere) || (Global_Data.av.v_dc_DUT > V_Limit)) {
			ultrazohm_state_machine_set_stop(true);
	    }
	    if((Global_Data.av.i_abc_Load.a > Global_Data.rasv.PMSM_Load_config.I_max_Ampere) || (Global_Data.av.i_abc_Load.b > Global_Data.rasv.PMSM_Load_config.I_max_Ampere) || (Global_Data.av.i_abc_Load.c > Global_Data.rasv.PMSM_Load_config.I_max_Ampere)
	    		|| (Global_Data.av.i_dc_Load > Global_Data.rasv.PMSM_Load_config.I_max_Ampere) || (Global_Data.av.v_dc_Load > V_Limit)) {
			ultrazohm_state_machine_set_stop(true);
	    }

	    //Calculations and transformations
	    Global_Data.av.i_dq_DUT					= uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_DUT, Global_Data.av.theta_elec_DUT);
	    Global_Data.av.v_dq_DUT					= uz_transformation_3ph_abc_to_dq(Global_Data.av.v_abc_DUT, Global_Data.av.theta_elec_DUT);
    	Global_Data.av.is_Load					= sqrtf((Global_Data.av.i_dq_Load.d * Global_Data.av.i_dq_Load.d) + (Global_Data.av.i_dq_Load.q * Global_Data.av.i_dq_Load.q));
    	Global_Data.av.i_dq_Load				= uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_Load, Global_Data.av.theta_elec_Load);
    	Global_Data.av.v_dq_Load				= uz_transformation_3ph_abc_to_dq(Global_Data.av.v_abc_Load, Global_Data.av.theta_elec_Load);
	    Global_Data.av.current_angle_degree_DUT = atan2f(Global_Data.av.i_dq_DUT.q,Global_Data.av.i_dq_DUT.d) /UZ_PIf * 180.0f;
	    Global_Data.av.is_DUT					= sqrtf((Global_Data.av.i_dq_DUT.d * Global_Data.av.i_dq_DUT.d) + (Global_Data.av.i_dq_DUT.q * Global_Data.av.i_dq_DUT.q));
    	break;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    // if "STOP"
     if (current_state==idle_state)
     {
     	uz_CurrentControl_reset(Global_Data.objects.CurrentControl_DUT);
     	uz_CurrentControl_reset(Global_Data.objects.CurrentControl_Load);
     	uz_SpeedControl_reset(Global_Data.objects.SpeedControl_Load);
//     	StepProfile = false;
//     	change_speed = false;
//     	setpoint_index = 0U;
//     	start_angle_found = false;
     	Global_Data.av.speed_ref_Load = 0.0f;
     	ext_clamping = false;
     	switch(ConApplication) {
     	    case CIL:
     	    	uz_pmsmModel_reset(Global_Data.objects.PMSM_Model);
     	    	break;

     	    case REAL:
     	    	// disable inverters
     	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_DUT, false);
     	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_Load, false);

     	    	// write zero dutycycle
     	    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
     	    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
     	    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
     	    	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
     	    	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
     	    	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
     	    	break;

     	    default:
     	    	break;
     	}
    }

     // if "ENABLE SYSTEM"
     if (current_state==running_state)
     {
      	switch(ConApplication) {
      	    case CIL:
      	    	//CODE
      	    	break;

      	    case REAL:
      	    	// disable inverters
      	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_DUT, true);
      	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_Load, true);
      	    	break;

      	    default:
      	    	break;
      	}
    }


    if (current_state==control_state)
    {
    	if(ConApplication == REAL && ConSelection != manual) {
    		//Only use load machine when REAL
    		Global_Data.av.speed_ref_filtered_Load 	= uz_signals_IIR_Filter_sample(Global_Data.objects.Speed_Filter_Load, Global_Data.av.speed_ref_Load);
    	    //Approximates required torque based on dq-Setpoints of DUT machine
    		Global_Data.av.Torque_ref_Load 			= uz_SpeedControl_sample(Global_Data.objects.SpeedControl_Load, Global_Data.av.omega_mech_Load, Global_Data.av.speed_ref_filtered_Load);
    		//Adds required torque of DUT as Vorsteuerung
    		Global_Data.av.Torque_ref_Load 			+= Global_Data.av.Torque_ref_DUT;
    		Global_Data.av.i_ref_dq_Load 			= uz_SetPoint_sample(Global_Data.objects.SetPoint_Load, Global_Data.av.omega_mech_Load, Global_Data.av.Torque_ref_Load, Global_Data.av.v_dc_Load, Global_Data.av.i_dq_Load);
    		Global_Data.av.v_ref_dq_Load 			= uz_CurrentControl_sample(Global_Data.objects.CurrentControl_Load, Global_Data.av.i_ref_dq_Load, Global_Data.av.i_dq_Load, Global_Data.av.v_dc_Load, Global_Data.av.omega_elec_Load);
    		Global_Data.av.DutyCycle_Load 			= uz_Space_Vector_Modulation(Global_Data.av.v_ref_dq_Load, Global_Data.av.v_dc_Load, Global_Data.av.theta_elec_advanced_Load);
    	}

    	switch(ConSelection) {
    	case LUT_FOC:
    		Global_Data.av.current_angle_ref_degree_DUT = uz_LUT_1D_get_value(Global_Data.objects.LUT_current_angle, Global_Data.av.Torque_ref_DUT);
    		Global_Data.av.is_ref_DUT 					= uz_LUT_1D_get_value(Global_Data.objects.LUT_Is, Global_Data.av.Torque_ref_DUT);
    		Global_Data.av.i_ref_dq_DUT.d 				= cosf((Global_Data.av.current_angle_ref_degree_DUT)/180.0f*UZ_PIf) * Global_Data.av.is_ref_DUT;
    		Global_Data.av.i_ref_dq_DUT.q 				= sinf((Global_Data.av.current_angle_ref_degree_DUT)/180.0f*UZ_PIf) * Global_Data.av.is_ref_DUT;
        	Global_Data.av.flux_approx_real_DUT 		= uz_approximate_flux_step(Global_Data.objects.FluxApproximation_DUT, Global_Data.av.i_dq_DUT);
        	Global_Data.av.flux_approx_reference_DUT 	= uz_approximate_flux_reference_step(Global_Data.objects.FluxApproximation_DUT, Global_Data.av.i_ref_dq_DUT, Global_Data.av.i_dq_DUT);
        	uz_CurrentControl_set_flux_approx(Global_Data.objects.CurrentControl_DUT, Global_Data.av.flux_approx_real_DUT, Global_Data.av.flux_approx_reference_DUT);
        	uz_CurrentControl_adjust_Kp(Global_Data.objects.CurrentControl_DUT, Global_Data.av.i_ref_dq_DUT, Global_Data.av.i_dq_DUT, BO_FACTOR);
        	Global_Data.av.v_ref_dq_DUT 				= uz_CurrentControl_sample(Global_Data.objects.CurrentControl_DUT, Global_Data.av.i_ref_dq_DUT, Global_Data.av.i_dq_DUT, Global_Data.av.v_dc_DUT, Global_Data.av.omega_elec_DUT);
        	Global_Data.av.DutyCycle_DUT 				= uz_Space_Vector_Modulation(Global_Data.av.v_ref_dq_DUT, Global_Data.av.v_dc_DUT, Global_Data.av.theta_elec_advanced_DUT);
        	break;

        case RL:
        	float V_max = Global_Data.rasv.PMSM_DUT_config.V_DC_Volts * uz_CurrentControl_get_max_modulation_index(Global_Data.objects.CurrentControl_DUT);
        	Observation[0] = Global_Data.av.Torque_ref_DUT / Global_Data.rasv.PMSM_DUT_config.M_rated_Nm;
        	Observation[1] = Global_Data.av.i_dq_DUT.d / Global_Data.rasv.PMSM_DUT_config.I_max_Ampere;
        	Observation[2] = Global_Data.av.i_dq_DUT.q / Global_Data.rasv.PMSM_DUT_config.I_max_Ampere;
        	Observation[3] = Global_Data.av.is_DUT / Global_Data.rasv.PMSM_DUT_config.I_max_Ampere;
        	Observation[4] = Global_Data.av.mechanicalRotorSpeed_DUT / Global_Data.rasv.PMSM_DUT_config.n_rated_rpm;
        	Observation[5] = Global_Data.av.v_ref_dq_DUT.d / V_max;
        	Observation[6] = Global_Data.av.v_ref_dq_DUT.q / V_max;
        	for (uint32_t i = 0; i < 7; i++) {
        		uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_acc,Observation[i],0U,i);
        	}
        	uz_NN_acc_ff_blocking(Global_Data.objects.NN_acc_Instance);
        	uz_matrix_multiply_by_scalar(Global_Data.objects.matrix_output_acc,V_max);
        	Global_Data.av.v_ref_dq_pre_limit_DUT.d = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,0U);
        	Global_Data.av.v_ref_dq_pre_limit_DUT.q = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,1U);
        	Global_Data.av.v_ref_dq_DUT = uz_CurrentControl_SpaceVector_Limitation(Global_Data.av.v_ref_dq_pre_limit_DUT, Global_Data.av.v_dc_DUT, uz_CurrentControl_get_max_modulation_index(Global_Data.objects.CurrentControl_DUT), Global_Data.av.omega_elec_DUT, Global_Data.av.i_ref_dq_DUT, &ext_clamping);
        	Global_Data.av.DutyCycle_DUT = uz_Space_Vector_Modulation(Global_Data.av.v_ref_dq_DUT, Global_Data.av.v_dc_DUT, Global_Data.av.theta_elec_advanced_DUT);
        	break;

        case manual:
        	//CIL set v_dq_ref manual via GUI
        	Global_Data.av.v_ref_dq_DUT = Global_Data.av.v_dq_ref_CIL_manual;
        	//REAL set DutyCycles manual via GUI
        	Global_Data.av.DutyCycle_DUT = Global_Data.av.DutyCycle_manual_DUT;
        	break;
    	}
    	switch(ConApplication) {
    		case CIL:
    	    	Global_Data.av.PMSM_inputs.v_d_V = Global_Data.av.v_ref_dq_DUT.d;
    	    	Global_Data.av.PMSM_inputs.v_q_V = Global_Data.av.v_ref_dq_DUT.q;
    	    	Global_Data.av.PMSM_inputs.omega_mech_1_s = Global_Data.av.speed_ref_Load / 30.0f * UZ_PIf;
    	    	uz_pmsmModel_set_inputs(Global_Data.objects.PMSM_Model, Global_Data.av.PMSM_inputs);
    	    	break;

    	    case REAL:
    	    	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.DutyCycle_DUT.DutyCycle_A;
    	        Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.DutyCycle_DUT.DutyCycle_B;
    	        Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.DutyCycle_DUT.DutyCycle_C;
        		Global_Data.rasv.halfBridge4DutyCycle = Global_Data.av.DutyCycle_Load.DutyCycle_A;
        		Global_Data.rasv.halfBridge5DutyCycle = Global_Data.av.DutyCycle_Load.DutyCycle_B;
        		Global_Data.rasv.halfBridge6DutyCycle = Global_Data.av.DutyCycle_Load.DutyCycle_C;
    	    	break;

    	    default:
    	    	break;
    	    }

    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================
static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3){
    float output;
    output = H1;
    if(L1 > output){
    	output = L1;
    }
    if(H2 > output){
       	output = H2;
    }
    if(L2 > output){
       	output = L2;
    }
    if(H3 > output){
       	output = H3;
    }
    if(L3 > output){
       	output = L3;
    }
    return output;
}
//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}


//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};




static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU GIC: Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



