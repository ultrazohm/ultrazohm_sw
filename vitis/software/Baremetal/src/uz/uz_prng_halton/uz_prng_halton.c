#include "uz_prng_halton.h"

#include "../uz_global_configuration.h"
#if UZ_PRNG_HALTON_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_halton.h"

struct uz_prng_halton_t
{
    bool is_ready;
    uint32_t base;
    uint32_t n_element;
};

static uint32_t instance_counter = 0U;
static uz_prng_halton_t instances[UZ_PRNG_HALTON_MAX_INSTANCES] = {0};

static uz_prng_halton_t *uz_prng_halton_allocation(void);

static uz_prng_halton_t *uz_prng_halton_allocation(void)
{
    uz_assert(instance_counter < UZ_PRNG_HALTON_MAX_INSTANCES);
    uz_prng_halton_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prng_halton_t *uz_prng_halton_init(uint32_t base)
{
    uz_prng_halton_t *self = uz_prng_halton_allocation();
    uz_assert(base > 1U);
    self->base = base;
    self->n_element = 0U;
    return (self);
}

// Implementation based on Wiki pseudo-code https://en.wikipedia.org/wiki/Halton_sequence#cite_note-Kc1997-1
float uz_prng_halton_get_uniform_float(uz_prng_halton_t *self)
{
    float f = 1.0f;
    float r = 0.0f;
    uint32_t i = self->n_element;
    while (i)
    {
        f = f / (float)self->base;
        r = r + f * (float)(i % self->base);
        i = i / self->base;
    }
    self->n_element++;
    return r;
}

#endif