#include "uz_JL_invModel_PT1_hwAdresses.h"
#include "uz_JL_invModel_PT1_hw.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_JL_invModel_PT1_hw_write_reset(uint32_t base_address,bool reset){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+PT1_reset_Data_uz_JL_InvModel_PT1,reset);
}

void uz_JL_invModel_PT1_hw_write_time_constant(uint32_t base_address, float time_constant){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+PT1_Ts_Data_uz_JL_InvModel_PT1,time_constant);
}

void uz_JL_invModel_PT1_hw_write_gain(uint32_t base_address,float gain){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+PT1_Gain_Data_uz_JL_InvModel_PT1,gain);
}

void uz_JL_invModel_PT1_hw_write_Ualpha(uint32_t base_address, float input){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+Ualpha_Data_uz_JL_InvModel_PT1,input);
}

void uz_JL_invModel_PT1_hw_write_Ubeta(uint32_t base_address, float input){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+Ubeta_Data_uz_JL_InvModel_PT1,input);
}

float uz_JL_invModel_PT1_hw_read_out_Ua(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+InvOut_PS_Data_uz_JL_InvModel_PT1);
}

float uz_JL_invModel_PT1_hw_read_out_Ub(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+InvOut_PS_Data_uz_JL_InvModel_PT1 + 0x004);
}

float uz_JL_invModel_PT1_hw_read_out_Uc(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+InvOut_PS_Data_uz_JL_InvModel_PT1 + 0x008);
}

void uz_JL_invModel_PT1_hw_trigger_output_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+InvOut_PS_Strobe_uz_JL_InvModel_PT1,true);
    uz_axi_write_bool(base_address+InvOut_PS_Strobe_uz_JL_InvModel_PT1,false);
}
