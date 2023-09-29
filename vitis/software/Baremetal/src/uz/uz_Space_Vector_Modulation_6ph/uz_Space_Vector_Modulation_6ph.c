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

#define SECTOR_ANGLE_RAD (2.0f*UZ_PIf/24.0f)
#define ANGLE_TOLERANCE 0.01f

#define MAKRO_HALFf(val) ((val) / 2.0f)



static const float inverse_T_tv_all[24][5][5] = {
    {{0.23205f, -0.86603f, -3.23205f, 0.86603f, 0.00000f},{0.75000f, -1.06699f, 0.75000f, -1.93301f, -0.00000f},{0.75000f, 0.20096f, 0.75000f, 2.79904f, -0.00000f},{0.00000f, 1.73205f, -0.00000f, -1.73205f, -0.00000f},{-1.73205f, 0.00000f, 1.73205f, -0.00000f, 1.00000f}},
    {{-0.23205f, 0.86603f, 3.23205f, -0.86603f, -0.00000f},{0.86603f, -1.50000f, -0.86603f, -1.50000f, -0.00000f},{0.75000f, 0.20096f, 0.75000f, 2.79904f, -0.00000f},{0.11603f, 1.29904f, -1.61603f, -1.29904f, 0.00000f},{-1.50000f, -0.86603f, -1.50000f, 0.86603f, 1.00000f}},
    {{0.63397f, -0.63397f, 2.36603f, -2.36603f, 0.00000f},{1.18301f, -0.54904f, 0.31699f, 2.04904f, 0.00000f},{0.54904f, 0.54904f, -2.04904f, -2.04904f, -0.00000f},{-0.86603f, 1.50000f, 0.86603f, 1.50000f, 0.00000f},{-1.50000f, -0.86603f, -1.50000f, 0.86603f, 1.00000f}},
    {{-0.63397f, 0.63397f, -2.36603f, 2.36603f, 0.00000f},{1.50000f, -0.86603f, 1.50000f, 0.86603f, -0.00000f},{0.54904f, 0.54904f, -2.04904f, -2.04904f, 0.00000f},{-0.54904f, 1.18301f, 2.04904f, 0.31699f, 0.00000f},{-0.86603f, -1.50000f, 0.86603f, -1.50000f, 1.00000f}},
    {{0.86603f, -0.23205f, -0.86603f, 3.23205f, -0.00000f},{1.29904f, 0.11603f, -1.29904f, -1.61603f, 0.00000f},{0.20096f, 0.75000f, 2.79904f, 0.75000f, -0.00000f},{-1.50000f, 0.86603f, -1.50000f, -0.86603f, -0.00000f},{-0.86603f, -1.50000f, 0.86603f, -1.50000f, 1.00000f}},
    {{-0.86603f, 0.23205f, 0.86603f, -3.23205f, 0.00000f},{1.73205f, -0.00000f, -1.73205f, 0.00000f, 0.00000f},{0.20096f, 0.75000f, 2.79904f, 0.75000f, 0.00000f},{-1.06699f, 0.75000f, -1.93301f, 0.75000f, 0.00000f},{0.00000f, -1.73205f, 0.00000f, 1.73205f, 1.00000f}},
    {{0.86603f, 0.23205f, -0.86603f, -3.23205f, 0.00000f},{1.06699f, 0.75000f, 1.93301f, 0.75000f, -0.00000f},{-0.20096f, 0.75000f, -2.79904f, 0.75000f, 0.00000f},{-1.73205f, 0.00000f, 1.73205f, -0.00000f, 0.00000f},{-0.00000f, -1.73205f, 0.00000f, 1.73205f, 1.00000f}},
    {{-0.86603f, -0.23205f, 0.86603f, 3.23205f, 0.00000f},{1.50000f, 0.86603f, 1.50000f, -0.86603f, -0.00000f},{-0.20096f, 0.75000f, -2.79904f, 0.75000f, 0.00000f},{-1.29904f, 0.11603f, 1.29904f, -1.61603f, 0.00000f},{0.86603f, -1.50000f, -0.86603f, -1.50000f, 1.00000f}},
    {{0.63397f, 0.63397f, 2.36603f, 2.36603f, 0.00000f},{0.54904f, 1.18301f, -2.04904f, 0.31699f, -0.00000f},{-0.54904f, 0.54904f, 2.04904f, -2.04904f, -0.00000f},{-1.50000f, -0.86603f, -1.50000f, 0.86603f, 0.00000f},{0.86603f, -1.50000f, -0.86603f, -1.50000f, 1.00000f}},
    {{-0.63397f, -0.63397f, -2.36603f, -2.36603f, -0.00000f},{0.86603f, 1.50000f, -0.86603f, 1.50000f, 0.00000f},{-0.54904f, 0.54904f, 2.04904f, -2.04904f, 0.00000f},{-1.18301f, -0.54904f, -0.31699f, 2.04904f, 0.00000f},{1.50000f, -0.86603f, 1.50000f, 0.86603f, 1.00000f}},
    {{0.23205f, 0.86603f, -3.23205f, -0.86603f, 0.00000f},{-0.11603f, 1.29904f, 1.61603f, -1.29904f, 0.00000f},{-0.75000f, 0.20096f, -0.75000f, 2.79904f, 0.00000f},{-0.86603f, -1.50000f, 0.86603f, -1.50000f, -0.00000f},{1.50000f, -0.86603f, 1.50000f, 0.86603f, 1.00000f}},
    {{-0.23205f, -0.86603f, 3.23205f, 0.86603f, 0.00000f},{0.00000f, 1.73205f, -0.00000f, -1.73205f, -0.00000f},{-0.75000f, 0.20096f, -0.75000f, 2.79904f, 0.00000f},{-0.75000f, -1.06699f, -0.75000f, -1.93301f, -0.00000f},{1.73205f, 0.00000f, -1.73205f, 0.00000f, 1.00000f}},
    {{-0.23205f, 0.86603f, 3.23205f, -0.86603f, 0.00000f},{-0.75000f, 1.06699f, -0.75000f, 1.93301f, 0.00000f},{-0.75000f, -0.20096f, -0.75000f, -2.79904f, -0.00000f},{-0.00000f, -1.73205f, 0.00000f, 1.73205f, 0.00000f},{1.73205f, -0.00000f, -1.73205f, 0.00000f, 1.00000f}},
    {{0.23205f, -0.86603f, -3.23205f, 0.86603f, -0.00000f},{-0.86603f, 1.50000f, 0.86603f, 1.50000f, 0.00000f},{-0.75000f, -0.20096f, -0.75000f, -2.79904f, 0.00000f},{-0.11603f, -1.29904f, 1.61603f, 1.29904f, -0.00000f},{1.50000f, 0.86603f, 1.50000f, -0.86603f, 1.00000f}},
    {{-0.63397f, 0.63397f, -2.36603f, 2.36603f, -0.00000f},{-1.18301f, 0.54904f, -0.31699f, -2.04904f, 0.00000f},{-0.54904f, -0.54904f, 2.04904f, 2.04904f, -0.00000f},{0.86603f, -1.50000f, -0.86603f, -1.50000f, 0.00000f},{1.50000f, 0.86603f, 1.50000f, -0.86603f, 1.00000f}},
    {{0.63397f, -0.63397f, 2.36603f, -2.36603f, 0.00000f},{-1.50000f, 0.86603f, -1.50000f, -0.86603f, -0.00000f},{-0.54904f, -0.54904f, 2.04904f, 2.04904f, 0.00000f},{0.54904f, -1.18301f, -2.04904f, -0.31699f, -0.00000f},{0.86603f, 1.50000f, -0.86603f, 1.50000f, 1.00000f}},
    {{-0.86603f, 0.23205f, 0.86603f, -3.23205f, 0.00000f},{-1.29904f, -0.11603f, 1.29904f, 1.61603f, 0.00000f},{-0.20096f, -0.75000f, -2.79904f, -0.75000f, -0.00000f},{1.50000f, -0.86603f, 1.50000f, 0.86603f, -0.00000f},{0.86603f, 1.50000f, -0.86603f, 1.50000f, 1.00000f}},
    {{0.86603f, -0.23205f, -0.86603f, 3.23205f, 0.00000f},{-1.73205f, 0.00000f, 1.73205f, -0.00000f, -0.00000f},{-0.20096f, -0.75000f, -2.79904f, -0.75000f, -0.00000f},{1.06699f, -0.75000f, 1.93301f, -0.75000f, 0.00000f},{-0.00000f, 1.73205f, -0.00000f, -1.73205f, 1.00000f}},
    {{-0.86603f, -0.23205f, 0.86603f, 3.23205f, 0.00000f},{-1.06699f, -0.75000f, -1.93301f, -0.75000f, -0.00000f},{0.20096f, -0.75000f, 2.79904f, -0.75000f, 0.00000f},{1.73205f, -0.00000f, -1.73205f, 0.00000f, 0.00000f},{0.00000f, 1.73205f, -0.00000f, -1.73205f, 1.00000f}},
    {{0.86603f, 0.23205f, -0.86603f, -3.23205f, 0.00000f},{-1.50000f, -0.86603f, -1.50000f, 0.86603f, 0.00000f},{0.20096f, -0.75000f, 2.79904f, -0.75000f, 0.00000f},{1.29904f, -0.11603f, -1.29904f, 1.61603f, 0.00000f},{-0.86603f, 1.50000f, 0.86603f, 1.50000f, 1.00000f}},
    {{-0.63397f, -0.63397f, -2.36603f, -2.36603f, 0.00000f},{-0.54904f, -1.18301f, 2.04904f, -0.31699f, -0.00000f},{0.54904f, -0.54904f, -2.04904f, 2.04904f, 0.00000f},{1.50000f, 0.86603f, 1.50000f, -0.86603f, -0.00000f},{-0.86603f, 1.50000f, 0.86603f, 1.50000f, 1.00000f}},
    {{0.63397f, 0.63397f, 2.36603f, 2.36603f, -0.00000f},{-0.86603f, -1.50000f, 0.86603f, -1.50000f, 0.00000f},{0.54904f, -0.54904f, -2.04904f, 2.04904f, -0.00000f},{1.18301f, 0.54904f, 0.31699f, -2.04904f, -0.00000f},{-1.50000f, 0.86603f, -1.50000f, -0.86603f, 1.00000f}},
    {{-0.23205f, -0.86603f, 3.23205f, 0.86603f, 0.00000f},{0.11603f, -1.29904f, -1.61603f, 1.29904f, 0.00000f},{0.75000f, -0.20096f, 0.75000f, -2.79904f, -0.00000f},{0.86603f, 1.50000f, -0.86603f, 1.50000f, -0.00000f},{-1.50000f, 0.86603f, -1.50000f, -0.86603f, 1.00000f}},
    {{0.23205f, 0.86603f, -3.23205f, -0.86603f, 0.00000f},{-0.00000f, -1.73205f, 0.00000f, 1.73205f, -0.00000f},{0.75000f, -0.20096f, 0.75000f, -2.79904f, -0.00000f},{0.75000f, 1.06699f, 0.75000f, 1.93301f, -0.00000f},{-1.73205f, 0.00000f, 1.73205f, -0.00000f, 1.00000f}}
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
static inline float uz_svm_6ph_calculate_dwell_times_2N(uz_6ph_alphabeta_t setpoints, const float inverse_T_tv_row[5]);
static inline void uz_svm_6ph_calculate_duty_cycles(float Duty_Cycles[6], float dwell[5], const int order[6]);
static inline int uz_svm_6ph_calculate_and_shift_duty_cycles(float Duty_Cycles[6], int sector);

struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24(uz_6ph_alphabeta_t setpoints, float V_dc){
    //space vector limitation


    //find sector
    int sector = uz_svm_6ph_get_sector(setpoints.alpha, setpoints.beta);

    // calculate dwell times
    float dwell_times[5];
    for(int i=0; i<5; i++){
        dwell_times[i] = uz_svm_6ph_calculate_dwell_times_2N(setpoints, &inverse_T_tv_all[sector-1][i][0]);
    }

    // calculate duty cycles from dwell times
    float Duty_Cycles[6];
    uz_svm_6ph_calculate_duty_cycles(&Duty_Cycles[0], &dwell_times[0], &svm_offline_order[sector-1][0]);

    // order duty cycles and determine shift
    int shift_system = uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles[0], sector);

    // assign duty cycles
    struct uz_svm_asym_6ph_CSVPWM24_out out = {
        .Duty_Cycle.system1.DutyCycle_A = Duty_Cycles[0],
        .Duty_Cycle.system1.DutyCycle_B = Duty_Cycles[1],
        .Duty_Cycle.system1.DutyCycle_C = Duty_Cycles[2],
        .Duty_Cycle.system2.DutyCycle_A = Duty_Cycles[3],
        .Duty_Cycle.system2.DutyCycle_B = Duty_Cycles[4],
        .Duty_Cycle.system2.DutyCycle_C = Duty_Cycles[5],
        .shift_system1 = 0.0f,
        .shift_system2 = 0.0f};
    
    // shift phase
    switch (shift_system){
        case 1: out.shift_system1 = 0.5f; break;
        case 2: out.shift_system2 = 0.5f; break;
        default: break;
    }

    // return output
    return out;
}

