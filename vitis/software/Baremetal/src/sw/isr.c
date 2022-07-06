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

#include "../Codegen/uz_vsd_opffd_asym6ph.h"
#include "../Codegen/uz_FD.h"
#include "../Codegen/VSD_FD_6PH_V6_ert_rtw/VSD_FD_6PH_V6.h"
#include "../Codegen/uz_singleindex_faultdetection.h"

#include "../uz/uz_VSD_6ph_FD/uz_VSD6phFD.h"
#include "../uz/uz_FOC/uz_FOC.h"


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

// variables for 6phase-vsd-test
const float amplitude = 5.0f;
const float frequency = 10.0f;	//Hz
const float p1 = 0.0;
const float p2 = -2*UZ_PIf/3;
const float p3 = -4*UZ_PIf/3;
const float p4 = -UZ_PIf/6;
const float p5 = -5*UZ_PIf/6;
const float p6 = -9*UZ_PIf/6;

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

float ph_a1 = 0.0f;
float ph_b1 = 0.0f;
float ph_c1 = 0.0f;
float ph_a2 = 0.0f;
float ph_b2 = 0.0f;
float ph_c2 = 0.0f;

uz_6phFD_indices R_FD = {0};
uz_6phFD_indices R_FD_Filt = {0};
uz_6phFD_indices R_FD_eval = {0};


extern uz_vsd_opffd_asym6ph vsd_fd_V4;
extern uz_FD uz_FD_V6;
extern uz_vsd_opf_fd_v7 uz_FD_v7;

extern uz_singleindex_faultdetection singleindex_FD;


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

extern uz_FOC* FOC_instance;
extern struct uz_FOC_config config_FOC;
extern struct uz_PMSM_t config_PMSM;

uz_6ph_abc_t m_6ph_abc_currents = {0};
uz_6ph_alphabeta_t m_6ph_alphabeta_currents = {0};

uz_3ph_alphabeta_t m_alphabeta_currents = {0};
uz_3ph_dq_t m_dq_currents = {0};

uz_3ph_alphabeta_t ref_alphabeta_voltage = {0};
uz_3ph_dq_t ref_dq_voltage = {0};

uz_6ph_abc_t ref_6ph_abc_voltage = {0};
uz_6ph_alphabeta_t ref_6ph_alphabeta_voltage = {0};

uz_3ph_abc_t ref_volage_phase_set1 = {0};
uz_3ph_abc_t ref_volage_phase_set2 = {0};

uz_3ph_dq_t ref_dq0_currents = {0};

struct uz_DutyCycle_t dutyCycles_set1 = {0};
struct uz_DutyCycle_t dutyCycles_set2 = {0};

float adc_offset = 0.0f;
float adc_factor = 1.0f;

float theta_el_offset = 0.0f;

float omega_el_rad_per_sec = 0.0f;
int mov_average_filter_length = 0;


extern struct uz_d_gan_inverter_t* gan_inverter_D3;
extern struct uz_d_gan_inverter_t* gan_inverter_D4;

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
    R_FD_eval = uz_fsd_fd_evaluation(R_FD_Filt, 0.5);


//Version 4:
/*
	//set inputs
    vsd_fd_V4.input.i_ab_xy_z1z2[0] = i_abxyz1z2.alpha;
    vsd_fd_V4.input.i_ab_xy_z1z2[1] = i_abxyz1z2.beta;
    vsd_fd_V4.input.i_ab_xy_z1z2[2] = i_abxyz1z2.x;
    vsd_fd_V4.input.i_ab_xy_z1z2[3] = i_abxyz1z2.y;
    vsd_fd_V4.input.i_ab_xy_z1z2[4] = 0.0f;// i_abxyz1z2.z1;	//has to be 0, not zero values are errors/ noise
    vsd_fd_V4.input.i_ab_xy_z1z2[5] = 0.0f;// i_abxyz1z2.z2;
    vsd_fd_V4.input.HB_u = 0.3;
    vsd_fd_V4.input.HB_o = 0.3;

    //run detection V4
    uz_vsd_opffd_asym6ph_step(&vsd_fd_V4);
    for(int i = 0; i<6; i++){
        vsd_output_V4[i] = (float)vsd_fd_V4.output.FD_raw[i];
        vsd_output_hyst_V4[i] = (float)vsd_fd_V4.output.FD_hyst[i];
        vsd_output_filtered_V4[i] = (float)vsd_fd_V4.output.FD_filtered[i];
    }
*/
//Version 6:
/*
    uz_FD_V6.input.i_ab_xy_z1z2[0] = i_abxyz1z2.alpha;
    uz_FD_V6.input.i_ab_xy_z1z2[1] = i_abxyz1z2.beta;
    uz_FD_V6.input.i_ab_xy_z1z2[2] = i_abxyz1z2.x;
    uz_FD_V6.input.i_ab_xy_z1z2[3] = i_abxyz1z2.y;
    uz_FD_V6.input.i_ab_xy_z1z2[4] = i_abxyz1z2.z1;
    uz_FD_V6.input.i_ab_xy_z1z2[5] = i_abxyz1z2.z2;
    uz_FD_V6.input.HB_u = 0.2;
    uz_FD_V6.input.HB_o = 0.2;

    uz_FD_step(&uz_FD_V6);
*/

//Version 7:

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


