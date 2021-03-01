#ifndef UZ_LED_H
#define UZ_LED_H

#include <stdbool.h>

#include "uz_HAL.h"

typedef enum {uReady=0,uzRunning,uzError,uzUser} StatusLedName;

typedef struct uz_Statusled_{
	_Bool isReady;
	StatusLedName name;
	void (*turnOn) (struct uz_Statusled_ *self);
	void (*turnOff) (struct uz_Statusled_ *self);
}uz_StatusLed;

int uz_led_init(uz_StatusLed *self);

#endif
