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
    uint32_t ssi_clk_frequency_Hz; /**< Clock frequency for the serial communication clock, values between 80 kHz and 2.5 MHz are allowed */
    uint32_t ssi_encoder_bit_width;/**< Number of position bits of the SSI encoder, values up to 32 are allowed */
    uint32_t machine_polepairs; /**< Polepairs of the machine, only positive values >=1 are allowed */
};

/**
 * @brief Output struct for uz_ssi_interface
 *
 */
struct uz_ssi_interface_outputs_t {
    uint32_t position_raw; /**< raw position in bit ticks, ranging from 0..ssi_encoder_bit_width-1 */
    float position_mech_si; /**< mechanical angle in rad, ranging from 0..2pi */
    float position_el_si; /**< electrical angle in rad, ranging from 0..2pi */
    float speed_mech_si; /**< mechanical rotational speed in rad/s */
    float speed_el_si; /**< electrical rotational speed in rad/s */
    float speed_mech_rpm; /**< mechanical rotational speed in rounds per minute */
};

/**
 * @brief Initializes an instance of the uz_ssi_interface driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_ssi_interface_t* uz_ssi_interface_init(struct uz_ssi_interface_config_t config, struct uz_ssi_interface_outputs_t outputs);

/**
 * @brief Writes the config from the struct into the IP-Core
 *
 * @param self Pointer to the instance
 */
void uz_ssi_interface_set_config(uz_ssi_interface_t *self);

#endif // UZ_SSI_INTERFACE_H
