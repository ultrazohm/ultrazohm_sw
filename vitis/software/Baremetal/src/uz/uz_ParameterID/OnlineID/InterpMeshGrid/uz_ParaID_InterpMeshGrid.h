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
#ifndef UZ_PARAID_INTERPMESHGRID_H
#define UZ_PARAID_INTERPMESHGRID_H

#include "InterpMeshGrid_codegen.h"

/**
 * @brief object definition for uz_ParaID_InterpMeshGrid_t
 * 
 */
typedef struct {
	ExtY_InterpMeshGrid_t output;
	ExtU_InterpMeshGrid_t input;
	DW_InterpMeshGrid_t rtDW; /* Observable states */
	RT_MODEL_InterpMeshGrid_t modelData;
	RT_MODEL_InterpMeshGrid_t *PtrToModelData;
} uz_ParaID_InterpMeshGrid_t;

/**
 * @brief Initializes the uz_ParaID_InterpMeshGrid_t object
 * 
 * @return uz_ParaID_InterpMeshGrid_t* pointer to object
 */
uz_ParaID_InterpMeshGrid_t* uz_InterpMeshGrid_init(void);

/**
 * @brief steps the InterpolateMeshGrid state once
 * 
 * @param self pointer to object
 */
void uz_InterpMeshGrid(uz_ParaID_InterpMeshGrid_t *self);

#endif
