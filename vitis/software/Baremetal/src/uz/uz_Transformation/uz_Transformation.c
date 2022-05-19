/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2021 Dennis Hufnagel
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

#include "uz_Transformation.h"
#include "../uz_HAL.h"
#include <math.h>

// not declared as static because tests showed better performance without static declaration
float uz_9ph_arraymul(int line, float const matrixval[9][9], float const val[9]);

// abc -> dq & reverse
uz_3ph_dq_t uz_transformation_3ph_abc_to_dq(uz_3ph_abc_t input, float theta_el_rad)
{
    uz_3ph_alphabeta_t ab = uz_transformation_3ph_abc_to_alphabeta(input);
    uz_3ph_dq_t output= uz_transformation_3ph_alphabeta_to_dq(ab,theta_el_rad);
    return (output);
}

uz_3ph_abc_t uz_transformation_3ph_dq_to_abc(uz_3ph_dq_t input, float theta_el_rad)
{
    uz_3ph_alphabeta_t ab = uz_transformation_3ph_dq_to_alphabeta(input,theta_el_rad);
    uz_3ph_abc_t output = uz_transformation_3ph_alphabeta_to_abc(ab);
    return (output);
}

// abc -> alphabeta & reverse
uz_3ph_alphabeta_t uz_transformation_3ph_abc_to_alphabeta(uz_3ph_abc_t input)
{
    uz_3ph_alphabeta_t output = {
        .alpha = (2.0f / 3.0f) * (input.a - (input.b / 2.0f) - (input.c / 2.0f)),
        .beta = (2.0f / 3.0f) * ((input.b * (sqrtf(3.0f) / 2.0f)) - (input.c * (sqrtf(3.0f) / 2.0f))),
        .gamma = (1.0f / 3.0f) * (input.a + input.b + input.c)};
    return (output);
}

uz_3ph_abc_t uz_transformation_3ph_alphabeta_to_abc(uz_3ph_alphabeta_t input)
{
    uz_3ph_abc_t output = {
        .a = input.alpha + input.gamma,
        .b = (input.alpha * (-1.0f / 2.0f)) + (input.beta * (sqrtf(3.0f) / 2.0f)) + input.gamma,
        .c = (input.alpha * (-1.0f / 2.0f)) + (input.beta * (-sqrtf(3.0f) / 2.0f)) + input.gamma};
    return (output);
}

// alphabeta -> dq & reverse
uz_3ph_dq_t uz_transformation_3ph_alphabeta_to_dq(uz_3ph_alphabeta_t input, float theta_el_rad)
{
    float sin_coefficient = sinf(theta_el_rad);
    float cos_coefficient = cosf(theta_el_rad);
    uz_3ph_dq_t output = {
        .d = (cos_coefficient * input.alpha) + (sin_coefficient * input.beta),
        .q = (-sin_coefficient * input.alpha) + (cos_coefficient * input.beta),
        .zero = input.gamma};
    return output;
}

uz_3ph_alphabeta_t uz_transformation_3ph_dq_to_alphabeta(uz_3ph_dq_t input, float theta_el_rad)
{
    float sin_coefficient = sinf(theta_el_rad);
    float cos_coefficient = cosf(theta_el_rad);
    uz_3ph_alphabeta_t ab = {
        .alpha = (cos_coefficient * input.d) - (sin_coefficient * input.q),
        .beta = (sin_coefficient * input.d) + (cos_coefficient * input.q),
        .gamma = input.zero};
    return ab;
}


