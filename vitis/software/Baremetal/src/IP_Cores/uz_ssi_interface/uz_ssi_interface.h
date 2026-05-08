#ifndef UZ_SSI_INTERFACE_H
#define UZ_SSI_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enumeration of the encoding configurations for the SSI position information
 *
 */
typedef enum uz_ssi_interface_position_encoding_t {
    uz_ssi_interface_binary = 0,
    uz_ssi_interface_gray_code
} uz_ssi_interface_position_encoding_t;

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
    uint32_t base_address; /**< Base address of the IP core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP core */
    uint32_t ssi_clk_frequency_Hz; /**< Clock frequency for the serial communication clock, values between 80 kHz and 2.5 MHz are allowed */
    uint32_t ssi_encoder_bit_width_single_turn;/**< Number of single-turn position bits of the SSI encoder, values from 1 to 31 are allowed. Note that the sum of all bit widths (single-turn, multi-turn, and status) has to be less than or equal to 64 */
    uint32_t ssi_encoder_bit_width_multi_turn;/**< Number of multi-turn position bits of the SSI encoder, values from 0 to 31 are allowed. Note that the sum of all bit widths (single-turn, multi-turn, and status) has to be less than or equal to 64 */
    uint32_t ssi_encoder_number_of_status_bits;/**< Number of status bits of the SSI encoder, values up to 32 are allowed. Note that the sum of all bit widths (single-turn, multi-turn, and status) has to be less than or equal to 64 */
    uz_ssi_interface_position_encoding_t position_encoding;/**< Selects whether the SSI encoder position data is encoded as binary or gray code */
    uint32_t machine_polepairs; /**< Pole pairs of the machine, only positive values >=1 are allowed */
    uint32_t sampling_delay_clk_ticks;/**< Delay of the serial data input sampling in IP core clock ticks, values from 0 to 100 are allowed */
    float sampling_interval_seconds; /**< Sampling interval for the integration employed in the PLL for speed calculation */
    float kp_pll; /**< Proportional gain for the PI within the PLL */
    float ki_pll; /**< Integral gain for the PI within the PLL */
    float position_mech_offset_si_single_turn; /**< Mechanical encoder offset between encoder zero and magnetic zero of the electric machine. Limited to -2*pi ... 2*pi and to values that fit into int32_t after conversion to encoder ticks */
};

/**
 * @brief Initializes an instance of the uz_ssi_interface driver
 *
 * @param config Configuration values for the IP core
 * @return Pointer to initialized instance
 */
uz_ssi_interface_t* uz_ssi_interface_init(struct uz_ssi_interface_config_t config);

/**
 * @brief Returns the raw single-turn position read from the SSI encoder.
 *
 * @param self Pointer to the instance
 * @return Raw single-turn position in encoder ticks
 */
uint32_t uz_ssi_interface_get_position_raw_single_turn(uz_ssi_interface_t *self);

/**
 * @brief Returns the raw multi-turn position read from the SSI encoder.
 *
 * @param self Pointer to the instance
 * @return Raw multi-turn position in encoder turns
 */
uint32_t uz_ssi_interface_get_position_raw_multi_turn(uz_ssi_interface_t *self);

/**
 * @brief Returns the offset-corrected multi-turn position from the IP core.
 *
 * @param self Pointer to the instance
 * @return Offset-corrected revolution counter that increments aligned with the full revolution wrap of the single-turn position
 */
uint32_t uz_ssi_interface_get_position_multi_turn(uz_ssi_interface_t *self);

/**
 * @brief Returns the mechanical single-turn position in SI units.
 *
 * @param self Pointer to the instance
 * @return Mechanical single-turn position in rad
 */
float uz_ssi_interface_get_position_mech_si_single_turn(uz_ssi_interface_t *self);

/**
 * @brief Returns the electrical single-turn position in SI units.
 *
 * @param self Pointer to the instance
 * @return Electrical single-turn position in rad
 */
float uz_ssi_interface_get_position_el_si_single_turn(uz_ssi_interface_t *self); 

/**
 * @brief Returns the mechanical speed in SI units.
 *
 * @param self Pointer to the instance
 * @return Mechanical speed in rad/s
 */
float uz_ssi_interface_get_speed_mech_si(uz_ssi_interface_t *self);

/**
 * @brief Returns the electrical speed in SI units.
 *
 * @param self Pointer to the instance
 * @return Electrical speed in rad/s
 */
float uz_ssi_interface_get_speed_el_si(uz_ssi_interface_t *self);

/**
 * @brief Returns the mechanical speed in revolutions per minute.
 *
 * @param self Pointer to the instance
 * @return Mechanical speed in rpm
 */
float uz_ssi_interface_get_speed_mech_rpm(uz_ssi_interface_t *self);

/**
 * @brief Returns the raw status bits read from the SSI encoder.
 *
 * @param self Pointer to the instance
 * @return Raw SSI encoder status bits
 */
uint32_t uz_ssi_interface_get_encoder_status(uz_ssi_interface_t *self);

/**
 * @brief Enables the IP core, i.e., starting the SSI transactions.
 * @brief The IP core is designed the way that no matter when you turn it on or off,
 * @brief it will perform enabling or disabling only when there is no SSI transaction happening.
 *
 * @param self Pointer to the instance
 * @param ip_core_off_on Flag to enable the IP core, false=off, true=enabled
 */
void uz_ssi_interface_enable_ip(uz_ssi_interface_t *self, bool ip_core_off_on);

/**
 * @brief Sets a new mechanical offset value for the single-turn position 
 * @brief Values between -2*pi ... 2*pi are allowed if the converted encoder tick value fits into int32_t
 *
 * @param self Pointer to the instance
 * @param position_mech_offset_si_single_turn Mechanical encoder offset between encoder zero and magnetic zero of the electric machine 
 */
void uz_ssi_interface_set_mechanical_offset_ssi_single_turn(uz_ssi_interface_t *self, float position_mech_offset_si_single_turn);

/**
 * @brief Sets the sampling delay of the serial data input in IP core clock ticks.
 * @brief Values between 0 and 100 are allowed.
 *
 * @param self Pointer to the instance
 * @param delay_clk_ticks Sampling delay in IP core clock ticks
 */
void uz_ssi_interface_set_sampling_delay_clk_ticks(uz_ssi_interface_t *self, uint32_t delay_clk_ticks);

/**
 * @brief Enables or disables the PLL debug mode.
 * @brief If enabled, the speed PLL uses the debug position instead of the encoder-derived mechanical position.
 *
 * @param self Pointer to the instance
 * @param debug_on_off Flag to enable the PLL debug mode, false=off, true=enabled
 */
void uz_ssi_interface_enable_pll_debug_mode(uz_ssi_interface_t *self, bool debug_on_off);

/**
 * @brief Sets the mechanical position used as debug input for the speed PLL.
 * @brief Values between 0 and 2*pi are allowed.
 *
 * @param self Pointer to the instance
 * @param position_mech_si Mechanical debug position in rad
 */
void uz_ssi_interface_set_pll_debug_position(uz_ssi_interface_t *self, float position_mech_si);

#endif // UZ_SSI_INTERFACE_H
