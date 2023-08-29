/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_slowCTRL.h
 *
 * Code generated for Simulink model 'FOC_slowCTRL'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Aug 24 12:54:27 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_slowCTRL_h_
#define RTW_HEADER_FOC_slowCTRL_h_
#ifndef FOC_slowCTRL_COMMON_INCLUDES_
#define FOC_slowCTRL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_slowCTRL_COMMON_INCLUDES_ */

#include "FOC_slowCTRL_types.h"
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
  real_T Switch1;                      /* '<S3>/Switch1' */
} B_FOC_slowCTRL_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DelayInput2_DSTATE;           /* '<S20>/Delay Input2' */
  real_T UnitDelay_DSTATE;             /* '<S23>/Unit Delay' */
  real_T TorqCtrlDelay_DSTATE;         /* '<S9>/TorqCtrlDelay' */
  real_T DelayInput2_DSTATE_f;         /* '<S12>/Delay Input2' */
  real_T DelayInput2_DSTATE_e;         /* '<S18>/Delay Input2' */
  real_T UnitDelay_DSTATE_m;           /* '<S9>/UnitDelay' */
  real_T UnitDelay_DSTATE_b;           /* '<S15>/Unit Delay' */
  real_T DelayInput2_DSTATE_d;         /* '<S29>/Delay Input2' */
  real_T UnitDelay_DSTATE_a;           /* '<S3>/Unit Delay' */
  boolean_T SPEED_CONTROLLER_MODE;     /* '<S1>/SPEED_CONTROLLER' */
} DW_FOC_slowCTRL_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Add;                    /* '<S14>/Add' */
} ConstB_FOC_slowCTRL_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: EMotor.FEM_data.I_d_M_MTPC.z
   * Referenced by: '<S10>/Id_Ref_M_MTPC'
   */
  real_T Id_Ref_M_MTPC_tableData[20];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S10>/Id_Ref_M_MTPC'
   *   '<S16>/Iq_Ref_M_MTPC'
   */
  real_T pooled2[20];

  /* Expression: EMotor.FEM_data.I_q_M_MTPC.z
   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
   */
  real_T Iq_Ref_M_MTPC_tableData[20];
} ConstP_FOC_slowCTRL_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T U_DCV;                        /* '<Root>/U_DC [V]' */
  real_T ModInd[2];                    /* '<Root>/ModInd' */
  real_T w_elrads;                     /* '<Root>/w_el [rad//s]' */
  real_T MotTempdegC;                  /* '<Root>/MotTemp [degC]' */
  real_T InvTempdegC;                  /* '<Root>/InvTemp [degC]' */
  real_T I_dq_ActA[4];                 /* '<Root>/I_dq_Act [A]' */
  real_T ExtTorqReqNm;                 /* '<Root>/ExtTorqReq [Nm]' */
  real_T SpeedCtrl_Enable;             /* '<Root>/SpeedCtrl_Enable' */
  real_T ExtTorqLimNm[2];              /* '<Root>/ExtTorqLim [Nm]' */
  real_T ExtSpeedReqrpm;               /* '<Root>/ExtSpeedReq [rpm]' */
} ExtU_FOC_slowCTRL_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T I_dq_RefA[2];                 /* '<Root>/I_dq_Ref [A]' */
  real_T TorqueEstNm;                  /* '<Root>/TorqueEst [Nm]' */
  real_T TorqueRefDeratedNm;           /* '<Root>/TorqueRefDerated [Nm]' */
} ExtY_FOC_slowCTRL_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_slowCTRL_T {
  const char_T * volatile errorStatus;
  B_FOC_slowCTRL_T *blockIO;
  ExtU_FOC_slowCTRL_T *inputs;
  ExtY_FOC_slowCTRL_T *outputs;
  DW_FOC_slowCTRL_T *dwork;
};

