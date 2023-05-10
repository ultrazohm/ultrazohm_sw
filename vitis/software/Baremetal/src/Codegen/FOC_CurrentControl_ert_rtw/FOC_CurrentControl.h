/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_CurrentControl.h
 *
 * Code generated for Simulink model 'FOC_CurrentControl'.
 *
 * Model version                  : 7.2
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed May 10 08:14:37 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_CurrentControl_h_
#define RTW_HEADER_FOC_CurrentControl_h_
#ifndef FOC_CurrentControl_COMMON_INCLUDES_
#define FOC_CurrentControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_CurrentControl_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE_b[2];        /* '<S21>/Unit Delay' */
  real_T IntegDelay1_DSTATE[2];        /* '<S32>/IntegDelay1' */
  real_T UnitDelay1_DSTATE_m[2];       /* '<S20>/Unit Delay1' */
  real_T UnitDelay_DSTATE_ec[2];       /* '<S20>/Unit Delay' */
  real_T DiscreteFIRFilter20thorder1_sta[19];
                                   /* '<S30>/Discrete FIR Filter 20th order1' */
  real_T DiscreteFIRFilter20thorder_stat[19];
                                    /* '<S30>/Discrete FIR Filter 20th order' */
  real_T DiscreteFIRFilter20thorder1_s_g[19];
                                   /* '<S36>/Discrete FIR Filter 20th order1' */
  real_T DiscreteFIRFilter20thorder_st_n[19];
                                    /* '<S36>/Discrete FIR Filter 20th order' */
  real_T TrafoSum;                     /* '<S30>/TrafoSum' */
  real_T TrafoSum1;                    /* '<S30>/TrafoSum1' */
  real_T DiscreteTransferFcn_states;   /* '<S15>/Discrete Transfer Fcn' */
  real_T UnitDelay_DSTATE;             /* '<S66>/Unit Delay' */
  real_T UnitDelay_DSTATE_g;           /* '<S46>/Unit Delay' */
  real_T UnitDelay_DSTATE_e;           /* '<S49>/Unit Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S27>/Unit Delay1' */
  real_T UnitDelay_DSTATE_m;           /* '<S18>/Unit Delay' */
  real_T DiscreteTransferFcn_states_e; /* '<S19>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states;  /* '<S19>/Discrete Transfer Fcn1' */
  real_T UnitDelay_DSTATE_a;           /* '<S26>/Unit Delay' */
  real_T UnitDelay3_DSTATE;            /* '<S23>/Unit Delay3' */
  real_T UnitDelay_DSTATE_p;           /* '<S45>/Unit Delay' */
  real_T UnitDelay_DSTATE_gl;          /* '<S48>/Unit Delay' */
  real_T UnitDelay_DSTATE_c;           /* '<S41>/Unit Delay' */
  real_T UnitDelay1_DSTATE_ms;         /* '<S28>/Unit Delay1' */
  real_T DelayInput2_DSTATE;           /* '<S64>/Delay Input2' */
  real_T UnitDelay_DSTATE_pj;          /* '<S14>/Unit Delay' */
  int32_T DiscreteFIRFilter20thorder1_cir;
                                   /* '<S30>/Discrete FIR Filter 20th order1' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S30>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder1_c_k;
                                   /* '<S36>/Discrete FIR Filter 20th order1' */
  int32_T DiscreteFIRFilter20thorder_ci_a;
                                    /* '<S36>/Discrete FIR Filter 20th order' */
  uint32_T m_bpIndex;                  /* '<S14>/V_R_Scheduling' */
  boolean_T DelayInput1_DSTATE;        /* '<S57>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_e;      /* '<S52>/Delay Input1' */
  boolean_T UnitDelay_DSTATE_k;        /* '<S44>/Unit Delay' */
  boolean_T Memory_PreviousInput;      /* '<S58>/Memory' */
  boolean_T Memory_PreviousInput_n;    /* '<S59>/Memory' */
  boolean_T Memory_PreviousInput_f;    /* '<S53>/Memory' */
  boolean_T Memory_PreviousInput_j;    /* '<S39>/Memory' */
  boolean_T Memory_PreviousInput_fu;   /* '<S40>/Memory' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T U_DC;                         /* '<Root>/U_DC' */
  real_T I_uvw[3];                     /* '<Root>/I_uvw' */
  real_T Idq_Ref;                      /* '<Root>/Idq_Ref' */
  real_T Phi_raw;                      /* '<Root>/Phi_raw' */
  real_T n_Ref_i;                      /* '<Root>/n_Ref' */
  real_T Enable;                       /* '<Root>/Enable' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T DutyCycles[3];                /* '<Root>/DutyCycles' */
  real_T Idq_Act[2];                   /* '<Root>/Idq_Act' */
  real_T ModInd;                       /* '<Root>/ModInd' */
  real_T w_el_j;                       /* '<Root>/w_el' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T CompareToConstant_const;     /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S7>/Constant'
                                       */
  real_T CompareToConstant_const_e; /* Mask Parameter: CompareToConstant_const_e
                                     * Referenced by: '<S50>/Constant'
                                     */
  real_T AntiWindupGT_d_const;         /* Mask Parameter: AntiWindupGT_d_const
                                        * Referenced by: '<S33>/Constant'
                                        */
  real_T AntiWindupGT_q_const;         /* Mask Parameter: AntiWindupGT_q_const
                                        * Referenced by: '<S34>/Constant'
                                        */
  real_T CompareToConstant_const_j; /* Mask Parameter: CompareToConstant_const_j
                                     * Referenced by: '<S47>/Constant'
                                     */
  boolean_T SRFlipFlop_initial_condition;
                                 /* Mask Parameter: SRFlipFlop_initial_condition
                                  * Referenced by: '<S58>/Memory'
                                  */
  boolean_T SRFlipFlop1_initial_condition;
                                /* Mask Parameter: SRFlipFlop1_initial_condition
                                 * Referenced by: '<S59>/Memory'
                                 */
  boolean_T SRFlipFlop_initial_condition_d;
                               /* Mask Parameter: SRFlipFlop_initial_condition_d
                                * Referenced by: '<S53>/Memory'
                                */
  boolean_T If_Start_over_initial_condition;
                              /* Mask Parameter: If_Start_over_initial_condition
                               * Referenced by: '<S39>/Memory'
                               */
  boolean_T If_Start_over1_initial_conditio;
                              /* Mask Parameter: If_Start_over1_initial_conditio
                               * Referenced by: '<S40>/Memory'
                               */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S57>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_c;
                                   /* Mask Parameter: DetectRisePositive_vinit_c
                                    * Referenced by: '<S52>/Delay Input1'
                                    */
  real_T AKS_LS_Value[3];              /* Expression: [0 0 0]
                                        * Referenced by: '<S3>/AKS_LS'
                                        */
  real_T AKS_HS_Value[3];              /* Expression: [1 1 1]
                                        * Referenced by: '<S3>/AKS_HS'
                                        */
  real_T AKS_LSHS_Value[3];            /* Expression: [0.5 0.5 0.5]
                                        * Referenced by: '<S3>/AKS_LSHS'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S16>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 2*pi
                                        * Referenced by: '<S16>/Constant3'
                                        */
  real_T Constant1_Value;              /* Expression: -2*pi
                                        * Referenced by: '<S16>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S16>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: 2*pi
                                        * Referenced by: '<S17>/Constant'
                                        */
  real_T Bias_Bias;                    /* Expression: -2*pi
                                        * Referenced by: '<S19>/Bias'
                                        */
  real_T Constant1_Value_n;            /* Expression: 1
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Constant2_Value_a;            /* Expression: -1
                                        * Referenced by: '<S4>/Constant2'
                                        */
  real_T Constant5_Value;              /* Expression: -2*pi
                                        * Referenced by: '<S26>/Constant5'
                                        */
  real_T Constant6_Value;              /* Expression: 0
                                        * Referenced by: '<S26>/Constant6'
                                        */
  real_T Constant2_Value_b;            /* Expression: 2*pi
                                        * Referenced by: '<S26>/Constant2'
                                        */
  real_T Constant4_Value;              /* Expression: 0
                                        * Referenced by: '<S26>/Constant4'
                                        */
  real_T Constant_Value_c;             /* Expression: 2*pi
                                        * Referenced by: '<S24>/Constant'
                                        */
  real_T Constant1_Value_d;            /* Expression: 2*pi
                                        * Referenced by: '<S24>/Constant1'
                                        */
  real_T Constant_Value_l;             /* Expression: 2*pi
                                        * Referenced by: '<S25>/Constant'
                                        */
  real_T Constant1_Value_m;            /* Expression: 2*pi
                                        * Referenced by: '<S25>/Constant1'
                                        */
  real_T IntegStopSwitch3_Threshold;   /* Expression: 0
                                        * Referenced by: '<S32>/IntegStopSwitch3'
                                        */
  real_T Gain_Gain;                    /* Expression: 1
                                        * Referenced by: '<S36>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S36>/Gain1'
                                        */
  real_T DiscreteFIRFilter20thorder1_Ini;/* Expression: 0
                                          * Referenced by: '<S36>/Discrete FIR Filter 20th order1'
                                          */
  real_T DiscreteFIRFilter20thorder1_Coe[20];
                   /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
                    * Referenced by: '<S36>/Discrete FIR Filter 20th order1'
                    */
  real_T Gain3_Gain;                   /* Expression: 1
                                        * Referenced by: '<S36>/Gain3'
                                        */
  real_T DiscreteFIRFilter20thorder_Init;/* Expression: 0
                                          * Referenced by: '<S36>/Discrete FIR Filter 20th order'
                                          */
  real_T DiscreteFIRFilter20thorder_Coef[20];
                   /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
                    * Referenced by: '<S36>/Discrete FIR Filter 20th order'
                    */
  real_T Gain2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S36>/Gain2'
                                        */
  real_T Constant1_Value_o;            /* Expression: 0.5
                                        * Referenced by: '<S37>/Constant1'
                                        */
  real_T Constant1_Value_p;            /* Expression: 0
                                        * Referenced by: '<S41>/Constant1'
                                        */
  real_T Constant1_Value_l;            /* Expression: 0
                                        * Referenced by: '<S48>/Constant1'
                                        */
  real_T Constant1_Value_c;            /* Expression: 0
                                        * Referenced by: '<S49>/Constant1'
                                        */
  real_T Gain1_Gain_c;                 /* Expression: 2*pi
                                        * Referenced by: '<S45>/Gain1'
                                        */
  real_T Constant1_Value_lx;           /* Expression: 0
                                        * Referenced by: '<S45>/Constant1'
                                        */
  real_T Constant1_Value_e;            /* Expression: 0
                                        * Referenced by: '<S46>/Constant1'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * Referenced by: '<S42>/Constant'
                                        */
  real_T limitT3_UpperSat;             /* Expression: 0
                                        * Referenced by: '<S14>/limit T3'
                                        */
  real_T V_R_Scheduling_tableData[5];  /* Expression: V_R_n.z
                                        * Referenced by: '<S14>/V_R_Scheduling'
                                        */
  real_T V_R_Scheduling_bp01Data[5];   /* Expression: V_R_n.x1
                                        * Referenced by: '<S14>/V_R_Scheduling'
                                        */
  real_T Constant7_Value;              /* Expression: 0
                                        * Referenced by: '<S14>/Constant7'
                                        */
  real_T Switch_Threshold;             /* Expression: 15e3
                                        * Referenced by: '<S14>/Switch'
                                        */
  real_T calc_TorqueRef_Value;         /* Expression: EMotor.par.k_T.z
                                        * Referenced by: '<S14>/calc_TorqueRef'
                                        */
  real_T Gain3_Gain_f;                 /* Expression: 1/sqrt(2)
                                        * Referenced by: '<S14>/Gain3'
                                        */
  real_T Id_Mn_LUT_tableData[400];     /* Expression: EMotor.FEM_data.Id_Mn.z
                                        * Referenced by: '<S14>/Id_Mn_LUT'
                                        */
  real_T Id_Mn_LUT_bp01Data[20];       /* Expression: EMotor.FEM_data.Id_Mn.x2
                                        * Referenced by: '<S14>/Id_Mn_LUT'
                                        */
  real_T Id_Mn_LUT_bp02Data[20];       /* Expression: EMotor.FEM_data.Id_Mn.x1
                                        * Referenced by: '<S14>/Id_Mn_LUT'
                                        */
  real_T Constant13_Value;             /* Expression: 0
                                        * Referenced by: '<S14>/Constant13'
                                        */
  real_T Switch2_Threshold;            /* Expression: 15e3
                                        * Referenced by: '<S14>/Switch2'
                                        */
  real_T IdRefZero1_Value;             /* Expression: 0
                                        * Referenced by: '<S14>/IdRefZero1'
                                        */
  real_T IdqRefZero_Value[2];          /* Expression: [0 0]
                                        * Referenced by: '<S14>/IdqRefZero'
                                        */
  real_T RMSTorqueconstant_Value;      /* Expression: EMotor.par.k_T.z
                                        * Referenced by: '<S14>/RMS Torque constant'
                                        */
  real_T Gain2_Gain_b;                 /* Expression: sqrt(2)
                                        * Referenced by: '<S14>/Gain2'
                                        */
  real_T limitT1_LowerSat;             /* Expression: 0
                                        * Referenced by: '<S14>/limit T1'
                                        */
  real_T Switch2_Threshold_c;          /* Expression: 0
                                        * Referenced by: '<S61>/Switch2'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S14>/Unit Delay'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S14>/Switch1'
                                        */
  real_T Constant3_Value_i;            /* Expression: 0.0001
                                        * Referenced by: '<S14>/Constant3'
                                        */
  real_T dummy_gain5_Gain;             /* Expression: 1
                                        * Referenced by: '<S14>/dummy_gain5'
                                        */
  real_T dummy_gain1_Gain;             /* Expression: 1
                                        * Referenced by: '<S14>/dummy_gain1'
                                        */
  real_T dummy_gain3_Gain;             /* Expression: 1
                                        * Referenced by: '<S14>/dummy_gain3'
                                        */
  real_T dummy_gain2_Gain;             /* Expression: 1
                                        * Referenced by: '<S14>/dummy_gain2'
                                        */
  real_T Null_Value[3];                /* Expression: [0;0;0]
                                        * Referenced by: '<S2>/Null'
                                        */
  real_T Zero_Value;                   /* Expression: 0
                                        * Referenced by: '<S32>/Zero'
                                        */
  real_T Constant_Value_g;             /* Expression: 1
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: 2*pi
                                        * Referenced by: '<S66>/Gain1'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * Referenced by: '<S66>/Constant1'
                                        */
  real_T DutyCycles_OUT_Y0;            /* Computed Parameter: DutyCycles_OUT_Y0
                                        * Referenced by: '<S2>/DutyCycles_OUT'
                                        */
  real_T ModInd_Y0;                    /* Computed Parameter: ModInd_Y0
                                        * Referenced by: '<S2>/ModInd'
                                        */
  real_T Idq_Y0;                       /* Computed Parameter: Idq_Y0
                                        * Referenced by: '<S2>/Idq'
                                        */
  real_T w_el_Y0;                      /* Computed Parameter: w_el_Y0
                                        * Referenced by: '<S2>/w_el'
                                        */
  real_T Constant_Value_j;             /* Expression: 0
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Constant_Value_n;             /* Expression: 0
                                        * Referenced by: '<S54>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: 0
                                        * Referenced by: '<S60>/Constant'
                                        */
  real_T Switch1_Threshold_e;          /* Expression: 0
                                        * Referenced by: '<S2>/Switch1'
                                        */
  real_T DiscreteTransferFcn_NumCoef;  /* Expression: [1-0.995]
                                        * Referenced by: '<S15>/Discrete Transfer Fcn'
                                        */
  real_T DiscreteTransferFcn_DenCoef[2];/* Expression: [1 -0.995]
                                         * Referenced by: '<S15>/Discrete Transfer Fcn'
                                         */
  real_T DiscreteTransferFcn_InitialStat;/* Expression: 0
                                          * Referenced by: '<S15>/Discrete Transfer Fcn'
                                          */
  real_T f_2_w_el_Gain;                /* Expression: 2*pi
                                        * Referenced by: '<S15>/f_2_w_el'
                                        */
  real_T UnitDelay_InitialCondition_o; /* Expression: 0
                                        * Referenced by: '<S66>/Unit Delay'
                                        */
  real_T TrafoMatrixuvwalphabeta_Gain[6];
                         /* Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3
                          * Referenced by: '<S30>/TrafoMatrix uvw->alphabeta'
                          */
  real_T Constant2_Value_l;            /* Expression: 1
                                        * Referenced by: '<S46>/Constant2'
                                        */
  real_T UnitDelay_InitialCondition_i; /* Expression: 0
                                        * Referenced by: '<S46>/Unit Delay'
                                        */
  real_T Constant2_Value_e;            /* Expression: 1
                                        * Referenced by: '<S49>/Constant2'
                                        */
  real_T UnitDelay_InitialCondition_i2;/* Expression: 0
                                        * Referenced by: '<S49>/Unit Delay'
                                        */
  real_T ResolverOffsetLimitation_UpperS;/* Expression: 2*pi
                                          * Referenced by: '<S5>/ResolverOffsetLimitation'
                                          */
  real_T ResolverOffsetLimitation_LowerS;/* Expression: 0
                                          * Referenced by: '<S5>/ResolverOffsetLimitation'
                                          */
  real_T Switch_Phi_Threshold;         /* Expression: 0
                                        * Referenced by: '<S17>/Switch_Phi'
                                        */
  real_T UnitDelay_InitialCondition_l; /* Expression: 0
                                        * Referenced by: '<S18>/Unit Delay'
                                        */
  real_T DiscreteTransferFcn_NumCoef_o[2];/* Expression: [1 -1]
                                           * Referenced by: '<S19>/Discrete Transfer Fcn'
                                           */
  real_T DiscreteTransferFcn_DenCoef_c[2];/* Expression: [1 0]
                                           * Referenced by: '<S19>/Discrete Transfer Fcn'
                                           */
  real_T DiscreteTransferFcn_InitialSt_i;/* Expression: 0
                                          * Referenced by: '<S19>/Discrete Transfer Fcn'
                                          */
  real_T Constant_Value_lr;            /* Expression: 3/2*pi
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Constant1_Value_jc;           /* Expression: 1/2*pi
                                        * Referenced by: '<S19>/Constant1'
                                        */
  real_T Constant2_Value_k;            /* Expression: pi
                                        * Referenced by: '<S19>/Constant2'
                                        */
  real_T DiscreteTransferFcn1_NumCoef[2];/* Expression: [1 -1]
                                          * Referenced by: '<S19>/Discrete Transfer Fcn1'
                                          */
  real_T DiscreteTransferFcn1_DenCoef[2];/* Expression: [1 0]
                                          * Referenced by: '<S19>/Discrete Transfer Fcn1'
                                          */
  real_T DiscreteTransferFcn1_InitialSta;/* Expression: 0
                                          * Referenced by: '<S19>/Discrete Transfer Fcn1'
                                          */
  real_T Switch2_Threshold_p;          /* Expression: 0
                                        * Referenced by: '<S4>/Switch2'
                                        */
  real_T Switch_Threshold_c;           /* Expression: 0
                                        * Referenced by: '<S4>/Switch'
                                        */
  real_T Constant_Value_mh;            /* Expression: pi/2
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Switch2_Threshold_f;          /* Expression: 2*pi
                                        * Referenced by: '<S16>/Switch2'
                                        */
  real_T Switch1_Threshold_o;          /* Expression: 0
                                        * Referenced by: '<S16>/Switch1'
                                        */
  real_T UnitDelay_InitialCondition_lk;/* Expression: 0
                                        * Referenced by: '<S26>/Unit Delay'
                                        */
  real_T Constant3_Value_d;            /* Expression: -pi
                                        * Referenced by: '<S26>/Constant3'
                                        */
  real_T Constant1_Value_k;            /* Expression: pi
                                        * Referenced by: '<S26>/Constant1'
                                        */
  real_T UnitDelay3_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S23>/Unit Delay3'
                                        */
  real_T Switch1_Threshold_n;          /* Expression: 2*pi
                                        * Referenced by: '<S24>/Switch1'
                                        */
  real_T Switch2_Threshold_a;          /* Expression: 0
                                        * Referenced by: '<S24>/Switch2'
                                        */
  real_T UnitDelay_InitialCondition_d; /* Expression: 0
                                        * Referenced by: '<S45>/Unit Delay'
                                        */
  real_T Constant2_Value_bl;           /* Expression: 1
                                        * Referenced by: '<S48>/Constant2'
                                        */
  real_T UnitDelay_InitialCondition_h; /* Expression: 0
                                        * Referenced by: '<S48>/Unit Delay'
                                        */
  real_T IntegDelay1_InitialCondition; /* Expression: 0
                                        * Referenced by: '<S32>/IntegDelay1'
                                        */
  real_T Switch1_Threshold_ep;         /* Expression: 2*pi
                                        * Referenced by: '<S25>/Switch1'
                                        */
  real_T Switch2_Threshold_h;          /* Expression: 0
                                        * Referenced by: '<S25>/Switch2'
                                        */
  real_T Gain1_Gain_g;                 /* Expression: 1
                                        * Referenced by: '<S38>/Gain1'
                                        */
  real_T Gain3_Gain_k;                 /* Expression: -0.5
                                        * Referenced by: '<S38>/Gain3'
                                        */
  real_T Gain4_Gain;                   /* Expression: sqrt(3)/2
                                        * Referenced by: '<S38>/Gain4'
                                        */
  real_T Gain2_Gain_m;                 /* Expression: 1
                                        * Referenced by: '<S38>/Gain2'
                                        */
  real_T Gain5_Gain;                   /* Expression: 1
                                        * Referenced by: '<S38>/Gain5'
                                        */
  real_T avoid_div_by_0_Value;         /* Expression: 1
                                        * Referenced by: '<S9>/avoid_div_by_0'
                                        */
  real_T U_DC_half_Value;              /* Expression: 2
                                        * Referenced by: '<S9>/U_DC_half'
                                        */
  real_T Switch_Threshold_o;           /* Expression: 0
                                        * Referenced by: '<S9>/Switch'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1
                                        * Referenced by: '<S35>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S35>/Saturation'
                                        */
  real_T AKS_Switch_Threshold;         /* Expression: 1
                                        * Referenced by: '<S3>/AKS_Switch'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S20>/Unit Delay1'
                                        */
  real_T Switch4_Threshold;            /* Expression: 0.5
                                        * Referenced by: '<S20>/Switch4'
                                        */
  real_T UnitDelay_InitialCondition_h3;/* Expression: 0
                                        * Referenced by: '<S20>/Unit Delay'
                                        */
  real_T Switch3_Threshold;            /* Expression: 0.5
                                        * Referenced by: '<S20>/Switch3'
                                        */
  real_T Zero1_Value[2];               /* Expression: [0,0]
                                        * Referenced by: '<S32>/Zero1'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: 1
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T Gain1_Gain_n;                 /* Expression: 1
                                        * Referenced by: '<S35>/Gain1'
                                        */
  real_T Gain2_Gain_o;                 /* Expression: 1
                                        * Referenced by: '<S35>/Gain2'
                                        */
  real_T Gain3_Gain_h;                 /* Expression: 1
                                        * Referenced by: '<S35>/Gain3'
                                        */
  real_T dummy_gain2_Gain_e;           /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain2'
                                        */
  real_T dummy_Gain;                   /* Expression: 1
                                        * Referenced by: '<S32>/dummy'
                                        */
  real_T dummy1_Gain;                  /* Expression: 1
                                        * Referenced by: '<S32>/dummy1'
                                        */
  real_T PsiReduceGain3_Gain;          /* Expression: 1
                                        * Referenced by: '<S6>/PsiReduceGain3'
                                        */
  real_T PsiReduceGain4_Gain;          /* Expression: 1
                                        * Referenced by: '<S6>/PsiReduceGain4'
                                        */
  real_T Constant2_Value_lu;           /* Expression: 1
                                        * Referenced by: '<S41>/Constant2'
                                        */
  real_T UnitDelay_InitialCondition_f; /* Expression: 0
                                        * Referenced by: '<S41>/Unit Delay'
                                        */
  real_T Switch_Threshold_b;           /* Expression: 0
                                        * Referenced by: '<S41>/Switch'
                                        */
  real_T DiscreteFIRFilter20thorder1_I_j;/* Expression: 0
                                          * Referenced by: '<S30>/Discrete FIR Filter 20th order1'
                                          */
  real_T DiscreteFIRFilter20thorder1_C_l[20];
                   /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
                    * Referenced by: '<S30>/Discrete FIR Filter 20th order1'
                    */
  real_T Gain6_Gain;                   /* Expression: 1
                                        * Referenced by: '<S30>/Gain6'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: 1
                                        * Referenced by: '<S30>/Gain1'
                                        */
  real_T DiscreteFIRFilter20thorder_In_a;/* Expression: 0
                                          * Referenced by: '<S30>/Discrete FIR Filter 20th order'
                                          */
  real_T DiscreteFIRFilter20thorder_Co_l[20];
                   /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
                    * Referenced by: '<S30>/Discrete FIR Filter 20th order'
                    */
  real_T Gain5_Gain_j;                 /* Expression: 1
                                        * Referenced by: '<S30>/Gain5'
                                        */
  real_T Gain_Gain_g;                  /* Expression: 1
                                        * Referenced by: '<S30>/Gain'
                                        */
  real_T Switch_Threshold_i;           /* Expression: 2*pi
                                        * Referenced by: '<S45>/Switch'
                                        */
  real_T dummy_gain4_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain4'
                                        */
  real_T dummy_gain1_Gain_j;           /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain1'
                                        */
  real_T Gain_Gain_gk;                 /* Expression: 2
                                        * Referenced by: '<S23>/Gain'
                                        */
  real_T UnitDelay1_InitialCondition_c;/* Expression: 0
                                        * Referenced by: '<S28>/Unit Delay1'
                                        */
  real_T dummy_gain5_Gain_j;           /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain5'
                                        */
  real_T Constant_Value_d;             /* Expression: 1
                                        * Referenced by: '<S18>/Constant'
                                        */
  real_T Gain2_Gain_k;                 /* Expression: 1
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real_T Gain3_Gain_b;                 /* Expression: 1
                                        * Referenced by: '<S4>/Gain3'
                                        */
  real_T Gain4_Gain_j;                 /* Expression: 1
                                        * Referenced by: '<S4>/Gain4'
                                        */
  real_T dummy_gain_Gain;              /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain'
                                        */
  real_T Switch_Threshold_k;           /* Expression: 0
                                        * Referenced by: '<S46>/Switch'
                                        */
  real_T Switch_Threshold_ks;          /* Expression: 2*pi
                                        * Referenced by: '<S66>/Switch'
                                        */
  real_T Gain2_Gain_h;                 /* Expression: 1
                                        * Referenced by: '<S30>/Gain2'
                                        */
  real_T Gain3_Gain_l;                 /* Expression: 1
                                        * Referenced by: '<S30>/Gain3'
                                        */
  real_T Gain4_Gain_g;                 /* Expression: 1
                                        * Referenced by: '<S30>/Gain4'
                                        */
  real32_T Constant5_Value_m;          /* Computed Parameter: Constant5_Value_m
                                        * Referenced by: '<S35>/Constant5'
                                        */
  real32_T Constant4_Value_i;          /* Computed Parameter: Constant4_Value_i
                                        * Referenced by: '<S35>/Constant4'
                                        */
  real32_T Gain1_Gain_m;               /* Computed Parameter: Gain1_Gain_m
                                        * Referenced by: '<S11>/Gain1'
                                        */
  real32_T Gain2_Gain_a;               /* Computed Parameter: Gain2_Gain_a
                                        * Referenced by: '<S12>/Gain2'
                                        */
  real32_T Gain1_Gain_mo;              /* Computed Parameter: Gain1_Gain_mo
                                        * Referenced by: '<S12>/Gain1'
                                        */
  uint32_T Id_Mn_LUT_maxIndex[2];      /* Computed Parameter: Id_Mn_LUT_maxIndex
                                        * Referenced by: '<S14>/Id_Mn_LUT'
                                        */
  boolean_T Constant2_Value_o;         /* Computed Parameter: Constant2_Value_o
                                        * Referenced by: '<S11>/Constant2'
                                        */
  boolean_T Constant1_Value_g;         /* Computed Parameter: Constant1_Value_g
                                        * Referenced by: '<S11>/Constant1'
                                        */
  boolean_T Constant3_Value_f;         /* Computed Parameter: Constant3_Value_f
                                        * Referenced by: '<S12>/Constant3'
                                        */
  boolean_T Constant1_Value_jr;        /* Computed Parameter: Constant1_Value_jr
                                        * Referenced by: '<S12>/Constant1'
                                        */
  boolean_T Constant2_Value_j;         /* Computed Parameter: Constant2_Value_j
                                        * Referenced by: '<S12>/Constant2'
                                        */
  boolean_T Constant4_Value_c;         /* Computed Parameter: Constant4_Value_c
                                        * Referenced by: '<S12>/Constant4'
                                        */
  boolean_T Logic_table[16];           /* Computed Parameter: Logic_table
                                        * Referenced by: '<S58>/Logic'
                                        */
  boolean_T Logic_table_c[16];         /* Computed Parameter: Logic_table_c
                                        * Referenced by: '<S59>/Logic'
                                        */
  boolean_T Logic_table_k[16];         /* Computed Parameter: Logic_table_k
                                        * Referenced by: '<S53>/Logic'
                                        */
  boolean_T UnitDelay_InitialCondition_hp;
                            /* Computed Parameter: UnitDelay_InitialCondition_hp
                             * Referenced by: '<S44>/Unit Delay'
                             */
  boolean_T Logic_table_kz[16];        /* Computed Parameter: Logic_table_kz
                                        * Referenced by: '<S39>/Logic'
                                        */
  boolean_T Logic_table_l[16];         /* Computed Parameter: Logic_table_l
                                        * Referenced by: '<S40>/Logic'
                                        */
  uint8_T dummy_gain5_Gain_m;          /* Computed Parameter: dummy_gain5_Gain_m
                                        * Referenced by: '<S10>/dummy_gain5'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T FOC_U_DC;                /* '<S2>/Switch1' */
