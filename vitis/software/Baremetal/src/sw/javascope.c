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
extern uz_3ph_abc_t three_phase_output;
extern struct uz_pmsmModel_outputs_t pmsm_outputs;
extern struct uz_pmsmModel_inputs_t pmsm_inputs;
extern struct uz_3ph_dq_t measured_currents_dq_Amp;
extern struct uz_3ph_dq_t FOC_output_Volts;
extern struct uz_3ph_abc_t measured_currents_uvw_Amp;
extern struct uz_3ph_dq_t measured_voltage_dq_V;
extern struct uz_3ph_dq_t reference_currents_Amp;


extern struct DS_Data data;
extern float i_u_A;
extern float option_js;
extern float torque_meas_filtered;
extern float theta_offset;

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
	js_ch_observable[JSO_i_a_meas] = &measured_currents_uvw_Amp.a;
	js_ch_observable[JSO_i_b_meas] = &measured_currents_uvw_Amp.b;
	js_ch_observable[JSO_i_c_meas] = &measured_currents_uvw_Amp.c;
	js_ch_observable[JSO_i_q_meas] = &measured_currents_dq_Amp.q;
	js_ch_observable[JSO_i_d_meas] = &measured_currents_dq_Amp.d;
	js_ch_observable[JSO_i_q_ref] = &reference_currents_Amp.q;
	js_ch_observable[JSO_i_d_ref] = &reference_currents_Amp.d;
	js_ch_observable[JSO_u_a_meas] = &data->av.U_L1;
	js_ch_observable[JSO_u_b_meas] = &data->av.U_L2;
	js_ch_observable[JSO_u_c_meas] = &data->av.U_L3;
	js_ch_observable[JSO_v_d_FOC] = &FOC_output_Volts.d;
	js_ch_observable[JSO_v_q_FOC] = &FOC_output_Volts.q;
	js_ch_observable[JSO_v_d_meas] = &measured_voltage_dq_V.d;
	js_ch_observable[JSO_v_q_meas] = &measured_voltage_dq_V.q;
	js_ch_observable[JSO_rpm] = &data->av.mechanicalRotorSpeed_filtered;
	js_ch_observable[JSO_theta_mech] = &data->av.theta_elec;
	js_ch_observable[JSO_torque_meas] = &data->av.mechanicalTorqueObserved;
	js_ch_observable[JSO_torque_meas_filtered] = &torque_meas_filtered;
	js_ch_observable[JSO_option] = &option_js;
	js_ch_observable[JSO_theta_offset] = &theta_offset;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_i_a_meas] 								= &(measured_currents_uvw_Amp.a);
	js_slowDataArray[JSSD_FLOAT_i_b_meas] 								= &(measured_currents_uvw_Amp.b);
	js_slowDataArray[JSSD_FLOAT_i_c_meas] 								= &(measured_currents_uvw_Amp.c);
	js_slowDataArray[JSSD_FLOAT_i_q_meas] 								= &(measured_currents_dq_Amp.q);
	js_slowDataArray[JSSD_FLOAT_i_d_meas] 								= &(measured_currents_dq_Amp.d);
	js_slowDataArray[JSSD_FLOAT_i_q_ref] 								= &(reference_currents_Amp.q);
	js_slowDataArray[JSSD_FLOAT_i_d_ref] 								= &(reference_currents_Amp.d);
	js_slowDataArray[JSSD_FLOAT_u_a_meas] 								= &(data->av.U_L1);
	js_slowDataArray[JSSD_FLOAT_u_b_meas] 								= &(data->av.U_L2);
	js_slowDataArray[JSSD_FLOAT_u_c_meas] 								= &(data->av.U_L3);
	js_slowDataArray[JSSD_FLOAT_v_d_FOC] 								= &(FOC_output_Volts.d);
	js_slowDataArray[JSSD_FLOAT_v_q_FOC] 								= &(FOC_output_Volts.q);
	js_slowDataArray[JSSD_FLOAT_v_d_meas] 								= &(measured_voltage_dq_V.d);
	js_slowDataArray[JSSD_FLOAT_v_q_meas] 								= &(measured_voltage_dq_V.q);
	js_slowDataArray[JSSD_FLOAT_rpm] 									= &(data->av.mechanicalRotorSpeed_filtered);
	js_slowDataArray[JSSD_FLOAT_theta_mech] 							= &(data->av.theta_elec);
	js_slowDataArray[JSSD_FLOAT_torque_meas] 							= &(data->av.mechanicalTorqueObserved);
	js_slowDataArray[JSSD_FLOAT_torque_meas_filtered] 					= &(torque_meas_filtered);
	js_slowDataArray[JSSD_FLOAT_option] 								= &(option_js);
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 						= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 							= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]							= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart] 				= &(System_UpTime_seconds);

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
