

#include "../include/uz_wavegen_init.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
#include <math.h>
#include "../uz/uz_global_configuration.h"

struct uz_wavegen_2_config wavegen_config_1 = {
	.amplitude = 2*M_PI,            /**< Amplitude*/
	.sample_time_s = 1.0f/UZ_ISR_FREQUENCY,
	.frequency_Hz = 50.0f,
	.offset = 0.0f,     /**< Offset*/
	.dutycycle = 0.5f,
	.low_pulse = 0.0f,
	.high_pulse = 1.0f,
	.phase_offset_0_1 = 0.0f,
	.wave_direction = WAVE_UP,
};

struct uz_wavegen_2_config wavegen_config_2 = {
	.amplitude = 1,            /**< Amplitude*/
	.sample_time_s = 1.0f/UZ_ISR_FREQUENCY,
	.frequency_Hz = 50.0f,
	.offset = 0.0f,     /**< Offset*/
	.dutycycle = 0.5f,
	.low_pulse = 0.0f,
	.high_pulse = 1.0f,
	.phase_offset_0_1 = 0.0f,
	.wave_direction = WAVE_UP,
};

struct uz_wavegen_2_config wavegen_config_theta = {
	.amplitude = 2*M_PI,            /**< Amplitude*/
	.sample_time_s = 1.0f/UZ_ISR_FREQUENCY,
	.frequency_Hz = 50.0f,
	.offset = 0.0f,     /**< Offset*/
	.dutycycle = 0.0f,
	.low_pulse = 0.0f,
	.high_pulse = 1.0f,
	.phase_offset_0_1 = 0.0f,
	.wave_direction = WAVE_UP,
};

uz_wavegen_2* init_wavgen_1(void){
	return  uz_wavegen_2_init(wavegen_config_1);
}
uz_wavegen_2* init_wavgen_2(void){
	return  uz_wavegen_2_init(wavegen_config_2);
}
uz_wavegen_2* init_wavgen_theta(void){
	return  uz_wavegen_2_init(wavegen_config_theta);
}
