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
#include "../uz/uz_more_pwm_6ph/uz_zero_injection_based_pwm.h"

#include "../uz/uz_more_pwm_6ph/uz_zero_injection_dual_3ph_pwm.h"
#include "../uz/uz_more_pwm_6ph/uz_zero_injection_pwm_3ph.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

//Changes
struct uz_pmsm_model6ph_dq_outputs_general_t CIL_out_general = {0};


float CIL_omega_mech = 100.0f; //fixed speed for the CIL model
float ts = 1.0f / UZ_ISR_FREQUENCY;
float V_DC_Volts = 36.0f;
float polepairs = 5.0f;

float theta_el_advanced = 0.0f;
int reset = 0U;
//Offset from Valentin
float theta_offset = 5.93f;
#define PHASE_CURRENT_CONV 12.5f
#define PHASE_VOLT_CONV	12.0f

#define PHASE_CURRENT_CONV_A1	12.803f
#define PHASE_CURRENT_CONV_B1	12.663f
#define PHASE_CURRENT_CONV_C1	12.652f
#define PHASE_CURRENT_CONV_A2	12.67f
#define PHASE_CURRENT_CONV_B2	12.69f
#define PHASE_CURRENT_CONV_C2	12.643f

#define PHASE_CURRENT_OFFSET_A1	0.012f
#define PHASE_CURRENT_OFFSET_B1	0.004f
#define PHASE_CURRENT_OFFSET_C1	0.006f
#define PHASE_CURRENT_OFFSET_A2	-0.012f
#define PHASE_CURRENT_OFFSET_B2	-0.01f
#define PHASE_CURRENT_OFFSET_C2	0.019f

#define PHASE_VOLT_CONV_A1	11.963f
#define PHASE_VOLT_CONV_B1	11.959f
#define PHASE_VOLT_CONV_C1	11.954f
#define PHASE_VOLT_CONV_A2	11.959f
#define PHASE_VOLT_CONV_B2	11.959f
#define PHASE_VOLT_CONV_C2	11.961f

#define PHASE_VOLT_OFFSET_A1	-0.09f
#define PHASE_VOLT_OFFSET_B1	0.002f
#define PHASE_VOLT_OFFSET_C1	-0.065f
#define PHASE_VOLT_OFFSET_A2	-0.038f
#define PHASE_VOLT_OFFSET_B2	-0.049f
#define PHASE_VOLT_OFFSET_C2	-0.02f


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

bool ext_clamping = false;

bool filter_active = false;

