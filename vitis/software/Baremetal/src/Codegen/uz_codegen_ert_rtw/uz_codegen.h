/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen.h
 *
 * Code generated for Simulink model 'uz_codegen'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Mar 13 14:42:22 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef uz_codegen_h_
#define uz_codegen_h_
#ifndef uz_codegen_COMMON_INCLUDES_
#define uz_codegen_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen_COMMON_INCLUDES_ */

#include <stddef.h>
#define uz_codegen_M                   (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Real-time Model Data Structure */
struct tag_RTM {
  char_T rt_unused;
};

/* Model entry point functions */
extern void uz_codegen_initialize(RT_MODEL *const rtM);
extern void uz_codegen_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant' : Unused code path elimination
 * Block '<Root>/Constant1' : Unused code path elimination
 * Block '<S1>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S3>/FixPt Constant' : Unused code path elimination
 * Block '<S3>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/FixPt Sum1' : Unused code path elimination
 * Block '<S1>/Output' : Unused code path elimination
 * Block '<S4>/Constant' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S4>/FixPt Switch' : Unused code path elimination
 * Block '<Root>/Data Type Conversion' : Unused code path elimination
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Gain' : Unused code path elimination
 * Block '<Root>/Rate Transition' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<S2>/Constant' : Unused code path elimination
 * Block '<S2>/Discrete-Time Integrator' : Unused code path elimination
 * Block '<S2>/Discrete-Time Integrator2' : Unused code path elimination
 * Block '<S2>/Gain1' : Unused code path elimination
 * Block '<S2>/Gain2' : Unused code path elimination
 * Block '<S2>/Sum' : Unused code path elimination
 * Block '<S2>/Sum3' : Unused code path elimination
 * Block '<S2>/Trigonometric Function' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/Counter Free-Running'
 * '<S2>'   : 'uz_codegen/uz_codegen'
 * '<S3>'   : 'uz_codegen/Counter Free-Running/Increment Real World'
 * '<S4>'   : 'uz_codegen/Counter Free-Running/Wrap To Zero'
 */

/*-
 * Requirements for '<Root>': uz_codegen

 */
#endif                                 /* uz_codegen_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
