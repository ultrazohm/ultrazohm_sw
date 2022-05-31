#ifndef UZ_DAC_INTERFACE_H
#define UZ_DAC_INTERFACE_H

#include <stdint.h>
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


#endif // UZ_DAC_INTERFACE_H
