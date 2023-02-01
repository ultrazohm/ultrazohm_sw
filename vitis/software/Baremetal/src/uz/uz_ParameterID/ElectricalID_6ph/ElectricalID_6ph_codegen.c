/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.c
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 3.21
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Feb  1 14:02:28 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
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
#define IN_alignRotor_d_on             ((uint8_T)8U)
#define IN_endState                    ((uint8_T)9U)
#define IN_findDutyCycle               ((uint8_T)10U)
#define IN_measure_psiPM               ((uint8_T)11U)
#define IN_rotorInertiaEstimation      ((uint8_T)12U)
#define IN_stop                        ((uint8_T)13U)
#define IN_waitAccept                  ((uint8_T)14U)
#define IN_waitLock                    ((uint8_T)15U)
#define IN_waitSetRPM                  ((uint8_T)16U)
#define IN_waitState                   ((uint8_T)17U)
#define NumBitsPerChar                 8U

extern real32_T rt_hypotf_snf(real32_T u0, real32_T u1);
extern real32_T rt_atan2f_snf(real32_T u0, real32_T u1);

/* Forward declaration for local functions */
static void initParams(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void reset_FOC_output(ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y);
static void Subchart_St_MeasureStepRespon_n(real32_T v_dq_d, real32_T i_dq_d,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm(const uz_ParaID_GlobalConfig_t *GlobalConfig, real32_T *
  R_est, real32_T *L_est, boolean_T *updateJ_n, real32_T *lambda_nm, real32_T
  *e_o, const uint16_T *n_iters_a, real32_T H_a[4], real32_T i_est_l[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart__b_MeasureStepRespon_g(real32_T v_dq_x, real32_T i_dq_x,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_m(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_m, real32_T *lambda_f,
  real32_T *e_e, const uint16_T *n_iters_o, real32_T H_h[4], real32_T i_est_k
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchart_bt_MeasureStepRespon_p(real32_T v_dq_y, real32_T i_dq_y,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_j(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_o, real32_T *lambda_g,
  real32_T *e_f, const uint16_T *n_iters_f, real32_T H_c[4], real32_T i_est_a1
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subchar_btw_MeasureStepRespon_k(real32_T v_dq_z1, real32_T i_dq_z1,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_a(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_h, real32_T *lambda_n,
  real32_T *e_k, const uint16_T *n_iters_e, real32_T H_j[4], real32_T i_est_m
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subcha_btw5_MeasureStepRespon_g(real32_T v_dq_z2, real32_T i_dq_z2,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_ak(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_k, real32_T *lambda_j,
  real32_T *e_m, const uint16_T *n_iters_j, real32_T H_e[4], real32_T i_est_e
  [2048], DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void Subch_btw5m_MeasureStepRespon_e(real32_T v_dq_q, real32_T i_dq_q,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void LM_algorithm_i(const uz_ParaID_GlobalConfig_t *GlobalConfig,
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ, real32_T *lambda,
  real32_T *e, const uint16_T *n_iters, real32_T H[4], real32_T i_est_a[2048],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void DutyCycle_mod(real32_T ia_reg_in, ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void FFTImplementationCallback_r2br_(const creal32_T x[16384], const
  real32_T costab[8192], const real32_T sintab[8192], creal32_T y[16384],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void FFTImplementationCallback_doHal(const real32_T x[10000], int32_T
  xoffInit, creal32_T y[10000], const creal32_T wwc[9999], const real32_T
  costab[16385], const real32_T sintab[16385], const real32_T costabinv[16385],
  const real32_T sintabinv[16385], DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void FFTRecordedVoltage(internal_psi_analysis *input, const real32_T
  data[10000], real32_T sampletime, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void FindPsiPMs(const internal_psi_analysis *input, internal_psi_analysis
  *output);
static void PsiCompensation(const internal_psi_analysis *input, real32_T
  R_series, real32_T R_parallel, real32_T C, internal_psi_analysis *output);
static real32_T SinusGenerator(real32_T Amp, real32_T Freq, real32_T sampleTime,
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW);
static void goertzel(ExtU_ElectricalID_6ph_codegen_t
                     *rtElectricalID_6ph_codegen_U,
                     DW_ElectricalID_6ph_codegen_t
                     *rtElectricalID_6ph_codegen_DW);
static void waitSetRPM(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void exit_internal_ElectricalID(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static void ElectricalID(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

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
  /* '<S1>:88:93' dampingFactor           = single(10.0); */
  rtElectricalID_6ph_codegen_DW->dampingFactor = 10.0F;

  /* '<S1>:88:94' psiOverJ                = single(5000); */
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
 * function MeasureStepResponse(v_dq,i_dq,voltage_correction)
 */
static void Subchart_St_MeasureStepRespon_n(real32_T v_dq_d, real32_T i_dq_d,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T voltage;

  /* MATLAB Function 'Subchart_St_MeasureStepResponse': '<S2>:39' */
  /* '<S2>:39:2' fns = fieldnames(i_dq); */
  /* '<S2>:39:3' current = i_dq.(fns{index}); */
  /* '<S2>:39:4' voltage = v_dq.(fns{index})*voltage_correction; */
  voltage = v_dq_d * voltage_correction;

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

        rtElectricalID_6ph_codegen_DW->Vstep_k[(int32_T)qY - 1] = voltage;

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
      rtElectricalID_6ph_codegen_DW->Vstep_k[0] = voltage;

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

    rtElectricalID_6ph_codegen_DW->Vstep_k[(int32_T)qY - 1] = voltage;

    /* '<S2>:39:20' V0 = mean(Vstep); */
    voltage = rtElectricalID_6ph_codegen_DW->Vstep_k[0];
    for (k = 0; k < 204; k++) {
      voltage += rtElectricalID_6ph_codegen_DW->Vstep_k[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_a = voltage / 205.0F;

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
  R_est, real32_T *L_est, boolean_T *updateJ_n, real32_T *lambda_nm, real32_T
  *e_o, const uint16_T *n_iters_a, real32_T H_a[4], real32_T i_est_l[2048],
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
  for (it = 0; it < *n_iters_a; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S2>:36:26' if updateJ == 1 */
    if (*updateJ_n) {
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
        rtElectricalID_6ph_codegen_DW->J_a[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_a) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_a *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_a[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_a *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S2>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_l[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_a / *R_est);
        rtElectricalID_6ph_codegen_DW->d_k5[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_a4[k] - i_est_l[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S2>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_a[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_a[tmp] += rtElectricalID_6ph_codegen_DW->J_a[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_a[(i << 11) + i_0];
          }
        }
      }

      /* '<S2>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S2>:36:44' e = dot(d,d); */
        *e_o = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_o += rtElectricalID_6ph_codegen_DW->d_k5[k] *
            rtElectricalID_6ph_codegen_DW->d_k5[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S2>:36:49' H(1,1) = H(1,1) + lambda; */
    H_a[0] += *lambda_nm;

    /* '<S2>:36:50' H(2,2)=H(2,2)+lambda; */
    H_a[3] += *lambda_nm;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S2>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_a[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_k5[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_a[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_k5[k];
    }

    if (fabsf(H_a[1]) > fabsf(H_a[0])) {
      r = H_a[0] / H_a[1];
      t = 1.0F / (r * H_a[3] - H_a[2]);
      b_y_idx_0 = H_a[3] / H_a[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_a[2] / H_a[1] * t;
      t *= r;
    } else {
      r = H_a[1] / H_a[0];
      t = 1.0F / (H_a[3] - r * H_a[2]);
      b_y_idx_0 = H_a[3] / H_a[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_a[2] / H_a[0] * t;
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
      i_est_l[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_a / r);
      rtElectricalID_6ph_codegen_DW->d_k5[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_a4[k] - i_est_l[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_k5[k] *
        rtElectricalID_6ph_codegen_DW->d_k5[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S2>:36:66' if e_lm < e */
    if (e_lm < *e_o) {
      /* '<S2>:36:67' lambda = lambda/10; */
      *lambda_nm /= 10.0F;

      /* '<S2>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S2>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S2>:36:70' e = e_lm; */
      *e_o = e_lm;

      /* '<S2>:36:71' updateJ = boolean(1); */
      *updateJ_n = true;
    } else {
      /* '<S2>:36:72' else */
      /* '<S2>:36:73' updateJ = boolean(0); */
      *updateJ_n = false;

      /* '<S2>:36:74' lambda = lambda*10; */
      *lambda_nm *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response1'
 * function MeasureStepResponse(v_dq,i_dq,voltage_correction)
 */
static void Subchart__b_MeasureStepRespon_g(real32_T v_dq_x, real32_T i_dq_x,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T voltage;

  /* MATLAB Function 'Subchart__b_MeasureStepResponse': '<S3>:39' */
  /* '<S3>:39:2' fns = fieldnames(i_dq); */
  /* '<S3>:39:3' current = i_dq.(fns{index}); */
  /* '<S3>:39:4' voltage = v_dq.(fns{index})*voltage_correction; */
  voltage = v_dq_x * voltage_correction;

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

        rtElectricalID_6ph_codegen_DW->Vstep_e[(int32_T)qY - 1] = voltage;

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
      rtElectricalID_6ph_codegen_DW->Vstep_e[0] = voltage;

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

    rtElectricalID_6ph_codegen_DW->Vstep_e[(int32_T)qY - 1] = voltage;

    /* '<S3>:39:20' V0 = mean(Vstep); */
    voltage = rtElectricalID_6ph_codegen_DW->Vstep_e[0];
    for (k = 0; k < 204; k++) {
      voltage += rtElectricalID_6ph_codegen_DW->Vstep_e[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_nx = voltage / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_m, real32_T *lambda_f,
  real32_T *e_e, const uint16_T *n_iters_o, real32_T H_h[4], real32_T i_est_k
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
  for (it = 0; it < *n_iters_o; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S3>:36:26' if updateJ == 1 */
    if (*updateJ_m) {
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
        rtElectricalID_6ph_codegen_DW->J_g[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_nx) / (*R_est * *R_est) -
          (((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_nx *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_g[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_nx *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S3>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_k[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_nx / *R_est);
        rtElectricalID_6ph_codegen_DW->d_cl[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_a[k] - i_est_k[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S3>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_h[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_h[tmp] += rtElectricalID_6ph_codegen_DW->J_g[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_g[(i << 11) + i_0];
          }
        }
      }

      /* '<S3>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S3>:36:44' e = dot(d,d); */
        *e_e = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_e += rtElectricalID_6ph_codegen_DW->d_cl[k] *
            rtElectricalID_6ph_codegen_DW->d_cl[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S3>:36:49' H(1,1) = H(1,1) + lambda; */
    H_h[0] += *lambda_f;

    /* '<S3>:36:50' H(2,2)=H(2,2)+lambda; */
    H_h[3] += *lambda_f;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S3>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_g[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_cl[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_g[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_cl[k];
    }

    if (fabsf(H_h[1]) > fabsf(H_h[0])) {
      r = H_h[0] / H_h[1];
      t = 1.0F / (r * H_h[3] - H_h[2]);
      b_y_idx_0 = H_h[3] / H_h[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_h[2] / H_h[1] * t;
      t *= r;
    } else {
      r = H_h[1] / H_h[0];
      t = 1.0F / (H_h[3] - r * H_h[2]);
      b_y_idx_0 = H_h[3] / H_h[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_h[2] / H_h[0] * t;
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
      i_est_k[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_nx / r);
      rtElectricalID_6ph_codegen_DW->d_cl[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_a[k] - i_est_k[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_cl[k] *
        rtElectricalID_6ph_codegen_DW->d_cl[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S3>:36:66' if e_lm < e */
    if (e_lm < *e_e) {
      /* '<S3>:36:67' lambda = lambda/10; */
      *lambda_f /= 10.0F;

      /* '<S3>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S3>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S3>:36:70' e = e_lm; */
      *e_e = e_lm;

      /* '<S3>:36:71' updateJ = boolean(1); */
      *updateJ_m = true;
    } else {
      /* '<S3>:36:72' else */
      /* '<S3>:36:73' updateJ = boolean(0); */
      *updateJ_m = false;

      /* '<S3>:36:74' lambda = lambda*10; */
      *lambda_f *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response2'
 * function MeasureStepResponse(v_dq,i_dq,voltage_correction)
 */
static void Subchart_bt_MeasureStepRespon_p(real32_T v_dq_y, real32_T i_dq_y,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T voltage;

  /* MATLAB Function 'Subchart_bt_MeasureStepResponse': '<S4>:39' */
  /* '<S4>:39:2' fns = fieldnames(i_dq); */
  /* '<S4>:39:3' current = i_dq.(fns{index}); */
  /* '<S4>:39:4' voltage = v_dq.(fns{index})*voltage_correction; */
  voltage = v_dq_y * voltage_correction;

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

        rtElectricalID_6ph_codegen_DW->Vstep_gw[(int32_T)qY - 1] = voltage;

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
      rtElectricalID_6ph_codegen_DW->Vstep_gw[0] = voltage;

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

    rtElectricalID_6ph_codegen_DW->Vstep_gw[(int32_T)qY - 1] = voltage;

    /* '<S4>:39:20' V0 = mean(Vstep); */
    voltage = rtElectricalID_6ph_codegen_DW->Vstep_gw[0];
    for (k = 0; k < 204; k++) {
      voltage += rtElectricalID_6ph_codegen_DW->Vstep_gw[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_n = voltage / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_o, real32_T *lambda_g,
  real32_T *e_f, const uint16_T *n_iters_f, real32_T H_c[4], real32_T i_est_a1
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
  for (it = 0; it < *n_iters_f; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S4>:36:26' if updateJ == 1 */
    if (*updateJ_o) {
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
        rtElectricalID_6ph_codegen_DW->J_p[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_n) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_p[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_n *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S4>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_a1[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_n / *R_est);
        rtElectricalID_6ph_codegen_DW->d_k[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_n[k] - i_est_a1[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S4>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_c[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_c[tmp] += rtElectricalID_6ph_codegen_DW->J_p[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_p[(i << 11) + i_0];
          }
        }
      }

      /* '<S4>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S4>:36:44' e = dot(d,d); */
        *e_f = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_f += rtElectricalID_6ph_codegen_DW->d_k[k] *
            rtElectricalID_6ph_codegen_DW->d_k[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S4>:36:49' H(1,1) = H(1,1) + lambda; */
    H_c[0] += *lambda_g;

    /* '<S4>:36:50' H(2,2)=H(2,2)+lambda; */
    H_c[3] += *lambda_g;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S4>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_p[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_k[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_p[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_k[k];
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
      i_est_a1[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_n / r);
      rtElectricalID_6ph_codegen_DW->d_k[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_n[k] - i_est_a1[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_k[k] *
        rtElectricalID_6ph_codegen_DW->d_k[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S4>:36:66' if e_lm < e */
    if (e_lm < *e_f) {
      /* '<S4>:36:67' lambda = lambda/10; */
      *lambda_g /= 10.0F;

      /* '<S4>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S4>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S4>:36:70' e = e_lm; */
      *e_f = e_lm;

      /* '<S4>:36:71' updateJ = boolean(1); */
      *updateJ_o = true;
    } else {
      /* '<S4>:36:72' else */
      /* '<S4>:36:73' updateJ = boolean(0); */
      *updateJ_o = false;

      /* '<S4>:36:74' lambda = lambda*10; */
      *lambda_g *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response3'
 * function MeasureStepResponse(v_dq,i_dq,voltage_correction)
 */
static void Subchar_btw_MeasureStepRespon_k(real32_T v_dq_z1, real32_T i_dq_z1,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T voltage;

  /* MATLAB Function 'Subchar_btw_MeasureStepResponse': '<S5>:39' */
  /* '<S5>:39:2' fns = fieldnames(i_dq); */
  /* '<S5>:39:3' current = i_dq.(fns{index}); */
  /* '<S5>:39:4' voltage = v_dq.(fns{index})*voltage_correction; */
  voltage = v_dq_z1 * voltage_correction;

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

        rtElectricalID_6ph_codegen_DW->Vstep_j[(int32_T)qY - 1] = voltage;

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
      rtElectricalID_6ph_codegen_DW->Vstep_j[0] = voltage;

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

    rtElectricalID_6ph_codegen_DW->Vstep_j[(int32_T)qY - 1] = voltage;

    /* '<S5>:39:20' V0 = mean(Vstep); */
    voltage = rtElectricalID_6ph_codegen_DW->Vstep_j[0];
    for (k = 0; k < 204; k++) {
      voltage += rtElectricalID_6ph_codegen_DW->Vstep_j[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_k = voltage / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_h, real32_T *lambda_n,
  real32_T *e_k, const uint16_T *n_iters_e, real32_T H_j[4], real32_T i_est_m
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
  for (it = 0; it < *n_iters_e; it++) {
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
        rtElectricalID_6ph_codegen_DW->J_i[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_k) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_i[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_k *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S5>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_m[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_k / *R_est);
        rtElectricalID_6ph_codegen_DW->d_f[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_i[k] - i_est_m[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S5>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_j[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_j[tmp] += rtElectricalID_6ph_codegen_DW->J_i[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_i[(i << 11) + i_0];
          }
        }
      }

      /* '<S5>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S5>:36:44' e = dot(d,d); */
        *e_k = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_k += rtElectricalID_6ph_codegen_DW->d_f[k] *
            rtElectricalID_6ph_codegen_DW->d_f[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S5>:36:49' H(1,1) = H(1,1) + lambda; */
    H_j[0] += *lambda_n;

    /* '<S5>:36:50' H(2,2)=H(2,2)+lambda; */
    H_j[3] += *lambda_n;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S5>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_i[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_i[(((k + 1024) / 1024) << 11)
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
        (rtElectricalID_6ph_codegen_DW->V0_k / r);
      rtElectricalID_6ph_codegen_DW->d_f[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_i[k] - i_est_m[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_f[k] *
        rtElectricalID_6ph_codegen_DW->d_f[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S5>:36:66' if e_lm < e */
    if (e_lm < *e_k) {
      /* '<S5>:36:67' lambda = lambda/10; */
      *lambda_n /= 10.0F;

      /* '<S5>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S5>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S5>:36:70' e = e_lm; */
      *e_k = e_lm;

      /* '<S5>:36:71' updateJ = boolean(1); */
      *updateJ_h = true;
    } else {
      /* '<S5>:36:72' else */
      /* '<S5>:36:73' updateJ = boolean(0); */
      *updateJ_h = false;

      /* '<S5>:36:74' lambda = lambda*10; */
      *lambda_n *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response4'
 * function MeasureStepResponse(v_dq,i_dq,voltage_correction)
 */
static void Subcha_btw5_MeasureStepRespon_g(real32_T v_dq_z2, real32_T i_dq_z2,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T voltage;

  /* MATLAB Function 'Subcha_btw5_MeasureStepResponse': '<S6>:39' */
  /* '<S6>:39:2' fns = fieldnames(i_dq); */
  /* '<S6>:39:3' current = i_dq.(fns{index}); */
  /* '<S6>:39:4' voltage = v_dq.(fns{index})*voltage_correction; */
  voltage = v_dq_z2 * voltage_correction;

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

        rtElectricalID_6ph_codegen_DW->Vstep_g[(int32_T)qY - 1] = voltage;

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
      rtElectricalID_6ph_codegen_DW->Vstep_g[0] = voltage;

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

    rtElectricalID_6ph_codegen_DW->Vstep_g[(int32_T)qY - 1] = voltage;

    /* '<S6>:39:20' V0 = mean(Vstep); */
    voltage = rtElectricalID_6ph_codegen_DW->Vstep_g[0];
    for (k = 0; k < 204; k++) {
      voltage += rtElectricalID_6ph_codegen_DW->Vstep_g[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0_g = voltage / 205.0F;

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
  real32_T *R_est, real32_T *L_est, boolean_T *updateJ_k, real32_T *lambda_j,
  real32_T *e_m, const uint16_T *n_iters_j, real32_T H_e[4], real32_T i_est_e
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
  for (it = 0; it < *n_iters_j; it++) {
    real32_T b_y_idx_0;
    real32_T b_y_idx_1;
    real32_T b_y_idx_2;
    real32_T e_lm;
    real32_T r;
    real32_T t;
    real32_T y_idx_1;

    /* '<S6>:36:26' if updateJ == 1 */
    if (*updateJ_k) {
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
        rtElectricalID_6ph_codegen_DW->J_b[k] = -((r - 1.0F) *
          rtElectricalID_6ph_codegen_DW->V0_g) / (*R_est * *R_est) - (((real32_T)
          k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_g *
          GlobalConfig->sampleTimeISR * r / (*L_est * *R_est);
        rtElectricalID_6ph_codegen_DW->J_b[k + 2048] = expf(-((((real32_T)k +
          1.0F) - 1.0F) * *R_est * GlobalConfig->sampleTimeISR) / *L_est) *
          ((((real32_T)k + 1.0F) - 1.0F) * rtElectricalID_6ph_codegen_DW->V0_g *
           GlobalConfig->sampleTimeISR) / (*L_est * *L_est);

        /* . */
        /* '<S6>:36:37' i_est(k) = V0/R_est*(1-exp(-R_est*((k-1)*GlobalConfig.sampleTimeISR)/L_est)); */
        i_est_e[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0_g / *R_est);
        rtElectricalID_6ph_codegen_DW->d_g[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array_j[k] - i_est_e[k];
      }

      /*  Approximierte Hesse-Matrix berechnen */
      /* '<S6>:36:42' H = J(1:1024,:)'*J(1:1024,:); */
      for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
          int32_T tmp;
          tmp = (i << 1) + k;
          H_e[tmp] = 0.0F;
          for (i_0 = 0; i_0 < 1024; i_0++) {
            H_e[tmp] += rtElectricalID_6ph_codegen_DW->J_b[(k << 11) + i_0] *
              rtElectricalID_6ph_codegen_DW->J_b[(i << 11) + i_0];
          }
        }
      }

      /* '<S6>:36:43' if it==1 */
      if (it + 1 == 1) {
        /* '<S6>:36:44' e = dot(d,d); */
        *e_m = 0.0F;
        for (k = 0; k < 2048; k++) {
          *e_m += rtElectricalID_6ph_codegen_DW->d_g[k] *
            rtElectricalID_6ph_codegen_DW->d_g[k];
        }

        /*  Fehlerquadrat berechnen */
      }
    }

    /*  Daempfungsfaktor lambda auf Hesse-Matrix anwenden */
    /* '<S6>:36:49' H(1,1) = H(1,1) + lambda; */
    H_e[0] += *lambda_j;

    /* '<S6>:36:50' H(2,2)=H(2,2)+lambda; */
    H_e[3] += *lambda_j;

    /*  Neue Paramterschaetzung berechnen */
    /* '<S6>:36:53' dp = -inv(H)*(J(1:1024,:)'*d(1:1024)); */
    e_lm = 0.0F;
    y_idx_1 = 0.0F;
    for (k = 0; k < 1024; k++) {
      e_lm += rtElectricalID_6ph_codegen_DW->J_b[((k / 1024) << 11) + k % 1024] *
        rtElectricalID_6ph_codegen_DW->d_g[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J_b[(((k + 1024) / 1024) << 11)
        + (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_g[k];
    }

    if (fabsf(H_e[1]) > fabsf(H_e[0])) {
      r = H_e[0] / H_e[1];
      t = 1.0F / (r * H_e[3] - H_e[2]);
      b_y_idx_0 = H_e[3] / H_e[1] * t;
      b_y_idx_1 = -t;
      b_y_idx_2 = -H_e[2] / H_e[1] * t;
      t *= r;
    } else {
      r = H_e[1] / H_e[0];
      t = 1.0F / (H_e[3] - r * H_e[2]);
      b_y_idx_0 = H_e[3] / H_e[0] * t;
      b_y_idx_1 = -r * t;
      b_y_idx_2 = -H_e[2] / H_e[0] * t;
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
      i_est_e[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0_g / r);
      rtElectricalID_6ph_codegen_DW->d_g[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array_j[k] - i_est_e[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_g[k] *
        rtElectricalID_6ph_codegen_DW->d_g[k];
    }

    /*  Fallunterscheidung ob Fehler groesser oder kleiner geworden ist */
    /* '<S6>:36:66' if e_lm < e */
    if (e_lm < *e_m) {
      /* '<S6>:36:67' lambda = lambda/10; */
      *lambda_j /= 10.0F;

      /* '<S6>:36:68' R_est = R_lm; */
      *R_est = r;

      /* '<S6>:36:69' L_est = L_lm; */
      *L_est = t;

      /* '<S6>:36:70' e = e_lm; */
      *e_m = e_lm;

      /* '<S6>:36:71' updateJ = boolean(1); */
      *updateJ_k = true;
    } else {
      /* '<S6>:36:72' else */
      /* '<S6>:36:73' updateJ = boolean(0); */
      *updateJ_k = false;

      /* '<S6>:36:74' lambda = lambda*10; */
      *lambda_j *= 10.0F;
    }
  }
}

/*
 * Function for Chart: '<S1>/ElectricalID.Subchart_Step_Response5'
 * function MeasureStepResponse(v_dq,i_dq,voltage_correction)
 */
static void Subch_btw5m_MeasureStepRespon_e(real32_T v_dq_q, real32_T i_dq_q,
  real32_T voltage_correction, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T k;
  real32_T voltage;

  /* MATLAB Function 'Subch_btw5m_MeasureStepResponse': '<S7>:39' */
  /* '<S7>:39:2' fns = fieldnames(i_dq); */
  /* '<S7>:39:3' current = i_dq.(fns{index}); */
  /* '<S7>:39:4' voltage = v_dq.(fns{index})*voltage_correction; */
  voltage = v_dq_q * voltage_correction;

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

        rtElectricalID_6ph_codegen_DW->Vstep[(int32_T)qY - 1] = voltage;

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
      rtElectricalID_6ph_codegen_DW->Vstep[0] = voltage;

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

    rtElectricalID_6ph_codegen_DW->Vstep[(int32_T)qY - 1] = voltage;

    /* '<S7>:39:20' V0 = mean(Vstep); */
    voltage = rtElectricalID_6ph_codegen_DW->Vstep[0];
    for (k = 0; k < 204; k++) {
      voltage += rtElectricalID_6ph_codegen_DW->Vstep[k + 1];
    }

    rtElectricalID_6ph_codegen_DW->V0 = voltage / 205.0F;

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
  real32_T *e, const uint16_T *n_iters, real32_T H[4], real32_T i_est_a[2048],
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
        i_est_a[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
          GlobalConfig->sampleTimeISR * -*R_est / *L_est)) *
          (rtElectricalID_6ph_codegen_DW->V0 / *R_est);
        rtElectricalID_6ph_codegen_DW->d_c[k] =
          rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_a[k];
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
          *e += rtElectricalID_6ph_codegen_DW->d_c[k] *
            rtElectricalID_6ph_codegen_DW->d_c[k];
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
        rtElectricalID_6ph_codegen_DW->d_c[k];
      y_idx_1 += rtElectricalID_6ph_codegen_DW->J[(((k + 1024) / 1024) << 11) +
        (k + 1024) % 1024] * rtElectricalID_6ph_codegen_DW->d_c[k];
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
      i_est_a[k] = (1.0F - expf((((real32_T)k + 1.0F) - 1.0F) *
        GlobalConfig->sampleTimeISR * -r / t)) *
        (rtElectricalID_6ph_codegen_DW->V0 / r);
      rtElectricalID_6ph_codegen_DW->d_c[k] =
        rtElectricalID_6ph_codegen_DW->current_meas_array[k] - i_est_a[k];
      e_lm += rtElectricalID_6ph_codegen_DW->d_c[k] *
        rtElectricalID_6ph_codegen_DW->d_c[k];
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
static void FFTImplementationCallback_r2br_(const creal32_T x[16384], const
  real32_T costab[8192], const real32_T sintab[8192], creal32_T y[16384],
  DW_ElectricalID_6ph_codegen_t *rtElectricalID_6ph_codegen_DW)
{
  int32_T b_i;
  int32_T j;
  int32_T ju;
  int32_T k;
  real32_T temp_im;
  real32_T twid_re;
  rtElectricalID_6ph_codegen_DW->iy_m = 0;
  ju = 0;
  for (k = 0; k < 16383; k++) {
    boolean_T tst;
    y[rtElectricalID_6ph_codegen_DW->iy_m] = x[k];
    rtElectricalID_6ph_codegen_DW->iy_m = 16384;
    tst = true;
    while (tst) {
      rtElectricalID_6ph_codegen_DW->iy_m >>= 1;
      ju ^= rtElectricalID_6ph_codegen_DW->iy_m;
      tst = ((ju & rtElectricalID_6ph_codegen_DW->iy_m) == 0);
    }

    rtElectricalID_6ph_codegen_DW->iy_m = ju;
  }

  y[rtElectricalID_6ph_codegen_DW->iy_m] = x[16383];
  for (rtElectricalID_6ph_codegen_DW->ix_g = 0;
       rtElectricalID_6ph_codegen_DW->ix_g <= 16383;
       rtElectricalID_6ph_codegen_DW->ix_g += 2) {
    temp_im = y[rtElectricalID_6ph_codegen_DW->ix_g + 1].re;
    twid_re = y[rtElectricalID_6ph_codegen_DW->ix_g + 1].im;
    y[rtElectricalID_6ph_codegen_DW->ix_g + 1].re =
      y[rtElectricalID_6ph_codegen_DW->ix_g].re - temp_im;
    y[rtElectricalID_6ph_codegen_DW->ix_g + 1].im =
      y[rtElectricalID_6ph_codegen_DW->ix_g].im - twid_re;
    y[rtElectricalID_6ph_codegen_DW->ix_g].re += temp_im;
    y[rtElectricalID_6ph_codegen_DW->ix_g].im += twid_re;
  }

  rtElectricalID_6ph_codegen_DW->ix_g = 2;
  ju = 4;
  k = 4096;
  rtElectricalID_6ph_codegen_DW->iy_m = 16381;
  while (k > 0) {
    int32_T istart;
    int32_T temp_re_tmp;
    real32_T temp_re;
    for (b_i = 0; b_i < rtElectricalID_6ph_codegen_DW->iy_m; b_i += ju) {
      temp_re_tmp = b_i + rtElectricalID_6ph_codegen_DW->ix_g;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[b_i].re - temp_re;
      y[temp_re_tmp].im = y[b_i].im - temp_im;
      y[b_i].re += temp_re;
      y[b_i].im += temp_im;
    }

    istart = 1;
    for (j = k; j < 8192; j += k) {
      int32_T ihi;
      real32_T twid_im;
      twid_re = costab[j];
      twid_im = sintab[j];
      b_i = istart;
      ihi = istart + rtElectricalID_6ph_codegen_DW->iy_m;
      while (b_i < ihi) {
        real32_T temp_re_tmp_0;
        temp_re_tmp = b_i + rtElectricalID_6ph_codegen_DW->ix_g;
        temp_im = y[temp_re_tmp].im;
        temp_re_tmp_0 = y[temp_re_tmp].re;
        temp_re = temp_re_tmp_0 * twid_re - temp_im * twid_im;
        temp_im = temp_im * twid_re + temp_re_tmp_0 * twid_im;
        y[temp_re_tmp].re = y[b_i].re - temp_re;
        y[temp_re_tmp].im = y[b_i].im - temp_im;
        y[b_i].re += temp_re;
        y[b_i].im += temp_im;
        b_i += ju;
      }

      istart++;
    }

    k /= 2;
    rtElectricalID_6ph_codegen_DW->ix_g = ju;
    ju += ju;
    rtElectricalID_6ph_codegen_DW->iy_m -= rtElectricalID_6ph_codegen_DW->ix_g;
  }

  for (rtElectricalID_6ph_codegen_DW->iy_m = 0;
       rtElectricalID_6ph_codegen_DW->iy_m < 16384;
       rtElectricalID_6ph_codegen_DW->iy_m++) {
    rtElectricalID_6ph_codegen_DW->y = y[rtElectricalID_6ph_codegen_DW->iy_m];
    rtElectricalID_6ph_codegen_DW->y.re *= 6.10351562E-5F;
    rtElectricalID_6ph_codegen_DW->y.im *= 6.10351562E-5F;
    y[rtElectricalID_6ph_codegen_DW->iy_m] = rtElectricalID_6ph_codegen_DW->y;
  }
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void FFTImplementationCallback_doHal(const real32_T x[10000], int32_T
  xoffInit, creal32_T y[10000], const creal32_T wwc[9999], const real32_T
  costab[16385], const real32_T sintab[16385], const real32_T costabinv[16385],
  const real32_T sintabinv[16385], DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  boolean_T tst;
  static const int16_T b_0[5000] = { 1, 5000, 4999, 4998, 4997, 4996, 4995, 4994,
    4993, 4992, 4991, 4990, 4989, 4988, 4987, 4986, 4985, 4984, 4983, 4982, 4981,
    4980, 4979, 4978, 4977, 4976, 4975, 4974, 4973, 4972, 4971, 4970, 4969, 4968,
    4967, 4966, 4965, 4964, 4963, 4962, 4961, 4960, 4959, 4958, 4957, 4956, 4955,
    4954, 4953, 4952, 4951, 4950, 4949, 4948, 4947, 4946, 4945, 4944, 4943, 4942,
    4941, 4940, 4939, 4938, 4937, 4936, 4935, 4934, 4933, 4932, 4931, 4930, 4929,
    4928, 4927, 4926, 4925, 4924, 4923, 4922, 4921, 4920, 4919, 4918, 4917, 4916,
    4915, 4914, 4913, 4912, 4911, 4910, 4909, 4908, 4907, 4906, 4905, 4904, 4903,
    4902, 4901, 4900, 4899, 4898, 4897, 4896, 4895, 4894, 4893, 4892, 4891, 4890,
    4889, 4888, 4887, 4886, 4885, 4884, 4883, 4882, 4881, 4880, 4879, 4878, 4877,
    4876, 4875, 4874, 4873, 4872, 4871, 4870, 4869, 4868, 4867, 4866, 4865, 4864,
    4863, 4862, 4861, 4860, 4859, 4858, 4857, 4856, 4855, 4854, 4853, 4852, 4851,
    4850, 4849, 4848, 4847, 4846, 4845, 4844, 4843, 4842, 4841, 4840, 4839, 4838,
    4837, 4836, 4835, 4834, 4833, 4832, 4831, 4830, 4829, 4828, 4827, 4826, 4825,
    4824, 4823, 4822, 4821, 4820, 4819, 4818, 4817, 4816, 4815, 4814, 4813, 4812,
    4811, 4810, 4809, 4808, 4807, 4806, 4805, 4804, 4803, 4802, 4801, 4800, 4799,
    4798, 4797, 4796, 4795, 4794, 4793, 4792, 4791, 4790, 4789, 4788, 4787, 4786,
    4785, 4784, 4783, 4782, 4781, 4780, 4779, 4778, 4777, 4776, 4775, 4774, 4773,
    4772, 4771, 4770, 4769, 4768, 4767, 4766, 4765, 4764, 4763, 4762, 4761, 4760,
    4759, 4758, 4757, 4756, 4755, 4754, 4753, 4752, 4751, 4750, 4749, 4748, 4747,
    4746, 4745, 4744, 4743, 4742, 4741, 4740, 4739, 4738, 4737, 4736, 4735, 4734,
    4733, 4732, 4731, 4730, 4729, 4728, 4727, 4726, 4725, 4724, 4723, 4722, 4721,
    4720, 4719, 4718, 4717, 4716, 4715, 4714, 4713, 4712, 4711, 4710, 4709, 4708,
    4707, 4706, 4705, 4704, 4703, 4702, 4701, 4700, 4699, 4698, 4697, 4696, 4695,
    4694, 4693, 4692, 4691, 4690, 4689, 4688, 4687, 4686, 4685, 4684, 4683, 4682,
    4681, 4680, 4679, 4678, 4677, 4676, 4675, 4674, 4673, 4672, 4671, 4670, 4669,
    4668, 4667, 4666, 4665, 4664, 4663, 4662, 4661, 4660, 4659, 4658, 4657, 4656,
    4655, 4654, 4653, 4652, 4651, 4650, 4649, 4648, 4647, 4646, 4645, 4644, 4643,
    4642, 4641, 4640, 4639, 4638, 4637, 4636, 4635, 4634, 4633, 4632, 4631, 4630,
    4629, 4628, 4627, 4626, 4625, 4624, 4623, 4622, 4621, 4620, 4619, 4618, 4617,
    4616, 4615, 4614, 4613, 4612, 4611, 4610, 4609, 4608, 4607, 4606, 4605, 4604,
    4603, 4602, 4601, 4600, 4599, 4598, 4597, 4596, 4595, 4594, 4593, 4592, 4591,
    4590, 4589, 4588, 4587, 4586, 4585, 4584, 4583, 4582, 4581, 4580, 4579, 4578,
    4577, 4576, 4575, 4574, 4573, 4572, 4571, 4570, 4569, 4568, 4567, 4566, 4565,
    4564, 4563, 4562, 4561, 4560, 4559, 4558, 4557, 4556, 4555, 4554, 4553, 4552,
    4551, 4550, 4549, 4548, 4547, 4546, 4545, 4544, 4543, 4542, 4541, 4540, 4539,
    4538, 4537, 4536, 4535, 4534, 4533, 4532, 4531, 4530, 4529, 4528, 4527, 4526,
    4525, 4524, 4523, 4522, 4521, 4520, 4519, 4518, 4517, 4516, 4515, 4514, 4513,
    4512, 4511, 4510, 4509, 4508, 4507, 4506, 4505, 4504, 4503, 4502, 4501, 4500,
    4499, 4498, 4497, 4496, 4495, 4494, 4493, 4492, 4491, 4490, 4489, 4488, 4487,
    4486, 4485, 4484, 4483, 4482, 4481, 4480, 4479, 4478, 4477, 4476, 4475, 4474,
    4473, 4472, 4471, 4470, 4469, 4468, 4467, 4466, 4465, 4464, 4463, 4462, 4461,
    4460, 4459, 4458, 4457, 4456, 4455, 4454, 4453, 4452, 4451, 4450, 4449, 4448,
    4447, 4446, 4445, 4444, 4443, 4442, 4441, 4440, 4439, 4438, 4437, 4436, 4435,
    4434, 4433, 4432, 4431, 4430, 4429, 4428, 4427, 4426, 4425, 4424, 4423, 4422,
    4421, 4420, 4419, 4418, 4417, 4416, 4415, 4414, 4413, 4412, 4411, 4410, 4409,
    4408, 4407, 4406, 4405, 4404, 4403, 4402, 4401, 4400, 4399, 4398, 4397, 4396,
    4395, 4394, 4393, 4392, 4391, 4390, 4389, 4388, 4387, 4386, 4385, 4384, 4383,
    4382, 4381, 4380, 4379, 4378, 4377, 4376, 4375, 4374, 4373, 4372, 4371, 4370,
    4369, 4368, 4367, 4366, 4365, 4364, 4363, 4362, 4361, 4360, 4359, 4358, 4357,
    4356, 4355, 4354, 4353, 4352, 4351, 4350, 4349, 4348, 4347, 4346, 4345, 4344,
    4343, 4342, 4341, 4340, 4339, 4338, 4337, 4336, 4335, 4334, 4333, 4332, 4331,
    4330, 4329, 4328, 4327, 4326, 4325, 4324, 4323, 4322, 4321, 4320, 4319, 4318,
    4317, 4316, 4315, 4314, 4313, 4312, 4311, 4310, 4309, 4308, 4307, 4306, 4305,
    4304, 4303, 4302, 4301, 4300, 4299, 4298, 4297, 4296, 4295, 4294, 4293, 4292,
    4291, 4290, 4289, 4288, 4287, 4286, 4285, 4284, 4283, 4282, 4281, 4280, 4279,
    4278, 4277, 4276, 4275, 4274, 4273, 4272, 4271, 4270, 4269, 4268, 4267, 4266,
    4265, 4264, 4263, 4262, 4261, 4260, 4259, 4258, 4257, 4256, 4255, 4254, 4253,
    4252, 4251, 4250, 4249, 4248, 4247, 4246, 4245, 4244, 4243, 4242, 4241, 4240,
    4239, 4238, 4237, 4236, 4235, 4234, 4233, 4232, 4231, 4230, 4229, 4228, 4227,
    4226, 4225, 4224, 4223, 4222, 4221, 4220, 4219, 4218, 4217, 4216, 4215, 4214,
    4213, 4212, 4211, 4210, 4209, 4208, 4207, 4206, 4205, 4204, 4203, 4202, 4201,
    4200, 4199, 4198, 4197, 4196, 4195, 4194, 4193, 4192, 4191, 4190, 4189, 4188,
    4187, 4186, 4185, 4184, 4183, 4182, 4181, 4180, 4179, 4178, 4177, 4176, 4175,
    4174, 4173, 4172, 4171, 4170, 4169, 4168, 4167, 4166, 4165, 4164, 4163, 4162,
    4161, 4160, 4159, 4158, 4157, 4156, 4155, 4154, 4153, 4152, 4151, 4150, 4149,
    4148, 4147, 4146, 4145, 4144, 4143, 4142, 4141, 4140, 4139, 4138, 4137, 4136,
    4135, 4134, 4133, 4132, 4131, 4130, 4129, 4128, 4127, 4126, 4125, 4124, 4123,
    4122, 4121, 4120, 4119, 4118, 4117, 4116, 4115, 4114, 4113, 4112, 4111, 4110,
    4109, 4108, 4107, 4106, 4105, 4104, 4103, 4102, 4101, 4100, 4099, 4098, 4097,
    4096, 4095, 4094, 4093, 4092, 4091, 4090, 4089, 4088, 4087, 4086, 4085, 4084,
    4083, 4082, 4081, 4080, 4079, 4078, 4077, 4076, 4075, 4074, 4073, 4072, 4071,
    4070, 4069, 4068, 4067, 4066, 4065, 4064, 4063, 4062, 4061, 4060, 4059, 4058,
    4057, 4056, 4055, 4054, 4053, 4052, 4051, 4050, 4049, 4048, 4047, 4046, 4045,
    4044, 4043, 4042, 4041, 4040, 4039, 4038, 4037, 4036, 4035, 4034, 4033, 4032,
    4031, 4030, 4029, 4028, 4027, 4026, 4025, 4024, 4023, 4022, 4021, 4020, 4019,
    4018, 4017, 4016, 4015, 4014, 4013, 4012, 4011, 4010, 4009, 4008, 4007, 4006,
    4005, 4004, 4003, 4002, 4001, 4000, 3999, 3998, 3997, 3996, 3995, 3994, 3993,
    3992, 3991, 3990, 3989, 3988, 3987, 3986, 3985, 3984, 3983, 3982, 3981, 3980,
    3979, 3978, 3977, 3976, 3975, 3974, 3973, 3972, 3971, 3970, 3969, 3968, 3967,
    3966, 3965, 3964, 3963, 3962, 3961, 3960, 3959, 3958, 3957, 3956, 3955, 3954,
    3953, 3952, 3951, 3950, 3949, 3948, 3947, 3946, 3945, 3944, 3943, 3942, 3941,
    3940, 3939, 3938, 3937, 3936, 3935, 3934, 3933, 3932, 3931, 3930, 3929, 3928,
    3927, 3926, 3925, 3924, 3923, 3922, 3921, 3920, 3919, 3918, 3917, 3916, 3915,
    3914, 3913, 3912, 3911, 3910, 3909, 3908, 3907, 3906, 3905, 3904, 3903, 3902,
    3901, 3900, 3899, 3898, 3897, 3896, 3895, 3894, 3893, 3892, 3891, 3890, 3889,
    3888, 3887, 3886, 3885, 3884, 3883, 3882, 3881, 3880, 3879, 3878, 3877, 3876,
    3875, 3874, 3873, 3872, 3871, 3870, 3869, 3868, 3867, 3866, 3865, 3864, 3863,
    3862, 3861, 3860, 3859, 3858, 3857, 3856, 3855, 3854, 3853, 3852, 3851, 3850,
    3849, 3848, 3847, 3846, 3845, 3844, 3843, 3842, 3841, 3840, 3839, 3838, 3837,
    3836, 3835, 3834, 3833, 3832, 3831, 3830, 3829, 3828, 3827, 3826, 3825, 3824,
    3823, 3822, 3821, 3820, 3819, 3818, 3817, 3816, 3815, 3814, 3813, 3812, 3811,
    3810, 3809, 3808, 3807, 3806, 3805, 3804, 3803, 3802, 3801, 3800, 3799, 3798,
    3797, 3796, 3795, 3794, 3793, 3792, 3791, 3790, 3789, 3788, 3787, 3786, 3785,
    3784, 3783, 3782, 3781, 3780, 3779, 3778, 3777, 3776, 3775, 3774, 3773, 3772,
    3771, 3770, 3769, 3768, 3767, 3766, 3765, 3764, 3763, 3762, 3761, 3760, 3759,
    3758, 3757, 3756, 3755, 3754, 3753, 3752, 3751, 3750, 3749, 3748, 3747, 3746,
    3745, 3744, 3743, 3742, 3741, 3740, 3739, 3738, 3737, 3736, 3735, 3734, 3733,
    3732, 3731, 3730, 3729, 3728, 3727, 3726, 3725, 3724, 3723, 3722, 3721, 3720,
    3719, 3718, 3717, 3716, 3715, 3714, 3713, 3712, 3711, 3710, 3709, 3708, 3707,
    3706, 3705, 3704, 3703, 3702, 3701, 3700, 3699, 3698, 3697, 3696, 3695, 3694,
    3693, 3692, 3691, 3690, 3689, 3688, 3687, 3686, 3685, 3684, 3683, 3682, 3681,
    3680, 3679, 3678, 3677, 3676, 3675, 3674, 3673, 3672, 3671, 3670, 3669, 3668,
    3667, 3666, 3665, 3664, 3663, 3662, 3661, 3660, 3659, 3658, 3657, 3656, 3655,
    3654, 3653, 3652, 3651, 3650, 3649, 3648, 3647, 3646, 3645, 3644, 3643, 3642,
    3641, 3640, 3639, 3638, 3637, 3636, 3635, 3634, 3633, 3632, 3631, 3630, 3629,
    3628, 3627, 3626, 3625, 3624, 3623, 3622, 3621, 3620, 3619, 3618, 3617, 3616,
    3615, 3614, 3613, 3612, 3611, 3610, 3609, 3608, 3607, 3606, 3605, 3604, 3603,
    3602, 3601, 3600, 3599, 3598, 3597, 3596, 3595, 3594, 3593, 3592, 3591, 3590,
    3589, 3588, 3587, 3586, 3585, 3584, 3583, 3582, 3581, 3580, 3579, 3578, 3577,
    3576, 3575, 3574, 3573, 3572, 3571, 3570, 3569, 3568, 3567, 3566, 3565, 3564,
    3563, 3562, 3561, 3560, 3559, 3558, 3557, 3556, 3555, 3554, 3553, 3552, 3551,
    3550, 3549, 3548, 3547, 3546, 3545, 3544, 3543, 3542, 3541, 3540, 3539, 3538,
    3537, 3536, 3535, 3534, 3533, 3532, 3531, 3530, 3529, 3528, 3527, 3526, 3525,
    3524, 3523, 3522, 3521, 3520, 3519, 3518, 3517, 3516, 3515, 3514, 3513, 3512,
    3511, 3510, 3509, 3508, 3507, 3506, 3505, 3504, 3503, 3502, 3501, 3500, 3499,
    3498, 3497, 3496, 3495, 3494, 3493, 3492, 3491, 3490, 3489, 3488, 3487, 3486,
    3485, 3484, 3483, 3482, 3481, 3480, 3479, 3478, 3477, 3476, 3475, 3474, 3473,
    3472, 3471, 3470, 3469, 3468, 3467, 3466, 3465, 3464, 3463, 3462, 3461, 3460,
    3459, 3458, 3457, 3456, 3455, 3454, 3453, 3452, 3451, 3450, 3449, 3448, 3447,
    3446, 3445, 3444, 3443, 3442, 3441, 3440, 3439, 3438, 3437, 3436, 3435, 3434,
    3433, 3432, 3431, 3430, 3429, 3428, 3427, 3426, 3425, 3424, 3423, 3422, 3421,
    3420, 3419, 3418, 3417, 3416, 3415, 3414, 3413, 3412, 3411, 3410, 3409, 3408,
    3407, 3406, 3405, 3404, 3403, 3402, 3401, 3400, 3399, 3398, 3397, 3396, 3395,
    3394, 3393, 3392, 3391, 3390, 3389, 3388, 3387, 3386, 3385, 3384, 3383, 3382,
    3381, 3380, 3379, 3378, 3377, 3376, 3375, 3374, 3373, 3372, 3371, 3370, 3369,
    3368, 3367, 3366, 3365, 3364, 3363, 3362, 3361, 3360, 3359, 3358, 3357, 3356,
    3355, 3354, 3353, 3352, 3351, 3350, 3349, 3348, 3347, 3346, 3345, 3344, 3343,
    3342, 3341, 3340, 3339, 3338, 3337, 3336, 3335, 3334, 3333, 3332, 3331, 3330,
    3329, 3328, 3327, 3326, 3325, 3324, 3323, 3322, 3321, 3320, 3319, 3318, 3317,
    3316, 3315, 3314, 3313, 3312, 3311, 3310, 3309, 3308, 3307, 3306, 3305, 3304,
    3303, 3302, 3301, 3300, 3299, 3298, 3297, 3296, 3295, 3294, 3293, 3292, 3291,
    3290, 3289, 3288, 3287, 3286, 3285, 3284, 3283, 3282, 3281, 3280, 3279, 3278,
    3277, 3276, 3275, 3274, 3273, 3272, 3271, 3270, 3269, 3268, 3267, 3266, 3265,
    3264, 3263, 3262, 3261, 3260, 3259, 3258, 3257, 3256, 3255, 3254, 3253, 3252,
    3251, 3250, 3249, 3248, 3247, 3246, 3245, 3244, 3243, 3242, 3241, 3240, 3239,
    3238, 3237, 3236, 3235, 3234, 3233, 3232, 3231, 3230, 3229, 3228, 3227, 3226,
    3225, 3224, 3223, 3222, 3221, 3220, 3219, 3218, 3217, 3216, 3215, 3214, 3213,
    3212, 3211, 3210, 3209, 3208, 3207, 3206, 3205, 3204, 3203, 3202, 3201, 3200,
    3199, 3198, 3197, 3196, 3195, 3194, 3193, 3192, 3191, 3190, 3189, 3188, 3187,
    3186, 3185, 3184, 3183, 3182, 3181, 3180, 3179, 3178, 3177, 3176, 3175, 3174,
    3173, 3172, 3171, 3170, 3169, 3168, 3167, 3166, 3165, 3164, 3163, 3162, 3161,
    3160, 3159, 3158, 3157, 3156, 3155, 3154, 3153, 3152, 3151, 3150, 3149, 3148,
    3147, 3146, 3145, 3144, 3143, 3142, 3141, 3140, 3139, 3138, 3137, 3136, 3135,
    3134, 3133, 3132, 3131, 3130, 3129, 3128, 3127, 3126, 3125, 3124, 3123, 3122,
    3121, 3120, 3119, 3118, 3117, 3116, 3115, 3114, 3113, 3112, 3111, 3110, 3109,
    3108, 3107, 3106, 3105, 3104, 3103, 3102, 3101, 3100, 3099, 3098, 3097, 3096,
    3095, 3094, 3093, 3092, 3091, 3090, 3089, 3088, 3087, 3086, 3085, 3084, 3083,
    3082, 3081, 3080, 3079, 3078, 3077, 3076, 3075, 3074, 3073, 3072, 3071, 3070,
    3069, 3068, 3067, 3066, 3065, 3064, 3063, 3062, 3061, 3060, 3059, 3058, 3057,
    3056, 3055, 3054, 3053, 3052, 3051, 3050, 3049, 3048, 3047, 3046, 3045, 3044,
    3043, 3042, 3041, 3040, 3039, 3038, 3037, 3036, 3035, 3034, 3033, 3032, 3031,
    3030, 3029, 3028, 3027, 3026, 3025, 3024, 3023, 3022, 3021, 3020, 3019, 3018,
    3017, 3016, 3015, 3014, 3013, 3012, 3011, 3010, 3009, 3008, 3007, 3006, 3005,
    3004, 3003, 3002, 3001, 3000, 2999, 2998, 2997, 2996, 2995, 2994, 2993, 2992,
    2991, 2990, 2989, 2988, 2987, 2986, 2985, 2984, 2983, 2982, 2981, 2980, 2979,
    2978, 2977, 2976, 2975, 2974, 2973, 2972, 2971, 2970, 2969, 2968, 2967, 2966,
    2965, 2964, 2963, 2962, 2961, 2960, 2959, 2958, 2957, 2956, 2955, 2954, 2953,
    2952, 2951, 2950, 2949, 2948, 2947, 2946, 2945, 2944, 2943, 2942, 2941, 2940,
    2939, 2938, 2937, 2936, 2935, 2934, 2933, 2932, 2931, 2930, 2929, 2928, 2927,
    2926, 2925, 2924, 2923, 2922, 2921, 2920, 2919, 2918, 2917, 2916, 2915, 2914,
    2913, 2912, 2911, 2910, 2909, 2908, 2907, 2906, 2905, 2904, 2903, 2902, 2901,
    2900, 2899, 2898, 2897, 2896, 2895, 2894, 2893, 2892, 2891, 2890, 2889, 2888,
    2887, 2886, 2885, 2884, 2883, 2882, 2881, 2880, 2879, 2878, 2877, 2876, 2875,
    2874, 2873, 2872, 2871, 2870, 2869, 2868, 2867, 2866, 2865, 2864, 2863, 2862,
    2861, 2860, 2859, 2858, 2857, 2856, 2855, 2854, 2853, 2852, 2851, 2850, 2849,
    2848, 2847, 2846, 2845, 2844, 2843, 2842, 2841, 2840, 2839, 2838, 2837, 2836,
    2835, 2834, 2833, 2832, 2831, 2830, 2829, 2828, 2827, 2826, 2825, 2824, 2823,
    2822, 2821, 2820, 2819, 2818, 2817, 2816, 2815, 2814, 2813, 2812, 2811, 2810,
    2809, 2808, 2807, 2806, 2805, 2804, 2803, 2802, 2801, 2800, 2799, 2798, 2797,
    2796, 2795, 2794, 2793, 2792, 2791, 2790, 2789, 2788, 2787, 2786, 2785, 2784,
    2783, 2782, 2781, 2780, 2779, 2778, 2777, 2776, 2775, 2774, 2773, 2772, 2771,
    2770, 2769, 2768, 2767, 2766, 2765, 2764, 2763, 2762, 2761, 2760, 2759, 2758,
    2757, 2756, 2755, 2754, 2753, 2752, 2751, 2750, 2749, 2748, 2747, 2746, 2745,
    2744, 2743, 2742, 2741, 2740, 2739, 2738, 2737, 2736, 2735, 2734, 2733, 2732,
    2731, 2730, 2729, 2728, 2727, 2726, 2725, 2724, 2723, 2722, 2721, 2720, 2719,
    2718, 2717, 2716, 2715, 2714, 2713, 2712, 2711, 2710, 2709, 2708, 2707, 2706,
    2705, 2704, 2703, 2702, 2701, 2700, 2699, 2698, 2697, 2696, 2695, 2694, 2693,
    2692, 2691, 2690, 2689, 2688, 2687, 2686, 2685, 2684, 2683, 2682, 2681, 2680,
    2679, 2678, 2677, 2676, 2675, 2674, 2673, 2672, 2671, 2670, 2669, 2668, 2667,
    2666, 2665, 2664, 2663, 2662, 2661, 2660, 2659, 2658, 2657, 2656, 2655, 2654,
    2653, 2652, 2651, 2650, 2649, 2648, 2647, 2646, 2645, 2644, 2643, 2642, 2641,
    2640, 2639, 2638, 2637, 2636, 2635, 2634, 2633, 2632, 2631, 2630, 2629, 2628,
    2627, 2626, 2625, 2624, 2623, 2622, 2621, 2620, 2619, 2618, 2617, 2616, 2615,
    2614, 2613, 2612, 2611, 2610, 2609, 2608, 2607, 2606, 2605, 2604, 2603, 2602,
    2601, 2600, 2599, 2598, 2597, 2596, 2595, 2594, 2593, 2592, 2591, 2590, 2589,
    2588, 2587, 2586, 2585, 2584, 2583, 2582, 2581, 2580, 2579, 2578, 2577, 2576,
    2575, 2574, 2573, 2572, 2571, 2570, 2569, 2568, 2567, 2566, 2565, 2564, 2563,
    2562, 2561, 2560, 2559, 2558, 2557, 2556, 2555, 2554, 2553, 2552, 2551, 2550,
    2549, 2548, 2547, 2546, 2545, 2544, 2543, 2542, 2541, 2540, 2539, 2538, 2537,
    2536, 2535, 2534, 2533, 2532, 2531, 2530, 2529, 2528, 2527, 2526, 2525, 2524,
    2523, 2522, 2521, 2520, 2519, 2518, 2517, 2516, 2515, 2514, 2513, 2512, 2511,
    2510, 2509, 2508, 2507, 2506, 2505, 2504, 2503, 2502, 2501, 2500, 2499, 2498,
    2497, 2496, 2495, 2494, 2493, 2492, 2491, 2490, 2489, 2488, 2487, 2486, 2485,
    2484, 2483, 2482, 2481, 2480, 2479, 2478, 2477, 2476, 2475, 2474, 2473, 2472,
    2471, 2470, 2469, 2468, 2467, 2466, 2465, 2464, 2463, 2462, 2461, 2460, 2459,
    2458, 2457, 2456, 2455, 2454, 2453, 2452, 2451, 2450, 2449, 2448, 2447, 2446,
    2445, 2444, 2443, 2442, 2441, 2440, 2439, 2438, 2437, 2436, 2435, 2434, 2433,
    2432, 2431, 2430, 2429, 2428, 2427, 2426, 2425, 2424, 2423, 2422, 2421, 2420,
    2419, 2418, 2417, 2416, 2415, 2414, 2413, 2412, 2411, 2410, 2409, 2408, 2407,
    2406, 2405, 2404, 2403, 2402, 2401, 2400, 2399, 2398, 2397, 2396, 2395, 2394,
    2393, 2392, 2391, 2390, 2389, 2388, 2387, 2386, 2385, 2384, 2383, 2382, 2381,
    2380, 2379, 2378, 2377, 2376, 2375, 2374, 2373, 2372, 2371, 2370, 2369, 2368,
    2367, 2366, 2365, 2364, 2363, 2362, 2361, 2360, 2359, 2358, 2357, 2356, 2355,
    2354, 2353, 2352, 2351, 2350, 2349, 2348, 2347, 2346, 2345, 2344, 2343, 2342,
    2341, 2340, 2339, 2338, 2337, 2336, 2335, 2334, 2333, 2332, 2331, 2330, 2329,
    2328, 2327, 2326, 2325, 2324, 2323, 2322, 2321, 2320, 2319, 2318, 2317, 2316,
    2315, 2314, 2313, 2312, 2311, 2310, 2309, 2308, 2307, 2306, 2305, 2304, 2303,
    2302, 2301, 2300, 2299, 2298, 2297, 2296, 2295, 2294, 2293, 2292, 2291, 2290,
    2289, 2288, 2287, 2286, 2285, 2284, 2283, 2282, 2281, 2280, 2279, 2278, 2277,
    2276, 2275, 2274, 2273, 2272, 2271, 2270, 2269, 2268, 2267, 2266, 2265, 2264,
    2263, 2262, 2261, 2260, 2259, 2258, 2257, 2256, 2255, 2254, 2253, 2252, 2251,
    2250, 2249, 2248, 2247, 2246, 2245, 2244, 2243, 2242, 2241, 2240, 2239, 2238,
    2237, 2236, 2235, 2234, 2233, 2232, 2231, 2230, 2229, 2228, 2227, 2226, 2225,
    2224, 2223, 2222, 2221, 2220, 2219, 2218, 2217, 2216, 2215, 2214, 2213, 2212,
    2211, 2210, 2209, 2208, 2207, 2206, 2205, 2204, 2203, 2202, 2201, 2200, 2199,
    2198, 2197, 2196, 2195, 2194, 2193, 2192, 2191, 2190, 2189, 2188, 2187, 2186,
    2185, 2184, 2183, 2182, 2181, 2180, 2179, 2178, 2177, 2176, 2175, 2174, 2173,
    2172, 2171, 2170, 2169, 2168, 2167, 2166, 2165, 2164, 2163, 2162, 2161, 2160,
    2159, 2158, 2157, 2156, 2155, 2154, 2153, 2152, 2151, 2150, 2149, 2148, 2147,
    2146, 2145, 2144, 2143, 2142, 2141, 2140, 2139, 2138, 2137, 2136, 2135, 2134,
    2133, 2132, 2131, 2130, 2129, 2128, 2127, 2126, 2125, 2124, 2123, 2122, 2121,
    2120, 2119, 2118, 2117, 2116, 2115, 2114, 2113, 2112, 2111, 2110, 2109, 2108,
    2107, 2106, 2105, 2104, 2103, 2102, 2101, 2100, 2099, 2098, 2097, 2096, 2095,
    2094, 2093, 2092, 2091, 2090, 2089, 2088, 2087, 2086, 2085, 2084, 2083, 2082,
    2081, 2080, 2079, 2078, 2077, 2076, 2075, 2074, 2073, 2072, 2071, 2070, 2069,
    2068, 2067, 2066, 2065, 2064, 2063, 2062, 2061, 2060, 2059, 2058, 2057, 2056,
    2055, 2054, 2053, 2052, 2051, 2050, 2049, 2048, 2047, 2046, 2045, 2044, 2043,
    2042, 2041, 2040, 2039, 2038, 2037, 2036, 2035, 2034, 2033, 2032, 2031, 2030,
    2029, 2028, 2027, 2026, 2025, 2024, 2023, 2022, 2021, 2020, 2019, 2018, 2017,
    2016, 2015, 2014, 2013, 2012, 2011, 2010, 2009, 2008, 2007, 2006, 2005, 2004,
    2003, 2002, 2001, 2000, 1999, 1998, 1997, 1996, 1995, 1994, 1993, 1992, 1991,
    1990, 1989, 1988, 1987, 1986, 1985, 1984, 1983, 1982, 1981, 1980, 1979, 1978,
    1977, 1976, 1975, 1974, 1973, 1972, 1971, 1970, 1969, 1968, 1967, 1966, 1965,
    1964, 1963, 1962, 1961, 1960, 1959, 1958, 1957, 1956, 1955, 1954, 1953, 1952,
    1951, 1950, 1949, 1948, 1947, 1946, 1945, 1944, 1943, 1942, 1941, 1940, 1939,
    1938, 1937, 1936, 1935, 1934, 1933, 1932, 1931, 1930, 1929, 1928, 1927, 1926,
    1925, 1924, 1923, 1922, 1921, 1920, 1919, 1918, 1917, 1916, 1915, 1914, 1913,
    1912, 1911, 1910, 1909, 1908, 1907, 1906, 1905, 1904, 1903, 1902, 1901, 1900,
    1899, 1898, 1897, 1896, 1895, 1894, 1893, 1892, 1891, 1890, 1889, 1888, 1887,
    1886, 1885, 1884, 1883, 1882, 1881, 1880, 1879, 1878, 1877, 1876, 1875, 1874,
    1873, 1872, 1871, 1870, 1869, 1868, 1867, 1866, 1865, 1864, 1863, 1862, 1861,
    1860, 1859, 1858, 1857, 1856, 1855, 1854, 1853, 1852, 1851, 1850, 1849, 1848,
    1847, 1846, 1845, 1844, 1843, 1842, 1841, 1840, 1839, 1838, 1837, 1836, 1835,
    1834, 1833, 1832, 1831, 1830, 1829, 1828, 1827, 1826, 1825, 1824, 1823, 1822,
    1821, 1820, 1819, 1818, 1817, 1816, 1815, 1814, 1813, 1812, 1811, 1810, 1809,
    1808, 1807, 1806, 1805, 1804, 1803, 1802, 1801, 1800, 1799, 1798, 1797, 1796,
    1795, 1794, 1793, 1792, 1791, 1790, 1789, 1788, 1787, 1786, 1785, 1784, 1783,
    1782, 1781, 1780, 1779, 1778, 1777, 1776, 1775, 1774, 1773, 1772, 1771, 1770,
    1769, 1768, 1767, 1766, 1765, 1764, 1763, 1762, 1761, 1760, 1759, 1758, 1757,
    1756, 1755, 1754, 1753, 1752, 1751, 1750, 1749, 1748, 1747, 1746, 1745, 1744,
    1743, 1742, 1741, 1740, 1739, 1738, 1737, 1736, 1735, 1734, 1733, 1732, 1731,
    1730, 1729, 1728, 1727, 1726, 1725, 1724, 1723, 1722, 1721, 1720, 1719, 1718,
    1717, 1716, 1715, 1714, 1713, 1712, 1711, 1710, 1709, 1708, 1707, 1706, 1705,
    1704, 1703, 1702, 1701, 1700, 1699, 1698, 1697, 1696, 1695, 1694, 1693, 1692,
    1691, 1690, 1689, 1688, 1687, 1686, 1685, 1684, 1683, 1682, 1681, 1680, 1679,
    1678, 1677, 1676, 1675, 1674, 1673, 1672, 1671, 1670, 1669, 1668, 1667, 1666,
    1665, 1664, 1663, 1662, 1661, 1660, 1659, 1658, 1657, 1656, 1655, 1654, 1653,
    1652, 1651, 1650, 1649, 1648, 1647, 1646, 1645, 1644, 1643, 1642, 1641, 1640,
    1639, 1638, 1637, 1636, 1635, 1634, 1633, 1632, 1631, 1630, 1629, 1628, 1627,
    1626, 1625, 1624, 1623, 1622, 1621, 1620, 1619, 1618, 1617, 1616, 1615, 1614,
    1613, 1612, 1611, 1610, 1609, 1608, 1607, 1606, 1605, 1604, 1603, 1602, 1601,
    1600, 1599, 1598, 1597, 1596, 1595, 1594, 1593, 1592, 1591, 1590, 1589, 1588,
    1587, 1586, 1585, 1584, 1583, 1582, 1581, 1580, 1579, 1578, 1577, 1576, 1575,
    1574, 1573, 1572, 1571, 1570, 1569, 1568, 1567, 1566, 1565, 1564, 1563, 1562,
    1561, 1560, 1559, 1558, 1557, 1556, 1555, 1554, 1553, 1552, 1551, 1550, 1549,
    1548, 1547, 1546, 1545, 1544, 1543, 1542, 1541, 1540, 1539, 1538, 1537, 1536,
    1535, 1534, 1533, 1532, 1531, 1530, 1529, 1528, 1527, 1526, 1525, 1524, 1523,
    1522, 1521, 1520, 1519, 1518, 1517, 1516, 1515, 1514, 1513, 1512, 1511, 1510,
    1509, 1508, 1507, 1506, 1505, 1504, 1503, 1502, 1501, 1500, 1499, 1498, 1497,
    1496, 1495, 1494, 1493, 1492, 1491, 1490, 1489, 1488, 1487, 1486, 1485, 1484,
    1483, 1482, 1481, 1480, 1479, 1478, 1477, 1476, 1475, 1474, 1473, 1472, 1471,
    1470, 1469, 1468, 1467, 1466, 1465, 1464, 1463, 1462, 1461, 1460, 1459, 1458,
    1457, 1456, 1455, 1454, 1453, 1452, 1451, 1450, 1449, 1448, 1447, 1446, 1445,
    1444, 1443, 1442, 1441, 1440, 1439, 1438, 1437, 1436, 1435, 1434, 1433, 1432,
    1431, 1430, 1429, 1428, 1427, 1426, 1425, 1424, 1423, 1422, 1421, 1420, 1419,
    1418, 1417, 1416, 1415, 1414, 1413, 1412, 1411, 1410, 1409, 1408, 1407, 1406,
    1405, 1404, 1403, 1402, 1401, 1400, 1399, 1398, 1397, 1396, 1395, 1394, 1393,
    1392, 1391, 1390, 1389, 1388, 1387, 1386, 1385, 1384, 1383, 1382, 1381, 1380,
    1379, 1378, 1377, 1376, 1375, 1374, 1373, 1372, 1371, 1370, 1369, 1368, 1367,
    1366, 1365, 1364, 1363, 1362, 1361, 1360, 1359, 1358, 1357, 1356, 1355, 1354,
    1353, 1352, 1351, 1350, 1349, 1348, 1347, 1346, 1345, 1344, 1343, 1342, 1341,
    1340, 1339, 1338, 1337, 1336, 1335, 1334, 1333, 1332, 1331, 1330, 1329, 1328,
    1327, 1326, 1325, 1324, 1323, 1322, 1321, 1320, 1319, 1318, 1317, 1316, 1315,
    1314, 1313, 1312, 1311, 1310, 1309, 1308, 1307, 1306, 1305, 1304, 1303, 1302,
    1301, 1300, 1299, 1298, 1297, 1296, 1295, 1294, 1293, 1292, 1291, 1290, 1289,
    1288, 1287, 1286, 1285, 1284, 1283, 1282, 1281, 1280, 1279, 1278, 1277, 1276,
    1275, 1274, 1273, 1272, 1271, 1270, 1269, 1268, 1267, 1266, 1265, 1264, 1263,
    1262, 1261, 1260, 1259, 1258, 1257, 1256, 1255, 1254, 1253, 1252, 1251, 1250,
    1249, 1248, 1247, 1246, 1245, 1244, 1243, 1242, 1241, 1240, 1239, 1238, 1237,
    1236, 1235, 1234, 1233, 1232, 1231, 1230, 1229, 1228, 1227, 1226, 1225, 1224,
    1223, 1222, 1221, 1220, 1219, 1218, 1217, 1216, 1215, 1214, 1213, 1212, 1211,
    1210, 1209, 1208, 1207, 1206, 1205, 1204, 1203, 1202, 1201, 1200, 1199, 1198,
    1197, 1196, 1195, 1194, 1193, 1192, 1191, 1190, 1189, 1188, 1187, 1186, 1185,
    1184, 1183, 1182, 1181, 1180, 1179, 1178, 1177, 1176, 1175, 1174, 1173, 1172,
    1171, 1170, 1169, 1168, 1167, 1166, 1165, 1164, 1163, 1162, 1161, 1160, 1159,
    1158, 1157, 1156, 1155, 1154, 1153, 1152, 1151, 1150, 1149, 1148, 1147, 1146,
    1145, 1144, 1143, 1142, 1141, 1140, 1139, 1138, 1137, 1136, 1135, 1134, 1133,
    1132, 1131, 1130, 1129, 1128, 1127, 1126, 1125, 1124, 1123, 1122, 1121, 1120,
    1119, 1118, 1117, 1116, 1115, 1114, 1113, 1112, 1111, 1110, 1109, 1108, 1107,
    1106, 1105, 1104, 1103, 1102, 1101, 1100, 1099, 1098, 1097, 1096, 1095, 1094,
    1093, 1092, 1091, 1090, 1089, 1088, 1087, 1086, 1085, 1084, 1083, 1082, 1081,
    1080, 1079, 1078, 1077, 1076, 1075, 1074, 1073, 1072, 1071, 1070, 1069, 1068,
    1067, 1066, 1065, 1064, 1063, 1062, 1061, 1060, 1059, 1058, 1057, 1056, 1055,
    1054, 1053, 1052, 1051, 1050, 1049, 1048, 1047, 1046, 1045, 1044, 1043, 1042,
    1041, 1040, 1039, 1038, 1037, 1036, 1035, 1034, 1033, 1032, 1031, 1030, 1029,
    1028, 1027, 1026, 1025, 1024, 1023, 1022, 1021, 1020, 1019, 1018, 1017, 1016,
    1015, 1014, 1013, 1012, 1011, 1010, 1009, 1008, 1007, 1006, 1005, 1004, 1003,
    1002, 1001, 1000, 999, 998, 997, 996, 995, 994, 993, 992, 991, 990, 989, 988,
    987, 986, 985, 984, 983, 982, 981, 980, 979, 978, 977, 976, 975, 974, 973,
    972, 971, 970, 969, 968, 967, 966, 965, 964, 963, 962, 961, 960, 959, 958,
    957, 956, 955, 954, 953, 952, 951, 950, 949, 948, 947, 946, 945, 944, 943,
    942, 941, 940, 939, 938, 937, 936, 935, 934, 933, 932, 931, 930, 929, 928,
    927, 926, 925, 924, 923, 922, 921, 920, 919, 918, 917, 916, 915, 914, 913,
    912, 911, 910, 909, 908, 907, 906, 905, 904, 903, 902, 901, 900, 899, 898,
    897, 896, 895, 894, 893, 892, 891, 890, 889, 888, 887, 886, 885, 884, 883,
    882, 881, 880, 879, 878, 877, 876, 875, 874, 873, 872, 871, 870, 869, 868,
    867, 866, 865, 864, 863, 862, 861, 860, 859, 858, 857, 856, 855, 854, 853,
    852, 851, 850, 849, 848, 847, 846, 845, 844, 843, 842, 841, 840, 839, 838,
    837, 836, 835, 834, 833, 832, 831, 830, 829, 828, 827, 826, 825, 824, 823,
    822, 821, 820, 819, 818, 817, 816, 815, 814, 813, 812, 811, 810, 809, 808,
    807, 806, 805, 804, 803, 802, 801, 800, 799, 798, 797, 796, 795, 794, 793,
    792, 791, 790, 789, 788, 787, 786, 785, 784, 783, 782, 781, 780, 779, 778,
    777, 776, 775, 774, 773, 772, 771, 770, 769, 768, 767, 766, 765, 764, 763,
    762, 761, 760, 759, 758, 757, 756, 755, 754, 753, 752, 751, 750, 749, 748,
    747, 746, 745, 744, 743, 742, 741, 740, 739, 738, 737, 736, 735, 734, 733,
    732, 731, 730, 729, 728, 727, 726, 725, 724, 723, 722, 721, 720, 719, 718,
    717, 716, 715, 714, 713, 712, 711, 710, 709, 708, 707, 706, 705, 704, 703,
    702, 701, 700, 699, 698, 697, 696, 695, 694, 693, 692, 691, 690, 689, 688,
    687, 686, 685, 684, 683, 682, 681, 680, 679, 678, 677, 676, 675, 674, 673,
    672, 671, 670, 669, 668, 667, 666, 665, 664, 663, 662, 661, 660, 659, 658,
    657, 656, 655, 654, 653, 652, 651, 650, 649, 648, 647, 646, 645, 644, 643,
    642, 641, 640, 639, 638, 637, 636, 635, 634, 633, 632, 631, 630, 629, 628,
    627, 626, 625, 624, 623, 622, 621, 620, 619, 618, 617, 616, 615, 614, 613,
    612, 611, 610, 609, 608, 607, 606, 605, 604, 603, 602, 601, 600, 599, 598,
    597, 596, 595, 594, 593, 592, 591, 590, 589, 588, 587, 586, 585, 584, 583,
    582, 581, 580, 579, 578, 577, 576, 575, 574, 573, 572, 571, 570, 569, 568,
    567, 566, 565, 564, 563, 562, 561, 560, 559, 558, 557, 556, 555, 554, 553,
    552, 551, 550, 549, 548, 547, 546, 545, 544, 543, 542, 541, 540, 539, 538,
    537, 536, 535, 534, 533, 532, 531, 530, 529, 528, 527, 526, 525, 524, 523,
    522, 521, 520, 519, 518, 517, 516, 515, 514, 513, 512, 511, 510, 509, 508,
    507, 506, 505, 504, 503, 502, 501, 500, 499, 498, 497, 496, 495, 494, 493,
    492, 491, 490, 489, 488, 487, 486, 485, 484, 483, 482, 481, 480, 479, 478,
    477, 476, 475, 474, 473, 472, 471, 470, 469, 468, 467, 466, 465, 464, 463,
    462, 461, 460, 459, 458, 457, 456, 455, 454, 453, 452, 451, 450, 449, 448,
    447, 446, 445, 444, 443, 442, 441, 440, 439, 438, 437, 436, 435, 434, 433,
    432, 431, 430, 429, 428, 427, 426, 425, 424, 423, 422, 421, 420, 419, 418,
    417, 416, 415, 414, 413, 412, 411, 410, 409, 408, 407, 406, 405, 404, 403,
    402, 401, 400, 399, 398, 397, 396, 395, 394, 393, 392, 391, 390, 389, 388,
    387, 386, 385, 384, 383, 382, 381, 380, 379, 378, 377, 376, 375, 374, 373,
    372, 371, 370, 369, 368, 367, 366, 365, 364, 363, 362, 361, 360, 359, 358,
    357, 356, 355, 354, 353, 352, 351, 350, 349, 348, 347, 346, 345, 344, 343,
    342, 341, 340, 339, 338, 337, 336, 335, 334, 333, 332, 331, 330, 329, 328,
    327, 326, 325, 324, 323, 322, 321, 320, 319, 318, 317, 316, 315, 314, 313,
    312, 311, 310, 309, 308, 307, 306, 305, 304, 303, 302, 301, 300, 299, 298,
    297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 287, 286, 285, 284, 283,
    282, 281, 280, 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268,
    267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 255, 254, 253,
    252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238,
    237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223,
    222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208,
    207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193,
    192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178,
    177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163,
    162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148,
    147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133,
    132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118,
    117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103,
    102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85,
    84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66,
    65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47,
    46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28,
    27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8,
    7, 6, 5, 4, 3, 2 };

  rtElectricalID_6ph_codegen_DW->costab1q_b[0] = 1.0F;
  for (rtElectricalID_6ph_codegen_DW->idx_f = 0;
       rtElectricalID_6ph_codegen_DW->idx_f < 2500;
       rtElectricalID_6ph_codegen_DW->idx_f++) {
    rtElectricalID_6ph_codegen_DW->costab1q_b
      [rtElectricalID_6ph_codegen_DW->idx_f + 1] = cosf(((real32_T)
      rtElectricalID_6ph_codegen_DW->idx_f + 1.0F) * 0.000314159261F);
  }

  for (rtElectricalID_6ph_codegen_DW->idx_f = 0;
       rtElectricalID_6ph_codegen_DW->idx_f < 2499;
       rtElectricalID_6ph_codegen_DW->idx_f++) {
    rtElectricalID_6ph_codegen_DW->costab1q_b
      [rtElectricalID_6ph_codegen_DW->idx_f + 2501] = sinf((5000.0F - ((real32_T)
      rtElectricalID_6ph_codegen_DW->idx_f + 2501.0F)) * 0.000314159261F);
  }

  rtElectricalID_6ph_codegen_DW->costab1q_b[5000] = 0.0F;
  rtElectricalID_6ph_codegen_DW->costable[0] = 1.0F;
  rtElectricalID_6ph_codegen_DW->sintable[0] = 0.0F;
  for (rtElectricalID_6ph_codegen_DW->idx_f = 0;
       rtElectricalID_6ph_codegen_DW->idx_f < 5000;
       rtElectricalID_6ph_codegen_DW->idx_f++) {
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      rtElectricalID_6ph_codegen_DW->costab1q_b
      [rtElectricalID_6ph_codegen_DW->idx_f + 1];
    rtElectricalID_6ph_codegen_DW->costable[rtElectricalID_6ph_codegen_DW->idx_f
      + 1] = rtElectricalID_6ph_codegen_DW->costable_tmp;
    rtElectricalID_6ph_codegen_DW->twid_re =
      -rtElectricalID_6ph_codegen_DW->costab1q_b[4999 -
      rtElectricalID_6ph_codegen_DW->idx_f];
    rtElectricalID_6ph_codegen_DW->sintable[rtElectricalID_6ph_codegen_DW->idx_f
      + 1] = rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->costable[rtElectricalID_6ph_codegen_DW->idx_f
      + 5001] = rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->sintable[rtElectricalID_6ph_codegen_DW->idx_f
      + 5001] = -rtElectricalID_6ph_codegen_DW->costable_tmp;
  }

  for (rtElectricalID_6ph_codegen_DW->idx_f = 0;
       rtElectricalID_6ph_codegen_DW->idx_f < 8192;
       rtElectricalID_6ph_codegen_DW->idx_f++) {
    rtElectricalID_6ph_codegen_DW->i_g = ((rtElectricalID_6ph_codegen_DW->idx_f
      + 1) << 1) - 2;
    rtElectricalID_6ph_codegen_DW->hcostab[rtElectricalID_6ph_codegen_DW->idx_f]
      = costab[rtElectricalID_6ph_codegen_DW->i_g];
    rtElectricalID_6ph_codegen_DW->hsintab[rtElectricalID_6ph_codegen_DW->idx_f]
      = sintab[rtElectricalID_6ph_codegen_DW->i_g];
    rtElectricalID_6ph_codegen_DW->hcostabinv
      [rtElectricalID_6ph_codegen_DW->idx_f] =
      costabinv[rtElectricalID_6ph_codegen_DW->i_g];
    rtElectricalID_6ph_codegen_DW->hsintabinv
      [rtElectricalID_6ph_codegen_DW->idx_f] =
      sintabinv[rtElectricalID_6ph_codegen_DW->i_g];
  }

  for (rtElectricalID_6ph_codegen_DW->idx_f = 0;
       rtElectricalID_6ph_codegen_DW->idx_f < 5000;
       rtElectricalID_6ph_codegen_DW->idx_f++) {
    rtElectricalID_6ph_codegen_DW->i_g = rtElectricalID_6ph_codegen_DW->idx_f <<
      1;
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      rtElectricalID_6ph_codegen_DW->sintable[rtElectricalID_6ph_codegen_DW->i_g];
    rtElectricalID_6ph_codegen_DW->reconVar1
      [rtElectricalID_6ph_codegen_DW->idx_f].re =
      rtElectricalID_6ph_codegen_DW->costable_tmp + 1.0F;
    rtElectricalID_6ph_codegen_DW->twid_re =
      rtElectricalID_6ph_codegen_DW->costable[rtElectricalID_6ph_codegen_DW->i_g];
    rtElectricalID_6ph_codegen_DW->reconVar1
      [rtElectricalID_6ph_codegen_DW->idx_f].im =
      -rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->reconVar2
      [rtElectricalID_6ph_codegen_DW->idx_f].re = 1.0F -
      rtElectricalID_6ph_codegen_DW->costable_tmp;
    rtElectricalID_6ph_codegen_DW->reconVar2
      [rtElectricalID_6ph_codegen_DW->idx_f].im =
      rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->i_g += xoffInit;
    rtElectricalID_6ph_codegen_DW->temp_re = x
      [rtElectricalID_6ph_codegen_DW->i_g];
    rtElectricalID_6ph_codegen_DW->temp_im = x
      [rtElectricalID_6ph_codegen_DW->i_g + 1];
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      wwc[rtElectricalID_6ph_codegen_DW->idx_f + 4999].re;
    rtElectricalID_6ph_codegen_DW->twid_re = wwc
      [rtElectricalID_6ph_codegen_DW->idx_f + 4999].im;
    rtElectricalID_6ph_codegen_DW->ytmp[rtElectricalID_6ph_codegen_DW->idx_f].re
      = rtElectricalID_6ph_codegen_DW->costable_tmp *
      rtElectricalID_6ph_codegen_DW->temp_re +
      rtElectricalID_6ph_codegen_DW->twid_re *
      rtElectricalID_6ph_codegen_DW->temp_im;
    rtElectricalID_6ph_codegen_DW->ytmp[rtElectricalID_6ph_codegen_DW->idx_f].im
      = rtElectricalID_6ph_codegen_DW->costable_tmp *
      rtElectricalID_6ph_codegen_DW->temp_im -
      rtElectricalID_6ph_codegen_DW->twid_re *
      rtElectricalID_6ph_codegen_DW->temp_re;
  }

  memset(&rtElectricalID_6ph_codegen_DW->fy[0], 0, sizeof(creal32_T) << 14U);
  rtElectricalID_6ph_codegen_DW->iy = 0;
  rtElectricalID_6ph_codegen_DW->idx_f = 0;
  for (rtElectricalID_6ph_codegen_DW->b_idx = 0;
       rtElectricalID_6ph_codegen_DW->b_idx < 4999;
       rtElectricalID_6ph_codegen_DW->b_idx++) {
    rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->iy] =
      rtElectricalID_6ph_codegen_DW->ytmp[rtElectricalID_6ph_codegen_DW->b_idx];
    rtElectricalID_6ph_codegen_DW->iy = 16384;
    tst = true;
    while (tst) {
      rtElectricalID_6ph_codegen_DW->iy >>= 1;
      rtElectricalID_6ph_codegen_DW->idx_f ^= rtElectricalID_6ph_codegen_DW->iy;
      tst = ((rtElectricalID_6ph_codegen_DW->idx_f &
              rtElectricalID_6ph_codegen_DW->iy) == 0);
    }

    rtElectricalID_6ph_codegen_DW->iy = rtElectricalID_6ph_codegen_DW->idx_f;
  }

  rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->iy] =
    rtElectricalID_6ph_codegen_DW->ytmp[4999];
  for (rtElectricalID_6ph_codegen_DW->b_idx = 0;
       rtElectricalID_6ph_codegen_DW->b_idx <= 16383;
       rtElectricalID_6ph_codegen_DW->b_idx += 2) {
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->b_idx + 1]
      .re;
    rtElectricalID_6ph_codegen_DW->twid_re = rtElectricalID_6ph_codegen_DW->
      fy[rtElectricalID_6ph_codegen_DW->b_idx + 1].im;
    rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->b_idx + 1].
      re = rtElectricalID_6ph_codegen_DW->fy
      [rtElectricalID_6ph_codegen_DW->b_idx].re -
      rtElectricalID_6ph_codegen_DW->costable_tmp;
    rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->b_idx + 1].
      im = rtElectricalID_6ph_codegen_DW->fy
      [rtElectricalID_6ph_codegen_DW->b_idx].im -
      rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->b_idx].re +=
      rtElectricalID_6ph_codegen_DW->costable_tmp;
    rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->b_idx].im +=
      rtElectricalID_6ph_codegen_DW->twid_re;
  }

  rtElectricalID_6ph_codegen_DW->b_idx = 2;
  rtElectricalID_6ph_codegen_DW->ix = 4;
  rtElectricalID_6ph_codegen_DW->idx_f = 4096;
  rtElectricalID_6ph_codegen_DW->iy = 16381;
  while (rtElectricalID_6ph_codegen_DW->idx_f > 0) {
    rtElectricalID_6ph_codegen_DW->h_i = 0;
    while (rtElectricalID_6ph_codegen_DW->h_i <
           rtElectricalID_6ph_codegen_DW->iy) {
      rtElectricalID_6ph_codegen_DW->i_g = rtElectricalID_6ph_codegen_DW->h_i +
        rtElectricalID_6ph_codegen_DW->b_idx;
      rtElectricalID_6ph_codegen_DW->temp_re = rtElectricalID_6ph_codegen_DW->
        fy[rtElectricalID_6ph_codegen_DW->i_g].re;
      rtElectricalID_6ph_codegen_DW->temp_im = rtElectricalID_6ph_codegen_DW->
        fy[rtElectricalID_6ph_codegen_DW->i_g].im;
      rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].re =
        rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i].re
        - rtElectricalID_6ph_codegen_DW->temp_re;
      rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].im =
        rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i].im
        - rtElectricalID_6ph_codegen_DW->temp_im;
      rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i].re +=
        rtElectricalID_6ph_codegen_DW->temp_re;
      rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i].im +=
        rtElectricalID_6ph_codegen_DW->temp_im;
      rtElectricalID_6ph_codegen_DW->h_i += rtElectricalID_6ph_codegen_DW->ix;
    }

    rtElectricalID_6ph_codegen_DW->b_istart = 1;
    rtElectricalID_6ph_codegen_DW->b_j = rtElectricalID_6ph_codegen_DW->idx_f;
    while (rtElectricalID_6ph_codegen_DW->b_j < 8192) {
      rtElectricalID_6ph_codegen_DW->twid_re =
        rtElectricalID_6ph_codegen_DW->hcostab
        [rtElectricalID_6ph_codegen_DW->b_j];
      rtElectricalID_6ph_codegen_DW->twid_im =
        rtElectricalID_6ph_codegen_DW->hsintab
        [rtElectricalID_6ph_codegen_DW->b_j];
      rtElectricalID_6ph_codegen_DW->h_i =
        rtElectricalID_6ph_codegen_DW->b_istart;
      rtElectricalID_6ph_codegen_DW->b_ihi =
        rtElectricalID_6ph_codegen_DW->b_istart +
        rtElectricalID_6ph_codegen_DW->iy;
      while (rtElectricalID_6ph_codegen_DW->h_i <
             rtElectricalID_6ph_codegen_DW->b_ihi) {
        rtElectricalID_6ph_codegen_DW->i_g = rtElectricalID_6ph_codegen_DW->h_i
          + rtElectricalID_6ph_codegen_DW->b_idx;
        rtElectricalID_6ph_codegen_DW->costable_tmp =
          rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].
          im;
        rtElectricalID_6ph_codegen_DW->temp_im =
          rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].
          re;
        rtElectricalID_6ph_codegen_DW->temp_re =
          rtElectricalID_6ph_codegen_DW->temp_im *
          rtElectricalID_6ph_codegen_DW->twid_re -
          rtElectricalID_6ph_codegen_DW->costable_tmp *
          rtElectricalID_6ph_codegen_DW->twid_im;
        rtElectricalID_6ph_codegen_DW->temp_im =
          rtElectricalID_6ph_codegen_DW->costable_tmp *
          rtElectricalID_6ph_codegen_DW->twid_re +
          rtElectricalID_6ph_codegen_DW->temp_im *
          rtElectricalID_6ph_codegen_DW->twid_im;
        rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].re
          = rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i]
          .re - rtElectricalID_6ph_codegen_DW->temp_re;
        rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].im
          = rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i]
          .im - rtElectricalID_6ph_codegen_DW->temp_im;
        rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i].re
          += rtElectricalID_6ph_codegen_DW->temp_re;
        rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->h_i].im
          += rtElectricalID_6ph_codegen_DW->temp_im;
        rtElectricalID_6ph_codegen_DW->h_i += rtElectricalID_6ph_codegen_DW->ix;
      }

      rtElectricalID_6ph_codegen_DW->b_istart++;
      rtElectricalID_6ph_codegen_DW->b_j += rtElectricalID_6ph_codegen_DW->idx_f;
    }

    rtElectricalID_6ph_codegen_DW->idx_f /= 2;
    rtElectricalID_6ph_codegen_DW->b_idx = rtElectricalID_6ph_codegen_DW->ix;
    rtElectricalID_6ph_codegen_DW->ix += rtElectricalID_6ph_codegen_DW->ix;
    rtElectricalID_6ph_codegen_DW->iy -= rtElectricalID_6ph_codegen_DW->b_idx;
  }

  memset(&rtElectricalID_6ph_codegen_DW->fv[0], 0, sizeof(creal32_T) << 14U);
  rtElectricalID_6ph_codegen_DW->iy = 0;
  for (rtElectricalID_6ph_codegen_DW->b_idx = 0;
       rtElectricalID_6ph_codegen_DW->b_idx < 9998;
       rtElectricalID_6ph_codegen_DW->b_idx++) {
    rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->iy] =
      wwc[rtElectricalID_6ph_codegen_DW->b_idx];
    rtElectricalID_6ph_codegen_DW->iy = 16384;
    tst = true;
    while (tst) {
      rtElectricalID_6ph_codegen_DW->iy >>= 1;
      rtElectricalID_6ph_codegen_DW->idx_f ^= rtElectricalID_6ph_codegen_DW->iy;
      tst = ((rtElectricalID_6ph_codegen_DW->idx_f &
              rtElectricalID_6ph_codegen_DW->iy) == 0);
    }

    rtElectricalID_6ph_codegen_DW->iy = rtElectricalID_6ph_codegen_DW->idx_f;
  }

  rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->iy] = wwc
    [9998];
  for (rtElectricalID_6ph_codegen_DW->b_idx = 0;
       rtElectricalID_6ph_codegen_DW->b_idx <= 16383;
       rtElectricalID_6ph_codegen_DW->b_idx += 2) {
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx + 1]
      .re;
    rtElectricalID_6ph_codegen_DW->twid_re = rtElectricalID_6ph_codegen_DW->
      fv[rtElectricalID_6ph_codegen_DW->b_idx + 1].im;
    rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx + 1].
      re = rtElectricalID_6ph_codegen_DW->fv
      [rtElectricalID_6ph_codegen_DW->b_idx].re -
      rtElectricalID_6ph_codegen_DW->costable_tmp;
    rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx + 1].
      im = rtElectricalID_6ph_codegen_DW->fv
      [rtElectricalID_6ph_codegen_DW->b_idx].im -
      rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx].re +=
      rtElectricalID_6ph_codegen_DW->costable_tmp;
    rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx].im +=
      rtElectricalID_6ph_codegen_DW->twid_re;
  }

  rtElectricalID_6ph_codegen_DW->b_idx = 2;
  rtElectricalID_6ph_codegen_DW->ix = 4;
  rtElectricalID_6ph_codegen_DW->idx_f = 4096;
  rtElectricalID_6ph_codegen_DW->iy = 16381;
  while (rtElectricalID_6ph_codegen_DW->idx_f > 0) {
    rtElectricalID_6ph_codegen_DW->h_i = 0;
    while (rtElectricalID_6ph_codegen_DW->h_i <
           rtElectricalID_6ph_codegen_DW->iy) {
      rtElectricalID_6ph_codegen_DW->i_g = rtElectricalID_6ph_codegen_DW->h_i +
        rtElectricalID_6ph_codegen_DW->b_idx;
      rtElectricalID_6ph_codegen_DW->temp_re = rtElectricalID_6ph_codegen_DW->
        fv[rtElectricalID_6ph_codegen_DW->i_g].re;
      rtElectricalID_6ph_codegen_DW->temp_im = rtElectricalID_6ph_codegen_DW->
        fv[rtElectricalID_6ph_codegen_DW->i_g].im;
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->i_g].re =
        rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i].re
        - rtElectricalID_6ph_codegen_DW->temp_re;
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->i_g].im =
        rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i].im
        - rtElectricalID_6ph_codegen_DW->temp_im;
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i].re +=
        rtElectricalID_6ph_codegen_DW->temp_re;
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i].im +=
        rtElectricalID_6ph_codegen_DW->temp_im;
      rtElectricalID_6ph_codegen_DW->h_i += rtElectricalID_6ph_codegen_DW->ix;
    }

    rtElectricalID_6ph_codegen_DW->b_istart = 1;
    rtElectricalID_6ph_codegen_DW->b_j = rtElectricalID_6ph_codegen_DW->idx_f;
    while (rtElectricalID_6ph_codegen_DW->b_j < 8192) {
      rtElectricalID_6ph_codegen_DW->twid_re =
        rtElectricalID_6ph_codegen_DW->hcostab
        [rtElectricalID_6ph_codegen_DW->b_j];
      rtElectricalID_6ph_codegen_DW->twid_im =
        rtElectricalID_6ph_codegen_DW->hsintab
        [rtElectricalID_6ph_codegen_DW->b_j];
      rtElectricalID_6ph_codegen_DW->h_i =
        rtElectricalID_6ph_codegen_DW->b_istart;
      rtElectricalID_6ph_codegen_DW->b_ihi =
        rtElectricalID_6ph_codegen_DW->b_istart +
        rtElectricalID_6ph_codegen_DW->iy;
      while (rtElectricalID_6ph_codegen_DW->h_i <
             rtElectricalID_6ph_codegen_DW->b_ihi) {
        rtElectricalID_6ph_codegen_DW->i_g = rtElectricalID_6ph_codegen_DW->h_i
          + rtElectricalID_6ph_codegen_DW->b_idx;
        rtElectricalID_6ph_codegen_DW->costable_tmp =
          rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->i_g].
          im;
        rtElectricalID_6ph_codegen_DW->temp_im =
          rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->i_g].
          re;
        rtElectricalID_6ph_codegen_DW->temp_re =
          rtElectricalID_6ph_codegen_DW->temp_im *
          rtElectricalID_6ph_codegen_DW->twid_re -
          rtElectricalID_6ph_codegen_DW->costable_tmp *
          rtElectricalID_6ph_codegen_DW->twid_im;
        rtElectricalID_6ph_codegen_DW->temp_im =
          rtElectricalID_6ph_codegen_DW->costable_tmp *
          rtElectricalID_6ph_codegen_DW->twid_re +
          rtElectricalID_6ph_codegen_DW->temp_im *
          rtElectricalID_6ph_codegen_DW->twid_im;
        rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->i_g].re
          = rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i]
          .re - rtElectricalID_6ph_codegen_DW->temp_re;
        rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->i_g].im
          = rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i]
          .im - rtElectricalID_6ph_codegen_DW->temp_im;
        rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i].re
          += rtElectricalID_6ph_codegen_DW->temp_re;
        rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->h_i].im
          += rtElectricalID_6ph_codegen_DW->temp_im;
        rtElectricalID_6ph_codegen_DW->h_i += rtElectricalID_6ph_codegen_DW->ix;
      }

      rtElectricalID_6ph_codegen_DW->b_istart++;
      rtElectricalID_6ph_codegen_DW->b_j += rtElectricalID_6ph_codegen_DW->idx_f;
    }

    rtElectricalID_6ph_codegen_DW->idx_f /= 2;
    rtElectricalID_6ph_codegen_DW->b_idx = rtElectricalID_6ph_codegen_DW->ix;
    rtElectricalID_6ph_codegen_DW->ix += rtElectricalID_6ph_codegen_DW->ix;
    rtElectricalID_6ph_codegen_DW->iy -= rtElectricalID_6ph_codegen_DW->b_idx;
  }

  for (rtElectricalID_6ph_codegen_DW->i_g = 0;
       rtElectricalID_6ph_codegen_DW->i_g < 16384;
       rtElectricalID_6ph_codegen_DW->i_g++) {
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      rtElectricalID_6ph_codegen_DW->fy[rtElectricalID_6ph_codegen_DW->i_g].re;
    rtElectricalID_6ph_codegen_DW->twid_re = rtElectricalID_6ph_codegen_DW->
      fv[rtElectricalID_6ph_codegen_DW->i_g].im;
    rtElectricalID_6ph_codegen_DW->temp_re = rtElectricalID_6ph_codegen_DW->
      fy[rtElectricalID_6ph_codegen_DW->i_g].im;
    rtElectricalID_6ph_codegen_DW->temp_im = rtElectricalID_6ph_codegen_DW->
      fv[rtElectricalID_6ph_codegen_DW->i_g].re;
    rtElectricalID_6ph_codegen_DW->fy_k[rtElectricalID_6ph_codegen_DW->i_g].re =
      rtElectricalID_6ph_codegen_DW->costable_tmp *
      rtElectricalID_6ph_codegen_DW->temp_im -
      rtElectricalID_6ph_codegen_DW->temp_re *
      rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->fy_k[rtElectricalID_6ph_codegen_DW->i_g].im =
      rtElectricalID_6ph_codegen_DW->costable_tmp *
      rtElectricalID_6ph_codegen_DW->twid_re +
      rtElectricalID_6ph_codegen_DW->temp_re *
      rtElectricalID_6ph_codegen_DW->temp_im;
  }

  FFTImplementationCallback_r2br_(rtElectricalID_6ph_codegen_DW->fy_k,
    rtElectricalID_6ph_codegen_DW->hcostabinv,
    rtElectricalID_6ph_codegen_DW->hsintabinv, rtElectricalID_6ph_codegen_DW->fv,
    rtElectricalID_6ph_codegen_DW);
  for (rtElectricalID_6ph_codegen_DW->b_idx = 0;
       rtElectricalID_6ph_codegen_DW->b_idx < 5000;
       rtElectricalID_6ph_codegen_DW->b_idx++) {
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      wwc[rtElectricalID_6ph_codegen_DW->b_idx + 4999].re;
    rtElectricalID_6ph_codegen_DW->twid_re = wwc
      [rtElectricalID_6ph_codegen_DW->b_idx + 4999].im;
    rtElectricalID_6ph_codegen_DW->ytmp[rtElectricalID_6ph_codegen_DW->b_idx].re
      = rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx +
      4999].re * rtElectricalID_6ph_codegen_DW->costable_tmp +
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx +
      4999].im * rtElectricalID_6ph_codegen_DW->twid_re;
    rtElectricalID_6ph_codegen_DW->ytmp[rtElectricalID_6ph_codegen_DW->b_idx].im
      = rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx +
      4999].im * rtElectricalID_6ph_codegen_DW->costable_tmp -
      rtElectricalID_6ph_codegen_DW->fv[rtElectricalID_6ph_codegen_DW->b_idx +
      4999].re * rtElectricalID_6ph_codegen_DW->twid_re;
  }

  for (rtElectricalID_6ph_codegen_DW->idx_f = 0;
       rtElectricalID_6ph_codegen_DW->idx_f < 5000;
       rtElectricalID_6ph_codegen_DW->idx_f++) {
    int16_T b;
    rtElectricalID_6ph_codegen_DW->temp_re =
      rtElectricalID_6ph_codegen_DW->reconVar2
      [rtElectricalID_6ph_codegen_DW->idx_f].re;
    rtElectricalID_6ph_codegen_DW->temp_im =
      rtElectricalID_6ph_codegen_DW->reconVar2
      [rtElectricalID_6ph_codegen_DW->idx_f].im;
    b = b_0[rtElectricalID_6ph_codegen_DW->idx_f];
    rtElectricalID_6ph_codegen_DW->twid_im =
      rtElectricalID_6ph_codegen_DW->reconVar1
      [rtElectricalID_6ph_codegen_DW->idx_f].re;
    rtElectricalID_6ph_codegen_DW->reconVar1_im =
      rtElectricalID_6ph_codegen_DW->reconVar1
      [rtElectricalID_6ph_codegen_DW->idx_f].im;
    rtElectricalID_6ph_codegen_DW->ytmp_re_tmp =
      rtElectricalID_6ph_codegen_DW->ytmp[b - 1].re;
    rtElectricalID_6ph_codegen_DW->ytmp_im_tmp =
      -rtElectricalID_6ph_codegen_DW->ytmp[b - 1].im;
    rtElectricalID_6ph_codegen_DW->costable_tmp =
      rtElectricalID_6ph_codegen_DW->ytmp[rtElectricalID_6ph_codegen_DW->idx_f].
      re;
    rtElectricalID_6ph_codegen_DW->twid_re = rtElectricalID_6ph_codegen_DW->
      ytmp[rtElectricalID_6ph_codegen_DW->idx_f].im;
    y[rtElectricalID_6ph_codegen_DW->idx_f].re =
      ((rtElectricalID_6ph_codegen_DW->costable_tmp *
        rtElectricalID_6ph_codegen_DW->twid_im -
        rtElectricalID_6ph_codegen_DW->twid_re *
        rtElectricalID_6ph_codegen_DW->reconVar1_im) +
       (rtElectricalID_6ph_codegen_DW->ytmp_re_tmp *
        rtElectricalID_6ph_codegen_DW->temp_re -
        rtElectricalID_6ph_codegen_DW->ytmp_im_tmp *
        rtElectricalID_6ph_codegen_DW->temp_im)) * 0.5F;
    y[rtElectricalID_6ph_codegen_DW->idx_f].im =
      ((rtElectricalID_6ph_codegen_DW->costable_tmp *
        rtElectricalID_6ph_codegen_DW->reconVar1_im +
        rtElectricalID_6ph_codegen_DW->twid_re *
        rtElectricalID_6ph_codegen_DW->twid_im) +
       (rtElectricalID_6ph_codegen_DW->ytmp_re_tmp *
        rtElectricalID_6ph_codegen_DW->temp_im +
        rtElectricalID_6ph_codegen_DW->ytmp_im_tmp *
        rtElectricalID_6ph_codegen_DW->temp_re)) * 0.5F;
    y[rtElectricalID_6ph_codegen_DW->idx_f + 5000].re =
      ((rtElectricalID_6ph_codegen_DW->costable_tmp *
        rtElectricalID_6ph_codegen_DW->temp_re -
        rtElectricalID_6ph_codegen_DW->twid_re *
        rtElectricalID_6ph_codegen_DW->temp_im) +
       (rtElectricalID_6ph_codegen_DW->ytmp_re_tmp *
        rtElectricalID_6ph_codegen_DW->twid_im -
        rtElectricalID_6ph_codegen_DW->ytmp_im_tmp *
        rtElectricalID_6ph_codegen_DW->reconVar1_im)) * 0.5F;
    y[rtElectricalID_6ph_codegen_DW->idx_f + 5000].im =
      ((rtElectricalID_6ph_codegen_DW->costable_tmp *
        rtElectricalID_6ph_codegen_DW->temp_im +
        rtElectricalID_6ph_codegen_DW->twid_re *
        rtElectricalID_6ph_codegen_DW->temp_re) +
       (rtElectricalID_6ph_codegen_DW->ytmp_re_tmp *
        rtElectricalID_6ph_codegen_DW->reconVar1_im +
        rtElectricalID_6ph_codegen_DW->ytmp_im_tmp *
        rtElectricalID_6ph_codegen_DW->twid_im)) * 0.5F;
  }
}

real32_T rt_hypotf_snf(real32_T u0, real32_T u1)
{
  real32_T a;
  real32_T y;
  a = fabsf(u0);
  y = fabsf(u1);
  if (a < y) {
    a /= y;
    y *= sqrtf(a * a + 1.0F);
  } else if (a > y) {
    y /= a;
    y = sqrtf(y * y + 1.0F) * a;
  } else if (!rtIsNaNF(y)) {
    y = a * 1.41421354F;
  }

  return y;
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    int32_T u0_0;
    int32_T u1_0;
    if (u0 > 0.0F) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0F) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2f((real32_T)u0_0, (real32_T)u1_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = atan2f(u0, u1);
  }

  return y;
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function [output] = FFTRecordedVoltage(input,data,sampletime)
 * FFTRecordedVoltage performs FFT
 *    Detailed explanation goes here
 *  carry datatype
 */
static void FFTRecordedVoltage(internal_psi_analysis *input, const real32_T
  data[10000], real32_T sampletime, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  static const real32_T e[5001] = { 0.0F, 0.0001F, 0.0002F, 0.0003F, 0.0004F,
    0.0005F, 0.0006F, 0.0007F, 0.0008F, 0.0009F, 0.001F, 0.0011F, 0.0012F,
    0.0013F, 0.0014F, 0.0015F, 0.0016F, 0.0017F, 0.0018F, 0.0019F, 0.002F,
    0.0021F, 0.0022F, 0.0023F, 0.0024F, 0.0025F, 0.0026F, 0.0027F, 0.0028F,
    0.0029F, 0.003F, 0.0031F, 0.0032F, 0.0033F, 0.0034F, 0.0035F, 0.0036F,
    0.0037F, 0.0038F, 0.0039F, 0.004F, 0.0041F, 0.0042F, 0.0043F, 0.0044F,
    0.0045F, 0.0046F, 0.0047F, 0.0048F, 0.0049F, 0.005F, 0.0051F, 0.0052F,
    0.0053F, 0.0054F, 0.0055F, 0.0056F, 0.0057F, 0.0058F, 0.0059F, 0.006F,
    0.0061F, 0.0062F, 0.0063F, 0.0064F, 0.0065F, 0.0066F, 0.0067F, 0.0068F,
    0.0069F, 0.007F, 0.0071F, 0.0072F, 0.0073F, 0.0074F, 0.0075F, 0.0076F,
    0.0077F, 0.0078F, 0.0079F, 0.008F, 0.0081F, 0.0082F, 0.0083F, 0.0084F,
    0.0085F, 0.0086F, 0.0087F, 0.0088F, 0.0089F, 0.009F, 0.0091F, 0.0092F,
    0.0093F, 0.0094F, 0.0095F, 0.0096F, 0.0097F, 0.0098F, 0.0099F, 0.01F,
    0.0101F, 0.0102F, 0.0103F, 0.0104F, 0.0105F, 0.0106F, 0.0107F, 0.0108F,
    0.0109F, 0.011F, 0.0111F, 0.0112F, 0.0113F, 0.0114F, 0.0115F, 0.0116F,
    0.0117F, 0.0118F, 0.0119F, 0.012F, 0.0121F, 0.0122F, 0.0123F, 0.0124F,
    0.0125F, 0.0126F, 0.0127F, 0.0128F, 0.0129F, 0.013F, 0.0131F, 0.0132F,
    0.0133F, 0.0134F, 0.0135F, 0.0136F, 0.0137F, 0.0138F, 0.0139F, 0.014F,
    0.0141F, 0.0142F, 0.0143F, 0.0144F, 0.0145F, 0.0146F, 0.0147F, 0.0148F,
    0.0149F, 0.015F, 0.0151F, 0.0152F, 0.0153F, 0.0154F, 0.0155F, 0.0156F,
    0.0157F, 0.0158F, 0.0159F, 0.016F, 0.0161F, 0.0162F, 0.0163F, 0.0164F,
    0.0165F, 0.0166F, 0.0167F, 0.0168F, 0.0169F, 0.017F, 0.0171F, 0.0172F,
    0.0173F, 0.0174F, 0.0175F, 0.0176F, 0.0177F, 0.0178F, 0.0179F, 0.018F,
    0.0181F, 0.0182F, 0.0183F, 0.0184F, 0.0185F, 0.0186F, 0.0187F, 0.0188F,
    0.0189F, 0.019F, 0.0191F, 0.0192F, 0.0193F, 0.0194F, 0.0195F, 0.0196F,
    0.0197F, 0.0198F, 0.0199F, 0.02F, 0.0201F, 0.0202F, 0.0203F, 0.0204F,
    0.0205F, 0.0206F, 0.0207F, 0.0208F, 0.0209F, 0.021F, 0.0211F, 0.0212F,
    0.0213F, 0.0214F, 0.0215F, 0.0216F, 0.0217F, 0.0218F, 0.0219F, 0.022F,
    0.0221F, 0.0222F, 0.0223F, 0.0224F, 0.0225F, 0.0226F, 0.0227F, 0.0228F,
    0.0229F, 0.023F, 0.0231F, 0.0232F, 0.0233F, 0.0234F, 0.0235F, 0.0236F,
    0.0237F, 0.0238F, 0.0239F, 0.024F, 0.0241F, 0.0242F, 0.0243F, 0.0244F,
    0.0245F, 0.0246F, 0.0247F, 0.0248F, 0.0249F, 0.025F, 0.0251F, 0.0252F,
    0.0253F, 0.0254F, 0.0255F, 0.0256F, 0.0257F, 0.0258F, 0.0259F, 0.026F,
    0.0261F, 0.0262F, 0.0263F, 0.0264F, 0.0265F, 0.0266F, 0.0267F, 0.0268F,
    0.0269F, 0.027F, 0.0271F, 0.0272F, 0.0273F, 0.0274F, 0.0275F, 0.0276F,
    0.0277F, 0.0278F, 0.0279F, 0.028F, 0.0281F, 0.0282F, 0.0283F, 0.0284F,
    0.0285F, 0.0286F, 0.0287F, 0.0288F, 0.0289F, 0.029F, 0.0291F, 0.0292F,
    0.0293F, 0.0294F, 0.0295F, 0.0296F, 0.0297F, 0.0298F, 0.0299F, 0.03F,
    0.0301F, 0.0302F, 0.0303F, 0.0304F, 0.0305F, 0.0306F, 0.0307F, 0.0308F,
    0.0309F, 0.031F, 0.0311F, 0.0312F, 0.0313F, 0.0314F, 0.0315F, 0.0316F,
    0.0317F, 0.0318F, 0.0319F, 0.032F, 0.0321F, 0.0322F, 0.0323F, 0.0324F,
    0.0325F, 0.0326F, 0.0327F, 0.0328F, 0.0329F, 0.033F, 0.0331F, 0.0332F,
    0.0333F, 0.0334F, 0.0335F, 0.0336F, 0.0337F, 0.0338F, 0.0339F, 0.034F,
    0.0341F, 0.0342F, 0.0343F, 0.0344F, 0.0345F, 0.0346F, 0.0347F, 0.0348F,
    0.0349F, 0.035F, 0.0351F, 0.0352F, 0.0353F, 0.0354F, 0.0355F, 0.0356F,
    0.0357F, 0.0358F, 0.0359F, 0.036F, 0.0361F, 0.0362F, 0.0363F, 0.0364F,
    0.0365F, 0.0366F, 0.0367F, 0.0368F, 0.0369F, 0.037F, 0.0371F, 0.0372F,
    0.0373F, 0.0374F, 0.0375F, 0.0376F, 0.0377F, 0.0378F, 0.0379F, 0.038F,
    0.0381F, 0.0382F, 0.0383F, 0.0384F, 0.0385F, 0.0386F, 0.0387F, 0.0388F,
    0.0389F, 0.039F, 0.0391F, 0.0392F, 0.0393F, 0.0394F, 0.0395F, 0.0396F,
    0.0397F, 0.0398F, 0.0399F, 0.04F, 0.0401F, 0.0402F, 0.0403F, 0.0404F,
    0.0405F, 0.0406F, 0.0407F, 0.0408F, 0.0409F, 0.041F, 0.0411F, 0.0412F,
    0.0413F, 0.0414F, 0.0415F, 0.0416F, 0.0417F, 0.0418F, 0.0419F, 0.042F,
    0.0421F, 0.0422F, 0.0423F, 0.0424F, 0.0425F, 0.0426F, 0.0427F, 0.0428F,
    0.0429F, 0.043F, 0.0431F, 0.0432F, 0.0433F, 0.0434F, 0.0435F, 0.0436F,
    0.0437F, 0.0438F, 0.0439F, 0.044F, 0.0441F, 0.0442F, 0.0443F, 0.0444F,
    0.0445F, 0.0446F, 0.0447F, 0.0448F, 0.0449F, 0.045F, 0.0451F, 0.0452F,
    0.0453F, 0.0454F, 0.0455F, 0.0456F, 0.0457F, 0.0458F, 0.0459F, 0.046F,
    0.0461F, 0.0462F, 0.0463F, 0.0464F, 0.0465F, 0.0466F, 0.0467F, 0.0468F,
    0.0469F, 0.047F, 0.0471F, 0.0472F, 0.0473F, 0.0474F, 0.0475F, 0.0476F,
    0.0477F, 0.0478F, 0.0479F, 0.048F, 0.0481F, 0.0482F, 0.0483F, 0.0484F,
    0.0485F, 0.0486F, 0.0487F, 0.0488F, 0.0489F, 0.049F, 0.0491F, 0.0492F,
    0.0493F, 0.0494F, 0.0495F, 0.0496F, 0.0497F, 0.0498F, 0.0499F, 0.05F,
    0.0501F, 0.0502F, 0.0503F, 0.0504F, 0.0505F, 0.0506F, 0.0507F, 0.0508F,
    0.0509F, 0.051F, 0.0511F, 0.0512F, 0.0513F, 0.0514F, 0.0515F, 0.0516F,
    0.0517F, 0.0518F, 0.0519F, 0.052F, 0.0521F, 0.0522F, 0.0523F, 0.0524F,
    0.0525F, 0.0526F, 0.0527F, 0.0528F, 0.0529F, 0.053F, 0.0531F, 0.0532F,
    0.0533F, 0.0534F, 0.0535F, 0.0536F, 0.0537F, 0.0538F, 0.0539F, 0.054F,
    0.0541F, 0.0542F, 0.0543F, 0.0544F, 0.0545F, 0.0546F, 0.0547F, 0.0548F,
    0.0549F, 0.055F, 0.0551F, 0.0552F, 0.0553F, 0.0554F, 0.0555F, 0.0556F,
    0.0557F, 0.0558F, 0.0559F, 0.056F, 0.0561F, 0.0562F, 0.0563F, 0.0564F,
    0.0565F, 0.0566F, 0.0567F, 0.0568F, 0.0569F, 0.057F, 0.0571F, 0.0572F,
    0.0573F, 0.0574F, 0.0575F, 0.0576F, 0.0577F, 0.0578F, 0.0579F, 0.058F,
    0.0581F, 0.0582F, 0.0583F, 0.0584F, 0.0585F, 0.0586F, 0.0587F, 0.0588F,
    0.0589F, 0.059F, 0.0591F, 0.0592F, 0.0593F, 0.0594F, 0.0595F, 0.0596F,
    0.0597F, 0.0598F, 0.0599F, 0.06F, 0.0601F, 0.0602F, 0.0603F, 0.0604F,
    0.0605F, 0.0606F, 0.0607F, 0.0608F, 0.0609F, 0.061F, 0.0611F, 0.0612F,
    0.0613F, 0.0614F, 0.0615F, 0.0616F, 0.0617F, 0.0618F, 0.0619F, 0.062F,
    0.0621F, 0.0622F, 0.0623F, 0.0624F, 0.0625F, 0.0626F, 0.0627F, 0.0628F,
    0.0629F, 0.063F, 0.0631F, 0.0632F, 0.0633F, 0.0634F, 0.0635F, 0.0636F,
    0.0637F, 0.0638F, 0.0639F, 0.064F, 0.0641F, 0.0642F, 0.0643F, 0.0644F,
    0.0645F, 0.0646F, 0.0647F, 0.0648F, 0.0649F, 0.065F, 0.0651F, 0.0652F,
    0.0653F, 0.0654F, 0.0655F, 0.0656F, 0.0657F, 0.0658F, 0.0659F, 0.066F,
    0.0661F, 0.0662F, 0.0663F, 0.0664F, 0.0665F, 0.0666F, 0.0667F, 0.0668F,
    0.0669F, 0.067F, 0.0671F, 0.0672F, 0.0673F, 0.0674F, 0.0675F, 0.0676F,
    0.0677F, 0.0678F, 0.0679F, 0.068F, 0.0681F, 0.0682F, 0.0683F, 0.0684F,
    0.0685F, 0.0686F, 0.0687F, 0.0688F, 0.0689F, 0.069F, 0.0691F, 0.0692F,
    0.0693F, 0.0694F, 0.0695F, 0.0696F, 0.0697F, 0.0698F, 0.0699F, 0.07F,
    0.0701F, 0.0702F, 0.0703F, 0.0704F, 0.0705F, 0.0706F, 0.0707F, 0.0708F,
    0.0709F, 0.071F, 0.0711F, 0.0712F, 0.0713F, 0.0714F, 0.0715F, 0.0716F,
    0.0717F, 0.0718F, 0.0719F, 0.072F, 0.0721F, 0.0722F, 0.0723F, 0.0724F,
    0.0725F, 0.0726F, 0.0727F, 0.0728F, 0.0729F, 0.073F, 0.0731F, 0.0732F,
    0.0733F, 0.0734F, 0.0735F, 0.0736F, 0.0737F, 0.0738F, 0.0739F, 0.074F,
    0.0741F, 0.0742F, 0.0743F, 0.0744F, 0.0745F, 0.0746F, 0.0747F, 0.0748F,
    0.0749F, 0.075F, 0.0751F, 0.0752F, 0.0753F, 0.0754F, 0.0755F, 0.0756F,
    0.0757F, 0.0758F, 0.0759F, 0.076F, 0.0761F, 0.0762F, 0.0763F, 0.0764F,
    0.0765F, 0.0766F, 0.0767F, 0.0768F, 0.0769F, 0.077F, 0.0771F, 0.0772F,
    0.0773F, 0.0774F, 0.0775F, 0.0776F, 0.0777F, 0.0778F, 0.0779F, 0.078F,
    0.0781F, 0.0782F, 0.0783F, 0.0784F, 0.0785F, 0.0786F, 0.0787F, 0.0788F,
    0.0789F, 0.079F, 0.0791F, 0.0792F, 0.0793F, 0.0794F, 0.0795F, 0.0796F,
    0.0797F, 0.0798F, 0.0799F, 0.08F, 0.0801F, 0.0802F, 0.0803F, 0.0804F,
    0.0805F, 0.0806F, 0.0807F, 0.0808F, 0.0809F, 0.081F, 0.0811F, 0.0812F,
    0.0813F, 0.0814F, 0.0815F, 0.0816F, 0.0817F, 0.0818F, 0.0819F, 0.082F,
    0.0821F, 0.0822F, 0.0823F, 0.0824F, 0.0825F, 0.0826F, 0.0827F, 0.0828F,
    0.0829F, 0.083F, 0.0831F, 0.0832F, 0.0833F, 0.0834F, 0.0835F, 0.0836F,
    0.0837F, 0.0838F, 0.0839F, 0.084F, 0.0841F, 0.0842F, 0.0843F, 0.0844F,
    0.0845F, 0.0846F, 0.0847F, 0.0848F, 0.0849F, 0.085F, 0.0851F, 0.0852F,
    0.0853F, 0.0854F, 0.0855F, 0.0856F, 0.0857F, 0.0858F, 0.0859F, 0.086F,
    0.0861F, 0.0862F, 0.0863F, 0.0864F, 0.0865F, 0.0866F, 0.0867F, 0.0868F,
    0.0869F, 0.087F, 0.0871F, 0.0872F, 0.0873F, 0.0874F, 0.0875F, 0.0876F,
    0.0877F, 0.0878F, 0.0879F, 0.088F, 0.0881F, 0.0882F, 0.0883F, 0.0884F,
    0.0885F, 0.0886F, 0.0887F, 0.0888F, 0.0889F, 0.089F, 0.0891F, 0.0892F,
    0.0893F, 0.0894F, 0.0895F, 0.0896F, 0.0897F, 0.0898F, 0.0899F, 0.09F,
    0.0901F, 0.0902F, 0.0903F, 0.0904F, 0.0905F, 0.0906F, 0.0907F, 0.0908F,
    0.0909F, 0.091F, 0.0911F, 0.0912F, 0.0913F, 0.0914F, 0.0915F, 0.0916F,
    0.0917F, 0.0918F, 0.0919F, 0.092F, 0.0921F, 0.0922F, 0.0923F, 0.0924F,
    0.0925F, 0.0926F, 0.0927F, 0.0928F, 0.0929F, 0.093F, 0.0931F, 0.0932F,
    0.0933F, 0.0934F, 0.0935F, 0.0936F, 0.0937F, 0.0938F, 0.0939F, 0.094F,
    0.0941F, 0.0942F, 0.0943F, 0.0944F, 0.0945F, 0.0946F, 0.0947F, 0.0948F,
    0.0949F, 0.095F, 0.0951F, 0.0952F, 0.0953F, 0.0954F, 0.0955F, 0.0956F,
    0.0957F, 0.0958F, 0.0959F, 0.096F, 0.0961F, 0.0962F, 0.0963F, 0.0964F,
    0.0965F, 0.0966F, 0.0967F, 0.0968F, 0.0969F, 0.097F, 0.0971F, 0.0972F,
    0.0973F, 0.0974F, 0.0975F, 0.0976F, 0.0977F, 0.0978F, 0.0979F, 0.098F,
    0.0981F, 0.0982F, 0.0983F, 0.0984F, 0.0985F, 0.0986F, 0.0987F, 0.0988F,
    0.0989F, 0.099F, 0.0991F, 0.0992F, 0.0993F, 0.0994F, 0.0995F, 0.0996F,
    0.0997F, 0.0998F, 0.0999F, 0.1F, 0.1001F, 0.1002F, 0.1003F, 0.1004F, 0.1005F,
    0.1006F, 0.1007F, 0.1008F, 0.1009F, 0.101F, 0.1011F, 0.1012F, 0.1013F,
    0.1014F, 0.1015F, 0.1016F, 0.1017F, 0.1018F, 0.1019F, 0.102F, 0.1021F,
    0.1022F, 0.1023F, 0.1024F, 0.1025F, 0.1026F, 0.1027F, 0.1028F, 0.1029F,
    0.103F, 0.1031F, 0.1032F, 0.1033F, 0.1034F, 0.1035F, 0.1036F, 0.1037F,
    0.1038F, 0.1039F, 0.104F, 0.1041F, 0.1042F, 0.1043F, 0.1044F, 0.1045F,
    0.1046F, 0.1047F, 0.1048F, 0.1049F, 0.105F, 0.1051F, 0.1052F, 0.1053F,
    0.1054F, 0.1055F, 0.1056F, 0.1057F, 0.1058F, 0.1059F, 0.106F, 0.1061F,
    0.1062F, 0.1063F, 0.1064F, 0.1065F, 0.1066F, 0.1067F, 0.1068F, 0.1069F,
    0.107F, 0.1071F, 0.1072F, 0.1073F, 0.1074F, 0.1075F, 0.1076F, 0.1077F,
    0.1078F, 0.1079F, 0.108F, 0.1081F, 0.1082F, 0.1083F, 0.1084F, 0.1085F,
    0.1086F, 0.1087F, 0.1088F, 0.1089F, 0.109F, 0.1091F, 0.1092F, 0.1093F,
    0.1094F, 0.1095F, 0.1096F, 0.1097F, 0.1098F, 0.1099F, 0.11F, 0.1101F,
    0.1102F, 0.1103F, 0.1104F, 0.1105F, 0.1106F, 0.1107F, 0.1108F, 0.1109F,
    0.111F, 0.1111F, 0.1112F, 0.1113F, 0.1114F, 0.1115F, 0.1116F, 0.1117F,
    0.1118F, 0.1119F, 0.112F, 0.1121F, 0.1122F, 0.1123F, 0.1124F, 0.1125F,
    0.1126F, 0.1127F, 0.1128F, 0.1129F, 0.113F, 0.1131F, 0.1132F, 0.1133F,
    0.1134F, 0.1135F, 0.1136F, 0.1137F, 0.1138F, 0.1139F, 0.114F, 0.1141F,
    0.1142F, 0.1143F, 0.1144F, 0.1145F, 0.1146F, 0.1147F, 0.1148F, 0.1149F,
    0.115F, 0.1151F, 0.1152F, 0.1153F, 0.1154F, 0.1155F, 0.1156F, 0.1157F,
    0.1158F, 0.1159F, 0.116F, 0.1161F, 0.1162F, 0.1163F, 0.1164F, 0.1165F,
    0.1166F, 0.1167F, 0.1168F, 0.1169F, 0.117F, 0.1171F, 0.1172F, 0.1173F,
    0.1174F, 0.1175F, 0.1176F, 0.1177F, 0.1178F, 0.1179F, 0.118F, 0.1181F,
    0.1182F, 0.1183F, 0.1184F, 0.1185F, 0.1186F, 0.1187F, 0.1188F, 0.1189F,
    0.119F, 0.1191F, 0.1192F, 0.1193F, 0.1194F, 0.1195F, 0.1196F, 0.1197F,
    0.1198F, 0.1199F, 0.12F, 0.1201F, 0.1202F, 0.1203F, 0.1204F, 0.1205F,
    0.1206F, 0.1207F, 0.1208F, 0.1209F, 0.121F, 0.1211F, 0.1212F, 0.1213F,
    0.1214F, 0.1215F, 0.1216F, 0.1217F, 0.1218F, 0.1219F, 0.122F, 0.1221F,
    0.1222F, 0.1223F, 0.1224F, 0.1225F, 0.1226F, 0.1227F, 0.1228F, 0.1229F,
    0.123F, 0.1231F, 0.1232F, 0.1233F, 0.1234F, 0.1235F, 0.1236F, 0.1237F,
    0.1238F, 0.1239F, 0.124F, 0.1241F, 0.1242F, 0.1243F, 0.1244F, 0.1245F,
    0.1246F, 0.1247F, 0.1248F, 0.1249F, 0.125F, 0.1251F, 0.1252F, 0.1253F,
    0.1254F, 0.1255F, 0.1256F, 0.1257F, 0.1258F, 0.1259F, 0.126F, 0.1261F,
    0.1262F, 0.1263F, 0.1264F, 0.1265F, 0.1266F, 0.1267F, 0.1268F, 0.1269F,
    0.127F, 0.1271F, 0.1272F, 0.1273F, 0.1274F, 0.1275F, 0.1276F, 0.1277F,
    0.1278F, 0.1279F, 0.128F, 0.1281F, 0.1282F, 0.1283F, 0.1284F, 0.1285F,
    0.1286F, 0.1287F, 0.1288F, 0.1289F, 0.129F, 0.1291F, 0.1292F, 0.1293F,
    0.1294F, 0.1295F, 0.1296F, 0.1297F, 0.1298F, 0.1299F, 0.13F, 0.1301F,
    0.1302F, 0.1303F, 0.1304F, 0.1305F, 0.1306F, 0.1307F, 0.1308F, 0.1309F,
    0.131F, 0.1311F, 0.1312F, 0.1313F, 0.1314F, 0.1315F, 0.1316F, 0.1317F,
    0.1318F, 0.1319F, 0.132F, 0.1321F, 0.1322F, 0.1323F, 0.1324F, 0.1325F,
    0.1326F, 0.1327F, 0.1328F, 0.1329F, 0.133F, 0.1331F, 0.1332F, 0.1333F,
    0.1334F, 0.1335F, 0.1336F, 0.1337F, 0.1338F, 0.1339F, 0.134F, 0.1341F,
    0.1342F, 0.1343F, 0.1344F, 0.1345F, 0.1346F, 0.1347F, 0.1348F, 0.1349F,
    0.135F, 0.1351F, 0.1352F, 0.1353F, 0.1354F, 0.1355F, 0.1356F, 0.1357F,
    0.1358F, 0.1359F, 0.136F, 0.1361F, 0.1362F, 0.1363F, 0.1364F, 0.1365F,
    0.1366F, 0.1367F, 0.1368F, 0.1369F, 0.137F, 0.1371F, 0.1372F, 0.1373F,
    0.1374F, 0.1375F, 0.1376F, 0.1377F, 0.1378F, 0.1379F, 0.138F, 0.1381F,
    0.1382F, 0.1383F, 0.1384F, 0.1385F, 0.1386F, 0.1387F, 0.1388F, 0.1389F,
    0.139F, 0.1391F, 0.1392F, 0.1393F, 0.1394F, 0.1395F, 0.1396F, 0.1397F,
    0.1398F, 0.1399F, 0.14F, 0.1401F, 0.1402F, 0.1403F, 0.1404F, 0.1405F,
    0.1406F, 0.1407F, 0.1408F, 0.1409F, 0.141F, 0.1411F, 0.1412F, 0.1413F,
    0.1414F, 0.1415F, 0.1416F, 0.1417F, 0.1418F, 0.1419F, 0.142F, 0.1421F,
    0.1422F, 0.1423F, 0.1424F, 0.1425F, 0.1426F, 0.1427F, 0.1428F, 0.1429F,
    0.143F, 0.1431F, 0.1432F, 0.1433F, 0.1434F, 0.1435F, 0.1436F, 0.1437F,
    0.1438F, 0.1439F, 0.144F, 0.1441F, 0.1442F, 0.1443F, 0.1444F, 0.1445F,
    0.1446F, 0.1447F, 0.1448F, 0.1449F, 0.145F, 0.1451F, 0.1452F, 0.1453F,
    0.1454F, 0.1455F, 0.1456F, 0.1457F, 0.1458F, 0.1459F, 0.146F, 0.1461F,
    0.1462F, 0.1463F, 0.1464F, 0.1465F, 0.1466F, 0.1467F, 0.1468F, 0.1469F,
    0.147F, 0.1471F, 0.1472F, 0.1473F, 0.1474F, 0.1475F, 0.1476F, 0.1477F,
    0.1478F, 0.1479F, 0.148F, 0.1481F, 0.1482F, 0.1483F, 0.1484F, 0.1485F,
    0.1486F, 0.1487F, 0.1488F, 0.1489F, 0.149F, 0.1491F, 0.1492F, 0.1493F,
    0.1494F, 0.1495F, 0.1496F, 0.1497F, 0.1498F, 0.1499F, 0.15F, 0.1501F,
    0.1502F, 0.1503F, 0.1504F, 0.1505F, 0.1506F, 0.1507F, 0.1508F, 0.1509F,
    0.151F, 0.1511F, 0.1512F, 0.1513F, 0.1514F, 0.1515F, 0.1516F, 0.1517F,
    0.1518F, 0.1519F, 0.152F, 0.1521F, 0.1522F, 0.1523F, 0.1524F, 0.1525F,
    0.1526F, 0.1527F, 0.1528F, 0.1529F, 0.153F, 0.1531F, 0.1532F, 0.1533F,
    0.1534F, 0.1535F, 0.1536F, 0.1537F, 0.1538F, 0.1539F, 0.154F, 0.1541F,
    0.1542F, 0.1543F, 0.1544F, 0.1545F, 0.1546F, 0.1547F, 0.1548F, 0.1549F,
    0.155F, 0.1551F, 0.1552F, 0.1553F, 0.1554F, 0.1555F, 0.1556F, 0.1557F,
    0.1558F, 0.1559F, 0.156F, 0.1561F, 0.1562F, 0.1563F, 0.1564F, 0.1565F,
    0.1566F, 0.1567F, 0.1568F, 0.1569F, 0.157F, 0.1571F, 0.1572F, 0.1573F,
    0.1574F, 0.1575F, 0.1576F, 0.1577F, 0.1578F, 0.1579F, 0.158F, 0.1581F,
    0.1582F, 0.1583F, 0.1584F, 0.1585F, 0.1586F, 0.1587F, 0.1588F, 0.1589F,
    0.159F, 0.1591F, 0.1592F, 0.1593F, 0.1594F, 0.1595F, 0.1596F, 0.1597F,
    0.1598F, 0.1599F, 0.16F, 0.1601F, 0.1602F, 0.1603F, 0.1604F, 0.1605F,
    0.1606F, 0.1607F, 0.1608F, 0.1609F, 0.161F, 0.1611F, 0.1612F, 0.1613F,
    0.1614F, 0.1615F, 0.1616F, 0.1617F, 0.1618F, 0.1619F, 0.162F, 0.1621F,
    0.1622F, 0.1623F, 0.1624F, 0.1625F, 0.1626F, 0.1627F, 0.1628F, 0.1629F,
    0.163F, 0.1631F, 0.1632F, 0.1633F, 0.1634F, 0.1635F, 0.1636F, 0.1637F,
    0.1638F, 0.1639F, 0.164F, 0.1641F, 0.1642F, 0.1643F, 0.1644F, 0.1645F,
    0.1646F, 0.1647F, 0.1648F, 0.1649F, 0.165F, 0.1651F, 0.1652F, 0.1653F,
    0.1654F, 0.1655F, 0.1656F, 0.1657F, 0.1658F, 0.1659F, 0.166F, 0.1661F,
    0.1662F, 0.1663F, 0.1664F, 0.1665F, 0.1666F, 0.1667F, 0.1668F, 0.1669F,
    0.167F, 0.1671F, 0.1672F, 0.1673F, 0.1674F, 0.1675F, 0.1676F, 0.1677F,
    0.1678F, 0.1679F, 0.168F, 0.1681F, 0.1682F, 0.1683F, 0.1684F, 0.1685F,
    0.1686F, 0.1687F, 0.1688F, 0.1689F, 0.169F, 0.1691F, 0.1692F, 0.1693F,
    0.1694F, 0.1695F, 0.1696F, 0.1697F, 0.1698F, 0.1699F, 0.17F, 0.1701F,
    0.1702F, 0.1703F, 0.1704F, 0.1705F, 0.1706F, 0.1707F, 0.1708F, 0.1709F,
    0.171F, 0.1711F, 0.1712F, 0.1713F, 0.1714F, 0.1715F, 0.1716F, 0.1717F,
    0.1718F, 0.1719F, 0.172F, 0.1721F, 0.1722F, 0.1723F, 0.1724F, 0.1725F,
    0.1726F, 0.1727F, 0.1728F, 0.1729F, 0.173F, 0.1731F, 0.1732F, 0.1733F,
    0.1734F, 0.1735F, 0.1736F, 0.1737F, 0.1738F, 0.1739F, 0.174F, 0.1741F,
    0.1742F, 0.1743F, 0.1744F, 0.1745F, 0.1746F, 0.1747F, 0.1748F, 0.1749F,
    0.175F, 0.1751F, 0.1752F, 0.1753F, 0.1754F, 0.1755F, 0.1756F, 0.1757F,
    0.1758F, 0.1759F, 0.176F, 0.1761F, 0.1762F, 0.1763F, 0.1764F, 0.1765F,
    0.1766F, 0.1767F, 0.1768F, 0.1769F, 0.177F, 0.1771F, 0.1772F, 0.1773F,
    0.1774F, 0.1775F, 0.1776F, 0.1777F, 0.1778F, 0.1779F, 0.178F, 0.1781F,
    0.1782F, 0.1783F, 0.1784F, 0.1785F, 0.1786F, 0.1787F, 0.1788F, 0.1789F,
    0.179F, 0.1791F, 0.1792F, 0.1793F, 0.1794F, 0.1795F, 0.1796F, 0.1797F,
    0.1798F, 0.1799F, 0.18F, 0.1801F, 0.1802F, 0.1803F, 0.1804F, 0.1805F,
    0.1806F, 0.1807F, 0.1808F, 0.1809F, 0.181F, 0.1811F, 0.1812F, 0.1813F,
    0.1814F, 0.1815F, 0.1816F, 0.1817F, 0.1818F, 0.1819F, 0.182F, 0.1821F,
    0.1822F, 0.1823F, 0.1824F, 0.1825F, 0.1826F, 0.1827F, 0.1828F, 0.1829F,
    0.183F, 0.1831F, 0.1832F, 0.1833F, 0.1834F, 0.1835F, 0.1836F, 0.1837F,
    0.1838F, 0.1839F, 0.184F, 0.1841F, 0.1842F, 0.1843F, 0.1844F, 0.1845F,
    0.1846F, 0.1847F, 0.1848F, 0.1849F, 0.185F, 0.1851F, 0.1852F, 0.1853F,
    0.1854F, 0.1855F, 0.1856F, 0.1857F, 0.1858F, 0.1859F, 0.186F, 0.1861F,
    0.1862F, 0.1863F, 0.1864F, 0.1865F, 0.1866F, 0.1867F, 0.1868F, 0.1869F,
    0.187F, 0.1871F, 0.1872F, 0.1873F, 0.1874F, 0.1875F, 0.1876F, 0.1877F,
    0.1878F, 0.1879F, 0.188F, 0.1881F, 0.1882F, 0.1883F, 0.1884F, 0.1885F,
    0.1886F, 0.1887F, 0.1888F, 0.1889F, 0.189F, 0.1891F, 0.1892F, 0.1893F,
    0.1894F, 0.1895F, 0.1896F, 0.1897F, 0.1898F, 0.1899F, 0.19F, 0.1901F,
    0.1902F, 0.1903F, 0.1904F, 0.1905F, 0.1906F, 0.1907F, 0.1908F, 0.1909F,
    0.191F, 0.1911F, 0.1912F, 0.1913F, 0.1914F, 0.1915F, 0.1916F, 0.1917F,
    0.1918F, 0.1919F, 0.192F, 0.1921F, 0.1922F, 0.1923F, 0.1924F, 0.1925F,
    0.1926F, 0.1927F, 0.1928F, 0.1929F, 0.193F, 0.1931F, 0.1932F, 0.1933F,
    0.1934F, 0.1935F, 0.1936F, 0.1937F, 0.1938F, 0.1939F, 0.194F, 0.1941F,
    0.1942F, 0.1943F, 0.1944F, 0.1945F, 0.1946F, 0.1947F, 0.1948F, 0.1949F,
    0.195F, 0.1951F, 0.1952F, 0.1953F, 0.1954F, 0.1955F, 0.1956F, 0.1957F,
    0.1958F, 0.1959F, 0.196F, 0.1961F, 0.1962F, 0.1963F, 0.1964F, 0.1965F,
    0.1966F, 0.1967F, 0.1968F, 0.1969F, 0.197F, 0.1971F, 0.1972F, 0.1973F,
    0.1974F, 0.1975F, 0.1976F, 0.1977F, 0.1978F, 0.1979F, 0.198F, 0.1981F,
    0.1982F, 0.1983F, 0.1984F, 0.1985F, 0.1986F, 0.1987F, 0.1988F, 0.1989F,
    0.199F, 0.1991F, 0.1992F, 0.1993F, 0.1994F, 0.1995F, 0.1996F, 0.1997F,
    0.1998F, 0.1999F, 0.2F, 0.2001F, 0.2002F, 0.2003F, 0.2004F, 0.2005F, 0.2006F,
    0.2007F, 0.2008F, 0.2009F, 0.201F, 0.2011F, 0.2012F, 0.2013F, 0.2014F,
    0.2015F, 0.2016F, 0.2017F, 0.2018F, 0.2019F, 0.202F, 0.2021F, 0.2022F,
    0.2023F, 0.2024F, 0.2025F, 0.2026F, 0.2027F, 0.2028F, 0.2029F, 0.203F,
    0.2031F, 0.2032F, 0.2033F, 0.2034F, 0.2035F, 0.2036F, 0.2037F, 0.2038F,
    0.2039F, 0.204F, 0.2041F, 0.2042F, 0.2043F, 0.2044F, 0.2045F, 0.2046F,
    0.2047F, 0.2048F, 0.2049F, 0.205F, 0.2051F, 0.2052F, 0.2053F, 0.2054F,
    0.2055F, 0.2056F, 0.2057F, 0.2058F, 0.2059F, 0.206F, 0.2061F, 0.2062F,
    0.2063F, 0.2064F, 0.2065F, 0.2066F, 0.2067F, 0.2068F, 0.2069F, 0.207F,
    0.2071F, 0.2072F, 0.2073F, 0.2074F, 0.2075F, 0.2076F, 0.2077F, 0.2078F,
    0.2079F, 0.208F, 0.2081F, 0.2082F, 0.2083F, 0.2084F, 0.2085F, 0.2086F,
    0.2087F, 0.2088F, 0.2089F, 0.209F, 0.2091F, 0.2092F, 0.2093F, 0.2094F,
    0.2095F, 0.2096F, 0.2097F, 0.2098F, 0.2099F, 0.21F, 0.2101F, 0.2102F,
    0.2103F, 0.2104F, 0.2105F, 0.2106F, 0.2107F, 0.2108F, 0.2109F, 0.211F,
    0.2111F, 0.2112F, 0.2113F, 0.2114F, 0.2115F, 0.2116F, 0.2117F, 0.2118F,
    0.2119F, 0.212F, 0.2121F, 0.2122F, 0.2123F, 0.2124F, 0.2125F, 0.2126F,
    0.2127F, 0.2128F, 0.2129F, 0.213F, 0.2131F, 0.2132F, 0.2133F, 0.2134F,
    0.2135F, 0.2136F, 0.2137F, 0.2138F, 0.2139F, 0.214F, 0.2141F, 0.2142F,
    0.2143F, 0.2144F, 0.2145F, 0.2146F, 0.2147F, 0.2148F, 0.2149F, 0.215F,
    0.2151F, 0.2152F, 0.2153F, 0.2154F, 0.2155F, 0.2156F, 0.2157F, 0.2158F,
    0.2159F, 0.216F, 0.2161F, 0.2162F, 0.2163F, 0.2164F, 0.2165F, 0.2166F,
    0.2167F, 0.2168F, 0.2169F, 0.217F, 0.2171F, 0.2172F, 0.2173F, 0.2174F,
    0.2175F, 0.2176F, 0.2177F, 0.2178F, 0.2179F, 0.218F, 0.2181F, 0.2182F,
    0.2183F, 0.2184F, 0.2185F, 0.2186F, 0.2187F, 0.2188F, 0.2189F, 0.219F,
    0.2191F, 0.2192F, 0.2193F, 0.2194F, 0.2195F, 0.2196F, 0.2197F, 0.2198F,
    0.2199F, 0.22F, 0.2201F, 0.2202F, 0.2203F, 0.2204F, 0.2205F, 0.2206F,
    0.2207F, 0.2208F, 0.2209F, 0.221F, 0.2211F, 0.2212F, 0.2213F, 0.2214F,
    0.2215F, 0.2216F, 0.2217F, 0.2218F, 0.2219F, 0.222F, 0.2221F, 0.2222F,
    0.2223F, 0.2224F, 0.2225F, 0.2226F, 0.2227F, 0.2228F, 0.2229F, 0.223F,
    0.2231F, 0.2232F, 0.2233F, 0.2234F, 0.2235F, 0.2236F, 0.2237F, 0.2238F,
    0.2239F, 0.224F, 0.2241F, 0.2242F, 0.2243F, 0.2244F, 0.2245F, 0.2246F,
    0.2247F, 0.2248F, 0.2249F, 0.225F, 0.2251F, 0.2252F, 0.2253F, 0.2254F,
    0.2255F, 0.2256F, 0.2257F, 0.2258F, 0.2259F, 0.226F, 0.2261F, 0.2262F,
    0.2263F, 0.2264F, 0.2265F, 0.2266F, 0.2267F, 0.2268F, 0.2269F, 0.227F,
    0.2271F, 0.2272F, 0.2273F, 0.2274F, 0.2275F, 0.2276F, 0.2277F, 0.2278F,
    0.2279F, 0.228F, 0.2281F, 0.2282F, 0.2283F, 0.2284F, 0.2285F, 0.2286F,
    0.2287F, 0.2288F, 0.2289F, 0.229F, 0.2291F, 0.2292F, 0.2293F, 0.2294F,
    0.2295F, 0.2296F, 0.2297F, 0.2298F, 0.2299F, 0.23F, 0.2301F, 0.2302F,
    0.2303F, 0.2304F, 0.2305F, 0.2306F, 0.2307F, 0.2308F, 0.2309F, 0.231F,
    0.2311F, 0.2312F, 0.2313F, 0.2314F, 0.2315F, 0.2316F, 0.2317F, 0.2318F,
    0.2319F, 0.232F, 0.2321F, 0.2322F, 0.2323F, 0.2324F, 0.2325F, 0.2326F,
    0.2327F, 0.2328F, 0.2329F, 0.233F, 0.2331F, 0.2332F, 0.2333F, 0.2334F,
    0.2335F, 0.2336F, 0.2337F, 0.2338F, 0.2339F, 0.234F, 0.2341F, 0.2342F,
    0.2343F, 0.2344F, 0.2345F, 0.2346F, 0.2347F, 0.2348F, 0.2349F, 0.235F,
    0.2351F, 0.2352F, 0.2353F, 0.2354F, 0.2355F, 0.2356F, 0.2357F, 0.2358F,
    0.2359F, 0.236F, 0.2361F, 0.2362F, 0.2363F, 0.2364F, 0.2365F, 0.2366F,
    0.2367F, 0.2368F, 0.2369F, 0.237F, 0.2371F, 0.2372F, 0.2373F, 0.2374F,
    0.2375F, 0.2376F, 0.2377F, 0.2378F, 0.2379F, 0.238F, 0.2381F, 0.2382F,
    0.2383F, 0.2384F, 0.2385F, 0.2386F, 0.2387F, 0.2388F, 0.2389F, 0.239F,
    0.2391F, 0.2392F, 0.2393F, 0.2394F, 0.2395F, 0.2396F, 0.2397F, 0.2398F,
    0.2399F, 0.24F, 0.2401F, 0.2402F, 0.2403F, 0.2404F, 0.2405F, 0.2406F,
    0.2407F, 0.2408F, 0.2409F, 0.241F, 0.2411F, 0.2412F, 0.2413F, 0.2414F,
    0.2415F, 0.2416F, 0.2417F, 0.2418F, 0.2419F, 0.242F, 0.2421F, 0.2422F,
    0.2423F, 0.2424F, 0.2425F, 0.2426F, 0.2427F, 0.2428F, 0.2429F, 0.243F,
    0.2431F, 0.2432F, 0.2433F, 0.2434F, 0.2435F, 0.2436F, 0.2437F, 0.2438F,
    0.2439F, 0.244F, 0.2441F, 0.2442F, 0.2443F, 0.2444F, 0.2445F, 0.2446F,
    0.2447F, 0.2448F, 0.2449F, 0.245F, 0.2451F, 0.2452F, 0.2453F, 0.2454F,
    0.2455F, 0.2456F, 0.2457F, 0.2458F, 0.2459F, 0.246F, 0.2461F, 0.2462F,
    0.2463F, 0.2464F, 0.2465F, 0.2466F, 0.2467F, 0.2468F, 0.2469F, 0.247F,
    0.2471F, 0.2472F, 0.2473F, 0.2474F, 0.2475F, 0.2476F, 0.2477F, 0.2478F,
    0.2479F, 0.248F, 0.2481F, 0.2482F, 0.2483F, 0.2484F, 0.2485F, 0.2486F,
    0.2487F, 0.2488F, 0.2489F, 0.249F, 0.2491F, 0.2492F, 0.2493F, 0.2494F,
    0.2495F, 0.2496F, 0.2497F, 0.2498F, 0.2499F, 0.25F, 0.2501F, 0.2502F,
    0.2503F, 0.2504F, 0.2505F, 0.2506F, 0.2507F, 0.2508F, 0.2509F, 0.251F,
    0.2511F, 0.2512F, 0.2513F, 0.2514F, 0.2515F, 0.2516F, 0.2517F, 0.2518F,
    0.2519F, 0.252F, 0.2521F, 0.2522F, 0.2523F, 0.2524F, 0.2525F, 0.2526F,
    0.2527F, 0.2528F, 0.2529F, 0.253F, 0.2531F, 0.2532F, 0.2533F, 0.2534F,
    0.2535F, 0.2536F, 0.2537F, 0.2538F, 0.2539F, 0.254F, 0.2541F, 0.2542F,
    0.2543F, 0.2544F, 0.2545F, 0.2546F, 0.2547F, 0.2548F, 0.2549F, 0.255F,
    0.2551F, 0.2552F, 0.2553F, 0.2554F, 0.2555F, 0.2556F, 0.2557F, 0.2558F,
    0.2559F, 0.256F, 0.2561F, 0.2562F, 0.2563F, 0.2564F, 0.2565F, 0.2566F,
    0.2567F, 0.2568F, 0.2569F, 0.257F, 0.2571F, 0.2572F, 0.2573F, 0.2574F,
    0.2575F, 0.2576F, 0.2577F, 0.2578F, 0.2579F, 0.258F, 0.2581F, 0.2582F,
    0.2583F, 0.2584F, 0.2585F, 0.2586F, 0.2587F, 0.2588F, 0.2589F, 0.259F,
    0.2591F, 0.2592F, 0.2593F, 0.2594F, 0.2595F, 0.2596F, 0.2597F, 0.2598F,
    0.2599F, 0.26F, 0.2601F, 0.2602F, 0.2603F, 0.2604F, 0.2605F, 0.2606F,
    0.2607F, 0.2608F, 0.2609F, 0.261F, 0.2611F, 0.2612F, 0.2613F, 0.2614F,
    0.2615F, 0.2616F, 0.2617F, 0.2618F, 0.2619F, 0.262F, 0.2621F, 0.2622F,
    0.2623F, 0.2624F, 0.2625F, 0.2626F, 0.2627F, 0.2628F, 0.2629F, 0.263F,
    0.2631F, 0.2632F, 0.2633F, 0.2634F, 0.2635F, 0.2636F, 0.2637F, 0.2638F,
    0.2639F, 0.264F, 0.2641F, 0.2642F, 0.2643F, 0.2644F, 0.2645F, 0.2646F,
    0.2647F, 0.2648F, 0.2649F, 0.265F, 0.2651F, 0.2652F, 0.2653F, 0.2654F,
    0.2655F, 0.2656F, 0.2657F, 0.2658F, 0.2659F, 0.266F, 0.2661F, 0.2662F,
    0.2663F, 0.2664F, 0.2665F, 0.2666F, 0.2667F, 0.2668F, 0.2669F, 0.267F,
    0.2671F, 0.2672F, 0.2673F, 0.2674F, 0.2675F, 0.2676F, 0.2677F, 0.2678F,
    0.2679F, 0.268F, 0.2681F, 0.2682F, 0.2683F, 0.2684F, 0.2685F, 0.2686F,
    0.2687F, 0.2688F, 0.2689F, 0.269F, 0.2691F, 0.2692F, 0.2693F, 0.2694F,
    0.2695F, 0.2696F, 0.2697F, 0.2698F, 0.2699F, 0.27F, 0.2701F, 0.2702F,
    0.2703F, 0.2704F, 0.2705F, 0.2706F, 0.2707F, 0.2708F, 0.2709F, 0.271F,
    0.2711F, 0.2712F, 0.2713F, 0.2714F, 0.2715F, 0.2716F, 0.2717F, 0.2718F,
    0.2719F, 0.272F, 0.2721F, 0.2722F, 0.2723F, 0.2724F, 0.2725F, 0.2726F,
    0.2727F, 0.2728F, 0.2729F, 0.273F, 0.2731F, 0.2732F, 0.2733F, 0.2734F,
    0.2735F, 0.2736F, 0.2737F, 0.2738F, 0.2739F, 0.274F, 0.2741F, 0.2742F,
    0.2743F, 0.2744F, 0.2745F, 0.2746F, 0.2747F, 0.2748F, 0.2749F, 0.275F,
    0.2751F, 0.2752F, 0.2753F, 0.2754F, 0.2755F, 0.2756F, 0.2757F, 0.2758F,
    0.2759F, 0.276F, 0.2761F, 0.2762F, 0.2763F, 0.2764F, 0.2765F, 0.2766F,
    0.2767F, 0.2768F, 0.2769F, 0.277F, 0.2771F, 0.2772F, 0.2773F, 0.2774F,
    0.2775F, 0.2776F, 0.2777F, 0.2778F, 0.2779F, 0.278F, 0.2781F, 0.2782F,
    0.2783F, 0.2784F, 0.2785F, 0.2786F, 0.2787F, 0.2788F, 0.2789F, 0.279F,
    0.2791F, 0.2792F, 0.2793F, 0.2794F, 0.2795F, 0.2796F, 0.2797F, 0.2798F,
    0.2799F, 0.28F, 0.2801F, 0.2802F, 0.2803F, 0.2804F, 0.2805F, 0.2806F,
    0.2807F, 0.2808F, 0.2809F, 0.281F, 0.2811F, 0.2812F, 0.2813F, 0.2814F,
    0.2815F, 0.2816F, 0.2817F, 0.2818F, 0.2819F, 0.282F, 0.2821F, 0.2822F,
    0.2823F, 0.2824F, 0.2825F, 0.2826F, 0.2827F, 0.2828F, 0.2829F, 0.283F,
    0.2831F, 0.2832F, 0.2833F, 0.2834F, 0.2835F, 0.2836F, 0.2837F, 0.2838F,
    0.2839F, 0.284F, 0.2841F, 0.2842F, 0.2843F, 0.2844F, 0.2845F, 0.2846F,
    0.2847F, 0.2848F, 0.2849F, 0.285F, 0.2851F, 0.2852F, 0.2853F, 0.2854F,
    0.2855F, 0.2856F, 0.2857F, 0.2858F, 0.2859F, 0.286F, 0.2861F, 0.2862F,
    0.2863F, 0.2864F, 0.2865F, 0.2866F, 0.2867F, 0.2868F, 0.2869F, 0.287F,
    0.2871F, 0.2872F, 0.2873F, 0.2874F, 0.2875F, 0.2876F, 0.2877F, 0.2878F,
    0.2879F, 0.288F, 0.2881F, 0.2882F, 0.2883F, 0.2884F, 0.2885F, 0.2886F,
    0.2887F, 0.2888F, 0.2889F, 0.289F, 0.2891F, 0.2892F, 0.2893F, 0.2894F,
    0.2895F, 0.2896F, 0.2897F, 0.2898F, 0.2899F, 0.29F, 0.2901F, 0.2902F,
    0.2903F, 0.2904F, 0.2905F, 0.2906F, 0.2907F, 0.2908F, 0.2909F, 0.291F,
    0.2911F, 0.2912F, 0.2913F, 0.2914F, 0.2915F, 0.2916F, 0.2917F, 0.2918F,
    0.2919F, 0.292F, 0.2921F, 0.2922F, 0.2923F, 0.2924F, 0.2925F, 0.2926F,
    0.2927F, 0.2928F, 0.2929F, 0.293F, 0.2931F, 0.2932F, 0.2933F, 0.2934F,
    0.2935F, 0.2936F, 0.2937F, 0.2938F, 0.2939F, 0.294F, 0.2941F, 0.2942F,
    0.2943F, 0.2944F, 0.2945F, 0.2946F, 0.2947F, 0.2948F, 0.2949F, 0.295F,
    0.2951F, 0.2952F, 0.2953F, 0.2954F, 0.2955F, 0.2956F, 0.2957F, 0.2958F,
    0.2959F, 0.296F, 0.2961F, 0.2962F, 0.2963F, 0.2964F, 0.2965F, 0.2966F,
    0.2967F, 0.2968F, 0.2969F, 0.297F, 0.2971F, 0.2972F, 0.2973F, 0.2974F,
    0.2975F, 0.2976F, 0.2977F, 0.2978F, 0.2979F, 0.298F, 0.2981F, 0.2982F,
    0.2983F, 0.2984F, 0.2985F, 0.2986F, 0.2987F, 0.2988F, 0.2989F, 0.299F,
    0.2991F, 0.2992F, 0.2993F, 0.2994F, 0.2995F, 0.2996F, 0.2997F, 0.2998F,
    0.2999F, 0.3F, 0.3001F, 0.3002F, 0.3003F, 0.3004F, 0.3005F, 0.3006F, 0.3007F,
    0.3008F, 0.3009F, 0.301F, 0.3011F, 0.3012F, 0.3013F, 0.3014F, 0.3015F,
    0.3016F, 0.3017F, 0.3018F, 0.3019F, 0.302F, 0.3021F, 0.3022F, 0.3023F,
    0.3024F, 0.3025F, 0.3026F, 0.3027F, 0.3028F, 0.3029F, 0.303F, 0.3031F,
    0.3032F, 0.3033F, 0.3034F, 0.3035F, 0.3036F, 0.3037F, 0.3038F, 0.3039F,
    0.304F, 0.3041F, 0.3042F, 0.3043F, 0.3044F, 0.3045F, 0.3046F, 0.3047F,
    0.3048F, 0.3049F, 0.305F, 0.3051F, 0.3052F, 0.3053F, 0.3054F, 0.3055F,
    0.3056F, 0.3057F, 0.3058F, 0.3059F, 0.306F, 0.3061F, 0.3062F, 0.3063F,
    0.3064F, 0.3065F, 0.3066F, 0.3067F, 0.3068F, 0.3069F, 0.307F, 0.3071F,
    0.3072F, 0.3073F, 0.3074F, 0.3075F, 0.3076F, 0.3077F, 0.3078F, 0.3079F,
    0.308F, 0.3081F, 0.3082F, 0.3083F, 0.3084F, 0.3085F, 0.3086F, 0.3087F,
    0.3088F, 0.3089F, 0.309F, 0.3091F, 0.3092F, 0.3093F, 0.3094F, 0.3095F,
    0.3096F, 0.3097F, 0.3098F, 0.3099F, 0.31F, 0.3101F, 0.3102F, 0.3103F,
    0.3104F, 0.3105F, 0.3106F, 0.3107F, 0.3108F, 0.3109F, 0.311F, 0.3111F,
    0.3112F, 0.3113F, 0.3114F, 0.3115F, 0.3116F, 0.3117F, 0.3118F, 0.3119F,
    0.312F, 0.3121F, 0.3122F, 0.3123F, 0.3124F, 0.3125F, 0.3126F, 0.3127F,
    0.3128F, 0.3129F, 0.313F, 0.3131F, 0.3132F, 0.3133F, 0.3134F, 0.3135F,
    0.3136F, 0.3137F, 0.3138F, 0.3139F, 0.314F, 0.3141F, 0.3142F, 0.3143F,
    0.3144F, 0.3145F, 0.3146F, 0.3147F, 0.3148F, 0.3149F, 0.315F, 0.3151F,
    0.3152F, 0.3153F, 0.3154F, 0.3155F, 0.3156F, 0.3157F, 0.3158F, 0.3159F,
    0.316F, 0.3161F, 0.3162F, 0.3163F, 0.3164F, 0.3165F, 0.3166F, 0.3167F,
    0.3168F, 0.3169F, 0.317F, 0.3171F, 0.3172F, 0.3173F, 0.3174F, 0.3175F,
    0.3176F, 0.3177F, 0.3178F, 0.3179F, 0.318F, 0.3181F, 0.3182F, 0.3183F,
    0.3184F, 0.3185F, 0.3186F, 0.3187F, 0.3188F, 0.3189F, 0.319F, 0.3191F,
    0.3192F, 0.3193F, 0.3194F, 0.3195F, 0.3196F, 0.3197F, 0.3198F, 0.3199F,
    0.32F, 0.3201F, 0.3202F, 0.3203F, 0.3204F, 0.3205F, 0.3206F, 0.3207F,
    0.3208F, 0.3209F, 0.321F, 0.3211F, 0.3212F, 0.3213F, 0.3214F, 0.3215F,
    0.3216F, 0.3217F, 0.3218F, 0.3219F, 0.322F, 0.3221F, 0.3222F, 0.3223F,
    0.3224F, 0.3225F, 0.3226F, 0.3227F, 0.3228F, 0.3229F, 0.323F, 0.3231F,
    0.3232F, 0.3233F, 0.3234F, 0.3235F, 0.3236F, 0.3237F, 0.3238F, 0.3239F,
    0.324F, 0.3241F, 0.3242F, 0.3243F, 0.3244F, 0.3245F, 0.3246F, 0.3247F,
    0.3248F, 0.3249F, 0.325F, 0.3251F, 0.3252F, 0.3253F, 0.3254F, 0.3255F,
    0.3256F, 0.3257F, 0.3258F, 0.3259F, 0.326F, 0.3261F, 0.3262F, 0.3263F,
    0.3264F, 0.3265F, 0.3266F, 0.3267F, 0.3268F, 0.3269F, 0.327F, 0.3271F,
    0.3272F, 0.3273F, 0.3274F, 0.3275F, 0.3276F, 0.3277F, 0.3278F, 0.3279F,
    0.328F, 0.3281F, 0.3282F, 0.3283F, 0.3284F, 0.3285F, 0.3286F, 0.3287F,
    0.3288F, 0.3289F, 0.329F, 0.3291F, 0.3292F, 0.3293F, 0.3294F, 0.3295F,
    0.3296F, 0.3297F, 0.3298F, 0.3299F, 0.33F, 0.3301F, 0.3302F, 0.3303F,
    0.3304F, 0.3305F, 0.3306F, 0.3307F, 0.3308F, 0.3309F, 0.331F, 0.3311F,
    0.3312F, 0.3313F, 0.3314F, 0.3315F, 0.3316F, 0.3317F, 0.3318F, 0.3319F,
    0.332F, 0.3321F, 0.3322F, 0.3323F, 0.3324F, 0.3325F, 0.3326F, 0.3327F,
    0.3328F, 0.3329F, 0.333F, 0.3331F, 0.3332F, 0.3333F, 0.3334F, 0.3335F,
    0.3336F, 0.3337F, 0.3338F, 0.3339F, 0.334F, 0.3341F, 0.3342F, 0.3343F,
    0.3344F, 0.3345F, 0.3346F, 0.3347F, 0.3348F, 0.3349F, 0.335F, 0.3351F,
    0.3352F, 0.3353F, 0.3354F, 0.3355F, 0.3356F, 0.3357F, 0.3358F, 0.3359F,
    0.336F, 0.3361F, 0.3362F, 0.3363F, 0.3364F, 0.3365F, 0.3366F, 0.3367F,
    0.3368F, 0.3369F, 0.337F, 0.3371F, 0.3372F, 0.3373F, 0.3374F, 0.3375F,
    0.3376F, 0.3377F, 0.3378F, 0.3379F, 0.338F, 0.3381F, 0.3382F, 0.3383F,
    0.3384F, 0.3385F, 0.3386F, 0.3387F, 0.3388F, 0.3389F, 0.339F, 0.3391F,
    0.3392F, 0.3393F, 0.3394F, 0.3395F, 0.3396F, 0.3397F, 0.3398F, 0.3399F,
    0.34F, 0.3401F, 0.3402F, 0.3403F, 0.3404F, 0.3405F, 0.3406F, 0.3407F,
    0.3408F, 0.3409F, 0.341F, 0.3411F, 0.3412F, 0.3413F, 0.3414F, 0.3415F,
    0.3416F, 0.3417F, 0.3418F, 0.3419F, 0.342F, 0.3421F, 0.3422F, 0.3423F,
    0.3424F, 0.3425F, 0.3426F, 0.3427F, 0.3428F, 0.3429F, 0.343F, 0.3431F,
    0.3432F, 0.3433F, 0.3434F, 0.3435F, 0.3436F, 0.3437F, 0.3438F, 0.3439F,
    0.344F, 0.3441F, 0.3442F, 0.3443F, 0.3444F, 0.3445F, 0.3446F, 0.3447F,
    0.3448F, 0.3449F, 0.345F, 0.3451F, 0.3452F, 0.3453F, 0.3454F, 0.3455F,
    0.3456F, 0.3457F, 0.3458F, 0.3459F, 0.346F, 0.3461F, 0.3462F, 0.3463F,
    0.3464F, 0.3465F, 0.3466F, 0.3467F, 0.3468F, 0.3469F, 0.347F, 0.3471F,
    0.3472F, 0.3473F, 0.3474F, 0.3475F, 0.3476F, 0.3477F, 0.3478F, 0.3479F,
    0.348F, 0.3481F, 0.3482F, 0.3483F, 0.3484F, 0.3485F, 0.3486F, 0.3487F,
    0.3488F, 0.3489F, 0.349F, 0.3491F, 0.3492F, 0.3493F, 0.3494F, 0.3495F,
    0.3496F, 0.3497F, 0.3498F, 0.3499F, 0.35F, 0.3501F, 0.3502F, 0.3503F,
    0.3504F, 0.3505F, 0.3506F, 0.3507F, 0.3508F, 0.3509F, 0.351F, 0.3511F,
    0.3512F, 0.3513F, 0.3514F, 0.3515F, 0.3516F, 0.3517F, 0.3518F, 0.3519F,
    0.352F, 0.3521F, 0.3522F, 0.3523F, 0.3524F, 0.3525F, 0.3526F, 0.3527F,
    0.3528F, 0.3529F, 0.353F, 0.3531F, 0.3532F, 0.3533F, 0.3534F, 0.3535F,
    0.3536F, 0.3537F, 0.3538F, 0.3539F, 0.354F, 0.3541F, 0.3542F, 0.3543F,
    0.3544F, 0.3545F, 0.3546F, 0.3547F, 0.3548F, 0.3549F, 0.355F, 0.3551F,
    0.3552F, 0.3553F, 0.3554F, 0.3555F, 0.3556F, 0.3557F, 0.3558F, 0.3559F,
    0.356F, 0.3561F, 0.3562F, 0.3563F, 0.3564F, 0.3565F, 0.3566F, 0.3567F,
    0.3568F, 0.3569F, 0.357F, 0.3571F, 0.3572F, 0.3573F, 0.3574F, 0.3575F,
    0.3576F, 0.3577F, 0.3578F, 0.3579F, 0.358F, 0.3581F, 0.3582F, 0.3583F,
    0.3584F, 0.3585F, 0.3586F, 0.3587F, 0.3588F, 0.3589F, 0.359F, 0.3591F,
    0.3592F, 0.3593F, 0.3594F, 0.3595F, 0.3596F, 0.3597F, 0.3598F, 0.3599F,
    0.36F, 0.3601F, 0.3602F, 0.3603F, 0.3604F, 0.3605F, 0.3606F, 0.3607F,
    0.3608F, 0.3609F, 0.361F, 0.3611F, 0.3612F, 0.3613F, 0.3614F, 0.3615F,
    0.3616F, 0.3617F, 0.3618F, 0.3619F, 0.362F, 0.3621F, 0.3622F, 0.3623F,
    0.3624F, 0.3625F, 0.3626F, 0.3627F, 0.3628F, 0.3629F, 0.363F, 0.3631F,
    0.3632F, 0.3633F, 0.3634F, 0.3635F, 0.3636F, 0.3637F, 0.3638F, 0.3639F,
    0.364F, 0.3641F, 0.3642F, 0.3643F, 0.3644F, 0.3645F, 0.3646F, 0.3647F,
    0.3648F, 0.3649F, 0.365F, 0.3651F, 0.3652F, 0.3653F, 0.3654F, 0.3655F,
    0.3656F, 0.3657F, 0.3658F, 0.3659F, 0.366F, 0.3661F, 0.3662F, 0.3663F,
    0.3664F, 0.3665F, 0.3666F, 0.3667F, 0.3668F, 0.3669F, 0.367F, 0.3671F,
    0.3672F, 0.3673F, 0.3674F, 0.3675F, 0.3676F, 0.3677F, 0.3678F, 0.3679F,
    0.368F, 0.3681F, 0.3682F, 0.3683F, 0.3684F, 0.3685F, 0.3686F, 0.3687F,
    0.3688F, 0.3689F, 0.369F, 0.3691F, 0.3692F, 0.3693F, 0.3694F, 0.3695F,
    0.3696F, 0.3697F, 0.3698F, 0.3699F, 0.37F, 0.3701F, 0.3702F, 0.3703F,
    0.3704F, 0.3705F, 0.3706F, 0.3707F, 0.3708F, 0.3709F, 0.371F, 0.3711F,
    0.3712F, 0.3713F, 0.3714F, 0.3715F, 0.3716F, 0.3717F, 0.3718F, 0.3719F,
    0.372F, 0.3721F, 0.3722F, 0.3723F, 0.3724F, 0.3725F, 0.3726F, 0.3727F,
    0.3728F, 0.3729F, 0.373F, 0.3731F, 0.3732F, 0.3733F, 0.3734F, 0.3735F,
    0.3736F, 0.3737F, 0.3738F, 0.3739F, 0.374F, 0.3741F, 0.3742F, 0.3743F,
    0.3744F, 0.3745F, 0.3746F, 0.3747F, 0.3748F, 0.3749F, 0.375F, 0.3751F,
    0.3752F, 0.3753F, 0.3754F, 0.3755F, 0.3756F, 0.3757F, 0.3758F, 0.3759F,
    0.376F, 0.3761F, 0.3762F, 0.3763F, 0.3764F, 0.3765F, 0.3766F, 0.3767F,
    0.3768F, 0.3769F, 0.377F, 0.3771F, 0.3772F, 0.3773F, 0.3774F, 0.3775F,
    0.3776F, 0.3777F, 0.3778F, 0.3779F, 0.378F, 0.3781F, 0.3782F, 0.3783F,
    0.3784F, 0.3785F, 0.3786F, 0.3787F, 0.3788F, 0.3789F, 0.379F, 0.3791F,
    0.3792F, 0.3793F, 0.3794F, 0.3795F, 0.3796F, 0.3797F, 0.3798F, 0.3799F,
    0.38F, 0.3801F, 0.3802F, 0.3803F, 0.3804F, 0.3805F, 0.3806F, 0.3807F,
    0.3808F, 0.3809F, 0.381F, 0.3811F, 0.3812F, 0.3813F, 0.3814F, 0.3815F,
    0.3816F, 0.3817F, 0.3818F, 0.3819F, 0.382F, 0.3821F, 0.3822F, 0.3823F,
    0.3824F, 0.3825F, 0.3826F, 0.3827F, 0.3828F, 0.3829F, 0.383F, 0.3831F,
    0.3832F, 0.3833F, 0.3834F, 0.3835F, 0.3836F, 0.3837F, 0.3838F, 0.3839F,
    0.384F, 0.3841F, 0.3842F, 0.3843F, 0.3844F, 0.3845F, 0.3846F, 0.3847F,
    0.3848F, 0.3849F, 0.385F, 0.3851F, 0.3852F, 0.3853F, 0.3854F, 0.3855F,
    0.3856F, 0.3857F, 0.3858F, 0.3859F, 0.386F, 0.3861F, 0.3862F, 0.3863F,
    0.3864F, 0.3865F, 0.3866F, 0.3867F, 0.3868F, 0.3869F, 0.387F, 0.3871F,
    0.3872F, 0.3873F, 0.3874F, 0.3875F, 0.3876F, 0.3877F, 0.3878F, 0.3879F,
    0.388F, 0.3881F, 0.3882F, 0.3883F, 0.3884F, 0.3885F, 0.3886F, 0.3887F,
    0.3888F, 0.3889F, 0.389F, 0.3891F, 0.3892F, 0.3893F, 0.3894F, 0.3895F,
    0.3896F, 0.3897F, 0.3898F, 0.3899F, 0.39F, 0.3901F, 0.3902F, 0.3903F,
    0.3904F, 0.3905F, 0.3906F, 0.3907F, 0.3908F, 0.3909F, 0.391F, 0.3911F,
    0.3912F, 0.3913F, 0.3914F, 0.3915F, 0.3916F, 0.3917F, 0.3918F, 0.3919F,
    0.392F, 0.3921F, 0.3922F, 0.3923F, 0.3924F, 0.3925F, 0.3926F, 0.3927F,
    0.3928F, 0.3929F, 0.393F, 0.3931F, 0.3932F, 0.3933F, 0.3934F, 0.3935F,
    0.3936F, 0.3937F, 0.3938F, 0.3939F, 0.394F, 0.3941F, 0.3942F, 0.3943F,
    0.3944F, 0.3945F, 0.3946F, 0.3947F, 0.3948F, 0.3949F, 0.395F, 0.3951F,
    0.3952F, 0.3953F, 0.3954F, 0.3955F, 0.3956F, 0.3957F, 0.3958F, 0.3959F,
    0.396F, 0.3961F, 0.3962F, 0.3963F, 0.3964F, 0.3965F, 0.3966F, 0.3967F,
    0.3968F, 0.3969F, 0.397F, 0.3971F, 0.3972F, 0.3973F, 0.3974F, 0.3975F,
    0.3976F, 0.3977F, 0.3978F, 0.3979F, 0.398F, 0.3981F, 0.3982F, 0.3983F,
    0.3984F, 0.3985F, 0.3986F, 0.3987F, 0.3988F, 0.3989F, 0.399F, 0.3991F,
    0.3992F, 0.3993F, 0.3994F, 0.3995F, 0.3996F, 0.3997F, 0.3998F, 0.3999F, 0.4F,
    0.4001F, 0.4002F, 0.4003F, 0.4004F, 0.4005F, 0.4006F, 0.4007F, 0.4008F,
    0.4009F, 0.401F, 0.4011F, 0.4012F, 0.4013F, 0.4014F, 0.4015F, 0.4016F,
    0.4017F, 0.4018F, 0.4019F, 0.402F, 0.4021F, 0.4022F, 0.4023F, 0.4024F,
    0.4025F, 0.4026F, 0.4027F, 0.4028F, 0.4029F, 0.403F, 0.4031F, 0.4032F,
    0.4033F, 0.4034F, 0.4035F, 0.4036F, 0.4037F, 0.4038F, 0.4039F, 0.404F,
    0.4041F, 0.4042F, 0.4043F, 0.4044F, 0.4045F, 0.4046F, 0.4047F, 0.4048F,
    0.4049F, 0.405F, 0.4051F, 0.4052F, 0.4053F, 0.4054F, 0.4055F, 0.4056F,
    0.4057F, 0.4058F, 0.4059F, 0.406F, 0.4061F, 0.4062F, 0.4063F, 0.4064F,
    0.4065F, 0.4066F, 0.4067F, 0.4068F, 0.4069F, 0.407F, 0.4071F, 0.4072F,
    0.4073F, 0.4074F, 0.4075F, 0.4076F, 0.4077F, 0.4078F, 0.4079F, 0.408F,
    0.4081F, 0.4082F, 0.4083F, 0.4084F, 0.4085F, 0.4086F, 0.4087F, 0.4088F,
    0.4089F, 0.409F, 0.4091F, 0.4092F, 0.4093F, 0.4094F, 0.4095F, 0.4096F,
    0.4097F, 0.4098F, 0.4099F, 0.41F, 0.4101F, 0.4102F, 0.4103F, 0.4104F,
    0.4105F, 0.4106F, 0.4107F, 0.4108F, 0.4109F, 0.411F, 0.4111F, 0.4112F,
    0.4113F, 0.4114F, 0.4115F, 0.4116F, 0.4117F, 0.4118F, 0.4119F, 0.412F,
    0.4121F, 0.4122F, 0.4123F, 0.4124F, 0.4125F, 0.4126F, 0.4127F, 0.4128F,
    0.4129F, 0.413F, 0.4131F, 0.4132F, 0.4133F, 0.4134F, 0.4135F, 0.4136F,
    0.4137F, 0.4138F, 0.4139F, 0.414F, 0.4141F, 0.4142F, 0.4143F, 0.4144F,
    0.4145F, 0.4146F, 0.4147F, 0.4148F, 0.4149F, 0.415F, 0.4151F, 0.4152F,
    0.4153F, 0.4154F, 0.4155F, 0.4156F, 0.4157F, 0.4158F, 0.4159F, 0.416F,
    0.4161F, 0.4162F, 0.4163F, 0.4164F, 0.4165F, 0.4166F, 0.4167F, 0.4168F,
    0.4169F, 0.417F, 0.4171F, 0.4172F, 0.4173F, 0.4174F, 0.4175F, 0.4176F,
    0.4177F, 0.4178F, 0.4179F, 0.418F, 0.4181F, 0.4182F, 0.4183F, 0.4184F,
    0.4185F, 0.4186F, 0.4187F, 0.4188F, 0.4189F, 0.419F, 0.4191F, 0.4192F,
    0.4193F, 0.4194F, 0.4195F, 0.4196F, 0.4197F, 0.4198F, 0.4199F, 0.42F,
    0.4201F, 0.4202F, 0.4203F, 0.4204F, 0.4205F, 0.4206F, 0.4207F, 0.4208F,
    0.4209F, 0.421F, 0.4211F, 0.4212F, 0.4213F, 0.4214F, 0.4215F, 0.4216F,
    0.4217F, 0.4218F, 0.4219F, 0.422F, 0.4221F, 0.4222F, 0.4223F, 0.4224F,
    0.4225F, 0.4226F, 0.4227F, 0.4228F, 0.4229F, 0.423F, 0.4231F, 0.4232F,
    0.4233F, 0.4234F, 0.4235F, 0.4236F, 0.4237F, 0.4238F, 0.4239F, 0.424F,
    0.4241F, 0.4242F, 0.4243F, 0.4244F, 0.4245F, 0.4246F, 0.4247F, 0.4248F,
    0.4249F, 0.425F, 0.4251F, 0.4252F, 0.4253F, 0.4254F, 0.4255F, 0.4256F,
    0.4257F, 0.4258F, 0.4259F, 0.426F, 0.4261F, 0.4262F, 0.4263F, 0.4264F,
    0.4265F, 0.4266F, 0.4267F, 0.4268F, 0.4269F, 0.427F, 0.4271F, 0.4272F,
    0.4273F, 0.4274F, 0.4275F, 0.4276F, 0.4277F, 0.4278F, 0.4279F, 0.428F,
    0.4281F, 0.4282F, 0.4283F, 0.4284F, 0.4285F, 0.4286F, 0.4287F, 0.4288F,
    0.4289F, 0.429F, 0.4291F, 0.4292F, 0.4293F, 0.4294F, 0.4295F, 0.4296F,
    0.4297F, 0.4298F, 0.4299F, 0.43F, 0.4301F, 0.4302F, 0.4303F, 0.4304F,
    0.4305F, 0.4306F, 0.4307F, 0.4308F, 0.4309F, 0.431F, 0.4311F, 0.4312F,
    0.4313F, 0.4314F, 0.4315F, 0.4316F, 0.4317F, 0.4318F, 0.4319F, 0.432F,
    0.4321F, 0.4322F, 0.4323F, 0.4324F, 0.4325F, 0.4326F, 0.4327F, 0.4328F,
    0.4329F, 0.433F, 0.4331F, 0.4332F, 0.4333F, 0.4334F, 0.4335F, 0.4336F,
    0.4337F, 0.4338F, 0.4339F, 0.434F, 0.4341F, 0.4342F, 0.4343F, 0.4344F,
    0.4345F, 0.4346F, 0.4347F, 0.4348F, 0.4349F, 0.435F, 0.4351F, 0.4352F,
    0.4353F, 0.4354F, 0.4355F, 0.4356F, 0.4357F, 0.4358F, 0.4359F, 0.436F,
    0.4361F, 0.4362F, 0.4363F, 0.4364F, 0.4365F, 0.4366F, 0.4367F, 0.4368F,
    0.4369F, 0.437F, 0.4371F, 0.4372F, 0.4373F, 0.4374F, 0.4375F, 0.4376F,
    0.4377F, 0.4378F, 0.4379F, 0.438F, 0.4381F, 0.4382F, 0.4383F, 0.4384F,
    0.4385F, 0.4386F, 0.4387F, 0.4388F, 0.4389F, 0.439F, 0.4391F, 0.4392F,
    0.4393F, 0.4394F, 0.4395F, 0.4396F, 0.4397F, 0.4398F, 0.4399F, 0.44F,
    0.4401F, 0.4402F, 0.4403F, 0.4404F, 0.4405F, 0.4406F, 0.4407F, 0.4408F,
    0.4409F, 0.441F, 0.4411F, 0.4412F, 0.4413F, 0.4414F, 0.4415F, 0.4416F,
    0.4417F, 0.4418F, 0.4419F, 0.442F, 0.4421F, 0.4422F, 0.4423F, 0.4424F,
    0.4425F, 0.4426F, 0.4427F, 0.4428F, 0.4429F, 0.443F, 0.4431F, 0.4432F,
    0.4433F, 0.4434F, 0.4435F, 0.4436F, 0.4437F, 0.4438F, 0.4439F, 0.444F,
    0.4441F, 0.4442F, 0.4443F, 0.4444F, 0.4445F, 0.4446F, 0.4447F, 0.4448F,
    0.4449F, 0.445F, 0.4451F, 0.4452F, 0.4453F, 0.4454F, 0.4455F, 0.4456F,
    0.4457F, 0.4458F, 0.4459F, 0.446F, 0.4461F, 0.4462F, 0.4463F, 0.4464F,
    0.4465F, 0.4466F, 0.4467F, 0.4468F, 0.4469F, 0.447F, 0.4471F, 0.4472F,
    0.4473F, 0.4474F, 0.4475F, 0.4476F, 0.4477F, 0.4478F, 0.4479F, 0.448F,
    0.4481F, 0.4482F, 0.4483F, 0.4484F, 0.4485F, 0.4486F, 0.4487F, 0.4488F,
    0.4489F, 0.449F, 0.4491F, 0.4492F, 0.4493F, 0.4494F, 0.4495F, 0.4496F,
    0.4497F, 0.4498F, 0.4499F, 0.45F, 0.4501F, 0.4502F, 0.4503F, 0.4504F,
    0.4505F, 0.4506F, 0.4507F, 0.4508F, 0.4509F, 0.451F, 0.4511F, 0.4512F,
    0.4513F, 0.4514F, 0.4515F, 0.4516F, 0.4517F, 0.4518F, 0.4519F, 0.452F,
    0.4521F, 0.4522F, 0.4523F, 0.4524F, 0.4525F, 0.4526F, 0.4527F, 0.4528F,
    0.4529F, 0.453F, 0.4531F, 0.4532F, 0.4533F, 0.4534F, 0.4535F, 0.4536F,
    0.4537F, 0.4538F, 0.4539F, 0.454F, 0.4541F, 0.4542F, 0.4543F, 0.4544F,
    0.4545F, 0.4546F, 0.4547F, 0.4548F, 0.4549F, 0.455F, 0.4551F, 0.4552F,
    0.4553F, 0.4554F, 0.4555F, 0.4556F, 0.4557F, 0.4558F, 0.4559F, 0.456F,
    0.4561F, 0.4562F, 0.4563F, 0.4564F, 0.4565F, 0.4566F, 0.4567F, 0.4568F,
    0.4569F, 0.457F, 0.4571F, 0.4572F, 0.4573F, 0.4574F, 0.4575F, 0.4576F,
    0.4577F, 0.4578F, 0.4579F, 0.458F, 0.4581F, 0.4582F, 0.4583F, 0.4584F,
    0.4585F, 0.4586F, 0.4587F, 0.4588F, 0.4589F, 0.459F, 0.4591F, 0.4592F,
    0.4593F, 0.4594F, 0.4595F, 0.4596F, 0.4597F, 0.4598F, 0.4599F, 0.46F,
    0.4601F, 0.4602F, 0.4603F, 0.4604F, 0.4605F, 0.4606F, 0.4607F, 0.4608F,
    0.4609F, 0.461F, 0.4611F, 0.4612F, 0.4613F, 0.4614F, 0.4615F, 0.4616F,
    0.4617F, 0.4618F, 0.4619F, 0.462F, 0.4621F, 0.4622F, 0.4623F, 0.4624F,
    0.4625F, 0.4626F, 0.4627F, 0.4628F, 0.4629F, 0.463F, 0.4631F, 0.4632F,
    0.4633F, 0.4634F, 0.4635F, 0.4636F, 0.4637F, 0.4638F, 0.4639F, 0.464F,
    0.4641F, 0.4642F, 0.4643F, 0.4644F, 0.4645F, 0.4646F, 0.4647F, 0.4648F,
    0.4649F, 0.465F, 0.4651F, 0.4652F, 0.4653F, 0.4654F, 0.4655F, 0.4656F,
    0.4657F, 0.4658F, 0.4659F, 0.466F, 0.4661F, 0.4662F, 0.4663F, 0.4664F,
    0.4665F, 0.4666F, 0.4667F, 0.4668F, 0.4669F, 0.467F, 0.4671F, 0.4672F,
    0.4673F, 0.4674F, 0.4675F, 0.4676F, 0.4677F, 0.4678F, 0.4679F, 0.468F,
    0.4681F, 0.4682F, 0.4683F, 0.4684F, 0.4685F, 0.4686F, 0.4687F, 0.4688F,
    0.4689F, 0.469F, 0.4691F, 0.4692F, 0.4693F, 0.4694F, 0.4695F, 0.4696F,
    0.4697F, 0.4698F, 0.4699F, 0.47F, 0.4701F, 0.4702F, 0.4703F, 0.4704F,
    0.4705F, 0.4706F, 0.4707F, 0.4708F, 0.4709F, 0.471F, 0.4711F, 0.4712F,
    0.4713F, 0.4714F, 0.4715F, 0.4716F, 0.4717F, 0.4718F, 0.4719F, 0.472F,
    0.4721F, 0.4722F, 0.4723F, 0.4724F, 0.4725F, 0.4726F, 0.4727F, 0.4728F,
    0.4729F, 0.473F, 0.4731F, 0.4732F, 0.4733F, 0.4734F, 0.4735F, 0.4736F,
    0.4737F, 0.4738F, 0.4739F, 0.474F, 0.4741F, 0.4742F, 0.4743F, 0.4744F,
    0.4745F, 0.4746F, 0.4747F, 0.4748F, 0.4749F, 0.475F, 0.4751F, 0.4752F,
    0.4753F, 0.4754F, 0.4755F, 0.4756F, 0.4757F, 0.4758F, 0.4759F, 0.476F,
    0.4761F, 0.4762F, 0.4763F, 0.4764F, 0.4765F, 0.4766F, 0.4767F, 0.4768F,
    0.4769F, 0.477F, 0.4771F, 0.4772F, 0.4773F, 0.4774F, 0.4775F, 0.4776F,
    0.4777F, 0.4778F, 0.4779F, 0.478F, 0.4781F, 0.4782F, 0.4783F, 0.4784F,
    0.4785F, 0.4786F, 0.4787F, 0.4788F, 0.4789F, 0.479F, 0.4791F, 0.4792F,
    0.4793F, 0.4794F, 0.4795F, 0.4796F, 0.4797F, 0.4798F, 0.4799F, 0.48F,
    0.4801F, 0.4802F, 0.4803F, 0.4804F, 0.4805F, 0.4806F, 0.4807F, 0.4808F,
    0.4809F, 0.481F, 0.4811F, 0.4812F, 0.4813F, 0.4814F, 0.4815F, 0.4816F,
    0.4817F, 0.4818F, 0.4819F, 0.482F, 0.4821F, 0.4822F, 0.4823F, 0.4824F,
    0.4825F, 0.4826F, 0.4827F, 0.4828F, 0.4829F, 0.483F, 0.4831F, 0.4832F,
    0.4833F, 0.4834F, 0.4835F, 0.4836F, 0.4837F, 0.4838F, 0.4839F, 0.484F,
    0.4841F, 0.4842F, 0.4843F, 0.4844F, 0.4845F, 0.4846F, 0.4847F, 0.4848F,
    0.4849F, 0.485F, 0.4851F, 0.4852F, 0.4853F, 0.4854F, 0.4855F, 0.4856F,
    0.4857F, 0.4858F, 0.4859F, 0.486F, 0.4861F, 0.4862F, 0.4863F, 0.4864F,
    0.4865F, 0.4866F, 0.4867F, 0.4868F, 0.4869F, 0.487F, 0.4871F, 0.4872F,
    0.4873F, 0.4874F, 0.4875F, 0.4876F, 0.4877F, 0.4878F, 0.4879F, 0.488F,
    0.4881F, 0.4882F, 0.4883F, 0.4884F, 0.4885F, 0.4886F, 0.4887F, 0.4888F,
    0.4889F, 0.489F, 0.4891F, 0.4892F, 0.4893F, 0.4894F, 0.4895F, 0.4896F,
    0.4897F, 0.4898F, 0.4899F, 0.49F, 0.4901F, 0.4902F, 0.4903F, 0.4904F,
    0.4905F, 0.4906F, 0.4907F, 0.4908F, 0.4909F, 0.491F, 0.4911F, 0.4912F,
    0.4913F, 0.4914F, 0.4915F, 0.4916F, 0.4917F, 0.4918F, 0.4919F, 0.492F,
    0.4921F, 0.4922F, 0.4923F, 0.4924F, 0.4925F, 0.4926F, 0.4927F, 0.4928F,
    0.4929F, 0.493F, 0.4931F, 0.4932F, 0.4933F, 0.4934F, 0.4935F, 0.4936F,
    0.4937F, 0.4938F, 0.4939F, 0.494F, 0.4941F, 0.4942F, 0.4943F, 0.4944F,
    0.4945F, 0.4946F, 0.4947F, 0.4948F, 0.4949F, 0.495F, 0.4951F, 0.4952F,
    0.4953F, 0.4954F, 0.4955F, 0.4956F, 0.4957F, 0.4958F, 0.4959F, 0.496F,
    0.4961F, 0.4962F, 0.4963F, 0.4964F, 0.4965F, 0.4966F, 0.4967F, 0.4968F,
    0.4969F, 0.497F, 0.4971F, 0.4972F, 0.4973F, 0.4974F, 0.4975F, 0.4976F,
    0.4977F, 0.4978F, 0.4979F, 0.498F, 0.4981F, 0.4982F, 0.4983F, 0.4984F,
    0.4985F, 0.4986F, 0.4987F, 0.4988F, 0.4989F, 0.499F, 0.4991F, 0.4992F,
    0.4993F, 0.4994F, 0.4995F, 0.4996F, 0.4997F, 0.4998F, 0.4999F, 0.5F };

  /* 'FFTRecordedVoltage:5' output = input; */
  /*  fft functionality */
  /* 'FFTRecordedVoltage:7' Y = single(zeros(10000,1)); */
  /* 1000 depends on the size of recorded data! */
  /* 'FFTRecordedVoltage:8' L = length(data); */
  /* 'FFTRecordedVoltage:9' Y = fft(data); */
  rtElectricalID_6ph_codegen_DW->costab1q[0] = 1.0F;
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 4096;
       rtElectricalID_6ph_codegen_DW->idx++) {
    rtElectricalID_6ph_codegen_DW->costab1q[rtElectricalID_6ph_codegen_DW->idx +
      1] = cosf(((real32_T)rtElectricalID_6ph_codegen_DW->idx + 1.0F) *
                0.000191747604F);
  }

  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 4095;
       rtElectricalID_6ph_codegen_DW->idx++) {
    rtElectricalID_6ph_codegen_DW->costab1q[rtElectricalID_6ph_codegen_DW->idx +
      4097] = sinf((8192.0F - ((real32_T)rtElectricalID_6ph_codegen_DW->idx +
      4097.0F)) * 0.000191747604F);
  }

  rtElectricalID_6ph_codegen_DW->costab1q[8192] = 0.0F;
  rtElectricalID_6ph_codegen_DW->costab[0] = 1.0F;
  rtElectricalID_6ph_codegen_DW->sintab[0] = 0.0F;
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 8192;
       rtElectricalID_6ph_codegen_DW->idx++) {
    rtElectricalID_6ph_codegen_DW->nt_im =
      rtElectricalID_6ph_codegen_DW->costab1q[8191 -
      rtElectricalID_6ph_codegen_DW->idx];
    rtElectricalID_6ph_codegen_DW->sintabinv[rtElectricalID_6ph_codegen_DW->idx
      + 1] = rtElectricalID_6ph_codegen_DW->nt_im;
    rtElectricalID_6ph_codegen_DW->sintabinv_tmp =
      rtElectricalID_6ph_codegen_DW->costab1q[rtElectricalID_6ph_codegen_DW->idx
      + 1];
    rtElectricalID_6ph_codegen_DW->sintabinv[rtElectricalID_6ph_codegen_DW->idx
      + 8193] = rtElectricalID_6ph_codegen_DW->sintabinv_tmp;
    rtElectricalID_6ph_codegen_DW->costab[rtElectricalID_6ph_codegen_DW->idx + 1]
      = rtElectricalID_6ph_codegen_DW->sintabinv_tmp;
    rtElectricalID_6ph_codegen_DW->sintab[rtElectricalID_6ph_codegen_DW->idx + 1]
      = -rtElectricalID_6ph_codegen_DW->nt_im;
    rtElectricalID_6ph_codegen_DW->costab[rtElectricalID_6ph_codegen_DW->idx +
      8193] = -rtElectricalID_6ph_codegen_DW->nt_im;
    rtElectricalID_6ph_codegen_DW->sintab[rtElectricalID_6ph_codegen_DW->idx +
      8193] = -rtElectricalID_6ph_codegen_DW->sintabinv_tmp;
  }

  rtElectricalID_6ph_codegen_DW->rt = 0;
  rtElectricalID_6ph_codegen_DW->wwc[4999].re = 1.0F;
  rtElectricalID_6ph_codegen_DW->wwc[4999].im = 0.0F;
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 4999;
       rtElectricalID_6ph_codegen_DW->idx++) {
    rtElectricalID_6ph_codegen_DW->y_c = ((rtElectricalID_6ph_codegen_DW->idx +
      1) << 1) - 1;
    if (10000 - rtElectricalID_6ph_codegen_DW->rt <=
        rtElectricalID_6ph_codegen_DW->y_c) {
      rtElectricalID_6ph_codegen_DW->rt = (rtElectricalID_6ph_codegen_DW->y_c +
        rtElectricalID_6ph_codegen_DW->rt) - 10000;
    } else {
      rtElectricalID_6ph_codegen_DW->rt += rtElectricalID_6ph_codegen_DW->y_c;
    }

    rtElectricalID_6ph_codegen_DW->nt_im = -3.14159274F * (real32_T)
      rtElectricalID_6ph_codegen_DW->rt / 5000.0F;
    if (rtElectricalID_6ph_codegen_DW->nt_im == 0.0F) {
      rtElectricalID_6ph_codegen_DW->wwc[4998 -
        rtElectricalID_6ph_codegen_DW->idx].re = 1.0F;
      rtElectricalID_6ph_codegen_DW->nt_im = 0.0F;
    } else {
      rtElectricalID_6ph_codegen_DW->wwc[4998 -
        rtElectricalID_6ph_codegen_DW->idx].re = cosf
        (rtElectricalID_6ph_codegen_DW->nt_im);
      rtElectricalID_6ph_codegen_DW->nt_im = sinf
        (rtElectricalID_6ph_codegen_DW->nt_im);
    }

    rtElectricalID_6ph_codegen_DW->wwc[4998 - rtElectricalID_6ph_codegen_DW->idx]
      .im = -rtElectricalID_6ph_codegen_DW->nt_im;
  }

  for (rtElectricalID_6ph_codegen_DW->idx = 4998;
       rtElectricalID_6ph_codegen_DW->idx >= 0;
       rtElectricalID_6ph_codegen_DW->idx--) {
    rtElectricalID_6ph_codegen_DW->wwc[rtElectricalID_6ph_codegen_DW->idx + 5000]
      = rtElectricalID_6ph_codegen_DW->wwc[4998 -
      rtElectricalID_6ph_codegen_DW->idx];
  }

  FFTImplementationCallback_doHal(data, 0, rtElectricalID_6ph_codegen_DW->Y,
    rtElectricalID_6ph_codegen_DW->wwc, rtElectricalID_6ph_codegen_DW->costab,
    rtElectricalID_6ph_codegen_DW->sintab, rtElectricalID_6ph_codegen_DW->costab,
    rtElectricalID_6ph_codegen_DW->sintabinv, rtElectricalID_6ph_codegen_DW);

  /* 'FFTRecordedVoltage:10' temp_amplitude = single(zeros(5001,1)); */
  /* 'FFTRecordedVoltage:11' temp_angle = single(zeros(10000,1)); */
  /* 'FFTRecordedVoltage:12' tol = single(1e-7); */
  /* 'FFTRecordedVoltage:13' for i=1:10000 */
  /* 'FFTRecordedVoltage:18' P2 = abs(Y/L); */
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 10000;
       rtElectricalID_6ph_codegen_DW->idx++) {
    rtElectricalID_6ph_codegen_DW->Y_c = rtElectricalID_6ph_codegen_DW->
      Y[rtElectricalID_6ph_codegen_DW->idx];
    rtElectricalID_6ph_codegen_DW->nt_im = rtElectricalID_6ph_codegen_DW->Y_c.re;
    rtElectricalID_6ph_codegen_DW->sintabinv_tmp =
      rtElectricalID_6ph_codegen_DW->Y_c.im;

    /* 1000 depends on the size of recorded data! */
    /* 'FFTRecordedVoltage:14' if(abs(Y(i))<tol) */
    if (rt_hypotf_snf(rtElectricalID_6ph_codegen_DW->Y_c.re,
                      rtElectricalID_6ph_codegen_DW->Y_c.im) < 1.0E-7F) {
      /* 'FFTRecordedVoltage:15' Y(i) = single(0); */
      rtElectricalID_6ph_codegen_DW->nt_im = 0.0F;
      rtElectricalID_6ph_codegen_DW->sintabinv_tmp = 0.0F;
    }

    if (rtElectricalID_6ph_codegen_DW->sintabinv_tmp == 0.0F) {
      rtElectricalID_6ph_codegen_DW->x_re = rtElectricalID_6ph_codegen_DW->nt_im
        / 10000.0F;
      rtElectricalID_6ph_codegen_DW->x_im = 0.0F;
    } else if (rtElectricalID_6ph_codegen_DW->nt_im == 0.0F) {
      rtElectricalID_6ph_codegen_DW->x_re = 0.0F;
      rtElectricalID_6ph_codegen_DW->x_im =
        rtElectricalID_6ph_codegen_DW->sintabinv_tmp / 10000.0F;
    } else {
      rtElectricalID_6ph_codegen_DW->x_re = rtElectricalID_6ph_codegen_DW->nt_im
        / 10000.0F;
      rtElectricalID_6ph_codegen_DW->x_im =
        rtElectricalID_6ph_codegen_DW->sintabinv_tmp / 10000.0F;
    }

    rtElectricalID_6ph_codegen_DW->P2[rtElectricalID_6ph_codegen_DW->idx] =
      rt_hypotf_snf(rtElectricalID_6ph_codegen_DW->x_re,
                    rtElectricalID_6ph_codegen_DW->x_im);
    rtElectricalID_6ph_codegen_DW->Y_c.re = rtElectricalID_6ph_codegen_DW->nt_im;
    rtElectricalID_6ph_codegen_DW->Y_c.im =
      rtElectricalID_6ph_codegen_DW->sintabinv_tmp;
    rtElectricalID_6ph_codegen_DW->Y[rtElectricalID_6ph_codegen_DW->idx] =
      rtElectricalID_6ph_codegen_DW->Y_c;
  }

  /* 'FFTRecordedVoltage:19' temp_amplitude = P2(1:L/2+1); */
  /* 'FFTRecordedVoltage:20' output.amplitudes(2:end-1) = 2*temp_amplitude(2:end-1); */
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 4999;
       rtElectricalID_6ph_codegen_DW->idx++) {
    input->amplitudes[rtElectricalID_6ph_codegen_DW->idx + 1] =
      rtElectricalID_6ph_codegen_DW->P2[rtElectricalID_6ph_codegen_DW->idx + 1] *
      2.0F;
  }

  /* 'FFTRecordedVoltage:21' output.frequencies = (0:(L/2))/L/sampletime; */
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 5001;
       rtElectricalID_6ph_codegen_DW->idx++) {
    input->frequencies[rtElectricalID_6ph_codegen_DW->idx] =
      e[rtElectricalID_6ph_codegen_DW->idx] / sampletime;
  }

  /* 'FFTRecordedVoltage:22' temp_angle=angle(Y); */
  for (rtElectricalID_6ph_codegen_DW->idx = 0;
       rtElectricalID_6ph_codegen_DW->idx < 10000;
       rtElectricalID_6ph_codegen_DW->idx++) {
    rtElectricalID_6ph_codegen_DW->P2[rtElectricalID_6ph_codegen_DW->idx] =
      rt_atan2f_snf(rtElectricalID_6ph_codegen_DW->
                    Y[rtElectricalID_6ph_codegen_DW->idx].im,
                    rtElectricalID_6ph_codegen_DW->
                    Y[rtElectricalID_6ph_codegen_DW->idx].re);
  }

  /* 'FFTRecordedVoltage:23' output.angles=temp_angle(1:L/2+1); */
  memcpy(&input->angles[0], &rtElectricalID_6ph_codegen_DW->P2[0], 5001U *
         sizeof(real32_T));
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function [output] = FindPsiPMs(input)
 * FindPsiPMs Finds PSI_PMs of higher orders
 *    Detailed explanation goes here
 *  carry datatype
 */
static void FindPsiPMs(const internal_psi_analysis *input, internal_psi_analysis
  *output)
{
  int32_T idx;
  int32_T k;
  real32_T ex;
  real32_T ex_tmp;
  static const int8_T b_a_0[5] = { 1, 3, 5, 7, 11 };

  /* 'FindPsiPMs:5' output = input; */
  *output = *input;

  /*  find fundamental */
  /* 'FindPsiPMs:7' [ampl_1,index_1] = max(input.amplitudes); */
  if (!rtIsNaNF(input->amplitudes[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5002)) {
      if (!rtIsNaNF(input->amplitudes[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    idx = 1;
  } else {
    ex = input->amplitudes[idx - 1];
    for (k = idx; k < 5001; k++) {
      if (ex < input->amplitudes[k]) {
        ex = input->amplitudes[k];
        idx = k + 1;
      }
    }
  }

  /* 'FindPsiPMs:8' omega_el1 = 2*pi*input.frequencies(index_1); */
  ex_tmp = input->frequencies[idx - 1];
  ex = ex_tmp * 6.28318548F;

  /*  initialize arrays */
  /* 'FindPsiPMs:10' order = single([1 3 5 7 11]); */
  /*  calculate results */
  /*  calculate frequencies to orders */
  /* 'FindPsiPMs:13' output.psi_freq = order*input.frequencies(index_1); */
  /*  calculate psi magnitude */
  /* 'FindPsiPMs:15' output.psi_pm = input.amplitudes(index_1*order)./(omega_el1*order); */
  /*  calculate angles */
  /* 'FindPsiPMs:17' output.psi_angle = input.angles(index_1*order)'; */
  for (k = 0; k < 5; k++) {
    int32_T tmp;
    int8_T b_a;
    b_a = b_a_0[k];
    output->psi_freq[k] = (real32_T)b_a * ex_tmp;
    tmp = idx * b_a - 1;
    output->psi_pm[k] = input->amplitudes[tmp] / (ex * (real32_T)b_a);
    output->psi_angle[k] = input->angles[tmp];
  }
}

/*
 * Function for Chart: '<Root>/ElectricalID_6ph_codegen'
 * function output = PsiCompensation(input,R_series,R_parallel,C)
 * PsiCompensation compensates the calculated psis for given voltage devider/filter
 *    Detailed explanation goes here
 *  set out=in
 */
static void PsiCompensation(const internal_psi_analysis *input, real32_T
  R_series, real32_T R_parallel, real32_T C, internal_psi_analysis *output)
{
  int32_T k;
  real32_T a_im;
  real32_T a_re;

  /* 'PsiCompensation:5' output = input; */
  *output = *input;

  /*  calculate complex voltage devider */
  /* 'PsiCompensation:7' Xc = 1./(1i*2*pi*C*input.psi_freq); */
  a_re = C * 0.0F;
  a_im = C * 6.28318548F;

  /* 'PsiCompensation:8' Z_parallel = Xc*R_parallel./(Xc+R_parallel); */
  /* 'PsiCompensation:9' factor = (Z_parallel + R_series) ./ Z_parallel; */
  /*  compensate */
  /* 'PsiCompensation:11' output.psi_angle = input.psi_angle + angle(factor); */
  /* 'PsiCompensation:12' output.psi_pm = input.psi_pm .* abs(factor); */
  for (k = 0; k < 5; k++) {
    real32_T Xc_im;
    real32_T Xc_re;
    real32_T ai;
    real32_T bi;
    real32_T bim;
    real32_T br;
    real32_T brm;
    bi = a_im * input->psi_freq[k];
    if (bi == 0.0F) {
      Xc_re = 1.0F / (a_re * input->psi_freq[k]);
      Xc_im = 0.0F;
    } else if (a_re * input->psi_freq[k] == 0.0F) {
      Xc_re = 0.0F;
      Xc_im = -(1.0F / bi);
    } else {
      Xc_re = (rtNaNF);
      Xc_im = (rtNaNF);
    }

    bi = Xc_re * R_parallel;
    ai = Xc_im * R_parallel;
    br = Xc_re + R_parallel;
    if (Xc_im == 0.0F) {
      if (ai == 0.0F) {
        Xc_re = bi / br;
        ai = 0.0F;
      } else if (bi == 0.0F) {
        Xc_re = 0.0F;
        ai /= br;
      } else {
        Xc_re = bi / br;
        ai /= br;
      }
    } else if (br == 0.0F) {
      if (bi == 0.0F) {
        Xc_re = ai / Xc_im;
        ai = 0.0F;
      } else if (ai == 0.0F) {
        Xc_re = 0.0F;
        ai = -(bi / Xc_im);
      } else {
        Xc_re = ai / Xc_im;
        ai = -(bi / Xc_im);
      }
    } else {
      brm = fabsf(br);
      bim = fabsf(Xc_im);
      if (brm > bim) {
        brm = Xc_im / br;
        Xc_im = brm * Xc_im + br;
        Xc_re = (brm * ai + bi) / Xc_im;
        ai = (ai - brm * bi) / Xc_im;
      } else if (bim == brm) {
        br = br > 0.0F ? 0.5F : -0.5F;
        Xc_im = Xc_im > 0.0F ? 0.5F : -0.5F;
        Xc_re = (bi * br + ai * Xc_im) / brm;
        ai = (ai * br - bi * Xc_im) / brm;
      } else {
        brm = br / Xc_im;
        Xc_im += brm * br;
        Xc_re = (brm * bi + ai) / Xc_im;
        ai = (brm * ai - bi) / Xc_im;
      }
    }

    bi = Xc_re + R_series;
    if (ai == 0.0F) {
      Xc_re = bi / Xc_re;
      ai = 0.0F;
    } else if (Xc_re == 0.0F) {
      if (bi == 0.0F) {
        Xc_re = ai / ai;
        ai = 0.0F;
      } else if (ai == 0.0F) {
        Xc_re = 0.0F;
        ai = -(bi / ai);
      } else {
        Xc_re = ai / ai;
        ai = -(bi / ai);
      }
    } else {
      brm = fabsf(Xc_re);
      bim = fabsf(ai);
      if (brm > bim) {
        brm = ai / Xc_re;
        br = brm * ai;
        Xc_im = br + Xc_re;
        Xc_re = (br + bi) / Xc_im;
        ai = (ai - brm * bi) / Xc_im;
      } else if (bim == brm) {
        br = Xc_re > 0.0F ? 0.5F : -0.5F;
        Xc_im = ai > 0.0F ? 0.5F : -0.5F;
        Xc_re = (bi * br + ai * Xc_im) / brm;
        ai = (ai * br - bi * Xc_im) / brm;
      } else {
        brm = Xc_re / ai;
        Xc_im = brm * Xc_re + ai;
        Xc_re = (brm * bi + ai) / Xc_im;
        ai = (brm * ai - bi) / Xc_im;
      }
    }

    output->psi_angle[k] = input->psi_angle[k] + rt_atan2f_snf(ai, Xc_re);
    output->psi_pm[k] = input->psi_pm[k] * rt_hypotf_snf(Xc_re, ai);
  }
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
  C_im = -A;
  if (-A == 0.0F) {
    C_re = expf(A * 0.0F);
    C_im = 0.0F;
  } else {
    A = expf(A * 0.0F / 2.0F);
    C_re = A * cosf(C_im) * A;
    C_im = A * sinf(C_im) * A;
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
      C_re = 0.0F;
    } else if (C_re == 0.0F) {
      C_im = 0.0F;
      C_re = B / b_y_re;
    } else {
      C_im = C_re / b_y_re;
      C_re = B / b_y_re;
    }
  } else if (b_y_re == 0.0F) {
    if (C_re == 0.0F) {
      C_im = B / b_y_im;
      C_re = 0.0F;
    } else if (B == 0.0F) {
      C_im = 0.0F;
      C_re = -(C_re / b_y_im);
    } else {
      C_im = B / b_y_im;
      C_re = -(C_re / b_y_im);
    }
  } else {
    A = fabsf(b_y_re);
    C_im = fabsf(b_y_im);
    if (A > C_im) {
      A = b_y_im / b_y_re;
      b_y_im = A * b_y_im + b_y_re;
      C_im = (A * B + C_re) / b_y_im;
      C_re = (B - A * C_re) / b_y_im;
    } else if (C_im == A) {
      b_y_re = b_y_re > 0.0F ? 0.5F : -0.5F;
      b_y_im = b_y_im > 0.0F ? 0.5F : -0.5F;
      C_im = (C_re * b_y_re + B * b_y_im) / A;
      C_re = (B * b_y_re - C_re * b_y_im) / A;
    } else {
      A = b_y_re / b_y_im;
      b_y_im += A * b_y_re;
      C_im = (A * C_re + B) / b_y_im;
      C_re = (A * B - C_re) / b_y_im;
    }
  }

  b_y_im = (C_im * 0.0F - C_re) * 2.0F * 3.14159274F * 40.0F;
  B = (C_re * 0.0F + C_im) * 2.0F * 3.14159274F * 40.0F;
  if (B == 0.0F) {
    C_re = 1.0F / b_y_im;
    C_im = 0.0F;
  } else if (b_y_im == 0.0F) {
    C_re = 0.0F;
    C_im = -(1.0F / B);
  } else {
    A = fabsf(b_y_im);
    C_im = fabsf(B);
    if (A > C_im) {
      A = B / b_y_im;
      b_y_im += A * B;
      C_re = (A * 0.0F + 1.0F) / b_y_im;
      C_im = (0.0F - A) / b_y_im;
    } else if (C_im == A) {
      b_y_re = b_y_im > 0.0F ? 0.5F : -0.5F;
      b_y_im = B > 0.0F ? 0.5F : -0.5F;
      C_re = (0.0F * b_y_im + b_y_re) / A;
      C_im = (0.0F * b_y_re - b_y_im) / A;
    } else {
      A = b_y_im / B;
      b_y_im = A * b_y_im + B;
      C_re = A / b_y_im;
      C_im = (A * 0.0F - 1.0F) / b_y_im;
    }
  }

  /* Merge: '<S1>/ Merge ' */
  rtElectricalID_6ph_codegen_DW->ElectricalID_output.PMSM_parameters.J_kg_m_squared
    = rt_hypotf_snf(C_re, C_im);

  /* without damping */
}

/* Function for Chart: '<Root>/ElectricalID_6ph_codegen' */
static void waitSetRPM(ExtU_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_U, ExtY_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_Y, DW_ElectricalID_6ph_codegen_t
  *rtElectricalID_6ph_codegen_DW)
{
  int32_T i;

  /* Inport: '<Root>/GlobalConfig' incorporates:
   *  Inport: '<Root>/ActualValues'
   */
  /* During 'waitSetRPM': '<S1>:1047' */
  /* '<S1>:1048:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1&&ActualValues.omega_m>5; */
  if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT &&
      (rtElectricalID_6ph_codegen_U->ActualValues.omega_m > 5.0F)) {
    /* Transition: '<S1>:1048' */
    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_measure_psiPM;

    /* Entry 'measure_psiPM': '<S1>:405' */
    memset(&rtElectricalID_6ph_codegen_DW->voltage_meas_array[0], 0, 10000U *
           sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->analysis.amplitudes[0], 0, 5001U *
           sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->analysis.frequencies[0], 0, 5001U *
           sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->analysis.angles[0], 0, 5001U * sizeof
           (real32_T));
    for (i = 0; i < 5; i++) {
      rtElectricalID_6ph_codegen_DW->analysis.psi_pm[i] = 0.0F;
      rtElectricalID_6ph_codegen_DW->analysis.psi_freq[i] = 0.0F;
      rtElectricalID_6ph_codegen_DW->analysis.psi_angle[i] = 0.0F;
    }

    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* '<S1>:405:4' ElectricalID_FOC_output.activeState = uint16(151); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 151U;

    /* '<S1>:405:5' counter = uint32(1); */
    rtElectricalID_6ph_codegen_DW->counter = 1U;
  } else {
    /* Outport: '<Root>/ElectricalID_FOC_output' */
    /* '<S1>:1047:2' ElectricalID_FOC_output.activeState = uint16(150); */
    rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 150U;

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:1047:3' ElectricalID_output.enable_TriState = boolean([1 1 1]); */
    /* '<S1>:1047:4' ElectricalID_output.enable_TriState_set_2 = boolean([1 1 1]); */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] = true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[0] =
      true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] = true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[1] =
      true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] = true;
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState_set_2[2] =
      true;
  }

  /* End of Inport: '<Root>/GlobalConfig' */
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
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S2>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S2>:35' */
      /* '<S2>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
      rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response1:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S3>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S3>:35' */
      /* '<S3>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
      rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response2:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S4>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S4>:35' */
      /* '<S4>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
      rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response3:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S5>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S5>:35' */
      /* '<S5>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
      rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response4:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S6>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S6>:35' */
      /* '<S6>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
      rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
        IN_NO_ACTIVE_CHILD;
      break;
    }

    rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_NO_ACTIVE_CHILD;
    break;

   case IN_Subchart_Step_Response5:
    /* Exit Internal: Subchart_Step_Response_6ph */
    switch (rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_) {
     case IN_Levenberg_Marquardt:
      /* Exit 'Levenberg_Marquardt': '<S7>:40' */
      rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
        IN_NO_ACTIVE_CHILD;
      break;

     case IN_stepResponse:
      /* Merge: '<S1>/ Merge ' */
      /* Exit 'stepResponse': '<S7>:35' */
      /* '<S7>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
      rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
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
    /* '<S1>:53:10' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
    rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
      rtElectricalID_6ph_codegen_U->ActualValues.theta_m;
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

   case IN_measure_psiPM:
    /* Inport: '<Root>/GlobalConfig' */
    /* Exit 'measure_psiPM': '<S1>:405' */
    /* '<S1>:405:10' analysis = FFTRecordedVoltage(analysis,voltage_meas_array,GlobalConfig.sampleTimeISR); */
    FFTRecordedVoltage(&rtElectricalID_6ph_codegen_DW->analysis,
                       rtElectricalID_6ph_codegen_DW->voltage_meas_array,
                       rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR,
                       rtElectricalID_6ph_codegen_DW);

    /* '<S1>:405:11' analysis = FindPsiPMs(analysis); */
    rtElectricalID_6ph_codegen_DW->r1 = rtElectricalID_6ph_codegen_DW->analysis;
    FindPsiPMs(&rtElectricalID_6ph_codegen_DW->r1,
               &rtElectricalID_6ph_codegen_DW->analysis);

    /* '<S1>:405:12' analysis = PsiCompensation(analysis,GlobalConfig.voltage_measurement_Rs,GlobalConfig.voltage_measurement_Rp,GlobalConfig.voltage_measurement_C); */
    rtElectricalID_6ph_codegen_DW->r1 = rtElectricalID_6ph_codegen_DW->analysis;

    /* Inport: '<Root>/GlobalConfig' */
    PsiCompensation(&rtElectricalID_6ph_codegen_DW->r1,
                    rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs,
                    rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp,
                    rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_C,
                    &rtElectricalID_6ph_codegen_DW->analysis);

    /* '<S1>:405:13' counter = uint32(1); */
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
  uint16_T n_iters_a;
  boolean_T updateJ_n;

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
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S2>:40' */
        /* '<S2>:61:1' sf_internal_predicateOutput = counter == 500; */
        if (rtElectricalID_6ph_codegen_DW->counter_n == 500U) {
          /* Transition: '<S2>:61' */
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
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
        /* '<S2>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
        rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S2>:40' */
        rtElectricalID_6ph_codegen_DW->e_o = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[3] = 0.0F;
        n_iters_a = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_nm = 0.01F;
        updateJ_n = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_k5[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_a[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S2>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_n = 1U;

        /* '<S2>:40:4' LM_algorithm; */
        LM_algorithm(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                     &rtElectricalID_6ph_codegen_DW->R_est_c,
                     &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_n,
                     &rtElectricalID_6ph_codegen_DW->lambda_nm,
                     &rtElectricalID_6ph_codegen_DW->e_o, &n_iters_a,
                     rtElectricalID_6ph_codegen_DW->H_a,
                     rtElectricalID_6ph_codegen_DW->i_est_l,
                     rtElectricalID_6ph_codegen_DW);

        /* '<S2>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S2>:35:9' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph,voltage_correction); */
        Subchart_St_MeasureStepRespon_n
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.d,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.d,
           rtElectricalID_6ph_codegen_DW->voltage_correction_bj,
           rtElectricalID_6ph_codegen_DW);

        /* '<S2>:35:10' counter = counter +1; */
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
        switch (rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S2>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S2>:35' */
          /* '<S2>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
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
        rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
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
          for (rtElectricalID_6ph_codegen_DW->i_p = 0;
               rtElectricalID_6ph_codegen_DW->i_p < 6;
               rtElectricalID_6ph_codegen_DW->i_p++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_l[6 *
              rtElectricalID_6ph_codegen_DW->i_p +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_p];
          }
        }

        /* setpoints in abc */
        /* '<S3>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_nm =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* set DutyCycles */
        /* '<S3>:35:7' voltage_correction = (GlobalConfig.voltage_measurement_Rp+GlobalConfig.voltage_measurement_Rs)/GlobalConfig.voltage_measurement_Rp; */
        rtElectricalID_6ph_codegen_DW->voltage_correction_f =
          (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp
           + rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs)
          /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp;

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response1' */
      }
      break;

     case IN_Subchart_Step_Response1:
      /* During 'Subchart_Step_Response1': '<S1>:1001' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S3>:40' */
        /* '<S3>:61:1' sf_internal_predicateOutput = counter == 500; */
        if (rtElectricalID_6ph_codegen_DW->counter_o == 500U) {
          /* Transition: '<S3>:61' */
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
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
        /* '<S3>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
        rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S3>:40' */
        rtElectricalID_6ph_codegen_DW->e_o = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[3] = 0.0F;
        n_iters_a = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_nm = 0.01F;
        updateJ_n = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_cl[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_g[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S3>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_o = 1U;

        /* '<S3>:40:4' LM_algorithm; */
        LM_algorithm_m(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_n,
                       &rtElectricalID_6ph_codegen_DW->lambda_nm,
                       &rtElectricalID_6ph_codegen_DW->e_o, &n_iters_a,
                       rtElectricalID_6ph_codegen_DW->H_a,
                       rtElectricalID_6ph_codegen_DW->i_est_l,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S3>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S3>:35:9' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph,voltage_correction); */
        Subchart__b_MeasureStepRespon_g
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.x,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.x,
           rtElectricalID_6ph_codegen_DW->voltage_correction_f,
           rtElectricalID_6ph_codegen_DW);

        /* '<S3>:35:10' counter = counter +1; */
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
        switch (rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S3>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S3>:35' */
          /* '<S3>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_stCf8mOih7YLxHmmCw99KT_S =
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
        rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_p = 0;
               rtElectricalID_6ph_codegen_DW->i_p < 6;
               rtElectricalID_6ph_codegen_DW->i_p++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_m[6 *
              rtElectricalID_6ph_codegen_DW->i_p +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_p];
          }
        }

        /* setpoints in abc */
        /* '<S4>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_nm =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* set DutyCycles */
        /* '<S4>:35:7' voltage_correction = (GlobalConfig.voltage_measurement_Rp+GlobalConfig.voltage_measurement_Rs)/GlobalConfig.voltage_measurement_Rp; */
        rtElectricalID_6ph_codegen_DW->voltage_correction_n =
          (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp
           + rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs)
          /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp;

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response2' */
      }
      break;

     case IN_Subchart_Step_Response2:
      /* During 'Subchart_Step_Response2': '<S1>:1009' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S4>:40' */
        /* '<S4>:61:1' sf_internal_predicateOutput = counter == 500; */
        if (rtElectricalID_6ph_codegen_DW->counter_f == 500U) {
          /* Transition: '<S4>:61' */
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
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
        /* '<S4>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
        rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S4>:40' */
        rtElectricalID_6ph_codegen_DW->e_o = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[3] = 0.0F;
        n_iters_a = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_nm = 0.01F;
        updateJ_n = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_k[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_p[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S4>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_f = 1U;

        /* '<S4>:40:4' LM_algorithm; */
        LM_algorithm_j(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_n,
                       &rtElectricalID_6ph_codegen_DW->lambda_nm,
                       &rtElectricalID_6ph_codegen_DW->e_o, &n_iters_a,
                       rtElectricalID_6ph_codegen_DW->H_a,
                       rtElectricalID_6ph_codegen_DW->i_est_l,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S4>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S4>:35:9' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph,voltage_correction); */
        Subchart_bt_MeasureStepRespon_p
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.y,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.y,
           rtElectricalID_6ph_codegen_DW->voltage_correction_n,
           rtElectricalID_6ph_codegen_DW);

        /* '<S4>:35:10' counter = counter +1; */
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
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S4>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S4>:35' */
          /* '<S4>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_sZOcCdU7kUMAo0AXD6Wq7pC_ =
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
        rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_p = 0;
               rtElectricalID_6ph_codegen_DW->i_p < 6;
               rtElectricalID_6ph_codegen_DW->i_p++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_a[6 *
              rtElectricalID_6ph_codegen_DW->i_p +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_p];
          }
        }

        /* setpoints in abc */
        /* '<S5>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_nm =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* set DutyCycles */
        /* '<S5>:35:7' voltage_correction = (GlobalConfig.voltage_measurement_Rp+GlobalConfig.voltage_measurement_Rs)/GlobalConfig.voltage_measurement_Rp; */
        rtElectricalID_6ph_codegen_DW->voltage_correction_b =
          (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp
           + rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs)
          /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp;

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response3' */
      }
      break;

     case IN_Subchart_Step_Response3:
      /* During 'Subchart_Step_Response3': '<S1>:1013' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S5>:40' */
        /* '<S5>:61:1' sf_internal_predicateOutput = counter == 500; */
        if (rtElectricalID_6ph_codegen_DW->counter_g == 500U) {
          /* Transition: '<S5>:61' */
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
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
        /* '<S5>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
        rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S5>:40' */
        rtElectricalID_6ph_codegen_DW->e_o = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[3] = 0.0F;
        n_iters_a = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_nm = 0.01F;
        updateJ_n = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_f[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_i[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S5>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_g = 1U;

        /* '<S5>:40:4' LM_algorithm; */
        LM_algorithm_a(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_n,
                       &rtElectricalID_6ph_codegen_DW->lambda_nm,
                       &rtElectricalID_6ph_codegen_DW->e_o, &n_iters_a,
                       rtElectricalID_6ph_codegen_DW->H_a,
                       rtElectricalID_6ph_codegen_DW->i_est_l,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S5>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S5>:35:9' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph,voltage_correction); */
        Subchar_btw_MeasureStepRespon_k
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.z1,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z1,
           rtElectricalID_6ph_codegen_DW->voltage_correction_b,
           rtElectricalID_6ph_codegen_DW);

        /* '<S5>:35:10' counter = counter +1; */
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
        switch (rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S5>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Exit 'stepResponse': '<S5>:35' */
          /* '<S5>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
          /* 'ResetDutyCycle:2' ElectricalID_output = ElectricalID_struct; */
          /* 'ResetDutyCycle:3' ElectricalID_output.PWM_Switch_0 = single(0); */
          /* 'ResetDutyCycle:4' ElectricalID_output.PWM_Switch_2 = single(0); */
          /* 'ResetDutyCycle:5' ElectricalID_output.PWM_Switch_4 = single(0); */
          /* 'ResetDutyCycle:6' ElectricalID_output.PWM_Switch_a2 = single(0); */
          /* 'ResetDutyCycle:7' ElectricalID_output.PWM_Switch_b2 = single(0); */
          /* 'ResetDutyCycle:8' ElectricalID_output.PWM_Switch_c2 = single(0); */
          rtElectricalID_6ph_codegen_DW->is_c14_soqu1B3Ht1nHmWueogiWW2E_ =
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
        rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_p = 0;
               rtElectricalID_6ph_codegen_DW->i_p < 6;
               rtElectricalID_6ph_codegen_DW->i_p++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_i[6 *
              rtElectricalID_6ph_codegen_DW->i_p +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_p];
          }
        }

        /* setpoints in abc */
        /* '<S6>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_nm =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* set DutyCycles */
        /* '<S6>:35:7' voltage_correction = (GlobalConfig.voltage_measurement_Rp+GlobalConfig.voltage_measurement_Rs)/GlobalConfig.voltage_measurement_Rp; */
        rtElectricalID_6ph_codegen_DW->voltage_correction_h =
          (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp
           + rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs)
          /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp;

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response4' */
      }
      break;

     case IN_Subchart_Step_Response4:
      /* During 'Subchart_Step_Response4': '<S1>:1017' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S6>:40' */
        /* '<S6>:61:1' sf_internal_predicateOutput = counter == 500; */
        if (rtElectricalID_6ph_codegen_DW->counter_j == 500U) {
          /* Transition: '<S6>:61' */
          /* Exit 'Levenberg_Marquardt': '<S6>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
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
        /* '<S6>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
        rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S6>:40' */
        rtElectricalID_6ph_codegen_DW->e_o = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[3] = 0.0F;
        n_iters_a = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_nm = 0.01F;
        updateJ_n = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_g[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J_b[0], 0, sizeof(real32_T) <<
               12U);

        /* '<S6>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_j = 1U;

        /* '<S6>:40:4' LM_algorithm; */
        LM_algorithm_ak(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                        &rtElectricalID_6ph_codegen_DW->R_est_c,
                        &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_n,
                        &rtElectricalID_6ph_codegen_DW->lambda_nm,
                        &rtElectricalID_6ph_codegen_DW->e_o, &n_iters_a,
                        rtElectricalID_6ph_codegen_DW->H_a,
                        rtElectricalID_6ph_codegen_DW->i_est_l,
                        rtElectricalID_6ph_codegen_DW);

        /* '<S6>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S6>:35:9' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph,voltage_correction); */
        Subcha_btw5_MeasureStepRespon_g
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.z2,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.z2,
           rtElectricalID_6ph_codegen_DW->voltage_correction_h,
           rtElectricalID_6ph_codegen_DW);

        /* '<S6>:35:10' counter = counter +1; */
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
        switch (rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S6>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Merge: '<S1>/ Merge ' */
          /* Exit 'stepResponse': '<S6>:35' */
          /* '<S6>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
          rtElectricalID_6ph_codegen_DW->is_c14_sYmfHmduXqEFQQp7CWY1xuF_ =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitLock;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'waitLock': '<S1>:1021' */
        /* '<S1>:1021:3' ElectricalID_FOC_output.activeState = uint16(147); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 147U;
      }
      break;

     case IN_Subchart_Step_Response5:
      /* During 'Subchart_Step_Response5': '<S1>:1025' */
      /* During: Subchart_Step_Response_6ph */
      if (rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ ==
          IN_Levenberg_Marquardt) {
        /* During 'Levenberg_Marquardt': '<S7>:40' */
        /* '<S7>:61:1' sf_internal_predicateOutput = counter == 500; */
        if (rtElectricalID_6ph_codegen_DW->counter_i == 500U) {
          /* Transition: '<S7>:61' */
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
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
        /* '<S7>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
        rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
          IN_Levenberg_Marquardt;

        /* Entry 'Levenberg_Marquardt': '<S7>:40' */
        rtElectricalID_6ph_codegen_DW->e_o = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[0] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[1] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[2] = 0.0F;
        rtElectricalID_6ph_codegen_DW->H_a[3] = 0.0F;
        n_iters_a = 100U;
        rtElectricalID_6ph_codegen_DW->lambda_nm = 0.01F;
        updateJ_n = true;
        memset(&rtElectricalID_6ph_codegen_DW->d_c[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->i_est_l[0], 0, sizeof(real32_T) <<
               11U);
        memset(&rtElectricalID_6ph_codegen_DW->J[0], 0, sizeof(real32_T) << 12U);

        /* '<S7>:40:3' counter = 1; */
        rtElectricalID_6ph_codegen_DW->counter_i = 1U;

        /* '<S7>:40:4' LM_algorithm; */
        LM_algorithm_i(&rtElectricalID_6ph_codegen_U->GlobalConfig_out,
                       &rtElectricalID_6ph_codegen_DW->R_est_c,
                       &rtElectricalID_6ph_codegen_DW->L_est_mb, &updateJ_n,
                       &rtElectricalID_6ph_codegen_DW->lambda_nm,
                       &rtElectricalID_6ph_codegen_DW->e_o, &n_iters_a,
                       rtElectricalID_6ph_codegen_DW->H_a,
                       rtElectricalID_6ph_codegen_DW->i_est_l,
                       rtElectricalID_6ph_codegen_DW);

        /* '<S7>:40:5' R_est = (R_est-R_corr); */
      } else {
        /* Inport: '<Root>/ActualValues' */
        /* '<S7>:35:9' MeasureStepResponse(ActualValues.v_dq_6ph,ActualValues.i_dq_6ph,voltage_correction); */
        Subch_btw5m_MeasureStepRespon_e
          (rtElectricalID_6ph_codegen_U->ActualValues.v_dq_6ph.q,
           rtElectricalID_6ph_codegen_U->ActualValues.i_dq_6ph.q,
           rtElectricalID_6ph_codegen_DW->voltage_correction,
           rtElectricalID_6ph_codegen_DW);

        /* '<S7>:35:10' counter = counter +1; */
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
        switch (rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_)
        {
         case IN_Levenberg_Marquardt:
          /* Exit 'Levenberg_Marquardt': '<S7>:40' */
          rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_stepResponse:
          /* Merge: '<S1>/ Merge ' */
          /* Exit 'stepResponse': '<S7>:35' */
          /* '<S7>:35:12' ElectricalID_output  = ResetDutyCycle(ElectricalID_output); */
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
          rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
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
        /* '<S1>:53:10' ElectricalID_output.thetaOffset = ActualValues.theta_m; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.thetaOffset =
          rtElectricalID_6ph_codegen_U->ActualValues.theta_m;
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
        rtElectricalID_6ph_codegen_DW->is_c14_s4NNbI5CtT2O66hxvHmQTTE_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_p = 0;
               rtElectricalID_6ph_codegen_DW->i_p < 6;
               rtElectricalID_6ph_codegen_DW->i_p++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD_p[6 *
              rtElectricalID_6ph_codegen_DW->i_p +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_p];
          }
        }

        /* setpoints in abc */
        /* '<S2>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_nm =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* set DutyCycles */
        /* '<S2>:35:7' voltage_correction = (GlobalConfig.voltage_measurement_Rp+GlobalConfig.voltage_measurement_Rs)/GlobalConfig.voltage_measurement_Rp; */
        rtElectricalID_6ph_codegen_DW->voltage_correction_bj =
          (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp
           + rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs)
          /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp;

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response' */
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
      if (rtElectricalID_6ph_codegen_DW->one_sec_transition_counter ==
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
        rtElectricalID_6ph_codegen_DW->e_o = (real32_T)
          rtElectricalID_6ph_codegen_DW->counter *
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR * 2.0F;

        /* '<S1>:3:8' if(DutyCycle_filt > 1) */
        if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* '<S1>:3:9' DutyCycle_filt = single(1.0); */
          rtElectricalID_6ph_codegen_DW->e_o = 1.0F;
        }

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:3:11' ElectricalID_output.PWM_Switch_0 = single(DutyCycle*DutyCycle_filt); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
          rtElectricalID_6ph_codegen_DW->DutyCycle *
          rtElectricalID_6ph_codegen_DW->e_o;

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
      /* During 'findDutyCycle': '<S1>:789' */
      /* '<S1>:921:1' sf_internal_predicateOutput = DC_valid == 1; */
      if (rtElectricalID_6ph_codegen_DW->DC_valid) {
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

        /* '<S1>:789:15' if(DC_valid==0) */
      } else if (!rtElectricalID_6ph_codegen_DW->DC_valid) {
        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:789:16' ElectricalID_output.PWM_Switch_0 = single(DutyCycle); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
          rtElectricalID_6ph_codegen_DW->DutyCycle;

        /* Set DC */
        /* '<S1>:789:17' if(counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
        rtElectricalID_6ph_codegen_DW->e_o = roundf(0.4F /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID_6ph_codegen_DW->e_o < 4.2949673E+9F) {
          if (rtElectricalID_6ph_codegen_DW->e_o >= 0.0F) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = (uint32_T)
              rtElectricalID_6ph_codegen_DW->e_o;
          } else {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
          }
        } else {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
        }

        if (rtElectricalID_6ph_codegen_DW->counter <
            rtElectricalID_6ph_codegen_DW->exitPortIndex) {
          /* Wait several time for step response to rise */
          /* '<S1>:789:18' counter = counter +1; */
          rtElectricalID_6ph_codegen_DW->exitPortIndex =
            rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
          if (rtElectricalID_6ph_codegen_DW->counter + 1U <
              rtElectricalID_6ph_codegen_DW->counter) {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          rtElectricalID_6ph_codegen_DW->counter =
            rtElectricalID_6ph_codegen_DW->exitPortIndex;
        } else {
          if (rtElectricalID_6ph_codegen_DW->e_o < 4.2949673E+9F) {
            if (rtElectricalID_6ph_codegen_DW->e_o >= 0.0F) {
              rtElectricalID_6ph_codegen_DW->exitPortIndex = (uint32_T)
                rtElectricalID_6ph_codegen_DW->e_o;
            } else {
              rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
            }
          } else {
            rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
          }

          if (rtElectricalID_6ph_codegen_DW->counter >=
              rtElectricalID_6ph_codegen_DW->exitPortIndex) {
            rtElectricalID_6ph_codegen_DW->e_o = roundf(0.5F /
              rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
            if (rtElectricalID_6ph_codegen_DW->e_o < 4.2949673E+9F) {
              if (rtElectricalID_6ph_codegen_DW->e_o >= 0.0F) {
                rtElectricalID_6ph_codegen_DW->exitPortIndex = (uint32_T)
                  rtElectricalID_6ph_codegen_DW->e_o;
              } else {
                rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
              }
            } else {
              rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
            }

            if (rtElectricalID_6ph_codegen_DW->counter <
                rtElectricalID_6ph_codegen_DW->exitPortIndex) {
              /* '<S1>:789:19' elseif(counter >= uint32(0.4/GlobalConfig.sampleTimeISR) &&.... */
              /* '<S1>:789:20'             counter < uint32(0.5/GlobalConfig.sampleTimeISR)) */
              /* . */
              /* record current - WHY NOW? */
              /* '<S1>:789:21' counter = counter +1; */
              rtElectricalID_6ph_codegen_DW->exitPortIndex =
                rtElectricalID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
              if (rtElectricalID_6ph_codegen_DW->counter + 1U <
                  rtElectricalID_6ph_codegen_DW->counter) {
                rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
              }

              rtElectricalID_6ph_codegen_DW->counter =
                rtElectricalID_6ph_codegen_DW->exitPortIndex;

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
        }
      }
      break;

     case IN_measure_psiPM:
      /* During 'measure_psiPM': '<S1>:405' */
      /* '<S1>:406:1' sf_internal_predicateOutput = counter==10000; */
      if (rtElectricalID_6ph_codegen_DW->counter == 10000U) {
        /* Transition: '<S1>:406' */
        /* Exit 'measure_psiPM': '<S1>:405' */
        /* '<S1>:405:10' analysis = FFTRecordedVoltage(analysis,voltage_meas_array,GlobalConfig.sampleTimeISR); */
        FFTRecordedVoltage(&rtElectricalID_6ph_codegen_DW->analysis,
                           rtElectricalID_6ph_codegen_DW->voltage_meas_array,
                           rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR,
                           rtElectricalID_6ph_codegen_DW);

        /* '<S1>:405:11' analysis = FindPsiPMs(analysis); */
        rtElectricalID_6ph_codegen_DW->r =
          rtElectricalID_6ph_codegen_DW->analysis;
        FindPsiPMs(&rtElectricalID_6ph_codegen_DW->r,
                   &rtElectricalID_6ph_codegen_DW->analysis);

        /* '<S1>:405:12' analysis = PsiCompensation(analysis,GlobalConfig.voltage_measurement_Rs,GlobalConfig.voltage_measurement_Rp,GlobalConfig.voltage_measurement_C); */
        rtElectricalID_6ph_codegen_DW->r =
          rtElectricalID_6ph_codegen_DW->analysis;
        PsiCompensation(&rtElectricalID_6ph_codegen_DW->r,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp,
                        rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_C,
                        &rtElectricalID_6ph_codegen_DW->analysis);

        /* '<S1>:405:13' counter = uint32(1); */
        rtElectricalID_6ph_codegen_DW->counter = 1U;
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_stop;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'stop': '<S1>:361' */
        /* state 10.1 */
        /* '<S1>:361:3' ElectricalID_FOC_output.activeState = uint16(152); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 152U;

        /* '<S1>:361:4' ElectricalID_FOC_output.n_ref_FOC = single(0); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.n_ref_FOC = 0.0F;

        /* '<S1>:361:5' ElectricalID_FOC_output.resetIntegrator = boolean(1); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.resetIntegrator =
          true;
      } else {
        /* '<S1>:405:7' voltage_meas_array(counter-1) = ActualValues.v_abc_6ph.a1; */
        rtElectricalID_6ph_codegen_DW->exitPortIndex =
          rtElectricalID_6ph_codegen_DW->counter - /*MW:OvSatOk*/ 1U;
        if (rtElectricalID_6ph_codegen_DW->counter - 1U >
            rtElectricalID_6ph_codegen_DW->counter) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
        }

        /* Inport: '<Root>/ActualValues' */
        rtElectricalID_6ph_codegen_DW->voltage_meas_array[(int32_T)
          rtElectricalID_6ph_codegen_DW->exitPortIndex - 1] =
          rtElectricalID_6ph_codegen_U->ActualValues.v_abc_6ph.a1;

        /* '<S1>:405:8' counter = counter + 1; */
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
        rtElectricalID_6ph_codegen_DW->e_o = roundf(3.0F /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
        if (rtElectricalID_6ph_codegen_DW->e_o < 4.2949673E+9F) {
          if (rtElectricalID_6ph_codegen_DW->e_o >= 0.0F) {
            rtElectricalID_6ph_codegen_DW->wait_count = (uint32_T)
              rtElectricalID_6ph_codegen_DW->e_o;
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

     case IN_waitAccept:
      /* During 'waitAccept': '<S1>:1028' */
      /* '<S1>:408:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT==1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:408' */
        rtElectricalID_6ph_codegen_DW->is_ElectricalID = IN_waitSetRPM;

        /* Outport: '<Root>/ElectricalID_FOC_output' */
        /* Entry 'waitSetRPM': '<S1>:1047' */
        /* '<S1>:1047:2' ElectricalID_FOC_output.activeState = uint16(150); */
        rtElectricalID_6ph_codegen_Y->ElectricalID_FOC_output.activeState = 150U;

        /* Merge: '<S1>/ Merge ' */
        /* '<S1>:1047:3' ElectricalID_output.enable_TriState = boolean([1 1 1]); */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[0] =
          true;
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[1] =
          true;
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.enable_TriState[2] =
          true;

        /* '<S1>:1047:4' ElectricalID_output.enable_TriState_set_2 = boolean([1 1 1]); */
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[0] = true;
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[1] = true;
        rtElectricalID_6ph_codegen_DW->
          ElectricalID_output.enable_TriState_set_2[2] = true;
      }
      break;

     case IN_waitLock:
      /* Inport: '<Root>/ElectricalIDConfig' */
      /* During 'waitLock': '<S1>:1021' */
      /* '<S1>:1026:1' sf_internal_predicateOutput = GlobalConfig.ACCEPT == 1&&ElectricalIDConfig.identLq == 1; */
      if (rtElectricalID_6ph_codegen_U->GlobalConfig_out.ACCEPT &&
          rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
        /* Transition: '<S1>:1026' */
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
        rtElectricalID_6ph_codegen_DW->is_c14_suvd7asaAR1GIT3n1KH4HNC_ =
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
          for (rtElectricalID_6ph_codegen_DW->i_p = 0;
               rtElectricalID_6ph_codegen_DW->i_p < 6;
               rtElectricalID_6ph_codegen_DW->i_p++) {
            rtElectricalID_6ph_codegen_DW->
              setp_abc[rtElectricalID_6ph_codegen_DW->i] +=
              rtElectricalID_6ph_codegen_DW->inv_VSD[6 *
              rtElectricalID_6ph_codegen_DW->i_p +
              rtElectricalID_6ph_codegen_DW->i] *
              rtElectricalID_6ph_codegen_DW->
              setp_dq[rtElectricalID_6ph_codegen_DW->i_p];
          }
        }

        /* setpoints in abc */
        /* '<S7>:35:6' ElectricalID_output = SetpVectorToDutyCycle6ph(ElectricalID_output,ActualValues.V_DC,setp_abc); */
        /* Copy ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:3' ElectricalID_output = ElectricalID_output_in; */
        /* Write DutyCycle to ElectricalID_output */
        /* 'SetpVectorToDutyCycle6ph:5' ElectricalID_output.PWM_Switch_0 = GenerateDutyCycle(VDC,SetpVector(1)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->lambda_nm =
          rtElectricalID_6ph_codegen_U->ActualValues.V_DC / 2.0F;
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[0] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_0 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:6' ElectricalID_output.PWM_Switch_2 = GenerateDutyCycle(VDC,SetpVector(2)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[1] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:7' ElectricalID_output.PWM_Switch_4 = GenerateDutyCycle(VDC,SetpVector(3)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[2] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 = 1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_4 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:8' ElectricalID_output.PWM_Switch_a2 = GenerateDutyCycle(VDC,SetpVector(4)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[3] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_a2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:9' ElectricalID_output.PWM_Switch_b2 = GenerateDutyCycle(VDC,SetpVector(5)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[4] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_b2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* 'SetpVectorToDutyCycle6ph:10' ElectricalID_output.PWM_Switch_c2 = GenerateDutyCycle(VDC,SetpVector(6)); */
        /* 'GenerateDutyCycle:2' DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); */
        rtElectricalID_6ph_codegen_DW->e_o =
          (rtElectricalID_6ph_codegen_DW->setp_abc[5] /
           rtElectricalID_6ph_codegen_DW->lambda_nm + 1.0F) / 2.0F;

        /* 'GenerateDutyCycle:3' if(DutyCycle < 0) */
        if (rtElectricalID_6ph_codegen_DW->e_o < 0.0F) {
          /* 'GenerateDutyCycle:4' out = single(0); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            0.0F;
        } else if (rtElectricalID_6ph_codegen_DW->e_o > 1.0F) {
          /* 'GenerateDutyCycle:5' elseif (DutyCycle > 1) */
          /* 'GenerateDutyCycle:6' out = single(1); */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            1.0F;
        } else {
          /* 'GenerateDutyCycle:7' else */
          /* 'GenerateDutyCycle:8' out = DutyCycle; */
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.PWM_Switch_c2 =
            rtElectricalID_6ph_codegen_DW->e_o;
        }

        /* set DutyCycles */
        /* '<S7>:35:7' voltage_correction = (GlobalConfig.voltage_measurement_Rp+GlobalConfig.voltage_measurement_Rs)/GlobalConfig.voltage_measurement_Rp; */
        rtElectricalID_6ph_codegen_DW->voltage_correction =
          (rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp
           + rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rs)
          /
          rtElectricalID_6ph_codegen_U->GlobalConfig_out.voltage_measurement_Rp;

        /* End of Chart: '<S1>/ElectricalID.Subchart_Step_Response5' */

        /* '<S1>:1029:1' sf_internal_predicateOutput = ElectricalIDConfig.identLq == 0; */
      } else if (!rtElectricalID_6ph_codegen_U->ElectricalIDConfig.identLq) {
        /* Merge: '<S1>/ Merge ' */
        /* Transition: '<S1>:1029' */
        /* '<S1>:1029:2' ElectricalID_output.inductances_6ph.q=ElectricalID_output.inductances_6ph.d; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.q =
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.inductances_6ph.d;

        /* '<S1>:1029:3' ElectricalID_output.resistances_6ph.q=ElectricalID_output.resistances_6ph.d; */
        rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.q =
          rtElectricalID_6ph_codegen_DW->ElectricalID_output.resistances_6ph.d;
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
      }
      break;

     case IN_waitSetRPM:
      waitSetRPM(rtElectricalID_6ph_codegen_U, rtElectricalID_6ph_codegen_Y,
                 rtElectricalID_6ph_codegen_DW);
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

    if (guard1) {
      rtElectricalID_6ph_codegen_DW->e_o = roundf(0.5F /
        rtElectricalID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
      if (rtElectricalID_6ph_codegen_DW->e_o < 4.2949673E+9F) {
        if (rtElectricalID_6ph_codegen_DW->e_o >= 0.0F) {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = (uint32_T)
            rtElectricalID_6ph_codegen_DW->e_o;
        } else {
          rtElectricalID_6ph_codegen_DW->exitPortIndex = 0U;
        }
      } else {
        rtElectricalID_6ph_codegen_DW->exitPortIndex = MAX_uint32_T;
      }

      if (rtElectricalID_6ph_codegen_DW->counter ==
          rtElectricalID_6ph_codegen_DW->exitPortIndex) {
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

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

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
    rtElectricalID_6ph_codegen_DW->counter_n = 1U;
    rtElectricalID_6ph_codegen_DW->z_c = 1U;
    rtElectricalID_6ph_codegen_DW->counter_o = 1U;
    rtElectricalID_6ph_codegen_DW->z_bs = 1U;
    rtElectricalID_6ph_codegen_DW->counter_f = 1U;
    rtElectricalID_6ph_codegen_DW->z_p = 1U;
    rtElectricalID_6ph_codegen_DW->counter_g = 1U;
    rtElectricalID_6ph_codegen_DW->z_k = 1U;
    rtElectricalID_6ph_codegen_DW->counter_j = 1U;
    rtElectricalID_6ph_codegen_DW->z_b = 1U;
    for (i = 0; i < 36; i++) {
      real32_T tmp;
      tmp = tmp_0[i];
      rtElectricalID_6ph_codegen_DW->inv_VSD_p[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_l[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_m[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_a[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD_i[i] = tmp;
      rtElectricalID_6ph_codegen_DW->inv_VSD[i] = tmp;
    }

    rtElectricalID_6ph_codegen_DW->counter_i = 1U;
    rtElectricalID_6ph_codegen_DW->z = 1U;
    memset(&rtElectricalID_6ph_codegen_DW->analysis.amplitudes[0], 0, 5001U *
           sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->analysis.frequencies[0], 0, 5001U *
           sizeof(real32_T));
    memset(&rtElectricalID_6ph_codegen_DW->analysis.angles[0], 0, 5001U * sizeof
           (real32_T));
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
      rtElectricalID_6ph_codegen_DW->analysis.psi_pm[i] = 0.0F;
      rtElectricalID_6ph_codegen_DW->analysis.psi_freq[i] = 0.0F;
      rtElectricalID_6ph_codegen_DW->analysis.psi_angle[i] = 0.0F;
      rtElectricalID_6ph_codegen_DW->ElectricalID_output.psi_pm[i] = 0.0F;
    }

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