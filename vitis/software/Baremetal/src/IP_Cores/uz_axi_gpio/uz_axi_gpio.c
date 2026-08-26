
#include "../../uz/uz_global_configuration.h"

#if UZ_AXI_GPIO_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_axi_gpio.h"
#include "xgpio.h"

#define UZ_AXI_INPUT 1U
#define UZ_AXI_OUTPUT 0U

#define CHANNEL_1 1U
struct uz_axi_gpio_t
{
    bool is_ready;
    XGpio xinstance;
    struct uz_axi_gpio_config_t config;
    uint32_t output_shadow;
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

#ifdef TEST
void uz_axi_gpio_reset_allocation(void)
{
    instance_counter = 0U;
    for (uint32_t index = 0U; index < UZ_AXI_GPIO_MAX_INSTANCES; index++) {
        instances[index].is_ready = false;
    }
}
#endif

uz_axi_gpio_t *uz_axi_gpio_init(struct uz_axi_gpio_config_t config)
{
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_true(config.number_of_pins > 0U);
    uz_assert_true(config.number_of_pins <= UZ_AXI_GPIO_MAX_PIN_NUMBER);
    uz_axi_gpio_t *self = uz_axi_gpio_allocation();
    self->config = config;
    uint32_t init_successful = XGpio_Initialize(&self->xinstance, self->config.device_id);
    (void)init_successful;
    uz_assert(self->xinstance.BaseAddress == self->config.base_address); // double check that the base address looked up by XGpio_Initialize matches the base address given by the user to prevent mismatch between used IP-Core instance and intended instance
    XGpio_SetDataDirection(&self->xinstance, CHANNEL_1, self->config.direction_of_pins);
    self->output_shadow = 0U;

    return (self);
}

static uint32_t uz_axi_gpio_output_mask(uz_axi_gpio_t *self)
{
    const uint32_t valid_pin_mask = (1U << self->config.number_of_pins) - 1U;
    return (~self->config.direction_of_pins) & valid_pin_mask;
}

void uz_axi_gpio_write_bitmask(uz_axi_gpio_t *self, uint32_t bitmask)
{
    uz_assert_not_NULL(self);
    uz_axi_gpio_set_output_shadow(self, bitmask);
    uz_axi_gpio_flush_outputs(self);
}

uint32_t uz_axi_gpio_read_bitmask(uz_axi_gpio_t *self)
{
    uz_assert_not_NULL(self);
    return XGpio_DiscreteRead(&self->xinstance, CHANNEL_1);
}

void uz_axi_gpio_write_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number, bool value)
{
    uz_axi_gpio_set_output_pin_to(self, pin_number, value);
    uz_axi_gpio_flush_outputs(self);
}

void uz_axi_gpio_set_output_pin(uz_axi_gpio_t *self, uint32_t pin_number)
{
    uz_axi_gpio_set_output_pin_to(self, pin_number, true);
}

void uz_axi_gpio_clear_output_pin(uz_axi_gpio_t *self, uint32_t pin_number)
{
    uz_axi_gpio_set_output_pin_to(self, pin_number, false);
}

void uz_axi_gpio_set_output_pin_to(uz_axi_gpio_t *self, uint32_t pin_number, bool value)
{
    uz_assert_not_NULL(self);
    uz_assert_true(pin_number < self->config.number_of_pins);
    if(value){
        self->output_shadow |= (1U << pin_number);
    }else{
        self->output_shadow &= ~(1U << pin_number);
    }
    self->output_shadow &= uz_axi_gpio_output_mask(self);
}

void uz_axi_gpio_set_output_bitmask(uz_axi_gpio_t *self, uint32_t set_mask)
{
    uz_assert_not_NULL(self);
    self->output_shadow |= set_mask;
    self->output_shadow &= uz_axi_gpio_output_mask(self);
}

void uz_axi_gpio_clear_output_bitmask(uz_axi_gpio_t *self, uint32_t clear_mask)
{
    uz_assert_not_NULL(self);
    self->output_shadow &= ~clear_mask;
    self->output_shadow &= uz_axi_gpio_output_mask(self);
}

void uz_axi_gpio_set_output_shadow(uz_axi_gpio_t *self, uint32_t bitmask)
{
    uz_assert_not_NULL(self);
    self->output_shadow = bitmask & uz_axi_gpio_output_mask(self);
}

uint32_t uz_axi_gpio_get_output_shadow(uz_axi_gpio_t *self)
{
    uz_assert_not_NULL(self);
    return self->output_shadow;
}

void uz_axi_gpio_flush_outputs(uz_axi_gpio_t *self)
{
    uz_assert_not_NULL(self);
    XGpio_DiscreteWrite(&self->xinstance, CHANNEL_1, self->output_shadow);
}

bool uz_axi_gpio_read_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number)
{
    uz_assert_not_NULL(self);
    uz_assert_true(pin_number < self->config.number_of_pins);
    uint32_t read_bitmask = XGpio_DiscreteRead(&self->xinstance, CHANNEL_1);
    bool extract_bit = (read_bitmask & (1U << pin_number)) != 0U;
    return extract_bit;
}

#endif
