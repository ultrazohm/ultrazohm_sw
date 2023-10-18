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
#ifndef UZ_PARAID_FRICTIONID_H
#define UZ_PARAID_FRICTIONID_H

#include "FrictionID_codegen.h"

/**
 * @brief Object definition for uz_ParaID_FrictionID_t
 * 
 */
typedef struct uz_ParaID_FrictionID_t uz_ParaID_FrictionID_t;

/**
 * @brief Initializes the uz_ParaID_FrictionID_t object
 * 
 * @return uz_ParaID_FrictionID_t* pointer to object
 */
uz_ParaID_FrictionID_t* uz_FrictionID_init(void);

/**
 * @brief steps the FrictionID state once
 * 
 * @param self pointer to uz_ParaID_FrictionID_t object
 */
void uz_FrictionID_step(uz_ParaID_FrictionID_t *self);

void uz_FrictionID_set_Config(uz_ParaID_FrictionID_t *self, uz_ParaID_FrictionIDConfig_t Config);
void uz_FrictionID_set_ActualValues(uz_ParaID_FrictionID_t *self, uz_ParaID_ActualValues_t ActualValues);
void uz_FrictionID_set_GlobalConfig(uz_ParaID_FrictionID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);
void uz_FrictionID_set_ControlFlags(uz_ParaID_FrictionID_t *self, uz_ParaID_ControlFlags_t *ControlFlags);

bool uz_FrictionID_get_enteredFrictionID(uz_ParaID_FrictionID_t *self);
bool uz_FrictionID_get_finishedFrictionID(uz_ParaID_FrictionID_t *self);
uz_ParaID_Controller_Parameters_output_t* uz_FrictionID_get_FOC_output(uz_ParaID_FrictionID_t *self);
uz_ParaID_FrictionID_output_t* uz_FrictionID_get_output(uz_ParaID_FrictionID_t *self);
#endif
