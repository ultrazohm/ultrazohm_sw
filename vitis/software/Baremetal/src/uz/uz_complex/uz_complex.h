#ifndef UZ_COMPLEX_H
#define UZ_COMPLEX_H

#include "../uz_math_constants.h"
#include <stdint.h>
#include <math.h>

/**
 * @brief struct for complex number in cartesian form
 *
 */
typedef struct uz_complex_cartesian_t{
    float real;             /**< real component */
    float imaginary;        /**< imaginary component */
}uz_complex_cartesian_t;

/**
 * @brief struct for complex number in exponantial form
 *
 */
typedef struct uz_complex_exponential_t{
    float absolute;         /**< absolute of exponential complex number */
    float phase;            /**< phase of exponential complex number in rad */
}uz_complex_exponential_t;

/**
 * @brief multiplication for complex numbers
 * 
 * @param arg1 first factor
 * @param arg2 second factor
 * @return uz_complex_cartesian_t the complex multiplication of both factors
 */
uz_complex_cartesian_t uz_complex_multiplication(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2);

/**
 * @brief addition for complex numbers
 * 
 * @param arg1 first summand
 * @param arg2 second summand
 * @return uz_complex_cartesian_t the complex addition of both summands
 */
uz_complex_cartesian_t uz_complex_addition(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2);

/**
 * @brief subtraction for complex numbers
 * 
 * @param subtrahend number to subtract
 * @param minuend number to subtract with
 * @return uz_complex_cartesian_t the complex subtraction of subtrahend - minuend
 */
uz_complex_cartesian_t uz_complex_subtraction(uz_complex_cartesian_t subtrahend, uz_complex_cartesian_t minuend);

/**
 * @brief division for complex numbers
 * 
 * @param dividend number to get divided
 * @param divisor number to divide with
 * @return uz_complex_cartesian_t the complex division of dividend/divisor
*/
uz_complex_cartesian_t uz_complex_division(uz_complex_cartesian_t dividend, uz_complex_cartesian_t divisor);

/**
 * @brief transformation from complex cartesian to complex exponential
 * 
 * @param in cartesian complex number
 * @return uz_complex_exponential_t complex number in exponential form
*/
uz_complex_exponential_t uz_complex_cartesian_to_exponential(uz_complex_cartesian_t in);

/**
 * @brief transformation from complex exponential to complex cartesian
 * 
 * @param in exponential complex number
 * @return uz_complex_cartesian_t complex number in cartesian form
*/
uz_complex_cartesian_t uz_complex_exponential_to_cartesian(uz_complex_exponential_t in);

#endif // UZ_COMPLEX_H
