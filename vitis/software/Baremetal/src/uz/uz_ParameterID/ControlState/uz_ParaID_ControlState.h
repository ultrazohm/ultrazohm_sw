/******************************************************************************
 * Copyright 2021 Dennis Hufnagel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#ifndef UZ_PARAID_CONTROLSTATE_H
#define UZ_PARAID_CONTROLSTATE_H

#include "ControlState_codegen.h"

/**
 * @brief Object definition for uz_ParaID_ControlState_t
 *
 */
typedef struct uz_ParaID_ControlState_t{
	ExtY_ControlState_t output;
	ExtU_ControlState_t input;
	DW_ControlState_t rtDW; /* Observable states */
	RT_MODEL_ControlState_t modelData;
	RT_MODEL_ControlState_t *PtrToModelData;
} uz_ParaID_ControlState_t;

/**
 * @brief Initializes the uz_ParaID_ControlState_t object
 *
 * @return uz_ParaID_ControlState_t* pointer to object
 */
uz_ParaID_ControlState_t* uz_ControlState_init(void);

/**
 * @brief steps the uz_ParaID_ControlState_t state once
 *
 * @param self pointer to uz_ParaID_ControlState_t* object
 */
void uz_ControlState_step(uz_ParaID_ControlState_t *self);

#endif
