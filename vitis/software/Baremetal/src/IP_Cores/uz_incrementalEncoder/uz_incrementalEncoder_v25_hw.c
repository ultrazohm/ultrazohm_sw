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

#include "uz_incrementalEncoder_v25_hw.h"
#include "IncEnc_V25_addr.h"

int frac_omega = 11;

void uz_incrementalEncoder_hw_set_speed_timeout(uint32_t base_address,uint32_t speed_timeout){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(speed_timeout < UINT32_MAX); // Data type in IP-Core is uint32_t
    uz_axi_write_uint32(base_address+timeout_value_AXI4_Data_IncEnc, speed_timeout);
}

void uz_incrementalEncoder_hw_reset_ip_core(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+IPCore_Enable_IncEnc,false);
    uz_axi_write_bool(base_address+IPCore_Reset_IncEnc, false);
    uz_axi_write_bool(base_address+IPCore_Reset_IncEnc, true);
    uz_axi_write_bool(base_address+IPCore_Reset_IncEnc, false);
    uz_axi_write_bool(base_address+IPCore_Enable_IncEnc,true);
}

float uz_incrementalEncoder_hw_get_omega_oversampled_N4(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address+omega_MA_N4_AXI_Data_IncEnc);
    return uz_convert_sfixed_to_float(tmp,frac_omega);
}
float uz_incrementalEncoder_hw_get_omega_oversampled_N8(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address+omega_MA_N8_AXI_Data_IncEnc);
    return uz_convert_sfixed_to_float(tmp,frac_omega);
}

float uz_incrementalEncoder_hw_get_A(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address + omegaA1_Data_IncEnc);
    return uz_convert_sfixed_to_float(tmp,frac_omega);
}

float uz_incrementalEncoder_hw_get_NOTA(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address + omegaNOTA1_Data_IncEnc);
    return uz_convert_sfixed_to_float(tmp,frac_omega);
}
float uz_incrementalEncoder_hw_get_B(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address + omegaB1_Data_IncEnc);
    return uz_convert_sfixed_to_float(tmp,frac_omega);
}
float uz_incrementalEncoder_hw_get_NOTB(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address + omegaNOTB1_Data_IncEnc);
    return uz_convert_sfixed_to_float(tmp,frac_omega);
}
