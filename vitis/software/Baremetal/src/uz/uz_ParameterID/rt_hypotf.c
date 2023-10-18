/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rt_hypotf.c
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 3.51
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Feb 23 16:51:10 2023
 */

#include "rtwtypes.h"
#include <math.h>
#include "rt_hypotf.h"

real32_T rt_hypotf(real32_T u0, real32_T u1)
{
  real32_T a;
  real32_T b;
  real32_T y;
  a = fabsf(u0);
  b = fabsf(u1);
  if (a < b) {
    a /= b;
    y = sqrtf(a * a + 1.0F) * b;
  } else if (a > b) {
    b /= a;
    y = sqrtf(b * b + 1.0F) * a;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
