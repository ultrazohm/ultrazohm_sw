/*
 * gm_uz_park_transformation.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "gm_uz_park_transformation".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu Aug 11 11:20:48 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "gm_uz_park_transformation.h"
#include "gm_uz_park_transformation_private.h"

/* Block signals (default storage) */
B_gm_uz_park_transformation_T gm_uz_park_transformation_B;

/* Block states (default storage) */
DW_gm_uz_park_transformation_T gm_uz_park_transformation_DW;

/* Real-time model */
static RT_MODEL_gm_uz_park_transform_T gm_uz_park_transformation_M_;
RT_MODEL_gm_uz_park_transform_T *const gm_uz_park_transformation_M =
  &gm_uz_park_transformation_M_;
static void rate_scheduler(void);
uint32_T plook_u32u16_bincka(uint16_T u, const uint16_T bp[], uint32_T maxIndex)
{
  uint32_T bpIndex;

  /* Prelookup - Index only
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U]) {
    bpIndex = 0U;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32u16(u, bp, maxIndex >> 1U, maxIndex);
  } else {
    bpIndex = maxIndex;
  }

  return bpIndex;
}

uint32_T binsearch_u32u16(uint16_T u, const uint16_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIdx;
  uint32_T bpIndex;
  uint32_T iRght;

  /* Binary Search */
  bpIdx = startIndex;
  bpIndex = 0U;
  iRght = maxIndex;
  while (iRght - bpIndex > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      bpIndex = bpIdx;
    }

    bpIdx = (iRght + bpIndex) >> 1U;
  }

  return bpIndex;
}

