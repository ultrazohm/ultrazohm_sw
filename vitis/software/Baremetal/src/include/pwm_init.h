#pragma once
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_0_to_5(void);
uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_6_to_11(void);
uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_12_to_17(void);
uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_18_to_23(void);

/** Update the minimum on-time in the PWM hardware register for the active 3-phase
 *  inverter instance (pin 0-5). Value is clamped to [0, 0.1] (duty cycle fraction). */
void pwm_set_min_pulse_width(float value);
