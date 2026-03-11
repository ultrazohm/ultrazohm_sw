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

#ifndef ERROR_CHECKS_H_
#define ERROR_CHECKS_H_

#include "../globalData.h"
#include <stdint.h>

#define ERR_OVERVOLTAGE_DC   (1U << 0)
#define ERR_OVERCURRENT_U    (1U << 1)
#define ERR_OVERCURRENT_V    (1U << 2)
#define ERR_OVERCURRENT_W    (1U << 3)
#define ERR_OVERSPEED        (1U << 4)
#define ERR_NAN_OBSERVER     (1U << 5)
#define ERR_NAN_MEASUREMENT  (1U << 6)

typedef struct {
    float vdc_max;
    float iphase_max;
    float max_mechanical_speed_rpm;
} error_checks_config_t;

extern volatile uint32_t error_reason;

void error_checks_step(const actualValues *av, const error_checks_config_t *config);
void error_checks_report(uint32_t error_mask);

#endif /* ERROR_CHECKS_H_ */
