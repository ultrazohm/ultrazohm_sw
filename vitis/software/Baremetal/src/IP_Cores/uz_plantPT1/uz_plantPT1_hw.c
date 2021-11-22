/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Tobias Schindler
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

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

void uz_plantPT1_hw_write_time_constant(uint32_t base_address, float reciprocal_time_constant){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+reciprocal_time_constant_Data_uz_plantModel_pt1,reciprocal_time_constant);
}

void uz_plantPT1_hw_write_gain(uint32_t base_address,float gain){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+gain_Data_uz_plantModel_pt1,gain);
}

void uz_plantPT1_hw_write_input(uint32_t base_address, float input){
    uz_assert_not_zero(base_address);
    uz_axi_write_float(base_address+input_Data_uz_plantModel_pt1,input);
}