extern real_T FOC_Mode_after_checks;   /* '<S2>/Switch' */
extern real_T Phi_Observer;            /* '<S23>/Sum7' */
extern real_T U_u;                     /* '<S38>/Gain1' */
extern real_T U_v;                     /* '<S38>/Gain2' */
extern real_T U_w;                     /* '<S38>/Gain5' */
extern real_T Mod_Index;               /* '<S9>/Gain1' */
extern real_T duty_cycle_u;            /* '<S35>/Gain1' */
extern real_T duty_cycle_v;            /* '<S35>/Gain2' */
extern real_T duty_cycle_w;            /* '<S35>/Gain3' */
extern real_T Phi_el_U_Transformation; /* '<S5>/dummy_gain2' */
extern real_T u_d_Integrator;          /* '<S32>/dummy' */
extern real_T u_q_Integrator;          /* '<S32>/dummy1' */
extern real_T I_d_Ref;                 /* '<S6>/PsiReduceGain3' */
extern real_T I_q_Ref;                 /* '<S6>/PsiReduceGain4' */
extern real_T I_q_Act_filt;            /* '<S30>/Gain6' */
extern real_T I_q_Act;                 /* '<S30>/Gain1' */
extern real_T I_d_Act_filt;            /* '<S30>/Gain5' */
extern real_T I_d_Act;                 /* '<S30>/Gain' */
extern real_T Phi_est_error_I_Trafo;   /* '<S5>/dummy_gain4' */
extern real_T Phi_el_I_Transformation; /* '<S5>/dummy_gain1' */
extern real_T Phi_est;                 /* '<S5>/dummy_gain5' */
extern real_T FOC_AngleEst_w_el;       /* '<S4>/Gain2' */
extern real_T FOC_AngleEst_Psi_PM_alpha;/* '<S4>/Gain3' */
extern real_T FOC_AngleEst_Psi_PM_beta;/* '<S4>/Gain4' */
extern real_T IfStarter_process_finished;/* '<S10>/dummy_gain5' */
extern real_T w_el;                    /* '<S5>/dummy_gain' */
extern real_T I_u;                     /* '<S30>/Gain2' */
extern real_T I_v;                     /* '<S30>/Gain3' */
extern real_T I_w;                     /* '<S30>/Gain4' */
extern real_T n_Ref;                   /* '<S61>/Switch2' */
extern real_T SPEED_CTRL_w_el_err;     /* '<S14>/Add' */
extern real_T n_Act;                   /* '<S14>/RPM => w_el1' */
extern real_T SPEED_CTRL_Iq_Ref;       /* '<S14>/dummy_gain5' */
extern real_T SPEED_CTRL_Integ;        /* '<S14>/dummy_gain1' */
extern real_T SPEED_CTRL_Prop;         /* '<S14>/dummy_gain3' */
extern real_T SPEED_CTRL_enable;       /* '<S14>/dummy_gain2' */
extern real_T u_d;                     /* '<S36>/Gain' */
extern real_T u_q;                     /* '<S36>/Gain1' */
extern real_T u_beta;                  /* '<S36>/Add' */
extern real_T u_alpha;                 /* '<S36>/Subtract' */
extern real_T u_q_filt;                /* '<S36>/Gain3' */
extern real_T u_d_filt;                /* '<S36>/Gain2' */
extern real32_T FOC_Overcurrent_I_uvw; /* '<S11>/Gain1' */
extern real32_T FOC_Overvoltage_U_DC;  /* '<S12>/Gain2' */
extern real32_T FOC_Undervoltage_U_DC; /* '<S12>/Gain1' */
extern boolean_T i_d_IntegNotStopped;  /* '<S31>/AntiWindupOR_d' */
extern boolean_T i_q_IntegNotStopped;  /* '<S31>/AntiWindupOR_q' */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T FOC_AKS_Mode;            /* Variable: FOC_AKS_Mode
                                        * Referenced by: '<S3>/FOC_AKS_Mode'
                                        */
