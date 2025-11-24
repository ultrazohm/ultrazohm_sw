/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.h
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Nov 24 14:15:51 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_FCF_h_
#define FOC_FCF_h_
#ifndef FOC_FCF_COMMON_INCLUDES_
#define FOC_FCF_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* FOC_FCF_COMMON_INCLUDES_ */

#include "FOC_FCF_types.h"
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
  real_T FOC_Mode_after_checks;        /* '<S1>/Switch' */
  real32_T U_DC_fcf;                   /* '<S1>/Switch1' */
  real32_T Abs[6];                     /* '<S6>/Abs' */
  real32_T MinMax;                     /* '<S6>/MinMax' */
  real32_T DiscreteTransferFcn;        /* '<S9>/Discrete Transfer Fcn' */
  real32_T f_2_w_el;                   /* '<S9>/f_2_w_el' */
  real32_T Product;                    /* '<S39>/Product' */
  real32_T UnitDelay;                  /* '<S39>/Unit Delay' */
  real32_T Add;                        /* '<S39>/Add' */
  real32_T TrafoMatrixuvwalphabeta[2]; /* '<S19>/TrafoMatrix uvw->alphabeta' */
  real32_T ResolverOffsetLimitation;   /* '<S3>/ResolverOffsetLimitation' */
  real32_T Sum1;                       /* '<S3>/Sum1' */
  real32_T w_el;                       /* '<S14>/Unit Delay1' */
  real32_T DeadTimeCompensation;       /* '<S11>/DeadTimeCompensation' */
  real32_T Sum3;                       /* '<S11>/Sum3' */
  real32_T UnitDelay_l;                /* '<S13>/Unit Delay' */
  real32_T Sum;                        /* '<S13>/Sum' */
  real32_T Switch;                     /* '<S13>/Switch' */
  real32_T Switch1;                    /* '<S13>/Switch1' */
  real32_T Sum2;                       /* '<S13>/Sum2' */
  real32_T UnitDelay3;                 /* '<S11>/Unit Delay3' */
  real32_T phi_el_observer;            /* '<S11>/Sum7' */
  real32_T Product_e;                  /* '<S8>/Product' */
  real32_T UnitDelay_a;                /* '<S8>/Unit Delay' */
  real32_T Add_m;                      /* '<S8>/Add' */
  real32_T phi_el_I_trafo;             /* '<S1>/Use_If_Starter' */
  real32_T TrigonometricFunction1;     /* '<S19>/Trigonometric Function1' */
  real32_T TrafoProd;                  /* '<S19>/TrafoProd' */
  real32_T TrigonometricFunction;      /* '<S19>/Trigonometric Function' */
  real32_T TrafoProd3;                 /* '<S19>/TrafoProd3' */
  real32_T I_d1_Act;                   /* '<S19>/I_d1_Act' */
  real32_T TrafoProd1;                 /* '<S19>/TrafoProd1' */
  real32_T TrafoProd2;                 /* '<S19>/TrafoProd2' */
  real32_T I_q1_Act;                   /* '<S19>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscreteFI[2];
  real32_T IdqErr[2];                  /* '<S17>/IdqErr' */
  real32_T KPek1[2];                   /* '<S22>/KP*e[k]1' */
  real32_T IntegDelay1[2];             /* '<S22>/IntegDelay1' */
  real32_T Product1;                   /* '<S22>/Product1' */
  real32_T IntegEnaSwitch1[2];         /* '<S22>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_h[2];/* '<S20>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum1_d;                     /* '<S5>/Sum1' */
  real32_T TrigonometricFunction1_b;   /* '<S20>/Trigonometric Function1' */
  real32_T TrafoProd_a;                /* '<S20>/TrafoProd' */
  real32_T TrigonometricFunction_l;    /* '<S20>/Trigonometric Function' */
  real32_T TrafoProd3_i;               /* '<S20>/TrafoProd3' */
  real32_T TrafoSum;                   /* '<S20>/TrafoSum' */
  real32_T TrafoProd1_b;               /* '<S20>/TrafoProd1' */
  real32_T TrafoProd2_b;               /* '<S20>/TrafoProd2' */
  real32_T TrafoSum1;                  /* '<S20>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_k[2];
  real32_T IdqErr_l[2];                /* '<S18>/IdqErr' */
  real32_T KPek1_l[2];                 /* '<S26>/KP*e[k]1' */
  real32_T IntegDelay1_o[2];           /* '<S26>/IntegDelay1' */
  real32_T Product1_k;                 /* '<S26>/Product1' */
  real32_T Product_c;                  /* '<S4>/Product' */
  real32_T Sum_k;                      /* '<S4>/Sum' */
  real32_T Switch1_k;                  /* '<S16>/Switch1' */
  real32_T Switch2;                    /* '<S16>/Switch2' */
  real32_T Sum2_p;                     /* '<S4>/Sum2' */
  real32_T SelectControlMode[6];       /* '<S1>/SelectControlMode' */
  real32_T TrigonometricFunction_n;    /* '<S47>/Trigonometric Function' */
  real32_T Gain1[4];                   /* '<S47>/Gain1' */
  real32_T TrigonometricFunction1_j;   /* '<S47>/Trigonometric Function1' */
  real32_T Gain[4];                    /* '<S47>/Gain' */
  real32_T Sum1_g[4];                  /* '<S47>/Sum1' */
  real32_T Product_c0[2];              /* '<S47>/Product' */
  real32_T U_uvw1[3];                  /* '<S45>/Product' */
  real32_T TrigonometricFunction_j;    /* '<S48>/Trigonometric Function' */
  real32_T Gain1_i[4];                 /* '<S48>/Gain1' */
  real32_T TrigonometricFunction1_h;   /* '<S48>/Trigonometric Function1' */
  real32_T Gain_f[4];                  /* '<S48>/Gain' */
  real32_T Sum1_f[4];                  /* '<S48>/Sum1' */
  real32_T Product_f[2];               /* '<S48>/Product' */
  real32_T Product_f3[3];              /* '<S46>/Product' */
  real32_T SelMod_DutyCycles[6];       /* '<S10>/SelectModulation' */
  real32_T Deviation;                  /* '<S11>/Deviation' */
  real32_T Product2;                   /* '<S11>/Product2' */
  real32_T Gain_g;                     /* '<S11>/Gain' */
  real32_T winkelimpuls;               /* '<S11>/Gain4' */
  real32_T Sum1_g4;                    /* '<S11>/Sum1' */
  real32_T Product_o;                  /* '<S11>/Product' */
  real32_T Product1_b;                 /* '<S11>/Product1' */
  real32_T UnitDelay1;                 /* '<S15>/Unit Delay1' */
  real32_T Sum2_m;                     /* '<S11>/Sum2' */
  real32_T Sum6;                       /* '<S11>/Sum6' */
  real32_T Product_n;                  /* '<S14>/Product' */
  real32_T Sum2_e;                     /* '<S14>/Sum2' */
  real32_T Product_cd;                 /* '<S15>/Product' */
  real32_T Sum2_j;                     /* '<S15>/Sum2' */
  real32_T phi_el_U_trafo[2];          /* '<S4>/Gain1' */
  real32_T IntegStopSwitch2[2];        /* '<S22>/IntegStopSwitch2' */
  real32_T U_d1_CC;                    /* '<S17>/Gain1' */
  real32_T U_q1_CC;                    /* '<S17>/Gain2' */
  real32_T IntegStopSwitch2_o[2];      /* '<S26>/IntegStopSwitch2' */
  real32_T I_dq1_Act_filt[2];       /* '<S19>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder[2];
                                    /* '<S20>/Discrete FIR Filter 20th order' */
  real32_T DataTypeConversion;         /* '<S6>/Data Type Conversion' */
  real32_T FOC_Overcurrent_I_uvw;      /* '<S6>/Gain1' */
  real32_T DataTypeConversion_i;       /* '<S7>/Data Type Conversion' */
  real32_T DataTypeConversion1;        /* '<S7>/Data Type Conversion1' */
  real32_T FOC_Undervoltage_U_DC;      /* '<S7>/Gain1' */
  real32_T FOC_Overvoltage_U_DC;       /* '<S7>/Gain2' */
  real32_T Abs_b;                      /* '<S8>/Abs' */
  real32_T Switch_l;                   /* '<S8>/Switch' */
  real32_T Add1;                       /* '<S8>/Add1' */
  real32_T Abs_f;                      /* '<S39>/Abs' */
  real32_T Switch_n;                   /* '<S39>/Switch' */
  real32_T Add1_c;                     /* '<S39>/Add1' */
  real32_T U_d1;                       /* '<S10>/Gain' */
  real32_T U_q1;                       /* '<S10>/Gain1' */
  real32_T U_alpha1;                   /* '<S10>/Gain2' */
  real32_T U_beta1;                    /* '<S10>/Gain3' */
  real32_T FCF_Cnt;                    /* '<S1>/FCF_Cnt' */
  real32_T Sum_o;                      /* '<S1>/Sum' */
  real32_T MinMax2;                    /* '<S44>/MinMax2' */
  real32_T MinMax3;                    /* '<S44>/MinMax3' */
  real32_T Sum1_o;                     /* '<S44>/Sum1' */
  real32_T Factor;                     /* '<S44>/Factor' */
  real32_T DutyCycle_SuperSinus_1[3];  /* '<S44>/DutyCycle_SuperSinus_1' */
  real32_T MinMax1;                    /* '<S44>/MinMax1' */
  real32_T MinMax4;                    /* '<S44>/MinMax4' */
  real32_T Sum2_i;                     /* '<S44>/Sum2' */
  real32_T Factor1;                    /* '<S44>/Factor1' */
  real32_T DutyCycle_SuperSinus_2[3];  /* '<S44>/DutyCycle_SuperSinus_2' */
  real32_T U_DC2;                      /* '<S43>/U_DC//2' */
  real32_T AvoidDivBy0;                /* '<S43>/AvoidDivBy0' */
  real32_T DutyCycle_normed[6];        /* '<S43>/DutyCycle_normalized' */
  real32_T U_DC2_l;                    /* '<S42>/U_DC//2' */
  real32_T AvoidDivBy0_f;              /* '<S42>/AvoidDivBy0' */
  real32_T Square[2];                  /* '<S42>/Square' */
  real32_T Sum_kr;                     /* '<S42>/Sum' */
  real32_T Sqrt;                       /* '<S42>/Sqrt' */
  real32_T Square1[2];                 /* '<S42>/Square1' */
  real32_T Sum1_a;                     /* '<S42>/Sum1' */
  real32_T Sqrt1;                      /* '<S42>/Sqrt1' */
  real32_T ModInd[2];                  /* '<S42>/Divide3' */
  real32_T Sign;                       /* '<S39>/Sign' */
  real32_T Gain1_o;                    /* '<S39>/Gain1' */
  real32_T Selectphicalc2;             /* '<S3>/Selectphicalc2' */
  real32_T Switch1_d;                  /* '<S12>/Switch1' */
  real32_T Switch2_f;                  /* '<S12>/Switch2' */
  real32_T Sum3_h;                     /* '<S12>/Sum3' */
  real32_T Sum2_l;                     /* '<S12>/Sum2' */
  real32_T ModeSwitch;                 /* '<S1>/ModeSwitch' */
  real32_T IntegEnaSwitch1_n[2];       /* '<S26>/IntegEnaSwitch1' */
  real32_T Product2_b[2];              /* '<S26>/Product2' */
  real32_T IntSum1[2];                 /* '<S26>/IntSum1' */
  real32_T Gain_fw;                    /* '<S40>/Gain' */
  real32_T Sign_p;                     /* '<S40>/Sign' */
  real32_T Abs_d;                      /* '<S40>/Abs' */
  real32_T Saturation1;                /* '<S40>/Saturation1' */
  real32_T Product_j;                  /* '<S40>/Product' */
  real32_T Sum1_n;                     /* '<S9>/Sum1' */
  real32_T Sign_n;                     /* '<S8>/Sign' */
  real32_T Gain1_h;                    /* '<S8>/Gain1' */
  real32_T IntegStopSwitch3[2];        /* '<S26>/IntegStopSwitch3' */
  real32_T IntSum2[2];                 /* '<S26>/IntSum2' */
  real32_T FOC_IntegDamp[2];           /* '<S26>/FOC_IntegDamp' */
  real32_T antiWindupProd[2];          /* '<S25>/antiWindupProd' */
  real32_T IntegStopSwitch1[2];        /* '<S26>/IntegStopSwitch1' */
  real32_T IntegStopSwitch3_h[2];      /* '<S22>/IntegStopSwitch3' */
  real32_T IntSum2_j[2];               /* '<S22>/IntSum2' */
  real32_T FOC_IntegDamp_c[2];         /* '<S22>/FOC_IntegDamp' */
  real32_T antiWindupProd_o[2];        /* '<S21>/antiWindupProd' */
  real32_T IntegStopSwitch1_f[2];      /* '<S22>/IntegStopSwitch1' */
  real32_T Product2_j[2];              /* '<S22>/Product2' */
  real32_T IntSum1_p[2];               /* '<S22>/IntSum1' */
  real32_T Sum3_d;                     /* '<S16>/Sum3' */
  real32_T Sum2_ez;                    /* '<S16>/Sum2' */
  real32_T ASCSwitch[6];               /* '<S2>/ASC Switch' */
  real32_T Scale02[6];                 /* '<S41>/Scale [0..2]' */
  real32_T Scale01[6];                 /* '<S41>/Scale  [0..1]' */
  real32_T Limit01[6];                 /* '<S41>/Limit [0..1]' */
  uint8_T Compare;                     /* '<S28>/Compare' */
  uint8_T Compare_i;                   /* '<S27>/Compare' */
  uint8_T Compare_o;                   /* '<S24>/Compare' */
  uint8_T Compare_f;                   /* '<S23>/Compare' */
  boolean_T Compare_b;                 /* '<S33>/Compare' */
  boolean_T LogicalOperator1;          /* '<S1>/Logical Operator1' */
  boolean_T LogicalOperator2;          /* '<S7>/Logical Operator2' */
  boolean_T Selectphicalc3;            /* '<S7>/Selectphicalc3' */
  boolean_T Memory;                    /* '<S36>/Memory' */
  boolean_T Logic[2];                  /* '<S36>/Logic' */
  boolean_T Selectphicalc1;            /* '<S7>/Selectphicalc1' */
  boolean_T Compare_br;                /* '<S34>/Compare' */
  boolean_T Compare_n;                 /* '<S38>/Compare' */
  boolean_T Uk1;                       /* '<S35>/Delay Input1' */
  boolean_T Selectphicalc4;            /* '<S7>/Selectphicalc4' */
  boolean_T Memory_k;                  /* '<S37>/Memory' */
  boolean_T Logic_g[2];                /* '<S37>/Logic' */
  boolean_T Selectphicalc2_m;          /* '<S7>/Selectphicalc2' */
  boolean_T LogicalOperator;           /* '<S7>/Logical Operator' */
  boolean_T Compare_a;                 /* '<S29>/Compare' */
  boolean_T Compare_l;                 /* '<S32>/Compare' */
  boolean_T Uk1_k;                     /* '<S30>/Delay Input1' */
  boolean_T Selectphicalc2_i;          /* '<S6>/Selectphicalc2' */
  boolean_T Memory_p;                  /* '<S31>/Memory' */
  boolean_T Logic_gq[2];               /* '<S31>/Logic' */
  boolean_T Selectphicalc1_j;          /* '<S6>/Selectphicalc1' */
  boolean_T LogicalOperator_n;         /* '<S1>/Logical Operator' */
  boolean_T Sprung;                    /* '<S13>/Sprung?' */
  boolean_T Sprung1;                   /* '<S13>/Sprung?1' */
  boolean_T FixPtRelationalOperator;   /* '<S35>/FixPt Relational Operator' */
  boolean_T LogicalOperator1_o;        /* '<S7>/Logical Operator1' */
  boolean_T FixPtRelationalOperator_e; /* '<S30>/FixPt Relational Operator' */
  boolean_T AntiWindupLE;              /* '<S25>/AntiWindupLE' */
  boolean_T AntiWindupOR_q;            /* '<S25>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d;            /* '<S25>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_l;            /* '<S21>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_o;          /* '<S21>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_e;          /* '<S21>/AntiWindupOR_d' */
} B_FOC_FCF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTransferFcn_states; /* '<S9>/Discrete Transfer Fcn' */
  real32_T UnitDelay_DSTATE;           /* '<S39>/Unit Delay' */
  real32_T UnitDelay1_DSTATE;          /* '<S14>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_h;         /* '<S13>/Unit Delay' */
  real32_T UnitDelay3_DSTATE;          /* '<S11>/Unit Delay3' */
  real32_T UnitDelay_DSTATE_p;         /* '<S8>/Unit Delay' */
  real32_T IntegDelay1_DSTATE[2];      /* '<S22>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_p[2];    /* '<S26>/IntegDelay1' */
  real32_T UnitDelay1_DSTATE_i;        /* '<S15>/Unit Delay1' */
  real32_T DiscreteFIRFilter20thorder_stat[38];
                                    /* '<S19>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_g[38];
                                    /* '<S20>/Discrete FIR Filter 20th order' */
  real32_T FCF_Cnt_DSTATE;             /* '<S1>/FCF_Cnt' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S19>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_m;
                                    /* '<S20>/Discrete FIR Filter 20th order' */
  boolean_T DelayInput1_DSTATE;        /* '<S35>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_c;      /* '<S30>/Delay Input1' */
  boolean_T Memory_PreviousInput;      /* '<S36>/Memory' */
  boolean_T Memory_PreviousInput_o;    /* '<S37>/Memory' */
  boolean_T Memory_PreviousInput_p;    /* '<S31>/Memory' */
} DW_FOC_FCF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T U_DC;                       /* '<Root>/U_DC [V]' */
  real32_T I_phA[6];                   /* '<Root>/I_ph [A]' */
  real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
  real32_T phi_elrad;                  /* '<Root>/phi_el [rad]' */
  real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
  real32_T FOC_Enable;                 /* '<Root>/FOC_Enable' */
  real32_T w_el_Ref_IfStarter;         /* '<Root>/w_el_Ref_IfStarter' */
  real32_T IfStarter_Active;           /* '<Root>/IfStarter_Active' */
} ExtU_FOC_FCF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T DutyCycles01[6];            /* '<Root>/DutyCycles [0..1]' */
  real32_T I_dq_ActA[4];               /* '<Root>/I_dq_Act [A]' */
  real32_T ModInd[2];                  /* '<Root>/ModInd' */
  real32_T w_elrads;                   /* '<Root>/w_el [rad//s]' */
  real32_T FOC_Error;                  /* '<Root>/FOC_Error' */
} ExtY_FOC_FCF_T;

