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

extern uz_3ph_dq_t i_dq_reference; 
extern uz_3ph_dq_t i_xy_reference; 
//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!
extern float start_marker;

extern uz_3ph_dq_t v_dq_non_limited_volts;
extern uz_3ph_dq_t v_xy_non_limited_volts;
extern uz_3ph_dq_t v_dq_limited_volts;
extern uz_3ph_dq_t v_xy_limited_volts;

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
	js_ch_observable[JSO_Speed_rpm]		= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_el_Speed_rpm]	= &data->av.electricalRotorSpeed;
	js_ch_observable[JSO_ia1] 			= &data->av.i_a1;
	js_ch_observable[JSO_ib1] 			= &data->av.i_b1;
	js_ch_observable[JSO_ic1] 			= &data->av.i_c1;
	js_ch_observable[JSO_ia2] 			= &data->av.i_a2;
	js_ch_observable[JSO_ib2] 			= &data->av.i_b2;
	js_ch_observable[JSO_ic2] 			= &data->av.i_c2;
	js_ch_observable[JSO_va1] 			= &data->av.v_a1;
	js_ch_observable[JSO_vb1] 			= &data->av.v_b1;
	js_ch_observable[JSO_vc1] 			= &data->av.v_c1;
	js_ch_observable[JSO_va2] 			= &data->av.v_a2;
	js_ch_observable[JSO_vb2] 			= &data->av.v_b2;
	js_ch_observable[JSO_vc2] 			= &data->av.v_c2;
	js_ch_observable[JSO_iq] 			= &data->av.I_q;
	js_ch_observable[JSO_iX]			= &data->av.I_X;
	js_ch_observable[JSO_iY]			= &data->av.I_Y;
	js_ch_observable[JSO_id] 			= &data->av.I_d;
	js_ch_observable[JSO_v_d_non] 			= &v_dq_non_limited_volts.d;
	js_ch_observable[JSO_v_q_non] 			= &v_dq_non_limited_volts.q;
	js_ch_observable[JSO_v_x_non] 			= &v_xy_non_limited_volts.d;
	js_ch_observable[JSO_v_y_non] 			= &v_xy_non_limited_volts.q;
	js_ch_observable[JSO_v_d_lim] = &v_dq_limited_volts.d;//k
	js_ch_observable[JSO_v_q_lim] = &v_dq_limited_volts.q;
	js_ch_observable[JSO_v_x_lim] = &v_xy_limited_volts.d;
	js_ch_observable[JSO_v_y_lim] = &v_xy_limited_volts.q;
	js_ch_observable[JSO_id_ref] = &i_dq_reference.d;
	js_ch_observable[JSO_iq_ref] = &i_dq_reference.q;
	js_ch_observable[JSO_iX_ref] = &i_xy_reference.d;
	js_ch_observable[JSO_iY_ref] = &i_xy_reference.q;
	js_ch_observable[JSO_start_marker] 			= &start_marker;
	js_ch_observable[JSO_Theta_el] 		= &data->av.theta_elec;
	js_ch_observable[JSO_theta_mech] 	= &data->av.theta_mech;
	js_ch_observable[JSO_ud]			= &data->av.U_d;//k-1
	js_ch_observable[JSO_uq]			= &data->av.U_q;
	js_ch_observable[JSO_uX]			= &data->av.U_X;
	js_ch_observable[JSO_uY]			= &data->av.U_Y;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;

	js_ch_observable[JSO_i_c1_pu]	= &data->av.i_c1_pu;
	js_ch_observable[JSO_i_b1_pu]	= &data->av.i_b1_pu;
	js_ch_observable[JSO_i_a1_pu]	= &data->av.i_a1_pu;
	js_ch_observable[JSO_i_c2_pu]	= &data->av.i_c2_pu;
	js_ch_observable[JSO_i_b2_pu]	= &data->av.i_b2_pu;
	js_ch_observable[JSO_i_a2_pu]	= &data->av.i_a2_pu;
	js_ch_observable[JSO_v_dc1_ip]	= &data->av.v_dc1_ip;
	js_ch_observable[JSO_v_dc2_ip]	= &data->av.v_dc2_ip;
	js_ch_observable[JSO_i_alpha_ip]	= &data->av.i_alpha_ip;
	js_ch_observable[JSO_i_beta_ip]	= &data->av.i_beta_ip;
	js_ch_observable[JSO_i_X_ip]	= &data->av.i_X_ip;
	js_ch_observable[JSO_i_Y_ip]	= &data->av.i_Y_ip;
	js_ch_observable[JSO_i_0p_ip]	= &data->av.i_0p_ip;
	js_ch_observable[JSO_i_0n_ip]	= &data->av.i_0n_ip;
	js_ch_observable[JSO_i_d_ip]	= &data->av.i_d_ip;
	js_ch_observable[JSO_i_q_ip]	= &data->av.i_q_ip;
	js_ch_observable[JSO_omega_ip]	= &data->av.omega_ip;




	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_TEMP_VSI1] 			    = &(data->av.temp_VSI_1);
	js_slowDataArray[JSSD_FLOAT_TEMP_VSI2] 			    = &(data->av.temp_VSI_2);
	js_slowDataArray[JSSD_FLOAT_V_DC_1]					= &(data->av.v_dc1);
	js_slowDataArray[JSSD_FLOAT_V_DC_2]					= &(data->av.v_dc2);
	js_slowDataArray[JSSD_FLOAT_u_d] 			        = &(data->av.U_d);
	js_slowDataArray[JSSD_FLOAT_u_q] 			        = &(data->av.U_q);
	js_slowDataArray[JSSD_FLOAT_i_d] 			        = &(data->av.I_d);
	js_slowDataArray[JSSD_FLOAT_i_q] 			        = &(data->av.I_q);
	js_slowDataArray[JSSD_FLOAT_u_X] 			        = &(data->av.U_X);
	js_slowDataArray[JSSD_FLOAT_u_Y] 			        = &(data->av.U_Y);
	js_slowDataArray[JSSD_FLOAT_i_X] 			        = &(data->av.I_X);
	js_slowDataArray[JSSD_FLOAT_i_Y] 			        = &(data->av.I_Y);
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
