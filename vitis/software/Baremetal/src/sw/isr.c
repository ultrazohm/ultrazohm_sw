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
#include <stdbool.h>
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
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"
#include "../uz/uz_ParameterID_rc/uz_ParameterID_rc.h"

float i_d_soll=0.0f;
float i_q_soll=0.0f;
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

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static float last_u_d_pu = 0.0f;
static float last_u_q_pu = 0.0f;
//defines and limits
#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f
#define		MAX_CURRENT_AMP		15.0f
#define		RATED_CURRENT		12.0f
#define		DC_VOLTAGE			48.0f
#define		MAX_MODULATION_INDEX (1.0f / sqrtf(3.0f))
#define		MAX_VOLTAGE			(DC_VOLTAGE * MAX_MODULATION_INDEX)
#define		TS_TRAINING			0.0001f
#define		NUMBER_OF_INPUTS_NN 9U
#define		RATED_SPEED			1000.0f

// measurement structs for motor control
struct uz_3ph_abc_t i_abc_left = {0.0f};
struct uz_3ph_abc_t i_abc_right = {0.0f};
struct uz_3ph_abc_t v_abc_right = {0.0f};
struct uz_3ph_abc_t v_abc_right_rev_filter = {0.0f};
struct uz_3ph_abc_t v_abc_right_filter_comp = {0.0f};
struct uz_3ph_abc_t v_abc_left = {0.0f};
struct uz_3ph_dq_t i_dq_left = {0.0f};
struct uz_3ph_dq_t i_dq_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_left = {0.0f};
struct uz_3ph_dq_t i_dq_error_left = {0.0f};
struct uz_3ph_dq_t i_dq_error_right = {0.0f};
struct uz_3ph_dq_t i_dq_integrated_error_left = {0.0f};
struct uz_3ph_dq_t i_dq_integrated_error_right = {0.0f};
struct uz_3ph_dq_t v_dq_ref_left = {0.0f};
struct uz_3ph_dq_t v_dq_ref_right = {0.0f};
struct uz_3ph_dq_t v_dq_rl_right = {0.0f};
struct uz_3ph_dq_t v_dq_meas_right = {0.0f};
struct uz_3ph_dq_t v_dq_meas_right_rev_filt = {0.0f};
struct uz_3ph_dq_t v_dq_meas_right_filter_comp = {0.0f};
struct uz_3ph_dq_t v_dq_meas_left = {0.0f};
struct uz_DutyCycle_t dutycyc_left = {0.0f};
struct uz_DutyCycle_t dutycyc_right = {0.0f};
struct uz_parameterID_rc_ref_val_t ref_rc_meas;
float thetal_el_right_unwrapped = 0.0f;
float thetal_el_left_unwrapped = 0.0f;
float average_temp_right = 0.0f;
float average_temp_left = 0.0f;
float observation[NUMBER_OF_INPUTS_NN] = {0};
struct uz_3ph_abc_t dc_motor_right = {0.0f};

enum ControllerApplication ConApp;
enum ControllerSelection ConSel;


