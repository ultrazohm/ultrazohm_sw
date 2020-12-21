#include "uz_MioGpio_mediator.h"

static void InitializeXilinxMioGpioInstance();
static void InitializeMioPinsForLEDs();
static void enableAllMioWithLEDsAttached();
static void InitializeAllStatusLEDs();

static XGpioPs Gpio_inst;
static uz_gpio MIO_LedReady, MIO_LedRunning, MIO_LedError, MIO_LedUser;

void uz_mio_gpio_init(){
	InitializeXilinxMioGpioInstance();
	InitializeMioPinsForLEDs();
	enableAllMioWithLEDsAttached();
	InitializeAllStatusLEDs();
};

static void InitializeXilinxMioGpioInstance(){
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status;
	status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert(status == UZ_SUCCESS);
};

static void InitializeMioPinsForLEDs(){
	uz_gpio_init(&MIO_LedReady,&Gpio_inst,LED_ready,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedRunning,&Gpio_inst,LED_running,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedError,&Gpio_inst,LED_error,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedUser,&Gpio_inst,LED_user,OUTPUT_PIN);
};

static void enableAllMioWithLEDsAttached(){
	MIO_LedReady.SetEnableOutput(&MIO_LedReady,true);
	MIO_LedRunning.SetEnableOutput(&MIO_LedRunning,true);
	MIO_LedError.SetEnableOutput(&MIO_LedError,true);
	MIO_LedUser.SetEnableOutput(&MIO_LedUser,true);
}

static void InitializeAllStatusLEDs(){
	uz_facadeCfg LEDcfg;
	LEDcfg.LedUser=MIO_LedUser;
	LEDcfg.LedRunning=MIO_LedRunning;
	LEDcfg.LedError=MIO_LedError;
	LEDcfg.LedReady=MIO_LedReady;
	uz_led_facade_init(LEDcfg);
}
