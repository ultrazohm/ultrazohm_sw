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

#include "../uz/uz_FOC/uz_FOC.h"
#include "../uz/uz_filter/uz_filter.h"


#include "../uz/uz_VSD_6ph_FD_control/uz_VSD_6ph_FD.h"
#include "../uz/uz_VSD_6ph_FD_control/uz_VSD_6ph_ML_MT_Control.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

int N1N2 = 1;
int ML = 1;

uz_6ph_abc_t i_6phase = {0};
uz_6ph_abc_t i_6phase_filtered = {0};
uz_6ph_alphabeta_t i_abxyz1z2 = {0};
uz_6ph_alphabeta_t i_abxyz1z2_filtered = {0};

float theta_ = 0;

float vsd_output[6] = {0};
float vsd_output_hyst[6] = {0};
float vsd_output_filtered[6] = {0};

float vsd_output_V4[6] = {0};
float vsd_output_hyst_V4[6] = {0};
float vsd_output_filtered_V4[6] = {0};


int toggle = 0;
float Rb1[5] = {0};
float Rb1_filtered[5] = {0};

uz_6phFD_indices R_FD = {0};
uz_6phFD_indices R_FD_Filt = {0};
uz_6phFD_indices R_FD_Filt_hyst = {0};
uz_6phFD_indices R_FD_eval = {0};

uz_6phFD_indices FD_indices = {0};



extern uz_resonantController_t* rc_2H_x;
extern uz_resonantController_t* rc_2H_y;
extern uz_resonantController_t* rc_5H_x;
extern uz_resonantController_t* rc_5H_y;
extern uz_resonantController_t* rc_7H_x;
extern uz_resonantController_t* rc_7H_y;

extern uz_resonantController_t* rc_3H_x;
extern uz_resonantController_t* rc_3H_y;
extern uz_resonantController_t* rc_3H_a;
extern uz_resonantController_t* rc_3H_b;
extern uz_resonantController_t* rc_5H_a;
extern uz_resonantController_t* rc_5H_b;
extern uz_resonantController_t* rc_7H_a;
extern uz_resonantController_t* rc_7H_b;


extern uz_resonantController_t* rc_6H_x;
extern uz_resonantController_t* rc_6H_y;
extern uz_resonantController_t* rc_2H_d;
extern uz_resonantController_t* rc_2H_q;
extern uz_resonantController_t* rc_8H_d;
extern uz_resonantController_t* rc_8H_q;
extern uz_resonantController_t* rc_12H_d;
extern uz_resonantController_t* rc_12H_q;

extern uz_resonantController_t* rc_1H_z1;
extern uz_resonantController_t* rc_1H_z2;
extern uz_resonantController_t* rc_3H_z1;
extern uz_resonantController_t* rc_3H_z2;
extern uz_resonantController_t* rc_9H_z1;
extern uz_resonantController_t* rc_9H_z2;



float r_c_VR;
float r_c_Tsw;
float r_c_omega_r;


extern uz_movingAverageFilter_t* movAvFilter_R1;
extern uz_movingAverageFilter_t* movAvFilter_R2;
extern uz_movingAverageFilter_t* movAvFilter_R3;
extern uz_movingAverageFilter_t* movAvFilter_R4;
extern uz_movingAverageFilter_t* movAvFilter_R5;
extern uz_movingAverageFilter_t* movAvFilter_R6;


float filteredFDIndices[6] = {0};

float tempfilteredFDIndices[5] = {0};

float testvalue = 0.0f;


//parameters for 6ph FOC:

extern uz_FOC* FOC_dq;
extern struct uz_FOC_config config_FOC;


float error_z1z2_s[2];
float error_z1z2_n[2];

float dq_error[2];

float xy2Rout[2];
float xy6Rout[2];
float dq2Rout[2];
float dq12Rout[2];
float dq8Rout[2];
float z1z2_1Rout[2];
float z1z2_3Rout[2];
float z1z2_9Rout[2];
int ref_counter = 0;


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

