#include "uz_PWM_duty_freq_detection_hw.h"
#include "uz_PWM_duty_freq_detection_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"


uint32_t uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_period_Data_uz_pwmdutyfreqdetection));
}

uint32_t uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_hightime_Data_uz_pwmdutyfreqdetection));
}

uint32_t uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_lowtime_Data_uz_pwmdutyfreqdetection));
}

float uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized(uint32_t base_address){
	uz_assert_not_zero(base_address);
    uint32_t axi_read_tempAsDutyCyc;
	axi_read_tempAsDutyCyc = uz_axi_read_uint32(base_address + AXI_dutycyc_Data_uz_pwmdutyfreqdetection);
	return(uz_convert_sfixed_to_float(axi_read_tempAsDutyCyc,31));
}
