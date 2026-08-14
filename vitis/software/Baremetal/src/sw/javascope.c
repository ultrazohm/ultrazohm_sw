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
#include "../IP_Cores/uz_JL_invModel_ideal/uz_JL_invModel_ideal.h"
#include "../IP_Cores/uz_JL_pmsmModel/uz_JL_pmsmModel.h"
#include "../Codegen/uz_codegen0_ert_rtw/uz_codegen0.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
//#include "../Codegen/uz_codegen.h"
#include "../globalData.h"
#include "../include/JL_SH_Umrichter.h"


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
static float conv_pwr_en_f;
static float conv_board_en_f;
static float conv_board_rst_f;
static float conv_board_ready_f;
static float conv_igbt_desat_f;
static float dpt_state_f;

uint32_t pollErrorCnt = 0U;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

//Initialize the Interrupt structure
extern XIpiPsu IPI_instance;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!
extern uint32_t output_bitmask;
extern float input_bit_float;
extern Bus_ZM_In struct_ZM_In;
extern uz_codegen regelung;
extern struct uz_JL_SigmaDelta_Interface_output_t Sinc3_Filter_out;
extern bool input_bit;
extern float Sinc3_Filter_out_f;
extern int32_t fault;
extern float fault_f;
extern DS_Data Global_Data;
extern conv_status_signals_t conv_status_signals;
extern float sine;

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
//	js_ch_observable[JSO_ideal_ia_filt]			= &i_a_filt;
//	js_ch_observable[JSO_ideal_ib_filt]			= &i_b_filt;
//	js_ch_observable[JSO_ideal_ic_filt]			= &i_c_filt;
//	js_ch_observable[JSO_pmsm_ideal_omega]		= &pmsm_ideal_out.omega_mech_1_s;
//	js_ch_observable[JSO_pmsm_ideal_phi]		= &pmsm_ideal_out.phi_mech_rad;
//	js_ch_observable[JSO_pmsm_ideal_torque]		= &pmsm_ideal_out.torque_Nm;
//	js_ch_observable[JSO_Soll_Drehzahl]			= &struct_ZM_In.Soll_Drehzahl;
//	js_ch_observable[JSO_ctrl_Ualpha] 			= &voltages_alphabeta.alpha;
//	js_ch_observable[JSO_ctrl_Ubeta] 			= &voltages_alphabeta.beta;
//	js_ch_observable[JSO_ideal_ua] 				= &ideal_outputs.Ua;
//	js_ch_observable[JSO_ideal_ub] 				= &ideal_outputs.Ub;
//	js_ch_observable[JSO_ideal_uc] 				= &ideal_outputs.Uc;
//	js_ch_observable[JSO_pmsm_ideal_ia]			= &pmsm_ideal_out.i_a_A;
//	js_ch_observable[JSO_pmsm_ideal_ib]			= &pmsm_ideal_out.i_b_A;
//	js_ch_observable[JSO_pmsm_ideal_ic]			= &pmsm_ideal_out.i_c_A;
	js_ch_observable[JSO_SD_U]					= &sine;
	js_ch_observable[JSO_SD_PH1]				= &Global_Data.av.Sinc3_Filter.data_PH1;
	js_ch_observable[JSO_SD_PH2]				= &Global_Data.av.Sinc3_Filter.data_PH2;
	js_ch_observable[JSO_SD_PH3]				= &Global_Data.av.Sinc3_Filter.data_PH3;
//	js_ch_observable[JSO_SD_PH4]				= &Global_Data.av.Sinc3_Filter.data_PH4;
	js_ch_observable[JSO_theta_el]				= &Global_Data.av.theta_el;
	js_ch_observable[JSO_theta_mech]			= &Global_Data.av.mechanicalPosition;
	js_ch_observable[JSO_n_rpm]					= &Global_Data.av.resolver_pl_outputs.n_mech_rpm;
	js_ch_observable[JSO_omega_mech]			= &Global_Data.av.resolver_pl_outputs.omega_mech_rad_s;
	js_ch_observable[JSO_dpt_state]				= &dpt_state_f;
	js_ch_observable[JSO_dpt_current]			= &Global_Data.av.Sinc3_Filter.data_PH1;
	js_ch_observable[JSO_conv_pwr_en]			= &conv_pwr_en_f;
	js_ch_observable[JSO_conv_board_en]			= &conv_board_en_f;
	js_ch_observable[JSO_conv_board_rst]		= &conv_board_rst_f;
	js_ch_observable[JSO_conv_board_ready]		= &conv_board_ready_f;
	js_ch_observable[JSO_conv_igbt_desat]		= &conv_igbt_desat_f;
	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_resolver_counter] 		= &(Global_Data.av.resolver_pl_outputs.revolution_counter);
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.mechanicalRotorSpeed);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_SD_raw_avg_PH1]			= SigmaDeltaWandler_get_raw_average(SDW_CH_PH1);
	js_slowDataArray[JSSD_FLOAT_SD_raw_avg_PH2]			= SigmaDeltaWandler_get_raw_average(SDW_CH_PH2);
	js_slowDataArray[JSSD_FLOAT_SD_raw_avg_PH3]			= SigmaDeltaWandler_get_raw_average(SDW_CH_PH3);


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
	conv_pwr_en_f			= (float)conv_status_signals.pwr_en;
	conv_board_en_f			= (float)conv_status_signals.board_en;
	conv_board_rst_f		= (float)conv_status_signals.board_rst;
	conv_board_ready_f		= (float)conv_status_signals.board_ready;
	conv_igbt_desat_f		= (float)conv_status_signals.igbt_desat;
	dpt_state_f				= (float)data->av.dpt_state;

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
