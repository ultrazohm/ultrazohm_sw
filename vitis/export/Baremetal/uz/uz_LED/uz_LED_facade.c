#include "uz_LED_facade.h"

static uz_StatusLed LedReady, LedRunning, LedError, LedUser;

void uz_led_facade_init(uz_LedfacadeCfg cfg){
	uz_led_init(&LedReady,cfg.LedReady);
	uz_led_init(&LedRunning,cfg.LedRunning);
	uz_led_init(&LedError,cfg.LedError);
	uz_led_init(&LedUser,cfg.LedUser);
};

void uz_led_SetLedReadyOn(){
	LedReady.turnOn(&LedReady);
};

void uz_led_SetLedReadyOff(){
	LedReady.turnOff(&LedReady);
};

void uz_led_SetLedRunningOn(){
	LedRunning.turnOn(&LedRunning);
};

void uz_led_SetLedRunningOff(){
	LedRunning.turnOff(&LedRunning);
};

void uz_led_SetLedErrorOn(){
	LedError.turnOn(&LedError);
};
void uz_led_SetLedErrorOff(){
	LedError.turnOff(&LedError);
};

void uz_led_SetLedUserOn(){
	LedUser.turnOn(&LedUser);
};

void uz_led_SetLedUserOff(){
	LedUser.turnOff(&LedUser);
};
