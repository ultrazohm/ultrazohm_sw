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



#define PHASE_CURRENT_CONV 12.5f
#define PHASE_VOLT_CONV	12.0f

#define PHASE_CURRENT_CONV_a	12.5f * 0.988f
#define PHASE_CURRENT_CONV_b	12.5f * 0.996f
#define PHASE_CURRENT_CONV_c	12.5f * 1.001f

#define PHASE_CURRENT_OFFSET_a	0.0f + 0.006f
#define PHASE_CURRENT_OFFSET_b	0.0f - 0.005f
#define PHASE_CURRENT_OFFSET_c 0.0f + 0.009f

#define PHASE_VOLT_CONV_a	12.0f
#define PHASE_VOLT_CONV_b	12.0f
#define PHASE_VOLT_CONV_c	12.0f

#define PHASE_VOLT_OFFSET_a	0.0f
#define PHASE_VOLT_OFFSET_b	0.0f
#define PHASE_VOLT_OFFSET_c	0.0f

#define MAX_MOTOR_SPEED_RPM 2000.0f
#define MAX_PHASE_CURRENT_AMP 4.2f
#define MAX2_PHASE_CURRENT_AMP 6.0f
#define MAX_DC_VOLT 50.0f
#define MAX_SECONDS_MAX_PHASE_CURRENT_AMP_1 1.0f
#define MAX_COUNT_MAX_PHASE_CURRENT_AMP_1 UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE * MAX_SECONDS_MAX_PHASE_CURRENT_AMP_1


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;
volatile float sector_debug_float = 0.0f; // @@@@


unsigned int currentlimit_counter = 0;

// ------------------------------- changes made am 13.06.25 below vvvv-------------code can be placed in its own uz file---------------@@@@@@@@@@@
int getSectorFromThetaEl(float theta_el_rad){

	int sector = 0;
	float UZ_PIf = 3.1415926535f;
	// theta_el_rad = - theta_el_rad;

	if (theta_el_rad < 0.0f){
		theta_el_rad = theta_el_rad + 2.0f*UZ_PIf;
	}

	theta_el_rad = fmodf(theta_el_rad, 2.0f*UZ_PIf);

	if (theta_el_rad >= 0 && theta_el_rad < UZ_PIf/3.0f){
		sector = 1;
	}
	else if(theta_el_rad >= UZ_PIf/3.0f && theta_el_rad < 2.0f*UZ_PIf/3.0f){
		sector = 2;
	}
	else if(theta_el_rad >= 2.0f*UZ_PIf/3.0f && theta_el_rad < UZ_PIf){
		sector = 3;
	}
	else if(theta_el_rad >= UZ_PIf && theta_el_rad < 4.0f*UZ_PIf/3.0f){
		sector = 4;
	}
	else if(theta_el_rad >= 4.0f*UZ_PIf/3.0f && theta_el_rad < 5.0f*UZ_PIf/3.0f){
		sector = 5;
	}
	else if(theta_el_rad >= 5.0f*UZ_PIf/3.0f && theta_el_rad < 2.0f*UZ_PIf){
		sector = 6;
	}
	else{
		sector = 1;
	}

	return sector;
}

// This section tells you which phase is HIGH (+), LOW (-) or FLOATING (0)
typedef struct uz_kommutierungs_wert_t{
	int a;
	int b;
	int c;
}uz_kommutierungs_wert_t;

void kommutierungSector(int sector, uz_kommutierungs_wert_t out){
	out.a = 0;
	out.b = 0;
	out.c = 0;
	if(sector == 1){
		out.a = 1;
		out.b = 0;
		out.c = -1;
	}
	else if(sector == 2){
		out.a = 0;
		out.b = 1;
		out.c = -1;
	}
	else if(sector == 3){
		out.a = -1;
		out.b = 1;
		out.c = 0;
	}
	else if(sector == 4){
		out.a = -1;
		out.b = 0;
		out.c = 1;
	}
	else if(sector == 5){
		out.a = 0;
		out.b = -1;
		out.c = 1;
	}
	else if(sector == 6){
		out.a = 1;
		out.b =-1;
		out.c = 0;
	}
}

