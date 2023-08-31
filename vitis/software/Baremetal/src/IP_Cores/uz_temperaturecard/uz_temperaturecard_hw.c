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

#include "uz_temperaturecard_hw.h"

//Basics
void uz_TempCard_IF_hw_Reset(uint32_t base_address){                         // Resets the Interface-IP to write new Channel configs
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0U; 
    Regdata = (uz_axi_read_uint32(base_address + TempCard_IF_Controlreg));
    // clear the Reset-Bit          
    uz_axi_write_uint32(base_address + TempCard_IF_Controlreg, Regdata & ~(0x00000002U));     

    // IP-Core should recognize one-cycle-reset and triggers a new power-up-sequence with reconfigurations of the LTC's

    Regdata = (uz_axi_read_uint32(base_address + TempCard_IF_Controlreg));
    // set the Reset-Bit (since this is an active-low-Reset, the 1 represents the running state)             
    uz_axi_write_uint32(base_address + TempCard_IF_Controlreg, Regdata | 0x00000002U);  
}

void uz_TempCard_IF_hw_Start(uint32_t base_address){                         // Starts the Interface-IP
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0U; 
    Regdata = (uz_axi_read_uint32(base_address + TempCard_IF_Controlreg));
    // set the Reset-Bit
    uz_axi_write_uint32(base_address + TempCard_IF_Controlreg, Regdata | 0x00000001U);     
}

void uz_TempCard_IF_hw_Stop(uint32_t base_address){                          // Stops the Interface-IP
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0U; 
    Regdata = (uz_axi_read_uint32(base_address + TempCard_IF_Controlreg));
    // clear the Reset-Bit
    uz_axi_write_uint32(base_address + TempCard_IF_Controlreg, Regdata & ~(0x00000001U));
}

void uz_TempCard_IF_hw_writeReg(uint32_t base_address,uint32_t data){         // write one Register
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address,data);
}

void uz_TempCard_IF_hw_write_channel_group_A_configdata(uint32_t base_address, uint32_t channel_config[20]) {
        uz_assert_not_zero(base_address);
        for(uint32_t i = 0U; i < CHANNEL_COUNT; i++){
            uz_TempCard_IF_hw_writeReg(base_address + TempCard_IF_Config_A_0 + (i*CHANNEL_ADDRESS_INCREMENT), channel_config[i]);
        }
}

void uz_TempCard_IF_hw_write_channel_group_B_configdata(uint32_t base_address, uint32_t channel_config[20]) {
        uz_assert_not_zero(base_address);
        for(uint32_t i = 0U; i < CHANNEL_COUNT; i++){
        //Select Channel_A
        uz_TempCard_IF_hw_writeReg(base_address + TempCard_IF_Config_B_0 + (i*CHANNEL_ADDRESS_INCREMENT), channel_config[i]);
        }
}

void uz_TempCard_IF_hw_write_channel_group_C_configdata(uint32_t base_address, uint32_t channel_config[20]) {
        uz_assert_not_zero(base_address);
        for(uint32_t i = 0U; i < CHANNEL_COUNT; i++){
        //Select Channel_A
        uz_TempCard_IF_hw_writeReg(base_address + TempCard_IF_Config_C_0 + (i*CHANNEL_ADDRESS_INCREMENT), channel_config[i]);
        }
}

uint32_t uz_TempCard_IF_hw_read_raw_value_channel_group_A(uint32_t base_address, uint32_t channel_number) {
        uz_assert_not_zero(base_address);
        uz_assert(channel_number < CHANNEL_COUNT);
        return(uz_TempCard_IF_hw_readReg(base_address + TempCard_IF_Result_A_0 + (channel_number*CHANNEL_ADDRESS_INCREMENT)));               
}

uint32_t uz_TempCard_IF_hw_read_raw_value_channel_group_B(uint32_t base_address, uint32_t channel_number) {
        uz_assert_not_zero(base_address);
        uz_assert(channel_number < CHANNEL_COUNT);
        return(uz_TempCard_IF_hw_readReg(base_address + TempCard_IF_Result_B_0 + (channel_number*CHANNEL_ADDRESS_INCREMENT)));               
}

uint32_t uz_TempCard_IF_hw_read_raw_value_channel_group_C(uint32_t base_address, uint32_t channel_number) {
        uz_assert_not_zero(base_address);
        uz_assert(channel_number < CHANNEL_COUNT);
        return(uz_TempCard_IF_hw_readReg(base_address + TempCard_IF_Result_C_0 + (channel_number*CHANNEL_ADDRESS_INCREMENT)));               
}


uint32_t uz_TempCard_IF_hw_readReg(uint32_t base_address){                    // read one Register
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address));
}

void uz_TempCard_IF_hw_writeCounterReg(uint32_t base_address,uint32_t data){     // write the Counter Register
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+TempCard_IF_Counterreg,data);
}

uint32_t uz_TempCard_IF_hw_readCounterReg(uint32_t base_address){             // read the Counter Register
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+TempCard_IF_Counterreg));
}

void uz_TempCard_IF_hw_writeGlobalConfigReg(uint32_t base_address,uint32_t data){// write the Global Config Register
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+TempCard_IF_GlobalConfig,data);
}
uint32_t uz_TempCard_IF_hw_readGlobalConfigReg(uint32_t base_address){           // read the Global Config Register
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+TempCard_IF_GlobalConfig));
}
void uz_TempCard_IF_hw_writeMuxConfigReg(uint32_t base_address,uint32_t data){   // write the Mux Config Register
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+TempCard_IF_MuxConfig,data);
}
uint32_t uz_TempCard_IF_hw_readMuxConfigReg(uint32_t base_address){              // read the Mux Config Register
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+TempCard_IF_MuxConfig));
}