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
	self->PWMFreqTicks = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_freq_Data_UZ_D_GaN_Inverter);
	return(self->PWMFreqTicks);
}

int uz_d_gan_inverter_get_PWMhightimeTicks(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	self->PWMhightimeTicks = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_hightime_Data_UZ_D_GaN_Inverter);
	return(self->PWMhightimeTicks);
}

int uz_d_gan_inverter_get_PWMlowtimeTicks(uz_d_gan_inverter_handle self){
	uz_assert_not_NULL(self);
	self->PWMlowtimeTicks = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_lowtime_Data_UZ_D_GaN_Inverter);
	return(self->PWMlowtimeTicks);
}

float uz_d_gan_inverter_get_PWMdutyCycPerCent(uz_d_gan_inverter_handle self){
	int32_t axi_read_temp;

	uz_assert_not_NULL(self);
	axi_read_temp = uz_axi_read_uint32(self->base_address + AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter);
	self->PWMdutyCycPerCent = (uz_convert_sfixed_to_float(axi_read_temp,24));
	return(self->PWMdutyCycPerCent);
}

int uz_d_gan_inverter_get_OC_GaN_H1(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->OC_GaN_H1 = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_H1_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN_H1);
}

int uz_d_gan_inverter_get_OC_GaN_L1(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->OC_GaN_L1 = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_L1_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN_L1);
}

int uz_d_gan_inverter_get_OC_GaN_H2(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->OC_GaN_H2 = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_H2_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN_H2);
}

int uz_d_gan_inverter_get_OC_GaN_L2(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->OC_GaN_L2 = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_L2_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN_L2);
}

int uz_d_gan_inverter_get_OC_GaN_H3(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->OC_GaN_H3 = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_H3_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN_H3);
}

int uz_d_gan_inverter_get_OC_GaN_L3(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->OC_GaN_L3 = uz_axi_read_uint32(self->base_address + AXI_GaN_OC_L3_Data_UZ_D_GaN_Inverter);
	return(self->OC_GaN_L3);
}

int uz_d_gan_inverter_get_FAULT_GaN_H1(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->FAULT_GaN_H1 = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_H1_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN_H1);
}

int uz_d_gan_inverter_get_FAULT_GaN_L1(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->FAULT_GaN_L1 = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_L1_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN_L1);
}

int uz_d_gan_inverter_get_FAULT_GaN_H2(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->FAULT_GaN_H2 = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_H2_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN_H2);
}

int uz_d_gan_inverter_get_FAULT_GaN_L2(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->FAULT_GaN_L2 = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_L2_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN_L2);
}

int uz_d_gan_inverter_get_FAULT_GaN_H3(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->FAULT_GaN_H3 = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_H3_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN_H3);
}

int uz_d_gan_inverter_get_FAULT_GaN_L3(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->FAULT_GaN_L3 = uz_axi_read_uint32(self->base_address + AXI_GaN_FAULT_L3_Data_UZ_D_GaN_Inverter);
	return(self->FAULT_GaN_L3);
}

int uz_d_gan_inverter_get_I_DIAG(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->I_DIAG = uz_axi_read_uint32(self->base_address + AXI_I_DIAG_Data_UZ_D_GaN_Inverter);
	return(self->I_DIAG);
}

int uz_d_gan_inverter_get_I1_DIAG(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->I1_DIAG = uz_axi_read_uint32(self->base_address + AXI_I1_DIAG_Data_UZ_D_GaN_Inverter);
	return(self->I1_DIAG);
}

int uz_d_gan_inverter_get_I2_DIAG(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->I2_DIAG = uz_axi_read_uint32(self->base_address + AXI_I2_DIAG_Data_UZ_D_GaN_Inverter);
	return(self->I2_DIAG);
}

int uz_d_gan_inverter_get_I3_DIAG(uz_d_gan_inverter_handle self) {
	uz_assert_not_NULL(self);
	self->I3_DIAG = uz_axi_read_uint32(self->base_address + AXI_I3_DIAG_Data_UZ_D_GaN_Inverter);
	return(self->I3_DIAG);
}

void uz_d_gan_inverter_set_PWM_EN(uz_d_gan_inverter_handle self, uint32_t PWM_on_off) {
	uz_assert_not_NULL(self);
	self->PWM_EN = PWM_on_off;
	uz_axi_write_uint32(self->base_address + AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
}
