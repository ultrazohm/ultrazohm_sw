#include "../main.h"
#include "../include/pi_foc.h"

extern DS_Data Global_Data;

    const struct uz_PMSM_t Beckhoff_AM8141 = {
      .R_ph_Ohm = 0.57,
      .Ld_Henry = 0.002f,
      .Lq_Henry = 0.002f,
      .Psi_PM_Vs = 0.040f, // LLeff bei 1000rpm mit Multimeter: 20,77 V
	  .polePairs = 4.0f,
	  .I_max_Ampere = 20.0f,
	  .J_kg_m_squared = 0.000108
    };//these parameters are only needed if linear decoupling is selected
    const struct uz_PI_Controller_config config_id_left = {
      .type = parallel,
	  .Kp = Beckhoff_AM8141.Ld_Henry/(2.0f*1.0f/UZ_PWM_FREQUENCY_ISR),
      .Ki = Beckhoff_AM8141.R_ph_Ohm/(2.0f*1.0f/UZ_PWM_FREQUENCY_ISR),
      .samplingTime_sec = 1/UZ_PWM_FREQUENCY_ISR,
      .upper_limit = 48.0f,
      .lower_limit = -48.0f
   };
   const struct uz_PI_Controller_config config_iq_left = {
	  .type = parallel,
	  .Kp = Beckhoff_AM8141.Lq_Henry/(2.0f*1.0f/UZ_PWM_FREQUENCY_ISR),
      .Ki = Beckhoff_AM8141.R_ph_Ohm/(2.0f*1.0f/UZ_PWM_FREQUENCY_ISR),
      .samplingTime_sec = 1/UZ_PWM_FREQUENCY_ISR,
      .upper_limit = 48.0f,
      .lower_limit = -48.0f
   };
   const struct uz_PI_Controller_config config_speed_right = {
		   .Kp = 0.2f,
		   .Ki = 2.0f,
		   .samplingTime_sec = 1/UZ_PWM_FREQUENCY_ISR,
		   .upper_limit = 3.4f,
		   .lower_limit = -3.4f
   };

   const struct uz_SetPoint_config config_setpoint_right = {
		   .config_PMSM = Beckhoff_AM8141,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = SMPMSM,
		   .relative_torque_tolerance = 0.01f
   };

   const struct uz_SpeedControl_config config_speed_ctrl_right = {
		   .config_controller = config_speed_right
   };

   struct uz_CurrentControl_config config_current_ctrl_left = {
      .config_PMSM = Beckhoff_AM8141,
	  .config_id = config_id_left,
	  .config_iq = config_iq_left,
	  .decoupling_select = linear_decoupling,
	  .max_modulation_index = 1.0f/sqrt(3.0f)
   };

   uz_CurrentControl_t* current_ctrl_left_init(void) {
	   Global_Data.rasv.Kp_cur_d_left = config_current_ctrl_left.config_id.Kp;
	   Global_Data.rasv.Ki_cur_d_left = config_current_ctrl_left.config_id.Ki;
	   Global_Data.rasv.Kp_cur_q_left = config_current_ctrl_left.config_iq.Kp;
	   Global_Data.rasv.Ki_cur_q_left = config_current_ctrl_left.config_iq.Ki;
	   return(uz_CurrentControl_init(config_current_ctrl_left));
   }

   uz_CurrentControl_t* current_ctrl_right_init(void) {
	   Global_Data.rasv.Kp_cur_d_right = config_current_ctrl_left.config_id.Kp;
	   Global_Data.rasv.Ki_cur_d_right = config_current_ctrl_left.config_id.Ki;
	   Global_Data.rasv.Kp_cur_q_right = config_current_ctrl_left.config_iq.Kp;
	   Global_Data.rasv.Ki_cur_q_right = config_current_ctrl_left.config_iq.Ki;
	   return(uz_CurrentControl_init(config_current_ctrl_left));
   }

   uz_SetPoint_t* setpoint_ctrl_right_init(void) {
	   return(uz_SetPoint_init(config_setpoint_right));
   }

   uz_SetPoint_t* setpoint_ctrl_left_init(void) {
	   return(uz_SetPoint_init(config_setpoint_right));
   }

   uz_SpeedControl_t* speed_ctrl_right_init(void) {
	   Global_Data.rasv.Kp_spd_right = config_speed_ctrl_right.config_controller.Kp;
	   Global_Data.rasv.Ki_spd_right = config_speed_ctrl_right.config_controller.Ki;
	   return(uz_SpeedControl_init(config_speed_ctrl_right));
   }

   uz_SpeedControl_t* speed_ctrl_left_init(void) {
	   Global_Data.rasv.Kp_spd_left = config_speed_ctrl_right.config_controller.Kp;
	   Global_Data.rasv.Ki_spd_left = config_speed_ctrl_right.config_controller.Ki;
	   return(uz_SpeedControl_init(config_speed_ctrl_right));
   }


