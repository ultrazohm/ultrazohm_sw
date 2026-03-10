/******************************************************************************
 * Copyright 2026
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

#include "../include/measurement_calibration.h"
#include "../uz/uz_HAL.h"

measurement_calibration_t measurement_calibration_init(uint32_t sample_counter_stop, float u_dc_offset)
{
    uz_assert(sample_counter_stop > 0U);
    return (measurement_calibration_t){
        .done = false,
        .sample_counter = 0U,
        .sample_counter_stop = sample_counter_stop,
        .total_u = 0.0,
        .total_v = 0.0,
        .total_w = 0.0,
        .i_u_offset = 0.0f,
        .i_v_offset = 0.0f,
        .i_w_offset = 0.0f,
        .u_dc_offset = u_dc_offset
    };
}

void measurement_calibration_step(measurement_calibration_t *state, const AnalogAdapters *aa, actualValues *av)
{
    uz_assert_not_NULL(state);
    uz_assert_not_NULL(aa);
    uz_assert_not_NULL(av);

    if (!state->done) {
        state->total_u += (double)aa->A1.me.ADC_A1;
        state->total_v += (double)aa->A1.me.ADC_A2;
        state->total_w += (double)aa->A1.me.ADC_A3;

        state->sample_counter++;
        if (state->sample_counter == state->sample_counter_stop) {
            state->i_u_offset = (float)(state->total_u / (double)state->sample_counter_stop);
            state->i_v_offset = (float)(state->total_v / (double)state->sample_counter_stop);
            state->i_w_offset = (float)(state->total_w / (double)state->sample_counter_stop);
            state->done = true;
        }
    }

    av->U_DC = aa->A1.me.ADC_A4 - state->u_dc_offset;
    av->I_U = aa->A1.me.ADC_A1 - state->i_u_offset;
    av->I_V = aa->A1.me.ADC_A2 - state->i_v_offset;
    av->I_W = aa->A1.me.ADC_A3 - state->i_w_offset;
}
