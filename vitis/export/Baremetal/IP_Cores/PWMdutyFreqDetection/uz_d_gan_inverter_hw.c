#include "uz_d_gan_inverter_private.h"
#include "uz_d_gan_inverter_hwAddresses.h"
#include "../../uz/uz_HAL.h"
#include "uz_d_gan_inverter_hw.h"


uz_d_gan_inverter_handle uz_d_gan_inverter_init(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	return self;
}

int uz_d_gan_inverter_get_PWMFreqTicks(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	self->PWMFreqTicks = uz_axi_read_uint32(self->base_address + AXI_freq_Data_PWMdutyFreqDetection);
	return(self->PWMFreqTicks);
}

int uz_d_gan_inverter_get_PWMhightimeTicks(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	self->PWMhightimeTicks = uz_axi_read_uint32(self->base_address + AXI_hightime_Data_PWMdutyFreqDetection);
	return(self->PWMhightimeTicks);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	self->PWMlowtimeTicks = uz_axi_read_uint32(self->base_address + AXI_lowtime_Data_PWMdutyFreqDetection);
	return(self->PWMlowtimeTicks);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_dutycyc_Data_PWMdutyFreqDetection);
	self->PWMdutyCycPerCent = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent);
}
