#include "../../uz/uz_global_configuration.h"
#if UZ_VSD_AND_PARK_TRANSFORMATION_6PHASE_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_vsd_and_park_transformation_6phase.h"
#include "uz_vsd_and_park_transformation_6phase_hw.h"

struct uz_vsd_and_park_transformation_6phase_t {
    bool is_ready;
    struct uz_vsd_and_park_transformation_6phase_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_vsd_and_park_transformation_6phase_t instances[UZ_VSD_AND_PARK_TRANSFORMATION_6PHASE_MAX_INSTANCES] = { 0 };

static uz_vsd_and_park_transformation_6phase_t* uz_vsd_and_park_transformation_6phase_allocation(void);

static uz_vsd_and_park_transformation_6phase_t* uz_vsd_and_park_transformation_6phase_allocation(void){
    uz_assert(instance_counter < UZ_VSD_AND_PARK_TRANSFORMATION_6PHASE_MAX_INSTANCES);
    uz_vsd_and_park_transformation_6phase_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_vsd_and_park_transformation_6phase_t* uz_vsd_and_park_transformation_6phase_init(struct uz_vsd_and_park_transformation_6phase_config_t config){
    uz_vsd_and_park_transformation_6phase_t* self = uz_vsd_and_park_transformation_6phase_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
    uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset(self->config.base_address, self->config.theta_offset);
    return (self);
}

uz_3ph_dq_t uz_vsd_and_park_transformation_6phase_get_id_iq(uz_vsd_and_park_transformation_6phase_t* self) {

    uz_assert_not_NULL(self);
    uz_3ph_dq_t currents = { 0 };

    currents.d = uz_vsd_and_park_transformation_6phase_hw_get_i_d(self->config.base_address);
    currents.q = uz_vsd_and_park_transformation_6phase_hw_get_i_q(self->config.base_address);

    return currents;
}

uz_6ph_alphabeta_t uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(uz_vsd_and_park_transformation_6phase_t* self) {

    uz_assert_not_NULL(self);
    uz_6ph_alphabeta_t currents = { 0 };

    currents.alpha = uz_vsd_and_park_transformation_6phase_hw_get_i_alpha(self->config.base_address);
    currents.beta = uz_vsd_and_park_transformation_6phase_hw_get_i_beta(self->config.base_address);
    currents.x = uz_vsd_and_park_transformation_6phase_hw_get_i_x(self->config.base_address);
    currents.y = uz_vsd_and_park_transformation_6phase_hw_get_i_y(self->config.base_address);
    currents.z1 = uz_vsd_and_park_transformation_6phase_hw_get_i_0_plus(self->config.base_address);
    currents.z2 = uz_vsd_and_park_transformation_6phase_hw_get_i_0_minus(self->config.base_address);

    return currents;
}

#endif