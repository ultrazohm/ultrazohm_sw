/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_FOC.c
 *
 * Code generated for Simulink model 'Basic_FOC'.
 *
 * Model version                  : 2.22
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jun 29 12:48:17 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
 */

#include "Basic_FOC.h"

/* Named constants for Chart: '<Root>/Basic_FOC' */
#define IN_CurrentControl              ((uint8_T)1U)
#define IN_InProcess                   ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_SpeedControl                ((uint8_T)2U)
#define IN_Start                       ((uint8_T)2U)
#define NumBitsPerChar                 8U

static void CurrentController_Init(DW_CurrentController *localDW);
static void CurrentController_Enable(DW_CurrentController *localDW);
static void CurrentController(RT_MODEL * const rtM, real32_T rtu_ia, real32_T
  rtu_ib, real32_T rtu_ic, real32_T rtu_w_el, real32_T rtu_flg_PreCtrl, real32_T
  rtu_theta_el, real32_T rtu_U_IC, real32_T rtu_id_ref, real32_T rtu_iq_ref,
  real32_T rtu_flg_LimitUdUq, real32_T *rty_ua, real32_T *rty_ub, real32_T
  *rty_uc, real32_T rty_Iq_ist[2], real32_T *rty_Id_ist, real32_T *rty_ud_soll,
  real32_T *rty_uq_soll, DW_CurrentController *localDW);
static void SpeedController_Init(DW_SpeedController *localDW);
static void SpeedController_Enable(DW_SpeedController *localDW);
static void SpeedController(RT_MODEL * const rtM, real32_T rtu_id_ref, real32_T
  rtu_iq_ref, real32_T rtu_n_soll, real32_T rtu_n_ist, real32_T
  rtu_flg_fieldWeakening, real32_T rtu_flg_UseMMPA, real32_T
  rtu_flg_SpeedControl, real32_T *rty_id_soll, real32_T *rty_iq_soll,
  DW_SpeedController *localDW);

/* Forward declaration for local functions */
static void enter_atomic_SpeedControl(real32_T *id_ref_n, real32_T *iq_ref_o,
  real32_T *n_soll, real32_T *n_ist, real32_T *flg_fieldWeakening, real32_T
  *flg_UseMMPA, ExtU *rtU, ExtY *rtY, RT_MODEL *rtM, DW *rtDW);
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

/* System initialize for function-call system: '<S1>/CurrentController' */
static void CurrentController_Init(DW_CurrentController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S45>/Integrator' */
  localDW->Integrator_PREV_U = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_PREV_U_f = 0.0F;
}

