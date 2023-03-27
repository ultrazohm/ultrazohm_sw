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

#include "../uz/uz_ParameterID/uz_ParameterID.h"
#include "../uz/uz_ParameterID/uz_ParameterID_6ph.h"

extern uz_ParameterID_Data_t ParaID_Data;
float activeState = 0.0f;
float para_state = 0.0f;
float FluxMapCounter = 0.0f;
float ArrayCounter = 0.0f;

extern uz_3ph_dq_t current_rotating_xy;
extern uz_3ph_dq_t  cc_3ph_xy_rotating;
extern float temp_avg;
extern struct uz_DutyCycle_t dutyCycles_set1;
extern struct uz_DutyCycle_t dutyCycles_set2;

float values_milli[4];
float index_array;

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
	js_ch_observable[JSO_Speed_rpm]            = &data->av.mechanicalRotorSpeedRPM;
	js_ch_observable[JSO_ud] = &ParaID_Data.ActualValues.v_dq_6ph.d;
	js_ch_observable[JSO_uq] = &ParaID_Data.ActualValues.v_dq_6ph.q;
	js_ch_observable[JSO_ux] = &ParaID_Data.ActualValues.v_dq_6ph.x;
	js_ch_observable[JSO_uy] = &ParaID_Data.ActualValues.v_dq_6ph.y;
	js_ch_observable[JSO_uz1] = &ParaID_Data.ActualValues.v_dq_6ph.z1;
	js_ch_observable[JSO_uz2] = &ParaID_Data.ActualValues.v_dq_6ph.z2;
	js_ch_observable[JSO_id] = &ParaID_Data.ActualValues.i_dq_6ph.d;
	js_ch_observable[JSO_iq] = &ParaID_Data.ActualValues.i_dq_6ph.q;
	js_ch_observable[JSO_ix] = &ParaID_Data.ActualValues.i_dq_6ph.x;
	js_ch_observable[JSO_iy] = &ParaID_Data.ActualValues.i_dq_6ph.y;
	js_ch_observable[JSO_iz1] = &ParaID_Data.ActualValues.i_dq_6ph.z1;
	js_ch_observable[JSO_iz2] = &ParaID_Data.ActualValues.i_dq_6ph.z2;
	js_ch_observable[JSO_ia1] = &(ParaID_Data.ActualValues.i_abc_6ph.a1);
	js_ch_observable[JSO_ib1] = &(ParaID_Data.ActualValues.i_abc_6ph.b1);
	js_ch_observable[JSO_ic1] = &(ParaID_Data.ActualValues.i_abc_6ph.c1);
	js_ch_observable[JSO_ia2] = &(ParaID_Data.ActualValues.i_abc_6ph.a2);
	js_ch_observable[JSO_ib2] = &(ParaID_Data.ActualValues.i_abc_6ph.b2);
	js_ch_observable[JSO_ic2] = &(ParaID_Data.ActualValues.i_abc_6ph.c2);
	js_ch_observable[JSO_x_rot] = &(ParaID_Data.ActualValues.i_xy_rotating.d);
	js_ch_observable[JSO_y_rot] = &(ParaID_Data.ActualValues.i_xy_rotating.q);
	js_ch_observable[JSO_z1_rot] = &(ParaID_Data.ActualValues.i_zero_rotating.d);
	js_ch_observable[JSO_z2_rot] = &(ParaID_Data.ActualValues.i_zero_rotating.q);


  js_ch_observable[JSO_Theta_el] = &ParaID_Data.ActualValues.theta_el;
  js_ch_observable[JSO_theta_mech] = &ParaID_Data.ActualValues.theta_m;
	js_ch_observable[JSO_state] = &(para_state);
	js_slowDataArray[JSO_fluxmap_index]				= &(ParaID_Data.FluxmapID_extended_controller_Output->array_index);
	js_slowDataArray[JSO_fluxmap_id]				= &(ParaID_Data.FluxmapID_extended_controller_Output->psi_array[0]);
	js_slowDataArray[JSO_fluxmap_iq]				= &(ParaID_Data.FluxmapID_extended_controller_Output->psi_array[1]);
	js_slowDataArray[JSO_fluxmap_psid]				= &(ParaID_Data.FluxmapID_extended_controller_Output->psi_array[2]);
	js_slowDataArray[JSO_fluxmap_psiq]				= &(ParaID_Data.FluxmapID_extended_controller_Output->psi_array[3]);

	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;


	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.mechanicalRotorSpeedRPM);
	js_slowDataArray[JSSD_FLOAT_torque] 		        = &(data->av.mechanicalRotorSpeedRPM);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_u_d]                    = &(ParaID_Data.ActualValues.v_dq_6ph.d);
	js_slowDataArray[JSSD_FLOAT_u_q]                    = &(ParaID_Data.ActualValues.v_dq_6ph.q);
	js_slowDataArray[JSSD_FLOAT_i_d]                    = &(ParaID_Data.ActualValues.i_dq_6ph.d);
	js_slowDataArray[JSSD_FLOAT_i_q]                    = &(ParaID_Data.ActualValues.i_dq_6ph.q);
	js_slowDataArray[JSSD_FLOAT_speed]                  = &(data->av.mechanicalRotorSpeedRPM);
	js_slowDataArray[JSSD_FLOAT_torque]                 = &(data->av.mechanicalRotorSpeedRPM);
	js_slowDataArray[JSSD_FLOAT_PsiPM_Offline]          = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Psi_PM_Vs);
	js_slowDataArray[JSSD_FLOAT_Lq_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Lq_Henry);
	js_slowDataArray[JSSD_FLOAT_Ld_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Ld_Henry);
	js_slowDataArray[JSSD_FLOAT_Rs_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.R_ph_Ohm);
	js_slowDataArray[JSSD_FLOAT_polePairs]              = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.polePairs);
	js_slowDataArray[JSSD_FLOAT_J]                      = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.J_kg_m_squared);
	js_slowDataArray[JSSD_FLOAT_activeState]            = &(activeState);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us]        = &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us]          = &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]           = &System_UpTime_ms;
	js_slowDataArray[JSSD_FLOAT_encoderOffset]          = &(ParaID_Data.ElectricalID_Output->thetaOffset);
	js_slowDataArray[JSSD_FLOAT_ArrayCounter]           = &(ArrayCounter);
	js_slowDataArray[JSSD_FLOAT_measArraySpeed]         = &(ParaID_Data.MeasArraySpeed_pointer);
	js_slowDataArray[JSSD_FLOAT_measArrayTorque]        = &(ParaID_Data.MeasArrayTorque_pointer);
	js_slowDataArray[JSSD_FLOAT_ArrayControlCounter]    = &(ArrayCounter);
	js_slowDataArray[JSSD_FLOAT_Stribtorque]            = &(ParaID_Data.FrictionID_Output->BrkTorque);
	js_slowDataArray[JSSD_FLOAT_Coulombtorque]          = &(ParaID_Data.FrictionID_Output->CoulTorque);
	js_slowDataArray[JSSD_FLOAT_Viscotorque]            = &(ParaID_Data.FrictionID_Output->ViscoTorque);
	js_slowDataArray[JSSD_FLOAT_TrainInertia]           = &(ParaID_Data.TwoMassID_Output->TrainInertia);
	js_slowDataArray[JSSD_FLOAT_LoadInertia]            = &(ParaID_Data.TwoMassID_Output->LoadInertia);
	js_slowDataArray[JSSD_FLOAT_c_est]                  = &(ParaID_Data.TwoMassID_Output->c_est_out);
	js_slowDataArray[JSSD_FLOAT_d_est]                  = &(ParaID_Data.TwoMassID_Output->d_est_out);
	js_slowDataArray[JSSD_FLOAT_I_rated]                = &(ParaID_Data.GlobalConfig.ratCurrent);
	js_slowDataArray[JSSD_FLOAT_totalRotorInertia]      = &(ParaID_Data.TwoMassID_Output->rotorInertia);
	js_slowDataArray[JSSD_FLOAT_Ld_Online]              = &(ParaID_Data.OnlineID_Output->Ld_out);
	js_slowDataArray[JSSD_FLOAT_Lq_Online]              = &(ParaID_Data.OnlineID_Output->Lq_out);
	js_slowDataArray[JSSD_FLOAT_PsiPM_Online]           = &(ParaID_Data.OnlineID_Output->psi_pm_out);
	js_slowDataArray[JSSD_FLOAT_Rs_Online]              = &(ParaID_Data.OnlineID_Output->Rph_out);
	js_slowDataArray[JSSD_FLOAT_n_FluxPoints]           = &(ParaID_Data.FluxMap_MeasuringPoints);
	js_slowDataArray[JSSD_FLOAT_Rs_online_FMID]         = &(ParaID_Data.FluxMapID_Output->R_s);
	js_slowDataArray[JSSD_FLOAT_Wtemp_FMID]             = &(ParaID_Data.FluxMapID_Output->WindingTemp);
	js_slowDataArray[JSSD_FLOAT_MapCounter]             = &(FluxMapCounter);
	js_slowDataArray[JSSD_FLOAT_psidMap]                = &(ParaID_Data.Psi_D_pointer);
	js_slowDataArray[JSSD_FLOAT_psiqMap]                = &(ParaID_Data.Psi_Q_pointer);
	js_slowDataArray[JSSD_FLOAT_MapControlCounter]      = &(FluxMapCounter);
	js_slowDataArray[JSSD_FLOAT_temp_inv1]				= &(data->av.temperature_inv_1);
	js_slowDataArray[JSSD_FLOAT_temp_inv2]				= &(data->av.temperature_inv_2);
	js_slowDataArray[JSSD_FLOAT_fluxmap_index]				= &(index_array);
	js_slowDataArray[JSSD_FLOAT_fluxmap_id]				= &(values_milli[0]);
	js_slowDataArray[JSSD_FLOAT_fluxmap_iq]				= &(values_milli[1]);
	js_slowDataArray[JSSD_FLOAT_fluxmap_psid]				= &(values_milli[2]);
	js_slowDataArray[JSSD_FLOAT_fluxmap_psiq]				= &(values_milli[3]);



	return Status;
}



void JavaScope_update(DS_Data* data){

	// create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START;
	struct APU_to_RPU_t Received_Data_from_A53 = {0};

	static int js_cnt_slowData=0;
	int status = XST_SUCCESS;
	para_state = activeState;
	uz_ParameterID_update_transmit_values(&ParaID_Data, &activeState, &FluxMapCounter, &ArrayCounter);

	values_milli[0] = 1000.0f*ParaID_Data.FluxmapID_extended_controller_Output->psi_array[0];
	values_milli[1] = 1000.0f*ParaID_Data.FluxmapID_extended_controller_Output->psi_array[1];
	values_milli[2] = 1000.0f*ParaID_Data.FluxmapID_extended_controller_Output->psi_array[2];
	values_milli[3] = 1000.0f*ParaID_Data.FluxmapID_extended_controller_Output->psi_array[3];
	index_array = (float) ParaID_Data.FluxmapID_extended_controller_Output->array_index;
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
