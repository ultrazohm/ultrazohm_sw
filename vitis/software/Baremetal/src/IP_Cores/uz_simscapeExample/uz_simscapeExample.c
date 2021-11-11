#include "uz_simscapeExample.h"
#include "uz_simscapeExample_private.h"
#include "uz_simscapeExample_hwAddresses.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_math_constants.h"
#include "../../uz/uz_SystemTime/uz_SystemTime.h"


static void uz_simscapeExample_set_Vin(uz_simscapeExample_handle self, float Vin);
static float uz_simscapeExample_get_IR(uz_simscapeExample_handle self);
static float uz_simscapeExample_get_Vdiode(uz_simscapeExample_handle self);
static float uz_simscapeExample_get_Iout(uz_simscapeExample_handle self);

uz_simscapeExample_handle uz_simscapeExample_init(uz_simscapeExample_handle self) {
	uz_assert_not_NULL(self); // Make sure no NULL pointer is passed to the function since this would be an error
	uz_assert( (self->base_address) != 0U); // Make sure that the base address is set
	uz_assert(self->is_ready == false); // Make sure this instance is not initialized two times
	self->is_ready = true;
	return (self);
}

void uz_simscapeExample_step_model_once(uz_simscapeExample_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	int tmp = (uz_SystemTime_GetInterruptCounter() % 10000);
	float t = tmp / 10000.0f;
	self->sine = self->amp * sinf(2.0f * UZ_PIf * t * self->freq_Hz);
	uz_simscapeExample_set_Vin(self, self->sine);
	self->IR = uz_simscapeExample_get_IR(self);
	self->Iout = uz_simscapeExample_get_Iout(self);
	self->Vdiode = uz_simscapeExample_get_Vdiode(self);
}

static void uz_simscapeExample_set_Vin(uz_simscapeExample_handle self, float Vin) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->Vin = Vin;
	uz_axi_write_float(self->base_address + Vin_Data_uz_simscapeExample, Vin);
}

static float uz_simscapeExample_get_IR(uz_simscapeExample_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (uz_axi_read_float(self->base_address + IR_Data_uz_simscapeExample));
}

static float uz_simscapeExample_get_Vdiode(uz_simscapeExample_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (uz_axi_read_float(self->base_address + Vdiode_Data_uz_simscapeExample));
}

static float uz_simscapeExample_get_Iout(uz_simscapeExample_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (uz_axi_read_float(self->base_address + Iout_Data_uz_simscapeExample));
}
