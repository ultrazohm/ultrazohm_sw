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
#include "../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer.h"
#include "../uz/uz_nn/uz_nn_activation_functions.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;
struct uz_3ph_abc_t i_abc_actual_Ampere = {0};
struct uz_3ph_abc_t v_abc_actualVolts = {0};
struct uz_3ph_dq_t i_dq_actual_Ampere = {0};
struct uz_3ph_dq_t i_dq_CIL_Ampere = {0};
struct uz_3ph_dq_t i_dq_reference_Ampere = {0};
struct uz_3ph_dq_t  i_dq_reference_Ampere_javascope={0};
struct uz_3ph_dq_t v_dq_actual_Volts = {0};
struct uz_3ph_dq_t v_dq_CurrentControl_Volts = {0};
struct uz_3ph_abc_t v_abc_Volts = {0};
struct uz_3ph_dq_t i_dq_SetPoint_currents_amp = {0};
struct uz_DutyCycle_t DutyCycle_output = {0};
struct uz_pmsmModel_inputs_t pmsm_inputs={
    .omega_mech_1_s=0.0f,
    .v_d_V=0.0f,
    .v_q_V=0.0f,
    .load_torque=0.0f
};
struct uz_pmsmModel_outputs_t pmsm_outputs={
    .i_d_A=0.0f,
    .i_q_A=0.0f,
    .torque_Nm=0.0f,
    .omega_mech_1_s=0.0f
};
float n_ref_rpm = 0.0f;
float M_ref_Nm = 0.0f;
float SC_torque_out = 0.0f;
float PMSM_IP_Core_V_DC = 48.0f;
extern bool select_CurrentControl;
extern bool select_DDPG_1;
extern bool select_DDPG_2;
extern bool select_DDPG_3;
extern bool select_Real;
extern bool select_SpeedControl;
extern bool select_CIL;
extern bool select_automatic_idiq;

extern float y_2[2];
// Variables for NN

#define NUMBER_OF_INPUTS_9N 9U
#define NUMBER_OF_INPUTS_7N 7U

uz_matrix_t* matrix_output_9n;
uz_matrix_t* matrix_output_7n;
struct uz_3ph_dq_t i_dq_integrated_error_Amp = {0};
struct uz_3ph_dq_t i_dq_error_Amp = {0};
struct uz_3ph_dq_t v_dq_limited_Volts = {0};
struct uz_3ph_dq_t v_dq_limited_Volts_k_old = {0};
struct uz_3ph_dq_t v_dq_non_limited_Volts = {0};
float observation_ip_9n[NUMBER_OF_INPUTS_9N] = {0};
float observation_ip_7n[NUMBER_OF_INPUTS_7N] = {0};
float rated_current = 4.2f;
float rated_Speed_rpm = 3000.0f;
float speed_weight = 1.0f / 3000.0f;
float U_max = 48.0f / 1.732050808f; // sqrt(3) Because of SpaceVetorLimitation
float Voltage_Scaling = 1.0f / (48.0f / 1.732050808f);
bool ext_clamping = false;
float max_modulation_index = 1.0f / 1.732050808f;
float ts = 1.0f / UZ_PWM_FREQUENCY;

float offset = 3.31f;

float id_setpoints[22]={
#include "id_setpoints.csv"
};

float iq_setpoints[22]={
#include "iq_setpoints.csv"
};



#if NN_9_INPUT_3_64
extern float mlp_ip_output[2U];
extern uz_matrix_t *p_output_data;
extern uz_mlp_three_layer_ip_t* mlp_ip_instance;
#endif


