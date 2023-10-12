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
#ifndef UZ_TEMPERATURECARD_HW
#define UZ_TEMPERATURECARD_HW

#include <stdint.h>
#include "uz_temperaturecard_hwAddresses.h"
#include "../../uz/uz_AXI.h"

/** Temperature Channel for one LTC2983 */
#define CHANNEL_COUNT               20U     
#define CHANNEL_ADDRESS_INCREMENT   0x4U

//Basics
void        uz_TempCard_IF_hw_Reset(uint32_t base_address);                         	// Resets the Interface-IP to write new Channel configs
void        uz_TempCard_IF_hw_Start(uint32_t base_address);                         	// Starts the Interface-IP
void        uz_TempCard_IF_hw_Stop(uint32_t base_address);                          	// Stops the Interface-IP
uint32_t    uz_TempCard_IF_hw_readErrorReg(uint32_t base_address);                  	// reads the Error_Register
uint32_t    uz_TempCard_IF_hw_readReadbackReg(uint32_t base_address);               	// reads the IP-Core Readback
void        uz_TempCard_IF_hw_writeReg(uint32_t base_address,uint32_t data);            // write one Register
uint32_t    uz_TempCard_IF_hw_readReg(uint32_t base_address);                       	// read one Register
void        uz_TempCard_IF_hw_writeCounterReg(uint32_t base_address,uint32_t data);     // write the Counter Register
uint32_t    uz_TempCard_IF_hw_readCounterReg(uint32_t base_address);                	// read the Counter Register
void        uz_TempCard_IF_hw_writeGlobalConfigReg(uint32_t base_address,uint32_t data);// write the Global Config Register
uint32_t    uz_TempCard_IF_hw_readGlobalConfigReg(uint32_t base_address);           	// read the Global Config Register
void        uz_TempCard_IF_hw_writeMuxConfigReg(uint32_t base_address,uint32_t data);  	// write the Mux Config Register
uint32_t    uz_TempCard_IF_hw_readMuxConfigReg(uint32_t base_address);              	// read the Mux Config Register

void uz_TempCard_IF_hw_write_channel_group_A_configdata(uint32_t base_address, uint32_t channel_config[20]);
void uz_TempCard_IF_hw_write_channel_group_B_configdata(uint32_t base_address, uint32_t channel_config[20]);
void uz_TempCard_IF_hw_write_channel_group_C_configdata(uint32_t base_address, uint32_t channel_config[20]);

uint32_t uz_TempCard_IF_hw_read_raw_value_channel_group_A(uint32_t base_address, uint32_t channel_number);
uint32_t uz_TempCard_IF_hw_read_raw_value_channel_group_B(uint32_t base_address, uint32_t channel_number);
uint32_t uz_TempCard_IF_hw_read_raw_value_channel_group_C(uint32_t base_address, uint32_t channel_number);


#endif // UZ_TEMPERATURECARD_HW
