#include "uz_BLDC_control.h"
#include <stdlib.h>
#include "../uz_global_configuration.h" // probably needed for the instances
#include <assert.h>
#include <math.h> // for fmodf, M_PI
#include "../uz_piController/uz_piController.h"
#include "../../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz_Trajectory/uz_Trajectory.h"


// External tristate driver
extern void uz_PWM_SS_2L_set_tristate(uz_PWM_SS_2L_t* pwm_handle, bool a, bool b, bool c);
// Define struct
struct uz_BLDC_control {
   bool is_ready;
   float duty_a;
   float duty_b;
   float duty_c;

   float n_RPM_error; //@
   float I_ph_error; //@
   float i_ref_kaskade; //@
   float u_BLDC_ref; //@

   struct uz_PI_Controller* PI_current_mode;
   struct uz_PI_Controller* PI_speed_mode;
   struct uz_PI_Controller* PI_speed_only_mode;

};

static uz_BLDC_control instances[UZ_BLDC_CONTROL_MAX_INSTANCES];
static int instance_count = 0;
// Initialization
uz_BLDC_control* uz_BLDC_control_init(struct uz_BLDC_control_config config) {
   assert(instance_count < UZ_BLDC_CONTROL_MAX_INSTANCES);
   uz_BLDC_control* self = &instances[instance_count++];
   self->is_ready = true;
   self->duty_a = 0.0f;
   self->duty_b = 0.0f;
   self->duty_c = 0.0f;

   self->n_RPM_error = 0.0f; //@
   self->I_ph_error = 0.0f; //@
   self->i_ref_kaskade = 0.0f; //@
   self->u_BLDC_ref = 0.0f; //@

   self->PI_current_mode = uz_PI_Controller_init(config.config_PI_current);
   self->PI_speed_mode = uz_PI_Controller_init(config.config_PI_speed);
   self->PI_speed_only_mode = uz_PI_Controller_init(config.config_PI_speed_only);

   (void)config;
   return self;
}
// Sector-based assignment of duty cycle, put here PI controllers, put the extra inputs, put arrows -> self...
void uz_BLDC_control_sample(uz_BLDC_control* self, int sector, float U_ctrl_ref, uz_PWM_SS_2L_t* pwm_handle, float n_ref_rpm, float n_act_rpm, float I_ph_ref, float I_ph_m, float U_ZK, bool SpeedControl, bool CurrentControl, bool CascadeControl, bool DutyCycleControl) {
   assert(self != NULL);
   assert(self->is_ready);

   float speed_RPM_error; //
   float current_error; //
   float i_ref_Cascade; //
   float d_BLDC; //
   float u_ref; //



	if(SpeedControl){
		//***Speed Control (Speed -> Control Voltage)
		speed_RPM_error = n_ref_rpm - n_act_rpm;
		u_ref = uz_PI_Controller_sample(self->PI_speed_only_mode, n_ref_rpm, n_act_rpm, false);

		self->n_RPM_error = speed_RPM_error;
		self->u_BLDC_ref = u_ref;
	}

	else if(CurrentControl){
		// ***Current Control (Current -> Control Voltage)
		current_error = I_ph_ref - I_ph_m;
		u_ref = uz_PI_Controller_sample(self->PI_current_mode, I_ph_ref, I_ph_m, false);

		self->I_ph_error = current_error;
		self->u_BLDC_ref = u_ref;
	}

	else if(CascadeControl){
		//Cascade Speed-Current-Controllers (Speed -> Current -> Control Voltage)
		speed_RPM_error = n_ref_rpm - n_act_rpm;
		i_ref_Cascade = uz_PI_Controller_sample(self->PI_speed_mode, n_ref_rpm, n_act_rpm, false);
		current_error = i_ref_Cascade - I_ph_m;
		u_ref = uz_PI_Controller_sample(self->PI_current_mode, i_ref_Cascade, I_ph_m, false);

		self->n_RPM_error = speed_RPM_error;
		self->I_ph_error = current_error;
		self->i_ref_kaskade = i_ref_Cascade;
		self->u_BLDC_ref = u_ref;
	}

	else if(DutyCycleControl){
		u_ref = U_ctrl_ref;

		self->u_BLDC_ref = u_ref;
	}

	// Now we normalize the control voltage from the current PI controller by dividing it by U_ZK
	d_BLDC = 2*fabs(u_ref)/U_ZK;

	// Duty Cycle value saturation (between 0 and 1)
	if (d_BLDC > 1.0f)
	    d_BLDC = 1.0f;
	else if(d_BLDC < 0.0f){
	    d_BLDC = 0.0f;
	}

   float d_a = 0.0f;
   float d_b = 0.0f;
   float d_c = 0.0f;
// ----------------------------------------------------- Commutation Sequence -----------------------------------------

   // ---------------------------------- Start Commutation Scheme OLD -------------------------------------------
   if (sector == 1) {
       d_a = 0; // AL
       d_c = d_BLDC; //CH
       if (u_ref < 0.0f) {
           d_a = d_BLDC; // AH
           d_c = 0; // CL
       }
       uz_PWM_SS_2L_set_tristate(pwm_handle, false, true, false);
   }
   else if (sector == 2) {
       d_b = 0;
       d_c = d_BLDC;
       if (u_ref < 0.0f) {
           d_b = d_BLDC;
           d_c = 0;
       }
       uz_PWM_SS_2L_set_tristate(pwm_handle, true, false, false);
   }
   else if (sector == 3) {
       d_a = d_BLDC;
       d_b = 0;
       if (u_ref < 0.0f) {
           d_a = 0;
           d_b = d_BLDC;
       }
       uz_PWM_SS_2L_set_tristate(pwm_handle, false, false, true);
   }
   else if (sector == 4) {
       d_a = d_BLDC;
       d_c = 0;
       if (u_ref < 0.0f) {
           d_a = 0;
           d_c = d_BLDC;
       }
       uz_PWM_SS_2L_set_tristate(pwm_handle, false, true, false);
   }
   else if (sector == 5) {
       d_b = d_BLDC;
       d_c = 0;
       if (u_ref < 0.0f) {
           d_b = 0;
           d_c = d_BLDC;
       }
       uz_PWM_SS_2L_set_tristate(pwm_handle, true, false, false);
   }
   else if (sector == 6) {
       d_a = 0;
       d_b = d_BLDC;
       if (u_ref < 0.0f) {
           d_a = d_BLDC;
           d_b = 0;
       }
       uz_PWM_SS_2L_set_tristate(pwm_handle, false, false, true);
   }

   // ---------------------------------- End Commutation Scheme -------------------------------------------


// ----------------------------------------------------- Commutation Sequence -----------------------------------------

   self->duty_a = d_a;
   self->duty_b = d_b;
   self->duty_c = d_c;
}

