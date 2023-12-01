#ifndef UZ_PRNG_HALTON_H
#define UZ_PRNG_HALTON_H

#include <stdint.h>
#include "../uz_array/uz_array.h"

/**
 * @brief Object of Halton sequence generator
 * 
 */
typedef struct uz_prng_halton_t uz_prng_halton_t;

/**
 * @brief Initializes the Halton sequence generator for a given base prime number. 
 *
 * @param base_prime Must be a prime number!
 * @return uz_prng_halton_t*
 */
uz_prng_halton_t *uz_prng_halton_init(uint32_t base_prime);

/**
 * @brief Generates one number of a Halton sequence. After n-calls, this function returns the n+1 number in the sequence given the initialization properties.
 * 
 * @param self 
 * @return float 
 */
float uz_prng_halton_get_uniform_float(uz_prng_halton_t *self);

/**
 * @brief Generates two numbers, x and y, of the 2D Halton sequence. Returns x and y by pointer, i.e., writes the number of the Halton sequence to the address specified by the arguments *x, *y.
 *
 * @param self
 * @param x Returns x-value of Halton sequence thought pointer
 * @param y Returns y-value of Halton sequence thought pointer
 */
void uz_prng_halton_get_uniform_float_2d(uz_prng_halton_t *self, float *x, float *y);

#endif // UZ_PRNG_HALTON_H
