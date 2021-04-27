#include "uz_axiTestIP2_hw.h"

void uz_axiTestIP2_hw_write_A_int32(uint32_t base_address, int32_t A){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+A_int32_Data_uz_axi_testIP, A);
}
void uz_axiTestIP2_hw_write_B_int32(uint32_t base_address, int32_t B){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+B_int32_Data_uz_axi_testIP, B);
}

int32_t uz_axiTestIP2_hw_read_C_int32(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address+C_int32_Data_uz_axi_testIP) );
}