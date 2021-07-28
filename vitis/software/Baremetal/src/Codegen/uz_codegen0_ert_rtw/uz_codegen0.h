/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.98
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 28 15:29:21 2021
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
#include <stddef.h>
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
  real_T Switch2[3];                   /* '<S121>/Switch2' */
  real32_T TmpSignalConversionAtGain3I[3];
  real32_T Gain1[3];                   /* '<S116>/Gain1' */
  real32_T Fcn;                        /* '<S136>/Fcn' */
  real32_T Fcn1;                       /* '<S136>/Fcn1' */
  real32_T Fcn_b;                      /* '<S135>/Fcn' */
  real32_T Fcn1_h;                     /* '<S135>/Fcn1' */
  real32_T Fcn_d;                      /* '<S130>/Fcn' */
  real32_T Fcn1_o;                     /* '<S130>/Fcn1' */
  real32_T Fcn_g;                      /* '<S129>/Fcn' */
  real32_T Fcn1_p;                     /* '<S129>/Fcn1' */
  real32_T UnitDelay1_DSTATE;          /* '<S4>/Unit Delay1' */
  real32_T Integrator_DSTATE;          /* '<S43>/Integrator' */
  real32_T UnitDelay_DSTATE;           /* '<S4>/Unit Delay' */
  real32_T Integrator_DSTATE_b;        /* '<S96>/Integrator' */
  real32_T Integrator_PREV_U;          /* '<S43>/Integrator' */
  real32_T Integrator_PREV_U_e;        /* '<S96>/Integrator' */
  real32_T a_W_on;
  real32_T a;
  real32_T b;
  int32_T sector;
  uint32_T CurrentController_PREV_T;   /* '<S1>/CurrentController' */
  int8_T Integrator_PrevResetState;    /* '<S43>/Integrator' */
  int8_T Integrator_PrevResetState_p;  /* '<S96>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S43>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE_b;  /* '<S96>/Integrator' */
  boolean_T CurrentController_RESET_ELAPS_T;/* '<S1>/CurrentController' */
} DW_CurrentController;

/* Block signals and states (default storage) for system '<S1>/SpeedController' */
typedef struct {
  real32_T Integrator_DSTATE;          /* '<S176>/Integrator' */
  real32_T Integrator_PREV_U;          /* '<S176>/Integrator' */
  uint32_T SpeedController_PREV_T;     /* '<S1>/SpeedController' */
  int8_T Integrator_PrevResetState;    /* '<S176>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S176>/Integrator' */
  boolean_T SpeedController_RESET_ELAPS_T;/* '<S1>/SpeedController' */
} DW_SpeedController;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_SpeedController SpeedController_j;/* '<S1>/SpeedController' */
  DW_CurrentController CurrentController_o;/* '<S1>/CurrentController' */
  real32_T Saturation[3];
  real32_T Switch_m[2];
  real32_T OutportBufferForub;
  real32_T OutportBufferForuc;
  uint8_T is_active_c3_uz_codegen0;    /* '<Root>/uz_codegen' */
  uint8_T is_c3_uz_codegen0;           /* '<Root>/uz_codegen' */
} DW;

/* Invariant block signals for system '<S1>/CurrentController' */
typedef struct {
  const uint8_T Compare_g;             /* '<S128>/Compare' */
  const uint8_T Compare_fz;            /* '<S134>/Compare' */
} ConstB_CurrentController;