bool ddpg_ext_clamping = false;
static bool first_step = true;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
//static void current_control_left_motor();
//static void speed_control_right_motor();
//static void filter_compensation_right();
static void speed_control_left_motor();
static void current_control_right_motor();
static void filter_compensation_left();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    switch(ConApp) {
    case CIL:
    	uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_model);
    	uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_model);
    	Global_Data.av.PMSM_outputs				= uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_model);
    	Global_Data.av.i_d_right				= Global_Data.av.PMSM_outputs.i_d_A;
    	Global_Data.av.i_q_right 				= Global_Data.av.PMSM_outputs.i_q_A;
    	Global_Data.av.omega_mech_right			= Global_Data.av.PMSM_outputs.omega_mech_1_s;
    	Global_Data.av.torque_right				= Global_Data.av.PMSM_outputs.torque_Nm;
    	Global_Data.av.speed_rpm_right 			= Global_Data.av.omega_mech_right * 30.0f / UZ_PIf;
    	Global_Data.av.omega_el_right 			= Global_Data.av.omega_mech_right * Global_Data.av.polepairs_right;
    	Global_Data.av.v_dc_right				= DC_VOLTAGE;
    	Global_Data.av.v_dc_left				= DC_VOLTAGE;
    	Global_Data.av.v_d_right				= Global_Data.av.PMSM_inputs.v_d_V;
    	Global_Data.av.v_q_right			    = Global_Data.av.PMSM_inputs.v_q_V;
    	i_dq_right.d							= Global_Data.av.i_d_right;
    	i_dq_right.q							= Global_Data.av.i_q_right;
    	break;

    case REAL:

		// update speed and position of encoders
		Global_Data.av.omega_mech_left = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.encoder_left);
		thetal_el_left_unwrapped = uz_incrementalEncoder_get_theta_el(Global_Data.objects.encoder_left) - Global_Data.av.theta_el_offset_left;
		Global_Data.av.theta_el_left = uz_signals_wrap(thetal_el_left_unwrapped, 2.0f*UZ_PIf);
		Global_Data.av.resolver_pl_outputs_right = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_right);
		Global_Data.av.omega_mech_right = Global_Data.av.resolver_pl_outputs_right.omega_mech_rad_s;
		Global_Data.av.theta_el_right = Global_Data.av.resolver_pl_outputs_right.position_el_2pi;
		// update status of both inverters
		uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_left);
		uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_right);
		// assign status to Global_Data
		Global_Data.av.inverter_left_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_left);
		Global_Data.av.inverter_right_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_right);

		// Torque Sensor measurement
		Global_Data.av.torque = (Global_Data.aa.A1.me.ADC_A1 * (-1.0f)); //positive q-current = positive torque

		// Current Sensor Measurement
		Global_Data.av.i_c_right_CD = Global_Data.aa.A1.me.ADC_B5 * 7.013f;

		// assign inverter measurements
		Global_Data.av.i_a_left = Global_Data.aa.A2.me.ADC_A4 * CURRENT_2_SI_AMPERE;
		Global_Data.av.i_b_left = Global_Data.aa.A2.me.ADC_A3 * CURRENT_2_SI_AMPERE;
		Global_Data.av.i_c_left = Global_Data.aa.A2.me.ADC_A2 * CURRENT_2_SI_AMPERE;
		Global_Data.av.i_dc_left = Global_Data.aa.A2.me.ADC_B5 * CURRENT_2_SI_AMPERE;
		Global_Data.av.v_a_left = Global_Data.aa.A2.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
		Global_Data.av.v_b_left = Global_Data.aa.A2.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
		Global_Data.av.v_c_left = Global_Data.aa.A2.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
		Global_Data.av.v_dc_left = Global_Data.aa.A2.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

		Global_Data.av.i_a_right = Global_Data.aa.A3.me.ADC_A4 * CURRENT_2_SI_AMPERE;
		Global_Data.av.i_b_right = Global_Data.aa.A3.me.ADC_A3 * CURRENT_2_SI_AMPERE;
		Global_Data.av.i_c_right = Global_Data.aa.A3.me.ADC_A2 * CURRENT_2_SI_AMPERE;
		Global_Data.av.i_dc_right = Global_Data.aa.A3.me.ADC_B5 * CURRENT_2_SI_AMPERE;
		Global_Data.av.v_a_right = Global_Data.aa.A3.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
		Global_Data.av.v_b_right = Global_Data.aa.A3.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
		Global_Data.av.v_c_right = Global_Data.aa.A3.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
		Global_Data.av.v_dc_right = Global_Data.aa.A3.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

		// assign measurements from global_data to motor control structs
		i_abc_left.a = Global_Data.av.i_a_left;
		i_abc_left.b = Global_Data.av.i_b_left;
		i_abc_left.c = Global_Data.av.i_c_left;
		i_abc_right.a = Global_Data.av.i_a_right;
		i_abc_right.b = Global_Data.av.i_b_right;
		i_abc_right.c = Global_Data.av.i_c_right;
		v_abc_right.a = Global_Data.av.v_a_right;
		v_abc_right.b = Global_Data.av.v_b_right;
		v_abc_right.c = Global_Data.av.v_c_right;
		v_abc_right_rev_filter.a =  uz_signals_IIR_Filter_reverse_sample(Global_Data.objects.d2_phase_a_lowpass, v_abc_right.a);
		v_abc_right_rev_filter.b =  uz_signals_IIR_Filter_reverse_sample(Global_Data.objects.d2_phase_b_lowpass, v_abc_right.b);
		v_abc_right_rev_filter.c =  uz_signals_IIR_Filter_reverse_sample(Global_Data.objects.d2_phase_c_lowpass, v_abc_right.c);
		v_abc_left.a = Global_Data.av.v_a_left;
		v_abc_left.b = Global_Data.av.v_b_left;
		v_abc_left.c = Global_Data.av.v_c_left;

		// park transformation of measured currents
		i_dq_left = uz_transformation_3ph_abc_to_dq(i_abc_left, Global_Data.av.theta_el_left);
		i_dq_right = uz_transformation_3ph_abc_to_dq(i_abc_right, Global_Data.av.theta_el_right);
		v_dq_meas_right_rev_filt = uz_transformation_3ph_abc_to_dq(v_abc_right_rev_filter,Global_Data.av.theta_el_right);
		v_dq_meas_right = uz_transformation_3ph_abc_to_dq(v_abc_right,Global_Data.av.theta_el_right);
		v_dq_meas_left = uz_transformation_3ph_abc_to_dq(v_abc_left,Global_Data.av.theta_el_left);
		Global_Data.av.speed_rpm_left = (Global_Data.av.omega_mech_left*60.0f)/(2.0f*UZ_PIf);
		Global_Data.av.speed_rpm_right = (Global_Data.av.omega_mech_right*60.0f)/(2.0f*UZ_PIf);
		Global_Data.av.i_d_left = i_dq_left.d;
		Global_Data.av.i_q_left = i_dq_left.q;
		Global_Data.av.i_d_right = i_dq_right.d;
		Global_Data.av.i_q_right = i_dq_right.q;
		Global_Data.av.v_d_right_meas = v_dq_meas_right.d;
		Global_Data.av.v_q_right_meas = v_dq_meas_right.q;
		Global_Data.av.v_d_left_meas = v_dq_meas_left.d;
		Global_Data.av.v_q_left_meas = v_dq_meas_left.q;

		// check for current limit
		if (fabs(Global_Data.av.i_a_left) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_b_left) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_c_left) > MAX_CURRENT_AMP ||
			fabs(Global_Data.av.i_a_right) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_b_right) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_c_right) > MAX_CURRENT_AMP) {
			ultrazohm_state_machine_set_stop(true);
		}

		// calculate mean temperature values over all measured temperatures of each inverter
		Global_Data.av.mean_temp_inv_left = (Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_L3) * 0.1667;
		Global_Data.av.mean_temp_inv_right = (Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_L3) * 0.1667;
		break;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // if "STOP"
    if (current_state==idle_state)
    {
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_left);
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_right);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_left);
		Global_Data.rasv.n_ref_left = 0.0f;
		Global_Data.rasv.n_ref_left_filt = 0.0f;
		Global_Data.rasv.js_set_n_ref_left = 0.0f;
		Global_Data.rasv.n_ref_right = 0.0f;
		Global_Data.rasv.n_ref_right_filt = 0.0f;
		Global_Data.rasv.js_set_n_ref_right = 0.0f;
		Global_Data.rasv.js_set_i_dq_ref_right.d = 0.0f;
		Global_Data.rasv.js_set_i_dq_ref_right.q = 0.0f;
		Global_Data.rasv.M_ref_left = 0.0f;
		Global_Data.rasv.i_dq_ref_left.d = 0.0f;
		Global_Data.rasv.i_dq_ref_left.q = 0.0f;
		Global_Data.rasv.i_dq_ref_right.d = 0.0f;
		Global_Data.rasv.i_dq_ref_right.q = 0.0f;
		Global_Data.rasv.rc_meas_output.data_valid = 0.0f;
		Global_Data.rasv.rc_meas_output.id_ref_Amps = 0.0f;
		Global_Data.rasv.rc_meas_output.iq_ref_Amps = 0.0f;
		Global_Data.rasv.rc_meas_output.n_ref_rpm = 0.0f;
		i_dq_integrated_error_right.q = 0.0f;
		i_dq_integrated_error_right.d = 0.0f;

		switch(ConApp) {
			case CIL:
				uz_pmsmModel_reset(Global_Data.objects.pmsm_model);
				break;
			case REAL:
				// disable inverters
				uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_left, false);
				uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_right, false);
				// set dutycycle
				uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
				uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);
				Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
				break;
			default:
				break;
			}
    }

    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	switch(ConApp){
    		case CIL:
    			for (uint32_t i = 0; i < 9U; i++) {
    			        observation[i] = 0.0f;
    			    }
    			i_dq_integrated_error_right.d = 0.0f;
    			i_dq_integrated_error_right.q = 0.0f;
    			last_u_d_pu = 0.0f;
    			last_u_q_pu = 0.0f;
    			first_step = true;
    			break;
    		case REAL:

				// enable inverters
				uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_left, true);
				uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_right, true);
				// reset tristate
				uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
				uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
				break;
    		default:
    			break;
    	}
    }


    if (current_state==control_state)
    {

    	// Start: Control algorithm - only if ultrazohm is in control state

    	// Get references
    	Global_Data.rasv.i_dq_ref_right.d = Global_Data.rasv.js_set_i_dq_ref_right.d;
	    Global_Data.rasv.i_dq_ref_right.q = Global_Data.rasv.js_set_i_dq_ref_right.q;
	    i_dq_ref_right.d = Global_Data.rasv.i_dq_ref_right.d;
	    i_dq_ref_right.q = Global_Data.rasv.js_set_i_dq_ref_right.q;
	    Global_Data.rasv.n_ref_left = Global_Data.rasv.js_set_n_ref_left;

		switch(ConSel) {

			case CC:
				filter_compensation_left();
				// control functions for DUT left
				speed_control_left_motor();
				current_control_right_motor();
				break;

			case RL:
				filter_compensation_left();
				speed_control_left_motor();

				if(ddpg_ext_clamping == false){
					i_dq_integrated_error_right.d += (i_dq_error_right.d / RATED_CURRENT);
					i_dq_integrated_error_right.q += (i_dq_error_right.q / RATED_CURRENT);
				}

				i_dq_error_right.d = i_dq_ref_right.d - i_dq_right.d;
				i_dq_error_right.q = i_dq_ref_right.q - i_dq_right.q;

				// calculate observations
				observation[0] = i_dq_right.d / RATED_CURRENT;
				observation[1] = i_dq_right.q / RATED_CURRENT;
				observation[2] = ((Global_Data.av.omega_mech_right * 60.0f) / (2.0f * UZ_PIf)) / RATED_SPEED;
				observation[3] = i_dq_error_right.d / RATED_CURRENT;
				observation[4] = i_dq_error_right.q / RATED_CURRENT;
				observation[5] = i_dq_integrated_error_right.d;
				observation[6] = i_dq_integrated_error_right.q;
				observation[7] = last_u_d_pu;
				observation[8] = last_u_q_pu;

				for (uint32_t i = 0; i < 9U; i++) {
						   uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_acc,observation[i],0U,i);
					  }
					  uz_nn_ff(Global_Data.objects.nn_layer_acc,Global_Data.objects.matrix_input_acc);
					  Global_Data.objects.matrix_output_acc = uz_nn_get_output_data(Global_Data.objects.nn_layer_acc);
					  uz_matrix_multiply_by_scalar(Global_Data.objects.matrix_output_acc, MAX_VOLTAGE);
					  v_dq_rl_right.d = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,0U);
					  v_dq_rl_right.q = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,1U);
					  if (first_step == true) {
					          // Im allerersten Schritt �berschreiben wir die Netz-Panik mit einer sicheren 0V
					          v_dq_rl_right.d = 0.0f;
					          v_dq_rl_right.q = 0.0f;
					          first_step = false;
					  }
					  v_dq_ref_right = uz_CurrentControl_SpaceVector_Limitation(v_dq_rl_right, DC_VOLTAGE, MAX_MODULATION_INDEX, Global_Data.av.omega_mech_right * Global_Data.av.polepairs_right, i_dq_ref_right, &ddpg_ext_clamping);
					  last_u_d_pu = v_dq_ref_right.d / MAX_VOLTAGE;
					  last_u_q_pu = v_dq_ref_right.q / MAX_VOLTAGE;
					  dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_left, Global_Data.av.theta_el_left_advanced);
				break;
			default:
				break;

		}

    	switch(ConApp) {
    		case CIL:
    	    	Global_Data.av.PMSM_inputs.v_d_V = v_dq_ref_right.d;
    	    	Global_Data.av.PMSM_inputs.v_q_V = v_dq_ref_right.q;
    	    	Global_Data.av.PMSM_inputs.omega_mech_1_s = Global_Data.rasv.n_ref_left / 30.0f * UZ_PIf;
    	    	uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_model, Global_Data.av.PMSM_inputs);
    	    	break;

    	    case REAL:
    	    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_left.DutyCycle_A;
    	    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_left.DutyCycle_B;
    	    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_left.DutyCycle_C;
    	    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_right.DutyCycle_A;
    	    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_right.DutyCycle_B;
    	    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_right.DutyCycle_C;
    	    	break;

    	    default:
    	    	break;
    	    }



	/*Global_Data.rasv.halfBridge1DutyCycle = dc_motor_right.a;
	Global_Data.rasv.halfBridge2DutyCycle = dc_motor_right.b;
	Global_Data.rasv.halfBridge3DutyCycle = dc_motor_right.c;*/
	/*Global_Data.rasv.halfBridge4DutyCycle = dc_motor_right.a;
	Global_Data.rasv.halfBridge5DutyCycle = dc_motor_right.b;
	Global_Data.rasv.halfBridge6DutyCycle = dc_motor_right.c;*/
    }


    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

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
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
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


