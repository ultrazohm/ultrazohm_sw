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
float uz_6ph_arraymul(int line, float const matrixval[6][6], float const val[6]);
float uz_9ph_arraymul(int line, float const matrixval[9][9], float const val[9]);
uz_3ph_alphabeta_t uz_complex_rotation(uz_3ph_alphabeta_t input, struct uz_complex_magn_phase factor);





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
    return (output);
}

uz_3ph_alphabeta_t uz_transformation_3ph_dq_to_alphabeta(uz_3ph_dq_t input, float theta_el_rad)
{
    float sin_coefficient = sinf(theta_el_rad);
    float cos_coefficient = cosf(theta_el_rad);
    uz_3ph_alphabeta_t ab = {
        .alpha = (cos_coefficient * input.d) - (sin_coefficient * input.q),
        .beta = (sin_coefficient * input.d) + (cos_coefficient * input.q),
        .gamma = input.zero};
    return (ab);
}




// 6 phase
uz_6ph_alphabeta_t uz_transformation_asym30deg_6ph_abc_to_alphabeta(uz_6ph_abc_t input){
    uz_6ph_alphabeta_t output = {0};
    float val[6] = {0};

    // VSD matrix from Matlab script, see Docs
    float const vsd_mat[6][6] = {
        { 0.3333333f, -0.1666667f, -0.1666667f, 0.2886751f, -0.2886751f, 0.0000000f },
        { 0.0000000f, 0.2886751f, -0.2886751f, 0.1666667f, 0.1666667f, -0.3333333f },
        { 0.3333333f, -0.1666667f, -0.1666667f, -0.2886751f, 0.2886751f, 0.0000000f },
        { 0.0000000f, -0.2886751f, 0.2886751f, 0.1666667f, 0.1666667f, -0.3333333f },
        { 0.3333333f, 0.3333333f, 0.3333333f, 0.0000000f, 0.0000000f, 0.0000000f },
        { 0.0000000f, 0.0000000f, 0.0000000f, 0.3333333f, 0.3333333f, 0.3333333f }
    };

    // write values of abc struct to array for easier usage
    val[0] = input.a1;
    val[1] = input.b1;
    val[2] = input.c1;
    val[3] = input.a2;
    val[4] = input.b2;
    val[5] = input.c2;


    // apply transformation matrix
    output.alpha = uz_6ph_arraymul(0, vsd_mat, val);
    output.beta = uz_6ph_arraymul(1, vsd_mat, val);
    output.x = uz_6ph_arraymul(2, vsd_mat, val);
    output.y = uz_6ph_arraymul(3, vsd_mat, val);
    output.z1 = uz_6ph_arraymul(4, vsd_mat, val);
    output.z2 = uz_6ph_arraymul(5, vsd_mat, val);

    return (output);

}

uz_6ph_abc_t uz_transformation_asym30deg_6ph_alphabeta_to_abc(uz_6ph_alphabeta_t input){
    uz_6ph_abc_t output = {0};
    float val[6] = {0};

    // VSD matrix from Matlab script, see Docs
    float const vsd_mat[6][6] = {
        { 1.0000000f, 0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f, -0.0000000f },
        { -0.5000001f, 0.8660254f, -0.4999999f, -0.8660254f, 1.0000000f, -0.0000000f },
        { -0.4999999f, -0.8660254f, -0.5000001f, 0.8660254f, 1.0000000f, 0.0000000f },
        { 0.8660254f, 0.5000000f, -0.8660254f, 0.5000000f, 0.0000000f, 1.0000000f },
        { -0.8660254f, 0.5000000f, 0.8660254f, 0.5000000f, 0.0000000f, 1.0000000f },
        { 0.0000000f, -1.0000000f, 0.0000000f, -1.0000000f, 0.0000000f, 1.0000000f }
    };

    
    // write values of abc struct to array for easier usage
    val[0] = input.alpha;
    val[1] = input.beta;
    val[2] = input.x;
    val[3] = input.y;
    val[4] = input.z1;
    val[5] = input.z2;

    // apply transformation matrix
    output.a1 = uz_6ph_arraymul(0, vsd_mat, val);
    output.b1 = uz_6ph_arraymul(1, vsd_mat, val);
    output.c1 = uz_6ph_arraymul(2, vsd_mat, val);
    output.a2 = uz_6ph_arraymul(3, vsd_mat, val);
    output.b2 = uz_6ph_arraymul(4, vsd_mat, val);
    output.c2 = uz_6ph_arraymul(5, vsd_mat, val);
    return (output);
}

