#include "../uz_GPIO/uz_gpio.h"
#include "../uz_HAL.h"
#include "uz_phy_reset.h"


#define OUTPUT_PIN				1 								//This Pin is an Output
#define INPUT_PIN				0 								//This Pin is an Input

#define ENABLE_PIN				1 								//This Pin is enabled
#define DISABLE_PIN				0 								//This Pin is disabled

#define PHY0_RESET_MIO_PIN		26U
#define PHY1_RESET_MIO_PIN		27U


static void uz_phy_reset_init();
static void InitializeXilinxMioGpioInstance();

static XGpioPs Gpio_inst;
static uz_gpio MIO_PHY0_Reset;
static uz_gpio MIO_PHY1_Reset;

int uz_phy_reset(void)
{
	uz_phy_reset_init();
	int phy_reset_high_time_us = 20e3; //20ms = 20,000 us

	// enable apply reset
	uz_gpio_set_enable_output(&MIO_PHY0_Reset, true);
	uz_gpio_write_pin(&MIO_PHY0_Reset, false);

	uz_gpio_set_enable_output(&MIO_PHY1_Reset, true);
	uz_gpio_write_pin(&MIO_PHY1_Reset, false);

	// wait for some time as defined in data sheet
	usleep(phy_reset_high_time_us);

	// release reset and disable MIO pin
	uz_gpio_write_pin(&MIO_PHY0_Reset, true);
	uz_gpio_set_enable_output(&MIO_PHY0_Reset, false);

	uz_gpio_write_pin(&MIO_PHY1_Reset, true);
	uz_gpio_set_enable_output(&MIO_PHY1_Reset, false);


	xil_printf("PHY reset successful \n\r");
}

static void uz_phy_reset_init() {
	InitializeXilinxMioGpioInstance();
	uz_gpio_init(&MIO_PHY0_Reset, &Gpio_inst, PHY0_RESET_MIO_PIN, OUTPUT_PIN);
	uz_gpio_init(&MIO_PHY1_Reset, &Gpio_inst, PHY1_RESET_MIO_PIN, OUTPUT_PIN);
}

static void InitializeXilinxMioGpioInstance() {
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert_false(status); // 0 -> no error
}

