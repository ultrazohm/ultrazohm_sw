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
#include "../uz/uz_spwm/uz_spwm.h"
#include "../uz/uz_Space_Vector_Modulation_6ph/uz_Space_Vector_Modulation_6ph.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);


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
#define MAX_longtime_CURRENT_AMP  16.0f
#define MAX_PHASE_CURRENT_AMP_Last  16.0f
#define MAX_PHASE_CURRENT_AMP_Pruef 7.0f
int longtime_Current = 0;
int reset_longtime_Current =0;

#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f

#define NEUTRAL_CONFIG 2U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;

platform_state_t current_state;

float rad_to_deg = 180/M_PI;
struct uz_DutyCycle_t dutycyc_last = {0.0f};
//====================
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);
static void filter_compensation();
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    Global_Data.av.resolver_outputs_d4_Last = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Last);
    Global_Data.av.resolver_outputs_d4_Pruef = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Pruef);
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
    Global_Data.av.inverter_outputs_d3 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d3);

    // Read out and convert ADC readings to currents in Amps
    Global_Data.av.i_abc_meas.a1 = Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1 +PHASE_CURRENT_OFFSET_A1;
    Global_Data.av.i_abc_meas.b1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1 +PHASE_CURRENT_OFFSET_B1;
    Global_Data.av.i_abc_meas.c1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1 +PHASE_CURRENT_OFFSET_C1;
    Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_abc_meas.a2 = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
    Global_Data.av.i_abc_meas.b2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
    Global_Data.av.i_abc_meas.c2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
    Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_a_Last = Global_Data.aa.A3.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
    Global_Data.av.i_b_Last = Global_Data.aa.A3.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
    Global_Data.av.i_c_Last = Global_Data.aa.A3.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
    Global_Data.av.i_dc_Last = Global_Data.aa.A3.me.ADC_B5 * PHASE_CURRENT_CONV;

    // Read out and convert ADC readings to voltages
    Global_Data.av.u_dc1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLT_CONV;
    Global_Data.av.u_a1 = Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_A1 +PHASE_VOLT_OFFSET_A1;
    Global_Data.av.u_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_B1 +PHASE_VOLT_OFFSET_B1;
    Global_Data.av.u_c1 = Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_C1 +PHASE_VOLT_OFFSET_C1;
    Global_Data.av.u_dc2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
    Global_Data.av.u_a2 = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
    Global_Data.av.u_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
    Global_Data.av.u_c2 = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;
    Global_Data.av.u_dc_Last = Global_Data.aa.A3.me.ADC_A1 * PHASE_VOLT_CONV;
    Global_Data.av.u_a_Last = Global_Data.aa.A3.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
    Global_Data.av.u_b_Last = Global_Data.aa.A3.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
    Global_Data.av.u_c_Last = Global_Data.aa.A3.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;

    //Read out inverter temp
        Global_Data.av.temp_VSI_1 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L1,
        		Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L2,
    			Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L3);
        Global_Data.av.temp_VSI_2 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1,
               	Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2,
       			Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3);
        Global_Data.av.temp_VSI_3 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_L1,
               	Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_L2,
       			Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_L3);

//        // check current limit
        if(fabs(Global_Data.av.i_abc_meas.a1) > MAX_longtime_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.b1) > MAX_longtime_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.c1) > MAX_longtime_CURRENT_AMP ||
                	fabs(Global_Data.av.i_abc_meas.a2) > MAX_longtime_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.b2) > MAX_longtime_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.c2) > MAX_longtime_CURRENT_AMP||
                	    	fabs(Global_Data.av.i_a_Last) > MAX_longtime_CURRENT_AMP || fabs(Global_Data.av.i_b_Last) > MAX_longtime_CURRENT_AMP || fabs(Global_Data.av.i_c_Last) > MAX_longtime_CURRENT_AMP) {

        	if(fabs(Global_Data.av.i_abc_meas.a1) > MAX_PHASE_CURRENT_AMP_Pruef || fabs(Global_Data.av.i_abc_meas.b1) > MAX_PHASE_CURRENT_AMP_Pruef || fabs(Global_Data.av.i_abc_meas.c1) > MAX_PHASE_CURRENT_AMP_Pruef ||
        			fabs(Global_Data.av.i_abc_meas.a2) > MAX_PHASE_CURRENT_AMP_Pruef || fabs(Global_Data.av.i_abc_meas.b2) > MAX_PHASE_CURRENT_AMP_Pruef || fabs(Global_Data.av.i_abc_meas.c2) > MAX_PHASE_CURRENT_AMP_Pruef||
        	    	fabs(Global_Data.av.i_a_Last) > MAX_PHASE_CURRENT_AMP_Last || fabs(Global_Data.av.i_b_Last) > MAX_PHASE_CURRENT_AMP_Last || fabs(Global_Data.av.i_c_Last) > MAX_PHASE_CURRENT_AMP_Last) {

        		ultrazohm_state_machine_set_stop(true);
        		Global_Data.av.error = 1;
        	}
        	longtime_Current ++;
        }
