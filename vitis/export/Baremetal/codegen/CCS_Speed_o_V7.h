/*
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * File: CCS_Speed_o_V7.h
 *
 * Code generated for Simulink model 'CCS_Speed_o_V7'.
 *
 * Model version                  : 1.1177
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri May 25 11:16:52 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Emulation hardware selection:
 *    Differs from embedded hardware (Custom Processor->MATLAB Host Computer)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CCS_Speed_o_V7_h_
#define RTW_HEADER_CCS_Speed_o_V7_h_
#include <string.h>
#ifndef CCS_Speed_o_V7_COMMON_INCLUDES_
# define CCS_Speed_o_V7_COMMON_INCLUDES_
#include "rtwtypes_CCS_Speed_o_V7.h"
#endif                                 /* CCS_Speed_o_V7_COMMON_INCLUDES_ */

#include "CCS_Speed_o_V7_types.h"
//#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T d_up;                         /* '<S1>/CCS-MPC Drehzahlregler' */
  real_T d_x_old[3];                   /* '<S1>/CCS-MPC Drehzahlregler' */
} DW_CCS_Speed_o_V7_T;

/* Parameters (default storage) */
struct P_CCS_Speed_o_V7_T_ {
  real_T d_M_max;                      /* Variable: d_M_max
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T d_invOmegaPhi_F[30];          /* Variable: d_invOmegaPhi_F
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T d_invOmegaPhi_R[12];          /* Variable: d_invOmegaPhi_R
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T d_phi_F[30];                  /* Variable: d_phi_F
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T d_phi_R[12];                  /* Variable: d_phi_R
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T d_phi_phi[36];                /* Variable: d_phi_phi
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T d_psi_pm;                     /* Variable: d_psi_pm
                                        * Referenced by:
                                        *   '<S1>/CCS-MPC Drehzahlregler'
                                        *   '<S1>/Gain11'
                                        */
  real_T d_rw;                         /* Variable: d_rw
                                        * Referenced by: '<S1>/CCS-MPC Drehzahlregler'
                                        */
  real_T ui8_p;                        /* Variable: ui8_p
                                        * Referenced by:
                                        *   '<S1>/CCS-MPC Drehzahlregler'
                                        *   '<S1>/Gain11'
                                        */
  real_T Gain8_Gain;                   /* Expression: (2*pi())/60
                                        * Referenced by: '<S1>/Gain8'
                                        */
  real_T Gain9_Gain;                   /* Expression: (2*pi())/60
                                        * Referenced by: '<S1>/Gain9'
                                        */
  real_T Gain13_Gain;                  /* Expression: (2*pi())/60
                                        * Referenced by: '<S1>/Gain13'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_CCS_Speed_o_V7_T {
  const char_T * volatile errorStatus;
  P_CCS_Speed_o_V7_T *defaultParam;
  DW_CCS_Speed_o_V7_T *dwork;
};

/* Model entry point functions */
extern void CCS_Speed_o_V7_initialize(RT_MODEL_CCS_Speed_o_V7_T *const
  CCS_Speed_o_V7_M, real_T *CCS_Speed_o_V7_U_d_n_ref, real_T
  *CCS_Speed_o_V7_U_d_i_q_meas, real_T *CCS_Speed_o_V7_U_d_n_meas, real_T
  *CCS_Speed_o_V7_U_d_M_L_meas, real_T *CCS_Speed_o_V7_U_d_delta_theta, real_T
  *CCS_Speed_o_V7_U_d_n_L_meas, real_T *CCS_Speed_o_V7_Y_d_i_q_ref);
extern void CCS_Speed_o_V7_step(RT_MODEL_CCS_Speed_o_V7_T *const
  CCS_Speed_o_V7_M, real_T CCS_Speed_o_V7_U_d_n_ref, real_T
  CCS_Speed_o_V7_U_d_n_meas, real_T CCS_Speed_o_V7_U_d_delta_theta, real_T
  CCS_Speed_o_V7_U_d_n_L_meas, real_T *CCS_Speed_o_V7_Y_d_i_q_ref);
extern void CCS_Speed_o_V7_terminate(RT_MODEL_CCS_Speed_o_V7_T *const
  CCS_Speed_o_V7_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S3>/Add1' : Unused code path elimination
 * Block '<S3>/Add2' : Unused code path elimination
 * Block '<S3>/Discrete-Time Integrator1' : Unused code path elimination
 * Block '<S3>/Discrete-Time Integrator2' : Unused code path elimination
 * Block '<S3>/Gain1 0.9' : Unused code path elimination
 * Block '<S3>/Gain2 1.1' : Unused code path elimination
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
 * hilite_system('PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen/CCS_Speed_o_V7')    - opens subsystem PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen/CCS_Speed_o_V7
 * hilite_system('PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen/CCS_Speed_o_V7/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen'
 * '<S1>'   : 'PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen/CCS_Speed_o_V7'
 * '<S2>'   : 'PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen/CCS_Speed_o_V7/CCS-MPC Drehzahlregler'
 * '<S3>'   : 'PMSM_CCS_FCS_Regelung_Diskret/CCF_MPC_CodeGen/CCS_Speed_o_V7/SprungfilterPT2'
 */
#endif                                 /* RTW_HEADER_CCS_Speed_o_V7_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
