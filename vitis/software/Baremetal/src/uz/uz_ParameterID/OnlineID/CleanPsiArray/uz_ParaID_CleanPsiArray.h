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
#ifndef UZ_PARAID_CLEANPSIARRAY_H
#define UZ_PARAID_CLEANPSIARRAY_H

#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../../uz_HAL.h"
#include "CleanPsiArray_codegen.h"

/**
 * @brief object definition for uz_ParaID_CleanPsiArray_t
 * 
 */
typedef struct {
	ExtY_CleanPsiArray_t output;
	ExtU_CleanPsiArray_t input;
	DW_CleanPsiArray_t rtDW; /* Observable states */
	RT_MODEL_CleanPsiArray_t modelData;
	RT_MODEL_CleanPsiArray_t *PtrToModelData;
} uz_ParaID_CleanPsiArray_t;

/**
 * @brief Initializes the uz_ParaID_CleanPsiArray_t object
 * 
 * @return uz_ParaID_CleanPsiArray_t* pointer to object
 */
uz_ParaID_CleanPsiArray_t* uz_CleanPsiArray_init(void);

/**
 * @brief steps the CleanPsiArray state once
 * 
 * @param self pointer to object
 */
void uz_CleanPsiArray(uz_ParaID_CleanPsiArray_t *self);

#endif
#endif