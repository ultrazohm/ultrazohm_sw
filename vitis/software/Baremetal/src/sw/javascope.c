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
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"

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

extern float d1_added_noise;
extern float d2_added_noise;
extern struct uz_pmsmModel_outputs_t cil_outputs;
extern struct uz_pmsmModel_inputs_t cil_inputs;

extern struct uz_pmsm_measurement_values d1_measurements;
extern struct uz_pmsm_measurement_values d2_measurements;

int JavaScope_initialize(DS_Data *data)
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
	js_ch_observable[JSO_cil_out_id] = &cil_outputs.i_d_A;
	js_ch_observable[JSO_cil_out_iq] = &cil_outputs.i_q_A;
	js_ch_observable[JSO_cil_out_omega_el] = &cil_outputs.omega_el_1_s;
	js_ch_observable[JSO_cil_out_omega_mech] = &cil_outputs.omega_mech_1_s;
	js_ch_observable[JSO_cil_out_torque] = &cil_outputs.torque_Nm;
	js_ch_observable[JSO_cil_in_load_torque] = &cil_inputs.load_torque;
	js_ch_observable[JSO_cil_in_omega_mech_1_s] = &cil_inputs.omega_mech_1_s;
	js_ch_observable[JSO_cil_in_v_d_V] = &cil_inputs.v_d_V;
	js_ch_observable[JSO_cil_in_v_q_V] = &cil_inputs.v_q_V;
	js_ch_observable[JSO_dut_ia_raw] = &data->dut.measurement_values->phase_currents_from_adc_ampere_per_volt.a;
	js_ch_observable[JSO_dut_ib_raw] = &data->dut.measurement_values->phase_currents_from_adc_ampere_per_volt.b;
	js_ch_observable[JSO_dut_ic_raw] = &data->dut.measurement_values->phase_currents_from_adc_ampere_per_volt.c;
	js_ch_observable[JSO_dut_ia]=&data->dut.actual_data->i_abc_in_A.a;
	js_ch_observable[JSO_dut_ib]=&data->dut.actual_data->i_abc_in_A.b;
	js_ch_observable[JSO_dut_ic]=&data->dut.actual_data->i_abc_in_A.c;
	js_ch_observable[JSO_dut_id]=&data->dut.actual_data->i_dq_in_A.d;
	js_ch_observable[JSO_dut_iq]=&data->dut.actual_data->i_dq_in_A.q;
	js_ch_observable[JSO_dut_vd] = &data->dut.actual_data->v_dq_in_V.d;
	js_ch_observable[JSO_dut_vq] = &data->dut.actual_data->v_dq_in_V.q;
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
	js_ch_observable[JSO_debug_speed_d5_1_filtered] = &data->av.d5_1_n_rpm_filtered;
	js_ch_observable[JSO_debug_speed_d5_1] = &data->av.d5_1_n_rpm;
	js_ch_observable[JSO_torque_added_d1] = &d1_added_noise;
	js_ch_observable[JSO_torque_added_d2] = &d2_added_noise;
	js_ch_observable[JSO_dut_theta_offset] = data->dut_theta_offset;
	js_ch_observable[JSO_input] = &data->javascope.input;
	js_ch_observable[JSO_d1_phase_voltage_a] = &d1_measurements.phase_voltage_from_adc_voltage_per_volt.a;
	js_ch_observable[JSO_d1_phase_voltage_b] = &d1_measurements.phase_voltage_from_adc_voltage_per_volt.b;
	js_ch_observable[JSO_d1_phase_voltage_c] = &d1_measurements.phase_voltage_from_adc_voltage_per_volt.c;
	js_ch_observable[JSO_d2_phase_voltage_a] = &d2_measurements.phase_voltage_from_adc_voltage_per_volt.a;
	js_ch_observable[JSO_d2_phase_voltage_b] = &d2_measurements.phase_voltage_from_adc_voltage_per_volt.b;
	js_ch_observable[JSO_d2_phase_voltage_c] = &d2_measurements.phase_voltage_from_adc_voltage_per_volt.c;
	js_ch_observable[JSO_d1_phase_current_a] = &d1_measurements.phase_currents_from_adc_ampere_per_volt.a;
	js_ch_observable[JSO_d1_phase_current_b] = &d1_measurements.phase_currents_from_adc_ampere_per_volt.b;
	js_ch_observable[JSO_d1_phase_current_c] = &d1_measurements.phase_currents_from_adc_ampere_per_volt.c;
	js_ch_observable[JSO_d2_phase_current_a] = &d2_measurements.phase_currents_from_adc_ampere_per_volt.a;
	js_ch_observable[JSO_d2_phase_current_b] = &d2_measurements.phase_currents_from_adc_ampere_per_volt.b;
	js_ch_observable[JSO_d2_phase_current_c] = &d2_measurements.phase_currents_from_adc_ampere_per_volt.c;
	js_ch_observable[JSO_duty_1] = &data->rasv.halfBridge1DutyCycle;
	js_ch_observable[JSO_duty_2] = &data->rasv.halfBridge2DutyCycle;
	js_ch_observable[JSO_duty_3] = &data->rasv.halfBridge3DutyCycle;
	js_ch_observable[JSO_duty_4] = &data->rasv.halfBridge4DutyCycle;
	js_ch_observable[JSO_duty_5] = &data->rasv.halfBridge5DutyCycle;
	js_ch_observable[JSO_duty_6] = &data->rasv.halfBridge6DutyCycle;
	js_ch_observable[JSO_dut_v_a_ref] = &data->dut.reference_values->v_abc_in_V.a;
	js_ch_observable[JSO_dut_v_b_ref] = &data->dut.reference_values->v_abc_in_V.b;
	js_ch_observable[JSO_dut_v_c_ref] = &data->dut.reference_values->v_abc_in_V.c;
	js_ch_observable[JSO_pm_v_a_ref] = &data->prime_mover.reference_values->v_abc_in_V.a;
	js_ch_observable[JSO_pm_v_b_ref] = &data->prime_mover.reference_values->v_abc_in_V.b;
	js_ch_observable[JSO_pm_v_c_ref] = &data->prime_mover.reference_values->v_abc_in_V.c;
	js_ch_observable[JSO_dut_v_a] = &data->dut.actual_data->v_abc_in_V.a;
	js_ch_observable[JSO_dut_v_b] = &data->dut.actual_data->v_abc_in_V.b;
	js_ch_observable[JSO_dut_v_c] = &data->dut.actual_data->v_abc_in_V.c;
	js_ch_observable[JSO_pm_v_a] = &data->prime_mover.actual_data->v_abc_in_V.a;
	js_ch_observable[JSO_pm_v_b] = &data->prime_mover.actual_data->v_abc_in_V.b;
	js_ch_observable[JSO_pm_v_c] = &data->prime_mover.actual_data->v_abc_in_V.c;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_d1_h1_tmp] = &data->av.inverter_outputs_d1.ChipTempDegreesCelsius_H1;
	js_slowDataArray[JSSD_FLOAT_d1_h2_tmp] = &data->av.inverter_outputs_d1.ChipTempDegreesCelsius_H2;
	js_slowDataArray[JSSD_FLOAT_d1_h3_tmp] = &data->av.inverter_outputs_d1.ChipTempDegreesCelsius_H3;
	js_slowDataArray[JSSD_FLOAT_d1_l1_tmp] = &data->av.inverter_outputs_d1.ChipTempDegreesCelsius_L1;
	js_slowDataArray[JSSD_FLOAT_d1_l2_tmp] = &data->av.inverter_outputs_d1.ChipTempDegreesCelsius_L2;
	js_slowDataArray[JSSD_FLOAT_d1_l3_tmp] = &data->av.inverter_outputs_d1.ChipTempDegreesCelsius_L3;
	js_slowDataArray[JSSD_FLOAT_d2_h1_tmp] = &data->av.inverter_outputs_d2.ChipTempDegreesCelsius_H1;
	js_slowDataArray[JSSD_FLOAT_d2_h2_tmp] = &data->av.inverter_outputs_d2.ChipTempDegreesCelsius_H2;
	js_slowDataArray[JSSD_FLOAT_d2_h3_tmp] = &data->av.inverter_outputs_d2.ChipTempDegreesCelsius_H3;
	js_slowDataArray[JSSD_FLOAT_d2_l1_tmp] = &data->av.inverter_outputs_d2.ChipTempDegreesCelsius_L1;
	js_slowDataArray[JSSD_FLOAT_d2_l2_tmp] = &data->av.inverter_outputs_d2.ChipTempDegreesCelsius_L2;
	js_slowDataArray[JSSD_FLOAT_d2_l3_tmp] = &data->av.inverter_outputs_d2.ChipTempDegreesCelsius_L3;
	js_slowDataArray[JSSD_FLOAT_dut_ia] = &data->dut.actual_data->i_abc_in_A.a;
	js_slowDataArray[JSSD_FLOAT_dut_ib] = &data->dut.actual_data->i_abc_in_A.b;
	js_slowDataArray[JSSD_FLOAT_dut_ic] = &data->dut.actual_data->i_abc_in_A.c;
	js_slowDataArray[JSSD_FLOAT_dut_id] = &data->dut.actual_data->i_dq_in_A.d;
	js_slowDataArray[JSSD_FLOAT_dut_iq] = &data->dut.actual_data->i_dq_in_A.q;
	js_slowDataArray[JSSD_FLOAT_dut_id_set] = &data->dut.reference_values->i_dq_in_A.d;
	js_slowDataArray[JSSD_FLOAT_dut_iq_set] = &data->dut.reference_values->i_dq_in_A.q;
	js_slowDataArray[JSSD_FLOAT_dut_vd_ref] = &data->dut.reference_values->v_dq_in_V.d;
	js_slowDataArray[JSSD_FLOAT_dut_vq_ref] = &data->dut.reference_values->v_dq_in_V.q;
	js_slowDataArray[JSSD_FLOAT_dut_v_dc] = &data->dut.actual_data->v_dc_in_V;
	js_slowDataArray[JSSD_FLOAT_dut_i_dc] = &data->dut.actual_data->i_dc_in_A;
	js_slowDataArray[JSSD_FLOAT_dut_speed_rpm] = &data->dut.actual_data->speed_in_rpm;
	js_slowDataArray[JSSD_FLOAT_dut_speed_rpm_ref] = &data->dut.reference_values->speed_in_rpm;
	js_slowDataArray[JSSD_FLOAT_dut_theta_el] = &data->dut.actual_data->theta_el;
	js_slowDataArray[JSSD_FLOAT_dut_theta_mech] = &data->dut.measurement_values->theta_mech;
	js_slowDataArray[JSSD_FLOAT_dut_torque_setpoint_Nm] = &data->dut.reference_values->M_in_Nm;
	js_slowDataArray[JSSD_FLOAT_pm_ia] = &data->prime_mover.actual_data->i_abc_in_A.a;
	js_slowDataArray[JSSD_FLOAT_pm_ib] = &data->prime_mover.actual_data->i_abc_in_A.b;
	js_slowDataArray[JSSD_FLOAT_pm_ic] = &data->prime_mover.actual_data->i_abc_in_A.c;
	js_slowDataArray[JSSD_FLOAT_pm_id] = &data->prime_mover.actual_data->i_dq_in_A.d;
	js_slowDataArray[JSSD_FLOAT_pm_iq] = &data->prime_mover.actual_data->i_dq_in_A.q;
	js_slowDataArray[JSSD_FLOAT_pm_id_set] = &data->prime_mover.reference_values->i_dq_in_A.d;
	js_slowDataArray[JSSD_FLOAT_pm_iq_set] = &data->prime_mover.reference_values->i_dq_in_A.q;
	js_slowDataArray[JSSD_FLOAT_pm_vd_ref] = &data->prime_mover.reference_values->v_dq_in_V.d;
	js_slowDataArray[JSSD_FLOAT_pm_vq_ref] = &data->prime_mover.reference_values->v_dq_in_V.q;
	js_slowDataArray[JSSD_FLOAT_pm_v_dc] = &data->prime_mover.actual_data->v_dc_in_V;
	js_slowDataArray[JSSD_FLOAT_pm_i_dc] = &data->prime_mover.actual_data->i_dc_in_A;
	js_slowDataArray[JSSD_FLOAT_pm_speed_rpm] = &data->prime_mover.actual_data->speed_in_rpm;
	js_slowDataArray[JSSD_FLOAT_pm_speed_rpm_ref] = &data->prime_mover.reference_values->speed_in_rpm;
	js_slowDataArray[JSSD_FLOAT_pm_theta_el] = &data->prime_mover.actual_data->theta_el;
	js_slowDataArray[JSSD_FLOAT_pm_theta_mech] = &data->prime_mover.measurement_values->theta_mech;
	js_slowDataArray[JSSD_FLOAT_pm_torque_setpoint_Nm] = &data->prime_mover.reference_values->M_in_Nm;
//	js_slowDataArray[JSSD_FLOAT_FLOAT_speed_1] 		        = &(data->av.d5_1_omega_mech_rad_per_sec);
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
