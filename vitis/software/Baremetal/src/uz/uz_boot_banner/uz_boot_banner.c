/******************************************************************************
* Copyright 2026 Eyke Aufderheide
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

#include "uz_boot_banner.h"
#include "../uz_HAL.h"
#include <math.h>

void uz_print_control_frequency(float pwm_frequency_hz, float isr_samplerate_s)
{
    uz_assert(isr_samplerate_s > 0.0f);

    const unsigned pwm_khz   = (unsigned)lroundf(pwm_frequency_hz / 1000.0f);
    const unsigned isr_khz   = (unsigned)lroundf((1.0f / isr_samplerate_s) / 1000.0f);
    const unsigned period_us = (unsigned)lroundf(isr_samplerate_s * 1.0e6f);

    uz_printf("RPU: PWM frequency:    %u kHz\r\n", pwm_khz);
    uz_printf("RPU: Control ISR rate: %u kHz  (period %u us)\r\n", isr_khz, period_us);
}
