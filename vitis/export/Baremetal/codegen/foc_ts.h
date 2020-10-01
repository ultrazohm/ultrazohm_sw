/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: foc_ts.h
 *
 * Code generated for Simulink model 'foc_ts'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Oct  1 16:09:58 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Passed (11), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_foc_ts_h_
#define RTW_HEADER_foc_ts_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef foc_ts_COMMON_INCLUDES_
#define foc_ts_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* foc_ts_COMMON_INCLUDES_ */

#include "foc_ts_types.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S95>/Integrator' */
  real_T Integrator_DSTATE_j;          /* '<S43>/Integrator' */
  real_T Integrator_DSTATE_a;          /* '<S145>/Integrator' */
} DW_foc_ts_T;

/* Real-time Model Data Structure */
struct tag_RTM_foc_ts_T {
  DW_foc_ts_T *dwork;
};

/* Model entry point functions */
extern void foc_ts_initialize(RT_MODEL_foc_ts_T *const foc_ts_M, real_T
  *foc_ts_U_d_u_dc, real_T *foc_ts_U_d_nSoll, real_T *foc_ts_U_d_omega_mech,
  real_T *foc_ts_U_d_theta_mech, real_T *foc_ts_U_d_i_a, real_T *foc_ts_U_d_i_b,
  real_T *foc_ts_U_d_i_c, real_T *foc_ts_U_d_K_p_d, real_T *foc_ts_U_d_K_i_d,
  real_T *foc_ts_U_d_K_p_q, real_T *foc_ts_U_d_K_i_q, real_T *foc_ts_U_d_K_p_n,
  real_T *foc_ts_U_d_K_i_n, real_T *foc_ts_U_i_d_soll, real_T *foc_ts_U_i_q_soll,
  real_T *foc_ts_Y_d_u_1_nom, real_T *foc_ts_Y_d_u_2_nom, real_T
  *foc_ts_Y_d_u_3_nom, real_T *foc_ts_Y_d_u_d, real_T *foc_ts_Y_d_u_q, real_T
  *foc_ts_Y_iqSollFB, real_T *foc_ts_Y_id_ist, real_T *foc_ts_Y_iq_ist, real_T
  *foc_ts_Y_theta_mech_out);
extern void foc_ts_step(RT_MODEL_foc_ts_T *const foc_ts_M, real_T
  foc_ts_U_d_u_dc, real_T foc_ts_U_d_nSoll, real_T foc_ts_U_d_omega_mech, real_T
  foc_ts_U_d_theta_mech, real_T foc_ts_U_d_i_a, real_T foc_ts_U_d_i_b, real_T
  foc_ts_U_d_i_c, real_T foc_ts_U_d_K_p_d, real_T foc_ts_U_d_K_i_d, real_T
  foc_ts_U_d_K_p_q, real_T foc_ts_U_d_K_i_q, real_T foc_ts_U_d_K_p_n, real_T
  foc_ts_U_d_K_i_n, real_T foc_ts_U_i_d_soll, real_T *foc_ts_Y_d_u_1_nom, real_T
  *foc_ts_Y_d_u_2_nom, real_T *foc_ts_Y_d_u_3_nom, real_T *foc_ts_Y_d_u_d,
  real_T *foc_ts_Y_d_u_q, real_T *foc_ts_Y_iqSollFB, real_T *foc_ts_Y_id_ist,
  real_T *foc_ts_Y_iq_ist, real_T *foc_ts_Y_theta_mech_out);
