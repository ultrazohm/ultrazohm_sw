/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen_pos_to_speed_pll.c
 *
 * Code generated for Simulink model 'uz_codegen_pos_to_speed_pll'.
 *
 * Model version                  : 6.4
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Dec  4 15:17:18 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "uz_codegen_pos_to_speed_pll.h"
#include <math.h>
#include "rtwtypes.h"

/* Model step function */
void uz_codegen_pos_to_speed_pll_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T rtb_dphi1;
  real32_T rtb_phi_me_p;

  /* Sum: '<S6>/dphi1' incorporates:
   *  Memory: '<S3>/Memory'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  Trigonometry: '<S2>/cos'
   *  Trigonometry: '<S2>/sin'
   */
  rtb_dphi1 = sinf(rtU->position_mech_SI) * rtDW->Memory_PreviousInput[0] - cosf
    (rtU->position_mech_SI) * rtDW->Memory_PreviousInput[1];

  /* Sum: '<S4>/phi_me' incorporates:
   *  Delay: '<S4>/Delay1'
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
  if ((rtb_phi_me_p >= 6.28318548F) || (rtb_phi_me_p < 0.0F)) {
    /* Sum: '<S4>/Sum1' incorporates:
     *  Product: '<S4>/Divide'
     *  Product: '<S4>/Product'
     *  Rounding: '<S4>/Floor'
     */
    rtb_phi_me_p -= floorf(rtb_phi_me_p / 6.28318548F) * 6.28318548F;

    /* Switch: '<S4>/Switch1' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Logic: '<S4>/AND1'
     *  RelationalOperator: '<S4>/Relational Operator2'
     *  RelationalOperator: '<S4>/Relational Operator3'
     *  Sum: '<S4>/Sum'
     */
    if ((rtb_phi_me_p >= 6.28318548F) || (rtb_phi_me_p < 0.0F)) {
      rtb_phi_me_p += 6.28318548F;
    }

    /* End of Switch: '<S4>/Switch1' */
  }

  /* End of Switch: '<S4>/Switch' */

  /* Outport: '<Root>/omega_mech' incorporates:
   *  Memory: '<S5>/Memory'
   */
  rtY->omega_mech = rtDW->Memory_PreviousInput_g;

  /* Outport: '<Root>/omega_el' incorporates:
   *  Memory: '<S5>/Memory'
   *  Product: '<S2>/Product'
   */
  rtY->omega_el = rtDW->Memory_PreviousInput_g * rtU->pole_pairs;

  /* Update for Memory: '<S3>/Memory' incorporates:
   *  Trigonometry: '<S7>/cos'
   *  Trigonometry: '<S7>/sin'
   */
  rtDW->Memory_PreviousInput[0] = cosf(rtb_phi_me_p);
  rtDW->Memory_PreviousInput[1] = sinf(rtb_phi_me_p);

  /* Update for Memory: '<S5>/Memory' incorporates:
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
void uz_codegen_pos_to_speed_pll_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;

  /* InitializeConditions for Memory: '<S3>/Memory' */
  rtDW->Memory_PreviousInput[0] = 1.0F;
  rtDW->Memory_PreviousInput[1] = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
