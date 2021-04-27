#pragma once
#include "../uz_SystemTime/uz_SystemTime.h"

typedef struct {
	float amplitude;
	float frequency_Hz;
	float DutyCycle;

} wavegen_pulse_settings;

float uz_wavegen_sine(int amplitude, int frequency_Hz);
float uz_wavegen_sawtooth(int amplitude, int frequency_Hz);
float uz_wavegen_pulse(wavegen_pulse_settings pulse);

