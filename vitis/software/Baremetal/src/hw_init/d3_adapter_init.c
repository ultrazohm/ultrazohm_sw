#include "../include/d3_adapter_init.h"

/* Project Wizard BEGIN: D3 definitions */
/* Project Wizard END: D3 definitions */
#include "xparameters.h"
#include "../IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

#ifndef XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_AXI_GPIO_D1_DEVICE_ID
#define XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_AXI_GPIO_D1_DEVICE_ID 0U
#endif

#define PROJECT_WIZARD_IO_CARD_D1_DIRECTION_MASK 0xC0000000U // Signal 30 and 31 are inputs https://www.rapidtables.com/convert/number/binary-to-hex.html?x=11000000000000000000000000000000

static struct uz_axi_gpio_config_t axi_gpio_d3_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D3_AXI_GPIO_0_BASEADDR,
    .device_id = XPAR_UZ_DIGITAL_ADAPTER_D3_AXI_GPIO_0_DEVICE_ID,
    .number_of_pins = 32U,
    .direction_of_pins = PROJECT_WIZARD_IO_CARD_D1_DIRECTION_MASK};

uz_axi_gpio_t *initialize_axi_gpio_d3(void)
{
    return uz_axi_gpio_init(axi_gpio_d3_config);
}

/* Project Wizard END: D1 definitions */