// 9 phase
uz_9ph_alphabeta_t uz_transformation_9ph_abc_to_alphabeta(uz_9ph_abc_t input)
{
    uz_9ph_alphabeta_t output = {0};
    float val[9] = {0};

    // VSD matrix from Matlab script, see Docs
    float const vsd_mat[9][9] =
        {
            {0.2222222f, -0.1111111f, -0.1111111f, 0.2088206f, -0.1702321f, -0.0385885f, 0.1702321f, -0.2088206f, 0.0385885f},
            {0.0000000f, 0.1924501f, -0.1924501f, 0.0760045f, 0.1428417f, -0.2188462f, 0.1428417f, 0.0760045f, -0.2188462f},
            {0.2222222f, 0.2222222f, 0.2222222f, 0.1111111f, 0.1111111f, 0.1111111f, -0.1111111f, -0.1111111f, -0.1111111f},
            {0.0000000f, -0.0000000f, -0.0000000f, 0.1924501f, 0.1924501f, 0.1924501f, 0.1924501f, 0.1924501f, 0.1924501f},
            {0.2222222f, -0.1111111f, -0.1111111f, -0.0385885f, 0.2088206f, -0.1702321f, -0.2088206f, 0.0385885f, 0.1702321f},
            {0.0000000f, -0.1924501f, 0.1924501f, 0.2188462f, -0.0760045f, -0.1428417f, -0.0760045f, 0.2188462f, -0.1428417f},
            {0.2222222f, -0.1111111f, -0.1111111f, -0.1702321f, -0.0385885f, 0.2088206f, 0.0385885f, 0.1702321f, -0.2088206f},
            {0.0000000f, 0.1924501f, -0.1924501f, 0.1428417f, -0.2188462f, 0.0760045f, -0.2188462f, 0.1428417f, 0.0760045f},
            {0.1111111f, 0.1111111f, 0.1111111f, -0.1111111f, -0.1111111f, -0.1111111f, 0.1111111f, 0.1111111f, 0.1111111f}};

    // write values of abc struct to array for easier usage
    val[0] = input.a1;
    val[1] = input.b1;
    val[2] = input.c1;
    val[3] = input.a2;
    val[4] = input.b2;
    val[5] = input.c2;
    val[6] = input.a3;
    val[7] = input.b3;
    val[8] = input.c3;

    // apply transformation matrix
    output.alpha = uz_9ph_arraymul(0, vsd_mat, val);
    output.beta = uz_9ph_arraymul(1, vsd_mat, val);
    output.z1 = uz_9ph_arraymul(2, vsd_mat, val);
    output.z2 = uz_9ph_arraymul(3, vsd_mat, val);
    output.x1 = uz_9ph_arraymul(4, vsd_mat, val);
    output.y1 = uz_9ph_arraymul(5, vsd_mat, val);
    output.x2 = uz_9ph_arraymul(6, vsd_mat, val);
    output.y2 = uz_9ph_arraymul(7, vsd_mat, val);
    output.z3 = uz_9ph_arraymul(8, vsd_mat, val);
    return (output);
}

uz_9ph_abc_t uz_transformation_9ph_alphabeta_to_abc(uz_9ph_alphabeta_t input)
{
    uz_9ph_abc_t output = {0};
    float val[9] = {0};

    // VSD matrix from Matlab script, see Docs
    float vsd_mat[9][9] = 
{
    { 1.0000000f, -0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f, -0.0000000f, 1.0000000f, -0.0000000f, 1.0000000f },
    { -0.5000000f, 0.8660254f, 1.0000000f, -0.0000000f, -0.5000000f, -0.8660254f, -0.5000000f, 0.8660254f, 1.0000000f },
    { -0.5000000f, -0.8660254f, 1.0000000f, 0.0000000f, -0.5000000f, 0.8660254f, -0.5000000f, -0.8660254f, 1.0000000f },
    { 0.9396926f, 0.3420201f, 0.5000000f, 0.8660254f, -0.1736482f, 0.9848078f, -0.7660444f, 0.6427876f, -1.0000000f },
    { -0.7660444f, 0.6427876f, 0.5000000f, 0.8660254f, 0.9396926f, -0.3420201f, -0.1736482f, -0.9848078f, -1.0000000f },
    { -0.1736482f, -0.9848078f, 0.5000000f, 0.8660254f, -0.7660444f, -0.6427876f, 0.9396926f, 0.3420201f, -1.0000000f },
    { 0.7660444f, 0.6427876f, -0.5000000f, 0.8660254f, -0.9396926f, -0.3420201f, 0.1736482f, -0.9848078f, 1.0000000f },
    { -0.9396926f, 0.3420201f, -0.5000000f, 0.8660254f, 0.1736482f, 0.9848078f, 0.7660444f, 0.6427876f, 1.0000000f },
    { 0.1736482f, -0.9848078f, -0.5000000f, 0.8660254f, 0.7660444f, -0.6427876f, -0.9396926f, 0.3420201f, 1.0000000f }
};

    // write values of abc struct to array for easier usage
    val[0] = input.alpha;
    val[1] = input.beta;
    val[2] = input.z1;
    val[3] = input.z2;
    val[4] = input.x1;
    val[5] = input.y1;
    val[6] = input.x2;
    val[7] = input.y2;
    val[8] = input.z3;

    // apply transformation matrix
    output.a1 = uz_9ph_arraymul(0, vsd_mat, val);
    output.b1 = uz_9ph_arraymul(1, vsd_mat, val);
    output.c1 = uz_9ph_arraymul(2, vsd_mat, val);
    output.a2 = uz_9ph_arraymul(3, vsd_mat, val);
    output.b2 = uz_9ph_arraymul(4, vsd_mat, val);
    output.c2 = uz_9ph_arraymul(5, vsd_mat, val);
    output.a3 = uz_9ph_arraymul(6, vsd_mat, val);
    output.b3 = uz_9ph_arraymul(7, vsd_mat, val);
    output.c3 = uz_9ph_arraymul(8, vsd_mat, val);
    return (output);
}

// 1D array multiplication ([a, b, c] * [x; y; z] = [a*x + b*y + c*z])
float uz_9ph_arraymul(int line, float const matrixval[9][9], float const val[9])
{
    float output = 0.0f;
    for (int i = 0; i < 9; i++){
        output = output + (matrixval[line][i] * val[i]);
    }
    return output;
}
