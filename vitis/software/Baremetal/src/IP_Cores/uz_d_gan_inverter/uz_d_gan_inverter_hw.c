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

float uz_d_gan_inverter_get_PWMdutyCycPerCent_H1(uint32_t base_address){
	int32_t axi_read_temp;
	axi_read_temp = uz_axi_read_uint32(base_address + AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter);
	return(uz_convert_sfixed_to_float(axi_read_temp,24));
}

// uint32_t uz_d_gan_inverter_get_PWMFreqTicks_L1(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_L1(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_L1(uint32_t base_address){

// }

// float uz_d_gan_inverter_get_PWMdutyCycPerCent_L1(){

// }

// uint32_t uz_d_gan_inverter_get_PWMFreqTicks_H2(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_H2(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_H2(uint32_t base_address){


// float uz_d_gan_inverter_get_PWMdutyCycPerCent_H2(){

// }

// uint32_t uz_d_gan_inverter_get_PWMFreqTicks_L2(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_L2(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_L2(uint32_t base_address){

// }

// float uz_d_gan_inverter_get_PWMdutyCycPerCent_L2(){

// }

// uint32_t uz_d_gan_inverter_get_PWMFreqTicks_H3(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_H3(uint32_t base_addressf){

// }

// uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_H3(uint32_t base_address){

// }

// float uz_d_gan_inverter_get_PWMdutyCycPerCent_H3(){

// }

// uint32_t uz_d_gan_inverter_get_PWMFreqTicks_L3(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMhightimeTicks_L3(uint32_t base_address){

// }

// uint32_t uz_d_gan_inverter_get_PWMlowtimeTicks_L3(uint32_t base_address){

// }

// float uz_d_gan_inverter_get_PWMdutyCycPerCent_L3(){

// }

// uint32_t uz_d_gan_inverter_get_OC_GaN(uint32_t base_address) {

// }

// uint32_t uz_d_gan_inverter_get_FAULT_GaN(uint32_t base_address) {

// }

// uint32_t uz_d_gan_inverter_get_I_DIAG(uint32_t base_address) {

// }

void uz_d_gan_inverter_hw_set_PWM_EN(uint32_t base_address, uint32_t PWM_on_off){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + AXI_PWM_Enable_Data_UZ_D_GaN_Inverter, PWM_on_off);
}