// vvv New from 18.06.25
// code below might be useful if I decide to use a phase current as a reference current instead of the I_ZK
void activePhase(int sector, uz_kommutierungs_wert_t out){
	out.a = 0;
	out.b = 0;
	out.c = 0;
	if(sector == 1){
		out.a = 1;
		out.b = 0;
		out.c = 0;
	}
	else if(sector == 2){
		out.a = 0;
		out.b = 1;
		out.c = 0;
	}
	else if(sector == 3){
		out.a = 0;
		out.b = 1;
		out.c = 0;
	}
	else if(sector == 4){
		out.a = 0;
		out.b = 0;
		out.c = 1;
	}
	else if(sector == 5){
		out.a = 0;
		out.b = 0;
		out.c = 1;
	}
	else if(sector == 6){
		out.a = 1;
		out.b = 0;
		out.c = 0;
	}
}

// the function below simply assigns the value i_out with the value of the phase current on the HIGH-side (going into the motor).
/*
float i_ph_current_selector(int sector, float i_a, float i_b, float i_c){
	float i_out = 0.0f;

	if(sector == 1){
		i_out = i_a;
	}
	else if(sector == 2){
		i_out = i_b;
	}
	else if(sector == 3){
		i_out = i_b;
	}
	else if(sector == 4){
		i_out = i_c;
	}
	else if(sector == 5){
		i_out = i_c;
	}
	else if(sector == 6){
		i_out = i_a;
	}
	return i_out;
}
*/
// ------------------------------- changes made am 13.06.25 above ^^^^-----------------------------------@@@@@@@@@@@




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

    Global_Data.av.omega_mech = 1*((Global_Data.av.mechanicalRotorSpeed_filtered / 60.0f) * (2.0f * (float)M_PI));
    Global_Data.av.omega_elec = Global_Data.av.omega_mech * 3;
    Global_Data.av.theta_elec = fmodf(((Global_Data.av.theta_mech*3) + Global_Data.av.theta_offset),(2* M_PI));

    Global_Data.av.u_a = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_a +PHASE_VOLT_OFFSET_a;
    Global_Data.av.u_b = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_b +PHASE_VOLT_OFFSET_b;
    Global_Data.av.u_c = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_c +PHASE_VOLT_OFFSET_c;
    Global_Data.av.U_ZK = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
    Global_Data.av.i_a = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_a +PHASE_CURRENT_OFFSET_a;
    Global_Data.av.i_b = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_b +PHASE_CURRENT_OFFSET_b;
    Global_Data.av.i_c = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_c +PHASE_CURRENT_OFFSET_c;
    Global_Data.av.I_ZK = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

    // @@@@@@@@@@@@@@@@@@@ calling the function (can be simplified even further)
    float theta_el = Global_Data.av.theta_elec;           // read the electrical angle
    Global_Data.av.sector = getSectorFromThetaEl(theta_el);          // use existing function
    sector_debug_float = (float)Global_Data.av.sector;                   // convert sector to float
    // @@@@@@@@@@@@@@@@@@@

    /*
    Global_Data.av.u_ab =    Global_Data.av.u_a -   Global_Data.av.u_b;
    Global_Data.av.u_bc =    Global_Data.av.u_b -   Global_Data.av.u_c;
    Global_Data.av.u_ca =    Global_Data.av.u_c -   Global_Data.av.u_a;
    Global_Data.av.u_n =    (Global_Data.av.u_a + Global_Data.av.u_b + Global_Data.av.u_c)/3;
    Global_Data.av.u_ph1 =   Global_Data.av.u_a - Global_Data.av.u_n;
    Global_Data.av.u_ph2 =   Global_Data.av.u_b - Global_Data.av.u_n;
    Global_Data.av.u_ph3 =   Global_Data.av.u_c - Global_Data.av.u_n;
   */



    if (current_state == running_state || current_state == control_state) {
      // enable inverter adapter hardware
      uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_D1, true);
    } else {
      // disable inverter adapter hardware
      uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_D1, false);
    }

    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_D1);
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
       ultrazohm_state_machine_set_error(true);
    }

    // Software current limit
    if(fabs(Global_Data.av.i_a) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c) > MAX_PHASE_CURRENT_AMP ){

    	currentlimit_counter = currentlimit_counter + 1;

    	if( (float)currentlimit_counter > MAX_COUNT_MAX_PHASE_CURRENT_AMP_1){
    		// Disable Inverter
			   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_D1, false);
			   ultrazohm_state_machine_set_stop(true);
			   Global_Data.av.errorcode = 1.0f;
    	}
    }else{
    	currentlimit_counter = 0;
    }

    // current and voltage in structs
	Global_Data.av.i_abc_m.a = Global_Data.av.i_a;
	Global_Data.av.i_abc_m.b = Global_Data.av.i_b;
	Global_Data.av.i_abc_m.c = Global_Data.av.i_c;

	Global_Data.av.u_abc_m.a = Global_Data.av.u_a;
	Global_Data.av.u_abc_m.b = Global_Data.av.u_b;
	Global_Data.av.u_abc_m.c = Global_Data.av.u_c;

	// abc-dq Transformation
    Global_Data.av.i_dq_m = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_m, Global_Data.av.theta_elec);
    Global_Data.av.u_dq_m = uz_transformation_3ph_abc_to_dq(Global_Data.av.u_abc_m, Global_Data.av.theta_elec);

    // --------------- BLDC ----------------- @@@@@
    // DC-link current measured for the current PI controller
    Global_Data.av.I_ph_m = Global_Data.av.I_ZK; // see line 252

    // Here I define the actual speed in RPM
    Global_Data.av.n_act_rpm = Global_Data.av.mechanicalRotorSpeed_filtered;
    // -------------------------------------- @@@@@


    if (current_state==control_state)
    {
    	Global_Data.av.u_dq_ref = uz_CurrentControl_sample(Global_Data.objects.current_control, Global_Data.av.i_dq_ref, Global_Data.av.i_dq_m, Global_Data.av.U_ZK, Global_Data.av.omega_elec);

    	Global_Data.av.output_Dutycycle = uz_spwm_dq(Global_Data.av.u_dq_ref, Global_Data.av.U_ZK, Global_Data.av.theta_elec);

    	// @@@@@

    	if(Global_Data.av.SpeedControl){
    		//***Speed Control (Speed -> Control Voltage)
    		Global_Data.av.n_RPM_error = Global_Data.av.n_ref_rpm - Global_Data.av.n_act_rpm;
    		Global_Data.av.u_BLDC_ref = uz_PI_Controller_sample(Global_Data.objects.PI_speed_only, Global_Data.av.n_ref_rpm, Global_Data.av.n_act_rpm, false);

    	}

    	else if(Global_Data.av.CurrentControl){
    		// ***Current Control (Current -> Control Voltage)
    		Global_Data.av.I_ph_error = Global_Data.av.I_ph_ref - Global_Data.av.I_ph_m;
    		Global_Data.av.u_BLDC_ref = uz_PI_Controller_sample(Global_Data.objects.PI_current, Global_Data.av.I_ph_ref, Global_Data.av.I_ph_m, false);
    	}

    	else if(Global_Data.av.CascadeControl){
    		//Cascade Speed-Current-Controllers (Speed -> Current -> Control Voltage)
    		Global_Data.av.i_ref_kaskade = uz_PI_Controller_sample(Global_Data.objects.PI_speed, Global_Data.av.n_ref_rpm, Global_Data.av.n_act_rpm, false);
    		Global_Data.av.u_BLDC_ref    = uz_PI_Controller_sample(Global_Data.objects.PI_current, Global_Data.av.i_ref_kaskade, Global_Data.av.I_ph_m, false);
    	}

    	else if(Global_Data.av.DutyCycleControl){
    		Global_Data.av.u_BLDC_ref = Global_Data.av.U_ctrl_ref;
    	}

    	// Now we normalize the control voltage from the current PI controller by dividing it by U_ZK
    	Global_Data.av.d_BLDC = fabs(Global_Data.av.u_BLDC_ref)/ Global_Data.av.U_ZK;

    	//Global_Data.av.d_BLDC = 0.0f;

    	// Duty Cycle value saturation (between 0 and 1)
    	if (Global_Data.av.d_BLDC > 1.0f)
    	    Global_Data.av.d_BLDC = 1.0f;
    	else if(Global_Data.av.d_BLDC < 0.0f){
    	    Global_Data.av.d_BLDC = 0.0f;
    	}


    	// Unipolar Switching Upper Switch PWM
    	float d_a = 0.0f;
    	float d_b = 0.0f;
    	float d_c = 0.0f;

    	// Unipolar means either the HIGH side is PWM controlled and the LOW side is either ON/OFF, or vice versa
    	if(Global_Data.av.sector == 1){
    		d_a = Global_Data.av.d_BLDC;
    		// d_b = OFF
    		d_c = 0; // this means the HIGH side is OFF and therefore the LOW side of C is ON
    		if (Global_Data.av.u_BLDC_ref < 0.0f){
    			d_a = 0;
    			// d_b = OFF
    			d_c = Global_Data.av.d_BLDC;
    		}
    		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, true, false);
    	}

    	else if(Global_Data.av.sector == 2){
       		//d_a -> OFF
       		d_b = Global_Data.av.d_BLDC;
       		d_c = 0;
       		if (Global_Data.av.u_BLDC_ref < 0.0f){
           		//d_a -> OFF
           		d_b = 0;
           		d_c = Global_Data.av.d_BLDC;
       		}
       		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, false, false);
       	}

    	else if(Global_Data.av.sector == 3){
       		d_a = 0;
       		d_b = Global_Data.av.d_BLDC;
       		//d_c -> Aus;
       		if (Global_Data.av.u_BLDC_ref < 0.0f){
           		d_a = Global_Data.av.d_BLDC;
           		d_b = 0;
           		//d_c -> Aus;
       		}
       		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, true);
       	}

    	else if(Global_Data.av.sector == 4){
       		d_a = 0;
       		//d_b -> Aus
       		d_c = Global_Data.av.d_BLDC;
       		if (Global_Data.av.u_BLDC_ref < 0.0f){
           		d_a = Global_Data.av.d_BLDC;
           		//d_b -> Aus
           		d_c = 0;
       		}

       		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, true, false);
       	}


    	else if(Global_Data.av.sector == 5){
       		//d_a -> Aus
       		d_b = 0;
       		d_c = Global_Data.av.d_BLDC;
       		if (Global_Data.av.u_BLDC_ref < 0.0f){
           		//d_a -> Aus
           		d_b = Global_Data.av.d_BLDC;
           		d_c = 0;
       		}

       		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, false, false);
       	}


    	else if(Global_Data.av.sector == 6){
       		d_a = Global_Data.av.d_BLDC;
       		d_b = 0;
       		//d_c -> Aus
       		if (Global_Data.av.u_BLDC_ref < 0.0f){
           		d_a = 0;
           		d_b = Global_Data.av.d_BLDC;
           		//d_c -> Aus
       		}

       		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, true);
       	}

    	Global_Data.rasv.halfBridge1DutyCycle = d_a;
    	Global_Data.rasv.halfBridge2DutyCycle = d_b;
    	Global_Data.rasv.halfBridge3DutyCycle = d_c;
    	// @@@@@

	   //Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.output_Dutycycle.DutyCycle_A;
	   //Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.output_Dutycycle.DutyCycle_B;
	   //Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.output_Dutycycle.DutyCycle_C;



    }else{

    	uz_CurrentControl_reset(Global_Data.objects.current_control);
    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;

    	if(Global_Data.av.directDuty){
        	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.d_a_ref;
        	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.d_b_ref;
        	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.d_c_ref;
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
