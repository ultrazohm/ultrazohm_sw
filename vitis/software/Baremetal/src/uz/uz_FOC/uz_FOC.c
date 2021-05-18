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
	self->config = config;
	return (self);
}

uz_FOC_SpeedControl_parameters* uz_FOC_SpeedControl_init(uz_FOC_SpeedControl_config config) {
	uz_assert(counter_FOC_SpeedControl < max_FOC_SpeedControl_instances);
	uz_FOC_SpeedControl_parameters* self = &instances_FOC_SpeedControl[counter_FOC_SpeedControl];
	uz_assert(self->is_ready == false);
	counter_FOC_SpeedControl += 1;
	self->is_ready = true;
	self->config = config;
	self->error_omega_sum = 0.0f;
	return (self);
}

void uz_FOC_CurrentControl(uz_FOC_CurrentControl_parameters* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready == true);

	float error_iq = self->config.iq_target_Ampere - self->iq_Ampere;
	self->error_iq_sum += error_iq;
	self->uq_target_Volt = error_iq * self->config.Kp_iq * (1.0f + self->error_iq_sum / self->config.Tn_iq);

	float error_id = self->config.id_target_Ampere - self->id_Ampere;
	self->error_id_sum += error_id;
	self->ud_target_Volt = error_id + self->config.Kp_id * (1.0f + self->error_id_sum / self->config.Tn_id);
}

void uz_FOC_SpeedControl(uz_FOC_SpeedControl_parameters* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float omega_target_rad = self->config.n_target_rpm * 2.0f * M_PI / 60.0f;
	float error_omega = omega_target_rad - self->omega_rad;
	self->error_omega_sum += error_omega;
	float iq_target_ampere = error_omega * self->config.Kp_n * (1.0f + self->error_omega_sum / self->config.Tn_n);

	float error_iq = iq_target_ampere - self->iq_Ampere;
	self->error_iq_sum += error_iq;
	self->uq_target_Volt = error_iq * self->config.Kp_iq * (1.0f + self->error_iq_sum / self->config.Tn_iq);

	float error_id = self->config.id_target_Ampere - self->id_Ampere;
	self->error_id_sum += error_id;
	self->ud_target_Volt = error_id + self->config.Kp_id * (1.0f + self->error_id_sum / self->config.Tn_id);

}
