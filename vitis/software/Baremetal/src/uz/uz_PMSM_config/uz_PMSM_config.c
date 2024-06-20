#include "uz_PMSM_config.h"
#include "../uz_HAL.h"

void uz_PMSM_config_assert(uz_PMSM_t config){
    uz_assert(config.R_ph_Ohm > 0.0f);
    uz_assert(config.Ld_Henry > 0.0f);
	uz_assert(config.Lq_Henry > 0.0f);
	uz_assert(config.Psi_PM_Vs >= 0.0f);
    uz_assert(config.polePairs > 0.0f);
	uz_assert(fmodf(config.polePairs, 1.0f) == 0);
    uz_assert(config.J_kg_m_squared > 0.0f);
    uz_assert(config.I_max_Ampere > 0.0f);
}

void uz_PMSM_flux_fitting_parameter_config_assert(uz_PMSM_flux_fitting_parameter_config_t fitting_config){
    uz_assert(fitting_config.ad1_parameter != 0.0f);
    uz_assert(fitting_config.ad2_parameter != 0.0f);
	uz_assert(fitting_config.ad3_parameter != 0.0f);
	uz_assert(fitting_config.ad4_parameter != 0.0f);
    uz_assert(fitting_config.ad5_parameter != 0.0f);
    uz_assert(fitting_config.ad6_parameter != 0.0f);
    uz_assert(fitting_config.aq1_parameter != 0.0f);
    uz_assert(fitting_config.aq2_parameter != 0.0f);
    uz_assert(fitting_config.aq3_parameter != 0.0f);
    uz_assert(fitting_config.aq4_parameter != 0.0f);
    uz_assert(fitting_config.aq5_parameter != 0.0f);
    uz_assert(fitting_config.aq6_parameter != 0.0f);
    uz_assert(fitting_config.F1G1_parameter != 0.0f);
    uz_assert(fitting_config.F2G2_parameter != 0.0f);
}