/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTRecordedVoltage.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 07-Feb-2023 15:30:05
 */

#ifndef FFTRECORDEDVOLTAGE_H
#define FFTRECORDEDVOLTAGE_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void FFTRecordedVoltage(const float data[10000], float sampletime,
                               float frequencies[5001], float amplitudes[5001],
                               float angles[5001]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTRecordedVoltage.h
 *
 * [EOF]
 */
