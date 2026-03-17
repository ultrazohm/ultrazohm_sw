#pragma once
#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include <stdint.h>
/**
 * @brief Object definition for generating a chirp signal
 *
 */
typedef struct uz_wavegen_2 uz_wavegen_2;

typedef enum {
    WAVE_UP,
    WAVE_DOWN
} wave_direction_t;

/**
 * @brief Configuration struct for chirp generation, pass to init function. Accessible by the user
 */
struct uz_wavegen_2_config {
	float amplitude;            /**< Amplitude*/
	float sample_time_s;
	float frequency_Hz;
	float offset;               /**< Offset*/
	float dutycycle;
	float low_pulse;
	float high_pulse;
	float phase_offset_0_1;
	wave_direction_t wave_direction;
};

/*
TODO mögliche Erweiterungen:
- evtl. Threshold pre compute
- linear sweep
- chirp
- sine-wave mit lookup Tabelle -> vermutlich nicht relevatn
- Rampe oder sowas
- synchronisierung mehrere waves, oder eine Grund phase und dann mehrere mit relativer Phase, Amplitude und Offset
*/

/**
 * @brief Initialization of a wavegenerator for a chirp signal
 *
 * @param config Configuration struct
 * @return Pointer to wavegen_chirp instance
 */
uz_wavegen_2* uz_wavegen_2_init(struct uz_wavegen_2_config config);

/**
 * @brief Returns one sample of the chirp
 *
 * @param self wavegen_2 instance
 * @return One sample of the chirp output for current system time
 */
uint32_t uz_wavegen_2_sample(uz_wavegen_2* self);

/**
 * @brief Resets the wavegen_chirp instance
 *
 * @param self wavegen_2 instance
 */
void uz_wavegen_2_reset(uz_wavegen_2* self);



// saw-tooth -32768...+32767
int16_t uz_wavegen_sawtooth_return_int16(uz_wavegen_2* self);

// saw-tooth 0...65535
uint16_t uz_wavegen_sawtooth_return_uint16(uz_wavegen_2* self);

float uz_wavegen_sawtooth_return_float_with_offset_and_amplitude(uz_wavegen_2* self);
// saw-tooth -32768...+32767
int16_t uz_wavegen_sawtooth_sample_int16(uz_wavegen_2* self);

// saw-tooth 0...65535
uint16_t uz_wavegen_sawtooth_sample_uint16(uz_wavegen_2* self);

float uz_wavegen_sawtooth_sample_float_with_offset_and_amplitude(uz_wavegen_2* self);



int16_t uz_wavegen_triangle_return_int16(uz_wavegen_2* self);

int32_t uz_wavegen_triangle_return_int32(uz_wavegen_2* self);

float uz_wavegen_triangle_return_float_with_offset_and_amplitude(uz_wavegen_2* self);

int16_t uz_wavegen_triangle_sample_int16(uz_wavegen_2* self);

int32_t uz_wavegen_triangle_sample_int32(uz_wavegen_2* self);

int32_t uz_wavegen_triangle_sample_float_with_offset_and_amplitude(uz_wavegen_2* self);


float uz_wavegen_pulse_return_float(uz_wavegen_2* self);

float uz_wavegen_pulse_sample_float(uz_wavegen_2* self);

uint32_t uz_wavegen_pulse_return_uint32(uz_wavegen_2* self);

uint32_t uz_wavegen_pulse_sample_uint32(uz_wavegen_2* self);

void uz_wavegen_2_set_amplitude(uz_wavegen_2* self, float amplitude);

void uz_wavegen_2_set_offset(uz_wavegen_2* self, float offset);

void uz_wavegen_2_set_dutycycle(uz_wavegen_2* self, float dutycycle);

void uz_wavegen_2_set_low_high_pulse(uz_wavegen_2* self, float low_pulse, float high_pulse);

void uz_wavegen_2_set_frequency(uz_wavegen_2* self, float frequency_Hz);

void uz_wavegen_2_set_sample_time(uz_wavegen_2* self, float sample_time_s);

void uz_wavegen_2_set_phase_offset_norm(uz_wavegen_2* self, float offset_norm);

void uz_wavegen_2_set_phase_offset_deg(uz_wavegen_2* self, float offset_deg);

void uz_wavegen_2_set_phase_offset_rad(uz_wavegen_2* self, float offset_rad);

float uz_wavegen_2_return_phase_offset_norm(uz_wavegen_2* self);

float uz_wavegen_2_return_phase_offset_deg(uz_wavegen_2* self);

float uz_wavegen_2_return_phase_offset_rad(uz_wavegen_2* self);

void uz_wavegen_2_set_direction(uz_wavegen_2* self, wave_direction_t direction);
