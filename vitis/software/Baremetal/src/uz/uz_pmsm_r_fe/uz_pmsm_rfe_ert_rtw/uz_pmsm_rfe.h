/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_pmsm_rfe.h
 *
 * Code generated for Simulink model 'uz_pmsm_rfe'.
 *
 * Model version                  : 6.2
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Feb  5 22:51:29 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_uz_pmsm_rfe_h_
#define RTW_HEADER_uz_pmsm_rfe_h_
#ifndef uz_pmsm_rfe_COMMON_INCLUDES_
#define uz_pmsm_rfe_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_pmsm_rfe_COMMON_INCLUDES_ */

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

#define uz_pmsm_rfe_M                  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S1>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S1>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S1>/Discrete-Time Integrator1' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T U_d;                        /* '<Root>/U_d' */
  real32_T U_q;                        /* '<Root>/U_q' */
  real32_T omega_el;                   /* '<Root>/omega_el' */
  boolean_T reset_integrator;          /* '<Root>/reset_integrator' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Mi_ist;                       /* '<Root>/Mi_ist' */
  real_T Mi_soll;                      /* '<Root>/Mi_soll' */
  real_T I_d;                          /* '<Root>/I_d' */
  real_T I_q;                          /* '<Root>/I_q' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T Ld;                           /* Variable: Ld
                                        * Referenced by:
                                        *   '<S1>/L_d1'
                                        *   '<S1>/L_d2'
                                        *   '<S1>/L_d3'
                                        *   '<S1>/1//L_d'
                                        */
  real_T Lq;                           /* Variable: Lq
                                        * Referenced by:
                                        *   '<S1>/L_q1'
                                        *   '<S1>/L_q2'
                                        *   '<S1>/L_q3'
                                        *   '<S1>/1//L_q'
                                        */
  real_T PN;                           /* Variable: PN
                                        * Referenced by:
                                        *   '<S1>/1.5*Z_p'
                                        *   '<S1>/1.5*Z_p1'
                                        */
  real_T psi_pm;                       /* Variable: psi_pm
                                        * Referenced by:
                                        *   '<S1>/Gesamtfluss PM'
                                        *   '<S1>/Gesamtfluss PM1'
                                        */
  real_T r_cd;                         /* Variable: r_cd
                                        * Referenced by:
                                        *   '<S1>/q-Komponente Eisenwiderstand'
                                        *   '<S1>/Rs//Rc_d'
                                        */
  real_T r_cq;                         /* Variable: r_cq
                                        * Referenced by:
                                        *   '<S1>/d-Komponente Eisenwiderstand'
                                        *   '<S1>/Rs//Rc_q'
                                        */
  real_T r_s;                          /* Variable: r_s
                                        * Referenced by:
                                        *   '<S1>/Rs//Rc_d'
                                        *   '<S1>/Rs//Rc_q'
                                        *   '<S1>/Statorwiderstand_d'
                                        *   '<S1>/Statorwiderstand_q'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<S1>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<S1>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator1_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                           * Referenced by: '<S1>/Discrete-Time Integrator1'
                           */
  real_T DiscreteTimeIntegrator1_IC;   /* Expression: 0
                                        * Referenced by: '<S1>/Discrete-Time Integrator1'
                                        */
  real32_T uRc_d_Gain;                 /* Computed Parameter: uRc_d_Gain
                                        * Referenced by: '<S1>/1//Rc_d'
                                        */
  real32_T uRc_q_Gain;                 /* Computed Parameter: uRc_q_Gain
                                        * Referenced by: '<S1>/1//Rc_q'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Block parameters (default storage) */
extern P rtP;

/* Model entry point functions */
extern void uz_pmsm_rfe_initialize(RT_MODEL *const rtM);
extern void uz_pmsm_rfe_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_codegen/uz_pmsm_rfe')    - opens subsystem uz_codegen/uz_pmsm_rfe
 * hilite_system('uz_codegen/uz_pmsm_rfe/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/uz_pmsm_rfe'
 */

/*-
 * Requirements for '<Root>': uz_pmsm_rfe

 */
#endif                                 /* RTW_HEADER_uz_pmsm_rfe_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
