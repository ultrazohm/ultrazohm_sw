#include "../../uz/uz_global_configuration.h"
#if UZ_DELAY_COMPENSATION_8_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_delay_compensation_8.h"
#include "uz_delay_compensation_8_hw.h"

struct uz_delay_compensation_8_t {
    bool is_ready;
    struct uz_delay_compensation_8_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_delay_compensation_8_t instances[UZ_DELAY_COMPENSATION_8_MAX_INSTANCES] = { 0 };

static uz_delay_compensation_8_t* uz_delay_compensation_8_allocation(void);

static uz_delay_compensation_8_t* uz_delay_compensation_8_allocation(void){
    uz_assert(instance_counter < UZ_DELAY_COMPENSATION_8_MAX_INSTANCES);
    uz_delay_compensation_8_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_delay_compensation_8_t* uz_delay_compensation_8_init(struct uz_delay_compensation_8_config_t config){
    uz_delay_compensation_8_t* self = uz_delay_compensation_8_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;

    uz_delay_compensation_8_set_psiPM(self->config.base_address, self->config.psiPM);
    uz_delay_compensation_8_set_Lq(self->config.base_address, self->config.Lq);
    uz_delay_compensation_8_set_Ld(self->config.base_address, self->config.Ld);
    uz_delay_compensation_8_set_Rs(self->config.base_address, self->config.Rs);
    uz_delay_compensation_8_set_SampleTime_div_Ld(self->config.base_address, self->config.SampleTime, self->config.Ld);
    uz_delay_compensation_8_set_pole_pairs(self->config.base_address, self->config.pole_pairs);
    uz_delay_compensation_8_set_SampleTime_div_Lq(self->config.base_address, self->config.SampleTime, self->config.Lq);
    uz_delay_compensation_8_set_SampleTime_div_Lx(self->config.base_address, self->config.SampleTime, self->config.Lx);
    uz_delay_compensation_8_set_SampleTime_div_Ly(self->config.base_address, self->config.SampleTime, self->config.Ly);
    return (self);
}
/*
uz_6ph_idk1_iqk1_ixk1_iyk1_t uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1(uz_delay_compensation_8_t* self){

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_6ph_idk1_iqk1_ixk1_iyk1_t currents = {0};

    currents.id_k_1 = uz_delay_compensation_8_get_id_k_1(self->config.base_address);
    currents.iq_k_1 = uz_delay_compensation_8_get_iq_k_1(self->config.base_address);
    currents.ix_k_1 = uz_delay_compensation_8_get_ix_k_1(self->config.base_address);
    currents.iy_k_1 = uz_delay_compensation_8_get_iy_k_1(self->config.base_address);

    return currents;
}
*/
#endif