extern real_T FOC_AngleEst_Delay1;     /* Variable: FOC_AngleEst_Delay1
                                        * Referenced by: '<S20>/FOC_AngleEst_Delay1'
                                        */
extern real_T FOC_AngleEst_Delay2;     /* Variable: FOC_AngleEst_Delay2
                                        * Referenced by: '<S20>/FOC_AngleEst_Delay2'
                                        */
extern real_T FOC_AngleEst_Komp_KP;    /* Variable: FOC_AngleEst_Komp_KP
                                        * Referenced by: '<S4>/komp_kp'
                                        */
extern real_T FOC_AngleEst_Lq;         /* Variable: FOC_AngleEst_Lq
                                        * Referenced by: '<S4>/FOC_AngleEst_Lq'
                                        */
extern real_T FOC_AngleEst_Psi_InitVal;/* Variable: FOC_AngleEst_Psi_InitVal
                                        * Referenced by: '<S21>/Unit Delay'
                                        */
extern real_T FOC_AngleEst_Rs;         /* Variable: FOC_AngleEst_Rs
                                        * Referenced by: '<S4>/FOC_AngleEst_Rs'
                                        */
extern real_T FOC_AngleEst_w_el_filtered_Tau;
                                     /* Variable: FOC_AngleEst_w_el_filtered_Tau
                                      * Referenced by: '<S18>/Tau'
                                      */
