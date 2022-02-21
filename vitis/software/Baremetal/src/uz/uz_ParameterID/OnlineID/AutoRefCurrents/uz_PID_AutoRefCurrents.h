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
#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U
#include <stdbool.h>
#include "../../../uz_HAL.h"
#include "AutoRefCurrents_codegen.h"

/**
 * @brief object definition for uz_PID_AutoRefCurrents_t
 * 
 */
typedef struct uz_PID_AutoRefCurrents_t{
	ExtY_AutoRefCurrents_t output;
	ExtU_AutoRefCurrents_t input;
	DW_AutoRefCurrents_t rtDW; /* Observable states */
	RT_MODEL_AutoRefCurrents_t modelData;
	RT_MODEL_AutoRefCurrents_t *PtrToModelData;
} uz_PID_AutoRefCurrents_t;
/**
 * @brief Initializes the uz_PID_AutoRefCurrents_t object
 * 
 * @return uz_PID_AutoRefCurrents_t* pointer to object
 */
uz_PID_AutoRefCurrents_t* uz_AutoRefCurrents_init(void);

/**
 * @brief steps the AutoRefCurrent state once
 * 
 * @param self pointer to object
 */
void uz_AutoRefCurrents_step(uz_PID_AutoRefCurrents_t *self);

#endif
