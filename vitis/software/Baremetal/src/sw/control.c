/******************************************************************************
 * Copyright 2025 Andreas Geiger
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

#include "control.h"
#include "misc_IO.h"
#include "APU_RPU_shared.h"
#include "xil_cache.h"
#include "../include/ipc_ARM.h"
#include "appl/Inverter_Temp_Driver.h"

// --- Simulink model variables ---
RT_MODEL_FOC_FCF_T FOC_FCF_M_;
RT_MODEL_FOC_FCF_T *const FOC_FCF_MPtr = &FOC_FCF_M_;/* Real-time model */
B_FOC_FCF_T FOC_FCF_B;          /* Observable signals */
DW_FOC_FCF_T FOC_FCF_DW;        /* Observable states */
ExtU_FOC_FCF_T FOC_FCF_U;       /* External inputs */
ExtY_FOC_FCF_T FOC_FCF_Y;       /* External outputs */

RT_MODEL_FOC_SCF_T FOC_SCF_M_;
RT_MODEL_FOC_SCF_T *const FOC_SCF_MPtr = &FOC_SCF_M_;
B_FOC_SCF_T FOC_SCF_B;          /* Observable signals */
DW_FOC_SCF_T FOC_SCF_DW;        /* Observable states */
ExtU_FOC_SCF_T FOC_SCF_U;       /* External inputs */
ExtY_FOC_SCF_T FOC_SCF_Y;       /* External outputs */

RT_MODEL_FOC_SMF_T FOC_SMF_M_;
RT_MODEL_FOC_SMF_T *const FOC_SMF_MPtr = &FOC_SMF_M_;/* Real-time model */
DW_FOC_SMF_T FOC_SMF_DW;        /* Observable states */
ExtU_FOC_SMF_T FOC_SMF_U;       /* External inputs */
ExtY_FOC_SMF_T FOC_SMF_Y;       /* External outputs */
// ----------------------

// system variables that are set by a timer and deleted after function processing
uint8_t Control_FLAG_1ms;
uint8_t Control_FLAG_10ms;
uint8_t Control_FLAG_100ms;

ctrl_data_t ctrl_data;


// Pointer to variables in shared OCM, (A53 writes / R5 reads)
struct data_A2R_t volatile * const data_A2R = (struct data_A2R_t *)(MEM_SHARED_START_APP_A2R);
// Pointer to variables in shared OCM, (R5 writes / A53 reads)
//struct data_R2A_t volatile * const data_R2A = (struct data_R2A_t *)(MEM_SHARED_START_APP_R2A);
struct data_A2R_t data_A2R_localRPU;
struct data_R2A_t data_R2A_localRPU;

// IPI instance from ISR module (defined elsewhere)
extern XIpiPsu INTCInst_IPI;

uint8_t OUT_KL15;
uint8_t OUT_PYRO_TRIGGER;
uint8_t OUT_RELAY2_CLOSE;
uint8_t OUT_RELAY3_CLOSE;
uint32_t IN_AXI_GPIO_bit_word;
uint8_t IN_KL_15_PG;
uint8_t IN_IGNITION_SUCCESS;
uint8_t IN_RELAY2_NOT_CLOSED;
uint8_t IN_RELAY3_NOT_CLOSED;

// variables for inverter temperature measurement
float DutyCycleMeas_Value;
uint32_t PWMin_HighTicks;
uint32_t PWMin_PeriodTicks;
uint32_t DutyCycleIPcoreTimestamp;


void init_control_functions(void)
{
	/* Pack model data into RTM */
	FOC_FCF_MPtr->blockIO = &FOC_FCF_B;
	FOC_FCF_MPtr->dwork = &FOC_FCF_DW;
	FOC_FCF_MPtr->inputs = &FOC_FCF_U;
	FOC_FCF_MPtr->outputs = &FOC_FCF_Y;

	/* Initialize model */
	FOC_FCF_initialize(FOC_FCF_MPtr);

	/* Pack model data into RTM */
	FOC_SCF_MPtr->blockIO = &FOC_SCF_B;
	FOC_SCF_MPtr->dwork = &FOC_SCF_DW;
	FOC_SCF_MPtr->inputs = &FOC_SCF_U;
	FOC_SCF_MPtr->outputs = &FOC_SCF_Y;

	/* Initialize model */
	FOC_SCF_initialize(FOC_SCF_MPtr);

	/* Pack model data into RTM */
	FOC_SMF_MPtr->dwork = &FOC_SMF_DW;
	FOC_SMF_MPtr->inputs = &FOC_SMF_U;
	FOC_SMF_MPtr->outputs = &FOC_SMF_Y;

	/* Initialize model */
	FOC_SMF_initialize(FOC_SMF_MPtr);
}

/**
 * Control Task 1ms
 */
void Control_Task_1ms(void)
{
	/* --- execute Simulink Slow Control Function --- */
	FOC_SCF_MPtr->inputs->bus_FCF     = ctrl_data.bus_FCF;
	FOC_SCF_MPtr->inputs->bus_SMF     = ctrl_data.bus_SMF;
	FOC_SCF_MPtr->inputs->bus_BSW_SMF = ctrl_data.bus_BSW_SMF;

	FOC_SCF_step(FOC_SCF_MPtr);

	ctrl_data.bus_SCF = FOC_SCF_MPtr->outputs->bus_SCF;
	/* --- End of Simulink Slow Control Function --- */

	/* === provide data for CAN communication via R5 === */
	data_R2A_localRPU.Torque_Actual   = ctrl_data.bus_SCF.TorqueEst;
	data_R2A_localRPU.Speed_Actual    = ctrl_data.bus_SCF.n_Act;
	data_R2A_localRPU.Voltage_DC_Link = ctrl_data.bus_FCF.U_DC;
	/* === End of provide data for CAN communication === */
}

