/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.c
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 5.0
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Jun  1 16:23:36 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warnings (2), Error (0)
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
#define IN_extendedOffsetEstimation    ((uint8_T)9U)
#define IN_findDutyCycle               ((uint8_T)10U)
#define IN_gatherResults               ((uint8_T)11U)
#define IN_initSetpointsExtendedOffsetE ((uint8_T)12U)
#define IN_measure_induced_voltage     ((uint8_T)13U)
#define IN_measure_psiPM               ((uint8_T)14U)
#define IN_rotorInertiaEstimation      ((uint8_T)15U)
#define IN_stop                        ((uint8_T)16U)
#define IN_waitFree                    ((uint8_T)17U)
#define IN_waitLock                    ((uint8_T)18U)
#define IN_waitSetRPM                  ((uint8_T)19U)
#define IN_waitState                   ((uint8_T)20U)
#define loc_FFT_length_ms              (1000.0F)

/* Forward declaration for local functions */
static void initParams(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void reset_FOC_output(ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y);
static void Subchart_St_MeasureStepRespon_e(real32_T v_dq_d, real32_T i_dq_d,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm(const uz_ParaID_GlobalConfig_t *GlobalConfig, real32_T *
  R_est, real32_T *L_est, const uint16_T *n_iters_hn, boolean_T *updateJ_ok,
  real32_T *lambda_l, real32_T *e_d, real32_T H_iu[4], real32_T i_est_lb[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart__b_MeasureStepRespon_d(real32_T v_dq_x, real32_T i_dq_x,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_g(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_h, boolean_T
  *updateJ_j, real32_T *lambda_g, real32_T *e_b, real32_T H_iq[4], real32_T
  i_est_o[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart_bt_MeasureStepRespon_b(real32_T v_dq_y, real32_T i_dq_y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_c(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_o, boolean_T
  *updateJ_o1, real32_T *lambda_h, real32_T *e_ib, real32_T H_d[4], real32_T
  i_est_l[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchar_btw_MeasureStepRespon_n(real32_T v_dq_z1, real32_T i_dq_z1,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_o(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_l, boolean_T
  *updateJ_h, real32_T *lambda_j, real32_T *e_i, real32_T H_l[4], real32_T
  i_est_m[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subcha_btw5_MeasureStepRespon_k(real32_T v_dq_z2, real32_T i_dq_z2,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_f(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_f, boolean_T
  *updateJ_o, real32_T *lambda_n, real32_T *e_f, real32_T H_i[4], real32_T
  i_est_f[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subch_btw5m_MeasureStepRespon_m(real32_T v_dq_q, real32_T i_dq_q,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_h(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters, boolean_T *updateJ,
  real32_T *lambda, real32_T *e, real32_T H[4], real32_T i_est_g[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void SetpVectorToDutyCycle6ph(uz_ParaID_ElectricalID_output_t
  *ElectricalID_output_in, real32_T VDC, const real32_T SetpVector[6]);
static void enter_atomic_waitState(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void DutyCycle_mod(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void findDutyCycle(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static real32_T cutoff_frequency(real32_T Rp, real32_T Rs, real32_T C);
static real32_T correct_setpoint(real32_T setpoint_rpm, real32_T ratSpeed_rpm,
  real32_T polepairs, real32_T FFT_length_ms);
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
static void rotorInertiaEstimation(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void exit_internal_ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, const
  uz_ParaID_ElectricalID_offset_estimation_t *BusConversion_InsertedFor_Ele_b,
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U,
  ExtY_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_Y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, const
  uz_ParaID_ElectricalID_offset_estimation_t *BusConversion_InsertedFor_Ele_b,
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U,
  ExtY_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_Y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);

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

  /* Merge: '<S1>/ Merge ' */
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

  /* '<S1>:88:78' finished_voltage_measurement                            = false; */
  rtElectricalID_6ph_codegen_Y->finished_voltage_measurement = false;

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
  rtElectricalID_6ph_codegen_DW->L_est_m = 0.0F;

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
  /* '<S1>:920:18' ElectricalID_FOC_output.PI_subsystem = 0x0000; */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.PI_subsystem = 0U;
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchart_St_MeasureStepRespon_e(real32_T v_dq_d, real32_T i_dq_d,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponse': '<S2>:39' */
  /* '<S2>:39:2' fns = fieldnames(i_dq); */
  /* '<S2>:39:3' current = i_dq.(fns{index}); */
  /* '<S2>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S2>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_b <= 1024U) {
    /* '<S2>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_b > 1U) {
      /* '<S2>:39:7' current_meas_array(counter-1) = current; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_b - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_b - 1U >
          rtElectricalID_6ph_codegen_DW->counter_b) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_bf[k - 1] = i_dq_d;

      /* safe 1024 current values to 2D array */
      /* '<S2>:39:8' voltage_meas_array(counter-1) = voltage; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_b - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_b - 1U >
          rtElectricalID_6ph_codegen_DW->counter_b) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[k - 1] = v_dq_d;

      /* '<S2>:39:9' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_b -
          rtElectricalID_6ph_codegen_DW->counter_b / 5U * 5U == 0U) {
        uint32_T tmp;

        /* exec every 5th cycle */
        /* '<S2>:39:10' Vstep(z-1) = voltage; */
        /* safe Va */
        /* '<S2>:39:11' z = z + 1; */
        tmp = rtElectricalID_6ph_codegen_DW->z_b + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_b + 1U > 65535U) {
          tmp = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_b = (uint16_T)tmp;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_b == 1U) {
      uint32_T tmp;

      /* '<S2>:39:13' elseif(counter == 1) */
      /* '<S2>:39:14' Vstep(1) = voltage; */
      /* safe Va 1st cycle */
      /* '<S2>:39:15' z = z + 1; */
      tmp = rtElectricalID_6ph_codegen_DW->z_b + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_b + 1U > 65535U) {
        tmp = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_b = (uint16_T)tmp;
    }

    /* '<S2>:39:17' else */
    /* '<S2>:39:18' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_b == 1025U) {
    real32_T x;

    /* '<S2>:39:19' current_meas_array(counter-1) = current; */
    rtElectricalID_6ph_codegen_DW->current_meas_array_bf[1023] = i_dq_d;

    /* safe last current val */
    /* '<S2>:39:20' voltage_meas_array(counter-1) = voltage; */
    rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[1023] = v_dq_d;

    /* '<S2>:39:21' Vstep(z-1) = voltage; */
    /* '<S2>:39:22' V0 = mean(voltage_meas_array); */
    x = rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[0];
    for (k = 0; k < 1023; k++) {
      x += rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_n4 = x / 1024.0F;

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
  R_est, real32_T *L_est, const uint16_T *n_iters_hn, boolean_T *updateJ_ok,
  real32_T *lambda_l, real32_T *e_d, real32_T H_iu[4], real32_T i_est_lb[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b;
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
  b = *n_iters_hn;
  for (it = 0; it < b; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S2>:36:26' if updateJ == 1 */
    if (*updateJ_ok) {
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
        rtElectricalID_6ph_codegen_DW->J_i[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_n4) / (*R_est * *R_est) -
          (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n4 *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_i[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n4 *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S2>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_lb[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_n4 / *R_est);
        rtElectricalID_6ph_codegen_DW->d_e[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_bf[k] - i_est_lb[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S2>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_iu[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_iu[tmp] += rtElectricalID_6ph_codegen_DW->J_i[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_i[(i << 11) + i_0];
          }
        }
      }

      /* '<S2>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S2>:36:44' e = dot(d,d); */
        *e_d = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_d += rtElectricalID_6ph_codegen_DW->d_e[k] *
            rtElectricalID_6ph_codegen_DW->d_e[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S2>:36:49' H(1,1) = H(1,1) + lambda; */
    H_iu[0] += *lambda_l;

    /* '<S2>:36:50' H(2,2)=H(2,2)+lambda; */
    H_iu[3] += *lambda_l;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S2>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_i[k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_e[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_i[(k + 1024) % 1024 + 2048] *
        rtElectricalID_6ph_codegen_DW->d_e[k];
    }

    if (fabsf(H_iu[1]) > fabsf(H_iu[0])) {
      r = H_iu[0] / H_iu[1];
      t = 1.0F / (r * H_iu[3] - H_iu[2]);
      b_y_idx_0 = H_iu[3] / H_iu[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_iu[2] / H_iu[1] * t;
      t *= r;
    } else {
      r = H_iu[1] / H_iu[0];
      t = 1.0F / (H_iu[3] - r * H_iu[2]);
      b_y_idx_0 = H_iu[3] / H_iu[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_iu[2] / H_iu[0] * t;
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
      i_est_lb[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_n4 / r);
      rtElectricalID_6ph_codegen_DW->d_e[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_bf[k] - i_est_lb[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_e[k] *
        rtElectricalID_6ph_codegen_DW->d_e[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S2>:36:66' if e_lm < e */
    if (e_lm < *e_d) {
      /* '<S2>:36:67' lambda = lambda/10; */
      *lambda_l /= 10.0F;

      /* '<S2>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S2>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S2>:36:70' e = e_lm; */
      *e_d = e_lm;

      /* '<S2>:36:71' updateJ = boolean(1); */
      *updateJ_ok = true;
    } else {
      /* '<S2>:36:72' else */
      /* '<S2>:36:73' updateJ = boolean(0); */
      *updateJ_ok = false;

      /* '<S2>:36:74' lambda = lambda*10; */
      *lambda_l *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response1'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchart__b_MeasureStepRespon_d(real32_T v_dq_x, real32_T i_dq_x,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponse': '<S3>:39' */
  /* '<S3>:39:2' fns = fieldnames(i_dq); */
  /* '<S3>:39:3' current = i_dq.(fns{index}); */
  /* '<S3>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S3>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_n <= 1024U) {
    /* '<S3>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_n > 1U) {
      /* '<S3>:39:7' current_meas_array(counter-1) = current; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_n - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_n - 1U >
          rtElectricalID_6ph_codegen_DW->counter_n) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_j[k - 1] = i_dq_x;

      /* safe 1024 current values to 2D array */
      /* '<S3>:39:8' voltage_meas_array(counter-1) = voltage; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_n - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_n - 1U >
          rtElectricalID_6ph_codegen_DW->counter_n) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->voltage_meas_array_m[k - 1] = v_dq_x;

      /* '<S3>:39:9' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_n -
          rtElectricalID_6ph_codegen_DW->counter_n / 5U * 5U == 0U) {
        uint32_T tmp;

        /* exec every 5th cycle */
        /* '<S3>:39:10' Vstep(z-1) = voltage; */
        /* safe Va */
        /* '<S3>:39:11' z = z + 1; */
        tmp = rtElectricalID_6ph_codegen_DW->z_f + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_f + 1U > 65535U) {
          tmp = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_f = (uint16_T)tmp;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_n == 1U) {
      uint32_T tmp;

      /* '<S3>:39:13' elseif(counter == 1) */
      /* '<S3>:39:14' Vstep(1) = voltage; */
      /* safe Va 1st cycle */
      /* '<S3>:39:15' z = z + 1; */
      tmp = rtElectricalID_6ph_codegen_DW->z_f + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_f + 1U > 65535U) {
        tmp = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_f = (uint16_T)tmp;
    }

    /* '<S3>:39:17' else */
    /* '<S3>:39:18' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_n == 1025U) {
    real32_T x;

    /* '<S3>:39:19' current_meas_array(counter-1) = current; */
    rtElectricalID_6ph_codegen_DW->current_meas_array_j[1023] = i_dq_x;

    /* safe last current val */
    /* '<S3>:39:20' voltage_meas_array(counter-1) = voltage; */
    rtElectricalID_6ph_codegen_DW->voltage_meas_array_m[1023] = v_dq_x;

    /* '<S3>:39:21' Vstep(z-1) = voltage; */
    /* '<S3>:39:22' V0 = mean(voltage_meas_array); */
    x = rtElectricalID_6ph_codegen_DW->voltage_meas_array_m[0];
    for (k = 0; k < 1023; k++) {
      x += rtElectricalID_6ph_codegen_DW->voltage_meas_array_m[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_al = x / 1024.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response1'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_g(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_h, boolean_T
  *updateJ_j, real32_T *lambda_g, real32_T *e_b, real32_T H_iq[4], real32_T
  i_est_o[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b;
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
  b = *n_iters_h;
  for (it = 0; it < b; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S3>:36:26' if updateJ == 1 */
    if (*updateJ_j) {
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
        rtElectricalID_6ph_codegen_DW->J_p[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_al) / (*R_est * *R_est) -
          (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_al *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_p[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_al *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S3>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_o[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_al / *R_est);
        rtElectricalID_6ph_codegen_DW->d_h[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_j[k] - i_est_o[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S3>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_iq[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_iq[tmp] += rtElectricalID_6ph_codegen_DW->J_p[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_p[(i << 11) + i_0];
          }
        }
      }

      /* '<S3>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S3>:36:44' e = dot(d,d); */
        *e_b = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_b += rtElectricalID_6ph_codegen_DW->d_h[k] *
            rtElectricalID_6ph_codegen_DW->d_h[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S3>:36:49' H(1,1) = H(1,1) + lambda; */
    H_iq[0] += *lambda_g;

    /* '<S3>:36:50' H(2,2)=H(2,2)+lambda; */
    H_iq[3] += *lambda_g;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S3>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_p[k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_h[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_p[(k + 1024) % 1024 + 2048] *
        rtElectricalID_6ph_codegen_DW->d_h[k];
    }

    if (fabsf(H_iq[1]) > fabsf(H_iq[0])) {
      r = H_iq[0] / H_iq[1];
      t = 1.0F / (r * H_iq[3] - H_iq[2]);
      b_y_idx_0 = H_iq[3] / H_iq[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_iq[2] / H_iq[1] * t;
      t *= r;
    } else {
      r = H_iq[1] / H_iq[0];
      t = 1.0F / (H_iq[3] - r * H_iq[2]);
      b_y_idx_0 = H_iq[3] / H_iq[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_iq[2] / H_iq[0] * t;
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
      i_est_o[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_al / r);
      rtElectricalID_6ph_codegen_DW->d_h[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_j[k] - i_est_o[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_h[k] *
        rtElectricalID_6ph_codegen_DW->d_h[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S3>:36:66' if e_lm < e */
    if (e_lm < *e_b) {
      /* '<S3>:36:67' lambda = lambda/10; */
      *lambda_g /= 10.0F;

      /* '<S3>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S3>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S3>:36:70' e = e_lm; */
      *e_b = e_lm;

      /* '<S3>:36:71' updateJ = boolean(1); */
      *updateJ_j = true;
    } else {
      /* '<S3>:36:72' else */
      /* '<S3>:36:73' updateJ = boolean(0); */
      *updateJ_j = false;

      /* '<S3>:36:74' lambda = lambda*10; */
      *lambda_g *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response2'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchart_bt_MeasureStepRespon_b(real32_T v_dq_y, real32_T i_dq_y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponse': '<S4>:39' */
  /* '<S4>:39:2' fns = fieldnames(i_dq); */
  /* '<S4>:39:3' current = i_dq.(fns{index}); */
  /* '<S4>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S4>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_j <= 1024U) {
    /* '<S4>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_j > 1U) {
      /* '<S4>:39:7' current_meas_array(counter-1) = current; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_j - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_j - 1U >
          rtElectricalID_6ph_codegen_DW->counter_j) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_b[k - 1] = i_dq_y;

      /* safe 1024 current values to 2D array */
      /* '<S4>:39:8' voltage_meas_array(counter-1) = voltage; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_j - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_j - 1U >
          rtElectricalID_6ph_codegen_DW->counter_j) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->voltage_meas_array_a[k - 1] = v_dq_y;

      /* '<S4>:39:9' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_j -
          rtElectricalID_6ph_codegen_DW->counter_j / 5U * 5U == 0U) {
        uint32_T tmp;

        /* exec every 5th cycle */
        /* '<S4>:39:10' Vstep(z-1) = voltage; */
        /* safe Va */
        /* '<S4>:39:11' z = z + 1; */
        tmp = rtElectricalID_6ph_codegen_DW->z_a + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_a + 1U > 65535U) {
          tmp = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_a = (uint16_T)tmp;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_j == 1U) {
      uint32_T tmp;

      /* '<S4>:39:13' elseif(counter == 1) */
      /* '<S4>:39:14' Vstep(1) = voltage; */
      /* safe Va 1st cycle */
      /* '<S4>:39:15' z = z + 1; */
      tmp = rtElectricalID_6ph_codegen_DW->z_a + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_a + 1U > 65535U) {
        tmp = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_a = (uint16_T)tmp;
    }

    /* '<S4>:39:17' else */
    /* '<S4>:39:18' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_j == 1025U) {
    real32_T x;

    /* '<S4>:39:19' current_meas_array(counter-1) = current; */
    rtElectricalID_6ph_codegen_DW->current_meas_array_b[1023] = i_dq_y;

    /* safe last current val */
    /* '<S4>:39:20' voltage_meas_array(counter-1) = voltage; */
    rtElectricalID_6ph_codegen_DW->voltage_meas_array_a[1023] = v_dq_y;

    /* '<S4>:39:21' Vstep(z-1) = voltage; */
    /* '<S4>:39:22' V0 = mean(voltage_meas_array); */
    x = rtElectricalID_6ph_codegen_DW->voltage_meas_array_a[0];
    for (k = 0; k < 1023; k++) {
      x += rtElectricalID_6ph_codegen_DW->voltage_meas_array_a[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_a = x / 1024.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response2'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_c(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_o, boolean_T
  *updateJ_o1, real32_T *lambda_h, real32_T *e_ib, real32_T H_d[4], real32_T
  i_est_l[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b;
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
  b = *n_iters_o;
  for (it = 0; it < b; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S4>:36:26' if updateJ == 1 */
    if (*updateJ_o1) {
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
        rtElectricalID_6ph_codegen_DW->J_bk[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_a) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_a *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_bk[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_a *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S4>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_l[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_a / *R_est);
        rtElectricalID_6ph_codegen_DW->d_p[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_b[k] - i_est_l[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S4>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_d[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_d[tmp] += rtElectricalID_6ph_codegen_DW->J_bk[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_bk[(i << 11) + i_0];
          }
        }
      }

      /* '<S4>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S4>:36:44' e = dot(d,d); */
        *e_ib = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_ib += rtElectricalID_6ph_codegen_DW->d_p[k] *
            rtElectricalID_6ph_codegen_DW->d_p[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S4>:36:49' H(1,1) = H(1,1) + lambda; */
    H_d[0] += *lambda_h;

    /* '<S4>:36:50' H(2,2)=H(2,2)+lambda; */
    H_d[3] += *lambda_h;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S4>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_bk[k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_p[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_bk[(k + 1024) % 1024 + 2048] *
        rtElectricalID_6ph_codegen_DW->d_p[k];
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
      i_est_l[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_a / r);
      rtElectricalID_6ph_codegen_DW->d_p[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_b[k] - i_est_l[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_p[k] *
        rtElectricalID_6ph_codegen_DW->d_p[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S4>:36:66' if e_lm < e */
    if (e_lm < *e_ib) {
      /* '<S4>:36:67' lambda = lambda/10; */
      *lambda_h /= 10.0F;

      /* '<S4>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S4>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S4>:36:70' e = e_lm; */
      *e_ib = e_lm;

      /* '<S4>:36:71' updateJ = boolean(1); */
      *updateJ_o1 = true;
    } else {
      /* '<S4>:36:72' else */
      /* '<S4>:36:73' updateJ = boolean(0); */
      *updateJ_o1 = false;

      /* '<S4>:36:74' lambda = lambda*10; */
      *lambda_h *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response3'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subchar_btw_MeasureStepRespon_n(real32_T v_dq_z1, real32_T i_dq_z1,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponse': '<S5>:39' */
  /* '<S5>:39:2' fns = fieldnames(i_dq); */
  /* '<S5>:39:3' current = i_dq.(fns{index}); */
  /* '<S5>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S5>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_l <= 1024U) {
    /* '<S5>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_l > 1U) {
      /* '<S5>:39:7' current_meas_array(counter-1) = current; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_l - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_l - 1U >
          rtElectricalID_6ph_codegen_DW->counter_l) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_k[k - 1] = i_dq_z1;

      /* safe 1024 current values to 2D array */
      /* '<S5>:39:8' voltage_meas_array(counter-1) = voltage; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_l - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_l - 1U >
          rtElectricalID_6ph_codegen_DW->counter_l) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->voltage_meas_array_e[k - 1] = v_dq_z1;

      /* '<S5>:39:9' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_l -
          rtElectricalID_6ph_codegen_DW->counter_l / 5U * 5U == 0U) {
        uint32_T tmp;

        /* exec every 5th cycle */
        /* '<S5>:39:10' Vstep(z-1) = voltage; */
        /* safe Va */
        /* '<S5>:39:11' z = z + 1; */
        tmp = rtElectricalID_6ph_codegen_DW->z_n + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_n + 1U > 65535U) {
          tmp = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_n = (uint16_T)tmp;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_l == 1U) {
      uint32_T tmp;

      /* '<S5>:39:13' elseif(counter == 1) */
      /* '<S5>:39:14' Vstep(1) = voltage; */
      /* safe Va 1st cycle */
      /* '<S5>:39:15' z = z + 1; */
      tmp = rtElectricalID_6ph_codegen_DW->z_n + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_n + 1U > 65535U) {
        tmp = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_n = (uint16_T)tmp;
    }

    /* '<S5>:39:17' else */
    /* '<S5>:39:18' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_l == 1025U) {
    real32_T x;

    /* '<S5>:39:19' current_meas_array(counter-1) = current; */
    rtElectricalID_6ph_codegen_DW->current_meas_array_k[1023] = i_dq_z1;

    /* safe last current val */
    /* '<S5>:39:20' voltage_meas_array(counter-1) = voltage; */
    rtElectricalID_6ph_codegen_DW->voltage_meas_array_e[1023] = v_dq_z1;

    /* '<S5>:39:21' Vstep(z-1) = voltage; */
    /* '<S5>:39:22' V0 = mean(voltage_meas_array); */
    x = rtElectricalID_6ph_codegen_DW->voltage_meas_array_e[0];
    for (k = 0; k < 1023; k++) {
      x += rtElectricalID_6ph_codegen_DW->voltage_meas_array_e[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_n = x / 1024.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response3'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_o(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_l, boolean_T
  *updateJ_h, real32_T *lambda_j, real32_T *e_i, real32_T H_l[4], real32_T
  i_est_m[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b;
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
  b = *n_iters_l;
  for (it = 0; it < b; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S5>:36:26' if updateJ == 1 */
    if (*updateJ_h) {
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
        rtElectricalID_6ph_codegen_DW->J_b[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_n) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_b[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S5>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_m[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_n / *R_est);
        rtElectricalID_6ph_codegen_DW->d_n[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_k[k] - i_est_m[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S5>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_l[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_l[tmp] += rtElectricalID_6ph_codegen_DW->J_b[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_b[(i << 11) + i_0];
          }
        }
      }

      /* '<S5>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S5>:36:44' e = dot(d,d); */
        *e_i = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_i += rtElectricalID_6ph_codegen_DW->d_n[k] *
            rtElectricalID_6ph_codegen_DW->d_n[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S5>:36:49' H(1,1) = H(1,1) + lambda; */
    H_l[0] += *lambda_j;

    /* '<S5>:36:50' H(2,2)=H(2,2)+lambda; */
    H_l[3] += *lambda_j;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S5>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_b[k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_n[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_b[(k + 1024) % 1024 + 2048] *
        rtElectricalID_6ph_codegen_DW->d_n[k];
    }

    if (fabsf(H_l[1]) > fabsf(H_l[0])) {
      r = H_l[0] / H_l[1];
      t = 1.0F / (r * H_l[3] - H_l[2]);
      b_y_idx_0 = H_l[3] / H_l[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_l[2] / H_l[1] * t;
      t *= r;
    } else {
      r = H_l[1] / H_l[0];
      t = 1.0F / (H_l[3] - r * H_l[2]);
      b_y_idx_0 = H_l[3] / H_l[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_l[2] / H_l[0] * t;
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
      i_est_m[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_n / r);
      rtElectricalID_6ph_codegen_DW->d_n[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_k[k] - i_est_m[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_n[k] *
        rtElectricalID_6ph_codegen_DW->d_n[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S5>:36:66' if e_lm < e */
    if (e_lm < *e_i) {
      /* '<S5>:36:67' lambda = lambda/10; */
      *lambda_j /= 10.0F;

      /* '<S5>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S5>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S5>:36:70' e = e_lm; */
      *e_i = e_lm;

      /* '<S5>:36:71' updateJ = boolean(1); */
      *updateJ_h = true;
    } else {
      /* '<S5>:36:72' else */
      /* '<S5>:36:73' updateJ = boolean(0); */
      *updateJ_h = false;

      /* '<S5>:36:74' lambda = lambda*10; */
      *lambda_j *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response4'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subcha_btw5_MeasureStepRespon_k(real32_T v_dq_z2, real32_T i_dq_z2,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponse': '<S6>:39' */
  /* '<S6>:39:2' fns = fieldnames(i_dq); */
  /* '<S6>:39:3' current = i_dq.(fns{index}); */
  /* '<S6>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S6>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_o <= 1024U) {
    /* '<S6>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_o > 1U) {
      /* '<S6>:39:7' current_meas_array(counter-1) = current; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_o - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_o - 1U >
          rtElectricalID_6ph_codegen_DW->counter_o) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array_m[k - 1] = i_dq_z2;

      /* safe 1024 current values to 2D array */
      /* '<S6>:39:8' voltage_meas_array(counter-1) = voltage; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_o - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_o - 1U >
          rtElectricalID_6ph_codegen_DW->counter_o) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->voltage_meas_array_p[k - 1] = v_dq_z2;

      /* '<S6>:39:9' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_o -
          rtElectricalID_6ph_codegen_DW->counter_o / 5U * 5U == 0U) {
        uint32_T tmp;

        /* exec every 5th cycle */
        /* '<S6>:39:10' Vstep(z-1) = voltage; */
        /* safe Va */
        /* '<S6>:39:11' z = z + 1; */
        tmp = rtElectricalID_6ph_codegen_DW->z_p + 1U;
        if (rtElectricalID_6ph_codegen_DW->z_p + 1U > 65535U) {
          tmp = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z_p = (uint16_T)tmp;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_o == 1U) {
      uint32_T tmp;

      /* '<S6>:39:13' elseif(counter == 1) */
      /* '<S6>:39:14' Vstep(1) = voltage; */
      /* safe Va 1st cycle */
      /* '<S6>:39:15' z = z + 1; */
      tmp = rtElectricalID_6ph_codegen_DW->z_p + 1U;
      if (rtElectricalID_6ph_codegen_DW->z_p + 1U > 65535U) {
        tmp = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z_p = (uint16_T)tmp;
    }

    /* '<S6>:39:17' else */
    /* '<S6>:39:18' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_o == 1025U) {
    real32_T x;

    /* '<S6>:39:19' current_meas_array(counter-1) = current; */
    rtElectricalID_6ph_codegen_DW->current_meas_array_m[1023] = i_dq_z2;

    /* safe last current val */
    /* '<S6>:39:20' voltage_meas_array(counter-1) = voltage; */
    rtElectricalID_6ph_codegen_DW->voltage_meas_array_p[1023] = v_dq_z2;

    /* '<S6>:39:21' Vstep(z-1) = voltage; */
    /* '<S6>:39:22' V0 = mean(voltage_meas_array); */
    x = rtElectricalID_6ph_codegen_DW->voltage_meas_array_p[0];
    for (k = 0; k < 1023; k++) {
      x += rtElectricalID_6ph_codegen_DW->voltage_meas_array_p[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_k = x / 1024.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response4'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_f(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters_f, boolean_T
  *updateJ_o, real32_T *lambda_n, real32_T *e_f, real32_T H_i[4], real32_T
  i_est_f[2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b;
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
  b = *n_iters_f;
  for (it = 0; it < b; it++) {
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
        rtElectricalID_6ph_codegen_DW->J_k[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_k) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_k[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S6>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_f[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_k / *R_est);
        rtElectricalID_6ph_codegen_DW->d_l[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_m[k] - i_est_f[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S6>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_i[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_i[tmp] += rtElectricalID_6ph_codegen_DW->J_k[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_k[(i << 11) + i_0];
          }
        }
      }

      /* '<S6>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S6>:36:44' e = dot(d,d); */
        *e_f = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_f += rtElectricalID_6ph_codegen_DW->d_l[k] *
            rtElectricalID_6ph_codegen_DW->d_l[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S6>:36:49' H(1,1) = H(1,1) + lambda; */
    H_i[0] += *lambda_n;

    /* '<S6>:36:50' H(2,2)=H(2,2)+lambda; */
    H_i[3] += *lambda_n;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S6>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_k[k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_l[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_k[(k + 1024) % 1024 + 2048] *
        rtElectricalID_6ph_codegen_DW->d_l[k];
    }

    if (fabsf(H_i[1]) > fabsf(H_i[0])) {
      r = H_i[0] / H_i[1];
      t = 1.0F / (r * H_i[3] - H_i[2]);
      b_y_idx_0 = H_i[3] / H_i[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_i[2] / H_i[1] * t;
      t *= r;
    } else {
      r = H_i[1] / H_i[0];
      t = 1.0F / (H_i[3] - r * H_i[2]);
      b_y_idx_0 = H_i[3] / H_i[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_i[2] / H_i[0] * t;
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
      i_est_f[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_k / r);
      rtElectricalID_6ph_codegen_DW->d_l[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_m[k] - i_est_f[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_l[k] *
        rtElectricalID_6ph_codegen_DW->d_l[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S6>:36:66' if e_lm < e */
    if (e_lm < *e_f) {
      /* '<S6>:36:67' lambda = lambda/10; */
      *lambda_n /= 10.0F;

      /* '<S6>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S6>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S6>:36:70' e = e_lm; */
      *e_f = e_lm;

      /* '<S6>:36:71' updateJ = boolean(1); */
      *updateJ_o = true;
    } else {
      /* '<S6>:36:72' else */
      /* '<S6>:36:73' updateJ = boolean(0); */
      *updateJ_o = false;

      /* '<S6>:36:74' lambda = lambda*10; */
      *lambda_n *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response5'
 * function MeasureStepResponse(v_dq,i_dq)
 */
static void Subch_btw5m_MeasureStepRespon_m(real32_T v_dq_q, real32_T i_dq_q,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;

  /* MATLAB Function 'MeasureStepResponse': '<S7>:39' */
  /* '<S7>:39:2' fns = fieldnames(i_dq); */
  /* '<S7>:39:3' current = i_dq.(fns{index}); */
  /* '<S7>:39:4' voltage = v_dq.(fns{index}); */
  /* '<S7>:39:5' if(counter <= 1024) */
  if (rtElectricalID_6ph_codegen_DW->counter_e <= 1024U) {
    /* '<S7>:39:6' if(counter > 1) */
    if (rtElectricalID_6ph_codegen_DW->counter_e > 1U) {
      /* '<S7>:39:7' current_meas_array(counter-1) = current; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_e - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_e - 1U >
          rtElectricalID_6ph_codegen_DW->counter_e) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->current_meas_array[k - 1] = i_dq_q;

      /* safe 1024 current values to 2D array */
      /* '<S7>:39:8' voltage_meas_array(counter-1) = voltage; */
      k = (int32_T)(rtElectricalID_6ph_codegen_DW->counter_e - 1U);
      if (rtElectricalID_6ph_codegen_DW->counter_e - 1U >
          rtElectricalID_6ph_codegen_DW->counter_e) {
        k = 0;
      }

      rtElectricalID_6ph_codegen_DW->voltage_meas_array[k - 1] = v_dq_q;

      /* '<S7>:39:9' if(mod(counter,5) == 0) */
      if (rtElectricalID_6ph_codegen_DW->counter_e -
          rtElectricalID_6ph_codegen_DW->counter_e / 5U * 5U == 0U) {
        uint32_T tmp;

        /* exec every 5th cycle */
        /* '<S7>:39:10' Vstep(z-1) = voltage; */
        /* safe Va */
        /* '<S7>:39:11' z = z + 1; */
        tmp = rtElectricalID_6ph_codegen_DW->z + 1U;
        if (rtElectricalID_6ph_codegen_DW->z + 1U > 65535U) {
          tmp = 65535U;
        }

        rtElectricalID_6ph_codegen_DW->z = (uint16_T)tmp;
      }
    } else if (rtElectricalID_6ph_codegen_DW->counter_e == 1U) {
      uint32_T tmp;

      /* '<S7>:39:13' elseif(counter == 1) */
      /* '<S7>:39:14' Vstep(1) = voltage; */
      /* safe Va 1st cycle */
      /* '<S7>:39:15' z = z + 1; */
      tmp = rtElectricalID_6ph_codegen_DW->z + 1U;
      if (rtElectricalID_6ph_codegen_DW->z + 1U > 65535U) {
        tmp = 65535U;
      }

      rtElectricalID_6ph_codegen_DW->z = (uint16_T)tmp;
    }

    /* '<S7>:39:17' else */
    /* '<S7>:39:18' if(counter == 1025) */
  } else if (rtElectricalID_6ph_codegen_DW->counter_e == 1025U) {
    real32_T x;

    /* '<S7>:39:19' current_meas_array(counter-1) = current; */
    rtElectricalID_6ph_codegen_DW->current_meas_array[1023] = i_dq_q;

    /* safe last current val */
    /* '<S7>:39:20' voltage_meas_array(counter-1) = voltage; */
    rtElectricalID_6ph_codegen_DW->voltage_meas_array[1023] = v_dq_q;

    /* '<S7>:39:21' Vstep(z-1) = voltage; */
    /* '<S7>:39:22' V0 = mean(voltage_meas_array); */
    x = rtElectricalID_6ph_codegen_DW->voltage_meas_array[0];
    for (k = 0; k < 1023; k++) {
      x += rtElectricalID_6ph_codegen_DW->voltage_meas_array[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0 = x / 1024.0F;

    /* average voltage */
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response5'
 * function LM_algorithm
 *  Startwerte Festlegen
 * V0 = V_s;                           % Spannungssprung in Volt
 */
static void LM_algorithm_h(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, const uint16_T *n_iters, boolean_T *updateJ,
  real32_T *lambda, real32_T *e, real32_T H[4], real32_T i_est_g[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b;
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
  b = *n_iters;
  for (it = 0; it < b; it++) {
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
        i_est_g[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0 / *R_est);
        rtElectricalID_6ph_codegen_DW->d_f[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_g[k];
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
          *e += rtElectricalID_6ph_codegen_DW->d_f[k] *
            rtElectricalID_6ph_codegen_DW->d_f[k];
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
      e_lm += rtElectricalID_6ph_codegen_DW->J[k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J[(k + 1024) % 1024 + 2048] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
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
      i_est_g[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0 / r);
      rtElectricalID_6ph_codegen_DW->d_f[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_g[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_f[k] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
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

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void enter_atomic_waitState(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
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

  /* '<S1>:428:5' ElectricalID_FOC_output.resetIntegrator=boolean(1); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = true;

  /* '<S1>:428:6' ElectricalID_FOC_output.PI_subsystem = 0x0000; */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.PI_subsystem = 0U;

  /*  recalculate speed controller using psiPM and J */
  /* '<S1>:428:8' Kp_n_loc = Kp_iq_loc/(ElectricalID_output.PMSM_parameters.Lq_Henry*dampingFactor*... */
  /* '<S1>:428:9'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*ElectricalID_output.PMSM_parameters.Psi_PM_Vs/.... */
  /* '<S1>:428:10'     ElectricalID_output.PMSM_parameters.J_kg_m_squared); */
  /* . */
  /* '<S1>:428:11' Ki_n_loc = (Kp_iq_loc * Kp_iq_loc)/( ElectricalID_output.PMSM_parameters.Lq_Henry * .... */
  /* '<S1>:428:12'     ElectricalID_output.PMSM_parameters.Lq_Henry * dampingFactor * dampingFactor * dampingFactor * .... */
  /* '<S1>:428:13'     GlobalConfig.PMSM_config.polePairs*3.0/2.0*ElectricalID_output.PMSM_parameters.Psi_PM_Vs/.... */
  /* '<S1>:428:14'     ElectricalID_output.PMSM_parameters.J_kg_m_squared); */
  /* . */
  /* '<S1>:428:15' ElectricalID_FOC_output.Kp_n_out = Kp_n_loc; */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_n_out =
    rtElectricalID_6ph_codegen_DW->Kp_iq_loc /
    (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
     * rtElectricalID_6ph_codegen_DW->dampingFactor *
     rtElectricalID_6ph_codegen_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F
     / 2.0F *
     rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
     /
     rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared);

  /* '<S1>:428:16' ElectricalID_FOC_output.Ki_n_out = Ki_n_loc; */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_n_out =
    rtElectricalID_6ph_codegen_DW->Kp_iq_loc *
    rtElectricalID_6ph_codegen_DW->Kp_iq_loc /
    (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
     * rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
     * rtElectricalID_6ph_codegen_DW->dampingFactor *
     rtElectricalID_6ph_codegen_DW->dampingFactor *
     rtElectricalID_6ph_codegen_DW->dampingFactor *
     rtElectricalID_6ph_codegen_U->GlobalConfig_out.PMSM_config.polePairs * 3.0F
     / 2.0F *
     rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Psi_PM_Vs
     /
     rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared);

  /* '<S1>:428:17' ElectricalID_FOC_output.activeState = uint16(170); */
  rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 170U;
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function DutyCycle_mod(ia_reg_in)
 */
static void DutyCycle_mod(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
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
  /* During 'findDutyCycle': '<S1>:789' */
  /* '<S1>:921:1' sf_internal_predicateOutput = DC_valid==1 && ElectricalIDConfig.manual_offset<0; */
  if (rtElectricalID_6ph_codegen_DW->DC_valid &&
      (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.manual_offset < 0.0F)) {
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

    /* '<S1>:1128:1' sf_internal_predicateOutput = DC_valid==1 && ElectricalIDConfig.manual_offset>=0; */
  } else if (rtElectricalID_6ph_codegen_DW->DC_valid &&
             (rtElectricalID_6ph_codegen_U->ElectricalIDConfig.manual_offset >=
              0.0F)) {
    /* Merge: '<S1>/ Merge ' */
    /* Transition: '<S1>:1128' */
    /* '<S1>:1128:1' ElectricalID_output.thetaOffset=ElectricalIDConfig.manual_offset */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
      rtElectricalID_6ph_codegen_U->ElectricalIDConfig.manual_offset;

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
    /* Inport: '<Root>/GlobalConfig' */
    /* '<S1>:789:16' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
      rtElectricalID_6ph_codegen_DW->DutyCycle;

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

    /* End of Inport: '<Root>/GlobalConfig' */
  }
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
 * function out = correct_setpoint(setpoint_rpm,ratSpeed_rpm,polepairs,FFT_length_ms)
 * correct_setpoint corrects the requested rpm
 *  function:
 *  if corrected_setpoint_rpm is larger than n_ref set it to n_ref
 */
static real32_T correct_setpoint(real32_T setpoint_rpm, real32_T ratSpeed_rpm,
  real32_T polepairs, real32_T FFT_length_ms)
{
  real32_T T_fundamental_ms;

  /* MATLAB Function 'correct_setpoint': '<S1>:1073' */
  /* '<S1>:1073:5' if(setpoint_rpm>ratSpeed_rpm) */
  if (setpoint_rpm > ratSpeed_rpm) {
    /* '<S1>:1073:6' setpoint_rpm = ratSpeed_rpm; */
    setpoint_rpm = ratSpeed_rpm;
  }

  /* '<S1>:1073:8' T_fundamental_ms = 1/(setpoint_rpm/60*polepairs)*1000; */
  T_fundamental_ms = 1.0F / (setpoint_rpm / 60.0F * polepairs) * 1000.0F;

  /*  find integer multiple of FFT window */
  /* '<S1>:1073:10' while mod(FFT_length_ms,T_fundamental_ms) */
  int32_T exitg1;
  real32_T b;
  do {
    exitg1 = 0;
    b = FFT_length_ms;
    if (T_fundamental_ms == 0.0F) {
      if (FFT_length_ms == 0.0F) {
        b = T_fundamental_ms;
      }
    } else if (FFT_length_ms == 0.0F) {
      b = 0.0F / T_fundamental_ms;
    } else {
      boolean_T rEQ0;
      b = fmodf(FFT_length_ms, T_fundamental_ms);
      rEQ0 = (b == 0.0F);
      if ((!rEQ0) && (T_fundamental_ms > floorf(T_fundamental_ms))) {
        real32_T q;
        q = fabsf(FFT_length_ms / T_fundamental_ms);
        rEQ0 = (fabsf(q - floorf(q + 0.5F)) <= 1.1920929E-7F * q);
      }

      if (rEQ0) {
        b = 0.0F;
      } else if ((FFT_length_ms < 0.0F) != (T_fundamental_ms < 0.0F)) {
        b += T_fundamental_ms;
      }
    }

    if (b != 0.0F) {
      /* '<S1>:1073:11' setpoint_rpm = setpoint_rpm-1; */
      setpoint_rpm--;

      /* '<S1>:1073:12' T_fundamental_ms = 1/(setpoint_rpm/60*polepairs)*1000; */
      T_fundamental_ms = 1.0F / (setpoint_rpm / 60.0F * polepairs) * 1000.0F;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  /* '<S1>:1073:14' out = setpoint_rpm; */
  return setpoint_rpm;
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void gatherResults(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  boolean_T guard1 = false;
  boolean_T tmp_0;

  /* During 'gatherResults': '<S1>:1028' */
  /* '<S1>:1104:1' sf_internal_predicateOutput = ~ElectricalIDConfig.extended_psi && GlobalConfig.ACCEPT==1 && ElectricalIDConfig.identLq==1; */
  tmp_0 = !rtElectricalID_6ph_codegen_U->ElectricalIDConfig.extended_psi;
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
    /* '<S1>:1047:8' loc_setpoint_rpm = f_cutoff/single(highest_order)/ElectricalID_output.PMSM_parameters.polePairs*single(60); */
    /* '<S1>:1047:9' ElectricalID_output.set_rpm_val = correct_setpoint(loc_setpoint_rpm,GlobalConfig.ratSpeed,.... */
    /* '<S1>:1047:10'     ElectricalID_output.PMSM_parameters.polePairs,loc_FFT_length_ms); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.set_rpm_val =
      correct_setpoint(cutoff_frequency
                       (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_C)
                       / 9.0F /
                       rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs
                       * 60.0F,
                       rtElectricalID_6ph_codegen_U->GlobalConfig_out.ratSpeed,
                       rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs,
                       loc_FFT_length_ms);

    /* . */

    /* '<S1>:1115:1' sf_internal_predicateOutput = ~ElectricalIDConfig.extended_psi && ElectricalIDConfig.identLq==0; */
  } else if (tmp_0 && (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq))
  {
    /* Transition: '<S1>:1115' */
    guard1 = true;
  }

  if (guard1) {
    uint64_T tmp;
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

    /* '<S1>:1106:7' wait_count = 5*one_sec_transition_counter; */
    tmp = 5ULL * rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
    if (tmp > 4294967295ULL) {
      tmp = 4294967295ULL;
    }

    rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)tmp;
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
  /* '<S1>:350:33' Xg = s0-s1*C */
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
  /* '<S1>:350:49' Yg = s0-s1*C */
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
static void rotorInertiaEstimation(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  uint32_T qY;

  /* During 'rotorInertiaEstimation': '<S1>:337' */
  /* '<S1>:1118:1' sf_internal_predicateOutput = counter == (wait_count+513) && ElectricalIDConfig.extended_offset==true; */
  qY = rtElectricalID_6ph_codegen_DW->wait_count + 513U;
  if (rtElectricalID_6ph_codegen_DW->wait_count + 513U <
      rtElectricalID_6ph_codegen_DW->wait_count) {
    qY = MAX_uint32_T;
  }

  if ((rtElectricalID_6ph_codegen_DW->counter == qY) &&
      rtElectricalID_6ph_codegen_U->ElectricalIDConfig.extended_offset) {
    /* Transition: '<S1>:1118' */
    /* Exit 'rotorInertiaEstimation': '<S1>:337' */
    /* '<S1>:337:18' goertzel; */
    goertzel(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* '<S1>:337:19' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = true;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID =
      IN_initSetpointsExtendedOffsetE;

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Entry 'initSetpointsExtendedOffsetEstimation': '<S1>:1123' */
    /* '<S1>:1123:3' ElectricalID_FOC_output.activeState = uint16(165); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 165U;

    /* '<S1>:1123:4' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;
  } else {
    /* '<S1>:357:1' sf_internal_predicateOutput = counter == (wait_count+513) && ElectricalIDConfig.extended_offset==false; */
    qY = rtElectricalID_6ph_codegen_DW->wait_count + 513U;
    if (rtElectricalID_6ph_codegen_DW->wait_count + 513U <
        rtElectricalID_6ph_codegen_DW->wait_count) {
      qY = MAX_uint32_T;
    }

    if ((rtElectricalID_6ph_codegen_DW->counter == qY) &&
        (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.extended_offset)) {
      /* Transition: '<S1>:357' */
      /* Exit 'rotorInertiaEstimation': '<S1>:337' */
      /* '<S1>:337:18' goertzel; */
      goertzel(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_DW);

      /* Outport: '<Root>/ElectricalID_FOC_output' */
      /* '<S1>:337:19' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
      rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
        true;
      rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitState;
      enter_atomic_waitState(rtElectricalID_6ph_codegen_U,
        rtElectricalID_6ph_codegen_Y, rtElectricalID_6ph_codegen_DW);
    } else {
      /* Outport: '<Root>/ElectricalID_FOC_output' */
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
      qY = rtElectricalID_6ph_codegen_DW->wait_count + /*MW:OvSatOk*/ 501U;
      if (rtElectricalID_6ph_codegen_DW->wait_count + 501U <
          rtElectricalID_6ph_codegen_DW->wait_count) {
        qY = MAX_uint32_T;
      }

      if ((rtElectricalID_6ph_codegen_DW->counter >
           rtElectricalID_6ph_codegen_DW->wait_count) &&
          (rtElectricalID_6ph_codegen_DW->counter < qY)) {
        /* '<S1>:337:13' measArray1(counter-wait_count) = ActualValues.i_dq.q; */
        qY = rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
          rtElectricalID_6ph_codegen_DW->wait_count;
        if (qY > rtElectricalID_6ph_codegen_DW->counter) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->measArray1[(int32_T)qY - 1] =
          rtElectricalID_6ph_codegen_U->ActualValues.i_dq.q;

        /* '<S1>:337:14' i_est(counter-wait_count) = ActualValues.omega_m; */
        qY = rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/
          rtElectricalID_6ph_codegen_DW->wait_count;
        if (qY > rtElectricalID_6ph_codegen_DW->counter) {
          qY = 0U;
        }

        rtElectricalID_6ph_codegen_DW->i_est[(int32_T)qY - 1] =
          rtElectricalID_6ph_codegen_U->ActualValues.omega_m;
      }

      /* '<S1>:337:16' counter = counter + 1; */
      qY = rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
      if (rtElectricalID_6ph_codegen_DW->counter + 1U <
          rtElectricalID_6ph_codegen_DW->counter) {
        qY = MAX_uint32_T;
      }

      rtElectricalID_6ph_codegen_DW->counter = qY;
    }
  }
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void exit_internal_ElectricalID(const uz_ParaID_ElectricalID_fft_in_t
  *BusConversion_InsertedFor_Elect, const
  uz_ParaID_ElectricalID_offset_estimation_t *BusConversion_InsertedFor_Ele_b,
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U,
  ExtY_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_Y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;

  /* Exit Internal 'ElectricalID': '<S1>:761' */
  switch (rtElectricalID_6ph_codegen_DW->is_ElectricalID) {
   case IN_Subchart_Step_Response:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S2>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
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
      rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response1:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S3>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
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
      rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response2:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S4>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
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
      rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response3:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S5>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
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
      rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response4:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
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
      rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response5:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S7>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
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
      rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
        IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_alignRotor_d_off:
    /* Merge: '<S1>/ Merge ' */
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

   case IN_extendedOffsetEstimation:
    /* Merge: '<S1>/ Merge ' */
    /* Exit 'extendedOffsetEstimation': '<S1>:1117' */
    /* '<S1>:1117:10' ElectricalID_output.thetaOffset = extended_offset_estimation.offset_angle_rad; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
      BusConversion_InsertedFor_Ele_b->offset_angle_rad;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_findDutyCycle:
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

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* '<S1>:337:19' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = true;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_stop:
    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* Exit 'stop': '<S1>:361' */
    /* '<S1>:361:6' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator = true;

    /* '<S1>:361:7' ElectricalID_FOC_output.enableFOC_speed = boolean(0); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed =
      false;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_waitFree:
    /* Merge: '<S1>/ Merge ' */
    /* Exit 'waitFree': '<S1>:1112' */
    /* '<S1>:1112:5' ElectricalID_output.enable_TriState = boolean([0 0 0]); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
      false;

    /* '<S1>:1112:6' ElectricalID_output.enable_TriState_set_2 = boolean([0 0 0]); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[0] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[1] =
      false;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[2] =
      false;
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_waitState:
    /* Exit 'waitState': '<S1>:428' */
    /* '<S1>:428:19' finishedElectricalID=boolean(1); */
    rtElectricalID_6ph_codegen_Y->finishedElectricalID = true;

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
  *BusConversion_InsertedFor_Elect, const
  uz_ParaID_ElectricalID_offset_estimation_t *BusConversion_InsertedFor_Ele_b,
  ExtU_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_U,
  ExtY_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_Y,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  uint16_T n_iters_hn;
  boolean_T updateJ_ok;

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
      BusConversion_InsertedFor_Ele_b, rtElectricalID_6ph_codegen_U,
      rtElectricalID_6ph_codegen_Y, rtElectricalID_6ph_codegen_DW);
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
      if (rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S2>:40' */
        /* '<S2>:61:1' sf_internal_predicateOutput = counter == 3*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 3ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        if (rtElectricalID_6ph_codegen_DW->counter_b == (uint32_T)
            rtElectricalID_6ph_codegen_DW->u) {
          /* Transition: '<S2>:61' */
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_c = 2U;
        } else {
          /* '<S2>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_b + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_b + 1U <
              rtElectricalID_6ph_codegen_DW->counter_b) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_b =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S2>:35' */
        /* '<S2>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_b == 1026U) {
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
        rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S2>:40' */
        rtElectricalID_6ph_codegen_DW->e_d = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[3] = 0.0F;
        n_iters_hn = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_l = 0.01F;
        updateJ_ok = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_e[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_lb[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_i[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S2>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_b = 1U;

        /* '<S2>:40:4' LM_algorithm; */
        LM_algorithm(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                     &rtElectricalID_6ph_codegen_DW->R_est_c,
                     &rtElectricalID_6ph_codegen_DW->L_est_m, &n_iters_hn,
                     &updateJ_ok, &rtElectricalID_6ph_codegen_DW->lambda_l,
                     &rtElectricalID_6ph_codegen_DW->e_d,
                     rtElectricalID_6ph_codegen_DW->H_iu,
                     rtElectricalID_6ph_codegen_DW->i_est_lb,
                     rtElectricalID_6ph_codegen_DW);

        /* '<S2>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* '<S2>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchart_St_MeasureStepRespon_e
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.d,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.d,
           rtElectricalID_6ph_codegen_DW);

        /* '<S2>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_b + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_b + 1U <
            rtElectricalID_6ph_codegen_DW->counter_b) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_b =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_c;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_c = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1003' */
        /* '<S1>:1003:1' ElectricalID_output.inductances_6ph.d=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d =
          rtElectricalID_6ph_codegen_DW->L_est_m;

        /* '<S1>:1003:2' ElectricalID_output.resistances_6ph.d=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
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
          rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response1;
        rtElectricalID_6ph_codegen_DW->counter_n = 1U;
        rtElectricalID_6ph_codegen_DW->z_f = 1U;
        rtElectricalID_6ph_codegen_DW->V0_al = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_j[0], 0,
               sizeof(real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_m[0], 0,
               sizeof(real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response1' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S3>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_f[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S3>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response1' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response1:
      /* During 'Subchart_Step_Response1': '<S1>:1001' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S3>:40' */
        /* '<S3>:61:1' sf_internal_predicateOutput = counter == 3*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 3ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        if (rtElectricalID_6ph_codegen_DW->counter_n == (uint32_T)
            rtElectricalID_6ph_codegen_DW->u) {
          /* Transition: '<S3>:61' */
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_i = 2U;
        } else {
          /* '<S3>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_n + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_n + 1U <
              rtElectricalID_6ph_codegen_DW->counter_n) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_n =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S3>:35' */
        /* '<S3>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_n == 1026U) {
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
        rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S3>:40' */
        rtElectricalID_6ph_codegen_DW->e_d = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[3] = 0.0F;
        n_iters_hn = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_l = 0.01F;
        updateJ_ok = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_h[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_lb[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_p[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S3>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_n = 1U;

        /* '<S3>:40:4' LM_algorithm; */
        LM_algorithm_g(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_m, &n_iters_hn,
                       &updateJ_ok, &rtElectricalID_6ph_codegen_DW->lambda_l,
                       &rtElectricalID_6ph_codegen_DW->e_d,
                       rtElectricalID_6ph_codegen_DW->H_iu,
                       rtElectricalID_6ph_codegen_DW->i_est_lb,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S3>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* '<S3>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchart__b_MeasureStepRespon_d
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.x,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.x,
           rtElectricalID_6ph_codegen_DW);

        /* '<S3>:35:9' counter = counter +1; */
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
        rtElectricalID_6ph_codegen_DW->exitPortIndex_i;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_i = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1018' */
        /* '<S1>:1018:1' ElectricalID_output.inductances_6ph.x=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.x =
          rtElectricalID_6ph_codegen_DW->L_est_m;

        /* '<S1>:1018:2' ElectricalID_output.resistances_6ph.x=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.x =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
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
          rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response2;
        rtElectricalID_6ph_codegen_DW->counter_j = 1U;
        rtElectricalID_6ph_codegen_DW->z_a = 1U;
        rtElectricalID_6ph_codegen_DW->V0_a = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_b[0], 0,
               sizeof(real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_a[0], 0,
               sizeof(real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response2' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S4>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_n[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S4>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response2' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response2:
      /* During 'Subchart_Step_Response2': '<S1>:1009' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S4>:40' */
        /* '<S4>:61:1' sf_internal_predicateOutput = counter == 3*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 3ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        if (rtElectricalID_6ph_codegen_DW->counter_j == (uint32_T)
            rtElectricalID_6ph_codegen_DW->u) {
          /* Transition: '<S4>:61' */
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_a = 2U;
        } else {
          /* '<S4>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_j + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_j + 1U <
              rtElectricalID_6ph_codegen_DW->counter_j) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_j =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S4>:35' */
        /* '<S4>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_j == 1026U) {
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
        rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S4>:40' */
        rtElectricalID_6ph_codegen_DW->e_d = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[3] = 0.0F;
        n_iters_hn = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_l = 0.01F;
        updateJ_ok = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_p[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_lb[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_bk[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S4>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_j = 1U;

        /* '<S4>:40:4' LM_algorithm; */
        LM_algorithm_c(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_m, &n_iters_hn,
                       &updateJ_ok, &rtElectricalID_6ph_codegen_DW->lambda_l,
                       &rtElectricalID_6ph_codegen_DW->e_d,
                       rtElectricalID_6ph_codegen_DW->H_iu,
                       rtElectricalID_6ph_codegen_DW->i_est_lb,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S4>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* '<S4>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchart_bt_MeasureStepRespon_b
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.y,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.y,
           rtElectricalID_6ph_codegen_DW);

        /* '<S4>:35:9' counter = counter +1; */
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
        rtElectricalID_6ph_codegen_DW->exitPortIndex_a;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_a = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1019' */
        /* '<S1>:1019:1' ElectricalID_output.inductances_6ph.y=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.y =
          rtElectricalID_6ph_codegen_DW->L_est_m;

        /* '<S1>:1019:2' ElectricalID_output.resistances_6ph.y=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.y =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
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
          rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response3;
        rtElectricalID_6ph_codegen_DW->counter_l = 1U;
        rtElectricalID_6ph_codegen_DW->z_n = 1U;
        rtElectricalID_6ph_codegen_DW->V0_n = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_k[0], 0,
               sizeof(real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_e[0], 0,
               sizeof(real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response3' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S5>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_o[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S5>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response3' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response3:
      /* During 'Subchart_Step_Response3': '<S1>:1013' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S5>:40' */
        /* '<S5>:61:1' sf_internal_predicateOutput = counter == 3*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 3ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        if (rtElectricalID_6ph_codegen_DW->counter_l == (uint32_T)
            rtElectricalID_6ph_codegen_DW->u) {
          /* Transition: '<S5>:61' */
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_p = 2U;
        } else {
          /* '<S5>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_l + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_l + 1U <
              rtElectricalID_6ph_codegen_DW->counter_l) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_l =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S5>:35' */
        /* '<S5>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_l == 1026U) {
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
        rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S5>:40' */
        rtElectricalID_6ph_codegen_DW->e_d = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[3] = 0.0F;
        n_iters_hn = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_l = 0.01F;
        updateJ_ok = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_n[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_lb[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_b[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S5>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_l = 1U;

        /* '<S5>:40:4' LM_algorithm; */
        LM_algorithm_o(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_m, &n_iters_hn,
                       &updateJ_ok, &rtElectricalID_6ph_codegen_DW->lambda_l,
                       &rtElectricalID_6ph_codegen_DW->e_d,
                       rtElectricalID_6ph_codegen_DW->H_iu,
                       rtElectricalID_6ph_codegen_DW->i_est_lb,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S5>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* '<S5>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subchar_btw_MeasureStepRespon_n
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.z1,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z1,
           rtElectricalID_6ph_codegen_DW);

        /* '<S5>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_l + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_l + 1U <
            rtElectricalID_6ph_codegen_DW->counter_l) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_l =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_p;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_p = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1020' */
        /* '<S1>:1020:1' ElectricalID_output.inductances_6ph.z1=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z1 =
          rtElectricalID_6ph_codegen_DW->L_est_m;

        /* '<S1>:1020:2' ElectricalID_output.resistances_6ph.z1=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z1 =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
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
          rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response4;
        rtElectricalID_6ph_codegen_DW->counter_o = 1U;
        rtElectricalID_6ph_codegen_DW->z_p = 1U;
        rtElectricalID_6ph_codegen_DW->V0_k = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_m[0], 0,
               sizeof(real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_p[0], 0,
               sizeof(real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response4' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S6>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_l[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S6>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response4' */
        /* set DutyCycles */
      }
      break;

     case IN_Subchart_Step_Response4:
      /* During 'Subchart_Step_Response4': '<S1>:1017' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S6>:40' */
        /* '<S6>:61:1' sf_internal_predicateOutput = counter == 3*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 3ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        if (rtElectricalID_6ph_codegen_DW->counter_o == (uint32_T)
            rtElectricalID_6ph_codegen_DW->u) {
          /* Transition: '<S6>:61' */
          /* Exit 'Levenberg_Marquardt': '<S6>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_lu = 2U;
        } else {
          /* '<S6>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_o + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_o + 1U <
              rtElectricalID_6ph_codegen_DW->counter_o) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_o =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S6>:35' */
        /* '<S6>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_o == 1026U) {
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
        rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S6>:40' */
        rtElectricalID_6ph_codegen_DW->e_d = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[3] = 0.0F;
        n_iters_hn = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_l = 0.01F;
        updateJ_ok = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_lb[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_k[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S6>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_o = 1U;

        /* '<S6>:40:4' LM_algorithm; */
        LM_algorithm_f(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_m, &n_iters_hn,
                       &updateJ_ok, &rtElectricalID_6ph_codegen_DW->lambda_l,
                       &rtElectricalID_6ph_codegen_DW->e_d,
                       rtElectricalID_6ph_codegen_DW->H_iu,
                       rtElectricalID_6ph_codegen_DW->i_est_lb,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S6>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* '<S6>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subcha_btw5_MeasureStepRespon_k
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.z2,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z2,
           rtElectricalID_6ph_codegen_DW);

        /* '<S6>:35:9' counter = counter +1; */
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
        rtElectricalID_6ph_codegen_DW->exitPortIndex_lu;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_lu = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1027' */
        /* '<S1>:1027:1' ElectricalID_output.inductances_6ph.z2=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.z2 =
          rtElectricalID_6ph_codegen_DW->L_est_m;

        /* '<S1>:1027:2' ElectricalID_output.resistances_6ph.z2=R_est */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.z2 =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S6>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
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
          rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_gatherResults;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'gatherResults': '<S1>:1028' */
        /* '<S1>:1028:3' ElectricalID_FOC_output.activeState = uint16(148); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 148U;

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

        /* . */
        /* '<S1>:1028:13' ElectricalID_FOC_output = ControllerParameter(ElectricalID_FOC_output,... */
        /* '<S1>:1028:14'     bandwidthCurrentControl,ElectricalID_output.PMSM_parameters,dampingFactor,psiOverJ); */
        rtElectricalID_6ph_codegen_DW->FOC_out_old =
          rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output;

        /* 'ControllerParameter:2' FOC_out_new = FOC_out_old; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output =
          rtElectricalID_6ph_codegen_DW->FOC_out_old;

        /* Outport: '<Root>/ElectricalID_FOC_output' incorporates:
         *  Merge: '<S1>/ Merge '
         */
        /* 'ControllerParameter:3' FOC_out_new.Kp_id_out = single(PMSM_config.Ld_Henry * bandwidthCurrentControl); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_id_out =
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Ld_Henry
          * rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl;

        /* 'ControllerParameter:4' FOC_out_new.Kp_iq_out = single(PMSM_config.Lq_Henry * bandwidthCurrentControl); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_iq_out =
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
          * rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl;

        /* 'ControllerParameter:5' FOC_out_new.Ki_id_out = single(PMSM_config.R_ph_Ohm * bandwidthCurrentControl); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_id_out =
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.R_ph_Ohm
          * rtElectricalID_6ph_codegen_DW->bandwidthCurrentControl;

        /* 'ControllerParameter:6' FOC_out_new.Ki_iq_out = single(FOC_out_new.Ki_id_out); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_iq_out =
          rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_id_out;

        /* 'ControllerParameter:7' FOC_out_new.Kp_n_out = single(FOC_out_new.Ki_iq_out/(PMSM_config.Lq_Henry*damping*PMSM_config.polePairs*3.0/2.0*psiOverJ)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_iq_out;
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Kp_n_out =
          rtElectricalID_6ph_codegen_DW->lambda_l /
          (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
           * rtElectricalID_6ph_codegen_DW->dampingFactor *
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs
           * 3.0F / 2.0F * rtElectricalID_6ph_codegen_DW->psiOverJ);

        /* 'ControllerParameter:8' FOC_out_new.Ki_n_out = single((FOC_out_new.Ki_iq_out)^2 / ((PMSM_config.Lq_Henry)^2 * damping^3 * PMSM_config.polePairs*3.0/2.0*psiOverJ)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_iq_out;
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.Ki_n_out =
          rtElectricalID_6ph_codegen_DW->lambda_l *
          rtElectricalID_6ph_codegen_DW->lambda_l /
          (rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
           * rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.Lq_Henry
           * powf(rtElectricalID_6ph_codegen_DW->dampingFactor, 3.0F) *
           rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.polePairs
           * 3.0F / 2.0F * rtElectricalID_6ph_codegen_DW->psiOverJ);
      }
      break;

     case IN_Subchart_Step_Response5:
      /* During 'Subchart_Step_Response5': '<S1>:1025' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S7>:40' */
        /* '<S7>:61:1' sf_internal_predicateOutput = counter == 3*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 3ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        if (rtElectricalID_6ph_codegen_DW->counter_e == (uint32_T)
            rtElectricalID_6ph_codegen_DW->u) {
          /* Transition: '<S7>:61' */
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
            IN_NO_ACTIVE_CHILD;
          rtElectricalID_6ph_codegen_DW->exitPortIndex_fb = 2U;
        } else {
          /* '<S7>:40:7' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter_e + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter_e + 1U <
              rtElectricalID_6ph_codegen_DW->counter_e) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter_e =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        }

        /* During 'stepResponse': '<S7>:35' */
        /* '<S7>:32:1' sf_internal_predicateOutput = counter == 1026; */
      } else if (rtElectricalID_6ph_codegen_DW->counter_e == 1026U) {
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
        rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S7>:40' */
        rtElectricalID_6ph_codegen_DW->e_d = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_iu[3] = 0.0F;
        n_iters_hn = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_l = 0.01F;
        updateJ_ok = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_f[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_lb[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J[0], 0, sizeof(real32_T) << 12U);

        /* '<S7>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_e = 1U;

        /* '<S7>:40:4' LM_algorithm; */
        LM_algorithm_h(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_m, &n_iters_hn,
                       &updateJ_ok, &rtElectricalID_6ph_codegen_DW->lambda_l,
                       &rtElectricalID_6ph_codegen_DW->e_d,
                       rtElectricalID_6ph_codegen_DW->H_iu,
                       rtElectricalID_6ph_codegen_DW->i_est_lb,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S7>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* '<S7>:35:8' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph); */
        Subch_btw5m_MeasureStepRespon_m
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.q,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.q,
           rtElectricalID_6ph_codegen_DW);

        /* '<S7>:35:9' counter = counter +1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter_e + /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter_e + 1U <
            rtElectricalID_6ph_codegen_DW->counter_e) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        rtElectricalID_6ph_codegen_DW->counter_e =
          rtElectricalID_6ph_codegen_DW->exitPortIndex;
      }

      rtElectricalID_6ph_codegen_DW->exitPortIndex =
        rtElectricalID_6ph_codegen_DW->exitPortIndex_fb;
      rtElectricalID_6ph_codegen_DW->exitPortIndex_fb = 0U;
      if (rtElectricalID_6ph_codegen_DW->exitPortIndex == 2U) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1030' */
        /* '<S1>:1030:1' ElectricalID_output.inductances_6ph.q=L_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q =
          rtElectricalID_6ph_codegen_DW->L_est_m;

        /* '<S1>:1030:2' ElectricalID_output.resistances_6ph.q=R_est; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q =
          rtElectricalID_6ph_codegen_DW->R_est_c;

        /* Exit Internal: Subchart_Step_Response_6ph */
        switch (rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
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
          rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response;
        rtElectricalID_6ph_codegen_DW->counter_b = 1U;
        rtElectricalID_6ph_codegen_DW->z_b = 1U;
        rtElectricalID_6ph_codegen_DW->V0_n4 = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_bf[0], 0,
               sizeof(real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[0], 0,
               sizeof(real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S2>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_g[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S2>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* set DutyCycles */
      }
      break;

     case IN_alignRotor_d_off:
      /* During 'alignRotor_d_off': '<S1>:53' */
      /* '<S1>:411:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Merge: '<S1>/ Merge ' */
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* Merge: '<S1>/ Merge ' */
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

     case IN_extendedOffsetEstimation:
      /* During 'extendedOffsetEstimation': '<S1>:1117' */
      /* '<S1>:1122:1' sf_internal_predicateOutput = extended_offset_estimation.finished_flag; */
      if (BusConversion_InsertedFor_Ele_b->finished_flag) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1122' */
        /* Exit 'extendedOffsetEstimation': '<S1>:1117' */
        /* '<S1>:1117:10' ElectricalID_output.thetaOffset = extended_offset_estimation.offset_angle_rad; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
          BusConversion_InsertedFor_Ele_b->offset_angle_rad;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitState;
        enter_atomic_waitState(rtElectricalID_6ph_codegen_U,
          rtElectricalID_6ph_codegen_Y, rtElectricalID_6ph_codegen_DW);
      } else {
        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:1117:7' ElectricalID_output.thetaOffset = extended_offset_estimation.offset_angle_rad; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
          BusConversion_InsertedFor_Ele_b->offset_angle_rad;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* '<S1>:1117:8' ElectricalID_FOC_output.i_dq_ref=extended_offset_estimation.i_dq_ref; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_dq_ref =
          BusConversion_InsertedFor_Ele_b->i_dq_ref;
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

     case IN_initSetpointsExtendedOffsetE:
      /* During 'initSetpointsExtendedOffsetEstimation': '<S1>:1123' */
      /* '<S1>:1124:1' sf_internal_predicateOutput = counter == 3; */
      if (rtElectricalID_6ph_codegen_DW->counter == 3U) {
        /* Transition: '<S1>:1124' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_extendedOffsetEstimation;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'extendedOffsetEstimation': '<S1>:1117' */
        /* '<S1>:1117:3' ElectricalID_FOC_output.enableFOC_current = boolean(1); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_current =
          true;

        /* '<S1>:1117:4' ElectricalID_FOC_output.activeState = uint16(166); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 166U;

        /* '<S1>:1117:5' ElectricalID_FOC_output.resetIntegrator = boolean(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
          false;
      } else {
        /* '<S1>:1123:6' counter = counter + 1; */
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
      rotorInertiaEstimation(rtElectricalID_6ph_codegen_U,
        rtElectricalID_6ph_codegen_Y, rtElectricalID_6ph_codegen_DW);
      break;

     case IN_stop:
      /* During 'stop': '<S1>:361' */
      /* '<S1>:362:1' sf_internal_predicateOutput = abs(ActualValues.omega_m) <= single(0.5); */
      if (fabsf(rtElectricalID_6ph_codegen_U->ActualValues.omega_m) <= 0.5F) {
        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Transition: '<S1>:362' */
        /* Exit 'stop': '<S1>:361' */
        /* '<S1>:361:6' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
        /* '<S1>:361:7' ElectricalID_FOC_output.enableFOC_speed = boolean(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.enableFOC_speed =
          false;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_rotorInertiaEstimation;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'rotorInertiaEstimation': '<S1>:337' */
        /* '<S1>:337:3' ElectricalID_FOC_output.PI_subsystem = 0x0001; */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.PI_subsystem = 1U;

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

        /* '<S1>:337:8' wait_count = 5*one_sec_transition_counter; */
        rtElectricalID_6ph_codegen_DW->u = 5ULL *
          rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k;
        if (rtElectricalID_6ph_codegen_DW->u > 4294967295ULL) {
          rtElectricalID_6ph_codegen_DW->u = 4294967295ULL;
        }

        rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)
          rtElectricalID_6ph_codegen_DW->u;
      }
      break;

     case IN_waitFree:
      /* During 'waitFree': '<S1>:1112' */
      /* '<S1>:1113:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1 && abs(ActualValues.omega_m) <= single(0.5); */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        updateJ_ok = (fabsf(rtElectricalID_6ph_codegen_U->ActualValues.omega_m) <=
                      0.5F);
      } else {
        updateJ_ok = false;
      }

      if (updateJ_ok) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1113' */
        /* Exit 'waitFree': '<S1>:1112' */
        /* '<S1>:1112:5' ElectricalID_output.enable_TriState = boolean([0 0 0]); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] =
          false;
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
          false;
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
          false;

        /* '<S1>:1112:6' ElectricalID_output.enable_TriState_set_2 = boolean([0 0 0]); */
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[0] = false;
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[1] = false;
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[2] = false;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_stop;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stop': '<S1>:361' */
        /* state 10.1 */
        /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(161); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 161U;

        /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;
      }
      break;

     case IN_waitLock:
      /* During 'waitLock': '<S1>:1021' */
      /* '<S1>:1078:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1 && ElectricalIDConfig.identLq==1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT &&
          rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
        /* Transition: '<S1>:1078' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response5;
        rtElectricalID_6ph_codegen_DW->counter_e = 1U;
        rtElectricalID_6ph_codegen_DW->z = 1U;
        rtElectricalID_6ph_codegen_DW->V0 = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array[0], 0, sizeof
               (real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array[0], 0, sizeof
               (real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response5' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S7>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_a[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S7>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response5' */
        /* set DutyCycles */

        /* '<S1>:1079:1' sf_internal_predicateOutput = ElectricalIDConfig.identLq== 0; */
      } else if (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
        /* Transition: '<S1>:1079' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID =
          IN_Subchart_Step_Response;
        rtElectricalID_6ph_codegen_DW->counter_b = 1U;
        rtElectricalID_6ph_codegen_DW->z_b = 1U;
        rtElectricalID_6ph_codegen_DW->V0_n4 = 0.0F;
        memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_bf[0], 0,
               sizeof(real32_T) << 10U);
        memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[0], 0,
               sizeof(real32_T) << 10U);

        /* Chart: '<S1>/ElectricalID.Subchart_Step_Response' incorporates:
         *  Merge: '<S1>/ Merge '
         *  Outport: '<Root>/ElectricalID_FOC_output'
         */
        /* Entry: Subchart_Step_Response_6ph */
        /* Entry Internal: Subchart_Step_Response_6ph */
        /* Transition: '<S2>:31' */
        rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_c = 0;
               rtElectricalID_6ph_codegen_DW->i_c < 6;
               rtElectricalID_6ph_codegen_DW->i_c++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_g[6 *
              rtElectricalID_6ph_codegen_DW->i_c +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_c];
          }
        }

        /* setpoints in abc */
        /* '<S2>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_d =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_l =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->e_d + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->lambda_l < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->lambda_l > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->lambda_l;
        }

        /* set DutyCycles */
      }
      break;

     case IN_waitSetRPM:
      /* Inport: '<Root>/GlobalConfig' incorporates:
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

      /* End of Inport: '<Root>/GlobalConfig' */
      break;

     default:
      /* During 'waitState': '<S1>:428' */
      /* '<S1>:905:1' sf_internal_predicateOutput = one_sec_transition_counter == counter; */
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k ==
          rtElectricalID_6ph_codegen_DW->counter) {
        /* Transition: '<S1>:905' */
        /* Exit 'waitState': '<S1>:428' */
        /* '<S1>:428:19' finishedElectricalID=boolean(1); */
        rtElectricalID_6ph_codegen_Y->finishedElectricalID = true;

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
      }
      break;
    }
  }
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
                 &rtElectricalID_6ph_codegen_U->extended_offset_estimation,
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
      -0.866025388F, -2.22044605E-16F, 3.85754713E-16F, 0.866025388F,
      -0.866025388F, 0.5F, 0.5F, -1.0F, 1.0F, -0.5F, -0.5F, -0.866025388F,
      0.866025388F, -8.8817842E-16F, -1.4891339E-15F, -0.866025388F,
      0.866025388F, 0.5F, 0.5F, -1.0F, 1.0F, 1.0F, 1.0F, 2.77555756E-16F,
      -7.77156117E-16F, 1.11022302E-15F, -5.5228814E-16F, -1.88737914E-15F,
      -1.22124533E-15F, 1.0F, 1.0F, 1.0F };

    /* SystemInitialize for Chart: '<Root>/ElectricalID_6ph_codegen' */
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_a[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_s6Q2IjU7ERsgdlZtleoGHQF_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_e = 1U;
    rtElectricalID_6ph_codegen_DW->z = 1U;
    rtElectricalID_6ph_codegen_DW->V0 = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->d_f[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_g[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_sJhqcuUy01z8ktZsP9n9gKB_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_b = 1U;
    rtElectricalID_6ph_codegen_DW->z_b = 1U;
    rtElectricalID_6ph_codegen_DW->V0_n4 = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_bf[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_c[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->d_e[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_i[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_f[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_s0mCk6LLDO0ZI0TefUTRfPE_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_n = 1U;
    rtElectricalID_6ph_codegen_DW->z_f = 1U;
    rtElectricalID_6ph_codegen_DW->V0_al = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_j[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_m[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->d_h[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_p[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_n[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_sP9SJ8tIvBr3MqXT5SPmpqC_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_j = 1U;
    rtElectricalID_6ph_codegen_DW->z_a = 1U;
    rtElectricalID_6ph_codegen_DW->V0_a = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_b[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_a[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->d_p[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_bk[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_o[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_sL6lRn6czalxpmpwmGjRinB_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_l = 1U;
    rtElectricalID_6ph_codegen_DW->z_n = 1U;
    rtElectricalID_6ph_codegen_DW->V0_n = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_k[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_e[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->d_n[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_b[0], 0, sizeof(real32_T) << 12U);
    memcpy(&rtElectricalID_6ph_codegen_DW->inv_VSD_l[0], &b[0], 36U * sizeof
           (real32_T));
    rtElectricalID_6ph_codegen_DW->is_c14_srbc3le2abCiUkjBJl1nFUF_ =
      IN_NO_ACTIVE_CHILD;
    rtElectricalID_6ph_codegen_DW->counter_o = 1U;
    rtElectricalID_6ph_codegen_DW->z_p = 1U;
    rtElectricalID_6ph_codegen_DW->V0_k = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->current_meas_array_m[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array_p[0], 0, sizeof
           (real32_T) << 10U);
    memset(&rtElectricalID_6ph_codegen_DW->d_l[0], 0, sizeof(real32_T) << 11U);
    memset(&rtElectricalID_6ph_codegen_DW->J_k[0], 0, sizeof(real32_T) << 12U);
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
    rtElectricalID_6ph_codegen_DW->one_sec_transition_counter_k = 0U;
    rtElectricalID_6ph_codegen_DW->ref_amplitude = 0.0F;
    memset(&rtElectricalID_6ph_codegen_DW->measArray1[0], 0, sizeof(real32_T) <<
           10U);
    memset(&rtElectricalID_6ph_codegen_DW->i_est[0], 0, sizeof(real32_T) << 11U);
    rtElectricalID_6ph_codegen_DW->R_est_c = 0.0F;
    rtElectricalID_6ph_codegen_DW->L_est_m = 0.0F;
    rtElectricalID_6ph_codegen_DW->DC_valid = false;
    rtElectricalID_6ph_codegen_DW->wait_count = 0U;
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
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_xy_ref.d = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_xy_ref.q = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_xy_ref.zero = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_zero_ref.d = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_zero_ref.q = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.i_zero_ref.zero = 0.0F;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resonant_subsystem =
      0U;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.PI_subsystem = 0U;
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.setpoint_filter = 0U;
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