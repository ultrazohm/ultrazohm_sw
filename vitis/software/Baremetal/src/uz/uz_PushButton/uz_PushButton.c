#include "uz_PushButton.h"
#include "../uz_HAL.h"

void uz_PushBotton_init(uz_PushButton *self, uz_gpio *hw){
	uz_assert_not_NULL(self);
	self->isReady=true;
	self->hw=hw;
};

_Bool uz_PushButton_GetValue(uz_PushButton *self){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	return ((_Bool) uz_gpio_read_pin(self->hw));
};
