#include "../../uz/uz_global_configuration.h"
#if UZ_AXI_MYTESTIP_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_axi_myTestIP.h"
#include "uz_axi_myTestIP_hw.h"

struct uz_axi_myTestIP {
   bool is_ready;
   struct uz_axi_myTestIP_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_axi_myTestIP instances[UZ_AXI_MYTESTIP_MAX_INSTANCES] = { 0 };

static uz_axi_myTestIP* uz_axi_myTestIP_allocation(void);

static uz_axi_myTestIP* uz_axi_myTestIP_allocation(void){
   uz_assert(instance_counter < UZ_AXI_MYTESTIP_MAX_INSTANCES);
   uz_axi_myTestIP* self = &instances[instance_counter];
   uz_assert_false(self->is_ready);
   instance_counter++;
   self->is_ready = true;
   return (self);
}

uz_axi_myTestIP* uz_axi_myTestIP_init(struct uz_axi_myTestIP_config_t config) {
   uz_axi_myTestIP* self = uz_axi_myTestIP_allocation();
   self->config = config;
   return (self);
}

int32_t uz_axi_myTestIP_multiply(uz_axi_myTestIP* self, int32_t A, int32_t B){
   uz_assert_not_NULL(self);
   uz_assert(self->is_ready);
   uz_axi_myTestIP_hw_write_A(self->config.base_address,A);
   uz_axi_myTestIP_hw_write_B(self->config.base_address,B);
   return (uz_axi_myTestIP_hw_read_result(self->config.base_address));
}
#endif