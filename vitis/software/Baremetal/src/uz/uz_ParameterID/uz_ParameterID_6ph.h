/******************************************************************************
 * Copyright 2022 Valentin Hoppe
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
#ifndef UZ_PARAMETERID_6PH_H
#define UZ_PARAMETERID_6PH_H

#include "../../globalData.h"
#include "uz_ParameterID_data.h"
#include "ControlState/uz_ParaID_ControlState.h"
#include "ElectricalID_6ph/uz_ParaID_ElectricalID_6ph.h"
#include "FluxMapID/uz_ParaID_FluxMapID.h"
#include "FrictionID/uz_ParaID_FrictionID.h"
#include "OnlineID/uz_ParaID_OnlineID.h"
#include "TwoMassID/uz_ParaID_TwoMassID.h"

/**
 * @brief Object definition for uz_ParameterID_6ph_t
 * 
 */
typedef struct uz_ParameterID_6ph_t uz_ParameterID_6ph_t;

/**
 * @brief Initializes the uz_ParameterID_6ph_t object and its sub-objects
 * 
 * @param Data pointer to uz_ParameterID_6ph_Data_t struct
 * @return uz_ParameterID_6ph_t* pointer to uz_ParameterID_6ph_t object
 */
uz_ParameterID_6ph_t* uz_ParameterID_6ph_init(uz_ParameterID_Data_t *Data);

/**
 * @brief steps the ParameterID_6ph once and updates the output values of the ID-states
 * 
 * @param self pointer to uz_ParameterID_6ph_t object
 * @param Data pointer to uz_ParameterID_6ph_Data_t struct
 */
void uz_ParameterID_6ph_step(uz_ParameterID_6ph_t* self, uz_ParameterID_Data_t* Data);

/**
 * @brief updates transmit values/Converts some int-values from the ParameterID_6ph to float and helps to sync the array transmission
 * 
 * @param Data pointer to uz_ParameterID_6ph_Data_t struct
 * @param activeState pointer to float variable of activeState
 * @param FluxMapCounter pointer to float variable of FluxMapCounter
 * @param ArrayCounter pointer to float variable of ArrayCounter
 */
void uz_ParameterID_6ph_update_transmit_values(uz_ParameterID_Data_t* Data, float *activeState, float *FluxMapCounter, float *ArrayCounter);


#endif // UZ_PARAMETERID_6PH_H