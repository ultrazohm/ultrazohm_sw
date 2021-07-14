/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.33
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 14 10:03:41 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (8), Warnings (2), Errors (2)
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
  real_T Gain1[3];                     /* '<S16>/Gain1' */
  real_T Fcn;                          /* '<S35>/Fcn' */
  real_T Fcn1;                         /* '<S35>/Fcn1' */
  real_T Fcn_b;                        /* '<S34>/Fcn' */
  real_T Fcn1_h;                       /* '<S34>/Fcn1' */
  real_T Fcn_d;                        /* '<S29>/Fcn' */
  real_T Fcn1_o;                       /* '<S29>/Fcn1' */
  real_T Fcn_g;                        /* '<S28>/Fcn' */
  real_T Fcn1_p;                       /* '<S28>/Fcn1' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S7>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_g;/* '<S8>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_PREV_U;/* '<S7>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_PREV_U_j;/* '<S8>/Discrete-Time Integrator' */
  real_T a_W_on;
  real_T c;
  real_T U_max;
  real_T u2;
  real_T U_max_dq;                     /* '<S2>/Gain' */
  real_T error;                        /* '<S7>/Subtract' */
  real_T Sum_l;                        /* '<S7>/Sum' */
  real_T Gain_j;                       /* '<S7>/Gain' */
  real_T Switch1_c;                    /* '<S6>/Switch1' */
  real_T Gain_c;                       /* '<S9>/Gain' */
  uint32_T CurrentController_PREV_T;   /* '<S1>/CurrentController' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S7>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_j;/* '<S8>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_E;/* '<S7>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_c;/* '<S8>/Discrete-Time Integrator' */
  boolean_T CurrentController_RESET_ELAPS_T;/* '<S1>/CurrentController' */
} DW_CurrentController;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_CurrentController CurrentController_o;/* '<S1>/CurrentController' */
  real_T Switch_e[3];
  real_T Switch_m[2];
  real_T Integrator_DSTATE;            /* '<S73>/Integrator' */
  real_T Integrator_PREV_U;            /* '<S73>/Integrator' */
  real_T IProdOut;                     /* '<S70>/IProd Out' */
  real_T Sum;                          /* '<S83>/Sum' */
  real_T SignPreIntegrator;            /* '<S63>/SignPreIntegrator' */
  real_T Integrator;
  real_T rtb_IProdOut_m;
  uint32_T SpeedController_PREV_T;     /* '<S1>/SpeedController' */
  int8_T Integrator_PrevResetState;    /* '<S73>/Integrator' */
  uint8_T is_active_c3_uz_codegen0;    /* '<Root>/uz_codegen' */
  uint8_T is_c3_uz_codegen0;           /* '<Root>/uz_codegen' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S73>/Integrator' */
  boolean_T SpeedController_RESET_ELAPS_T;/* '<S1>/SpeedController' */
} DW;

/* Invariant block signals for system '<S1>/CurrentController' */
typedef struct {
  const uint8_T Compare_g;             /* '<S27>/Compare' */
  const uint8_T Compare_fz;            /* '<S33>/Compare' */
} ConstB_CurrentController;