uz_6ph_dq_t uz_transformation_asym30deg_6ph_alphabeta_to_dq(uz_6ph_alphabeta_t input, float theta_el_rad)
{
    uz_3ph_alphabeta_t intermediate_three_phase_ab={
        .alpha=input.alpha,
        .beta=input.beta,
        .gamma=0.0f};
    uz_3ph_dq_t intermediate_dq=uz_transformation_3ph_alphabeta_to_dq(intermediate_three_phase_ab,theta_el_rad);
    uz_6ph_dq_t result={
        .d=intermediate_dq.d,
        .q=intermediate_dq.q,
        .x=input.x,
        .y=input.y,
        .z1=input.z1,
        .z2=input.z2};
    return (result);
}

 uz_6ph_alphabeta_t uz_transformation_asym30deg_6ph_dq_to_alphabeta(uz_6ph_dq_t input, float theta_el_rad){    
    uz_3ph_dq_t dq_3phase={
        .d=input.d,
        .q=input.q,
        .zero=0.0f}; 
    uz_3ph_alphabeta_t intermediate=uz_transformation_3ph_dq_to_alphabeta(dq_3phase,theta_el_rad);
    uz_6ph_alphabeta_t result={
        .alpha=intermediate.alpha,
        .beta=intermediate.beta,
        .x=input.x,
        .y=input.y,
        .z1=input.z1,
        .z2=input.z2};
    return (result);
}

uz_6ph_dq_t uz_transformation_asym30deg_6ph_abc_to_dq(uz_6ph_abc_t input, float theta_el_rad){
    uz_6ph_alphabeta_t intermediate=uz_transformation_asym30deg_6ph_abc_to_alphabeta(input);
    return (uz_transformation_asym30deg_6ph_alphabeta_to_dq(intermediate,theta_el_rad));
}

uz_6ph_abc_t uz_transformation_asym30deg_6ph_dq_to_abc(uz_6ph_dq_t input, float theta_el_rad){
    uz_6ph_alphabeta_t intermediate=uz_transformation_asym30deg_6ph_dq_to_alphabeta(input,theta_el_rad);
    return (uz_transformation_asym30deg_6ph_alphabeta_to_abc(intermediate));
}

uz_3ph_alphabeta_t uz_complex_rotation(uz_3ph_alphabeta_t input, struct uz_complex_magn_phase factor){
    uz_3ph_alphabeta_t output = {0};
    struct uz_complex_magn_phase complex = {0};
    complex.magnitude = sqrtf(powf(input.alpha,2.0f)+powf(input.beta,2.0f));
    complex.phase = atan2f(input.beta,input.alpha);
    output.alpha = complex.magnitude * factor.magnitude * cosf(complex.phase+factor.phase);
    output.beta = complex.magnitude * factor.magnitude * sinf(complex.phase+factor.phase);
    output.gamma = input.gamma;
    return output;
}

uz_6ph_abc_t uz_line_line_to_abc(uz_6ph_abc_t input){
    uz_6ph_abc_t output = {0};
    uz_3ph_abc_t abc_sys1 = {0};
    uz_3ph_abc_t abc_sys2 = {0};
    uz_3ph_alphabeta_t alphabeta_sys1 = {0};
    uz_3ph_alphabeta_t alphabeta_sys2 = {0};
    struct uz_complex_magn_phase factor = {
        .magnitude = 1.0f/sqrtf(3.0f),
        .phase = -1.0f/6.0f*UZ_PIf};
    abc_sys1.a = input.a1;
    abc_sys1.b = input.b1;
    abc_sys1.c = input.c1;
    abc_sys2.a = input.a2;
    abc_sys2.b = input.b2;
    abc_sys2.c = input.c2;
    alphabeta_sys1 = uz_complex_rotation(uz_transformation_3ph_abc_to_alphabeta(abc_sys1),factor);
    alphabeta_sys2 = uz_complex_rotation(uz_transformation_3ph_abc_to_alphabeta(abc_sys2),factor);
    abc_sys1 = uz_transformation_3ph_alphabeta_to_abc(alphabeta_sys1);
    abc_sys2 = uz_transformation_3ph_alphabeta_to_abc(alphabeta_sys2);
    output.a1 = abc_sys1.a;
    output.b1 = abc_sys1.b;
    output.c1 = abc_sys1.c;
    output.a2 = abc_sys2.a;
    output.b2 = abc_sys2.b;
    output.c2 = abc_sys2.c;
    return output;
}



// 1D array multiplication ([a, b, c] * [x; y; z] = [a*x + b*y + c*z])
float uz_6ph_arraymul(int line, float const matrixval[6][6], float const val[6])
{
    float output = 0.0f;
    for (int i = 0; i < 6; i++){
        output = output + (matrixval[line][i] * val[i]);
    }
    return (output);
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
    output.x1 = uz_9ph_arraymul(2, vsd_mat, val);
    output.y1 = uz_9ph_arraymul(3, vsd_mat, val);
    output.x2 = uz_9ph_arraymul(4, vsd_mat, val);
    output.y2 = uz_9ph_arraymul(5, vsd_mat, val);
    output.x3 = uz_9ph_arraymul(6, vsd_mat, val);
    output.y3 = uz_9ph_arraymul(7, vsd_mat, val);
    output.zero = uz_9ph_arraymul(8, vsd_mat, val);
    return (output);
}

