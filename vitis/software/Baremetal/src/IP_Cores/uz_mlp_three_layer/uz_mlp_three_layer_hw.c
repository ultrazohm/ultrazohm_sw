#include "uz_mlp_three_layer_hw.h"
#include "../uz/uz_HAL.h"
#include <math.h>

void uz_mlp_three_layer_hw_write_enable_nn(uint32_t base_address,bool trigger_conversion){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+enable_nn_Data_uz_mlp_three_layer,trigger_conversion);
}

void uz_mlp_three_layer_hw_write_bias_data(uint32_t base_address, float value, struct uz_fixedpoint_definition_t fixedpoint_definition){
    uz_assert_not_zero_uint32(base_address);
    uz_fixedpoint_axi_write(base_address+axi_bias_Data_uz_mlp_three_layer,value,fixedpoint_definition);
}


void uz_mlp_three_layer_hw_write_weight_data(uint32_t base_address, float value, struct uz_fixedpoint_definition_t fixedpoint_definition){
    uz_assert_not_zero_uint32(base_address);
    uz_fixedpoint_axi_write(base_address+axi_weight_Data_uz_mlp_three_layer,value,fixedpoint_definition);
}

void uz_mlp_three_layer_hw_write_weight_address(uint32_t base_address,uint32_t weight_address){
    uz_assert_not_zero_uint32(base_address);
    const uint32_t data_bits=10U;
    uz_assert(weight_address < powf(2,data_bits));
    uz_axi_write_uint32(base_address+axi_weight_addr_Data_uz_mlp_three_layer,weight_address);


}







