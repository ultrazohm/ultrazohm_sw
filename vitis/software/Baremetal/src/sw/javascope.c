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
#include "../include/FOC.h"

#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

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

extern uz_3ph_dq_t i_dq_ref;

uint32_t pollErrorCnt = 0U;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

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
	js_ch_observable[JSO_i_a1] 					= &data->av.i_a1;
	js_ch_observable[JSO_i_b1] 					= &data->av.i_b1;
	js_ch_observable[JSO_i_c1] 					= &data->av.i_c1;
	js_ch_observable[JSO_i_a2] 					= &data->av.i_a2;
	js_ch_observable[JSO_i_b2] 					= &data->av.i_b2;
	js_ch_observable[JSO_i_c2] 					= &data->av.i_c2;
	js_ch_observable[JSO_i_alpha]				= &data->av.i_alpha;
	js_ch_observable[JSO_i_beta]				= &data->av.i_beta;
	js_ch_observable[JSO_i_X]					= &data->av.i_X;
	js_ch_observable[JSO_i_Y]					= &data->av.i_Y;
	js_ch_observable[JSO_i_d] 					= &data->av.i_d;
	js_ch_observable[JSO_i_q] 					= &data->av.i_q;
	js_ch_observable[JSO_i_x] 					= &data->av.i_x;
	js_ch_observable[JSO_i_y] 					= &data->av.i_y;
	js_ch_observable[JSO_speed_rpm]				= &data->av.mechanicalRotorSpeedRPM;
	js_ch_observable[JSO_dutycyc_MPC_a1]		= &data->av.dutycyc[0];
	js_ch_observable[JSO_dutycyc_MPC_b1]		= &data->av.dutycyc[1];
	js_ch_observable[JSO_dutycyc_MPC_c1]		= &data->av.dutycyc[2];
	js_ch_observable[JSO_dutycyc_MPC_a2]		= &data->av.dutycyc[3];
	js_ch_observable[JSO_dutycyc_MPC_b2]		= &data->av.dutycyc[4];
	js_ch_observable[JSO_dutycyc_MPC_c2]		= &data->av.dutycyc[5];
	js_ch_observable[JSO_dutycyc_out_a1]		= &data->rasv.halfBridge1DutyCycle;
	js_ch_observable[JSO_dutycyc_out_b1]		= &data->rasv.halfBridge2DutyCycle;
	js_ch_observable[JSO_dutycyc_out_c1]		= &data->rasv.halfBridge3DutyCycle;
	js_ch_observable[JSO_dutycyc_out_a2]		= &data->rasv.halfBridge4DutyCycle;
	js_ch_observable[JSO_dutycyc_out_b2]		= &data->rasv.halfBridge5DutyCycle;
	js_ch_observable[JSO_dutycyc_out_c2]		= &data->rasv.halfBridge6DutyCycle;
	js_ch_observable[JSO_iterations]			= &data->av.iterations;
	js_ch_observable[JSO_id_ref]				= &i_dq_ref.d;
	js_ch_observable[JSO_iq_ref]				= &i_dq_ref.q;
	js_ch_observable[JSO_v_d_ref]				= &data->av.u_dq_ref.d;
	js_ch_observable[JSO_v_q_ref]				= &data->av.u_dq_ref.q;
	js_ch_observable[JSO_v_d]					= &data->av.v_d;
	js_ch_observable[JSO_v_q]					= &data->av.v_q;
	js_ch_observable[JSO_v_x]					= &data->av.v_x;
	js_ch_observable[JSO_v_y]					= &data->av.v_y;
	js_ch_observable[JSO_v_a1]					= &data->av.v_a1;
	js_ch_observable[JSO_pos_mech]				= &data->av.pos_mech;
	js_ch_observable[JSO_pos_elec]				= &data->av.pos_elec;
	js_ch_observable[JSO_dob_e_est_d]			= &data->av.dob_e_est_d;
	js_ch_observable[JSO_dob_e_est_q]			= &data->av.dob_e_est_q;
	js_ch_observable[JSO_dob_e_est_x]			= &data->av.dob_e_est_x;
	js_ch_observable[JSO_dob_e_est_y]			= &data->av.dob_e_est_y;
	js_ch_observable[JSO_dualsvm_clamped]		= &data->av.dualsvm_clamped_f;
	js_ch_observable[JSO_xy_r6_ref_d]			= &data->av.xy_r6_v_d_ref;
	js_ch_observable[JSO_xy_r6_ref_q]			= &data->av.xy_r6_v_q_ref;
	js_ch_observable[JSO_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   			= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]			= &ISR_period_us;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_v_dc1] 			        = &(data->av.v_dc1);
	js_slowDataArray[JSSD_FLOAT_v_dc2] 			        = &(data->av.v_dc2);
	js_slowDataArray[JSSD_FLOAT_i_d] 			        = &(data->av.i_d);
	js_slowDataArray[JSSD_FLOAT_i_q] 			        = &(data->av.i_q);
	js_slowDataArray[JSSD_FLOAT_speed]					= &(data->av.mechanicalRotorSpeedRPM);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_overcurrent]			= &(data->av.overcurrent_FPGA_fl);
	js_slowDataArray[JSSD_FLOAT_inv1Temp]				= &(data->av.temperature_inv_1);
	js_slowDataArray[JSSD_FLOAT_inv2Temp]				= &(data->av.temperature_inv_2);
	js_slowDataArray[JSSD_FLOAT_winding_temp]			= &(data->av.average_winding_temp);
	js_slowDataArray[JSSD_FLOAT_zynq_temp]				= &(data->av.zynq_temp);
	js_slowDataArray[JSSD_FLOAT_theta_el]				= &(data->av.theta_elec_rad_ip);
	js_slowDataArray[JSSD_FLOAT_w_el]					= &(data->av.electricalRotorSpeedRADpS);
	js_slowDataArray[JSSD_FLOAT_Kp_id]					= &data->av.Kp_id;
	js_slowDataArray[JSSD_FLOAT_Ki_id]					= &data->av.Ki_id;
	js_slowDataArray[JSSD_FLOAT_Kp_iq]					= &data->av.Kp_iq;
	js_slowDataArray[JSSD_FLOAT_Ki_iq]					= &data->av.Ki_iq;
	js_slowDataArray[JSSD_FLOAT_Kalman_R]				= &data->av.kalman_R;
	js_slowDataArray[JSSD_FLOAT_Kalman_Q1]				= &data->av.kalman_Q1;
	js_slowDataArray[JSSD_FLOAT_Kalman_Q2]				= &data->av.kalman_Q2;
	js_slowDataArray[JSSD_FLOAT_phi_pm_5th]				= &data->av.phiPM_h[0];
	js_slowDataArray[JSSD_FLOAT_phi_pm_7th]				= &data->av.phiPM_h[1];

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
	rpu_to_apu_user_data->v_DC_pu = data->av.v_dc1_pu;
	rpu_to_apu_user_data->theta_el_pos = (data->av.theta_el_pos_MPC);
	rpu_to_apu_user_data->theta_el_neg = (data->av.theta_el_neg_MPC);
	rpu_to_apu_user_data->Ts_times_ZB_over_Ld = data->av.Ts_times_ZB_over_Ld;
	rpu_to_apu_user_data->Ts_times_ZB_over_Lq = data->av.Ts_times_ZB_over_Lq;
	rpu_to_apu_user_data->Ts_times_ZB_over_Lx = data->av.Ts_times_ZB_over_Lx;
	rpu_to_apu_user_data->Ts_times_ZB_over_Ly = data->av.Ts_times_ZB_over_Ly;
	rpu_to_apu_user_data->Rs_over_ZB = data->av.Rs_over_ZB;
	rpu_to_apu_user_data->Ld_over_LB = data->av.Ld_over_LB;
	rpu_to_apu_user_data->Lq_over_LB = data->av.Lq_over_LB;
	rpu_to_apu_user_data->Lx_over_LB = data->av.Lx_over_LB;
	rpu_to_apu_user_data->Ly_over_LB = data->av.Ly_over_LB;
	rpu_to_apu_user_data->psi_pm_over_psiB = data->av.psi_pm_over_psiB;
	rpu_to_apu_user_data->omega_el_pu = data->av.omega_el_pu;
	rpu_to_apu_user_data->i_d_pu = data->av.i_d_pu;
	rpu_to_apu_user_data->i_q_pu = data->av.i_q_pu;
	rpu_to_apu_user_data->i_x_pu = data->av.i_x_pu;
	rpu_to_apu_user_data->i_y_pu = data->av.i_y_pu;
	rpu_to_apu_user_data->i_d_ref_pu = data->av.i_d_ref_pu;
	rpu_to_apu_user_data->i_q_ref_pu = data->av.i_q_ref_pu;
	rpu_to_apu_user_data->i_x_ref_pu = data->av.i_x_ref_pu;
	rpu_to_apu_user_data->i_y_ref_pu = data->av.i_y_ref_pu;
	rpu_to_apu_user_data->lambda_dq = data->av.lambda_dq;
	rpu_to_apu_user_data->lambda_xy = data->av.lambda_xy;
	rpu_to_apu_user_data->solver_tolerance = data->av.solver_tolerance;
	rpu_to_apu_user_data->max_iter = data->av.max_iter;
	rpu_to_apu_user_data->HC_off_on = data->av.HC_off_on;
	rpu_to_apu_user_data->psiPM_h_pu[0] = data->av.psi_pm_h_pu_over_psiB[0];
	rpu_to_apu_user_data->psiPM_h_pu[1] = data->av.psi_pm_h_pu_over_psiB[1];
	rpu_to_apu_user_data->phiPM_h[0] = data->av.phiPM_h[0];
	rpu_to_apu_user_data->phiPM_h[1] = data->av.phiPM_h[1];
	rpu_to_apu_user_data->kalman_off_on = data->av.kalman_off_on;
	rpu_to_apu_user_data->kalman_R = data->av.kalman_R;
	rpu_to_apu_user_data->kalman_Q1 = data->av.kalman_Q1;
	rpu_to_apu_user_data->kalman_Q2 = data->av.kalman_Q2;
	rpu_to_apu_user_data->Ts_over_tB = data->av.Ts_over_tB;
	rpu_to_apu_user_data->tB_over_Ts = data->av.tB_over_Ts;
	rpu_to_apu_user_data->a53_ctrl_off_on = data->rasv.a53_ctrl_off_on;

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
	data->av.dutycyc[0] = 1.0f-apu_to_rpu_user_data->dutycyc[0];
	data->av.dutycyc[1] = 1.0f-apu_to_rpu_user_data->dutycyc[1];
	data->av.dutycyc[2] = 1.0f-apu_to_rpu_user_data->dutycyc[2];
	data->av.dutycyc[3] = 1.0f-apu_to_rpu_user_data->dutycyc[3];
	data->av.dutycyc[4] = 1.0f-apu_to_rpu_user_data->dutycyc[4];
	data->av.dutycyc[5] = 1.0f-apu_to_rpu_user_data->dutycyc[5];

	data->av.dob_e_est_d = apu_to_rpu_user_data->dob_error_estimate[0];
	data->av.dob_e_est_q = apu_to_rpu_user_data->dob_error_estimate[1];
	data->av.dob_e_est_x = apu_to_rpu_user_data->dob_error_estimate[2];
	data->av.dob_e_est_y = apu_to_rpu_user_data->dob_error_estimate[3];

	data->av.iterations = apu_to_rpu_user_data->iterations;

#endif

	ipc_Control_func(Received_Data_from_A53.id, Received_Data_from_A53.value, data);

}
