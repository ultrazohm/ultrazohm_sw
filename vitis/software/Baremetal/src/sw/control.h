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
	bus_FCF_t bus_FCF;                   /* '<Root>/bus_FCF' */
	bus_BSW_FCF_t bus_BSW_FCF;           /* '<Root>/bus_BSW_FCF' */
	bus_SCF_t bus_SCF;                   /* '<Root>/bus_SCF' */
	bus_SMF_t bus_SMF;                   /* '<Root>/bus_SMF' */
	bus_BSW_SMF_t bus_BSW_SMF;           /* '<Root>/bus_BSW_SCF' */
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
