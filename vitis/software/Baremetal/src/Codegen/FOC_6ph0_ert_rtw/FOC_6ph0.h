/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_6ph0.h
 *
 * Code generated for Simulink model 'FOC_6ph0'.
 *
 * Model version                  : 7.43
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Nov 26 11:12:50 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_6ph0_h_
#define RTW_HEADER_FOC_6ph0_h_
#include <math.h>
#include <string.h>
#ifndef FOC_6ph0_COMMON_INCLUDES_
#define FOC_6ph0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_6ph0_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOC_6ph0_T RT_MODEL_FOC_6ph0_T;

/* Block signals (default storage) */
typedef struct {
  real32_T Fcn;                        /* '<S168>/Fcn' */
  real32_T Fcn1;                       /* '<S168>/Fcn1' */
  real32_T Fcn_o;                      /* '<S167>/Fcn' */
  real32_T Fcn1_h;                     /* '<S167>/Fcn1' */
  real32_T Fcn_l;                      /* '<S14>/Fcn' */
  real32_T Fcn1_a;                     /* '<S14>/Fcn1' */
  real32_T Fcn_lr;                     /* '<S13>/Fcn' */
  real32_T Fcn1_k;                     /* '<S13>/Fcn1' */
} B_FOC_6ph0_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S98>/Integrator' */
  real_T Integrator_DSTATE_m;          /* '<S48>/Integrator' */
  real_T Integrator_DSTATE_e;          /* '<S148>/Integrator' */
  real_T Integrator_PREV_U;            /* '<S98>/Integrator' */
  real_T Integrator_PREV_U_j;          /* '<S48>/Integrator' */
  real_T Integrator_PREV_U_a;          /* '<S148>/Integrator' */
  uint32_T superStateFOC_PREV_T;       /* '<S1>/superState.FOC' */
  int8_T Integrator_PrevResetState;    /* '<S98>/Integrator' */
  int8_T Integrator_PrevResetState_c;  /* '<S148>/Integrator' */
  uint8_T is_active_c33_FOC_6ph0;      /* '<Root>/FOC_6ph' */
  uint8_T is_superState;               /* '<Root>/FOC_6ph' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S98>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE_e;  /* '<S48>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE_m;  /* '<S148>/Integrator' */
  boolean_T superStateFOC_RESET_ELAPS_T;/* '<S1>/superState.FOC' */
} DW_FOC_6ph0_T;

