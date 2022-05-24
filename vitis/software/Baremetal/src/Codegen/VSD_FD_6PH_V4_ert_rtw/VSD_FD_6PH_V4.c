/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VSD_FD_6PH_V4.c
 *
 * Code generated for Simulink model 'VSD_FD_6PH_V4'.
 *
 * Model version                  : 3.3
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May 24 11:06:20 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "VSD_FD_6PH_V4.h"

/* Model step function */
void VSD_FD_6PH_V4_step(RT_MODEL_VSD_FD_6PH_V4 *const rtM_VSD_FD_6PH_V4)
{
  DW_VSD_FD_6PH_V4 *rtDW_VSD_FD_6PH_V4 = rtM_VSD_FD_6PH_V4->dwork;
  ExtU_VSD_FD_6PH_V4 *rtU_VSD_FD_6PH_V4 = (ExtU_VSD_FD_6PH_V4 *)
    rtM_VSD_FD_6PH_V4->inputs;
  ExtY_VSD_FD_6PH_V4 *rtY_VSD_FD_6PH_V4 = (ExtY_VSD_FD_6PH_V4 *)
    rtM_VSD_FD_6PH_V4->outputs;
  real_T denum;
  int32_T i;

  /* MATLAB Function: '<S1>/Fehlerindexe_asym_6Ph' incorporates:
   *  Inport: '<Root>/i_ab_xy_z1z2'
   */
  /* MATLAB Function 'VSD_FD_6PH_V4/Fehlerindexe_asym_6Ph': '<S2>:1' */
  /* OPF-Fehlerindexe nach Duran: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7858758&tag=1 */
  /* '<S2>:1:5' denum = 0; */
  /*  Phase a */
  /* '<S2>:1:8' denum = (i_a+i_z1); */
  denum = rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[0] + rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[4];

  /* '<S2>:1:9' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:10' R1 = 0; */
    rtDW_VSD_FD_6PH_V4->R[0] = 0.0;
  } else {
    /* '<S2>:1:11' else */
    /* '<S2>:1:12' R1 = -i_x/denum; */
    rtDW_VSD_FD_6PH_V4->R[0] = -rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[2] / denum;
  }

  /*  Phase b */
  /* '<S2>:1:16' denum = (-i_a+sqrt(3)*i_b-sqrt(3)*i_y+2*i_z1); */
  denum = ((1.7320508075688772 * rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[1] +
            -rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[0]) - 1.7320508075688772 *
           rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[3]) + 2.0 *
    rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[4];

  /* '<S2>:1:17' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:18' R2 = 0; */
    rtDW_VSD_FD_6PH_V4->R[1] = 0.0;
  } else {
    /* '<S2>:1:19' else */
    /* '<S2>:1:20' R2 = i_x/denum; */
    rtDW_VSD_FD_6PH_V4->R[1] = rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[2] / denum;
  }

  /*  Phase c */
  /* '<S2>:1:24' denum = (-i_a-sqrt(3)*i_b+sqrt(3)*i_y+2*i_z1); */
  denum = ((-rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[0] - 1.7320508075688772 *
            rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[1]) + 1.7320508075688772 *
           rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[3]) + 2.0 *
    rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[4];

  /* '<S2>:1:25' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:26' R3 = 0; */
    rtDW_VSD_FD_6PH_V4->R[2] = 0.0;
  } else {
    /* '<S2>:1:27' else */
    /* '<S2>:1:28' R3 = i_x/denum; */
    rtDW_VSD_FD_6PH_V4->R[2] = rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[2] / denum;
  }

  /*  Phase d */
  /* '<S2>:1:32' denum = (i_a+1/sqrt(3)*i_b + 1/sqrt(3) * i_y+2/sqrt(3) *i_z2); */
  denum = ((0.57735026918962584 * rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[1] +
            rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[0]) + 0.57735026918962584 *
           rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[3]) + 1.1547005383792517 *
    rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[5];

  /* '<S2>:1:33' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:34' R4 = 0; */
    rtDW_VSD_FD_6PH_V4->R[3] = 0.0;
  } else {
    /* '<S2>:1:35' else */
    /* '<S2>:1:36' R4 = i_x/denum; */
    rtDW_VSD_FD_6PH_V4->R[3] = rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[2] / denum;
  }

  /*  Phase e */
  /* '<S2>:1:40' denum = (i_a-1/sqrt(3)*i_b-1/sqrt(3)*i_y-2/sqrt(3)*i_z2); */
  denum = ((rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[0] - 0.57735026918962584 *
            rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[1]) - 0.57735026918962584 *
           rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[3]) - 1.1547005383792517 *
    rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[5];

  /* '<S2>:1:41' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:42' R5 = 0; */
    rtDW_VSD_FD_6PH_V4->R[4] = 0.0;
  } else {
    /* '<S2>:1:43' else */
    /* '<S2>:1:44' R5 = i_x/denum; */
    rtDW_VSD_FD_6PH_V4->R[4] = rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[2] / denum;
  }

  /*  Phase f */
  /* '<S2>:1:48' denum = (i_b-i_z2); */
  denum = rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[1] - rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[5];

  /* '<S2>:1:49' if denum == 0 */
  if (denum == 0.0) {
    /* '<S2>:1:50' R6 = 0; */
    rtDW_VSD_FD_6PH_V4->R[5] = 0.0;
  } else {
    /* '<S2>:1:51' else */
    /* '<S2>:1:52' R6 = -i_y/denum; */
    rtDW_VSD_FD_6PH_V4->R[5] = -rtU_VSD_FD_6PH_V4->i_ab_xy_z1z2[3] / denum;
  }

  /* End of MATLAB Function: '<S1>/Fehlerindexe_asym_6Ph' */
  /* '<S2>:1:55' R=[R1; R2; R3; R4; R5; R6]; */
  /*  % Phase a */
  /*  R1 = -i_x/(i_a+i_z1); */
  /*  if isinf(R1) | isnan(R1) */
  /*      R1 = 0; */
  /*  end */
  /*   */
  /*  % Phase b */
  /*  R2 = i_x/(-i_a+sqrt(3)*i_b-sqrt(3)*i_y+2*i_z1);    */
  /*  if isinf(R2) | isnan(R2) */
  /*      R2 = 0; */
  /*  end */
  /*   */
  /*  % Phase c */
  /*  R3 = i_x/(-i_a-sqrt(3)*i_b+sqrt(3)*i_y+2*i_z1); */
  /*  if isinf(R3) | isnan(R3) */
  /*      R3 = 0; */
  /*  end */
  /*   */
  /*  % Phase d */
  /*  R4 = i_x/(i_a+1/sqrt(3)*i_b + 1/sqrt(3) * i_y+2/sqrt(3) *i_z2); */
  /*  if isinf(R4) | isnan(R4) */
  /*      R4 = 0; */
  /*  end */
  /*   */
  /*  % Phase e */
  /*  R5 = i_x/(i_a-1/sqrt(3)*i_b-1/sqrt(3)*i_y-2/sqrt(3)*i_z2); */
  /*  if isinf(R5) | isnan(R5) */
  /*      R5 = 0; */
  /*  end */
  /*   */
  /*  % Phase f */
  /*  R6 = -i_y/(i_b-i_z2); */
  /*  if isinf(R6) | isnan(R6) */
  /*      R6 = 0; */
  /*  end */
  /* MATLAB Function 'VSD_FD_6PH_V4/HystereseBand': '<S4>:1' */
  /*  Hystereseband, Ausgang Ro ist gleich Ri falls Ri im Bereich von +-e um 1 */
  /*  ist, ansonsten ist Ro = 0 */
  /* '<S4>:1:6' X = ((1-e_u <= Ri) & (Ri <= 1+e_o)); */
  /* '<S4>:1:7' Ro = X.*Ri; */
  for (i = 0; i < 6; i++) {
    real_T rtb_Ro;

    /* MATLAB Function: '<S1>/HystereseBand' incorporates:
     *  Inport: '<Root>/HB_o'
     *  Inport: '<Root>/HB_u'
     */
    denum = rtDW_VSD_FD_6PH_V4->R[i];
    rtb_Ro = (real_T)((1.0 - rtU_VSD_FD_6PH_V4->HB_u <= denum) && (denum <=
      rtU_VSD_FD_6PH_V4->HB_o + 1.0)) * denum;

    /* Outport: '<Root>/FD_filtered' incorporates:
     *  Gain: '<S5>/C'
     *  Gain: '<S5>/D'
     *  Sum: '<S5>/sum1'
     *  UnitDelay: '<S5>/Delay_x'
     */
    rtY_VSD_FD_6PH_V4->FD_filtered[i] = 0.0099013168773229958 * rtb_Ro +
      9.900986831226771E-5 * rtDW_VSD_FD_6PH_V4->Delay_x_DSTATE[i];

    /* Outport: '<Root>/FD_hyst' */
    rtY_VSD_FD_6PH_V4->FD_hyst[i] = rtb_Ro;

    /* Outport: '<Root>/FD_raw' */
    rtY_VSD_FD_6PH_V4->FD_raw[i] = denum;

    /* Update for UnitDelay: '<S5>/Delay_x' incorporates:
     *  Gain: '<S5>/A'
     *  Gain: '<S5>/B'
     *  Sum: '<S5>/A*x(k) + B*u(k)'
     */
    rtDW_VSD_FD_6PH_V4->Delay_x_DSTATE[i] = 0.980197366245354 *
      rtDW_VSD_FD_6PH_V4->Delay_x_DSTATE[i] + 198.0263375464599 * rtb_Ro;
  }
}

/* Model initialize function */
void VSD_FD_6PH_V4_initialize(RT_MODEL_VSD_FD_6PH_V4 *const rtM_VSD_FD_6PH_V4)
{
  DW_VSD_FD_6PH_V4 *rtDW_VSD_FD_6PH_V4 = rtM_VSD_FD_6PH_V4->dwork;
  ExtU_VSD_FD_6PH_V4 *rtU_VSD_FD_6PH_V4 = (ExtU_VSD_FD_6PH_V4 *)
    rtM_VSD_FD_6PH_V4->inputs;
  ExtY_VSD_FD_6PH_V4 *rtY_VSD_FD_6PH_V4 = (ExtY_VSD_FD_6PH_V4 *)
    rtM_VSD_FD_6PH_V4->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW_VSD_FD_6PH_V4, 0,
                sizeof(DW_VSD_FD_6PH_V4));

  /* external inputs */
  (void)memset(rtU_VSD_FD_6PH_V4, 0, sizeof(ExtU_VSD_FD_6PH_V4));

  /* external outputs */
  (void)memset(rtY_VSD_FD_6PH_V4, 0, sizeof(ExtY_VSD_FD_6PH_V4));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
