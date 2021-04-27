#include "uz_wavegen.h"

//typedef struct {
//	float amplitude;
//	float frequency;
//	float DutyCycle;
//
//} wavegen_pulse_settings;


//wavegen_pulse_settings test = { .amplitude = 0.0f, .frequency = 0.0f, .DutyCycle = 0.0f };

float uz_wavegen_sine(int amplitude, int frequency_Hz) {
	float angle = 0.0;

	angle = 2.0 * M_PI * uz_SystemTime_GetInterruptCounter() * frequency_Hz / uz_SystemTime_GetIsrFrequencyInHz();

	return (amplitude * sinf(angle));
}

float uz_wavegen_sawtooth(int amplitude, int frequency_Hz) {

	float sample = 0.0;

	sample = fmodf(uz_SystemTime_GetInterruptCounter(), (uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz));

	return (sample * amplitude / (uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz));
}

float uz_wavegen_pulse(wavegen_pulse_settings pulse) {
	float sample = 0.0f;

	sample = fmodf(uz_SystemTime_GetInterruptCounter(), (uz_SystemTime_GetIsrFrequencyInHz() / pulse.frequency_Hz));

	if (sample > (uz_SystemTime_GetIsrFrequencyInHz() / pulse.frequency_Hz) * pulse.DutyCycle)
		pulse.amplitude = 0.0f;

	return (pulse.amplitude);
}
