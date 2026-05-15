/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: complex_types.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 10.5
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu May 14 14:56:45 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#ifndef COMPLEX_TYPES_H
#define COMPLEX_TYPES_H
#include <stdint.h>

/*===========================================================================*
 * Complex number type definitions                                           *
 *===========================================================================*/
#define CREAL_T

typedef struct {
  float re;
  float im;
} creal32_T;

typedef struct {
  double re;
  double im;
} creal_T;

typedef creal_T creal64_T;

#define CINT8_T

typedef struct {
  int8_t re;
  int8_t im;
} cint8_T;

#define CUINT8_T

typedef struct {
  uint8_t re;
  uint8_t im;
} cuint8_T;

#define CINT16_T

typedef struct {
  int16_t re;
  int16_t im;
} cint16_T;

#define CUINT16_T

typedef struct {
  uint16_t re;
  uint16_t im;
} cuint16_T;

#define CINT32_T

typedef struct {
  int32_t re;
  int32_t im;
} cint32_T;

#define CUINT32_T

typedef struct {
  uint32_t re;
  uint32_t im;
} cuint32_T;

#define CINT64_T

typedef struct {
  int64_t re;
  int64_t im;
} cint64_T;

#define CUINT64_T

typedef struct {
  uint64_t re;
  uint64_t im;
} cuint64_T;

#endif                                 /* COMPLEX_TYPES_H */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
