#include "../include/d2_adapter_init.h"

/* Project Wizard BEGIN: D2 definitions */
/* Project Wizard generated content for D2 AXI GPIO IO card */
#include "xparameters.h"
#include "../IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

#ifndef XPAR_UZ_DIGITAL_ADAPTER_D2_ADAPTER_AXI_GPIO_D2_DEVICE_ID
#define XPAR_UZ_DIGITAL_ADAPTER_D2_ADAPTER_AXI_GPIO_D2_DEVICE_ID 1U
#endif

#define PROJECT_WIZARD_IO_CARD_D2_DIRECTION_MASK 0x0000FFFFU

static struct uz_axi_gpio_config_t axi_gpio_d2_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D2_ADAPTER_AXI_GPIO_D2_BASEADDR,
    .device_id = XPAR_UZ_DIGITAL_ADAPTER_D2_ADAPTER_AXI_GPIO_D2_DEVICE_ID,
    .number_of_pins = 30U,
    .direction_of_pins = PROJECT_WIZARD_IO_CARD_D2_DIRECTION_MASK
};

uz_axi_gpio_t* initialize_axi_gpio_d2(void)
{
    return uz_axi_gpio_init(axi_gpio_d2_config);
}
/* Project Wizard END: D2 definitions */
