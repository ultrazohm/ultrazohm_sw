/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Strom_einfach.h
 *
 * Code generated for Simulink model 'FOC_Strom_einfach'.
 *
 * Model version                  : 2.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Jul 12 17:04:00 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_FOC_Strom_einfach_h_
#define RTW_HEADER_FOC_Strom_einfach_h_
#include <math.h>
#include <string.h>
#ifndef FOC_Strom_einfach_COMMON_INCLUDES_
#define FOC_Strom_einfach_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Strom_einfach_COMMON_INCLUDES_ */

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

#define FOC_Strom_einfach_M            (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S41>/Integrator' */
  real_T Integrator_DSTATE_h;          /* '<S89>/Integrator' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Iv;                           /* '<Root>/Iv' */
  real_T Iu;                           /* '<Root>/Iu' */
  real_T theta_el;                     /* '<Root>/theta_el' */
  real_T Iw;                           /* '<Root>/Iw' */
  real_T Iq;                           /* '<Root>/Iq' */
  real_T Id;                           /* '<Root>/Id' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T U;                            /* '<Root>/U' */
  real_T V;                            /* '<Root>/V' */
  real_T W;                            /* '<Root>/W' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T P_R_id;                  /* Variable: P_R_id
                                        * Referenced by: '<S39>/Proportional Gain'
                                        */
extern real_T P_R_iq;                  /* Variable: P_R_iq
                                        * Referenced by: '<S87>/Proportional Gain'
                                        */
extern real_T T_R_id;                  /* Variable: T_R_id
                                        * Referenced by: '<S38>/Integral Gain'
                                        */
extern real_T T_R_iq;                  /* Variable: T_R_iq
                                        * Referenced by: '<S86>/Integral Gain'
                                        */
extern real_T U_ZK;                    /* Variable: U_ZK
                                        * Referenced by: '<S9>/Constant'
                                        */

