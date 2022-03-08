#include "../../uz/uz_global_configuration.h"
#if UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_dq_transformation.h"
#include "uz_dq_transformation_hw.h"
struct uz_dqIPcore_t {
    bool is_ready;
    struct uz_dqIPcore_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_dqIPcore_t instances[UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES] = { 0 };

static uz_dqIPcore_t* uz_dqIPcore_allocation(void);

static uz_dqIPcore_t* uz_dqIPcore_allocation(void){
    uz_assert(instance_counter < UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES);
    uz_dqIPcore_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}


uz_dqIPcore_t* uz_dqIPcore_init(struct uz_dqIPcore_config_t config){
    uz_dqIPcore_t* self = uz_dqIPcore_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
    uz_dqTransformation_hw_set_thetaOffset(self->config.base_address, self->config.theta_offset);
    return (self);
}

uz_3ph_dq_t uz_dqIPcore_get_id_iq(uz_dqIPcore_t* self) {

    uz_3ph_dq_t currents = { 0 };

    currents.d = uz_dqTransformation_hw_get_id(self->config.base_address);
    currents.q = uz_dqTransformation_hw_get_iq(self->config.base_address);

    return currents;
}

uz_3ph_abc_t uz_dqIPcore_get_i_uvw(uz_dqIPcore_t* self) {

    uz_assert_not_NULL(self);
	uz_3ph_abc_t currents = { 0 };

    currents.a = uz_dqTransformation_hw_get_i1(self->config.base_address);
    currents.b = uz_dqTransformation_hw_get_i2(self->config.base_address);
    currents.c = uz_dqTransformation_hw_get_i3(self->config.base_address);

    return currents;
}

#endif
