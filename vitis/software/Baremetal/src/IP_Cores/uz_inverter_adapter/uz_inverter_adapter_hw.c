#include "uz_inverter_adapter_hw.h"
#include "uz_inverter_adapter_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

uint32_t uz_inverter_adapter_hw_get_PWMFreqTicks_H1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_1_period_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMhightimeTicks_H1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_1_hightime_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMlowtimeTicks_H1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_1_lowtime_Data_uz_d_inverter_adapter));
}

float uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H1(uint32_t base_address){
	uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Temp_1_dutycyc_Data_uz_d_inverter_adapter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_inverter_adapter_hw_get_PWMFreqTicks_L1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_2_period_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMhightimeTicks_L1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_2_hightime_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMlowtimeTicks_L1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_2_lowtime_Data_uz_d_inverter_adapter));
}

float uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L1(uint32_t base_address){
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Temp_2_dutycyc_Data_uz_d_inverter_adapter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_inverter_adapter_hw_get_PWMFreqTicks_H2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_3_period_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMhightimeTicks_H2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_3_hightime_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMlowtimeTicks_H2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_3_lowtime_Data_uz_d_inverter_adapter));
}

float uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H2(uint32_t base_address){
	uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Temp_3_dutycyc_Data_uz_d_inverter_adapter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_inverter_adapter_hw_get_PWMFreqTicks_L2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_4_period_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMhightimeTicks_L2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_4_hightime_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMlowtimeTicks_L2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_4_lowtime_Data_uz_d_inverter_adapter));
}

float uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L2(uint32_t base_address){
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Temp_4_dutycyc_Data_uz_d_inverter_adapter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_inverter_adapter_hw_get_PWMFreqTicks_H3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_5_period_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMhightimeTicks_H3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_5_hightime_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMlowtimeTicks_H3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_5_lowtime_Data_uz_d_inverter_adapter));
}

float uz_inverter_adapter_hw_get_PWMdutyCycNormalized_H3(uint32_t base_address){
	uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Temp_5_dutycyc_Data_uz_d_inverter_adapter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_inverter_adapter_hw_get_PWMFreqTicks_L3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_6_period_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMhightimeTicks_L3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_6_hightime_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_PWMlowtimeTicks_L3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_Temp_6_lowtime_Data_uz_d_inverter_adapter));
}

float uz_inverter_adapter_hw_get_PWMdutyCycNormalized_L3(uint32_t base_address){
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_Temp_6_dutycyc_Data_uz_d_inverter_adapter);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}

uint32_t uz_inverter_adapter_hw_get_OC(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_OC_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_FAULT(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_FAULT_Data_uz_d_inverter_adapter));
}

uint32_t uz_inverter_adapter_hw_get_I_DIAG(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_I_DIAG_Data_uz_d_inverter_adapter));
}

void uz_inverter_adapter_hw_set_PWM_EN(uint32_t base_address, uint32_t PWM_on_off){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + AXI_PWM_Enable_Data_uz_d_inverter_adapter, PWM_on_off);
}