/* Enable for function-call system: '<S1>/CurrentController' */
static void CurrentController_Enable(DW_CurrentController *localDW)
{
  localDW->CurrentController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S45>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 1U;

  /* Enable for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE_a = 1U;
}

/* Output and update for function-call system: '<S1>/CurrentController' */
static void CurrentController(RT_MODEL * const rtM, real32_T rtu_ia, real32_T
  rtu_ib, real32_T rtu_ic, real32_T rtu_w_el, real32_T rtu_flg_PreCtrl, real32_T
  rtu_theta_el, real32_T rtu_U_IC, real32_T rtu_id_ref, real32_T rtu_iq_ref,
  real32_T rtu_flg_LimitUdUq, real32_T *rty_ua, real32_T *rty_ub, real32_T
  *rty_uc, real32_T rty_Iq_ist[2], real32_T *rty_Id_ist, real32_T *rty_ud_soll,
  real32_T *rty_uq_soll, DW_CurrentController *localDW)
{
  int32_T quadrant;
  int32_T sector;
  real32_T Integrator;
  real32_T Integrator_p;
  real32_T U_max;
  real32_T a_tmp;
  real32_T c;
  real32_T rtb_Gain;
  real32_T rtb_Gain1_eb;
  real32_T rtb_IntegralGain;
  real32_T rtb_SignPreSat;
  real32_T rtb_SignPreSat_b;
  real32_T rtb_Switch_m_idx_0;
  real32_T rtb_Switch_m_idx_1;
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
    localDW->Gain1[quadrant] = 0.666666687F * (rtConstP.Gain3_Gain[quadrant + 6]
      * rtu_ic + (rtConstP.Gain3_Gain[quadrant + 3] * rtu_ib +
                  rtConstP.Gain3_Gain[quadrant] * rtu_ia));
  }

  /* Outputs for Enabled SubSystem: '<S122>/Subsystem1' incorporates:
   *  EnablePort: '<S126>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<S115>/Subsystem1' incorporates:
   *  EnablePort: '<S120>/Enable'
   */
  /* Fcn: '<S120>/Fcn' incorporates:
   *  Fcn: '<S120>/Fcn1'
   *  Fcn: '<S126>/Fcn'
   *  Fcn: '<S126>/Fcn1'
   */
  localDW->a_W_on = sinf(rtu_theta_el);
  rtb_Switch_m_idx_1 = cosf(rtu_theta_el);

  /* End of Outputs for SubSystem: '<S122>/Subsystem1' */

  /* Switch: '<S115>/Switch' incorporates:
   *  Fcn: '<S120>/Fcn'
   *  Fcn: '<S120>/Fcn1'
   */
  rty_Iq_ist[0] = localDW->Gain1[0] * rtb_Switch_m_idx_1 + localDW->Gain1[1] *
    localDW->a_W_on;
  rty_Iq_ist[1] = -localDW->Gain1[0] * localDW->a_W_on + localDW->Gain1[1] *
    rtb_Switch_m_idx_1;

  /* End of Outputs for SubSystem: '<S115>/Subsystem1' */

  /* Sum: '<S7>/Subtract' */
  rtb_IntegralGain = rtu_id_ref - rty_Iq_ist[0];

  /* DiscreteIntegrator: '<S45>/Integrator' */
  if (localDW->Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S45>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S45>/Integrator' */
    Integrator = 0.0001F * (real32_T)CurrentController_ELAPS_T
      * localDW->Integrator_PREV_U + localDW->Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S45>/Integrator' */

  /* Gain: '<S43>/Proportional Gain' incorporates:
   *  Sum: '<S54>/Sum'
   */
  rtb_SignPreSat = (rtb_IntegralGain + Integrator) * 0.100530967F;

  /* Saturate: '<S52>/Saturation' */
  if (rtb_SignPreSat > 26.5581131F) {
    rtb_Switch_m_idx_0 = 26.5581131F;
  } else if (rtb_SignPreSat < -26.5581131F) {
    rtb_Switch_m_idx_0 = -26.5581131F;
  } else {
    rtb_Switch_m_idx_0 = rtb_SignPreSat;
  }

  /* End of Saturate: '<S52>/Saturation' */

  /* Switch: '<S4>/Switch1' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Product'
   */
  if (rtu_flg_PreCtrl > 0.0F) {
    localDW->Switch_b = -1.6E-5F * rtu_iq_ref * rtu_w_el;
  } else {
    localDW->Switch_b = 0.0;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S4>/Add' */
  localDW->Switch_b += rtb_Switch_m_idx_0;

  /* Gain: '<S9>/Gain' */
  rtb_Gain = 0.5774F * rtu_U_IC;

  /* Switch: '<S113>/Switch2' incorporates:
   *  Gain: '<S9>/Gain1'
   *  RelationalOperator: '<S113>/LowerRelop1'
   *  RelationalOperator: '<S113>/UpperRelop'
   *  Switch: '<S113>/Switch'
   */
  if (localDW->Switch_b > rtb_Gain) {
    localDW->Switch2 = rtb_Gain;
  } else if (localDW->Switch_b < -rtb_Gain) {
    /* Switch: '<S113>/Switch' incorporates:
     *  Gain: '<S9>/Gain1'
     */
    localDW->Switch2 = -rtb_Gain;
  } else {
    localDW->Switch2 = localDW->Switch_b;
  }

  /* End of Switch: '<S113>/Switch2' */

  /* Switch: '<S4>/Switch2' */
  if (rtu_flg_LimitUdUq > 0.0F) {
    *rty_ud_soll = (real32_T)localDW->Switch2;
  } else {
    *rty_ud_soll = (real32_T)localDW->Switch_b;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Sum: '<S8>/Subtract' */
  rtb_Gain1_eb = rtu_iq_ref - rty_Iq_ist[1];

  /* DiscreteIntegrator: '<S96>/Integrator' */
  if (localDW->Integrator_SYSTEM_ENABLE_a != 0) {
    /* DiscreteIntegrator: '<S96>/Integrator' */
    Integrator_p = localDW->Integrator_DSTATE_a;
  } else {
    /* DiscreteIntegrator: '<S96>/Integrator' */
    Integrator_p = 0.0001F * (real32_T)CurrentController_ELAPS_T
      * localDW->Integrator_PREV_U_f + localDW->Integrator_DSTATE_a;
  }

  /* End of DiscreteIntegrator: '<S96>/Integrator' */

  /* Gain: '<S94>/Proportional Gain' incorporates:
   *  Sum: '<S105>/Sum'
   */
  rtb_SignPreSat_b = (rtb_Gain1_eb + Integrator_p) * 0.100530967F;

  /* Switch: '<S4>/Switch' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S6>/Gain2'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Add'
   */
  if (rtu_flg_PreCtrl > 0.0F) {
    localDW->Switch_b = (1.6E-5F * rtu_id_ref + 0.003) * rtu_w_el;
  } else {
    localDW->Switch_b = 0.0;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Saturate: '<S103>/Saturation' */
  if (rtb_SignPreSat_b > 26.5581131F) {
    localDW->a_U_on = 26.5581131F;
  } else if (rtb_SignPreSat_b < -26.5581131F) {
    localDW->a_U_on = -26.5581131F;
  } else {
    localDW->a_U_on = rtb_SignPreSat_b;
  }

  /* End of Saturate: '<S103>/Saturation' */

  /* Sum: '<S4>/Add1' */
  localDW->Switch_b += localDW->a_U_on;

  /* Switch: '<S4>/Switch3' */
  if (rtu_flg_LimitUdUq > 0.0F) {
    /* Sqrt: '<S9>/Sqrt' incorporates:
     *  Math: '<S9>/Square'
     *  Math: '<S9>/Square1'
     *  Sum: '<S9>/Add'
     */
    localDW->Switch2 = sqrt(rtb_Gain * rtb_Gain - localDW->Switch2 *
      localDW->Switch2);

    /* Switch: '<S114>/Switch2' incorporates:
     *  RelationalOperator: '<S114>/LowerRelop1'
     */
    if (!(localDW->Switch_b > localDW->Switch2)) {
      /* Gain: '<S9>/Gain2' */
      localDW->Switch2 = -localDW->Switch2;

      /* Switch: '<S114>/Switch' incorporates:
       *  RelationalOperator: '<S114>/UpperRelop'
       */
      if (!(localDW->Switch_b < localDW->Switch2)) {
        localDW->Switch2 = localDW->Switch_b;
      }

      /* End of Switch: '<S114>/Switch' */
    }

    /* End of Switch: '<S114>/Switch2' */
    *rty_uq_soll = (real32_T)localDW->Switch2;
  } else {
    *rty_uq_soll = (real32_T)localDW->Switch_b;
  }

  /* End of Switch: '<S4>/Switch3' */

  /* Outputs for Enabled SubSystem: '<S122>/Subsystem1' incorporates:
   *  EnablePort: '<S126>/Enable'
   */
  /* Switch: '<S122>/Switch' incorporates:
   *  Fcn: '<S126>/Fcn'
   *  Fcn: '<S126>/Fcn1'
   */
  rtb_Switch_m_idx_0 = *rty_ud_soll * rtb_Switch_m_idx_1 - *rty_uq_soll *
    localDW->a_W_on;
  rtb_Switch_m_idx_1 = *rty_ud_soll * localDW->a_W_on + *rty_uq_soll *
    rtb_Switch_m_idx_1;

  /* End of Outputs for SubSystem: '<S122>/Subsystem1' */

  /* MATLAB Function: '<S5>/SpaceVectorModulation' */
  /* MATLAB Function 'Basic_FOC/CurrentController/SpaceVectorModulation/SpaceVectorModulation': '<S121>:1' */
  /* '<S121>:1:3' a_U_on= single(0); */
  localDW->a_U_on = 0.0F;

  /* '<S121>:1:4' a_V_on= single(0); */
  rtb_Gain = 0.0F;

  /* '<S121>:1:5' a_W_on= single(0); */
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
  /* '<S121>:1:23' a = single(abs(u_alpha) + 0.5774*abs(u_beta)); */
  a_tmp = fabsf(rtb_Switch_m_idx_0);
  c = fabsf(rtb_Switch_m_idx_1);
  localDW->a = 0.5774F * c + a_tmp;

  /* '<S121>:1:24' b = single(abs(u_alpha) - 0.5774*abs(u_beta)); */
  localDW->b = a_tmp - 0.5774F * fabsf(rtb_Switch_m_idx_1);

  /* '<S121>:1:25' c = single(1.1547*abs(u_beta)); */
  c *= 1.1547F;

  /* '<S121>:1:27' U_max = single(0.6667 * U_ZK); */
  U_max = 0.6667F * rtu_U_IC;

  /* Maximum Voltage U_ZL/sqrt(3) */
  /* Sektor und Quadranten nach Quang Dittrich S32 */
  /* '<S121>:1:31' if(u_beta < 0) */
  if (rtb_Switch_m_idx_1 < 0.0F) {
    /* '<S121>:1:32' if (u_alpha <0) */
    if (rtb_Switch_m_idx_0 < 0.0F) {
      /* '<S121>:1:33' quadrant=3; */
      quadrant = 3;

      /* '<S121>:1:34' if(b < 0) */
      if (localDW->b < 0.0F) {
        /* '<S121>:1:35' sector = 5; */
        sector = 5;
      } else {
        /* '<S121>:1:36' else */
        /* '<S121>:1:37' sector = 4; */
        sector = 4;
      }
    } else {
      /* '<S121>:1:39' else */
      /* '<S121>:1:40' quadrant=4; */
      quadrant = 4;

      /* '<S121>:1:41' if(b < 0) */
      if (localDW->b < 0.0F) {
        /* '<S121>:1:42' sector = 5; */
        sector = 5;
      } else {
        /* '<S121>:1:43' else */
        /* '<S121>:1:44' sector = 6; */
        sector = 6;
      }
    }

    /* '<S121>:1:48' else */
    /* '<S121>:1:49' if (u_alpha <0) */
  } else if (rtb_Switch_m_idx_0 < 0.0F) {
    /* '<S121>:1:50' quadrant=2; */
    quadrant = 2;

    /* '<S121>:1:51' if(b < 0) */
    if (localDW->b < 0.0F) {
      /* '<S121>:1:52' sector = 2; */
      sector = 2;
    } else {
      /* '<S121>:1:53' else */
      /* '<S121>:1:54' sector = 3; */
      sector = 3;
    }
  } else {
    /* '<S121>:1:56' else */
    /* '<S121>:1:57' quadrant=1; */
    quadrant = 1;

    /* '<S121>:1:58' if(b < 0) */
    if (localDW->b < 0.0F) {
      /* '<S121>:1:59' sector = 2; */
      sector = 2;
    } else {
      /* '<S121>:1:60' else */
      /* '<S121>:1:61' sector = 1; */
      sector = 1;
    }
  }

  /* '<S121>:1:66' sector_out = single(sector); */
  /* Modulationsfunktionen f¸r Phasen U,V,W */
  /* Erzeugung der Aussteuergrade f¸r die Halbbr¸cken */
  /* --> Erzeugung einer "regulary Sampled SVM" erfolgt anschlieﬂend durch Abtastung */
  /* mit Dreiecksz‰hlern in Hardware. */
  /* '<S121>:1:73' if (sector_out == 1) */
  if (sector == 1) {
    /* Quang S.24 and normed to 2/3 U_DC */
    /* '<S121>:1:76' u1 = b/(U_max); */
    localDW->a_W_on = localDW->b / U_max;

    /* '<S121>:1:77' u2 = c/(U_max); */
    u2 = c / U_max;

    /* Quang S.34 */
    /* '<S121>:1:80' a_U_on = single(0.5 + u1*0.5 + u2*0.5); */
    localDW->a_U_on = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S121>:1:81' a_V_on = single(0.5 - u1*0.5 + u2*0.5); */
    rtb_Gain = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;

    /* '<S121>:1:82' a_W_on = single(0.5 - u1*0.5 - u2*0.5); */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;
  }

  /* '<S121>:1:86' if ((sector_out == 2) && (quadrant == 1)) */
  if ((sector == 2) && (quadrant == 1)) {
    /* '<S121>:1:88' u1 = a/(U_max); */
    localDW->a_W_on = localDW->a / U_max;

    /* '<S121>:1:89' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    u2 = (0.5774F * fabsf(rtb_Switch_m_idx_1) + -a_tmp) / U_max;

    /* '<S121>:1:91' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->a_U_on = (localDW->a_W_on * 0.5F + 0.5F) - u2 * 0.5F;

    /* '<S121>:1:92' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    rtb_Gain = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S121>:1:93' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;
  }

  /* '<S121>:1:97' if ((sector_out == 2) && (quadrant == 2)) */
  if ((sector == 2) && (quadrant == 2)) {
    /* '<S121>:1:99' u1 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->a_W_on = (0.5774F * fabsf(rtb_Switch_m_idx_1) + -fabsf
                       (rtb_Switch_m_idx_0)) / U_max;

    /* '<S121>:1:100' u2 = a/(U_max); */
    u2 = localDW->a / U_max;

    /* '<S121>:1:102' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->a_U_on = (localDW->a_W_on * 0.5F + 0.5F) - u2 * 0.5F;

    /* '<S121>:1:103' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    rtb_Gain = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S121>:1:104' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;
  }

  /* '<S121>:1:108' if (sector_out == 3) */
  if (sector == 3) {
    /* '<S121>:1:110' u1 = c/(U_max); */
    localDW->a_W_on = c / U_max;

    /* '<S121>:1:111' u2 = b/(U_max); */
    u2 = localDW->b / U_max;

    /* '<S121>:1:113' a_U_on=  0.5 - u1*0.5 - u2*0.5; */
    localDW->a_U_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S121>:1:114' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    rtb_Gain = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S121>:1:115' a_W_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->a_W_on = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;
  }

  /* '<S121>:1:118' if (sector_out == 4) */
  if (sector == 4) {
    /* '<S121>:1:120' u1 = b/(U_max); */
    localDW->a_W_on = localDW->b / U_max;

    /* '<S121>:1:121' u2 = c/(U_max); */
    u2 = c / U_max;

    /* '<S121>:1:123' a_U_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->a_U_on = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S121>:1:124' a_V_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->a_W_on = localDW->a_W_on * 0.5F + 0.5F;
    rtb_Gain = localDW->a_W_on - u2 * 0.5F;

    /* '<S121>:1:125' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_W_on += u2 * 0.5F;
  }

  /* '<S121>:1:129' if ((sector_out == 5) && (quadrant == 3)) */
  if ((sector == 5) && (quadrant == 3)) {
    /* '<S121>:1:131' u1 = a/(U_max); */
    localDW->a_W_on = localDW->a / U_max;

    /* '<S121>:1:132' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    u2 = (0.5774F * fabsf(rtb_Switch_m_idx_1) + -fabsf(rtb_Switch_m_idx_0)) /
      U_max;

    /* '<S121>:1:134' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->a_U_on = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;

    /* '<S121>:1:135' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    rtb_Gain = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S121>:1:136' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_W_on = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;
  }

  /* '<S121>:1:140' if ((sector_out == 5) && (quadrant == 4)) */
  if ((sector == 5) && (quadrant == 4)) {
    /* '<S121>:1:142' u1 =(-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->a_W_on = (0.5774F * fabsf(rtb_Switch_m_idx_1) + -fabsf
                       (rtb_Switch_m_idx_0)) / U_max;

    /* '<S121>:1:143' u2 =  a/(U_max); */
    u2 = localDW->a / U_max;

    /* '<S121>:1:145' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->a_U_on = (0.5F - localDW->a_W_on * 0.5F) + u2 * 0.5F;

    /* '<S121>:1:146' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    rtb_Gain = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S121>:1:147' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_W_on = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;
  }

  /* '<S121>:1:151' if (sector_out == 6) */
  if (sector == 6) {
    /* '<S121>:1:153' u1 = c/(U_max); */
    localDW->a_W_on = c / U_max;

    /* '<S121>:1:154' u2 = b/(U_max); */
    u2 = localDW->b / U_max;

    /* '<S121>:1:156' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->a_U_on = (localDW->a_W_on * 0.5F + 0.5F) + u2 * 0.5F;

    /* '<S121>:1:157' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    rtb_Gain = (0.5F - localDW->a_W_on * 0.5F) - u2 * 0.5F;

    /* '<S121>:1:158' a_W_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->a_W_on = (localDW->a_W_on * 0.5F + 0.5F) - u2 * 0.5F;
  }

  /* '<S121>:1:161' if a_U_on > 1.0 */
  if (localDW->a_U_on > 1.0F) {
    /* '<S121>:1:162' a_U_on = single(1.0); */
    localDW->a_U_on = 1.0F;
  }

  /* '<S121>:1:164' if a_V_on > 1.0 */
  if (rtb_Gain > 1.0F) {
    /* '<S121>:1:165' a_V_on = single(1.0); */
    rtb_Gain = 1.0F;
  }

  /* '<S121>:1:167' if a_W_on > 1.0 */
  if (localDW->a_W_on > 1.0F) {
    /* '<S121>:1:168' a_W_on = single(1.0); */
    localDW->a_W_on = 1.0F;
  }

  /* '<S121>:1:171' u_a = a_U_on; */
  *rty_ua = localDW->a_U_on;

  /* '<S121>:1:172' u_b = a_V_on; */
  *rty_ub = rtb_Gain;

  /* '<S121>:1:173' u_c = a_W_on; */
  *rty_uc = localDW->a_W_on;

  /* End of MATLAB Function: '<S5>/SpaceVectorModulation' */

  /* Gain: '<S87>/ZeroGain' */
  rtb_Gain = 0.0F * rtb_SignPreSat_b;

  /* DeadZone: '<S89>/DeadZone' */
  if (rtb_SignPreSat_b > 26.5581131F) {
    rtb_SignPreSat_b -= 26.5581131F;
  } else if (rtb_SignPreSat_b >= -26.5581131F) {
    rtb_SignPreSat_b = 0.0F;
  } else {
    rtb_SignPreSat_b -= -26.5581131F;
  }

  /* End of DeadZone: '<S89>/DeadZone' */

  /* Gain: '<S93>/Integral Gain' */
  rtb_Gain1_eb *= 2500.0F;

  /* Gain: '<S36>/ZeroGain' */
  localDW->a_U_on = 0.0F * rtb_SignPreSat;

  /* DeadZone: '<S38>/DeadZone' */
  if (rtb_SignPreSat > 26.5581131F) {
    rtb_SignPreSat -= 26.5581131F;
  } else if (rtb_SignPreSat >= -26.5581131F) {
    rtb_SignPreSat = 0.0F;
  } else {
    rtb_SignPreSat -= -26.5581131F;
  }

  /* End of DeadZone: '<S38>/DeadZone' */

  /* Gain: '<S42>/Integral Gain' */
  rtb_IntegralGain *= 2500.0F;

  /* SignalConversion generated from: '<S2>/Id_ist' */
  *rty_Id_ist = rty_Iq_ist[0];

  /* Update for DiscreteIntegrator: '<S45>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 0U;
  localDW->Integrator_DSTATE = Integrator;

  /* Signum: '<S36>/SignPreSat' */
  if (rtb_SignPreSat < 0.0F) {
    rtb_Switch_m_idx_0 = -1.0F;
  } else if (rtb_SignPreSat > 0.0F) {
    rtb_Switch_m_idx_0 = 1.0F;
  } else if (rtb_SignPreSat == 0.0F) {
    rtb_Switch_m_idx_0 = 0.0F;
  } else {
    rtb_Switch_m_idx_0 = (rtNaNF);
  }

  /* End of Signum: '<S36>/SignPreSat' */

  /* Signum: '<S36>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0F) {
    Integrator = -1.0F;
  } else if (rtb_IntegralGain > 0.0F) {
    Integrator = 1.0F;
  } else if (rtb_IntegralGain == 0.0F) {
    Integrator = 0.0F;
  } else {
    Integrator = (rtNaNF);
  }

  /* End of Signum: '<S36>/SignPreIntegrator' */

  /* Switch: '<S36>/Switch' incorporates:
   *  DataTypeConversion: '<S36>/DataTypeConv1'
   *  DataTypeConversion: '<S36>/DataTypeConv2'
   *  Logic: '<S36>/AND3'
   *  RelationalOperator: '<S36>/Equal1'
   *  RelationalOperator: '<S36>/NotEqual'
   */
  if ((localDW->a_U_on != rtb_SignPreSat) && ((int8_T)rtb_Switch_m_idx_0 ==
       (int8_T)Integrator)) {
    /* Update for DiscreteIntegrator: '<S45>/Integrator' incorporates:
     *  Constant: '<S36>/Constant1'
     */
    localDW->Integrator_PREV_U = 0.0F;
  } else {
    /* Update for DiscreteIntegrator: '<S45>/Integrator' */
    localDW->Integrator_PREV_U = rtb_IntegralGain;
  }

  /* End of Switch: '<S36>/Switch' */

  /* Update for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE_a = 0U;
  localDW->Integrator_DSTATE_a = Integrator_p;

  /* Signum: '<S87>/SignPreSat' */
  if (rtb_SignPreSat_b < 0.0F) {
    localDW->a_U_on = -1.0F;
  } else if (rtb_SignPreSat_b > 0.0F) {
    localDW->a_U_on = 1.0F;
  } else if (rtb_SignPreSat_b == 0.0F) {
    localDW->a_U_on = 0.0F;
  } else {
    localDW->a_U_on = (rtNaNF);
  }

  /* End of Signum: '<S87>/SignPreSat' */

  /* Signum: '<S87>/SignPreIntegrator' */
  if (rtb_Gain1_eb < 0.0F) {
    rtb_IntegralGain = -1.0F;
  } else if (rtb_Gain1_eb > 0.0F) {
    rtb_IntegralGain = 1.0F;
  } else if (rtb_Gain1_eb == 0.0F) {
    rtb_IntegralGain = 0.0F;
  } else {
    rtb_IntegralGain = (rtNaNF);
  }

  /* End of Signum: '<S87>/SignPreIntegrator' */

  /* Switch: '<S87>/Switch' incorporates:
   *  DataTypeConversion: '<S87>/DataTypeConv1'
   *  DataTypeConversion: '<S87>/DataTypeConv2'
   *  Logic: '<S87>/AND3'
   *  RelationalOperator: '<S87>/Equal1'
   *  RelationalOperator: '<S87>/NotEqual'
   */
  if ((rtb_Gain != rtb_SignPreSat_b) && ((int8_T)localDW->a_U_on == (int8_T)
       rtb_IntegralGain)) {
    /* Update for DiscreteIntegrator: '<S96>/Integrator' incorporates:
     *  Constant: '<S87>/Constant1'
     */
    localDW->Integrator_PREV_U_f = 0.0F;
  } else {
    /* Update for DiscreteIntegrator: '<S96>/Integrator' */
    localDW->Integrator_PREV_U_f = rtb_Gain1_eb;
  }

  /* End of Switch: '<S87>/Switch' */
}

/* System initialize for function-call system: '<S1>/SpeedController' */
static void SpeedController_Init(DW_SpeedController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S163>/Integrator' */
  localDW->Integrator_PREV_U = 0.0F;
}

/* Enable for function-call system: '<S1>/SpeedController' */
static void SpeedController_Enable(DW_SpeedController *localDW)
{
  localDW->SpeedController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S163>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 1U;
}

/* Output and update for function-call system: '<S1>/SpeedController' */
static void SpeedController(RT_MODEL * const rtM, real32_T rtu_id_ref, real32_T
  rtu_iq_ref, real32_T rtu_n_soll, real32_T rtu_n_ist, real32_T
  rtu_flg_fieldWeakening, real32_T rtu_flg_UseMMPA, real32_T
  rtu_flg_SpeedControl, real32_T *rty_id_soll, real32_T *rty_iq_soll,
  DW_SpeedController *localDW)
{
  real32_T Integrator;
  real32_T rtb_IntegralGain;
  real32_T rtb_IntegralGain_o;
  real32_T rtb_ProportionalGain;
  real32_T rtb_SignPreIntegrator_p;
  uint32_T SpeedController_ELAPS_T;
  if (localDW->SpeedController_RESET_ELAPS_T) {
    SpeedController_ELAPS_T = 0U;
  } else {
    SpeedController_ELAPS_T = rtM->Timing.clockTick0 -
      localDW->SpeedController_PREV_T;
  }

  localDW->SpeedController_PREV_T = rtM->Timing.clockTick0;
  localDW->SpeedController_RESET_ELAPS_T = false;

  /* Switch: '<S127>/Switch' incorporates:
   *  Constant: '<S127>/Constant'
   *  Switch: '<S128>/Switch'
   */
  if (rtu_flg_UseMMPA > 0.0F) {
    *rty_id_soll = 0.0F;
  } else if (rtu_flg_fieldWeakening > 0.0F) {
    /* Switch: '<S128>/Switch' incorporates:
     *  Constant: '<S128>/Constant'
     */
    *rty_id_soll = 0.0F;
  } else {
    *rty_id_soll = rtu_id_ref;
  }

  /* End of Switch: '<S127>/Switch' */

  /* Sum: '<S128>/Sum' */
  rtb_IntegralGain = rtu_n_soll - rtu_n_ist;

  /* DiscreteIntegrator: '<S163>/Integrator' */
  if (localDW->Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S163>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S163>/Integrator' */
    Integrator = 0.0001F * (real32_T)SpeedController_ELAPS_T
      * localDW->Integrator_PREV_U + localDW->Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S163>/Integrator' */

  /* Gain: '<S161>/Proportional Gain' incorporates:
   *  Sum: '<S172>/Sum'
   */
  rtb_ProportionalGain = (rtb_IntegralGain + Integrator) * 2.90111828F;

  /* Switch: '<S127>/Switch1' incorporates:
   *  Constant: '<S127>/Constant'
   *  Switch: '<S128>/Switch1'
   */
  if (rtu_flg_UseMMPA > 0.0F) {
    *rty_iq_soll = 0.0F;
  } else if (rtu_flg_SpeedControl > 0.0F) {
    /* Saturate: '<S170>/Saturation' incorporates:
     *  Switch: '<S128>/Switch1'
     */
    if (rtb_ProportionalGain > 100.0F) {
      *rty_iq_soll = 100.0F;
    } else if (rtb_ProportionalGain < -100.0F) {
      *rty_iq_soll = -100.0F;
    } else {
      *rty_iq_soll = rtb_ProportionalGain;
    }

    /* End of Saturate: '<S170>/Saturation' */
  } else {
    /* Switch: '<S128>/Switch1' */
    *rty_iq_soll = rtu_iq_ref;
  }

  /* End of Switch: '<S127>/Switch1' */

  /* DeadZone: '<S156>/DeadZone' */
  if (rtb_ProportionalGain > 100.0F) {
    rtb_SignPreIntegrator_p = rtb_ProportionalGain - 100.0F;
  } else if (rtb_ProportionalGain >= -100.0F) {
    rtb_SignPreIntegrator_p = 0.0F;
  } else {
    rtb_SignPreIntegrator_p = rtb_ProportionalGain - -100.0F;
  }

  /* End of DeadZone: '<S156>/DeadZone' */

  /* Gain: '<S160>/Integral Gain' */
  rtb_IntegralGain *= 174.532928F;

  /* Update for DiscreteIntegrator: '<S163>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 0U;
  localDW->Integrator_DSTATE = Integrator;

  /* Signum: '<S154>/SignPreSat' */
  if (rtb_SignPreIntegrator_p < 0.0F) {
    Integrator = -1.0F;
  } else if (rtb_SignPreIntegrator_p > 0.0F) {
    Integrator = 1.0F;
  } else if (rtb_SignPreIntegrator_p == 0.0F) {
    Integrator = 0.0F;
  } else {
    Integrator = (rtNaNF);
  }

  /* End of Signum: '<S154>/SignPreSat' */

  /* Signum: '<S154>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0F) {
    rtb_IntegralGain_o = -1.0F;
  } else if (rtb_IntegralGain > 0.0F) {
    rtb_IntegralGain_o = 1.0F;
  } else if (rtb_IntegralGain == 0.0F) {
    rtb_IntegralGain_o = 0.0F;
  } else {
    rtb_IntegralGain_o = (rtNaNF);
  }

  /* End of Signum: '<S154>/SignPreIntegrator' */

  /* Switch: '<S154>/Switch' incorporates:
   *  DataTypeConversion: '<S154>/DataTypeConv1'
   *  DataTypeConversion: '<S154>/DataTypeConv2'
   *  Gain: '<S154>/ZeroGain'
   *  Logic: '<S154>/AND3'
   *  RelationalOperator: '<S154>/Equal1'
   *  RelationalOperator: '<S154>/NotEqual'
   */
  if ((0.0F * rtb_ProportionalGain != rtb_SignPreIntegrator_p) && ((int8_T)
       Integrator == (int8_T)rtb_IntegralGain_o)) {
    /* Update for DiscreteIntegrator: '<S163>/Integrator' incorporates:
     *  Constant: '<S154>/Constant1'
     */
    localDW->Integrator_PREV_U = 0.0F;
  } else {
    /* Update for DiscreteIntegrator: '<S163>/Integrator' */
    localDW->Integrator_PREV_U = rtb_IntegralGain;
  }

  /* End of Switch: '<S154>/Switch' */
}

/* Function for Chart: '<Root>/Basic_FOC' */
static void enter_atomic_SpeedControl(real32_T *id_ref_n, real32_T *iq_ref_o,
  real32_T *n_soll, real32_T *n_ist, real32_T *flg_fieldWeakening, real32_T
  *flg_UseMMPA, ExtU *rtU, ExtY *rtY, RT_MODEL *rtM, DW *rtDW)
{
  /* Inport: '<Root>/id_ref' */
  /* Entry 'SpeedControl': '<S1>:90' */
  /* '<S1>:90:3' [id_soll,iq_soll] = SpeedController(id_ref,iq_ref,n_soll,n_ist,flg_fieldWeakening,flg_UseMMPA,flg_SpeedControl) */
  /* Simulink Function 'SpeedController': '<S1>:62' */
  *id_ref_n = rtU->id_ref;

  /* Inport: '<Root>/iq_ref' */
  *iq_ref_o = rtU->iq_ref;

  /* Inport: '<Root>/n_soll' */
  *n_soll = rtU->n_soll;

  /* Inport: '<Root>/n_ist' */
  *n_ist = rtU->n_ist;

  /* Inport: '<Root>/flg_fieldWeakening' */
  *flg_fieldWeakening = rtU->flg_fieldWeakening;

  /* Inport: '<Root>/flg_UseMMPA' */
  *flg_UseMMPA = rtU->flg_UseMMPA;

  /* Inport: '<Root>/flg_SpeedControl' */
  rtDW->flg_SpeedControl = rtU->flg_SpeedControl;

  /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
  SpeedController(rtM, *id_ref_n, *iq_ref_o, *n_soll, *n_ist,
                  *flg_fieldWeakening, *flg_UseMMPA, rtDW->flg_SpeedControl,
                  &rtDW->Switch, &rtDW->Switch1, &rtDW->SpeedController_c);

  /* End of Outputs for SubSystem: '<S1>/SpeedController' */
  rtDW->id_soll = rtDW->Switch;
  rtDW->iq_soll = rtDW->Switch1;

  /* Inport: '<Root>/ia' */
  /* '<S1>:90:4' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
  /* Simulink Function 'CurrentController': '<S1>:72' */
  rtDW->ia = rtU->ia;

  /* Inport: '<Root>/ib' */
  rtDW->ib = rtU->ib;

  /* Inport: '<Root>/ic' */
  rtDW->ic = rtU->ic;

  /* Inport: '<Root>/w_el' */
  rtDW->w_el = rtU->w_el;

  /* Inport: '<Root>/flg_PreCntr' */
  rtDW->flg_PreCtrl = rtU->flg_PreCntr;

  /* Inport: '<Root>/theta_el' */
  rtDW->theta_el = rtU->theta_el;

  /* Inport: '<Root>/U_IC' */
  rtDW->U_IC = rtU->U_IC;
  rtDW->id_ref = rtDW->id_soll;
  rtDW->iq_ref = rtDW->iq_soll;

  /* Inport: '<Root>/flgLimitUdUq' */
  rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

  /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
  CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                    rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC, rtDW->id_ref,
                    rtDW->iq_ref, rtDW->flg_LimitUdUq, &rtDW->u_a, &rtDW->u_b,
                    &rtDW->u_c, rtDW->Switch_h, &rtDW->OutportBufferForId_ist,
                    &rtDW->Switch2, &rtDW->Switch3, &rtDW->CurrentController_i);

  /* End of Outputs for SubSystem: '<S1>/CurrentController' */

  /* Outport: '<Root>/Ua_DutyCycle' */
  rtY->Ua_DutyCycle = rtDW->u_a;

  /* Outport: '<Root>/Ub_DutyCycle' */
  rtY->Ub_DutyCycle = rtDW->u_b;

  /* Outport: '<Root>/Uc_DutyCycle' */
  rtY->Uc_DutyCycle = rtDW->u_c;

  /* Outport: '<Root>/iq_ist' */
  rtY->iq_ist = rtDW->Switch_h[1];

  /* Outport: '<Root>/id_ist' */
  rtY->id_ist = rtDW->OutportBufferForId_ist;

  /* Outport: '<Root>/ud' */
  rtY->ud = rtDW->Switch2;

  /* Outport: '<Root>/uq' */
  rtY->uq = rtDW->Switch3;

  /* '<S1>:90:5' cnt_CurrentCtrl = 1 */
  rtDW->cnt_CurrentCtrl = 1.0F;
}

/* Model step function */
void Basic_FOC_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Chart: '<Root>/Basic_FOC' incorporates:
   *  Inport: '<Root>/RESET'
   *  Inport: '<Root>/START'
   *  Inport: '<Root>/T_controller'
   *  Inport: '<Root>/T_speedController'
   *  Inport: '<Root>/U_IC'
   *  Inport: '<Root>/flgLimitUdUq'
   *  Inport: '<Root>/flg_PreCntr'
   *  Inport: '<Root>/flg_SpeedControl'
   *  Inport: '<Root>/flg_UseMMPA'
   *  Inport: '<Root>/flg_fieldWeakening'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Inport: '<Root>/id_ref'
   *  Inport: '<Root>/iq_ref'
   *  Inport: '<Root>/n_ist'
   *  Inport: '<Root>/n_soll'
   *  Inport: '<Root>/theta_el'
   *  Inport: '<Root>/w_el'
   */
  /* Gateway: Basic_FOC */
  /* During: Basic_FOC */
  if (rtDW->is_active_c3_Basic_FOC == 0U) {
    /* Entry: Basic_FOC */
    rtDW->is_active_c3_Basic_FOC = 1U;

    /* Entry Internal: Basic_FOC */
    /* Transition: '<S1>:2' */
    rtDW->is_c3_Basic_FOC = IN_Start;

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
  } else if (rtDW->is_c3_Basic_FOC == IN_InProcess) {
    /* Outport: '<Root>/activeState' */
    rtY->activeState = 2.0F;

    /* During 'InProcess': '<S1>:3' */
    /* '<S1>:18:1' sf_internal_predicateOutput = RESET==1; */
    if (rtU->RESET == 1.0F) {
      /* Transition: '<S1>:18' */
      /* Exit Internal 'InProcess': '<S1>:3' */
      rtDW->is_InProcess = IN_NO_ACTIVE_CHILD;
      rtDW->is_c3_Basic_FOC = IN_Start;

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
    } else if (rtDW->is_InProcess == IN_CurrentControl) {
      /* During 'CurrentControl': '<S1>:91' */
      /* '<S1>:102:1' sf_internal_predicateOutput = cnt_CurrentCtrl >= rat_freq; */
      if (rtDW->cnt_CurrentCtrl >= rtDW->rat_freq) {
        /* Transition: '<S1>:102' */
        rtDW->is_InProcess = IN_SpeedControl;
        enter_atomic_SpeedControl(&rtDW->id_ref_n, &rtDW->iq_ref_o,
          &rtDW->n_soll, &rtDW->n_ist, &rtDW->flg_fieldWeakening,
          &rtDW->flg_UseMMPA, rtU, rtY, rtM, rtDW);
      } else {
        /* '<S1>:91:6' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
        /* Simulink Function 'CurrentController': '<S1>:72' */
        rtDW->ia = rtU->ia;
        rtDW->ib = rtU->ib;
        rtDW->ic = rtU->ic;
        rtDW->w_el = rtU->w_el;
        rtDW->flg_PreCtrl = rtU->flg_PreCntr;
        rtDW->theta_el = rtU->theta_el;
        rtDW->U_IC = rtU->U_IC;
        rtDW->id_ref = rtDW->id_soll;
        rtDW->iq_ref = rtDW->iq_soll;
        rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

        /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
        CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                          rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC,
                          rtDW->id_ref, rtDW->iq_ref, rtDW->flg_LimitUdUq,
                          &rtDW->u_a, &rtDW->u_b, &rtDW->u_c, rtDW->Switch_h,
                          &rtDW->OutportBufferForId_ist, &rtDW->Switch2,
                          &rtDW->Switch3, &rtDW->CurrentController_i);

        /* End of Outputs for SubSystem: '<S1>/CurrentController' */

        /* Outport: '<Root>/Ua_DutyCycle' incorporates:
         *  Inport: '<Root>/U_IC'
         *  Inport: '<Root>/flgLimitUdUq'
         *  Inport: '<Root>/flg_PreCntr'
         *  Inport: '<Root>/ia'
         *  Inport: '<Root>/ib'
         *  Inport: '<Root>/ic'
         *  Inport: '<Root>/theta_el'
         *  Inport: '<Root>/w_el'
         */
        rtY->Ua_DutyCycle = rtDW->u_a;

        /* Outport: '<Root>/Ub_DutyCycle' */
        rtY->Ub_DutyCycle = rtDW->u_b;

        /* Outport: '<Root>/Uc_DutyCycle' */
        rtY->Uc_DutyCycle = rtDW->u_c;

        /* Outport: '<Root>/iq_ist' */
        rtY->iq_ist = rtDW->Switch_h[1];

        /* Outport: '<Root>/id_ist' */
        rtY->id_ist = rtDW->OutportBufferForId_ist;

        /* Outport: '<Root>/ud' */
        rtY->ud = rtDW->Switch2;

        /* Outport: '<Root>/uq' */
        rtY->uq = rtDW->Switch3;

        /* '<S1>:91:7' cnt_CurrentCtrl = cnt_CurrentCtrl +1; */
        rtDW->cnt_CurrentCtrl++;
      }

      /* During 'SpeedControl': '<S1>:90' */
      /* '<S1>:100:1' sf_internal_predicateOutput = rat_freq > 1; */
    } else if (rtDW->rat_freq > 1.0F) {
      /* Transition: '<S1>:100' */
      rtDW->is_InProcess = IN_CurrentControl;

      /* Entry 'CurrentControl': '<S1>:91' */
      /* '<S1>:91:3' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
      /* Simulink Function 'CurrentController': '<S1>:72' */
      rtDW->ia = rtU->ia;
      rtDW->ib = rtU->ib;
      rtDW->ic = rtU->ic;
      rtDW->w_el = rtU->w_el;
      rtDW->flg_PreCtrl = rtU->flg_PreCntr;
      rtDW->theta_el = rtU->theta_el;
      rtDW->U_IC = rtU->U_IC;
      rtDW->id_ref = rtDW->id_soll;
      rtDW->iq_ref = rtDW->iq_soll;
      rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

      /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
      CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                        rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC,
                        rtDW->id_ref, rtDW->iq_ref, rtDW->flg_LimitUdUq,
                        &rtDW->u_a, &rtDW->u_b, &rtDW->u_c, rtDW->Switch_h,
                        &rtDW->OutportBufferForId_ist, &rtDW->Switch2,
                        &rtDW->Switch3, &rtDW->CurrentController_i);

      /* End of Outputs for SubSystem: '<S1>/CurrentController' */

      /* Outport: '<Root>/Ua_DutyCycle' incorporates:
       *  Inport: '<Root>/U_IC'
       *  Inport: '<Root>/flgLimitUdUq'
       *  Inport: '<Root>/flg_PreCntr'
       *  Inport: '<Root>/ia'
       *  Inport: '<Root>/ib'
       *  Inport: '<Root>/ic'
       *  Inport: '<Root>/theta_el'
       *  Inport: '<Root>/w_el'
       */
      rtY->Ua_DutyCycle = rtDW->u_a;

      /* Outport: '<Root>/Ub_DutyCycle' */
      rtY->Ub_DutyCycle = rtDW->u_b;

      /* Outport: '<Root>/Uc_DutyCycle' */
      rtY->Uc_DutyCycle = rtDW->u_c;

      /* Outport: '<Root>/iq_ist' */
      rtY->iq_ist = rtDW->Switch_h[1];

      /* Outport: '<Root>/id_ist' */
      rtY->id_ist = rtDW->OutportBufferForId_ist;

      /* Outport: '<Root>/ud' */
      rtY->ud = rtDW->Switch2;

      /* Outport: '<Root>/uq' */
      rtY->uq = rtDW->Switch3;

      /* '<S1>:91:4' cnt_CurrentCtrl = cnt_CurrentCtrl +1; */
      rtDW->cnt_CurrentCtrl++;
    } else {
      /* '<S1>:90:7' [id_soll,iq_soll] = SpeedController(id_ref,iq_ref,n_soll,n_ist,flg_fieldWeakening,flg_UseMMPA,flg_SpeedControl) */
      /* Simulink Function 'SpeedController': '<S1>:62' */
      rtDW->flg_SpeedControl = rtU->flg_SpeedControl;

      /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
      SpeedController(rtM, rtU->id_ref, rtU->iq_ref, rtU->n_soll, rtU->n_ist,
                      rtU->flg_fieldWeakening, rtU->flg_UseMMPA,
                      rtDW->flg_SpeedControl, &rtDW->Switch, &rtDW->Switch1,
                      &rtDW->SpeedController_c);

      /* End of Outputs for SubSystem: '<S1>/SpeedController' */
      rtDW->id_soll = rtDW->Switch;
      rtDW->iq_soll = rtDW->Switch1;

      /* '<S1>:90:8' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
      /* Simulink Function 'CurrentController': '<S1>:72' */
      rtDW->ia = rtU->ia;
      rtDW->ib = rtU->ib;
      rtDW->ic = rtU->ic;
      rtDW->w_el = rtU->w_el;
      rtDW->flg_PreCtrl = rtU->flg_PreCntr;
      rtDW->theta_el = rtU->theta_el;
      rtDW->U_IC = rtU->U_IC;
      rtDW->id_ref = rtDW->id_soll;
      rtDW->iq_ref = rtDW->iq_soll;
      rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

      /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
      CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                        rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC,
                        rtDW->id_ref, rtDW->iq_ref, rtDW->flg_LimitUdUq,
                        &rtDW->u_a, &rtDW->u_b, &rtDW->u_c, rtDW->Switch_h,
                        &rtDW->OutportBufferForId_ist, &rtDW->Switch2,
                        &rtDW->Switch3, &rtDW->CurrentController_i);

      /* End of Outputs for SubSystem: '<S1>/CurrentController' */

      /* Outport: '<Root>/Ua_DutyCycle' incorporates:
       *  Inport: '<Root>/U_IC'
       *  Inport: '<Root>/flgLimitUdUq'
       *  Inport: '<Root>/flg_PreCntr'
       *  Inport: '<Root>/flg_SpeedControl'
       *  Inport: '<Root>/flg_UseMMPA'
       *  Inport: '<Root>/flg_fieldWeakening'
       *  Inport: '<Root>/ia'
       *  Inport: '<Root>/ib'
       *  Inport: '<Root>/ic'
       *  Inport: '<Root>/id_ref'
       *  Inport: '<Root>/iq_ref'
       *  Inport: '<Root>/n_ist'
       *  Inport: '<Root>/n_soll'
       *  Inport: '<Root>/theta_el'
       *  Inport: '<Root>/w_el'
       */
      rtY->Ua_DutyCycle = rtDW->u_a;

      /* Outport: '<Root>/Ub_DutyCycle' */
      rtY->Ub_DutyCycle = rtDW->u_b;

      /* Outport: '<Root>/Uc_DutyCycle' */
      rtY->Uc_DutyCycle = rtDW->u_c;

      /* Outport: '<Root>/iq_ist' */
      rtY->iq_ist = rtDW->Switch_h[1];

      /* Outport: '<Root>/id_ist' */
      rtY->id_ist = rtDW->OutportBufferForId_ist;

      /* Outport: '<Root>/ud' */
      rtY->ud = rtDW->Switch2;

      /* Outport: '<Root>/uq' */
      rtY->uq = rtDW->Switch3;
    }
  } else {
    /* Outport: '<Root>/activeState' */
    rtY->activeState = 1.0F;

    /* During 'Start': '<S1>:1' */
    /* '<S1>:17:1' sf_internal_predicateOutput = START==1 & RESET==0; */
    if ((rtU->START == 1.0F) && (rtU->RESET == 0.0F)) {
      /* Transition: '<S1>:17' */
      rtDW->is_c3_Basic_FOC = IN_InProcess;

      /* Outport: '<Root>/activeState' */
      /* Entry 'InProcess': '<S1>:3' */
      /* '<S1>:3:3' activeState = 2; */
      rtY->activeState = 2.0F;

      /* '<S1>:3:4' id_soll = 0; */
      /* '<S1>:3:5' iq_soll = 0; */
      /* '<S1>:3:6' rat_freq = T_speedController/T_controller; */
      rtDW->rat_freq = rtU->T_speedController / rtU->T_controller;

      /* Entry Internal 'InProcess': '<S1>:3' */
      /* Transition: '<S1>:101' */
      rtDW->is_InProcess = IN_SpeedControl;
      enter_atomic_SpeedControl(&rtDW->id_ref_n, &rtDW->iq_ref_o, &rtDW->n_soll,
        &rtDW->n_ist, &rtDW->flg_fieldWeakening, &rtDW->flg_UseMMPA, rtU, rtY,
        rtM, rtDW);
    }
  }

  /* End of Chart: '<Root>/Basic_FOC' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.0001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rtM->Timing.clockTick0++;
}

/* Model initialize function */
void Basic_FOC_initialize(RT_MODEL *const rtM)
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
  rtDW->is_InProcess = IN_NO_ACTIVE_CHILD;
  rtDW->is_active_c3_Basic_FOC = 0U;
  rtDW->is_c3_Basic_FOC = IN_NO_ACTIVE_CHILD;
  rtDW->id_soll = 0.0F;
  rtDW->iq_soll = 0.0F;
  rtDW->rat_freq = 0.0F;
  rtDW->cnt_CurrentCtrl = 0.0F;

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

  /* SystemInitialize for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Init(&rtDW->CurrentController_i);

  /* SystemInitialize for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  SpeedController_Init(&rtDW->SpeedController_c);

  /* Enable for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Enable(&rtDW->CurrentController_i);

  /* Enable for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  SpeedController_Enable(&rtDW->SpeedController_c);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
