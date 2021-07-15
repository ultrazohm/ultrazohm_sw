/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Strom.h
 *
 * Code generated for Simulink model 'FOC_Strom'.
 *
 * Model version                  : 2.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 14 12:08:25 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_FOC_Strom_h_
#define RTW_HEADER_FOC_Strom_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef FOC_Strom_COMMON_INCLUDES_
#define FOC_Strom_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Strom_COMMON_INCLUDES_ */

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

#define FOC_Strom_M                    (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S45>/Integrator' */
  real_T Integrator_DSTATE_a;          /* '<S93>/Integrator' */
  real_T alpha_b;                      /* '<S5>/Gain' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S1>/Switch Case' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Act_Iv;                       /* '<Root>/Act_Iv' */
  real_T Act_Iu;                       /* '<Root>/Act_Iu' */
  real_T Act_w_el;                     /* '<Root>/Act_w_el' */
  real_T Act_theta_el;                 /* '<Root>/Act_theta_el' */
  real_T Act_Iw;                       /* '<Root>/Act_Iw' */
  real_T Act_U_ZK;                     /* '<Root>/Act_U_ZK' */
  real_T Ref_Iq;                       /* '<Root>/Ref_Iq' */
  real_T Ref_Id;                       /* '<Root>/Ref_Id' */
  real_T fl_decoupling;                /* '<Root>/fl_decoupling' */
  real_T fl_power;                     /* '<Root>/fl_power' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T a_U;                          /* '<Root>/a_U' */
  real_T a_V;                          /* '<Root>/a_V' */
  real_T a_W;                          /* '<Root>/a_W' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T K_R_id;                       /* Variable: K_R_id
                                        * Referenced by: '<S42>/Integral Gain'
                                        */
  real_T K_R_iq;                       /* Variable: K_R_iq
                                        * Referenced by: '<S90>/Integral Gain'
                                        */
  real_T L_d;                          /* Variable: L_d
                                        * Referenced by: '<S12>/Gain1'
                                        */
  real_T L_q;                          /* Variable: L_q
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T P_R_id;                       /* Variable: P_R_id
                                        * Referenced by: '<S43>/Proportional Gain'
                                        */
  real_T P_R_iq;                       /* Variable: P_R_iq
                                        * Referenced by: '<S91>/Proportional Gain'
                                        */
  real_T Psi_PM;                       /* Variable: Psi_PM
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T PI_d_InitialConditionForIntegra;
                              /* Mask Parameter: PI_d_InitialConditionForIntegra
                               * Referenced by: '<S45>/Integrator'
                               */
  real_T PI_q_InitialConditionForIntegra;
                              /* Mask Parameter: PI_q_InitialConditionForIntegra
                               * Referenced by: '<S93>/Integrator'
                               */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S13>/Constant1'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S45>/Integrator'
                                        */
  real_T Integrator_gainval_p;       /* Computed Parameter: Integrator_gainval_p
                                      * Referenced by: '<S93>/Integrator'
                                      */
  real_T Gain_Gain;                    /* Expression: 1/2
                                        * Referenced by: '<S110>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/2*sqrt(3)
                                        * Referenced by: '<S110>/Gain1'
                                        */
  real_T Constant2_Value;              /* Expression: 1/2
                                        * Referenced by: '<S11>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 1/2
                                        * Referenced by: '<S11>/Constant3'
                                        */
  real_T Gain2_Gain;                   /* Expression: 2
                                        * Referenced by: '<S110>/Gain2'
                                        */
  real_T Constant1_Value_i;            /* Expression: 1/2
                                        * Referenced by: '<S11>/Constant1'
                                        */
  real_T Constant_Value_p;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Gain2_Gain_g;                 /* Expression: 2
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real_T Gain_Gain_c;                  /* Expression: 1/3
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: 1/3*sqrt(3)
                                        * Referenced by: '<S5>/Gain1'
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
extern void FOC_Strom_initialize(RT_MODEL *const rtM);
extern void FOC_Strom_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_codegen_FOC_Current/FOC_Strom')    - opens subsystem uz_codegen_FOC_Current/FOC_Strom
 * hilite_system('uz_codegen_FOC_Current/FOC_Strom/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen_FOC_Current'
 * '<S1>'   : 'uz_codegen_FOC_Current/FOC_Strom'
 * '<S2>'   : 'uz_codegen_FOC_Current/FOC_Strom/Strang-Rotor'
 * '<S3>'   : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem'
 * '<S4>'   : 'uz_codegen_FOC_Current/FOC_Strom/Switch Case Action Subsystem'
 * '<S5>'   : 'uz_codegen_FOC_Current/FOC_Strom/Strang-Rotor/Clarke-Transformation'
 * '<S6>'   : 'uz_codegen_FOC_Current/FOC_Strom/Strang-Rotor/Park-Transformation'
 * '<S7>'   : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Entkopplung'
 * '<S8>'   : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d'
 * '<S9>'   : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q'
 * '<S10>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Rotor-Strang'
 * '<S11>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Tastgradbestimmung'
 * '<S12>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Entkopplung/Switch Case Action Subsystem'
 * '<S13>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Entkopplung/Switch Case Action Subsystem1'
 * '<S14>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Anti-windup'
 * '<S15>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/D Gain'
 * '<S16>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Filter'
 * '<S17>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Filter ICs'
 * '<S18>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/I Gain'
 * '<S19>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Ideal P Gain'
 * '<S20>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Ideal P Gain Fdbk'
 * '<S21>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Integrator'
 * '<S22>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Integrator ICs'
 * '<S23>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/N Copy'
 * '<S24>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/N Gain'
 * '<S25>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/P Copy'
 * '<S26>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Parallel P Gain'
 * '<S27>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Reset Signal'
 * '<S28>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Saturation'
 * '<S29>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Saturation Fdbk'
 * '<S30>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Sum'
 * '<S31>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Sum Fdbk'
 * '<S32>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tracking Mode'
 * '<S33>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tracking Mode Sum'
 * '<S34>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tsamp - Integral'
 * '<S35>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tsamp - Ngain'
 * '<S36>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/postSat Signal'
 * '<S37>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/preSat Signal'
 * '<S38>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Anti-windup/Passthrough'
 * '<S39>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/D Gain/Disabled'
 * '<S40>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Filter/Disabled'
 * '<S41>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Filter ICs/Disabled'
 * '<S42>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/I Gain/Internal Parameters'
 * '<S43>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Ideal P Gain/Internal Parameters'
 * '<S44>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Ideal P Gain Fdbk/Disabled'
 * '<S45>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Integrator/Discrete'
 * '<S46>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Integrator ICs/Internal IC'
 * '<S47>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/N Copy/Disabled wSignal Specification'
 * '<S48>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/N Gain/Disabled'
 * '<S49>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/P Copy/Disabled'
 * '<S50>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Parallel P Gain/Passthrough'
 * '<S51>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Reset Signal/Disabled'
 * '<S52>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Saturation/Passthrough'
 * '<S53>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Saturation Fdbk/Disabled'
 * '<S54>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Sum/Sum_PI'
 * '<S55>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Sum Fdbk/Disabled'
 * '<S56>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tracking Mode/Disabled'
 * '<S57>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tracking Mode Sum/Passthrough'
 * '<S58>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tsamp - Integral/Passthrough'
 * '<S59>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/Tsamp - Ngain/Passthrough'
 * '<S60>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/postSat Signal/Forward_Path'
 * '<S61>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_d/preSat Signal/Forward_Path'
 * '<S62>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Anti-windup'
 * '<S63>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/D Gain'
 * '<S64>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Filter'
 * '<S65>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Filter ICs'
 * '<S66>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/I Gain'
 * '<S67>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Ideal P Gain'
 * '<S68>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Ideal P Gain Fdbk'
 * '<S69>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Integrator'
 * '<S70>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Integrator ICs'
 * '<S71>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/N Copy'
 * '<S72>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/N Gain'
 * '<S73>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/P Copy'
 * '<S74>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Parallel P Gain'
 * '<S75>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Reset Signal'
 * '<S76>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Saturation'
 * '<S77>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Saturation Fdbk'
 * '<S78>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Sum'
 * '<S79>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Sum Fdbk'
 * '<S80>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tracking Mode'
 * '<S81>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tracking Mode Sum'
 * '<S82>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tsamp - Integral'
 * '<S83>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tsamp - Ngain'
 * '<S84>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/postSat Signal'
 * '<S85>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/preSat Signal'
 * '<S86>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Anti-windup/Passthrough'
 * '<S87>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/D Gain/Disabled'
 * '<S88>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Filter/Disabled'
 * '<S89>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Filter ICs/Disabled'
 * '<S90>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/I Gain/Internal Parameters'
 * '<S91>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Ideal P Gain/Internal Parameters'
 * '<S92>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Ideal P Gain Fdbk/Disabled'
 * '<S93>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Integrator/Discrete'
 * '<S94>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Integrator ICs/Internal IC'
 * '<S95>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/N Copy/Disabled wSignal Specification'
 * '<S96>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/N Gain/Disabled'
 * '<S97>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/P Copy/Disabled'
 * '<S98>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Parallel P Gain/Passthrough'
 * '<S99>'  : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Reset Signal/Disabled'
 * '<S100>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Saturation/Passthrough'
 * '<S101>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Saturation Fdbk/Disabled'
 * '<S102>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Sum/Sum_PI'
 * '<S103>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Sum Fdbk/Disabled'
 * '<S104>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tracking Mode/Disabled'
 * '<S105>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tracking Mode Sum/Passthrough'
 * '<S106>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tsamp - Integral/Passthrough'
 * '<S107>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/Tsamp - Ngain/Passthrough'
 * '<S108>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/postSat Signal/Forward_Path'
 * '<S109>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/PI_q/preSat Signal/Forward_Path'
 * '<S110>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Rotor-Strang/Inverse-Clark-Transformation'
 * '<S111>' : 'uz_codegen_FOC_Current/FOC_Strom/Subsystem/Rotor-Strang/Inverse-Park-Transormation'
 */

/*-
 * Requirements for '<Root>': FOC_Strom
 */
#endif                                 /* RTW_HEADER_FOC_Strom_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
