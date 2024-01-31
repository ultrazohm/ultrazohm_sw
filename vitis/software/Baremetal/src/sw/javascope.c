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

//Data of PMSM 1
extern float n_ref_rpm_1;
extern float theta_el_rad_1;
extern float theta_el_offset_1;
extern struct uz_3ph_dq_t i_dq_ref_Amps_1;
extern struct uz_3ph_dq_t i_dq_Amps_1;
extern struct uz_3ph_abc_t i_abc_Amps_1;
extern struct uz_3ph_dq_t v_dq_Volts_1;
extern struct uz_3ph_dq_t v_dq_ref_Volts_1;
extern struct uz_3ph_abc_t v_abc_Volts_1;


//Data of PMSM 2
extern float n_ref_rpm_2;
extern float theta_el_rad_2;
extern float theta_el_offset_2;
extern struct uz_3ph_dq_t i_dq_ref_Amps_2;
extern struct uz_3ph_dq_t i_dq_Amps_2;
extern struct uz_3ph_abc_t i_abc_Amps_2;
extern struct uz_3ph_dq_t v_dq_ref_Volts_2;
extern struct uz_3ph_abc_t v_abc_Volts_2;
extern struct uz_3ph_dq_t v_ind_dq_Volts_2;
extern struct uz_3ph_dq_t v_ind_dq_filt_Volts_2;
extern struct uz_3ph_dq_t v_dq_Volts_2;
extern struct uz_3ph_dq_t psi_dq_mVoltseconds_2;
extern struct uz_3ph_dq_t rc_dq_Ohm;
extern struct uz_3ph_dq_t rc_para_dq;



