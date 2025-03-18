/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flussschaetzer.c
 *
 * Code generated for Simulink model 'Flussschaetzer'.
 *
 * Model version                  : 9.3
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Mar 18 09:51:14 2025
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
  int32_T k;
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1;
  real32_T b_accumulatedData;
  real32_T c_accumulatedData;
  real32_T rtb_Sum;
  real32_T rtb_Sum1;
  real32_T rtb_psi_alpha;
  real32_T rtb_psi_alpha_filt;
  real32_T rtb_psi_alpha_filt_a;
  real32_T rtb_psi_alpha_filt_h;
  real32_T rtb_psi_beta;
  real32_T rtb_theta_el_est;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Gain: '<S4>/Gain'
   */
  rtb_Sum1 = rtU->u_alphabeta[1] - rtP.Rs * rtU->i_alphabeta[1];

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  DiscreteTimeIntegrator = 2.5E-5F * rtb_Sum1 +
    rtDW->DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S4>/Sum3' incorporates:
   *  Gain: '<S4>/Gain2'
   */
  rtb_psi_beta = DiscreteTimeIntegrator - rtP.Ls * rtU->i_alphabeta[1];

  /* DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn1' */
  rtb_psi_alpha_filt_h = rtb_psi_beta - -0.998555899F *
    rtDW->DiscreteTransferFcn1_states;
  rtb_theta_el_est = 0.999277949F * rtb_psi_alpha_filt_h + -0.999277949F *
    rtDW->DiscreteTransferFcn1_states;

  /* Outport: '<Root>/psi_beta_filt' */
  rtY->psi_beta_filt = rtb_theta_el_est;

  /* Sum: '<S4>/Sum' incorporates:
   *  Gain: '<S4>/Gain1'
   */
  rtb_Sum = rtU->u_alphabeta[0] - rtP.Rs * rtU->i_alphabeta[0];

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 2.5E-5F * rtb_Sum +
    rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S4>/Sum2' incorporates:
   *  Gain: '<S4>/Gain3'
   */
  rtb_psi_alpha = DiscreteTimeIntegrator1 - rtP.Ls * rtU->i_alphabeta[0];

  /* DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn2' */
  rtb_psi_alpha_filt_a = rtb_psi_alpha - -0.998555899F *
    rtDW->DiscreteTransferFcn2_states;
  rtb_psi_alpha_filt = 0.999277949F * rtb_psi_alpha_filt_a + -0.999277949F *
    rtDW->DiscreteTransferFcn2_states;

  /* Trigonometry: '<S4>/Atan2' */
  rtb_theta_el_est = rt_atan2f_snf(rtb_theta_el_est, rtb_psi_alpha_filt);

  /* MATLAB Function: '<S2>/Regressionsverfahren_omega_el' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant5'
   *  Sum: '<S2>/Add3'
   */
  for (k = 0; k < 9; k++) {
    rtDW->theta_values[k] = rtDW->theta_values[k + 1];
  }

  rtDW->theta_values[9] = rtb_theta_el_est + 3.14159274F;
  for (k = 0; k < 10; k++) {
    rtDW->time_values[k] = ((real32_T)k + 1.0F) * rtP.Ts;
  }

  rtDW->accumulatedData = rtDW->time_values[0];
  b_accumulatedData = rtDW->theta_values[0];
  for (k = 0; k < 9; k++) {
    rtDW->accumulatedData += rtDW->time_values[k + 1];
    b_accumulatedData += rtDW->theta_values[k + 1];
  }

  rtDW->accumulatedData /= 10.0;
  b_accumulatedData /= 10.0F;
  for (k = 0; k < 10; k++) {
    rtDW->x_tmp_m = rtDW->time_values[k] - rtDW->accumulatedData;
    rtDW->x_tmp[k] = rtDW->x_tmp_m;
    rtDW->x[k] = (rtDW->theta_values[k] - b_accumulatedData) * (real32_T)
      rtDW->x_tmp_m;
  }

  b_accumulatedData = rtDW->x[0];
  for (k = 0; k < 9; k++) {
    b_accumulatedData += rtDW->x[k + 1];
  }

  for (k = 0; k < 10; k++) {
    rtDW->x_tmp_m = rtDW->x_tmp[k];
    rtDW->time_values[k] = rtDW->x_tmp_m * rtDW->x_tmp_m;
  }

  rtDW->accumulatedData = rtDW->time_values[0];
  c_accumulatedData = rtDW->omega_el_array[0];
  for (k = 0; k < 9; k++) {
    rtDW->accumulatedData += rtDW->time_values[k + 1];
    c_accumulatedData += rtDW->omega_el_array[k + 1];
  }

  b_accumulatedData /= (real32_T)rtDW->accumulatedData;
  if (!(fabsf(b_accumulatedData - c_accumulatedData / 10.0F) >= 50.0F)) {
    for (k = 0; k < 9; k++) {
      rtDW->omega_el_array[k] = rtDW->omega_el_array[k + 1];
    }

    rtDW->omega_el_array[9] = b_accumulatedData;
  }

  b_accumulatedData = rtDW->omega_el_array[0];
  for (k = 0; k < 9; k++) {
    b_accumulatedData += rtDW->omega_el_array[k + 1];
  }

  b_accumulatedData /= 10.0F;

  /* End of MATLAB Function: '<S2>/Regressionsverfahren_omega_el' */

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/negativ'
   *  Constant: '<S3>/positiv'
   */
  if (b_accumulatedData > 0.0F) {
    k = -1;
  } else {
    k = 1;
  }

  /* Outport: '<Root>/theta_el_kor' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Constant: '<S3>/Constant2'
   *  Math: '<S3>/Mod'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Sum4'
   *  Sum: '<S3>/Sum5'
   *  Switch: '<S3>/Switch'
   *  Trigonometry: '<S3>/Atan'
   */
  rtY->theta_el_kor = rt_modf_snf((1.57079637F - atanf(rtP.THP * fabsf
    (b_accumulatedData))) * (real32_T)k + rtb_theta_el_est, 6.28318548F);

  /* Outport: '<Root>/omega_m_est' */
  rtY->omega_m_est = b_accumulatedData;

  /* Outport: '<Root>/theta_el_est' */
  rtY->theta_el_est = rtb_theta_el_est;

  /* Outport: '<Root>/psi_alpha_filt' */
  rtY->psi_alpha_filt = rtb_psi_alpha_filt;

  /* Outport: '<Root>/psi_beta' */
  rtY->psi_beta = rtb_psi_alpha;

  /* Outport: '<Root>/psi_alpha' */
  rtY->psi_alpha = rtb_psi_beta;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE = 2.5E-5F * rtb_Sum1 +
    DiscreteTimeIntegrator;

  /* Update for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states = rtb_psi_alpha_filt_h;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 2.5E-5F * rtb_Sum +
    DiscreteTimeIntegrator1;

  /* Update for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn2' */
  rtDW->DiscreteTransferFcn2_states = rtb_psi_alpha_filt_a;
}

/* Model initialize function */
void Flussschaetzer_initialize(RT_MODEL_Flussschaetzer *const rtM)
{
  DW_Flussschaetzer *rtDW = rtM->dwork;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE = 1.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states = 1.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 1.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn2' */
  rtDW->DiscreteTransferFcn2_states = 1.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