//array[row][column]


static int uz_svm_6ph_get_sector(float alpha, float beta){
    uz_complex_cartesian_t sv_setpoint_cartesian = {
        .real = alpha,
        .imag = beta};
    uz_complex_polar_t sv_setpoint_polar = uz_complex_cartesian_to_polar(sv_setpoint_cartesian);
    float phase_wrapped = uz_signals_wrap(sv_setpoint_polar.angle, 2.0f*UZ_PIf);
    int sector = (int)(floorf(phase_wrapped / SECTOR_ANGLE_RAD)) + 1;
    return sector;
}

static inline float uz_svm_6ph_calculate_dwell_times_2N(uz_6ph_alphabeta_t setpoints, const float inverse_T_tv_row[5]){
    float out = inverse_T_tv_row[0]*setpoints.alpha + inverse_T_tv_row[1]*setpoints.beta + inverse_T_tv_row[2]*setpoints.x + inverse_T_tv_row[3]*setpoints.y + inverse_T_tv_row[4];
    return out;
}

static inline void uz_svm_6ph_calculate_duty_cycles(float Duty_Cycles[6], float dwell[5], const int order[6]){
    Duty_Cycles[order[0]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3] + dwell[2] + dwell[1] + MAKRO_HALFf(dwell[0]);
    Duty_Cycles[order[1]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3] + dwell[2] + dwell[1];
    Duty_Cycles[order[2]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3] + dwell[2];
    Duty_Cycles[order[3]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]) + dwell[3];
    Duty_Cycles[order[4]] = MAKRO_HALFf(dwell[4]) + MAKRO_HALFf(dwell[0]);
    Duty_Cycles[order[5]] = MAKRO_HALFf(dwell[4]);
}

