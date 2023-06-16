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
#ifndef UZ_TEMPERATURECARD_HWADDRESSES_H_
#define UZ_TEMPERATURECARD_HWADDRESSES_H_

// Control-register
#define  TempCard_IF_Controlreg         0x000  	// controlregister for the temperature card interface IP | Bit 0 enable | Bit 1 reset (must be set to 1)
#define  TempCard_IF_Counterreg         0x004  	// counterregister for the automatic measurement trigger
//#define  empty_reg          			0x008  	//
//#define  empty_reg          			0x00C  	//
//#define  empty_reg          			0x010  	//
//#define  empty_reg          			0x014  	//
#define  TempCard_IF_internal_error     0x018  	// Register to read internal IP-Core errors
#define  TempCard_IF_Design_RB     		0x01C  	// Readback from the IP-Core to check if the core exists. Must be AFFEAFFE!!!

//LTC2983 Channel A - Temperature results
#define  TempCard_IF_Result_A_0   		0x020  	// Measurement Result Channel A 0
#define  TempCard_IF_Result_A_1   		0x024  	// Measurement Result Channel A 1
#define  TempCard_IF_Result_A_2   		0x028  	// Measurement Result Channel A 2
#define  TempCard_IF_Result_A_3   		0x02C  	// Measurement Result Channel A 3
#define  TempCard_IF_Result_A_4   		0x030  	// Measurement Result Channel A 4
#define  TempCard_IF_Result_A_5   		0x034  	// Measurement Result Channel A 5
#define  TempCard_IF_Result_A_6   		0x038  	// Measurement Result Channel A 6
#define  TempCard_IF_Result_A_7   		0x03C  	// Measurement Result Channel A 7
#define  TempCard_IF_Result_A_8   		0x040  	// Measurement Result Channel A 8
#define  TempCard_IF_Result_A_9   		0x044  	// Measurement Result Channel A 9
#define  TempCard_IF_Result_A_10   		0x048  	// Measurement Result Channel A 10
#define  TempCard_IF_Result_A_11  		0x04C  	// Measurement Result Channel A 11
#define  TempCard_IF_Result_A_12  		0x050  	// Measurement Result Channel A 12
#define  TempCard_IF_Result_A_13  		0x054  	// Measurement Result Channel A 13
#define  TempCard_IF_Result_A_14  		0x058  	// Measurement Result Channel A 14
#define  TempCard_IF_Result_A_15  		0x05C  	// Measurement Result Channel A 15
#define  TempCard_IF_Result_A_16  		0x060  	// Measurement Result Channel A 16
#define  TempCard_IF_Result_A_17  		0x064  	// Measurement Result Channel A 17
#define  TempCard_IF_Result_A_18  		0x068  	// Measurement Result Channel A 18
#define  TempCard_IF_Result_A_19   		0x06C  	// Measurement Result Channel A 19

#define  TempCard_IF_Config_A_0   		0x070  	// Measurement Config Channel A 0
#define  TempCard_IF_Config_A_1   		0x074  	// Measurement Config Channel A 1
#define  TempCard_IF_Config_A_2   		0x078  	// Measurement Config Channel A 2
#define  TempCard_IF_Config_A_3   		0x07C  	// Measurement Config Channel A 3
#define  TempCard_IF_Config_A_4   		0x080  	// Measurement Config Channel A 4
#define  TempCard_IF_Config_A_5   		0x084  	// Measurement Config Channel A 5
#define  TempCard_IF_Config_A_6   		0x088  	// Measurement Config Channel A 6
#define  TempCard_IF_Config_A_7   		0x08C  	// Measurement Config Channel A 7
#define  TempCard_IF_Config_A_8   		0x090  	// Measurement Config Channel A 8
#define  TempCard_IF_Config_A_9   		0x094  	// Measurement Config Channel A 9
#define  TempCard_IF_Config_A_10   		0x098  	// Measurement Config Channel A 10
#define  TempCard_IF_Config_A_11  		0x09C  	// Measurement Config Channel A 11
#define  TempCard_IF_Config_A_12  		0x0A0  	// Measurement Config Channel A 12
#define  TempCard_IF_Config_A_13  		0x0A4  	// Measurement Config Channel A 13
#define  TempCard_IF_Config_A_14  		0x0A8  	// Measurement Config Channel A 14
#define  TempCard_IF_Config_A_15  		0x0AC  	// Measurement Config Channel A 15
#define  TempCard_IF_Config_A_16  		0x0B0  	// Measurement Config Channel A 16
#define  TempCard_IF_Config_A_17  		0x0B4  	// Measurement Config Channel A 17
#define  TempCard_IF_Config_A_18  		0x0B8  	// Measurement Config Channel A 18
#define  TempCard_IF_Config_A_19   		0x0BC  	// Measurement Config Channel A 19

