#pragma once
#include <stdbool.h>

typedef struct uz_wavegen uz_wavegen;

struct uz_wavegen {
	bool is_ready;
	float time_integrator_s;
	float amplitude;
	float frequency_Hz;
};

float uz_wavegen_sine(float amplitude, float frequency_Hz);
float uz_wavegen_sine_with_offset(float amplitude, float frequency_Hz, float offset);
float uz_wavegen_sawtooth(float amplitude, float frequency_Hz);
float uz_wavegen_sawtooth_with_offset(float amplitude, float frequency_Hz, float offset);
float uz_wavegen_pulse(float amplitude, float frequency_Hz, float duty_cycle);
float uz_wavegen_square(float amplitude, float frequency_Hz);
float uz_wavegen_triangle(float amplitude, float frequency_Hz);
float uz_wavegen_triangle_with_offset(float amplitude, float frequency_Hz, float offset);
float uz_wavegen_saturation(float signal, float upper_limit, float lower_limit);

// Wave generation with state
float uz_wavegen_chirp_init(uz_wavegen* self);
float uz_wavegen_chirp(uz_wavegen* self);
