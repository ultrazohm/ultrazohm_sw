/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID.c
 *
 * Code generated for Simulink model 'ElectricalID'.
 *
 * Model version                  : 2.11
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov 22 08:28:19 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "uz_PID_ElectricalID_codegen.h"
#if UZ_PID_ELECTRICALID_ACTIVE > 0U 

/* Named constants for Chart: '<Root>/ElectricalID' */
#define IN_ElectricalID                ((uint8_T)1U)
#define IN_Levenberg_Marquardt         ((uint8_T)1U)
#define IN_Levenberg_Marquardt_q       ((uint8_T)2U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Waiting                     ((uint8_T)2U)
#define IN_alignRotor_d_off            ((uint8_T)3U)
#define IN_alignRotor_d_off1           ((uint8_T)4U)
#define IN_alignRotor_d_off2           ((uint8_T)5U)
#define IN_alignRotor_d_on             ((uint8_T)6U)
#define IN_alignRotor_d_on1            ((uint8_T)7U)
#define IN_alignRotor_q_off            ((uint8_T)8U)
#define IN_alignRotor_q_on             ((uint8_T)9U)
#define IN_calculatePIcontroller       ((uint8_T)10U)
#define IN_endState                    ((uint8_T)11U)
#define IN_evaluate_Turn_DC            ((uint8_T)12U)
#define IN_findDutyCycle               ((uint8_T)13U)
#define IN_measure_psiPM               ((uint8_T)14U)
#define IN_rotorInertiaEstimation      ((uint8_T)15U)
#define IN_stepResponse                ((uint8_T)16U)
#define IN_stepResponse_q              ((uint8_T)17U)
#define IN_stop                        ((uint8_T)18U)
#define IN_waitState                   ((uint8_T)19U)

extern real32_T rt_hypotf(real32_T u0, real32_T u1);

