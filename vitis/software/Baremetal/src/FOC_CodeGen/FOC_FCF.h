/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.h
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.21
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Jan 16 11:31:17 2026
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
  real32_T ModeSwitch;                 /* '<S1>/ModeSwitch' */
  real32_T U_DC_fcf;                   /* '<S1>/Switch1' */
  real32_T Abs[9];                     /* '<S8>/Abs' */
  real32_T MinMax;                     /* '<S8>/MinMax' */
  real32_T DiscreteTransferFcn;        /* '<S11>/Discrete Transfer Fcn' */
  real32_T f_2_w_el;                   /* '<S11>/f_2_w_el' */
  real32_T Product;                    /* '<S48>/Product' */
  real32_T UnitDelay;                  /* '<S48>/Unit Delay' */
  real32_T Add;                        /* '<S48>/Add' */
  real32_T TrafoMatrixuvwalphabeta[2]; /* '<S22>/TrafoMatrix uvw->alphabeta' */
  real32_T ResolverOffsetLimitation;   /* '<S3>/ResolverOffsetLimitation' */
  real32_T Sum1;                       /* '<S3>/Sum1' */
  real32_T w_el;                       /* '<S16>/Unit Delay1' */
  real32_T DeadTimeCompensation;       /* '<S13>/DeadTimeCompensation' */
  real32_T Sum3;                       /* '<S13>/Sum3' */
  real32_T UnitDelay_l;                /* '<S15>/Unit Delay' */
  real32_T Sum;                        /* '<S15>/Sum' */
  real32_T Switch;                     /* '<S15>/Switch' */
  real32_T Switch1;                    /* '<S15>/Switch1' */
  real32_T Sum2;                       /* '<S15>/Sum2' */
  real32_T UnitDelay3;                 /* '<S13>/Unit Delay3' */
  real32_T phi_el_observer;            /* '<S13>/Sum7' */
  real32_T Product_e;                  /* '<S10>/Product' */
  real32_T UnitDelay_a;                /* '<S10>/Unit Delay' */
  real32_T Add_m;                      /* '<S10>/Add' */
  real32_T f_2_w_el_b;                 /* '<S7>/f_2_w_el' */
  real32_T Product_h;                  /* '<S37>/Product' */
  real32_T UnitDelay_j;                /* '<S37>/Unit Delay' */
  real32_T Add_mp;                     /* '<S37>/Add' */
  real32_T Use_If_Mode[2];             /* '<S1>/Use_If_Mode' */
  real32_T TrigonometricFunction1;     /* '<S22>/Trigonometric Function1' */
  real32_T TrafoProd;                  /* '<S22>/TrafoProd' */
  real32_T TrigonometricFunction;      /* '<S22>/Trigonometric Function' */
  real32_T TrafoProd3;                 /* '<S22>/TrafoProd3' */
  real32_T I_d1_Act;                   /* '<S22>/I_d1_Act' */
  real32_T TrafoProd1;                 /* '<S22>/TrafoProd1' */
  real32_T TrafoProd2;                 /* '<S22>/TrafoProd2' */
  real32_T I_q1_Act;                   /* '<S22>/I_q1_Act' */
  real32_T TmpSignalConversionAtDiscreteFI[2];
  real32_T IdqErr[2];                  /* '<S19>/IdqErr' */
  real32_T KPek1[2];                   /* '<S26>/KP*e[k]1' */
  real32_T IntegDelay1[2];             /* '<S26>/IntegDelay1' */
  real32_T Product1;                   /* '<S26>/Product1' */
  real32_T IntegEnaSwitch1[2];         /* '<S26>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_h[2];/* '<S23>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum1_d;                     /* '<S5>/Sum1' */
  real32_T TrigonometricFunction1_b;   /* '<S23>/Trigonometric Function1' */
  real32_T TrafoProd_a;                /* '<S23>/TrafoProd' */
  real32_T TrigonometricFunction_l;    /* '<S23>/Trigonometric Function' */
  real32_T TrafoProd3_i;               /* '<S23>/TrafoProd3' */
  real32_T TrafoSum;                   /* '<S23>/TrafoSum' */
  real32_T TrafoProd1_b;               /* '<S23>/TrafoProd1' */
  real32_T TrafoProd2_b;               /* '<S23>/TrafoProd2' */
  real32_T TrafoSum1;                  /* '<S23>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_k[2];
  real32_T IdqErr_l[2];                /* '<S20>/IdqErr' */
  real32_T KPek1_l[2];                 /* '<S30>/KP*e[k]1' */
  real32_T IntegDelay1_o[2];           /* '<S30>/IntegDelay1' */
  real32_T Product1_k;                 /* '<S30>/Product1' */
  real32_T IntegEnaSwitch1_n[2];       /* '<S30>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_m[2];/* '<S24>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum2_m;                     /* '<S5>/Sum2' */
  real32_T TrigonometricFunction1_k;   /* '<S24>/Trigonometric Function1' */
  real32_T TrafoProd_n;                /* '<S24>/TrafoProd' */
  real32_T TrigonometricFunction_k;    /* '<S24>/Trigonometric Function' */
  real32_T TrafoProd3_o;               /* '<S24>/TrafoProd3' */
  real32_T TrafoSum_n;                 /* '<S24>/TrafoSum' */
  real32_T TrafoProd1_e;               /* '<S24>/TrafoProd1' */
  real32_T TrafoProd2_h;               /* '<S24>/TrafoProd2' */
  real32_T TrafoSum1_p;                /* '<S24>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_c[2];
  real32_T IdqErr_e[2];                /* '<S21>/IdqErr' */
  real32_T KPek1_h[2];                 /* '<S34>/KP*e[k]1' */
  real32_T IntegDelay1_d[2];           /* '<S34>/IntegDelay1' */
  real32_T Product1_b;                 /* '<S34>/Product1' */
  real32_T IntegEnaSwitch1_h[2];       /* '<S34>/IntegEnaSwitch1' */
  real32_T Product_c;                  /* '<S4>/Product' */
  real32_T Sum_k;                      /* '<S4>/Sum' */
  real32_T Switch1_k;                  /* '<S18>/Switch1' */
  real32_T Switch2;                    /* '<S18>/Switch2' */
  real32_T Sum2_p;                     /* '<S4>/Sum2' */
  real32_T Sum1_l;                     /* '<S4>/Sum1' */
  real32_T SelectControlMode[9];       /* '<S1>/SelectControlMode' */
  real32_T TrigonometricFunction_n;    /* '<S58>/Trigonometric Function' */
  real32_T Gain1[4];                   /* '<S58>/Gain1' */
  real32_T TrigonometricFunction1_j;   /* '<S58>/Trigonometric Function1' */
  real32_T Gain[4];                    /* '<S58>/Gain' */
  real32_T Sum1_g[4];                  /* '<S58>/Sum1' */
  real32_T Product_c0[2];              /* '<S58>/Product' */
  real32_T U_uvw1[3];                  /* '<S55>/Product' */
  real32_T TrigonometricFunction_j;    /* '<S59>/Trigonometric Function' */
  real32_T Gain1_i[4];                 /* '<S59>/Gain1' */
  real32_T TrigonometricFunction1_h;   /* '<S59>/Trigonometric Function1' */
  real32_T Gain_f[4];                  /* '<S59>/Gain' */
  real32_T Sum1_f[4];                  /* '<S59>/Sum1' */
  real32_T Product_f[2];               /* '<S59>/Product' */
  real32_T Product_f3[3];              /* '<S56>/Product' */
  real32_T TrigonometricFunction_h;    /* '<S60>/Trigonometric Function' */
  real32_T Gain1_n[4];                 /* '<S60>/Gain1' */
  real32_T TrigonometricFunction1_hh;  /* '<S60>/Trigonometric Function1' */
  real32_T Gain_l[4];                  /* '<S60>/Gain' */
  real32_T Sum1_lz[4];                 /* '<S60>/Sum1' */
  real32_T Product_i[2];               /* '<S60>/Product' */
  real32_T Product_fb[3];              /* '<S57>/Product' */
  real32_T SelMod_DutyCycles[9];       /* '<S12>/SelectModulation' */
  real32_T Scale02[9];                 /* '<S50>/Scale [0..2]' */
  real32_T Scale01[9];                 /* '<S50>/Scale  [0..1]' */
  real32_T Limit01[9];                 /* '<S50>/Limit [0..1]' */
  real32_T Select_GateDriver_Assignment_1[3];
                                    /* '<S53>/Select_GateDriver_Assignment_1' */
  real32_T Select_GateDriver_Assignment_2[3];
                                    /* '<S53>/Select_GateDriver_Assignment_2' */
  real32_T Select_GateDriver_Assignment_3[3];
                                    /* '<S53>/Select_GateDriver_Assignment_3' */
  real32_T Deviation;                  /* '<S13>/Deviation' */
  real32_T Product2;                   /* '<S13>/Product2' */
  real32_T Gain_g;                     /* '<S13>/Gain' */
  real32_T winkelimpuls;               /* '<S13>/Gain4' */
  real32_T Sum1_g4;                    /* '<S13>/Sum1' */
  real32_T Product_o;                  /* '<S13>/Product' */
  real32_T Product1_bi;                /* '<S13>/Product1' */
  real32_T UnitDelay1;                 /* '<S17>/Unit Delay1' */
  real32_T Sum2_mq;                    /* '<S13>/Sum2' */
  real32_T Sum6;                       /* '<S13>/Sum6' */
  real32_T Product_n;                  /* '<S16>/Product' */
  real32_T Sum2_e;                     /* '<S16>/Sum2' */
  real32_T Product_cd;                 /* '<S17>/Product' */
  real32_T Sum2_j;                     /* '<S17>/Sum2' */
  real32_T phi_el_U_trafo[3];          /* '<S4>/Gain1' */
  real32_T IntegStopSwitch2[2];        /* '<S26>/IntegStopSwitch2' */
  real32_T U_d1_CC;                    /* '<S19>/Gain1' */
  real32_T U_q1_CC;                    /* '<S19>/Gain2' */
  real32_T IntegStopSwitch2_o[2];      /* '<S30>/IntegStopSwitch2' */
  real32_T IntegStopSwitch2_h[2];      /* '<S34>/IntegStopSwitch2' */
  real32_T I_dq1_Act_filt[2];       /* '<S22>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder[2];
                                    /* '<S23>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_l[2];
                                    /* '<S24>/Discrete FIR Filter 20th order' */
  real32_T Abs_e;                      /* '<S37>/Abs' */
  real32_T Switch_d;                   /* '<S37>/Switch' */
  real32_T Add1;                       /* '<S37>/Add1' */
  real32_T DataTypeConversion;         /* '<S8>/Data Type Conversion' */
  real32_T FOC_Overcurrent_I_uvw;      /* '<S8>/Gain1' */
  real32_T DataTypeConversion_i;       /* '<S9>/Data Type Conversion' */
  real32_T DataTypeConversion1;        /* '<S9>/Data Type Conversion1' */
  real32_T FOC_Undervoltage_U_DC;      /* '<S9>/Gain1' */
  real32_T FOC_Overvoltage_U_DC;       /* '<S9>/Gain2' */
  real32_T Abs_b;                      /* '<S10>/Abs' */
  real32_T Switch_l;                   /* '<S10>/Switch' */
  real32_T Add1_j;                     /* '<S10>/Add1' */
  real32_T Abs_f;                      /* '<S48>/Abs' */
  real32_T Switch_n;                   /* '<S48>/Switch' */
  real32_T Add1_c;                     /* '<S48>/Add1' */
  real32_T U_d1;                       /* '<S12>/Gain' */
  real32_T U_q1;                       /* '<S12>/Gain1' */
  real32_T U_alpha1;                   /* '<S12>/Gain2' */
  real32_T U_beta1;                    /* '<S12>/Gain3' */
  real32_T DutyCycle_u1;               /* '<S53>/DutyCycle_u1' */
  real32_T DutyCycle_u2;               /* '<S53>/DutyCycle_u2' */
  real32_T DutyCycle_u3;               /* '<S53>/DutyCycle_u3' */
  real32_T DutyCycle_v1;               /* '<S53>/DutyCycle_v1' */
  real32_T DutyCycle_v2;               /* '<S53>/DutyCycle_v2' */
  real32_T DutyCycle_v3;               /* '<S53>/DutyCycle_v3' */
  real32_T DutyCycle_w1;               /* '<S53>/DutyCycle_w1' */
  real32_T DutyCycle_w2;               /* '<S53>/DutyCycle_w2' */
  real32_T DutyCycle_w3;               /* '<S53>/DutyCycle_w3' */
  real32_T FCF_Cnt;                    /* '<S1>/FCF_Cnt' */
  real32_T Sum_o;                      /* '<S1>/Sum' */
  real32_T MinMax2;                    /* '<S54>/MinMax2' */
  real32_T MinMax3;                    /* '<S54>/MinMax3' */
  real32_T Sum1_o;                     /* '<S54>/Sum1' */
  real32_T Factor;                     /* '<S54>/Factor' */
  real32_T DutyCycle_SuperSinus_1[3];  /* '<S54>/DutyCycle_SuperSinus_1' */
  real32_T MinMax1;                    /* '<S54>/MinMax1' */
  real32_T MinMax4;                    /* '<S54>/MinMax4' */
  real32_T Sum2_i;                     /* '<S54>/Sum2' */
  real32_T Factor1;                    /* '<S54>/Factor1' */
  real32_T DutyCycle_SuperSinus_2[3];  /* '<S54>/DutyCycle_SuperSinus_2' */
  real32_T MinMax5;                    /* '<S54>/MinMax5' */
  real32_T MinMax6;                    /* '<S54>/MinMax6' */
  real32_T Sum3_k;                     /* '<S54>/Sum3' */
  real32_T Factor2;                    /* '<S54>/Factor2' */
  real32_T DutyCycle_SuperSinus_3[3];  /* '<S54>/DutyCycle_SuperSinus_3' */
  real32_T U_DC2;                      /* '<S52>/U_DC//2' */
  real32_T AvoidDivBy0;                /* '<S52>/AvoidDivBy0' */
  real32_T DutyCycle_normed[9];        /* '<S52>/DutyCycle_normalized' */
  real32_T U_DC2_l;                    /* '<S51>/U_DC//2' */
  real32_T AvoidDivBy0_f;              /* '<S51>/AvoidDivBy0' */
  real32_T Square[2];                  /* '<S51>/Square' */
  real32_T Sum_kr;                     /* '<S51>/Sum' */
  real32_T Sqrt;                       /* '<S51>/Sqrt' */
  real32_T Square1[2];                 /* '<S51>/Square1' */
  real32_T Sum1_a;                     /* '<S51>/Sum1' */
  real32_T Sqrt1;                      /* '<S51>/Sqrt1' */
  real32_T Square2[2];                 /* '<S51>/Square2' */
  real32_T Sum2_iq;                    /* '<S51>/Sum2' */
  real32_T Sqrt2;                      /* '<S51>/Sqrt2' */
  real32_T ModInd[3];                  /* '<S51>/Divide3' */
  real32_T Sign;                       /* '<S48>/Sign' */
  real32_T Gain1_o;                    /* '<S48>/Gain1' */
  real32_T Use_If_Starter;             /* '<S1>/Use_If_Starter' */
  real32_T Selectphicalc2;             /* '<S3>/Selectphicalc2' */
  real32_T Switch1_d;                  /* '<S14>/Switch1' */
  real32_T Switch2_f;                  /* '<S14>/Switch2' */
  real32_T Sum3_h;                     /* '<S14>/Sum3' */
  real32_T Sum2_l;                     /* '<S14>/Sum2' */
  real32_T Gain_fw;                    /* '<S49>/Gain' */
  real32_T Sign_p;                     /* '<S49>/Sign' */
  real32_T Abs_d;                      /* '<S49>/Abs' */
  real32_T Saturation1;                /* '<S49>/Saturation1' */
  real32_T Product_j;                  /* '<S49>/Product' */
  real32_T Sum1_n;                     /* '<S11>/Sum1' */
  real32_T Sum2_d;                     /* '<S11>/Sum2' */
  real32_T Sign_n;                     /* '<S10>/Sign' */
  real32_T Gain1_h;                    /* '<S10>/Gain1' */
  real32_T Sign_d;                     /* '<S37>/Sign' */
  real32_T Gain1_j;                    /* '<S37>/Gain1' */
  real32_T IntegStopSwitch3[2];        /* '<S34>/IntegStopSwitch3' */
  real32_T IntSum2[2];                 /* '<S34>/IntSum2' */
  real32_T FOC_IntegDamp[2];           /* '<S34>/FOC_IntegDamp' */
  real32_T antiWindupProd[2];          /* '<S33>/antiWindupProd' */
  real32_T IntegStopSwitch1[2];        /* '<S34>/IntegStopSwitch1' */
  real32_T Product2_e[2];              /* '<S34>/Product2' */
  real32_T IntSum1[2];                 /* '<S34>/IntSum1' */
  real32_T IntegStopSwitch3_n[2];      /* '<S30>/IntegStopSwitch3' */
  real32_T IntSum2_f[2];               /* '<S30>/IntSum2' */
  real32_T FOC_IntegDamp_g[2];         /* '<S30>/FOC_IntegDamp' */
  real32_T antiWindupProd_d[2];        /* '<S29>/antiWindupProd' */
  real32_T IntegStopSwitch1_g[2];      /* '<S30>/IntegStopSwitch1' */
  real32_T Product2_b[2];              /* '<S30>/Product2' */
  real32_T IntSum1_l[2];               /* '<S30>/IntSum1' */
  real32_T IntegStopSwitch3_h[2];      /* '<S26>/IntegStopSwitch3' */
  real32_T IntSum2_j[2];               /* '<S26>/IntSum2' */
  real32_T FOC_IntegDamp_c[2];         /* '<S26>/FOC_IntegDamp' */
  real32_T antiWindupProd_o[2];        /* '<S25>/antiWindupProd' */
  real32_T IntegStopSwitch1_f[2];      /* '<S26>/IntegStopSwitch1' */
  real32_T Product2_j[2];              /* '<S26>/Product2' */
  real32_T IntSum1_p[2];               /* '<S26>/IntSum1' */
  real32_T Sum3_d;                     /* '<S18>/Sum3' */
  real32_T Sum2_ez;                    /* '<S18>/Sum2' */
  real32_T ASCSwitch[9];               /* '<S2>/ASC Switch' */
  uint8_T Compare;                     /* '<S36>/Compare' */
  uint8_T Compare_k;                   /* '<S35>/Compare' */
  uint8_T Compare_g;                   /* '<S32>/Compare' */
  uint8_T Compare_i;                   /* '<S31>/Compare' */
  uint8_T Compare_o;                   /* '<S28>/Compare' */
  uint8_T Compare_f;                   /* '<S27>/Compare' */
  boolean_T Compare_b;                 /* '<S42>/Compare' */
  boolean_T LogicalOperator1;          /* '<S1>/Logical Operator1' */
  boolean_T LogicalOperator2;          /* '<S9>/Logical Operator2' */
  boolean_T Selectphicalc3;            /* '<S9>/Selectphicalc3' */
  boolean_T Memory;                    /* '<S45>/Memory' */
  boolean_T Logic[2];                  /* '<S45>/Logic' */
  boolean_T Selectphicalc1;            /* '<S9>/Selectphicalc1' */
  boolean_T Compare_br;                /* '<S43>/Compare' */
  boolean_T Compare_n;                 /* '<S47>/Compare' */
  boolean_T Uk1;                       /* '<S44>/Delay Input1' */
  boolean_T Selectphicalc4;            /* '<S9>/Selectphicalc4' */
  boolean_T Memory_k;                  /* '<S46>/Memory' */
  boolean_T Logic_g[2];                /* '<S46>/Logic' */
  boolean_T Selectphicalc2_m;          /* '<S9>/Selectphicalc2' */
  boolean_T LogicalOperator;           /* '<S9>/Logical Operator' */
  boolean_T Compare_a;                 /* '<S38>/Compare' */
  boolean_T Compare_l;                 /* '<S41>/Compare' */
  boolean_T Uk1_k;                     /* '<S39>/Delay Input1' */
  boolean_T Selectphicalc2_i;          /* '<S8>/Selectphicalc2' */
  boolean_T Memory_p;                  /* '<S40>/Memory' */
  boolean_T Logic_gq[2];               /* '<S40>/Logic' */
  boolean_T Selectphicalc1_j;          /* '<S8>/Selectphicalc1' */
  boolean_T LogicalOperator_n;         /* '<S1>/Logical Operator' */
  boolean_T Compare_lu;                /* '<S6>/Compare' */
  boolean_T Sprung;                    /* '<S15>/Sprung?' */
  boolean_T Sprung1;                   /* '<S15>/Sprung?1' */
  boolean_T FixPtRelationalOperator;   /* '<S44>/FixPt Relational Operator' */
  boolean_T LogicalOperator1_o;        /* '<S9>/Logical Operator1' */
  boolean_T FixPtRelationalOperator_e; /* '<S39>/FixPt Relational Operator' */
  boolean_T AntiWindupLE;              /* '<S33>/AntiWindupLE' */
  boolean_T AntiWindupOR_q;            /* '<S33>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d;            /* '<S33>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_f;            /* '<S29>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_l;          /* '<S29>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_m;          /* '<S29>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_l;            /* '<S25>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_o;          /* '<S25>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_e;          /* '<S25>/AntiWindupOR_d' */
} B_FOC_FCF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTransferFcn_states; /* '<S11>/Discrete Transfer Fcn' */
  real32_T UnitDelay_DSTATE;           /* '<S48>/Unit Delay' */
  real32_T UnitDelay1_DSTATE;          /* '<S16>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_h;         /* '<S15>/Unit Delay' */
  real32_T UnitDelay3_DSTATE;          /* '<S13>/Unit Delay3' */
  real32_T UnitDelay_DSTATE_p;         /* '<S10>/Unit Delay' */
  real32_T UnitDelay_DSTATE_f;         /* '<S37>/Unit Delay' */
  real32_T IntegDelay1_DSTATE[2];      /* '<S26>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_p[2];    /* '<S30>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_h[2];    /* '<S34>/IntegDelay1' */
  real32_T UnitDelay1_DSTATE_i;        /* '<S17>/Unit Delay1' */
  real32_T DiscreteFIRFilter20thorder_stat[38];
                                    /* '<S22>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_g[38];
                                    /* '<S23>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_p[38];
                                    /* '<S24>/Discrete FIR Filter 20th order' */
  real32_T FCF_Cnt_DSTATE;             /* '<S1>/FCF_Cnt' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S22>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_m;
                                    /* '<S23>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_c;
                                    /* '<S24>/Discrete FIR Filter 20th order' */
  boolean_T DelayInput1_DSTATE;        /* '<S44>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_c;      /* '<S39>/Delay Input1' */
  boolean_T Memory_PreviousInput;      /* '<S45>/Memory' */
  boolean_T Memory_PreviousInput_o;    /* '<S46>/Memory' */
  boolean_T Memory_PreviousInput_p;    /* '<S40>/Memory' */
} DW_FOC_FCF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T U_DC;                       /* '<Root>/U_DC [V]' */
  real32_T I_phA[9];                   /* '<Root>/I_ph [A]' */
  real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
  real32_T phi_elrad;                  /* '<Root>/phi_el [rad]' */
  real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
  real32_T FOC_Enable;                 /* '<Root>/FOC_Enable' */
  real32_T w_el_Ref_IfStarter;         /* '<Root>/w_el_Ref_IfStarter' */
  real32_T IfStarter_Active;           /* '<Root>/IfStarter_Active' */
} ExtU_FOC_FCF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T DutyCycles01[9];            /* '<Root>/DutyCycles [0..1]' */
  real32_T I_dq_ActA[6];               /* '<Root>/I_dq_Act [A]' */
  real32_T ModInd[3];                  /* '<Root>/ModInd' */
  real32_T w_elrads;                   /* '<Root>/w_el [rad//s]' */
  real32_T FOC_Error;                  /* '<Root>/FOC_Error' */
} ExtY_FOC_FCF_T;

