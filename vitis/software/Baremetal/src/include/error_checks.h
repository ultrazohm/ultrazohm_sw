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
#include <stdbool.h>
#include <stdint.h>

#define ERR_IM_OVERVOLTAGE_DC   (1U << 0)
#define ERR_IM_OVERCURRENT_U    (1U << 1)
#define ERR_IM_OVERCURRENT_V    (1U << 2)
#define ERR_IM_OVERCURRENT_W    (1U << 3)
#define ERR_IM_OVERSPEED        (1U << 4)
#define ERR_NAN_OBSERVER        (1U << 5)
#define ERR_NAN_MEASUREMENT     (1U << 6)
#define ERR_VA_OVERVOLTAGE_DC   (1U << 7)
#define ERR_VA_OVERCURRENT_U    (1U << 8)
#define ERR_VA_OVERCURRENT_V    (1U << 9)
#define ERR_VA_OVERCURRENT_W    (1U << 10)
#define ERR_IM_UNDERVOLTAGE_DC  (1U << 11)

#define ERR_OVERVOLTAGE_DC ERR_IM_OVERVOLTAGE_DC
#define ERR_UNDERVOLTAGE_DC ERR_IM_UNDERVOLTAGE_DC
#define ERR_OVERCURRENT_U  ERR_IM_OVERCURRENT_U
#define ERR_OVERCURRENT_V  ERR_IM_OVERCURRENT_V
#define ERR_OVERCURRENT_W  ERR_IM_OVERCURRENT_W
#define ERR_OVERSPEED      ERR_IM_OVERSPEED

typedef struct {
    float im_vdc_min;
    float im_vdc_max;
    float im_iphase_max;
    float im_max_mechanical_speed_rpm;
    float va_vdc_max;
    float va_iphase_max;
} error_checks_config_t;

extern volatile uint32_t error_reason;
extern float js_error_max_current_im;
extern float js_error_vdc_im;
extern float js_error_vdc_va;
extern float js_error_max_current_va;
extern float js_error_nan_observer;
extern float js_error_nan_measurement;

uint32_t error_checks_step(const actualValues *av, const error_checks_config_t *config);
void error_checks_report(uint32_t error_mask);
bool error_checks_trip_pending(void);
void error_checks_reset(void);

#endif /* ERROR_CHECKS_H_ */
