#ifndef UZ_PRNG_SQUARES_H
#define UZ_PRNG_SQUARES_H

#include <stdint.h>

/**
 * @brief Object of Squares generator
 *
 */
typedef struct uz_prng_squares_t uz_prng_squares_t;

/**
 * @brief Initializes the Squares random number generator.
 *
 * @param key Values 0-29 choose a key from https://squaresrng.wixsite.com/rand. Values >30 are directly set as key, only supply properly calculated custom key's.
 * @return uz_prng_squares_t*
 */
uz_prng_squares_t *uz_prng_squares_init(uint64_t key);

/**
 * @brief Returns a uniformly distributed unsigned integer within 0...UINT32_MAX (i.e., 2^32-1=4,294,967,295)
 *
 * @param self
 * @return uint32_t
 */
uint32_t uz_prng_squares_get_uniform_uint32(uz_prng_squares_t *self);

/**
 * @brief Resets generator to key
 * 
 * @param self 
 * @param key 
 */
void uz_prng_squares_reset(uz_prng_squares_t *self, uint64_t key);

#endif // UZ_PRNG_SQUARES_H
