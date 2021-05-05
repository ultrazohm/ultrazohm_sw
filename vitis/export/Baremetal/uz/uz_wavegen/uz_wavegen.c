#include "uz_wavegen.h"
#include <math.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"

float uz_wavegen_sine(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * M_PI * t * frequency_Hz;
	return (amplitude * sinf(angle));
}

float uz_wavegen_sine_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * M_PI * t * frequency_Hz;
	return ((amplitude * sinf(angle)) + offset);
}

float uz_wavegen_sawtooth(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	return (sample * amplitude * frequency_Hz);
}

float uz_wavegen_sawtooth_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	return (sample * amplitude * frequency_Hz + offset);
}

float uz_wavegen_pulse(float amplitude, float frequency_Hz, float duty_cycle) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(duty_cycle >= 0.0f);
	uz_assert(duty_cycle <= 1.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	if (sample > 1 / frequency_Hz * duty_cycle) {
		amplitude = 0.0f;
	}
	return (amplitude);
}

float uz_wavegen_square(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	if (sample > 1 / frequency_Hz * 0.5f) {
		amplitude = amplitude * -1.0f;
	}
	return (amplitude);
}

float uz_wavegen_triangle(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	float triangle_wave = 0.0f;
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	if (sample > 1 / frequency_Hz * 0.5f) {
		triangle_wave = 2.0f * amplitude - 2.0f * sample * amplitude * frequency_Hz;
	} else {
		triangle_wave = 2.0f * sample * amplitude * frequency_Hz;
	}
	return (triangle_wave);
}

float uz_wavegen_triangle_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	float triangle_wave = 0.0f;
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	if (sample > 1 / frequency_Hz * 0.5f) {
		triangle_wave = (2.0f * amplitude - 2.0f * sample * amplitude * frequency_Hz) + offset;
	} else {
		triangle_wave = (2.0f * sample * amplitude * frequency_Hz) + offset;
	}
	return (triangle_wave);
}

float uz_wavegen_saturation(float signal, float upper_limit, float lower_limit) {
	uz_assert(upper_limit > lower_limit);
	if (signal > upper_limit) {
		signal = upper_limit;
	} else if (signal < lower_limit) {
		signal = lower_limit;
	}
	return (signal);
}

float uz_wavegen_chirp(uz_wavegen* self) {
	uz_assert(self->is_ready);
	uz_assert(self->start_frequency_Hz > 0);
	uz_assert(self->end_frequency_Hz > 0);
	uz_assert(self->end_frequency_Hz > self->start_frequency_Hz);
	uz_assert(self->initial_delay_Sec >= 0);
	uz_assert(self->duration_Sec > 0);
	float delay_Sec = self->initial_delay_Sec - self->elapsed_time_since_start;
	float system_time_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float t_Sec = self->elapsed_time_since_start - self->initial_delay_Sec;
	float chirp_rate = (self->end_frequency_Hz - self->start_frequency_Hz) / self->duration_Sec;
	float chirp_output = 0.0f;

	if (delay_Sec > 0) {
		chirp_output = 0.0f;
	} else {
		if (t_Sec <= self->duration_Sec) {
			self->transition_angle = 2.0 * M_PI * (chirp_rate / 2 * t_Sec * t_Sec + t_Sec * self->start_frequency_Hz);
			chirp_output = self->amplitude * sinf(self->transition_angle);
		} else {
			chirp_output = self->amplitude * sinf(self->transition_angle + 2.0 * M_PI * t_Sec * self->end_frequency_Hz);
		}
	}
	self->elapsed_time_since_start = system_time_Sec - self->initial_global_time_Sec;
	return (chirp_output);

}
