
#include "uz_JL_SDDemod.h"
#include "uz_JL_SDDemod_hw.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_JL_SDDEMOD_MAX_INSTANCES > 0U
#include <stdbool.h> 

struct uz_JL_SDDemod_t {
    bool is_ready;
    struct uz_JL_SDDemod_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_JL_SDDemod_t instances[UZ_JL_SDDEMOD_MAX_INSTANCES] = { 0 };

static uz_JL_SDDemod_t* uz_JL_SDDemod_allocation(void);

static uz_JL_SDDemod_t* uz_JL_SDDemod_allocation(void){
    uz_assert(instance_counter < UZ_JL_SDDEMOD_MAX_INSTANCES);
    uz_JL_SDDemod_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_JL_SDDemod_t* uz_JL_SDDemod_init(struct uz_JL_SDDemod_config_t config) {
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    uz_assert(config.R_axi>0U);
    uz_JL_SDDemod_t* self = uz_JL_SDDemod_allocation();
    self->config = config;
    uz_JL_SDDemod_set_Raxi(self, config.R_axi);
    return (self);
}

 void uz_JL_SDDemod_set_Raxi(uz_JL_SDDemod_t *self, uint16_t R_axi)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SDDemod_hw_write_R_axi(self->config.base_address, R_axi);
}

struct uz_JL_SDDemod_output_t uz_JL_SDDemod_get_outputs(uz_JL_SDDemod_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_JL_SDDemod_output_t outputs = {
        .data = 0};
    outputs.data = uz_JL_SDDemod_hw_read_data(self->config.base_address);
    return outputs;
}
#endif
