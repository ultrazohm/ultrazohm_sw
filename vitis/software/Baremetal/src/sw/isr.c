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
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;


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
#define MAX_longtime_CURRENT_AMP  7.0f
#define MAX_PHASE_CURRENT_AMP  15.0f
int longtime_Current = 0;

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
static void ReadAllADC();
static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);

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

        	if(fabs(Global_Data.av.i_abc_meas.a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.c1) > MAX_PHASE_CURRENT_AMP ||
        			fabs(Global_Data.av.i_abc_meas.a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc_meas.c2) > MAX_PHASE_CURRENT_AMP||
        	    	fabs(Global_Data.av.i_a_Last) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b_Last) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c_Last) > MAX_PHASE_CURRENT_AMP) {

        		ultrazohm_state_machine_set_stop(true);
        		Global_Data.av.error = 1;
        	}
        	longtime_Current ++;
        }
        if(longtime_Current >= 5000){
    		ultrazohm_state_machine_set_stop(true);
    		Global_Data.av.error = 1.5;
        	longtime_Current = 0;
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

        Global_Data.av.u_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq(Global_Data.av.u_abc_meas, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
 	    Global_Data.av.U_d = Global_Data.av.u_dqxy_meas.d;
 	    Global_Data.av.U_q = Global_Data.av.u_dqxy_meas.q;
 	    Global_Data.av.U_x = Global_Data.av.u_dqxy_meas.x;
 	    Global_Data.av.U_y = Global_Data.av.u_dqxy_meas.y;

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
    	// enable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);
    	Global_Data.av.error = 0;

    }

    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    	if(Global_Data.av.select_fixed_values == true){

    		Global_Data.av.svm_out.Duty_Cycle.system1.DutyCycle_A = Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_A;
    		Global_Data.av.svm_out.Duty_Cycle.system1.DutyCycle_B = Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_B;
    		Global_Data.av.svm_out.Duty_Cycle.system1.DutyCycle_C = Global_Data.av.DutyCycle_output_Pruef.system1.DutyCycle_C;
    		Global_Data.av.svm_out.Duty_Cycle.system2.DutyCycle_A = Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_A;
    	    Global_Data.av.svm_out.Duty_Cycle.system2.DutyCycle_B = Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_B;
    	    Global_Data.av.svm_out.Duty_Cycle.system2.DutyCycle_C = Global_Data.av.DutyCycle_output_Pruef.system2.DutyCycle_C;
    		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.DutyCycle_output_Last.DutyCycle_A;
    		Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.DutyCycle_output_Last.DutyCycle_B;
    		Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.DutyCycle_output_Last.DutyCycle_C;


    	}


    	if(Global_Data.av.select_Control == true){

    		Global_Data.av.u_dq_pruef_ref = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance_Pruef, Global_Data.av.i_dq_pruef_ref, Global_Data.av.i_dq_pruef_meas, Global_Data.av.u_dc1, Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s*5);
    		Global_Data.av.u_dqxy_ref.d = Global_Data.av.u_dq_pruef_ref.d;
    		Global_Data.av.u_dqxy_ref.q = Global_Data.av.u_dq_pruef_ref.q;
    		Global_Data.av.DutyCycle_output_Pruef = uz_spwm_dq_6ph(Global_Data.av.u_dqxy_ref, Global_Data.av.u_dc1,Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);

    		Global_Data.av.u_dq_last_ref = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance_Last, Global_Data.av.i_dq_last_ref, Global_Data.av.i_dq_last_meas, Global_Data.av.u_dc_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s*5);
    		dutycyc_last = uz_Space_Vector_Modulation(Global_Data.av.u_dq_last_ref, Global_Data.av.u_dc_Last, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);
    	}
    }
    else{
    	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance_Pruef);
    	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance_Last);
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
    // DutyCycles Lastmaschine setzen
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, dutycyc_last.DutyCycle_A, dutycyc_last.DutyCycle_B, dutycyc_last.DutyCycle_C);

    // assign Duty Cycles Prüfling
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.av.svm_out.Duty_Cycle.system2.DutyCycle_A, Global_Data.av.svm_out.Duty_Cycle.system2.DutyCycle_B, Global_Data.av.svm_out.Duty_Cycle.system2.DutyCycle_C);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.av.svm_out.Duty_Cycle.system1.DutyCycle_A, Global_Data.av.svm_out.Duty_Cycle.system1.DutyCycle_B, Global_Data.av.svm_out.Duty_Cycle.system1.DutyCycle_C);
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
