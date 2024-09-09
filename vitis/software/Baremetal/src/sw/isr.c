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
struct uz_pmsm_model6ph_dq_outputs_general_t CIL_out_general = {0};
uz_6ph_dq_t v_dqxy_limited_volts = {0};
uz_3ph_dq_t v_dq_limited_volts = {0};
uz_3ph_dq_t v_xy_limited_volts = {0};
uz_6ph_dq_t v_dqxy_limited_volts_k_old = {0};
uz_6ph_dq_t v_dqxy_non_limited_volts = {0};
uz_6ph_abc_t REAL_i_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_ref = {0};
uz_6ph_dq_t REAL_i_dqxy_meas = {0};
uz_6ph_dq_t REAL_v_dqxy_meas = {0};
uz_6ph_dq_t i_dqxy_integrated_error = {0};
uz_6ph_dq_t i_dqxy_error = {0};
uz_3ph_dq_t REAL_v_dq_reference = {0};
uz_3ph_dq_t i_dq_reference = {0};
uz_3ph_alphabeta_t v_XY_limited_volts = {0};

int ISR_Counter = 0;

float I_ref = 0.0;

extern float System_UpTime_ms;

struct uz_DutyCycle_2x3ph_t DutyCycle_output = {0};

float CIL_omega_mech = 100.0f; //fixed speed for the CIL model
float max_modulation_index = (1.0f / 2.0f) * 0.707106781f;

int reset = 0U;

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

// software limits -> Stop Zustand
#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f

#define MAX_PHASE_CURRENT_AMP  40.0f
#define MAX_SECONDS_MAX_PHASE_CURRENT_AMP_1 1.0f
#define MAX_COUNT_MAX_PHASE_CURRENT_AMP_1 UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE * MAX_SECONDS_MAX_PHASE_CURRENT_AMP_1

// software limits assert
#define MAX_PHASE_CURRENT_AMP_1  45.0f
#define MAX_PHASE_CURRENT_AMP_2  50.0f

#define MAX_DC_VOLT_2 52.0f
#define MAX_TEMP_DEG_2 95.0f

//neutral config
#define NEUTRAL_CONFIG 2U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_a1c1 = 0.0f;
float u_a2c2 = 0.0f;

unsigned int currentlimit_counter = 0;

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

int getSectorFromThetaEl(float theta_el_rad, bool theta_ref_d_axis){

	int sector = 0;

	theta_el_rad = - theta_el_rad;

	if (theta_el_rad < 0.0f){
		theta_el_rad = theta_el_rad + 2.0f*UZ_PIf;
	}

	if(theta_ref_d_axis){
		//theta_el_rad = theta_el_rad + 2.0f*UZ_PIf - UZ_PIf/2.0f;

		theta_el_rad = theta_el_rad + UZ_PIf/2.0f;  // d-Achse als Referenz statt q-Achse für den Rotorwinkel -> muss kompensiert werden für die Sektorberechnung
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



//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();



void ISR_Control(void *data)
{
	ISR_Counter = ISR_Counter + 1;

    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr

    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // get reference values from Global_Data, written over the JavaScope



    //Take measurements independent of control_state, but only if Real is selected

    	//Read out speed & position

        Global_Data.av.theta_elec = Global_Data.av.theta_elec - Global_Data.av.theta_offset;

        Global_Data.av.theta_elec = Global_Data.av.theta_elec - Global_Data.av.theta_offset2;

        Global_Data.av.theta_elec = Global_Data.av.theta_elec + 2.0f*M_PI;
        Global_Data.av.theta_elec = fmod(Global_Data.av.theta_elec, 2.0f*M_PI);

        Global_Data.av.theta_elec2 = Global_Data.av.theta_elec;
        Global_Data.av.omega_mech = (Global_Data.av.mechanicalRotorSpeed / 60.0f) * (2.0f * UZ_PIf);
        Global_Data.av.omega_elec = Global_Data.av.omega_mech * Global_Data.av.pmsm_6ph.polePairs;

        Global_Data.av.n_act_rpm = Global_Data.av.mechanicalRotorSpeed;

        // Read out and convert ADC readings to currents in Amps
        Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1 +PHASE_CURRENT_OFFSET_A1;
        Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1 +PHASE_CURRENT_OFFSET_B1;
        Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1 +PHASE_CURRENT_OFFSET_C1;
        Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
        //Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
        //Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
        //Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
        //Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

        // Read out and convert ADC readings to voltages
        Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_A1 +PHASE_VOLT_OFFSET_A1;
        Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_B1 +PHASE_VOLT_OFFSET_B1;
        Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_C1 +PHASE_VOLT_OFFSET_C1;
        //Global_Data.av.v_dc2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
        //Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
        //Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
        //Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;

        //Read out inverter temperature
        Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
        //Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
        Global_Data.av.temp_VSI_1 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L1,
        Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L2,
		Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L3);
        //Global_Data.av.temp_VSI_2 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1,
        //Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2,
        //Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3);

        // check current limit
        if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
        	fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {

        	currentlimit_counter = currentlimit_counter + 1;

        	if( (float)currentlimit_counter > MAX_COUNT_MAX_PHASE_CURRENT_AMP_1){
        		// Disable Inverter
				   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
				   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
				   ultrazohm_state_machine_set_stop(true);
				   Global_Data.av.errorcode = 1.0f;
        	}
        }else{
        	currentlimit_counter = 0;
        }

        // Höhere Strombegrenzung 1
        if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP_1 || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP_1 || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP_1 ||
        	fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP_1 || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP_1 || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP_1) {
        	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
		   	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
        	ultrazohm_state_machine_set_stop(true);
        	Global_Data.av.errorcode = 11.0f;
        }

        // Höhere Strombegrenzung 2
        if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP_2 || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP_2 || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP_2 ||
        	fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP_2 || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP_2 || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP_2) {
     	   Global_Data.av.errorcode = 111.0f;
		   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
		   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
     	   uz_assert(0);
        }

           // check DC Bus
           if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {

        	   // Disable Inverter
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
        	   ultrazohm_state_machine_set_stop(true);
        	   Global_Data.av.errorcode = 2.0f;

        	   if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT_2 || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT_2) {
        		   Global_Data.av.errorcode = 21.0f;
        		   uz_assert(0);
        	   }

           }
