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

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

// =============== Declares for PMSM 1 =============== //
struct uz_resolver_pl_interface_outputs_t Resolver_outputs = {0};
// FOC Instances and Configs
extern uz_SpeedControl_t* speed_controller_hoerner;
extern uz_SetPoint_t* SP_instance_1;
extern uz_CurrentControl_t* current_controller_hoerner;
extern struct uz_PMSM_t config_PMSM_hoerner;
extern uz_HarmonicCurrentInjection_t* hci_5th_hoerner;
extern uz_HarmonicCurrentInjection_t* hci_7th_hoerner;

// Inverter Measurement
struct uz_3ph_abc_t v_abc_Volts_hoerner 	= {0};
struct uz_3ph_dq_t v_dq_Volts_hoerner 	= {0};
struct uz_3ph_dq_t v_dq_ref_Volts_hoerner = {0};
struct uz_3ph_abc_t i_abc_Amps_hoener 	= {0};
struct uz_3ph_dq_t i_dq_Amps_hoerner 		= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_hoerner 	= {0};
float v_DC_Volts_hoerner 					= 24.0f;
float i_DC_Amps_hoerner 					= 0.0f;

// FOC Variables
float n_ref_rpm_1 					= 0.0f;
float M_ref_Nm_1 					= 0.0f;
float omega_m_rad_per_sec_hoerner 		= 0.0f;
float omega_el_rad_per_sec_hoerner 		= 0.0f;
float theta_el_rad_hoerner 				= 0.0f;
float theta_el_rad_hoerner_advanced		= 0.0f;
float theta_el_offset_hoerner 			= 0.0;
struct uz_DutyCycle_t duty_cycle_hoerner 		= {0};

// Controller Settings
float Kp_speed_1 					= 0.005f;
float Ki_speed_1 					= 0.01f;
//float Kp_id_1 = 0.3f;
//float Ki_id_1 = 230.0f;
//float Kp_iq_1 = 0.5f;
//float Ki_iq_1 = 230.0f;

// Harmonic Current Injection
int mode = 0;
struct uz_3ph_dq_t i_dqn_ref_5th_Amps_hoerner = {0};
struct uz_3ph_dq_t i_dqn_ref_7th_Amps_hoerner = {0};
struct uz_3ph_dq_t i_dqn_filtered_5th_Amps_hoerner = {0};
struct uz_3ph_dq_t i_dqn_filtered_7th_Amps_hoerner = {0};
struct uz_3ph_dq_t v_dq_ref_5th_Volts_hoerner = {0};
struct uz_3ph_dq_t v_dq_ref_7th_Volts_hoerner = {0};
struct uz_3ph_dq_t v_dq_ref_HCI_Volts_hoerner = {0};

// =============== Declares for PMSM 2 =============== //

// FOC Instances and Configs
extern uz_SpeedControl_t* speed_controller_beckhoff;
extern uz_SetPoint_t* setpoint_instance_beckhoff;
extern uz_CurrentControl_t* current_controller_beckhoff;
extern struct uz_PMSM_t config_PMSM_beckhoff;

// Inverter Measurement
struct uz_3ph_abc_t v_abc_Volts_beckhoff 	= {0};
struct uz_3ph_dq_t v_dq_Volts_beckhoff 	= {0};
struct uz_3ph_dq_t v_dq_ref_Volts_beckhoff = {0};
struct uz_3ph_abc_t i_abc_Amps_beckhoff 	= {0};
struct uz_3ph_dq_t i_dq_Amps_beckhoff 		= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_beckhoff 	= {0};
float v_DC_Volts_beckhoff 					= 12.0f;
float i_DC_Amps_beckhoff 					= 0.0f;

// FOC Variables
float n_ref_rpm_beckhoff 					= 0.0f;
float M_ref_Nm_beckhoff 					= 0.0f;
float omega_m_rad_per_sec_beckhoff 		= 0.0f;
float omega_el_rad_per_sec_beckhoff 		= 0.0f;
float theta_el_rad_beckhoff 				= 0.0f;
float theta_el_rad_beckhoff_advanced		= 0.0f;
float theta_el_offset_2 			= 1.4f;
struct uz_DutyCycle_t duty_cycle_beckhoff 		= {0};
uz_3ph_dq_t flux_approx             = {0};
uz_3ph_dq_t flux_reference          = {0};
float K_p_id                        = 0.0f;
float K_p_iq                        = 0.0f;


