#include "uz_PWM_3L_hw.h"
#include "uz_PWM_3L_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_PWM_3L_hw_set_carrier_f(uint32_t base_address, uint32_t f_carrier_hz)
{
    uz_assert_not_zero_uint32(base_address);
    uint32_t scal_t_carrier = (uint32_t)50000000*(1.0/f_carrier_hz); //amount of IPcore clock cycles per carrier cycle
    uz_axi_write_uint32(base_address + Scal_T_carrier_AXI_Data_PWM_3Level_control, scal_t_carrier);
}

void uz_PWM_3L_hw_enable_IP_core(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address + PWM_en_AXI_Data_PWM_3Level_control, 1); // Enable IP core
}

void uz_PWM_3L_hw_set_u1(uint32_t base_address, float u1){
	uz_assert_not_zero_uint32(base_address);
	u1 = u1*pow(2,12);
	uint32_t u1_cast = (uint32_t)u1;
	uz_axi_write_uint32(base_address + m_u1_norm_Data_PWM_3Level_control, u1_cast);
}

void uz_PWM_3L_get_switch_states(uint32_t base_address, uint8_t states[][4]){
	uz_assert_not_zero_uint32(base_address);
	states[0][0] = uz_axi_read_uint32(base_address + SS0_OUT_Data_PWM_3Level_control);
	states[0][1] = uz_axi_read_uint32(base_address + SS1_OUT_Data_PWM_3Level_control);
	states[0][2] = uz_axi_read_uint32(base_address + SS2_OUT_Data_PWM_3Level_control);
	states[0][3] = uz_axi_read_uint32(base_address + SS3_OUT_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_enable_IP_core_readback(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + PWM_en_AXI_readback_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_u1_readback(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + m_u1_norm_readback_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_get_carrier(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + Carrier_out_Data_PWM_3Level_control);
}

uint32_t uz_PWM_3L_hw_carrier_f_readback(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address + Scal_T_carrier_AXI_readback_Data_PWM_3Level_control);
}
