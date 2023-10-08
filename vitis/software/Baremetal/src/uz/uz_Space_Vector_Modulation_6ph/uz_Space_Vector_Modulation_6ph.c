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

#define SVM_6PH_MAXIMUM_XY_RELATIVE 0.1f
#define SVM_6PH_MAXIMUM_MODULATION_INDEX (1.0f/sqrtf(3.0f)*0.975f)
#define SECTOR_ANGLE_RAD (2.0f*UZ_PIf/24.0f)

#define MAKRO_HALFf(val) ((val) / 2.0f)
#define MAKRO_INVERT_DUTYCYCLE(val) (1.0f - (val))



static const float inverse_T_tv_all[24][5][5] = {
    {{0.232050808f, -0.866025404f, -3.232050808f, 0.866025404f, 0.000000000f},{0.750000000f, -1.066987298f, 0.750000000f, -1.933012702f, -0.000000000f},{0.750000000f, 0.200961894f, 0.750000000f, 2.799038106f, -0.000000000f},{0.000000000f, 1.732050808f, -0.000000000f, -1.732050808f, -0.000000000f},{-1.732050808f, 0.000000000f, 1.732050808f, -0.000000000f, 1.000000000f}},
    {{-0.232050808f, 0.866025404f, 3.232050808f, -0.866025404f, -0.000000000f},{0.866025404f, -1.500000000f, -0.866025404f, -1.500000000f, -0.000000000f},{0.750000000f, 0.200961894f, 0.750000000f, 2.799038106f, -0.000000000f},{0.116025404f, 1.299038106f, -1.616025404f, -1.299038106f, 0.000000000f},{-1.500000000f, -0.866025404f, -1.500000000f, 0.866025404f, 1.000000000f}},
    {{0.633974596f, -0.633974596f, 2.366025404f, -2.366025404f, 0.000000000f},{1.183012702f, -0.549038106f, 0.316987298f, 2.049038106f, 0.000000000f},{0.549038106f, 0.549038106f, -2.049038106f, -2.049038106f, -0.000000000f},{-0.866025404f, 1.500000000f, 0.866025404f, 1.500000000f, 0.000000000f},{-1.500000000f, -0.866025404f, -1.500000000f, 0.866025404f, 1.000000000f}},
    {{-0.633974596f, 0.633974596f, -2.366025404f, 2.366025404f, 0.000000000f},{1.500000000f, -0.866025404f, 1.500000000f, 0.866025404f, -0.000000000f},{0.549038106f, 0.549038106f, -2.049038106f, -2.049038106f, 0.000000000f},{-0.549038106f, 1.183012702f, 2.049038106f, 0.316987298f, 0.000000000f},{-0.866025404f, -1.500000000f, 0.866025404f, -1.500000000f, 1.000000000f}},
    {{0.866025404f, -0.232050808f, -0.866025404f, 3.232050808f, -0.000000000f},{1.299038106f, 0.116025404f, -1.299038106f, -1.616025404f, 0.000000000f},{0.200961894f, 0.750000000f, 2.799038106f, 0.750000000f, -0.000000000f},{-1.500000000f, 0.866025404f, -1.500000000f, -0.866025404f, -0.000000000f},{-0.866025404f, -1.500000000f, 0.866025404f, -1.500000000f, 1.000000000f}},
    {{-0.866025404f, 0.232050808f, 0.866025404f, -3.232050808f, 0.000000000f},{1.732050808f, -0.000000000f, -1.732050808f, 0.000000000f, 0.000000000f},{0.200961894f, 0.750000000f, 2.799038106f, 0.750000000f, 0.000000000f},{-1.066987298f, 0.750000000f, -1.933012702f, 0.750000000f, 0.000000000f},{0.000000000f, -1.732050808f, 0.000000000f, 1.732050808f, 1.000000000f}},
    {{0.866025404f, 0.232050808f, -0.866025404f, -3.232050808f, 0.000000000f},{1.066987298f, 0.750000000f, 1.933012702f, 0.750000000f, -0.000000000f},{-0.200961894f, 0.750000000f, -2.799038106f, 0.750000000f, 0.000000000f},{-1.732050808f, 0.000000000f, 1.732050808f, -0.000000000f, 0.000000000f},{-0.000000000f, -1.732050808f, 0.000000000f, 1.732050808f, 1.000000000f}},
    {{-0.866025404f, -0.232050808f, 0.866025404f, 3.232050808f, 0.000000000f},{1.500000000f, 0.866025404f, 1.500000000f, -0.866025404f, -0.000000000f},{-0.200961894f, 0.750000000f, -2.799038106f, 0.750000000f, 0.000000000f},{-1.299038106f, 0.116025404f, 1.299038106f, -1.616025404f, 0.000000000f},{0.866025404f, -1.500000000f, -0.866025404f, -1.500000000f, 1.000000000f}},
    {{0.633974596f, 0.633974596f, 2.366025404f, 2.366025404f, 0.000000000f},{0.549038106f, 1.183012702f, -2.049038106f, 0.316987298f, -0.000000000f},{-0.549038106f, 0.549038106f, 2.049038106f, -2.049038106f, -0.000000000f},{-1.500000000f, -0.866025404f, -1.500000000f, 0.866025404f, 0.000000000f},{0.866025404f, -1.500000000f, -0.866025404f, -1.500000000f, 1.000000000f}},
    {{-0.633974596f, -0.633974596f, -2.366025404f, -2.366025404f, -0.000000000f},{0.866025404f, 1.500000000f, -0.866025404f, 1.500000000f, 0.000000000f},{-0.549038106f, 0.549038106f, 2.049038106f, -2.049038106f, 0.000000000f},{-1.183012702f, -0.549038106f, -0.316987298f, 2.049038106f, 0.000000000f},{1.500000000f, -0.866025404f, 1.500000000f, 0.866025404f, 1.000000000f}},
    {{0.232050808f, 0.866025404f, -3.232050808f, -0.866025404f, 0.000000000f},{-0.116025404f, 1.299038106f, 1.616025404f, -1.299038106f, 0.000000000f},{-0.750000000f, 0.200961894f, -0.750000000f, 2.799038106f, 0.000000000f},{-0.866025404f, -1.500000000f, 0.866025404f, -1.500000000f, -0.000000000f},{1.500000000f, -0.866025404f, 1.500000000f, 0.866025404f, 1.000000000f}},
    {{-0.232050808f, -0.866025404f, 3.232050808f, 0.866025404f, 0.000000000f},{0.000000000f, 1.732050808f, -0.000000000f, -1.732050808f, -0.000000000f},{-0.750000000f, 0.200961894f, -0.750000000f, 2.799038106f, 0.000000000f},{-0.750000000f, -1.066987298f, -0.750000000f, -1.933012702f, -0.000000000f},{1.732050808f, 0.000000000f, -1.732050808f, 0.000000000f, 1.000000000f}},
    {{-0.232050808f, 0.866025404f, 3.232050808f, -0.866025404f, 0.000000000f},{-0.750000000f, 1.066987298f, -0.750000000f, 1.933012702f, 0.000000000f},{-0.750000000f, -0.200961894f, -0.750000000f, -2.799038106f, -0.000000000f},{-0.000000000f, -1.732050808f, 0.000000000f, 1.732050808f, 0.000000000f},{1.732050808f, -0.000000000f, -1.732050808f, 0.000000000f, 1.000000000f}},
    {{0.232050808f, -0.866025404f, -3.232050808f, 0.866025404f, -0.000000000f},{-0.866025404f, 1.500000000f, 0.866025404f, 1.500000000f, 0.000000000f},{-0.750000000f, -0.200961894f, -0.750000000f, -2.799038106f, 0.000000000f},{-0.116025404f, -1.299038106f, 1.616025404f, 1.299038106f, -0.000000000f},{1.500000000f, 0.866025404f, 1.500000000f, -0.866025404f, 1.000000000f}},
    {{-0.633974596f, 0.633974596f, -2.366025404f, 2.366025404f, -0.000000000f},{-1.183012702f, 0.549038106f, -0.316987298f, -2.049038106f, 0.000000000f},{-0.549038106f, -0.549038106f, 2.049038106f, 2.049038106f, -0.000000000f},{0.866025404f, -1.500000000f, -0.866025404f, -1.500000000f, 0.000000000f},{1.500000000f, 0.866025404f, 1.500000000f, -0.866025404f, 1.000000000f}},
    {{0.633974596f, -0.633974596f, 2.366025404f, -2.366025404f, 0.000000000f},{-1.500000000f, 0.866025404f, -1.500000000f, -0.866025404f, -0.000000000f},{-0.549038106f, -0.549038106f, 2.049038106f, 2.049038106f, 0.000000000f},{0.549038106f, -1.183012702f, -2.049038106f, -0.316987298f, -0.000000000f},{0.866025404f, 1.500000000f, -0.866025404f, 1.500000000f, 1.000000000f}},
    {{-0.866025404f, 0.232050808f, 0.866025404f, -3.232050808f, 0.000000000f},{-1.299038106f, -0.116025404f, 1.299038106f, 1.616025404f, 0.000000000f},{-0.200961894f, -0.750000000f, -2.799038106f, -0.750000000f, -0.000000000f},{1.500000000f, -0.866025404f, 1.500000000f, 0.866025404f, -0.000000000f},{0.866025404f, 1.500000000f, -0.866025404f, 1.500000000f, 1.000000000f}},
    {{0.866025404f, -0.232050808f, -0.866025404f, 3.232050808f, 0.000000000f},{-1.732050808f, 0.000000000f, 1.732050808f, -0.000000000f, -0.000000000f},{-0.200961894f, -0.750000000f, -2.799038106f, -0.750000000f, -0.000000000f},{1.066987298f, -0.750000000f, 1.933012702f, -0.750000000f, 0.000000000f},{-0.000000000f, 1.732050808f, -0.000000000f, -1.732050808f, 1.000000000f}},
    {{-0.866025404f, -0.232050808f, 0.866025404f, 3.232050808f, 0.000000000f},{-1.066987298f, -0.750000000f, -1.933012702f, -0.750000000f, -0.000000000f},{0.200961894f, -0.750000000f, 2.799038106f, -0.750000000f, 0.000000000f},{1.732050808f, -0.000000000f, -1.732050808f, 0.000000000f, 0.000000000f},{0.000000000f, 1.732050808f, -0.000000000f, -1.732050808f, 1.000000000f}},
    {{0.866025404f, 0.232050808f, -0.866025404f, -3.232050808f, 0.000000000f},{-1.500000000f, -0.866025404f, -1.500000000f, 0.866025404f, 0.000000000f},{0.200961894f, -0.750000000f, 2.799038106f, -0.750000000f, 0.000000000f},{1.299038106f, -0.116025404f, -1.299038106f, 1.616025404f, 0.000000000f},{-0.866025404f, 1.500000000f, 0.866025404f, 1.500000000f, 1.000000000f}},
    {{-0.633974596f, -0.633974596f, -2.366025404f, -2.366025404f, 0.000000000f},{-0.549038106f, -1.183012702f, 2.049038106f, -0.316987298f, -0.000000000f},{0.549038106f, -0.549038106f, -2.049038106f, 2.049038106f, 0.000000000f},{1.500000000f, 0.866025404f, 1.500000000f, -0.866025404f, -0.000000000f},{-0.866025404f, 1.500000000f, 0.866025404f, 1.500000000f, 1.000000000f}},
    {{0.633974596f, 0.633974596f, 2.366025404f, 2.366025404f, -0.000000000f},{-0.866025404f, -1.500000000f, 0.866025404f, -1.500000000f, 0.000000000f},{0.549038106f, -0.549038106f, -2.049038106f, 2.049038106f, -0.000000000f},{1.183012702f, 0.549038106f, 0.316987298f, -2.049038106f, -0.000000000f},{-1.500000000f, 0.866025404f, -1.500000000f, -0.866025404f, 1.000000000f}},
    {{-0.232050808f, -0.866025404f, 3.232050808f, 0.866025404f, 0.000000000f},{0.116025404f, -1.299038106f, -1.616025404f, 1.299038106f, 0.000000000f},{0.750000000f, -0.200961894f, 0.750000000f, -2.799038106f, -0.000000000f},{0.866025404f, 1.500000000f, -0.866025404f, 1.500000000f, -0.000000000f},{-1.500000000f, 0.866025404f, -1.500000000f, -0.866025404f, 1.000000000f}},
    {{0.232050808f, 0.866025404f, -3.232050808f, -0.866025404f, 0.000000000f},{-0.000000000f, -1.732050808f, 0.000000000f, 1.732050808f, -0.000000000f},{0.750000000f, -0.200961894f, 0.750000000f, -2.799038106f, -0.000000000f},{0.750000000f, 1.066987298f, 0.750000000f, 1.933012702f, -0.000000000f},{-1.732050808f, 0.000000000f, 1.732050808f, -0.000000000f, 1.000000000f}}
};

