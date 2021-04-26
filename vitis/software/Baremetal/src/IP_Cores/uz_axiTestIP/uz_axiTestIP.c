#include "uz_axiTestIP.h"
#include "uz_axiTestIP_private.h"
#include "uz_axiTestIP_hwAddresses.h"

uz_axiTestIP_handle uz_axiTestIP_init(uz_axiTestIP_handle self) {
	uz_assert_not_NULL(self); // Make sure no NULL pointer is passed to the function since this would be an error
	uz_assert(self->base_address != 0); // Make sure that the base address is set
	uz_assert(self->is_ready == false); // Make sure this instance is not initialized two times
	self->is_ready = true;
	return (self);
}

void uz_axiTestIP_set_A_int32(uz_axiTestIP_handle self, int32_t A) {
	uz_assert_not_NULL(self);
	self->A_int32_t = A;
	uz_axi_write_int32(self->base_address + A_int32_Data_uz_axi_testIP, self->A_int32_t);
}

void uz_axiTestIP_set_B_int32(uz_axiTestIP_handle self, int32_t B) {
	uz_assert_not_NULL(self);
	self->B_int32_t  = B;
	uz_axi_write_int32(self->base_address + B_int32_Data_uz_axi_testIP, self->B_int32_t);
}

int32_t uz_axiTestIP_get_C_int32(uz_axiTestIP_handle self) {
	uz_assert_not_NULL(self);
	self->C_int32_t  = uz_axi_read_int32(self->base_address + C_int32_Data_uz_axi_testIP);
	return (self->C_int32_t);
}

void uz_axiTestIP_set_A_float(uz_axiTestIP_handle self, float A) {
	uz_assert_not_NULL(self);
	self->A_float = A;
	uz_axi_write_float(self->base_address + A_float_Data_uz_axi_testIP, self->A_float);
	uz_axi_write_bool(self->base_address + A_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(self->base_address + A_float_Strobe_uz_axi_testIP, true);
	uz_axi_write_bool(self->base_address + A_float_Strobe_uz_axi_testIP, false);
}

void uz_axiTestIP_set_B_float(uz_axiTestIP_handle self, float B) {
	uz_assert_not_NULL(self);
	self->B_float  = B;
	uz_axi_write_float(self->base_address + B_float_Data_uz_axi_testIP, self->B_float);
	uz_axi_write_bool(self->base_address + B_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(self->base_address + B_float_Strobe_uz_axi_testIP, true);
	uz_axi_write_bool(self->base_address + B_float_Strobe_uz_axi_testIP, false);
}

float uz_axiTestIP_get_C_float(uz_axiTestIP_handle self) {
	uz_assert_not_NULL(self);
	uz_axi_write_bool(self->base_address + C_float_Strobe_uz_axi_testIP, false);
	uz_axi_write_bool(self->base_address + C_float_Strobe_uz_axi_testIP, true);
	uz_axi_write_bool(self->base_address + C_float_Strobe_uz_axi_testIP, false);
	self->C_float  = uz_axi_read_float(self->base_address + C_float_Data_uz_axi_testIP);
	return (self->C_float );
}
