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
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

//Changes
#define NUMBER_OF_INPUTS_15N 15U
#define NUMBER_OF_INPUTS_17N 17U
uz_matrix_t* matrix_output_15n;
uz_matrix_t* matrix_output_17n;
struct uz_pmsm_model6ph_dq_outputs_general_t CIL_out_general = {0};
uz_6ph_dq_t v_dqxy_limited_volts = {0};
uz_3ph_dq_t v_dq_limited_volts = {0};
uz_3ph_dq_t v_xy_limited_volts = {0};
uz_3ph_dq_t v_dq_non_limited_volts = {0};
uz_3ph_dq_t v_xy_non_limited_volts = {0};
uz_6ph_dq_t v_dqxy_limited_volts_k_old = {0};
uz_6ph_dq_t v_dqxy_non_limited_volts = {0};
uz_6ph_dq_t CIL_i_dqxy_meas = {0};
uz_6ph_abc_t REAL_i_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_ref = {0};
uz_6ph_dq_t REAL_i_dqxy_meas = {0};
uz_6ph_dq_t REAL_v_dqxy_meas = {0};
uz_6ph_dq_t i_dqxy_integrated_error = {0};
uz_6ph_dq_t i_dqxy_error = {0};
uz_3ph_dq_t CIL_v_dq_reference = {0};
uz_3ph_dq_t CIL_v_xy_reference = {0};
uz_3ph_dq_t CIL_v_z1z2_reference = {0};
uz_3ph_dq_t REAL_v_dq_reference = {0};
uz_3ph_dq_t REAL_v_xy_reference = {0};
uz_3ph_dq_t REAL_v_z1z2_reference = {0};
uz_3ph_dq_t i_dq_reference = {0};
uz_3ph_dq_t i_xy_reference = {0};
uz_3ph_dq_t i_z1z2_reference = {0};
uz_3ph_dq_t CIL_i_dq_meas= {0};
uz_3ph_dq_t CIL_i_xy_meas = {0};
uz_3ph_dq_t CIL_i_z1z2_meas = {0};
uz_3ph_dq_t REAL_i_dq_meas= {0};
uz_3ph_dq_t REAL_i_xy_meas = {0};
uz_3ph_dq_t REAL_i_z1z2_meas = {0};
struct uz_DutyCycle_2x3ph_t DutyCycle_output = {0};
float CIL_omega_mech = 100.0f; //fixed speed for the CIL model
float max_modulation_index = (1.0f / 2.0f) * 0.707106781f;
float ts = 1.0f / UZ_ISR_FREQUENCY;
float V_DC_Volts = 36.0f;
float U_max = (36.0f / 2.0f) * 0.707106781f;
float Voltage_Scaling = 1.0f / (36.0f / 2.0f);
float rated_current = 18.0f;//24.0f;
float polepairs = 5.0f;
float rated_Speed_rpm = 1100.0f;
float speed_weight = 1.0f / 1100.0f;
bool ext_clamping_dq = false;
bool ext_clamping_xy = false;
extern bool select_CurrentControl;
extern bool select_DDPG_1_64;
extern bool select_DDPG_3_64;
extern bool select_Real;
extern bool select_CIL;
extern bool select_automatic_idiq;
extern float n_ref_rpm;
extern float i_d_ref;
extern float i_q_ref;
extern float i_X_ref;
extern float i_Y_ref;
float observation_ip_15n[NUMBER_OF_INPUTS_15N] = {0};
float observation_ip_17n[NUMBER_OF_INPUTS_17N] = {0};
int reset = 0U;
//Offset from Valentin
float theta_offset = 5.4843f;
#define PHASE_CURRENT_CONV 12.5f
#define PHASE_VOLT_CONV	12.0f
// software limits
#define MAX_PHASE_CURRENT_AMP  30.0f
#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f
//neutral config
#define NEUTRAL_CONFIG 2U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_a1c1 = 0.0f;
float u_a2c2 = 0.0f;

float id_setpoints[22]={
#include "id_setpoints.csv"
};

float iq_setpoints[22]={
#include "iq_setpoints.csv"
};

float iX_setpoints[22]={
#include "iX_setpoints.csv"
};

