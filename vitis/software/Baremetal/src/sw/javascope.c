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

// maximum number of while loops in the polling function for the acknowledge flag
#define POLL_FOR_ACK_TIMEOUT_COUNT	1000
// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)
uint32_t cache_size_to_flush = 0U;
//Variables for JavaScope
static float zerovalue = 0.0;
static const float *js_slowDataArray[JSSD_ENDMARKER];
const float *js_ch_observable[JSO_ENDMARKER];
const float *js_ch_selected[JS_CHANNELS];

static float lifecheck;
static float ISR_execution_time_us;
static float ISR_period_us;
static float System_UpTime_seconds;
static float System_UpTime_ms;

uint32_t pollErrorCnt = 0U;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

//Initialize the Interrupt structure
extern XIpiPsu IPI_instance;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!


struct JavaScope_pmsm_control_observable_ids {
	enum JS_OberservableData actual_i_d;
	enum JS_OberservableData actual_i_q;
	enum JS_OberservableData actual_i_zero;
	enum JS_OberservableData actual_v_d;
	enum JS_OberservableData actual_v_q;
	enum JS_OberservableData actual_v_zero;
	enum JS_OberservableData actual_omega_el_rad_s;
	enum JS_OberservableData actual_speed_rpm;
	enum JS_OberservableData actual_theta_el;
	enum JS_OberservableData actual_theta_el_advanced;
	enum JS_OberservableData theta_offset;
	enum JS_OberservableData ref_speed_rpm;
	enum JS_OberservableData ref_torque_Nm;
	enum JS_OberservableData ref_i_d;
	enum JS_OberservableData ref_i_q;
	enum JS_OberservableData ref_i_zero;
	enum JS_OberservableData ref_v_d;
	enum JS_OberservableData ref_v_q;
	enum JS_OberservableData ref_v_zero;
	enum JS_OberservableData ref_v_a;
	enum JS_OberservableData ref_v_b;
	enum JS_OberservableData ref_v_c;
	enum JS_OberservableData ref_duty_a;
	enum JS_OberservableData ref_duty_b;
	enum JS_OberservableData ref_duty_c;
	enum JS_OberservableData meas_i_a;
	enum JS_OberservableData meas_i_b;
	enum JS_OberservableData meas_i_c;
	enum JS_OberservableData meas_v_a;
	enum JS_OberservableData meas_v_b;
	enum JS_OberservableData meas_v_c;
	enum JS_OberservableData meas_v_dc;
	enum JS_OberservableData meas_i_dc;
	enum JS_OberservableData meas_omega_mech_rad_s;
	enum JS_OberservableData meas_theta_mech;
};