static const int svm_offline_order[24][6] = {
    {4, 0, 5, 1, 2, 3},
    {0, 4, 5, 1, 3, 2},
    {0, 3, 1, 4, 5, 2},
    {3, 0, 1, 4, 2, 5},
    {3, 2, 4, 0, 1, 5},
    {2, 3, 4, 0, 5, 1},
    {2, 5, 0, 3, 4, 1},
    {5, 2, 0, 3, 1, 4},
    {5, 1, 3, 2, 0, 4},
    {1, 5, 3, 2, 4, 0},
    {1, 4, 2, 5, 3, 0},
    {4, 1, 2, 5, 0, 3},
    {4, 0, 5, 1, 2, 3},
    {0, 4, 5, 1, 3, 2},
    {0, 3, 1, 4, 5, 2},
    {3, 0, 1, 4, 2, 5},
    {3, 2, 4, 0, 1, 5},
    {2, 3, 4, 0, 5, 1},
    {2, 5, 0, 3, 4, 1},
    {5, 2, 0, 3, 1, 4},
    {5, 1, 3, 2, 0, 4},
    {1, 5, 3, 2, 4, 0},
    {1, 4, 2, 5, 3, 0},
    {4, 1, 2, 5, 0, 3}
};

static int uz_svm_6ph_get_sector(float alpha, float beta);
static inline float uz_svm_6ph_calculate_dwell_times_2N(uz_6ph_alphabeta_t u_ref_V, const float inverse_T_tv_row[5]);
static inline void uz_svm_6ph_calculate_duty_cycles(float Duty_Cycles[6], float dwell[5], const int order[6]);
static inline void uz_svm_6ph_calculate_and_shift_duty_cycles(float Duty_Cycles[6], int sector, float *shift_system_1, float *shift_system_2);
static uz_6ph_alphabeta_t uz_svm_6ph_overall_limitation(uz_6ph_alphabeta_t input, float maximum_abs, bool *limited_ab, bool *limited_xy);
static inline uz_6ph_alphabeta_t uz_svm_6ph_norm_vdc(uz_6ph_alphabeta_t input, float V_dc);

