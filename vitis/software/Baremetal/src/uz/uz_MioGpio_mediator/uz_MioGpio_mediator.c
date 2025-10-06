#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"
#include "../uz_LED/uz_LED.h"
#include "../uz_LED/uz_LED_facade.h"

#include "../uz_PushButton/uz_PushButton.h"
#include "../uz_PushButton/uz_PushButton_facade.h"

#include "xgpiops.h"
#include "../uz_MioGpio_mediator/uz_MioGpioMapping.h"
#include "uz_MioGpio_mediator.h"

static void InitializeXilinxMioGpioInstance(void);
static void InitializeMioPinsForLEDs(uint32_t ultrazohm_revision);
static void enableAllMioWithLEDsAttached(void);
static void InitializeAllStatusLEDs(void);
static void TurnAllLEDOff(void);
static void InitializeMioPinsForButtons(uint32_t ultrazohm_revision);
static void InitializeAllPushButtons(void);
static void enableAllMioWithButonsAttached(void);

static XGpioPs Gpio_inst;
static uz_gpio MIO_LedReady;
static uz_gpio MIO_LedRunning;
static uz_gpio MIO_LedError;
static uz_gpio MIO_LedUser;
static uz_gpio MIO_SWError;
static uz_gpio MIO_SWControl;
static uz_gpio MIO_SWSystem;
static uz_gpio MIO_SWExternalStop;

void uz_frontplane_button_and_led_init(uint32_t ultrazohm_revision)
{
	InitializeXilinxMioGpioInstance();
	InitializeMioPinsForLEDs(ultrazohm_revision);
	enableAllMioWithLEDsAttached();
	InitializeAllStatusLEDs();
	TurnAllLEDOff();

	InitializeMioPinsForButtons(ultrazohm_revision);
	InitializeAllPushButtons();
	enableAllMioWithButonsAttached();
}

static void InitializeXilinxMioGpioInstance(void)
{
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR;  // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert_false(status); // 0 -> no error
}

static void InitializeMioPinsForLEDs(uint32_t ultrazohm_revision)
{
	uz_assert(ultrazohm_revision > 0U);
	if (ultrazohm_revision < 4U)
	{ // Rev 3 and earlier
		uz_gpio_init(&MIO_LedReady, &Gpio_inst, UZ_REV_3_LED_ready, OUTPUT_PIN);
		uz_gpio_init(&MIO_LedRunning, &Gpio_inst, UZ_REV_3_LED_running, OUTPUT_PIN);
		uz_gpio_init(&MIO_LedError, &Gpio_inst, UZ_REV_3_LED_error, OUTPUT_PIN);
		uz_gpio_init(&MIO_LedUser, &Gpio_inst, UZ_REV_3_LED_user, OUTPUT_PIN);
	}
	else
	{
		switch (ultrazohm_revision)
		{
		case 4U:
			uz_gpio_init(&MIO_LedReady, &Gpio_inst, UZ_REV_4_LED_ready, OUTPUT_PIN);
			uz_gpio_init(&MIO_LedRunning, &Gpio_inst, UZ_REV_4_LED_running, OUTPUT_PIN);
			uz_gpio_init(&MIO_LedError, &Gpio_inst, UZ_REV_4_LED_error, OUTPUT_PIN);
			uz_gpio_init(&MIO_LedUser, &Gpio_inst, UZ_REV_4_LED_user, OUTPUT_PIN);
			break;
		case 5U:
		case 6U:
			uz_gpio_init(&MIO_LedReady, &Gpio_inst, UZ_REV_5_LED_ready, OUTPUT_PIN);
			uz_gpio_init(&MIO_LedRunning, &Gpio_inst, UZ_REV_5_LED_running, OUTPUT_PIN);
			uz_gpio_init(&MIO_LedError, &Gpio_inst, UZ_REV_5_LED_error, OUTPUT_PIN);
			uz_gpio_init(&MIO_LedUser, &Gpio_inst, UZ_REV_5_LED_user, OUTPUT_PIN);
			break;
		default:
			uz_assert(0); // Unknown revision
			break;
		}
	}
}

static void InitializeMioPinsForButtons(uint32_t ultrazohm_revision)
{
	uz_assert(ultrazohm_revision > 0U);
	if (ultrazohm_revision < 4U)
	{ // Rev 3 and earlier
		uz_gpio_init(&MIO_SWError, &Gpio_inst, UZ_REV_3_SW_stop, INPUT_PIN);
		uz_gpio_init(&MIO_SWSystem, &Gpio_inst, UZ_REV_3_SW_system, INPUT_PIN);
		uz_gpio_init(&MIO_SWControl, &Gpio_inst, UZ_REV_3_SW_control, INPUT_PIN);
		uz_gpio_init(&MIO_SWExternalStop, &Gpio_inst, UZ_REV_3_SW_external_stop, INPUT_PIN);
	}
	else
	{
		switch (ultrazohm_revision)
		{
		case 4U:
			uz_gpio_init(&MIO_SWError, &Gpio_inst, UZ_REV_4_SW_stop, INPUT_PIN);
			uz_gpio_init(&MIO_SWSystem, &Gpio_inst, UZ_REV_4_SW_system, INPUT_PIN);
			uz_gpio_init(&MIO_SWControl, &Gpio_inst, UZ_REV_4_SW_control, INPUT_PIN);
			uz_gpio_init(&MIO_SWExternalStop, &Gpio_inst, UZ_REV_4_SW_external_stop, INPUT_PIN);
			break;
		case 5U:
			uz_gpio_init(&MIO_SWError, &Gpio_inst, UZ_REV_5_SW_stop, INPUT_PIN);
			uz_gpio_init(&MIO_SWSystem, &Gpio_inst, UZ_REV_5_SW_system, INPUT_PIN);
			uz_gpio_init(&MIO_SWControl, &Gpio_inst, UZ_REV_5_SW_control, INPUT_PIN);
			uz_gpio_init(&MIO_SWExternalStop, &Gpio_inst, UZ_REV_5_SW_external_stop, INPUT_PIN);
			break;
		case 6U: // No changes between 5 and 6
			uz_gpio_init(&MIO_SWError, &Gpio_inst, UZ_REV_5_SW_stop, INPUT_PIN);
			uz_gpio_init(&MIO_SWSystem, &Gpio_inst, UZ_REV_5_SW_system, INPUT_PIN);
			uz_gpio_init(&MIO_SWControl, &Gpio_inst, UZ_REV_5_SW_control, INPUT_PIN);
			uz_gpio_init(&MIO_SWExternalStop, &Gpio_inst, UZ_REV_5_SW_external_stop, INPUT_PIN);
			break;
		default:
			uz_assert(0); // Unknown revision
			break;
		}
	}
}

static void InitializeAllPushButtons(void)
{
	uz_PushButtonFacadeCfg swcfg;
	swcfg.Stop = &MIO_SWError;
	swcfg.EnableSystem = &MIO_SWSystem;
	swcfg.EnableControl = &MIO_SWControl;
	swcfg.ExternalStop = &MIO_SWExternalStop;
	uz_PushButton_facade_init(swcfg);
}

static void enableAllMioWithLEDsAttached(void)
{
	uz_gpio_set_enable_output(&MIO_LedReady, true);
	uz_gpio_set_enable_output(&MIO_LedRunning, true);
	uz_gpio_set_enable_output(&MIO_LedError, true);
	uz_gpio_set_enable_output(&MIO_LedUser, true);
}

static void enableAllMioWithButonsAttached(void)
{
	uz_gpio_set_enable_output(&MIO_SWError, 1);
	uz_gpio_set_enable_output(&MIO_SWSystem, 1);
	uz_gpio_set_enable_output(&MIO_SWControl, 1);
	uz_gpio_set_enable_output(&MIO_SWExternalStop, 1);
}

static void InitializeAllStatusLEDs(void)
{
	uz_LedfacadeCfg LEDcfg;
	LEDcfg.LedUser = &MIO_LedUser;
	LEDcfg.LedRunning = &MIO_LedRunning;
	LEDcfg.LedError = &MIO_LedError;
	LEDcfg.LedReady = &MIO_LedReady;
	uz_led_facade_init(LEDcfg);
}

static void TurnAllLEDOff(void)
{
	uz_led_set_readyLED_off();
	uz_led_set_runningLED_off();
	uz_led_set_userLED_off();
	uz_led_set_errorLED_off();
}
