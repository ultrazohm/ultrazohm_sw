#include "../../uz/uz_global_configuration.h"
#if UZ_TRANS_DQ_ALPHABETA_123_IP_CORE_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_trans_dq_alphabeta_123.h"
#include "uz_trans_dq_alphabeta_123_hw.h"

struct uz_dq_alphabeta_123_IPcore_t {
    bool is_ready;
    struct uz_dq_alphabeta_123_IPcore_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_dq_alphabeta_123_IPcore_t instances[UZ_TRANS_DQ_ALPHABETA_123_IP_CORE_MAX_INSTANCES] = { 0 };

static uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_allocation(void);

static uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_allocation(void){
    uz_assert(instance_counter < UZ_TRANS_DQ_ALPHABETA_123_IP_CORE_MAX_INSTANCES);
    uz_dq_alphabeta_123_IPcore_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_dq_alphabeta_123_IPcore_t* uz_dq_alphabeta_123_IPcore_init(struct uz_dq_alphabeta_123_IPcore_config_t config){
    uz_dq_alphabeta_123_IPcore_t* self = uz_dq_alphabeta_123_IPcore_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
    uz_trans_dq_alphabeta_123_hw_set_thetaOffset(self->config.base_address, self->config.theta_offset);
    uz_trans_dq_alphabeta_123_hw_set_idref(self->config.base_address, self->config.id_ref);
    uz_trans_dq_alphabeta_123_hw_set_iqref(self->config.base_address, self->config.iq_ref);
    return (self);
}

void uz_dq_alphabeta_123_IPcore_idref_iqref_update(uz_dq_alphabeta_123_IPcore_t* self, uz_3ph_dq_t updated_values){
 
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_trans_dq_alphabeta_123_hw_set_idref(self->config.base_address, updated_values.d);
    uz_trans_dq_alphabeta_123_hw_set_iqref(self->config.base_address, updated_values.q);
}

uz_3ph_abc_t uz_dq_alphabeta_123_IPcore_get_i_abc(uz_dq_alphabeta_123_IPcore_t* self) {

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	uz_3ph_abc_t currents = { 0 };

    currents.a =  uz_trans_dq_alphabeta_123_hw_get_i1(self->config.base_address);
    currents.b = uz_trans_dq_alphabeta_123_hw_get_i2(self->config.base_address);
    currents.c = uz_trans_dq_alphabeta_123_hw_get_i3(self->config.base_address);

    return currents;
}

uz_3ph_alphabeta_t uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta(uz_dq_alphabeta_123_IPcore_t* self) {

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_3ph_alphabeta_t currents = { 0 };

    currents.alpha = uz_trans_dq_alphabeta_123_hw_get_ialpha(self->config.base_address);
    currents.beta = uz_trans_dq_alphabeta_123_hw_get_ibeta(self->config.base_address);
    return currents;
}

#endif