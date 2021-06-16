#include "uz_plantPT1_hw.h"
#include "uz_plantPT1_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_plantPT1_hw_write_reset(uint32_t base_address,bool reset){
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address+reset_Data_uz_plantModel_pt1,reset);
}

float uz_plantPT1_hw_read_output(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return uz_axi_read_float(base_address+output_Data_uz_plantModel_pt1);
}

void uz_plantPT1_hw_write_time_constant(uint32_t base_address, float time_constant){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+time_constant_Data_uz_plantModel_pt1,time_constant);
}

void uz_plantPT1_hw_write_gain(uint32_t base_address,float gain){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+gain_Data_uz_plantModel_pt1,gain);
}

void uz_plantPT1_hw_write_input(uint32_t base_address, float input){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+input_Data_uz_plantModel_pt1,input);
}