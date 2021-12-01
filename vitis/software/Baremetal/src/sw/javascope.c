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
#include "xil_cache.h"

// IPI Messaging System R5 <-> A53
#define IPI_A53toR5_MSG_LEN		3U

//Variables for JavaScope
static Oszi_to_ARM_Data_shared_struct ControlData;

static float zerovalue = 0.0;
static union SlowData js_slowDataArray[JSSD_ENDMARKER];
float *js_ch_observable[JSO_ENDMARKER];
float *js_ch_selected[JS_CHANNELS];

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

static float lifecheck;
static float ISR_execution_time_us;
static float ISR_period_us;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;

//Experimental Code
extern uz_ParameterID_Data_t PID_Data;

int JavaScope_initalize(DS_Data* data)
{
	int Status = 0;
	//Initialize all variables with zero
	for (int j=0; j<JSO_ENDMARKER; j++)
	{
		js_ch_observable[j] = &zerovalue;
	}

	for(int j=0; j<JS_CHANNELS; j++)
	{
		js_ch_selected[j] = &zerovalue;
	}

	for (int j=0; j<JSSD_ENDMARKER; j++)
	{
		js_slowDataArray[j].i = (uint32_t) zerovalue;
	}

	ControlData.digInputs =0;
	ControlData.id =0;
	ControlData.value =0;

	// Store every observable signal into the Pointer-Array.
	// With the JavaScope, signals can be displayed simultaneously
	// Changing between the observable signals is possible at runtime in the JavaScope.
	// the addresses in Global_Data do not change during runtime, this can be done in the init
	js_ch_observable[JSO_Speed_rpm]		= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_ia] = &PID_Data.PID_ActualValues.I_UVW.U;
	js_ch_observable[JSO_ib] = &PID_Data.PID_ActualValues.I_UVW.V;
	js_ch_observable[JSO_ic] = &PID_Data.PID_ActualValues.I_UVW.W;
	js_ch_observable[JSO_ua] = &PID_Data.PID_ActualValues.U_UVW.U;
	js_ch_observable[JSO_ib] = &PID_Data.PID_ActualValues.U_UVW.V;
	js_ch_observable[JSO_ic] = &PID_Data.PID_ActualValues.U_UVW.W;
	js_ch_observable[JSO_iq] = &PID_Data.PID_ActualValues.i_dq.d;
	js_ch_observable[JSO_id] = &PID_Data.PID_ActualValues.i_dq.q;
	js_ch_observable[JSO_Theta_el] 		= &data->av.theta_elec;
	js_ch_observable[JSO_theta_mech] 	= &data->av.theta_mech;
	js_ch_observable[JSO_Wtemp]			= &data->pID.WindingTemp;
	js_ch_observable[JSO_ud] = &PID_Data.PID_ActualValues.u_dq.d;
	js_ch_observable[JSO_uq] = &PID_Data.PID_ActualValues.u_dq.q;
	js_ch_observable[JSO_Ld_mH]			= &data->pID.Online_Ld;
	js_ch_observable[JSO_Lq_mH]			= &data->pID.Online_Lq;
	js_ch_observable[JSO_Rs_mOhm]		= &data->pID.Online_Rs;
	js_ch_observable[JSO_PsiPM_mVs]		= &data->pID.Online_Psi_PM;
	js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ch_observable[JSO_lifecheck]   	= &lifecheck;
	js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;
	return Status;
}


