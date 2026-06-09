/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel, Tobias Schindler
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
#if UZ_WAVEGEN_SAWTOOTH_MAX_INSTANCES > 0U
#include "uz_wavegen.h"
#include <stdint.h>
#include "../uz_HAL.h"

struct uz_wavegen_sawtooth {
    bool is_ready;
    struct uz_wavegen_phase_acc acc;
};

static uint32_t instance_counter = 0U;
static uz_wavegen_sawtooth_t instances[UZ_WAVEGEN_SAWTOOTH_MAX_INSTANCES] = { 0 };

static uz_wavegen_sawtooth_t* uz_wavegen_sawtooth_allocation(void);
static float uz_wavegen_sawtooth_sample_impl(uz_wavegen_sawtooth_t* self, float amplitude, float frequency_Hz, float offset);

static uz_wavegen_sawtooth_t* uz_wavegen_sawtooth_allocation(void) {
    uz_assert(instance_counter < UZ_WAVEGEN_SAWTOOTH_MAX_INSTANCES);
    uz_wavegen_sawtooth_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return self;
}

static float uz_wavegen_sawtooth_sample_impl(uz_wavegen_sawtooth_t* self, float amplitude, float frequency_Hz, float offset) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(frequency_Hz > 0.0f);
    uz_assert(amplitude != 0.0f);
    float phase = uz_wavegen_phase_acc_step(&self->acc, frequency_Hz);
    return amplitude * phase + offset;
}

uz_wavegen_sawtooth_t* uz_wavegen_sawtooth_init(void) {
    uz_wavegen_sawtooth_t* self = uz_wavegen_sawtooth_allocation();
    uz_wavegen_phase_acc_reset(&self->acc);
    return self;
}

float uz_wavegen_sawtooth_sample(uz_wavegen_sawtooth_t* self, float amplitude, float frequency_Hz) {
    return uz_wavegen_sawtooth_sample_impl(self, amplitude, frequency_Hz, 0.0f);
}

float uz_wavegen_sawtooth_sample_with_offset(uz_wavegen_sawtooth_t* self, float amplitude, float frequency_Hz, float offset) {
    return uz_wavegen_sawtooth_sample_impl(self, amplitude, frequency_Hz, offset);
}

void uz_wavegen_sawtooth_reset(uz_wavegen_sawtooth_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_wavegen_phase_acc_reset(&self->acc);
}

#endif
