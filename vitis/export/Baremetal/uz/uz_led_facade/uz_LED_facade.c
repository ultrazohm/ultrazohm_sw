#include "../uz_led_facade/uz_LED_facade.h"

static XGpioPs Gpio_inst;
static uz_gpio MIO_LedReady, MIO_LedError, MIO_LedRunning, MIO_LedUser;
static uz_StatusLed LedReady, LedRunning, LedError, LedUser;

void uz_led_facade_init(){
	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = XPAR_PSU_GPIO_0_BASEADDR; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = XPAR_PSU_GPIO_0_DEVICE_ID; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;
	int status;
	status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	uz_assert(status == UZ_SUCCESS);

	uz_gpio_init(&MIO_LedReady,&Gpio_inst,LED_ready,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedRunning,&Gpio_inst,LED_running,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedError,&Gpio_inst,LED_error,OUTPUT_PIN);
	uz_gpio_init(&MIO_LedUser,&Gpio_inst,LED_user,OUTPUT_PIN);

	MIO_LedReady.SetEnableOutput(&MIO_LedReady,ENABLE_PIN);
	MIO_LedRunning.SetEnableOutput(&MIO_LedRunning,ENABLE_PIN);
	MIO_LedError.SetEnableOutput(&MIO_LedError,ENABLE_PIN);
	MIO_LedUser.SetEnableOutput(&MIO_LedUser,ENABLE_PIN);

	uz_led_init(&LedReady,&MIO_LedReady);
	uz_led_init(&LedRunning,&MIO_LedRunning);
	uz_led_init(&LedError,&MIO_LedError);
	uz_led_init(&LedUser,&MIO_LedUser);
};

void uz_SetLedReadyOn(){
	LedReady.turnOn(&LedReady);
};

void uz_SetLedReadyOff(){
	LedReady.turnOff(&LedReady);
};

void uz_SetLedRunningOn(){
	LedRunning.turnOn(&LedRunning);
};

void uz_SetLedRunningOff(){
	LedRunning.turnOff(&LedRunning);
};

void uz_SetLedErrorOn(){
	LedError.turnOn(&LedError);
};
void uz_SetLedErrorOff(){
	LedError.turnOff(&LedError);
}

void uz_SetLedUserOn(){
	LedUser.turnOn(&LedUser);
}
void uz_SetLedUserOff(){
	LedUser.turnOff(&LedUser);
}
