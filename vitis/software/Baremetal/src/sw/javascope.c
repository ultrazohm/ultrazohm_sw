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
	js_ch_observable[JSO_va_DUT]					= &data->av.v_abc_DUT.a;
	js_ch_observable[JSO_vb_DUT]					= &data->av.v_abc_DUT.b;
	js_ch_observable[JSO_vc_DUT]					= &data->av.v_abc_DUT.c;
	js_ch_observable[JSO_ia_DUT]					= &data->av.i_abc_DUT.a;
	js_ch_observable[JSO_ib_DUT]					= &data->av.i_abc_DUT.b;
	js_ch_observable[JSO_ic_DUT]					= &data->av.i_abc_DUT.c;
	js_ch_observable[JSO_Speed_rpm_DUT]				= &data->av.mechanicalRotorSpeed_DUT;
	js_ch_observable[JSO_Theta_el_DUT] 				= &data->av.theta_elec_DUT;
	js_ch_observable[JSO_Theta_mech_DUT] 			= &data->av.theta_mech_DUT;
	js_ch_observable[JSO_i_dc_DUT]					= &data->av.i_dc_DUT;
	js_ch_observable[JSO_v_dc_DUT]					= &data->av.v_dc_DUT;
	js_ch_observable[JSO_id_DUT]					= &data->av.i_dq_DUT.d;
	js_ch_observable[JSO_iq_DUT]					= &data->av.i_dq_DUT.q;
	js_ch_observable[JSO_id_ref_DUT]				= &data->av.i_ref_dq_DUT.d;
	js_ch_observable[JSO_iq_ref_DUT]				= &data->av.i_ref_dq_DUT.q;
	js_ch_observable[JSO_vd_DUT]					= &data->av.v_dq_DUT.d;
	js_ch_observable[JSO_vq_DUT]					= &data->av.v_dq_DUT.q;
	js_ch_observable[JSO_vd_ref_DUT]				= &data->av.v_ref_dq_DUT.d;
	js_ch_observable[JSO_vq_ref_DUT]				= &data->av.v_ref_dq_DUT.q;
	js_ch_observable[JSO_current_angle_deg_DUT]		= &data->av.current_angle_degree_DUT;
	js_ch_observable[JSO_current_angle_ref_DUT]		= &data->av.current_angle_ref_degree_DUT;
	js_ch_observable[JSO_is_DUT]					= &data->av.is_DUT;
	js_ch_observable[JSO_is_ref_DUT]				= &data->av.is_ref_DUT;
	js_ch_observable[JSO_torque_DUT]				= &data->av.Torque_DUT;
	js_ch_observable[JSO_torque_ref_DUT]			= &data->av.Torque_ref_DUT;
	js_ch_observable[JSO_va_Load]					= &data->av.v_abc_Load.a;
	js_ch_observable[JSO_vb_Load]					= &data->av.v_abc_Load.b;
	js_ch_observable[JSO_vc_Load]					= &data->av.v_abc_Load.c;
	js_ch_observable[JSO_ia_Load]					= &data->av.i_abc_Load.a;
	js_ch_observable[JSO_ib_Load]					= &data->av.i_abc_Load.b;
	js_ch_observable[JSO_ic_Load]					= &data->av.i_abc_Load.c;
	js_ch_observable[JSO_Speed_rpm_Load]			= &data->av.mechanicalRotorSpeed_Load;
	js_ch_observable[JSO_Theta_el_Load] 			= &data->av.theta_elec_Load;
	js_ch_observable[JSO_Theta_mech_Load] 			= &data->av.theta_mech_Load;
	js_ch_observable[JSO_i_dc_Load]					= &data->av.i_dc_Load;
	js_ch_observable[JSO_v_dc_Load]					= &data->av.v_dc_Load;
	js_ch_observable[JSO_id_Load]					= &data->av.i_dq_Load.d;
	js_ch_observable[JSO_iq_Load]					= &data->av.i_dq_Load.q;
	js_ch_observable[JSO_id_ref_Load]				= &data->av.i_ref_dq_Load.d;
	js_ch_observable[JSO_iq_ref_Load]				= &data->av.i_ref_dq_Load.q;
	js_ch_observable[JSO_vd_Load]					= &data->av.v_dq_Load.d;
	js_ch_observable[JSO_vq_Load]					= &data->av.v_dq_Load.q;
	js_ch_observable[JSO_vd_ref_Load]				= &data->av.v_ref_dq_Load.d;
	js_ch_observable[JSO_vq_ref_Load]				= &data->av.v_ref_dq_Load.q;
	js_ch_observable[JSO_is_Load]					= &data->av.is_Load;
	js_ch_observable[JSO_torque_Load]				= &data->av.Torque_Load;
	js_ch_observable[JSO_torque_ref_Load]			= &data->av.Torque_ref_Load;

	js_ch_observable[JSO_ISR_ExecTime_us] 			= &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   				= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]				= &ISR_period_us;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_v_d_DUT] 			        = &(data->av.v_dq_DUT.d);
	js_slowDataArray[JSSD_FLOAT_v_q_DUT] 			        = &(data->av.v_dq_DUT.q);
	js_slowDataArray[JSSD_FLOAT_v_d_ref_DUT] 			    = &(data->av.v_ref_dq_DUT.d);
	js_slowDataArray[JSSD_FLOAT_v_q_ref_DUT] 			    = &(data->av.v_ref_dq_DUT.q);
	js_slowDataArray[JSSD_FLOAT_i_d_DUT] 			        = &(data->av.i_dq_DUT.d);
	js_slowDataArray[JSSD_FLOAT_i_q_DUT] 			        = &(data->av.i_dq_DUT.q);
	js_slowDataArray[JSSD_FLOAT_i_s_DUT] 			        = &(data->av.is_DUT);
	js_slowDataArray[JSSD_FLOAT_speed_DUT] 		         	= &(data->av.mechanicalRotorSpeed_DUT);
	js_slowDataArray[JSSD_FLOAT_torque_DUT] 		        = &(data->av.Torque_DUT);
	js_slowDataArray[JSSD_FLOAT_current_angle_deg_DUT]		= &(data->av.current_angle_degree_DUT);
	js_slowDataArray[JSSD_FLOAT_v_d_Load] 			        = &(data->av.v_dq_Load.d);
	js_slowDataArray[JSSD_FLOAT_v_q_Load] 			        = &(data->av.v_dq_Load.q);
	js_slowDataArray[JSSD_FLOAT_v_d_ref_Load] 			    = &(data->av.v_ref_dq_Load.d);
	js_slowDataArray[JSSD_FLOAT_v_q_ref_Load] 			    = &(data->av.v_ref_dq_Load.q);
	js_slowDataArray[JSSD_FLOAT_i_d_Load] 			        = &(data->av.i_dq_Load.d);
	js_slowDataArray[JSSD_FLOAT_i_q_Load] 			        = &(data->av.i_dq_Load.q);
	js_slowDataArray[JSSD_FLOAT_speed_Load]		         	= &(data->av.mechanicalRotorSpeed_Load);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]	= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 			= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 				= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]				= &System_UpTime_ms;

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
