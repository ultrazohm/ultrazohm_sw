#include "uz_speedcontrol.h"

static struct uz_dq_t uz_SpeedControl_field_weakening(struct uz_PMSM_t config, float omega_el_rad_per_sec, float U_zk_Volts, bool* fw_flag);
static float uz_SpeedControl_decide_id_ref(float id_ref_Ampere, float id_field_weakening_Ampere, bool fw_flag);
static float uz_SpeedControl_calculate_omega_cut(struct uz_PMSM_t config, float U_SV_max);
static struct uz_dq_t uz_SpeedControl_calculate_fw_currents(struct uz_PMSM_t config, float omega_el_rad_per_sec, float omega_cut, float U_SV_max);

uz_PI_Controller* uz_SpeedControl_init(struct uz_PI_Controller_config config){
    uz_PI_Controller* self = uz_PI_Controller_init(config);
    return(self);
}

struct uz_dq_t uz_SpeedControl_sample(uz_PI_Controller* self, float omega_el_rad_per_sec, float n_ref_rpm, float U_zk_Volts, float id_ref_Ampere, struct uz_PMSM_t config, bool ext_clamping){
    uz_assert(config.polePairs > 0.0f);
	uz_assert(fmodf(config.polePairs, 1.0f) == 0);
    bool fw_flag = false;
    struct uz_dq_t i_output_Ampere = {0};
	float omega_el_ref_rad_per_sec = (n_ref_rpm * 2.0f * M_PI * config.polePairs) / 60.0f;
    struct uz_dq_t i_field_weakening_Ampere = uz_SpeedControl_field_weakening(config, omega_el_rad_per_sec, U_zk_Volts, &fw_flag);
    uz_PI_Controller_update_limits(self, i_field_weakening_Ampere.q, -i_field_weakening_Ampere.q);
	i_output_Ampere.d = uz_SpeedControl_decide_id_ref(id_ref_Ampere, i_field_weakening_Ampere.d, fw_flag);
    i_output_Ampere.q = uz_PI_Controller_sample(self, omega_el_ref_rad_per_sec, omega_el_rad_per_sec, ext_clamping);
    return(i_output_Ampere);
}

void uz_SpeedControl_reset(uz_PI_Controller* self){
	uz_PI_Controller_reset(self);
}

static struct uz_dq_t uz_SpeedControl_field_weakening(struct uz_PMSM_t config, float omega_el_rad_per_sec, float U_zk_Volts, bool* fw_flag){
    struct uz_dq_t output = {0};
    float U_SV_max =(U_zk_Volts / sqrtf(3.0f) ) * 0.95f;
	float omega_cut = uz_SpeedControl_calculate_omega_cut(config, U_SV_max);
    if (omega_el_rad_per_sec > omega_cut) {
        *fw_flag = true;
        output = uz_SpeedControl_calculate_fw_currents(config, omega_el_rad_per_sec, omega_cut, U_SV_max);
    } else {
	    *fw_flag = false;
        output.d = 0.0f;
        output.q = config.I_max_Ampere;
    }
        
    return(output);
}

static float uz_SpeedControl_decide_id_ref(float id_ref_Ampere, float id_field_weakening_Ampere, bool fw_flag){
    float output = 0.0f;
    bool id_ref_smaller_than_id_fw = id_ref_Ampere <= id_field_weakening_Ampere;
    if(fw_flag == false){
	    output = id_ref_Ampere;
	} else if ( (fw_flag == true) && (id_ref_smaller_than_id_fw == true) ) {
		output = id_ref_Ampere;
    }else{
	    output = id_field_weakening_Ampere;
    }
    return(output);
}

static float uz_SpeedControl_calculate_omega_cut(struct uz_PMSM_t config, float U_SV_max) {
    float a_omega = (powf(config.I_max_Ampere, 2.0f) * powf(config.Lq_Henry, 2.0f) ) + powf(config.Psi_PM_Vs, 2.0f);
    float b_omega = 2.0f * config.R_ph_Ohm * config.Psi_PM_Vs * config.I_max_Ampere;
    float c_omega = (powf(config.I_max_Ampere, 2.0f) * powf(config.R_ph_Ohm, 2.0f) ) - powf(U_SV_max, 2.0f);
    float omega_cut = (-b_omega + sqrtf(powf(b_omega, 2.0f) - (4 * a_omega * c_omega) )) / (2 * a_omega);
	return (omega_cut);
}

static struct uz_dq_t uz_SpeedControl_calculate_fw_currents(struct uz_PMSM_t config, float omega_el_rad_per_sec, float omega_cut, float U_SV_max) {
    uz_assert(omega_cut > 0.0f);
    struct uz_dq_t output = {0};
    output.d = (config.Psi_PM_Vs / config.Ld_Henry) * ( (omega_cut / omega_el_rad_per_sec) - 1.0f);
    if (output.d < (-config.I_max_Ampere)){
        output.d = -config.I_max_Ampere;
    }
    float iq_max = sqrtf(powf(config.I_max_Ampere, 2.0f) - powf(output.d, 2.0f));
    float a_iq_fw = (powf(omega_el_rad_per_sec, 2.0f) * powf(config.Lq_Henry, 2.0f) ) + powf(config.R_ph_Ohm, 2.0f);
    float b_iq_fw = 2.0f * config.R_ph_Ohm * config.Psi_PM_Vs * omega_el_rad_per_sec;
    float c_iq_fw = (powf(output.d, 2.0f) * powf(config.R_ph_Ohm, 2.0f) ) +
    (powf(omega_el_rad_per_sec, 2.0f) * (powf(config.Psi_PM_Vs, 2.0f) + (powf(config.Ld_Henry, 2.0f) * powf(output.d, 2.0f)) + (2.0f * config.Psi_PM_Vs * config.Ld_Henry * output.d))) - powf(U_SV_max, 2.0f);
   	output.q = (-b_iq_fw + sqrtf(powf(b_iq_fw, 2.0f) - (4 * a_iq_fw * c_iq_fw) )) / (2 * a_iq_fw);
    if(output.q > iq_max) {
        output.q = iq_max;
    }
    return(output);
}
