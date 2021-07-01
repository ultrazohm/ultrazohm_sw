/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rtmodel.h
 *
 * Code generated for Simulink model 'Basic_FOC'.
 *
 * Model version                  : 2.22
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jun 29 12:48:17 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_rtmodel_h_
#define RTW_HEADER_rtmodel_h_
#include "Basic_FOC.h"

/*
 * ROOT_IO_FORMAT: 0 (Individual arguments)
 * ROOT_IO_FORMAT: 1 (Structure reference)
 * ROOT_IO_FORMAT: 2 (Part of model data structure)
 */
#define ROOT_IO_FORMAT                 2

/* Macros generated for backwards compatibility  */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((void) 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((void*) 0)
#endif
#endif                                 /* RTW_HEADER_rtmodel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
