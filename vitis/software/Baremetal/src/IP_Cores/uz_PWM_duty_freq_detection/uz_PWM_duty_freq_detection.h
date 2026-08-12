#ifndef UZ_PWM_DUTY_FREQ_DETECTION_H
#define UZ_PWM_DUTY_FREQ_DETECTION_H

#include <stdint.h>

typedef struct uz_PWM_duty_freq_detection_t uz_PWM_duty_freq_detection_t;

struct uz_PWM_duty_freq_detection_config_t {
    uint32_t base_address;
    uint32_t ip_clk_frequency_Hz;
};

uz_PWM_duty_freq_detection_t *uz_PWM_duty_freq_detection_init(struct uz_PWM_duty_freq_detection_config_t config);
float uz_PWM_duty_freq_detection_get_frequency_in_Hz(uz_PWM_duty_freq_detection_t *self);

/** Returns the duty-cycle ratio in the range 0.0 to 1.0. */
float uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(uz_PWM_duty_freq_detection_t *self);

#endif
