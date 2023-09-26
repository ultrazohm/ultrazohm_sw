/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_slowCTRL_data.c
 *
 * Code generated for Simulink model 'FOC_slowCTRL'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Sep 26 09:35:18 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_slowCTRL.h"

/* Invariant block signals (default storage) */
const ConstB_FOC_slowCTRL_T FOC_slowCTRL_ConstB = {
  -0.00047000000000000004              /* '<S14>/Add' */
};

/* Constant parameters (default storage) */
const ConstP_FOC_slowCTRL_T FOC_slowCTRL_ConstP = {
  /* Expression: EMotor.FEM_data.I_d_M_MTPC.z
   * Referenced by: '<S10>/Id_Ref_M_MTPC'
   */
  { 0.0, -6.0085507565999023, -18.648957730588887, -34.087694712758278,
    -51.341930212302486, -69.463648350175035, -89.147496569685,
    -108.77923084485306, -130.07433517891718, -152.35506238888672,
    -175.7523467698949, -196.98273335018547, -216.24720550552323,
    -235.4173141375534, -254.67547233773774, -275.0078579954727,
    -293.41814944651691, -310.50118965849134, -330.43503338670251,
    -350.28571483439976 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S10>/Id_Ref_M_MTPC'
   *   '<S16>/Iq_Ref_M_MTPC'
   */
  { -0.0037440216292055259, 13.359503610375837, 28.759810625246441,
    45.929165491622321, 63.604180053639332, 81.619150254687, 99.746961563665309,
    117.70342630475001, 135.43690802915745, 152.71648178418585,
    169.1241970850904, 185.1315247301477, 200.40375682762257, 215.28064383481677,
    229.63097844075426, 243.24056984417842, 255.66015213399, 265.91923550417084,
    275.04214125891735, 283.53453237990743 },

  /* Expression: EMotor.FEM_data.I_q_M_MTPC.z
   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
   */
  { 0.0, 24.538224561279229, 46.958758105600779, 67.691014104528165,
    87.038155719807918, 105.50109112347292, 122.59241877325269,
    139.42815042418079, 154.68420967857253, 168.77302467054739,
    181.47679544866077, 196.01858974707645, 212.46612730580426,
    228.99579912281109, 245.42396901112454, 260.71399286187716,
    278.0142786978198, 296.70971782202292, 312.40724107900553,
    328.17665666977837 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
