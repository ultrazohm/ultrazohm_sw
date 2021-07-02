/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_FOC.h
 *
 * Code generated for Simulink model 'Basic_FOC'.
 *
 * Model version                  : 2.28
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Jul  2 16:27:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_Basic_FOC_h_
#define RTW_HEADER_Basic_FOC_h_
#include <math.h>
#include <string.h>
#ifndef Basic_FOC_COMMON_INCLUDES_
#define Basic_FOC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Basic_FOC_COMMON_INCLUDES_ */

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

#define Basic_FOC_M                    (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S1>/CurrentController' */
typedef struct {
  real_T Gain1[3];                     /* '<S116>/Gain1' */
  real_T Integrator_DSTATE;            /* '<S45>/Integrator' */
  real_T Integrator_DSTATE_j;          /* '<S96>/Integrator' */
  real_T Integrator_PREV_U;            /* '<S45>/Integrator' */
  real_T Integrator_PREV_U_f;          /* '<S96>/Integrator' */
  real_T a;
  real_T b;
  real_T c;
  real_T U_max;
  real_T u2;
  real_T IntegralGain;                 /* '<S42>/Integral Gain' */
  real_T SignPreSat;                   /* '<S36>/SignPreSat' */
  real_T Switch_ls;                    /* '<S4>/Switch' */
  real_T UdV;                          /* '<S4>/Add' */
  real_T Gain;                         /* '<S9>/Gain' */
  real_T Gain1_p;                      /* '<S9>/Gain1' */
  uint32_T CurrentController_PREV_T;   /* '<S1>/CurrentController' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S45>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE_n;  /* '<S96>/Integrator' */
  boolean_T CurrentController_RESET_ELAPS_T;/* '<S1>/CurrentController' */
} DW_CurrentController;