float iY_setpoints[22]={
#include "iY_setpoints.csv"
};
uint64_t old_uptime=0U;
uint32_t setpoint_index=0U;
bool automatic_idiq_lock=false; // hack to only do it once
float start_marker=0.0f;
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    if(select_CIL) {
    	uz_pmsm_model6ph_trigger_voltage_input_strobe(Global_Data.objects.CIL_pmsm);
    	uz_pmsm_model6ph_trigger_current_output_strobe(Global_Data.objects.CIL_pmsm);
    }
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();

    if( (select_automatic_idiq) ){
    	start_marker=1.0f;
    	i_dq_reference.d=id_setpoints[setpoint_index];
    	i_dq_reference.q=iq_setpoints[setpoint_index];
    	i_xy_reference.d=iX_setpoints[setpoint_index];
		i_xy_reference.q=iY_setpoints[setpoint_index];

    	// step throught the array
    	uint64_t current_uptime=uz_SystemTime_GetInterruptCounter();
    	if(current_uptime>(old_uptime +300 ) ){
    		old_uptime=current_uptime;

    		if(setpoint_index<21){
    			setpoint_index++;
    		}else{
    			setpoint_index=0;
    			select_automatic_idiq=false;
    			start_marker=0.0f;
    		}
    	}
		
    }else{
       	i_dq_reference.d = i_d_ref;
       	i_dq_reference.q = i_q_ref;
       	i_xy_reference.d = i_X_ref;
       	i_xy_reference.q = i_Y_ref;
    }



    //Take measurements independent of control_state
    if(select_Real) {
    	//Read out speed&position
        Global_Data.av.theta_elec = Global_Data.av.theta_elec - theta_offset;
        Global_Data.av.omega_mech = (Global_Data.av.mechanicalRotorSpeed / 60.0f) * (2.0f * UZ_PIf);
        Global_Data.av.omega_elec = Global_Data.av.omega_mech * polepairs;

        // Read out and convert ADC readings to currents in Amps
        Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV;
        Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV;
        Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV;
        Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
        Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV;
        Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV;
        Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV;
        Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

        // Read out and convert ADC readings to voltages
        Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV;
        Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV;
        Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV;
        Global_Data.av.v_dc2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV;
        Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV;
        Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV;

        //Read out inverter temp
        Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
        Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
        Global_Data.av.temp_VSI_1 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L1,
        		Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L2,
				Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L3);
        Global_Data.av.temp_VSI_2 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1,
               	Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2,
       			Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3);

        // check current limit
        if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
        	fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
        		uz_assert(0);
        }
           // check DC Bus
           if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
        	   uz_assert(0);
           }
           // check inverter temp
           if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG) {
        	   uz_assert(0);
           }

           //write to structs
           REAL_i_abc_meas.a1 = Global_Data.av.i_a1;
           REAL_i_abc_meas.b1 = Global_Data.av.i_b1;
           REAL_i_abc_meas.c1 = Global_Data.av.i_c1;
           REAL_i_abc_meas.a2 = Global_Data.av.i_a2;
           REAL_i_abc_meas.b2 = Global_Data.av.i_b2;
           REAL_i_abc_meas.c2 = Global_Data.av.i_c2;

           // calc u neutral voltage
           switch(NEUTRAL_CONFIG){
           case 1U:{
           	u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1 + Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2) / 6.0f;
           	u_n2 = u_n1;
           	break;
           }
           case 2U:{
           	u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1)/3.0f;
           	u_n2 = (Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2)/3.0f;
           	break;
           }
           default: break;
           }

           // calc phase voltages with neutral voltage
           REAL_v_abc_meas.a1 = Global_Data.av.v_a1 - u_n1;
           REAL_v_abc_meas.b1 = Global_Data.av.v_b1 - u_n1;
           REAL_v_abc_meas.c1 = Global_Data.av.v_c1 - u_n1;
           REAL_v_abc_meas.a2 = Global_Data.av.v_a2 - u_n2;
           REAL_v_abc_meas.b2 = Global_Data.av.v_b2 - u_n2;
           REAL_v_abc_meas.c2 = Global_Data.av.v_c2 - u_n2;

           //VSD-Transformation
           REAL_i_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(REAL_i_abc_meas, Global_Data.av.theta_elec);
           Global_Data.av.I_d = REAL_i_dqxy_meas.d;
           Global_Data.av.I_q = REAL_i_dqxy_meas.q;
           Global_Data.av.I_X = REAL_i_dqxy_meas.x;
           Global_Data.av.I_Y = REAL_i_dqxy_meas.y;

           REAL_v_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(REAL_v_abc_meas, Global_Data.av.theta_elec);
		   Global_Data.av.U_d = v_dqxy_limited_volts.d;
		   Global_Data.av.U_q = v_dqxy_limited_volts.q;
		   Global_Data.av.U_X = v_dqxy_limited_volts.x;
		   Global_Data.av.U_Y = v_dqxy_limited_volts.y;

		   //Only allow enable of inverter, if "select_Real" is true
           if (current_state == running_state || current_state == control_state) {
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
           } else {
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
           }
       }


   //-----------------------------------------------------------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
   //-------------------------------------------CONTROL---------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
       if (current_state==control_state)
       {
           if(select_CIL) {
           	CIL_omega_mech = (n_ref_rpm / 60.0f) * 2.0f * UZ_PIf;
           	if(reset) {
           		uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
           	}


           	CIL_out_general = uz_pmsm_model6ph_dq_get_outputs_general(Global_Data.objects.CIL_pmsm);    // read out resulting general outputs
           	CIL_i_dqxy_meas = uz_pmsm_model6ph_dq_get_output_currents(Global_Data.objects.CIL_pmsm);   // read out actual currents
           	Global_Data.av.mechanicalRotorSpeed = (CIL_out_general.omega_mech * 60.0f) / (2.0f * UZ_PIf);
           	Global_Data.av.omega_elec = CIL_out_general.omega_mech * polepairs;
           	CIL_i_dq_meas.d = CIL_i_dqxy_meas.d;
           	CIL_i_dq_meas.q = CIL_i_dqxy_meas.q;
           	CIL_i_xy_meas.d = CIL_i_dqxy_meas.x;
           	CIL_i_xy_meas.q = CIL_i_dqxy_meas.y;
           	CIL_i_z1z2_meas.d = CIL_i_dqxy_meas.z1;
           	CIL_i_z1z2_meas.q = CIL_i_dqxy_meas.z2;
           	Global_Data.av.I_d = CIL_i_dqxy_meas.d;
           	Global_Data.av.I_q = CIL_i_dqxy_meas.q;
           	Global_Data.av.I_X = CIL_i_dqxy_meas.x;
           	Global_Data.av.I_Y = CIL_i_dqxy_meas.y;
           	Global_Data.av.U_d = v_dqxy_limited_volts.d;
           	Global_Data.av.U_q = v_dqxy_limited_volts.q;
           	Global_Data.av.U_X = v_dqxy_limited_volts.x;
           	Global_Data.av.U_Y = v_dqxy_limited_volts.y;
           	
           	uz_6ph_abc_t temp = uz_transformation_asym30deg_6ph_dq_xy_to_abc(CIL_i_dqxy_meas,CIL_out_general.theta_el);
           	Global_Data.av.i_a1 = temp.a1;
        	Global_Data.av.i_b1 = temp.b1;
        	Global_Data.av.i_c1 = temp.c1;
        	Global_Data.av.i_a2 = temp.a2;
        	Global_Data.av.i_b2 = temp.b2;
        	Global_Data.av.i_c2 = temp.c2;

           	if(select_CurrentControl) {
           		v_dq_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, i_dq_reference, CIL_i_dq_meas, V_DC_Volts, Global_Data.av.omega_elec);
           		v_xy_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance, i_xy_reference, CIL_i_xy_meas, V_DC_Volts, Global_Data.av.omega_elec);

           	} else if(select_DDPG_1_64) {
       			if(ext_clamping_dq == false && ext_clamping_xy == false) {
       				i_dqxy_integrated_error.d = (i_dqxy_integrated_error.d + (i_dqxy_error.d * ts)); // use Forward-Euler with error of previous timestep for integration
       				i_dqxy_integrated_error.q = (i_dqxy_integrated_error.q + (i_dqxy_error.q * ts));
       				i_dqxy_integrated_error.x = (i_dqxy_integrated_error.x + (i_dqxy_error.x * ts));
       				i_dqxy_integrated_error.y = (i_dqxy_integrated_error.y + (i_dqxy_error.y * ts));
       			} else {
       				i_dqxy_integrated_error.d += 0.0f;
       				i_dqxy_integrated_error.q += 0.0f;
       				i_dqxy_integrated_error.x += 0.0f;
       				i_dqxy_integrated_error.y += 0.0f;
       			}
       		i_dqxy_error.d = (i_dq_reference.d - CIL_i_dqxy_meas.d) / rated_current;
       		i_dqxy_error.q = (i_dq_reference.q - CIL_i_dqxy_meas.q) / rated_current;
       		i_dqxy_error.x = (i_xy_reference.d - CIL_i_dqxy_meas.x) / rated_current;
       		i_dqxy_error.y = (i_xy_reference.q - CIL_i_dqxy_meas.y) / rated_current;
#if NN_15_INPUT_1_64==1
       		observation_ip_15n[0] = i_dqxy_error.d;
       		observation_ip_15n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
       		observation_ip_15n[2] = i_dqxy_error.q;
       		observation_ip_15n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
       		observation_ip_15n[4] = CIL_i_dqxy_meas.d / rated_current;
       		observation_ip_15n[5] = CIL_i_dqxy_meas.q / rated_current;
       		observation_ip_15n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
       		observation_ip_15n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
       		observation_ip_15n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
       		observation_ip_15n[9] = i_dqxy_error.x;
       		observation_ip_15n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
       		observation_ip_15n[11] = i_dqxy_error.y;
       		observation_ip_15n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
       		observation_ip_15n[13] = v_dqxy_limited_volts.x * Voltage_Scaling;
       		observation_ip_15n[14] = v_dqxy_limited_volts.y * Voltage_Scaling;
   	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_15N; i++) {
   	        	uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_15n,observation_ip_15n[i],0U,i);
   	        }
   	        uz_nn_ff(Global_Data.objects.nn_layer_15n,Global_Data.objects.matrix_input_15n);
   	        matrix_output_15n = uz_nn_get_output_data(Global_Data.objects.nn_layer_15n);
   	        uz_matrix_multiply_by_scalar(matrix_output_15n,U_max); // scaling layer of nn
   	        v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,0U);
   	        v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,1U);
   	        v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,2U);
   	        v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,3U);
