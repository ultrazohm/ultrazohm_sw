#ifndef UZ_POS_TO_SPEED_PLL_H
#define UZ_POS_TO_SPEED_PLL_H

/**
 * @brief Configuration struct for uz_pos_to_speed_pll.
 */
struct uz_pos_to_speed_pll_config_t {
    float machine_polepairs;            /**< Number of pole pairs of the electric machine. Has to be greater than 0.0f */
    float kp_pll;                       /**< Proportional gain for the PLL */
    float ki_pll;                       /**< Integral gain for the PLL */
    float sampling_time_in_seconds;     /**< Integration step time for the PLL. Has to be greater than 0.0f */
};


/**
 * @brief Struct definition for uz_pos_to_speed_pll
 *
 */
typedef struct uz_pos_to_speed_pll_t uz_pos_to_speed_pll_t;

/**
 * @brief init function for the position to speed PLL
 * @param config struct uz_pos_to_speed_pll_config
 *
 * @return pointer to the instance
 *
 */
uz_pos_to_speed_pll_t* uz_pos_to_speed_pll_init(struct uz_pos_to_speed_pll_config_t config);


/**
 * @brief set function for writing the config parameters to the instance
 * @param pointer to the instance
 * @param config struct
 *
 */
void uz_pos_to_speed_pll_set_config(uz_pos_to_speed_pll_t* self, struct uz_pos_to_speed_pll_config_t config);


/**
 * @brief step function. Call periodically in the ISR
 * @param pointer to the instance
 * @param mechanical position input value in rad, e.g. from a position encoder, Has to be between 0...2*PI
 *
 */
void uz_pos_to_speed_pll_step(uz_pos_to_speed_pll_t* self, float position_mech_si);


/**
 * @brief get function for the mechanical speed
 * @param pointer to the instance
 *
 * @return mechanical speed in rad per second
 */
float uz_pos_to_speed_pll_get_omega_mech_si(uz_pos_to_speed_pll_t* self);


/**
 * @brief get function for the electrical speed
 * @param pointer to the instance
 *
 * @return electrical speed in rad per second. This value is calculated by multiplying the mechanical speed with the polepairs value from the config struct
 */
float uz_pos_to_speed_pll_get_omega_el_si(uz_pos_to_speed_pll_t* self);

#endif // UZ_POS_TO_SPEED_PLL_H
