/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_pmsm_rfe.c
 *
 * Code generated for Simulink model 'uz_pmsm_rfe'.
 *
 * Model version                  : 6.0
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Feb  5 22:25:04 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "uz_pmsm_rfe.h"
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void uz_pmsm_rfe_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real_T rtb_Add5;
  real_T rtb_I_d;
  real_T rtb_I_q;
  real_T rtb_xi_q;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  if ((rtU->reset_integrator > 0.0) && (rtDW->DiscreteTimeIntegrator_PrevRese <=
       0)) {
    rtDW->DiscreteTimeIntegrator_DSTATE = 0.0;
  }

  /* Gain: '<S1>/1//L_d' incorporates:
   *  Constant: '<S1>/Gesamtfluss PM'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Sum: '<S1>/Add3'
   */
  rtb_I_d = (rtDW->DiscreteTimeIntegrator_DSTATE - 0.007) * 33333.333333333336;

  /* Sum: '<S1>/Add5' incorporates:
   *  Gain: '<S1>/1//Rc_d'
   *  Gain: '<S1>/Rs//Rc_d'
   */
  rtb_Add5 = (0.014063500861356533 * rtb_I_d - 0.61145655918941444 * rtU->U_d) +
    rtb_I_d;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  if ((rtU->reset_integrator > 0.0) && (rtDW->DiscreteTimeIntegrator1_PrevRes <=
       0)) {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* Gain: '<S1>/1//L_q' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   */
  rtb_I_q = 20000.0 * rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S1>/Add6' incorporates:
   *  Gain: '<S1>/1//Rc_q'
   *  Gain: '<S1>/Rs//Rc_q'
   */
  rtb_xi_q = (0.014063500861356533 * rtb_I_q + rtb_I_q) - 0.61145655918941444 *
    rtU->U_q;

  /* Outport: '<Root>/Mi_ist' incorporates:
   *  Constant: '<S1>/Gesamtfluss PM1'
   *  Constant: '<S1>/L_d3'
   *  Constant: '<S1>/L_q3'
   *  Gain: '<S1>/1.5*Z_p1'
   *  Product: '<S1>/Product6'
   *  Product: '<S1>/Product8'
   *  Product: '<S1>/Product9'
   *  Sum: '<S1>/Add4'
   *  Sum: '<S1>/Add7'
   */
  rtY->Mi_ist = ((rtb_Add5 * 3.0E-5 + 0.007) * rtb_xi_q - rtb_Add5 * rtb_xi_q *
                 5.0E-5) * 7.5;

  /* Outport: '<Root>/Mi_soll' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  Gain: '<S1>/1.5*Z_p'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product2'
   *  Sum: '<S1>/Add2'
   */
  rtY->Mi_soll = (rtDW->DiscreteTimeIntegrator_DSTATE * rtb_I_q - rtb_I_d *
                  rtDW->DiscreteTimeIntegrator1_DSTATE) * 7.5;

  /* Outport: '<Root>/I_q' */
  rtY->I_q = rtb_I_q;

  /* Product: '<S1>/Product3' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  rtb_Add5 = rtDW->DiscreteTimeIntegrator_DSTATE * rtU->omega_el;

  /* Product: '<S1>/Divide' incorporates:
   *  Constant: '<S1>/L_q1'
   *  Constant: '<S1>/d-Komponente Eisenwiderstand'
   */
  rtb_xi_q = 5.0E-5 * rtU->omega_el * rtU->omega_el / 1.63543915748596;

  /* Outport: '<Root>/I_d' */
  rtY->I_d = rtb_I_d;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S1>/Gesamtfluss PM'
   *  Constant: '<S1>/L_d1'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  Gain: '<S1>/Statorwiderstand_d'
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product4'
   *  Product: '<S1>/Product5'
   *  Sum: '<S1>/Add'
   * */
  rtDW->DiscreteTimeIntegrator_DSTATE += (((rtU->omega_el *
    rtDW->DiscreteTimeIntegrator1_DSTATE - rtb_xi_q * 0.007) - 3.0E-5 * rtb_xi_q
    * rtb_I_d) - 0.023 * rtb_I_d) + rtU->U_d;
  if (rtU->reset_integrator > 0.0) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 1;
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
  } else {
    if (rtU->reset_integrator < 0.0) {
      rtDW->DiscreteTimeIntegrator_PrevRese = -1;
    } else if (rtU->reset_integrator == 0.0) {
      rtDW->DiscreteTimeIntegrator_PrevRese = 0;
    } else {
      rtDW->DiscreteTimeIntegrator_PrevRese = 2;
    }

    if (rtU->reset_integrator < 0.0) {
      rtDW->DiscreteTimeIntegrator1_PrevRes = -1;
    } else if (rtU->reset_integrator == 0.0) {
      rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
    } else {
      rtDW->DiscreteTimeIntegrator1_PrevRes = 2;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S1>/L_d2'
   *  Constant: '<S1>/L_q2'
   *  Constant: '<S1>/q-Komponente Eisenwiderstand'
   *  Gain: '<S1>/Statorwiderstand_q'
   *  Product: '<S1>/Divide1'
   *  Product: '<S1>/Product7'
   *  Sum: '<S1>/Add1'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE += ((rtU->U_q - rtb_Add5) - 0.023 *
    rtb_I_q) - 3.0E-5 * rtU->omega_el * rtU->omega_el / 1.63543915748596 *
    rtb_I_q * 5.0E-5;
}

/* Model initialize function */
void uz_pmsm_rfe_initialize(RT_MODEL *const rtM)
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
  (void)memset(rtY, 0, sizeof(ExtY));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_PrevRese = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevRes = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
