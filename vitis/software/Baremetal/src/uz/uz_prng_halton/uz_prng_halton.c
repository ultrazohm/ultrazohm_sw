#include "uz_prng_halton.h"

#include "../uz_global_configuration.h"
#if UZ_PRNG_HALTON_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_halton.h"
#include <stdbool.h>
struct uz_prng_halton_t
{
    bool is_ready;
    uint32_t base;
    uint32_t n_element;
};

static uint32_t instance_counter = 0U;
static uz_prng_halton_t instances[UZ_PRNG_HALTON_MAX_INSTANCES] = {0};

static uz_prng_halton_t *uz_prng_halton_allocation(void);
static float get_uniform_float(uint32_t i_th_element, uint32_t base);

static uz_prng_halton_t *uz_prng_halton_allocation(void)
{
    uz_assert(instance_counter < UZ_PRNG_HALTON_MAX_INSTANCES);
    uz_prng_halton_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prng_halton_t *uz_prng_halton_init(uint32_t base_prime)
{
    uz_prng_halton_t *self = uz_prng_halton_allocation();
    uz_assert(base_prime > 1U);
    self->base = base_prime;
    self->n_element = 100U; // Arbitrarily skips the first 100 numbers since Wikipedia states that for some bases, the first elements can be correlated in the n-d case
    return (self);
}

float uz_prng_halton_get_uniform_float(uz_prng_halton_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float r = get_uniform_float(self->n_element, self->base);
    self->n_element++;
    return r;
}

void uz_prng_halton_get_uniform_float_2d(uz_prng_halton_t *self, float *x, float *y)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    *x = get_uniform_float(self->n_element, 3U); // Hardcoded prime numbers for 2d case
    *y = get_uniform_float(self->n_element, 5U);
    self->n_element++;
}

// Implementation based on Wiki pseudo-code https://en.wikipedia.org/wiki/Halton_sequence#cite_note-Kc1997-1
static float get_uniform_float(uint32_t i_th_element, uint32_t base)
{
    float f = 1.0f;
    float r = 0.0f;
    while (i_th_element)
    {
        f = f / (float)base;
        r = r + f * (float)(i_th_element % base);
        i_th_element = i_th_element / base;
    }
    return r;
}

#endif