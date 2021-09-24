#include "uz_nn_activation_functions.h"
#include "../uz/uz_HAL.h"

float uz_nn_activation_function_linear(float x){
    return (x);
}

float uz_nn_activation_function_linear_derivative(float x){
    return (1.0f);
}

float uz_nn_activation_function_relu(float x){
    float y=0.0f;
    if (x >0.0f){
        y=x;
    }else{
        y=0.0f;
    }
    return (y);
}

float uz_nn_activation_function_relu_derivative(float x){
    float y=0.0f;
    if (x > 0.0f){
        y=1.0f;
    }
    return (y);
}

float uz_nn_activation_function_leaky_relu(float x, float alpha){
    uz_assert(alpha>0.0f);
    uz_assert(alpha<1.0f);
    float y=0.0f;
    if (x >0.0f){
        y=x;
    }else{
        y=alpha * x;
    }
    return (y);
}

float uz_nn_activation_function_leaky_relu_derivative(float x, float alpha){
    uz_assert(alpha>0.0f);
    uz_assert(alpha<1.0f);
    float y=alpha;
    if (x > 0.0f){
        y=1.0f;
    }
    return (y);
}

