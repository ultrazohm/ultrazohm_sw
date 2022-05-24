/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VSD_FD_6PH_V6.h
 *
 * Code generated for Simulink model 'VSD_FD_6PH_V6'.
 *
 * Model version                  : 3.1
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May 24 08:43:52 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_VSD_FD_6PH_V6_h_
#define RTW_HEADER_VSD_FD_6PH_V6_h_
#include <string.h>
#ifndef VSD_FD_6PH_V6_COMMON_INCLUDES_
#define VSD_FD_6PH_V6_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* VSD_FD_6PH_V6_COMMON_INCLUDES_ */

/* Model Code Variants */

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

#define VSD_FD_6PH_V6_M                (rtM_VSD_FD_6PH_V6)

/* Forward declaration for rtModel */
typedef struct tag_RTM_VSD_FD_6PH_V6 RT_MODEL_VSD_FD_6PH_V6;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_x_DSTATE[6];            /* '<S5>/Delay_x' */
  real_T R[6];                         /* '<S1>/Fehlerindexe_asym_6Ph' */
} DW_VSD_FD_6PH_V6;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T i_ab_xy_z1z2[6];              /* '<Root>/i_ab_xy_z1z2' */
  real_T HB_u;                         /* '<Root>/HB_u' */
  real_T HB_o;                         /* '<Root>/HB_o' */
} ExtU_VSD_FD_6PH_V6;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T FD_filtered[6];               /* '<Root>/FD_filtered' */
  real_T FD[6];                        /* '<Root>/FD' */
  real_T Output[6];                    /* '<Root>/Output' */
} ExtY_VSD_FD_6PH_V6;

/* Real-time Model Data Structure */
struct tag_RTM_VSD_FD_6PH_V6 {
  ExtU_VSD_FD_6PH_V6 *inputs;
  ExtY_VSD_FD_6PH_V6 *outputs;
  DW_VSD_FD_6PH_V6 *dwork;
};

/* Model entry point functions */
extern void VSD_FD_6PH_V6_initialize(RT_MODEL_VSD_FD_6PH_V6 *const
  rtM_VSD_FD_6PH_V6);
extern void VSD_FD_6PH_V6_step(RT_MODEL_VSD_FD_6PH_V6 *const rtM_VSD_FD_6PH_V6);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope31' : Unused code path elimination
 * Block '<S1>/Reshape1' : Reshape block reduction
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
 * hilite_system('VSD_FD_codegen_V2/VSD_FD_6PH_V6')    - opens subsystem VSD_FD_codegen_V2/VSD_FD_6PH_V6
 * hilite_system('VSD_FD_codegen_V2/VSD_FD_6PH_V6/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VSD_FD_codegen_V2'
 * '<S1>'   : 'VSD_FD_codegen_V2/VSD_FD_6PH_V6'
 * '<S2>'   : 'VSD_FD_codegen_V2/VSD_FD_6PH_V6/Fehlerindexe_asym_6Ph'
 * '<S3>'   : 'VSD_FD_codegen_V2/VSD_FD_6PH_V6/First-Order Filter'
 * '<S4>'   : 'VSD_FD_codegen_V2/VSD_FD_6PH_V6/HystereseBand'
 * '<S5>'   : 'VSD_FD_codegen_V2/VSD_FD_6PH_V6/First-Order Filter/Model'
 */

/*-
 * Requirements for '<Root>': VSD_FD_6PH_V6
 */
#endif                                 /* RTW_HEADER_VSD_FD_6PH_V6_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