//static void current_control_left_motor() {
//	// calculate reference voltages for current control
//	v_dq_ref_left = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_left, Global_Data.rasv.i_dq_ref_left, i_dq_left, Global_Data.av.v_dc_left, Global_Data.av.omega_mech_left*Global_Data.av.polepairs_left);
//	Global_Data.av.v_d_left = v_dq_ref_left.d;
//	Global_Data.av.v_q_left = v_dq_ref_left.q;
//	Global_Data.av.theta_el_left_advanced =  Global_Data.av.theta_el_left + (1.5f * (Global_Data.av.omega_mech_left*Global_Data.av.polepairs_left) * (1.0f / (UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)));
//	dutycyc_left = uz_Space_Vector_Modulation(v_dq_ref_left, Global_Data.av.v_dc_left, Global_Data.av.theta_el_left_advanced);
//};

//static void speed_control_right_motor() {
//	// filter speed setpoint signal
//	Global_Data.rasv.n_ref_right_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_right, Global_Data.rasv.n_ref_right);
//	// calculate reference torque from speed ctrl of left motor
//	Global_Data.rasv.M_ref_right = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_right, Global_Data.av.omega_mech_right, Global_Data.rasv.n_ref_right_filt);
//	// calculate current setpoints i_dq_ref for left motor
//	Global_Data.rasv.i_dq_ref_right = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_right, Global_Data.av.omega_mech_right, Global_Data.rasv.M_ref_right, Global_Data.av.v_dc_right, i_dq_right);
//    // calculate reference voltages for current control
//    v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, Global_Data.rasv.i_dq_ref_right, i_dq_right, Global_Data.av.v_dc_right, Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right);
//    Global_Data.av.v_d_right = v_dq_ref_right.d;
//    Global_Data.av.v_q_right = v_dq_ref_right.q;
//    // calculate duty cycles from reference dq voltages
//	Global_Data.av.theta_el_right_advanced = Global_Data.av.theta_el_right + (1.5f * (Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right) * (1.0f / (UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)));
//    dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.theta_el_right_advanced);
//};