// "main" 6ph svm function
struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta(uz_6ph_alphabeta_t u_ref_V, float V_dc){
    uz_assert(V_dc > 0.0f);
    struct uz_svm_asym_6ph_CSVPWM24_out out = {0};

    // space vector limitation
    uz_6ph_alphabeta_t u_ref_V_normed = uz_svm_6ph_norm_vdc(u_ref_V, V_dc);
    uz_6ph_alphabeta_t u_ref_V_limited = uz_svm_6ph_overall_limitation(u_ref_V_normed, SVM_6PH_MAXIMUM_MODULATION_INDEX, &out.limited_alphabeta, &out.limited_xy);

    // find sector
    int sector = uz_svm_6ph_get_sector(u_ref_V_limited.alpha, u_ref_V_limited.beta);

    // calculate dwell times
    float dwell_times[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    for(int i=0; i<5; i++){
        dwell_times[i] = uz_svm_6ph_calculate_dwell_times_2N(u_ref_V_limited, &inverse_T_tv_all[sector-1][i][0]);
    }

    // calculate duty cycles from dwell times
    float Duty_Cycles[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    uz_svm_6ph_calculate_duty_cycles(&Duty_Cycles[0], &dwell_times[0], &svm_offline_order[sector-1][0]);

    // order duty cycles and determine shift
    uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles[0], sector, &out.shift_system1, &out.shift_system2);

    // assign duty cycles AFTER SHIFTING
    out.Duty_Cycle.system1.DutyCycle_A = Duty_Cycles[0];
    out.Duty_Cycle.system1.DutyCycle_B = Duty_Cycles[1];
    out.Duty_Cycle.system1.DutyCycle_C = Duty_Cycles[2];
    out.Duty_Cycle.system2.DutyCycle_A = Duty_Cycles[3];
    out.Duty_Cycle.system2.DutyCycle_B = Duty_Cycles[4];
    out.Duty_Cycle.system2.DutyCycle_C = Duty_Cycles[5];

    // return output
    return out;
}

// dq wrapped function
struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_dq(uz_6ph_dq_t u_ref_V, float V_dc, float theta_el){
    struct uz_svm_asym_6ph_CSVPWM24_out out = uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta(uz_transformation_asym30deg_6ph_dq_to_alphabeta(u_ref_V, theta_el), V_dc);
    return out;
}

// get sector of alphabeta setpoint
static int uz_svm_6ph_get_sector(float alpha, float beta){
    uz_complex_cartesian_t sv_setpoint_cartesian = {                                                // convert setpoint to cartesian
        .real = alpha,
        .imag = beta};
    uz_complex_polar_t sv_setpoint_polar = uz_complex_cartesian_to_polar(sv_setpoint_cartesian);    // convert setpoint to polar
    float phase_wrapped = uz_signals_wrap(sv_setpoint_polar.angle, 2.0f*UZ_PIf);                    // warp angle (polar form is -pi to pi and now its 0 to 2pi)
    int sector = (int)(floorf(phase_wrapped / SECTOR_ANGLE_RAD)) + 1;                               // get how often sector angle matches in phase angle, add one to make 1-based and not 0-based
    return sector;
}

// calculate dwell times with setpoint and given row (needs to be called 5 times, for each column once), basically just matrix multiplication
static inline float uz_svm_6ph_calculate_dwell_times_2N(uz_6ph_alphabeta_t u_ref_V, const float inverse_T_tv_row[5]){
    float out = inverse_T_tv_row[0]*u_ref_V.alpha + inverse_T_tv_row[1]*u_ref_V.beta + inverse_T_tv_row[2]*u_ref_V.x + inverse_T_tv_row[3]*u_ref_V.y + inverse_T_tv_row[4];
    return out;
}

// calculate duty cycles from dwell times by using the order
static inline void uz_svm_6ph_calculate_duty_cycles(float Duty_Cycles[6], float dwell[5], const int order[6]){
    Duty_Cycles[order[0]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3] + dwell[2] + dwell[1] + MAKRO_HALFf(dwell[0]);
    Duty_Cycles[order[1]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3] + dwell[2] + dwell[1];
    Duty_Cycles[order[2]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3] + dwell[2];
    Duty_Cycles[order[3]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3];
    Duty_Cycles[order[4]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]);
    Duty_Cycles[order[5]] = MAKRO_HALFf(dwell[4]);
}