extern const ConstB_FOC_slowCTRL_T FOC_slowCTRL_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_FOC_slowCTRL_T FOC_slowCTRL_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T Udc_scf;                 /* '<S1>/Switch1' */
extern real_T Test_Torqu_Request;      /* '<S8>/Switch' */
extern real_T Torq_Ref_PGAIN;          /* '<S9>/FOC_TORQ_REDUC_PGAIN' */
extern real_T Id_Ref_raw;              /* '<S5>/Multiport Switch' */
extern real_T Iq_Ref_raw;              /* '<S6>/Multiport Switch' */
extern real_T Torq_Ref_PSM;            /* '<S9>/Gain' */
extern real_T Torq_Ref_IqDiff;         /* '<S9>/FOC_IQ_DIFF_REDUC_GAIN' */
extern real_T M_est;                   /* '<S4>/TorqEst_Nm' */
extern real_T FOC_MotTemp_PSM;         /* '<S8>/Gain1' */
extern boolean_T Temp_Derating_aktiv;  /* '<S25>/Compare' */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T FOC_ENABLE_Idq_Ref;      /* Variable: FOC_ENABLE_Idq_Ref
                                        * Referenced by: '<S2>/FOC_ENABLE_Idq_Ref'
                                        */
extern real_T FOC_IQ_DIFF_REDUC_GAIN;  /* Variable: FOC_IQ_DIFF_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_IQ_DIFF_REDUC_GAIN'
                                        */
extern real_T FOC_LIMIT_I_PHASE_PEAK_MAX;/* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
                                          * Referenced by: '<S15>/Constant'
                                          */
extern real_T FOC_LIMIT_Idq_Ref_SlewRate_Down;
                                    /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Down
                                     * Referenced by:
                                     *   '<S11>/Constant7'
                                     *   '<S17>/Constant7'
                                     */
extern real_T FOC_LIMIT_Idq_Ref_SlewRate_Up;
                                      /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Up
                                       * Referenced by:
                                       *   '<S11>/Constant6'
                                       *   '<S17>/Constant6'
                                       */
extern real_T FOC_LIMIT_Motor_Torque_MAX;/* Variable: FOC_LIMIT_Motor_Torque_MAX
                                          * Referenced by: '<S8>/Maximum_Torque_Maschine'
                                          */
extern real_T FOC_LIMIT_Torque_Derating_Temp;
                                     /* Variable: FOC_LIMIT_Torque_Derating_Temp
                                      * Referenced by: '<S26>/Constant'
                                      */
extern real_T FOC_LIMIT_Torque_Ref_MAX;/* Variable: FOC_LIMIT_Torque_Ref_MAX
                                        * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                        */
extern real_T FOC_LIMIT_Torque_Ref_MIN;/* Variable: FOC_LIMIT_Torque_Ref_MIN
                                        * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                        */
extern real_T FOC_LIMIT_Torque_Ref_SlewRate_Down;
                                 /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Down
                                  * Referenced by: '<S7>/Constant7'
                                  */
extern real_T FOC_LIMIT_Torque_Ref_SlewRate_Up;
                                   /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Up
                                    * Referenced by: '<S7>/Constant6'
                                    */
extern real_T FOC_LIMIT_n_Ref_SlewRate_Down;
                                      /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
                                       * Referenced by: '<S27>/Constant7'
                                       */
extern real_T FOC_LIMIT_n_Ref_SlewRate_InitVal;
                                   /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
                                    * Referenced by: '<S29>/Delay Input2'
                                    */
extern real_T FOC_LIMIT_n_Ref_SlewRate_Up;/* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
                                           * Referenced by: '<S27>/Constant6'
                                           */
extern real_T FOC_MANUAL_Id_Ref;       /* Variable: FOC_MANUAL_Id_Ref
                                        * Referenced by: '<S5>/Constant5'
                                        */
extern real_T FOC_MANUAL_Iq_Ref;       /* Variable: FOC_MANUAL_Iq_Ref
                                        * Referenced by: '<S6>/Constant3'
                                        */
extern real_T FOC_MANUAL_Torque_Request;/* Variable: FOC_MANUAL_Torque_Request
                                         * Referenced by: '<S1>/Constant'
                                         */
