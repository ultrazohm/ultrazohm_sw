/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_FFTRecordedVoltage_api.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 07-Feb-2023 13:28:43
 */

#ifndef _CODER_FFTRECORDEDVOLTAGE_API_H
#define _CODER_FFTRECORDEDVOLTAGE_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void FFTRecordedVoltage(real32_T data[10000], real32_T sampletime,
                        real32_T frequencies[5001], real32_T amplitudes[5001],
                        real32_T angles[5001]);

void FFTRecordedVoltage_api(const mxArray *const prhs[2], int32_T nlhs,
                            const mxArray *plhs[3]);

void FFTRecordedVoltage_atexit(void);

void FFTRecordedVoltage_initialize(void);

void FFTRecordedVoltage_terminate(void);

void FFTRecordedVoltage_xil_shutdown(void);

void FFTRecordedVoltage_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_FFTRecordedVoltage_api.h
 *
 * [EOF]
 */
