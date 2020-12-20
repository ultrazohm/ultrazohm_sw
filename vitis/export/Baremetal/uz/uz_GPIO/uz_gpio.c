#include "uz_gpio.h"

static void uz_gpio_SetDirection(struct uz_gpio_ *self, int Direction);
static int uz_gpio_GetDirection(struct uz_gpio_ *self);
static void uz_gpio_SetEnableOutput(struct uz_gpio_ *self, int EnableOutput);
static int uz_gpio_GetEnableOutput(struct uz_gpio_ *self);
static void uz_gpio_WritePin(struct uz_gpio_ *self, int value);
static int uz_gpio_ReadPin(struct uz_gpio_ *self);

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, int PinNumber, int Direction){
	uz_assertNotNull(self);
	uz_assertNotNull(Xgpio_instance);
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


static void uz_gpio_SetDirection(struct uz_gpio_ *self, int Direction){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	XGpioPs_SetDirectionPin(self->hw, (uint32_t)self->PinNumber, (uint32_t)self->Direction);
}

static int uz_gpio_GetDirection(struct uz_gpio_ *self){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	return XGpioPs_GetDirectionPin(self->hw, (uint32_t)self->PinNumber);
}

static void uz_gpio_SetEnableOutput(struct uz_gpio_ *self, int EnableOutput){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	XGpioPs_SetOutputEnablePin(self->hw, (uint32_t)self->PinNumber, (uint32_t)EnableOutput);
}

static int uz_gpio_GetEnableOutput(struct uz_gpio_ *self){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	return XGpioPs_GetOutputEnablePin(self->hw, (uint32_t)self->PinNumber);
}

static void uz_gpio_WritePin(struct uz_gpio_ *self, int value){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	XGpioPs_WritePin(self->hw, (uint32_t)self->PinNumber, (uint32_t)value);
}

static int uz_gpio_ReadPin(struct uz_gpio_ *self){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	return XGpioPs_ReadPin(self->hw, (uint32_t)self->PinNumber);
}
