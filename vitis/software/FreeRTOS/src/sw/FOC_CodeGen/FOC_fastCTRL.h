/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_fastCTRL.h
 *
 * Code generated for Simulink model 'FOC_fastCTRL'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Oct  9 23:28:17 2023
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
  real_T ModeSwitch;                   /* '<S1>/ModeSwitch' */
  real_T DiscreteTransferFcn;          /* '<S7>/Discrete Transfer Fcn' */
  real_T f_2_w_el;                     /* '<S7>/f_2_w_el' */
  real_T Product;                      /* '<S48>/Product' */
  real_T UnitDelay;                    /* '<S48>/Unit Delay' */
  real_T Add;                          /* '<S48>/Add' */
  real_T TrafoMatrixuvwalphabeta[2];   /* '<S38>/TrafoMatrix uvw->alphabeta' */
  real_T UnitDelay1;                   /* '<S33>/Unit Delay1' */
  real_T AutoSwitchHysteresis;         /* '<S5>/AutoSwitchHysteresis' */
  real_T Selectphicalc3;               /* '<S5>/Selectphicalc3' */
  real_T Switch;                       /* '<S24>/Switch' */
  real_T Switch_j;                     /* '<S25>/Switch' */
  real_T Switch_i;                     /* '<S27>/Switch' */
  real_T ResolverOffsetLimitation;     /* '<S5>/ResolverOffsetLimitation' */
  real_T Sum3;                         /* '<S5>/Sum3' */
  real_T UnitDelay_b[2];               /* '<S15>/Unit Delay' */
  real_T Product3[2];                  /* '<S3>/Product3' */
  real_T psi_PM_alphabeta[2];          /* '<S3>/Sum1' */
  real_T TrigonometricFunction;        /* '<S11>/Trigonometric Function' */
  real_T Switch_Phi;                   /* '<S11>/Switch_Phi' */
  real_T UnitDelay_n;                  /* '<S12>/Unit Delay' */
  real_T Product_o;                    /* '<S13>/Product' */
  real_T DiscreteTransferFcn_e;        /* '<S13>/Discrete Transfer Fcn' */
  real_T Switch1;                      /* '<S13>/Switch1' */
  real_T Product1;                     /* '<S13>/Product1' */
  real_T DiscreteTransferFcn1;         /* '<S13>/Discrete Transfer Fcn1' */
  real_T Switch_speed;                 /* '<S13>/Switch_speed' */
  real_T Switch2;                      /* '<S3>/Switch2' */
  real_T Switch_ib;                    /* '<S3>/Switch' */
  real_T Abs;                          /* '<S3>/Abs' */
  real_T Product_h;                    /* '<S3>/Product' */
  real_T TrigonometricFunction_m;      /* '<S3>/Trigonometric Function' */
  real_T Sum3_l;                       /* '<S3>/Sum3' */
  real_T Product1_d;                   /* '<S3>/Product1' */
  real_T Sum2;                         /* '<S3>/Sum2' */
  real_T Switch2_n;                    /* '<S10>/Switch2' */
  real_T Switch1_m;                    /* '<S10>/Switch1' */
  real_T Sum1;                         /* '<S10>/Sum1' */
  real_T Selectphicalc1;               /* '<S5>/Selectphicalc1' */
  real_T Switch1_j;                    /* '<S30>/Switch1' */
  real_T Switch2_k;                    /* '<S30>/Switch2' */
  real_T Selectphicalc3_c;             /* '<S26>/Selectphicalc3' */
  real_T Product3_g;                   /* '<S26>/Product3' */
  real_T Sum3_h;                       /* '<S26>/Sum3' */
  real_T UnitDelay_c;                  /* '<S32>/Unit Delay' */
  real_T Sum;                          /* '<S32>/Sum' */
  real_T Switch_p;                     /* '<S32>/Switch' */
  real_T Switch1_g;                    /* '<S32>/Switch1' */
  real_T Sum2_n;                       /* '<S32>/Sum2' */
  real_T UnitDelay3;                   /* '<S26>/Unit Delay3' */
  real_T Selectphicalc2;               /* '<S5>/Selectphicalc2' */
  real_T Switch1_d;                    /* '<S28>/Switch1' */
  real_T Switch2_nz;                   /* '<S28>/Switch2' */
  real_T TrigonometricFunction1;       /* '<S38>/Trigonometric Function1' */
  real_T TrafoProd;                    /* '<S38>/TrafoProd' */
  real_T TrigonometricFunction_h;      /* '<S38>/Trigonometric Function' */
  real_T TrafoProd3;                   /* '<S38>/TrafoProd3' */
  real_T TrafoSum;                     /* '<S38>/TrafoSum' */
  real_T TrafoProd1;                   /* '<S38>/TrafoProd1' */
  real_T TrafoProd2;                   /* '<S38>/TrafoProd2' */
  real_T TrafoSum1;                    /* '<S38>/TrafoSum1' */
  real_T TmpSignalConversionAtMathFuncti[2];
  real_T IdqErr[2];                    /* '<S36>/IdqErr' */
  real_T KPek1[2];                     /* '<S41>/KP*e[k]1' */
  real_T IntegDelay1[2];               /* '<S41>/IntegDelay1' */
  real_T Product1_f;                   /* '<S41>/Product1' */
  real_T TrafoMatrixuvwalphabeta_c[2]; /* '<S39>/TrafoMatrix uvw->alphabeta' */
  real_T Sum1_f;                       /* '<S6>/Sum1' */
  real_T TrigonometricFunction1_c;     /* '<S39>/Trigonometric Function1' */
  real_T TrafoProd_d;                  /* '<S39>/TrafoProd' */
  real_T TrigonometricFunction_j;      /* '<S39>/Trigonometric Function' */
  real_T TrafoProd3_o;                 /* '<S39>/TrafoProd3' */
  real_T TrafoSum_a;                   /* '<S39>/TrafoSum' */
  real_T TrafoProd1_m;                 /* '<S39>/TrafoProd1' */
  real_T TrafoProd2_e;                 /* '<S39>/TrafoProd2' */
  real_T TrafoSum1_h;                  /* '<S39>/TrafoSum1' */
  real_T TmpSignalConversionAtDiscreteFI[2];
  real_T IdqErr_i[2];                  /* '<S37>/IdqErr' */
  real_T KPek1_a[2];                   /* '<S45>/KP*e[k]1' */
  real_T IntegDelay1_b[2];             /* '<S45>/IntegDelay1' */
  real_T Product1_p;                   /* '<S45>/Product1' */
  real_T Product_d;                    /* '<S5>/Product' */
  real_T Sum_e;                        /* '<S5>/Sum' */
  real_T Switch1_b;                    /* '<S29>/Switch1' */
  real_T Switch2_e;                    /* '<S29>/Switch2' */
  real_T SelectControlMode[6];         /* '<S1>/SelectControlMode' */
  real_T TrigonometricFunction_mr;     /* '<S56>/Trigonometric Function' */
  real_T Gain1[4];                     /* '<S56>/Gain1' */
  real_T TrigonometricFunction1_m;     /* '<S56>/Trigonometric Function1' */
  real_T Gain[4];                      /* '<S56>/Gain' */
  real_T Sum1_b[4];                    /* '<S56>/Sum1' */
  real_T Product_i[2];                 /* '<S56>/Product' */
  real_T Product_hu[3];                /* '<S54>/Product' */
  real_T TrigonometricFunction_o;      /* '<S57>/Trigonometric Function' */
  real_T Gain1_j[4];                   /* '<S57>/Gain1' */
  real_T TrigonometricFunction1_j;     /* '<S57>/Trigonometric Function1' */
  real_T Gain_f[4];                    /* '<S57>/Gain' */
  real_T Sum1_bx[4];                   /* '<S57>/Sum1' */
  real_T Product_p[2];                 /* '<S57>/Product' */
  real_T Product_b[3];                 /* '<S55>/Product' */
  real_T T_ab;                         /* '<S12>/T_ab' */
  real_T Sum1_bh;                      /* '<S12>/Sum1' */
  real_T Divide;                       /* '<S12>/Divide' */
  real_T Divide2;                      /* '<S12>/Divide2' */
  real_T Product3_h;                   /* '<S12>/Product3' */
  real_T Sum_p;                        /* '<S12>/Sum' */
  real_T Product2[2];                  /* '<S3>/Product2' */
  real_T Product_g[2];                 /* '<S16>/Product' */
  real_T UnitDelay_l[2];               /* '<S14>/Unit Delay' */
  real_T UnitDelay1_j[2];              /* '<S14>/Unit Delay1' */
  real_T Switch4[2];                   /* '<S14>/Switch4' */
  real_T Switch3[2];                   /* '<S14>/Switch3' */
  real_T Sum_ey[2];                    /* '<S3>/Sum' */
  real_T Product_bg[2];                /* '<S15>/Product' */
  real_T Sum4[2];                      /* '<S15>/Sum4' */
  real_T UnitDelay_lj[2];              /* '<S22>/Unit Delay' */
  real_T Product3_c[2];                /* '<S4>/Product3' */
  real_T psi_PM_alphabeta_n[2];        /* '<S4>/Sum1' */
  real_T TrigonometricFunction_a;      /* '<S18>/Trigonometric Function' */
  real_T Switch_Phi_a;                 /* '<S18>/Switch_Phi' */
  real_T UnitDelay_h;                  /* '<S19>/Unit Delay' */
  real_T Product_e;                    /* '<S20>/Product' */
  real_T DiscreteTransferFcn_m;        /* '<S20>/Discrete Transfer Fcn' */
  real_T Switch1_n;                    /* '<S20>/Switch1' */
  real_T Product1_i;                   /* '<S20>/Product1' */
  real_T DiscreteTransferFcn1_l;       /* '<S20>/Discrete Transfer Fcn1' */
  real_T Switch_speed_m;               /* '<S20>/Switch_speed' */
  real_T Switch2_kf;                   /* '<S4>/Switch2' */
  real_T Switch_pg;                    /* '<S4>/Switch' */
  real_T Abs_f;                        /* '<S4>/Abs' */
  real_T Product_n;                    /* '<S4>/Product' */
  real_T TrigonometricFunction_n;      /* '<S4>/Trigonometric Function' */
  real_T Sum3_o;                       /* '<S4>/Sum3' */
  real_T Product1_a;                   /* '<S4>/Product1' */
  real_T Sum2_p;                       /* '<S4>/Sum2' */
  real_T Switch2_g;                    /* '<S17>/Switch2' */
  real_T Switch1_bk;                   /* '<S17>/Switch1' */
  real_T Sum1_n;                       /* '<S17>/Sum1' */
  real_T T_ab_i;                       /* '<S19>/T_ab' */
  real_T Sum1_a;                       /* '<S19>/Sum1' */
  real_T Divide_l;                     /* '<S19>/Divide' */
  real_T Divide2_p;                    /* '<S19>/Divide2' */
  real_T Product3_hb;                  /* '<S19>/Product3' */
  real_T Sum_g;                        /* '<S19>/Sum' */
  real_T Product2_i[2];                /* '<S4>/Product2' */
  real_T Product_k[2];                 /* '<S23>/Product' */
  real_T UnitDelay_k[2];               /* '<S21>/Unit Delay' */
  real_T UnitDelay1_f[2];              /* '<S21>/Unit Delay1' */
  real_T Switch4_n[2];                 /* '<S21>/Switch4' */
  real_T Switch3_p[2];                 /* '<S21>/Switch3' */
  real_T Sum_n[2];                     /* '<S4>/Sum' */
  real_T Product_f[2];                 /* '<S22>/Product' */
  real_T Sum4_l[2];                    /* '<S22>/Sum4' */
  real_T phi_est_2;                    /* '<S4>/phi_est_2' */
  real_T AnpassungderSignalfrequenzanPol;
                       /* '<S25>/Anpassung der Signalfrequenz an Polpaarzahl' */
  real_T Constant;                     /* '<S25>/Constant' */
  real_T Deviation;                    /* '<S26>/Deviation' */
  real_T Product2_n;                   /* '<S26>/Product2' */
  real_T Gain_e;                       /* '<S26>/Gain' */
  real_T winkelimpuls;                 /* '<S26>/Gain4' */
  real_T Sum1_e;                       /* '<S26>/Sum1' */
  real_T Product_fh;                   /* '<S26>/Product' */
  real_T Product1_b;                   /* '<S26>/Product1' */
  real_T UnitDelay1_i;                 /* '<S34>/Unit Delay1' */
  real_T Sum2_o;                       /* '<S26>/Sum2' */
  real_T Sum6;                         /* '<S26>/Sum6' */
  real_T Product_f4;                   /* '<S33>/Product' */
  real_T Sum2_d;                       /* '<S33>/Sum2' */
  real_T Product_dh;                   /* '<S34>/Product' */
  real_T Sum2_on;                      /* '<S34>/Sum2' */
  real_T phi_est_error2;               /* '<S5>/phi_est_error2' */
  real_T phi_est_error;                /* '<S5>/phi_est_error' */
  real_T MathFunction[2];              /* '<S35>/Math Function' */
  real_T Sum_i;                        /* '<S35>/Sum' */
  real_T I_ph_peak;                    /* '<S35>/I_ph_peak' */
  real_T I_ph_RMS;                     /* '<S35>/I_ph_RMS' */
  real_T IntegStopSwitch2[2];          /* '<S41>/IntegStopSwitch2' */
  real_T I_d_Ref;                      /* '<S36>/I_d_Ref' */
  real_T I_q_Ref;                      /* '<S36>/I_q_Ref' */
  real_T IntegStopSwitch2_h[2];        /* '<S45>/IntegStopSwitch2' */
  real_T I_d_Act_1;                    /* '<S38>/I_d_Act_1' */
  real_T I_q_Act_1;                    /* '<S38>/I_q_Act_1' */
  real_T I_u_1;                        /* '<S38>/I_u_1' */
  real_T I_v_1;                        /* '<S38>/I_v_1' */
  real_T I_w_1;                        /* '<S38>/I_w_1' */
  real_T DiscreteFIRFilter20thorder[2];
                                    /* '<S38>/Discrete FIR Filter 20th order' */
  real_T I_d_Act_filt_1;               /* '<S38>/Gain5' */
  real_T I_q_Act_filt_1;               /* '<S38>/Gain6' */
  real_T DiscreteFIRFilter20thorder_h[2];
                                    /* '<S39>/Discrete FIR Filter 20th order' */
  real_T I_d_Act_2;                    /* '<S39>/I_d_Act_2' */
  real_T I_d_Act_filt_2;               /* '<S39>/I_d_Act_filt_2' */
  real_T I_q_Act_2;                    /* '<S39>/I_q_Act_2' */
  real_T I_q_Act_filt_2;               /* '<S39>/I_q_Act_filt_2' */
  real_T I_u_2;                        /* '<S39>/I_u_2' */
  real_T I_v_2;                        /* '<S39>/I_v_2' */
  real_T I_w_2;                        /* '<S39>/I_w_2' */
  real_T Abs_p;                        /* '<S48>/Abs' */
  real_T Switch_ip;                    /* '<S48>/Switch' */
  real_T Add1;                         /* '<S48>/Add1' */
  real_T UnitDelay_c3[2];              /* '<S1>/Unit Delay' */
  real_T U_d_1;                        /* '<S56>/U_d_1' */
  real_T U_q_1;                        /* '<S56>/U_q_1' */
  real_T U_d_2;                        /* '<S57>/U_d_2' */
  real_T U_q_2;                        /* '<S57>/U_q_2' */
  real_T TrigonometricFunction_c;      /* '<S59>/Trigonometric Function' */
  real_T TrigonometricFunction_k;      /* '<S58>/Trigonometric Function' */
  real_T Sum2_di;                      /* '<S9>/Sum2' */
  real_T TrigonometricFunction_p;      /* '<S9>/Trigonometric Function' */
  real_T DiscreteFIRFilter10thorder; /* '<S9>/Discrete FIR Filter 10th order' */
  real_T Sum_pl;                       /* '<S1>/Sum' */
  real_T Sig1;                         /* '<S1>/Gain' */
  real_T Sig2;                         /* '<S1>/Gain1' */
  real_T Sig3;                         /* '<S1>/Gain2' */
  real_T Sig4;                         /* '<S1>/Gain3' */
  real_T Sig5;                         /* '<S1>/Gain4' */
  real_T Sig6;                         /* '<S1>/Gain5' */
  real_T Sig7;                         /* '<S1>/Gain6' */
  real_T Sig8;                         /* '<S1>/Gain7' */
  real_T U_DC2;                        /* '<S52>/U_DC//2' */
  real_T AvoidDivBy0;                  /* '<S52>/AvoidDivBy0' */
  real_T Divide3[6];                   /* '<S52>/Divide3' */
  real_T U_DC2_p;                      /* '<S51>/U_DC//2' */
  real_T AvoidDivBy0_d;                /* '<S51>/AvoidDivBy0' */
  real_T Square[2];                    /* '<S51>/Square' */
  real_T Sum_h;                        /* '<S51>/Sum' */
  real_T Sqrt;                         /* '<S51>/Sqrt' */
  real_T Square1[2];                   /* '<S51>/Square1' */
  real_T Sum1_nn;                      /* '<S51>/Sum1' */
  real_T Sqrt1;                        /* '<S51>/Sqrt1' */
  real_T ModInd_1;                     /* '<S51>/ModInd_1' */
  real_T ModInd_2;                     /* '<S51>/ModInd_2' */
  real_T Sign;                         /* '<S48>/Sign' */
  real_T Gain1_k;                      /* '<S48>/Gain1' */
  real_T IntegEnaSwitch1[2];           /* '<S41>/IntegEnaSwitch1' */
  real_T IntegEnaSwitch1_m[2];         /* '<S45>/IntegEnaSwitch1' */
  real_T Sum2_e;                       /* '<S5>/Sum2' */
  real_T Product2_e[2];                /* '<S45>/Product2' */
  real_T IntSum1[2];                   /* '<S45>/IntSum1' */
  real_T Product2_b[2];                /* '<S41>/Product2' */
  real_T IntSum1_f[2];                 /* '<S41>/IntSum1' */
  real_T Gain_i;                       /* '<S49>/Gain' */
  real_T Sign_m;                       /* '<S49>/Sign' */
  real_T Abs_e;                        /* '<S49>/Abs' */
  real_T Saturation1;                  /* '<S49>/Saturation1' */
  real_T Product_i4;                   /* '<S49>/Product' */
  real_T Sum1_c;                       /* '<S7>/Sum1' */
  real_T IntegStopSwitch3[2];          /* '<S45>/IntegStopSwitch3' */
  real_T IntSum2[2];                   /* '<S45>/IntSum2' */
  real_T FOC_IntegDamp[2];             /* '<S45>/FOC_IntegDamp' */
  real_T antiWindupProd[2];            /* '<S44>/antiWindupProd' */
  real_T IntegStopSwitch1[2];          /* '<S45>/IntegStopSwitch1' */
  real_T IntegStopSwitch3_o[2];        /* '<S41>/IntegStopSwitch3' */
  real_T IntSum2_l[2];                 /* '<S41>/IntSum2' */
  real_T FOC_IntegDamp_g[2];           /* '<S41>/FOC_IntegDamp' */
  real_T antiWindupProd_j[2];          /* '<S40>/antiWindupProd' */
  real_T IntegStopSwitch1_e[2];        /* '<S41>/IntegStopSwitch1' */
  real_T Sum3_d;                       /* '<S30>/Sum3' */
  real_T Sum2_k;                       /* '<S30>/Sum2' */
  real_T Sum3_a;                       /* '<S29>/Sum3' */
  real_T Sum2_op;                      /* '<S29>/Sum2' */
  real_T Sum3_n;                       /* '<S28>/Sum3' */
  real_T Sum2_i;                       /* '<S28>/Sum2' */
  real_T PhiInverted;                  /* '<S27>/PhiInverted' */
  real_T Switch1_p;                    /* '<S31>/Switch1' */
  real_T Switch2_d;                    /* '<S31>/Switch2' */
  real_T Sum3_c;                       /* '<S31>/Sum3' */
  real_T Sum2_m;                       /* '<S31>/Sum2' */
  real_T Bias;                         /* '<S20>/Bias' */
  real_T Sum1_ce;                      /* '<S18>/Sum1' */
  real_T Bias_p;                       /* '<S13>/Bias' */
  real_T Sum1_bu;                      /* '<S11>/Sum1' */
  real_T AKSSwitch[6];                 /* '<S2>/AKS Switch' */
  real_T SelectModulation[6];          /* '<S8>/SelectModulation' */
  real_T u2[6];                        /* '<S50>/[0..2]' */
  real_T u1[6];                        /* '<S50>/[0..1]' */
  real_T Limit01[6];                   /* '<S50>/Limit [0..1]' */
  real_T MinMax2;                      /* '<S53>/MinMax2' */
  real_T MinMax3;                      /* '<S53>/MinMax3' */
  real_T Sum1_nk;                      /* '<S53>/Sum1' */
  real_T Factor;                       /* '<S53>/Factor' */
  real_T MinMax1;                      /* '<S53>/MinMax1' */
  real_T MinMax4;                      /* '<S53>/MinMax4' */
  real_T Sum2_b;                       /* '<S53>/Sum2' */
  real_T Factor1;                      /* '<S53>/Factor1' */
  real_T Sum3_f[3];                    /* '<S53>/Sum3' */
  real_T Sum4_p[3];                    /* '<S53>/Sum4' */
  uint8_T Compare;                     /* '<S47>/Compare' */
  uint8_T Compare_h;                   /* '<S46>/Compare' */
  uint8_T Compare_l;                   /* '<S43>/Compare' */
  uint8_T Compare_p;                   /* '<S42>/Compare' */
  boolean_T RelationalOperator;        /* '<S13>/Relational Operator' */
  boolean_T RelationalOperator1;       /* '<S13>/Relational Operator1' */
  boolean_T LogicalOperator;           /* '<S13>/Logical Operator' */
  boolean_T RelationalOperator2;       /* '<S13>/Relational Operator2' */
  boolean_T Sprung;                    /* '<S32>/Sprung?' */
  boolean_T Sprung1;                   /* '<S32>/Sprung?1' */
  boolean_T LogicalOperator1;          /* '<S1>/Logical Operator1' */
  boolean_T RelationalOperator_o;      /* '<S20>/Relational Operator' */
  boolean_T RelationalOperator1_c;     /* '<S20>/Relational Operator1' */
  boolean_T LogicalOperator_a;         /* '<S20>/Logical Operator' */
  boolean_T RelationalOperator2_n;     /* '<S20>/Relational Operator2' */
  boolean_T AntiWindupLE;              /* '<S44>/AntiWindupLE' */
  boolean_T AntiWindupOR_q;            /* '<S44>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d;            /* '<S44>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_k;            /* '<S40>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_d;          /* '<S40>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_b;          /* '<S40>/AntiWindupOR_d' */
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
  real_T UnitDelay_DSTATE_o[2];        /* '<S14>/Unit Delay' */
  real_T UnitDelay1_DSTATE_h[2];       /* '<S14>/Unit Delay1' */
  real_T UnitDelay_DSTATE_e[2];        /* '<S22>/Unit Delay' */
  real_T UnitDelay_DSTATE_b;           /* '<S19>/Unit Delay' */
  real_T DiscreteTransferFcn_states_j; /* '<S20>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states_c;/* '<S20>/Discrete Transfer Fcn1' */
  real_T UnitDelay_DSTATE_k[2];        /* '<S21>/Unit Delay' */
  real_T UnitDelay1_DSTATE_e[2];       /* '<S21>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_he;         /* '<S34>/Unit Delay1' */
  real_T DiscreteFIRFilter20thorder_stat[38];
                                    /* '<S38>/Discrete FIR Filter 20th order' */
  real_T DiscreteFIRFilter20thorder_st_p[38];
                                    /* '<S39>/Discrete FIR Filter 20th order' */
  real_T UnitDelay_DSTATE_bs[2];       /* '<S1>/Unit Delay' */
  real_T DiscreteFIRFilter10thorder_stat[9];
                                     /* '<S9>/Discrete FIR Filter 10th order' */
  real_T FCF_Cnt_DSTATE;               /* '<S1>/FCF_Cnt' */
  real_T DiscreteTransferFcn_tmp;      /* '<S13>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_tmp;     /* '<S13>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn_tmp_g;    /* '<S20>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_tmp_l;   /* '<S20>/Discrete Transfer Fcn1' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S38>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_a;
                                    /* '<S39>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter10thorder_circ;
                                     /* '<S9>/Discrete FIR Filter 10th order' */
  boolean_T AutoSwitchHysteresis_Mode; /* '<S5>/AutoSwitchHysteresis' */
} DW_FOC_fastCTRL_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T U_DCV;                        /* '<Root>/U_DC [V]' */
  real_T I_phA[6];                     /* '<Root>/I_ph [A]' */
  real_T I_dq_RefA[2];                 /* '<Root>/I_dq_Ref [A]' */
  real_T phi_elrad;                    /* '<Root>/phi_el [rad]' */
  real_T FOC_Mode;                     /* '<Root>/FOC_Mode' */
  real_T FOC_Enable;                   /* '<Root>/FOC_Enable' */
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