/**
 * Control Task 10ms
 */
void Control_Task_10ms(void)
{
	/* === Read A53 -> R5 shared data (OCM) ========== */
	// Invalidate CPU data cache for the shared area so we read fresh values
	Xil_DCacheInvalidateRange((u32)data_A2R, sizeof(struct data_A2R_t));

	// Read values written by A53 and save to local struct to provide data to R5 functions
	data_A2R_localRPU = *data_A2R;
	/* === End of read A53 -> R5 shared data (OCM) === */


	/* === Read miscellanious inputs from FPGA interface ========== */
	IN_AXI_GPIO_bit_word = uz_get_misc_inputs();
	IN_KL_15_PG          = (IN_AXI_GPIO_bit_word >> 0) & 0x01;
	IN_IGNITION_SUCCESS  = (IN_AXI_GPIO_bit_word >> 1) & 0x01;
	IN_RELAY2_NOT_CLOSED = (IN_AXI_GPIO_bit_word >> 2) & 0x01;
	IN_RELAY3_NOT_CLOSED = (IN_AXI_GPIO_bit_word >> 3) & 0x01;
	/* === End of read miscellanious inputs from FPGA interface === */


	/* === Start of Simulink State Machine Function === */
	ctrl_data.bus_BSW_SMF.EXT_State_Request  = data_A2R_localRPU.State_Request;
	ctrl_data.bus_BSW_SMF.EXT_Torque_Request = data_A2R_localRPU.Torque_Request;
	ctrl_data.bus_BSW_SMF.EXT_Speed_Request  = data_A2R_localRPU.Speed_Request;
	ctrl_data.bus_BSW_SMF.EXT_KL15_PG        = IN_KL_15_PG;


	FOC_SMF_MPtr->inputs->bus_BSW_SMF = ctrl_data.bus_BSW_SMF;
	FOC_SMF_MPtr->inputs->bus_FCF     = ctrl_data.bus_FCF;

	FOC_SMF_step(FOC_SMF_MPtr);

	ctrl_data.bus_SMF = FOC_SMF_MPtr->outputs->bus_SMF;
	/* === End of Simulink State Machine Function === */


	/* === Write miscellanious outputs to FPGA interface ========== */
	uz_set_misc_outputs(OUT_KL15, OUT_PYRO_TRIGGER, OUT_RELAY2_CLOSE, OUT_RELAY3_CLOSE);
	/* === End of write miscellanious outputs to FPGA interface === */


#if 0
	/* --- Write R5 -> A53 shared data and notify A53 --- */
	// Map SMF outputs into the shared R5->A53 structure (example mapping)
	data_R2A->Data1 = cnt_r5++;//ctrl_data.smf_out.SysStateAct;
	data_R2A->Data2 = 2;//ctrl_data.smf_out.FOC_Mode;
	data_R2A->Data3 = 3;//ctrl_data.smf_out.StateFOC;

	// Flush cache so A53 sees updated values
	Xil_DCacheFlushRange((u32)data_R2A, sizeof(struct data_R2A_t));

	// Ensure memory operations complete before IPI
	__asm__ volatile ("dmb ish" ::: "memory");

	// Trigger IPI to A53 to notify new data
	if (XIpiPsu_TriggerIpi(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK) != (u32)XST_SUCCESS) {
		// optional: handle error (e.g., retry or log)
	}
#endif
}

/**
 * Control Task 100ms
 */
void Control_Task_100ms(void)
{

	inverter_temp_update_values();

	/* Rotor Temperature Measurement
	 *
	 * Sensitivity: 24 mV/°C
	 * Note: measurement value <50 °C not valid (=1.2 V)
	 * */
	// if()
	//	T_Rotor = ADC_V * 41.6667f;
	// else()
	//  T_Rotor = 0;


	/* === provide data for CAN communication via R5 === */
	data_R2A_localRPU.Temp_Inv_Phase_1 = Inv_SiC_Temp.T_Sys1_Ph1;
	data_R2A_localRPU.Temp_Inv_Phase_2 = Inv_SiC_Temp.T_Sys1_Ph2;
	data_R2A_localRPU.Temp_Inv_Phase_3 = Inv_SiC_Temp.T_Sys1_Ph3;
	data_R2A_localRPU.Temp_Inv_Phase_4 = 4;
	data_R2A_localRPU.Temp_Inv_Phase_5 = 5;
	data_R2A_localRPU.Temp_Inv_Phase_6 = 6;
	data_R2A_localRPU.Temp_Mot_Phase_1 = 1;
	data_R2A_localRPU.Temp_Mot_Phase_2 = 2;
	data_R2A_localRPU.Temp_Mot_Phase_3 = 3;
	data_R2A_localRPU.Temp_Mot_Phase_4 = 4;
	data_R2A_localRPU.Temp_Mot_Phase_5 = 5;
	data_R2A_localRPU.Temp_Mot_Phase_6 = 6;
//	data_R2A_localRPU.Temp_Mot_Rotor = 1;
	/* === End of provide data for CAN communication === */
}

/**
 * Control Task Idle
 */
void Control_Task_Idle(void)
{

}
