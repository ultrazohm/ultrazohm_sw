#include "../../uz/uz_global_configuration.h"
#if UZ_MUX_AXI_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_mux_axi.h"
#include "uz_mux_axi_hw.h"

struct uz_mux_axi_t {
    bool is_ready;
    struct uz_mux_axi_config_t config;
    float max_delay_adc_trigger_in_us;
};

static uint32_t instance_counter = 0U;
static uz_mux_axi_t instances[UZ_MUX_AXI_MAX_INSTANCES] = { 0 };

static uz_mux_axi_t* uz_mux_axi_allocation(void);
static uint32_t calculate_delay_cycles_from_microseconds(uint32_t clock_frequency_Hz, float delay_in_microseconds);
static float calculate_microseconds_from_delay_cycles(uint32_t clock_frequency_Hz, uint32_t delay_cycles);

static uz_mux_axi_t* uz_mux_axi_allocation(void){
    uz_assert(instance_counter <UZ_MUX_AXI_MAX_INSTANCES);
    uz_mux_axi_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_mux_axi_t* uz_mux_axi_init(struct uz_mux_axi_config_t config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    uz_assert(config.mux<7U);
    uz_assert(config.n_th_interrupt<256U);
    uz_mux_axi_t* self = uz_mux_axi_allocation();
    self->config=config;
    self->max_delay_adc_trigger_in_us = calculate_microseconds_from_delay_cycles(self->config.ip_clk_frequency_Hz, UZ_MUX_AXI_HW_MAX_DELAY_CYCLES);
    uz_assert(config.delay_adc_trigger_in_us >= 0.0F);
    uz_assert(config.delay_adc_trigger_in_us <= self->max_delay_adc_trigger_in_us);
    uz_assert_not_zero(self->is_ready);
    uz_mux_axi_enable(self);
    uz_mux_axi_set_mux(self, self->config.mux);
    uz_mux_axi_set_n_th_interrupt(self, self->config.n_th_interrupt);
    uz_mux_axi_set_delay_adc_trigger_in_us(self, self->config.delay_adc_trigger_in_us);
    return (self);
}

void uz_mux_axi_enable(struct uz_mux_axi_t *self) {
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    uz_mux_axi_hw_enable_IP_core(self->config.base_address);
}

void uz_mux_axi_set_mux(struct uz_mux_axi_t *self, uint32_t mux) {
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.mux = mux;
    uz_mux_axi_hw_set_mux(self->config.base_address, mux);   
}

void uz_mux_axi_set_n_th_interrupt(struct uz_mux_axi_t *self, uint32_t n_th_interrupt) {
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    self->config.n_th_interrupt = n_th_interrupt;
    uz_mux_axi_hw_set_n_th_interrupt(self->config.base_address, n_th_interrupt);
}

void uz_mux_axi_set_delay_adc_trigger_in_us(struct uz_mux_axi_t *self, float delay_adc_trigger_in_us) {
    uz_assert_not_zero_uint32(self->config.base_address);
    uz_assert_not_zero(self->is_ready);
    uz_assert(delay_adc_trigger_in_us >= 0.0F);
    uz_assert(delay_adc_trigger_in_us <= self->max_delay_adc_trigger_in_us);
    const uint32_t delay_adc_trigger_in_clk_cycles = calculate_delay_cycles_from_microseconds(self->config.ip_clk_frequency_Hz, delay_adc_trigger_in_us);
    self->config.delay_adc_trigger_in_us = delay_adc_trigger_in_us;
    uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles(self->config.base_address, delay_adc_trigger_in_clk_cycles);
}

static uint32_t calculate_delay_cycles_from_microseconds(uint32_t clock_frequency_Hz, float delay_in_microseconds){
    uz_assert(delay_in_microseconds >= 0.0F);
    uz_assert_not_zero_uint32(clock_frequency_Hz);
    const float clk_us = 1.0e6F / (float) clock_frequency_Hz;
    const uint32_t delay_cycles = (uint32_t) ceilf(delay_in_microseconds / clk_us);
    uz_assert(delay_cycles <= UZ_MUX_AXI_HW_MAX_DELAY_CYCLES);
    return (delay_cycles);
}

static float calculate_microseconds_from_delay_cycles(uint32_t clock_frequency_Hz, uint32_t delay_cycles){
    uz_assert_not_zero_uint32(clock_frequency_Hz);
    const float clk_us = 1.0e6F / (float) clock_frequency_Hz;
    const float delay_in_us = clk_us * (float) delay_cycles;
    return (delay_in_us);
}
#endif
