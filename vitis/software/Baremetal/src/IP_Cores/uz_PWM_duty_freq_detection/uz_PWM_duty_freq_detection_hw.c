#include "uz_PWM_duty_freq_detection_hw.h"
#include "uz_PWM_duty_freq_detection_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

uint32_t uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + AXI_PERIOD_DATA_UZ_PWMDUTYFREQDETECTION);
}

uint32_t uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + AXI_HIGHTIME_DATA_UZ_PWMDUTYFREQDETECTION);
}

uint32_t uz_PWM_duty_freq_detection_hw_get_PWM_lowtime_ticks(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + AXI_LOWTIME_DATA_UZ_PWMDUTYFREQDETECTION);
}

void uz_PWM_duty_freq_detection_hw_trigger_output_strobe(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + AXI_OUTPUT_STROBE_UZ_PWMDUTYFREQDETECTION, true);
    uz_axi_write_bool(base_address + AXI_OUTPUT_STROBE_UZ_PWMDUTYFREQDETECTION, false);
}
