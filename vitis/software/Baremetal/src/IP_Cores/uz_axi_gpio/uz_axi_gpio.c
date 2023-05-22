#include "../../uz/uz_global_configuration.h"
#if UZ_AXI_GPIO_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_axi_gpio.h" 

struct uz_axi_gpio_t {
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_axi_gpio_t instances[UZ_AXI_GPIO_MAX_INSTANCES] = { 0 };

static uz_axi_gpio_t* uz_axi_gpio_allocation(void);

static uz_axi_gpio_t* uz_axi_gpio_allocation(void){
    uz_assert(instance_counter < UZ_AXI_GPIO_MAX_INSTANCES);
    uz_axi_gpio_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_axi_gpio_t* uz_axi_gpio_init() {
    uz_axi_gpio_t* self = uz_axi_gpio_allocation();
    return (self);
}
#endif