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
#include "../Codegen/uz_codegen.h"

// maximum number of while loops in the polling function for the acknowledge flag
#define POLL_FOR_ACK_TIMEOUT_COUNT	1000
// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)

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
extern float f_mod_wait_cnt;

uint32_t pollErrorCnt = 0U;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

extern uz_codegen codegenInstance;

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
	js_ch_observable[JSO_mech_Speed_rpm_left]	= &data->av.resolver_pl_outputs_d5_1.n_mech_rpm;
	js_ch_observable[JSO_mech_Speed_rpm_right]	= &data->av.resolver_pl_outputs_d5_2.n_mech_rpm;
	js_ch_observable[JSO_ia_left] 			= &data->av.i_a_d1;
	js_ch_observable[JSO_ib_left] 			= &data->av.i_b_d1;
	js_ch_observable[JSO_ic_left] 			= &data->av.i_c_d1;
	js_ch_observable[JSO_ia_right] 			= &data->av.i_a_d2;
	js_ch_observable[JSO_ib_right] 			= &data->av.i_b_d2;
	js_ch_observable[JSO_ic_right] 			= &data->av.i_c_d2;
	js_ch_observable[JSO_va_left] 			= &data->av.v_a_d1;
	js_ch_observable[JSO_vb_left] 			= &data->av.v_b_d1;
	js_ch_observable[JSO_vc_left] 			= &data->av.v_c_d1;
	js_ch_observable[JSO_va_right] 			= &data->av.v_a_d2;
	js_ch_observable[JSO_vb_right] 			= &data->av.v_b_d2;
	js_ch_observable[JSO_vc_right] 			= &data->av.v_c_d2;
	js_ch_observable[JSO_id_left] 			= &data->av.i_d_0;
	js_ch_observable[JSO_iq_left] 			= &data->av.i_q_0;
	js_ch_observable[JSO_id_right] 			= &data->av.i_d_1;
	js_ch_observable[JSO_iq_right] 			= &data->av.i_q_1;
	js_ch_observable[JSO_theta_el_left] 	= &data->av.resolver_pl_outputs_d5_1.position_el_2pi;
	js_ch_observable[JSO_theta_el_right] 	= &data->av.resolver_pl_outputs_d5_2.position_el_2pi;
	js_ch_observable[JSO_theta_mech_left] 	= &data->av.resolver_pl_outputs_d5_1.position_mech_2pi;
	js_ch_observable[JSO_theta_mech_right] 	= &data->av.resolver_pl_outputs_d5_2.position_mech_2pi;
	js_ch_observable[JSO_vd_left]			= &data->av.v_d_0;
	js_ch_observable[JSO_vd_left_filt]		= &data->av.v_d_0_filt;
	js_ch_observable[JSO_vq_left]			= &data->av.v_q_0;
	js_ch_observable[JSO_vd_right]			= &data->av.v_d_1;
	js_ch_observable[JSO_vq_right]			= &data->av.v_q_1;
	js_ch_observable[JSO_ia_pu_ip]			= &data->av.i_a_pu;
	js_ch_observable[JSO_ib_pu_ip]			= &data->av.i_b_pu;
	js_ch_observable[JSO_ic_pu_ip]			= &data->av.i_c_pu;
	js_ch_observable[JSO_id_pu_ip]			= &data->av.i_d_ip;
	js_ch_observable[JSO_iq_pu_ip]			= &data->av.i_q_ip;
	js_ch_observable[JSO_vd_pu]				= &data->av.vd_pu;
	js_ch_observable[JSO_vq_pu]				= &data->av.vq_pu;
	js_ch_observable[JSO_id_delay_pu]		= &data->av.id_delay_pu;
	js_ch_observable[JSO_iq_delay_pu]		= &data->av.iq_delay_pu;
	js_ch_observable[JSO_ISR_ExecTime_us] 	= &ISR_execution_time_us;
	js_ch_observable[JSO_idc_right]			= &data->av.i_dc_d1;
	js_ch_observable[JSO_idc_left]			= &data->av.i_dc_d2;
	js_ch_observable[JSO_lifecheck]   		= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]		= &ISR_period_us;
	js_ch_observable[JSO_f_sw_avg_Hz_0]		= &data->av.f_sw_avg_Hz_0;
	js_ch_observable[JSO_f_sw_avg_Hz_1]		= &data->av.f_sw_avg_Hz_1;
	js_ch_observable[JSO_f_sw_flag]			= &data->av.f_f_sw_measure_flag;
	js_ch_observable[JSO_req_meas_flag]		= &data->rasv.f_req_measure_flag;
	js_ch_observable[JSO_meas_flag]			= &data->av.f_measure_flag;
	js_ch_observable[JSO_pause_timer_sec]	= &data->av.pause_timer_sec;
	js_ch_observable[JSO_f_cnt]				= &data->rasv.f_cnt_lambda_u;
	js_ch_observable[JSO_f_mod_cnt]			= &f_mod_wait_cnt;
	js_ch_observable[JSO_lambda_u_left]		= &data->av.lambda_u_left;
	js_ch_observable[JSO_duty_a_left]		= &data->rasv.halfBridge1DutyCycle;
	js_ch_observable[JSO_duty_b_left]		= &data->rasv.halfBridge2DutyCycle;
	js_ch_observable[JSO_duty_c_left]		= &data->rasv.halfBridge3DutyCycle;
	js_ch_observable[JSO_duty_a_right]		= &data->rasv.halfBridge4DutyCycle;
	js_ch_observable[JSO_duty_b_right]		= &data->rasv.halfBridge5DutyCycle;
	js_ch_observable[JSO_duty_c_right]		= &data->rasv.halfBridge6DutyCycle;
	js_ch_observable[JSO_svm_clamping_left]	= &data->av.f_svm_clamping_left;
	js_ch_observable[JSO_i_ref_a_left]		= &data->rasv.i_abc_ref_left.a;
	js_ch_observable[JSO_i_ref_b_left]		= &data->rasv.i_abc_ref_left.b;
	js_ch_observable[JSO_i_ref_c_left]		= &data->rasv.i_abc_ref_left.c;
	js_ch_observable[JSO_i_ref_a_left_zero_crossing] = &data->rasv.f_i_a_ref_zero_crossing;
	js_ch_observable[JSO_iq_ref_left]		= &data->rasv.i_dq_ref_0.q;
	js_ch_observable[JSO_trig_flag]			= &data->av.f_trig_flag;
	js_ch_observable[JSO_d_pred_er_sq_filt_pu]	= &data->av.d_pred_error_sq_filt;
	js_ch_observable[JSO_q_pred_er_sq_filt_pu]	= &data->av.q_pred_error_sq_filt;
	js_ch_observable[JSO_d_pred_er_sq_pu]	= &data->av.d_pred_error_sq;
	js_ch_observable[JSO_q_pred_er_sq_pu]	= &data->av.q_pred_error_sq;
	js_ch_observable[JSO_d_delay_diff]		= &data->av.d_delay_diff;
	js_ch_observable[JSO_q_delay_diff]		= &data->av.q_delay_diff;
	js_ch_observable[JSO_CMPA_a]			= &data->av.CMPA_opt[0];
	js_ch_observable[JSO_CMPA_b]			= &data->av.CMPA_opt[1];
	js_ch_observable[JSO_CMPA_c]			= &data->av.CMPA_opt[2];
	js_ch_observable[JSO_unsuited_1]		= &data->av.unsuited_qp[1];
	js_ch_observable[JSO_unsuited_2]		= &data->av.unsuited_qp[2];
	js_ch_observable[JSO_unsuited_3]		= &data->av.unsuited_qp[3];
	js_ch_observable[JSO_unsuited_4]		= &data->av.unsuited_qp[4];
	js_ch_observable[JSO_unsuited_5]		= &data->av.unsuited_qp[5];
	js_ch_observable[JSO_unsuited_6]		= &data->av.unsuited_qp[6];
	js_ch_observable[JSO_unsuited_sum]		= &data->av.unsuited_qp[0];
	js_ch_observable[JSO_iterations_1]		= &data->av.iterations_qp[1];
	js_ch_observable[JSO_iterations_2]		= &data->av.iterations_qp[2];
	js_ch_observable[JSO_iterations_3]		= &data->av.iterations_qp[3];
	js_ch_observable[JSO_iterations_4]		= &data->av.iterations_qp[4];
	js_ch_observable[JSO_iterations_5]		= &data->av.iterations_qp[5];
	js_ch_observable[JSO_iterations_6]		= &data->av.iterations_qp[6];
	js_ch_observable[JSO_omega_el_pu]		= &data->av.omega_el_left_pu;


	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_id_right] 			    = &(data->av.i_d_1);
	js_slowDataArray[JSSD_FLOAT_iq_right] 			    = &(data->av.i_q_1);
	js_slowDataArray[JSSD_FLOAT_id_left] 			    = &(data->av.i_d_0);
	js_slowDataArray[JSSD_FLOAT_iq_left] 			    = &(data->av.i_q_0);
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.resolver_pl_outputs_d5_2.n_mech_rpm);
	js_slowDataArray[JSSD_FLOAT_v_dc_d1]				= &(data->av.v_dc_d1);
	js_slowDataArray[JSSD_FLOAT_v_dc_d2]				= &(data->av.v_dc_d2);
	js_slowDataArray[JSSD_FLOAT_temp_inv_left]			= &(data->av.mean_temp_inv_d1);
	js_slowDataArray[JSSD_FLOAT_temp_inv_right]			= &(data->av.mean_temp_inv_d2);
	js_slowDataArray[JSSD_FLOAT_f_sw_avg_Hz_0]			= &(data->av.f_sw_avg_Hz_0);
	js_slowDataArray[JSSD_FLOAT_f_sw_avg_Hz_1]			= &(data->av.f_sw_avg_Hz_1);
	js_slowDataArray[JSSD_FLOAT_pause_timer_sec]		= &(data->av.pause_timer_sec);
	js_slowDataArray[JSSD_FLOAT_cnt_lambda_u]			= &(data->rasv.f_cnt_lambda_u);
	js_slowDataArray[JSSD_FLOAT_end_cnt_lambda_u]		= &(data->rasv.f_cnt_lambda_u_end);
	js_slowDataArray[JSSD_FLOAT_f_mod_cnt]				= &f_mod_wait_cnt;
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_lambda_u_left]			= &(data->av.lambda_u_left);
	js_slowDataArray[JSSD_FLOAT_lambda_u_right]			= &(data->av.lambda_u_right);
	js_slowDataArray[JSSD_FLOAT_lambda_u_left_1e5]		= &(data->av.lambda_u_e5_left);
	js_slowDataArray[JSSD_FLOAT_i_max_mpc]				= &(data->av.i_max_mpc);
	js_slowDataArray[JSSD_FLOAT_Kp_spd_right]			= &(data->rasv.Kp_spd_right);
	js_slowDataArray[JSSD_FLOAT_Ki_spd_right]			= &(data->rasv.Ki_spd_right);
	js_slowDataArray[JSSD_FLOAT_Kp_cur_d_left]			= &(data->rasv.Kp_cur_d_left);
	js_slowDataArray[JSSD_FLOAT_Ki_cur_d_left]			= &(data->rasv.Ki_cur_d_left);
	js_slowDataArray[JSSD_FLOAT_Kp_cur_q_left]			= &(data->rasv.Kp_cur_q_left);
	js_slowDataArray[JSSD_FLOAT_Ki_cur_q_left]			= &(data->rasv.Ki_cur_q_left);
	js_slowDataArray[JSSD_FLOAT_vd_left]				= &(data->av.v_d_0);
	js_slowDataArray[JSSD_FLOAT_vq_left]				= &(data->av.v_q_0);
	js_slowDataArray[JSSD_FLOAT_Ts_left]				= &(data->rasv.Ts_left_changed);

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
	rpu_to_apu_user_data->v_DC_pu = data->av.v_dc_d1*0.0360844f;
	rpu_to_apu_user_data->i_dq_pu[0] = data->av.i_d_0*0.088388f;
	rpu_to_apu_user_data->i_dq_pu[1] = data->av.i_q_0*0.088388f;
	rpu_to_apu_user_data->i_d_ref_pu = data->rasv.i_dq_ref_0.d*0.088388f;
	rpu_to_apu_user_data->i_q_ref_pu = data->rasv.i_dq_ref_0.q*0.088388f;
	rpu_to_apu_user_data->omega_el_pu = data->av.resolver_pl_outputs_d5_1.omega_mech_rad_s*data->av.polepairs_left*0.0023873f;
	rpu_to_apu_user_data->theta_el = data->av.resolver_pl_outputs_d5_1.position_el_2pi;
	rpu_to_apu_user_data->lambda_impl_mod = data->av.lambda_impl_mod;
	rpu_to_apu_user_data->all_or_deadbeat = data->av.all_or_deadbeat;

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
	status = XIpiPsu_TriggerIpi(&INTCInst_IPI,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI Trigger failed\r\n");
	}

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	//Poll Acknowledgment of IPI
	status = XIpiPsu_PollForAck(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, POLL_FOR_ACK_TIMEOUT_COUNT);
	if(status != (u32)XST_SUCCESS) {
		pollErrorCnt++;
	}
