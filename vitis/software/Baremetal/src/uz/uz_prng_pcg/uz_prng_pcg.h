#ifndef UZ_PRNG_PCG_H
#define UZ_PRNG_PCG_H

#include <stdint.h>

/**
 * @brief Object of PCG generator
 *
 */
typedef struct uz_prng_pcg_t uz_prng_pcg_t;

/**
 * @brief  Initializes the PCG number generator for a given random seed. Internally, there is a second value that determines the random stream, which is arbitrarily fixed.
 *
 * @param seed  Random seed of the generator. Output is deterministic and reproducible for each given seed.
 * @return uz_prng_pcg_t*
 */
uz_prng_pcg_t *uz_prng_pcg_init(uint64_t seed);

/**
 * @brief Returns a uniformly distributed unsigned integer within 0...UINT32_MAX (i.e., 2^32-1=4,294,967,295)
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_prng_pcg_get_uniform_uint32(uz_prng_pcg_t *self);

#endif // UZ_PRNG_PCG_H
