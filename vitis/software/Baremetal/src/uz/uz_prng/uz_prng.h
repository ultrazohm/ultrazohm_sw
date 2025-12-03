#ifndef UZ_PRNG_H
#define UZ_PRNG_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object of a random number generator
 * 
 */
typedef struct uz_prng_t uz_prng_t;

/**
 * @brief Choose which generator is used internally.
 * 
 */
enum uz_prng_generator
{
    uz_prng_generator_squares,
    uz_prng_generator_mtwister,
    uz_prng_generator_pcg,
    uz_prng_generator_xoshiro,
    uz_prng_generator_halton
};

/**
 * @brief Choose which scaling version to generate random float values is used. uz_prng_float_scale_fp_shift_multiply is recommended.
 *
 */
enum uz_prng_float_scale_method
{
    uz_prng_float_scale_fp_multiply,
    uz_prng_float_scale_fp_divide,
    uz_prng_float_scale_fp_shift_multiply
};

/**
 * @brief Initializes a random number generator for the specified generator type, scaling method and random seed.
 * 
 * @param generator Generator type
 * @param scale_method Scaling version
 * @param seed Seed of the generator. See documentation of the individual generator types on how to set the seed.
 * @return uz_prng_t* 
 */
uz_prng_t *uz_prng_init(enum uz_prng_generator generator, enum uz_prng_float_scale_method scale_method, uint64_t seed);

/**
 * @brief Generate one uniform distributed uint32 in the interval [0,2^32), i.e., 0 up to and including UINT32_MAX.
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t uz_prng_get_uniform_uint32_zero_to_uint32_max(uz_prng_t *self);

/**
 * @brief Generate one uniform distributed uint32 in the interval [0,range), i.e., 0 up to but excluding "range". Uses Lemire's method (https://arxiv.org/abs/1805.10941) according to https://www.pcg-random.org/posts/bounded-rands.html.
 *
 * @param self
 * @param range
 * @return uint32_t
 */
uint32_t uz_prng_get_uniform_uint32_zero_to_range_unbiased(uz_prng_t *self, uint32_t range);

/**
 * @brief Generate one uniform distributed uint32 in the interval [0,range), i.e., 0 up to but excluding "range". Uses an faster version of Lemire's method (https://arxiv.org/abs/1805.10941) according to https://www.pcg-random.org/posts/bounded-rands.html.
 *
 * @param self
 * @param range
 * @return uint32_t
 */
uint32_t uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(uz_prng_t *self, uint32_t range);

/**
 * @brief Generate one uniform distributed uint32 in the interval [0,range), i.e., 0 up to but excluding "range". Uses float multiplication to scale and is biased according to https://www.pcg-random.org/posts/bounded-rands.html.
 *
 * @param self
 * @param range
 * @return uint32_t
 */
uint32_t uz_prng_get_uniform_uint32_zero_to_range_float_mult(uz_prng_t *self, uint32_t range);

/**
 * @brief Generate one uniform distributed uint32 in the interval [0,range), i.e., 0 up to but excluding "range". Uses integer multiplication to scale and is biased according to https://www.pcg-random.org/posts/bounded-rands.html.
 *
 * @param self
 * @param range
 * @return uint32_t
 */
uint32_t uz_prng_get_uniform_uint32_zero_to_range_int_mult(uz_prng_t *self, uint32_t range);

/**
 * @brief Returns true or false in a uniform distribution
 * 
 * @param self 
 * @return true 
 * @return false 
 */
bool uz_prng_get_uniform_bool(uz_prng_t *self);

/**
 * @brief Returns uniform distributed float values in the unit interval [0,1)
 * 
 * @param self 
 * @return float 
 */
float uz_prng_get_uniform_float_zero_to_one(uz_prng_t *self);

/**
 * @brief Returns uniform distributed float values in the unit (min,max). Min and max can be positive or negative, but max>min is required.
 *
 * @param self
 * @param min Lower bound of the interval
 * @param max Upper bound of the interval
 * @return float
 */
float uz_prng_get_uniform_float_min_to_max(uz_prng_t *self, float min, float max);

/**
 * @brief Resets the generator to given seed
 * 
 * @param self 
 * @param seed 
 */
void uz_prng_reset(uz_prng_t *self, uint64_t seed);

/**
 * @brief Generate normal distributed random float
 * 
 * @param self 
 * @param mean Mean value of the normal distribution
 * @param sigma Standard deviation of the normal distribution
 * @return float 
 */
float uz_prng_get_normal_float(uz_prng_t *self, float mean, float sigma);

#endif // UZ_PRNG_H
