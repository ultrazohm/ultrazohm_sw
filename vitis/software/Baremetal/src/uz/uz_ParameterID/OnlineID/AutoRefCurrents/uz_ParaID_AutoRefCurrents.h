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
#ifndef UZ_PARAID_AUTOREFCURRENTS_H
#define UZ_PARAID_AUTOREFCURRENTS_H

#include "AutoRefCurrents_codegen.h"

/**
 * @brief object definition for uz_ParaID_AutoRefCurrents_t
 * 
 */
typedef struct uz_ParaID_AutoRefCurrents_t{
	ExtY_AutoRefCurrents_t output;
	ExtU_AutoRefCurrents_t input;
	DW_AutoRefCurrents_t rtDW; /* Observable states */
	RT_MODEL_AutoRefCurrents_t modelData;
	RT_MODEL_AutoRefCurrents_t *PtrToModelData;
} uz_ParaID_AutoRefCurrents_t;

/**
 * @brief Initializes the uz_ParaID_AutoRefCurrents_t object
 * 
 * @return uz_ParaID_AutoRefCurrents_t* pointer to object
 */
uz_ParaID_AutoRefCurrents_t* uz_AutoRefCurrents_init(void);

/**
 * @brief steps the AutoRefCurrent state once
 * 
 * @param self pointer to object
 */
void uz_AutoRefCurrents_step(uz_ParaID_AutoRefCurrents_t *self);

#endif
