
#include "uz_JL_SDDemod_hw.h"

#include "uz_JL_SDDemod_hwAddresses.h"
#include "../../uz/uz_AXI.h"


void uz_JL_SDDemod_hw_write_R_axi(uint32_t base_address, uint16_t R_axi)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + R_axi_Data_uz_JL_SDDemod, R_axi);
}

int32_t uz_JL_SDDemod_hw_read_data(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_Data_uz_JL_SDDemod);
}