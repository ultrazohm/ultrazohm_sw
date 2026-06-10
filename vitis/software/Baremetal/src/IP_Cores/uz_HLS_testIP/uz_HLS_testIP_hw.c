#include "uz_HLS_testIP_hw.h"
#include "uz_HLS_testIP_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_HLS_testIP_hw_write_A(uint32_t base_address,int32_t A){
   uz_assert_not_zero_uint32(base_address);
   uz_axi_write_int32(base_address+XUZ_HLS_TESTIP_CONTROL_ADDR_A_DATA,A);
}

void uz_HLS_testIP_hw_write_B(uint32_t base_address,int32_t B){
   uz_assert_not_zero_uint32(base_address);
   uz_axi_write_int32(base_address+XUZ_HLS_TESTIP_CONTROL_ADDR_B_DATA,B);
}

int32_t uz_HLS_testIP_hw_read_result(uint32_t base_address){
   uz_assert_not_zero_uint32(base_address);
   return (uz_axi_read_int32(base_address+XUZ_HLS_TESTIP_CONTROL_ADDR_RESULT_DATA));
}