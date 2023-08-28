/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonant_Controller.c
 *
 * Code generated for Simulink model 'Resonant_Controller'.
 *
 * Model version                  : 6.2
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Aug 28 14:01:48 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (3), Error (0)
 */

#include "Resonant_Controller.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>
#include <stddef.h>
#define NumBitsPerChar                 8U
#define NOT_USING_NONFINITE_LITERALS   1

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
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

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

/* Model step function */
void Resonant_Controller_step(RT_MODEL_Resonant_Controller_T *const
  Resonant_Controller_M)
{
  DW_Resonant_Controller_T *Resonant_Controller_DW =
    Resonant_Controller_M->dwork;
  ExtU_Resonant_Controller_T *Resonant_Controller_U =
    (ExtU_Resonant_Controller_T *) Resonant_Controller_M->inputs;
  ExtY_Resonant_Controller_T *Resonant_Controller_Y =
    (ExtY_Resonant_Controller_T *) Resonant_Controller_M->outputs;
  real32_T rtb_Cos;
  real32_T rtb_Cos1;
  real32_T rtb_Product2;

  /* Product: '<S1>/Product' incorporates:
   *  Product: '<S1>/Product3'
   */
  rtb_Cos = Resonant_Controller_U->omega_el * Resonant_Controller_U->h *
    Resonant_Controller_U->T_sw;

  /* Trigonometry: '<S1>/Cos1' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtb_Cos1 = cosf(2.0F * rtb_Cos);

  /* Delay: '<S1>/Delay' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   */
  if (Resonant_Controller_U->Reset != 0.0F) {
    Resonant_Controller_DW->Delay_DSTATE = 0.0F;
    Resonant_Controller_DW->Delay3_DSTATE = 0.0F;
    Resonant_Controller_DW->Delay1_DSTATE = 0.0F;
    Resonant_Controller_DW->Delay2_DSTATE = 0.0F;
  }

  /* Product: '<S1>/Product2' incorporates:
   *  Delay: '<S1>/Delay'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product4'
   *  Sum: '<S1>/Subtract'
   *  Sum: '<S1>/Sum'
   */
  rtb_Product2 = ((Resonant_Controller_U->in_ref - Resonant_Controller_U->in_m)
                  - Resonant_Controller_U->Klim *
                  Resonant_Controller_DW->Delay_DSTATE) *
    Resonant_Controller_U->VR * Resonant_Controller_U->T_sw;

  /* Trigonometry: '<S1>/Cos' */
  rtb_Cos = cosf(rtb_Cos);

  /* Sum: '<S1>/Sum2' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Product: '<S1>/-a1'
   *  Product: '<S1>/b0'
   *  Product: '<S1>/b1'
   *  Sum: '<S1>/Sum3'
   */
  rtb_Cos = ((-rtb_Cos * Resonant_Controller_DW->Delay3_DSTATE -
              Resonant_Controller_DW->Delay1_DSTATE) + 2.0F * rtb_Cos *
             Resonant_Controller_DW->Delay2_DSTATE) + rtb_Cos1 * rtb_Product2;

  /* MATLAB Function: '<S1>/saturation' */
  /* MATLAB Function 'Resonant_Controller/saturation': '<S2>:1' */
  /* '<S2>:1:3' output = input; */
  rtb_Cos1 = rtb_Cos;

  /* '<S2>:1:5' if (input > upper_limit) */
  if (rtb_Cos > Resonant_Controller_U->upper_limit) {
    /* '<S2>:1:6' output = upper_limit; */
    rtb_Cos1 = Resonant_Controller_U->upper_limit;
  }

  /* '<S2>:1:9' if (input < lower_limit) */
  if (rtb_Cos < Resonant_Controller_U->lower_limit) {
    /* '<S2>:1:10' output = lower_limit; */
    rtb_Cos1 = Resonant_Controller_U->lower_limit;
  }

  /* '<S2>:1:13' if isnan(output) */
  if (rtIsNaNF(rtb_Cos1)) {
    /* '<S2>:1:14' output = single(0.0); */
    rtb_Cos1 = 0.0F;
  }

  /* End of MATLAB Function: '<S1>/saturation' */

  /* Outport: '<Root>/out' */
  Resonant_Controller_Y->out = rtb_Cos1;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  Sum: '<S1>/Sum1'
   */
  Resonant_Controller_DW->Delay_DSTATE = rtb_Cos - rtb_Cos1;

  /* Update for Delay: '<S1>/Delay3' */
  Resonant_Controller_DW->Delay3_DSTATE = rtb_Product2;

  /* Update for Delay: '<S1>/Delay1' incorporates:
   *  Delay: '<S1>/Delay2'
   */
  Resonant_Controller_DW->Delay1_DSTATE = Resonant_Controller_DW->Delay2_DSTATE;

  /* Update for Delay: '<S1>/Delay2' */
  Resonant_Controller_DW->Delay2_DSTATE = rtb_Cos;
}

/* Model initialize function */
void Resonant_Controller_initialize(RT_MODEL_Resonant_Controller_T *const
  Resonant_Controller_M)
{
  DW_Resonant_Controller_T *Resonant_Controller_DW =
    Resonant_Controller_M->dwork;
  ExtU_Resonant_Controller_T *Resonant_Controller_U =
    (ExtU_Resonant_Controller_T *) Resonant_Controller_M->inputs;
  ExtY_Resonant_Controller_T *Resonant_Controller_Y =
    (ExtY_Resonant_Controller_T *) Resonant_Controller_M->outputs;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* states (dwork) */
  (void) memset((void *)Resonant_Controller_DW, 0,
                sizeof(DW_Resonant_Controller_T));

  /* external inputs */
  (void)memset(Resonant_Controller_U, 0, sizeof(ExtU_Resonant_Controller_T));

  /* external outputs */
  Resonant_Controller_Y->out = 0.0F;

  /* InitializeConditions for Delay: '<S1>/Delay' */
  Resonant_Controller_DW->Delay_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  Resonant_Controller_DW->Delay3_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  Resonant_Controller_DW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S1>/Delay2' */
  Resonant_Controller_DW->Delay2_DSTATE = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
