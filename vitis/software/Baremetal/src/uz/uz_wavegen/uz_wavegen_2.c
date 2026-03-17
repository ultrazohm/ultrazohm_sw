/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2026 Josef Knoblach
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "../uz_global_configuration.h"
#if UZ_WAVEGEN_2_MAX_INSTANCES > 0U
#include "uz_wavegen_2.h"
#include <math.h>
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_SystemTime/uz_SystemTime.h"

struct uz_wavegen_2 {
	bool is_ready;
	uint32_t phase;
	uint32_t phase_increment;
	uint32_t phase_offset;
	struct uz_wavegen_2_config config;
};
static uint32_t instance_counter = 0U;
static uz_wavegen_2 instances[UZ_WAVEGEN_2_MAX_INSTANCES] = { 0 };

static uz_wavegen_2* uz_wavegen_2_allocation(void);

static uz_wavegen_2* uz_wavegen_2_allocation(void){
	uz_assert(instance_counter < UZ_WAVEGEN_2_MAX_INSTANCES);
	uz_wavegen_2* self = &instances[instance_counter];
	uz_assert_false(self->is_ready);
	instance_counter++;
	self->is_ready = true;
	return (self);
}

void uz_wavegen_2_set_phase_increment(uz_wavegen_2* self) {
	uz_assert_not_NULL(self);
	if(self->config.wave_direction == WAVE_UP){
		self->phase_increment = (uint32_t)((self->config.frequency_Hz * 4294967296.0f) * self->config.sample_time_s);
	}
	else{
		self->phase_increment = ~((uint32_t)((self->config.frequency_Hz * 4294967296.0f) * self->config.sample_time_s))+1 ;	// als 2er-Komplement "negativ"
	}
}

void uz_wavegen_2_set_direction(uz_wavegen_2* self, wave_direction_t direction){
	self->config.wave_direction == direction;
	uz_wavegen_2_set_phase_increment(self);
}

uz_wavegen_2* uz_wavegen_2_init(struct uz_wavegen_2_config config) {
	uz_wavegen_2* self = uz_wavegen_2_allocation();
	uz_assert(config.amplitude != 0.0f);
	uz_assert(config.frequency_Hz >= 0.0f);
	self->phase = 0;
	self->config = config;
	uz_wavegen_2_set_phase_increment(self);

	return (self);
}



void uz_wavegen_2_reset(uz_wavegen_2* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->phase = 0;
}

// saw-tooth kompletter uint32_t bereich
uint32_t uz_wavegen_2_sample(uz_wavegen_2* self){
	self->phase += self->phase_increment;
	return self->phase;
}



// saw-tooth -32768...+32767
int16_t uz_wavegen_sawtooth_return_int16(uz_wavegen_2* self){
	return (int16_t)((self->phase+self->phase_offset) >> 16);
}

// saw-tooth 0...65535
uint16_t uz_wavegen_sawtooth_return_uint16(uz_wavegen_2* self){
	return (uint16_t)((self->phase+self->phase_offset) >> 16);
}

float uz_wavegen_sawtooth_return_float_with_offset_and_amplitude(uz_wavegen_2* self){
	float phase_norm = (float)(self->phase+self->phase_offset) / 4294967296.0f;
	return self->config.offset + self->config.amplitude * phase_norm;
}


// saw-tooth -32768...+32767
int16_t uz_wavegen_sawtooth_sample_int16(uz_wavegen_2* self){
	uz_wavegen_2_sample(self);
	return uz_wavegen_sawtooth_return_int16(self);
}

// saw-tooth 0...65535
uint16_t uz_wavegen_sawtooth_sample_uint16(uz_wavegen_2* self){
	uz_wavegen_2_sample(self);
	return uz_wavegen_sawtooth_return_uint16(self);
}

float uz_wavegen_sawtooth_sample_float_with_offset_and_amplitude(uz_wavegen_2* self){
	uz_wavegen_2_sample(self);
	return uz_wavegen_sawtooth_return_float_with_offset_and_amplitude(self);
}


/*
int16_t wavegen_dds_square(wavegen_dds_t *gen)
{
    return (gen->phase >> 31) ? 32767 : -32768;
}
*/

int16_t uz_wavegen_triangle_return_int16(uz_wavegen_2* self){
    return (int16_t)(((self->phase+self->phase_offset) >> 15) ^ (self->phase >> 31));
}

int32_t uz_wavegen_triangle_return_int32(uz_wavegen_2* self)
{
    // Triangle: MSB entscheidet auf-/absteigend
    return ((int32_t)((self->phase+self->phase_offset) ^ (self->phase & 0x80000000))) << 1;
}


