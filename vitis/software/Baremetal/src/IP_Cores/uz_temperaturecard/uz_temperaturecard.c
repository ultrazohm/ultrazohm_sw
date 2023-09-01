/******************************************************************************
* Copyright 2023 Robert Zipprich, Michael Hoerner
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

#include "../../uz/uz_global_configuration.h"
#if UZ_TEMPERATURE_CARD_MAX_INSTANCES > 0U
#include "uz_temperaturecard.h" 

struct uz_temperaturecard_t {
    bool                                is_ready;
    uint32_t                            Stepcounter;
    struct uz_temperaturecard_config_t  config;
    uz_temperaturecard_OneGroup         Channelgroup_A;
    uz_temperaturecard_OneGroup         Channelgroup_B;
    uz_temperaturecard_OneGroup         Channelgroup_C;
};

static uint32_t instance_counter = 0U;
static uz_temperaturecard_t instances[UZ_TEMPERATURE_CARD_MAX_INSTANCES] = {0U};

static uz_temperaturecard_t* uz_temperaturecard_allocation(void);

static uz_temperaturecard_t* uz_temperaturecard_allocation(void) {
    uz_assert(instance_counter < UZ_TEMPERATURE_CARD_MAX_INSTANCES);
    uz_temperaturecard_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_temperaturecard_t* uz_temperaturecard_init(struct uz_temperaturecard_config_t config) {
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.Sample_Freq_Hz);
    uz_temperaturecard_t* self  = uz_temperaturecard_allocation();
    // Store settings
    self->config = config;
    self->Stepcounter = 0U;
    for(uint32_t i = 0U; i < CHANNEL_COUNT; i++) {
    	self->Channelgroup_A.Configdata[i] = self->config.Configdata_A[i];
    	self->Channelgroup_B.Configdata[i] = self->config.Configdata_B[i];
    	self->Channelgroup_C.Configdata[i] = self->config.Configdata_C[i];
    }
    uz_TempCard_IF_set_config(self);
    return (self);
}

void uz_TempCard_IF_set_config(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Write Config-Regs
    uint32_t Configbuffer = 0U;
    Configbuffer = (self->config.Config_Global_C << 16U) | (self->config.Config_Global_B << 8U) | (self->config.Config_Global_A << 0U);
    uz_TempCard_IF_hw_writeGlobalConfigReg(self->config.base_address, Configbuffer);
    Configbuffer = 0U;
    Configbuffer = (self->config.Config_Mux_C << 16U) | (self->config.Config_Mux_B << 8U) | (self->config.Config_Mux_A << 0U);
    uz_TempCard_IF_hw_writeMuxConfigReg(self->config.base_address, Configbuffer);

    uint32_t sample_counter_end_value = (uint32_t)((1.0f/((float)self->config.Sample_Freq_Hz))/(1.0f/(float)self->config.ip_clk_frequency_Hz));

    //Write Channelsettings
    uz_TempCard_IF_hw_writeCounterReg(self->config.base_address, sample_counter_end_value);   
    uz_TempCard_IF_write_channel_group_configdata(self);
}

void uz_TempCard_IF_write_channel_group_configdata(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_zero(self->config.base_address);
    uz_TempCard_IF_hw_write_channel_group_A_configdata(self->config.base_address, self->Channelgroup_A.Configdata);
    uz_TempCard_IF_hw_write_channel_group_B_configdata(self->config.base_address, self->Channelgroup_B.Configdata);
    uz_TempCard_IF_hw_write_channel_group_C_configdata(self->config.base_address, self->Channelgroup_C.Configdata);
}

void uz_TempCard_IF_extract_fault_data_for_channel_in_group_A(uz_temperaturecard_t* self, uint32_t channel) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    self->Channelgroup_A.Channel_Fault_Data[channel] = (self->Channelgroup_A.temperature_raw[channel] & 0xFF000000U) >> 24U;
}

void uz_TempCard_IF_extract_fault_data_for_channel_in_group_B(uz_temperaturecard_t* self, uint32_t channel) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    self->Channelgroup_B.Channel_Fault_Data[channel] = (self->Channelgroup_B.temperature_raw[channel] & 0xFF000000U) >> 24U;
}

void uz_TempCard_IF_extract_fault_data_for_channel_in_group_C(uz_temperaturecard_t* self, uint32_t channel) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    self->Channelgroup_C.Channel_Fault_Data[channel] = (self->Channelgroup_C.temperature_raw[channel] & 0xFF000000U) >> 24U;
}

void uz_TempCard_IF_calculate_temperature_degrees_celsius_if_valid_group_A(uz_temperaturecard_t* self, uint32_t channel) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    if (self->Channelgroup_A.Channel_Fault_Data[channel] == 1U) { //1U means no fault, temperature is valid
        self->Channelgroup_A.temperature[channel] = (float)(self->Channelgroup_A.temperature_raw[channel] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;
    } else {
        self->Channelgroup_A.temperature[channel] = -333.33f;
    }
}

void uz_TempCard_IF_calculate_temperature_degrees_celsius_if_valid_group_B(uz_temperaturecard_t* self, uint32_t channel) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    if (self->Channelgroup_B.Channel_Fault_Data[channel] == 1U) { //1U means no fault, temperature is valid
        self->Channelgroup_B.temperature[channel] = (float)(self->Channelgroup_B.temperature_raw[channel] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;
    } else {
        self->Channelgroup_B.temperature[channel] = -333.33f;
    }
}

void uz_TempCard_IF_calculate_temperature_degrees_celsius_if_valid_group_C(uz_temperaturecard_t* self, uint32_t channel) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    if (self->Channelgroup_C.Channel_Fault_Data[channel] == 1U) { //1U means no fault, temperature is valid
        self->Channelgroup_C.temperature[channel] = (float)(self->Channelgroup_C.temperature_raw[channel] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;
    } else {
        self->Channelgroup_C.temperature[channel] = -333.33f;
    }
}

void uz_TempCard_IF_Reset(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_TempCard_IF_hw_Reset(self->config.base_address);
}

void uz_TempCard_IF_Start(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_TempCard_IF_hw_Start(self->config.base_address);
}

void uz_TempCard_IF_Stop(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_TempCard_IF_hw_Stop(self->config.base_address);
}

void uz_TempCard_IF_MeasureTemps_cyclic(uz_temperaturecard_t* self) {
	uz_assert_not_NULL(self);
    if(self->Stepcounter < CHANNEL_COUNT){
        // Channelgroup_A
    	self->Channelgroup_A.temperature_raw[self->Stepcounter]   = uz_TempCard_IF_hw_read_raw_value_channel_group_A(self->config.base_address, self->Stepcounter);
    	uz_TempCard_IF_extract_fault_data_for_channel_in_group_A(self, self->Stepcounter);
        uz_TempCard_IF_calculate_temperature_degrees_celsius_if_valid_group_A(self, self->Stepcounter);
    	self->Stepcounter += 1U;
    }else if(self->Stepcounter >= CHANNEL_COUNT && self->Stepcounter < (CHANNEL_COUNT*2U)){
        // Channelgroup_B
    	self->Channelgroup_B.temperature_raw[self->Stepcounter-CHANNEL_COUNT]  = uz_TempCard_IF_hw_read_raw_value_channel_group_B(self->config.base_address, self->Stepcounter-CHANNEL_COUNT);
        uz_TempCard_IF_extract_fault_data_for_channel_in_group_B(self, self->Stepcounter-CHANNEL_COUNT);
        uz_TempCard_IF_calculate_temperature_degrees_celsius_if_valid_group_B(self, self->Stepcounter-CHANNEL_COUNT);
    	self->Stepcounter += 1U;
    }else if(self->Stepcounter >= (CHANNEL_COUNT*2U) && self->Stepcounter < (CHANNEL_COUNT*3U)){
        // Channelgroup_C
    	self->Channelgroup_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2U]  = uz_TempCard_IF_hw_read_raw_value_channel_group_C(self->config.base_address, self->Stepcounter-CHANNEL_COUNT*2U);
    	uz_TempCard_IF_extract_fault_data_for_channel_in_group_C(self, self->Stepcounter-CHANNEL_COUNT*2U);
        uz_TempCard_IF_calculate_temperature_degrees_celsius_if_valid_group_B(self, self->Stepcounter-CHANNEL_COUNT*2U);
    	self->Stepcounter += 1U;
    }else{
    	self->Stepcounter = 0U;
    }
}

uz_temperaturecard_OneGroup uz_TempCard_IF_get_channel_group(uz_temperaturecard_t* self, const char channelgroup){
    uz_assert_not_NULL(self);
    uz_temperaturecard_OneGroup out = {0U};
    switch (channelgroup){
        case 'a':
        case 'A':{
            out = self->Channelgroup_A;
            break;}
        case 'b':
        case 'B':{
            out = self->Channelgroup_B;
            break;}
        case 'c':
        case 'C':{
            out = self->Channelgroup_C;
            break;}
        default:{
            uz_assert(0);
            break;}
    }
    return out;
}

float uz_TempCard_IF_get_channel(uz_temperaturecard_t* self, const char channelgroup, uint32_t channel){
	uz_assert(channel < CHANNEL_COUNT);

	uz_temperaturecard_OneGroup group_buffer = {0U};

    group_buffer = uz_TempCard_IF_get_channel_group(self, channelgroup);
    return(group_buffer.temperature[channel]);
}

float uz_TempCard_IF_average_temperature_for_valid(uz_temperaturecard_OneGroup channeldata, const uint32_t lower, const uint32_t upper){
    uz_assert(lower <= upper);
    uz_assert(upper < 20U);
    float sum = 0.0f;
    float valid = 0.0f;
    for(uint32_t i=lower; i<=upper; i++){
        sum += channeldata.temperature[i]*(channeldata.Channel_Fault_Data[i]==1U);
        valid += (channeldata.Channel_Fault_Data[i]==1U);
    }
    if(valid != 0.0f){
        return (sum/valid);
    }else{
        return (-333.3f);
    }
}

#endif
