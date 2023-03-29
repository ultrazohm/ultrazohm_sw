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

// Since this library uses coded based on the Linduino-Sketchbook from Analog devices, the needed license from Analog Devices is attached!

/*
LTC2983: Multi-Sensor High Accuracy Digital Temperature Measurement System
@verbatim

DC2211_UNIVERSAL_TEMPERATURE_MEASUREMENT_BOARD.ino:
Generated Linduino code from the LTC2983 Demo Software.
This code  is designed to be used by a Linduino,
but can also be used to understand how to program the LTC2983.


@endverbatim

http://www.linear.com/product/LTC2983

http://www.linear.com/product/LTC2983#demoboards

Copyright 2018(c) Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.
 - Neither the name of Analog Devices, Inc. nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.
 - The use of this software may or may not infringe the patent rights
   of one or more patent holders.  This license does not release you
   from the requirement that you obtain separate licenses from these
   patent holders to use this software.
 - Use of the software either in source or binary form, must be run
   on or directly connected to an Analog Devices Inc. component.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
//***********************************************************************************************************
#ifndef UZ_TEMPERATURECARD_H
#define UZ_TEMPERATURECARD_H

#include <stdint.h>
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_temperaturecard_hw.h"

// Defines for easier configuration
//-----------------------------------------------------------------------------------------------------------
// -- SENSOR TYPES --
// RTD
#define SENSOR_TYPE__RTD_PT_10 (uint32_t) 0xA << 27
#define SENSOR_TYPE__RTD_PT_50 (uint32_t) 0xB << 27
#define SENSOR_TYPE__RTD_PT_100 (uint32_t) 0xC << 27
#define SENSOR_TYPE__RTD_PT_200 (uint32_t) 0xD << 27
#define SENSOR_TYPE__RTD_PT_500 (uint32_t) 0xE << 27
#define SENSOR_TYPE__RTD_PT_1000 (uint32_t) 0xF << 27
#define SENSOR_TYPE__RTD_PT_1000_375 (uint32_t) 0x10 << 27
#define SENSOR_TYPE__RTD_NI_120 (uint32_t) 0x11 << 27
#define SENSOR_TYPE__RTD_CUSTOM (uint32_t) 0x12 << 27
// Sense Resistor
#define SENSOR_TYPE__SENSE_RESISTOR (uint32_t) 0x1D << 27
// -
#define SENSOR_TYPE__NONE (uint32_t) 0x0 << 27
// Direct ADC
#define SENSOR_TYPE__DIRECT_ADC (uint32_t) 0x1E << 27
// Thermistor
#define SENSOR_TYPE__THERMISTOR_44004_2P252K_25C (uint32_t) 0x13 << 27
#define SENSOR_TYPE__THERMISTOR_44005_3K_25C (uint32_t) 0x14 << 27
#define SENSOR_TYPE__THERMISTOR_44007_5K_25C (uint32_t) 0x15 << 27
#define SENSOR_TYPE__THERMISTOR_44006_10K_25C (uint32_t) 0x16 << 27
#define SENSOR_TYPE__THERMISTOR_44008_30K_25C (uint32_t) 0x17 << 27
#define SENSOR_TYPE__THERMISTOR_YSI_400_2P252K_25C (uint32_t) 0x18 << 27
#define SENSOR_TYPE__THERMISTOR_1003K_1K_25C (uint32_t) 0x19 << 27
#define SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART (uint32_t) 0x1A << 27
#define SENSOR_TYPE__THERMISTOR_CUSTOM_TABLE (uint32_t) 0x1B << 27
// Thermocouple
#define SENSOR_TYPE__TYPE_J_THERMOCOUPLE (uint32_t) 0x1 << 27
#define SENSOR_TYPE__TYPE_K_THERMOCOUPLE (uint32_t) 0x2 << 27
#define SENSOR_TYPE__TYPE_E_THERMOCOUPLE (uint32_t) 0x3 << 27
#define SENSOR_TYPE__TYPE_N_THERMOCOUPLE (uint32_t) 0x4 << 27
#define SENSOR_TYPE__TYPE_R_THERMOCOUPLE (uint32_t) 0x5 << 27
#define SENSOR_TYPE__TYPE_S_THERMOCOUPLE (uint32_t) 0x6 << 27
#define SENSOR_TYPE__TYPE_T_THERMOCOUPLE (uint32_t) 0x7 << 27
#define SENSOR_TYPE__TYPE_B_THERMOCOUPLE (uint32_t) 0x8 << 27
#define SENSOR_TYPE__CUSTOM_THERMOCOUPLE (uint32_t) 0x9 << 27
// Off-Chip Diode
#define SENSOR_TYPE__OFF_CHIP_DIODE (uint32_t) 0x1C << 27
//-----------------------------------------------------------------------------------------------------------
// -- RTD --
// rtd - rsense channel
#define RTD_RSENSE_CHANNEL__NONE (uint32_t) 0x0 << 22
#define RTD_RSENSE_CHANNEL__1 (uint32_t) 0x1 << 22
#define RTD_RSENSE_CHANNEL__2 (uint32_t) 0x2 << 22
#define RTD_RSENSE_CHANNEL__3 (uint32_t) 0x3 << 22
#define RTD_RSENSE_CHANNEL__4 (uint32_t) 0x4 << 22
#define RTD_RSENSE_CHANNEL__5 (uint32_t) 0x5 << 22
#define RTD_RSENSE_CHANNEL__6 (uint32_t) 0x6 << 22
#define RTD_RSENSE_CHANNEL__7 (uint32_t) 0x7 << 22
#define RTD_RSENSE_CHANNEL__8 (uint32_t) 0x8 << 22
#define RTD_RSENSE_CHANNEL__9 (uint32_t) 0x9 << 22
#define RTD_RSENSE_CHANNEL__10 (uint32_t) 0xA << 22
#define RTD_RSENSE_CHANNEL__11 (uint32_t) 0xB << 22
#define RTD_RSENSE_CHANNEL__12 (uint32_t) 0xC << 22
#define RTD_RSENSE_CHANNEL__13 (uint32_t) 0xD << 22
#define RTD_RSENSE_CHANNEL__14 (uint32_t) 0xE << 22
#define RTD_RSENSE_CHANNEL__15 (uint32_t) 0xF << 22
#define RTD_RSENSE_CHANNEL__16 (uint32_t) 0x10 << 22
#define RTD_RSENSE_CHANNEL__17 (uint32_t) 0x11 << 22
#define RTD_RSENSE_CHANNEL__18 (uint32_t) 0x12 << 22
#define RTD_RSENSE_CHANNEL__19 (uint32_t) 0x13 << 22
#define RTD_RSENSE_CHANNEL__20 (uint32_t) 0x14 << 22
// rtd - num wires
#define RTD_NUM_WIRES__2_WIRE (uint32_t) 0x0 << 20
#define RTD_NUM_WIRES__3_WIRE (uint32_t) 0x1 << 20
#define RTD_NUM_WIRES__4_WIRE (uint32_t) 0x2 << 20
#define RTD_NUM_WIRES__4_WIRE_KELVIN_RSENSE (uint32_t) 0x3 << 20
// rtd - excitation mode
#define RTD_EXCITATION_MODE__NO_ROTATION_NO_SHARING (uint32_t) 0x0 << 18
#define RTD_EXCITATION_MODE__NO_ROTATION_SHARING (uint32_t) 0x1 << 18
#define RTD_EXCITATION_MODE__ROTATION_SHARING (uint32_t) 0x2 << 18
// rtd - excitation current
#define RTD_EXCITATION_CURRENT__INVALID (uint32_t) 0x0 << 14
#define RTD_EXCITATION_CURRENT__5UA (uint32_t) 0x1 << 14
#define RTD_EXCITATION_CURRENT__10UA (uint32_t) 0x2 << 14
#define RTD_EXCITATION_CURRENT__25UA (uint32_t) 0x3 << 14
#define RTD_EXCITATION_CURRENT__50UA (uint32_t) 0x4 << 14
#define RTD_EXCITATION_CURRENT__100UA (uint32_t) 0x5 << 14
#define RTD_EXCITATION_CURRENT__250UA (uint32_t) 0x6 << 14
#define RTD_EXCITATION_CURRENT__500UA (uint32_t) 0x7 << 14
#define RTD_EXCITATION_CURRENT__1MA (uint32_t) 0x8 << 14
// rtd - standard
#define RTD_STANDARD__EUROPEAN (uint32_t) 0x0 << 12
#define RTD_STANDARD__AMERICAN (uint32_t) 0x1 << 12
#define RTD_STANDARD__JAPANESE (uint32_t) 0x2 << 12
#define RTD_STANDARD__ITS_90 (uint32_t) 0x3 << 12
//-----------------------------------------------------------------------------------------------------------
// -- Sense Resistor --
// sense resistor - value
#define SENSE_RESISTOR_VALUE 0
//-----------------------------------------------------------------------------------------------------------
// -- Thermistor --
// thermistor - rsense channel
#define THERMISTOR_RSENSE_CHANNEL__NONE (uint32_t) 0x0 << 22
#define THERMISTOR_RSENSE_CHANNEL__1 (uint32_t) 0x1 << 22
#define THERMISTOR_RSENSE_CHANNEL__2 (uint32_t) 0x2 << 22
#define THERMISTOR_RSENSE_CHANNEL__3 (uint32_t) 0x3 << 22
#define THERMISTOR_RSENSE_CHANNEL__4 (uint32_t) 0x4 << 22
#define THERMISTOR_RSENSE_CHANNEL__5 (uint32_t) 0x5 << 22
#define THERMISTOR_RSENSE_CHANNEL__6 (uint32_t) 0x6 << 22
#define THERMISTOR_RSENSE_CHANNEL__7 (uint32_t) 0x7 << 22
#define THERMISTOR_RSENSE_CHANNEL__8 (uint32_t) 0x8 << 22
#define THERMISTOR_RSENSE_CHANNEL__9 (uint32_t) 0x9 << 22
#define THERMISTOR_RSENSE_CHANNEL__10 (uint32_t) 0xA << 22
#define THERMISTOR_RSENSE_CHANNEL__11 (uint32_t) 0xB << 22
#define THERMISTOR_RSENSE_CHANNEL__12 (uint32_t) 0xC << 22
#define THERMISTOR_RSENSE_CHANNEL__13 (uint32_t) 0xD << 22
#define THERMISTOR_RSENSE_CHANNEL__14 (uint32_t) 0xE << 22
#define THERMISTOR_RSENSE_CHANNEL__15 (uint32_t) 0xF << 22
#define THERMISTOR_RSENSE_CHANNEL__16 (uint32_t) 0x10 << 22
#define THERMISTOR_RSENSE_CHANNEL__17 (uint32_t) 0x11 << 22
#define THERMISTOR_RSENSE_CHANNEL__18 (uint32_t) 0x12 << 22
#define THERMISTOR_RSENSE_CHANNEL__19 (uint32_t) 0x13 << 22
#define THERMISTOR_RSENSE_CHANNEL__20 (uint32_t) 0x14 << 22
// thermistor - differential?
#define THERMISTOR_DIFFERENTIAL (uint32_t) 0x0 << 21
#define THERMISTOR_SINGLE_ENDED (uint32_t) 0x1 << 21
// thermistor - excitation mode
#define THERMISTOR_EXCITATION_MODE__NO_SHARING_NO_ROTATION (uint32_t) 0x0 << 19
#define THERMISTOR_EXCITATION_MODE__SHARING_ROTATION (uint32_t) 0x1 << 19
#define THERMISTOR_EXCITATION_MODE__SHARING_NO_ROTATION (uint32_t) 0x2 << 19
// thermistor - excitation current
#define THERMISTOR_EXCITATION_CURRENT__INVALID (uint32_t) 0x0 << 15
#define THERMISTOR_EXCITATION_CURRENT__250NA (uint32_t) 0x1 << 15
#define THERMISTOR_EXCITATION_CURRENT__500NA (uint32_t) 0x2 << 15
#define THERMISTOR_EXCITATION_CURRENT__1UA (uint32_t) 0x3 << 15
#define THERMISTOR_EXCITATION_CURRENT__5UA (uint32_t) 0x4 << 15
#define THERMISTOR_EXCITATION_CURRENT__10UA (uint32_t) 0x5 << 15
#define THERMISTOR_EXCITATION_CURRENT__25UA (uint32_t) 0x6 << 15
#define THERMISTOR_EXCITATION_CURRENT__50UA (uint32_t) 0x7 << 15
#define THERMISTOR_EXCITATION_CURRENT__100UA (uint32_t) 0x8 << 15
#define THERMISTOR_EXCITATION_CURRENT__250UA (uint32_t) 0x9 << 15
#define THERMISTOR_EXCITATION_CURRENT__500UA (uint32_t) 0xA << 15
#define THERMISTOR_EXCITATION_CURRENT__1MA (uint32_t) 0xB << 15
#define THERMISTOR_EXCITATION_CURRENT__AUTORANGE (uint32_t) 0xC << 15
//-----------------------------------------------------------------------------------------------------------
// -- Thermocouple --
// tc - cold junction ch
#define TC_COLD_JUNCTION_CH__NONE (uint32_t) 0x0 << 22
#define TC_COLD_JUNCTION_CH__1 (uint32_t) 0x1 << 22
#define TC_COLD_JUNCTION_CH__2 (uint32_t) 0x2 << 22
#define TC_COLD_JUNCTION_CH__3 (uint32_t) 0x3 << 22
#define TC_COLD_JUNCTION_CH__4 (uint32_t) 0x4 << 22
#define TC_COLD_JUNCTION_CH__5 (uint32_t) 0x5 << 22
#define TC_COLD_JUNCTION_CH__6 (uint32_t) 0x6 << 22
#define TC_COLD_JUNCTION_CH__7 (uint32_t) 0x7 << 22
#define TC_COLD_JUNCTION_CH__8 (uint32_t) 0x8 << 22
#define TC_COLD_JUNCTION_CH__9 (uint32_t) 0x9 << 22
#define TC_COLD_JUNCTION_CH__10 (uint32_t) 0xA << 22
#define TC_COLD_JUNCTION_CH__11 (uint32_t) 0xB << 22
#define TC_COLD_JUNCTION_CH__12 (uint32_t) 0xC << 22
#define TC_COLD_JUNCTION_CH__13 (uint32_t) 0xD << 22
#define TC_COLD_JUNCTION_CH__14 (uint32_t) 0xE << 22
#define TC_COLD_JUNCTION_CH__15 (uint32_t) 0xF << 22
#define TC_COLD_JUNCTION_CH__16 (uint32_t) 0x10 << 22
#define TC_COLD_JUNCTION_CH__17 (uint32_t) 0x11 << 22
#define TC_COLD_JUNCTION_CH__18 (uint32_t) 0x12 << 22
#define TC_COLD_JUNCTION_CH__19 (uint32_t) 0x13 << 22
#define TC_COLD_JUNCTION_CH__20 (uint32_t) 0x14 << 22
// tc - differential?
#define TC_DIFFERENTIAL (uint32_t) 0x0 << 21
#define TC_SINGLE_ENDED (uint32_t) 0x1 << 21
// tc - open ckt detect?
#define TC_OPEN_CKT_DETECT__NO (uint32_t) 0x0 << 20
#define TC_OPEN_CKT_DETECT__YES (uint32_t) 0x1 << 20
// tc - open ckt detect current
#define TC_OPEN_CKT_DETECT_CURRENT__10UA (uint32_t) 0x0 << 18
#define TC_OPEN_CKT_DETECT_CURRENT__100UA (uint32_t) 0x1 << 18
#define TC_OPEN_CKT_DETECT_CURRENT__500UA (uint32_t) 0x2 << 18
#define TC_OPEN_CKT_DETECT_CURRENT__1MA (uint32_t) 0x3 << 18
//-----------------------------------------------------------------------------------------------------------
// -- Off-Chip Diode --
// diode - differential?
#define DIODE_DIFFERENTIAL (uint32_t) 0x0 << 26
#define DIODE_SINGLE_ENDED (uint32_t) 0x1 << 26
// diode - num readings
#define DIODE_NUM_READINGS__2 (uint32_t) 0x0 << 25
#define DIODE_NUM_READINGS__3 (uint32_t) 0x1 << 25
// diode - averaging on?
#define DIODE_AVERAGING_OFF (uint32_t) 0x0 << 24
#define DIODE_AVERAGING_ON (uint32_t) 0x1 << 24
// diode - current
#define DIODE_CURRENT__10UA_40UA_80UA (uint32_t) 0x0 << 22
#define DIODE_CURRENT__20UA_80UA_160UA (uint32_t) 0x1 << 22
#define DIODE_CURRENT__40UA_160UA_320UA (uint32_t) 0x2 << 22
#define DIODE_CURRENT__80UA_320UA_640UA (uint32_t) 0x3 << 22
//-----------------------------------------------------------------------------------------------------------
// -- STATUS BYTE CONSTANTS --
#define SENSOR_HARD_FAILURE (uint8_t) 0x80
#define ADC_HARD_FAILURE    (uint8_t) 0x40
#define CJ_HARD_FAILURE     (uint8_t) 0x20
#define CJ_SOFT_FAILURE     (uint8_t) 0x10
#define SENSOR_ABOVE        (uint8_t) 0x8
#define SENSOR_BELOW        (uint8_t) 0x4
#define ADC_RANGE_ERROR     (uint8_t) 0x2
#define VALID               (uint8_t) 0x1
//-----------------------------------------------------------------------------------------------------------

//Defines for the lib
/** Needed to calculate the Temperature */
#define TEMP_CONVERSION_FACTOR      0.000976563                         // 1/1024
/** Temperature Channel for one LTC2983 */
#define CHANNEL_COUNT     			    20                                 
/** Number of LTC2983 */
#define GROUP_COUNT                 3                                   
/** calculated Number of Temperature Channels */
#define CHANNEL_TOTAL               CHANNEL_COUNT * GROUP_COUNT         
/** Readback to check if IP-Core is available */
#define IP_CORE_READBACK_VALUE      0xAFFEAFFE                         

