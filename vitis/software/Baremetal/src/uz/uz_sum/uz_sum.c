#include "uz_sum.h"

#include "../../uz_global_configuration.h"

#if UZ_SUM_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz_HAL.h"
#include "uz_sum.h" 

struct uz_sum_t {
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_sum_t instances[UZ_SUM_MAX_INSTANCES] = { 0 };

static uz_sum_t* uz_sum_allocation(void);

static uz_sum_t* uz_sum_allocation(void){
    uz_assert(instance_counter < UZ_SUM_MAX_INSTANCES);
    uz_sum_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_sum_t* uz_sum_init() {
    uz_sum_t* self = uz_sum_allocation();
    return (self);
}

#endif