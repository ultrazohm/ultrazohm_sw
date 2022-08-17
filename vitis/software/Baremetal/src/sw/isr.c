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
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_Transformation/uz_Transformation.h"

#include "../Codegen/uz_singleindex_faultdetection.h"

#include "../uz/uz_VSD_6ph_FD/uz_VSD6phFD.h"
#include "../uz/uz_FOC/uz_FOC.h"
#include "../uz/uz_filter/uz_filter.h"

#include "../uz/uz_6ph_opf_control/parameter_MLMT_ADT.h"

#include "../IP_Cores/uz_vsd_and_park_transformation_6phase/uz_vsd_and_park_transformation_6phase.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;


uz_6ph_abc_t i_6phase = {0};
uz_6ph_abc_t i_6phase_filtered = {0};
uz_6ph_alphabeta_t i_abxyz1z2 = {0};
uz_6ph_alphabeta_t i_abxyz1z2_filtered = {0};

float vsd_output[6] = {0};
float vsd_output_hyst[6] = {0};
float vsd_output_filtered[6] = {0};

float vsd_output_V4[6] = {0};
float vsd_output_hyst_V4[6] = {0};
float vsd_output_filtered_V4[6] = {0};

float Rb1[5] = {0};
float Rb1_filtered[5] = {0};

float singleIndex_FD_R = 0.0f;

uz_6phFD_indices R_FD = {0};
uz_6phFD_indices R_FD_Filt = {0};
uz_6phFD_indices R_FD_eval = {0};


extern uz_vsd_opf_fd_v7 uz_FD_v7;

extern uz_singleindex_faultdetection singleindex_FD;


extern uz_resonant_controller r_c_2H_x;
extern uz_resonant_controller r_c_2H_y;
extern uz_resonant_controller r_c_6H_x;
extern uz_resonant_controller r_c_6H_y;
extern uz_resonant_controller r_c_2H_d;
extern uz_resonant_controller r_c_2H_q;

extern uz_resonant_controller r_c_2H_z1;
extern uz_resonant_controller r_c_2H_z2;
extern uz_resonant_controller r_c_3H_z1;
extern uz_resonant_controller r_c_3H_z2;

extern uz_filter_t* r_c_iir_2H_x;
extern uz_filter_t* r_c_iir_2H_y;

float r_c_VR;
float r_c_Tsw;
float r_c_omega_r;


extern uz_movAverageFilter_t* movAvFilter;

extern uz_movAverageFilter_t* movAvFilter_R1;
extern uz_movAverageFilter_t* movAvFilter_R2;
extern uz_movAverageFilter_t* movAvFilter_R3;
extern uz_movAverageFilter_t* movAvFilter_R4;
extern uz_movAverageFilter_t* movAvFilter_R5;
extern uz_movAverageFilter_t* movAvFilter_R6;

int toggle = 0;

float filteredFDIndices[6] = {0};

extern uz_filter_t* filter_a1;
extern uz_filter_t* filter_b1;
extern uz_filter_t* filter_c1;
extern uz_filter_t* filter_a2;
extern uz_filter_t* filter_b2;
extern uz_filter_t* filter_c2;

float testvalue = 0.0f;


//parameters for 6ph FOC:

extern uz_FOC* FOC_dq;
extern struct uz_FOC_config config_FOC;
extern struct uz_PMSM_t config_PMSM;


float error_z1z2_s[2];
float error_z1z2_n[2];


uz_6ph_abc_t m_6ph_abc_currents = {0};
uz_6ph_alphabeta_t m_6ph_alphabeta_currents = {0};

uz_3ph_alphabeta_t m_alphabeta_currents = {0};
uz_3ph_dq_t m_dq_currents = {0};
uz_3ph_dq_t m_dq_n_currents = {0};
uz_3ph_dq_t temp_3ph_dq_t_var = {0};
uz_3ph_alphabeta_t temp_3ph_alpabeta_var = {0};

uz_3ph_alphabeta_t ref_alphabeta_voltage = {0};
uz_3ph_dq_t ref_dq_voltage = {0};
uz_3ph_dq_t ref_dq_n_voltage = {0};


extern uz_PI_Controller* PI_d_n;
extern uz_PI_Controller* PI_q_n;
extern uz_PI_Controller* PI_x_s;
extern uz_PI_Controller* PI_x_n;
extern uz_PI_Controller* PI_y_s;
extern uz_PI_Controller* PI_y_n;

extern uz_PI_Controller* PI_z1_s;
extern uz_PI_Controller* PI_z1_n;
extern uz_PI_Controller* PI_z2_s;
extern uz_PI_Controller* PI_z2_n;


float m_xy_currents[2];
float ref_xy_currents[2];

float m_xy_s_currents[2];
float ref_xy_s_currents[2];

float m_xy_n_currents[2];
float ref_xy_n_currents[2];

float xy_error[2];

float m_z1z2_currents[2];
float ref_z1z2_currents[2];

float m_z1z2_s_currents[2];
float ref_z1z2_s_currents[2];

float m_z1z2_n_currents[2];
float ref_z1z2_n_currents[2];

float ref_xy_voltage[2];
float ref_xy_voltage_n[2];
float ref_xy_voltage_s[2];

float ref_xy_s_voltage[2];
float ref_xy_n_voltage[2];

float ref_z1z2_voltage[2];
float ref_z1z2_voltage_n[2];
float ref_z1z2_voltage_s[2];

float z1z2_error[2];

float ref_z1z2_s_voltage[2];
float ref_z1z2_n_voltage[2];

float m_ab_currents[2];
float ref_ab_currents[2];
float ref_ab_n_currents[2];
float m_ab_n_currents[2];
float ref_ab_n_voltage[2];
float ref_ab_voltage_n[2];
float ref_dq_currents[2];

float m_ab_n_currents_testvariable[2];
float m_ab_n_currents_testvariable2[2];
float m_ab_n_currents_testvariable3[2];


uz_6ph_abc_t ref_6ph_abc_voltage = {0};
uz_6ph_alphabeta_t ref_6ph_alphabeta_voltage = {0};

