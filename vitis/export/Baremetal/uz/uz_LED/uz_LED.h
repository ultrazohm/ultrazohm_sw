#ifndef UZ_LED_H
#define UZ_LED_H

#include <stdbool.h>

#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"

typedef struct uz_Statusled_{
	_Bool is_ready;
	uz_gpio *hw;
	void (*turn_on) (struct uz_Statusled_ *self);
	void (*turn_off) (struct uz_Statusled_ *self);
}uz_statusLED;

void uz_led_init(uz_statusLED *self, uz_gpio *hw);

#endif
