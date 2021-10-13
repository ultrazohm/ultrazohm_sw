#ifndef UZ_LED_H
#define UZ_LED_H

#include <stdbool.h>
#include "../uz_GPIO/uz_gpio.h"

typedef struct uz_Statusled_{
	_Bool is_ready;
	uz_gpio *hw;
}uz_statusLED;

void uz_led_init(uz_statusLED *self, uz_gpio *hw);

void uz_led_turn_on(uz_statusLED *self);
void uz_led_turn_off(uz_statusLED *self);

#endif
