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
#include "../include/error_checks.h"

// maximum number of while loops in the polling function for the acknowledge flag
#define POLL_FOR_ACK_TIMEOUT_COUNT	1000
// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)
uint32_t cache_size_to_flush = 0U;
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

uint32_t pollErrorCnt = 0U;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;				// Contains (among other things?) the status of the four "UltraZohm LEDs" (cf. ipc_ARM.c):
												//  Bits 3-0: User (3), Error (2), Running (1) and Ready (0)
												//  This is probably it?
												// Is sent to APU (and PC) by means of javascope_data->status in JavaScope_update (below)

//Initialize the Interrupt structure
extern XIpiPsu IPI_instance;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!


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
	js_ch_observable[JSO_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   			= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]			= &ISR_period_us;
	js_ch_observable[JSO_IM_1LA7073_I_A]=&data->av.im_siemens_1LA7073_ia;
	js_ch_observable[JSO_IM_1LA7073_I_B]=&data->av.im_siemens_1LA7073_ib;
	js_ch_observable[JSO_IM_1LA7073_I_C]=&data->av.im_siemens_1LA7073_ic;
	js_ch_observable[JSO_IM_1LA7073_V_DC]=&data->av.im_siemens_1LA7073_vdc;
	js_ch_observable[JSO_IM_1LA7073_SPEED_RPM]=&data->av.im_siemens_1LA7073_speed_rpm;
	js_ch_observable[JSO_IM_1LA7073_FREQUENCY_HZ]=&data->av.im_siemens_1LA7073_uf_data.frequency_command_Hz;
	js_ch_observable[JSO_IM_1LA7073_VOLTAGE_V]=&data->av.im_siemens_1LA7073_uf_data.applied_voltage_magnitude_V;
	js_ch_observable[JSO_IM_1LA7073_I_D]=&data->av.im_siemens_1LA7073_id;
	js_ch_observable[JSO_IM_1LA7073_I_Q]=&data->av.im_siemens_1LA7073_iq;
	js_ch_observable[JSO_IM_1LA7073_I_D_RAW]=&data->av.im_siemens_1LA7073_id_raw;
	js_ch_observable[JSO_IM_1LA7073_I_Q_RAW]=&data->av.im_siemens_1LA7073_iq_raw;
	js_ch_observable[JSO_IM_1LA7073_I_D_REF]=&data->rasv.im_siemens_1LA7073_id_reference_A;
	js_ch_observable[JSO_IM_1LA7073_I_Q_REF]=&data->rasv.im_siemens_1LA7073_iq_reference_A;
	js_ch_observable[JSO_IM_1LA7073_FLUX_VS]=&data->av.im_siemens_1LA7073_flux_magnitude_Vs;
	js_ch_observable[JSO_IM_1LA7073_FLUX_ANGLE_RAD]=&data->av.im_siemens_1LA7073_flux_angle_rad;
	js_ch_observable[JSO_IM_1LA7073_ROTOR_ELECTRICAL_ANGLE_RAD]=&data->av.im_siemens_1LA7073_rotor_electrical_angle_rad;
	js_ch_observable[JSO_IM_1LA7073_FLUX_ROTOR_ANGLE_DIFFERENCE_RAD]=&data->av.im_siemens_1LA7073_flux_rotor_angle_difference_rad;
	js_ch_observable[JSO_IM_1LA7073_ROTOR_ELECTRICAL_FREQUENCY_HZ]=&data->av.im_siemens_1LA7073_rotor_electrical_frequency_Hz;
	js_ch_observable[JSO_IM_1LA7073_SLIP_FREQUENCY_HZ]=&data->av.im_siemens_1LA7073_slip_frequency_Hz;
	js_ch_observable[JSO_IM_1LA7073_SLIP_PERCENT]=&data->av.im_siemens_1LA7073_slip_percent;
	js_ch_observable[JSO_IM_1LA7073_STATOR_FREQUENCY_HZ]=&data->av.im_siemens_1LA7073_stator_frequency_Hz;
	js_ch_observable[JSO_IM_1LA7073_DUTY_A]=&data->rasv.pwm_2L_0_halfBridgeDutyCycle_1;
	js_ch_observable[JSO_IM_1LA7073_DUTY_B]=&data->rasv.pwm_2L_0_halfBridgeDutyCycle_2;
	js_ch_observable[JSO_IM_1LA7073_DUTY_C]=&data->rasv.pwm_2L_0_halfBridgeDutyCycle_3;
	js_ch_observable[JSO_D3_INPUT_LOOPBACK_UINT32] = &data->av.d3_input_loopback_uint32;
	js_ch_observable[JSO_INVERTER_TEMPERATURE_DEG_C] = &data->av.inverter_temperature_degC;
	js_ch_observable[JSO_INVERTER_TEMPERATURE_PWM_DUTY_CYCLE_PERCENT] = &data->av.inverter_temperature_pwm_duty_cycle_percent;
	js_ch_observable[JSO_INVERTER_TEMPERATURE_PWM_FREQUENCY_HZ] = &data->av.inverter_temperature_pwm_frequency_Hz;

	js_ch_selected[0] = js_ch_observable[JSO_IM_1LA7073_I_A];
	js_ch_selected[1] = js_ch_observable[JSO_IM_1LA7073_I_B];
	js_ch_selected[2] = js_ch_observable[JSO_IM_1LA7073_I_C];
	js_ch_selected[17] = js_ch_observable[JSO_IM_1LA7073_SLIP_PERCENT];
	js_ch_selected[18] = js_ch_observable[JSO_INVERTER_TEMPERATURE_PWM_DUTY_CYCLE_PERCENT];
	js_ch_selected[19] = js_ch_observable[JSO_INVERTER_TEMPERATURE_DEG_C];

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_Error_Code] = &js_error_code;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Speed_RPM] = &data->av.im_siemens_1LA7073_speed_rpm;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_V_DC] = &data->av.im_siemens_1LA7073_vdc;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Slip_Percent] = &data->av.im_siemens_1LA7073_slip_percent;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Frequency_Hz] = &data->av.im_siemens_1LA7073_uf_data.frequency_command_Hz;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Voltage_V] = &data->av.im_siemens_1LA7073_uf_data.applied_voltage_magnitude_V;
	js_slowDataArray[JSSD_FLOAT_Inverter_Temperature_DegC] = &data->av.inverter_temperature_degC;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_I_D] = &data->av.im_siemens_1LA7073_id;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_I_Q] = &data->av.im_siemens_1LA7073_iq;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_I_D_Raw] = &data->av.im_siemens_1LA7073_id_raw;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_I_Q_Raw] = &data->av.im_siemens_1LA7073_iq_raw;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Flux_Vs] = &data->av.im_siemens_1LA7073_flux_magnitude_Vs;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Flux_Angle_Rad] = &data->av.im_siemens_1LA7073_flux_angle_rad;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Rotor_Electrical_Angle_Rad] = &data->av.im_siemens_1LA7073_rotor_electrical_angle_rad;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Flux_Rotor_Angle_Difference_Rad] = &data->av.im_siemens_1LA7073_flux_rotor_angle_difference_rad;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Rotor_Electrical_Frequency_Hz] = &data->av.im_siemens_1LA7073_rotor_electrical_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_Inverter_Hardware_Overcurrent] = &data->av.inverter_hardware_overcurrent;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Slip_Frequency_Hz] = &data->av.im_siemens_1LA7073_slip_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_Stator_Frequency_Hz] = &data->av.im_siemens_1LA7073_stator_frequency_Hz;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_I_D_Reference_A] = &data->rasv.im_siemens_1LA7073_id_reference_A;
	js_slowDataArray[JSSD_FLOAT_IM_1LA7073_I_Q_Reference_A] = &data->rasv.im_siemens_1LA7073_iq_reference_A;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Current_Kp_D] = &data->rasv.im_siemens_1LA7073_foc_parameters.current_kp_d;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Current_Ki_D] = &data->rasv.im_siemens_1LA7073_foc_parameters.current_ki_d;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Current_Kp_Q] = &data->rasv.im_siemens_1LA7073_foc_parameters.current_kp_q;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Current_Ki_Q] = &data->rasv.im_siemens_1LA7073_foc_parameters.current_ki_q;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Kalman_Q_A2_Per_S] = &data->rasv.im_siemens_1LA7073_foc_parameters.kalman_q_A2_per_s;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Kalman_R_A2] = &data->rasv.im_siemens_1LA7073_foc_parameters.kalman_r_A2;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Resonant_Gain_D] = &data->rasv.im_siemens_1LA7073_foc_parameters.resonant_gain_d;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Resonant_Gain_Q] = &data->rasv.im_siemens_1LA7073_foc_parameters.resonant_gain_q;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Resonant_Harmonic_Order] = &data->rasv.im_siemens_1LA7073_foc_parameters.resonant_harmonic_order;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Resonant_Antiwindup_Gain] = &data->rasv.im_siemens_1LA7073_foc_parameters.resonant_antiwindup_gain;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Resonant_Voltage_Limit_V] = &data->rasv.im_siemens_1LA7073_foc_parameters.resonant_voltage_limit_V;
	js_slowDataArray[JSSD_FLOAT_IM_FOC_Slip_Flux_Minimum_Vs] = &data->rasv.im_siemens_1LA7073_foc_parameters.slip_flux_minimum_Vs;
/* Project Wizard BEGIN: javascope_slowdata_pointers */
/* Project Wizard END: javascope_slowdata_pointers */

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
