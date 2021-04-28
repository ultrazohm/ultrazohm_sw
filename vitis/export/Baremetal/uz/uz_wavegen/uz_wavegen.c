#include "uz_wavegen.h"

float uz_wavegen_sine(float amplitude, float frequency_Hz) {
	float angle = 0.0;

	uz_assert(frequency_Hz < 0.0);

	angle = 2.0 * M_PI * uz_SystemTime_GetInterruptCounter() * frequency_Hz / uz_SystemTime_GetIsrFrequencyInHz();

	return (amplitude * sinf(angle));
}

float uz_wavegen_sawtooth(float amplitude, float frequency_Hz) {

	float sample = 0.0;

	uz_assert(frequency_Hz < 0.0);

	sample = fmodf(uz_SystemTime_GetInterruptCounter(), (uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz));

	return (sample * amplitude / (uz_SystemTime_GetIsrFrequencyInHz() / frequency_Hz));
}

float uz_wavegen_pulse(wavegen_pulse_settings pulse) {
	float sample = 0.0f;

	uz_assert(pulse.frequency_Hz < 0.0);
	uz_assert(pulse.DutyCycle < 0.0);
	uz_assert(pulse.DutyCycle > 1.0);

	sample = fmodf(uz_SystemTime_GetInterruptCounter(), (uz_SystemTime_GetIsrFrequencyInHz() / pulse.frequency_Hz));

	if (sample > (uz_SystemTime_GetIsrFrequencyInHz() / pulse.frequency_Hz) * pulse.DutyCycle)
		pulse.amplitude = 0.0f;

	return (pulse.amplitude);
}
