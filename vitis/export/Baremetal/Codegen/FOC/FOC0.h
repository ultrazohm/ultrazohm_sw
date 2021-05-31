/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC0.h
 *
 * Code generated for Simulink model 'FOC0'.
 *
 * Model version                  : 6.2
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Tue May 25 15:31:25 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (7), Warnings (3), Errors (2)
 */

#ifndef RTW_HEADER_FOC0_h_
#define RTW_HEADER_FOC0_h_
#include <math.h>
#include <string.h>
#ifndef FOC0_COMMON_INCLUDES_
#define FOC0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC0_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
#define rtmGetBlockIO(rtm)             ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
#define rtmSetBlockIO(rtm, val)        ((rtm)->blockIO = (val))
#endif

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

#define FOC0_M                         (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals (default storage) */
typedef struct {
  real32_T Fcn;                        /* '<S166>/Fcn' */
  real32_T Fcn1;                       /* '<S166>/Fcn1' */
  real32_T Fcn_i;                      /* '<S165>/Fcn' */
  real32_T Fcn1_e;                     /* '<S165>/Fcn1' */
  real32_T Fcn_h;                      /* '<S12>/Fcn' */
  real32_T Fcn1_o;                     /* '<S12>/Fcn1' */
  real32_T Fcn_ig;                     /* '<S11>/Fcn' */
  real32_T Fcn1_j;                     /* '<S11>/Fcn1' */
} B;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S96>/Integrator' */
  real_T Integrator_DSTATE_a;          /* '<S46>/Integrator' */
  real_T Integrator_DSTATE_k;          /* '<S146>/Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S96>/Integrator' */
  int8_T Integrator_PrevResetState_c;  /* '<S146>/Integrator' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const uint8_T Compare;               /* '<S9>/Compare' */
  const uint8_T Compare_o;             /* '<S10>/Compare' */
  const uint8_T Compare_b;             /* '<S163>/Compare' */
  const uint8_T Compare_c;             /* '<S164>/Compare' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S7>/Gain3'
   */
  real32_T Gain3_Gain[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T u_dc;                       /* '<Root>/u_dc' */
  uint16_T period;                     /* '<Root>/period' */
  real32_T id_ref;                     /* '<Root>/id_ref' */
  real32_T iq_ref;                     /* '<Root>/iq_ref' */
  real32_T i1;                         /* '<Root>/i1' */
  real32_T i2;                         /* '<Root>/i2' */
  real32_T i3;                         /* '<Root>/i3' */
  real32_T u1;                         /* '<Root>/u1' */
  real32_T u2;                         /* '<Root>/u2' */
  real32_T u3;                         /* '<Root>/u3' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  uint16_T currentORspeedControl;      /* '<Root>/currentORspeedControl' */
  real32_T n_RPM;                      /* '<Root>/n_RPM' */
  real32_T n_ref_RPM;                  /* '<Root>/n_ref_RPM' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int16_T CMPA_1;                      /* '<Root>/CMPA_1' */
  int16_T CMPA_2;                      /* '<Root>/CMPA_2' */
  int16_T CMPA_3;                      /* '<Root>/CMPA_3' */
  int32_T sector;                      /* '<Root>/sector' */
  real32_T id;                         /* '<Root>/id' */
  real32_T iq;                         /* '<Root>/iq' */
  real32_T ud_ctrl;                    /* '<Root>/ud_ctrl' */
  real32_T uq_ctrl;                    /* '<Root>/uq_ctrl' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  B *blockIO;
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T Kpd;                     /* Variable: Kpd
                                        * Referenced by:
                                        *   '<S94>/Proportional Gain'
                                        *   '<S100>/P Copy'
                                        */
extern real_T Kpn;                     /* Variable: Kpn
                                        * Referenced by:
                                        *   '<S44>/Proportional Gain'
                                        *   '<S50>/P Copy'
                                        */
extern real_T Kpq;                     /* Variable: Kpq
                                        * Referenced by:
                                        *   '<S144>/Proportional Gain'
                                        *   '<S150>/P Copy'
                                        */
extern real_T Tnd;                     /* Variable: Tnd
                                        * Referenced by: '<S93>/Integral Gain'
                                        */
extern real_T Tnn;                     /* Variable: Tnn
                                        * Referenced by: '<S43>/Integral Gain'
                                        */
extern real_T Tnq;                     /* Variable: Tnq
                                        * Referenced by: '<S143>/Integral Gain'
                                        */

/* Model entry point functions */
extern void FOC0_initialize(RT_MODEL *const rtM);
extern void FOC0_step(RT_MODEL *const rtM);
extern void FOC0_terminate(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Conversion9' : Eliminate redundant data type conversion
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
 * hilite_system('FOC/FOC')    - opens subsystem FOC/FOC
 * hilite_system('FOC/FOC/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FOC'
 * '<S1>'   : 'FOC/FOC'
 * '<S2>'   : 'FOC/FOC/Alpha-Beta-Zero to dq0'
 * '<S3>'   : 'FOC/FOC/PI speed controller'
 * '<S4>'   : 'FOC/FOC/PID Controller2'
 * '<S5>'   : 'FOC/FOC/PID Controller3'
 * '<S6>'   : 'FOC/FOC/RZM_Traegerbasiert'
 * '<S7>'   : 'FOC/FOC/abc to Alpha-Beta-Zero'
 * '<S8>'   : 'FOC/FOC/dq0 to Alpha-Beta-Zero1'
 * '<S9>'   : 'FOC/FOC/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S10>'  : 'FOC/FOC/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S11>'  : 'FOC/FOC/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S12>'  : 'FOC/FOC/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S13>'  : 'FOC/FOC/PI speed controller/Anti-windup'
 * '<S14>'  : 'FOC/FOC/PI speed controller/D Gain'
 * '<S15>'  : 'FOC/FOC/PI speed controller/Filter'
 * '<S16>'  : 'FOC/FOC/PI speed controller/Filter ICs'
 * '<S17>'  : 'FOC/FOC/PI speed controller/I Gain'
 * '<S18>'  : 'FOC/FOC/PI speed controller/Ideal P Gain'
 * '<S19>'  : 'FOC/FOC/PI speed controller/Ideal P Gain Fdbk'
 * '<S20>'  : 'FOC/FOC/PI speed controller/Integrator'
 * '<S21>'  : 'FOC/FOC/PI speed controller/Integrator ICs'
 * '<S22>'  : 'FOC/FOC/PI speed controller/N Copy'
 * '<S23>'  : 'FOC/FOC/PI speed controller/N Gain'
 * '<S24>'  : 'FOC/FOC/PI speed controller/P Copy'
 * '<S25>'  : 'FOC/FOC/PI speed controller/Parallel P Gain'
 * '<S26>'  : 'FOC/FOC/PI speed controller/Reset Signal'
 * '<S27>'  : 'FOC/FOC/PI speed controller/Saturation'
 * '<S28>'  : 'FOC/FOC/PI speed controller/Saturation Fdbk'
 * '<S29>'  : 'FOC/FOC/PI speed controller/Sum'
 * '<S30>'  : 'FOC/FOC/PI speed controller/Sum Fdbk'
 * '<S31>'  : 'FOC/FOC/PI speed controller/Tracking Mode'
 * '<S32>'  : 'FOC/FOC/PI speed controller/Tracking Mode Sum'
 * '<S33>'  : 'FOC/FOC/PI speed controller/Tsamp - Integral'
 * '<S34>'  : 'FOC/FOC/PI speed controller/Tsamp - Ngain'
 * '<S35>'  : 'FOC/FOC/PI speed controller/postSat Signal'
 * '<S36>'  : 'FOC/FOC/PI speed controller/preSat Signal'
 * '<S37>'  : 'FOC/FOC/PI speed controller/Anti-windup/Disc. Clamping Ideal'
 * '<S38>'  : 'FOC/FOC/PI speed controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S39>'  : 'FOC/FOC/PI speed controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S40>'  : 'FOC/FOC/PI speed controller/D Gain/Disabled'
 * '<S41>'  : 'FOC/FOC/PI speed controller/Filter/Disabled'
 * '<S42>'  : 'FOC/FOC/PI speed controller/Filter ICs/Disabled'
 * '<S43>'  : 'FOC/FOC/PI speed controller/I Gain/Internal Parameters'
 * '<S44>'  : 'FOC/FOC/PI speed controller/Ideal P Gain/Internal Parameters'
 * '<S45>'  : 'FOC/FOC/PI speed controller/Ideal P Gain Fdbk/Disabled'
 * '<S46>'  : 'FOC/FOC/PI speed controller/Integrator/Discrete'
 * '<S47>'  : 'FOC/FOC/PI speed controller/Integrator ICs/Internal IC'
 * '<S48>'  : 'FOC/FOC/PI speed controller/N Copy/Disabled wSignal Specification'
 * '<S49>'  : 'FOC/FOC/PI speed controller/N Gain/Disabled'
 * '<S50>'  : 'FOC/FOC/PI speed controller/P Copy/Internal Parameters Ideal'
 * '<S51>'  : 'FOC/FOC/PI speed controller/Parallel P Gain/Passthrough'
 * '<S52>'  : 'FOC/FOC/PI speed controller/Reset Signal/Disabled'
 * '<S53>'  : 'FOC/FOC/PI speed controller/Saturation/Enabled'
 * '<S54>'  : 'FOC/FOC/PI speed controller/Saturation Fdbk/Disabled'
 * '<S55>'  : 'FOC/FOC/PI speed controller/Sum/Sum_PI'
 * '<S56>'  : 'FOC/FOC/PI speed controller/Sum Fdbk/Disabled'
 * '<S57>'  : 'FOC/FOC/PI speed controller/Tracking Mode/Disabled'
 * '<S58>'  : 'FOC/FOC/PI speed controller/Tracking Mode Sum/Passthrough'
 * '<S59>'  : 'FOC/FOC/PI speed controller/Tsamp - Integral/Passthrough'
 * '<S60>'  : 'FOC/FOC/PI speed controller/Tsamp - Ngain/Passthrough'
 * '<S61>'  : 'FOC/FOC/PI speed controller/postSat Signal/Forward_Path'
 * '<S62>'  : 'FOC/FOC/PI speed controller/preSat Signal/Forward_Path'
 * '<S63>'  : 'FOC/FOC/PID Controller2/Anti-windup'
 * '<S64>'  : 'FOC/FOC/PID Controller2/D Gain'
 * '<S65>'  : 'FOC/FOC/PID Controller2/Filter'
 * '<S66>'  : 'FOC/FOC/PID Controller2/Filter ICs'
 * '<S67>'  : 'FOC/FOC/PID Controller2/I Gain'
 * '<S68>'  : 'FOC/FOC/PID Controller2/Ideal P Gain'
 * '<S69>'  : 'FOC/FOC/PID Controller2/Ideal P Gain Fdbk'
 * '<S70>'  : 'FOC/FOC/PID Controller2/Integrator'
 * '<S71>'  : 'FOC/FOC/PID Controller2/Integrator ICs'
 * '<S72>'  : 'FOC/FOC/PID Controller2/N Copy'
 * '<S73>'  : 'FOC/FOC/PID Controller2/N Gain'
 * '<S74>'  : 'FOC/FOC/PID Controller2/P Copy'
 * '<S75>'  : 'FOC/FOC/PID Controller2/Parallel P Gain'
 * '<S76>'  : 'FOC/FOC/PID Controller2/Reset Signal'
 * '<S77>'  : 'FOC/FOC/PID Controller2/Saturation'
 * '<S78>'  : 'FOC/FOC/PID Controller2/Saturation Fdbk'
 * '<S79>'  : 'FOC/FOC/PID Controller2/Sum'
 * '<S80>'  : 'FOC/FOC/PID Controller2/Sum Fdbk'
 * '<S81>'  : 'FOC/FOC/PID Controller2/Tracking Mode'
 * '<S82>'  : 'FOC/FOC/PID Controller2/Tracking Mode Sum'
 * '<S83>'  : 'FOC/FOC/PID Controller2/Tsamp - Integral'
 * '<S84>'  : 'FOC/FOC/PID Controller2/Tsamp - Ngain'
 * '<S85>'  : 'FOC/FOC/PID Controller2/postSat Signal'
 * '<S86>'  : 'FOC/FOC/PID Controller2/preSat Signal'
 * '<S87>'  : 'FOC/FOC/PID Controller2/Anti-windup/Disc. Clamping Ideal'
 * '<S88>'  : 'FOC/FOC/PID Controller2/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S89>'  : 'FOC/FOC/PID Controller2/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S90>'  : 'FOC/FOC/PID Controller2/D Gain/Disabled'
 * '<S91>'  : 'FOC/FOC/PID Controller2/Filter/Disabled'
 * '<S92>'  : 'FOC/FOC/PID Controller2/Filter ICs/Disabled'
 * '<S93>'  : 'FOC/FOC/PID Controller2/I Gain/Internal Parameters'
 * '<S94>'  : 'FOC/FOC/PID Controller2/Ideal P Gain/Internal Parameters'
 * '<S95>'  : 'FOC/FOC/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S96>'  : 'FOC/FOC/PID Controller2/Integrator/Discrete'
 * '<S97>'  : 'FOC/FOC/PID Controller2/Integrator ICs/Internal IC'
 * '<S98>'  : 'FOC/FOC/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S99>'  : 'FOC/FOC/PID Controller2/N Gain/Disabled'
 * '<S100>' : 'FOC/FOC/PID Controller2/P Copy/Internal Parameters Ideal'
 * '<S101>' : 'FOC/FOC/PID Controller2/Parallel P Gain/Passthrough'
 * '<S102>' : 'FOC/FOC/PID Controller2/Reset Signal/External Reset'
 * '<S103>' : 'FOC/FOC/PID Controller2/Saturation/Enabled'
 * '<S104>' : 'FOC/FOC/PID Controller2/Saturation Fdbk/Disabled'
 * '<S105>' : 'FOC/FOC/PID Controller2/Sum/Sum_PI'
 * '<S106>' : 'FOC/FOC/PID Controller2/Sum Fdbk/Disabled'
 * '<S107>' : 'FOC/FOC/PID Controller2/Tracking Mode/Disabled'
 * '<S108>' : 'FOC/FOC/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S109>' : 'FOC/FOC/PID Controller2/Tsamp - Integral/Passthrough'
 * '<S110>' : 'FOC/FOC/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S111>' : 'FOC/FOC/PID Controller2/postSat Signal/Forward_Path'
 * '<S112>' : 'FOC/FOC/PID Controller2/preSat Signal/Forward_Path'
 * '<S113>' : 'FOC/FOC/PID Controller3/Anti-windup'
 * '<S114>' : 'FOC/FOC/PID Controller3/D Gain'
 * '<S115>' : 'FOC/FOC/PID Controller3/Filter'
 * '<S116>' : 'FOC/FOC/PID Controller3/Filter ICs'
 * '<S117>' : 'FOC/FOC/PID Controller3/I Gain'
 * '<S118>' : 'FOC/FOC/PID Controller3/Ideal P Gain'
 * '<S119>' : 'FOC/FOC/PID Controller3/Ideal P Gain Fdbk'
 * '<S120>' : 'FOC/FOC/PID Controller3/Integrator'
 * '<S121>' : 'FOC/FOC/PID Controller3/Integrator ICs'
 * '<S122>' : 'FOC/FOC/PID Controller3/N Copy'
 * '<S123>' : 'FOC/FOC/PID Controller3/N Gain'
 * '<S124>' : 'FOC/FOC/PID Controller3/P Copy'
 * '<S125>' : 'FOC/FOC/PID Controller3/Parallel P Gain'
 * '<S126>' : 'FOC/FOC/PID Controller3/Reset Signal'
 * '<S127>' : 'FOC/FOC/PID Controller3/Saturation'
 * '<S128>' : 'FOC/FOC/PID Controller3/Saturation Fdbk'
 * '<S129>' : 'FOC/FOC/PID Controller3/Sum'
 * '<S130>' : 'FOC/FOC/PID Controller3/Sum Fdbk'
 * '<S131>' : 'FOC/FOC/PID Controller3/Tracking Mode'
 * '<S132>' : 'FOC/FOC/PID Controller3/Tracking Mode Sum'
 * '<S133>' : 'FOC/FOC/PID Controller3/Tsamp - Integral'
 * '<S134>' : 'FOC/FOC/PID Controller3/Tsamp - Ngain'
 * '<S135>' : 'FOC/FOC/PID Controller3/postSat Signal'
 * '<S136>' : 'FOC/FOC/PID Controller3/preSat Signal'
 * '<S137>' : 'FOC/FOC/PID Controller3/Anti-windup/Disc. Clamping Ideal'
 * '<S138>' : 'FOC/FOC/PID Controller3/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S139>' : 'FOC/FOC/PID Controller3/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S140>' : 'FOC/FOC/PID Controller3/D Gain/Disabled'
 * '<S141>' : 'FOC/FOC/PID Controller3/Filter/Disabled'
 * '<S142>' : 'FOC/FOC/PID Controller3/Filter ICs/Disabled'
 * '<S143>' : 'FOC/FOC/PID Controller3/I Gain/Internal Parameters'
 * '<S144>' : 'FOC/FOC/PID Controller3/Ideal P Gain/Internal Parameters'
 * '<S145>' : 'FOC/FOC/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S146>' : 'FOC/FOC/PID Controller3/Integrator/Discrete'
 * '<S147>' : 'FOC/FOC/PID Controller3/Integrator ICs/Internal IC'
 * '<S148>' : 'FOC/FOC/PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S149>' : 'FOC/FOC/PID Controller3/N Gain/Disabled'
 * '<S150>' : 'FOC/FOC/PID Controller3/P Copy/Internal Parameters Ideal'
 * '<S151>' : 'FOC/FOC/PID Controller3/Parallel P Gain/Passthrough'
 * '<S152>' : 'FOC/FOC/PID Controller3/Reset Signal/External Reset'
 * '<S153>' : 'FOC/FOC/PID Controller3/Saturation/Enabled'
 * '<S154>' : 'FOC/FOC/PID Controller3/Saturation Fdbk/Disabled'
 * '<S155>' : 'FOC/FOC/PID Controller3/Sum/Sum_PI'
 * '<S156>' : 'FOC/FOC/PID Controller3/Sum Fdbk/Disabled'
 * '<S157>' : 'FOC/FOC/PID Controller3/Tracking Mode/Disabled'
 * '<S158>' : 'FOC/FOC/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S159>' : 'FOC/FOC/PID Controller3/Tsamp - Integral/Passthrough'
 * '<S160>' : 'FOC/FOC/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S161>' : 'FOC/FOC/PID Controller3/postSat Signal/Forward_Path'
 * '<S162>' : 'FOC/FOC/PID Controller3/preSat Signal/Forward_Path'
 * '<S163>' : 'FOC/FOC/dq0 to Alpha-Beta-Zero1/Compare To Constant'
 * '<S164>' : 'FOC/FOC/dq0 to Alpha-Beta-Zero1/Compare To Constant1'
 * '<S165>' : 'FOC/FOC/dq0 to Alpha-Beta-Zero1/Subsystem - pi//2 delay'
 * '<S166>' : 'FOC/FOC/dq0 to Alpha-Beta-Zero1/Subsystem1'
 */

/*-
 * Requirements for '<Root>': FOC0
 */
#endif                                 /* RTW_HEADER_FOC0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
