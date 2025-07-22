#ifndef UZ_BLDC_CONTROL_H
#define UZ_BLDC_CONTROL_H
#include <stdbool.h>

#include "../uz_piController/uz_piController.h"
#include "../../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

// Forward declaration (so that pointers point to this before declaration, prob not necessaey since I defined the full struct in .c)
typedef struct uz_BLDC_control uz_BLDC_control;
// Config struct (currently empty)


struct uz_BLDC_control_config{

	// here we include the 3 pi controller configs and structure

	struct uz_PI_Controller_config config_PI_current;
	struct uz_PI_Controller_config config_PI_speed;
	struct uz_PI_Controller_config config_PI_speed_only;

};



// Initialization
uz_BLDC_control* uz_BLDC_control_init(struct uz_BLDC_control_config config);
// Here we update duty cycle based on sector and reference voltage
void uz_BLDC_control_sample(uz_BLDC_control* self, int sector, float U_ctrl_ref, uz_PWM_SS_2L_t* pwm_handle, float n_ref_rpm, float n_act_rpm, float I_ph_ref, float I_ph_m, float U_ZK, bool SpeedControl, bool CurrentControl, bool CascadeControl, bool DutyCycleControl);
// Here we get the Duty cycle values
float uz_BLDC_control_get_duty_a(uz_BLDC_control* self);
float uz_BLDC_control_get_duty_b(uz_BLDC_control* self);
float uz_BLDC_control_get_duty_c(uz_BLDC_control* self);

// Here we get the PI inputs and outputs
float uz_BLDC_control_get_n_RPM_error(uz_BLDC_control* self);
float uz_BLDC_control_get_I_ph_error(uz_BLDC_control* self);
float uz_BLDC_control_get_i_ref_kaskade(uz_BLDC_control* self);
float uz_BLDC_control_get_u_BLDC_ref(uz_BLDC_control* self);

// Utility functions
int getSectorFromThetaEl(float theta_el_rad);
float i_ph_current_selector(int sector, float i_a, float i_b, float i_c);
#endif // UZ_BLDC_CONTROL_H