uz_3ph_abc_t ref_volage_phase_set1 = {0};
uz_3ph_abc_t ref_volage_phase_set2 = {0};

uz_3ph_dq_t ref_dq0_currents = {0};
uz_3ph_dq_t ref_dq0_n_currents = {0};
uz_3ph_alphabeta_t ref_alphabeta_currents = {0};

struct uz_DutyCycle_t dutyCycles_set1 = {0};
struct uz_DutyCycle_t dutyCycles_set2 = {0};

float adc_offset = 0.0f;
float adc_factor = 1.0f;

float theta_el_offset = 0.0f;

float omega_el_rad_per_sec = 0.0f;
int mov_average_filter_length = 0;


extern struct uz_d_gan_inverter_t* gan_inverter_D3;
extern struct uz_d_gan_inverter_t* gan_inverter_D4;

bool dq_n = false;
bool xy_n = true;
bool xy_s = false;
bool z1z2_n = false;
bool z1z2_s = false;
bool xy_n_2 = true;
bool xy_n_6 = true;
bool dq_2 = true;
bool z1z2_2 = false;
bool z1z2_3 = false;

float zw_1;
float zw_2;

int opf_phases[6] = {0};
int num_OPF = 0;


extern uz_vsd_and_park_transformation_6phase_t* vsd_park;

uz_3ph_dq_t value_1;
uz_6ph_alphabeta_t value_2;

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
	omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed*config_FOC.config_PMSM.polePairs*2.0f*M_PI/60;

    i_6phase.a1 =  m_6ph_abc_currents.a1;
    i_6phase.b1 =  m_6ph_abc_currents.b1;
    i_6phase.c1 =  m_6ph_abc_currents.c1;
    i_6phase.a2 =  m_6ph_abc_currents.a2;
    i_6phase.b2 =  m_6ph_abc_currents.b2;
    i_6phase.c2 =  m_6ph_abc_currents.c2;

    i_6phase_filtered.a1 = Global_Data.av.I_U_Filtered;
    i_6phase_filtered.b1 = Global_Data.av.I_V_Filtered;
    i_6phase_filtered.c1 = Global_Data.av.I_W_Filtered;
    i_6phase_filtered.a2 = Global_Data.av.I_X_Filtered;
    i_6phase_filtered.b2 = Global_Data.av.I_Y_Filtered;
    i_6phase_filtered.c2 = Global_Data.av.I_Z_Filtered;

    //Transform from abc to alpha-beta-x-y-z1-z2-System
    i_abxyz1z2 = uz_transformation_asym30deg_6ph_abc_to_alphabeta(i_6phase);


    i_abxyz1z2_filtered = uz_transformation_asym30deg_6ph_abc_to_alphabeta(i_6phase_filtered);

/*
    //z1z2 0 setzen:
    i_abxyz1z2.z1 = 0.0f;
    i_abxyz1z2.z2 = 0.0f;
    i_abxyz1z2_filtered.z1 = 0.0f;
    i_abxyz1z2_filtered.z2 = 0.0f;
*/

    //c-code-fault-detection
    R_FD = uz_vsd_opf_6ph_faultdetection(i_abxyz1z2);
    R_FD_Filt = uz_vsd_fd_hysteresis_filter(R_FD, 0.8, 1.2);


//Version 7:
/*
    uz_FD_v7.input.HB_o = 0.2;
    uz_FD_v7.input.HB_u = 0.2;
    uz_FD_v7.input.i_ab_xy_z1z2[0] = i_abxyz1z2.alpha;
    uz_FD_v7.input.i_ab_xy_z1z2[1] = i_abxyz1z2.beta;
    uz_FD_v7.input.i_ab_xy_z1z2[2] = i_abxyz1z2.x;
    uz_FD_v7.input.i_ab_xy_z1z2[3] = i_abxyz1z2.y;
    uz_FD_v7.input.i_ab_xy_z1z2[4] = i_abxyz1z2.z1;
    uz_FD_v7.input.i_ab_xy_z1z2[5] = i_abxyz1z2.z2;

    uz_vsd_opf_fd_v7_step(&uz_FD_v7);

    for(int i = 0; i<6; i++){
        vsd_output[i] = (float)uz_FD_v7.output.FD_raw[i];
        vsd_output_hyst[i] = (float)uz_FD_v7.output.FD_hyst[i];
        vsd_output_filtered[i] = (float)uz_FD_v7.output.FD_filtered[i];

    }
    for(int i=0; i<5; i++){
    	Rb1[i] = (float)uz_FD_v7.output.R_b1[i];
		Rb1_filtered[i] = (float)uz_FD_v7.output.R_b1_filtered[i];
    }
*/

//Single Index:
/*
    singleindex_FD.input.i_ab_xy_z1z2[0] = i_abxyz1z2.alpha;
    singleindex_FD.input.i_ab_xy_z1z2[1] = i_abxyz1z2.beta;
    singleindex_FD.input.i_ab_xy_z1z2[2] = i_abxyz1z2.x;
    singleindex_FD.input.i_ab_xy_z1z2[3] = i_abxyz1z2.y;
    singleindex_FD.input.HB_Wert = 2.0;

    uz_singleindex_faultdetection_step(&singleindex_FD);

    singleIndex_FD_R = singleindex_FD.output.FD_filtered;
*/
    //movAverageFilter:

    //filteredFDIndices[0] = uz_movAverageFilter_sample(movAvFilter, vsd_output_hyst_V4[0]);


    //calculate optimal filterlength
    float k = 1.0;	//part of one electric period

    if (omega_el_rad_per_sec != 0){
    	mov_average_filter_length = k * 10000 * 2 * M_PI / abs(omega_el_rad_per_sec);
    }else{
    	mov_average_filter_length = 0;
    }


    //Splitted the movAverageFiltering into two sets, each executed every other cycle (10kHz reduced to 5kHz)
    mov_average_filter_length = mov_average_filter_length/2;
