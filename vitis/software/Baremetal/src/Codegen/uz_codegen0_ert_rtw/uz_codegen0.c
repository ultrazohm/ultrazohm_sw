/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.98
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 28 15:29:21 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "uz_codegen0.h"

/* Named constants for Chart: '<Root>/uz_codegen' */
#define IN_InProcess                   ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Reset                       ((uint8_T)2U)
#define IN_Start                       ((uint8_T)3U)
#define NumBitsPerChar                 8U

static void Subsystempi2delay(uint8_T rtu_Enable, real32_T rtu_dq, real32_T
  rtu_dq_a, real32_T rtu_wt, real32_T *rty_alpha_beta, real32_T
  *rty_alpha_beta_d);
static void Subsystem1(uint8_T rtu_Enable, real32_T rtu_dq, real32_T rtu_dq_g,
  real32_T rtu_wt, real32_T *rty_alpha_beta, real32_T *rty_alpha_beta_k);
static void CurrentController_Init(DW_CurrentController *localDW);
static void CurrentController_Enable(DW_CurrentController *localDW);
static void CurrentController(RT_MODEL * const rtM, real32_T rtu_ia, real32_T
  rtu_ib, real32_T rtu_ic, real32_T rtu_w_el, int8_T rtu_flg_PreCtrl, real32_T
  rtu_theta_el, real32_T rtu_U_IC, real32_T rtu_id_ref, real32_T rtu_iq_ref,
  int8_T rtu_flg_LimitUdUq, real32_T rtu_Kp_Iq, real32_T rtu_Ki_Iq, real32_T
  rtu_Kp_Id, real32_T rtu_Ki_Id, int8_T rtu_flg_SpaceVectorModulation, int8_T
  rtu_flg_Reset, int8_T rtu_flg_deadTimeCompensation, int8_T
  rtu_flg_theta_el_compensation, real32_T rty_ua[3], real32_T *rty_ub, real32_T *
  rty_uc, real32_T rty_Iq_ist[2], real32_T *rty_Id_ist, real32_T *rty_ud_soll,
  real32_T *rty_uq_soll, const ConstB_CurrentController *localC,
  DW_CurrentController *localDW);
static void SpeedController_Init(DW_SpeedController *localDW);
static void SpeedController_Enable(DW_SpeedController *localDW);
static void SpeedController(RT_MODEL * const rtM, real32_T rtu_id_ref, real32_T
  rtu_iq_ref, real32_T rtu_n_ref, real32_T rtu_n_ist, int8_T
  rtu_flg_SpeedControl, int8_T rtu_flg_FieldWeakening, real32_T rtu_Kp_Speed,
  real32_T rtu_Ki_Speed, real32_T rtu_I_max, real32_T rtu_U_DC, int8_T rtu_RESET,
  real32_T *rty_id_soll, real32_T *rty_iq_soll, DW_SpeedController *localDW);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
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
 * Output and update for enable system:
 *    '<S126>/Subsystem - pi//2 delay'
 *    '<S132>/Subsystem - pi//2 delay'
 */
static void Subsystempi2delay(uint8_T rtu_Enable, real32_T rtu_dq, real32_T
  rtu_dq_a, real32_T rtu_wt, real32_T *rty_alpha_beta, real32_T
  *rty_alpha_beta_d)
{
  real32_T tmp;
  real32_T tmp_0;

  /* Outputs for Enabled SubSystem: '<S126>/Subsystem - pi//2 delay' incorporates:
   *  EnablePort: '<S129>/Enable'
   */
  if (rtu_Enable > 0) {
    /* Fcn: '<S129>/Fcn' incorporates:
     *  Fcn: '<S129>/Fcn1'
     */
    tmp = cosf(rtu_wt);
    tmp_0 = sinf(rtu_wt);
    *rty_alpha_beta = rtu_dq * tmp_0 + rtu_dq_a * tmp;

    /* Fcn: '<S129>/Fcn1' */
    *rty_alpha_beta_d = -rtu_dq * tmp + rtu_dq_a * tmp_0;
  }

  /* End of Outputs for SubSystem: '<S126>/Subsystem - pi//2 delay' */
}

/*
 * Output and update for enable system:
 *    '<S126>/Subsystem1'
 *    '<S132>/Subsystem1'
 */
static void Subsystem1(uint8_T rtu_Enable, real32_T rtu_dq, real32_T rtu_dq_g,
  real32_T rtu_wt, real32_T *rty_alpha_beta, real32_T *rty_alpha_beta_k)
{
  real32_T tmp;
  real32_T tmp_0;

  /* Outputs for Enabled SubSystem: '<S126>/Subsystem1' incorporates:
   *  EnablePort: '<S130>/Enable'
   */
  if (rtu_Enable > 0) {
    /* Fcn: '<S130>/Fcn' incorporates:
     *  Fcn: '<S130>/Fcn1'
     */
    tmp = sinf(rtu_wt);
    tmp_0 = cosf(rtu_wt);
    *rty_alpha_beta = rtu_dq * tmp_0 - rtu_dq_g * tmp;

    /* Fcn: '<S130>/Fcn1' */
    *rty_alpha_beta_k = rtu_dq * tmp + rtu_dq_g * tmp_0;
  }

  /* End of Outputs for SubSystem: '<S126>/Subsystem1' */
}

/* System initialize for function-call system: '<S1>/CurrentController' */
static void CurrentController_Init(DW_CurrentController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S43>/Integrator' */
  localDW->Integrator_PrevResetState = 0;
  localDW->Integrator_PREV_U = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_PrevResetState_p = 0;
  localDW->Integrator_PREV_U_e = 0.0F;
}

