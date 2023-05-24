/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID.c
 *
 * Code generated for Simulink model 'ElectricalID'.
 *
 * Model version                  : 2.651
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jul  5 15:55:57 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "ElectricalID_codegen.h"
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U

/* Named constants for Chart: '<Root>/ElectricalID' */
#define IN_ElectricalID                ((uint8_T)1U)
#define IN_Levenberg_Marquardt         ((uint8_T)1U)
#define IN_Levenberg_Marquardt_q       ((uint8_T)2U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Waiting                     ((uint8_T)2U)
#define IN_alignRotor_d_off            ((uint8_T)3U)
#define IN_alignRotor_d_off2           ((uint8_T)4U)
#define IN_alignRotor_d_on             ((uint8_T)5U)
#define IN_calculatePIcontroller       ((uint8_T)6U)
#define IN_endState                    ((uint8_T)7U)
#define IN_evaluate_Turn_DC            ((uint8_T)8U)
#define IN_findDutyCycle               ((uint8_T)9U)
#define IN_measure_psiPM               ((uint8_T)10U)
#define IN_rotorInertiaEstimation      ((uint8_T)11U)
#define IN_stepResponse                ((uint8_T)12U)
#define IN_stepResponse_q              ((uint8_T)13U)
#define IN_stop                        ((uint8_T)14U)
#define IN_waitState                   ((uint8_T)15U)

extern real32_T rt_hypotf(real32_T u0, real32_T u1);

