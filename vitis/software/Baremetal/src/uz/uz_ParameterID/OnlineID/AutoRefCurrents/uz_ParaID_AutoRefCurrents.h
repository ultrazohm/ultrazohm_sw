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
typedef struct uz_ParaID_AutoRefCurrents_t uz_ParaID_AutoRefCurrents_t;

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

/**
 * @brief Sets the config struct for the AutoRefCurrents
 * 
 * @param self pointer to uz_ParaID_AutoRefCurrents_t object
 * @param Config configuration struct for AutoRefCurrents
 */
void uz_AutoRefCurrents_set_Config(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_AutoRefCurrentsConfig_t Config);

/**
 * @brief Sets the ActualValues struct for the AutoRefCurrents
 * 
 * @param self pointer to uz_ParaID_AutoRefCurrents_t object
 * @param ActualValues struct for the measurement values
 */
void uz_AutoRefCurrents_set_ActualValues(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_ActualValues_t ActualValues);

/**
 * @brief Sets the GlobalConfig struct for the AutoRefCurrents
 * 
 * @param self pointer to uz_ParaID_AutoRefCurrents_t object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_AutoRefCurrents_set_GlobalConfig(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the ControlFlags struct for the AutoRefCurrents
 * 
 * @param self pointer to uz_ParaID_AutoRefCurrents_t object
 * @param ControlFlags pointer to the struct with the enable signals of the ParameterID
 */
void uz_AutoRefCurrents_set_ControlFlags(uz_ParaID_AutoRefCurrents_t *self, uz_ParaID_ControlFlags_t* ControlFlags);

/**
 * @brief Gets the pointer to the output struct of the AutoRefCurrents
 * 
 * @param self pointer to uz_ParaID_AutoRefCurrents_t object
 * @return uz_ParaID_AutoRefCurrents_output_t* pointer to the output struct
 */
uz_ParaID_AutoRefCurrents_output_t* uz_AutoRefCurrents_get_output(uz_ParaID_AutoRefCurrents_t *self);
#endif