//        if(longtime_Current >= 6000){
//    		ultrazohm_state_machine_set_stop(true);
//    		Global_Data.av.error = 1.5;
//        	longtime_Current = 0;
//        }
        if(fabs(Global_Data.av.i_abc_meas.a1) < MAX_longtime_CURRENT_AMP && fabs(Global_Data.av.i_abc_meas.b1) < MAX_longtime_CURRENT_AMP && fabs(Global_Data.av.i_abc_meas.c1) < MAX_longtime_CURRENT_AMP &&
                	fabs(Global_Data.av.i_abc_meas.a2) < MAX_longtime_CURRENT_AMP && fabs(Global_Data.av.i_abc_meas.b2) < MAX_longtime_CURRENT_AMP && fabs(Global_Data.av.i_abc_meas.c2) < MAX_longtime_CURRENT_AMP&&
                	    	fabs(Global_Data.av.i_a_Last) < MAX_longtime_CURRENT_AMP && fabs(Global_Data.av.i_b_Last) < MAX_longtime_CURRENT_AMP && fabs(Global_Data.av.i_c_Last) < MAX_longtime_CURRENT_AMP) {
        	reset_longtime_Current++;
        	if(reset_longtime_Current >= 10000){
        		reset_longtime_Current=0;
        		longtime_Current=0;
        	}
        }
        // check DC Bus
        if(fabs(Global_Data.av.u_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.u_dc2) > MAX_DC_VOLT) {
     	   ultrazohm_state_machine_set_stop(true);
     	  Global_Data.av.error = 2;
        }
