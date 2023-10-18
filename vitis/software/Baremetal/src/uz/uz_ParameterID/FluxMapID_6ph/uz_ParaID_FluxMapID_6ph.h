/******************************************************************************
 * Copyright 2023 Valentin Hoppe
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

#ifndef UZ_PARAID_FLUXMAPID_6PH_H
#define UZ_PARAID_FLUXMAPID_6PH_H

#include "../uz_ParameterID_data.h"
#include "../../uz_CurrentControl/uz_CurrentControl.h"
#include "../../uz_ResonantController/uz_resonant_controller.h"
#include "../../uz_math_constants.h"
#include "../../uz_signals/uz_signals.h"
#include <stdio.h>

/**
 * @brief Object definition for uz_ParaID_FluxMapID_6ph_t
 * 
 */
typedef struct uz_ParaID_FluxMapID_6ph_t uz_ParaID_FluxMapID_6ph_t;

/**
 * @brief Initializes the uz_ParaID_FluxMapID_6ph_t object
 * 
 * @return uz_ParaID_FluxMapID_6ph_t pointer to object
 */
uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_init(void);

/**
 * @brief steps the uz_ParaID_FluxMapID_6ph_t state once
 * 
 * @param self pointer to uz_ParaID_FluxMapID_6ph_t object
 */
void uz_FluxMapID_6ph_step(uz_ParaID_FluxMapID_6ph_t* self);

void uz_FluxMapID_6ph_set_Config(uz_ParaID_FluxMapID_6ph_t *self, uz_ParaID_FluxMapIDConfig_t Config);
void uz_FluxMapID_6ph_set_ActualValues(uz_ParaID_FluxMapID_6ph_t *self, uz_ParaID_ActualValues_t ActualValues);
void uz_FluxMapID_6ph_set_GlobalConfig(uz_ParaID_FluxMapID_6ph_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);
void uz_FluxMapID_6ph_set_ControlFlags(uz_ParaID_FluxMapID_6ph_t *self, uz_ParaID_ControlFlags_t* ControlFlags);

/**
 * @brief Gets the status of the enteredFluxMapID flag
 * 
 * @param self pointer to uz_ParaID_FluxMapID_6ph_t object
 * @return true state has been entered
 * @return false state hasn't been entered
 */
bool uz_get_FluxMapID_6ph_entered(uz_ParaID_FluxMapID_6ph_t* self);

/**
 * @brief Gets the status of the finishedFluxMapID flag
 * 
 * @param self pointer to uz_ParaID_FluxMapID_6ph_t object
 * @return true state has finished
 * @return false state hasn't finished
 */
bool uz_get_FluxMapID_6ph_finished(uz_ParaID_FluxMapID_6ph_t* self);

/**
 * @brief Gets the pointer to the output controller struct of the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_6ph_t object
 * @return uz_ParaID_Controller_Parameters_output_t* pointer to the FOC controller parameters struct
 */
uz_ParaID_Controller_Parameters_output_t* uz_get_FluxMapID_6ph_FOCoutput(uz_ParaID_FluxMapID_6ph_t* self);

/**
 * @brief Gets the pointer to the output struct of the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_6ph_t object
 * @return uz_ParaID_FluxMapID_output_t* pointer to the output struct
 */
uz_ParaID_FluxMapID_output_t* uz_get_FluxMapID_6ph_output(uz_ParaID_FluxMapID_6ph_t* self);
#endif // UZ_PARAID_FLUXMAPID_6PH_H
