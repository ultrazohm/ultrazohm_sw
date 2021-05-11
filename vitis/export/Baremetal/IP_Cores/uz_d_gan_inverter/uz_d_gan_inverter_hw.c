#include "../uz_d_gan_inverter/uz_d_gan_inverter_hw.h"
#include "../uz_d_gan_inverter/uz_d_gan_inverter_hwAddresses.h"
#include "../uz_d_gan_inverter/uz_d_gan_inverter_private.h"
#include "../../uz/uz_HAL.h"

uz_d_gan_inverter_handle uz_d_gan_inverter_init(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self); 				// Make sure no NULL pointer is passed to the function since this would be an error
	uz_assert( (self->base_address) != 0); 	// Make sure that the base address is set
	uz_assert(self->is_ready == false); 	// Make sure this instance is not initialized two times
	self->is_ready = true;
	return (self);
}

int uz_d_gan_inverter_get_PWMFreqTicks_H1(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMFreqTicks_H1 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_period_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks_H1);
}

int uz_d_gan_inverter_get_PWMhightimeTicks_H1(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMhightimeTicks_H1 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks_H1);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks_H1(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMlowtimeTicks_H1 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks_H1);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent_H1 = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent_H1);
}

int uz_d_gan_inverter_get_PWMFreqTicks_L1(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMFreqTicks_L1 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_2_period_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks_L1);
}

int uz_d_gan_inverter_get_PWMhightimeTicks_L1(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMhightimeTicks_L1 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_2_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks_L1);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks_L1(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMlowtimeTicks_L1 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_2_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks_L1);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_2_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent_L1 = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent_L1);
}

int uz_d_gan_inverter_get_PWMFreqTicks_H2(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMFreqTicks_H2 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_3_period_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks_H2);
}

int uz_d_gan_inverter_get_PWMhightimeTicks_H2(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMhightimeTicks_H2 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_3_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks_H2);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks_H2(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMlowtimeTicks_H2 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_3_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks_H2);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_3_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent_H2 = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent_H2);
}

int uz_d_gan_inverter_get_PWMFreqTicks_L2(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMFreqTicks_L2 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_4_period_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks_L2);
}

int uz_d_gan_inverter_get_PWMhightimeTicks_L2(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMhightimeTicks_L2 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_4_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks_L2);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks_L2(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMlowtimeTicks_L2 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_4_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks_L2);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_4_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent_L2 = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent_L2);
}

int uz_d_gan_inverter_get_PWMFreqTicks_H3(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMFreqTicks_H3 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_5_period_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks_H3);
}

int uz_d_gan_inverter_get_PWMhightimeTicks_H3(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMhightimeTicks_H3 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_5_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks_H3);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks_H3(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMlowtimeTicks_H3 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_5_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks_H3);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_5_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent_H3 = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent_H3);
}

int uz_d_gan_inverter_get_PWMFreqTicks_L3(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMFreqTicks_L3 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_6_period_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks_L3);
}

int uz_d_gan_inverter_get_PWMhightimeTicks_L3(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMhightimeTicks_L3 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_6_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks_L3);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks_L3(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->PWMlowtimeTicks_L3 = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_6_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks_L3);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_6_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent_L3 = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent_L3);
}

int uz_d_gan_inverter_get_OC_GaN(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->OC_GaN = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN);
}

int uz_d_gan_inverter_get_FAULT_GaN(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->FAULT_GaN = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN);
}

int uz_d_gan_inverter_get_I_DIAG(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->I_DIAG = uz_axi_read_uint32(self->base_address + AXI_I_DIAG_Data_UZ_D_GaN_Inverter);
	return(self->I_DIAG);
}

void uz_d_gan_inverter_set_PWM_EN(uz_d_gan_inverter_handle self, uint32_t PWM_on_off) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(PWM_on_off == true || PWM_on_off == false);
	self->PWM_EN = PWM_on_off;
	uz_axi_write_uint32(self->base_address + AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
}
