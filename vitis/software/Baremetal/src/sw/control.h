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

/* public variables */
extern RT_MODEL_FOC_FCF_T *const FOC_FCF_MPtr;

extern uint8_t Control_FLAG_1ms;
extern uint8_t Control_FLAG_10ms;
extern uint8_t Control_FLAG_100ms;


/* public functions */
void init_control_functions(void);
extern void Control_Task_1ms(void);
extern void Control_Task_10ms(void);
extern void Control_Task_100ms(void);
extern void Control_Task_Idle(void);

#endif /* __control_h__ */
