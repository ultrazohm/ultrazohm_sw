#include "../../main.h"
#include "../../uz/uz_piController/uz_piController.h"

#include "init_BLDC_control.h"


const struct uz_PMSM_t pmsm_config_dq_BLDC = {

// Brose-6ph-Prüfstand
	//.Ld_Henry = 0.00012516f,
    //.Lq_Henry = 0.00012595f,
    //.Psi_PM_Vs = 0.0047f,
    //.R_ph_Ohm = 0.0643f,


// Motor 1 und 2

	.Ld_Henry = 0.0001968f, // line-to-line inductance
    .Lq_Henry = 0.0001968f, // line-to-line inductance
    .Psi_PM_Vs = 0.0047f,
    .R_ph_Ohm = 2.0f*0.04512f, // eine Phase, x2 evtl.


// Motor Handwicklung No 1:
//	.Ld_Henry = 0.0001968f*3.0f, // line-to-line inductance
//    .Lq_Henry = 0.0001968f*3.0f, // line-to-line inductance
//    .Psi_PM_Vs = 0.0047f,
//		.R_ph_Ohm = 0.5f*1.54f, // 1/2 phase to phase

/*
	.Ld_Henry = 0.002442f, // line-to-line inductance
    .Lq_Henry = 0.002442f, // line-to-line inductance
    .Psi_PM_Vs = 0.0047f,
    .R_ph_Ohm = 1.5167f, // phase to phase
*/
    .polePairs = 6.0f
};

const float T_sigma = 2.0f/10000.0f;

   struct uz_PI_Controller_config config_I_control_BLDC = {
      .type = parallel,
      .Kp = pmsm_config_dq_BLDC.Ld_Henry/(2.0f*T_sigma),
      .Ki = pmsm_config_dq_BLDC.Ld_Henry/(2.0f*T_sigma) * pmsm_config_dq_BLDC.R_ph_Ohm / pmsm_config_dq_BLDC.Ld_Henry,

	  // Langsamer:
       //.Kp = pmsm_config_dq_BLDC.R_ph_Ohm,
       //.Ki = pmsm_config_dq_BLDC.R_ph_Ohm * pmsm_config_dq_BLDC.R_ph_Ohm/ ( pmsm_config_dq_BLDC.Ld_Henry / pmsm_config_dq_BLDC.R_ph_Ohm ),

      .samplingTime_sec = 0.00005f,
      .upper_limit = 13.0f/2.0f,
      .lower_limit = -13.0f/2.0f
   };

   struct uz_PI_Controller_config config_Speed_control_BLDC = {
      .type = parallel,
      .Kp = 0.01f, // 0.001f
      .Ki = 0.01f, // 0.001f
      .samplingTime_sec = 0.00005f,
      .upper_limit = 2.5f,
      .lower_limit = -2.5f
   };

uz_PI_Controller* init_I_control_BLDC(void){
	return uz_PI_Controller_init(config_I_control_BLDC);
}


uz_PI_Controller* init_Speed_control_BLDC(void){
	return uz_PI_Controller_init(config_Speed_control_BLDC);
}
