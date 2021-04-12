#include "uz_PushButton.h"

static _Bool uz_PushButton_GetValue(uz_PushButton *self);

void uz_PushBotton_init(uz_PushButton *self, uz_gpio *hw){
	uz_assert_not_NULL(self);
	self->isReady=true;
	self->hw=hw;
	self->GetValue=&uz_PushButton_GetValue;
};

static _Bool uz_PushButton_GetValue(uz_PushButton *self){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	return ((_Bool)self->hw->ReadPin(self->hw));
};