/*
    if(toggle == 0){
		uz_movAverageFilter_set_filterLength(movAvFilter_R1, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R2, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R3, mov_average_filter_length);

	    filteredFDIndices[0] = uz_movAverageFilter_sample(movAvFilter_R1, vsd_output_hyst[0]);
	    filteredFDIndices[1] = uz_movAverageFilter_sample(movAvFilter_R2, vsd_output_hyst[1]);
	    filteredFDIndices[2] = uz_movAverageFilter_sample(movAvFilter_R3, vsd_output_hyst[2]);
	    toggle = 1;
    }
    else{
		uz_movAverageFilter_set_filterLength(movAvFilter_R4, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R5, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R6, mov_average_filter_length);

	    filteredFDIndices[3] = uz_movAverageFilter_sample(movAvFilter_R4, vsd_output_hyst[3]);
	    filteredFDIndices[4] = uz_movAverageFilter_sample(movAvFilter_R5, vsd_output_hyst[4]);
	    filteredFDIndices[5] = uz_movAverageFilter_sample(movAvFilter_R6, vsd_output_hyst[5]);
	    toggle = 0;
    }
*/
    if(toggle == 0){
		uz_movAverageFilter_set_filterLength(movAvFilter_R1, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R2, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R3, mov_average_filter_length);

	    filteredFDIndices[0] = uz_movAverageFilter_sample(movAvFilter_R1, R_FD_Filt.R1);
	    filteredFDIndices[1] = uz_movAverageFilter_sample(movAvFilter_R2, R_FD_Filt.R2);
	    filteredFDIndices[2] = uz_movAverageFilter_sample(movAvFilter_R3, R_FD_Filt.R3);
	    toggle = 1;
    }
    else{
		uz_movAverageFilter_set_filterLength(movAvFilter_R4, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R5, mov_average_filter_length);
		uz_movAverageFilter_set_filterLength(movAvFilter_R6, mov_average_filter_length);

	    filteredFDIndices[3] = uz_movAverageFilter_sample(movAvFilter_R4, R_FD_Filt.R4);
	    filteredFDIndices[4] = uz_movAverageFilter_sample(movAvFilter_R5, R_FD_Filt.R5);
	    filteredFDIndices[5] = uz_movAverageFilter_sample(movAvFilter_R6, R_FD_Filt.R6);
	    toggle = 0;
    }

    //for FOC:
/*
	//Read the phase-currents
	m_6ph_abc_currents.a1 = (Global_Data.aa.A2.me.ADC_A1 + adc_offset) * adc_factor;
	m_6ph_abc_currents.b1 = (Global_Data.aa.A2.me.ADC_A2 + adc_offset) * adc_factor;
	m_6ph_abc_currents.c1 = (Global_Data.aa.A2.me.ADC_A3 + adc_offset) * adc_factor;
	m_6ph_abc_currents.a2 = (Global_Data.aa.A2.me.ADC_A4 + adc_offset) * adc_factor;
	m_6ph_abc_currents.b2 = (Global_Data.aa.A2.me.ADC_B5 + adc_offset) * adc_factor;
	m_6ph_abc_currents.c2 = (Global_Data.aa.A2.me.ADC_B6 + adc_offset) * adc_factor;
*/

	//assign ADC values to motor currents

