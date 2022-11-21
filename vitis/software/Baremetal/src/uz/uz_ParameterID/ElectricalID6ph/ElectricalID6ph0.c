/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID6ph0.c
 *
 * Code generated for Simulink model 'ElectricalID6ph0'.
 *
 * Model version                  : 2.679
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov 21 09:26:17 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "ElectricalID6ph0.h"

/* Named constants for Chart: '<S1>/ElectricalID6ph' */
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
#define IN_stepResponse1               ((uint8_T)12U)
#define IN_stepResponse_q              ((uint8_T)13U)
#define IN_stop                        ((uint8_T)14U)
#define IN_waitState                   ((uint8_T)15U)

extern real32_T rt_hypotf(real32_T u0, real32_T u1);

/* Forward declaration for local functions */
static void initParams(real32_T *R_est, real32_T *L_est, ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void reset_FOC_output(ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y);
static void resetParams_LM(real32_T *R_est, real32_T *L_est,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void enter_atomic_calculatePIcontrol(ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void RefreshDataRegister(DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void DutyCycle_mod(const real32_T om_reg_in[5], ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void TurnMotor(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
                      ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
                      DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void evaluate_Turn_DC(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
  ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y, DW_ElectricalID6ph0_t
  *rtElectricalID6ph0_DW);
static void DutyCycle_mod_d(real32_T ia_reg_in, ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void measure_psiPM(ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void goertzel(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
                     ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
                     DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void SetpVectorToDutyCycle6ph(uz_ParaID_ElectricalID6ph_output_t
  *ElectricalID_output_in, real32_T VDC, const real32_T SetpVector[6]);
static void VSD6ph(const real32_T b_VSD[36], real32_T abc_struct_a1, real32_T
                   abc_struct_b1, real32_T abc_struct_c1, real32_T abc_struct_a2,
                   real32_T abc_struct_b2, real32_T abc_struct_c2, real32_T
                   *out_alpha, real32_T *out_beta, real32_T *out_x, real32_T
                   *out_y, real32_T *out_z1, real32_T *out_z2,
                   DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void MeasureStepResponse(real32_T voltage, real32_T current,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void inv(const real32_T x[4], real32_T y[4]);
static void mtimes(const real32_T A[2048], const real32_T B[1024], real32_T C[2]);
static void LM_algorithm_Lq(real32_T *R_est, real32_T *L_est,
  ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U, DW_ElectricalID6ph0_t
  *rtElectricalID6ph0_DW);
static void stepResponse_q(real32_T *R_est, real32_T *L_est,
  ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t
  *rtElectricalID6ph0_Y, DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void exit_internal_ElectricalID(ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW);
static void ElectricalID(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
  ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y, DW_ElectricalID6ph0_t
  *rtElectricalID6ph0_DW);

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function initParams
 * This is used instead of "after(1.0,sec) to ensure the same transition time
 * independelty of the sampletime in the c-code
 */
static void initParams(real32_T *R_est, real32_T *L_est, ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  real32_T tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'initParams': '<S2>:88' */
  /* '<S2>:88:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F / rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtElectricalID6ph0_DW->one_sec_transition_counter = (uint32_T)tmp;
    } else {
      rtElectricalID6ph0_DW->one_sec_transition_counter = 0U;
    }
  } else {
    rtElectricalID6ph0_DW->one_sec_transition_counter = MAX_uint32_T;
  }

  /*  initialize variables */
  /* '<S2>:88:7' Ki_n_loc            = single(0.0); */
  /* '<S2>:88:8' Kp_n_loc            = single(0.0); */
  /* '<S2>:88:9' n_filt              = single(0.0); */
  /* '<S2>:88:10' n_ref_old           = single(0.0); */
  /* '<S2>:88:11' repetitionCounter   = uint32(0); */
  /* '<S2>:88:12' dutyCycAdj          = single(0.0); */
  /* '<S2>:88:13' counter 			= uint32(1); */
  rtElectricalID6ph0_DW->counter = 1U;

  /* '<S2>:88:14' Kp_iq_loc           = single(0.0); */
  rtElectricalID6ph0_DW->Kp_iq_loc = 0.0F;

  /* '<S2>:88:15' Ki_iq_loc           = single(0.0); */
  /* '<S2>:88:16' Kp_id_loc           = single(0.0); */
  /* '<S2>:88:17' Ki_id_loc           = single(0.0); */
  /* '<S2>:88:18' DutyCycle_filt      = single(0.0); */
  /* '<S2>:88:19' measArray1			= single(zeros(1024,1)); */
  memset(&rtElectricalID6ph0_DW->measArray1[0], 0, sizeof(real32_T) << 10U);

  /* '<S2>:88:20' meas_sum            = single(zeros(2,1)); */
  /* used for Friction Id */
  /* '<S2>:88:21' J2                  = single(zeros(256,5)); */
  /* '<S2>:88:22' thetaOffset         = single(0.0); */
  /* '<S2>:88:23' Vstep               = single(zeros(205,1)); */
  memset(&rtElectricalID6ph0_DW->Vstep[0], 0, 205U * sizeof(real32_T));

  /* '<S2>:88:24' DutyCycle           = single(0.0); */
  rtElectricalID6ph0_DW->DutyCycle = 0.0F;

  /* '<S2>:88:25' omega_sum           = single(0); */
  rtElectricalID6ph0_DW->omega_sum = 0.0F;

  /* '<S2>:88:26' om_con              = boolean(0); */
  rtElectricalID6ph0_DW->om_con = false;

  /* '<S2>:88:27' ia_sum              = single(0); */
  rtElectricalID6ph0_DW->ia_sum = 0.0F;

  /* '<S2>:88:28' ia_valid            = boolean(0); */
  rtElectricalID6ph0_DW->ia_valid = false;

  /* '<S2>:88:29' DC_manual           = boolean(0); */
  rtElectricalID6ph0_DW->DC_manual = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Outputs */
  /* '<S2>:88:32' ElectricalID_FOC_output.Ki_n_out                    = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_n_out = 0.0F;

  /* '<S2>:88:33' ElectricalID_FOC_output.Ki_iq_out                   = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_iq_out = 0.0F;

  /* '<S2>:88:34' ElectricalID_FOC_output.Ki_id_out                   = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_id_out = 0.0F;

  /* '<S2>:88:35' ElectricalID_FOC_output.Kp_n_out                    = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_n_out = 0.0F;

  /* '<S2>:88:36' ElectricalID_FOC_output.Kp_iq_out                   = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_iq_out = 0.0F;

  /* '<S2>:88:37' ElectricalID_FOC_output.Kp_id_out                   = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_id_out = 0.0F;

  /* '<S2>:88:38' ElectricalID_FOC_output.n_ref_FOC                   = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S2>:88:39' ElectricalID_FOC_output.i_dq_ref.d                  = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S2>:88:40' ElectricalID_FOC_output.i_dq_ref.q                  = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S2>:88:41' ElectricalID_FOC_output.i_dq_ref.zero               = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S2>:88:42' ElectricalID_FOC_output.enableFOC_speed             = boolean(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S2>:88:43' ElectricalID_FOC_output.enableFOC_current           = boolean(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_current = false;

  /* '<S2>:88:44' ElectricalID_FOC_output.resetIntegrator             = boolean(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.resetIntegrator = false;

  /* Outport: '<Root>/finishedElectricalID' */
  /* '<S2>:88:45' ElectricalID_FOC_output.activeState                 = uint16(0); */
  /* '<S2>:88:46' finishedElectricalID= boolean(0); */
  rtElectricalID6ph0_Y->finishedElectricalID = false;

  /* Outport: '<Root>/ElectricalID_output' */
  /* '<S2>:88:48' ElectricalID_output.PWM_Switch_a1                        = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;

  /* '<S2>:88:49' ElectricalID_output.PWM_Switch_b1                        = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;

  /* '<S2>:88:50' ElectricalID_output.PWM_Switch_c1                        = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

  /* '<S2>:88:51' ElectricalID_output.PWM_Switch_a2                        = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;

  /* '<S2>:88:52' ElectricalID_output.PWM_Switch_b2                        = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;

  /* '<S2>:88:53' ElectricalID_output.PWM_Switch_c2                        = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;

  /* '<S2>:88:54' ElectricalID_output.enable_TriState                     = boolean(zeros(1,3)); */
  rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[0] = false;
  rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[1] = false;
  rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[2] = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* 0 = TriState off, 1 = TriState on    */
  /* '<S2>:88:55' ElectricalID_FOC_output.activeState                     = uint16(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 0U;

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S2>:88:56' ElectricalID_output.thetaOffset                         = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.thetaOffset = 0.0F;

  /* '<S2>:88:57' ElectricalID_output.PMSM_parameters.R_ph_Ohm            = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm = 0.0F;

  /* '<S2>:88:58' ElectricalID_output.PMSM_parameters.Ld_Henry            = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Ld_Henry = 0.0F;

  /* '<S2>:88:59' ElectricalID_output.PMSM_parameters.Lq_Henry            = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry = 0.0F;

  /* '<S2>:88:60' ElectricalID_output.PMSM_parameters.Psi_PM_Vs           = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs = 0.0F;

  /* '<S2>:88:61' ElectricalID_output.PMSM_parameters.polePairs           = GlobalConfig.PMSM_config.polePairs; */
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.polePairs =
    rtElectricalID6ph0_U->GlobalConfig_out.PMSM_config.polePairs;

  /* '<S2>:88:62' ElectricalID_output.PMSM_parameters.J_kg_m_squared      = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared =
    0.0F;

  /* Outport: '<Root>/enteredElectricalID' */
  /* '<S2>:88:63' enteredElectricalID                                     = boolean(0); */
  rtElectricalID6ph0_Y->enteredElectricalID = false;

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S2>:88:66' d        			= single(zeros(2048,1)); */
  /* '<S2>:88:67' dp      			= single(zeros(2,1)); */
  /* '<S2>:88:68' e       			= single(0); */
  rtElectricalID6ph0_DW->e = 0.0F;

  /* '<S2>:88:69' e_lm  				= single(0); */
  /* '<S2>:88:70' H 					= single(zeros(2,2)); */
  rtElectricalID6ph0_DW->H[0] = 0.0F;
  rtElectricalID6ph0_DW->H[1] = 0.0F;
  rtElectricalID6ph0_DW->H[2] = 0.0F;
  rtElectricalID6ph0_DW->H[3] = 0.0F;

  /* '<S2>:88:71' i_est 				= single(zeros(2048,1)); */
  memset(&rtElectricalID6ph0_DW->d[0], 0, sizeof(real32_T) << 11U);
  memset(&rtElectricalID6ph0_DW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S2>:88:72' it 					= uint16(0); */
  /* '<S2>:88:73' J 					= single(zeros(2048,2)); */
  memset(&rtElectricalID6ph0_DW->J[0], 0, sizeof(real32_T) << 12U);

  /* '<S2>:88:74' k 					= single(0); */
  /* '<S2>:88:75' L0 					= single(0); */
  /* '<S2>:88:76' L_est   			= single(0); */
  *L_est = 0.0F;

  /* '<S2>:88:77' L_lm 				= single(0); */
  /* '<S2>:88:78' Ndata  				= uint16(512); */
  /* '<S2>:88:79' Nparams 			= uint16(2); */
  /* '<S2>:88:80' n_iters 			= uint16(100); */
  rtElectricalID6ph0_DW->n_iters = 100U;

  /* '<S2>:88:81' R0 					= single(0); */
  /* '<S2>:88:82' R_est 				= single(0); */
  *R_est = 0.0F;

  /* '<S2>:88:83' R_lm 				= single(0); */
  /* '<S2>:88:84' V0 					= single(0); */
  rtElectricalID6ph0_DW->V0 = 0.0F;

  /* '<S2>:88:85' lambda  			= single(0.01); */
  rtElectricalID6ph0_DW->lambda = 0.01F;

  /* '<S2>:88:86' updateJ 			= boolean(1); */
  rtElectricalID6ph0_DW->updateJ = true;

  /*  initialize varaibles for PMSM parameters */
  /* '<S2>:88:89' R_corr              = single(0.000); */
  rtElectricalID6ph0_DW->R_corr = 0.0F;

  /* 0.060 */
  /*  variables for controller calculation */
  /* '<S2>:88:92' bandwidthCurrentControl = single(1000); */
  rtElectricalID6ph0_DW->bandwidthCurrentControl = 1000.0F;

  /* '<S2>:88:93' dampingFactor           = single(10.0); */
  rtElectricalID6ph0_DW->dampingFactor = 10.0F;

  /* '<S2>:88:94' psiOverJ                = single(5000); */
  rtElectricalID6ph0_DW->psiOverJ = 5000.0F;
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function reset_FOC_output
 * Outputs
 */
static void reset_FOC_output(ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y)
{
  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* MATLAB Function 'reset_FOC_output': '<S2>:920' */
  /* '<S2>:920:4' ElectricalID_FOC_output.n_ref_FOC           = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S2>:920:5' ElectricalID_FOC_output.i_dq_ref.d          = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S2>:920:6' ElectricalID_FOC_output.i_dq_ref.q          = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S2>:920:7' ElectricalID_FOC_output.i_dq_ref.zero       = single(0.0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S2>:920:8' ElectricalID_FOC_output.enableFOC_speed     = boolean(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S2>:920:9' ElectricalID_FOC_output.enableFOC_current   = boolean(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_current = false;

  /* '<S2>:920:10' ElectricalID_FOC_output.resetIntegrator     = boolean(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.resetIntegrator = false;

  /* '<S2>:920:11' ElectricalID_FOC_output.activeState         = uint16(0); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 0U;

  /* '<S2>:920:12' TwoMassID_FOC_output.Kp_id_out              = single(Kp_id_loc); */
  /* '<S2>:920:13' TwoMassID_FOC_output.Kp_iq_out              = single(Kp_iq_loc); */
  /* '<S2>:920:14' TwoMassID_FOC_output.Kp_n_out               = single(Kp_n_loc); */
  /* '<S2>:920:15' TwoMassID_FOC_output.Ki_id_out              = single(Ki_id_loc); */
  /* '<S2>:920:16' TwoMassID_FOC_output.Ki_iq_out              = single(Ki_iq_loc); */
  /* '<S2>:920:17' TwoMassID_FOC_output.Ki_n_out               = single(Ki_n_loc); */
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function resetParams_LM
 *  reset variables
 */
static void resetParams_LM(real32_T *R_est, real32_T *L_est,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  /* MATLAB Function 'resetParams_LM': '<S2>:283' */
  /* '<S2>:283:4' measArray1			= single(zeros(1024,1)); */
  memset(&rtElectricalID6ph0_DW->measArray1[0], 0, sizeof(real32_T) << 10U);

  /* '<S2>:283:5' Vstep               = single(zeros(205,1)); */
  memset(&rtElectricalID6ph0_DW->Vstep[0], 0, 205U * sizeof(real32_T));

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S2>:283:8' d        			= single(zeros(2048,1)); */
  /* '<S2>:283:9' dp      			= single(zeros(2,1)); */
  /* '<S2>:283:10' e       			= single(0); */
  rtElectricalID6ph0_DW->e = 0.0F;

  /* '<S2>:283:11' e_lm  				= single(0); */
  /* '<S2>:283:12' H 					= single(zeros(2,2)); */
  rtElectricalID6ph0_DW->H[0] = 0.0F;
  rtElectricalID6ph0_DW->H[1] = 0.0F;
  rtElectricalID6ph0_DW->H[2] = 0.0F;
  rtElectricalID6ph0_DW->H[3] = 0.0F;

  /* '<S2>:283:13' i_est 				= single(zeros(2048,1)); */
  memset(&rtElectricalID6ph0_DW->d[0], 0, sizeof(real32_T) << 11U);
  memset(&rtElectricalID6ph0_DW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S2>:283:14' it 					= uint16(0); */
  /* '<S2>:283:15' J 					= single(zeros(2048,2)); */
  memset(&rtElectricalID6ph0_DW->J[0], 0, sizeof(real32_T) << 12U);

  /* '<S2>:283:16' k 					= single(0); */
  /* '<S2>:283:17' L0 					= single(0); */
  /* '<S2>:283:18' L_est   			= single(0); */
  *L_est = 0.0F;

  /* '<S2>:283:19' L_lm 				= single(0); */
  /* '<S2>:283:20' Ndata  				= uint16(512); */
  /* '<S2>:283:21' Nparams 			= uint16(2); */
  /* '<S2>:283:22' n_iters 			= uint16(100); */
  rtElectricalID6ph0_DW->n_iters = 100U;

  /* '<S2>:283:23' R0 					= single(0); */
  /* '<S2>:283:24' R_est 				= single(0); */
  *R_est = 0.0F;

  /* '<S2>:283:25' R_lm 				= single(0); */
  /* '<S2>:283:26' V0 					= single(0); */
  rtElectricalID6ph0_DW->V0 = 0.0F;

  /* '<S2>:283:27' lambda  			= single(0.01); */
  rtElectricalID6ph0_DW->lambda = 0.01F;

  /* '<S2>:283:28' updateJ 			= boolean(1); */
  rtElectricalID6ph0_DW->updateJ = true;

  /* L_d                 = single(0); */
  /* R_s                 = single(0); */
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
static void enter_atomic_calculatePIcontrol(ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  real32_T Ki_id_loc;
  real32_T Kp_id_loc;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Entry 'calculatePIcontroller': '<S2>:284' */
  /* state6.0 */
  /* '<S2>:284:4' ElectricalID_FOC_output.activeState = uint16(144); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 144U;

  /* Outport: '<Root>/ElectricalID_output' */
  /*  calculation according to TI instaSpin */
  /* '<S2>:284:6' Kp_id_loc = ElectricalID_output.PMSM_parameters.Ld_Henry * bandwidthCurrentControl; */
  Kp_id_loc = rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Ld_Henry
    * rtElectricalID6ph0_DW->bandwidthCurrentControl;

  /* '<S2>:284:7' Ki_id_loc = ElectricalID_output.PMSM_parameters.R_ph_Ohm * bandwidthCurrentControl; */
  Ki_id_loc = rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm
    * rtElectricalID6ph0_DW->bandwidthCurrentControl;

  /* '<S2>:284:8' Ki_iq_loc = Ki_id_loc; */
  /* '<S2>:284:9' if (ElectricalIDConfig.identLq == 1) */
  if (rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.identLq) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S2>:284:10' Kp_iq_loc = ElectricalID_output.PMSM_parameters.Lq_Henry * bandwidthCurrentControl; */
    rtElectricalID6ph0_DW->Kp_iq_loc =
      rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
      rtElectricalID6ph0_DW->bandwidthCurrentControl;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S2>:284:11' elseif (ElectricalIDConfig.identLq == 0) */
    /* '<S2>:284:12' ElectricalID_output.PMSM_parameters.Lq_Henry = .... */
    /* '<S2>:284:13'         ElectricalID_output.PMSM_parameters.Ld_Henry; */
    rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry =
      rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Ld_Henry;

    /* . */
    /* '<S2>:284:14' Kp_iq_loc = Kp_id_loc; */
    rtElectricalID6ph0_DW->Kp_iq_loc = Kp_id_loc;
  }

  /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/ElectricalID_output'
   */
  /* '<S2>:284:16' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.PMSM_parameters.Lq_Henry*dampingFactor*.... */
  /* '<S2>:284:17'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*psiOverJ); */
  /* . */
  /* '<S2>:284:18' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.PMSM_parameters.Lq_Henry *.... */
  /* '<S2>:284:19'     ElectricalID_output.PMSM_parameters.Lq_Henry  * dampingFactor * dampingFactor * .... */
  /* '<S2>:284:20'     dampingFactor * GlobalConfig.PMSM_config.polePairs... */
  /* '<S2>:284:21'     *3.0/2.0*psiOverJ); */
  /* . */
  /* . */
  /* Output calculated values */
  /* '<S2>:284:23' ElectricalID_FOC_output.Kp_id_out = Kp_id_loc; */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_id_out = Kp_id_loc;

  /* '<S2>:284:24' ElectricalID_FOC_output.Ki_id_out = Ki_id_loc; */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_id_out = Ki_id_loc;

  /* '<S2>:284:25' ElectricalID_FOC_output.Kp_iq_out = Kp_iq_loc; */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_iq_out =
    rtElectricalID6ph0_DW->Kp_iq_loc;

  /* '<S2>:284:26' ElectricalID_FOC_output.Ki_iq_out = Ki_iq_loc; */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_iq_out = Ki_id_loc;

  /* '<S2>:284:27' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_n_out =
    rtElectricalID6ph0_DW->Kp_iq_loc /
    (rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
     rtElectricalID6ph0_DW->dampingFactor *
     rtElectricalID6ph0_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F / 2.0F *
     rtElectricalID6ph0_DW->psiOverJ);

  /* '<S2>:284:28' ElectricalID_FOC_output.Ki_n_out = single(Ki_n_loc); */
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_n_out =
    rtElectricalID6ph0_DW->Kp_iq_loc * rtElectricalID6ph0_DW->Kp_iq_loc /
    (rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
     rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
     rtElectricalID6ph0_DW->dampingFactor * rtElectricalID6ph0_DW->dampingFactor
     * rtElectricalID6ph0_DW->dampingFactor *
     rtElectricalID6ph0_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F / 2.0F *
     rtElectricalID6ph0_DW->psiOverJ);
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  /* MATLAB Function 'RefreshDataRegister': '<S2>:784' */
  /* '<S2>:784:3' m=length(omega_register); */
  /* '<S2>:784:4' for k= single(0):single(m-2) */
  /* '<S2>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID6ph0_DW->omega_register[4] =
    rtElectricalID6ph0_DW->omega_register[3];

  /* '<S2>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID6ph0_DW->omega_register[3] =
    rtElectricalID6ph0_DW->omega_register[2];

  /* '<S2>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID6ph0_DW->omega_register[2] =
    rtElectricalID6ph0_DW->omega_register[1];

  /* '<S2>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID6ph0_DW->omega_register[1] =
    rtElectricalID6ph0_DW->omega_register[0];
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function DutyCycle_mod(om_reg_in)
 */
static void DutyCycle_mod(const real32_T om_reg_in[5], ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  real32_T ex;
  real32_T mean_om_reg;
  real32_T tmp;

  /* MATLAB Function 'DutyCycle_mod': '<S2>:769' */
  /* '<S2>:769:2' mean_om_reg=mean(om_reg_in); */
  mean_om_reg = ((((om_reg_in[0] + om_reg_in[1]) + om_reg_in[2]) + om_reg_in[3])
                 + om_reg_in[4]) / 5.0F;

  /* if no manual value for the DutyCycle is set, this function determines, if the rotor is turning above */
  /* the stated minimal speed and the oscillation is below */
  /* the stated threshold */
  /* '<S2>:769:7' if(om_con==0) */
  if (!rtElectricalID6ph0_DW->om_con) {
    /* Inport: '<Root>/GlobalConfig' */
    /* '<S2>:769:8' if(mean_om_reg >(ElectricalIDConfig.min_n_ratio*GlobalConfig.ratSpeed*2*pi)/60) */
    if (mean_om_reg >
        rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.min_n_ratio *
        rtElectricalID6ph0_U->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F /
        60.0F) {
      /* minimal speed in rad/sec */
      /* determines if the oscillation is below the stated threshold */
      /* (currently 5% of rated speed) */
      /* '<S2>:769:12' if((mean_om_reg+(0.05*(GlobalConfig.ratSpeed*2*pi)/60))>=max(om_reg_in)&& ... */
      /* '<S2>:769:13'              (mean_om_reg-(0.05*(GlobalConfig.ratSpeed*2*pi)/60))<=min(om_reg_in)&&min(om_reg_in)~=0) */
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

      tmp = rtElectricalID6ph0_U->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F
        * 0.05F / 60.0F;
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
            /* '<S2>:769:15' om_con=boolean(1); */
            rtElectricalID6ph0_DW->om_con = true;
          } else {
            /* '<S2>:769:16' else */
            /* '<S2>:769:17' om_con=boolean(0); */
            rtElectricalID6ph0_DW->om_con = false;
          }
        } else {
          /* '<S2>:769:16' else */
          /* '<S2>:769:17' om_con=boolean(0); */
          rtElectricalID6ph0_DW->om_con = false;
        }
      } else {
        /* '<S2>:769:16' else */
        /* '<S2>:769:17' om_con=boolean(0); */
        rtElectricalID6ph0_DW->om_con = false;
      }
    } else {
      /* '<S2>:769:19' else */
      /* '<S2>:769:20' om_con=boolean(0); */
      rtElectricalID6ph0_DW->om_con = false;
    }

    /* End of Inport: '<Root>/GlobalConfig' */
  }

  if (!rtElectricalID6ph0_DW->om_con) {
    /* Increases the DutyCycle by 1% every 2 seconds, if the motor isn't */
    /* rotating properly */
    /* '<S2>:769:26' DutyCycle = DutyCycle + 0.01; */
    rtElectricalID6ph0_DW->DutyCycle += 0.01F;

    /* Simulation 0.001 | Real 0.01 */
  }

  /* '<S2>:769:23' if(om_con == 0) */
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function TurnMotor
 */
static void TurnMotor(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
                      ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
                      DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  real32_T ElectricalID_output_tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'TurnMotor': '<S2>:380' */
  /* '<S2>:380:3' sineCounter = single(counter); */
  /* '<S2>:380:4' gamma=pi/6; */
  /*  rechtslauf */
  /* '<S2>:380:7' ElectricalID_output.PWM_Switch_a1 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2)+0.5; */
  ElectricalID_output_tmp = 50.2654839F * (real32_T)
    rtElectricalID6ph0_DW->counter *
    rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR;

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = sinf
    (ElectricalID_output_tmp + 1.57079637F) * (0.5F *
    rtElectricalID6ph0_DW->DutyCycle) + 0.5F;

  /* '<S2>:380:8' ElectricalID_output.PWM_Switch_b1 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2)+0.5; */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = sinf
    ((ElectricalID_output_tmp - 2.09439516F) + 1.57079637F) * (0.5F *
    rtElectricalID6ph0_DW->DutyCycle) + 0.5F;

  /* '<S2>:380:9' ElectricalID_output.PWM_Switch_c1 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-4*pi/3+pi/2)+0.5; */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = sinf
    ((ElectricalID_output_tmp - 4.18879032F) + 1.57079637F) * (0.5F *
    rtElectricalID6ph0_DW->DutyCycle) + 0.5F;

  /* '<S2>:380:10' ElectricalID_output.PWM_Switch_a2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2-gamma)+0.5; */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = sinf((50.2654839F *
    (real32_T)rtElectricalID6ph0_DW->counter *
    rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR + 1.57079637F) -
    0.52359879F) * (0.5F * rtElectricalID6ph0_DW->DutyCycle) + 0.5F;

  /* '<S2>:380:11' ElectricalID_output.PWM_Switch_b2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2-gamma)+0.5; */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = sinf(((50.2654839F *
    (real32_T)rtElectricalID6ph0_DW->counter *
    rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR - 2.09439516F) +
    1.57079637F) - 0.52359879F) * (0.5F * rtElectricalID6ph0_DW->DutyCycle) +
    0.5F;

  /* '<S2>:380:12' ElectricalID_output.PWM_Switch_c2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-4*pi/3+pi/2-gamma)+0.5; */
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = sinf(((50.2654839F *
    (real32_T)rtElectricalID6ph0_DW->counter *
    rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR - 4.18879032F) +
    1.57079637F) - 0.52359879F) * (0.5F * rtElectricalID6ph0_DW->DutyCycle) +
    0.5F;

  /*  linkslauf */
  /*  ElectricalID_output.PWM_Switch_0 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2); */
  /*  ElectricalID_output.PWM_Switch_2 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+2*pi/3+pi/2); */
  /*  ElectricalID_output.PWM_Switch_4 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2); */
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
static void evaluate_Turn_DC(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
  ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y, DW_ElectricalID6ph0_t
  *rtElectricalID6ph0_DW)
{
  int32_T k;
  real32_T c_y[5];
  real32_T tmp;
  uint32_T y;

  /* During 'evaluate_Turn_DC': '<S2>:379' */
  /* '<S2>:383:1' sf_internal_predicateOutput = om_con==1; */
  if (rtElectricalID6ph0_DW->om_con || rtElectricalID6ph0_DW->DC_manual) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* Transition: '<S2>:383' */
    /* Transition: '<S2>:921' */
    /* Exit 'evaluate_Turn_DC': '<S2>:379' */
    /* '<S2>:379:27' ElectricalID_output.PWM_Switch_a1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;

    /* '<S2>:379:28' ElectricalID_output.PWM_Switch_b1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;

    /* '<S2>:379:29' ElectricalID_output.PWM_Switch_c1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

    /* '<S2>:379:30' ElectricalID_output.PWM_Switch_a2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;

    /* '<S2>:379:31' ElectricalID_output.PWM_Switch_b2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;

    /* '<S2>:379:32' ElectricalID_output.PWM_Switch_c2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_alignRotor_d_on;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'alignRotor_d_on': '<S2>:3' */
    /* '<S2>:3:4' ElectricalID_FOC_output.activeState = uint16(120); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 120U;

    /* '<S2>:3:5' counter = uint32(1); */
    rtElectricalID6ph0_DW->counter = 1U;
  } else {
    /* '<S2>:921:1' sf_internal_predicateOutput = DC_manual == 1; */
    /* '<S2>:379:13' if(DC_manual == 0) */
    if (!rtElectricalID6ph0_DW->DC_manual) {
      /* averages the last 0.1s */
      /* '<S2>:379:14' omega_sum=omega_sum+single(ActualValues.omega_m); */
      rtElectricalID6ph0_DW->omega_sum +=
        rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.omega_m;

      /* Inport: '<Root>/GlobalConfig' */
      /* '<S2>:379:15' if(mod(counter,uint32(0.1/GlobalConfig.sampleTimeISR))==0) */
      tmp = roundf(0.1F / rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
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
        y = rtElectricalID6ph0_DW->counter;
      } else {
        y = rtElectricalID6ph0_DW->counter - rtElectricalID6ph0_DW->counter / y *
          y;
      }

      if (y == 0U) {
        /* '<S2>:379:16' RefreshDataRegister; */
        RefreshDataRegister(rtElectricalID6ph0_DW);

        /* Inport: '<Root>/GlobalConfig' */
        /* '<S2>:379:17' omega_register(1,1)=omega_sum*(GlobalConfig.sampleTimeISR/0.1); */
        rtElectricalID6ph0_DW->omega_register[0] =
          rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR / 0.1F *
          rtElectricalID6ph0_DW->omega_sum;

        /* '<S2>:379:18' omega_sum=single(0); */
        rtElectricalID6ph0_DW->omega_sum = 0.0F;
      }

      /* Inport: '<Root>/GlobalConfig' */
      /* '<S2>:379:20' if(mod(counter,uint32(2/GlobalConfig.sampleTimeISR))==0) */
      tmp = roundf(2.0F / rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
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
        y = rtElectricalID6ph0_DW->counter;
      } else {
        y = rtElectricalID6ph0_DW->counter - rtElectricalID6ph0_DW->counter / y *
          y;
      }

      if (y == 0U) {
        /* after 2s omega will be evaluated */
        /* '<S2>:379:21' DutyCycle_mod(abs(omega_register)); */
        for (k = 0; k < 5; k++) {
          c_y[k] = fabsf(rtElectricalID6ph0_DW->omega_register[k]);
        }

        DutyCycle_mod(c_y, rtElectricalID6ph0_U, rtElectricalID6ph0_DW);
      }
    }

    /* '<S2>:379:24' counter = counter + 1; */
    y = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
    if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter) {
      y = MAX_uint32_T;
    }

    rtElectricalID6ph0_DW->counter = y;

    /* '<S2>:379:25' TurnMotor; */
    TurnMotor(rtElectricalID6ph0_U, rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function DutyCycle_mod(ia_reg_in)
 */
static void DutyCycle_mod_d(real32_T ia_reg_in, ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'DutyCycle_mod': '<S2>:796' */
  /* '<S2>:796:3' mean_ia_reg=mean(ia_reg_in); */
  /* determines if the mean value is below the step-response current limit */
  /* '<S2>:796:5' if(mean_ia_reg < 0.5*GlobalConfig.ratCurrent) */
  if (ia_reg_in < 0.5F * rtElectricalID6ph0_U->GlobalConfig_out.ratCurrent) {
    /* Current limit for step response   */
    /* '<S2>:796:6' ia_valid=boolean(0); */
    rtElectricalID6ph0_DW->ia_valid = false;
  } else {
    /* '<S2>:796:7' else */
    /* '<S2>:796:8' ia_valid=boolean(1); */
    rtElectricalID6ph0_DW->ia_valid = true;
  }

  /* End of Inport: '<Root>/GlobalConfig' */
  /* '<S2>:796:11' if(ia_valid == 0) */
  if (!rtElectricalID6ph0_DW->ia_valid) {
    /* Increases the DutyCycle by 0.5% every 0.5 second, if the step response */
    /* is below the current limit */
    /* '<S2>:796:14' DutyCycle = DutyCycle + 0.005; */
    rtElectricalID6ph0_DW->DutyCycle += 0.005F;

    /* Simulation 0.001 | Real 0.005 */
  }
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
static void measure_psiPM(ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  int32_T k;
  real32_T b_x;
  real32_T c_x;
  real32_T x;
  uint32_T qY;
  uint32_T qY_tmp;
  uint32_T qY_tmp_tmp;

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
  /* During 'measure_psiPM': '<S2>:405' */
  /* '<S2>:406:1' sf_internal_predicateOutput = ElectricalID_output.PMSM_parameters.Psi_PM_Vs > 0; */
  if (rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs > 0.0F)
  {
    /* Transition: '<S2>:406' */
    /* Exit 'measure_psiPM': '<S2>:405' */
    /* '<S2>:405:20' counter = uint32(1); */
    rtElectricalID6ph0_DW->counter = 1U;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_stop;

    /* Entry 'stop': '<S2>:361' */
    /* state 10.1 */
    /* '<S2>:361:3' ElectricalID_FOC_output.activeState = uint16(151); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 151U;

    /* '<S2>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

    /* '<S2>:361:5' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.resetIntegrator = true;
  } else {
    /* '<S2>:405:9' if(counter > wait_count && counter < (wait_count+1025)) */
    qY = rtElectricalID6ph0_DW->wait_count + 1025U;
    if (rtElectricalID6ph0_DW->wait_count + 1025U <
        rtElectricalID6ph0_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if ((rtElectricalID6ph0_DW->counter > rtElectricalID6ph0_DW->wait_count) &&
        (rtElectricalID6ph0_DW->counter < qY)) {
      /* '<S2>:405:10' measArray1(counter-wait_count) = ActualValues.v_dq.q; */
      qY_tmp_tmp = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/
        rtElectricalID6ph0_DW->wait_count;
      qY_tmp = qY_tmp_tmp;
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID6ph0_DW->counter) {
        qY = 0U;
        qY_tmp = 0U;
      }

      rtElectricalID6ph0_DW->measArray1[(int32_T)qY - 1] =
        rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.q;

      /* '<S2>:405:11' d(counter-wait_count) = ActualValues.i_dq.q; */
      rtElectricalID6ph0_DW->d[(int32_T)qY_tmp - 1] =
        rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.q;

      /* '<S2>:405:12' i_est(counter-wait_count) = ActualValues.omega_el; */
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID6ph0_DW->counter) {
        qY = 0U;
      }

      rtElectricalID6ph0_DW->i_est[(int32_T)qY - 1] =
        rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.omega_el;
    }

    /* '<S2>:405:14' if(counter == (wait_count+1025)) */
    qY = rtElectricalID6ph0_DW->wait_count + 1025U;
    if (rtElectricalID6ph0_DW->wait_count + 1025U <
        rtElectricalID6ph0_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if (rtElectricalID6ph0_DW->counter == qY) {
      /* '<S2>:405:15' ElectricalID_output.PMSM_parameters.Psi_PM_Vs = (mean(measArray1(1:1024))-mean(d(1:1024))*.... */
      /* '<S2>:405:16'         ElectricalID_output.PMSM_parameters.R_ph_Ohm)/(mean(i_est(1:1024))); */
      x = rtElectricalID6ph0_DW->measArray1[0];
      b_x = rtElectricalID6ph0_DW->d[0];
      c_x = rtElectricalID6ph0_DW->i_est[0];
      for (k = 0; k < 1023; k++) {
        x += rtElectricalID6ph0_DW->measArray1[k + 1];
        b_x += rtElectricalID6ph0_DW->d[k + 1];
        c_x += rtElectricalID6ph0_DW->i_est[k + 1];
      }

      rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs = (x /
        1024.0F - b_x / 1024.0F *
        rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm) /
        (c_x / 1024.0F);

      /* . */
    }

    /* '<S2>:405:18' counter = counter + 1; */
    qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
    if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter) {
      qY = MAX_uint32_T;
    }

    rtElectricalID6ph0_DW->counter = qY;
  }

  /* End of Outport: '<Root>/ElectricalID_output' */
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function y = SinusGenerator(Amp, Freq, sampleTime)
 */
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  real32_T tmp;
  real32_T x;
  uint32_T qY;

  /* MATLAB Function 'SinusGenerator': '<S2>:922' */
  /* '<S2>:922:6' if isempty(sineCounter) */
  /* '<S2>:922:10' u = single(Amp*sin(2*pi*single(Freq)*single(sineCounter)*sampleTime)); */
  x = 6.28318548F * Freq * (real32_T)rtElectricalID6ph0_DW->sineCounter *
    sampleTime;

  /* '<S2>:922:11' sineCounter = sineCounter + 1; */
  qY = rtElectricalID6ph0_DW->sineCounter + /*MW:OvSatOk*/ 1U;
  if (rtElectricalID6ph0_DW->sineCounter + 1U <
      rtElectricalID6ph0_DW->sineCounter) {
    qY = MAX_uint32_T;
  }

  rtElectricalID6ph0_DW->sineCounter = qY;

  /* '<S2>:922:12' if(sineCounter == uint32(1/(single(Freq)*sampleTime))) */
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

  if (rtElectricalID6ph0_DW->sineCounter == qY) {
    /* '<S2>:922:13' sineCounter = uint32(0); */
    rtElectricalID6ph0_DW->sineCounter = 0U;
  }

  /* '<S2>:922:17' y = single(u); */
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
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function goertzel
 *  goertzel algorithm for J calculation
 */
static void goertzel(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
                     ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
                     DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
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

  /* MATLAB Function 'goertzel': '<S2>:350' */
  /*  calculate momentum from i_q */
  /* '<S2>:350:6' for k=single(1):single(500) */
  for (k = 0; k < 500; k++) {
    /* Inport: '<Root>/GlobalConfig' incorporates:
     *  Outport: '<Root>/ElectricalID_output'
     */
    /* '<S2>:350:7' d(k) = 1.5*GlobalConfig.PMSM_config.polePairs*ElectricalID_output.PMSM_parameters.Psi_PM_Vs*measArray1(k); */
    rtElectricalID6ph0_DW->d[k] = 1.5F *
      rtElectricalID6ph0_U->GlobalConfig_out.PMSM_config.polePairs *
      rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs *
      rtElectricalID6ph0_DW->measArray1[k];
  }

  /* Inport: '<Root>/GlobalConfig' */
  /*  goertzel */
  /* '<S2>:350:11' ISR_factor = single(0.0001 / GlobalConfig.sampleTimeISR); */
  /* Adjusts the k-factor for different ISR frequencys */
  /* '<S2>:350:12' k = single(2.0 / ISR_factor); */
  /*  coefficient number of the spectrum (40Hz) */
  /* '<S2>:350:13' N = 500; */
  /*  length of input signal */
  /* Precalculation of constants */
  /* '<S2>:350:16' A = 2*pi*k/N; */
  A = 2.0F / (0.0001F / rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR) *
    6.28318548F / 500.0F;

  /* '<S2>:350:17' B = 2*cos(A); */
  B = 2.0F * cosf(A);

  /* '<S2>:350:18' C = exp(-j*A); */
  if (-A == 0.0F) {
    C_re = 1.0F;
    C_im = 0.0F;
  } else {
    C_re = cosf(-A);
    C_im = sinf(-A);
  }

  /* State variables */
  /* '<S2>:350:20' s0 = single(0.0); */
  /* '<S2>:350:21' s1 = single(0.0); */
  A = 0.0F;

  /* '<S2>:350:22' s2 = single(0.0); */
  s2 = 0.0F;

  /* Main loop for M */
  /* '<S2>:350:25' for i = 1:N */
  for (k = 0; k < 500; k++) {
    /* N multiplications, 2N additions */
    /* '<S2>:350:26' s0 = d(i) +B*s1-s2; */
    s0 = (B * A + rtElectricalID6ph0_DW->d[k]) - s2;

    /* corresponds to (16) */
    /* '<S2>:350:27' s2 = s1; */
    s2 = A;

    /* '<S2>:350:28' s1 = s0; */
    A = s0;
  }

  /* Finalizing calculations for M */
  /* '<S2>:350:32' s0 = B*s1-s2; */
  /* corresponds to (16) with zero input; 1 multiplication and 1 addition */
  /* '<S2>:350:33' Xg = s0-s1*C %corresponds to (17); 4 multiplications and 3 additions */
  Xg_re = (B * A - s2) - A * C_re;
  Xg_im = 0.0F - A * C_im;

  /* corresponds to (17); 4 multiplications and 3 additions */
  /* Reset state variables */
  /* '<S2>:350:36' s0 = single(0.0); */
  /* '<S2>:350:37' s1 = single(0.0); */
  A = 0.0F;

  /* '<S2>:350:38' s2 = single(0.0); */
  s2 = 0.0F;

  /* Main loop for omega_m */
  /* '<S2>:350:41' for i = 1:N */
  for (k = 0; k < 500; k++) {
    /* N multiplications, 2N additions */
    /* '<S2>:350:42' s0 = i_est(i) +B*s1-s2; */
    s0 = (B * A + rtElectricalID6ph0_DW->i_est[k]) - s2;

    /* corresponds to (16) */
    /* '<S2>:350:43' s2 = s1; */
    s2 = A;

    /* '<S2>:350:44' s1 = s0; */
    A = s0;
  }

  /* Finalizing calculations for omega_m */
  /* '<S2>:350:48' s0 = B*s1-s2; */
  /* corresponds to (16) with zero input; 1 multiplication and 1 addition */
  /* '<S2>:350:49' Yg = s0-s1*C %corresponds to (17); 4 multiplications and 3 additions */
  /* corresponds to (17); 4 multiplications and 3 additions */
  /*  calculate value of transfer function  */
  /* '<S2>:350:54' Gg = Yg/Xg; */
  /*  calculate J from Gg */
  /* '<S2>:350:56' ElectricalID_output.PMSM_parameters.J_kg_m_squared = single(abs(1/(Gg*j*2*pi*40))); */
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
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared =
    rt_hypotf(C_re, C_im);

  /* without damping */
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function [ElectricalID_output] = SetpVectorToDutyCycle6ph(ElectricalID_output_in,VDC,SetpVector)
 * Copy ElectricalID_output
 */
static void SetpVectorToDutyCycle6ph(uz_ParaID_ElectricalID6ph_output_t
  *ElectricalID_output_in, real32_T VDC, const real32_T SetpVector[6])
{
  real32_T DutyCycle;

  /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
  /* Write DutyCycle to ElectricalID_output */
  /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_a1 = GenerateDutyCycle(VDC,SetpVector(1)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[0] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_a1 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_a1 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_a1 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_b1 = GenerateDutyCycle(VDC,SetpVector(2)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[1] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_b1 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_b1 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_b1 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_c1 = GenerateDutyCycle(VDC,SetpVector(3)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[2] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_c1 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_c1 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_c1 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[3] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_a2 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_a2 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_a2 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[4] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_b2 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_b2 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_b2 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[5] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_c2 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_c2 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_c2 = DutyCycle;
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function [out] = VSD6ph(VSD,abc_struct)
 */
static void VSD6ph(const real32_T b_VSD[36], real32_T abc_struct_a1, real32_T
                   abc_struct_b1, real32_T abc_struct_c1, real32_T abc_struct_a2,
                   real32_T abc_struct_b2, real32_T abc_struct_c2, real32_T
                   *out_alpha, real32_T *out_beta, real32_T *out_x, real32_T
                   *out_y, real32_T *out_z1, real32_T *out_z2,
                   DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  int32_T i;
  int32_T i_0;
  real32_T alphabeta_vector[6];

  /* 'VSD6ph:2' abc_vector = cat(1,abc_struct.a1,abc_struct.b1,abc_struct.c1,abc_struct.a2,abc_struct.b2,abc_struct.c2); */
  rtElectricalID6ph0_DW->abc_vector[0] = abc_struct_a1;
  rtElectricalID6ph0_DW->abc_vector[1] = abc_struct_b1;
  rtElectricalID6ph0_DW->abc_vector[2] = abc_struct_c1;
  rtElectricalID6ph0_DW->abc_vector[3] = abc_struct_a2;
  rtElectricalID6ph0_DW->abc_vector[4] = abc_struct_b2;
  rtElectricalID6ph0_DW->abc_vector[5] = abc_struct_c2;

  /* 'VSD6ph:3' alphabeta_vector = VSD*abc_vector; */
  for (i = 0; i < 6; i++) {
    alphabeta_vector[i] = 0.0F;
    for (i_0 = 0; i_0 < 6; i_0++) {
      alphabeta_vector[i] += b_VSD[6 * i_0 + i] *
        rtElectricalID6ph0_DW->abc_vector[i_0];
    }
  }

  /* 'VSD6ph:4' out.alpha = alphabeta_vector(1); */
  *out_alpha = alphabeta_vector[0];

  /* 'VSD6ph:5' out.beta = alphabeta_vector(2); */
  *out_beta = alphabeta_vector[1];

  /* 'VSD6ph:6' out.x = alphabeta_vector(3); */
  *out_x = alphabeta_vector[2];

  /* 'VSD6ph:7' out.y = alphabeta_vector(4); */
  *out_y = alphabeta_vector[3];

  /* 'VSD6ph:8' out.z1 = alphabeta_vector(5); */
  *out_z1 = alphabeta_vector[4];

  /* 'VSD6ph:9' out.z2 = alphabeta_vector(6); */
  *out_z2 = alphabeta_vector[5];
}

/*
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function MeasureStepResponse(voltage,current)
 */
static void MeasureStepResponse(real32_T voltage, real32_T current,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  int32_T k;
  real32_T x;
  uint32_T qY;

  /* MATLAB Function 'MeasureStepResponse': '<S2>:951' */
  /* '<S2>:951:2' if(counter <= 1024) */
  if (rtElectricalID6ph0_DW->counter <= 1024U) {
    /* '<S2>:951:3' if(counter > 1) */
    if (rtElectricalID6ph0_DW->counter > 1U) {
      /* '<S2>:951:4' measArray1(counter-1) = current; */
      qY = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID6ph0_DW->counter - 1U > rtElectricalID6ph0_DW->counter)
      {
        qY = 0U;
      }

      rtElectricalID6ph0_DW->measArray1[(int32_T)qY - 1] = current;

      /* safe 1024 current values to 2D array */
      /* '<S2>:951:5' if(mod(counter,5) == 0) */
      if (rtElectricalID6ph0_DW->counter - rtElectricalID6ph0_DW->counter / 5U *
          5U == 0U) {
        /* exec every 5th cycle */
        /* '<S2>:951:6' Vstep(z-1) = voltage; */
        qY = rtElectricalID6ph0_DW->z - 1U;
        if (rtElectricalID6ph0_DW->z - 1U > rtElectricalID6ph0_DW->z) {
          qY = 0U;
        }

        rtElectricalID6ph0_DW->Vstep[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S2>:951:7' z = z + 1; */
        qY = rtElectricalID6ph0_DW->z + 1U;
        if (rtElectricalID6ph0_DW->z + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID6ph0_DW->z = (uint16_T)qY;
      }
    } else if (rtElectricalID6ph0_DW->counter == 1U) {
      /* '<S2>:951:9' elseif(counter == 1) */
      /* '<S2>:951:10' Vstep(1) = voltage; */
      rtElectricalID6ph0_DW->Vstep[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S2>:951:11' z = z + 1; */
      qY = rtElectricalID6ph0_DW->z + 1U;
      if (rtElectricalID6ph0_DW->z + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID6ph0_DW->z = (uint16_T)qY;
    }

    /* '<S2>:951:13' else */
    /* '<S2>:951:14' if(counter == 1025) */
  } else if (rtElectricalID6ph0_DW->counter == 1025U) {
    /* '<S2>:951:15' measArray1(counter-1) = current; */
    qY = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID6ph0_DW->counter - 1U > rtElectricalID6ph0_DW->counter) {
      qY = 0U;
    }

    rtElectricalID6ph0_DW->measArray1[(int32_T)qY - 1] = current;

    /* safe last current val */
    /* '<S2>:951:16' Vstep(z-1) = voltage; */
    qY = rtElectricalID6ph0_DW->z - 1U;
    if (rtElectricalID6ph0_DW->z - 1U > rtElectricalID6ph0_DW->z) {
      qY = 0U;
    }

    rtElectricalID6ph0_DW->Vstep[(int32_T)qY - 1] = voltage;

    /* '<S2>:951:17' V0 = mean(Vstep); */
    x = rtElectricalID6ph0_DW->Vstep[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID6ph0_DW->Vstep[k + 1];
    }

    rtElectricalID6ph0_DW->V0 = x / 205.0F;

    /* average voltage */
  }
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
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

/* Function for Chart: '<S1>/ElectricalID6ph' */
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
 * Function for Chart: '<S1>/ElectricalID6ph'
 * function LM_algorithm_Lq
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_Lq(real32_T *R_est, real32_T *L_est,
  ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U, DW_ElectricalID6ph0_t
  *rtElectricalID6ph0_DW)
{
  int32_T H_tmp;
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;
  real32_T L_lm;
  real32_T R_lm;
  real32_T e_lm;

  /* MATLAB Function 'LM_algorithm_Lq': '<S2>:281' */
  /* '<S2>:281:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S2>:281:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S2>:281:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S2>:281:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S2>:281:25' for it=uint16(1):n_iters */
  for (it = 0; it < rtElectricalID6ph0_DW->n_iters; it++) {
    /* '<S2>:281:26' if updateJ == 1 */
    if (rtElectricalID6ph0_DW->updateJ) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S2>:281:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S2>:281:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S2>:281:40' d(1:1024) = measArray1(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* Inport: '<Root>/GlobalConfig' */
        /* '<S2>:281:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S2>:281:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S2>:281:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S2>:281:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S2>:281:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        R_lm = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                      rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR) /
                    *L_est);
        L_lm = (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID6ph0_DW->V0 *
          rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR;
        rtElectricalID6ph0_DW->J[k] = -((R_lm - 1.0F) *
          rtElectricalID6ph0_DW->V0) / (*R_est * *R_est) - L_lm * R_lm / (*L_est
          * *R_est);
        rtElectricalID6ph0_DW->J[k + 2048] = R_lm * L_lm / (*L_est * *L_est);

        /* Inport: '<Root>/GlobalConfig' */
        /* . */
        /* . */
        /* . */
        /* . */
        /* '<S2>:281:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        rtElectricalID6ph0_DW->i_est[k] = (1.0F - expf((((real32_T)k + 1.0F) -
          1.0F) * rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR * -*R_est
          / *L_est)) * (rtElectricalID6ph0_DW->V0 / *R_est);
        rtElectricalID6ph0_DW->d[k] = rtElectricalID6ph0_DW->measArray1[k] -
          rtElectricalID6ph0_DW->i_est[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S2>:281:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          H_tmp = k + (i << 1);
          rtElectricalID6ph0_DW->H[H_tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            rtElectricalID6ph0_DW->H[H_tmp] += rtElectricalID6ph0_DW->J[(k << 11)
              + i_0] * rtElectricalID6ph0_DW->J[(i << 11) + i_0];
          }
        }
      }

      /* '<S2>:281:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S2>:281:44' e = dot(d,d); */
        rtElectricalID6ph0_DW->e = 0.0F;
        for (k = 0; k < 2048; k++) {
          rtElectricalID6ph0_DW->e += rtElectricalID6ph0_DW->d[k] *
            rtElectricalID6ph0_DW->d[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S2>:281:49' H(1,1) = H(1,1) + lambda; */
    rtElectricalID6ph0_DW->H[0] += rtElectricalID6ph0_DW->lambda;

    /* '<S2>:281:50' H(2,2)=H(2,2)+lambda; */
    rtElectricalID6ph0_DW->H[3] += rtElectricalID6ph0_DW->lambda;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S2>:281:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    inv(rtElectricalID6ph0_DW->H, rtElectricalID6ph0_DW->fv4);
    for (k = 0; k < 2; k++) {
      memcpy(&rtElectricalID6ph0_DW->fv[k << 10], &rtElectricalID6ph0_DW->J[k <<
             11], sizeof(real32_T) << 10U);
    }

    mtimes(rtElectricalID6ph0_DW->fv, &rtElectricalID6ph0_DW->d[0],
           rtElectricalID6ph0_DW->fv5);

    /* '<S2>:281:54' R_lm = R_est + dp(1); */
    R_lm = (-rtElectricalID6ph0_DW->fv4[0] * rtElectricalID6ph0_DW->fv5[0] +
            -rtElectricalID6ph0_DW->fv4[2] * rtElectricalID6ph0_DW->fv5[1]) +
      *R_est;

    /* '<S2>:281:55' L_lm = L_est + dp(2); */
    L_lm = (-rtElectricalID6ph0_DW->fv4[1] * rtElectricalID6ph0_DW->fv5[0] +
            -rtElectricalID6ph0_DW->fv4[3] * rtElectricalID6ph0_DW->fv5[1]) +
      *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S2>:281:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S2>:281:62' d(1:1024) = measArray1(1:1024) - i_est(1:1024); */
    /* '<S2>:281:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* Inport: '<Root>/GlobalConfig' */
      /* '<S2>:281:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      rtElectricalID6ph0_DW->i_est[k] = (1.0F - expf((((real32_T)k + 1.0F) -
        1.0F) * rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR * -R_lm /
        L_lm)) * (rtElectricalID6ph0_DW->V0 / R_lm);
      rtElectricalID6ph0_DW->d[k] = rtElectricalID6ph0_DW->measArray1[k] -
        rtElectricalID6ph0_DW->i_est[k];
      e_lm += rtElectricalID6ph0_DW->d[k] * rtElectricalID6ph0_DW->d[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S2>:281:66' if e_lm < e */
    if (e_lm < rtElectricalID6ph0_DW->e) {
      /* '<S2>:281:67' lambda = lambda/10; */
      rtElectricalID6ph0_DW->lambda /= 10.0F;

      /* '<S2>:281:68' R_est = R_lm; */
      *R_est = R_lm;

      /* '<S2>:281:69' L_est = L_lm; */
      *L_est = L_lm;

      /* '<S2>:281:70' e = e_lm; */
      rtElectricalID6ph0_DW->e = e_lm;

      /* '<S2>:281:71' updateJ = boolean(1); */
      rtElectricalID6ph0_DW->updateJ = true;
    } else {
      /* '<S2>:281:72' else */
      /* '<S2>:281:73' updateJ = boolean(0); */
      rtElectricalID6ph0_DW->updateJ = false;

      /* '<S2>:281:74' lambda = lambda*10; */
      rtElectricalID6ph0_DW->lambda *= 10.0F;
    }
  }
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
static void stepResponse_q(real32_T *R_est, real32_T *L_est,
  ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t
  *rtElectricalID6ph0_Y, DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  int32_T k;
  real32_T x;
  uint32_T qY;

  /* During 'stepResponse_q': '<S2>:277' */
  /* '<S2>:279:1' sf_internal_predicateOutput = counter == 1026; */
  if (rtElectricalID6ph0_DW->counter == 1026U) {
    /* Outport: '<Root>/ElectricalID_output' */
    /* Transition: '<S2>:279' */
    /* Exit 'stepResponse_q': '<S2>:277' */
    /* '<S2>:277:36' ElectricalID_output.enable_TriState          = [boolean(0),boolean(0),boolean(0)]; */
    rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[0] = false;
    rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[1] = false;
    rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[2] = false;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_Levenberg_Marquardt_q;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'Levenberg_Marquardt_q': '<S2>:278' */
    /* '<S2>:278:4' ElectricalID_FOC_output.activeState = uint16(143); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 143U;

    /* '<S2>:278:5' LM_algorithm_Lq; */
    LM_algorithm_Lq(R_est, L_est, rtElectricalID6ph0_U, rtElectricalID6ph0_DW);

    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S2>:278:6' ElectricalID_output.PMSM_parameters.Lq_Henry = L_est*0.5; */
    rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry = *L_est *
      0.5F;
  } else {
    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S2>:277:11' ElectricalID_output.PWM_Switch_c1 = single(DutyCycle); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 =
      rtElectricalID6ph0_DW->DutyCycle;

    /* '<S2>:277:12' if(counter <= 1024) */
    if (rtElectricalID6ph0_DW->counter <= 1024U) {
      /* '<S2>:277:13' if(counter > 1) */
      if (rtElectricalID6ph0_DW->counter > 1U) {
        /* '<S2>:277:14' measArray1(counter-1) = ActualValues.I_abc.c1; */
        qY = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter - 1U > rtElectricalID6ph0_DW->counter)
        {
          qY = 0U;
        }

        rtElectricalID6ph0_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.c1;

        /* '<S2>:277:15' if(mod(counter,5) == 0) */
        if (rtElectricalID6ph0_DW->counter - rtElectricalID6ph0_DW->counter / 5U
            * 5U == 0U) {
          /* '<S2>:277:16' Vstep(z-1) = ActualValues.V_abc.b1+ActualValues.V_abc.c1; */
          qY = rtElectricalID6ph0_DW->z - 1U;
          if (rtElectricalID6ph0_DW->z - 1U > rtElectricalID6ph0_DW->z) {
            qY = 0U;
          }

          rtElectricalID6ph0_DW->Vstep[(int32_T)qY - 1] =
            rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.b1 +
            rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.c1;

          /* '<S2>:277:17' z = z + 1; */
          qY = rtElectricalID6ph0_DW->z + 1U;
          if (rtElectricalID6ph0_DW->z + 1U > 65535U) {
            qY = 65535U;
          }

          rtElectricalID6ph0_DW->z = (uint16_T)qY;
        }

        /* '<S2>:277:19' counter = counter + 1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }

      /* '<S2>:277:21' if(counter == 1) */
      if (rtElectricalID6ph0_DW->counter == 1U) {
        /* '<S2>:277:22' counter = counter + 1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;

        /* '<S2>:277:23' Vstep(1) = ActualValues.V_abc.c1+ActualValues.V_abc.b1; */
        rtElectricalID6ph0_DW->Vstep[0] =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.c1 +
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.b1;

        /* '<S2>:277:24' z = z + 1; */
        qY = rtElectricalID6ph0_DW->z + 1U;
        if (rtElectricalID6ph0_DW->z + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID6ph0_DW->z = (uint16_T)qY;
      }
    } else {
      /* '<S2>:277:26' else */
      /* '<S2>:277:27' if(counter == 1025) */
      if (rtElectricalID6ph0_DW->counter == 1025U) {
        /* '<S2>:277:28' measArray1(counter-1) = ActualValues.I_abc.c1; */
        qY = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter - 1U > rtElectricalID6ph0_DW->counter)
        {
          qY = 0U;
        }

        rtElectricalID6ph0_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.c1;

        /* '<S2>:277:29' Vstep(z-1) = ActualValues.V_abc.b1+ActualValues.V_abc.c1; */
        qY = rtElectricalID6ph0_DW->z - 1U;
        if (rtElectricalID6ph0_DW->z - 1U > rtElectricalID6ph0_DW->z) {
          qY = 0U;
        }

        rtElectricalID6ph0_DW->Vstep[(int32_T)qY - 1] =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.b1 +
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.c1;

        /* '<S2>:277:30' V0 = mean(Vstep); */
        x = rtElectricalID6ph0_DW->Vstep[0];
        for (k = 0; k < 204; k++) {
          x += rtElectricalID6ph0_DW->Vstep[k + 1];
        }

        rtElectricalID6ph0_DW->V0 = x / 205.0F;
      }

      /* Outport: '<Root>/ElectricalID_output' */
      /* '<S2>:277:32' ElectricalID_output.PWM_Switch_c1 = single(0); */
      rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

      /* '<S2>:277:33' counter = counter + 1; */
      qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
      if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
      {
        qY = MAX_uint32_T;
      }

      rtElectricalID6ph0_DW->counter = qY;
    }
  }
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
static void exit_internal_ElectricalID(ExtU_ElectricalID6ph0_t
  *rtElectricalID6ph0_U, ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y,
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW)
{
  /* Exit Internal 'ElectricalID': '<S2>:761' */
  switch (rtElectricalID6ph0_DW->is_ElectricalID) {
   case IN_Levenberg_Marquardt:
    /* Exit 'Levenberg_Marquardt': '<S2>:91' */
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Levenberg_Marquardt_q:
    /* Exit 'Levenberg_Marquardt_q': '<S2>:278' */
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'alignRotor_d_off': '<S2>:53' */
    /* '<S2>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
    rtElectricalID6ph0_Y->ElectricalID_output.thetaOffset =
      rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.theta_m;

    /* '<S2>:53:8' DutyCycle=single(0.0); */
    rtElectricalID6ph0_DW->DutyCycle = 0.0F;

    /* resets the DC and DC_manual flag, so that for the step-response */
    /* '<S2>:53:9' DC_manual=boolean(0); */
    rtElectricalID6ph0_DW->DC_manual = false;

    /* a new DC can be entered */
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off2:
    /* Exit 'alignRotor_d_off2': '<S2>:848' */
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_on:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'alignRotor_d_on': '<S2>:3' */
    /* '<S2>:3:19' ElectricalID_output.PWM_Switch_a1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_evaluate_Turn_DC:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'evaluate_Turn_DC': '<S2>:379' */
    /* '<S2>:379:27' ElectricalID_output.PWM_Switch_a1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;

    /* '<S2>:379:28' ElectricalID_output.PWM_Switch_b1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;

    /* '<S2>:379:29' ElectricalID_output.PWM_Switch_c1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

    /* '<S2>:379:30' ElectricalID_output.PWM_Switch_a2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;

    /* '<S2>:379:31' ElectricalID_output.PWM_Switch_b2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;

    /* '<S2>:379:32' ElectricalID_output.PWM_Switch_c2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_findDutyCycle:
    /* Exit 'findDutyCycle': '<S2>:789' */
    /* '<S2>:789:30' ref_amplitude = single(ActualVabc.a1); */
    rtElectricalID6ph0_DW->ref_amplitude = rtElectricalID6ph0_DW->ActualVabc.a1;

    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S2>:789:31' ElectricalID_output.PWM_Switch_a1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_measure_psiPM:
    /* Exit 'measure_psiPM': '<S2>:405' */
    /* '<S2>:405:20' counter = uint32(1); */
    rtElectricalID6ph0_DW->counter = 1U;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_rotorInertiaEstimation:
    /* Exit 'rotorInertiaEstimation': '<S2>:337' */
    /* '<S2>:337:18' goertzel; */
    goertzel(rtElectricalID6ph0_U, rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_stepResponse1:
    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Exit 'stepResponse1': '<S2>:940' */
    /* '<S2>:940:15' ElectricalID_FOC_output.activeState = uint16(22); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 22U;

    /* Outport: '<Root>/ElectricalID_output' */
    /* '<S2>:940:16' ElectricalID_output.PWM_Switch_a1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;

    /* '<S2>:940:17' ElectricalID_output.PWM_Switch_b1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;

    /* '<S2>:940:18' ElectricalID_output.PWM_Switch_c1 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

    /* '<S2>:940:19' ElectricalID_output.PWM_Switch_a2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;

    /* '<S2>:940:20' ElectricalID_output.PWM_Switch_b2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;

    /* '<S2>:940:21' ElectricalID_output.PWM_Switch_c2 = single(0); */
    rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_stepResponse_q:
    /* Outport: '<Root>/ElectricalID_output' */
    /* Exit 'stepResponse_q': '<S2>:277' */
    /* '<S2>:277:36' ElectricalID_output.enable_TriState          = [boolean(0),boolean(0),boolean(0)]; */
    rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[0] = false;
    rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[1] = false;
    rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[2] = false;
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_waitState:
    /* Outport: '<Root>/finishedElectricalID' */
    /* Exit 'waitState': '<S2>:428' */
    /* '<S2>:428:19' finishedElectricalID=boolean(1); */
    rtElectricalID6ph0_Y->finishedElectricalID = true;

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S2>:428:20' enteredElectricalID=boolean(0); */
    rtElectricalID6ph0_Y->enteredElectricalID = false;

    /* '<S2>:428:21' reset_FOC_output; */
    reset_FOC_output(rtElectricalID6ph0_Y);
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   default:
    rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/ElectricalID6ph' */
static void ElectricalID(ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U,
  ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y, DW_ElectricalID6ph0_t
  *rtElectricalID6ph0_DW)
{
  int32_T i;
  int32_T i_0;
  uint32_T qY;
  boolean_T guard1 = false;

  /* Inport: '<Root>/GlobalConfig' */
  /* During 'ElectricalID': '<S2>:761' */
  /* '<S2>:901:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.ElectricalID==0 ||.... */
  /* '<S2>:901:2'  GlobalConfig.enableParameterID==0; */
  /* . */
  if (rtElectricalID6ph0_U->GlobalConfig_out.Reset ||
      (!rtElectricalID6ph0_U->GlobalConfig_out.ElectricalID) ||
      (!rtElectricalID6ph0_U->GlobalConfig_out.enableParameterID)) {
    /* Transition: '<S2>:901' */
    /* '<S2>:901:3' enteredElectricalID=boolean(0); */
    /* '<S2>:901:3' initParams; */
    initParams(&rtElectricalID6ph0_DW->R_est_m, &rtElectricalID6ph0_DW->L_est_c,
               rtElectricalID6ph0_U, rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);
    exit_internal_ElectricalID(rtElectricalID6ph0_U, rtElectricalID6ph0_Y,
      rtElectricalID6ph0_DW);
    rtElectricalID6ph0_DW->is_c3_ElectricalID6ph0 = IN_Waiting;

    /* Entry 'Waiting': '<S2>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else {
    guard1 = false;
    switch (rtElectricalID6ph0_DW->is_ElectricalID) {
     case IN_Levenberg_Marquardt:
      /* During 'Levenberg_Marquardt': '<S2>:91' */
      /* '<S2>:426:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 &&.... */
      /* '<S2>:426:2'  ElectricalIDConfig.identLq == 0; */
      /* . */
      if (rtElectricalID6ph0_U->GlobalConfig_out.ACCEPT &&
          (!rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.identLq)) {
        /* Transition: '<S2>:426' */
        /* Exit 'Levenberg_Marquardt': '<S2>:91' */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_calculatePIcontroller;
        enter_atomic_calculatePIcontrol(rtElectricalID6ph0_U,
          rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);

        /* '<S2>:420:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1 .... */
        /* '<S2>:420:2' && ElectricalIDConfig.identLq == 1; */
        /* . */
      } else if (rtElectricalID6ph0_U->GlobalConfig_out.ACCEPT &&
                 rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.identLq)
      {
        /* Transition: '<S2>:420' */
        /* Exit 'Levenberg_Marquardt': '<S2>:91' */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_stepResponse_q;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stepResponse_q': '<S2>:277' */
        /* '<S2>:277:4' ElectricalID_FOC_output.activeState = uint16(142); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 142U;

        /* '<S2>:277:5' resetParams_LM; */
        resetParams_LM(&rtElectricalID6ph0_DW->R_est_m,
                       &rtElectricalID6ph0_DW->L_est_c, rtElectricalID6ph0_DW);

        /* '<S2>:277:6' z = uint16(1); */
        rtElectricalID6ph0_DW->z = 1U;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S2>:277:7' ElectricalID_output.enable_TriState          = [boolean(1),boolean(0),boolean(0)]; */
        rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[0] = true;
        rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[1] = false;
        rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[2] = false;

        /* '<S2>:277:8' ElectricalID_output.PWM_Switch_a1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;

        /* '<S2>:277:9' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;
      }
      break;

     case IN_Levenberg_Marquardt_q:
      /* During 'Levenberg_Marquardt_q': '<S2>:278' */
      /* Transition: '<S2>:295' */
      /* Exit 'Levenberg_Marquardt_q': '<S2>:278' */
      rtElectricalID6ph0_DW->is_ElectricalID = IN_calculatePIcontroller;
      enter_atomic_calculatePIcontrol(rtElectricalID6ph0_U, rtElectricalID6ph0_Y,
        rtElectricalID6ph0_DW);
      break;

     case IN_alignRotor_d_off:
      /* During 'alignRotor_d_off': '<S2>:53' */
      /* '<S2>:411:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID6ph0_DW->one_sec_transition_counter ==
          rtElectricalID6ph0_DW->counter) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S2>:411' */
        /* Exit 'alignRotor_d_off': '<S2>:53' */
        /* '<S2>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
        rtElectricalID6ph0_Y->ElectricalID_output.thetaOffset =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.theta_m;

        /* '<S2>:53:8' DutyCycle=single(0.0); */
        rtElectricalID6ph0_DW->DutyCycle = 0.0F;

        /* resets the DC and DC_manual flag, so that for the step-response */
        /* '<S2>:53:9' DC_manual=boolean(0); */
        rtElectricalID6ph0_DW->DC_manual = false;

        /* a new DC can be entered */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_findDutyCycle;

        /* Entry 'findDutyCycle': '<S2>:789' */
        rtElectricalID6ph0_DW->ActualVabc.a1 = 0.0F;
        rtElectricalID6ph0_DW->ActualVabc.b1 = 0.0F;
        rtElectricalID6ph0_DW->ActualVabc.c1 = 0.0F;
        rtElectricalID6ph0_DW->ActualVabc.a2 = 0.0F;
        rtElectricalID6ph0_DW->ActualVabc.b2 = 0.0F;
        rtElectricalID6ph0_DW->ActualVabc.c2 = 0.0F;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Motor must be manually locked via load machine until state 60 */
        /* '<S2>:789:4' ElectricalID_FOC_output.activeState = uint16(130); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 130U;

        /* '<S2>:789:5' if(ElectricalIDConfig.dutyCyc > 0.0) */
        if (rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.dutyCyc >
            0.0F) {
          /* Checks if a manual value for the DutyCycle was set */
          /* '<S2>:789:6' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
          rtElectricalID6ph0_DW->DutyCycle =
            rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.dutyCyc;

          /* '<S2>:789:7' DC_manual = boolean(1); */
          rtElectricalID6ph0_DW->DC_manual = true;
        } else {
          /* '<S2>:789:8' else */
          /* '<S2>:789:9' DutyCycle = single(DutyCycle); */
          /* Starting DC */
        }

        /* '<S2>:789:11' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* starts with 1, so that the DutyCylce_mod function wont be entered */
        /* during the fist cycle through the state */
      } else {
        /* '<S2>:53:5' counter  = counter +1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     case IN_alignRotor_d_off2:
      /* During 'alignRotor_d_off2': '<S2>:848' */
      /* '<S2>:849:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID6ph0_DW->one_sec_transition_counter ==
          rtElectricalID6ph0_DW->counter) {
        /* Transition: '<S2>:849' */
        /* Exit 'alignRotor_d_off2': '<S2>:848' */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_stepResponse1;

        /* Entry 'stepResponse1': '<S2>:940' */
        rtElectricalID6ph0_DW->current.alpha = 0.0F;
        rtElectricalID6ph0_DW->current.beta = 0.0F;
        rtElectricalID6ph0_DW->current.x = 0.0F;
        rtElectricalID6ph0_DW->current.y = 0.0F;
        rtElectricalID6ph0_DW->current.z1 = 0.0F;
        rtElectricalID6ph0_DW->current.z2 = 0.0F;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* state 2.0 */
        /* '<S2>:940:3' ElectricalID_FOC_output.activeState = uint16(140); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 140U;

        /* '<S2>:940:4' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* '<S2>:940:5' z = uint16(1); */
        rtElectricalID6ph0_DW->z = 1U;
      } else {
        /* '<S2>:848:5' counter = counter +1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     case IN_alignRotor_d_on:
      /* During 'alignRotor_d_on': '<S2>:3' */
      /* '<S2>:164:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID6ph0_DW->one_sec_transition_counter ==
          rtElectricalID6ph0_DW->counter) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S2>:164' */
        /* Exit 'alignRotor_d_on': '<S2>:3' */
        /* '<S2>:3:19' ElectricalID_output.PWM_Switch_a1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;
        rtElectricalID6ph0_DW->is_ElectricalID = IN_alignRotor_d_off;

        /* Entry 'alignRotor_d_off': '<S2>:53' */
        /* '<S2>:53:3' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S2>:53:4' ElectricalID_FOC_output.activeState = uint16(121); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 121U;
      } else {
        /* '<S2>:3:7' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
        rtElectricalID6ph0_DW->R_est_m = (real32_T)
          rtElectricalID6ph0_DW->counter *
          rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S2>:3:8' if(DutyCycle_filt > 1) */
        if (rtElectricalID6ph0_DW->R_est_m > 1.0F) {
          /* '<S2>:3:9' DutyCycle_filt = single(1.0); */
          rtElectricalID6ph0_DW->R_est_m = 1.0F;
        }

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S2>:3:11' ElectricalID_output.PWM_Switch_a1 = single(DutyCycle*DutyCycle_filt); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 =
          rtElectricalID6ph0_DW->DutyCycle * rtElectricalID6ph0_DW->R_est_m;

        /* '<S2>:3:12' ElectricalID_output.PWM_Switch_b1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;

        /* '<S2>:3:13' ElectricalID_output.PWM_Switch_c1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

        /* '<S2>:3:14' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* '<S2>:3:15' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* '<S2>:3:16' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;

        /* '<S2>:3:17' counter  = counter +1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     case IN_calculatePIcontroller:
      /* During 'calculatePIcontroller': '<S2>:284' */
      /* '<S2>:408:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1; */
      if (rtElectricalID6ph0_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S2>:408' */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_measure_psiPM;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'measure_psiPM': '<S2>:405' */
        /* '<S2>:405:4' ElectricalID_FOC_output.activeState = uint16(150); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 150U;

        /* '<S2>:405:5' ElectricalID_FOC_output.enableFOC_speed = boolean(1); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_speed = true;

        /* '<S2>:405:6' ElectricalID_FOC_output.n_ref_FOC = ElectricalIDConfig.n_ref_measurement; */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.n_ref_FOC =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.n_ref_measurement;

        /* '<S2>:405:7' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        rtElectricalID6ph0_DW->R_est_m = roundf(3.0F /
          rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID6ph0_DW->R_est_m < 4.2949673E+9F) {
          if (rtElectricalID6ph0_DW->R_est_m >= 0.0F) {
            rtElectricalID6ph0_DW->wait_count = (uint32_T)
              rtElectricalID6ph0_DW->R_est_m;
          } else {
            rtElectricalID6ph0_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID6ph0_DW->wait_count = MAX_uint32_T;
        }
      }
      break;

     case IN_endState:
      /* During 'endState': '<S2>:356' */
      /* '<S2>:425:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID6ph0_DW->one_sec_transition_counter ==
          rtElectricalID6ph0_DW->counter) {
        /* Transition: '<S2>:425' */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_waitState;

        /* Entry 'waitState': '<S2>:428' */
        /* do nothing */
        /* '<S2>:428:3' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Outport: '<Root>/ElectricalID_output'
         */
        /* '<S2>:428:4' ElectricalID_FOC_output.enableFOC_current = boolean(0); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_current = false;

        /* '<S2>:428:5' ElectricalID_FOC_output.activeState = uint16(170); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 170U;

        /*  recalculate speed controller using psiPM and J */
        /* '<S2>:428:7' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.PMSM_parameters.Lq_Henry*dampingFactor*... */
        /* '<S2>:428:8'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*ElectricalID_output.PMSM_parameters.Psi_PM_Vs/.... */
        /* '<S2>:428:9'     ElectricalID_output.PMSM_parameters.J_kg_m_squared); */
        /* . */
        /* '<S2>:428:10' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.PMSM_parameters.Lq_Henry * .... */
        /* '<S2>:428:11'     ElectricalID_output.PMSM_parameters.Lq_Henry * dampingFactor * dampingFactor * dampingFactor * .... */
        /* '<S2>:428:12'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*ElectricalID_output.PMSM_parameters.Psi_PM_Vs/.... */
        /* '<S2>:428:13'     ElectricalID_output.PMSM_parameters.J_kg_m_squared); */
        /* . */
        /* . */
        /* . */
        /* '<S2>:428:14' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_n_out =
          rtElectricalID6ph0_DW->Kp_iq_loc /
          (rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
           rtElectricalID6ph0_DW->dampingFactor *
           rtElectricalID6ph0_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F /
           2.0F *
           rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs /
           rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared);

        /* '<S2>:428:15' ElectricalID_FOC_output.Ki_n_out = Ki_n_loc; */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_n_out =
          rtElectricalID6ph0_DW->Kp_iq_loc * rtElectricalID6ph0_DW->Kp_iq_loc /
          (rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
           rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry *
           rtElectricalID6ph0_DW->dampingFactor *
           rtElectricalID6ph0_DW->dampingFactor *
           rtElectricalID6ph0_DW->dampingFactor *
           rtElectricalID6ph0_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F /
           2.0F *
           rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs /
           rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared);
      } else {
        /* '<S2>:356:8' counter = counter + 1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     case IN_evaluate_Turn_DC:
      evaluate_Turn_DC(rtElectricalID6ph0_U, rtElectricalID6ph0_Y,
                       rtElectricalID6ph0_DW);
      break;

     case IN_findDutyCycle:
      /* During 'findDutyCycle': '<S2>:789' */
      /* '<S2>:790:1' sf_internal_predicateOutput = ia_valid==1 ||DC_manual == 1; */
      if (rtElectricalID6ph0_DW->ia_valid || rtElectricalID6ph0_DW->DC_manual) {
        /* Transition: '<S2>:790' */
        /* Exit 'findDutyCycle': '<S2>:789' */
        /* '<S2>:789:30' ref_amplitude = single(ActualVabc.a1); */
        rtElectricalID6ph0_DW->ref_amplitude =
          rtElectricalID6ph0_DW->ActualVabc.a1;

        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S2>:789:31' ElectricalID_output.PWM_Switch_a1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;
        rtElectricalID6ph0_DW->is_ElectricalID = IN_alignRotor_d_off2;

        /* Entry 'alignRotor_d_off2': '<S2>:848' */
        /* '<S2>:848:3' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S2>:848:4' ElectricalID_FOC_output.activeState = uint16(131); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 131U;

        /* '<S2>:789:14' if(DC_manual == 0 && ia_valid==0) */
      } else if ((!rtElectricalID6ph0_DW->DC_manual) &&
                 (!rtElectricalID6ph0_DW->ia_valid)) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* '<S2>:789:15' ElectricalID_output.PWM_Switch_a1 = single(DutyCycle); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 =
          rtElectricalID6ph0_DW->DutyCycle;

        /* Set DC */
        /* '<S2>:789:16' ActualVabc = DutyCycleToPhaseVoltage6ph(ActualValues.V_DC,ElectricalID_output); */
        /* 'DutyCycleToPhaseVoltage6ph:2' ActualVabc.a1 = V_DC * ElectricalID_output.PWM_Switch_a1; */
        rtElectricalID6ph0_DW->ActualVabc.a1 =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC *
          rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1;

        /* 'DutyCycleToPhaseVoltage6ph:3' ActualVabc.b1 = V_DC * ElectricalID_output.PWM_Switch_b1; */
        rtElectricalID6ph0_DW->ActualVabc.b1 =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC *
          rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1;

        /* 'DutyCycleToPhaseVoltage6ph:4' ActualVabc.c1 = V_DC * ElectricalID_output.PWM_Switch_c1; */
        rtElectricalID6ph0_DW->ActualVabc.c1 =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC *
          rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1;

        /* 'DutyCycleToPhaseVoltage6ph:5' ActualVabc.a2 = V_DC * ElectricalID_output.PWM_Switch_a2; */
        rtElectricalID6ph0_DW->ActualVabc.a2 =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC *
          rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2;

        /* 'DutyCycleToPhaseVoltage6ph:6' ActualVabc.b2 = V_DC * ElectricalID_output.PWM_Switch_b2; */
        rtElectricalID6ph0_DW->ActualVabc.b2 =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC *
          rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2;

        /* 'DutyCycleToPhaseVoltage6ph:7' ActualVabc.c2 = V_DC * ElectricalID_output.PWM_Switch_c2; */
        rtElectricalID6ph0_DW->ActualVabc.c2 =
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC *
          rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2;

        /* '<S2>:789:17' if(counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
        rtElectricalID6ph0_DW->R_est_m = roundf(0.4F /
          rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID6ph0_DW->R_est_m < 4.2949673E+9F) {
          if (rtElectricalID6ph0_DW->R_est_m >= 0.0F) {
            qY = (uint32_T)rtElectricalID6ph0_DW->R_est_m;
          } else {
            qY = 0U;
          }
        } else {
          qY = MAX_uint32_T;
        }

        if (rtElectricalID6ph0_DW->counter < qY) {
          /* Wait several time for step response to rise */
          /* '<S2>:789:18' counter = counter +1; */
          qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID6ph0_DW->counter + 1U <
              rtElectricalID6ph0_DW->counter) {
            qY = MAX_uint32_T;
          }

          rtElectricalID6ph0_DW->counter = qY;
        } else {
          if (rtElectricalID6ph0_DW->R_est_m < 4.2949673E+9F) {
            if (rtElectricalID6ph0_DW->R_est_m >= 0.0F) {
              qY = (uint32_T)rtElectricalID6ph0_DW->R_est_m;
            } else {
              qY = 0U;
            }
          } else {
            qY = MAX_uint32_T;
          }

          if (rtElectricalID6ph0_DW->counter >= qY) {
            rtElectricalID6ph0_DW->R_est_m = roundf(0.5F /
              rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
            if (rtElectricalID6ph0_DW->R_est_m < 4.2949673E+9F) {
              if (rtElectricalID6ph0_DW->R_est_m >= 0.0F) {
                qY = (uint32_T)rtElectricalID6ph0_DW->R_est_m;
              } else {
                qY = 0U;
              }
            } else {
              qY = MAX_uint32_T;
            }

            if (rtElectricalID6ph0_DW->counter < qY) {
              /* '<S2>:789:19' elseif(counter >= uint32(0.4/GlobalConfig.sampleTimeISR) &&.... */
              /* '<S2>:789:20'             counter < uint32(0.5/GlobalConfig.sampleTimeISR)) */
              /* . */
              /* record current - WHY NOW? */
              /* '<S2>:789:21' counter = counter +1; */
              qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
              if (rtElectricalID6ph0_DW->counter + 1U <
                  rtElectricalID6ph0_DW->counter) {
                qY = MAX_uint32_T;
              }

              rtElectricalID6ph0_DW->counter = qY;

              /* '<S2>:789:22' ia_sum=ia_sum+single(ActualValues.I_abc.a1); */
              rtElectricalID6ph0_DW->ia_sum +=
                rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.a1;

              /* integral of current - WHY? */
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
      measure_psiPM(rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);
      break;

     case IN_rotorInertiaEstimation:
      /* During 'rotorInertiaEstimation': '<S2>:337' */
      /* '<S2>:357:1' sf_internal_predicateOutput = counter == (wait_count+513); */
      qY = rtElectricalID6ph0_DW->wait_count + /*MW:OvSatOk*/ 513U;
      if (rtElectricalID6ph0_DW->wait_count + 513U <
          rtElectricalID6ph0_DW->wait_count) {
        qY = MAX_uint32_T;
      }

      if (rtElectricalID6ph0_DW->counter == qY) {
        /* Transition: '<S2>:357' */
        /* Exit 'rotorInertiaEstimation': '<S2>:337' */
        /* '<S2>:337:18' goertzel; */
        goertzel(rtElectricalID6ph0_U, rtElectricalID6ph0_Y,
                 rtElectricalID6ph0_DW);
        rtElectricalID6ph0_DW->is_ElectricalID = IN_endState;

        /* Entry 'endState': '<S2>:356' */
        /* '<S2>:356:4' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S2>:356:5' ElectricalID_FOC_output.activeState = uint16(161); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 161U;

        /* '<S2>:356:6' ElectricalID_FOC_output.resetIntegrator=boolean(1); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.resetIntegrator = true;
      } else {
        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S2>:337:10' ElectricalID_FOC_output.i_dq_ref.q = SinusGenerator(ElectricalIDConfig.goertzlAmp,.... */
        /* '<S2>:337:11'     ElectricalIDConfig.goertzlFreq,GlobalConfig.sampleTimeISR); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.q =
          SinusGenerator
          (rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.goertzlAmp,
           rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.goertzlFreq,
           rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR,
           rtElectricalID6ph0_DW);

        /* . */
        /* '<S2>:337:12' if(counter > wait_count && counter < (wait_count+501)) */
        qY = rtElectricalID6ph0_DW->wait_count + /*MW:OvSatOk*/ 501U;
        if (rtElectricalID6ph0_DW->wait_count + 501U <
            rtElectricalID6ph0_DW->wait_count) {
          qY = MAX_uint32_T;
        }

        if ((rtElectricalID6ph0_DW->counter > rtElectricalID6ph0_DW->wait_count)
            && (rtElectricalID6ph0_DW->counter < qY)) {
          /* '<S2>:337:13' measArray1(counter-wait_count) = ActualValues.i_dq.q; */
          qY = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/
            rtElectricalID6ph0_DW->wait_count;
          if (qY > rtElectricalID6ph0_DW->counter) {
            qY = 0U;
          }

          rtElectricalID6ph0_DW->measArray1[(int32_T)qY - 1] =
            rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.q;

          /* '<S2>:337:14' i_est(counter-wait_count) = ActualValues.omega_m; */
          qY = rtElectricalID6ph0_DW->counter - /*MW:OvSatOk*/
            rtElectricalID6ph0_DW->wait_count;
          if (qY > rtElectricalID6ph0_DW->counter) {
            qY = 0U;
          }

          rtElectricalID6ph0_DW->i_est[(int32_T)qY - 1] =
            rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.omega_m;
        }

        /* '<S2>:337:16' counter = counter + 1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     case IN_stepResponse1:
      /* During 'stepResponse1': '<S2>:940' */
      /* '<S2>:95:1' sf_internal_predicateOutput = counter == 1026; */
      if (rtElectricalID6ph0_DW->counter == 1026U) {
        /* Outport: '<Root>/ElectricalID_output' */
        /* Transition: '<S2>:95' */
        /* Exit 'stepResponse1': '<S2>:940' */
        /* '<S2>:940:15' ElectricalID_FOC_output.activeState = uint16(22); */
        /* '<S2>:940:16' ElectricalID_output.PWM_Switch_a1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;

        /* '<S2>:940:17' ElectricalID_output.PWM_Switch_b1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;

        /* '<S2>:940:18' ElectricalID_output.PWM_Switch_c1 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;

        /* '<S2>:940:19' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* '<S2>:940:20' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* '<S2>:940:21' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID6ph0_DW->is_ElectricalID = IN_Levenberg_Marquardt;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'Levenberg_Marquardt': '<S2>:91' */
        /* state 3.0 */
        /* '<S2>:91:4' ElectricalID_FOC_output.activeState = uint16(141); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 141U;

        /* '<S2>:91:5' LM_algorithm; */
        LM_algorithm_Lq(&rtElectricalID6ph0_DW->R_est_m,
                        &rtElectricalID6ph0_DW->L_est_c, rtElectricalID6ph0_U,
                        rtElectricalID6ph0_DW);

        /* Outport: '<Root>/ElectricalID_output' */
        /*  calculate R and L. Considering that all three phases */
        /*  are connected and that a delta connected winding has */
        /*  to be calculated into star connected values, the factor */
        /*  is 2/3 for delta and star connected windings. */
        /*  Therefore Rs and Ld are the values expressed in */
        /*  star connection */
        /* '<S2>:91:12' ElectricalID_output.PMSM_parameters.R_ph_Ohm = (R_est-R_corr)*2.0/3.0; */
        rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm =
          (rtElectricalID6ph0_DW->R_est_m - rtElectricalID6ph0_DW->R_corr) *
          2.0F / 3.0F;

        /* '<S2>:91:13' ElectricalID_output.PMSM_parameters.Ld_Henry = L_est*2.0/3.0; */
        rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Ld_Henry =
          rtElectricalID6ph0_DW->L_est_c * 2.0F / 3.0F;
      } else {
        /* select subsystem component to excite and transform to DutyCycles - in entry??? */
        /* '<S2>:940:8' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,inv_VSD*[ref_amplitude;single(0);single(0);single(0);single(0);single(0)]); */
        rtElectricalID6ph0_DW->fv2[0] = rtElectricalID6ph0_DW->ref_amplitude;
        rtElectricalID6ph0_DW->fv2[1] = 0.0F;
        rtElectricalID6ph0_DW->fv2[2] = 0.0F;
        rtElectricalID6ph0_DW->fv2[3] = 0.0F;
        rtElectricalID6ph0_DW->fv2[4] = 0.0F;
        rtElectricalID6ph0_DW->fv2[5] = 0.0F;
        for (i = 0; i < 6; i++) {
          rtElectricalID6ph0_DW->fv3[i] = 0.0F;
          for (i_0 = 0; i_0 < 6; i_0++) {
            rtElectricalID6ph0_DW->fv3[i] +=
              rtElectricalID6ph0_ConstP.ElectricalID6ph_inv_VSD[6 * i_0 + i] *
              rtElectricalID6ph0_DW->fv2[i_0];
          }
        }

        /* Outport: '<Root>/ElectricalID_output' */
        SetpVectorToDutyCycle6ph(&rtElectricalID6ph0_Y->ElectricalID_output,
          rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC,
          rtElectricalID6ph0_DW->fv3);

        /* calculate trafo */
        /* '<S2>:940:10' current = VSD6ph(VSD,ActualValues.I_abc); */
        VSD6ph(rtElectricalID6ph0_ConstP.ElectricalID6ph_VSD,
               rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.a1,
               rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.b1,
               rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.c1,
               rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.a2,
               rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.b2,
               rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.c2,
               &rtElectricalID6ph0_DW->current.alpha,
               &rtElectricalID6ph0_DW->current.beta,
               &rtElectricalID6ph0_DW->current.x,
               &rtElectricalID6ph0_DW->current.y,
               &rtElectricalID6ph0_DW->current.z1,
               &rtElectricalID6ph0_DW->current.z2, rtElectricalID6ph0_DW);

        /* record data */
        /* '<S2>:940:12' MeasureStepResponse(ref_amplitude,current.alpha); */
        MeasureStepResponse(rtElectricalID6ph0_DW->ref_amplitude,
                            rtElectricalID6ph0_DW->current.alpha,
                            rtElectricalID6ph0_DW);

        /* '<S2>:940:13' counter = counter +1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     case IN_stepResponse_q:
      stepResponse_q(&rtElectricalID6ph0_DW->R_est_m,
                     &rtElectricalID6ph0_DW->L_est_c, rtElectricalID6ph0_U,
                     rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);
      break;

     case IN_stop:
      /* During 'stop': '<S2>:361' */
      /* '<S2>:362:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID6ph0_DW->one_sec_transition_counter ==
          rtElectricalID6ph0_DW->counter) {
        /* Transition: '<S2>:362' */
        rtElectricalID6ph0_DW->is_ElectricalID = IN_rotorInertiaEstimation;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'rotorInertiaEstimation': '<S2>:337' */
        /* '<S2>:337:3' ElectricalID_FOC_output.enableFOC_speed = boolean(0); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_speed = false;

        /* '<S2>:337:4' ElectricalID_FOC_output.enableFOC_current = boolean(1); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_current = true;

        /* '<S2>:337:5' counter = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S2>:337:6' ElectricalID_FOC_output.resetIntegrator = boolean(0); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.resetIntegrator = false;

        /* '<S2>:337:7' ElectricalID_FOC_output.activeState = uint16(160); */
        rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 160U;

        /* '<S2>:337:8' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        rtElectricalID6ph0_DW->R_est_m = roundf(3.0F /
          rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID6ph0_DW->R_est_m < 4.2949673E+9F) {
          if (rtElectricalID6ph0_DW->R_est_m >= 0.0F) {
            rtElectricalID6ph0_DW->wait_count = (uint32_T)
              rtElectricalID6ph0_DW->R_est_m;
          } else {
            rtElectricalID6ph0_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID6ph0_DW->wait_count = MAX_uint32_T;
        }
      } else {
        /* '<S2>:361:6' counter = counter +1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;

     default:
      /* During 'waitState': '<S2>:428' */
      /* '<S2>:905:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID6ph0_DW->one_sec_transition_counter ==
          rtElectricalID6ph0_DW->counter) {
        /* Outport: '<Root>/finishedElectricalID' */
        /* Transition: '<S2>:905' */
        /* Exit 'waitState': '<S2>:428' */
        /* '<S2>:428:19' finishedElectricalID=boolean(1); */
        rtElectricalID6ph0_Y->finishedElectricalID = true;

        /* Outport: '<Root>/enteredElectricalID' */
        /* '<S2>:428:20' enteredElectricalID=boolean(0); */
        rtElectricalID6ph0_Y->enteredElectricalID = false;

        /* '<S2>:428:21' reset_FOC_output; */
        reset_FOC_output(rtElectricalID6ph0_Y);
        rtElectricalID6ph0_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
        rtElectricalID6ph0_DW->is_c3_ElectricalID6ph0 = IN_Waiting;

        /* Entry 'Waiting': '<S2>:902' */
        /* wait for activation of */
        /* ElectricalID */
        /* donothing */
      } else {
        /* '<S2>:428:17' counter = counter + 1; */
        qY = rtElectricalID6ph0_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID6ph0_DW->counter + 1U < rtElectricalID6ph0_DW->counter)
        {
          qY = MAX_uint32_T;
        }

        rtElectricalID6ph0_DW->counter = qY;
      }
      break;
    }

    if (guard1) {
      rtElectricalID6ph0_DW->R_est_m = roundf(0.5F /
        rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR);
      if (rtElectricalID6ph0_DW->R_est_m < 4.2949673E+9F) {
        if (rtElectricalID6ph0_DW->R_est_m >= 0.0F) {
          qY = (uint32_T)rtElectricalID6ph0_DW->R_est_m;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtElectricalID6ph0_DW->counter == qY) {
        /* '<S2>:789:23' elseif(counter == uint32(0.5/GlobalConfig.sampleTimeISR)) */
        /* endtime */
        /* '<S2>:789:24' DutyCycle_mod(abs(ia_sum*(GlobalConfig.sampleTimeISR/0.1))); */
        DutyCycle_mod_d(fabsf(rtElectricalID6ph0_DW->ia_sum *
                              (rtElectricalID6ph0_U->GlobalConfig_out.sampleTimeISR
          / 0.1F)), rtElectricalID6ph0_U, rtElectricalID6ph0_DW);

        /* exec fct */
        /* '<S2>:789:25' counter  = uint32(1); */
        rtElectricalID6ph0_DW->counter = 1U;

        /* '<S2>:789:26' ia_sum = single(0.0); */
        rtElectricalID6ph0_DW->ia_sum = 0.0F;
      }
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
}

/* Model step function */
void ElectricalID6ph0_step(RT_MODEL_ElectricalID6ph0_t *const
  rtElectricalID6ph0_M)
{
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW = rtElectricalID6ph0_M->dwork;
  ExtU_ElectricalID6ph0_t *rtElectricalID6ph0_U = (ExtU_ElectricalID6ph0_t *)
    rtElectricalID6ph0_M->inputs;
  ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y = (ExtY_ElectricalID6ph0_t *)
    rtElectricalID6ph0_M->outputs;

  /* BusCreator generated from: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/dutyCyc'
   *  Inport: '<Root>/goertzlAmp'
   *  Inport: '<Root>/goertzlFreq'
   *  Inport: '<Root>/identLq'
   *  Inport: '<Root>/min_n_ratio'
   *  Inport: '<Root>/n_ref_measurement'
   */
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.goertzlFreq =
    rtElectricalID6ph0_U->goertzlFreq;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.dutyCyc =
    rtElectricalID6ph0_U->dutyCyc;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.n_ref_measurement =
    rtElectricalID6ph0_U->n_ref_measurement;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.identLq =
    rtElectricalID6ph0_U->identLq;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.goertzlAmp =
    rtElectricalID6ph0_U->goertzlAmp;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.min_n_ratio =
    rtElectricalID6ph0_U->min_n_ratio;

  /* BusCreator generated from: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/a1'
   *  Inport: '<Root>/a2'
   *  Inport: '<Root>/b1'
   *  Inport: '<Root>/b2'
   *  Inport: '<Root>/c1'
   *  Inport: '<Root>/c2'
   */
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.a1 =
    rtElectricalID6ph0_U->a1;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.b1 =
    rtElectricalID6ph0_U->b1;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.c1 =
    rtElectricalID6ph0_U->c1;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.a2 =
    rtElectricalID6ph0_U->a2;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.b2 =
    rtElectricalID6ph0_U->b2;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_abc.c2 =
    rtElectricalID6ph0_U->c2;

  /* BusCreator generated from: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/a1b'
   *  Inport: '<Root>/a2b'
   *  Inport: '<Root>/b1b'
   *  Inport: '<Root>/b2b'
   *  Inport: '<Root>/c1b'
   *  Inport: '<Root>/c2b'
   */
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.a1 =
    rtElectricalID6ph0_U->a1_n;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.b1 =
    rtElectricalID6ph0_U->b1_c;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.c1 =
    rtElectricalID6ph0_U->c1_i;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.a2 =
    rtElectricalID6ph0_U->a2_k;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.b2 =
    rtElectricalID6ph0_U->b2_f;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.I_abc.c2 =
    rtElectricalID6ph0_U->c2_d;

  /* BusCreator generated from: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/d'
   *  Inport: '<Root>/q'
   *  Inport: '<Root>/x'
   *  Inport: '<Root>/y'
   *  Inport: '<Root>/z1'
   *  Inport: '<Root>/z2'
   */
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.d =
    rtElectricalID6ph0_U->d;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.q =
    rtElectricalID6ph0_U->q;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.x =
    rtElectricalID6ph0_U->x;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.y =
    rtElectricalID6ph0_U->y;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.z1 =
    rtElectricalID6ph0_U->z1;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.i_dq.z2 =
    rtElectricalID6ph0_U->z2;

  /* BusCreator generated from: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/db'
   *  Inport: '<Root>/qb'
   *  Inport: '<Root>/xb'
   *  Inport: '<Root>/yb'
   *  Inport: '<Root>/z1b'
   *  Inport: '<Root>/z2b'
   */
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.d =
    rtElectricalID6ph0_U->d_b;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.q =
    rtElectricalID6ph0_U->q_n;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.x =
    rtElectricalID6ph0_U->x_i;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.y =
    rtElectricalID6ph0_U->y_p;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.z1 =
    rtElectricalID6ph0_U->z1_f;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.v_dq.z2 =
    rtElectricalID6ph0_U->z2_i;

  /* BusCreator generated from: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/V_DC'
   *  Inport: '<Root>/omega_el'
   *  Inport: '<Root>/omega_m'
   *  Inport: '<Root>/theta_el'
   *  Inport: '<Root>/theta_m'
   */
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.omega_m =
    rtElectricalID6ph0_U->omega_m;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.omega_el =
    rtElectricalID6ph0_U->omega_el;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.theta_m =
    rtElectricalID6ph0_U->theta_m;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.theta_el =
    rtElectricalID6ph0_U->theta_el;
  rtElectricalID6ph0_DW->BusConversion_InsertedFor_Elect.V_DC =
    rtElectricalID6ph0_U->V_DC;

  /* Chart: '<S1>/ElectricalID6ph' incorporates:
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
  /* Gateway: ElectricalID6ph/ElectricalID6ph */
  /* During: ElectricalID6ph/ElectricalID6ph */
  if (rtElectricalID6ph0_DW->is_active_c3_ElectricalID6ph0 == 0U) {
    /* Entry: ElectricalID6ph/ElectricalID6ph */
    rtElectricalID6ph0_DW->is_active_c3_ElectricalID6ph0 = 1U;

    /* Entry Internal: ElectricalID6ph/ElectricalID6ph */
    /* Transition: '<S2>:897' */
    rtElectricalID6ph0_DW->is_c3_ElectricalID6ph0 = IN_Waiting;

    /* Entry 'Waiting': '<S2>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else if (rtElectricalID6ph0_DW->is_c3_ElectricalID6ph0 == IN_ElectricalID) {
    ElectricalID(rtElectricalID6ph0_U, rtElectricalID6ph0_Y,
                 rtElectricalID6ph0_DW);

    /* During 'Waiting': '<S2>:902' */
    /* '<S2>:899:1' sf_internal_predicateOutput = ControlFlags.startElectricalID==1 &&.... */
    /* '<S2>:899:2'  GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
  } else if (rtElectricalID6ph0_U->ControlFlags.startElectricalID &&
             (!rtElectricalID6ph0_U->GlobalConfig_out.Reset) &&
             rtElectricalID6ph0_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S2>:899' */
    rtElectricalID6ph0_DW->is_c3_ElectricalID6ph0 = IN_ElectricalID;

    /* Entry 'ElectricalID': '<S2>:761' */
    /* '<S2>:761:3' initParams; */
    initParams(&rtElectricalID6ph0_DW->R_est, &rtElectricalID6ph0_DW->L_est,
               rtElectricalID6ph0_U, rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S2>:761:4' ElectricalID_FOC_output.activeState = uint16(100); */
    /* '<S2>:761:5' enteredElectricalID=boolean(1); */
    rtElectricalID6ph0_Y->enteredElectricalID = true;

    /* Entry Internal 'ElectricalID': '<S2>:761' */
    /* Transition: '<S2>:243' */
    rtElectricalID6ph0_DW->is_ElectricalID = IN_evaluate_Turn_DC;

    /* Entry 'evaluate_Turn_DC': '<S2>:379' */
    /* '<S2>:379:3' ElectricalID_FOC_output.activeState = uint16(110); */
    rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 110U;

    /* '<S2>:379:4' counter = uint32(1); */
    rtElectricalID6ph0_DW->counter = 1U;

    /* '<S2>:379:5' omega_register=single(zeros(5,1)); */
    for (rtElectricalID6ph0_DW->i = 0; rtElectricalID6ph0_DW->i < 5;
         rtElectricalID6ph0_DW->i++) {
      rtElectricalID6ph0_DW->omega_register[rtElectricalID6ph0_DW->i] = 0.0F;
    }

    /* '<S2>:379:6' if(ElectricalIDConfig.dutyCyc > 0.0) */
    if (rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.dutyCyc > 0.0F) {
      /* Checks if a manual value for the DutyCycle was set */
      /* '<S2>:379:7' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
      rtElectricalID6ph0_DW->DutyCycle =
        rtElectricalID6ph0_DW->BusConversion_InsertedFor_Ele_n.dutyCyc;

      /* '<S2>:379:8' DC_manual = boolean(1); */
      rtElectricalID6ph0_DW->DC_manual = true;
    } else {
      /* '<S2>:379:9' else */
      /* '<S2>:379:10' DutyCycle = single(0.01); */
      rtElectricalID6ph0_DW->DutyCycle = 0.01F;
    }

    /* '<S2>:914:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtElectricalID6ph0_U->GlobalConfig_out.Reset) {
    /* Transition: '<S2>:914' */
    /* '<S2>:914:2' finishedElectricalID=boolean(0); */
    /* '<S2>:914:3' enteredElectricalID=boolean(0); */
    /* '<S2>:914:4' initParams; */
    initParams(&rtElectricalID6ph0_DW->R_est, &rtElectricalID6ph0_DW->L_est,
               rtElectricalID6ph0_U, rtElectricalID6ph0_Y, rtElectricalID6ph0_DW);
    rtElectricalID6ph0_DW->is_c3_ElectricalID6ph0 = IN_Waiting;

    /* Entry 'Waiting': '<S2>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  }

  /* End of Chart: '<S1>/ElectricalID6ph' */
}

/* Model initialize function */
void ElectricalID6ph0_initialize(RT_MODEL_ElectricalID6ph0_t *const
  rtElectricalID6ph0_M)
{
  DW_ElectricalID6ph0_t *rtElectricalID6ph0_DW = rtElectricalID6ph0_M->dwork;
  ExtY_ElectricalID6ph0_t *rtElectricalID6ph0_Y = (ExtY_ElectricalID6ph0_t *)
    rtElectricalID6ph0_M->outputs;

  /* SystemInitialize for Chart: '<S1>/ElectricalID6ph' incorporates:
   *  Outport: '<Root>/ElectricalID_FOC_output'
   *  Outport: '<Root>/ElectricalID_output'
   */
  rtElectricalID6ph0_DW->current.alpha = 0.0F;
  rtElectricalID6ph0_DW->current.beta = 0.0F;
  rtElectricalID6ph0_DW->current.x = 0.0F;
  rtElectricalID6ph0_DW->current.y = 0.0F;
  rtElectricalID6ph0_DW->current.z1 = 0.0F;
  rtElectricalID6ph0_DW->current.z2 = 0.0F;
  rtElectricalID6ph0_DW->ActualVabc.a1 = 0.0F;
  rtElectricalID6ph0_DW->ActualVabc.b1 = 0.0F;
  rtElectricalID6ph0_DW->ActualVabc.c1 = 0.0F;
  rtElectricalID6ph0_DW->ActualVabc.a2 = 0.0F;
  rtElectricalID6ph0_DW->ActualVabc.b2 = 0.0F;
  rtElectricalID6ph0_DW->ActualVabc.c2 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.activeState = 0U;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_speed = false;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.enableFOC_current = false;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.resetIntegrator = false;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_id_out = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_iq_out = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Kp_n_out = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_id_out = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_iq_out = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_FOC_output.Ki_n_out = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a1 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b1 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c1 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_a2 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_b2 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PWM_Switch_c2 = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[0] = false;
  rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[1] = false;
  rtElectricalID6ph0_Y->ElectricalID_output.enable_TriState[2] = false;
  rtElectricalID6ph0_Y->ElectricalID_output.thetaOffset = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.R_ph_Ohm = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Ld_Henry = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Lq_Henry = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.Psi_PM_Vs = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.polePairs = 0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.J_kg_m_squared =
    0.0F;
  rtElectricalID6ph0_Y->ElectricalID_output.PMSM_parameters.I_max_Ampere = 0.0F;

  /* '<S2>:922:7' sineCounter = uint32(0); */
  /* initialize */
  /* '<S2>:922:8' u = single(0); */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
