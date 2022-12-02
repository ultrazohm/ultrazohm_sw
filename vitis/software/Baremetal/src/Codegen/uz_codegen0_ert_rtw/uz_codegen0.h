/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 3.5
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Dec  2 15:28:40 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (8), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

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

#define uz_codegen0_M                  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T iLrange_NL[8];
  real_T iRrange_NL[8];
  real_T iLrange_NR[8];
  real_T iLrange_NL_m;
  real_T iRrange_NL_c;
  real_T iLrange_NR_k;
  real_T iRrange_NR;
  real32_T correctionCurve_d[3150];    /* '<S1>/Data Store Memory1' */
  real32_T correctionCurve_q[3150];    /* '<S1>/Data Store Memory2' */
  real32_T varargin_1[9];
  real32_T b_iLrange_NL[8];
  real32_T b_iRrange_NL[8];
  real32_T b_iLrange_NR[8];
  real32_T b_iRrange_NR[8];
  real32_T fv[8];
  real32_T fv1[8];
  real32_T step;                       /* '<S1>/Read Memory Function' */
  real32_T wait;                       /* '<S1>/Read Memory Function' */
  real32_T step_p;                     /* '<S1>/MATLAB Function' */
  real32_T NL;
  real32_T NR;
  real32_T factorNL;
  real32_T factorNR;
  real32_T index_NL;
  real32_T iL_NL;
  int32_T iL_NVec;
  int32_T iR_NVec;
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: InvImp_d_Value
   * Referenced by: '<S1>/InvImp_d'
   */
  real32_T InvImp_d_Value[8];

  /* Computed Parameter: InvImp_d1_Value
   * Referenced by: '<S1>/InvImp_d1'
   */
  real32_T InvImp_d1_Value[8];

  /* Computed Parameter: NVec_Value
   * Referenced by: '<S1>/NVec'
   */
  real32_T NVec_Value[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T angle;                      /* '<Root>/angle' */
  real32_T Id_act;                     /* '<Root>/Id_act' */
  real32_T Id_ref;                     /* '<Root>/Id_ref' */
  real32_T omega_el;                   /* '<Root>/omega_el' */
  real32_T Iq_act;                     /* '<Root>/Iq_act' */
  real32_T Iq_ref;                     /* '<Root>/Iq_ref' */
  boolean_T FOC_ENABLE_HC;             /* '<Root>/FOC_ENABLE_HC' */
  boolean_T FOC_READ_ILR_MEMORY;       /* '<Root>/FOC_READ_ILR_MEMORY' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Idq_ref_ILR[2];             /* '<Root>/Idq_ref_ILR' */
  real32_T memoryd;                    /* '<Root>/memoryd' */
  real32_T memoryq;                    /* '<Root>/memoryq' */
  real32_T step_out;                   /* '<Root>/step_out' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void uz_codegen0_initialize(RT_MODEL *const rtM);
extern void uz_codegen0_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_codegen/uz_codegen')    - opens subsystem uz_codegen/uz_codegen
 * hilite_system('uz_codegen/uz_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/uz_codegen'
 * '<S2>'   : 'uz_codegen/uz_codegen/MATLAB Function'
 * '<S3>'   : 'uz_codegen/uz_codegen/Read Memory Function'
 */

/*-
 * Requirements for '<Root>': uz_codegen0
 */
#endif                                 /* RTW_HEADER_uz_codegen0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
