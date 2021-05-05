// Facade for LEDs of the ultrazohm
// provides API for LEDs
#ifndef UZ_PUSHBUTTON_FACADE_H
#define UZ_PUSHBUTTON_FACADE_H

#include "../uz_HAL.h"
#include "../uz_GPIO/uz_gpio.h"
#include "uz_PushButton.h"
#include "stdbool.h"

typedef struct{
	uz_gpio *EnableSystem;
	uz_gpio *EnableControl;
	uz_gpio *Stop;
}uz_PushButtonFacadeCfg;

void uz_PushButton_facade_init(uz_PushButtonFacadeCfg cfg);

_Bool uz_GetPushButtonStop();
_Bool uz_GetPushButtonEnableSystem();
_Bool uz_GetPushButtonEnableControl();

#endif