#endif

	u32 ControlData_length = sizeof(Received_Data_from_A53)/sizeof(float); // XIpiPsu_WriteMessage expects number of 32bit values as message length

	//Afterwards the acknowledge a message from the APU can be read/checked, if a53 is enabled for external calculations of the r5 we wait for the acknowledge flag,
	//if not, we don't do it in order to guarantee that the control-ISR never waits and always runs! -> This is due to the Polling of the acknowledge flag.
	status = XIpiPsu_ReadMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, (u32*)(&Received_Data_from_A53), ControlData_length, XIPIPSU_BUF_TYPE_RESP);

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
	data->av.unsuited_qp[1] = apu_to_rpu_user_data->unsuited_qp[1];
	data->av.unsuited_qp[2] = apu_to_rpu_user_data->unsuited_qp[2];
	data->av.unsuited_qp[3] = apu_to_rpu_user_data->unsuited_qp[3];
	data->av.unsuited_qp[4] = apu_to_rpu_user_data->unsuited_qp[4];
	data->av.unsuited_qp[5] = apu_to_rpu_user_data->unsuited_qp[5];
	data->av.unsuited_qp[6] = apu_to_rpu_user_data->unsuited_qp[6];

	data->av.iterations_qp[1] = apu_to_rpu_user_data->iterations_qp[1];
	data->av.iterations_qp[2] = apu_to_rpu_user_data->iterations_qp[2];
	data->av.iterations_qp[3] = apu_to_rpu_user_data->iterations_qp[3];
	data->av.iterations_qp[4] = apu_to_rpu_user_data->iterations_qp[4];
	data->av.iterations_qp[5] = apu_to_rpu_user_data->iterations_qp[5];
	data->av.iterations_qp[6] = apu_to_rpu_user_data->iterations_qp[6];

	data->av.CMPA_opt[0] = 1.0f-apu_to_rpu_user_data->CMPA_opt[0];
	data->av.CMPA_opt[1] = 1.0f-apu_to_rpu_user_data->CMPA_opt[1];
	data->av.CMPA_opt[2] = 1.0f-apu_to_rpu_user_data->CMPA_opt[2];

#endif

	ipc_Control_func(Received_Data_from_A53.id, Received_Data_from_A53.value, data);

}
