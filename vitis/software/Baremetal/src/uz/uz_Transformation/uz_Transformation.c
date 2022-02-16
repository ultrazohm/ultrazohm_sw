/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel
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
struct uz_dq_t uz_dq_transformation(struct uz_UVW_t input, float theta_el_rad){
    struct uz_alphabeta_t ab = uz_clarke_transformation(input);
    float sin_coefficent = sinf(theta_el_rad);
    float cos_coefficent = cosf(theta_el_rad);
    struct uz_dq_t output = {
        .d = (cos_coefficent * ab.alpha) + (sin_coefficent * ab.beta),
        .q = (-sin_coefficent * ab.alpha) + (cos_coefficent * ab.beta),
        .zero = ab.gamma
    };
    return(output);
}

struct uz_UVW_t uz_dq_inverse_transformation(struct uz_dq_t input, float theta_el_rad){
   
   float sin_coefficent = sinf(theta_el_rad);
   float cos_coefficent = cosf(theta_el_rad);
    struct uz_alphabeta_t ab = {
        .alpha = (cos_coefficent * input.d) - (sin_coefficent * input.q),
        .beta = (sin_coefficent * input.d) + (cos_coefficent * input.q),
        .gamma = input.zero
    };
    struct uz_UVW_t output=uz_clarke_inverse_transformation(ab);
    return(output);
}

struct uz_alphabeta_t uz_clarke_transformation(struct uz_UVW_t input) {
	struct uz_alphabeta_t output = {
        .alpha = (2.0f / 3.0f) * (input.U - (input.V / 2.0f) - (input.W / 2.0f) ),
        .beta = (2.0f / 3.0f) * ( (input.V * (sqrtf(3.0f) / 2.0f) ) - (input.W * (sqrtf(3.0f) / 2.0f) ) ),
        .gamma = (1.0f / 3.0f) * (input.U + input.V + input.W)
    };
    return(output);
}

struct uz_UVW_t uz_clarke_inverse_transformation(struct uz_alphabeta_t input){
    struct uz_UVW_t output = {
        .U =  input.alpha + input.gamma,
        .V = (input.alpha * (-1.0f / 2.0f) ) + (input.beta * (sqrtf(3.0f) / 2.0f) ) + input.gamma,
        .W = (input.alpha * (-1.0f / 2.0f) ) + (input.beta * (-sqrtf(3.0f) / 2.0f) ) + input.gamma
    };
    return(output);
}

float uz_9ph_arraymul(int line, float matrixval[9][9], float electricval[9]){
    int i=0;
    float output=0;
    for(i=0;i<9;i++)
        output = output + matrixval[line][i]*electricval[i];
    return output;
}


struct uz_alphabeta_9ph_t uz_9ph_clarke_transformation(struct uz_abc_9ph_t input){
    struct uz_alphabeta_9ph_t output;
    float electricval[9], vsd_mat[9][9];

    //write values of abc struct to array for easier usage
    electricval[0] = input.a1;
    electricval[1] = input.b1;
    electricval[2] = input.c1;
    electricval[3] = input.a2;
    electricval[4] = input.b2;
    electricval[5] = input.c2;
    electricval[6] = input.a3;
    electricval[7] = input.b3;
    electricval[8] = input.c3;

