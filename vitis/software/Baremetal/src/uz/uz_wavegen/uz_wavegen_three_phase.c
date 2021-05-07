#include "uz_wavegen.h"
#include <math.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"
#define max_wavegen_instances 2

struct uz_wavegen_three_phase {
	bool is_ready;
	bool read_system_time;
	float phase_U;
	float phase_V;
	float phase_W;
	struct uz_wavegen_three_phase_config config;
};

static size_t counter = 0;
static uz_wavegen_three_phase_sin instances[max_wavegen_instances] = { 0 };

uz_wavegen_three_phase_sin* uz_wavegen_three_phase_init(struct uz_wavegen_three_phase_config config) {
	uz_assert(counter < max_wavegen_instances);
	uz_wavegen_three_phase_sin* self = &instances[counter];
	uz_assert(self->is_ready == false);
	counter += 1;
	self->is_ready = true;
	uz_assert(config.frequency_Hz > 0);
	uz_assert(config.amplitude != 0.0f);
	self->config = config;
	return (self);
}

void uz_wavegen_three_phase(uz_wavegen_three_phase_sin* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * M_PI * t_Sec * self->config.frequency_Hz;
	self->phase_U = self->config.amplitude * sinf(angle) + self->config.offset;
	self->phase_V = self->config.amplitude * sinf(angle + 2.0f * M_PI / 3.0f) + self->config.offset;
	self->phase_W = self->config.amplitude * sinf(angle + 4.0f * M_PI / 3.0f) + self->config.offset;
}
