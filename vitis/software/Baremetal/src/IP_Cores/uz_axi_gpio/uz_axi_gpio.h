#ifndef UZ_AXI_GPIO_H
#define UZ_AXI_GPIO_H

#include <stdbool.h>

typedef struct uz_axi_gpio_t uz_axi_gpio_t;

#define UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT 0x00000000
#define UZ_AXI_GPIO_DIRECTION_ALL_INPUT  0xFFFFFFFF

struct uz_axi_gpio_config_t
{
    uint32_t base_address;
    uint16_t device_id;
    uint32_t number_of_pins;
    uint32_t direction_of_pins;
};

uz_axi_gpio_t *uz_axi_gpio_init(struct uz_axi_gpio_config_t config);

void uz_axi_gpio_write_pin(); // write to one pin
bool uz_axi_gpio_read_pin();  // read one pin

void uz_axi_gpio_write_bitmask(); // write to all pins at once with bitmask
bool uz_axi_gpio_read_bitmask();  // read one pin

#define UZ_AXI_GPIO_PIN1 (1U << 0)
#define UZ_AXI_GPIO_PIN2 (1U << 1)
#define UZ_AXI_GPIO_PIN3 (1U << 2)
#define UZ_AXI_GPIO_PIN4 (1U << 3)
#define UZ_AXI_GPIO_PIN5 (1U << 4)
#define UZ_AXI_GPIO_PIN6 (1U << 5)
#define UZ_AXI_GPIO_PIN7 (1U << 6)
#define UZ_AXI_GPIO_PIN8 (1U << 7)
#define UZ_AXI_GPIO_PIN9 (1U << 8)
#define UZ_AXI_GPIO_PIN10 (1U << 9)
#define UZ_AXI_GPIO_PIN11 (1U << 10)
#define UZ_AXI_GPIO_PIN12 (1U << 11)
#define UZ_AXI_GPIO_PIN13 (1U << 12)
#define UZ_AXI_GPIO_PIN14 (1U << 13)
#define UZ_AXI_GPIO_PIN15 (1U << 14)
#define UZ_AXI_GPIO_PIN16 (1U << 15)
#define UZ_AXI_GPIO_PIN17 (1U << 16)
#define UZ_AXI_GPIO_PIN18 (1U << 17)
#define UZ_AXI_GPIO_PIN19 (1U << 18)
#define UZ_AXI_GPIO_PIN20 (1U << 19)
#define UZ_AXI_GPIO_PIN21 (1U << 20)
#define UZ_AXI_GPIO_PIN22 (1U << 21)
#define UZ_AXI_GPIO_PIN23 (1U << 22)
#define UZ_AXI_GPIO_PIN24 (1U << 23)
#define UZ_AXI_GPIO_PIN25 (1U << 24)
#define UZ_AXI_GPIO_PIN26 (1U << 25)
#define UZ_AXI_GPIO_PIN27 (1U << 26)
#define UZ_AXI_GPIO_PIN28 (1U << 27)
#define UZ_AXI_GPIO_PIN29 (1U << 28)
#define UZ_AXI_GPIO_PIN30 (1U << 29)
#define UZ_AXI_GPIO_PIN31 (1U << 30)
#define UZ_AXI_GPIO_PIN32 (1U << 31)

#endif // UZ_AXI_GPIO_H
