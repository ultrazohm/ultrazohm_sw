/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel, Philipp Löhdefink
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
*******************************************************************************/

#include "../main.h"
#include "../defines.h"
#include "../include/javascope.h"
#include "../include/ipc_ARM.h"
#include "xil_cache.h"
#include "../include/error_checks.h"

// maximum number of while loops in the polling function for the acknowledge flag
#define POLL_FOR_ACK_TIMEOUT_COUNT	1000
// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)
uint32_t cache_size_to_flush = 0U;
//Variables for JavaScope
static float zerovalue = 0.0;
static float *js_slowDataArray[JSSD_ENDMARKER];
float *js_ch_observable[JSO_ENDMARKER];
float *js_ch_selected[JS_CHANNELS];

static float lifecheck;
static float ISR_execution_time_us;
static float ISR_period_us;
static float System_UpTime_seconds;
static float System_UpTime_ms;

uint32_t pollErrorCnt = 0U;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

//Initialize the Interrupt structure
extern XIpiPsu IPI_instance;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!


int JavaScope_initialize(DS_Data* data)
{
	int Status = 0;
	//Initialize all variables with zero
	for (int j=0; j<JSO_ENDMARKER; j++){
		js_ch_observable[j] = &zerovalue;
	}

	for(int j=0; j<JS_CHANNELS; j++){
		js_ch_selected[j] = &zerovalue;
	}

	for (int j=0; j<JSSD_ENDMARKER; j++){
		js_slowDataArray[j] = &zerovalue;
	}

	// Store every observable signal into the Pointer-Array.
	// With the JavaScope, signals can be displayed simultaneously
	// Changing between the observable signals is possible at runtime in the JavaScope.
	// the addresses in Global_Data do not change during runtime, this can be done in the init
	js_ch_observable[JSO_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   			= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]			= &ISR_period_us;
	js_ch_observable[JSO_IM_I_A]=&data->av.im_i_a_A;
	js_ch_observable[JSO_IM_I_B]=&data->av.im_i_b_A;
	js_ch_observable[JSO_IM_I_C]=&data->av.im_i_c_A;
	js_ch_observable[JSO_IM_V_DC]=&data->av.im_v_dc_V;
	js_ch_observable[JSO_IM_SPEED_RPM]=&data->av.im_speed_rpm;
	js_ch_observable[JSO_IM_FREQUENCY_HZ]=&data->av.im_control_actual.u_f_command_frequency_Hz;
	js_ch_observable[JSO_IM_VOLTAGE_V]=&data->av.im_control_actual.u_f_applied_voltage_V;
	js_ch_observable[JSO_IM_I_D]=&data->av.im_control_actual.i_dq_A.d;
	js_ch_observable[JSO_IM_I_Q]=&data->av.im_control_actual.i_dq_A.q;
	js_ch_observable[JSO_IM_I_D_RAW]=&data->av.im_control_actual.i_dq_raw_A.d;
	js_ch_observable[JSO_IM_I_Q_RAW]=&data->av.im_control_actual.i_dq_raw_A.q;
	js_ch_observable[JSO_IM_I_D_REF]=&data->rasv.im_i_d_reference_A;
	js_ch_observable[JSO_IM_I_Q_REF]=&data->rasv.im_i_q_reference_A;
	js_ch_observable[JSO_IM_FLUX_VS]=&data->av.im_control_actual.rotor_flux_magnitude_Vs;
	js_ch_observable[JSO_IM_FLUX_ANGLE_RAD]=&data->av.im_control_actual.rotor_flux_angle_rad;
	js_ch_observable[JSO_IM_ROTOR_ELECTRICAL_ANGLE_RAD]=&data->av.im_control_actual.rotor_electrical_angle_rad;
	js_ch_observable[JSO_IM_FLUX_ROTOR_ANGLE_DIFFERENCE_RAD]=&data->av.im_control_actual.flux_rotor_angle_difference_rad;
	js_ch_observable[JSO_IM_ROTOR_ELECTRICAL_FREQUENCY_HZ]=&data->av.im_control_actual.rotor_electrical_frequency_Hz;
	js_ch_observable[JSO_IM_SLIP_FREQUENCY_HZ]=&data->av.im_control_actual.slip_frequency_Hz;
	js_ch_observable[JSO_IM_SLIP_PERCENT]=&data->av.im_control_actual.slip_percent;
	js_ch_observable[JSO_IM_STATOR_FREQUENCY_HZ]=&data->av.im_control_actual.stator_frequency_Hz;
	js_ch_observable[JSO_IM_DUTY_A]=&data->rasv.pwm_2L_0_halfBridgeDutyCycle_1;
	js_ch_observable[JSO_IM_DUTY_B]=&data->rasv.pwm_2L_0_halfBridgeDutyCycle_2;
	js_ch_observable[JSO_IM_DUTY_C]=&data->rasv.pwm_2L_0_halfBridgeDutyCycle_3;
	js_ch_observable[JSO_D3_INPUT_LOOPBACK_UINT32] = &data->av.d3_input_loopback_uint32;
	js_ch_observable[JSO_INVERTER_TEMPERATURE_DEG_C] = &data->av.inverter_temperature_degC;
	js_ch_observable[JSO_INVERTER_TEMPERATURE_PWM_DUTY_CYCLE_PERCENT] = &data->av.inverter_temperature_pwm_duty_cycle_percent;
	js_ch_observable[JSO_INVERTER_TEMPERATURE_PWM_FREQUENCY_HZ] = &data->av.inverter_temperature_pwm_frequency_Hz;
	js_ch_observable[JSO_IM_CURRENT_OFFSET_A_A] = &data->av.im_current_offset_a_A;
	js_ch_observable[JSO_IM_CURRENT_OFFSET_B_A] = &data->av.im_current_offset_b_A;
	js_ch_observable[JSO_IM_CURRENT_OFFSET_C_A] = &data->av.im_current_offset_c_A;
	js_ch_observable[JSO_IM_CURRENT_OFFSET_PROGRESS_PERCENT] = &data->av.im_current_offset_progress_percent;
	js_ch_observable[JSO_IM_CURRENT_OFFSET_MAX_STDDEV_A] = &data->av.im_current_offset_max_stddev_A;
	js_ch_observable[JSO_IM_CURRENT_SUM_ERROR_A] = &data->av.im_current_sum_error_A;
	js_ch_observable[JSO_IM_CURRENT_OFFSET_VALID] = &data->av.im_current_offset_valid;
	js_ch_observable[JSO_IM_ROTOR_FLUX_VALID] = &data->av.im_control_actual.rotor_flux_valid;
	js_ch_observable[JSO_IM_SLIP_FREQUENCY_LIMITED] = &data->av.im_control_actual.slip_frequency_limited;
	js_ch_observable[JSO_IM_FLUX_ANGLE_STEP_RAD] = &data->av.im_control_actual.flux_angle_step_rad;
	js_ch_observable[JSO_IM_FLUX_ANGLE_STEP_VIOLATION] = &data->av.im_control_actual.flux_angle_step_violation;
	js_ch_observable[JSO_IM_PHASE_CURRENT_SUM_A] = &data->av.im_control_actual.phase_current_sum_A;
	js_ch_observable[JSO_IM_PHASE_CURRENT_SUM_VIOLATION] = &data->av.im_control_actual.phase_current_sum_violation;
	js_ch_observable[JSO_IM_VOLTAGE_VECTOR_MAGNITUDE_V] = &data->av.im_control_actual.voltage_vector_magnitude_V;
	js_ch_observable[JSO_IM_VOLTAGE_VECTOR_LIMIT_V] = &data->av.im_control_actual.voltage_vector_limit_V;
	js_ch_observable[JSO_IM_VOLTAGE_VECTOR_SATURATED] = &data->av.im_control_actual.voltage_vector_saturated;
	js_ch_observable[JSO_IM_ESTIMATED_ELECTRICAL_TORQUE_NM] = &data->av.im_control_actual.estimated_electrical_torque_Nm;
	js_ch_observable[JSO_IM_ROTOR_ELECTRICAL_ANGULAR_SPEED_RAD_PER_S] = &data->av.im_control_actual.rotor_electrical_angular_speed_rad_per_s;
	js_ch_observable[JSO_IM_SLIP_ANGULAR_FREQUENCY_RAD_PER_S] = &data->av.im_control_actual.slip_angular_frequency_rad_per_s;
	js_ch_observable[JSO_IM_STATOR_ANGULAR_FREQUENCY_RAD_PER_S] = &data->av.im_control_actual.stator_angular_frequency_rad_per_s;
	js_ch_observable[JSO_IM_KALMAN_INNOVATION_ALPHA_A] = &data->av.im_control_actual.kalman_innovation_alpha_A;
	js_ch_observable[JSO_IM_KALMAN_INNOVATION_BETA_A] = &data->av.im_control_actual.kalman_innovation_beta_A;
	js_ch_observable[JSO_IM_CURRENT_PI_V_D] = &data->av.im_control_actual.current_pi_voltage_dq_V.d;
	js_ch_observable[JSO_IM_CURRENT_PI_V_Q] = &data->av.im_control_actual.current_pi_voltage_dq_V.q;
	js_ch_observable[JSO_IM_DECOUPLING_V_D] = &data->av.im_control_actual.decoupling_voltage_dq_V.d;
	js_ch_observable[JSO_IM_DECOUPLING_V_Q] = &data->av.im_control_actual.decoupling_voltage_dq_V.q;
	js_ch_observable[JSO_IM_RESONANT_V_D] = &data->av.im_control_actual.resonant_voltage_dq_V.d;
	js_ch_observable[JSO_IM_RESONANT_V_Q] = &data->av.im_control_actual.resonant_voltage_dq_V.q;
	js_ch_observable[JSO_IM_REFERENCE_V_D] = &data->av.im_control_reference.v_dq_V.d;
	js_ch_observable[JSO_IM_REFERENCE_V_Q] = &data->av.im_control_reference.v_dq_V.q;
	js_ch_observable[JSO_IM_KF_STATE_I_ALPHA_A] = &data->av.im_observer_diagnostics.state[0];
	js_ch_observable[JSO_IM_KF_STATE_I_BETA_A] = &data->av.im_observer_diagnostics.state[1];
	js_ch_observable[JSO_IM_KF_STATE_PSI_ALPHA_VS] = &data->av.im_observer_diagnostics.state[2];
	js_ch_observable[JSO_IM_KF_STATE_PSI_BETA_VS] = &data->av.im_observer_diagnostics.state[3];
	js_ch_observable[JSO_IM_DETERMINISTIC_FLUX_ALPHA_VS] = &data->av.im_observer_diagnostics.deterministic_flux_alpha_Vs;
	js_ch_observable[JSO_IM_DETERMINISTIC_FLUX_BETA_VS] = &data->av.im_observer_diagnostics.deterministic_flux_beta_Vs;
	js_ch_observable[JSO_IM_KALMAN_STATOR_FREQUENCY_HZ] = &data->av.im_observer_diagnostics.kalman_stator_frequency_Hz;
	js_ch_observable[JSO_IM_DETERMINISTIC_STATOR_FREQUENCY_HZ] = &data->av.im_observer_diagnostics.deterministic_stator_frequency_Hz;
	js_ch_observable[JSO_IM_VALIDATION_PROFILE_STAGE] = &data->av.im_validation_profile_stage;
	js_ch_observable[JSO_IM_VALIDATION_PROFILE_ELAPSED_S] = &data->rasv.im_validation_profile_elapsed_s;
	js_ch_observable[JSO_IM_VALIDATION_OBSERVER_MODE] = &data->av.im_validation_observer_mode;

	/* Default FastData layout for reproducible three-observer validation. */
	js_ch_selected[0] = js_ch_observable[JSO_IM_VALIDATION_PROFILE_ELAPSED_S];
	js_ch_selected[1] = js_ch_observable[JSO_IM_VALIDATION_OBSERVER_MODE];
	js_ch_selected[2] = js_ch_observable[JSO_IM_VALIDATION_PROFILE_STAGE];
	js_ch_selected[3] = js_ch_observable[JSO_IM_FREQUENCY_HZ];
	js_ch_selected[4] = js_ch_observable[JSO_IM_SPEED_RPM];
	js_ch_selected[5] = js_ch_observable[JSO_IM_I_A];
	js_ch_selected[6] = js_ch_observable[JSO_IM_I_B];
	js_ch_selected[7] = js_ch_observable[JSO_IM_I_C];
	js_ch_selected[8] = js_ch_observable[JSO_IM_FLUX_VS];
	js_ch_selected[9] = js_ch_observable[JSO_IM_FLUX_ANGLE_RAD];
	js_ch_selected[10] = js_ch_observable[JSO_IM_STATOR_FREQUENCY_HZ];
	js_ch_selected[11] = js_ch_observable[JSO_IM_ROTOR_ELECTRICAL_FREQUENCY_HZ];
	js_ch_selected[12] = js_ch_observable[JSO_IM_SLIP_FREQUENCY_HZ];
	js_ch_selected[13] = js_ch_observable[JSO_IM_KALMAN_INNOVATION_ALPHA_A];
	js_ch_selected[14] = js_ch_observable[JSO_IM_KALMAN_INNOVATION_BETA_A];
	js_ch_selected[15] = js_ch_observable[JSO_IM_I_D];
	js_ch_selected[16] = js_ch_observable[JSO_IM_I_Q];
	js_ch_selected[17] = js_ch_observable[JSO_IM_ROTOR_FLUX_VALID];
	js_ch_selected[18] = js_ch_observable[JSO_IM_FLUX_ANGLE_STEP_RAD];
	js_ch_selected[19] = js_ch_observable[JSO_IM_PHASE_CURRENT_SUM_A];

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_Error_Code] = &js_error_code;
	js_slowDataArray[JSSD_FLOAT_IM_Speed_RPM] = &data->av.im_speed_rpm;
	js_slowDataArray[JSSD_FLOAT_IM_V_DC] = &data->av.im_v_dc_V;
	js_slowDataArray[JSSD_FLOAT_IM_Slip_Percent] = &data->av.im_control_actual.slip_percent;
	js_slowDataArray[JSSD_FLOAT_IM_Frequency_Hz] = &data->av.im_control_actual.u_f_command_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_IM_Voltage_V] = &data->av.im_control_actual.u_f_applied_voltage_V;
	js_slowDataArray[JSSD_FLOAT_Inverter_Temperature_DegC] = &data->av.inverter_temperature_degC;
	js_slowDataArray[JSSD_FLOAT_IM_I_D] = &data->av.im_control_actual.i_dq_A.d;
	js_slowDataArray[JSSD_FLOAT_IM_I_Q] = &data->av.im_control_actual.i_dq_A.q;
	js_slowDataArray[JSSD_FLOAT_IM_I_D_Raw] = &data->av.im_control_actual.i_dq_raw_A.d;
	js_slowDataArray[JSSD_FLOAT_IM_I_Q_Raw] = &data->av.im_control_actual.i_dq_raw_A.q;
	js_slowDataArray[JSSD_FLOAT_IM_Flux_Vs] = &data->av.im_control_actual.rotor_flux_magnitude_Vs;
	js_slowDataArray[JSSD_FLOAT_IM_Flux_Angle_Rad] = &data->av.im_control_actual.rotor_flux_angle_rad;
	js_slowDataArray[JSSD_FLOAT_IM_Rotor_Electrical_Angle_Rad] = &data->av.im_control_actual.rotor_electrical_angle_rad;
	js_slowDataArray[JSSD_FLOAT_IM_Flux_Rotor_Angle_Difference_Rad] = &data->av.im_control_actual.flux_rotor_angle_difference_rad;
	js_slowDataArray[JSSD_FLOAT_IM_Rotor_Electrical_Frequency_Hz] = &data->av.im_control_actual.rotor_electrical_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_Inverter_Hardware_Overcurrent] = &data->av.inverter_hardware_overcurrent;
	js_slowDataArray[JSSD_FLOAT_IM_Slip_Frequency_Hz] = &data->av.im_control_actual.slip_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_IM_Stator_Frequency_Hz] = &data->av.im_control_actual.stator_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_IM_I_D_Reference_A] = &data->rasv.im_i_d_reference_A;
	js_slowDataArray[JSSD_FLOAT_IM_I_Q_Reference_A] = &data->rasv.im_i_q_reference_A;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_SOR_Status] = &data->av.im_control_violation_code;
	js_slowDataArray[JSSD_FLOAT_IM_Current_Offset_Valid] = &data->av.im_current_offset_valid;
	js_slowDataArray[JSSD_FLOAT_IM_Rotor_Flux_Valid] = &data->av.im_control_actual.rotor_flux_valid;
	js_slowDataArray[JSSD_FLOAT_IM_Slip_Frequency_Limited] = &data->av.im_control_actual.slip_frequency_limited;
	js_slowDataArray[JSSD_FLOAT_IM_Flux_Angle_Step_Violation] = &data->av.im_control_actual.flux_angle_step_violation;
	js_slowDataArray[JSSD_FLOAT_IM_Phase_Current_Sum_Violation] = &data->av.im_control_actual.phase_current_sum_violation;
	js_slowDataArray[JSSD_FLOAT_IM_Voltage_Vector_Saturated] = &data->av.im_control_actual.voltage_vector_saturated;
	js_slowDataArray[JSSD_FLOAT_IM_Estimated_Electrical_Torque_Nm] = &data->av.im_control_actual.estimated_electrical_torque_Nm;
	js_slowDataArray[JSSD_FLOAT_IM_KF_S_00] = &data->av.im_observer_diagnostics.innovation_covariance[0][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_S_01] = &data->av.im_observer_diagnostics.innovation_covariance[0][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_S_10] = &data->av.im_observer_diagnostics.innovation_covariance[1][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_S_11] = &data->av.im_observer_diagnostics.innovation_covariance[1][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_00] = &data->av.im_observer_diagnostics.covariance[0][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_01] = &data->av.im_observer_diagnostics.covariance[0][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_02] = &data->av.im_observer_diagnostics.covariance[0][2];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_03] = &data->av.im_observer_diagnostics.covariance[0][3];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_10] = &data->av.im_observer_diagnostics.covariance[1][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_11] = &data->av.im_observer_diagnostics.covariance[1][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_12] = &data->av.im_observer_diagnostics.covariance[1][2];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_13] = &data->av.im_observer_diagnostics.covariance[1][3];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_20] = &data->av.im_observer_diagnostics.covariance[2][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_21] = &data->av.im_observer_diagnostics.covariance[2][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_22] = &data->av.im_observer_diagnostics.covariance[2][2];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_23] = &data->av.im_observer_diagnostics.covariance[2][3];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_30] = &data->av.im_observer_diagnostics.covariance[3][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_31] = &data->av.im_observer_diagnostics.covariance[3][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_32] = &data->av.im_observer_diagnostics.covariance[3][2];
	js_slowDataArray[JSSD_FLOAT_IM_KF_P_33] = &data->av.im_observer_diagnostics.covariance[3][3];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_00] = &data->av.im_observer_diagnostics.kalman_gain[0][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_01] = &data->av.im_observer_diagnostics.kalman_gain[0][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_10] = &data->av.im_observer_diagnostics.kalman_gain[1][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_11] = &data->av.im_observer_diagnostics.kalman_gain[1][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_20] = &data->av.im_observer_diagnostics.kalman_gain[2][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_21] = &data->av.im_observer_diagnostics.kalman_gain[2][1];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_30] = &data->av.im_observer_diagnostics.kalman_gain[3][0];
	js_slowDataArray[JSSD_FLOAT_IM_KF_K_31] = &data->av.im_observer_diagnostics.kalman_gain[3][1];
	js_slowDataArray[JSSD_FLOAT_IM_Measurement_V_A] = &data->av.im_control_measurements.v_abc_V.a;
	js_slowDataArray[JSSD_FLOAT_IM_Measurement_V_B] = &data->av.im_control_measurements.v_abc_V.b;
	js_slowDataArray[JSSD_FLOAT_IM_Measurement_V_C] = &data->av.im_control_measurements.v_abc_V.c;
	js_slowDataArray[JSSD_FLOAT_IM_Measurement_I_DC] = &data->av.im_control_measurements.i_dc_A;
	js_slowDataArray[JSSD_FLOAT_IM_Measurement_Rotor_Angle_Rad] = &data->av.im_control_measurements.rotor_mechanical_angle_rad;
	js_slowDataArray[JSSD_FLOAT_IM_Reference_Speed_RPM] = &data->av.im_control_reference.speed_rpm;