#endif
#if NN_17_INPUT_1_64==1
       		observation_ip_17n[0] = i_dqxy_error.d;
       		observation_ip_17n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
       		observation_ip_17n[2] = i_dqxy_error.q;
       		observation_ip_17n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
       		observation_ip_17n[4] = CIL_i_dqxy_meas.d / rated_current;
       		observation_ip_17n[5] = CIL_i_dqxy_meas.q / rated_current;
       		observation_ip_17n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
       		observation_ip_17n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
       		observation_ip_17n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
       		observation_ip_17n[9] = i_dqxy_error.x;
       		observation_ip_17n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
       		observation_ip_17n[11] = i_dqxy_error.y;
       		observation_ip_17n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
       		observation_ip_17n[13] = CIL_i_dqxy_meas.x / rated_current;
       		observation_ip_17n[14] = CIL_i_dqxy_meas.y / rated_current;
       		observation_ip_17n[15] = v_dqxy_limited_volts.x * Voltage_Scaling;
       		observation_ip_17n[16] = v_dqxy_limited_volts.y * Voltage_Scaling;
   	        for (uint32_t i = 0; i < NUMBER_OF_INPUTS_17N; i++) {
   	        	uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_17n,observation_ip_17n[i],0U,i);
   	        }
   	        uz_nn_ff(Global_Data.objects.nn_layer_17n,Global_Data.objects.matrix_input_17n);
   	        matrix_output_17n = uz_nn_get_output_data(Global_Data.objects.nn_layer_17n);
   	        uz_matrix_multiply_by_scalar(matrix_output_17n,U_max); // scaling layer of nn
   	        v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,0U);
   	        v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,1U);
   	        v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,2U);
   	        v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,3U);
