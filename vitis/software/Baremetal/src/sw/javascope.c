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
#include "../Codegen/uz_codegen0_ert_rtw/uz_codegen0.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
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
static float mult_pos_valid_f;
static float ocp_fault_f;
static float flt_fault_f;
static float watchdog_fault_f;
static float i_max;
static float i_min;

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
extern struct SDC_Interface_output_t Sinc3_Filter_out;
extern bool input_bit;
extern float Sinc3_Filter_out_f;
extern int32_t fault;
extern float fault_f;
extern DS_Data Global_Data;
extern conv_status_signals_t conv_status_signals;
extern float sine;
extern uz_codegen regelung;
extern bool data_valid;

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
	js_ch_observable[JSO_SD_PH1]				= &Global_Data.av.Sinc3_Filter_P.data_PH1_A;
	js_ch_observable[JSO_SD_PH2]				= &Global_Data.av.Sinc3_Filter_P.data_PH2_A;
	js_ch_observable[JSO_SD_PH3]				= &Global_Data.av.Sinc3_Filter_P.data_PH3_A;
	 js_ch_observable[JSO_SD_OCP_PH1]			= &Global_Data.av.Sinc3_Filter_OCP.data_PH1_A;
	 js_ch_observable[JSO_SD_OCP_PH2]			= &Global_Data.av.Sinc3_Filter_OCP.data_PH2_A;
	 js_ch_observable[JSO_SD_OCP_PH3]			= &Global_Data.av.Sinc3_Filter_OCP.data_PH3_A;
	 js_ch_observable[JSO_FLOAT_flt_fault]			    = &flt_fault_f;
	 js_ch_observable[JSO_FLOAT_ocp_fault]			    = &ocp_fault_f;
	 js_ch_observable[JSO_FLOAT_watchdog_fault]		    = &watchdog_fault_f;
	 js_ch_observable[JSO_I_MAX]				= &i_max;
	 js_ch_observable[JSO_I_MIN]				= &i_min;
	// js_ch_observable[JSO_SD2_PH1]				= &Global_Data.av.Sinc3_Filter_I.data_PH1_A;
	// js_ch_observable[JSO_SD2_PH2]				= &Global_Data.av.Sinc3_Filter_I.data_PH2_A;
	// js_ch_observable[JSO_SD2_PH3]				= &Global_Data.av.Sinc3_Filter_I.data_PH3_A;
	js_ch_observable[JSO_theta_el]				= &Global_Data.av.theta_el;
	js_ch_observable[JSO_theta_mech]			= &Global_Data.av.mechanicalPosition;
	js_ch_observable[JSO_n_rpm]					= &Global_Data.av.resolver_pl_outputs.n_mech_rpm;
	js_ch_observable[JSO_omega_mech]			= &Global_Data.av.resolver_pl_outputs.omega_mech_rad_s;
	js_ch_observable[JSO_ctrl_Iqref]			= &regelung.output.IQRef;
	js_ch_observable[JSO_ctrl_Soll_Moment]		= &regelung.output.Soll_Moment;
	js_ch_observable[JSO_ctrl_ist_omega]		= &regelung.output.ctrl_omega;
	js_ch_observable[JSO_ctrl_soll_omega]		= &regelung.output.soll_omega;
	js_ch_observable[JSO_ctrl_Ist_Iq]			= &regelung.output.Ist_Iq;
	js_ch_observable[JSO_ctrl_act_id_I]			= &regelung.output.act_id_I;
	js_ch_observable[JSO_ctrl_act_iq_I]			= &regelung.output.act_iq_I;
	js_ch_observable[JSO_ctrl_act_id_P]			= &regelung.output.act_id_P;
	js_ch_observable[JSO_ctrl_ref_Id]			= &regelung.output.ref_Id;
	js_ch_observable[JSO_conv_pwr_en]			= &conv_pwr_en_f;
	js_ch_observable[JSO_conv_board_en]			= &conv_board_en_f;
	js_ch_observable[JSO_conv_board_rst]		= &conv_board_rst_f;
	js_ch_observable[JSO_conv_board_ready]		= &conv_board_ready_f;
	js_ch_observable[JSO_conv_igbt_desat]		= &conv_igbt_desat_f;
	js_ch_observable[JSO_mult_pos_grad]			= &Global_Data.av.mult_pos_grad;
	js_ch_observable[JSO_mult_pos_valid]		= &mult_pos_valid_f;
	js_ch_observable[JSO_CB_phi_ist]			= &regelung.output.phi_ist_safety;
	js_ch_observable[JSO_CB_phi_max]			= &regelung.output.phi_max;
	js_ch_observable[JSO_CB_v_max]				= &regelung.output.Soll_v_max_grads;
	js_ch_observable[JSO_CB_Grenze_aktiv]		= &regelung.output.Grenze_aktiv;
 	js_ch_observable[JSO_CB_Soll_Beschl]		= &regelung.output.Bus_Ctrl_Out_o.Soll_Beschleunigung_CB_Grads2;
	js_ch_observable[JSO_CB_Soll_Geschw]		= &regelung.output.Bus_Ctrl_Out_o.Soll_Drehzahl_CB_Grads;
	js_ch_observable[JSO_CB_Soll_Winkel]		= &regelung.output.Bus_Ctrl_Out_o.Soll_Winkel_CB_Grad;
	js_ch_observable[JSO_CB_omega_grads]		= &Global_Data.av.CB_omega_grads;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_resolver_counter] 		= &(Global_Data.av.mult_pos_turns);
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.resolver_pl_outputs.n_mech_rpm);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_timestamp]			    = &(Global_Data.av.debug_timestamp_s);
	js_slowDataArray[JSSD_FLOAT_flt_fault]			    = &flt_fault_f;
	js_slowDataArray[JSSD_FLOAT_ocp_fault]			    = &ocp_fault_f;
	js_slowDataArray[JSSD_FLOAT_phi_ist]			    = &regelung.output.phi_ist_safety;
	js_slowDataArray[JSSD_FLOAT_watchdog_fault]		    = &watchdog_fault_f;
	// js_slowDataArray[JSSD_FLOAT_SD_raw_avg_PH2]			= SigmaDeltaWandler_get_raw_average(SDW_FILTER_0, SDW_CH_PH2);
	// js_slowDataArray[JSSD_FLOAT_SD_raw_avg_PH3]			= SigmaDeltaWandler_get_raw_average(SDW_FILTER_0, SDW_CH_PH3);
	// js_slowDataArray[JSSD_FLOAT_Soll_Drehzahl]				= &regelung.input.Bus_ZM_In_a.Soll_Drehzahl_Umin;
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
	mult_pos_valid_f		= (float)Global_Data.av.mult_pos_valid;
	ocp_fault_f				= (float)conv_status_signals.ocp_fault;
	i_max					= SDW_OCP_I_MAX_A;
	i_min					= SDW_OCP_I_MIN_A;
	flt_fault_f				= (data->objects.flt_dis != NULL)
								  ? (float)io_fault_shutdown_get_fault(data->objects.flt_dis)
								  : 0.0f;
	watchdog_fault_f		= (data->objects.ctrl_loop_watchdog != NULL)
								  ? (float)ctrl_loop_watchdog_get_fault(data->objects.ctrl_loop_watchdog)
								  : 0.0f;

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
