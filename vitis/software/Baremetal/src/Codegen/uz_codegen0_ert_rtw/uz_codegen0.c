/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.33
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 14 10:03:41 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (8), Warnings (2), Errors (2)
 */

#include "uz_codegen0.h"

/* Named constants for Chart: '<Root>/uz_codegen' */
#define IN_InProcess                   ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Reset                       ((uint8_T)2U)
#define IN_Start                       ((uint8_T)3U)
#define NumBitsPerChar                 8U

static void Subsystempi2delay(uint8_T rtu_Enable, real_T rtu_dq, real_T rtu_dq_a,
  real_T rtu_wt, real_T *rty_alpha_beta, real_T *rty_alpha_beta_d);
static void Subsystem1(uint8_T rtu_Enable, real_T rtu_dq, real_T rtu_dq_g,
  real_T rtu_wt, real_T *rty_alpha_beta, real_T *rty_alpha_beta_k);
static void CurrentController_Init(DW_CurrentController *localDW);
static void CurrentController_Enable(DW_CurrentController *localDW);
static void CurrentController(RT_MODEL * const rtM, real_T rtu_ia, real_T rtu_ib,
  real_T rtu_ic, real_T rtu_w_el, real_T rtu_flg_PreCtrl, real_T rtu_theta_el,
  real_T rtu_U_IC, real_T rtu_id_ref, real_T rtu_iq_ref, real_T
  rtu_flg_LimitUdUq, real_T rtu_Kp_Iq, real_T rtu_Ki_Iq, real_T rtu_Kp_Id,
  real_T rtu_Ki_Id, real_T rtu_flg_SpaceVectorModulation, real_T rtu_flg_Reset,
  real_T rtu_flg_theta_el_compensation, real_T rty_ua[3], real_T *rty_ub, real_T
  *rty_uc, real_T rty_Iq_ist[2], real_T *rty_Id_ist, real_T *rty_ud_soll, real_T
  *rty_uq_soll, const ConstB_CurrentController *localC, DW_CurrentController
  *localDW);
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
 *    '<S25>/Subsystem - pi//2 delay'
 *    '<S31>/Subsystem - pi//2 delay'
 */
static void Subsystempi2delay(uint8_T rtu_Enable, real_T rtu_dq, real_T rtu_dq_a,
  real_T rtu_wt, real_T *rty_alpha_beta, real_T *rty_alpha_beta_d)
{
  real_T tmp;
  real_T tmp_0;

  /* Outputs for Enabled SubSystem: '<S25>/Subsystem - pi//2 delay' incorporates:
   *  EnablePort: '<S28>/Enable'
   */
  if (rtu_Enable > 0) {
    /* Fcn: '<S28>/Fcn' incorporates:
     *  Fcn: '<S28>/Fcn1'
     */
    tmp = cos(rtu_wt);
    tmp_0 = sin(rtu_wt);
    *rty_alpha_beta = rtu_dq * tmp_0 + rtu_dq_a * tmp;

    /* Fcn: '<S28>/Fcn1' */
    *rty_alpha_beta_d = -rtu_dq * tmp + rtu_dq_a * tmp_0;
  }

  /* End of Outputs for SubSystem: '<S25>/Subsystem - pi//2 delay' */
}

/*
 * Output and update for enable system:
 *    '<S25>/Subsystem1'
 *    '<S31>/Subsystem1'
 */
static void Subsystem1(uint8_T rtu_Enable, real_T rtu_dq, real_T rtu_dq_g,
  real_T rtu_wt, real_T *rty_alpha_beta, real_T *rty_alpha_beta_k)
{
  real_T tmp;
  real_T tmp_0;

  /* Outputs for Enabled SubSystem: '<S25>/Subsystem1' incorporates:
   *  EnablePort: '<S29>/Enable'
   */
  if (rtu_Enable > 0) {
    /* Fcn: '<S29>/Fcn' incorporates:
     *  Fcn: '<S29>/Fcn1'
     */
    tmp = sin(rtu_wt);
    tmp_0 = cos(rtu_wt);
    *rty_alpha_beta = rtu_dq * tmp_0 - rtu_dq_g * tmp;

    /* Fcn: '<S29>/Fcn1' */
    *rty_alpha_beta_k = rtu_dq * tmp + rtu_dq_g * tmp_0;
  }

  /* End of Outputs for SubSystem: '<S25>/Subsystem1' */
}

/* System initialize for function-call system: '<S1>/CurrentController' */
static void CurrentController_Init(DW_CurrentController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_PrevRese = 0;
  localDW->DiscreteTimeIntegrator_PREV_U = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_PrevRe_j = 0;
  localDW->DiscreteTimeIntegrator_PREV_U_j = 0.0;
}