extern real_T FOC_AngleObs_w_InitVal;  /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S27>/Unit Delay1'
                                        */
extern real_T FOC_AngleObserver_D;     /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S23>/Constant1'
                                        */
extern real_T FOC_AngleObserver_w0;    /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S23>/Constant'
                                        */
extern real_T FOC_ENABLE_IfStarter;    /* Variable: FOC_ENABLE_IfStarter
                                        * Referenced by: '<S10>/Enable_If_Starter'
                                        */
extern real_T FOC_ENABLE_Overcurrent_I_uvw;/* Variable: FOC_ENABLE_Overcurrent_I_uvw
                                            * Referenced by: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
                                            */
extern real_T FOC_ENABLE_Overvoltage_U_DC;/* Variable: FOC_ENABLE_Overvoltage_U_DC
                                           * Referenced by: '<S12>/FOC_ENABLE_Overvoltage_U_DC1'
                                           */
extern real_T FOC_ENABLE_Undervoltage_U_DC;/* Variable: FOC_ENABLE_Undervoltage_U_DC
                                            * Referenced by: '<S12>/FOC_ENABLE_Undervoltage_U_DC1'
                                            */
extern real_T FOC_Enable;              /* Variable: FOC_Enable
                                        * Referenced by: '<S2>/Enable'
                                        */
