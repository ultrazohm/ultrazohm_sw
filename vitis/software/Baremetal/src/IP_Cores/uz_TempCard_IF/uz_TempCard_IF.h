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

/******************************************************************************
 * HOW THIS DRIVER COULD BE USED:
 * ------------------------------
 * This library provide an easy way to use the UZ_Temperature_Card.
 * For easier handling, the library uses an internal structure to mirror the Registers of the Interface-IP.
 * The Channels can be addressed by values from 0-59 and all needed address calculation will be performed internally.
 * 
 * To get comfy with the library, here is some pseudo-code, which will configure the Channels and starts the continuous measurement:
 * 1. create needed handler and assign the IP-Base-Addresse
 * 		uz_TempCard_IF uz_TempCard_IF_Instance1 = {
				.base_address = 0x00A0000000
		};
		uz_TempCard_IF_handle UZ_TempCard = uz_TempCard_IF_init(&uz_TempCard_IF_Instance1);

 * 2. Perform an Initial Reset for the Interface-IP
 *      uz_TempCard_IF_Reset(handle);
 * 
 * 3. Write the Channelconfigs according to the LTC2983-Datasheet. The config-words can be determined by (https://www.analog.com/en/products/ltc2983.html)
 *      uz_TempCard_IF_SetConfig(handle, Configword, Channel); [Repeat this for every channel needed]
 * 
 * 4. Sync the Configs to the Interface-IP
 *      uz_TempCard_IF_SyncConfig(handle);
 * 
 * 5. Set a counter period, which will trigger the continuous measurement
 *      uz_TempCard_IF_setCounter(handle, countervalue);
 * 
 * 6. Start the Interface-IP
 *       uz_TempCard_IF_Start(handle);
 * 
 * 7. Fetch the Measurements in the internal structure
 *      uz_TempCard_IF_MeasureTemps(handle);
 * 
 * 8. Enjoy measuremt temperatures
 *      uz_TempCard_IF_ReadMeasurement_Channel(handle, Channel);
 * 
 * ADDITIONAL INFORMATIONS:
 * A. If you want to change some Channel configs while running, you have to perform the following steps:
 *      1. write the new config in the structure with uz_TempCard_IF_SetConfig.
 *      2.  sync down the configs with uz_TempCard_IF_SyncConfig.
 *      3. Just reset the Interface-IP with uz_TempCard_IF_Reset. This will apply the new config within the LTC2983 and resumes the measurement.
 * 
 * B. The function uz_TempCard_IF_ReadBack must always return 0xAFFEAFFE, otherwise the Interfafe-IP is not present at the specified address.
 * C. With the function uz_TempCard_IF_CheckSync you can easily secure if the configs are in sync (Struct and HW).
 * D. The LTC2983 offers a wide range for checking if the measurement is done right or if some failure occur. 
 *    With the function uz_TempCard_IF_CheckMeasurement_Channel you can see if the stored temperature value can be used or is corrupted.
 *    The defines in this header-file can help you for further implementation. 
 *    Value 1 returned by this functions declares a valid measurement, other values should be checked.
 *    More informations can be found in the Datasheet (https://www.analog.com/en/products/ltc2983.html).
 * 
 ******************************************************************************/
#pragma once
#ifndef UZ_TEMPCARD_IF_H
#define UZ_TEMPCARD_IF_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

//Defines for the lib
#define TEMP_CONVERSION_FACTOR      0.000976563     // 1/1024
#define CHANNEL_COUNT_OneChannel    20
#define CHANNEL_COUNT               3
#define CHANNEL_TOTAL               CHANNEL_COUNT_OneChannel * CHANNEL_COUNT
#define IP_CORE_READBACK_VALUE      0xAFFEAFFE

//Defines for the LTC2983
#define SENSOR_HARD_FAULT           128
#define ADC_HARD_FAULT              64
#define CJ_HARD_FAULT               32
#define CJ_SOFT_FAULT               16
#define SENSOR_OVER_RANGE_FAULT     8
#define SENSOR_UNDER_RANGE_FAULT    4
#define ADC_OUT_OF_RANGE_FAULT      2
#define VALID                       1

//
typedef struct uz_TempCard_IF uz_TempCard_IF;
typedef struct uz_TempCard_IF *uz_TempCard_IF_handle;

//Handling with the Core
uz_TempCard_IF_handle uz_TempCard_IF_init(uz_TempCard_IF_handle self);

void        uz_TempCard_IF_Reset(uz_TempCard_IF_handle self);                                               // Resets the Interface-IP to write new Channel configs
void        uz_TempCard_IF_Start(uz_TempCard_IF_handle self);                                               // Starts the Interface-IP
void        uz_TempCard_IF_Stop(uz_TempCard_IF_handle self);                                                // Stops the Interface-IP
uint32_t    uz_TempCard_IF_ReadBack(uz_TempCard_IF_handle self);                                            // Stops the Interface-IP
void        uz_TempCard_IF_setCounter(uz_TempCard_IF_handle self, uint32_t Counter);                        // Set the Counter for the internal trigger generator
uint32_t    uz_TempCard_IF_SetConfig(uz_TempCard_IF_handle self, uint32_t ConfigWord, uint32_t Channel);// Set the ConfigWord for the specified channel
uint32_t    uz_TempCard_IF_GetConfig(uz_TempCard_IF_handle self, uint32_t Channel);                         // Read the Config of the specified Channel
void        uz_TempCard_IF_SyncConfig(uz_TempCard_IF_handle self);                                          // Writes the in the struct stored config down to the Interface-IP
bool        uz_TempCard_IF_CheckSync(uz_TempCard_IF_handle self);                                           // Checks wheather the in the IP stored config is in Sync with the config stored in the struct
void        uz_TempCard_IF_MeasureTemps(uz_TempCard_IF_handle self);                                        // Gets the Temperature-Data from all LTC2983, converts the results and stores the tempvalue in the struct
float       uz_TempCard_IF_ReadMeasurement_Channel(uz_TempCard_IF_handle self, uint32_t Channel);           // Read the Temperature Value of the specified Channel
uint8_t     uz_TempCard_IF_CheckMeasurement_Channel(uz_TempCard_IF_handle self, uint32_t Channel);          // Checks wheather the measurement of the Channel is valid


// Static allocator function
uz_TempCard_IF_handle uz_TempCard_IF_staticAllocator(void);


#endif // UZ_TEMPCARD_IF_H
