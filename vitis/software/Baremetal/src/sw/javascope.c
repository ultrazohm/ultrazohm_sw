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

// IM observer / FOC diagnostic variables from isr.c
extern float vf_frequency_setpoint_Hz;
extern float vf_ratio_V_per_Hz;
extern float vf_boost_voltage_V;
extern float vf_max_frequency_Hz;
extern float vf_max_voltage_V;
extern float vf_voltage_magnitude_V;
extern float stator_current_fundamental_frequency_Hz;
extern float psi_r_mag_Vs;
extern float omega_s_rad_s;
extern float kf_innov_alpha;
extern float kf_innov_beta;
extern float kf_q_i;
extern float kf_q_psi;
extern float kf_r_i;
extern float id_meas_raw_dq;
extern float iq_meas_raw_dq;
extern float ud_pi_V;
extern float uq_pi_V;
extern float ud_decoup_V;
extern float uq_decoup_V;
extern float ud_res_V;
extern float uq_res_V;
extern float omega_slip_rad_s_diag;
extern float speed_ref_rpm;
extern float id_ref_A;
extern float iq_ref_A;
extern float js_error_vdc_im;
extern float js_error_vdc_va;
extern float js_error_max_current_va;

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
	js_ch_observable[JSO_pwm_freq]				= &data->av.pwm_freq;
	js_ch_observable[JSO_duty_cycle]			= &data->av.duty_cycle;
	js_ch_observable[JSO_temp]			  		= &data->av.temp;
	js_ch_observable[JSO_OCP]			  		= &data->av.OCP_INVERTER;
	js_ch_observable[JSO_FAULT]			  		= &data->av.FAULT_INVERTER;
	js_ch_observable[JSO_pwm_frequency_hz]		= &data->av.pwm_frequency_hz;
	js_ch_observable[JSO_isr_samplerate_s]		= &data->av.isr_samplerate_s;
	js_ch_observable[JSO_IM_ia]				= &data->av.IM_ia;
	js_ch_observable[JSO_IM_ib]				= &data->av.IM_ib;
	js_ch_observable[JSO_IM_ic]				= &data->av.IM_ic;
	js_ch_observable[JSO_IM_vdc]				= &data->av.IM_vdc;
	js_ch_observable[JSO_IM_mechanicalRotorSpeed] = &data->av.IM_mechanicalRotorSpeed;
	js_ch_observable[JSO_IM_mechanicalRotorSpeed_filtered] = &data->av.IM_mechanicalRotorSpeed_filtered;
	js_ch_observable[JSO_IM_mechanicalPosition] = &data->av.IM_mechanicalPosition;
	js_ch_observable[JSO_IM_I_d]				= &data->av.IM_I_d;
	js_ch_observable[JSO_IM_I_q]				= &data->av.IM_I_q;
	js_ch_observable[JSO_IM_theta_elec]		= &data->av.IM_theta_elec;
	js_ch_observable[JSO_IM_theta_mech]		= &data->av.IM_theta_mech;
	js_ch_observable[JSO_IM_theta_offset]		= &data->av.IM_theta_offset;
	js_ch_observable[JSO_IM_theta_elec_advanced] = &data->av.IM_theta_elec_advanced;
	js_ch_observable[JSO_VA_polepairs]			= &data->av.VA_polepairs;
	js_ch_observable[JSO_VA_ia]					= &data->av.VA_ia;
	js_ch_observable[JSO_VA_ib]					= &data->av.VA_ib;
	js_ch_observable[JSO_VA_ic]					= &data->av.VA_ic;
	js_ch_observable[JSO_VA_vd]					= &data->av.VA_vd;
	js_ch_observable[JSO_VA_vq]					= &data->av.VA_vq;
	js_ch_observable[JSO_VA_vdc]				= &data->av.VA_vdc;
	js_ch_observable[JSO_VA_mechanicalRotorSpeed] = &data->av.VA_mechanicalRotorSpeed;
	js_ch_observable[JSO_VA_mechanicalRotorSpeed_filtered] = &data->av.VA_mechanicalRotorSpeed_filtered;
	js_ch_observable[JSO_VA_mechanicalPosition] = &data->av.VA_mechanicalPosition;
	js_ch_observable[JSO_VA_omega_mech]			= &data->av.VA_omega_mech;
	js_ch_observable[JSO_VA_I_d]				= &data->av.VA_I_d;
	js_ch_observable[JSO_VA_I_q]				= &data->av.VA_I_q;
	js_ch_observable[JSO_VA_theta_elec]			= &data->av.VA_theta_elec;
	js_ch_observable[JSO_VA_theta_mech]			= &data->av.VA_theta_mech;
	js_ch_observable[JSO_VA_theta_offset]		= &data->av.VA_theta_offset;
	js_ch_observable[JSO_VA_theta_elec_advanced] = &data->av.VA_theta_elec_advanced;
	js_ch_observable[JSO_VA_i_d_ref]			= &data->rasv.i_dq_ref_VA.d;
	js_ch_observable[JSO_VA_i_q_ref]			= &data->rasv.i_dq_ref_VA.q;
	// Debug V/f
	js_ch_observable[JSO_DUT1]			= &data->rasv.halfBridge1DutyCycle;
	js_ch_observable[JSO_DUT2]			= &data->rasv.halfBridge2DutyCycle;
	js_ch_observable[JSO_DUT3]			= &data->rasv.halfBridge3DutyCycle;
	js_ch_observable[JSO_UF_voltage_magnitude_V] = &vf_voltage_magnitude_V;

	// IM observer / FOC diagnostics
	js_ch_observable[JSO_IM_psi_r_mag]			= &psi_r_mag_Vs;
	js_ch_observable[JSO_IM_omega_s_rad_s]		= &omega_s_rad_s;
	js_ch_observable[JSO_IM_kf_innov_alpha]		= &kf_innov_alpha;
	js_ch_observable[JSO_IM_kf_innov_beta]		= &kf_innov_beta;
	js_ch_observable[JSO_IM_id_raw]				= &id_meas_raw_dq;
	js_ch_observable[JSO_IM_iq_raw]				= &iq_meas_raw_dq;
	js_ch_observable[JSO_IM_ud_pi]				= &ud_pi_V;
	js_ch_observable[JSO_IM_uq_pi]				= &uq_pi_V;
	js_ch_observable[JSO_IM_ud_decoup]			= &ud_decoup_V;
	js_ch_observable[JSO_IM_uq_decoup]			= &uq_decoup_V;
	js_ch_observable[JSO_IM_ud_res]				= &ud_res_V;
	js_ch_observable[JSO_IM_uq_res]				= &uq_res_V;
	js_ch_observable[JSO_IM_omega_slip]			= &omega_slip_rad_s_diag;
	js_ch_observable[JSO_IM_speed_ref]			= &speed_ref_rpm;
	js_ch_observable[JSO_IM_speed]			= &data->av.IM_mechanicalRotorSpeed;
	js_ch_observable[JSO_IM_vd]				= &data->av.IM_vd;
	js_ch_observable[JSO_IM_vq]				= &data->av.IM_vq;
	js_ch_observable[JSO_IM_id_ref]			= &id_ref_A;
	js_ch_observable[JSO_IM_iq_ref]			= &iq_ref_A;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_u_d] 			        = &(data->av.VA_vd);
	js_slowDataArray[JSSD_FLOAT_u_q] 			        = &(data->av.VA_vq);
	js_slowDataArray[JSSD_FLOAT_i_d] 			        = &(data->av.VA_I_d);
	js_slowDataArray[JSSD_FLOAT_i_q] 			        = &(data->av.VA_I_q);
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.VA_mechanicalRotorSpeed);
	js_slowDataArray[JSSD_FLOAT_torque] 		        = &zerovalue;
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_IM_vdc]				= &(data->av.IM_vdc);
	js_slowDataArray[JSSD_FLOAT_VA_vdc]				= &(data->av.VA_vdc);
	js_slowDataArray[JSSD_FLOAT_VA_i_d]				= &(data->av.VA_I_d);
	js_slowDataArray[JSSD_FLOAT_VA_i_q]				= &(data->av.VA_I_q);
	js_slowDataArray[JSSD_FLOAT_VA_speed]				= &(data->av.VA_mechanicalRotorSpeed);
	js_slowDataArray[JSSD_FLOAT_VA_theta_elec]			= &(data->av.VA_theta_elec);
	js_slowDataArray[JSSD_FLOAT_IM_ia]					= &(data->av.IM_ia);
	js_slowDataArray[JSSD_FLOAT_IM_ib]					= &(data->av.IM_ib);
	js_slowDataArray[JSSD_FLOAT_IM_ic]					= &(data->av.IM_ic);
	js_slowDataArray[JSSD_FLOAT_VA_ia]					= &(data->av.VA_ia);
	js_slowDataArray[JSSD_FLOAT_VA_ib]					= &(data->av.VA_ib);
	js_slowDataArray[JSSD_FLOAT_VA_ic]					= &(data->av.VA_ic);
	// KF tuning
	js_slowDataArray[JSSD_FLOAT_kf_q_i]				= &kf_q_i;
	js_slowDataArray[JSSD_FLOAT_kf_q_psi]				= &kf_q_psi;
	js_slowDataArray[JSSD_FLOAT_kf_r_i]				= &kf_r_i;
	// V/f parameters
	js_slowDataArray[JSSD_FLOAT_vf_frequency_setpoint_Hz]	= &vf_frequency_setpoint_Hz;
	js_slowDataArray[JSSD_FLOAT_vf_ratio_V_per_Hz]			= &vf_ratio_V_per_Hz;
	js_slowDataArray[JSSD_FLOAT_vf_boost_voltage_V]			= &vf_boost_voltage_V;
	js_slowDataArray[JSSD_FLOAT_vf_max_frequency_Hz]		= &vf_max_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_vf_max_voltage_V]			= &vf_max_voltage_V;
	js_slowDataArray[JSSD_FLOAT_vf_applied_voltage_magnitude_V]	= &vf_voltage_magnitude_V;
	// IM observer diagnostics
	js_slowDataArray[JSSD_FLOAT_psi_r_mag]				= &psi_r_mag_Vs;
	js_slowDataArray[JSSD_FLOAT_IM_id]					= &(data->av.IM_I_d);
	js_slowDataArray[JSSD_FLOAT_IM_iq]					= &(data->av.IM_I_q);
	js_slowDataArray[JSSD_FLOAT_error_vdc_im]			= &js_error_vdc_im;
	js_slowDataArray[JSSD_FLOAT_error_vdc_va]			= &js_error_vdc_va;
	js_slowDataArray[JSSD_FLOAT_error_max_current_va]	= &js_error_max_current_va;
	js_slowDataArray[JSSD_FLOAT_FreqReadback]			= &stator_current_fundamental_frequency_Hz;

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
	Xil_DCacheFlushRange(MEM_SHARED_START_OCM_BANK_3_JAVASCOPE, JAVASCOPE_DATA_SIZE_2POW);

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