uint64_t old_uptime=0;
uint32_t setpoint_index=0;
bool automatic_idiq_lock=false; // hack to only do it once
float start_marker=0.0f;
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    if( (select_automatic_idiq) && (!automatic_idiq_lock) ){
    	start_marker=1.0f;
    	i_dq_reference_Ampere.d=id_setpoints[setpoint_index];
    	i_dq_reference_Ampere.q=iq_setpoints[setpoint_index];

    	// step throught the array
    	uint64_t current_uptime=uz_SystemTime_GetInterruptCounter();
    	if(current_uptime>(old_uptime +300 ) ){
    		old_uptime=current_uptime;

    		if(setpoint_index<21){
    			setpoint_index++;
    		}else{
    			setpoint_index=0;
    			select_automatic_idiq=false;
    			automatic_idiq_lock=true;
    		}



    	}
    }else{
    	i_dq_reference_Ampere=i_dq_reference_Ampere_javascope;
    }


    if(select_CIL) {
		uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_IP_core);
		uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_IP_core);
		pmsm_outputs=uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_IP_core);

		i_dq_CIL_Ampere.d = pmsm_outputs.i_d_A;
		i_dq_CIL_Ampere.q = pmsm_outputs.i_q_A;
		Global_Data.av.I_d = pmsm_outputs.i_d_A;
		Global_Data.av.I_q = pmsm_outputs.i_q_A;
		Global_Data.av.omega_m = pmsm_outputs.omega_mech_1_s;
		Global_Data.av.mechanicalRotorSpeed = pmsm_outputs.omega_mech_1_s * 60.0f / (2.0f*M_PI);
		Global_Data.av.omega_elec = pmsm_outputs.omega_mech_1_s * 3.0f;
    	if (current_state==control_state) {

    		if(select_SpeedControl || select_CurrentControl) {
    			if(select_SpeedControl) {
    				SC_torque_out = uz_SpeedControl_sample(Global_Data.objects.SC_instance, pmsm_outputs.omega_mech_1_s, n_ref_rpm);
    				Global_Data.av.mechanicalTorque = SC_torque_out;
    				i_dq_SetPoint_currents_amp = uz_SetPoint_sample(Global_Data.objects.SP_instance, pmsm_outputs.omega_mech_1_s, SC_torque_out, PMSM_IP_Core_V_DC, i_dq_CIL_Ampere);
    				v_dq_CurrentControl_Volts = uz_CurrentControl_sample(Global_Data.objects.CC_instance, i_dq_SetPoint_currents_amp, i_dq_CIL_Ampere, PMSM_IP_Core_V_DC, Global_Data.av.omega_elec);
    			}
    			if(select_CurrentControl) {
    				v_dq_CurrentControl_Volts = uz_CurrentControl_sample(Global_Data.objects.CC_instance, i_dq_reference_Ampere, i_dq_CIL_Ampere, PMSM_IP_Core_V_DC, Global_Data.av.omega_elec);
    			}
    			pmsm_inputs.v_d_V = v_dq_CurrentControl_Volts.d;
    			pmsm_inputs.v_q_V = v_dq_CurrentControl_Volts.q;

    		}
    		if(select_DDPG_1) {
    			//DDPG with 9 observations
    			if(ext_clamping == false) {
    				i_dq_integrated_error_Amp.d = (i_dq_integrated_error_Amp.d + (i_dq_error_Amp.d * ts)); // use Forward-Euler with error of previous timestep for integration
    				i_dq_integrated_error_Amp.q = (i_dq_integrated_error_Amp.q + (i_dq_error_Amp.q * ts));
    			} else {
    				i_dq_integrated_error_Amp.d += 0.0f;
    				i_dq_integrated_error_Amp.q += 0.0f;
    			}
    			i_dq_error_Amp.d = (i_dq_reference_Ampere.d - i_dq_CIL_Ampere.d) / rated_current;
    			i_dq_error_Amp.q = (i_dq_reference_Ampere.q - i_dq_CIL_Ampere.q) / rated_current;
    			observation_ip_9n[0] = i_dq_error_Amp.d;
    			observation_ip_9n[1] = i_dq_integrated_error_Amp.d * UZ_PWM_FREQUENCY;
    			observation_ip_9n[2] = i_dq_error_Amp.q;
    			observation_ip_9n[3] = i_dq_integrated_error_Amp.q * UZ_PWM_FREQUENCY ;
    			observation_ip_9n[4] = i_dq_CIL_Ampere.d / rated_current;
    			observation_ip_9n[5] = i_dq_CIL_Ampere.q / rated_current;
    			observation_ip_9n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
    			observation_ip_9n[7] = pmsm_inputs.v_d_V * Voltage_Scaling;
    			observation_ip_9n[8] = pmsm_inputs.v_q_V * Voltage_Scaling;
    	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_9N; i++) {
    	        	uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_9n,observation_ip_9n[i],0U,i);
    	        }

#if NN_9_INPUT_3_64 == 1
    	        uz_mlp_three_layer_ff_blocking(mlp_ip_instance, Global_Data.objects.matrix_input_9n, p_output_data);
    	        // IP-Core only calculates with linear, tanh has to be added manually
    	        v_dq_non_limited_Volts.d=(uz_nn_activation_function_tanh(mlp_ip_output[0]))*U_max;
    	        v_dq_non_limited_Volts.q=(uz_nn_activation_function_tanh(mlp_ip_output[1]))*U_max;