void js_fetchData()
{
	// create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START
	static struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START;

	static int js_cnt_slowData=0;
	int status;
	u32 RespBuf[IPI_A53toR5_MSG_LEN] = {0};

	// Refresh variables since the init function sets the javascope to point to a address, but the variables are never refreshed
	lifecheck 				= uz_SystemTime_GetInterruptCounter() % 1000;
	ISR_execution_time_us	= uz_SystemTime_GetIsrExectionTimeInUs();
	ISR_period_us			= uz_SystemTime_GetIsrPeriodInUs();

	// write data to shared memory
	for(int j=0; j<JS_CHANNELS; j++){
		javascope_data->scope_ch[j] = *js_ch_selected[j];
	}
	javascope_data->slowDataID 		= js_cnt_slowData;
	javascope_data->slowDataContent = js_slowDataArray[js_cnt_slowData].u;
	javascope_data->status 			= js_status_BareToRTOS;

	// flush data cache of shared memory region to make sure shared memory is updated
	Xil_DCacheFlushRange(MEM_SHARED_START, JAVASCOPE_DATA_SIZE_2POW);

	//Send an interrupt to APU
	status = XIpiPsu_TriggerIpi(&INTCInst_IPI,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI Trigger failed\r\n");
	}

	//Afterwards an acknowledge and a message from the APU can be read/checked, but we don't do it in order to guarantee that the control-ISR never waits and always runs! -> This is due to the Polling of the acknowledge flag.
	status = XIpiPsu_ReadMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, RespBuf,IPI_A53toR5_MSG_LEN, XIPIPSU_BUF_TYPE_RESP);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI reading from A53 failed\r\n");
	}

	ControlData.id 			= (uint16_t)RespBuf[0];
	ControlData.value 		= (uint16_t)RespBuf[1];
	ControlData.digInputs 	= (uint16_t)RespBuf[2];

	js_cnt_slowData++;
	if (js_cnt_slowData >= JSSD_ENDMARKER){
		js_cnt_slowData = 0;
	}

	i_fetchDataLifeCheck++; //LiveCheck
	if(i_fetchDataLifeCheck > 10000){
		i_fetchDataLifeCheck =0;
	}
}

