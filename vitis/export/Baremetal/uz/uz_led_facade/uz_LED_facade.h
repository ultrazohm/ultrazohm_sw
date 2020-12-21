// Facade for LEDs of the ultrazohm
// provides API for LEDs
#ifndef UZ_LED_FACADE_H
#define UZ_LED_FACADE_H

#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"
#include "../uz_LED/uz_LED.h"
#include "../../main.h"

void uz_led_facade_init();

void uz_SetLedReadyOn();
void uz_SetLedReadyOff();

void uz_SetLedRunningOn();
void uz_SetLedRunningOff();

void uz_SetLedErrorOn();
void uz_SetLedErrorOff();

void uz_SetLedUserOn();
void uz_SetLedUserOff();

#endif