extern real_T FOC_Id_Ref_constFW_factor;/* Variable: FOC_Id_Ref_constFW_factor
                                         * Referenced by: '<S14>/Constant10'
                                         */
extern real_T FOC_Id_Ref_constFW_offset;/* Variable: FOC_Id_Ref_constFW_offset
                                         * Referenced by: '<S14>/Constant11'
                                         */
extern real_T FOC_IfStarter_Delta_w;   /* Variable: FOC_IfStarter_Delta_w
                                        * Referenced by: '<S10>/Delta_w'
                                        */
extern real_T FOC_IfStarter_Id_Ref;    /* Variable: FOC_IfStarter_Id_Ref
                                        * Referenced by: '<S10>/I_d_Ref'
                                        */
extern real_T FOC_IfStarter_T_Id_Ramp; /* Variable: FOC_IfStarter_T_Id_Ramp
                                        * Referenced by: '<S10>/T_Id_Ramp'
                                        */
extern real_T FOC_IfStarter_T_switch;  /* Variable: FOC_IfStarter_T_switch
                                        * Referenced by: '<S10>/T_switch'
                                        */
extern real_T FOC_IfStarter_T_w_Ramp;  /* Variable: FOC_IfStarter_T_w_Ramp
                                        * Referenced by: '<S10>/T_w_Ramp'
                                        */