//Stuff

uint32_t setpoint_index				= 0U;
uint64_t old_uptime					= 0U;
float start_marker					= 0.0f;
float id_setpoints[22]={
#include "id_setpoints.csv"
};

float iq_setpoints[22]={
#include "iq_setpoints.csv"
};
extern bool select_automatic_idiq;
extern float PMSM_rated_current_hoerner;
uint32_t Fehlerfall  = 0U;
extern bool select_misalignment;
extern uz_3ph_dq_t i_dq_ref_java_Amps_hoerner;

//DDPG Stuff
extern bool select_DDPG;
extern bool select_FOC;
float observation_ip[9U] = {0};
#define NUMBER_OF_INPUTS_7N 7U
#define NUMBER_OF_INPUTS_9N 9U
uz_matrix_t* matrix_output;
uz_3ph_dq_t i_dq_integrated_error_Amps_hoerner = {0};
uz_3ph_dq_t i_dq_error_Amps_hoerner = {0};
float ts = 1.0f / UZ_PWM_FREQUENCY;
float speed_weight_hoerner = 1.0f / 1500.0f;
uz_3ph_dq_t v_dq_non_limited_Volts_hoerner = {0};
uz_3ph_dq_t v_dq_limited_Volts_hoerner = {0};
uz_3ph_dq_t v_dq_limited_Volts_old_old_hoerner = {0};
float U_max_hoerner = 48.0f / 1.732050808f;
float Voltage_Scaling_hoerner = 1.0f / (48.0f / 1.732050808f);
bool ext_clamping_hoerner = false;
float max_modulation_index_hoerner = 1.0f / 1.732050808f;
bool start_angle_found = false;
float theta_el_old_hoerner = 0.0f;
bool change_speed = false;

// 3 layer MLP