/* Forward declaration for local functions */
static void initParams(ExtY *rtY, DW *rtDW);
static void resetParams_LM(DW *rtDW);
static void enter_atomic_calculatePIcontrol(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void RefreshDataRegister(DW *rtDW);
static void DutyCycle_mod(const real32_T om_reg_in[5], ExtU *rtU, DW *rtDW);
static void TurnMotor(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void evaluate_Turn_DC(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void DutyCycle_mod_o(real32_T ia_reg_in, ExtU *rtU, DW *rtDW);
static void findDutyCycle(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void measure_psiPM(ExtU *rtU, ExtY *rtY, DW *rtDW);
static real32_T goertzel(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void inv(const real32_T x[4], real32_T y[4]);
static void mtimes(const real32_T A[2048], const real32_T B_0[1024], real32_T C[2]);
static void LM_algorithm(real32_T *L_est, real32_T *R_est, ExtU *rtU, DW *rtDW);
static void stepResponse(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void LM_algorithm_Lq(real32_T *L_est, ExtU *rtU, DW *rtDW);
static void stepResponse_q(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void exit_internal_ElectricalID(ExtU *rtU, ExtY *rtY, DW *rtDW);
static void ElectricalID_c(ExtU *rtU, ExtY *rtY, DW *rtDW);

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function initParams
 *  initialize variables
 */
static void initParams(ExtY *rtY, DW *rtDW)
{
  /* MATLAB Function 'initParams': '<S1>:88' */
  /* '<S1>:88:4' Ki_n_loc            = single(0.0); */
	rtDW->Ki_n_loc = 0.0F;

  /* '<S1>:88:5' Kp_n_loc            = single(0.0); */
	rtDW->Kp_n_loc = 0.0F;

  /* '<S1>:88:6' n_filt              = single(0.0); */
  /* '<S1>:88:7' n_ref_old           = single(0.0); */
  /* '<S1>:88:8' repetitionCounter   = uint32(0); */
  /* '<S1>:88:9' dutyCycAdj          = single(0.0); */
  /* '<S1>:88:10' counter 			= uint32(1); */
	rtDW->counter = 1U;

  /* '<S1>:88:11' Kp_iq_loc           = single(0.0); */
	rtDW->Kp_iq_loc = 0.0F;

  /* '<S1>:88:12' Ki_iq_loc           = single(0.0); */
  /* '<S1>:88:13' Kp_id_loc           = single(0.0); */
  /* '<S1>:88:14' Ki_id_loc           = single(0.0); */
  /* '<S1>:88:15' DutyCycle_filt      = single(0.0); */
  /* '<S1>:88:16' measArray1			= single(zeros(1024,1)); */
	memset(&rtDW->measArray1[0], 0, sizeof(real32_T) << 10U);

  /* '<S1>:88:17' meas_sum            = single(zeros(2,1)); */
  /* used for Friction Id */
  /* '<S1>:88:18' J2                  = single(zeros(256,5)); */
  /* '<S1>:88:19' thetaOffset         = single(0.0); */
  /* '<S1>:88:20' Ustep               = single(zeros(205,1)); */
	memset(&rtDW->Ustep[0], 0, 205U * sizeof(real32_T));

  /* '<S1>:88:21' DutyCycle           = single(0.0); */
	rtDW->DutyCycle = 0.0F;

  /* '<S1>:88:22' omega_sum           = single(0); */
	rtDW->omega_sum = 0.0F;

  /* '<S1>:88:23' om_con              = boolean(0); */
	rtDW->om_con = false;

  /* '<S1>:88:24' ia_sum              = single(0); */
	rtDW->ia_sum = 0.0F;

  /* '<S1>:88:25' ia_valid            = boolean(0); */
	rtDW->ia_valid = false;

  /* '<S1>:88:26' DC_manual           = boolean(0); */
	rtDW->DC_manual = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Outputs */
  /* '<S1>:88:29' ElectricalID_FOC_output.Ki_n_out    = single(0.0); */
	rtY->ElectricalID_FOC_output.Ki_n_out = 0.0F;

  /* '<S1>:88:30' ElectricalID_FOC_output.Ki_iq_out   = single(0.0); */
	rtY->ElectricalID_FOC_output.Ki_iq_out = 0.0F;

  /* '<S1>:88:31' ElectricalID_FOC_output.Ki_id_out   = single(0.0); */
	rtY->ElectricalID_FOC_output.Ki_id_out = 0.0F;

  /* '<S1>:88:32' ElectricalID_FOC_output.Kp_n_out 	= single(0.0); */
	rtY->ElectricalID_FOC_output.Kp_n_out = 0.0F;

  /* '<S1>:88:33' ElectricalID_FOC_output.Kp_iq_out 	= single(0.0); */
	rtY->ElectricalID_FOC_output.Kp_iq_out = 0.0F;

  /* '<S1>:88:34' ElectricalID_FOC_output.Kp_id_out 	= single(0.0); */
	rtY->ElectricalID_FOC_output.Kp_id_out = 0.0F;

  /* '<S1>:88:35' ElectricalID_FOC_output.n_ref_FOC = single(0.0); */
	rtY->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:88:36' ElectricalID_FOC_output.PRBS_out = single(0.0); */
	rtY->ElectricalID_FOC_output.PRBS_out = 0.0F;

  /* '<S1>:88:37' ElectricalID_FOC_output.i_d_ref_out = single(0.0); */
	rtY->ElectricalID_FOC_output.i_d_ref_out = 0.0F;

  /* '<S1>:88:38' ElectricalID_FOC_output.i_q_ref_out = single(0.0); */
	rtY->ElectricalID_FOC_output.i_q_ref_out = 0.0F;

  /* '<S1>:88:39' ElectricalID_FOC_output.enableFOC_speed = boolean(0); */
	rtY->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S1>:88:40' ElectricalID_FOC_output.enableFOC_current = boolean(0); */
	rtY->ElectricalID_FOC_output.enableFOC_current = false;

  /* '<S1>:88:41' ElectricalID_FOC_output.VibOn_out = boolean(0); */
	rtY->ElectricalID_FOC_output.VibOn_out = false;

  /* '<S1>:88:42' ElectricalID_FOC_output.VibFreq_out = uint16(0); */
	rtY->ElectricalID_FOC_output.VibFreq_out = 0U;

  /* '<S1>:88:43' ElectricalID_FOC_output.VibAmp_out = single(0); */
	rtY->ElectricalID_FOC_output.VibAmp_out = 0.0F;

  /* '<S1>:88:44' ElectricalID_FOC_output.resetIntegrator = boolean(0); */
	rtY->ElectricalID_FOC_output.resetIntegrator = false;

  /* Outport: '<Root>/finishedElectricalID' */
  /* '<S1>:88:45' finishedElectricalID= boolean(0); */
	rtY->finishedElectricalID = false;

  /* Outport: '<Root>/ElectricalID_output' */
  /* '<S1>:88:47' ElectricalID_output.PWM_Switch_0        = single(0.0); */
	rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

  /* '<S1>:88:48' ElectricalID_output.PWM_Switch_1        = single(0.0); */
	rtY->ElectricalID_output_o.PWM_Switch_1 = 0.0F;

  /* '<S1>:88:49' ElectricalID_output.PWM_Switch_2        = single(0.0); */
	rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;

  /* '<S1>:88:50' ElectricalID_output.PWM_Switch_3        = single(0.0); */
	rtY->ElectricalID_output_o.PWM_Switch_3 = 0.0F;

  /* '<S1>:88:51' ElectricalID_output.PWM_Switch_4        = single(0.0); */
	rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;

  /* '<S1>:88:52' ElectricalID_output.PWM_Switch_5        = single(0.0); */
	rtY->ElectricalID_output_o.PWM_Switch_5 = 0.0F;

  /* '<S1>:88:53' ElectricalID_output.outputMode          = boolean(zeros(1,3)); */
  /* '<S1>:88:54' ElectricalID_output.outputMode          = [boolean(1),boolean(1),boolean(1)]; */
	rtY->ElectricalID_output_o.outputMode[0] = true;
	rtY->ElectricalID_output_o.outputMode[1] = true;
	rtY->ElectricalID_output_o.outputMode[2] = true;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* 0 = GPIO, 1 = PWM */
  /* '<S1>:88:55' ElectricalID_FOC_output.activeState 		= uint16(0); */
	rtY->ElectricalID_FOC_output.activeState = 0U;

  /* Outport: '<Root>/ElectricalID_output' */
  /* '<S1>:88:56' ElectricalID_output.thetaOffset         = single(0.0); */
	rtY->ElectricalID_output_o.thetaOffset = 0.0F;

  /* '<S1>:88:57' ElectricalID_output.R_s                 = single(0.0); */
	rtY->ElectricalID_output_o.R_s = 0.0F;

  /* '<S1>:88:58' ElectricalID_output.L_d                 = single(0.0); */
	rtY->ElectricalID_output_o.L_d = 0.0F;

  /* '<S1>:88:59' ElectricalID_output.L_q                 = single(0.0); */
	rtY->ElectricalID_output_o.L_q = 0.0F;

  /* '<S1>:88:60' ElectricalID_output.psiPM               = single(0.0); */
	rtY->ElectricalID_output_o.psiPM = 0.0F;

  /* '<S1>:88:61' ElectricalID_output.rotorInertia        = single(0.0); */
	rtY->ElectricalID_output_o.rotorInertia = 0.0F;

  /* '<S1>:88:62' ElectricalID_output.p                   = uint16(0); */
	rtY->ElectricalID_output_o.p = 0U;

  /* '<S1>:88:63' ElectricalID_output.TrainInertia        = single(0.0); */
	rtY->ElectricalID_output_o.TrainInertia = 0.0F;

  /* Outport: '<Root>/enteredElectricalID' */
  /* '<S1>:88:64' enteredElectricalID                     = boolean(0); */
	rtY->enteredElectricalID = false;

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S1>:88:67' d        			= single(zeros(2048,1)); */
  /* '<S1>:88:68' dp      			= single(zeros(2,1)); */
  /* '<S1>:88:69' e       			= single(0); */
	rtDW->e = 0.0F;

  /* '<S1>:88:70' e_lm  				= single(0); */
  /* '<S1>:88:71' H 					= single(zeros(2,2)); */
	rtDW->H[0] = 0.0F;
	rtDW->H[1] = 0.0F;
	rtDW->H[2] = 0.0F;
	rtDW->H[3] = 0.0F;

  /* '<S1>:88:72' i_est 				= single(zeros(2048,1)); */
	memset(&rtDW->d[0], 0, sizeof(real32_T) << 11U);
	memset(&rtDW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S1>:88:73' it 					= uint16(0); */
  /* '<S1>:88:74' J 					= single(zeros(2048,2)); */
	memset(&rtDW->J[0], 0, sizeof(real32_T) << 12U);

  /* '<S1>:88:75' k 					= single(0); */
  /* '<S1>:88:76' L0 					= single(0); */
  /* '<S1>:88:77' L_est   			= single(0); */
  /* '<S1>:88:78' L_lm 				= single(0); */
  /* '<S1>:88:79' Ndata  				= uint16(512); */
  /* '<S1>:88:80' Nparams 			= uint16(2); */
  /* '<S1>:88:81' n_iters 			= uint16(100); */
	rtDW->n_iters = 100U;

  /* '<S1>:88:82' R0 					= single(0); */
  /* '<S1>:88:83' R_est 				= single(0); */
  /* '<S1>:88:84' R_lm 				= single(0); */
  /* '<S1>:88:85' U0 					= single(0); */
	rtDW->U0 = 0.0F;

  /* '<S1>:88:86' lambda  			= single(0.01); */
	rtDW->lambda = 0.01F;

  /* '<S1>:88:87' updateJ 			= boolean(1); */
	rtDW->updateJ = true;

  /*  initialize varaibles for PMSM parameters */
  /* '<S1>:88:90' R_corr              = single(0.000); */
	rtDW->R_corr = 0.0F;

  /* 0.060 */
  /*  variables for controller calculation */
  /* '<S1>:88:93' bandwidthCurrentControl = single(2000); */
	rtDW->bandwidthCurrentControl = 2000.0F;

  /* '<S1>:88:94' dampingFactor           = single(10.0); */
	rtDW->dampingFactor = 10.0F;

  /* '<S1>:88:95' psiOverJ                = single(5000); */
	rtDW->psiOverJ = 5000.0F;
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function resetParams_LM
 *  reset variables
 */
static void resetParams_LM(DW *rtDW)
{
  /* MATLAB Function 'resetParams_LM': '<S1>:283' */
  /* '<S1>:283:4' measArray1			= single(zeros(1024,1)); */
	memset(&rtDW->measArray1[0], 0, sizeof(real32_T) << 10U);

  /* '<S1>:283:5' Ustep               = single(zeros(205,1)); */
	memset(&rtDW->Ustep[0], 0, 205U * sizeof(real32_T));

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S1>:283:8' d        			= single(zeros(2048,1)); */
  /* '<S1>:283:9' dp      			= single(zeros(2,1)); */
  /* '<S1>:283:10' e       			= single(0); */
	rtDW->e = 0.0F;

  /* '<S1>:283:11' e_lm  				= single(0); */
  /* '<S1>:283:12' H 					= single(zeros(2,2)); */
	rtDW->H[0] = 0.0F;
	rtDW->H[1] = 0.0F;
	rtDW->H[2] = 0.0F;
	rtDW->H[3] = 0.0F;

  /* '<S1>:283:13' i_est 				= single(zeros(2048,1)); */
	memset(&rtDW->d[0], 0, sizeof(real32_T) << 11U);
	memset(&rtDW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S1>:283:14' it 					= uint16(0); */
  /* '<S1>:283:15' J 					= single(zeros(2048,2)); */
	memset(&rtDW->J[0], 0, sizeof(real32_T) << 12U);

  /* '<S1>:283:16' k 					= single(0); */
  /* '<S1>:283:17' L0 					= single(0); */
  /* '<S1>:283:18' L_est   			= single(0); */
  /* '<S1>:283:19' L_lm 				= single(0); */
  /* '<S1>:283:20' Ndata  				= uint16(512); */
  /* '<S1>:283:21' Nparams 			= uint16(2); */
  /* '<S1>:283:22' n_iters 			= uint16(100); */
	rtDW->n_iters = 100U;

  /* '<S1>:283:23' R0 					= single(0); */
  /* '<S1>:283:24' R_est 				= single(0); */
  /* '<S1>:283:25' R_lm 				= single(0); */
  /* '<S1>:283:26' U0 					= single(0); */
	rtDW->U0 = 0.0F;

  /* '<S1>:283:27' lambda  			= single(0.01); */
	rtDW->lambda = 0.01F;

  /* '<S1>:283:28' updateJ 			= boolean(1); */
	rtDW->updateJ = true;

  /* L_d                 = single(0); */
  /* R_s                 = single(0); */
}

/* Function for Chart: '<Root>/ElectricalID' */
static void enter_atomic_calculatePIcontrol(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  real32_T Ki_id_loc;
  real32_T Kp_id_loc;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Entry 'calculatePIcontroller': '<S1>:284' */
  /* state6.0 */
  /* '<S1>:284:4' ElectricalID_FOC_output.activeState = uint16(144); */
	rtY->ElectricalID_FOC_output.activeState = 144U;

  /* Outport: '<Root>/ElectricalID_output' */
  /*  calculation according to TI instaSpin */
  /* '<S1>:284:6' Kp_id_loc = ElectricalID_output.L_d * bandwidthCurrentControl; */
	Kp_id_loc = rtY->ElectricalID_output_o.L_d * rtDW->bandwidthCurrentControl;

  /* '<S1>:284:7' Ki_id_loc = ElectricalID_output.R_s * bandwidthCurrentControl; */
	Ki_id_loc = rtY->ElectricalID_output_o.R_s * rtDW->bandwidthCurrentControl;

  /* Inport: '<Root>/ElectricalIDConfig' */
  /* '<S1>:284:8' Ki_iq_loc = Ki_id_loc; */
  /* '<S1>:284:9' if (ElectricalIDConfig.identLq == 1) */
	if (rtU->ElectricalIDConfig_l.identLq) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:284:10' ElectricalID_output.L_q = 0.00245; */
		rtY->ElectricalID_output_o.L_q = 0.00245F;

    /* '<S1>:284:11' Kp_iq_loc = ElectricalID_output.L_q * bandwidthCurrentControl; */
		rtDW->Kp_iq_loc = rtY->ElectricalID_output_o.L_q * rtDW->bandwidthCurrentControl;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:284:12' elseif (ElectricalIDConfig.identLq == 0) */
    /* '<S1>:284:13' ElectricalID_output.L_q = ElectricalID_output.L_d; */
		rtY->ElectricalID_output_o.L_q = rtY->ElectricalID_output_o.L_d;

    /* '<S1>:284:14' Kp_iq_loc = Kp_id_loc; */
		rtDW->Kp_iq_loc = Kp_id_loc;
  }

  /* End of Inport: '<Root>/ElectricalIDConfig' */

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S1>:284:16' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.L_q*dampingFactor*.... */
  /* '<S1>:284:17'     GlobalConfig.polePairs*3.0/2.0*psiOverJ); */
	rtDW->Kp_n_loc = rtDW->Kp_iq_loc / (rtY->ElectricalID_output_o.L_q * rtDW->dampingFactor * rtU->GlobalConfig_out.polePairs * 3.0F / 2.0F * rtDW->psiOverJ);

  /* . */
  /* Ki_n_loc = (dampingFactor*dampingFactor*ElectricalID_output.L_q)/Kp_iq_loc; */
  /* '<S1>:284:19' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.L_q * ElectricalID_output.L_q * .... */
  /* '<S1>:284:20'     dampingFactor * dampingFactor * dampingFactor * GlobalConfig.polePairs*3.0/2.0*psiOverJ); */
	rtDW->Ki_n_loc = rtDW->Kp_iq_loc * rtDW->Kp_iq_loc
	                / (rtY->ElectricalID_output_o.L_q * rtY->ElectricalID_output_o.L_q * rtDW->dampingFactor * rtDW->dampingFactor * rtDW->dampingFactor * rtU->GlobalConfig_out.polePairs * 3.0F
	                                / 2.0F * rtDW->psiOverJ);

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* . */
  /* Output calculated values */
  /* '<S1>:284:22' ElectricalID_FOC_output.Kp_id_out = Kp_id_loc; */
	rtY->ElectricalID_FOC_output.Kp_id_out = Kp_id_loc;

  /* '<S1>:284:23' ElectricalID_FOC_output.Ki_id_out = Ki_id_loc; */
	rtY->ElectricalID_FOC_output.Ki_id_out = Ki_id_loc;

  /* '<S1>:284:24' ElectricalID_FOC_output.Kp_iq_out = Kp_iq_loc; */
	rtY->ElectricalID_FOC_output.Kp_iq_out = rtDW->Kp_iq_loc;

  /* '<S1>:284:25' ElectricalID_FOC_output.Ki_iq_out = Ki_iq_loc; */
	rtY->ElectricalID_FOC_output.Ki_iq_out = Ki_id_loc;

  /* '<S1>:284:26' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
	rtY->ElectricalID_FOC_output.Kp_n_out = rtDW->Kp_n_loc;

  /* '<S1>:284:27' ElectricalID_FOC_output.Ki_n_out = single(Ki_n_loc); */
	rtY->ElectricalID_FOC_output.Ki_n_out = rtDW->Ki_n_loc;
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW *rtDW)
{
  /* MATLAB Function 'RefreshDataRegister': '<S1>:784' */
  /* '<S1>:784:3' m=length(omega_register); */
  /* '<S1>:784:4' for k= single(0):single(m-2) */
  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
	rtDW->omega_register[4] = rtDW->omega_register[3];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
	rtDW->omega_register[3] = rtDW->omega_register[2];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
	rtDW->omega_register[2] = rtDW->omega_register[1];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
	rtDW->omega_register[1] = rtDW->omega_register[0];
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function DutyCycle_mod(om_reg_in)
 */
static void DutyCycle_mod(const real32_T om_reg_in[5], ExtU *rtU, DW *rtDW)
{
  real32_T ex;
  real32_T mean_om_reg;
  real32_T tmp;

  /* MATLAB Function 'DutyCycle_mod': '<S1>:769' */
  /* '<S1>:769:2' mean_om_reg=mean(om_reg_in); */
  mean_om_reg = ((((om_reg_in[0] + om_reg_in[1]) + om_reg_in[2]) + om_reg_in[3])
                 + om_reg_in[4]) / 5.0F;

  /* if no manual value for the DutyCycle is set, this function determines, if the rotor is turning above */
  /* the stated minimal speed and the oscillation is below */
  /* the stated threshold */
  /* '<S1>:769:7' if(om_con==0) */
	if (!rtDW->om_con) {
    /* Inport: '<Root>/ElectricalIDConfig' incorporates:
     *  Inport: '<Root>/GlobalConfig'
     */
    /* '<S1>:769:8' if(mean_om_reg >(ElectricalIDConfig.min_n_ratio*GlobalConfig.ratSpeed*2*pi)/60) */
		if (mean_om_reg > rtU->ElectricalIDConfig_l.min_n_ratio * rtU->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F / 60.0F) {
      /* minimal speed in rad/sec */
      /* determines if the oscillation is below the stated threshold */
      /* (currently 5% of rated speed) */
      /* '<S1>:769:12' if((mean_om_reg+(0.05*(GlobalConfig.ratSpeed*2*pi)/60))>=max(om_reg_in)&& ... */
      /* '<S1>:769:13'              (mean_om_reg-(0.05*(GlobalConfig.ratSpeed*2*pi)/60))<=min(om_reg_in)&&min(om_reg_in)~=0) */
      ex = om_reg_in[0];
      if (om_reg_in[0] < om_reg_in[1]) {
        ex = om_reg_in[1];
      }

      if (ex < om_reg_in[2]) {
        ex = om_reg_in[2];
      }

      if (ex < om_reg_in[3]) {
        ex = om_reg_in[3];
      }

      if (ex < om_reg_in[4]) {
        ex = om_reg_in[4];
      }

			tmp = rtU->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F * 0.05F / 60.0F;
      if (tmp + mean_om_reg >= ex) {
        ex = om_reg_in[0];
        if (om_reg_in[0] > om_reg_in[1]) {
          ex = om_reg_in[1];
        }

        if (ex > om_reg_in[2]) {
          ex = om_reg_in[2];
        }

        if (ex > om_reg_in[3]) {
          ex = om_reg_in[3];
        }

        if (ex > om_reg_in[4]) {
          ex = om_reg_in[4];
        }

        if (mean_om_reg - tmp <= ex) {
          mean_om_reg = om_reg_in[0];
          if (om_reg_in[0] > om_reg_in[1]) {
            mean_om_reg = om_reg_in[1];
          }

          if (mean_om_reg > om_reg_in[2]) {
            mean_om_reg = om_reg_in[2];
          }

          if (mean_om_reg > om_reg_in[3]) {
            mean_om_reg = om_reg_in[3];
          }

          if (mean_om_reg > om_reg_in[4]) {
            mean_om_reg = om_reg_in[4];
          }

          if (mean_om_reg != 0.0F) {
            /* '<S1>:769:15' om_con=boolean(1); */
						rtDW->om_con = true;
          } else {
            /* '<S1>:769:16' else */
            /* '<S1>:769:17' om_con=boolean(0); */
						rtDW->om_con = false;
          }
        } else {
          /* '<S1>:769:16' else */
          /* '<S1>:769:17' om_con=boolean(0); */
					rtDW->om_con = false;
        }
      } else {
        /* '<S1>:769:16' else */
        /* '<S1>:769:17' om_con=boolean(0); */
				rtDW->om_con = false;
      }
    } else {
      /* '<S1>:769:19' else */
      /* '<S1>:769:20' om_con=boolean(0); */
			rtDW->om_con = false;
    }

    /* End of Inport: '<Root>/ElectricalIDConfig' */
  }

	if (!rtDW->om_con) {
    /* Increases the DutyCycle by 1% every 2 seconds, if the motor isn't */
    /* rotating properly */
    /* '<S1>:769:26' DutyCycle = DutyCycle + 0.01; */
		rtDW->DutyCycle += 0.01F;

    /* Simulation 0.001 | Real 0.01 */
  }

	/* '<S1>:769:23' if(om_con == 0) */
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function TurnMotor
 */
static void TurnMotor(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
	real32_T ElectricalID_output_o_tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'TurnMotor': '<S1>:380' */
  /* '<S1>:380:3' sineCounter = single(counter); */
  /*  rechtslauf */
  /* '<S1>:380:6' ElectricalID_output.PWM_Switch_0 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2)+0.5; */
	ElectricalID_output_o_tmp = 50.2654839F * (real32_T) rtDW->counter * rtU->GlobalConfig_out.sampleTimeISR;

  /* Outport: '<Root>/ElectricalID_output' */
	rtY->ElectricalID_output_o.PWM_Switch_0 = sinf(ElectricalID_output_o_tmp + 1.57079637F) * (0.5F * rtDW->DutyCycle) + 0.5F;

  /* '<S1>:380:7' ElectricalID_output.PWM_Switch_2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2)+0.5; */
	rtY->ElectricalID_output_o.PWM_Switch_2 = sinf((ElectricalID_output_o_tmp - 2.09439516F) + 1.57079637F) * (0.5F * rtDW->DutyCycle) + 0.5F;

  /* '<S1>:380:8' ElectricalID_output.PWM_Switch_4 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+2*pi/3+pi/2)+0.5; */
	rtY->ElectricalID_output_o.PWM_Switch_4 = sinf((ElectricalID_output_o_tmp + 2.09439516F) + 1.57079637F) * (0.5F * rtDW->DutyCycle) + 0.5F;

  /*  linkslauf */
  /*  ElectricalID_output.PWM_Switch_0 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2); */
  /*  ElectricalID_output.PWM_Switch_2 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+2*pi/3+pi/2); */
  /*  ElectricalID_output.PWM_Switch_4 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2); */
}

/* Function for Chart: '<Root>/ElectricalID' */
static void evaluate_Turn_DC(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  int32_T k;
  real32_T c_y[5];
  real32_T tmp;
  uint32_T y;

  /* Inport: '<Root>/GlobalConfig' */
  /* During 'evaluate_Turn_DC': '<S1>:379' */
  /* '<S1>:383:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 && (om_con==1 || DC_manual == 1); */
	if (rtU->GlobalConfig_out.ACCEPT && (rtDW->om_con || rtDW->DC_manual)) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* Transition: '<S1>:383' */
    /* Exit 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:27' ElectricalID_output.PWM_Switch_0 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

    /* '<S1>:379:28' ElectricalID_output.PWM_Switch_2 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;

    /* '<S1>:379:29' ElectricalID_output.PWM_Switch_4 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;
		rtDW->is_ElectricalID = IN_alignRotor_d_on;
		rtDW->temporalCounter_i1 = 0U;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'alignRotor_d_on': '<S1>:3' */
    /* '<S1>:3:4' ElectricalID_FOC_output.activeState = uint16(120); */
		rtY->ElectricalID_FOC_output.activeState = 120U;

    /* '<S1>:3:5' counter = uint32(1); */
		rtDW->counter = 1U;
  } else {
    /* '<S1>:379:13' if(DC_manual == 0) */
		if (!rtDW->DC_manual) {
      /* Inport: '<Root>/ActualValues' */
      /* averages the last 0.1s */
      /* '<S1>:379:14' omega_sum=omega_sum+single(ActualValues.omega_m); */
			rtDW->omega_sum += rtU->ActualValues_i.omega_m;

      /* '<S1>:379:15' if(mod(counter,uint32(0.1/GlobalConfig.sampleTimeISR))==0) */
			tmp = roundf(0.1F / rtU->GlobalConfig_out.sampleTimeISR);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          y = (uint32_T)tmp;
        } else {
          y = 0U;
        }
      } else {
        y = MAX_uint32_T;
      }

      if (y == 0U) {
				y = rtDW->counter;
      } else {
				y = rtDW->counter - rtDW->counter / y * y;
      }

      if (y == 0U) {
        /* '<S1>:379:16' RefreshDataRegister; */
				RefreshDataRegister(rtDW);

        /* '<S1>:379:17' omega_register(1,1)=omega_sum*(GlobalConfig.sampleTimeISR/0.1); */
				rtDW->omega_register[0] = rtU->GlobalConfig_out.sampleTimeISR / 0.1F * rtDW->omega_sum;

        /* '<S1>:379:18' omega_sum=single(0); */
				rtDW->omega_sum = 0.0F;
      }

      /* '<S1>:379:20' if(mod(counter,uint32(2/GlobalConfig.sampleTimeISR))==0) */
			tmp = roundf(2.0F / rtU->GlobalConfig_out.sampleTimeISR);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          y = (uint32_T)tmp;
        } else {
          y = 0U;
        }
      } else {
        y = MAX_uint32_T;
      }

      if (y == 0U) {
				y = rtDW->counter;
      } else {
				y = rtDW->counter - rtDW->counter / y * y;
      }

      if (y == 0U) {
        /* after 2s omega will be evaluated */
        /* '<S1>:379:21' DutyCycle_mod(abs(omega_register)); */
        for (k = 0; k < 5; k++) {
					c_y[k] = fabsf(rtDW->omega_register[k]);
        }

				DutyCycle_mod(c_y, rtU, rtDW);
      }
    }

    /* '<S1>:379:24' counter = counter + 1; */
		y = rtDW->counter + /*MW:OvSatOk*/1U;
		if (rtDW->counter + 1U < rtDW->counter) {
      y = MAX_uint32_T;
    }

		rtDW->counter = y;

    /* '<S1>:379:25' TurnMotor; */
		TurnMotor(rtU, rtY, rtDW);
  }

	/* End of Inport: '<Root>/GlobalConfig' */
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function DutyCycle_mod(ia_reg_in)
 */
static void DutyCycle_mod_o(real32_T ia_reg_in, ExtU *rtU, DW *rtDW)
{
  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'DutyCycle_mod': '<S1>:796' */
  /* '<S1>:796:3' mean_ia_reg=mean(ia_reg_in); */
  /* determines if the mean value is below the step-response current limit */
  /* '<S1>:796:5' if(mean_ia_reg < 0.5*GlobalConfig.ratCurrent) */
	if (ia_reg_in < 0.5F * rtU->GlobalConfig_out.ratCurrent) {
    /* Current limit for step response   */
    /* '<S1>:796:6' ia_valid=boolean(0); */
		rtDW->ia_valid = false;
  } else {
    /* '<S1>:796:7' else */
    /* '<S1>:796:8' ia_valid=boolean(1); */
		rtDW->ia_valid = true;
  }

  /* End of Inport: '<Root>/GlobalConfig' */
  /* '<S1>:796:11' if(ia_valid == 0) */
	if (!rtDW->ia_valid) {
    /* Increases the DutyCycle by 0.5% every 0.5 second, if the step response */
    /* is below the current limit */
    /* '<S1>:796:14' DutyCycle = DutyCycle + 0.005; */
		rtDW->DutyCycle += 0.005F;

    /* Simulation 0.001 | Real 0.005 */
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void findDutyCycle(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  real_T tmp_0;
  real32_T tmp;
  uint32_T qY;

  /* Inport: '<Root>/GlobalConfig' */
  /* During 'findDutyCycle': '<S1>:789' */
  /* '<S1>:790:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 && (ia_valid==1 ||DC_manual == 1); */
	if (rtU->GlobalConfig_out.ACCEPT && (rtDW->ia_valid || rtDW->DC_manual)) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* Transition: '<S1>:790' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:29' ElectricalID_output.PWM_Switch_0 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;
		rtDW->is_ElectricalID = IN_alignRotor_d_off2;
		rtDW->temporalCounter_i1 = 0U;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'alignRotor_d_off2': '<S1>:848' */
    /* '<S1>:848:4' ElectricalID_FOC_output.activeState = uint16(131); */
		rtY->ElectricalID_FOC_output.activeState = 131U;

    /* '<S1>:789:14' if(DC_manual == 0 && ia_valid==0) */
	} else if ((!rtDW->DC_manual) && (!rtDW->ia_valid)) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:789:15' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = rtDW->DutyCycle;

    /* '<S1>:789:16' if(counter < (0.4/GlobalConfig.sampleTimeISR)) */
		tmp_0 = 0.4F / rtU->GlobalConfig_out.sampleTimeISR;
		if (rtDW->counter < tmp_0) {
      /* '<S1>:789:17' counter = counter +1; */
			qY = rtDW->counter + /*MW:OvSatOk*/1U;
			if (rtDW->counter + 1U < rtDW->counter) {
        qY = MAX_uint32_T;
      }

			rtDW->counter = qY;
		} else if ((rtDW->counter >= tmp_0) && ((real_T) rtDW->counter < 0.5F / rtU->GlobalConfig_out.sampleTimeISR)) {
      /* '<S1>:789:18' elseif(counter >= (0.4/GlobalConfig.sampleTimeISR) &&.... */
      /* '<S1>:789:19'             counter < (0.5/GlobalConfig.sampleTimeISR)) */
      /* . */
      /* '<S1>:789:20' counter = counter +1; */
			qY = rtDW->counter + /*MW:OvSatOk*/1U;
			if (rtDW->counter + 1U < rtDW->counter) {
        qY = MAX_uint32_T;
      }

			rtDW->counter = qY;

      /* Inport: '<Root>/ActualValues' */
      /* '<S1>:789:21' ia_sum=ia_sum+single(ActualValues.i_a); */
			rtDW->ia_sum += rtU->ActualValues_i.i_a;
    } else {
			tmp = roundf(0.5F / rtU->GlobalConfig_out.sampleTimeISR);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          qY = (uint32_T)tmp;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

			if (rtDW->counter == qY) {
        /* '<S1>:789:22' elseif(counter == uint32(0.5/GlobalConfig.sampleTimeISR)) */
        /* '<S1>:789:23' DutyCycle_mod(abs(ia_sum*(GlobalConfig.sampleTimeISR/0.1))); */
				DutyCycle_mod_o(fabsf(rtDW->ia_sum * (rtU->GlobalConfig_out.sampleTimeISR / 0.1F)), rtU, rtDW);

        /* '<S1>:789:24' counter  = uint32(1); */
				rtDW->counter = 1U;

        /* '<S1>:789:25' ia_sum = single(0.0); */
				rtDW->ia_sum = 0.0F;
      }
    }
  }

	/* End of Inport: '<Root>/GlobalConfig' */
}

/* Function for Chart: '<Root>/ElectricalID' */
static void measure_psiPM(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  int32_T k;
  real32_T b_x;
  real32_T c_x;
  real32_T x;
  uint32_T qY;
  uint32_T qY_tmp;
  uint32_T qY_tmp_tmp;

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
  /* During 'measure_psiPM': '<S1>:405' */
  /* '<S1>:406:1' sf_internal_predicateOutput = ElectricalID_output.psiPM > 0; */
	if (rtY->ElectricalID_output_o.psiPM > 0.0F) {
    /* Transition: '<S1>:406' */
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:20' counter = uint32(1); */
		rtDW->counter = 1U;
		rtDW->is_ElectricalID = IN_stop;
		rtDW->temporalCounter_i1 = 0U;

    /* Entry 'stop': '<S1>:361' */
    /* state 10.1 */
    /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(151); */
		rtY->ElectricalID_FOC_output.activeState = 151U;

    /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
		rtY->ElectricalID_FOC_output.n_ref_FOC = 0.0F;
  } else {
    /* '<S1>:405:9' if(counter > wait_count && counter < (wait_count+1025)) */
		qY = rtDW->wait_count + 1025U;
		if (rtDW->wait_count + 1025U < rtDW->wait_count) {
      qY = MAX_uint32_T;
    }

		if ((rtDW->counter > rtDW->wait_count) && (rtDW->counter < qY)) {
      /* '<S1>:405:10' measArray1(counter-wait_count) = ActualValues.u_q; */
			qY_tmp_tmp = rtDW->counter - /*MW:OvSatOk*/rtDW->wait_count;
      qY_tmp = qY_tmp_tmp;
      qY = qY_tmp_tmp;
			if (qY_tmp_tmp > rtDW->counter) {
        qY = 0U;
        qY_tmp = 0U;
      }

			rtDW->measArray1[(int32_T) qY - 1] = rtU->ActualValues_i.u_q;

      /* '<S1>:405:11' d(counter-wait_count) = ActualValues.i_q; */
			rtDW->d[(int32_T) qY_tmp - 1] = rtU->ActualValues_i.i_q;

      /* '<S1>:405:12' i_est(counter-wait_count) = ActualValues.omega_el; */
      qY = qY_tmp_tmp;
			if (qY_tmp_tmp > rtDW->counter) {
        qY = 0U;
      }

			rtDW->i_est[(int32_T) qY - 1] = rtU->ActualValues_i.omega_el;
    }

    /* '<S1>:405:14' if(counter == (wait_count+1025)) */
		qY = rtDW->wait_count + 1025U;
		if (rtDW->wait_count + 1025U < rtDW->wait_count) {
      qY = MAX_uint32_T;
    }

		if (rtDW->counter == qY) {
      /* '<S1>:405:15' ElectricalID_output.psiPM = .... */
      /* '<S1>:405:16'         (mean(measArray1(1:1024))-mean(d(1:1024))*ElectricalID_output.R_s)/(mean(i_est(1:1024))); */
			x = rtDW->measArray1[0];
			b_x = rtDW->d[0];
			c_x = rtDW->i_est[0];
      for (k = 0; k < 1023; k++) {
				x += rtDW->measArray1[k + 1];
				b_x += rtDW->d[k + 1];
				c_x += rtDW->i_est[k + 1];
      }

			rtY->ElectricalID_output_o.psiPM = (x / 1024.0F - b_x / 1024.0F * rtY->ElectricalID_output_o.R_s) / (c_x / 1024.0F);

      /* . */
    }

    /* '<S1>:405:18' counter = counter + 1; */
		qY = rtDW->counter + /*MW:OvSatOk*/1U;
		if (rtDW->counter + 1U < rtDW->counter) {
      qY = MAX_uint32_T;
    }

		rtDW->counter = qY;
  }

  /* End of Outport: '<Root>/ElectricalID_output' */
}

real32_T rt_hypotf(real32_T u0, real32_T u1)
{
  real32_T a;
  real32_T b;
  real32_T y;
	a = fabsf(u0);
	b = fabsf(u1);
  if (a < b) {
    a /= b;
		y = sqrtf(a * a + 1.0F) * b;
  } else if (a > b) {
    b /= a;
		y = sqrtf(b * b + 1.0F) * a;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function u = goertzel
 *  goertzel algorithm for J calculation
 */
static real32_T goertzel(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
	int32_T k;
  real32_T Xg_im;
  real32_T Xg_re;
  real32_T ai;
	real32_T r;
  real32_T s0;
  real32_T s2;

  /* MATLAB Function 'goertzel': '<S1>:350' */
  /*  calculate momentum from i_q */
  /* '<S1>:350:6' for k=single(1):single(500) */
  /*  goertzel */
  /* '<S1>:350:11' k = single(2.0); */
  /*  coefficient number of the spectrum (40Hz) */
  /* '<S1>:350:12' N = 500; */
  /*  length of input signal */
  /* Precalculation of constants */
  /* '<S1>:350:15' A = 2*pi*k/N; */
  /* '<S1>:350:16' B = 2*cos(A); */
  /* '<S1>:350:17' C = exp(-j*A); */
  /* State variables */
  /* '<S1>:350:19' s0 = single(0.0); */
  /* '<S1>:350:20' s1 = single(0.0); */
	r = 0.0F;

  /* '<S1>:350:21' s2 = single(0.0); */
  s2 = 0.0F;

  /* Main loop for M */
  /* '<S1>:350:24' for i = 1:N */
	for (k = 0; k < 500; k++) {
    /* Inport: '<Root>/GlobalConfig' incorporates:
     *  Outport: '<Root>/ElectricalID_output'
     */
    /* '<S1>:350:7' d(k) = 1.5*GlobalConfig.polePairs*ElectricalID_output.psiPM*measArray1(k); */
		rtDW->d[k] = 1.5F * rtU->GlobalConfig_out.polePairs * rtY->ElectricalID_output_o.psiPM * rtDW->measArray1[k];

    /* N multiplications, 2N additions */
    /* '<S1>:350:25' s0 = d(i) +B*s1-s2; */
		s0 = (1.99936843F * r + rtDW->d[k]) - s2;

    /* corresponds to (16) */
    /* '<S1>:350:26' s2 = s1; */
		s2 = r;

    /* '<S1>:350:27' s1 = s0; */
		r = s0;
  }

  /* Finalizing calculations for M */
  /* '<S1>:350:31' s0 = B*s1-s2; */
  /* corresponds to (16) with zero input; 1 multiplication and 1 addition */
  /* '<S1>:350:32' Xg = s0-s1*C %corresponds to (17); 4 multiplications and 3 additions */
	Xg_re = (1.99936843F * r - s2) - r * 0.999684215F;
	Xg_im = 0.0F - r * -0.0251300968F;

  /* corresponds to (17); 4 multiplications and 3 additions */
  /* Reset state variables */
  /* '<S1>:350:35' s0 = single(0.0); */
  /* '<S1>:350:36' s1 = single(0.0); */
	r = 0.0F;

  /* '<S1>:350:37' s2 = single(0.0); */
  s2 = 0.0F;

  /* Main loop for omega_m */
  /* '<S1>:350:40' for i = 1:N */
	for (k = 0; k < 500; k++) {
    /* N multiplications, 2N additions */
    /* '<S1>:350:41' s0 = i_est(i) +B*s1-s2; */
		s0 = (1.99936843F * r + rtDW->i_est[k]) - s2;

    /* corresponds to (16) */
    /* '<S1>:350:42' s2 = s1; */
		s2 = r;

    /* '<S1>:350:43' s1 = s0; */
		r = s0;
  }

  /* Finalizing calculations for omega_m */
  /* '<S1>:350:47' s0 = B*s1-s2; */
  /* corresponds to (16) with zero input; 1 multiplication and 1 addition */
  /* '<S1>:350:48' Yg = s0-s1*C %corresponds to (17); 4 multiplications and 3 additions */
  /* corresponds to (17); 4 multiplications and 3 additions */
  /*  calculate value of transfer function  */
  /* '<S1>:350:53' Gg = Yg/Xg; */
  /*  calculate J from Gg */
  /* rotorInertia = abs(((1/viscFrictCoeff-Gg)*viscFrictCoeff)/(Gg*j*2*pi*20)); %with damping */
  /* '<S1>:350:56' ElectricalID_output.rotorInertia = abs(1/(Gg*j*2*pi*40)); */
	s2 = (1.99936843F * r - s2) - r * 0.999684215F;
	ai = 0.0F - r * -0.0251300968F;
  if (Xg_im == 0.0F) {
    if (ai == 0.0F) {
      s0 = s2 / Xg_re;
      Xg_im = 0.0F;
    } else if (s2 == 0.0F) {
      s0 = 0.0F;
      Xg_im = ai / Xg_re;
    } else {
      s0 = s2 / Xg_re;
      Xg_im = ai / Xg_re;
    }
  } else if (Xg_re == 0.0F) {
    if (s2 == 0.0F) {
      s0 = ai / Xg_im;
      Xg_im = 0.0F;
    } else if (ai == 0.0F) {
      s0 = 0.0F;
      Xg_im = -(s2 / Xg_im);
    } else {
      s0 = ai / Xg_im;
      Xg_im = -(s2 / Xg_im);
    }
  } else {
		r = fabsf(Xg_re);
		s0 = fabsf(Xg_im);
		if (r > s0) {
			r = Xg_im / Xg_re;
			Xg_im = r * Xg_im + Xg_re;
			s0 = (r * ai + s2) / Xg_im;
			Xg_im = (ai - r * s2) / Xg_im;
		} else if (s0 == r) {
      Xg_re = Xg_re > 0.0F ? 0.5F : -0.5F;
      Xg_im = Xg_im > 0.0F ? 0.5F : -0.5F;
			s0 = (s2 * Xg_re + ai * Xg_im) / r;
			Xg_im = (ai * Xg_re - s2 * Xg_im) / r;
    } else {
			r = Xg_re / Xg_im;
			Xg_im += r * Xg_re;
			s0 = (r * s2 + ai) / Xg_im;
			Xg_im = (r * ai - s2) / Xg_im;
    }
  }

  Xg_im = (0.0F - Xg_im) * 2.0F * 3.14159274F * 40.0F;
  s2 = 2.0F * s0 * 3.14159274F * 40.0F;
  if (s2 == 0.0F) {
    s0 = 1.0F / Xg_im;
    Xg_im = 0.0F;
  } else if (Xg_im == 0.0F) {
    s0 = 0.0F;
    Xg_im = -(1.0F / s2);
  } else {
		r = fabsf(Xg_im);
		s0 = fabsf(s2);
		if (r > s0) {
			r = s2 / Xg_im;
			Xg_im += r * s2;
      s0 = 1.0F / Xg_im;
			Xg_im = (0.0F - r) / Xg_im;
		} else if (s0 == r) {
			s0 = (Xg_im > 0.0F ? 0.5F : -0.5F) / r;
			Xg_im = (0.0F - (s2 > 0.0F ? 0.5F : -0.5F)) / r;
    } else {
			r = Xg_im / s2;
			Xg_im = r * Xg_im + s2;
			s0 = r / Xg_im;
      Xg_im = -1.0F / Xg_im;
    }
  }

  /* Outport: '<Root>/ElectricalID_output' */
	rtY->ElectricalID_output_o.rotorInertia = rt_hypotf(s0, Xg_im);

  /* without damping */
  /* '<S1>:350:57' u = single(ElectricalID_output.rotorInertia); */
	return rtY->ElectricalID_output_o.rotorInertia;
}

/* Function for Chart: '<Root>/ElectricalID' */
static void inv(const real32_T x[4], real32_T y[4])
{
  real32_T r;
  real32_T t;
	if (fabsf(x[1]) > fabsf(x[0])) {
    r = x[0] / x[1];
    t = 1.0F / (r * x[3] - x[2]);
    y[0] = x[3] / x[1] * t;
    y[1] = -t;
    y[2] = -x[2] / x[1] * t;
    y[3] = r * t;
  } else {
    r = x[1] / x[0];
    t = 1.0F / (x[3] - r * x[2]);
    y[0] = x[3] / x[0] * t;
    y[1] = -r * t;
    y[2] = -x[2] / x[0] * t;
    y[3] = t;
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void mtimes(const real32_T A[2048], const real32_T B_0[1024], real32_T C[2])
{
	int32_T i;
	real32_T B_1;
  C[0] = 0.0F;
  C[1] = 0.0F;
	for (i = 0; i < 1024; i++) {
		B_1 = B_0[i];
		C[0] += A[i] * B_1;
		C[1] += A[i + 1024] * B_1;
  }
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function LM_algorithm
 *  Startwerte Festlegen
 * U0 = U_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm(real32_T *L_est, real32_T *R_est, ExtU *rtU, DW *rtDW)
{
  int32_T H_tmp;
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;
  real32_T L_lm;
  real32_T R_lm;
  real32_T e_lm;

  /* MATLAB Function 'LM_algorithm': '<S1>:92' */
  /* '<S1>:92:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S1>:92:7' L0 = single(0.000005); */
  /*  Induktivität in Henry (50µH ... 50 mH) */
  /* '<S1>:92:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S1>:92:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S1>:92:25' for it=uint16(1):n_iters */
	for (it = 0; it < rtDW->n_iters; it++) {
    /* '<S1>:92:26' if updateJ == 1 */
		if (rtDW->updateJ) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S1>:92:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S1>:92:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S1>:92:40' d(1:1024) = measArray1(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* Inport: '<Root>/GlobalConfig' */
        /* '<S1>:92:29' J(k,:) = [- (U0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S1>:92:30'                  - 1))/R_est^2 - (U0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S1>:92:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S1>:92:32'                  , (U0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S1>:92:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
				R_lm = expf(-((((real32_T) k + 1.0F) - 1.0F) * *R_est * rtU->GlobalConfig_out.sampleTimeISR) / *L_est);
				L_lm = (((real32_T) k + 1.0F) - 1.0F) * rtDW->U0 * rtU->GlobalConfig_out.sampleTimeISR;
				rtDW->J[k] = -((R_lm - 1.0F) * rtDW->U0) / (*R_est * *R_est) - L_lm * R_lm / (*L_est * *R_est);
				rtDW->J[k + 2048] = R_lm * L_lm / (*L_est * *L_est);

        /* Inport: '<Root>/GlobalConfig' */
        /* . */
        /* . */
        /* . */
        /* . */
        /* '<S1>:92:37' i_est(k) = U0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
				rtDW->i_est[k] = (1.0F - expf((((real32_T) k + 1.0F) - 1.0F) * rtU->GlobalConfig_out.sampleTimeISR * -*R_est / *L_est)) * (rtDW->U0 / *R_est);
				rtDW->d[k] = rtDW->measArray1[k] - rtDW->i_est[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S1>:92:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          H_tmp = k + (i << 1);
					rtDW->H[H_tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
						rtDW->H[H_tmp] += rtDW->J[(k << 11) + i_0] * rtDW->J[(i << 11) + i_0];
          }
        }
      }

      /* '<S1>:92:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S1>:92:44' e = dot(d,d); */
				rtDW->e = 0.0F;
        for (k = 0; k < 2048; k++) {
					rtDW->e += rtDW->d[k] * rtDW->d[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Dämpfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S1>:92:49' H(1,1) = H(1,1) + lambda; */
		rtDW->H[0] += rtDW->lambda;

    /* '<S1>:92:50' H(2,2)=H(2,2)+lambda; */
		rtDW->H[3] += rtDW->lambda;

    /*  Neue Paramterschätzung berechnen */
    /* '<S1>:92:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
		inv(rtDW->H, rtDW->fv4);
    for (k = 0; k < 2; k++) {
			memcpy(&rtDW->fv[k << 10], &rtDW->J[k << 11], sizeof(real32_T) << 10U);
    }

		mtimes(rtDW->fv, &rtDW->d[0], rtDW->fv5);

    /* '<S1>:92:54' R_lm = R_est + dp(1); */
		R_lm = (-rtDW->fv4[0] * rtDW->fv5[0] + -rtDW->fv4[2] * rtDW->fv5[1]) + *R_est;

    /* '<S1>:92:55' L_lm = L_est + dp(2); */
		L_lm = (-rtDW->fv4[1] * rtDW->fv5[0] + -rtDW->fv4[3] * rtDW->fv5[1]) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S1>:92:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S1>:92:62' d(1:1024) = measArray1(1:1024) - i_est(1:1024); */
    /* '<S1>:92:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* Inport: '<Root>/GlobalConfig' */
      /* '<S1>:92:59' i_est(k) = U0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
			rtDW->i_est[k] = (1.0F - expf((((real32_T) k + 1.0F) - 1.0F) * rtU->GlobalConfig_out.sampleTimeISR * -R_lm / L_lm)) * (rtDW->U0 / R_lm);
			rtDW->d[k] = rtDW->measArray1[k] - rtDW->i_est[k];
			e_lm += rtDW->d[k] * rtDW->d[k];
    }

    /*  Fallunterscheidung ob Fehler größer oder kleiner geworden ist */
    /* '<S1>:92:66' if e_lm < e */
		if (e_lm < rtDW->e) {
      /* '<S1>:92:67' lambda = lambda/10; */
			rtDW->lambda /= 10.0F;

      /* '<S1>:92:68' R_est = R_lm; */
      *R_est = R_lm;

      /* '<S1>:92:69' L_est = L_lm; */
      *L_est = L_lm;

      /* '<S1>:92:70' e = e_lm; */
			rtDW->e = e_lm;

      /* '<S1>:92:71' updateJ = boolean(1); */
			rtDW->updateJ = true;
    } else {
      /* '<S1>:92:72' else */
      /* '<S1>:92:73' updateJ = boolean(0); */
			rtDW->updateJ = false;

      /* '<S1>:92:74' lambda = lambda*10; */
			rtDW->lambda *= 10.0F;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void stepResponse(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  int32_T k;
  real32_T L_est;
  real32_T R_est;
  uint32_T qY;

  /* During 'stepResponse': '<S1>:5' */
  /* '<S1>:95:1' sf_internal_predicateOutput = counter == 1026; */
	if (rtDW->counter == 1026U) {
    /* Transition: '<S1>:95' */
    /* Exit 'stepResponse': '<S1>:5' */
    /* '<S1>:5:32' ElectricalID_FOC_output.activeState = uint16(22); */
		rtDW->is_ElectricalID = IN_Levenberg_Marquardt;
		rtDW->temporalCounter_i1 = 0U;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'Levenberg_Marquardt': '<S1>:91' */
    /* state 3.0 */
    /* '<S1>:91:4' ElectricalID_FOC_output.activeState = uint16(141); */
		rtY->ElectricalID_FOC_output.activeState = 141U;

    /* '<S1>:91:5' LM_algorithm; */
		LM_algorithm(&L_est, &R_est, rtU, rtDW);

    /* Outport: '<Root>/ElectricalID_output' */
    /*  calculate R and L. Considering that all three phases */
    /*  are connected and that a delta connected winding has */
    /*  to be calculated into star connected values, the factor */
    /*  is 2/3 for delta and star connected windings. */
    /*  Therefore Rs and Ld are the values expressed in */
    /*  star connection */
    /* '<S1>:91:12' ElectricalID_output.R_s = (R_est-R_corr)*2.0/3.0; */
		rtY->ElectricalID_output_o.R_s = (R_est - rtDW->R_corr) * 2.0F / 3.0F;

    /* '<S1>:91:13' ElectricalID_output.L_d = L_est*2.0/3.0; */
		rtY->ElectricalID_output_o.L_d = L_est * 2.0F / 3.0F;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:5:7' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = rtDW->DutyCycle;

    /* '<S1>:5:8' if(counter <= 1024) */
		if (rtDW->counter <= 1024U) {
      /* '<S1>:5:9' if(counter > 1) */
			if (rtDW->counter > 1U) {
        /* '<S1>:5:10' measArray1(counter-1) = ActualValues.i_a; */
				qY = rtDW->counter - /*MW:OvSatOk*/1U;
				if (rtDW->counter - 1U > rtDW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
				rtDW->measArray1[(int32_T) qY - 1] = rtU->ActualValues_i.i_a;

        /* '<S1>:5:11' if(mod(counter,5) == 0) */
				if (rtDW->counter - rtDW->counter / 5U * 5U == 0U) {
          /* '<S1>:5:12' Ustep(z-1) = ActualValues.u_a; */
					qY = rtDW->z - 1U;
					if (rtDW->z - 1U > rtDW->z) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
					rtDW->Ustep[(int32_T) qY - 1] = rtU->ActualValues_i.u_a;

          /* '<S1>:5:13' z = z + 1; */
					qY = rtDW->z + 1U;
					if (rtDW->z + 1U > 65535U) {
            qY = 65535U;
          }

					rtDW->z = (uint16_T) qY;
        }

        /* '<S1>:5:15' counter = counter + 1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;
      }

      /* '<S1>:5:17' if(counter == 1) */
			if (rtDW->counter == 1U) {
        /* '<S1>:5:18' counter = counter + 1 */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;

        /* Inport: '<Root>/ActualValues' */
        /* '<S1>:5:19' Ustep(1) = ActualValues.u_a; */
				rtDW->Ustep[0] = rtU->ActualValues_i.u_a;

        /* '<S1>:5:20' z = z + 1; */
				qY = rtDW->z + 1U;
				if (rtDW->z + 1U > 65535U) {
          qY = 65535U;
        }

				rtDW->z = (uint16_T) qY;
      }
    } else {
      /* '<S1>:5:22' else */
      /* '<S1>:5:23' if(counter == 1025) */
			if (rtDW->counter == 1025U) {
        /* '<S1>:5:24' measArray1(counter-1) = ActualValues.i_a; */
				qY = rtDW->counter - /*MW:OvSatOk*/1U;
				if (rtDW->counter - 1U > rtDW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
				rtDW->measArray1[(int32_T) qY - 1] = rtU->ActualValues_i.i_a;

        /* '<S1>:5:25' Ustep(z-1) = ActualValues.u_a; */
				qY = rtDW->z - 1U;
				if (rtDW->z - 1U > rtDW->z) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
				rtDW->Ustep[(int32_T) qY - 1] = rtU->ActualValues_i.u_a;

        /* '<S1>:5:26' U0 = mean(Ustep); */
				L_est = rtDW->Ustep[0];
        for (k = 0; k < 204; k++) {
					L_est += rtDW->Ustep[k + 1];
        }

				rtDW->U0 = L_est / 205.0F;
      }

      /* Outport: '<Root>/ElectricalID_output' */
      /* '<S1>:5:28' ElectricalID_output.PWM_Switch_0 = single(0); */
			rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

      /* '<S1>:5:29' counter = counter + 1; */
			qY = rtDW->counter + /*MW:OvSatOk*/1U;
			if (rtDW->counter + 1U < rtDW->counter) {
        qY = MAX_uint32_T;
      }

			rtDW->counter = qY;
    }
  }
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function LM_algorithm_Lq
 *  Startwerte Festlegen
 * U0 = U_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_Lq(real32_T *L_est, ExtU *rtU, DW *rtDW)
{
  int32_T H_tmp;
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;
  real32_T L_lm;
  real32_T R_est;
  real32_T R_lm;
  real32_T e_lm;

  /* MATLAB Function 'LM_algorithm_Lq': '<S1>:281' */
  /* '<S1>:281:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S1>:281:7' L0 = single(0.000005); */
  /*  Induktivität in Henry (50µH ... 50 mH) */
  /* '<S1>:281:9' R_est   = R0; */
  R_est = 0.001F;

  /* '<S1>:281:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S1>:281:25' for it=uint16(1):n_iters */
	for (it = 0; it < rtDW->n_iters; it++) {
    /* '<S1>:281:26' if updateJ == 1 */
		if (rtDW->updateJ) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S1>:281:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S1>:281:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S1>:281:40' d(1:1024) = measArray1(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* Inport: '<Root>/GlobalConfig' */
        /* '<S1>:281:29' J(k,:) = [- (U0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S1>:281:30'                  - 1))/R_est^2 - (U0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S1>:281:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S1>:281:32'                  , (U0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S1>:281:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
				R_lm = expf(-((((real32_T) k + 1.0F) - 1.0F) * R_est * rtU->GlobalConfig_out.sampleTimeISR) / *L_est);
				L_lm = (((real32_T) k + 1.0F) - 1.0F) * rtDW->U0 * rtU->GlobalConfig_out.sampleTimeISR;
				rtDW->J[k] = -((R_lm - 1.0F) * rtDW->U0) / (R_est * R_est) - L_lm * R_lm / (*L_est * R_est);
				rtDW->J[k + 2048] = R_lm * L_lm / (*L_est * *L_est);

        /* Inport: '<Root>/GlobalConfig' */
        /* . */
        /* . */
        /* . */
        /* . */
        /* '<S1>:281:37' i_est(k) = U0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
				rtDW->i_est[k] = (1.0F - expf((((real32_T) k + 1.0F) - 1.0F) * rtU->GlobalConfig_out.sampleTimeISR * -R_est / *L_est)) * (rtDW->U0 / R_est);
				rtDW->d[k] = rtDW->measArray1[k] - rtDW->i_est[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S1>:281:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          H_tmp = k + (i << 1);
					rtDW->H[H_tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
						rtDW->H[H_tmp] += rtDW->J[(k << 11) + i_0] * rtDW->J[(i << 11) + i_0];
          }
        }
      }

      /* '<S1>:281:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S1>:281:44' e = dot(d,d); */
				rtDW->e = 0.0F;
        for (k = 0; k < 2048; k++) {
					rtDW->e += rtDW->d[k] * rtDW->d[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Dämpfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S1>:281:49' H(1,1) = H(1,1) + lambda; */
		rtDW->H[0] += rtDW->lambda;

    /* '<S1>:281:50' H(2,2)=H(2,2)+lambda; */
		rtDW->H[3] += rtDW->lambda;

    /*  Neue Paramterschätzung berechnen */
    /* '<S1>:281:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
		inv(rtDW->H, rtDW->fv2);
    for (k = 0; k < 2; k++) {
			memcpy(&rtDW->fv1[k << 10], &rtDW->J[k << 11], sizeof(real32_T) << 10U);
    }

		mtimes(rtDW->fv1, &rtDW->d[0], rtDW->fv3);

    /* '<S1>:281:54' R_lm = R_est + dp(1); */
		R_lm = (-rtDW->fv2[0] * rtDW->fv3[0] + -rtDW->fv2[2] * rtDW->fv3[1]) + R_est;

    /* '<S1>:281:55' L_lm = L_est + dp(2); */
		L_lm = (-rtDW->fv2[1] * rtDW->fv3[0] + -rtDW->fv2[3] * rtDW->fv3[1]) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S1>:281:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S1>:281:62' d(1:1024) = measArray1(1:1024) - i_est(1:1024); */
    /* '<S1>:281:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* Inport: '<Root>/GlobalConfig' */
      /* '<S1>:281:59' i_est(k) = U0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
			rtDW->i_est[k] = (1.0F - expf((((real32_T) k + 1.0F) - 1.0F) * rtU->GlobalConfig_out.sampleTimeISR * -R_lm / L_lm)) * (rtDW->U0 / R_lm);
			rtDW->d[k] = rtDW->measArray1[k] - rtDW->i_est[k];
			e_lm += rtDW->d[k] * rtDW->d[k];
    }

    /*  Fallunterscheidung ob Fehler größer oder kleiner geworden ist */
    /* '<S1>:281:66' if e_lm < e */
		if (e_lm < rtDW->e) {
      /* '<S1>:281:67' lambda = lambda/10; */
			rtDW->lambda /= 10.0F;

      /* '<S1>:281:68' R_est = R_lm; */
      R_est = R_lm;

      /* '<S1>:281:69' L_est = L_lm; */
      *L_est = L_lm;

      /* '<S1>:281:70' e = e_lm; */
			rtDW->e = e_lm;

      /* '<S1>:281:71' updateJ = boolean(1); */
			rtDW->updateJ = true;
    } else {
      /* '<S1>:281:72' else */
      /* '<S1>:281:73' updateJ = boolean(0); */
			rtDW->updateJ = false;

      /* '<S1>:281:74' lambda = lambda*10; */
			rtDW->lambda *= 10.0F;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void stepResponse_q(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  int32_T k;
  real32_T L_est;
  uint32_T qY;

  /* During 'stepResponse_q': '<S1>:277' */
  /* '<S1>:279:1' sf_internal_predicateOutput = counter == 1026; */
	if (rtDW->counter == 1026U) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* Transition: '<S1>:279' */
    /* Exit 'stepResponse_q': '<S1>:277' */
    /* '<S1>:277:38' ElectricalID_output.outputMode          = [boolean(1),boolean(1),boolean(1)]; */
		rtY->ElectricalID_output_o.outputMode[0] = true;
		rtY->ElectricalID_output_o.outputMode[1] = true;
		rtY->ElectricalID_output_o.outputMode[2] = true;
		rtDW->is_ElectricalID = IN_Levenberg_Marquardt_q;
		rtDW->temporalCounter_i1 = 0U;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'Levenberg_Marquardt_q': '<S1>:278' */
    /* '<S1>:278:4' ElectricalID_FOC_output.activeState = uint16(143); */
		rtY->ElectricalID_FOC_output.activeState = 143U;

    /* '<S1>:278:5' LM_algorithm_Lq; */
		LM_algorithm_Lq(&L_est, rtU, rtDW);

    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:278:6' ElectricalID_output.L_q = L_est*0.5; */
		rtY->ElectricalID_output_o.L_q = L_est * 0.5F;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:277:12' ElectricalID_output.PWM_Switch_4 = single(DutyCycle); */
		rtY->ElectricalID_output_o.PWM_Switch_4 = rtDW->DutyCycle;

    /* '<S1>:277:13' if(counter <= 1024) */
		if (rtDW->counter <= 1024U) {
      /* '<S1>:277:14' if(counter > 1) */
			if (rtDW->counter > 1U) {
        /* '<S1>:277:15' measArray1(counter-1) = ActualValues.i_c; */
				qY = rtDW->counter - /*MW:OvSatOk*/1U;
				if (rtDW->counter - 1U > rtDW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
				rtDW->measArray1[(int32_T) qY - 1] = rtU->ActualValues_i.i_c;

        /* '<S1>:277:16' if(mod(counter,5) == 0) */
				if (rtDW->counter - rtDW->counter / 5U * 5U == 0U) {
          /* '<S1>:277:17' Ustep(z-1) = ActualValues.u_b+ActualValues.u_c; */
					qY = rtDW->z - 1U;
					if (rtDW->z - 1U > rtDW->z) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
					rtDW->Ustep[(int32_T) qY - 1] = rtU->ActualValues_i.u_b + rtU->ActualValues_i.u_c;

          /* '<S1>:277:18' z = z + 1; */
					qY = rtDW->z + 1U;
					if (rtDW->z + 1U > 65535U) {
            qY = 65535U;
          }

					rtDW->z = (uint16_T) qY;
        }

        /* '<S1>:277:20' counter = counter + 1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;
      }

      /* '<S1>:277:22' if(counter == 1) */
			if (rtDW->counter == 1U) {
        /* '<S1>:277:23' counter = counter + 1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;

        /* Inport: '<Root>/ActualValues' */
        /* '<S1>:277:24' Ustep(1) = ActualValues.u_b+ActualValues.u_c; */
				rtDW->Ustep[0] = rtU->ActualValues_i.u_b + rtU->ActualValues_i.u_c;

        /* '<S1>:277:25' z = z + 1; */
				qY = rtDW->z + 1U;
				if (rtDW->z + 1U > 65535U) {
          qY = 65535U;
        }

				rtDW->z = (uint16_T) qY;
      }
    } else {
      /* '<S1>:277:27' else */
      /* '<S1>:277:28' if(counter == 1025) */
			if (rtDW->counter == 1025U) {
        /* '<S1>:277:29' measArray1(counter-1) = ActualValues.i_c; */
				qY = rtDW->counter - /*MW:OvSatOk*/1U;
				if (rtDW->counter - 1U > rtDW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
				rtDW->measArray1[(int32_T) qY - 1] = rtU->ActualValues_i.i_c;

        /* '<S1>:277:30' Ustep(z-1) = ActualValues.u_b+ActualValues.u_c; */
				qY = rtDW->z - 1U;
				if (rtDW->z - 1U > rtDW->z) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
				rtDW->Ustep[(int32_T) qY - 1] = rtU->ActualValues_i.u_b + rtU->ActualValues_i.u_c;

        /* '<S1>:277:31' U0 = mean(Ustep); */
				L_est = rtDW->Ustep[0];
        for (k = 0; k < 204; k++) {
					L_est += rtDW->Ustep[k + 1];
        }

				rtDW->U0 = L_est / 205.0F;
      }

      /* Outport: '<Root>/ElectricalID_output' */
      /* '<S1>:277:34' ElectricalID_output.PWM_Switch_4 = single(0); */
			rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;

      /* '<S1>:277:35' counter = counter + 1; */
			qY = rtDW->counter + /*MW:OvSatOk*/1U;
			if (rtDW->counter + 1U < rtDW->counter) {
        qY = MAX_uint32_T;
      }

			rtDW->counter = qY;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void exit_internal_ElectricalID(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  /* Exit Internal 'ElectricalID': '<S1>:761' */
	switch (rtDW->is_ElectricalID) {
	case IN_Levenberg_Marquardt:
    /* Exit 'Levenberg_Marquardt': '<S1>:91' */
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_Levenberg_Marquardt_q:
    /* Exit 'Levenberg_Marquardt_q': '<S1>:278' */
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_alignRotor_d_off:
    /* Outport: '<Root>/ElectricalID_output' incorporates:
     *  Inport: '<Root>/ActualValues'
     */
    /* Exit 'alignRotor_d_off': '<S1>:53' */
    /* '<S1>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
		rtY->ElectricalID_output_o.thetaOffset = rtU->ActualValues_i.theta_m;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_alignRotor_d_off1:
    /* Exit 'alignRotor_d_off1': '<S1>:417' */
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_alignRotor_d_off2:
    /* Exit 'alignRotor_d_off2': '<S1>:848' */
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_alignRotor_d_on:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'alignRotor_d_on': '<S1>:3' */
    /* '<S1>:3:16' ElectricalID_output.PWM_Switch_0 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_alignRotor_d_on1:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'alignRotor_d_on1': '<S1>:415' */
    /* '<S1>:415:15' ElectricalID_output.PWM_Switch_0 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

    /* '<S1>:415:16' DutyCycle=single(0.0); */
		rtDW->DutyCycle = 0.0F;

    /* resets the DC and DC_manual flag, so that for the step-response */
    /* '<S1>:415:17' DC_manual=boolean(0); */
		rtDW->DC_manual = false;

    /* a new DC can be entered */
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_alignRotor_q_on:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'alignRotor_q_on': '<S1>:410' */
    /* '<S1>:410:17' ElectricalID_output.PWM_Switch_2 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_evaluate_Turn_DC:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:27' ElectricalID_output.PWM_Switch_0 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

    /* '<S1>:379:28' ElectricalID_output.PWM_Switch_2 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;

    /* '<S1>:379:29' ElectricalID_output.PWM_Switch_4 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_findDutyCycle:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:29' ElectricalID_output.PWM_Switch_0 = single(0); */
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_measure_psiPM:
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:20' counter = uint32(1); */
		rtDW->counter = 1U;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_rotorInertiaEstimation:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'rotorInertiaEstimation': '<S1>:337' */
    /* '<S1>:337:21' ElectricalID_output.TrainInertia = goertzel; */
		rtY->ElectricalID_output_o.TrainInertia = goertzel(rtU, rtY, rtDW);
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_stepResponse:
    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Exit 'stepResponse': '<S1>:5' */
    /* '<S1>:5:32' ElectricalID_FOC_output.activeState = uint16(22); */
		rtY->ElectricalID_FOC_output.activeState = 22U;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_stepResponse_q:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'stepResponse_q': '<S1>:277' */
    /* '<S1>:277:38' ElectricalID_output.outputMode          = [boolean(1),boolean(1),boolean(1)]; */
		rtY->ElectricalID_output_o.outputMode[0] = true;
		rtY->ElectricalID_output_o.outputMode[1] = true;
		rtY->ElectricalID_output_o.outputMode[2] = true;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

	case IN_waitState:
    /* Outport: '<Root>/finishedElectricalID' */
    /* Exit 'waitState': '<S1>:428' */
    /* '<S1>:428:15' finishedElectricalID=boolean(1); */
		rtY->finishedElectricalID = true;

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:428:16' enteredElectricalID=boolean(0); */
		rtY->enteredElectricalID = false;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* '<S1>:428:17' ElectricalID_FOC_output.enableFOC_speed=boolean(0); */
		rtY->ElectricalID_FOC_output.enableFOC_speed = false;

    /* '<S1>:428:18' ElectricalID_FOC_output.resetIntegrator=boolean(0); */
		rtY->ElectricalID_FOC_output.resetIntegrator = false;
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   default:
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void ElectricalID_c(ExtU *rtU, ExtY *rtY, DW *rtDW)
{
  real32_T DutyCycle_filt;
  uint32_T qY;

  /* Inport: '<Root>/GlobalConfig' */
  /* During 'ElectricalID': '<S1>:761' */
  /* '<S1>:901:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.ElectricalID==0; */
	if (rtU->GlobalConfig_out.Reset || (!rtU->GlobalConfig_out.ElectricalID)) {
    /* Outport: '<Root>/enteredElectricalID' */
    /* Transition: '<S1>:901' */
    /* '<S1>:901:2' enteredElectricalID=boolean(0) */
		rtY->enteredElectricalID = false;
		exit_internal_ElectricalID(rtU, rtY, rtDW);
		rtDW->is_c3_ElectricalID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* FrictionID */
    /* donothing */
  } else {
		switch (rtDW->is_ElectricalID) {
		case IN_Levenberg_Marquardt:
      /* Inport: '<Root>/ElectricalIDConfig' */
      /* During 'Levenberg_Marquardt': '<S1>:91' */
      /* '<S1>:426:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 &&.... */
      /* '<S1>:426:2'  ElectricalIDConfig.identLq == 0; */
      /* . */
			if (rtU->GlobalConfig_out.ACCEPT && (!rtU->ElectricalIDConfig_l.identLq)) {
        /* Transition: '<S1>:426' */
        /* Exit 'Levenberg_Marquardt': '<S1>:91' */
				rtDW->is_ElectricalID = IN_calculatePIcontroller;
				enter_atomic_calculatePIcontrol(rtU, rtY, rtDW);

        /* '<S1>:420:1' sf_internal_predicateOutput = (after(1.0,sec)) && (GlobalConfig.ACCEPT == 1 .... */
        /* '<S1>:420:2' && ElectricalIDConfig.identLq == 1); */
        /* . */
			} else if ((rtDW->temporalCounter_i1 >= 10000U) && rtU->GlobalConfig_out.ACCEPT && rtU->ElectricalIDConfig_l.identLq) {
        /* Transition: '<S1>:420' */
        /* Exit 'Levenberg_Marquardt': '<S1>:91' */
				rtDW->is_ElectricalID = IN_stepResponse_q;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stepResponse_q': '<S1>:277' */
        /* '<S1>:277:4' ElectricalID_FOC_output.activeState = uint16(142); */
				rtY->ElectricalID_FOC_output.activeState = 142U;

        /* '<S1>:277:5' resetParams_LM; */
				resetParams_LM(rtDW);

        /* '<S1>:277:6' z = uint16(1); */
				rtDW->z = 1U;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:277:7' ElectricalID_output.outputMode          = [boolean(0),boolean(1),boolean(1)]; */
				rtY->ElectricalID_output_o.outputMode[0] = false;
				rtY->ElectricalID_output_o.outputMode[1] = true;
				rtY->ElectricalID_output_o.outputMode[2] = true;

        /* '<S1>:277:8' ElectricalID_output.PWM_Switch_0 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

        /* '<S1>:277:9' ElectricalID_output.PWM_Switch_1 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_1 = 0.0F;

        /* '<S1>:277:10' counter = uint32(1); */
				rtDW->counter = 1U;
      }
      break;

		case IN_Levenberg_Marquardt_q:
      /* During 'Levenberg_Marquardt_q': '<S1>:278' */
      /* '<S1>:295:1' sf_internal_predicateOutput = after(0.1,sec); */
			if (rtDW->temporalCounter_i1 >= 1000U) {
        /* Transition: '<S1>:295' */
        /* Exit 'Levenberg_Marquardt_q': '<S1>:278' */
				rtDW->is_ElectricalID = IN_calculatePIcontroller;
				enter_atomic_calculatePIcontrol(rtU, rtY, rtDW);
      }
      break;

		case IN_alignRotor_d_off:
      /* During 'alignRotor_d_off': '<S1>:53' */
      /* '<S1>:411:1' sf_internal_predicateOutput = after(1.0, sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Outport: '<Root>/ElectricalID_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         */
        /* Transition: '<S1>:411' */
        /* Exit 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
				rtY->ElectricalID_output_o.thetaOffset = rtU->ActualValues_i.theta_m;
				rtDW->is_ElectricalID = IN_alignRotor_q_on;
				rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_q_on': '<S1>:410' */
        /* '<S1>:410:4' ElectricalID_FOC_output.activeState = uint16(123); */
				rtY->ElectricalID_FOC_output.activeState = 123U;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:410:5' ElectricalID_output.outputMode          = [boolean(0),boolean(1),boolean(1)]; */
				rtY->ElectricalID_output_o.outputMode[0] = false;
				rtY->ElectricalID_output_o.outputMode[1] = true;
				rtY->ElectricalID_output_o.outputMode[2] = true;

        /* '<S1>:410:6' ElectricalID_output.PWM_Switch_0 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

        /* '<S1>:410:7' ElectricalID_output.PWM_Switch_1 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_1 = 0.0F;

        /* '<S1>:410:8' counter = uint32(1); */
				rtDW->counter = 1U;
      }
      break;

		case IN_alignRotor_d_off1:
      /* During 'alignRotor_d_off1': '<S1>:417' */
      /* '<S1>:419:1' sf_internal_predicateOutput = (after(1.0,sec)) && (GlobalConfig.ACCEPT == 1); */
			if ((rtDW->temporalCounter_i1 >= 10000U) && rtU->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:419' */
        /* Exit 'alignRotor_d_off1': '<S1>:417' */
				rtDW->is_ElectricalID = IN_findDutyCycle;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'findDutyCycle': '<S1>:789' */
        /* Motor must be manually locked via load machine until state 60 */
        /* '<S1>:789:4' ElectricalID_FOC_output.activeState = uint16(130); */
				rtY->ElectricalID_FOC_output.activeState = 130U;

        /* Inport: '<Root>/ElectricalIDConfig' */
        /* '<S1>:789:5' if(ElectricalIDConfig.dutyCyc > 0.0) */
				if (rtU->ElectricalIDConfig_l.dutyCyc > 0.0F) {
          /* Checks if a manual value for the DutyCycle was set */
          /* '<S1>:789:6' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
					rtDW->DutyCycle = rtU->ElectricalIDConfig_l.dutyCyc;

          /* '<S1>:789:7' DC_manual = boolean(1); */
					rtDW->DC_manual = true;
        } else {
          /* '<S1>:789:8' else */
          /* '<S1>:789:9' DutyCycle = single(0.005); */
					rtDW->DutyCycle = 0.005F;
        }

        /* '<S1>:789:11' counter = uint32(1); */
				rtDW->counter = 1U;

        /* starts with 1, so that the DutyCylce_mod function wont be entered */
        /* during the fist cycle through the state */
      }
      break;

		case IN_alignRotor_d_off2:
      /* During 'alignRotor_d_off2': '<S1>:848' */
      /* '<S1>:849:1' sf_internal_predicateOutput = after(1.0,sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Transition: '<S1>:849' */
        /* Exit 'alignRotor_d_off2': '<S1>:848' */
				rtDW->is_ElectricalID = IN_stepResponse;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stepResponse': '<S1>:5' */
        /* state 2.0 */
        /* '<S1>:5:3' ElectricalID_FOC_output.activeState = uint16(140); */
				rtY->ElectricalID_FOC_output.activeState = 140U;

        /* '<S1>:5:4' counter = uint32(1); */
				rtDW->counter = 1U;

        /* '<S1>:5:5' z = uint16(1); */
				rtDW->z = 1U;
      }
      break;

		case IN_alignRotor_d_on:
      /* During 'alignRotor_d_on': '<S1>:3' */
      /* '<S1>:164:1' sf_internal_predicateOutput = after(1.0,sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:164' */
        /* Exit 'alignRotor_d_on': '<S1>:3' */
        /* '<S1>:3:16' ElectricalID_output.PWM_Switch_0 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;
				rtDW->is_ElectricalID = IN_alignRotor_d_off;
				rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:4' ElectricalID_FOC_output.activeState = uint16(121); */
				rtY->ElectricalID_FOC_output.activeState = 121U;
      } else {
        /* '<S1>:3:7' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
				DutyCycle_filt = (real32_T) rtDW->counter * rtU->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S1>:3:8' if(DutyCycle_filt > 1) */
        if (DutyCycle_filt > 1.0F) {
          /* '<S1>:3:9' DutyCycle_filt = single(1.0); */
          DutyCycle_filt = 1.0F;
        }

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:3:11' ElectricalID_output.PWM_Switch_0 = single(DutyCycle*DutyCycle_filt); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = rtDW->DutyCycle * DutyCycle_filt;

        /* '<S1>:3:12' ElectricalID_output.PWM_Switch_2 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;

        /* '<S1>:3:13' ElectricalID_output.PWM_Switch_4 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;

        /* '<S1>:3:14' counter  = counter +1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;
      }
      break;

		case IN_alignRotor_d_on1:
      /* During 'alignRotor_d_on1': '<S1>:415' */
      /* '<S1>:418:1' sf_internal_predicateOutput = after(1.0,sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:418' */
        /* Exit 'alignRotor_d_on1': '<S1>:415' */
        /* '<S1>:415:15' ElectricalID_output.PWM_Switch_0 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

        /* '<S1>:415:16' DutyCycle=single(0.0); */
				rtDW->DutyCycle = 0.0F;

        /* resets the DC and DC_manual flag, so that for the step-response */
        /* '<S1>:415:17' DC_manual=boolean(0); */
				rtDW->DC_manual = false;

        /* a new DC can be entered */
				rtDW->is_ElectricalID = IN_alignRotor_d_off1;
				rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_d_off1': '<S1>:417' */
        /* '<S1>:417:4' ElectricalID_FOC_output.activeState = uint16(126); */
				rtY->ElectricalID_FOC_output.activeState = 126U;
      } else {
        /* '<S1>:415:8' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
				DutyCycle_filt = (real32_T) rtDW->counter * rtU->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S1>:415:9' if(DutyCycle_filt > 1) */
        if (DutyCycle_filt > 1.0F) {
          /* '<S1>:415:10' DutyCycle_filt = single(1.0); */
          DutyCycle_filt = 1.0F;
        }

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:415:12' ElectricalID_output.PWM_Switch_0 = single(DutyCycle*DutyCycle_filt); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = rtDW->DutyCycle * DutyCycle_filt;

        /* '<S1>:415:13' counter = counter + 1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;
      }
      break;

		case IN_alignRotor_q_off:
      /* During 'alignRotor_q_off': '<S1>:412' */
      /* '<S1>:55:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1; */
			if (rtU->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:55' */
				rtDW->is_ElectricalID = IN_alignRotor_d_on1;
				rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_d_on1': '<S1>:415' */
        /* '<S1>:415:4' ElectricalID_FOC_output.activeState = uint16(125); */
				rtY->ElectricalID_FOC_output.activeState = 125U;

        /* '<S1>:415:5' counter = uint32(1); */
				rtDW->counter = 1U;

        /* '<S1>:415:6' DutyCycle_filt = single(0.0); */
      }
      break;

		case IN_alignRotor_q_on:
      /* During 'alignRotor_q_on': '<S1>:410' */
      /* '<S1>:413:1' sf_internal_predicateOutput = after(1.0,sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:413' */
        /* Exit 'alignRotor_q_on': '<S1>:410' */
        /* '<S1>:410:17' ElectricalID_output.PWM_Switch_2 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;
				rtDW->is_ElectricalID = IN_alignRotor_q_off;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_q_off': '<S1>:412' */
        /* '<S1>:412:4' ElectricalID_FOC_output.activeState = uint16(124); */
				rtY->ElectricalID_FOC_output.activeState = 124U;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:412:5' ElectricalID_output.outputMode          = [boolean(1),boolean(1),boolean(1)]; */
				rtY->ElectricalID_output_o.outputMode[0] = true;
				rtY->ElectricalID_output_o.outputMode[1] = true;
				rtY->ElectricalID_output_o.outputMode[2] = true;

        /* Inport: '<Root>/ActualValues' */
        /* '<S1>:412:6' ElectricalID_output.p = uint16(round((pi/2.0) / (abs(ActualValues.theta_m)))); */
				DutyCycle_filt = roundf(1.57079637F / fabsf(rtU->ActualValues_i.theta_m));
        if (DutyCycle_filt < 65536.0F) {
          /* Outport: '<Root>/ElectricalID_output' */
					rtY->ElectricalID_output_o.p = (uint16_T) DutyCycle_filt;
        } else {
          /* Outport: '<Root>/ElectricalID_output' */
					rtY->ElectricalID_output_o.p = MAX_uint16_T;
        }
      } else {
        /* '<S1>:410:10' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
				DutyCycle_filt = (real32_T) rtDW->counter * rtU->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S1>:410:11' if(DutyCycle_filt > 1) */
        if (DutyCycle_filt > 1.0F) {
          /* '<S1>:410:12' DutyCycle_filt = single(1.0); */
          DutyCycle_filt = 1.0F;
        }

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:410:14' ElectricalID_output.PWM_Switch_2 = single(1.5*DutyCycle*DutyCycle_filt); */
				rtY->ElectricalID_output_o.PWM_Switch_2 = 1.5F * rtDW->DutyCycle * DutyCycle_filt;

        /* '<S1>:410:15' counter = counter + 1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;
      }
      break;

		case IN_calculatePIcontroller:
      /* During 'calculatePIcontroller': '<S1>:284' */
      /* '<S1>:408:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1; */
			if (rtU->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:408' */
				rtDW->is_ElectricalID = IN_measure_psiPM;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Inport: '<Root>/ElectricalIDConfig'
         */
        /* Entry 'measure_psiPM': '<S1>:405' */
        /* '<S1>:405:4' ElectricalID_FOC_output.activeState = uint16(150); */
				rtY->ElectricalID_FOC_output.activeState = 150U;

        /* '<S1>:405:5' ElectricalID_FOC_output.enableFOC_speed = boolean(1); */
				rtY->ElectricalID_FOC_output.enableFOC_speed = true;

        /* '<S1>:405:6' ElectricalID_FOC_output.n_ref_FOC = ElectricalIDConfig.n_ref_measurement; */
				rtY->ElectricalID_FOC_output.n_ref_FOC = rtU->ElectricalIDConfig_l.n_ref_measurement;

        /* '<S1>:405:7' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
				DutyCycle_filt = roundf(3.0F / rtU->GlobalConfig_out.sampleTimeISR);
        if (DutyCycle_filt < 4.2949673E+9F) {
          if (DutyCycle_filt >= 0.0F) {
						rtDW->wait_count = (uint32_T) DutyCycle_filt;
          } else {
						rtDW->wait_count = 0U;
          }
        } else {
					rtDW->wait_count = MAX_uint32_T;
        }
      }
      break;

		case IN_endState:
      /* During 'endState': '<S1>:356' */
      /* '<S1>:425:1' sf_internal_predicateOutput = after(1,sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Transition: '<S1>:425' */
				rtDW->is_ElectricalID = IN_waitState;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'waitState': '<S1>:428' */
        /* do nothing */
        /* '<S1>:428:3' ElectricalID_FOC_output.activeState = uint16(170); */
				rtY->ElectricalID_FOC_output.activeState = 170U;

        /* Outport: '<Root>/ElectricalID_output' */
        /*  recalculate speed controller using psiPM and J */
        /* '<S1>:428:5' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.L_q*dampingFactor*GlobalConfig.polePairs.... */
        /* '<S1>:428:6'     *3.0/2.0*ElectricalID_output.psiPM/ElectricalID_output.rotorInertia); */
				rtDW->Kp_n_loc = rtDW->Kp_iq_loc
				                / (rtY->ElectricalID_output_o.L_q * rtDW->dampingFactor * rtU->GlobalConfig_out.polePairs * 3.0F / 2.0F * rtY->ElectricalID_output_o.psiPM
				                                / rtY->ElectricalID_output_o.rotorInertia);

        /* . */
        /* Ki_n_loc = (dampingFactor*dampingFactor*ElectricalID_output.L_q)/Kp_iq_loc; */
        /* '<S1>:428:8' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.L_q * ElectricalID_output.L_q * .... */
        /* '<S1>:428:9'     dampingFactor * dampingFactor * dampingFactor * GlobalConfig.polePairs*3.0/2.0*.... */
        /* '<S1>:428:10'     ElectricalID_output.psiPM/ElectricalID_output.rotorInertia); */
				rtDW->Ki_n_loc = rtDW->Kp_iq_loc * rtDW->Kp_iq_loc
				                / (rtY->ElectricalID_output_o.L_q * rtY->ElectricalID_output_o.L_q * rtDW->dampingFactor * rtDW->dampingFactor * rtDW->dampingFactor
				                                * rtU->GlobalConfig_out.polePairs * 3.0F / 2.0F * rtY->ElectricalID_output_o.psiPM / rtY->ElectricalID_output_o.rotorInertia);

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* . */
        /* . */
        /* '<S1>:428:11' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
				rtY->ElectricalID_FOC_output.Kp_n_out = rtDW->Kp_n_loc;

        /* '<S1>:428:12' ElectricalID_FOC_output.Ki_n_out = Ki_n_loc; */
				rtY->ElectricalID_FOC_output.Ki_n_out = rtDW->Ki_n_loc;
      }
      break;

		case IN_evaluate_Turn_DC:
			evaluate_Turn_DC(rtU, rtY, rtDW);
      break;

		case IN_findDutyCycle:
			findDutyCycle(rtU, rtY, rtDW);
      break;

		case IN_measure_psiPM:
			measure_psiPM(rtU, rtY, rtDW);
      break;

		case IN_rotorInertiaEstimation:
      /* During 'rotorInertiaEstimation': '<S1>:337' */
      /* '<S1>:357:1' sf_internal_predicateOutput = counter == (wait_count+513); */
			qY = rtDW->wait_count + /*MW:OvSatOk*/513U;
			if (rtDW->wait_count + 513U < rtDW->wait_count) {
        qY = MAX_uint32_T;
      }

			if (rtDW->counter == qY) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:357' */
        /* Exit 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:21' ElectricalID_output.TrainInertia = goertzel; */
				rtY->ElectricalID_output_o.TrainInertia = goertzel(rtU, rtY, rtDW);
				rtDW->is_ElectricalID = IN_endState;
				rtDW->temporalCounter_i1 = 0U;

        /* Entry 'endState': '<S1>:356' */
        /* '<S1>:356:4' counter = uint32(1); */
				rtDW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:356:5' ElectricalID_FOC_output.activeState = uint16(161); */
				rtY->ElectricalID_FOC_output.activeState = 161U;

        /* '<S1>:356:6' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
				rtY->ElectricalID_FOC_output.Kp_n_out = rtDW->Kp_n_loc;

        /* '<S1>:356:7' ElectricalID_FOC_output.Ki_n_out = single(Ki_n_loc); */
				rtY->ElectricalID_FOC_output.Ki_n_out = rtDW->Ki_n_loc;

        /* '<S1>:356:8' ElectricalID_FOC_output.VibOn_out=boolean(0); */
				rtY->ElectricalID_FOC_output.VibOn_out = false;

        /* '<S1>:356:9' ElectricalID_FOC_output.VibAmp_out = single(0); */
				rtY->ElectricalID_FOC_output.VibAmp_out = 0.0F;

        /* '<S1>:356:10' ElectricalID_FOC_output.VibFreq_out = uint16(0); */
				rtY->ElectricalID_FOC_output.VibFreq_out = 0U;

        /* '<S1>:356:11' ElectricalID_FOC_output.resetIntegrator=boolean(1); */
				rtY->ElectricalID_FOC_output.resetIntegrator = true;
      } else {
        /* '<S1>:337:15' if(counter > wait_count && counter < (wait_count+501)) */
				qY = rtDW->wait_count + /*MW:OvSatOk*/501U;
				if (rtDW->wait_count + 501U < rtDW->wait_count) {
          qY = MAX_uint32_T;
        }

				if ((rtDW->counter > rtDW->wait_count) && (rtDW->counter < qY)) {
          /* '<S1>:337:16' measArray1(counter-wait_count) = ActualValues.i_q; */
					qY = rtDW->counter - /*MW:OvSatOk*/rtDW->wait_count;
					if (qY > rtDW->counter) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
					rtDW->measArray1[(int32_T) qY - 1] = rtU->ActualValues_i.i_q;

          /* '<S1>:337:17' i_est(counter-wait_count) = ActualValues.omega_m; */
					qY = rtDW->counter - /*MW:OvSatOk*/rtDW->wait_count;
					if (qY > rtDW->counter) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
					rtDW->i_est[(int32_T) qY - 1] = rtU->ActualValues_i.omega_m;
        }

        /* '<S1>:337:19' counter = counter + 1; */
				qY = rtDW->counter + /*MW:OvSatOk*/1U;
				if (rtDW->counter + 1U < rtDW->counter) {
          qY = MAX_uint32_T;
        }

				rtDW->counter = qY;
      }
      break;

		case IN_stepResponse:
			stepResponse(rtU, rtY, rtDW);
      break;

		case IN_stepResponse_q:
			stepResponse_q(rtU, rtY, rtDW);
      break;

		case IN_stop:
      /* During 'stop': '<S1>:361' */
      /* '<S1>:362:1' sf_internal_predicateOutput = after(1.0,sec); */
			if (rtDW->temporalCounter_i1 >= 10000U) {
        /* Transition: '<S1>:362' */
				rtDW->is_ElectricalID = IN_rotorInertiaEstimation;

        /* Entry 'rotorInertiaEstimation': '<S1>:337' */
        /* state 11 */
        /* '<S1>:337:3' counter = uint32(1); */
				rtDW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:337:4' ElectricalID_FOC_output.activeState = uint16(160); */
				rtY->ElectricalID_FOC_output.activeState = 160U;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:337:5' ElectricalID_output.PWM_Switch_0 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;

        /* '<S1>:337:6' ElectricalID_output.PWM_Switch_2 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;

        /* '<S1>:337:7' ElectricalID_output.PWM_Switch_4 = single(0); */
				rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Inport: '<Root>/ElectricalIDConfig'
         */
        /* '<S1>:337:8' ElectricalID_FOC_output.Kp_n_out=single(0.0); */
				rtY->ElectricalID_FOC_output.Kp_n_out = 0.0F;

        /* '<S1>:337:9' ElectricalID_FOC_output.Ki_n_out=single(0.0); */
				rtY->ElectricalID_FOC_output.Ki_n_out = 0.0F;

        /* '<S1>:337:10' ElectricalID_FOC_output.VibOn_out=boolean(1); */
				rtY->ElectricalID_FOC_output.VibOn_out = true;

        /* '<S1>:337:11' ElectricalID_FOC_output.VibAmp_out = single(ElectricalIDConfig.goertzlAmp); */
				rtY->ElectricalID_FOC_output.VibAmp_out = rtU->ElectricalIDConfig_l.goertzlAmp;

        /* '<S1>:337:12' ElectricalID_FOC_output.VibFreq_out = uint16(40); */
				rtY->ElectricalID_FOC_output.VibFreq_out = 40U;

        /* '<S1>:337:13' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
				DutyCycle_filt = roundf(3.0F / rtU->GlobalConfig_out.sampleTimeISR);
        if (DutyCycle_filt < 4.2949673E+9F) {
          if (DutyCycle_filt >= 0.0F) {
						rtDW->wait_count = (uint32_T) DutyCycle_filt;
          } else {
						rtDW->wait_count = 0U;
          }
        } else {
					rtDW->wait_count = MAX_uint32_T;
        }
      }
      break;

     default:
      /* Outport: '<Root>/finishedElectricalID' */
      /* During 'waitState': '<S1>:428' */
      /* Transition: '<S1>:905' */
      /* Exit 'waitState': '<S1>:428' */
      /* '<S1>:428:15' finishedElectricalID=boolean(1); */
			rtY->finishedElectricalID = true;

      /* Outport: '<Root>/enteredElectricalID' */
      /* '<S1>:428:16' enteredElectricalID=boolean(0); */
			rtY->enteredElectricalID = false;

      /* Outport: '<Root>/ElectricalID_FOC_output' */
      /* '<S1>:428:17' ElectricalID_FOC_output.enableFOC_speed=boolean(0); */
			rtY->ElectricalID_FOC_output.enableFOC_speed = false;

      /* '<S1>:428:18' ElectricalID_FOC_output.resetIntegrator=boolean(0); */
			rtY->ElectricalID_FOC_output.resetIntegrator = false;
			rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
			rtDW->is_c3_ElectricalID = IN_Waiting;

      /* Entry 'Waiting': '<S1>:902' */
      /* wait for activation of */
      /* FrictionID */
      /* donothing */
      break;
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
}

/* Model step function */
void ElectricalID_step(RT_MODEL * const rtM)
{
	DW *rtDW = rtM->dwork;
	ExtU *rtU = (ExtU *) rtM->inputs;
	ExtY *rtY = (ExtY *) rtM->outputs;

  /* Chart: '<Root>/ElectricalID' incorporates:
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/ElectricalIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
	if (rtDW->temporalCounter_i1 < 16383U) {
		rtDW->temporalCounter_i1++;
  }

  /* Gateway: ElectricalID */
  /* During: ElectricalID */
	if (rtDW->is_active_c3_ElectricalID == 0U) {
    /* Entry: ElectricalID */
		rtDW->is_active_c3_ElectricalID = 1U;

    /* Entry Internal: ElectricalID */
    /* Transition: '<S1>:897' */
		rtDW->is_c3_ElectricalID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* FrictionID */
    /* donothing */
	} else if (rtDW->is_c3_ElectricalID == IN_ElectricalID) {
		ElectricalID_c(rtU, rtY, rtDW);

    /* During 'Waiting': '<S1>:902' */
    /* '<S1>:899:1' sf_internal_predicateOutput = ControlFlags.startElectricalID==1 &&.... */
    /* '<S1>:899:2'  GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
	} else if (rtU->ControlFlags_o.startElectricalID && (!rtU->GlobalConfig_out.Reset) && rtU->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:899' */
		rtDW->is_c3_ElectricalID = IN_ElectricalID;

    /* Entry 'ElectricalID': '<S1>:761' */
    /* '<S1>:761:3' ElectricalID_FOC_output.activeState = uint16(100); */
    /* '<S1>:761:4' initParams; */
		initParams(rtY, rtDW);

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:761:5' enteredElectricalID=boolean(1); */
		rtY->enteredElectricalID = true;

    /* Entry Internal 'ElectricalID': '<S1>:761' */
    /* Transition: '<S1>:243' */
		rtDW->is_ElectricalID = IN_evaluate_Turn_DC;

    /* Entry 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:3' ElectricalID_FOC_output.activeState = uint16(110); */
		rtY->ElectricalID_FOC_output.activeState = 110U;

    /* '<S1>:379:4' counter = uint32(1); */
		rtDW->counter = 1U;

    /* '<S1>:379:5' omega_register=single(zeros(5,1)); */
		for (rtDW->i = 0; rtDW->i < 5; rtDW->i++) {
			rtDW->omega_register[rtDW->i] = 0.0F;
    }

    /* '<S1>:379:6' if(ElectricalIDConfig.dutyCyc > 0.0) */
		if (rtU->ElectricalIDConfig_l.dutyCyc > 0.0F) {
      /* Checks if a manual value for the DutyCycle was set */
      /* '<S1>:379:7' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
			rtDW->DutyCycle = rtU->ElectricalIDConfig_l.dutyCyc;

      /* '<S1>:379:8' DC_manual = boolean(1); */
			rtDW->DC_manual = true;
    } else {
      /* '<S1>:379:9' else */
      /* '<S1>:379:10' DutyCycle = single(0.01); */
			rtDW->DutyCycle = 0.01F;
    }

    /* '<S1>:914:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
	} else if (rtU->GlobalConfig_out.Reset) {
    /* Outport: '<Root>/finishedElectricalID' */
    /* Transition: '<S1>:914' */
    /* '<S1>:914:2' finishedElectricalID=boolean(0); */
		rtY->finishedElectricalID = false;

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:914:3' enteredElectricalID=boolean(0); */
		rtY->enteredElectricalID = false;
		rtDW->is_c3_ElectricalID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* FrictionID */
    /* donothing */
  }

  /* End of Chart: '<Root>/ElectricalID' */
}

/* Model initialize function */
void ElectricalID_initialize(RT_MODEL * const rtM)
{
	DW *rtDW = rtM->dwork;
	ExtY *rtY = (ExtY *) rtM->outputs;
	ExtU *rtU = (ExtU *) rtM->inputs;

	/* Registration code */

	/* states (dwork) */
	(void) memset((void *) rtDW, 0, sizeof(DW));

	/* external inputs */
	(void) memset(rtU, 0, sizeof(ExtU));

	/* external outputs */
	(void) memset((void *) rtY, 0, sizeof(ExtY));

	{
		int32_T i;

		/* SystemInitialize for Chart: '<Root>/ElectricalID' */
		rtDW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
		rtDW->temporalCounter_i1 = 0U;
		rtDW->is_active_c3_ElectricalID = 0U;
		rtDW->is_c3_ElectricalID = IN_NO_ACTIVE_CHILD;
		rtDW->counter = 0U;
		rtDW->e = 0.0F;
		rtDW->H[0] = 0.0F;
		rtDW->H[1] = 0.0F;
		rtDW->H[2] = 0.0F;
		rtDW->H[3] = 0.0F;
		rtDW->n_iters = 0U;
		rtDW->lambda = 0.0F;
		rtDW->updateJ = false;
		rtDW->U0 = 0.0F;
		rtDW->z = 0U;
		rtDW->R_corr = 0.0F;
		rtDW->bandwidthCurrentControl = 0.0F;
		rtDW->dampingFactor = 0.0F;
		rtDW->psiOverJ = 0.0F;
		rtDW->Kp_n_loc = 0.0F;
		rtDW->Ki_n_loc = 0.0F;
		rtDW->Kp_iq_loc = 0.0F;
		for (i = 0; i < 5; i++) {
			rtDW->omega_register[i] = 0.0F;
		}

		rtDW->omega_sum = 0.0F;
		rtDW->om_con = false;
		rtDW->ia_valid = false;
		rtDW->ia_sum = 0.0F;
		rtDW->DC_manual = false;
		memset(&rtDW->d[0], 0, sizeof(real32_T) << 11U);
		memset(&rtDW->i_est[0], 0, sizeof(real32_T) << 11U);
		memset(&rtDW->J[0], 0, sizeof(real32_T) << 12U);
		memset(&rtDW->Ustep[0], 0, 205U * sizeof(real32_T));
		rtDW->DutyCycle = 0.0F;
		rtDW->wait_count = 0U;
		memset(&rtDW->measArray1[0], 0, sizeof(real32_T) << 10U);

		/* SystemInitialize for Outport: '<Root>/enteredElectricalID' incorporates:
		 *  Chart: '<Root>/ElectricalID'
		 */
		rtY->enteredElectricalID = false;

		/* SystemInitialize for Outport: '<Root>/finishedElectricalID' incorporates:
		 *  Chart: '<Root>/ElectricalID'
		 */
		rtY->finishedElectricalID = false;

		/* SystemInitialize for Chart: '<Root>/ElectricalID' incorporates:
		 *  Outport: '<Root>/ElectricalID_FOC_output'
		 *  Outport: '<Root>/ElectricalID_output'
		 */
		rtY->ElectricalID_FOC_output.activeState = 0U;
		rtY->ElectricalID_FOC_output.n_ref_FOC = 0.0F;
		rtY->ElectricalID_FOC_output.i_d_ref_out = 0.0F;
		rtY->ElectricalID_FOC_output.i_q_ref_out = 0.0F;
		rtY->ElectricalID_FOC_output.enableFOC_speed = false;
		rtY->ElectricalID_FOC_output.enableFOC_current = false;
		rtY->ElectricalID_FOC_output.VibOn_out = false;
		rtY->ElectricalID_FOC_output.VibAmp_out = 0.0F;
		rtY->ElectricalID_FOC_output.VibFreq_out = 0U;
		rtY->ElectricalID_FOC_output.resetIntegrator = false;
		rtY->ElectricalID_FOC_output.PRBS_out = 0.0F;
		rtY->ElectricalID_FOC_output.Kp_id_out = 0.0F;
		rtY->ElectricalID_FOC_output.Kp_iq_out = 0.0F;
		rtY->ElectricalID_FOC_output.Kp_n_out = 0.0F;
		rtY->ElectricalID_FOC_output.Ki_id_out = 0.0F;
		rtY->ElectricalID_FOC_output.Ki_iq_out = 0.0F;
		rtY->ElectricalID_FOC_output.Ki_n_out = 0.0F;
		rtY->ElectricalID_output_o.PWM_Switch_0 = 0.0F;
		rtY->ElectricalID_output_o.PWM_Switch_1 = 0.0F;
		rtY->ElectricalID_output_o.PWM_Switch_2 = 0.0F;
		rtY->ElectricalID_output_o.PWM_Switch_3 = 0.0F;
		rtY->ElectricalID_output_o.PWM_Switch_4 = 0.0F;
		rtY->ElectricalID_output_o.PWM_Switch_5 = 0.0F;
		rtY->ElectricalID_output_o.outputMode[0] = false;
		rtY->ElectricalID_output_o.outputMode[1] = false;
		rtY->ElectricalID_output_o.outputMode[2] = false;
		rtY->ElectricalID_output_o.R_s = 0.0F;
		rtY->ElectricalID_output_o.L_d = 0.0F;
		rtY->ElectricalID_output_o.L_q = 0.0F;
		rtY->ElectricalID_output_o.psiPM = 0.0F;
		rtY->ElectricalID_output_o.rotorInertia = 0.0F;
		rtY->ElectricalID_output_o.thetaOffset = 0.0F;
		rtY->ElectricalID_output_o.p = 0U;
		rtY->ElectricalID_output_o.TrainInertia = 0.0F;
	}
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif