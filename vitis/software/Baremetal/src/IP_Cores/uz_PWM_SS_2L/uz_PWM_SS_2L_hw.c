#include "uz_PWM_SS_2L_hw.h"
#include "uz_PWM_SS_2L_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_PWM_SS_2L_hw_SetExternalCounterSource(uint32_t base_address, uint32_t CntExtSrc_on_off){
    uz_assert_not_zero(base_address);
    uz_assert(CntExtSrc_on_off<=1);
    uz_axi_write_uint32(base_address + count_src_ext_AXI_Data_PWM_and_SS_control_V4_ip, CntExtSrc_on_off);
}

void uz_PWM_SS_2L_hw_SetDutyCycle(uint32_t base_address, float dutyCyc_A, float dutyCyc_B, float dutyCyc_C){
    uz_assert_not_zero(base_address);
    uz_assert(dutyCyc_A>=0 && dutyCyc_A<=1.0);
    uz_assert(dutyCyc_B>=0 && dutyCyc_B<=1.0);
    uz_assert(dutyCyc_C>=0 && dutyCyc_C<=1.0);
    int32_t m_u1_norm = uz_convert_float_to_sfixed(dutyCyc_A,12);
    int32_t m_u2_norm = uz_convert_float_to_sfixed(dutyCyc_B,12);
    int32_t m_u3_norm = uz_convert_float_to_sfixed(dutyCyc_C,12);
    uz_axi_write_uint32(base_address + m_u1_norm_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)m_u1_norm);
    uz_axi_write_uint32(base_address + m_u2_norm_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)m_u2_norm);
    uz_axi_write_uint32(base_address + m_u3_norm_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)m_u3_norm);
}

void uz_PWM_SS_2L_hw_SetStatus(uint32_t base_address, uint32_t PWM_en){
    uz_assert_not_zero(base_address);
    uz_assert(PWM_en<=1);
    uz_axi_write_uint32(base_address + PWM_en_AXI_Data_PWM_and_SS_control_V4_ip, PWM_en);
}

void uz_PWM_SS_2L_hw_SetMode(uint32_t base_address, uint32_t PWM_mode){
    uz_assert_not_zero(base_address);
    uz_assert(PWM_mode<=2);
    uz_axi_write_uint32(base_address + Mode_AXI_Data_PWM_and_SS_control_V4_ip, PWM_mode);
}

void uz_PWM_SS_2L_hw_SetCarrierFrequency(uint32_t base_address, uint32_t ip_clk_frequency_Hz, float PWM_freq_Hz){
    uz_assert_not_zero(base_address);
    uz_assert_not_zero(ip_clk_frequency_Hz);
    float PWM_Scal_f_carrier = (PWM_freq_Hz/(ip_clk_frequency_Hz*0.5));
    int32_t PWM_Scal_f_carrier_Q26 = uz_convert_float_to_sfixed(PWM_Scal_f_carrier,26);
    // PWM carrier signal frequency is set, e.g. 100 kHz
    uz_axi_write_uint32(base_address + Scal_f_carrier_AXI_Data_PWM_and_SS_control_V4_ip, PWM_Scal_f_carrier_Q26);
    // calculate PWM period in microseconds	
    float PWM_period_us = 1.0f/(PWM_freq_Hz)*1e6;
    // Set carrier signal period time (T_carrier = 1/PWM_period)
	float PWM_Scal_T_carrier = (PWM_period_us*((ip_clk_frequency_Hz*1e-6)*0.5));
    // PWM carrier signal Period is set to 1/PWM_freq, e.g. 10 us
    uz_axi_write_uint32(base_address + Scal_T_carrier_AXI_Data_PWM_and_SS_control_V4_ip, (uint32_t)PWM_Scal_T_carrier);
}

void uz_PWM_SS_2L_hw_SetMinimumPulseWidth(uint32_t base_address, float min_pulse_width_percent){
    uz_assert_not_zero(base_address);
    uz_assert(min_pulse_width_percent>=0);
    int32_t min_pulse_width_percent_Q12 = uz_convert_float_to_sfixed(min_pulse_width_percent,12);
    uz_axi_write_uint32(base_address + PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V4_ip, min_pulse_width_percent_Q12);
}

void uz_PWM_SS_2L_hw_SetTristate(uint32_t base_address, uint32_t halfBridgeNumber, uint32_t TriState_true_false){
    uz_assert_not_zero(base_address);
    uz_assert_not_zero(halfBridgeNumber);
    uz_assert(halfBridgeNumber<=3);
    uz_assert(TriState_true_false<=1);
    uint32_t halfBridgeAddress = 0;
    switch (halfBridgeNumber) {
        case 1  :
            halfBridgeAddress = TriState_HB1_AXI_Data_PWM_and_SS_control_V4_ip;
            break;

        case 2  :
            halfBridgeAddress = TriState_HB2_AXI_Data_PWM_and_SS_control_V4_ip;
            break;

        case 3  :
            halfBridgeAddress = TriState_HB3_AXI_Data_PWM_and_SS_control_V4_ip;
            break;
    }
    uz_axi_write_uint32(base_address + halfBridgeAddress, TriState_true_false);
}
