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

#ifndef MEASUREMENT_CALIBRATION_H_
#define MEASUREMENT_CALIBRATION_H_

#include "../globalData.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool done;
    uint32_t sample_counter;
    uint32_t sample_counter_stop;
    double total_u;
    double total_v;
    double total_w;
    float i_u_offset;
    float i_v_offset;
    float i_w_offset;
    float u_dc_offset;
} measurement_calibration_t;

measurement_calibration_t measurement_calibration_init(uint32_t sample_counter_stop, float u_dc_offset);
void measurement_calibration_step(measurement_calibration_t *state, const AnalogAdapters *aa, actualValues *av);

#endif /* MEASUREMENT_CALIBRATION_H_ */
