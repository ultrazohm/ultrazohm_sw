#include "uz_wavegen.h"
#include <math.h>
#include <stdlib.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"

float uz_wavegen_sine(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t_Sec = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * M_PI * t_Sec * frequency_Hz;
	return (amplitude * sinf(angle));
}

float uz_wavegen_sine_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float angle = 2.0f * M_PI * t * frequency_Hz;
	return ((amplitude * sinf(angle)) + offset);
}

float uz_wavegen_sawtooth(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	return (sample * amplitude * frequency_Hz);
}

float uz_wavegen_sawtooth_with_offset(float amplitude, float frequency_Hz, float offset) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	return (sample * amplitude * frequency_Hz + offset);
}

float uz_wavegen_pulse(float amplitude, float frequency_Hz, float duty_cycle) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(duty_cycle >= 0.0f);
	uz_assert(duty_cycle <= 1.0f);
	uz_assert(amplitude != 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	if (sample > 1 / frequency_Hz * duty_cycle) {
		amplitude = 0.0f;
	}
	return (amplitude);
}

float uz_wavegen_square(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
	float t = uz_SystemTime_GetGlobalTimeInSec();
	float sample = fmodf(t, 1 / frequency_Hz);
	if (sample > 1 / frequency_Hz * 0.5f) {
		amplitude = amplitude * -1.0f;
	}
	return (amplitude);
}

float uz_wavegen_triangle(float amplitude, float frequency_Hz) {
	uz_assert(frequency_Hz > 0.0f);
	uz_assert(amplitude != 0.0f);
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
	uz_assert(amplitude != 0.0f);
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

float uz_wavegen_white_noise(float amplitude) {
	uz_assert(amplitude != 0.0f);
	return (amplitude * ((float) rand() / RAND_MAX * 2.0f - 1.0f));
}
