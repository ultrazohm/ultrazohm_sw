
#include "uz_JL_SigmaDelta_Interface.h"
#include "uz_JL_SigmaDelta_Interface_hw.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_JL_SigmaDelta_Interface_MAX_INSTANCES > 0U
#include <stdbool.h> 

struct uz_JL_SigmaDelta_Interface_t {
    bool is_ready;
    struct uz_JL_SigmaDelta_Interface_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_JL_SigmaDelta_Interface_t instances[UZ_JL_SigmaDelta_Interface_MAX_INSTANCES] = { 0 };

static uz_JL_SigmaDelta_Interface_t* uz_JL_SigmaDelta_Interface_allocation(void);

static uz_JL_SigmaDelta_Interface_t* uz_JL_SigmaDelta_Interface_allocation(void){
    uz_assert(instance_counter < UZ_JL_SigmaDelta_Interface_MAX_INSTANCES);
    uz_JL_SigmaDelta_Interface_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static void write_config_to_pl(uz_JL_SigmaDelta_Interface_t *self);

uz_JL_SigmaDelta_Interface_t* uz_JL_SigmaDelta_Interface_init(struct uz_JL_SigmaDelta_Interface_config_t config) {
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    uz_assert(config.dezimation>0U);
    uz_assert(config.clk_ratio>0U);
    uz_JL_SigmaDelta_Interface_t* self = uz_JL_SigmaDelta_Interface_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

static void write_config_to_pl(uz_JL_SigmaDelta_Interface_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_clk_ratio(self->config.base_address, self->config.clk_ratio);
    uz_JL_SigmaDelta_Interface_hw_write_data_delay(self->config.base_address, self->config.filt_input_delay);
    uz_JL_SigmaDelta_Interface_hw_write_switch_edge(self->config.base_address, self->config.switch_edge);
    uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc(self->config.base_address, self->config.switch_cont_disc);
    uz_JL_SigmaDelta_Interface_hw_write_dezimation(self->config.base_address, self->config.dezimation);
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle(self->config.base_address, self->config.clk_dutycycle);
    uz_JL_SigmaDelta_Interface_hw_write_start_time_us(self->config.base_address, self->config.start_time_us);
    uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid(self->config.base_address, self->config.delay_data_valid);
    uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods(self->config.base_address, self->config.sinc_sample_periods);
    uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext(self->config.base_address, self->config.use_clk_ext);
}

void uz_JL_SigmaDelta_Interface_set_data_delay(uz_JL_SigmaDelta_Interface_t *self, uint8_t filt_input_delay)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_data_delay(self->config.base_address, filt_input_delay);
}

void uz_JL_SigmaDelta_Interface_set_switch_edge(uz_JL_SigmaDelta_Interface_t *self, uint8_t switch_edge)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_switch_edge(self->config.base_address, switch_edge);
}

void uz_JL_SigmaDelta_Interface_set_switch_cont_disc(uz_JL_SigmaDelta_Interface_t *self, bool switch_cont_disc)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc(self->config.base_address, switch_cont_disc);
}

void uz_JL_SigmaDelta_Interface_set_clk_dutycycle(uz_JL_SigmaDelta_Interface_t *self, float dutycycle)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle(self->config.base_address, dutycycle);
}

void uz_JL_SigmaDelta_Interface_set_delay_data_valid(uz_JL_SigmaDelta_Interface_t *self, uint8_t delay_data_valid)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid(self->config.base_address, delay_data_valid);
}

void uz_JL_SigmaDelta_Interface_set_sinc_sample_periods(uz_JL_SigmaDelta_Interface_t *self, uint8_t sinc_sample_periods)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods(self->config.base_address, sinc_sample_periods);
}

void uz_JL_SigmaDelta_Interface_set_use_clk_ext(uz_JL_SigmaDelta_Interface_t *self, bool use_clk_ext)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext(self->config.base_address, use_clk_ext);
}

bool uz_JL_SigmaDelta_Interface_is_data_valid(uz_JL_SigmaDelta_Interface_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_JL_SigmaDelta_Interface_hw_read_data_valid(self->config.base_address);
}

void uz_JL_SigmaDelta_Interface_reset_data_valid_cnt(uz_JL_SigmaDelta_Interface_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_SigmaDelta_Interface_hw_reset_data_valid_cnt(self->config.base_address);
}

uint8_t uz_JL_SigmaDelta_Interface_get_data_valid_cnt(uz_JL_SigmaDelta_Interface_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_JL_SigmaDelta_Interface_hw_read_data_valid_cnt(self->config.base_address);
}

struct uz_JL_SigmaDelta_Interface_output_t uz_JL_SigmaDelta_Interface_get_outputs(uz_JL_SigmaDelta_Interface_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_JL_SigmaDelta_Interface_output_t outputs = {
        .data_U = 0,
        .data_PH1 = 0,
        .data_PH2 = 0,
        .data_PH3 = 0,
        .data_PH4 = 0
    };
    

    uz_JL_SigmaDelta_Interface_hw_trigger_output_strobe(self->config.base_address);
    outputs.data_U = uz_JL_SigmaDelta_Interface_hw_read_data_out_U(self->config.base_address);
    outputs.data_PH1 = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH1(self->config.base_address);
    outputs.data_PH2 = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH2(self->config.base_address);
    outputs.data_PH3 = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH3(self->config.base_address);
    outputs.data_PH4 = uz_JL_SigmaDelta_Interface_hw_read_data_out_PH4(self->config.base_address);
    return outputs;
}
#endif
