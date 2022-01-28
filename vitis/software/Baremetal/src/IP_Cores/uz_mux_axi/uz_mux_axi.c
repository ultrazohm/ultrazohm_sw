#include "../../uz/uz_global_configuration.h"
#if UZ_MUX_AXI_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_mux_axi.h"
#include "uz_mux_axi_hw.h"

struct uz_mux_axi_t {
    bool is_ready;
    struct uz_mux_axi_config_t config;
};

static size_t instance_counter = 0U;
static uz_mux_axi_t instances[UZ_MUX_AXI_MAX_INSTANCES] = { 0 };

static uz_mux_axi_t* uz_mux_axi_allocation(void);

static uz_mux_axi_t* uz_mux_axi_allocation(void){
    uz_assert(instance_counter <UZ_MUX_AXI_MAX_INSTANCES);
    uz_mux_axi_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_mux_axi_t* uz_mux_axi_init(struct uz_mux_axi_config_t config) {
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_clk_frequency_Hz);
    uz_mux_axi_t* self = uz_mux_axi_allocation();
    self->config=config;
    uz_assert_not_zero(self->is_ready);
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
#endif