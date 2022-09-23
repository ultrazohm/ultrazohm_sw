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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_VSD_6ph_FD/uz_VSD6phFD.h"

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


extern uz_6ph_alphabeta_t i_abxyz1z2_filtered;


extern float vsd_output[6];
extern float vsd_output_filtered[6];
extern float vsd_output_hyst[6];

extern float vsd_output_V4[6];
extern float vsd_output_hyst_V4[6];
extern float vsd_output_filtered_V4[6];

extern float Rb1[5];
extern float Rb1_filtered[5];

extern uz_6phFD_indices R_FD_Filt;
extern uz_6phFD_indices R_FD;
extern uz_6phFD_indices R_FD_eval;

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

extern float filteredFDIndices[6];

extern float singleIndex_FD_R;

extern float testvalue;

extern float m_ab_n_currents[2];
extern float ref_ab_currents[2];
extern float ref_ab_n_currents[2];
extern float m_ab_currents[2];
extern float m_ab_n_currents_testvariable[2];
extern float m_ab_n_currents_testvariable2[2];
extern float m_ab_n_currents_testvariable3[2];

extern float zw_1;
extern float zw_2;
extern float ref_xy_voltage_n[2];
extern float ref_xy_voltage_s[2];

extern float ref_xy_currents[2];
extern float ref_z1z2_currents[2];
extern uz_3ph_alphabeta_t ref_alphabeta_currents;

extern float ref_xy_voltage[2];
extern float m_xy_s_currents[2];
extern float ref_xy_s_currents[2];
extern float m_xy_n_currents[2];
extern float ref_xy_n_currents[2];
extern float ref_z1z2_voltage[2];

extern float ref_z1z2_n_voltage[2];
extern float ref_z1z2_s_voltage[2];

extern float z1z2_error[2];
extern float error_z1z2_s[2];
extern float error_z1z2_n[2];
extern float xy_error[2];

extern uz_3ph_dq_t value_1;
extern uz_6ph_alphabeta_t value_2;
extern uz_6ph_abc_t value_3;

extern int display_OPF_f;

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

	js_ch_observable[JSO_i_a1] = &data->av.I_U;
	js_ch_observable[JSO_i_b1] = &data->av.I_V;
	js_ch_observable[JSO_i_c1] = &data->av.I_W;
	js_ch_observable[JSO_i_a2] = &data->av.I_X;
	js_ch_observable[JSO_i_b2] = &data->av.I_Y;
	js_ch_observable[JSO_i_c2] = &data->av.I_Z;
	js_ch_observable[JSO_i_alpha] = &data->av.I_alpha;
	js_ch_observable[JSO_i_beta] = &data->av.I_beta;
	js_ch_observable[JSO_i_x] = &data->av.I_x;
	js_ch_observable[JSO_i_y] = &data->av.I_y;
	js_ch_observable[JSO_i_z1] = &data->av.I_z1;
	js_ch_observable[JSO_i_z2] = &data->av.I_z2;

	js_ch_observable[JSO_FD_a1] = &vsd_output[0];
	js_ch_observable[JSO_FD_b1] = &vsd_output[1];
	js_ch_observable[JSO_FD_c1] = &vsd_output[2];
	js_ch_observable[JSO_FD_a2] = &vsd_output[3];
	js_ch_observable[JSO_FD_b2] = &vsd_output[4];
	js_ch_observable[JSO_FD_c2] = &vsd_output[5];
	js_ch_observable[JSO_FD_Hyst_a1] = &vsd_output_hyst[0];
	js_ch_observable[JSO_FD_Hyst_b1] = &vsd_output_hyst[1];
	js_ch_observable[JSO_FD_Hyst_c1] = &vsd_output_hyst[2];
	js_ch_observable[JSO_FD_Hyst_a2] = &vsd_output_hyst[3];
	js_ch_observable[JSO_FD_Hyst_b2] = &vsd_output_hyst[4];
	js_ch_observable[JSO_FD_Hyst_c2] = &vsd_output_hyst[5];
	js_ch_observable[JSO_FD_Filtered_a1] = &vsd_output_filtered[0];
	js_ch_observable[JSO_FD_Filtered_b1] = &vsd_output_filtered[1];
	js_ch_observable[JSO_FD_Filtered_c1] = &vsd_output_filtered[2];
	js_ch_observable[JSO_FD_Filtered_a2] = &vsd_output_filtered[3];
	js_ch_observable[JSO_FD_Filtered_b2] = &vsd_output_filtered[4];
	js_ch_observable[JSO_FD_Filtered_c2] = &vsd_output_filtered[5];

	js_ch_observable[JSO_FD_MOVAVG_a1] = &filteredFDIndices[0];
	js_ch_observable[JSO_FD_MOVAVG_b1] = &filteredFDIndices[1];
	js_ch_observable[JSO_FD_MOVAVG_c1] = &filteredFDIndices[2];
	js_ch_observable[JSO_FD_MOVAVG_a2] = &filteredFDIndices[3];
	js_ch_observable[JSO_FD_MOVAVG_b2] = &filteredFDIndices[4];
	js_ch_observable[JSO_FD_MOVAVG_c2] = &filteredFDIndices[5];

	//R_FD_eval
	js_ch_observable[JSO_Testvalue_1] = &ref_z1z2_n_voltage[0];
	js_ch_observable[JSO_Testvalue_2] = &ref_z1z2_n_voltage[1];
	js_ch_observable[JSO_Testvalue_3] = &ref_z1z2_s_voltage[0];
	js_ch_observable[JSO_Testvalue_4] = &ref_z1z2_s_voltage[1];



	js_ch_observable[JSO_Testvalue_5] = &ref_alphabeta_currents.alpha;
	js_ch_observable[JSO_Testvalue_6] = &ref_alphabeta_currents.beta;
	js_ch_observable[JSO_Testvalue_7] = &ref_xy_currents[0];
	js_ch_observable[JSO_Testvalue_8] = &ref_xy_currents[1];
	js_ch_observable[JSO_Testvalue_9] = &ref_z1z2_currents[0];
	js_ch_observable[JSO_Testvalue_10] = &ref_z1z2_currents[1];


	/*
	js_ch_observable[JSO_Testvalue_5] = &value_3.a1;
	js_ch_observable[JSO_Testvalue_6] = &value_3.b1;
	js_ch_observable[JSO_Testvalue_7] = &value_3.c1;
	js_ch_observable[JSO_Testvalue_8] = &value_3.a2;
	js_ch_observable[JSO_Testvalue_9] = &value_3.b2;
	js_ch_observable[JSO_Testvalue_10] = &value_3.c2;
*/



	js_ch_observable[JSO_Testvalue_11] = &ref_xy_voltage[0];
	js_ch_observable[JSO_Testvalue_12] = &ref_xy_voltage[1];
	js_ch_observable[JSO_Testvalue_13] = &xy_error[0];
	js_ch_observable[JSO_Testvalue_14] = &xy_error[1];

	/*
	js_ch_observable[JSO_Testvalue_15] = &ref_xy_voltage_n[0];
	js_ch_observable[JSO_Testvalue_16] = &ref_xy_voltage_n[1];
	js_ch_observable[JSO_Testvalue_17] = &ref_xy_voltage_s[0];
	js_ch_observable[JSO_Testvalue_18] = &ref_xy_voltage_s[1];
	 */

	js_ch_observable[JSO_Testvalue_15] = & m_xy_n_currents[0];
	js_ch_observable[JSO_Testvalue_16] = & m_xy_n_currents[1];
	js_ch_observable[JSO_Testvalue_17] = &ref_z1z2_voltage[0];
	js_ch_observable[JSO_Testvalue_18] = &ref_z1z2_voltage[1];

