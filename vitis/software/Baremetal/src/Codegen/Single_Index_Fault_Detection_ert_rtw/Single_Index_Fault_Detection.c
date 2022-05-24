/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Single_Index_Fault_Detection.c
 *
 * Code generated for Simulink model 'Single_Index_Fault_Detection'.
 *
 * Model version                  : 3.4
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May 24 14:21:41 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "Single_Index_Fault_Detection.h"

/* Model step function */
void Single_Index_Fault_Detection_step(RT_MODEL_Single_Index_Fault_Det *const
  rtM_Single_Index_Fault_Detecti)
{
  DW_Single_Index_Fault_Detection *rtDW_Single_Index_Fault_Detecti =
    rtM_Single_Index_Fault_Detecti->dwork;
  ExtU_Single_Index_Fault_Detecti *rtU_Single_Index_Fault_Detectio =
    (ExtU_Single_Index_Fault_Detecti *) rtM_Single_Index_Fault_Detecti->inputs;
  ExtY_Single_Index_Fault_Detecti *rtY_Single_Index_Fault_Detectio =
    (ExtY_Single_Index_Fault_Detecti *) rtM_Single_Index_Fault_Detecti->outputs;
  real_T B;
  real_T rtb_Ro;

  /* MATLAB Function: '<S1>/Single_Index' incorporates:
   *  Inport: '<Root>/i_ab_xy_z1z2'
   */
  /* MATLAB Function 'Single_Index_Fault_Detection/Single_Index': '<S4>:1' */
  /* https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8948312&tag=1 */
  /* '<S4>:1:5' A= i_x*i_x+i_y*i_y; */
  /* '<S4>:1:6' B= i_a*i_a+i_b*i_b; */
  B = rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[0] *
    rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[0] +
    rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[1] *
    rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[1];

  /* '<S4>:1:9' if B == 0 */
  if (B == 0.0) {
    /* '<S4>:1:10' R=0; */
    B = 0.0;
  } else {
    /* '<S4>:1:11' else */
    /* '<S4>:1:12' R=A/B; */
    B = (rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[2] *
         rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[2] +
         rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[3] *
         rtU_Single_Index_Fault_Detectio->i_ab_xy_z1z2[3]) / B;
  }

  /* End of MATLAB Function: '<S1>/Single_Index' */

  /* MATLAB Function: '<S1>/HystereseBand1' incorporates:
   *  Inport: '<Root>/HB_Wert'
   */
  /*  if (1-e <= Ri) & (Ri <= 1+e)      %das funktioniert nicht für einen Vektor */
  /*      Ro = Ri; */
  /*  else */
  /*      Ro = 0; */
  /*  end */
  /* MATLAB Function 'Single_Index_Fault_Detection/HystereseBand1': '<S3>:1' */
  /* Hystereseband, Ausgang Ro ist gleich Ri falls Ri im Bereich von +-e um 1 */
  /* ist, ansonsten ist Ro = 0 */
  /* '<S3>:1:12' X = ((1-e <= Ri) & (Ri <= 1+e)); */
  /* '<S3>:1:13' Ro = X.*Ri; */
  rtb_Ro = (real_T)((1.0 - rtU_Single_Index_Fault_Detectio->HB_Wert <= B) && (B <=
    rtU_Single_Index_Fault_Detectio->HB_Wert + 1.0)) * B;

  /* Outport: '<Root>/FD_filtered' incorporates:
   *  Gain: '<S5>/C'
   *  Gain: '<S5>/D'
   *  Sum: '<S5>/sum1'
   *  UnitDelay: '<S5>/Delay_x'
   */
  rtY_Single_Index_Fault_Detectio->FD_filtered = 0.0099013168773229958 * rtb_Ro
    + 9.900986831226771E-5 * rtDW_Single_Index_Fault_Detecti->Delay_x_DSTATE;

  /* Outport: '<Root>/FD_hyst' */
  rtY_Single_Index_Fault_Detectio->FD_hyst = rtb_Ro;

  /* Outport: '<Root>/FD_raw' */
  rtY_Single_Index_Fault_Detectio->FD_raw = B;

  /* Update for UnitDelay: '<S5>/Delay_x' incorporates:
   *  Gain: '<S5>/A'
   *  Gain: '<S5>/B'
   *  Sum: '<S5>/A*x(k) + B*u(k)'
   */
  rtDW_Single_Index_Fault_Detecti->Delay_x_DSTATE = 0.980197366245354 *
    rtDW_Single_Index_Fault_Detecti->Delay_x_DSTATE + 198.0263375464599 * rtb_Ro;
}

/* Model initialize function */
void Single_Index_Fault_Detection_initialize(RT_MODEL_Single_Index_Fault_Det *
  const rtM_Single_Index_Fault_Detecti)
{
  DW_Single_Index_Fault_Detection *rtDW_Single_Index_Fault_Detecti =
    rtM_Single_Index_Fault_Detecti->dwork;
  ExtU_Single_Index_Fault_Detecti *rtU_Single_Index_Fault_Detectio =
    (ExtU_Single_Index_Fault_Detecti *) rtM_Single_Index_Fault_Detecti->inputs;
  ExtY_Single_Index_Fault_Detecti *rtY_Single_Index_Fault_Detectio =
    (ExtY_Single_Index_Fault_Detecti *) rtM_Single_Index_Fault_Detecti->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW_Single_Index_Fault_Detecti, 0,
                sizeof(DW_Single_Index_Fault_Detection));

  /* external inputs */
  (void)memset(rtU_Single_Index_Fault_Detectio, 0, sizeof
               (ExtU_Single_Index_Fault_Detecti));

  /* external outputs */
  (void)memset(rtY_Single_Index_Fault_Detectio, 0, sizeof
               (ExtY_Single_Index_Fault_Detecti));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