#if ((NN_9_INPUT_3_64) || (NN_7_INPUT_3_64))
extern float mlp_ip_output[2U];
extern uz_matrix_t *p_output_data;
extern uz_mlp_three_layer_ip_t *mlp_ip_instance;
#endif

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
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);

    // Set tristate to false
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_hoerner, false, false, false);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2_beckhoff, false, false, false);

    // Read Measurement Data of First Inverter
    v_abc_Volts_hoerner.a = 11.7657f * Global_Data.aa.A1.me.ADC_B8 + 0.0533f;
    v_abc_Volts_hoerner.b = 11.7657f * Global_Data.aa.A1.me.ADC_B7 + 0.0533f;
    v_abc_Volts_hoerner.c = 11.7657f * Global_Data.aa.A1.me.ADC_B6 + 0.0533f;
    v_DC_Volts_hoerner 	= Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps_hoener.a  = 12.223f * Global_Data.aa.A1.me.ADC_A4 + 0.0164f;
    i_abc_Amps_hoener.b  = 12.3123f * Global_Data.aa.A1.me.ADC_A3 + 0.0161f;
    i_abc_Amps_hoener.c  = 12.4303f * Global_Data.aa.A1.me.ADC_A2 - 0.0184f;
    i_DC_Amps_hoerner     = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d1_hoerner = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1_hoerner);


    // Read Measurement of Second Inverter
    v_abc_Volts_beckhoff.a = 11.6798f * Global_Data.aa.A2.me.ADC_B8 - 0.3648f;
    v_abc_Volts_beckhoff.b = 11.7657f * Global_Data.aa.A2.me.ADC_B7 + 0.0533f;
    v_abc_Volts_beckhoff.c = 11.7657f * Global_Data.aa.A2.me.ADC_B6 + 0.0533f;
    v_DC_Volts_beckhoff 	= Global_Data.aa.A2.me.ADC_A1 * 12.0f;
    i_abc_Amps_beckhoff.a  = 12.2889f * Global_Data.e.ADC_A4 + 0.0802f;
    i_abc_Amps_beckhoff.b  = 11.8330f * Global_Data.aa.A2.me.ADC_A3 + 0.1344f;
    i_abc_Amps_beckhoff.c  = 11.7894f * Global_Data.aa.A2.me.ADC_A2 + 0.1197f;
    i_DC_Amps_beckhoff     = Global_Data.aa.A2.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d2_beckhoff = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2_beckhoff);

    // Get current state
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state) {
    	// enable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_hoerner, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_beckhoff, true);
    } else {
        // disable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_hoerner, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_beckhoff, false);
    }

    // Calculation of Signals for FOC for PMSM 1
    omega_m_rad_per_sec_hoerner = Global_Data.av.mechanicalRotorSpeed_filtered_hoerner*(2.0f*UZ_PIf)/60.0f;
    omega_el_rad_per_sec_hoerner = omega_m_rad_per_sec_hoerner*config_PMSM_hoerner.polePairs;
    Global_Data.av.omega_el_hoerner = omega_el_rad_per_sec_hoerner;
    theta_el_rad_hoerner = Global_Data.av.theta_elec_hoerner - theta_el_offset_hoerner;
    if(select_misalignment==true) {
    	theta_el_rad_hoerner += 5.0f * (M_PI / 180.0f);
    }
    //Anglelead
    theta_el_rad_hoerner_advanced = theta_el_rad_hoerner + (1.5f * omega_el_rad_per_sec_hoerner ) / UZ_PWM_FREQUENCY;
    Global_Data.av.theta_mech_hoerner = theta_el_rad_hoerner / 4.0f;
    i_dq_Amps_hoerner = uz_transformation_3ph_abc_to_dq(i_abc_Amps_hoener, theta_el_rad_hoerner);
    v_dq_Volts_hoerner = uz_transformation_3ph_abc_to_dq(v_abc_Volts_hoerner, theta_el_rad_hoerner);



    // Calculation of Signals for FOC for PMSM 2
    Resolver_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4);
    Global_Data.av.mechanicalRotorSpeed_beckhoff = Resolver_outputs.n_mech_rpm;
    Global_Data.av.mechanicalRotorSpeed_filtered_beckhoff = Resolver_outputs.n_mech_rpm;
    omega_m_rad_per_sec_beckhoff = Resolver_outputs.omega_mech_rad_s;
    omega_el_rad_per_sec_beckhoff = omega_m_rad_per_sec_beckhoff * config_PMSM_beckhoff.polePairs;
    Global_Data.av.omega_el_beckhoff = omega_el_rad_per_sec_beckhoff;
    theta_el_rad_beckhoff = Resolver_outputs.position_el_2pi;
    //Anglelead
    theta_el_rad_beckhoff_advanced = theta_el_rad_beckhoff + (1.5f * omega_el_rad_per_sec_beckhoff ) / UZ_PWM_FREQUENCY;
    i_dq_Amps_beckhoff = uz_transformation_3ph_abc_to_dq(i_abc_Amps_beckhoff, theta_el_rad_beckhoff);
    v_dq_Volts_beckhoff = uz_transformation_3ph_abc_to_dq(v_abc_Volts_beckhoff, theta_el_rad_beckhoff);

    //Automatic evaluation profile
    if( (select_automatic_idiq) ){
    	if ((((theta_el_old_hoerner - Global_Data.av.theta_elec_hoerner) > UZ_PIf) || (Global_Data.av.mechanicalRotorSpeed_beckhoff < 10.0f))&& (!start_angle_found)) {
    		start_angle_found = true;
    	}

    	if (start_angle_found) {

    		start_marker=1.0f;
    		i_dq_ref_Amps_hoerner.d = id_setpoints[setpoint_index];
    		i_dq_ref_Amps_hoerner.q = iq_setpoints[setpoint_index] * PMSM_rated_current_hoerner;

    		// step throught the array
    		uint64_t current_uptime=uz_SystemTime_GetInterruptCounter();
    		if((current_uptime>(old_uptime + 11290) && (!change_speed)) ){
    			old_uptime=current_uptime;

    			if(setpoint_index<21){
    				setpoint_index++;
    			}else{
    				setpoint_index = 0U;
    				start_angle_found = false;
    				start_marker = 0.0f;
    				change_speed = true;
    			}

    		}
    		if (change_speed) {
    			if(current_uptime>(old_uptime + 11290)) {
    				n_ref_rpm_beckhoff = n_ref_rpm_beckhoff - 100.0f;
    				change_speed = false;
    				select_automatic_idiq = false;
    			}
    		}
    	}

    }else{
    	i_dq_ref_Amps_hoerner=i_dq_ref_java_Amps_hoerner;
    }
    theta_el_old_hoerner = Global_Data.av.theta_elec_hoerner;




    if (current_state==control_state)
    {
    	if(select_FOC) {
    		// Field Oriented Control of PMSM 1
    		//M_ref_Nm_1 = uz_SpeedControl_sample(speed_controller_hoerner, omega_m_rad_per_sec_hoerner, n_ref_rpm_1);
    		//i_dq_ref_Amps_hoerner = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_hoerner, M_ref_Nm_1, v_DC_Volts_hoerner, i_dq_Amps_hoerner);

    		//Approximate psid and psiq and set new kpd and kpq
    		flux_approx = uz_approximate_flux_step(Global_Data.objects.approximate_flux_instance, i_dq_Amps_hoerner);
    		uz_CurrentControl_set_flux_approx(current_controller_hoerner, flux_approx);
    		flux_reference = uz_approximate_flux_reference_step(Global_Data.objects.approximate_flux_instance,i_dq_ref_Amps_hoerner,i_dq_Amps_hoerner);
    		K_p_id = uz_CurrentControl_Kp_id_adjustment_step(Global_Data.objects.Kp_id_adjustment_instance,i_dq_ref_Amps_hoerner, i_dq_Amps_hoerner, flux_reference, flux_approx);
    		K_p_iq = uz_CurrentControl_Kp_iq_adjustment_step(Global_Data.objects.Kp_iq_adjustment_instance,i_dq_ref_Amps_hoerner, i_dq_Amps_hoerner, flux_reference, flux_approx);
    		uz_CurrentControl_set_Kp_id(current_controller_hoerner, K_p_id);
    		uz_CurrentControl_set_Kp_iq(current_controller_hoerner, K_p_iq);
            v_dq_ref_Volts_hoerner = uz_CurrentControl_sample(current_controller_hoerner, i_dq_ref_Amps_hoerner, i_dq_Amps_hoerner, v_DC_Volts_hoerner, omega_el_rad_per_sec_hoerner);
            switch (mode)
    		{
    		default:
    			duty_cycle_hoerner = uz_Space_Vector_Modulation(v_dq_ref_Volts_hoerner, v_DC_Volts_hoerner, theta_el_rad_hoerner_advanced);
    			break;
    		case 1:
        		i_dqn_filtered_5th_Amps_hoerner = uz_HarmonicCurrentInjection_filter(hci_5th_hoerner, i_abc_Amps_hoener, theta_el_rad_hoerner);
        		i_dqn_filtered_7th_Amps_hoerner = uz_HarmonicCurrentInjection_filter(hci_7th_hoerner, i_abc_Amps_hoener, theta_el_rad_hoerner);
        		uz_HarmonicCurrentInjection_set_filters(hci_5th_hoerner, omega_el_rad_per_sec_hoerner);
        		uz_HarmonicCurrentInjection_set_filters(hci_7th_hoerner, omega_el_rad_per_sec_hoerner);
    			v_dq_ref_HCI_Volts_hoerner.d = v_dq_ref_Volts_hoerner.d +  v_dq_ref_5th_Volts_hoerner.d + v_dq_ref_7th_Volts_hoerner.d;
    			v_dq_ref_HCI_Volts_hoerner.q = v_dq_ref_Volts_hoerner.q +  v_dq_ref_5th_Volts_hoerner.q + v_dq_ref_7th_Volts_hoerner.q;
    			v_dq_ref_5th_Volts_hoerner = uz_HarmonicCurrentInjection_sample(hci_5th_hoerner, i_dqn_ref_5th_Amps_hoerner, i_dqn_filtered_5th_Amps_hoerner, v_DC_Volts_hoerner, omega_el_rad_per_sec_hoerner, theta_el_rad_hoerner);
    			v_dq_ref_7th_Volts_hoerner = uz_HarmonicCurrentInjection_sample(hci_7th_hoerner, i_dqn_ref_7th_Amps_hoerner, i_dqn_filtered_7th_Amps_hoerner, v_DC_Volts_hoerner, omega_el_rad_per_sec_hoerner, theta_el_rad_hoerner);
    			duty_cycle_hoerner = uz_Space_Vector_Modulation(v_dq_ref_HCI_Volts_hoerner, v_DC_Volts_hoerner, theta_el_rad_hoerner_advanced);
    			break;
    		}
    	} else if(select_DDPG) {
    		if(ext_clamping_hoerner == false) {
    			i_dq_integrated_error_Amps_hoerner.d = (i_dq_integrated_error_Amps_hoerner.d + (i_dq_error_Amps_hoerner.d * ts)); // use Forward-Euler with error of previous timestep for integration
    			i_dq_integrated_error_Amps_hoerner.q = (i_dq_integrated_error_Amps_hoerner.q + (i_dq_error_Amps_hoerner.q * ts));
    		} else {
    			i_dq_integrated_error_Amps_hoerner.d += 0.0f;
    			i_dq_integrated_error_Amps_hoerner.q += 0.0f;
    		}
    		i_dq_error_Amps_hoerner.d = (i_dq_ref_Amps_hoerner.d - i_dq_Amps_hoerner.d) / PMSM_rated_current_hoerner;
    		i_dq_error_Amps_hoerner.q = (i_dq_ref_Amps_hoerner.q - i_dq_Amps_hoerner.q) / PMSM_rated_current_hoerner;

#if ((NN_9_INPUT_1_64) || (NN_9_INPUT_3_64)) == 1

            observation_ip[0] = i_dq_error_Amps_hoerner.d;
    		observation_ip[1] = i_dq_integrated_error_Amps_hoerner.d * UZ_PWM_FREQUENCY;
    		observation_ip[2] = i_dq_error_Amps_hoerner.q;
    		observation_ip[3] = i_dq_integrated_error_Amps_hoerner.q * UZ_PWM_FREQUENCY ;
    		observation_ip[4] = i_dq_Amps_hoerner.d / PMSM_rated_current_hoerner;
    		observation_ip[5] = i_dq_Amps_hoerner.q / PMSM_rated_current_hoerner;
    		observation_ip[6] = -1.0f*n_ref_rpm_beckhoff * speed_weight_hoerner; //Global_Data.av.mechanicalRotorSpeed_filtered_hoerner * speed_weight_hoerner;
    		observation_ip[7] = v_dq_limited_Volts_old_old_hoerner.d * Voltage_Scaling_hoerner;
    		observation_ip[8] = v_dq_limited_Volts_old_old_hoerner.q * Voltage_Scaling_hoerner;
			for (uint32_t i = 0; i < NUMBER_OF_INPUTS_9N; i++) {
	  			uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input,observation_ip[i],0U,i);
	  		}
#elif NN_7_INPUT_1_64 == 1
			observation_ip[0] = i_dq_error_Amps_hoerner.d;
			observation_ip[1] = v_dq_limited_Volts_old_old_hoerner.d * Voltage_Scaling_hoerner;
			observation_ip[2] = i_dq_error_Amps_hoerner.q;
			observation_ip[3] = v_dq_limited_Volts_old_old_hoerner.q * Voltage_Scaling_hoerner;
			observation_ip[4] = i_dq_Amps_hoerner.d / PMSM_rated_current_hoerner;
			observation_ip[5] = i_dq_Amps_hoerner.q / PMSM_rated_current_hoerner;
			observation_ip[6] = Global_Data.av.mechanicalRotorSpeed_filtered_hoerner * speed_weight_hoerner;
			for (uint32_t i = 0; i < NUMBER_OF_INPUTS_7N; i++) {
					uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input,observation_ip[i],0U,i);
			}