//
        // check inverter temp
        if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG) {
     	   ultrazohm_state_machine_set_stop(true);
     	  Global_Data.av.error = 3;
        }

        // calc u neutral voltage
        switch(NEUTRAL_CONFIG){
        case 1U:{
        	u_n1 = (Global_Data.av.u_a1 + Global_Data.av.u_b1 + Global_Data.av.u_c1 + Global_Data.av.u_a2 + Global_Data.av.u_b2 + Global_Data.av.u_c2) / 6.0f;
        	u_n2 = u_n1;
        	break;
        }
        case 2U:{
        	u_n1 = (Global_Data.av.u_a1 + Global_Data.av.u_b1 + Global_Data.av.u_c1)/3.0f;
        	u_n2 = (Global_Data.av.u_a2 + Global_Data.av.u_b2 + Global_Data.av.u_c2)/3.0f;
        	break;
        }
        default: break;
        }

        // calc phase voltages with neutral voltage
        Global_Data.av.u_abc_meas.a1 = Global_Data.av.u_a1 - u_n1;
        Global_Data.av.u_abc_meas.b1 = Global_Data.av.u_b1 - u_n1;
        Global_Data.av.u_abc_meas.c1 = Global_Data.av.u_c1 - u_n1;
        Global_Data.av.u_abc_meas.a2 = Global_Data.av.u_a2 - u_n2;
        Global_Data.av.u_abc_meas.b2 = Global_Data.av.u_b2 - u_n2;
        Global_Data.av.u_abc_meas.c2 = Global_Data.av.u_c2 - u_n2;


        //VSD-Transformation
        Global_Data.av.i_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq(Global_Data.av.i_abc_meas, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
        Global_Data.av.i_dq_pruef_meas.d = Global_Data.av.i_dqxy_meas.d;
        Global_Data.av.i_dq_pruef_meas.q = Global_Data.av.i_dqxy_meas.q;
        Global_Data.av.I_d = Global_Data.av.i_dqxy_meas.d;
        Global_Data.av.I_q = Global_Data.av.i_dqxy_meas.q;
        Global_Data.av.I_x = Global_Data.av.i_dqxy_meas.x;
        Global_Data.av.I_y = Global_Data.av.i_dqxy_meas.y;

        Global_Data.av.i_alphabeta_Pruef_meas = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Global_Data.av.i_abc_meas);


 	    Global_Data.av.U_d_Pruef = Global_Data.av.u_dqxy_meas.d;
 	    Global_Data.av.U_q_Pruef = Global_Data.av.u_dqxy_meas.q;
 	    Global_Data.av.U_x_Pruef = Global_Data.av.u_dqxy_meas.x;
 	    Global_Data.av.U_y_Pruef = Global_Data.av.u_dqxy_meas.y;

 	    //Winkel umrechnen
 	    Global_Data.av.theta_elec_Last =  Global_Data.av.resolver_outputs_d4_Last.position_el_2pi * rad_to_deg;
 	    Global_Data.av.theta_elec_Pruef =  Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi * rad_to_deg;
 	    Global_Data.av.theta_mech_Last =  Global_Data.av.resolver_outputs_d4_Last.position_mech_2pi * rad_to_deg;
 	    Global_Data.av.theta_mech_Pruef =  Global_Data.av.resolver_outputs_d4_Pruef.position_mech_2pi * rad_to_deg;

 	    //dq-Transformation
 	    Global_Data.av.i_abc_last_meas.a = Global_Data.av.i_a_Last;
 	    Global_Data.av.i_abc_last_meas.b = Global_Data.av.i_b_Last;
 	    Global_Data.av.i_abc_last_meas.c = Global_Data.av.i_c_Last;
 	    Global_Data.av.i_dq_last_meas = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_last_meas, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);
 	    current_state = ultrazohm_state_machine_get_state();


    // if "STOP"
    if (current_state==idle_state)
    {
    	// disable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);

		// write zero dutycycle
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge9DutyCycle = 0.0f;


    }

   // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {

    	Global_Data.av.error = 0;

    }

    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    	if(Global_Data.av.select_fixed_values == true){
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);
        	dutycyc_last.DutyCycle_A = Global_Data.av.DutyCycle_output_Last.DutyCycle_A;
        	dutycyc_last.DutyCycle_B = Global_Data.av.DutyCycle_output_Last.DutyCycle_B;
        	dutycyc_last.DutyCycle_C = Global_Data.av.DutyCycle_output_Last.DutyCycle_C;


    	}


    	if(Global_Data.av.select_Current_Control_Last == true){
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);

    		Global_Data.av.u_dq_last_ref = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance_Last, Global_Data.av.i_dq_last_ref, Global_Data.av.i_dq_last_meas, Global_Data.av.u_dc_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s*5);
    		dutycyc_last = uz_Space_Vector_Modulation(Global_Data.av.u_dq_last_ref, Global_Data.av.u_dc_Last, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);
    	}

    	if(Global_Data.av.select_Speed_Control_Last == true){

        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);
        	if(Global_Data.av.enable_inv_pruef == true){
            	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
            	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
        	}
        	else{
            	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
            	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
        	}
        	filter_compensation();
        	float n_ref_Last_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_prefilter_Last, Global_Data.av.n_ref_Last);
        	// calculate reference torque from speed ctrl of Last motor
        	Global_Data.av.M_ref_Last = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s, n_ref_Last_filtered);
        	// calculate current setpoints i_dq_ref for Last motor
        	Global_Data.av.i_dq_last_ref = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s, Global_Data.av.M_ref_Last, Global_Data.av.u_dc_Last, Global_Data.av.i_dq_last_meas);

        	if((Global_Data.av.i_dq_last_ref.q * Global_Data.av.i_dq_last_ref.q + Global_Data.av.i_dq_last_ref.d * Global_Data.av.i_dq_last_ref.d) > (MAX_PHASE_CURRENT_AMP_Last * MAX_PHASE_CURRENT_AMP_Last)) {
    			float alpha = atan2f(Global_Data.av.i_dq_last_ref.q, Global_Data.av.i_dq_last_ref.d);
    			Global_Data.av.i_dq_last_ref.d = MAX_PHASE_CURRENT_AMP_Last * 0.95f * cosf(alpha);
				Global_Data.av.i_dq_last_ref.q = MAX_PHASE_CURRENT_AMP_Last * 0.95f * sinf(alpha);
    		}
        	Global_Data.av.u_dq_last_ref = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance_Last, Global_Data.av.i_dq_last_ref, Global_Data.av.i_dq_last_meas, Global_Data.av.u_dc_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s*5);
    		dutycyc_last = uz_Space_Vector_Modulation(Global_Data.av.u_dq_last_ref, Global_Data.av.u_dc_Last, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);


    		Global_Data.av.DutyCycle_output_Pruef = uz_spwm_dq_6ph(Global_Data.av.u_dqxy_ref, Global_Data.av.u_dc1,Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
    	}

    	if(Global_Data.av.select_Control_Pruef == true){

        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);
    		//Global_Data.av.u_dq_pruef_ref = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance_Pruef, Global_Data.av.i_dq_pruef_ref, Global_Data.av.i_dq_pruef_meas, Global_Data.av.u_dc1, Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s*5);
    		//Global_Data.av.u_dqxy_ref.d = Global_Data.av.u_dq_pruef_ref.d;
    		//Global_Data.av.u_dqxy_ref.q = Global_Data.av.u_dq_pruef_ref.q;
    		Global_Data.av.DutyCycle_output_Pruef = uz_spwm_dq_6ph(Global_Data.av.u_dqxy_ref, Global_Data.av.u_dc1,Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
    	}
    }
    else{
    	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance_Pruef);
    	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance_Last);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_Last);
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge9DutyCycle = 0.0f;
		Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_A = Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_B =Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_C =	Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_A = Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_B = Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_C =0;
		Global_Data.av.u_dqxy_ref.d = Global_Data.av.u_dqxy_ref.q = Global_Data.av.u_dqxy_ref.x = Global_Data.av.u_dqxy_ref.y = 0;
    }
    // assign DutyCycles Lastmaschine
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, dutycyc_last.DutyCycle_A, dutycyc_last.DutyCycle_B, dutycyc_last.DutyCycle_C);

    // assign Duty Cycles Pr�fling
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_A, Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_B, Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_C);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_A, Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_B, Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_C);


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