extern real_T FOC_SELECT_ExtTrqReq;    /* Variable: FOC_SELECT_ExtTrqReq
                                        * Referenced by: '<S1>/Constant2'
                                        */
extern real_T FOC_SELECT_Id_Ref;       /* Variable: FOC_SELECT_Id_Ref
                                        * Referenced by: '<S5>/Constant3'
                                        */
extern real_T FOC_SELECT_Idq_Ref_Ramp; /* Variable: FOC_SELECT_Idq_Ref_Ramp
                                        * Referenced by:
                                        *   '<S11>/Constant5'
                                        *   '<S17>/Constant5'
                                        */
extern real_T FOC_SELECT_Iq_Ref;       /* Variable: FOC_SELECT_Iq_Ref
                                        * Referenced by: '<S6>/Constant5'
                                        */
extern real_T FOC_SELECT_Temp_Derating;/* Variable: FOC_SELECT_Temp_Derating
                                        * Referenced by: '<S2>/Temp_Derating_Selector'
                                        */
extern real_T FOC_SELECT_TorqEstMdl;   /* Variable: FOC_SELECT_TorqEstMdl
                                        * Referenced by: '<S4>/Constant4'
                                        */
extern real_T FOC_SELECT_Torque_Ref_Ramp;/* Variable: FOC_SELECT_Torque_Ref_Ramp
                                          * Referenced by: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
                                          */
extern real_T FOC_SELECT_n_Ref_Ramp;   /* Variable: FOC_SELECT_n_Ref_Ramp
                                        * Referenced by: '<S27>/Constant5'
                                        */
extern real_T FOC_TORQ_REDUC_GAIN;     /* Variable: FOC_TORQ_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_GAIN'
                                        */
extern real_T FOC_TORQ_REDUC_PGAIN;    /* Variable: FOC_TORQ_REDUC_PGAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_PGAIN'
                                        */
extern real_T FOC_TORQ_REDUC_START;    /* Variable: FOC_TORQ_REDUC_START
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_START'
                                        */
extern real_T FOC_Torque_Derating_Temp_Gain;
                                      /* Variable: FOC_Torque_Derating_Temp_Gain
                                       * Referenced by: '<S23>/Constant1'
                                       */
extern real_T FOC_z_P;                 /* Variable: FOC_z_P
                                        * Referenced by:
                                        *   '<S3>/RPM => w_el'
                                        *   '<S31>/3*Z_p//2'
                                        *   '<S14>/Gain'
                                        */
extern real_T SCF_MANUAL_U_DC;         /* Variable: SCF_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc2'
                                        */
extern real_T SCF_SELECT_U_DC_INPUT;   /* Variable: SCF_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
extern real_T SPEED_CTRL_K_AWU;        /* Variable: SPEED_CTRL_K_AWU
                                        * Referenced by: '<S3>/Gain1'
                                        */
extern real_T SPEED_CTRL_LIMIT_n_Ref_MAX;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
                                          * Referenced by: '<S3>/limit T2'
                                          */
extern real_T SPEED_CTRL_LIMIT_n_Ref_MIN;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
                                          * Referenced by: '<S3>/limit T2'
                                          */
extern real_T SPEED_CTRL_MANUAL_n_RPM; /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S3>/OmegaRot2'
                                        */
extern real_T SPEED_CTRL_SELECT_TorqLimit;/* Variable: SPEED_CTRL_SELECT_TorqLimit
                                           * Referenced by: '<S3>/OmegaRot3'
                                           */
extern real_T SPEED_CTRL_SELECT_n_Ref; /* Variable: SPEED_CTRL_SELECT_n_Ref
                                        * Referenced by: '<S3>/OmegaRot1'
                                        */
extern real_T SPEED_CTRL_TORQLIMNEG;   /* Variable: SPEED_CTRL_TORQLIMNEG
                                        * Referenced by: '<S3>/Constant5'
                                        */
extern real_T SPEED_CTRL_TORQLIMPOS;   /* Variable: SPEED_CTRL_TORQLIMPOS
                                        * Referenced by: '<S3>/Constant4'
                                        */
