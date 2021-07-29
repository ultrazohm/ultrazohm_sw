#include "uz_space_vector_limitation.h"
#include "../uz_HAL.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_signals/uz_signals.h"

struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_dq_ref_Volts, float U_zk_Volts, float omega_el_rad_per_sec, struct uz_dq_t i_dq_meas_Ampere, bool* ext_clamping){
	uz_assert_not_NULL(ext_clamping);
	uz_assert(U_zk_Volts > 0.0f);
	*ext_clamping = false;
	struct uz_dq_t u_dq_limit_Volts = {0};

  	float U_RZ_max =U_zk_Volts / sqrtf(3.0f);
	float U_RZ_betrag = sqrtf(u_dq_ref_Volts.d * u_dq_ref_Volts.d + u_dq_ref_Volts.q * u_dq_ref_Volts.q);

	if ( U_RZ_betrag > U_RZ_max ){
		*ext_clamping = true;
		if ((uz_signals_get_sign_of_value(omega_el_rad_per_sec) == uz_signals_get_sign_of_value(i_dq_meas_Ampere.q))) {
			if ((fabsf(u_dq_ref_Volts.d) > 0.95f * U_RZ_max)) {
				u_dq_limit_Volts.d = uz_signals_get_sign_of_value(u_dq_ref_Volts.d) * 0.95f * U_RZ_max;
				u_dq_limit_Volts.q = uz_signals_get_sign_of_value(u_dq_ref_Volts.q) * sqrtf( (U_RZ_max * U_RZ_max) - (u_dq_limit_Volts.d * u_dq_limit_Volts.d) );
			} else {
				u_dq_limit_Volts.d = u_dq_ref_Volts.d;
				u_dq_limit_Volts.q = uz_signals_get_sign_of_value(u_dq_ref_Volts.q) * sqrtf( (U_RZ_max * U_RZ_max) - (u_dq_limit_Volts.d * u_dq_limit_Volts.d) );
			}


	     } else if ((uz_signals_get_sign_of_value(omega_el_rad_per_sec) != uz_signals_get_sign_of_value(i_dq_meas_Ampere.q))) {
			if (fabsf(u_dq_ref_Volts.q) > 0.95f * U_RZ_max) {
				u_dq_limit_Volts.q = uz_signals_get_sign_of_value(u_dq_ref_Volts.q) * 0.95f * U_RZ_max;
				u_dq_limit_Volts.d = uz_signals_get_sign_of_value(u_dq_ref_Volts.d) * sqrtf((U_RZ_max * U_RZ_max) - (u_dq_limit_Volts.q * u_dq_limit_Volts.q));
			} else {
				u_dq_limit_Volts.q = u_dq_ref_Volts.q;
				u_dq_limit_Volts.d = uz_signals_get_sign_of_value(u_dq_ref_Volts.d) * sqrtf((U_RZ_max * U_RZ_max) - (u_dq_limit_Volts.q * u_dq_limit_Volts.q));
			}
		} else {
			u_dq_limit_Volts.d = 0.0f;
			u_dq_limit_Volts.q = 0.0f;
		}

	} else {
		u_dq_limit_Volts.d = u_dq_ref_Volts.d;
		u_dq_limit_Volts.q = u_dq_ref_Volts.q;
		*ext_clamping = false;
	}
	return (u_dq_limit_Volts);
}
