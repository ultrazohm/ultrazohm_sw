#include "../main.h"
extern DS_Data Global_Data;

struct uz_axi_gpio_config_t output_config={
            .base_address=XPAR_UZ_USER_AXI_GPIO_0_BASEADDR,
            .device_id=XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID,
            .number_of_pins=3,
            .direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT
};

struct uz_axi_gpio_config_t input_config={
            .base_address=XPAR_UZ_USER_AXI_GPIO_1_BASEADDR,
            .device_id=XPAR_UZ_USER_AXI_GPIO_1_DEVICE_ID,
            .number_of_pins=2,
            .direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_INPUT
};

uz_axi_gpio_t* init_axi_gpio_input(void) {
	return(uz_axi_gpio_init(input_config));
}
uz_axi_gpio_t* init_axi_gpio_output(void) {
	return(uz_axi_gpio_init(output_config));
}
