/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VSD_FD_6PH_V6.c
 *
 * Code generated for Simulink model 'VSD_FD_6PH_V6'.
 *
 * Model version                  : 3.1
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May 24 08:43:52 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "VSD_FD_6PH_V6.h"

/* Model step function */
void VSD_FD_6PH_V6_step(RT_MODEL_VSD_FD_6PH_V6 *const rtM_VSD_FD_6PH_V6)
{
  DW_VSD_FD_6PH_V6 *rtDW_VSD_FD_6PH_V6 = rtM_VSD_FD_6PH_V6->dwork;
  ExtU_VSD_FD_6PH_V6 *rtU_VSD_FD_6PH_V6 = (ExtU_VSD_FD_6PH_V6 *)
    rtM_VSD_FD_6PH_V6->inputs;
  ExtY_VSD_FD_6PH_V6 *rtY_VSD_FD_6PH_V6 = (ExtY_VSD_FD_6PH_V6 *)
    rtM_VSD_FD_6PH_V6->outputs;
  int32_T i;

  /* MATLAB Function: '<S1>/Fehlerindexe_asym_6Ph' incorporates:
   *  Inport: '<Root>/i_ab_xy_z1z2'
   */
  /*  Phase a */
  /* MATLAB Function 'VSD_FD_6PH_V6/Fehlerindexe_asym_6Ph': '<S2>:1' */
  /* OPF-Fehlerindexe nach Duran: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7858758&tag=1 */
  /* '<S2>:1:6' R1 = -i_x/(i_a+i_z1); */
  /* '<S2>:1:7' if isinf(R1) | isnan(R1) */
  /*  Phase b */
  /* '<S2>:1:12' R2 = i_x/(-i_a+sqrt(3)*i_b-sqrt(3)*i_y+2*i_z1); */
  /* '<S2>:1:13' if isinf(R2) | isnan(R2) */
  /*  Phase c */
  /* '<S2>:1:18' R3 = i_x/(-i_a-sqrt(3)*i_b+sqrt(3)*i_y+2*i_z1); */
  /* '<S2>:1:19' if isinf(R3) | isnan(R3) */
  /*  Phase d */
  /* '<S2>:1:24' R4 = i_x/(i_a+1/sqrt(3)*i_b + 1/sqrt(3) * i_y+2/sqrt(3) *i_z2); */
  /* '<S2>:1:25' if isinf(R4) | isnan(R4) */
  /*  Phase e */
  /* '<S2>:1:30' R5 = i_x/(i_a-1/sqrt(3)*i_b-1/sqrt(3)*i_y-2/sqrt(3)*i_z2); */
  /* '<S2>:1:31' if isinf(R5) | isnan(R5) */
  /*  Phase f */
  /* '<S2>:1:36' R6 = -i_y/(i_b-i_z2); */
  /* '<S2>:1:37' if isinf(R6) | isnan(R6) */
  /* '<S2>:1:41' R=[R1; R2; R3; R4; R5; R6]; */
  rtDW_VSD_FD_6PH_V6->R[0] = -rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[2] /
    (rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[0] + rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[4]);
  rtDW_VSD_FD_6PH_V6->R[1] = rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[2] /
    (((1.7320508075688772 * rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[1] +
       -rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[0]) - 1.7320508075688772 *
      rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[3]) + 2.0 *
     rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[4]);
  rtDW_VSD_FD_6PH_V6->R[2] = rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[2] /
    (((-rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[0] - 1.7320508075688772 *
       rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[1]) + 1.7320508075688772 *
      rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[3]) + 2.0 *
     rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[4]);
  rtDW_VSD_FD_6PH_V6->R[3] = rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[2] /
    (((0.57735026918962584 * rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[1] +
       rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[0]) + 0.57735026918962584 *
      rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[3]) + 1.1547005383792517 *
     rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[5]);
  rtDW_VSD_FD_6PH_V6->R[4] = rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[2] /
    (((rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[0] - 0.57735026918962584 *
       rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[1]) - 0.57735026918962584 *
      rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[3]) - 1.1547005383792517 *
     rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[5]);
  rtDW_VSD_FD_6PH_V6->R[5] = -rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[3] /
    (rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[1] - rtU_VSD_FD_6PH_V6->i_ab_xy_z1z2[5]);

  /*  if (1-e <= Ri) & (Ri <= 1+e)      %das funktioniert nicht für einen Vektor */
  /*      Ro = Ri; */
  /*  else */
  /*      Ro = 0; */
  /*  end */
  /* MATLAB Function 'VSD_FD_6PH_V6/HystereseBand': '<S4>:1' */
  /*  Hystereseband, Ausgang Ro ist gleich Ri falls Ri im Bereich von +-e um 1 */
  /*  ist, ansonsten ist Ro = 0 */
  /* '<S4>:1:12' X = ((1-e_u <= Ri) & (Ri <= 1+e_o)); */
  /* '<S4>:1:13' Ro = X.*Ri; */
  for (i = 0; i < 6; i++) {
    real_T rtb_R;
    real_T rtb_Ro;

    /* MATLAB Function: '<S1>/HystereseBand' incorporates:
     *  Inport: '<Root>/HB_o'
     *  Inport: '<Root>/HB_u'
     */
    rtb_R = rtDW_VSD_FD_6PH_V6->R[i];
    rtb_Ro = (real_T)((1.0 - rtU_VSD_FD_6PH_V6->HB_u <= rtb_R) && (rtb_R <=
      rtU_VSD_FD_6PH_V6->HB_o + 1.0)) * rtb_R;

    /* Outport: '<Root>/FD_filtered' incorporates:
     *  Gain: '<S5>/C'
     *  Gain: '<S5>/D'
     *  Sum: '<S5>/sum1'
     *  UnitDelay: '<S5>/Delay_x'
     */
    rtY_VSD_FD_6PH_V6->FD_filtered[i] = 0.0099013168773229958 * rtb_Ro +
      9.900986831226771E-5 * rtDW_VSD_FD_6PH_V6->Delay_x_DSTATE[i];

    /* Outport: '<Root>/FD' */
    rtY_VSD_FD_6PH_V6->FD[i] = rtb_Ro;

    /* Outport: '<Root>/Output' */
    rtY_VSD_FD_6PH_V6->Output[i] = rtb_R;

    /* Update for UnitDelay: '<S5>/Delay_x' incorporates:
     *  Gain: '<S5>/A'
     *  Gain: '<S5>/B'
     *  Sum: '<S5>/A*x(k) + B*u(k)'
     */
    rtDW_VSD_FD_6PH_V6->Delay_x_DSTATE[i] = 0.980197366245354 *
      rtDW_VSD_FD_6PH_V6->Delay_x_DSTATE[i] + 198.0263375464599 * rtb_Ro;
  }
}

/* Model initialize function */
void VSD_FD_6PH_V6_initialize(RT_MODEL_VSD_FD_6PH_V6 *const rtM_VSD_FD_6PH_V6)
{
  DW_VSD_FD_6PH_V6 *rtDW_VSD_FD_6PH_V6 = rtM_VSD_FD_6PH_V6->dwork;
  ExtU_VSD_FD_6PH_V6 *rtU_VSD_FD_6PH_V6 = (ExtU_VSD_FD_6PH_V6 *)
    rtM_VSD_FD_6PH_V6->inputs;
  ExtY_VSD_FD_6PH_V6 *rtY_VSD_FD_6PH_V6 = (ExtY_VSD_FD_6PH_V6 *)
    rtM_VSD_FD_6PH_V6->outputs;

  /* Registration code */

/*
  (void) memset((void *)rtDW_VSD_FD_6PH_V6, 0,
                sizeof(DW_VSD_FD_6PH_V6));

  (void)memset(rtU_VSD_FD_6PH_V6, 0, sizeof(ExtU_VSD_FD_6PH_V6));


  (void)memset(rtY_VSD_FD_6PH_V6, 0, sizeof(ExtY_VSD_FD_6PH_V6));
*/
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
