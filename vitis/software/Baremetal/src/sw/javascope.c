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
******************************************************************************/

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
uint32_t js_status_BareToRTOS=0;

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

//Experimental code
extern uz_ParameterID_Data_t PID_Data;

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
	js_ch_observable[JSO_Speed_rpm] = &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_ia] = &PID_Data.PID_ActualValues.I_UVW.U;
	js_ch_observable[JSO_ib] = &PID_Data.PID_ActualValues.I_UVW.V;
	js_ch_observable[JSO_ic] = &PID_Data.PID_ActualValues.I_UVW.W;
	js_ch_observable[JSO_ua] = &PID_Data.PID_ActualValues.V_UVW.U;
	js_ch_observable[JSO_ib] = &PID_Data.PID_ActualValues.V_UVW.V;
	js_ch_observable[JSO_ic] = &PID_Data.PID_ActualValues.V_UVW.W;
	js_ch_observable[JSO_iq] = &PID_Data.PID_ActualValues.i_dq.q;
	js_ch_observable[JSO_id] = &PID_Data.PID_ActualValues.i_dq.d;
	js_ch_observable[JSO_Theta_el] 		= &data->av.theta_elec;
	js_ch_observable[JSO_theta_mech] 	= &data->av.theta_mech;
	js_ch_observable[JSO_Wtemp] = &PID_Data.PID_OnlineID_Output.Wtemp;
	js_ch_observable[JSO_ud] = &PID_Data.PID_ActualValues.v_dq.d;
	js_ch_observable[JSO_uq] = &PID_Data.PID_ActualValues.v_dq.q;
	js_ch_observable[JSO_Ld_mH] = &PID_Data.PID_OnlineID_Output.Ld_out;
	js_ch_observable[JSO_Lq_mH] = &PID_Data.PID_OnlineID_Output.Lq_out;
	js_ch_observable[JSO_Rs_mOhm] = &PID_Data.PID_OnlineID_Output.Rph_out;
	js_ch_observable[JSO_PsiPM_mVs] = &PID_Data.PID_OnlineID_Output.psi_pm_out;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;


	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	// Only float is allowed!
	js_slowDataArray[JSSD_FLOAT_FreqReadback] 		  	= &(data->rasv.referenceFrequency);
	js_slowDataArray[JSSD_FLOAT_ADCconvFactorReadback] 	= &(data->mrp.ADCconvFactorReadback);
	js_slowDataArray[JSSD_FLOAT_PsiPM_Offline] = &(PID_Data.PID_ElectricalID_Output.PMSM_parameters.Psi_PM_Vs);
	js_slowDataArray[JSSD_FLOAT_Lq_Offline] = &(PID_Data.PID_ElectricalID_Output.PMSM_parameters.Lq_Henry);
	js_slowDataArray[JSSD_FLOAT_Ld_Offline] = &(PID_Data.PID_ElectricalID_Output.PMSM_parameters.Ld_Henry);
	js_slowDataArray[JSSD_FLOAT_Rs_Offline] = &(PID_Data.PID_ElectricalID_Output.PMSM_parameters.R_ph_Ohm);
	js_slowDataArray[JSSD_FLOAT_polePairs] = &(PID_Data.PID_ElectricalID_Output.PMSM_parameters.polePairs);
	js_slowDataArray[JSSD_FLOAT_J] = &(PID_Data.PID_ElectricalID_Output.PMSM_parameters.J_kg_m_squared);
	js_slowDataArray[JSSD_FLOAT_activeState] = &(PID_Data.PID_Controller_Parameters.activeState);
	js_slowDataArray[JSSD_FLOAT_J] 			         	= &(data->pID.Offline_motorRotorInertia);
	js_slowDataArray[JSSD_FLOAT_u_d] = &(PID_Data.PID_ActualValues.v_dq.d);
	js_slowDataArray[JSSD_FLOAT_u_q] = &(PID_Data.PID_ActualValues.v_dq.q);
	js_slowDataArray[JSSD_FLOAT_i_d] = &(PID_Data.PID_ActualValues.i_dq.d);
	js_slowDataArray[JSSD_FLOAT_i_q] = &(PID_Data.PID_ActualValues.i_dq.q);
	js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(data->av.mechanicalRotorSpeed);
	js_slowDataArray[JSSD_FLOAT_torque] 		        = &(data->av.mechanicalTorqueObserved);
	js_slowDataArray[JSSD_FLOAT_encoderOffset]         	= &(data->mrp.incrementalEncoderOffset);
	js_slowDataArray[JSSD_FLOAT_u_d_ref] 		        = &(data->pID.Offline_ud_ref);
	js_slowDataArray[JSSD_FLOAT_u_q_ref] 		        = &(data->pID.Offline_uq_ref);
	js_slowDataArray[JSSD_FLOAT_ArrayCounter]           = &(data->pID.array_counter);
	js_slowDataArray[JSSD_FLOAT_measArray] 	         	= &(data->pID.Online_MessArray_Element);
	js_slowDataArray[JSSD_FLOAT_i_est]		        	= &(data->pID.Online_i_est_Element);
	js_slowDataArray[JSSD_FLOAT_ArrayControl]          	= &(data->pID.array_counter);
	js_slowDataArray[JSSD_FLOAT_Stribtorque] = &(PID_Data.PID_FrictionID_Output.BrkTorque);
	js_slowDataArray[JSSD_FLOAT_Coulombtorque] = &(PID_Data.PID_FrictionID_Output.CoulTorque);
	js_slowDataArray[JSSD_FLOAT_Viscotorque] = &(PID_Data.PID_FrictionID_Output.ViscoTorque);
	js_slowDataArray[JSSD_FLOAT_Rs] 			        = &(data->mrp.motorStatorResistance);
	js_slowDataArray[JSSD_FLOAT_PsiPM] 		         	= &(data->mrp.motorFluxConstant);
	js_slowDataArray[JSSD_FLOAT_TrainInertia]         	= &(data->pID.Offline_totalRotorInertia);
	js_slowDataArray[JSSD_FLOAT_LoadInertia] 	        = &(data->pID.Offline_loadRotorInertia);
	js_slowDataArray[JSSD_FLOAT_c_est]		         	= &(data->pID.Offline_TwoMassSystemStiffness);
	js_slowDataArray[JSSD_FLOAT_d_est]		         	= &(data->pID.Offline_TwoMassSystemDamping);
	js_slowDataArray[JSSD_FLOAT_c_0]			        = &(data->pID.Offline_TwoMassSystem_c_0);
	js_slowDataArray[JSSD_FLOAT_I_rated]		        = &(data->mrp.motorNominalCurrent);
	js_slowDataArray[JSSD_FLOAT_Wtemp] = &(PID_Data.PID_OnlineID_Output.Wtemp);
	js_slowDataArray[JSSD_FLOAT_FluxTempConst]         	= &(data->pID.FluxTempConst);
	js_slowDataArray[JSSD_FLOAT_FluxTempError]         	= &(data->pID.FluxTempError);
	js_slowDataArray[JSSD_FLOAT_Ld_Online] = &(PID_Data.PID_OnlineID_Output.Ld_out);
	js_slowDataArray[JSSD_FLOAT_Lq_Online] = &(PID_Data.PID_OnlineID_Output.Lq_out);
	js_slowDataArray[JSSD_FLOAT_PsiPM_Online] = &(PID_Data.PID_OnlineID_Output.psi_pm_out);
	js_slowDataArray[JSSD_FLOAT_Rs_Online] = &(PID_Data.PID_OnlineID_Output.Rph_out);
	js_slowDataArray[JSSD_FLOAT_n_FluxPoints]	        = &(data->pID.n_FluxPoints);
	js_slowDataArray[JSSD_FLOAT_Ld] 			        = &(data->mrp.motorDirectInductance);
	js_slowDataArray[JSSD_FLOAT_Lq] 			        = &(data->mrp.motorQuadratureInductance);
	js_slowDataArray[JSSD_FLOAT_totalRotorInertia] 	 	= &(data->mrp.totalRotorInertia);
	js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us] 		= &ISR_execution_time_us;
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us] 			= &ISR_period_us;
	js_slowDataArray[JSSD_FLOAT_Milliseconds]			= &System_UpTime_ms;

	return Status;
}



void JavaScope_update(DS_Data* data){

	// create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START;
	struct APU_to_RPU_t Received_Data_from_A53;

	static int js_cnt_slowData=0;
	int status;

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
