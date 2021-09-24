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

#endif // UZ_NN_ACTIVATION_FUNCTIONS_H
