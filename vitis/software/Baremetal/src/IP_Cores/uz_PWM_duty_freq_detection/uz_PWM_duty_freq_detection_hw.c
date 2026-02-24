#include "uz_PWM_duty_freq_detection_hw.h"
#include "uz_PWM_duty_freq_detection_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"


uint32_t uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_period_Data_uz_pwmdutyfreqdetection));
}

uint32_t uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_hightime_Data_uz_pwmdutyfreqdetection));
}

uint32_t uz_PWM_duty_freq_detection_hw_get_PWM_lowtime_ticks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_lowtime_Data_uz_pwmdutyfreqdetection));
}