    //create transformationmatrix
    vsd_mat[0][0] = 0.2222222f;
    vsd_mat[0][1] = -0.1111111f;
    vsd_mat[0][2] = -0.1111111f;
    vsd_mat[0][3] = 0.2088206f;
    vsd_mat[0][4] = -0.1702321f;
    vsd_mat[0][5] = -0.0385885f;
    vsd_mat[0][6] = 0.1702321f;
    vsd_mat[0][7] = -0.2088206f;
    vsd_mat[0][8] = 0.0385885f;
    vsd_mat[1][0] = 0.0000000f;
    vsd_mat[1][1] = 0.1924501f;
    vsd_mat[1][2] = -0.1924501f;
    vsd_mat[1][3] = 0.0760045f;
    vsd_mat[1][4] = 0.1428417f;
    vsd_mat[1][5] = -0.2188462f;
    vsd_mat[1][6] = 0.1428417f;
    vsd_mat[1][7] = 0.0760045f;
    vsd_mat[1][8] = -0.2188462f;
    vsd_mat[2][0] = 0.2222222f;
    vsd_mat[2][1] = 0.2222222f;
    vsd_mat[2][2] = 0.2222222f;
    vsd_mat[2][3] = 0.1111111f;
    vsd_mat[2][4] = 0.1111111f;
    vsd_mat[2][5] = 0.1111111f;
    vsd_mat[2][6] = -0.1111111f;
    vsd_mat[2][7] = -0.1111111f;
    vsd_mat[2][8] = -0.1111111f;
    vsd_mat[3][0] = 0.0000000f;
    vsd_mat[3][1] = -0.0000000f;
    vsd_mat[3][2] = -0.0000000f;
    vsd_mat[3][3] = 0.1924501f;
    vsd_mat[3][4] = 0.1924501f;
    vsd_mat[3][5] = 0.1924501f;
    vsd_mat[3][6] = 0.1924501f;
    vsd_mat[3][7] = 0.1924501f;
    vsd_mat[3][8] = 0.1924501f;
    vsd_mat[4][0] = 0.2222222f;
    vsd_mat[4][1] = -0.1111111f;
    vsd_mat[4][2] = -0.1111111f;
    vsd_mat[4][3] = -0.0385885f;
    vsd_mat[4][4] = 0.2088206f;
    vsd_mat[4][5] = -0.1702321f;
    vsd_mat[4][6] = -0.2088206f;
    vsd_mat[4][7] = 0.0385885f;
    vsd_mat[4][8] = 0.1702321f;
    vsd_mat[5][0] = 0.0000000f;
    vsd_mat[5][1] = -0.1924501f;
    vsd_mat[5][2] = 0.1924501f;
    vsd_mat[5][3] = 0.2188462f;
    vsd_mat[5][4] = -0.0760045f;
    vsd_mat[5][5] = -0.1428417f;
    vsd_mat[5][6] = -0.0760045f;
    vsd_mat[5][7] = 0.2188462f;
    vsd_mat[5][8] = -0.1428417f;
    vsd_mat[6][0] = 0.2222222f;
    vsd_mat[6][1] = -0.1111111f;
    vsd_mat[6][2] = -0.1111111f;
    vsd_mat[6][3] = -0.1702321f;
    vsd_mat[6][4] = -0.0385885f;
    vsd_mat[6][5] = 0.2088206f;
    vsd_mat[6][6] = 0.0385885f;
    vsd_mat[6][7] = 0.1702321f;
    vsd_mat[6][8] = -0.2088206f;
    vsd_mat[7][0] = 0.0000000f;
    vsd_mat[7][1] = 0.1924501f;
    vsd_mat[7][2] = -0.1924501f;
    vsd_mat[7][3] = 0.1428417f;
    vsd_mat[7][4] = -0.2188462f;
    vsd_mat[7][5] = 0.0760045f;
    vsd_mat[7][6] = -0.2188462f;
    vsd_mat[7][7] = 0.1428417f;
    vsd_mat[7][8] = 0.0760045f;
    vsd_mat[8][0] = 0.1111111f;
    vsd_mat[8][1] = 0.1111111f;
    vsd_mat[8][2] = 0.1111111f;
    vsd_mat[8][3] = 0.1111111f;
    vsd_mat[8][4] = 0.1111111f;
    vsd_mat[8][5] = 0.1111111f;
    vsd_mat[8][6] = 0.1111111f;
    vsd_mat[8][7] = 0.1111111f;
    vsd_mat[8][8] = 0.1111111f;

    //apply transformation matrix
    output.alpha = uz_9ph_arraymul(0, vsd_mat, electricval);
    output.beta  = uz_9ph_arraymul(1, vsd_mat, electricval);
    output.o1 = uz_9ph_arraymul(2, vsd_mat, electricval);
    output.o2 = uz_9ph_arraymul(3, vsd_mat, electricval);
    output.x1 = uz_9ph_arraymul(4, vsd_mat, electricval);
    output.y1 = uz_9ph_arraymul(5, vsd_mat, electricval);
    output.x2 = uz_9ph_arraymul(6, vsd_mat, electricval);
    output.y2 = uz_9ph_arraymul(7, vsd_mat, electricval);
    output.zero = uz_9ph_arraymul(8, vsd_mat, electricval);
    return(output);
}


struct uz_abc_9ph_t uz_9ph_clarke_inverse_transformation(struct uz_alphabeta_9ph_t input){
    struct uz_abc_9ph_t output;
    float electricval[9], vsd_mat[9][9];

    //write values of abc struct to array for easier usage
    electricval[0] = input.alpha;
    electricval[1] = input.beta;
    electricval[2] = input.o1;
    electricval[3] = input.o2;
    electricval[4] = input.x1;
    electricval[5] = input.y1;
    electricval[6] = input.x2;
    electricval[7] = input.y2;
    electricval[8] = input.zero;

