/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.29
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jul 13 14:13:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#include <math.h>
#include <string.h>
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

/* Block signals and states (default storage) for system '<S1>/CurrentController' */
typedef struct {
  real_T Gain1[3];                     /* '<S15>/Gain1' */
  real_T Fcn;                          /* '<S34>/Fcn' */
  real_T Fcn1;                         /* '<S34>/Fcn1' */
  real_T Fcn_b;                        /* '<S33>/Fcn' */
  real_T Fcn1_h;                       /* '<S33>/Fcn1' */
  real_T Fcn_d;                        /* '<S28>/Fcn' */
  real_T Fcn1_o;                       /* '<S28>/Fcn1' */
  real_T Fcn_g;                        /* '<S27>/Fcn' */
  real_T Fcn1_p;                       /* '<S27>/Fcn1' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S6>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_g;/* '<S7>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_PREV_U;/* '<S6>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_PREV_U_j;/* '<S7>/Discrete-Time Integrator' */
  real_T a_W_on;
  real_T c;
  real_T U_max;
  real_T u2;
  real_T U_max_dq;                     /* '<S2>/Gain' */
  real_T error;                        /* '<S6>/Subtract' */
  real_T Sum;                          /* '<S6>/Sum' */
  real_T Gain_j;                       /* '<S6>/Gain' */
  real_T Switch1;                      /* '<S5>/Switch1' */
  real_T Gain;                         /* '<S8>/Gain' */
  uint32_T CurrentController_PREV_T;   /* '<S1>/CurrentController' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S6>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_j;/* '<S7>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_E;/* '<S6>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_c;/* '<S7>/Discrete-Time Integrator' */
  boolean_T CurrentController_RESET_ELAPS_T;/* '<S1>/CurrentController' */
} DW_CurrentController;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_CurrentController CurrentController_o;/* '<S1>/CurrentController' */
  real_T Switch_e[3];
  real_T Switch[2];
  real_T OutportBufferForub;
  real_T OutportBufferForuc;
  uint8_T is_active_c3_uz_codegen0;    /* '<Root>/uz_codegen' */
  uint8_T is_c3_uz_codegen0;           /* '<Root>/uz_codegen' */
} DW;

/* Invariant block signals for system '<S1>/CurrentController' */
typedef struct {
  const uint8_T Compare_g;             /* '<S26>/Compare' */
  const uint8_T Compare_fz;            /* '<S32>/Compare' */
} ConstB_CurrentController;

/* Invariant block signals (default storage) */
typedef struct {
  ConstB_CurrentController CurrentController_o;/* '<S1>/CurrentController' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [ 1   0   1; -1/2  sqrt(3)/2   1; -1/2  -sqrt(3)/2  1 ]
   * Referenced by: '<S23>/Gain3'
   */
  real_T Gain3_Gain[9];

  /* Expression: [ 1   -1/2   -1/2; 0   sqrt(3)/2   -sqrt(3)/2; 1/2  1/2  1/2 ]
   * Referenced by: '<S15>/Gain3'
   */
  real_T Gain3_Gain_i[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T flg_PreCntr;                /* '<Root>/flg_PreCntr' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T w_el;                       /* '<Root>/w_el' */
  real32_T ia;                         /* '<Root>/ia' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  real32_T iq_ref;                     /* '<Root>/iq_ref' */
  real32_T id_ref;                     /* '<Root>/id_ref' */
  real32_T U_IC;                       /* '<Root>/U_IC' */
  real32_T RESET;                      /* '<Root>/RESET' */
  real32_T START;                      /* '<Root>/START' */
  real32_T flgLimitUdUq;               /* '<Root>/flgLimitUdUq' */
  boolean_T flg_SpaceVectorModulation; /* '<Root>/flg_SpaceVectorModulation' */
  real32_T Kp_Iq;                      /* '<Root>/Kp_Iq' */
  real32_T Kp_Id;                      /* '<Root>/Kp_Id' */
  real32_T Ki_Iq;                      /* '<Root>/Ki_Iq' */
  real32_T Ki_Id;                      /* '<Root>/Ki_Id' */
  boolean_T flg_deadTimeCompensation;  /* '<Root>/flg_deadTimeCompensation' */
  boolean_T flg_theta_el_compensation; /* '<Root>/flg_theta_el_compensation' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Ua_DutyCycle;                 /* '<Root>/Ua_DutyCycle' */
  real_T activeState;                  /* '<Root>/activeState' */
  real_T Uc_DutyCycle;                 /* '<Root>/Uc_DutyCycle' */
  real_T Ub_DutyCycle;                 /* '<Root>/Ub_DutyCycle' */
  real_T iq_ist;                       /* '<Root>/iq_ist' */
  real_T id_ist;                       /* '<Root>/id_ist' */
  real_T uq;                           /* '<Root>/uq' */
  real_T ud;                           /* '<Root>/ud' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void uz_codegen0_initialize(RT_MODEL *const rtM);
extern void uz_codegen0_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
 * Block '<S21>/Constant' : Unused code path elimination
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
 * hilite_system('uz_codegen/uz_codegen')    - opens subsystem uz_codegen/uz_codegen
 * hilite_system('uz_codegen/uz_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/uz_codegen'
 * '<S2>'   : 'uz_codegen/uz_codegen/CurrentController'
 * '<S3>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller'
 * '<S4>'   : 'uz_codegen/uz_codegen/CurrentController/Modulation'
 * '<S5>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Entkopplung'
 * '<S6>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller'
 * '<S7>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller'
 * '<S8>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung'
 * '<S9>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0'
 * '<S10>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Saturation Dynamic'
 * '<S11>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Saturation Dynamic'
 * '<S12>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung/Saturation Dynamic'
 * '<S13>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung/Saturation Dynamic1'
 * '<S14>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0'
 * '<S15>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/abc to Alpha-Beta-Zero'
 * '<S16>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S17>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S18>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S19>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S20>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle'
 * '<S21>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation'
 * '<S22>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc'
 * '<S23>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/Alpha-Beta-Zero to abc'
 * '<S24>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero'
 * '<S25>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S26>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S27>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S28>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Subsystem1'
 * '<S29>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/SpaceVectorModulation'
 * '<S30>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero'
 * '<S31>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S32>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S33>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S34>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem1'
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