uz_3ph_dq_t ref_dq_voltage_PI = {0};


extern uz_PI_Controller* PI_x_n;
extern uz_PI_Controller* PI_y_n;
extern uz_PI_Controller* PI_z1;
extern uz_PI_Controller* PI_z2;

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


float omega_el_rad_per_sec = 0.0f;
int mov_average_filter_length = 0;
int mov_average_filter_length1 = 0;
int mov_average_filter_length2 = 0;
int mov_average_filter_length3 = 0;
int mov_average_filter_length4 = 0;
int mov_average_filter_length5 = 0;

float movave_length = 0.0f;

extern struct uz_d_gan_inverter_t* gan_inverter_D3;
extern struct uz_d_gan_inverter_t* gan_inverter_D4;


bool dq_2 = false;
bool dq_8 = false;
bool dq_12 = false;
bool xy_n_PI = false;
bool xy_n = false;
bool xy_n_2 = false;
bool xy_n_6 = false;
bool y_off = false;
bool z1z2_1H = false;
bool z1z2_3H = false;
bool z1z2_9H = false;
bool z1z2_control = false;
bool xy_5_7 = false;


int opf_phases[6] = {0};
int num_OPF = 0;

bool no_reset = false;
int OPF_a1;
int OPF_b1;
int OPF_c1;
int OPF_a2;
int OPF_b2;
int OPF_c2;
int display_OPF;
float display_OPF_f;

//6-Phase FCS-MPC
extern uz_vsd_8_t* test_instance_vsd_8;
uz_6ph_abc_t a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation;
extern float a1_current_vsd_and_park_transformation;
extern float b1_current_vsd_and_park_transformation;
extern float c1_current_vsd_and_park_transformation;
extern float a2_current_vsd_and_park_transformation;
extern float b2_current_vsd_and_park_transformation;
extern float c2_current_vsd_and_park_transformation;
uz_3ph_dq_t dq_currents_vsd_and_park_transformation;
extern float d_current_vsd_and_park_transformation;
extern float q_current_vsd_and_park_transformation;


extern uz_phase_voltages_8_t* test_instance_phase_voltages_8;
extern float Index_phase_voltages_8;

extern uz_prediction_and_cost_function_8_t* test_instance_prediction_and_cost_function_8;
uz_6ph_idref_iqref_ixref_iyref_t updated_values={
	.id_ref=0.0f,
	.iq_ref=0.0f,
	.ix_ref=0.0f,
	.iy_ref=0.0f
 };
extern float Index_prediction_and_cost_function_8;

extern uz_delay_compensation_8_t* test_instance_delay_compensation_8;

extern uz_min_cost_function_8_t* test_instance_min_cost_function_8;
extern float Index_min_cost_function_8;


extern uz_switching_states_6Phase_8_t* test_instance_switching_states_6Phase_8;
extern float Index_switching_states_8;


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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////			6-Phase FCS-MPC					////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	  uz_prediction_and_cost_function_8_idref_iqref_ixref_iyref_update(test_instance_prediction_and_cost_function_8, updated_values);

    a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation = uz_vsd_8_get_ia1_ib1_ic1_ia2_ib2_ic2(test_instance_vsd_8);
    a1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.a1;
    b1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.b1;
    c1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.c1;
    a2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.a2;
    b2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.b2;
    c2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.c2;

    dq_currents_vsd_and_park_transformation = uz_vsd_and_park_8_transformation_6phase_get_id_iq(test_instance_vsd_8);
    d_current_vsd_and_park_transformation = dq_currents_vsd_and_park_transformation.d;
    q_current_vsd_and_park_transformation = dq_currents_vsd_and_park_transformation.q;

    Index_phase_voltages_8=uz_phase_voltages_8_read_Index_in(test_instance_phase_voltages_8);

    Index_prediction_and_cost_function_8=uz_prediction_and_cost_function_8_read_Index(test_instance_prediction_and_cost_function_8);

    Index_min_cost_function_8=uz_min_cost_function_8_read_Index_in(test_instance_min_cost_function_8);

    Index_switching_states_8=uz_switching_states_6Phase_8_read_Index_in(test_instance_switching_states_6Phase_8);

