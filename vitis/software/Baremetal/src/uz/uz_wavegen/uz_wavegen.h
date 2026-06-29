#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "../uz_Transformation/uz_Transformation.h"
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
 * @brief Object definition for generating a sine signal
 *
 */
typedef struct uz_wavegen_sine uz_wavegen_sine_t;

/**
 * @brief Object definition for generating a sawtooth signal
 *
 */
typedef struct uz_wavegen_sawtooth uz_wavegen_sawtooth_t;

/**
 * @brief Object definition for generating a pulse signal
 *
 */
typedef struct uz_wavegen_pulse uz_wavegen_pulse_t;

/**
 * @brief Object definition for generating a square signal
 *
 */
typedef struct uz_wavegen_square uz_wavegen_square_t;

/**
 * @brief Object definition for generating a triangle signal
 *
 */
typedef struct uz_wavegen_triangle uz_wavegen_triangle_t;

/**
 * @brief Internal phase accumulator shared by all time-dependent wavegen
 *        modules. Stores normalized phase in [0,1) and advances by
 *        frequency_Hz * dt on every step. Time is stored as integer
 *        microseconds and only the small delta is converted to seconds, so
 *        long uptimes do not quantize the waveform through float timestamp
 *        precision.
 */
struct uz_wavegen_phase_acc {
    bool is_first_call;
    uint64_t t_prev_us;
    float phase; /**< wrapped to [0.0f, 1.0f) */
};

/**
 * @brief Advances the accumulator and returns the current normalized phase.
 *
 * On the first call, seeds t_prev_us from uz_SystemTime_GetUptimeInUs() and
 * returns 0.0f without advancing. Subsequent calls advance the phase by
 * frequency_Hz * dt_us * 1e-6, then wrap via phase -= floorf(phase).
 *
 * @param acc Pointer to accumulator state
 * @param frequency_Hz Current frequency in Hz. Must be > 0.
 * @return Normalized phase in [0.0f, 1.0f).
 */
float uz_wavegen_phase_acc_step(struct uz_wavegen_phase_acc* acc, float frequency_Hz);

/**
 * @brief Resets the accumulator to its first-call state.
 *
 * @param acc Pointer to accumulator state
 */
void uz_wavegen_phase_acc_reset(struct uz_wavegen_phase_acc* acc);

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
 * @brief Initialization of a sine wavegenerator.
 *        Must be called once before uz_wavegen_sine_sample*.
 *        Uses phase accumulation so ramped frequency and long uptimes are
 *        handled correctly.
 * @return Pointer to uz_wavegen_sine instance
 */
uz_wavegen_sine_t* uz_wavegen_sine_init(void);

/**
 * @brief Outputs one sample of a sine wave. Advances the internal phase
 *        accumulator by frequency_Hz * dt since the previous call.
 *
 * @param self Pointer to uz_wavegen_sine instance
 * @param amplitude Amplitude for the sine wave
 * @param frequency_Hz Frequency for the sine wave in Hz. Only positive values are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_sine_sample(uz_wavegen_sine_t* self, float amplitude, float frequency_Hz);

/**
 * @brief Outputs one sample of a sine wave with the specified DC offset.
 *
 * @param self Pointer to uz_wavegen_sine instance
 * @param amplitude Amplitude for the sine wave
 * @param frequency_Hz Frequency for the sine wave in Hz. Only positive values are permitted
 * @param offset DC offset added to the sample
 * @return Returns one sample for current system time
 */
float uz_wavegen_sine_sample_with_offset(uz_wavegen_sine_t* self, float amplitude, float frequency_Hz, float offset);

/**
 * @brief Resets the sine phase accumulator.
 * @param self Pointer to uz_wavegen_sine instance
 */
void uz_wavegen_sine_reset(uz_wavegen_sine_t* self);

/**
 * @brief Initialization of a sawtooth wavegenerator.
 *        Must be called once before uz_wavegen_sawtooth_sample*.
 * @return Pointer to uz_wavegen_sawtooth instance
 */
uz_wavegen_sawtooth_t* uz_wavegen_sawtooth_init(void);

/**
 * @brief Returns one sample of a sawtooth wave.
 *
 * @param self Pointer to uz_wavegen_sawtooth instance
 * @param amplitude Amplitude for the sawtooth wave
 * @param frequency_Hz Frequency for the sawtooth wave in Hz. Only positive values are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_sawtooth_sample(uz_wavegen_sawtooth_t* self, float amplitude, float frequency_Hz);

/**
 * @brief Returns one sample of a sawtooth wave with a configurable DC offset.
 *
 * @param self Pointer to uz_wavegen_sawtooth instance
 * @param amplitude Amplitude for the sawtooth wave
 * @param frequency_Hz Frequency for the sawtooth wave in Hz. Only positive values are permitted
 * @param offset DC offset added to the sample
 * @return Returns one sample for current system time
 */
