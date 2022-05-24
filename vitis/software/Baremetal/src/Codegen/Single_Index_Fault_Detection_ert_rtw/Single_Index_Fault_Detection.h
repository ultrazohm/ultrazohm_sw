/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Single_Index_Fault_Detection.h
 *
 * Code generated for Simulink model 'Single_Index_Fault_Detection'.
 *
 * Model version                  : 3.4
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May 24 13:16:51 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_Single_Index_Fault_Detection_h_
#define RTW_HEADER_Single_Index_Fault_Detection_h_
#include <string.h>
#ifndef Single_Index_Fault_Detection_COMMON_INCLUDES_
#define Single_Index_Fault_Detection_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                       /* Single_Index_Fault_Detection_COMMON_INCLUDES_ */

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

#define Single_Index_Fault_Detection_M (rtM_Single_Index_Fault_Detecti)

/* Forward declaration for rtModel */
typedef struct tag_RTM_Single_Index_Fault_Dete RT_MODEL_Single_Index_Fault_Det;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_x_DSTATE;               /* '<S5>/Delay_x' */
} DW_Single_Index_Fault_Detection;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T HB_Wert;                      /* '<Root>/HB_Wert' */
  real_T i_ab_xy_z1z2[4];              /* '<Root>/i_ab_xy_z1z2' */
} ExtU_Single_Index_Fault_Detecti;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T FD_filtered;                  /* '<Root>/FD_filtered' */
  real_T FD_hyst;                      /* '<Root>/FD_hyst' */
  real_T FD_raw;                       /* '<Root>/FD_raw' */
} ExtY_Single_Index_Fault_Detecti;

/* Real-time Model Data Structure */
struct tag_RTM_Single_Index_Fault_Dete {
  ExtU_Single_Index_Fault_Detecti *inputs;
  ExtY_Single_Index_Fault_Detecti *outputs;
  DW_Single_Index_Fault_Detection *dwork;
};

/* Model entry point functions */
extern void Single_Index_Fault_Detection_initialize
  (RT_MODEL_Single_Index_Fault_Det *const rtM_Single_Index_Fault_Detecti);
extern void Single_Index_Fault_Detection_step(RT_MODEL_Single_Index_Fault_Det *
  const rtM_Single_Index_Fault_Detecti);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope16' : Unused code path elimination
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
 * hilite_system('VSD_FD_codegen_V2/Single_Index_Fault_Detection')    - opens subsystem VSD_FD_codegen_V2/Single_Index_Fault_Detection
 * hilite_system('VSD_FD_codegen_V2/Single_Index_Fault_Detection/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VSD_FD_codegen_V2'
 * '<S1>'   : 'VSD_FD_codegen_V2/Single_Index_Fault_Detection'
 * '<S2>'   : 'VSD_FD_codegen_V2/Single_Index_Fault_Detection/First-Order Filter'
 * '<S3>'   : 'VSD_FD_codegen_V2/Single_Index_Fault_Detection/HystereseBand1'
 * '<S4>'   : 'VSD_FD_codegen_V2/Single_Index_Fault_Detection/Single_Index'
 * '<S5>'   : 'VSD_FD_codegen_V2/Single_Index_Fault_Detection/First-Order Filter/Model'
 */

/*-
 * Requirements for '<Root>': Single_Index_Fault_Detection
 */
#endif                          /* RTW_HEADER_Single_Index_Fault_Detection_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
