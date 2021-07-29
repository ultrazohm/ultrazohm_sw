#include "uz_FOC.h"
#include "../uz_global_configuration.h"
typedef struct uz_FOC {
	bool is_ready;
	bool ext_clamping;
	struct uz_FOC_config config_FOC;
	struct uz_lin_decoupling_config config_lin_Decoup;
	struct uz_PI_Controller* Controller_id;
	struct uz_PI_Controller* Controller_iq;
	struct uz_PI_Controller* Controller_n;
}uz_FOC;

static struct uz_dq_t uz_FOC_CurrentControl(uz_FOC* self, uz_FOC_ActualValues values);
static struct uz_dq_t uz_FOC_SpeedControl(uz_FOC* self, uz_FOC_ActualValues values);
static size_t instances_counter_FOC = 0;

static uz_FOC instances_FOC[UZ_FOC_MAX_INSTANCES] = {0};


/**
 * @brief Memory allocation of the uz_FOC struct
 *
 * @return Pointer to uz_FOC instance
 */
static uz_FOC* uz_FOC_allocation(void);

static uz_FOC* uz_FOC_allocation(void) {
	uz_assert(instances_counter_FOC < UZ_FOC_MAX_INSTANCES);
	uz_FOC* self = &instances_FOC[instances_counter_FOC];
	uz_assert(self->is_ready == false);
	instances_counter_FOC++;
	self->is_ready = true;
	return (self);
}

uz_FOC* uz_FOC_init(uz_FOC_config config_FOC, uz_PI_Controller_config config_id, uz_PI_Controller_config config_iq, uz_PI_Controller_config config_n, uz_lin_decoupling_config config_lin_Decoup){
	uz_FOC* self = uz_FOC_allocation();
	uz_assert(config_FOC.polePairs > 0.0f);
	uz_assert(config_FOC.FOC_Select >= 1U && config_FOC.FOC_Select <= 2U);

	if (config_FOC.FOC_Select == 2U) {
		self->Controller_n = uz_PI_Controller_init(config_n);
	}else{
		config_n.Ki = 0.0f;
		config_n.Kp = 0.0f;
		config_n.lower_limit = 0.0f;
		config_n.upper_limit = 0.0f;
		config_n.samplingTime_sec = 0.0f;
	}
	self->Controller_id = uz_PI_Controller_init(config_id);
	self->Controller_iq = uz_PI_Controller_init(config_iq);
	self->config_FOC = config_FOC;
	self->config_lin_Decoup = config_lin_Decoup;
	return (self);
}

struct uz_dq_t uz_FOC_sample(uz_FOC* self, uz_FOC_ActualValues values) {
	struct uz_dq_t u_dq_ref_Volts = { 0 };
	if (self->config_FOC.FOC_Select == 1U) {
		u_dq_ref_Volts = uz_FOC_CurrentControl(self, values);
	} else if (self->config_FOC.FOC_Select == 2U) {
		u_dq_ref_Volts = uz_FOC_SpeedControl(self, values);
	} else {
		u_dq_ref_Volts.d = 0.0f;
		u_dq_ref_Volts.q = 0.0f;
	}
	struct uz_dq_t u_dq_vor_Volts = uz_FOC_linear_decoupling(values.i_dq_meas_Ampere, self->config_lin_Decoup, values.omega_el_rad_per_sec);
	u_dq_ref_Volts.d = u_dq_ref_Volts.d + u_dq_vor_Volts.d;
	u_dq_ref_Volts.q = u_dq_ref_Volts.q + u_dq_vor_Volts.q;
	struct uz_dq_t u_dq_limit_Volts = uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts, values.U_zk_Volts, values.omega_el_rad_per_sec, values.i_dq_meas_Ampere, &self->ext_clamping);
	return (u_dq_limit_Volts);
}

struct uz_dq_t uz_FOC_CurrentControl(uz_FOC* self, uz_FOC_ActualValues values) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	struct uz_dq_t u_dq_ref_Volts = { 0 };
	u_dq_ref_Volts.q = uz_PI_Controller_sample(self->Controller_iq, self->config_FOC.iq_ref_Ampere, values.i_dq_meas_Ampere.q, self->ext_clamping);
	u_dq_ref_Volts.d = uz_PI_Controller_sample(self->Controller_id, self->config_FOC.id_ref_Ampere, values.i_dq_meas_Ampere.d, self->ext_clamping);
	return (u_dq_ref_Volts);

}

struct uz_dq_t uz_FOC_SpeedControl(uz_FOC* self, uz_FOC_ActualValues values) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	struct uz_dq_t u_dq_ref_Volts = { .d = 0.0f, .q = 0.0f, .zero = 0.0f };
	float omega_el_ref_rad_per_sec = (self->config_FOC.n_ref_rpm * 2.0f * M_PI * self->config_FOC.polePairs) / 60.0f;
	self->config_FOC.iq_ref_Ampere = uz_PI_Controller_sample(self->Controller_n, omega_el_ref_rad_per_sec, values.omega_el_rad_per_sec, self->ext_clamping);
	u_dq_ref_Volts = uz_FOC_CurrentControl(self, values);
	return (u_dq_ref_Volts);
}