extern real_T FOC_IfStarter_T_w_Wait;  /* Variable: FOC_IfStarter_T_w_Wait
                                        * Referenced by: '<S10>/T_w_Wait'
                                        */
extern real_T FOC_IfStarter_Trigger;   /* Variable: FOC_IfStarter_Trigger
                                        * Referenced by: '<S2>/FOC_IfStarter_Trigger'
                                        */
extern real_T FOC_IfStarter_w_el_Ref;  /* Variable: FOC_IfStarter_w_el_Ref
                                        * Referenced by: '<S10>/w_el_Ref'
                                        */
extern real_T FOC_IfStarter_w_min_off; /* Variable: FOC_IfStarter_w_min_off
                                        * Referenced by: '<S10>/w_min_off'
                                        */
extern real_T FOC_IntegDamp;           /* Variable: FOC_IntegDamp
                                        * Referenced by: '<S32>/FOC_IntegDamp'
                                        */
extern real_T FOC_KI;                  /* Variable: FOC_KI
                                        * Referenced by: '<S32>/FOC_KI'
                                        */
extern real_T FOC_KP;                  /* Variable: FOC_KP
                                        * Referenced by: '<S32>/FOC_KP1'
                                        */
extern real_T FOC_LIMIT_I_PHASE_PEAK_MAX;/* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
                                          * Referenced by:
                                          *   '<S14>/limit T1'
                                          *   '<S14>/limit T3'
                                          */
extern real_T FOC_LIMIT_MAX_Id_Ref_constFW;/* Variable: FOC_LIMIT_MAX_Id_Ref_constFW
                                            * Referenced by: '<S14>/Constant8'
                                            */
extern real_T FOC_LIMIT_MIN_Id_Ref_constFW;/* Variable: FOC_LIMIT_MIN_Id_Ref_constFW
                                            * Referenced by: '<S14>/Constant9'
                                            */
extern real_T FOC_LIMIT_Overcurrent_I_uvw;/* Variable: FOC_LIMIT_Overcurrent_I_uvw
                                           * Referenced by: '<S51>/Constant'
                                           */