static inline int uz_svm_6ph_calculate_and_shift_duty_cycles(float Duty_Cycles[6], int sector){
    int system_to_shift = 0;
    switch (sector){
        // shift system 2 and diff system 2 DCs with T_sw
        case  1:
        case  2:
        case  9:
        case 10:
        case 17:
        case 18:
            system_to_shift = 2;
            Duty_Cycles[3] = 1.0f - Duty_Cycles[3];
            Duty_Cycles[4] = 1.0f - Duty_Cycles[4];
            Duty_Cycles[5] = 1.0f - Duty_Cycles[5];
            break;
        // shift system 2 and diff system 2 DCs with T_sw
        case  5:
        case  6:
        case 13:
        case 14:
        case 21:
        case 22:
            system_to_shift = 1;
            Duty_Cycles[0] = 1.0f - Duty_Cycles[0];
            Duty_Cycles[1] = 1.0f - Duty_Cycles[1];
            Duty_Cycles[2] = 1.0f - Duty_Cycles[2];
            break;
        // no shift, but diff both systems DCs with T_sw
        case  7:
        case  8:
        case 15:
        case 16:
        case 23:
        case 24:
            Duty_Cycles[0] = 1.0f - Duty_Cycles[0];
            Duty_Cycles[1] = 1.0f - Duty_Cycles[1];
            Duty_Cycles[2] = 1.0f - Duty_Cycles[2];
            Duty_Cycles[3] = 1.0f - Duty_Cycles[3];
            Duty_Cycles[4] = 1.0f - Duty_Cycles[4];
            Duty_Cycles[5] = 1.0f - Duty_Cycles[5];
            break;
        // do nothing, no shift
        default:
        case  3:
        case  4:
        case 11:
        case 12:
        case 19:
        case 20:
            break;
    }
    return system_to_shift;
}