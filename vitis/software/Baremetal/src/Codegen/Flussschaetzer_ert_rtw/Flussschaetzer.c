/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flussschaetzer.c
 *
 * Code generated for Simulink model 'Flussschaetzer'.
 *
 * Model version                  : 9.9
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Apr 14 16:27:27 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Flussschaetzer.h"
#include "../lib/rt_atan2f_snf.h"
#include <math.h>
#include "../lib/rt_modf_snf.h"
#include "../lib/rtwtypes.h"

/* Model step function */
void Flussschaetzer_step(RT_MODEL_Flussschaetzer *const rtM)
{
  DW_Flussschaetzer *rtDW = rtM->dwork;
  ExtU_Flussschaetzer *rtU = (ExtU_Flussschaetzer *) rtM->inputs;
  ExtY_Flussschaetzer *rtY = (ExtY_Flussschaetzer *) rtM->outputs;
  int32_T i;
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1;
  real32_T c_accumulatedData;
  real32_T rtb_Atan2;
  real32_T rtb_DiscreteTransferFcn1;
  real32_T rtb_DiscreteTransferFcn2;
  real32_T rtb_DiscreteTransferFcn2_f;
  real32_T rtb_DiscreteTransferFcn2_o;
  real32_T rtb_Sum;
  real32_T rtb_Sum1;
  real32_T rtb_Sum2;
  real32_T rtb_Sum3;
  boolean_T rtb_LogicalOperator;

  /* Logic: '<S7>/Logical Operator' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S7>/Time constant'
   *  RelationalOperator: '<S11>/Compare'
   *  Sum: '<S7>/Sum1'
   */
  rtb_LogicalOperator = ((real32_T)(0.0039788735772973835 - rtDW->Probe[0]) <=
    0.0F);

  /* Sum: '<S4>/Sum1' incorporates:
   *  Gain: '<S4>/Gain'
   */
  rtb_Sum1 = rtU->u_alphabeta[1] - rtP.Rs * rtU->i_alphabeta[1];

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  if ((rtU->integrator_reset != 0.0F) || (rtDW->DiscreteTimeIntegrator_PrevRese
       != 0)) {
    rtDW->DiscreteTimeIntegrator_DSTATE = 0.0F;
  }

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  DiscreteTimeIntegrator = 2.5E-5F * rtb_Sum1 +
    rtDW->DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S4>/Sum3' incorporates:
   *  Gain: '<S4>/Gain2'
   */
  rtb_Sum3 = DiscreteTimeIntegrator - rtP.Ls * rtU->i_alphabeta[1];

  /* DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn1' */
  rtb_DiscreteTransferFcn2_o = rtb_Sum3 - -0.998430431F *
    rtDW->DiscreteTransferFcn1_states;
  rtb_DiscreteTransferFcn1 = 0.999215245F * rtb_DiscreteTransferFcn2_o +
    -0.999215245F * rtDW->DiscreteTransferFcn1_states;

  /* Sum: '<S4>/Sum' incorporates:
   *  Gain: '<S4>/Gain1'
   */
  rtb_Sum = rtU->u_alphabeta[0] - rtP.Rs * rtU->i_alphabeta[0];

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  if ((rtU->integrator_reset != 0.0F) || (rtDW->DiscreteTimeIntegrator1_PrevRes
       != 0)) {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;
  }

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 2.5E-5F * rtb_Sum +
    rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S4>/Sum2' incorporates:
   *  Gain: '<S4>/Gain3'
   */
  rtb_Sum2 = DiscreteTimeIntegrator1 - rtP.Ls * rtU->i_alphabeta[0];

  /* DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn2' */
  rtb_DiscreteTransferFcn2_f = rtb_Sum2 - -0.998430431F *
    rtDW->DiscreteTransferFcn2_states;
  rtb_DiscreteTransferFcn2 = 0.999215245F * rtb_DiscreteTransferFcn2_f +
    -0.999215245F * rtDW->DiscreteTransferFcn2_states;

  /* Trigonometry: '<S4>/Atan2' */
  rtb_Atan2 = rt_atan2f_snf(rtb_DiscreteTransferFcn1, rtb_DiscreteTransferFcn2);

  /* MATLAB Function: '<S2>/Regressionsverfahren_omega_el' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant5'
   *  Sum: '<S2>/Add3'
   */
  for (i = 0; i < 9; i++) {
    rtDW->theta_values[i] = rtDW->theta_values[i + 1];
  }

  rtDW->theta_values[9] = rtb_Atan2 + 3.14159274F;
  for (i = 0; i < 10; i++) {
    rtDW->time_values[i] = ((real32_T)i + 1.0F) * rtP.Ts;
  }

  rtDW->accumulatedData = rtDW->time_values[0];
  rtDW->b_accumulatedData = rtDW->theta_values[0];
  for (i = 0; i < 9; i++) {
    rtDW->accumulatedData += rtDW->time_values[i + 1];
    rtDW->b_accumulatedData += rtDW->theta_values[i + 1];
  }

  rtDW->accumulatedData /= 10.0;
  rtDW->b_accumulatedData /= 10.0F;
  for (i = 0; i < 10; i++) {
    rtDW->x_tmp_m = rtDW->time_values[i] - rtDW->accumulatedData;
    rtDW->x_tmp[i] = rtDW->x_tmp_m;
    rtDW->x[i] = (rtDW->theta_values[i] - rtDW->b_accumulatedData) * (real32_T)
      rtDW->x_tmp_m;
  }

  rtDW->b_accumulatedData = rtDW->x[0];
  for (i = 0; i < 9; i++) {
    rtDW->b_accumulatedData += rtDW->x[i + 1];
  }

  for (i = 0; i < 10; i++) {
    rtDW->x_tmp_m = rtDW->x_tmp[i];
    rtDW->time_values[i] = rtDW->x_tmp_m * rtDW->x_tmp_m;
  }

  rtDW->accumulatedData = rtDW->time_values[0];
  for (i = 0; i < 9; i++) {
    rtDW->accumulatedData += rtDW->time_values[i + 1];
  }

  rtDW->b_accumulatedData /= (real32_T)rtDW->accumulatedData;
  if (rtU->integrator_reset == 1.0F) {
    for (i = 0; i < 10; i++) {
      rtDW->omega_el_array[i] = 0.0F;
    }
  } else {
    c_accumulatedData = rtDW->omega_el_array[0];
    for (i = 0; i < 9; i++) {
      c_accumulatedData += rtDW->omega_el_array[i + 1];
    }

    if (!(fabsf(rtDW->b_accumulatedData - c_accumulatedData / 10.0F) >= 50.0F))
    {
      for (i = 0; i < 9; i++) {
        rtDW->omega_el_array[i] = rtDW->omega_el_array[i + 1];
      }

      rtDW->omega_el_array[9] = rtDW->b_accumulatedData;
    }
  }

  rtDW->b_accumulatedData = rtDW->omega_el_array[0];
  for (i = 0; i < 9; i++) {
    rtDW->b_accumulatedData += rtDW->omega_el_array[i + 1];
  }

  rtDW->b_accumulatedData /= 10.0F;

  /* End of MATLAB Function: '<S2>/Regressionsverfahren_omega_el' */

  /* DiscreteIntegrator: '<S13>/Integrator' */
  if (rtDW->Integrator_IC_LOADING != 0) {
    rtDW->Integrator_DSTATE = rtDW->b_accumulatedData;
  }

  if (rtb_LogicalOperator || (rtDW->Integrator_PrevResetState != 0)) {
    rtDW->Integrator_DSTATE = rtDW->b_accumulatedData;
  }

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/negativ'
   *  Constant: '<S3>/positiv'
   *  DiscreteIntegrator: '<S13>/Integrator'
   */
  if (rtDW->Integrator_DSTATE > 0.0F) {
    i = -1;
  } else {
    i = 1;
  }

  /* Outport: '<Root>/theta_el_kor' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Constant: '<S3>/Constant2'
   *  DiscreteIntegrator: '<S13>/Integrator'
   *  Math: '<S3>/Mod'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Sum4'
   *  Sum: '<S3>/Sum5'
   *  Switch: '<S3>/Switch'
   *  Trigonometry: '<S3>/Atan'
   */
  rtY->theta_el_kor = rt_modf_snf((1.57079637F - atanf(rtP.THP * fabsf
    (rtDW->Integrator_DSTATE))) * (real32_T)i + rtb_Atan2, 6.28318548F);

  /* Outport: '<Root>/omega_m_est' incorporates:
   *  DiscreteIntegrator: '<S13>/Integrator'
   *  Gain: '<S2>/Gain'
   */
  rtY->omega_m_est = 0.333333343F * rtDW->Integrator_DSTATE;

  /* Outport: '<Root>/omega_el_raw' */
  rtY->omega_el_raw = rtDW->b_accumulatedData;

  /* Outport: '<Root>/theta_el_est' */
  rtY->theta_el_est = rtb_Atan2;

  /* Outport: '<Root>/psi_alpha_filt' */
  rtY->psi_alpha_filt = rtb_DiscreteTransferFcn2;

  /* Outport: '<Root>/psi_alpha' */
  rtY->psi_alpha = rtb_Sum2;

  /* Outport: '<Root>/psi_beta_filt' */
  rtY->psi_beta_filt = rtb_DiscreteTransferFcn1;

  /* Outport: '<Root>/psi_beta' */
  rtY->psi_beta = rtb_Sum3;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
   */
  rtDW->DiscreteTimeIntegrator_DSTATE = 2.5E-5F * rtb_Sum1 +
    DiscreteTimeIntegrator;
  if (rtU->integrator_reset > 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 1;
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
  } else if (rtU->integrator_reset < 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = -1;
    rtDW->DiscreteTimeIntegrator1_PrevRes = -1;
  } else if (rtU->integrator_reset == 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 0;
    rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
  } else {
    rtDW->DiscreteTimeIntegrator_PrevRese = 2;
    rtDW->DiscreteTimeIntegrator1_PrevRes = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */

  /* Update for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states = rtb_DiscreteTransferFcn2_o;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 2.5E-5F * rtb_Sum +
    DiscreteTimeIntegrator1;

  /* Update for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn2' */
  rtDW->DiscreteTransferFcn2_states = rtb_DiscreteTransferFcn2_f;

  /* Update for DiscreteIntegrator: '<S13>/Integrator' incorporates:
   *  Constant: '<S7>/Time constant'
   *  MinMax: '<S7>/Max'
   *  Product: '<S5>/1//T'
   *  Sum: '<S5>/Sum1'
   */
  rtDW->Integrator_IC_LOADING = 0U;
  rtDW->Integrator_DSTATE += 1.0F / (real32_T)fmax(rtDW->Probe[0],
    0.0039788735772973835) * (rtDW->b_accumulatedData - rtDW->Integrator_DSTATE)
    * 5.0E-5F;
  rtDW->Integrator_PrevResetState = (int8_T)rtb_LogicalOperator;
}

/* Model initialize function */
void Flussschaetzer_initialize(RT_MODEL_Flussschaetzer *const rtM)
{
  DW_Flussschaetzer *rtDW = rtM->dwork;

  /* Start for Probe: '<S7>/Probe' */
  rtDW->Probe[0] = 5.0E-5F;
  rtDW->Probe[1] = 0.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states = 1.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn2' */
  rtDW->DiscreteTransferFcn2_states = 1.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Integrator' */
  rtDW->Integrator_IC_LOADING = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