/* Parameters (default storage) */
struct P_FOC_fastCTRL_T_ {
  real_T DutyCycle_1;                  /* Variable: DutyCycle_1
                                        * Referenced by: '<S2>/DutyCycle1_ManualMode'
                                        */
  real_T DutyCycle_2;                  /* Variable: DutyCycle_2
                                        * Referenced by: '<S2>/DutyCycle2_ManualMode'
                                        */
  real_T DutyCycle_3;                  /* Variable: DutyCycle_3
                                        * Referenced by: '<S2>/DutyCycle3_ManualMode'
                                        */
  real_T DutyCycle_4;                  /* Variable: DutyCycle_4
                                        * Referenced by: '<S2>/DutyCycle4_ManualMode'
                                        */
  real_T DutyCycle_5;                  /* Variable: DutyCycle_5
                                        * Referenced by: '<S2>/DutyCycle5_ManualMode'
                                        */
  real_T DutyCycle_6;                  /* Variable: DutyCycle_6
                                        * Referenced by: '<S2>/DutyCycle6_ManualMode'
                                        */
  real_T FOC_6ph_AngleShift;           /* Variable: FOC_6ph_AngleShift
                                        * Referenced by:
                                        *   '<S5>/FOC_6ph_AngleShift'
                                        *   '<S6>/FOC_6ph_AngleShift'
                                        *   '<S7>/FOC_6ph_AngleShift'
                                        */
  real_T FOC_AKS_Mode;                 /* Variable: FOC_AKS_Mode
                                        * Referenced by: '<S2>/FOC_AKS_Mode'
                                        */
  real_T FOC_AngleEst_AutoSwitch_wel_off;
                                    /* Variable: FOC_AngleEst_AutoSwitch_wel_off
                                     * Referenced by: '<S5>/AutoSwitchHysteresis'
                                     */
  real_T FOC_AngleEst_AutoSwitch_wel_on;
                                     /* Variable: FOC_AngleEst_AutoSwitch_wel_on
                                      * Referenced by: '<S5>/AutoSwitchHysteresis'
                                      */
  real_T FOC_AngleEst_Delay1;          /* Variable: FOC_AngleEst_Delay1
                                        * Referenced by:
                                        *   '<S14>/FOC_AngleEst_Delay1'
                                        *   '<S21>/FOC_AngleEst_Delay1'
                                        */
  real_T FOC_AngleEst_Delay2;          /* Variable: FOC_AngleEst_Delay2
                                        * Referenced by:
                                        *   '<S14>/FOC_AngleEst_Delay2'
                                        *   '<S21>/FOC_AngleEst_Delay2'
                                        */
  real_T FOC_AngleEst_Komp_KP;         /* Variable: FOC_AngleEst_Komp_KP
                                        * Referenced by:
                                        *   '<S3>/komp_kp'
                                        *   '<S4>/komp_kp'
                                        */
  real_T FOC_AngleEst_Lq;              /* Variable: FOC_AngleEst_Lq
                                        * Referenced by:
                                        *   '<S3>/FOC_AngleEst_Lq'
                                        *   '<S4>/FOC_AngleEst_Lq'
                                        */
  real_T FOC_AngleEst_Psi_InitVal;     /* Variable: FOC_AngleEst_Psi_InitVal
                                        * Referenced by:
                                        *   '<S15>/Unit Delay'
                                        *   '<S22>/Unit Delay'
                                        */
  real_T FOC_AngleEst_Rs;              /* Variable: FOC_AngleEst_Rs
                                        * Referenced by:
                                        *   '<S3>/FOC_AngleEst_Rs'
                                        *   '<S4>/FOC_AngleEst_Rs'
                                        */
  real_T FOC_AngleEst_w_el_filtered_Tau;
                                     /* Variable: FOC_AngleEst_w_el_filtered_Tau
                                      * Referenced by:
                                      *   '<S12>/Tau'
                                      *   '<S19>/Tau'
                                      */
  real_T FOC_AngleObs_w_InitVal;       /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S33>/Unit Delay1'
                                        */
  real_T FOC_AngleObserver_D;          /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S26>/Constant1'
                                        */
  real_T FOC_AngleObserver_w0;         /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S26>/Constant'
                                        */
  real_T FOC_Enable;                   /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
  real_T FOC_IntegDamp;                /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S41>/FOC_IntegDamp'
                                        *   '<S45>/FOC_IntegDamp'
                                        */
  real_T FOC_KI;                       /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S41>/FOC_KI'
                                        *   '<S45>/FOC_KI'
                                        */
  real_T FOC_KP;                       /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S41>/FOC_KP1'
                                        *   '<S45>/FOC_KP1'
                                        */
  real_T FOC_MANUAL_U_DC;              /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc1'
                                        */
  real_T FOC_MaxModInd;                /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S40>/FOC_MaxModInd'
                                        *   '<S44>/FOC_MaxModInd'
                                        */
  real_T FOC_Mode_Intern;              /* Variable: FOC_Mode_Intern
                                        * Referenced by: '<S1>/FOC_Mode_Intern'
                                        */
  real_T FOC_OmegaObs3;                /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S26>/Gain4'
                                        */
  real_T FOC_PhiSensorTdead;           /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S26>/Constant2'
                                        */
  real_T FOC_PhiSensorTdead_AngleEst;  /* Variable: FOC_PhiSensorTdead_AngleEst
                                        * Referenced by: '<S26>/Constant3'
                                        */
  real_T FOC_SELECT_AngleAdaption2PolePairs;
                                 /* Variable: FOC_SELECT_AngleAdaption2PolePairs
                                  * Referenced by: '<S5>/Constant2'
                                  */
  real_T FOC_SELECT_AngleAdaptionRange;
                                      /* Variable: FOC_SELECT_AngleAdaptionRange
                                       * Referenced by: '<S5>/Constant4'
                                       */
  real_T FOC_SELECT_AngleEst;          /* Variable: FOC_SELECT_AngleEst
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T FOC_SELECT_AngleEst_AutoSwitch;
                                     /* Variable: FOC_SELECT_AngleEst_AutoSwitch
                                      * Referenced by: '<S5>/Constant5'
                                      */
  real_T FOC_SELECT_AngleEst_w_el_filtered;
                                  /* Variable: FOC_SELECT_AngleEst_w_el_filtered
                                   * Referenced by:
                                   *   '<S3>/useFilteredCorrection'
                                   *   '<S4>/useFilteredCorrection'
                                   */
  real_T FOC_SELECT_InvertAngle;       /* Variable: FOC_SELECT_InvertAngle
                                        * Referenced by: '<S5>/FOC_Invert_Encoder'
                                        */
  real_T FOC_SELECT_Mode_Intern;       /* Variable: FOC_SELECT_Mode_Intern
                                        * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
                                        */
  real_T FOC_SELECT_Modulation;        /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S8>/Enable_SuperSinMod'
                                        */
  real_T FOC_SELECT_U_DC_INPUT;        /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
  real_T FOC_SELECT_phi;               /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real_T FOC_Uf_U_max;                 /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S49>/Saturation1'
                                        */
  real_T FOC_Uf_U_min;                 /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S49>/Saturation1'
                                        */
  real_T FOC_Uf_Ud;                    /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S7>/Uf_Ud'
                                        */
  real_T FOC_Uf_f_el;                  /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S7>/Uf_w_el'
                                        */
  real_T FOC_Uf_m;                     /* Variable: FOC_Uf_m
                                        * Referenced by: '<S49>/Gain'
                                        */
  real_T FOC_f_fastCTRL;               /* Variable: FOC_f_fastCTRL
                                        * Referenced by:
                                        *   '<S5>/FOC_T_fast'
                                        *   '<S12>/FOC_f_fast'
                                        *   '<S13>/FOC_f_fastCTRL'
                                        *   '<S13>/FOC_f_fastCTRL1'
                                        *   '<S15>/FOC_T_fast'
                                        *   '<S19>/FOC_f_fast'
                                        *   '<S20>/FOC_f_fastCTRL'
                                        *   '<S20>/FOC_f_fastCTRL1'
                                        *   '<S22>/FOC_T_fast'
                                        *   '<S26>/FOC_T_fast'
                                        *   '<S48>/FOC_T_fast'
                                        *   '<S33>/FOC_T_fast'
                                        *   '<S34>/FOC_T_fast'
                                        *   '<S41>/FOC_T_fast'
                                        *   '<S45>/FOC_T_fast'
                                        */
  real_T FOC_output_trafo_delay;       /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S5>/FOC_output_trafo_delay'
                                        */
  real_T FOC_phi_offset;               /* Variable: FOC_phi_offset
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T FOC_z_P;                      /* Variable: FOC_z_P
                                        * Referenced by: '<S25>/Anpassung der Signalfrequenz an Polpaarzahl'
                                        */
  real_T Factor_OmegaRot;              /* Variable: Factor_OmegaRot
                                        * Referenced by: '<S26>/Gain5'
                                        */
  real_T Par1;                         /* Variable: Par1
                                        * Referenced by: '<S1>/Par1'
                                        */
  real_T Par2;                         /* Variable: Par2
                                        * Referenced by: '<S1>/Par2'
                                        */
  real_T Par3;                         /* Variable: Par3
                                        * Referenced by: '<S1>/Par3'
                                        */
  real_T Par4;                         /* Variable: Par4
                                        * Referenced by: '<S1>/Par4'
                                        */
  real_T Par5;                         /* Variable: Par5
                                        * Referenced by: '<S1>/Par5'
                                        */
  real_T Par6;                         /* Variable: Par6
                                        * Referenced by: '<S1>/Par6'
                                        */
  real_T Par7;                         /* Variable: Par7
                                        * Referenced by: '<S1>/Par7'
                                        */
  real_T Par8;                         /* Variable: Par8
                                        * Referenced by: '<S1>/Par8'
                                        */
  real_T AntiWindupGT_d_const;         /* Mask Parameter: AntiWindupGT_d_const
                                        * Referenced by: '<S42>/Constant'
                                        */
  real_T AntiWindupGT_q_const;         /* Mask Parameter: AntiWindupGT_q_const
                                        * Referenced by: '<S43>/Constant'
                                        */
  real_T AntiWindupGT_d_const_m;       /* Mask Parameter: AntiWindupGT_d_const_m
                                        * Referenced by: '<S46>/Constant'
                                        */
  real_T AntiWindupGT_q_const_h;       /* Mask Parameter: AntiWindupGT_q_const_h
                                        * Referenced by: '<S47>/Constant'
                                        */
  real_T Factor_Gain;                  /* Expression: 1/2
                                        * Referenced by: '<S53>/Factor'
                                        */
  real_T Factor1_Gain;                 /* Expression: 1/2
                                        * Referenced by: '<S53>/Factor1'
                                        */
  real_T u2_Bias;                      /* Expression: 1
                                        * Referenced by: '<S50>/[0..2]'
                                        */
  real_T u1_Gain;                      /* Expression: 1/2
                                        * Referenced by: '<S50>/[0..1]'
                                        */
  real_T Limit01_UpperSat;             /* Expression: 1
                                        * Referenced by: '<S50>/Limit [0..1]'
                                        */
  real_T Limit01_LowerSat;             /* Expression: 0
                                        * Referenced by: '<S50>/Limit [0..1]'
                                        */
  real_T AKS_LS_Value[6];              /* Expression: [0 0 0 0 0 0]
                                        * Referenced by: '<S2>/AKS_LS'
                                        */
  real_T AKS_HS_Value[6];              /* Expression: [1 1 1 1 1 1]
                                        * Referenced by: '<S2>/AKS_HS'
                                        */
  real_T AKS_LSHS_Value[6];            /* Expression: [0.5 0.5 0.5 0.5 0.5 0.5]
                                        * Referenced by: '<S2>/AKS_LSHS'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S10>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 2*pi
                                        * Referenced by: '<S10>/Constant3'
                                        */
  real_T Constant1_Value;              /* Expression: -2*pi
                                        * Referenced by: '<S10>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S10>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: 2*pi
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Bias_Bias;                    /* Expression: -2*pi
                                        * Referenced by: '<S13>/Bias'
                                        */
  real_T Constant1_Value_i;            /* Expression: 1
                                        * Referenced by: '<S3>/Constant1'
                                        */
  real_T Constant2_Value_l;            /* Expression: -1
                                        * Referenced by: '<S3>/Constant2'
                                        */
  real_T Constant2_Value_d;            /* Expression: 0
                                        * Referenced by: '<S17>/Constant2'
                                        */
  real_T Constant3_Value_b;            /* Expression: 2*pi
                                        * Referenced by: '<S17>/Constant3'
                                        */
  real_T Constant1_Value_f;            /* Expression: -2*pi
                                        * Referenced by: '<S17>/Constant1'
                                        */
  real_T Constant_Value_c;             /* Expression: 0
                                        * Referenced by: '<S17>/Constant'
                                        */
  real_T Constant_Value_o;             /* Expression: 2*pi
                                        * Referenced by: '<S18>/Constant'
                                        */
  real_T Bias_Bias_m;                  /* Expression: -2*pi
                                        * Referenced by: '<S20>/Bias'
                                        */
  real_T Constant1_Value_l;            /* Expression: 1
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Constant2_Value_o;            /* Expression: -1
                                        * Referenced by: '<S4>/Constant2'
                                        */
  real_T Constant_Value_k;             /* Expression: 2*pi
                                        * Referenced by: '<S31>/Constant'
                                        */
  real_T Constant1_Value_b;            /* Expression: 2*pi
                                        * Referenced by: '<S31>/Constant1'
                                        */
  real_T Switch1_Threshold;            /* Expression: 2*pi
                                        * Referenced by: '<S31>/Switch1'
                                        */
  real_T Switch2_Threshold;            /* Expression: 0
                                        * Referenced by: '<S31>/Switch2'
                                        */
  real_T Constant5_Value;              /* Expression: -2*pi
                                        * Referenced by: '<S32>/Constant5'
                                        */
  real_T Constant6_Value;              /* Expression: 0
                                        * Referenced by: '<S32>/Constant6'
                                        */
  real_T Constant2_Value_m;            /* Expression: 2*pi
                                        * Referenced by: '<S32>/Constant2'
                                        */
  real_T Constant4_Value;              /* Expression: 0
                                        * Referenced by: '<S32>/Constant4'
                                        */
  real_T Constant_Value_n;             /* Expression: 2*pi
                                        * Referenced by: '<S27>/Constant'
                                        */
  real_T Constant_Value_l;             /* Expression: 2*pi
                                        * Referenced by: '<S28>/Constant'
                                        */
  real_T Constant1_Value_o;            /* Expression: 2*pi
                                        * Referenced by: '<S28>/Constant1'
                                        */
  real_T Constant_Value_lk;            /* Expression: 2*pi
                                        * Referenced by: '<S29>/Constant'
                                        */
  real_T Constant1_Value_p;            /* Expression: 2*pi
                                        * Referenced by: '<S29>/Constant1'
                                        */
  real_T Constant_Value_f;             /* Expression: 2*pi
                                        * Referenced by: '<S30>/Constant'
                                        */
  real_T Constant1_Value_c;            /* Expression: 2*pi
                                        * Referenced by: '<S30>/Constant1'
                                        */
  real_T IntegStopSwitch3_Threshold;   /* Expression: 0
                                        * Referenced by: '<S41>/IntegStopSwitch3'
                                        */
  real_T IntegStopSwitch3_Threshold_p; /* Expression: 0
                                        * Referenced by: '<S45>/IntegStopSwitch3'
                                        */
  real_T Zero_Value;                   /* Expression: 0
                                        * Referenced by: '<S41>/Zero'
                                        */
  real_T Zero_Value_j;                 /* Expression: 0
                                        * Referenced by: '<S45>/Zero'
                                        */
  real_T Gain1_Gain;                   /* Expression: 2*pi
                                        * Referenced by: '<S48>/Gain1'
                                        */
  real_T Constant1_Value_l0;           /* Expression: 0
                                        * Referenced by: '<S48>/Constant1'
                                        */
  real_T Constant2_Value_e;            /* Expression: 1
                                        * Referenced by: '<S51>/Constant2'
                                        */
  real_T U_DC2_Gain;                   /* Expression: 1/2
                                        * Referenced by: '<S51>/U_DC//2'
                                        */
  real_T ModInd_1_Gain;                /* Expression: 1
                                        * Referenced by: '<S51>/ModInd_1'
                                        */
  real_T ModInd_2_Gain;                /* Expression: 1
                                        * Referenced by: '<S51>/ModInd_2'
                                        */
  real_T Constant2_Value_mf;           /* Expression: 1
                                        * Referenced by: '<S52>/Constant2'
                                        */
  real_T U_DC2_Gain_k;                 /* Expression: 1/2
                                        * Referenced by: '<S52>/U_DC//2'
                                        */
  real_T Constant_Value_i[6];/* Expression: [1,0;-0.5,sqrt(3)/2;-0.5,-sqrt(3)/2]
                              * Referenced by: '<S54>/Constant'
                              */
  real_T Null_Value[6];                /* Expression: [0;0;0;0;0;0]
                                        * Referenced by: '<S1>/Null'
                                        */
  real_T DiscreteTransferFcn_NumCoef;  /* Expression: [1-0.995]
                                        * Referenced by: '<S7>/Discrete Transfer Fcn'
                                        */
  real_T DiscreteTransferFcn_DenCoef[2];/* Expression: [1 -0.995]
                                         * Referenced by: '<S7>/Discrete Transfer Fcn'
                                         */
  real_T DiscreteTransferFcn_InitialStat;/* Expression: 0
                                          * Referenced by: '<S7>/Discrete Transfer Fcn'
                                          */
  real_T f_2_w_el_Gain;                /* Expression: 2*pi
                                        * Referenced by: '<S7>/f_2_w_el'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S48>/Unit Delay'
                                        */
  real_T TrafoMatrixuvwalphabeta_Gain[6];
                         /* Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3
                          * Referenced by: '<S38>/TrafoMatrix uvw->alphabeta'
                          */
  real_T AutoSwitchHysteresis_YOn;     /* Expression: 1
                                        * Referenced by: '<S5>/AutoSwitchHysteresis'
                                        */
  real_T AutoSwitchHysteresis_YOff;    /* Expression: 0
                                        * Referenced by: '<S5>/AutoSwitchHysteresis'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S25>/Switch'
                                        */
  real_T ResolverOffsetLimitation_UpperS;/* Expression: 2*pi
                                          * Referenced by: '<S5>/ResolverOffsetLimitation'
                                          */
  real_T ResolverOffsetLimitation_LowerS;/* Expression: 0
                                          * Referenced by: '<S5>/ResolverOffsetLimitation'
                                          */
  real_T Switch_Phi_Threshold;         /* Expression: 0
                                        * Referenced by: '<S11>/Switch_Phi'
                                        */
  real_T UnitDelay_InitialCondition_g; /* Expression: 0
                                        * Referenced by: '<S12>/Unit Delay'
                                        */
  real_T DiscreteTransferFcn_NumCoef_o[2];/* Expression: [1 -1]
                                           * Referenced by: '<S13>/Discrete Transfer Fcn'
                                           */
  real_T DiscreteTransferFcn_DenCoef_o[2];/* Expression: [1 0]
                                           * Referenced by: '<S13>/Discrete Transfer Fcn'
                                           */
  real_T DiscreteTransferFcn_InitialSt_b;/* Expression: 0
                                          * Referenced by: '<S13>/Discrete Transfer Fcn'
                                          */
  real_T Constant_Value_h;             /* Expression: 3/2*pi
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Constant1_Value_g;            /* Expression: 1/2*pi
                                        * Referenced by: '<S13>/Constant1'
                                        */
  real_T Constant2_Value_ej;           /* Expression: pi
                                        * Referenced by: '<S13>/Constant2'
                                        */
  real_T DiscreteTransferFcn1_NumCoef[2];/* Expression: [1 -1]
                                          * Referenced by: '<S13>/Discrete Transfer Fcn1'
                                          */
  real_T DiscreteTransferFcn1_DenCoef[2];/* Expression: [1 0]
                                          * Referenced by: '<S13>/Discrete Transfer Fcn1'
                                          */
  real_T DiscreteTransferFcn1_InitialSta;/* Expression: 0
                                          * Referenced by: '<S13>/Discrete Transfer Fcn1'
                                          */
  real_T Switch2_Threshold_b;          /* Expression: 0
                                        * Referenced by: '<S3>/Switch2'
                                        */
  real_T Switch_Threshold_l;           /* Expression: 0
                                        * Referenced by: '<S3>/Switch'
                                        */
  real_T Constant_Value_b;             /* Expression: pi/2
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Switch2_Threshold_g;          /* Expression: 2*pi
                                        * Referenced by: '<S10>/Switch2'
                                        */
  real_T Switch1_Threshold_m;          /* Expression: 0
                                        * Referenced by: '<S10>/Switch1'
                                        */
  real_T Switch1_Threshold_o;          /* Expression: 2*pi
                                        * Referenced by: '<S30>/Switch1'
                                        */
  real_T Switch2_Threshold_l;          /* Expression: 0
                                        * Referenced by: '<S30>/Switch2'
                                        */
  real_T UnitDelay_InitialCondition_n; /* Expression: 0
                                        * Referenced by: '<S32>/Unit Delay'
                                        */
  real_T Constant3_Value_g;            /* Expression: -pi
                                        * Referenced by: '<S32>/Constant3'
                                        */
  real_T Constant1_Value_oz;           /* Expression: pi
                                        * Referenced by: '<S32>/Constant1'
                                        */
  real_T UnitDelay3_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S26>/Unit Delay3'
                                        */
  real_T Switch1_Threshold_a;          /* Expression: 2*pi
                                        * Referenced by: '<S28>/Switch1'
                                        */
  real_T Switch2_Threshold_gc;         /* Expression: 0
                                        * Referenced by: '<S28>/Switch2'
                                        */
  real_T IntegDelay1_InitialCondition; /* Expression: 0
                                        * Referenced by: '<S41>/IntegDelay1'
                                        */
  real_T TrafoMatrixuvwalphabeta_Gain_m[6];
                         /* Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3
                          * Referenced by: '<S39>/TrafoMatrix uvw->alphabeta'
                          */
  real_T IntegDelay1_InitialCondition_a;/* Expression: 0
                                         * Referenced by: '<S45>/IntegDelay1'
                                         */
  real_T Switch1_Threshold_p;          /* Expression: 2*pi
                                        * Referenced by: '<S29>/Switch1'
                                        */
  real_T Switch2_Threshold_d;          /* Expression: 0
                                        * Referenced by: '<S29>/Switch2'
                                        */
  real_T Gain1_Gain_p[4];              /* Expression: [0,-1;1,0]
                                        * Referenced by: '<S56>/Gain1'
                                        */
  real_T Gain_Gain[4];                 /* Expression: [1,0;0,1]
                                        * Referenced by: '<S56>/Gain'
                                        */
  real_T Constant_Value_a[6];/* Expression: [1,0;-0.5,sqrt(3)/2;-0.5,-sqrt(3)/2]
                              * Referenced by: '<S55>/Constant'
                              */
  real_T Gain1_Gain_k[4];              /* Expression: [0,-1;1,0]
                                        * Referenced by: '<S57>/Gain1'
                                        */
  real_T Gain_Gain_d[4];               /* Expression: [1,0;0,1]
                                        * Referenced by: '<S57>/Gain'
                                        */
  real_T Switch1_Threshold_l;          /* Expression: 0
                                        * Referenced by: '<S1>/Switch1'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S3>/Gain2'
                                        */
  real_T Gain3_Gain;                   /* Expression: 1
                                        * Referenced by: '<S3>/Gain3'
                                        */
  real_T Gain4_Gain;                   /* Expression: 1
                                        * Referenced by: '<S3>/Gain4'
                                        */
  real_T Constant_Value_e;             /* Expression: 1
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T UnitDelay_InitialCondition_a; /* Expression: 0
                                        * Referenced by: '<S14>/Unit Delay'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S14>/Unit Delay1'
                                        */
  real_T Switch4_Threshold;            /* Expression: 0.5
                                        * Referenced by: '<S14>/Switch4'
                                        */
  real_T Switch3_Threshold;            /* Expression: 0.5
                                        * Referenced by: '<S14>/Switch3'
                                        */
  real_T Switch_Phi_Threshold_m;       /* Expression: 0
                                        * Referenced by: '<S18>/Switch_Phi'
                                        */
  real_T UnitDelay_InitialCondition_nf;/* Expression: 0
                                        * Referenced by: '<S19>/Unit Delay'
                                        */
  real_T DiscreteTransferFcn_NumCoef_i[2];/* Expression: [1 -1]
                                           * Referenced by: '<S20>/Discrete Transfer Fcn'
                                           */
  real_T DiscreteTransferFcn_DenCoef_a[2];/* Expression: [1 0]
                                           * Referenced by: '<S20>/Discrete Transfer Fcn'
                                           */
  real_T DiscreteTransferFcn_InitialSt_o;/* Expression: 0
                                          * Referenced by: '<S20>/Discrete Transfer Fcn'
                                          */
  real_T Constant_Value_ip;            /* Expression: 3/2*pi
                                        * Referenced by: '<S20>/Constant'
                                        */
  real_T Constant1_Value_e;            /* Expression: 1/2*pi
                                        * Referenced by: '<S20>/Constant1'
                                        */
  real_T Constant2_Value_eji;          /* Expression: pi
                                        * Referenced by: '<S20>/Constant2'
                                        */
  real_T DiscreteTransferFcn1_NumCoef_b[2];/* Expression: [1 -1]
                                            * Referenced by: '<S20>/Discrete Transfer Fcn1'
                                            */
  real_T DiscreteTransferFcn1_DenCoef_f[2];/* Expression: [1 0]
                                            * Referenced by: '<S20>/Discrete Transfer Fcn1'
                                            */
  real_T DiscreteTransferFcn1_InitialS_h;/* Expression: 0
                                          * Referenced by: '<S20>/Discrete Transfer Fcn1'
                                          */
  real_T Switch2_Threshold_p;          /* Expression: 0
                                        * Referenced by: '<S4>/Switch2'
                                        */
  real_T Switch_Threshold_j;           /* Expression: 0
                                        * Referenced by: '<S4>/Switch'
                                        */
  real_T Constant_Value_cr;            /* Expression: pi/2
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Switch2_Threshold_f;          /* Expression: 2*pi
                                        * Referenced by: '<S17>/Switch2'
                                        */
  real_T Switch1_Threshold_l3;         /* Expression: 0
                                        * Referenced by: '<S17>/Switch1'
                                        */
  real_T Constant_Value_n2;            /* Expression: 1
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T UnitDelay_InitialCondition_gn;/* Expression: 0
                                        * Referenced by: '<S21>/Unit Delay'
                                        */
  real_T UnitDelay1_InitialCondition_j;/* Expression: 0
                                        * Referenced by: '<S21>/Unit Delay1'
                                        */
  real_T Switch4_Threshold_a;          /* Expression: 0.5
                                        * Referenced by: '<S21>/Switch4'
                                        */
  real_T Switch3_Threshold_o;          /* Expression: 0.5
                                        * Referenced by: '<S21>/Switch3'
                                        */
  real_T phi_est_2_Gain;               /* Expression: 1
                                        * Referenced by: '<S4>/phi_est_2'
                                        */
  real_T Constant_Value_nb;            /* Expression: 2*pi
                                        * Referenced by: '<S25>/Constant'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 2
                                        * Referenced by: '<S26>/Gain'
                                        */
  real_T UnitDelay1_InitialCondition_o;/* Expression: 0
                                        * Referenced by: '<S34>/Unit Delay1'
                                        */
  real_T dummy_gain_Gain;              /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain'
                                        */
  real_T dummy_gain1_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain1'
                                        */
  real_T dummy_gain2_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain2'
                                        */
  real_T dummy_gain3_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain3'
                                        */
  real_T dummy_gain4_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain4'
                                        */
  real_T dummy_gain5_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain5'
                                        */
  real_T dummy_gain6_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain6'
                                        */
  real_T dummy_gain7_Gain;             /* Expression: 1
                                        * Referenced by: '<S5>/dummy_gain7'
                                        */
  real_T I_ph_RMS_Gain;                /* Expression: 1/sqrt(2)
                                        * Referenced by: '<S35>/I_ph_RMS'
                                        */
  real_T Zero1_Value[2];               /* Expression: [0,0]
                                        * Referenced by: '<S41>/Zero1'
                                        */
  real_T I_d_Ref_Gain;                 /* Expression: 1
                                        * Referenced by: '<S36>/I_d_Ref'
                                        */
  real_T I_q_Ref_Gain;                 /* Expression: 1
                                        * Referenced by: '<S36>/I_q_Ref'
                                        */
  real_T Zero1_Value_e[2];             /* Expression: [0,0]
                                        * Referenced by: '<S45>/Zero1'
                                        */
  real_T I_d_Act_1_Gain;               /* Expression: 1
                                        * Referenced by: '<S38>/I_d_Act_1'
                                        */
  real_T I_q_Act_1_Gain;               /* Expression: 1
                                        * Referenced by: '<S38>/I_q_Act_1'
                                        */
  real_T I_u_1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S38>/I_u_1'
                                        */
  real_T I_v_1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S38>/I_v_1'
                                        */
  real_T I_w_1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S38>/I_w_1'
                                        */
  real_T DiscreteFIRFilter20thorder_Init;/* Expression: 0
                                          * Referenced by: '<S38>/Discrete FIR Filter 20th order'
                                          */
  real_T DiscreteFIRFilter20thorder_Coef[20];
                   /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
                    * Referenced by: '<S38>/Discrete FIR Filter 20th order'
                    */
  real_T Gain5_Gain;                   /* Expression: 1
                                        * Referenced by: '<S38>/Gain5'
                                        */
  real_T Gain6_Gain;                   /* Expression: 1
                                        * Referenced by: '<S38>/Gain6'
                                        */
  real_T DiscreteFIRFilter20thorder_In_p;/* Expression: 0
                                          * Referenced by: '<S39>/Discrete FIR Filter 20th order'
                                          */
  real_T DiscreteFIRFilter20thorder_Co_f[20];
                   /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
                    * Referenced by: '<S39>/Discrete FIR Filter 20th order'
                    */
  real_T I_d_Act_2_Gain;               /* Expression: 1
                                        * Referenced by: '<S39>/I_d_Act_2'
                                        */
  real_T I_d_Act_filt_2_Gain;          /* Expression: 1
                                        * Referenced by: '<S39>/I_d_Act_filt_2'
                                        */
  real_T I_q_Act_2_Gain;               /* Expression: 1
                                        * Referenced by: '<S39>/I_q_Act_2'
                                        */
  real_T I_q_Act_filt_2_Gain;          /* Expression: 1
                                        * Referenced by: '<S39>/I_q_Act_filt_2'
                                        */
  real_T I_u_2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S39>/I_u_2'
                                        */
  real_T I_v_2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S39>/I_v_2'
                                        */
  real_T I_w_2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S39>/I_w_2'
                                        */
  real_T Switch_Threshold_e;           /* Expression: 2*pi
                                        * Referenced by: '<S48>/Switch'
                                        */
  real_T UnitDelay_InitialCondition_l; /* Expression: 0
                                        * Referenced by: '<S1>/Unit Delay'
                                        */
  real_T U_d_1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S56>/U_d_1'
                                        */
  real_T U_q_1_Gain;                   /* Expression: 1
                                        * Referenced by: '<S56>/U_q_1'
                                        */
  real_T U_d_2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S57>/U_d_2'
                                        */
  real_T U_q_2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S57>/U_q_2'
                                        */
  real_T DiscreteFIRFilter10thorder_Init;/* Expression: 0
                                          * Referenced by: '<S9>/Discrete FIR Filter 10th order'
                                          */
  real_T DiscreteFIRFilter10thorder_Coef[10];/* Expression: 1/10*[1 1 1 1 1 1 1 1 1 1]
                                              * Referenced by: '<S9>/Discrete FIR Filter 10th order'
                                              */
  real_T Manipulate_FOC_Error_Value;   /* Expression: 0
                                        * Referenced by: '<S1>/Manipulate_FOC_Error'
                                        */
  real_T Counter_Start_Value;          /* Expression: 1
                                        * Referenced by: '<S1>/Counter_Start'
                                        */
  real_T FCF_Cnt_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S1>/FCF_Cnt'
                                        */
  real_T Gain_Gain_m;                  /* Expression: 1
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain1_Gain_m;                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Gain2_Gain_i;                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Gain3_Gain_o;                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain3'
                                        */
  real_T Gain4_Gain_l;                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain4'
                                        */
  real_T Gain5_Gain_o;                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain5'
                                        */
  real_T Gain6_Gain_o;                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain6'
                                        */
  real_T Gain7_Gain;                   /* Expression: 1
                                        * Referenced by: '<S1>/Gain7'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_FOC_fastCTRL_T {
  const char_T * volatile errorStatus;
  B_FOC_fastCTRL_T *blockIO;
  ExtU_FOC_fastCTRL_T *inputs;
  ExtY_FOC_fastCTRL_T *outputs;
  DW_FOC_fastCTRL_T *dwork;
};

/* Block parameters (default storage) */
extern P_FOC_fastCTRL_T FOC_fastCTRL_P;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T Phi_Observer;            /* '<S26>/Sum7' */
extern real_T FOC_U_DC;                /* '<S1>/Switch1' */
extern real_T FOC_AngleEst_w_el;       /* '<S3>/Gain2' */
extern real_T FOC_AngleEst_Psi_PM_alpha;/* '<S3>/Gain3' */
extern real_T FOC_AngleEst_Psi_PM_beta;/* '<S3>/Gain4' */
extern real_T w_el;                    /* '<S5>/dummy_gain' */
extern real_T Phi_el_I_Transformation; /* '<S5>/dummy_gain1' */
extern real_T Phi_el_U_Transformation; /* '<S5>/dummy_gain2' */
extern real_T Phi_Measured_Raw;        /* '<S5>/dummy_gain3' */
extern real_T Phi_est_error_I_Trafo;   /* '<S5>/dummy_gain4' */
extern real_T Phi_est;                 /* '<S5>/dummy_gain5' */
extern real_T Phi_AngleEst_AutoSwitch; /* '<S5>/dummy_gain6' */
extern real_T Phi_est_error;           /* '<S5>/dummy_gain7' */
extern real_T FCF_Cnt;                 /* '<S1>/FCF_Cnt' */

/* Model entry point functions */
extern void FOC_fastCTRL_initialize(RT_MODEL_FOC_fastCTRL_T *const
  FOC_fastCTRL_M);
extern void FOC_fastCTRL_step(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M);
extern void FOC_fastCTRL_terminate(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M);

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