/*
    m_6ph_abc_currents.a1 = -1.0*Global_Data.aa.A2.me.ADC_A4-0.0338*Global_Data.aa.A2.me.ADC_A4+0.0259;
	m_6ph_abc_currents.b1 = -1.0*Global_Data.aa.A2.me.ADC_A3+0.0407*Global_Data.aa.A2.me.ADC_A3+0.0280;
	m_6ph_abc_currents.c1 = -1.0*Global_Data.aa.A2.me.ADC_A2+0.0401*Global_Data.aa.A2.me.ADC_A2+0.0220;
	m_6ph_abc_currents.a2 = -1.0*Global_Data.aa.A2.me.ADC_B8+0.0541*Global_Data.aa.A2.me.ADC_B8+0.0352;
	m_6ph_abc_currents.b2 = -1.0*Global_Data.aa.A2.me.ADC_B7+0.0516*Global_Data.aa.A2.me.ADC_B7-0.0133;
	m_6ph_abc_currents.c2 = -1.0*Global_Data.aa.A2.me.ADC_B6+0.0341*Global_Data.aa.A2.me.ADC_B6+0.0383;
*/

    m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4 +0.0209)*1.067;
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3-0.0170)*1.04;
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2-0.0230)*1.08;	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8+0.0)*1.06;
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7+0.012)*1.05;
	m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6-0.02)*1.06;


	//crude over current protection
	if(fabs(m_6ph_abc_currents.a1) > 15.0f || fabs(m_6ph_abc_currents.b1) > 15.0f || fabs(m_6ph_abc_currents.c1) > 15.0f || fabs(m_6ph_abc_currents.a2) > 15.0f || fabs(m_6ph_abc_currents.b2) > 15.0f || fabs(m_6ph_abc_currents.c2) > 15.0f){

		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge9DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge10DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge11DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge12DutyCycle = 0.0f;

		//write duty-cycles
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);	//D3 gan inv
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);	//D4 gan inv
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

		uz_assert(0);
	}


	//write phase currents into global_data-struct
	Global_Data.av.I_U = m_6ph_abc_currents.a1;
	Global_Data.av.I_V = m_6ph_abc_currents.b1;
	Global_Data.av.I_W = m_6ph_abc_currents.c1;
	Global_Data.av.I_X = m_6ph_abc_currents.a2;
	Global_Data.av.I_Y = m_6ph_abc_currents.b2;
	Global_Data.av.I_Z = m_6ph_abc_currents.c2;


	//Transform phase-currents to alpha-beta-x-y-z1-z2
	m_6ph_alphabeta_currents = uz_transformation_asym30deg_6ph_abc_to_alphabeta(m_6ph_abc_currents);

	Global_Data.av.I_alpha = m_6ph_alphabeta_currents.alpha;
	Global_Data.av.I_beta = m_6ph_alphabeta_currents.beta;
	Global_Data.av.I_x = m_6ph_alphabeta_currents.x;
	Global_Data.av.I_y = m_6ph_alphabeta_currents.y;
	Global_Data.av.I_z1 = m_6ph_alphabeta_currents.z1;
	Global_Data.av.I_z2 = m_6ph_alphabeta_currents.z2;

	//calculate meassured dq-currents
	m_alphabeta_currents.alpha = m_6ph_alphabeta_currents.alpha;
	m_alphabeta_currents.beta = m_6ph_alphabeta_currents.beta;
	m_dq_currents = uz_transformation_3ph_alphabeta_to_dq(m_alphabeta_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

	m_xy_currents[0] = m_6ph_alphabeta_currents.x;
	m_xy_currents[1] = m_6ph_alphabeta_currents.y;

	m_z1z2_currents[0] = m_6ph_alphabeta_currents.z1;
	m_z1z2_currents[1] = m_6ph_alphabeta_currents.z2;

	Global_Data.av.I_d = m_dq_currents.d;
	Global_Data.av.I_q = m_dq_currents.q;

	//

	ref_dq0_currents.d = Global_Data.av.I_d_ref;
	ref_dq0_currents.q = Global_Data.av.I_q_ref;


	// ML_MT-OPF-Control get Reference-Values for Control:

	R_FD_Filt.R1 = filteredFDIndices[0];
	R_FD_Filt.R2 = filteredFDIndices[1];
	R_FD_Filt.R3 = filteredFDIndices[2];
	R_FD_Filt.R4 = filteredFDIndices[3];
	R_FD_Filt.R5 = filteredFDIndices[4];
	R_FD_Filt.R6 = filteredFDIndices[5];

	R_FD_eval = uz_fsd_fd_evaluation(R_FD_Filt, 0.4);

	//R_FD_eval;

	num_OPF = 0;

	if (R_FD_eval.R1 == 1.0f){
		opf_phases[num_OPF] = 1;
		num_OPF += 1;
	}
	if (R_FD_eval.R2 == 1.0f){
		opf_phases[num_OPF] = 2;
		num_OPF += 1;
	}
	if (R_FD_eval.R3 == 1.0f){
		opf_phases[num_OPF] = 3;
		num_OPF += 1;
	}
	if (R_FD_eval.R4 == 1.0f){
		opf_phases[num_OPF] = 4;
		num_OPF += 1;
	}
	if (R_FD_eval.R5 == 1.0f){
		opf_phases[num_OPF] = 5;
		num_OPF += 1;
	}
	if (R_FD_eval.R6 == 1.0f){
		opf_phases[num_OPF] = 6;
		num_OPF += 1;
	}



	int N1N2 = 1;
	int ML = 1;		//0 -> MT, 1 -> ML
	float a = 0.0f;
	int error_opf;

	kparameter k_parameter;

	k_parameter = get_k_parameter(opf_phases[0], opf_phases[1], opf_phases[2], num_OPF, N1N2, ML, &a, &error_opf);

	// calculate reference values for xy and 0102:

	// ref_dq0_currents.d = Global_Data.av.I_d_ref;
	// ref_dq0_currents.q = Global_Data.av.I_q_ref;

	// calculate alpha-beta-refs:

	ref_alphabeta_currents = uz_transformation_3ph_dq_to_alphabeta(ref_dq0_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

	// x_ref = k1 * i_alpha + k2 * i_beta
	// y_ref = k3 * i_alpha + k4 * i_beta
	// z1_ref = k5 * i_alpha + k6 * i_beta
	// z2_ref = k7 * i_alpha + k8 * i_beta

	ref_xy_currents[0] = k_parameter.k1 * ref_alphabeta_currents.alpha + k_parameter.k2 * ref_alphabeta_currents.beta;
	ref_xy_currents[1] = k_parameter.k3 * ref_alphabeta_currents.alpha + k_parameter.k4 * ref_alphabeta_currents.beta;
	ref_z1z2_currents[0] = k_parameter.k5 * ref_alphabeta_currents.alpha + k_parameter.k6 * ref_alphabeta_currents.beta;
	ref_z1z2_currents[1] = k_parameter.k7 * ref_alphabeta_currents.alpha + k_parameter.k8 * ref_alphabeta_currents.beta;

	/*-----------------------------------------------------------*/


	// read data from gan inverters:
	uz_d_gan_inverter_update_states(gan_inverter_D3);
	uz_d_gan_inverter_update_states(gan_inverter_D4);

	Global_Data.objects.gan_inverter_outputs_D3 = uz_d_gan_inverter_get_outputs(gan_inverter_D3);
	Global_Data.objects.gan_inverter_outputs_D4 = uz_d_gan_inverter_get_outputs(gan_inverter_D4);


	platform_state_t current_state=ultrazohm_state_machine_get_state();

	//enable gan inverters if system enable
	if (current_state == idle_state || current_state == error_state) {
		//Set Data To UZ_D_GaN_Inverter
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_1_UZ_D_GAN_INVERTER_0_BASEADDR, false);
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR, false);
	} else if (current_state == running_state || current_state == control_state) { //Call this function only once. If there was an error, "enableSystem " must be reseted!
		//Set Data To UZ_D_GaN_Inverter
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_1_UZ_D_GAN_INVERTER_0_BASEADDR, true);
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR, true);
	}


	//default dutyclcles:
	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.ref_halfBridge1DutyCycle;
	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.ref_halfBridge2DutyCycle;
	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.ref_halfBridge3DutyCycle;
	Global_Data.rasv.halfBridge4DutyCycle = Global_Data.rasv.ref_halfBridge4DutyCycle;
	Global_Data.rasv.halfBridge5DutyCycle = Global_Data.rasv.ref_halfBridge5DutyCycle;
	Global_Data.rasv.halfBridge6DutyCycle = Global_Data.rasv.ref_halfBridge6DutyCycle;
	Global_Data.rasv.halfBridge7DutyCycle = Global_Data.rasv.ref_halfBridge7DutyCycle;
	Global_Data.rasv.halfBridge8DutyCycle = Global_Data.rasv.ref_halfBridge8DutyCycle;
	Global_Data.rasv.halfBridge9DutyCycle = Global_Data.rasv.ref_halfBridge9DutyCycle;
	Global_Data.rasv.halfBridge10DutyCycle = Global_Data.rasv.ref_halfBridge10DutyCycle;
	Global_Data.rasv.halfBridge11DutyCycle = Global_Data.rasv.ref_halfBridge11DutyCycle;
	Global_Data.rasv.halfBridge12DutyCycle = Global_Data.rasv.ref_halfBridge12DutyCycle;

