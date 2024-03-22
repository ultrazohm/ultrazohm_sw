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
#include "../uz/uz_parameterid_rs/uz_parameterid_rs.h"
#include "../uz/uz_parameterid_rc/uz_parameterid_rc.h"
#include "stdbool.h"


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
extern uz_encoder_offset_estimation_t* encoder_offset_obj_1;
extern uz_wavegen_chirp* chirp_instance_1;

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



// ------------------- Wavegen Chirp -------------------- //
bool enable_excitation 							= false;
float excitation_amplitude 						= 0.0f;
float sampling_time 							= 1.0f/25.0e3f;

// ======================= PMSM 2 ======================= //
// --------------- Pointers to instances ---------------- //
extern struct uz_PMSM_t config_PMSM_2;
extern uz_SpeedControl_t* SC_instance_2;
extern uz_SetPoint_t* SP_instance_2;
extern uz_CurrentControl_t* CC_instance_2;
extern uz_encoder_offset_estimation_t* encoder_offset_obj_2;

// ---------------- Inverter Measurement ---------------- //
struct uz_3ph_abc_t v_abc_Volts_2 				= {0};
float v_DC_Volts_2 								= 48.0f;
struct uz_3ph_abc_t i_abc_Amps_2 				= {0};
float i_DC_Amps_2 								= 0.0f;

// --------- Field Oriented Control and Signals --------- //
float omega_m_rad_per_sec_2 					= 0.0f;
float omega_el_rad_per_sec_2 					= 0.0f;
float theta_el_rad_2 							= 0.0f;
float theta_el_offset_2 						= 3.46f;
struct uz_3ph_dq_t i_dq_Amps_2 					= {0};
struct uz_3ph_dq_t v_dq_Volts_2 				= {0};
float n_ref_rpm_2 								= 0.0f;
float M_ref_Nm_2 								= 0.0f;
struct uz_3ph_dq_t v_dq_ref_Volts_2 			= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_2 				= {0};
struct uz_DutyCycle_t output_2 					= {0};



// ---------------- induced voltage ----------------- //
struct uz_3ph_dq_t v_ind_dq_Volts_2 			= {0};
struct uz_3ph_dq_t v_ind_dq_filt_Volts_2 			= {0};
struct uz_3ph_dq_t v_ind_dq_ref_Volts_2 			= {0};
struct uz_3ph_dq_t v_dq_SOS_Volts_2 			= {0};
float r_s_2 									= 0.030f;
extern uz_IIR_Filter_t* LP_instance_ud_ind_2;
extern uz_IIR_Filter_t* LP_instance_uq_ind_2;
extern uz_IIR_Filter_t* LP_instance_rc_d_2;
extern uz_IIR_Filter_t* LP_instance_rc_q_2;
extern uz_CurrentControl_t* CC_instance_u_ind;
struct uz_3ph_dq_t psi_dq_mVoltseconds_2 			= {0};
struct uz_3ph_dq_t rc_dq_Ohm 			= {0};
struct uz_3ph_dq_t rc_dq_filt_Ohm 			= {0};
struct uz_3ph_dq_t rc_para_dq 			= {0};
float Ld2 = 30.0e-6f;
float Lq2 = 50.0e-6f;
float Psi_PM = 7.0e-3f;


// ======================= Others ======================= //
float error_type = 0.0f;
int counter = 1;
float M_meas_Nm = 0.0f;
float M_meas_Nm2 = 0.0f;
int control_induced_voltages = 0;
float rc_repeat_counter = 0.0f;

float DC_A = 0.0f;
float DC_B = 0.0f;
float DC_C = 0.0f;
// ======================= CIL ======================= //

