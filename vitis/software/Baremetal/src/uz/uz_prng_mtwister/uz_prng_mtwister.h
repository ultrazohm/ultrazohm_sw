#ifndef UZ_PRNG_MTWISTER_H
#define UZ_PRNG_MTWISTER_H

#include <stdint.h>

/**
 * @brief Object of Mersenne Twister generator
 * 
 */
typedef struct uz_prng_mtwister_t uz_prng_mtwister_t;

/**
 * @brief Initializes the Mersenne Twister random number generator for a given random seed.
 *
 * @param random_seed Random seed of the generator. Output is deterministic and reproducible for each given seed.
 * @return uz_prng_mtwister_t*
 */
uz_prng_mtwister_t *uz_prng_mtwister_init(uint32_t random_seed);

/**
 * @brief Returns a uniformly distributed unsigned integer within 0...UINT32_MAX (i.e., 2^32-1=4,294,967,295)
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_prng_mtwister_get_uniform_uint32(uz_prng_mtwister_t *self);

#endif // UZ_PRNG_MTWISTER_H
