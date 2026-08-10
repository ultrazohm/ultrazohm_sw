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

#include "../include/error_checks.h"
#include "../include/uz_platform_state_machine.h"
#include "../uz/uz_HAL.h"
#include <math.h>
#include <stdbool.h>

volatile uint32_t error_reason = 0U;
float js_error_max_current_im = 0.0f;
float js_error_vdc_im = 0.0f;
float js_error_vdc_va = 0.0f;
float js_error_max_current_va = 0.0f;
float js_error_nan_observer = 0.0f;
float js_error_nan_measurement = 0.0f;

static void error_checks_update_visualization_latches(uint32_t error_mask)
{
    if ((error_mask & (ERR_IM_OVERCURRENT_U | ERR_IM_OVERCURRENT_V | ERR_IM_OVERCURRENT_W)) != 0U) {
        js_error_max_current_im = 1.0f;
    }
    if ((error_mask & (ERR_IM_OVERVOLTAGE_DC | ERR_IM_UNDERVOLTAGE_DC)) != 0U) {
        js_error_vdc_im = 1.0f;
    }
    if ((error_mask & ERR_VA_OVERVOLTAGE_DC) != 0U) {
        js_error_vdc_va = 1.0f;
    }
    if ((error_mask & (ERR_VA_OVERCURRENT_U | ERR_VA_OVERCURRENT_V | ERR_VA_OVERCURRENT_W)) != 0U) {
        js_error_max_current_va = 1.0f;
    }
    if ((error_mask & ERR_NAN_OBSERVER) != 0U) {
        js_error_nan_observer = 1.0f;
    }
    if ((error_mask & ERR_NAN_MEASUREMENT) != 0U) {
        js_error_nan_measurement = 1.0f;
    }
}

void error_checks_report(uint32_t error_mask)
{
    if (error_mask != 0U) {
        error_reason |= error_mask;
        error_checks_update_visualization_latches(error_mask);
        ultrazohm_state_machine_set_error(true);
    }
}

uint32_t error_checks_step(const actualValues *av, const error_checks_config_t *config)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(config);

    bool const nan_meas = !isfinite(av->IM_vdc) || !isfinite(av->IM_ia) ||
                          !isfinite(av->IM_ib) || !isfinite(av->IM_ic) ||
                          !isfinite(av->IM_mechanicalRotorSpeed_filtered);
    bool const im_uv_dc = av->IM_vdc < config->im_vdc_min;
    bool const im_ov_dc = av->IM_vdc > config->im_vdc_max;
    bool const im_oc_iu = fabsf(av->IM_ia) > config->im_iphase_max;
    bool const im_oc_iv = fabsf(av->IM_ib) > config->im_iphase_max;
    bool const im_oc_iw = fabsf(av->IM_ic) > config->im_iphase_max;
    bool const im_overspeed = fabsf(av->IM_mechanicalRotorSpeed_filtered) > config->im_max_mechanical_speed_rpm;
    bool const va_ov_dc = av->VA_vdc > config->va_vdc_max;
    bool const va_oc_iu = fabsf(av->VA_ia) > config->va_iphase_max;
    bool const va_oc_iv = fabsf(av->VA_ib) > config->va_iphase_max;
    bool const va_oc_iw = fabsf(av->VA_ic) > config->va_iphase_max;

    uint32_t error_mask = 0U;
    if (im_uv_dc) {
        error_mask |= ERR_IM_UNDERVOLTAGE_DC;
    }
    if (im_ov_dc) {
        error_mask |= ERR_IM_OVERVOLTAGE_DC;
    }
    if (im_oc_iu) {
        error_mask |= ERR_IM_OVERCURRENT_U;
    }
    if (im_oc_iv) {
        error_mask |= ERR_IM_OVERCURRENT_V;
    }
    if (im_oc_iw) {
        error_mask |= ERR_IM_OVERCURRENT_W;
    }
    if (im_overspeed) {
        error_mask |= ERR_IM_OVERSPEED;
    }
    if (va_ov_dc) {
        error_mask |= ERR_VA_OVERVOLTAGE_DC;
    }
    if (va_oc_iu) {
        error_mask |= ERR_VA_OVERCURRENT_U;
    }
    if (va_oc_iv) {
        error_mask |= ERR_VA_OVERCURRENT_V;
    }
    if (va_oc_iw) {
        error_mask |= ERR_VA_OVERCURRENT_W;
    }
    if (nan_meas) {
        error_mask |= ERR_NAN_MEASUREMENT;
    }

    error_checks_report(error_mask);
    return error_mask;
}

bool error_checks_trip_pending(void)
{
    return (error_reason != 0U);
}

void error_checks_reset(void)
{
    error_reason = 0U;
    js_error_max_current_im = 0.0f;
    js_error_vdc_im = 0.0f;
    js_error_vdc_va = 0.0f;
    js_error_max_current_va = 0.0f;
    js_error_nan_observer = 0.0f;
    js_error_nan_measurement = 0.0f;
}