////////////////////////////////////////////////////////////////////////////////////////////////////
////			Phase current measurement and various transformations (dq, VSD)					////
////////////////////////////////////////////////////////////////////////////////////////////////////

	//assign ADC values to motor current variables

    m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4);
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3);
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2);
	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8);
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7);
	//m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6);

	m_6ph_abc_currents.c2 = - m_6ph_abc_currents.a1 - m_6ph_abc_currents.b1 - m_6ph_abc_currents.c1 -m_6ph_abc_currents.a2 - m_6ph_abc_currents.b2;

/*
    m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4)*1.0712 - 0.0487;
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3)*1.0556 + 0.0226;
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2)*1.0552 - 0.0176;
	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8)*1.0697 - 0.0055;
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7)*1.0564 + 0.0029;
	m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6)*1.0561 - 0.0266;
*/
/*
	//crude over current protection
	if(fabs(m_6ph_abc_currents.a1) > 30.0f || fabs(m_6ph_abc_currents.b1) > 30.0f || fabs(m_6ph_abc_currents.c1) > 30.0f || fabs(m_6ph_abc_currents.a2) > 30.0f || fabs(m_6ph_abc_currents.b2) > 30.0f || fabs(m_6ph_abc_currents.c2) > 30.0f){

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

		//write duty-cycles to 0 to disable inverter
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);	//D3 gan inv
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);	//D4 gan inv
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

		uz_assert(0);
	}
*/

    //crude over current protection
      if((fabs(a1_current_vsd_and_park_transformation) > 15.0f || fabs(b1_current_vsd_and_park_transformation) > 15.0f || fabs(c1_current_vsd_and_park_transformation) > 15.0f || fabs(a2_current_vsd_and_park_transformation) > 15.0f || fabs(b2_current_vsd_and_park_transformation) > 15.0f || fabs(c2_current_vsd_and_park_transformation) > 15.0f) && (fabs(updated_values.id_ref) > 15.0f || fabs(updated_values.iq_ref) > 15.0f || fabs(updated_values.ix_ref) > 15.0f || fabs(updated_values.iy_ref) > 15.0f)) {
      	uz_assert(0);
      	}


	//write phase currents into global_data-struct
	Global_Data.av.I_U = m_6ph_abc_currents.a1;
	Global_Data.av.I_V = m_6ph_abc_currents.b1;
	Global_Data.av.I_W = m_6ph_abc_currents.c1;
	Global_Data.av.I_X = m_6ph_abc_currents.a2;
	Global_Data.av.I_Y = m_6ph_abc_currents.b2;
	Global_Data.av.I_Z = m_6ph_abc_currents.c2;


	//Transform phase-currents to alpha-beta-x-y-z1-z2 and write to global_data-struct
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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////			Reference-value generation for current control									////
	////////////////////////////////////////////////////////////////////////////////////////////////////

		FD_indices.R1 = 0;//OPF_a1;
		FD_indices.R2 = 0;//OPF_b1;
		FD_indices.R3 = 0;//OPF_c1;
		FD_indices.R4 = 0;//OPF_a2;
		FD_indices.R5 = 0;//OPF_b2;
		FD_indices.R6 = 0;//OPF_c2;


		// Neutral Point configuration (N1N2 = 1 -> 1N with one neutral point, N1N2 = 2 -> 2N with two separate neutral points)
		N1N2 = 1;
		ML = 1;		//0 -> MT, 1 -> ML (selection of optimization)


		// get k-parameter from Look-up-table
		kparameter k_parameter;
		//k_parameter = get_k_parameter(opf_phases[0], opf_phases[1], opf_phases[2], num_OPF, N1N2, ML, &a, &error_opf);
		k_parameter = get_k_parameter(FD_indices,  N1N2, ML);

		// Reference Values for d and q current from reference value (Torque control)
		ref_dq0_currents.d = Global_Data.av.I_d_ref;
		ref_dq0_currents.q = Global_Data.av.I_q_ref;


		// enable, disable Controllers depending on OPFs


		ref_dq0_currents.d = Global_Data.av.I_d_ref;
		ref_dq0_currents.q = Global_Data.av.I_q_ref;


		// calculate reference values in alpha-beta-subspace
		ref_alphabeta_currents = uz_transformation_3ph_dq_to_alphabeta(ref_dq0_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

		// calculate reference values in x-y-subspace and zero-subspace
		// x_ref = k1 * i_alpha + k2 * i_beta
		// y_ref = k3 * i_alpha + k4 * i_beta
		// z1_ref = k5 * i_alpha + k6 * i_beta
		// z2_ref = k7 * i_alpha + k8 * i_beta
		ref_xy_currents[0] = k_parameter.k1 * ref_alphabeta_currents.alpha + k_parameter.k2 * ref_alphabeta_currents.beta;
		ref_xy_currents[1] = k_parameter.k3 * ref_alphabeta_currents.alpha + k_parameter.k4 * ref_alphabeta_currents.beta;
		ref_z1z2_currents[0] = k_parameter.k5 * ref_alphabeta_currents.alpha + k_parameter.k6 * ref_alphabeta_currents.beta;
		ref_z1z2_currents[1] = k_parameter.k7 * ref_alphabeta_currents.alpha + k_parameter.k8 * ref_alphabeta_currents.beta;


		// ref_xy_currents[0] = sin(7* (Global_Data.av.theta_elec + Global_Data.av.theta_offset));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////			Stuff for the inverter															////
	////////////////////////////////////////////////////////////////////////////////////////////////////


		// read data from gan inverters:
		uz_d_gan_inverter_update_states(gan_inverter_D3);
		uz_d_gan_inverter_update_states(gan_inverter_D4);

		Global_Data.objects.gan_inverter_outputs_D3 = uz_d_gan_inverter_get_outputs(gan_inverter_D3);
		Global_Data.objects.gan_inverter_outputs_D4 = uz_d_gan_inverter_get_outputs(gan_inverter_D4);


		platform_state_t current_state=ultrazohm_state_machine_get_state();

		//enable gan inverters if system enable
		if (current_state == idle_state || current_state == error_state) {
			//Set Data To UZ_D_GaN_Inverter
			uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_D_GAN_INVERTER_0_BASEADDR, false);
			uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_D_GAN_INVERTER_1_BASEADDR, false);
		} else if (current_state == running_state || current_state == control_state) { //Call this function only once. If there was an error, "enableSystem " must be reseted!
			//Set Data To UZ_D_GaN_Inverter
			uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_D_GAN_INVERTER_0_BASEADDR, true);
			uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_D_GAN_INVERTER_1_BASEADDR, true);
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

		theta_ = Global_Data.av.theta_elec + Global_Data.av.theta_offset;


		////////////////////////////////////////////////////////////////////////////////////////////////////
		////			Current control																	////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		    if (current_state==control_state)
		    {
		        // Start: Control algorithm - only if ultrazohm is in control state


		    	//6-Phase-FOC:

		 //------------------------------------dq-current-control----------------------------------//

				dq_error[0] = ref_dq0_currents.d - m_dq_currents.d;
				dq_error[1] = ref_dq0_currents.q - m_dq_currents.q;

		    	//Control
		    	// d-q-PI-Controller
		    	ref_dq_voltage = uz_FOC_sample(FOC_dq, ref_dq0_currents, m_dq_currents, Global_Data.av.U_ZK, omega_el_rad_per_sec);
		    	ref_dq_voltage_PI = ref_dq_voltage;

		    	// R-Controller: 2H d
				rc_2H_d->input.lower_limit = -8.0;
				rc_2H_d->input.upper_limit = 8.0;


				uz_resonantController_step(rc_2H_d, ref_dq0_currents.d, m_dq_currents.d, omega_el_rad_per_sec);
				dq2Rout[0] = rc_2H_d->output.out;
				if (dq_2){
					ref_dq_voltage.d = ref_dq_voltage.d + uz_resonantController_get_output(rc_2H_d);
				}


				// R-Controller: 2H q
				rc_2H_q->input.lower_limit = -8.0;	//4
				rc_2H_q->input.upper_limit = 8.0;	//4

				uz_resonantController_step(rc_2H_q, ref_dq0_currents.q, m_dq_currents.q, omega_el_rad_per_sec);
				dq2Rout[1] = rc_2H_q->output.out;
				if (dq_2){
					ref_dq_voltage.q = ref_dq_voltage.q + uz_resonantController_get_output(rc_2H_q);
				}


		    	// R-Controller: 12H d
				rc_12H_d->input.lower_limit = -4.0;
				rc_12H_d->input.upper_limit = 4.0;



				uz_resonantController_step(rc_12H_d, ref_dq0_currents.d, m_dq_currents.d, omega_el_rad_per_sec);
				dq12Rout[0] = rc_12H_d->output.out;
				if (dq_12){
					ref_dq_voltage.d = ref_dq_voltage.d + rc_12H_d->output.out;
				}

				// R-Controller: 12H q
				rc_12H_q->input.lower_limit = -4.0;
				rc_12H_q->input.upper_limit = 4.0;


				uz_resonantController_step(rc_12H_q, ref_dq0_currents.q, m_dq_currents.q, omega_el_rad_per_sec);
				dq12Rout[1] = rc_12H_q->output.out;
				if (dq_12){
					ref_dq_voltage.q = ref_dq_voltage.q + rc_12H_q->output.out;
				}



		    	//Transform back to phase-values:
		    	ref_alphabeta_voltage = uz_transformation_3ph_dq_to_alphabeta(ref_dq_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);


		    	// new control-parameters for dq-PI-Controller:
		    	uz_FOC_set_Kp_id(FOC_dq, Global_Data.av.kp_d);
		    	uz_FOC_set_Ki_id(FOC_dq, Global_Data.av.ki_d);
		    	uz_FOC_set_Kp_iq(FOC_dq, Global_Data.av.kp_q);
		    	uz_FOC_set_Ki_iq(FOC_dq, Global_Data.av.ki_q);



		//------------------------------------xy-current-control----------------------------------//



		    	ref_xy_voltage[0] = 0;
		    	ref_xy_voltage[1] = 0;


				//transform into antisynchronous frame:
				uz_inv_park_transform(m_xy_n_currents, m_xy_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);
				uz_inv_park_transform(ref_xy_n_currents, ref_xy_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);





				//PI-Controllers in antisynchronous frame
				ref_xy_n_voltage[0] = uz_PI_Controller_sample(PI_x_n, ref_xy_n_currents[0], m_xy_n_currents[0], false);
				ref_xy_n_voltage[1] = uz_PI_Controller_sample(PI_y_n, ref_xy_n_currents[1], m_xy_n_currents[1], false);

				// lineare Vorsteuerung:
				float L_y = 0.0000499; 	// in Henry
				float L_x = 0.0000557;
				ref_xy_n_voltage[0] += omega_el_rad_per_sec * L_y * m_xy_n_currents[1];
				ref_xy_n_voltage[1] += -omega_el_rad_per_sec * L_x * m_xy_n_currents[0];

				// ausschalten PI-Regler
				if(!xy_n_PI){
					ref_xy_n_voltage[0]=0;
					ref_xy_n_voltage[0]=0;
				}


				xy_error[0] = ref_xy_n_currents[0] - m_xy_n_currents[0];
				xy_error[1] = ref_xy_n_currents[1] - m_xy_n_currents[1];





				// Controller: 2H. x
				rc_2H_x->input.lower_limit = -4.0;	//4
				rc_2H_x->input.upper_limit = 4.0;


				uz_resonantController_step(rc_2H_x, ref_xy_n_currents[0], m_xy_n_currents[0], omega_el_rad_per_sec);
				xy2Rout[0] = rc_2H_x->output.out;
				if (xy_n_2){
					ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + rc_2H_x->output.out;
				}

				// Controller: 2H. y
				rc_2H_y->input.lower_limit = -4.0;	//4
				rc_2H_y->input.upper_limit = 4.0;


				uz_resonantController_step(rc_2H_y, ref_xy_n_currents[1], m_xy_n_currents[1], omega_el_rad_per_sec);
				xy2Rout[1] = rc_2H_y->output.out;
				if (xy_n_2){
					ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + rc_2H_y->output.out;
				}

				// R-Controller: 6H. x
				rc_6H_x->input.lower_limit = -4.0;
				rc_6H_x->input.upper_limit = 4.0;


				uz_resonantController_step(rc_6H_x, ref_xy_n_currents[0], m_xy_n_currents[0], omega_el_rad_per_sec);
				xy6Rout[0] = rc_6H_x->output.out;
				if (xy_n_6){
					ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + rc_6H_x->output.out;
				}

				if(y_off){
					ref_xy_n_voltage[1] = 0.0f;
				}

				// R-Controller: 6H. y
				rc_6H_y->input.lower_limit = -4.0;
				rc_6H_y->input.upper_limit = 4.0;


				uz_resonantController_step(rc_6H_y, ref_xy_n_currents[1], m_xy_n_currents[1], omega_el_rad_per_sec);
				xy6Rout[1] = rc_6H_y->output.out;
				if (xy_n_6){
					ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + rc_6H_y->output.out;
				}

				//Transform reference voltage from inverse rotating to stationary frame
				uz_park_transform(ref_xy_voltage_n, ref_xy_n_voltage, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

				// activate control in xy-subspace
		    	if(xy_n){
		    		ref_xy_voltage[0] = ref_xy_voltage_n[0];
		    		ref_xy_voltage[1] = ref_xy_voltage_n[1];
		    	}

		    	if(xy_5_7){

		    		uz_resonantController_step(rc_5H_x, ref_xy_currents[0], m_xy_currents[0], omega_el_rad_per_sec);
		    		uz_resonantController_step(rc_7H_x, ref_xy_currents[0], m_xy_currents[0], omega_el_rad_per_sec);
					uz_resonantController_step(rc_5H_y, ref_xy_currents[1], m_xy_currents[1], omega_el_rad_per_sec);
					uz_resonantController_step(rc_7H_y, ref_xy_currents[1], m_xy_currents[1], omega_el_rad_per_sec);

		    		ref_xy_voltage[0] += uz_resonantController_get_output(rc_5H_x);
		    		ref_xy_voltage[0] += uz_resonantController_get_output(rc_7H_x);
					ref_xy_voltage[1] += uz_resonantController_get_output(rc_5H_y);
					ref_xy_voltage[1] += uz_resonantController_get_output(rc_7H_y);
		    	}


		//------------------------------------z1z2-current-control----------------------------------//

		    	ref_z1z2_voltage[0] = 0;
		    	ref_z1z2_voltage[1] = 0;

				z1z2_error[0] = ref_z1z2_currents[0] - m_z1z2_currents[0];
				z1z2_error[1] = ref_z1z2_currents[1] - m_z1z2_currents[1];

				// P-Controller in z1z2-Frame
		    	ref_z1z2_voltage[0] = uz_PI_Controller_sample(PI_z1, ref_z1z2_currents[0], m_z1z2_currents[0], false);
				ref_z1z2_voltage[1] = uz_PI_Controller_sample(PI_z2, ref_z1z2_currents[1], m_z1z2_currents[1], false);



		    	//  R-Controller: 9H. z1
				rc_9H_z1->input.lower_limit = -4.0;
				rc_9H_z1->input.upper_limit = 4.0;

				uz_resonantController_step(rc_9H_z1, ref_z1z2_currents[0], m_z1z2_currents[0], omega_el_rad_per_sec);
				z1z2_9Rout[0] = rc_9H_z1->output.out;
				if (z1z2_9H){
					ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + rc_9H_z1->output.out;
				}

				//  R-Controller: 9H. z2
				rc_9H_z2->input.lower_limit = -4.0;
				rc_9H_z2->input.upper_limit = 4.0;


				uz_resonantController_step(rc_9H_z2, ref_z1z2_currents[1], m_z1z2_currents[1], omega_el_rad_per_sec);
				z1z2_9Rout[1] = rc_9H_z2->output.out;
				if(z1z2_9H){
					ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + rc_9H_z2->output.out;
				}



		    	//  R-Controller: 3H. z1
				rc_3H_z1->input.lower_limit = -4.0;
				rc_3H_z1->input.upper_limit = 4.0;



				uz_resonantController_step(rc_3H_z1, ref_z1z2_currents[0], m_z1z2_currents[0], omega_el_rad_per_sec);
				z1z2_3Rout[0] = rc_3H_z1->output.out;
				if (z1z2_3H){
					ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + rc_3H_z1->output.out;
				}

				//  R-Controller: 3H. z1
				rc_3H_z2->input.lower_limit = -4.0;
				rc_3H_z2->input.upper_limit = 4.0;


				uz_resonantController_step(rc_3H_z2, ref_z1z2_currents[1], m_z1z2_currents[1], omega_el_rad_per_sec);
				z1z2_3Rout[1] = rc_3H_z2->output.out;
				if(z1z2_3H){
					ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + rc_3H_z2->output.out;
				}


		    	//  R-Controller: 1H. z1
				rc_1H_z1->input.lower_limit = -4.0;
				rc_1H_z1->input.upper_limit = 4.0;


				uz_resonantController_step(rc_1H_z1, ref_z1z2_currents[0], m_z1z2_currents[0], omega_el_rad_per_sec);
				z1z2_1Rout[0] = rc_1H_z1->output.out;
				if (z1z2_1H){
					ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + rc_1H_z1->output.out;
				}


				//  R-Controller: 1H. z2
				rc_1H_z2->input.lower_limit = -4.0;
				rc_1H_z2->input.upper_limit = 4.0;


				uz_resonantController_step(rc_1H_z2, ref_z1z2_currents[1], m_z1z2_currents[1], omega_el_rad_per_sec);
				z1z2_1Rout[1] = rc_1H_z2->output.out;
				if(z1z2_1H){
					ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + rc_1H_z2->output.out;
				}

				// activate control in xy-subspace
		    	if(!z1z2_control){
		    		ref_z1z2_voltage[0] = 0;
		    		ref_z1z2_voltage[1] = 0;
		    	}

		//----------------combine reference values form alpha-beta, x-y and z1-z2 control----------------//


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

				dutyCycles_set2 = uz_FOC_generate_DutyCycles(ref_volage_phase_set1, Global_Data.av.U_ZK);
				dutyCycles_set1 = uz_FOC_generate_DutyCycles(ref_volage_phase_set2, Global_Data.av.U_ZK);

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
				uz_PI_Controller_reset(PI_x_n);
				uz_PI_Controller_reset(PI_y_n);
				uz_PI_Controller_reset(PI_z1);
				uz_PI_Controller_reset(PI_z2);

				uz_resonantController_reset(rc_2H_x);
		        uz_resonantController_reset(rc_2H_y);
		        uz_resonantController_reset(rc_6H_x);
		        uz_resonantController_reset(rc_6H_y);
		        uz_resonantController_reset(rc_2H_d);
		        uz_resonantController_reset(rc_2H_q);
		        uz_resonantController_reset(rc_8H_d);
		        uz_resonantController_reset(rc_8H_q);
		        uz_resonantController_reset(rc_12H_d);
		        uz_resonantController_reset(rc_12H_q);

		        uz_resonantController_reset(rc_1H_z1);
		        uz_resonantController_reset(rc_1H_z2);
		        uz_resonantController_reset(rc_3H_z1);
		        uz_resonantController_reset(rc_3H_z2);
		        uz_resonantController_reset(rc_9H_z1);
		        uz_resonantController_reset(rc_9H_z2);

		    }




		    // dutzy cycles:
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