/* Parameters (default storage) */
struct P_FOC_FCF_T_ {
  real_T FOC_ENABLE_Overcurrent_I_uvw; /* Variable: FOC_ENABLE_Overcurrent_I_uvw
                                        * Referenced by: '<S8>/FOC_ENABLE_Overcurrent_I_uvw1'
                                        */
  real_T FOC_ENABLE_Overvoltage_U_DC;  /* Variable: FOC_ENABLE_Overvoltage_U_DC
                                        * Referenced by: '<S9>/FOC_ENABLE_Overvoltage_U_DC1'
                                        */
  real_T FOC_ENABLE_Undervoltage_U_DC; /* Variable: FOC_ENABLE_Undervoltage_U_DC
                                        * Referenced by: '<S9>/FOC_ENABLE_Undervoltage_U_DC1'
                                        */
  real_T FOC_RESET_OC_Error;           /* Variable: FOC_RESET_OC_Error
                                        * Referenced by: '<S8>/Reset_OC_Error'
                                        */
  real_T FOC_RESET_OV_Error;           /* Variable: FOC_RESET_OV_Error
                                        * Referenced by: '<S9>/Reset_OV_Error'
                                        */
  real32_T FOC_9ph_AngleShift;         /* Variable: FOC_9ph_AngleShift
                                        * Referenced by:
                                        *   '<S4>/FOC_9ph_AngleShift'
                                        *   '<S5>/FOC_9ph_AngleShift'
                                        *   '<S11>/FOC_9ph_AngleShift'
                                        */
  real32_T FOC_ASC_Mode;               /* Variable: FOC_ASC_Mode
                                        * Referenced by: '<S2>/FOC_AKS_Mode'
                                        */
  real32_T FOC_AngleObs_w_InitVal;     /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S16>/Unit Delay1'
                                        */
  real32_T FOC_AngleObserver_D;        /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S13>/Constant1'
                                        */
  real32_T FOC_AngleObserver_w0;       /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S13>/Constant'
                                        */
  real32_T FOC_Enable;                 /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
  real32_T FOC_If_f_el;                /* Variable: FOC_If_f_el
                                        * Referenced by: '<S7>/If_f_el'
                                        */
  real32_T FOC_IntegDamp;              /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S26>/FOC_IntegDamp'
                                        *   '<S30>/FOC_IntegDamp'
                                        *   '<S34>/FOC_IntegDamp'
                                        */
  real32_T FOC_KI;                     /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S26>/FOC_KI'
                                        *   '<S30>/FOC_KI'
                                        *   '<S34>/FOC_KI'
                                        */
  real32_T FOC_KP;                     /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S26>/FOC_KP1'
                                        *   '<S30>/FOC_KP1'
                                        *   '<S34>/FOC_KP1'
                                        */
  real32_T FOC_LIMIT_Overcurrent_I_uvw;/* Variable: FOC_LIMIT_Overcurrent_I_uvw
                                        * Referenced by: '<S38>/Constant'
                                        */
  real32_T FOC_LIMIT_Overvoltage_U_DC; /* Variable: FOC_LIMIT_Overvoltage_U_DC
                                        * Referenced by: '<S43>/Constant'
                                        */
  real32_T FOC_LIMIT_Undervoltage_U_DC;/* Variable: FOC_LIMIT_Undervoltage_U_DC
                                        * Referenced by: '<S42>/Constant'
                                        */
  real32_T FOC_MANUAL_U_DC;            /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc1'
                                        */
  real32_T FOC_MaxModInd;              /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S25>/FOC_MaxModInd'
                                        *   '<S29>/FOC_MaxModInd'
                                        *   '<S33>/FOC_MaxModInd'
                                        */
  real32_T FOC_Mode_Intern;            /* Variable: FOC_Mode_Intern
                                        * Referenced by: '<S1>/FOC_Mode_Intern'
                                        */
  real32_T FOC_OmegaObs3;              /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S13>/Gain4'
                                        */
  real32_T FOC_PhiSensorTdead;         /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S13>/DeadTimeCompensation'
                                        */
  real32_T FOC_SELECT_Voltage_Assignment_UVW;
                                  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
                                   * Referenced by: '<S53>/Constant6'
                                   */
  real32_T FOC_Uf_U_max;               /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S49>/Saturation1'
                                        */
  real32_T FOC_Uf_U_min;               /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S49>/Saturation1'
                                        */
  real32_T FOC_Uf_Ud;                  /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S11>/Uf_Ud'
                                        */
  real32_T FOC_Uf_f_el;                /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S11>/Uf_w_el'
                                        */
  real32_T FOC_Uf_m;                   /* Variable: FOC_Uf_m
                                        * Referenced by: '<S49>/Gain'
                                        */
  real32_T FOC_output_trafo_delay;     /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S4>/FOC_output_trafo_delay'
                                        */
  real32_T FOC_phi_offset;             /* Variable: FOC_phi_offset
                                        * Referenced by: '<S3>/Constant'
                                        */
  real32_T enumState_FOC_IF;           /* Variable: enumState_FOC_IF
                                        * Referenced by: '<S6>/Constant'
                                        */
  uint8_T FOC_SELECT_Mode_Intern;      /* Variable: FOC_SELECT_Mode_Intern
                                        * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
                                        */
  uint8_T FOC_SELECT_Modulation;       /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S12>/Enable_SuperSinMod'
                                        */
  uint8_T FOC_SELECT_U_DC_INPUT;       /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
  uint8_T FOC_SELECT_phi;              /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real32_T AntiWindupGT_d_const;       /* Mask Parameter: AntiWindupGT_d_const
                                        * Referenced by: '<S27>/Constant'
                                        */
  real32_T AntiWindupGT_q_const;       /* Mask Parameter: AntiWindupGT_q_const
                                        * Referenced by: '<S28>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_n;     /* Mask Parameter: AntiWindupGT_d_const_n
                                        * Referenced by: '<S31>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_h;     /* Mask Parameter: AntiWindupGT_q_const_h
                                        * Referenced by: '<S32>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_f;     /* Mask Parameter: AntiWindupGT_d_const_f
                                        * Referenced by: '<S35>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_l;     /* Mask Parameter: AntiWindupGT_q_const_l
                                        * Referenced by: '<S36>/Constant'
                                        */
  boolean_T SRFlipFlop_initial_condition;
                                 /* Mask Parameter: SRFlipFlop_initial_condition
                                  * Referenced by: '<S45>/Memory'
                                  */
  boolean_T SRFlipFlop1_initial_condition;
                                /* Mask Parameter: SRFlipFlop1_initial_condition
                                 * Referenced by: '<S46>/Memory'
                                 */
  boolean_T SRFlipFlop_initial_condition_a;
                               /* Mask Parameter: SRFlipFlop_initial_condition_a
                                * Referenced by: '<S40>/Memory'
                                */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S44>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_o;
                                   /* Mask Parameter: DetectRisePositive_vinit_o
                                    * Referenced by: '<S39>/Delay Input1'
                                    */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S41>/Constant'
                                        */
  real_T Constant_Value_o;             /* Expression: 0
                                        * Referenced by: '<S47>/Constant'
                                        */
  real32_T ASC_LS_Value[9];            /* Computed Parameter: ASC_LS_Value
                                        * Referenced by: '<S2>/ASC_LS'
                                        */
  real32_T ASC_HS_Value[9];            /* Computed Parameter: ASC_HS_Value
                                        * Referenced by: '<S2>/ASC_HS'
                                        */
  real32_T ASC_LSHS_Value[9];          /* Computed Parameter: ASC_LSHS_Value
                                        * Referenced by: '<S2>/ASC_LSHS'
                                        */
  real32_T Constant5_Value;            /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S15>/Constant5'
                                        */
  real32_T Constant6_Value;            /* Computed Parameter: Constant6_Value
                                        * Referenced by: '<S15>/Constant6'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S15>/Constant2'
                                        */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S15>/Constant4'
                                        */
  real32_T Constant_Value_n;           /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S18>/Constant'
                                        */
  real32_T Constant1_Value_d;          /* Computed Parameter: Constant1_Value_d
                                        * Referenced by: '<S18>/Constant1'
                                        */
  real32_T Zero_Value;                 /* Computed Parameter: Zero_Value
                                        * Referenced by: '<S26>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold;
                               /* Computed Parameter: IntegStopSwitch3_Threshold
                                * Referenced by: '<S26>/IntegStopSwitch3'
                                */
  real32_T Zero_Value_o;               /* Computed Parameter: Zero_Value_o
                                        * Referenced by: '<S30>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold_a;
                             /* Computed Parameter: IntegStopSwitch3_Threshold_a
                              * Referenced by: '<S30>/IntegStopSwitch3'
                              */
  real32_T Zero_Value_n;               /* Computed Parameter: Zero_Value_n
                                        * Referenced by: '<S34>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold_ad;
                            /* Computed Parameter: IntegStopSwitch3_Threshold_ad
                             * Referenced by: '<S34>/IntegStopSwitch3'
                             */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S37>/Gain1'
                                        */
  real32_T Constant1_Value_c;          /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<S37>/Constant1'
                                        */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S10>/Gain1'
                                        */
  real32_T Constant1_Value_k;          /* Computed Parameter: Constant1_Value_k
                                        * Referenced by: '<S10>/Constant1'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S14>/Constant'
                                        */
  real32_T Constant1_Value_g;          /* Computed Parameter: Constant1_Value_g
                                        * Referenced by: '<S14>/Constant1'
                                        */
  real32_T Switch1_Threshold;          /* Computed Parameter: Switch1_Threshold
                                        * Referenced by: '<S14>/Switch1'
                                        */
  real32_T Switch2_Threshold;          /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S14>/Switch2'
                                        */
  real32_T Gain1_Gain_a;               /* Computed Parameter: Gain1_Gain_a
                                        * Referenced by: '<S48>/Gain1'
                                        */
  real32_T Constant1_Value_e;          /* Computed Parameter: Constant1_Value_e
                                        * Referenced by: '<S48>/Constant1'
                                        */
  real32_T Constant2_Value_d;          /* Computed Parameter: Constant2_Value_d
                                        * Referenced by: '<S51>/Constant2'
                                        */
  real32_T U_DC2_Gain;                 /* Computed Parameter: U_DC2_Gain
                                        * Referenced by: '<S51>/U_DC//2'
                                        */
  real32_T Constant2_Value_g;          /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S52>/Constant2'
                                        */
  real32_T U_DC2_Gain_p;               /* Computed Parameter: U_DC2_Gain_p
                                        * Referenced by: '<S52>/U_DC//2'
                                        */
  real32_T Factor_Gain;                /* Computed Parameter: Factor_Gain
                                        * Referenced by: '<S54>/Factor'
                                        */
  real32_T Factor1_Gain;               /* Computed Parameter: Factor1_Gain
                                        * Referenced by: '<S54>/Factor1'
                                        */
  real32_T Factor2_Gain;               /* Computed Parameter: Factor2_Gain
                                        * Referenced by: '<S54>/Factor2'
                                        */
  real32_T Constant_Value_d[6];        /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S55>/Constant'
                                        */
  real32_T Null_Value[9];              /* Computed Parameter: Null_Value
                                        * Referenced by: '<S1>/Null'
                                        */
  real32_T DiscreteTransferFcn_NumCoef;
                              /* Computed Parameter: DiscreteTransferFcn_NumCoef
                               * Referenced by: '<S11>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_DenCoef[2];
                              /* Computed Parameter: DiscreteTransferFcn_DenCoef
                               * Referenced by: '<S11>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_InitialStat;
                          /* Computed Parameter: DiscreteTransferFcn_InitialStat
                           * Referenced by: '<S11>/Discrete Transfer Fcn'
                           */
  real32_T f_2_w_el_Gain;              /* Computed Parameter: f_2_w_el_Gain
                                        * Referenced by: '<S11>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value;           /* Computed Parameter: FOC_T_fast_Value
                                        * Referenced by: '<S48>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S48>/Unit Delay'
                                */
  real32_T TrafoMatrixuvwalphabeta_Gain[6];
                             /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
                              * Referenced by: '<S22>/TrafoMatrix uvw->alphabeta'
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
                              * Referenced by: '<S15>/Unit Delay'
                              */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S15>/Constant3'
                                        */
  real32_T Constant1_Value_ep;         /* Computed Parameter: Constant1_Value_ep
                                        * Referenced by: '<S15>/Constant1'
                                        */
  real32_T UnitDelay3_InitialCondition;
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S13>/Unit Delay3'
                               */
  real32_T FOC_T_fast_Value_d;         /* Computed Parameter: FOC_T_fast_Value_d
                                        * Referenced by: '<S10>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_p;
                             /* Computed Parameter: UnitDelay_InitialCondition_p
                              * Referenced by: '<S10>/Unit Delay'
                              */
  real32_T f_2_w_el_Gain_j;            /* Computed Parameter: f_2_w_el_Gain_j
                                        * Referenced by: '<S7>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value_f;         /* Computed Parameter: FOC_T_fast_Value_f
                                        * Referenced by: '<S37>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_d;
                             /* Computed Parameter: UnitDelay_InitialCondition_d
                              * Referenced by: '<S37>/Unit Delay'
                              */
  real32_T IntegDelay1_InitialCondition;
                             /* Computed Parameter: IntegDelay1_InitialCondition
                              * Referenced by: '<S26>/IntegDelay1'
                              */
  real32_T FOC_T_fast_Value_n;         /* Computed Parameter: FOC_T_fast_Value_n
                                        * Referenced by: '<S26>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_p[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
                            * Referenced by: '<S23>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_m;
                           /* Computed Parameter: IntegDelay1_InitialCondition_m
                            * Referenced by: '<S30>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_e;         /* Computed Parameter: FOC_T_fast_Value_e
                                        * Referenced by: '<S30>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_j[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_j
                            * Referenced by: '<S24>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_p;
                           /* Computed Parameter: IntegDelay1_InitialCondition_p
                            * Referenced by: '<S34>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_er;       /* Computed Parameter: FOC_T_fast_Value_er
                                       * Referenced by: '<S34>/FOC_T_fast'
                                       */
  real32_T FOC_T_fast_Value_m;         /* Computed Parameter: FOC_T_fast_Value_m
                                        * Referenced by: '<S4>/FOC_T_fast'
                                        */
  real32_T Switch1_Threshold_a;       /* Computed Parameter: Switch1_Threshold_a
                                       * Referenced by: '<S18>/Switch1'
                                       */
  real32_T Switch2_Threshold_o;       /* Computed Parameter: Switch2_Threshold_o
                                       * Referenced by: '<S18>/Switch2'
                                       */
  real32_T Gain1_Gain_h[4];            /* Computed Parameter: Gain1_Gain_h
                                        * Referenced by: '<S58>/Gain1'
                                        */
  real32_T Gain_Gain[4];               /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S58>/Gain'
                                        */
  real32_T Constant_Value_g[6];        /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S56>/Constant'
                                        */
  real32_T Gain1_Gain_ck[4];           /* Computed Parameter: Gain1_Gain_ck
                                        * Referenced by: '<S59>/Gain1'
                                        */
  real32_T Gain_Gain_l[4];             /* Computed Parameter: Gain_Gain_l
                                        * Referenced by: '<S59>/Gain'
                                        */
  real32_T Constant_Value_oq[6];       /* Computed Parameter: Constant_Value_oq
                                        * Referenced by: '<S57>/Constant'
                                        */
  real32_T Gain1_Gain_k[4];            /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S60>/Gain1'
                                        */
  real32_T Gain_Gain_j[4];             /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S60>/Gain'
                                        */
  real32_T Scale02_Bias;               /* Computed Parameter: Scale02_Bias
                                        * Referenced by: '<S50>/Scale [0..2]'
                                        */
  real32_T Scale01_Gain;               /* Computed Parameter: Scale01_Gain
                                        * Referenced by: '<S50>/Scale  [0..1]'
                                        */
  real32_T Limit01_UpperSat;           /* Computed Parameter: Limit01_UpperSat
                                        * Referenced by: '<S50>/Limit [0..1]'
                                        */
  real32_T Limit01_LowerSat;           /* Computed Parameter: Limit01_LowerSat
                                        * Referenced by: '<S50>/Limit [0..1]'
                                        */
  real32_T FOC_T_fast_Value_df;       /* Computed Parameter: FOC_T_fast_Value_df
                                       * Referenced by: '<S13>/FOC_T_fast'
                                       */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S13>/Gain'
                                        */
  real32_T UnitDelay1_InitialCondition;
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<S17>/Unit Delay1'
                               */
  real32_T FOC_T_fast_Value_c;         /* Computed Parameter: FOC_T_fast_Value_c
                                        * Referenced by: '<S16>/FOC_T_fast'
                                        */
  real32_T FOC_T_fast_Value_k;         /* Computed Parameter: FOC_T_fast_Value_k
                                        * Referenced by: '<S17>/FOC_T_fast'
                                        */
  real32_T Gain1_Gain_kl;              /* Computed Parameter: Gain1_Gain_kl
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real32_T Zero1_Value[2];             /* Computed Parameter: Zero1_Value
                                        * Referenced by: '<S26>/Zero1'
                                        */
  real32_T Gain1_Gain_cs;              /* Computed Parameter: Gain1_Gain_cs
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S19>/Gain2'
                                        */
  real32_T Zero1_Value_l[2];           /* Computed Parameter: Zero1_Value_l
                                        * Referenced by: '<S30>/Zero1'
                                        */
  real32_T Zero1_Value_o[2];           /* Computed Parameter: Zero1_Value_o
                                        * Referenced by: '<S34>/Zero1'
                                        */
  real32_T DiscreteFIRFilter20thorder_Init;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Init
                           * Referenced by: '<S22>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Coef[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
                           * Referenced by: '<S22>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_k;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
                           * Referenced by: '<S23>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_a[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
                           * Referenced by: '<S23>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_n;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_n
                           * Referenced by: '<S24>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_l[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_l
                           * Referenced by: '<S24>/Discrete FIR Filter 20th order'
                           */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S37>/Switch'
                                        */
  real32_T Gain1_Gain_f;               /* Computed Parameter: Gain1_Gain_f
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real32_T Gain1_Gain_g;               /* Computed Parameter: Gain1_Gain_g
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real32_T Gain2_Gain_n;               /* Computed Parameter: Gain2_Gain_n
                                        * Referenced by: '<S9>/Gain2'
                                        */
  real32_T Switch_Threshold_b;         /* Computed Parameter: Switch_Threshold_b
                                        * Referenced by: '<S10>/Switch'
                                        */
  real32_T Switch_Threshold_c;         /* Computed Parameter: Switch_Threshold_c
                                        * Referenced by: '<S48>/Switch'
                                        */
  real32_T Gain_Gain_jm;               /* Computed Parameter: Gain_Gain_jm
                                        * Referenced by: '<S12>/Gain'
                                        */
  real32_T Gain1_Gain_e;               /* Computed Parameter: Gain1_Gain_e
                                        * Referenced by: '<S12>/Gain1'
                                        */
  real32_T Gain2_Gain_f;               /* Computed Parameter: Gain2_Gain_f
                                        * Referenced by: '<S12>/Gain2'
                                        */
  real32_T Gain3_Gain;                 /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<S12>/Gain3'
                                        */
  real32_T DutyCycle_u1_Gain;          /* Computed Parameter: DutyCycle_u1_Gain
                                        * Referenced by: '<S53>/DutyCycle_u1'
                                        */
  real32_T DutyCycle_u2_Gain;          /* Computed Parameter: DutyCycle_u2_Gain
                                        * Referenced by: '<S53>/DutyCycle_u2'
                                        */
  real32_T DutyCycle_u3_Gain;          /* Computed Parameter: DutyCycle_u3_Gain
                                        * Referenced by: '<S53>/DutyCycle_u3'
                                        */
  real32_T DutyCycle_v1_Gain;          /* Computed Parameter: DutyCycle_v1_Gain
                                        * Referenced by: '<S53>/DutyCycle_v1'
                                        */
  real32_T DutyCycle_v2_Gain;          /* Computed Parameter: DutyCycle_v2_Gain
                                        * Referenced by: '<S53>/DutyCycle_v2'
                                        */
  real32_T DutyCycle_v3_Gain;          /* Computed Parameter: DutyCycle_v3_Gain
                                        * Referenced by: '<S53>/DutyCycle_v3'
                                        */
  real32_T DutyCycle_w1_Gain;          /* Computed Parameter: DutyCycle_w1_Gain
                                        * Referenced by: '<S53>/DutyCycle_w1'
                                        */
  real32_T DutyCycle_w2_Gain;          /* Computed Parameter: DutyCycle_w2_Gain
                                        * Referenced by: '<S53>/DutyCycle_w2'
                                        */
  real32_T DutyCycle_w3_Gain;          /* Computed Parameter: DutyCycle_w3_Gain
                                        * Referenced by: '<S53>/DutyCycle_w3'
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
                                        * Referenced by: '<S8>/Constant2'
                                        */
  boolean_T Constant1_Value_gm;        /* Computed Parameter: Constant1_Value_gm
                                        * Referenced by: '<S8>/Constant1'
                                        */
  boolean_T Constant3_Value_i;         /* Computed Parameter: Constant3_Value_i
                                        * Referenced by: '<S9>/Constant3'
                                        */
  boolean_T Constant1_Value_j;         /* Computed Parameter: Constant1_Value_j
                                        * Referenced by: '<S9>/Constant1'
                                        */
  boolean_T Constant2_Value_j;         /* Computed Parameter: Constant2_Value_j
                                        * Referenced by: '<S9>/Constant2'
                                        */
  boolean_T Constant4_Value_b;         /* Computed Parameter: Constant4_Value_b
                                        * Referenced by: '<S9>/Constant4'
                                        */
  boolean_T Logic_table[16];           /* Computed Parameter: Logic_table
                                        * Referenced by: '<S45>/Logic'
                                        */
  boolean_T Logic_table_m[16];         /* Computed Parameter: Logic_table_m
                                        * Referenced by: '<S46>/Logic'
                                        */
  boolean_T Logic_table_f[16];         /* Computed Parameter: Logic_table_f
                                        * Referenced by: '<S40>/Logic'
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
 * '<S6>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Enable_If_Mode'
 * '<S7>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/I_f'
 * '<S8>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection'
 * '<S9>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection'
 * '<S10>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/SubS_2pi_Integrator'
 * '<S11>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f'
 * '<S12>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output'
 * '<S13>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver'
 * '<S14>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/Modulo2Pi'
 * '<S15>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/2PiKorr'
 * '<S16>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator'
 * '<S17>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator1'
 * '<S18>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Lead/Modulo2Pi'
 * '<S19>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1'
 * '<S20>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2'
 * '<S21>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3'
 * '<S22>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_1'
 * '<S23>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_2'
 * '<S24>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_3'
 * '<S25>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup'
 * '<S26>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/FeedbackPI'
 * '<S27>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_d'
 * '<S28>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_q'
 * '<S29>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup'
 * '<S30>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/FeedbackPI'
 * '<S31>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_d'
 * '<S32>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_q'
 * '<S33>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup'
 * '<S34>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/FeedbackPI'
 * '<S35>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup/AntiWindupGT_d'
 * '<S36>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup/AntiWindupGT_q'
 * '<S37>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/I_f/SubS_2pi_Integrator'
 * '<S38>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/Compare To Constant'
 * '<S39>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/Detect Rise Positive'
 * '<S40>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/S-R Flip-Flop'
 * '<S41>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_Detection/Detect Rise Positive/Positive'
 * '<S42>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Compare To Constant'
 * '<S43>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Compare To Constant1'
 * '<S44>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Detect Rise Positive'
 * '<S45>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/S-R Flip-Flop'
 * '<S46>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/S-R Flip-Flop1'
 * '<S47>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OV_UV_Detection/Detect Rise Positive/Positive'
 * '<S48>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/SubS_2pi_Integrator'
 * '<S49>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/UfKennlinie'
 * '<S50>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Adjust_duty_cycle_range'
 * '<S51>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Calc_Modulation_Index'
 * '<S52>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/NormalizedVoltage'
 * '<S53>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Phase_Assignment'
 * '<S54>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Super_Sinus_Modulation'
 * '<S55>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_1'
 * '<S56>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_2'
 * '<S57>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_3'
 * '<S58>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_1'
 * '<S59>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_2'
 * '<S60>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_3'
 */
#endif                                 /* FOC_FCF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
