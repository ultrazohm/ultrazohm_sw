/******************************************************************************
 * Copyright 2025 Andreas Geiger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "control.h"

// --- Simulink model variables ---
RT_MODEL_FOC_FCF_T FOC_FCF_M_;
RT_MODEL_FOC_FCF_T *const FOC_FCF_MPtr = &FOC_FCF_M_;/* Real-time model */
B_FOC_FCF_T FOC_FCF_B;          /* Observable signals */
DW_FOC_FCF_T FOC_FCF_DW;        /* Observable states */
ExtU_FOC_FCF_T FOC_FCF_U;       /* External inputs */
ExtY_FOC_FCF_T FOC_FCF_Y;       /* External outputs */
// ----------------------


void init_control_functions(void)
{
	/* Pack model data into RTM */
	FOC_FCF_MPtr->blockIO = &FOC_FCF_B;
	FOC_FCF_MPtr->dwork = &FOC_FCF_DW;
	FOC_FCF_MPtr->inputs = &FOC_FCF_U;
	FOC_FCF_MPtr->outputs = &FOC_FCF_Y;

	/* Initialize model */
	FOC_FCF_initialize(FOC_FCF_MPtr);

}

