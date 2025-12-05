#include "../uz_global_configuration.h"
#if UZ_BUCK_CONTROL_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "/uz_HAL.h"
#include "uz_buck_control_h" 

struct uz_buck_control_t {
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_buck_control_t instances[UZ_BUCK_CONTROL_MAX_INSTANCES] = { 0 };

static uz_buck_control_t* uz_buck_control_allocation(void);

static uz_buck_control_t* uz_buck_control_allocation(void){
    uz_assert(instance_counter < UZ_BUCK_CONTROL_
    MAX_INSTANCES);
    uz_buck_control_
t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_buck_control_t* uz_buck_control_init() {
    uz_buck_control_
t* self = uz_buck_control_
allocation();
    return (self);
}
#endif