// shift pwm and adapt duty cycles depending on sector
static inline void uz_svm_6ph_calculate_and_shift_duty_cycles(float Duty_Cycles[6], int sector, float *shift_system_1, float *shift_system_2){
    switch (sector){
        // shift system 2 and invert its DutyCycles
        case  1:
        case  2:
        case  9:
        case 10:
        case 17:
        case 18:
            *shift_system_1 = 0.0f;
            *shift_system_2 = 0.5f;
            Duty_Cycles[3] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[3]);
            Duty_Cycles[4] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[4]);
            Duty_Cycles[5] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[5]);
            break;
        // shift system 1 and invert its DutyCycles
        case  5:
        case  6:
        case 13:
        case 14:
        case 21:
        case 22:
            *shift_system_1 = 0.5f;
            *shift_system_2 = 0.0f;
            Duty_Cycles[0] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[0]);
            Duty_Cycles[1] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[1]);
            Duty_Cycles[2] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[2]);
            break;
        // shift both systems and invert both DutyCycles
        case  7:
        case  8:
        case 15:
        case 16:
        case 23:
        case 24:
            *shift_system_1 = 0.5f;
            *shift_system_2 = 0.5f;
            Duty_Cycles[0] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[0]);
            Duty_Cycles[1] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[1]);
            Duty_Cycles[2] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[2]);
            Duty_Cycles[3] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[3]);
            Duty_Cycles[4] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[4]);
            Duty_Cycles[5] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[5]);
            break;
        // do nothing, no shift
        default:
        case  3:
        case  4:
        case 11:
        case 12:
        case 19:
        case 20:
            *shift_system_1 = 0.0f;
            *shift_system_2 = 0.0f;
            break;
    }
}

