#ifndef UZ_GPIO_H
#define UZ_GPIO_H

#include <stdbool.h>

#include "xgpiops.h"

#include "../uz_HAL.h"

typedef struct uz_gpio_{
	XGpioPs *hw;
	_Bool isReady;
	int PinNumber;
	int Direction;
	void (*SetDirection)(struct uz_gpio_ *self, int Direction);
	int (*GetDirection)(struct uz_gpio_ *self);
	void (*SetEnableOutput)(struct uz_gpio_ *self, int EnableOutput);
	int (*GetEnableOutput)(struct uz_gpio_ *self);
	void (*WritePin) (struct uz_gpio_ *self, int value);
	int (*ReadPin) (struct uz_gpio_ *self);
}uz_gpio;

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, int PinNumber, int Direction);

#endif
