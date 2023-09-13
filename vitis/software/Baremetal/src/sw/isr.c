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

// ======================= PMSM 1 ======================= //
// --------------- Pointers to instances ---------------- //
extern struct uz_PMSM_t config_PMSM_1;
extern uz_SpeedControl_t* SC_instance_1;
extern uz_SetPoint_t* SP_instance_1;
extern uz_CurrentControl_t* CC_instance_1;
extern uz_CurrentControl_t* CC_instance_5th_1;
extern uz_CurrentControl_t* CC_instance_7th_1;
extern uz_subspace_resonant_control* RC_instance_5th_1;
extern uz_subspace_resonant_control* RC_instance_7th_1;
extern uz_subspace_resonant_control* RC_instance_6th_1;
extern uz_subspace_resonant_control* RC_instance_12th_1;
extern uz_IIR_Filter_t* BP_instance_5th_a_1;
extern uz_IIR_Filter_t* BP_instance_5th_b_1;
extern uz_IIR_Filter_t* BP_instance_5th_c_1;
extern uz_IIR_Filter_t* BP_instance_7th_a_1;
extern uz_IIR_Filter_t* BP_instance_7th_b_1;
extern uz_IIR_Filter_t* BP_instance_7th_c_1;
extern uz_IIR_Filter_t* LP_instance_5th_d_1;
extern uz_IIR_Filter_t* LP_instance_5th_q_1;
extern uz_IIR_Filter_t* LP_instance_7th_d_1;
extern uz_IIR_Filter_t* LP_instance_7th_q_1;
extern uz_encoder_offset_estimation_t* encoder_offset_obj_1;
extern uz_wavegen_chirp* chirp_instance;

// ---------------- Inverter Measurement ---------------- //
struct uz_3ph_abc_t v_abc_Volts_1				= {0};
float v_DC_Volts_1 								= 24.0f;
struct uz_3ph_abc_t i_abc_Amps_1 				= {0};
float i_DC_Amps_1 								= 0.0f;

// --------- Field Oriented Control and Signals --------- //
float omega_m_rad_per_sec_1 					= 0.0f;
float omega_el_rad_per_sec_1 					= 0.0f;
float theta_el_rad_1 							= 0.0f;
float theta_el_offset_1 						= 1.1f;
struct uz_3ph_dq_t 	i_dq_Amps_1 				= {0};
struct uz_3ph_alphabeta_t i_alphabeta_Amps_1 	= {0};
struct uz_3ph_dq_t 	v_dq_Volts_1 				= {0};
float n_ref_rpm_1 								= 0.0f;
float M_ref_Nm_1 								= 0.0f;
struct uz_3ph_dq_t i_dq_ref_Amps_1 				= {0};
struct uz_3ph_dq_t 	v_dq_ref_Volts_1 			= {0};
struct uz_DutyCycle_t output_1 					= {0};

// ---------------- Resonant Controllers ---------------- //
struct uz_3ph_dq_t i_dq_6th_ref_Amps_1					= {0};
struct uz_3ph_dq_t v_dq_6th_ref_Volts_1					= {0};
struct uz_3ph_dq_t i_dq_12th_ref_Amps_1					= {0};
struct uz_3ph_dq_t v_dq_12th_ref_Volts_1				= {0};
struct uz_3ph_alphabeta_t i_alphabeta_5th_ref_Amps_1	= {0};
struct uz_3ph_alphabeta_t v_alphabeta_5th_ref_Volts_1	= {0};
struct uz_3ph_dq_t v_dq_5th_ref_Volts_1					= {0};
struct uz_3ph_alphabeta_t i_alphabeta_7th_ref_Amps_1	= {0};
struct uz_3ph_alphabeta_t v_alphabeta_7th_ref_Volts_1	= {0};
struct uz_3ph_dq_t v_dq_7th_ref_Volts_1					= {0};
struct uz_3ph_dq_t output_FOC_RC_1						= {0};