/* Invariant block signals (default storage) */
typedef struct {
  const uint8_T Compare;               /* '<S11>/Compare' */
  const uint8_T Compare_m;             /* '<S12>/Compare' */
  const uint8_T Compare_d;             /* '<S165>/Compare' */
  const uint8_T Compare_f;             /* '<S166>/Compare' */
} ConstB_FOC_6ph0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T RESET;                     /* '<Root>/RESET' */
  boolean_T NEXT;                      /* '<Root>/NEXT' */
  real32_T u_dc_k;                     /* '<Root>/u_dc' */
  uint16_T PERIOD_m;                   /* '<Root>/PERIOD' */
  real32_T id_ref;                     /* '<Root>/id_ref' */
  real32_T iq_ref;                     /* '<Root>/iq_ref' */
  real32_T i_a1;                       /* '<Root>/i_a1' */
  real32_T i_b1;                       /* '<Root>/i_b1' */
  real32_T i_c1;                       /* '<Root>/i_c1' */
  real32_T i_a2;                       /* '<Root>/i_a2' */
  real32_T i_b2;                       /* '<Root>/i_b2' */
  real32_T i_c2;                       /* '<Root>/i_c2' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  real32_T u1;                         /* '<Root>/u1' */
  real32_T u2;                         /* '<Root>/u2' */
  real32_T u3;                         /* '<Root>/u3' */
  real32_T Rs;                         /* '<Root>/Rs' */
  real32_T Ls;                         /* '<Root>/Ls' */
  real32_T psiPM;                      /* '<Root>/psiPM' */
  boolean_T currentORspeedControl;     /* '<Root>/currentORspeedControl' */
  real32_T n_ref_RPM;                  /* '<Root>/n_ref_RPM' */
  real32_T n_RPM;                      /* '<Root>/n_RPM' */
  real32_T Kr;                         /* '<Root>/Kr' */
} ExtU_FOC_6ph0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T activeState;                 /* '<Root>/activeState' */
  real_T CMPA_1;                       /* '<Root>/CMPA_1' */
  real_T CMPA_2;                       /* '<Root>/CMPA_2' */
  real_T CMPA_3;                       /* '<Root>/CMPA_3' */
  int32_T sector;                      /* '<Root>/sector' */
  real_T CMPA_5;                       /* '<Root>/CMPA_5' */
  real_T CMPA_6;                       /* '<Root>/CMPA_6' */
  real_T CMPA_4;                       /* '<Root>/CMPA_4' */
  real32_T id;                         /* '<Root>/id' */
  real32_T iq;                         /* '<Root>/iq' */
  real32_T ix;                         /* '<Root>/ix' */
  real32_T iy;                         /* '<Root>/iy' */
  real32_T ud_ctrl;                    /* '<Root>/ud_ctrl' */
  real32_T uq_ctrl;                    /* '<Root>/uq_ctrl' */
} ExtY_FOC_6ph0_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_6ph0_T {
  B_FOC_6ph0_T *blockIO;
  ExtU_FOC_6ph0_T *inputs;
  ExtY_FOC_6ph0_T *outputs;
  DW_FOC_6ph0_T *dwork;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

extern const ConstB_FOC_6ph0_T FOC_6ph0_ConstB;/* constant block i/o */

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
                                        *   '<S96>/Proportional Gain'
                                        *   '<S102>/P Copy'
                                        */
extern real_T Kpn;                     /* Variable: Kpn
                                        * Referenced by:
                                        *   '<S46>/Proportional Gain'
                                        *   '<S52>/P Copy'
                                        */
extern real_T Kpq;                     /* Variable: Kpq
                                        * Referenced by:
                                        *   '<S146>/Proportional Gain'
                                        *   '<S152>/P Copy'
                                        */
extern real_T PERIOD;                  /* Variable: PERIOD
                                        * Referenced by:
                                        *   '<S2>/Gain2'
                                        *   '<S2>/Gain3'
                                        *   '<S2>/Gain4'
                                        *   '<S2>/Gain5'
                                        *   '<S2>/Gain6'
                                        *   '<S2>/Gain7'
                                        */
extern real_T Tnd;                     /* Variable: Tnd
                                        * Referenced by: '<S95>/Integral Gain'
                                        */
extern real_T Tnn;                     /* Variable: Tnn
                                        * Referenced by: '<S45>/Integral Gain'
                                        */
extern real_T Tnq;                     /* Variable: Tnq
                                        * Referenced by: '<S145>/Integral Gain'
                                        */
extern real_T u_dc;                    /* Variable: u_dc
                                        * Referenced by:
                                        *   '<S105>/Saturation'
                                        *   '<S155>/Saturation'
                                        *   '<S91>/DeadZone'
                                        *   '<S141>/DeadZone'
                                        */

/* Model entry point functions */
extern void FOC_6ph0_initialize(RT_MODEL_FOC_6ph0_T *const FOC_6ph0_M);
extern void FOC_6ph0_step(RT_MODEL_FOC_6ph0_T *const FOC_6ph0_M);
extern void FOC_6ph0_terminate(RT_MODEL_FOC_6ph0_T *const FOC_6ph0_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Constant8' : Unused code path elimination
 * Block '<S2>/Gain' : Unused code path elimination
 * Block '<S2>/RPM2omega_mech' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Data Type Conversion9' : Eliminate redundant data type conversion
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
 * hilite_system('FOC_6ph/FOC_6ph')    - opens subsystem FOC_6ph/FOC_6ph
 * hilite_system('FOC_6ph/FOC_6ph/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FOC_6ph'
 * '<S1>'   : 'FOC_6ph/FOC_6ph'
 * '<S2>'   : 'FOC_6ph/FOC_6ph/superState.FOC'
 * '<S3>'   : 'FOC_6ph/FOC_6ph/superState.FOC/6ph_PMSM_30deg_VSD1'
 * '<S4>'   : 'FOC_6ph/FOC_6ph/superState.FOC/Alpha-Beta-Zero to dq0'
 * '<S5>'   : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller'
 * '<S6>'   : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2'
 * '<S7>'   : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3'
 * '<S8>'   : 'FOC_6ph/FOC_6ph/superState.FOC/RZM_Traegerbasiert'
 * '<S9>'   : 'FOC_6ph/FOC_6ph/superState.FOC/RZM_Traegerbasiert1'
 * '<S10>'  : 'FOC_6ph/FOC_6ph/superState.FOC/dq0 to Alpha-Beta-Zero1'
 * '<S11>'  : 'FOC_6ph/FOC_6ph/superState.FOC/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S12>'  : 'FOC_6ph/FOC_6ph/superState.FOC/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S13>'  : 'FOC_6ph/FOC_6ph/superState.FOC/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S14>'  : 'FOC_6ph/FOC_6ph/superState.FOC/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S15>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Anti-windup'
 * '<S16>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/D Gain'
 * '<S17>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Filter'
 * '<S18>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Filter ICs'
 * '<S19>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/I Gain'
 * '<S20>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Ideal P Gain'
 * '<S21>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Ideal P Gain Fdbk'
 * '<S22>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Integrator'
 * '<S23>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Integrator ICs'
 * '<S24>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/N Copy'
 * '<S25>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/N Gain'
 * '<S26>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/P Copy'
 * '<S27>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Parallel P Gain'
 * '<S28>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Reset Signal'
 * '<S29>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Saturation'
 * '<S30>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Saturation Fdbk'
 * '<S31>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Sum'
 * '<S32>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Sum Fdbk'
 * '<S33>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tracking Mode'
 * '<S34>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tracking Mode Sum'
 * '<S35>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tsamp - Integral'
 * '<S36>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tsamp - Ngain'
 * '<S37>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/postSat Signal'
 * '<S38>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/preSat Signal'
 * '<S39>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Anti-windup/Disc. Clamping Ideal'
 * '<S40>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S41>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S42>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/D Gain/Disabled'
 * '<S43>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Filter/Disabled'
 * '<S44>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Filter ICs/Disabled'
 * '<S45>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/I Gain/Internal Parameters'
 * '<S46>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Ideal P Gain/Internal Parameters'
 * '<S47>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Ideal P Gain Fdbk/Disabled'
 * '<S48>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Integrator/Discrete'
 * '<S49>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Integrator ICs/Internal IC'
 * '<S50>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/N Copy/Disabled wSignal Specification'
 * '<S51>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/N Gain/Disabled'
 * '<S52>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/P Copy/Internal Parameters Ideal'
 * '<S53>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Parallel P Gain/Passthrough'
 * '<S54>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Reset Signal/Disabled'
 * '<S55>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Saturation/Enabled'
 * '<S56>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Saturation Fdbk/Disabled'
 * '<S57>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Sum/Sum_PI'
 * '<S58>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Sum Fdbk/Disabled'
 * '<S59>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tracking Mode/Disabled'
 * '<S60>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tracking Mode Sum/Passthrough'
 * '<S61>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tsamp - Integral/Passthrough'
 * '<S62>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/Tsamp - Ngain/Passthrough'
 * '<S63>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/postSat Signal/Forward_Path'
 * '<S64>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PI speed controller/preSat Signal/Forward_Path'
 * '<S65>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Anti-windup'
 * '<S66>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/D Gain'
 * '<S67>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Filter'
 * '<S68>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Filter ICs'
 * '<S69>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/I Gain'
 * '<S70>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Ideal P Gain'
 * '<S71>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Ideal P Gain Fdbk'
 * '<S72>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Integrator'
 * '<S73>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Integrator ICs'
 * '<S74>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/N Copy'
 * '<S75>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/N Gain'
 * '<S76>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/P Copy'
 * '<S77>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Parallel P Gain'
 * '<S78>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Reset Signal'
 * '<S79>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Saturation'
 * '<S80>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Saturation Fdbk'
 * '<S81>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Sum'
 * '<S82>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Sum Fdbk'
 * '<S83>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tracking Mode'
 * '<S84>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tracking Mode Sum'
 * '<S85>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tsamp - Integral'
 * '<S86>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tsamp - Ngain'
 * '<S87>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/postSat Signal'
 * '<S88>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/preSat Signal'
 * '<S89>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Anti-windup/Disc. Clamping Ideal'
 * '<S90>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S91>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S92>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/D Gain/Disabled'
 * '<S93>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Filter/Disabled'
 * '<S94>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Filter ICs/Disabled'
 * '<S95>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/I Gain/Internal Parameters'
 * '<S96>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Ideal P Gain/Internal Parameters'
 * '<S97>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S98>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Integrator/Discrete'
 * '<S99>'  : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Integrator ICs/Internal IC'
 * '<S100>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S101>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/N Gain/Disabled'
 * '<S102>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/P Copy/Internal Parameters Ideal'
 * '<S103>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Parallel P Gain/Passthrough'
 * '<S104>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Reset Signal/External Reset'
 * '<S105>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Saturation/Enabled'
 * '<S106>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Saturation Fdbk/Disabled'
 * '<S107>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Sum/Sum_PI'
 * '<S108>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Sum Fdbk/Disabled'
 * '<S109>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tracking Mode/Disabled'
 * '<S110>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S111>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tsamp - Integral/Passthrough'
 * '<S112>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S113>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/postSat Signal/Forward_Path'
 * '<S114>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller2/preSat Signal/Forward_Path'
 * '<S115>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Anti-windup'
 * '<S116>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/D Gain'
 * '<S117>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Filter'
 * '<S118>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Filter ICs'
 * '<S119>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/I Gain'
 * '<S120>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Ideal P Gain'
 * '<S121>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Ideal P Gain Fdbk'
 * '<S122>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Integrator'
 * '<S123>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Integrator ICs'
 * '<S124>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/N Copy'
 * '<S125>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/N Gain'
 * '<S126>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/P Copy'
 * '<S127>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Parallel P Gain'
 * '<S128>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Reset Signal'
 * '<S129>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Saturation'
 * '<S130>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Saturation Fdbk'
 * '<S131>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Sum'
 * '<S132>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Sum Fdbk'
 * '<S133>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tracking Mode'
 * '<S134>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tracking Mode Sum'
 * '<S135>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tsamp - Integral'
 * '<S136>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tsamp - Ngain'
 * '<S137>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/postSat Signal'
 * '<S138>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/preSat Signal'
 * '<S139>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Anti-windup/Disc. Clamping Ideal'
 * '<S140>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S141>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S142>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/D Gain/Disabled'
 * '<S143>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Filter/Disabled'
 * '<S144>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Filter ICs/Disabled'
 * '<S145>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/I Gain/Internal Parameters'
 * '<S146>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Ideal P Gain/Internal Parameters'
 * '<S147>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S148>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Integrator/Discrete'
 * '<S149>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Integrator ICs/Internal IC'
 * '<S150>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S151>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/N Gain/Disabled'
 * '<S152>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/P Copy/Internal Parameters Ideal'
 * '<S153>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Parallel P Gain/Passthrough'
 * '<S154>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Reset Signal/External Reset'
 * '<S155>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Saturation/Enabled'
 * '<S156>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Saturation Fdbk/Disabled'
 * '<S157>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Sum/Sum_PI'
 * '<S158>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Sum Fdbk/Disabled'
 * '<S159>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tracking Mode/Disabled'
 * '<S160>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S161>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tsamp - Integral/Passthrough'
 * '<S162>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S163>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/postSat Signal/Forward_Path'
 * '<S164>' : 'FOC_6ph/FOC_6ph/superState.FOC/PID Controller3/preSat Signal/Forward_Path'
 * '<S165>' : 'FOC_6ph/FOC_6ph/superState.FOC/dq0 to Alpha-Beta-Zero1/Compare To Constant'
 * '<S166>' : 'FOC_6ph/FOC_6ph/superState.FOC/dq0 to Alpha-Beta-Zero1/Compare To Constant1'
 * '<S167>' : 'FOC_6ph/FOC_6ph/superState.FOC/dq0 to Alpha-Beta-Zero1/Subsystem - pi//2 delay'
 * '<S168>' : 'FOC_6ph/FOC_6ph/superState.FOC/dq0 to Alpha-Beta-Zero1/Subsystem1'
 */

/*-
 * Requirements for '<Root>': FOC_6ph0
 */
#endif                                 /* RTW_HEADER_FOC_6ph0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
