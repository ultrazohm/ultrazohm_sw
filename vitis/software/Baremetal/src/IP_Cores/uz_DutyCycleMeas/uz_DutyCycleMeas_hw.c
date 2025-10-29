#include "uz_DutyCycleMeas_hw.h"
#include "uz_DutyCycleMeas_hwAddresses.h"
#include "../../uz/uz_AXI.h"

uint32_t uz_DutyCycleMeas_hw_get_PWMperiodTicks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_period_Data_uz_dutycyclemeas_ip));
}

uint32_t uz_DutyCycleMeas_hw_get_PWMhightimeTicks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_hightime_Data_uz_dutycyclemeas_ip));
}

uint32_t uz_DutyCycleMeas_hw_get_PWMlowtimeTicks(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_lowtime_Data_uz_dutycyclemeas_ip));
}

float uz_DutyCycleMeas_hw_get_DutyCycle(uint32_t base_address){
    float DutyCycle;
    DutyCycle = (float)uz_DutyCycleMeas_hw_get_PWMhightimeTicks(base_address) / (float)uz_DutyCycleMeas_hw_get_PWMperiodTicks(base_address);
	return(DutyCycle);
}
