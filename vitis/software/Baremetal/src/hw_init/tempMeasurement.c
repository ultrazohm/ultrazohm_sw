#include "../include/tempMeasurement.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"


struct uz_PWM_duty_freq_detection_config_t config1 = {
    .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_1_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .linear_interpolation_parameters_t.a = -142.86f,
    .linear_interpolation_parameters_t.b = 146.43f
};

struct uz_PWM_duty_freq_detection_config_t config2 = {
    .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_2_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .linear_interpolation_parameters_t.a = -142.86f,
    .linear_interpolation_parameters_t.b = 146.43f
};

struct uz_PWM_duty_freq_detection_outputs_t outputs1 = {
    .PWMdutyCycNormalized = 0.0f,
    .TempDegreesCelsius = 0.0f,
    .PWMFreq = 0,
    .PWMhightime = 0,
    .PWMlowtime = 0,
};

struct uz_PWM_duty_freq_detection_outputs_t outputs2 = {
    .PWMdutyCycNormalized = 0.0f,
    .TempDegreesCelsius = 0.0f,
    .PWMFreq = 0,
    .PWMhightime = 0,
    .PWMlowtime = 0,
};


uz_PWM_duty_freq_detection_t* init_tempMeasurement1(void) {
	return(uz_PWM_duty_freq_detection_init(config1, outputs1));
}

uz_PWM_duty_freq_detection_t* init_tempMeasurement2(void) {
	return(uz_PWM_duty_freq_detection_init(config2, outputs2));
}

