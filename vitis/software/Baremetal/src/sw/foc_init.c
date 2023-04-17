#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"

    const struct uz_PMSM_t Beckhoff_AM8141 = {
      .R_ph_Ohm = 0.45,
      .Ld_Henry = 0.00175f,
      .Lq_Henry = 0.00175f,
      .Psi_PM_Vs = 0.035f,
	  .polePairs = 4.0f,
	  .I_max_Ampere = 12.0f
    };//these parameters are only needed if linear decoupling is selected
    const struct uz_PI_Controller_config config_id_d1 = {
      .Kp = 4.4f,
      .Ki = 250.0f,
      .samplingTime_sec = 0.0001f,
      .upper_limit = 48.0f,
      .lower_limit = -48.0f
   };
   const struct uz_PI_Controller_config config_iq_d1 = {
      .Kp = 4.4f,
      .Ki = 250.0f,
      .samplingTime_sec = 0.0001f,
      .upper_limit = 48.0f,
      .lower_limit = -48.0f
   };
   const struct uz_PI_Controller_config config_speed_d1 = {
		   .Kp = 0.02f,
		   .Ki = 2.0f,
		   .samplingTime_sec = 0.0001f,
		   .upper_limit = 12.0f,
		   .lower_limit = -12.0f
   };

   const struct uz_SetPoint_config config_setpoint_d1 = {
		   .config_PMSM = Beckhoff_AM8141,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = SMPMSM
   };

   const struct uz_SpeedControl_config config_speed_ctrl_d1 = {
		   .config_controller = config_speed_d1
   };

   const struct uz_PI_Controller_config config_id_d2 = {
     .Kp = 4.4f,
     .Ki = 250.0f,
     .samplingTime_sec = 0.00005f,
     .upper_limit = 48.0f,
     .lower_limit = -48.0f
  };
  const struct uz_PI_Controller_config config_iq_d2 = {
     .Kp = 4.4f,
     .Ki = 250.0f,
     .samplingTime_sec = 0.00005f,
     .upper_limit = 48.0f,
     .lower_limit = -48.0f
  };

   struct uz_CurrentControl_config config_current_ctrl_d1 = {
      .config_PMSM = Beckhoff_AM8141,
	  .config_id = config_id_d1,
	  .config_iq = config_iq_d1,
	  .decoupling_select = no_decoupling,
	  .max_modulation_index = 1.0f/sqrt(3.0f)
   };

   struct uz_CurrentControl_config config_current_ctrl_d2 = {
      .config_PMSM = Beckhoff_AM8141,
	  .config_id = config_id_d2,
	  .config_iq = config_iq_d2,
	  .decoupling_select = no_decoupling,
	  .max_modulation_index = 1.0f/sqrt(3.0f)
   };

   uz_CurrentControl_t* current_ctrl_d1_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_d1));
   }

   uz_SetPoint_t* setpoint_ctrl_d1_init(void) {
	   return(uz_SetPoint_init(config_setpoint_d1));
   }

   uz_SpeedControl_t* speed_ctrl_d1_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl_d1));
   }

   uz_CurrentControl_t* current_ctrl_d2_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_d2));
   }


