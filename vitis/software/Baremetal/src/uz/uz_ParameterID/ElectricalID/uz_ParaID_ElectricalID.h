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

#include "ElectricalID_codegen.h"

/**
 * @brief Object definition for uz_ParaID_ElectricalID_t
 * 
 */
typedef struct uz_ParaID_ElectricalID_t uz_ParaID_ElectricalID_t;

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

/**
 * @brief Sets the config struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @param Config configuration struct for ElectricalID
 */
void uz_ElectricalID_set_Config(uz_ParaID_ElectricalID_t *self, uz_ParaID_ElectricalIDConfig_t Config);

/**
 * @brief Sets the ActualValues struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @param ActualValues struct for the measurement values
 */
void uz_ElectricalID_set_ActualValues(uz_ParaID_ElectricalID_t *self, uz_ParaID_ActualValues_t ActualValues);

/**
 * @brief Sets the GlobalConfig struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_ElectricalID_set_GlobalConfig(uz_ParaID_ElectricalID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the ControlFlags struct for the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @param ControlFlags pointer to the struct with the enable signals of the ParameterID
 */
void uz_ElectricalID_set_ControlFlags(uz_ParaID_ElectricalID_t *self, uz_ParaID_ControlFlags_t *ControlFlags);

/**
 * @brief Gets the status of the enteredElectricalID flag
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @return true state has been entered
 * @return false state hasn't been entered
 */
bool uz_ElectricalID_get_enteredElectricalID(uz_ParaID_ElectricalID_t *self);

/**
 * @brief Gets the status of the finishedElectricalID flag
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @return true state has finished
 * @return false state hasn't finished
 */
bool uz_ElectricalID_get_finishedElectricalID(uz_ParaID_ElectricalID_t *self);

/**
 * @brief Gets the pointer to the output controller struct of the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @return uz_ParaID_Controller_Parameters_output_t* pointer to the FOC controller parameters struct
 */
uz_ParaID_Controller_Parameters_output_t* uz_ElectricalID_get_FOC_output(uz_ParaID_ElectricalID_t *self);

/**
 * @brief Gets the pointer to the output struct of the ElectricalID
 * 
 * @param self pointer to uz_ParaID_ElectricalID_t* object
 * @return uz_ParaID_ElectricalID_output_t* pointer to the output struct
 */
uz_ParaID_ElectricalID_output_t* uz_ElectricalID_get_output(uz_ParaID_ElectricalID_t *self);
#endif
