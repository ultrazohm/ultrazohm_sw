#include "uz_wavegen.h"
#include <math.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"
#define max_wavegen_instances 2

struct uz_wavegen_chirp {
	bool is_ready;
	bool read_system_time;
	float elapsed_time_since_start;
	float initial_global_time_Sec;
	float transition_angle;
	struct uz_wavegen_config config;
};
static size_t counter = 0;
static uz_wavegen instances[max_wavegen_instances] = { 0 };

uz_wavegen* uz_wavegen_chirp_init(struct uz_wavegen_config config) {
	uz_assert(counter < max_wavegen_instances);
	uz_wavegen* self = &instances[counter];
	uz_assert(self->is_ready == false);
	counter += 1;
	self->is_ready = true;
	self->read_system_time = true;
	uz_assert(config.start_frequency_Hz > 0);
	uz_assert(config.end_frequency_Hz > 0);
	uz_assert(config.end_frequency_Hz > config.start_frequency_Hz);
	uz_assert(config.initial_delay_Sec >= 0);
	uz_assert(config.duration_Sec > 0);
	self->initial_global_time_Sec = uz_SystemTime_GetGlobalTimeInSec();
	self->config = config;
	return (self);
}

void uz_wavegen_chirp_reset(uz_wavegen* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready == true);
	self->read_system_time = true;
	self->elapsed_time_since_start = 0.0f;
	self->transition_angle = 0.0f;
}

float uz_wavegen_chirp(uz_wavegen* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float remaining_delay_Sec = self->config.initial_delay_Sec - self->elapsed_time_since_start;
	float t_Sec = self->elapsed_time_since_start - self->config.initial_delay_Sec;
	float chirp_rate = (self->config.end_frequency_Hz - self->config.start_frequency_Hz) / self->config.duration_Sec;
	float chirp_output = 0.0f;
	float system_time_Sec = uz_SystemTime_GetGlobalTimeInSec();

	if (self->read_system_time == true) {
		self->initial_global_time_Sec = uz_SystemTime_GetGlobalTimeInSec();
		self->read_system_time = false;
	}
	if (remaining_delay_Sec > 0) {
		chirp_output = 0.0f;
	} else {
		if (t_Sec <= self->config.duration_Sec) {
			self->transition_angle = 2.0 * M_PI * (chirp_rate / 2 * t_Sec * t_Sec + t_Sec * self->config.start_frequency_Hz);
			chirp_output = self->config.amplitude * sinf(self->transition_angle);
		} else {
			chirp_output = self->config.amplitude * sinf(self->transition_angle + 2.0 * M_PI * t_Sec * self->config.end_frequency_Hz);
		}
	}
	self->elapsed_time_since_start = system_time_Sec - self->initial_global_time_Sec;
	return (chirp_output);

}
