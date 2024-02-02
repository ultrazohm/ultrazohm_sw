/*
 * uz_pmsm_model.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "uz_pmsm_model".
 *
 * Model version              : 7.69
 * Simulink Coder version : 23.2 (R2023b) 01-Aug-2023
 * C source code generated on : Fri Feb  2 15:22:22 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "uz_pmsm_model.h"
#include "rtwtypes.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "uz_pmsm_model_private.h"
#include "zero_crossing_types.h"
#include <string.h>

/* Block signals (default storage) */
B_uz_pmsm_model_T uz_pmsm_model_B;

/* Block states (default storage) */
DW_uz_pmsm_model_T uz_pmsm_model_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_uz_pmsm_model_T uz_pmsm_model_PrevZCX;

/* Real-time model */
static RT_MODEL_uz_pmsm_model_T uz_pmsm_model_M_;
RT_MODEL_uz_pmsm_model_T *const uz_pmsm_model_M = &uz_pmsm_model_M_;
static void rate_scheduler(void);
real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const real_T bp1[],
                     const real_T table[], const uint32_T maxIndex[], uint32_T
                     stride)
{
  real_T fractions[2];
  real_T frac;
  real_T yL_0d0;
  real_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (uz_pmsm_model_M->Timing.TaskCounters.TID[1])++;
  if ((uz_pmsm_model_M->Timing.TaskCounters.TID[1]) > 24) {/* Sample time: [5.0E-5s, 0.0s] */
    uz_pmsm_model_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void uz_pmsm_model_step(void)
{
  /* local block i/o variables */
  boolean_T rtb_simulate_nonlinear;
  real_T rtb_Gain2;
  real_T rtb_Integrator;
  real_T rtb_Integrator_c;
  real_T rtb_Integrator_j;
  real_T rtb_Integrator_n;
  real_T rtb_Integrator_nb;
  real_T rtb_Lqq_adap;
  real_T rtb_Product1_i;
  real_T rtb_Product1_p;
  real_T rtb_error_id;
  real_T rtb_error_iq;
  real_T rtb_id_regler_b;
  real_T rtb_iq_regler_fk;
  real_T rtb_psi_q_controller;
  real_T rtb_u_d;
  real_T rtb_u_q;
  real_T rtb_uq_l;
  int32_T rtb_i_d_soll;
  int32_T tmp;
  real32_T rtb_DataTypeConversion23;
  real32_T rtb_Delay1_aj;
  real32_T rtb_Delay1_k;
  real32_T rtb_M_Mi_o;
  real32_T rtb_Product4_i;
  real32_T rtb_Sum1_a;
  real32_T rtb_error_i_d;
  real32_T rtb_i_d_hdl;
  real32_T rtb_i_q;
  real32_T rtb_i_q_hdl;
  ZCSigState Delay1_Reset_ZCE_tmp;

  /* RateTransition: '<Root>/Rate Transition6' incorporates:
   *  Constant: '<Root>/Constant3'
   */
  uz_pmsm_model_B.RateTransition6 = 0.0;

  /* RateTransition: '<Root>/Rate Transition8' incorporates:
   *  Constant: '<Root>/simulate_mechanical'
   */
  uz_pmsm_model_B.RateTransition8 = false;

  /* RateTransition: '<S4>/Rate Transition16' */
  uz_pmsm_model_B.u_J = uz_pmsm_model_ConstB.DataTypeConversion12_h;

  /* RateTransition: '<S4>/Rate Transition15' */
  uz_pmsm_model_B.mu = uz_pmsm_model_ConstB.DataTypeConversion13_o;

  /* RateTransition: '<S4>/Rate Transition10' */
  uz_pmsm_model_B.M_R0 = uz_pmsm_model_ConstB.DataTypeConversion14_o;

  /* RateTransition: '<S4>/Rate Transition12' */
  uz_pmsm_model_B.R_1 = uz_pmsm_model_ConstB.DataTypeConversion9_c;

  /* RateTransition: '<S4>/Rate Transition13' */
  uz_pmsm_model_B.polepair = uz_pmsm_model_ConstB.DataTypeConversion10_h;

  /* RateTransition: '<S4>/Rate Transition9' */
  uz_pmsm_model_B.u_L_d = uz_pmsm_model_ConstB.DataTypeConversion7_h;

  /* RateTransition: '<S4>/Rate Transition11' */
  uz_pmsm_model_B.u_L_q = uz_pmsm_model_ConstB.DataTypeConversion8_c;

  /* RateTransition: '<S4>/Rate Transition14' */
  uz_pmsm_model_B.psi_pm = uz_pmsm_model_ConstB.DataTypeConversion11_j;

  /* RateTransition: '<Root>/Rate Transition2' incorporates:
   *  RateTransition: '<Root>/Rate Transition1'
   */
  if (uz_pmsm_model_M->Timing.TaskCounters.TID[1] == 0) {
    /* RateTransition: '<Root>/Rate Transition2' */
    uz_pmsm_model_B.RateTransition2 = uz_pmsm_model_DW.RateTransition2_Buffer0;

    /* RateTransition: '<Root>/Rate Transition1' */
    uz_pmsm_model_B.RateTransition1 = uz_pmsm_model_DW.RateTransition1_Buffer0;
  }

  /* End of RateTransition: '<Root>/Rate Transition2' */

  /* RateTransition: '<Root>/Rate Transition' */
  uz_pmsm_model_B.RateTransition = uz_pmsm_model_ConstB.Gain2;

  /* RateTransition: '<Root>/Rate Transition17' incorporates:
   *  Constant: '<Root>/load_torque'
   */
  uz_pmsm_model_B.RateTransition17 = 0.0;

  /* Outputs for Atomic SubSystem: '<Root>/uz_pmsm_model' */
  /* Delay: '<S227>/Delay1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Delay: '<S226>/Delay1'
   *  Delay: '<S228>/Delay1'
   */
  tmp = (uz_pmsm_model_B.RateTransition6 == 0.0);
  if ((((uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE == POS_ZCSIG) == tmp) &&
       (uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE != UNINITIALIZED_ZCSIG)) ||
      (uz_pmsm_model_B.RateTransition6 != 0.0)) {
    uz_pmsm_model_DW.Delay1_DSTATE_j = 0.0F;
  }

  /* End of Outputs for SubSystem: '<Root>/uz_pmsm_model' */

  /* DataTypeConversion: '<Root>/Data Type Conversion3' */
  Delay1_Reset_ZCE_tmp = (ZCSigState)(uz_pmsm_model_B.RateTransition6 != 0.0);

  /* Outputs for Atomic SubSystem: '<Root>/uz_pmsm_model' */
  /* Delay: '<S227>/Delay1' */
  uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE = Delay1_Reset_ZCE_tmp;
  rtb_Delay1_k = uz_pmsm_model_DW.Delay1_DSTATE_j;

  /* Delay: '<S228>/Delay1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   */
  if ((((uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_f == POS_ZCSIG) == tmp) &&
       (uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_f != UNINITIALIZED_ZCSIG)) ||
      (uz_pmsm_model_B.RateTransition6 != 0.0)) {
    uz_pmsm_model_DW.Delay1_DSTATE_e = 0.0F;
  }

  uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_f = Delay1_Reset_ZCE_tmp;
  rtb_Delay1_aj = uz_pmsm_model_DW.Delay1_DSTATE_e;

  /* Delay: '<S226>/Delay1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   */
  if ((((uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_i == POS_ZCSIG) == tmp) &&
       (uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_i != UNINITIALIZED_ZCSIG)) ||
      (uz_pmsm_model_B.RateTransition6 != 0.0)) {
    uz_pmsm_model_DW.Delay1_DSTATE_n = 0.0F;
  }

  uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_i = Delay1_Reset_ZCE_tmp;

  /* Switch: '<S5>/Switch' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion2'
   *  DataTypeConversion: '<Root>/Data Type Conversion4'
   *  Delay: '<S226>/Delay1'
   *  Switch: '<S5>/Switch1'
   */
  if (uz_pmsm_model_B.RateTransition8) {
    rtb_DataTypeConversion23 = uz_pmsm_model_DW.Delay1_DSTATE_n;
    rtb_i_q = uz_pmsm_model_DW.Delay1_DSTATE_n;
  } else {
    rtb_DataTypeConversion23 = (real32_T)uz_pmsm_model_B.RateTransition;
    rtb_i_q = (real32_T)uz_pmsm_model_B.RateTransition;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Abs: '<S223>/Abs' incorporates:
   *  Delay: '<S226>/Delay1'
   */
  rtb_error_i_d = (real32_T)fabs(uz_pmsm_model_DW.Delay1_DSTATE_n);

  /* Delay: '<S223>/Delay' */
  rtb_i_q_hdl = uz_pmsm_model_DW.Delay_DSTATE;

  /* Sum: '<S223>/Sum1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion15'
   */
  rtb_Sum1_a = rtb_i_q_hdl - (real32_T)uz_pmsm_model_B.RateTransition17;

  /* Signum: '<S223>/Sign1' incorporates:
   *  Delay: '<S226>/Delay1'
   */
  if (rtIsNaNF(uz_pmsm_model_DW.Delay1_DSTATE_n)) {
    rtb_i_q_hdl = (rtNaNF);
  } else if (uz_pmsm_model_DW.Delay1_DSTATE_n < 0.0F) {
    rtb_i_q_hdl = -1.0F;
  } else {
    rtb_i_q_hdl = (real32_T)(uz_pmsm_model_DW.Delay1_DSTATE_n > 0.0F);
  }

  /* End of Signum: '<S223>/Sign1' */

  /* Product: '<S223>/Product4' incorporates:
   *  Product: '<S223>/Product12'
   *  Sum: '<S223>/Sum5'
   */
  rtb_Product4_i = (uz_pmsm_model_B.mu * rtb_error_i_d + uz_pmsm_model_B.M_R0) *
    rtb_i_q_hdl;

  /* Product: '<S224>/Product1' */
  rtb_error_i_d = rtb_Delay1_aj * uz_pmsm_model_B.u_L_q;

  /* Sum: '<S224>/Sum' incorporates:
   *  Product: '<S224>/Product5'
   */
  rtb_i_q_hdl = rtb_Delay1_k * uz_pmsm_model_B.u_L_d + uz_pmsm_model_B.psi_pm;

  /* Product: '<S225>/Product9' incorporates:
   *  Gain: '<S225>/Factor'
   *  Product: '<S225>/Product2'
   *  Product: '<S225>/Product3'
   *  Sum: '<S225>/Sum3'
   */
  rtb_M_Mi_o = (rtb_i_q_hdl * rtb_Delay1_aj - rtb_Delay1_k * rtb_error_i_d) *
    1.5F * uz_pmsm_model_B.polepair;

  /* Switch: '<S224>/Switch' incorporates:
   *  Constant: '<S224>/Constant2'
   */
  if (uz_pmsm_model_B.u_L_d != 0.0F) {
    rtb_i_d_hdl = uz_pmsm_model_B.u_L_d;
  } else {
    rtb_i_d_hdl = 1.1920929E-7F;
  }

  /* End of Switch: '<S224>/Switch' */

  /* Product: '<S224>/Product13' */
  rtb_DataTypeConversion23 *= uz_pmsm_model_B.polepair;

  /* Sum: '<S224>/Sum3' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Product: '<S224>/Product3'
   *  Product: '<S224>/Product4'
   */
  rtb_error_i_d = ((real32_T)uz_pmsm_model_B.RateTransition2 -
                   uz_pmsm_model_B.R_1 * rtb_Delay1_k) +
    rtb_DataTypeConversion23 * rtb_error_i_d;

  /* Sum: '<S224>/Sum4' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion1'
   *  Product: '<S224>/Product2'
   *  Product: '<S224>/Product9'
   */
  rtb_i_q_hdl = ((real32_T)uz_pmsm_model_B.RateTransition1 - rtb_i_q_hdl *
                 rtb_DataTypeConversion23) - rtb_Delay1_aj * uz_pmsm_model_B.R_1;

  /* Switch: '<S224>/Switch8' incorporates:
   *  Constant: '<S224>/Constant1'
   */
  if (uz_pmsm_model_B.u_L_q != 0.0F) {
    rtb_DataTypeConversion23 = uz_pmsm_model_B.u_L_q;
  } else {
    rtb_DataTypeConversion23 = 1.1920929E-7F;
  }

  /* End of Switch: '<S224>/Switch8' */

  /* Update for Delay: '<S227>/Delay1' incorporates:
   *  Gain: '<S227>/Gain7'
   *  Product: '<S224>/Divide'
   *  Sum: '<S227>/Sum5'
   */
  uz_pmsm_model_DW.Delay1_DSTATE_j = 1.0F / rtb_i_d_hdl * rtb_error_i_d *
    2.0E-6F + rtb_Delay1_k;

  /* Update for Delay: '<S228>/Delay1' incorporates:
   *  Gain: '<S228>/Gain7'
   *  Product: '<S224>/Divide1'
   *  Sum: '<S228>/Sum5'
   */
  uz_pmsm_model_DW.Delay1_DSTATE_e = rtb_i_q_hdl / rtb_DataTypeConversion23 *
    2.0E-6F + rtb_Delay1_aj;

  /* Update for Delay: '<S226>/Delay1' incorporates:
   *  Gain: '<S226>/Gain'
   *  Product: '<S223>/Product11'
   *  Sum: '<S226>/Sum3'
   */
  uz_pmsm_model_DW.Delay1_DSTATE_n += uz_pmsm_model_B.u_J * rtb_Sum1_a * 2.0E-6F;

  /* Update for Delay: '<S223>/Delay' incorporates:
   *  Sum: '<S223>/Sum'
   */
  uz_pmsm_model_DW.Delay_DSTATE = rtb_M_Mi_o - rtb_Product4_i;

  /* End of Outputs for SubSystem: '<Root>/uz_pmsm_model' */

  /* DataTypeConversion: '<Root>/Data Type Conversion6' */
  rtb_i_d_hdl = rtb_Delay1_k;

  /* DataTypeConversion: '<Root>/Data Type Conversion7' */
  rtb_i_q_hdl = rtb_Delay1_aj;

  /* Sum: '<Root>/Sum' */
  rtb_error_i_d = 0.0F - rtb_i_d_hdl;

  /* Sum: '<Root>/Sum1' */
  rtb_DataTypeConversion23 = 0.0F - rtb_i_q_hdl;

  /* RateTransition: '<Root>/Rate Transition5' */
  uz_pmsm_model_B.i_d = rtb_i_d_hdl;

  /* RateTransition: '<Root>/Rate Transition4' */
  uz_pmsm_model_B.i_q = rtb_i_q_hdl;

  /* RateTransition: '<Root>/Rate Transition3' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion5'
   */
  uz_pmsm_model_B.RateTransition3 = rtb_M_Mi_o;

  /* RateTransition: '<Root>/Rate Transition7' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion8'
   */
  uz_pmsm_model_B.RateTransition7 = rtb_i_q;

  /* RateTransition: '<S3>/Rate Transition5' */
  if (uz_pmsm_model_M->Timing.TaskCounters.TID[1] == 0) {
    /* Step: '<Root>/Step1' */
    rtb_Product1_i = !((((uz_pmsm_model_M->Timing.clockTick1+
                          uz_pmsm_model_M->Timing.clockTickH1* 4294967296.0)) *
                        5.0E-5) < 0.025);

    /* Gain: '<Root>/Gain3' */
    rtb_uq_l = -rtb_Product1_i;

    /* DataTypeConversion: '<Root>/Data Type Conversion9' */
    rtb_i_d_soll = (int32_T)rtb_uq_l;

    /* RateTransition: '<S3>/Rate Transition5' */
    uz_pmsm_model_B.u_Fid1_Giq1 = uz_pmsm_model_DW.RateTransition5_Buffer0;

    /* RateTransition: '<S3>/Rate Transition6' */
    uz_pmsm_model_B.u_Fid2_Giq2 = uz_pmsm_model_DW.RateTransition6_Buffer0;
  }

  /* End of RateTransition: '<S3>/Rate Transition5' */

  /* RateTransition: '<S3>/Rate Transition16' */
  uz_pmsm_model_B.ad1 = uz_pmsm_model_ConstB.DataTypeConversion12;

  /* RateTransition: '<S3>/Rate Transition15' */
  uz_pmsm_model_B.ad2 = uz_pmsm_model_ConstB.DataTypeConversion13;

  /* RateTransition: '<S3>/Rate Transition10' */
  uz_pmsm_model_B.ad3 = uz_pmsm_model_ConstB.DataTypeConversion14;

  /* RateTransition: '<S3>/Rate Transition9' */
  uz_pmsm_model_B.ad4 = uz_pmsm_model_ConstB.DataTypeConversion7;

  /* RateTransition: '<S3>/Rate Transition11' */
  uz_pmsm_model_B.ad5 = uz_pmsm_model_ConstB.DataTypeConversion8;

  /* RateTransition: '<S3>/Rate Transition12' */
  uz_pmsm_model_B.ad6 = uz_pmsm_model_ConstB.DataTypeConversion9;

  /* RateTransition: '<S3>/Rate Transition13' */
  uz_pmsm_model_B.aq1 = uz_pmsm_model_ConstB.DataTypeConversion10;

  /* RateTransition: '<S3>/Rate Transition14' */
  uz_pmsm_model_B.aq2 = uz_pmsm_model_ConstB.DataTypeConversion11;

  /* RateTransition: '<S3>/Rate Transition1' */
  uz_pmsm_model_B.aq3 = uz_pmsm_model_ConstB.DataTypeConversion3;

  /* RateTransition: '<S3>/Rate Transition2' */
  uz_pmsm_model_B.aq4 = uz_pmsm_model_ConstB.DataTypeConversion4;

  /* RateTransition: '<S3>/Rate Transition3' */
  uz_pmsm_model_B.aq5 = uz_pmsm_model_ConstB.DataTypeConversion5;

  /* RateTransition: '<S3>/Rate Transition4' */
  uz_pmsm_model_B.aq6 = uz_pmsm_model_ConstB.DataTypeConversion6;

  /* RateTransition: '<S3>/Rate Transition7' */
  uz_pmsm_model_B.ad4ad5 = uz_pmsm_model_ConstB.DataTypeConversion1;

  /* RateTransition: '<S3>/Rate Transition8' */
  uz_pmsm_model_B.ad1ad2 = uz_pmsm_model_ConstB.DataTypeConversion2;

  /* RateTransition: '<S3>/Rate Transition17' */
  uz_pmsm_model_B.aq4aq5 = uz_pmsm_model_ConstB.DataTypeConversion17;

  /* RateTransition: '<S3>/Rate Transition18' */
  uz_pmsm_model_B.aq1aq2 = uz_pmsm_model_ConstB.DataTypeConversion18;

  /* RateTransition: '<S3>/Rate Transition23' incorporates:
   *  Constant: '<S3>/Constant32'
   *  DataTypeConversion: '<S3>/Data Type Conversion23'
   *  Product: '<S3>/Product4'
   */
  uz_pmsm_model_B.aq3_aq6 = (real32_T)(uz_pmsm_model_ConstB.Add * 0.5);

  /* RateTransition: '<S3>/Rate Transition19' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   *  DataTypeConversion: '<S1>/Data Type Conversion2'
   *  RateTransition: '<S1>/Rate Transition1'
   *  RateTransition: '<S1>/Rate Transition11'
   *  RateTransition: '<S1>/Rate Transition3'
   */
  if (uz_pmsm_model_M->Timing.TaskCounters.TID[1] == 0) {
    /* RateTransition: '<S3>/Rate Transition19' */
    uz_pmsm_model_B.aq4_aq5 = uz_pmsm_model_DW.RateTransition19_Buffer0;

    /* RateTransition: '<S3>/Rate Transition20' */
    uz_pmsm_model_B.aq1_aq2 = uz_pmsm_model_DW.RateTransition20_Buffer0;

    /* RateTransition: '<S3>/Rate Transition21' */
    uz_pmsm_model_B.ad4_ad5 = uz_pmsm_model_DW.RateTransition21_Buffer0;

    /* RateTransition: '<S3>/Rate Transition22' */
    uz_pmsm_model_B.ad1_ad2 = uz_pmsm_model_DW.RateTransition22_Buffer0;
    uz_pmsm_model_DW.RateTransition3_Buffer[0] = uz_pmsm_model_B.ad1;
    uz_pmsm_model_DW.RateTransition3_Buffer[1] = uz_pmsm_model_B.ad2;
    uz_pmsm_model_DW.RateTransition3_Buffer[2] = uz_pmsm_model_B.ad3;
    uz_pmsm_model_DW.RateTransition3_Buffer[3] = uz_pmsm_model_B.ad4;
    uz_pmsm_model_DW.RateTransition3_Buffer[4] = uz_pmsm_model_B.ad5;
    uz_pmsm_model_DW.RateTransition3_Buffer[5] = uz_pmsm_model_B.ad6;
    uz_pmsm_model_DW.RateTransition3_Buffer[6] = uz_pmsm_model_B.aq1;
    uz_pmsm_model_DW.RateTransition3_Buffer[7] = uz_pmsm_model_B.aq2;
    uz_pmsm_model_DW.RateTransition3_Buffer[8] = uz_pmsm_model_B.aq3;
    uz_pmsm_model_DW.RateTransition3_Buffer[9] = uz_pmsm_model_B.aq4;
    uz_pmsm_model_DW.RateTransition3_Buffer[10] = uz_pmsm_model_B.aq5;
    uz_pmsm_model_DW.RateTransition3_Buffer[11] = uz_pmsm_model_B.aq6;
    uz_pmsm_model_DW.RateTransition3_Buffer[12] = uz_pmsm_model_B.u_Fid1_Giq1;
    uz_pmsm_model_DW.RateTransition3_Buffer[13] = uz_pmsm_model_B.u_Fid2_Giq2;
    uz_pmsm_model_DW.RateTransition3_Buffer[14] = uz_pmsm_model_B.ad4ad5;
    uz_pmsm_model_DW.RateTransition3_Buffer[15] = uz_pmsm_model_B.ad1ad2;
    uz_pmsm_model_DW.RateTransition3_Buffer[16] = uz_pmsm_model_B.aq4aq5;
    uz_pmsm_model_DW.RateTransition3_Buffer[17] = uz_pmsm_model_B.aq1aq2;
    uz_pmsm_model_DW.RateTransition3_Buffer[18] = uz_pmsm_model_B.aq4_aq5;
    uz_pmsm_model_DW.RateTransition3_Buffer[19] = uz_pmsm_model_B.aq1_aq2;
    uz_pmsm_model_DW.RateTransition3_Buffer[20] = uz_pmsm_model_B.ad4_ad5;
    uz_pmsm_model_DW.RateTransition3_Buffer[21] = uz_pmsm_model_B.ad1_ad2;
    uz_pmsm_model_DW.RateTransition3_Buffer[22] = uz_pmsm_model_B.aq3_aq6;
    uz_pmsm_model_DW.RateTransition1_Buffer = rtb_Delay1_aj;
    uz_pmsm_model_DW.RateTransition11_Buffer = rtb_Delay1_k;

    /* Sum: '<S113>/Sum' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion1'
     *  DataTypeConversion: '<S1>/Data Type Conversion2'
     */
    rtb_Integrator_n = uz_pmsm_model_DW.RateTransition11_Buffer -
      uz_pmsm_model_DW.RateTransition3_Buffer[2];

    /* Product: '<S113>/Product' incorporates:
     *  Product: '<S115>/Product7'
     */
    rtb_Integrator = rtb_Integrator_n * uz_pmsm_model_DW.RateTransition3_Buffer
      [1];
    rtb_Integrator_j = rtb_Integrator;

    /* Product: '<S113>/Product1' incorporates:
     *  Trigonometry: '<S113>/Tanh'
     */
    rtb_Integrator_n = tanh(rtb_Integrator_j) *
      uz_pmsm_model_DW.RateTransition3_Buffer[0];

    /* Sum: '<S113>/Sum1' */
    rtb_Integrator_j = uz_pmsm_model_DW.RateTransition11_Buffer -
      uz_pmsm_model_DW.RateTransition3_Buffer[5];

    /* Product: '<S113>/Product2' incorporates:
     *  Product: '<S115>/Product10'
     */
    rtb_error_iq = rtb_Integrator_j * uz_pmsm_model_DW.RateTransition3_Buffer[4];

    /* Product: '<S113>/Product3' incorporates:
     *  Product: '<S113>/Product2'
     *  Trigonometry: '<S113>/Tanh1'
     */
    rtb_Integrator_j = tanh(rtb_error_iq) *
      uz_pmsm_model_DW.RateTransition3_Buffer[3];

    /* Product: '<S113>/Product4' incorporates:
     *  Product: '<S115>/Product'
     */
    rtb_Integrator_nb = uz_pmsm_model_DW.RateTransition1_Buffer *
      uz_pmsm_model_DW.RateTransition3_Buffer[7];

    /* Product: '<S113>/Product6' incorporates:
     *  Math: '<S113>/Log'
     *  Product: '<S113>/Product4'
     *  Trigonometry: '<S113>/Tanh2'
     *
     * About '<S113>/Log':
     *  Operator: log
     */
    rtb_uq_l = log(cosh(rtb_Integrator_nb)) *
      uz_pmsm_model_DW.RateTransition3_Buffer[19];

    /* Product: '<S113>/Product7' incorporates:
     *  Product: '<S113>/Product8'
     */
    rtb_Lqq_adap = uz_pmsm_model_DW.RateTransition1_Buffer *
      uz_pmsm_model_DW.RateTransition1_Buffer *
      uz_pmsm_model_DW.RateTransition3_Buffer[22];

    /* Product: '<S113>/Product5' incorporates:
     *  Product: '<S115>/Product2'
     */
    rtb_Gain2 = uz_pmsm_model_DW.RateTransition1_Buffer *
      uz_pmsm_model_DW.RateTransition3_Buffer[10];

    /* Product: '<S113>/Product12' incorporates:
     *  Math: '<S113>/Log1'
     *  Product: '<S113>/Product5'
     *  Trigonometry: '<S113>/Tanh3'
     *
     * About '<S113>/Log1':
     *  Operator: log
     */
    rtb_Integrator_c = log(cosh(rtb_Gain2)) *
      uz_pmsm_model_DW.RateTransition3_Buffer[18];

    /* Sum: '<S113>/Sum7' incorporates:
     *  Product: '<S113>/Product10'
     *  Sum: '<S113>/Sum2'
     *  Sum: '<S113>/Sum3'
     */
    rtb_Integrator_n -= ((rtb_uq_l + rtb_Lqq_adap) - rtb_Integrator_c) *
      (rtb_Integrator_n - rtb_Integrator_j) *
      uz_pmsm_model_DW.RateTransition3_Buffer[12];

    /* RateTransition: '<S1>/Rate Transition5' incorporates:
     *  Constant: '<S1>/Constant2'
     */
    uz_pmsm_model_DW.RateTransition5_Buffer = 0.0003;

    /* Switch: '<S11>/Switch' incorporates:
     *  RateTransition: '<S1>/Rate Transition5'
     */
    rtb_Integrator_c = uz_pmsm_model_DW.RateTransition5_Buffer;

    /* RateTransition: '<S1>/Rate Transition7' incorporates:
     *  Constant: '<S1>/Constant'
     */
    uz_pmsm_model_DW.RateTransition7_Buffer = 5000.0;

    /* Product: '<S11>/Product' incorporates:
     *  RateTransition: '<S1>/Rate Transition7'
     */
    rtb_Integrator_c *= uz_pmsm_model_DW.RateTransition7_Buffer;

    /* DataTypeConversion: '<Root>/Data Type Conversion10' */
    rtb_Delay1_k = (real32_T)rtb_Product1_i;

    /* Product: '<S115>/Product5' */
    rtb_Lqq_adap = uz_pmsm_model_DW.RateTransition1_Buffer *
      uz_pmsm_model_DW.RateTransition3_Buffer[8];

    /* Product: '<S115>/Product' */
    rtb_Integrator_j = rtb_Integrator_nb;

    /* Sum: '<S115>/Sum4' incorporates:
     *  Product: '<S115>/Product1'
     *  Trigonometry: '<S115>/Tanh'
     */
    rtb_Lqq_adap += tanh(rtb_Integrator_j) *
      uz_pmsm_model_DW.RateTransition3_Buffer[6];

    /* Product: '<S115>/Product2' */
    rtb_Integrator_j = rtb_Gain2;

    /* Product: '<S115>/Product3' incorporates:
     *  Trigonometry: '<S115>/Tanh1'
     */
    rtb_Gain2 = tanh(rtb_Integrator_j) *
      uz_pmsm_model_DW.RateTransition3_Buffer[9];

    /* Product: '<S115>/Product6' */
    rtb_Integrator_j = uz_pmsm_model_DW.RateTransition1_Buffer *
      uz_pmsm_model_DW.RateTransition3_Buffer[11];

    /* Sum: '<S115>/Sum2' incorporates:
     *  Sum: '<S115>/Sum1'
     */
    rtb_Gain2 = rtb_Lqq_adap - (rtb_Gain2 + rtb_Integrator_j);

    /* RateTransition: '<S1>/Rate Transition4' incorporates:
     *  Constant: '<S1>/Constant3'
     */
    uz_pmsm_model_DW.RateTransition4_Buffer = 0.002;

    /* Switch: '<S11>/Switch1' incorporates:
     *  RateTransition: '<S1>/Rate Transition4'
     */
    rtb_Integrator_j = uz_pmsm_model_DW.RateTransition4_Buffer;

    /* Product: '<S11>/Product1' incorporates:
     *  RateTransition: '<S1>/Rate Transition7'
     */
    rtb_Integrator_j *= uz_pmsm_model_DW.RateTransition7_Buffer;

    /* RateTransition: '<S1>/Rate Transition2' */
    uz_pmsm_model_DW.RateTransition2_Buffer_f = rtb_i_q;

    /* Sum: '<S1>/Sum3' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion10'
     */
    rtb_uq_l = rtb_Product1_i - uz_pmsm_model_DW.RateTransition1_Buffer;

    /* Product: '<S100>/PProd Out' */
    rtb_Integrator_nb = rtb_uq_l * rtb_Integrator_j;

    /* DiscreteIntegrator: '<S95>/Integrator' */
    rtb_Integrator_j = uz_pmsm_model_DW.Integrator_DSTATE;

    /* Sum: '<S104>/Sum' */
    rtb_Product1_i = rtb_Integrator_nb + rtb_Integrator_j;

    /* Delay: '<S1>/Delay1' */
    rtb_Integrator_j = uz_pmsm_model_DW.Delay1_DSTATE;

    /* Gain: '<S15>/Gain2' incorporates:
     *  Gain: '<S12>/Gain2'
     *  RateTransition: '<S1>/Rate Transition2'
     */
    rtb_Delay1_aj = 4.0F * uz_pmsm_model_DW.RateTransition2_Buffer_f;

    /* Product: '<S15>/Product' incorporates:
     *  Gain: '<S15>/Gain2'
     *  Math: '<S115>/Log1'
     *  Math: '<S115>/Log2'
     *  Product: '<S115>/Product10'
     *  Product: '<S115>/Product20'
     *  Product: '<S115>/Product4'
     *  Product: '<S115>/Product7'
     *  Product: '<S115>/Product9'
     *  Sum: '<S115>/Sum10'
     *  Sum: '<S115>/Sum5'
     *  Trigonometry: '<S115>/Tanh2'
     *  Trigonometry: '<S115>/Tanh4'
     *
     * About '<S115>/Log1':
     *  Operator: log
     *
     * About '<S115>/Log2':
     *  Operator: log
     */
    rtb_Gain2 = (rtb_Lqq_adap - (uz_pmsm_model_DW.RateTransition3_Buffer[21] *
      (real32_T)log((real32_T)cosh((real32_T)rtb_Integrator)) - (real32_T)log
      ((real32_T)cosh((real32_T)rtb_error_iq)) *
      uz_pmsm_model_DW.RateTransition3_Buffer[20]) * rtb_Gain2 *
                 uz_pmsm_model_DW.RateTransition3_Buffer[13]) * rtb_Delay1_aj;

    /* Switch: '<S6>/Switch3' incorporates:
     *  Gain: '<S12>/Gain'
     *  Product: '<S12>/Product'
     */
    rtb_psi_q_controller = 0.002F * rtb_Delay1_k * rtb_Delay1_aj;

    /* Delay: '<S1>/Delay2' */
    rtb_Integrator_nb = uz_pmsm_model_DW.Delay2_DSTATE;

    /* Sum: '<S1>/Sum2' */
    rtb_error_iq = (real_T)rtb_i_d_soll -
      uz_pmsm_model_DW.RateTransition11_Buffer;

    /* Product: '<S52>/PProd Out' */
    rtb_Lqq_adap = rtb_error_iq * rtb_Integrator_c;

    /* DiscreteIntegrator: '<S47>/Integrator' */
    rtb_Integrator_c = uz_pmsm_model_DW.Integrator_DSTATE_e;

    /* Sum: '<S56>/Sum' */
    rtb_Integrator = rtb_Lqq_adap + rtb_Integrator_c;

    /* Product: '<S15>/Product1' incorporates:
     *  Gain: '<S15>/Gain2'
     */
    rtb_Integrator_c = rtb_Integrator_n * rtb_Delay1_aj;

    /* Switch: '<S6>/Switch2' incorporates:
     *  Constant: '<S12>/Constant1'
     *  Gain: '<S12>/Gain1'
     *  Product: '<S12>/Product1'
     *  Sum: '<S12>/Sum6'
     */
    rtb_Lqq_adap = (0.0003F * (real32_T)rtb_i_d_soll + 0.0194) * rtb_Delay1_aj;

    /* RateTransition: '<S1>/Rate Transition6' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    uz_pmsm_model_DW.RateTransition6_Buffer = 0.3;

    /* Product: '<S11>/Product2' incorporates:
     *  RateTransition: '<S1>/Rate Transition6'
     *  RateTransition: '<S1>/Rate Transition7'
     */
    rtb_error_id = uz_pmsm_model_DW.RateTransition7_Buffer *
      uz_pmsm_model_DW.RateTransition6_Buffer;

    /* Product: '<S44>/IProd Out' */
    rtb_Gain2 = rtb_error_iq * rtb_error_id;

    /* Product: '<S92>/IProd Out' */
    rtb_error_iq = rtb_uq_l * rtb_error_id;

    /* Switch: '<S1>/Switch' incorporates:
     *  Sum: '<S1>/Sum1'
     */
    rtb_u_q = rtb_Product1_i + rtb_Lqq_adap;

    /* Switch: '<S1>/Switch1' incorporates:
     *  Sum: '<S1>/Sum'
     */
    rtb_u_d = rtb_Integrator - rtb_psi_q_controller;
  }

  /* End of RateTransition: '<S3>/Rate Transition19' */

  /* RateTransition: '<Root>/Rate Transition9' incorporates:
   *  Constant: '<Root>/simulate_nonlinear_modell'
   */
  uz_pmsm_model_B.RateTransition9 = true;

  /* DataTypeConversion: '<Root>/Data Type Conversion11' */
  rtb_simulate_nonlinear = uz_pmsm_model_B.RateTransition9;
  if (uz_pmsm_model_M->Timing.TaskCounters.TID[1] == 0) {
    /* Switch: '<S3>/Switch1' incorporates:
     *  Constant: '<S3>/Constant23'
     *  Constant: '<S3>/Constant34'
     */
    if (uz_pmsm_model_ConstB.Abs1 >= 2.2204460492503131E-16) {
      rtb_error_id = 0.17052123571015093;
    } else {
      rtb_error_id = 2.2204460492503131E-16;
    }

    /* End of Switch: '<S3>/Switch1' */

    /* Product: '<S3>/Divide' incorporates:
     *  Constant: '<S3>/Constant22'
     */
    rtb_error_id = 0.0050018709753382991 / rtb_error_id;

    /* Switch: '<S3>/Switch5' incorporates:
     *  Constant: '<S3>/Constant12'
     *  Constant: '<S3>/Constant38'
     */
    if (uz_pmsm_model_ConstB.Abs4 >= 2.2204460492503131E-16) {
      rtb_Lqq_adap = -0.0013567940263368022;
    } else {
      rtb_Lqq_adap = 2.2204460492503131E-16;
    }

    /* End of Switch: '<S3>/Switch5' */

    /* Update for RateTransition: '<S3>/Rate Transition5' incorporates:
     *  Constant: '<S3>/Constant37'
     *  DataTypeConversion: '<S3>/Data Type Conversion15'
     *  Product: '<S3>/Divide4'
     */
    uz_pmsm_model_DW.RateTransition5_Buffer0 = (real32_T)(1.0 / rtb_Lqq_adap);

    /* Switch: '<S3>/Switch6' incorporates:
     *  Constant: '<S3>/Constant13'
     *  Constant: '<S3>/Constant40'
     */
    if (uz_pmsm_model_ConstB.Abs5 >= 2.2204460492503131E-16) {
      rtb_Lqq_adap = 0.078813850391712681;
    } else {
      rtb_Lqq_adap = 2.2204460492503131E-16;
    }

    /* End of Switch: '<S3>/Switch6' */

    /* Update for RateTransition: '<S3>/Rate Transition6' incorporates:
     *  Constant: '<S3>/Constant39'
     *  DataTypeConversion: '<S3>/Data Type Conversion16'
     *  Product: '<S3>/Divide5'
     */
    uz_pmsm_model_DW.RateTransition6_Buffer0 = (real32_T)(1.0 / rtb_Lqq_adap);

    /* Update for RateTransition: '<S3>/Rate Transition19' incorporates:
     *  DataTypeConversion: '<S3>/Data Type Conversion19'
     */
    uz_pmsm_model_DW.RateTransition19_Buffer0 = (real32_T)rtb_error_id;

    /* Switch: '<S3>/Switch2' incorporates:
     *  Constant: '<S3>/Constant25'
     *  Constant: '<S3>/Constant33'
     */
    if (uz_pmsm_model_ConstB.Abs >= 2.2204460492503131E-16) {
      rtb_error_id = 0.17159525478425847;
    } else {
      rtb_error_id = 2.2204460492503131E-16;
    }

    /* End of Switch: '<S3>/Switch2' */

    /* Update for RateTransition: '<S3>/Rate Transition20' incorporates:
     *  Constant: '<S3>/Constant24'
     *  DataTypeConversion: '<S3>/Data Type Conversion20'
     *  Product: '<S3>/Divide1'
     */
    uz_pmsm_model_DW.RateTransition20_Buffer0 = (real32_T)(0.0048166705428629008
      / rtb_error_id);

    /* Switch: '<S3>/Switch3' incorporates:
     *  Constant: '<S3>/Constant27'
     *  Constant: '<S3>/Constant35'
     */
    if (uz_pmsm_model_ConstB.Abs2 >= 2.2204460492503131E-16) {
      rtb_error_id = 0.00061831633744579932;
    } else {
      rtb_error_id = 2.2204460492503131E-16;
    }

    /* End of Switch: '<S3>/Switch3' */

    /* Update for RateTransition: '<S3>/Rate Transition21' incorporates:
     *  Constant: '<S3>/Constant26'
     *  DataTypeConversion: '<S3>/Data Type Conversion21'
     *  Product: '<S3>/Divide2'
     */
    uz_pmsm_model_DW.RateTransition21_Buffer0 = (real32_T)(1.2964386333449704 /
      rtb_error_id);

    /* Switch: '<S3>/Switch4' incorporates:
     *  Constant: '<S3>/Constant29'
     *  Constant: '<S3>/Constant36'
     */
    if (uz_pmsm_model_ConstB.Abs3 >= 2.2204460492503131E-16) {
      rtb_error_id = 0.040244227373266737;
    } else {
      rtb_error_id = 2.2204460492503131E-16;
    }

    /* End of Switch: '<S3>/Switch4' */

    /* Update for RateTransition: '<S3>/Rate Transition22' incorporates:
     *  Constant: '<S3>/Constant28'
     *  DataTypeConversion: '<S3>/Data Type Conversion22'
     *  Product: '<S3>/Divide3'
     */
    uz_pmsm_model_DW.RateTransition22_Buffer0 = (real32_T)(0.030483840951002285 /
      rtb_error_id);

    /* RateTransition: '<S2>/Rate Transition1' */
    uz_pmsm_model_DW.RateTransition1_Buffer_l = 0.0;
    rtb_iq_regler_fk = uz_pmsm_model_DW.RateTransition1_Buffer_l;

    /* Lookup_n-D: '<S120>/Flux_d Lookup Table1' incorporates:
     *  Lookup_n-D: '<S120>/Flux_d Lookup Table'
     *  RateTransition: '<S2>/Rate Transition1'
     */
    rtb_Product1_p = look2_binlxpw(0.0, rtb_iq_regler_fk,
      uz_pmsm_model_ConstP.pooled22, uz_pmsm_model_ConstP.pooled23,
      uz_pmsm_model_ConstP.pooled21, uz_pmsm_model_ConstP.pooled36, 20U);
    rtb_error_id = rtb_Product1_p;

    /* RateTransition: '<S2>/Rate Transition11' */
    uz_pmsm_model_DW.RateTransition11_Buffer_f = 0.0;
    rtb_id_regler_b = uz_pmsm_model_DW.RateTransition11_Buffer_f;

    /* Sum: '<S122>/Sum4' */
    rtb_Lqq_adap = rtb_error_id - rtb_Product1_p;

    /* Sum: '<S2>/Sum2' */
    rtb_error_id = 0.0 - rtb_id_regler_b;

    /* Abs: '<S122>/Abs' incorporates:
     *  Abs: '<S122>/Abs1'
     */
    rtb_uq_l = fabs(rtb_error_id);
    rtb_Integrator_c = rtb_uq_l;

    /* Switch: '<S122>/Switch2' incorporates:
     *  Constant: '<S122>/Constant4'
     */
    if (rtb_Integrator_c >= 2.2204460492503131E-16) {
      rtb_Integrator_n = rtb_error_id;
    } else {
      rtb_Integrator_n = 2.2204460492503131E-16;
    }

    /* Product: '<S122>/Divide' incorporates:
     *  Switch: '<S122>/Switch2'
     */
    rtb_Integrator_c = rtb_Lqq_adap / rtb_Integrator_n;

    /* RateTransition: '<S122>/Rate Transition12' incorporates:
     *  Constant: '<S122>/Constant'
     */
    uz_pmsm_model_DW.RateTransition12_Buffer = 5000.0;

    /* Product: '<S122>/Product' incorporates:
     *  RateTransition: '<S122>/Rate Transition12'
     */
    rtb_Integrator = 0.0003 * uz_pmsm_model_DW.RateTransition12_Buffer;

    /* Lookup_n-D: '<S120>/Flux_q Lookup Table1' incorporates:
     *  Lookup_n-D: '<S120>/Flux_q Lookup Table2'
     *  RateTransition: '<S2>/Rate Transition1'
     *  RateTransition: '<S2>/Rate Transition11'
     */
    rtb_psi_q_controller = look2_binlxpw(rtb_id_regler_b, rtb_iq_regler_fk,
      uz_pmsm_model_ConstP.pooled22, uz_pmsm_model_ConstP.pooled23,
      uz_pmsm_model_ConstP.pooled24, uz_pmsm_model_ConstP.pooled36, 20U);

    /* Abs: '<S122>/Abs1' */
    rtb_Lqq_adap = rtb_uq_l;

    /* Switch: '<S122>/Switch3' incorporates:
     *  Constant: '<S122>/Constant5'
     *  Sum: '<S2>/Sum2'
     */
    if (rtb_Lqq_adap >= 2.2204460492503131E-16) {
      rtb_Integrator_n = 0.0 - rtb_id_regler_b;
    } else {
      rtb_Integrator_n = 2.2204460492503131E-16;
    }

    /* Product: '<S122>/Divide1' incorporates:
     *  Sum: '<S122>/Sum5'
     *  Switch: '<S122>/Switch3'
     */
    rtb_Lqq_adap = (rtb_psi_q_controller - rtb_psi_q_controller) /
      rtb_Integrator_n;

    /* Product: '<S122>/Product1' incorporates:
     *  RateTransition: '<S122>/Rate Transition12'
     */
    rtb_Integrator_n = uz_pmsm_model_DW.RateTransition12_Buffer * 0.002;

    /* RateTransition: '<S2>/Rate Transition2' */
    uz_pmsm_model_DW.RateTransition2_Buffer = 0.0;

    /* Product: '<S211>/PProd Out' incorporates:
     *  Sum: '<S2>/Sum3'
     */
    rtb_uq_l = (0.0 - rtb_iq_regler_fk) * rtb_Integrator_n;

    /* DiscreteIntegrator: '<S206>/Integrator' */
    rtb_Integrator_n = uz_pmsm_model_DW.Integrator_DSTATE_c;

    /* Sum: '<S215>/Sum' */
    rtb_uq_l += rtb_Integrator_n;

    /* Gain: '<S126>/Gain2' incorporates:
     *  Gain: '<S123>/Gain2'
     *  RateTransition: '<S2>/Rate Transition2'
     */
    rtb_Product1_i = 4.0 * uz_pmsm_model_DW.RateTransition2_Buffer;

    /* Product: '<S126>/Product' */
    rtb_Integrator_n = rtb_psi_q_controller * rtb_Product1_i;

    /* Switch: '<S116>/Switch3' incorporates:
     *  Product: '<S123>/Product'
     */
    rtb_psi_q_controller = uz_pmsm_model_ConstB.Gain * rtb_Product1_i;

    /* Product: '<S163>/PProd Out' */
    rtb_error_id *= rtb_Integrator;

    /* DiscreteIntegrator: '<S158>/Integrator' */
    rtb_Integrator = uz_pmsm_model_DW.Integrator_DSTATE_j;

    /* Product: '<S126>/Product1' */
    rtb_Product1_p *= rtb_Product1_i;

    /* Switch: '<S116>/Switch2' incorporates:
     *  Constant: '<S123>/Constant1'
     *  Product: '<S123>/Product1'
     *  Sum: '<S123>/Sum6'
     */
    rtb_Product1_i *= uz_pmsm_model_ConstB.Gain1 + 0.0194;

    /* Sum: '<S2>/Sum' incorporates:
     *  Sum: '<S167>/Sum'
     */
    rtb_Integrator = (rtb_error_id + rtb_Integrator) - rtb_psi_q_controller;

    /* Sum: '<S2>/Sum1' */
    rtb_uq_l += rtb_Product1_i;

    /* RateTransition: '<S122>/Rate Transition1' incorporates:
     *  Constant: '<S122>/Constant1'
     */
    uz_pmsm_model_DW.RateTransition1_Buffer_j = 0.3;

    /* Product: '<S122>/Product2' incorporates:
     *  RateTransition: '<S122>/Rate Transition1'
     *  RateTransition: '<S122>/Rate Transition12'
     */
    rtb_Product1_i = uz_pmsm_model_DW.RateTransition12_Buffer *
      uz_pmsm_model_DW.RateTransition1_Buffer_j;

    /* Update for Delay: '<S2>/Delay1' incorporates:
     *  Switch: '<S2>/Switch'
     */
    uz_pmsm_model_DW.Delay1_DSTATE_a = rtb_uq_l;

    /* Update for Delay: '<S2>/Delay2' incorporates:
     *  Switch: '<S2>/Switch1'
     */
    uz_pmsm_model_DW.Delay2_DSTATE_l = rtb_Integrator;

    /* Update for RateTransition: '<Root>/Rate Transition2' */
    uz_pmsm_model_DW.RateTransition2_Buffer0 = rtb_Integrator_nb;

    /* Update for RateTransition: '<Root>/Rate Transition1' */
    uz_pmsm_model_DW.RateTransition1_Buffer0 = rtb_Integrator_j;

    /* Update for DiscreteIntegrator: '<S95>/Integrator' */
    uz_pmsm_model_DW.Integrator_DSTATE += 5.0E-5 * rtb_error_iq;

    /* Update for Delay: '<S1>/Delay1' */
    uz_pmsm_model_DW.Delay1_DSTATE = rtb_u_q;

    /* Update for Delay: '<S1>/Delay2' */
    uz_pmsm_model_DW.Delay2_DSTATE = rtb_u_d;

    /* Update for DiscreteIntegrator: '<S47>/Integrator' */
    uz_pmsm_model_DW.Integrator_DSTATE_e += 5.0E-5 * rtb_Gain2;

    /* Update for DiscreteIntegrator: '<S206>/Integrator' incorporates:
     *  DiscreteIntegrator: '<S158>/Integrator'
     *  Product: '<S203>/IProd Out'
     *  Sum: '<S2>/Sum3'
     */
    rtb_Integrator_j = (0.0 - rtb_iq_regler_fk) * rtb_Product1_i * 5.0E-5;
    uz_pmsm_model_DW.Integrator_DSTATE_c += rtb_Integrator_j;

    /* Update for DiscreteIntegrator: '<S158>/Integrator' */
    uz_pmsm_model_DW.Integrator_DSTATE_j += rtb_Integrator_j;
  }

  /* Matfile logging */
  rt_UpdateTXYLogVars(uz_pmsm_model_M->rtwLogInfo,
                      (&uz_pmsm_model_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [2.0E-6s, 0.0s] */
    if ((rtmGetTFinal(uz_pmsm_model_M)!=-1) &&
        !((rtmGetTFinal(uz_pmsm_model_M)-uz_pmsm_model_M->Timing.taskTime0) >
          uz_pmsm_model_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(uz_pmsm_model_M, "Simulation finished");
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
  if (!(++uz_pmsm_model_M->Timing.clockTick0)) {
    ++uz_pmsm_model_M->Timing.clockTickH0;
  }

  uz_pmsm_model_M->Timing.taskTime0 = uz_pmsm_model_M->Timing.clockTick0 *
    uz_pmsm_model_M->Timing.stepSize0 + uz_pmsm_model_M->Timing.clockTickH0 *
    uz_pmsm_model_M->Timing.stepSize0 * 4294967296.0;
  if (uz_pmsm_model_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [5.0E-5s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 5.0E-5, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    uz_pmsm_model_M->Timing.clockTick1++;
    if (!uz_pmsm_model_M->Timing.clockTick1) {
      uz_pmsm_model_M->Timing.clockTickH1++;
    }
  }

  rate_scheduler();
}

/* Model initialize function */
void uz_pmsm_model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)uz_pmsm_model_M, 0,
                sizeof(RT_MODEL_uz_pmsm_model_T));
  rtmSetTFinal(uz_pmsm_model_M, 0.049999999999999996);
  uz_pmsm_model_M->Timing.stepSize0 = 2.0E-6;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    uz_pmsm_model_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(uz_pmsm_model_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(uz_pmsm_model_M->rtwLogInfo, (NULL));
    rtliSetLogT(uz_pmsm_model_M->rtwLogInfo, "");
    rtliSetLogX(uz_pmsm_model_M->rtwLogInfo, "");
    rtliSetLogXFinal(uz_pmsm_model_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(uz_pmsm_model_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(uz_pmsm_model_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(uz_pmsm_model_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(uz_pmsm_model_M->rtwLogInfo, 1);
    rtliSetLogY(uz_pmsm_model_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(uz_pmsm_model_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(uz_pmsm_model_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &uz_pmsm_model_B), 0,
                sizeof(B_uz_pmsm_model_T));

  /* states (dwork) */
  (void) memset((void *)&uz_pmsm_model_DW, 0,
                sizeof(DW_uz_pmsm_model_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(uz_pmsm_model_M->rtwLogInfo, 0.0,
    rtmGetTFinal(uz_pmsm_model_M), uz_pmsm_model_M->Timing.stepSize0,
    (&rtmGetErrorStatus(uz_pmsm_model_M)));

  /* Start for RateTransition: '<Root>/Rate Transition2' */
  uz_pmsm_model_B.RateTransition2 = 0.0;

  /* Start for RateTransition: '<Root>/Rate Transition1' */
  uz_pmsm_model_B.RateTransition1 = 0.0;

  /* Start for RateTransition: '<S3>/Rate Transition5' */
  uz_pmsm_model_B.u_Fid1_Giq1 = 0.0F;

  /* Start for RateTransition: '<S3>/Rate Transition6' */
  uz_pmsm_model_B.u_Fid2_Giq2 = 0.0F;

  /* Start for RateTransition: '<S3>/Rate Transition19' */
  uz_pmsm_model_B.aq4_aq5 = 0.0F;

  /* Start for RateTransition: '<S3>/Rate Transition20' */
  uz_pmsm_model_B.aq1_aq2 = 0.0F;

  /* Start for RateTransition: '<S3>/Rate Transition21' */
  uz_pmsm_model_B.ad4_ad5 = 0.0F;

  /* Start for RateTransition: '<S3>/Rate Transition22' */
  uz_pmsm_model_B.ad1_ad2 = 0.0F;
  uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_f = UNINITIALIZED_ZCSIG;
  uz_pmsm_model_PrevZCX.Delay1_Reset_ZCE_i = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition2' */
  uz_pmsm_model_DW.RateTransition2_Buffer0 = 0.0;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition1' */
  uz_pmsm_model_DW.RateTransition1_Buffer0 = 0.0;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition5' */
  uz_pmsm_model_DW.RateTransition5_Buffer0 = 0.0F;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition6' */
  uz_pmsm_model_DW.RateTransition6_Buffer0 = 0.0F;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition19' */
  uz_pmsm_model_DW.RateTransition19_Buffer0 = 0.0F;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition20' */
  uz_pmsm_model_DW.RateTransition20_Buffer0 = 0.0F;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition21' */
  uz_pmsm_model_DW.RateTransition21_Buffer0 = 0.0F;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition22' */
  uz_pmsm_model_DW.RateTransition22_Buffer0 = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S95>/Integrator' */
  uz_pmsm_model_DW.Integrator_DSTATE = 0.0;

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  uz_pmsm_model_DW.Delay1_DSTATE = 0.0;

  /* InitializeConditions for Delay: '<S1>/Delay2' */
  uz_pmsm_model_DW.Delay2_DSTATE = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Integrator' */
  uz_pmsm_model_DW.Integrator_DSTATE_e = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S206>/Integrator' */
  uz_pmsm_model_DW.Integrator_DSTATE_c = 0.0;

  /* InitializeConditions for Delay: '<S2>/Delay1' */
  uz_pmsm_model_DW.Delay1_DSTATE_a = 0.0;

  /* InitializeConditions for Delay: '<S2>/Delay2' */
  uz_pmsm_model_DW.Delay2_DSTATE_l = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S158>/Integrator' */
  uz_pmsm_model_DW.Integrator_DSTATE_j = 0.0;

  /* InitializeConditions for Delay: '<S227>/Delay1' */
  uz_pmsm_model_DW.Delay1_DSTATE_j = 0.0F;

  /* InitializeConditions for Delay: '<S228>/Delay1' */
  uz_pmsm_model_DW.Delay1_DSTATE_e = 0.0F;

  /* InitializeConditions for Delay: '<S226>/Delay1' */
  uz_pmsm_model_DW.Delay1_DSTATE_n = 0.0F;

  /* InitializeConditions for Delay: '<S223>/Delay' */
  uz_pmsm_model_DW.Delay_DSTATE = 0.0F;

  /* End of SystemInitialize for SubSystem: '<Root>/uz_pmsm_model' */
}

/* Model terminate function */
void uz_pmsm_model_terminate(void)
{
  /* (no terminate code required) */
}