void JavaScope_update(DS_Data* data){
	static Oszi_to_ARM_Data_shared_struct ControlDataShadowBare;

	 //In order to avoid unnecessary memory access, call only if something has changed!
	if((ControlDataShadowBare.id != ControlData.id)||(ControlDataShadowBare.value != ControlData.value)){
		//Safe the current control data into a shadow register
		ControlDataShadowBare.id = ControlData.id;
		ControlDataShadowBare.value = ControlData.value;
		ControlDataShadowBare.digInputs = ControlData.digInputs;
		//Read the control values from JavaScope
		ipc_Control_func(ControlDataShadowBare.id, ControlDataShadowBare.value, data); //check always in while(1) if there are new control values
	}

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	js_slowDataArray[JSSD_INT_SecondsSinceSystemStart].i= uz_SystemTime_GetUptimeInSec();
	js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us].f 		= uz_SystemTime_GetIsrExectionTimeInUs();
	js_slowDataArray[JSSD_FLOAT_ISR_Period_us].f 		= uz_SystemTime_GetIsrPeriodInUs();
	js_slowDataArray[JSSD_INT_Milliseconds].i 			= uz_SystemTime_GetUptimeInMs();

	js_slowDataArray[JSSD_FLOAT_FreqReadback].f 		= data->rasv.referenceFrequency;
	js_slowDataArray[JSSD_FLOAT_ADCconvFactorReadback].f = data->mrp.ADCconvFactorReadback;
	js_slowDataArray[JSSD_FLOAT_PsiPM_Offline].f = PID_Data.PID_ElectricalID_Output.PMSM_parameters.Psi_PM_Vs;
	js_slowDataArray[JSSD_FLOAT_Lq_Offline].f = PID_Data.PID_ElectricalID_Output.PMSM_parameters.Lq_Henry;
	js_slowDataArray[JSSD_FLOAT_Ld_Offline].f = PID_Data.PID_ElectricalID_Output.PMSM_parameters.Ld_Henry;
	js_slowDataArray[JSSD_FLOAT_Rs_Offline].f = PID_Data.PID_ElectricalID_Output.PMSM_parameters.R_ph_Ohm;
	js_slowDataArray[JSSD_INT_polePairs].i = (uint16_T) PID_Data.PID_ElectricalID_Output.PMSM_parameters.polePairs;
	js_slowDataArray[JSSD_FLOAT_J].f = PID_Data.PID_ElectricalID_Output.PMSM_parameters.J_kg_m_squared;
	js_slowDataArray[JSSD_INT_activeState].i = PID_Data.PID_Controller_Parameters.activeState;
	js_slowDataArray[JSSD_FLOAT_u_d].f = PID_Data.PID_ActualValues.u_dq.d;
	js_slowDataArray[JSSD_FLOAT_u_q].f = PID_Data.PID_ActualValues.u_dq.q;
	js_slowDataArray[JSSD_FLOAT_i_d].f = PID_Data.PID_ActualValues.i_dq.d;
	js_slowDataArray[JSSD_FLOAT_i_q].f = PID_Data.PID_ActualValues.i_dq.q;
	js_slowDataArray[JSSD_FLOAT_speed].f 		= data->av.mechanicalRotorSpeed;
	js_slowDataArray[JSSD_FLOAT_torque].f 		= data->av.mechanicalTorqueObserved;
	js_slowDataArray[JSSD_FLOAT_encoderOffset].f = PID_Data.PID_ElectricalID_Output.thetaOffset;
	js_slowDataArray[JSSD_FLOAT_u_d_ref].f 		= data->pID.Offline_ud_ref;
	js_slowDataArray[JSSD_FLOAT_u_q_ref].f 		= data->pID.Offline_uq_ref;
	js_slowDataArray[JSSD_FLOAT_ArrayCounter].f = data->pID.array_counter;
	js_slowDataArray[JSSD_FLOAT_measArray].f 	= data->pID.Online_MessArray_Element;
	js_slowDataArray[JSSD_FLOAT_i_est].f		= data->pID.Online_i_est_Element;
	js_slowDataArray[JSSD_FLOAT_ArrayControl].f = data->pID.array_counter;
	js_slowDataArray[JSSD_FLOAT_Stribtorque].f 	= data->pID.Offline_BreakawayTorque;
	js_slowDataArray[JSSD_FLOAT_Coulombtorque].f= data->pID.Offline_CoulombFriction;
	js_slowDataArray[JSSD_FLOAT_Viscotorque].f 	= data->pID.Offline_ViscousFriction;
	js_slowDataArray[JSSD_FLOAT_Rs].f 			= data->mrp.motorStatorResistance;
	js_slowDataArray[JSSD_FLOAT_PsiPM].f 		= data->mrp.motorFluxConstant;
	js_slowDataArray[JSSD_FLOAT_TrainInertia].f = data->pID.Offline_totalRotorInertia;
	js_slowDataArray[JSSD_FLOAT_LoadInertia].f 	= data->pID.Offline_loadRotorInertia;
	js_slowDataArray[JSSD_FLOAT_c_est].f		= data->pID.Offline_TwoMassSystemStiffness;
	js_slowDataArray[JSSD_FLOAT_d_est].f		= data->pID.Offline_TwoMassSystemDamping;
	js_slowDataArray[JSSD_FLOAT_c_0].f			= data->pID.Offline_TwoMassSystem_c_0;
	js_slowDataArray[JSSD_FLOAT_I_rated].f		= data->mrp.motorNominalCurrent;
	js_slowDataArray[JSSD_FLOAT_Wtemp].f = PID_Data.PID_FluxMapID_Output.WindingTemp;
	js_slowDataArray[JSSD_FLOAT_FluxTempConst].f= data->pID.FluxTempConst;
	js_slowDataArray[JSSD_FLOAT_FluxTempError].f= data->pID.FluxTempError;
	js_slowDataArray[JSSD_FLOAT_Ld_Online].f	= data->pID.Online_Ld;
	js_slowDataArray[JSSD_FLOAT_Lq_Online].f	= data->pID.Online_Lq;
	js_slowDataArray[JSSD_FLOAT_PsiPM_Online].f	= data->pID.Online_Psi_PM;
	js_slowDataArray[JSSD_FLOAT_Rs_Online].f = PID_Data.PID_FluxMapID_Output.R_s;
	js_slowDataArray[JSSD_FLOAT_n_FluxPoints].f	= data->pID.n_FluxPoints;
	js_slowDataArray[JSSD_FLOAT_Ld].f 			= data->mrp.motorDirectInductance;
	js_slowDataArray[JSSD_FLOAT_Lq].f 			= data->mrp.motorQuadratureInductance;
	js_slowDataArray[JSSD_FLOAT_totalRotorInertia].f 	= data->mrp.totalRotorInertia;

	js_fetchData();

	// End JavaScope---------------------------------------------------------------------------------------

}
