#include "uz_sine_generator_16bit.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_SINE_GENERATOR_16BIT_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_sine_generator_16bit.h"
#include "uz_sine_generator_16bit_hw.h"

struct uz_sine_generator_16bit_t {
    bool is_ready;
    struct uz_sine_generator_16bit_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_sine_generator_16bit_t instances[UZ_SINE_GENERATOR_16BIT_MAX_INSTANCES] = { 0 };

static uz_sine_generator_16bit_t* uz_sine_generator_16bit_allocation(void);

static uz_sine_generator_16bit_t* uz_sine_generator_16bit_allocation(void){
    uz_assert(instance_counter < UZ_SINE_GENERATOR_16BIT_MAX_INSTANCES);
    uz_sine_generator_16bit_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_sine_generator_16bit_t *uz_sine_generator_16bit_init(struct uz_sine_generator_16bit_config_t config)
{
    uz_sine_generator_16bit_t* self = uz_sine_generator_16bit_allocation();
    self->config=config;
    uz_sine_generator_16bit_hw_write_enable(self->config.base_address, false);

    uz_sine_generator_16bit_hw_write_amplitude_1(self->config.base_address, self->config.amplitude[0]);
    uz_sine_generator_16bit_hw_write_amplitude_2(self->config.base_address, self->config.amplitude[1]);
    uz_sine_generator_16bit_hw_write_amplitude_3(self->config.base_address, self->config.amplitude[2]);
    uz_sine_generator_16bit_hw_write_amplitude_4(self->config.base_address, self->config.amplitude[3]);
    uz_sine_generator_16bit_hw_write_amplitude_5(self->config.base_address, self->config.amplitude[4]);
    uz_sine_generator_16bit_hw_write_amplitude_6(self->config.base_address, self->config.amplitude[5]);
    uz_sine_generator_16bit_hw_write_amplitude_7(self->config.base_address, self->config.amplitude[6]);
    uz_sine_generator_16bit_hw_write_amplitude_8(self->config.base_address, self->config.amplitude[7]);

    uz_sine_generator_16bit_hw_write_phase_1(self->config.base_address, self->config.phase[0]);
    uz_sine_generator_16bit_hw_write_phase_2(self->config.base_address, self->config.phase[1]);
    uz_sine_generator_16bit_hw_write_phase_3(self->config.base_address, self->config.phase[2]);
    uz_sine_generator_16bit_hw_write_phase_4(self->config.base_address, self->config.phase[3]);
    uz_sine_generator_16bit_hw_write_phase_5(self->config.base_address, self->config.phase[4]);
    uz_sine_generator_16bit_hw_write_phase_6(self->config.base_address, self->config.phase[5]);
    uz_sine_generator_16bit_hw_write_phase_7(self->config.base_address, self->config.phase[6]);
    uz_sine_generator_16bit_hw_write_phase_8(self->config.base_address, self->config.phase[7]);

    uz_sine_generator_16bit_hw_write_frequency_1(self->config.base_address, self->config.frequency[0]);
    uz_sine_generator_16bit_hw_write_frequency_2(self->config.base_address, self->config.frequency[1]);
    uz_sine_generator_16bit_hw_write_frequency_3(self->config.base_address, self->config.frequency[2]);
    uz_sine_generator_16bit_hw_write_frequency_4(self->config.base_address, self->config.frequency[3]);
    uz_sine_generator_16bit_hw_write_frequency_5(self->config.base_address, self->config.frequency[4]);
    uz_sine_generator_16bit_hw_write_frequency_6(self->config.base_address, self->config.frequency[5]);
    uz_sine_generator_16bit_hw_write_frequency_7(self->config.base_address, self->config.frequency[6]);
    uz_sine_generator_16bit_hw_write_frequency_8(self->config.base_address, self->config.frequency[7]);

    uz_sine_generator_16bit_hw_write_reset(self->config.base_address, true);
    uz_sine_generator_16bit_hw_write_reset(self->config.base_address, false);
    uz_sine_generator_16bit_hw_write_enable(self->config.base_address, true);

    return (self);
}

#endif