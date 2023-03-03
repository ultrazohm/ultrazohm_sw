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
typedef struct uz_ParaID_InterpMeshGrid_t uz_ParaID_InterpMeshGrid_t;

/**
 * @brief Initializes the uz_ParaID_InterpMeshGrid_t object
 * 
 * @return uz_ParaID_InterpMeshGrid_t* pointer to object
 */
uz_ParaID_InterpMeshGrid_t* uz_InterpMeshGrid_init(void);

/**
 * @brief steps the InterpolateMeshGrid state once
 * 
 * @param self pointer to uz_ParaID_InterpMeshGrid_t object
 */
void uz_InterpMeshGrid_step(uz_ParaID_InterpMeshGrid_t *self);

/**
 * @brief Sets the cleaned psi_array from the CleanPsiArray
 * 
 * @param self pointer to uz_ParaID_InterpMeshGrid_t object
 * @param psi_array_in cleaned array from the CleanPsiArray
 */
void uz_InterpMeshGrid_set_psi_array(uz_ParaID_InterpMeshGrid_t *self, float psi_array_in[600]);

/**
 * @brief Sets the rated current of the machine for the InterpMeshGrid algorithm
 * 
 * @param self pointer to uz_ParaID_InterpMeshGrid_t object
 * @param i_rat rated current of the machine
 */
void uz_InterpMeshGrid_set_i_rat(uz_ParaID_InterpMeshGrid_t *self, float i_rat);

/**
 * @brief Sets the OnlineID output struct for the InterpMeshGrid
 * 
 * @param self pointer to uz_ParaID_InterpMeshGrid_t object
 * @param OnlineID_input output struct of the OnlineID
 */
void uz_InterpMeshGrid_set_OnlineID_output(uz_ParaID_InterpMeshGrid_t *self, uz_ParaID_OnlineID_output_t* OnlineID_input);

/**
 * @brief Gets the inter-&extrapolated FluxMaps
 * 
 * @param self pointer to uz_ParaID_InterpMeshGrid_t object
 * @return uz_ParaID_FluxMapsData_t* pointer to the array
 */
uz_ParaID_FluxMapsData_t* uz_InterpMeshGrid_get_FluxMapData(uz_ParaID_InterpMeshGrid_t *self);


#endif