#endif

           	v_dq_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_volts, V_DC_Volts, max_modulation_index, Global_Data.av.omega_elec, CIL_i_dq_meas, &ext_clamping_dq);
   			v_xy_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_xy_non_limited_volts, V_DC_Volts, max_modulation_index, Global_Data.av.omega_elec, CIL_i_xy_meas, &ext_clamping_xy);

           	}

           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
           	v_dqxy_limited_volts.z1 = 0.0f;
           	v_dqxy_limited_volts.z2 = 0.0f;
           	uz_pmsm_model6ph_dq_set_inputs_general(Global_Data.objects.CIL_pmsm,CIL_omega_mech,0.0f);   // set fixed speed, because load simulation is disabled by pmsm_config.simulate_mechanical_system
           	uz_pmsm_model6ph_dq_set_voltage(Global_Data.objects.CIL_pmsm,v_dqxy_limited_volts);

           } else {
           	uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
           }

           if(select_Real) {
           	REAL_i_dq_meas.d = REAL_i_dqxy_meas.d;
           	REAL_i_dq_meas.q = REAL_i_dqxy_meas.q;
           	REAL_i_xy_meas.d = REAL_i_dqxy_meas.x;
           	REAL_i_xy_meas.q = REAL_i_dqxy_meas.y;
           	REAL_i_z1z2_meas.d = REAL_i_dqxy_meas.z1;
           	REAL_i_z1z2_meas.q = REAL_i_dqxy_meas.z2;

           	if(select_CurrentControl) {
           		v_dq_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, i_dq_reference, REAL_i_dq_meas, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
           		v_xy_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance, i_xy_reference, REAL_i_xy_meas, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);

           	} else if(select_DDPG_1_64) {
       			if(ext_clamping_dq == false && ext_clamping_xy == false) {
       				i_dqxy_integrated_error.d = (i_dqxy_integrated_error.d + (i_dqxy_error.d * ts)); // use Forward-Euler with error of previous timestep for integration
       				i_dqxy_integrated_error.q = (i_dqxy_integrated_error.q + (i_dqxy_error.q * ts));
       				i_dqxy_integrated_error.x = (i_dqxy_integrated_error.x + (i_dqxy_error.x * ts));
       				i_dqxy_integrated_error.y = (i_dqxy_integrated_error.y + (i_dqxy_error.y * ts));
       			} else {
       				i_dqxy_integrated_error.d += 0.0f;
       				i_dqxy_integrated_error.q += 0.0f;
       				i_dqxy_integrated_error.x += 0.0f;
       				i_dqxy_integrated_error.y += 0.0f;
       			}
           		i_dqxy_error.d = (i_dq_reference.d - REAL_i_dqxy_meas.d) / rated_current;
           		i_dqxy_error.q = (i_dq_reference.q - REAL_i_dqxy_meas.q) / rated_current;
           		i_dqxy_error.x = (i_xy_reference.d - REAL_i_dqxy_meas.x) / rated_current;
           		i_dqxy_error.y = (i_xy_reference.q - REAL_i_dqxy_meas.y) / rated_current;
#if NN_15_INPUT_1_64==1
           		observation_ip_15n[0] = i_dqxy_error.d;
           		observation_ip_15n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
           		observation_ip_15n[2] = i_dqxy_error.q;
           		observation_ip_15n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
           		observation_ip_15n[4] = REAL_i_dqxy_meas.d / rated_current;
           		observation_ip_15n[5] = REAL_i_dqxy_meas.q / rated_current;
           		observation_ip_15n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
           		observation_ip_15n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
           		observation_ip_15n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
           		observation_ip_15n[9] = i_dqxy_error.x;
           		observation_ip_15n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
           		observation_ip_15n[11] = i_dqxy_error.y;
           		observation_ip_15n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
           		observation_ip_15n[13] = v_dqxy_limited_volts.x * Voltage_Scaling;
           		observation_ip_15n[14] = v_dqxy_limited_volts.y * Voltage_Scaling;
           		for (uint32_t i = 0; i < NUMBER_OF_INPUTS_15N; i++) {
           			uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_15n,observation_ip_15n[i],0U,i);
           		}
           		uz_nn_ff(Global_Data.objects.nn_layer_15n,Global_Data.objects.matrix_input_15n);
           		matrix_output_15n = uz_nn_get_output_data(Global_Data.objects.nn_layer_15n);
           		uz_matrix_multiply_by_scalar(matrix_output_15n,U_max); // scaling layer of nn
           		v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,0U);
           		v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,1U);
           		v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_15n,0U,2U);
           		v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_15n,0U,3U);
