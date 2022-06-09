/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_modes.c
 *
 * Code generation for function 'compute_modes'
 *
 */

/* Include files */
#include "compute_modes.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void compute_modes(const real_T x[12], const real_T u[81], real_T t,
                   boolean_T modes[12])
{
  (void)t;
  modes[0] = (x[0] + -u[0] > 0.8);
  modes[1] = (u[1] > 0.5);
  modes[2] = (-x[1] + -u[0] > 0.8);
  modes[3] = (u[2] > 0.5);
  modes[4] = (-x[2] + -u[0] > 0.8);
  modes[5] = (u[3] > 0.5);
  modes[6] = (x[1] + -u[0] > 0.8);
  modes[7] = (u[4] > 0.05);
  modes[8] = (-x[0] + -u[0] > 0.8);
  modes[9] = (u[5] > 0.5);
  modes[10] = (x[2] + -u[0] > 0.8);
  modes[11] = (u[6] > 0.05);
}

/* End of code generation (compute_modes.c) */
