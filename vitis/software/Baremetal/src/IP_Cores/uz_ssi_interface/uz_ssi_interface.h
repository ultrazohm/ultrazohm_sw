#ifndef UZ_SSI_INTERFACE_H
#define UZ_SSI_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enumeration of the encoding configurations for the position information
 *
 */
enum position_encoding_t {
    binary=0,
    gray_code
};

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
    uint32_t ssi_encoder_bit_width_single_turn;/**< Number of single-turn position bits of the SSI encoder, values up to 25 are allowed. Note that the sum of all bit widths (single-turn, multi-turn, and status) have to be less or equal than 64 */
    uint32_t ssi_encoder_bit_width_multi_turn;/**< Number of multi-turn position bits of the SSI encoder, values up to 25 are allowed */
    uint32_t ssi_encoder_number_of_status_bits;/**< Number of status bits of the SSI encoder, values up to 32 are allowed */
    enum position_encoding_t position_encoding;/**< Select if the position encoding of the SSI encoder is \n
                                                                                         binary or \n 
                                                                                         gray_code */
    uint32_t machine_polepairs; /**< Pole pairs of the machine, only positive values >=1 are allowed */
    float sampling_interval_seconds; /**< Sampling interval for the integration employed in the PLL for speed calculation */
    float kp_pll; /**< Proportional gain for the PI within the PLL */
    float ki_pll; /**< Integral gain for the PI within the PLL */
    float position_mech_offset_si_single_turn; /**< Mechanical encoder offset between encoder zero and magnetic zero of the electric machine. Limited to -7.999 ... 7.999 */
};

/**
 * @brief Output struct for uz_ssi_interface
 *
 */
struct uz_ssi_interface_outputs_t {
    uint32_t position_raw_single_turn; /**< raw position in bit ticks, ranging from 0..ssi_encoder_bit_width_single_turn-1 */
    uint32_t position_multi_turn; /**< raw position in bit ticks, ranging from 0..ssi_encoder_bit_width_multi_turn-1 */
    float position_mech_si_single_turn; /**< mechanical angle in rad, ranging from 0..2pi */
    float position_el_si_single_turn; /**< electrical angle in rad, ranging from 0..2pi */
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

/**
 * @brief Updates the output struct of the driver
 *
 * @param self Pointer to the instance
 */
void uz_ssi_interface_update_all_outputs(uz_ssi_interface_t *self);

uint32_t uz_ssi_interface_get_position_raw_single_turn(uz_ssi_interface_t *self);
uint32_t uz_ssi_interface_get_position_raw_multi_turn(uz_ssi_interface_t *self);
float uz_ssi_interface_get_position_mech_si_single_turn(uz_ssi_interface_t *self);
float uz_ssi_interface_get_position_el_si_single_turn(uz_ssi_interface_t *self); 
float uz_ssi_interface_get_speed_mech_si(uz_ssi_interface_t *self);
float uz_ssi_interface_get_speed_el_si(uz_ssi_interface_t *self);
float uz_ssi_interface_get_speed_mech_rpm(uz_ssi_interface_t *self);

/**
 * @brief Enables the IP core, i.e., starting the SSI transactions.
 * @brief The IP core is designed the way that no matter when you turn it on or off the, 
 * @brief it will perform enabling or disabling only when there is no SSI transaction happening.
 *
 * @param self Pointer to the instance
 * @param ip_core_off_on Flag to enable the IP core, false=off, true=enabled
 */
void uz_ssi_interface_enable_ip(uz_ssi_interface_t *self, bool ip_core_off_on);

/**
 * @brief Sets a new mechanical offset value for the single-turn position 
 * @brief Values between -7.999 ... 7.999 are allowed
 *
 * @param self Pointer to the instance
 * @param position_mech_offset_si_single_turn Mechanical encoder offset between encoder zero and magnetic zero of the electric machine 
 */
void uz_ssi_interface_set_mechanical_offset_ssi_single_turn(uz_ssi_interface_t *self, float position_mech_offset_si_single_turn);


/**
 * @brief Calculates the ceiled value of an unsigned integer division.
 * @brief Attention: Does not catch overflow of (a+b)>UINT32_MAX
 *
 * @param a Dividend
 * @param b Divisor
 *
 * @return Ceiled unsigned integer division
 */
uint32_t ceil_div(uint32_t a, uint32_t b);

#endif // UZ_SSI_INTERFACE_H
