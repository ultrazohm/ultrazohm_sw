#include "../../uz/uz_global_configuration.h"
#if UZ_VSD_8_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_vsd_8.h"
#include "uz_vsd_8_hw.h"

struct uz_vsd_8_t {
    bool is_ready;
    struct uz_vsd_8_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_vsd_8_t instances[UZ_VSD_8_MAX_INSTANCES] = { 0 };

static uz_vsd_8_t* uz_vsd_8_allocation(void);

static uz_vsd_8_t* uz_vsd_8_allocation(void){
    uz_assert(instance_counter < UZ_VSD_8_MAX_INSTANCES);
    uz_vsd_8_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_vsd_8_t* uz_vsd_8_init(struct uz_vsd_8_config_t config){
    uz_vsd_8_t* self = uz_vsd_8_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
    uz_vsd_8_hw_set_thetaOffset(self->config.base_address, self->config.theta_offset);
    return (self);
}

uz_6ph_abc_t uz_vsd_8_get_ia1_ib1_ic1_ia2_ib2_ic2(uz_vsd_8_t* self) {

    uz_assert_not_NULL(self);
    uz_6ph_abc_t currents = { 0 };

    currents.a1 = uz_vsd_8_hw_get_i_a1(self->config.base_address);
    currents.b1 = uz_vsd_8_hw_get_i_b1(self->config.base_address);
    currents.c1 = uz_vsd_8_hw_get_i_c1(self->config.base_address);
    currents.a2 = uz_vsd_8_hw_get_i_a2(self->config.base_address);
    currents.b2 = uz_vsd_8_hw_get_i_b2(self->config.base_address);
    currents.c2 = uz_vsd_8_hw_get_i_c2(self->config.base_address);

    return currents;
}

uz_3ph_dq_t uz_vsd_and_park_8_transformation_6phase_get_id_iq(uz_vsd_8_t* self) {

    uz_assert_not_NULL(self);
    uz_3ph_dq_t currents = { 0 };

    currents.d = uz_vsd_and_park_8_transformation_6phase_hw_get_i_d(self->config.base_address);
    currents.q = uz_vsd_and_park_8_transformation_6phase_hw_get_i_q(self->config.base_address);

    return currents;
}


#endif
