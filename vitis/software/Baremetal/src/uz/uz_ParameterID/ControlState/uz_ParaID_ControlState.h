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
typedef struct uz_ParaID_ControlState_t uz_ParaID_ControlState_t;

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

/**
 * @brief Sets the finishedFrictionID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param is_finished flag to signal, that the FrictionID state has finished
 */
void uz_ControlState_set_finishedFrictionID(uz_ParaID_ControlState_t *self, bool is_finished);

/**
 * @brief Sets the finishedElectricalID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param is_finished flag to signal, that the ElectricalID state has finished
 */
void uz_ControlState_set_finishedElectricalID(uz_ParaID_ControlState_t *self, bool is_finished);

/**
 * @brief Sets the finishedTwoMassID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param is_finished flag to signal, that the TwoMassID state has finished
 */
void uz_ControlState_set_finishedTwoMassID(uz_ParaID_ControlState_t *self, bool is_finished);

/**
 * @brief Sets the finishedFluxMapID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param is_finished flag to signal, that the FluxMapID state has finished
 */
void uz_ControlState_set_finishedFluxMapID(uz_ParaID_ControlState_t *self, bool is_finished);

/**
 * @brief Sets the enteredFrictionID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param did_enter flag to signal, that the FrictionID state has been entered
 */
void uz_ControlState_set_enteredFrictionID(uz_ParaID_ControlState_t *self, bool did_enter);

/**
 * @brief Sets the enteredFluxMapID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param did_enter flag to signal, that the FluxMapID state has been entered
 */
void uz_ControlState_set_enteredFluxMapID(uz_ParaID_ControlState_t *self, bool did_enter);

/**
 * @brief Sets the enteredTwoMassID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param did_enter flag to signal, that the TwoMassID state has been entered
 */
void uz_ControlState_set_enteredTwoMassID(uz_ParaID_ControlState_t *self, bool did_enter);

/**
 * @brief Sets the enteredElectricalID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param did_enter flag to signal, that the ElectricalID state has been entered
 */
void uz_ControlState_set_enteredElectricalID(uz_ParaID_ControlState_t *self, bool did_enter);

/**
 * @brief Sets the enteredOnlineID flag for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param did_enter flag to signal, that the OnlineID state has been entered
 */
void uz_ControlState_set_enteredOnlineID(uz_ParaID_ControlState_t *self, bool did_enter);

/**
 * @brief Sets the output struct of the ElectricalID for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param ElectricalID_output pointer to the output struct of the ElectricalID
 */
void uz_ControlState_set_ElectricalID_output(uz_ParaID_ControlState_t *self, uz_ParaID_ElectricalID_output_t* ElectricalID_output);

/**
 * @brief Sets the GlobalConfig struct of the ParameterID for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param GlobalConfig struct for the general settings of the ParameterID
 */
void uz_ControlState_set_GlobalConfig(uz_ParaID_ControlState_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);

/**
 * @brief Sets the Controller Parameters of the ElectricalID state for the ControlState
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @param ElectricalID_FOC_output struct for the ElectricalID controller parameters output struct
 */
void uz_ControlState_set_ElectricalID_FOC_output(uz_ParaID_ControlState_t *self, uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output);

/**
 * @brief Gets the GlobalConfig struct of the ControlState. This struct should be given to every ID-state
 * 
 * @param self pointer to uz_ParaID_ControlState_t* object
 * @return uz_ParaID_GlobalConfig_t* pointer to the struct
 */
uz_ParaID_GlobalConfig_t* uz_ControlState_get_GlobalConfig(uz_ParaID_ControlState_t *self);

/**
 * @brief Gets the ControlFlags struct. This struct should be given to every ID-state
 * 
 * @param self struct for the general settings of the ParameterID
 * @return uz_ParaID_ControlFlags_t* pointer to the struct
 */
uz_ParaID_ControlFlags_t* uz_ControlState_get_ControlFlags(uz_ParaID_ControlState_t *self);



#endif