#endif

#if NN_17_INPUT_1_64==1
           		observation_ip_17n[0] = i_dqxy_error.d;
           		observation_ip_17n[1] = i_dqxy_integrated_error.d * UZ_ISR_FREQUENCY;
           		observation_ip_17n[2] = i_dqxy_error.q;
           		observation_ip_17n[3] = i_dqxy_integrated_error.q * UZ_ISR_FREQUENCY;
           		observation_ip_17n[4] = REAL_i_dqxy_meas.d / rated_current;
           		observation_ip_17n[5] = REAL_i_dqxy_meas.q / rated_current;
           		observation_ip_17n[6] = Global_Data.av.mechanicalRotorSpeed * speed_weight;
           		observation_ip_17n[7] = v_dqxy_limited_volts.d * Voltage_Scaling;
           		observation_ip_17n[8] = v_dqxy_limited_volts.q * Voltage_Scaling;
           		observation_ip_17n[9] = i_dqxy_error.x;
           		observation_ip_17n[10] = i_dqxy_integrated_error.x * UZ_ISR_FREQUENCY;
           		observation_ip_17n[11] = i_dqxy_error.y;
           		observation_ip_17n[12] = i_dqxy_integrated_error.y * UZ_ISR_FREQUENCY;
           		observation_ip_17n[13] = REAL_i_dqxy_meas.x / rated_current;
           		observation_ip_17n[14] = REAL_i_dqxy_meas.y / rated_current;
           		observation_ip_17n[15] = v_dqxy_limited_volts.x * Voltage_Scaling;
           		observation_ip_17n[16] = v_dqxy_limited_volts.y * Voltage_Scaling;
           		for (uint32_t i = 0; i < NUMBER_OF_INPUTS_17N; i++) {
           			uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_17n,observation_ip_17n[i],0U,i);
           		}
           		uz_nn_ff(Global_Data.objects.nn_layer_17n,Global_Data.objects.matrix_input_17n);
           		matrix_output_17n = uz_nn_get_output_data(Global_Data.objects.nn_layer_17n);
           		uz_matrix_multiply_by_scalar(matrix_output_17n,U_max); // scaling layer of nn
           		v_dq_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,0U);
           		v_dq_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,1U);
           		v_xy_non_limited_volts.d = uz_matrix_get_element_zero_based(matrix_output_17n,0U,2U);
           		v_xy_non_limited_volts.q = uz_matrix_get_element_zero_based(matrix_output_17n,0U,3U);
