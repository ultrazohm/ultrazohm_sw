/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2021 Tobias Schindler
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

#include "uz_nn_activation_functions.h"
#include "../uz_HAL.h"

float uz_nn_activation_function_linear(float x)
{
    return (x);
}

// The variable x is unused here since it is not required to calculate the derivative. Still in the function call to ensure consistent interface to all activation functions+derivatives.
// Compiler warning suppresed by using gcc attribute "unused"
float uz_nn_activation_function_linear_derivative(__attribute__((unused)) float x)
{
    return (1.0f);
}

float uz_nn_activation_function_relu(float x)
{
    float y = 0.0f;
    if (x > 0.0f)
    {
        y = x;
    }
    else
    {
        y = 0.0f;
    }
    return (y);
}

float uz_nn_activation_function_relu_derivative(float x)
{
    float y = 0.0f;
    if (x > 0.0f)
    {
        y = 1.0f;
    }
    return (y);
}

float uz_nn_activation_function_leaky_relu(float x, float alpha)
{
    uz_assert(alpha > 0.0f);
    uz_assert(alpha < 1.0f);
    float y = 0.0f;
    if (x > 0.0f)
    {
        y = x;
    }
    else
    {
        y = alpha * x;
    }
    return (y);
}

float uz_nn_activation_function_leaky_relu_derivative(float x, float alpha)
{
    uz_assert(alpha > 0.0f);
    uz_assert(alpha < 1.0f);
    float y = alpha;
    if (x > 0.0f)
    {
        y = 1.0f;
    }
    return (y);
}

float uz_nn_activation_function_sigmoid_logistic(float x)
{
    return (1.0f / (1.0f + expf(-x)));
}

float uz_nn_activation_function_sigmoid_logistic_derivative(float x)
{
    float sigmoid_result = uz_nn_activation_function_sigmoid_logistic(x);
    float sigmoid_derivative = sigmoid_result * (1.0f - sigmoid_result);
    return sigmoid_derivative;
}

float uz_nn_activation_function_sigmoid2_logistic(float x)
{
    return (0.5f + (0.5f * tanhf(0.5f * x)));
}

float uz_nn_activation_function_sigmoid2_logistic_derivative(float x)
{
    float sigmoid_result = uz_nn_activation_function_sigmoid2_logistic(x);
    float sig_derivative = sigmoid_result * (1.0f - sigmoid_result);
    return sig_derivative;
}

//

float uz_nn_activation_function_tanh(float x)
{
    return tanhf(x);
}

float uz_nn_activation_function_tanh_derivative(float x)
{
    float tanh_result = uz_nn_activation_function_tanh(x);
    return (1 - (tanh_result * tanh_result));
}