extern void foc_ts_terminate(RT_MODEL_foc_ts_T *const foc_ts_M);

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
 * hilite_system('CodeGen_FOC/foc_ts')    - opens subsystem CodeGen_FOC/foc_ts
 * hilite_system('CodeGen_FOC/foc_ts/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'CodeGen_FOC'
 * '<S1>'   : 'CodeGen_FOC/foc_ts'
 * '<S2>'   : 'CodeGen_FOC/foc_ts/AlphaBeta_to_abc1'
 * '<S3>'   : 'CodeGen_FOC/foc_ts/FOC_ts'
 * '<S4>'   : 'CodeGen_FOC/foc_ts/abc_to_dq'
 * '<S5>'   : 'CodeGen_FOC/foc_ts/dq_to_AlphaBeta1'
 * '<S6>'   : 'CodeGen_FOC/foc_ts/normalize_U_for_ePWM'
 * '<S7>'   : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler'
 * '<S8>'   : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler'
 * '<S9>'   : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller'
 * '<S10>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Anti-windup'
 * '<S11>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/D Gain'
 * '<S12>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Filter'
 * '<S13>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Filter ICs'
 * '<S14>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/I Gain'
 * '<S15>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Ideal P Gain'
 * '<S16>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Ideal P Gain Fdbk'
 * '<S17>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Integrator'
 * '<S18>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Integrator ICs'
 * '<S19>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/N Copy'
 * '<S20>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/N Gain'
 * '<S21>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/P Copy'
 * '<S22>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Parallel P Gain'
 * '<S23>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Reset Signal'
 * '<S24>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Saturation'
 * '<S25>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Saturation Fdbk'
 * '<S26>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Sum'
 * '<S27>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Sum Fdbk'
 * '<S28>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tracking Mode'
 * '<S29>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tracking Mode Sum'
 * '<S30>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tsamp - Integral'
 * '<S31>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tsamp - Ngain'
 * '<S32>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/postSat Signal'
 * '<S33>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/preSat Signal'
 * '<S34>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Anti-windup/Disc. Clamping Ideal'
 * '<S35>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
 * '<S36>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
 * '<S37>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/D Gain/Disabled'
 * '<S38>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Filter/Disabled'
 * '<S39>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Filter ICs/Disabled'
 * '<S40>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/I Gain/External Parameters'
 * '<S41>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Ideal P Gain/External Parameters'
 * '<S42>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S43>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Integrator/Discrete'
 * '<S44>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Integrator ICs/Internal IC'
 * '<S45>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S46>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/N Gain/Disabled'
 * '<S47>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/P Copy/External Parameters Ideal'
 * '<S48>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Parallel P Gain/Passthrough'
 * '<S49>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Reset Signal/Disabled'
 * '<S50>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Saturation/Enabled'
 * '<S51>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Saturation Fdbk/Disabled'
 * '<S52>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Sum/Sum_PI'
 * '<S53>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Sum Fdbk/Disabled'
 * '<S54>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tracking Mode/Disabled'
 * '<S55>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S56>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tsamp - Integral/Passthrough'
 * '<S57>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S58>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/postSat Signal/Forward_Path'
 * '<S59>'  : 'CodeGen_FOC/foc_ts/FOC_ts/DrehzahlRegler/PID Controller/preSat Signal/Forward_Path'
 * '<S60>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller'
 * '<S61>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1'
 * '<S62>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Anti-windup'
 * '<S63>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/D Gain'
 * '<S64>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Filter'
 * '<S65>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Filter ICs'
 * '<S66>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/I Gain'
 * '<S67>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Ideal P Gain'
 * '<S68>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Ideal P Gain Fdbk'
 * '<S69>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Integrator'
 * '<S70>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Integrator ICs'
 * '<S71>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/N Copy'
 * '<S72>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/N Gain'
 * '<S73>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/P Copy'
 * '<S74>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Parallel P Gain'
 * '<S75>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Reset Signal'
 * '<S76>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Saturation'
 * '<S77>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Saturation Fdbk'
 * '<S78>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Sum'
 * '<S79>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Sum Fdbk'
 * '<S80>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tracking Mode'
 * '<S81>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tracking Mode Sum'
 * '<S82>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tsamp - Integral'
 * '<S83>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tsamp - Ngain'
 * '<S84>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/postSat Signal'
 * '<S85>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/preSat Signal'
 * '<S86>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S87>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S88>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S89>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/D Gain/Disabled'
 * '<S90>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Filter/Disabled'
 * '<S91>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Filter ICs/Disabled'
 * '<S92>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/I Gain/External Parameters'
 * '<S93>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Ideal P Gain/Passthrough'
 * '<S94>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S95>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Integrator/Discrete'
 * '<S96>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Integrator ICs/Internal IC'
 * '<S97>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S98>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/N Gain/Disabled'
 * '<S99>'  : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/P Copy/Disabled'
 * '<S100>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Parallel P Gain/External Parameters'
 * '<S101>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Reset Signal/Disabled'
 * '<S102>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Saturation/Enabled'
 * '<S103>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Saturation Fdbk/Disabled'
 * '<S104>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Sum/Sum_PI'
 * '<S105>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Sum Fdbk/Disabled'
 * '<S106>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tracking Mode/Disabled'
 * '<S107>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S108>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tsamp - Integral/Passthrough'
 * '<S109>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S110>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/postSat Signal/Forward_Path'
 * '<S111>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller/preSat Signal/Forward_Path'
 * '<S112>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Anti-windup'
 * '<S113>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/D Gain'
 * '<S114>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Filter'
 * '<S115>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Filter ICs'
 * '<S116>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/I Gain'
 * '<S117>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Ideal P Gain'
 * '<S118>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Ideal P Gain Fdbk'
 * '<S119>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Integrator'
 * '<S120>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Integrator ICs'
 * '<S121>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/N Copy'
 * '<S122>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/N Gain'
 * '<S123>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/P Copy'
 * '<S124>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Parallel P Gain'
 * '<S125>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Reset Signal'
 * '<S126>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Saturation'
 * '<S127>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Saturation Fdbk'
 * '<S128>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Sum'
 * '<S129>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Sum Fdbk'
 * '<S130>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tracking Mode'
 * '<S131>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tracking Mode Sum'
 * '<S132>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tsamp - Integral'
 * '<S133>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tsamp - Ngain'
 * '<S134>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/postSat Signal'
 * '<S135>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/preSat Signal'
 * '<S136>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S137>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S138>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S139>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/D Gain/Disabled'
 * '<S140>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Filter/Disabled'
 * '<S141>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Filter ICs/Disabled'
 * '<S142>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/I Gain/External Parameters'
 * '<S143>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Ideal P Gain/Passthrough'
 * '<S144>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S145>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Integrator/Discrete'
 * '<S146>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Integrator ICs/Internal IC'
 * '<S147>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S148>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/N Gain/Disabled'
 * '<S149>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/P Copy/Disabled'
 * '<S150>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Parallel P Gain/External Parameters'
 * '<S151>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Reset Signal/Disabled'
 * '<S152>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Saturation/Enabled'
 * '<S153>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Saturation Fdbk/Disabled'
 * '<S154>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Sum/Sum_PI'
 * '<S155>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Sum Fdbk/Disabled'
 * '<S156>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tracking Mode/Disabled'
 * '<S157>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S158>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S159>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S160>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/postSat Signal/Forward_Path'
 * '<S161>' : 'CodeGen_FOC/foc_ts/FOC_ts/Stromregler/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_foc_ts_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
