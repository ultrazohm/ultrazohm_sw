#include "../../uz/uz_global_configuration.h"
#if UZ_SWITCHING_STATES_6PHASE_8_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_switching_states_6Phase_8.h"
#include "uz_switching_states_6Phase_8_hw.h"

struct uz_switching_states_6Phase_8_t {
    bool is_ready;
    struct uz_switching_states_6Phase_8_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_switching_states_6Phase_8_t instances[UZ_SWITCHING_STATES_6PHASE_8_MAX_INSTANCES] = { 0 };

static uz_switching_states_6Phase_8_t* uz_switching_states_6Phase_8_allocation(void);

static uz_switching_states_6Phase_8_t* uz_switching_states_6Phase_8_allocation(void){
    uz_assert(instance_counter < UZ_SWITCHING_STATES_6PHASE_8_MAX_INSTANCES);
    uz_switching_states_6Phase_8_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_switching_states_6Phase_8_t* uz_switching_states_6Phase_8_init(struct uz_switching_states_6Phase_8_config_t config){
    uz_switching_states_6Phase_8_t* self = uz_switching_states_6Phase_8_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
   
    return (self);
}

int32_t uz_switching_states_6Phase_8_read_Index_in (uz_switching_states_6Phase_8_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t Index = 0;
    Index = uz_switching_states_6Phase_8_get_min_Index_(self->config.base_address);

    return Index;
}

#endif