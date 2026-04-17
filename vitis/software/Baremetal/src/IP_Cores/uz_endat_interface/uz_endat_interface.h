#ifndef UZ_ENDAT_INTERFACE_H
#define UZ_ENDAT_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enumeration of the EnDat MODE commands
 *
 */
enum mode_commands_t {
    send_position=7U
};

/**
 * @brief Data type for object uz_endat_interface
 *
 */
typedef struct uz_endat_interface_t uz_endat_interface_t;

/**
 * @brief Configuration struct for uz_endat_interface
 *
 */
struct uz_endat_interface_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    uint32_t endat_clk_frequency_Hz; /**< Clock frequency for the serial communication clock, values between 80 kHz and 2.5 MHz are allowed */
    uint32_t endat_encoder_bit_width_single_turn;/**< Number of single-turn position bits of the endat encoder, values up to 25 are allowed. Note that the sum of all bit widths (single-turn, multi-turn, and status) have to be less or equal than 64 */
    uint32_t endat_encoder_bit_width_multi_turn;/**< Number of multi-turn position bits of the endat encoder, values up to 25 are allowed */
    uint32_t endat_encoder_number_of_CRC_bits;/**< Number of CRC bits of the endat encoder, endat standard defines 5 bits */
    uint32_t machine_polepairs; /**< Pole pairs of the machine, only positive values >=1 are allowed */
    float sampling_interval_seconds; /**< Sampling interval for the integration employed in the PLL for speed calculation */
    float kp_pll; /**< Proportional gain for the PI within the PLL */
    float ki_pll; /**< Integral gain for the PI within the PLL */
    float position_mech_offset_si_single_turn; /**< Mechanical encoder offset between encoder zero and magnetic zero of the electric machine. Limited to -7.999 ... 7.999 */
};

/**
 * @brief Initializes an instance of the uz_endat_interface driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_endat_interface_t* uz_endat_interface_init(struct uz_endat_interface_config_t config);

/**
 * @brief Writes the config from the struct into the IP-Core
 *
 * @param self Pointer to the instance
 */
void uz_endat_interface_set_config(uz_endat_interface_t *self);

uint32_t uz_endat_interface_get_position_raw_single_turn(uz_endat_interface_t *self);
uint32_t uz_endat_interface_get_position_raw_multi_turn(uz_endat_interface_t *self);
uint32_t uz_endat_interface_get_position_multi_turn(uz_endat_interface_t *self);
float uz_endat_interface_get_position_mech_si_single_turn(uz_endat_interface_t *self);
float uz_endat_interface_get_position_el_si_single_turn(uz_endat_interface_t *self); 
float uz_endat_interface_get_speed_mech_si(uz_endat_interface_t *self);
float uz_endat_interface_get_speed_el_si(uz_endat_interface_t *self);
float uz_endat_interface_get_speed_mech_rpm(uz_endat_interface_t *self);

/**
 * @brief Enables the IP core, i.e., starting the endat transactions.
 * @brief The IP core is designed the way that no matter when you turn it on or off the, 
 * @brief it will perform enabling or disabling only when there is no endat transaction happening.
 *
 * @param self Pointer to the instance
 * @param ip_core_off_on Flag to enable the IP core, false=off, true=enabled
 */
void uz_endat_interface_enable_ip(uz_endat_interface_t *self, bool ip_core_off_on);

/**
 * @brief Writes the MODE command to the IP-core, that will be sent to the encoder.
 *
 * @param self Pointer to the instance
 * @param MODE command
 */
void uz_endat_interface_set_mode_command(uz_endat_interface_t *self, uint32_t mode_command);

/**
 * @brief Sets a new mechanical offset value for the single-turn position 
 * @brief Values between -7.999 ... 7.999 are allowed
 *
 * @param self Pointer to the instance
 * @param position_mech_offset_si_single_turn Mechanical encoder offset between encoder zero and magnetic zero of the electric machine 
 */
void uz_endat_interface_set_mechanical_offset_endat_single_turn(uz_endat_interface_t *self, float position_mech_offset_si_single_turn);


#endif // UZ_ENDAT_INTERFACE_H
