#define UZ_STATIC_ALLOCATOR(objectname,maxinstances)                    \
                                                                        \
static size_t objectname##_counter = 0;                                 \
static uz_##objectname objectname##_instances[maxinstances] = { 0 };	\


#define UZ_ALLOCATION(objectname,maxinstances)   \
	uz_assert( objectname##_counter < maxinstances);    \
	uz_##objectname * self = &objectname##_instances[objectname##_counter];       \
	objectname##_counter += 1;                                                 \
	uz_assert(self->is_ready == false); \
	self->is_ready = true; \


#include "../uz_global_configuration.h"
#if UZ_WAVEGEN_CHIRP_MAX_INSTANCES > 0
#include "uz_wavegen.h"
#include <math.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"


struct uz_wavegen_chirp {
	bool is_ready;
	bool is_first_call_to_sample;
	float elapsed_time_since_start;
	float initial_global_time_sec;
	float transition_angle;
	struct uz_wavegen_chirp_config config;
};
UZ_STATIC_ALLOCATOR(wavegen_chirp, UZ_WAVEGEN_CHIRP_MAX_INSTANCES)
//static size_t counter_chirp = 0;
//static uz_wavegen_chirp instances_chirp[UZ_WAVEGEN_CHIRP_MAX_INSTANCES] = { 0 };

uz_wavegen_chirp* uz_wavegen_chirp_init(struct uz_wavegen_chirp_config config) {
	//uz_assert(counter_chirp < UZ_WAVEGEN_CHIRP_MAX_INSTANCES);
	//uz_wavegen_chirp* self = &instances_chirp[counter_chirp];
	//uz_assert_false(self->is_ready);
	//counter_chirp += 1;
	//self->is_ready = true;
	UZ_ALLOCATION(wavegen_chirp,UZ_WAVEGEN_CHIRP_MAX_INSTANCES)

	self->is_first_call_to_sample = true;
	uz_assert(config.amplitude != 0.0f);
	uz_assert(config.start_frequency_Hz > 0);
	uz_assert(config.end_frequency_Hz > 0);
	uz_assert(config.end_frequency_Hz > config.start_frequency_Hz);
	uz_assert(config.initial_delay_sec >= 0);
	uz_assert(config.duration_sec > 0);
	self->config = config;
	return (self);
}

void uz_wavegen_chirp_reset(uz_wavegen_chirp* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->is_first_call_to_sample = true;
	self->elapsed_time_since_start = 0.0f;
	self->transition_angle = 0.0f;
}

float uz_wavegen_chirp_sample(uz_wavegen_chirp* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float system_time_sec = uz_SystemTime_GetGlobalTimeInSec();
	// If its the first call, we take the current time as the initial time to have small numbers at start with 0
	if (self->is_first_call_to_sample) {
		self->initial_global_time_sec = system_time_sec; // system_time_sec holds the current global time, thus we take this value as the inital time
		self->is_first_call_to_sample = false;
	}
	self->elapsed_time_since_start = system_time_sec - self->initial_global_time_sec;
	float remaining_delay_sec = self->config.initial_delay_sec - self->elapsed_time_since_start;
	float t_Sec = self->elapsed_time_since_start - self->config.initial_delay_sec;
	float chirp_rate = (self->config.end_frequency_Hz - self->config.start_frequency_Hz) / self->config.duration_sec;
	float chirp_output = 0.0f;
	if (remaining_delay_sec > 0) {
		chirp_output =0.0f;
	} else {
		if (t_Sec <= self->config.duration_sec) {
			self->transition_angle = 2.0 * M_PI * (((chirp_rate / 2) * t_Sec * t_Sec) + (t_Sec * self->config.start_frequency_Hz));
			chirp_output = self->config.amplitude * sinf(self->transition_angle) + self->config.offset;
		} else {
			chirp_output = self->config.amplitude * sinf(self->transition_angle + (2.0 * M_PI * t_Sec * self->config.end_frequency_Hz)) + self->config.offset;
		}
	}
	return (chirp_output);

}
#endif