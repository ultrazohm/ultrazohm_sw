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


#include "uz_wavegen.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "../uz_HAL.h"
#include "../uz_SystemTime/uz_SystemTime.h"

float uz_wavegen_phase_acc_step(struct uz_wavegen_phase_acc* acc, float frequency_Hz) {
    uz_assert_not_NULL(acc);
    uz_assert(frequency_Hz > 0.0f);
    uint64_t t_now_us = uz_SystemTime_GetUptimeInUs();
    if (acc->is_first_call) {
        acc->t_prev_us = t_now_us;
        acc->phase = 0.0f;
        acc->is_first_call = false;
        return 0.0f;
    }
    uint64_t dt_us = t_now_us - acc->t_prev_us;
    acc->t_prev_us = t_now_us;
    float dt = (float)dt_us * 1.0e-6f;
    acc->phase += frequency_Hz * dt;
    acc->phase -= floorf(acc->phase);
    return acc->phase;
}

void uz_wavegen_phase_acc_reset(struct uz_wavegen_phase_acc* acc) {
    uz_assert_not_NULL(acc);
    acc->is_first_call = true;
    acc->t_prev_us = 0U;
    acc->phase = 0.0f;
}

float uz_wavegen_white_noise(float amplitude) {
	uz_assert(amplitude != 0.0f);
	return (amplitude * ( ((float)rand() / (float)RAND_MAX * 2.0f) - 1.0f) );
}
