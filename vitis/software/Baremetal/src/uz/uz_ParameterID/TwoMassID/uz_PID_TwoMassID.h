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
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz_HAL.h"
#include "TwoMassID_codegen.h"

/**
 * @brief Object definition for uz_PID_TwoMassID_t
 * 
 */
typedef struct uz_PID_TwoMassID_t{
	ExtY_TwoMassID_t output;
	ExtU_TwoMassID_t input;
	DW_TwoMassID_t rtDW; /* Observable states */
	RT_MODEL_TwoMassID_t modelData;
	RT_MODEL_TwoMassID_t *PtrToModelData;
} uz_PID_TwoMassID_t;

/**
 * @brief Initializes the uz_PID_TwoMassID_t object
 * 
 * @return uz_PID_TwoMassID_t* pointer to object
 */
uz_PID_TwoMassID_t* uz_TwoMassID_init(void);

/**
 * @brief steps the TwoMassID state once
 * 
 * @param self pointer to uz_PID_TwoMassID_t object
 */
void uz_TwoMassID_step(uz_PID_TwoMassID_t *self);

#endif