#endif
           		v_dq_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_dq_non_limited_volts, V_DC_Volts, max_modulation_index, Global_Data.av.omega_elec, REAL_i_dq_meas, &ext_clamping_dq);
           		v_xy_limited_volts = uz_CurrentControl_SpaceVector_Limitation(v_xy_non_limited_volts, V_DC_Volts, max_modulation_index, Global_Data.av.omega_elec, REAL_i_xy_meas, &ext_clamping_xy);

           	}

           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
           	v_dqxy_limited_volts.z1 = 0.0f;
           	v_dqxy_limited_volts.z2 = 0.0f;
           	REAL_v_abc_ref = uz_transformation_asym30deg_6ph_dq_xy_to_abc(v_dqxy_limited_volts, Global_Data.av.theta_elec);
           	DutyCycle_output = uz_spwm_abc_6ph(REAL_v_abc_ref, V_DC_Volts);
           	Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.system1.DutyCycle_A;
           	Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.system1.DutyCycle_B;
           	Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.system1.DutyCycle_C;
           	Global_Data.rasv.halfBridge4DutyCycle = DutyCycle_output.system2.DutyCycle_A;
           	Global_Data.rasv.halfBridge5DutyCycle = DutyCycle_output.system2.DutyCycle_B;
           	Global_Data.rasv.halfBridge6DutyCycle = DutyCycle_output.system2.DutyCycle_C;

           }

       } else {
       	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance);
       	uz_CurrentControl_reset(Global_Data.objects.CC_xy_instance);
       	ext_clamping_dq = false;
       	ext_clamping_xy = false;
       	v_dq_limited_volts.d = 0.0f;
       	v_dq_limited_volts.q = 0.0f;
       	v_xy_limited_volts.d = 0.0f;
       	v_xy_limited_volts.q = 0.0f;
       	i_dqxy_integrated_error.d = 0.0f;
       	i_dqxy_integrated_error.q = 0.0f;
       	i_dqxy_integrated_error.x = 0.0f;
       	i_dqxy_integrated_error.y = 0.0f;
       	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
       }

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}


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
