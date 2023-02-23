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

//Inputs
void uz_ControlState_set_finishedFrictionID(uz_ParaID_ControlState_t *self, bool is_finished);
void uz_ControlState_set_finishedElectricalID(uz_ParaID_ControlState_t *self, bool is_finished);
void uz_ControlState_set_finishedTwoMassID(uz_ParaID_ControlState_t *self, bool is_finished);
void uz_ControlState_set_finishedFluxMapID(uz_ParaID_ControlState_t *self, bool is_finished);
void uz_ControlState_set_enteredFrictionID(uz_ParaID_ControlState_t *self, bool did_enter);
void uz_ControlState_set_enteredFluxMapID(uz_ParaID_ControlState_t *self, bool did_enter);
void uz_ControlState_set_enteredTwoMassID(uz_ParaID_ControlState_t *self, bool did_enter);
void uz_ControlState_set_enteredElectricalID(uz_ParaID_ControlState_t *self, bool did_enter);
void uz_ControlState_set_enteredOnlineID(uz_ParaID_ControlState_t *self, bool did_enter);
void uz_ControlState_set_ElectricalID_output(uz_ParaID_ControlState_t *self, uz_ParaID_ElectricalID_output_t* ElectricalID_output);
void uz_ControlState_set_GlobalConfig(uz_ParaID_ControlState_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);
void uz_ControlState_set_ElectricalID_FOC_output(uz_ParaID_ControlState_t *self, uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output);

//Outputs
uz_ParaID_GlobalConfig_t* uz_ControlState_get_GlobalConfig(uz_ParaID_ControlState_t *self);
uz_ParaID_ControlFlags_t* uz_ControlState_get_ControlFlags(uz_ParaID_ControlState_t *self);



#endif
