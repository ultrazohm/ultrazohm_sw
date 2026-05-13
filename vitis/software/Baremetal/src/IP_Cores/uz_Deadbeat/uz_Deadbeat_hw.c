
#include "uz_Deadbeat_hw.h"
#include "uz_Deadbeat_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_Deadbeat_hw_write_id_ref(uint32_t base_address, int32_t id_ref)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + id_ref_Data_uz_Deadbeat_ip, id_ref);
}

void uz_Deadbeat_hw_write_iq_ref(uint32_t base_address, int32_t iq_ref)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + iq_ref_Data_uz_Deadbeat_ip, iq_ref);
}

void uz_Deadbeat_hw_write_id(uint32_t base_address, int32_t id)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + id_Data_uz_Deadbeat_ip, id);
}

void uz_Deadbeat_hw_write_iq(uint32_t base_address, int32_t iq)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + iq_Data_uz_Deadbeat_ip, iq);
}

void uz_Deadbeat_hw_write_theta(uint32_t base_address, int32_t theta)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + theta_Data_uz_Deadbeat_ip, theta);
}

void uz_Deadbeat_hw_write_theta_0(uint32_t base_address, int32_t theta_0)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + theta_0_Data_uz_Deadbeat_ip, theta_0);
}

void uz_Deadbeat_hw_write_w_e(uint32_t base_address, int32_t w_e)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + w_e_Data_uz_Deadbeat_ip, w_e);
}

void uz_Deadbeat_hw_write_ua_0(uint32_t base_address, int32_t ua_0)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + ua_0_input_Data_uz_Deadbeat_ip, ua_0);
}

void uz_Deadbeat_hw_write_ub_0(uint32_t base_address, int32_t ub_0)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + ub_0_input_Data_uz_Deadbeat_ip, ub_0);
}

void uz_Deadbeat_hw_write_uc_0(uint32_t base_address, int32_t uc_0)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + uc_0_input_Data_uz_Deadbeat_ip, uc_0);
}

int32_t uz_Deadbeat_hw_read_ua_0(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address + ua_0_Data_uz_Deadbeat_ip);
}

int32_t uz_Deadbeat_hw_read_ub_o(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address + ub_o_Data_uz_Deadbeat_ip);
}

int32_t uz_Deadbeat_hw_read_uc_0(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address + uc_0_Data_uz_Deadbeat_ip);
}
