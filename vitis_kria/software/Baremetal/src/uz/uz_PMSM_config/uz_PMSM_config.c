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