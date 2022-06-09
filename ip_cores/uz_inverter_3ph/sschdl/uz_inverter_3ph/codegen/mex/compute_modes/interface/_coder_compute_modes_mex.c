/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_compute_modes_mex.c
 *
 * Code generation for function '_coder_compute_modes_mex'
 *
 */

/* Include files */
#include "_coder_compute_modes_mex.h"
#include "_coder_compute_modes_api.h"
#include "compute_modes_data.h"
#include "compute_modes_initialize.h"
#include "compute_modes_terminate.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void compute_modes_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                               const mxArray *prhs[3])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        13, "compute_modes");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "compute_modes");
  }
  /* Call the function. */
  compute_modes_api(prhs, &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&compute_modes_atexit);
  /* Module initialization. */
  compute_modes_initialize();
  /* Dispatch the entry-point. */
  compute_modes_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  compute_modes_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2021a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_compute_modes_mex.c) */
