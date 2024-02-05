/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_pmsm_rfe.c
 *
 * Code generated for Simulink model 'uz_pmsm_rfe'.
 *
 * Model version                  : 6.2
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Feb  5 22:51:29 2024
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
  real_T rtb_I_d;
  real_T rtb_Product;
  real_T rtb_xi_d;
  real_T rtb_xi_q;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  if (rtU->reset_integrator && (rtDW->DiscreteTimeIntegrator_PrevRese <= 0)) {
    rtDW->DiscreteTimeIntegrator_DSTATE = rtP.DiscreteTimeIntegrator_IC;
  }

  /* Gain: '<S1>/1//L_d' incorporates:
   *  Constant: '<S1>/Gesamtfluss PM'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Sum: '<S1>/Add3'
   */
  rtb_I_d = 1.0 / rtP.Ld * (rtDW->DiscreteTimeIntegrator_DSTATE - rtP.psi_pm);

  /* Sum: '<S1>/Add5' incorporates:
   *  Gain: '<S1>/1//Rc_d'
   *  Gain: '<S1>/Rs//Rc_d'
   */
  rtb_xi_d = (rtP.r_s / rtP.r_cd * rtb_I_d - rtP.uRc_d_Gain * rtU->U_d) +
    rtb_I_d;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  if (rtU->reset_integrator && (rtDW->DiscreteTimeIntegrator1_PrevRes <= 0)) {
    rtDW->DiscreteTimeIntegrator1_DSTATE = rtP.DiscreteTimeIntegrator1_IC;
  }

  /* Gain: '<S1>/1//L_q' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   */
  rtb_xi_q = 1.0 / rtP.Lq * rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S1>/Add6' incorporates:
   *  Gain: '<S1>/1//Rc_q'
   *  Gain: '<S1>/Rs//Rc_q'
   */
  rtb_Product = (rtP.r_s / rtP.r_cq * rtb_xi_q + rtb_xi_q) - rtP.uRc_q_Gain *
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
  rtY->Mi_ist = ((rtb_xi_d * rtP.Ld + rtP.psi_pm) * rtb_Product - rtb_xi_d *
                 rtb_Product * rtP.Lq) * (1.5 * rtP.PN);

  /* Outport: '<Root>/Mi_soll' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  Gain: '<S1>/1.5*Z_p'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product2'
   *  Sum: '<S1>/Add2'
   */
  rtY->Mi_soll = (rtDW->DiscreteTimeIntegrator_DSTATE * rtb_xi_q - rtb_I_d *
                  rtDW->DiscreteTimeIntegrator1_DSTATE) * (1.5 * rtP.PN);

  /* Outport: '<Root>/I_q' */
  rtY->I_q = rtb_xi_q;

  /* Sum: '<S1>/Add1' incorporates:
   *  Constant: '<S1>/L_d2'
   *  Constant: '<S1>/L_q2'
   *  Constant: '<S1>/q-Komponente Eisenwiderstand'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Gain: '<S1>/Statorwiderstand_q'
   *  Product: '<S1>/Divide1'
   *  Product: '<S1>/Product3'
   *  Product: '<S1>/Product7'
   */
  rtb_xi_d = ((rtU->U_q - rtDW->DiscreteTimeIntegrator_DSTATE * rtU->omega_el) -
              rtP.r_s * rtb_xi_q) - rtP.Ld * rtU->omega_el * rtU->omega_el /
    rtP.r_cd * rtb_xi_q * rtP.Lq;

  /* Product: '<S1>/Divide' incorporates:
   *  Constant: '<S1>/L_q1'
   *  Constant: '<S1>/d-Komponente Eisenwiderstand'
   */
  rtb_xi_q = rtP.Lq * rtU->omega_el * rtU->omega_el / rtP.r_cq;

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
   */
  rtDW->DiscreteTimeIntegrator_DSTATE += ((((rtU->omega_el *
    rtDW->DiscreteTimeIntegrator1_DSTATE - rtb_xi_q * rtP.psi_pm) - rtP.Ld *
    rtb_xi_q * rtb_I_d) - rtP.r_s * rtb_I_d) + rtU->U_d) *
    rtP.DiscreteTimeIntegrator_gainval;
  rtDW->DiscreteTimeIntegrator_PrevRese = (int8_T)rtU->reset_integrator;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE += rtP.DiscreteTimeIntegrator1_gainval *
    rtb_xi_d;
  rtDW->DiscreteTimeIntegrator1_PrevRes = (int8_T)rtU->reset_integrator;
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
  rtDW->DiscreteTimeIntegrator_DSTATE = rtP.DiscreteTimeIntegrator_IC;
  rtDW->DiscreteTimeIntegrator_PrevRese = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = rtP.DiscreteTimeIntegrator1_IC;
  rtDW->DiscreteTimeIntegrator1_PrevRes = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
