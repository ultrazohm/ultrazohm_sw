/******************************************************************************
* Copyright 2022 Valentin Hoppe
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
#pragma once
#ifndef CIL_INIT_
#define CIL_INIT_
#include "xparameters.h"
#include "../IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
#include "../IP_Cores/uz_pmsm6ph_transformation/uz_pmsm6ph_transformation.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include <stddef.h>

typedef struct uz_CIL_objects_t{
    uz_pmsm_model6ph_dq_t* cil_pmsm; 
    uz_pmsm6ph_transformation_t* cil_transformation;
    uz_inverter_3ph_t* cil_inverter1;
    uz_inverter_3ph_t* cil_inverter2;
    uz_PWM_SS_2L_t* cil_pwm1;
    uz_PWM_SS_2L_t* cil_pwm2;
}uz_CIL_objects_t;

void init_CIL_6phase(uz_CIL_objects_t* cil_objects);
void init_PWM_CIL_6phase(uz_CIL_objects_t* cil_objects);

#endif
