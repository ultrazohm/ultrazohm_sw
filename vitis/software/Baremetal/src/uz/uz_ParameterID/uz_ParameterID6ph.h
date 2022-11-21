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
#ifndef UZ_ParameterID6PH_H
#define UZ_ParameterID6PH_H

#include "../../globalData.h"
#include "uz_ParameterID_data.h"
#include "uz_ParameterID_data_multiphase.h"
#include "../uz_FOC/uz_FOC.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "ControlState/uz_ParaID_ControlState.h"
#include "ElectricalID6ph/uz_ParaID_ElectricalID6ph0.h"

/**
 * @brief Object definition for uz_ParameterID6ph_t
 * 
 */
typedef struct uz_ParameterID6ph_t uz_ParameterID6ph_t;

/**
 * @brief Initializes the uz_ParameterID6ph_t object and its sub-objects
 * 
 * @param Data pointer to uz_ParameterID6ph_Data_t struct
 * @return uz_ParameterID6ph_t* pointer to uz_ParameterID6ph_t object
 */
uz_ParameterID6ph_t* uz_ParameterID6ph_init(uz_ParameterID6ph_Data_t *Data);

/**
 * @brief steps the ParameterID6ph once and updates the output values of the ID-states
 * 
 * @param self pointer to uz_ParameterID6ph_t object
 * @param Data pointer to uz_ParameterID6ph_Data_t struct
 */
void uz_ParameterID6ph_step(uz_ParameterID6ph_t* self, uz_ParameterID6ph_Data_t* Data);

#endif // UZ_ParameterID6ph_H

