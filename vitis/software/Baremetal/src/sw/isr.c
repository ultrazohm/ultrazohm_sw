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
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_Transformation/uz_Transformation.h"


#define MAX_PHASE_CURRENT_AMP  13.0f


//
neutral_point_configuration N1N2 = N2;
ML_MT_optimization MLMT = MT;		//0 -> MT, 1 -> ML (selection of optimization)



// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

// Data for determination of mechanical resolver angle
float theta_mech_old=0.0f;
int32_t cnt = 0U;
bool cnt_reset = 0;
float cnt_float=0.0f;
float cnt_reset_float=0.0f;
float theta_mech_calc_from_resolver = 0.0f;
float theta_m_max = 0.0f;
float theta_m_min = 0.0f;

uz_6ph_abc_t six_ph_currents = {0.0f};
uz_6ph_alphabeta_t six_ph_alphabeta = {0.0f};
uz_3ph_alphabeta_t three_ph_alphabeta = {0.0f};
uz_3ph_dq_t rotating_dq = {0};

uz_3ph_dq_t i_dq_ref = {0.0f};
uz_3ph_dq_t i_dq_actual = {0.0f};
uz_3ph_dq_t u_dq_ref = {0.0f};
uz_3ph_dq_t u_dq_ref_dq = {0.0f};



uz_3ph_alphabeta_t alphabeta_ref_volts = {0.0f};
uz_6ph_alphabeta_t vsd_ref_volts = {0.0f};
uz_6ph_abc_t phase_ref_volts = {0.0f};

uz_3ph_abc_t input1 = {0.0f};
uz_3ph_abc_t input2 = {0.0f};
struct uz_DutyCycle_t output1 = {0};
struct uz_DutyCycle_t output2 = {0};

uz_3ph_dq_t speed_ctrl_ref_currents = {0.0f};

#define PHASE_CURRENT_CONV	37.735/7.0f/1.19f
#define DC_VOLT_CONV		250
#define DC_VOLT_OFF			250

const struct uz_PMSM_t config_PMSM1 = {
	.R_ph_Ohm = 0.2f,
   .Ld_Henry = 0.0001f,
   .Lq_Henry = 0.0001f,
   .Psi_PM_Vs = 0.008f,
   .polePairs = 5.0f,
   .I_max_Ampere = 10.0f
 };//these parameters are only needed if linear decoupling is selected

/*---------------------------------------------*/


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

float singleIndex_FD_R = 0.0f;

uz_6phFD_indices R_FD = {0};
uz_6phFD_indices R_FD_Filt = {0};
uz_6phFD_indices R_FD_Filt_hyst = {0};
uz_6phFD_indices R_FD_eval = {0};

uz_6phFD_indices FD_indices = {0};



extern uz_resonantController_t* rc_2H_x;
extern uz_resonantController_t* rc_2H_y;
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

extern uz_movingAverageFilter_t* movAvFilter_temp1;
extern uz_movingAverageFilter_t* movAvFilter_temp2;
extern uz_movingAverageFilter_t* movAvFilter_temp3;
extern uz_movingAverageFilter_t* movAvFilter_temp4;
extern uz_movingAverageFilter_t* movAvFilter_temp5;

//parameters for 6ph FOC:

extern uz_PI_Controller* PI_x_n;
extern uz_PI_Controller* PI_y_n;
extern uz_PI_Controller* PI_z1;
extern uz_PI_Controller* PI_z2;

float m_xy_currents[2];
float ref_xy_currents[2];

float m_xy_n_currents[2];
float ref_xy_n_currents[2];

float m_z1z2_currents[2];
float ref_z1z2_currents[2];

float ref_xy_voltage[2];
float xy_error[2];
float ref_xy_n_voltage[2];
float ref_xy_voltage_n[2];

float ref_z1z2_voltage[2];

uz_6ph_abc_t ref_6ph_abc_voltage = {0};
uz_6ph_alphabeta_t ref_6ph_alphabeta_voltage = {0};