/* Project Wizard BEGIN: javascope_slowdata_pointers */
/* Project Wizard END: javascope_slowdata_pointers */

	return Status;
}


void JavaScope_update(DS_Data* data){

	// create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START_OCM_BANK_3_JAVASCOPE
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
	struct APU_to_RPU_t Received_Data_from_A53 = {0};
	// create pointers to user data variables located in OCM Bank 1 and 2
	struct RPU_to_APU_user_data_t volatile * const rpu_to_apu_user_data = (struct RPU_to_APU_user_data_t*)MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU;
	struct APU_to_RPU_user_data_t volatile * const apu_to_rpu_user_data = (struct APU_to_RPU_user_data_t*)MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU;
	static int js_cnt_slowData=0;
	int status = XST_SUCCESS;

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	// write data to a53 in shared memory and flush cache
	rpu_to_apu_user_data->slowDataCounter = js_cnt_slowData; //just an example
	// add further data...

	Xil_DCacheFlushRange(MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU, CACHE_FLUSH_SIZE_RPU_TO_APU);
#endif

	// Refresh variables since the init function sets the javascope to point to a address, but the variables are never refreshed
	lifecheck 				= uz_SystemTime_GetInterruptCounter() % 1000;
	ISR_execution_time_us	= uz_SystemTime_GetIsrExectionTimeInUs();
	ISR_period_us			= uz_SystemTime_GetIsrPeriodInUs();
	System_UpTime_seconds   = uz_SystemTime_GetUptimeInSec();
	System_UpTime_ms		= uz_SystemTime_GetUptimeInMs();

	// write data to shared memory
	for(int j=0; j<JS_CHANNELS; j++){
		javascope_data->scope_ch[j] = *js_ch_selected[j];
	}
	javascope_data->slowDataID 		= js_cnt_slowData;
	javascope_data->slowDataContent = *js_slowDataArray[js_cnt_slowData];
	javascope_data->status 			= js_status_BareToRTOS;

	// flush data cache of shared memory region to make sure shared memory is updated
	Xil_DCacheFlushRange(MEM_SHARED_START_OCM_BANK_3_JAVASCOPE, JAVASCOPE_DATA_SIZE);

	//Send an interrupt to APU
	status = XIpiPsu_TriggerIpi(&IPI_instance,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI Trigger failed\r\n");
	}

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	//Poll Acknowledgment of IPI
	status = XIpiPsu_PollForAck(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, POLL_FOR_ACK_TIMEOUT_COUNT);
	if(status != (u32)XST_SUCCESS) {
		pollErrorCnt++;
	}
#endif

	u32 ControlData_length = sizeof(Received_Data_from_A53)/sizeof(float); // XIpiPsu_WriteMessage expects number of 32bit values as message length

	//Afterwards the acknowledge a message from the APU can be read/checked, if a53 is enabled for external calculations of the r5 we wait for the acknowledge flag,
	//if not, we don't do it in order to guarantee that the control-ISR never waits and always runs! -> This is due to the Polling of the acknowledge flag.
	status = XIpiPsu_ReadMessage(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, (u32*)(&Received_Data_from_A53), ControlData_length, XIPIPSU_BUF_TYPE_RESP);

	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI reading from A53 failed\r\n");
	}

	js_cnt_slowData++;
	if (js_cnt_slowData >= JSSD_ENDMARKER){
		js_cnt_slowData = 0;
	}

	i_fetchDataLifeCheck++; //LiveCheck
	if(i_fetchDataLifeCheck > 10000){
		i_fetchDataLifeCheck =0;
	}

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	//invalidate cache and read data from a53 shared memory
	Xil_DCacheInvalidateRange(MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU, CACHE_FLUSH_SIZE_APU_TO_RPU);
	// get data from apu_to_rpu_user_data struct and use it
	 data->av.slowDataCounter = apu_to_rpu_user_data->slowDataCounter; //just an example
#endif

	ipc_Control_func(Received_Data_from_A53.id, Received_Data_from_A53.value, data);

}
