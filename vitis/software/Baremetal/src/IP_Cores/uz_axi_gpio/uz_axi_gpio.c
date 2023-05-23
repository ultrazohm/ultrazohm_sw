#include "../../uz/uz_global_configuration.h"
#if UZ_AXI_GPIO_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_axi_gpio.h"
#include "xpgio.h"

#define UZ_AXI_INPUT 1U
#define UZ_AXI_OUTPUT 0U

struct uz_axi_gpio_t
{
    bool is_ready;
    XGpio xinstance;
    struct uz_axi_gpio_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_axi_gpio_t instances[UZ_AXI_GPIO_MAX_INSTANCES] = {0};

static uz_axi_gpio_t *uz_axi_gpio_allocation(void);

static uz_axi_gpio_t *uz_axi_gpio_allocation(void)
{
    uz_assert(instance_counter < UZ_AXI_GPIO_MAX_INSTANCES);
    uz_axi_gpio_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_axi_gpio_t *uz_axi_gpio_init(struct uz_axi_gpio_config_t config)
{
    uz_assert_not_zero_uint32(config.base_address);
    uz_axi_gpio_t *self = uz_axi_gpio_allocation();
    self->config=config;
    XGpio_Initialize(&self->xinstance, self->config.device_id);
    uz_assert(self->xinstance.BaseAddress==self->config.base_address); // double check that the base address looked up by XGpio_Initialize matches the base address given by the user to prevent mismatch between used IP-Core instance and intended instance
        XGpio_SetDataDirection(&self->xinstance, 1U, self->config.direction_of_pins);

    return (self);
}

void uz_axi_gpio_write_bitmask(uz_axi_gpio_t *self, uint32_t bitmask){
    uz_assert_not_NULL(self);
    XGpio_DiscreteWrite(&self->xinstance, 1U, bitmask);
}

uint32_t uz_axi_gpio_read_bitmask(uz_axi_gpio_t *self){
    uz_assert_not_NULL(self);
    return XGpio_DiscreteRead(&self->xinstance, 1U);
}

#endif