/******************************************************************************
 * Copyright 2022 Valentin Hoppe
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
#ifndef UZ_PARAID_ELECTRICALID6PH_H
#define UZ_PARAID_ELECTRICALID6PH_H

#include "ElectricalID6ph0.h"

/**
 * @brief Object definition for uz_ParaID_ElectricalID6ph_t
 * 
 */
typedef struct uz_ParaID_ElectricalID6ph_t{
	ExtY_ElectricalID6ph0_t output;
	ExtU_ElectricalID6ph0_t input;
	DW_ElectricalID6ph0_t rtDW; /* Observable states */
	RT_MODEL_ElectricalID6ph0_t modelData;
	RT_MODEL_ElectricalID6ph0_t *PtrToModelData;
} uz_ParaID_ElectricalID6ph_t;

/**
 * @brief Initializes the uz_ParaID_ElectricalID6ph_t object
 * 
 * @return uz_ParaID_ElectricalID6ph_t* pointer to object
 */
uz_ParaID_ElectricalID6ph_t* uz_ElectricalID6ph_init(void);

/**
 * @brief steps the ElectricalID6ph state once
 * 
 * @param self pointer to uz_ParaID_ElectricalID6ph_t* object
 */
void uz_ElectricalID6ph_step(uz_ParaID_ElectricalID6ph_t *self);

#endif
