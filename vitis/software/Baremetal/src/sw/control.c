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

uint8_t OUT_KL15;
uint8_t OUT_PYRO_TRIGGER;
uint8_t OUT_RELAY2_CLOSE;
uint8_t OUT_RELAY3_CLOSE;
uint32_t IN_AXI_GPIO_bit_word;
uint8_t IN_KL_15_PG;
uint8_t IN_IGNITION_SUCCESS;
uint8_t IN_RELAY2_NOT_CLOSED;
uint8_t IN_RELAY3_NOT_CLOSED;

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
	ctrl_data.scf_in.U_DC        = ctrl_data.fcf_in.U_DC;
	ctrl_data.scf_in.ModInd[0]   = ctrl_data.fcf_out.ModInd[0];
	ctrl_data.scf_in.w_el_rad_s  = ctrl_data.fcf_out.w_elrads;
	ctrl_data.scf_in.I_dq_Act[0] = ctrl_data.fcf_out.I_dq_ActA[0];
	ctrl_data.scf_in.I_dq_Act[1] = ctrl_data.fcf_out.I_dq_ActA[1];

	FOC_SCF_MPtr->inputs->U_DC        = ctrl_data.scf_in.U_DC;
	FOC_SCF_MPtr->inputs->ModInd[0]   = ctrl_data.scf_in.ModInd[0];
	FOC_SCF_MPtr->inputs->w_el_rad_s  = ctrl_data.scf_in.w_el_rad_s;
	FOC_SCF_MPtr->inputs->I_dq_Act[0] = ctrl_data.scf_in.I_dq_Act[0];
	FOC_SCF_MPtr->inputs->I_dq_Act[1] = ctrl_data.scf_in.I_dq_Act[1];

	FOC_SCF_step(FOC_SCF_MPtr);

	ctrl_data.scf_out.I_dq_RefA[0]       = FOC_SCF_MPtr->outputs->I_dq_RefA[0];
	ctrl_data.scf_out.I_dq_RefA[1]       = FOC_SCF_MPtr->outputs->I_dq_RefA[1];
	ctrl_data.scf_out.TorqueEstNm        = FOC_SCF_MPtr->outputs->TorqueEstNm;
	ctrl_data.scf_out.TorqueRefDeratedNm = FOC_SCF_MPtr->outputs->TorqueRefDeratedNm;
	/* --- End of Simulink Slow Control Function --- */
}

/**
 * Control Task 10ms
 */
void Control_Task_10ms(void)
{


	/* --- execute Simulink State Machine Function --- */
	ctrl_data.smf_in.FastCtrl_Error = ctrl_data.fcf_out.FOC_Error;

	FOC_SMF_MPtr->inputs->FastCtrl_Error = ctrl_data.smf_in.FastCtrl_Error;

	FOC_SMF_step(FOC_SMF_MPtr);

	ctrl_data.smf_out.SysStateAct = FOC_SMF_MPtr->outputs->SysStateAct;
	ctrl_data.smf_out.FOC_Mode = FOC_SMF_MPtr->outputs->FOC_Mode;
	ctrl_data.smf_out.StateFOC = FOC_SMF_MPtr->outputs->StateFOC;
	ctrl_data.smf_out.FOC_Enable_PWM = FOC_SMF_MPtr->outputs->FOC_Enable_PWM;
	ctrl_data.smf_out.global_reset_errors = FOC_SMF_MPtr->outputs->global_reset_errors;
	ctrl_data.smf_out.SPEED_CTRL_Enable = FOC_SMF_MPtr->outputs->SPEED_CTRL_Enable;

	/* --- End of Simulink State Machine Function --- */
}

/**
 * Control Task 100ms
 */
void Control_Task_100ms(void)
{
	IN_AXI_GPIO_bit_word = uz_get_misc_inputs();
	IN_KL_15_PG          = (IN_AXI_GPIO_bit_word >> 0) & 0x01;
	IN_IGNITION_SUCCESS  = (IN_AXI_GPIO_bit_word >> 1) & 0x01;
	IN_RELAY2_NOT_CLOSED = (IN_AXI_GPIO_bit_word >> 2) & 0x01;
	IN_RELAY3_NOT_CLOSED = (IN_AXI_GPIO_bit_word >> 3) & 0x01;

	uz_set_misc_outputs(OUT_KL15, OUT_PYRO_TRIGGER, OUT_RELAY2_CLOSE, OUT_RELAY3_CLOSE);
}

/**
 * Control Task Idle
 */
void Control_Task_Idle(void)
{

}
