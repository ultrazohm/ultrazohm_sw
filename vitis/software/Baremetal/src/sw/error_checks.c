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

void error_checks_report(uint32_t error_mask)
{
    if (error_mask != 0U) {
        error_reason |= error_mask;
        ultrazohm_state_machine_set_error(true);
    }
}

void error_checks_step(const actualValues *av, const error_checks_config_t *config)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(config);

    bool const nan_meas = !isfinite(av->U_DC) || !isfinite(av->I_U) ||
                          !isfinite(av->I_V) || !isfinite(av->I_W) ||
                          !isfinite(av->mechanicalRotorSpeed_filtered);
    bool const ov_dc = av->U_DC > config->vdc_max;
    bool const oc_iu = fabsf(av->I_U) > config->iphase_max;
    bool const oc_iv = fabsf(av->I_V) > config->iphase_max;
    bool const oc_iw = fabsf(av->I_W) > config->iphase_max;
    bool const overspeed = fabsf(av->mechanicalRotorSpeed_filtered) > config->max_mechanical_speed_rpm;

    uint32_t error_mask = 0U;
    if (ov_dc) {
        error_mask |= ERR_OVERVOLTAGE_DC;
    }
    if (oc_iu) {
        error_mask |= ERR_OVERCURRENT_U;
    }
    if (oc_iv) {
        error_mask |= ERR_OVERCURRENT_V;
    }
    if (oc_iw) {
        error_mask |= ERR_OVERCURRENT_W;
    }
    if (overspeed) {
        error_mask |= ERR_OVERSPEED;
    }
    if (nan_meas) {
        error_mask |= ERR_NAN_MEASUREMENT;
    }

    error_checks_report(error_mask);
}
