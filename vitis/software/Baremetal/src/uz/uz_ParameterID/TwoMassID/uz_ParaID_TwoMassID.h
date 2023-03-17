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
#ifndef UZ_PARAID_TWOMASSID_H
#define UZ_PARAID_TWOMASSID_H

#include "TwoMassID_codegen.h"

/**
 * @brief Object definition for uz_ParaID_TwoMassID_t
 * 
 */
typedef struct uz_ParaID_TwoMassID_t uz_ParaID_TwoMassID_t;

/**
 * @brief Initializes the uz_ParaID_TwoMassID_t object
 * 
 * @return uz_ParaID_TwoMassID_t* pointer to object
 */
uz_ParaID_TwoMassID_t* uz_TwoMassID_init(void);

/**
 * @brief steps the TwoMassID state once
 * 
 * @param self pointer to uz_ParaID_TwoMassID_t object
 */
void uz_TwoMassID_step(uz_ParaID_TwoMassID_t *self);

void uz_TwoMassID_set_Config(uz_ParaID_TwoMassID_t *self, uz_ParaID_TwoMassIDConfig_t Config);
void uz_TwoMassID_set_ActualValues(uz_ParaID_TwoMassID_t *self, uz_ParaID_ActualValues_t ActualValues);
void uz_TwoMassID_set_GlobalConfig(uz_ParaID_TwoMassID_t *self, uz_ParaID_GlobalConfig_t GlobalConfig);
void uz_TwoMassID_set_ControlFlags(uz_ParaID_TwoMassID_t *self, uz_ParaID_ControlFlags_t *ControlFlags);

bool uz_TwoMassID_get_enteredTwoMassID(uz_ParaID_TwoMassID_t *self);
bool uz_TwoMassID_get_finishedTwoMassID(uz_ParaID_TwoMassID_t *self);
uz_ParaID_Controller_Parameters_output_t* uz_TwoMassID_get_FOC_output(uz_ParaID_TwoMassID_t *self);
uz_ParaID_TwoMassID_output_t* uz_TwoMassID_get_output(uz_ParaID_TwoMassID_t *self);
#endif
