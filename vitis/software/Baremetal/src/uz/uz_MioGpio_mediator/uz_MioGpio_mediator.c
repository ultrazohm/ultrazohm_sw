#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"
#include "../uz_LED/uz_LED.h"
#include "../uz_LED/uz_LED_facade.h"

#include "../uz_PushButton/uz_PushButton.h"
#include "../uz_PushButton/uz_PushButton_facade.h"

#include "xgpiops.h"
#include "../uz_MioGpio_mediator/uz_MioGpioMapping.h"
#include "uz_MioGpio_mediator.h"

static void InitializeXilinxMioGpioInstance();
static void InitializeMioPinsForLEDs();
static void enableAllMioWithLEDsAttached();
static void InitializeAllStatusLEDs();
static void TurnAllLEDOff();
static void InitializeMioPinsForButtons();
static void InitializeAllPushButtons();
static void enableAllMioWithButonsAttached();

XGpioPs Gpio_inst;
uz_gpio MIO_LedReady;
uz_gpio MIO_LedRunning;
uz_gpio MIO_LedError;
uz_gpio MIO_LedUser;
uz_gpio MIO_SWError;
uz_gpio MIO_SWControl;
uz_gpio MIO_SWSystem;

void uz_frontplane_button_and_led_init() {
	InitializeXilinxMioGpioInstance();
	InitializeMioPinsForLEDs();
	enableAllMioWithLEDsAttached();
	InitializeAllStatusLEDs();
	TurnAllLEDOff();

	InitializeMioPinsForButtons();
	InitializeAllPushButtons();
	enableAllMioWithButonsAttached();
}

static void InitializeXilinxMioGpioInstance() {
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status;
	status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert(status == UZ_SUCCESS);
}

static void InitializeMioPinsForLEDs() {
	uz_gpio_init(&MIO_LedReady, &Gpio_inst, LED_ready, OUTPUT_PIN);
	uz_gpio_init(&MIO_LedRunning, &Gpio_inst, LED_running, OUTPUT_PIN);
	uz_gpio_init(&MIO_LedError, &Gpio_inst, LED_error, OUTPUT_PIN);
	uz_gpio_init(&MIO_LedUser, &Gpio_inst, LED_user, OUTPUT_PIN);
}

static void InitializeMioPinsForButtons() {
	uz_gpio_init(&MIO_SWError, &Gpio_inst, SW_stop, INPUT_PIN);
	uz_gpio_init(&MIO_SWSystem, &Gpio_inst, SW_system, INPUT_PIN);
	uz_gpio_init(&MIO_SWControl, &Gpio_inst, SW_control, INPUT_PIN);
}

static void InitializeAllPushButtons() {
	uz_PushButtonFacadeCfg swcfg;
	swcfg.Stop = &MIO_SWError;
	swcfg.EnableSystem = &MIO_SWSystem;
	swcfg.EnableControl = &MIO_SWControl;
	uz_PushButton_facade_init(swcfg);
}
;

static void enableAllMioWithLEDsAttached() {
	uz_gpio_set_enable_output(&MIO_LedReady, true);
	uz_gpio_set_enable_output(&MIO_LedRunning, true);
	uz_gpio_set_enable_output(&MIO_LedError, true);
	uz_gpio_set_enable_output(&MIO_LedUser, true);
}

static void enableAllMioWithButonsAttached() {
	uz_gpio_set_enable_output(&MIO_SWError, 1);
	uz_gpio_set_enable_output(&MIO_SWSystem, 1);
	uz_gpio_set_enable_output(&MIO_SWControl, 1);
}

static void InitializeAllStatusLEDs() {
	uz_LedfacadeCfg LEDcfg;
	LEDcfg.LedUser = &MIO_LedUser;
	LEDcfg.LedRunning = &MIO_LedRunning;
	LEDcfg.LedError = &MIO_LedError;
	LEDcfg.LedReady = &MIO_LedReady;
	uz_led_facade_init(LEDcfg);
}

static void TurnAllLEDOff() {
	uz_led_set_readyLED_off();
	uz_led_set_runningLED_off();
	uz_led_set_userLED_off();
	uz_led_set_errorLED_off();
}
