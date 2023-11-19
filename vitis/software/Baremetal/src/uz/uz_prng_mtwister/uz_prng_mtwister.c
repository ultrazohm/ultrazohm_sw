/* An implementation of the MT19937 Algorithm for the Mersenne Twister
 * by Evan Sultanik.  Based upon the pseudocode in: M. Matsumoto and
 * T. Nishimura, "Mersenne Twister: A 623-dimensionally
 * equidistributed uniform pseudorandom number generator," ACM
 * Transactions on Modeling and Computer Simulation Vol. 8, No. 1,
 * January pp.3-30 1998.
 *
 * http://www.sultanik.com/Mersenne_twister
 * https://github.com/ESultanik/mtwister/tree/master
 */
#include "../uz_global_configuration.h"
#if UZ_MTWISTER_MAX_INSTANCES > 0U

#include <math.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_mtwister.h"
#include "mt19937.h"

struct uz_prng_mtwister_t
{
    bool is_ready;
    uint32_t seed;
    struct _ORG_STATE state;
};


static uint32_t instance_counterrand = 0U;
static uz_prng_mtwister_t instancesrand[UZ_MTWISTER_MAX_INSTANCES] = {0};
static uz_prng_mtwister_t *uz_prng_mtwister_allocation(void);

static uz_prng_mtwister_t *uz_prng_mtwister_allocation(void)
{
    uz_assert(instance_counterrand < UZ_MTWISTER_MAX_INSTANCES);
    uz_prng_mtwister_t *self = &instancesrand[instance_counterrand];
    uz_assert_false(self->is_ready);
    instance_counterrand++;
    self->is_ready = true;
    return (self);
}

uz_prng_mtwister_t *uz_prng_mtwister_init(uint32_t random_seed)
{
    uz_prng_mtwister_t *self = uz_prng_mtwister_allocation();
    self->seed = random_seed;
    _sgenrand_dc(&self->state,random_seed);
    return (self);
}

uint32_t uz_prng_mtwister_get_uniform_uint32(uz_prng_mtwister_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return _genrand_dc(&self->state);
}

#endif // UZ_MTWISTER_H