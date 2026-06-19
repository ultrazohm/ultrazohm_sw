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

#ifndef UZ_BOOT_BANNER_H_
#define UZ_BOOT_BANNER_H_

/**
 * @brief Print the configured PWM frequency and control-ISR rate on UART.
 *
 * @param pwm_frequency_hz  PWM switching frequency in Hz.
 * @param isr_samplerate_s  Control-ISR period in seconds (reciprocal of the ISR rate).
 *
 * Formatted as integer kHz + integer microseconds because xil_printf
 * (the backend of uz_printf) has no %f support.
 */
void uz_print_control_frequency(float pwm_frequency_hz, float isr_samplerate_s);

#endif /* UZ_BOOT_BANNER_H_ */
