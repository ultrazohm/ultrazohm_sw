#ifndef UZ_AXI_GPIO_H
#define UZ_AXI_GPIO_H

#include <stdbool.h>

typedef struct uz_axi_gpio_t uz_axi_gpio_t;

#define UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT 0x00000000U
#define UZ_AXI_GPIO_DIRECTION_ALL_INPUT  0xFFFFFFFFU

struct uz_axi_gpio_config_t
{
    uint32_t base_address;
    uint16_t device_id;
    uint32_t number_of_pins;
    uint32_t direction_of_pins;
};

uz_axi_gpio_t *uz_axi_gpio_init(struct uz_axi_gpio_config_t config);

void uz_axi_gpio_write_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number, bool value); // write to one pin
bool uz_axi_gpio_read_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number);              // read one pin

void uz_axi_gpio_write_bitmask(uz_axi_gpio_t *self, uint32_t bitmask); // write to all pins at once with bitmask
uint32_t uz_axi_gpio_read_bitmask(uz_axi_gpio_t *self);                        // read one pin



#endif // UZ_AXI_GPIO_H
