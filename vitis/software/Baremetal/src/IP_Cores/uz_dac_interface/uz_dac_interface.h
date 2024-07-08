#ifndef UZ_DAC_INTERFACE_H
#define UZ_DAC_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_array/uz_array.h"

/**
 * @brief Typedef for uz_dac_interface object definition
 * 
 */
typedef struct uz_dac_interface_t uz_dac_interface_t; 

/**
 * @brief Defines the maximum number of DAC channels on the PCB. Has to be 8!
 * 
 */
#define UZ_DAC_INTERFACE_OUTPUT_CHANNELS 8U

/**
 * @brief Configuration struct for the DAC Interface IP-Core
 * 
 */
struct uz_dac_interface_config_t{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of IP-Core */
    float reset_value; /**< Value to which the outputs are set if reset is true*/
    bool use_axi_inputs; /**< If true, data is used from AXI, otherwise from PL*/
    float gain[UZ_DAC_INTERFACE_OUTPUT_CHANNELS]; /**< Gain of the output OpAMPs of the DAC card. Usually set to 2.0f, but can be fine-tuned to match actual hardware. */
};

/**
 * @brief Initializes an instance of the DAC driver
 * 
 * @param config Config struct for the DAC
 * @return uz_dac_interface_t* Pointer to an instance of the driver
 */
uz_dac_interface_t* uz_dac_interface_init(struct uz_dac_interface_config_t config);

/**
 * @brief Writes the set-point to all DAC simultaneously. Saturates internally to allow for clipped operation.
 * 
 * @param self Pointer to driver instance
 * @param output_values Array of set-point values
 */
void uz_dac_interface_set_ouput_values(uz_dac_interface_t* self,uz_array_float_t* output_values);

/**
 * @brief Writes the reset value to the IP-Core, i.e., the value that the DAC card outputs on all channels when the reset signal is true.
 * 
 * @param self 
 * @param reset_value 
 */
void uz_dac_interface_set_reset_value(uz_dac_interface_t *self, float reset_value);

/**
 * @brief Sets the IP-Core in reset mode, i.e., all channels output the reset value.
 * 
 * @param self 
 * @param reset 
 */
void uz_dac_interface_reset(uz_dac_interface_t *self, bool reset);

/**
 * @brief Set 'use_axi', which determines if the output data and trigger source is AXI4 (use_axi=true) or PL (use_axi=false) pins.
 *
 * @param self
 * @param use_axi
 */
void uz_dac_interface_use_axi_inputs(uz_dac_interface_t *self, bool use_axi);


#endif // UZ_DAC_INTERFACE_H