uz_3ph_abc_t ref_volage_phase_set1 = {0};
uz_3ph_abc_t ref_volage_phase_set2 = {0};

uz_3ph_dq_t ref_dq0_currents = {0};
uz_3ph_dq_t ref_dq0_n_currents = {0};
uz_3ph_alphabeta_t ref_alphabeta_currents = {0};

float omega_el_rad_per_sec = 0.0f;
int mov_average_filter_length = 0;
int mov_average_filter_length1 = 0;
int mov_average_filter_length2 = 0;
int mov_average_filter_length3 = 0;
int mov_average_filter_length4 = 0;
int mov_average_filter_length5 = 0;

bool dq_2 = true;
bool dq_8 = false;
bool dq_12 = false;
bool xy_n_PI = true;
bool xy_n = true;
bool xy_n_2 = true;
bool xy_n_6 = false;
bool y_off = true;
bool z1z2_1H = false;
bool z1z2_3H = false;
bool z1z2_9H = false;
bool z1z2_control = false;
bool z2_control_off = false;

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
    update_position_and_speed_of_resolverIP(&Global_Data);
    //update_position_of_resolverIP(&Global_Data);
    //update_speed_of_resolverIP(&Global_Data);
    //readRegister_of_resolverIP(&Global_Data);

    // convert ADC readings to currents in Amps
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c1 = -1.0f * Global_Data.aa.A1.me.ADC_B6 * PHASE_CURRENT_CONV;
    Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c2 = -1.0f * Global_Data.aa.A2.me.ADC_B6 * PHASE_CURRENT_CONV;
    // convert ADC readings to dc link voltages
    Global_Data.av.U_ZK = -1.0f * Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV - DC_VOLT_OFF;
    Global_Data.av.U_ZK2 = -1.0f * Global_Data.aa.A2.me.ADC_B8 * DC_VOLT_CONV - DC_VOLT_OFF;

    // filter values
    Global_Data.av.i_a1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a1, Global_Data.av.i_a1);
    Global_Data.av.i_b1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b1, Global_Data.av.i_b1);
    Global_Data.av.i_c1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c1, Global_Data.av.i_c1);
    Global_Data.av.i_a2_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a2, Global_Data.av.i_a2);
    Global_Data.av.i_b2_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b2, Global_Data.av.i_b2);
    Global_Data.av.i_c2_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c2, Global_Data.av.i_c2);
    Global_Data.av.U_ZK_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_dc, Global_Data.av.U_ZK);
    Global_Data.av.rpm_ref_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_rpm_ref, Global_Data.av.rpm_ref);
    // theta offset and scaling to el. angle
    Global_Data.av.theta_m_offset_comp = theta_mech_calc_from_resolver - Global_Data.av.theta_offset;
    Global_Data.av.theta_elec = Global_Data.av.theta_m_offset_comp * Global_Data.av.polepairs;

    // transform phase currents
    six_ph_currents.a1 = Global_Data.av.i_a1_filt;
    six_ph_currents.b1 = Global_Data.av.i_b1_filt;
    six_ph_currents.c1 = Global_Data.av.i_c1_filt;
    six_ph_currents.a2 = Global_Data.av.i_a2_filt;
    six_ph_currents.b2 = Global_Data.av.i_b2_filt;
    six_ph_currents.c2 = Global_Data.av.i_c2_filt;
    six_ph_alphabeta = uz_transformation_asym30deg_6ph_abc_to_alphabeta(six_ph_currents);


    m_xy_currents[0] = six_ph_alphabeta.x;
    m_xy_currents[1] = six_ph_alphabeta.y;

    m_z1z2_currents[0] = six_ph_alphabeta.z1;
    m_z1z2_currents[1] = six_ph_alphabeta.z2;


    three_ph_alphabeta.alpha = six_ph_alphabeta.alpha;
    three_ph_alphabeta.beta = six_ph_alphabeta.beta;
    Global_Data.av.i_alpha = three_ph_alphabeta.alpha;
    Global_Data.av.i_beta = three_ph_alphabeta.beta;
    Global_Data.av.i_x = six_ph_alphabeta.x;
    Global_Data.av.i_y = six_ph_alphabeta.y;
    Global_Data.av.i_z1 = six_ph_alphabeta.z1;
    Global_Data.av.i_z2 = six_ph_alphabeta.z2;
    rotating_dq = uz_transformation_3ph_alphabeta_to_dq(three_ph_alphabeta, Global_Data.av.theta_elec);
    Global_Data.av.i_d = rotating_dq.d;
    Global_Data.av.i_q = rotating_dq.q;

    i_dq_actual.d = Global_Data.av.i_d;
    i_dq_actual.q = Global_Data.av.i_q;

	i_dq_ref.d = Global_Data.av.i_d_ref;
	i_dq_ref.q = Global_Data.av.i_q_ref;

	if(fabs(six_ph_currents.a1) > MAX_PHASE_CURRENT_AMP || fabs(six_ph_currents.b1) > MAX_PHASE_CURRENT_AMP || fabs(six_ph_currents.c1) > MAX_PHASE_CURRENT_AMP ||
	   fabs(six_ph_currents.a2) > MAX_PHASE_CURRENT_AMP || fabs(six_ph_currents.b2) > MAX_PHASE_CURRENT_AMP || fabs(six_ph_currents.c2) > MAX_PHASE_CURRENT_AMP) {

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


////////////////////////////////////////////////////////////////////////////////////////////////////
////			Open Phase Fault Detection														////
////////////////////////////////////////////////////////////////////////////////////////////////////

	   //VSD-fault-detection
			// calculation of fault indices
	    R_FD = uz_vsd_opf_6ph_faultdetection(six_ph_alphabeta);

	    Global_Data.av.R_a1 = R_FD.R1;
	    Global_Data.av.R_b1 = R_FD.R2;
	    Global_Data.av.R_c1 = R_FD.R3;
	    Global_Data.av.R_a2 = R_FD.R4;
	    Global_Data.av.R_b2 = R_FD.R5;
	    Global_Data.av.R_c2 = R_FD.R6;

	    	// hysteresis filter
	    R_FD_Filt_hyst = uz_vsd_fd_hysteresis_filter(R_FD, 0.9, 1.1);

	    Global_Data.av.R_h_a1 = R_FD_Filt_hyst.R1;
	    Global_Data.av.R_h_b1 = R_FD_Filt_hyst.R2;
	    Global_Data.av.R_h_c1 = R_FD_Filt_hyst.R3;
	    Global_Data.av.R_h_a2 = R_FD_Filt_hyst.R4;
	    Global_Data.av.R_h_b2 = R_FD_Filt_hyst.R5;
	    Global_Data.av.R_h_c2 = R_FD_Filt_hyst.R6;

	    // moving average filter for fault indices:

	    //calculate optimal filterlength from omega_el
	    float k = 0.4;	//portion of one electric period

	    if (omega_el_rad_per_sec != 0){
	    	mov_average_filter_length = k * 10000 * 2 * M_PI / abs(omega_el_rad_per_sec);
	    }else{
	    	mov_average_filter_length = 1;
	    }
	    mov_average_filter_length = mov_average_filter_length/2;

	    if(mov_average_filter_length == 0){
	    	mov_average_filter_length = 1;
	    }
	    if(mov_average_filter_length > 499){
	    	mov_average_filter_length = 499;
	    }

	    //Splitted the movAverageFiltering into two sets, each executed every other cycle (10kHz reduced to 5kHz) to save computations


	if(toggle == 0){
		uz_movingAverageFilter_set_filterLength(movAvFilter_R1, mov_average_filter_length);
		uz_movingAverageFilter_set_filterLength(movAvFilter_R2, mov_average_filter_length);
		uz_movingAverageFilter_set_filterLength(movAvFilter_R3, mov_average_filter_length);

		R_FD_Filt.R1 = uz_movingAverageFilter_sample_variable_length(movAvFilter_R1, R_FD_Filt_hyst.R1);
		R_FD_Filt.R2 = uz_movingAverageFilter_sample_variable_length(movAvFilter_R2, R_FD_Filt_hyst.R2);
		R_FD_Filt.R3 = uz_movingAverageFilter_sample_variable_length(movAvFilter_R3, R_FD_Filt_hyst.R3);
	    toggle = 1;
	}else{

		uz_movingAverageFilter_set_filterLength(movAvFilter_R4, mov_average_filter_length);
		uz_movingAverageFilter_set_filterLength(movAvFilter_R5, mov_average_filter_length);
		uz_movingAverageFilter_set_filterLength(movAvFilter_R6, mov_average_filter_length);

		R_FD_Filt.R4 = uz_movingAverageFilter_sample_variable_length(movAvFilter_R4, R_FD_Filt_hyst.R4);
		R_FD_Filt.R5 = uz_movingAverageFilter_sample_variable_length(movAvFilter_R5, R_FD_Filt_hyst.R5);
		R_FD_Filt.R6 = uz_movingAverageFilter_sample_variable_length(movAvFilter_R6, R_FD_Filt_hyst.R6);
		    toggle = 0;
	}

	Global_Data.av.R_avg_a1 = R_FD_Filt.R1;
	Global_Data.av.R_avg_b1 = R_FD_Filt.R2;
	Global_Data.av.R_avg_c1 = R_FD_Filt.R3;
	Global_Data.av.R_avg_a2 = R_FD_Filt.R4;
	Global_Data.av.R_avg_b2 = R_FD_Filt.R5;
	Global_Data.av.R_avg_c2 = R_FD_Filt.R6;

		R_FD_eval = uz_vsd_fd_evaluation(R_FD_Filt, 0.4f);


////////////////////////////////////////////////////////////////////////////////////////////////////
////			Reference-value generation for current control									////
////////////////////////////////////////////////////////////////////////////////////////////////////

		// ML_MT-OPF-Control get Reference-Values for Control:

		// no reset open phase detection -> if activated a detected fault will not be reset if corresponding faultindex is below threshold
		if(no_reset){
			if(!OPF_a1){
				OPF_a1 = (int)R_FD_eval.R1;
			}
			if(!OPF_b1){
				OPF_b1 = (int)R_FD_eval.R2;
			}
			if(!OPF_c1){
				OPF_c1 = (int)R_FD_eval.R3;
			}
			if(!OPF_a2){
				OPF_a2 = (int)R_FD_eval.R4;
			}
			if(!OPF_b2){
				OPF_b2 = (int)R_FD_eval.R5;
			}
			if(!OPF_c2){
				OPF_c2 = (int)R_FD_eval.R6;
			}
		}
		else{
			OPF_a1 = (int)R_FD_eval.R1;
			OPF_b1 = (int)R_FD_eval.R2;
			OPF_c1 = (int)R_FD_eval.R3;
			OPF_a2 = (int)R_FD_eval.R4;
			OPF_b2 = (int)R_FD_eval.R5;
			OPF_c2 = (int)R_FD_eval.R6;
		}

		// get number of faulted phases
		// write phase-number of faulted phases into array opf_phases in increasing order (a1-b1-c1-a2-b2-c2)

		num_OPF = 0;

		if (OPF_a1 == 1){
			opf_phases[num_OPF] = 1;
			num_OPF += 1;
		}
		if (OPF_b1 == 1){
			opf_phases[num_OPF] = 2;
			num_OPF += 1;
		}
		if (OPF_c1 == 1){
			opf_phases[num_OPF] = 3;
			num_OPF += 1;
		}
		if (OPF_a2 == 1){
			opf_phases[num_OPF] = 4;
			num_OPF += 1;
		}
		if (OPF_b2 == 1){
			opf_phases[num_OPF] = 5;
			num_OPF += 1;
		}
		if (OPF_c2 == 1){
			opf_phases[num_OPF] = 6;
			num_OPF += 1;
		}

		//OPF display as integer. :
		display_OPF = 0;
		display_OPF += 100000*OPF_a1;
		display_OPF += 10000*OPF_b1;
		display_OPF += 1000*OPF_c1;
		display_OPF += 100*OPF_a2;
		display_OPF += 10*OPF_b2;
		display_OPF += 1*OPF_c2;
		display_OPF_f = (float)display_OPF;


		FD_indices.R1 = OPF_a1;
		FD_indices.R2 = OPF_b1;
		FD_indices.R3 = OPF_c1;
		FD_indices.R4 = OPF_a2;
		FD_indices.R5 = OPF_b2;
		FD_indices.R6 = OPF_c2;

		Global_Data.av.FD_a1 = FD_indices.R1;
		Global_Data.av.FD_b1 = FD_indices.R2;
		Global_Data.av.FD_c1 = FD_indices.R3;
		Global_Data.av.FD_a2 = FD_indices.R4;
		Global_Data.av.FD_b2 = FD_indices.R5;
		Global_Data.av.FD_c2 = FD_indices.R6;


		// Neutral Point configuration (N1N2 = 1 -> 1N with one neutral point, N1N2 = 2 -> 2N with two separate neutral points)


		// get k-parameter from Look-up-table
		uz_6ph_MLMT_kparameter k_parameter;
		//k_parameter = get_k_parameter(opf_phases[0], opf_phases[1], opf_phases[2], num_OPF, N1N2, ML, &a, &error_opf);
		k_parameter = get_k_parameter(FD_indices,  N1N2, MLMT);

		// Reference Values for d and q current from reference value (Torque control)
		ref_dq0_currents.d = Global_Data.av.i_d_ref;
		ref_dq0_currents.q = Global_Data.av.i_q_ref;


		// enable, disable Controllers depending on OPFs


	dq_2 = true;
	//dq_12 = true;
	xy_n_PI = true;
	xy_n = true;
	xy_n_2 = true;
	xy_n_6 = true;
	y_off = false;
	z1z2_1H = true;
	z1z2_3H = true;
	z1z2_9H = true;
	z1z2_control = true;




	if(N1N2 == 1){
		if(num_OPF == 1){
			z1z2_1H = false;
		}
		else if(num_OPF == 2){
			z1z2_1H = false;
			y_off = true;
		}
		else if(num_OPF == 3){
			z1z2_1H = false;
			xy_n_2 = false;
			xy_n_PI = false;
		}
	}
	else if((N1N2 ==2) && (ML == 1)){
		if(num_OPF == 1){
			z1z2_1H = false;
			y_off = true;
		}
		else if(num_OPF > 1){
			z1z2_1H = false;
			 xy_n_2 = false;
			 xy_n_PI = false;
		}
	}
	else{
		if(num_OPF > 0){
			z1z2_1H = false;
		}
	}



		ref_dq0_currents.d = i_dq_ref.d;
		ref_dq0_currents.q = i_dq_ref.q;


		// calculate reference values in alpha-beta-subspace
		ref_alphabeta_currents = uz_transformation_3ph_dq_to_alphabeta(ref_dq0_currents, Global_Data.av.theta_elec);

		// calculate reference values in x-y-subspace and zero-subspace
		// x_ref = k1 * i_alpha + k2 * i_beta
		// y_ref = k3 * i_alpha + k4 * i_beta
		// z1_ref = k5 * i_alpha + k6 * i_beta
		// z2_ref = k7 * i_alpha + k8 * i_beta
		ref_xy_currents[0] = k_parameter.k1 * ref_alphabeta_currents.alpha + k_parameter.k2 * ref_alphabeta_currents.beta;
		ref_xy_currents[1] = k_parameter.k3 * ref_alphabeta_currents.alpha + k_parameter.k4 * ref_alphabeta_currents.beta;
		ref_z1z2_currents[0] = k_parameter.k5 * ref_alphabeta_currents.alpha + k_parameter.k6 * ref_alphabeta_currents.beta;
		ref_z1z2_currents[1] = k_parameter.k7 * ref_alphabeta_currents.alpha + k_parameter.k8 * ref_alphabeta_currents.beta;

		Global_Data.av.i_alpha_ref = ref_alphabeta_currents.alpha;
		Global_Data.av.i_beta_ref = ref_alphabeta_currents.beta;
		Global_Data.av.i_x_ref = ref_xy_currents[0];
		Global_Data.av.i_y_ref = ref_xy_currents[1];
		Global_Data.av.i_z1_ref = ref_z1z2_currents[0];
		Global_Data.av.i_z2_ref = ref_z1z2_currents[1];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
//    	speed_ctrl_ref_currents = uz_SpeedControl_sample(Global_Data.objects.foc_speed, Global_Data.av.mechanicalRotorSpeed*3.1415/30.0f*Global_Data.av.polepairs,Global_Data.av.rpm_ref_filt, Global_Data.av.U_ZK_filt, Global_Data.av.i_d_ref, config_PMSM1, false);

    	omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed*3.1415/30.0f*Global_Data.av.polepairs;

// dq-control: --------------------------------------------------------------------------------------------------------

    	u_dq_ref = uz_FOC_sample(Global_Data.objects.foc_current, i_dq_ref, i_dq_actual, Global_Data.av.U_ZK_filt, Global_Data.av.mechanicalRotorSpeed*3.1415/30.0f*Global_Data.av.polepairs);
    	u_dq_ref_dq = u_dq_ref;
    	u_dq_ref_dq.d = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_multipurpose, u_dq_ref.d);

    	Global_Data.av.u_d_ref = u_dq_ref.d;
    	Global_Data.av.u_q_ref = u_dq_ref.q;


		if (dq_2){
			u_dq_ref.d = u_dq_ref.d + uz_resonantController_step(rc_2H_d, i_dq_ref.d, i_dq_actual.d, omega_el_rad_per_sec);
			u_dq_ref.q = u_dq_ref.q + uz_resonantController_step(rc_2H_q, i_dq_ref.q, i_dq_actual.q, omega_el_rad_per_sec);
		}

		if (dq_12){
			u_dq_ref.d = u_dq_ref.d + uz_resonantController_step(rc_12H_d, i_dq_ref.d, i_dq_actual.d, omega_el_rad_per_sec);
			u_dq_ref.q = u_dq_ref.q + uz_resonantController_step(rc_12H_d, i_dq_ref.q, i_dq_actual.q, omega_el_rad_per_sec);
		}

    	alphabeta_ref_volts = uz_transformation_3ph_dq_to_alphabeta(u_dq_ref, Global_Data.av.theta_elec);
    	vsd_ref_volts.alpha = alphabeta_ref_volts.alpha;
    	vsd_ref_volts.beta = alphabeta_ref_volts.beta;


