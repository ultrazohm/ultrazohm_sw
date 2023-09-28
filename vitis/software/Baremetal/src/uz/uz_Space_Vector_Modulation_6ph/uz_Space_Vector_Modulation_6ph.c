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
    {{0.23205f, -0.86603f, -3.23205f, 0.86603f, 0.00000f},{0.75000f, -1.06699f, 0.75000f, -1.93301f, 0.00000f},{0.75000f, 0.20096f, 0.75000f, 2.79904f, 0.00000f},{-0.00000f, 1.73205f, 0.00000f, -1.73205f, 0.00000f},{-1.73205f, 0.00000f, 1.73205f, -0.00000f, 1.00000f}},
    {{-0.23205f, 0.86603f, 3.23205f, -0.86603f, -0.00000f},{0.86603f, -1.50000f, -0.86603f, -1.50000f, 0.00000f},{0.86603f, -0.23205f, -0.86603f, 3.23205f, 0.00000f},{0.00000f, 1.73205f, 0.00000f, -1.73205f, -0.00000f},{-1.50000f, -0.86603f, -1.50000f, 0.86603f, 1.00000f}},
    {{0.63397f, -0.63397f, 2.36603f, -2.36603f, 0.00000f},{0.86603f, -0.23205f, -0.86603f, 3.23205f, 0.00000f},{0.86603f, 0.23205f, -0.86603f, -3.23205f, -0.00000f},{-0.86603f, 1.50000f, 0.86603f, 1.50000f, 0.00000f},{-1.50000f, -0.86603f, -1.50000f, 0.86603f, 1.00000f}},
    {{-1.26795f, 1.26795f, -4.73205f, 4.73205f, -0.00000f},{1.50000f, -0.86603f, 1.50000f, 0.86603f, 0.00000f},{1.50000f, -0.40192f, 1.50000f, -5.59808f, 0.00000f},{-1.50000f, 2.13397f, -1.50000f, 3.86603f, -0.00000f},{-0.23205f, -2.13397f, 3.23205f, -3.86603f, 1.00000f}},
    {{1.73205f, -0.46410f, -1.73205f, 6.46410f, -0.00000f},{-0.00000f, 0.46410f, -0.00000f, -6.46410f, -0.00000f},{1.50000f, 0.40192f, 1.50000f, 5.59808f, 0.00000f},{-1.50000f, 0.86603f, -1.50000f, -0.86603f, -0.00000f},{-1.73205f, -1.26795f, 1.73205f, -4.73205f, 1.00000f}},
    {{804490588791352.75000f, -215562603585080.87500f, -804490588791350.87500f, 3002399751580332.00000f, 0.00000f},{0.57094f, 0.31112f, -0.57094f, -4.33333f, 0.00000f},{-402245294395674.62500f, 107781301792540.68750f, 402245294395676.68750f, -1501199875790159.50000f, 0.00781f},{402245294395674.25000f, -107781301792539.37500f, -402245294395676.25000f, 1501199875790162.75000f, -0.01562f},{-804490588791352.75000f, 215562603585079.00000f, 804490588791351.00000f, -3002399751580330.50000f, 0.98438f}},
    {{3215200082385512.50000f, 861510265579673.00000f, -3215200082385523.50000f, -11999290063962368.00000f, 0.06250f},{-1607600041192751.75000f, -430755132789834.81250f, 1607600041192760.25000f, 5999645031981172.00000f, -0.03125f},{1607600041192749.75000f, 430755132789835.56250f, -1607600041192758.25000f, -5999645031981160.00000f, 0.03125f},{2.59585f, 1.15966f, -2.59585f, -16.15193f, 0.00000f},{-3215200082385513.00000f, -861510265579674.87500f, 3215200082385524.00000f, 11999290063962372.00000f, 0.93750f}},
    {{-1501199875790160.50000f, -402245294395673.18750f, 1501199875790165.50000f, 5602554208764964.00000f, 0.00000f},{3.09192f, 1.29258f, -0.09192f, -6.80716f, -0.00000f},{-3.09192f, -0.02463f, 0.09192f, 11.53921f, 0.00000f},{-0.00000f, 0.46410f, 0.00000f, -6.46410f, -0.00000f},{1501199875790160.75000f, 402245294395671.50000f, -1501199875790165.75000f, -5602554208764963.00000f, 1.00000f}},
    {{387202179725593.12500f, 387202179725593.12500f, 1445058207537328.25000f, 1445058207537323.25000f, 0.00000f},{1.08940f, 1.72337f, -0.03239f, 2.33364f, 0.00000f},{-1.08940f, 0.00868f, 0.03239f, -4.06569f, -0.00000f},{-1.08940f, -0.45542f, 0.03239f, 2.39841f, 0.00000f},{-387202179725592.12500f, -387202179725594.43750f, -1445058207537328.25000f, -1445058207537324.00000f, 1.00000f}},
    {{-1.26795f, -1.26795f, -4.73205f, -4.73205f, 0.00000f},{0.86603f, 1.50000f, -0.86603f, 1.50000f, 0.00000f},{-0.86603f, 0.23205f, 0.86603f, -3.23205f, 0.00000f},{-0.86603f, -0.23205f, 0.86603f, 3.23205f, -0.00000f},{2.13397f, -0.23205f, 3.86603f, 3.23205f, 1.00000f}},
    {{0.46410f, 1.73205f, -6.46410f, -1.73205f, 0.00000f},{0.00000f, 1.73205f, -0.00000f, -1.73205f, -0.00000f},{-0.86603f, -0.23205f, 0.86603f, 3.23205f, -0.00000f},{-0.86603f, -1.50000f, 0.86603f, -1.50000f, -0.00000f},{1.26795f, -1.73205f, 4.73205f, 1.73205f, 1.00000f}},
    {{-0.23205f, -0.86603f, 3.23205f, 0.86603f, 0.00000f},{0.00000f, 1.73205f, 0.00000f, -1.73205f, -0.00000f},{-0.75000f, 0.20096f, -0.75000f, 2.79904f, 0.00000f},{-0.75000f, -1.06699f, -0.75000f, -1.93301f, -0.00000f},{1.73205f, -0.00000f, -1.73205f, 0.00000f, 1.00000f}},
    {{-0.23205f, 0.86603f, 3.23205f, -0.86603f, 0.00000f},{-0.75000f, 1.06699f, -0.75000f, 1.93301f, -0.00000f},{-0.75000f, -0.20096f, -0.75000f, -2.79904f, -0.00000f},{-0.00000f, -1.73205f, -0.00000f, 1.73205f, 0.00000f},{1.73205f, 0.00000f, -1.73205f, 0.00000f, 1.00000f}},
    {{0.23205f, -0.86603f, -3.23205f, 0.86603f, -0.00000f},{-0.86603f, 1.50000f, 0.86603f, 1.50000f, 0.00000f},{-0.86603f, 0.23205f, 0.86603f, -3.23205f, 0.00000f},{-0.00000f, -1.73205f, 0.00000f, 1.73205f, -0.00000f},{1.50000f, 0.86603f, 1.50000f, -0.86603f, 1.00000f}},
    {{-0.63397f, 0.63397f, -2.36603f, 2.36603f, 0.00000f},{-0.86603f, 0.23205f, 0.86603f, -3.23205f, 0.00000f},{-0.86603f, -0.23205f, 0.86603f, 3.23205f, 0.00000f},{0.86603f, -1.50000f, -0.86603f, -1.50000f, -0.00000f},{1.50000f, 0.86603f, 1.50000f, -0.86603f, 1.00000f}},
    {{1.26795f, -1.26795f, 4.73205f, -4.73205f, 0.00000f},{-1.50000f, 0.86603f, -1.50000f, -0.86603f, 0.00000f},{-1.50000f, 0.40192f, -1.50000f, 5.59808f, 0.00000f},{1.50000f, -2.13397f, 1.50000f, -3.86603f, 0.00000f},{0.23205f, 2.13397f, -3.23205f, 3.86603f, 1.00000f}},
    {{-1.73205f, 0.46410f, 1.73205f, -6.46410f, 0.00000f},{0.00000f, -0.46410f, 0.00000f, 6.46410f, -0.00000f},{-1.50000f, -0.40192f, -1.50000f, -5.59808f, 0.00000f},{1.50000f, -0.86603f, 1.50000f, 0.86603f, 0.00000f},{1.73205f, 1.26795f, -1.73205f, 4.73205f, 1.00000f}},
    {{-839468440477933.62500f, 224934890697476.00000f, 839468440477932.25000f, -3132938871214259.50000f, 0.04688f},{-0.61365f, -0.29967f, 0.61365f, 4.17391f, -0.00000f},{419734220238965.00000f, -112467445348738.31250f, -419734220238967.31250f, 1566469435607123.00000f, -0.02344f},{-419734220238964.56250f, 112467445348736.87500f, 419734220238966.81250f, -1566469435607126.00000f, 0.01562f},{839468440477933.75000f, -224934890697474.25000f, -839468440477932.25000f, 3132938871214258.00000f, 0.98438f}},
    {{-2661249101739650.50000f, -713079547669186.12500f, 2661249101739658.50000f, 9931916859289408.00000f, 0.06250f},{1330624550869821.25000f, 356539773834591.43750f, -1330624550869828.25000f, -4965958429644693.00000f, -0.03125f},{-1330624550869819.75000f, -356539773834592.37500f, 1330624550869826.75000f, 4965958429644683.00000f, 0.03125f},{-1.85019f, -0.95986f, 1.85019f, 13.36909f, 0.00000f},{2661249101739651.00000f, 713079547669188.00000f, -2661249101739659.00000f, -9931916859289412.00000f, 0.93750f}},
    {{1501199875790160.75000f, 402245294395672.87500f, -1501199875790165.00000f, -5602554208764964.00000f, 0.00000f},{-3.24141f, -1.33264f, 0.24141f, 7.36506f, 0.00000f},{3.24141f, 0.06469f, -0.24141f, -12.09711f, 0.00000f},{0.00000f, -0.46410f, -0.00000f, 6.46410f, 0.00000f},{-1501199875790161.00000f, -402245294395671.18750f, 1501199875790165.25000f, 5602554208764963.00000f, 1.00000f}},
    {{-365003133023422.75000f, -365003133023422.75000f, -1362210237365234.00000f, -1362210237365229.50000f, 0.00000f},{-1.07659f, -1.71057f, 0.08018f, -2.28584f, 0.00000f},{1.07659f, -0.02148f, -0.08018f, 4.01789f, 0.00000f},{1.07659f, 0.44262f, -0.08018f, -2.44621f, 0.00000f},{365003133023421.75000f, 365003133023424.06250f, 1362210237365234.00000f, 1362210237365230.25000f, 1.00000f}},
    {{1.26795f, 1.26795f, 4.73205f, 4.73205f, 0.00000f},{-0.86603f, -1.50000f, 0.86603f, -1.50000f, 0.00000f},{0.86603f, -0.23205f, -0.86603f, 3.23205f, 0.00000f},{0.86603f, 0.23205f, -0.86603f, -3.23205f, 0.00000f},{-2.13397f, 0.23205f, -3.86603f, -3.23205f, 1.00000f}},
    {{-0.46410f, -1.73205f, 6.46410f, 1.73205f, -0.00000f},{-0.00000f, -1.73205f, 0.00000f, 1.73205f, -0.00000f},{0.86603f, 0.23205f, -0.86603f, -3.23205f, 0.00000f},{0.86603f, 1.50000f, -0.86603f, 1.50000f, 0.00000f},{-1.26795f, 1.73205f, -4.73205f, -1.73205f, 1.00000f}},
    {{0.23205f, 0.86603f, -3.23205f, -0.86603f, -0.00000f},{-0.00000f, -1.73205f, -0.00000f, 1.73205f, 0.00000f},{0.75000f, -0.20096f, 0.75000f, -2.79904f, 0.00000f},{0.75000f, 1.06699f, 0.75000f, 1.93301f, 0.00000f},{-1.73205f, 0.00000f, 1.73205f, -0.00000f, 1.00000f}}
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

struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24(uz_6ph_alphabeta_t setpoints, const float T_sw){
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
        // do nothing, no shift
        default:
        case  3:
        case  4:
        case  7:
        case  8:
        case 11:
        case 12:
        case 15:
        case 16:
        case 19:
        case 20:
        case 23:
        case 24:
            break;
    }
    return system_to_shift;
}