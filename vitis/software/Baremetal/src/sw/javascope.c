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
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

// External
extern float theta_el_rad_hoerner;
extern float theta_el_rad_beckhoff;
extern struct uz_3ph_abc_t i_abc_Amps_hoener;
extern struct uz_3ph_abc_t i_abc_Amps_beckhoff;
extern struct uz_3ph_dq_t i_dq_Amps_hoerner;
extern struct uz_3ph_dq_t i_dq_Amps_beckhoff;
extern struct uz_3ph_dq_t i_dqn_filtered_5th_Amps_hoerner;
extern struct uz_3ph_dq_t i_dqn_filtered_7th_Amps_hoerner;
extern struct uz_3ph_dq_t v_dq_Volts_beckhoff;
extern struct uz_3ph_dq_t v_dq_Volts_hoerner;
extern struct uz_3ph_abc_t v_abc_Volts_hoerner;
extern float observation_ip[9U];
float Torque_placeholder = 0.0f;
//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!


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
	js_ch_observable[JSO_ISR_ExecTime_us]=&ISR_execution_time_us;
	js_ch_observable[JSO_ISR_Period_us]=&ISR_period_us;
	js_ch_observable[JSO_lifecheck]=&lifecheck;
	js_ch_observable[JSO_dut_ia]=&data->dut.actual_data->i_abc_in_A.a;
	js_ch_observable[JSO_dut_ib]=&data->dut.actual_data->i_abc_in_A.b;
	js_ch_observable[JSO_dut_ic]=&data->dut.actual_data->i_abc_in_A.c;
	js_ch_observable[JSO_dut_id]=&data->dut.actual_data->i_dq_in_A.d;
	js_ch_observable[JSO_dut_iq]=&data->dut.actual_data->i_dq_in_A.q;
	js_ch_observable[JSO_dut_id_set]=&data->dut.reference_values->i_dq_in_A.d;
	js_ch_observable[JSO_dut_iq_set]=&data->dut.reference_values->i_dq_in_A.q;
	js_ch_observable[JSO_dut_vd_ref]=&data->dut.reference_values->v_dq_in_V.d;
	js_ch_observable[JSO_dut_vq_ref]=&data->dut.reference_values->v_dq_in_V.q;
	js_ch_observable[JSO_dut_v_dc]=&data->dut.actual_data->v_dc_in_V;
	js_ch_observable[JSO_dut_i_dc] = &data->dut.actual_data->i_dc_in_A;
	js_ch_observable[JSO_dut_speed_rpm]=&data->dut.actual_data->speed_in_rpm;
	js_ch_observable[JSO_dut_speed_rpm_ref]=&data->dut.reference_values->speed_in_rpm;
	js_ch_observable[JSO_dut_theta_el]=&data->dut.actual_data->theta_el;
	js_ch_observable[JSO_dut_theta_mech]=&data->dut.measurement_values->theta_mech;
	js_ch_observable[JSO_dut_torque_setpoint_Nm]=&data->dut.reference_values->M_in_Nm;
	js_ch_observable[JSO_pm_ia] = &data->prime_mover.actual_data->i_abc_in_A.a;
	js_ch_observable[JSO_pm_ib] = &data->prime_mover.actual_data->i_abc_in_A.b;
	js_ch_observable[JSO_pm_ic] = &data->prime_mover.actual_data->i_abc_in_A.c;
	js_ch_observable[JSO_pm_id] = &data->prime_mover.actual_data->i_dq_in_A.d;
	js_ch_observable[JSO_pm_iq] = &data->prime_mover.actual_data->i_dq_in_A.q;
	js_ch_observable[JSO_pm_id_set] = &data->prime_mover.reference_values->i_dq_in_A.d;
	js_ch_observable[JSO_pm_iq_set] = &data->prime_mover.reference_values->i_dq_in_A.q;
	js_ch_observable[JSO_pm_vd_ref] = &data->prime_mover.reference_values->v_dq_in_V.d;
	js_ch_observable[JSO_pm_vq_ref] = &data->prime_mover.reference_values->v_dq_in_V.q;
	js_ch_observable[JSO_pm_v_dc] = &data->prime_mover.actual_data->v_dc_in_V;
	js_ch_observable[JSO_pm_i_dc] = &data->prime_mover.actual_data->i_dc_in_A;
	js_ch_observable[JSO_pm_speed_rpm] = &data->prime_mover.actual_data->speed_in_rpm;
	js_ch_observable[JSO_pm_speed_rpm_ref] = &data->prime_mover.reference_values->speed_in_rpm;
	js_ch_observable[JSO_pm_theta_el] = &data->prime_mover.actual_data->theta_el;
	js_ch_observable[JSO_pm_theta_mech] = &data->prime_mover.measurement_values->theta_mech;
	js_ch_observable[JSO_pm_torque_setpoint_Nm] = &data->prime_mover.reference_values->M_in_Nm;
	js_ch_observable[JSO_enable]=&data->javascope.start_marker;
	js_ch_observable[JSO_ddpg_obs_1]=&observation_ip[0];
	js_ch_observable[JSO_ddpg_obs_2]=&observation_ip[1];
	js_ch_observable[JSO_ddpg_obs_3]=&observation_ip[2];
	js_ch_observable[JSO_ddpg_obs_4]=&observation_ip[3];
	js_ch_observable[JSO_ddpg_obs_5]=&observation_ip[4];
	js_ch_observable[JSO_ddpg_obs_6]=&observation_ip[5];
	js_ch_observable[JSO_ddpg_obs_7]=&observation_ip[6];
	js_ch_observable[JSO_ddpg_obs_8]=&observation_ip[7];
	js_ch_observable[JSO_ddpg_obs_9]=&observation_ip[8];
	js_ch_observable[JSO_torque_measured_Nm]=&data->M_meas_Nm;
	js_ch_observable[JSO_pm_speed_filtered]=&data->av.mechanicalRotorSpeed_filtered_prime_mover;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
//	js_slowDataArray[JSSD_FLOAT_u_d_1] 			        = &(data->av.U_d_1);
//	js_slowDataArray[JSSD_FLOAT_u_q_1] 			        = &(data->av.U_q_1);
//	js_slowDataArray[JSSD_FLOAT_i_d_1] 			        = &i_dq_Amps_hoerner.d;
//	js_slowDataArray[JSSD_FLOAT_i_d_2] 			        = &i_dq_Amps_beckhoff.d;
//	js_slowDataArray[JSSD_FLOAT_i_q_1] 			        = &i_dq_Amps_hoerner.q;
//	js_slowDataArray[JSSD_FLOAT_i_q_2] 			        = &i_dq_Amps_beckhoff.q;
	js_slowDataArray[JSSD_FLOAT_speed_1] 		        = &(data->av.d5_1_omega_mech_rad_per_sec);
//	js_slowDataArray[JSSD_FLOAT_speed_2] 		        = &(data->av.mechanicalRotorSpeed_beckhoff);
//	js_slowDataArray[JSSD_FLOAT_torque] 		        = &(data->av.mechanicalTorqueObserved);
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
