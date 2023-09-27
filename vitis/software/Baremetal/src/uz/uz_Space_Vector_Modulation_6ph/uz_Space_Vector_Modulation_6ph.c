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

#include "uz_Space_Vector_Modulation_6ph.h"
#include "../uz_HAL.h"
#include "../uz_complex/uz_complex.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_math_constants.h"

#define SECTOR_ANGLE_RAD 2.0f*UZ_PIf/24.0f
#define ANGLE_TOLERANCE 0.01f

void SVM_6ph(uz_6ph_alphabeta_t setpoints){
//space vector limitation
//find sector
//get dwell times or even DCs

}


static int uz_svm_6ph_get_sector(float alpha, float beta){
    uz_complex_cartesian_t sv_setpoint_cartesian = {
        .real = alpha,
        .imag = beta};
    uz_complex_polar_t sv_setpoint_polar = uz_complex_cartesian_to_polar(sv_setpoint_cartesian);
    float phase_wrapped = uz_signals_wrap(sv_setpoint_polar.angle, 2.0f*UZ_PIf);
    int sector = (int)(floorf(phase_wrapped / SECTOR_ANGLE_RAD)) + 1;
    return sector;
}

static void uz_svm_6ph_calculate_dwell_times(int sector, uz_6ph_alphabeta_t setpoints){
    // create LUT before impl
}