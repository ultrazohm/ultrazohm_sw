#include "uz_PWM_SS_2L_hw.h"
#include "uz_PWM_SS_2L_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_PWM_SS_2L_hw_SetExternalCounterSource(uint32_t base_address, bool use_external_counter){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + count_src_ext_AXI_Data_PWM_and_SS_control_V4_ip, use_external_counter);
}

void uz_PWM_SS_2L_hw_SetDutyCycle(uint32_t base_address, float dutyCyc_HB1, float dutyCyc_HB2, float dutyCyc_HB3){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(dutyCyc_HB1>=0.0f);
    uz_assert(dutyCyc_HB1<=1.0f);
    uz_assert(dutyCyc_HB2>=0.0f);
    uz_assert(dutyCyc_HB2<=1.0f);
    uz_assert(dutyCyc_HB3>=0.0f);
    uz_assert(dutyCyc_HB3<=1.0f);        
    int32_t m_u1_norm = uz_convert_float_to_sfixed(dutyCyc_HB1,16);
    int32_t m_u2_norm = uz_convert_float_to_sfixed(dutyCyc_HB2,16);
    int32_t m_u3_norm = uz_convert_float_to_sfixed(dutyCyc_HB3,16);
    uz_axi_write_uint32(base_address + m_u1_norm_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)m_u1_norm);
    uz_axi_write_uint32(base_address + m_u2_norm_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)m_u2_norm);
    uz_axi_write_uint32(base_address + m_u3_norm_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)m_u3_norm);
}

void uz_PWM_SS_2L_hw_SetStatus(uint32_t base_address, bool PWM_en){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + PWM_en_AXI_Data_PWM_and_SS_control_V4_ip, PWM_en);
}

void uz_PWM_SS_2L_hw_SetMode(uint32_t base_address, uint32_t PWM_mode){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(PWM_mode<=2U);
    uz_axi_write_uint32(base_address + Mode_AXI_Data_PWM_and_SS_control_V4_ip, PWM_mode);
}

void uz_PWM_SS_2L_hw_SetCarrierFrequency(uint32_t base_address, uint32_t ip_clk_frequency_Hz, float PWM_freq_Hz){
    uz_assert_not_zero_uint32(base_address);
    uz_assert_not_zero_uint32(ip_clk_frequency_Hz);
    float PWM_Scal_f_carrier = (PWM_freq_Hz/( (float)ip_clk_frequency_Hz*0.5f));
    int32_t PWM_Scal_f_carrier_Q26 = uz_convert_float_to_sfixed(PWM_Scal_f_carrier,26);
    // PWM carrier signal frequency is set, e.g. 100 kHz
    uz_axi_write_uint32(base_address + Scal_f_carrier_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)PWM_Scal_f_carrier_Q26);
    // calculate PWM period in microseconds	
    float PWM_period_us = 1.0f/(PWM_freq_Hz)*1e6f;
    // Set carrier signal period time (T_carrier = 1/PWM_period)
	float PWM_Scal_T_carrier = (PWM_period_us*(( (float)ip_clk_frequency_Hz*1e-6f)*0.5f));
    // PWM carrier signal Period is set to 1/PWM_freq, e.g. 10 us
    uz_axi_write_uint32(base_address + Scal_T_carrier_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)PWM_Scal_T_carrier);
}

void uz_PWM_SS_2L_hw_SetMinimumPulseWidth(uint32_t base_address, float min_pulse_width_percent){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(min_pulse_width_percent>=0.0f);
    int32_t min_pulse_width_percent_Q16 = uz_convert_float_to_sfixed(min_pulse_width_percent,16);
    uz_axi_write_uint32(base_address + PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)min_pulse_width_percent_Q16);
}

void uz_PWM_SS_2L_hw_SetTristate(uint32_t base_address, bool Tristate_HB1, bool Tristate_HB2, bool Tristate_HB3)
{
    uz_assert_not_zero_uint32(base_address);
    uint32_t tristate_status = 0xFFFFU;

    if (!Tristate_HB1) {
        tristate_status &= ~(1U << 0);
    }
    if (!Tristate_HB2) {
        tristate_status &= ~(1U << 1);
    }
    if (!Tristate_HB3) {
        tristate_status &= ~(1U << 2);
    }

    uz_axi_write_uint32(base_address + TriState_HB_AXI_Data_PWM_and_SS_control_V4_ip, tristate_status);
}

void uz_PWM_SS_2L_hw_SetTriangleShift(uint32_t base_address, float triangle_shift_HB1, float triangle_shift_HB2, float triangle_shift_HB3){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(triangle_shift_HB1 >= 0.0f);
    uz_assert(triangle_shift_HB1 <= 1.0f);
    uz_assert(triangle_shift_HB2 >= 0.0f);
    uz_assert(triangle_shift_HB2 <= 1.0f);
    uz_assert(triangle_shift_HB3 >= 0.0f);
    uz_assert(triangle_shift_HB3 <= 1.0f);
    uint32_t triangle_shift_HB1_Q17 = uz_convert_float_to_unsigned_fixed(triangle_shift_HB1, 17);
    uint32_t triangle_shift_HB2_Q17 = uz_convert_float_to_unsigned_fixed(triangle_shift_HB2, 17);
    uint32_t triangle_shift_HB3_Q17 = uz_convert_float_to_unsigned_fixed(triangle_shift_HB3, 17);
    uz_axi_write_uint32(base_address + triangle_shift_HB1_AXI_Data_PWM_and_SS_control_V4_ip, triangle_shift_HB1_Q17);
    uz_axi_write_uint32(base_address + triangle_shift_HB2_AXI_Data_PWM_and_SS_control_V4_ip, triangle_shift_HB2_Q17);
    uz_axi_write_uint32(base_address + triangle_shift_HB3_AXI_Data_PWM_and_SS_control_V4_ip, triangle_shift_HB3_Q17);
}

void uz_PWM_SS_2L_hw_SetTriggerSource(uint32_t base_address, uint32_t trigger_source) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(trigger_source <= 2U); 
    uz_axi_write_uint32(base_address + PWM_trigger_source_AXI_Data_PWM_and_SS_control_V4_ip, trigger_source);
    
}
