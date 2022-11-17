#include "../../uz/uz_global_configuration.h"
#if UZ_MIN_COST_FUNCTION_8_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_min_cost_function_8.h"
#include "uz_min_cost_function_8_hw.h"

struct uz_min_cost_function_8_t {
    bool is_ready;
    struct uz_min_cost_function_8_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_min_cost_function_8_t instances[UZ_MIN_COST_FUNCTION_8_MAX_INSTANCES] = { 0 };

static uz_min_cost_function_8_t* uz_min_cost_function_8_allocation(void);

static uz_min_cost_function_8_t* uz_min_cost_function_8_allocation(void){
    uz_assert(instance_counter < UZ_MIN_COST_FUNCTION_8_MAX_INSTANCES);
    uz_min_cost_function_8_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_min_cost_function_8_t* uz_min_cost_function_8_init(struct uz_min_cost_function_8_config_t config){
    uz_min_cost_function_8_t* self = uz_min_cost_function_8_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
   return (self);
}
/*
int32_t uz_min_cost_function_8_read_Index_out(uz_min_cost_function_8_t* self){
    
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t Index_out = 0;

    Index_out = uz_min_cost_function_8_hw_get_Index_out_AXI(self->config.base_address);

    return Index_out;
}

float uz_min_cost_function_8_get_J_out_AXI(uz_min_cost_function_8_t* self){
  
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float J_out_AXI = 0.0f;

    J_out_AXI = uz_min_cost_function_8_hw_get_J_out_AXI(self->config.base_address);

    return J_out_AXI;
}
*/

int32_t uz_min_cost_function_8_read_Index_in(uz_min_cost_function_8_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    int32_t Index = 0;
    Index = uz_min_cost_function_8_hw_get_Index_in(self->config.base_address);

    return Index;
}
#endif