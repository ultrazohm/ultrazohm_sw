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

void uz_led_set_readyLED_on();
void uz_led_set_readyLED_off();

void uz_led_set_runningLED_on();
void uz_led_set_runningLED_off();

void uz_led_set_errorLED_on();
void uz_led_set_errorLED_off();

void uz_led_set_userLED_on();
void uz_led_set_userLED_off();

bool uz_get_led_status(uz_statusLED *self);

#endif
