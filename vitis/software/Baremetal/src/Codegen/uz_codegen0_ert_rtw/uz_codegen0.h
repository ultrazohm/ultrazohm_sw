/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 9.111
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Apr 16 10:52:55 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef uz_codegen0_h_
#define uz_codegen0_h_
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>

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
  real_T u_a0;                         /* '<S1>/Deadbeat Control' */
  real_T u_b0;                         /* '<S1>/Deadbeat Control' */
  real_T u_c0;                         /* '<S1>/Deadbeat Control' */
  real_T u_alpha0;
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ia;                           /* '<Root>/ia' */
  real_T ib;                           /* '<Root>/ib' */
  real_T ic;                           /* '<Root>/ic' */
  real_T id_ref;                       /* '<Root>/id_ref' */
  real_T iq_ref;                       /* '<Root>/iq_ref' */
  real_T theta_e;                      /* '<Root>/theta_e' */
  real_T w_e;                          /* '<Root>/w_e' */
  real_T Comp_PM;                      /* '<Root>/Comp_PM' */
  real_T Rs_PM;                        /* '<Root>/Rs_PM' */
  real_T Psi_PM;                       /* '<Root>/Psi_PM' */
  real_T Ts;                           /* '<Root>/Ts' */
  real_T V_dc_nom_PM;                  /* '<Root>/V_dc_nom_PM' */
  real_T Ld_PM;                        /* '<Root>/Ld_PM' */
  real_T Lq_PM;                        /* '<Root>/Lq_PM' */
  real_T Lambda;                       /* '<Root>/Lambda' */
  real_T Np;                           /* '<Root>/Np' */
  real_T Kp_current;                   /* '<Root>/Kp_current' */
  real_T Ki_current;                   /* '<Root>/Ki_current' */
  real_T id_ref_left;                  /* '<Root>/id_ref_left' */
  real_T iq_ref_left;                  /* '<Root>/iq_ref_left' */
  real_T id_left;                      /* '<Root>/id_left' */
  real_T iq_left;                      /* '<Root>/iq_left' */
  real_T theta_left;                   /* '<Root>/theta_left' */
  real_T we_left;                      /* '<Root>/we_left' */
  real_T k;                            /* '<Root>/k' */
  real_T wc;                           /* '<Root>/wc' */
  real_T wc_speed;                     /* '<Root>/wc_speed' */
  real_T id;                           /* '<Root>/id' */
  real_T iq;                           /* '<Root>/iq' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T da;                           /* '<Root>/da' */
  real_T db;                           /* '<Root>/db' */
  real_T dc;                           /* '<Root>/dc' */
  real_T da_left;                      /* '<Root>/da_left' */
  real_T db_left;                      /* '<Root>/db_left' */
  real_T dc_left;                      /* '<Root>/dc_left' */
  real_T theta_e_est;                  /* '<Root>/theta_e_est' */
  real_T i_alpha;                      /* '<Root>/i_alpha' */
  real_T i_beta;                       /* '<Root>/i_beta' */
  real_T i_alpha_est;                  /* '<Root>/i_alpha_est' */
  real_T i_beta_est;                   /* '<Root>/i_beta_est' */
  real_T theta_unwrap;                 /* '<Root>/theta_unwrap' */
  real_T n_est;                        /* '<Root>/n_est' */
  real_T Te_est;                       /* '<Root>/Te_est' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

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
 * '<S2>'   : 'uz_codegen/uz_codegen/Deadbeat Control'
 */

/*-
 * Requirements for '<Root>': uz_codegen0

 */
#endif                                 /* uz_codegen0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
