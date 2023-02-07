/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_FFTRecordedVoltage_mex.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 07-Feb-2023 13:28:43
 */

#ifndef _CODER_FFTRECORDEDVOLTAGE_MEX_H
#define _CODER_FFTRECORDEDVOLTAGE_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_FFTRecordedVoltage_mexFunction(int32_T nlhs, mxArray *plhs[3],
                                           int32_T nrhs,
                                           const mxArray *prhs[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_FFTRecordedVoltage_mex.h
 *
 * [EOF]
 */
