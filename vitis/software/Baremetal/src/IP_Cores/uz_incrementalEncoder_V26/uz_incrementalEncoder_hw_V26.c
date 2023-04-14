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

#include "uz_incrementalEncoder_hw_V26.h"

#include "IncreEncoder_V26_ip_addr.h"

int frac_omega_V25 = 11;
int frac_theta_el_V25 = 20;


void uz_incrementalEncoder_hw_reset_ip_core_V26(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+IPCore_Enable_Incremental_Encoder_v26,false);
    uz_axi_write_bool(base_address+IPCore_Reset_Incremental_Encoder_v26, false);
    uz_axi_write_bool(base_address+IPCore_Reset_Incremental_Encoder_v26, true);
    uz_axi_write_bool(base_address+IPCore_Reset_Incremental_Encoder_v26, false);
    uz_axi_write_bool(base_address+IPCore_Enable_Incremental_Encoder_v26,true);
}

void uz_incrementalEncoder_hw_set_Position_Offset_V26(uint32_t base_address, uint32_t increments_offset_position){
	uz_assert_not_zero_uint32(base_address);
	uz_assert(increments_offset_position < UINT16_MAX); // Data type in IP-Core is uint16_t, thus increments_per_turn has to be smaller than that
	uz_axi_write_uint32(base_address+Position_offset_AXI4_Data_Incremental_Encoder_v26, increments_offset_position);	// direct Count-Value
}


void uz_incrementalEncoder_hw_set_timer_fpga_ms_V26(uint32_t base_address, float timer_ms){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(timer_ms > 0.0f);
    uz_assert(timer_ms < 1.0f); // data type of pi2inc in ip-core is ufix32_en32, thus maximum is 0.9999...
    uz_axi_write_uint32(base_address+Timer_FPGA_ms_AXI4_Data_Incremental_Encoder_v26,uz_convert_float_to_unsigned_fixed(timer_ms,32) ); // Data type is ufix24_En24
}


void uz_incrementalEncoder_hw_set_pi2_inc_V26(uint32_t base_address, float pi2_inc){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(pi2_inc > 0.0f);
    uz_assert(pi2_inc < 1.0f); // data type of pi2inc in ip-core is ufix24_en24, thus maximum is 0.9999...
    uz_axi_write_uint32(base_address+PI2_Inc_AXI4_Data_Incremental_Encoder_v26,uz_convert_float_to_unsigned_fixed(pi2_inc,24));
}


void uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_V26(uint32_t base_address, uint32_t increments_per_turn){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(increments_per_turn < UINT16_MAX); // Data type in IP-Core is uint16_t, thus increments_per_turn has to be smaller than that
    uz_axi_write_uint32(base_address+IncPerTurn_mech_AXI4_Data_Incremental_Encoder_v26,increments_per_turn);
}


void uz_incrementalEncoder_hw_set_theta_el_Offset_V26(uint32_t base_address, uint32_t increments_offset_theta_el){
	uz_assert_not_zero_uint32(base_address);
	uz_assert(increments_offset_theta_el < UINT16_MAX); // Data type in IP-Core is uint16_t, thus increments_per_turn has to be smaller than that
	uz_axi_write_uint32(base_address+theta_el_offset_AXI4_Data_Incremental_Encoder_v26, increments_offset_theta_el);	// direct Count-Value
}


void uz_incrementalEncoder_hw_set_increments_per_turn_electric_V26(uint32_t base_address, uint32_t increments_per_turn){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(increments_per_turn < UINT16_MAX); // Data type in IP-Core is uint16_t, thus increments_per_turn has to be smaller than that
    uz_axi_write_uint32(base_address+IncPerTurn_elek_AXI4_Data_Incremental_Encoder_v26,increments_per_turn);
}

void uz_incrementalEncoder_hw_set_omegaPerOverSample_V26(uint32_t base_address,float omega_per_over_sampl){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(omega_per_over_sampl < 4095.0f);
    uz_assert(omega_per_over_sampl > -4095.0f); // make sure omega_per_oversampl fits data type sfix_24_en11
    uz_axi_write_int32(base_address+OmegaPerOverSampl_AXI4_Data_Incremental_Encoder_v26,uz_convert_float_to_sfixed(omega_per_over_sampl,11));
}


void uz_incrementalEncoder_hw_set_speed_timeout_value_V26(uint32_t base_address,uint32_t speed_timeout){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(speed_timeout < UINT32_MAX); // Data type in IP-Core is uint32_t
    uz_axi_write_uint32(base_address+timeout_value_AXI4_Data_Incremental_Encoder_v26, speed_timeout);
}

void uz_incrementalEncoder_hw_set_cw_ccw_direction_V26(uint32_t base_address,uint32_t cw_ccw_direction){
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address+CW_CCW_Switch_AXI4_Data_Incremental_Encoder_v26, cw_ccw_direction);	// set CW- CCW- counting with bool-value
}

void uz_incrementalEncoder_hw_set_d_axis_hit_Offset_V26(uint32_t base_address,uint32_t d_axis_hit_Offset_Value){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+d_axis_Hit_Compare_AXI_Data_Incremental_Encoder_v26, d_axis_hit_Offset_Value); // set Counter-Compare_Value for d-Axis-Hit_Offset
}

//------------------------------------------------------------------------------------------------------------------------

float uz_incrementalEncoder_hw_get_omega_V26(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address+omega_AXI4_Data_Incremental_Encoder_v26);
    return uz_convert_sfixed_to_float(tmp,frac_omega_V25);
}

float uz_incrementalEncoder_hw_get_direction_V26(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address+direction_AXI4_Data_Incremental_Encoder_v26);
    return uz_convert_sfixed_to_float(tmp,frac_omega_V25);
}

float uz_incrementalEncoder_hw_get_theta_electric_V26(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp= uz_axi_read_int32(base_address+theta_el_AXI4_Data_Incremental_Encoder_v26);
    return uz_convert_sfixed_to_float(tmp,frac_theta_el_V25);
}

uint32_t uz_incrementalEncoder_hw_get_position_V26(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+position_AXI4_Data_Incremental_Encoder_v26);
}

uint32_t uz_incrementalEncoder_hw_get_counterPerPeriod_V26(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+countPerPeriod_AXI4_Data_Incremental_Encoder_v26);
}



float uz_incrementalEncoder_hw_get_omega_MA_N4_V26(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	int32_t tmp=uz_axi_read_int32(base_address+omega_MA_N4_AXI_Data_Incremental_Encoder_v26);
	return uz_convert_sfixed_to_float(tmp,frac_omega_V25);
}

uint32_t uz_incrementalEncoder_hw_get_position_wOffset_V26(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address+position_wOffset_AXI4_Data_Incremental_Encoder_v26);
}

uint32_t uz_incrementalEncoder_hw_get_Index_found_V26(uint32_t base_address){
	uz_assert_not_zero_uint32(base_address);
	return uz_axi_read_uint32(base_address+Index_found_AXI4_Data_Incremental_Encoder_v26);
}
