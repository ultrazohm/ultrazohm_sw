/******************************************************************************
* Copyright 2023 Robert Zipprich
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

#ifndef UZ_LINEARREGRESSIONCORE_H
#define UZ_LINEARREGRESSIONCORE_H

#include <stdint.h>
#include "uz_LinearRegressionCore_hw.h"
#include "../../uz/uz_HAL.h"

// Defines for easier configuration
//-----------------------------------------------------------------------------------------------------------
#define LR_CHANNEL_1			0b00000000000000000000000000000001
#define LR_CHANNEL_2			0b00000000000000000000000000000010
#define LR_CHANNEL_3			0b00000000000000000000000000000100
#define LR_CHANNEL_4			0b00000000000000000000000000001000
#define LR_CHANNEL_5			0b00000000000000000000000000010000
#define LR_CHANNEL_6			0b00000000000000000000000000100000
#define LR_CHANNEL_7			0b00000000000000000000000001000000
#define LR_CHANNEL_8			0b00000000000000000000000010000000
#define LR_CHANNEL_4			0b00000000000000000000000100000000
#define LR_CHANNEL_10			0b00000000000000000000001000000000
#define LR_CHANNEL_11			0b00000000000000000000010000000000
#define LR_CHANNEL_12			0b00000000000000000000100000000000
#define LR_CHANNEL_13			0b00000000000000000001000000000000
#define LR_CHANNEL_14			0b00000000000000000010000000000000
#define LR_CHANNEL_15			0b00000000000000000100000000000000
#define LR_CHANNEL_16			0b00000000000000001000000000000000
#define LR_CHANNEL_17			0b00000000000000010000000000000000
#define LR_CHANNEL_18			0b00000000000000100000000000000000
#define LR_CHANNEL_19			0b00000000000001000000000000000000
#define LR_CHANNEL_20			0b00000000000010000000000000000000
#define LR_CHANNEL_21			0b00000000000100000000000000000000
#define LR_CHANNEL_22			0b00000000001000000000000000000000
#define LR_CHANNEL_23			0b00000000010000000000000000000000
#define LR_CHANNEL_24			0b00000000100000000000000000000000
#define LR_CHANNEL_25			0b00000001000000000000000000000000
#define LR_CHANNEL_26			0b00000010000000000000000000000000
#define LR_CHANNEL_27			0b00000100000000000000000000000000
#define LR_CHANNEL_28			0b00001000000000000000000000000000
#define LR_CHANNEL_29			0b00010000000000000000000000000000
#define LR_CHANNEL_30			0b00100000000000000000000000000000
#define LR_CHANNEL_31			0b01000000000000000000000000000000
#define LR_CHANNEL_32			0b10000000000000000000000000000000

#define LR_CHANNEL_All			0xFFFF
#define LR_CHANNEL_None			0X0000

//Defines for the Driver
#define CHANNEL_Max			32

/**
 * @brief Data type for object uz_LinearRegressionCore
 *
 */
typedef struct uz_LinearRegressionCore_t uz_LinearRegressionCore_t;


/**
 * @brief Configuration struct for uz_LinearRegressionCore-IP
 *
 */
struct uz_LinearRegressionCore_config_t{
    uint32_t    base_address;
    uint32_t    ip_clk_frequency_Hz;
    uint32_t    enabled_Channels;
};

/**
 * @brief Initializes an instance of the uz_LinearRegressionCore driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_LinearRegressionCore_t* uz_LinearRegressionCore_init(struct uz_LinearRegressionCore_config_t config);

/**
 * @brief enables Linear Regression on specified Channel
 *
 * @param self Pointer to driver instance
 * @param Channel_nr Number of the Channel to enable
 */
void enable_Channel(uz_LinearRegressionCore_t*, uint32_t Channel_nr);	//

/**
 * @brief disables Linear Regression on specified Channel
 *
 * @param self Pointer to driver instance
 * @param Channel_nr Number of the Channel to disable
 */
void disable_Channel(uz_LinearRegressionCore_t*, uint32_t Channel_nr);

/**
 * @brief Starts the TemperatureCard-IP
 *
 * @param self Pointer to driver instance
 * @return Value with determines enabled Channels
 */
uint32_t check_Channel(uz_LinearRegressionCore_t*);

#endif // UZ_LINEARREGRESSIONCORE_H