// Here we get/assign our duty cycles to getter functions
float uz_BLDC_control_get_duty_a(uz_BLDC_control* self) {
   assert(self != NULL);
   return self->duty_a;
}
float uz_BLDC_control_get_duty_b(uz_BLDC_control* self) {
   assert(self != NULL);
   return self->duty_b;
}
float uz_BLDC_control_get_duty_c(uz_BLDC_control* self) {
   assert(self != NULL);
   return self->duty_c;
}

float uz_BLDC_control_get_n_RPM_error(uz_BLDC_control* self) {
    assert(self != NULL);
    return self->n_RPM_error;
}

float uz_BLDC_control_get_I_ph_error(uz_BLDC_control* self) {
    assert(self != NULL);
    return self->I_ph_error;
}

float uz_BLDC_control_get_i_ref_kaskade(uz_BLDC_control* self) {
    assert(self != NULL);
    return self->i_ref_kaskade;
}

float uz_BLDC_control_get_u_BLDC_ref(uz_BLDC_control* self) {
    assert(self != NULL);
    return self->u_BLDC_ref;
}
// -------------------------------------------------------------------------

// Get commutation sector from electrical angle
int getSectorFromThetaEl(float theta_el_rad) {
   int sector = 0;
   float UZ_PIf = M_PI;
   //theta_el_rad = - theta_el_rad;
   if (theta_el_rad < 0.0f) {
       theta_el_rad += 2.0f * UZ_PIf;
   }
   theta_el_rad = fmodf(theta_el_rad, 2.0f * UZ_PIf);
   if (theta_el_rad >= 0 && theta_el_rad < UZ_PIf / 3.0f) {
       sector = 1;
   }
   else if (theta_el_rad >= UZ_PIf/3.0f && theta_el_rad < 2.0f*UZ_PIf/3.0f) {
       sector = 2;
   }
   else if (theta_el_rad >= 2.0f*UZ_PIf/3.0f && theta_el_rad < UZ_PIf) {
       sector = 3;
   }
   else if (theta_el_rad >= UZ_PIf && theta_el_rad < 4.0f*UZ_PIf/3.0f) {
       sector = 4;
   }
   else if (theta_el_rad >= 4.0f*UZ_PIf/3.0f && theta_el_rad < 5.0f*UZ_PIf/3.0f) {
       sector = 5;
   }
   else if (theta_el_rad >= 5.0f*UZ_PIf/3.0f && theta_el_rad < 2.0f*UZ_PIf) {
       sector = 6;
   }
   else {
       sector = 1; // fallback
   }
   return sector;
}
// Select active phase current based on sector (we select the HIGH/incoming/positive current based on which sector we are in)

float i_ph_current_selector(int sector, float i_a, float i_b, float i_c) {
   float i_out = 0.0f;
   if (sector == 1) {
       i_out = i_c;
   }
   else if (sector == 2) {
       i_out = i_c;
   }
   else if (sector == 3) {
          i_out = i_a;
      }
   else if (sector == 4) {
          i_out = i_a;
      }
   else if (sector == 5) {
       i_out = i_b;
   }
   else if (sector == 6) {
       i_out = i_b;
   }
   return i_out;
}
