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
	js_ch_observable[JSO_vd_left_filt]			= &data->av.v_d_0_filt;
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
	js_slowDataArray[JSSD_FLOAT_vd_left_filt]				= &(data->av.v_d_0_filt);
	js_slowDataArray[JSSD_FLOAT_vq_left]				= &(data->av.v_q_0);

	return Status;
}



void JavaScope_update(DS_Data* data){

	// create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START;
	struct APU_to_RPU_t Received_Data_from_A53 = {0};

	static int js_cnt_slowData=0;
	int status = XST_SUCCESS;

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
	Xil_DCacheFlushRange(MEM_SHARED_START, JAVASCOPE_DATA_SIZE_2POW);

	//Send an interrupt to APU
	status = XIpiPsu_TriggerIpi(&INTCInst_IPI,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI Trigger failed\r\n");
	}

	u32 ControlData_length = sizeof(Received_Data_from_A53)/sizeof(float); // XIpiPsu_WriteMessage expects number of 32bit values as message length

	//Afterwards an acknowledge and a message from the APU can be read/checked, but we don't do it in order to guarantee that the control-ISR never waits and always runs! -> This is due to the Polling of the acknowledge flag.
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

	ipc_Control_func(Received_Data_from_A53.id, Received_Data_from_A53.value, data);

}
