/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flussschaetzer.h
 *
 * Code generated for Simulink model 'Flussschaetzer'.
 *
 * Model version                  : 9.9
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Apr 14 16:27:27 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef Flussschaetzer_h_
#define Flussschaetzer_h_
#ifndef Flussschaetzer_COMMON_INCLUDES_
#define Flussschaetzer_COMMON_INCLUDES_
#include "../lib/rtwtypes.h"
#include "math.h"
#endif                                 /* Flussschaetzer_COMMON_INCLUDES_ */

#include <stddef.h>
#include "../lib/rt_nonfinite.h"
#include "../lib/rtGetNaN.h"

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

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define Flussschaetzer_M               (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM_Flussschaetzer RT_MODEL_Flussschaetzer;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T x_tmp[10];
  real_T time_values[10];
  real_T accumulatedData;
  real_T x_tmp_m;
  real32_T Probe[2];                   /* '<S7>/Probe' */
  real32_T omega_el_array[10];        /* '<S2>/Regressionsverfahren_omega_el' */
  real32_T theta_values[10];          /* '<S2>/Regressionsverfahren_omega_el' */
  real32_T x[10];
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S4>/Discrete-Time Integrator' */
  real32_T DiscreteTransferFcn1_states;/* '<S4>/Discrete Transfer Fcn1' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S4>/Discrete-Time Integrator1' */
  real32_T DiscreteTransferFcn2_states;/* '<S4>/Discrete Transfer Fcn2' */
  real32_T Integrator_DSTATE;          /* '<S13>/Integrator' */
  real32_T b_accumulatedData;
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S4>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S4>/Discrete-Time Integrator1' */
  int8_T Integrator_PrevResetState;    /* '<S13>/Integrator' */
  uint8_T Integrator_IC_LOADING;       /* '<S13>/Integrator' */
} DW_Flussschaetzer;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T u_alphabeta[3];             /* '<Root>/u_alphabeta' */
  real32_T i_alphabeta[3];             /* '<Root>/i_alphabeta' */
  real32_T integrator_reset;           /* '<Root>/integrator_reset' */
} ExtU_Flussschaetzer;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T theta_el_kor;               /* '<Root>/theta_el_kor' */
  real32_T omega_m_est;                /* '<Root>/omega_m_est' */
  real32_T psi_beta_filt;              /* '<Root>/psi_beta_filt' */
  real32_T psi_alpha_filt;             /* '<Root>/psi_alpha_filt' */
  real32_T theta_el_est;               /* '<Root>/theta_el_est' */
  real32_T psi_beta;                   /* '<Root>/psi_beta' */
  real32_T psi_alpha;                  /* '<Root>/psi_alpha' */
  real32_T omega_el_raw;               /* '<Root>/omega_el_raw' */
} ExtY_Flussschaetzer;

/* Parameters (default storage) */
struct P_Flussschaetzer_ {
  real32_T Ls;                         /* Variable: Ls
                                        * Referenced by:
                                        *   '<S4>/Gain2'
                                        *   '<S4>/Gain3'
                                        */
  real32_T Rs;                         /* Variable: Rs
                                        * Referenced by:
                                        *   '<S4>/Gain'
                                        *   '<S4>/Gain1'
                                        */
  real32_T THP;                        /* Variable: THP
                                        * Referenced by: '<S3>/Constant'
                                        */
  real32_T Ts;                         /* Variable: Ts
                                        * Referenced by: '<S2>/Constant3'
                                        */
};

/* Parameters (default storage) */
typedef struct P_Flussschaetzer_ P_Flussschaetzer;

/* Real-time Model Data Structure */
struct tag_RTM_Flussschaetzer {
  const char_T * volatile errorStatus;
  ExtU_Flussschaetzer *inputs;
  ExtY_Flussschaetzer *outputs;
  DW_Flussschaetzer *dwork;
};

/* Block parameters (default storage) */
extern P_Flussschaetzer rtP;

/* Model entry point functions */
extern void Flussschaetzer_initialize(RT_MODEL_Flussschaetzer *const rtM);
extern void Flussschaetzer_step(RT_MODEL_Flussschaetzer *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S13>/Saturation' : Eliminated Saturate block
 * Block '<S5>/K' : Eliminated nontunable gain of 1
 * Block '<S2>/Rate Transition1' : Eliminated since input and output rates are identical
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
 * hilite_system('uz_codegen/Flussschaetzer')    - opens subsystem uz_codegen/Flussschaetzer
 * hilite_system('uz_codegen/Flussschaetzer/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/Flussschaetzer'
 * '<S2>'   : 'uz_codegen/Flussschaetzer/Regressionsgerade'
 * '<S3>'   : 'uz_codegen/Flussschaetzer/theta_e_korrigieren_Drehzahlabhängig'
 * '<S4>'   : 'uz_codegen/Flussschaetzer/theta_el_schätzen'
 * '<S5>'   : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)'
 * '<S6>'   : 'uz_codegen/Flussschaetzer/Regressionsgerade/Regressionsverfahren_omega_el'
 * '<S7>'   : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S8>'   : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S9>'   : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S10>'  : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Constant'
 * '<S11>'  : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S12>'  : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_u'
 * '<S13>'  : 'uz_codegen/Flussschaetzer/Regressionsgerade/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 */

/*-
 * Requirements for '<Root>': Flussschaetzer

 */
#endif                                 /* Flussschaetzer_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