extern uz_pmsmModel_t *pmsm;
extern uz_CurrentControl_t* CurrentControl_instance;
uz_3ph_dq_t reference_currents_Amp = {0};
uz_3ph_dq_t measured_currents_Amp = {0};
uz_3ph_dq_t CurrentControl_output_Volts = {0};
float omega_el_rad_per_sec = 0.0f;
struct uz_pmsmModel_inputs_t pmsm_inputs={
  .omega_mech_1_s=0.0f,
  .v_d_V=0.0f,
  .v_q_V=0.0f,
  .load_torque=0.0f
};
struct uz_pmsmModel_outputs_t pmsm_outputs={
  .i_d_A=0.0f,
  .i_q_A=0.0f,
  .torque_Nm=0.0f,
  .omega_mech_1_s=0.0f
};
extern uz_parameterid_rs_t* rs_meas_instance;
extern uz_parameterid_rc_t* rc_meas_instance;
struct uz_parameterid_output actual_output;
struct uz_parameterid_rc_meas_out_t rc_output;
struct uz_3ph_dq_t cil_u_ind_Volts 			= {0};
struct uz_3ph_dq_t cil_u_ind_ref_Volts 			= {0};


enum running_mode run_state = normal;

enum switch_control switch_control = control_idq;

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
    M_meas_Nm = Global_Data.aa.A3.me.ADC_A4 * 2.0f - 0.02f;
    M_meas_Nm2 = -1.0f * M_meas_Nm;

    // Tristate Inverters
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);

    // Read Measurement Data of first Inverter Card
    v_abc_Volts_1.a = 11.7657f * Global_Data.aa.A1.me.ADC_B8 + 0.0533f;
    v_abc_Volts_1.b = 11.7657f * Global_Data.aa.A1.me.ADC_B7 + 0.0533f;
    v_abc_Volts_1.c = 11.7657f * Global_Data.aa.A1.me.ADC_B6 + 0.0533f;
    v_DC_Volts_1 	= Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps_1.a  = 12.223f * Global_Data.aa.A1.me.ADC_A4 + 0.0164f;
    i_abc_Amps_1.b  = 12.3123f * Global_Data.aa.A1.me.ADC_A3 + 0.0161f ;
    i_abc_Amps_1.c  = 12.4303f * Global_Data.aa.A1.me.ADC_A2 - 0.0184f ;
    i_DC_Amps_1     = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);

    // Read Measurement Data of second Inverter Card
    v_abc_Volts_2.a = 12.0f * Global_Data.aa.A2.me.ADC_B8;
    v_abc_Volts_2.b = 12.0f * Global_Data.aa.A2.me.ADC_B7;
    v_abc_Volts_2.c = 12.0f * Global_Data.aa.A2.me.ADC_B6;
    v_DC_Volts_2 	= Global_Data.aa.A2.me.ADC_A1 * 12.0f;
    i_abc_Amps_2.a  = 12.5f * Global_Data.aa.A2.me.ADC_A4;
    i_abc_Amps_2.b  = 12.5f * Global_Data.aa.A2.me.ADC_A3;
    i_abc_Amps_2.c  = 12.5f * Global_Data.aa.A2.me.ADC_A2;
    i_DC_Amps_2     = Global_Data.aa.A2.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);

    // Get Current State
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state) {
    	// enable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    } else {
    	// disable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    }

    // Calculation of Signals for FOC of PMSM 1
    /*omega_m_rad_per_sec_1 = Global_Data.av.mechanicalRotorSpeed_filtered_1*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec_1 = omega_m_rad_per_sec_1*config_PMSM_1.polePairs;
    Global_Data.av.omega_el_1 = omega_el_rad_per_sec_1;
    theta_el_rad_1 = Global_Data.av.theta_elec_1 - Global_Data.av.theta_offset_1;
    i_dq_Amps_1 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_1, theta_el_rad_1);
    v_dq_Volts_1 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_1, theta_el_rad_1);*/

    // Calculation of Signals for FOC of PMSM 2
    omega_m_rad_per_sec_2 = Global_Data.av.mechanicalRotorSpeed_filtered_2*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec_2 = omega_m_rad_per_sec_2*config_PMSM_2.polePairs;
    Global_Data.av.omega_el_2 = omega_el_rad_per_sec_2;
    theta_el_rad_2 = Global_Data.av.theta_elec_2 - theta_el_offset_2;
    i_dq_Amps_2 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_2, theta_el_rad_2);
    v_dq_Volts_2 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_2, theta_el_rad_2);

    // Enable Control
    if (current_state==control_state)
    {

    		v_dq_SOS_Volts_2.d = (v_dq_Volts_2.d + v_dq_ref_Volts_2.d)/2.0f;
    		v_dq_SOS_Volts_2.q = (v_dq_Volts_2.q + v_dq_ref_Volts_2.q)/2.0f;
    		r_s_2 = (1.75e-6f * Global_Data.av.mechanicalRotorSpeed_filtered_2 * Global_Data.av.mechanicalRotorSpeed_filtered_2 + 5.733e-4f * Global_Data.av.mechanicalRotorSpeed_filtered_2 + 28.4648f)/1000.0f;
    		v_ind_dq_Volts_2.d = v_dq_SOS_Volts_2.d - (r_s_2 * i_dq_Amps_2.d);
    		v_ind_dq_Volts_2.q = v_dq_SOS_Volts_2.q - (r_s_2 * i_dq_Amps_2.q);
    		v_ind_dq_filt_Volts_2.d = uz_signals_IIR_Filter_sample(LP_instance_ud_ind_2, v_ind_dq_Volts_2.d);
    	    v_ind_dq_filt_Volts_2.q = uz_signals_IIR_Filter_sample(LP_instance_uq_ind_2, v_ind_dq_Volts_2.q);

    	    switch(run_state) {
				case rs_measurement_Heidrive:
					// Field Oriented Control of PMSM 1 - speed-controlled
		    		/*M_ref_Nm_1 = uz_SpeedControl_sample(SC_instance_1, omega_m_rad_per_sec_1, actual_output.n_sample);
		    		i_dq_ref_Amps_1 = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_1, M_ref_Nm_1, v_DC_Volts_1, i_dq_Amps_1);
					v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
					output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);

					// Set DutyCycles of PMSM 1
					Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
					Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
					Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;*/

					// calculation of set-values
			        actual_output = uz_parameterid_rs_generate_outputs(rs_meas_instance, v_dq_Volts_2.d, i_dq_Amps_2.d);
			        i_dq_ref_Amps_2.d = actual_output.i_sample;
			        i_dq_ref_Amps_2.q = 0.0f;

					// Field Oriented Control of PMSM 2 - current-controlled
					v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_2, i_dq_ref_Amps_2, i_dq_Amps_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
					output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);

					// Set DutyCycles of PMSM 2
					Global_Data.rasv.halfBridge4DutyCycle = output_2.DutyCycle_A;
					Global_Data.rasv.halfBridge5DutyCycle = output_2.DutyCycle_B;
					Global_Data.rasv.halfBridge6DutyCycle = output_2.DutyCycle_C;
					break;


				case rc_measurement_Heidrive:
					// Field Oriented Control of PMSM 1 - speed-controlled
		    		/*M_ref_Nm_1 = uz_SpeedControl_sample(SC_instance_1, omega_m_rad_per_sec_1, rc_output.set_out.n_set);
		    		i_dq_ref_Amps_1 = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_1, M_ref_Nm_1, v_DC_Volts_1, i_dq_Amps_1);
					v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
					output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);

					// Set DutyCycles of PMSM 1
					Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
					Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
					Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;*/

					// calculation of set-values
			        rc_output = uz_parameterid_rc_generate_outputs(rc_meas_instance, v_dq_SOS_Volts_2.d, v_dq_SOS_Volts_2.q, i_dq_Amps_2.d, i_dq_Amps_2.q, Global_Data.av.mechanicalRotorSpeed_filtered_2, M_meas_Nm);
			        i_dq_ref_Amps_2.d = rc_output.set_out.id_set;
			        i_dq_ref_Amps_2.q = rc_output.set_out.iq_set;
			        rc_repeat_counter = rc_output.finished;

			        // Field Oriented Control of PMSM 2
			        if(rc_output.generator_mode){
						// Field Oriented Control of PMSM 2 - u_ind-controlled
						v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_u_ind, i_dq_ref_Amps_2, v_ind_dq_Volts_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
						output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
			        } else {
					// Field Oriented Control of PMSM 2 - current-controlled
					v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_2, i_dq_ref_Amps_2, i_dq_Amps_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
					output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
			        }

					// Set DutyCycles of PMSM 2
					Global_Data.rasv.halfBridge4DutyCycle = output_2.DutyCycle_A;
					Global_Data.rasv.halfBridge5DutyCycle = output_2.DutyCycle_B;
					Global_Data.rasv.halfBridge6DutyCycle = output_2.DutyCycle_C;
					break;

				case normal:
					// Field Oriented Control of PMSM 1 - speed-controlled
		    		/*M_ref_Nm_1 = uz_SpeedControl_sample(SC_instance_1, omega_m_rad_per_sec_1, n_ref_rpm_1);
		    		i_dq_ref_Amps_1 = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_1, M_ref_Nm_1, v_DC_Volts_1, i_dq_Amps_1);
					v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
					output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);

					// Set DutyCycles of PMSM 1
					Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
					Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
					Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;*/

					// Field Oriented Control of PMSM 2
					if (switch_control == control_uind ){
					// Field Oriented Control of PMSM 2 - current-controlled
					v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_u_ind, v_ind_dq_ref_Volts_2, v_ind_dq_Volts_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
					output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
					} else {
					v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_2, i_dq_ref_Amps_2, i_dq_Amps_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
					output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
					}

					// Set DutyCycles of PMSM 2
					//Global_Data.rasv.halfBridge4DutyCycle = DC_A;
					//Global_Data.rasv.halfBridge5DutyCycle = DC_B;
					//Global_Data.rasv.halfBridge6DutyCycle = DC_C;

					Global_Data.rasv.halfBridge4DutyCycle = output_2.DutyCycle_A;
					Global_Data.rasv.halfBridge5DutyCycle = output_2.DutyCycle_B;
					Global_Data.rasv.halfBridge6DutyCycle = output_2.DutyCycle_C;
					break;


				case reset:
					uz_parameterid_rs_reset(rs_meas_instance);
					actual_output.i_sample = 0.0f;
					actual_output.n_sample = 0.0f;
					actual_output.isr_stepcounter = 0.0f;
					n_ref_rpm_1 = 0.0f;
					uz_parameterid_rc_reset(rc_meas_instance);
			    	uz_CurrentControl_reset(CC_instance_u_ind);
					rc_output.mot_rc_d = 0.0f;
					rc_output.mot_rc_q = 0.0f;
					rc_output.gen_rc_d = 0.0f;
					rc_output.gen_rc_q = 0.0f;
					rc_output.set_out.id_set = 0.0f;
					rc_output.set_out.iq_set = 0.0f;
					i_dq_ref_Amps_1.d = 0.0f;
					i_dq_ref_Amps_1.q = 0.0f;
					i_dq_ref_Amps_2.d = 0.0f;
					i_dq_ref_Amps_2.q = 0.0f;
					switch_control = control_idq;

					// Set DutyCycles of PMSM 1 and 2
					/*v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
					output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);
					Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
					Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
					Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;*/

					v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_2, i_dq_ref_Amps_2, i_dq_Amps_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
					output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
					Global_Data.rasv.halfBridge4DutyCycle = output_2.DutyCycle_A;
					Global_Data.rasv.halfBridge5DutyCycle = output_2.DutyCycle_B;
					Global_Data.rasv.halfBridge6DutyCycle = output_2.DutyCycle_C;

				    // Tristate OFF
				    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
				    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
					break;

				default:
					break;
			}


    }
    else
    {
    	// Set Tristate
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);

    	// Reset Speed and Current Controllers
    	//uz_SpeedControl_reset(SC_instance_1);
    	//uz_CurrentControl_reset(CC_instance_1);
    	uz_SpeedControl_reset(SC_instance_2);
    	uz_CurrentControl_reset(CC_instance_2);
    	uz_CurrentControl_reset(CC_instance_u_ind);

    }

    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);


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
    if (!Global_Data.av.inverter_outputs_d2.OC_H2) {
      	error_type = 20.0f;
       ultrazohm_state_machine_set_error(true);
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
