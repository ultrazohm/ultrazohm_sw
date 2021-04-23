#include "uz_wavegen.h"

float uz_wavegen_sine(int amplitude, int frequency_Hz) {
	float angle = 0.0;

	angle = 2.0 * M_PI * uz_SystemTime_GetInterruptCounter() * frequency_Hz / uz_SystemTime_GetIsrFrequencyInHz();

	return (amplitude * sin(angle));
}

float uz_wavegen_sawtooth(int amplitude, int frequency_Hz) {

	static unsigned int sample = 0.0;

	if (sample > uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz - 1) {
		sample = 0;
	}

	sample += 1U;

	return (amplitude * sample * frequency_Hz / uz_SystemTime_GetIsrFrequencyInHz());
}
