// //#include "../../uz/uz_global_configuration.h"
// #define UZ_PLANTPT1_MAX_INSTANCES 6U
// #if UZ_PLANTPT1_MAX_INSTANCES > 0U
// #include <stdbool.h>
// #include "../../uz/uz_HAL.h"
// #include "uz_plantPT1.h"

// struct uz_plantPT1_t
// {
//     bool is_ready;
// };

// static size_t instance_counter = 0U;
// static uz_plantPT1_t instances[UZ_PLANTPT1_MAX_INSTANCES] = {0};

// static uz_plantPT1_t *uz_plantPT1_allocation(void);

// static uz_plantPT1_t *uz_plantPT1_allocation(void)
// {
//     uz_assert(instance_counter < UZ_PLANTPT1_MAX_INSTANCES);
//     uz_myIP_t *self = &instances[instance_counter];
//     uz_assert_false(self->is_ready);
//     instance_counter++;
//     self->is_ready = true;
//     return (self);
// }

// uz_plantPT1_t *uz_plantPT1_init()
// {
//     uz_plantPT1_t *self = uz_plantPT1_allocation();
//     return (self);
// }
// #endif