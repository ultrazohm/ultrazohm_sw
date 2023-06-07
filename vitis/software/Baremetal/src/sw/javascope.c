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

#include "xuz_log_data.h"
#include "xtime_l.h"
#include "sleep.h"
#include <stdio.h>
#include <stdlib.h>

#include "xil_mpu.h"
#include "xgpiops.h"
#include "xil_mem.h"

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

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

extern float DataLogger_out;

XGpioPs myPlGpio;

XTime xStart, xEnd;						// XTime = u32
float xDifference_us, xDifference_s; 	// define BRAM read-out latency benchmark variables
//int write_array_local[128];			// local array in PS for BRAM data (memcpy-source)
int PS_TO_BRAM_WORDCOUNT;
float DiffArray[50];
int cnt_to_50 = 0;

#define NUM_DATA_VALUES 512
int write_array_local[NUM_DATA_VALUES] = {};
//int write_array_local[128]= {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,
//	 	 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,
//		 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,
//		 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
//XGpio PLtoggle;

XMpu_Config tmp_MPU_readout;

void rand_array(unsigned int len) {
	for(int i=0; i<len; i++){
		write_array_local[i] = rand();
	};
}

int JavaScope_initalize(DS_Data* data)
{
	// Initialize write array
	rand_array(NUM_DATA_VALUES);

	// Initialize GPIO for PL signal during measurement
	//XGpio_Initialize(&PLtoggle, XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_2_DEVICE_ID);
	//XGpio_SetDataDirection(&PLtoggle, 1, 0x00000000); // bits set to 0 are output

	// Initialize EMIO_GPIO for PL signal during measurement
	XGpioPs_Config *PL_IOreference_Config;
	PL_IOreference_Config = XGpioPs_LookupConfig(XPAR_PSU_GPIO_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&myPlGpio, PL_IOreference_Config, PL_IOreference_Config->BaseAddr);
	XGpioPs_SetDirection(&myPlGpio, 5, 0xffffffff); //"bits with 1 are	set to Output Mode"; UG1085 (v2.3) p.776


	// change MPU Config for R5 -> BRAM write process
	//Xil_UpdateMPUConfig(1, 0x80000000, REGION_1G, NORM_NSHARED_WB_WA | PRIV_RW_USER_RW);
	//Xil_UpdateMPUConfig(1, XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, REGION_256K, NORM_NSHARED_WB_WA | PRIV_RW_USER_RW);
	//Xil_SetMPURegionByRegNum(1, 0x80000000 , REGION_1G, NORM_NSHARED_WT_NWA | PRIV_RW_USER_RW);
	//Xil_SetMPURegionByRegNum(15, XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR , REGION_256K, NORM_NSHARED_WT_NWA | PRIV_RW_USER_RW);
	//XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, REGION_256K

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
	js_ch_observable[JSO_Speed_rpm]		= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_ia] 			= &data->av.I_U;
	js_ch_observable[JSO_ib] 			= &data->av.I_V;
	js_ch_observable[JSO_ic] 			= &data->av.I_W;
	js_ch_observable[JSO_ua] 			= &data->av.U_U;
	js_ch_observable[JSO_ub] 			= &data->av.U_V;
	js_ch_observable[JSO_uc] 			= &data->av.U_W;
	js_ch_observable[JSO_iq] 			= &data->av.I_q;
	js_ch_observable[JSO_id] 			= &data->av.I_d;
	js_ch_observable[JSO_Theta_el] 		= &data->av.theta_elec;
	js_ch_observable[JSO_theta_mech] 	= &data->av.theta_mech;
	js_ch_observable[JSO_ud]			= &data->av.U_d;
	js_ch_observable[JSO_uq]			= &data->av.U_q;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;
	// OCM test:
