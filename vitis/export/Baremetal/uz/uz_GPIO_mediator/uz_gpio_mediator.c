#include "uz_gpio_mediator.h"

static void MioGpioInstance_init();

static XGpioPs Gpio_inst;
static uz_gpio MIO_LedReady, MIO_LedRunning, MIO_LedError, MIO_LedUser;

void uz_mio_gpio_init(){
	MioGpioInstance_init();
	//GPIO INIT
	uz_facadeCfg LEDcfg;
	uz_gpio_init(&MIO_LedReady,&Gpio_inst,LED_ready,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedRunning,&Gpio_inst,LED_running,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedError,&Gpio_inst,LED_error,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedUser,&Gpio_inst,LED_user,OUTPUT_PIN);

	MIO_LedReady.SetEnableOutput(&MIO_LedReady,ENABLE_PIN);
	MIO_LedRunning.SetEnableOutput(&MIO_LedRunning,ENABLE_PIN);
	MIO_LedError.SetEnableOutput(&MIO_LedError,ENABLE_PIN);
	MIO_LedUser.SetEnableOutput(&MIO_LedUser,ENABLE_PIN);


	LEDcfg.LedUser=MIO_LedUser;
	LEDcfg.LedRunning=MIO_LedRunning;
	LEDcfg.LedError=MIO_LedError;
	LEDcfg.LedReady=MIO_LedReady;
	uz_led_facade_init(LEDcfg);
}

static void MioGpioInstance_init(){
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status;
	status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert(status == UZ_SUCCESS);
};

static void init_mio_leds(){

};