/*
           // check inverter temperature
           if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG ) {

        	   // Disable Inverter
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
        	   ultrazohm_state_machine_set_stop(true);
        	   Global_Data.av.errorcode = 3.0f;

          	  Global_Data.rasv.d_a1_ref = 0.0f;
          	  Global_Data.rasv.d_b1_ref = 0.0f;
          	  Global_Data.rasv.d_c1_ref = 0.0f;

        	   if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG_2 || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG_2   ) {
        		   Global_Data.av.errorcode = 31.0f;
        		   //uz_assert(0);
        	   }

           }
*/
           //write to structs
           //REAL_i_abc_meas.a1 = Global_Data.av.i_a1;
           //REAL_i_abc_meas.b1 = Global_Data.av.i_b1;
           //REAL_i_abc_meas.c1 = Global_Data.av.i_c1;
           //REAL_i_abc_meas.a2 = Global_Data.av.i_a2;
           //REAL_i_abc_meas.b2 = Global_Data.av.i_b2;
           //REAL_i_abc_meas.c2 = Global_Data.av.i_c2;

           /*
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
           REAL_i_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(REAL_i_abc_meas, Global_Data.av.theta_elec, - Global_Data.av.theta_elec);
           Global_Data.av.I_d = REAL_i_dqxy_meas.d;
           Global_Data.av.I_q = REAL_i_dqxy_meas.q;
           Global_Data.av.I_X = REAL_i_dqxy_meas.x;
           Global_Data.av.I_Y = REAL_i_dqxy_meas.y;

           REAL_v_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(REAL_v_abc_meas, Global_Data.av.theta_elec, - Global_Data.av.theta_elec);
		   Global_Data.av.U_d = v_dqxy_limited_volts.d;
		   Global_Data.av.U_q = v_dqxy_limited_volts.q;
		   Global_Data.av.U_X = v_dqxy_limited_volts.x;
		   Global_Data.av.U_Y = v_dqxy_limited_volts.y;

           */

		   //Only allow enable of inverter, if "select_Real" is true
           if (current_state == running_state || current_state == control_state) {
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
           } else {
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
           }


    // BLDC:
    Global_Data.av.sector = getSectorFromThetaEl( Global_Data.av.theta_elec, true );

	   // Vorläufig Inverter Disable:
	   // uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
	   // uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);

   //-----------------------------------------------------------------------------------------------------------------------------//

	   // get current:
	   Global_Data.av.I_ph_m = i_ph_current_selector(Global_Data.av.sector, Global_Data.av.i_a1, Global_Data.av.i_b1, Global_Data.av.i_c1);



	   if(Global_Data.rasv.inc_dec != 0.0f && ( ISR_Counter % 1000) == 0 ){
		   Global_Data.rasv.i_q_ref = Global_Data.rasv.i_q_ref + Global_Data.rasv.inc_dec * Global_Data.rasv.i_step;
		   Global_Data.rasv.inc_dec = 0.0f;
	   }

	   // reference current:
	   Global_Data.av.I_ph_ref = Global_Data.rasv.i_q_ref;

       if (current_state==control_state)
       {



    	   // Hier PI-Regler für Stromregelung:
           Global_Data.av.u_BLDC_ref = uz_PI_Controller_sample(Global_Data.objects.I_control_BLDC, Global_Data.av.I_ph_ref, Global_Data.av.I_ph_m, false);

           // Hier alternativ PI-Regler für Drehzahlregelung mit u_BLDC Sollwert
           // Global_Data.av.u_BLDC_ref = uz_PI_Controller_sample(Global_Data.objects.Speed_control_BLDC, Global_Data.rasv.n_ref_rpm, Global_Data.av.n_act_rpm, false);

           // Kaskade Drehzahl-Strom-Regler
           //Global_Data.av.i_ref_kaskade = uz_PI_Controller_sample(Global_Data.objects.Speed_control_BLDC, Global_Data.rasv.n_ref_rpm, Global_Data.av.n_act_rpm, false);
           //Global_Data.av.u_BLDC_ref    = uz_PI_Controller_sample(Global_Data.objects.I_control_BLDC, Global_Data.av.i_ref_kaskade, Global_Data.av.I_ph_m, false);

           // skalieren für DutyCycle:
           Global_Data.av.d_BLDC = fabs(Global_Data.av.u_BLDC_ref) * 2.0f/ Global_Data.av.U_ZK;

           //Global_Data.av.d_BLDC = 0.0f;

           // Begrenzen des Dutycycles (Eigentlich schon durch die Sättigung des PI-Reglers abgedeckt)
           if (Global_Data.av.d_BLDC > 1.0f)
        	   Global_Data.av.d_BLDC = 1.0f;
           else if(Global_Data.av.d_BLDC < 0.0f){
        	   Global_Data.av.d_BLDC = 0.0f;
           }

    	   // Unipolar Switching Upper Switch PWM
           float d_a = 0.0f;
           float d_b = 0.0f;
           float d_c = 0.0f;

           // je nach Sektor werden zwei Phasen bestromt
           // Unipolar-Switching (Bipolar wäre cooler, ist aber mit dem UZ-PWM-Standardmodul schwieriger)
           // Eine Halbbrücke wird PWM-Betrieben, die andere auf Low gesetzt, die dritte in den Tri-State gesetzt
           // bei negativer Soll-Spannung muss die Ansteuerung getauscht werden

           	if(Global_Data.av.sector == 1){
           		d_a = Global_Data.av.d_BLDC;
           		//d_b -> Aus
           		d_c = 0;
           		if (Global_Data.av.u_BLDC_ref < 0.0f){
               		d_a = 0;
               		//d_b -> Aus
               		d_c = Global_Data.av.d_BLDC;
           		}

           		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, true, false);
           	}
           	else if(Global_Data.av.sector == 2){
           		//d_a -> Aus
           		d_b = Global_Data.av.d_BLDC;
           		d_c = 0;
           		if (Global_Data.av.u_BLDC_ref < 0.0f){
               		//d_a -> Aus
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

           	// Dutycycles für den 2. Umrichter am Broseprüfstand auf 0
           	Global_Data.rasv.halfBridge4DutyCycle = 0;
           	Global_Data.rasv.halfBridge5DutyCycle = 0;
           	Global_Data.rasv.halfBridge6DutyCycle = 0;

           	// 2. Umrichter am Broseprüfstand in tristate schalten
           	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);


           // END REAL // --------------------------

       }

       else if (current_state == running_state && Global_Data.rasv.offsetBestimmung == true){
    	   uz_PI_Controller_reset(Global_Data.objects.I_control_BLDC);
    	   uz_PI_Controller_reset(Global_Data.objects.Speed_control_BLDC);

			Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.d_a1_ref;
			Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.d_b1_ref;
			Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.d_c1_ref;

			Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge6DutyCycle = 0.0f;

			uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
       }


       else {
    	   uz_PI_Controller_reset(Global_Data.objects.I_control_BLDC);
    	   uz_PI_Controller_reset(Global_Data.objects.Speed_control_BLDC);

			Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge3DutyCycle = 0.0f;

			Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
       }




       if(Global_Data.rasv.offsetBestimmung == true){
    	   Global_Data.rasv.offsetBestimmungOn = 1.0f;
       }
       else{
    	   Global_Data.rasv.offsetBestimmungOn = 0.0f;
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
