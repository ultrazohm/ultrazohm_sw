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
#ifndef UZ_PARAID_FLUXMAPID_H
#define UZ_PARAID_FLUXMAPID_H

#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz_HAL.h"
#include "FluxMapID_codegen.h"

/**
 * @brief Object definition for uz_ParaID_ElectricalID_t
 * 
 */
typedef struct uz_ParaID_FluxMapID_t{
	ExtY_FluxMapID_t output;
	ExtU_FluxMapID_t input;
	DW_FluxMapID_t rtDW; /* Observable states */
	RT_MODEL_FluxMapID_t modelData;
	RT_MODEL_FluxMapID_t *PtrToModelData;
} uz_ParaID_FluxMapID_t;

/**
 * @brief Initializes the uz_ParaID_FluxMapID_t object
 * 
 * @return uz_ParaID_FluxMapID_t* pointer to object
 */
uz_ParaID_FluxMapID_t* uz_FluxMapID_init(void);

/**
 * @brief steps the FluxMapID state once
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 */
void uz_FluxMapID_step(uz_ParaID_FluxMapID_t *self);

#endif
#endif