//LTC2983 Channel B - Temperature results
#define  TempCard_IF_Result_B_0   		0x0C0  	// Measurement Result Channel B 0
#define  TempCard_IF_Result_B_1   		0x0C4  	// Measurement Result Channel B 1
#define  TempCard_IF_Result_B_2   		0x0C8  	// Measurement Result Channel B 2
#define  TempCard_IF_Result_B_3   		0x0CC  	// Measurement Result Channel B 3
#define  TempCard_IF_Result_B_4   		0x0D0  	// Measurement Result Channel B 4
#define  TempCard_IF_Result_B_5   		0x0D4  	// Measurement Result Channel B 5
#define  TempCard_IF_Result_B_6   		0x0D8  	// Measurement Result Channel B 6
#define  TempCard_IF_Result_B_7   		0x0DC  	// Measurement Result Channel B 7
#define  TempCard_IF_Result_B_8   		0x0E0  	// Measurement Result Channel B 8
#define  TempCard_IF_Result_B_9   		0x0E4  	// Measurement Result Channel B 9
#define  TempCard_IF_Result_B_10   		0x0E8  	// Measurement Result Channel B 10
#define  TempCard_IF_Result_B_11  		0x0EC  	// Measurement Result Channel B 11
#define  TempCard_IF_Result_B_12  		0x0F0  	// Measurement Result Channel B 12
#define  TempCard_IF_Result_B_13  		0x0F4  	// Measurement Result Channel B 13
#define  TempCard_IF_Result_B_14  		0x0F8  	// Measurement Result Channel B 14
#define  TempCard_IF_Result_B_15  		0x0FC  	// Measurement Result Channel B 15
#define  TempCard_IF_Result_B_16  		0x100  	// Measurement Result Channel B 16
#define  TempCard_IF_Result_B_17  		0x104  	// Measurement Result Channel B 17
#define  TempCard_IF_Result_B_18  		0x108  	// Measurement Result Channel B 18
#define  TempCard_IF_Result_B_19   		0x10C  	// Measurement Result Channel B 19

#define  TempCard_IF_Config_B_0   		0x110  	// Measurement Config Channel B 0
#define  TempCard_IF_Config_B_1   		0x114  	// Measurement Config Channel B 1
#define  TempCard_IF_Config_B_2   		0x118  	// Measurement Config Channel B 2
#define  TempCard_IF_Config_B_3   		0x11C  	// Measurement Config Channel B 3
#define  TempCard_IF_Config_B_4   		0x120  	// Measurement Config Channel B 4
#define  TempCard_IF_Config_B_5   		0x124  	// Measurement Config Channel B 5
#define  TempCard_IF_Config_B_6   		0x128  	// Measurement Config Channel B 6
#define  TempCard_IF_Config_B_7   		0x12C  	// Measurement Config Channel B 7
#define  TempCard_IF_Config_B_8   		0x130  	// Measurement Config Channel B 8
#define  TempCard_IF_Config_B_9   		0x134  	// Measurement Config Channel B 9
#define  TempCard_IF_Config_B_10   		0x138  	// Measurement Config Channel B 10
#define  TempCard_IF_Config_B_11  		0x13C  	// Measurement Config Channel B 11
#define  TempCard_IF_Config_B_12  		0x140  	// Measurement Config Channel B 12
#define  TempCard_IF_Config_B_13  		0x144  	// Measurement Config Channel B 13
#define  TempCard_IF_Config_B_14  		0x148  	// Measurement Config Channel B 14
#define  TempCard_IF_Config_B_15  		0x14C  	// Measurement Config Channel B 15
#define  TempCard_IF_Config_B_16  		0x150  	// Measurement Config Channel B 16
#define  TempCard_IF_Config_B_17  		0x154  	// Measurement Config Channel B 17
#define  TempCard_IF_Config_B_18  		0x158  	// Measurement Config Channel B 18
#define  TempCard_IF_Config_B_19   		0x15C  	// Measurement Config Channel B 19

