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

#include "../FluxMapID/uz_PID_FluxMapID_codegen.h"

typedef struct {
	ExtY_FluxMapID_t output;
	ExtU_FluxMapID_t input;
	DW_FluxMapID_t rtDW; /* Observable states */
	RT_MODEL_FluxMapID_t modelData;
	RT_MODEL_FluxMapID_t *PtrToModelData;
} uz_PID_FluxMapID_t;

void uz_PID_FluxMapID_init(uz_PID_FluxMapID_t *self);
void uz_PID_FluxMapID_step(uz_PID_FluxMapID_t *self);