/*
	js_ch_observable[JSO_Testvalue_11] = &value_1.d;
	js_ch_observable[JSO_Testvalue_12] = &value_1.q;
	js_ch_observable[JSO_Testvalue_13] = &value_2.alpha;
	js_ch_observable[JSO_Testvalue_14] = &value_2.beta;
	js_ch_observable[JSO_Testvalue_15] = &value_2.x;
	js_ch_observable[JSO_Testvalue_16] = &value_2.y;
	js_ch_observable[JSO_Testvalue_17] = &value_2.z1;
	js_ch_observable[JSO_Testvalue_18] = &value_2.z2;
*/



	js_ch_observable[JSO_SingleIndex_R] = &singleIndex_FD_R;



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
	js_slowDataArray[JSSD_FLOAT_GAN_Temp_D3_H1]			= &(data->objects.gan_inverter_outputs_D3.GaN_ChipTempDegreesCelsius_H1);
	js_slowDataArray[JSSD_FLOAT_GAN_Temp_D3_H2]			= &(data->objects.gan_inverter_outputs_D3.GaN_ChipTempDegreesCelsius_H2);
	js_slowDataArray[JSSD_FLOAT_GAN_Temp_D3_H3]			= &(data->objects.gan_inverter_outputs_D3.GaN_ChipTempDegreesCelsius_H3);
	js_slowDataArray[JSSD_FLOAT_GAN_Temp_D4_H1]			= &(data->objects.gan_inverter_outputs_D4.GaN_ChipTempDegreesCelsius_H1);
	js_slowDataArray[JSSD_FLOAT_GAN_Temp_D4_H2]			= &(data->objects.gan_inverter_outputs_D4.GaN_ChipTempDegreesCelsius_H2);
	js_slowDataArray[JSSD_FLOAT_GAN_Temp_D4_H3]			= &(data->objects.gan_inverter_outputs_D4.GaN_ChipTempDegreesCelsius_H3);
	js_slowDataArray[JSSD_FLOAT_I_a1] = &(data->av.I_U_Filtered);
	js_slowDataArray[JSSD_FLOAT_I_b1] = &(data->av.I_V_Filtered);
	js_slowDataArray[JSSD_FLOAT_I_c1] = &(data->av.I_W_Filtered);
	js_slowDataArray[JSSD_FLOAT_I_a2] = &(data->av.I_X_Filtered);
	js_slowDataArray[JSSD_FLOAT_I_b2] = &(data->av.I_Y_Filtered);
	js_slowDataArray[JSSD_FLOAT_I_c2] = &(data->av.I_Z_Filtered);
	js_slowDataArray[JSSD_FLOAT_display_OPF] = &(display_OPF_f);

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