// --------------- Harmonic Controllers ----------------- //
struct uz_3ph_abc_t i_abc_5th_Amps_bp_1 				= {0};
struct uz_3ph_abc_t i_abc_7th_Amps_bp_1 				= {0};
struct uz_3ph_dq_t i_dqn_5th_Amps_bp_1 					= {0};
struct uz_3ph_dq_t i_dqn_7th_Amps_bp_1 					= {0};
struct uz_3ph_dq_t i_dqn_5th_Amps_1 					= {0};
struct uz_3ph_dq_t i_dqn_7th_Amps_1 					= {0};
struct uz_3ph_dq_t i_dqn_5th_ref_Amps_1 				= {0};
struct uz_3ph_dq_t i_dqn_7th_ref_Amps_1 				= {0};
struct uz_3ph_dq_t v_dqn_5th_ref_Volts_1 				= {0};
struct uz_3ph_dq_t v_dqn_7th_ref_Volts_1 				= {0};
struct uz_3ph_abc_t v_abc_5th_ref_Volts_1 				= {0};
struct uz_3ph_abc_t v_abc_7th_ref_Volts_1 				= {0};
struct uz_3ph_dq_t output_FOC_HC_1						= {0};

// ---------------- Controller Settings ----------------- //
float Kp_speed_1 								= 0.01f;
float Ki_speed_1 								= 1.0f;
float Kp_id_1 									= 0.3f;
float Ki_id_1 									= 230.0f;
float Kp_iq_1 									= 0.5f;
float Ki_iq_1 									= 230.0f;
float Gain_RC_6th_1								= 100.0f;
float Gain_RC_12th_1							= 10.0f;
float Gain_RC_5th_1								= 100.0f;
float Gain_RC_7th_1								= 100.0f;

// ------------------- Wavegen Chirp -------------------- //
bool enable_excitation 							= false;
float excitation_amplitude 						= 0.0f;
float sampling_time 							= 1.0f/30.0e3f;

// ======================= PMSM 2 ======================= //
// --------------- Pointers to instances ---------------- //
extern struct uz_PMSM_t config_PMSM_2;
extern uz_SpeedControl_t* SC_instance_2;
extern uz_SetPoint_t* SP_instance_2;
extern uz_CurrentControl_t* CC_instance_2;
extern uz_subspace_resonant_control* RC_instance_6th_2;
extern uz_encoder_offset_estimation_t* encoder_offset_obj_2;

// ---------------- Inverter Measurement ---------------- //
struct uz_3ph_abc_t v_abc_Volts_2 				= {0};
float v_DC_Volts_2 								= 24.0f;
struct uz_3ph_abc_t i_abc_Amps_2 				= {0};
float i_DC_Amps_2 								= 0.0f;

// --------- Field Oriented Control and Signals --------- //
float omega_m_rad_per_sec_2 					= 0.0f;
float omega_el_rad_per_sec_2 					= 0.0f;
float theta_el_rad_2 							= 0.0f;
float theta_el_offset_2 						= 1.4f;
struct uz_3ph_dq_t i_dq_Amps_2 					= {0};
struct uz_3ph_dq_t v_dq_Volts_2 				= {0};
float n_ref_rpm_2 								= 0.0f;
float M_ref_Nm_2 								= 0.0f;
struct uz_3ph_dq_t v_dq_ref_Volts_2 			= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_2 				= {0};
struct uz_DutyCycle_t output_2 					= {0};

// ---------------- Resonant Controllers ---------------- //
struct uz_3ph_dq_t dq_resonant_ref_2			= {0};
struct uz_3ph_dq_t dq_resonant_2				= {0};
struct uz_3ph_dq_t output_FOC_RC_2				= {0};

// ---------------- Controller Settings ----------------- //
float Kp_speed_2 								= 0.1f;
float Ki_speed_2 								= 1.0f;
float Kp_id_2 									= 0.3f;
float Ki_id_2 									= 230.0f;
float Kp_iq_2 									= 0.5f;
float Ki_iq_2 									= 230.0f;
float Gain_RC_6th_2								= 10.0f;