/* Parameters (default storage) */
struct P_FOC_FCF_T_ {
  real_T FOC_ENABLE_Overcurrent_I_uvw; /* Variable: FOC_ENABLE_Overcurrent_I_uvw
                                        * Referenced by: '<S6>/FOC_ENABLE_Overcurrent_I_uvw1'
                                        */
  real_T FOC_ENABLE_Overvoltage_U_DC;  /* Variable: FOC_ENABLE_Overvoltage_U_DC
                                        * Referenced by: '<S7>/FOC_ENABLE_Overvoltage_U_DC1'
                                        */
  real_T FOC_ENABLE_Undervoltage_U_DC; /* Variable: FOC_ENABLE_Undervoltage_U_DC
                                        * Referenced by: '<S7>/FOC_ENABLE_Undervoltage_U_DC1'
                                        */
  real_T FOC_RESET_OC_Error;           /* Variable: FOC_RESET_OC_Error
                                        * Referenced by: '<S6>/Reset_OC_Error'
                                        */
  real_T FOC_RESET_OV_Error;           /* Variable: FOC_RESET_OV_Error
                                        * Referenced by: '<S7>/Reset_OV_Error'
                                        */
  real32_T FOC_6ph_AngleShift;         /* Variable: FOC_6ph_AngleShift
                                        * Referenced by:
                                        *   '<S4>/FOC_6ph_AngleShift'
                                        *   '<S5>/FOC_6ph_AngleShift'
                                        *   '<S9>/FOC_6ph_AngleShift'
                                        */
  real32_T FOC_ASC_Mode;               /* Variable: FOC_ASC_Mode
                                        * Referenced by: '<S2>/FOC_AKS_Mode'
                                        */
  real32_T FOC_AngleObs_w_InitVal;     /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S14>/Unit Delay1'
                                        */
  real32_T FOC_AngleObserver_D;        /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S11>/Constant1'
                                        */
  real32_T FOC_AngleObserver_w0;       /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S11>/Constant'
                                        */
  real32_T FOC_Enable;                 /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
  real32_T FOC_IntegDamp;              /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S22>/FOC_IntegDamp'
                                        *   '<S26>/FOC_IntegDamp'
                                        */
  real32_T FOC_KI;                     /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S22>/FOC_KI'
                                        *   '<S26>/FOC_KI'
                                        */
  real32_T FOC_KP;                     /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S22>/FOC_KP1'
                                        *   '<S26>/FOC_KP1'
                                        */
  real32_T FOC_LIMIT_Overcurrent_I_uvw;/* Variable: FOC_LIMIT_Overcurrent_I_uvw
                                        * Referenced by: '<S29>/Constant'
                                        */
  real32_T FOC_LIMIT_Overvoltage_U_DC; /* Variable: FOC_LIMIT_Overvoltage_U_DC
                                        * Referenced by: '<S34>/Constant'
                                        */
  real32_T FOC_LIMIT_Undervoltage_U_DC;/* Variable: FOC_LIMIT_Undervoltage_U_DC
                                        * Referenced by: '<S33>/Constant'
                                        */
  real32_T FOC_MANUAL_U_DC;            /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc1'
                                        */
  real32_T FOC_MaxModInd;              /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S21>/FOC_MaxModInd'
                                        *   '<S25>/FOC_MaxModInd'
                                        */
  real32_T FOC_Mode_Intern;            /* Variable: FOC_Mode_Intern
                                        * Referenced by: '<S1>/FOC_Mode_Intern'
                                        */
  real32_T FOC_OmegaObs3;              /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S11>/Gain4'
                                        */
  real32_T FOC_PhiSensorTdead;         /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S11>/DeadTimeCompensation'
                                        */
  real32_T FOC_Uf_U_max;               /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S40>/Saturation1'
                                        */
  real32_T FOC_Uf_U_min;               /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S40>/Saturation1'
                                        */
  real32_T FOC_Uf_Ud;                  /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S9>/Uf_Ud'
                                        */
  real32_T FOC_Uf_f_el;                /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S9>/Uf_w_el'
                                        */
  real32_T FOC_Uf_m;                   /* Variable: FOC_Uf_m
                                        * Referenced by: '<S40>/Gain'
                                        */
  real32_T FOC_output_trafo_delay;     /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S4>/FOC_output_trafo_delay'
                                        */
  real32_T FOC_phi_offset;             /* Variable: FOC_phi_offset
                                        * Referenced by: '<S3>/Constant'
                                        */
  uint8_T FOC_SELECT_Mode_Intern;      /* Variable: FOC_SELECT_Mode_Intern
                                        * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
                                        */
  uint8_T FOC_SELECT_Modulation;       /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S10>/Enable_SuperSinMod'
                                        */
  uint8_T FOC_SELECT_U_DC_INPUT;       /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
  uint8_T FOC_SELECT_phi;              /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real32_T AntiWindupGT_d_const;       /* Mask Parameter: AntiWindupGT_d_const
                                        * Referenced by: '<S23>/Constant'
                                        */
  real32_T AntiWindupGT_q_const;       /* Mask Parameter: AntiWindupGT_q_const
                                        * Referenced by: '<S24>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_n;     /* Mask Parameter: AntiWindupGT_d_const_n
                                        * Referenced by: '<S27>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_h;     /* Mask Parameter: AntiWindupGT_q_const_h
                                        * Referenced by: '<S28>/Constant'
                                        */
  boolean_T SRFlipFlop_initial_condition;
                                 /* Mask Parameter: SRFlipFlop_initial_condition
                                  * Referenced by: '<S36>/Memory'
                                  */
  boolean_T SRFlipFlop1_initial_condition;
                                /* Mask Parameter: SRFlipFlop1_initial_condition
                                 * Referenced by: '<S37>/Memory'
                                 */
  boolean_T SRFlipFlop_initial_condition_a;
                               /* Mask Parameter: SRFlipFlop_initial_condition_a
                                * Referenced by: '<S31>/Memory'
                                */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S35>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_o;
                                   /* Mask Parameter: DetectRisePositive_vinit_o
                                    * Referenced by: '<S30>/Delay Input1'
                                    */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S32>/Constant'
                                        */
  real_T Constant_Value_o;             /* Expression: 0
                                        * Referenced by: '<S38>/Constant'
                                        */
  real32_T Scale02_Bias;               /* Computed Parameter: Scale02_Bias
                                        * Referenced by: '<S41>/Scale [0..2]'
                                        */
  real32_T Scale01_Gain;               /* Computed Parameter: Scale01_Gain
                                        * Referenced by: '<S41>/Scale  [0..1]'
                                        */
  real32_T Limit01_UpperSat;           /* Computed Parameter: Limit01_UpperSat
                                        * Referenced by: '<S41>/Limit [0..1]'
                                        */
  real32_T Limit01_LowerSat;           /* Computed Parameter: Limit01_LowerSat
                                        * Referenced by: '<S41>/Limit [0..1]'
                                        */
  real32_T ASC_LS_Value[6];            /* Computed Parameter: ASC_LS_Value
                                        * Referenced by: '<S2>/ASC_LS'
                                        */
  real32_T ASC_HS_Value[6];            /* Computed Parameter: ASC_HS_Value
                                        * Referenced by: '<S2>/ASC_HS'
                                        */
  real32_T ASC_LSHS_Value[6];          /* Computed Parameter: ASC_LSHS_Value
                                        * Referenced by: '<S2>/ASC_LSHS'
                                        */
  real32_T Constant5_Value;            /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S13>/Constant5'
                                        */
  real32_T Constant6_Value;            /* Computed Parameter: Constant6_Value
                                        * Referenced by: '<S13>/Constant6'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S13>/Constant2'
                                        */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S13>/Constant4'
                                        */
  real32_T Constant_Value_n;           /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S16>/Constant'
                                        */
  real32_T Constant1_Value_d;          /* Computed Parameter: Constant1_Value_d
                                        * Referenced by: '<S16>/Constant1'
                                        */
  real32_T Zero_Value;                 /* Computed Parameter: Zero_Value
                                        * Referenced by: '<S22>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold;
                               /* Computed Parameter: IntegStopSwitch3_Threshold
                                * Referenced by: '<S22>/IntegStopSwitch3'
                                */
  real32_T IntegStopSwitch3_Threshold_a;
                             /* Computed Parameter: IntegStopSwitch3_Threshold_a
                              * Referenced by: '<S26>/IntegStopSwitch3'
                              */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real32_T Constant1_Value_k;          /* Computed Parameter: Constant1_Value_k
                                        * Referenced by: '<S8>/Constant1'
                                        */
  real32_T Zero_Value_o;               /* Computed Parameter: Zero_Value_o
                                        * Referenced by: '<S26>/Zero'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S12>/Constant'
                                        */
  real32_T Constant1_Value_g;          /* Computed Parameter: Constant1_Value_g
                                        * Referenced by: '<S12>/Constant1'
                                        */
  real32_T Switch1_Threshold;          /* Computed Parameter: Switch1_Threshold
                                        * Referenced by: '<S12>/Switch1'
                                        */
  real32_T Switch2_Threshold;          /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S12>/Switch2'
                                        */
  real32_T Gain1_Gain_a;               /* Computed Parameter: Gain1_Gain_a
                                        * Referenced by: '<S39>/Gain1'
                                        */
  real32_T Constant1_Value_e;          /* Computed Parameter: Constant1_Value_e
                                        * Referenced by: '<S39>/Constant1'
                                        */
  real32_T Constant2_Value_d;          /* Computed Parameter: Constant2_Value_d
                                        * Referenced by: '<S42>/Constant2'
                                        */
  real32_T U_DC2_Gain;                 /* Computed Parameter: U_DC2_Gain
                                        * Referenced by: '<S42>/U_DC//2'
                                        */
  real32_T Constant2_Value_g;          /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S43>/Constant2'
                                        */
  real32_T U_DC2_Gain_p;               /* Computed Parameter: U_DC2_Gain_p
                                        * Referenced by: '<S43>/U_DC//2'
                                        */
  real32_T Factor_Gain;                /* Computed Parameter: Factor_Gain
                                        * Referenced by: '<S44>/Factor'
                                        */
  real32_T Factor1_Gain;               /* Computed Parameter: Factor1_Gain
                                        * Referenced by: '<S44>/Factor1'
                                        */
  real32_T Constant_Value_d[6];        /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S45>/Constant'
                                        */
  real32_T Null_Value[6];              /* Computed Parameter: Null_Value
                                        * Referenced by: '<S1>/Null'
                                        */
  real32_T DiscreteTransferFcn_NumCoef;
                              /* Computed Parameter: DiscreteTransferFcn_NumCoef
                               * Referenced by: '<S9>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_DenCoef[2];
                              /* Computed Parameter: DiscreteTransferFcn_DenCoef
                               * Referenced by: '<S9>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_InitialStat;
                          /* Computed Parameter: DiscreteTransferFcn_InitialStat
                           * Referenced by: '<S9>/Discrete Transfer Fcn'
                           */
  real32_T f_2_w_el_Gain;              /* Computed Parameter: f_2_w_el_Gain
                                        * Referenced by: '<S9>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value;           /* Computed Parameter: FOC_T_fast_Value
                                        * Referenced by: '<S39>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S39>/Unit Delay'
                                */
  real32_T TrafoMatrixuvwalphabeta_Gain[6];
                             /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
                              * Referenced by: '<S19>/TrafoMatrix uvw->alphabeta'
                              */
  real32_T ResolverOffsetLimitation_UpperS;
                          /* Computed Parameter: ResolverOffsetLimitation_UpperS
                           * Referenced by: '<S3>/ResolverOffsetLimitation'
                           */
  real32_T ResolverOffsetLimitation_LowerS;
                          /* Computed Parameter: ResolverOffsetLimitation_LowerS
                           * Referenced by: '<S3>/ResolverOffsetLimitation'
                           */
  real32_T UnitDelay_InitialCondition_b;
                             /* Computed Parameter: UnitDelay_InitialCondition_b
                              * Referenced by: '<S13>/Unit Delay'
                              */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S13>/Constant3'
                                        */
  real32_T Constant1_Value_ep;         /* Computed Parameter: Constant1_Value_ep
                                        * Referenced by: '<S13>/Constant1'
                                        */
  real32_T UnitDelay3_InitialCondition;
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S11>/Unit Delay3'
                               */
  real32_T FOC_T_fast_Value_d;         /* Computed Parameter: FOC_T_fast_Value_d
                                        * Referenced by: '<S8>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_p;
                             /* Computed Parameter: UnitDelay_InitialCondition_p
                              * Referenced by: '<S8>/Unit Delay'
                              */
  real32_T IntegDelay1_InitialCondition;
                             /* Computed Parameter: IntegDelay1_InitialCondition
                              * Referenced by: '<S22>/IntegDelay1'
                              */
  real32_T FOC_T_fast_Value_n;         /* Computed Parameter: FOC_T_fast_Value_n
                                        * Referenced by: '<S22>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_p[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
                            * Referenced by: '<S20>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_m;
                           /* Computed Parameter: IntegDelay1_InitialCondition_m
                            * Referenced by: '<S26>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_e;         /* Computed Parameter: FOC_T_fast_Value_e
                                        * Referenced by: '<S26>/FOC_T_fast'
                                        */
  real32_T FOC_T_fast_Value_m;         /* Computed Parameter: FOC_T_fast_Value_m
                                        * Referenced by: '<S4>/FOC_T_fast'
                                        */
  real32_T Switch1_Threshold_a;       /* Computed Parameter: Switch1_Threshold_a
                                       * Referenced by: '<S16>/Switch1'
                                       */
  real32_T Switch2_Threshold_o;       /* Computed Parameter: Switch2_Threshold_o
                                       * Referenced by: '<S16>/Switch2'
                                       */
  real32_T Gain1_Gain_h[4];            /* Computed Parameter: Gain1_Gain_h
                                        * Referenced by: '<S47>/Gain1'
                                        */
  real32_T Gain_Gain[4];               /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S47>/Gain'
                                        */
  real32_T Constant_Value_g[6];        /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S46>/Constant'
                                        */
  real32_T Gain1_Gain_c[4];            /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S48>/Gain1'
                                        */
  real32_T Gain_Gain_l[4];             /* Computed Parameter: Gain_Gain_l
                                        * Referenced by: '<S48>/Gain'
                                        */
  real32_T FOC_T_fast_Value_df;       /* Computed Parameter: FOC_T_fast_Value_df
                                       * Referenced by: '<S11>/FOC_T_fast'
                                       */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S11>/Gain'
                                        */
  real32_T UnitDelay1_InitialCondition;
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<S15>/Unit Delay1'
                               */
  real32_T FOC_T_fast_Value_c;         /* Computed Parameter: FOC_T_fast_Value_c
                                        * Referenced by: '<S14>/FOC_T_fast'
                                        */
  real32_T FOC_T_fast_Value_k;         /* Computed Parameter: FOC_T_fast_Value_k
                                        * Referenced by: '<S15>/FOC_T_fast'
                                        */
  real32_T Gain1_Gain_k;               /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real32_T Zero1_Value[2];             /* Computed Parameter: Zero1_Value
                                        * Referenced by: '<S22>/Zero1'
                                        */
  real32_T Gain1_Gain_cs;              /* Computed Parameter: Gain1_Gain_cs
                                        * Referenced by: '<S17>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S17>/Gain2'
                                        */
  real32_T Zero1_Value_l[2];           /* Computed Parameter: Zero1_Value_l
                                        * Referenced by: '<S26>/Zero1'
                                        */
  real32_T DiscreteFIRFilter20thorder_Init;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Init
                           * Referenced by: '<S19>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Coef[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
                           * Referenced by: '<S19>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_k;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
                           * Referenced by: '<S20>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_a[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
                           * Referenced by: '<S20>/Discrete FIR Filter 20th order'
                           */
  real32_T Gain1_Gain_f;               /* Computed Parameter: Gain1_Gain_f
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real32_T Gain1_Gain_g;               /* Computed Parameter: Gain1_Gain_g
                                        * Referenced by: '<S7>/Gain1'
                                        */
  real32_T Gain2_Gain_n;               /* Computed Parameter: Gain2_Gain_n
                                        * Referenced by: '<S7>/Gain2'
                                        */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S8>/Switch'
                                        */
  real32_T Switch_Threshold_c;         /* Computed Parameter: Switch_Threshold_c
                                        * Referenced by: '<S39>/Switch'
                                        */
  real32_T Gain_Gain_j;                /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S10>/Gain'
                                        */
  real32_T Gain1_Gain_e;               /* Computed Parameter: Gain1_Gain_e
                                        * Referenced by: '<S10>/Gain1'
                                        */
  real32_T Gain2_Gain_f;               /* Computed Parameter: Gain2_Gain_f
                                        * Referenced by: '<S10>/Gain2'
                                        */
  real32_T Gain3_Gain;                 /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<S10>/Gain3'
                                        */
  real32_T Constant_Value_e2;          /* Computed Parameter: Constant_Value_e2
                                        * Referenced by: '<S1>/Constant'
                                        */
  real32_T Counter_Start_Value;       /* Computed Parameter: Counter_Start_Value
                                       * Referenced by: '<S1>/Counter_Start'
                                       */
  real32_T FCF_Cnt_InitialCondition;
                                 /* Computed Parameter: FCF_Cnt_InitialCondition
                                  * Referenced by: '<S1>/FCF_Cnt'
                                  */
  boolean_T Constant2_Value_o;         /* Computed Parameter: Constant2_Value_o
                                        * Referenced by: '<S6>/Constant2'
                                        */
  boolean_T Constant1_Value_gm;        /* Computed Parameter: Constant1_Value_gm
                                        * Referenced by: '<S6>/Constant1'
                                        */
  boolean_T Constant3_Value_i;         /* Computed Parameter: Constant3_Value_i
                                        * Referenced by: '<S7>/Constant3'
                                        */
  boolean_T Constant1_Value_j;         /* Computed Parameter: Constant1_Value_j
                                        * Referenced by: '<S7>/Constant1'
                                        */
  boolean_T Constant2_Value_j;         /* Computed Parameter: Constant2_Value_j
                                        * Referenced by: '<S7>/Constant2'
                                        */
  boolean_T Constant4_Value_b;         /* Computed Parameter: Constant4_Value_b
                                        * Referenced by: '<S7>/Constant4'
                                        */
  boolean_T Logic_table[16];           /* Computed Parameter: Logic_table
                                        * Referenced by: '<S36>/Logic'
                                        */
  boolean_T Logic_table_m[16];         /* Computed Parameter: Logic_table_m
                                        * Referenced by: '<S37>/Logic'
                                        */
  boolean_T Logic_table_f[16];         /* Computed Parameter: Logic_table_f
                                        * Referenced by: '<S31>/Logic'
                                        */
  uint8_T Switch1_Threshold_m;        /* Computed Parameter: Switch1_Threshold_m
                                       * Referenced by: '<S1>/Switch1'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM_FOC_FCF_T {
  const char_T * volatile errorStatus;
  B_FOC_FCF_T *blockIO;
  ExtU_FOC_FCF_T *inputs;
  ExtY_FOC_FCF_T *outputs;
  DW_FOC_FCF_T *dwork;
};

/* Block parameters (default storage) */
extern P_FOC_FCF_T FOC_FCF_P;

/* Model entry point functions */
extern void FOC_FCF_initialize(RT_MODEL_FOC_FCF_T *const FOC_FCF_M);
extern void FOC_FCF_step(RT_MODEL_FOC_FCF_T *const FOC_FCF_M);
extern void FOC_FCF_terminate(RT_MODEL_FOC_FCF_T *const FOC_FCF_M);

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
 * hilite_system('MotorControl_HeadModel/Motor_Control_Model/FOC_FCF')    - opens subsystem MotorControl_HeadModel/Motor_Control_Model/FOC_FCF
 * hilite_system('MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MotorControl_HeadModel/Motor_Control_Model'
 * '<S1>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF'
 * '<S2>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ASC_Switch'
 * '<S3>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption'
 * '<S4>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Lead'
 * '<S5>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller'
 * '<S6>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection'
 * '<S7>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection'
 * '<S8>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/SubS_2pi_Integrator'
 * '<S9>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f'
 * '<S10>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output'
 * '<S11>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver'
 * '<S12>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/Modulo2Pi'
 * '<S13>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/2PiKorr'
 * '<S14>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator'
 * '<S15>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator1'
 * '<S16>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Lead/Modulo2Pi'
 * '<S17>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1'
 * '<S18>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2'
 * '<S19>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_1'
 * '<S20>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_2'
 * '<S21>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup'
 * '<S22>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/FeedbackPI'
 * '<S23>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_d'
 * '<S24>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_q'
 * '<S25>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup'
 * '<S26>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/FeedbackPI'
 * '<S27>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_d'
 * '<S28>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_q'
 * '<S29>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/Compare To Constant'
 * '<S30>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/Detect Rise Positive'
 * '<S31>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/S-R Flip-Flop'
 * '<S32>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/Detect Rise Positive/Positive'
 * '<S33>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Compare To Constant'
 * '<S34>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Compare To Constant1'
 * '<S35>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Detect Rise Positive'
 * '<S36>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/S-R Flip-Flop'
 * '<S37>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/S-R Flip-Flop1'
 * '<S38>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Detect Rise Positive/Positive'
 * '<S39>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/SubS_2pi_Integrator'
 * '<S40>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/UfKennlinie'
 * '<S41>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Adjust_duty_cycle_range'
 * '<S42>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Calc_Modulation_Index'
 * '<S43>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/NormalizedVoltage'
 * '<S44>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Super_Sinus_Modulation'
 * '<S45>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_1'
 * '<S46>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_2'
 * '<S47>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_1'
 * '<S48>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_2'
 */
#endif                                 /* FOC_FCF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
