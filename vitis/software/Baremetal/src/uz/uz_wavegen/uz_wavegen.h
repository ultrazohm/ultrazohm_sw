#pragma once
#include <stdbool.h>

/**
 * @brief Object definition for generating a chirp signal
 * 
 */
typedef struct uz_wavegen_chirp uz_wavegen_chirp;

typedef struct uz_wavegen_three_phase uz_wavegen_three_phase_sine;

/**
 * @brief Configuration struct for chirp generation, pass to init function.
 * 
 */
struct uz_wavegen_chirp_config {
	float amplitude; /**< Amplitude of the chirp signal */ 
	float start_frequency_Hz; /**< Start frequency of the chrip */
	float end_frequency_Hz; /**< End frequency of the chirp*/ 
	float duration_sec; /**< Duration of the transition from start to end frequency in seconds */
	float initial_delay_sec; /**< Delay until transition starts, time a sine with start frequency is returned from sample function */
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


/**
 * @brief Initialization of a wavegenerator for a chirp signal
 * 
 * @param config Configuration struct
 * @return uz_wavegen_chirp* Pointer to wavegen_chirp instance
 */
uz_wavegen_chirp* uz_wavegen_chirp_init(struct uz_wavegen_chirp_config config);

/**
 * @brief Returns one sample of the chirp
 * 
 * @param self wavegen_chirp instance
 * @return float One sample of the chirp output for current system time
 */
float uz_wavegen_chirp_sample(uz_wavegen_chirp* self);

/**
 * @brief Resets the wavegen_chirp instance
 * 
 * @param self 
 */
void uz_wavegen_chirp_reset(uz_wavegen_chirp* self);

uz_wavegen_three_phase_sine* uz_wavegen_three_phase_init(struct uz_wavegen_three_phase_config config);
void uz_wavegen_three_phase(uz_wavegen_three_phase_sine* self);
float uz_wavegen_three_phase_get_phaseU(uz_wavegen_three_phase_sine* self);
float uz_wavegen_three_phase_get_phaseV(uz_wavegen_three_phase_sine* self);
float uz_wavegen_three_phase_get_phaseW(uz_wavegen_three_phase_sine* self);