// ======================= Others ======================= //
float error_type = 0.0f;
int counter = 1;
int mode_1 = 0;
float order_6th = 6.0f;
float amplitude_6th_d = 0.0f;
float amplitude_6th_q = 0.0f;
float amplitude_5th = 0.0f;
float amplitude_7th = 0.0f;

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

    // Read Measurement from ADCs and Encoder
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_2(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_3(&Global_Data);

    // Tristate Inverters
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);

    // Read Measurement Data of first Inverter Card
    v_abc_Volts_1.a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    v_abc_Volts_1.b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    v_abc_Volts_1.c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    v_DC_Volts_1 	= Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps_1.a  = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    i_abc_Amps_1.b  = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    i_abc_Amps_1.c  = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    i_DC_Amps_1     = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);

    // Read Measurement Data of second Inverter Card
    v_abc_Volts_2.a = Global_Data.aa.A2.me.ADC_B8 * 12.0f;
    v_abc_Volts_2.b = Global_Data.aa.A2.me.ADC_B7 * 12.0f;
    v_abc_Volts_2.c = Global_Data.aa.A2.me.ADC_B6 * 12.0f;
    v_DC_Volts_2 	= Global_Data.aa.A2.me.ADC_A1 * 12.0f;
    i_abc_Amps_2.a  = Global_Data.aa.A2.me.ADC_A4 * 12.5f;
    i_abc_Amps_2.b  = Global_Data.aa.A2.me.ADC_A3 * 12.5f;
    i_abc_Amps_2.c  = Global_Data.aa.A2.me.ADC_A2 * 12.5f;
    i_DC_Amps_2     = Global_Data.aa.A2.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);

    // Get Current State
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state) {
    	// enable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    } else {
    	// disable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    }

    // Calculation of Signals for FOC for PMSM 1
    omega_m_rad_per_sec_1 = Global_Data.av.mechanicalRotorSpeed_filtered_1*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec_1 = omega_m_rad_per_sec_1*config_PMSM_1.polePairs;
    Global_Data.av.omega_el_1 = omega_el_rad_per_sec_1;
    theta_el_rad_1 = Global_Data.av.theta_elec_1 - Global_Data.av.theta_offset_1;
    i_dq_Amps_1 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_1, theta_el_rad_1);
    i_alphabeta_Amps_1 = uz_transformation_3ph_abc_to_alphabeta(i_abc_Amps_1);
    v_dq_Volts_1 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_1, theta_el_rad_1);

    // Calculation of Signals for FOC for PMSM 2
    omega_m_rad_per_sec_2 = Global_Data.av.mechanicalRotorSpeed_filtered_2*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec_2 = omega_m_rad_per_sec_2*config_PMSM_2.polePairs;
    Global_Data.av.omega_el_2 = omega_el_rad_per_sec_2;
    theta_el_rad_2 = Global_Data.av.theta_elec_2 - Global_Data.av.theta_offset_2;
    i_dq_Amps_2 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_2, theta_el_rad_2);
    v_dq_Volts_2 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_2, theta_el_rad_2);