extern real_T SPEED_CTRL_T_N;          /* Variable: SPEED_CTRL_T_N
                                        * Referenced by: '<S3>/Constant'
                                        */
extern real_T SPEED_CTRL_V_R;          /* Variable: SPEED_CTRL_V_R
                                        * Referenced by: '<S3>/Constant14'
                                        */

/* Model entry point functions */
extern void FOC_slowCTRL_initialize(RT_MODEL_FOC_slowCTRL_T *const
  FOC_slowCTRL_M);
extern void FOC_slowCTRL_step(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M);
extern void FOC_slowCTRL_terminate(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S12>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Propagation' : Unused code path elimination
 * Block '<S20>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/[1//s] => [rpm]' : Unused code path elimination
 * Block '<S29>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Data Type Propagation' : Unused code path elimination
 * Block '<S28>/Data Type Duplicate' : Unused code path elimination
 * Block '<S28>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/I_ph_peak' : Unused code path elimination
 * Block '<S4>/I_ph_rms' : Unused code path elimination
 * Block '<S4>/Product' : Unused code path elimination
 * Block '<S4>/Sqrt' : Unused code path elimination
 * Block '<S4>/Subtract2' : Unused code path elimination
 * Block '<S22>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S9>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S9>/Gain2' : Eliminated nontunable gain of 1
 * Block '<S3>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * hilite_system('SCF/FOC_slowCTRL')    - opens subsystem SCF/FOC_slowCTRL
 * hilite_system('SCF/FOC_slowCTRL/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SCF'
 * '<S1>'   : 'SCF/FOC_slowCTRL'
 * '<S2>'   : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation'
 * '<S3>'   : 'SCF/FOC_slowCTRL/SPEED_CONTROLLER'
 * '<S4>'   : 'SCF/FOC_slowCTRL/TorqEstimation'
 * '<S5>'   : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Id_Ref_Calculation'
 * '<S6>'   : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation'
 * '<S7>'   : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Limit_Torque_Ref_SlewRate'
 * '<S8>'   : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Temp_Derating'
 * '<S9>'   : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Torque_Derating'
 * '<S10>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Id_Ref_MTPC'
 * '<S11>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Limit_Id_SlewRate'
 * '<S12>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Limit_Id_SlewRate/RateLimiterDynamic'
 * '<S13>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Limit_Id_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S14>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/CalcIqRef_from_Torque'
 * '<S15>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Iq_LIMITER'
 * '<S16>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Iq_Ref_MTPC'
 * '<S17>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Limit_Iq_SlewRate'
 * '<S18>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Limit_Iq_SlewRate/RateLimiterDynamic'
 * '<S19>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Limit_Iq_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S20>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Limit_Torque_Ref_SlewRate/RateLimiterDynamic'
 * '<S21>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Limit_Torque_Ref_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S22>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Temp_Derating/Derating'
 * '<S23>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Temp_Derating/Momentreduzierung'
 * '<S24>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Temp_Derating/Derating/Compare To Constant'
 * '<S25>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Temp_Derating/Derating/Compare To Zero'
 * '<S26>'  : 'SCF/FOC_slowCTRL/FOC_I_dqRef_Calculation/Temp_Derating/Momentreduzierung/CompareToConstant'
 * '<S27>'  : 'SCF/FOC_slowCTRL/SPEED_CONTROLLER/Limit_n_Ref_SlewRate'
 * '<S28>'  : 'SCF/FOC_slowCTRL/SPEED_CONTROLLER/Saturation Dynamic'
 * '<S29>'  : 'SCF/FOC_slowCTRL/SPEED_CONTROLLER/Limit_n_Ref_SlewRate/RateLimiterDynamic'
 * '<S30>'  : 'SCF/FOC_slowCTRL/SPEED_CONTROLLER/Limit_n_Ref_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S31>'  : 'SCF/FOC_slowCTRL/TorqEstimation/Linear_Inductance_Model'
 */
#endif                                 /* RTW_HEADER_FOC_slowCTRL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
