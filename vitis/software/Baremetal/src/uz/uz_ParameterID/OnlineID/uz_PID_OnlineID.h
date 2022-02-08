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
#if UZ_PARAMETERID_ACTIVE > 0U
#include <stdbool.h>
#include "../../uz_HAL.h"
#include "OnlineID_codegen.h"
#include "CleanPsiArray/uz_PID_CleanPsiArray.h"
#include "InterpMeshGrid/uz_PID_InterpMeshGrid.h"
#include "AutoRefCurrents/uz_PID_AutoRefCurrents.h"

typedef struct {
	ExtY_OnlineID_t output;
	ExtU_OnlineID_t input;
	DW_OnlineID_t rtDW; /* Observable states */
	RT_MODEL_OnlineID_t modelData;
	RT_MODEL_OnlineID_t *PtrToModelData;
	uz_PID_CleanPsiArray_t* CleanPsiArray;
	uz_PID_InterpMeshGrid_t* InterpMeshGrid;
	uz_PID_AutoRefCurrents_t* AutoRefCurrents;
} uz_PID_OnlineID_t;

uz_PID_OnlineID_t* uz_OnlineID_init(void);
void uz_OnlineID_step(uz_PID_OnlineID_t *self);
void uz_OnlineID_CleanPsiArray(uz_PID_OnlineID_t* self);
void uz_OnlineID_CalcFluxMaps(uz_PID_OnlineID_t* self);
void uz_OnlineID_AutoRefCurrents(uz_PID_OnlineID_t* self);

#endif