#include "uz_wavegen.h"



//amplitude: 		Amplitude of the output sine wave
//frequency:		Frequency of the output sine wave
float uz_wavegen_sine(int amplitude, int frequency) {
	//Variables
	float angle = 0.0;

	angle = 2.0 * M_PI * frequency * uz_SystemTime_GetIsrPeriodInUs() * 0.000001 * uz_SystemTime_GetInterruptCounter();

	return (amplitude * sin(angle));
}

//amplitude: 		Amplitude of the output sawtooth wave
//frequency:		Frequency of the output sawtooth wave
float uz_wavegen_sawtooth(int amplitude, int frequency) {
	//Variables
	float sawtooth = 0.0;
	static float counter = 0.0;

	if (counter > (1 / (uz_SystemTime_GetIsrPeriodInUs() * 0.000001)) / frequency)
		counter = 0;

	sawtooth = amplitude * (counter * frequency * uz_SystemTime_GetIsrPeriodInUs() * 0.000001);

	counter += 1;

	return (sawtooth);
}
