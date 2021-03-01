#ifndef UZ_LED_H
#define UZ_LED_H

#include <stdbool.h>

#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"

typedef struct uz_Statusled_{
	_Bool isReady;
	uz_gpio *hw;
	void (*turnOn) (struct uz_Statusled_ *self);
	void (*turnOff) (struct uz_Statusled_ *self);
}uz_StatusLed;

void uz_led_init(uz_StatusLed *self, uz_gpio *hw);

#endif