//	js_ch_observable[JSO_PL_Data_1]		= (float *)0xA0000000U; //0x00FFFC0000;
//	js_ch_observable[JSO_PL_Data_2]		= (float *)0xA0000004U; //0x00FFFC0004;
	/*js_ch_observable[JSO_PL_Data_3]		= (float *)0x00FFFC0008;
	js_ch_observable[JSO_PL_Data_4]		= (float *)0x00FFFC000C;
	js_ch_observable[JSO_PL_Data_5]		= (float *)0x00FFFC0010;
	js_ch_observable[JSO_PL_Data_6]		= (float *)0x00FFFC0014;
	js_ch_observable[JSO_PL_Data_7]		= (float *)0x00FFFC0018;*/
	// BRAM test:

	/*js_ch_observable[JSO_PL_Data_1]		= &log_array[0];
	js_ch_observable[JSO_PL_Data_2]		= &log_array[1];
	js_ch_observable[JSO_PL_Data_3]		= &log_array[2];
	js_ch_observable[JSO_PL_Data_4]		= &log_array[3];
	js_ch_observable[JSO_PL_Data_5]		= &log_array[4];
	js_ch_observable[JSO_PL_Data_6]		= &log_array[5];
	js_ch_observable[JSO_PL_Data_7]		= &log_array[6];*/


	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_u_d] 			        = &(data->av.U_d);
	js_slowDataArray[JSSD_FLOAT_u_q] 			        = &(data->av.U_q);
	js_slowDataArray[JSSD_FLOAT_i_d] 			        = &(data->av.I_d);
	js_slowDataArray[JSSD_FLOAT_i_q] 			        = &(data->av.I_q);
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.mechanicalRotorSpeed);
	js_slowDataArray[JSSD_FLOAT_torque] 		        = &(data->av.mechanicalTorqueObserved);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;

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
	//Data_Logger_out			= XUz_log_data_Get_dlog_1(&PL_Logger_1);
	//Data_Logger_out			= (float)0x00FFFC0004;

	/*float log_array_local[64];
	js_ch_observable[JSO_PL_Data_1]		= &log_array_local[0];
	js_ch_observable[JSO_PL_Data_2]		= &log_array_local[1];
	memcpy(log_array_local, XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(log_array_local));*/

// BRAM - RPU COMMUNICATION
	// Write data to the BRAM
/*	int write_array_local[128];
	PS_TO_BRAM_WORDCOUNT = sizeof(write_array_local)/sizeof(write_array_local[0]);
	for(int i=0; i<PS_TO_BRAM_WORDCOUNT; i++){
		write_array_local[i] = rand();
	}
*/

	//Xil_DCacheInvalidateRange(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(write_array_local));
	//Xil_DCacheFlushRange(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(write_array_local));
	//Xil_DCacheFlush();
	//Xil_DCacheInvalidate();
/*
	xDifference_us = (float)(xEnd-xStart)/(COUNTS_PER_SECOND/1000000);
	xDifference_us = (float)(xEnd-xStart)/COUNTS_PER_USECOND;
	xDifference_s = (float)(xEnd-xStart)/(COUNTS_PER_SECOND);
*/

	// write data to shared memory
	// NORM_NSHARED_WT_NWA | PRIV_RW_USER_RW oder NORM_NSHARED_WB_WA oder NORM_NSHARED_WB_NWA
	for(int j=0; j<JS_CHANNELS; j++){

		//Xil_GetMPUConfig(tmp_MPU_readout);
		// printf("\n Status: %x", tmp_MPU_readout[1].RegionStatus);
		// printf("\n Attribute: %x", tmp_MPU_readout[1].Attribute);

		javascope_data->scope_ch[j] = *js_ch_selected[j];

	}

	javascope_data->slowDataID 		= js_cnt_slowData;
	javascope_data->slowDataContent = *js_slowDataArray[js_cnt_slowData];
	javascope_data->status 			= js_status_BareToRTOS;

	// flush data cache of shared memory region to make sure shared memory is updated
	Xil_DCacheFlushRange(MEM_SHARED_START, JAVASCOPE_DATA_SIZE_2POW);
	//Xil_DCacheFlushRange(0x00FFFC0000, 16);


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

	// XGpioPs_WritePin(&myPlGpio, 164, 1); //between memcpy and flush
	// Xil_DCacheFlushRange(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(write_array_local));
	// Xil_DCacheFlush();

	ipc_Control_func(Received_Data_from_A53.id, Received_Data_from_A53.value, data);
	//XGpio_DiscreteWrite(&PLtoggle, 1, 1);
	Xil_GetMPUConfig(tmp_MPU_readout);
	XGpioPs_WritePin(&myPlGpio, 163, 1);
	XTime_GetTime(&xStart);
	memcpy((void*)XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, write_array_local, sizeof(write_array_local));
	Xil_DCacheFlush();
	XTime_GetTime(&xEnd);
	xDifference_us = (float)(xEnd-xStart)/(COUNTS_PER_SECOND/1000000);
	asm("nop;");
	XGpioPs_WritePin(&myPlGpio, 163, 0);
	XGpioPs_WritePin(&myPlGpio, 164, 0);

	if(cnt_to_50<50){
		DiffArray[cnt_to_50] = xDifference_us;
	}
	cnt_to_50++;

}