uint64_t old_uptime=0U;
uint32_t setpoint_index=0U;
bool automatic_idiq_lock=false; // hack to only do it once
float start_marker=0.0f;
bool start_angle_found = false;
float theta_el_old = 0.0f;
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
    if(Global_Data.av.select_CIL) {
    	uz_pmsm_model6ph_trigger_voltage_input_strobe(Global_Data.objects.CIL_pmsm);
    	uz_pmsm_model6ph_trigger_current_output_strobe(Global_Data.objects.CIL_pmsm);
    }
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();




    //Take measurements independent of control_state
    if(Global_Data.av.select_Real) {
    	//Read out speed&position
        Global_Data.av.theta_elec = Global_Data.av.theta_elec - theta_offset;
        Global_Data.av.omega_mech = (Global_Data.av.mechanicalRotorSpeed / 60.0f) * (2.0f * UZ_PIf);
        Global_Data.av.omega_elec = Global_Data.av.omega_mech * polepairs;
        theta_el_advanced = Global_Data.av.theta_elec + 1.5f * ts * Global_Data.av.omega_elec;

        // Read out and convert ADC readings to currents in Amps
        Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1 +PHASE_CURRENT_OFFSET_A1;
        Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1 +PHASE_CURRENT_OFFSET_B1;
        Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1 +PHASE_CURRENT_OFFSET_C1;
        Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
        Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
        Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
        Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
        Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

        // Read out and convert ADC readings to voltages
        Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_A1 +PHASE_VOLT_OFFSET_A1;
        Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_B1 +PHASE_VOLT_OFFSET_B1;
        Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_C1 +PHASE_VOLT_OFFSET_C1;
        Global_Data.av.v_dc2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
        Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
        Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;

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

           	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
           	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
           	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
           	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
           	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
           	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
            uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
            uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);


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

           if(!filter_active){
        	   //write to structs
			   Global_Data.av.REAL_i_abc_meas.a1 = Global_Data.av.i_a1;
			   Global_Data.av.REAL_i_abc_meas.b1 = Global_Data.av.i_b1;
			   Global_Data.av.REAL_i_abc_meas.c1 = Global_Data.av.i_c1;
			   Global_Data.av.REAL_i_abc_meas.a2 = Global_Data.av.i_a2;
			   Global_Data.av.REAL_i_abc_meas.b2 = Global_Data.av.i_b2;
			   Global_Data.av.REAL_i_abc_meas.c2 = Global_Data.av.i_c2;
           }
           else{
               Global_Data.av.REAL_i_abc_meas.a1 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_A1, Global_Data.av.i_a1);
               Global_Data.av.REAL_i_abc_meas.b1 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_B1, Global_Data.av.i_b1);
               Global_Data.av.REAL_i_abc_meas.c1 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_C1, Global_Data.av.i_c1);
               Global_Data.av.REAL_i_abc_meas.a2 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_A2, Global_Data.av.i_a2);
               Global_Data.av.REAL_i_abc_meas.b2 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_B2, Global_Data.av.i_b2);
               Global_Data.av.REAL_i_abc_meas.c2 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_C2, Global_Data.av.i_c2);
           }


           Global_Data.av.REAL_i_abc_meas.a1 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_A1, Global_Data.av.i_a1);
           Global_Data.av.REAL_i_abc_meas.b1 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_B1, Global_Data.av.i_b1);
           Global_Data.av.REAL_i_abc_meas.c1 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_C1, Global_Data.av.i_c1);
           Global_Data.av.REAL_i_abc_meas.a2 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_A2, Global_Data.av.i_a2);
           Global_Data.av.REAL_i_abc_meas.b2 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_B2, Global_Data.av.i_b2);
           Global_Data.av.REAL_i_abc_meas.c2 = uz_signals_IIR_Filter_sample(Global_Data.objects.IRR_filter_C2, Global_Data.av.i_c2);




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
           Global_Data.av.REAL_v_abc_meas.a1 = Global_Data.av.v_a1 - u_n1;
           Global_Data.av.REAL_v_abc_meas.b1 = Global_Data.av.v_b1 - u_n1;
           Global_Data.av.REAL_v_abc_meas.c1 = Global_Data.av.v_c1 - u_n1;
           Global_Data.av.REAL_v_abc_meas.a2 = Global_Data.av.v_a2 - u_n2;
           Global_Data.av.REAL_v_abc_meas.b2 = Global_Data.av.v_b2 - u_n2;
           Global_Data.av.REAL_v_abc_meas.c2 = Global_Data.av.v_c2 - u_n2;

           //VSD-Transformation
           Global_Data.av.REAL_i_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(Global_Data.av.REAL_i_abc_meas, Global_Data.av.theta_elec);
           Global_Data.av.I_d = Global_Data.av.REAL_i_dqxy_meas.d;
           Global_Data.av.I_q = Global_Data.av.REAL_i_dqxy_meas.q;
           Global_Data.av.I_X = Global_Data.av.REAL_i_dqxy_meas.x;
           Global_Data.av.I_Y = Global_Data.av.REAL_i_dqxy_meas.y;

           Global_Data.av.REAL_v_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(Global_Data.av.REAL_v_abc_meas, Global_Data.av.theta_elec);
		   Global_Data.av.U_d = Global_Data.av.v_dqxy_limited_volts.d;
		   Global_Data.av.U_q = Global_Data.av.v_dqxy_limited_volts.q;
		   Global_Data.av.U_X = Global_Data.av.v_dqxy_limited_volts.x;
		   Global_Data.av.U_Y = Global_Data.av.v_dqxy_limited_volts.y;

		   //Only allow enable of inverter, if "select_Real" is true
           if (current_state == running_state || current_state == control_state) {
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
           } else {
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
           }
       }


       	Global_Data.av.i_dq_reference.d = Global_Data.av.i_d_ref;
       	Global_Data.av.i_dq_reference.q = Global_Data.av.i_q_ref;
       	Global_Data.av.i_xy_reference.d = Global_Data.av.i_X_ref;
       	Global_Data.av.i_xy_reference.q = Global_Data.av.i_Y_ref;

    theta_el_old = Global_Data.av.theta_elec;



    //-----------------------------------------------------------------------------------------------------------------------------//
    //-----------------------------------------------------------------------------------------------------------------------------//
    //-------------------------------------------TEST PWM--------------------------------------------------------------------------//
    //-----------------------------------------------------------------------------------------------------------------------------//
    //-----------------------------------------------------------------------------------------------------------------------------//




   	Global_Data.av.v_dqxy_ref.d = Global_Data.av.i_d_ref;
   	Global_Data.av.v_dqxy_ref.q = Global_Data.av.i_q_ref;
   	Global_Data.av.v_dqxy_ref.x = Global_Data.av.i_X_ref;
   	Global_Data.av.v_dqxy_ref.y = Global_Data.av.i_Y_ref;

	Global_Data.av.u_ref_6ph_alphabeta =  uz_transformation_asym30deg_6ph_dq_to_alphabeta(Global_Data.av.v_dqxy_ref, Global_Data.av.theta_elec);

	Global_Data.av.u_ref_6ph_abc =  uz_transformation_asym30deg_6ph_dq_to_abc(Global_Data.av.v_dqxy_ref, Global_Data.av.theta_elec);

	Global_Data.av.u_ref_abc.a = Global_Data.av.u_ref_6ph_abc.a1;
	Global_Data.av.u_ref_abc.b = Global_Data.av.u_ref_6ph_abc.b1;
	Global_Data.av.u_ref_abc.c = Global_Data.av.u_ref_6ph_abc.c1;

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(Global_Data.av.u_ref_abc);


   	float phi_rad = 0.0f;

   	Global_Data.av.U_ZK = 36.0f;

   	// Tested: 1,2,3, 4, 5, 6, 7, 8, 10, 11, 12

   	// Fehler: 9, 21,

   	switch(Global_Data.av.PWM_select){
   	case 1:
   		Global_Data.av.test_var += 1;
   		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_PWM_THI_1_4_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
   		break;
   	case 2:
   		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_PWM_THI_1_6_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
   		break;
   	case 3:
   		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_SVM_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
   		break;
   	case 4:
   		//Global_Data.av.DutyCycle_6ph_test.system1 =  uz_GDPWM_abc_3ph(Global_Data.av.u_ref_abc, phi_rad, Global_Data.av.U_ZK);

   		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_GDPWM_abc_3ph_V2(Global_Data.av.u_ref_abc, Global_Data.av.phi_rad, Global_Data.av.U_ZK);
   		break;
   	case 5:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM0_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 6:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM1_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 7:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM1PHI_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 8:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM2_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 9:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM3_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 10:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM3PHI_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 11:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM_MAX_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;
   	case 12:
		Global_Data.av.DutyCycle_6ph_test.system1 =  uz_DPWM_MIN_abc_3ph(Global_Data.av.u_ref_abc, Global_Data.av.U_ZK);
		break;


   	case 13:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_PWM_THI_1_4_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 14:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_PWM_THI_1_6_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 15:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_SVM_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 16:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_GDPWM_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, phi_rad, Global_Data.av.U_ZK);
		break;
   	case 17:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM0_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 18:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM1_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 19:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM1PHI_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 20:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM2_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 21:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM3_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 22:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM3PHI_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 23:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM_MAX_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 24:
		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM_MIN_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;

   	case 25:
		Global_Data.av.DutyCycle_6ph_test = uz_6ph_CSVPWM_24_4_active_SV_V1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 26:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_CSVPWM_24_4_active_SV_V2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 27:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_CSVPWM_24_5_active_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 28:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 29:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 30:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 31:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 32:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_2M_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 33:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_2M_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 34:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 35:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 36:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v1_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 37:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v1_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 38:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v2_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 39:
		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v2_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.U_ZK);
		break;
   	case 40:
   		Global_Data.av.DutyCycle_6ph_test =   uz_Dual_GDPWM_alphabeta_6ph_V2(Global_Data.av.u_ref_6ph_alphabeta,Global_Data.av.phi_rad, Global_Data.av.U_ZK);

   	default:

   		break;

   	}


   	//Global_Data.av.DutyCycle_6ph_test = uz_6ph_calculated_dutycycle_and_phaseshift(Global_Data.av.DutyCycle_6ph_test, Global_Data.av.phaseshiftoption, &Global_Data.av.shift_system_1, &Global_Data.av.shift_system_2);


   //-----------------------------------------------------------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
   //-------------------------------------------CONTROL---------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
       if (current_state==control_state)
       {
           if(Global_Data.av.select_CIL) {
           	CIL_omega_mech = (Global_Data.av.n_ref_rpm / 60.0f) * 2.0f * UZ_PIf;
           	if(reset) {
           		uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
           	}


           	CIL_out_general = uz_pmsm_model6ph_dq_get_outputs_general(Global_Data.objects.CIL_pmsm);    // read out resulting general outputs
           	Global_Data.av.CIL_i_dqxy_meas = uz_pmsm_model6ph_dq_get_output_currents(Global_Data.objects.CIL_pmsm);   // read out actual currents
           	Global_Data.av.mechanicalRotorSpeed = (CIL_out_general.omega_mech * 60.0f) / (2.0f * UZ_PIf);
           	Global_Data.av.omega_elec = CIL_out_general.omega_mech * polepairs;
           	Global_Data.av.CIL_i_dq_meas.d = Global_Data.av.CIL_i_dqxy_meas.d;
           	Global_Data.av.CIL_i_dq_meas.q = Global_Data.av.CIL_i_dqxy_meas.q;
           	Global_Data.av.CIL_i_xy_meas.d = Global_Data.av.CIL_i_dqxy_meas.x;
           	Global_Data.av.CIL_i_xy_meas.q = Global_Data.av.CIL_i_dqxy_meas.y;
           	Global_Data.av.CIL_i_z1z2_meas.d = Global_Data.av.CIL_i_dqxy_meas.z1;
           	Global_Data.av.CIL_i_z1z2_meas.q = Global_Data.av.CIL_i_dqxy_meas.z2;
           	Global_Data.av.I_d = Global_Data.av.CIL_i_dqxy_meas.d;
           	Global_Data.av.I_q = Global_Data.av.CIL_i_dqxy_meas.q;
           	Global_Data.av.I_X = Global_Data.av.CIL_i_dqxy_meas.x;
           	Global_Data.av.I_Y = Global_Data.av.CIL_i_dqxy_meas.y;
           	Global_Data.av.U_d = Global_Data.av.v_dqxy_limited_volts.d;
           	Global_Data.av.U_q = Global_Data.av.v_dqxy_limited_volts.q;
           	Global_Data.av.U_X = Global_Data.av.v_dqxy_limited_volts.x;
           	Global_Data.av.U_Y = Global_Data.av.v_dqxy_limited_volts.y;
           	
           	uz_6ph_abc_t temp = uz_transformation_asym30deg_6ph_dq_xy_to_abc(Global_Data.av.CIL_i_dqxy_meas,CIL_out_general.theta_el);
           	Global_Data.av.i_a1 = temp.a1;
        	Global_Data.av.i_b1 = temp.b1;
        	Global_Data.av.i_c1 = temp.c1;
        	Global_Data.av.i_a2 = temp.a2;
        	Global_Data.av.i_b2 = temp.b2;
        	Global_Data.av.i_c2 = temp.c2;

           	if(Global_Data.av.select_CurrentControl) {
           		Global_Data.av.v_dq_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, Global_Data.av.i_dq_reference, Global_Data.av.CIL_i_dq_meas, V_DC_Volts, Global_Data.av.omega_elec);
           		Global_Data.av.v_xy_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance, Global_Data.av.i_xy_reference, Global_Data.av.CIL_i_xy_meas, V_DC_Volts, Global_Data.av.omega_elec);
           		Global_Data.av.v_dqxy_non_limited_volts.d = Global_Data.av.v_dq_limited_volts.d;
           		Global_Data.av.v_dqxy_non_limited_volts.q = Global_Data.av.v_dq_limited_volts.q;
           		Global_Data.av.v_dqxy_non_limited_volts.x = Global_Data.av.v_xy_limited_volts.d;
           		Global_Data.av.v_dqxy_non_limited_volts.y = Global_Data.av.v_xy_limited_volts.q;
           	}


           	Global_Data.av.v_dqxy_limited_volts = uz_6ph_Space_Vector_Limitation(Global_Data.av.v_dqxy_non_limited_volts, V_DC_Volts, 0.5f, Global_Data.av.omega_elec, Global_Data.av.CIL_i_dqxy_meas, &ext_clamping);
