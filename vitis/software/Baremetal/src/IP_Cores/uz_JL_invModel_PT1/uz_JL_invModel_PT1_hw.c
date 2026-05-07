#include "uz_JL_invModel_PT1_hwAdresses.h"
#include "uz_JL_invModel_PT1_hw.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_JL_invModel_PT1_hw_write_reset(uint32_t base_address,bool reset){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+InvConf_PT1_reset_Data_uz_JL_Inv_PT1,reset);
}

void uz_JL_invModel_PT1_hw_write_time_constant(uint32_t base_address, float time_constant){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+InvConf_PT1_Ts_Data_uz_JL_Inv_PT1,time_constant);
}

void uz_JL_invModel_PT1_hw_write_gain(uint32_t base_address,float gain){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+InvConf_PT1_Gain_Data_uz_JL_Inv_PT1,gain);
}

void uz_JL_invModel_PT1_hw_write_Ualpha(uint32_t base_address, float input){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+InvIn_Ualpha_Data_uz_JL_Inv_PT1,input);
}

void uz_JL_invModel_PT1_hw_write_Ubeta(uint32_t base_address, float input){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+InvIn_Ubeta_Data_uz_JL_Inv_PT1,input);
}