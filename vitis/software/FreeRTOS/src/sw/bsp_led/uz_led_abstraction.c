/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface for LEDs
 */

#include "xparameters.h"
#include "xgpiops.h"

#include "../uz_HAL.h"
#include "uz_MioGpioMapping.h"
#include "../../uz/uz_GPIO/uz_gpio.h"

//====================================================================
// Static variables
//====================================================================
static XGpioPs Gpio_inst;
static uz_gpio MIO_LedReady;
static uz_gpio MIO_LedRunning;
static uz_gpio MIO_LedError;
static uz_gpio MIO_LedUser;
static uz_gpio MIO_SWError;
static uz_gpio MIO_SWControl;
static uz_gpio MIO_SWSystem;

//====================================================================
// Static functions
//====================================================================
static void InitializeXilinxMioGpioInstance() {
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert_false(status); // 0 -> no error
}

static void InitializeMioPinsForLEDs() {
	uz_gpio_init(&MIO_LedReady, &Gpio_inst, LED_ready, OUTPUT_PIN);
	uz_gpio_init(&MIO_LedRunning, &Gpio_inst, LED_running, OUTPUT_PIN);
	uz_gpio_init(&MIO_LedError, &Gpio_inst, LED_error, OUTPUT_PIN);
	uz_gpio_init(&MIO_LedUser, &Gpio_inst, LED_user, OUTPUT_PIN);
}

static void enableAllMioWithLEDsAttached() {
	uz_gpio_set_enable_output(&MIO_LedReady, true);
	uz_gpio_set_enable_output(&MIO_LedRunning, true);
	uz_gpio_set_enable_output(&MIO_LedError, true);
	uz_gpio_set_enable_output(&MIO_LedUser, true);
}

static void pin_set(uz_gpio *gpio, uint32_t on)
{
	XGpioPs_WritePin(&Gpio_inst, gpio->pin_number, on);
}

static void set_leds_off(void)
{
	pin_set(&MIO_LedReady, 0);
	pin_set(&MIO_LedRunning, 0);
	pin_set(&MIO_LedError, 0);
	pin_set(&MIO_LedUser, 0);
}

//====================================================================
// Global functions
//====================================================================
void uz_led_abstraction_init(void)
{
	InitializeXilinxMioGpioInstance();
	InitializeMioPinsForLEDs();
	set_leds_off();
	enableAllMioWithLEDsAttached();

}

void uz_led_abstraction_set(int led, int on)
{
	switch (led) {
	case 0: pin_set(&MIO_LedReady, on); break;
	case 1: pin_set(&MIO_LedRunning, on); break;
	case 2: pin_set(&MIO_LedError, on); break;
	case 3: pin_set(&MIO_LedUser, on); break;
	}
}
