#include "../../uz/uz_global_configuration.h"
#if UZ_PHASE_VOLTAGES_8_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_phase_voltages_8.h"
#include "uz_phase_voltages_8_hw.h"

struct uz_phase_voltages_8_t {
    bool is_ready;
    struct uz_phase_voltages_8_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_phase_voltages_8_t instances[UZ_PHASE_VOLTAGES_8_MAX_INSTANCES] = { 0 };

static uz_phase_voltages_8_t* uz_phase_voltages_8_allocation(void);

static uz_phase_voltages_8_t* uz_phase_voltages_8_allocation(void){
    uz_assert(instance_counter < UZ_PHASE_VOLTAGES_8_MAX_INSTANCES);
    uz_phase_voltages_8_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_phase_voltages_8_t* uz_phase_voltages_8_init(struct uz_phase_voltages_8_config_t config){
    uz_phase_voltages_8_t* self = uz_phase_voltages_8_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

    uz_phase_voltages_8_set_theta_el_offset(self->config.base_address, self->config.theta_el_offset);
    uz_phase_voltages_8_set_u_dc_link_voltage(self->config.base_address, self->config.u_dc_link_voltage);
   
    return (self);
}
/*
int32_t uz_phase_voltages_8_read_Index_in (uz_phase_voltages_8_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t Index = 0;
    Index = uz_phase_voltages_8_get_Index_in(self->config.base_address);

    return Index;
}

void uz_phase_voltages_8_set_set_done_delay_compensation_AXI(uz_phase_voltages_8_t* self, _Bool done_delay_compensation_AXI){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_phase_voltages_8_hw_set_done_delay_compensation_AXI(self->config.base_address, done_delay_compensation_AXI);
}
*/
#endif