static void JavaScope_register_pmsm_control_observables(uz_pmsm_control_t *controller, const struct JavaScope_pmsm_control_observable_ids *ids)
{
	if (controller == NULL) {
		return;
	}

	const struct uz_pmsm_actual_data *actual = uz_pmsm_control_get_actual_data(controller);
	const struct uz_pmsm_reference_values *reference = uz_pmsm_control_get_reference_values(controller);
	const struct uz_pmsm_measurement_values *measurement = uz_pmsm_control_get_pmsm_measurement_values(controller);

	js_ch_observable[ids->actual_i_d] = &actual->i_dq_in_A.d;
	js_ch_observable[ids->actual_i_q] = &actual->i_dq_in_A.q;
	js_ch_observable[ids->actual_i_zero] = &actual->i_dq_in_A.zero;
	js_ch_observable[ids->actual_v_d] = &actual->v_dq_in_V.d;
	js_ch_observable[ids->actual_v_q] = &actual->v_dq_in_V.q;
	js_ch_observable[ids->actual_v_zero] = &actual->v_dq_in_V.zero;
	js_ch_observable[ids->actual_omega_el_rad_s] = &actual->omega_el_rad_per_sec;
	js_ch_observable[ids->actual_speed_rpm] = &actual->speed_in_rpm;
	js_ch_observable[ids->actual_theta_el] = &actual->theta_el;
	js_ch_observable[ids->actual_theta_el_advanced] = &actual->theta_el_advanced;
	js_ch_observable[ids->theta_offset] = uz_pmsm_control_get_pointer_to_theta_offset(controller);

	js_ch_observable[ids->ref_speed_rpm] = &reference->speed_in_rpm;
	js_ch_observable[ids->ref_torque_Nm] = &reference->M_in_Nm;
	js_ch_observable[ids->ref_i_d] = &reference->i_dq_in_A.d;
	js_ch_observable[ids->ref_i_q] = &reference->i_dq_in_A.q;
	js_ch_observable[ids->ref_i_zero] = &reference->i_dq_in_A.zero;
	js_ch_observable[ids->ref_v_d] = &reference->v_dq_in_V.d;
	js_ch_observable[ids->ref_v_q] = &reference->v_dq_in_V.q;
	js_ch_observable[ids->ref_v_zero] = &reference->v_dq_in_V.zero;
	js_ch_observable[ids->ref_v_a] = &reference->v_abc_in_V.a;
	js_ch_observable[ids->ref_v_b] = &reference->v_abc_in_V.b;
	js_ch_observable[ids->ref_v_c] = &reference->v_abc_in_V.c;
	js_ch_observable[ids->ref_duty_a] = &reference->duty_cycle.DutyCycle_A;
	js_ch_observable[ids->ref_duty_b] = &reference->duty_cycle.DutyCycle_B;
	js_ch_observable[ids->ref_duty_c] = &reference->duty_cycle.DutyCycle_C;

	js_ch_observable[ids->meas_i_a] = &measurement->i_abc_in_A.a;
	js_ch_observable[ids->meas_i_b] = &measurement->i_abc_in_A.b;
	js_ch_observable[ids->meas_i_c] = &measurement->i_abc_in_A.c;
	js_ch_observable[ids->meas_v_a] = &measurement->v_abc_in_V.a;
	js_ch_observable[ids->meas_v_b] = &measurement->v_abc_in_V.b;
	js_ch_observable[ids->meas_v_c] = &measurement->v_abc_in_V.c;
	js_ch_observable[ids->meas_v_dc] = &measurement->v_dc_in_V;
	js_ch_observable[ids->meas_i_dc] = &measurement->i_dc_in_A;
	js_ch_observable[ids->meas_omega_mech_rad_s] = &measurement->omega_mech_rad_per_sec;
	js_ch_observable[ids->meas_theta_mech] = &measurement->theta_mech;
}

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
	js_ch_observable[JSO_Speed_rpm]				= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_el_Speed_rpm]			= &data->av.electricalRotorSpeed;
	js_ch_observable[JSO_ia] 					= &data->av.I_U;
	js_ch_observable[JSO_ib] 					= &data->av.I_V;
	js_ch_observable[JSO_ic] 					= &data->av.I_W;
	js_ch_observable[JSO_ua] 					= &data->av.U_U;
	js_ch_observable[JSO_ub] 					= &data->av.U_V;
	js_ch_observable[JSO_uc] 					= &data->av.U_W;
	js_ch_observable[JSO_iq] 					= &data->av.I_q;
	js_ch_observable[JSO_id] 					= &data->av.I_d;
	js_ch_observable[JSO_Theta_el] 				= &data->av.theta_elec;
	js_ch_observable[JSO_theta_mech] 			= &data->av.theta_mech;
	js_ch_observable[JSO_ud]					= &data->av.U_d;
	js_ch_observable[JSO_uq]					= &data->av.U_q;
	js_ch_observable[JSO_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   			= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]			= &ISR_period_us;


	static const struct JavaScope_pmsm_control_observable_ids swmodel_control_ids = {
		JSO_PMSM_SW_ACTUAL_I_D,
		JSO_PMSM_SW_ACTUAL_I_Q,
		JSO_PMSM_SW_ACTUAL_I_ZERO,
		JSO_PMSM_SW_ACTUAL_V_D,
		JSO_PMSM_SW_ACTUAL_V_Q,
		JSO_PMSM_SW_ACTUAL_V_ZERO,
		JSO_PMSM_SW_ACTUAL_OMEGA_EL_RAD_S,
		JSO_PMSM_SW_ACTUAL_SPEED_RPM,
		JSO_PMSM_SW_ACTUAL_THETA_EL,
		JSO_PMSM_SW_ACTUAL_THETA_EL_ADVANCED,
		JSO_PMSM_SW_THETA_OFFSET,
		JSO_PMSM_SW_REF_SPEED_RPM,
		JSO_PMSM_SW_REF_TORQUE_NM,
		JSO_PMSM_SW_REF_I_D,
		JSO_PMSM_SW_REF_I_Q,
		JSO_PMSM_SW_REF_I_ZERO,
		JSO_PMSM_SW_REF_V_D,
		JSO_PMSM_SW_REF_V_Q,
		JSO_PMSM_SW_REF_V_ZERO,
		JSO_PMSM_SW_REF_V_A,
		JSO_PMSM_SW_REF_V_B,
		JSO_PMSM_SW_REF_V_C,
		JSO_PMSM_SW_REF_DUTY_A,
		JSO_PMSM_SW_REF_DUTY_B,
		JSO_PMSM_SW_REF_DUTY_C,
		JSO_PMSM_SW_MEAS_I_A,
		JSO_PMSM_SW_MEAS_I_B,
		JSO_PMSM_SW_MEAS_I_C,
		JSO_PMSM_SW_MEAS_V_A,
		JSO_PMSM_SW_MEAS_V_B,
		JSO_PMSM_SW_MEAS_V_C,
		JSO_PMSM_SW_MEAS_V_DC,
		JSO_PMSM_SW_MEAS_I_DC,
		JSO_PMSM_SW_MEAS_OMEGA_MECH_RAD_S,
		JSO_PMSM_SW_MEAS_THETA_MECH
	};
	static const struct JavaScope_pmsm_control_observable_ids ipcore_control_ids = {
		JSO_PMSM_IP_ACTUAL_I_D,
		JSO_PMSM_IP_ACTUAL_I_Q,
		JSO_PMSM_IP_ACTUAL_I_ZERO,
		JSO_PMSM_IP_ACTUAL_V_D,
		JSO_PMSM_IP_ACTUAL_V_Q,
		JSO_PMSM_IP_ACTUAL_V_ZERO,
		JSO_PMSM_IP_ACTUAL_OMEGA_EL_RAD_S,
		JSO_PMSM_IP_ACTUAL_SPEED_RPM,
		JSO_PMSM_IP_ACTUAL_THETA_EL,
		JSO_PMSM_IP_ACTUAL_THETA_EL_ADVANCED,
		JSO_PMSM_IP_THETA_OFFSET,
		JSO_PMSM_IP_REF_SPEED_RPM,
		JSO_PMSM_IP_REF_TORQUE_NM,
		JSO_PMSM_IP_REF_I_D,
		JSO_PMSM_IP_REF_I_Q,
		JSO_PMSM_IP_REF_I_ZERO,
		JSO_PMSM_IP_REF_V_D,
		JSO_PMSM_IP_REF_V_Q,
		JSO_PMSM_IP_REF_V_ZERO,
		JSO_PMSM_IP_REF_V_A,
		JSO_PMSM_IP_REF_V_B,
		JSO_PMSM_IP_REF_V_C,
		JSO_PMSM_IP_REF_DUTY_A,
		JSO_PMSM_IP_REF_DUTY_B,
		JSO_PMSM_IP_REF_DUTY_C,
		JSO_PMSM_IP_MEAS_I_A,
		JSO_PMSM_IP_MEAS_I_B,
		JSO_PMSM_IP_MEAS_I_C,
		JSO_PMSM_IP_MEAS_V_A,
		JSO_PMSM_IP_MEAS_V_B,
		JSO_PMSM_IP_MEAS_V_C,
		JSO_PMSM_IP_MEAS_V_DC,
		JSO_PMSM_IP_MEAS_I_DC,
		JSO_PMSM_IP_MEAS_OMEGA_MECH_RAD_S,
		JSO_PMSM_IP_MEAS_THETA_MECH
	};

	JavaScope_register_pmsm_control_observables(data->objects.pmsm_control_swmodel, &swmodel_control_ids);
	JavaScope_register_pmsm_control_observables(data->objects.pmsm_control_ipcore, &ipcore_control_ids);

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

	const struct uz_pmsm_actual_data *swmodel_actual = uz_pmsm_control_get_actual_data(data->objects.pmsm_control_swmodel);
	const struct uz_pmsm_actual_data *ipcore_actual = uz_pmsm_control_get_actual_data(data->objects.pmsm_control_ipcore);
	js_slowDataArray[JSSD_FLOAT_pmsm_sw_i_d] = &swmodel_actual->i_dq_in_A.d;
	js_slowDataArray[JSSD_FLOAT_pmsm_sw_i_q] = &swmodel_actual->i_dq_in_A.q;
	js_slowDataArray[JSSD_FLOAT_pmsm_ip_i_d] = &ipcore_actual->i_dq_in_A.d;
	js_slowDataArray[JSSD_FLOAT_pmsm_ip_i_q] = &ipcore_actual->i_dq_in_A.q;
	js_slowDataArray[JSSD_FLOAT_i_q_ref] = &data->av.snd_fld[4];

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