float uz_wavegen_sawtooth_sample_with_offset(uz_wavegen_sawtooth_t* self, float amplitude, float frequency_Hz, float offset);

/**
 * @brief Resets the sawtooth phase accumulator.
 * @param self Pointer to uz_wavegen_sawtooth instance
 */
void uz_wavegen_sawtooth_reset(uz_wavegen_sawtooth_t* self);

/**
 * @brief Initialization of a pulse wavegenerator.
 * @return Pointer to uz_wavegen_pulse instance
 */
uz_wavegen_pulse_t* uz_wavegen_pulse_init(void);

/**
 * @brief Returns one sample of a pulse wave (amplitude during duty, zero after).
 *
 * @param self Pointer to uz_wavegen_pulse instance
 * @param amplitude Amplitude for the pulse wave
 * @param frequency_Hz Frequency for the pulse wave in Hz. Only positive values are permitted
 * @param duty_cycle Duty Cycle for the pulse wave. Only values 0.0 <= DutyCycle <= 1.0 are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_pulse_sample(uz_wavegen_pulse_t* self, float amplitude, float frequency_Hz, float duty_cycle);

/**
 * @brief Resets the pulse phase accumulator.
 * @param self Pointer to uz_wavegen_pulse instance
 */
void uz_wavegen_pulse_reset(uz_wavegen_pulse_t* self);

/**
 * @brief Initialization of a square wavegenerator.
 * @return Pointer to uz_wavegen_square instance
 */
uz_wavegen_square_t* uz_wavegen_square_init(void);

/**
 * @brief Returns one sample of a square wave (+amplitude during duty, -amplitude after).
 *
 * @param self Pointer to uz_wavegen_square instance
 * @param amplitude Amplitude for the square wave
 * @param frequency_Hz Frequency for the square wave in Hz. Only positive values are permitted
 * @param duty_cycle Duty Cycle for the square wave. Only values 0.0 <= DutyCycle <= 1.0 is permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_square_sample(uz_wavegen_square_t* self, float amplitude, float frequency_Hz, float duty_cycle);

/**
 * @brief Resets the square phase accumulator.
 * @param self Pointer to uz_wavegen_square instance
 */
void uz_wavegen_square_reset(uz_wavegen_square_t* self);

/**
 * @brief Initialization of a triangle wavegenerator.
 * @return Pointer to uz_wavegen_triangle instance
 */
uz_wavegen_triangle_t* uz_wavegen_triangle_init(void);

/**
 * @brief Returns one sample of a triangle wave.
 *
 * @param self Pointer to uz_wavegen_triangle instance
 * @param amplitude Amplitude for the triangle wave
 * @param frequency_Hz Frequency for the triangle wave in Hz. Only positive values are permitted
 * @return Returns one sample for current system time
 */
float uz_wavegen_triangle_sample(uz_wavegen_triangle_t* self, float amplitude, float frequency_Hz);

/**
 * @brief Returns one sample of a triangle wave with a configurable DC offset.
 *
 * @param self Pointer to uz_wavegen_triangle instance
 * @param amplitude Amplitude for the triangle wave
 * @param frequency_Hz Frequency for the triangle wave in Hz. Only positive values are permitted
 * @param offset DC offset added to the sample
 * @return Returns one sample for current system time
 */
float uz_wavegen_triangle_sample_with_offset(uz_wavegen_triangle_t* self, float amplitude, float frequency_Hz, float offset);

/**
 * @brief Resets the triangle phase accumulator.
 * @param self Pointer to uz_wavegen_triangle instance
 */
void uz_wavegen_triangle_reset(uz_wavegen_triangle_t* self);

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
 * @brief Initialization of a three-phase sine wavegenerator.
 *        Must be called once before uz_wavegen_three_phase_sample.
 * @return Pointer to uz_wavegen_three_phase instance
 */
uz_wavegen_three_phase* uz_wavegen_three_phase_init(void);

/**
 * @brief Returns one sample of a three-phase sine wave using phase accumulation.
 *        Correctly handles ramped frequency and preserves precision at long uptimes.
 *
 * @param self Pointer to uz_wavegen_three_phase instance
 * @param amplitude Amplitude of all three signals
 * @param frequency_Hz Frequency in Hertz. Only positive values permitted.
 * @param offset DC offset added to all three phases
 * @return uz_3ph_abc_t
 */
uz_3ph_abc_t uz_wavegen_three_phase_sample(uz_wavegen_three_phase* self, float amplitude, float frequency_Hz, float offset);

/**
 * @brief Resets the three-phase phase accumulator.
 * @param self Pointer to uz_wavegen_three_phase instance
 */
void uz_wavegen_three_phase_reset(uz_wavegen_three_phase* self);
