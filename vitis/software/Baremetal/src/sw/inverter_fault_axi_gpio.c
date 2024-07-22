#include "../include/inverter_fault_axi_gpio.h"

// inverter fault inputs
struct uz_axi_gpio_config_t axi_gpio_inverter_faults_config={
            .base_address=XPAR_UZ_USER_AXI_GPIO_0_BASEADDR,
            .device_id=XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID,
            .number_of_pins=2,
            .direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_INPUT
};

uz_axi_gpio_t* init_inverter_fault_axi_gpio(void)
{
	return(uz_axi_gpio_init(axi_gpio_inverter_faults_config));
}