/**
 * @brief Data type for object uz_temperaturecard
 *
 */
typedef struct uz_temperaturecard_t uz_temperaturecard_t;

/**
 * @brief Data type for object uz_temperaturecard_OneGroup
 *
 */
typedef struct {
	float       temperature[20];       /**< calculated value for one Temperature Channel */
	uint32_t    temperature_raw[20];   /**< raw value for one Temperature Channel */
	uint32_t    Configdata[20];        /**< used Config for one Temperature Channel */
	uint32_t	Channels_Valid[20];  /**< Informations about the measurement */
}uz_temperaturecard_OneGroup;

/**
 * @brief Configuration struct for TemperatureCard-IP
 *
 */
struct uz_temperaturecard_config_t{
    uint32_t    base_address;                   /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t    ip_clk_frequency_Hz;            /**< Clock frequency of IP-Core */
    uint32_t 	  Sample_Freq;                    /**< Sampling frequency to trigger a temperature measurement */
    uint32_t    Configdata_A[20];               /**< Configuration-struct for the first 20-Channels  / Channelgroup A */
    uint32_t    Configdata_B[20];               /**< Configuration-struct for the second 20-Channels / Channelgroup B */
    uint32_t    Configdata_C[20];               /**< Configuration-struct for the last 20-Channels   / Channelgroup C */
};

