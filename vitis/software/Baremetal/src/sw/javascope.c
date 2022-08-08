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

#include "../IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"


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


extern struct uz_pmsm_model9ph_dq_outputs_general_t pmsm_outputs;
extern uz_9ph_abc_t setpoint_natural;
extern uz_9ph_abc_t pmsm_output_currents;
extern uz_9ph_alphabeta_t stationary_currents;
extern uz_3ph_dq_t outputs_dq;
extern uz_3ph_dq_t setpoint_dq;
extern uz_9ph_abc_t actual_currents_abc;
extern uz_9ph_dq_t actual_currents_dq;
extern uz_9ph_dq_t in_voltage_dq;

extern float setp_omega;
extern float setp_q;
extern uz_3ph_dq_t current_set_point;

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
	js_ch_observable[JSO_Speed_rpm]		= &pmsm_outputs.omega_mech;
		js_ch_observable[JSO_ib1] 			= &actual_currents_abc.b1;
		js_ch_observable[JSO_ia1] 			= &actual_currents_abc.a1;
		js_ch_observable[JSO_ic1] 			= &actual_currents_abc.c1;
		js_ch_observable[JSO_ia2] 			= &actual_currents_abc.a2;
		js_ch_observable[JSO_ib2] 			= &actual_currents_abc.b2;
		js_ch_observable[JSO_ic2] 			= &actual_currents_abc.c2;
		js_ch_observable[JSO_ia3] 			= &actual_currents_abc.a3;
		js_ch_observable[JSO_ib3] 			= &actual_currents_abc.b3;
		js_ch_observable[JSO_ic3] 			= &actual_currents_abc.c3;
		js_ch_observable[JSO_iq] 			= &actual_currents_dq.q;
		js_ch_observable[JSO_id] 			= &actual_currents_dq.d;
		js_ch_observable[JSO_ix1] 			= &actual_currents_dq.x1;
		js_ch_observable[JSO_iy1] 			= &actual_currents_dq.y1;
		js_ch_observable[JSO_ix2] 			= &actual_currents_dq.x2;
		js_ch_observable[JSO_iy2] 			= &actual_currents_dq.y2;
		js_ch_observable[JSO_ix3] 			= &actual_currents_dq.x3;
		js_ch_observable[JSO_iy3] 			= &actual_currents_dq.y3;
		js_ch_observable[JSO_izero] 			= &actual_currents_dq.zero;
		js_ch_observable[JSO_ud] 			= &in_voltage_dq.d;
		js_ch_observable[JSO_uq] 			= &in_voltage_dq.q;
		js_ch_observable[JSO_ux1] 			= &in_voltage_dq.x1;
		js_ch_observable[JSO_uy1] 			= &in_voltage_dq.y1;
		js_ch_observable[JSO_ux2] 			= &in_voltage_dq.x2;
		js_ch_observable[JSO_uy2] 			= &in_voltage_dq.y2;
		js_ch_observable[JSO_ux3] 			= &in_voltage_dq.x3;
		js_ch_observable[JSO_uy3] 			= &in_voltage_dq.y3;
		js_ch_observable[JSO_uzero] 			= &in_voltage_dq.zero;
		js_ch_observable[JSO_id_setpoint]   = &current_set_point.d;
		js_ch_observable[JSO_iq_setpoint]   = &current_set_point.q;
		js_ch_observable[JSO_Theta_el] 		= &pmsm_outputs.theta_el;
		js_ch_observable[JSO_setp_omega] 	= &setp_omega;
		js_ch_observable[JSO_lifecheck]   	= &lifecheck;


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