static uz_6ph_alphabeta_t uz_svm_6ph_overall_limitation(uz_6ph_alphabeta_t input, float maximum_abs, bool *limited_ab, bool *limited_xy){
    // init
    uz_6ph_alphabeta_t out = input;                                             // init output with input
    *limited_ab = false;                                                        // init limited false
    *limited_xy = false;                                                        // init limited false
    uz_complex_cartesian_t cartesian_ab = {                                     // write alphabeta in to complex struct
        .real = input.alpha,
        .imag = input.beta};
    uz_complex_cartesian_t cartesian_xy = {                                     // write XY in to complex struct
        .real = input.x,
        .imag = input.y};
    uz_complex_polar_t polar_ab = uz_complex_cartesian_to_polar(cartesian_ab);  // make polar number from complex alphabeta input
    uz_complex_polar_t polar_xy = uz_complex_cartesian_to_polar(cartesian_xy);  // make polar number from complex XY input

    // limit xy relative to alphabeta
    if(polar_xy.abs > SVM_6PH_MAXIMUM_XY_RELATIVE * polar_ab.abs){              // if absolute u_ref_V are too large compared with alphabeta        
        polar_xy.abs = SVM_6PH_MAXIMUM_XY_RELATIVE * polar_ab.abs;              // reduce setpoint
        *limited_xy = true;                                                     // set limited flag
    }

    // check overall limit
    float factor = (polar_ab.abs + polar_xy.abs) / maximum_abs;                 // calculate sum of absolutes to maximum abs relation
    if(factor > 1.0f){                                                          // if factor is greater one
        polar_ab.abs /= factor;                                                 // reduce abs ab by factor
        polar_xy.abs /= factor;                                                 // reduce abs xy by factor
        *limited_ab = true;                                                     // set limited flag
        *limited_xy = true;                                                        
    }

    // calculate back if something was limited
    if(*limited_ab == true){
        cartesian_ab = uz_complex_polar_to_cartesian(polar_ab);                 // calculate back to cartesian
        out.alpha = cartesian_ab.real;                                          // assign back to alphabeta struct
        out.beta = cartesian_ab.imag;
    }
    if(*limited_xy == true){
        cartesian_xy = uz_complex_polar_to_cartesian(polar_xy);                 // calculate back to cartesian
        out.x = cartesian_xy.real;                                              // assign back to alphabeta struct
        out.y = cartesian_xy.imag;
    }

    // return
    return out;                                                                 // return out
}

// norm u_ref_V to Dc voltage
static inline uz_6ph_alphabeta_t uz_svm_6ph_norm_vdc(uz_6ph_alphabeta_t input, float V_dc){
    uz_6ph_alphabeta_t out = {
        .alpha = input.alpha/V_dc,
        .beta = input.beta/V_dc,
        .x = input.x/V_dc,
        .y = input.y/V_dc,
        .z1 = input.z1/V_dc,
        .z2 = input.z2/V_dc};
    return out;
}