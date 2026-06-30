#include "../include/d1_adapter_init.h"

/* Project Wizard BEGIN: D1 definitions */
/* Project Wizard generated content for D1 AXI GPIO IO card */
#include "xparameters.h"
#include "../IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

#ifndef XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_AXI_GPIO_D1_DEVICE_ID
#define XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_AXI_GPIO_D1_DEVICE_ID 0U
#endif

#define PROJECT_WIZARD_IO_CARD_D1_DIRECTION_MASK 0x3FFF0000U

static struct uz_axi_gpio_config_t axi_gpio_d1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_AXI_GPIO_D1_BASEADDR,
    .device_id = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_AXI_GPIO_D1_DEVICE_ID,
    .number_of_pins = 30U,
    .direction_of_pins = PROJECT_WIZARD_IO_CARD_D1_DIRECTION_MASK
};

uz_axi_gpio_t* initialize_axi_gpio_d1(void)
{
    return uz_axi_gpio_init(axi_gpio_d1_config);
}
/* Project Wizard END: D1 definitions */