//Single Index:

    singleindex_FD.input.i_ab_xy_z1z2[0] = i_abxyz1z2.alpha;
    singleindex_FD.input.i_ab_xy_z1z2[1] = i_abxyz1z2.beta;
    singleindex_FD.input.i_ab_xy_z1z2[2] = i_abxyz1z2.x;
    singleindex_FD.input.i_ab_xy_z1z2[3] = i_abxyz1z2.y;
    singleindex_FD.input.HB_Wert = 2.0;

    uz_singleindex_faultdetection_step(&singleindex_FD);

    singleIndex_FD_R = singleindex_FD.output.FD_filtered;

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
/*
    //Die zusätzlichen Offsets helfen schonmal Faktoren evtl. nochmal anpassen
	m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4-0.0338*Global_Data.aa.A2.me.ADC_A4+0.0259-0.005	)*1;
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3+0.0407*Global_Data.aa.A2.me.ADC_A3+0.0280-0.045	)*1.05;
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2+0.0401*Global_Data.aa.A2.me.ADC_A2+0.0220-0.045	)*1.05;
	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8+0.0541*Global_Data.aa.A2.me.ADC_B8+0.0352-0.035    )*1.09;
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7+0.0516*Global_Data.aa.A2.me.ADC_B7-0.0133+0.025    )*1.1;
	m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6+0.0341*Global_Data.aa.A2.me.ADC_B6+0.0383-0.058	)*1.1;
*/

	//Offset und Faktor:
/*
    m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4 +0.0209)*1.0;
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3-0.0170)*1.04;
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2-0.0230)*1.08;
	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8+0.0)*1.04;
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7+0.012)*1.02;
	m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6-0.02)*1.03;
*/
    m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4 +0.0209)*1.067;
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3-0.0170)*1.04;
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2-0.0230)*1.08;
	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8+0.0)*1.06;
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7+0.012)*1.05;
	m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6-0.02)*1.06;


	//crude over current protection
	if(fabs(m_6ph_abc_currents.a1) > 15.0f || fabs(m_6ph_abc_currents.b1) > 15.0f || fabs(m_6ph_abc_currents.c1) > 15.0f || fabs(m_6ph_abc_currents.a2) > 15.0f || fabs(m_6ph_abc_currents.b2) > 15.0f || fabs(m_6ph_abc_currents.c2) > 15.0f){
		uz_assert(0);
	}


	//write phase currents into global_data-struct
	Global_Data.av.I_U = m_6ph_abc_currents.a1;
	Global_Data.av.I_V = m_6ph_abc_currents.b1;
	Global_Data.av.I_W = m_6ph_abc_currents.c1;
	Global_Data.av.I_X = m_6ph_abc_currents.a2;
	Global_Data.av.I_Y = m_6ph_abc_currents.b2;
	Global_Data.av.I_Z = m_6ph_abc_currents.c2;

	//filter phase-currents:
	Global_Data.av.I_U_Filtered = (float)uz_filter_sample(filter_a1, (double)m_6ph_abc_currents.a1);
	Global_Data.av.I_V_Filtered = (float)uz_filter_sample(filter_b1, (double)m_6ph_abc_currents.b1);
	Global_Data.av.I_W_Filtered = (float)uz_filter_sample(filter_c1, (double)m_6ph_abc_currents.c1);
	Global_Data.av.I_X_Filtered = (float)uz_filter_sample(filter_a2, (double)m_6ph_abc_currents.a2);
	Global_Data.av.I_Y_Filtered = (float)uz_filter_sample(filter_b2, (double)m_6ph_abc_currents.b2);
	Global_Data.av.I_Z_Filtered = (float)uz_filter_sample(filter_c2, (double)m_6ph_abc_currents.c2);


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

	Global_Data.av.I_d = m_dq_currents.d;
	Global_Data.av.I_q = m_dq_currents.q;

	//

	ref_dq0_currents.d = Global_Data.av.I_d_ref;
	ref_dq0_currents.q = Global_Data.av.I_q_ref;



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


    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state


    	//6-Phase-FOC:

    	//Control
    		//FOC_instance
    	ref_dq_voltage = uz_FOC_sample(FOC_instance, ref_dq0_currents, m_dq_currents, Global_Data.av.U_ZK, omega_el_rad_per_sec);

    	// new control-parameters:
    	uz_FOC_set_Kp_id(FOC_instance, Global_Data.av.kp_d);
    	uz_FOC_set_Ki_id(FOC_instance, Global_Data.av.ki_d);
    	uz_FOC_set_Kp_iq(FOC_instance, Global_Data.av.kp_q);
    	uz_FOC_set_Ki_iq(FOC_instance, Global_Data.av.ki_q);


    	//Transform back to phase-values:
    	ref_alphabeta_voltage = uz_transformation_3ph_dq_to_alphabeta(ref_dq_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

    	ref_6ph_alphabeta_voltage.alpha = ref_alphabeta_voltage.alpha;
    	ref_6ph_alphabeta_voltage.beta = ref_alphabeta_voltage.beta;
    	ref_6ph_alphabeta_voltage.x = 0.0f;
    	ref_6ph_alphabeta_voltage.y = 0.0f;
    	ref_6ph_alphabeta_voltage.z1 = 0.0f;
    	ref_6ph_alphabeta_voltage.z2 = 0.0f;

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