#endif

#if NN_9_INPUT_3_64 == 1
            uz_mlp_three_layer_ff_blocking(mlp_ip_instance, Global_Data.objects.matrix_input, p_output_data);
            // IP-Core only calculates with linear, tanh has to be added manually
            v_dq_non_limited_Volts_hoerner.d = (uz_nn_activation_function_tanh(mlp_ip_output[0])) * U_max_hoerner;
            v_dq_non_limited_Volts_hoerner.q = (uz_nn_activation_function_tanh(mlp_ip_output[1])) * U_max_hoerner;
#else
            uz_nn_ff(Global_Data.objects.nn_layer,Global_Data.objects.matrix_input);
    	    matrix_output = uz_nn_get_output_data(Global_Data.objects.nn_layer);
    	    uz_matrix_multiply_by_scalar(matrix_output,U_max_hoerner); // scaling layer of nn
    	    v_dq_non_limited_Volts_hoerner.d = uz_matrix_get_element_zero_based(matrix_output,0U,0U);
    	    v_dq_non_limited_Volts_hoerner.q = uz_matrix_get_element_zero_based(matrix_output,0U,1U);
#endif
    	    v_dq_limited_Volts_hoerner = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_Volts_hoerner, v_DC_Volts_hoerner, max_modulation_index_hoerner, omega_el_rad_per_sec_hoerner, i_dq_ref_Amps_hoerner, &ext_clamping_hoerner);
    	    //Introduce delay
    	    v_dq_limited_Volts_old_old_hoerner = v_dq_limited_Volts_hoerner;
    	    duty_cycle_hoerner = uz_Space_Vector_Modulation(v_dq_limited_Volts_hoerner, v_DC_Volts_hoerner, theta_el_rad_hoerner_advanced);

    	} else {
    		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	}
    	Global_Data.rasv.halfBridge1DutyCycle = duty_cycle_hoerner.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = duty_cycle_hoerner.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = duty_cycle_hoerner.DutyCycle_C;

    	// Field Oriented Control of PMSM 2
        M_ref_Nm_beckhoff = uz_SpeedControl_sample(speed_controller_beckhoff, omega_m_rad_per_sec_beckhoff, n_ref_rpm_beckhoff);
        i_dq_ref_Amps_beckhoff = uz_SetPoint_sample(setpoint_instance_beckhoff, omega_m_rad_per_sec_beckhoff, M_ref_Nm_beckhoff, v_DC_Volts_beckhoff, i_dq_Amps_beckhoff);
       	v_dq_ref_Volts_beckhoff = uz_CurrentControl_sample(current_controller_beckhoff, i_dq_ref_Amps_beckhoff, i_dq_Amps_beckhoff, v_DC_Volts_beckhoff, omega_el_rad_per_sec_beckhoff);
       	duty_cycle_beckhoff = uz_Space_Vector_Modulation(v_dq_ref_Volts_beckhoff, v_DC_Volts_beckhoff, theta_el_rad_beckhoff_advanced);
       	Global_Data.rasv.halfBridge4DutyCycle = duty_cycle_beckhoff.DutyCycle_A;
       	Global_Data.rasv.halfBridge5DutyCycle = duty_cycle_beckhoff.DutyCycle_B;
       	Global_Data.rasv.halfBridge6DutyCycle = duty_cycle_beckhoff.DutyCycle_C;

    }
    else
    {
    	// Set tristate
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_hoerner, true, true, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2_beckhoff, true, true, true);

    	// Reset speed and current control
    	uz_SpeedControl_reset(speed_controller_hoerner);
    	uz_CurrentControl_reset(current_controller_hoerner);
    	uz_SpeedControl_reset(speed_controller_beckhoff);
    	uz_CurrentControl_reset(current_controller_beckhoff);

    	//Reset DDPG
    	ext_clamping_hoerner = false;
    	i_dq_integrated_error_Amps_hoerner.d = 0.0f;
    	i_dq_integrated_error_Amps_hoerner.q = 0.0f;
    }

    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_hoerner, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d2_beckhoff, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    // Update Javascope
    JavaScope_update(&Global_Data);

    // Inverter 1 safety
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1_hoerner.FAULT_H1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 1U;
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1_hoerner.FAULT_L1) {
        //ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 2U;
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1_hoerner.FAULT_H2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 3U;
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1_hoerner.FAULT_L2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 4U;
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1_hoerner.FAULT_H3) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 5U;
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1_hoerner.FAULT_L3) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 6U;
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1_hoerner.OC_L1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 7U;
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1_hoerner.OC_H1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 8U;
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1_hoerner.OC_L2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 9U;
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1_hoerner.OC_H2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 10U;
    }

    // Inverter 2 safety
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.FAULT_H1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 11U;
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.FAULT_L1) {
    	//ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 12U;
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.FAULT_H2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 13U;
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.FAULT_L2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 14U;
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.FAULT_H3) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 15U;
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.FAULT_L3) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 16U;
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.OC_L1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 17U;
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.OC_H1) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 18U;
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.OC_L2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 19U;
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d2_beckhoff.OC_H2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 20U;
    }

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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG);
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
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId)
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