uz_temperaturecard_OneGroup uz_TempCard_IF_get_channel(uz_temperaturecard_t* self, const char channel);

/**
 * @brief Initializes an instance of the temperaturecard driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_temperaturecard_t* uz_temperaturecard_init(struct uz_temperaturecard_config_t config);

/**
 * @brief Resets the whole TemperatureCard-IP. This should be used after the init of the IP-Core to update the LTC2983
 *
 * @param self Pointer to driver instance
 */
void uz_TempCard_IF_Reset(uz_temperaturecard_t* self);

/**
 * @brief Starts the TemperatureCard-IP
 *
 * @param self Pointer to driver instance
 */
void uz_TempCard_IF_Start(uz_temperaturecard_t* self);

/**
 * @brief Starts the TemperatureCard-IP
 *
 * @param self Pointer to driver instance
 */
void uz_TempCard_IF_Stop(uz_temperaturecard_t* self);

/**
 * @brief Reads every Temperature-Channel of the IP-Core and updates every Temperature-Data of the instance. ATTENTION!!! this will need a lot of time, NEVER use it in the ISR!
 *
 * @param self Pointer to driver instance
 */
void uz_TempCard_IF_MeasureTemps_all(uz_temperaturecard_t* self);

/**
 * @brief Reads one Temperature-Channel of the IP-Core and updates the dedicated Temperature-Data of the the instance. To Update the whole Temperature-Data of the instance, multiple calls equal the Channel-amount (60) are needed. Can be used inside the ISR.
 *
 * @param self Pointer to driver instance
 */
void uz_TempCard_IF_MeasureTemps_cyclic(uz_temperaturecard_t* self);


#endif // UZ_TEMPERATURECARD_H
