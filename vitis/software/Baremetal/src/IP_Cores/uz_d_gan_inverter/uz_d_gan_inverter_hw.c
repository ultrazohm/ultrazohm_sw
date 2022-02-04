#include "uz_d_gan_inverter_hw.h"
#include "uz_d_gan_inverter_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

uint32_t uz_d_gan_inverter_get_PWMFreqTicks_H1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_1_period_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_H1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_1_hightime_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_H1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_1_lowtime_Data_UZ_D_GaN_Inverter));
}

float uz_d_gan_inverter_get_PWMdutyCycNormalized_H1(uint32_t base_address){
	uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_d_gan_inverter_get_PWMFreqTicks_L1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_2_period_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_L1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_2_hightime_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_L1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_2_lowtime_Data_UZ_D_GaN_Inverter));
}

float uz_d_gan_inverter_get_PWMdutyCycNormalized_L1(uint32_t base_address){
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Gan_Temp_2_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_d_gan_inverter_get_PWMFreqTicks_H2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_3_period_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_H2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_3_hightime_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_H2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_3_lowtime_Data_UZ_D_GaN_Inverter));
}

float uz_d_gan_inverter_get_PWMdutyCycNormalized_H2(uint32_t base_address){
	uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Gan_Temp_3_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_d_gan_inverter_get_PWMFreqTicks_L2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_4_period_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_L2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_4_hightime_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_L2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_4_lowtime_Data_UZ_D_GaN_Inverter));
}

float uz_d_gan_inverter_get_PWMdutyCycNormalized_L2(uint32_t base_address){
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Gan_Temp_4_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_d_gan_inverter_get_PWMFreqTicks_H3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_5_period_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_H3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_5_hightime_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_H3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_5_lowtime_Data_UZ_D_GaN_Inverter));
}

float uz_d_gan_inverter_get_PWMdutyCycNormalized_H3(uint32_t base_address){
	uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Gan_Temp_5_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_d_gan_inverter_get_PWMFreqTicks_L3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_6_period_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_L3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_6_hightime_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_L3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Gan_Temp_6_lowtime_Data_UZ_D_GaN_Inverter));
}

float uz_d_gan_inverter_get_PWMdutyCycNormalized_L3(uint32_t base_address){
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Gan_Temp_6_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_d_gan_inverter_get_OC_GaN(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_GaN_OC_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_FAULT_GaN(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_GaN_FAULT_Data_UZ_D_GaN_Inverter));
}

uint32_t uz_d_gan_inverter_get_I_DIAG(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_I_DIAG_Data_UZ_D_GaN_Inverter));
}

void uz_d_gan_inverter_hw_set_PWM_EN(uint32_t base_address, uint32_t PWM_on_off){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
}
