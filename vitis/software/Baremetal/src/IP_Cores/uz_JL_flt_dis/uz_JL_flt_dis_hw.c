
#include "uz_JL_flt_dis_hw.h"
#include "uz_JL_flt_dis_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_JL_flt_dis_hw_write_FLT_PS(uint32_t base_address, bool flt_ps)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + FLT_PS_Data_uz_JL_flt_ip, flt_ps);
}

void uz_JL_flt_dis_hw_write_FLT_RST(uint32_t base_address, bool reset)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + FLT_RST_Data_uz_JL_flt_ip, reset);
}

void uz_JL_flt_dis_hw_write_use_flt_dis(uint32_t base_address, bool use_flt_dis)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + use_flt_dis_Data_uz_JL_flt_ip, use_flt_dis);
}

uint32_t uz_JL_flt_dis_hw_read_FLT_ps(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + FLT_ps_Data_uz_JL_flt_ip);
}
