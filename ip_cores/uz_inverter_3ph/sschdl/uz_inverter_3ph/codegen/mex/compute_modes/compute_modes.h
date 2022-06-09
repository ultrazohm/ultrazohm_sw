/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_modes.h
 *
 * Code generation for function 'compute_modes'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void compute_modes(const real_T x[12], const real_T u[81], real_T t,
                   boolean_T modes[12]);

/* End of code generation (compute_modes.h) */
