// Facade for LEDs of the ultrazohm
// provides API for LEDs
#ifndef UZ_LED_FACADE_H
#define UZ_LED_FACADE_H

#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"
#include "uz_LED.h"

typedef struct{
	uz_gpio *LedReady;
	uz_gpio *LedError;
	uz_gpio *LedRunning;
	uz_gpio *LedUser;
}uz_LedfacadeCfg;

void uz_led_facade_init(uz_LedfacadeCfg cfg);

void uz_led_SetLedReadyOn();
void uz_led_SetLedReadyOff();

void uz_led_SetLedRunningOn();
void uz_led_SetLedRunningOff();

void uz_led_SetLedErrorOn();
void uz_led_SetLedErrorOff();

void uz_led_SetLedUserOn();
void uz_led_SetLedUserOff();

#endif
