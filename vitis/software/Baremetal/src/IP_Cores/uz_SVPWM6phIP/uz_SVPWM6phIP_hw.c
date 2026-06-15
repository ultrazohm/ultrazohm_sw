#include "uz_SVPWM6phIP_hw.h"
#include "uz_SVPWM6phIP_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_SVPWM6phIP_hw_SetExternalCounterSource(uint32_t base_address, bool use_external_counter){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + count_src_ext_AXI_Data_SVPWM_6ph_ip, use_external_counter);
}

void uz_SVPWM6phIP_hw_Set_T_and_SV(uint32_t base_address, float T1, float T2, float T3, float T4, float T5, uint32_t SV1, uint32_t SV2, uint32_t SV3, uint32_t SV4, uint32_t SV5){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(T1>=0.0f);
    uz_assert(T2>=0.0f);
    uz_assert(T3>=0.0f);
    uz_assert(T4>=0.0f);
    uz_assert(T5>=0.0f);
    uz_assert(T1<=1.0f);
    uz_assert(T2<=1.0f);
    uz_assert(T3<=1.0f);
    uz_assert(T4<=1.0f);
    uz_assert(T5<=1.0f);
    uz_assert(SV1<=63);        
    uz_assert(SV2<=63);
    uz_assert(SV3<=63);
    uz_assert(SV4<=63);
    uz_assert(SV5<=63);
    int32_t T1_norm = uz_convert_float_to_sfixed(T1,16);
    int32_t T2_norm = uz_convert_float_to_sfixed(T2,16);
    int32_t T3_norm = uz_convert_float_to_sfixed(T3,16);
    int32_t T4_norm = uz_convert_float_to_sfixed(T4,16);
    int32_t T5_norm = uz_convert_float_to_sfixed(T5,16);
    uz_axi_write_uint32(base_address + in_T1_AXI_Data_SVPWM_6ph_ip, (uint32_t)T1_norm);
    uz_axi_write_uint32(base_address + in_T2_AXI_Data_SVPWM_6ph_ip, (uint32_t)T2_norm);
    uz_axi_write_uint32(base_address + in_T3_AXI_Data_SVPWM_6ph_ip, (uint32_t)T3_norm);
    uz_axi_write_uint32(base_address + in_T4_AXI_Data_SVPWM_6ph_ip, (uint32_t)T4_norm);
    uz_axi_write_uint32(base_address + in_T5_AXI_Data_SVPWM_6ph_ip, (uint32_t)T5_norm);
    uz_axi_write_uint32(base_address + in_SV1_AXI_Data_SVPWM_6ph_ip, (uint32_t)SV1);
    uz_axi_write_uint32(base_address + in_SV2_AXI_Data_SVPWM_6ph_ip, (uint32_t)SV2);
    uz_axi_write_uint32(base_address + in_SV3_AXI_Data_SVPWM_6ph_ip, (uint32_t)SV3);
    uz_axi_write_uint32(base_address + in_SV4_AXI_Data_SVPWM_6ph_ip, (uint32_t)SV4);
    uz_axi_write_uint32(base_address + in_SV5_AXI_Data_SVPWM_6ph_ip, (uint32_t)SV5);
}

void uz_SVPWM6phIP_hw_SetStatus(uint32_t base_address, bool PWM_en){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + PWM_en_AXI_Data_SVPWM_6ph_ip, PWM_en);
}

void uz_SVPWM6phIP_hw_SetMode(uint32_t base_address, uint32_t PWM_mode){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(PWM_mode<=2U);
    uz_axi_write_uint32(base_address + Mode_AXI_Data_SVPWM_6ph_ip, PWM_mode);
}

void uz_SVPWM6phIP_hw_SetCarrierFrequency(uint32_t base_address, uint32_t ip_clk_frequency_Hz, float PWM_freq_Hz){
    uz_assert_not_zero_uint32(base_address);
    uz_assert_not_zero_uint32(ip_clk_frequency_Hz);
    float PWM_Scal_f_carrier = (PWM_freq_Hz/( (float)ip_clk_frequency_Hz*0.5f));
    int32_t PWM_Scal_f_carrier_Q26 = uz_convert_float_to_sfixed(PWM_Scal_f_carrier,26);
    // PWM carrier signal frequency is set, e.g. 100 kHz
    uz_axi_write_uint32(base_address + Scal_f_carrier_AXI_Data_SVPWM_6ph_ip, (uint32_t)PWM_Scal_f_carrier_Q26);
    // calculate PWM period in microseconds	
    float PWM_period_us = 1.0f/(PWM_freq_Hz)*1e6f;
    // Set carrier signal period time (T_carrier = 1/PWM_period)
	float PWM_Scal_T_carrier = (PWM_period_us*(( (float)ip_clk_frequency_Hz*1e-6f)*0.5f));
    // PWM carrier signal Period is set to 1/PWM_freq, e.g. 10 us
    uz_axi_write_uint32(base_address + Scal_T_carrier_AXI_Data_SVPWM_6ph_ip, (uint32_t)PWM_Scal_T_carrier);
}

void uz_SVPWM6phIP_hw_SetMinimumTon(uint32_t base_address, float min_on_time_percent){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(min_on_time_percent>=0.0f);
    int32_t min_on_time_percent_Q12 = uz_convert_float_to_sfixed(min_on_time_percent,12);
    uz_axi_write_uint32(base_address + PWM_min_SV_time_AXI_Data_SVPWM_6ph_ip, (uint32_t)min_on_time_percent_Q12);
}

void uz_SVPWM6phIP_hw_SetTristate(uint32_t base_address, uint32_t halfBridgeNumber, bool TriState_true_false){
    uz_assert_not_zero_uint32(base_address);
    uz_assert_not_zero_uint32(halfBridgeNumber);
    uz_assert(halfBridgeNumber<=6U);
    uint32_t halfBridgeAddress = 0U;
    switch (halfBridgeNumber) {
        case 1  :
            halfBridgeAddress = TriState_HB1_AXI_Data_SVPWM_6ph_ip;
            break;

        case 2  :
            halfBridgeAddress = TriState_HB2_AXI_Data_SVPWM_6ph_ip;
            break;

        case 3  :
            halfBridgeAddress = TriState_HB3_AXI_Data_SVPWM_6ph_ip;
            break;

        case 4  :
            halfBridgeAddress = TriState_HB4_AXI1_Data_SVPWM_6ph_ip;
            break;

        case 5  :
            halfBridgeAddress = TriState_HB5_AXI1_Data_SVPWM_6ph_ip;
            break;

        case 6  :
            halfBridgeAddress = TriState_HB6_AXI1_Data_SVPWM_6ph_ip;
            break;

        default :
            break;
    }
    uz_axi_write_bool(base_address + halfBridgeAddress, TriState_true_false);
}

void uz_SVPWM6phIP_hw_SetTriggerSource(uint32_t base_address, uint32_t trigger_source) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(trigger_source <= 2U); 
    uz_axi_write_uint32(base_address + PWM_trigger_source_AXI_Data_SVPWM_6ph_ip, trigger_source);
    
}
