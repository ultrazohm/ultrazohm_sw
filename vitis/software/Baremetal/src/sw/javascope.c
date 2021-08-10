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
#include "../Codegen/uz_codegen.h"
#include "../globalData.h"


float myIQfactor[15] = {1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0, 4096.0, 8192.0, 16384.0};

// IPI Messaging System R5 <-> A53
#define IPI_HEADER			0x1E0000 /* 1E - Target Module ID */
#define IPI_R5toA53_MSG_LEN		8U //27U
#define IPI_A53toR5_MSG_LEN		3U

//Variables for JavaScope
extern ARM_to_Oszi_Data_shared_struct OsziData;
extern Oszi_to_ARM_Data_shared_struct ControlData;
extern Oszi_to_ARM_Data_shared_struct ControlDataShadowBare;
extern uz_codegen codegenInstance;
extern DS_Data Global_Data;

uint32_t cnt_javascope=0, cnt_slowData=0;

uint16_t js_factor1 = 0, js_factor2 = 0, js_factor3 = 0, js_factor4 = 0;

// Channel-pointer and pointer array
float *js_ptr_arr[JSO_ENDMARKER];
float *js_ptr[4];	// channel ptr
float zerovalue = 0.0;
uint32_t  i_fetchDataLifeCheck=0;

//Initialize the Interrupt structure
extern XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

//Xint16 values[20];
union SlowData js_slowDataArray[JSSD_ENDMARKER];

static float lifecheck;
static float ISRExecutionTime;
static float isr_period_us;


int JavaScope_initalize(DS_Data* data)
{
	int Status = 0;
	//Initialize all variables with zero
	int j=0;

	for (j=0; j<JSO_ENDMARKER; j++)
	{
		js_ptr_arr[j] = &zerovalue;
	}

	js_ptr[0] = &zerovalue;
	js_ptr[1] = &zerovalue;
	js_ptr[2] = &zerovalue;
	js_ptr[3] = &zerovalue;

	for (j=0; j<JSSD_ENDMARKER; j++)
	{
		js_slowDataArray[j].i = (uint32_t) zerovalue;
	}

	//Initialize the RAM with zeros
	ControlData.digInputs =0;
	ControlData.id =0;
	ControlData.value =0;

	// Store every observable signal into the Pointer-Array.
	// With the JavaScope, 4 signals can be displayed simultaneously
	// Changing between the observable signals is possible at runtime in the JavaScope.
	// the addresses in Global_Data do not change during runtime, this can be done in the init
	js_ptr_arr[JSO_iu] 			= &codegenInstance.input.Act_Iu;
	js_ptr_arr[JSO_iv] 			= &codegenInstance.input.Act_Iv;
	js_ptr_arr[JSO_iw] 			= &codegenInstance.input.Act_Iw;
	js_ptr_arr[JSO_id] 			= &codegenInstance.output.Id_Act;
	js_ptr_arr[JSO_iq] 			= &codegenInstance.output.Iq_Act;
	js_ptr_arr[JSO_id_ref] 		= &codegenInstance.output.Id_Ref;
	js_ptr_arr[JSO_iq_ref] 		= &codegenInstance.output.Iq_Ref;
	js_ptr_arr[JSO_ud_ref] 		= &codegenInstance.output.Ud_Ref;
	js_ptr_arr[JSO_uq_ref] 		= &codegenInstance.output.Uq_Ref;
	js_ptr_arr[JSO_Speed_rpm]	= &codegenInstance.input.Act_n;
	js_ptr_arr[JSO_Speed_ref_rpm] = &codegenInstance.input.Ref_n;
	js_ptr_arr[JSO_U_ZK] 		= &codegenInstance.input.Act_U_ZK;
	js_ptr_arr[JSO_Theta_el] 	= &codegenInstance.input.Act_theta_el;
	js_ptr_arr[JSO_Theta_mech] 	= &Global_Data.av.theta_mech;
	js_ptr_arr[JSO_Error_I_continuous] = &codegenInstance.output.fault_max_current;
	js_ptr_arr[JSO_Error_I_peak] = &codegenInstance.output.fault_peak_current;
	js_ptr_arr[JSO_Error_n_continuous] = &codegenInstance.output.fault_max_speed;
	js_ptr_arr[JSO_Error_n_peak] = &codegenInstance.output.fault_peak_speed;
	js_ptr_arr[JSO_ISR_ExecutionTime_us] = &ISRExecutionTime;
	js_ptr_arr[JSO_ISR_Period_us] = &isr_period_us;
	js_ptr_arr[JSO_lifecheck]   = &lifecheck;
	return Status;
}


