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
#ifndef UZ_PARAID_ONLINEID_H
#define UZ_PARAID_ONLINEID_H

#include "OnlineID_codegen.h"
#include "CleanPsiArray/uz_ParaID_CleanPsiArray.h"
#include "InterpMeshGrid/uz_ParaID_InterpMeshGrid.h"
#include "AutoRefCurrents/uz_ParaID_AutoRefCurrents.h"

/**
 * @brief Object definition for uz_ParaID_OnlineID_t
 * 
 */
typedef struct uz_ParaID_OnlineID_t uz_ParaID_OnlineID_t;

/**
 * @brief Initializes the uz_ParaID_OnlineID_t object
 * 
 * @return uz_ParaID_OnlineID_t* pointer to object
 */
uz_ParaID_OnlineID_t* uz_OnlineID_init(void);

/**
 * @brief steps the OnlineID state once
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 */
void uz_OnlineID_step(uz_ParaID_OnlineID_t *self);

/**
 * @brief This function is cleaning the array storing the measurement values, which always consists of a d-q-current combination a winding temperature and a speed value such as a d-q-flux combination
The function is searching for measuring pairs which are closer than "eta_c" to their neighbors. In this case it is averaging these similar pairs to avoid measuring values containing the same information.
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 */
void uz_OnlineID_CleanPsiArray(uz_ParaID_OnlineID_t* self, uz_ParameterID_Data_t* Data);

/**
 * @brief This function is calculating the regular flux maps out of the irregular scatter data array. The outputs is written onto the member FluxMap_Data of the uz_ParameterID_Data_t struct.
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 */
void uz_OnlineID_CalcFluxMaps(uz_ParaID_OnlineID_t* self, uz_ParameterID_Data_t* Data);

/**
 * @brief Calls an stateflow which automatically generates reference currents to speed up the measurement of the OnlineID flux maps. This is more like an extra and not needed for the OnlineID to work. 
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 */
void uz_OnlineID_AutoRefCurrents_step(uz_ParaID_OnlineID_t* self, uz_ParameterID_Data_t* Data);

/**
 * @brief Sets the config struct for the OnlineID
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param Config configuration struct for OnlineID
 */
void uz_OnlineID_set_Config(uz_ParaID_OnlineID_t *self, uz_ParaID_OnlineIDConfig_t Config);

/**
 * @brief Sets the ActualValues struct for the OnlineID
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param ActualValues struct for the measurement values
 */
void uz_OnlineID_set_ActualValues(uz_ParaID_OnlineID_t *self, uz_ParaID_ActualValues_t ActualValues);

/**
 * @brief Sets the GlobalConfig struct for the OnlineID
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_OnlineID_set_GlobalConfig(uz_ParaID_OnlineID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the ControlFlags struct for the OnlineID
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param ControlFlags pointer to the struct with the enable signals of the ParameterID
 */
void uz_OnlineID_set_ControlFlags(uz_ParaID_OnlineID_t *self, uz_ParaID_ControlFlags_t* ControlFlags);

/**
 * @brief Sets the cleaned_psi_array from the CleanPsiArray state
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param array_pointer pointer to the cleaned array
 */
void uz_OnlineID_set_cleaned_psi_array(uz_ParaID_OnlineID_t *self, float* array_pointer);

/**
 * @brief Sets config struct of the AutoRefCurrents state embedded in the OnlineID state
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param Config configuration struct for the AutoRefCurrents state
 */
void uz_OnlineID_set_AutoRefCurrents_Config(uz_ParaID_OnlineID_t *self, uz_ParaID_AutoRefCurrentsConfig_t Config);

/**
 * @brief Sets the GlobalConfig struct for the AutoRefCurrents state embedded in the OnlineID state
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_OnlineID_set_AutoRefCurrents_GlobalConfig(uz_ParaID_OnlineID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the ControlFlags struct for the AutoRefCurrents state embedded in the OnlineID state
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @param ControlFlags pointer to the struct with the enable signals of the ParameterID
 */
void uz_OnlineID_set_AutoRefCurrents_ControlFlags(uz_ParaID_OnlineID_t *self, uz_ParaID_ControlFlags_t* ControlFlags);

/**
 * @brief Gets the interpolated flux maps from the InterMeshGrid state embedded in the OnlineID state
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @return uz_ParaID_FluxMapsData_t* interpolated flux maps
 */
uz_ParaID_FluxMapsData_t* uz_OnlineID_get_InterpMeshGrid_FluxMapData(uz_ParaID_OnlineID_t *self);

/**
 * @brief Gets the status of the enteredOnlineID flag
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @return true state has been entered
 * @return false state hasn't been entered
 */
bool uz_OnlineID_get_enteredOnlineID(uz_ParaID_OnlineID_t *self);

/**
 * @brief Gets the pointer to the output struct of the OnlineID
 * 
 * @param self pointer to uz_ParaID_OnlineID_t object
 * @return uz_ParaID_OnlineID_output_t* pointer to the output struct
 */
uz_ParaID_OnlineID_output_t* uz_OnlineID_get_output(uz_ParaID_OnlineID_t *self);
#endif
