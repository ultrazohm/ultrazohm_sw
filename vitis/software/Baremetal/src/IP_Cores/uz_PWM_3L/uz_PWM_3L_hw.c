#include "uz_PWM_3L_hw.h"
#include "uz_PWM_3L_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_PWM_3L_hw_set_carrier_f(uint32_t base_address, uint32_t f_carrier_hz)
{
    uz_assert_not_zero_uint32(base_address);
    uint32_t scal_t_carrier = 100000000U / f_carrier_hz; // core runs at 100MHz, so 10ns period
    uz_axi_write_uint32(base_address + Scal_T_carrier_AXI_Data_PWM_3Level_control, scal_t_carrier);
}

void uz_PWM_3L_hw_set_carrier_arrangement(uint32_t base_address, float arrangement)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_float(base_address + Scal_carrier_arrangement_Data_PWM_3Level_control,  arrangement);
}

void uz_PWM_3L_hw_enable_IP_core(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address + IPCore_Enable_PWM_3Level_control, 1); // Enable IP core
}

void uz_PWM_3L_hw_set_u1(uint32_t base_address, float u1){
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + m_u1_norm_Data_PWM_3Level_control, u1);
}

void uz_PWM_3L_get_switch_states(uint32_t base_address, uint8_t *states){
	uz_assert_not_zero_uint32(base_address);
	states[0] = uz_axi_read_uint32(base_address + SS0_OUT_Data_PWM_3Level_control);
	states[1] = uz_axi_read_uint32(base_address + SS1_OUT_Data_PWM_3Level_control);
	states[2] = uz_axi_read_uint32(base_address + SS2_OUT_Data_PWM_3Level_control);
	states[3] = uz_axi_read_uint32(base_address + SS3_OUT_Data_PWM_3Level_control);
}