uz_9ph_abc_t uz_transformation_9ph_alphabeta_to_abc(uz_9ph_alphabeta_t input)
{
    uz_9ph_abc_t output = {0};
    float val[9] = {0};

    // VSD matrix from Matlab script, see Docs
    float const vsd_mat[9][9] = 
        {
            { 1.0000000f, -0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f, -0.0000000f, 1.0000000f, -0.0000000f, 1.0000000f },
            { -0.5000000f, 0.8660254f, 1.0000000f, -0.0000000f, -0.5000000f, -0.8660254f, -0.5000000f, 0.8660254f, 1.0000000f },
            { -0.5000000f, -0.8660254f, 1.0000000f, 0.0000000f, -0.5000000f, 0.8660254f, -0.5000000f, -0.8660254f, 1.0000000f },
            { 0.9396926f, 0.3420201f, 0.5000000f, 0.8660254f, -0.1736482f, 0.9848078f, -0.7660444f, 0.6427876f, -1.0000000f },
            { -0.7660444f, 0.6427876f, 0.5000000f, 0.8660254f, 0.9396926f, -0.3420201f, -0.1736482f, -0.9848078f, -1.0000000f },
            { -0.1736482f, -0.9848078f, 0.5000000f, 0.8660254f, -0.7660444f, -0.6427876f, 0.9396926f, 0.3420201f, -1.0000000f },
            { 0.7660444f, 0.6427876f, -0.5000000f, 0.8660254f, -0.9396926f, -0.3420201f, 0.1736482f, -0.9848078f, 1.0000000f },
            { -0.9396926f, 0.3420201f, -0.5000000f, 0.8660254f, 0.1736482f, 0.9848078f, 0.7660444f, 0.6427876f, 1.0000000f },
            { 0.1736482f, -0.9848078f, -0.5000000f, 0.8660254f, 0.7660444f, -0.6427876f, -0.9396926f, 0.3420201f, 1.0000000f }};

    // write values of abc struct to array for easier usage
    val[0] = input.alpha;
    val[1] = input.beta;
    val[2] = input.x1;
    val[3] = input.y1;
    val[4] = input.x2;
    val[5] = input.y2;
    val[6] = input.x3;
    val[7] = input.y3;
    val[8] = input.zero;

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
    return (output);
}

uz_9ph_dq_t uz_transformation_9ph_alphabeta_to_dq(uz_9ph_alphabeta_t input, float theta_el_rad){
    uz_3ph_alphabeta_t intermediate_three_phase_ab={
        .alpha=input.alpha,
        .beta=input.beta,
        .gamma=0.0f
    };
    uz_3ph_dq_t intermediate_dq=uz_transformation_3ph_alphabeta_to_dq(intermediate_three_phase_ab,theta_el_rad);
   
    uz_9ph_dq_t result={
        .d=intermediate_dq.d,
        .q=intermediate_dq.q,
        .x1=input.x1,
        .y1=input.y1,
        .x2=input.x2,
        .y2=input.y2,
        .x3=input.x3,
        .y3=input.y3,
        .zero=input.zero,
    };
    return (result);
}

uz_9ph_alphabeta_t uz_transformation_9ph_dq_to_alphabeta(uz_9ph_dq_t input, float theta_el_rad){
    
    uz_3ph_dq_t dq_3phase={
        .d=input.d,
        .q=input.q,
        .zero=0.0f
    };    
    uz_3ph_alphabeta_t intermediate=uz_transformation_3ph_dq_to_alphabeta(dq_3phase,theta_el_rad);
    uz_9ph_alphabeta_t result={
        .alpha=intermediate.alpha,
        .beta=intermediate.beta,
        .x1=input.x1,
        .y1=input.y1,
        .x2=input.x2,
        .y2=input.y2,
        .x3=input.x3,
        .y3=input.y3,
        .zero=input.zero,
    };
    return (result);
}

uz_9ph_dq_t uz_transformation_9ph_abc_to_dq(uz_9ph_abc_t input, float theta_el_rad){
    uz_9ph_alphabeta_t intermediate=uz_transformation_9ph_abc_to_alphabeta(input);
    return (uz_transformation_9ph_alphabeta_to_dq(intermediate,theta_el_rad));
}

uz_9ph_abc_t uz_transformation_9ph_dq_to_abc(uz_9ph_dq_t input, float theta_el_rad){
    uz_9ph_alphabeta_t intermediate=uz_transformation_9ph_dq_to_alphabeta(input,theta_el_rad);
    return (uz_transformation_9ph_alphabeta_to_abc(intermediate));
}