void js_fetchData4CH()
{
	int status;
	u32 MsgPtr[IPI_R5toA53_MSG_LEN] = {0};
	u32 RespBuf[IPI_A53toR5_MSG_LEN] = {0};
	// Refresh variables since the init function sets the javascope to point to a address, but the variables are never refreshed
	lifecheck =  uz_SystemTime_GetInterruptCounter() % 1000;
	ISRExecutionTime=uz_SystemTime_GetIsrExectionTimeInUs();
	isr_period_us=uz_SystemTime_GetIsrPeriodInUs();
	//EL: write values that will be transfered into MsgPtr array
	//MsgPtr contains values, js_ptr contains pointers to values
	memcpy(&(MsgPtr[0]), js_ptr[0], sizeof(u32));
	memcpy(&(MsgPtr[1]), js_ptr[1], sizeof(u32));
	memcpy(&(MsgPtr[2]), js_ptr[2], sizeof(u32));
	memcpy(&(MsgPtr[3]), js_ptr[3], sizeof(u32));

	memcpy(&(MsgPtr[4]), &(js_slowDataArray[cnt_slowData]), sizeof(u32));		// copy without automatic float -> int conversion
	MsgPtr[5] = cnt_slowData;
	MsgPtr[6] = OsziData.status_BareToRTOS;
	MsgPtr[7] = 0;//free 32bit channel


	cnt_javascope++;
	if (cnt_javascope >= 5) //Send a new SlowData only every 5th cycle
	{
		cnt_javascope =0;
		cnt_slowData++;
		if (cnt_slowData >= JSSD_ENDMARKER)
			cnt_slowData = 0;
	}

	i_fetchDataLifeCheck++; //LiveCheck
	if(i_fetchDataLifeCheck > 10000){
		i_fetchDataLifeCheck =0;
	}

	//SW: Write message for interrupt to APU
	status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, MsgPtr, IPI_R5toA53_MSG_LEN, XIPIPSU_BUF_TYPE_MSG);

	//SW: Send an interrupt to APU
	status = XIpiPsu_TriggerIpi(&INTCInst_IPI,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI Trigger failed\r\n");
	}

	//SW: Afterwards an acknowledge and a message from the APU can be read/checked, but we don't do it in order to guarantee that the control-ISR never waits and always runs! -> This is due to the Polling of the acknowledge flag.
	status = XIpiPsu_ReadMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK, RespBuf,IPI_A53toR5_MSG_LEN, XIPIPSU_BUF_TYPE_RESP);
	if(status != (u32)XST_SUCCESS) {
		xil_printf("RPU: IPI reading from A53 failed\r\n");
	}

	ControlData.id 			= (uint16_t)RespBuf[0];
	ControlData.value 		= (uint16_t)RespBuf[1];
	ControlData.digInputs 	= (uint16_t)RespBuf[2];

	//End: send interrupt/message to the other processor with the FreeRTOS----------------------------
}

