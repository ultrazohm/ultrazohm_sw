#include "xparameters.h"
#include "../include/axi_gpio_relais.h"

static struct uz_axi_gpio_config_t cfg = {
		.base_address = XPAR_UZ_USER_AXI_GPIO_RELAIS_BASEADDR,
		.device_id = XPAR_UZ_USER_AXI_GPIO_RELAIS_DEVICE_ID,
		.direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT,
		.number_of_pins = 1
};

uz_axi_gpio_t* init_axi_gpio_relais(void){
	uz_axi_gpio_t* obj = uz_axi_gpio_init(cfg);
	return obj;
}

