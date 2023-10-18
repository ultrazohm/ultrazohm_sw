/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: mean_GqoxPyM9.c
 *
 * Code generated for Simulink model 'FluxMapID_6ph_codegen'.
 *
 * Model version                  : 3.66
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Mar  8 12:42:46 2023
 */

#include "rtwtypes.h"
#include "mean_GqoxPyM9.h"

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
real32_T mean_GqoxPyM9(const real32_T x[10000])
{
  int32_T b_k;
  int32_T k;
  real32_T b_x;
  b_x = x[0];
  for (k = 0; k < 1023; k++) {
    b_x += x[k + 1];
  }

  for (k = 0; k < 9; k++) {
    int32_T hi;
    int32_T xblockoffset;
    real32_T bsum;
    xblockoffset = (k + 1) << 10;
    bsum = x[xblockoffset];
    if (k + 2 == 10) {
      hi = 784;
    } else {
      hi = 1024;
    }

    for (b_k = 2; b_k <= hi; b_k++) {
      bsum += x[(xblockoffset + b_k) - 1];
    }

    b_x += bsum;
  }

  return b_x / 10000.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
