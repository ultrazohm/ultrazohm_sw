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

// Channel-pointer and pointer array
static float zerovalue = 0.0;
static union SlowData js_slowDataArray[JSSD_ENDMARKER];
float *js_ptr_arr[JSO_ENDMARKER];
float *js_ptr[JS_CHANNELS];			// channel ptr

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

static float lifecheck;
static float ISR_execution_time_us;
static float ISR_period_us;

uint32_t i_fetchDataLifeCheck=0;
uint32_t js_status_BareToRTOS=0;

int JavaScope_initalize(DS_Data* data)
{
	int Status = 0;
	//Initialize all variables with zero
	for (int j=0; j<JSO_ENDMARKER; j++)
	{
		js_ptr_arr[j] = &zerovalue;
	}

	for(int j=0; j<JS_CHANNELS; j++)
	{
		js_ptr[j] = &zerovalue;
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
	js_ptr_arr[JSO_Speed_rpm]	= &data->av.mechanicalRotorSpeed;
	js_ptr_arr[JSO_ia] 			= &data->av.I_U;
	js_ptr_arr[JSO_ib] 			= &data->av.I_V;
	js_ptr_arr[JSO_ic] 			= &data->av.I_W;
	js_ptr_arr[JSO_ua] 			= &data->av.U_U;
	js_ptr_arr[JSO_ub] 			= &data->av.U_V;
	js_ptr_arr[JSO_uc] 			= &data->av.U_W;
	js_ptr_arr[JSO_iq] 			= &data->av.I_q;
	js_ptr_arr[JSO_id] 			= &data->av.I_d;
	js_ptr_arr[JSO_Theta_el] 	= &data->av.theta_elec;
	js_ptr_arr[JSO_theta_mech] 	= &data->av.theta_mech;
	js_ptr_arr[JSO_Wtemp]		= &data->pID.WindingTemp;
	js_ptr_arr[JSO_ud]			= &data->av.U_d;
	js_ptr_arr[JSO_uq]			= &data->av.U_q;
	js_ptr_arr[JSO_Ld_mH]		= &data->pID.Online_Ld;
	js_ptr_arr[JSO_Lq_mH]		= &data->pID.Online_Lq;
	js_ptr_arr[JSO_Rs_mOhm]		= &data->pID.Online_Rs;
	js_ptr_arr[JSO_PsiPM_mVs]	= &data->pID.Online_Psi_PM;
	js_ptr_arr[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
	js_ptr_arr[JSO_lifecheck]   	= &lifecheck;
	js_ptr_arr[JSO_ISR_Period_us]   = &ISR_period_us;
	return Status;
}


void js_fetchData()
{
	// create pointer to struct javascope_data_t named javascope_data located at MEM_SHARED_START
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
		javascope_data->scope_ch[j] = *js_ptr[j];
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
	js_slowDataArray[JSSD_FLOAT_PsiPM_Offline].f= data->pID.Offline_Psi_PM;
	js_slowDataArray[JSSD_FLOAT_Lq_Offline].f 	= data->pID.Offline_Lq;
	js_slowDataArray[JSSD_FLOAT_Ld_Offline].f 	= data->pID.Offline_Ld;
	js_slowDataArray[JSSD_FLOAT_Rs_Offline].f 	= data->pID.Offline_Rs;
	js_slowDataArray[JSSD_INT_polePairs].i 		= (int)data->mrp.motorPolePairNumber;
	js_slowDataArray[JSSD_FLOAT_J].f 			= data->pID.Offline_motorRotorInertia;
	js_slowDataArray[JSSD_INT_activeState].i 	= data->pID.activeState;
	js_slowDataArray[JSSD_FLOAT_J].f 			= data->pID.Offline_motorRotorInertia;
	js_slowDataArray[JSSD_FLOAT_u_d].f 			= data->av.U_d;
	js_slowDataArray[JSSD_FLOAT_u_q].f 			= data->av.U_q;
	js_slowDataArray[JSSD_FLOAT_i_d].f 			= data->av.I_d;
	js_slowDataArray[JSSD_FLOAT_i_q].f 			= data->av.I_q;
	js_slowDataArray[JSSD_FLOAT_speed].f 		= data->av.mechanicalRotorSpeed;
	js_slowDataArray[JSSD_FLOAT_torque].f 		= data->av.mechanicalTorqueObserved;
	js_slowDataArray[JSSD_FLOAT_encoderOffset].f= data->mrp.incrementalEncoderOffset;
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
	js_slowDataArray[JSSD_FLOAT_Wtemp].f		= data->pID.WindingTemp;
	js_slowDataArray[JSSD_FLOAT_FluxTempConst].f= data->pID.FluxTempConst;
	js_slowDataArray[JSSD_FLOAT_FluxTempError].f= data->pID.FluxTempError;
	js_slowDataArray[JSSD_FLOAT_Ld_Online].f	= data->pID.Online_Ld;
	js_slowDataArray[JSSD_FLOAT_Lq_Online].f	= data->pID.Online_Lq;
	js_slowDataArray[JSSD_FLOAT_PsiPM_Online].f	= data->pID.Online_Psi_PM;
	js_slowDataArray[JSSD_FLOAT_Rs_Online].f	= data->pID.Online_Rs;
	js_slowDataArray[JSSD_FLOAT_n_FluxPoints].f	= data->pID.n_FluxPoints;
	js_slowDataArray[JSSD_FLOAT_Ld].f 			= data->mrp.motorDirectInductance;
	js_slowDataArray[JSSD_FLOAT_Lq].f 			= data->mrp.motorQuadratureInductance;
	js_slowDataArray[JSSD_FLOAT_totalRotorInertia].f 	= data->mrp.totalRotorInertia;

	js_fetchData();

	// End JavaScope---------------------------------------------------------------------------------------

}
