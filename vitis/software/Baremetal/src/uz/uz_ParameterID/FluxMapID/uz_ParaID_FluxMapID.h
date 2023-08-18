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

#include "FluxMapID_codegen.h"

/**
 * @brief Object definition for uz_ParaID_FluxMapID_t
 * 
 */
typedef struct uz_ParaID_FluxMapID_t uz_ParaID_FluxMapID_t;

/**
 * @brief Initializes the uz_ParaID_FluxMapID_t object
 * 
 * @return uz_ParaID_FluxMapID_t pointer to object
 */
uz_ParaID_FluxMapID_t* uz_FluxMapID_init(void);

/**
 * @brief steps the FluxMapID state once
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 */
void uz_FluxMapID_step(uz_ParaID_FluxMapID_t *self);

/**
 * @brief Sets the config struct for the FluxMapID
 * 
 * @param self uz_ParaID_FluxMapID_t pointer to object
 * @param Config configuration struct for the FluxMapID
 */
void uz_FluxMapID_set_Config(uz_ParaID_FluxMapID_t *self, uz_ParaID_FluxMapIDConfig_t Config);

/**
 * @brief Sets the ActualValues struct for the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @param ActualValues struct for the measurement values
 */
void uz_FluxMapID_set_ActualValues(uz_ParaID_FluxMapID_t *self, uz_ParaID_ActualValues_t ActualValues);

/**
 * @brief Sets the GlobalConfig struct for the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_FluxMapID_set_GlobalConfig(uz_ParaID_FluxMapID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the ControlFlags struct for the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @param ControlFlags pointer to the struct with the enable signals of the ParameterID
 */
void uz_FluxMapID_set_ControlFlags(uz_ParaID_FluxMapID_t *self, uz_ParaID_ControlFlags_t *ControlFlags);

/**
 * @brief Gets the status of the enteredFluxMapID flag
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @return true state has been entered
 * @return false state hasn't been entered
 */
bool uz_FluxMapID_get_enteredFluxMapID(uz_ParaID_FluxMapID_t *self);

/**
 * @brief Gets the status of the finishedFluxMapID flag
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @return true state has finished
 * @return false state hasn't finished
 */
bool uz_FluxMapID_get_finishedFluxMapID(uz_ParaID_FluxMapID_t *self);

/**
 * @brief Gets the pointer to the output controller struct of the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @return uz_ParaID_Controller_Parameters_output_t* pointer to the FOC controller parameters struct
 */
uz_ParaID_Controller_Parameters_output_t* uz_FluxMapID_get_FOC_output(uz_ParaID_FluxMapID_t *self);

/**
 * @brief Gets the pointer to the output struct of the FluxMapID
 * 
 * @param self pointer to uz_ParaID_FluxMapID_t object
 * @return uz_ParaID_FluxMapID_output_t* pointer to the output struct
 */
uz_ParaID_FluxMapID_output_t* uz_FluxMapID_get_output(uz_ParaID_FluxMapID_t *self);
#endif