extern real_T FOC_LIMIT_Overvoltage_U_DC;/* Variable: FOC_LIMIT_Overvoltage_U_DC
                                          * Referenced by: '<S56>/Constant'
                                          */
extern real_T FOC_LIMIT_Undervoltage_U_DC;/* Variable: FOC_LIMIT_Undervoltage_U_DC
                                           * Referenced by: '<S55>/Constant'
                                           */
extern real_T FOC_LIMIT_n_Ref_SlewRate_Down;
                                      /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
                                       * Referenced by: '<S61>/Constant7'
                                       */
extern real_T FOC_LIMIT_n_Ref_SlewRate_InitVal;
                                   /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
                                    * Referenced by: '<S64>/Delay Input2'
                                    */
extern real_T FOC_LIMIT_n_Ref_SlewRate_Up;/* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
                                           * Referenced by: '<S61>/Constant6'
                                           */
extern real_T FOC_MANUAL_Id_Ref_SPEED_CTRL;/* Variable: FOC_MANUAL_Id_Ref_SPEED_CTRL
                                            * Referenced by: '<S14>/Constant6'
                                            */
extern real_T FOC_MANUAL_U_DC;         /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S2>/Udc1'
                                        */
extern real_T FOC_MaxModInd;           /* Variable: FOC_MaxModInd
                                        * Referenced by: '<S31>/FOC_MaxModInd'
                                        */
extern real_T FOC_Mode;                /* Variable: FOC_Mode
                                        * Referenced by: '<S2>/FOC_Mode'
                                        */
extern real_T FOC_OmegaObs3;           /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S23>/Gain4'
                                        */
extern real_T FOC_PhiSensorTdead;      /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S23>/DeadTimeCompensation'
                                        */
extern real_T FOC_RESET_OC_Error;      /* Variable: FOC_RESET_OC_Error
                                        * Referenced by: '<S11>/Reset_OC_Error'
                                        */
extern real_T FOC_RESET_OV_Error;      /* Variable: FOC_RESET_OV_Error
                                        * Referenced by: '<S12>/Reset_OV_Error'
                                        */
extern real_T FOC_SELECT_AngleEst_w_el_filtered;
                                  /* Variable: FOC_SELECT_AngleEst_w_el_filtered
                                   * Referenced by: '<S4>/useFilteredCorrection'
                                   */
extern real_T FOC_SELECT_Id_Ref_constFW;/* Variable: FOC_SELECT_Id_Ref_constFW
                                         * Referenced by: '<S14>/Constant12'
                                         */
extern real_T FOC_SELECT_Modulation;   /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S9>/modulation'
                                        */
extern real_T FOC_SELECT_Phase_Assignment_UVW;
                                    /* Variable: FOC_SELECT_Phase_Assignment_UVW
                                     * Referenced by: '<S13>/Selektierung Phase'
                                     */
extern real_T FOC_SELECT_U_DC_INPUT;   /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S2>/0: P_Udc 1: Udc_measured'
                                        */
extern real_T FOC_SELECT_n_Ref_Ramp;   /* Variable: FOC_SELECT_n_Ref_Ramp
                                        * Referenced by: '<S61>/Constant5'
                                        */
extern real_T FOC_SELECT_phi;          /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S5>/Constant3'
                                        */
extern real_T FOC_SELECT_speed_control;/* Variable: FOC_SELECT_speed_control
                                        * Referenced by: '<S2>/0: on // 1: off'
                                        */
extern real_T FOC_T_fast;              /* Variable: FOC_T_fast
                                        * Referenced by: '<S5>/Gain'
                                        */
extern real_T FOC_Uf_U_max;            /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S67>/Saturation1'
                                        */
extern real_T FOC_Uf_U_min;            /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S67>/Saturation1'
                                        */
extern real_T FOC_Uf_Ud;               /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S15>/Uf_Ud'
                                        */
extern real_T FOC_Uf_f_el;             /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S15>/Uf_w_el'
                                        */
extern real_T FOC_Uf_m;                /* Variable: FOC_Uf_m
                                        * Referenced by: '<S67>/Gain'
                                        */
extern real_T FOC_f_fastCTRL;          /* Variable: FOC_f_fastCTRL
                                        * Referenced by:
                                        *   '<S14>/FOC_T_fast'
                                        *   '<S18>/FOC_f_fast'
                                        *   '<S19>/FOC_f_fastCTRL'
                                        *   '<S19>/FOC_f_fastCTRL1'
                                        *   '<S21>/FOC_T_fast'
                                        *   '<S23>/FOC_T_fast'
                                        *   '<S41>/FOC_T_fast'
                                        *   '<S45>/FOC_T_fast'
                                        *   '<S46>/FOC_T_fast'
                                        *   '<S66>/FOC_T_fast'
                                        *   '<S27>/FOC_T_fast'
                                        *   '<S28>/FOC_T_fast'
                                        *   '<S32>/FOC_T_fast'
                                        *   '<S48>/FOC_T_fast'
                                        *   '<S49>/FOC_T_fast'
                                        *   '<S64>/FOC_T_fast'
                                        */
extern real_T FOC_output_trafo_delay;  /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S5>/Gain'
                                        */
extern real_T FOC_phi_offset;          /* Variable: FOC_phi_offset
                                        * Referenced by: '<S5>/Constant'
                                        */
extern real_T FOC_z_P;                 /* Variable: FOC_z_P
                                        * Referenced by:
                                        *   '<S14>/RPM => w_el'
                                        *   '<S14>/RPM => w_el1'
                                        */
extern real_T Factor_OmegaRot;         /* Variable: Factor_OmegaRot
                                        * Referenced by: '<S23>/Gain5'
                                        */
extern real_T SELECT_SPEED_CTRL_V_R;   /* Variable: SELECT_SPEED_CTRL_V_R
                                        * Referenced by: '<S14>/Constant15'
                                        */
extern real_T SPEED_CTRL_IQ_MAX;       /* Variable: SPEED_CTRL_IQ_MAX
                                        * Referenced by: '<S14>/Constant1'
                                        */
extern real_T SPEED_CTRL_IQ_MIN;       /* Variable: SPEED_CTRL_IQ_MIN
                                        * Referenced by: '<S14>/Constant2'
                                        */
extern real_T SPEED_CTRL_K_AWU;        /* Variable: SPEED_CTRL_K_AWU
                                        * Referenced by: '<S14>/Gain1'
                                        */
extern real_T SPEED_CTRL_LIMIT_n_Ref_MAX;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
                                          * Referenced by: '<S14>/limit T2'
                                          */
extern real_T SPEED_CTRL_LIMIT_n_Ref_MIN;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
                                          * Referenced by: '<S14>/limit T2'
                                          */
extern real_T SPEED_CTRL_MANUAL_n_RPM; /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S14>/OmegaRot2'
                                        */
