/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.c
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 3.20
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Dec  9 08:59:48 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "ElectricalID_6ph_codegen.h"
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

/* Named constants for Chart: '<S1>/ElectricalID.Subchart_Step_Response' */
#define IN_Levenberg_Marquardt         ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_stepResponse                ((uint8_T)2U)

/* Named constants for Chart: '<Root>/ElectricalID_6ph_codegen' */
#define IN_ElectricalID                ((uint8_T)1U)
#define IN_Subchart_Step_Response      ((uint8_T)1U)
#define IN_Subchart_Step_Response1     ((uint8_T)2U)
#define IN_Subchart_Step_Response2     ((uint8_T)3U)
#define IN_Subchart_Step_Response3     ((uint8_T)4U)
#define IN_Subchart_Step_Response4     ((uint8_T)5U)
#define IN_Subchart_Step_Response5     ((uint8_T)6U)
#define IN_Waiting                     ((uint8_T)2U)
#define IN_alignRotor_d_off            ((uint8_T)7U)
#define IN_alignRotor_d_off2           ((uint8_T)8U)
#define IN_alignRotor_d_on             ((uint8_T)9U)
#define IN_calculatePIcontroller       ((uint8_T)10U)
#define IN_endState                    ((uint8_T)11U)
#define IN_evaluate_Turn_DC            ((uint8_T)12U)
#define IN_findDutyCycle               ((uint8_T)13U)
#define IN_measure_psiPM               ((uint8_T)14U)
#define IN_rotorInertiaEstimation      ((uint8_T)15U)
#define IN_stop                        ((uint8_T)16U)
#define IN_waitAccept                  ((uint8_T)17U)
#define IN_waitLock                    ((uint8_T)18U)
#define IN_waitState                   ((uint8_T)19U)

extern real32_T rt_hypotf(real32_T u0, real32_T u1);

