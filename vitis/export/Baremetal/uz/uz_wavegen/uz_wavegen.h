#pragma once
#include "../uz_SystemTime/uz_SystemTime.h"

typedef struct {
	float amplitude;
	float frequency_Hz;
	float DutyCycle;
} wavegen_pulse_settings;

typedef struct {
	float input_signal;
	float upper_limit;
	float lower_limit;

} wavegen_saturation_settings;

float uz_wavegen_sine(float amplitude, float frequency_Hz);
float uz_wavegen_sawtooth(float amplitude, float frequency_Hz);
float uz_wavegen_pulse(wavegen_pulse_settings pulse);
float uz_wavegen_square(float amplitude, float frequency_Hz);
float uz_wavegen_triangle(float amplitude, float frequency_Hz);
float uz_wavegen_saturation(wavegen_saturation_settings saturation);