extern real_T SPEED_CTRL_SELECT_IfStarter;/* Variable: SPEED_CTRL_SELECT_IfStarter
                                           * Referenced by: '<S2>/OmegaRot1'
                                           */
extern real_T SPEED_CTRL_SELECT_TorqLimit;/* Variable: SPEED_CTRL_SELECT_TorqLimit
                                           * Referenced by: '<S14>/OmegaRot3'
                                           */
extern real_T SPEED_CTRL_SELECT_n_Ref; /* Variable: SPEED_CTRL_SELECT_n_Ref
                                        * Referenced by: '<S14>/OmegaRot1'
                                        */
extern real_T SPEED_CTRL_TORQLIMNEG;   /* Variable: SPEED_CTRL_TORQLIMNEG
                                        * Referenced by: '<S14>/Constant5'
                                        */
extern real_T SPEED_CTRL_TORQLIMPOS;   /* Variable: SPEED_CTRL_TORQLIMPOS
                                        * Referenced by: '<S14>/Constant4'
                                        */
extern real_T SPEED_CTRL_T_N;          /* Variable: SPEED_CTRL_T_N
                                        * Referenced by: '<S14>/Constant'
                                        */
extern real_T SPEED_CTRL_V_R;          /* Variable: SPEED_CTRL_V_R
                                        * Referenced by: '<S14>/Constant14'
                                        */
extern real32_T FOC_SELECT_Voltage_Assignment_UVW;
                                  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
                                   * Referenced by: '<S35>/Constant6'
                                   */

/* Model entry point functions */
extern void FOC_CurrentControl_initialize(void);
extern void FOC_CurrentControl_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S19>/testo' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S64>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S65>/Data Type Duplicate' : Unused code path elimination
 * Block '<S65>/Data Type Propagation' : Unused code path elimination
 * Block '<S62>/Data Type Duplicate' : Unused code path elimination
 * Block '<S62>/Data Type Propagation' : Unused code path elimination
 * Block '<S63>/Data Type Duplicate' : Unused code path elimination
 * Block '<S63>/Data Type Propagation' : Unused code path elimination
 * Block '<S14>/Scope' : Unused code path elimination
 * Block '<S14>/Scope1' : Unused code path elimination
 * Block '<S14>/Scope2' : Unused code path elimination
 * Block '<S14>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * hilite_system('FOC_FastCTRL/FOC_CurrentControl')    - opens subsystem FOC_FastCTRL/FOC_CurrentControl
 * hilite_system('FOC_FastCTRL/FOC_CurrentControl/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FOC_FastCTRL'
 * '<S1>'   : 'FOC_FastCTRL/FOC_CurrentControl'
 * '<S2>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem'
 * '<S3>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AKS_Switch'
 * '<S4>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation'
 * '<S5>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption'
 * '<S6>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER'
 * '<S7>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Compare To Constant'
 * '<S8>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Compare To Zero'
 * '<S9>'   : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/FOC_VoltOutput'
 * '<S10>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter'
 * '<S11>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OC_Detection'
 * '<S12>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection'
 * '<S13>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Phase_Assignment'
 * '<S14>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/SPEED_CONTROLLER'
 * '<S15>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/U_f'
 * '<S16>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/2piFormatting'
 * '<S17>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/AngleCalculation'
 * '<S18>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/LowpassFilter'
 * '<S19>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/Subsystem2'
 * '<S20>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/delay'
 * '<S21>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/disc. Int.'
 * '<S22>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/AngleEstimation/disc. P'
 * '<S23>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption/AngleObserver'
 * '<S24>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption/Modulo2Pi'
 * '<S25>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption/Modulo2Pi_'
 * '<S26>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption/AngleObserver/2PiKorr'
 * '<S27>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption/AngleObserver/integrator'
 * '<S28>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/Angle_Adaption/AngleObserver/integrator1'
 * '<S29>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER/PI_CONTROLLER'
 * '<S30>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER/UVW_DQ'
 * '<S31>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER/PI_CONTROLLER/AntiWindup'
 * '<S32>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER/PI_CONTROLLER/FeedbackPI'
 * '<S33>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER/PI_CONTROLLER/AntiWindup/AntiWindupGT_d'
 * '<S34>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/CURRENT_CONTROLLER/PI_CONTROLLER/AntiWindup/AntiWindupGT_q'
 * '<S35>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/FOC_VoltOutput/Adjust_duty_cycle_range'
 * '<S36>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/FOC_VoltOutput/SubS_InversePark_dq_alpha_beta'
 * '<S37>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/FOC_VoltOutput/SubS_Modulation'
 * '<S38>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/FOC_VoltOutput/alpha_beta->abc'
 * '<S39>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/If_Start_over'
 * '<S40>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/If_Start_over1'
 * '<S41>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Process_Id_DC_Injection'
 * '<S42>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Process_Id_Ramp'
 * '<S43>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Process_w_el_Ramp'
 * '<S44>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Rising'
 * '<S45>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/SubS_2pi_Integrator'
 * '<S46>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/TimeOver_Integrator'
 * '<S47>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Process_Id_DC_Injection/Compare To Constant'
 * '<S48>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Process_Id_Ramp/Id_Integrator'
 * '<S49>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/Process_w_el_Ramp/w_Integrator'
 * '<S50>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/IfStarter/TimeOver_Integrator/Compare To Constant'
 * '<S51>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OC_Detection/Compare To Constant'
 * '<S52>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OC_Detection/Detect Rise Positive'
 * '<S53>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OC_Detection/S-R Flip-Flop'
 * '<S54>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OC_Detection/Detect Rise Positive/Positive'
 * '<S55>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection/Compare To Constant'
 * '<S56>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection/Compare To Constant1'
 * '<S57>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection/Detect Rise Positive'
 * '<S58>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection/S-R Flip-Flop'
 * '<S59>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection/S-R Flip-Flop1'
 * '<S60>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/OV_UV_Detection/Detect Rise Positive/Positive'
 * '<S61>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/SPEED_CONTROLLER/Limit_n_Ref_SlewRate'
 * '<S62>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/SPEED_CONTROLLER/Saturation Dynamic'
 * '<S63>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/SPEED_CONTROLLER/Saturation Dynamic1'
 * '<S64>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/SPEED_CONTROLLER/Limit_n_Ref_SlewRate/RateLimiterDynamic'
 * '<S65>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/SPEED_CONTROLLER/Limit_n_Ref_SlewRate/RateLimiterDynamic/Saturation Dynamic'
 * '<S66>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/U_f/SubS_2pi_Integrator'
 * '<S67>'  : 'FOC_FastCTRL/FOC_CurrentControl/Subsystem/U_f/UfKennlinie'
 */
#endif                                 /* RTW_HEADER_FOC_CurrentControl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