/* Invariant block signals (default storage) */
typedef struct {
  ConstB_CurrentController CurrentController_o;/* '<S1>/CurrentController' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S125>/Gain3'
   */
  real32_T Gain3_Gain[9];

  /* Computed Parameter: Gain3_Gain_i
   * Referenced by: '<S116>/Gain3'
   */
  real32_T Gain3_Gain_i[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  int8_T flg_PreCntr;                  /* '<Root>/flg_PreCntr' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T w_el;                       /* '<Root>/w_el' */
  real32_T ia;                         /* '<Root>/ia' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  real32_T iq_ref;                     /* '<Root>/iq_ref' */
  real32_T id_ref;                     /* '<Root>/id_ref' */
  real32_T U_IC;                       /* '<Root>/U_IC' */
  int8_T RESET;                        /* '<Root>/RESET' */
  int8_T START;                        /* '<Root>/START' */
  int8_T flgLimitUdUq;                 /* '<Root>/flgLimitUdUq' */
  int8_T flg_SpaceVectorModulation;    /* '<Root>/flg_SpaceVectorModulation' */
  real32_T Kp_Iq;                      /* '<Root>/Kp_Iq' */
  real32_T Kp_Id;                      /* '<Root>/Kp_Id' */
  real32_T Ki_Iq;                      /* '<Root>/Ki_Iq' */
  real32_T Ki_Id;                      /* '<Root>/Ki_Id' */
  int8_T flg_deadTimeCompensation;     /* '<Root>/flg_deadTimeCompensation' */
  int8_T flg_theta_el_compensation;    /* '<Root>/flg_theta_el_compensation' */
  int8_T flg_SpeedControl;             /* '<Root>/flg_SpeedControl' */
  int8_T flg_FieldWeakening;           /* '<Root>/flg_FieldWeakening' */
  real32_T n_ref;                      /* '<Root>/n_ref' */
  real32_T n_ist;                      /* '<Root>/n_ist' */
  real32_T I_max;                      /* '<Root>/I_max' */
  real32_T Kp_Speed;                   /* '<Root>/Kp_Speed' */
  real32_T Ki_Speed;                   /* '<Root>/Ki_Speed' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Ua_DutyCycle;               /* '<Root>/Ua_DutyCycle' */
  real32_T activeState;                /* '<Root>/activeState' */
  real32_T Uc_DutyCycle;               /* '<Root>/Uc_DutyCycle' */
  real32_T Ub_DutyCycle;               /* '<Root>/Ub_DutyCycle' */
  real32_T iq_ist;                     /* '<Root>/iq_ist' */
  real32_T id_ist;                     /* '<Root>/id_ist' */
  real32_T uq;                         /* '<Root>/uq' */
  real32_T ud;                         /* '<Root>/ud' */
  real32_T iq_soll;                    /* '<Root>/iq_soll' */
  real32_T id_soll;                    /* '<Root>/id_soll' */
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
 * Block '<S51>/Data Type Duplicate' : Unused code path elimination
 * Block '<S51>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S104>/Data Type Duplicate' : Unused code path elimination
 * Block '<S104>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S8>/Scope1' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S9>/Scope' : Unused code path elimination
 * Block '<S2>/Gain' : Unused code path elimination
 * Block '<S122>/Constant' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S184>/Data Type Duplicate' : Unused code path elimination
 * Block '<S184>/Data Type Propagation' : Unused code path elimination
 * Block '<S138>/Scope' : Unused code path elimination
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
 * '<S3>'   : 'uz_codegen/uz_codegen/SpeedController'
 * '<S4>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller'
 * '<S5>'   : 'uz_codegen/uz_codegen/CurrentController/Modulation'
 * '<S6>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Entkopplung'
 * '<S7>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller'
 * '<S8>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller'
 * '<S9>'   : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung'
 * '<S10>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0'
 * '<S11>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller'
 * '<S12>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Anti-windup'
 * '<S13>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/D Gain'
 * '<S14>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Filter'
 * '<S15>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Filter ICs'
 * '<S16>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/I Gain'
 * '<S17>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Ideal P Gain'
 * '<S18>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Ideal P Gain Fdbk'
 * '<S19>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Integrator'
 * '<S20>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Integrator ICs'
 * '<S21>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/N Copy'
 * '<S22>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/N Gain'
 * '<S23>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/P Copy'
 * '<S24>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Parallel P Gain'
 * '<S25>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Reset Signal'
 * '<S26>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Saturation'
 * '<S27>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Saturation Fdbk'
 * '<S28>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Sum'
 * '<S29>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Sum Fdbk'
 * '<S30>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tracking Mode'
 * '<S31>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tracking Mode Sum'
 * '<S32>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tsamp - Integral'
 * '<S33>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tsamp - Ngain'
 * '<S34>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/postSat Signal'
 * '<S35>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/preSat Signal'
 * '<S36>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Anti-windup/Passthrough'
 * '<S37>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/D Gain/Disabled'
 * '<S38>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Filter/Disabled'
 * '<S39>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Filter ICs/Disabled'
 * '<S40>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/I Gain/External Parameters'
 * '<S41>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Ideal P Gain/Passthrough'
 * '<S42>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Ideal P Gain Fdbk/Disabled'
 * '<S43>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Integrator/Discrete'
 * '<S44>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Integrator ICs/Internal IC'
 * '<S45>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/N Copy/Disabled wSignal Specification'
 * '<S46>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/N Gain/Disabled'
 * '<S47>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/P Copy/Disabled'
 * '<S48>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Parallel P Gain/External Parameters'
 * '<S49>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Reset Signal/External Reset'
 * '<S50>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Saturation/External'
 * '<S51>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Saturation/External/Saturation Dynamic'
 * '<S52>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Saturation Fdbk/Disabled'
 * '<S53>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Sum/Sum_PI'
 * '<S54>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Sum Fdbk/Disabled'
 * '<S55>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tracking Mode/Disabled'
 * '<S56>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tracking Mode Sum/Passthrough'
 * '<S57>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tsamp - Integral/Passthrough'
 * '<S58>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/Tsamp - Ngain/Passthrough'
 * '<S59>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/postSat Signal/Forward_Path'
 * '<S60>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Id-Controller/preSat Signal/Forward_Path'
 * '<S61>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller'
 * '<S62>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Anti-windup'
 * '<S63>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/D Gain'
 * '<S64>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Filter'
 * '<S65>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Filter ICs'
 * '<S66>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/I Gain'
 * '<S67>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Ideal P Gain'
 * '<S68>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Ideal P Gain Fdbk'
 * '<S69>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Integrator'
 * '<S70>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Integrator ICs'
 * '<S71>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/N Copy'
 * '<S72>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/N Gain'
 * '<S73>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/P Copy'
 * '<S74>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Parallel P Gain'
 * '<S75>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Reset Signal'
 * '<S76>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Saturation'
 * '<S77>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Saturation Fdbk'
 * '<S78>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Sum'
 * '<S79>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Sum Fdbk'
 * '<S80>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tracking Mode'
 * '<S81>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tracking Mode Sum'
 * '<S82>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tsamp - Integral'
 * '<S83>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tsamp - Ngain'
 * '<S84>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/postSat Signal'
 * '<S85>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/preSat Signal'
 * '<S86>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S87>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S88>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S89>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S90>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/D Gain/Disabled'
 * '<S91>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Filter/Disabled'
 * '<S92>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Filter ICs/Disabled'
 * '<S93>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/I Gain/External Parameters'
 * '<S94>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Ideal P Gain/Passthrough'
 * '<S95>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Ideal P Gain Fdbk/Disabled'
 * '<S96>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Integrator/Discrete'
 * '<S97>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Integrator ICs/Internal IC'
 * '<S98>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/N Copy/Disabled wSignal Specification'
 * '<S99>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/N Gain/Disabled'
 * '<S100>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/P Copy/Disabled'
 * '<S101>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Parallel P Gain/External Parameters'
 * '<S102>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Reset Signal/External Reset'
 * '<S103>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Saturation/External'
 * '<S104>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Saturation/External/Saturation Dynamic'
 * '<S105>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Saturation Fdbk/Disabled'
 * '<S106>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Sum/Sum_PI'
 * '<S107>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Sum Fdbk/Disabled'
 * '<S108>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tracking Mode/Disabled'
 * '<S109>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tracking Mode Sum/Passthrough'
 * '<S110>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tsamp - Integral/Passthrough'
 * '<S111>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/Tsamp - Ngain/Passthrough'
 * '<S112>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/postSat Signal/Forward_Path'
 * '<S113>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Iq_Controller/preSat Signal/Forward_Path'
 * '<S114>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung/MATLAB Function'
 * '<S115>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0'
 * '<S116>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/abc to Alpha-Beta-Zero'
 * '<S117>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S118>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S119>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S120>' : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S121>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle'
 * '<S122>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation'
 * '<S123>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/Subsystem'
 * '<S124>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc'
 * '<S125>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/Alpha-Beta-Zero to abc'
 * '<S126>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero'
 * '<S127>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S128>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S129>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S130>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Subsystem1'
 * '<S131>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/SpaceVectorModulation'
 * '<S132>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero'
 * '<S133>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S134>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S135>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S136>' : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem1'
 * '<S137>' : 'uz_codegen/uz_codegen/SpeedController/speed controller'
 * '<S138>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control'
 * '<S139>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/Field Weakening'
 * '<S140>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller'
 * '<S141>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/Field Weakening/MATLAB Function'
 * '<S142>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup'
 * '<S143>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/D Gain'
 * '<S144>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter'
 * '<S145>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter ICs'
 * '<S146>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/I Gain'
 * '<S147>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain'
 * '<S148>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain Fdbk'
 * '<S149>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator'
 * '<S150>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator ICs'
 * '<S151>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Copy'
 * '<S152>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Gain'
 * '<S153>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/P Copy'
 * '<S154>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Parallel P Gain'
 * '<S155>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Reset Signal'
 * '<S156>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation'
 * '<S157>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation Fdbk'
 * '<S158>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum'
 * '<S159>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum Fdbk'
 * '<S160>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode'
 * '<S161>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode Sum'
 * '<S162>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Integral'
 * '<S163>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Ngain'
 * '<S164>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/postSat Signal'
 * '<S165>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/preSat Signal'
 * '<S166>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S167>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S168>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S169>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S170>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/D Gain/Disabled'
 * '<S171>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter/Disabled'
 * '<S172>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter ICs/Disabled'
 * '<S173>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/I Gain/External Parameters'
 * '<S174>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain/Passthrough'
 * '<S175>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S176>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator/Discrete'
 * '<S177>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator ICs/Internal IC'
 * '<S178>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S179>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Gain/Disabled'
 * '<S180>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/P Copy/Disabled'
 * '<S181>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Parallel P Gain/External Parameters'
 * '<S182>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Reset Signal/External Reset'
 * '<S183>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation/External'
 * '<S184>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation/External/Saturation Dynamic'
 * '<S185>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation Fdbk/Disabled'
 * '<S186>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum/Sum_PI'
 * '<S187>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum Fdbk/Disabled'
 * '<S188>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode/Disabled'
 * '<S189>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S190>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Integral/Passthrough'
 * '<S191>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S192>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/postSat Signal/Forward_Path'
 * '<S193>' : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/preSat Signal/Forward_Path'
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
