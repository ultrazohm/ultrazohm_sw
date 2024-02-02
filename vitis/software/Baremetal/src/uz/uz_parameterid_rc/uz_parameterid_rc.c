#include "uz_parameterid_rc.h"

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_RC_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_parameterid_rc.h" 

struct uz_parameterid_rc_t{
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_parameterid_rc_t instances[UZ_PARAMETERID_RC_MAX_INSTANCES] = { 0 };

static uz_parameterid_rc_t* uz_parameterid_rc_allocation(void);

static uz_parameterid_rc_t* uz_parameterid_rc_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_RC_MAX_INSTANCES);
    uz_parameterid_rc_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_parameterid_rc_t* uz_parameterid_rc_init() {
    uz_parameterid_rc_t* self = uz_parameterid_rc_allocation();
    return (self);
}
#endif