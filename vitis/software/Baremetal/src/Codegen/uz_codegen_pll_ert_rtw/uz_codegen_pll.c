/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen_pll.c
 *
 * Code generated for Simulink model 'uz_codegen_pll'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Apr 14 16:44:06 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "uz_codegen_pll.h"

extern real_T rt_modd(real_T u0, real_T u1);
real_T rt_modd(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  boolean_T yEq;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else {
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      q = fabs(u0 / u1);
      yEq = (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q);
    }

    if (yEq) {
      y = 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Model step function */
void uz_codegen_pll_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real_T rtb_dphi1;
  real_T rtb_phi_me_p;

  /* Sum: '<S6>/dphi1' incorporates:
   *  Inport: '<Root>/position_mech_SI'
   *  Memory: '<S3>/Memory'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  Trigonometry: '<S2>/cos'
   *  Trigonometry: '<S2>/sin'
   */
  rtb_dphi1 = sin(rtU->position_mech_SI) * rtDW->Memory_PreviousInput[0] - cos
    (rtU->position_mech_SI) * rtDW->Memory_PreviousInput[1];

  /* Sum: '<S4>/phi_me' incorporates:
   *  Delay: '<S4>/Delay1'
   *  Inport: '<Root>/kp_pll'
   *  Inport: '<Root>/sampling_time_seconds'
   *  Memory: '<S5>/Memory'
   *  Product: '<S4>/Product5'
   *  Product: '<S5>/Product1'
   *  Sum: '<S5>/Sum_om'
   */
  rtb_phi_me_p = (rtb_dphi1 * rtU->kp_pll + rtDW->Memory_PreviousInput_g) *
    rtU->sampling_time_seconds + rtDW->Delay1_DSTATE;

  /* Switch: '<S4>/Switch' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Logic: '<S4>/AND'
   *  RelationalOperator: '<S4>/Relational Operator'
   *  RelationalOperator: '<S4>/Relational Operator1'
   */
  if ((rtb_phi_me_p >= 6.2831853071795862) || (rtb_phi_me_p < 0.0)) {
    /* Sum: '<S4>/Sum1' incorporates:
     *  Product: '<S4>/Divide'
     *  Product: '<S4>/Product'
     *  Rounding: '<S4>/Floor'
     */
    rtb_phi_me_p -= floor(rtb_phi_me_p / 6.2831853071795862) *
      6.2831853071795862;

    /* Switch: '<S4>/Switch1' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Logic: '<S4>/AND1'
     *  RelationalOperator: '<S4>/Relational Operator2'
     *  RelationalOperator: '<S4>/Relational Operator3'
     *  Sum: '<S4>/Sum'
     */
    if ((rtb_phi_me_p >= 6.2831853071795862) || (rtb_phi_me_p < 0.0)) {
      rtb_phi_me_p += 6.2831853071795862;
    }

    /* End of Switch: '<S4>/Switch1' */
  }

  /* End of Switch: '<S4>/Switch' */

  /* Outport: '<Root>/omega_mech' incorporates:
   *  Memory: '<S5>/Memory'
   */
  rtY->omega_mech = rtDW->Memory_PreviousInput_g;

  /* Outport: '<Root>/omega_el' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/pole_pairs'
   *  Math: '<S2>/Mod'
   *  Memory: '<S5>/Memory'
   *  Product: '<S2>/Product'
   */
  rtY->omega_el = rt_modd(rtDW->Memory_PreviousInput_g * rtU->pole_pairs,
    6.2831853071795862);

  /* Update for Memory: '<S3>/Memory' incorporates:
   *  Trigonometry: '<S7>/cos'
   *  Trigonometry: '<S7>/sin'
   */
  rtDW->Memory_PreviousInput[0] = cos(rtb_phi_me_p);
  rtDW->Memory_PreviousInput[1] = sin(rtb_phi_me_p);

  /* Update for Memory: '<S5>/Memory' incorporates:
   *  Inport: '<Root>/ki_pll'
   *  Inport: '<Root>/sampling_time_seconds'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product6'
   *  Sum: '<S5>/Sum2'
   */
  rtDW->Memory_PreviousInput_g += rtU->ki_pll * rtb_dphi1 *
    rtU->sampling_time_seconds;

  /* Update for Delay: '<S4>/Delay1' */
  rtDW->Delay1_DSTATE = rtb_phi_me_p;
}

/* Model initialize function */
void uz_codegen_pll_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));

  /* InitializeConditions for Memory: '<S3>/Memory' */
  rtDW->Memory_PreviousInput[0] = 1.0;
  rtDW->Memory_PreviousInput[1] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