#else
    	        uz_nn_ff(Global_Data.objects.nn_layer_9n,Global_Data.objects.matrix_input_9n);
    	        matrix_output_9n = uz_nn_get_output_data(Global_Data.objects.nn_layer_9n);
    	        uz_matrix_multiply_by_scalar(matrix_output_9n,U_max); // scaling layer of nn
    	        v_dq_non_limited_Volts.d = uz_matrix_get_element_zero_based(matrix_output_9n,0U,0U);
    	        v_dq_non_limited_Volts.q = uz_matrix_get_element_zero_based(matrix_output_9n,0U,1U);
#endif
    	        v_dq_limited_Volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_Volts, PMSM_IP_Core_V_DC, max_modulation_index, Global_Data.av.omega_elec, i_dq_actual_Ampere, &ext_clamping);
    	        pmsm_inputs.omega_mech_1_s = ( n_ref_rpm / 60.0f ) * 2.0f * M_PI;
    	        pmsm_inputs.v_d_V = v_dq_limited_Volts.d;
    	        pmsm_inputs.v_q_V = v_dq_limited_Volts.q;
    		}
    		if (select_DDPG_2) {
    			//DDPG with 7 observations
    			i_dq_error_Amp.d = (i_dq_reference_Ampere.d - i_dq_CIL_Ampere.d) / rated_current;
    			i_dq_error_Amp.q = (i_dq_reference_Ampere.q - i_dq_CIL_Ampere.q) / rated_current;
    			observation_ip_7n[0] = i_dq_error_Amp.d;
    			observation_ip_7n[1] = i_dq_error_Amp.q;
    			observation_ip_7n[2] = i_dq_CIL_Ampere.d / rated_current;
    			observation_ip_7n[3] = i_dq_CIL_Ampere.q / rated_current;
    			observation_ip_7n[4] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
    			observation_ip_7n[5] = pmsm_inputs.v_d_V * Voltage_Scaling;
    			observation_ip_7n[6] = pmsm_inputs.v_q_V * Voltage_Scaling;
    			for (uint32_t i = 0; i < NUMBER_OF_INPUTS_7N; i++) {
    				uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_7n,observation_ip_7n[i],0U,i);
    			}
    			uz_nn_ff(Global_Data.objects.nn_layer_7n,Global_Data.objects.matrix_input_7n);
    			matrix_output_7n = uz_nn_get_output_data(Global_Data.objects.nn_layer_7n);

    			uz_matrix_multiply_by_scalar(matrix_output_7n,U_max); // scaling layer of nn
    			v_dq_non_limited_Volts.d = uz_matrix_get_element_zero_based(matrix_output_7n,0U,0U);
    			v_dq_non_limited_Volts.q = uz_matrix_get_element_zero_based(matrix_output_7n,0U,1U);
    			v_dq_limited_Volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_Volts, PMSM_IP_Core_V_DC, max_modulation_index, Global_Data.av.omega_elec, i_dq_actual_Ampere, &ext_clamping);
    			pmsm_inputs.omega_mech_1_s = ( n_ref_rpm / 60.0f ) * 2.0f * M_PI;
    			pmsm_inputs.v_d_V = v_dq_limited_Volts.d;
    			pmsm_inputs.v_q_V = v_dq_limited_Volts.q;
    		}
    		if (select_DDPG_3) {
    			//DDPG with IP-core

    			//Code here
    		}
    	} else {
        	uz_CurrentControl_reset(Global_Data.objects.CC_instance);
        	uz_SpeedControl_reset(Global_Data.objects.SC_instance);
        	i_dq_reference_Ampere.d = 0.0f;
        	i_dq_reference_Ampere.q = 0.0f;
        	pmsm_inputs.v_d_V = 0.0f;
        	pmsm_inputs.v_q_V = 0.0f;
        	i_dq_integrated_error_Amp.d = 0.0f;
        	i_dq_integrated_error_Amp.q = 0.0f;
        	ext_clamping = false;
    	}

    	uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_IP_core, pmsm_inputs);
		Global_Data.av.U_d = pmsm_inputs.v_d_V;
		Global_Data.av.U_q = pmsm_inputs.v_q_V;
    }
    if(select_Real) {
    	Global_Data.av.theta_mech = Global_Data.av.theta_mech - offset;
    	Global_Data.av.omega_elec = Global_Data.av.omega_m * 3.0f;
    	Global_Data.av.theta_elec = Global_Data.av.theta_mech * 3.0f;  //I changed the encoder function to write the theta onto theta_mech
    	Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    	Global_Data.av.I_U = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    	Global_Data.av.I_V = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    	Global_Data.av.I_W = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    	Global_Data.av.I_DC = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    	Global_Data.av.U_U = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    	Global_Data.av.U_V = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    	Global_Data.av.U_W = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    	Global_Data.av.U_ZK = Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    	i_abc_actual_Ampere.a = Global_Data.av.I_U;
    	i_abc_actual_Ampere.b = Global_Data.av.I_V;
    	i_abc_actual_Ampere.c = Global_Data.av.I_W;
    	v_abc_actualVolts.a = Global_Data.av.U_U;
    	v_abc_actualVolts.b = Global_Data.av.U_V;
    	v_abc_actualVolts.c = Global_Data.av.U_W;
    	i_dq_actual_Ampere = uz_transformation_3ph_abc_to_dq(i_abc_actual_Ampere, Global_Data.av.theta_elec);
    	v_dq_actual_Volts = uz_transformation_3ph_abc_to_dq(v_abc_actualVolts, Global_Data.av.theta_elec);
    	Global_Data.av.I_d = i_dq_actual_Ampere.d;
    	Global_Data.av.I_q = i_dq_actual_Ampere.q;
    	Global_Data.av.U_d = v_dq_actual_Volts.d;
    	Global_Data.av.U_q = v_dq_actual_Volts.q;
    	if (current_state == running_state || current_state == control_state) {
    		// enable inverter adapter hardware
    	 	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    	} else {
    	  	// disable inverter adapter hardware
    	   	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    	}
    	if (current_state==control_state) {
    	  	if(select_SpeedControl || select_CurrentControl) {
    	   		if(select_SpeedControl) {
    	   			SC_torque_out = uz_SpeedControl_sample(Global_Data.objects.SC_instance, Global_Data.av.omega_m, n_ref_rpm);
    	   			Global_Data.av.mechanicalTorque = SC_torque_out;
    	   			i_dq_SetPoint_currents_amp = uz_SetPoint_sample(Global_Data.objects.SP_instance, Global_Data.av.omega_m, SC_torque_out, Global_Data.av.U_ZK, i_dq_actual_Ampere);
    	   			v_dq_CurrentControl_Volts = uz_CurrentControl_sample(Global_Data.objects.CC_instance, i_dq_SetPoint_currents_amp, i_dq_actual_Ampere, Global_Data.av.U_ZK, Global_Data.av.omega_elec);
    	   		}
    	   		if(select_CurrentControl) {
    	   			v_dq_CurrentControl_Volts = uz_CurrentControl_sample(Global_Data.objects.CC_instance, i_dq_reference_Ampere, i_dq_actual_Ampere, Global_Data.av.U_ZK, Global_Data.av.omega_elec);
    	   		}
    	   		DutyCycle_output = uz_Space_Vector_Modulation(v_dq_CurrentControl_Volts, Global_Data.av.U_ZK, Global_Data.av.theta_elec);
    	   		Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.DutyCycle_A;
    	   		Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.DutyCycle_B;
    	   		Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.DutyCycle_C;
    	  	}
    	  	if(select_DDPG_1) {
    	  		//DDPG with 9 observations
    	  		if(ext_clamping == false) {
    	  			i_dq_integrated_error_Amp.d = (i_dq_integrated_error_Amp.d + (i_dq_error_Amp.d * ts)); // use Forward-Euler with error of previous timestep for integration
    	  			i_dq_integrated_error_Amp.q = (i_dq_integrated_error_Amp.q + (i_dq_error_Amp.q * ts));
    	  		} else {
    	  			i_dq_integrated_error_Amp.d += 0.0f;
    	  			i_dq_integrated_error_Amp.q += 0.0f;
    	  		}
    	  		i_dq_error_Amp.d = (i_dq_reference_Ampere.d - i_dq_actual_Ampere.d) / rated_current;
    	  		i_dq_error_Amp.q = (i_dq_reference_Ampere.q - i_dq_actual_Ampere.q) / rated_current;
    	  		observation_ip_9n[0] = i_dq_error_Amp.d;
    	  		observation_ip_9n[1] = i_dq_integrated_error_Amp.d * UZ_PWM_FREQUENCY;
    	  		observation_ip_9n[2] = i_dq_error_Amp.q;
    	  		observation_ip_9n[3] = i_dq_integrated_error_Amp.q * UZ_PWM_FREQUENCY ;
    	  		observation_ip_9n[4] = i_dq_actual_Ampere.d / rated_current;
    	  		observation_ip_9n[5] = i_dq_actual_Ampere.q / rated_current;
    	  		observation_ip_9n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
				observation_ip_9n[7] = v_dq_limited_Volts_k_old.d * Voltage_Scaling;
				observation_ip_9n[8] = v_dq_limited_Volts_k_old.q * Voltage_Scaling;
				for (uint32_t i = 0; i < NUMBER_OF_INPUTS_9N; i++) {
    	  			uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_9n,observation_ip_9n[i],0U,i);
    	  		}
    	  		uz_nn_ff(Global_Data.objects.nn_layer_9n,Global_Data.objects.matrix_input_9n);
    	  		matrix_output_9n = uz_nn_get_output_data(Global_Data.objects.nn_layer_9n);

    	  		uz_matrix_multiply_by_scalar(matrix_output_9n,U_max); // scaling layer of nn
    	  		v_dq_non_limited_Volts.d = uz_matrix_get_element_zero_based(matrix_output_9n,0U,0U);
    	  		v_dq_non_limited_Volts.q = uz_matrix_get_element_zero_based(matrix_output_9n,0U,1U);
    	  		v_dq_limited_Volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_Volts, Global_Data.av.U_ZK, max_modulation_index, Global_Data.av.omega_elec, i_dq_actual_Ampere, &ext_clamping);
				v_dq_limited_Volts_k_old = v_dq_limited_Volts;
				DutyCycle_output = uz_Space_Vector_Modulation(v_dq_limited_Volts, Global_Data.av.U_ZK, Global_Data.av.theta_elec);
				Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.DutyCycle_A;
    	  		Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.DutyCycle_B;
    	  		Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.DutyCycle_C;
    	  	}
    	  	if (select_DDPG_2) {
    	  		//DDPG with 7 observations

    	  	    //Code here
    	  	}
    	  	if (select_DDPG_3) {
    	  		//DDPG with IP-core

    	  	    //Code here
    	  	}
   	    } else {
    	    	uz_CurrentControl_reset(Global_Data.objects.CC_instance);
    	    	uz_SpeedControl_reset(Global_Data.objects.SC_instance);
    	    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
            	i_dq_integrated_error_Amp.d = 0.0f;
            	i_dq_integrated_error_Amp.q = 0.0f;
            	ext_clamping = false;
    	    }
    }

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================

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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &Timer_Interrupt);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable uz_mux_axi for triggering the ADCs and the ISR
//    uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
//    uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
//    uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    //uz_mux_axi_enable(Global_Data.objects.mux_axi);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE AXI-TIMER FOR ISRs
// - "TIMER_LOAD_VALUE" sets the counter-end-value in order to set the ISR-frequency f_c
// - "Con_TIMER_DEVICE_ID" uses the Device-ID of the used timer in Vivado
// - "Timer_Interrupt" is the used timer structure instance
// - "XTC_INT_MODE_OPTION" activates the Interrupt function
// - "XTC_AUTO_RELOAD_OPTION" activates an automatic reload of the timer
// - By default, the counter counts up
//----------------------------------------------------
int Initialize_Timer()
{

    int Status;

    // SETUP THE TIMER 1 for Interrupts
    Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_UZ_SYSTEM_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;
    // XTmrCtr_SetHandler(&Timer_Interrupt, ISR_Control, &Timer_Interrupt);
    XTmrCtr_SetOptions(&Timer_Interrupt, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
    XTmrCtr_SetResetValue(&Timer_Interrupt, 0, TIMER_LOAD_VALUE);
    XTmrCtr_Reset(&Timer_Interrupt, 0);
    XTmrCtr_Start(&Timer_Interrupt, 0);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Timer_Interrupt_InstancePtr)
{
    XScuGic_Config *IntcConfig;
    int status;

    // Interrupt controller initialization
    IntcConfig = XScuGic_LookupConfig(DeviceId);
    status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstPtr);

    /* Enable interrupts in the processor */
    Xil_ExceptionEnable(); // Enable interrupts in the ARM

    // setting interrupt trigger sensitivity
    // b01	Active HIGH level sensitive
    // b11 	Rising edge sensitive
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
    // XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

    // Make the connection between the IntId of the interrupt source and the
    // associated handler that is to run when the interrupt is recognized.
    status = XScuGic_Connect(IntcInstPtr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             (void *)IntcInstPtr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Enable GPIO and timer interrupts in the controller
    XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
    XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);

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
    XIpiPsu_Config *IntcConfig_IPI;
    int status;

    // Interrupt controller configuration
    IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
    if (IntcConfig_IPI == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: RPU_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};
