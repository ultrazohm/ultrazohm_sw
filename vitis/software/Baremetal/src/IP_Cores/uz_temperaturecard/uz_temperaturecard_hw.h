/******************************************************************************
* Copyright 2021 Robert Zipprich
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
#ifndef UZ_TEMPERATURECARD_HW
#define UZ_TEMPERATURECARD_HW

#include <stdint.h>
#include "uz_temperaturecard_hwAddresses.h"
#include "../../uz/uz_AXI.h"

//Basics
void        uz_TempCard_IF_hw_Reset(uint32_t base_address);                         // Resets the Interface-IP to write new Channel configs
void        uz_TempCard_IF_hw_Start(uint32_t base_address);                         // Starts the Interface-IP
void        uz_TempCard_IF_hw_Stop(uint32_t base_address);                          // Stops the Interface-IP
int32_t     uz_TempCard_IF_hw_readErrorReg(uint32_t base_address);                  // reads the Error_Register
int32_t     uz_TempCard_IF_hw_readReadbackReg(uint32_t base_address);               // reads the IP-Core Readback
void        uz_TempCard_IF_hw_writeReg(uint32_t base_address,int32_t B);            // write one Register
int32_t     uz_TempCard_IF_hw_readReg(uint32_t base_address);                       // read one Register
void        uz_TempCard_IF_hw_writeCounterReg(uint32_t base_address,int32_t B);     // write the Counter Register
int32_t     uz_TempCard_IF_hw_readCounterReg(uint32_t base_address);                // read the Counter Register

//Register-specified
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_0(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_1(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_2(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_3(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_4(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_5(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_6(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_7(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_8(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_9(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_10(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_11(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_12(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_13(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_14(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_15(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_16(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_17(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_18(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_A_19(uint32_t base_address,int32_t data);

void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_0(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_0(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_1(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_1(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_2(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_2(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_3(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_3(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_4(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_4(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_5(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_5(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_6(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_6(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_7(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_7(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_8(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_8(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_9(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_9(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_10(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_10(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_11(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_11(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_12(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_12(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_13(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_13(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_14(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_14(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_15(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_15(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_16(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_16(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_17(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_17(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_18(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_18(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_A_19(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_A_19(uint32_t base_address);


int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_0(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_1(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_2(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_3(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_4(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_5(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_6(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_7(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_8(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_9(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_10(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_11(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_12(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_13(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_14(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_15(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_16(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_17(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_18(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_B_19(uint32_t base_address,int32_t data);

void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_0(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_0(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_1(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_1(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_2(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_2(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_3(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_3(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_4(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_4(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_5(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_5(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_6(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_6(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_7(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_7(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_8(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_8(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_9(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_9(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_10(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_10(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_11(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_11(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_12(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_12(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_13(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_13(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_14(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_14(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_15(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_15(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_16(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_16(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_17(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_17(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_18(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_18(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_B_19(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_B_19(uint32_t base_address);


int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_0(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_1(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_2(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_3(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_4(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_5(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_6(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_7(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_8(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_9(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_10(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_11(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_12(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_13(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_14(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_15(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_16(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_17(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_18(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Result_C_19(uint32_t base_address,int32_t data);

void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_0(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_0(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_1(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_1(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_2(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_2(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_3(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_3(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_4(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_4(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_5(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_5(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_6(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_6(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_7(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_7(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_8(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_8(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_9(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_9(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_10(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_10(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_11(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_11(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_12(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_12(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_13(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_13(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_14(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_14(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_15(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_15(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_16(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_16(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_17(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_17(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_18(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_18(uint32_t base_address);
void        uz_TempCard_IF_hw_writeReg_TempCard_IF_Config_C_19(uint32_t base_address,int32_t data);
int32_t     uz_TempCard_IF_hw_readReg_TempCard_IF_Config_C_19(uint32_t base_address);

#endif // UZ_TEMPERATURECARD_HW
