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

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

//IP-Cores for 6 Phase FSC-MPC
float d_current_vsd_and_park_transformation;
float q_current_vsd_and_park_transformation;
float alpha_current_vsd_and_park_transformation;
float beta_current_vsd_and_park_transformation;
float x_current_vsd_and_park_transformation;
float y_current_vsd_and_park_transformation;
float a1_current_vsd_and_park_transformation;
float b1_current_vsd_and_park_transformation;
float c1_current_vsd_and_park_transformation;
float a2_current_vsd_and_park_transformation;
float b2_current_vsd_and_park_transformation;
float c2_current_vsd_and_park_transformation;

float idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
float iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
float ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
float iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;

float d_voltage_per_switching_state;
float q_voltage_per_switching_state;
float x_voltage_per_switching_state;
float y_voltage_per_switching_state;

float J_AXI;

float last_applied_optimal_voltage_d;
float last_applied_optimal_voltage_q;
float last_applied_optimal_voltage_x;
float last_applied_optimal_voltage_y;

int JavaScope_initalize(DS_Data* data)
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
	js_ch_observable[JSO_d_current_vsd_and_park_transformation] = &d_current_vsd_and_park_transformation;
	js_ch_observable[JSO_q_current_vsd_and_park_transformation] = &q_current_vsd_and_park_transformation;
	js_ch_observable[JSO_alpha_current_vsd_and_park_transformation] = &alpha_current_vsd_and_park_transformation;
	js_ch_observable[JSO_beta_current_vsd_and_park_transformation] = &beta_current_vsd_and_park_transformation;
	js_ch_observable[JSO_x_current_vsd_and_park_transformation] = &x_current_vsd_and_park_transformation;
	js_ch_observable[JSO_y_current_vsd_and_park_transformation] = &y_current_vsd_and_park_transformation;
	js_ch_observable[JSO_a1_current_vsd_and_park_transformation] = &a1_current_vsd_and_park_transformation;
	js_ch_observable[JSO_b1_current_vsd_and_park_transformation] = &b1_current_vsd_and_park_transformation;
	js_ch_observable[JSO_c1_current_vsd_and_park_transformation] = &c1_current_vsd_and_park_transformation;
	js_ch_observable[JSO_a2_current_vsd_and_park_transformation] = &a2_current_vsd_and_park_transformation;
	js_ch_observable[JSO_b2_current_vsd_and_park_transformation] = &b2_current_vsd_and_park_transformation;
	js_ch_observable[JSO_c2_current_vsd_and_park_transformation] = &c2_current_vsd_and_park_transformation;
	js_ch_observable[JSO_idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm] = &idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
	js_ch_observable[JSO_iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm] = &iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
	js_ch_observable[JSO_ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm] = &ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
	js_ch_observable[JSO_iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm] = &iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
	js_ch_observable[JSO_d_voltage_per_switching_state] = &d_voltage_per_switching_state;
	js_ch_observable[JSO_q_voltage_per_switching_state] = &q_voltage_per_switching_state;
	js_ch_observable[JSO_x_voltage_per_switching_state] = &x_voltage_per_switching_state;
	js_ch_observable[JSO_y_voltage_per_switching_state] = &y_voltage_per_switching_state;
	js_ch_observable[JSO_J_AXI] = &J_AXI;
	js_ch_observable[JSO_last_applied_optimal_voltage_d] = &last_applied_optimal_voltage_d;
	js_ch_observable[JSO_last_applied_optimal_voltage_q] = &last_applied_optimal_voltage_q;
	js_ch_observable[JSO_last_applied_optimal_voltage_x] = &last_applied_optimal_voltage_x;
	js_ch_observable[JSO_last_applied_optimal_voltage_y] = &last_applied_optimal_voltage_y;

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
