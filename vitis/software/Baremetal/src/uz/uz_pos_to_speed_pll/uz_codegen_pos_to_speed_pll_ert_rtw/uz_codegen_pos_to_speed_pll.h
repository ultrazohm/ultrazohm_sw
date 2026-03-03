/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen_pos_to_speed_pll.h
 *
 * Code generated for Simulink model 'uz_codegen_pos_to_speed_pll'.
 *
 * Model version                  : 6.4
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Dec  4 15:17:18 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#ifndef RTW_HEADER_uz_codegen_pos_to_speed_pll_h_
#define RTW_HEADER_uz_codegen_pos_to_speed_pll_h_
#ifndef uz_codegen_pos_to_speed_pll_COMMON_INCLUDES_
#define uz_codegen_pos_to_speed_pll_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                        /* uz_codegen_pos_to_speed_pll_COMMON_INCLUDES_ */

#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetRootDWork
#define rtmGetRootDWork(rtm)           ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
#define rtmSetRootDWork(rtm, val)      ((rtm)->dwork = (val))
#endif

#ifndef rtmGetU
#define rtmGetU(rtm)                   ((rtm)->inputs)
#endif

#ifndef rtmSetU
#define rtmSetU(rtm, val)              ((rtm)->inputs = (val))
#endif

#ifndef rtmGetY
#define rtmGetY(rtm)                   ((rtm)->outputs)
#endif

#ifndef rtmSetY
#define rtmSetY(rtm, val)              ((rtm)->outputs = (val))
#endif

#define uz_codegen_pos_to_speed_pll_M  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T Memory_PreviousInput[2];    /* '<S3>/Memory' */
  real32_T Delay1_DSTATE;              /* '<S4>/Delay1' */
  real32_T Memory_PreviousInput_g;     /* '<S5>/Memory' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T position_mech_SI;           /* '<Root>/position_mech_SI' */
  real32_T pole_pairs;                 /* '<Root>/pole_pairs' */
  real32_T kp_pll;                     /* '<Root>/kp_pll' */
  real32_T ki_pll;                     /* '<Root>/ki_pll' */
  real32_T sampling_time_seconds;      /* '<Root>/sampling_time_seconds' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T omega_mech;                 /* '<Root>/omega_mech' */
  real32_T omega_el;                   /* '<Root>/omega_el' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Model entry point functions */
extern void uz_codegen_pos_to_speed_pll_initialize(RT_MODEL *const rtM);
extern void uz_codegen_pos_to_speed_pll_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S7>/Scope2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll')    - opens subsystem uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll
 * hilite_system('uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_pos_to_speed_pll'
 * '<S1>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll'
 * '<S2>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/PLL'
 * '<S3>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/PLL/PLL'
 * '<S4>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/PLL/PLL/Integrator'
 * '<S5>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/PLL/PLL/PI-Regler'
 * '<S6>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/PLL/PLL/phase discriminator'
 * '<S7>'   : 'uz_pos_to_speed_pll/uz_codegen_pos_to_speed_pll/PLL/PLL/rad2cs'
 */

/*-
 * Requirements for '<Root>': uz_codegen_pos_to_speed_pll

 */
#endif                           /* RTW_HEADER_uz_codegen_pos_to_speed_pll_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
