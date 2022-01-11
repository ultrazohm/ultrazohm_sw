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
#include <stdbool.h>
#include "../../../uz_HAL.h"
#include "CleanPsiArray_codegen.h"

typedef struct {
	ExtY_CleanPsiArray_t output;
	ExtU_CleanPsiArray_t input;
	DW_CleanPsiArray_t rtDW; /* Observable states */
	RT_MODEL_CleanPsiArray_t modelData;
	RT_MODEL_CleanPsiArray_t *PtrToModelData;
} uz_PID_CleanPsiArray_t;

uz_PID_CleanPsiArray_t* uz_CleanPsiArray_init(void);
void uz_CleanPsiArray(uz_PID_CleanPsiArray_t *self);
