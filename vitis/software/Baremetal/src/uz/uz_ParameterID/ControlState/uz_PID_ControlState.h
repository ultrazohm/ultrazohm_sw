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
#include "../../uz_HAL.h"
#include <stdbool.h>
#include "ControlState_codegen.h"

typedef struct {
	ExtY_ControlState_t output;
	ExtU_ControlState_t input;
	DW_ControlState_t rtDW; /* Observable states */
	RT_MODEL_ControlState_t modelData;
	RT_MODEL_ControlState_t *PtrToModelData;
} uz_PID_ControlState_t;

uz_PID_ControlState_t* uz_ControlState_init(void);
void uz_ControlState_step(uz_PID_ControlState_t *self);

#endif