/* Forward declaration for local functions */
static void initParams(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void reset_FOC_output(ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y);
static void Subchart_St_MeasureStepRespon_n(real32_T voltage, real32_T i_dq_d,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm(const uz_ParaID_GlobalConfig_t *GlobalConfig, real32_T *
  R_est, real32_T *L_est, boolean_T *updateJ_d, real32_T *lambda_b, real32_T
  *e_n, const uint16_T *n_iters_e, real32_T H_j[4], real32_T i_est_dz[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart__f_MeasureStepRespon_a(real32_T voltage, real32_T i_dq_x,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_m(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_k, real32_T *lambda_n,
  real32_T *e_k, const uint16_T *n_iters_j1, real32_T H_c[4], real32_T i_est_d
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart_fy_MeasureStepRespon_g(real32_T voltage, real32_T i_dq_y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_j(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_l, real32_T *lambda_d,
  real32_T *e_c, const uint16_T *n_iters_j, real32_T H_os[4], real32_T i_est_p0
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchar_fy4_MeasureStepRespon_p(real32_T voltage, real32_T i_dq_z1,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_a(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_j, real32_T *lambda_p,
  real32_T *e_p, const uint16_T *n_iters_o, real32_T H_o[4], real32_T i_est_p
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subcha_fy4w_MeasureStepRespon_f(real32_T voltage, real32_T i_dq_z2,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_ak(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_e, real32_T *lambda_k,
  real32_T *e_e, const uint16_T *n_iters_d, real32_T H_d[4], real32_T i_est_h
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart_Step_Response4(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void Subch_fy4wk_MeasureStepRespon_g(real32_T voltage, real32_T i_dq_q,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_i(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ, real32_T *lambda,
  real32_T *e, const uint16_T *n_iters, real32_T H[4], real32_T i_est_e[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void RefreshDataRegister(DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void DutyCycle_mod(const real32_T om_reg_in[5],
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void TurnMotor(ExtU_ElectricalID_6ph_codegen_t
                      *rtElectricalID_6ph_codegen_U,
                      DW_ElectricalID_6ph_codegen_t
                      *rtElectricalID_6ph_codegen_DW);
static void DutyCycle_mod_e(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t *
  rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void measure_psiPM(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void goertzel(ExtU_ElectricalID_6ph_codegen_t
                     *rtElectricalID_6ph_codegen_U,
                     DW_ElectricalID_6ph_codegen_t
                     *rtElectricalID_6ph_codegen_DW);
static void ControllerParameter(uz_ParaID_Controller_Parameters_output_t
  *FOC_out_old, real32_T bandwidthCurrentControl, real32_T PMSM_config_R_ph_Ohm,
  real32_T PMSM_config_Ld_Henry, real32_T PMSM_config_Lq_Henry, real32_T
  PMSM_config_polePairs, real32_T damping, real32_T psiOverJ);
static void exit_internal_ElectricalID(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void ElectricalID(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function initParams
 * This is used instead of "after(1.0,sec) to ensure the same transition time
 * independelty of the sampletime in the c-code
 */
static void initParams(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  real32_T tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'initParams': '<S1>:88' */
  /* '<S1>:88:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F /
               rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtElectricalID_6ph_codegen_DW->one_sec_transition_counter = (uint32_T)tmp;
    } else {
      rtElectricalID_6ph_codegen_DW->one_sec_transition_counter = 0U;
    }
  } else {
    rtElectricalID_6ph_codegen_DW->one_sec_transition_counter = MAX_uint32_T;
  }

  /*  initialize variables */
  /* '<S1>:88:7' Ki_n_loc            = single(0.0); */
  /* '<S1>:88:8' Kp_n_loc            = single(0.0); */
  /* '<S1>:88:9' n_filt              = single(0.0); */
  /* '<S1>:88:10' n_ref_old           = single(0.0); */
  /* '<S1>:88:11' repetitionCounter   = uint32(0); */
  /* '<S1>:88:12' dutyCycAdj          = single(0.0); */
  /* '<S1>:88:13' counter 			= uint32(1); */
  rtElectricalID_6ph_codegen_DW->counter = 1U;

  /* '<S1>:88:14' Kp_iq_loc           = single(0.0); */
  rtElectricalID_6ph_codegen_DW->Kp_iq_loc = 0.0F;

  /* '<S1>:88:15' Ki_iq_loc           = single(0.0); */
  /* '<S1>:88:16' Kp_id_loc           = single(0.0); */
  /* '<S1>:88:17' Ki_id_loc           = single(0.0); */
  /* '<S1>:88:18' DutyCycle_filt      = single(0.0); */
  /* '<S1>:88:19' measArray1			= single(zeros(1024,1)); */
  memset(&rtElectricalID_6ph_codegen_DW->measArray1[0], 0, sizeof(real32_T) <<
         10U);

  /* '<S1>:88:20' meas_sum            = single(zeros(2,1)); */
  /* used for Friction Id */
  /* '<S1>:88:21' J2                  = single(zeros(256,5)); */
  /* '<S1>:88:22' thetaOffset         = single(0.0); */
  /* '<S1>:88:23' Vstep               = single(zeros(205,1)); */
  /* '<S1>:88:24' DutyCycle           = single(0.0); */
  rtElectricalID_6ph_codegen_DW->DutyCycle = 0.0F;

  /* '<S1>:88:25' omega_sum           = single(0); */
  rtElectricalID_6ph_codegen_DW->omega_sum = 0.0F;

  /* '<S1>:88:26' om_con              = boolean(0); */
  rtElectricalID_6ph_codegen_DW->om_con = false;

  /* '<S1>:88:27' ia_sum              = single(0); */
  rtElectricalID_6ph_codegen_DW->ia_sum = 0.0F;

  /* '<S1>:88:28' ia_valid            = boolean(0); */
  rtElectricalID_6ph_codegen_DW->ia_valid = false;

  /* '<S1>:88:29' DC_manual           = boolean(0); */
  rtElectricalID_6ph_codegen_DW->DC_manual = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* Outputs */
  /* '<S1>:88:32' ElectricalID_FOC_output.Ki_n_out                    = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_n_out = 0.0F;

  /* '<S1>:88:33' ElectricalID_FOC_output.Ki_iq_out                   = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_iq_out = 0.0F;

  /* '<S1>:88:34' ElectricalID_FOC_output.Ki_id_out                   = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_id_out = 0.0F;

  /* '<S1>:88:35' ElectricalID_FOC_output.Kp_n_out                    = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_n_out = 0.0F;

  /* '<S1>:88:36' ElectricalID_FOC_output.Kp_iq_out                   = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_iq_out = 0.0F;

  /* '<S1>:88:37' ElectricalID_FOC_output.Kp_id_out                   = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_id_out = 0.0F;

  /* '<S1>:88:38' ElectricalID_FOC_output.n_ref_FOC                   = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:88:39' ElectricalID_FOC_output.i_dq_ref.d                  = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:88:40' ElectricalID_FOC_output.i_dq_ref.q                  = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:88:41' ElectricalID_FOC_output.i_dq_ref.zero               = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:88:42' ElectricalID_FOC_output.enableFOC_speed             = boolean(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S1>:88:43' ElectricalID_FOC_output.enableFOC_current           = boolean(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_current =
    false;

  /* '<S1>:88:44' ElectricalID_FOC_output.resetIntegrator             = boolean(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = false;

  /* Outport: '<Root>/finishedElectricalID' */
  /* '<S1>:88:45' ElectricalID_FOC_output.activeState                 = uint16(0); */
  /* '<S1>:88:46' finishedElectricalID= boolean(0); */
  rtElectricalID_6ph_codegen_Y->finishedElectricalID = false;

  /* Merge: '<S1>/ Merge ' */
  /* '<S1>:88:48' ElectricalID_output.PWM_Switch_0                        = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

  /* '<S1>:88:49' ElectricalID_output.PWM_Switch_2                        = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

  /* '<S1>:88:50' ElectricalID_output.PWM_Switch_4                        = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

  /* '<S1>:88:51' ElectricalID_output.PWM_Switch_a2                        = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

  /* '<S1>:88:52' ElectricalID_output.PWM_Switch_b2                        = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

  /* '<S1>:88:53' ElectricalID_output.PWM_Switch_c2                        = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;

  /* '<S1>:88:54' ElectricalID_output.enable_TriState                     = boolean(zeros(1,3)); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] = false;
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] = false;
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] = false;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* 0 = TriState off, 1 = TriState on    */
  /* '<S1>:88:55' ElectricalID_FOC_output.activeState                     = uint16(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 0U;

  /* Merge: '<S1>/ Merge ' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S1>:88:56' ElectricalID_output.thetaOffset                         = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset = 0.0F;

  /* '<S1>:88:57' ElectricalID_output.PMSM_parameters.R_ph_Ohm            = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm =
    0.0F;

  /* '<S1>:88:58' ElectricalID_output.PMSM_parameters.Ld_Henry            = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry =
    0.0F;

  /* '<S1>:88:59' ElectricalID_output.PMSM_parameters.Lq_Henry            = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry =
    0.0F;

  /* '<S1>:88:60' ElectricalID_output.PMSM_parameters.Psi_PM_Vs           = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs =
    0.0F;

  /* '<S1>:88:61' ElectricalID_output.PMSM_parameters.polePairs           = GlobalConfig.PMSM_config.polePairs; */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs =
    rtElectricalID_6ph_codegen_U->GlobalConfig_out.PMSM_config.polePairs;

  /* '<S1>:88:62' ElectricalID_output.PMSM_parameters.J_kg_m_squared      = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared
    = 0.0F;

  /* Outport: '<Root>/enteredElectricalID' */
  /* '<S1>:88:63' enteredElectricalID                                     = boolean(0); */
  rtElectricalID_6ph_codegen_Y->enteredElectricalID = false;

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S1>:88:66' d        			= single(zeros(2048,1)); */
  /* '<S1>:88:67' dp      			= single(zeros(2,1)); */
  /* '<S1>:88:68' e       			= single(0); */
  /* '<S1>:88:69' e_lm  				= single(0); */
  /* '<S1>:88:70' H 					= single(zeros(2,2)); */
  /* '<S1>:88:71' i_est 				= single(zeros(2048,1)); */
  memset(&rtElectricalID_6ph_codegen_DW->d[0], 0, sizeof(real32_T) << 11U);
  memset(&rtElectricalID_6ph_codegen_DW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S1>:88:72' it 					= uint16(0); */
  /* '<S1>:88:73' J 					= single(zeros(2048,2)); */
  /* '<S1>:88:74' k 					= single(0); */
  /* '<S1>:88:75' L0 					= single(0); */
  /* '<S1>:88:76' L_est   			= single(0); */
  rtElectricalID_6ph_codegen_DW->L_est_mb = 0.0F;

  /* '<S1>:88:77' L_lm 				= single(0); */
  /* '<S1>:88:78' Ndata  				= uint16(512); */
  /* '<S1>:88:79' Nparams 			= uint16(2); */
  /* '<S1>:88:80' n_iters 			= uint16(100); */
  /* '<S1>:88:81' R0 					= single(0); */
  /* '<S1>:88:82' R_est 				= single(0); */
  rtElectricalID_6ph_codegen_DW->R_est_c = 0.0F;

  /* '<S1>:88:83' R_lm 				= single(0); */
  /* '<S1>:88:84' V0 					= single(0); */
  /* '<S1>:88:85' lambda  			= single(0.01); */
  /* '<S1>:88:86' updateJ 			= boolean(1); */
  /*  initialize varaibles for PMSM parameters */
  /* '<S1>:88:89' R_corr              = single(0.000); */
  /* 0.060 */
  /*  variables for controller calculation */
  /* '<S1>:88:92' bandwidthCurrentControl = single(1000); */
  rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl = 1000.0F;

  /* '<S1>:88:93' dampingFactor           = single(10.0); */
  rtElectricalID_6ph_codegen_DW->dampingFactor = 10.0F;

  /* '<S1>:88:94' psiOverJ                = single(5000); */
  rtElectricalID_6ph_codegen_DW->psiOverJ = 5000.0F;
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function reset_FOC_output
 * Outputs
 */
static void reset_FOC_output(ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y)
{
  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* MATLAB Function 'reset_FOC_output': '<S1>:920' */
  /* '<S1>:920:4' ElectricalID_FOC_output.n_ref_FOC           = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:920:5' ElectricalID_FOC_output.i_dq_ref.d          = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:920:6' ElectricalID_FOC_output.i_dq_ref.q          = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:920:7' ElectricalID_FOC_output.i_dq_ref.zero       = single(0.0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:920:8' ElectricalID_FOC_output.enableFOC_speed     = boolean(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed = false;

  /* '<S1>:920:9' ElectricalID_FOC_output.enableFOC_current   = boolean(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_current =
    false;

  /* '<S1>:920:10' ElectricalID_FOC_output.resetIntegrator     = boolean(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = false;

  /* '<S1>:920:11' ElectricalID_FOC_output.activeState         = uint16(0); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 0U;

  /* '<S1>:920:12' TwoMassID_FOC_output.Kp_id_out              = single(Kp_id_loc); */
  /* '<S1>:920:13' TwoMassID_FOC_output.Kp_iq_out              = single(Kp_iq_loc); */
  /* '<S1>:920:14' TwoMassID_FOC_output.Kp_n_out               = single(Kp_n_loc); */
  /* '<S1>:920:15' TwoMassID_FOC_output.Ki_id_out              = single(Ki_id_loc); */
  /* '<S1>:920:16' TwoMassID_FOC_output.Ki_iq_out              = single(Ki_iq_loc); */
  /* '<S1>:920:17' TwoMassID_FOC_output.Ki_n_out               = single(Ki_n_loc); */
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response'
 * function MeasureStepResponse(voltage,i_dq)
 */
static void Subchart_St_MeasureStepRespon_n(real32_T voltage, real32_T i_dq_d,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'Subchart_St_MeasureStepResponse': '<S2>:39' */
  /* '<S2>:39:2' fns = fieldnames(i_dq); */
  /* '<S2>:39:3' current = i_dq.(fns{index}); */
  /* '<S2>:39:4' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_ha <= 1024U) {
    /* '<S2>:39:5' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_ha > 1U) {
      uint32_T qY;

      /* '<S2>:39:6' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_ha - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_ha - 1U >
          rtElectricalID_6ph_codegen_DW->counter_ha) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_p[(int32_T)qY - 1] =
        i_dq_d;

      /* safe 1024 current values to 2D array */
      /* '<S2>:39:7' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_ha -
          rtElectricalID_6ph_codegen_DW->counter_ha / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S2>:39:8' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_d - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_d - 1U >
            rtElectricalID_6ph_codegen_DW->z_d) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_f[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S2>:39:9' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_d + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_d + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_d = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_ha == 1U) {
      uint32_T qY;

      /* '<S2>:39:11' elseif(counter == 1) */
      /* '<S2>:39:12' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_f[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S2>:39:13' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_d + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_d + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_d = (uint16_T)qY;
    }

    /* '<S2>:39:15' else */
    /* '<S2>:39:16' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_ha == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S2>:39:17' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_ha - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_ha - 1U >
        rtElectricalID_6ph_codegen_DW->counter_ha) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_p[(int32_T)qY - 1] =
      i_dq_d;

    /* safe last current val */
    /* '<S2>:39:18' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_d - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_d - 1U >
        rtElectricalID_6ph_codegen_DW->z_d) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_f[(int32_T)qY - 1] = voltage;

    /* '<S2>:39:19' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_f[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_f[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_k = x / 205.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm(const uz_ParaID_GlobalConfig_t *GlobalConfig, real32_T *
  R_est, real32_T *L_est, boolean_T *updateJ_d, real32_T *lambda_b, real32_T
  *e_n, const uint16_T *n_iters_e, real32_T H_j[4], real32_T i_est_dz[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;

  /* MATLAB Function 'LM_algorithm': '<S2>:36' */
  /* '<S2>:36:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S2>:36:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S2>:36:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S2>:36:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S2>:36:25' for it=uint16(1):n_iters */
  for (it = 0; it < *n_iters_e; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S2>:36:26' if updateJ == 1 */
    if (*updateJ_d) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S2>:36:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S2>:36:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S2>:36:40' d(1:1024) = current_meas_array(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* '<S2>:36:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S2>:36:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S2>:36:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S2>:36:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S2>:36:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        r = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                   GlobalConfig->sampleTimeISR) / *L_est);
        rtElectricalID_6ph_codegen_DW->J_c[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_k) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_c[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S2>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_dz[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_k / *R_est);
        rtElectricalID_6ph_codegen_DW->d_f[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_p[k] - i_est_dz[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S2>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_j[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_j[tmp] += rtElectricalID_6ph_codegen_DW->J_c[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_c[(i << 11) + i_0];
          }
        }
      }

      /* '<S2>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S2>:36:44' e = dot(d,d); */
        *e_n = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_n += rtElectricalID_6ph_codegen_DW->d_f[k] *
            rtElectricalID_6ph_codegen_DW->d_f[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S2>:36:49' H(1,1) = H(1,1) + lambda; */
    H_j[0] += *lambda_b;

    /* '<S2>:36:50' H(2,2)=H(2,2)+lambda; */
    H_j[3] += *lambda_b;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S2>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_c[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_c[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_f[k];
    }

    if (fabsf(H_j[1]) > fabsf(H_j[0])) {
      r = H_j[0] / H_j[1];
      t = 1.0F / (r * H_j[3] - H_j[2]);
      b_y_idx_0 = H_j[3] / H_j[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_j[2] / H_j[1] * t;
      t *= r;
    } else {
      r = H_j[1] / H_j[0];
      t = 1.0F / (H_j[3] - r * H_j[2]);
      b_y_idx_0 = H_j[3] / H_j[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_j[2] / H_j[0] * t;
    }

    /* '<S2>:36:54' R_lm = R_est + dp(1); */
    r = (-b_y_idx_0 * e_lm + -b_y_idx_2 * y_idx_1) + *R_est;

    /* '<S2>:36:55' L_lm = L_est + dp(2); */
    t = (-b_y_idx_1 * e_lm + -t * y_idx_1) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S2>:36:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S2>:36:62' d(1:1024) = current_meas_array(1:1024) - i_est(1:1024); */
    /* '<S2>:36:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* '<S2>:36:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      i_est_dz[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_k / r);
      rtElectricalID_6ph_codegen_DW->d_f[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_p[k] - i_est_dz[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_f[k] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S2>:36:66' if e_lm < e */
    if (e_lm < *e_n) {
      /* '<S2>:36:67' lambda = lambda/10; */
      *lambda_b /= 10.0F;

      /* '<S2>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S2>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S2>:36:70' e = e_lm; */
      *e_n = e_lm;

      /* '<S2>:36:71' updateJ = boolean(1); */
      *updateJ_d = true;
    } else {
      /* '<S2>:36:72' else */
      /* '<S2>:36:73' updateJ = boolean(0); */
      *updateJ_d = false;

      /* '<S2>:36:74' lambda = lambda*10; */
      *lambda_b *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response1'
 * function MeasureStepResponse(voltage,i_dq)
 */
static void Subchart__f_MeasureStepRespon_a(real32_T voltage, real32_T i_dq_x,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'Subchart__f_MeasureStepResponse': '<S3>:39' */
  /* '<S3>:39:2' fns = fieldnames(i_dq); */
  /* '<S3>:39:3' current = i_dq.(fns{index}); */
  /* '<S3>:39:4' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_a <= 1024U) {
    /* '<S3>:39:5' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_a > 1U) {
      uint32_T qY;

      /* '<S3>:39:6' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_a - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_a - 1U >
          rtElectricalID_6ph_codegen_DW->counter_a) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_ny[(int32_T)qY - 1] =
        i_dq_x;

      /* safe 1024 current values to 2D array */
      /* '<S3>:39:7' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_a -
          rtElectricalID_6ph_codegen_DW->counter_a / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S3>:39:8' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_m - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_m - 1U >
            rtElectricalID_6ph_codegen_DW->z_m) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_c[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S3>:39:9' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_m + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_m + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_m = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_a == 1U) {
      uint32_T qY;

      /* '<S3>:39:11' elseif(counter == 1) */
      /* '<S3>:39:12' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_c[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S3>:39:13' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_m + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_m + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_m = (uint16_T)qY;
    }

    /* '<S3>:39:15' else */
    /* '<S3>:39:16' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_a == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S3>:39:17' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_a - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_a - 1U >
        rtElectricalID_6ph_codegen_DW->counter_a) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_ny[(int32_T)qY - 1] =
      i_dq_x;

    /* safe last current val */
    /* '<S3>:39:18' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_m - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_m - 1U >
        rtElectricalID_6ph_codegen_DW->z_m) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_c[(int32_T)qY - 1] = voltage;

    /* '<S3>:39:19' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_c[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_c[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_h = x / 205.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response1'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_m(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_k, real32_T *lambda_n,
  real32_T *e_k, const uint16_T *n_iters_j1, real32_T H_c[4], real32_T i_est_d
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;

  /* MATLAB Function 'LM_algorithm': '<S3>:36' */
  /* '<S3>:36:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S3>:36:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S3>:36:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S3>:36:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S3>:36:25' for it=uint16(1):n_iters */
  for (it = 0; it < *n_iters_j1; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S3>:36:26' if updateJ == 1 */
    if (*updateJ_k) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S3>:36:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S3>:36:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S3>:36:40' d(1:1024) = current_meas_array(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* '<S3>:36:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S3>:36:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S3>:36:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S3>:36:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S3>:36:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        r = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                   GlobalConfig->sampleTimeISR) / *L_est);
        rtElectricalID_6ph_codegen_DW->J_l[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_h) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_h *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_l[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_h *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S3>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_d[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_h / *R_est);
        rtElectricalID_6ph_codegen_DW->d_i[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_ny[k] - i_est_d[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S3>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_c[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_c[tmp] += rtElectricalID_6ph_codegen_DW->J_l[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_l[(i << 11) + i_0];
          }
        }
      }

      /* '<S3>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S3>:36:44' e = dot(d,d); */
        *e_k = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_k += rtElectricalID_6ph_codegen_DW->d_i[k] *
            rtElectricalID_6ph_codegen_DW->d_i[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S3>:36:49' H(1,1) = H(1,1) + lambda; */
    H_c[0] += *lambda_n;

    /* '<S3>:36:50' H(2,2)=H(2,2)+lambda; */
    H_c[3] += *lambda_n;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S3>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_l[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_i[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_l[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_i[k];
    }

    if (fabsf(H_c[1]) > fabsf(H_c[0])) {
      r = H_c[0] / H_c[1];
      t = 1.0F / (r * H_c[3] - H_c[2]);
      b_y_idx_0 = H_c[3] / H_c[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_c[2] / H_c[1] * t;
      t *= r;
    } else {
      r = H_c[1] / H_c[0];
      t = 1.0F / (H_c[3] - r * H_c[2]);
      b_y_idx_0 = H_c[3] / H_c[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_c[2] / H_c[0] * t;
    }

    /* '<S3>:36:54' R_lm = R_est + dp(1); */
    r = (-b_y_idx_0 * e_lm + -b_y_idx_2 * y_idx_1) + *R_est;

    /* '<S3>:36:55' L_lm = L_est + dp(2); */
    t = (-b_y_idx_1 * e_lm + -t * y_idx_1) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S3>:36:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S3>:36:62' d(1:1024) = current_meas_array(1:1024) - i_est(1:1024); */
    /* '<S3>:36:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* '<S3>:36:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      i_est_d[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_h / r);
      rtElectricalID_6ph_codegen_DW->d_i[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_ny[k] - i_est_d[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_i[k] *
        rtElectricalID_6ph_codegen_DW->d_i[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S3>:36:66' if e_lm < e */
    if (e_lm < *e_k) {
      /* '<S3>:36:67' lambda = lambda/10; */
      *lambda_n /= 10.0F;

      /* '<S3>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S3>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S3>:36:70' e = e_lm; */
      *e_k = e_lm;

      /* '<S3>:36:71' updateJ = boolean(1); */
      *updateJ_k = true;
    } else {
      /* '<S3>:36:72' else */
      /* '<S3>:36:73' updateJ = boolean(0); */
      *updateJ_k = false;

      /* '<S3>:36:74' lambda = lambda*10; */
      *lambda_n *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response2'
 * function MeasureStepResponse(voltage,i_dq)
 */
static void Subchart_fy_MeasureStepRespon_g(real32_T voltage, real32_T i_dq_y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'Subchart_fy_MeasureStepResponse': '<S4>:39' */
  /* '<S4>:39:2' fns = fieldnames(i_dq); */
  /* '<S4>:39:3' current = i_dq.(fns{index}); */
  /* '<S4>:39:4' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_k <= 1024U) {
    /* '<S4>:39:5' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_k > 1U) {
      uint32_T qY;

      /* '<S4>:39:6' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_k - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_k - 1U >
          rtElectricalID_6ph_codegen_DW->counter_k) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_o[(int32_T)qY - 1] =
        i_dq_y;

      /* safe 1024 current values to 2D array */
      /* '<S4>:39:7' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_k -
          rtElectricalID_6ph_codegen_DW->counter_k / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S4>:39:8' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_n - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_n - 1U >
            rtElectricalID_6ph_codegen_DW->z_n) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_a[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S4>:39:9' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_n + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_n + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_n = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_k == 1U) {
      uint32_T qY;

      /* '<S4>:39:11' elseif(counter == 1) */
      /* '<S4>:39:12' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_a[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S4>:39:13' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_n + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_n + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_n = (uint16_T)qY;
    }

    /* '<S4>:39:15' else */
    /* '<S4>:39:16' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_k == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S4>:39:17' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_k - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_k - 1U >
        rtElectricalID_6ph_codegen_DW->counter_k) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_o[(int32_T)qY - 1] =
      i_dq_y;

    /* safe last current val */
    /* '<S4>:39:18' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_n - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_n - 1U >
        rtElectricalID_6ph_codegen_DW->z_n) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_a[(int32_T)qY - 1] = voltage;

    /* '<S4>:39:19' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_a[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_a[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_b = x / 205.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response2'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_j(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_l, real32_T *lambda_d,
  real32_T *e_c, const uint16_T *n_iters_j, real32_T H_os[4], real32_T i_est_p0
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;

  /* MATLAB Function 'LM_algorithm': '<S4>:36' */
  /* '<S4>:36:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S4>:36:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S4>:36:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S4>:36:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S4>:36:25' for it=uint16(1):n_iters */
  for (it = 0; it < *n_iters_j; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S4>:36:26' if updateJ == 1 */
    if (*updateJ_l) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S4>:36:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S4>:36:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S4>:36:40' d(1:1024) = current_meas_array(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* '<S4>:36:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S4>:36:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S4>:36:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S4>:36:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S4>:36:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        r = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                   GlobalConfig->sampleTimeISR) / *L_est);
        rtElectricalID_6ph_codegen_DW->J_h[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_b) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_b *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_h[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_b *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S4>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_p0[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_b / *R_est);
        rtElectricalID_6ph_codegen_DW->d_d[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_o[k] - i_est_p0[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S4>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_os[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_os[tmp] += rtElectricalID_6ph_codegen_DW->J_h[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_h[(i << 11) + i_0];
          }
        }
      }

      /* '<S4>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S4>:36:44' e = dot(d,d); */
        *e_c = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_c += rtElectricalID_6ph_codegen_DW->d_d[k] *
            rtElectricalID_6ph_codegen_DW->d_d[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S4>:36:49' H(1,1) = H(1,1) + lambda; */
    H_os[0] += *lambda_d;

    /* '<S4>:36:50' H(2,2)=H(2,2)+lambda; */
    H_os[3] += *lambda_d;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S4>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_h[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_d[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_h[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_d[k];
    }

    if (fabsf(H_os[1]) > fabsf(H_os[0])) {
      r = H_os[0] / H_os[1];
      t = 1.0F / (r * H_os[3] - H_os[2]);
      b_y_idx_0 = H_os[3] / H_os[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_os[2] / H_os[1] * t;
      t *= r;
    } else {
      r = H_os[1] / H_os[0];
      t = 1.0F / (H_os[3] - r * H_os[2]);
      b_y_idx_0 = H_os[3] / H_os[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_os[2] / H_os[0] * t;
    }

    /* '<S4>:36:54' R_lm = R_est + dp(1); */
    r = (-b_y_idx_0 * e_lm + -b_y_idx_2 * y_idx_1) + *R_est;

    /* '<S4>:36:55' L_lm = L_est + dp(2); */
    t = (-b_y_idx_1 * e_lm + -t * y_idx_1) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S4>:36:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S4>:36:62' d(1:1024) = current_meas_array(1:1024) - i_est(1:1024); */
    /* '<S4>:36:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* '<S4>:36:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      i_est_p0[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_b / r);
      rtElectricalID_6ph_codegen_DW->d_d[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_o[k] - i_est_p0[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_d[k] *
        rtElectricalID_6ph_codegen_DW->d_d[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S4>:36:66' if e_lm < e */
    if (e_lm < *e_c) {
      /* '<S4>:36:67' lambda = lambda/10; */
      *lambda_d /= 10.0F;

      /* '<S4>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S4>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S4>:36:70' e = e_lm; */
      *e_c = e_lm;

      /* '<S4>:36:71' updateJ = boolean(1); */
      *updateJ_l = true;
    } else {
      /* '<S4>:36:72' else */
      /* '<S4>:36:73' updateJ = boolean(0); */
      *updateJ_l = false;

      /* '<S4>:36:74' lambda = lambda*10; */
      *lambda_d *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response3'
 * function MeasureStepResponse(voltage,i_dq)
 */
static void Subchar_fy4_MeasureStepRespon_p(real32_T voltage, real32_T i_dq_z1,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'Subchar_fy4_MeasureStepResponse': '<S5>:39' */
  /* '<S5>:39:2' fns = fieldnames(i_dq); */
  /* '<S5>:39:3' current = i_dq.(fns{index}); */
  /* '<S5>:39:4' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_l <= 1024U) {
    /* '<S5>:39:5' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_l > 1U) {
      uint32_T qY;

      /* '<S5>:39:6' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_l - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_l - 1U >
          rtElectricalID_6ph_codegen_DW->counter_l) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_n[(int32_T)qY - 1] =
        i_dq_z1;

      /* safe 1024 current values to 2D array */
      /* '<S5>:39:7' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_l -
          rtElectricalID_6ph_codegen_DW->counter_l / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S5>:39:8' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_g - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_g - 1U >
            rtElectricalID_6ph_codegen_DW->z_g) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_d[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S5>:39:9' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_g + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_g + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_g = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_l == 1U) {
      uint32_T qY;

      /* '<S5>:39:11' elseif(counter == 1) */
      /* '<S5>:39:12' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_d[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S5>:39:13' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_g + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_g + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_g = (uint16_T)qY;
    }

    /* '<S5>:39:15' else */
    /* '<S5>:39:16' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_l == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S5>:39:17' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_l - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_l - 1U >
        rtElectricalID_6ph_codegen_DW->counter_l) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_n[(int32_T)qY - 1] =
      i_dq_z1;

    /* safe last current val */
    /* '<S5>:39:18' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_g - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_g - 1U >
        rtElectricalID_6ph_codegen_DW->z_g) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_d[(int32_T)qY - 1] = voltage;

    /* '<S5>:39:19' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_d[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_d[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_m = x / 205.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response3'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_a(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_j, real32_T *lambda_p,
  real32_T *e_p, const uint16_T *n_iters_o, real32_T H_o[4], real32_T i_est_p
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;

  /* MATLAB Function 'LM_algorithm': '<S5>:36' */
  /* '<S5>:36:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S5>:36:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S5>:36:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S5>:36:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S5>:36:25' for it=uint16(1):n_iters */
  for (it = 0; it < *n_iters_o; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S5>:36:26' if updateJ == 1 */
    if (*updateJ_j) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S5>:36:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S5>:36:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S5>:36:40' d(1:1024) = current_meas_array(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* '<S5>:36:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S5>:36:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S5>:36:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S5>:36:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S5>:36:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        r = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                   GlobalConfig->sampleTimeISR) / *L_est);
        rtElectricalID_6ph_codegen_DW->J_m[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_m) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_m *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_m[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_m *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S5>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_p[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_m / *R_est);
        rtElectricalID_6ph_codegen_DW->d_b[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_n[k] - i_est_p[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S5>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_o[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_o[tmp] += rtElectricalID_6ph_codegen_DW->J_m[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_m[(i << 11) + i_0];
          }
        }
      }

      /* '<S5>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S5>:36:44' e = dot(d,d); */
        *e_p = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_p += rtElectricalID_6ph_codegen_DW->d_b[k] *
            rtElectricalID_6ph_codegen_DW->d_b[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S5>:36:49' H(1,1) = H(1,1) + lambda; */
    H_o[0] += *lambda_p;

    /* '<S5>:36:50' H(2,2)=H(2,2)+lambda; */
    H_o[3] += *lambda_p;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S5>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_m[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_b[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_m[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_b[k];
    }

    if (fabsf(H_o[1]) > fabsf(H_o[0])) {
      r = H_o[0] / H_o[1];
      t = 1.0F / (r * H_o[3] - H_o[2]);
      b_y_idx_0 = H_o[3] / H_o[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_o[2] / H_o[1] * t;
      t *= r;
    } else {
      r = H_o[1] / H_o[0];
      t = 1.0F / (H_o[3] - r * H_o[2]);
      b_y_idx_0 = H_o[3] / H_o[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_o[2] / H_o[0] * t;
    }

    /* '<S5>:36:54' R_lm = R_est + dp(1); */
    r = (-b_y_idx_0 * e_lm + -b_y_idx_2 * y_idx_1) + *R_est;

    /* '<S5>:36:55' L_lm = L_est + dp(2); */
    t = (-b_y_idx_1 * e_lm + -t * y_idx_1) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S5>:36:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S5>:36:62' d(1:1024) = current_meas_array(1:1024) - i_est(1:1024); */
    /* '<S5>:36:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* '<S5>:36:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      i_est_p[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_m / r);
      rtElectricalID_6ph_codegen_DW->d_b[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_n[k] - i_est_p[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_b[k] *
        rtElectricalID_6ph_codegen_DW->d_b[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S5>:36:66' if e_lm < e */
    if (e_lm < *e_p) {
      /* '<S5>:36:67' lambda = lambda/10; */
      *lambda_p /= 10.0F;

      /* '<S5>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S5>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S5>:36:70' e = e_lm; */
      *e_p = e_lm;

      /* '<S5>:36:71' updateJ = boolean(1); */
      *updateJ_j = true;
    } else {
      /* '<S5>:36:72' else */
      /* '<S5>:36:73' updateJ = boolean(0); */
      *updateJ_j = false;

      /* '<S5>:36:74' lambda = lambda*10; */
      *lambda_p *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response4'
 * function MeasureStepResponse(voltage,i_dq)
 */
static void Subcha_fy4w_MeasureStepRespon_f(real32_T voltage, real32_T i_dq_z2,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'Subcha_fy4w_MeasureStepResponse': '<S6>:39' */
  /* '<S6>:39:2' fns = fieldnames(i_dq); */
  /* '<S6>:39:3' current = i_dq.(fns{index}); */
  /* '<S6>:39:4' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_h <= 1024U) {
    /* '<S6>:39:5' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_h > 1U) {
      uint32_T qY;

      /* '<S6>:39:6' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_h - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_h - 1U >
          rtElectricalID_6ph_codegen_DW->counter_h) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_e[(int32_T)qY - 1] =
        i_dq_z2;

      /* safe 1024 current values to 2D array */
      /* '<S6>:39:7' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_h -
          rtElectricalID_6ph_codegen_DW->counter_h / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S6>:39:8' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_a - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_a - 1U >
            rtElectricalID_6ph_codegen_DW->z_a) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_j[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S6>:39:9' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_a + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_a + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_a = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_h == 1U) {
      uint32_T qY;

      /* '<S6>:39:11' elseif(counter == 1) */
      /* '<S6>:39:12' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_j[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S6>:39:13' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_a + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_a + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_a = (uint16_T)qY;
    }

    /* '<S6>:39:15' else */
    /* '<S6>:39:16' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_h == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S6>:39:17' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_h - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_h - 1U >
        rtElectricalID_6ph_codegen_DW->counter_h) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_e[(int32_T)qY - 1] =
      i_dq_z2;

    /* safe last current val */
    /* '<S6>:39:18' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_a - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_a - 1U >
        rtElectricalID_6ph_codegen_DW->z_a) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_j[(int32_T)qY - 1] = voltage;

    /* '<S6>:39:19' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_j[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_j[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_j = x / 205.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response4'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_ak(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_e, real32_T *lambda_k,
  real32_T *e_e, const uint16_T *n_iters_d, real32_T H_d[4], real32_T i_est_h
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;

  /* MATLAB Function 'LM_algorithm': '<S6>:36' */
  /* '<S6>:36:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S6>:36:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S6>:36:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S6>:36:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S6>:36:25' for it=uint16(1):n_iters */
  for (it = 0; it < *n_iters_d; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S6>:36:26' if updateJ == 1 */
    if (*updateJ_e) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S6>:36:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S6>:36:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S6>:36:40' d(1:1024) = current_meas_array(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* '<S6>:36:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S6>:36:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S6>:36:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S6>:36:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S6>:36:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        r = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                   GlobalConfig->sampleTimeISR) / *L_est);
        rtElectricalID_6ph_codegen_DW->J_n[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_j) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_j *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_n[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_j *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S6>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_h[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_j / *R_est);
        rtElectricalID_6ph_codegen_DW->d_g[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_e[k] - i_est_h[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S6>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_d[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_d[tmp] += rtElectricalID_6ph_codegen_DW->J_n[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_n[(i << 11) + i_0];
          }
        }
      }

      /* '<S6>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S6>:36:44' e = dot(d,d); */
        *e_e = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_e += rtElectricalID_6ph_codegen_DW->d_g[k] *
            rtElectricalID_6ph_codegen_DW->d_g[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S6>:36:49' H(1,1) = H(1,1) + lambda; */
    H_d[0] += *lambda_k;

    /* '<S6>:36:50' H(2,2)=H(2,2)+lambda; */
    H_d[3] += *lambda_k;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S6>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_n[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_g[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_n[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_g[k];
    }

    if (fabsf(H_d[1]) > fabsf(H_d[0])) {
      r = H_d[0] / H_d[1];
      t = 1.0F / (r * H_d[3] - H_d[2]);
      b_y_idx_0 = H_d[3] / H_d[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_d[2] / H_d[1] * t;
      t *= r;
    } else {
      r = H_d[1] / H_d[0];
      t = 1.0F / (H_d[3] - r * H_d[2]);
      b_y_idx_0 = H_d[3] / H_d[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_d[2] / H_d[0] * t;
    }

    /* '<S6>:36:54' R_lm = R_est + dp(1); */
    r = (-b_y_idx_0 * e_lm + -b_y_idx_2 * y_idx_1) + *R_est;

    /* '<S6>:36:55' L_lm = L_est + dp(2); */
    t = (-b_y_idx_1 * e_lm + -t * y_idx_1) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S6>:36:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S6>:36:62' d(1:1024) = current_meas_array(1:1024) - i_est(1:1024); */
    /* '<S6>:36:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* '<S6>:36:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      i_est_h[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_j / r);
      rtElectricalID_6ph_codegen_DW->d_g[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_e[k] - i_est_h[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_g[k] *
        rtElectricalID_6ph_codegen_DW->d_g[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S6>:36:66' if e_lm < e */
    if (e_lm < *e_e) {
      /* '<S6>:36:67' lambda = lambda/10; */
      *lambda_k /= 10.0F;

      /* '<S6>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S6>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S6>:36:70' e = e_lm; */
      *e_e = e_lm;

      /* '<S6>:36:71' updateJ = boolean(1); */
      *updateJ_e = true;
    } else {
      /* '<S6>:36:72' else */
      /* '<S6>:36:73' updateJ = boolean(0); */
      *updateJ_e = false;

      /* '<S6>:36:74' lambda = lambda*10; */
      *lambda_k *= 10.0F;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void Subchart_Step_Response4(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  uint16_T n_iters_d;
  boolean_T updateJ_e;

  /* Inport: '<Root>/ElectricalIDConfig' */
  /* During 'Subchart_Step_Response4': '<S1>:1017' */
  /* '<S1>:1027:1' sf_internal_predicateOutput = finish_subsystem==true&&ElectricalIDConfig.identLq == 1; */
  if (rtElectricalID_6ph_codegen_DW->finish_subsystem &&
      rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
    /* Merge: '<S1>/ Merge ' */
    /* Transition: '<S1>:1027' */
    /* '<S1>:1027:2' ElectricalID_output.inductances_6ph.z2=L_est; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z2 =
      rtElectricalID_6ph_codegen_DW->L_est_mb;

    /* '<S1>:1027:3' ElectricalID_output.resistances_6ph.z2=R_est */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z2 =
      rtElectricalID_6ph_codegen_DW->R_est_c;

    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S6>:35' */
      /* '<S6>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitLock;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'waitLock': '<S1>:1021' */
    /* '<S1>:1021:3' ElectricalID_FOC_output.activeState = uint16(147); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 147U;

    /* '<S1>:1029:1' sf_internal_predicateOutput = finish_subsystem==true&&ElectricalIDConfig.identLq == 0; */
  } else if (rtElectricalID_6ph_codegen_DW->finish_subsystem &&
             (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq)) {
    /* Merge: '<S1>/ Merge ' */
    /* Transition: '<S1>:1029' */
    /* '<S1>:1029:2' ElectricalID_output.inductances_6ph.z2=L_est; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z2 =
      rtElectricalID_6ph_codegen_DW->L_est_mb;

    /* '<S1>:1029:3' ElectricalID_output.resistances_6ph.z2=R_est; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z2 =
      rtElectricalID_6ph_codegen_DW->R_est_c;

    /* '<S1>:1029:4' ElectricalID_output.inductances_6ph.q=ElectricalID_output.inductances_6ph.d; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q =
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d;

    /* '<S1>:1029:5' ElectricalID_output.resistances_6ph.q=ElectricalID_output.resistances_6ph.d; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q =
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d;

    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S6>:35' */
      /* '<S6>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitAccept;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'waitAccept': '<S1>:1028' */
    /* '<S1>:1028:3' ElectricalID_FOC_output.activeState = uint16(148); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 148U;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:1028:4' ElectricalID_output.PMSM_parameters.Ld_Henry = ElectricalID_output.inductances_6ph.d; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry =
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d;

    /* '<S1>:1028:5' ElectricalID_output.PMSM_parameters.Lq_Henry = ElectricalID_output.inductances_6ph.q; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry =
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q;

    /* '<S1>:1028:6' ElectricalID_output.PMSM_parameters.R_ph_Ohm = ElectricalID_output.resistances_6ph.d; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm =
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d;

    /* During: Subchart_Step_Response */
  } else if (rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ !=
             IN_Levenberg_Marquardt) {
    /* During 'stepResponse': '<S6>:35' */
    /* '<S6>:32:1' sf_internal_predicateOutput = counter == 1026; */
    if (rtElectricalID_6ph_codegen_DW->counter_h == 1026U) {
      /* Transition: '<S6>:32' */
      /* Exit 'stepResponse': '<S6>:35' */
      /* '<S6>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_Levenberg_Marquardt;

      /* Entry 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->e_e = 0.0F;
      rtElectricalID_6ph_codegen_DW->H_d[0] = 0.0F;
      rtElectricalID_6ph_codegen_DW->H_d[1] = 0.0F;
      rtElectricalID_6ph_codegen_DW->H_d[2] = 0.0F;
      rtElectricalID_6ph_codegen_DW->H_d[3] = 0.0F;
      n_iters_d = 100U;
      rtElectricalID_6ph_codegen_DW->lambda_k = 0.01F;
      updateJ_e = true;
      memset(&rtElectricalID_6ph_codegen_DW->d_g[0], 0, sizeof(real32_T) << 11U);
      memset(&rtElectricalID_6ph_codegen_DW->i_est_h[0], 0, sizeof(real32_T) <<
             11U);
      memset(&rtElectricalID_6ph_codegen_DW->J_n[0], 0, sizeof(real32_T) << 12U);

      /* Inport: '<Root>/GlobalConfig' */
      /* '<S6>:40:3' LM_algorithm; */
      LM_algorithm_ak(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                      &rtElectricalID_6ph_codegen_DW->R_est_c,
                      &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_e,
                      &rtElectricalID_6ph_codegen_DW->lambda_k,
                      &rtElectricalID_6ph_codegen_DW->e_e, &n_iters_d,
                      rtElectricalID_6ph_codegen_DW->H_d,
                      rtElectricalID_6ph_codegen_DW->i_est_h,
                      rtElectricalID_6ph_codegen_DW);

      /* '<S6>:40:4' R_est = (R_est-R_corr); */
      /* '<S6>:40:5' finished_flag = true; */
      rtElectricalID_6ph_codegen_DW->finish_subsystem = true;
    } else {
      /* Inport: '<Root>/ActualValues' */
      /* '<S6>:35:12' MeasureStepResponse(ref_amplitude,ActualValues.i_dq_6ph); */
      Subcha_fy4w_MeasureStepRespon_f
        (rtElectricalID_6ph_codegen_DW->ref_amplitude,
         rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z2,
         rtElectricalID_6ph_codegen_DW);

      /* '<S6>:35:13' counter = counter +1; */
      rtElectricalID_6ph_codegen_DW->qY_b =
        rtElectricalID_6ph_codegen_DW->counter_h + /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_h + 1U <
          rtElectricalID_6ph_codegen_DW->counter_h) {
        rtElectricalID_6ph_codegen_DW->qY_b = MAX_uint32_T;
      }

      rtElectricalID_6ph_codegen_DW->counter_h =
        rtElectricalID_6ph_codegen_DW->qY_b;
    }
  } else {
    /* During 'Levenberg_Marquardt': '<S6>:40' */
  }

  /* End of Inport: '<Root>/ElectricalIDConfig' */
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response5'
 * function MeasureStepResponse(voltage,i_dq)
 */
static void Subch_fy4wk_MeasureStepRespon_g(real32_T voltage, real32_T i_dq_q,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'Subch_fy4wk_MeasureStepResponse': '<S7>:39' */
  /* '<S7>:39:2' fns = fieldnames(i_dq); */
  /* '<S7>:39:3' current = i_dq.(fns{index}); */
  /* '<S7>:39:4' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_f <= 1024U) {
    /* '<S7>:39:5' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_f > 1U) {
      uint32_T qY;

      /* '<S7>:39:6' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_f - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_f - 1U >
          rtElectricalID_6ph_codegen_DW->counter_f) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array[(int32_T)qY - 1] =
        i_dq_q;

      /* safe 1024 current values to 2D array */
      /* '<S7>:39:7' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_f -
          rtElectricalID_6ph_codegen_DW->counter_f / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S7>:39:8' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z - 1U;
        if (rtElectricalID_6ph_codegen_DW->z - 1U >
            rtElectricalID_6ph_codegen_DW->z) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep[(int32_T)qY - 1] = voltage;

        /* safe Va */
        /* '<S7>:39:9' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z + 1U;
        if (rtElectricalID_6ph_codegen_DW->z + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_f == 1U) {
      uint32_T qY;

      /* '<S7>:39:11' elseif(counter == 1) */
      /* '<S7>:39:12' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep[0] = voltage;

      /* safe Va 1st cycle */
      /* '<S7>:39:13' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z + 1U;
      if (rtElectricalID_6ph_codegen_DW->z + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z = (uint16_T)qY;
    }

    /* '<S7>:39:15' else */
    /* '<S7>:39:16' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_f == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S7>:39:17' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_f - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_f - 1U >
        rtElectricalID_6ph_codegen_DW->counter_f) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array[(int32_T)qY - 1] = i_dq_q;

    /* safe last current val */
    /* '<S7>:39:18' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z - 1U;
    if (rtElectricalID_6ph_codegen_DW->z - 1U > rtElectricalID_6ph_codegen_DW->z)
    {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep[(int32_T)qY - 1] = voltage;

    /* '<S7>:39:19' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0 = x / 205.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response5'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_i(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ, real32_T *lambda,
  real32_T *e, const uint16_T *n_iters, real32_T H[4], real32_T i_est_e[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  int32_T i_0;
  int32_T it;
  int32_T k;

  /* MATLAB Function 'LM_algorithm': '<S7>:36' */
  /* '<S7>:36:6' R0 = single(0.001000); */
  /*  Widerstand in Ohm (0.01 ... 40 Ohm) */
  /* '<S7>:36:7' L0 = single(0.000005); */
  /*  Induktivitaet in Henry (0.05mH ... 50 mH) */
  /* '<S7>:36:9' R_est   = R0; */
  *R_est = 0.001F;

  /* '<S7>:36:10' L_est   = L0; */
  *L_est = 5.0E-6F;

  /*  Levenberg-Marquardt Curve Fitting */
  /*  i_input(Stromwerte) -> Stromwerte in A !!! */
  /*  Mathematische Grundlagen mit Symbolic Toolbox erstellen */
  /* syms U R L t i real;                   %Symbolische Variablen erstellen */
  /* f = U/R*(1-exp(-R*t/L))                %Modellfunktion (Laden einer Spule) */
  /* d = i-f;                               %Fehler d = Messung - Modell */
  /* Jsym = jacobian(d,[R L])               %Jacobi-Matrix des Fehlers (Ableitungen nach den Parametern R und L)                   */
  /*  Parameterbestimmung durch Iteration */
  /* '<S7>:36:25' for it=uint16(1):n_iters */
  for (it = 0; it < *n_iters; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S7>:36:26' if updateJ == 1 */
    if (*updateJ) {
      /*  Jacobi-Matrix mit aktuellem Parametersatz berechnen */
      /* '<S7>:36:28' for k=single(1):single(1024) */
      /*  Modellfunktion mit aktuellem Parametersatz berechnen */
      /* '<S7>:36:36' for k=single(1):single(1024) */
      /*  Fehler zwischen Messdaten und Modellfunktionswerten berechnen */
      /* '<S7>:36:40' d(1:1024) = current_meas_array(1:1024)-i_est(1:1024); */
      for (k = 0; k < 1024; k++) {
        /* '<S7>:36:29' J(k,:) = [- (V0*(exp(-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est).... */
        /* '<S7>:36:30'                  - 1))/R_est^2 - (V0*(k-1)*GlobalConfig.sampleTimeISR*exp.... */
        /* '<S7>:36:31'                  (-(R_est*(k-1)*GlobalConfig.sampleTimeISR)/L_est))/(L_est*R_est).... */
        /* '<S7>:36:32'                  , (V0*(k-1)*GlobalConfig.sampleTimeISR*exp(-(R_est*(k-1)*.... */
        /* '<S7>:36:33'                  GlobalConfig.sampleTimeISR)/L_est))/L_est^2]; */
        r = expf(-((((real32_T)k + 1.0F) - 1.0F) * *R_est *
                   GlobalConfig->sampleTimeISR) / *L_est);
        rtElectricalID_6ph_codegen_DW->J[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0) / (*R_est * *R_est) - (((real32_T)k
          + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0 *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J[k + 2048] = expf(-((((real32_T)k + 1.0F)
          - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0 *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S7>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_e[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0 / *R_est);
        rtElectricalID_6ph_codegen_DW->d_a[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_e[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S7>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H[tmp] += rtElectricalID_6ph_codegen_DW->J[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J[(i << 11) + i_0];
          }
        }
      }

      /* '<S7>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S7>:36:44' e = dot(d,d); */
        *e = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e += rtElectricalID_6ph_codegen_DW->d_a[k] *
            rtElectricalID_6ph_codegen_DW->d_a[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S7>:36:49' H(1,1) = H(1,1) + lambda; */
    H[0] += *lambda;

    /* '<S7>:36:50' H(2,2)=H(2,2)+lambda; */
    H[3] += *lambda;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S7>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_a[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J[(((k + 1024) / 1024) << 11) +
        (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_a[k];
    }

    if (fabsf(H[1]) > fabsf(H[0])) {
      r = H[0] / H[1];
      t = 1.0F / (r * H[3] - H[2]);
      b_y_idx_0 = H[3] / H[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H[2] / H[1] * t;
      t *= r;
    } else {
      r = H[1] / H[0];
      t = 1.0F / (H[3] - r * H[2]);
      b_y_idx_0 = H[3] / H[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H[2] / H[0] * t;
    }

    /* '<S7>:36:54' R_lm = R_est + dp(1); */
    r = (-b_y_idx_0 * e_lm + -b_y_idx_2 * y_idx_1) + *R_est;

    /* '<S7>:36:55' L_lm = L_est + dp(2); */
    t = (-b_y_idx_1 * e_lm + -t * y_idx_1) + *L_est;

    /*  Modellfunktion mit neuem Parametersatz berechnen */
    /* '<S7>:36:58' for k=single(1):single(1024) */
    /*  Fehler und Fehlerquadrate neu berechnen */
    /* '<S7>:36:62' d(1:1024) = current_meas_array(1:1024) - i_est(1:1024); */
    /* '<S7>:36:63' e_lm = dot(d(1:1024),d(1:1024)); */
    e_lm = 0.0F;
    for (k = 0; k < 1024; k++) {
      /* '<S7>:36:59' i_est(k) = V0/R_lm*(1-exp(-R_lm*((k-1)*GlobalConfig.sampleTimeISR)/L_lm)); */
      i_est_e[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0 / r);
      rtElectricalID_6ph_codegen_DW->d_a[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_e[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_a[k] *
        rtElectricalID_6ph_codegen_DW->d_a[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S7>:36:66' if e_lm < e */
    if (e_lm < *e) {
      /* '<S7>:36:67' lambda = lambda/10; */
      *lambda /= 10.0F;

      /* '<S7>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S7>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S7>:36:70' e = e_lm; */
      *e = e_lm;

      /* '<S7>:36:71' updateJ = boolean(1); */
      *updateJ = true;
    } else {
      /* '<S7>:36:72' else */
      /* '<S7>:36:73' updateJ = boolean(0); */
      *updateJ = false;

      /* '<S7>:36:74' lambda = lambda*10; */
      *lambda *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  /* MATLAB Function 'RefreshDataRegister': '<S1>:784' */
  /* '<S1>:784:3' m=length(omega_register); */
  /* '<S1>:784:4' for k= single(0):single(m-2) */
  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_6ph_codegen_DW->omega_register[4] =
    rtElectricalID_6ph_codegen_DW->omega_register[3];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_6ph_codegen_DW->omega_register[3] =
    rtElectricalID_6ph_codegen_DW->omega_register[2];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_6ph_codegen_DW->omega_register[2] =
    rtElectricalID_6ph_codegen_DW->omega_register[1];

  /* '<S1>:784:5' omega_register(m-k)=omega_register(m-(k+1)); */
  rtElectricalID_6ph_codegen_DW->omega_register[1] =
    rtElectricalID_6ph_codegen_DW->omega_register[0];
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function DutyCycle_mod(om_reg_in)
 */
static void DutyCycle_mod(const real32_T om_reg_in[5],
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  real32_T mean_om_reg;

  /* MATLAB Function 'DutyCycle_mod': '<S1>:769' */
  /* '<S1>:769:2' mean_om_reg=mean(om_reg_in); */
  mean_om_reg = ((((om_reg_in[0] + om_reg_in[1]) + om_reg_in[2]) + om_reg_in[3])
                 + om_reg_in[4]) / 5.0F;

  /* if no manual value for the DutyCycle is set, this function determines, if the rotor is turning above */
  /* the stated minimal speed and the oscillation is below */
  /* the stated threshold */
  /* '<S1>:769:7' if(om_con==0) */
  if (!rtElectricalID_6ph_codegen_DW->om_con) {
    /* Inport: '<Root>/ElectricalIDConfig' incorporates:
     *  Inport: '<Root>/GlobalConfig'
     */
    /* '<S1>:769:8' if(mean_om_reg >(ElectricalIDConfig.min_n_ratio*GlobalConfig.ratSpeed*2*pi)/60) */
    if (mean_om_reg >
        rtElectricalID_6ph_codegen_U->ElectricalIDConfig.min_n_ratio *
        rtElectricalID_6ph_codegen_U->GlobalConfig_out.ratSpeed * 2.0F *
        3.14159274F / 60.0F) {
      real32_T ex;
      real32_T tmp;

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

      tmp = rtElectricalID_6ph_codegen_U->GlobalConfig_out.ratSpeed * 2.0F *
        3.14159274F * 0.05F / 60.0F;
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
            rtElectricalID_6ph_codegen_DW->om_con = true;
          } else {
            /* '<S1>:769:16' else */
            /* '<S1>:769:17' om_con=boolean(0); */
            rtElectricalID_6ph_codegen_DW->om_con = false;
          }
        } else {
          /* '<S1>:769:16' else */
          /* '<S1>:769:17' om_con=boolean(0); */
          rtElectricalID_6ph_codegen_DW->om_con = false;
        }
      } else {
        /* '<S1>:769:16' else */
        /* '<S1>:769:17' om_con=boolean(0); */
        rtElectricalID_6ph_codegen_DW->om_con = false;
      }
    } else {
      /* '<S1>:769:19' else */
      /* '<S1>:769:20' om_con=boolean(0); */
      rtElectricalID_6ph_codegen_DW->om_con = false;
    }

    /* End of Inport: '<Root>/ElectricalIDConfig' */
  }

  if (!rtElectricalID_6ph_codegen_DW->om_con) {
    /* Increases the DutyCycle by 1% every 2 seconds, if the motor isn't */
    /* rotating properly */
    /* '<S1>:769:26' DutyCycle = DutyCycle + 0.01; */
    rtElectricalID_6ph_codegen_DW->DutyCycle += 0.01F;

    /* Simulation 0.001 | Real 0.01 */
  }

  /* '<S1>:769:23' if(om_con == 0) */
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function TurnMotor
 */
static void TurnMotor(ExtU_ElectricalID_6ph_codegen_t
                      *rtElectricalID_6ph_codegen_U,
                      DW_ElectricalID_6ph_codegen_t
                      *rtElectricalID_6ph_codegen_DW)
{
  real32_T ElectricalID_output_tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'TurnMotor': '<S1>:380' */
  /* '<S1>:380:3' sineCounter = single(counter); */
  /* '<S1>:380:4' gamma=pi/6; */
  /*  rechtslauf */
  /* '<S1>:380:7' ElectricalID_output.PWM_Switch_0 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2)+0.5; */
  ElectricalID_output_tmp = 50.2654839F * (real32_T)
    rtElectricalID_6ph_codegen_DW->counter *
    rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR;

  /* Merge: '<S1>/ Merge ' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = sinf
    (ElectricalID_output_tmp + 1.57079637F) * (0.5F *
    rtElectricalID_6ph_codegen_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:8' ElectricalID_output.PWM_Switch_2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2)+0.5; */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = sinf
    ((ElectricalID_output_tmp - 2.09439516F) + 1.57079637F) * (0.5F *
    rtElectricalID_6ph_codegen_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:9' ElectricalID_output.PWM_Switch_4 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-4*pi/3+pi/2)+0.5; */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = sinf
    ((ElectricalID_output_tmp - 4.18879032F) + 1.57079637F) * (0.5F *
    rtElectricalID_6ph_codegen_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:10' ElectricalID_output.PWM_Switch_a2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2-gamma)+0.5; */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = sinf
    ((50.2654839F * (real32_T)rtElectricalID_6ph_codegen_DW->counter *
      rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR + 1.57079637F)
     - 0.52359879F) * (0.5F * rtElectricalID_6ph_codegen_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:11' ElectricalID_output.PWM_Switch_b2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2-gamma)+0.5; */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = sinf
    (((50.2654839F * (real32_T)rtElectricalID_6ph_codegen_DW->counter *
       rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR -
       2.09439516F) + 1.57079637F) - 0.52359879F) * (0.5F *
    rtElectricalID_6ph_codegen_DW->DutyCycle) + 0.5F;

  /* '<S1>:380:12' ElectricalID_output.PWM_Switch_c2 = 0.5*DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-4*pi/3+pi/2-gamma)+0.5; */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = sinf
    (((50.2654839F * (real32_T)rtElectricalID_6ph_codegen_DW->counter *
       rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR -
       4.18879032F) + 1.57079637F) - 0.52359879F) * (0.5F *
    rtElectricalID_6ph_codegen_DW->DutyCycle) + 0.5F;

  /*  linkslauf */
  /*  ElectricalID_output.PWM_Switch_0 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+pi/2); */
  /*  ElectricalID_output.PWM_Switch_2 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR+2*pi/3+pi/2); */
  /*  ElectricalID_output.PWM_Switch_4 = DutyCycle*sin(2*pi*8*sineCounter*GlobalConfig.sampleTimeISR-2*pi/3+pi/2); */
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function DutyCycle_mod(ia_reg_in)
 */
static void DutyCycle_mod_e(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t *
  rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'DutyCycle_mod': '<S1>:796' */
  /* '<S1>:796:3' mean_ia_reg=mean(ia_reg_in); */
  /* determines if the mean value is below the step-response current limit */
  /* '<S1>:796:5' if(mean_ia_reg < 0.5*GlobalConfig.ratCurrent) */
  if (ia_reg_in < 0.5F *
      rtElectricalID_6ph_codegen_U->GlobalConfig_out.ratCurrent) {
    /* Current limit for step response   */
    /* '<S1>:796:6' ia_valid=boolean(0); */
    rtElectricalID_6ph_codegen_DW->ia_valid = false;
  } else {
    /* '<S1>:796:7' else */
    /* '<S1>:796:8' ia_valid=boolean(1); */
    rtElectricalID_6ph_codegen_DW->ia_valid = true;
  }

  /* End of Inport: '<Root>/GlobalConfig' */
  /* '<S1>:796:11' if(ia_valid == 0) */
  if (!rtElectricalID_6ph_codegen_DW->ia_valid) {
    /* Increases the DutyCycle by 0.5% every 0.5 second, if the step response */
    /* is below the current limit */
    /* '<S1>:796:14' DutyCycle = DutyCycle + 0.005; */
    rtElectricalID_6ph_codegen_DW->DutyCycle += 0.005F;

    /* Simulation 0.001 | Real 0.005 */
  }
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void measure_psiPM(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* Merge: '<S1>/ Merge ' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
  /* During 'measure_psiPM': '<S1>:405' */
  /* '<S1>:406:1' sf_internal_predicateOutput = ElectricalID_output.PMSM_parameters.Psi_PM_Vs > 0; */
  if (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
      > 0.0F) {
    /* Transition: '<S1>:406' */
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:20' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_stop;

    /* Entry 'stop': '<S1>:361' */
    /* state 10.1 */
    /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(151); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 151U;

    /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

    /* '<S1>:361:5' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = true;
  } else {
    uint32_T qY;

    /* '<S1>:405:9' if(counter > wait_count && counter < (wait_count+1025)) */
    qY = rtElectricalID_6ph_codegen_DW->wait_count + 1025U;
    if (rtElectricalID_6ph_codegen_DW->wait_count + 1025U <
        rtElectricalID_6ph_codegen_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if ((rtElectricalID_6ph_codegen_DW->counter >
         rtElectricalID_6ph_codegen_DW->wait_count) &&
        (rtElectricalID_6ph_codegen_DW->counter < qY)) {
      uint32_T qY_tmp;
      uint32_T qY_tmp_tmp;

      /* '<S1>:405:10' measArray1(counter-wait_count) = ActualValues.v_dq.q; */
      qY_tmp_tmp = rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
        rtElectricalID_6ph_codegen_DW->wait_count;
      qY_tmp = qY_tmp_tmp;
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID_6ph_codegen_DW->counter) {
        qY = 0U;
        qY_tmp = 0U;
      }

      rtElectricalID_6ph_codegen_DW->measArray1[(int32_T)qY - 1] =
        rtElectricalID_6ph_codegen_U->ActualValues.v_dq.q;

      /* '<S1>:405:11' d(counter-wait_count) = ActualValues.i_dq.q; */
      rtElectricalID_6ph_codegen_DW->d[(int32_T)qY_tmp - 1] =
        rtElectricalID_6ph_codegen_U->ActualValues.i_dq.q;

      /* '<S1>:405:12' i_est(counter-wait_count) = ActualValues.omega_el; */
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID_6ph_codegen_DW->counter) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->i_est[(int32_T)qY - 1] =
        rtElectricalID_6ph_codegen_U->ActualValues.omega_el;
    }

    /* '<S1>:405:14' if(counter == (wait_count+1025)) */
    qY = rtElectricalID_6ph_codegen_DW->wait_count + 1025U;
    if (rtElectricalID_6ph_codegen_DW->wait_count + 1025U <
        rtElectricalID_6ph_codegen_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if (rtElectricalID_6ph_codegen_DW->counter == qY) {
      real32_T b_x;
      real32_T c_x;

      /* '<S1>:405:15' ElectricalID_output.PMSM_parameters.Psi_PM_Vs = (mean(measArray1(1:1024))-mean(d(1:1024))*.... */
      /* '<S1>:405:16'         ElectricalID_output.PMSM_parameters.R_ph_Ohm)/(mean(i_est(1:1024))); */
      b_x = rtElectricalID_6ph_codegen_DW->measArray1[0];
      c_x = rtElectricalID_6ph_codegen_DW->d[0];
      for (k = 0; k < 1023; k++) {
        b_x += rtElectricalID_6ph_codegen_DW->measArray1[k + 1];
        c_x += rtElectricalID_6ph_codegen_DW->d[k + 1];
      }

      b_x = b_x / 1024.0F - c_x / 1024.0F *
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm;
      c_x = rtElectricalID_6ph_codegen_DW->i_est[0];
      for (k = 0; k < 1023; k++) {
        c_x += rtElectricalID_6ph_codegen_DW->i_est[k + 1];
      }

      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
        = b_x / (c_x / 1024.0F);

      /* . */
    }

    /* '<S1>:405:18' counter = counter + 1; */
    qY = rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter + 1U <
        rtElectricalID_6ph_codegen_DW->counter) {
      qY = MAX_uint32_T;
    }

    rtElectricalID_6ph_codegen_DW->counter = qY;
  }

  /* End of Merge: '<S1>/ Merge ' */
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function y = SinusGenerator(Amp, Freq, sampleTime)
 */
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  real32_T tmp;
  real32_T y;
  uint32_T qY;

  /* MATLAB Function 'SinusGenerator': '<S1>:922' */
  /* '<S1>:922:6' if isempty(sineCounter) */
  /* '<S1>:922:10' u = single(Amp*sin(2*pi*single(Freq)*single(sineCounter)*sampleTime)); */
  y = sinf(6.28318548F * Freq * (real32_T)
           rtElectricalID_6ph_codegen_DW->sineCounter * sampleTime) * Amp;

  /* '<S1>:922:11' sineCounter = sineCounter + 1; */
  qY = rtElectricalID_6ph_codegen_DW->sineCounter + /*MW:OvSatOk*/ 1U;
  if (rtElectricalID_6ph_codegen_DW->sineCounter + 1U <
      rtElectricalID_6ph_codegen_DW->sineCounter) {
    qY = MAX_uint32_T;
  }

  rtElectricalID_6ph_codegen_DW->sineCounter = qY;

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

  if (rtElectricalID_6ph_codegen_DW->sineCounter == qY) {
    /* '<S1>:922:13' sineCounter = uint32(0); */
    rtElectricalID_6ph_codegen_DW->sineCounter = 0U;
  }

  /* '<S1>:922:17' y = single(u); */
  return y;
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
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function goertzel
 *  goertzel algorithm for J calculation
 */
static void goertzel(ExtU_ElectricalID_6ph_codegen_t
                     *rtElectricalID_6ph_codegen_U,
                     DW_ElectricalID_6ph_codegen_t
                     *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T A;
  real32_T B;
  real32_T C_im;
  real32_T C_re;
  real32_T b_y_im;
  real32_T b_y_re;
  real32_T s0;
  real32_T s2;

  /* MATLAB Function 'goertzel': '<S1>:350' */
  /*  calculate momentum from i_q */
  /* '<S1>:350:6' for k=single(1):single(500) */
  for (k = 0; k < 500; k++) {
    /* Inport: '<Root>/GlobalConfig' incorporates:
     *  Merge: '<S1>/ Merge '
     */
    /* '<S1>:350:7' d(k) = 1.5*GlobalConfig.PMSM_config.polePairs*ElectricalID_output.PMSM_parameters.Psi_PM_Vs*measArray1(k); */
    rtElectricalID_6ph_codegen_DW->d[k] = 1.5F *
      rtElectricalID_6ph_codegen_U->GlobalConfig_out.PMSM_config.polePairs *
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
      * rtElectricalID_6ph_codegen_DW->measArray1[k];
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
  A = 2.0F / (0.0001F /
              rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR) *
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
    s0 = (B * A + rtElectricalID_6ph_codegen_DW->d[k]) - s2;

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
  b_y_re = (B * A - s2) - A * C_re;
  b_y_im = 0.0F - A * C_im;

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
    s0 = (B * A + rtElectricalID_6ph_codegen_DW->i_est[k]) - s2;

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
  if (b_y_im == 0.0F) {
    if (B == 0.0F) {
      C_im = C_re / b_y_re;
      b_y_im = 0.0F;
    } else if (C_re == 0.0F) {
      C_im = 0.0F;
      b_y_im = B / b_y_re;
    } else {
      C_im = C_re / b_y_re;
      b_y_im = B / b_y_re;
    }
  } else if (b_y_re == 0.0F) {
    if (C_re == 0.0F) {
      C_im = B / b_y_im;
      b_y_im = 0.0F;
    } else if (B == 0.0F) {
      C_im = 0.0F;
      b_y_im = -(C_re / b_y_im);
    } else {
      C_im = B / b_y_im;
      b_y_im = -(C_re / b_y_im);
    }
  } else {
    A = fabsf(b_y_re);
    C_im = fabsf(b_y_im);
    if (A > C_im) {
      A = b_y_im / b_y_re;
      b_y_im = A * b_y_im + b_y_re;
      C_im = (A * B + C_re) / b_y_im;
      b_y_im = (B - A * C_re) / b_y_im;
    } else if (C_im == A) {
      b_y_re = b_y_re > 0.0F ? 0.5F : -0.5F;
      b_y_im = b_y_im > 0.0F ? 0.5F : -0.5F;
      C_im = (C_re * b_y_re + B * b_y_im) / A;
      b_y_im = (B * b_y_re - C_re * b_y_im) / A;
    } else {
      A = b_y_re / b_y_im;
      b_y_im += A * b_y_re;
      C_im = (A * C_re + B) / b_y_im;
      b_y_im = (A * B - C_re) / b_y_im;
    }
  }

  b_y_im = (0.0F - b_y_im) * 2.0F * 3.14159274F * 40.0F;
  b_y_re = 2.0F * C_im * 3.14159274F * 40.0F;
  if (b_y_re == 0.0F) {
    C_re = 1.0F / b_y_im;
    C_im = 0.0F;
  } else if (b_y_im == 0.0F) {
    C_re = 0.0F;
    C_im = -(1.0F / b_y_re);
  } else {
    A = fabsf(b_y_im);
    C_im = fabsf(b_y_re);
    if (A > C_im) {
      A = b_y_re / b_y_im;
      b_y_im += A * b_y_re;
      C_re = 1.0F / b_y_im;
      C_im = (0.0F - A) / b_y_im;
    } else if (C_im == A) {
      C_re = (b_y_im > 0.0F ? 0.5F : -0.5F) / A;
      C_im = (0.0F - (b_y_re > 0.0F ? 0.5F : -0.5F)) / A;
    } else {
      A = b_y_im / b_y_re;
      b_y_im = A * b_y_im + b_y_re;
      C_re = A / b_y_im;
      C_im = -1.0F / b_y_im;
    }
  }

  /* Merge: '<S1>/ Merge ' */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared
    = rt_hypotf(C_re, C_im);

  /* without damping */
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function [FOC_out_new] = ControllerParameter(FOC_out_old,bandwidthCurrentControl,PMSM_config,damping,psiOverJ)
 */
static void ControllerParameter(uz_ParaID_Controller_Parameters_output_t
  *FOC_out_old, real32_T bandwidthCurrentControl, real32_T PMSM_config_R_ph_Ohm,
  real32_T PMSM_config_Ld_Henry, real32_T PMSM_config_Lq_Henry, real32_T
  PMSM_config_polePairs, real32_T damping, real32_T psiOverJ)
{
  /* 'ControllerParameter:2' FOC_out_new = FOC_out_old; */
  /* 'ControllerParameter:3' FOC_out_new.Kp_id_out = single(PMSM_config.Ld_Henry * bandwidthCurrentControl); */
  FOC_out_old->Kp_id_out = PMSM_config_Ld_Henry * bandwidthCurrentControl;

  /* 'ControllerParameter:4' FOC_out_new.Kp_iq_out = single(PMSM_config.Lq_Henry * bandwidthCurrentControl); */
  FOC_out_old->Kp_iq_out = PMSM_config_Lq_Henry * bandwidthCurrentControl;

  /* 'ControllerParameter:5' FOC_out_new.Ki_id_out = single(PMSM_config.R_ph_Ohm * bandwidthCurrentControl); */
  FOC_out_old->Ki_id_out = PMSM_config_R_ph_Ohm * bandwidthCurrentControl;

  /* 'ControllerParameter:6' FOC_out_new.Ki_iq_out = single(FOC_out_new.Ki_id_out); */
  FOC_out_old->Ki_iq_out = FOC_out_old->Ki_id_out;

  /* 'ControllerParameter:7' FOC_out_new.Kp_n_out = single(FOC_out_new.Ki_iq_out/(PMSM_config.Lq_Henry*damping*PMSM_config.polePairs*3.0/2.0*psiOverJ)); */
  FOC_out_old->Kp_n_out = FOC_out_old->Ki_iq_out / (PMSM_config_Lq_Henry *
    damping * PMSM_config_polePairs * 3.0F / 2.0F * psiOverJ);

  /* 'ControllerParameter:8' FOC_out_new.Ki_n_out = single((FOC_out_new.Ki_iq_out)^2 / ((PMSM_config.Lq_Henry)^2 * damping^3 * PMSM_config.polePairs*3.0/2.0*psiOverJ)); */
  FOC_out_old->Ki_n_out = FOC_out_old->Ki_iq_out * FOC_out_old->Ki_iq_out /
    (PMSM_config_Lq_Henry * PMSM_config_Lq_Henry * powf(damping, 3.0F) *
     PMSM_config_polePairs * 3.0F / 2.0F * psiOverJ);
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void exit_internal_ElectricalID(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  /* Exit Internal 'ElectricalID': '<S1>:761' */
  switch (rtElectricalID_6ph_codegen_DW->is_ElectricalID) {
   case IN_Subchart_Step_Response:
    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S2>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S2>:35' */
      /* '<S2>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response1:
    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S3>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S3>:35' */
      /* '<S3>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response2:
    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S4>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S4>:35' */
      /* '<S4>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response3:
    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S5>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S5>:35' */
      /* '<S5>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response4:
    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S6>:35' */
      /* '<S6>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response5:
    /* Exit Internal: Subchart_Step_Response */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S7>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Exit 'stepResponse': '<S7>:35' */
      /* '<S7>:35:15' ResetDutyCycle(); */
      rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off:
    /* Merge: '<S1>/ Merge ' incorporates:
     *  Inport: '<Root>/ActualValues'
     */
    /* Exit 'alignRotor_d_off': '<S1>:53' */
    /* '<S1>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
      rtElectricalID_6ph_codegen_U->ActualValues.theta_m;

    /* '<S1>:53:8' DutyCycle=single(0.0); */
    rtElectricalID_6ph_codegen_DW->DutyCycle = 0.0F;

    /* resets the DC and DC_manual flag, so that for the step-response */
    /* '<S1>:53:9' DC_manual=boolean(0); */
    rtElectricalID_6ph_codegen_DW->DC_manual = false;

    /* a new DC can be entered */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off2:
    /* Exit 'alignRotor_d_off2': '<S1>:848' */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_on:
    /* Exit 'alignRotor_d_on': '<S1>:3' */
    /* '<S1>:3:14' ResetDutyCycle(); */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_evaluate_Turn_DC:
    /* Exit 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:27' ResetDutyCycle(); */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_findDutyCycle:
    /* Inport: '<Root>/ActualValues' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:29' ref_amplitude = single(DutyCycle*ActualValues.V_DC); */
    rtElectricalID_6ph_codegen_DW->ref_amplitude =
      rtElectricalID_6ph_codegen_DW->DutyCycle *
      rtElectricalID_6ph_codegen_U->ActualValues.V_DC;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:789:30' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_measure_psiPM:
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:20' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_rotorInertiaEstimation:
    /* Exit 'rotorInertiaEstimation': '<S1>:337' */
    /* '<S1>:337:18' goertzel; */
    goertzel(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_waitState:
    /* Outport: '<Root>/finishedElectricalID' */
    /* Exit 'waitState': '<S1>:428' */
    /* '<S1>:428:19' finishedElectricalID=boolean(1); */
    rtElectricalID_6ph_codegen_Y->finishedElectricalID = true;

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:428:20' enteredElectricalID=boolean(0); */
    rtElectricalID_6ph_codegen_Y->enteredElectricalID = false;

    /* '<S1>:428:21' reset_FOC_output; */
    reset_FOC_output(rtElectricalID_6ph_codegen_Y);
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   default:
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void ElectricalID(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  uint16_T n_iters_e;
  boolean_T updateJ_d;

  /* Inport: '<Root>/GlobalConfig' */
  /* During 'ElectricalID': '<S1>:761' */
  /* '<S1>:901:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.ElectricalID==0 ||.... */
  /* '<S1>:901:2'  GlobalConfig.enableParameterID==0; */
  /* . */
  if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.Reset ||
      (!rtElectricalID_6ph_codegen_U->GlobalConfig_out.ElectricalID) ||
      (!rtElectricalID_6ph_codegen_U->GlobalConfig_out.enableParameterID)) {
    /* Transition: '<S1>:901' */
    /* '<S1>:901:3' enteredElectricalID=boolean(0); */
    /* '<S1>:901:3' initParams; */
    initParams(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
               rtElectricalID_6ph_codegen_DW);
    exit_internal_ElectricalID(rtElectricalID_6ph_codegen_U,
      rtElectricalID_6ph_codegen_Y, rtElectricalID_6ph_codegen_DW);
    rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else {
    boolean_T guard1 = false;
    guard1 = false;
    switch (rtElectricalID_6ph_codegen_DW->is_ElectricalID) {
     case IN_Subchart_Step_Response:
      /* During 'Subchart_Step_Response': '<S1>:994' */
      /* '<S1>:1003:1' sf_internal_predicateOutput = finish_subsystem==true; */
      if (rtElectricalID_6ph_codegen_DW->finish_subsystem) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1003' */
        /* '<S1>:1003:2' ElectricalID_output.inductances_6ph.d=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1003:3' ElectricalID_output.resistances_6ph.d=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S2>:35' */
          /* '<S2>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response1;
        rtElectricalID_6ph_codegen_DW->counter_a = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_c[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_ny[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_m = 1U;
        rtElectricalID_6ph_codegen_DW->V0_h = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response1' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response */
        /* Entry Internal: Subchart_Step_Response */
        /* Transition: '<S3>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S3>:35' */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
        }

        /* '<S3>:35:3' finished_flag = false; */
        rtElectricalID_6ph_codegen_DW->finish_subsystem = false;

        /* current_meas_array(:) = single(0); */
        /* Vstep(:) = single(0); */
        /* counter=uint32(1); */
        /* '<S3>:35:7' activeState = uint16(140)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 143U;

        /* '<S3>:35:8' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[2] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S3>:35:9' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i_k] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_m[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i_k] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S3>:35:10' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_b =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response1' */
        /* set DutyCycles */

        /* During: Subchart_Step_Response */
      } else if (rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_
                 != IN_Levenberg_Marquardt) {
        /* During 'stepResponse': '<S2>:35' */
        /* '<S2>:32:1' sf_internal_predicateOutput = counter == 1026; */
        if (rtElectricalID_6ph_codegen_DW->counter_ha == 1026U) {
          /* Transition: '<S2>:32' */
          /* Exit 'stepResponse': '<S2>:35' */
          /* '<S2>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_ =
            IN_Levenberg_Marquardt;

          /* Entry 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->e_n = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[0] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[1] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[2] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[3] = 0.0F;
          n_iters_e = 100U;
          rtElectricalID_6ph_codegen_DW->lambda_b = 0.01F;
          updateJ_d = true;
          memset(&rtElectricalID_6ph_codegen_DW->d_f[0], 0, sizeof(real32_T) <<
                 11U);
          memset(&rtElectricalID_6ph_codegen_DW->i_est_dz[0], 0, sizeof(real32_T)
                 << 11U);
          memset(&rtElectricalID_6ph_codegen_DW->J_c[0], 0, sizeof(real32_T) <<
                 12U);

          /* '<S2>:40:3' LM_algorithm; */
          LM_algorithm(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_d,
                       &rtElectricalID_6ph_codegen_DW->lambda_b,
                       &rtElectricalID_6ph_codegen_DW->e_n, &n_iters_e,
                       rtElectricalID_6ph_codegen_DW->H_j,
                       rtElectricalID_6ph_codegen_DW->i_est_dz,
                       rtElectricalID_6ph_codegen_DW);

          /* '<S2>:40:4' R_est = (R_est-R_corr); */
          /* '<S2>:40:5' finished_flag = true; */
          rtElectricalID_6ph_codegen_DW->finish_subsystem = true;
        } else {
          /* Inport: '<Root>/ActualValues' */
          /* '<S2>:35:12' MeasureStepResponse(ref_amplitude,ActualValues.i_dq_6ph); */
          Subchart_St_MeasureStepRespon_n
            (rtElectricalID_6ph_codegen_DW->ref_amplitude,
             rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.d,
             rtElectricalID_6ph_codegen_DW);

          /* '<S2>:35:13' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter_ha + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_ha + 1U <
              rtElectricalID_6ph_codegen_DW->counter_ha) {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_ha =
            rtElectricalID_6ph_codegen_DW->qY;
        }
      } else {
        /* During 'Levenberg_Marquardt': '<S2>:40' */
      }
      break;

     case IN_Subchart_Step_Response1:
      /* During 'Subchart_Step_Response1': '<S1>:1001' */
      /* '<S1>:1018:1' sf_internal_predicateOutput = finish_subsystem==true; */
      if (rtElectricalID_6ph_codegen_DW->finish_subsystem) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1018' */
        /* '<S1>:1018:2' ElectricalID_output.inductances_6ph.x=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.x =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1018:3' ElectricalID_output.resistances_6ph.x=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.x =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S3>:35' */
          /* '<S3>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response2;
        rtElectricalID_6ph_codegen_DW->counter_k = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_a[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_o[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_n = 1U;
        rtElectricalID_6ph_codegen_DW->V0_b = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response2' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response */
        /* Entry Internal: Subchart_Step_Response */
        /* Transition: '<S4>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S4>:35' */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
        }

        /* '<S4>:35:3' finished_flag = false; */
        rtElectricalID_6ph_codegen_DW->finish_subsystem = false;

        /* current_meas_array(:) = single(0); */
        /* Vstep(:) = single(0); */
        /* counter=uint32(1); */
        /* '<S4>:35:7' activeState = uint16(140)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 144U;

        /* '<S4>:35:8' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[3] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S4>:35:9' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i_k] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_h[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i_k] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S4>:35:10' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_b =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response2' */
        /* set DutyCycles */

        /* During: Subchart_Step_Response */
      } else if (rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_
                 != IN_Levenberg_Marquardt) {
        /* During 'stepResponse': '<S3>:35' */
        /* '<S3>:32:1' sf_internal_predicateOutput = counter == 1026; */
        if (rtElectricalID_6ph_codegen_DW->counter_a == 1026U) {
          /* Transition: '<S3>:32' */
          /* Exit 'stepResponse': '<S3>:35' */
          /* '<S3>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_s8mSgIiQKbXVcTjgztm9xxC_ =
            IN_Levenberg_Marquardt;

          /* Entry 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->e_n = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[0] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[1] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[2] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[3] = 0.0F;
          n_iters_e = 100U;
          rtElectricalID_6ph_codegen_DW->lambda_b = 0.01F;
          updateJ_d = true;
          memset(&rtElectricalID_6ph_codegen_DW->d_i[0], 0, sizeof(real32_T) <<
                 11U);
          memset(&rtElectricalID_6ph_codegen_DW->i_est_dz[0], 0, sizeof(real32_T)
                 << 11U);
          memset(&rtElectricalID_6ph_codegen_DW->J_l[0], 0, sizeof(real32_T) <<
                 12U);

          /* '<S3>:40:3' LM_algorithm; */
          LM_algorithm_m(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                         &rtElectricalID_6ph_codegen_DW->R_est_c,
                         &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_d,
                         &rtElectricalID_6ph_codegen_DW->lambda_b,
                         &rtElectricalID_6ph_codegen_DW->e_n, &n_iters_e,
                         rtElectricalID_6ph_codegen_DW->H_j,
                         rtElectricalID_6ph_codegen_DW->i_est_dz,
                         rtElectricalID_6ph_codegen_DW);

          /* '<S3>:40:4' R_est = (R_est-R_corr); */
          /* '<S3>:40:5' finished_flag = true; */
          rtElectricalID_6ph_codegen_DW->finish_subsystem = true;
        } else {
          /* Inport: '<Root>/ActualValues' */
          /* '<S3>:35:12' MeasureStepResponse(ref_amplitude,ActualValues.i_dq_6ph); */
          Subchart__f_MeasureStepRespon_a
            (rtElectricalID_6ph_codegen_DW->ref_amplitude,
             rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.x,
             rtElectricalID_6ph_codegen_DW);

          /* '<S3>:35:13' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter_a + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_a + 1U <
              rtElectricalID_6ph_codegen_DW->counter_a) {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_a =
            rtElectricalID_6ph_codegen_DW->qY;
        }
      } else {
        /* During 'Levenberg_Marquardt': '<S3>:40' */
      }
      break;

     case IN_Subchart_Step_Response2:
      /* During 'Subchart_Step_Response2': '<S1>:1009' */
      /* '<S1>:1019:1' sf_internal_predicateOutput = finish_subsystem==true; */
      if (rtElectricalID_6ph_codegen_DW->finish_subsystem) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1019' */
        /* '<S1>:1019:2' ElectricalID_output.inductances_6ph.y=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.y =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1019:3' ElectricalID_output.resistances_6ph.y=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.y =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S4>:35' */
          /* '<S4>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response3;
        rtElectricalID_6ph_codegen_DW->counter_l = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_d[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_n[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_g = 1U;
        rtElectricalID_6ph_codegen_DW->V0_m = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response3' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response */
        /* Entry Internal: Subchart_Step_Response */
        /* Transition: '<S5>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S5>:35' */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
        }

        /* '<S5>:35:3' finished_flag = false; */
        rtElectricalID_6ph_codegen_DW->finish_subsystem = false;

        /* current_meas_array(:) = single(0); */
        /* Vstep(:) = single(0); */
        /* counter=uint32(1); */
        /* '<S5>:35:7' activeState = uint16(140)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 145U;

        /* '<S5>:35:8' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[4] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S5>:35:9' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i_k] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_p[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i_k] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S5>:35:10' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_b =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response3' */
        /* set DutyCycles */

        /* During: Subchart_Step_Response */
      } else if (rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_
                 != IN_Levenberg_Marquardt) {
        /* During 'stepResponse': '<S4>:35' */
        /* '<S4>:32:1' sf_internal_predicateOutput = counter == 1026; */
        if (rtElectricalID_6ph_codegen_DW->counter_k == 1026U) {
          /* Transition: '<S4>:32' */
          /* Exit 'stepResponse': '<S4>:35' */
          /* '<S4>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_sxLaC9TKhCvTBlVuzaf2X9C_ =
            IN_Levenberg_Marquardt;

          /* Entry 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->e_n = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[0] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[1] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[2] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[3] = 0.0F;
          n_iters_e = 100U;
          rtElectricalID_6ph_codegen_DW->lambda_b = 0.01F;
          updateJ_d = true;
          memset(&rtElectricalID_6ph_codegen_DW->d_d[0], 0, sizeof(real32_T) <<
                 11U);
          memset(&rtElectricalID_6ph_codegen_DW->i_est_dz[0], 0, sizeof(real32_T)
                 << 11U);
          memset(&rtElectricalID_6ph_codegen_DW->J_h[0], 0, sizeof(real32_T) <<
                 12U);

          /* '<S4>:40:3' LM_algorithm; */
          LM_algorithm_j(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                         &rtElectricalID_6ph_codegen_DW->R_est_c,
                         &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_d,
                         &rtElectricalID_6ph_codegen_DW->lambda_b,
                         &rtElectricalID_6ph_codegen_DW->e_n, &n_iters_e,
                         rtElectricalID_6ph_codegen_DW->H_j,
                         rtElectricalID_6ph_codegen_DW->i_est_dz,
                         rtElectricalID_6ph_codegen_DW);

          /* '<S4>:40:4' R_est = (R_est-R_corr); */
          /* '<S4>:40:5' finished_flag = true; */
          rtElectricalID_6ph_codegen_DW->finish_subsystem = true;
        } else {
          /* Inport: '<Root>/ActualValues' */
          /* '<S4>:35:12' MeasureStepResponse(ref_amplitude,ActualValues.i_dq_6ph); */
          Subchart_fy_MeasureStepRespon_g
            (rtElectricalID_6ph_codegen_DW->ref_amplitude,
             rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.y,
             rtElectricalID_6ph_codegen_DW);

          /* '<S4>:35:13' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter_k + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_k + 1U <
              rtElectricalID_6ph_codegen_DW->counter_k) {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_k =
            rtElectricalID_6ph_codegen_DW->qY;
        }
      } else {
        /* During 'Levenberg_Marquardt': '<S4>:40' */
      }
      break;

     case IN_Subchart_Step_Response3:
      /* During 'Subchart_Step_Response3': '<S1>:1013' */
      /* '<S1>:1020:1' sf_internal_predicateOutput = finish_subsystem==true; */
      if (rtElectricalID_6ph_codegen_DW->finish_subsystem) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1020' */
        /* '<S1>:1020:2' ElectricalID_output.inductances_6ph.z1=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z1 =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1020:3' ElectricalID_output.resistances_6ph.z1=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z1 =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S5>:35' */
          /* '<S5>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response4;
        rtElectricalID_6ph_codegen_DW->counter_h = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_j[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_e[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_a = 1U;
        rtElectricalID_6ph_codegen_DW->V0_j = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response4' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response */
        /* Entry Internal: Subchart_Step_Response */
        /* Transition: '<S6>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_se4gXkCdMTwKJYW518oKG6B_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S6>:35' */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
        }

        /* '<S6>:35:3' finished_flag = false; */
        rtElectricalID_6ph_codegen_DW->finish_subsystem = false;

        /* current_meas_array(:) = single(0); */
        /* Vstep(:) = single(0); */
        /* counter=uint32(1); */
        /* '<S6>:35:7' activeState = uint16(140)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 146U;

        /* '<S6>:35:8' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[5] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S6>:35:9' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i_k] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_b[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i_k] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S6>:35:10' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_b =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response4' */
        /* set DutyCycles */

        /* During: Subchart_Step_Response */
      } else if (rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S
                 != IN_Levenberg_Marquardt) {
        /* During 'stepResponse': '<S5>:35' */
        /* '<S5>:32:1' sf_internal_predicateOutput = counter == 1026; */
        if (rtElectricalID_6ph_codegen_DW->counter_l == 1026U) {
          /* Transition: '<S5>:32' */
          /* Exit 'stepResponse': '<S5>:35' */
          /* '<S5>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_seI33vPcpaZiAnLIB3XaoL_S =
            IN_Levenberg_Marquardt;

          /* Entry 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->e_n = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[0] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[1] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[2] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[3] = 0.0F;
          n_iters_e = 100U;
          rtElectricalID_6ph_codegen_DW->lambda_b = 0.01F;
          updateJ_d = true;
          memset(&rtElectricalID_6ph_codegen_DW->d_b[0], 0, sizeof(real32_T) <<
                 11U);
          memset(&rtElectricalID_6ph_codegen_DW->i_est_dz[0], 0, sizeof(real32_T)
                 << 11U);
          memset(&rtElectricalID_6ph_codegen_DW->J_m[0], 0, sizeof(real32_T) <<
                 12U);

          /* '<S5>:40:3' LM_algorithm; */
          LM_algorithm_a(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                         &rtElectricalID_6ph_codegen_DW->R_est_c,
                         &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_d,
                         &rtElectricalID_6ph_codegen_DW->lambda_b,
                         &rtElectricalID_6ph_codegen_DW->e_n, &n_iters_e,
                         rtElectricalID_6ph_codegen_DW->H_j,
                         rtElectricalID_6ph_codegen_DW->i_est_dz,
                         rtElectricalID_6ph_codegen_DW);

          /* '<S5>:40:4' R_est = (R_est-R_corr); */
          /* '<S5>:40:5' finished_flag = true; */
          rtElectricalID_6ph_codegen_DW->finish_subsystem = true;
        } else {
          /* Inport: '<Root>/ActualValues' */
          /* '<S5>:35:12' MeasureStepResponse(ref_amplitude,ActualValues.i_dq_6ph); */
          Subchar_fy4_MeasureStepRespon_p
            (rtElectricalID_6ph_codegen_DW->ref_amplitude,
             rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z1,
             rtElectricalID_6ph_codegen_DW);

          /* '<S5>:35:13' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter_l + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_l + 1U <
              rtElectricalID_6ph_codegen_DW->counter_l) {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_l =
            rtElectricalID_6ph_codegen_DW->qY;
        }
      } else {
        /* During 'Levenberg_Marquardt': '<S5>:40' */
      }
      break;

     case IN_Subchart_Step_Response4:
      Subchart_Step_Response4(rtElectricalID_6ph_codegen_U,
        rtElectricalID_6ph_codegen_Y, rtElectricalID_6ph_codegen_DW);
      break;

     case IN_Subchart_Step_Response5:
      /* During 'Subchart_Step_Response5': '<S1>:1025' */
      /* '<S1>:1030:1' sf_internal_predicateOutput = finish_subsystem==true; */
      if (rtElectricalID_6ph_codegen_DW->finish_subsystem) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1030' */
        /* '<S1>:1030:2' ElectricalID_output.inductances_6ph.q=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1030:3' ElectricalID_output.resistances_6ph.q=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S7>:35' */
          /* '<S7>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitAccept;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'waitAccept': '<S1>:1028' */
        /* '<S1>:1028:3' ElectricalID_FOC_output.activeState = uint16(148); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 148U;

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:1028:4' ElectricalID_output.PMSM_parameters.Ld_Henry = ElectricalID_output.inductances_6ph.d; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry
          = rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d;

        /* '<S1>:1028:5' ElectricalID_output.PMSM_parameters.Lq_Henry = ElectricalID_output.inductances_6ph.q; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
          = rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q;

        /* '<S1>:1028:6' ElectricalID_output.PMSM_parameters.R_ph_Ohm = ElectricalID_output.resistances_6ph.d; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm
          = rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d;

        /* During: Subchart_Step_Response */
      } else if (rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_
                 != IN_Levenberg_Marquardt) {
        /* During 'stepResponse': '<S7>:35' */
        /* '<S7>:32:1' sf_internal_predicateOutput = counter == 1026; */
        if (rtElectricalID_6ph_codegen_DW->counter_f == 1026U) {
          /* Transition: '<S7>:32' */
          /* Exit 'stepResponse': '<S7>:35' */
          /* '<S7>:35:15' ResetDutyCycle(); */
          rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_ =
            IN_Levenberg_Marquardt;

          /* Entry 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->e_n = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[0] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[1] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[2] = 0.0F;
          rtElectricalID_6ph_codegen_DW->H_j[3] = 0.0F;
          n_iters_e = 100U;
          rtElectricalID_6ph_codegen_DW->lambda_b = 0.01F;
          updateJ_d = true;
          memset(&rtElectricalID_6ph_codegen_DW->d_a[0], 0, sizeof(real32_T) <<
                 11U);
          memset(&rtElectricalID_6ph_codegen_DW->i_est_dz[0], 0, sizeof(real32_T)
                 << 11U);
          memset(&rtElectricalID_6ph_codegen_DW->J[0], 0, sizeof(real32_T) <<
                 12U);

          /* '<S7>:40:3' LM_algorithm; */
          LM_algorithm_i(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                         &rtElectricalID_6ph_codegen_DW->R_est_c,
                         &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_d,
                         &rtElectricalID_6ph_codegen_DW->lambda_b,
                         &rtElectricalID_6ph_codegen_DW->e_n, &n_iters_e,
                         rtElectricalID_6ph_codegen_DW->H_j,
                         rtElectricalID_6ph_codegen_DW->i_est_dz,
                         rtElectricalID_6ph_codegen_DW);

          /* '<S7>:40:4' R_est = (R_est-R_corr); */
          /* '<S7>:40:5' finished_flag = true; */
          rtElectricalID_6ph_codegen_DW->finish_subsystem = true;
        } else {
          /* Inport: '<Root>/ActualValues' */
          /* '<S7>:35:12' MeasureStepResponse(ref_amplitude,ActualValues.i_dq_6ph); */
          Subch_fy4wk_MeasureStepRespon_g
            (rtElectricalID_6ph_codegen_DW->ref_amplitude,
             rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.q,
             rtElectricalID_6ph_codegen_DW);

          /* '<S7>:35:13' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter_f + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_f + 1U <
              rtElectricalID_6ph_codegen_DW->counter_f) {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_f =
            rtElectricalID_6ph_codegen_DW->qY;
        }
      } else {
        /* During 'Levenberg_Marquardt': '<S7>:40' */
      }
      break;

     case IN_alignRotor_d_off:
      /* During 'alignRotor_d_off': '<S1>:53' */
      /* '<S1>:411:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Merge: '<S1>/ Merge ' incorporates:
         *  Inport: '<Root>/ActualValues'
         */
        /* Transition: '<S1>:411' */
        /* Exit 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:7' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
          rtElectricalID_6ph_codegen_U->ActualValues.theta_m;

        /* '<S1>:53:8' DutyCycle=single(0.0); */
        rtElectricalID_6ph_codegen_DW->DutyCycle = 0.0F;

        /* resets the DC and DC_manual flag, so that for the step-response */
        /* '<S1>:53:9' DC_manual=boolean(0); */
        rtElectricalID_6ph_codegen_DW->DC_manual = false;

        /* a new DC can be entered */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_findDutyCycle;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'findDutyCycle': '<S1>:789' */
        /* Motor must be manually locked via load machine until state 60 */
        /* '<S1>:789:4' ElectricalID_FOC_output.activeState = uint16(130); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 130U;

        /* Inport: '<Root>/ElectricalIDConfig' */
        /* '<S1>:789:5' if(ElectricalIDConfig.dutyCyc > 0.0) */
        if (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.dutyCyc > 0.0F) {
          /* Checks if a manual value for the DutyCycle was set */
          /* '<S1>:789:6' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
          rtElectricalID_6ph_codegen_DW->DutyCycle =
            rtElectricalID_6ph_codegen_U->ElectricalIDConfig.dutyCyc;

          /* '<S1>:789:7' DC_manual = boolean(1); */
          rtElectricalID_6ph_codegen_DW->DC_manual = true;
        } else {
          /* '<S1>:789:8' else */
          /* '<S1>:789:9' DutyCycle = single(DutyCycle); */
          /* Starting DC */
        }

        /* '<S1>:789:11' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* starts with 1, so that the DutyCylce_mod function wont be entered */
        /* during the fist cycle through the state */
      } else {
        /* '<S1>:53:5' counter  = counter +1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;

     case IN_alignRotor_d_off2:
      /* During 'alignRotor_d_off2': '<S1>:848' */
      /* '<S1>:849:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Transition: '<S1>:849' */
        /* Exit 'alignRotor_d_off2': '<S1>:848' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response;
        rtElectricalID_6ph_codegen_DW->counter_ha = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_f[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_p[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_d = 1U;
        rtElectricalID_6ph_codegen_DW->V0_k = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response */
        /* Entry Internal: Subchart_Step_Response */
        /* Transition: '<S2>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sjo6JU1cq2wZZNYlRD9HH0C_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S2>:35' */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
        }

        /* '<S2>:35:3' finished_flag = false; */
        rtElectricalID_6ph_codegen_DW->finish_subsystem = false;

        /* current_meas_array(:) = single(0); */
        /* Vstep(:) = single(0); */
        /* counter=uint32(1); */
        /* '<S2>:35:7' activeState = uint16(140)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 141U;

        /* '<S2>:35:8' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[0] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S2>:35:9' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i_k] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_ph[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i_k] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S2>:35:10' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_b =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response' */
        /* set DutyCycles */
      } else {
        /* '<S1>:848:5' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;

     case IN_alignRotor_d_on:
      /* During 'alignRotor_d_on': '<S1>:3' */
      /* '<S1>:164:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Transition: '<S1>:164' */
        /* Exit 'alignRotor_d_on': '<S1>:3' */
        /* '<S1>:3:14' ResetDutyCycle(); */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_alignRotor_d_off;

        /* Entry 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:3' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:53:4' ElectricalID_FOC_output.activeState = uint16(121); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 121U;
      } else {
        /* '<S1>:3:7' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
        rtElectricalID_6ph_codegen_DW->e_n = (real32_T)
          rtElectricalID_6ph_codegen_DW->counter *
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S1>:3:8' if(DutyCycle_filt > 1) */
        if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* '<S1>:3:9' DutyCycle_filt = single(1.0); */
          rtElectricalID_6ph_codegen_DW->e_n = 1.0F;
        }

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:3:11' ElectricalID_output.PWM_Switch_0 = single(DutyCycle*DutyCycle_filt); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
          rtElectricalID_6ph_codegen_DW->DutyCycle *
          rtElectricalID_6ph_codegen_DW->e_n;

        /* '<S1>:3:12' counter  = counter +1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;

     case IN_calculatePIcontroller:
      /* During 'calculatePIcontroller': '<S1>:284' */
      /* '<S1>:408:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:408' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_measure_psiPM;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Inport: '<Root>/ElectricalIDConfig'
         */
        /* Entry 'measure_psiPM': '<S1>:405' */
        /* '<S1>:405:4' ElectricalID_FOC_output.activeState = uint16(150); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 150U;

        /* '<S1>:405:5' ElectricalID_FOC_output.enableFOC_speed = boolean(1); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed =
          true;

        /* '<S1>:405:6' ElectricalID_FOC_output.n_ref_FOC = ElectricalIDConfig.n_ref_measurement; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC =
          rtElectricalID_6ph_codegen_U->ElectricalIDConfig.n_ref_measurement;

        /* '<S1>:405:7' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        rtElectricalID_6ph_codegen_DW->e_n = roundf(3.0F /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
          if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
            rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)
              rtElectricalID_6ph_codegen_DW->e_n;
          } else {
            rtElectricalID_6ph_codegen_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID_6ph_codegen_DW->wait_count = MAX_uint32_T;
        }
      }
      break;

     case IN_endState:
      /* During 'endState': '<S1>:356' */
      /* '<S1>:425:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Transition: '<S1>:425' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitState;

        /* Entry 'waitState': '<S1>:428' */
        /* do nothing */
        /* '<S1>:428:3' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Merge: '<S1>/ Merge '
         */
        /* '<S1>:428:4' ElectricalID_FOC_output.enableFOC_current = boolean(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_current =
          false;

        /* '<S1>:428:5' ElectricalID_FOC_output.activeState = uint16(170); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 170U;

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
        /* '<S1>:428:14' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_n_out =
          rtElectricalID_6ph_codegen_DW->Kp_iq_loc /
          (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
           * rtElectricalID_6ph_codegen_DW->dampingFactor *
           rtElectricalID_6ph_codegen_U->GlobalConfig_out.PMSM_config.polePairs *
           3.0F / 2.0F *
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
           /
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared);

        /* '<S1>:428:15' ElectricalID_FOC_output.Ki_n_out = Ki_n_loc; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_n_out =
          rtElectricalID_6ph_codegen_DW->Kp_iq_loc *
          rtElectricalID_6ph_codegen_DW->Kp_iq_loc /
          (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
           * rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
           * rtElectricalID_6ph_codegen_DW->dampingFactor *
           rtElectricalID_6ph_codegen_DW->dampingFactor *
           rtElectricalID_6ph_codegen_DW->dampingFactor *
           rtElectricalID_6ph_codegen_U->GlobalConfig_out.PMSM_config.polePairs *
           3.0F / 2.0F *
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
           /
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared);
      } else {
        /* '<S1>:356:8' counter = counter + 1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;

     case IN_evaluate_Turn_DC:
      /* During 'evaluate_Turn_DC': '<S1>:379' */
      /* '<S1>:383:1' sf_internal_predicateOutput = om_con==1; */
      if (rtElectricalID_6ph_codegen_DW->om_con ||
          rtElectricalID_6ph_codegen_DW->DC_manual) {
        /* Transition: '<S1>:383' */
        /* Transition: '<S1>:921' */
        /* Exit 'evaluate_Turn_DC': '<S1>:379' */
        /* '<S1>:379:27' ResetDutyCycle(); */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_alignRotor_d_on;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'alignRotor_d_on': '<S1>:3' */
        /* '<S1>:3:4' ElectricalID_FOC_output.activeState = uint16(120); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 120U;

        /* '<S1>:3:5' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;
      } else {
        /* '<S1>:921:1' sf_internal_predicateOutput = DC_manual == 1; */
        /* '<S1>:379:13' if(DC_manual == 0) */
        if (!rtElectricalID_6ph_codegen_DW->DC_manual) {
          /* Inport: '<Root>/ActualValues' */
          /* averages the last 0.1s */
          /* '<S1>:379:14' omega_sum=omega_sum+single(ActualValues.omega_m); */
          rtElectricalID_6ph_codegen_DW->omega_sum +=
            rtElectricalID_6ph_codegen_U->ActualValues.omega_m;

          /* '<S1>:379:15' if(mod(counter,uint32(0.1/GlobalConfig.sampleTimeISR))==0) */
          rtElectricalID_6ph_codegen_DW->e_n = roundf(0.1F /
            rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
          if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
            if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
              rtElectricalID_6ph_codegen_DW->qY = (uint32_T)
                rtElectricalID_6ph_codegen_DW->e_n;
            } else {
              rtElectricalID_6ph_codegen_DW->qY = 0U;
            }
          } else {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          if (rtElectricalID_6ph_codegen_DW->qY == 0U) {
            rtElectricalID_6ph_codegen_DW->qY =
              rtElectricalID_6ph_codegen_DW->counter;
          } else {
            rtElectricalID_6ph_codegen_DW->qY =
              rtElectricalID_6ph_codegen_DW->counter -
              rtElectricalID_6ph_codegen_DW->counter /
              rtElectricalID_6ph_codegen_DW->qY *
              rtElectricalID_6ph_codegen_DW->qY;
          }

          if (rtElectricalID_6ph_codegen_DW->qY == 0U) {
            /* '<S1>:379:16' RefreshDataRegister; */
            RefreshDataRegister(rtElectricalID_6ph_codegen_DW);

            /* '<S1>:379:17' omega_register(1,1)=omega_sum*(GlobalConfig.sampleTimeISR/0.1); */
            rtElectricalID_6ph_codegen_DW->omega_register[0] =
              rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR /
              0.1F * rtElectricalID_6ph_codegen_DW->omega_sum;

            /* '<S1>:379:18' omega_sum=single(0); */
            rtElectricalID_6ph_codegen_DW->omega_sum = 0.0F;
          }

          /* '<S1>:379:20' if(mod(counter,uint32(2/GlobalConfig.sampleTimeISR))==0) */
          rtElectricalID_6ph_codegen_DW->e_n = roundf(2.0F /
            rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
          if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
            if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
              rtElectricalID_6ph_codegen_DW->qY = (uint32_T)
                rtElectricalID_6ph_codegen_DW->e_n;
            } else {
              rtElectricalID_6ph_codegen_DW->qY = 0U;
            }
          } else {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          if (rtElectricalID_6ph_codegen_DW->qY == 0U) {
            rtElectricalID_6ph_codegen_DW->qY =
              rtElectricalID_6ph_codegen_DW->counter;
          } else {
            rtElectricalID_6ph_codegen_DW->qY =
              rtElectricalID_6ph_codegen_DW->counter -
              rtElectricalID_6ph_codegen_DW->counter /
              rtElectricalID_6ph_codegen_DW->qY *
              rtElectricalID_6ph_codegen_DW->qY;
          }

          if (rtElectricalID_6ph_codegen_DW->qY == 0U) {
            /* after 2s omega will be evaluated */
            /* '<S1>:379:21' DutyCycle_mod(abs(omega_register)); */
            for (rtElectricalID_6ph_codegen_DW->i_k = 0;
                 rtElectricalID_6ph_codegen_DW->i_k < 5;
                 rtElectricalID_6ph_codegen_DW->i_k++) {
              rtElectricalID_6ph_codegen_DW->k_y
                [rtElectricalID_6ph_codegen_DW->i_k] = fabsf
                (rtElectricalID_6ph_codegen_DW->
                 omega_register[rtElectricalID_6ph_codegen_DW->i_k]);
            }

            DutyCycle_mod(rtElectricalID_6ph_codegen_DW->k_y,
                          rtElectricalID_6ph_codegen_U,
                          rtElectricalID_6ph_codegen_DW);
          }
        }

        /* '<S1>:379:24' counter = counter + 1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;

        /* '<S1>:379:25' TurnMotor; */
        TurnMotor(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);
      }
      break;

     case IN_findDutyCycle:
      /* During 'findDutyCycle': '<S1>:789' */
      /* '<S1>:790:1' sf_internal_predicateOutput = ia_valid==1 ||DC_manual == 1; */
      if (rtElectricalID_6ph_codegen_DW->ia_valid ||
          rtElectricalID_6ph_codegen_DW->DC_manual) {
        /* Inport: '<Root>/ActualValues' */
        /* Transition: '<S1>:790' */
        /* Exit 'findDutyCycle': '<S1>:789' */
        /* '<S1>:789:29' ref_amplitude = single(DutyCycle*ActualValues.V_DC); */
        rtElectricalID_6ph_codegen_DW->ref_amplitude =
          rtElectricalID_6ph_codegen_DW->DutyCycle *
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC;

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:789:30' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_alignRotor_d_off2;

        /* Entry 'alignRotor_d_off2': '<S1>:848' */
        /* '<S1>:848:3' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:848:4' ElectricalID_FOC_output.activeState = uint16(131); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 131U;

        /* '<S1>:789:14' if(DC_manual == 0 && ia_valid==0) */
      } else if ((!rtElectricalID_6ph_codegen_DW->DC_manual) &&
                 (!rtElectricalID_6ph_codegen_DW->ia_valid)) {
        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:789:15' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
          rtElectricalID_6ph_codegen_DW->DutyCycle;

        /* Set DC */
        /* '<S1>:789:16' if(counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
        rtElectricalID_6ph_codegen_DW->e_n = roundf(0.4F /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
          if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
            rtElectricalID_6ph_codegen_DW->qY = (uint32_T)
              rtElectricalID_6ph_codegen_DW->e_n;
          } else {
            rtElectricalID_6ph_codegen_DW->qY = 0U;
          }
        } else {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        if (rtElectricalID_6ph_codegen_DW->counter <
            rtElectricalID_6ph_codegen_DW->qY) {
          /* Wait several time for step response to rise */
          /* '<S1>:789:17' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter + 1U <
              rtElectricalID_6ph_codegen_DW->counter) {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter =
            rtElectricalID_6ph_codegen_DW->qY;
        } else {
          if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
            if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
              rtElectricalID_6ph_codegen_DW->qY = (uint32_T)
                rtElectricalID_6ph_codegen_DW->e_n;
            } else {
              rtElectricalID_6ph_codegen_DW->qY = 0U;
            }
          } else {
            rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
          }

          if (rtElectricalID_6ph_codegen_DW->counter >=
              rtElectricalID_6ph_codegen_DW->qY) {
            rtElectricalID_6ph_codegen_DW->e_n = roundf(0.5F /
              rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
            if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
              if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
                rtElectricalID_6ph_codegen_DW->qY = (uint32_T)
                  rtElectricalID_6ph_codegen_DW->e_n;
              } else {
                rtElectricalID_6ph_codegen_DW->qY = 0U;
              }
            } else {
              rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
            }

            if (rtElectricalID_6ph_codegen_DW->counter <
                rtElectricalID_6ph_codegen_DW->qY) {
              /* '<S1>:789:18' elseif(counter >= uint32(0.4/GlobalConfig.sampleTimeISR) &&.... */
              /* '<S1>:789:19'             counter < uint32(0.5/GlobalConfig.sampleTimeISR)) */
              /* . */
              /* record current - WHY NOW? */
              /* '<S1>:789:20' counter = counter +1; */
              rtElectricalID_6ph_codegen_DW->qY =
                rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
              if (rtElectricalID_6ph_codegen_DW->counter + 1U <
                  rtElectricalID_6ph_codegen_DW->counter) {
                rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
              }

              rtElectricalID_6ph_codegen_DW->counter =
                rtElectricalID_6ph_codegen_DW->qY;

              /* Inport: '<Root>/ActualValues' */
              /* '<S1>:789:21' ia_sum=ia_sum+single(ActualValues.i_abc_6ph.a1); */
              rtElectricalID_6ph_codegen_DW->ia_sum +=
                rtElectricalID_6ph_codegen_U->ActualValues.i_abc_6ph.a1;

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
      measure_psiPM(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
                    rtElectricalID_6ph_codegen_DW);
      break;

     case IN_rotorInertiaEstimation:
      /* During 'rotorInertiaEstimation': '<S1>:337' */
      /* '<S1>:357:1' sf_internal_predicateOutput = counter == (wait_count+513); */
      rtElectricalID_6ph_codegen_DW->qY =
        rtElectricalID_6ph_codegen_DW->wait_count + /*MW:OvSatOk*/ 513U;
      if (rtElectricalID_6ph_codegen_DW->wait_count + 513U <
          rtElectricalID_6ph_codegen_DW->wait_count) {
        rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
      }

      if (rtElectricalID_6ph_codegen_DW->counter ==
          rtElectricalID_6ph_codegen_DW->qY) {
        /* Transition: '<S1>:357' */
        /* Exit 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:18' goertzel; */
        goertzel(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_endState;

        /* Entry 'endState': '<S1>:356' */
        /* '<S1>:356:4' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:356:5' ElectricalID_FOC_output.activeState = uint16(161); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 161U;

        /* '<S1>:356:6' ElectricalID_FOC_output.resetIntegrator=boolean(1); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
          true;
      } else {
        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Inport: '<Root>/ElectricalIDConfig'
         */
        /* '<S1>:337:10' ElectricalID_FOC_output.i_dq_ref.q = SinusGenerator(ElectricalIDConfig.goertzlTorque,.... */
        /* '<S1>:337:11'     ElectricalIDConfig.goertzlFreq,GlobalConfig.sampleTimeISR); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.q =
          SinusGenerator
          (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.goertzlTorque,
           rtElectricalID_6ph_codegen_U->ElectricalIDConfig.goertzlFreq,
           rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR,
           rtElectricalID_6ph_codegen_DW);

        /* . */
        /* '<S1>:337:12' if(counter > wait_count && counter < (wait_count+501)) */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->wait_count + /*MW:OvSatOk*/ 501U;
        if (rtElectricalID_6ph_codegen_DW->wait_count + 501U <
            rtElectricalID_6ph_codegen_DW->wait_count) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        if ((rtElectricalID_6ph_codegen_DW->counter >
             rtElectricalID_6ph_codegen_DW->wait_count) &&
            (rtElectricalID_6ph_codegen_DW->counter <
             rtElectricalID_6ph_codegen_DW->qY)) {
          /* '<S1>:337:13' measArray1(counter-wait_count) = ActualValues.i_dq.q; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
            rtElectricalID_6ph_codegen_DW->wait_count;
          if (rtElectricalID_6ph_codegen_DW->qY >
              rtElectricalID_6ph_codegen_DW->counter) {
            rtElectricalID_6ph_codegen_DW->qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_6ph_codegen_DW->measArray1[(int32_T)
            rtElectricalID_6ph_codegen_DW->qY - 1] =
            rtElectricalID_6ph_codegen_U->ActualValues.i_dq.q;

          /* '<S1>:337:14' i_est(counter-wait_count) = ActualValues.omega_m; */
          rtElectricalID_6ph_codegen_DW->qY =
            rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
            rtElectricalID_6ph_codegen_DW->wait_count;
          if (rtElectricalID_6ph_codegen_DW->qY >
              rtElectricalID_6ph_codegen_DW->counter) {
            rtElectricalID_6ph_codegen_DW->qY = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_6ph_codegen_DW->i_est[(int32_T)
            rtElectricalID_6ph_codegen_DW->qY - 1] =
            rtElectricalID_6ph_codegen_U->ActualValues.omega_m;
        }

        /* '<S1>:337:16' counter = counter + 1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;

     case IN_stop:
      /* During 'stop': '<S1>:361' */
      /* '<S1>:362:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Transition: '<S1>:362' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_rotorInertiaEstimation;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:3' ElectricalID_FOC_output.enableFOC_speed = boolean(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed =
          false;

        /* '<S1>:337:4' ElectricalID_FOC_output.enableFOC_current = boolean(1); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_current =
          true;

        /* '<S1>:337:5' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:337:6' ElectricalID_FOC_output.resetIntegrator = boolean(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
          false;

        /* '<S1>:337:7' ElectricalID_FOC_output.activeState = uint16(160); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 160U;

        /* '<S1>:337:8' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        rtElectricalID_6ph_codegen_DW->e_n = roundf(3.0F /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
          if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
            rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)
              rtElectricalID_6ph_codegen_DW->e_n;
          } else {
            rtElectricalID_6ph_codegen_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID_6ph_codegen_DW->wait_count = MAX_uint32_T;
        }
      } else {
        /* '<S1>:361:6' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;

     case IN_waitAccept:
      /* During 'waitAccept': '<S1>:1028' */
      /* '<S1>:420:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:420' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_calculatePIcontroller;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'calculatePIcontroller': '<S1>:284' */
        /* state6.0 */
        /* '<S1>:284:4' ElectricalID_FOC_output.activeState = uint16(149); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 149U;

        /* '<S1>:284:5' ElectricalID_FOC_output = ControllerParameter(ElectricalID_FOC_output,... */
        /* '<S1>:284:6'     bandwidthCurrentControl,ElectricalID_output.PMSM_parameters,dampingFactor,psiOverJ); */
        rtElectricalID_6ph_codegen_DW->b =
          rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output;

        /* Merge: '<S1>/ Merge ' */
        ControllerParameter(&rtElectricalID_6ph_codegen_DW->b,
                            rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl,
                            rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm,
                            rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry,
                            rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry,
                            rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs,
                            rtElectricalID_6ph_codegen_DW->dampingFactor,
                            rtElectricalID_6ph_codegen_DW->psiOverJ);

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output =
          rtElectricalID_6ph_codegen_DW->b;
      }
      break;

     case IN_waitLock:
      /* During 'waitLock': '<S1>:1021' */
      /* '<S1>:1026:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:1026' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response5;
        rtElectricalID_6ph_codegen_DW->counter_f = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array[0], 0, sizeof
               (real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z = 1U;
        rtElectricalID_6ph_codegen_DW->V0 = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response5' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response */
        /* Entry Internal: Subchart_Step_Response */
        /* Transition: '<S7>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_s3Z5HukMf8eGhX4LkL6qsaD_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S7>:35' */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
        }

        /* '<S7>:35:3' finished_flag = false; */
        rtElectricalID_6ph_codegen_DW->finish_subsystem = false;

        /* current_meas_array(:) = single(0); */
        /* Vstep(:) = single(0); */
        /* counter=uint32(1); */
        /* '<S7>:35:7' activeState = uint16(140)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 142U;

        /* '<S7>:35:8' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[1] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S7>:35:9' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i_k = 0;
             rtElectricalID_6ph_codegen_DW->i_k < 6;
             rtElectricalID_6ph_codegen_DW->i_k++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i_k] = 0.0F;
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i_k] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i_k] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S7>:35:10' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_b =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_n =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_b + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_n < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_n > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_n;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response5' */
        /* set DutyCycles */
      }
      break;

     default:
      /* During 'waitState': '<S1>:428' */
      /* '<S1>:905:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Outport: '<Root>/finishedElectricalID' */
        /* Transition: '<S1>:905' */
        /* Exit 'waitState': '<S1>:428' */
        /* '<S1>:428:19' finishedElectricalID=boolean(1); */
        rtElectricalID_6ph_codegen_Y->finishedElectricalID = true;

        /* Outport: '<Root>/enteredElectricalID' */
        /* '<S1>:428:20' enteredElectricalID=boolean(0); */
        rtElectricalID_6ph_codegen_Y->enteredElectricalID = false;

        /* '<S1>:428:21' reset_FOC_output; */
        reset_FOC_output(rtElectricalID_6ph_codegen_Y);
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
        rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen =
          IN_Waiting;

        /* Entry 'Waiting': '<S1>:902' */
        /* wait for activation of */
        /* ElectricalID */
        /* donothing */
      } else {
        /* '<S1>:428:17' counter = counter + 1; */
        rtElectricalID_6ph_codegen_DW->qY =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->qY;
      }
      break;
    }

    if (guard1) {
      rtElectricalID_6ph_codegen_DW->e_n = roundf(0.5F /
        rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
      if (rtElectricalID_6ph_codegen_DW->e_n < 4.2949673E+9F) {
        if (rtElectricalID_6ph_codegen_DW->e_n >= 0.0F) {
          rtElectricalID_6ph_codegen_DW->qY = (uint32_T)
            rtElectricalID_6ph_codegen_DW->e_n;
        } else {
          rtElectricalID_6ph_codegen_DW->qY = 0U;
        }
      } else {
        rtElectricalID_6ph_codegen_DW->qY = MAX_uint32_T;
      }

      if (rtElectricalID_6ph_codegen_DW->counter ==
          rtElectricalID_6ph_codegen_DW->qY) {
        /* '<S1>:789:22' elseif(counter == uint32(0.5/GlobalConfig.sampleTimeISR)) */
        /* endtime */
        /* '<S1>:789:23' DutyCycle_mod(abs(ia_sum*(GlobalConfig.sampleTimeISR/0.1))); */
        DutyCycle_mod_e(fabsf(rtElectricalID_6ph_codegen_DW->ia_sum *
                              (rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR
          / 0.1F)), rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);

        /* exec fct */
        /* '<S1>:789:24' counter  = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* '<S1>:789:25' ia_sum = single(0.0); */
        rtElectricalID_6ph_codegen_DW->ia_sum = 0.0F;
      }
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
}

/* Model step function */
void ElectricalID_6ph_codegen_step(RT_MODEL_ElectricalID_6ph_cod_t *const
  rtElectricalID_6ph_codegen_M)
{
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW =
    rtElectricalID_6ph_codegen_M->dwork;
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U =
    (ExtU_ElectricalID_6ph_codegen_t *) rtElectricalID_6ph_codegen_M->inputs;
  ExtY_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_Y =
    (ExtY_ElectricalID_6ph_codegen_t *) rtElectricalID_6ph_codegen_M->outputs;

  /* Chart: '<Root>/ElectricalID_6ph_codegen' incorporates:
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/ElectricalIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/ElectricalID_FOC_output'
   */
  /* Gateway: ElectricalID_6ph_codegen */
  /* During: ElectricalID_6ph_codegen */
  if (rtElectricalID_6ph_codegen_DW->is_active_c3_ElectricalID_6ph_c == 0U) {
    /* Entry: ElectricalID_6ph_codegen */
    rtElectricalID_6ph_codegen_DW->is_active_c3_ElectricalID_6ph_c = 1U;

    /* Entry Internal: ElectricalID_6ph_codegen */
    /* Transition: '<S1>:897' */
    rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else if (rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen ==
             IN_ElectricalID) {
    ElectricalID(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
                 rtElectricalID_6ph_codegen_DW);

    /* During 'Waiting': '<S1>:902' */
    /* '<S1>:899:1' sf_internal_predicateOutput = ControlFlags.startElectricalID==1 &&.... */
    /* '<S1>:899:2'  GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
  } else if (rtElectricalID_6ph_codegen_U->ControlFlags.startElectricalID &&
             (!rtElectricalID_6ph_codegen_U->GlobalConfig_out.Reset) &&
             rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:899' */
    rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen =
      IN_ElectricalID;

    /* Entry 'ElectricalID': '<S1>:761' */
    /* '<S1>:761:3' initParams; */
    initParams(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
               rtElectricalID_6ph_codegen_DW);

    /* Outport: '<Root>/enteredElectricalID' */
    /* '<S1>:761:4' ElectricalID_FOC_output.activeState = uint16(100); */
    /* '<S1>:761:5' enteredElectricalID=boolean(1); */
    rtElectricalID_6ph_codegen_Y->enteredElectricalID = true;

    /* Entry Internal 'ElectricalID': '<S1>:761' */
    /* Transition: '<S1>:243' */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_evaluate_Turn_DC;

    /* Entry 'evaluate_Turn_DC': '<S1>:379' */
    /* '<S1>:379:3' ElectricalID_FOC_output.activeState = uint16(110); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 110U;

    /* '<S1>:379:4' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;

    /* '<S1>:379:5' omega_register=single(zeros(5,1)); */
    for (rtElectricalID_6ph_codegen_DW->i = 0; rtElectricalID_6ph_codegen_DW->i <
         5; rtElectricalID_6ph_codegen_DW->i++) {
      rtElectricalID_6ph_codegen_DW->
        omega_register[rtElectricalID_6ph_codegen_DW->i] = 0.0F;
    }

    /* '<S1>:379:6' if(ElectricalIDConfig.dutyCyc > 0.0) */
    if (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.dutyCyc > 0.0F) {
      /* Checks if a manual value for the DutyCycle was set */
      /* '<S1>:379:7' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
      rtElectricalID_6ph_codegen_DW->DutyCycle =
        rtElectricalID_6ph_codegen_U->ElectricalIDConfig.dutyCyc;

      /* '<S1>:379:8' DC_manual = boolean(1); */
      rtElectricalID_6ph_codegen_DW->DC_manual = true;
    } else {
      /* '<S1>:379:9' else */
      /* '<S1>:379:10' DutyCycle = single(0.01); */
      rtElectricalID_6ph_codegen_DW->DutyCycle = 0.01F;
    }

    /* '<S1>:914:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.Reset) {
    /* Transition: '<S1>:914' */
    /* '<S1>:914:2' finishedElectricalID=boolean(0); */
    /* '<S1>:914:3' enteredElectricalID=boolean(0); */
    /* '<S1>:914:4' initParams; */
    initParams(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
               rtElectricalID_6ph_codegen_DW);
    rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  }

  /* End of Chart: '<Root>/ElectricalID_6ph_codegen' */

  /* Outport: '<Root>/ElectricalID_output' incorporates:
   *  Merge: '<S1>/ Merge '
   */
  rtElectricalID_6ph_codegen_Y->ElectricalID_output =
    rtElectricalID_6ph_codegen_DW->ElectricalID_output;
}

/* Model initialize function */
void ElectricalID_6ph_codegen_initialize(RT_MODEL_ElectricalID_6ph_cod_t *const
  rtElectricalID_6ph_codegen_M)
{
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW =
    rtElectricalID_6ph_codegen_M->dwork;
  ExtY_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_Y =
    (ExtY_ElectricalID_6ph_codegen_t *) rtElectricalID_6ph_codegen_M->outputs;

  {
    int32_T i;
    static const real32_T tmp_0[36] = { 1.0F, -0.5F, -0.5F, 0.866025388F,
      -0.866025388F, -2.22044605E-16F, 4.0292992E-16F, 0.866025388F,
      -0.866025388F, 0.5F, 0.5F, -1.0F, 1.0F, -0.5F, -0.5F, -0.866025388F,
      0.866025388F, -8.11506533E-16F, -1.47195872E-15F, -0.866025388F,
      0.866025388F, 0.5F, 0.5F, -1.0F, 1.0F, 1.0F, 1.0F, 3.03318581E-16F,
      -6.53560669E-16F, 1.03355119E-15F, -5.17937724E-16F, -1.83585349E-15F,
      -1.27277098E-15F, 1.0F, 1.0F, 1.0F };

    /* SystemInitialize for Chart: '<Root>/ElectricalID_6ph_codegen' incorporates:
     *  Merge: '<S1>/ Merge '
     *  Outport: '<Root>/ElectricalID_FOC_output'
     */
    rtElectricalID_6ph_codegen_DW->counter_ha = 1U;
    rtElectricalID_6ph_codegen_DW->z_d = 1U;
    rtElectricalID_6ph_codegen_DW->counter_a = 1U;
    rtElectricalID_6ph_codegen_DW->z_m = 1U;
    rtElectricalID_6ph_codegen_DW->counter_k = 1U;
    rtElectricalID_6ph_codegen_DW->z_n = 1U;
    rtElectricalID_6ph_codegen_DW->counter_l = 1U;
    rtElectricalID_6ph_codegen_DW->z_g = 1U;
    rtElectricalID_6ph_codegen_DW->counter_h = 1U;
    rtElectricalID_6ph_codegen_DW->z_a = 1U;
    for (i = 0; i < 36; i++) {
      real32_T tmp;
      tmp = tmp_0[i];
      rtElectricalID_6ph_codegen_DW->inv_VSD_ph[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_m[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_h[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_p[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_b[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD[i] = tmp;
    }

    rtElectricalID_6ph_codegen_DW->counter_f = 1U;
    rtElectricalID_6ph_codegen_DW->z = 1U;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.d = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.q = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref.zero = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 0U;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed =
      false;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_current =
      false;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
      false;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_id_out = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_iq_out = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_n_out = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_id_out = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_iq_out = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_n_out = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm =
      0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry =
      0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry =
      0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
      = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs
      = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared
      = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.I_max_Ampere
      = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.x = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.y = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z1 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z2 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.x = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.y = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z1 = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z2 = 0.0F;

    /* End of SystemInitialize for Chart: '<Root>/ElectricalID_6ph_codegen' */
    /* '<S1>:922:7' sineCounter = uint32(0); */
    /* initialize */
    /* '<S1>:922:8' u = single(0); */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
#endif