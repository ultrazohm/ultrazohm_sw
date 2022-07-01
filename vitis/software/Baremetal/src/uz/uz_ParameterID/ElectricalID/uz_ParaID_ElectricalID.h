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
#ifndef UZ_PARAID_ELECTRICALID_H
#define UZ_PARAID_ELECTRICALID_H

#include "../../uz_global_configuration.h"
#include <stdbool.h>
#include "../../uz_HAL.h"
#include "ElectricalID_codegen.h"

/**
 * @brief Object definition for uz_ParaID_ElectricalID_t
 * 
 */
typedef struct uz_ParaID_ElectricalID_t{
	ExtY_ElectricalID_t output;
	ExtU_ElectricalID_t input;
	DW_ElectricalID_t rtDW; /* Observable states */
	RT_MODEL_ElectricalID_t modelData;
	RT_MODEL_ElectricalID_t *PtrToModelData;
} uz_ParaID_ElectricalID_t;

/**
 * @brief Initializes the uz_ParaID_ElectricalID_t object
 * 
 * @return uz_ParaID_ElectricalID_t* pointer to object
 */
uz_ParaID_ElectricalID_t* uz_ElectricalID_init(void);

/**
 * @brief steps the ElectricalID state once
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 */
void uz_ElectricalID_step(uz_ParaID_ElectricalID_t *self);

#endif