void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Hi;
  uint32_T in0Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
  in0Hi = absIn0 >> 16U;
  in0Lo = absIn0 & 65535U;
  in1Hi = absIn1 >> 16U;
  absIn0 = absIn1 & 65535U;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0U;
  in0Lo = (productLoHi << 16U) + absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1U;
  }

  absIn0 = in0Lo;
  in0Lo += productHiLo << 16U;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    absIn1;
  if ((in0 != 0) && ((in1 != 0) && ((in0 > 0) != (in1 > 0)))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_loSR(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  u32_clo = u32_chi << (32U - aShift) | u32_clo >> aShift;
  return (int32_T)u32_clo;
}

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (gm_uz_park_transformation_M->Timing.TaskCounters.TID[2])++;
  if ((gm_uz_park_transformation_M->Timing.TaskCounters.TID[2]) > 49) {/* Sample time: [5.0E-7s, 0.0s] */
    gm_uz_park_transformation_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/* Model step function */
void gm_uz_park_transformation_step(void)
{
  /* local block i/o variables */
  int32_T rtb_Switch;
  int32_T rtb_Switch1;
  int32_T rtb_Add;
  int32_T rtb_Add1;
  int32_T rtb_Switch2;
  int32_T rtb_LookUpTable;
  int32_T rtb_LookUpTable1;
  int32_T rtb_Switch3;
  uint8_T rtb_dtc;
  boolean_T rtb_Delay13;
  boolean_T rtb_Compare;
  boolean_T rtb_FixPtRelationalOperator;
  boolean_T rtb_LTEp501;
  boolean_T rtb_DataTypeConversion5;
  real_T rtb_PulseGenerator;
  real_T tmp_0;
  int32_T rtb_Delay8;
  int32_T rtb_Delay9;
  int32_T rtb_Divide2;
  int32_T rtb_Divide3;
  int32_T rtb_QuadHandle1;
  int32_T rtb_QuadHandle1b;
  int32_T tmp;
  uint32_T rtb_LTEp50_tmp_tmp;
  uint16_T rtb_CastU16En2;
  uint16_T rtb_CastU16En31;
  uint16_T rtb_Switch1_n;
  boolean_T rtb_LTEp251;
  boolean_T rtb_LTEp50;

  /* Sin: '<Root>/Sine Wave' incorporates:
   *  Sin: '<Root>/Sine Wave1'
   */
  rtb_PulseGenerator = 1884.9555921538758 *
    gm_uz_park_transformation_M->Timing.t[0];

  /* Sin: '<Root>/Sine Wave' */
  gm_uz_park_transformation_B.SineWave = sin(rtb_PulseGenerator + 0.0) * 1.0 +
    0.0;

  /* RateTransition: '<Root>/Rate Transition' */
  gm_uz_park_transformation_B.RateTransition =
    gm_uz_park_transformation_B.SineWave;

  /* DataTypeConversion: '<Root>/Data Type Conversion' */
  tmp_0 = floor(gm_uz_park_transformation_B.RateTransition * 1.6777216E+7);
  if (rtIsNaN(tmp_0) || rtIsInf(tmp_0)) {
    tmp_0 = 0.0;
  } else {
    tmp_0 = fmod(tmp_0, 1.34217728E+8);
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion' */
  gm_uz_park_transformation_B.DataTypeConversion = ((int32_T)tmp_0 & 67108864U)
    != 0U ? (int32_T)tmp_0 | -67108864 : (int32_T)tmp_0 & 67108863;

  /* Sin: '<Root>/Sine Wave1' */
  gm_uz_park_transformation_B.SineWave1 = sin(rtb_PulseGenerator +
    (-1.5707963267948966)) * 1.0 + 0.0;

  /* RateTransition: '<Root>/Rate Transition1' */
  gm_uz_park_transformation_B.RateTransition1 =
    gm_uz_park_transformation_B.SineWave1;

  /* DataTypeConversion: '<Root>/Data Type Conversion2' */
  tmp_0 = floor(gm_uz_park_transformation_B.RateTransition1 * 1.6777216E+7);
  if (rtIsNaN(tmp_0) || rtIsInf(tmp_0)) {
    tmp_0 = 0.0;
  } else {
    tmp_0 = fmod(tmp_0, 1.34217728E+8);
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion2' */
  gm_uz_park_transformation_B.DataTypeConversion2 = ((int32_T)tmp_0 & 67108864U)
    != 0U ? (int32_T)tmp_0 | -67108864 : (int32_T)tmp_0 & 67108863;

  /* Outputs for Atomic SubSystem: '<Root>/uz_park_transformation' */
  /* DataTypeConversion: '<S9>/Positive' incorporates:
   *  Delay: '<S9>/PipelineRegister'
   *  Product: '<S1>/Divide2'
   */
  rtb_Divide2 = gm_uz_park_transformation_DW.PipelineRegister_DSTATE;

  /* Switch: '<S9>/SignCorrected' incorporates:
   *  Delay: '<S9>/PipelineRegister'
   *  Delay: '<S9>/delayMatch1'
   *  Product: '<S1>/Divide2'
   *  UnaryMinus: '<S9>/Negate'
   */
  if (gm_uz_park_transformation_DW.delayMatch1_DSTATE_i == 0) {
    rtb_Divide2 = (-gm_uz_park_transformation_DW.PipelineRegister_DSTATE &
                   131072U) != 0U ?
      -gm_uz_park_transformation_DW.PipelineRegister_DSTATE | -131072 :
      -gm_uz_park_transformation_DW.PipelineRegister_DSTATE & 131071;
  }

  /* End of Switch: '<S9>/SignCorrected' */

  /* DataTypeConversion: '<S9>/Positive1' incorporates:
   *  Delay: '<S9>/PipelineRegister1'
   *  Switch: '<S9>/QuadHandle1b'
   */
  rtb_QuadHandle1b = gm_uz_park_transformation_DW.PipelineRegister1_DSTATE;

  /* Switch: '<S9>/SignCorrected1' incorporates:
   *  Delay: '<S9>/PipelineRegister1'
   *  Delay: '<S9>/delayMatch'
   *  Switch: '<S9>/QuadHandle1b'
   *  UnaryMinus: '<S9>/Negate1'
   */
  if (!gm_uz_park_transformation_DW.delayMatch_DSTATE_d) {
    rtb_QuadHandle1b = (-gm_uz_park_transformation_DW.PipelineRegister1_DSTATE &
                        131072U) != 0U ?
      -gm_uz_park_transformation_DW.PipelineRegister1_DSTATE | -131072 :
      -gm_uz_park_transformation_DW.PipelineRegister1_DSTATE & 131071;
  }

  /* End of Switch: '<S9>/SignCorrected1' */

  /* Product: '<S1>/Divide1' incorporates:
   *  Delay: '<S1>/delayMatch1'
   *  Switch: '<S9>/QuadHandle1b'
   */
  tmp = mul_s32_loSR(rtb_QuadHandle1b,
                     gm_uz_park_transformation_DW.delayMatch1_DSTATE, 24U);

  /* Product: '<S1>/Divide' incorporates:
   *  Delay: '<S1>/delayMatch'
   *  Product: '<S1>/Divide2'
   */
  rtb_Divide3 = mul_s32_loSR(rtb_Divide2,
    gm_uz_park_transformation_DW.delayMatch_DSTATE, 24U);

  /* Sum: '<S1>/Add' incorporates:
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Divide1'
   */
  tmp = ((rtb_Divide3 & 67108864U) != 0U ? rtb_Divide3 | -67108864 : rtb_Divide3
         & 67108863) + ((tmp & 67108864U) != 0U ? tmp | -67108864 : tmp &
                        67108863);
  tmp = (tmp & 134217728U) != 0U ? tmp | -134217728 : tmp & 134217727;

  /* Sum: '<S1>/Add' */
  rtb_Add = (tmp & 67108864U) != 0U ? tmp | -67108864 : tmp & 67108863;

  /* Product: '<S1>/Divide3' incorporates:
   *  Delay: '<S1>/delayMatch2'
   *  Product: '<S1>/Divide2'
   */
  tmp = mul_s32_loSR(rtb_Divide2,
                     gm_uz_park_transformation_DW.delayMatch2_DSTATE, 24U);
  rtb_Divide3 = (tmp & 67108864U) != 0U ? tmp | -67108864 : tmp & 67108863;

  /* Product: '<S1>/Divide2' incorporates:
   *  Delay: '<S1>/delayMatch3'
   *  Switch: '<S9>/QuadHandle1b'
   */
  tmp = mul_s32_loSR(rtb_QuadHandle1b,
                     gm_uz_park_transformation_DW.delayMatch3_DSTATE, 24U);
  rtb_Divide2 = (tmp & 67108864U) != 0U ? tmp | -67108864 : tmp & 67108863;

  /* Sum: '<S1>/Add1' incorporates:
   *  Product: '<S1>/Divide2'
   *  Product: '<S1>/Divide3'
   */
  tmp = rtb_Divide3 - rtb_Divide2;
  tmp = (tmp & 134217728U) != 0U ? tmp | -134217728 : tmp & 134217727;

  /* Sum: '<S1>/Add1' */
  rtb_Add1 = (tmp & 67108864U) != 0U ? tmp | -67108864 : tmp & 67108863;

  /* Delay: '<S1>/Delay10' */
  rtb_Divide2 = gm_uz_park_transformation_DW.Delay10_DSTATE;

  /* Delay: '<S1>/Delay13' */
  rtb_Delay13 = gm_uz_park_transformation_DW.Delay13_DSTATE;

  /* Delay: '<S1>/Delay7' */
  rtb_Divide3 = gm_uz_park_transformation_DW.Delay7_DSTATE;

  /* Delay: '<S1>/Delay8' */
  rtb_Delay8 = gm_uz_park_transformation_DW.Delay8_DSTATE;

  /* Delay: '<S1>/Delay9' */
  rtb_Delay9 = gm_uz_park_transformation_DW.Delay9_DSTATE;

  /* RelationalOperator: '<S10>/Compare' incorporates:
   *  Constant: '<S10>/Constant'
   *  Delay: '<S1>/Delay3'
   */
  rtb_Compare = ((int32_T)gm_uz_park_transformation_DW.Delay3_DSTATE > (int32_T)
                 false);

  /* RelationalOperator: '<S2>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S2>/Delay Input1'
   */
  rtb_FixPtRelationalOperator = ((int32_T)rtb_Compare > (int32_T)
    gm_uz_park_transformation_DW.DelayInput1_DSTATE);

  /* Switch: '<S1>/Switch3' incorporates:
   *  Switch: '<S1>/Switch2'
   */
  if (rtb_FixPtRelationalOperator) {
    /* Switch: '<S1>/Switch3' incorporates:
     *  Delay: '<S1>/Delay11'
     */
    rtb_Switch3 = gm_uz_park_transformation_DW.Delay11_DSTATE;

    /* Switch: '<S1>/Switch2' incorporates:
     *  Delay: '<S1>/Delay2'
     */
    rtb_Switch2 = gm_uz_park_transformation_DW.Delay2_DSTATE;
  } else {
    /* Switch: '<S1>/Switch3' incorporates:
     *  Delay: '<S1>/Delay12'
     */
    rtb_Switch3 = gm_uz_park_transformation_DW.Delay12_DSTATE;

    /* Switch: '<S1>/Switch2' incorporates:
     *  Delay: '<S1>/Delay6'
     */
    rtb_Switch2 = gm_uz_park_transformation_DW.Delay6_DSTATE;
  }

  /* End of Switch: '<S1>/Switch3' */

  /* Product: '<S1>/Product' incorporates:
   *  Switch: '<S1>/Switch2'
   *  Switch: '<S1>/Switch3'
   */
  tmp = mul_s32_loSR(rtb_Switch3, rtb_Switch2, 20U);

  /* Gain: '<S1>/Gain' incorporates:
   *  Product: '<S1>/Product'
   */
  tmp = mul_s32_loSR(83443, (tmp & 131072U) != 0U ? tmp | -131072 : tmp & 131071,
                     17U);

  /* DataTypeConversion: '<S9>/insig' incorporates:
   *  DataTypeConversion: '<S9>/insig1'
   *  Gain: '<S1>/Gain'
   */
  rtb_CastU16En31 = (uint16_T)((uint16_T)(((tmp & 131072U) != 0U ? tmp | -131072
    : tmp & 131071) >> 6) & 1023);

  /* RelationalOperator: '<S9>/LTEp25' incorporates:
   *  Constant: '<S9>/Point25'
   *  DataTypeConversion: '<S9>/insig'
   *  RelationalOperator: '<S9>/LTEp501'
   */
  rtb_LTEp50_tmp_tmp = (uint32_T)rtb_CastU16En31 << 8;
  rtb_LTEp50 = (rtb_LTEp50_tmp_tmp <= 65536U);

  /* RelationalOperator: '<S9>/GTEp75' incorporates:
   *  Constant: '<S9>/Point75'
   *  RelationalOperator: '<S9>/LTEp25'
   */
  rtb_LTEp251 = (rtb_LTEp50_tmp_tmp >= 196608U);

  /* Switch: '<S9>/QuadHandle1a' incorporates:
   *  Sum: '<S9>/Amp25'
   *  Sum: '<S9>/p25mA'
   *  Switch: '<S9>/QuadHandle1'
   */
  if (rtb_LTEp50) {
    /* Sum: '<S9>/p25mA' incorporates:
     *  Constant: '<S9>/Point25'
     *  DataTypeConversion: '<S9>/insig'
     */
    tmp = (int32_T)65536U - (rtb_CastU16En31 << 8);
    rtb_QuadHandle1 = (tmp & 262144U) != 0U ? tmp | -262144 : tmp & 262143;
  } else {
    /* Sum: '<S9>/Amp25' incorporates:
     *  Constant: '<S9>/Point25'
     *  DataTypeConversion: '<S9>/insig'
     */
    tmp = (rtb_CastU16En31 << 8) - (int32_T)65536U;
    rtb_QuadHandle1 = (tmp & 262144U) != 0U ? tmp | -262144 : tmp & 262143;
  }

  /* End of Switch: '<S9>/QuadHandle1a' */

  /* Switch: '<S9>/QuadHandle1b' incorporates:
   *  Sum: '<S9>/Amp75'
   *  Sum: '<S9>/p75mA'
   */
  if (rtb_LTEp251) {
    /* Sum: '<S9>/Amp75' incorporates:
     *  Constant: '<S9>/Point75'
     *  DataTypeConversion: '<S9>/insig'
     */
    tmp = (rtb_CastU16En31 << 8) - (int32_T)196608U;
    rtb_QuadHandle1b = (tmp & 262144U) != 0U ? tmp | -262144 : tmp & 262143;
  } else {
    /* Sum: '<S9>/p75mA' incorporates:
     *  Constant: '<S9>/Point75'
     *  DataTypeConversion: '<S9>/insig'
     */
    tmp = (int32_T)196608U - (rtb_CastU16En31 << 8);
    rtb_QuadHandle1b = (tmp & 262144U) != 0U ? tmp | -262144 : tmp & 262143;
  }

  /* End of Switch: '<S9>/QuadHandle1b' */

  /* Switch: '<S9>/QuadHandle2' incorporates:
   *  Constant: '<S9>/Point50'
   *  RelationalOperator: '<S9>/LTEp25'
   *  RelationalOperator: '<S9>/LTEp50'
   *  Switch: '<S9>/QuadHandle1'
   *  Switch: '<S9>/QuadHandle1b'
   */
  if (rtb_LTEp50_tmp_tmp <= 131072U) {
    tmp = rtb_QuadHandle1 >> 8;
    if (tmp < 0) {
      tmp = 0;
    }

    /* DataTypeConversion: '<S9>/CastU16En2' incorporates:
     *  DataTypeConversion: '<S9>/CastU16En3'
     *  Switch: '<S9>/QuadHandle1'
     */
    rtb_CastU16En2 = (uint16_T)tmp;
  } else {
    tmp = rtb_QuadHandle1b >> 8;
    if (tmp < 0) {
      tmp = 0;
    }

    /* DataTypeConversion: '<S9>/CastU16En2' incorporates:
     *  DataTypeConversion: '<S9>/CastU16En3'
     *  Switch: '<S9>/QuadHandle1b'
     */
    rtb_CastU16En2 = (uint16_T)tmp;
  }

  /* End of Switch: '<S9>/QuadHandle2' */

  /* RelationalOperator: '<S9>/LTEp501' incorporates:
   *  Constant: '<S9>/Point501'
   */
  rtb_LTEp501 = (rtb_LTEp50_tmp_tmp <= 131072U);

  /* Switch: '<S9>/QuadHandle1' incorporates:
   *  Sum: '<S9>/Amp50'
   */
  if (rtb_LTEp501) {
    rtb_QuadHandle1 = rtb_CastU16En31 << 8;
  } else {
    /* Sum: '<S9>/Amp50' incorporates:
     *  Constant: '<S9>/Point501'
     */
    tmp = (rtb_CastU16En31 << 8) - (int32_T)131072U;
    rtb_QuadHandle1 = (tmp & 262144U) != 0U ? tmp | -262144 : tmp & 262143;
  }

  /* End of Switch: '<S9>/QuadHandle1' */

  /* Switch: '<S9>/QuadHandle21' incorporates:
   *  Constant: '<S9>/Point251'
   *  RelationalOperator: '<S9>/LTEp251'
   *  Switch: '<S9>/QuadHandle1'
   */
  if (rtb_QuadHandle1 <= (int32_T)65536U) {
    /* DataTypeConversion: '<S9>/CastU16En31' incorporates:
     *  DataTypeConversion: '<S9>/CastU16En4'
     *  Switch: '<S9>/Switch1'
     */
    rtb_CastU16En31 = (uint16_T)((uint16_T)(rtb_QuadHandle1 >> 8) & 1023);
  } else {
    /* Sum: '<S9>/p50mA' incorporates:
     *  Constant: '<S9>/Point501'
     */
    tmp = (int32_T)131072U - rtb_QuadHandle1;

    /* DataTypeConversion: '<S9>/CastU16En31' incorporates:
     *  DataTypeConversion: '<S9>/CastU16En4'
     *  Sum: '<S9>/p50mA'
     *  Switch: '<S9>/Switch1'
     */
    rtb_CastU16En31 = (uint16_T)((uint16_T)(((tmp & 524288U) != 0U ? tmp |
      -524288 : tmp & 524287) >> 8) & 1023);
  }

  /* End of Switch: '<S9>/QuadHandle21' */

  /* Saturate: '<S9>/Saturation' incorporates:
   *  DataTypeConversion: '<S9>/CastU16En2'
   *  Switch: '<S9>/Switch1'
   */
  if (rtb_CastU16En2 < ((uint16_T)255U)) {
    rtb_Switch1_n = rtb_CastU16En2;
  } else {
    rtb_Switch1_n = ((uint16_T)255U);
  }

  /* End of Saturate: '<S9>/Saturation' */

  /* Lookup_n-D: '<S9>/Look-Up Table' incorporates:
   *  Constant: '<S9>/pow2switch'
   *  Switch: '<S9>/Switch'
   *  Switch: '<S9>/Switch1'
   */
  if (true) {
    rtb_CastU16En2 = rtb_Switch1_n;
  }

  /* Lookup_n-D: '<S9>/Look-Up Table' */
  rtb_LookUpTable = gm_uz_park_transformatio_ConstP.pooled6[plook_u32u16_bincka
    (rtb_CastU16En2, gm_uz_park_transformatio_ConstP.pooled11, 255U)];

  /* Saturate: '<S9>/Saturation1' incorporates:
   *  DataTypeConversion: '<S9>/CastU16En31'
   *  Switch: '<S9>/Switch1'
   */
  if (rtb_CastU16En31 < ((uint16_T)255U)) {
    rtb_Switch1_n = rtb_CastU16En31;
  } else {
    rtb_Switch1_n = ((uint16_T)255U);
  }

  /* End of Saturate: '<S9>/Saturation1' */

  /* Lookup_n-D: '<S9>/Look-Up Table1' incorporates:
   *  Constant: '<S9>/pow2switch1'
   *  Switch: '<S9>/Switch1'
   */
  if (true) {
    rtb_CastU16En31 = rtb_Switch1_n;
  }

  /* Lookup_n-D: '<S9>/Look-Up Table1' */
  rtb_LookUpTable1 = gm_uz_park_transformatio_ConstP.pooled6[plook_u32u16_bincka
    (rtb_CastU16En31, gm_uz_park_transformatio_ConstP.pooled11, 255U)];

  /* DataTypeConversion: '<S9>/dtc' incorporates:
   *  Logic: '<S9>/1st or 4th Quad'
   */
  rtb_dtc = (uint8_T)(rtb_LTEp50 || rtb_LTEp251);

  /* Switch: '<S1>/Switch' incorporates:
   *  Switch: '<S1>/Switch1'
   */
  if (rtb_FixPtRelationalOperator) {
    /* Switch: '<S1>/Switch' incorporates:
     *  Delay: '<S1>/Delay'
     */
    rtb_Switch = gm_uz_park_transformation_DW.Delay_DSTATE;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Delay: '<S1>/Delay1'
     */
    rtb_Switch1 = gm_uz_park_transformation_DW.Delay1_DSTATE;
  } else {
    /* Switch: '<S1>/Switch' incorporates:
     *  Delay: '<S1>/Delay5'
     */
    rtb_Switch = gm_uz_park_transformation_DW.Delay5_DSTATE;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Delay: '<S1>/Delay4'
     */
    rtb_Switch1 = gm_uz_park_transformation_DW.Delay4_DSTATE;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Delay: '<S1>/delayMatch4' */
  rtb_LTEp50 = gm_uz_park_transformation_DW.delayMatch4_DSTATE;

  /* End of Outputs for SubSystem: '<Root>/uz_park_transformation' */

  /* SignalGenerator: '<Root>/Sawtooth Generator' */
  rtb_PulseGenerator = 300.0 * gm_uz_park_transformation_M->Timing.t[0];

  /* Gain: '<Root>/Gain' incorporates:
   *  Constant: '<Root>/Constant1'
   *  SignalGenerator: '<Root>/Sawtooth Generator'
   *  Sum: '<Root>/Sum'
   */
  gm_uz_park_transformation_B.Gain = (6.2831853071795862 - (1.0 -
    (rtb_PulseGenerator - floor(rtb_PulseGenerator)) * 2.0) * 6.2831853071795862)
    * 0.5;

  /* RateTransition: '<Root>/Rate Transition2' */
  gm_uz_park_transformation_B.RateTransition2 = gm_uz_park_transformation_B.Gain;

  /* DataTypeConversion: '<Root>/Data Type Conversion1' */
  tmp_0 = floor(gm_uz_park_transformation_B.RateTransition2 * 1.048576E+6);
  if (rtIsNaN(tmp_0) || rtIsInf(tmp_0)) {
    tmp_0 = 0.0;
  } else {
    tmp_0 = fmod(tmp_0, 1.6777216E+7);
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion1' */
  gm_uz_park_transformation_B.DataTypeConversion1 = ((int32_T)tmp_0 & 8388608U)
    != 0U ? (int32_T)tmp_0 | -8388608 : (int32_T)tmp_0 & 8388607;

  /* RateTransition: '<Root>/Rate Transition3' */
  if (gm_uz_park_transformation_M->Timing.TaskCounters.TID[2] == 0) {
    /* RateTransition: '<Root>/Rate Transition3' */
    gm_uz_park_transformation_B.trigger =
      gm_uz_park_transformation_DW.RateTransition3_Buffer0;
  }

  /* End of RateTransition: '<Root>/Rate Transition3' */
  /* RateTransition: '<Root>/Rate Transition4' incorporates:
   *  Constant: '<Root>/Constant'
   */
  gm_uz_park_transformation_B.RateTransition4 = 1.0;

  /* DataTypeConversion: '<Root>/Data Type Conversion3' */
  tmp_0 = floor(gm_uz_park_transformation_B.RateTransition4 * 16384.0);
  if (rtIsNaN(tmp_0) || rtIsInf(tmp_0)) {
    tmp_0 = 0.0;
  } else {
    tmp_0 = fmod(tmp_0, 262144.0);
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion3' */
  gm_uz_park_transformation_B.DataTypeConversion3 = ((int32_T)tmp_0 & 131072U)
    != 0U ? (int32_T)tmp_0 | -131072 : (int32_T)tmp_0 & 131071;
  if (gm_uz_park_transformation_M->Timing.TaskCounters.TID[2] == 0) {
    /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
    rtb_PulseGenerator = (gm_uz_park_transformation_DW.clockTickCounter < 1.0) &&
      (gm_uz_park_transformation_DW.clockTickCounter >= 0) ? 1.0 : 0.0;
    if (gm_uz_park_transformation_DW.clockTickCounter >= 20.0 - 1.0) {
      gm_uz_park_transformation_DW.clockTickCounter = 0;
    } else {
      gm_uz_park_transformation_DW.clockTickCounter++;
    }

    /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

    /* DataTypeConversion: '<Root>/Data Type Conversion5' */
    rtb_DataTypeConversion5 = (rtb_PulseGenerator != 0.0);
  }

  /* Matfile logging */
  rt_UpdateTXYLogVars(gm_uz_park_transformation_M->rtwLogInfo,
                      (gm_uz_park_transformation_M->Timing.t));

  /* Update for Atomic SubSystem: '<Root>/uz_park_transformation' */
  /* Update for Delay: '<S9>/PipelineRegister' incorporates:
   *  Lookup_n-D: '<S9>/Look-Up Table'
   */
  gm_uz_park_transformation_DW.PipelineRegister_DSTATE = rtb_LookUpTable;

  /* Update for Delay: '<S9>/delayMatch1' */
  gm_uz_park_transformation_DW.delayMatch1_DSTATE_i = rtb_dtc;

  /* Update for Delay: '<S1>/delayMatch' incorporates:
   *  Switch: '<S1>/Switch'
   */
  gm_uz_park_transformation_DW.delayMatch_DSTATE = rtb_Switch;

  /* Update for Delay: '<S9>/PipelineRegister1' incorporates:
   *  Lookup_n-D: '<S9>/Look-Up Table1'
   */
  gm_uz_park_transformation_DW.PipelineRegister1_DSTATE = rtb_LookUpTable1;

  /* Update for Delay: '<S9>/delayMatch' */
  gm_uz_park_transformation_DW.delayMatch_DSTATE_d = rtb_LTEp501;

  /* Update for Delay: '<S1>/delayMatch1' incorporates:
   *  Switch: '<S1>/Switch1'
   */
  gm_uz_park_transformation_DW.delayMatch1_DSTATE = rtb_Switch1;

  /* Update for Delay: '<S1>/delayMatch2' incorporates:
   *  Switch: '<S1>/Switch1'
   */
  gm_uz_park_transformation_DW.delayMatch2_DSTATE = rtb_Switch1;

  /* Update for Delay: '<S1>/delayMatch3' incorporates:
   *  Switch: '<S1>/Switch'
   */
  gm_uz_park_transformation_DW.delayMatch3_DSTATE = rtb_Switch;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  gm_uz_park_transformation_DW.Delay_DSTATE =
    gm_uz_park_transformation_B.DataTypeConversion;

  /* Update for Delay: '<S1>/Delay1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion2'
   */
  gm_uz_park_transformation_DW.Delay1_DSTATE =
    gm_uz_park_transformation_B.DataTypeConversion2;

  /* Update for Delay: '<S1>/Delay10' incorporates:
   *  Sum: '<S1>/Add1'
   */
  gm_uz_park_transformation_DW.Delay10_DSTATE = rtb_Add1;

  /* Update for Delay: '<S1>/Delay11' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   */
  gm_uz_park_transformation_DW.Delay11_DSTATE =
    gm_uz_park_transformation_B.DataTypeConversion3;

  /* Update for Delay: '<S1>/Delay12' incorporates:
   *  Switch: '<S1>/Switch3'
   */
  gm_uz_park_transformation_DW.Delay12_DSTATE = rtb_Switch3;

  /* Update for Delay: '<S1>/Delay13' */
  gm_uz_park_transformation_DW.Delay13_DSTATE = rtb_FixPtRelationalOperator;

  /* Update for Delay: '<S1>/Delay2' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion1'
   */
  gm_uz_park_transformation_DW.Delay2_DSTATE =
    gm_uz_park_transformation_B.DataTypeConversion1;

  /* Update for Delay: '<S1>/Delay3' */
  gm_uz_park_transformation_DW.Delay3_DSTATE =
    gm_uz_park_transformation_B.trigger;

  /* Update for Delay: '<S1>/Delay4' incorporates:
   *  Switch: '<S1>/Switch1'
   */
  gm_uz_park_transformation_DW.Delay4_DSTATE = rtb_Switch1;

  /* Update for Delay: '<S1>/Delay5' incorporates:
   *  Switch: '<S1>/Switch'
   */
  gm_uz_park_transformation_DW.Delay5_DSTATE = rtb_Switch;

  /* Update for Delay: '<S1>/Delay6' incorporates:
   *  Switch: '<S1>/Switch2'
   */
  gm_uz_park_transformation_DW.Delay6_DSTATE = rtb_Switch2;

  /* Update for Delay: '<S1>/Delay7' incorporates:
   *  Sum: '<S1>/Add'
   */
  gm_uz_park_transformation_DW.Delay7_DSTATE = rtb_Add;

  /* Update for Delay: '<S1>/Delay8' incorporates:
   *  Sum: '<S1>/Add1'
   */
  gm_uz_park_transformation_DW.Delay8_DSTATE = rtb_Add1;

  /* Update for Delay: '<S1>/Delay9' incorporates:
   *  Sum: '<S1>/Add'
   */
  gm_uz_park_transformation_DW.Delay9_DSTATE = rtb_Add;

  /* Update for UnitDelay: '<S2>/Delay Input1' */
  gm_uz_park_transformation_DW.DelayInput1_DSTATE = rtb_Compare;

  /* Update for Delay: '<S1>/delayMatch4' */
  gm_uz_park_transformation_DW.delayMatch4_DSTATE = rtb_Delay13;

  /* End of Update for SubSystem: '<Root>/uz_park_transformation' */

  /* Update for RateTransition: '<Root>/Rate Transition3' */
  if (gm_uz_park_transformation_M->Timing.TaskCounters.TID[2] == 0) {
    gm_uz_park_transformation_DW.RateTransition3_Buffer0 =
      rtb_DataTypeConversion5;
  }

  /* End of Update for RateTransition: '<Root>/Rate Transition3' */

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(gm_uz_park_transformation_M)!=-1) &&
        !((rtmGetTFinal(gm_uz_park_transformation_M)-
           gm_uz_park_transformation_M->Timing.t[0]) >
          gm_uz_park_transformation_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(gm_uz_park_transformation_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++gm_uz_park_transformation_M->Timing.clockTick0)) {
    ++gm_uz_park_transformation_M->Timing.clockTickH0;
  }

  gm_uz_park_transformation_M->Timing.t[0] =
    gm_uz_park_transformation_M->Timing.clockTick0 *
    gm_uz_park_transformation_M->Timing.stepSize0 +
    gm_uz_park_transformation_M->Timing.clockTickH0 *
    gm_uz_park_transformation_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [1.0E-8s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 1.0E-8, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    gm_uz_park_transformation_M->Timing.clockTick1++;
    if (!gm_uz_park_transformation_M->Timing.clockTick1) {
      gm_uz_park_transformation_M->Timing.clockTickH1++;
    }
  }

  rate_scheduler();
}

/* Model initialize function */
void gm_uz_park_transformation_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)gm_uz_park_transformation_M, 0,
                sizeof(RT_MODEL_gm_uz_park_transform_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&gm_uz_park_transformation_M->solverInfo,
                          &gm_uz_park_transformation_M->Timing.simTimeStep);
    rtsiSetTPtr(&gm_uz_park_transformation_M->solverInfo, &rtmGetTPtr
                (gm_uz_park_transformation_M));
    rtsiSetStepSizePtr(&gm_uz_park_transformation_M->solverInfo,
                       &gm_uz_park_transformation_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&gm_uz_park_transformation_M->solverInfo,
                          (&rtmGetErrorStatus(gm_uz_park_transformation_M)));
    rtsiSetRTModelPtr(&gm_uz_park_transformation_M->solverInfo,
                      gm_uz_park_transformation_M);
  }

  rtsiSetSimTimeStep(&gm_uz_park_transformation_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&gm_uz_park_transformation_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(gm_uz_park_transformation_M,
             &gm_uz_park_transformation_M->Timing.tArray[0]);
  rtmSetTFinal(gm_uz_park_transformation_M, 0.01);
  gm_uz_park_transformation_M->Timing.stepSize0 = 1.0E-8;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    gm_uz_park_transformation_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(gm_uz_park_transformation_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(gm_uz_park_transformation_M->rtwLogInfo, (NULL));
    rtliSetLogT(gm_uz_park_transformation_M->rtwLogInfo, "");
    rtliSetLogX(gm_uz_park_transformation_M->rtwLogInfo, "");
    rtliSetLogXFinal(gm_uz_park_transformation_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(gm_uz_park_transformation_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(gm_uz_park_transformation_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(gm_uz_park_transformation_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(gm_uz_park_transformation_M->rtwLogInfo, 1);
    rtliSetLogY(gm_uz_park_transformation_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(gm_uz_park_transformation_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(gm_uz_park_transformation_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &gm_uz_park_transformation_B), 0,
                sizeof(B_gm_uz_park_transformation_T));

  /* states (dwork) */
  (void) memset((void *)&gm_uz_park_transformation_DW, 0,
                sizeof(DW_gm_uz_park_transformation_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(gm_uz_park_transformation_M->rtwLogInfo, 0.0,
    rtmGetTFinal(gm_uz_park_transformation_M),
    gm_uz_park_transformation_M->Timing.stepSize0, (&rtmGetErrorStatus
    (gm_uz_park_transformation_M)));

  /* Start for RateTransition: '<Root>/Rate Transition3' */
  gm_uz_park_transformation_B.trigger = false;

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  gm_uz_park_transformation_DW.clockTickCounter = 0;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition3' */
  gm_uz_park_transformation_DW.RateTransition3_Buffer0 = false;

  /* SystemInitialize for Atomic SubSystem: '<Root>/uz_park_transformation' */
  /* InitializeConditions for Delay: '<S9>/PipelineRegister' */
  gm_uz_park_transformation_DW.PipelineRegister_DSTATE = 0;

  /* InitializeConditions for Delay: '<S9>/delayMatch1' */
  gm_uz_park_transformation_DW.delayMatch1_DSTATE_i = ((uint8_T)0U);

  /* InitializeConditions for Delay: '<S1>/delayMatch' */
  gm_uz_park_transformation_DW.delayMatch_DSTATE = 0;

  /* InitializeConditions for Delay: '<S9>/PipelineRegister1' */
  gm_uz_park_transformation_DW.PipelineRegister1_DSTATE = 0;

  /* InitializeConditions for Delay: '<S9>/delayMatch' */
  gm_uz_park_transformation_DW.delayMatch_DSTATE_d = false;

  /* InitializeConditions for Delay: '<S1>/delayMatch1' */
  gm_uz_park_transformation_DW.delayMatch1_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/delayMatch2' */
  gm_uz_park_transformation_DW.delayMatch2_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/delayMatch3' */
  gm_uz_park_transformation_DW.delayMatch3_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay' */
  gm_uz_park_transformation_DW.Delay_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  gm_uz_park_transformation_DW.Delay1_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay10' */
  gm_uz_park_transformation_DW.Delay10_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay11' */
  gm_uz_park_transformation_DW.Delay11_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay12' */
  gm_uz_park_transformation_DW.Delay12_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay13' */
  gm_uz_park_transformation_DW.Delay13_DSTATE = false;

  /* InitializeConditions for Delay: '<S1>/Delay2' */
  gm_uz_park_transformation_DW.Delay2_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  gm_uz_park_transformation_DW.Delay3_DSTATE = false;

  /* InitializeConditions for Delay: '<S1>/Delay4' */
  gm_uz_park_transformation_DW.Delay4_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay5' */
  gm_uz_park_transformation_DW.Delay5_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay6' */
  gm_uz_park_transformation_DW.Delay6_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay7' */
  gm_uz_park_transformation_DW.Delay7_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay8' */
  gm_uz_park_transformation_DW.Delay8_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/Delay9' */
  gm_uz_park_transformation_DW.Delay9_DSTATE = 0;

  /* InitializeConditions for UnitDelay: '<S2>/Delay Input1' */
  gm_uz_park_transformation_DW.DelayInput1_DSTATE = false;

  /* InitializeConditions for Delay: '<S1>/delayMatch4' */
  gm_uz_park_transformation_DW.delayMatch4_DSTATE = false;

  /* End of SystemInitialize for SubSystem: '<Root>/uz_park_transformation' */
}

/* Model terminate function */
void gm_uz_park_transformation_terminate(void)
{
  /* (no terminate code required) */
}
