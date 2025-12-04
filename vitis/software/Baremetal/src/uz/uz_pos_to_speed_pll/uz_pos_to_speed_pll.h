#ifndef UZ_POS_TO_SPEED_PLL_H
#define UZ_POS_TO_SPEED_PLL_H

struct uz_pos_to_speed_pll_config_t {
    float machine_polepairs; /**< Number of pole pairs of the electric machine */
    float kp_pll; /**< Proportional gain for the PLL */
    float ki_pll; /**< Integral gain for the PLL */
    float sampling_time_in_seconds; /**< Integration step time for the PLL */
};

typedef struct uz_pos_to_speed_pll_t uz_pos_to_speed_pll_t;
uz_pos_to_speed_pll_t* uz_pos_to_speed_pll_init(struct uz_pos_to_speed_pll_config_t config);

void uz_pos_to_speed_pll_set_config(uz_pos_to_speed_pll_t* self, struct uz_pos_to_speed_pll_config_t config);

void uz_pos_to_speed_pll_step(uz_pos_to_speed_pll_t* self, float position_mech_si);

float uz_pos_to_speed_pll_get_omega_mech_si(uz_pos_to_speed_pll_t* self);

float uz_pos_to_speed_pll_get_omega_el_si(uz_pos_to_speed_pll_t* self);

#endif // UZ_POS_TO_SPEED_PLL_H