/* Invariant block signals (default storage) */
typedef struct {
  ConstB_CurrentController CurrentController_o;/* '<S1>/CurrentController' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [ 1   0   1; -1/2  sqrt(3)/2   1; -1/2  -sqrt(3)/2  1 ]
   * Referenced by: '<S24>/Gain3'
   */
  real_T Gain3_Gain[9];

  /* Expression: [ 1   -1/2   -1/2; 0   sqrt(3)/2   -sqrt(3)/2; 1/2  1/2  1/2 ]
   * Referenced by: '<S16>/Gain3'
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
  real32_T flg_SpeedControl;           /* '<Root>/flg_SpeedControl' */
  real32_T flg_FieldWeakening;         /* '<Root>/flg_FieldWeakening' */
  real32_T n_ref;                      /* '<Root>/n_ref' */
  real32_T n_ist;                      /* '<Root>/n_ist' */
  real32_T I_max;                      /* '<Root>/I_max' */
  real32_T Kp_Speed;                   /* '<Root>/Kp_Speed' */
  real32_T Ki_Speed;                   /* '<Root>/Ki_Speed' */
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
  real_T iq_soll;                      /* '<Root>/iq_soll' */
  real_T id_soll;                      /* '<Root>/id_soll' */
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
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Propagation' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Propagation' : Unused code path elimination
 * Block '<S22>/Constant' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Propagation' : Unused code path elimination
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
 * '<S11>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Id-Controller/Saturation Dynamic'
 * '<S12>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Iq-Controller/Saturation Dynamic'
 * '<S13>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung/Saturation Dynamic'
 * '<S14>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/Spannungsbegrenzung/Saturation Dynamic1'
 * '<S15>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0'
 * '<S16>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/abc to Alpha-Beta-Zero'
 * '<S17>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S18>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S19>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S20>'  : 'uz_codegen/uz_codegen/CurrentController/Current Controller/abc to dq0/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S21>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle'
 * '<S22>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation'
 * '<S23>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc'
 * '<S24>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/Alpha-Beta-Zero to abc'
 * '<S25>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero'
 * '<S26>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S27>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S28>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S29>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/DutyCycle/dq0 to abc/dq0 to Alpha-Beta-Zero/Subsystem1'
 * '<S30>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/SpaceVectorModulation'
 * '<S31>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero'
 * '<S32>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant'
 * '<S33>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Compare To Constant1'
 * '<S34>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem - pi//2 delay'
 * '<S35>'  : 'uz_codegen/uz_codegen/CurrentController/Modulation/SpaceVectorModulation/dq0 to Alpha-Beta-Zero/Subsystem1'
 * '<S36>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller'
 * '<S37>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control'
 * '<S38>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller'
 * '<S39>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup'
 * '<S40>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/D Gain'
 * '<S41>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter'
 * '<S42>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter ICs'
 * '<S43>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/I Gain'
 * '<S44>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain'
 * '<S45>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain Fdbk'
 * '<S46>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator'
 * '<S47>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator ICs'
 * '<S48>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Copy'
 * '<S49>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Gain'
 * '<S50>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/P Copy'
 * '<S51>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Parallel P Gain'
 * '<S52>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Reset Signal'
 * '<S53>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation'
 * '<S54>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation Fdbk'
 * '<S55>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum'
 * '<S56>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum Fdbk'
 * '<S57>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode'
 * '<S58>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode Sum'
 * '<S59>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Integral'
 * '<S60>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Ngain'
 * '<S61>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/postSat Signal'
 * '<S62>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/preSat Signal'
 * '<S63>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S64>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S65>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S66>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S67>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/D Gain/Disabled'
 * '<S68>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter/Disabled'
 * '<S69>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Filter ICs/Disabled'
 * '<S70>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/I Gain/External Parameters'
 * '<S71>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain/Passthrough'
 * '<S72>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S73>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator/Discrete'
 * '<S74>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Integrator ICs/Internal IC'
 * '<S75>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S76>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/N Gain/Disabled'
 * '<S77>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/P Copy/Disabled'
 * '<S78>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Parallel P Gain/External Parameters'
 * '<S79>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Reset Signal/External Reset'
 * '<S80>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation/External'
 * '<S81>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation/External/Saturation Dynamic'
 * '<S82>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Saturation Fdbk/Disabled'
 * '<S83>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum/Sum_PI'
 * '<S84>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Sum Fdbk/Disabled'
 * '<S85>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode/Disabled'
 * '<S86>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S87>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Integral/Passthrough'
 * '<S88>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S89>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/postSat Signal/Forward_Path'
 * '<S90>'  : 'uz_codegen/uz_codegen/SpeedController/speed controller/PI_Speed_Control/PID Controller/preSat Signal/Forward_Path'
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