static void speed_control_left_motor() {
	// filter speed setpoint signal
	Global_Data.rasv.n_ref_left_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_left, Global_Data.rasv.n_ref_left);
	// calculate reference torque from speed ctrl of left motor
	Global_Data.rasv.M_ref_left = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_left, Global_Data.av.omega_mech_left, Global_Data.rasv.n_ref_left_filt);
	// calculate current setpoints i_dq_ref for left motor
	Global_Data.rasv.i_dq_ref_left = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_left, Global_Data.av.omega_mech_left, Global_Data.rasv.M_ref_left, Global_Data.av.v_dc_left, i_dq_left);
	// calculate reference voltages for current control
	v_dq_ref_left = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_left, Global_Data.rasv.i_dq_ref_left, i_dq_left, Global_Data.av.v_dc_left, Global_Data.av.omega_mech_left*Global_Data.av.polepairs_left);
	Global_Data.av.v_d_left = v_dq_ref_left.d;
	Global_Data.av.v_q_left = v_dq_ref_left.q;
	Global_Data.av.theta_el_left_advanced =  Global_Data.av.theta_el_left + (1.5f * (Global_Data.av.omega_mech_left*Global_Data.av.polepairs_left) * (1.0f / (UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)));
	dutycyc_left = uz_Space_Vector_Modulation(v_dq_ref_left, Global_Data.av.v_dc_left, Global_Data.av.theta_el_left_advanced);
};