// =============== Offset Estimation =============== //
//    // Offset Estimation
//    Global_Data.av.U_q = v_dq_ref_Volts_1.q;                                              // write controller output ref voltage to global data
// =============== Offset Estimation =============== //

    // Enable Control
    if (current_state==control_state)
    {

// =============== Chirp Excitation =============== //
//   	// Noise and Chirp Generation
//    	if(enable_excitation){
//    		}else{
//    	}
//    	i_dq_ref_Amps.q=0.0f;
//        i_dq_ref_Amps.d=uz_wavegen_white_noise(excitation_amplitude);
//        i_dq_ref_Amps.d=uz_wavegen_sine(5.0f, excitation_amplitude);
//        i_dq_ref_Amps.d= excitation_amplitude * uz_wavegen_chirp_sample(chirp_instance, sampling_time);
//        i_dq_ref_Amps.q=0.0f;
//        i_dq_ref_Amps.d= excitation_amplitude;
//        // Offset estimation
//    	if(!uz_encoder_offset_estimation_get_finished(encoder_offset_obj)){         // if not finished
//    		i_dq_ref_Amps = uz_encoder_offset_estimation_step(encoder_offset_obj);//receive current controller setpoint current from stepping function
//    	}else{
//    	    i_dq_ref_Amps.d = 0.0f;                                              // else: it is finished, setpoints are 0
//    	    i_dq_ref_Amps.q = 0.0f;
//    	}
// =============================================== //

    // Field Oriented Control of PMSM 1 and Resonant Controller
    M_ref_Nm_1 = uz_SpeedControl_sample(SC_instance_1, omega_m_rad_per_sec_1, n_ref_rpm_1);
    i_dq_ref_Amps_1 = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_1, M_ref_Nm_1, v_DC_Volts_1, i_dq_Amps_1);
    v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);

    switch (mode_1)
    {
    default: // No Resonant Controller
    	output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);
    	break;

    case 1: // Resonant Controller for 6th and 12th Harmonic in dq-System
    	i_dq_6th_ref_Amps_1.d = amplitude_6th_d;
    	i_dq_6th_ref_Amps_1.q = amplitude_6th_q;
		v_dq_6th_ref_Volts_1 = uz_subspace_resonant_control_step_dq(RC_instance_6th_1, i_dq_6th_ref_Amps_1, i_dq_Amps_1, omega_el_rad_per_sec_1);
		v_dq_12th_ref_Volts_1 = uz_subspace_resonant_control_step_dq(RC_instance_12th_1, i_dq_12th_ref_Amps_1, i_dq_Amps_1, omega_el_rad_per_sec_1);
		output_FOC_RC_1.d = v_dq_ref_Volts_1.d + v_dq_6th_ref_Volts_1.d + v_dq_12th_ref_Volts_1.d;
		output_FOC_RC_1.q = v_dq_ref_Volts_1.q + v_dq_6th_ref_Volts_1.q + v_dq_12th_ref_Volts_1.q;
		output_1 = uz_Space_Vector_Modulation(output_FOC_RC_1, v_DC_Volts_1, theta_el_rad_1);
    	break;

    case 2: // Resonant Controller for 5th and 7th Harmonic in abc-System
    	i_alphabeta_5th_ref_Amps_1.alpha = amplitude_5th;
    	i_alphabeta_5th_ref_Amps_1.beta = amplitude_5th;
    	i_alphabeta_7th_ref_Amps_1.alpha = amplitude_7th;
    	i_alphabeta_7th_ref_Amps_1.beta = amplitude_7th;
    	v_alphabeta_5th_ref_Volts_1 = uz_subspace_resonant_control_step_alphabeta(RC_instance_5th_1, i_alphabeta_5th_ref_Amps_1, i_alphabeta_Amps_1, omega_el_rad_per_sec_1);
    	v_alphabeta_7th_ref_Volts_1 = uz_subspace_resonant_control_step_alphabeta(RC_instance_7th_1, i_alphabeta_7th_ref_Amps_1, i_alphabeta_Amps_1, omega_el_rad_per_sec_1);
    	v_dq_5th_ref_Volts_1 = uz_transformation_3ph_alphabeta_to_dq(v_alphabeta_5th_ref_Volts_1, theta_el_rad_1);
    	v_dq_7th_ref_Volts_1 = uz_transformation_3ph_alphabeta_to_dq(v_alphabeta_7th_ref_Volts_1, theta_el_rad_1);
    	output_FOC_RC_1.d = v_dq_ref_Volts_1.d + v_dq_5th_ref_Volts_1.d + v_dq_7th_ref_Volts_1.d;
    	output_FOC_RC_1.q = v_dq_ref_Volts_1.q + v_dq_5th_ref_Volts_1.q + v_dq_7th_ref_Volts_1.q;
    	output_1 = uz_Space_Vector_Modulation(output_FOC_RC_1, v_DC_Volts_1, theta_el_rad_1);
    	break;

    case 3: // Harmonic Controllers for 5th and 7th Harmonic
    	i_abc_5th_Amps_bp_1.a = uz_signals_IIR_Filter_sample(BP_instance_5th_a_1, i_abc_Amps_1.a);
    	i_abc_5th_Amps_bp_1.b = uz_signals_IIR_Filter_sample(BP_instance_5th_b_1, i_abc_Amps_1.b);
    	i_abc_5th_Amps_bp_1.c = uz_signals_IIR_Filter_sample(BP_instance_5th_c_1, i_abc_Amps_1.c);
    	i_abc_7th_Amps_bp_1.a = uz_signals_IIR_Filter_sample(BP_instance_7th_a_1, i_abc_Amps_1.a);
    	i_abc_7th_Amps_bp_1.b = uz_signals_IIR_Filter_sample(BP_instance_7th_b_1, i_abc_Amps_1.b);
    	i_abc_7th_Amps_bp_1.c = uz_signals_IIR_Filter_sample(BP_instance_7th_c_1, i_abc_Amps_1.c);
    	i_dqn_5th_Amps_bp_1 = uz_transformation_3ph_harmonic_abc_to_dq(i_abc_5th_Amps_bp_1, theta_el_rad_1, -5.0f);
    	i_dqn_7th_Amps_bp_1 = uz_transformation_3ph_harmonic_abc_to_dq(i_abc_7th_Amps_bp_1, theta_el_rad_1, 7.0f);
    	i_dqn_5th_Amps_1.d = uz_signals_IIR_Filter_sample(LP_instance_5th_d_1, i_dqn_5th_Amps_bp_1.d);
    	i_dqn_5th_Amps_1.q = uz_signals_IIR_Filter_sample(LP_instance_5th_q_1, i_dqn_5th_Amps_bp_1.q);
    	i_dqn_7th_Amps_1.d = uz_signals_IIR_Filter_sample(LP_instance_7th_d_1, i_dqn_7th_Amps_bp_1.d);
    	i_dqn_7th_Amps_1.q = uz_signals_IIR_Filter_sample(LP_instance_7th_q_1, i_dqn_7th_Amps_bp_1.q);
    	v_dqn_5th_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_5th_1, i_dqn_5th_ref_Amps_1, i_dqn_5th_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
    	v_dqn_7th_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_7th_1, i_dqn_7th_ref_Amps_1, i_dqn_7th_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
    	v_abc_5th_ref_Volts_1 = uz_transformation_3ph_harmonic_dq_to_abc(v_dqn_5th_ref_Volts_1, theta_el_rad_1, -5.0f);
    	v_abc_7th_ref_Volts_1 = uz_transformation_3ph_harmonic_dq_to_abc(v_dqn_7th_ref_Volts_1, theta_el_rad_1, 7.0f);
    	v_dq_5th_ref_Volts_1 = uz_transformation_3ph_abc_to_dq(v_abc_5th_ref_Volts_1,theta_el_rad_1);
    	v_dq_7th_ref_Volts_1 = uz_transformation_3ph_abc_to_dq(v_abc_7th_ref_Volts_1,theta_el_rad_1);
    	output_FOC_HC_1.d = v_dq_ref_Volts_1.d + v_dq_5th_ref_Volts_1.d + v_dq_7th_ref_Volts_1.d;
    	output_FOC_HC_1.q = v_dq_ref_Volts_1.q + v_dq_5th_ref_Volts_1.q + v_dq_7th_ref_Volts_1.q;
    	output_1 = uz_Space_Vector_Modulation(output_FOC_HC_1, v_DC_Volts_1, theta_el_rad_1);
    	break;
    }

	Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
    Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
    Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;

   	// Field Oriented Control of PMSM 2