//           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
//           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
//           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
//           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
//           	v_dqxy_limited_volts.z1 = 0.0f;
//           	v_dqxy_limited_volts.z2 = 0.0f;
           	uz_pmsm_model6ph_dq_set_inputs_general(Global_Data.objects.CIL_pmsm,CIL_omega_mech,0.0f);   // set fixed speed, because load simulation is disabled by pmsm_config.simulate_mechanical_system
           	uz_pmsm_model6ph_dq_set_voltage(Global_Data.objects.CIL_pmsm,Global_Data.av.v_dqxy_limited_volts);

           } else {
           	uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
           }





           if(Global_Data.av.select_Real) {
        	   Global_Data.av.REAL_i_dq_meas.d = Global_Data.av.REAL_i_dqxy_meas.d;
        	   Global_Data.av.REAL_i_dq_meas.q = Global_Data.av.REAL_i_dqxy_meas.q;
        	   Global_Data.av.REAL_i_xy_meas.d = Global_Data.av.REAL_i_dqxy_meas.x;
        	   Global_Data.av.REAL_i_xy_meas.q = Global_Data.av.REAL_i_dqxy_meas.y;
        	   Global_Data.av.REAL_i_z1z2_meas.d = Global_Data.av.REAL_i_dqxy_meas.z1;
        	   Global_Data.av.REAL_i_z1z2_meas.q = Global_Data.av.REAL_i_dqxy_meas.z2;

           	if(Global_Data.av.select_CurrentControl) {
           		Global_Data.av.v_dq_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, Global_Data.av.i_dq_reference, Global_Data.av.REAL_i_dq_meas, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
           		Global_Data.av.v_xy_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance,Global_Data.av. i_xy_reference, Global_Data.av.REAL_i_xy_meas, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
           		Global_Data.av.v_dqxy_non_limited_volts.d = Global_Data.av.v_dq_limited_volts.d;
           		Global_Data.av.v_dqxy_non_limited_volts.q = Global_Data.av.v_dq_limited_volts.q;
           		Global_Data.av.v_dqxy_non_limited_volts.x = Global_Data.av.v_xy_limited_volts.d;
           		Global_Data.av.v_dqxy_non_limited_volts.y = Global_Data.av.v_xy_limited_volts.q;

           		Global_Data.av.v_dqxy_non_limited_volts.x = 0.0f;
           		Global_Data.av.v_dqxy_non_limited_volts.y = 0.0f;

           		uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
                uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
           	}
           	Global_Data.av.v_dqxy_limited_volts = uz_6ph_Space_Vector_Limitation(Global_Data.av.v_dqxy_non_limited_volts, V_DC_Volts, 0.5f, Global_Data.av.omega_elec, Global_Data.av.REAL_i_dqxy_meas, &ext_clamping);
//           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
//           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
//           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
//           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
//           	v_dqxy_limited_volts.z1 = 0.0f;
//           	v_dqxy_limited_volts.z2 = 0.0f;
           	Global_Data.av.REAL_v_abc_ref = uz_transformation_asym30deg_6ph_dq_xy_to_abc(Global_Data.av.v_dqxy_limited_volts, Global_Data.av.theta_elec);
           	Global_Data.av.REAL_v_vsd_ref = uz_transformation_asym30deg_6ph_dq_xy_to_alphabeta_XY(Global_Data.av.v_dqxy_limited_volts, Global_Data.av.theta_elec);
           	//REAL_v_abc_ref = uz_transformation_asym30deg_6ph_dq_xy_to_abc(v_dqxy_limited_volts, theta_el_advanced);

           	Global_Data.av.DutyCycle_output = uz_spwm_abc_6ph(Global_Data.av.REAL_v_abc_ref, Global_Data.av.v_dc1);



           	Global_Data.av.u_ref_6ph_alphabeta = Global_Data.av.REAL_v_vsd_ref;

            Global_Data.av.V_DC_Volts = Global_Data.av.v_dc1;

            /*
           	switch(Global_Data.av.PWM_select){

           	case 13:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_PWM_THI_1_4_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 14:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_PWM_THI_1_6_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 15:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_SVM_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 16:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_GDPWM_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, phi_rad, Global_Data.av.V_DC_Volts);
        		break;
           	case 17:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM0_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 18:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM1_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 19:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM1PHI_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 20:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM2_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 21:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM3_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 22:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM3PHI_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 23:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM_MAX_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 24:
        		Global_Data.av.DutyCycle_6ph_test = uz_Dual_DPWM_MIN_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;

           	case 25:
        		Global_Data.av.DutyCycle_6ph_test = uz_6ph_CSVPWM_24_4_active_SV_V1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 26:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_CSVPWM_24_4_active_SV_V2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 27:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_CSVPWM_24_5_active_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 28:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 29:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 30:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 31:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 32:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_2M_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 33:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_2M_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 34:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 35:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 36:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v1_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 37:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v1_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 38:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v2_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 39:
        		Global_Data.av.DutyCycle_6ph_test =  uz_6ph_DSVPWM_24_3L_1M_v2_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;


           	default:

           		Global_Data.av.DutyCycle_6ph_test = uz_spwm_abc_6ph(Global_Data.av.REAL_v_abc_ref, V_DC_Volts);

           		break;

           	}
            */

            // Brutal: 16, 17,    21 besser als 22!   18 besser als 19 -> jeweils das ohne Winkel berechnung mit atan2 ist besser!

           	switch(Global_Data.av.PWM_select){

           	case 13:
        		Global_Data.av.DutyCycle_output = uz_Dual_PWM_THI_1_4_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 14:
        		Global_Data.av.DutyCycle_output = uz_Dual_PWM_THI_1_6_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 15:
        		Global_Data.av.DutyCycle_output = uz_Dual_SVM_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 16:
        		Global_Data.av.DutyCycle_output = uz_Dual_GDPWM_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, phi_rad, Global_Data.av.V_DC_Volts);
        		break;
           	case 17:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM0_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 18:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM1_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 19:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM1PHI_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 20:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM2_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 21:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM3_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 22:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM3PHI_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 23:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM_MAX_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 24:
        		Global_Data.av.DutyCycle_output = uz_Dual_DPWM_MIN_alphabeta_6ph(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;

           	case 25:
        		Global_Data.av.DutyCycle_output = uz_6ph_CSVPWM_24_4_active_SV_V1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 26:
        		Global_Data.av.DutyCycle_output =  uz_6ph_CSVPWM_24_4_active_SV_V2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 27:
        		Global_Data.av.DutyCycle_output =  uz_6ph_CSVPWM_24_5_active_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 28:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 29:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 30:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 31:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 32:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_3L_2M_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 33:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_3L_2M_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 34:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 35:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 36:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_3L_1M_v1_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 37:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_3L_1M_v1_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 38:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_3L_1M_v2_D1_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;
           	case 39:
        		Global_Data.av.DutyCycle_output =  uz_6ph_DSVPWM_24_3L_1M_v2_D2_alphabeta_INJ(Global_Data.av.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
        		break;


           	default:

           		Global_Data.av.DutyCycle_output = uz_spwm_abc_6ph(Global_Data.av.REAL_v_abc_ref,  Global_Data.av.V_DC_Volts);

           		break;

           	}







           	//struct uz_DutyCycle_t  uz_Space_Vector_Modulation(uz_3ph_dq_t v_ref_Volts, float V_DC_Volts, float theta_el_rad);

           	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.DutyCycle_output.system1.DutyCycle_A;
           	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.DutyCycle_output.system1.DutyCycle_B;
           	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.DutyCycle_output.system1.DutyCycle_C;
           	Global_Data.rasv.halfBridge4DutyCycle = Global_Data.av.DutyCycle_output.system2.DutyCycle_A;
           	Global_Data.rasv.halfBridge5DutyCycle = Global_Data.av.DutyCycle_output.system2.DutyCycle_B;
           	Global_Data.rasv.halfBridge6DutyCycle = Global_Data.av.DutyCycle_output.system2.DutyCycle_C;

           }

       } else {
       	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance);
       	uz_CurrentControl_reset(Global_Data.objects.CC_xy_instance);
       	ext_clamping = false;
       	Global_Data.av.v_dq_limited_volts.d = 0.0f;
       	Global_Data.av.v_dq_limited_volts.q = 0.0f;
       	Global_Data.av.v_xy_limited_volts.d = 0.0f;
       	Global_Data.av.v_xy_limited_volts.q = 0.0f;
       	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
       	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
       }

       uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.av.shift_system_1, Global_Data.av.shift_system_1, Global_Data.av.shift_system_1);
       uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.av.shift_system_2, Global_Data.av.shift_system_2, Global_Data.av.shift_system_2);


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
