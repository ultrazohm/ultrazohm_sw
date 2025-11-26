/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SCF.h
 *
 * Code generated for Simulink model 'FOC_SCF'.
 *
 * Model version                  : 5.9
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Nov 18 15:25:56 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_SCF_h_
#define FOC_SCF_h_
#ifndef FOC_SCF_COMMON_INCLUDES_
#define FOC_SCF_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* FOC_SCF_COMMON_INCLUDES_ */

#include "FOC_SCF_types.h"
#include "rtGetNaN.h"
#include <string.h>
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
  real_T deltariselimit;               /* '<S18>/delta rise limit' */
  real_T Iq_Ref_raw;                   /* '<S6>/Multiport Switch' */
  real_T MultiportSwitch1;             /* '<S6>/Multiport Switch1' */
  real_T Yk1;                          /* '<S18>/Delay Input2' */
  real_T UkYk1;                        /* '<S18>/Difference Inputs1' */
  real_T deltafalllimit;               /* '<S18>/delta fall limit' */
  real_T Switch;                       /* '<S19>/Switch' */
  real_T Switch2;                      /* '<S19>/Switch2' */
  real_T DifferenceInputs2;            /* '<S18>/Difference Inputs2' */
  real32_T Bias;                       /* '<S5>/Bias' */
  real32_T UnitDelay;                  /* '<S23>/Unit Delay' */
  real32_T Saturation;                 /* '<S23>/Saturation' */
  real32_T Sum2;                       /* '<S23>/Sum2' */
  real32_T Product1;                   /* '<S8>/Product1' */
  real32_T deltariselimit_o;           /* '<S20>/delta rise limit' */
  real32_T TorqRef_Source;             /* '<S1>/TorqRef_Source' */
  real32_T Yk1_n;                      /* '<S20>/Delay Input2' */
  real32_T UkYk1_k;                    /* '<S20>/Difference Inputs1' */
  real32_T deltafalllimit_a;           /* '<S20>/delta fall limit' */
  real32_T Switch_k;                   /* '<S21>/Switch' */
  real32_T Switch2_a;                  /* '<S21>/Switch2' */
  real32_T DifferenceInputs2_n;        /* '<S20>/Difference Inputs2' */
  real32_T Switch4;                    /* '<S7>/Switch4' */
  real32_T Abs;                        /* '<S8>/Abs' */
  real32_T MinMax;                     /* '<S22>/MinMax' */
  real32_T Abs1;                       /* '<S22>/Abs1' */
  real32_T Abs_o;                      /* '<S22>/Abs' */
  real32_T Subtract;                   /* '<S22>/Subtract' */
  real32_T Test_Torqu_Request;         /* '<S8>/Switch' */
  real32_T Switch_l;                   /* '<S2>/Switch' */
  real32_T TorqCtrlDelay;              /* '<S9>/TorqCtrlDelay' */
  real32_T MinMax_n;                   /* '<S2>/MinMax' */
  real32_T Sum1;                       /* '<S9>/Sum1' */
  real32_T FOC_TORQ_REDUC_PGAIN;       /* '<S9>/FOC_TORQ_REDUC_PGAIN' */
  real32_T TorqCtrlSum3;               /* '<S9>/TorqCtrlSum3' */
  real32_T Saturation_d;               /* '<S9>/Saturation' */
  real32_T Yk1_b;                      /* '<S12>/Delay Input2' */
  real32_T Id_Ref_raw;                 /* '<S5>/Multiport Switch' */
  real32_T MultiportSwitch1_o;         /* '<S5>/Multiport Switch1' */
  real32_T UkYk1_l;                    /* '<S12>/Difference Inputs1' */
  real32_T deltariselimit_m;           /* '<S12>/delta rise limit' */
  real32_T deltafalllimit_o;           /* '<S12>/delta fall limit' */
  real32_T Switch_m;                   /* '<S13>/Switch' */
  real32_T Switch2_e;                  /* '<S13>/Switch2' */
  real32_T DifferenceInputs2_f;        /* '<S12>/Difference Inputs2' */
  real32_T Switch2_ae;                 /* '<S11>/Switch2' */
  real32_T Bias_h;                     /* '<S6>/Bias' */
  real32_T Gain;                       /* '<S6>/Gain' */
  real32_T Abs2;                       /* '<S16>/Abs2' */
  real32_T Iq_Ref_M_MTPC;              /* '<S16>/Iq_Ref_M_MTPC' */
  real32_T Sign;                       /* '<S16>/Sign' */
  real32_T I_q_Ref_MTPC;               /* '<S16>/Product1' */
  real32_T Switch2_i;                  /* '<S17>/Switch2' */
  real32_T Product;                    /* '<S15>/Product' */
  real32_T Product1_d;                 /* '<S15>/Product1' */
  real32_T Subtract1;                  /* '<S15>/Subtract1' */
  real32_T Sqrt;                       /* '<S15>/Sqrt' */
  real32_T mcrPsiRef1;                 /* '<S15>/mcrPsiRef1' */
  real32_T PsiReduceGain1;             /* '<S15>/PsiReduceGain1' */
  real32_T I_q_Ref_limited;            /* '<S15>/MinMax1' */
  real32_T FOC_IqDiff;                 /* '<S15>/Subtract' */
  real32_T UnitDelay_i;                /* '<S15>/Unit Delay' */
  real32_T FOC_MotTemp_PSM;            /* '<S8>/Gain1' */
  real32_T Sum;                        /* '<S23>/Sum' */
  real32_T Product_c;                  /* '<S23>/Product' */
  real32_T Sum1_i;                     /* '<S23>/Sum1' */
  real32_T UnitDelay_o;                /* '<S9>/UnitDelay' */
  real32_T FOC_IQ_DIFF_REDUC_GAIN;     /* '<S9>/FOC_IQ_DIFF_REDUC_GAIN' */
  real32_T FOC_TORQ_REDUC_GAIN;        /* '<S9>/FOC_TORQ_REDUC_GAIN' */
  real32_T Torq_Ref_PSM;               /* '<S9>/Gain' */
  real32_T Torq_Ref_IqDiff;            /* '<S9>/Gain1' */
  real32_T Torq_Ref_PGAIN;             /* '<S9>/Gain2' */
  real32_T TorqCtrlSwitch1;            /* '<S9>/TorqCtrlSwitch1' */
  real32_T TorqCtrlSwitch3;            /* '<S9>/TorqCtrlSwitch3' */
  real32_T TorqCtrlSum4;               /* '<S9>/TorqCtrlSum4' */
  real32_T TorqCtrlSum1;               /* '<S9>/TorqCtrlSum1' */
  real32_T n_Act;                      /* '<S2>/[1//s] => [rpm]' */
  real32_T U_DC_scf;                   /* '<S1>/Switch1' */
  real32_T Product_h[4];               /* '<S4>/Product' */
  real32_T Subtract2;                  /* '<S4>/Subtract2' */
  real32_T Sqrt_b;                     /* '<S4>/Sqrt' */
  real32_T I_ph_peak_Act;              /* '<S4>/I_ph_peak' */
  real32_T I_ph_rms_Act;               /* '<S4>/I_ph_rms' */
  real32_T M_est;                      /* '<S4>/TorqEst_Nm' */
  real32_T SCF_Cnt;                    /* '<S1>/SCF_Cnt' */
  real32_T Sum_o;                      /* '<S1>/Sum' */
  real32_T Sum_a;                      /* '<S31>/Sum' */
  real32_T Product2;                   /* '<S31>/Product2' */
  real32_T product_2;                  /* '<S31>/product_2' */
  real32_T add2;                       /* '<S31>/add2' */
  real32_T Product1_m;                 /* '<S31>/Product1' */
  real32_T product;                    /* '<S31>/product' */
  real32_T add1;                       /* '<S31>/add1' */
  real32_T Add;                        /* '<S31>/Add' */
  real32_T uZ_p2;                      /* '<S31>/3*Z_p//2' */
  real32_T uph_to_6ph_factor;          /* '<S4>/3ph_to_6ph_factor' */
  real32_T Switch2_d;                  /* '<S1>/Switch2' */
  real32_T TORQUE_REQ_LIMIT;           /* '<S1>/TORQUE_REQ_LIMIT' */
  real32_T deltariselimit_h;           /* '<S29>/delta rise limit' */
  real32_T n_Ref_Source;               /* '<S3>/n_Ref_Source' */
  real32_T limitT2;                    /* '<S3>/limit T2' */
  real32_T Yk1_e;                      /* '<S29>/Delay Input2' */
  real32_T UkYk1_d;                    /* '<S29>/Difference Inputs1' */
  real32_T deltafalllimit_ah;          /* '<S29>/delta fall limit' */
  real32_T Switch_g;                   /* '<S30>/Switch' */
  real32_T Switch2_f;                  /* '<S30>/Switch2' */
  real32_T DifferenceInputs2_m;        /* '<S29>/Difference Inputs2' */
  real32_T n_Ref;                      /* '<S27>/Switch2' */
  real32_T w_el_Ref_SpeedCtrl;         /* '<S3>/RPM => w_el' */
  real32_T Add_e;                      /* '<S3>/Add' */
  real32_T Product6;                   /* '<S3>/Product6' */
  real32_T UnitDelay_k;                /* '<S3>/Unit Delay' */
  real32_T Add2;                       /* '<S3>/Add2' */
  real32_T TorqLimitSource[2];         /* '<S3>/TorqLimitSource' */
  real32_T limitT1;                    /* '<S3>/limit T1' */
  real32_T limitT3;                    /* '<S3>/limit T3' */
  real32_T Switch_p;                   /* '<S28>/Switch' */
  real32_T Switch2_b;                  /* '<S28>/Switch2' */
  real32_T Subtract_m;                 /* '<S3>/Subtract' */
  real32_T Gain1;                      /* '<S3>/Gain1' */
  real32_T Sum_b;                      /* '<S3>/Sum' */
  real32_T Product5;                   /* '<S3>/Product5' */
  real32_T avoid_div_by_0;             /* '<S3>/avoid_div_by_0' */
  real32_T Divide;                     /* '<S3>/Divide' */
  real32_T Add1;                       /* '<S3>/Add1' */
  real32_T Product_p;                  /* '<S3>/Product' */
  real32_T M_Ref_SpeedCtrl;            /* '<S3>/Switch1' */
  real32_T TorqCtrlMin2;               /* '<S9>/TorqCtrlMin2' */
  real32_T TorqCtrlMinusOne;           /* '<S9>/TorqCtrlMinusOne' */
  real32_T Switch1;                    /* '<S22>/Switch1' */
  real32_T Gain1_a;                    /* '<S22>/Gain1' */
  real32_T Gain_n;                     /* '<S22>/Gain' */
  real32_T Gain_e;                     /* '<S14>/Gain' */
  real32_T Add_h;                      /* '<S14>/Add' */
  real32_T Product_n;                  /* '<S14>/Product' */
  real32_T Add1_o;                     /* '<S14>/Add1' */
  real32_T Divide_d;                   /* '<S14>/Divide' */
  real32_T IqRefRaw_PSM;               /* '<S14>/IqRefRaw_PSM' */
  real32_T Gain_i;                     /* '<S5>/Gain' */
  real32_T Abs2_l;                     /* '<S10>/Abs2' */
  real32_T Id_Ref_M_MTPC;              /* '<S10>/Id_Ref_M_MTPC' */
  uint8_T Compare;                     /* '<S26>/Compare' */
  uint8_T Compare_d;                   /* '<S24>/Compare' */
  boolean_T LowerRelop1;               /* '<S21>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S21>/UpperRelop' */
  boolean_T Temp_Derating_aktiv;       /* '<S25>/Compare' */
  boolean_T LowerRelop1_i;             /* '<S13>/LowerRelop1' */
  boolean_T UpperRelop_d;              /* '<S13>/UpperRelop' */
  boolean_T LowerRelop1_j;             /* '<S19>/LowerRelop1' */
  boolean_T UpperRelop_o;              /* '<S19>/UpperRelop' */
  boolean_T LowerRelop1_i5;            /* '<S30>/LowerRelop1' */
  boolean_T UpperRelop_i;              /* '<S30>/UpperRelop' */
  boolean_T LowerRelop1_d;             /* '<S28>/LowerRelop1' */
  boolean_T UpperRelop_id;             /* '<S28>/UpperRelop' */
} B_FOC_SCF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DelayInput2_DSTATE;           /* '<S18>/Delay Input2' */
  real32_T UnitDelay_DSTATE;           /* '<S23>/Unit Delay' */
  real32_T DelayInput2_DSTATE_i;       /* '<S20>/Delay Input2' */
  real32_T TorqCtrlDelay_DSTATE;       /* '<S9>/TorqCtrlDelay' */
  real32_T DelayInput2_DSTATE_h;       /* '<S12>/Delay Input2' */
  real32_T UnitDelay_DSTATE_m;         /* '<S15>/Unit Delay' */
  real32_T UnitDelay_DSTATE_j;         /* '<S9>/UnitDelay' */
  real32_T SCF_Cnt_DSTATE;             /* '<S1>/SCF_Cnt' */
  real32_T DelayInput2_DSTATE_m;       /* '<S29>/Delay Input2' */
  real32_T UnitDelay_DSTATE_mg;        /* '<S3>/Unit Delay' */
  real32_T Sum_DWORK1;                 /* '<S23>/Sum' */
  boolean_T SPEED_CONTROLLER_MODE;     /* '<S1>/SPEED_CONTROLLER' */
} DW_FOC_SCF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T U_DC;                       /* '<Root>/U_DC [V]' */
  real32_T ModInd[2];                  /* '<Root>/ModInd' */
  real32_T w_el_rad_s;                 /* '<Root>/w_el [rad//s]' */
  real32_T I_dq_Act[4];                /* '<Root>/I_dq_Act [A]' */
  real32_T MotTempdegC;                /* '<Root>/MotTemp [degC]' */
  real32_T InvTempdegC;                /* '<Root>/InvTemp [degC]' */
  real32_T EXT_Torque_Request;         /* '<Root>/ExtTorqReq [Nm]' */
  real32_T SPEED_CTRL_Enable;          /* '<Root>/SpeedCtrl_Enable' */
  real32_T ExtTorqLimNm[2];            /* '<Root>/ExtTorqLim [Nm]' */
  real32_T EXT_Speed_Request;          /* '<Root>/ExtSpeedReq [rpm]' */
} ExtU_FOC_SCF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
  real32_T TorqueEstNm;                /* '<Root>/TorqueEst [Nm]' */
  real32_T TorqueRefDeratedNm;         /* '<Root>/TorqueRefDerated [Nm]' */
} ExtY_FOC_SCF_T;