// Alternativ offset und amplitude hier als übergabeparameter?
float uz_wavegen_triangle_return_float_with_offset_and_amplitude(uz_wavegen_2* self)
{
    // Phase normalisiert auf 0..1
    float phase_norm = (float)(self->phase+self->phase_offset) / 4294967296.0f; // 2^32
    // Triangle : 0..1..0
    float tri_norm = 1.0f - fabsf(phase_norm * 2.0f - 1.0f);
    // Auf -1..+1 zentrieren
    tri_norm = tri_norm * 2.0f - 1.0f;
    // Amplitude und Offset anwenden
    return self->config.offset + self->config.amplitude * tri_norm;
}

int16_t uz_wavegen_triangle_sample_int16(uz_wavegen_2* self){
	uz_wavegen_2_sample(self);
    return uz_wavegen_triangle_return_int16(self);
}

int32_t uz_wavegen_triangle_sample_int32(uz_wavegen_2* self)
{
	uz_wavegen_2_sample(self);
    return  uz_wavegen_triangle_return_int32(self);
}

int32_t uz_wavegen_triangle_sample_float_with_offset_and_amplitude(uz_wavegen_2* self)
{
	uz_wavegen_2_sample(self);
    return  uz_wavegen_triangle_return_float_with_offset_and_amplitude(self);
}



float uz_wavegen_pulse_return_float(uz_wavegen_2* self)
{
    uint32_t threshold = (uint32_t)(self->config.dutycycle * 4294967296.0f);
    return ((self->phase+self->phase_offset) < threshold) ? self->config.high_pulse : self->config.low_pulse;
}

float uz_wavegen_pulse_sample_float(uz_wavegen_2* self)
{
	uz_wavegen_2_sample(self);
    return uz_wavegen_pulse_return_float(self);
}

uint32_t uz_wavegen_pulse_return_uint32(uz_wavegen_2* self)
{
    uint32_t threshold = (uint32_t)(self->config.dutycycle * 4294967296.0f);
    return (uint32_t)( ((self->phase+self->phase_offset) < threshold) ? 1 : 0);
}

uint32_t uz_wavegen_pulse_sample_uint32(uz_wavegen_2* self)
{
	uz_wavegen_2_sample(self);
    return uz_wavegen_pulse_return_uint32(self);
}

void uz_wavegen_2_set_amplitude(uz_wavegen_2* self, float amplitude) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.amplitude = amplitude;
}

void uz_wavegen_2_set_offset(uz_wavegen_2* self, float offset) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.offset = offset;
}

void uz_wavegen_2_set_dutycycle(uz_wavegen_2* self, float dutycycle) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.dutycycle = dutycycle;
}

void uz_wavegen_2_set_low_high_pulse(uz_wavegen_2* self, float low_pulse, float high_pulse) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.low_pulse = low_pulse;
	self->config.high_pulse = high_pulse;
}

void uz_wavegen_2_set_frequency(uz_wavegen_2* self, float frequency_Hz) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.frequency_Hz = frequency_Hz;
	uz_wavegen_2_set_phase_increment(self);
}


void uz_wavegen_2_set_sample_time(uz_wavegen_2* self, float sample_time_s) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.sample_time_s = sample_time_s;
	uz_wavegen_2_set_phase_increment(self);
}




void uz_wavegen_2_set_phase_offset_norm(uz_wavegen_2* self, float offset_norm)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    // Wrap auf 0..1
	offset_norm -= (int)offset_norm;   // entfernt ganzzahligen Anteil

    if (offset_norm < 0.0f)
    	offset_norm += 1.0f;

    self->config.phase_offset_0_1 = offset_norm;
    self->phase_offset = (uint32_t)(offset_norm * 4294967296.0f); // 2^32
}

void uz_wavegen_2_set_phase_offset_deg(uz_wavegen_2* self, float offset_deg)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    float offset_norm = offset_deg / 360.0f;

    uz_wavegen_2_set_phase_offset_norm(self, offset_norm);
}



void uz_wavegen_2_set_phase_offset_rad(uz_wavegen_2* self, float offset_rad)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    float offset_norm = offset_rad / (2.0f * (float)M_PI);

    uz_wavegen_2_set_phase_offset_norm(self, offset_norm);
}

float uz_wavegen_2_return_phase_offset_norm(uz_wavegen_2* self){
	return self->config.phase_offset_0_1;
}

float uz_wavegen_2_return_phase_offset_deg(uz_wavegen_2* self){
	return self->config.phase_offset_0_1 * 360.0f;
}

float uz_wavegen_2_return_phase_offset_rad(uz_wavegen_2* self){
	return self->config.phase_offset_0_1 * (2.0f * (float)M_PI);
}

#endif