// xy-control: --------------------------------------------------------------------------------------------------------

    	ref_xy_voltage[0] = 0;
        ref_xy_voltage[1] = 0;

        xy_error[0] = ref_xy_currents[0] - m_xy_currents[0];
        xy_error[1] = ref_xy_currents[1] - m_xy_currents[1];

        //transform into antisynchronous frame:
    	uz_inv_park_transform(m_xy_n_currents, m_xy_currents, Global_Data.av.theta_elec);
    	uz_inv_park_transform(ref_xy_n_currents, ref_xy_currents, Global_Data.av.theta_elec);

		//PI-Controllers in antisynchronous frame
		ref_xy_n_voltage[0] = uz_PI_Controller_sample(PI_x_n, ref_xy_n_currents[0], m_xy_n_currents[0], false);
		ref_xy_n_voltage[1] = uz_PI_Controller_sample(PI_y_n, ref_xy_n_currents[1], m_xy_n_currents[1], false);

		// lineare Vorsteuerung:
		//float L_y = 0.0000499; 	// in Henry
		//float L_x = 0.0000557;
		//ref_xy_n_voltage[0] += omega_el_rad_per_sec * L_y * m_xy_n_currents[1];
		//ref_xy_n_voltage[1] += -omega_el_rad_per_sec * L_x * m_xy_n_currents[0];

		// disable PI-Controller
		if(!xy_n_PI){
			ref_xy_n_voltage[0]=0;
			ref_xy_n_voltage[0]=0;
		}
		// disable y-Control
		if(y_off){
			ref_xy_n_voltage[1] = 0.0f;
		}

	// Resonant-Controllers:

		// Controller: 2H.
		if (xy_n_2){
			ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + uz_resonantController_step(rc_2H_x, ref_xy_n_currents[0], m_xy_n_currents[0], omega_el_rad_per_sec);
			ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + uz_resonantController_step(rc_2H_y, ref_xy_n_currents[1], m_xy_n_currents[1], omega_el_rad_per_sec);
		}

		// R-Controller: 6H.
		if (xy_n_6){
			ref_xy_n_voltage[0] = ref_xy_n_voltage[0] + uz_resonantController_step(rc_6H_x, ref_xy_n_currents[0], m_xy_n_currents[0], omega_el_rad_per_sec);
			ref_xy_n_voltage[1] = ref_xy_n_voltage[1] + uz_resonantController_step(rc_6H_y, ref_xy_n_currents[1], m_xy_n_currents[1], omega_el_rad_per_sec);
		}

		//Transform reference voltage from inverse rotating to stationary frame
		uz_park_transform(ref_xy_voltage_n, ref_xy_n_voltage, Global_Data.av.theta_elec);

		// activate control in xy-subspace
		if(xy_n){
			ref_xy_voltage[0] = ref_xy_voltage_n[0];
			ref_xy_voltage[1] = ref_xy_voltage_n[1];
		}

		vsd_ref_volts.x = ref_xy_voltage[0];
		vsd_ref_volts.y = ref_xy_voltage[1];

