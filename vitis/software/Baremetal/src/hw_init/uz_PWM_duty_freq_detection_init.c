#include "../include/uz_PWM_duty_freq_detection_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

 // config struct
 struct uz_PWM_duty_freq_detection_config_t config_VSI_1 = {
     .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_1_BASEADDR,
     .ip_clk_frequency_Hz = 100000000,
     .linear_interpolation_parameters_t.a = -142.86f,
     .linear_interpolation_parameters_t.b = 146.43f
 };

 // output struct
 struct uz_PWM_duty_freq_detection_outputs_t outputs_VSI_1 = {
     .PWMdutyCycNormalized = 0.0f,
     .TempDegreesCelsius = 0.0f,
     .PWMFreq = 0,
     .PWMhightime = 0,
     .PWMlowtime = 0,
 };
 //DIG_IO_16 inverter1
 //DIG_IO_17 inverter2
 // config struct
 struct uz_PWM_duty_freq_detection_config_t config_VSI_2 = {
     .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_2_BASEADDR,
     .ip_clk_frequency_Hz = 100000000,
     .linear_interpolation_parameters_t.a = -142.86f,
     .linear_interpolation_parameters_t.b = 146.43f
 };

 // output struct
 struct uz_PWM_duty_freq_detection_outputs_t outputs_VSI_2 = {
     .PWMdutyCycNormalized = 0.0f,
     .TempDegreesCelsius = 0.0f,
     .PWMFreq = 0,
     .PWMhightime = 0,
     .PWMlowtime = 0,
 };

 uz_PWM_duty_freq_detection_t* initialize_PWM_duty_freq_detection_VSI_1(void) {
	 return(uz_PWM_duty_freq_detection_init(config_VSI_1, outputs_VSI_1));
 }

 uz_PWM_duty_freq_detection_t* initialize_PWM_duty_freq_detection_VSI_2(void) {
	 return(uz_PWM_duty_freq_detection_init(config_VSI_2, outputs_VSI_2));
 }