/* Model entry point functions */
extern void FOC_Strom_einfach_initialize(RT_MODEL *const rtM);
extern void FOC_Strom_einfach_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_codegen_FOC_Current_einfach/FOC_Strom_einfach')    - opens subsystem uz_codegen_FOC_Current_einfach/FOC_Strom_einfach
 * hilite_system('uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen_FOC_Current_einfach'
 * '<S1>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach'
 * '<S2>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Strang-Rotor'
 * '<S3>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem'
 * '<S4>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Strang-Rotor/Clarke-Transformation'
 * '<S5>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Strang-Rotor/Park-Transformation'
 * '<S6>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d'
 * '<S7>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q'
 * '<S8>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/Rotor-Strang'
 * '<S9>'   : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/Tastgradbestimmung'
 * '<S10>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Anti-windup'
 * '<S11>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/D Gain'
 * '<S12>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Filter'
 * '<S13>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Filter ICs'
 * '<S14>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/I Gain'
 * '<S15>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Ideal P Gain'
 * '<S16>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Ideal P Gain Fdbk'
 * '<S17>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Integrator'
 * '<S18>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Integrator ICs'
 * '<S19>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/N Copy'
 * '<S20>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/N Gain'
 * '<S21>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/P Copy'
 * '<S22>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Parallel P Gain'
 * '<S23>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Reset Signal'
 * '<S24>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Saturation'
 * '<S25>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Saturation Fdbk'
 * '<S26>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Sum'
 * '<S27>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Sum Fdbk'
 * '<S28>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tracking Mode'
 * '<S29>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tracking Mode Sum'
 * '<S30>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tsamp - Integral'
 * '<S31>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tsamp - Ngain'
 * '<S32>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/postSat Signal'
 * '<S33>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/preSat Signal'
 * '<S34>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Anti-windup/Passthrough'
 * '<S35>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/D Gain/Disabled'
 * '<S36>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Filter/Disabled'
 * '<S37>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Filter ICs/Disabled'
 * '<S38>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/I Gain/Internal Parameters'
 * '<S39>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Ideal P Gain/Internal Parameters'
 * '<S40>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Ideal P Gain Fdbk/Disabled'
 * '<S41>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Integrator/Discrete'
 * '<S42>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Integrator ICs/Internal IC'
 * '<S43>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/N Copy/Disabled wSignal Specification'
 * '<S44>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/N Gain/Disabled'
 * '<S45>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/P Copy/Disabled'
 * '<S46>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Parallel P Gain/Passthrough'
 * '<S47>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Reset Signal/Disabled'
 * '<S48>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Saturation/Passthrough'
 * '<S49>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Saturation Fdbk/Disabled'
 * '<S50>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Sum/Sum_PI'
 * '<S51>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Sum Fdbk/Disabled'
 * '<S52>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tracking Mode/Disabled'
 * '<S53>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tracking Mode Sum/Passthrough'
 * '<S54>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tsamp - Integral/Passthrough'
 * '<S55>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/Tsamp - Ngain/Passthrough'
 * '<S56>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/postSat Signal/Forward_Path'
 * '<S57>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_d/preSat Signal/Forward_Path'
 * '<S58>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Anti-windup'
 * '<S59>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/D Gain'
 * '<S60>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Filter'
 * '<S61>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Filter ICs'
 * '<S62>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/I Gain'
 * '<S63>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Ideal P Gain'
 * '<S64>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Ideal P Gain Fdbk'
 * '<S65>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Integrator'
 * '<S66>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Integrator ICs'
 * '<S67>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/N Copy'
 * '<S68>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/N Gain'
 * '<S69>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/P Copy'
 * '<S70>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Parallel P Gain'
 * '<S71>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Reset Signal'
 * '<S72>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Saturation'
 * '<S73>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Saturation Fdbk'
 * '<S74>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Sum'
 * '<S75>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Sum Fdbk'
 * '<S76>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tracking Mode'
 * '<S77>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tracking Mode Sum'
 * '<S78>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tsamp - Integral'
 * '<S79>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tsamp - Ngain'
 * '<S80>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/postSat Signal'
 * '<S81>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/preSat Signal'
 * '<S82>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Anti-windup/Passthrough'
 * '<S83>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/D Gain/Disabled'
 * '<S84>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Filter/Disabled'
 * '<S85>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Filter ICs/Disabled'
 * '<S86>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/I Gain/Internal Parameters'
 * '<S87>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Ideal P Gain/Internal Parameters'
 * '<S88>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Ideal P Gain Fdbk/Disabled'
 * '<S89>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Integrator/Discrete'
 * '<S90>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Integrator ICs/Internal IC'
 * '<S91>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/N Copy/Disabled wSignal Specification'
 * '<S92>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/N Gain/Disabled'
 * '<S93>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/P Copy/Disabled'
 * '<S94>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Parallel P Gain/Passthrough'
 * '<S95>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Reset Signal/Disabled'
 * '<S96>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Saturation/Passthrough'
 * '<S97>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Saturation Fdbk/Disabled'
 * '<S98>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Sum/Sum_PI'
 * '<S99>'  : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Sum Fdbk/Disabled'
 * '<S100>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tracking Mode/Disabled'
 * '<S101>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tracking Mode Sum/Passthrough'
 * '<S102>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tsamp - Integral/Passthrough'
 * '<S103>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/Tsamp - Ngain/Passthrough'
 * '<S104>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/postSat Signal/Forward_Path'
 * '<S105>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/PI_q/preSat Signal/Forward_Path'
 * '<S106>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/Rotor-Strang/Inverse-Clark-Transformation'
 * '<S107>' : 'uz_codegen_FOC_Current_einfach/FOC_Strom_einfach/Subsystem/Rotor-Strang/Inverse-Park-Transormation'
 */

/*-
 * Requirements for '<Root>': FOC_Strom_einfach
 */
#endif                                 /* RTW_HEADER_FOC_Strom_einfach_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
