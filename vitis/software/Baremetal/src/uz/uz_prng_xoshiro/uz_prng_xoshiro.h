#ifndef UZ_PRNG_XOSHIRO_H
#define UZ_PRNG_XOSHIRO_H

#include <stdint.h>

/**
 * @brief Object of Xoshiro128++ generator
 *
 */
typedef struct uz_prng_xoshiro_t uz_prng_xoshiro_t;

/**
 * @brief Initializes the Xoshiro128++ random generator. The supplied Seed is shuffled using Splitmix64 to ensure that the lower bits are not zero.
 * 
 * @param seed Seed for the initial properties of the generator.
 * @return uz_prng_xoshiro_t* 
 */
uz_prng_xoshiro_t *uz_prng_xoshiro_init(uint64_t seed);

/**
 * @brief Returns a uniformly distributed unsigned integer within 0...UINT32_MAX (i.e., 2^32-1=4,294,967,295)
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_prng_xoshiro_get_uniform_uint32(uz_prng_xoshiro_t *self);

#endif // UZ_PRNG_XOSHIRO_H
