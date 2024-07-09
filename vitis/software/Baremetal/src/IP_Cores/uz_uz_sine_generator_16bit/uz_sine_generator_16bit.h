#ifndef UZ_SINE_GENERATOR_16BIT_H
#define UZ_SINE_GENERATOR_16BIT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct uz_sine_generator_16bit_t uz_sine_generator_16bit_t;

struct uz_sine_generator_16bit_config_t
{
    uint32_t base_address;                        /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_clk_frequency_Hz;                 /**< Clock frequency of IP-Core */
    float amplitude[8U];
    float phase[8U];
    float frequency[8U];
};

uz_sine_generator_16bit_t *uz_sine_generator_16bit_init(struct uz_sine_generator_16bit_config_t config);

#endif // UZ_SINE_GENERATOR_16BIT_H
