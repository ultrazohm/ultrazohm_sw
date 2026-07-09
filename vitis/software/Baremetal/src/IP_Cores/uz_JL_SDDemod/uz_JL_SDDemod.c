
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
    uz_assert(config.dezimation_U>0U);
    uz_assert(config.dezimation_I>0U);
    uz_assert(config.clk_ratio>0U);
    uz_JL_SDDemod_t* self = uz_JL_SDDemod_allocation();
    self->config = config;
    uz_JL_SDDemod_set_dezimation(self, config.dezimation_U, config.dezimation_I);
    uz_JL_SDDemod_set_clk_ratio(self, config.clk_ratio);
    uz_JL_SDDemod_set_switch_edge(self, config.switch_edge);
    return (self);
}

 void uz_JL_SDDemod_set_dezimation(uz_JL_SDDemod_t *self, uint16_t dezimation_U, uint16_t dezimation_I)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SDDemod_hw_write_dezi_U(self->config.base_address, dezimation_U);
    uz_JL_SDDemod_hw_write_dezi_I(self->config.base_address, dezimation_I);
}

 void uz_JL_SDDemod_set_clk_ratio(uz_JL_SDDemod_t *self, uint16_t clk_ratio)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SDDemod_hw_write_clk_ratio(self->config.base_address, clk_ratio);
}

 void uz_JL_SDDemod_set_switch_edge(uz_JL_SDDemod_t *self, bool switch_edge)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SDDemod_hw_write_switch_edge(self->config.base_address, switch_edge);
}

struct uz_JL_SDDemod_output_t uz_JL_SDDemod_get_outputs(uz_JL_SDDemod_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_JL_SDDemod_output_t outputs = {
        .data_U = 0,
        .data_PH1 = 0,
        .data_PH2 = 0,
        .data_PH3 = 0,
        .data_PH4 = 0
    };
    outputs.data_U = uz_JL_SDDemod_hw_read_data_out_ps_U(self->config.base_address);
    outputs.data_PH1 = uz_JL_SDDemod_hw_read_data_out_ps_PH1(self->config.base_address);
    outputs.data_PH2 = uz_JL_SDDemod_hw_read_data_out_ps_PH2(self->config.base_address);
    outputs.data_PH3 = uz_JL_SDDemod_hw_read_data_out_ps_PH3(self->config.base_address);
    outputs.data_PH4 = uz_JL_SDDemod_hw_read_data_out_ps_PH4(self->config.base_address);
    return outputs;
}
#endif
