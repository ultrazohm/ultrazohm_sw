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

/**
 * @brief Object definition for uz_PID_OnlineID_t
 * 
 */
typedef struct uz_PID_OnlineID_t{
	ExtY_OnlineID_t output;
	ExtU_OnlineID_t input;
	DW_OnlineID_t rtDW; /* Observable states */
	RT_MODEL_OnlineID_t modelData;
	RT_MODEL_OnlineID_t *PtrToModelData;
	uz_PID_CleanPsiArray_t* CleanPsiArray;
	uz_PID_InterpMeshGrid_t* InterpMeshGrid;
	uz_PID_AutoRefCurrents_t* AutoRefCurrents;
} uz_PID_OnlineID_t;

/**
 * @brief Initializes the uz_PID_OnlineID_t object
 * 
 * @return uz_PID_OnlineID_t* pointer to object
 */
uz_PID_OnlineID_t* uz_OnlineID_init(void);

/**
 * @brief steps the OnlineID state once
 * 
 * @param self pointer to uz_PID_OnlineID_t object
 */
void uz_OnlineID_step(uz_PID_OnlineID_t *self);

/**
 * @brief This function is cleaning the array storing the measurement values, which always consits of a d-q-current combination a winding temperature and a speed value such as a d-q-flux combination
The function is searching for measuring pairs which are closer than "eta_c" to their neighbors. In this case it is averaging these similar pairs to avoid measuring values containing the same information.
 * 
 * @param self pointer to uz_PID_OnlineID_t object
 */
void uz_OnlineID_CleanPsiArray(uz_PID_OnlineID_t* self);

/**
 * @brief This function is calculating the regular flux maps out of the irregular scatter data array. The outputs is written onto the member FluxMap_Data of the uz_ParameterID_Data_t struct.
 * 
 * @param self pointer to uz_PID_OnlineID_t object
 */
void uz_OnlineID_CalcFluxMaps(uz_PID_OnlineID_t* self);

/**
 * @brief Calls an stateflow which automatically generates reference currents to speed up the measurement of the OnlineID flux maps. This is more like an extra and not needed for the OnlineID to work. 
 * 
 * @param self pointer to uz_PID_OnlineID_t object
 */
void uz_OnlineID_AutoRefCurrents(uz_PID_OnlineID_t* self);

#endif