static void filter_compensation(){
	// calculate Frequency response of the magnitude
	Global_Data.av.magnitude = sqrt(1.0f + (((Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * 5.0f) / (2.0f * UZ_PIf * 1745.0f)) * ((Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * 5.0f) / (2.0f * UZ_PIf * 1745.0f))));

	Global_Data.av.u_abc_meas_filter_comp.a1 = Global_Data.av.u_abc_meas.a1 * Global_Data.av.magnitude;
	Global_Data.av.u_abc_meas_filter_comp.a2 = Global_Data.av.u_abc_meas.a2 * Global_Data.av.magnitude;
	Global_Data.av.u_abc_meas_filter_comp.b1 = Global_Data.av.u_abc_meas.b1 * Global_Data.av.magnitude;
	Global_Data.av.u_abc_meas_filter_comp.b2 = Global_Data.av.u_abc_meas.b2 * Global_Data.av.magnitude;
	Global_Data.av.u_abc_meas_filter_comp.c1 = Global_Data.av.u_abc_meas.c1 * Global_Data.av.magnitude;
	Global_Data.av.u_abc_meas_filter_comp.c2 = Global_Data.av.u_abc_meas.c2 * Global_Data.av.magnitude;
	Global_Data.av.phi_filter_comp = - atanf((Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * 5.0f) / (2.0f * UZ_PIf * 1745.0f));
	Global_Data.av.phi_filter_comp = - 1.0f * uz_signals_wrap(Global_Data.av.phi_filter_comp, 2.0f*UZ_PIf);

	float theta_new =  Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi - Global_Data.av.phi_filter_comp;
	Global_Data.av.u_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq(Global_Data.av.u_abc_meas_filter_comp, theta_new);
};
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
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) <intid>
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



