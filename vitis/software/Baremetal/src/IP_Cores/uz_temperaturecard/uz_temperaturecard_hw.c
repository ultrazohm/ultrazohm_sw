/******************************************************************************
* Copyright 2022 Robert Zipprich
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
    uint32_t Regdata = 0; 
    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));
    // clear the Reset-Bit          
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata & ~(0x00000002));     

    // IP-Core should recognize one-cycle-reset and triggers a new power-up-sequence with reconfigurations of the LTC's

    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));
    // set the Reset-Bit (since this is an active-low-Reset, the 1 represents the running state)             
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata | 0x00000002);  
}

void uz_TempCard_IF_hw_Start(uint32_t base_address){                         // Starts the Interface-IP
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0; 
    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));
    // set the Reset-Bit
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata | 0x00000001);     
}

void uz_TempCard_IF_hw_Stop(uint32_t base_address){                          // Stops the Interface-IP
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0; 
    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));
    // clear the Reset-Bit
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata & ~(0x00000001));
}

void uz_TempCard_IF_hw_writeReg(uint32_t base_address,int32_t data){         // write one Register
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address,data);
}

int32_t uz_TempCard_IF_hw_readReg(uint32_t base_address){                    // read one Register
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address));
}

void uz_TempCard_IF_hw_writeCounterReg(uint32_t base_address,int32_t data){     // write the Counter Register
    uz_assert_not_zero(base_address+TempCard_IF_Counterreg);
    uz_axi_write_int32(base_address+TempCard_IF_Counterreg,data);
}

int32_t uz_TempCard_IF_hw_readCounterReg(uint32_t base_address){             // read the Counter Register
    uz_assert_not_zero(base_address+TempCard_IF_Counterreg);
    return (uz_axi_read_int32(base_address+TempCard_IF_Counterreg));
}

//Register-specified
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_0(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_0);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_0));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_1(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_1);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_1));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_2(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_2);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_2));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_3(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_3);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_3));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_4(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_4);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_4));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_5(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_5);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_5));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_6(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_6);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_6));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_7(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_7);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_7));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_8(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_8);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_8));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_9(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_9);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_9));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_10(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_10);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_10));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_11(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_11);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_11));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_12(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_12);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_12));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_13(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_13);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_13));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_14(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_14);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_14));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_15(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_15);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_15));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_16(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_16);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_16));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_17(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_17);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_17));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_18(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_18);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_18));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_19(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_19);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_19));
}

void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_0(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_0);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_0,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_0(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_0);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_0));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_1(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_1);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_1,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_1(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_1);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_1));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_2(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_2);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_2,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_2(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_2);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_2));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_3(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_3);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_3,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_3(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_3);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_3));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_4(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_4);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_4,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_4(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_4);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_4));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_5(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_5);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_5,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_5(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_5);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_5));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_6(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_6);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_6,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_6(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_6);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_6));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_7(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_7);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_7,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_7(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_7);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_7));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_8(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_8);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_8,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_8(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_8);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_8));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_9(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_9);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_9,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_9(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_9);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_9));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_10(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_10);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_10,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_10(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_10);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_10));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_11(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_11);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_11,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_11(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_11);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_11));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_12(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_12);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_12,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_12(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_12);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_12));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_13(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_13);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_13,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_13(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_13);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_13));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_14(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_14);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_14,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_14(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_14);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_14));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_15(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_15);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_15,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_15(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_15);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_15));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_16(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_16);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_16,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_16(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_16);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_16));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_17(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_17);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_17,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_17(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_17);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_17));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_18(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_18);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_18,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_18(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_18);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_18));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_19(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_19);
    uz_axi_write_int32(base_address + TempCard_IF_Result_A_19,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_19(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_A_19);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_A_19));
}


void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_0(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_0);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_0));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_1(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_1);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_1));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_2(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_2);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_2));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_3(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_3);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_3));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_4(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_4);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_4));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_5(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_5);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_5));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_6(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_6);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_6));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_7(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_7);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_7));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_8(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_8);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_8));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_9(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_9);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_9));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_10(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_10);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_10));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_11(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_11);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_11));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_12(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_12);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_12));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_13(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_13);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_13));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_14(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_14);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_14));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_15(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_15);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_15));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_16(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_16);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_16));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_17(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_17);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_17));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_18(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_18);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_18));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_19(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_19);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_19));
}

void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_0(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_0);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_0,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_0(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_0);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_0));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_1(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_1);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_1,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_1(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_1);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_1));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_2(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_2);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_2,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_2(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_2);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_2));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_3(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_3);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_3,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_3(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_3);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_3));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_4(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_4);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_4,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_4(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_4);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_4));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_5(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_5);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_5,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_5(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_5);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_5));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_6(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_6);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_6,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_6(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_6);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_6));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_7(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_7);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_7,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_7(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_7);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_7));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_8(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_8);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_8,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_8(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_8);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_8));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_9(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_9);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_9,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_9(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_9);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_9));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_10(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_10);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_10,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_10(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_10);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_10));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_11(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_11);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_11,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_11(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_11);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_11));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_12(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_12);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_12,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_12(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_12);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_12));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_13(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_13);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_13,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_13(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_13);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_13));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_14(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_14);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_14,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_14(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_14);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_14));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_15(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_15);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_15,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_15(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_15);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_15));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_16(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_16);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_16,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_16(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_16);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_16));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_17(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_17);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_17,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_17(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_17);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_17));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_18(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_18);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_18,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_18(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_18);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_18));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_19(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_19);
    uz_axi_write_int32(base_address + TempCard_IF_Result_B_19,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_19(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_B_19);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_B_19));
}


void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_0(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_0);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_0));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_1(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_1);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_1));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_2(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_2);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_2));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_3(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_3);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_3));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_4(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_4);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_4));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_5(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_5);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_5));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_6(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_6);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_6));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_7(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_7);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_7));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_8(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_8);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_8));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_9(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_9);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_9));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_10(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_10);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_10));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_11(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_11);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_11));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_12(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_12);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_12));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_13(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_13);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_13));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_14(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_14);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_14));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_15(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_15);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_15));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_16(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_16);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_16));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_17(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_17);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_17));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_18(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_18);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_18));
}
void uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_19(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_19);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_19));
}

void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_0(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_0);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_0,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_0(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_0);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_0));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_1(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_1 + TempCard_IF_Result_C_1);
    uz_axi_write_int32(base_address,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_1(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_1);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_1));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_2(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_2);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_2,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_2(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_2);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_2));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_3(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_3);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_3,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_3(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_3);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_3));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_4(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_4);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_4,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_4(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_4);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_4));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_5(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_5);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_5,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_5(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_5);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_5));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_6(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_6);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_6,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_6(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_6);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_6));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_7(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_7);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_7,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_7(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_7);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_7));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_8(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_8);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_8,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_8(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_8);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_8));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_9(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_9);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_9,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_9(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_9);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_9));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_10(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_10);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_10,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_10(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_10);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_10));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_11(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_11);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_11,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_11(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_11);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_11));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_12(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_12);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_12,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_12(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_12);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_12));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_13(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_13);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_13,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_13(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_13);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_13));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_14(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_14);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_14,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_14(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_14);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_14));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_15(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_15);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_15,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_15(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_15);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_15));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_16(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_16);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_16,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_16(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_16);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_16));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_17(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_17);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_17,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_17(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_17);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_17));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_18(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_18);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_18,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_18(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_18);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_18));
}
void uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_19(uint32_t base_address,int32_t data){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_19);
    uz_axi_write_int32(base_address + TempCard_IF_Result_C_19,data);
}
int32_t uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_19(uint32_t base_address){
    uz_assert_not_zero(base_address + TempCard_IF_Result_C_19);
    return (uz_axi_read_int32(base_address + TempCard_IF_Result_C_19));
}
