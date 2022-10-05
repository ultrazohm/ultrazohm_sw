#include "uz_myIP_hw.h"
#include "uz_myIP_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_myIP_hw_write_A(uint32_t base_address,int32_t A){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+A_int32_Data_uz_axi_testIP,A);
}

void uz_myIP_hw_write_B(uint32_t base_address,int32_t B){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+B_int32_Data_uz_axi_testIP,B);
}

int32_t uz_myIP_hw_read_C(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address+C_int32_Data_uz_axi_testIP));
}

void uz_myIP_hw_write_A_uint(uint32_t base_address,uint32_t A){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+A_uint32_Data_uz_axi_testIP,A);
}

void uz_myIP_hw_write_B_uint(uint32_t base_address,uint32_t B){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+B_uint32_Data_uz_axi_testIP,B);
}

uint32_t uz_myIP_hw_read_C_uint(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+C_uint32_Data_uz_axi_testIP));
}