//LTC2983 Channel C - Temperature results
#define  TempCard_IF_Result_C_0   		0x160  	// Measurement Result Channel C 0
#define  TempCard_IF_Result_C_1   		0x164  	// Measurement Result Channel C 1
#define  TempCard_IF_Result_C_2   		0x168  	// Measurement Result Channel C 2
#define  TempCard_IF_Result_C_3   		0x16C  	// Measurement Result Channel C 3
#define  TempCard_IF_Result_C_4   		0x170  	// Measurement Result Channel C 4
#define  TempCard_IF_Result_C_5   		0x174  	// Measurement Result Channel C 5
#define  TempCard_IF_Result_C_6   		0x178  	// Measurement Result Channel C 6
#define  TempCard_IF_Result_C_7   		0x17C  	// Measurement Result Channel C 7
#define  TempCard_IF_Result_C_8   		0x180  	// Measurement Result Channel C 8
#define  TempCard_IF_Result_C_9   		0x184  	// Measurement Result Channel C 9
#define  TempCard_IF_Result_C_10   		0x188  	// Measurement Result Channel C 10
#define  TempCard_IF_Result_C_11  		0x18C  	// Measurement Result Channel C 11
#define  TempCard_IF_Result_C_12  		0x190  	// Measurement Result Channel C 12
#define  TempCard_IF_Result_C_13  		0x194  	// Measurement Result Channel C 13
#define  TempCard_IF_Result_C_14  		0x198  	// Measurement Result Channel C 14
#define  TempCard_IF_Result_C_15  		0x19C  	// Measurement Result Channel C 15
#define  TempCard_IF_Result_C_16  		0x1A0  	// Measurement Result Channel C 16
#define  TempCard_IF_Result_C_17  		0x1A4  	// Measurement Result Channel C 17
#define  TempCard_IF_Result_C_18  		0x1A8  	// Measurement Result Channel C 18
#define  TempCard_IF_Result_C_19   		0x1AC  	// Measurement Result Channel C 19

#define  TempCard_IF_Config_C_0   		0x1B0  	// Measurement Config Channel C 0
#define  TempCard_IF_Config_C_1   		0x1B4  	// Measurement Config Channel C 1
#define  TempCard_IF_Config_C_2   		0x1B8  	// Measurement Config Channel C 2
#define  TempCard_IF_Config_C_3   		0x1BC  	// Measurement Config Channel C 3
#define  TempCard_IF_Config_C_4   		0x1C0  	// Measurement Config Channel C 4
#define  TempCard_IF_Config_C_5   		0x1C4  	// Measurement Config Channel C 5
#define  TempCard_IF_Config_C_6   		0x1C8  	// Measurement Config Channel C 6
#define  TempCard_IF_Config_C_7   		0x1CC  	// Measurement Config Channel C 7
#define  TempCard_IF_Config_C_8   		0x1D0  	// Measurement Config Channel C 8
#define  TempCard_IF_Config_C_9   		0x1D4  	// Measurement Config Channel C 9
#define  TempCard_IF_Config_C_10   		0x1D8  	// Measurement Config Channel C 10
#define  TempCard_IF_Config_C_11  		0x1DC  	// Measurement Config Channel C 11
#define  TempCard_IF_Config_C_12  		0x1E0  	// Measurement Config Channel C 12
#define  TempCard_IF_Config_C_13  		0x1E4  	// Measurement Config Channel C 13
#define  TempCard_IF_Config_C_14  		0x1E8  	// Measurement Config Channel C 14
#define  TempCard_IF_Config_C_15  		0x1EC  	// Measurement Config Channel C 15
#define  TempCard_IF_Config_C_16  		0x1F0  	// Measurement Config Channel C 16
#define  TempCard_IF_Config_C_17  		0x1F4  	// Measurement Config Channel C 17
#define  TempCard_IF_Config_C_18  		0x1F8  	// Measurement Config Channel C 18
#define  TempCard_IF_Config_C_19   		0x1FC  	// Measurement Config Channel C 19

#endif /* UZ_TEMPERATURECARD_HWADDRESSES_H_ */
