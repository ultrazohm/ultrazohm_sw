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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "xil_cache.h"

//Variables for JavaScope
static float zerovalue = 0.0;
static float *js_slowDataArray[JSSD_ENDMARKER];
float *js_ch_observable[JSO_ENDMARKER];
float *js_ch_selected[JS_CHANNELS];
extern float position_abs;
extern float position_ref;
extern float input_nn[5];
extern float dqn_mutex_float;
extern float position_target;
static float lifecheck;
static float ISR_execution_time_us;
static float ISR_period_us;
static float System_UpTime_seconds;
static float System_UpTime_ms;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!


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
	js_ch_observable[JSO_Speed_rpm]	= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_trigger]	= &data->av.trigger_logging;
	js_ch_observable[JSO_Speed_filtered]	= &data->av.mechanicalRotorSpeed_filtered;
	js_ch_observable[JSO_d_ref]		= &data->rasv.dq_reference_current.d;
	js_ch_observable[JSO_q_ref]		= &data->rasv.dq_reference_current.q;
	js_ch_observable[JSO_n_ref]		= &data->rasv.n_ref_rpm;
	js_ch_observable[JSO_position_motor]	= &data->av.position_motor;
	js_ch_observable[JSO_thetapendulum]	= &data->av.theta_pendulum;
	js_ch_observable[JSO_position_abs]		= &position_abs;
	js_ch_observable[JSO_position_target]		= &position_target;
	js_ch_observable[JSO_ia] 				= &data->mv.measurement_current.a;
	js_ch_observable[JSO_ib] 				= &data->mv.measurement_current.b;
	js_ch_observable[JSO_ic] 				= &data->mv.measurement_current.c;
	js_ch_observable[JSO_dqn_chart_error] 	= &data->obs.dqn_chart_error;
	js_ch_observable[JSO_dqn_angle_derv] 		= &data->obs.dqn_angle_derv;
	js_ch_observable[JSO_dqn_chart_position_derv]= &data->obs.dqn_chart_position_derv;
	js_ch_observable[JSO_dqn_angle] = 				&data->obs.dqn_angle;
	js_ch_observable[JSO_dqn_angle_derv_raw] 		= &data->obs.dqn_angle_derv_raw;
	js_ch_observable[JSO_dqn_chart_position_derv_raw]= &data->obs.dqn_chart_position_derv_raw;
	js_ch_observable[JSO_dqn_angle_raw] = 				&data->obs.dqn_angle_raw;
	js_ch_observable[JSO_iq] 			= &data->mv.dq_measurement_current.q;
	js_ch_observable[JSO_id] 			= &data->mv.dq_measurement_current.d;
	js_ch_observable[JSO_ud]			=&data->rasv.dq_ref_Volts.d;
	js_ch_observable[JSO_uq]			=&data->rasv.dq_ref_Volts.q;
	js_ch_observable[JSO_Theta_el] 		= &data->av.theta_elec;
	js_ch_observable[JSO_Theta_mech] 	= &data->av.theta_mech;
	js_ch_observable[JSO_Speed_IIR_Filter]= &data->av.mechanicalRotorSpeed_IIR_Filter;
	js_ch_observable[JSO_dqn_sin_angle]			= &data->obs.dqn_sin_angle;
	js_ch_observable[JSO_dqn_cos_angle]			= &data->obs.dqn_cos_angle;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_dqn_mutex]   	= &dqn_mutex_float;
	js_ch_observable[JSO_x_0_input]   	= &input_nn[0];
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;

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
