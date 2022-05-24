#ifndef UZ_INCREMENTALENCODER_H
#define UZ_INCREMENTALENCODER_H
#include <stdint.h>

/**
 * @brief Object data type definition of the incremental encoder IP-Core driver
 * 
 */
typedef struct uz_incrementalEncoder_t uz_incrementalEncoder_t;


/**
 * @brief Configuration struct for the encoder driver
 * 
 */
struct uz_incrementalEncoder_config{
    uint32_t base_address; /**< Base address of IP-Core instance */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    uint32_t line_number_per_turn_mech; /**< Number of lines eper one mechanical turn of the attached encoder */
    float OmegaPerOverSample_in_rpm; /**< Rotational speed omega in 1/min after which the OverSamplingFactor is increased by one */
    uint32_t drive_pole_pair; /**< Number of pole pairs of the electric drive that is attached to the encoder. Set to zero if no drive is attached or increments per mechanical turn is not an integer multiple of pole pairs */
    uint32_t speed_timeout_in_ms; /**< When no edge is detected for this amount of time in milliseconds, the speed is set zero. Typical: 10ms*/
};

/**
 * @brief Initialization of one instance of the driver for the incremental encoder IP-Core
 * 
 * @param config 
 * @return uz_incrementalEncoder_t* 
 */
uz_incrementalEncoder_t* uz_incrementalEncoder_init(struct uz_incrementalEncoder_config config);

uz_incrementalEncoder_t* uz_incrementalEncoder_init_v25(struct uz_incrementalEncoder_config config);

/**
 * @brief Returns the measured omega based on counting edges of the A-lane in 1/s.
 * 
 * @param self 
 * @return float 
 */
float uz_incrementalEncoder_get_omega_mech(uz_incrementalEncoder_t* self);

/**
 * @brief Returns the measured electrical angle in 0..2pi range if drive_pole_pair is not zero in the config.
 * 
 * @param self 
 * @return float 
 */
float uz_incrementalEncoder_get_omega_mech_OS_N4(uz_incrementalEncoder_t* self);

/**
 * @brief Returns the measured electrical angle in 0..2pi range if drive_pole_pair is not zero in the config.
 *
 * @param self
 * @return float
 */
float uz_incrementalEncoder_get_omega_mech_OS_N8(uz_incrementalEncoder_t* self);
float uz_incrementalEncoder_get_omegaB(uz_incrementalEncoder_t* self);
float uz_incrementalEncoder_get_omegaNOTB(uz_incrementalEncoder_t* self);
float uz_incrementalEncoder_get_omegaA(uz_incrementalEncoder_t* self);
float uz_incrementalEncoder_get_omegaNOTA(uz_incrementalEncoder_t* self);


/**
 * @brief Returns the measured electrical angle in 0..2pi range if drive_pole_pair is not zero in the config.
 *
 * @param self
 * @return float
 */
float uz_incrementalEncoder_get_theta_el(uz_incrementalEncoder_t* self);

/**
 * @brief Returns the measured mechanical angle in 0..increments.
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t uz_incrementalEncoder_get_position(uz_incrementalEncoder_t* self);

#endif // UZ_INCREMENTALENCODER_H
