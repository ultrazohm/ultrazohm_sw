#ifndef UZ_RESOLVER_PL_INTERFACE_H
#define UZ_RESOLVER_PL_INTERFACE_H
#include <stdint.h>

// Datasheet values of AD2S1210 needed fpr internal calculations of the IP-Core
// Maximum representable rounds per second according to resolver resolution setting
#define RPS_MAX_16BIT  125U
#define RPS_MAX_14BIT  500U
#define RPS_MAX_12BIT 1000U
#define RPS_MAX_10BIT 2500U
// Calculation factor for results in rounds per second from raw value
#define BIT_TO_RPS_FACTOR_16BIT (float)(RPS_MAX_16BIT/(2^(16-1)))
#define BIT_TO_RPS_FACTOR_14BIT (float)(RPS_MAX_14BIT/(2^(14-1)))
#define BIT_TO_RPS_FACTOR_12BIT (float)(RPS_MAX_12BIT/(2^(12-1)))
#define BIT_TO_RPS_FACTOR_10BIT (float)(RPS_MAX_10BIT/(2^(10-1)))

/**
 * @brief Data type for object uz_resolver_pl_interface
 *
 */
typedef struct uz_resolver_pl_interface_t uz_resolver_pl_interface_t;

/**
 * @brief Configuration struct for uz_resolver_pl_interface
 *
 */
struct uz_resolver_pl_interface_config_t {
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    int32_t resolver_polepairs; /**< Polepairs of the resolver, only positive values >=1 are allowed */
    int32_t machine_polepairs; /**< Polepairs of the machine, only positive values >=1 are allowed */
    int32_t position_intmax; /**< Maximum representable int value for selected bit resolution, e.g. 2^16=65525 for 16bit resolution */
    float bitToRPS_factor; /**< value for calculating velocity raw value of resolverIP int rounds per second */
    float theta_m_offset_rad; /**< mechanical angle offset in rad between machine angle zero and resolver angle zero, only values <=0.0f & >=-2pi allowed */
};

/**
 * @brief Output struct for uz_resolver_pl_interface
 *
 */
struct uz_resolver_pl_interface_outputs_t {
    int32_t revolution_counter; /**< Not needed in regular operation, internal counter of the IP-Core, that is used to calculate correct electrical and mechanical angles if polepairs of resolver and machine result in a fractional rational number */
    float position_mech_2pi; /**< mechanical angle in rad, ranging from 0..2pi */
    float position_el_2pi; /**< electrical angle in rad, ranging from 0..2pi */
    float omega_mech_rad_s; /**< mechanical speed in rad per second */
    float n_mech_rpm; /**< mechanical speed in min^(-1) */
};

/**
 * @brief Initializes an instance of the uz_resolver_pl_interface driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_resolver_pl_interface_t* uz_resolver_pl_interface_init(struct uz_resolver_pl_interface_config_t config, struct uz_resolver_pl_interface_outputs_t outputs);

/**
 * @brief Writes the config from the struct into the IP-Core
 *
 * @param self Pointer to the instance
 */
void uz_resolver_pl_interface_set_config(uz_resolver_pl_interface_t *self);

/**
 * @brief Updates and returns the AXI outputs of the IP-Core
 *
 * @param self Pointer to the instance
 */
struct uz_resolver_pl_interface_outputs_t uz_resolver_pl_interface_get_outputs(uz_resolver_pl_interface_t *self);

/**
 * @brief Writes new theta_m_offset_rad value into config and into the IP-Core
 *
 * @param self Pointer to the instance
 * @param theta_m_offset_rad Mechanical angle offset in rad between machine angle zero and resolver angle zero, only values <=0.0f & >=-2pi allowed
 */
void uz_resolver_pl_interface_set_theta_m_offset_rad(uz_resolver_pl_interface_t *self, float theta_m_offset_rad);

/**
 * @brief Resets the internal revolution counter of the IP-Core, automatically done at init
 *
 * @param self Pointer to the instance
 */
void uz_resolver_pl_interface_reset(uz_resolver_pl_interface_t *self);

#endif // UZ_RESOLVER_PL_INTERFACE_H
