/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Valentin Hoppe
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
#include "uz_controller_setpoint_filter.h"

uz_3ph_dq_t uz_signals_IIR_Filter_dq_setpoint(uz_IIR_Filter_t* filter_1, uz_IIR_Filter_t* filter_2, uz_3ph_dq_t setpoint){
    uz_3ph_dq_t out = {
        .d = uz_signals_IIR_Filter_sample(filter_1, setpoint.d),
        .q = uz_signals_IIR_Filter_sample(filter_2, setpoint.q),
        .zero = 0.0f};
    return out;
}