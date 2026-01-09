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

#ifndef __control_h__
#define __control_h__

#include "../main.h"
#include "../FOC_CodeGen/FOC_FCF.h"
#include "../FOC_CodeGen/FOC_SCF.h"
#include "../FOC_CodeGen/FOC_SMF.h"

/* public variables */
extern RT_MODEL_FOC_FCF_T *const FOC_FCF_MPtr;
extern RT_MODEL_FOC_SCF_T *const FOC_SCF_MPtr;
extern RT_MODEL_FOC_SMF_T *const FOC_SMF_MPtr;

extern uint8_t Control_FLAG_1ms;
extern uint8_t Control_FLAG_10ms;
extern uint8_t Control_FLAG_100ms;

typedef struct {
	struct {
		real32_T U_DC;                       /* '<Root>/U_DC [V]' */
		real32_T I_phA[6];                   /* '<Root>/I_ph [A]' */
		real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
		real32_T phi_elrad;                  /* '<Root>/phi_el [rad]' */
		real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
		real32_T FOC_Enable;                 /* '<Root>/FOC_Enable' */
		real32_T w_el_Ref_IfStarter;         /* '<Root>/w_el_Ref_IfStarter' */
		real32_T IfStarter_Active;           /* '<Root>/IfStarter_Active' */
	} fcf_in;
	struct {
		real32_T DutyCycles01[6];            /* '<Root>/DutyCycles [0..1]' */
		real32_T I_dq_ActA[4];               /* '<Root>/I_dq_Act [A]' */
		real32_T ModInd[2];                  /* '<Root>/ModInd' */
		real32_T w_elrads;                   /* '<Root>/w_el [rad//s]' */
		real32_T FOC_Error;                  /* '<Root>/FOC_Error' */
	} fcf_out;
	struct {
		real32_T U_DC;                       /* '<Root>/U_DC [V]' */
		real32_T ModInd[2];                  /* '<Root>/ModInd' */
		real32_T w_el_rad_s;                 /* '<Root>/w_el [rad//s]' */
		real32_T I_dq_Act[4];                /* '<Root>/I_dq_Act [A]' */
		real32_T MotTempdegC;                /* '<Root>/MotTemp [degC]' */
		real32_T InvTempdegC;                /* '<Root>/InvTemp [degC]' */
		real32_T EXT_Torque_Request;         /* '<Root>/ExtTorqReq [Nm]' */
		real32_T SPEED_CTRL_Enable;          /* '<Root>/SpeedCtrl_Enable' */
		real32_T ExtTorqLimNm[2];            /* '<Root>/ExtTorqLim [Nm]' */
		real32_T EXT_Speed_Request;          /* '<Root>/ExtSpeedReq [rpm]' */
	} scf_in;
	struct {
		real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
		real32_T TorqueEstNm;                /* '<Root>/TorqueEst [Nm]' */
		real32_T TorqueRefDeratedNm;         /* '<Root>/TorqueRefDerated [Nm]' */
	} scf_out;
	struct {
		real32_T EXT_State_Request;          /* '<Root>/<EXT_State_Request>' */
		real32_T EXT_Torque_Request;         /* '<Root>/<EXT_Torque_Request>' */
		real32_T EXT_Speed_Request;          /* '<Root>/<EXT_Speed_Request>' */
boolean_T FastCtrl_Error;            /* '<Root>/<FastCtrl_Error>' */
	} smf_in;
	struct {
		real32_T SysStateAct;                /* '<Root>/SysStateAct' */
		real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
		real32_T StateFOC;                   /* '<Root>/StateFOC' */
		real32_T FOC_Enable_PWM;             /* '<Root>/FOC_Enable_PWM' */
		real32_T global_reset_errors;        /* '<Root>/global_reset_errors' */
		real32_T SPEED_CTRL_Enable;          /* '<Root>/SPEED_CTRL_Enable' */
	} smf_out;
} ctrl_data_t;

extern ctrl_data_t ctrl_data;

extern struct data_A2R_t data_A2R_localRPU;
extern struct data_R2A_t data_R2A_localRPU;

/* public functions */
void init_control_functions(void);
extern void Control_Task_1ms(void);
extern void Control_Task_10ms(void);
extern void Control_Task_100ms(void);
extern void Control_Task_Idle(void);

#endif /* __control_h__ */
