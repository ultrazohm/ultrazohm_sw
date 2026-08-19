#include "../include/uz_foc_init.h"
#include <math.h>
#include "../main.h"
#include "../uz/uz_PMSM_config/uz_PMSM_config.h"


const struct uz_PMSM_t config_PMSM = {
	      .Ld_Henry = 0.0072F,
	      .Lq_Henry = 0.0072F,
	      .Psi_PM_Vs = 0.1423f,
		  .R_ph_Ohm=1.8f,
		  .polePairs=4,
		  .I_max_Ampere = 15.0f,
		  .J_kg_m_squared = 0.000875F
	    };//these parameters are only needed if linear decoupling is selected

uz_CurrentControl_t* init_uz_foc(void) {


	    struct uz_PI_Controller_config config_id = {
	      .type = UZ_PI_PARALLEL,
	      .Kp = 0.0072F/(2.0f*1.0f/UZ_PWM_FREQUENCY),
	      .Ki = 1.8f/(2.0f*1.0f/UZ_PWM_FREQUENCY),
	      .samplingTime_sec = 0.0001f
	   };
	   struct uz_PI_Controller_config config_iq = {
	   	  .type = UZ_PI_PARALLEL,
	      .Kp =  0.0072F/(2.0f*1.0f/UZ_PWM_FREQUENCY),
	      .Ki = 1.8f/(2.0f*1.0f/UZ_PWM_FREQUENCY),
	      .samplingTime_sec = 0.0001f
	   };
	   struct uz_CurrentControl_config CC_config = {
	      .decoupling_select = no_decoupling,
	      .Kp_adjustment_flag = false,
	      .config_PMSM = config_PMSM,
	      .config_id = config_id,
	      .config_iq = config_iq,
	      .max_modulation_index = 1.0f / sqrtf(3.0f)
	   };

	   uz_CurrentControl_t* CC_instance = uz_CurrentControl_init(CC_config);
	   return CC_instance;
}

const struct uz_PI_Controller_config config_speed = {
			.type = UZ_PI_PARALLEL,
		   .Kp = 0.2f,
		   .Ki = 2.0f,
		   .samplingTime_sec = 0.0001f,
		   .upper_limit = 6.0f,
		   .lower_limit = -6.0f
  };

const struct uz_SetPoint_config config_setpoint = {
		   .config_PMSM = config_PMSM,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = SMPMSM,
		   .relative_torque_tolerance = 0.01f
 };

const struct uz_SpeedControl_config config_speed_ctrl = {
		   .config_controller = config_speed
};


uz_SpeedControl_t* speed_ctrl_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl));
}
uz_SetPoint_t* setpoint_ctrl_init(void) {
	   return(uz_SetPoint_init(config_setpoint));
 }
