#ifndef UZ_PUSHBUTTON_H
#define UZ_PUSHBUTTON_H

#include <stdbool.h>
#include "../uz_GPIO/uz_gpio.h"

typedef struct uz_PushButton_{
	_Bool isReady;
	uz_gpio *hw;
}uz_PushButton;

void uz_PushBotton_init(uz_PushButton *self, uz_gpio *hw);
_Bool uz_PushButton_GetValue(uz_PushButton *self);

#endif
