#include "../../uz/uz_global_configuration.h"
#if UZ_DQ_TRANSFORMATION_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_dq_transformation.h" 
struct uz_dq_transformation_t {
    bool is_ready;
};

static size_t instance_counter = 0U;
static uz_dq_transformation_t instances[UZ_DQ_TRANSFORMATION_MAX_INSTANCES] = { 0 };

static uz_dq_transformation_t* uz_dq_transformation_allocation(void);

static uz_dq_transformation_t* uz_dq_transformation_allocation(void){
    uz_assert(instance_counter < UZ_DQ_TRANSFORMATION_MAX_INSTANCES);
    uz_dq_transformation_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_dq_transformation_t* uz_dq_transformation_init() {
    uz_dq_transformation_t* self = uz_dq_transformation_allocation();
    return (self);
}
#endif