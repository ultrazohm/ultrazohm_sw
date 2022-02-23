/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CleanPsiArray.h
 *
 * Code generated for Simulink model 'CleanPsiArray'.
 *
 * Model version                  : 2.381
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jan 11 13:27:09 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */
#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#ifndef RTW_HEADER_CleanPsiArray_h_
#define RTW_HEADER_CleanPsiArray_h_
#include "../../rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef CleanPsiArray_COMMON_INCLUDES_
#define CleanPsiArray_COMMON_INCLUDES_
#include "../../rtwtypes.h"
#endif                                 /* CleanPsiArray_COMMON_INCLUDES_ */

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

#define CleanPsiArray_M                (rtCleanPsiArray_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_CleanPsiArray_t RT_MODEL_CleanPsiArray_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_OnlineID_output_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_OnlineID_output_t_

typedef struct {
  real32_T id_out;
  real32_T Rph_out;
  real32_T Wtemp;
  real32_T psi_array[600];
  boolean_T IdControlFlag;
  real32_T delta_psi[200];
  uint16_T activeState;
  real32_T psi_pm_out;
  real32_T Ld_out;
  real32_T Lq_out;
  boolean_T clean_array;
} uz_PID_OnlineID_output_t;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T OnlineID_output_psi_array[600];
  real32_T psi_array_out[600];         /* '<Root>/CleanPsiArray' */
} DW_CleanPsiArray_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_PID_OnlineID_output_t OnlineID_output;/* '<Root>/OnlineID_output' */
  real32_T eta_c;                      /* '<Root>/eta_c' */
} ExtU_CleanPsiArray_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T psi_array_out[600];         /* '<Root>/psi_array_out' */
  boolean_T array_cleaned_flag;        /* '<Root>/array_cleaned_flag' */
  real32_T n_flux_points;              /* '<Root>/n_flux_points' */
} ExtY_CleanPsiArray_t;

/* Real-time Model Data Structure */
struct tag_RTM_CleanPsiArray_t {
  ExtU_CleanPsiArray_t *inputs;
  ExtY_CleanPsiArray_t *outputs;
  DW_CleanPsiArray_t *dwork;
};

/* Model entry point functions */
extern void CleanPsiArray_initialize(RT_MODEL_CleanPsiArray_t *const
  rtCleanPsiArray_M);
extern void CleanPsiArray_step(RT_MODEL_CleanPsiArray_t *const rtCleanPsiArray_M);

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
 * hilite_system('uz_ParameterID/CleanPsiArray')    - opens subsystem uz_ParameterID/CleanPsiArray
 * hilite_system('uz_ParameterID/CleanPsiArray/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/CleanPsiArray'
 */

/*-
 * Requirements for '<Root>': CleanPsiArray
 */
#endif                                 /* RTW_HEADER_CleanPsiArray_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
