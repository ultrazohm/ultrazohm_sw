#include "uz_wavegen.h"

float uz_wavegen_sine(int amplitude, int frequency_Hz) {
	float angle = 0.0;

	angle = 2.0 * M_PI * uz_SystemTime_GetInterruptCounter() * frequency_Hz / uz_SystemTime_GetIsrFrequencyInHz();

	return (amplitude * sin(angle));
}

float uz_wavegen_sawtooth(int amplitude, int frequency_Hz) {

	float sample = 0.0;

	sample = fmodf(uz_SystemTime_GetInterruptCounter(), (uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz));

	return (sample * amplitude / (uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz));
}