/* Block signals and states (default storage) for system '<S1>/SpeedController' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S163>/Integrator' */
  real_T Integrator_PREV_U;            /* '<S163>/Integrator' */
  uint32_T SpeedController_PREV_T;     /* '<S1>/SpeedController' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S163>/Integrator' */
  boolean_T SpeedController_RESET_ELAPS_T;/* '<S1>/SpeedController' */
} DW_SpeedController;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_SpeedController SpeedController_j;/* '<S1>/SpeedController' */
  DW_CurrentController CurrentController_f;/* '<S1>/CurrentController' */
  real_T Switch_j[2];                  /* '<S115>/Switch' */
  real_T ia;                           /* '<Root>/Basic_FOC' */
  real_T ib;                           /* '<Root>/Basic_FOC' */
  real_T ic;                           /* '<Root>/Basic_FOC' */
  real_T w_el;                         /* '<Root>/Basic_FOC' */
  real_T flg_PreCtrl;                  /* '<Root>/Basic_FOC' */
  real_T theta_el;                     /* '<Root>/Basic_FOC' */
  real_T U_IC;                         /* '<Root>/Basic_FOC' */
  real_T id_ref;                       /* '<Root>/Basic_FOC' */
  real_T iq_ref;                       /* '<Root>/Basic_FOC' */
  real_T flg_LimitUdUq;                /* '<Root>/Basic_FOC' */
  real_T flg_SpeedControl;             /* '<Root>/Basic_FOC' */
  real_T Switch;                       /* '<S127>/Switch' */
  real_T Switch1;                      /* '<S127>/Switch1' */
  real_T Switch2;                      /* '<S4>/Switch2' */
  real_T Switch3;                      /* '<S4>/Switch3' */
  real_T OutportBufferForId_ist;       /* '<S2>/Current Controller' */
  real_T u_a;                          /* '<S5>/SpaceVectorModulation' */
  real_T u_b;                          /* '<S5>/SpaceVectorModulation' */
  real_T u_c;                          /* '<S5>/SpaceVectorModulation' */
  real_T id_soll;                      /* '<Root>/Basic_FOC' */
  real_T iq_soll;                      /* '<Root>/Basic_FOC' */
  real_T rat_freq;                     /* '<Root>/Basic_FOC' */
  real_T cnt_CurrentCtrl;              /* '<Root>/Basic_FOC' */
  real_T id_ref_h;
  real_T iq_ref_e;
  real_T n_soll;
  real_T n_ist;
  real_T flg_fieldWeakening;
  real_T flg_UseMMPA;
  uint8_T is_active_c3_Basic_FOC;      /* '<Root>/Basic_FOC' */
  uint8_T is_c3_Basic_FOC;             /* '<Root>/Basic_FOC' */
  uint8_T is_InProcess;                /* '<Root>/Basic_FOC' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [ 1   -1/2   -1/2; 0   sqrt(3)/2   -sqrt(3)/2; 1/2  1/2  1/2 ]
   * Referenced by: '<S116>/Gain3'
   */
  real_T Gain3_Gain[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T flg_PreCntr;                /* '<Root>/flg_PreCntr' */
  real32_T flg_fieldWeakening;         /* '<Root>/flg_fieldWeakening' */
  real32_T flg_SpeedControl;           /* '<Root>/flg_SpeedControl' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T w_el;                       /* '<Root>/w_el' */
  real32_T ia;                         /* '<Root>/ia' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  real32_T iq_ref;                     /* '<Root>/iq_ref' */
  real32_T n_ist;                      /* '<Root>/n_ist' */
  real32_T id_ref;                     /* '<Root>/id_ref' */
  real32_T n_soll;                     /* '<Root>/n_soll' */
  real32_T U_IC;                       /* '<Root>/U_IC' */
  real32_T RESET;                      /* '<Root>/RESET' */
  real32_T START;                      /* '<Root>/START' */
  real32_T flgLimitUdUq;               /* '<Root>/flgLimitUdUq' */
  real32_T flg_UseMMPA;                /* '<Root>/flg_UseMMPA' */
  real_T T_speedController;            /* '<Root>/T_speedController' */
  real_T T_controller;                 /* '<Root>/T_controller' */
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

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Basic_FOC_initialize(RT_MODEL *const rtM);
extern void Basic_FOC_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S6>/Product2' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S113>/Data Type Duplicate' : Unused code path elimination
 * Block '<S113>/Data Type Propagation' : Unused code path elimination
 * Block '<S114>/Data Type Duplicate' : Unused code path elimination
 * Block '<S114>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/Scope' : Unused code path elimination
 * Block '<S9>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S5>/Constant' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
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
 * hilite_system('uz_codegen/Basic_FOC')    - opens subsystem uz_codegen/Basic_FOC
 * hilite_system('uz_codegen/Basic_FOC/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/Basic_FOC'
 * '<S2>'   : 'uz_codegen/Basic_FOC/CurrentController'
 * '<S3>'   : 'uz_codegen/Basic_FOC/SpeedController'
 * '<S4>'   : 'uz_codegen/Basic_FOC/CurrentController/Current Controller'
 * '<S5>'   : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation'
 * '<S6>'   : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/EntkopplungUndVorsteuerung'
 * '<S7>'   : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller'
 * '<S8>'   : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller'
 * '<S9>'   : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Spannungsbegrenzung'
 * '<S10>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0'
 * '<S11>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller'
 * '<S12>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Anti-windup'
 * '<S13>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/D Gain'
 * '<S14>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Filter'
 * '<S15>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Filter ICs'
 * '<S16>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/I Gain'
 * '<S17>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Ideal P Gain'
 * '<S18>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Ideal P Gain Fdbk'
 * '<S19>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Integrator'
 * '<S20>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Integrator ICs'
 * '<S21>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/N Copy'
 * '<S22>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/N Gain'
 * '<S23>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/P Copy'
 * '<S24>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Parallel P Gain'
 * '<S25>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Reset Signal'
 * '<S26>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Saturation'
 * '<S27>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Saturation Fdbk'
 * '<S28>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Sum'
 * '<S29>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Sum Fdbk'
 * '<S30>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tracking Mode'
 * '<S31>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tracking Mode Sum'
 * '<S32>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tsamp - Integral'
 * '<S33>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tsamp - Ngain'
 * '<S34>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/postSat Signal'
 * '<S35>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/preSat Signal'
 * '<S36>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Anti-windup/Disc. Clamping Ideal'
 * '<S37>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S38>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S39>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/D Gain/Disabled'
 * '<S40>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Filter/Disabled'
 * '<S41>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Filter ICs/Disabled'
 * '<S42>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/I Gain/Internal Parameters'
 * '<S43>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Ideal P Gain/Internal Parameters'
 * '<S44>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S45>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Integrator/Discrete'
 * '<S46>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Integrator ICs/Internal IC'
 * '<S47>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S48>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/N Gain/Disabled'
 * '<S49>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/P Copy/Internal Parameters Ideal'
 * '<S50>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Parallel P Gain/Passthrough'
 * '<S51>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Reset Signal/Disabled'
 * '<S52>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Saturation/Enabled'
 * '<S53>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S54>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Sum/Sum_PI'
 * '<S55>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Sum Fdbk/Disabled'
 * '<S56>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tracking Mode/Disabled'
 * '<S57>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S58>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tsamp - Integral/Passthrough'
 * '<S59>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S60>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/postSat Signal/Forward_Path'
 * '<S61>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Id-Controller/PID Controller/preSat Signal/Forward_Path'
 * '<S62>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller'
 * '<S63>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Anti-windup'
 * '<S64>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/D Gain'
 * '<S65>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Filter'
 * '<S66>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Filter ICs'
 * '<S67>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/I Gain'
 * '<S68>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Ideal P Gain'
 * '<S69>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Ideal P Gain Fdbk'
 * '<S70>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Integrator'
 * '<S71>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Integrator ICs'
 * '<S72>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/N Copy'
 * '<S73>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/N Gain'
 * '<S74>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/P Copy'
 * '<S75>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Parallel P Gain'
 * '<S76>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Reset Signal'
 * '<S77>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Saturation'
 * '<S78>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Saturation Fdbk'
 * '<S79>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Sum'
 * '<S80>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Sum Fdbk'
 * '<S81>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tracking Mode'
 * '<S82>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tracking Mode Sum'
 * '<S83>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tsamp - Integral'
 * '<S84>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tsamp - Ngain'
 * '<S85>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/postSat Signal'
 * '<S86>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/preSat Signal'
 * '<S87>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Anti-windup/Disc. Clamping Ideal'
 * '<S88>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S89>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S90>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/D Gain/Disabled'
 * '<S91>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Filter/Disabled'
 * '<S92>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Filter ICs/Disabled'
 * '<S93>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/I Gain/Internal Parameters'
 * '<S94>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Ideal P Gain/Internal Parameters'
 * '<S95>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S96>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Integrator/Discrete'
 * '<S97>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Integrator ICs/Internal IC'
 * '<S98>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S99>'  : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/N Gain/Disabled'
 * '<S100>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/P Copy/Internal Parameters Ideal'
 * '<S101>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Parallel P Gain/Passthrough'
 * '<S102>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Reset Signal/Disabled'
 * '<S103>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Saturation/Enabled'
 * '<S104>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S105>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Sum/Sum_PI'
 * '<S106>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Sum Fdbk/Disabled'
 * '<S107>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tracking Mode/Disabled'
 * '<S108>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S109>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tsamp - Integral/Passthrough'
 * '<S110>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S111>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/postSat Signal/Forward_Path'
 * '<S112>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Iq-Controller/PID Controller/preSat Signal/Forward_Path'
 * '<S113>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Spannungsbegrenzung/Saturation Dynamic'
 * '<S114>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/Spannungsbegrenzung/Saturation Dynamic1'
 * '<S115>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0'
 * '<S116>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0/abc to Alpha-Beta-Zero'
 * '<S117>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S118>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S119>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S120>' : 'uz_codegen/Basic_FOC/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S121>' : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation/SpaceVectorModulation'
 * '<S122>' : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation/dq0 to Alpha-Beta-Zero'
 * '<S123>' : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S124>' : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S125>' : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S126>' : 'uz_codegen/Basic_FOC/CurrentController/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem1'
 * '<S127>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller'
 * '<S128>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem'
 * '<S129>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller'
 * '<S130>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Anti-windup'
 * '<S131>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/D Gain'
 * '<S132>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Filter'
 * '<S133>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Filter ICs'
 * '<S134>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/I Gain'
 * '<S135>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Ideal P Gain'
 * '<S136>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Ideal P Gain Fdbk'
 * '<S137>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Integrator'
 * '<S138>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Integrator ICs'
 * '<S139>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/N Copy'
 * '<S140>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/N Gain'
 * '<S141>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/P Copy'
 * '<S142>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Parallel P Gain'
 * '<S143>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Reset Signal'
 * '<S144>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Saturation'
 * '<S145>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Saturation Fdbk'
 * '<S146>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Sum'
 * '<S147>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Sum Fdbk'
 * '<S148>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tracking Mode'
 * '<S149>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tracking Mode Sum'
 * '<S150>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tsamp - Integral'
 * '<S151>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tsamp - Ngain'
 * '<S152>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/postSat Signal'
 * '<S153>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/preSat Signal'
 * '<S154>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Anti-windup/Disc. Clamping Ideal'
 * '<S155>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S156>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S157>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/D Gain/Disabled'
 * '<S158>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Filter/Disabled'
 * '<S159>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Filter ICs/Disabled'
 * '<S160>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/I Gain/Internal Parameters'
 * '<S161>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Ideal P Gain/Internal Parameters'
 * '<S162>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S163>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Integrator/Discrete'
 * '<S164>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Integrator ICs/Internal IC'
 * '<S165>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S166>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/N Gain/Disabled'
 * '<S167>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/P Copy/Internal Parameters Ideal'
 * '<S168>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Parallel P Gain/Passthrough'
 * '<S169>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Reset Signal/Disabled'
 * '<S170>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Saturation/Enabled'
 * '<S171>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Saturation Fdbk/Disabled'
 * '<S172>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Sum/Sum_PI'
 * '<S173>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Sum Fdbk/Disabled'
 * '<S174>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tracking Mode/Disabled'
 * '<S175>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S176>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tsamp - Integral/Passthrough'
 * '<S177>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S178>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/postSat Signal/Forward_Path'
 * '<S179>' : 'uz_codegen/Basic_FOC/SpeedController/speed controller/Subsystem/PID Controller/preSat Signal/Forward_Path'
 */

/*-
 * Requirements for '<Root>': Basic_FOC
 */
#endif                                 /* RTW_HEADER_Basic_FOC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
