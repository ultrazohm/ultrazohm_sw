#include "uz_parameterid_rs.h"

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_RS_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_parameterid_rs.h" 

struct uz_parameterid_rs_t {
    bool is_ready;
    struct uz_parameterid_rs_config_t internal_config;
    struct uz_parameterid_rs_increments_t calc_increments;

};

static uint32_t instance_counter = 0U;
static uz_parameterid_rs_t instances[UZ_PARAMETERID_RS_MAX_INSTANCES] = { 0 };

static uz_parameterid_rs_t* uz_parameterid_rs_allocation(void);

static uz_parameterid_rs_t* uz_parameterid_rs_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_RS_MAX_INSTANCES);
    uz_parameterid_rs_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_parameterid_rs_t* uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config)
{
    uz_parameterid_rs_t* self = uz_parameterid_rs_allocation();
    self->internal_config = initial_config;
    self->calc_increments.n_increment = (initial_config.n_end - initial_config.n_start)/initial_config.n_steps;
    self->calc_increments.i_increment = (initial_config.i_end - initial_config.i_start)/initial_config.i_steps;
	uz_assert(initial_config.n_start > 0.0f);
	uz_assert(initial_config.n_end > 0.0f);
	uz_assert(initial_config.n_end > initial_config.n_start);
	uz_assert(initial_config.n_steps > 0.0f);
	uz_assert(initial_config.i_start > 0.0f);
	uz_assert(initial_config.i_end > 0.0f);
	uz_assert(initial_config.i_end > initial_config.i_start);
	uz_assert(initial_config.i_steps > 0.0f);
    return (self);
}

struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->internal_config;
}

struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->calc_increments;
}




#endif



