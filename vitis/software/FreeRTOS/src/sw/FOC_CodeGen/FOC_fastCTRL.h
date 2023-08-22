/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_fastCTRL.h
 *
 * Code generated for Simulink model 'FOC_fastCTRL'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Aug 22 14:14:27 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_fastCTRL_h_
#define RTW_HEADER_FOC_fastCTRL_h_
#ifndef FOC_fastCTRL_COMMON_INCLUDES_
#define FOC_fastCTRL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_fastCTRL_COMMON_INCLUDES_ */

#include "FOC_fastCTRL_types.h"
#include <string.h>
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T DiscreteFIRFilter10thorder; /* '<S9>/Discrete FIR Filter 10th order' */
} B_FOC_fastCTRL_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTransferFcn_states;   /* '<S7>/Discrete Transfer Fcn' */
  real_T UnitDelay_DSTATE;             /* '<S48>/Unit Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S33>/Unit Delay1' */
  real_T UnitDelay_DSTATE_m[2];        /* '<S15>/Unit Delay' */
  real_T UnitDelay_DSTATE_n;           /* '<S12>/Unit Delay' */
  real_T DiscreteTransferFcn_states_o; /* '<S13>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states;  /* '<S13>/Discrete Transfer Fcn1' */
  real_T UnitDelay_DSTATE_g;           /* '<S32>/Unit Delay' */
  real_T UnitDelay3_DSTATE;            /* '<S26>/Unit Delay3' */
  real_T IntegDelay1_DSTATE[2];        /* '<S41>/IntegDelay1' */
  real_T IntegDelay1_DSTATE_g[2];      /* '<S45>/IntegDelay1' */
  real_T UnitDelay1_DSTATE_h[2];       /* '<S14>/Unit Delay1' */
  real_T UnitDelay_DSTATE_o[2];        /* '<S14>/Unit Delay' */
  real_T DiscreteFIRFilter20thorder_stat[38];
                                    /* '<S39>/Discrete FIR Filter 20th order' */
  real_T DiscreteFIRFilter20thorder_st_h[38];
                                    /* '<S38>/Discrete FIR Filter 20th order' */
  real_T UnitDelay_DSTATE_b[2];        /* '<S1>/Unit Delay' */
  real_T DiscreteFIRFilter10thorder_stat[9];
                                     /* '<S9>/Discrete FIR Filter 10th order' */
  real_T UnitDelay1_DSTATE_he;         /* '<S34>/Unit Delay1' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S39>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_a;
                                    /* '<S38>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter10thorder_circ;
                                     /* '<S9>/Discrete FIR Filter 10th order' */
  boolean_T AutoSwitchHysteresis_Mode; /* '<S5>/AutoSwitchHysteresis' */
} DW_FOC_fastCTRL_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [1,0;-0.5,sqrt(3)/2;-0.5,-sqrt(3)/2])
   * Referenced by:
   *   '<S54>/Constant'
   *   '<S55>/Constant'
   */
  real_T pooled8[6];

  /* Pooled Parameter (Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3)
   * Referenced by:
   *   '<S38>/TrafoMatrix uvw->alphabeta'
   *   '<S39>/TrafoMatrix uvw->alphabeta'
   */
  real_T pooled9[6];
} ConstP_FOC_fastCTRL_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T U_DCV;                        /* '<Root>/U_DC [V]' */
  real_T I_phA[6];                     /* '<Root>/I_ph [A]' */
  real_T I_dq_RefA[2];                 /* '<Root>/I_dq_Ref [A]' */
  real_T phi_elrad;                    /* '<Root>/phi_el [rad]' */
  real_T FOC_Mode;                     /* '<Root>/FOC_Mode' */
  real_T FOC_Enable_i;                 /* '<Root>/FOC_Enable' */
} ExtU_FOC_fastCTRL_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T DutyCycles01[6];              /* '<Root>/DutyCycles [0..1]' */
  real_T I_dq_ActA[4];                 /* '<Root>/I_dq_Act [A]' */
  real_T ModInd[2];                    /* '<Root>/ModInd' */
  real_T w_elrads;                     /* '<Root>/w_el [rad//s]' */
  real_T FOC_Error;                    /* '<Root>/FOC_Error' */
  real_T I_dq_Ref_outA[2];             /* '<Root>/I_dq_Ref_out [A]' */
} ExtY_FOC_fastCTRL_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_fastCTRL_T {
  const char_T * volatile errorStatus;
  B_FOC_fastCTRL_T *blockIO;
  ExtU_FOC_fastCTRL_T *inputs;
  ExtY_FOC_fastCTRL_T *outputs;
  DW_FOC_fastCTRL_T *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP_FOC_fastCTRL_T FOC_fastCTRL_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T Phi_AngleEst_AutoSwitch; /* '<S5>/Selectphicalc3' */
extern real_T FOC_AngleEst_w_el;       /* '<S13>/Switch_speed' */
extern real_T Phi_est;                 /* '<S10>/Sum1' */
extern real_T Phi_Observer;            /* '<S26>/Sum7' */
extern real_T Phi_el_I_Transformation; /* '<S28>/Switch2' */
extern real_T Phi_el_U_Transformation; /* '<S29>/Switch2' */
extern real_T FOC_U_DC;                /* '<S1>/Switch1' */
extern real_T Phi_est_error_I_Trafo;   /* '<S5>/phi_est_error2' */
extern real_T Phi_est_error;           /* '<S5>/phi_est_error' */
extern real_T FOC_AngleEst_Psi_PM_alpha;/* '<S3>/Gain3' */
extern real_T FOC_AngleEst_Psi_PM_beta;/* '<S3>/Gain4' */
extern real_T w_el;                    /* '<S5>/dummy_gain' */
extern real_T Phi_Measured_Raw;        /* '<S5>/dummy_gain3' */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T FOC_6ph_AngleShift;      /* Variable: FOC_6ph_AngleShift
                                        * Referenced by:
                                        *   '<S5>/FOC_6ph_AngleShift'
                                        *   '<S6>/FOC_6ph_AngleShift'
                                        *   '<S7>/FOC_6ph_AngleShift'
                                        */
extern real_T FOC_AKS_Mode;            /* Variable: FOC_AKS_Mode
                                        * Referenced by: '<S2>/FOC_AKS_Mode'
                                        */
extern real_T FOC_AngleEst_AutoSwitch_wel_off;
                                    /* Variable: FOC_AngleEst_AutoSwitch_wel_off
                                     * Referenced by: '<S5>/AutoSwitchHysteresis'
                                     */
extern real_T FOC_AngleEst_AutoSwitch_wel_on;
                                     /* Variable: FOC_AngleEst_AutoSwitch_wel_on
                                      * Referenced by: '<S5>/AutoSwitchHysteresis'
                                      */
extern real_T FOC_AngleEst_Delay1;     /* Variable: FOC_AngleEst_Delay1
                                        * Referenced by: '<S14>/FOC_AngleEst_Delay1'
                                        */
extern real_T FOC_AngleEst_Delay2;     /* Variable: FOC_AngleEst_Delay2
                                        * Referenced by: '<S14>/FOC_AngleEst_Delay2'
                                        */
extern real_T FOC_AngleEst_Komp_KP;    /* Variable: FOC_AngleEst_Komp_KP
                                        * Referenced by: '<S3>/komp_kp'
                                        */
extern real_T FOC_AngleEst_Lq;         /* Variable: FOC_AngleEst_Lq
                                        * Referenced by: '<S3>/FOC_AngleEst_Lq'
                                        */
extern real_T FOC_AngleEst_Psi_InitVal;/* Variable: FOC_AngleEst_Psi_InitVal
                                        * Referenced by: '<S15>/Unit Delay'
                                        */
extern real_T FOC_AngleEst_Rs;         /* Variable: FOC_AngleEst_Rs
                                        * Referenced by: '<S3>/FOC_AngleEst_Rs'
                                        */
extern real_T FOC_AngleEst_w_el_filtered_Tau;
                                     /* Variable: FOC_AngleEst_w_el_filtered_Tau
                                      * Referenced by: '<S12>/Tau'
                                      */
extern real_T FOC_AngleObs_w_InitVal;  /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S33>/Unit Delay1'
                                        */
extern real_T FOC_AngleObserver_D;     /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S26>/Constant1'
                                        */
extern real_T FOC_AngleObserver_w0;    /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S26>/Constant'
                                        */
extern real_T FOC_Enable;              /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
extern real_T FOC_IntegDamp;           /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S41>/FOC_IntegDamp'
                                        *   '<S45>/FOC_IntegDamp'
                                        */
extern real_T FOC_KI;                  /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S41>/FOC_KI'
                                        *   '<S45>/FOC_KI'
                                        */
extern real_T FOC_KP;                  /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S41>/FOC_KP1'
                                        *   '<S45>/FOC_KP1'
                                        */
extern real_T FOC_MANUAL_U_DC;         /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc1'
                                        */
extern real_T FOC_MaxModInd;           /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S40>/FOC_MaxModInd'
                                        *   '<S44>/FOC_MaxModInd'
                                        */
extern real_T FOC_OmegaObs3;           /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S26>/Gain4'
                                        */
extern real_T FOC_PhiSensorTdead;      /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S26>/Constant2'
                                        */
extern real_T FOC_PhiSensorTdead_AngleEst;/* Variable: FOC_PhiSensorTdead_AngleEst
                                           * Referenced by: '<S26>/Constant3'
                                           */
extern real_T FOC_SELECT_AngleAdaption2PolePairs;
                                 /* Variable: FOC_SELECT_AngleAdaption2PolePairs
                                  * Referenced by: '<S5>/Constant2'
                                  */
extern real_T FOC_SELECT_AngleAdaptionRange;
                                      /* Variable: FOC_SELECT_AngleAdaptionRange
                                       * Referenced by: '<S5>/Constant4'
                                       */
extern real_T FOC_SELECT_AngleEst;     /* Variable: FOC_SELECT_AngleEst
                                        * Referenced by: '<S5>/Constant1'
                                        */
extern real_T FOC_SELECT_AngleEst_AutoSwitch;
                                     /* Variable: FOC_SELECT_AngleEst_AutoSwitch
                                      * Referenced by: '<S5>/Constant5'
                                      */
extern real_T FOC_SELECT_AngleEst_w_el_filtered;
                                  /* Variable: FOC_SELECT_AngleEst_w_el_filtered
                                   * Referenced by: '<S3>/useFilteredCorrection'
                                   */
extern real_T FOC_SELECT_InvertAngle;  /* Variable: FOC_SELECT_InvertAngle
                                        * Referenced by: '<S5>/FOC_Invert_Encoder'
                                        */
extern real_T FOC_SELECT_Modulation;   /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S8>/Enable_SuperSinMod'
                                        */
extern real_T FOC_SELECT_U_DC_INPUT;   /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
extern real_T FOC_SELECT_phi;          /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S5>/Constant3'
                                        */
extern real_T FOC_Uf_U_max;            /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S49>/Saturation1'
                                        */
extern real_T FOC_Uf_U_min;            /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S49>/Saturation1'
                                        */
extern real_T FOC_Uf_Ud;               /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S7>/Uf_Ud'
                                        */
extern real_T FOC_Uf_f_el;             /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S7>/Uf_w_el'
                                        */
extern real_T FOC_Uf_m;                /* Variable: FOC_Uf_m
                                        * Referenced by: '<S49>/Gain'
                                        */
extern real_T FOC_f_fastCTRL;          /* Variable: FOC_f_fastCTRL
                                        * Referenced by:
                                        *   '<S5>/FOC_T_fast'
                                        *   '<S12>/FOC_f_fast'
                                        *   '<S13>/FOC_f_fastCTRL'
                                        *   '<S13>/FOC_f_fastCTRL1'
                                        *   '<S15>/FOC_T_fast'
                                        *   '<S26>/FOC_T_fast'
                                        *   '<S48>/FOC_T_fast'
                                        *   '<S33>/FOC_T_fast'
                                        *   '<S34>/FOC_T_fast'
                                        *   '<S41>/FOC_T_fast'
                                        *   '<S45>/FOC_T_fast'
                                        */
extern real_T FOC_output_trafo_delay;  /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S5>/FOC_output_trafo_delay'
                                        */
extern real_T FOC_phi_offset;          /* Variable: FOC_phi_offset
                                        * Referenced by: '<S5>/Constant'
                                        */
extern real_T Factor_OmegaRot;         /* Variable: Factor_OmegaRot
                                        * Referenced by: '<S26>/Gain5'
                                        */

/* Model entry point functions */
extern void FOC_fastCTRL_initialize(RT_MODEL_FOC_fastCTRL_T *const
  FOC_fastCTRL_M);
extern void FOC_fastCTRL_step(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M);
extern void FOC_fastCTRL_terminate(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S13>/testo' : Unused code path elimination
 * Block '<S17>/Constant' : Unused code path elimination
 * Block '<S17>/Constant1' : Unused code path elimination
 * Block '<S17>/Constant2' : Unused code path elimination
 * Block '<S17>/Constant3' : Unused code path elimination
 * Block '<S17>/Sum1' : Unused code path elimination
 * Block '<S17>/Switch1' : Unused code path elimination
 * Block '<S17>/Switch2' : Unused code path elimination
 * Block '<S4>/Abs' : Unused code path elimination
 * Block '<S18>/Constant' : Unused code path elimination
 * Block '<S18>/Sum1' : Unused code path elimination
 * Block '<S18>/Switch_Phi' : Unused code path elimination
 * Block '<S18>/Trigonometric Function' : Unused code path elimination
 * Block '<S4>/Constant' : Unused code path elimination
 * Block '<S4>/Constant1' : Unused code path elimination
 * Block '<S4>/Constant2' : Unused code path elimination
 * Block '<S4>/FOC_AngleEst_Lq' : Unused code path elimination
 * Block '<S4>/FOC_AngleEst_Rs' : Unused code path elimination
 * Block '<S19>/Constant' : Unused code path elimination
 * Block '<S19>/Divide' : Unused code path elimination
 * Block '<S19>/Divide2' : Unused code path elimination
 * Block '<S19>/FOC_f_fast' : Unused code path elimination
 * Block '<S19>/Product3' : Unused code path elimination
 * Block '<S19>/Sum' : Unused code path elimination
 * Block '<S19>/Sum1' : Unused code path elimination
 * Block '<S19>/T_ab' : Unused code path elimination
 * Block '<S19>/Tau' : Unused code path elimination
 * Block '<S19>/Unit Delay' : Unused code path elimination
 * Block '<S4>/Product' : Unused code path elimination
 * Block '<S4>/Product1' : Unused code path elimination
 * Block '<S4>/Product2' : Unused code path elimination
 * Block '<S4>/Product3' : Unused code path elimination
 * Block '<S20>/Bias' : Unused code path elimination
 * Block '<S20>/Constant' : Unused code path elimination
 * Block '<S20>/Constant1' : Unused code path elimination
 * Block '<S20>/Constant2' : Unused code path elimination
 * Block '<S20>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S20>/Discrete Transfer Fcn1' : Unused code path elimination
 * Block '<S20>/FOC_f_fastCTRL' : Unused code path elimination
 * Block '<S20>/FOC_f_fastCTRL1' : Unused code path elimination
 * Block '<S20>/Logical Operator' : Unused code path elimination
 * Block '<S20>/Product' : Unused code path elimination
 * Block '<S20>/Product1' : Unused code path elimination
 * Block '<S20>/Relational Operator' : Unused code path elimination
 * Block '<S20>/Relational Operator1' : Unused code path elimination
 * Block '<S20>/Relational Operator2' : Unused code path elimination
 * Block '<S20>/Switch1' : Unused code path elimination
 * Block '<S20>/Switch_speed' : Unused code path elimination
 * Block '<S20>/testo' : Unused code path elimination
 * Block '<S4>/Sum' : Unused code path elimination
 * Block '<S4>/Sum1' : Unused code path elimination
 * Block '<S4>/Sum2' : Unused code path elimination
 * Block '<S4>/Sum3' : Unused code path elimination
 * Block '<S4>/Switch' : Unused code path elimination
 * Block '<S4>/Switch2' : Unused code path elimination
 * Block '<S4>/Trigonometric Function' : Unused code path elimination
 * Block '<S21>/FOC_AngleEst_Delay1' : Unused code path elimination
 * Block '<S21>/FOC_AngleEst_Delay2' : Unused code path elimination
 * Block '<S21>/Switch3' : Unused code path elimination
 * Block '<S21>/Switch4' : Unused code path elimination
 * Block '<S21>/Unit Delay' : Unused code path elimination
 * Block '<S21>/Unit Delay1' : Unused code path elimination
 * Block '<S22>/FOC_T_fast' : Unused code path elimination
 * Block '<S22>/Product' : Unused code path elimination
 * Block '<S22>/Sum4' : Unused code path elimination
 * Block '<S22>/Unit Delay' : Unused code path elimination
 * Block '<S23>/Product' : Unused code path elimination
 * Block '<S4>/komp_kp' : Unused code path elimination
 * Block '<S4>/phi_est_2' : Unused code path elimination
 * Block '<S4>/useFilteredCorrection' : Unused code path elimination
 * Block '<S25>/Anpassung der Signalfrequenz an Polpaarzahl' : Unused code path elimination
 * Block '<S25>/Constant' : Unused code path elimination
 * Block '<S35>/I_ph_RMS' : Unused code path elimination
 * Block '<S35>/I_ph_peak' : Unused code path elimination
 * Block '<S35>/Math Function' : Unused code path elimination
 * Block '<S35>/Sum' : Unused code path elimination
 * Block '<S36>/I_d_Ref' : Unused code path elimination
 * Block '<S36>/I_q_Ref' : Unused code path elimination
 * Block '<S38>/Gain5' : Unused code path elimination
 * Block '<S38>/Gain6' : Unused code path elimination
 * Block '<S38>/I_d_Act_1' : Unused code path elimination
 * Block '<S38>/I_q_Act_1' : Unused code path elimination
 * Block '<S38>/I_u_1' : Unused code path elimination
 * Block '<S38>/I_v_1' : Unused code path elimination
 * Block '<S38>/I_w_1' : Unused code path elimination
 * Block '<S39>/I_d_Act_2' : Unused code path elimination
 * Block '<S39>/I_d_Act_filt_2' : Unused code path elimination
 * Block '<S39>/I_q_Act_2' : Unused code path elimination
 * Block '<S39>/I_q_Act_filt_2' : Unused code path elimination
 * Block '<S39>/I_u_2' : Unused code path elimination
 * Block '<S39>/I_v_2' : Unused code path elimination
 * Block '<S39>/I_w_2' : Unused code path elimination
 * Block '<S51>/ModInd_1' : Unused code path elimination
 * Block '<S51>/ModInd_2' : Unused code path elimination
 * Block '<S56>/U_d_1' : Unused code path elimination
 * Block '<S56>/U_q_1' : Unused code path elimination
 * Block '<S57>/U_d_2' : Unused code path elimination
 * Block '<S57>/U_q_2' : Unused code path elimination
 * Block '<S3>/Gain2' : Eliminated nontunable gain of 1
 * Block '<S5>/dummy_gain1' : Eliminated nontunable gain of 1
 * Block '<S5>/dummy_gain2' : Eliminated nontunable gain of 1
 * Block '<S5>/dummy_gain4' : Eliminated nontunable gain of 1
 * Block '<S5>/dummy_gain5' : Eliminated nontunable gain of 1
 * Block '<S5>/dummy_gain6' : Eliminated nontunable gain of 1
 * Block '<S5>/dummy_gain7' : Eliminated nontunable gain of 1
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * hilite_system('FCF/FOC_fastCTRL')    - opens subsystem FCF/FOC_fastCTRL
 * hilite_system('FCF/FOC_fastCTRL/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FCF'
 * '<S1>'   : 'FCF/FOC_fastCTRL'
 * '<S2>'   : 'FCF/FOC_fastCTRL/AKS_Switch'
 * '<S3>'   : 'FCF/FOC_fastCTRL/AngleEstimation'
 * '<S4>'   : 'FCF/FOC_fastCTRL/AngleEstimation_2'
 * '<S5>'   : 'FCF/FOC_fastCTRL/Angle_Adaption'
 * '<S6>'   : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER'
 * '<S7>'   : 'FCF/FOC_fastCTRL/U_f'
 * '<S8>'   : 'FCF/FOC_fastCTRL/Voltage_Output'
 * '<S9>'   : 'FCF/FOC_fastCTRL/calcPowerFactor'
 * '<S10>'  : 'FCF/FOC_fastCTRL/AngleEstimation/2piFormatting'
 * '<S11>'  : 'FCF/FOC_fastCTRL/AngleEstimation/AngleCalculation'
 * '<S12>'  : 'FCF/FOC_fastCTRL/AngleEstimation/LowpassFilter'
 * '<S13>'  : 'FCF/FOC_fastCTRL/AngleEstimation/Subsystem2'
 * '<S14>'  : 'FCF/FOC_fastCTRL/AngleEstimation/delay'
 * '<S15>'  : 'FCF/FOC_fastCTRL/AngleEstimation/disc. Int.'
 * '<S16>'  : 'FCF/FOC_fastCTRL/AngleEstimation/disc. P'
 * '<S17>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/2piFormatting'
 * '<S18>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/AngleCalculation'
 * '<S19>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/LowpassFilter'
 * '<S20>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/Subsystem2'
 * '<S21>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/delay'
 * '<S22>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/disc. Int.'
 * '<S23>'  : 'FCF/FOC_fastCTRL/AngleEstimation_2/disc. P'
 * '<S24>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleAdaption_Range'
 * '<S25>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleAdaption_mech2el'
 * '<S26>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleObserver'
 * '<S27>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/InvertAngle'
 * '<S28>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/Modulo2Pi'
 * '<S29>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/Modulo2Pi_'
 * '<S30>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/Modulo2Pi__'
 * '<S31>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleAdaption_Range/Modulo2Pi'
 * '<S32>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleObserver/2PiKorr'
 * '<S33>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleObserver/integrator'
 * '<S34>'  : 'FCF/FOC_fastCTRL/Angle_Adaption/AngleObserver/integrator1'
 * '<S35>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/Auxiliary_Calculations'
 * '<S36>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_1'
 * '<S37>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_2'
 * '<S38>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/UVW_DQ_1'
 * '<S39>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/UVW_DQ_2'
 * '<S40>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_1/AntiWindup'
 * '<S41>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_1/FeedbackPI'
 * '<S42>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_1/AntiWindup/AntiWindupGT_d'
 * '<S43>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_1/AntiWindup/AntiWindupGT_q'
 * '<S44>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_2/AntiWindup'
 * '<S45>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_2/FeedbackPI'
 * '<S46>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_2/AntiWindup/AntiWindupGT_d'
 * '<S47>'  : 'FCF/FOC_fastCTRL/CURRENT_CONTROLLER/PI_CONTROLLER_2/AntiWindup/AntiWindupGT_q'
 * '<S48>'  : 'FCF/FOC_fastCTRL/U_f/SubS_2pi_Integrator'
 * '<S49>'  : 'FCF/FOC_fastCTRL/U_f/UfKennlinie'
 * '<S50>'  : 'FCF/FOC_fastCTRL/Voltage_Output/Adjust_duty_cycle_range'
 * '<S51>'  : 'FCF/FOC_fastCTRL/Voltage_Output/Calc_Modulation_Index'
 * '<S52>'  : 'FCF/FOC_fastCTRL/Voltage_Output/NormalizedVoltage'
 * '<S53>'  : 'FCF/FOC_fastCTRL/Voltage_Output/Super_Sinus_Modulation'
 * '<S54>'  : 'FCF/FOC_fastCTRL/Voltage_Output/inverse Clarke-Trafo_1'
 * '<S55>'  : 'FCF/FOC_fastCTRL/Voltage_Output/inverse Clarke-Trafo_2'
 * '<S56>'  : 'FCF/FOC_fastCTRL/Voltage_Output/inverse Park-Trafo_1'
 * '<S57>'  : 'FCF/FOC_fastCTRL/Voltage_Output/inverse Park-Trafo_2'
 * '<S58>'  : 'FCF/FOC_fastCTRL/calcPowerFactor/calcAngle'
 * '<S59>'  : 'FCF/FOC_fastCTRL/calcPowerFactor/calcAngle1'
 */
#endif                                 /* RTW_HEADER_FOC_fastCTRL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