/* Parameters (default storage) */
struct P_FOC_SCF_T_ {
  real32_T FOC_ENABLE_Idq_Ref;         /* Variable: FOC_ENABLE_Idq_Ref
                                        * Referenced by: '<S2>/FOC_ENABLE_Idq_Ref'
                                        */
  real32_T FOC_IQ_DIFF_REDUC_GAIN;     /* Variable: FOC_IQ_DIFF_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_IQ_DIFF_REDUC_GAIN'
                                        */
  real32_T FOC_LIMIT_I_PHASE_PEAK_MAX; /* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
                                        * Referenced by: '<S15>/Constant'
                                        */
  real32_T FOC_LIMIT_Idq_Ref_SlewRate_Down;
                                    /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Down
                                     * Referenced by:
                                     *   '<S11>/Constant7'
                                     *   '<S17>/Constant7'
                                     */
  real32_T FOC_LIMIT_Idq_Ref_SlewRate_Up;
                                      /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Up
                                       * Referenced by:
                                       *   '<S11>/Constant6'
                                       *   '<S17>/Constant6'
                                       */
  real32_T FOC_LIMIT_Motor_Torque_MAX; /* Variable: FOC_LIMIT_Motor_Torque_MAX
                                        * Referenced by: '<S8>/Maximum_Torque_Maschine'
                                        */
  real32_T FOC_LIMIT_Torque_Derating_Temp;
                                     /* Variable: FOC_LIMIT_Torque_Derating_Temp
                                      * Referenced by: '<S26>/Constant'
                                      */
  real32_T FOC_LIMIT_Torque_Ref_MAX;   /* Variable: FOC_LIMIT_Torque_Ref_MAX
                                        * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                        */
  real32_T FOC_LIMIT_Torque_Ref_MIN;   /* Variable: FOC_LIMIT_Torque_Ref_MIN
                                        * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                        */
  real32_T FOC_LIMIT_Torque_Ref_SlewRate_Down;
                                 /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Down
                                  * Referenced by: '<S7>/Constant7'
                                  */
  real32_T FOC_LIMIT_Torque_Ref_SlewRate_Up;
                                   /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Up
                                    * Referenced by: '<S7>/Constant6'
                                    */
  real32_T FOC_LIMIT_n_Ref_SlewRate_Down;
                                      /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
                                       * Referenced by: '<S27>/Constant7'
                                       */
  real32_T FOC_LIMIT_n_Ref_SlewRate_InitVal;
                                   /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
                                    * Referenced by: '<S29>/Delay Input2'
                                    */
  real32_T FOC_LIMIT_n_Ref_SlewRate_Up;/* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
                                        * Referenced by: '<S27>/Constant6'
                                        */
  real32_T FOC_L_sd;                   /* Variable: FOC_L_sd
                                        * Referenced by:
                                        *   '<S31>/FOC_L_sd'
                                        *   '<S14>/Constant1'
                                        */
  real32_T FOC_L_sq;                   /* Variable: FOC_L_sq
                                        * Referenced by:
                                        *   '<S31>/FOC_L_sq'
                                        *   '<S14>/Constant2'
                                        */
  real32_T FOC_MANUAL_Id_Ref;          /* Variable: FOC_MANUAL_Id_Ref
                                        * Referenced by: '<S5>/Constant5'
                                        */
  real32_T FOC_MANUAL_Iq_Ref;          /* Variable: FOC_MANUAL_Iq_Ref
                                        * Referenced by: '<S6>/Constant3'
                                        */
  real32_T FOC_MANUAL_Torque_Request;  /* Variable: FOC_MANUAL_Torque_Request
                                        * Referenced by: '<S1>/Constant'
                                        */
  real32_T FOC_M_peak_max;             /* Variable: FOC_M_peak_max
                                        * Referenced by: '<S3>/limit T1'
                                        */
  real32_T FOC_Psi_PM;                 /* Variable: FOC_Psi_PM
                                        * Referenced by:
                                        *   '<S31>/FOC_Psi_PM'
                                        *   '<S14>/Constant4'
                                        */
  real32_T FOC_SELECT_ExtTrqReq;       /* Variable: FOC_SELECT_ExtTrqReq
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real32_T FOC_SELECT_Id_Ref;          /* Variable: FOC_SELECT_Id_Ref
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real32_T FOC_SELECT_Iq_Ref;          /* Variable: FOC_SELECT_Iq_Ref
                                        * Referenced by: '<S6>/Constant5'
                                        */
  real32_T FOC_TORQ_REDUC_GAIN;        /* Variable: FOC_TORQ_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_GAIN'
                                        */
  real32_T FOC_TORQ_REDUC_PGAIN;       /* Variable: FOC_TORQ_REDUC_PGAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_PGAIN'
                                        */
  real32_T FOC_TORQ_REDUC_START;       /* Variable: FOC_TORQ_REDUC_START
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_START'
                                        */
  real32_T FOC_Torque_Derating_Temp_Gain;
                                      /* Variable: FOC_Torque_Derating_Temp_Gain
                                       * Referenced by: '<S23>/Constant1'
                                       */
  real32_T SCF_MANUAL_U_DC;            /* Variable: SCF_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc2'
                                        */
  real32_T SCF_SELECT_U_DC_INPUT;      /* Variable: SCF_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
  real32_T SPEED_CTRL_K_AWU;           /* Variable: SPEED_CTRL_K_AWU
                                        * Referenced by: '<S3>/Gain1'
                                        */
  real32_T SPEED_CTRL_LIMIT_n_Ref_MAX; /* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
                                        * Referenced by: '<S3>/limit T2'
                                        */
  real32_T SPEED_CTRL_LIMIT_n_Ref_MIN; /* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
                                        * Referenced by: '<S3>/limit T2'
                                        */
  real32_T SPEED_CTRL_MANUAL_n_RPM;    /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S3>/OmegaRot2'
                                        */
  real32_T SPEED_CTRL_TORQLIMNEG;      /* Variable: SPEED_CTRL_TORQLIMNEG
                                        * Referenced by: '<S3>/Constant5'
                                        */
  real32_T SPEED_CTRL_TORQLIMPOS;      /* Variable: SPEED_CTRL_TORQLIMPOS
                                        * Referenced by: '<S3>/Constant4'
                                        */
  real32_T SPEED_CTRL_T_N;             /* Variable: SPEED_CTRL_T_N
                                        * Referenced by: '<S3>/Constant'
                                        */
  real32_T SPEED_CTRL_V_R;             /* Variable: SPEED_CTRL_V_R
                                        * Referenced by: '<S3>/Constant14'
                                        */
  uint8_T FOC_SELECT_Idq_Ref_Ramp;     /* Variable: FOC_SELECT_Idq_Ref_Ramp
                                        * Referenced by:
                                        *   '<S11>/Constant5'
                                        *   '<S17>/Constant5'
                                        */
  uint8_T FOC_SELECT_Temp_Derating;    /* Variable: FOC_SELECT_Temp_Derating
                                        * Referenced by: '<S2>/Temp_Derating_Selector'
                                        */
  uint8_T FOC_SELECT_TorqEstMdl;       /* Variable: FOC_SELECT_TorqEstMdl
                                        * Referenced by: '<S4>/Constant4'
                                        */
  uint8_T FOC_SELECT_Torque_Ref_Ramp;  /* Variable: FOC_SELECT_Torque_Ref_Ramp
                                        * Referenced by: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
                                        */
  uint8_T FOC_SELECT_n_Ref_Ramp;       /* Variable: FOC_SELECT_n_Ref_Ramp
                                        * Referenced by: '<S27>/Constant5'
                                        */
  uint8_T SPEED_CTRL_SELECT_TorqLimit; /* Variable: SPEED_CTRL_SELECT_TorqLimit
                                        * Referenced by: '<S3>/OmegaRot3'
                                        */
  uint8_T SPEED_CTRL_SELECT_n_Ref;     /* Variable: SPEED_CTRL_SELECT_n_Ref
                                        * Referenced by: '<S3>/OmegaRot1'
                                        */
  real32_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S24>/Constant'
                                       */
  real_T FOC_T_slow_Value;             /* Expression: FOC_T_slow
                                        * Referenced by: '<S29>/FOC_T_slow'
                                        */
  real_T Constant6_Value;              /* Expression: FOC_T_slow
                                        * Referenced by: '<S20>/Constant6'
                                        */
  real_T Constant6_Value_d;            /* Expression: FOC_T_slow
                                        * Referenced by: '<S12>/Constant6'
                                        */
  real_T IqRefZero_Value;              /* Expression: 0
                                        * Referenced by: '<S6>/IqRefZero'
                                        */
  real_T Constant6_Value_f;            /* Expression: FOC_T_slow
                                        * Referenced by: '<S18>/Constant6'
                                        */
  real_T DelayInput2_InitialCondition; /* Expression: 0
                                        * Referenced by: '<S18>/Delay Input2'
                                        */
  real32_T zero_Current_Value;         /* Computed Parameter: zero_Current_Value
                                        * Referenced by: '<S5>/zero_Current'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S5>/Gain'
                                        */
  real32_T Id_Ref_M_MTPC_tableData[20];
                                  /* Computed Parameter: Id_Ref_M_MTPC_tableData
                                   * Referenced by: '<S10>/Id_Ref_M_MTPC'
                                   */
  real32_T Id_Ref_M_MTPC_bp01Data[20];
                                   /* Computed Parameter: Id_Ref_M_MTPC_bp01Data
                                    * Referenced by: '<S10>/Id_Ref_M_MTPC'
                                    */
  real32_T zero_Current_Value_l;     /* Computed Parameter: zero_Current_Value_l
                                      * Referenced by: '<S6>/zero_Current'
                                      */
  real32_T Gain_Gain_n;                /* Computed Parameter: Gain_Gain_n
                                        * Referenced by: '<S14>/Gain'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S14>/Constant'
                                        */
  real32_T Gain_Gain_l;                /* Computed Parameter: Gain_Gain_l
                                        * Referenced by: '<S22>/Gain'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S22>/Gain1'
                                        */
  real32_T TorqCtrlMinusOne_Gain;   /* Computed Parameter: TorqCtrlMinusOne_Gain
                                     * Referenced by: '<S9>/TorqCtrlMinusOne'
                                     */
  real32_T ZeroTorq_Value;             /* Computed Parameter: ZeroTorq_Value
                                        * Referenced by: '<S3>/ZeroTorq'
                                        */
  real32_T ZeroTorq1_Value;            /* Computed Parameter: ZeroTorq1_Value
                                        * Referenced by: '<S3>/ZeroTorq1'
                                        */
  real32_T ZeroTorq2_Value;            /* Computed Parameter: ZeroTorq2_Value
                                        * Referenced by: '<S3>/ZeroTorq2'
                                        */
  real32_T TorqReqNm_Y0;               /* Computed Parameter: TorqReqNm_Y0
                                        * Referenced by: '<S3>/TorqReq [Nm]'
                                        */
  real32_T RPMw_el_Gain;               /* Computed Parameter: RPMw_el_Gain
                                        * Referenced by: '<S3>/RPM => w_el'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S3>/Unit Delay'
                                */
  real32_T limitT1_LowerSat;           /* Computed Parameter: limitT1_LowerSat
                                        * Referenced by: '<S3>/limit T1'
                                        */
  real32_T limitT3_UpperSat;           /* Computed Parameter: limitT3_UpperSat
                                        * Referenced by: '<S3>/limit T3'
                                        */
  real32_T limitT3_LowerSat;           /* Computed Parameter: limitT3_LowerSat
                                        * Referenced by: '<S3>/limit T3'
                                        */
  real32_T FOC_T_slow_Value_a;         /* Expression: FOC_T_slow
                                        * Referenced by: '<S3>/FOC_T_slow'
                                        */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real32_T Switch1_Threshold;          /* Computed Parameter: Switch1_Threshold
                                        * Referenced by: '<S3>/Switch1'
                                        */
  real32_T Switch2_Threshold;          /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S1>/Switch2'
                                        */
  real32_T Constant_Value_n;           /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S4>/Constant'
                                        */
  real32_T uZ_p2_Gain;                 /* Computed Parameter: uZ_p2_Gain
                                        * Referenced by: '<S31>/3*Z_p//2'
                                        */
  real32_T uph_to_6ph_factor_Gain; /* Computed Parameter: uph_to_6ph_factor_Gain
                                    * Referenced by: '<S4>/3ph_to_6ph_factor'
                                    */
  real32_T Constant_Value_g;           /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S25>/Constant'
                                        */
  real32_T Bias_Bias;                  /* Computed Parameter: Bias_Bias
                                        * Referenced by: '<S5>/Bias'
                                        */
  real32_T UnitDelay_InitialCondition_e;
                             /* Computed Parameter: UnitDelay_InitialCondition_e
                              * Referenced by: '<S23>/Unit Delay'
                              */
  real32_T Saturation_UpperSat;       /* Computed Parameter: Saturation_UpperSat
                                       * Referenced by: '<S23>/Saturation'
                                       */
  real32_T Saturation_LowerSat;       /* Computed Parameter: Saturation_LowerSat
                                       * Referenced by: '<S23>/Saturation'
                                       */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S23>/Constant2'
                                        */
  real32_T DelayInput2_InitialCondition_l;
                           /* Computed Parameter: DelayInput2_InitialCondition_l
                            * Referenced by: '<S20>/Delay Input2'
                            */
  real32_T TorqCtrlDelay_InitialCondition;
                           /* Computed Parameter: TorqCtrlDelay_InitialCondition
                            * Referenced by: '<S9>/TorqCtrlDelay'
                            */
  real32_T Saturation_UpperSat_h;   /* Computed Parameter: Saturation_UpperSat_h
                                     * Referenced by: '<S9>/Saturation'
                                     */
  real32_T Saturation_LowerSat_e;   /* Computed Parameter: Saturation_LowerSat_e
                                     * Referenced by: '<S9>/Saturation'
                                     */
  real32_T IdRefZero1_Value;           /* Computed Parameter: IdRefZero1_Value
                                        * Referenced by: '<S5>/IdRefZero1'
                                        */
  real32_T DelayInput2_InitialCondition_g;
                           /* Computed Parameter: DelayInput2_InitialCondition_g
                            * Referenced by: '<S12>/Delay Input2'
                            */
  real32_T Bias_Bias_k;                /* Computed Parameter: Bias_Bias_k
                                        * Referenced by: '<S6>/Bias'
                                        */
  real32_T Gain_Gain_d;                /* Computed Parameter: Gain_Gain_d
                                        * Referenced by: '<S6>/Gain'
                                        */
  real32_T Iq_Ref_M_MTPC_tableData[20];
                                  /* Computed Parameter: Iq_Ref_M_MTPC_tableData
                                   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
                                   */
  real32_T Iq_Ref_M_MTPC_bp01Data[20];
                                   /* Computed Parameter: Iq_Ref_M_MTPC_bp01Data
                                    * Referenced by: '<S16>/Iq_Ref_M_MTPC'
                                    */
  real32_T PsiReduceGain1_Gain;       /* Computed Parameter: PsiReduceGain1_Gain
                                       * Referenced by: '<S15>/PsiReduceGain1'
                                       */
  real32_T UnitDelay_InitialCondition_l;
                             /* Computed Parameter: UnitDelay_InitialCondition_l
                              * Referenced by: '<S15>/Unit Delay'
                              */
  real32_T Gain1_Gain_i;               /* Computed Parameter: Gain1_Gain_i
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real32_T Constant_Value_gz;          /* Computed Parameter: Constant_Value_gz
                                        * Referenced by: '<S23>/Constant'
                                        */
  real32_T UnitDelay_InitialCondition_a;
                             /* Computed Parameter: UnitDelay_InitialCondition_a
                              * Referenced by: '<S9>/UnitDelay'
                              */
  real32_T Gain_Gain_j;                /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S9>/Gain'
                                        */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S9>/Gain2'
                                        */
  real32_T TorqCtrlSwitch1_Threshold;
                                /* Computed Parameter: TorqCtrlSwitch1_Threshold
                                 * Referenced by: '<S9>/TorqCtrlSwitch1'
                                 */
  real32_T TorqCtrlSwitch3_Threshold;
                                /* Computed Parameter: TorqCtrlSwitch3_Threshold
                                 * Referenced by: '<S9>/TorqCtrlSwitch3'
                                 */
  real32_T usrpm_Gain;                 /* Computed Parameter: usrpm_Gain
                                        * Referenced by: '<S2>/[1//s] => [rpm]'
                                        */
  real32_T Switch1_Threshold_l;       /* Computed Parameter: Switch1_Threshold_l
                                       * Referenced by: '<S1>/Switch1'
                                       */
  real32_T I_ph_peak_Gain;             /* Computed Parameter: I_ph_peak_Gain
                                        * Referenced by: '<S4>/I_ph_peak'
                                        */
  real32_T I_ph_rms_Gain;              /* Computed Parameter: I_ph_rms_Gain
                                        * Referenced by: '<S4>/I_ph_rms'
                                        */
  real32_T TorqEst_Nm_Gain;            /* Computed Parameter: TorqEst_Nm_Gain
                                        * Referenced by: '<S4>/TorqEst_Nm'
                                        */
  real32_T Counter_Start_Value;       /* Computed Parameter: Counter_Start_Value
                                       * Referenced by: '<S1>/Counter_Start'
                                       */
  real32_T SCF_Cnt_InitialCondition;
                                 /* Computed Parameter: SCF_Cnt_InitialCondition
                                  * Referenced by: '<S1>/SCF_Cnt'
                                  */
  uint8_T Switch1_Threshold_k;        /* Computed Parameter: Switch1_Threshold_k
                                       * Referenced by: '<S22>/Switch1'
                                       */
  uint8_T Switch2_Threshold_l;        /* Computed Parameter: Switch2_Threshold_l
                                       * Referenced by: '<S27>/Switch2'
                                       */
  uint8_T Switch4_Threshold;           /* Computed Parameter: Switch4_Threshold
                                        * Referenced by: '<S7>/Switch4'
                                        */
  uint8_T Switch_Threshold;            /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S2>/Switch'
                                        */
  uint8_T Switch2_Threshold_f;        /* Computed Parameter: Switch2_Threshold_f
                                       * Referenced by: '<S11>/Switch2'
                                       */
  uint8_T Switch2_Threshold_n;        /* Computed Parameter: Switch2_Threshold_n
                                       * Referenced by: '<S17>/Switch2'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM_FOC_SCF_T {
  const char_T * volatile errorStatus;
  B_FOC_SCF_T *blockIO;
  ExtU_FOC_SCF_T *inputs;
  ExtY_FOC_SCF_T *outputs;
  DW_FOC_SCF_T *dwork;
};

/* Block parameters (default storage) */
extern P_FOC_SCF_T FOC_SCF_P;

/* Model entry point functions */
extern void FOC_SCF_initialize(RT_MODEL_FOC_SCF_T *const FOC_SCF_M);
extern void FOC_SCF_step(RT_MODEL_FOC_SCF_T *const FOC_SCF_M);
extern void FOC_SCF_terminate(RT_MODEL_FOC_SCF_T *const FOC_SCF_M);

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
 * hilite_system('MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF')    - opens subsystem MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF
 * hilite_system('MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MotorControl_HeadModel/FOC_SlowCtrlFcn'
 * '<S1>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF'
 * '<S2>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation'
 * '<S3>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/SPEED_CONTROLLER'
 * '<S4>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/TorqEstimation'
 * '<S5>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Id_Ref_Calculation'
 * '<S6>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation'
 * '<S7>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Limit_Torque_Ref_SlewRate'
 * '<S8>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Temp_Derating'
 * '<S9>'   : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Torque_Derating'
 * '<S10>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Id_Ref_MTPC'
 * '<S11>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Limit_Id_SlewRate'
 * '<S12>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Limit_Id_SlewRate/RateLimiterDynamic'
 * '<S13>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Id_Ref_Calculation/Limit_Id_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S14>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/CalcIqRef_from_Torque'
 * '<S15>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Iq_LIMITER'
 * '<S16>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Iq_Ref_MTPC'
 * '<S17>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Limit_Iq_SlewRate'
 * '<S18>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Limit_Iq_SlewRate/RateLimiterDynamic'
 * '<S19>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Iq_Ref_Calculation/Limit_Iq_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S20>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Limit_Torque_Ref_SlewRate/RateLimiterDynamic'
 * '<S21>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Limit_Torque_Ref_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S22>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Temp_Derating/Derating'
 * '<S23>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Temp_Derating/Momentreduzierung'
 * '<S24>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Temp_Derating/Derating/Compare To Constant'
 * '<S25>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Temp_Derating/Derating/Compare To Zero'
 * '<S26>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/FOC_I_dqRef_Calculation/Temp_Derating/Momentreduzierung/CompareToConstant'
 * '<S27>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/SPEED_CONTROLLER/Limit_n_Ref_SlewRate'
 * '<S28>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/SPEED_CONTROLLER/Saturation Dynamic'
 * '<S29>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/SPEED_CONTROLLER/Limit_n_Ref_SlewRate/RateLimiterDynamic'
 * '<S30>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/SPEED_CONTROLLER/Limit_n_Ref_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S31>'  : 'MotorControl_HeadModel/FOC_SlowCtrlFcn/FOC_SCF/TorqEstimation/Linear_Inductance_Model'
 */
#endif                                 /* FOC_SCF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
