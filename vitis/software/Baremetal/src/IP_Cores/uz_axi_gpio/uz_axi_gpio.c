#include "../../uz/uz_global_configuration.h"
#if UZ_AXI_GPIO_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_axi_gpio.h"
#include "xpgio.h"

#define UZ_AXI_INPUT 1U
#define UZ_AXI_OUTPUT 0U

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

#define CHANNEL_1 1U
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
    self->config = config;
    uint32_t init_successful = XGpio_Initialize(&self->xinstance, self->config.device_id);
    uz_assert(self->xinstance.BaseAddress == self->config.base_address); // double check that the base address looked up by XGpio_Initialize matches the base address given by the user to prevent mismatch between used IP-Core instance and intended instance
    XGpio_SetDataDirection(&self->xinstance, CHANNEL_1, self->config.direction_of_pins);

    return (self);
}

void uz_axi_gpio_write_bitmask(uz_axi_gpio_t *self, uint32_t bitmask)
{
    uz_assert_not_NULL(self);
    XGpio_DiscreteWrite(&self->xinstance, CHANNEL_1, bitmask);
}

uint32_t uz_axi_gpio_read_bitmask(uz_axi_gpio_t *self)
{
    uz_assert_not_NULL(self);
    return XGpio_DiscreteRead(&self->xinstance, CHANNEL_1);
}

void uz_axi_gpio_write_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number, bool value)
{
    uz_assert_not_NULL(self);
    uz_assert_true(pin_number < self->config.number_of_pins);
    uint32_t current_bitmask = XGpio_DiscreteRead(&self->xinstance, CHANNEL_1);
    // Sets the bit at pin_number to true/false and keeps all other bits as they are by bit-wise or/and with 1 at each position except for pin_number
    if(value){
        current_bitmask |= (1U << pin_number);
    }else{
        current_bitmask &= ~(1U << pin_number); 
    }
    uz_axi_gpio_write_bitmask(self,current_bitmask);
}

bool uz_axi_gpio_read_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number)
{
    uz_assert_not_NULL(self);
    uz_assert_true(pin_number<self->config.number_of_pins);
    uint32_t read_bitmask = XGpio_DiscreteRead(&self->xinstance, CHANNEL_1);
    bool extract_bit = (read_bitmask & (1 << pin_number));
    return extract_bit;
}

#endif