static void current_control_right_motor() {
	// calculate reference voltages for current control
    v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, Global_Data.rasv.i_dq_ref_right, i_dq_right, Global_Data.av.v_dc_right, Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right);
    Global_Data.av.v_d_right = v_dq_ref_right.d;
    Global_Data.av.v_q_right = v_dq_ref_right.q;
    // calculate duty cycles from reference dq voltages
	Global_Data.av.theta_el_right_advanced = Global_Data.av.theta_el_right + (1.5f * (Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right) * (1.0f / (UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)));
    dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.theta_el_right_advanced);
};

//static void filter_compensation_right(){
//	// calculate Frequency response of the magnitude
//	Global_Data.av.magnitude = sqrt(1.0f + (((Global_Data.av.omega_mech_right * 4.0f) / (2.0f * UZ_PIf * 1750.0f)) * ((Global_Data.av.omega_mech_right * 4.0f) / (2.0f * UZ_PIf * 1750.0f))));
//
//	Global_Data.av.v_abc_right_filter_comp.a = v_abc_right.a * Global_Data.av.magnitude;
//	Global_Data.av.v_abc_right_filter_comp.b = v_abc_right.b * Global_Data.av.magnitude;
//	Global_Data.av.v_abc_right_filter_comp.c = v_abc_right.c * Global_Data.av.magnitude;
//
//	Global_Data.av.phi_right = - atanf((Global_Data.av.omega_mech_right * 4.0f) / (2.0f * UZ_PIf * 1750.0f));
//	Global_Data.av.phi_right = - 1.0f * uz_signals_wrap(Global_Data.av.phi_right, 2.0f*UZ_PIf);
//
//	float theta_new =  Global_Data.av.theta_el_right - Global_Data.av.phi_right;
//	Global_Data.av.v_dq_meas_right_filter_comp =  uz_transformation_3ph_abc_to_dq(Global_Data.av.v_abc_right_filter_comp, theta_new);
//};

