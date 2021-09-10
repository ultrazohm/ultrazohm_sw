#include "uz_incrementalEncoder_hw.h"
#include "IncreEncoder_V24_ip_addr.h"

void uz_incrementalEncoder_hw_set_timer_fpga_ms(uint32_t base_address, uint32_t timer_ms){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip,timer_ms);
}


void uz_incrementalEncoder_hw_set_pi2_inc(uint32_t base_address, uint32_t pi2_inc){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+PI2_Inc_AXI4_Data_IncreEncoder_V24_ip,pi2_inc);
}


