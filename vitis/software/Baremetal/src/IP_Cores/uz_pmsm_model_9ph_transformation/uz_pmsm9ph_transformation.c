#include "../../uz/uz_global_configuration.h"
#if UZ_PMSM9PH_TRANSFORMATION_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_pmsm9ph_transformation.h" 
#include "uz_pmsm9ph_transformation_hw.h"

struct uz_pmsm9ph_transformation_t {
    bool is_ready;
    struct uz_pmsm9ph_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_pmsm9ph_transformation_t instances[UZ_PMSM9PH_TRANSFORMATION_MAX_INSTANCES] = { 0 };

static uz_pmsm9ph_transformation_t* uz_pmsm9ph_transformation_allocation(void);

static uz_pmsm9ph_transformation_t* uz_pmsm9ph_transformation_allocation(void){
    uz_assert(instance_counter < UZ_PMSM9PH_TRANSFORMATION_MAX_INSTANCES);
    uz_pmsm9ph_transformation_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_pmsm9ph_transformation_t* uz_pmsm9ph_transformation_init(struct uz_pmsm9ph_config_t config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_pmsm9ph_transformation_t* self = uz_pmsm9ph_transformation_allocation();
    self->config=config;
    return (self);
}

uz_9ph_abc_t uz_pmsm9ph_transformation_get_currents(uz_pmsm9ph_transformation_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_pmsm9ph_transformation_hw_read_currents(self->config.base_address);
}

float uz_pmsm9ph_transformation_get_theta_el(uz_pmsm9ph_transformation_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_pmsm9ph_transformatoin_hw_read_theta_el(self->config.base_address);
}


#endif