#include "uz_count_switching_hw.h"
#include "uz_count_switching_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_count_switching_hw_reset(uint32_t base_address, bool reset){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + bResetAXI_Data_uz_count_ip, reset);
}
uint32_t uz_count_switching_hw_read_count_0(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_0_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_1_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_2_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_3(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_3_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_4(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_4_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_5(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_5_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_6(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_6_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_7(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_7_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_8(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_8_AXI_Data_uz_count_ip);
}

uint32_t uz_count_switching_hw_read_count_sum(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + count_out_sum_AXI1_Data_uz_count_ip);
}
