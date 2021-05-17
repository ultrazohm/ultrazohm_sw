#include "uz_FOC.h"
#define max_FOC_CurrentControl_instances 1
#define max_FOC_SpeedControl_instances 1

static size_t counter_FOC_CurrentControl = 0;
static size_t counter_FOC_SpeedControl = 0;

static uz_FOC_CurrentControl_parameters instances_FOC_CurrentControl[max_FOC_CurrentControl_instances] = { 0 };
static uz_FOC_SpeedControl_parameters instances_FOC_SpeedControl[max_FOC_SpeedControl_instances] = { 0 };

uz_FOC_CurrentControl_parameters* uz_FOC_CurrentControl_init(uz_FOC_CurrentControl_config config) {
	uz_assert(counter_FOC_CurrentControl < max_FOC_CurrentControl_instances);
	uz_FOC_CurrentControl_parameters* self = &instances_FOC_CurrentControl[counter_FOC_CurrentControl];
	uz_assert(self->is_ready == false);
	counter_FOC_CurrentControl += 1;
	self->is_ready = true;
	uz_assert(config.Rs_mOhm > 0);
	uz_assert(config.Ld_mH > 0);
	uz_assert(config.Lq_mH > 0);
	uz_assert(config.Psi_PM_mVs > 0);
	uz_assert(config.polePairs > 0);
	self->bandwith_Hz = 20000.0f; //Replace with function for ISR-frequency
	self->Kp_id = config.Ld_mH * self->bandwith_Hz;
	self->Tn_id = config.Ld_mH / config.Rs_mOhm;
	self->Kp_iq = config.Lq_mH * self->bandwith_Hz;
	self->Tn_iq = config.Lq_mH / config.Rs_mOhm;
	self->config = config;
	return (self);
}

uz_FOC_SpeedControl_parameters* uz_FOC_SpeedControl_init(uz_FOC_SpeedControl_config config) {
	uz_assert(counter_FOC_SpeedControl < max_FOC_SpeedControl_instances);
	uz_FOC_SpeedControl_parameters* self = &instances_FOC_SpeedControl[counter_FOC_SpeedControl];
	uz_assert(self->is_ready == false);
	counter_FOC_SpeedControl += 1;
	self->is_ready = true;
	uz_assert(config.Rs_mOhm > 0);
	uz_assert(config.Ld_mH > 0);
	uz_assert(config.Lq_mH > 0);
	uz_assert(config.Psi_PM_mVs > 0);
	uz_assert(config.polePairs > 0);
	uz_assert(config.dampingFactor > 0);
	uz_assert(config.rotorInertia > 0);
	uz_assert(config.n_target_rpm != 0);

	self->bandwith_Hz = 20000.0; //Replace with function for ISR-frequency
	self->Kp_id = config.Ld_mH * self->bandwith_Hz;
	self->Tn_id = config.Ld_mH / config.Rs_mOhm;
	self->Kp_iq = config.Lq_mH * self->bandwith_Hz;
	self->Tn_iq = config.Lq_mH / config.Rs_mOhm;
	self->Kp_n = self->Kp_iq / (config.Lq_mH * config.dampingFactor * config.polePairs * 3U * config.Psi_PM_mVs / (config.rotorInertia * 2U));
	self->config = config;
	return (self);
}

//void uz_FOC_CurrentControl(uz_FOC_CurrentControl_parameters* self) {
//	uz_assert_not_NULL(self);
//	uz_assert(self->is_ready == true);
//}
//
//void uz_FOC_SpeedControl(uz_FOC_SpeedControl_parameters* self) {
//	uz_assert_not_NULL(self);
//	uz_assert(self->is_ready);
//	float n_target_omega = self->config.n_target_rpm * 2.0f * M_PI / 60.0f;
//	float n_difference_rpm = self->config.n_target_rpm - self->n_rpm;
//
//
//}
