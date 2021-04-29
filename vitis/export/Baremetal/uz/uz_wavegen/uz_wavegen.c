#include "uz_wavegen.h"
#include <math.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"

float uz_wavegen_sine(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0 * M_PI * t * frequency_Hz;
	return (amplitude * sinf(angle));
}

float uz_wavegen_sine_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0 * M_PI * t * frequency_Hz;
	return ((amplitude * sinf(angle)) + offset);
}

float uz_wavegen_sawtooth(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, frequency_Hz);
	return (sample * amplitude);
}

float uz_wavegen_sawtooth_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0);
	float counter = uz_SystemTime_GetInterruptCounter();
	float frequency_adjusted = uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz;
	float sample = fmodf(counter, frequency_adjusted);
	return ((sample * amplitude / frequency_adjusted) + offset);
}

float uz_wavegen_pulse(float amplitude, float frequency_Hz, float duty_cycle) {
	uz_assert(frequency_Hz > 0.0);
	uz_assert(duty_cycle >= 0.0);
	uz_assert(duty_cycle <= 1.0);
	float counter = uz_SystemTime_GetInterruptCounter();
	float frequency_adjusted = uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz;
	float sample = fmodf(counter, frequency_adjusted);
	if (sample > frequency_adjusted * duty_cycle) {
		amplitude = 0.0f;
	}
	return (amplitude);
}

float uz_wavegen_square(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0);
	float counter = uz_SystemTime_GetInterruptCounter();
	float frequency_adjusted = uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz;
	float sample = fmodf(counter, frequency_adjusted);
	if (sample > frequency_adjusted * 0.5f) {
		amplitude = amplitude * -1.0f;
	}
	return (amplitude);
}

float uz_wavegen_triangle(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0);
	float triangle_wave = 0.0f;
	float counter = uz_SystemTime_GetInterruptCounter();
	float frequency_adjusted = uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz;
	float sample = fmodf(counter, frequency_adjusted);
	if (sample > frequency_adjusted * 0.5f) {
		triangle_wave = 2.0f * amplitude - 2.0f * sample * amplitude / frequency_adjusted;
	} else {
		triangle_wave = 2.0f * sample * amplitude / frequency_adjusted;
	}
	return (triangle_wave);
}

float uz_wavegen_triangle_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0);
	float triangle_wave = 0.0f;
	float counter = uz_SystemTime_GetInterruptCounter();
	float frequency_adjusted = uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz;
	float sample = fmodf(counter, frequency_adjusted);
	if (sample > frequency_adjusted * 0.5f) {
		triangle_wave = 2.0f * amplitude - 2.0f * sample * amplitude / frequency_adjusted + offset;
	} else {
		triangle_wave = 2.0f * sample * amplitude / frequency_adjusted + offset;
	}
	return (triangle_wave);
}


float uz_wavegen_saturation(float signal, float upper_limit, float lower_limit) {
	if (signal > upper_limit) {
		signal = upper_limit;
	} else if (signal < lower_limit) {
		signal = lower_limit;
	}
	return (signal);
}

float uz_wavegen_chirp(uz_wavegen* self) {
	uz_assert(self->is_ready);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	self->time_integrator_s += 0.0001 * t;
	return (self->amplitude * sinf(2.0 * M_PI * self->frequency_Hz * self->time_integrator_s));

}
