/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_slowCTRL.h
 *
 * Code generated for Simulink model 'FOC_slowCTRL'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Oct  9 23:28:30 2023
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
  real_T Bias;                         /* '<S5>/Bias' */
  real_T UnitDelay;                    /* '<S23>/Unit Delay' */
  real_T Saturation;                   /* '<S23>/Saturation' */
  real_T Sum2;                         /* '<S23>/Sum2' */
  real_T Product1;                     /* '<S8>/Product1' */
  real_T deltariselimit;               /* '<S20>/delta rise limit' */
  real_T TorqRef_Source;               /* '<S1>/TorqRef_Source' */
  real_T Yk1;                          /* '<S20>/Delay Input2' */
  real_T UkYk1;                        /* '<S20>/Difference Inputs1' */
  real_T deltafalllimit;               /* '<S20>/delta fall limit' */
  real_T Switch;                       /* '<S21>/Switch' */
  real_T Switch2;                      /* '<S21>/Switch2' */
  real_T DifferenceInputs2;            /* '<S20>/Difference Inputs2' */
  real_T Switch4;                      /* '<S7>/Switch4' */
  real_T Abs;                          /* '<S8>/Abs' */
  real_T MinMax;                       /* '<S22>/MinMax' */
  real_T Abs1;                         /* '<S22>/Abs1' */
  real_T Abs_h;                        /* '<S22>/Abs' */
  real_T Subtract;                     /* '<S22>/Subtract' */
  real_T Switch_i;                     /* '<S2>/Switch' */
  real_T TorqCtrlDelay;                /* '<S9>/TorqCtrlDelay' */
  real_T MinMax_d;                     /* '<S2>/MinMax' */
  real_T Sum1;                         /* '<S9>/Sum1' */
  real_T FOC_TORQ_REDUC_PGAIN;         /* '<S9>/FOC_TORQ_REDUC_PGAIN' */
  real_T TorqCtrlSum3;                 /* '<S9>/TorqCtrlSum3' */
  real_T Saturation_j;                 /* '<S9>/Saturation' */
  real_T Yk1_o;                        /* '<S12>/Delay Input2' */
  real_T MultiportSwitch1;             /* '<S5>/Multiport Switch1' */
  real_T UkYk1_a;                      /* '<S12>/Difference Inputs1' */
  real_T deltariselimit_k;             /* '<S12>/delta rise limit' */
  real_T deltafalllimit_b;             /* '<S12>/delta fall limit' */
  real_T Switch_n;                     /* '<S13>/Switch' */
  real_T Switch2_h;                    /* '<S13>/Switch2' */
  real_T DifferenceInputs2_f;          /* '<S12>/Difference Inputs2' */
  real_T Switch2_p;                    /* '<S11>/Switch2' */
  real_T Bias_h;                       /* '<S6>/Bias' */
  real_T deltariselimit_o;             /* '<S18>/delta rise limit' */
  real_T MultiportSwitch1_f;           /* '<S6>/Multiport Switch1' */
  real_T Yk1_h;                        /* '<S18>/Delay Input2' */
  real_T UkYk1_f;                      /* '<S18>/Difference Inputs1' */
  real_T deltafalllimit_f;             /* '<S18>/delta fall limit' */
  real_T Switch_j;                     /* '<S19>/Switch' */
  real_T Switch2_pl;                   /* '<S19>/Switch2' */
  real_T DifferenceInputs2_fc;         /* '<S18>/Difference Inputs2' */
  real_T Switch2_e;                    /* '<S17>/Switch2' */
  real_T Product;                      /* '<S15>/Product' */
  real_T Product1_e;                   /* '<S15>/Product1' */
  real_T Subtract1;                    /* '<S15>/Subtract1' */
  real_T Sqrt;                         /* '<S15>/Sqrt' */
  real_T mcrPsiRef1;                   /* '<S15>/mcrPsiRef1' */
  real_T PsiReduceGain1;               /* '<S15>/PsiReduceGain1' */
  real_T IqRef;                        /* '<S15>/MinMax1' */
  real_T FOC_IqDiff;                   /* '<S15>/Subtract' */
  real_T UnitDelay_f;                  /* '<S15>/Unit Delay' */
  real_T Sum;                          /* '<S23>/Sum' */
  real_T Product_m;                    /* '<S23>/Product' */
  real_T Sum1_a;                       /* '<S23>/Sum1' */
  real_T UnitDelay_i;                  /* '<S9>/UnitDelay' */
  real_T FOC_IQ_DIFF_REDUC_GAIN;       /* '<S9>/FOC_IQ_DIFF_REDUC_GAIN' */
  real_T FOC_TORQ_REDUC_GAIN;          /* '<S9>/FOC_TORQ_REDUC_GAIN' */
  real_T TorqCtrlSwitch1;              /* '<S9>/TorqCtrlSwitch1' */
  real_T TorqCtrlSwitch3;              /* '<S9>/TorqCtrlSwitch3' */
  real_T TorqCtrlSum4;                 /* '<S9>/TorqCtrlSum4' */
  real_T TorqCtrlSum1;                 /* '<S9>/TorqCtrlSum1' */
  real_T usrpm;                        /* '<S2>/[1//s] => [rpm]' */
  real_T Product_j[4];                 /* '<S4>/Product' */
  real_T Subtract2;                    /* '<S4>/Subtract2' */
  real_T Sqrt_b;                       /* '<S4>/Sqrt' */
  real_T I_ph_peak;                    /* '<S4>/I_ph_peak' */
  real_T I_ph_rms;                     /* '<S4>/I_ph_rms' */
  real_T Sum_k;                        /* '<S1>/Sum' */
  real_T Sum_e;                        /* '<S31>/Sum' */
  real_T Product2;                     /* '<S31>/Product2' */
  real_T product_2;                    /* '<S31>/product_2' */
  real_T add2;                         /* '<S31>/add2' */
  real_T Product1_eh;                  /* '<S31>/Product1' */
  real_T product;                      /* '<S31>/product' */
  real_T add1;                         /* '<S31>/add1' */
  real_T Add;                          /* '<S31>/Add' */
  real_T uZ_p2;                        /* '<S31>/3*Z_p//2' */
  real_T uph_to_6ph_factor;            /* '<S4>/3ph_to_6ph_factor' */
  real_T Switch2_o;                    /* '<S1>/Switch2' */
  real_T TORQUE_REQ_LIMIT;             /* '<S1>/TORQUE_REQ_LIMIT' */
  real_T deltariselimit_c;             /* '<S29>/delta rise limit' */
  real_T n_Ref_Source;                 /* '<S3>/n_Ref_Source' */
  real_T limitT2;                      /* '<S3>/limit T2' */
  real_T Yk1_g;                        /* '<S29>/Delay Input2' */
  real_T UkYk1_d;                      /* '<S29>/Difference Inputs1' */
  real_T deltafalllimit_m;             /* '<S29>/delta fall limit' */
  real_T Switch_jn;                    /* '<S30>/Switch' */
  real_T Switch2_n;                    /* '<S30>/Switch2' */
  real_T DifferenceInputs2_j;          /* '<S29>/Difference Inputs2' */
  real_T Switch2_a;                    /* '<S27>/Switch2' */
  real_T w_el_Ref_SPEED_CTRL;          /* '<S3>/RPM => w_el' */
  real_T Add_h;                        /* '<S3>/Add' */
  real_T Product6;                     /* '<S3>/Product6' */
  real_T UnitDelay_l;                  /* '<S3>/Unit Delay' */
  real_T Add2;                         /* '<S3>/Add2' */
  real_T TorqLimitSource[2];           /* '<S3>/TorqLimitSource' */
  real_T limitT1;                      /* '<S3>/limit T1' */
  real_T limitT3;                      /* '<S3>/limit T3' */
  real_T Switch_k;                     /* '<S28>/Switch' */
  real_T Switch2_l;                    /* '<S28>/Switch2' */
  real_T Subtract_p;                   /* '<S3>/Subtract' */
  real_T Gain1;                        /* '<S3>/Gain1' */
  real_T Sum_d;                        /* '<S3>/Sum' */
  real_T Product5;                     /* '<S3>/Product5' */
  real_T avoid_div_by_0;               /* '<S3>/avoid_div_by_0' */
  real_T Divide;                       /* '<S3>/Divide' */
  real_T Add1;                         /* '<S3>/Add1' */
  real_T DataTypeConversion;           /* '<S3>/Data Type Conversion' */
  real_T Product_k;                    /* '<S3>/Product' */
  real_T Switch1;                      /* '<S3>/Switch1' */
  real_T TorqCtrlMin2;                 /* '<S9>/TorqCtrlMin2' */
  real_T TorqCtrlMinusOne;             /* '<S9>/TorqCtrlMinusOne' */
  real_T Switch1_o;                    /* '<S22>/Switch1' */
  real_T Gain1_g;                      /* '<S22>/Gain1' */
  real_T Gain;                         /* '<S22>/Gain' */
  real_T Gain_k;                       /* '<S6>/Gain' */
  real_T Sign;                         /* '<S16>/Sign' */
  real_T Abs2;                         /* '<S16>/Abs2' */
  real_T Iq_Ref_M_MTPC;                /* '<S16>/Iq_Ref_M_MTPC' */
  real_T Product1_b;                   /* '<S16>/Product1' */
  real_T Gain_g;                       /* '<S14>/Gain' */
  real_T Add_p;                        /* '<S14>/Add' */
  real_T Product_l;                    /* '<S14>/Product' */
  real_T Add1_d;                       /* '<S14>/Add1' */
  real_T Divide_k;                     /* '<S14>/Divide' */
  real_T IqRefRaw_PSM;                 /* '<S14>/IqRefRaw_PSM' */
  real_T Gain_m;                       /* '<S5>/Gain' */
  real_T Abs2_b;                       /* '<S10>/Abs2' */
  real_T Id_Ref_M_MTPC;                /* '<S10>/Id_Ref_M_MTPC' */
  uint8_T Compare;                     /* '<S26>/Compare' */
  uint8_T Compare_m;                   /* '<S24>/Compare' */
  boolean_T LowerRelop1;               /* '<S21>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S21>/UpperRelop' */
  boolean_T LowerRelop1_n;             /* '<S13>/LowerRelop1' */
  boolean_T UpperRelop_j;              /* '<S13>/UpperRelop' */
  boolean_T LowerRelop1_k;             /* '<S19>/LowerRelop1' */
  boolean_T UpperRelop_o;              /* '<S19>/UpperRelop' */
  boolean_T LowerRelop1_c;             /* '<S30>/LowerRelop1' */
  boolean_T UpperRelop_l;              /* '<S30>/UpperRelop' */
  boolean_T LowerRelop1_c1;            /* '<S28>/LowerRelop1' */
  boolean_T UpperRelop_jt;             /* '<S28>/UpperRelop' */
} B_FOC_slowCTRL_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S23>/Unit Delay' */
  real_T DelayInput2_DSTATE;           /* '<S20>/Delay Input2' */
  real_T TorqCtrlDelay_DSTATE;         /* '<S9>/TorqCtrlDelay' */
  real_T DelayInput2_DSTATE_f;         /* '<S12>/Delay Input2' */
  real_T DelayInput2_DSTATE_e;         /* '<S18>/Delay Input2' */
  real_T UnitDelay_DSTATE_b;           /* '<S15>/Unit Delay' */
  real_T UnitDelay_DSTATE_m;           /* '<S9>/UnitDelay' */
  real_T SCF_Cnt_DSTATE;               /* '<S1>/SCF_Cnt' */
  real_T DelayInput2_DSTATE_d;         /* '<S29>/Delay Input2' */
  real_T UnitDelay_DSTATE_a;           /* '<S3>/Unit Delay' */
  real_T Sum_DWORK1;                   /* '<S23>/Sum' */
  boolean_T SPEED_CONTROLLER_MODE;     /* '<S1>/SPEED_CONTROLLER' */
} DW_FOC_slowCTRL_T;

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

