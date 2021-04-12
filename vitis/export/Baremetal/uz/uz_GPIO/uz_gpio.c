#include "uz_gpio.h"

static void uz_gpio_SetDirection(struct uz_gpio_ *self, uint32_t Direction);
static uint32_t uz_gpio_GetDirection(struct uz_gpio_ *self);
static void uz_gpio_SetEnableOutput(struct uz_gpio_ *self, uint32_t EnableOutput);
static uint32_t uz_gpio_GetEnableOutput(struct uz_gpio_ *self);
static void uz_gpio_WritePin(struct uz_gpio_ *self, uint32_t value);
static uint32_t uz_gpio_ReadPin(struct uz_gpio_ *self);

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, uint32_t PinNumber, uint32_t Direction){
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Xgpio_instance);
	uz_assert(Xgpio_instance->IsReady);

	self->hw=Xgpio_instance;
	self->PinNumber=PinNumber;
	self->Direction=Direction;
	self->isReady=true;

	self->SetDirection=&uz_gpio_SetDirection;
	self->GetDirection=&uz_gpio_GetDirection;
	self->SetEnableOutput=&uz_gpio_SetEnableOutput;
	self->GetEnableOutput=&uz_gpio_GetEnableOutput;
	self->WritePin=&uz_gpio_WritePin;
	self->ReadPin=&uz_gpio_ReadPin;
	self->SetDirection(self,self->Direction);
}


static void uz_gpio_SetDirection(struct uz_gpio_ *self, uint32_t Direction){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	XGpioPs_SetDirectionPin(self->hw, (uint32_t)self->PinNumber, (uint32_t)self->Direction);
}

static uint32_t uz_gpio_GetDirection(struct uz_gpio_ *self){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	return ((uint32_t)XGpioPs_GetDirectionPin(self->hw, (uint32_t)self->PinNumber));
}

static void uz_gpio_SetEnableOutput(struct uz_gpio_ *self, uint32_t EnableOutput){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	XGpioPs_SetOutputEnablePin(self->hw, (uint32_t)self->PinNumber, (uint32_t)EnableOutput);
}

static uint32_t uz_gpio_GetEnableOutput(struct uz_gpio_ *self){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	return ((uint32_t)XGpioPs_GetOutputEnablePin(self->hw, (uint32_t)self->PinNumber));
}

static void uz_gpio_WritePin(struct uz_gpio_ *self, uint32_t value){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	uz_assert(self->GetEnableOutput);
	XGpioPs_WritePin(self->hw, (uint32_t)self->PinNumber, (uint32_t)value);
}

static uint32_t uz_gpio_ReadPin(struct uz_gpio_ *self){
	uz_assert_not_NULL(self);
	uz_assert(self->isReady);
	return (XGpioPs_ReadPin(self->hw, (uint32_t)self->PinNumber));
}
