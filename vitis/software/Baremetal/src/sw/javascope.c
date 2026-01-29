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
	js_ch_observable[JSO_i_dc1]					= &data->av.i_dc1;
	js_ch_observable[JSO_i_dc2]					= &data->av.i_dc2;
	js_ch_observable[JSO_i_dc_Last]				= &data->av.i_dc_Last;
	js_ch_observable[JSO_v_dc1]					= &data->av.v_dc1;
	js_ch_observable[JSO_v_dc2]					= &data->av.v_dc2;
	js_ch_observable[JSO_v_dc_Last]				= &data->av.v_dc_Last;
	js_ch_observable[JSO_i_a1] 					= &data->av.i_abc.a1;
	js_ch_observable[JSO_i_b1] 					= &data->av.i_abc.b1;
	js_ch_observable[JSO_i_c1] 					= &data->av.i_abc.c1;
	js_ch_observable[JSO_i_a2] 					= &data->av.i_abc.a2;
	js_ch_observable[JSO_i_b2] 					= &data->av.i_abc.b2;
	js_ch_observable[JSO_i_c2] 					= &data->av.i_abc.c2;
	js_ch_observable[JSO_i_d] 					= &data->av.i_dqxy.d;
	js_ch_observable[JSO_i_q] 					= &data->av.i_dqxy.q;
	js_ch_observable[JSO_i_x] 					= &data->av.i_dqxy.x;
	js_ch_observable[JSO_i_y] 					= &data->av.i_dqxy.y;
	js_ch_observable[JSO_i_d_ref] 				= &data->av.i_dqxy_ref.d;
	js_ch_observable[JSO_i_q_ref] 				= &data->av.i_dqxy_ref.q;
	js_ch_observable[JSO_i_x_ref] 				= &data->av.i_dqxy_ref.x;
	js_ch_observable[JSO_i_y_ref] 				= &data->av.i_dqxy_ref.y;
	js_ch_observable[JSO_v_a1] 					= &data->av.v_abc.a1;
	js_ch_observable[JSO_v_b1] 					= &data->av.v_abc.b1;
	js_ch_observable[JSO_v_c1] 					= &data->av.v_abc.c1;
	js_ch_observable[JSO_v_a2] 					= &data->av.v_abc.a2;
	js_ch_observable[JSO_v_b2] 					= &data->av.v_abc.b2;
	js_ch_observable[JSO_v_c2] 					= &data->av.v_abc.c2;
	js_ch_observable[JSO_v_d] 					= &data->av.v_dqxy.d;
	js_ch_observable[JSO_v_q] 					= &data->av.v_dqxy.q;
	js_ch_observable[JSO_v_x] 					= &data->av.v_dqxy.x;
	js_ch_observable[JSO_v_y] 					= &data->av.v_dqxy.y;
	js_ch_observable[JSO_v_d_ref] 				= &data->av.v_dqxy_ref.d;
	js_ch_observable[JSO_v_q_ref] 				= &data->av.v_dqxy_ref.q;
	js_ch_observable[JSO_v_x_ref] 				= &data->av.v_dqxy_ref.x;
	js_ch_observable[JSO_v_y_ref] 				= &data->av.v_dqxy_ref.y;
	js_ch_observable[JSO_Theta_el_Last] 		= &data->av.theta_elec_Last;
	js_ch_observable[JSO_Theta_el] 				= &data->av.theta_elec;
	js_ch_observable[JSO_Theta_el_advanced] 	= &data->av.theta_elec_advanced;
	js_ch_observable[JSO_Theta_mech] 			= &data->av.theta_mech;
	js_ch_observable[JSO_Theta_mech_Last] 		= &data->av.theta_mech_Last;
	js_ch_observable[JSO_omega_el] 				= &data->av.omega_elec;
	js_ch_observable[JSO_omega_mech] 			= &data->av.omega_mech;
	js_ch_observable[JSO_omega_el_Last] 		= &data->av.omega_elec_Last;
	js_ch_observable[JSO_omega_mech_Last] 		= &data->av.omega_mech_Last;
	js_ch_observable[JSO_n_rpm] 				= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_n_Last_rpm] 			= &data->av.mechanicalRotorSpeed_Last;
	js_ch_observable[JSO_n_ref_Last_rpm] 		= &data->av.n_ref_Last;
	js_ch_observable[JSO_M_ref_Last] 			= &data->av.M_ref_Last;
	js_ch_observable[JSO_i_d_ref_Last] 			= &data->av.i_dq_Last_ref.d;
	js_ch_observable[JSO_i_q_ref_Last] 			= &data->av.i_dq_Last_ref.q;
	js_ch_observable[JSO_i_a_Last] 				= &data->av.i_abc_Last.a;
	js_ch_observable[JSO_i_b_Last] 				= &data->av.i_abc_Last.b;
	js_ch_observable[JSO_i_c_Last] 				= &data->av.i_abc_Last.c;
	js_ch_observable[JSO_i_d_Last]				= &data->av.i_dq_Last.d;
	js_ch_observable[JSO_i_q_Last] 				= &data->av.i_dq_Last.q;
	js_ch_observable[JSO_M_vor_Last] 			= &data->av.M_vor_Last;
	js_ch_observable[JSO_start_marker]			= &data->av.start_marker;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_i_d] 			        = &data->av.i_dqxy.d;
	js_slowDataArray[JSSD_FLOAT_i_q] 			        = &data->av.i_dqxy.q;
	js_slowDataArray[JSSD_FLOAT_i_x] 			        = &data->av.i_dqxy.x;
	js_slowDataArray[JSSD_FLOAT_i_y] 			        = &data->av.i_dqxy.y;
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.mechanicalRotorSpeed);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_error] 			    	= &(data->av.error);
	js_slowDataArray[JSSD_FLOAT_Temp_Inv1]				= &data->av.temp_VSI_1;
	js_slowDataArray[JSSD_FLOAT_Temp_Inv2]				= &data->av.temp_VSI_2;
	js_slowDataArray[JSSD_FLOAT_Temp_Inv3]				= &data->av.temp_VSI_3;
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