//Others
extern float M_meas_Nm;
extern float option_js;
extern float error_type;
extern float r_s_2;
extern struct uz_pmsmModel_outputs_t pmsm_outputs;
extern struct uz_pmsmModel_inputs_t pmsm_inputs;
extern float omega_el_rad_per_sec;

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
	js_ch_observable[JSO_Speed_rpm_filtered_1] = &data->av.mechanicalRotorSpeed_filtered_1;
	js_ch_observable[JSO_Speed_rpm_filtered_2] = &data->av.mechanicalRotorSpeed_filtered_2;
	js_ch_observable[JSO_Speed_rpm_filtered_3] = &data->av.mechanicalRotorSpeed_filtered_3;
	js_ch_observable[JSO_Speed_rpm_1] 	= &data->av.mechanicalRotorSpeed_1;
	js_ch_observable[JSO_Speed_rpm_2] 	= &data->av.mechanicalRotorSpeed_2;
	js_ch_observable[JSO_Speed_rpm_3] 	= &data->av.mechanicalRotorSpeed_3;
	js_ch_observable[JSO_el_Speed_rpm_1]	= &data->av.electricalRotorSpeed_1;
	js_ch_observable[JSO_el_Speed_rpm_2]	= &data->av.electricalRotorSpeed_2;
	js_ch_observable[JSO_el_Speed_rpm_3]	= &data->av.electricalRotorSpeed_3;
	js_ch_observable[JSO_ia_1] 			= &i_abc_Amps_1.a;
	js_ch_observable[JSO_ib_1] 			= &i_abc_Amps_1.b;
	js_ch_observable[JSO_ic_1] 			= &i_abc_Amps_1.c;
	js_ch_observable[JSO_ia_2] 			= &i_abc_Amps_2.a;
	js_ch_observable[JSO_ib_2] 			= &i_abc_Amps_2.b;
	js_ch_observable[JSO_ic_2] 			= &i_abc_Amps_2.c;
	js_ch_observable[JSO_ua_1] 			= &v_abc_Volts_1.a;
	js_ch_observable[JSO_ub_1] 			= &v_abc_Volts_1.b;
	js_ch_observable[JSO_uc_1] 			= &v_abc_Volts_1.c;
	js_ch_observable[JSO_ua_2] 			= &v_abc_Volts_2.a;
	js_ch_observable[JSO_ub_2] 			= &v_abc_Volts_2.b;
	js_ch_observable[JSO_uc_2] 			= &v_abc_Volts_2.c;
	js_ch_observable[JSO_iq_1] 			= &i_dq_Amps_1.q;
	js_ch_observable[JSO_id_1] 			= &i_dq_Amps_1.d;
	js_ch_observable[JSO_iq_2] 			= &i_dq_Amps_2.q;
	js_ch_observable[JSO_id_2] 			= &i_dq_Amps_2.d;
	js_ch_observable[JSO_uq_ref_1]		= &v_dq_ref_Volts_1.q;
	js_ch_observable[JSO_ud_ref_1]		= &v_dq_ref_Volts_1.d;
	js_ch_observable[JSO_uq_ref_2]		= &v_dq_ref_Volts_2.q;
	js_ch_observable[JSO_ud_ref_2]		= &v_dq_ref_Volts_2.d;
	js_ch_observable[JSO_iq_ref_1] 		= &i_dq_ref_Amps_1.q;
	js_ch_observable[JSO_id_ref_1] 		= &i_dq_ref_Amps_1.d;
	js_ch_observable[JSO_iq_ref_2] 		= &i_dq_ref_Amps_2.q;
	js_ch_observable[JSO_id_ref_2] 		= &i_dq_ref_Amps_2.d;
	js_ch_observable[JSO_n_ref_1]		= &n_ref_rpm_1;
	js_ch_observable[JSO_n_ref_2]		= &n_ref_rpm_2;
	js_ch_observable[JSO_M_meas]		= &M_meas_Nm;
	js_ch_observable[JSO_Theta_el_1] 	= &data->av.theta_elec_1;
	js_ch_observable[JSO_Theta_el_2] 	= &data->av.theta_elec_2;
	js_ch_observable[JSO_Theta_el_3] 	= &data->av.theta_elec_3;
	js_ch_observable[JSO_Theta_el_cor_1]= &theta_el_rad_1;
	js_ch_observable[JSO_Theta_el_cor_2]= &theta_el_rad_2;
	js_ch_observable[JSO_Theta_el_off_1]= &data->av.theta_offset_1;
	js_ch_observable[JSO_Theta_el_off_2]= &data->av.theta_offset_2;
	js_ch_observable[JSO_Theta_mech_1] 	= &data->av.theta_mech_1;
	js_ch_observable[JSO_ud_1]			= &v_dq_Volts_1.d;
	js_ch_observable[JSO_uq_1]			= &v_dq_Volts_1.q;
	js_ch_observable[JSO_ud_2]			= &v_dq_Volts_2.d;
	js_ch_observable[JSO_uq_2]			= &v_dq_Volts_2.q;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;
	js_ch_observable[JSO_ud_ind_2]			= &v_ind_dq_Volts_2.d;
	js_ch_observable[JSO_uq_ind_2]			= &v_ind_dq_Volts_2.q;
	js_ch_observable[JSO_ud_ind_filt_2]			= &v_ind_dq_filt_Volts_2.d;
	js_ch_observable[JSO_uq_ind_filt_2]			= &v_ind_dq_filt_Volts_2.q;
	js_ch_observable[JSO_error_type]			= &error_type;
	js_ch_observable[JSO_psi_d_2]			= &psi_dq_mVoltseconds_2.d;
	js_ch_observable[JSO_psi_q_2]			= &psi_dq_mVoltseconds_2.q;
	js_ch_observable[JSO_i_q] 			= &pmsm_outputs.i_q_A;
	js_ch_observable[JSO_i_d] 			= &pmsm_outputs.i_d_A;
	js_ch_observable[JSO_omega]			 = &pmsm_outputs.omega_mech_1_s;
	js_ch_observable[JSO_v_d]			 = &pmsm_inputs.v_d_V;
	js_ch_observable[JSO_v_q]			 = &pmsm_inputs.v_q_V;
	js_ch_observable[JSO_rc_d]			 = &rc_dq_Ohm.d;
	js_ch_observable[JSO_rc_q]			 = &rc_dq_Ohm.q;
	js_ch_observable[JSO_rc_para_d]			 = &rc_para_dq.d;
	js_ch_observable[JSO_rc_para_q]			 = &rc_para_dq.q;



	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_u_d_1] 			        = &(data->av.U_d_1);
	js_slowDataArray[JSSD_FLOAT_u_q_1] 			        = &(data->av.U_q_1);
	js_slowDataArray[JSSD_FLOAT_i_d_1] 			        = &i_dq_Amps_1.d;
	js_slowDataArray[JSSD_FLOAT_i_q_1] 			        = &i_dq_Amps_1.q;
	js_slowDataArray[JSSD_FLOAT_i_d_2] 			        = &i_dq_Amps_2.d;
	js_slowDataArray[JSSD_FLOAT_i_q_2] 			        = &i_dq_Amps_2.q;
	js_slowDataArray[JSSD_FLOAT_speed_1] 		        = &(data->av.mechanicalRotorSpeed_1);
	js_slowDataArray[JSSD_FLOAT_torque] 		        = &(data->av.mechanicalTorqueObserved);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_u_ind_d]   				= &v_ind_dq_Volts_2.d;
	js_slowDataArray[JSSD_FLOAT_u_ind_q]   				= &v_ind_dq_Volts_2.q;
	js_slowDataArray[JSSD_FLOAT_u_ind_filt_d]   		= &v_ind_dq_filt_Volts_2.d;
	js_slowDataArray[JSSD_FLOAT_u_ind_filt_q]   		= &v_ind_dq_filt_Volts_2.q;
	js_slowDataArray[JSSD_FLOAT_psi_d]   				= &psi_dq_mVoltseconds_2.d;
	js_slowDataArray[JSSD_FLOAT_psi_q]   				= &psi_dq_mVoltseconds_2.q;
	js_slowDataArray[JSSD_FLOAT_theta_el_offset_2]   	= &data->av.theta_offset_2;
	js_slowDataArray[JSSD_FLOAT_ia2_av]   				= &data->aa.A2.me.ADC_A4;
	js_slowDataArray[JSSD_FLOAT_ib2_av]  			 	= &data->aa.A2.me.ADC_A3;
	js_slowDataArray[JSSD_FLOAT_ic2_av]  			 	= &data->aa.A2.me.ADC_A2;
	js_slowDataArray[JSSD_FLOAT_ua2_av]   				= &data->aa.A2.me.ADC_B8;
	js_slowDataArray[JSSD_FLOAT_ub2_av]  			 	= &data->aa.A2.me.ADC_B7;
	js_slowDataArray[JSSD_FLOAT_uc2_av]  			 	= &data->aa.A2.me.ADC_B6;
	js_slowDataArray[JSSD_FLOAT_ia1_av]   				= &data->aa.A1.me.ADC_A4;
	js_slowDataArray[JSSD_FLOAT_ib1_av]  			 	= &data->aa.A1.me.ADC_A3;
	js_slowDataArray[JSSD_FLOAT_ic1_av]  			 	= &data->aa.A1.me.ADC_A2;
	js_slowDataArray[JSSD_FLOAT_ua1_av]   				= &data->aa.A1.me.ADC_B8;
	js_slowDataArray[JSSD_FLOAT_ub1_av]  			 	= &data->aa.A1.me.ADC_B7;
	js_slowDataArray[JSSD_FLOAT_uc1_av]  			 	= &data->aa.A1.me.ADC_B6;
	js_slowDataArray[JSSD_FLOAT_rs2]  			 		= &r_s_2;
	js_slowDataArray[JSSD_FLOAT_u_d]                    = &(pmsm_inputs.v_d_V);
	js_slowDataArray[JSSD_FLOAT_u_q]                    = &(pmsm_inputs.v_q_V);
	js_slowDataArray[JSSD_FLOAT_i_d]                    = &(pmsm_outputs.i_d_A);
	js_slowDataArray[JSSD_FLOAT_i_q]                    = &(pmsm_outputs.i_q_A);
	js_slowDataArray[JSSD_FLOAT_speed]                  = &(pmsm_outputs.omega_mech_1_s);
	js_slowDataArray[JSSD_FLOAT_rc_d]			 		= &rc_dq_Ohm.d;
	js_slowDataArray[JSSD_FLOAT_rc_q]					= &rc_dq_Ohm.q;
	js_slowDataArray[JSSD_FLOAT_rc_para_d]			 	= &rc_para_dq.d;
	js_slowDataArray[JSSD_FLOAT_rc_para_q]				= &rc_para_dq.q;

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
