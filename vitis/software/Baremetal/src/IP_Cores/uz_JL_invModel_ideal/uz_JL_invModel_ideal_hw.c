
#include "uz_JL_invModel_ideal_hw.h"
#include "uz_JL_invModel_ideal_hwAddresses.h"
#include "../../uz/uz_AXI.h"


void uz_JL_invModel_ideal_hw_write_Udc(uint32_t base_address, float Udc)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address + Udc_Data_uz_JL_invModel_ideal, Udc);
}

float uz_JL_invModel_ideal_hw_read_out_Ua(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+InvOut_PS_Data_uz_JL_invModel_ideal);
}

float uz_JL_invModel_ideal_hw_read_out_Ub(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+InvOut_PS_Data_uz_JL_invModel_ideal + 0x004);
}

float uz_JL_invModel_ideal_hw_read_out_Uc(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+InvOut_PS_Data_uz_JL_invModel_ideal + 0x008);
}

void uz_JL_invModel_ideal_hw_trigger_output_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+InvOut_PS_Strobe_uz_JL_invModel_ideal,true);
    uz_axi_write_bool(base_address+InvOut_PS_Strobe_uz_JL_invModel_ideal,false);
}