static void filter_compensation_left(){
	// calculate Frequency response of the magnitude
	Global_Data.av.magnitude = sqrt(1.0f + (((Global_Data.av.omega_mech_left * 4.0f) / (2.0f * UZ_PIf * 1750.0f)) * ((Global_Data.av.omega_mech_left * 4.0f) / (2.0f * UZ_PIf * 1750.0f))));

	Global_Data.av.v_abc_left_filter_comp.a = v_abc_left.a * Global_Data.av.magnitude;
	Global_Data.av.v_abc_left_filter_comp.b = v_abc_left.b * Global_Data.av.magnitude;
	Global_Data.av.v_abc_left_filter_comp.c = v_abc_left.c * Global_Data.av.magnitude;

	Global_Data.av.phi_left = - atanf((Global_Data.av.omega_mech_left * 4.0f) / (2.0f * UZ_PIf * 1750.0f));
	Global_Data.av.phi_left = - 1.0f * uz_signals_wrap(Global_Data.av.phi_left, 2.0f*UZ_PIf);

	float theta_new =  Global_Data.av.theta_el_left - Global_Data.av.phi_left;
	Global_Data.av.v_dq_meas_left_filter_comp =  uz_transformation_3ph_abc_to_dq(Global_Data.av.v_abc_left_filter_comp, theta_new);
};