void JavaScope_update(DS_Data* data){
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
	// Will be transferred one after another (one every 0,5 ms).
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	js_slowDataArray[JSSD_INT_SecondsSinceSystemStart].i 	= uz_SystemTime_GetUptimeInSec();
	js_slowDataArray[JSSD_FLOAT_uSecPerIsr].f 			 	= uz_SystemTime_GetIsrExectionTimeInUs();
	js_slowDataArray[JSSD_FLOAT_Sine].f 					= uz_SystemTime_GetIsrPeriodInUs();
	js_slowDataArray[JSSD_FLOAT_FreqReadback].f 			= data->rasv.referenceFrequency;
	js_slowDataArray[JSSD_INT_Milliseconds].i 				= uz_SystemTime_GetUptimeInMs();
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
	js_slowDataArray[JSSD_FLOAT_i_d].f 			= data->av.I_d; //data->pID.ParameterID_I_d;	//
	js_slowDataArray[JSSD_FLOAT_i_q].f 			= data->av.I_q; //data->pID.ParameterID_I_q;	//
	js_slowDataArray[JSSD_FLOAT_speed].f 		= data->av.mechanicalRotorSpeed;
	js_slowDataArray[JSSD_FLOAT_torque].f 		= data->av.mechanicalTorqueObserved;
	js_slowDataArray[JSSD_FLOAT_encoderOffset].f= data->mrp.incrementalEncoderOffset;
	js_slowDataArray[JSSD_FLOAT_u_d_ref].f 		= data->pID.Offline_ud_ref;
	js_slowDataArray[JSSD_FLOAT_u_q_ref].f 		= data->pID.Offline_uq_ref;
	js_slowDataArray[JSSD_FLOAT_ArrayCounter].f = data->pID.array_counter;
	js_slowDataArray[JSSD_FLOAT_measArray].f 	= data->pID.Online_MessArray_Element; //OHMrichterMotorControl_Y_measArray1[(Xuint16)(data->pID.array_counter)];
	js_slowDataArray[JSSD_FLOAT_i_est].f		= data->pID.Online_i_est_Element; //OHMrichterMotorControl_Y_i_est[(Xuint16)(data->pID.array_counter)];
	js_slowDataArray[JSSD_FLOAT_ArrayControl].f = data->pID.array_counter;
	js_slowDataArray[JSSD_FLOAT_Stribtorque].f 	= data->pID.Offline_BreakawayTorque;
	js_slowDataArray[JSSD_FLOAT_Coulombtorque].f= data->pID.Offline_CoulombFriction;
	js_slowDataArray[JSSD_FLOAT_Viscotorque].f 	= data->pID.Offline_ViscousFriction;
	js_slowDataArray[JSSD_FLOAT_Rs].f 			= data->mrp.motorStatorResistance;
	js_slowDataArray[JSSD_FLOAT_PsiPM].f 		= data->mrp.motorFluxConstant;
	js_slowDataArray[JSSD_FLOAT_TrainInertia].f = data->pID.Offline_totalRotorInertia;//OHMrichterMotorControl_Y_ViscoTorqueLoad;
	js_slowDataArray[JSSD_FLOAT_LoadInertia].f 	= data->pID.Offline_loadRotorInertia;
	js_slowDataArray[JSSD_FLOAT_c_est].f		= data->pID.Offline_TwoMassSystemStiffness;
	js_slowDataArray[JSSD_FLOAT_d_est].f		= data->pID.Offline_TwoMassSystemDamping;
	js_slowDataArray[JSSD_FLOAT_c_0].f			= data->pID.Offline_TwoMassSystem_c_0;
	js_slowDataArray[JSSD_FLOAT_MapCounter].f	= data->pID.map_counter;

	if(data->pID.map_counter<401){ //400 = comes from 20x20 Raster of the flux maps
		js_slowDataArray[JSSD_FLOAT_psidMap].f	= data->pID.FluxMap_d[(uint16_t)(data->pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_psiqMap].f	= data->pID.FluxMap_q[(uint16_t)(data->pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_idMap].f	= data->pID.InvFluxMap_d[(uint16_t)(data->pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_iqMap].f	= data->pID.InvFluxMap_q[(uint16_t)(data->pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_FluxTemp].f	= data->pID.FluxTemp[(uint16_t)(data->pID.map_counter/2)];
	}
	js_slowDataArray[JSSD_FLOAT_psi_array].f	= data->pID.psi_array[(uint16_t)(data->pID.map_counter)];
	js_slowDataArray[JSSD_FLOAT_MapControl].f	= data->pID.map_counter;
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

	js_fetchData4CH();

	// End JavaScope---------------------------------------------------------------------------------------

}
