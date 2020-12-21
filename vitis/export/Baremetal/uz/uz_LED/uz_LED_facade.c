#include "uz_LED_facade.h"

static uz_StatusLed LedReady, LedRunning, LedError, LedUser;

void uz_led_facade_init(uz_facadeCfg cfg){
	uz_led_init(&LedReady,&cfg.LedReady);
	uz_led_init(&LedRunning,&cfg.LedRunning);
	uz_led_init(&LedError,&cfg.LedError);
	uz_led_init(&LedUser,&cfg.LedUser);
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
};

void uz_SetLedUserOn(){
	LedUser.turnOn(&LedUser);
};

void uz_SetLedUserOff(){
	LedUser.turnOff(&LedUser);
};