// z1z2-control: ------------------------------------------------------------------------------------------------------

        	ref_z1z2_voltage[0] = 0;
        	ref_z1z2_voltage[1] = 0;

    		// P-Controller in z1z2-Frame
        	ref_z1z2_voltage[0] = uz_PI_Controller_sample(PI_z1, ref_z1z2_currents[0], m_z1z2_currents[0], false);
    		ref_z1z2_voltage[1] = uz_PI_Controller_sample(PI_z2, ref_z1z2_currents[1], m_z1z2_currents[1], false);

        	//  R-Controller: 9H. z1z2
    		if (z1z2_9H){
    			ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + uz_resonantController_step(rc_9H_z1, ref_z1z2_currents[0], m_z1z2_currents[0], omega_el_rad_per_sec);
    			ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + uz_resonantController_step(rc_9H_z2, ref_z1z2_currents[1], m_z1z2_currents[1], omega_el_rad_per_sec);
    		}

        	//  R-Controller: 3H. z1
    		if (z1z2_3H){
    			ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + uz_resonantController_step(rc_3H_z1, ref_z1z2_currents[0], m_z1z2_currents[0], omega_el_rad_per_sec);
    			ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + uz_resonantController_step(rc_3H_z2, ref_z1z2_currents[1], m_z1z2_currents[1], omega_el_rad_per_sec);
    		}

        	//  R-Controller: 1H. z1
    		if (z1z2_1H){
    			ref_z1z2_voltage[0] = ref_z1z2_voltage[0] + uz_resonantController_step(rc_1H_z1, ref_z1z2_currents[0], m_z1z2_currents[0], omega_el_rad_per_sec);
    			ref_z1z2_voltage[1] = ref_z1z2_voltage[1] + uz_resonantController_step(rc_1H_z2, ref_z1z2_currents[1], m_z1z2_currents[1], omega_el_rad_per_sec);
    		}

    		// activate control in z1z2-subspace
        	if(!z1z2_control){
        		ref_z1z2_voltage[0] = 0;
        		ref_z1z2_voltage[1] = 0;
        	}
        	// disable z2-control
        	if(z2_control_off){
        		ref_z1z2_voltage[1] = 0;
        	}

        	vsd_ref_volts.z1 = ref_z1z2_voltage[0];
        	vsd_ref_volts.z2 = ref_z1z2_voltage[1];

