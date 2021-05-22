#pragma once
#include <stdbool.h>

typedef struct uz_wavegen_chirp uz_wavegen_chirp;
typedef struct uz_wavegen_three_phase uz_wavegen_three_phase_sine;
struct uz_wavegen_chirp_config {
	float amplitude;
	float start_frequency_Hz;
	float end_frequency_Hz;
	float duration_sec;
	float initial_delay_sec;
};
struct uz_wavegen_three_phase_config {
	float amplitude;
	float frequency_Hz;
	float offset;
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
uz_wavegen_chirp* uz_wavegen_chirp_init(struct uz_wavegen_chirp_config config);
float uz_wavegen_chirp_sample(uz_wavegen_chirp* self);
void uz_wavegen_chirp_reset(uz_wavegen_chirp* self);

uz_wavegen_three_phase_sine* uz_wavegen_three_phase_init(struct uz_wavegen_three_phase_config config);
void uz_wavegen_three_phase(uz_wavegen_three_phase_sine* self);

float uz_wavegen_three_phase_get_phaseU(uz_wavegen_three_phase_sine* self);
float uz_wavegen_three_phase_get_phaseV(uz_wavegen_three_phase_sine* self);
float uz_wavegen_three_phase_get_phaseW(uz_wavegen_three_phase_sine* self);

