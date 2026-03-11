#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../main.h"

extern DS_Data Global_Data;
// parameter masterarbeit
//uz_IM_t IM_config = {
//    .Rs_Ohm = 21.22f,
//    .Rr_Ohm = 18.78f,
//    .Lsigma_s_Henry = 91e-3f,
//    .Lsigma_r_Henry = 102e-3f,
//    .Lm_Henry = 809e-3f,
//    .polePairs = 2.0f,
//    .J_kg_m_squared = 0.000826f,
//    .I_max_Ampere = 2.0f,
//    .Psi_rated_Vs = 0.599f,
//};
// parameter projektarbeit
//uz_IM_t IM_config = {
//    .Rs_Ohm = 7.05f,
//    .Rr_Ohm = 6.23f,
//    .Lsigma_s_Henry = 31e-3f,
//    .Lsigma_r_Henry = 36e-3f,
//    .Lm_Henry = 271e-3f,
//    .polePairs = 2.0f,
//    .J_kg_m_squared = 0.000826f,
//    .I_max_Ampere = 2.0f,
//    .Psi_rated_Vs = 0.599f,
//};
#if UZ_MACHINE_ENABLE_IM_SIEMENS
    const struct uz_PMSM_t IM_Siemens = {
      .R_ph_Ohm = 0.51,
      .Ld_Henry = 0.002f,
      .Lq_Henry = 0.002f,
      .Psi_PM_Vs = 0.042f,
	  .polePairs = 2.0f,
	  .I_max_Ampere = 5.0f,
	  .J_kg_m_squared = 0.000108
    };//these parameters are only needed if linear decoupling is selected
#endif

#if UZ_MACHINE_ENABLE_VOESTALPINE
    const struct uz_PMSM_t Voestalpine = {
      .R_ph_Ohm = 0.157,
      .Ld_Henry = 585e-6f,
      .Lq_Henry = 770e-6f,
      .Psi_PM_Vs = 0.0167f,
	  .polePairs = 4.0f,
	  .I_max_Ampere = 8.0f,
	  .J_kg_m_squared = 0.000108,
    };//these parameters are only needed if linear decoupling is selected
#endif

#if UZ_MACHINE_ENABLE_IM_THN
    const struct uz_PMSM_t IM_THN = {
      .R_ph_Ohm = 0.72f,
      .Ld_Henry = 2.8e-3f,
      .Lq_Henry = 2.8e-3f,
      .Psi_PM_Vs = 0.040f,
	  .polePairs = 2.0f,
	  .I_max_Ampere = 6.0f,
	  .J_kg_m_squared = 0.000150f
    };
#endif

#if UZ_MACHINE_ENABLE_IM_TUM
    const struct uz_PMSM_t IM_TUM = {
      .R_ph_Ohm = 0.63f,
      .Ld_Henry = 2.4e-3f,
      .Lq_Henry = 2.4e-3f,
      .Psi_PM_Vs = 0.038f,
	  .polePairs = 2.0f,
	  .I_max_Ampere = 7.0f,
	  .J_kg_m_squared = 0.000120f
    };
#endif

#if !UZ_MACHINE_ENABLE_VOESTALPINE
#error "Current VA control configuration in init_control_machines.c requires UZ_MACHINE_ENABLE_VOESTALPINE = 1U."
#endif

    const struct uz_PI_Controller_config config_id_VA = {
    	      .type = UZ_PI_PARALLEL,
    		  .Kp = Voestalpine.Ld_Henry/(2.0f*1.0f/UZ_PWM_FREQUENCY),
    	      .Ki = Voestalpine.R_ph_Ohm/(2.0f*1.0f/UZ_PWM_FREQUENCY),
    	      .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
    	      .upper_limit = 24.0f,
			  .lower_limit = -24.0f
   };
   const struct uz_PI_Controller_config config_iq_VA = {
			  .type = UZ_PI_PARALLEL,
			  .Kp = Voestalpine.Lq_Henry/(2.0f*1.0f/UZ_PWM_FREQUENCY),
		      .Ki = Voestalpine.R_ph_Ohm/(2.0f*1.0f/UZ_PWM_FREQUENCY),
		      .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
		      .upper_limit = 24.0f,
		      .lower_limit = -24.0f
   };
   const struct uz_PI_Controller_config config_speed_VA = {
		   .Kp = 0.2f,
		   .Ki = 2.0f,
		   .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
		   .upper_limit = 8.0f,
		   .lower_limit = -8.0f
   };

   const struct uz_SetPoint_config config_setpoint_VA = {
		   .config_PMSM = Voestalpine,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = IPMSM,
		   .relative_torque_tolerance = 0.01f
   };

   const struct uz_SpeedControl_config config_speed_ctrl_VA = {
		   .config_controller = config_speed_VA
   };

   struct uz_CurrentControl_config config_current_ctrl_VA = {
      .config_PMSM = Voestalpine,
	  .config_id = config_id_VA,
	  .config_iq = config_iq_VA,
	  .decoupling_select = no_decoupling,
	  .max_modulation_index = 0.57735 //=1.0f/sqrt(3.0f)
   };


   struct uz_IIR_Filter_config config_IIR = { .selection = LowPass_first_order,
   		.cutoff_frequency_Hz = 0.5f, .sample_frequency_Hz = UZ_PWM_FREQUENCY};

   uz_CurrentControl_t* current_ctrl_VA_init(void) {
	   return(uz_CurrentControl_init(config_current_ctrl_VA));
   }


   uz_SetPoint_t* setpoint_ctrl_VA_init(void) {
	   return(uz_SetPoint_init(config_setpoint_VA));
   }


   uz_SpeedControl_t* speed_ctrl_VA_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl_VA));
   }

   uz_IIR_Filter_t* speed_filt_VA_init(void) {
	   return(uz_signals_IIR_Filter_init(config_IIR));
   }