// --------------------------------------------------------------------------------------------------------------------

    		Global_Data.av.u_alpha_ref = vsd_ref_volts.alpha;
    		Global_Data.av.u_beta_ref = vsd_ref_volts.beta;
    		Global_Data.av.u_x_ref = vsd_ref_volts.x;
    		Global_Data.av.u_y_ref = vsd_ref_volts.y;
    		Global_Data.av.u_z1_ref = vsd_ref_volts.z1;
    		Global_Data.av.u_z2_ref = vsd_ref_volts.z2;


    	phase_ref_volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(vsd_ref_volts);

    	input1.a = phase_ref_volts.a1;
    	input1.b = phase_ref_volts.b1;
    	input1.c = phase_ref_volts.c1;
    	input2.a = phase_ref_volts.a2;
    	input2.b = phase_ref_volts.b2;
    	input2.c = phase_ref_volts.c2;

    	output1 = uz_FOC_generate_DutyCycles(input1, Global_Data.av.U_ZK_filt);
    	output2 = uz_FOC_generate_DutyCycles(input2, Global_Data.av.U_ZK_filt);

    	Global_Data.rasv.halfBridge1DutyCycle = output1.DutyCycle_U;
    	Global_Data.rasv.halfBridge2DutyCycle = output1.DutyCycle_V;
    	Global_Data.rasv.halfBridge3DutyCycle = output1.DutyCycle_W;
    	Global_Data.rasv.halfBridge4DutyCycle = output2.DutyCycle_U;
    	Global_Data.rasv.halfBridge5DutyCycle = output2.DutyCycle_V;
    	Global_Data.rasv.halfBridge6DutyCycle = output2.DutyCycle_W;

    }
    else{
    	// Reset Controllers if control-state is not active
    	uz_FOC_reset(Global_Data.objects.foc_current);
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
        uz_resonantController_reset(rc_12H_d);
        uz_resonantController_reset(rc_12H_q);

        uz_resonantController_reset(rc_1H_z1);
        uz_resonantController_reset(rc_1H_z2);
        uz_resonantController_reset(rc_3H_z1);
        uz_resonantController_reset(rc_3H_z2);
        uz_resonantController_reset(rc_9H_z1);
        uz_resonantController_reset(rc_9H_z2);


    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;

        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

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

    // Determine mechanical angle of resolver
    if(theta_mech_old-Global_Data.av.theta_mech > 4.0f) {
    	cnt++;
    	cnt_float=(float)cnt;
    } else if (theta_mech_old-Global_Data.av.theta_mech < -4.0f) {
    	cnt--;
    	cnt_float=(float)cnt;
    }

    if(cnt > 1 || cnt < -1) {
    	cnt = 0;
    	cnt_float = 0.0f;
    }

    if(cnt_reset == 1) {
    	cnt = 0;
    	cnt_float = 0;
    	cnt_reset = 0;
    	cnt_reset_float=0;
    }


    if(cnt >= 0){
    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech/uz_resolverIP_getResolverPolePairs(Global_Data.objects.resolver_IP) + cnt*2*3.14159265358979323846/2.0f;
    } else {
    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech/2.0f + (2+cnt)*2*3.14159265358979323846/2.0f;
    }

    theta_mech_old = Global_Data.av.theta_mech;

    if (Global_Data.av.theta_mech <= theta_m_min) {
    	theta_m_min = Global_Data.av.theta_mech;
    }

    if (Global_Data.av.theta_mech >= theta_m_max) {
    	theta_m_max = Global_Data.av.theta_mech;
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
