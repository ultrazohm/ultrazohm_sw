#pragma once
#include <stdbool.h>

/**
 * @brief Object definition for generating a chirp signal
 * 
 */
typedef struct uz_wavegen_chirp uz_wavegen_chirp;

/**
 * @brief Object definition for generating a three phase sine signal
 * 
 */
typedef struct uz_wavegen_three_phase uz_wavegen_three_phase;

/**
 * @brief Configuration struct for chirp generation, pass to init function. Accessible by the user 
 */
struct uz_wavegen_chirp_config {
	float amplitude;            /**< Amplitude of the chirp signal */ 
	float start_frequency_Hz;   /**< Start frequency of the chirp in Hz. Only positive values are permitted */
	float end_frequency_Hz;     /**< End frequency of the chirp in Hz. Only positive values are permitted*/ 
	float duration_sec;         /**< Duration of the transition from start to end frequency in seconds. Only positive values are permitted */
	float initial_delay_sec;    /**< Delay after first function call until transition starts in seconds. No negative values are permitted */
	float offset;               /**< Offset of the chirp wave */
};

/**
 * @brief Configuration struct for three phase sine, pass to init function. Accessible by the user
 */
struct uz_wavegen_three_phase_config {
	float amplitude;    /**< Amplitude of the three sine waves */
	float frequency_Hz; /**< Frequency of the three sine waves. Only positive values are permitted */
	float offset;       /**< Offset of the three sine waves */
};

/**
 * @brief Outputs one sample of a sine wave for the current global system time at each function call.
 * 
 * @param amplitude Amplitude for the sine wave
 * @param frequency_Hz Frequency for the sine wave in Hz. Only positive values are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_sine(float amplitude, float frequency_Hz);

/**
 * @brief Outputs one sample of a sine wave with the specified offset for the current global system time at each function call.
 * 
 * @param amplitude Amplitude for the sine wave
 * @param frequency_Hz Frequency for the sine wave in Hz. Only positive values are permitted
 * @param offset Offset for the sine wave
 * @return Returns one sample for current system time
 */
float uz_wavegen_sine_with_offset(float amplitude, float frequency_Hz, float offset);

/**
 * @brief Returns one sample of a sawtooth wave
 * 
 * @param amplitude Amplitude for the sawtooth wave
 * @param frequency_Hz Frequency for the sawtooth wave in Hz. Only positive values are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_sawtooth(float amplitude, float frequency_Hz);

/**
 * @brief Returns one sample of a sawtooth wave with an configurable offset
 * 
 * @param amplitude Amplitude for the sawtooth wave
 * @param frequency_Hz Frequency for the sawtooth wave in Hz. Only positive values are permitted
 * @param offset Offset for the sawtooth wave
 * @return Returns one sample for current system time
 */
float uz_wavegen_sawtooth_with_offset(float amplitude, float frequency_Hz, float offset);

/**
 * @brief Returns one sample of a pulse wave
 * 
 * @param amplitude Amplitude for the pulse wave
 * @param frequency_Hz Frequency for the pulse wave in Hz. Only positive values are permitted
 * @param duty_cycle Duty Cycle for the pulse wave. Only values 0.0 <= DutyCycle <= 1.0 are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_pulse(float amplitude, float frequency_Hz, float duty_cycle);

/**
 * @brief Returns one sample of a square wave
 * 
 * @param amplitude Amplitude for the square wave
 * @param frequency_Hz Frequency for the square wave in Hz. Only positive values are permitted
 * @param duty_cycle Duty Cycle for the square wave. Only values 0.0 <= DutyCycle <= 1.0 is permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_square(float amplitude, float frequency_Hz, float duty_cycle);

/**
 * @brief Returns one sample of a triangle wave
 * 
 * @param amplitude Amplitude for the triangle wave
 * @param frequency_Hz Frequency for the triangle wave in Hz. Only positive values are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_triangle(float amplitude, float frequency_Hz);

/**
 * @brief Returns one sample of a triangle wave with an configurable offset
 * 
 * @param amplitude Amplitude for the triangle wave
 * @param frequency_Hz Frequency for the triangle wave in Hz. Only positive values are permitted
 * @param offset Offset for the triangle wave
 * @return Returns one sample for current system time
 */
float uz_wavegen_triangle_with_offset(float amplitude, float frequency_Hz, float offset);

/**
 * @brief Returns one sample which either limits the input signal to the lower or upper limit, or passes the input signal through. Functions very similar to the saturation block in Simulink.
 * 
 * @param signal Any input signal
 * @param upper_limit Upper limit of the saturation
 * @param lower_limit Lower limit of the saturation. upper_limit > lower_limit is required
 * @return Returns one sample of the adjusted input
 */
float uz_wavegen_saturation(float signal, float upper_limit, float lower_limit);

/**
 * @brief Returns one random sample of a white-noise function
 * 
 * @param amplitude Max value of the white-noise wave
 * @return Returns one random sample 
 */
float uz_wavegen_white_noise(float amplitude);

/**
 * @brief Initialization of a wavegenerator for a chirp signal
 * 
 * @param config Configuration struct
 * @return Pointer to wavegen_chirp instance
 */
uz_wavegen_chirp* uz_wavegen_chirp_init(struct uz_wavegen_chirp_config config);

/**
 * @brief Returns one sample of the chirp
 * 
 * @param self wavegen_chirp instance
 * @return One sample of the chirp output for current system time
 */
float uz_wavegen_chirp_sample(uz_wavegen_chirp* self);

/**
 * @brief Resets the wavegen_chirp instance
 * 
 * @param self wavegen_chirp instance
 */
void uz_wavegen_chirp_reset(uz_wavegen_chirp* self);

/**
 * @brief Initialization of a wavegenerator for a three phase sine
 * 
 * @param config Configuration struct
 * @return Pointer to wavegen_three_phase instance
 */
uz_wavegen_three_phase* uz_wavegen_three_phase_init(struct uz_wavegen_three_phase_config config);

/**
 * @brief Calculates one sample for each phase for current system time
 * 
 * @param self wavegen_three_phase instance
 */
void uz_wavegen_three_phase_sample(uz_wavegen_three_phase* self);

/**
 * @brief Returns the last calculated sample for the Phase U
 * 
 * @param self wavegen_three_phase instance
 * @return Returns last sample for Phase U 
 */
float uz_wavegen_three_phase_get_phaseU(uz_wavegen_three_phase* self);

/**
 * @brief Returns the last calculated sample for the Phase V
 * 
 * @param self wavegen_three_phase instance
 * @return Returns last sample for Phase V 
 */
float uz_wavegen_three_phase_get_phaseV(uz_wavegen_three_phase* self);

/**
 * @brief Returns the last calculated sample for the Phase W
 * 
 * @param self wavegen_three_phase instance
 * @return Returns last sample for Phase W 
 */
float uz_wavegen_three_phase_get_phaseW(uz_wavegen_three_phase* self);
