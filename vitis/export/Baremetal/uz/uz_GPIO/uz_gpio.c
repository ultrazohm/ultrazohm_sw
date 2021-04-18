#include "uz_gpio.h"

static void uz_gpio_set_direction(struct uz_gpio_ *self, uint32_t Direction);
static uint32_t uz_gpio_get_direction(struct uz_gpio_ *self);
static void uz_gpio_set_enable_output(struct uz_gpio_ *self, uint32_t EnableOutput);
static uint32_t uz_gpio_get_enable_output(struct uz_gpio_ *self);
static void uz_gpio_write_pin(struct uz_gpio_ *self, uint32_t value);
static uint32_t uz_gpio_read_pin(struct uz_gpio_ *self);

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, uint32_t pin_number, uint32_t direction) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(Xgpio_instance);
	uz_assert(Xgpio_instance->IsReady);
	self->hw = Xgpio_instance;
	self->pin_number = pin_number;
	self->direction = direction;
	self->is_ready = true;
	self->set_direction = &uz_gpio_set_direction;
	self->get_direction = &uz_gpio_get_direction;
	self->set_enable_output = &uz_gpio_set_enable_output;
	self->get_enable_output = &uz_gpio_get_enable_output;
	self->write_pin = &uz_gpio_write_pin;
	self->read_pin = &uz_gpio_read_pin;
	self->set_direction(self, self->direction);
}

static void uz_gpio_set_direction(struct uz_gpio_ *self, uint32_t Direction) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	XGpioPs_SetDirectionPin(self->hw, (uint32_t) self->pin_number, (uint32_t) self->direction);
}

static uint32_t uz_gpio_get_direction(struct uz_gpio_ *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return ((uint32_t) XGpioPs_GetDirectionPin(self->hw, (uint32_t) self->pin_number));
}

static void uz_gpio_set_enable_output(struct uz_gpio_ *self, uint32_t EnableOutput) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	XGpioPs_SetOutputEnablePin(self->hw, (uint32_t) self->pin_number, (uint32_t) EnableOutput);
}

static uint32_t uz_gpio_get_enable_output(struct uz_gpio_ *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return ((uint32_t) XGpioPs_GetOutputEnablePin(self->hw, (uint32_t) self->pin_number));
}

static void uz_gpio_write_pin(struct uz_gpio_ *self, uint32_t value) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(self->get_enable_output);
	XGpioPs_WritePin(self->hw, (uint32_t) self->pin_number, (uint32_t) value);
}

static uint32_t uz_gpio_read_pin(struct uz_gpio_ *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (XGpioPs_ReadPin(self->hw, (uint32_t) self->pin_number));
}
