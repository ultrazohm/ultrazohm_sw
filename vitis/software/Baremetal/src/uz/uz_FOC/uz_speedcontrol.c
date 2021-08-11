#include "uz_speedcontrol.h"

uz_PI_Controller* uz_SpeedControl_init(struct uz_PI_Controller_config config){
    uz_PI_Controller* self = uz_PI_Controller_init(config);
    return(self);
}

struct uz_dq_t uz_SpeedControl_sample(uz_PI_Controller* self, float omega_el_rad_per_sec, float n_ref_rpm,  float id_ref_Ampere, float polePairs, bool ext_clamping){
    uz_assert(polePairs > 0.0f);
	uz_assert(fmodf(polePairs, 1.0f) == 0);
    struct uz_dq_t i_output_Ampere = {0};
	float omega_el_ref_rad_per_sec = (n_ref_rpm * 2.0f * M_PI * polePairs) / 60.0f;
	i_output_Ampere.q = uz_PI_Controller_sample(self, omega_el_ref_rad_per_sec, omega_el_rad_per_sec, ext_clamping);
    i_output_Ampere.d = id_ref_Ampere;
    return(i_output_Ampere);
}

void uz_SpeedControl_reset(uz_PI_Controller* self){
	uz_PI_Controller_reset(self);
}
