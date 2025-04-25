#ifndef UZ_SSI_INTERFACE_H
#define UZ_SSI_INTERFACE_H
#include <stdint.h>

/**
 * @brief Data type for object uz_ssi_interface
 *
 */
typedef struct uz_ssi_interface_t uz_ssi_interface_t;

/**
 * @brief Configuration struct for uz_ssi_interface
 *
 */
struct uz_ssi_interface_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Output struct for uz_ssi_interface
 *
 */
struct uz_ssi_interface_outputs_t {
    uint32_t position_raw; /**< raw position in bit ticks, ranging from 0..ssi_encoder_bit_width-1 */
    float position_si; /**< mechanical angle in rad, ranging from 0..2pi */
    float speed_mech_si; /**< mechanical rotational speed in rad/s */
};

/**
 * @brief Initializes an instance of the uz_ssi_interface driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_ssi_interface_t* uz_ssi_interface_init(struct uz_ssi_interface_config_t config);

#endif // UZ_SSI_INTERFACE_H
