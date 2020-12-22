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
uz_gpio MIO_LedReady, MIO_LedRunning, MIO_LedError, MIO_LedUser;
uz_gpio MIO_SWError, MIO_SWControl, MIO_SWSystem;


void uz_mio_gpio_init(){
	InitializeXilinxMioGpioInstance();
	InitializeMioPinsForLEDs();
	enableAllMioWithLEDsAttached();
	InitializeAllStatusLEDs();
	TurnAllLEDOff();

	InitializeMioPinsForButtons();
	InitializeAllPushButtons();
	enableAllMioWithButonsAttached();
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

static void InitializeMioPinsForButtons(){
	uz_gpio_init(&MIO_SWError,&Gpio_inst,SW_stop,INPUT_PIN);
	uz_gpio_init(&MIO_SWSystem,&Gpio_inst,SW_system,INPUT_PIN);
	uz_gpio_init(&MIO_SWControl,&Gpio_inst,SW_control,INPUT_PIN);
};

static void InitializeAllPushButtons(){
	uz_PushButtonFacadeCfg swcfg;
	swcfg.Stop=&MIO_SWError;
	swcfg.EnableSystem=&MIO_SWSystem;
	swcfg.EnableControl=&MIO_SWControl;
	uz_PushButton_facade_init(swcfg);
};

static void enableAllMioWithLEDsAttached(){
	MIO_LedReady.SetEnableOutput(&MIO_LedReady,true);
	MIO_LedRunning.SetEnableOutput(&MIO_LedRunning,true);
	MIO_LedError.SetEnableOutput(&MIO_LedError,true);
	MIO_LedUser.SetEnableOutput(&MIO_LedUser,true);
};

static void enableAllMioWithButonsAttached(){
	MIO_SWError.SetEnableOutput(&MIO_SWError,1);
	MIO_SWSystem.SetEnableOutput(&MIO_SWSystem,1);
	MIO_SWControl.SetEnableOutput(&MIO_SWControl,1);
};

static void InitializeAllStatusLEDs(){
	uz_LedfacadeCfg LEDcfg;
	LEDcfg.LedUser=&MIO_LedUser;
	LEDcfg.LedRunning=&MIO_LedRunning;
	LEDcfg.LedError=&MIO_LedError;
	LEDcfg.LedReady=&MIO_LedReady;
	uz_led_facade_init(LEDcfg);
};

static void TurnAllLEDOff(){
	uz_SetLedReadyOff();
	uz_SetLedRunningOff();
	uz_SetLedUserOff();
	uz_SetLedErrorOff();
};