//    if (counter == 10)
//    	{
//    	M_ref_Nm_2 = uz_SpeedControl_sample(SC_instance_2, omega_m_rad_per_sec_2, n_ref_rpm_2);
//    	counter = 1;
//    	}
//    else
//    	{
//    	counter++;
//    	}
//    i_dq_ref_Amps_2 = uz_SetPoint_sample(SP_instance_2, omega_m_rad_per_sec_2, M_ref_Nm_2, v_DC_Volts_2, i_dq_Amps_2);
//    v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_2, i_dq_ref_Amps_2, i_dq_Amps_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
//    output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
//    dq_resonant_2 = uz_subspace_resonant_control_step_dq(RC_instance_2, dq_resonant_ref_2, i_dq_Amps_2, omega_el_rad_per_sec_2/5.0f*4.0f);
//    output_FOC_RC_2.d = v_dq_ref_Volts_2.d + dq_resonant_2.d;
//    output_FOC_RC_2.q = v_dq_ref_Volts_2.q + dq_resonant_2.q;
//    output_2 = uz_Space_Vector_Modulation(output_FOC_RC_2, v_DC_Volts_2, theta_el_rad_2);
//    output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
   	Global_Data.rasv.halfBridge4DutyCycle = output_2.DutyCycle_A;
   	Global_Data.rasv.halfBridge5DutyCycle = output_2.DutyCycle_B;
   	Global_Data.rasv.halfBridge6DutyCycle = output_2.DutyCycle_C;

    }
    else
    {
    	// Set Tristate
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);

    	// Reset Speed and Current Controllers
    	uz_SpeedControl_reset(SC_instance_1);
    	uz_CurrentControl_reset(CC_instance_1);
    	uz_SpeedControl_reset(SC_instance_2);
    	uz_CurrentControl_reset(CC_instance_2);

    	// Reset Resonant Controllers
    	uz_subspace_resonant_control_reset(RC_instance_6th_1);
    	uz_subspace_resonant_control_reset(RC_instance_12th_1);
    	uz_subspace_resonant_control_reset(RC_instance_5th_1);
    	uz_subspace_resonant_control_reset(RC_instance_7th_1);
    	uz_subspace_resonant_control_reset(RC_instance_6th_2);
    }

    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);

    // Set Controllers of PMSM 1
    uz_SpeedControl_set_Kp(SC_instance_1, Kp_speed_1);
    uz_SpeedControl_set_Ki(SC_instance_1, Ki_speed_1);
    uz_CurrentControl_set_Kp_id(CC_instance_1, Kp_id_1);
    uz_CurrentControl_set_Kp_iq(CC_instance_1, Kp_iq_1);
    uz_CurrentControl_set_Ki_id(CC_instance_1, Ki_id_1);
    uz_CurrentControl_set_Ki_iq(CC_instance_1, Ki_iq_1);

    // Set Controllers of PMSM 2
    uz_SpeedControl_set_Kp(SC_instance_2, Kp_speed_2);
    uz_SpeedControl_set_Ki(SC_instance_2, Ki_speed_2);
    uz_CurrentControl_set_Kp_id(CC_instance_2, Kp_id_2);
    uz_CurrentControl_set_Kp_iq(CC_instance_2, Kp_iq_2);
    uz_CurrentControl_set_Ki_id(CC_instance_2, Ki_id_2);
    uz_CurrentControl_set_Ki_iq(CC_instance_2, Ki_iq_2);

    // Set Resonant Controller Gains of PMSM 1
    uz_subspace_resonant_control_set_gains(RC_instance_6th_1, Gain_RC_6th_1, Gain_RC_6th_1);
    uz_subspace_resonant_control_set_gains(RC_instance_12th_1, Gain_RC_12th_1, Gain_RC_12th_1);
    uz_subspace_resonant_control_set_gains(RC_instance_5th_1, Gain_RC_5th_1, Gain_RC_5th_1);
    uz_subspace_resonant_control_set_gains(RC_instance_7th_1, Gain_RC_7th_1, Gain_RC_7th_1);

    // Set Resonant Controller Gains of PMSM 2
    uz_subspace_resonant_control_set_gains(RC_instance_6th_2, Gain_RC_6th_2, Gain_RC_6th_2);

    // Update JavaScope
    JavaScope_update(&Global_Data);

    // ------ Inverter 1 ------ //
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
        error_type = 1.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
    	error_type = 2.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    	error_type = 3.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
    	error_type = 4.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    	error_type = 5.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
    	error_type = 6.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
    	error_type = 7.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
    	error_type = 8.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
    	error_type = 9.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
    	error_type = 10.0f;
       ultrazohm_state_machine_set_error(true);
    }

    // ------ Inverter 2 ------ //
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H1) {
        error_type = 11.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L1) {
     	error_type = 12.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H2) {
     	error_type = 13.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L2) {
    	error_type = 14.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H3) {
      	error_type = 15.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L3) {
      	error_type = 16.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d2.OC_L1) {
      	error_type = 17.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d2.OC_H1) {
     	error_type = 18.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d2.OC_L2) {
      	error_type = 19.0f;
       ultrazohm_state_machine_set_error(true);
     }
    //Overcurrent for DC-link
//    if (!Global_Data.av.inverter_outputs_d2.OC_H2) {
//      	error_type = 20.0f;
//       ultrazohm_state_machine_set_error(true);
//    }

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
