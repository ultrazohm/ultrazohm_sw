#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../main.h"

extern DS_Data Global_Data;

    const struct uz_PMSM_t Siemens_1FK7043 = {
      .R_ph_Ohm = 1.2f,
      .Ld_Henry = 0.0136f,
      .Lq_Henry = 0.0136f,
      .Psi_PM_Vs = 0.1142,//0.140f, //54V/1000rpm -> (54V*sqrt(2)*60/1000) / (3*sqrt(3)*2*pi) = 0.140 Vs
	  .polePairs = 3.0f,
	  .I_max_Ampere = 12.5f, //15.0f?
	  .J_kg_m_squared = 0.0002506f // 0.00010f per motor from datasheet, value calculated from 2*motor,2*coupling and 1x torque sensor
    };//these parameters are only needed if linear decoupling is selected
    const struct uz_PI_Controller_config config_id_left = {
    	      .type = UZ_PI_PARALLEL,
    		  .Kp = 20,
    	      .Ki = 100,
			  //.Kp = Siemens_1FK7043.Ld_Henry/(2.0f*1.5f*1.0f/UZ_PWM_FREQUENCY), // Ld_Herny / (2*tau_sigma) | tau_sigma = 1.5 * t_pwm
    	      //.Ki = Siemens_1FK7043.R_ph_Ohm/(2.0f*1.5f*1.0f/UZ_PWM_FREQUENCY),
    	      .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
			  //Kp = 10, Ki = 40 at high speed
			  //Kp = 45.3, Ki = 4000 at low speed
   };
   const struct uz_PI_Controller_config config_iq_left = {
			  .type = UZ_PI_PARALLEL,
    		  .Kp = 20,
    	      .Ki = 100,
			  //.Kp = Siemens_1FK7043.Lq_Henry/(2.0f*1.5f*1.0f/UZ_PWM_FREQUENCY),
		      //.Ki = Siemens_1FK7043.R_ph_Ohm/(2.0f*1.5f*1.0f/UZ_PWM_FREQUENCY),
		      .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
   };
   const struct uz_PI_Controller_config config_speed_left = {
		   .Kp = 0.06f,//0.1
		   .Ki = 2.0f,//2.0
		   .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
		   .upper_limit = 9.0f,
		   .lower_limit = -9.0f
   };

   const struct uz_PI_Controller_config config_speed_right = {
		   .Kp = 0.06f,//0.1
		   .Ki = 2.0f,//2.0
		   .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
		   .upper_limit = 9.0f,
		   .lower_limit = -9.0f
   };

   const struct uz_SetPoint_config config_setpoint_left = {
		   .config_PMSM = Siemens_1FK7043,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = SMPMSM,
		   .relative_torque_tolerance = 0.01f
   };

   const struct uz_SetPoint_config config_setpoint_right = {
		   .config_PMSM = Siemens_1FK7043,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = SMPMSM,
		   .relative_torque_tolerance = 0.01f
   };

   const struct uz_SpeedControl_config config_speed_ctrl_left = {
		   .config_controller = config_speed_left
   };

   const struct uz_SpeedControl_config config_speed_ctrl_right = {
		   .config_controller = config_speed_right
   };

   const struct uz_PI_Controller_config config_id_right = {
 	      .type = UZ_PI_PARALLEL,
		  .Kp = 130,//20
	      .Ki = 100,
		  //.Kp = Siemens_1FK7043.Ld_Henry/(2.0f*1.0f/UZ_PWM_FREQUENCY),
 	      //.Ki = Siemens_1FK7043.R_ph_Ohm/(2.0f*1.0f/UZ_PWM_FREQUENCY),
 	      .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
  };
  const struct uz_PI_Controller_config config_iq_right = {
		  .type = UZ_PI_PARALLEL,
		  .Kp = 130,//20
	      .Ki = 100,
		  //.Kp = Siemens_1FK7043.Lq_Henry/(2.0f*1.0f/UZ_PWM_FREQUENCY),
	      //.Ki = Siemens_1FK7043.R_ph_Ohm/(2.0f*1.0f/UZ_PWM_FREQUENCY),
	      .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
  };

   struct uz_CurrentControl_config config_current_ctrl_left = {
      .config_PMSM = Siemens_1FK7043,
	  .config_id = config_id_left,
	  .config_iq = config_iq_left,
	  .decoupling_select = linear_decoupling,
	  .max_modulation_index = 0.57735 //=1.0f/sqrt(3.0f)
   };

   struct uz_CurrentControl_config config_current_ctrl_right = {
      .config_PMSM = Siemens_1FK7043,
	  .config_id = config_id_right,
	  .config_iq = config_iq_right,
	  .decoupling_select = linear_decoupling,
	  .max_modulation_index = 0.57735 //=1.0f/sqrt(3.0f)
   };


   struct uz_IIR_Filter_config config_IIR_speed_left = { .selection = LowPass_first_order,
   		.cutoff_frequency_Hz = 0.5f, .sample_frequency_Hz = UZ_PWM_FREQUENCY};

   struct uz_IIR_Filter_config config_IIR_speed_right = { .selection = LowPass_first_order,
   		.cutoff_frequency_Hz = 0.5f, .sample_frequency_Hz = UZ_PWM_FREQUENCY};

   struct uz_IIR_Filter_config config_IIR_torque = { .selection = LowPass_first_order,
      		.cutoff_frequency_Hz = 100.0f, .sample_frequency_Hz = UZ_PWM_FREQUENCY};

   uz_CurrentControl_t* current_ctrl_left_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_left));
   }

   uz_CurrentControl_t* current_ctrl_right_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_right));
   }

   uz_SetPoint_t* setpoint_ctrl_left_init(void) {
	   return(uz_SetPoint_init(config_setpoint_left));
   }

   uz_SetPoint_t* setpoint_ctrl_right_init(void) {
	   return(uz_SetPoint_init(config_setpoint_right));
   }

   uz_SpeedControl_t* speed_ctrl_left_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl_left));
   }

   uz_SpeedControl_t* speed_ctrl_right_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl_right));
   }

   uz_IIR_Filter_t* speed_filt_left_init(void) {
	   return(uz_signals_IIR_Filter_init(config_IIR_speed_left));
   }

   uz_IIR_Filter_t* speed_filt_right_init(void) {
	   return(uz_signals_IIR_Filter_init(config_IIR_speed_right));
   }

   uz_IIR_Filter_t* torque_filt_init(void) {
	   return(uz_signals_IIR_Filter_init(config_IIR_torque));
   }
