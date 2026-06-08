#include "../../uz/uz_global_configuration.h"
#if UZ_HLS_TESTIP_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_HLS_testIP.h"
#include "uz_HLS_testIP_hw.h"

struct uz_HLS_testIP {
   bool is_ready;
   struct uz_HLS_testIP_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_HLS_testIP instances[UZ_HLS_TESTIP_MAX_INSTANCES] = { 0 };

static uz_HLS_testIP* uz_HLS_testIP_allocation(void);

static uz_HLS_testIP* uz_HLS_testIP_allocation(void){
   uz_assert(instance_counter < UZ_HLS_TESTIP_MAX_INSTANCES);
   uz_HLS_testIP* self = &instances[instance_counter];
   uz_assert_false(self->is_ready);
   instance_counter++;
   self->is_ready = true;
   return (self);
}

uz_HLS_testIP* uz_HLS_testIP_init(struct uz_HLS_testIP_config_t config) {
   uz_HLS_testIP* self = uz_HLS_testIP_allocation();
   self->config = config;
   return (self);
}

int32_t uz_HLS_testIP_multiply(uz_HLS_testIP* self, int32_t A, int32_t B){
   uz_assert_not_NULL(self);
   uz_assert(self->is_ready);
   uz_HLS_testIP_hw_write_A(self->config.base_address,A);
   uz_HLS_testIP_hw_write_B(self->config.base_address,B);
   return (uz_HLS_testIP_hw_read_result(self->config.base_address));
}
#endif