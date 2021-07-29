#include "uz_linear_decoupling.h"

struct uz_dq_t uz_FOC_linear_decoupling(struct uz_dq_t i_dq_meas_Ampere, uz_lin_decoupling_config config, float omega_el_rad_per_sec){
    uz_assert(config.Ld_Henry > 0.0f);
	uz_assert(config.Lq_Henry > 0.0f);
	uz_assert(config.Psi_PM_Vs > 0.0f);
	struct uz_dq_t u_dq_vor_Volts;
	u_dq_vor_Volts.d = i_dq_meas_Ampere.q * -1.0f * config.Lq_Henry * omega_el_rad_per_sec;
	u_dq_vor_Volts.q = (i_dq_meas_Ampere.d* config.Ld_Henry + config.Psi_PM_Vs) * omega_el_rad_per_sec;
	return (u_dq_vor_Volts);
}