/* Forward declaration for local functions */
static void initParams(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static void reset_FOC_output(ExtY_ElectricalID_t *rtElectricalID_Y);
static void resetParams_LM(DW_ElectricalID_t *rtElectricalID_DW);
static void enter_atomic_calculatePIcontrol(ExtU_ElectricalID_t
  *rtElectricalID_U, ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t
  *rtElectricalID_DW);
static void RefreshDataRegister(DW_ElectricalID_t *rtElectricalID_DW);
static void DutyCycle_mod(const real32_T om_reg_in[5], ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW);
static void TurnMotor(ExtU_ElectricalID_t *rtElectricalID_U, ExtY_ElectricalID_t
                      *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static void DutyCycle_mod_a(real32_T ia_reg_in, ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW);
static void measure_psiPM(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID_t *rtElectricalID_DW);
static void goertzel(ExtU_ElectricalID_t *rtElectricalID_U, ExtY_ElectricalID_t *
                     rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static void inv(const real32_T x[4], real32_T y[4]);
static void mtimes(const real32_T A[2048], const real32_T B[1024], real32_T C[2]);
static void LM_algorithm(real32_T *L_est, real32_T *R_est, ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW);
static void stepResponse(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static void LM_algorithm_Lq(real32_T *L_est, ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW);
static void stepResponse_q(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static void exit_internal_ElectricalID(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);
static void ElectricalID_p(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW);

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function initParams
 * This is used instead of "after(1.0,sec) to ensure the same transition time
 * independelty of the sampletime in the c-code
 */
static void initParams(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  real32_T tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'initParams': '<S1>:88' */
  /* '<S1>:88:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F / rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtElectricalID_DW->one_sec_transition_counter = (uint32_T)tmp;
    } else {
      rtElectricalID_DW->one_sec_transition_counter = 0U;
    }
  } else {
    rtElectricalID_DW->one_sec_transition_counter = MAX_uint32_T;
  }

  /*  initialize variables */
  /* '<S1>:88:7' Ki_n_loc            = single(0.0); */
  /* '<S1>:88:8' Kp_n_loc            = single(0.0); */
  /* '<S1>:88:9' n_filt              = single(0.0); */
  /* '<S1>:88:10' n_ref_old           = single(0.0); */
  /* '<S1>:88:11' repetitionCounter   = uint32(0); */
  /* '<S1>:88:12' dutyCycAdj          = single(0.0); */
  /* '<S1>:88:13' counter 			= uint32(1); */
  rtElectricalID_DW->counter = 1U;

  /* '<S1>:88:14' Kp_iq_loc           = single(0.0); */
  rtElectricalID_DW->Kp_iq_loc = 0.0F;

  /* '<S1>:88:15' Ki_iq_loc           = single(0.0); */
  /* '<S1>:88:16' Kp_id_loc           = single(0.0); */
  /* '<S1>:88:17' Ki_id_loc           = single(0.0); */
  /* '<S1>:88:18' DutyCycle_filt      = single(0.0); */
  /* '<S1>:88:19' measArray1			= single(zeros(1024,1)); */
  memset(&rtElectricalID_DW->measArray1[0], 0, sizeof(real32_T) << 10U);

  /* '<S1>:88:20' meas_sum            = single(zeros(2,1)); */
  /* used for Friction Id */
  /* '<S1>:88:21' J2                  = single(zeros(256,5)); */
  /* '<S1>:88:22' thetaOffset         = single(0.0); */
  /* '<S1>:88:23' Vstep               = single(zeros(205,1)); */
  memset(&rtElectricalID_DW->Vstep[0], 0, 205U * sizeof(real32_T));

  /* '<S1>:88:24' DutyCycle           = single(0.0); */
  rtElectricalID_DW->DutyCycle = 0.0F;

  /* '<S1>:88:25' omega_sum           = single(0); */
  rtElectricalID_DW->omega_sum = 0.0F;

  /* '<S1>:88:26' om_con              = boolean(0); */
  rtElectricalID_DW->om_con = false;

  /* '<S1>:88:27' ia_sum              = single(0); */
  rtElectricalID_DW->ia_sum = 0.0F;

  /* '<S1>:88:28' ia_valid            = boolean(0); */
  rtElectricalID_DW->ia_valid = false;

  /* '<S1>:88:29' DC_manual           = boolean(0); */
  rtElectricalID_DW->DC_manual = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Outputs */
  /* '<S1>:88:32' ElectricalID_FOC_output.Ki_n_out                    = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_n_out = 0.0F;

  /* '<S1>:88:33' ElectricalID_FOC_output.Ki_iq_out                   = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_iq_out = 0.0F;

  /* '<S1>:88:34' ElectricalID_FOC_output.Ki_id_out                   = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_id_out = 0.0F;

  /* '<S1>:88:35' ElectricalID_FOC_output.Kp_n_out                    = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_n_out = 0.0F;

  /* '<S1>:88:36' ElectricalID_FOC_output.Kp_iq_out                   = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_iq_out = 0.0F;

  /* '<S1>:88:37' ElectricalID_FOC_output.Kp_id_out                   = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_id_out = 0.0F;

  /* '<S1>:88:38' ElectricalID_FOC_output.n_ref_FOC                   = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:88:39' ElectricalID_FOC_output.M_ref_FOC                   = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.M_ref_FOC = 0.0F;

  /* '<S1>:88:40' ElectricalID_FOC_output.i_dq_ref.d                  = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:88:41' ElectricalID_FOC_output.i_dq_ref.q                  = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:88:42' ElectricalID_FOC_output.i_dq_ref.zero               = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:88:43' ElectricalID_FOC_output.enableFOC_speed             = boolean(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S1>:88:44' ElectricalID_FOC_output.enableFOC_current           = boolean(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_current = false;

  /* '<S1>:88:45' ElectricalID_FOC_output.resetIntegrator             = boolean(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.resetIntegrator = false;

  /* Outport: '<Root>/finishedElectricalID' */
  /* '<S1>:88:46' ElectricalID_FOC_output.activeState                 = uint16(0); */
  /* '<S1>:88:47' finishedElectricalID= boolean(0); */
  rtElectricalID_Y->finishedElectricalID = false;

  /* Outport: '<Root>/ElectricalID_output' */
  /* '<S1>:88:49' ElectricalID_output.PWM_Switch_0                        = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;

  /* '<S1>:88:50' ElectricalID_output.PWM_Switch_2                        = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_2 = 0.0F;

  /* '<S1>:88:51' ElectricalID_output.PWM_Switch_4                        = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = 0.0F;

  /* '<S1>:88:52' ElectricalID_output.enable_TriState                     = boolean(zeros(1,3)); */
  rtElectricalID_Y->ElectricalID_output.enable_TriState[0] = false;
  rtElectricalID_Y->ElectricalID_output.enable_TriState[1] = false;
  rtElectricalID_Y->ElectricalID_output.enable_TriState[2] = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* 0 = TriState off, 1 = TriState on    */
  /* '<S1>:88:53' ElectricalID_FOC_output.activeState                     = uint16(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.activeState = 0U;

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S1>:88:54' ElectricalID_output.thetaOffset                         = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.thetaOffset = 0.0F;

  /* '<S1>:88:55' ElectricalID_output.PMSM_parameters.R_ph_Ohm            = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm = 0.0F;

  /* '<S1>:88:56' ElectricalID_output.PMSM_parameters.Ld_Henry            = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Ld_Henry = 0.0F;

  /* '<S1>:88:57' ElectricalID_output.PMSM_parameters.Lq_Henry            = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry = 0.0F;

  /* '<S1>:88:58' ElectricalID_output.PMSM_parameters.Psi_PM_Vs           = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs = 0.0F;

  /* '<S1>:88:59' ElectricalID_output.PMSM_parameters.polePairs           = GlobalConfig.PMSM_config.polePairs; */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.polePairs =
    rtElectricalID_U->GlobalConfig_out.PMSM_config.polePairs;

  /* '<S1>:88:60' ElectricalID_output.PMSM_parameters.J_kg_m_squared      = single(0.0); */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared = 0.0F;

  /* Outport: '<Root>/enteredElectricalID' */
  /* '<S1>:88:61' enteredElectricalID                                     = boolean(0); */
  rtElectricalID_Y->enteredElectricalID = false;

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S1>:88:64' d        			= single(zeros(2048,1)); */
  /* '<S1>:88:65' dp      			= single(zeros(2,1)); */
  /* '<S1>:88:66' e       			= single(0); */
  rtElectricalID_DW->e = 0.0F;

  /* '<S1>:88:67' e_lm  				= single(0); */
  /* '<S1>:88:68' H 					= single(zeros(2,2)); */
  rtElectricalID_DW->H[0] = 0.0F;
  rtElectricalID_DW->H[1] = 0.0F;
  rtElectricalID_DW->H[2] = 0.0F;
  rtElectricalID_DW->H[3] = 0.0F;

  /* '<S1>:88:69' i_est 				= single(zeros(2048,1)); */
  memset(&rtElectricalID_DW->d[0], 0, sizeof(real32_T) << 11U);
  memset(&rtElectricalID_DW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S1>:88:70' it 					= uint16(0); */
  /* '<S1>:88:71' J 					= single(zeros(2048,2)); */
  memset(&rtElectricalID_DW->J[0], 0, sizeof(real32_T) << 12U);

  /* '<S1>:88:72' k 					= single(0); */
  /* '<S1>:88:73' L0 					= single(0); */
  /* '<S1>:88:74' L_est   			= single(0); */
  /* '<S1>:88:75' L_lm 				= single(0); */
  /* '<S1>:88:76' Ndata  				= uint16(512); */
  /* '<S1>:88:77' Nparams 			= uint16(2); */
  /* '<S1>:88:78' n_iters 			= uint16(100); */
  rtElectricalID_DW->n_iters = 100U;

  /* '<S1>:88:79' R0 					= single(0); */
  /* '<S1>:88:80' R_est 				= single(0); */
  /* '<S1>:88:81' R_lm 				= single(0); */
  /* '<S1>:88:82' V0 					= single(0); */
  rtElectricalID_DW->V0 = 0.0F;

  /* '<S1>:88:83' lambda  			= single(0.01); */
  rtElectricalID_DW->lambda = 0.01F;

  /* '<S1>:88:84' updateJ 			= boolean(1); */
  rtElectricalID_DW->updateJ = true;

  /*  initialize varaibles for PMSM parameters */
  /* '<S1>:88:87' R_corr              = single(0.000); */
  rtElectricalID_DW->R_corr = 0.0F;

  /* 0.060 */
  /*  variables for controller calculation */
  /* '<S1>:88:91' dampingFactor           = single(10.0); */
  rtElectricalID_DW->dampingFactor = 10.0F;

  /* '<S1>:88:92' psiOverJ                = single(5000); */
  rtElectricalID_DW->psiOverJ = 5000.0F;
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function reset_FOC_output
 * Outputs
 */
static void reset_FOC_output(ExtY_ElectricalID_t *rtElectricalID_Y)
{
  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* MATLAB Function 'reset_FOC_output': '<S1>:920' */
  /* '<S1>:920:4' ElectricalID_FOC_output.n_ref_FOC           = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:920:5' ElectricalID_FOC_output.M_ref_FOC           = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.M_ref_FOC = 0.0F;

  /* '<S1>:920:6' ElectricalID_FOC_output.i_dq_ref.d          = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:920:7' ElectricalID_FOC_output.i_dq_ref.q          = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:920:8' ElectricalID_FOC_output.i_dq_ref.zero       = single(0.0); */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:920:9' ElectricalID_FOC_output.enableFOC_speed     = boolean(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S1>:920:10' ElectricalID_FOC_output.enableFOC_current   = boolean(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_current = false;

  /* '<S1>:920:11' ElectricalID_FOC_output.resetIntegrator     = boolean(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.resetIntegrator = false;

  /* '<S1>:920:12' ElectricalID_FOC_output.activeState         = uint16(0); */
  rtElectricalID_Y->ElectricalID_FOC_output.activeState = 0U;

  /* '<S1>:920:13' TwoMassID_FOC_output.Kp_id_out              = single(Kp_id_loc); */
  /* '<S1>:920:14' TwoMassID_FOC_output.Kp_iq_out              = single(Kp_iq_loc); */
  /* '<S1>:920:15' TwoMassID_FOC_output.Kp_n_out               = single(Kp_n_loc); */
  /* '<S1>:920:16' TwoMassID_FOC_output.Ki_id_out              = single(Ki_id_loc); */
  /* '<S1>:920:17' TwoMassID_FOC_output.Ki_iq_out              = single(Ki_iq_loc); */
  /* '<S1>:920:18' TwoMassID_FOC_output.Ki_n_out               = single(Ki_n_loc); */
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function resetParams_LM
 *  reset variables
 */
static void resetParams_LM(DW_ElectricalID_t *rtElectricalID_DW)
{
  /* MATLAB Function 'resetParams_LM': '<S1>:283' */
  /* '<S1>:283:4' measArray1			= single(zeros(1024,1)); */
  memset(&rtElectricalID_DW->measArray1[0], 0, sizeof(real32_T) << 10U);

  /* '<S1>:283:5' Vstep               = single(zeros(205,1)); */
  memset(&rtElectricalID_DW->Vstep[0], 0, 205U * sizeof(real32_T));

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S1>:283:8' d        			= single(zeros(2048,1)); */
  /* '<S1>:283:9' dp      			= single(zeros(2,1)); */
  /* '<S1>:283:10' e       			= single(0); */
  rtElectricalID_DW->e = 0.0F;

  /* '<S1>:283:11' e_lm  				= single(0); */
  /* '<S1>:283:12' H 					= single(zeros(2,2)); */
  rtElectricalID_DW->H[0] = 0.0F;
  rtElectricalID_DW->H[1] = 0.0F;
  rtElectricalID_DW->H[2] = 0.0F;
  rtElectricalID_DW->H[3] = 0.0F;

  /* '<S1>:283:13' i_est 				= single(zeros(2048,1)); */
  memset(&rtElectricalID_DW->d[0], 0, sizeof(real32_T) << 11U);
  memset(&rtElectricalID_DW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S1>:283:14' it 					= uint16(0); */
  /* '<S1>:283:15' J 					= single(zeros(2048,2)); */
  memset(&rtElectricalID_DW->J[0], 0, sizeof(real32_T) << 12U);

  /* '<S1>:283:16' k 					= single(0); */
  /* '<S1>:283:17' L0 					= single(0); */
  /* '<S1>:283:18' L_est   			= single(0); */
  /* '<S1>:283:19' L_lm 				= single(0); */
  /* '<S1>:283:20' Ndata  				= uint16(512); */
  /* '<S1>:283:21' Nparams 			= uint16(2); */
  /* '<S1>:283:22' n_iters 			= uint16(100); */
  rtElectricalID_DW->n_iters = 100U;

  /* '<S1>:283:23' R0 					= single(0); */
  /* '<S1>:283:24' R_est 				= single(0); */
  /* '<S1>:283:25' R_lm 				= single(0); */
  /* '<S1>:283:26' V0 					= single(0); */
  rtElectricalID_DW->V0 = 0.0F;

  /* '<S1>:283:27' lambda  			= single(0.01); */
  rtElectricalID_DW->lambda = 0.01F;

  /* '<S1>:283:28' updateJ 			= boolean(1); */
  rtElectricalID_DW->updateJ = true;

  /* L_d                 = single(0); */
  /* R_s                 = single(0); */
}

/* Function for Chart: '<Root>/ElectricalID' */
static void enter_atomic_calculatePIcontrol(ExtU_ElectricalID_t
  *rtElectricalID_U, ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t
  *rtElectricalID_DW)
{
  real32_T Ki_id_loc;
  real32_T Kp_id_loc;
  real32_T Kp_id_loc_tmp;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Entry 'calculatePIcontroller': '<S1>:284' */
  /* state6.0 */
  /* '<S1>:284:4' ElectricalID_FOC_output.activeState = uint16(144); */
  rtElectricalID_Y->ElectricalID_FOC_output.activeState = 144U;

  /*  calculation according to Gemaßmer KIT */
  /* '<S1>:284:6' Kp_id_loc = ElectricalID_output.PMSM_parameters.Ld_Henry / (3.0 * GlobalConfig.sampleTimeISR) ; */
  Kp_id_loc_tmp = 3.0F * rtElectricalID_U->GlobalConfig_out.sampleTimeISR;

  /* Outport: '<Root>/ElectricalID_output' */
  Kp_id_loc =
    rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Ld_Henry /
    Kp_id_loc_tmp;

  /* '<S1>:284:7' Ki_id_loc = ElectricalID_output.PMSM_parameters.R_ph_Ohm / (3.0 * GlobalConfig.sampleTimeISR) ; */
  Ki_id_loc =
    rtElectricalID_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm /
    Kp_id_loc_tmp;

  /* '<S1>:284:8' Ki_iq_loc = Ki_id_loc; */
  /* '<S1>:284:9' if (ElectricalIDConfig.identLq == 1) */
  if (rtElectricalID_U->ElectricalIDConfig.identLq) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:284:10' Kp_iq_loc = ElectricalID_output.PMSM_parameters.Lq_Henry / (3.0 * GlobalConfig.sampleTimeISR) ; */
    rtElectricalID_DW->Kp_iq_loc =
      rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry /
      Kp_id_loc_tmp;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:284:11' elseif (ElectricalIDConfig.identLq == 0) */
    /* '<S1>:284:12' ElectricalID_output.PMSM_parameters.Lq_Henry = .... */
    /* '<S1>:284:13'         ElectricalID_output.PMSM_parameters.Ld_Henry; */
    rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry =
      rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Ld_Henry;

    /* . */
    /* '<S1>:284:14' Kp_iq_loc = Kp_id_loc; */
    rtElectricalID_DW->Kp_iq_loc = Kp_id_loc;
  }

  /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
   *  Outport: '<Root>/ElectricalID_output'
   */
  /* '<S1>:284:16' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.PMSM_parameters.Lq_Henry*dampingFactor*.... */
  /* '<S1>:284:17'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*psiOverJ); */
  /* . */
  /* '<S1>:284:18' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.PMSM_parameters.Lq_Henry *.... */
  /* '<S1>:284:19'     ElectricalID_output.PMSM_parameters.Lq_Henry  * dampingFactor * dampingFactor * .... */
  /* '<S1>:284:20'     dampingFactor * GlobalConfig.PMSM_config.polePairs... */
  /* '<S1>:284:21'     *3.0/2.0*psiOverJ); */
  /* . */
  /* Output calculated values */
  /* '<S1>:284:23' ElectricalID_FOC_output.Kp_id_out = Kp_id_loc; */
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_id_out = Kp_id_loc;

  /* '<S1>:284:24' ElectricalID_FOC_output.Ki_id_out = Ki_id_loc; */
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_id_out = Ki_id_loc;

  /* '<S1>:284:25' ElectricalID_FOC_output.Kp_iq_out = Kp_iq_loc; */
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_iq_out =
    rtElectricalID_DW->Kp_iq_loc;

  /* '<S1>:284:26' ElectricalID_FOC_output.Ki_iq_out = Ki_iq_loc; */
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_iq_out = Ki_id_loc;

  /* '<S1>:284:27' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_n_out =
    rtElectricalID_DW->Kp_iq_loc /
    (rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
     rtElectricalID_DW->dampingFactor *
     rtElectricalID_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F / 2.0F *
     rtElectricalID_DW->psiOverJ);

  /* '<S1>:284:28' ElectricalID_FOC_output.Ki_n_out = single(Ki_n_loc); */
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_n_out =
    rtElectricalID_DW->Kp_iq_loc * rtElectricalID_DW->Kp_iq_loc /
    (rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
     rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
     rtElectricalID_DW->dampingFactor * rtElectricalID_DW->dampingFactor *
     rtElectricalID_DW->dampingFactor *
     rtElectricalID_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F / 2.0F *
     rtElectricalID_DW->psiOverJ);
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW_ElectricalID_t *rtElectricalID_DW)
{
  /* MATLAB Function 'RefreshDataRegister': '<S1>:784' */
  /* '<S1>:784:3' m=length(omega_register); */
  /* '<S1>:784:4' for k= single(0):single(m-2) */
  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_DW->omega_register[4] = rtElectricalID_DW->omega_register[3];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_DW->omega_register[3] = rtElectricalID_DW->omega_register[2];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_DW->omega_register[2] = rtElectricalID_DW->omega_register[1];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_DW->omega_register[1] = rtElectricalID_DW->omega_register[0];
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function DutyCycle_mod(om_reg_in)
 */
static void DutyCycle_mod(const real32_T om_reg_in[5], ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW)
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
  if (!rtElectricalID_DW->om_con) {
    /* Inport: '<Root>/ElectricalIDConfig' incorporates:
     *  Inport: '<Root>/GlobalConfig'
     */
    /* '<S1>:769:8' if(mean_om_reg >(ElectricalIDConfig.min_n_ratio*GlobalConfig.ratSpeed*2*pi)/60) */
    if (mean_om_reg > rtElectricalID_U->ElectricalIDConfig.min_n_ratio *
        rtElectricalID_U->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F / 60.0F)
    {
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

      tmp = rtElectricalID_U->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F *
        0.05F / 60.0F;
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
            rtElectricalID_DW->om_con = true;
          } else {
            /* '<S1>:769:16' else */
            /* '<S1>:769:17' om_con=boolean(0); */
            rtElectricalID_DW->om_con = false;
          }
        } else {
          /* '<S1>:769:16' else */
          /* '<S1>:769:17' om_con=boolean(0); */
          rtElectricalID_DW->om_con = false;
        }
      } else {
        /* '<S1>:769:16' else */
        /* '<S1>:769:17' om_con=boolean(0); */
        rtElectricalID_DW->om_con = false;
      }
    } else {
      /* '<S1>:769:19' else */
      /* '<S1>:769:20' om_con=boolean(0); */
      rtElectricalID_DW->om_con = false;
    }

    /* End of Inport: '<Root>/ElectricalIDConfig' */
  }

  if (!rtElectricalID_DW->om_con) {
    /* Increases the DutyCycle by 1% every 2 seconds, if the motor isn't */
    /* rotating properly */
    /* '<S1>:769:26' DutyCycle = DutyCycle + 0.01; */
    rtElectricalID_DW->DutyCycle += 0.01F;

    /* Simulation 0.001 | Real 0.01 */
  }

  /* '<S1>:769:23' if(om_con == 0) */
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function TurnMotor
 */
static void TurnMotor(ExtU_ElectricalID_t *rtElectricalID_U, ExtY_ElectricalID_t
                      *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  real32_T ElectricalID_output_tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'TurnMotor': '<S1>:380' */
  /* '<S1>:380:3' sineCounter = single(counter); */
  /*  rechtslauf */
  /* '<S1>:380:6' ElectricalID_output.PWM_Switch_0 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2)+0.5; */
  ElectricalID_output_tmp = 50.2654839F * (real32_T)rtElectricalID_DW->counter *
    rtElectricalID_U->GlobalConfig_out.sampleTimeISR;

  /* Outport: '<Root>/ElectricalID_output' */
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = sinf
    (ElectricalID_output_tmp + 1.57079637F) * (0.5F *
    rtElectricalID_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:7' ElectricalID_output.PWM_Switch_2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2)+0.5; */
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_2 = sinf
    ((ElectricalID_output_tmp - 2.09439516F) + 1.57079637F) * (0.5F *
    rtElectricalID_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:8' ElectricalID_output.PWM_Switch_4 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+2*pi/3+pi/2)+0.5; */
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = sinf
    ((ElectricalID_output_tmp + 2.09439516F) + 1.57079637F) * (0.5F *
    rtElectricalID_DW->DutyCycle) + 0.5F;

  /*  linkslauf */
  /*  ElectricalID_output.PWM_Switch_0 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2); */
  /*  ElectricalID_output.PWM_Switch_2 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+2*pi/3+pi/2); */
  /*  ElectricalID_output.PWM_Switch_4 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2); */
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function DutyCycle_mod(ia_reg_in)
 */
static void DutyCycle_mod_a(real32_T ia_reg_in, ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW)
{
  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'DutyCycle_mod': '<S1>:796' */
  /* '<S1>:796:3' mean_ia_reg=mean(ia_reg_in); */
  /* determines if the mean value is below the step-response current limit */
  /* '<S1>:796:5' if(mean_ia_reg < 0.5*GlobalConfig.ratCurrent) */
  if (ia_reg_in < 0.5F * rtElectricalID_U->GlobalConfig_out.ratCurrent) {
    /* Current limit for step response   */
    /* '<S1>:796:6' ia_valid=boolean(0); */
    rtElectricalID_DW->ia_valid = false;
  } else {
    /* '<S1>:796:7' else */
    /* '<S1>:796:8' ia_valid=boolean(1); */
    rtElectricalID_DW->ia_valid = true;
  }

  /* End of Inport: '<Root>/GlobalConfig' */
  /* '<S1>:796:11' if(ia_valid == 0) */
  if (!rtElectricalID_DW->ia_valid) {
    /* Increases the DutyCycle by 0.5% every 0.5 second, if the step response */
    /* is below the current limit */
    /* '<S1>:796:14' DutyCycle = DutyCycle + 0.005; */
    rtElectricalID_DW->DutyCycle += 0.005F;

    /* Simulation 0.001 | Real 0.005 */
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void measure_psiPM(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
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
  /* '<S1>:406:1' sf_internal_predicateOutput = ElectricalID_output.PMSM_parameters.Psi_PM_Vs > 0; */
  if (rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs > 0.0F) {
    /* Transition: '<S1>:406' */
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:20' counter = uint32(1); */
    rtElectricalID_DW->counter = 1U;
    rtElectricalID_DW->is_ElectricalID = IN_stop;

    /* Entry 'stop': '<S1>:361' */
    /* state 10.1 */
    /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(151); */
    rtElectricalID_Y->ElectricalID_FOC_output.activeState = 151U;

    /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
    rtElectricalID_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

    /* '<S1>:361:5' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID_Y->ElectricalID_FOC_output.resetIntegrator = true;
  } else {
    /* '<S1>:405:9' if(counter > wait_count && counter < (wait_count+1025)) */
    qY = rtElectricalID_DW->wait_count + 1025U;
    if (rtElectricalID_DW->wait_count + 1025U < rtElectricalID_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if ((rtElectricalID_DW->counter > rtElectricalID_DW->wait_count) &&
        (rtElectricalID_DW->counter < qY)) {
      /* '<S1>:405:10' measArray1(counter-wait_count) = ActualValues.v_dq.q; */
      qY_tmp_tmp = rtElectricalID_DW->counter - /*MW:OvSatOk*/
        rtElectricalID_DW->wait_count;
      qY_tmp = qY_tmp_tmp;
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID_DW->counter) {
        qY = 0U;
        qY_tmp = 0U;
      }

      rtElectricalID_DW->measArray1[(int32_T)qY - 1] =
        rtElectricalID_U->ActualValues.v_dq.q;

      /* '<S1>:405:11' d(counter-wait_count) = ActualValues.i_dq.q; */
      rtElectricalID_DW->d[(int32_T)qY_tmp - 1] =
        rtElectricalID_U->ActualValues.i_dq.q;

      /* '<S1>:405:12' i_est(counter-wait_count) = ActualValues.omega_el; */
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID_DW->counter) {
        qY = 0U;
      }

      rtElectricalID_DW->i_est[(int32_T)qY - 1] =
        rtElectricalID_U->ActualValues.omega_el;
    }

    /* '<S1>:405:14' if(counter == (wait_count+1025)) */
    qY = rtElectricalID_DW->wait_count + 1025U;
    if (rtElectricalID_DW->wait_count + 1025U < rtElectricalID_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if (rtElectricalID_DW->counter == qY) {
      /* '<S1>:405:15' ElectricalID_output.PMSM_parameters.Psi_PM_Vs = (mean(measArray1(1:1024))-mean(d(1:1024))*.... */
      /* '<S1>:405:16'         ElectricalID_output.PMSM_parameters.R_ph_Ohm)/(mean(i_est(1:1024))); */
      x = rtElectricalID_DW->measArray1[0];
      b_x = rtElectricalID_DW->d[0];
      c_x = rtElectricalID_DW->i_est[0];
      for (k = 0; k < 1023; k++) {
        x += rtElectricalID_DW->measArray1[k + 1];
        b_x += rtElectricalID_DW->d[k + 1];
        c_x += rtElectricalID_DW->i_est[k + 1];
      }

      rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs = (x /
        1024.0F - b_x / 1024.0F *
        rtElectricalID_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm) / (c_x /
        1024.0F);

      /* . */
    }

    /* '<S1>:405:18' counter = counter + 1; */
    qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
      qY = MAX_uint32_T;
    }

    rtElectricalID_DW->counter = qY;
  }

  /* End of Outport: '<Root>/ElectricalID_output' */
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function y = SinusGenerator(Amp, Freq, sampleTime)
 */
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID_t *rtElectricalID_DW)
{
  real32_T tmp;
  real32_T x;
  uint32_T qY;

  /* MATLAB Function 'SinusGenerator': '<S1>:922' */
  /* '<S1>:922:6' if isempty(sineCounter) */
  /* '<S1>:922:10' u = single(Amp*sin(2*pi*single(Freq)*single(sineCounter)*sampleTime)); */
  x = 6.28318548F * Freq * (real32_T)rtElectricalID_DW->sineCounter * sampleTime;

  /* '<S1>:922:11' sineCounter = sineCounter + 1; */
  qY = rtElectricalID_DW->sineCounter + /*MW:OvSatOk*/ 1U;
  if (rtElectricalID_DW->sineCounter + 1U < rtElectricalID_DW->sineCounter) {
    qY = MAX_uint32_T;
  }

  rtElectricalID_DW->sineCounter = qY;

  /* '<S1>:922:12' if(sineCounter == uint32(1/(single(Freq)*sampleTime))) */
  tmp = roundf(1.0F / (Freq * sampleTime));
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      qY = (uint32_T)tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtElectricalID_DW->sineCounter == qY) {
    /* '<S1>:922:13' sineCounter = uint32(0); */
    rtElectricalID_DW->sineCounter = 0U;
  }

  /* '<S1>:922:17' y = single(u); */
  return Amp * sinf(x);
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
 * function goertzel
 *  goertzel algorithm for J calculation
 */
static void goertzel(ExtU_ElectricalID_t *rtElectricalID_U, ExtY_ElectricalID_t *
                     rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  int32_T k;
  real32_T A;
  real32_T B;
  real32_T C_im;
  real32_T C_re;
  real32_T Xg_im;
  real32_T Xg_re;
  real32_T s0;
  real32_T s2;

  /* MATLAB Function 'goertzel': '<S1>:350' */
  /*  calculate momentum from i_q */
  /* '<S1>:350:6' for k=single(1):single(500) */
  for (k = 0; k < 500; k++) {
    /* Inport: '<Root>/GlobalConfig' incorporates:
     *  Outport: '<Root>/ElectricalID_output'
     */
    /* '<S1>:350:7' d(k) = 1.5*GlobalConfig.PMSM_config.polePairs*ElectricalID_output.PMSM_parameters.Psi_PM_Vs*measArray1(k); */
    rtElectricalID_DW->d[k] = 1.5F *
      rtElectricalID_U->GlobalConfig_out.PMSM_config.polePairs *
      rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs *
      rtElectricalID_DW->measArray1[k];
  }

  /* Inport: '<Root>/GlobalConfig' */
  /*  goertzel */
  /* '<S1>:350:11' ISR_factor = single(0.0001 / GlobalConfig.sampleTimeISR); */
  /* Adjusts the k-factor for different ISR frequencys */
  /* '<S1>:350:12' k = single(2.0 / ISR_factor); */
  /*  coefficient number of the spectrum (40Hz) */
  /* '<S1>:350:13' N = 500; */
  /*  length of input signal */
  /* Precalculation of constants */
  /* '<S1>:350:16' A = 2*pi*k/N; */
  A = 2.0F / (0.0001F / rtElectricalID_U->GlobalConfig_out.sampleTimeISR) *
    6.28318548F / 500.0F;

  /* '<S1>:350:17' B = 2*cos(A); */
  B = 2.0F * cosf(A);

  /* '<S1>:350:18' C = exp(-j*A); */
  if (-A == 0.0F) {
    C_re = 1.0F;
    C_im = 0.0F;
  } else {
    C_re = cosf(-A);
    C_im = sinf(-A);
  }

  /* State variables */
  /* '<S1>:350:20' s0 = single(0.0); */
  /* '<S1>:350:21' s1 = single(0.0); */
  A = 0.0F;

  /* '<S1>:350:22' s2 = single(0.0); */
  s2 = 0.0F;

  /* Main loop for M */
  /* '<S1>:350:25' for i = 1:N */
  for (k = 0; k < 500; k++) {
    /* N multiplications, 2N additions */
    /* '<S1>:350:26' s0 = d(i) +B*s1-s2; */
    s0 = (B * A + rtElectricalID_DW->d[k]) - s2;

    /* corresponds to (16) */
    /* '<S1>:350:27' s2 = s1; */
    s2 = A;

    /* '<S1>:350:28' s1 = s0; */
    A = s0;
  }

  /* Finalizing calculations for M */
  /* '<S1>:350:32' s0 = B*s1-s2; */
  /* corresponds to (16) with zero input; 1 multiplication and 1 addition */
  /* '<S1>:350:33' Xg = s0-s1*C %corresponds to (17); 4 multiplications and 3 additions */
  Xg_re = (B * A - s2) - A * C_re;
  Xg_im = 0.0F - A * C_im;

  /* corresponds to (17); 4 multiplications and 3 additions */
  /* Reset state variables */
  /* '<S1>:350:36' s0 = single(0.0); */
  /* '<S1>:350:37' s1 = single(0.0); */
  A = 0.0F;

  /* '<S1>:350:38' s2 = single(0.0); */
  s2 = 0.0F;

  /* Main loop for omega_m */
  /* '<S1>:350:41' for i = 1:N */
  for (k = 0; k < 500; k++) {
    /* N multiplications, 2N additions */
    /* '<S1>:350:42' s0 = i_est(i) +B*s1-s2; */
    s0 = (B * A + rtElectricalID_DW->i_est[k]) - s2;

    /* corresponds to (16) */
    /* '<S1>:350:43' s2 = s1; */
    s2 = A;

    /* '<S1>:350:44' s1 = s0; */
    A = s0;
  }

  /* Finalizing calculations for omega_m */
  /* '<S1>:350:48' s0 = B*s1-s2; */
  /* corresponds to (16) with zero input; 1 multiplication and 1 addition */
  /* '<S1>:350:49' Yg = s0-s1*C %corresponds to (17); 4 multiplications and 3 additions */
  /* corresponds to (17); 4 multiplications and 3 additions */
  /*  calculate value of transfer function  */
  /* '<S1>:350:54' Gg = Yg/Xg; */
  /*  calculate J from Gg */
  /* '<S1>:350:56' ElectricalID_output.PMSM_parameters.J_kg_m_squared = single(abs(1/(Gg*j*2*pi*40))); */
  C_re = (B * A - s2) - A * C_re;
  B = 0.0F - A * C_im;
  if (Xg_im == 0.0F) {
    if (B == 0.0F) {
      C_im = C_re / Xg_re;
      Xg_im = 0.0F;
    } else if (C_re == 0.0F) {
      C_im = 0.0F;
      Xg_im = B / Xg_re;
    } else {
      C_im = C_re / Xg_re;
      Xg_im = B / Xg_re;
    }
  } else if (Xg_re == 0.0F) {
    if (C_re == 0.0F) {
      C_im = B / Xg_im;
      Xg_im = 0.0F;
    } else if (B == 0.0F) {
      C_im = 0.0F;
      Xg_im = -(C_re / Xg_im);
    } else {
      C_im = B / Xg_im;
      Xg_im = -(C_re / Xg_im);
    }
  } else {
    A = fabsf(Xg_re);
    C_im = fabsf(Xg_im);
    if (A > C_im) {
      A = Xg_im / Xg_re;
      Xg_im = A * Xg_im + Xg_re;
      C_im = (A * B + C_re) / Xg_im;
      Xg_im = (B - A * C_re) / Xg_im;
    } else if (C_im == A) {
      Xg_re = Xg_re > 0.0F ? 0.5F : -0.5F;
      Xg_im = Xg_im > 0.0F ? 0.5F : -0.5F;
      C_im = (C_re * Xg_re + B * Xg_im) / A;
      Xg_im = (B * Xg_re - C_re * Xg_im) / A;
    } else {
      A = Xg_re / Xg_im;
      Xg_im += A * Xg_re;
      C_im = (A * C_re + B) / Xg_im;
      Xg_im = (A * B - C_re) / Xg_im;
    }
  }

  Xg_im = (0.0F - Xg_im) * 2.0F * 3.14159274F * 40.0F;
  Xg_re = 2.0F * C_im * 3.14159274F * 40.0F;
  if (Xg_re == 0.0F) {
    C_re = 1.0F / Xg_im;
    C_im = 0.0F;
  } else if (Xg_im == 0.0F) {
    C_re = 0.0F;
    C_im = -(1.0F / Xg_re);
  } else {
    A = fabsf(Xg_im);
    C_im = fabsf(Xg_re);
    if (A > C_im) {
      A = Xg_re / Xg_im;
      Xg_im += A * Xg_re;
      C_re = 1.0F / Xg_im;
      C_im = (0.0F - A) / Xg_im;
    } else if (C_im == A) {
      C_re = (Xg_im > 0.0F ? 0.5F : -0.5F) / A;
      C_im = (0.0F - (Xg_re > 0.0F ? 0.5F : -0.5F)) / A;
    } else {
      A = Xg_im / Xg_re;
      Xg_im = A * Xg_im + Xg_re;
      C_re = A / Xg_im;
      C_im = -1.0F / Xg_im;
    }
  }

  /* Outport: '<Root>/ElectricalID_output' */
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared =
    rt_hypotf(C_re, C_im);

  /* without damping */
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
static void mtimes(const real32_T A[2048], const real32_T B[1024], real32_T C[2])
{
  int32_T i;
  real32_T B_0;
  C[0] = 0.0F;
  C[1] = 0.0F;
  for (i = 0; i < 1024; i++) {
    B_0 = B[i];
    C[0] += A[i] * B_0;
    C[1] += A[i + 1024] * B_0;
  }
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm(real32_T *L_est, real32_T *R_est, ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW)
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
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
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
  for (it = 0; it < rtElectricalID_DW->n_iters; it++) {
    /* '<S1>:92:26' if updateJ == 1 */
    if (rtElectricalID_DW->updateJ) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S1>:92:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S1>:92:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S1>:92:40' d(1:1024) = measArray1(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* Inport: '<Root>/GlobalConfig' */
        /* '<S1>:92:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S1>:92:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S1>:92:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S1>:92:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S1>:92:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        R_lm = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                      rtElectricalID_U->GlobalConfig_out.sampleTimeISR) / *L_est);
        L_lm = (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_DW->V0 *
          rtElectricalID_U->GlobalConfig_out.sampleTimeISR;
        rtElectricalID_DW->J[k] = -((R_lm - 1.0F) * rtElectricalID_DW->V0) /
          (*R_est * *R_est) - L_lm * R_lm / (*L_est * *R_est);
        rtElectricalID_DW->J[k + 2048] = R_lm * L_lm / (*L_est * *L_est);

        /* Inport: '<Root>/GlobalConfig' */
        /* . */
        /* . */
        /* . */
        /* . */
        /* '<S1>:92:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        rtElectricalID_DW->i_est[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F)
          * rtElectricalID_U->GlobalConfig_out.sampleTimeISR * -*R_est / *L_est))
          * (rtElectricalID_DW->V0 / *R_est);
        rtElectricalID_DW->d[k] = rtElectricalID_DW->measArray1[k] -
          rtElectricalID_DW->i_est[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S1>:92:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          H_tmp = k + (i << 1);
          rtElectricalID_DW->H[H_tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            rtElectricalID_DW->H[H_tmp] += rtElectricalID_DW->J[(k << 11) + i_0]
              * rtElectricalID_DW->J[(i << 11) + i_0];
          }
        }
      }

      /* '<S1>:92:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S1>:92:44' e = dot(d,d); */
        rtElectricalID_DW->e = 0.0F;
        for (k = 0; k < 2048; k++) {
          rtElectricalID_DW->e += rtElectricalID_DW->d[k] * rtElectricalID_DW->
            d[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S1>:92:49' H(1,1) = H(1,1) + lambda; */
    rtElectricalID_DW->H[0] += rtElectricalID_DW->lambda;

    /* '<S1>:92:50' H(2,2)=H(2,2)+lambda; */
    rtElectricalID_DW->H[3] += rtElectricalID_DW->lambda;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S1>:92:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    inv(rtElectricalID_DW->H, rtElectricalID_DW->fv4);
    for (k = 0; k < 2; k++) {
      memcpy(&rtElectricalID_DW->fv1[k << 10], &rtElectricalID_DW->J[k << 11],
             sizeof(real32_T) << 10U);
    }

    mtimes(rtElectricalID_DW->fv1, &rtElectricalID_DW->d[0],
           rtElectricalID_DW->fv5);

    /* '<S1>:92:54' R_lm = R_est + dp(1); */
    R_lm = (-rtElectricalID_DW->fv4[0] * rtElectricalID_DW->fv5[0] +
            -rtElectricalID_DW->fv4[2] * rtElectricalID_DW->fv5[1]) + *R_est;

    /* '<S1>:92:55' L_lm = L_est + dp(2); */
    L_lm = (-rtElectricalID_DW->fv4[1] * rtElectricalID_DW->fv5[0] +
            -rtElectricalID_DW->fv4[3] * rtElectricalID_DW->fv5[1]) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S1>:92:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S1>:92:62' d(1:1024) = measArray1(1:1024) - i_est(1:1024); */
    /* '<S1>:92:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* Inport: '<Root>/GlobalConfig' */
      /* '<S1>:92:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      rtElectricalID_DW->i_est[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        rtElectricalID_U->GlobalConfig_out.sampleTimeISR * -R_lm / L_lm)) *
        (rtElectricalID_DW->V0 / R_lm);
      rtElectricalID_DW->d[k] = rtElectricalID_DW->measArray1[k] -
        rtElectricalID_DW->i_est[k];
      e_lm += rtElectricalID_DW->d[k] * rtElectricalID_DW->d[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S1>:92:66' if e_lm < e */
    if (e_lm < rtElectricalID_DW->e) {
      /* '<S1>:92:67' lambda = lambda/10; */
      rtElectricalID_DW->lambda /= 10.0F;

      /* '<S1>:92:68' R_est = R_lm; */
      *R_est = R_lm;

      /* '<S1>:92:69' L_est = L_lm; */
      *L_est = L_lm;

      /* '<S1>:92:70' e = e_lm; */
      rtElectricalID_DW->e = e_lm;

      /* '<S1>:92:71' updateJ = boolean(1); */
      rtElectricalID_DW->updateJ = true;
    } else {
      /* '<S1>:92:72' else */
      /* '<S1>:92:73' updateJ = boolean(0); */
      rtElectricalID_DW->updateJ = false;

      /* '<S1>:92:74' lambda = lambda*10; */
      rtElectricalID_DW->lambda *= 10.0F;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void stepResponse(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  int32_T k;
  real32_T L_est;
  real32_T R_est;
  uint32_T qY;

  /* During 'stepResponse': '<S1>:5' */
  /* '<S1>:95:1' sf_internal_predicateOutput = counter == 1026; */
  if (rtElectricalID_DW->counter == 1026U) {
    /* Transition: '<S1>:95' */
    /* Exit 'stepResponse': '<S1>:5' */
    /* '<S1>:5:32' ElectricalID_FOC_output.activeState = uint16(22); */
    rtElectricalID_DW->is_ElectricalID = IN_Levenberg_Marquardt;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'Levenberg_Marquardt': '<S1>:91' */
    /* state 3.0 */
    /* '<S1>:91:4' ElectricalID_FOC_output.activeState = uint16(141); */
    rtElectricalID_Y->ElectricalID_FOC_output.activeState = 141U;

    /* '<S1>:91:5' LM_algorithm; */
    LM_algorithm(&L_est, &R_est, rtElectricalID_U, rtElectricalID_DW);

    /* Outport: '<Root>/ElectricalID_output' */
    /*  calculate R and L. Considering that all three phases */
    /*  are connected and that a delta connected winding has */
    /*  to be calculated into star connected values, the factor */
    /*  is 2/3 for delta and star connected windings. */
    /*  Therefore Rs and Ld are the values expressed in */
    /*  star connection */
    /* '<S1>:91:12' ElectricalID_output.PMSM_parameters.R_ph_Ohm = (R_est-R_corr)*2.0/3.0; */
    rtElectricalID_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm = (R_est -
      rtElectricalID_DW->R_corr) * 2.0F / 3.0F;

    /* '<S1>:91:13' ElectricalID_output.PMSM_parameters.Ld_Henry = L_est*2.0/3.0; */
    rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Ld_Henry = L_est *
      2.0F / 3.0F;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:5:7' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 =
      rtElectricalID_DW->DutyCycle;

    /* '<S1>:5:8' if(counter <= 1024) */
    if (rtElectricalID_DW->counter <= 1024U) {
      /* '<S1>:5:9' if(counter > 1) */
      if (rtElectricalID_DW->counter > 1U) {
        /* '<S1>:5:10' measArray1(counter-1) = ActualValues.I_abc.a; */
        qY = rtElectricalID_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter - 1U > rtElectricalID_DW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID_U->ActualValues.I_abc.a;

        /* '<S1>:5:11' if(mod(counter,5) == 0) */
        if (rtElectricalID_DW->counter - rtElectricalID_DW->counter / 5U * 5U ==
            0U) {
          /* '<S1>:5:12' Vstep(z-1) = ActualValues.V_abc.a; */
          qY = rtElectricalID_DW->z - 1U;
          if (rtElectricalID_DW->z - 1U > rtElectricalID_DW->z) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_DW->Vstep[(int32_T)qY - 1] =
            rtElectricalID_U->ActualValues.V_abc.a;

          /* '<S1>:5:13' z = z + 1; */
          qY = rtElectricalID_DW->z + 1U;
          if (rtElectricalID_DW->z + 1U > 65535U) {
            qY = 65535U;
          }

          rtElectricalID_DW->z = (uint16_T)qY;
        }

        /* '<S1>:5:15' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }

      /* '<S1>:5:17' if(counter == 1) */
      if (rtElectricalID_DW->counter == 1U) {
        /* '<S1>:5:18' counter = counter + 1 */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;

        /* Inport: '<Root>/ActualValues' */
        /* '<S1>:5:19' Vstep(1) = ActualValues.V_abc.a; */
        rtElectricalID_DW->Vstep[0] = rtElectricalID_U->ActualValues.V_abc.a;

        /* '<S1>:5:20' z = z + 1; */
        qY = rtElectricalID_DW->z + 1U;
        if (rtElectricalID_DW->z + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_DW->z = (uint16_T)qY;
      }
    } else {
      /* '<S1>:5:22' else */
      /* '<S1>:5:23' if(counter == 1025) */
      if (rtElectricalID_DW->counter == 1025U) {
        /* '<S1>:5:24' measArray1(counter-1) = ActualValues.I_abc.a; */
        qY = rtElectricalID_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter - 1U > rtElectricalID_DW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID_U->ActualValues.I_abc.a;

        /* '<S1>:5:25' Vstep(z-1) = ActualValues.I_abc.a; */
        qY = rtElectricalID_DW->z - 1U;
        if (rtElectricalID_DW->z - 1U > rtElectricalID_DW->z) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_DW->Vstep[(int32_T)qY - 1] =
          rtElectricalID_U->ActualValues.I_abc.a;

        /* '<S1>:5:26' V0 = mean(Vstep); */
        L_est = rtElectricalID_DW->Vstep[0];
        for (k = 0; k < 204; k++) {
          L_est += rtElectricalID_DW->Vstep[k + 1];
        }

        rtElectricalID_DW->V0 = L_est / 205.0F;
      }

      /* Outport: '<Root>/ElectricalID_output' */
      /* '<S1>:5:28' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* '<S1>:5:29' counter = counter + 1; */
      qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
        qY = MAX_uint32_T;
      }

      rtElectricalID_DW->counter = qY;
    }
  }
}

/*
 * Function for Chart: '<Root>/ElectricalID'
 * function LM_algorithm_Lq
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_Lq(real32_T *L_est, ExtU_ElectricalID_t
  *rtElectricalID_U, DW_ElectricalID_t *rtElectricalID_DW)
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
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
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
  for (it = 0; it < rtElectricalID_DW->n_iters; it++) {
    /* '<S1>:281:26' if updateJ == 1 */
    if (rtElectricalID_DW->updateJ) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S1>:281:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S1>:281:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S1>:281:40' d(1:1024) = measArray1(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* Inport: '<Root>/GlobalConfig' */
        /* '<S1>:281:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S1>:281:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S1>:281:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S1>:281:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S1>:281:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        R_lm = expf(-((((real32_T)k + 1.0F) - 1.0F) * R_est *
                      rtElectricalID_U->GlobalConfig_out.sampleTimeISR) / *L_est);
        L_lm = (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_DW->V0 *
          rtElectricalID_U->GlobalConfig_out.sampleTimeISR;
        rtElectricalID_DW->J[k] = -((R_lm - 1.0F) * rtElectricalID_DW->V0) /
          (R_est * R_est) - L_lm * R_lm / (*L_est * R_est);
        rtElectricalID_DW->J[k + 2048] = R_lm * L_lm / (*L_est * *L_est);

        /* Inport: '<Root>/GlobalConfig' */
        /* . */
        /* . */
        /* . */
        /* . */
        /* '<S1>:281:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        rtElectricalID_DW->i_est[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F)
          * rtElectricalID_U->GlobalConfig_out.sampleTimeISR * -R_est / *L_est))
          * (rtElectricalID_DW->V0 / R_est);
        rtElectricalID_DW->d[k] = rtElectricalID_DW->measArray1[k] -
          rtElectricalID_DW->i_est[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S1>:281:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          H_tmp = k + (i << 1);
          rtElectricalID_DW->H[H_tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            rtElectricalID_DW->H[H_tmp] += rtElectricalID_DW->J[(k << 11) + i_0]
              * rtElectricalID_DW->J[(i << 11) + i_0];
          }
        }
      }

      /* '<S1>:281:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S1>:281:44' e = dot(d,d); */
        rtElectricalID_DW->e = 0.0F;
        for (k = 0; k < 2048; k++) {
          rtElectricalID_DW->e += rtElectricalID_DW->d[k] * rtElectricalID_DW->
            d[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S1>:281:49' H(1,1) = H(1,1) + lambda; */
    rtElectricalID_DW->H[0] += rtElectricalID_DW->lambda;

    /* '<S1>:281:50' H(2,2)=H(2,2)+lambda; */
    rtElectricalID_DW->H[3] += rtElectricalID_DW->lambda;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S1>:281:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    inv(rtElectricalID_DW->H, rtElectricalID_DW->fv2);
    for (k = 0; k < 2; k++) {
      memcpy(&rtElectricalID_DW->fv[k << 10], &rtElectricalID_DW->J[k << 11],
             sizeof(real32_T) << 10U);
    }

    mtimes(rtElectricalID_DW->fv, &rtElectricalID_DW->d[0],
           rtElectricalID_DW->fv3);

    /* '<S1>:281:54' R_lm = R_est + dp(1); */
    R_lm = (-rtElectricalID_DW->fv2[0] * rtElectricalID_DW->fv3[0] +
            -rtElectricalID_DW->fv2[2] * rtElectricalID_DW->fv3[1]) + R_est;

    /* '<S1>:281:55' L_lm = L_est + dp(2); */
    L_lm = (-rtElectricalID_DW->fv2[1] * rtElectricalID_DW->fv3[0] +
            -rtElectricalID_DW->fv2[3] * rtElectricalID_DW->fv3[1]) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S1>:281:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S1>:281:62' d(1:1024) = measArray1(1:1024) - i_est(1:1024); */
    /* '<S1>:281:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* Inport: '<Root>/GlobalConfig' */
      /* '<S1>:281:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      rtElectricalID_DW->i_est[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        rtElectricalID_U->GlobalConfig_out.sampleTimeISR * -R_lm / L_lm)) *
        (rtElectricalID_DW->V0 / R_lm);
      rtElectricalID_DW->d[k] = rtElectricalID_DW->measArray1[k] -
        rtElectricalID_DW->i_est[k];
      e_lm += rtElectricalID_DW->d[k] * rtElectricalID_DW->d[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S1>:281:66' if e_lm < e */
    if (e_lm < rtElectricalID_DW->e) {
      /* '<S1>:281:67' lambda = lambda/10; */
      rtElectricalID_DW->lambda /= 10.0F;

      /* '<S1>:281:68' R_est = R_lm; */
      R_est = R_lm;

      /* '<S1>:281:69' L_est = L_lm; */
      *L_est = L_lm;

      /* '<S1>:281:70' e = e_lm; */
      rtElectricalID_DW->e = e_lm;

      /* '<S1>:281:71' updateJ = boolean(1); */
      rtElectricalID_DW->updateJ = true;
    } else {
      /* '<S1>:281:72' else */
      /* '<S1>:281:73' updateJ = boolean(0); */
      rtElectricalID_DW->updateJ = false;

      /* '<S1>:281:74' lambda = lambda*10; */
      rtElectricalID_DW->lambda *= 10.0F;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void stepResponse_q(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  int32_T k;
  real32_T L_est;
  uint32_T qY;

  /* During 'stepResponse_q': '<S1>:277' */
  /* '<S1>:279:1' sf_internal_predicateOutput = counter == 1026; */
  if (rtElectricalID_DW->counter == 1026U) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* Transition: '<S1>:279' */
    /* Exit 'stepResponse_q': '<S1>:277' */
    /* '<S1>:277:37' ElectricalID_output.enable_TriState          = [boolean(0),boolean(0),boolean(0)]; */
    rtElectricalID_Y->ElectricalID_output.enable_TriState[0] = false;
    rtElectricalID_Y->ElectricalID_output.enable_TriState[1] = false;
    rtElectricalID_Y->ElectricalID_output.enable_TriState[2] = false;
    rtElectricalID_DW->is_ElectricalID = IN_Levenberg_Marquardt_q;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'Levenberg_Marquardt_q': '<S1>:278' */
    /* '<S1>:278:4' ElectricalID_FOC_output.activeState = uint16(143); */
    rtElectricalID_Y->ElectricalID_FOC_output.activeState = 143U;

    /* '<S1>:278:5' LM_algorithm_Lq; */
    LM_algorithm_Lq(&L_est, rtElectricalID_U, rtElectricalID_DW);

    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:278:6' ElectricalID_output.PMSM_parameters.Lq_Henry = L_est*0.5; */
    rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry = L_est *
      0.5F;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S1>:277:11' ElectricalID_output.PWM_Switch_4 = single(DutyCycle); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 =
      rtElectricalID_DW->DutyCycle;

    /* '<S1>:277:12' if(counter <= 1024) */
    if (rtElectricalID_DW->counter <= 1024U) {
      /* '<S1>:277:13' if(counter > 1) */
      if (rtElectricalID_DW->counter > 1U) {
        /* '<S1>:277:14' measArray1(counter-1) = ActualValues.I_abc.c; */
        qY = rtElectricalID_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter - 1U > rtElectricalID_DW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID_U->ActualValues.I_abc.c;

        /* '<S1>:277:15' if(mod(counter,5) == 0) */
        if (rtElectricalID_DW->counter - rtElectricalID_DW->counter / 5U * 5U ==
            0U) {
          /* '<S1>:277:16' Vstep(z-1) = ActualValues.V_abc.b+ActualValues.V_abc.c; */
          qY = rtElectricalID_DW->z - 1U;
          if (rtElectricalID_DW->z - 1U > rtElectricalID_DW->z) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_DW->Vstep[(int32_T)qY - 1] =
            rtElectricalID_U->ActualValues.V_abc.b +
            rtElectricalID_U->ActualValues.V_abc.c;

          /* '<S1>:277:17' z = z + 1; */
          qY = rtElectricalID_DW->z + 1U;
          if (rtElectricalID_DW->z + 1U > 65535U) {
            qY = 65535U;
          }

          rtElectricalID_DW->z = (uint16_T)qY;
        }

        /* '<S1>:277:19' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }

      /* '<S1>:277:21' if(counter == 1) */
      if (rtElectricalID_DW->counter == 1U) {
        /* '<S1>:277:22' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;

        /* Inport: '<Root>/ActualValues' */
        /* '<S1>:277:23' Vstep(1) = ActualValues.V_abc.c+ActualValues.V_abc.b; */
        rtElectricalID_DW->Vstep[0] = rtElectricalID_U->ActualValues.V_abc.c +
          rtElectricalID_U->ActualValues.V_abc.b;

        /* '<S1>:277:24' z = z + 1; */
        qY = rtElectricalID_DW->z + 1U;
        if (rtElectricalID_DW->z + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_DW->z = (uint16_T)qY;
      }
    } else {
      /* '<S1>:277:26' else */
      /* '<S1>:277:27' if(counter == 1025) */
      if (rtElectricalID_DW->counter == 1025U) {
        /* '<S1>:277:28' measArray1(counter-1) = ActualValues.I_abc.c; */
        qY = rtElectricalID_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter - 1U > rtElectricalID_DW->counter) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID_U->ActualValues.I_abc.c;

        /* '<S1>:277:29' Vstep(z-1) = ActualValues.V_abc.b+ActualValues.V_abc.c; */
        qY = rtElectricalID_DW->z - 1U;
        if (rtElectricalID_DW->z - 1U > rtElectricalID_DW->z) {
          qY = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_DW->Vstep[(int32_T)qY - 1] =
          rtElectricalID_U->ActualValues.V_abc.b +
          rtElectricalID_U->ActualValues.V_abc.c;

        /* '<S1>:277:30' V0 = mean(Vstep); */
        L_est = rtElectricalID_DW->Vstep[0];
        for (k = 0; k < 204; k++) {
          L_est += rtElectricalID_DW->Vstep[k + 1];
        }

        rtElectricalID_DW->V0 = L_est / 205.0F;
      }

      /* Outport: '<Root>/ElectricalID_output' */
      /* '<S1>:277:33' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* '<S1>:277:34' counter = counter + 1; */
      qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
        qY = MAX_uint32_T;
      }

      rtElectricalID_DW->counter = qY;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void exit_internal_ElectricalID(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  /* Exit Internal 'ElectricalID': '<S1>:761' */
  switch (rtElectricalID_DW->is_ElectricalID) {
   case IN_Levenberg_Marquardt:
    /* Exit 'Levenberg_Marquardt': '<S1>:91' */
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Levenberg_Marquardt_q:
    /* Exit 'Levenberg_Marquardt_q': '<S1>:278' */
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off:
    /* Outport: '<Root>/ElectricalID_output' incorporates:
     *  Inport: '<Root>/ActualValues'
     */
    /* Exit 'alignRotor_d_off': '<S1>:53' */
    /* '<S1>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
    rtElectricalID_Y->ElectricalID_output.thetaOffset =
      rtElectricalID_U->ActualValues.theta_m;

    /* '<S1>:53:8' DutyCycle=single(0.0); */
    rtElectricalID_DW->DutyCycle = 0.0F;

    /* resets the DC and DC_manual flag, so that for the step-response */
    /* '<S1>:53:9' DC_manual=boolean(0); */
    rtElectricalID_DW->DC_manual = false;

    /* a new DC can be entered */
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off2:
    /* Exit 'alignRotor_d_off2': '<S1>:848' */
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_on:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'alignRotor_d_on': '<S1>:3' */
    /* '<S1>:3:16' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_evaluate_Turn_DC:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:27' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;

    /* '<S1>:379:28' ElectricalID_output.PWM_Switch_2 = single(0); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_2 = 0.0F;

    /* '<S1>:379:29' ElectricalID_output.PWM_Switch_4 = single(0); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = 0.0F;
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_findDutyCycle:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:29' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_measure_psiPM:
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:20' counter = uint32(1); */
    rtElectricalID_DW->counter = 1U;
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_rotorInertiaEstimation:
    /* Exit 'rotorInertiaEstimation': '<S1>:337' */
    /* '<S1>:337:18' goertzel; */
    goertzel(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_stepResponse:
    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Exit 'stepResponse': '<S1>:5' */
    /* '<S1>:5:32' ElectricalID_FOC_output.activeState = uint16(22); */
    rtElectricalID_Y->ElectricalID_FOC_output.activeState = 22U;
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_stepResponse_q:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'stepResponse_q': '<S1>:277' */
    /* '<S1>:277:37' ElectricalID_output.enable_TriState          = [boolean(0),boolean(0),boolean(0)]; */
    rtElectricalID_Y->ElectricalID_output.enable_TriState[0] = false;
    rtElectricalID_Y->ElectricalID_output.enable_TriState[1] = false;
    rtElectricalID_Y->ElectricalID_output.enable_TriState[2] = false;
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_waitState:
    /* Outport: '<Root>/finishedElectricalID' */
    /* Exit 'waitState': '<S1>:428' */
    /* '<S1>:428:19' finishedElectricalID=boolean(1); */
    rtElectricalID_Y->finishedElectricalID = true;

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:428:20' enteredElectricalID=boolean(0); */
    rtElectricalID_Y->enteredElectricalID = false;

    /* '<S1>:428:21' reset_FOC_output; */
    reset_FOC_output(rtElectricalID_Y);
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   default:
    rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<Root>/ElectricalID' */
static void ElectricalID_p(ExtU_ElectricalID_t *rtElectricalID_U,
  ExtY_ElectricalID_t *rtElectricalID_Y, DW_ElectricalID_t *rtElectricalID_DW)
{
  real32_T DutyCycle_filt;
  uint32_T qY;
  boolean_T guard1 = false;

  /* Inport: '<Root>/GlobalConfig' */
  /* During 'ElectricalID': '<S1>:761' */
  /* '<S1>:901:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.ElectricalID==0 ||.... */
  /* '<S1>:901:2'  GlobalConfig.enableParameterID==0; */
  /* . */
  if (rtElectricalID_U->GlobalConfig_out.Reset ||
      (!rtElectricalID_U->GlobalConfig_out.ElectricalID) ||
      (!rtElectricalID_U->GlobalConfig_out.enableParameterID)) {
    /* Transition: '<S1>:901' */
    /* '<S1>:901:3' enteredElectricalID=boolean(0); */
    /* '<S1>:901:3' initParams; */
    initParams(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
    exit_internal_ElectricalID(rtElectricalID_U, rtElectricalID_Y,
      rtElectricalID_DW);
    rtElectricalID_DW->is_c3_ElectricalID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else {
    guard1 = false;
    switch (rtElectricalID_DW->is_ElectricalID) {
     case IN_Levenberg_Marquardt:
      /* Inport: '<Root>/ElectricalIDConfig' */
      /* During 'Levenberg_Marquardt': '<S1>:91' */
      /* '<S1>:426:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 &&.... */
      /* '<S1>:426:2'  ElectricalIDConfig.identLq == 0; */
      /* . */
      if (rtElectricalID_U->GlobalConfig_out.ACCEPT &&
          (!rtElectricalID_U->ElectricalIDConfig.identLq)) {
        /* Transition: '<S1>:426' */
        /* Exit 'Levenberg_Marquardt': '<S1>:91' */
        rtElectricalID_DW->is_ElectricalID = IN_calculatePIcontroller;
        enter_atomic_calculatePIcontrol(rtElectricalID_U, rtElectricalID_Y,
          rtElectricalID_DW);

        /* '<S1>:420:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 .... */
        /* '<S1>:420:2' && ElectricalIDConfig.identLq == 1; */
        /* . */
      } else if (rtElectricalID_U->GlobalConfig_out.ACCEPT &&
                 rtElectricalID_U->ElectricalIDConfig.identLq) {
        /* Transition: '<S1>:420' */
        /* Exit 'Levenberg_Marquardt': '<S1>:91' */
        rtElectricalID_DW->is_ElectricalID = IN_stepResponse_q;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stepResponse_q': '<S1>:277' */
        /* '<S1>:277:4' ElectricalID_FOC_output.activeState = uint16(142); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 142U;

        /* '<S1>:277:5' resetParams_LM; */
        resetParams_LM(rtElectricalID_DW);

        /* '<S1>:277:6' z = uint16(1); */
        rtElectricalID_DW->z = 1U;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:277:7' ElectricalID_output.enable_TriState          = [boolean(1),boolean(0),boolean(0)]; */
        rtElectricalID_Y->ElectricalID_output.enable_TriState[0] = true;
        rtElectricalID_Y->ElectricalID_output.enable_TriState[1] = false;
        rtElectricalID_Y->ElectricalID_output.enable_TriState[2] = false;

        /* '<S1>:277:8' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* '<S1>:277:9' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;
      }
      break;

     case IN_Levenberg_Marquardt_q:
      /* During 'Levenberg_Marquardt_q': '<S1>:278' */
      /* Transition: '<S1>:295' */
      /* Exit 'Levenberg_Marquardt_q': '<S1>:278' */
      rtElectricalID_DW->is_ElectricalID = IN_calculatePIcontroller;
      enter_atomic_calculatePIcontrol(rtElectricalID_U, rtElectricalID_Y,
        rtElectricalID_DW);
      break;

     case IN_alignRotor_d_off:
      /* During 'alignRotor_d_off': '<S1>:53' */
      /* '<S1>:411:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_DW->one_sec_transition_counter ==
          rtElectricalID_DW->counter) {
        /* Outport: '<Root>/ElectricalID_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         */
        /* Transition: '<S1>:411' */
        /* Exit 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
        rtElectricalID_Y->ElectricalID_output.thetaOffset =
          rtElectricalID_U->ActualValues.theta_m;

        /* '<S1>:53:8' DutyCycle=single(0.0); */
        /* resets the DC and DC_manual flag, so that for the step-response */
        /* '<S1>:53:9' DC_manual=boolean(0); */
        rtElectricalID_DW->DC_manual = false;

        /* a new DC can be entered */
        rtElectricalID_DW->is_ElectricalID = IN_findDutyCycle;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'findDutyCycle': '<S1>:789' */
        /* Motor must be manually locked via load machine until state 60 */
        /* '<S1>:789:4' ElectricalID_FOC_output.activeState = uint16(130); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 130U;

        /* Inport: '<Root>/ElectricalIDConfig' */
        /* '<S1>:789:5' if(ElectricalIDConfig.dutyCyc > 0.0) */
        if (rtElectricalID_U->ElectricalIDConfig.dutyCyc > 0.0F) {
          /* Checks if a manual value for the DutyCycle was set */
          /* '<S1>:789:6' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
          rtElectricalID_DW->DutyCycle =
            rtElectricalID_U->ElectricalIDConfig.dutyCyc;

          /* '<S1>:789:7' DC_manual = boolean(1); */
          rtElectricalID_DW->DC_manual = true;
        } else {
          /* '<S1>:789:8' else */
          /* '<S1>:789:9' DutyCycle = single(0.005); */
          rtElectricalID_DW->DutyCycle = 0.005F;
        }

        /* '<S1>:789:11' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* starts with 1, so that the DutyCylce_mod function wont be entered */
        /* during the fist cycle through the state */
      } else {
        /* '<S1>:53:5' counter  = counter +1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;

     case IN_alignRotor_d_off2:
      /* During 'alignRotor_d_off2': '<S1>:848' */
      /* '<S1>:849:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_DW->one_sec_transition_counter ==
          rtElectricalID_DW->counter) {
        /* Transition: '<S1>:849' */
        /* Exit 'alignRotor_d_off2': '<S1>:848' */
        rtElectricalID_DW->is_ElectricalID = IN_stepResponse;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stepResponse': '<S1>:5' */
        /* state 2.0 */
        /* '<S1>:5:3' ElectricalID_FOC_output.activeState = uint16(140); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 140U;

        /* '<S1>:5:4' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* '<S1>:5:5' z = uint16(1); */
        rtElectricalID_DW->z = 1U;
      } else {
        /* '<S1>:848:5' counter = counter +1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;

     case IN_alignRotor_d_on:
      /* During 'alignRotor_d_on': '<S1>:3' */
      /* '<S1>:164:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_DW->one_sec_transition_counter ==
          rtElectricalID_DW->counter) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:164' */
        /* Exit 'alignRotor_d_on': '<S1>:3' */
        /* '<S1>:3:16' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;
        rtElectricalID_DW->is_ElectricalID = IN_alignRotor_d_off;

        /* Entry 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:3' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:53:4' ElectricalID_FOC_output.activeState = uint16(121); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 121U;
      } else {
        /* '<S1>:3:7' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
        DutyCycle_filt = (real32_T)rtElectricalID_DW->counter *
          rtElectricalID_U->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S1>:3:8' if(DutyCycle_filt > 1) */
        if (DutyCycle_filt > 1.0F) {
          /* '<S1>:3:9' DutyCycle_filt = single(1.0); */
          DutyCycle_filt = 1.0F;
        }

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:3:11' ElectricalID_output.PWM_Switch_0 = single(DutyCycle*DutyCycle_filt); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 =
          rtElectricalID_DW->DutyCycle * DutyCycle_filt;

        /* '<S1>:3:12' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* '<S1>:3:13' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* '<S1>:3:14' counter  = counter +1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;

     case IN_calculatePIcontroller:
      /* During 'calculatePIcontroller': '<S1>:284' */
      /* '<S1>:408:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1; */
      if (rtElectricalID_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:408' */
        rtElectricalID_DW->is_ElectricalID = IN_measure_psiPM;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Inport: '<Root>/ElectricalIDConfig'
         */
        /* Entry 'measure_psiPM': '<S1>:405' */
        /* '<S1>:405:4' ElectricalID_FOC_output.activeState = uint16(150); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 150U;

        /* '<S1>:405:5' ElectricalID_FOC_output.enableFOC_speed = boolean(1); */
        rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_speed = true;

        /* '<S1>:405:6' ElectricalID_FOC_output.n_ref_FOC = ElectricalIDConfig.n_ref_measurement; */
        rtElectricalID_Y->ElectricalID_FOC_output.n_ref_FOC =
          rtElectricalID_U->ElectricalIDConfig.n_ref_measurement;

        /* '<S1>:405:7' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        DutyCycle_filt = roundf(3.0F /
          rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
        if (DutyCycle_filt < 4.2949673E+9F) {
          if (DutyCycle_filt >= 0.0F) {
            rtElectricalID_DW->wait_count = (uint32_T)DutyCycle_filt;
          } else {
            rtElectricalID_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID_DW->wait_count = MAX_uint32_T;
        }
      }
      break;

     case IN_endState:
      /* During 'endState': '<S1>:356' */
      /* '<S1>:425:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_DW->one_sec_transition_counter ==
          rtElectricalID_DW->counter) {
        /* Transition: '<S1>:425' */
        rtElectricalID_DW->is_ElectricalID = IN_waitState;

        /* Entry 'waitState': '<S1>:428' */
        /* do nothing */
        /* '<S1>:428:3' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Outport: '<Root>/ElectricalID_output'
         */
        /* '<S1>:428:4' ElectricalID_FOC_output.enableFOC_torque = boolean(0); */
        rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_torque = false;

        /* '<S1>:428:5' ElectricalID_FOC_output.activeState = uint16(170); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 170U;

        /*  recalculate speed controller using psiPM and J */
        /* '<S1>:428:7' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.PMSM_parameters.Lq_Henry*dampingFactor*... */
        /* '<S1>:428:8'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*ElectricalID_output.PMSM_parameters.Psi_PM_Vs/.... */
        /* '<S1>:428:9'     ElectricalID_output.PMSM_parameters.J_kg_m_squared); */
        /* . */
        /* '<S1>:428:10' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.PMSM_parameters.Lq_Henry * .... */
        /* '<S1>:428:11'     ElectricalID_output.PMSM_parameters.Lq_Henry * dampingFactor * dampingFactor * dampingFactor * .... */
        /* '<S1>:428:12'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*ElectricalID_output.PMSM_parameters.Psi_PM_Vs/.... */
        /* '<S1>:428:13'     ElectricalID_output.PMSM_parameters.J_kg_m_squared); */
        /* . */
        /* . */
        /* . */
        /* '<S1>:428:14' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
        rtElectricalID_Y->ElectricalID_FOC_output.Kp_n_out =
          rtElectricalID_DW->Kp_iq_loc /
          (rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
           rtElectricalID_DW->dampingFactor *
           rtElectricalID_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F /
           2.0F *
           rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs /
           rtElectricalID_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared);

        /* '<S1>:428:15' ElectricalID_FOC_output.Ki_n_out = Ki_n_loc; */
        rtElectricalID_Y->ElectricalID_FOC_output.Ki_n_out =
          rtElectricalID_DW->Kp_iq_loc * rtElectricalID_DW->Kp_iq_loc /
          (rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
           rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
           rtElectricalID_DW->dampingFactor * rtElectricalID_DW->dampingFactor *
           rtElectricalID_DW->dampingFactor *
           rtElectricalID_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F /
           2.0F *
           rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs /
           rtElectricalID_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared);
      } else {
        /* '<S1>:356:9' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;

     case IN_evaluate_Turn_DC:
      /* During 'evaluate_Turn_DC': '<S1>:379' */
      /* '<S1>:383:1' sf_internal_predicateOutput = om_con==1; */
      if (rtElectricalID_DW->om_con || rtElectricalID_DW->DC_manual) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:383' */
        /* Transition: '<S1>:921' */
        /* Exit 'evaluate_Turn_DC': '<S1>:379' */
        /* '<S1>:379:27' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* '<S1>:379:28' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* '<S1>:379:29' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = 0.0F;
        rtElectricalID_DW->is_ElectricalID = IN_alignRotor_d_on;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_d_on': '<S1>:3' */
        /* '<S1>:3:4' ElectricalID_FOC_output.activeState = uint16(120); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 120U;

        /* '<S1>:3:5' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;
      } else {
        /* '<S1>:921:1' sf_internal_predicateOutput = DC_manual == 1; */
        /* '<S1>:379:13' if(DC_manual == 0) */
        if (!rtElectricalID_DW->DC_manual) {
          /* Inport: '<Root>/ActualValues' */
          /* averages the last 0.1s */
          /* '<S1>:379:14' omega_sum=omega_sum+single(ActualValues.omega_m); */
          rtElectricalID_DW->omega_sum += rtElectricalID_U->ActualValues.omega_m;

          /* '<S1>:379:15' if(mod(counter,uint32(0.1/GlobalConfig.sampleTimeISR))==0) */
          DutyCycle_filt = roundf(0.1F /
            rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
          if (DutyCycle_filt < 4.2949673E+9F) {
            if (DutyCycle_filt >= 0.0F) {
              qY = (uint32_T)DutyCycle_filt;
            } else {
              qY = 0U;
            }
          } else {
            qY = MAX_uint32_T;
          }

          if (qY == 0U) {
            qY = rtElectricalID_DW->counter;
          } else {
            qY = rtElectricalID_DW->counter - rtElectricalID_DW->counter / qY *
              qY;
          }

          if (qY == 0U) {
            /* '<S1>:379:16' RefreshDataRegister; */
            RefreshDataRegister(rtElectricalID_DW);

            /* '<S1>:379:17' omega_register(1,1)=omega_sum*(GlobalConfig.sampleTimeISR/0.1); */
            rtElectricalID_DW->omega_register[0] =
              rtElectricalID_U->GlobalConfig_out.sampleTimeISR / 0.1F *
              rtElectricalID_DW->omega_sum;

            /* '<S1>:379:18' omega_sum=single(0); */
            rtElectricalID_DW->omega_sum = 0.0F;
          }

          /* '<S1>:379:20' if(mod(counter,uint32(2/GlobalConfig.sampleTimeISR))==0) */
          DutyCycle_filt = roundf(2.0F /
            rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
          if (DutyCycle_filt < 4.2949673E+9F) {
            if (DutyCycle_filt >= 0.0F) {
              qY = (uint32_T)DutyCycle_filt;
            } else {
              qY = 0U;
            }
          } else {
            qY = MAX_uint32_T;
          }

          if (qY == 0U) {
            qY = rtElectricalID_DW->counter;
          } else {
            qY = rtElectricalID_DW->counter - rtElectricalID_DW->counter / qY *
              qY;
          }

          if (qY == 0U) {
            /* after 2s omega will be evaluated */
            /* '<S1>:379:21' DutyCycle_mod(abs(omega_register)); */
            for (rtElectricalID_DW->k = 0; rtElectricalID_DW->k < 5;
                 rtElectricalID_DW->k++) {
              rtElectricalID_DW->c_y[rtElectricalID_DW->k] = fabsf
                (rtElectricalID_DW->omega_register[rtElectricalID_DW->k]);
            }

            DutyCycle_mod(rtElectricalID_DW->c_y, rtElectricalID_U,
                          rtElectricalID_DW);
          }
        }

        /* '<S1>:379:24' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;

        /* '<S1>:379:25' TurnMotor; */
        TurnMotor(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
      }
      break;

     case IN_findDutyCycle:
      /* During 'findDutyCycle': '<S1>:789' */
      /* '<S1>:790:1' sf_internal_predicateOutput = ia_valid==1 ||DC_manual == 1; */
      if (rtElectricalID_DW->ia_valid || rtElectricalID_DW->DC_manual) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S1>:790' */
        /* Exit 'findDutyCycle': '<S1>:789' */
        /* '<S1>:789:29' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;
        rtElectricalID_DW->is_ElectricalID = IN_alignRotor_d_off2;

        /* Entry 'alignRotor_d_off2': '<S1>:848' */
        /* '<S1>:848:3' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:848:4' ElectricalID_FOC_output.activeState = uint16(131); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 131U;

        /* '<S1>:789:14' if(DC_manual == 0 && ia_valid==0) */
      } else if ((!rtElectricalID_DW->DC_manual) &&
                 (!rtElectricalID_DW->ia_valid)) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S1>:789:15' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
        rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 =
          rtElectricalID_DW->DutyCycle;

        /* '<S1>:789:16' if(counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
        DutyCycle_filt = roundf(0.4F /
          rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
        if (DutyCycle_filt < 4.2949673E+9F) {
          if (DutyCycle_filt >= 0.0F) {
            qY = (uint32_T)DutyCycle_filt;
          } else {
            qY = 0U;
          }
        } else {
          qY = MAX_uint32_T;
        }

        if (rtElectricalID_DW->counter < qY) {
          /* '<S1>:789:17' counter = counter +1; */
          qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
            qY = MAX_uint32_T;
          }

          rtElectricalID_DW->counter = qY;
        } else {
          if (DutyCycle_filt < 4.2949673E+9F) {
            if (DutyCycle_filt >= 0.0F) {
              qY = (uint32_T)DutyCycle_filt;
            } else {
              qY = 0U;
            }
          } else {
            qY = MAX_uint32_T;
          }

          if (rtElectricalID_DW->counter >= qY) {
            DutyCycle_filt = roundf(0.5F /
              rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
            if (DutyCycle_filt < 4.2949673E+9F) {
              if (DutyCycle_filt >= 0.0F) {
                qY = (uint32_T)DutyCycle_filt;
              } else {
                qY = 0U;
              }
            } else {
              qY = MAX_uint32_T;
            }

            if (rtElectricalID_DW->counter < qY) {
              /* '<S1>:789:18' elseif(counter >= uint32(0.4/GlobalConfig.sampleTimeISR) &&.... */
              /* '<S1>:789:19'             counter < uint32(0.5/GlobalConfig.sampleTimeISR)) */
              /* . */
              /* '<S1>:789:20' counter = counter +1; */
              qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
              if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter)
              {
                qY = MAX_uint32_T;
              }

              rtElectricalID_DW->counter = qY;

              /* Inport: '<Root>/ActualValues' */
              /* '<S1>:789:21' ia_sum=ia_sum+single(ActualValues.I_abc.a); */
              rtElectricalID_DW->ia_sum +=
                rtElectricalID_U->ActualValues.I_abc.a;
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }
        }
      }
      break;

     case IN_measure_psiPM:
      measure_psiPM(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
      break;

     case IN_rotorInertiaEstimation:
      /* During 'rotorInertiaEstimation': '<S1>:337' */
      /* '<S1>:357:1' sf_internal_predicateOutput = counter == (wait_count+513); */
      qY = rtElectricalID_DW->wait_count + /*MW:OvSatOk*/ 513U;
      if (rtElectricalID_DW->wait_count + 513U < rtElectricalID_DW->wait_count)
      {
        qY = MAX_uint32_T;
      }

      if (rtElectricalID_DW->counter == qY) {
        /* Transition: '<S1>:357' */
        /* Exit 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:18' goertzel; */
        goertzel(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
        rtElectricalID_DW->is_ElectricalID = IN_endState;

        /* Entry 'endState': '<S1>:356' */
        /* '<S1>:356:4' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:356:5' ElectricalID_FOC_output.activeState = uint16(161); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 161U;

        /* '<S1>:356:6' ElectricalID_FOC_output.resetIntegrator=boolean(1); */
        rtElectricalID_Y->ElectricalID_FOC_output.resetIntegrator = true;

        /* '<S1>:356:7' ElectricalID_FOC_output.M_ref_FOC = single(0.0); */
        rtElectricalID_Y->ElectricalID_FOC_output.M_ref_FOC = 0.0F;
      } else {
        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Inport: '<Root>/ElectricalIDConfig'
         */
        /* '<S1>:337:10' ElectricalID_FOC_output.M_ref_FOC = SinusGenerator(ElectricalIDConfig.goertzlTorque,.... */
        /* '<S1>:337:11'     ElectricalIDConfig.goertzlFreq,GlobalConfig.sampleTimeISR); */
        rtElectricalID_Y->ElectricalID_FOC_output.M_ref_FOC = SinusGenerator
          (rtElectricalID_U->ElectricalIDConfig.goertzlTorque,
           rtElectricalID_U->ElectricalIDConfig.goertzlFreq,
           rtElectricalID_U->GlobalConfig_out.sampleTimeISR, rtElectricalID_DW);

        /* . */
        /* '<S1>:337:12' if(counter > wait_count && counter < (wait_count+501)) */
        qY = rtElectricalID_DW->wait_count + /*MW:OvSatOk*/ 501U;
        if (rtElectricalID_DW->wait_count + 501U < rtElectricalID_DW->wait_count)
        {
          qY = MAX_uint32_T;
        }

        if ((rtElectricalID_DW->counter > rtElectricalID_DW->wait_count) &&
            (rtElectricalID_DW->counter < qY)) {
          /* '<S1>:337:13' measArray1(counter-wait_count) = ActualValues.i_dq.q; */
          qY = rtElectricalID_DW->counter - /*MW:OvSatOk*/
            rtElectricalID_DW->wait_count;
          if (qY > rtElectricalID_DW->counter) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_DW->measArray1[(int32_T)qY - 1] =
            rtElectricalID_U->ActualValues.i_dq.q;

          /* '<S1>:337:14' i_est(counter-wait_count) = ActualValues.omega_m; */
          qY = rtElectricalID_DW->counter - /*MW:OvSatOk*/
            rtElectricalID_DW->wait_count;
          if (qY > rtElectricalID_DW->counter) {
            qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_DW->i_est[(int32_T)qY - 1] =
            rtElectricalID_U->ActualValues.omega_m;
        }

        /* '<S1>:337:16' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;

     case IN_stepResponse:
      stepResponse(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
      break;

     case IN_stepResponse_q:
      stepResponse_q(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
      break;

     case IN_stop:
      /* During 'stop': '<S1>:361' */
      /* '<S1>:362:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_DW->one_sec_transition_counter ==
          rtElectricalID_DW->counter) {
        /* Transition: '<S1>:362' */
        rtElectricalID_DW->is_ElectricalID = IN_rotorInertiaEstimation;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:3' ElectricalID_FOC_output.enableFOC_speed = boolean(0); */
        rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_speed = false;

        /* '<S1>:337:4' ElectricalID_FOC_output.enableFOC_torque = boolean(1); */
        rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_torque = true;

        /* '<S1>:337:5' counter = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:337:6' ElectricalID_FOC_output.resetIntegrator = boolean(0); */
        rtElectricalID_Y->ElectricalID_FOC_output.resetIntegrator = false;

        /* '<S1>:337:7' ElectricalID_FOC_output.activeState = uint16(160); */
        rtElectricalID_Y->ElectricalID_FOC_output.activeState = 160U;

        /* '<S1>:337:8' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        DutyCycle_filt = roundf(3.0F /
          rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
        if (DutyCycle_filt < 4.2949673E+9F) {
          if (DutyCycle_filt >= 0.0F) {
            rtElectricalID_DW->wait_count = (uint32_T)DutyCycle_filt;
          } else {
            rtElectricalID_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID_DW->wait_count = MAX_uint32_T;
        }
      } else {
        /* '<S1>:361:6' counter = counter +1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;

     default:
      /* During 'waitState': '<S1>:428' */
      /* '<S1>:905:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_DW->one_sec_transition_counter ==
          rtElectricalID_DW->counter) {
        /* Outport: '<Root>/finishedElectricalID' */
        /* Transition: '<S1>:905' */
        /* Exit 'waitState': '<S1>:428' */
        /* '<S1>:428:19' finishedElectricalID=boolean(1); */
        rtElectricalID_Y->finishedElectricalID = true;

        /* Outport: '<Root>/enteredElectricalID' */
        /* '<S1>:428:20' enteredElectricalID=boolean(0); */
        rtElectricalID_Y->enteredElectricalID = false;

        /* '<S1>:428:21' reset_FOC_output; */
        reset_FOC_output(rtElectricalID_Y);
        rtElectricalID_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
        rtElectricalID_DW->is_c3_ElectricalID = IN_Waiting;

        /* Entry 'Waiting': '<S1>:902' */
        /* wait for activation of */
        /* ElectricalID */
        /* donothing */
      } else {
        /* '<S1>:428:17' counter = counter + 1; */
        qY = rtElectricalID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_DW->counter + 1U < rtElectricalID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtElectricalID_DW->counter = qY;
      }
      break;
    }

    if (guard1) {
      DutyCycle_filt = roundf(0.5F /
        rtElectricalID_U->GlobalConfig_out.sampleTimeISR);
      if (DutyCycle_filt < 4.2949673E+9F) {
        if (DutyCycle_filt >= 0.0F) {
          qY = (uint32_T)DutyCycle_filt;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtElectricalID_DW->counter == qY) {
        /* '<S1>:789:22' elseif(counter == uint32(0.5/GlobalConfig.sampleTimeISR)) */
        /* '<S1>:789:23' DutyCycle_mod(abs(ia_sum*(GlobalConfig.sampleTimeISR/0.1))); */
        DutyCycle_mod_a(fabsf(rtElectricalID_DW->ia_sum *
                              (rtElectricalID_U->GlobalConfig_out.sampleTimeISR /
          0.1F)), rtElectricalID_U, rtElectricalID_DW);

        /* '<S1>:789:24' counter  = uint32(1); */
        rtElectricalID_DW->counter = 1U;

        /* '<S1>:789:25' ia_sum = single(0.0); */
        rtElectricalID_DW->ia_sum = 0.0F;
      }
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
}

/* Model step function */
void ElectricalID_step(RT_MODEL_ElectricalID_t *const rtElectricalID_M)
{
  DW_ElectricalID_t *rtElectricalID_DW = rtElectricalID_M->dwork;
  ExtU_ElectricalID_t *rtElectricalID_U = (ExtU_ElectricalID_t *)
    rtElectricalID_M->inputs;
  ExtY_ElectricalID_t *rtElectricalID_Y = (ExtY_ElectricalID_t *)
    rtElectricalID_M->outputs;

  /* Chart: '<Root>/ElectricalID' incorporates:
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/ElectricalIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
  /* Gateway: ElectricalID */
  /* During: ElectricalID */
  if (rtElectricalID_DW->is_active_c3_ElectricalID == 0U) {
    /* Entry: ElectricalID */
    rtElectricalID_DW->is_active_c3_ElectricalID = 1U;

    /* Entry Internal: ElectricalID */
    /* Transition: '<S1>:897' */
    rtElectricalID_DW->is_c3_ElectricalID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else if (rtElectricalID_DW->is_c3_ElectricalID == IN_ElectricalID) {
    ElectricalID_p(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);

    /* During 'Waiting': '<S1>:902' */
    /* '<S1>:899:1' sf_internal_predicateOutput = ControlFlags.startElectricalID==1 &&.... */
    /* '<S1>:899:2'  GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
  } else if (rtElectricalID_U->ControlFlags.startElectricalID &&
             (!rtElectricalID_U->GlobalConfig_out.Reset) &&
             rtElectricalID_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:899' */
    rtElectricalID_DW->is_c3_ElectricalID = IN_ElectricalID;

    /* Entry 'ElectricalID': '<S1>:761' */
    /* '<S1>:761:3' initParams; */
    initParams(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:761:4' ElectricalID_FOC_output.activeState = uint16(100); */
    /* '<S1>:761:5' enteredElectricalID=boolean(1); */
    rtElectricalID_Y->enteredElectricalID = true;

    /* Entry Internal 'ElectricalID': '<S1>:761' */
    /* Transition: '<S1>:243' */
    rtElectricalID_DW->is_ElectricalID = IN_evaluate_Turn_DC;

    /* Entry 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:3' ElectricalID_FOC_output.activeState = uint16(110); */
    rtElectricalID_Y->ElectricalID_FOC_output.activeState = 110U;

    /* '<S1>:379:4' counter = uint32(1); */
    rtElectricalID_DW->counter = 1U;

    /* '<S1>:379:5' omega_register=single(zeros(5,1)); */
    for (rtElectricalID_DW->i = 0; rtElectricalID_DW->i < 5;
         rtElectricalID_DW->i++) {
      rtElectricalID_DW->omega_register[rtElectricalID_DW->i] = 0.0F;
    }

    /* '<S1>:379:6' if(ElectricalIDConfig.dutyCyc > 0.0) */
    if (rtElectricalID_U->ElectricalIDConfig.dutyCyc > 0.0F) {
      /* Checks if a manual value for the DutyCycle was set */
      /* '<S1>:379:7' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
      rtElectricalID_DW->DutyCycle =
        rtElectricalID_U->ElectricalIDConfig.dutyCyc;

      /* '<S1>:379:8' DC_manual = boolean(1); */
      rtElectricalID_DW->DC_manual = true;
    } else {
      /* '<S1>:379:9' else */
      /* '<S1>:379:10' DutyCycle = single(0.01); */
      rtElectricalID_DW->DutyCycle = 0.01F;
    }

    /* '<S1>:914:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtElectricalID_U->GlobalConfig_out.Reset) {
    /* Transition: '<S1>:914' */
    /* '<S1>:914:2' finishedElectricalID=boolean(0); */
    /* '<S1>:914:3' enteredElectricalID=boolean(0); */
    /* '<S1>:914:4' initParams; */
    initParams(rtElectricalID_U, rtElectricalID_Y, rtElectricalID_DW);
    rtElectricalID_DW->is_c3_ElectricalID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  }

  /* End of Chart: '<Root>/ElectricalID' */
}

/* Model initialize function */
void ElectricalID_initialize(RT_MODEL_ElectricalID_t *const rtElectricalID_M)
{
  ExtY_ElectricalID_t *rtElectricalID_Y = (ExtY_ElectricalID_t *)
    rtElectricalID_M->outputs;

  /* SystemInitialize for Chart: '<Root>/ElectricalID' incorporates:
   *  Outport: '<Root>/ElectricalID_FOC_output'
   *  Outport: '<Root>/ElectricalID_output'
   */
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.M_ref_FOC = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.activeState = 0U;
  rtElectricalID_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_speed = false;
  rtElectricalID_Y->ElectricalID_FOC_output.enableFOC_current = false;
  rtElectricalID_Y->ElectricalID_FOC_output.resetIntegrator = false;
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_id_out = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_iq_out = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.Kp_n_out = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_id_out = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_iq_out = 0.0F;
  rtElectricalID_Y->ElectricalID_FOC_output.Ki_n_out = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_0 = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_2 = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PWM_Switch_4 = 0.0F;
  rtElectricalID_Y->ElectricalID_output.enable_TriState[0] = false;
  rtElectricalID_Y->ElectricalID_output.enable_TriState[1] = false;
  rtElectricalID_Y->ElectricalID_output.enable_TriState[2] = false;
  rtElectricalID_Y->ElectricalID_output.thetaOffset = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Ld_Henry = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Lq_Henry = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.polePairs = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared = 0.0F;
  rtElectricalID_Y->ElectricalID_output.PMSM_parameters.I_max_Ampere = 0.0F;

  /* '<S1>:922:7' sineCounter = uint32(0); */
  /* initialize */
  /* '<S1>:922:8' u = single(0); */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
