#ifndef UZ_NN_ACTIVATION_FUNCTIONS_H
#define UZ_NN_ACTIVATION_FUNCTIONS_H

/**
 * @brief Linear activation function, f(x)=x
 * 
 * @param x 
 * @return float 
 */
float uz_nn_activation_function_linear(float x);

/**
 * @brief Derivative of linear activation function, f'(x)=1
 * 
 * @param x 
 * @return float 
 */
// cppcheck-suppress misra-c2012-2.7 // the input argument "x" is not used here. However, the function definition should be consistent with all other activation function definitions to ensure that function pointers can be used with the same arguments.
float uz_nn_activation_function_linear_derivative(float x);

/**
 * @brief Rectified linear unit, returns 0 if x <= 0, otherwise x 
 * 
 * @param x 
 * @return float 
 */
float uz_nn_activation_function_relu(float x);

/**
 * @brief Derivative of rectified linear unit, returns 0 if x <= 0, otherwise 1.0
 * 
 * @param x 
 * @return float 
 */
float uz_nn_activation_function_relu_derivative(float x);

/**
 * @brief Leaky rectified linear unit, returns alpha*x if x <=0, otherwise x
 * 
 * @param x 
 * @param alpha Linear factor for x if x < 0. alpha has to be 1>alpha>0
 * @return float 
 */
float uz_nn_activation_function_leaky_relu(float x, float alpha);

/**
 * @brief Derivative of leaky rectified linear unit, returns alpha if x <=0, otherwise 1.0
 * 
 * @param x 
 * @param alpha Linear factor for x if x < 0. alpha has to be 1>alpha>0
 * @return float 
 */
float uz_nn_activation_function_leaky_relu_derivative(float x, float alpha);

/**
 * @brief 
 * 
 * @param x 
 * @return float 
 */
float uz_nn_activation_function_sigmoid_logistic(float x);

float uz_nn_activation_function_sigmoid_logistic_derivative(float x);

float uz_nn_activation_function_sigmoid2_logistic(float x);

float uz_nn_activation_function_sigmoid2_logistic_derivative(float x);

float uz_nn_activation_function_tanh(float x);

float uz_nn_activation_function_tanh_derivative(float x);


#endif // UZ_NN_ACTIVATION_FUNCTIONS_H
