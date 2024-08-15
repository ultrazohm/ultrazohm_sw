#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../main.h"

extern DS_Data Global_Data;

    const struct uz_PMSM_t Beckhoff_AM8141 = {
      .R_ph_Ohm = 0.51,
      .Ld_Henry = 0.002f,
      .Lq_Henry = 0.002f,
      .Psi_PM_Vs = 0.042f,
	  .polePairs = 4.0f,
	  .I_max_Ampere = 12.0f,
	  .J_kg_m_squared = 0.000108
    };//these parameters are only needed if linear decoupling is selected
    const struct uz_PI_Controller_config config_id_left = {
      .Kp = 5.0f,
      .Ki = 255.0f,
      .samplingTime_sec = 0.0001f,
      .upper_limit = 48.0f,
      .lower_limit = -48.0f
   };
   const struct uz_PI_Controller_config config_iq_left = {
      .Kp = 5.0f,
      .Ki = 255.0f,
      .samplingTime_sec = 0.0001f,
      .upper_limit = 48.0f,
      .lower_limit = -48.0f
   };
   const struct uz_PI_Controller_config config_speed_left = {
		   .Kp = 0.008f,
		   .Ki = 0.8f,
		   .samplingTime_sec = 0.0001f,
		   .upper_limit = 3.5f,
		   .lower_limit = -3.5f
   };

   const struct uz_SetPoint_config config_setpoint_left = {
		   .config_PMSM = Beckhoff_AM8141,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = SMPMSM,
		   .relative_torque_tolerance = 0.01f
   };

   const struct uz_SpeedControl_config config_speed_ctrl_left = {
		   .config_controller = config_speed_left
   };

   const struct uz_PI_Controller_config config_id_right = {
     .Kp = 5.0f,
     .Ki = 255.0f,
     .samplingTime_sec = 0.0001f,
     .upper_limit = 48.0f,
     .lower_limit = -48.0f
  };
  const struct uz_PI_Controller_config config_iq_right = {
     .Kp = 5.0f,
     .Ki = 255.0f,
     .samplingTime_sec = 0.0001f,
     .upper_limit = 48.0f,
     .lower_limit = -48.0f
  };

   struct uz_CurrentControl_config config_current_ctrl_left = {
      .config_PMSM = Beckhoff_AM8141,
	  .config_id = config_id_left,
	  .config_iq = config_iq_left,
	  .decoupling_select = no_decoupling,
	  .max_modulation_index = 0.57735 //=1.0f/sqrt(3.0f)
   };

   struct uz_CurrentControl_config config_current_ctrl_right = {
      .config_PMSM = Beckhoff_AM8141,
	  .config_id = config_id_right,
	  .config_iq = config_iq_right,
	  .decoupling_select = no_decoupling,
	  .max_modulation_index = 0.57735 //=1.0f/sqrt(3.0f)
   };

   uz_CurrentControl_t* current_ctrl_left_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_left));
   }

   uz_SetPoint_t* setpoint_ctrl_left_init(void) {
	   return(uz_SetPoint_init(config_setpoint_left));
   }

   uz_SpeedControl_t* speed_ctrl_left_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl_left));
   }

   uz_CurrentControl_t* current_ctrl_right_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_right));
   }
