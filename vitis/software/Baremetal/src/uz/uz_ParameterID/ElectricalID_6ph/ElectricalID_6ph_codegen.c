/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.c
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 3.86
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Apr 25 09:57:17 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "ElectricalID_6ph_codegen.h"
#include "../rt_hypotf.h"
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
#define IN_alignRotor_d_on             ((uint8_T)8U)
#define IN_endState                    ((uint8_T)9U)
#define IN_findDutyCycle               ((uint8_T)10U)
#define IN_gatherResults               ((uint8_T)11U)
#define IN_measure_induced_voltage     ((uint8_T)12U)
#define IN_measure_psiPM               ((uint8_T)13U)
#define IN_rotorInertiaEstimation      ((uint8_T)14U)
#define IN_stop                        ((uint8_T)15U)
#define IN_waitFree                    ((uint8_T)16U)
#define IN_waitLock                    ((uint8_T)17U)
#define IN_waitSetRPM                  ((uint8_T)18U)
#define IN_waitState                   ((uint8_T)19U)

/* Forward declaration for local functions */
static void initParams(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void reset_FOC_output(ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y);
static void Subchart_St_MeasureStepRespon_n(real32_T v_dq_d, real32_T i_dq_d,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm(const uz_ParaID_GlobalConfig_t *GlobalConfig, real32_T *
  R_est, real32_T *L_est, boolean_T *updateJ_m, real32_T *lambda_c, real32_T
  *e_h4, const uint16_T *n_iters_f, real32_T H_bn[4], real32_T i_est_n[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart__b_MeasureStepRespon_g(real32_T v_dq_x, real32_T i_dq_x,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_m(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_g, real32_T *lambda_m,
  real32_T *e_h, const uint16_T *n_iters_k, real32_T H_f4[4], real32_T i_est_a
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart_bt_MeasureStepRespon_p(real32_T v_dq_y, real32_T i_dq_y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_j(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_b, real32_T *lambda_a,
  real32_T *e_a, const uint16_T *n_iters_bs, real32_T H_b[4], real32_T i_est_k
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchar_btw_MeasureStepRespon_k(real32_T v_dq_z1, real32_T i_dq_z1,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_a(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_k, real32_T *lambda_p,
  real32_T *e_j, const uint16_T *n_iters_g, real32_T H_f[4], real32_T i_est_ez
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subcha_btw5_MeasureStepRespon_g(real32_T v_dq_z2, real32_T i_dq_z2,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_ak(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_o, real32_T *lambda_h,
  real32_T *e_e, const uint16_T *n_iters_b, real32_T H_p[4], real32_T i_est_g
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void ControllerParameter(uz_ParaID_Controller_Parameters_output_t
  *FOC_out_old, real32_T bandwidthCurrentControl, real32_T PMSM_config_R_ph_Ohm,
  real32_T PMSM_config_Ld_Henry, real32_T PMSM_config_Lq_Henry, real32_T
  PMSM_config_polePairs, real32_T damping, real32_T psiOverJ);
static void Subch_btw5m_MeasureStepRespon_e(real32_T v_dq_q, real32_T i_dq_q,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_i(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ, real32_T *lambda,
  real32_T *e, const uint16_T *n_iters, real32_T H[4], real32_T i_est_e[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void SetpVectorToDutyCycle6ph(uz_ParaID_ElectricalID_output_t
  *ElectricalID_output_in, real32_T VDC, const real32_T SetpVector[6]);
static void DutyCycle_mod(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void findDutyCycle(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static real32_T cutoff_frequency(real32_T Rp, real32_T Rs, real32_T C);
static real32_T correct_setpoint(real32_T setpoint, real32_T ratSpeed, real32_T
  polepairs);
static void gatherResults(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
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
static void exit_internal_ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, ExtU_ElectricalID_6ph_codegen_t
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
  int32_T i;
  real32_T tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'initParams': '<S1>:88' */
  /* '<S1>:88:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F /
               rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k = (uint32_T)
        tmp;
    } else {
      rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k = 0U;
    }
  } else {
    rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k = MAX_uint32_T;
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
  /* '<S1>:88:26' om_con              = boolean(0); */
  /* '<S1>:88:27' ia_sum              = single(0); */
  rtElectricalID_6ph_codegen_DW->ia_sum = 0.0F;

  /* Outport: '<Root>/ElectricalID_FOC_output' */
  /* '<S1>:88:28' ia_valid            = boolean(0); */
  /* '<S1>:88:29' DC_manual           = boolean(0); */
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

  /* '<S1>:88:63' ElectricalID_output.inductances_6ph.d                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d = 0.0F;

  /* '<S1>:88:64' ElectricalID_output.inductances_6ph.q                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q = 0.0F;

  /* '<S1>:88:65' ElectricalID_output.inductances_6ph.x                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.x = 0.0F;

  /* '<S1>:88:66' ElectricalID_output.inductances_6ph.y                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.y = 0.0F;

  /* '<S1>:88:67' ElectricalID_output.inductances_6ph.z1                  = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z1 = 0.0F;

  /* '<S1>:88:68' ElectricalID_output.inductances_6ph.z2                  = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z2 = 0.0F;

  /* '<S1>:88:69' ElectricalID_output.resistances_6ph.d                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d = 0.0F;

  /* '<S1>:88:70' ElectricalID_output.resistances_6ph.q                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q = 0.0F;

  /* '<S1>:88:71' ElectricalID_output.resistances_6ph.x                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.x = 0.0F;

  /* '<S1>:88:72' ElectricalID_output.resistances_6ph.y                   = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.y = 0.0F;

  /* '<S1>:88:73' ElectricalID_output.resistances_6ph.z1                  = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z1 = 0.0F;

  /* '<S1>:88:74' ElectricalID_output.resistances_6ph.z2                  = single(0.0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z2 = 0.0F;

  /* '<S1>:88:75' ElectricalID_output.psi_pm                              = single([0;0;0;0;0]); */
  /* '<S1>:88:76' ElectricalID_output.psi_pm_angle                        = single([0;0;0;0;0]); */
  for (i = 0; i < 5; i++) {
    /* Merge: '<S1>/ Merge ' */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm[i] = 0.0F;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm_angle[i] = 0.0F;
  }

  /* Merge: '<S1>/ Merge ' */
  /* '<S1>:88:77' ElectricalID_output.set_rpm_val                         = single(0); */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.set_rpm_val = 0.0F;

  /* Outport: '<Root>/finished_voltage_measurement' */
  /* '<S1>:88:78' finished_voltage_measurement                            = false; */
  rtElectricalID_6ph_codegen_Y->finished_voltage_measurement = false;

  /* Outport: '<Root>/enteredElectricalID' */
  /* '<S1>:88:79' enteredElectricalID                                     = boolean(0); */
  rtElectricalID_6ph_codegen_Y->enteredElectricalID = false;

  /*  initialize variables for Levenberg-Marquardt */
  /* '<S1>:88:82' d        			= single(zeros(2048,1)); */
  /* '<S1>:88:83' dp      			= single(zeros(2,1)); */
  /* '<S1>:88:84' e       			= single(0); */
  /* '<S1>:88:85' e_lm  				= single(0); */
  /* '<S1>:88:86' H 					= single(zeros(2,2)); */
  /* '<S1>:88:87' i_est 				= single(zeros(2048,1)); */
  memset(&rtElectricalID_6ph_codegen_DW->d[0], 0, sizeof(real32_T) << 11U);
  memset(&rtElectricalID_6ph_codegen_DW->i_est[0], 0, sizeof(real32_T) << 11U);

  /* '<S1>:88:88' it 					= uint16(0); */
  /* '<S1>:88:89' J 					= single(zeros(2048,2)); */
  /* '<S1>:88:90' k 					= single(0); */
  /* '<S1>:88:91' L0 					= single(0); */
  /* '<S1>:88:92' L_est   			= single(0); */
  rtElectricalID_6ph_codegen_DW->L_est_mb = 0.0F;

  /* '<S1>:88:93' L_lm 				= single(0); */
  /* '<S1>:88:94' Ndata  				= uint16(512); */
  /* '<S1>:88:95' Nparams 			= uint16(2); */
  /* '<S1>:88:96' n_iters 			= uint16(100); */
  /* '<S1>:88:97' R0 					= single(0); */
  /* '<S1>:88:98' R_est 				= single(0); */
  rtElectricalID_6ph_codegen_DW->R_est_c = 0.0F;

  /* '<S1>:88:99' R_lm 				= single(0); */
  /* '<S1>:88:100' V0 					= single(0); */
  /* '<S1>:88:101' lambda  			= single(0.01); */
  /* '<S1>:88:102' updateJ 			= boolean(1); */
  /*  initialize varaibles for PMSM parameters */
  /* '<S1>:88:105' R_corr              = single(0.000); */
  /* 0.060 */
  /*  variables for controller calculation */
  /* '<S1>:88:108' bandwidthCurrentControl = single(1000); */
  rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl = 1000.0F;

  /* '<S1>:88:109' dampingFactor           = single(10.0); */
  rtElectricalID_6ph_codegen_DW->dampingFactor = 10.0F;

  /* '<S1>:88:110' psiOverJ                = single(5000); */
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
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchart_St_MeasureStepRespon_n(real32_T v_dq_d, real32_T i_dq_d,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponsec14_sMWbr9x0gq9qn9qDdVLZeFF_Subchart_Step_Response': '<S2>:39' */
  /* '<S2>:39:2' fns = fieldnames(i_dq); */
  /* '<S2>:39:3' current = i_dq.(fns{index}); */
  /* '<S2>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S2>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_n <= 1024U) {
    /* '<S2>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_n > 1U) {
      uint32_T qY;

      /* '<S2>:39:7' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_n - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_n - 1U >
          rtElectricalID_6ph_codegen_DW->counter_n) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_a4[(int32_T)qY - 1] =
        i_dq_d;

      /* safe 1024 current values to 2D array */
      /* '<S2>:39:8' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_n -
          rtElectricalID_6ph_codegen_DW->counter_n / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S2>:39:9' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_c - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_c - 1U >
            rtElectricalID_6ph_codegen_DW->z_c) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_k[(int32_T)qY - 1] = v_dq_d;

        /* safe Va */
        /* '<S2>:39:10' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_c + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_c + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_c = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_n == 1U) {
      uint32_T qY;

      /* '<S2>:39:12' elseif(counter == 1) */
      /* '<S2>:39:13' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_k[0] = v_dq_d;

      /* safe Va 1st cycle */
      /* '<S2>:39:14' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_c + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_c + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_c = (uint16_T)qY;
    }

    /* '<S2>:39:16' else */
    /* '<S2>:39:17' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_n == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S2>:39:18' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_n - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_n - 1U >
        rtElectricalID_6ph_codegen_DW->counter_n) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_a4[(int32_T)qY - 1] =
      i_dq_d;

    /* safe last current val */
    /* '<S2>:39:19' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_c - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_c - 1U >
        rtElectricalID_6ph_codegen_DW->z_c) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_k[(int32_T)qY - 1] = v_dq_d;

    /* '<S2>:39:20' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_k[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_k[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_a = x / 205.0F;

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
  R_est, real32_T *L_est, boolean_T *updateJ_m, real32_T *lambda_c, real32_T
  *e_h4, const uint16_T *n_iters_f, real32_T H_bn[4], real32_T i_est_n[2048],
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
  for (it = 0; it < *n_iters_f; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S2>:36:26' if updateJ == 1 */
    if (*updateJ_m) {
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
        rtElectricalID_6ph_codegen_DW->J_o[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_a) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_a *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_o[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_a *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S2>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_n[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_a / *R_est);
        rtElectricalID_6ph_codegen_DW->d_m[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_a4[k] - i_est_n[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S2>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_bn[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_bn[tmp] += rtElectricalID_6ph_codegen_DW->J_o[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_o[(i << 11) + i_0];
          }
        }
      }

      /* '<S2>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S2>:36:44' e = dot(d,d); */
        *e_h4 = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_h4 += rtElectricalID_6ph_codegen_DW->d_m[k] *
            rtElectricalID_6ph_codegen_DW->d_m[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S2>:36:49' H(1,1) = H(1,1) + lambda; */
    H_bn[0] += *lambda_c;

    /* '<S2>:36:50' H(2,2)=H(2,2)+lambda; */
    H_bn[3] += *lambda_c;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S2>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_o[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_m[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_o[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_m[k];
    }

    if (fabsf(H_bn[1]) > fabsf(H_bn[0])) {
      r = H_bn[0] / H_bn[1];
      t = 1.0F / (r * H_bn[3] - H_bn[2]);
      b_y_idx_0 = H_bn[3] / H_bn[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_bn[2] / H_bn[1] * t;
      t *= r;
    } else {
      r = H_bn[1] / H_bn[0];
      t = 1.0F / (H_bn[3] - r * H_bn[2]);
      b_y_idx_0 = H_bn[3] / H_bn[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_bn[2] / H_bn[0] * t;
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
      i_est_n[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_a / r);
      rtElectricalID_6ph_codegen_DW->d_m[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_a4[k] - i_est_n[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_m[k] *
        rtElectricalID_6ph_codegen_DW->d_m[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S2>:36:66' if e_lm < e */
    if (e_lm < *e_h4) {
      /* '<S2>:36:67' lambda = lambda/10; */
      *lambda_c /= 10.0F;

      /* '<S2>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S2>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S2>:36:70' e = e_lm; */
      *e_h4 = e_lm;

      /* '<S2>:36:71' updateJ = boolean(1); */
      *updateJ_m = true;
    } else {
      /* '<S2>:36:72' else */
      /* '<S2>:36:73' updateJ = boolean(0); */
      *updateJ_m = false;

      /* '<S2>:36:74' lambda = lambda*10; */
      *lambda_c *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response1'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchart__b_MeasureStepRespon_g(real32_T v_dq_x, real32_T i_dq_x,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponsec14_suUPVh77ZXqqMHR03zyk1ZB_Subchart_Step_Response': '<S3>:39' */
  /* '<S3>:39:2' fns = fieldnames(i_dq); */
  /* '<S3>:39:3' current = i_dq.(fns{index}); */
  /* '<S3>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S3>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_o <= 1024U) {
    /* '<S3>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_o > 1U) {
      uint32_T qY;

      /* '<S3>:39:7' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_o - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_o - 1U >
          rtElectricalID_6ph_codegen_DW->counter_o) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_a[(int32_T)qY - 1] =
        i_dq_x;

      /* safe 1024 current values to 2D array */
      /* '<S3>:39:8' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_o -
          rtElectricalID_6ph_codegen_DW->counter_o / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S3>:39:9' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_bs - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_bs - 1U >
            rtElectricalID_6ph_codegen_DW->z_bs) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_e[(int32_T)qY - 1] = v_dq_x;

        /* safe Va */
        /* '<S3>:39:10' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_bs + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_bs + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_bs = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_o == 1U) {
      uint32_T qY;

      /* '<S3>:39:12' elseif(counter == 1) */
      /* '<S3>:39:13' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_e[0] = v_dq_x;

      /* safe Va 1st cycle */
      /* '<S3>:39:14' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_bs + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_bs + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_bs = (uint16_T)qY;
    }

    /* '<S3>:39:16' else */
    /* '<S3>:39:17' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_o == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S3>:39:18' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_o - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_o - 1U >
        rtElectricalID_6ph_codegen_DW->counter_o) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_a[(int32_T)qY - 1] =
      i_dq_x;

    /* safe last current val */
    /* '<S3>:39:19' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_bs - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_bs - 1U >
        rtElectricalID_6ph_codegen_DW->z_bs) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_e[(int32_T)qY - 1] = v_dq_x;

    /* '<S3>:39:20' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_e[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_e[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_nx = x / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_g, real32_T *lambda_m,
  real32_T *e_h, const uint16_T *n_iters_k, real32_T H_f4[4], real32_T i_est_a
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
  for (it = 0; it < *n_iters_k; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S3>:36:26' if updateJ == 1 */
    if (*updateJ_g) {
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
        rtElectricalID_6ph_codegen_DW->J_h[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_nx) / (*R_est * *R_est) -
          (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_nx *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_h[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_nx *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S3>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_a[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_nx / *R_est);
        rtElectricalID_6ph_codegen_DW->d_o[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_a[k] - i_est_a[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S3>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_f4[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_f4[tmp] += rtElectricalID_6ph_codegen_DW->J_h[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_h[(i << 11) + i_0];
          }
        }
      }

      /* '<S3>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S3>:36:44' e = dot(d,d); */
        *e_h = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_h += rtElectricalID_6ph_codegen_DW->d_o[k] *
            rtElectricalID_6ph_codegen_DW->d_o[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S3>:36:49' H(1,1) = H(1,1) + lambda; */
    H_f4[0] += *lambda_m;

    /* '<S3>:36:50' H(2,2)=H(2,2)+lambda; */
    H_f4[3] += *lambda_m;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S3>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_h[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_o[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_h[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_o[k];
    }

    if (fabsf(H_f4[1]) > fabsf(H_f4[0])) {
      r = H_f4[0] / H_f4[1];
      t = 1.0F / (r * H_f4[3] - H_f4[2]);
      b_y_idx_0 = H_f4[3] / H_f4[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_f4[2] / H_f4[1] * t;
      t *= r;
    } else {
      r = H_f4[1] / H_f4[0];
      t = 1.0F / (H_f4[3] - r * H_f4[2]);
      b_y_idx_0 = H_f4[3] / H_f4[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_f4[2] / H_f4[0] * t;
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
      i_est_a[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_nx / r);
      rtElectricalID_6ph_codegen_DW->d_o[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_a[k] - i_est_a[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_o[k] *
        rtElectricalID_6ph_codegen_DW->d_o[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S3>:36:66' if e_lm < e */
    if (e_lm < *e_h) {
      /* '<S3>:36:67' lambda = lambda/10; */
      *lambda_m /= 10.0F;

      /* '<S3>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S3>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S3>:36:70' e = e_lm; */
      *e_h = e_lm;

      /* '<S3>:36:71' updateJ = boolean(1); */
      *updateJ_g = true;
    } else {
      /* '<S3>:36:72' else */
      /* '<S3>:36:73' updateJ = boolean(0); */
      *updateJ_g = false;

      /* '<S3>:36:74' lambda = lambda*10; */
      *lambda_m *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response2'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchart_bt_MeasureStepRespon_p(real32_T v_dq_y, real32_T i_dq_y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponsec14_sXsuRAan3TDX1V4pP05BViE_Subchart_Step_Response': '<S4>:39' */
  /* '<S4>:39:2' fns = fieldnames(i_dq); */
  /* '<S4>:39:3' current = i_dq.(fns{index}); */
  /* '<S4>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S4>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_f <= 1024U) {
    /* '<S4>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_f > 1U) {
      uint32_T qY;

      /* '<S4>:39:7' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_f - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_f - 1U >
          rtElectricalID_6ph_codegen_DW->counter_f) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_n[(int32_T)qY - 1] =
        i_dq_y;

      /* safe 1024 current values to 2D array */
      /* '<S4>:39:8' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_f -
          rtElectricalID_6ph_codegen_DW->counter_f / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S4>:39:9' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_p - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_p - 1U >
            rtElectricalID_6ph_codegen_DW->z_p) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_gw[(int32_T)qY - 1] = v_dq_y;

        /* safe Va */
        /* '<S4>:39:10' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_p + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_p + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_p = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_f == 1U) {
      uint32_T qY;

      /* '<S4>:39:12' elseif(counter == 1) */
      /* '<S4>:39:13' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_gw[0] = v_dq_y;

      /* safe Va 1st cycle */
      /* '<S4>:39:14' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_p + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_p + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_p = (uint16_T)qY;
    }

    /* '<S4>:39:16' else */
    /* '<S4>:39:17' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_f == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S4>:39:18' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_f - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_f - 1U >
        rtElectricalID_6ph_codegen_DW->counter_f) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_n[(int32_T)qY - 1] =
      i_dq_y;

    /* safe last current val */
    /* '<S4>:39:19' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_p - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_p - 1U >
        rtElectricalID_6ph_codegen_DW->z_p) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_gw[(int32_T)qY - 1] = v_dq_y;

    /* '<S4>:39:20' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_gw[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_gw[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_n = x / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_b, real32_T *lambda_a,
  real32_T *e_a, const uint16_T *n_iters_bs, real32_T H_b[4], real32_T i_est_k
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
  for (it = 0; it < *n_iters_bs; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S4>:36:26' if updateJ == 1 */
    if (*updateJ_b) {
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
        rtElectricalID_6ph_codegen_DW->J_cu[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_n) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_cu[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S4>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_k[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_n / *R_est);
        rtElectricalID_6ph_codegen_DW->d_l[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_n[k] - i_est_k[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S4>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_b[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_b[tmp] += rtElectricalID_6ph_codegen_DW->J_cu[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_cu[(i << 11) + i_0];
          }
        }
      }

      /* '<S4>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S4>:36:44' e = dot(d,d); */
        *e_a = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_a += rtElectricalID_6ph_codegen_DW->d_l[k] *
            rtElectricalID_6ph_codegen_DW->d_l[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S4>:36:49' H(1,1) = H(1,1) + lambda; */
    H_b[0] += *lambda_a;

    /* '<S4>:36:50' H(2,2)=H(2,2)+lambda; */
    H_b[3] += *lambda_a;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S4>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_cu[((k / 1024) << 11) + k % 1024]
        * rtElectricalID_6ph_codegen_DW->d_l[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_cu[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_l[k];
    }

    if (fabsf(H_b[1]) > fabsf(H_b[0])) {
      r = H_b[0] / H_b[1];
      t = 1.0F / (r * H_b[3] - H_b[2]);
      b_y_idx_0 = H_b[3] / H_b[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_b[2] / H_b[1] * t;
      t *= r;
    } else {
      r = H_b[1] / H_b[0];
      t = 1.0F / (H_b[3] - r * H_b[2]);
      b_y_idx_0 = H_b[3] / H_b[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_b[2] / H_b[0] * t;
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
      i_est_k[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_n / r);
      rtElectricalID_6ph_codegen_DW->d_l[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_n[k] - i_est_k[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_l[k] *
        rtElectricalID_6ph_codegen_DW->d_l[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S4>:36:66' if e_lm < e */
    if (e_lm < *e_a) {
      /* '<S4>:36:67' lambda = lambda/10; */
      *lambda_a /= 10.0F;

      /* '<S4>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S4>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S4>:36:70' e = e_lm; */
      *e_a = e_lm;

      /* '<S4>:36:71' updateJ = boolean(1); */
      *updateJ_b = true;
    } else {
      /* '<S4>:36:72' else */
      /* '<S4>:36:73' updateJ = boolean(0); */
      *updateJ_b = false;

      /* '<S4>:36:74' lambda = lambda*10; */
      *lambda_a *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response3'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchar_btw_MeasureStepRespon_k(real32_T v_dq_z1, real32_T i_dq_z1,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponsec14_siDrVKQJrmgth2tO4iYKAXD_Subchart_Step_Response': '<S5>:39' */
  /* '<S5>:39:2' fns = fieldnames(i_dq); */
  /* '<S5>:39:3' current = i_dq.(fns{index}); */
  /* '<S5>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S5>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_g <= 1024U) {
    /* '<S5>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_g > 1U) {
      uint32_T qY;

      /* '<S5>:39:7' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_g - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_g - 1U >
          rtElectricalID_6ph_codegen_DW->counter_g) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_i[(int32_T)qY - 1] =
        i_dq_z1;

      /* safe 1024 current values to 2D array */
      /* '<S5>:39:8' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_g -
          rtElectricalID_6ph_codegen_DW->counter_g / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S5>:39:9' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_k - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_k - 1U >
            rtElectricalID_6ph_codegen_DW->z_k) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_j[(int32_T)qY - 1] = v_dq_z1;

        /* safe Va */
        /* '<S5>:39:10' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_k + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_k + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_k = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_g == 1U) {
      uint32_T qY;

      /* '<S5>:39:12' elseif(counter == 1) */
      /* '<S5>:39:13' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_j[0] = v_dq_z1;

      /* safe Va 1st cycle */
      /* '<S5>:39:14' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_k + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_k + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_k = (uint16_T)qY;
    }

    /* '<S5>:39:16' else */
    /* '<S5>:39:17' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_g == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S5>:39:18' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_g - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_g - 1U >
        rtElectricalID_6ph_codegen_DW->counter_g) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_i[(int32_T)qY - 1] =
      i_dq_z1;

    /* safe last current val */
    /* '<S5>:39:19' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_k - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_k - 1U >
        rtElectricalID_6ph_codegen_DW->z_k) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_j[(int32_T)qY - 1] = v_dq_z1;

    /* '<S5>:39:20' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_j[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_j[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_k = x / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_k, real32_T *lambda_p,
  real32_T *e_j, const uint16_T *n_iters_g, real32_T H_f[4], real32_T i_est_ez
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
  for (it = 0; it < *n_iters_g; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S5>:36:26' if updateJ == 1 */
    if (*updateJ_k) {
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
        rtElectricalID_6ph_codegen_DW->J_p[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_k) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_p[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S5>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_ez[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_k / *R_est);
        rtElectricalID_6ph_codegen_DW->d_h[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_i[k] - i_est_ez[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S5>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_f[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_f[tmp] += rtElectricalID_6ph_codegen_DW->J_p[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_p[(i << 11) + i_0];
          }
        }
      }

      /* '<S5>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S5>:36:44' e = dot(d,d); */
        *e_j = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_j += rtElectricalID_6ph_codegen_DW->d_h[k] *
            rtElectricalID_6ph_codegen_DW->d_h[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S5>:36:49' H(1,1) = H(1,1) + lambda; */
    H_f[0] += *lambda_p;

    /* '<S5>:36:50' H(2,2)=H(2,2)+lambda; */
    H_f[3] += *lambda_p;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S5>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_p[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_h[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_p[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_h[k];
    }

    if (fabsf(H_f[1]) > fabsf(H_f[0])) {
      r = H_f[0] / H_f[1];
      t = 1.0F / (r * H_f[3] - H_f[2]);
      b_y_idx_0 = H_f[3] / H_f[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_f[2] / H_f[1] * t;
      t *= r;
    } else {
      r = H_f[1] / H_f[0];
      t = 1.0F / (H_f[3] - r * H_f[2]);
      b_y_idx_0 = H_f[3] / H_f[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_f[2] / H_f[0] * t;
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
      i_est_ez[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_k / r);
      rtElectricalID_6ph_codegen_DW->d_h[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_i[k] - i_est_ez[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_h[k] *
        rtElectricalID_6ph_codegen_DW->d_h[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S5>:36:66' if e_lm < e */
    if (e_lm < *e_j) {
      /* '<S5>:36:67' lambda = lambda/10; */
      *lambda_p /= 10.0F;

      /* '<S5>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S5>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S5>:36:70' e = e_lm; */
      *e_j = e_lm;

      /* '<S5>:36:71' updateJ = boolean(1); */
      *updateJ_k = true;
    } else {
      /* '<S5>:36:72' else */
      /* '<S5>:36:73' updateJ = boolean(0); */
      *updateJ_k = false;

      /* '<S5>:36:74' lambda = lambda*10; */
      *lambda_p *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response4'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subcha_btw5_MeasureStepRespon_g(real32_T v_dq_z2, real32_T i_dq_z2,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponsec14_swiDrWmrnFiNemiFZhejbKE_Subchart_Step_Response': '<S6>:39' */
  /* '<S6>:39:2' fns = fieldnames(i_dq); */
  /* '<S6>:39:3' current = i_dq.(fns{index}); */
  /* '<S6>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S6>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_j <= 1024U) {
    /* '<S6>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_j > 1U) {
      uint32_T qY;

      /* '<S6>:39:7' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_j - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_j - 1U >
          rtElectricalID_6ph_codegen_DW->counter_j) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_j[(int32_T)qY - 1] =
        i_dq_z2;

      /* safe 1024 current values to 2D array */
      /* '<S6>:39:8' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_j -
          rtElectricalID_6ph_codegen_DW->counter_j / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S6>:39:9' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z_b - 1U;
        if (rtElectricalID_6ph_codegen_DW->z_b - 1U >
            rtElectricalID_6ph_codegen_DW->z_b) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep_g[(int32_T)qY - 1] = v_dq_z2;

        /* safe Va */
        /* '<S6>:39:10' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z_b + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_b + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_b = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_j == 1U) {
      uint32_T qY;

      /* '<S6>:39:12' elseif(counter == 1) */
      /* '<S6>:39:13' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep_g[0] = v_dq_z2;

      /* safe Va 1st cycle */
      /* '<S6>:39:14' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z_b + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_b + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_b = (uint16_T)qY;
    }

    /* '<S6>:39:16' else */
    /* '<S6>:39:17' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_j == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S6>:39:18' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_j - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_j - 1U >
        rtElectricalID_6ph_codegen_DW->counter_j) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array_j[(int32_T)qY - 1] =
      i_dq_z2;

    /* safe last current val */
    /* '<S6>:39:19' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z_b - 1U;
    if (rtElectricalID_6ph_codegen_DW->z_b - 1U >
        rtElectricalID_6ph_codegen_DW->z_b) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep_g[(int32_T)qY - 1] = v_dq_z2;

    /* '<S6>:39:20' V0 = mean(Vstep); */
    x = rtElectricalID_6ph_codegen_DW->Vstep_g[0];
    for (k = 0; k < 204; k++) {
      x += rtElectricalID_6ph_codegen_DW->Vstep_g[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_g = x / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_o, real32_T *lambda_h,
  real32_T *e_e, const uint16_T *n_iters_b, real32_T H_p[4], real32_T i_est_g
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
  for (it = 0; it < *n_iters_b; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S6>:36:26' if updateJ == 1 */
    if (*updateJ_o) {
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
        rtElectricalID_6ph_codegen_DW->J_c[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_g) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_g *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_c[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_g *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S6>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_g[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_g / *R_est);
        rtElectricalID_6ph_codegen_DW->d_i[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_j[k] - i_est_g[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S6>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_p[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_p[tmp] += rtElectricalID_6ph_codegen_DW->J_c[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_c[(i << 11) + i_0];
          }
        }
      }

      /* '<S6>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S6>:36:44' e = dot(d,d); */
        *e_e = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_e += rtElectricalID_6ph_codegen_DW->d_i[k] *
            rtElectricalID_6ph_codegen_DW->d_i[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S6>:36:49' H(1,1) = H(1,1) + lambda; */
    H_p[0] += *lambda_h;

    /* '<S6>:36:50' H(2,2)=H(2,2)+lambda; */
    H_p[3] += *lambda_h;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S6>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_c[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_i[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_c[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_i[k];
    }

    if (fabsf(H_p[1]) > fabsf(H_p[0])) {
      r = H_p[0] / H_p[1];
      t = 1.0F / (r * H_p[3] - H_p[2]);
      b_y_idx_0 = H_p[3] / H_p[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_p[2] / H_p[1] * t;
      t *= r;
    } else {
      r = H_p[1] / H_p[0];
      t = 1.0F / (H_p[3] - r * H_p[2]);
      b_y_idx_0 = H_p[3] / H_p[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_p[2] / H_p[0] * t;
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
      i_est_g[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_g / r);
      rtElectricalID_6ph_codegen_DW->d_i[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_j[k] - i_est_g[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_i[k] *
        rtElectricalID_6ph_codegen_DW->d_i[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S6>:36:66' if e_lm < e */
    if (e_lm < *e_e) {
      /* '<S6>:36:67' lambda = lambda/10; */
      *lambda_h /= 10.0F;

      /* '<S6>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S6>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S6>:36:70' e = e_lm; */
      *e_e = e_lm;

      /* '<S6>:36:71' updateJ = boolean(1); */
      *updateJ_o = true;
    } else {
      /* '<S6>:36:72' else */
      /* '<S6>:36:73' updateJ = boolean(0); */
      *updateJ_o = false;

      /* '<S6>:36:74' lambda = lambda*10; */
      *lambda_h *= 10.0F;
    }
  }
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

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response5'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subch_btw5m_MeasureStepRespon_e(real32_T v_dq_q, real32_T i_dq_q,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponsec14_sOrida1dLJHFhz3jwws1fnH_Subchart_Step_Response': '<S7>:39' */
  /* '<S7>:39:2' fns = fieldnames(i_dq); */
  /* '<S7>:39:3' current = i_dq.(fns{index}); */
  /* '<S7>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S7>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_i <= 1024U) {
    /* '<S7>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_i > 1U) {
      uint32_T qY;

      /* '<S7>:39:7' current_meas_array(counter-1) = current; */
      qY = rtElectricalID_6ph_codegen_DW->counter_i - /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter_i - 1U >
          rtElectricalID_6ph_codegen_DW->counter_i) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array[(int32_T)qY - 1] =
        i_dq_q;

      /* safe 1024 current values to 2D array */
      /* '<S7>:39:8' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_i -
          rtElectricalID_6ph_codegen_DW->counter_i / 5U * 5U == 0U) {
        /* exec every 5th cycle */
        /* '<S7>:39:9' Vstep(z-1) = voltage; */
        qY = rtElectricalID_6ph_codegen_DW->z - 1U;
        if (rtElectricalID_6ph_codegen_DW->z - 1U >
            rtElectricalID_6ph_codegen_DW->z) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->Vstep[(int32_T)qY - 1] = v_dq_q;

        /* safe Va */
        /* '<S7>:39:10' z = z + 1; */
        qY = rtElectricalID_6ph_codegen_DW->z + 1U;
        if (rtElectricalID_6ph_codegen_DW->z + 1U > 65535U) {
          qY = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z = (uint16_T)qY;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_i == 1U) {
      uint32_T qY;

      /* '<S7>:39:12' elseif(counter == 1) */
      /* '<S7>:39:13' Vstep(1) = voltage; */
      rtElectricalID_6ph_codegen_DW->Vstep[0] = v_dq_q;

      /* safe Va 1st cycle */
      /* '<S7>:39:14' z = z + 1; */
      qY = rtElectricalID_6ph_codegen_DW->z + 1U;
      if (rtElectricalID_6ph_codegen_DW->z + 1U > 65535U) {
        qY = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z = (uint16_T)qY;
    }

    /* '<S7>:39:16' else */
    /* '<S7>:39:17' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_i == 1025U) {
    real32_T x;
    uint32_T qY;

    /* '<S7>:39:18' current_meas_array(counter-1) = current; */
    qY = rtElectricalID_6ph_codegen_DW->counter_i - /*MW:OvSatOk*/ 1U;
    if (rtElectricalID_6ph_codegen_DW->counter_i - 1U >
        rtElectricalID_6ph_codegen_DW->counter_i) {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->current_meas_array[(int32_T)qY - 1] = i_dq_q;

    /* safe last current val */
    /* '<S7>:39:19' Vstep(z-1) = voltage; */
    qY = rtElectricalID_6ph_codegen_DW->z - 1U;
    if (rtElectricalID_6ph_codegen_DW->z - 1U > rtElectricalID_6ph_codegen_DW->z)
    {
      qY = 0U;
    }

    rtElectricalID_6ph_codegen_DW->Vstep[(int32_T)qY - 1] = v_dq_q;

    /* '<S7>:39:20' V0 = mean(Vstep); */
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
        rtElectricalID_6ph_codegen_DW->d_n[k] =
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
          *e += rtElectricalID_6ph_codegen_DW->d_n[k] *
            rtElectricalID_6ph_codegen_DW->d_n[k];
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
        rtElectricalID_6ph_codegen_DW->d_n[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J[(((k + 1024) / 1024) << 11) +
        (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_n[k];
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
      rtElectricalID_6ph_codegen_DW->d_n[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_e[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_n[k] *
        rtElectricalID_6ph_codegen_DW->d_n[k];
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
 * function [ElectricalID_output] = SetpVectorToDutyCycle6ph(ElectricalID_output_in,VDC,SetpVector)
 * Copy ElectricalID_output
 */
static void SetpVectorToDutyCycle6ph(uz_ParaID_ElectricalID_output_t
  *ElectricalID_output_in, real32_T VDC, const real32_T SetpVector[6])
{
  real32_T DutyCycle;

  /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
  /* Write DutyCycle to ElectricalID_output */
  /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[0] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_0 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_0 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_0 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[1] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_2 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_2 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_2 = DutyCycle;
  }

  /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
  /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
  DutyCycle = (SetpVector[2] / (VDC / 2.0F) + 1.0F) / 2.0F;

  /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
  if (DutyCycle < 0.0F) {
    /* 'GenerateDutyCycle:4' out = single(0); */
    ElectricalID_output_in->PWM_Switch_4 = 0.0F;
  } else if (DutyCycle > 1.0F) {
    /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
    /* 'GenerateDutyCycle:6' out = single(1); */
    ElectricalID_output_in->PWM_Switch_4 = 1.0F;
  } else {
    /* 'GenerateDutyCycle:7' else */
    /* 'GenerateDutyCycle:8' out = DutyCycle; */
    ElectricalID_output_in->PWM_Switch_4 = DutyCycle;
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
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function DutyCycle_mod(ia_reg_in)
 */
static void DutyCycle_mod(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
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
    /* '<S1>:796:6' DC_valid=boolean(0); */
    rtElectricalID_6ph_codegen_DW->DC_valid = false;
  } else {
    /* '<S1>:796:7' else */
    /* '<S1>:796:8' DC_valid=boolean(1); */
    rtElectricalID_6ph_codegen_DW->DC_valid = true;
  }

  /* End of Inport: '<Root>/GlobalConfig' */
  /* '<S1>:796:11' if(DC_valid == 0) */
  if (!rtElectricalID_6ph_codegen_DW->DC_valid) {
    /* Increases the DutyCycle by 0.5% every 0.5 second, if the step response */
    /* is below the current limit */
    /* '<S1>:796:14' DutyCycle = DutyCycle + 0.005; */
    rtElectricalID_6ph_codegen_DW->DutyCycle += 0.005F;

    /* Simulation 0.001 | Real 0.005 */
  }
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void findDutyCycle(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  /* Inport: '<Root>/ElectricalIDConfig' */
  /* During 'findDutyCycle': '<S1>:789' */
  /* '<S1>:921:1' sf_internal_predicateOutput = DC_valid==1 && ElectricalIDConfig.manual_offset<0; */
  if (rtElectricalID_6ph_codegen_DW->DC_valid &&
      (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.manual_offset < 0.0F)) {
    /* Inport: '<Root>/ActualValues' */
    /* Transition: '<S1>:921' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:30' ref_amplitude = single(DutyCycle*ActualValues.V_DC); */
    rtElectricalID_6ph_codegen_DW->ref_amplitude =
      rtElectricalID_6ph_codegen_DW->DutyCycle *
      rtElectricalID_6ph_codegen_U->ActualValues.V_DC;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:789:31' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_alignRotor_d_on;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'alignRotor_d_on': '<S1>:3' */
    /* '<S1>:3:4' ElectricalID_FOC_output.activeState = uint16(120); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 120U;

    /* '<S1>:3:5' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;

    /* '<S1>:1114:1' sf_internal_predicateOutput = DC_valid==1 && ElectricalIDConfig.manual_offset>=0; */
  } else if (rtElectricalID_6ph_codegen_DW->DC_valid &&
             (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.manual_offset >=
              0.0F)) {
    /* Inport: '<Root>/ActualValues' */
    /* Transition: '<S1>:1114' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:30' ref_amplitude = single(DutyCycle*ActualValues.V_DC); */
    rtElectricalID_6ph_codegen_DW->ref_amplitude =
      rtElectricalID_6ph_codegen_DW->DutyCycle *
      rtElectricalID_6ph_codegen_U->ActualValues.V_DC;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:789:31' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitLock;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'waitLock': '<S1>:1021' */
    /* '<S1>:1021:3' ElectricalID_FOC_output.activeState = uint16(130); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 130U;

    /* '<S1>:789:15' if(DC_valid==0) */
  } else if (!rtElectricalID_6ph_codegen_DW->DC_valid) {
    real32_T tmp;
    uint32_T qY;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:789:16' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
      rtElectricalID_6ph_codegen_DW->DutyCycle;

    /* Inport: '<Root>/GlobalConfig' */
    /* Set DC */
    /* '<S1>:789:17' if(counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
    tmp = roundf(0.4F /
                 rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
    if (tmp < 4.2949673E+9F) {
      if (tmp >= 0.0F) {
        qY = (uint32_T)tmp;
      } else {
        qY = 0U;
      }
    } else {
      qY = MAX_uint32_T;
    }

    if (rtElectricalID_6ph_codegen_DW->counter < qY) {
      /* Wait several time for step response to rise */
      /* '<S1>:789:18' counter = counter +1; */
      qY = rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter + 1U <
          rtElectricalID_6ph_codegen_DW->counter) {
        qY = MAX_uint32_T;
      }

      rtElectricalID_6ph_codegen_DW->counter = qY;
    } else {
      boolean_T guard1 = false;
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          qY = (uint32_T)tmp;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      guard1 = false;
      if (rtElectricalID_6ph_codegen_DW->counter >= qY) {
        /* Inport: '<Root>/GlobalConfig' */
        tmp = roundf(0.5F /
                     rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (tmp < 4.2949673E+9F) {
          if (tmp >= 0.0F) {
            qY = (uint32_T)tmp;
          } else {
            qY = 0U;
          }
        } else {
          qY = MAX_uint32_T;
        }

        if (rtElectricalID_6ph_codegen_DW->counter < qY) {
          /* '<S1>:789:19' elseif(counter >= uint32(0.4/GlobalConfig.sampleTimeISR) &&.... */
          /* '<S1>:789:20'             counter < uint32(0.5/GlobalConfig.sampleTimeISR)) */
          /* . */
          /* record current - WHY NOW? */
          /* '<S1>:789:21' counter = counter +1; */
          qY = rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter + 1U <
              rtElectricalID_6ph_codegen_DW->counter) {
            qY = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter = qY;

          /* Inport: '<Root>/ActualValues' */
          /* '<S1>:789:22' ia_sum=ia_sum+single(ActualValues.i_abc_6ph.a1); */
          rtElectricalID_6ph_codegen_DW->ia_sum +=
            rtElectricalID_6ph_codegen_U->ActualValues.i_abc_6ph.a1;

          /* integral of current - WHY? */
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        /* Inport: '<Root>/GlobalConfig' */
        tmp = roundf(0.5F /
                     rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (tmp < 4.2949673E+9F) {
          if (tmp >= 0.0F) {
            qY = (uint32_T)tmp;
          } else {
            qY = 0U;
          }
        } else {
          qY = MAX_uint32_T;
        }

        if (rtElectricalID_6ph_codegen_DW->counter == qY) {
          /* Inport: '<Root>/GlobalConfig' */
          /* '<S1>:789:23' elseif(counter == uint32(0.5/GlobalConfig.sampleTimeISR)) */
          /* endtime */
          /* '<S1>:789:24' DutyCycle_mod(abs(ia_sum*(GlobalConfig.sampleTimeISR/0.1))); */
          DutyCycle_mod(fabsf(rtElectricalID_6ph_codegen_DW->ia_sum *
                              (rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR
                               / 0.1F)), rtElectricalID_6ph_codegen_U,
                        rtElectricalID_6ph_codegen_DW);

          /* exec fct */
          /* '<S1>:789:25' counter  = uint32(1); */
          rtElectricalID_6ph_codegen_DW->counter = 1U;

          /* '<S1>:789:26' ia_sum = single(0.0); */
          rtElectricalID_6ph_codegen_DW->ia_sum = 0.0F;
        }
      }
    }
  }

  /* End of Inport: '<Root>/ElectricalIDConfig' */
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function out = cutoff_frequency(Rp,Rs,C)
 * cutoff_frequency determines cutoff frequency for given filter
 *    uses filter configuration with 2R and a C
 *  function:
 */
static real32_T cutoff_frequency(real32_T Rp, real32_T Rs, real32_T C)
{
  /* MATLAB Function 'cutoff_frequency': '<S1>:1064' */
  /* '<S1>:1064:5' resistance = Rp*Rs/(Rp+Rs); */
  /* '<S1>:1064:6' out = 1/(2*pi*resistance*C); */
  return 1.0F / (Rp * Rs / (Rp + Rs) * 6.28318548F * C);
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function out = correct_setpoint(setpoint,ratSpeed,polepairs)
 * correct_setpoint corrects the requested rpm
 *    ties the rpm to rated speed if its higher or rounds it to nearest
 *    hundred
 *  function:
 *  if corrected_setpoint_rpm is larger than n_ref set it to n_ref
 */
static real32_T correct_setpoint(real32_T setpoint, real32_T ratSpeed, real32_T
  polepairs)
{
  real32_T tmp;
  uint32_T T_fundamental;
  uint32_T x_0;

  /* MATLAB Function 'correct_setpoint': '<S1>:1073' */
  /* '<S1>:1073:7' if(setpoint>ratSpeed) */
  if (setpoint > ratSpeed) {
    /* '<S1>:1073:8' setpoint = ratSpeed; */
    setpoint = ratSpeed;
  }

  /* '<S1>:1073:10' T_fundamental = uint32(floor(setpoint/single(60)*polepairs)); */
  tmp = floorf(setpoint / 60.0F * polepairs);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      T_fundamental = (uint32_T)tmp;
    } else {
      T_fundamental = 0U;
    }
  } else {
    T_fundamental = MAX_uint32_T;
  }

  /*  find integer multiple of FFT window */
  /* '<S1>:1073:12' while mod(uint32(ratSpeed),T_fundamental) */
  tmp = roundf(ratSpeed);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      x_0 = (uint32_T)tmp;
    } else {
      x_0 = 0U;
    }
  } else {
    x_0 = MAX_uint32_T;
  }

  int32_T exitg1;
  uint32_T x;
  do {
    exitg1 = 0;
    x = x_0;
    if (T_fundamental != 0U) {
      x = x_0 - x_0 / T_fundamental * T_fundamental;
    }

    if (x != 0U) {
      /* '<S1>:1073:13' setpoint = setpoint-1; */
      setpoint--;

      /* '<S1>:1073:14' T_fundamental = uint32(floor(setpoint/single(60)*polepairs)); */
      tmp = floorf(setpoint / 60.0F * polepairs);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          T_fundamental = (uint32_T)tmp;
        } else {
          T_fundamental = 0U;
        }
      } else {
        T_fundamental = MAX_uint32_T;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  /* '<S1>:1073:16' out = setpoint; */
  return setpoint;
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void gatherResults(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  boolean_T guard1 = false;
  boolean_T tmp_0;

  /* Inport: '<Root>/ElectricalIDConfig' */
  /* During 'gatherResults': '<S1>:1028' */
  /* '<S1>:1104:1' sf_internal_predicateOutput = ~ElectricalIDConfig.extended_psi && GlobalConfig.ACCEPT==1 && ElectricalIDConfig.identLq==1; */
  tmp_0 = !rtElectricalID_6ph_codegen_U->ElectricalIDConfig.extended_psi;

  /* Inport: '<Root>/GlobalConfig' incorporates:
   *  Inport: '<Root>/ElectricalIDConfig'
   */
  guard1 = false;
  if (tmp_0 && rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT &&
      rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
    /* Transition: '<S1>:1104' */
    guard1 = true;

    /* '<S1>:408:1' sf_internal_predicateOutput = ElectricalIDConfig.extended_psi; */
  } else if (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.extended_psi) {
    /* Transition: '<S1>:408' */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitSetRPM;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'waitSetRPM': '<S1>:1047' */
    /* '<S1>:1047:3' ElectricalID_FOC_output.activeState = uint16(155); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 155U;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:1047:4' ElectricalID_output.enable_TriState = boolean([1 1 1]); */
    /* '<S1>:1047:5' ElectricalID_output.enable_TriState_set_2 = boolean([1 1 1]); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] = true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[0] =
      true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] = true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[1] =
      true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] = true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[2] =
      true;

    /* '<S1>:1047:6' f_cutoff = cutoff_frequency(GlobalConfig.voltage_measurement_Rp,.... */
    /* '<S1>:1047:7'     GlobalConfig.voltage_measurement_Rs,GlobalConfig.voltage_measurement_C); */
    /* . */
    /* '<S1>:1047:8' setpoint_rpm = f_cutoff/single(highest_order)/ElectricalID_output.PMSM_parameters.polePairs*single(60); */
    /* '<S1>:1047:9' ElectricalID_output.set_rpm_val = correct_setpoint(setpoint_rpm,GlobalConfig.ratSpeed,.... */
    /* '<S1>:1047:10'     ElectricalID_output.PMSM_parameters.polePairs); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.set_rpm_val =
      correct_setpoint(cutoff_frequency
                       (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_C)
                       / 9.0F /
                       rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs
                       * 60.0F,
                       rtElectricalID_6ph_codegen_U->GlobalConfig_out.ratSpeed,
                       rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs);

    /* . */

    /* '<S1>:1115:1' sf_internal_predicateOutput = ~ElectricalIDConfig.extended_psi && ElectricalIDConfig.identLq==0; */
  } else if (tmp_0 && (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq))
  {
    /* Transition: '<S1>:1115' */
    guard1 = true;
  }

  if (guard1) {
    real32_T tmp;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_measure_psiPM;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'measure_psiPM': '<S1>:1106' */
    /* '<S1>:1106:4' ElectricalID_FOC_output.activeState = uint16(150); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 150U;

    /* '<S1>:1106:5' ElectricalID_FOC_output.enableFOC_speed = boolean(1); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed = true;

    /* '<S1>:1106:6' ElectricalID_FOC_output.n_ref_FOC = ElectricalIDConfig.n_ref_measurement; */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC =
      rtElectricalID_6ph_codegen_U->ElectricalIDConfig.n_ref_measurement;

    /* '<S1>:1106:7' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
    tmp = roundf(3.0F /
                 rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
    if (tmp < 4.2949673E+9F) {
      if (tmp >= 0.0F) {
        rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)tmp;
      } else {
        rtElectricalID_6ph_codegen_DW->wait_count = 0U;
      }
    } else {
      rtElectricalID_6ph_codegen_DW->wait_count = MAX_uint32_T;
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
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
  /* During 'measure_psiPM': '<S1>:1106' */
  /* '<S1>:1111:1' sf_internal_predicateOutput = ElectricalID_output.PMSM_parameters.Psi_PM_Vs > 0; */
  if (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
      > 0.0F) {
    /* Transition: '<S1>:1111' */
    /* Exit 'measure_psiPM': '<S1>:1106' */
    /* '<S1>:1106:20' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_stop;

    /* Entry 'stop': '<S1>:361' */
    /* state 10.1 */
    /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(161); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 161U;

    /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

    /* '<S1>:361:5' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = true;
  } else {
    uint32_T qY;

    /* '<S1>:1106:9' if(counter > wait_count && counter < (wait_count+1025)) */
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

      /* '<S1>:1106:10' measArray1(counter-wait_count) = ActualValues.v_dq.q; */
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

      /* '<S1>:1106:11' d(counter-wait_count) = ActualValues.i_dq.q; */
      rtElectricalID_6ph_codegen_DW->d[(int32_T)qY_tmp - 1] =
        rtElectricalID_6ph_codegen_U->ActualValues.i_dq.q;

      /* '<S1>:1106:12' i_est(counter-wait_count) = ActualValues.omega_el; */
      qY = qY_tmp_tmp;
      if (qY_tmp_tmp > rtElectricalID_6ph_codegen_DW->counter) {
        qY = 0U;
      }

      rtElectricalID_6ph_codegen_DW->i_est[(int32_T)qY - 1] =
        rtElectricalID_6ph_codegen_U->ActualValues.omega_el;
    }

    /* '<S1>:1106:14' if(counter == (wait_count+1025)) */
    qY = rtElectricalID_6ph_codegen_DW->wait_count + 1025U;
    if (rtElectricalID_6ph_codegen_DW->wait_count + 1025U <
        rtElectricalID_6ph_codegen_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if (rtElectricalID_6ph_codegen_DW->counter == qY) {
      real32_T b_x;
      real32_T c_x;

      /* '<S1>:1106:15' ElectricalID_output.PMSM_parameters.Psi_PM_Vs = (mean(measArray1(1:1024))-mean(d(1:1024))*.... */
      /* '<S1>:1106:16'         ElectricalID_output.PMSM_parameters.R_ph_Ohm)/(mean(i_est(1:1024))); */
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

    /* '<S1>:1106:18' counter = counter + 1; */
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

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void exit_internal_ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;

  /* Exit Internal 'ElectricalID': '<S1>:761' */
  switch (rtElectricalID_6ph_codegen_DW->is_ElectricalID) {
   case IN_Subchart_Step_Response:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S2>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S2>:35' */
      /* '<S2>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
      /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
      /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

      /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

      /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

      /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
      rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response1:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S3>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S3>:35' */
      /* '<S3>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
      /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
      /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

      /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

      /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

      /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
      rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response2:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S4>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S4>:35' */
      /* '<S4>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
      /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
      /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

      /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

      /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

      /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
      rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response3:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S5>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S5>:35' */
      /* '<S5>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
      /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
      /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

      /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

      /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

      /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
      rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response4:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S6>:35' */
      /* '<S6>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
      /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
      /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

      /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

      /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

      /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
      rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response5:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S7>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S7>:35' */
      /* '<S7>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
      /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
      /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

      /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

      /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

      /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

      /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

      /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
      rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
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
    /* '<S1>:53:10' ElectricalID_output.thetaOffset = ActualValues.theta_el; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
      rtElectricalID_6ph_codegen_U->ActualValues.theta_el;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_on:
    /* Merge: '<S1>/ Merge ' */
    /* Exit 'alignRotor_d_on': '<S1>:3' */
    /* '<S1>:3:14' ElectricalID_output = ResetDutyCycle(ElectricalID_output); */
    /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
    /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

    /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

    /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

    /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

    /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

    /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_findDutyCycle:
    /* Inport: '<Root>/ActualValues' */
    /* Exit 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:30' ref_amplitude = single(DutyCycle*ActualValues.V_DC); */
    rtElectricalID_6ph_codegen_DW->ref_amplitude =
      rtElectricalID_6ph_codegen_DW->DutyCycle *
      rtElectricalID_6ph_codegen_U->ActualValues.V_DC;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:789:31' ElectricalID_output.PWM_Switch_0 = single(0); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_measure_induced_voltage:
    /* Exit 'measure_induced_voltage': '<S1>:405' */
    /* '<S1>:405:14' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;

    /* '<S1>:405:15' ElectricalID_output.psi_pm = ElectricalID_fft_in.psi_pm_amplitude; */
    /* '<S1>:405:16' ElectricalID_output.psi_pm_angle = ElectricalID_fft_in.psi_pm_angle; */
    for (i = 0; i < 5; i++) {
      /* Merge: '<S1>/ Merge ' */
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm[i] =
        BusConversion_InsertedFor_Elect->psi_pm_amplitude[i];
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm_angle[i] =
        BusConversion_InsertedFor_Elect->psi_pm_angle[i];
    }

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:405:17' ElectricalID_output.PMSM_parameters.Psi_PM_Vs = ElectricalID_output.psi_pm(1); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
      = rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm[0];

    /* '<S1>:405:18' ElectricalID_output.enable_TriState = boolean([0 0 0]); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
      false;

    /* '<S1>:405:19' ElectricalID_output.enable_TriState_set_2 = boolean([0 0 0]); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[0] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[2] =
      false;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_measure_psiPM:
    /* Exit 'measure_psiPM': '<S1>:1106' */
    /* '<S1>:1106:20' counter = uint32(1); */
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
static void ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;
  uint16_T n_iters_f;
  boolean_T updateJ_m;

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
    exit_internal_ElectricalID(BusConversion_InsertedFor_Elect,
      rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
      rtElectricalID_6ph_codegen_DW);
    rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:902' */
    /* wait for activation of */
    /* ElectricalID */
    /* donothing */
  } else {
    switch (rtElectricalID_6ph_codegen_DW->is_ElectricalID) {
     case IN_Subchart_Step_Response:
      /* During 'Subchart_Step_Response': '<S1>:994' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S2>:40' */
        /* '<S2>:61:1' sf_internal_predicateOutput = counter == one_sec_transition_counter; */
        if (rtElectricalID_6ph_codegen_DW->counter_n ==
            rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k) {
          /* Transition: '<S2>:61' */
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_p = 2U;
        } else {
          /* '<S2>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_n + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_n + 1U <
              rtElectricalID_6ph_codegen_DW->counter_n) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_n =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S2>:35' */
        /* '<S2>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_n == 1026U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S2>:32' */
        /* Exit 'stepResponse': '<S2>:35' */
        /* '<S2>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S2>:40' */
        rtElectricalID_6ph_codegen_DW->e_h4 = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[3] = 0.0F;
        n_iters_f = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_c = 0.01F;
        updateJ_m = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_m[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_o[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S2>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_n = 1U;

        /* '<S2>:40:4' LM_algorithm; */
        LM_algorithm(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                     &rtElectricalID_6ph_codegen_DW->R_est_c,
                     &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_m,
                     &rtElectricalID_6ph_codegen_DW->lambda_c,
                     &rtElectricalID_6ph_codegen_DW->e_h4, &n_iters_f,
                     rtElectricalID_6ph_codegen_DW->H_bn,
                     rtElectricalID_6ph_codegen_DW->i_est_n,
                     rtElectricalID_6ph_codegen_DW);

        /* '<S2>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S2>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchart_St_MeasureStepRespon_n
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.d,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.d,
           rtElectricalID_6ph_codegen_DW);

        /* '<S2>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_n + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_n + 1U <
            rtElectricalID_6ph_codegen_DW->counter_n) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_n =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_p;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_p = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1003' */
        /* '<S1>:1003:1' ElectricalID_output.inductances_6ph.d=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1003:2' ElectricalID_output.resistances_6ph.d=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S2>:35' */
          /* '<S2>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response1;
        rtElectricalID_6ph_codegen_DW->counter_o = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_e[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_a[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_bs = 1U;
        rtElectricalID_6ph_codegen_DW->V0_nx = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response1' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S3>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S3>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S3>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 133U;

        /* '<S3>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[2] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S3>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_l[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S3>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response1' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response1:
      /* During 'Subchart_Step_Response1': '<S1>:1001' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S3>:40' */
        /* '<S3>:61:1' sf_internal_predicateOutput = counter == one_sec_transition_counter; */
        if (rtElectricalID_6ph_codegen_DW->counter_o ==
            rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k) {
          /* Transition: '<S3>:61' */
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_ji = 2U;
        } else {
          /* '<S3>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_o + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_o + 1U <
              rtElectricalID_6ph_codegen_DW->counter_o) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_o =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S3>:35' */
        /* '<S3>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_o == 1026U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S3>:32' */
        /* Exit 'stepResponse': '<S3>:35' */
        /* '<S3>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S3>:40' */
        rtElectricalID_6ph_codegen_DW->e_h4 = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[3] = 0.0F;
        n_iters_f = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_c = 0.01F;
        updateJ_m = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_o[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_h[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S3>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_o = 1U;

        /* '<S3>:40:4' LM_algorithm; */
        LM_algorithm_m(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_m,
                       &rtElectricalID_6ph_codegen_DW->lambda_c,
                       &rtElectricalID_6ph_codegen_DW->e_h4, &n_iters_f,
                       rtElectricalID_6ph_codegen_DW->H_bn,
                       rtElectricalID_6ph_codegen_DW->i_est_n,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S3>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S3>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchart__b_MeasureStepRespon_g
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.x,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.x,
           rtElectricalID_6ph_codegen_DW);

        /* '<S3>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_o + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_o + 1U <
            rtElectricalID_6ph_codegen_DW->counter_o) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_o =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_ji;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_ji = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1018' */
        /* '<S1>:1018:1' ElectricalID_output.inductances_6ph.x=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.x =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1018:2' ElectricalID_output.resistances_6ph.x=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.x =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S3>:35' */
          /* '<S3>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response2;
        rtElectricalID_6ph_codegen_DW->counter_f = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_gw[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_n[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_p = 1U;
        rtElectricalID_6ph_codegen_DW->V0_n = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response2' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S4>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S4>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S4>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 134U;

        /* '<S4>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[3] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S4>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_m[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S4>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response2' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response2:
      /* During 'Subchart_Step_Response2': '<S1>:1009' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S4>:40' */
        /* '<S4>:61:1' sf_internal_predicateOutput = counter == one_sec_transition_counter; */
        if (rtElectricalID_6ph_codegen_DW->counter_f ==
            rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k) {
          /* Transition: '<S4>:61' */
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_a = 2U;
        } else {
          /* '<S4>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_f + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_f + 1U <
              rtElectricalID_6ph_codegen_DW->counter_f) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_f =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S4>:35' */
        /* '<S4>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_f == 1026U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S4>:32' */
        /* Exit 'stepResponse': '<S4>:35' */
        /* '<S4>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S4>:40' */
        rtElectricalID_6ph_codegen_DW->e_h4 = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[3] = 0.0F;
        n_iters_f = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_c = 0.01F;
        updateJ_m = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_cu[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S4>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_f = 1U;

        /* '<S4>:40:4' LM_algorithm; */
        LM_algorithm_j(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_m,
                       &rtElectricalID_6ph_codegen_DW->lambda_c,
                       &rtElectricalID_6ph_codegen_DW->e_h4, &n_iters_f,
                       rtElectricalID_6ph_codegen_DW->H_bn,
                       rtElectricalID_6ph_codegen_DW->i_est_n,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S4>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S4>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchart_bt_MeasureStepRespon_p
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.y,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.y,
           rtElectricalID_6ph_codegen_DW);

        /* '<S4>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_f + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_f + 1U <
            rtElectricalID_6ph_codegen_DW->counter_f) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_f =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_a;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_a = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1019' */
        /* '<S1>:1019:1' ElectricalID_output.inductances_6ph.y=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.y =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1019:2' ElectricalID_output.resistances_6ph.y=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.y =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S4>:35' */
          /* '<S4>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response3;
        rtElectricalID_6ph_codegen_DW->counter_g = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_j[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_i[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_k = 1U;
        rtElectricalID_6ph_codegen_DW->V0_k = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response3' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S5>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S5>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S5>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 135U;

        /* '<S5>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[4] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S5>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_a[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S5>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response3' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response3:
      /* During 'Subchart_Step_Response3': '<S1>:1013' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S5>:40' */
        /* '<S5>:61:1' sf_internal_predicateOutput = counter == one_sec_transition_counter; */
        if (rtElectricalID_6ph_codegen_DW->counter_g ==
            rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k) {
          /* Transition: '<S5>:61' */
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_b5 = 2U;
        } else {
          /* '<S5>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_g + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_g + 1U <
              rtElectricalID_6ph_codegen_DW->counter_g) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_g =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S5>:35' */
        /* '<S5>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_g == 1026U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S5>:32' */
        /* Exit 'stepResponse': '<S5>:35' */
        /* '<S5>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S5>:40' */
        rtElectricalID_6ph_codegen_DW->e_h4 = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[3] = 0.0F;
        n_iters_f = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_c = 0.01F;
        updateJ_m = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_h[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_p[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S5>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_g = 1U;

        /* '<S5>:40:4' LM_algorithm; */
        LM_algorithm_a(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_m,
                       &rtElectricalID_6ph_codegen_DW->lambda_c,
                       &rtElectricalID_6ph_codegen_DW->e_h4, &n_iters_f,
                       rtElectricalID_6ph_codegen_DW->H_bn,
                       rtElectricalID_6ph_codegen_DW->i_est_n,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S5>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S5>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchar_btw_MeasureStepRespon_k
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.z1,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z1,
           rtElectricalID_6ph_codegen_DW);

        /* '<S5>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_g + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_g + 1U <
            rtElectricalID_6ph_codegen_DW->counter_g) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_g =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_b5;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_b5 = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1020' */
        /* '<S1>:1020:1' ElectricalID_output.inductances_6ph.z1=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z1 =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1020:2' ElectricalID_output.resistances_6ph.z1=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z1 =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S5>:35' */
          /* '<S5>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response4;
        rtElectricalID_6ph_codegen_DW->counter_j = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_g[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_j[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_b = 1U;
        rtElectricalID_6ph_codegen_DW->V0_g = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response4' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S6>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S6>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S6>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 136U;

        /* '<S6>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[5] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S6>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_i[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S6>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response4' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response4:
      /* During 'Subchart_Step_Response4': '<S1>:1017' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S6>:40' */
        /* '<S6>:61:1' sf_internal_predicateOutput = counter == one_sec_transition_counter; */
        if (rtElectricalID_6ph_codegen_DW->counter_j ==
            rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k) {
          /* Transition: '<S6>:61' */
          /* Exit 'Levenberg_Marquardt': '<S6>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_d = 2U;
        } else {
          /* '<S6>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_j + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_j + 1U <
              rtElectricalID_6ph_codegen_DW->counter_j) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_j =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S6>:35' */
        /* '<S6>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_j == 1026U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S6>:32' */
        /* Exit 'stepResponse': '<S6>:35' */
        /* '<S6>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S6>:40' */
        rtElectricalID_6ph_codegen_DW->e_h4 = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[3] = 0.0F;
        n_iters_f = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_c = 0.01F;
        updateJ_m = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_i[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_c[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S6>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_j = 1U;

        /* '<S6>:40:4' LM_algorithm; */
        LM_algorithm_ak(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                        &rtElectricalID_6ph_codegen_DW->R_est_c,
                        &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_m,
                        &rtElectricalID_6ph_codegen_DW->lambda_c,
                        &rtElectricalID_6ph_codegen_DW->e_h4, &n_iters_f,
                        rtElectricalID_6ph_codegen_DW->H_bn,
                        rtElectricalID_6ph_codegen_DW->i_est_n,
                        rtElectricalID_6ph_codegen_DW);

        /* '<S6>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S6>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subcha_btw5_MeasureStepRespon_g
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.z2,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z2,
           rtElectricalID_6ph_codegen_DW);

        /* '<S6>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_j + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_j + 1U <
            rtElectricalID_6ph_codegen_DW->counter_j) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_j =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_d;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_d = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1027' */
        /* '<S1>:1027:1' ElectricalID_output.inductances_6ph.z2=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z2 =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1027:2' ElectricalID_output.resistances_6ph.z2=R_est */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z2 =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S6>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Merge: '<S1>/ Merge ' */
          /* Exit 'stepResponse': '<S6>:35' */
          /* '<S6>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;

          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;

          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
          rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_gatherResults;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'gatherResults': '<S1>:1028' */
        /* '<S1>:1028:3' ElectricalID_FOC_output.activeState = uint16(148); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 148U;

        /* Inport: '<Root>/ElectricalIDConfig' */
        /* '<S1>:1028:4' if(ElectricalIDConfig.identLq ==  0) */
        if (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
          /* Merge: '<S1>/ Merge ' */
          /* '<S1>:1028:5' ElectricalID_output.inductances_6ph.q=ElectricalID_output.inductances_6ph.d; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q =
            rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d;

          /* '<S1>:1028:6' ElectricalID_output.resistances_6ph.q=ElectricalID_output.resistances_6ph.d; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q =
            rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d;
        }

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:1028:8' ElectricalID_output.PMSM_parameters.Ld_Henry = ElectricalID_output.inductances_6ph.d; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry
          = rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d;

        /* '<S1>:1028:9' ElectricalID_output.PMSM_parameters.Lq_Henry = ElectricalID_output.inductances_6ph.q; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
          = rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q;

        /* '<S1>:1028:10' ElectricalID_output.PMSM_parameters.R_ph_Ohm = (ElectricalID_output.resistances_6ph.d + .... */
        /* '<S1>:1028:11'     ElectricalID_output.resistances_6ph.q + ElectricalID_output.resistances_6ph.x + .... */
        /* '<S1>:1028:12'     ElectricalID_output.resistances_6ph.y)/single(4); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm
          =
          (((rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d
             + rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q)
            + rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.x)
           + rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.y)
          / 4.0F;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* . */
        /* '<S1>:1028:13' ElectricalID_FOC_output = ControllerParameter(ElectricalID_FOC_output,... */
        /* '<S1>:1028:14'     bandwidthCurrentControl,ElectricalID_output.PMSM_parameters,dampingFactor,psiOverJ); */
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

     case IN_Subchart_Step_Response5:
      /* During 'Subchart_Step_Response5': '<S1>:1025' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S7>:40' */
        /* '<S7>:61:1' sf_internal_predicateOutput = counter == one_sec_transition_counter; */
        if (rtElectricalID_6ph_codegen_DW->counter_i ==
            rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k) {
          /* Transition: '<S7>:61' */
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_m = 2U;
        } else {
          /* '<S7>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_i + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_i + 1U <
              rtElectricalID_6ph_codegen_DW->counter_i) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_i =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S7>:35' */
        /* '<S7>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_i == 1026U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S7>:32' */
        /* Exit 'stepResponse': '<S7>:35' */
        /* '<S7>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S7>:40' */
        rtElectricalID_6ph_codegen_DW->e_h4 = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_bn[3] = 0.0F;
        n_iters_f = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_c = 0.01F;
        updateJ_m = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J[0], 0, sizeof(real32_T) << 12U);

        /* '<S7>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_i = 1U;

        /* '<S7>:40:4' LM_algorithm; */
        LM_algorithm_i(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_m,
                       &rtElectricalID_6ph_codegen_DW->lambda_c,
                       &rtElectricalID_6ph_codegen_DW->e_h4, &n_iters_f,
                       rtElectricalID_6ph_codegen_DW->H_bn,
                       rtElectricalID_6ph_codegen_DW->i_est_n,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S7>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S7>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subch_btw5m_MeasureStepRespon_e
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.q,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.q,
           rtElectricalID_6ph_codegen_DW);

        /* '<S7>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_i + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_i + 1U <
            rtElectricalID_6ph_codegen_DW->counter_i) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_i =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_m;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_m = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1030' */
        /* '<S1>:1030:1' ElectricalID_output.inductances_6ph.q=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q =
          rtElectricalID_6ph_codegen_DW->L_est_mb;

        /* '<S1>:1030:2' ElectricalID_output.resistances_6ph.q=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S7>:35' */
          /* '<S7>:35:11' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response;
        rtElectricalID_6ph_codegen_DW->counter_n = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_k[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_a4[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_c = 1U;
        rtElectricalID_6ph_codegen_DW->V0_a = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S2>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S2>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S2>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 131U;

        /* '<S2>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[0] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S2>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_p[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S2>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* set DutyCycles */
      }
      break;

     case IN_alignRotor_d_off:
      /* During 'alignRotor_d_off': '<S1>:53' */
      /* '<S1>:411:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Merge: '<S1>/ Merge ' incorporates:
         *  Inport: '<Root>/ActualValues'
         */
        /* Transition: '<S1>:411' */
        /* Exit 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:10' ElectricalID_output.thetaOffset = ActualValues.theta_el; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
          rtElectricalID_6ph_codegen_U->ActualValues.theta_el;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitLock;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'waitLock': '<S1>:1021' */
        /* '<S1>:1021:3' ElectricalID_FOC_output.activeState = uint16(130); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 130U;
      } else {
        /* '<S1>:53:8' counter  = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }
      break;

     case IN_alignRotor_d_on:
      /* During 'alignRotor_d_on': '<S1>:3' */
      /* '<S1>:164:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:164' */
        /* Exit 'alignRotor_d_on': '<S1>:3' */
        /* '<S1>:3:14' ElectricalID_output = ResetDutyCycle(ElectricalID_output); */
        /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
        /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
        /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;

        /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;

        /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 = 0.0F;

        /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 = 0.0F;

        /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 = 0.0F;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_alignRotor_d_off;

        /* Entry 'alignRotor_d_off': '<S1>:53' */
        /* '<S1>:53:4' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:53:5' ElectricalID_output.PWM_Switch_0 = single(0); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:53:6' ElectricalID_FOC_output.activeState = uint16(121); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 121U;
      } else {
        /* '<S1>:3:7' DutyCycle_filt = single(single(counter)*GlobalConfig.sampleTimeISR*2); */
        /* '<S1>:3:8' if(DutyCycle_filt > 1) */
        /* '<S1>:3:11' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,inv_VSD*[ref_amplitude;0;0;0;0;0]); */
        rtElectricalID_6ph_codegen_DW->setp_dq[0] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;
        rtElectricalID_6ph_codegen_DW->setp_dq[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->setp_dq[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->setp_dq[3] = 0.0F;
        rtElectricalID_6ph_codegen_DW->setp_dq[4] = 0.0F;
        rtElectricalID_6ph_codegen_DW->setp_dq[5] = 0.0F;
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* Merge: '<S1>/ Merge ' incorporates:
         *  Inport: '<Root>/ActualValues'
         */
        SetpVectorToDutyCycle6ph
          (&rtElectricalID_6ph_codegen_DW->ElectricalID_output,
           rtElectricalID_6ph_codegen_U->ActualValues.V_DC,
           rtElectricalID_6ph_codegen_DW->setp_abc);

        /* set DutyCycles */
        /* '<S1>:3:12' counter  = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }
      break;

     case IN_endState:
      /* During 'endState': '<S1>:356' */
      /* '<S1>:425:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
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
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }
      break;

     case IN_findDutyCycle:
      findDutyCycle(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
                    rtElectricalID_6ph_codegen_DW);
      break;

     case IN_gatherResults:
      gatherResults(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
                    rtElectricalID_6ph_codegen_DW);
      break;

     case IN_measure_induced_voltage:
      /* During 'measure_induced_voltage': '<S1>:405' */
      /* '<S1>:406:1' sf_internal_predicateOutput = ElectricalID_fft_in.finished_flag; */
      if (BusConversion_InsertedFor_Elect->finished_flag) {
        /* Transition: '<S1>:406' */
        /* Exit 'measure_induced_voltage': '<S1>:405' */
        /* '<S1>:405:14' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* '<S1>:405:15' ElectricalID_output.psi_pm = ElectricalID_fft_in.psi_pm_amplitude; */
        /* '<S1>:405:16' ElectricalID_output.psi_pm_angle = ElectricalID_fft_in.psi_pm_angle; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 5;
             rtElectricalID_6ph_codegen_DW->i++) {
          /* Merge: '<S1>/ Merge ' */
          rtElectricalID_6ph_codegen_DW->
            ElectricalID_output.psi_pm[rtElectricalID_6ph_codegen_DW->i] =
            BusConversion_InsertedFor_Elect->
            psi_pm_amplitude[rtElectricalID_6ph_codegen_DW->i];
          rtElectricalID_6ph_codegen_DW->
            ElectricalID_output.psi_pm_angle[rtElectricalID_6ph_codegen_DW->i] =
            BusConversion_InsertedFor_Elect->
            psi_pm_angle[rtElectricalID_6ph_codegen_DW->i];
        }

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:405:17' ElectricalID_output.PMSM_parameters.Psi_PM_Vs = ElectricalID_output.psi_pm(1); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
          = rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm[0];

        /* '<S1>:405:18' ElectricalID_output.enable_TriState = boolean([0 0 0]); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] =
          false;
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
          false;
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
          false;

        /* '<S1>:405:19' ElectricalID_output.enable_TriState_set_2 = boolean([0 0 0]); */
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[0] = false;
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[1] = false;
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[2] = false;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitFree;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'waitFree': '<S1>:1112' */
        /* '<S1>:1112:3' ElectricalID_FOC_output.activeState = uint16(160); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 160U;

        /* '<S1>:405:7' if(counter<=10000) */
      } else if (rtElectricalID_6ph_codegen_DW->counter <= 10000U) {
        /* '<S1>:405:8' voltage_meas_array(counter-1) = ActualValues.v_abc_6ph.a1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter - 1U >
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
        }

        /* Outport: '<Root>/voltage_meas_array' incorporates:
         *  Inport: '<Root>/ActualValues'
         */
        rtElectricalID_6ph_codegen_Y->voltage_meas_array[(int32_T)
          rtElectricalID_6ph_codegen_DW->exitPortIndex - 1] =
          rtElectricalID_6ph_codegen_U->ActualValues.v_abc_6ph.a1;

        /* '<S1>:405:9' counter = counter + 1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      } else {
        /* Outport: '<Root>/finished_voltage_measurement' */
        /* '<S1>:405:10' else */
        /* '<S1>:405:11' finished_voltage_measurement = true; */
        rtElectricalID_6ph_codegen_Y->finished_voltage_measurement = true;
      }
      break;

     case IN_measure_psiPM:
      measure_psiPM(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
                    rtElectricalID_6ph_codegen_DW);
      break;

     case IN_rotorInertiaEstimation:
      /* During 'rotorInertiaEstimation': '<S1>:337' */
      /* '<S1>:357:1' sf_internal_predicateOutput = counter == (wait_count+513); */
      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->wait_count + /*MW:OvSatOk*/ 513U;
      if (rtElectricalID_6ph_codegen_DW->wait_count + 513U <
          rtElectricalID_6ph_codegen_DW->wait_count) {
        rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
      }

      if (rtElectricalID_6ph_codegen_DW->counter ==
          rtElectricalID_6ph_codegen_DW->exitPortIndex) {
        /* Transition: '<S1>:357' */
        /* Exit 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:18' goertzel; */
        goertzel(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_endState;

        /* Entry 'endState': '<S1>:356' */
        /* '<S1>:356:4' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:356:5' ElectricalID_FOC_output.activeState = uint16(163); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 163U;

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
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->wait_count + /*MW:OvSatOk*/ 501U;
        if (rtElectricalID_6ph_codegen_DW->wait_count + 501U <
            rtElectricalID_6ph_codegen_DW->wait_count) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        if ((rtElectricalID_6ph_codegen_DW->counter >
             rtElectricalID_6ph_codegen_DW->wait_count) &&
            (rtElectricalID_6ph_codegen_DW->counter <
             rtElectricalID_6ph_codegen_DW->exitPortIndex)) {
          /* '<S1>:337:13' measArray1(counter-wait_count) = ActualValues.i_dq.q; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
            rtElectricalID_6ph_codegen_DW->wait_count;
          if (rtElectricalID_6ph_codegen_DW->exitPortIndex >
              rtElectricalID_6ph_codegen_DW->counter) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_6ph_codegen_DW->measArray1[(int32_T)
            rtElectricalID_6ph_codegen_DW->exitPortIndex - 1] =
            rtElectricalID_6ph_codegen_U->ActualValues.i_dq.q;

          /* '<S1>:337:14' i_est(counter-wait_count) = ActualValues.omega_m; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
            rtElectricalID_6ph_codegen_DW->wait_count;
          if (rtElectricalID_6ph_codegen_DW->exitPortIndex >
              rtElectricalID_6ph_codegen_DW->counter) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
          }

          /* Inport: '<Root>/ActualValues' */
          rtElectricalID_6ph_codegen_DW->i_est[(int32_T)
            rtElectricalID_6ph_codegen_DW->exitPortIndex - 1] =
            rtElectricalID_6ph_codegen_U->ActualValues.omega_m;
        }

        /* '<S1>:337:16' counter = counter + 1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }
      break;

     case IN_stop:
      /* During 'stop': '<S1>:361' */
      /* '<S1>:362:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
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

        /* '<S1>:337:7' ElectricalID_FOC_output.activeState = uint16(162); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 162U;

        /* '<S1>:337:8' wait_count = uint32(3/GlobalConfig.sampleTimeISR); */
        rtElectricalID_6ph_codegen_DW->e_h4 = roundf(3.0F /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 4.2949673E+9F) {
          if (rtElectricalID_6ph_codegen_DW->e_h4 >= 0.0F) {
            rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)
              rtElectricalID_6ph_codegen_DW->e_h4;
          } else {
            rtElectricalID_6ph_codegen_DW->wait_count = 0U;
          }
        } else {
          rtElectricalID_6ph_codegen_DW->wait_count = MAX_uint32_T;
        }
      } else {
        /* '<S1>:361:6' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }
      break;

     case IN_waitFree:
      /* During 'waitFree': '<S1>:1112' */
      /* '<S1>:1113:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:1113' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_stop;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stop': '<S1>:361' */
        /* state 10.1 */
        /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(161); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 161U;

        /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

        /* '<S1>:361:5' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
          true;
      }
      break;

     case IN_waitLock:
      /* Inport: '<Root>/ElectricalIDConfig' */
      /* During 'waitLock': '<S1>:1021' */
      /* '<S1>:1078:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1 && ElectricalIDConfig.identLq==1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT &&
          rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
        /* Transition: '<S1>:1078' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response5;
        rtElectricalID_6ph_codegen_DW->counter_i = 1U;
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
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S7>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S7>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S7>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 132U;

        /* '<S7>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[1] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S7>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_n[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S7>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response5' */
        /* set DutyCycles */

        /* '<S1>:1079:1' sf_internal_predicateOutput = ElectricalIDConfig.identLq== 0; */
      } else if (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
        /* Transition: '<S1>:1079' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response;
        rtElectricalID_6ph_codegen_DW->counter_n = 1U;
        memset(&rtElectricalID_6ph_codegen_DW->Vstep_k[0], 0, 205U * sizeof
               (real32_T));
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_a4[0], 0,
               sizeof(real32_T) << 10U);
        rtElectricalID_6ph_codegen_DW->z_c = 1U;
        rtElectricalID_6ph_codegen_DW->V0_a = 0.0F;

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S2>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
          IN_stepResponse;

        /* Entry 'stepResponse': '<S2>:35' */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_dq
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
        }

        /* '<S2>:35:3' activeState = uint16(130)+index; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 131U;

        /* '<S2>:35:4' setp_dq(index)=ref_amplitude; */
        rtElectricalID_6ph_codegen_DW->setp_dq[0] =
          rtElectricalID_6ph_codegen_DW->ref_amplitude;

        /* setpoints in dq */
        /* '<S2>:35:5' setp_abc = inv_VSD*setp_dq; */
        for (rtElectricalID_6ph_codegen_DW->i = 0;
             rtElectricalID_6ph_codegen_DW->i < 6;
             rtElectricalID_6ph_codegen_DW->i++) {
          rtElectricalID_6ph_codegen_DW->setp_abc
            [rtElectricalID_6ph_codegen_DW->i] = 0.0F;
          for (i = 0; i < 6; i++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_p[6 * i +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->setp_dq[i];
          }
        }

        /* setpoints in abc */
        /* '<S2>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_c =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_h4 =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_c + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_h4 < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_h4 > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_h4;
        }

        /* set DutyCycles */
      }
      break;

     case IN_waitSetRPM:
      /* Inport: '<Root>/ActualValues' incorporates:
       *  Merge: '<S1>/ Merge '
       *  Outport: '<Root>/ElectricalID_FOC_output'
       */
      /* During 'waitSetRPM': '<S1>:1047' */
      /* '<S1>:1048:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1&&ActualValues.omega_m>(ElectricalID_output.set_rpm_val*single(0.9*2*pi/60))&&ActualValues.omega_m<(ElectricalID_output.set_rpm_val*single(1.1*2*pi/60)); */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT &&
          (rtElectricalID_6ph_codegen_U->ActualValues.omega_m >
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.set_rpm_val *
           0.0942477807F) && (rtElectricalID_6ph_codegen_U->ActualValues.omega_m
           < rtElectricalID_6ph_codegen_DW->ElectricalID_output.set_rpm_val *
                              0.115191728F)) {
        /* Transition: '<S1>:1048' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_measure_induced_voltage;

        /* Entry 'measure_induced_voltage': '<S1>:405' */
        /* '<S1>:405:4' ElectricalID_FOC_output.activeState = uint16(156); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 156U;

        /* '<S1>:405:5' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;
      }
      break;

     default:
      /* During 'waitState': '<S1>:428' */
      /* '<S1>:905:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
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
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter + 1U <
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }
      break;
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
   *  Inport: '<Root>/ElectricalID_fft_in'
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
    ElectricalID(&rtElectricalID_6ph_codegen_U->ElectricalID_fft_in,
                 rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
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
    /* Transition: '<S1>:1037' */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_findDutyCycle;

    /* Entry 'findDutyCycle': '<S1>:789' */
    /* '<S1>:789:4' ElectricalID_FOC_output.activeState = uint16(110); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 110U;

    /* '<S1>:789:5' if(ElectricalIDConfig.dutyCyc > 0.0) */
    if (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.dutyCyc > 0.0F) {
      /* Checks if a manual value for the DutyCycle was set */
      /* '<S1>:789:6' DutyCycle = single(ElectricalIDConfig.dutyCyc); */
      rtElectricalID_6ph_codegen_DW->DutyCycle =
        rtElectricalID_6ph_codegen_U->ElectricalIDConfig.dutyCyc;

      /* '<S1>:789:7' DC_valid = boolean(1); */
      rtElectricalID_6ph_codegen_DW->DC_valid = true;
    } else {
      /* '<S1>:789:8' else */
      /* '<S1>:789:9' DutyCycle = single(0.01); */
      rtElectricalID_6ph_codegen_DW->DutyCycle = 0.01F;

      /* Starting DC */
      /* '<S1>:789:10' DC_valid = boolean(0); */
      rtElectricalID_6ph_codegen_DW->DC_valid = false;
    }

    /* '<S1>:789:12' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;

    /* starts with 1, so that the DutyCylce_mod function wont be entered */
    /* during the fist cycle through the state */

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
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U =
    (ExtU_ElectricalID_6ph_codegen_t *) rtElectricalID_6ph_codegen_M->inputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtElectricalID_6ph_codegen_DW, 0,
                sizeof(DW_ElectricalID_6ph_codegen_t));

  /* external inputs */
  (void)memset(rtElectricalID_6ph_codegen_U, 0, sizeof
               (ExtU_ElectricalID_6ph_codegen_t));

  /* external outputs */
  (void)memset(rtElectricalID_6ph_codegen_Y, 0, sizeof
               (ExtY_ElectricalID_6ph_codegen_t));

  {
    int32_T i;
    static const real32_T b[36] = { 1.0F, -0.5F, -0.5F, 0.866025388F,
      -0.866025388F, -2.22044605E-16F, 4.0292992E-16F, 0.866025388F,
      -0.866025388F, 0.5F, 0.5F, -1.0F, 1.0F, -0.5F, -0.5F, -0.866025388F,
      0.866025388F, -8.11506533E-16F, -1.47195872E-15F, -0.866025388F,
      0.866025388F, 0.5F, 0.5F, -1.0F, 1.0F, 1.0F, 1.0F, 3.03318581E-16F,
      -6.53560669E-16F, 1.03355119E-15F, -5.17937724E-16F, -1.83585349E-15F,
      -1.27277098E-15F, 1.0F, 1.0F, 1.0F };

    /* SystemInitialize for Chart: '<Root>/ElectricalID_6ph_codegen' */
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_n[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_sOrida1dLJHFhz3jwws1fnH_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_i = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->Vstep[0], 0, 205U * sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array[0], 0, sizeof
           (real32_T) << 10U);
    rtElectricalID_6ph_codegen_DW->z = 1U;
    rtElectricalID_6ph_codegen_DW->V0 = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d_n[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_p[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_sMWbr9x0gq9qn9qDdVLZeFF_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_n = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->Vstep_k[0], 0, 205U * sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_a4[0], 0, sizeof
           (real32_T) << 10U);
    rtElectricalID_6ph_codegen_DW->z_c = 1U;
    rtElectricalID_6ph_codegen_DW->V0_a = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d_m[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_o[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_l[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_suUPVh77ZXqqMHR03zyk1ZB_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_o = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->Vstep_e[0], 0, 205U * sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_a[0], 0, sizeof
           (real32_T) << 10U);
    rtElectricalID_6ph_codegen_DW->z_bs = 1U;
    rtElectricalID_6ph_codegen_DW->V0_nx = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d_o[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_h[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_m[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_sXsuRAan3TDX1V4pP05BViE_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_f = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->Vstep_gw[0], 0, 205U * sizeof
           (real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_n[0], 0, sizeof
           (real32_T) << 10U);
    rtElectricalID_6ph_codegen_DW->z_p = 1U;
    rtElectricalID_6ph_codegen_DW->V0_n = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d_l[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_cu[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_a[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_siDrVKQJrmgth2tO4iYKAXD_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_g = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->Vstep_j[0], 0, 205U * sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_i[0], 0, sizeof
           (real32_T) << 10U);
    rtElectricalID_6ph_codegen_DW->z_k = 1U;
    rtElectricalID_6ph_codegen_DW->V0_k = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d_h[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_p[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_i[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_swiDrWmrnFiNemiFZhejbKE_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_j = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->Vstep_g[0], 0, 205U * sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_j[0], 0, sizeof
           (real32_T) << 10U);
    rtElectricalID_6ph_codegen_DW->z_b = 1U;
    rtElectricalID_6ph_codegen_DW->V0_g = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d_i[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_c[0], 0, sizeof(real32_T) << 12U);
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->is_active_c3_ElectricalID_6ph_c = 0U;
    rtElectricalID_6ph_codegen_DW->is_c3_ElectricalID_6ph_codegen =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter = 0U;
    rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl = 0.0F;
    rtElectricalID_6ph_codegen_DW->dampingFactor = 0.0F;
    rtElectricalID_6ph_codegen_DW->psiOverJ = 0.0F;
    rtElectricalID_6ph_codegen_DW->Kp_iq_loc = 0.0F;
    rtElectricalID_6ph_codegen_DW->ia_sum = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->d[0], 0, sizeof(real32_T) << 11U);
    rtElectricalID_6ph_codegen_DW->DutyCycle = 0.0F;
    rtElectricalID_6ph_codegen_DW->wait_count = 0U;
    rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k = 0U;
    rtElectricalID_6ph_codegen_DW->ref_amplitude = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->measArray1[0], 0, sizeof(real32_T) <<
           10U);
    memset(&rtElectricalID_6ph_codegen_DW->i_est[0], 0, sizeof(real32_T) << 11U);
    rtElectricalID_6ph_codegen_DW->R_est_c = 0.0F;
    rtElectricalID_6ph_codegen_DW->L_est_mb = 0.0F;
    rtElectricalID_6ph_codegen_DW->DC_valid = false;
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD[0], &b[0], 36U * sizeof
           (real32_T));

    /* SystemInitialize for Outport: '<Root>/enteredElectricalID' incorporates:
     *  Chart: '<Root>/ElectricalID_6ph_codegen'
     */
    rtElectricalID_6ph_codegen_Y->enteredElectricalID = false;

    /* SystemInitialize for Outport: '<Root>/finishedElectricalID' incorporates:
     *  Chart: '<Root>/ElectricalID_6ph_codegen'
     */
    rtElectricalID_6ph_codegen_Y->finishedElectricalID = false;

    /* SystemInitialize for Chart: '<Root>/ElectricalID_6ph_codegen' incorporates:
     *  Merge: '<S1>/ Merge '
     *  Outport: '<Root>/ElectricalID_FOC_output'
     */
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
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[0] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[2] =
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
    for (i = 0; i < 5; i++) {
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm[i] = 0.0F;
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm_angle[i] = 0.0F;
    }

    rtElectricalID_6ph_codegen_DW->ElectricalID_output.set_rpm_val = 0.0F;

    /* SystemInitialize for Outport: '<Root>/voltage_meas_array' incorporates:
     *  Chart: '<Root>/ElectricalID_6ph_codegen'
     */
    memset(&rtElectricalID_6ph_codegen_Y->voltage_meas_array[0], 0, 10000U *
           sizeof(real32_T));

    /* SystemInitialize for Outport: '<Root>/finished_voltage_measurement' incorporates:
     *  Chart: '<Root>/ElectricalID_6ph_codegen'
     */
    rtElectricalID_6ph_codegen_Y->finished_voltage_measurement = false;

    /* SystemInitialize for Chart: '<Root>/ElectricalID_6ph_codegen' */
    /* '<S1>:922:7' sineCounter = uint32(0); */
    rtElectricalID_6ph_codegen_DW->sineCounter = 0U;

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