/* Enable for function-call system: '<S1>/CurrentController' */
static void CurrentController_Enable(DW_CurrentController *localDW)
{
  localDW->CurrentController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_SYSTEM_E = 1U;

  /* Enable for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_SYSTEM_c = 1U;
}

/* Output and update for function-call system: '<S1>/CurrentController' */
static void CurrentController(RT_MODEL * const rtM, real_T rtu_ia, real_T rtu_ib,
  real_T rtu_ic, real_T rtu_w_el, real_T rtu_flg_PreCtrl, real_T rtu_theta_el,
  real_T rtu_U_IC, real_T rtu_id_ref, real_T rtu_iq_ref, real_T
  rtu_flg_LimitUdUq, real_T rtu_Kp_Iq, real_T rtu_Ki_Iq, real_T rtu_Kp_Id,
  real_T rtu_Ki_Id, real_T rtu_flg_SpaceVectorModulation, real_T rtu_flg_Reset,
  real_T rtu_flg_theta_el_compensation, real_T rty_ua[3], real_T *rty_ub, real_T
  *rty_uc, real_T rty_Iq_ist[2], real_T *rty_Id_ist, real_T *rty_ud_soll, real_T
  *rty_uq_soll, const ConstB_CurrentController *localC, DW_CurrentController
  *localDW)
{
  real_T DiscreteTimeIntegrator;
  real_T rtb_Gain_c_tmp;
  real_T rtb_Sum_c;
  real_T rtb_Switch2_n;
  int32_T quadrant;
  int32_T sector;
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
    /* Gain: '<S16>/Gain1' incorporates:
     *  Gain: '<S16>/Gain3'
     *  SignalConversion generated from: '<S16>/Gain3'
     */
    localDW->Gain1[quadrant] = 0.66666666666666663 *
      (rtConstP.Gain3_Gain_i[quadrant + 6] * rtu_ic +
       (rtConstP.Gain3_Gain_i[quadrant + 3] * rtu_ib +
        rtConstP.Gain3_Gain_i[quadrant] * rtu_ia));
  }

  /* Gain: '<S2>/Gain' */
  localDW->U_max_dq = 0.57735026918962584 * rtu_U_IC;

  /* Outputs for Enabled SubSystem: '<S15>/Subsystem1' incorporates:
   *  EnablePort: '<S20>/Enable'
   */
  /* Fcn: '<S20>/Fcn' incorporates:
   *  Fcn: '<S20>/Fcn1'
   */
  localDW->error = sin(rtu_theta_el);
  DiscreteTimeIntegrator = cos(rtu_theta_el);

  /* Switch: '<S15>/Switch' incorporates:
   *  Fcn: '<S20>/Fcn'
   *  Fcn: '<S20>/Fcn1'
   */
  rty_Iq_ist[0] = localDW->Gain1[0] * DiscreteTimeIntegrator + localDW->Gain1[1]
    * localDW->error;
  rty_Iq_ist[1] = -localDW->Gain1[0] * localDW->error + localDW->Gain1[1] *
    DiscreteTimeIntegrator;

  /* End of Outputs for SubSystem: '<S15>/Subsystem1' */

  /* Sum: '<S7>/Subtract' */
  localDW->error = rtu_id_ref - rty_Iq_ist[0];

  /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
  if (localDW->DiscreteTimeIntegrator_SYSTEM_E != 0) {
    /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
    DiscreteTimeIntegrator = localDW->DiscreteTimeIntegrator_DSTATE;
  } else if ((rtu_flg_Reset != 0.0) || (localDW->DiscreteTimeIntegrator_PrevRese
              != 0)) {
    localDW->DiscreteTimeIntegrator_DSTATE = 0.0;

    /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
    DiscreteTimeIntegrator = localDW->DiscreteTimeIntegrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
    DiscreteTimeIntegrator = 5.0E-5 * (real_T)CurrentController_ELAPS_T
      * localDW->DiscreteTimeIntegrator_PREV_U +
      localDW->DiscreteTimeIntegrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */

  /* Sum: '<S7>/Sum' incorporates:
   *  Product: '<S7>/Product'
   */
  localDW->Sum_l = localDW->error * rtu_Kp_Id + DiscreteTimeIntegrator;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Gain: '<S7>/Gain'
   *  RelationalOperator: '<S11>/LowerRelop1'
   *  RelationalOperator: '<S11>/UpperRelop'
   *  Switch: '<S11>/Switch'
   */
  if (localDW->Sum_l > localDW->U_max_dq) {
    localDW->Sum_l = localDW->U_max_dq;
  } else if (localDW->Sum_l < -localDW->U_max_dq) {
    /* Switch: '<S11>/Switch' incorporates:
     *  Gain: '<S7>/Gain'
     */
    localDW->Sum_l = -localDW->U_max_dq;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Switch: '<S6>/Switch' incorporates:
   *  Constant: '<S6>/Constant1'
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Product'
   */
  if (rtu_flg_PreCtrl > 0.0) {
    rtb_Sum_c = -1.6E-5 * rty_Iq_ist[1] * rtu_w_el;
  } else {
    rtb_Sum_c = 0.0;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Sum: '<S4>/Add' */
  localDW->Sum_l += rtb_Sum_c;

  /* Gain: '<S9>/Gain' incorporates:
   *  Gain: '<S21>/Gain'
   *  Switch: '<S5>/Switch'
   */
  rtb_Gain_c_tmp = 0.5774 * rtu_U_IC;

  /* Switch: '<S13>/Switch2' incorporates:
   *  Gain: '<S9>/Gain'
   *  Gain: '<S9>/Gain1'
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S13>/Switch'
   */
  if (localDW->Sum_l > rtb_Gain_c_tmp) {
    rtb_Switch2_n = rtb_Gain_c_tmp;
  } else if (localDW->Sum_l < -rtb_Gain_c_tmp) {
    /* Switch: '<S13>/Switch' incorporates:
     *  Gain: '<S9>/Gain1'
     */
    rtb_Switch2_n = -rtb_Gain_c_tmp;
  } else {
    rtb_Switch2_n = localDW->Sum_l;
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Switch: '<S9>/Switch2' */
  if (rtu_flg_LimitUdUq > 0.0) {
    *rty_ud_soll = rtb_Switch2_n;
  } else {
    *rty_ud_soll = localDW->Sum_l;
  }

  /* End of Switch: '<S9>/Switch2' */

  /* Sum: '<S8>/Subtract' */
  localDW->Sum_l = rtu_iq_ref - rty_Iq_ist[1];

  /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  if (localDW->DiscreteTimeIntegrator_SYSTEM_c != 0) {
    /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
    localDW->Gain_j = localDW->DiscreteTimeIntegrator_DSTATE_g;
  } else if ((rtu_flg_Reset != 0.0) || (localDW->DiscreteTimeIntegrator_PrevRe_j
              != 0)) {
    localDW->DiscreteTimeIntegrator_DSTATE_g = 0.0;

    /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
    localDW->Gain_j = localDW->DiscreteTimeIntegrator_DSTATE_g;
  } else {
    /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
    localDW->Gain_j = 5.0E-5 * (real_T)CurrentController_ELAPS_T
      * localDW->DiscreteTimeIntegrator_PREV_U_j +
      localDW->DiscreteTimeIntegrator_DSTATE_g;
  }

  /* End of DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */

  /* Sum: '<S8>/Sum' incorporates:
   *  Product: '<S8>/Product'
   */
  rtb_Sum_c = localDW->Sum_l * rtu_Kp_Iq + localDW->Gain_j;

  /* Switch: '<S12>/Switch2' incorporates:
   *  RelationalOperator: '<S12>/LowerRelop1'
   */
  if (!(rtb_Sum_c > localDW->U_max_dq)) {
    /* Gain: '<S8>/Gain' */
    localDW->U_max_dq = -localDW->U_max_dq;

    /* Switch: '<S12>/Switch' incorporates:
     *  RelationalOperator: '<S12>/UpperRelop'
     */
    if (!(rtb_Sum_c < localDW->U_max_dq)) {
      localDW->U_max_dq = rtb_Sum_c;
    }

    /* End of Switch: '<S12>/Switch' */
  }

  /* End of Switch: '<S12>/Switch2' */

  /* Switch: '<S6>/Switch1' incorporates:
   *  Constant: '<S6>/Constant'
   *  Constant: '<S6>/Constant1'
   *  Gain: '<S6>/Gain2'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Add'
   */
  if (rtu_flg_PreCtrl > 0.0) {
    rtb_Sum_c = (1.6E-5 * rty_Iq_ist[0] + 0.0048) * rtu_w_el;
  } else {
    rtb_Sum_c = 0.0;
  }

  /* End of Switch: '<S6>/Switch1' */

  /* Sum: '<S4>/Add1' */
  localDW->U_max_dq += rtb_Sum_c;

  /* Switch: '<S9>/Switch3' */
  if (rtu_flg_LimitUdUq > 0.0) {
    /* Sqrt: '<S9>/Sqrt' incorporates:
     *  Gain: '<S9>/Gain'
     *  Math: '<S9>/Square'
     *  Math: '<S9>/Square1'
     *  Sum: '<S9>/Add'
     */
    localDW->Gain_c = sqrt(rtb_Gain_c_tmp * rtb_Gain_c_tmp - rtb_Switch2_n *
      rtb_Switch2_n);

    /* Switch: '<S14>/Switch2' incorporates:
     *  Gain: '<S9>/Gain2'
     *  RelationalOperator: '<S14>/LowerRelop1'
     *  RelationalOperator: '<S14>/UpperRelop'
     *  Switch: '<S14>/Switch'
     */
    if (localDW->U_max_dq > localDW->Gain_c) {
      *rty_uq_soll = localDW->Gain_c;
    } else if (localDW->U_max_dq < -localDW->Gain_c) {
      /* Switch: '<S14>/Switch' incorporates:
       *  Gain: '<S9>/Gain2'
       */
      *rty_uq_soll = -localDW->Gain_c;
    } else {
      *rty_uq_soll = localDW->U_max_dq;
    }

    /* End of Switch: '<S14>/Switch2' */
  } else {
    *rty_uq_soll = localDW->U_max_dq;
  }

  /* End of Switch: '<S9>/Switch3' */

  /* Switch: '<S21>/Switch' incorporates:
   *  Constant: '<S21>/Constant2'
   *  Gain: '<S21>/Gain2'
   */
  if (rtu_flg_theta_el_compensation > 0.0) {
    localDW->U_max_dq = 0.00015000000000000001 * rtu_w_el;
  } else {
    localDW->U_max_dq = 0.0;
  }

  /* End of Switch: '<S21>/Switch' */

  /* Sum: '<S21>/Sum1' */
  localDW->U_max_dq += rtu_theta_el;

  /* Outputs for Enabled SubSystem: '<S25>/Subsystem1' */
  Subsystem1(1, *rty_ud_soll, *rty_uq_soll, localDW->U_max_dq, &localDW->Fcn_d,
             &localDW->Fcn1_o);

  /* End of Outputs for SubSystem: '<S25>/Subsystem1' */

  /* Outputs for Enabled SubSystem: '<S25>/Subsystem - pi//2 delay' */
  Subsystempi2delay(localC->Compare_g, *rty_ud_soll, *rty_uq_soll,
                    localDW->U_max_dq, &localDW->Fcn_g, &localDW->Fcn1_p);

  /* End of Outputs for SubSystem: '<S25>/Subsystem - pi//2 delay' */

  /* Switch: '<S22>/Switch' incorporates:
   *  Constant: '<S22>/Constant2'
   *  Gain: '<S22>/Gain2'
   */
  if (rtu_flg_theta_el_compensation > 0.0) {
    localDW->U_max_dq = 0.00015000000000000001 * rtu_w_el;
  } else {
    localDW->U_max_dq = 0.0;
  }

  /* End of Switch: '<S22>/Switch' */

  /* Sum: '<S22>/Sum' */
  localDW->U_max_dq += rtu_theta_el;

  /* Outputs for Enabled SubSystem: '<S31>/Subsystem1' */
  Subsystem1(1, *rty_ud_soll, *rty_uq_soll, localDW->U_max_dq, &localDW->Fcn,
             &localDW->Fcn1);

  /* End of Outputs for SubSystem: '<S31>/Subsystem1' */

  /* Outputs for Enabled SubSystem: '<S31>/Subsystem - pi//2 delay' */
  Subsystempi2delay(localC->Compare_fz, *rty_ud_soll, *rty_uq_soll,
                    localDW->U_max_dq, &localDW->Fcn_b, &localDW->Fcn1_h);

  /* End of Outputs for SubSystem: '<S31>/Subsystem - pi//2 delay' */

  /* MATLAB Function: '<S22>/SpaceVectorModulation' incorporates:
   *  Switch: '<S31>/Switch'
   */
  /* MATLAB Function 'uz_codegen/CurrentController/Modulation/SpaceVectorModulation/SpaceVectorModulation': '<S30>:1' */
  /* '<S30>:1:3' a_U_on=0; */
  localDW->U_max_dq = 0.0;

  /* '<S30>:1:4' a_V_on=0; */
  localDW->Gain_c = 0.0;

  /* '<S30>:1:5' a_W_on=0; */
  localDW->a_W_on = 0.0;

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
  /* '<S30>:1:23' a = abs(u_alpha) + 0.5774*abs(u_beta); */
  rtb_Switch2_n = fabs(localDW->Fcn);
  localDW->c = fabs(localDW->Fcn1);
  localDW->Switch1_c = 0.5774 * localDW->c + rtb_Switch2_n;

  /* '<S30>:1:24' b = abs(u_alpha) - 0.5774*abs(u_beta); */
  rtb_Sum_c = rtb_Switch2_n - 0.5774 * fabs(localDW->Fcn1);

  /* '<S30>:1:25' c = 1.1547*abs(u_beta); */
  localDW->c *= 1.1547;

  /* '<S30>:1:27' U_max = 0.6667 * U_ZK; */
  localDW->U_max = 0.6667 * rtu_U_IC;

  /* Maximum Voltage U_ZL/sqrt(3) */
  /* Sektor und Quadranten nach Quang Dittrich S32 */
  /* '<S30>:1:31' if(u_beta < 0) */
  if (localDW->Fcn1 < 0.0) {
    /* '<S30>:1:32' if (u_alpha <0) */
    if (localDW->Fcn < 0.0) {
      /* '<S30>:1:33' quadrant=3; */
      quadrant = 3;

      /* '<S30>:1:34' if(b < 0) */
      if (rtb_Sum_c < 0.0) {
        /* '<S30>:1:35' sector = 5; */
        sector = 5;
      } else {
        /* '<S30>:1:36' else */
        /* '<S30>:1:37' sector = 4; */
        sector = 4;
      }
    } else {
      /* '<S30>:1:39' else */
      /* '<S30>:1:40' quadrant=4; */
      quadrant = 4;

      /* '<S30>:1:41' if(b < 0) */
      if (rtb_Sum_c < 0.0) {
        /* '<S30>:1:42' sector = 5; */
        sector = 5;
      } else {
        /* '<S30>:1:43' else */
        /* '<S30>:1:44' sector = 6; */
        sector = 6;
      }
    }

    /* '<S30>:1:48' else */
    /* '<S30>:1:49' if (u_alpha <0) */
  } else if (localDW->Fcn < 0.0) {
    /* '<S30>:1:50' quadrant=2; */
    quadrant = 2;

    /* '<S30>:1:51' if(b < 0) */
    if (rtb_Sum_c < 0.0) {
      /* '<S30>:1:52' sector = 2; */
      sector = 2;
    } else {
      /* '<S30>:1:53' else */
      /* '<S30>:1:54' sector = 3; */
      sector = 3;
    }
  } else {
    /* '<S30>:1:56' else */
    /* '<S30>:1:57' quadrant=1; */
    quadrant = 1;

    /* '<S30>:1:58' if(b < 0) */
    if (rtb_Sum_c < 0.0) {
      /* '<S30>:1:59' sector = 2; */
      sector = 2;
    } else {
      /* '<S30>:1:60' else */
      /* '<S30>:1:61' sector = 1; */
      sector = 1;
    }
  }

  /* '<S30>:1:66' sector = sector; */
  /* Modulationsfunktionen f¸r Phasen U,V,W */
  /* Erzeugung der Aussteuergrade f¸r die Halbbr¸cken */
  /* --> Erzeugung einer "regulary Sampled SVM" erfolgt anschlieﬂend durch Abtastung */
  /* mit Dreiecksz‰hlern in Hardware. */
  /* '<S30>:1:73' if (sector == 1) */
  if (sector == 1) {
    /* Quang S.24 and normed to 2/3 U_DC */
    /* '<S30>:1:76' u1 = b/(U_max); */
    localDW->a_W_on = rtb_Sum_c / localDW->U_max;

    /* '<S30>:1:77' u2 = c/(U_max); */
    localDW->u2 = localDW->c / localDW->U_max;

    /* Quang S.34 */
    /* '<S30>:1:80' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->U_max_dq = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:81' a_V_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->Gain_c = (0.5 - localDW->a_W_on * 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:82' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->a_W_on = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;
  }

  /* '<S30>:1:86' if ((sector == 2) && (quadrant == 1)) */
  if ((sector == 2) && (quadrant == 1)) {
    /* '<S30>:1:88' u1 = a/(U_max); */
    localDW->a_W_on = localDW->Switch1_c / localDW->U_max;

    /* '<S30>:1:89' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->u2 = (0.5774 * fabs(localDW->Fcn1) + -rtb_Switch2_n) /
      localDW->U_max;

    /* '<S30>:1:91' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->U_max_dq = (localDW->a_W_on * 0.5 + 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:92' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Gain_c = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:93' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->a_W_on = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;
  }

  /* '<S30>:1:97' if ((sector == 2) && (quadrant == 2)) */
  if ((sector == 2) && (quadrant == 2)) {
    /* '<S30>:1:99' u1 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->a_W_on = (0.5774 * fabs(localDW->Fcn1) + -fabs(localDW->Fcn)) /
      localDW->U_max;

    /* '<S30>:1:100' u2 = a/(U_max); */
    localDW->u2 = localDW->Switch1_c / localDW->U_max;

    /* '<S30>:1:102' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->U_max_dq = (localDW->a_W_on * 0.5 + 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:103' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Gain_c = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:104' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->a_W_on = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;
  }

  /* '<S30>:1:108' if (sector == 3) */
  if (sector == 3) {
    /* '<S30>:1:110' u1 = c/(U_max); */
    localDW->a_W_on = localDW->c / localDW->U_max;

    /* '<S30>:1:111' u2 = b/(U_max); */
    localDW->u2 = rtb_Sum_c / localDW->U_max;

    /* '<S30>:1:113' a_U_on=  0.5 - u1*0.5 - u2*0.5; */
    localDW->U_max_dq = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:114' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Gain_c = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:115' a_W_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->a_W_on = (0.5 - localDW->a_W_on * 0.5) + localDW->u2 * 0.5;
  }

  /* '<S30>:1:118' if (sector == 4) */
  if (sector == 4) {
    /* '<S30>:1:120' u1 = b/(U_max); */
    localDW->a_W_on = rtb_Sum_c / localDW->U_max;

    /* '<S30>:1:121' u2 = c/(U_max); */
    localDW->u2 = localDW->c / localDW->U_max;

    /* '<S30>:1:123' a_U_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->U_max_dq = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:124' a_V_on = 0.5 + u1*0.5 - u2*0.5; */
    rtb_Switch2_n = localDW->a_W_on * 0.5 + 0.5;
    localDW->Gain_c = rtb_Switch2_n - localDW->u2 * 0.5;

    /* '<S30>:1:125' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_W_on = rtb_Switch2_n + localDW->u2 * 0.5;
  }

  /* '<S30>:1:129' if ((sector == 5) && (quadrant == 3)) */
  if ((sector == 5) && (quadrant == 3)) {
    /* '<S30>:1:131' u1 = a/(U_max); */
    localDW->a_W_on = localDW->Switch1_c / localDW->U_max;

    /* '<S30>:1:132' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->u2 = (0.5774 * fabs(localDW->Fcn1) + -fabs(localDW->Fcn)) /
      localDW->U_max;

    /* '<S30>:1:134' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->U_max_dq = (0.5 - localDW->a_W_on * 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:135' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Gain_c = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:136' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_W_on = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;
  }

  /* '<S30>:1:140' if ((sector == 5) && (quadrant == 4)) */
  if ((sector == 5) && (quadrant == 4)) {
    /* '<S30>:1:142' u1 =(-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->a_W_on = (0.5774 * fabs(localDW->Fcn1) + -fabs(localDW->Fcn)) /
      localDW->U_max;

    /* '<S30>:1:143' u2 =  a/(U_max); */
    localDW->u2 = localDW->Switch1_c / localDW->U_max;

    /* '<S30>:1:145' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->U_max_dq = (0.5 - localDW->a_W_on * 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:146' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Gain_c = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:147' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_W_on = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;
  }

  /* '<S30>:1:151' if (sector == 6) */
  if (sector == 6) {
    /* '<S30>:1:153' u1 = c/(U_max); */
    localDW->a_W_on = localDW->c / localDW->U_max;

    /* '<S30>:1:154' u2 = b/(U_max); */
    localDW->u2 = rtb_Sum_c / localDW->U_max;

    /* '<S30>:1:156' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->U_max_dq = (localDW->a_W_on * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S30>:1:157' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Gain_c = (0.5 - localDW->a_W_on * 0.5) - localDW->u2 * 0.5;

    /* '<S30>:1:158' a_W_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->a_W_on = (localDW->a_W_on * 0.5 + 0.5) - localDW->u2 * 0.5;
  }

  /* '<S30>:1:161' if a_U_on > 1.0 */
  if (localDW->U_max_dq > 1.0) {
    /* '<S30>:1:162' a_U_on = 1.0; */
    localDW->U_max_dq = 1.0;
  }

  /* '<S30>:1:164' if a_V_on > 1.0 */
  if (localDW->Gain_c > 1.0) {
    /* '<S30>:1:165' a_V_on = 1.0; */
    localDW->Gain_c = 1.0;
  }

  /* '<S30>:1:167' if a_W_on > 1.0 */
  if (localDW->a_W_on > 1.0) {
    /* '<S30>:1:168' a_W_on = 1.0; */
    localDW->a_W_on = 1.0;
  }

  /* Switch: '<S5>/Switch' incorporates:
   *  MATLAB Function: '<S22>/SpaceVectorModulation'
   */
  /* '<S30>:1:171' u_a = a_U_on; */
  /* '<S30>:1:172' u_b = a_V_on; */
  /* '<S30>:1:173' u_c = a_W_on; */
  if (rtu_flg_SpaceVectorModulation > 0.0) {
    rty_ua[0] = localDW->U_max_dq;
    rty_ua[1] = localDW->Gain_c;
    rty_ua[2] = localDW->a_W_on;
  } else {
    /* Product: '<S21>/Divide' incorporates:
     *  Constant: '<S21>/Constant1'
     *  Gain: '<S21>/Gain1'
     *  Gain: '<S24>/Gain3'
     *  Sum: '<S21>/Sum'
     *  Switch: '<S25>/Switch'
     */
    for (quadrant = 0; quadrant < 3; quadrant++) {
      rty_ua[quadrant] = ((rtConstP.Gain3_Gain[quadrant + 3] * localDW->Fcn1_o +
                           rtConstP.Gain3_Gain[quadrant] * localDW->Fcn_d) +
                          rtConstP.Gain3_Gain[quadrant + 6] * 0.0) /
        rtb_Gain_c_tmp * 0.5 + 0.5;
    }

    /* End of Product: '<S21>/Divide' */
  }

  /* SignalConversion generated from: '<S2>/ub' */
  *rty_ub = rty_ua[1];

  /* SignalConversion generated from: '<S2>/uc' */
  *rty_uc = rty_ua[2];

  /* SignalConversion generated from: '<S2>/Id_ist' */
  *rty_Id_ist = rty_Iq_ist[0];

  /* Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator' incorporates:
   *  DiscreteIntegrator: '<S8>/Discrete-Time Integrator'
   *  Product: '<S7>/Product1'
   */
  localDW->DiscreteTimeIntegrator_SYSTEM_E = 0U;
  localDW->DiscreteTimeIntegrator_DSTATE = DiscreteTimeIntegrator;
  if (rtu_flg_Reset > 0.0) {
    localDW->DiscreteTimeIntegrator_PrevRese = 1;
    localDW->DiscreteTimeIntegrator_PrevRe_j = 1;
  } else {
    if (rtu_flg_Reset < 0.0) {
      localDW->DiscreteTimeIntegrator_PrevRese = -1;
    } else if (rtu_flg_Reset == 0.0) {
      localDW->DiscreteTimeIntegrator_PrevRese = 0;
    } else {
      localDW->DiscreteTimeIntegrator_PrevRese = 2;
    }

    if (rtu_flg_Reset < 0.0) {
      localDW->DiscreteTimeIntegrator_PrevRe_j = -1;
    } else if (rtu_flg_Reset == 0.0) {
      localDW->DiscreteTimeIntegrator_PrevRe_j = 0;
    } else {
      localDW->DiscreteTimeIntegrator_PrevRe_j = 2;
    }
  }

  localDW->DiscreteTimeIntegrator_PREV_U = localDW->error * rtu_Ki_Id;

  /* End of Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' incorporates:
   *  Product: '<S8>/Product1'
   */
  localDW->DiscreteTimeIntegrator_SYSTEM_c = 0U;
  localDW->DiscreteTimeIntegrator_DSTATE_g = localDW->Gain_j;
  localDW->DiscreteTimeIntegrator_PREV_U_j = localDW->Sum_l * rtu_Ki_Iq;
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  uint32_T SpeedController_ELAPS_T;

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
    rtY->activeState = 1.0;

    /* Outport: '<Root>/Ua_DutyCycle' */
    /* '<S1>:1:4' Ua_DutyCycle = 0; */
    rtY->Ua_DutyCycle = 0.0;

    /* Outport: '<Root>/Ub_DutyCycle' */
    /* '<S1>:1:5' Ub_DutyCycle = 0; */
    rtY->Ub_DutyCycle = 0.0;

    /* Outport: '<Root>/Uc_DutyCycle' */
    /* '<S1>:1:6' Uc_DutyCycle = 0; */
    rtY->Uc_DutyCycle = 0.0;
  } else {
    switch (rtDW->is_c3_uz_codegen0) {
     case IN_InProcess:
      /* During 'InProcess': '<S1>:3' */
      /* '<S1>:18:1' sf_internal_predicateOutput = RESET==1; */
      if (rtU->RESET == 1.0F) {
        /* Transition: '<S1>:18' */
        rtDW->is_c3_uz_codegen0 = IN_Reset;

        /* Entry 'Reset': '<S1>:119' */
      } else {
        /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
        /* '<S1>:3:5' [id_soll, iq_soll] = SpeedController(id_ref, iq_ref, n_ref, n_ist, flg_SpeedControl, flg_FieldWeakening, Kp_Speed, Ki_Speed, I_max, RESET) */
        /* Simulink Function 'SpeedController': '<S1>:133' */
        if (rtDW->SpeedController_RESET_ELAPS_T) {
          SpeedController_ELAPS_T = 0U;
        } else {
          SpeedController_ELAPS_T = rtM->Timing.clockTick0 -
            rtDW->SpeedController_PREV_T;
        }

        rtDW->SpeedController_PREV_T = rtM->Timing.clockTick0;
        rtDW->SpeedController_RESET_ELAPS_T = false;

        /* Sum: '<S37>/Sum' incorporates:
         *  Inport: '<Root>/n_ist'
         *  Inport: '<Root>/n_ref'
         */
        rtDW->IProdOut = (real_T)rtU->n_ref - rtU->n_ist;

        /* DiscreteIntegrator: '<S73>/Integrator' */
        if (rtDW->Integrator_SYSTEM_ENABLE != 0) {
          /* DiscreteIntegrator: '<S73>/Integrator' */
          rtDW->Integrator = rtDW->Integrator_DSTATE;
        } else if ((rtU->RESET != 0.0F) || (rtDW->Integrator_PrevResetState != 0))
        {
          rtDW->Integrator_DSTATE = 0.0;

          /* DiscreteIntegrator: '<S73>/Integrator' */
          rtDW->Integrator = rtDW->Integrator_DSTATE;
        } else {
          /* DiscreteIntegrator: '<S73>/Integrator' */
          rtDW->Integrator = 5.0E-5 * (real_T)SpeedController_ELAPS_T
            * rtDW->Integrator_PREV_U + rtDW->Integrator_DSTATE;
        }

        /* End of DiscreteIntegrator: '<S73>/Integrator' */

        /* Sum: '<S83>/Sum' incorporates:
         *  Inport: '<Root>/Kp_Speed'
         *  Product: '<S78>/PProd Out'
         */
        rtDW->Sum = rtDW->IProdOut * rtU->Kp_Speed + rtDW->Integrator;

        /* Switch: '<S66>/Switch' incorporates:
         *  Gain: '<S37>/Gain'
         *  Inport: '<Root>/I_max'
         *  RelationalOperator: '<S66>/u_GTE_up'
         *  RelationalOperator: '<S66>/u_GT_lo'
         *  Switch: '<S66>/Switch1'
         */
        if (rtDW->Sum >= rtU->I_max) {
          rtDW->SignPreIntegrator = rtU->I_max;
        } else if (rtDW->Sum > -(real_T)rtU->I_max) {
          /* Switch: '<S66>/Switch1' */
          rtDW->SignPreIntegrator = rtDW->Sum;
        } else {
          rtDW->SignPreIntegrator = -(real_T)rtU->I_max;
        }

        /* End of Switch: '<S66>/Switch' */

        /* Sum: '<S66>/Diff' */
        rtDW->SignPreIntegrator = rtDW->Sum - rtDW->SignPreIntegrator;

        /* Product: '<S70>/IProd Out' incorporates:
         *  Inport: '<Root>/Ki_Speed'
         */
        rtDW->IProdOut *= rtU->Ki_Speed;

        /* Switch: '<S36>/Switch1' incorporates:
         *  Inport: '<Root>/flg_SpeedControl'
         */
        if (rtU->flg_SpeedControl > 0.0F) {
          /* Switch: '<S81>/Switch2' incorporates:
           *  Gain: '<S37>/Gain'
           *  Inport: '<Root>/I_max'
           *  RelationalOperator: '<S81>/LowerRelop1'
           *  RelationalOperator: '<S81>/UpperRelop'
           *  Switch: '<S81>/Switch'
           */
          if (rtDW->Sum > rtU->I_max) {
            /* Outport: '<Root>/iq_soll' incorporates:
             *  Switch: '<S36>/Switch1'
             */
            rtY->iq_soll = rtU->I_max;
          } else if (rtDW->Sum < -(real_T)rtU->I_max) {
            /* Switch: '<S81>/Switch' incorporates:
             *  Gain: '<S37>/Gain'
             *  Outport: '<Root>/iq_soll'
             *  Switch: '<S36>/Switch1'
             */
            rtY->iq_soll = -(real_T)rtU->I_max;
          } else {
            /* Outport: '<Root>/iq_soll' incorporates:
             *  Switch: '<S36>/Switch1'
             *  Switch: '<S81>/Switch'
             */
            rtY->iq_soll = rtDW->Sum;
          }

          /* End of Switch: '<S81>/Switch2' */
        } else {
          /* Outport: '<Root>/iq_soll' incorporates:
           *  Inport: '<Root>/iq_ref'
           *  Switch: '<S36>/Switch1'
           */
          rtY->iq_soll = rtU->iq_ref;
        }

        /* End of Switch: '<S36>/Switch1' */

        /* Update for DiscreteIntegrator: '<S73>/Integrator' */
        rtDW->Integrator_SYSTEM_ENABLE = 0U;
        rtDW->Integrator_DSTATE = rtDW->Integrator;
        if (rtU->RESET > 0.0F) {
          rtDW->Integrator_PrevResetState = 1;
        } else if (rtU->RESET < 0.0F) {
          rtDW->Integrator_PrevResetState = -1;
        } else if (rtU->RESET == 0.0F) {
          rtDW->Integrator_PrevResetState = 0;
        } else {
          rtDW->Integrator_PrevResetState = 2;
        }

        /* Signum: '<S63>/SignPreSat' */
        if (rtDW->SignPreIntegrator < 0.0) {
          rtDW->Integrator = -1.0;
        } else if (rtDW->SignPreIntegrator > 0.0) {
          rtDW->Integrator = 1.0;
        } else if (rtDW->SignPreIntegrator == 0.0) {
          rtDW->Integrator = 0.0;
        } else {
          rtDW->Integrator = (rtNaN);
        }

        /* End of Signum: '<S63>/SignPreSat' */

        /* Signum: '<S63>/SignPreIntegrator' */
        if (rtDW->IProdOut < 0.0) {
          rtDW->rtb_IProdOut_m = -1.0;
        } else if (rtDW->IProdOut > 0.0) {
          rtDW->rtb_IProdOut_m = 1.0;
        } else if (rtDW->IProdOut == 0.0) {
          rtDW->rtb_IProdOut_m = 0.0;
        } else {
          rtDW->rtb_IProdOut_m = (rtNaN);
        }

        /* End of Signum: '<S63>/SignPreIntegrator' */

        /* Switch: '<S63>/Switch' incorporates:
         *  DataTypeConversion: '<S63>/DataTypeConv1'
         *  DataTypeConversion: '<S63>/DataTypeConv2'
         *  Gain: '<S63>/ZeroGain'
         *  Logic: '<S63>/AND3'
         *  RelationalOperator: '<S63>/Equal1'
         *  RelationalOperator: '<S63>/NotEqual'
         */
        if ((0.0 * rtDW->Sum != rtDW->SignPreIntegrator) && ((int8_T)
             rtDW->Integrator == (int8_T)rtDW->rtb_IProdOut_m)) {
          /* Update for DiscreteIntegrator: '<S73>/Integrator' incorporates:
           *  Constant: '<S63>/Constant1'
           */
          rtDW->Integrator_PREV_U = 0.0;
        } else {
          /* Update for DiscreteIntegrator: '<S73>/Integrator' */
          rtDW->Integrator_PREV_U = rtDW->IProdOut;
        }

        /* End of Switch: '<S63>/Switch' */

        /* Switch: '<S36>/Switch' incorporates:
         *  Inport: '<Root>/flg_SpeedControl'
         */
        if (rtU->flg_SpeedControl > 0.0F) {
          /* Outport: '<Root>/id_soll' incorporates:
           *  Constant: '<S37>/Constant'
           */
          rtY->id_soll = 0.0;
        } else {
          /* Outport: '<Root>/id_soll' incorporates:
           *  Inport: '<Root>/id_ref'
           */
          rtY->id_soll = rtU->id_ref;
        }

        /* End of Switch: '<S36>/Switch' */
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
        CurrentController(rtM, (real_T)rtU->ia, (real_T)rtU->ib, (real_T)rtU->ic,
                          (real_T)rtU->w_el, (real_T)rtU->flg_PreCntr, (real_T)
                          rtU->theta_el, (real_T)rtU->U_IC, rtY->id_soll,
                          rtY->iq_soll, (real_T)rtU->flgLimitUdUq, (real_T)
                          rtU->Kp_Iq, (real_T)rtU->Ki_Iq, (real_T)rtU->Kp_Id,
                          (real_T)rtU->Ki_Id, (real_T)
                          rtU->flg_SpaceVectorModulation, (real_T)rtU->RESET,
                          (real_T)rtU->flg_theta_el_compensation, rtDW->Switch_e,
                          &rtY->Ub_DutyCycle, &rtY->Uc_DutyCycle, rtDW->Switch_m,
                          &rtY->id_ist, &rtY->ud, &rtY->uq,
                          &rtConstB.CurrentController_o,
                          &rtDW->CurrentController_o);

        /* End of Outputs for SubSystem: '<S1>/CurrentController' */

        /* Outport: '<Root>/Ua_DutyCycle' */
        rtY->Ua_DutyCycle = rtDW->Switch_e[0];

        /* Outport: '<Root>/iq_ist' */
        rtY->iq_ist = rtDW->Switch_m[1];
      }
      break;

     case IN_Reset:
      /* During 'Reset': '<S1>:119' */
      /* '<S1>:121:1' sf_internal_predicateOutput = RESET == 0; */
      if (rtU->RESET == 0.0F) {
        /* Transition: '<S1>:121' */
        rtDW->is_c3_uz_codegen0 = IN_Start;

        /* Outport: '<Root>/activeState' */
        /* Entry 'Start': '<S1>:1' */
        /* '<S1>:1:3' activeState = 1; */
        rtY->activeState = 1.0;

        /* Outport: '<Root>/Ua_DutyCycle' */
        /* '<S1>:1:4' Ua_DutyCycle = 0; */
        rtY->Ua_DutyCycle = 0.0;

        /* Outport: '<Root>/Ub_DutyCycle' */
        /* '<S1>:1:5' Ub_DutyCycle = 0; */
        rtY->Ub_DutyCycle = 0.0;

        /* Outport: '<Root>/Uc_DutyCycle' */
        /* '<S1>:1:6' Uc_DutyCycle = 0; */
        rtY->Uc_DutyCycle = 0.0;
      } else {
        /* Outport: '<Root>/activeState' */
        /* '<S1>:119:3' activeState = 3; */
        rtY->activeState = 3.0;

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
        /* '<S1>:119:4' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_ref,iq_ref,flgLimitUdUq, Kp_Iq, Ki_Iq, Kp_Id, Ki_Id, flg_SpaceVectorModulation, RESET, flg_deadTimeCompensation, flg_theta_el_compensation) */
        /* Simulink Function 'CurrentController': '<S1>:72' */
        CurrentController(rtM, (real_T)rtU->ia, (real_T)rtU->ib, (real_T)rtU->ic,
                          (real_T)rtU->w_el, (real_T)rtU->flg_PreCntr, (real_T)
                          rtU->theta_el, (real_T)rtU->U_IC, (real_T)rtU->id_ref,
                          (real_T)rtU->iq_ref, (real_T)rtU->flgLimitUdUq,
                          (real_T)rtU->Kp_Iq, (real_T)rtU->Ki_Iq, (real_T)
                          rtU->Kp_Id, (real_T)rtU->Ki_Id, (real_T)
                          rtU->flg_SpaceVectorModulation, (real_T)rtU->RESET,
                          (real_T)rtU->flg_theta_el_compensation, rtDW->Switch_e,
                          &rtDW->Sum, &rtDW->IProdOut, rtDW->Switch_m,
                          &rtY->id_ist, &rtY->ud, &rtY->uq,
                          &rtConstB.CurrentController_o,
                          &rtDW->CurrentController_o);

        /* End of Outputs for SubSystem: '<S1>/CurrentController' */

        /* Outport: '<Root>/iq_ist' */
        rtY->iq_ist = rtDW->Switch_m[1];

        /* Outport: '<Root>/Ua_DutyCycle' */
        /* '<S1>:119:5' Ua_DutyCycle = 0; */
        rtY->Ua_DutyCycle = 0.0;

        /* Outport: '<Root>/Ub_DutyCycle' */
        /* '<S1>:119:6' Ub_DutyCycle = 0; */
        rtY->Ub_DutyCycle = 0.0;

        /* Outport: '<Root>/Uc_DutyCycle' */
        /* '<S1>:119:7' Uc_DutyCycle = 0; */
        rtY->Uc_DutyCycle = 0.0;
      }
      break;

     default:
      /* During 'Start': '<S1>:1' */
      /* '<S1>:17:1' sf_internal_predicateOutput = START==1 & RESET==0; */
      if ((rtU->START == 1.0F) && (rtU->RESET == 0.0F)) {
        /* Transition: '<S1>:17' */
        rtDW->is_c3_uz_codegen0 = IN_InProcess;

        /* Outport: '<Root>/activeState' */
        /* Entry 'InProcess': '<S1>:3' */
        /* '<S1>:3:3' activeState = 2; */
        rtY->activeState = 2.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/uz_codegen' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 5.0E-5, which is the step size
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
  rtY->Ua_DutyCycle = 0.0;

  /* SystemInitialize for Outport: '<Root>/activeState' */
  rtY->activeState = 0.0;

  /* SystemInitialize for Outport: '<Root>/Uc_DutyCycle' */
  rtY->Uc_DutyCycle = 0.0;

  /* SystemInitialize for Outport: '<Root>/Ub_DutyCycle' */
  rtY->Ub_DutyCycle = 0.0;

  /* SystemInitialize for Outport: '<Root>/iq_ist' */
  rtY->iq_ist = 0.0;

  /* SystemInitialize for Outport: '<Root>/id_ist' */
  rtY->id_ist = 0.0;

  /* SystemInitialize for Outport: '<Root>/uq' */
  rtY->uq = 0.0;

  /* SystemInitialize for Outport: '<Root>/ud' */
  rtY->ud = 0.0;

  /* SystemInitialize for Outport: '<Root>/iq_soll' */
  rtY->iq_soll = 0.0;

  /* SystemInitialize for Outport: '<Root>/id_soll' */
  rtY->id_soll = 0.0;

  /* SystemInitialize for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Init(&rtDW->CurrentController_o);

  /* SystemInitialize for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S73>/Integrator' */
  rtDW->Integrator_PrevResetState = 0;
  rtDW->Integrator_PREV_U = 0.0;

  /* Enable for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Enable(&rtDW->CurrentController_o);

  /* Enable for Chart: '<Root>/uz_codegen' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  rtDW->SpeedController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S73>/Integrator' */
  rtDW->Integrator_SYSTEM_ENABLE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
