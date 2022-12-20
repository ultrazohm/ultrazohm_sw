/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VSD_FD_6PH_V7.c
 *
 * Code generated for Simulink model 'VSD_FD_6PH_V7'.
 *
 * Model version                  : 3.9
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Jun 15 09:54:43 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "VSD_FD_6PH_V7.h"

/* Model step function */
void VSD_FD_6PH_V7_step(RT_MODEL_VSD_FD_6PH_V7 *const rtM_VSD_FD_6PH_V7)
{
  DW_VSD_FD_6PH_V7 *rtDW_VSD_FD_6PH_V7 = rtM_VSD_FD_6PH_V7->dwork;
  ExtU_VSD_FD_6PH_V7 *rtU_VSD_FD_6PH_V7 = (ExtU_VSD_FD_6PH_V7 *)
    rtM_VSD_FD_6PH_V7->inputs;
  ExtY_VSD_FD_6PH_V7 *rtY_VSD_FD_6PH_V7 = (ExtY_VSD_FD_6PH_V7 *)
    rtM_VSD_FD_6PH_V7->outputs;
  real_T R1;
  real_T R2;
  real_T R3;
  real_T denum;
  int32_T i;
  boolean_T rtb_R2_4h;

  /* MATLAB Function: '<S1>/Fehlerindexe_asym_6Ph' incorporates:
   *  Inport: '<Root>/i_ab_xy_z1z2'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  /* MATLAB Function 'VSD_FD_6PH_V7/Fehlerindexe_asym_6Ph': '<S2>:1' */
  /* OPF-Fehlerindexe nach Duran: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7858758&tag=1 */
  /* '<S2>:1:5' denum = 0; */
  /* -------------------------------------------------------------------------% */
  /*  Phase a */
  /* '<S2>:1:9' denum = (i_a+i_z1); */
  denum = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0] + rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[4];

  /* '<S2>:1:10' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:11' R1 = 0; */
    rtDW_VSD_FD_6PH_V7->R[0] = 0.0;
  } else {
    /* '<S2>:1:12' else */
    /* '<S2>:1:13' R1 = -i_x/denum; */
    rtDW_VSD_FD_6PH_V7->R[0] = -rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2] / denum;
  }

  /* -------------------------------------------------------------------------% */
  /*  Phase b */
  /* '<S2>:1:18' denum = (-i_a+sqrt(3)*i_b-sqrt(3)*i_y+2*i_z1); */
  R2 = 1.7320508075688772 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1] +
    -rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0];
  R1 = (R2 - 1.7320508075688772 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3]) + 2.0 *
    rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[4];

  /* '<S2>:1:19' if denum == 0 */
  if (R1 == 0.0) {
    /* '<S2>:1:20' R2 = 0; */
    rtDW_VSD_FD_6PH_V7->R[1] = 0.0;
  } else {
    /* '<S2>:1:21' else */
    /* '<S2>:1:22' R2 = i_x/denum; */
    rtDW_VSD_FD_6PH_V7->R[1] = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2] / R1;
  }

  /* -------------------------------------------------------------------------% */
  /*  Phase c */
  /* '<S2>:1:27' denum = (-i_a-sqrt(3)*i_b+sqrt(3)*i_y+2*i_z1); */
  denum = ((-rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0] - 1.7320508075688772 *
            rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1]) + 1.7320508075688772 *
           rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3]) + 2.0 *
    rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[4];

  /* '<S2>:1:28' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:29' R3 = 0; */
    rtDW_VSD_FD_6PH_V7->R[2] = 0.0;
  } else {
    /* '<S2>:1:30' else */
    /* '<S2>:1:31' R3 = i_x/denum; */
    rtDW_VSD_FD_6PH_V7->R[2] = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2] / denum;
  }

  /* -------------------------------------------------------------------------% */
  /*  Phase d */
  /* '<S2>:1:36' denum = (i_a+1/sqrt(3)*i_b + 1/sqrt(3) * i_y+2/sqrt(3) *i_z2); */
  denum = ((0.57735026918962584 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1] +
            rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0]) + 0.57735026918962584 *
           rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3]) + 1.1547005383792517 *
    rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[5];

  /* '<S2>:1:37' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:38' R4 = 0; */
    rtDW_VSD_FD_6PH_V7->R[3] = 0.0;
  } else {
    /* '<S2>:1:39' else */
    /* '<S2>:1:40' R4 = i_x/denum; */
    rtDW_VSD_FD_6PH_V7->R[3] = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2] / denum;
  }

  /* -------------------------------------------------------------------------% */
  /*  Phase e */
  /* '<S2>:1:45' denum = (i_a-1/sqrt(3)*i_b-1/sqrt(3)*i_y-2/sqrt(3)*i_z2); */
  denum = ((rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0] - 0.57735026918962584 *
            rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1]) - 0.57735026918962584 *
           rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3]) - 1.1547005383792517 *
    rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[5];

  /* '<S2>:1:46' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:47' R5 = 0; */
    rtDW_VSD_FD_6PH_V7->R[4] = 0.0;
  } else {
    /* '<S2>:1:48' else */
    /* '<S2>:1:49' R5 = i_x/denum; */
    rtDW_VSD_FD_6PH_V7->R[4] = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2] / denum;
  }

  /* -------------------------------------------------------------------------% */
  /*  Phase f */
  /* '<S2>:1:54' denum = (i_b-i_z2); */
  denum = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1] - rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[5];

  /* '<S2>:1:55' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:56' R6 = 0; */
    rtDW_VSD_FD_6PH_V7->R[5] = 0.0;
  } else {
    /* '<S2>:1:57' else */
    /* '<S2>:1:58' R6 = -i_y/denum; */
    rtDW_VSD_FD_6PH_V7->R[5] = -rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3] / denum;
  }

  /* End of MATLAB Function: '<S1>/Fehlerindexe_asym_6Ph' */
  /* '<S2>:1:61' R=[R1; R2; R3; R4; R5; R6]; */
  /* MATLAB Function 'VSD_FD_6PH_V7/HystereseBand': '<S5>:1' */
  /*  Hystereseband, Ausgang Ro ist gleich Ri falls Ri im Bereich von +-e um 1 */
  /*  ist, ansonsten ist Ro = 0 */
  /* '<S5>:1:6' X = ((1-e_u <= Ri) & (Ri <= 1+e_o)); */
  /* '<S5>:1:7' Ro = X.*Ri; */
  for (i = 0; i < 6; i++) {
    /* MATLAB Function: '<S1>/HystereseBand' incorporates:
     *  Inport: '<Root>/HB_o'
     *  Inport: '<Root>/HB_u'
     */
    denum = rtDW_VSD_FD_6PH_V7->R[i];
    R3 = (real_T)((1.0 - rtU_VSD_FD_6PH_V7->HB_u <= denum) && (denum <=
      rtU_VSD_FD_6PH_V7->HB_o + 1.0)) * denum;

    /* Outport: '<Root>/FD_filtered' incorporates:
     *  Gain: '<S7>/C'
     *  Gain: '<S7>/D'
     *  Sum: '<S7>/sum1'
     *  UnitDelay: '<S7>/Delay_x'
     */
    rtY_VSD_FD_6PH_V7->FD_filtered[i] = 0.0099013168773229958 * R3 +
      9.900986831226771E-5 * rtDW_VSD_FD_6PH_V7->Delay_x_DSTATE[i];

    /* Outport: '<Root>/FD_hyst' */
    rtY_VSD_FD_6PH_V7->FD_hyst[i] = R3;

    /* Outport: '<Root>/FD_raw' */
    rtY_VSD_FD_6PH_V7->FD_raw[i] = denum;

    /* MATLAB Function: '<S1>/HystereseBand' */
    rtDW_VSD_FD_6PH_V7->Ro[i] = R3;
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/HB_o'
   *  Inport: '<Root>/HB_u'
   *  Inport: '<Root>/i_ab_xy_z1z2'
   */
  /* MATLAB Function 'VSD_FD_6PH_V7/MATLAB Function': '<S6>:1' */
  /* '<S6>:1:3' denum = 0; */
  /* '<S6>:1:5' denum = (-i_a+sqrt(3)*i_b-sqrt(3)*i_y+2*i_z1); */
  /* '<S6>:1:6' if denum == 0 */
  if (R1 == 0.0) {
    /* '<S6>:1:7' R2_0 = 0; */
    R1 = 0.0;
  } else {
    /* '<S6>:1:8' else */
    /* '<S6>:1:9' R2_0 = i_x/denum; */
    R1 = rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2] / R1;
  }

  /* '<S6>:1:12' denum = (-i_a + sqrt(3)*i_b); */
  /* '<S6>:1:13' if denum == 0 */
  if (R2 == 0.0) {
    /* '<S6>:1:14' R2_1 = 0; */
    R2 = 0.0;
  } else {
    /* '<S6>:1:15' else */
    /* '<S6>:1:16' R2_1 = (i_x + sqrt(3)*i_y ) / denum; */
    R2 = (1.7320508075688772 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3] +
          rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2]) / R2;
  }

  /* '<S6>:1:19' denum = (-i_a); */
  /* '<S6>:1:20' if denum == 0 */
  if (-rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0] == 0.0) {
    /* '<S6>:1:21' R2_2 = 0; */
    R3 = 0.0;
  } else {
    /* '<S6>:1:22' else */
    /* '<S6>:1:23' R2_2 = (i_x + sqrt(3)*i_y - sqrt(3)*i_b) / denum; */
    R3 = ((1.7320508075688772 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3] +
           rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2]) - 1.7320508075688772 *
          rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1]) / -rtU_VSD_FD_6PH_V7->
      i_ab_xy_z1z2[0];
  }

  /* '<S6>:1:26' denum = (sqrt(3)*i_b - sqrt(3)*i_y ); */
  denum = 1.7320508075688772 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[1] -
    1.7320508075688772 * rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[3];

  /* '<S6>:1:27' if denum == 0 */
  if (denum == 0.0) {
    /* '<S6>:1:28' R2_3 = 0; */
    denum = 0.0;
  } else {
    /* '<S6>:1:29' else */
    /* '<S6>:1:30' R2_3 = (i_x + i_a) / denum; */
    denum = (rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[0] +
             rtU_VSD_FD_6PH_V7->i_ab_xy_z1z2[2]) / denum;
  }

  /* Hysterese: */
  /* '<S6>:1:34' R2_0_h = ((1-e_u <= R2_0) & (R2_0 <= 1+e_o)); */
  /* '<S6>:1:35' R2_1_h = ((1-e_u <= R2_1) & (R2_1 <= 1+e_o)); */
  /* '<S6>:1:36' R2_2_h = ((1-e_u <= R2_2) & (R2_2 <= 1+e_o)); */
  /* '<S6>:1:37' R2_3_h = ((1-e_u <= R2_3) & (R2_3 <= 1+e_o)); */
  /* '<S6>:1:39' R2_4h = R2_0_h | R2_1_h | R2_2_h | R2_3_h; */
  rtb_R2_4h = (((1.0 - rtU_VSD_FD_6PH_V7->HB_u <= R1) && (R1 <=
    rtU_VSD_FD_6PH_V7->HB_o + 1.0)) || ((1.0 - rtU_VSD_FD_6PH_V7->HB_u <= R2) &&
    (R2 <= rtU_VSD_FD_6PH_V7->HB_o + 1.0)) || ((1.0 - rtU_VSD_FD_6PH_V7->HB_u <=
    R3) && (R3 <= rtU_VSD_FD_6PH_V7->HB_o + 1.0)) || ((1.0 -
    rtU_VSD_FD_6PH_V7->HB_u <= denum) && (denum <= rtU_VSD_FD_6PH_V7->HB_o + 1.0)));

  /* Reshape: '<S1>/Reshape2' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Double'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  rtDW_VSD_FD_6PH_V7->Reshape2[0] = R1;
  rtDW_VSD_FD_6PH_V7->Reshape2[1] = R2;
  rtDW_VSD_FD_6PH_V7->Reshape2[2] = R3;
  rtDW_VSD_FD_6PH_V7->Reshape2[3] = denum;
  rtDW_VSD_FD_6PH_V7->Reshape2[4] = rtb_R2_4h;

  /* Outport: '<Root>/R_b1_filtered' incorporates:
   *  Gain: '<S8>/C'
   *  Gain: '<S8>/D'
   *  Reshape: '<S1>/Reshape2'
   *  Sum: '<S8>/sum1'
   *  UnitDelay: '<S8>/Delay_x'
   */
  for (i = 0; i < 5; i++) {
    rtY_VSD_FD_6PH_V7->R_b1_filtered[i] = 0.0099013168773229958 *
      rtDW_VSD_FD_6PH_V7->Reshape2[i] + 9.900986831226771E-5 *
      rtDW_VSD_FD_6PH_V7->Delay_x_DSTATE_b[i];
  }

  /* End of Outport: '<Root>/R_b1_filtered' */

  /* Outport: '<Root>/R_b1' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Double'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  rtY_VSD_FD_6PH_V7->R_b1[0] = R1;
  rtY_VSD_FD_6PH_V7->R_b1[1] = R2;
  rtY_VSD_FD_6PH_V7->R_b1[2] = R3;
  rtY_VSD_FD_6PH_V7->R_b1[3] = denum;
  rtY_VSD_FD_6PH_V7->R_b1[4] = rtb_R2_4h;

  /* Update for UnitDelay: '<S7>/Delay_x' incorporates:
   *  Gain: '<S7>/A'
   *  Gain: '<S7>/B'
   *  Sum: '<S7>/A*x(k) + B*u(k)'
   */
  for (i = 0; i < 6; i++) {
    rtDW_VSD_FD_6PH_V7->Delay_x_DSTATE[i] = 0.980197366245354 *
      rtDW_VSD_FD_6PH_V7->Delay_x_DSTATE[i] + 198.0263375464599 *
      rtDW_VSD_FD_6PH_V7->Ro[i];
  }

  /* End of Update for UnitDelay: '<S7>/Delay_x' */

  /* Update for UnitDelay: '<S8>/Delay_x' incorporates:
   *  Gain: '<S8>/A'
   *  Gain: '<S8>/B'
   *  Reshape: '<S1>/Reshape2'
   *  Sum: '<S8>/A*x(k) + B*u(k)'
   */
  for (i = 0; i < 5; i++) {
    rtDW_VSD_FD_6PH_V7->Delay_x_DSTATE_b[i] = 0.980197366245354 *
      rtDW_VSD_FD_6PH_V7->Delay_x_DSTATE_b[i] + 198.0263375464599 *
      rtDW_VSD_FD_6PH_V7->Reshape2[i];
  }

  /* End of Update for UnitDelay: '<S8>/Delay_x' */
}

/* Model initialize function */
void VSD_FD_6PH_V7_initialize(RT_MODEL_VSD_FD_6PH_V7 *const rtM_VSD_FD_6PH_V7)
{
  DW_VSD_FD_6PH_V7 *rtDW_VSD_FD_6PH_V7 = rtM_VSD_FD_6PH_V7->dwork;
  ExtU_VSD_FD_6PH_V7 *rtU_VSD_FD_6PH_V7 = (ExtU_VSD_FD_6PH_V7 *)
    rtM_VSD_FD_6PH_V7->inputs;
  ExtY_VSD_FD_6PH_V7 *rtY_VSD_FD_6PH_V7 = (ExtY_VSD_FD_6PH_V7 *)
    rtM_VSD_FD_6PH_V7->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW_VSD_FD_6PH_V7, 0,
                sizeof(DW_VSD_FD_6PH_V7));

  /* external inputs */
  (void)memset(rtU_VSD_FD_6PH_V7, 0, sizeof(ExtU_VSD_FD_6PH_V7));

  /* external outputs */
  (void)memset(rtY_VSD_FD_6PH_V7, 0, sizeof(ExtY_VSD_FD_6PH_V7));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
