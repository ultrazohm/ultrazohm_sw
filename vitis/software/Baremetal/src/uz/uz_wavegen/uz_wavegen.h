#pragma once
#include <stdbool.h>

typedef struct uz_wavegen uz_wavegen;

struct uz_wavegen_config {
	float amplitude;
	float start_frequency_Hz;
	float end_frequency_Hz;
	float duration_Sec;
	float initial_delay_Sec;

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
float uz_wavegen_white_noise(float amplitude);

// Wave generation with state
uz_wavegen* uz_wavegen_chirp_init(struct uz_wavegen_config config);
float uz_wavegen_chirp(uz_wavegen* self);
void uz_wavegen_chirp_reset(uz_wavegen* self);