/* Enable for function-call system: '<S1>/CurrentController' */
static void CurrentController_Enable(DW_CurrentController *localDW)
{
  localDW->CurrentController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S43>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 1U;

  /* Enable for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE_b = 1U;
}

/* Output and update for function-call system: '<S1>/CurrentController' */
static void CurrentController(RT_MODEL * const rtM, real32_T rtu_ia, real32_T
  rtu_ib, real32_T rtu_ic, real32_T rtu_w_el, int8_T rtu_flg_PreCtrl, real32_T
  rtu_theta_el, real32_T rtu_U_IC, real32_T rtu_id_ref, real32_T rtu_iq_ref,
  int8_T rtu_flg_LimitUdUq, real32_T rtu_Kp_Iq, real32_T rtu_Ki_Iq, real32_T
  rtu_Kp_Id, real32_T rtu_Ki_Id, int8_T rtu_flg_SpaceVectorModulation, int8_T
  rtu_flg_Reset, int8_T rtu_flg_deadTimeCompensation, int8_T
  rtu_flg_theta_el_compensation, real32_T rty_ua[3], real32_T *rty_ub, real32_T *
  rty_uc, real32_T rty_Iq_ist[2], real32_T *rty_Id_ist, real32_T *rty_ud_soll,
  real32_T *rty_uq_soll, const ConstB_CurrentController *localC,
  DW_CurrentController *localDW)
{
  int32_T quadrant;
  real32_T Integrator;
  real32_T U_max;
  real32_T c;
  real32_T rtb_Gain;
  real32_T rtb_Gain1_lc;
  real32_T rtb_SignPreIntegrator;
  real32_T rtb_Sum;
  real32_T rtb_Sum_dd;
  real32_T rtb_Switch1_h;
  real32_T rtb_UdV;
  real32_T rtb_error;
  real32_T u2;
  uint32_T CurrentController_ELAPS_T;
  if (localDW->CurrentController_RESET_ELAPS_T) {
    CurrentController_ELAPS_T = 0U;
  } else {
    CurrentController_ELAPS_T = rtM->Timing.clockTick0 -
      localDW->CurrentController_PREV_T;
  }

  localDW->CurrentController_PREV_T = rtM->Timing.clockTick0;
  localDW->CurrentController_RESET_ELAPS_T = false;
  for (quadrant = 0; quadrant < 3; quadrant++) {
    /* Gain: '<S116>/Gain1' incorporates:
     *  Gain: '<S116>/Gain3'
     *  SignalConversion generated from: '<S116>/Gain3'
     */
    localDW->Gain1[quadrant] = 0.666666687F * (rtConstP.Gain3_Gain_i[quadrant +
      6] * rtu_ic + (rtConstP.Gain3_Gain_i[quadrant + 3] * rtu_ib +
                     rtConstP.Gain3_Gain_i[quadrant] * rtu_ia));
  }

  /* Outputs for Enabled SubSystem: '<S115>/Subsystem1' incorporates:
   *  EnablePort: '<S120>/Enable'
   */
  /* Fcn: '<S120>/Fcn' incorporates:
   *  Fcn: '<S120>/Fcn1'
   */
  rtb_Sum = sinf(rtu_theta_el);
  rtb_Sum_dd = cosf(rtu_theta_el);

  /* Switch: '<S115>/Switch' incorporates:
   *  Fcn: '<S120>/Fcn'
   *  Fcn: '<S120>/Fcn1'
   */
  rty_Iq_ist[0] = localDW->Gain1[0] * rtb_Sum_dd + localDW->Gain1[1] * rtb_Sum;
  rty_Iq_ist[1] = -localDW->Gain1[0] * rtb_Sum + localDW->Gain1[1] * rtb_Sum_dd;

  /* End of Outputs for SubSystem: '<S115>/Subsystem1' */

  /* Sum: '<S7>/Subtract' */
  rtb_error = rtu_id_ref - rty_Iq_ist[0];

  /* DiscreteIntegrator: '<S43>/Integrator' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   */
  if (localDW->Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S43>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else if ((rtu_flg_Reset != 0) || (localDW->Integrator_PrevResetState != 0))
  {
    localDW->Integrator_DSTATE = 0.0F;

    /* DiscreteIntegrator: '<S43>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S43>/Integrator' */
    Integrator = 2.5E-5F * (real32_T)CurrentController_ELAPS_T
      * localDW->Integrator_PREV_U + localDW->Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S43>/Integrator' */

  /* Sum: '<S53>/Sum' incorporates:
   *  Product: '<S48>/PProd Out'
   */
  rtb_Sum = rtb_error * rtu_Kp_Id + Integrator;

  /* Switch: '<S51>/Switch2' incorporates:
   *  Gain: '<S7>/Gain1'
   *  RelationalOperator: '<S51>/LowerRelop1'
   *  RelationalOperator: '<S51>/UpperRelop'
   *  Switch: '<S51>/Switch'
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  if (rtb_Sum > localDW->UnitDelay1_DSTATE) {
    rtb_Sum = localDW->UnitDelay1_DSTATE;
  } else if (rtb_Sum < -localDW->UnitDelay1_DSTATE) {
    /* Switch: '<S51>/Switch' incorporates:
     *  Gain: '<S7>/Gain1'
     */
    rtb_Sum = -localDW->UnitDelay1_DSTATE;
  }

  /* End of Switch: '<S51>/Switch2' */

  /* Switch: '<S6>/Switch' incorporates:
   *  Constant: '<S6>/Constant1'
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Product'
   */
  if (rtu_flg_PreCtrl > 0) {
    rtb_Switch1_h = -1.6E-5F * rty_Iq_ist[1] * rtu_w_el;
  } else {
    rtb_Switch1_h = 0.0F;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Sum: '<S4>/Add' */
  rtb_UdV = rtb_Sum + rtb_Switch1_h;

  /* Sum: '<S8>/Subtract' */
  rtb_Sum = rtu_iq_ref - rty_Iq_ist[1];

  /* DiscreteIntegrator: '<S96>/Integrator' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   */
  if (localDW->Integrator_SYSTEM_ENABLE_b != 0) {
    /* DiscreteIntegrator: '<S96>/Integrator' */
    rtb_Gain1_lc = localDW->Integrator_DSTATE_b;
  } else if ((rtu_flg_Reset != 0) || (localDW->Integrator_PrevResetState_p != 0))
  {
    localDW->Integrator_DSTATE_b = 0.0F;

    /* DiscreteIntegrator: '<S96>/Integrator' */
    rtb_Gain1_lc = localDW->Integrator_DSTATE_b;
  } else {
    /* DiscreteIntegrator: '<S96>/Integrator' */
    rtb_Gain1_lc = 2.5E-5F * (real32_T)CurrentController_ELAPS_T
      * localDW->Integrator_PREV_U_e + localDW->Integrator_DSTATE_b;
  }

  /* End of DiscreteIntegrator: '<S96>/Integrator' */

  /* Sum: '<S106>/Sum' incorporates:
   *  Product: '<S101>/PProd Out'
   */
  rtb_Sum_dd = rtb_Sum * rtu_Kp_Iq + rtb_Gain1_lc;

  /* Switch: '<S6>/Switch1' incorporates:
   *  Constant: '<S6>/Constant'
   *  Constant: '<S6>/Constant1'
   *  Gain: '<S6>/Gain2'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Add'
   */
  if (rtu_flg_PreCtrl > 0) {
    rtb_Switch1_h = (1.6E-5F * rty_Iq_ist[0] + 0.0048F) * rtu_w_el;
  } else {
    rtb_Switch1_h = 0.0F;
  }

  /* End of Switch: '<S6>/Switch1' */

  /* Switch: '<S104>/Switch2' incorporates:
   *  Gain: '<S8>/Gain1'
   *  RelationalOperator: '<S104>/LowerRelop1'
   *  RelationalOperator: '<S104>/UpperRelop'
   *  Switch: '<S104>/Switch'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  if (rtb_Sum_dd > localDW->UnitDelay_DSTATE) {
    rtb_SignPreIntegrator = localDW->UnitDelay_DSTATE;
  } else if (rtb_Sum_dd < -localDW->UnitDelay_DSTATE) {
    /* Switch: '<S104>/Switch' incorporates:
     *  Gain: '<S8>/Gain1'
     */
    rtb_SignPreIntegrator = -localDW->UnitDelay_DSTATE;
  } else {
    rtb_SignPreIntegrator = rtb_Sum_dd;
  }

  /* End of Switch: '<S104>/Switch2' */

  /* Sum: '<S4>/Add1' */
  rtb_SignPreIntegrator += rtb_Switch1_h;

  /* Gain: '<S9>/Gain' */
  rtb_Gain = 0.577350259F * rtu_U_IC;

  /* MATLAB Function: '<S9>/MATLAB Function' */
  /* Voltage Limitation Quang S.183 */
  /* MATLAB Function 'uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung/MATLAB Function': '<S114>:1' */
  /* '<S114>:1:5' if flg_limitUdUq == 1 */
  if (rtu_flg_LimitUdUq == 1) {
    /* '<S114>:1:6' if 0.95 * U_max_dq > sqrt(ud_soll^2 + uq_soll^2) */
    if (0.95F * rtb_Gain > sqrtf(rtb_UdV * rtb_UdV + rtb_SignPreIntegrator *
         rtb_SignPreIntegrator)) {
      /* Update for UnitDelay: '<S4>/Unit Delay1' */
      /* Limitation is not necessary */
      /* '<S114>:1:8' ud_ref = ud_soll; */
      /* '<S114>:1:9' uq_ref = uq_soll; */
      /* '<S114>:1:10' ud_lim = single(0.95) * U_max_dq; */
      localDW->UnitDelay1_DSTATE = 0.95F * rtb_Gain;

      /* '<S114>:1:11' uq_lim = single(0.95) * U_max_dq; */
      rtb_Switch1_h = 0.95F * rtb_Gain;
    } else {
      /* '<S114>:1:12' else */
      /* '<S114>:1:13' if sign(w_el) ~= sign(iq_soll) */
      if (rtu_w_el < 0.0F) {
        rtb_Switch1_h = -1.0F;
      } else if (rtu_w_el > 0.0F) {
        rtb_Switch1_h = 1.0F;
      } else if (rtu_w_el == 0.0F) {
        rtb_Switch1_h = 0.0F;
      } else {
        rtb_Switch1_h = (rtNaNF);
      }

      if (rtu_iq_ref < 0.0F) {
        localDW->a_W_on = -1.0F;
      } else if (rtu_iq_ref > 0.0F) {
        localDW->a_W_on = 1.0F;
      } else if (rtu_iq_ref == 0.0F) {
        localDW->a_W_on = 0.0F;
      } else {
        localDW->a_W_on = (rtNaNF);
      }

      if (rtb_Switch1_h != localDW->a_W_on) {
        /* Breaking  */
        /* '<S114>:1:15' if abs(uq_soll) > 0.95 * U_max_dq */
        if (fabsf(rtb_SignPreIntegrator) > 0.95F * rtb_Gain) {
          /* '<S114>:1:16' uq_ref = sign(uq_soll)*0.95*U_max_dq; */
          if (rtb_SignPreIntegrator < 0.0F) {
            rtb_SignPreIntegrator = -1.0F;
          } else if (rtb_SignPreIntegrator > 0.0F) {
            rtb_SignPreIntegrator = 1.0F;
          } else if (rtb_SignPreIntegrator == 0.0F) {
            rtb_SignPreIntegrator = 0.0F;
          } else {
            rtb_SignPreIntegrator = (rtNaNF);
          }

          rtb_SignPreIntegrator = rtb_SignPreIntegrator * 0.95F * rtb_Gain;

          /* '<S114>:1:17' ud_ref = sign(ud_soll)*sqrt(U_max_dq^2 - uq_ref^2); */
          if (rtb_UdV < 0.0F) {
            rtb_UdV = -1.0F;
          } else if (rtb_UdV > 0.0F) {
            rtb_UdV = 1.0F;
          } else if (rtb_UdV == 0.0F) {
            rtb_UdV = 0.0F;
          } else {
            rtb_UdV = (rtNaNF);
          }

          rtb_UdV *= sqrtf(rtb_Gain * rtb_Gain - rtb_SignPreIntegrator *
                           rtb_SignPreIntegrator);
        } else {
          /* '<S114>:1:18' else */
          /* '<S114>:1:19' uq_ref = uq_soll; */
          /* '<S114>:1:20' ud_ref = sign(ud_soll) * sqrt(U_max_dq^2 - uq_ref^2); */
          if (rtb_UdV < 0.0F) {
            rtb_UdV = -1.0F;
          } else if (rtb_UdV > 0.0F) {
            rtb_UdV = 1.0F;
          } else if (rtb_UdV == 0.0F) {
            rtb_UdV = 0.0F;
          } else {
            rtb_UdV = (rtNaNF);
          }

          rtb_UdV *= sqrtf(rtb_Gain * rtb_Gain - rtb_SignPreIntegrator *
                           rtb_SignPreIntegrator);
        }

        /* '<S114>:1:22' uq_lim = single(0.95)*U_max_dq; */
        rtb_Switch1_h = 0.95F * rtb_Gain;

        /* Update for UnitDelay: '<S4>/Unit Delay1' */
        /* '<S114>:1:23' ud_lim = single(sqrt(U_max_dq^2 - uq_ref^2)); */
        localDW->UnitDelay1_DSTATE = sqrtf(rtb_Gain * rtb_Gain -
          rtb_SignPreIntegrator * rtb_SignPreIntegrator);
      } else {
        /* '<S114>:1:24' else */
        /* Acceleration */
        /* '<S114>:1:26' if abs(ud_soll) > 0.95 * U_max_dq */
        if (fabsf(rtb_UdV) > 0.95F * rtb_Gain) {
          /* '<S114>:1:27' ud_ref = sign(ud_soll) * 0.95*U_max_dq; */
          if (rtb_UdV < 0.0F) {
            rtb_UdV = -1.0F;
          } else if (rtb_UdV > 0.0F) {
            rtb_UdV = 1.0F;
          } else if (rtb_UdV == 0.0F) {
            rtb_UdV = 0.0F;
          } else {
            rtb_UdV = (rtNaNF);
          }

          rtb_UdV = rtb_UdV * 0.95F * rtb_Gain;

          /* '<S114>:1:28' uq_ref = sign(uq_soll) * sqrt(U_max_dq^2 - ud_ref^2); */
          if (rtb_SignPreIntegrator < 0.0F) {
            rtb_SignPreIntegrator = -1.0F;
          } else if (rtb_SignPreIntegrator > 0.0F) {
            rtb_SignPreIntegrator = 1.0F;
          } else if (rtb_SignPreIntegrator == 0.0F) {
            rtb_SignPreIntegrator = 0.0F;
          } else {
            rtb_SignPreIntegrator = (rtNaNF);
          }

          rtb_SignPreIntegrator *= sqrtf(rtb_Gain * rtb_Gain - rtb_UdV * rtb_UdV);
        } else {
          /* '<S114>:1:29' else */
          /* '<S114>:1:30' ud_ref = ud_soll; */
          /* '<S114>:1:31' uq_ref = sign(uq_soll) * sqrt(U_max_dq^2 - ud_ref^2); */
          if (rtb_SignPreIntegrator < 0.0F) {
            rtb_SignPreIntegrator = -1.0F;
          } else if (rtb_SignPreIntegrator > 0.0F) {
            rtb_SignPreIntegrator = 1.0F;
          } else if (rtb_SignPreIntegrator == 0.0F) {
            rtb_SignPreIntegrator = 0.0F;
          } else {
            rtb_SignPreIntegrator = (rtNaNF);
          }

          rtb_SignPreIntegrator *= sqrtf(rtb_Gain * rtb_Gain - rtb_UdV * rtb_UdV);
        }

        /* '<S114>:1:33' uq_lim = single(sqrt(U_max_dq^2 - ud_ref^2)); */
        rtb_Switch1_h = sqrtf(rtb_Gain * rtb_Gain - rtb_UdV * rtb_UdV);

        /* Update for UnitDelay: '<S4>/Unit Delay1' */
        /* '<S114>:1:34' ud_lim = single(0.95)*U_max_dq; */
        localDW->UnitDelay1_DSTATE = 0.95F * rtb_Gain;
      }
    }
  } else {
    /* '<S114>:1:37' else */
    /* '<S114>:1:38' ud_ref = ud_soll; */
    /* '<S114>:1:39' uq_ref = uq_soll; */
    /* '<S114>:1:40' uq_lim = single(U_max_dq); */
    rtb_Switch1_h = rtb_Gain;

    /* Update for UnitDelay: '<S4>/Unit Delay1' */
    /* '<S114>:1:41' ud_lim = single(U_max_dq); */
    localDW->UnitDelay1_DSTATE = rtb_Gain;
  }

  /* '<S114>:1:44' ud = ud_ref; */
  *rty_ud_soll = rtb_UdV;

  /* '<S114>:1:45' uq = uq_ref; */
  *rty_uq_soll = rtb_SignPreIntegrator;

  /* End of MATLAB Function: '<S9>/MATLAB Function' */

  /* Switch: '<S121>/Switch' incorporates:
   *  Constant: '<S121>/Constant2'
   *  Gain: '<S121>/Gain2'
   */
  if (rtu_flg_theta_el_compensation > 0) {
    rtb_SignPreIntegrator = 5.0E-5F * rtu_w_el;
  } else {
    rtb_SignPreIntegrator = 0.0F;
  }

  /* End of Switch: '<S121>/Switch' */

  /* Sum: '<S121>/Sum1' */
  rtb_SignPreIntegrator += rtu_theta_el;

  /* Outputs for Enabled SubSystem: '<S126>/Subsystem1' */
  Subsystem1(1, *rty_ud_soll, *rty_uq_soll, rtb_SignPreIntegrator,
             &localDW->Fcn_d, &localDW->Fcn1_o);

  /* End of Outputs for SubSystem: '<S126>/Subsystem1' */

  /* Outputs for Enabled SubSystem: '<S126>/Subsystem - pi//2 delay' */
  Subsystempi2delay(localC->Compare_g, *rty_ud_soll, *rty_uq_soll,
                    rtb_SignPreIntegrator, &localDW->Fcn_g, &localDW->Fcn1_p);

  /* End of Outputs for SubSystem: '<S126>/Subsystem - pi//2 delay' */

  /* Switch: '<S122>/Switch' incorporates:
   *  Constant: '<S122>/Constant2'
   *  Gain: '<S122>/Gain2'
   */
  if (rtu_flg_theta_el_compensation > 0) {
    rtb_SignPreIntegrator = 5.0E-5F * rtu_w_el;
  } else {
    rtb_SignPreIntegrator = 0.0F;
  }

  /* End of Switch: '<S122>/Switch' */

  /* Sum: '<S122>/Sum' */
  rtb_SignPreIntegrator += rtu_theta_el;

  /* Outputs for Enabled SubSystem: '<S132>/Subsystem1' */
  Subsystem1(1, *rty_ud_soll, *rty_uq_soll, rtb_SignPreIntegrator, &localDW->Fcn,
             &localDW->Fcn1);

  /* End of Outputs for SubSystem: '<S132>/Subsystem1' */

  /* Outputs for Enabled SubSystem: '<S132>/Subsystem - pi//2 delay' */
  Subsystempi2delay(localC->Compare_fz, *rty_ud_soll, *rty_uq_soll,
                    rtb_SignPreIntegrator, &localDW->Fcn_b, &localDW->Fcn1_h);

  /* End of Outputs for SubSystem: '<S132>/Subsystem - pi//2 delay' */

  /* MATLAB Function: '<S122>/SpaceVectorModulation' incorporates:
   *  Switch: '<S132>/Switch'
   */
  /* MATLAB Function 'uz_codegen/CurrentController/Modulation/SpaceVectorModulation/SpaceVectorModulation': '<S131>:1' */
  /* '<S131>:1:3' a_U_on=single(0); */
  rtb_SignPreIntegrator = 0.0F;

  /* '<S131>:1:4' a_V_on=single(0); */
  rtb_UdV = 0.0F;

  /* '<S131>:1:5' a_W_on=single(0); */
  localDW->a_W_on = 0.0F;

  /* __%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%_ */
  /* Tr‰gerbasierte Raumzeigermodulation%% */
  /* Eing‰nge: */
  /* U_ZK       -- Zwischenkreisspannung */
  /* u_alpha    -- alphakomponente des Sollspannungsraumzeigers */
  /* u_beta     -- betakomponente des Sollspannungsraumzeigers */
  /* CMP_Period_max_val  -- maximalwert des Dreiecks/S‰gezahnz‰hlers zum Gewichten der Aussteuergrade */
  /* Ausg‰nge: */
  /* CMP_U        -- Vergleichswert U */
  /* CMP_V        -- Vergleichswert V */
  /* CMP_W        -- Vergleichswert W */
  /* sector       -- Ausgabe des Sektors des Spannungszeigers */
  /* Berechnung von a, b, c nach Quang Dittrich S24 */
  /* '<S131>:1:23' a = single(abs(u_alpha) + 0.5774*abs(u_beta)); */
  rtb_Gain = fabsf(localDW->Fcn);
  c = fabsf(localDW->Fcn1);
  localDW->a = 0.5774F * c + rtb_Gain;

  /* '<S131>:1:24' b = single(abs(u_alpha) - 0.5774*abs(u_beta)); */
  localDW->b = rtb_Gain - 0.5774F * fabsf(localDW->Fcn1);

  /* '<S131>:1:25' c = single(1.1547*abs(u_beta)); */
  c *= 1.1547F;

  /* '<S131>:1:27' U_max = single(0.6667) * U_ZK; */
  U_max = 0.6667F * rtu_U_IC;

  /* Maximum Voltage U_ZL/sqrt(3) */
  /* Sektor und Quadranten nach Quang Dittrich S32 */
  /* '<S131>:1:31' if(u_beta < 0) */
  if (localDW->Fcn1 < 0.0F) {
    /* '<S131>:1:32' if (u_alpha <0) */
    if (localDW->Fcn < 0.0F) {
      /* '<S131>:1:33' quadrant=single(3); */
      quadrant = 3;

      /* '<S131>:1:34' if(b < 0) */
      if (localDW->b < 0.0F) {
        /* '<S131>:1:35' sector = single(5); */
        localDW->sector = 5;
      } else {
        /* '<S131>:1:36' else */
        /* '<S131>:1:37' sector = single(4); */
        localDW->sector = 4;
      }
    } else {
      /* '<S131>:1:39' else */
      /* '<S131>:1:40' quadrant=single(4); */
      quadrant = 4;

      /* '<S131>:1:41' if(b < 0) */
      if (localDW->b < 0.0F) {
        /* '<S131>:1:42' sector = single(5); */
        localDW->sector = 5;
      } else {
        /* '<S131>:1:43' else */
        /* '<S131>:1:44' sector = single(6); */
        localDW->sector = 6;
      }
    }

    /* '<S131>:1:48' else */
    /* '<S131>:1:49' if (u_alpha <0) */
  } else if (localDW->Fcn < 0.0F) {
    /* '<S131>:1:50' quadrant=single(2); */
    quadrant = 2;

    /* '<S131>:1:51' if(b < 0) */
    if (localDW->b < 0.0F) {
      /* '<S131>:1:52' sector = single(2); */
      localDW->sector = 2;
    } else {
      /* '<S131>:1:53' else */
      /* '<S131>:1:54' sector = single(3); */
      localDW->sector = 3;
    }
  } else {
    /* '<S131>:1:56' else */
    /* '<S131>:1:57' quadrant=single(1); */
    quadrant = 1;

    /* '<S131>:1:58' if(b < 0) */
    if (localDW->b < 0.0F) {
      /* '<S131>:1:59' sector = single(2); */
      localDW->sector = 2;
    } else {
      /* '<S131>:1:60' else */
      /* '<S131>:1:61' sector = single(1); */
      localDW->sector = 1;
    }
  }

  /* '<S131>:1:66' sector = sector; */
  /* Modulationsfunktionen f¸r Phasen U,V,W */
  /* Erzeugung der Aussteuergrade f¸r die Halbbr¸cken */
  /* --> Erzeugung einer "regulary Sampled SVM" erfolgt anschlieﬂend durch Abtastung */
  /* mit Dreiecksz‰hlern in Hardware. */
  /* '<S131>:1:73' if (sector == 1) */
  if (localDW->sector == 1) {
    /* Quang S.24 and normed to 2/3 U_DC */
    /* '<S131>:1:76' u1 = b/(U_max); */
    localDW->a_W_on = localDW->b / U_max;

    /* '<S131>:1:77' u2 = c/(U_max); */
    u2 = c / U_max;

    /* Quang S.34 */
    /* '<S131>:1:80' a_U_on = single(0.5 + u1*0.5 + u2*0.5); */
    rtb_SignPreIntegrator = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S131>:1:81' a_V_on = single(0.5 - u1*0.5 + u2*0.5); */
    rtb_UdV = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;

    /* '<S131>:1:82' a_W_on = single(0.5 - u1*0.5 - u2*0.5); */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;
  }

  /* '<S131>:1:86' if ((sector == 2) && (quadrant == 1)) */
  if ((localDW->sector == 2) && (quadrant == 1)) {
    /* '<S131>:1:88' u1 = a/(U_max); */
    localDW->a_W_on = localDW->a / U_max;

    /* '<S131>:1:89' u2 = single((-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max)); */
    u2 = (0.5774F * fabsf(localDW->Fcn1) + -rtb_Gain) / U_max;

    /* '<S131>:1:91' a_U_on = single(0.5 + u1*0.5 - u2*0.5); */
    rtb_SignPreIntegrator = (localDW->a_W_on * 0.5F + 0.5F) - u2 * 0.5F;

    /* '<S131>:1:92' a_V_on = single(0.5 + u1*0.5 + u2*0.5); */
    rtb_UdV = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S131>:1:93' a_W_on = single(0.5 - u1*0.5 - u2*0.5); */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;
  }

  /* '<S131>:1:97' if ((sector == 2) && (quadrant == 2)) */
  if ((localDW->sector == 2) && (quadrant == 2)) {
    /* '<S131>:1:99' u1 = single((-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max)); */
    localDW->a_W_on = (0.5774F * fabsf(localDW->Fcn1) + -fabsf(localDW->Fcn)) /
      U_max;

    /* '<S131>:1:100' u2 = a/(U_max); */
    u2 = localDW->a / U_max;

    /* '<S131>:1:102' a_U_on = single(0.5 + u1*0.5 - u2*0.5); */
    rtb_SignPreIntegrator = (localDW->a_W_on * 0.5F + 0.5F) - u2 * 0.5F;

    /* '<S131>:1:103' a_V_on = single(0.5 + u1*0.5 + u2*0.5); */
    rtb_UdV = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S131>:1:104' a_W_on = single(0.5 - u1*0.5 - u2*0.5); */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;
  }

  /* '<S131>:1:108' if (sector == 3) */
  if (localDW->sector == 3) {
    /* '<S131>:1:110' u1 = c/(U_max); */
    localDW->a_W_on = c / U_max;

    /* '<S131>:1:111' u2 = b/(U_max); */
    u2 = localDW->b / U_max;

    /* '<S131>:1:113' a_U_on=  single(0.5 - u1*0.5 - u2*0.5); */
    rtb_SignPreIntegrator = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S131>:1:114' a_V_on = single(0.5 + u1*0.5 + u2*0.5); */
    rtb_UdV = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S131>:1:115' a_W_on = single(0.5 - u1*0.5 + u2*0.5); */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;
  }

  /* '<S131>:1:118' if (sector == 4) */
  if (localDW->sector == 4) {
    /* '<S131>:1:120' u1 = b/(U_max); */
    localDW->a_W_on = localDW->b / U_max;

    /* '<S131>:1:121' u2 = c/(U_max); */
    u2 = c / U_max;

    /* '<S131>:1:123' a_U_on = single(0.5 - u1*0.5 - u2*0.5); */
    rtb_SignPreIntegrator = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S131>:1:124' a_V_on = single(0.5 + u1*0.5 - u2*0.5); */
    localDW->a_W_on = localDW->a_W_on * 0.5F + 0.5F;
    rtb_UdV = localDW->a_W_on - u2 * 0.5F;

    /* '<S131>:1:125' a_W_on = single(0.5 + u1*0.5 + u2*0.5); */
    localDW->a_W_on += u2 * 0.5F;
  }

  /* '<S131>:1:129' if ((sector == 5) && (quadrant == 3)) */
  if ((localDW->sector == 5) && (quadrant == 3)) {
    /* '<S131>:1:131' u1 = a/(U_max); */
    localDW->a_W_on = localDW->a / U_max;

    /* '<S131>:1:132' u2 = single((-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max)); */
    u2 = (0.5774F * fabsf(localDW->Fcn1) + -fabsf(localDW->Fcn)) / U_max;

    /* '<S131>:1:134' a_U_on = single(0.5 - u1*0.5 + u2*0.5); */
    rtb_SignPreIntegrator = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;

    /* '<S131>:1:135' a_V_on = single(0.5 - u1*0.5 - u2*0.5); */
    rtb_UdV = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S131>:1:136' a_W_on = single(0.5 + u1*0.5 + u2*0.5); */
    localDW->a_W_on = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;
  }

  /* '<S131>:1:140' if ((sector == 5) && (quadrant == 4)) */
  if ((localDW->sector == 5) && (quadrant == 4)) {
    /* '<S131>:1:142' u1 = single((-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max)); */
    localDW->a_W_on = (0.5774F * fabsf(localDW->Fcn1) + -fabsf(localDW->Fcn)) /
      U_max;

    /* '<S131>:1:143' u2 =  a/(U_max); */
    u2 = localDW->a / U_max;

    /* '<S131>:1:145' a_U_on = single(0.5 - u1*0.5 + u2*0.5); */
    rtb_SignPreIntegrator = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;

    /* '<S131>:1:146' a_V_on = single(0.5 - u1*0.5 - u2*0.5); */
    rtb_UdV = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S131>:1:147' a_W_on = single(0.5 + u1*0.5 + u2*0.5); */
    localDW->a_W_on = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;
  }

  /* '<S131>:1:151' if (sector == 6) */
  if (localDW->sector == 6) {
    /* '<S131>:1:153' u1 = c/(U_max); */
    localDW->a_W_on = c / U_max;

    /* '<S131>:1:154' u2 = b/(U_max); */
    u2 = localDW->b / U_max;

    /* '<S131>:1:156' a_U_on = single(0.5 + u1*0.5 + u2*0.5); */
    rtb_SignPreIntegrator = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S131>:1:157' a_V_on = single(0.5 - u1*0.5 - u2*0.5); */
    rtb_UdV = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S131>:1:158' a_W_on = single(0.5 + u1*0.5 - u2*0.5); */
    localDW->a_W_on = (localDW->a_W_on * 0.5F + 0.5F) - u2 * 0.5F;
  }

  /* '<S131>:1:161' if a_U_on > single(1.0) */
  if (rtb_SignPreIntegrator > 1.0F) {
    /* '<S131>:1:162' a_U_on = single(1.0); */
    rtb_SignPreIntegrator = 1.0F;
  }

  /* '<S131>:1:164' if a_V_on > single(1.0) */
  if (rtb_UdV > 1.0F) {
    /* '<S131>:1:165' a_V_on = single(1.0); */
    rtb_UdV = 1.0F;
  }

  /* '<S131>:1:167' if a_W_on > single(1.0) */
  if (localDW->a_W_on > 1.0F) {
    /* '<S131>:1:168' a_W_on = single(1.0); */
    localDW->a_W_on = 1.0F;
  }

  /* Switch: '<S5>/Switch' incorporates:
   *  MATLAB Function: '<S122>/SpaceVectorModulation'
   *  Sum: '<S122>/Sum1'
   */
  /* '<S131>:1:171' u_a = a_U_on; */
  /* '<S131>:1:172' u_b = a_V_on; */
  /* '<S131>:1:173' u_c = a_W_on; */
  if (rtu_flg_SpaceVectorModulation > 0) {
    /* Switch: '<S122>/Switch1' incorporates:
     *  Constant: '<S122>/Constant1'
     *  Gain: '<S122>/Gain'
     */
    if (rtu_flg_deadTimeCompensation > 0) {
      /* Signum: '<S122>/Sign' incorporates:
       *  SignalConversion generated from: '<S116>/Gain3'
       */
      if (rtu_ia < 0.0F) {
        rtb_Gain = -1.0F;
      } else if (rtu_ia > 0.0F) {
        rtb_Gain = 1.0F;
      } else if (rtu_ia == 0.0F) {
        rtb_Gain = 0.0F;
      } else {
        rtb_Gain = (rtNaNF);
      }

      localDW->Gain1[0] = 0.02F * rtb_Gain;

      /* Signum: '<S122>/Sign' incorporates:
       *  Gain: '<S122>/Gain'
       *  SignalConversion generated from: '<S116>/Gain3'
       */
      if (rtu_ib < 0.0F) {
        rtb_Gain = -1.0F;
      } else if (rtu_ib > 0.0F) {
        rtb_Gain = 1.0F;
      } else if (rtu_ib == 0.0F) {
        rtb_Gain = 0.0F;
      } else {
        rtb_Gain = (rtNaNF);
      }

      localDW->Gain1[1] = 0.02F * rtb_Gain;

      /* Signum: '<S122>/Sign' incorporates:
       *  Gain: '<S122>/Gain'
       *  SignalConversion generated from: '<S116>/Gain3'
       */
      if (rtu_ic < 0.0F) {
        rtb_Gain = -1.0F;
      } else if (rtu_ic > 0.0F) {
        rtb_Gain = 1.0F;
      } else if (rtu_ic == 0.0F) {
        rtb_Gain = 0.0F;
      } else {
        rtb_Gain = (rtNaNF);
      }

      localDW->Gain1[2] = 0.02F * rtb_Gain;
    } else {
      localDW->Gain1[0] = 0.0F;
      localDW->Gain1[1] = 0.0F;
      localDW->Gain1[2] = 0.0F;
    }

    /* End of Switch: '<S122>/Switch1' */
    localDW->TmpSignalConversionAtGain3I[0] = rtb_SignPreIntegrator +
      localDW->Gain1[0];
    localDW->TmpSignalConversionAtGain3I[1] = rtb_UdV + localDW->Gain1[1];
    localDW->TmpSignalConversionAtGain3I[2] = localDW->a_W_on + localDW->Gain1[2];
  } else {
    /* Gain: '<S121>/Gain' */
    rtb_SignPreIntegrator = 0.5F * rtu_U_IC;

    /* Switch: '<S121>/Switch2' incorporates:
     *  Constant: '<S121>/Constant5'
     *  Gain: '<S123>/Gain'
     *  Gain: '<S123>/Gain1'
     *  Product: '<S123>/Product'
     *  Product: '<S123>/Product1'
     *  SignalConversion generated from: '<S116>/Gain3'
     */
    if (rtu_flg_deadTimeCompensation > 0) {
      /* Signum: '<S123>/Sign' incorporates:
       *  SignalConversion generated from: '<S116>/Gain3'
       */
      if (rtu_ia < 0.0F) {
        rtb_Gain = -1.0F;
      } else if (rtu_ia > 0.0F) {
        rtb_Gain = 1.0F;
      } else if (rtu_ia == 0.0F) {
        rtb_Gain = 0.0F;
      } else {
        rtb_Gain = (rtNaNF);
      }

      localDW->Switch2[0] = 1.0E-6F * rtu_ia * 20000.0F * rtb_Gain *
        *rty_ud_soll;

      /* Signum: '<S123>/Sign' incorporates:
       *  Gain: '<S123>/Gain'
       *  Gain: '<S123>/Gain1'
       *  Product: '<S123>/Product'
       *  Product: '<S123>/Product1'
       *  SignalConversion generated from: '<S116>/Gain3'
       */
      if (rtu_ib < 0.0F) {
        rtb_Gain = -1.0F;
      } else if (rtu_ib > 0.0F) {
        rtb_Gain = 1.0F;
      } else if (rtu_ib == 0.0F) {
        rtb_Gain = 0.0F;
      } else {
        rtb_Gain = (rtNaNF);
      }

      localDW->Switch2[1] = 1.0E-6F * rtu_ib * 20000.0F * rtb_Gain *
        *rty_ud_soll;

      /* Signum: '<S123>/Sign' incorporates:
       *  Gain: '<S123>/Gain'
       *  Gain: '<S123>/Gain1'
       *  Product: '<S123>/Product'
       *  Product: '<S123>/Product1'
       *  SignalConversion generated from: '<S116>/Gain3'
       */
      if (rtu_ic < 0.0F) {
        rtb_Gain = -1.0F;
      } else if (rtu_ic > 0.0F) {
        rtb_Gain = 1.0F;
      } else if (rtu_ic == 0.0F) {
        rtb_Gain = 0.0F;
      } else {
        rtb_Gain = (rtNaNF);
      }

      localDW->Switch2[2] = 1.0E-6F * rtu_ic * 20000.0F * rtb_Gain *
        *rty_ud_soll;
    } else {
      localDW->Switch2[0] = 0.0;
      localDW->Switch2[1] = 0.0;
      localDW->Switch2[2] = 0.0;
    }

    /* End of Switch: '<S121>/Switch2' */

    /* Product: '<S121>/Divide' incorporates:
     *  Constant: '<S121>/Constant1'
     *  Gain: '<S121>/Gain1'
     *  Gain: '<S125>/Gain3'
     *  Sum: '<S121>/Sum'
     *  Sum: '<S121>/Sum2'
     *  Switch: '<S126>/Switch'
     */
    for (quadrant = 0; quadrant < 3; quadrant++) {
      localDW->TmpSignalConversionAtGain3I[quadrant] = (real32_T)
        ((((rtConstP.Gain3_Gain[quadrant + 3] * localDW->Fcn1_o +
            rtConstP.Gain3_Gain[quadrant] * localDW->Fcn_d) +
           rtConstP.Gain3_Gain[quadrant + 6] * 0.0F) + localDW->Switch2[quadrant])
         / rtb_SignPreIntegrator) * 0.5F + 0.5F;
    }

    /* End of Product: '<S121>/Divide' */
  }

  /* End of Switch: '<S5>/Switch' */

  /* Saturate: '<S5>/Saturation' */
  if (localDW->TmpSignalConversionAtGain3I[0] > 1.0F) {
    rty_ua[0] = 1.0F;
  } else if (localDW->TmpSignalConversionAtGain3I[0] < 0.0F) {
    rty_ua[0] = 0.0F;
  } else {
    rty_ua[0] = localDW->TmpSignalConversionAtGain3I[0];
  }

  if (localDW->TmpSignalConversionAtGain3I[1] > 1.0F) {
    rty_ua[1] = 1.0F;
  } else if (localDW->TmpSignalConversionAtGain3I[1] < 0.0F) {
    rty_ua[1] = 0.0F;
  } else {
    rty_ua[1] = localDW->TmpSignalConversionAtGain3I[1];
  }

  if (localDW->TmpSignalConversionAtGain3I[2] > 1.0F) {
    rty_ua[2] = 1.0F;
  } else if (localDW->TmpSignalConversionAtGain3I[2] < 0.0F) {
    rty_ua[2] = 0.0F;
  } else {
    rty_ua[2] = localDW->TmpSignalConversionAtGain3I[2];
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* SignalConversion generated from: '<S2>/ub' */
  *rty_ub = rty_ua[1];

  /* SignalConversion generated from: '<S2>/uc' */
  *rty_uc = rty_ua[2];

  /* Switch: '<S89>/Switch' incorporates:
   *  Gain: '<S8>/Gain1'
   *  RelationalOperator: '<S89>/u_GTE_up'
   *  RelationalOperator: '<S89>/u_GT_lo'
   *  Switch: '<S89>/Switch1'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  if (rtb_Sum_dd >= localDW->UnitDelay_DSTATE) {
    rtb_SignPreIntegrator = localDW->UnitDelay_DSTATE;
  } else if (rtb_Sum_dd > -localDW->UnitDelay_DSTATE) {
    /* Switch: '<S89>/Switch1' */
    rtb_SignPreIntegrator = rtb_Sum_dd;
  } else {
    rtb_SignPreIntegrator = -localDW->UnitDelay_DSTATE;
  }

  /* End of Switch: '<S89>/Switch' */

  /* Sum: '<S89>/Diff' */
  rtb_SignPreIntegrator = rtb_Sum_dd - rtb_SignPreIntegrator;

  /* Product: '<S93>/IProd Out' */
  rtb_Sum *= rtu_Ki_Iq;

  /* SignalConversion generated from: '<S2>/Id_ist' */
  *rty_Id_ist = rty_Iq_ist[0];

  /* Update for DiscreteIntegrator: '<S43>/Integrator' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  DiscreteIntegrator: '<S96>/Integrator'
   *  Product: '<S40>/IProd Out'
   */
  localDW->Integrator_SYSTEM_ENABLE = 0U;
  localDW->Integrator_DSTATE = Integrator;
  if (rtu_flg_Reset > 0) {
    localDW->Integrator_PrevResetState = 1;
    localDW->Integrator_PrevResetState_p = 1;
  } else {
    if (rtu_flg_Reset < 0) {
      localDW->Integrator_PrevResetState = -1;
    } else {
      localDW->Integrator_PrevResetState = 0;
    }

    if (rtu_flg_Reset < 0) {
      localDW->Integrator_PrevResetState_p = -1;
    } else {
      localDW->Integrator_PrevResetState_p = 0;
    }
  }

  localDW->Integrator_PREV_U = rtb_error * rtu_Ki_Id;

  /* End of Update for DiscreteIntegrator: '<S43>/Integrator' */

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  localDW->UnitDelay_DSTATE = rtb_Switch1_h;

  /* Update for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE_b = 0U;
  localDW->Integrator_DSTATE_b = rtb_Gain1_lc;

  /* Signum: '<S86>/SignPreSat' */
  if (rtb_SignPreIntegrator < 0.0F) {
    rtb_error = -1.0F;
  } else if (rtb_SignPreIntegrator > 0.0F) {
    rtb_error = 1.0F;
  } else if (rtb_SignPreIntegrator == 0.0F) {
    rtb_error = 0.0F;
  } else {
    rtb_error = (rtNaNF);
  }

  /* End of Signum: '<S86>/SignPreSat' */

  /* Signum: '<S86>/SignPreIntegrator' */
  if (rtb_Sum < 0.0F) {
    Integrator = -1.0F;
  } else if (rtb_Sum > 0.0F) {
    Integrator = 1.0F;
  } else if (rtb_Sum == 0.0F) {
    Integrator = 0.0F;
  } else {
    Integrator = (rtNaNF);
  }

  /* End of Signum: '<S86>/SignPreIntegrator' */

  /* Switch: '<S86>/Switch' incorporates:
   *  DataTypeConversion: '<S86>/DataTypeConv1'
   *  DataTypeConversion: '<S86>/DataTypeConv2'
   *  Gain: '<S86>/ZeroGain'
   *  Logic: '<S86>/AND3'
   *  RelationalOperator: '<S86>/Equal1'
   *  RelationalOperator: '<S86>/NotEqual'
   */
  if ((0.0F * rtb_Sum_dd != rtb_SignPreIntegrator) && ((int8_T)rtb_error ==
       (int8_T)Integrator)) {
    /* Update for DiscreteIntegrator: '<S96>/Integrator' incorporates:
     *  Constant: '<S86>/Constant1'
     */
    localDW->Integrator_PREV_U_e = 0.0F;
  } else {
    /* Update for DiscreteIntegrator: '<S96>/Integrator' */
    localDW->Integrator_PREV_U_e = rtb_Sum;
  }

  /* End of Switch: '<S86>/Switch' */
}

/* System initialize for function-call system: '<S1>/SpeedController' */
static void SpeedController_Init(DW_SpeedController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S176>/Integrator' */
  localDW->Integrator_PrevResetState = 0;
  localDW->Integrator_PREV_U = 0.0F;
}

/* Enable for function-call system: '<S1>/SpeedController' */
static void SpeedController_Enable(DW_SpeedController *localDW)
{
  localDW->SpeedController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S176>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 1U;
}

/* Output and update for function-call system: '<S1>/SpeedController' */
static void SpeedController(RT_MODEL * const rtM, real32_T rtu_id_ref, real32_T
  rtu_iq_ref, real32_T rtu_n_ref, real32_T rtu_n_ist, int8_T
  rtu_flg_SpeedControl, int8_T rtu_flg_FieldWeakening, real32_T rtu_Kp_Speed,
  real32_T rtu_Ki_Speed, real32_T rtu_I_max, real32_T rtu_U_DC, int8_T rtu_RESET,
  real32_T *rty_id_soll, real32_T *rty_iq_soll, DW_SpeedController *localDW)
{
  real32_T Integrator;
  real32_T a;
  real32_T a_fw;
  real32_T a_tmp;
  real32_T b;
  real32_T b_fw;
  real32_T rtb_IProdOut_a;
  real32_T rtb_Sum;
  real32_T u_max_dq;
  real32_T u_max_dq_tmp;
  uint32_T SpeedController_ELAPS_T;
  if (localDW->SpeedController_RESET_ELAPS_T) {
    SpeedController_ELAPS_T = 0U;
  } else {
    SpeedController_ELAPS_T = rtM->Timing.clockTick0 -
      localDW->SpeedController_PREV_T;
  }

  localDW->SpeedController_PREV_T = rtM->Timing.clockTick0;
  localDW->SpeedController_RESET_ELAPS_T = false;

  /* DiscreteIntegrator: '<S176>/Integrator' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   */
  if (localDW->Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S176>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else if ((rtu_RESET != 0) || (localDW->Integrator_PrevResetState != 0)) {
    localDW->Integrator_DSTATE = 0.0F;

    /* DiscreteIntegrator: '<S176>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S176>/Integrator' */
    Integrator = 2.5E-5F * (real32_T)SpeedController_ELAPS_T
      * localDW->Integrator_PREV_U + localDW->Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S176>/Integrator' */

  /* Sum: '<S138>/Sum' */
  rtb_IProdOut_a = rtu_n_ref - rtu_n_ist;

  /* Sum: '<S186>/Sum' incorporates:
   *  Product: '<S181>/PProd Out'
   */
  rtb_Sum = rtb_IProdOut_a * rtu_Kp_Speed + Integrator;

  /* MATLAB Function: '<S139>/MATLAB Function' incorporates:
   *  Constant: '<S139>/Constant'
   *  Constant: '<S139>/Constant1'
   *  Constant: '<S139>/Constant2'
   *  Constant: '<S139>/Constant3'
   *  Constant: '<S139>/Constant5'
   */
  /* Maximum voltage vector */
  /* MATLAB Function 'uz_codegen/SpeedController/speed controller/PI_Speed_Control/Field Weakening/MATLAB Function': '<S141>:1' */
  /* '<S141>:1:4' u_max_dq = single(0.95* U_IC/sqrt(single(3))); */
  u_max_dq = 0.95F * rtu_U_DC / 1.73205078F;

  /* Calculation of n_cut */
  /* '<S141>:1:7' a = single(I_max^2 * Lq^2 + psi_pm^2); */
  a_tmp = rtu_I_max * rtu_I_max;
  a = a_tmp * 2.56E-10F + 2.30400019E-5F;

  /* '<S141>:1:8' b = single(2*R*psi_pm*I_max); */
  b = 0.000384F * rtu_I_max;

  /* '<S141>:1:9' c = single((I_max^2 * R^2)-u_max_dq^2); */
  /* '<S141>:1:11' w_cut = single((-b + sqrt(b^2 - 4*a*c))/(2*a)); */
  a = (sqrtf(b * b - (a_tmp * 0.0016F - u_max_dq * u_max_dq) * (4.0F * a)) + -b)
    / (2.0F * a);

  /* Current speed */
  /* '<S141>:1:14' w_el = single(n_ist*2*pi*zp/60); */
  b = rtu_n_ist * 2.0F * 3.14159274F * 21.0F / 60.0F;

  /* Check if w_cut is valid */
  /* '<S141>:1:17' if w_cut > 0 && isreal(single(w_cut)) */
  if (a > 0.0F) {
    /* Calcultation of Id_ref */
    /* '<S141>:1:19' if w_el > w_cut */
    if (b > a) {
      /* '<S141>:1:20' id_ref = single(psi_pm/Ld * (w_cut/w_el -1)); */
      a = (a / b - 1.0F) * 300.0F;

      /* '<S141>:1:21' if id_ref < -I_max */
      if (a < -rtu_I_max) {
        /* '<S141>:1:22' id_ref = -I_max; */
        a = -rtu_I_max;
      }
    } else {
      /* '<S141>:1:24' else */
      /* '<S141>:1:25' id_ref = single(0.0); */
      a = 0.0F;
    }
  } else {
    /* '<S141>:1:27' else */
    /* '<S141>:1:28' id_ref = single(0.0); */
    a = 0.0F;
  }

  /* '<S141>:1:31' id_soll = single(id_ref); */
  /* '<S141>:1:33' if id_soll < single(0.0) */
  if (a < 0.0F) {
    /* '<S141>:1:34' a_fw = single(R^2 + w_el^2 * Lq^2); */
    a_fw = b * b * 2.56E-10F + 0.0016F;

    /* '<S141>:1:35' b_fw = single(2*R*w_el*psi_pm); */
    b_fw = 0.08F * b * 0.0048F;

    /* '<S141>:1:36' c_fw = single(id_soll^2 * R^2 -u_max_dq^2 + w_el^2 * (psi_pm^2 + Ld^2 * id_soll^2 + 2*psi_pm*Ld*id_soll)); */
    /* '<S141>:1:38' iq_max = single((-b_fw + sqrt(b_fw^2 - 4*a_fw*c_fw))/(2*a_fw)); */
    u_max_dq_tmp = a * a;
    u_max_dq = (sqrtf(b_fw * b_fw - (((u_max_dq_tmp * 2.56E-10F + 2.30400019E-5F)
      + 1.53600013E-7F * a) * (b * b) + (u_max_dq_tmp * 0.0016F - u_max_dq *
      u_max_dq)) * (4.0F * a_fw)) + -b_fw) / (2.0F * a_fw);

    /* '<S141>:1:39' if iq_max > single(sqrt(I_max^2 - id_soll^2)) */
    b = sqrtf(a_tmp - u_max_dq_tmp);
    if (u_max_dq > b) {
      /* '<S141>:1:40' iq_max =  single(sqrt(I_max^2 - id_soll^2)); */
      u_max_dq = b;
    }
  } else {
    /* '<S141>:1:42' else */
    /* '<S141>:1:43' iq_max = I_max; */
    u_max_dq = rtu_I_max;
  }

  /* Switch: '<S138>/Switch1' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   *  MATLAB Function: '<S139>/MATLAB Function'
   */
  if (rtu_flg_FieldWeakening > 0) {
    b = u_max_dq;
  } else {
    b = rtu_I_max;
  }

  /* End of Switch: '<S138>/Switch1' */

  /* Switch: '<S169>/Switch' incorporates:
   *  Gain: '<S138>/Gain'
   *  RelationalOperator: '<S169>/u_GTE_up'
   *  RelationalOperator: '<S169>/u_GT_lo'
   *  Switch: '<S169>/Switch1'
   */
  if (rtb_Sum >= b) {
    u_max_dq = b;
  } else if (rtb_Sum > -b) {
    /* Switch: '<S169>/Switch1' */
    u_max_dq = rtb_Sum;
  } else {
    u_max_dq = -b;
  }

  /* End of Switch: '<S169>/Switch' */

  /* Sum: '<S169>/Diff' */
  u_max_dq = rtb_Sum - u_max_dq;

  /* Product: '<S173>/IProd Out' */
  rtb_IProdOut_a *= rtu_Ki_Speed;

  /* Switch: '<S137>/Switch1' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion2'
   *  Switch: '<S137>/Switch'
   */
  if (rtu_flg_SpeedControl > 0) {
    /* Switch: '<S138>/Switch2' incorporates:
     *  Constant: '<S138>/Constant1'
     *  Constant: '<S138>/Constant2'
     *  DataTypeConversion: '<S3>/Data Type Conversion'
     *  Gain: '<S138>/Gain'
     *  RelationalOperator: '<S184>/LowerRelop1'
     *  RelationalOperator: '<S184>/UpperRelop'
     *  Switch: '<S138>/Switch3'
     *  Switch: '<S184>/Switch'
     *  Switch: '<S184>/Switch2'
     */
    if (rtu_RESET > 0) {
      *rty_iq_soll = 0.0F;
      *rty_id_soll = 0.0F;
    } else {
      if (rtb_Sum > b) {
        /* Switch: '<S184>/Switch2' */
        *rty_iq_soll = b;
      } else if (rtb_Sum < -b) {
        /* Switch: '<S184>/Switch' incorporates:
         *  Gain: '<S138>/Gain'
         *  Switch: '<S184>/Switch2'
         */
        *rty_iq_soll = -b;
      } else {
        /* Switch: '<S184>/Switch2' incorporates:
         *  Switch: '<S184>/Switch'
         */
        *rty_iq_soll = rtb_Sum;
      }

      /* Switch: '<S138>/Switch' incorporates:
       *  Constant: '<S138>/Constant'
       *  DataTypeConversion: '<S3>/Data Type Conversion1'
       *  Gain: '<S138>/Gain'
       *  MATLAB Function: '<S139>/MATLAB Function'
       *  RelationalOperator: '<S184>/UpperRelop'
       *  Switch: '<S184>/Switch'
       *  Switch: '<S184>/Switch2'
       */
      if (rtu_flg_FieldWeakening > 0) {
        *rty_id_soll = a;
      } else {
        *rty_id_soll = 0.0F;
      }

      /* End of Switch: '<S138>/Switch' */
    }

    /* End of Switch: '<S138>/Switch2' */
  } else {
    *rty_iq_soll = rtu_iq_ref;
    *rty_id_soll = rtu_id_ref;
  }

  /* End of Switch: '<S137>/Switch1' */

  /* Update for DiscreteIntegrator: '<S176>/Integrator' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   */
  localDW->Integrator_SYSTEM_ENABLE = 0U;
  localDW->Integrator_DSTATE = Integrator;
  if (rtu_RESET > 0) {
    localDW->Integrator_PrevResetState = 1;
  } else if (rtu_RESET < 0) {
    localDW->Integrator_PrevResetState = -1;
  } else {
    localDW->Integrator_PrevResetState = 0;
  }

  /* Signum: '<S166>/SignPreSat' */
  if (u_max_dq < 0.0F) {
    Integrator = -1.0F;
  } else if (u_max_dq > 0.0F) {
    Integrator = 1.0F;
  } else if (u_max_dq == 0.0F) {
    Integrator = 0.0F;
  } else {
    Integrator = (rtNaNF);
  }

  /* End of Signum: '<S166>/SignPreSat' */

  /* Signum: '<S166>/SignPreIntegrator' */
  if (rtb_IProdOut_a < 0.0F) {
    a = -1.0F;
  } else if (rtb_IProdOut_a > 0.0F) {
    a = 1.0F;
  } else if (rtb_IProdOut_a == 0.0F) {
    a = 0.0F;
  } else {
    a = (rtNaNF);
  }

  /* End of Signum: '<S166>/SignPreIntegrator' */

  /* Switch: '<S166>/Switch' incorporates:
   *  DataTypeConversion: '<S166>/DataTypeConv1'
   *  DataTypeConversion: '<S166>/DataTypeConv2'
   *  Gain: '<S166>/ZeroGain'
   *  Logic: '<S166>/AND3'
   *  RelationalOperator: '<S166>/Equal1'
   *  RelationalOperator: '<S166>/NotEqual'
   */
  if ((0.0F * rtb_Sum != u_max_dq) && ((int8_T)Integrator == (int8_T)a)) {
    /* Update for DiscreteIntegrator: '<S176>/Integrator' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    localDW->Integrator_PREV_U = 0.0F;
  } else {
    /* Update for DiscreteIntegrator: '<S176>/Integrator' */
    localDW->Integrator_PREV_U = rtb_IProdOut_a;
  }

  /* End of Switch: '<S166>/Switch' */
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Chart: '<Root>/uz_codegen' incorporates:
   *  Inport: '<Root>/RESET'
   *  Inport: '<Root>/START'
   */
  /* Gateway: uz_codegen */
  /* During: uz_codegen */
  if (rtDW->is_active_c3_uz_codegen0 == 0U) {
    /* Entry: uz_codegen */
    rtDW->is_active_c3_uz_codegen0 = 1U;

    /* Entry Internal: uz_codegen */
    /* Transition: '<S1>:2' */
    rtDW->is_c3_uz_codegen0 = IN_Start;

    /* Outport: '<Root>/activeState' */
    /* Entry 'Start': '<S1>:1' */
    /* '<S1>:1:3' activeState = 1; */
    rtY->activeState = 1.0F;

    /* Outport: '<Root>/Ua_DutyCycle' */
    /* '<S1>:1:4' Ua_DutyCycle = 0; */
    rtY->Ua_DutyCycle = 0.0F;

    /* Outport: '<Root>/Ub_DutyCycle' */
    /* '<S1>:1:5' Ub_DutyCycle = 0; */
    rtY->Ub_DutyCycle = 0.0F;

    /* Outport: '<Root>/Uc_DutyCycle' */
    /* '<S1>:1:6' Uc_DutyCycle = 0; */
    rtY->Uc_DutyCycle = 0.0F;
  } else {
    switch (rtDW->is_c3_uz_codegen0) {
     case IN_InProcess:
      /* During 'InProcess': '<S1>:3' */
      /* '<S1>:18:1' sf_internal_predicateOutput = RESET==1; */
      if (rtU->RESET == 1) {
        /* Transition: '<S1>:18' */
        rtDW->is_c3_uz_codegen0 = IN_Reset;

        /* Entry 'Reset': '<S1>:119' */
      } else {
        /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
        /* Outport: '<Root>/iq_soll' incorporates:
         *  Inport: '<Root>/I_max'
         *  Inport: '<Root>/Ki_Speed'
         *  Inport: '<Root>/Kp_Speed'
         *  Inport: '<Root>/U_IC'
         *  Inport: '<Root>/flg_FieldWeakening'
         *  Inport: '<Root>/flg_SpeedControl'
         *  Inport: '<Root>/id_ref'
         *  Inport: '<Root>/iq_ref'
         *  Inport: '<Root>/n_ist'
         *  Inport: '<Root>/n_ref'
         *  Outport: '<Root>/id_soll'
         */
        /* '<S1>:3:5' [id_soll, iq_soll] = SpeedController(id_ref, iq_ref, n_ref, n_ist, flg_SpeedControl, flg_FieldWeakening, Kp_Speed, Ki_Speed, I_max, U_IC, RESET) */
        /* Simulink Function 'SpeedController': '<S1>:133' */
        SpeedController(rtM, rtU->id_ref, rtU->iq_ref, rtU->n_ref, rtU->n_ist,
                        rtU->flg_SpeedControl, rtU->flg_FieldWeakening,
                        rtU->Kp_Speed, rtU->Ki_Speed, rtU->I_max, rtU->U_IC,
                        rtU->RESET, &rtY->id_soll, &rtY->iq_soll,
                        &rtDW->SpeedController_j);

        /* End of Outputs for SubSystem: '<S1>/SpeedController' */

        /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
        /* Outport: '<Root>/uq' incorporates:
         *  Inport: '<Root>/Ki_Id'
         *  Inport: '<Root>/Ki_Iq'
         *  Inport: '<Root>/Kp_Id'
         *  Inport: '<Root>/Kp_Iq'
         *  Inport: '<Root>/U_IC'
         *  Inport: '<Root>/flgLimitUdUq'
         *  Inport: '<Root>/flg_PreCntr'
         *  Inport: '<Root>/flg_SpaceVectorModulation'
         *  Inport: '<Root>/flg_deadTimeCompensation'
         *  Inport: '<Root>/flg_theta_el_compensation'
         *  Inport: '<Root>/ia'
         *  Inport: '<Root>/ib'
         *  Inport: '<Root>/ic'
         *  Inport: '<Root>/theta_el'
         *  Inport: '<Root>/w_el'
         *  Outport: '<Root>/Ub_DutyCycle'
         *  Outport: '<Root>/Uc_DutyCycle'
         *  Outport: '<Root>/id_ist'
         *  Outport: '<Root>/id_soll'
         *  Outport: '<Root>/iq_soll'
         *  Outport: '<Root>/ud'
         */
        /* '<S1>:3:6' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq, Kp_Iq, Ki_Iq, Kp_Id, Ki_Id, flg_SpaceVectorModulation, RESET, flg_deadTimeCompensation, flg_theta_el_compensation) */
        /* Simulink Function 'CurrentController': '<S1>:72' */
        CurrentController(rtM, rtU->ia, rtU->ib, rtU->ic, rtU->w_el,
                          rtU->flg_PreCntr, rtU->theta_el, rtU->U_IC,
                          rtY->id_soll, rtY->iq_soll, rtU->flgLimitUdUq,
                          rtU->Kp_Iq, rtU->Ki_Iq, rtU->Kp_Id, rtU->Ki_Id,
                          rtU->flg_SpaceVectorModulation, rtU->RESET,
                          rtU->flg_deadTimeCompensation,
                          rtU->flg_theta_el_compensation, rtDW->Saturation,
                          &rtY->Ub_DutyCycle, &rtY->Uc_DutyCycle, rtDW->Switch_m,
                          &rtY->id_ist, &rtY->ud, &rtY->uq,
                          &rtConstB.CurrentController_o,
                          &rtDW->CurrentController_o);

        /* End of Outputs for SubSystem: '<S1>/CurrentController' */

        /* Outport: '<Root>/Ua_DutyCycle' */
        rtY->Ua_DutyCycle = rtDW->Saturation[0];

        /* Outport: '<Root>/iq_ist' */
        rtY->iq_ist = rtDW->Switch_m[1];
      }
      break;

     case IN_Reset:
      /* During 'Reset': '<S1>:119' */
      /* '<S1>:121:1' sf_internal_predicateOutput = RESET == 0; */
      if (rtU->RESET == 0) {
        /* Transition: '<S1>:121' */
        rtDW->is_c3_uz_codegen0 = IN_Start;

        /* Outport: '<Root>/activeState' */
        /* Entry 'Start': '<S1>:1' */
        /* '<S1>:1:3' activeState = 1; */
        rtY->activeState = 1.0F;

        /* Outport: '<Root>/Ua_DutyCycle' */
        /* '<S1>:1:4' Ua_DutyCycle = 0; */
        rtY->Ua_DutyCycle = 0.0F;

        /* Outport: '<Root>/Ub_DutyCycle' */
        /* '<S1>:1:5' Ub_DutyCycle = 0; */
        rtY->Ub_DutyCycle = 0.0F;

        /* Outport: '<Root>/Uc_DutyCycle' */
        /* '<S1>:1:6' Uc_DutyCycle = 0; */
        rtY->Uc_DutyCycle = 0.0F;
      } else {
        /* Outport: '<Root>/activeState' */
        /* '<S1>:119:3' activeState = 3; */
        rtY->activeState = 3.0F;

        /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
        /* Outport: '<Root>/iq_soll' incorporates:
         *  Inport: '<Root>/I_max'
         *  Inport: '<Root>/Ki_Speed'
         *  Inport: '<Root>/Kp_Speed'
         *  Inport: '<Root>/U_IC'
         *  Inport: '<Root>/flg_FieldWeakening'
         *  Inport: '<Root>/flg_SpeedControl'
         *  Inport: '<Root>/id_ref'
         *  Inport: '<Root>/iq_ref'
         *  Inport: '<Root>/n_ist'
         *  Inport: '<Root>/n_ref'
         *  Outport: '<Root>/id_soll'
         */
        /* '<S1>:119:4' [id_soll, iq_soll] = SpeedController(id_ref, iq_ref, n_ref, n_ist, flg_SpeedControl, flg_FieldWeakening, Kp_Speed, Ki_Speed, I_max, U_IC, RESET) */
        /* Simulink Function 'SpeedController': '<S1>:133' */
        SpeedController(rtM, rtU->id_ref, rtU->iq_ref, rtU->n_ref, rtU->n_ist,
                        rtU->flg_SpeedControl, rtU->flg_FieldWeakening,
                        rtU->Kp_Speed, rtU->Ki_Speed, rtU->I_max, rtU->U_IC,
                        rtU->RESET, &rtY->id_soll, &rtY->iq_soll,
                        &rtDW->SpeedController_j);

        /* End of Outputs for SubSystem: '<S1>/SpeedController' */

        /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
        /* Outport: '<Root>/uq' incorporates:
         *  Inport: '<Root>/Ki_Id'
         *  Inport: '<Root>/Ki_Iq'
         *  Inport: '<Root>/Kp_Id'
         *  Inport: '<Root>/Kp_Iq'
         *  Inport: '<Root>/U_IC'
         *  Inport: '<Root>/flgLimitUdUq'
         *  Inport: '<Root>/flg_PreCntr'
         *  Inport: '<Root>/flg_SpaceVectorModulation'
         *  Inport: '<Root>/flg_deadTimeCompensation'
         *  Inport: '<Root>/flg_theta_el_compensation'
         *  Inport: '<Root>/ia'
         *  Inport: '<Root>/ib'
         *  Inport: '<Root>/ic'
         *  Inport: '<Root>/id_ref'
         *  Inport: '<Root>/iq_ref'
         *  Inport: '<Root>/theta_el'
         *  Inport: '<Root>/w_el'
         *  Outport: '<Root>/id_ist'
         *  Outport: '<Root>/ud'
         */
        /* '<S1>:119:5' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_ref,iq_ref,flgLimitUdUq, Kp_Iq, Ki_Iq, Kp_Id, Ki_Id, flg_SpaceVectorModulation, RESET, flg_deadTimeCompensation, flg_theta_el_compensation) */
        /* Simulink Function 'CurrentController': '<S1>:72' */
        CurrentController(rtM, rtU->ia, rtU->ib, rtU->ic, rtU->w_el,
                          rtU->flg_PreCntr, rtU->theta_el, rtU->U_IC,
                          rtU->id_ref, rtU->iq_ref, rtU->flgLimitUdUq,
                          rtU->Kp_Iq, rtU->Ki_Iq, rtU->Kp_Id, rtU->Ki_Id,
                          rtU->flg_SpaceVectorModulation, rtU->RESET,
                          rtU->flg_deadTimeCompensation,
                          rtU->flg_theta_el_compensation, rtDW->Saturation,
                          &rtDW->OutportBufferForub, &rtDW->OutportBufferForuc,
                          rtDW->Switch_m, &rtY->id_ist, &rtY->ud, &rtY->uq,
                          &rtConstB.CurrentController_o,
                          &rtDW->CurrentController_o);

        /* End of Outputs for SubSystem: '<S1>/CurrentController' */

        /* Outport: '<Root>/iq_ist' */
        rtY->iq_ist = rtDW->Switch_m[1];

        /* Outport: '<Root>/Ua_DutyCycle' */
        /* '<S1>:119:6' Ua_DutyCycle = 0; */
        rtY->Ua_DutyCycle = 0.0F;

        /* Outport: '<Root>/Ub_DutyCycle' */
        /* '<S1>:119:7' Ub_DutyCycle = 0; */
        rtY->Ub_DutyCycle = 0.0F;

        /* Outport: '<Root>/Uc_DutyCycle' */
        /* '<S1>:119:8' Uc_DutyCycle = 0; */
        rtY->Uc_DutyCycle = 0.0F;
      }
      break;

     default:
      /* During 'Start': '<S1>:1' */
      /* '<S1>:17:1' sf_internal_predicateOutput = START==1 & RESET==0; */
      if ((rtU->START == 1) && (rtU->RESET == 0)) {
        /* Transition: '<S1>:17' */
        rtDW->is_c3_uz_codegen0 = IN_InProcess;

        /* Outport: '<Root>/activeState' */
        /* Entry 'InProcess': '<S1>:3' */
        /* '<S1>:3:3' activeState = 2; */
        rtY->activeState = 2.0F;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/uz_codegen' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 2.5E-5, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rtM->Timing.clockTick0++;
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtY *rtY = (ExtY *) rtM->outputs;
  ExtU *rtU = (ExtU *) rtM->inputs;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));
  rtDW->is_active_c3_uz_codegen0 = 0U;
  rtDW->is_c3_uz_codegen0 = IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Outport: '<Root>/Ua_DutyCycle' */
  rtY->Ua_DutyCycle = 0.0F;

  /* SystemInitialize for Outport: '<Root>/activeState' */
  rtY->activeState = 0.0F;

  /* SystemInitialize for Outport: '<Root>/Uc_DutyCycle' */
  rtY->Uc_DutyCycle = 0.0F;

  /* SystemInitialize for Outport: '<Root>/Ub_DutyCycle' */
  rtY->Ub_DutyCycle = 0.0F;

  /* SystemInitialize for Outport: '<Root>/iq_ist' */
  rtY->iq_ist = 0.0F;

  /* SystemInitialize for Outport: '<Root>/id_ist' */
  rtY->id_ist = 0.0F;

  /* SystemInitialize for Outport: '<Root>/uq' */
  rtY->uq = 0.0F;

  /* SystemInitialize for Outport: '<Root>/ud' */
  rtY->ud = 0.0F;

  /* SystemInitialize for Outport: '<Root>/iq_soll' */
  rtY->iq_soll = 0.0F;

  /* SystemInitialize for Outport: '<Root>/id_soll' */
  rtY->id_soll = 0.0F;

  /* SystemInitialize for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Init(&rtDW->CurrentController_o);

  /* SystemInitialize for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  SpeedController_Init(&rtDW->SpeedController_j);

  /* Enable for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Enable(&rtDW->CurrentController_o);

  /* Enable for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  SpeedController_Enable(&rtDW->SpeedController_j);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