/* Parameters (default storage) */
struct P_FOC_slowCTRL_T_ {
  real_T FOC_ENABLE_Idq_Ref;           /* Variable: FOC_ENABLE_Idq_Ref
                                        * Referenced by: '<S2>/FOC_ENABLE_Idq_Ref'
                                        */
  real_T FOC_IQ_DIFF_REDUC_GAIN;       /* Variable: FOC_IQ_DIFF_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_IQ_DIFF_REDUC_GAIN'
                                        */
  real_T FOC_LIMIT_I_PHASE_PEAK_MAX;   /* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
                                        * Referenced by: '<S15>/Constant'
                                        */
  real_T FOC_LIMIT_Idq_Ref_SlewRate_Down;
                                    /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Down
                                     * Referenced by:
                                     *   '<S11>/Constant7'
                                     *   '<S17>/Constant7'
                                     */
  real_T FOC_LIMIT_Idq_Ref_SlewRate_Up;
                                      /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Up
                                       * Referenced by:
                                       *   '<S11>/Constant6'
                                       *   '<S17>/Constant6'
                                       */
  real_T FOC_LIMIT_Motor_Torque_MAX;   /* Variable: FOC_LIMIT_Motor_Torque_MAX
                                        * Referenced by: '<S8>/Maximum_Torque_Maschine'
                                        */
  real_T FOC_LIMIT_Torque_Derating_Temp;
                                     /* Variable: FOC_LIMIT_Torque_Derating_Temp
                                      * Referenced by: '<S26>/Constant'
                                      */
  real_T FOC_LIMIT_Torque_Ref_MAX;     /* Variable: FOC_LIMIT_Torque_Ref_MAX
                                        * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                        */
  real_T FOC_LIMIT_Torque_Ref_MIN;     /* Variable: FOC_LIMIT_Torque_Ref_MIN
                                        * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                        */
  real_T FOC_LIMIT_Torque_Ref_SlewRate_Down;
                                 /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Down
                                  * Referenced by: '<S7>/Constant7'
                                  */
  real_T FOC_LIMIT_Torque_Ref_SlewRate_Up;
                                   /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Up
                                    * Referenced by: '<S7>/Constant6'
                                    */
  real_T FOC_LIMIT_n_Ref_SlewRate_Down;
                                      /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
                                       * Referenced by: '<S27>/Constant7'
                                       */
  real_T FOC_LIMIT_n_Ref_SlewRate_InitVal;
                                   /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
                                    * Referenced by: '<S29>/Delay Input2'
                                    */
  real_T FOC_LIMIT_n_Ref_SlewRate_Up;  /* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
                                        * Referenced by: '<S27>/Constant6'
                                        */
  real_T FOC_L_sd;                     /* Variable: FOC_L_sd
                                        * Referenced by:
                                        *   '<S31>/FOC_L_sd'
                                        *   '<S14>/Constant1'
                                        */
  real_T FOC_L_sq;                     /* Variable: FOC_L_sq
                                        * Referenced by:
                                        *   '<S31>/FOC_L_sq'
                                        *   '<S14>/Constant2'
                                        */
  real_T FOC_MANUAL_Id_Ref;            /* Variable: FOC_MANUAL_Id_Ref
                                        * Referenced by: '<S5>/Constant5'
                                        */
  real_T FOC_MANUAL_Iq_Ref;            /* Variable: FOC_MANUAL_Iq_Ref
                                        * Referenced by: '<S6>/Constant3'
                                        */
  real_T FOC_MANUAL_Torque_Request;    /* Variable: FOC_MANUAL_Torque_Request
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T FOC_M_peak_max;               /* Variable: FOC_M_peak_max
                                        * Referenced by:
                                        *   '<S3>/limit T1'
                                        *   '<S3>/limit T3'
                                        */
  real_T FOC_Psi_PM;                   /* Variable: FOC_Psi_PM
                                        * Referenced by:
                                        *   '<S31>/FOC_Psi_PM'
                                        *   '<S14>/Constant4'
                                        */
  real_T FOC_SELECT_ExtTrqReq;         /* Variable: FOC_SELECT_ExtTrqReq
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T FOC_SELECT_Id_Ref;            /* Variable: FOC_SELECT_Id_Ref
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real_T FOC_SELECT_Idq_Ref_Ramp;      /* Variable: FOC_SELECT_Idq_Ref_Ramp
                                        * Referenced by:
                                        *   '<S11>/Constant5'
                                        *   '<S17>/Constant5'
                                        */
  real_T FOC_SELECT_Iq_Ref;            /* Variable: FOC_SELECT_Iq_Ref
                                        * Referenced by: '<S6>/Constant5'
                                        */
  real_T FOC_SELECT_Temp_Derating;     /* Variable: FOC_SELECT_Temp_Derating
                                        * Referenced by: '<S2>/Temp_Derating_Selector'
                                        */
  real_T FOC_SELECT_TorqEstMdl;        /* Variable: FOC_SELECT_TorqEstMdl
                                        * Referenced by: '<S4>/Constant4'
                                        */
  real_T FOC_SELECT_Torque_Ref_Ramp;   /* Variable: FOC_SELECT_Torque_Ref_Ramp
                                        * Referenced by: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
                                        */
  real_T FOC_SELECT_n_Ref_Ramp;        /* Variable: FOC_SELECT_n_Ref_Ramp
                                        * Referenced by: '<S27>/Constant5'
                                        */
  real_T FOC_TORQ_REDUC_GAIN;          /* Variable: FOC_TORQ_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_GAIN'
                                        */
  real_T FOC_TORQ_REDUC_PGAIN;         /* Variable: FOC_TORQ_REDUC_PGAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_PGAIN'
                                        */
  real_T FOC_TORQ_REDUC_START;         /* Variable: FOC_TORQ_REDUC_START
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_START'
                                        */
  real_T FOC_T_slow;                   /* Variable: FOC_T_slow
                                        * Referenced by:
                                        *   '<S3>/FOC_T_slow'
                                        *   '<S20>/Constant6'
                                        *   '<S29>/FOC_T_slow'
                                        *   '<S12>/Constant6'
                                        *   '<S18>/Constant6'
                                        */
  real_T FOC_Torque_Derating_Temp_Gain;
                                      /* Variable: FOC_Torque_Derating_Temp_Gain
                                       * Referenced by: '<S23>/Constant1'
                                       */
  real_T FOC_z_P;                      /* Variable: FOC_z_P
                                        * Referenced by:
                                        *   '<S2>/[1//s] => [rpm]'
                                        *   '<S3>/RPM => w_el'
                                        *   '<S31>/3*Z_p//2'
                                        *   '<S14>/Gain'
                                        */
  real_T SCF_MANUAL_U_DC;              /* Variable: SCF_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc2'
                                        */
  real_T SCF_SELECT_U_DC_INPUT;        /* Variable: SCF_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
  real_T SPEED_CTRL_K_AWU;             /* Variable: SPEED_CTRL_K_AWU
                                        * Referenced by: '<S3>/Gain1'
                                        */
  real_T SPEED_CTRL_LIMIT_n_Ref_MAX;   /* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
                                        * Referenced by: '<S3>/limit T2'
                                        */
  real_T SPEED_CTRL_LIMIT_n_Ref_MIN;   /* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
                                        * Referenced by: '<S3>/limit T2'
                                        */
  real_T SPEED_CTRL_MANUAL_n_RPM;      /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S3>/OmegaRot2'
                                        */
  real_T SPEED_CTRL_SELECT_TorqLimit;  /* Variable: SPEED_CTRL_SELECT_TorqLimit
                                        * Referenced by: '<S3>/OmegaRot3'
                                        */
  real_T SPEED_CTRL_SELECT_n_Ref;      /* Variable: SPEED_CTRL_SELECT_n_Ref
                                        * Referenced by: '<S3>/OmegaRot1'
                                        */
  real_T SPEED_CTRL_TORQLIMNEG;        /* Variable: SPEED_CTRL_TORQLIMNEG
                                        * Referenced by: '<S3>/Constant5'
                                        */
  real_T SPEED_CTRL_TORQLIMPOS;        /* Variable: SPEED_CTRL_TORQLIMPOS
                                        * Referenced by: '<S3>/Constant4'
                                        */
  real_T SPEED_CTRL_T_N;               /* Variable: SPEED_CTRL_T_N
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T SPEED_CTRL_V_R;               /* Variable: SPEED_CTRL_V_R
                                        * Referenced by: '<S3>/Constant14'
                                        */
  real_T CompareToConstant_const;     /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S24>/Constant'
                                       */
  real_T zero_Current_Value;           /* Expression: 0
                                        * Referenced by: '<S5>/zero_Current'
                                        */
  real_T Gain_Gain;                    /* Expression: 0.5
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Id_Ref_M_MTPC_tableData[20];/* Expression: EMotor.FEM_data.I_d_M_MTPC.z
                                      * Referenced by: '<S10>/Id_Ref_M_MTPC'
                                      */
  real_T Id_Ref_M_MTPC_bp01Data[20];/* Expression: EMotor.FEM_data.I_d_M_MTPC.x1
                                     * Referenced by: '<S10>/Id_Ref_M_MTPC'
                                     */
  real_T zero_Current_Value_c;         /* Expression: 0
                                        * Referenced by: '<S6>/zero_Current'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S14>/Constant'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 0.5
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Iq_Ref_M_MTPC_tableData[20];/* Expression: EMotor.FEM_data.I_q_M_MTPC.z
                                      * Referenced by: '<S16>/Iq_Ref_M_MTPC'
                                      */
  real_T Iq_Ref_M_MTPC_bp01Data[20];/* Expression: EMotor.FEM_data.I_q_M_MTPC.x1
                                     * Referenced by: '<S16>/Iq_Ref_M_MTPC'
                                     */
  real_T Gain_Gain_n;                  /* Expression: -1
                                        * Referenced by: '<S22>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S22>/Gain1'
                                        */
  real_T TorqCtrlMinusOne_Gain;        /* Expression: -1
                                        * Referenced by: '<S9>/TorqCtrlMinusOne'
                                        */
  real_T ZeroTorq_Value;               /* Expression: 0
                                        * Referenced by: '<S3>/ZeroTorq'
                                        */
  real_T ZeroTorq1_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/ZeroTorq1'
                                        */
  real_T ZeroTorq2_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/ZeroTorq2'
                                        */
  real_T TorqReqNm_Y0;                 /* Computed Parameter: TorqReqNm_Y0
                                        * Referenced by: '<S3>/TorqReq [Nm]'
                                        */
  real_T Switch2_Threshold;            /* Expression: 0
                                        * Referenced by: '<S27>/Switch2'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay'
                                        */
  real_T limitT1_LowerSat;             /* Expression: 0
                                        * Referenced by: '<S3>/limit T1'
                                        */
  real_T limitT3_UpperSat;             /* Expression: 0
                                        * Referenced by: '<S3>/limit T3'
                                        */
  real_T Constant3_Value;              /* Expression: 0.0001
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S3>/Switch1'
                                        */
  real_T Switch2_Threshold_h;          /* Expression: 0
                                        * Referenced by: '<S1>/Switch2'
                                        */
  real_T Constant_Value_p;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T uph_to_6ph_factor_Gain;       /* Expression: 2
                                        * Referenced by: '<S4>/3ph_to_6ph_factor'
                                        */
  real_T Constant_Value_n;             /* Expression: 0
                                        * Referenced by: '<S25>/Constant'
                                        */
  real_T Bias_Bias;                    /* Expression: 1
                                        * Referenced by: '<S5>/Bias'
                                        */
  real_T UnitDelay_InitialCondition_j; /* Expression: 0
                                        * Referenced by: '<S23>/Unit Delay'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1
                                        * Referenced by: '<S23>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S23>/Saturation'
                                        */
  real_T Constant2_Value;              /* Expression: 1
                                        * Referenced by: '<S23>/Constant2'
                                        */
  real_T DelayInput2_InitialCondition; /* Expression: 0
                                        * Referenced by: '<S20>/Delay Input2'
                                        */
  real_T Switch4_Threshold;            /* Expression: 0
                                        * Referenced by: '<S7>/Switch4'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S2>/Switch'
                                        */
  real_T TorqCtrlDelay_InitialCondition;/* Expression: 1
                                         * Referenced by: '<S9>/TorqCtrlDelay'
                                         */
  real_T Saturation_UpperSat_d;        /* Expression: 1
                                        * Referenced by: '<S9>/Saturation'
                                        */
  real_T Saturation_LowerSat_a;        /* Expression: 0
                                        * Referenced by: '<S9>/Saturation'
                                        */
  real_T IdRefZero1_Value;             /* Expression: 0
                                        * Referenced by: '<S5>/IdRefZero1'
                                        */
  real_T DelayInput2_InitialCondition_p;/* Expression: 0
                                         * Referenced by: '<S12>/Delay Input2'
                                         */
  real_T Switch2_Threshold_m;          /* Expression: 0
                                        * Referenced by: '<S11>/Switch2'
                                        */
  real_T Bias_Bias_f;                  /* Expression: 1
                                        * Referenced by: '<S6>/Bias'
                                        */
  real_T IqRefZero_Value;              /* Expression: 0
                                        * Referenced by: '<S6>/IqRefZero'
                                        */
  real_T DelayInput2_InitialCondition_l;/* Expression: 0
                                         * Referenced by: '<S18>/Delay Input2'
                                         */
  real_T Switch2_Threshold_j;          /* Expression: 0
                                        * Referenced by: '<S17>/Switch2'
                                        */
  real_T PsiReduceGain1_Gain;          /* Expression: -1
                                        * Referenced by: '<S15>/PsiReduceGain1'
                                        */
  real_T UnitDelay_InitialCondition_k; /* Expression: 0
                                        * Referenced by: '<S15>/Unit Delay'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: 1
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real_T Constant_Value_j;             /* Expression: 0.5
                                        * Referenced by: '<S23>/Constant'
                                        */
  real_T UnitDelay_InitialCondition_h; /* Expression: 0
                                        * Referenced by: '<S9>/UnitDelay'
                                        */
  real_T Gain_Gain_a;                  /* Expression: 1
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: 1
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S9>/Gain2'
                                        */
  real_T TorqCtrlSwitch1_Threshold;    /* Expression: 0
                                        * Referenced by: '<S9>/TorqCtrlSwitch1'
                                        */
  real_T TorqCtrlSwitch3_Threshold;    /* Expression: 0
                                        * Referenced by: '<S9>/TorqCtrlSwitch3'
                                        */
  real_T Switch1_Threshold_h;          /* Expression: 0
                                        * Referenced by: '<S1>/Switch1'
                                        */
  real_T I_ph_peak_Gain;               /* Expression: 1
                                        * Referenced by: '<S4>/I_ph_peak'
                                        */
  real_T I_ph_rms_Gain;                /* Expression: 1/sqrt(2)
                                        * Referenced by: '<S4>/I_ph_rms'
                                        */
  real_T TorqEst_Nm_Gain;              /* Expression: 1
                                        * Referenced by: '<S4>/TorqEst_Nm'
                                        */
  real_T Counter_Start_Value;          /* Expression: 1
                                        * Referenced by: '<S1>/Counter_Start'
                                        */
  real_T SCF_Cnt_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S1>/SCF_Cnt'
                                        */
  uint8_T Switch1_Threshold_n;        /* Computed Parameter: Switch1_Threshold_n
                                       * Referenced by: '<S22>/Switch1'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM_FOC_slowCTRL_T {
  const char_T * volatile errorStatus;
  B_FOC_slowCTRL_T *blockIO;
  ExtU_FOC_slowCTRL_T *inputs;
  ExtY_FOC_slowCTRL_T *outputs;
  DW_FOC_slowCTRL_T *dwork;
};

/* Block parameters (default storage) */
extern P_FOC_slowCTRL_T FOC_slowCTRL_P;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T Test_Torqu_Request;      /* '<S8>/Switch' */
extern real_T Id_Ref_raw;              /* '<S5>/Multiport Switch' */
extern real_T Iq_Ref_raw;              /* '<S6>/Multiport Switch' */
extern real_T FOC_MotTemp_PSM;         /* '<S8>/Gain1' */
extern real_T Torq_Ref_PSM;            /* '<S9>/Gain' */
extern real_T Torq_Ref_IqDiff;         /* '<S9>/Gain1' */
extern real_T Torq_Ref_PGAIN;          /* '<S9>/Gain2' */
extern real_T Udc_scf;                 /* '<S1>/Switch1' */
extern real_T M_est;                   /* '<S4>/TorqEst_Nm' */
extern real_T SCF_Cnt;                 /* '<S1>/SCF_Cnt' */
extern boolean_T Temp_Derating_aktiv;  /* '<S25>/Compare' */

/* Model entry point functions */
extern void FOC_slowCTRL_initialize(RT_MODEL_FOC_slowCTRL_T *const
  FOC_slowCTRL_M);
extern void FOC_slowCTRL_step(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M);
extern void FOC_slowCTRL_terminate(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M);

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