    //create transformationmatrix, values imported from Matlab script LINK??
vsd_mat[0][0] = 1.0000000f;
vsd_mat[0][1] = 0.0000002f;
vsd_mat[0][2] = -0.0000002f;
vsd_mat[0][3] = -1.7320511f;
vsd_mat[0][4] = 0.9999998f;
vsd_mat[0][5] = 0.0000001f;
vsd_mat[0][6] = 1.0000000f;
vsd_mat[0][7] = -0.0000000f;
vsd_mat[0][8] = 3.0000005f;
vsd_mat[1][0] = -0.5000001f;
vsd_mat[1][1] = 0.8660257f;
vsd_mat[1][2] = 0.0000000f;
vsd_mat[1][3] = -1.7320509f;
vsd_mat[1][4] = -0.5000000f;
vsd_mat[1][5] = -0.8660253f;
vsd_mat[1][6] = -0.4999999f;
vsd_mat[1][7] = 0.8660253f;
vsd_mat[1][8] = 3.0000000f;
vsd_mat[2][0] = -0.5000000f;
vsd_mat[2][1] = -0.8660253f;
vsd_mat[2][2] = 0.0000000f;
vsd_mat[2][3] = -1.7320509f;
vsd_mat[2][4] = -0.5000000f;
vsd_mat[2][5] = 0.8660254f;
vsd_mat[2][6] = -0.5000001f;
vsd_mat[2][7] = -0.8660254f;
vsd_mat[2][8] = 3.0000000f;
vsd_mat[3][0] = 0.9396926f;
vsd_mat[3][1] = 0.3420202f;
vsd_mat[3][2] = 1.5000002f;
vsd_mat[3][3] = 2.5980763f;
vsd_mat[3][4] = -0.1736481f;
vsd_mat[3][5] = 0.9848076f;
vsd_mat[3][6] = -0.7660445f;
vsd_mat[3][7] = 0.6427875f;
vsd_mat[3][8] = -3.0000005f;
vsd_mat[4][0] = -0.7660444f;
vsd_mat[4][1] = 0.6427875f;
vsd_mat[4][2] = 1.4999998f;
vsd_mat[4][3] = 2.5980761f;
vsd_mat[4][4] = 0.9396926f;
vsd_mat[4][5] = -0.3420202f;
vsd_mat[4][6] = -0.1736481f;
vsd_mat[4][7] = -0.9848077f;
vsd_mat[4][8] = -2.9999995f;
vsd_mat[5][0] = -0.1736481f;
vsd_mat[5][1] = -0.9848077f;
vsd_mat[5][2] = 1.5000002f;
vsd_mat[5][3] = 2.5980763f;
vsd_mat[5][4] = -0.7660444f;
vsd_mat[5][5] = -0.6427878f;
vsd_mat[5][6] = 0.9396926f;
vsd_mat[5][7] = 0.3420201f;
vsd_mat[5][8] = -3.0000005f;
vsd_mat[6][0] = 0.7660444f;
vsd_mat[6][1] = 0.6427878f;
vsd_mat[6][2] = -1.4999998f;
vsd_mat[6][3] = -0.8660253f;
vsd_mat[6][4] = -0.9396927f;
vsd_mat[6][5] = -0.3420200f;
vsd_mat[6][6] = 0.1736483f;
vsd_mat[6][7] = -0.9848078f;
vsd_mat[6][8] = 2.9999995f;
vsd_mat[7][0] = -0.9396926f;
vsd_mat[7][1] = 0.3420202f;
vsd_mat[7][2] = -1.4999999f;
vsd_mat[7][3] = -0.8660253f;
vsd_mat[7][4] = 0.1736481f;
vsd_mat[7][5] = 0.9848078f;
vsd_mat[7][6] = 0.7660445f;
vsd_mat[7][7] = 0.6427876f;
vsd_mat[7][8] = 2.9999998f;
vsd_mat[8][0] = 0.1736481f;
vsd_mat[8][1] = -0.9848076f;
vsd_mat[8][2] = -1.5000000f;
vsd_mat[8][3] = -0.8660254f;
vsd_mat[8][4] = 0.7660444f;
vsd_mat[8][5] = -0.6427876f;
vsd_mat[8][6] = -0.9396925f;
vsd_mat[8][7] = 0.3420201f;
vsd_mat[8][8] = 3.0000000f;

    //apply transformation matrix
    output.a1 = uz_9ph_arraymul(0, vsd_mat, electricval);
    output.b1 = uz_9ph_arraymul(1, vsd_mat, electricval);
    output.c1 = uz_9ph_arraymul(2, vsd_mat, electricval);
    output.a2 = uz_9ph_arraymul(3, vsd_mat, electricval);
    output.b2 = uz_9ph_arraymul(4, vsd_mat, electricval);
    output.c2 = uz_9ph_arraymul(5, vsd_mat, electricval);
    output.a3 = uz_9ph_arraymul(6, vsd_mat, electricval);
    output.b3 = uz_9ph_arraymul(7, vsd_mat, electricval);
    output.c3 = uz_9ph_arraymul(8, vsd_mat, electricval);
    return(output);
}


struct uz_dq_t uz_ab_to_dq_transformation(struct uz_alphabeta_t input, float theta_el_rad){
    float cos_theta = 0, sin_theta = 0;
    struct uz_dq_t output;
    cos_theta = cosf(theta_el_rad);
    sin_theta = sinf(theta_el_rad);
    output.d =    cos_theta*input.alpha + sin_theta*input.beta;
    output.q = -1*sin_theta*input.alpha + cos_theta*input.beta;
    output.zero = -999999.0f;
    return output;
}

struct uz_alphabeta_t uz_dq_to_ab_inverse_transformation(struct uz_dq_t input, float theta_el_rad){
    float cos_theta = 0, sin_theta = 0;
    struct uz_alphabeta_t output;
    cos_theta = cosf(theta_el_rad);
    sin_theta = sinf(theta_el_rad);
    output.alpha = cos_theta*input.d - sin_theta*input.q;
    output.beta  = sin_theta*input.d + cos_theta*input.q;
    output.gamma = -999999.0f;
    return output;
}