/*
	value_1 = uz_vsd_and_park_transformation_6phase_get_id_iq(vsd_park);

	value_2 = uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(vsd_park);
*/






    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state


    	//6-Phase-FOC:

    	//Control
    		//FOC_instance
    	ref_dq_voltage = uz_FOC_sample(FOC_dq, ref_dq0_currents, m_dq_currents, Global_Data.av.U_ZK, omega_el_rad_per_sec);


    	// R-Controller: 2 H. dq
    	r_c_2H_d.input.T_sw = 0.0001; //1/10000;
		r_c_2H_d.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
		r_c_2H_d.input.h = 2.0;
		r_c_2H_d.input.omega_el = omega_el_rad_per_sec;
		r_c_2H_d.input.in_ref = ref_dq0_currents.d;
		r_c_2H_d.input.in_m = m_dq_currents.d;

		uz_resonant_controller_step(&r_c_2H_d);

		if (dq_2){
			ref_dq_voltage.d = ref_dq_voltage.d + r_c_2H_d.output.out;
		}


		r_c_2H_q.input.T_sw = 0.0001; //1/10000;
		r_c_2H_q.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
		r_c_2H_q.input.h = 2.0;
		r_c_2H_q.input.omega_el = omega_el_rad_per_sec;
		r_c_2H_q.input.in_ref = ref_dq0_currents.q;
		r_c_2H_q.input.in_m = m_dq_currents.q;

		uz_resonant_controller_step(&r_c_2H_q);

		if(dq_2){
			ref_dq_voltage.q = ref_dq_voltage.q + r_c_2H_q.output.out;
		}









    	//Transform back to phase-values:
    	ref_alphabeta_voltage = uz_transformation_3ph_dq_to_alphabeta(ref_dq_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

    	// new control-parameters:
    	uz_FOC_set_Kp_id(FOC_dq, Global_Data.av.kp_d);
    	uz_FOC_set_Ki_id(FOC_dq, Global_Data.av.ki_d);
    	uz_FOC_set_Kp_iq(FOC_dq, Global_Data.av.kp_q);
    	uz_FOC_set_Ki_iq(FOC_dq, Global_Data.av.ki_q);


    	//antisynchron frame:

    		//measurement and ref values in alpha-beta frame:
			m_ab_currents[0] = m_alphabeta_currents.alpha;
			m_ab_currents[1] = m_alphabeta_currents.beta;

			ref_dq_currents[0] = ref_dq0_currents.d;
			ref_dq_currents[1] = ref_dq0_currents.q;

			uz_inv_park_transform(ref_ab_currents, ref_dq_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);


			//transform into antisynchron frame:
			uz_inv_park_transform(m_ab_n_currents, m_ab_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
			uz_inv_park_transform(ref_ab_n_currents, ref_ab_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

			//PI-Controller:

    		//PI-Controllers
			ref_ab_n_voltage[0] = uz_PI_Controller_sample(PI_d_n, ref_ab_n_currents[0], m_ab_n_currents[0], false);
    		ref_ab_n_voltage[1] = uz_PI_Controller_sample(PI_q_n, ref_ab_n_currents[1], m_ab_n_currents[1], false);

    		//transform back to alpha-beta frame
    		uz_park_transform(ref_ab_voltage_n, ref_ab_n_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);


    	//combine:
    	if(dq_n){
			ref_alphabeta_voltage.alpha += ref_ab_voltage_n[0];
			ref_alphabeta_voltage.beta += ref_ab_voltage_n[1];
    	}


    //-xy-current control:--------------//

    	// Measurement and reference values for xy-currents:

    	// m_xy_currents[0] = m_6ph_alphabeta_currents.x;
    	// m_xy_currents[1] = m_6ph_alphabeta_currents.y;

		xy_error[0] = ref_xy_currents[0] - m_xy_currents[0];
		xy_error[1] = ref_xy_currents[1] - m_xy_currents[1];

    	// ref_xy_currents[0] = 0;

    	// ref_xy_currents[1] = 0;

    	ref_xy_voltage[0] = 0;
    	ref_xy_voltage[1] = 0;

    	// synchron PI-controller:
#define PI_CONTROLLER
#ifndef PI_CONTROLLER
    		//transform into synchronous frame:
    		uz_park_transform(m_xy_s_currents, m_xy_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
    		uz_park_transform(ref_xy_s_currents, ref_xy_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

    		//PI-Controllers
    		ref_xy_s_voltage[0] = uz_PI_Controller_sample(PI_x_s, ref_xy_s_currents[0], m_xy_s_currents[0], false);
    		ref_xy_s_voltage[1] = uz_PI_Controller_sample(PI_y_s, ref_xy_s_currents[1], m_xy_s_currents[1], false);

    		//inverse transform to stationary frame
    		uz_inv_park_transform(ref_xy_voltage_s, ref_xy_s_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
#endif

    	// antisynchron PI-controller:

    		//transform into antisynchronous frame:
    		uz_inv_park_transform(m_xy_n_currents, m_xy_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
    		uz_inv_park_transform(ref_xy_n_currents, ref_xy_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

    		//PI-Controllers
    		ref_xy_n_voltage[0] = uz_PI_Controller_sample(PI_x_n, ref_xy_n_currents[0], m_xy_n_currents[0], false);
    		ref_xy_n_voltage[1] = uz_PI_Controller_sample(PI_y_n, ref_xy_n_currents[1], m_xy_n_currents[1], false);




    	// antisynchron R-Controller 2. Harmonische:
    		r_c_2H_x.input.T_sw = 0.0001; //1/10000;
    		r_c_2H_x.input.VR = 160; //0.1*(2.0*M_PI*10000.0/10.0)*(2*M_PI*10000.0/10.0)*0.00004;
    		r_c_2H_x.input.h = 2;
    		r_c_2H_x.input.omega_el = omega_el_rad_per_sec;
    		r_c_2H_x.input.in_ref = ref_xy_n_currents[0];
			r_c_2H_x.input.in_m = m_xy_n_currents[0];

			//uz_resonant_controller_step(&r_c_2H_x);

			//ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + r_c_2H_x.output.out;

    		r_c_2H_y.input.T_sw = 0.0001; //1/10000;
    		r_c_2H_y.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    		r_c_2H_y.input.h = 2.0;
    		r_c_2H_y.input.omega_el = omega_el_rad_per_sec;
    		r_c_2H_y.input.in_ref = ref_xy_n_currents[1];
			r_c_2H_y.input.in_m = m_xy_n_currents[1];

			//uz_resonant_controller_step(&r_c_2H_y);

			//ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + r_c_2H_y.output.out;


			//////////////////

    		r_c_6H_x.input.T_sw = 0.0001; //1/10000;
    		r_c_6H_x.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    		r_c_6H_x.input.h = 2.0;
    		r_c_6H_x.input.omega_el = omega_el_rad_per_sec;
    		r_c_6H_x.input.in_ref = ref_xy_n_currents[0];
    		r_c_6H_x.input.in_m = m_xy_n_currents[0];

    		uz_resonant_controller_step(&r_c_6H_x);

    		if (xy_n_6){
    			ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + r_c_6H_x.output.out;
    		}


    		r_c_6H_y.input.T_sw = 0.0001; //1/10000;
    		r_c_6H_y.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    		r_c_6H_y.input.h = 2.0;
    		r_c_6H_y.input.omega_el = omega_el_rad_per_sec;
    		r_c_6H_y.input.in_ref = ref_xy_n_currents[1];
    		r_c_6H_y.input.in_m = m_xy_n_currents[1];

    		uz_resonant_controller_step(&r_c_6H_y);

    		if(xy_n_6){
    			ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + r_c_6H_y.output.out;
    		}

    		/////////////////////////


		// alternativer R-Controller:

			// Reglerparameter anpassen:

			r_c_VR = 160; //0.1 * (2.0*M_PI*1000.0)*(2.0*M_PI*1000.0)* 0.00004;
			r_c_Tsw = 0.0001f; // 1/10000;
			r_c_omega_r = 2 * omega_el_rad_per_sec;		// 2 gegen 6 austauschen für 6. Harmonische!!!

			r_c_iir_2H_x->filterParameterA[0] = 1.0;
			r_c_iir_2H_x->filterParameterA[1] = -2.0*cos(r_c_omega_r*r_c_Tsw);
			r_c_iir_2H_x->filterParameterA[2] = 1.0;
			r_c_iir_2H_x->filterParameterB[0] = r_c_VR*r_c_Tsw*cos(2.0*r_c_omega_r*r_c_Tsw);
			r_c_iir_2H_x->filterParameterB[1] = r_c_VR*r_c_Tsw* -cos(r_c_omega_r*r_c_Tsw);
			r_c_iir_2H_x->filterParameterB[2] = r_c_VR*r_c_Tsw*0;

			zw_1 = uz_filter_sample(r_c_iir_2H_x, (ref_xy_n_currents[0] - m_xy_n_currents[0]));

			r_c_iir_2H_y->filterParameterA[0] = 1.0;
			r_c_iir_2H_y->filterParameterA[1] = -2.0*cos(r_c_omega_r*r_c_Tsw);
			r_c_iir_2H_y->filterParameterA[2] = 1.0;
			r_c_iir_2H_y->filterParameterB[0] = r_c_VR*r_c_Tsw*cos(2.0*r_c_omega_r*r_c_Tsw);
			r_c_iir_2H_y->filterParameterB[1] = r_c_VR*r_c_Tsw* -cos(r_c_omega_r*r_c_Tsw);
			r_c_iir_2H_y->filterParameterB[2] = r_c_VR*r_c_Tsw*0;

			zw_2 = uz_filter_sample(r_c_iir_2H_y, (ref_xy_n_currents[1] - m_xy_n_currents[1]));

			/* Bilineare Übertragungsfunktion:

			float Kr = 120;
			float Ta = 0.0001f;
			float wc = 10;
			float wr = 2 * omega_el_rad_per_sec;

			r_c_iir_2H_x->filterParameterB[2] = -2*Kr*Ta;
			r_c_iir_2H_x->filterParameterB[1] = 0;
			r_c_iir_2H_x->filterParameterB[0] = 2*Kr*Ta;
			r_c_iir_2H_x->filterParameterA[2] = 4-4*wc*Ta+wr*wr*Ta*Ta;
			r_c_iir_2H_x->filterParameterA[1] = 2*wr*wr*Ta*Ta - 8;
			r_c_iir_2H_x->filterParameterA[0] = 4 + 4*wc*Ta + wr*wr*Ta*Ta;
			*/

			/* Impulsinvariant Übertragungsfunktion:
			float Kr = 100;
			float Ta = 0.0001f;
			float wc = 10;
			float wr = 2 * omega_el_rad_per_sec;

			r_c_iir_2H_x->filterParameterB[2] = -Kr*Ta*cos(wr*Ta);
			r_c_iir_2H_x->filterParameterB[1] = 0;
			r_c_iir_2H_x->filterParameterB[0] = Kr*Ta;
			r_c_iir_2H_x->filterParameterA[2] = 1;
			r_c_iir_2H_x->filterParameterA[1] = -2*cos(wr*Ta);
			r_c_iir_2H_x->filterParameterA[0] = 1;
			*/

		if(xy_n_2){
			ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + zw_1;
			ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + zw_2;
		}
    	//combine values from synchron- and antisynchron frame:

		//Transform pack to stationary frame
		uz_park_transform(ref_xy_voltage_n, ref_xy_n_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);


    	if(xy_n){
    		ref_xy_voltage[0] = ref_xy_voltage_n[0];
    		ref_xy_voltage[1] = ref_xy_voltage_n[1];
    	}
    	if(xy_s){
    		ref_xy_voltage[0] += ref_xy_voltage_s[0];
    		ref_xy_voltage[1] += ref_xy_voltage_s[1];
    	}




    //-z1z2-current control:--------------//


		z1z2_error[0] = ref_z1z2_currents[0] - m_z1z2_currents[0];
		z1z2_error[1] = ref_z1z2_currents[1] - m_z1z2_currents[1];


/*


    	ref_z1z2_voltage[0] = 0;
    	ref_z1z2_voltage[1] = 0;

		z1z2_error[0] = ref_z1z2_currents[0] - m_z1z2_currents[0];
		z1z2_error[1] = ref_z1z2_currents[1] - m_z1z2_currents[1];


    	// make P-Controller from PI-Controller
    	uz_PI_Controller_set_Ki(PI_z1_s, 0);
    	uz_PI_Controller_set_Ki(PI_z2_s, 0);

    	uz_PI_Controller_set_Kp(PI_z1_s, 0.05*0.1f);
		uz_PI_Controller_set_Kp(PI_z2_s, 0.05*0.1f);

    	ref_z1z2_voltage[0] = uz_PI_Controller_sample(PI_z1_s, ref_z1z2_currents[0], m_z1z2_currents[0], false);
		ref_z1z2_voltage[1] = uz_PI_Controller_sample(PI_z2_s, ref_z1z2_currents[1], m_z1z2_currents[1], false);



		z1z2_error[0] = ref_z1z2_currents[0] - m_z1z2_currents[0];
		z1z2_error[1] = ref_z1z2_currents[1] - m_z1z2_currents[1];


    	// R-Controller: 9 H. //fundamental frequency

    	r_c_2H_z1.input.T_sw = 0.0001f; //1/10000;
    	r_c_2H_z1.input.VR =  100; // 30; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    	r_c_2H_z1.input.h =9.0;
    	r_c_2H_z1.input.omega_el = omega_el_rad_per_sec;
    	r_c_2H_z1.input.in_ref = ref_z1z2_currents[0];
    	r_c_2H_z1.input.in_m = m_z1z2_currents[0];

		uz_resonant_controller_step(&r_c_2H_z1);

		if (z1z2_2){
			ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + r_c_2H_z1.output.out;
		}


		r_c_2H_z2.input.T_sw = 0.0001; //1/10000;
		r_c_2H_z2.input.VR = 100; // 30; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
		r_c_2H_z2.input.h = 9.0;
		r_c_2H_z2.input.omega_el = omega_el_rad_per_sec;
		r_c_2H_z2.input.in_ref = ref_z1z2_currents[1];
		r_c_2H_z2.input.in_m = m_z1z2_currents[1];

		uz_resonant_controller_step(&r_c_2H_z2);

		if(z1z2_2){
			ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + r_c_2H_z2.output.out;
		}





    	// R-Controller: 3 H.
		r_c_3H_z1.input.T_sw = 0.0001; //1/10000;
		r_c_3H_z1.input.VR =  100; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
		r_c_3H_z1.input.h = 3.0;
		r_c_3H_z1.input.omega_el = omega_el_rad_per_sec;
		r_c_3H_z1.input.in_ref = ref_z1z2_currents[0];
		r_c_3H_z1.input.in_m = m_z1z2_currents[0];

		uz_resonant_controller_step(&r_c_3H_z1);

		if (z1z2_3){
			ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + r_c_3H_z1.output.out;
		}


		r_c_3H_z2.input.T_sw = 0.0001; //1/10000;
		r_c_3H_z2.input.VR =  100; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
		r_c_3H_z2.input.h = 3.0;
		r_c_3H_z2.input.omega_el = omega_el_rad_per_sec;
		r_c_3H_z2.input.in_ref = ref_z1z2_currents[1];
		r_c_3H_z2.input.in_m = m_z1z2_currents[1];

		uz_resonant_controller_step(&r_c_3H_z2);

		if(z1z2_3){
			ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + r_c_3H_z2.output.out;
		}
*/



    	// synchron PI-controller:

    		//transform into synchronous frame:
    		uz_park_transform(m_z1z2_s_currents, m_z1z2_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
    		uz_park_transform(ref_z1z2_s_currents, ref_z1z2_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);


    		error_z1z2_s[0] = ref_z1z2_s_currents[0] -m_z1z2_s_currents[0];
    		error_z1z2_s[1] = ref_z1z2_s_currents[1] -m_z1z2_s_currents[1];

    		//PI-Controllers
    		ref_z1z2_s_voltage[0] = uz_PI_Controller_sample(PI_z1_s, ref_z1z2_s_currents[0], m_z1z2_s_currents[0], false);
    		ref_z1z2_s_voltage[1] = uz_PI_Controller_sample(PI_z2_s, ref_z1z2_s_currents[1], m_z1z2_s_currents[1], false);

/*

        	// R-Controller: 3 H.
    		r_c_3H_z1.input.T_sw = 0.0001; //1/10000;
    		r_c_3H_z1.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    		r_c_3H_z1.input.h = 2.0;
    		r_c_3H_z1.input.omega_el = omega_el_rad_per_sec;
    		r_c_3H_z1.input.in_ref = ref_z1z2_s_currents[0];
    		r_c_3H_z1.input.in_m = m_z1z2_s_currents[0];

    		uz_resonant_controller_step(&r_c_3H_z1);

    		if (z1z2_3){
    			ref_z1z2_s_voltage[0] = ref_z1z2_s_voltage[0] + r_c_3H_z1.output.out;
    		}


    		r_c_3H_z2.input.T_sw = 0.0001; //1/10000;
    		r_c_3H_z2.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    		r_c_3H_z2.input.h = 2.0;
    		r_c_3H_z2.input.omega_el = omega_el_rad_per_sec;
    		r_c_3H_z2.input.in_ref = ref_z1z2_s_currents[1];
    		r_c_3H_z2.input.in_m = m_z1z2_s_currents[1];

    		uz_resonant_controller_step(&r_c_3H_z2);

    		if(z1z2_3){
    			ref_z1z2_s_voltage[1] = ref_z1z2_s_voltage[1] + r_c_3H_z2.output.out;
    		}

*/




    		//inverse transform to stationary frame
    		uz_inv_park_transform(ref_z1z2_voltage_s, ref_z1z2_s_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);



    	// antisynchron PI-controller:

    		//transform into antisynchronous frame:
    		uz_inv_park_transform(m_z1z2_n_currents, m_z1z2_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
    		uz_inv_park_transform(ref_z1z2_n_currents, ref_z1z2_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

    		error_z1z2_n[0] = ref_z1z2_n_currents[0] -m_z1z2_n_currents[0];
    		error_z1z2_n[1] = ref_z1z2_n_currents[1] -m_z1z2_n_currents[1];

    		//PI-Controllers
    		ref_z1z2_n_voltage[0] = uz_PI_Controller_sample(PI_z1_n, ref_z1z2_n_currents[0], m_z1z2_n_currents[0], false);
    		ref_z1z2_n_voltage[1] = uz_PI_Controller_sample(PI_z2_n, ref_z1z2_n_currents[1], m_z1z2_n_currents[1], false);

/*

        	// R-Controller: 1 H.
        	r_c_2H_z1.input.T_sw = 0.0001; //1/10000;
        	r_c_2H_z1.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
        	r_c_2H_z1.input.h =2.0;
        	r_c_2H_z1.input.omega_el = omega_el_rad_per_sec;
        	r_c_2H_z1.input.in_ref = ref_z1z2_n_currents[0];
        	r_c_2H_z1.input.in_m = m_z1z2_n_currents[0];

    		uz_resonant_controller_step(&r_c_2H_z1);

    		if (z1z2_2){
    			ref_z1z2_n_voltage[0] += r_c_2H_z1.output.out;
    		}


    		r_c_2H_z2.input.T_sw = 0.0001; //1/10000;
    		r_c_2H_z2.input.VR =  160; // 0.1*(2.0*M_PI*1000.0f)*(2.0*M_PI*1000.0f)*0.00004;
    		r_c_2H_z2.input.h = 2.0;
    		r_c_2H_z2.input.omega_el = omega_el_rad_per_sec;
    		r_c_2H_z2.input.in_ref = ref_z1z2_n_currents[1];
    		r_c_2H_z2.input.in_m = m_z1z2_n_currents[1];

    		uz_resonant_controller_step(&r_c_2H_z2);

    		if(z1z2_2){
    			ref_z1z2_n_voltage[1] += r_c_2H_z2.output.out;
    		}
*/




    		//Transform back to stationary frame
    		uz_park_transform(ref_z1z2_voltage_n, ref_z1z2_n_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);





    	// enable/disable PI-Controllers:
        	if(z1z2_n){
        		ref_z1z2_voltage[0] = ref_z1z2_voltage_n[0];
        		ref_z1z2_voltage[1] = ref_z1z2_voltage_n[1];
        	}
        	if(z1z2_s){
        		ref_z1z2_voltage[0] += ref_z1z2_voltage_s[0];
        		ref_z1z2_voltage[1] += ref_z1z2_voltage_s[1];
        	}




    //----------------------------------//





    	ref_6ph_alphabeta_voltage.alpha = ref_alphabeta_voltage.alpha;
    	ref_6ph_alphabeta_voltage.beta = ref_alphabeta_voltage.beta;
    	ref_6ph_alphabeta_voltage.x = ref_xy_voltage[0];
    	ref_6ph_alphabeta_voltage.y = ref_xy_voltage[1];
    	ref_6ph_alphabeta_voltage.z1 = ref_z1z2_voltage[0];
    	ref_6ph_alphabeta_voltage.z2 = ref_z1z2_voltage[1];

    	ref_6ph_abc_voltage = uz_transformation_asym30deg_6ph_alphabeta_to_abc(ref_6ph_alphabeta_voltage);

    	//calculate duty-cycles:
    	ref_volage_phase_set1.a = ref_6ph_abc_voltage.a1;
		ref_volage_phase_set1.b = ref_6ph_abc_voltage.b1;
		ref_volage_phase_set1.c = ref_6ph_abc_voltage.c1;
		ref_volage_phase_set2.a = ref_6ph_abc_voltage.a2;
		ref_volage_phase_set2.b = ref_6ph_abc_voltage.b2;
		ref_volage_phase_set2.c = ref_6ph_abc_voltage.c2;

		dutyCycles_set1 = uz_FOC_generate_DutyCycles(ref_volage_phase_set1, Global_Data.av.U_ZK);
    	dutyCycles_set2 = uz_FOC_generate_DutyCycles(ref_volage_phase_set2, Global_Data.av.U_ZK);

    	//write duty-cycles
    	Global_Data.rasv.halfBridge4DutyCycle = dutyCycles_set2.DutyCycle_U;
    	Global_Data.rasv.halfBridge5DutyCycle = dutyCycles_set2.DutyCycle_V;
    	Global_Data.rasv.halfBridge6DutyCycle = dutyCycles_set2.DutyCycle_W;
    	Global_Data.rasv.halfBridge7DutyCycle = dutyCycles_set1.DutyCycle_U;
    	Global_Data.rasv.halfBridge8DutyCycle = dutyCycles_set1.DutyCycle_V;
    	Global_Data.rasv.halfBridge9DutyCycle = dutyCycles_set1.DutyCycle_W;

    }
    else{
    	// Reset Controllers if control-state is not active
    	uz_FOC_reset(FOC_dq);
    	uz_PI_Controller_reset(PI_d_n);
		uz_PI_Controller_reset(PI_q_n);
		uz_PI_Controller_reset(PI_x_s);
		uz_PI_Controller_reset(PI_y_s);
		uz_PI_Controller_reset(PI_x_n);
		uz_PI_Controller_reset(PI_y_n);
		uz_PI_Controller_reset(PI_z1_s);
		uz_PI_Controller_reset(PI_z1_n);
		uz_PI_Controller_reset(PI_z2_s);
		uz_PI_Controller_reset(PI_z2_n);
		uz_filter_reset(r_c_iir_2H_x);
		uz_filter_reset(r_c_iir_2H_y);
    }





    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);	//D3 gan inv
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);	//D4 gan inv
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
