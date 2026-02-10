/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.h
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.38
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Feb 10 16:30:06 2026
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
  bus_InvStatus_t bus_InvStatus;       /* '<S8>/Bus Creator' */
  real_T U_DC_Undervoltage_Error;      /* '<S49>/Selectphicalc1' */
  real_T U_DC_Overvoltage_Error;       /* '<S49>/Selectphicalc2' */
  real_T DataSourceSwitch;             /* '<S7>/DataSourceSwitch' */
  real_T Overspeed_Error;              /* '<S11>/Data Type Conversion' */
  real_T DataTypeConversion[9];        /* '<S53>/Data Type Conversion' */
  real_T DataTypeConversion1;          /* '<S49>/Data Type Conversion1' */
  real_T DataTypeConversion_n;         /* '<S49>/Data Type Conversion' */
  uint32_T Mask_6Bits_Inv1_FLT;        /* '<S8>/Mask_6Bits_Inv1_FLT' */
  uint32_T BitwiseNOT;                 /* '<S41>/Bitwise NOT' */
  uint32_T MaskBit0;                   /* '<S41>/MaskBit0' */
  uint32_T get_U_HS_FLT;               /* '<S41>/get_U_HS_FLT' */
  uint32_T MaskBit1;                   /* '<S41>/MaskBit1' */
  uint32_T get_U_LS_FLT;               /* '<S41>/get_U_LS_FLT' */
  uint32_T MaskBit2;                   /* '<S41>/MaskBit2' */
  uint32_T get_V_HS_FLT;               /* '<S41>/get_V_HS_FLT' */
  uint32_T MaskBit3;                   /* '<S41>/MaskBit3' */
  uint32_T get_V_LS_FLT;               /* '<S41>/get_V_LS_FLT' */
  uint32_T MaskBit4;                   /* '<S41>/MaskBit4' */
  uint32_T get_W_HS_FLT;               /* '<S41>/get_W_HS_FLT' */
  uint32_T MaskBit5;                   /* '<S41>/MaskBit5' */
  uint32_T get_W_LS_FLT;               /* '<S41>/get_W_LS_FLT' */
  uint32_T Mask_6Bits_Inv1_RDY;        /* '<S8>/Mask_6Bits_Inv1_RDY' */
  uint32_T MaskBit0_c;                 /* '<S42>/MaskBit0' */
  uint32_T get_U_HS_RDY;               /* '<S42>/get_U_HS_RDY' */
  uint32_T MaskBit1_b;                 /* '<S42>/MaskBit1' */
  uint32_T get_U_LS_RDY;               /* '<S42>/get_U_LS_RDY' */
  uint32_T MaskBit2_n;                 /* '<S42>/MaskBit2' */
  uint32_T get_V_HS_RDY;               /* '<S42>/get_V_HS_RDY' */
  uint32_T MaskBit3_a;                 /* '<S42>/MaskBit3' */
  uint32_T get_V_LS_RDY;               /* '<S42>/get_V_LS_RDY' */
  uint32_T MaskBit4_c;                 /* '<S42>/MaskBit4' */
  uint32_T get_W_HS_RDY;               /* '<S42>/get_W_HS_RDY' */
  uint32_T MaskBit5_l;                 /* '<S42>/MaskBit5' */
  uint32_T get_W_LS_RDY;               /* '<S42>/get_W_LS_RDY' */
  uint32_T Mask_6Bits_Inv2_FLT;        /* '<S8>/Mask_6Bits_Inv2_FLT' */
  uint32_T BitwiseNOT_j;               /* '<S43>/Bitwise NOT' */
  uint32_T MaskBit0_o;                 /* '<S43>/MaskBit0' */
  uint32_T get_U_HS_FLT_i;             /* '<S43>/get_U_HS_FLT' */
  uint32_T MaskBit1_ba;                /* '<S43>/MaskBit1' */
  uint32_T get_U_LS_FLT_a;             /* '<S43>/get_U_LS_FLT' */
  uint32_T MaskBit2_d;                 /* '<S43>/MaskBit2' */
  uint32_T get_V_HS_FLT_i;             /* '<S43>/get_V_HS_FLT' */
  uint32_T MaskBit3_d;                 /* '<S43>/MaskBit3' */
  uint32_T get_V_LS_FLT_c;             /* '<S43>/get_V_LS_FLT' */
  uint32_T MaskBit4_p;                 /* '<S43>/MaskBit4' */
  uint32_T get_W_HS_FLT_f;             /* '<S43>/get_W_HS_FLT' */
  uint32_T MaskBit5_o;                 /* '<S43>/MaskBit5' */
  uint32_T get_W_LS_FLT_l;             /* '<S43>/get_W_LS_FLT' */
  uint32_T Mask_6Bits_Inv2_RDY;        /* '<S8>/Mask_6Bits_Inv2_RDY' */
  uint32_T MaskBit0_p;                 /* '<S44>/MaskBit0' */
  uint32_T get_U_HS_RDY_i;             /* '<S44>/get_U_HS_RDY' */
  uint32_T MaskBit1_m;                 /* '<S44>/MaskBit1' */
  uint32_T get_U_LS_RDY_f;             /* '<S44>/get_U_LS_RDY' */
  uint32_T MaskBit2_g;                 /* '<S44>/MaskBit2' */
  uint32_T get_V_HS_RDY_j;             /* '<S44>/get_V_HS_RDY' */
  uint32_T MaskBit3_k;                 /* '<S44>/MaskBit3' */
  uint32_T get_V_LS_RDY_a;             /* '<S44>/get_V_LS_RDY' */
  uint32_T MaskBit4_l;                 /* '<S44>/MaskBit4' */
  uint32_T get_W_HS_RDY_n;             /* '<S44>/get_W_HS_RDY' */
  uint32_T MaskBit5_lb;                /* '<S44>/MaskBit5' */
  uint32_T get_W_LS_RDY_l;             /* '<S44>/get_W_LS_RDY' */
  uint32_T Mask_6Bits_Inv3_FLT;        /* '<S8>/Mask_6Bits_Inv3_FLT' */
  uint32_T BitwiseNOT_c;               /* '<S45>/Bitwise NOT' */
  uint32_T MaskBit0_ph;                /* '<S45>/MaskBit0' */
  uint32_T get_U_HS_FLT_m;             /* '<S45>/get_U_HS_FLT' */
  uint32_T MaskBit1_k;                 /* '<S45>/MaskBit1' */
  uint32_T get_U_LS_FLT_h;             /* '<S45>/get_U_LS_FLT' */
  uint32_T MaskBit2_f;                 /* '<S45>/MaskBit2' */
  uint32_T get_V_HS_FLT_h;             /* '<S45>/get_V_HS_FLT' */
  uint32_T MaskBit3_a2;                /* '<S45>/MaskBit3' */
  uint32_T get_V_LS_FLT_g;             /* '<S45>/get_V_LS_FLT' */
  uint32_T MaskBit4_f;                 /* '<S45>/MaskBit4' */
  uint32_T get_W_HS_FLT_m;             /* '<S45>/get_W_HS_FLT' */
  uint32_T MaskBit5_h;                 /* '<S45>/MaskBit5' */
  uint32_T get_W_LS_FLT_g;             /* '<S45>/get_W_LS_FLT' */
  uint32_T Mask_6Bits_Inv3_RDY;        /* '<S8>/Mask_6Bits_Inv3_RDY' */
  uint32_T MaskBit0_k;                 /* '<S46>/MaskBit0' */
  uint32_T get_U_HS_RDY_e;             /* '<S46>/get_U_HS_RDY' */
  uint32_T MaskBit1_o;                 /* '<S46>/MaskBit1' */
  uint32_T get_U_LS_RDY_l;             /* '<S46>/get_U_LS_RDY' */
  uint32_T MaskBit2_a;                 /* '<S46>/MaskBit2' */
  uint32_T get_V_HS_RDY_e;             /* '<S46>/get_V_HS_RDY' */
  uint32_T MaskBit3_kg;                /* '<S46>/MaskBit3' */
  uint32_T get_V_LS_RDY_k;             /* '<S46>/get_V_LS_RDY' */
  uint32_T MaskBit4_ch;                /* '<S46>/MaskBit4' */
  uint32_T get_W_HS_RDY_h;             /* '<S46>/get_W_HS_RDY' */
  uint32_T MaskBit5_p;                 /* '<S46>/MaskBit5' */
  uint32_T get_W_LS_RDY_m;             /* '<S46>/get_W_LS_RDY' */
  real32_T FOC_Mode_Request;           /* '<S1>/ModeSwitch' */
  real32_T Abs[9];                     /* '<S48>/Abs' */
  real32_T MinMax;                     /* '<S48>/MinMax' */
  real32_T FOC_Mode_after_checks;      /* '<S1>/Switch' */
  real32_T DiscreteTransferFcn;        /* '<S13>/Discrete Transfer Fcn' */
  real32_T f_2_w_el;                   /* '<S13>/f_2_w_el' */
  real32_T Product;                    /* '<S77>/Product' */
  real32_T UnitDelay;                  /* '<S77>/Unit Delay' */
  real32_T Add;                        /* '<S77>/Add' */
  real32_T TrafoMatrixuvwalphabeta[2]; /* '<S24>/TrafoMatrix uvw->alphabeta' */
  real32_T ResolverOffsetLimitation;   /* '<S3>/ResolverOffsetLimitation' */
  real32_T Sum1;                       /* '<S3>/Sum1' */
  real32_T w_el;                       /* '<S18>/Unit Delay1' */
  real32_T DeadTimeCompensation;       /* '<S15>/DeadTimeCompensation' */
  real32_T Sum3;                       /* '<S15>/Sum3' */
  real32_T UnitDelay_l;                /* '<S17>/Unit Delay' */
  real32_T Sum;                        /* '<S17>/Sum' */
  real32_T Switch;                     /* '<S17>/Switch' */
  real32_T Switch1;                    /* '<S17>/Switch1' */
  real32_T Sum2;                       /* '<S17>/Sum2' */
  real32_T UnitDelay3;                 /* '<S15>/Unit Delay3' */
  real32_T phi_el_observer;            /* '<S15>/Sum7' */
  real32_T Product_e;                  /* '<S12>/Product' */
  real32_T UnitDelay_a;                /* '<S12>/Unit Delay' */
  real32_T Add_m;                      /* '<S12>/Add' */
  real32_T f_2_w_el_b;                 /* '<S9>/f_2_w_el' */
  real32_T Product_h;                  /* '<S47>/Product' */
  real32_T UnitDelay_j;                /* '<S47>/Unit Delay' */
  real32_T Add_mp;                     /* '<S47>/Add' */
  real32_T Use_If_Mode[2];             /* '<S1>/Use_If_Mode' */
  real32_T TrigonometricFunction1;     /* '<S24>/Trigonometric Function1' */
  real32_T TrafoProd;                  /* '<S24>/TrafoProd' */
  real32_T TrigonometricFunction;      /* '<S24>/Trigonometric Function' */
  real32_T TrafoProd3;                 /* '<S24>/TrafoProd3' */
  real32_T I_d1_Act;                   /* '<S24>/I_d1_Act' */
  real32_T TrafoProd1;                 /* '<S24>/TrafoProd1' */
  real32_T TrafoProd2;                 /* '<S24>/TrafoProd2' */
  real32_T I_q1_Act;                   /* '<S24>/I_q1_Act' */
  real32_T TmpSignalConversionAtDiscreteFI[2];
  real32_T IdqErr[2];                  /* '<S21>/IdqErr' */
  real32_T KPek1[2];                   /* '<S28>/KP*e[k]1' */
  real32_T IntegDelay1[2];             /* '<S28>/IntegDelay1' */
  real32_T Product1;                   /* '<S28>/Product1' */
  real32_T IntegEnaSwitch1[2];         /* '<S28>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_h[2];/* '<S25>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum1_d;                     /* '<S5>/Sum1' */
  real32_T TrigonometricFunction1_b;   /* '<S25>/Trigonometric Function1' */
  real32_T TrafoProd_a;                /* '<S25>/TrafoProd' */
  real32_T TrigonometricFunction_l;    /* '<S25>/Trigonometric Function' */
  real32_T TrafoProd3_i;               /* '<S25>/TrafoProd3' */
  real32_T TrafoSum;                   /* '<S25>/TrafoSum' */
  real32_T TrafoProd1_b;               /* '<S25>/TrafoProd1' */
  real32_T TrafoProd2_b;               /* '<S25>/TrafoProd2' */
  real32_T TrafoSum1;                  /* '<S25>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_k[2];
  real32_T IdqErr_l[2];                /* '<S22>/IdqErr' */
  real32_T KPek1_l[2];                 /* '<S32>/KP*e[k]1' */
  real32_T IntegDelay1_o[2];           /* '<S32>/IntegDelay1' */
  real32_T Product1_k;                 /* '<S32>/Product1' */
  real32_T IntegEnaSwitch1_n[2];       /* '<S32>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_m[2];/* '<S26>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum2_m;                     /* '<S5>/Sum2' */
  real32_T TrigonometricFunction1_k;   /* '<S26>/Trigonometric Function1' */
  real32_T TrafoProd_n;                /* '<S26>/TrafoProd' */
  real32_T TrigonometricFunction_k;    /* '<S26>/Trigonometric Function' */
  real32_T TrafoProd3_o;               /* '<S26>/TrafoProd3' */
  real32_T TrafoSum_n;                 /* '<S26>/TrafoSum' */
  real32_T TrafoProd1_e;               /* '<S26>/TrafoProd1' */
  real32_T TrafoProd2_h;               /* '<S26>/TrafoProd2' */
  real32_T TrafoSum1_p;                /* '<S26>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_c[2];
  real32_T IdqErr_e[2];                /* '<S23>/IdqErr' */
  real32_T KPek1_h[2];                 /* '<S36>/KP*e[k]1' */
  real32_T IntegDelay1_d[2];           /* '<S36>/IntegDelay1' */
  real32_T Product1_b;                 /* '<S36>/Product1' */
  real32_T IntegEnaSwitch1_h[2];       /* '<S36>/IntegEnaSwitch1' */
  real32_T Product_c;                  /* '<S4>/Product' */
  real32_T Sum_k;                      /* '<S4>/Sum' */
  real32_T Switch1_k;                  /* '<S20>/Switch1' */
  real32_T Switch2;                    /* '<S20>/Switch2' */
  real32_T Sum2_p;                     /* '<S4>/Sum2' */
  real32_T Sum1_l;                     /* '<S4>/Sum1' */
  real32_T SelectControlMode[9];       /* '<S1>/SelectControlMode' */
  real32_T TrigonometricFunction_n;    /* '<S87>/Trigonometric Function' */
  real32_T Gain1[4];                   /* '<S87>/Gain1' */
  real32_T TrigonometricFunction1_j;   /* '<S87>/Trigonometric Function1' */
  real32_T Gain[4];                    /* '<S87>/Gain' */
  real32_T Sum1_g[4];                  /* '<S87>/Sum1' */
  real32_T Product_c0[2];              /* '<S87>/Product' */
  real32_T U_uvw1[3];                  /* '<S84>/Product' */
  real32_T TrigonometricFunction_j;    /* '<S88>/Trigonometric Function' */
  real32_T Gain1_i[4];                 /* '<S88>/Gain1' */
  real32_T TrigonometricFunction1_h;   /* '<S88>/Trigonometric Function1' */
  real32_T Gain_f[4];                  /* '<S88>/Gain' */
  real32_T Sum1_f[4];                  /* '<S88>/Sum1' */
  real32_T Product_f[2];               /* '<S88>/Product' */
  real32_T Product_f3[3];              /* '<S85>/Product' */
  real32_T TrigonometricFunction_h;    /* '<S89>/Trigonometric Function' */
  real32_T Gain1_n[4];                 /* '<S89>/Gain1' */
  real32_T TrigonometricFunction1_hh;  /* '<S89>/Trigonometric Function1' */
  real32_T Gain_l[4];                  /* '<S89>/Gain' */
  real32_T Sum1_lz[4];                 /* '<S89>/Sum1' */
  real32_T Product_i[2];               /* '<S89>/Product' */
  real32_T Product_fb[3];              /* '<S86>/Product' */
  real32_T U_DC_fcf;                   /* '<S1>/U_DC_switch' */
  real32_T SelMod_DutyCycles[9];       /* '<S14>/SelectModulation' */
  real32_T Scale02[9];                 /* '<S79>/Scale [0..2]' */
  real32_T Scale01[9];                 /* '<S79>/Scale  [0..1]' */
  real32_T Limit01[9];                 /* '<S79>/Limit [0..1]' */
  real32_T Select_GateDriver_Assignment_1[3];
                                    /* '<S82>/Select_GateDriver_Assignment_1' */
  real32_T Select_GateDriver_Assignment_2[3];
                                    /* '<S82>/Select_GateDriver_Assignment_2' */
  real32_T Select_GateDriver_Assignment_3[3];
                                    /* '<S82>/Select_GateDriver_Assignment_3' */
  real32_T Deviation;                  /* '<S15>/Deviation' */
  real32_T Product2;                   /* '<S15>/Product2' */
  real32_T Gain_g;                     /* '<S15>/Gain' */
  real32_T winkelimpuls;               /* '<S15>/Gain4' */
  real32_T Sum1_g4;                    /* '<S15>/Sum1' */
  real32_T Product_o;                  /* '<S15>/Product' */
  real32_T Product1_bi;                /* '<S15>/Product1' */
  real32_T UnitDelay1;                 /* '<S19>/Unit Delay1' */
  real32_T Sum2_mq;                    /* '<S15>/Sum2' */
  real32_T Sum6;                       /* '<S15>/Sum6' */
  real32_T Product_n;                  /* '<S18>/Product' */
  real32_T Sum2_e;                     /* '<S18>/Sum2' */
  real32_T Product_cd;                 /* '<S19>/Product' */
  real32_T Sum2_j;                     /* '<S19>/Sum2' */
  real32_T phi_el_U_trafo[3];          /* '<S4>/Gain1' */
  real32_T IntegStopSwitch2[2];        /* '<S28>/IntegStopSwitch2' */
  real32_T U_d1_CC;                    /* '<S21>/Gain1' */
  real32_T U_q1_CC;                    /* '<S21>/Gain2' */
  real32_T IntegStopSwitch2_o[2];      /* '<S32>/IntegStopSwitch2' */
  real32_T IntegStopSwitch2_h[2];      /* '<S36>/IntegStopSwitch2' */
  real32_T I_dq1_Act_filt[2];       /* '<S24>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder[2];
                                    /* '<S25>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_l[2];
                                    /* '<S26>/Discrete FIR Filter 20th order' */
  real32_T EN_FLT_Switch1;             /* '<S7>/EN_FLT_Switch1' */
  real32_T EN_RDY_Switch;              /* '<S7>/EN_RDY_Switch' */
  real32_T usrpm;                      /* '<S11>/[1//s] => [rpm]' */
  real32_T Abs_d;                      /* '<S11>/Abs' */
  real32_T Abs_e;                      /* '<S47>/Abs' */
  real32_T Switch_d;                   /* '<S47>/Switch' */
  real32_T Add1;                       /* '<S47>/Add1' */
  real32_T Abs_b;                      /* '<S12>/Abs' */
  real32_T Switch_l;                   /* '<S12>/Switch' */
  real32_T Add1_j;                     /* '<S12>/Add1' */
  real32_T Abs_f;                      /* '<S77>/Abs' */
  real32_T Switch_n;                   /* '<S77>/Switch' */
  real32_T Add1_c;                     /* '<S77>/Add1' */
  real32_T U_d1;                       /* '<S14>/Gain' */
  real32_T U_q1;                       /* '<S14>/Gain1' */
  real32_T U_alpha1;                   /* '<S14>/Gain2' */
  real32_T U_beta1;                    /* '<S14>/Gain3' */
  real32_T DutyCycle_u1;               /* '<S82>/DutyCycle_u1' */
  real32_T DutyCycle_u2;               /* '<S82>/DutyCycle_u2' */
  real32_T DutyCycle_u3;               /* '<S82>/DutyCycle_u3' */
  real32_T DutyCycle_v1;               /* '<S82>/DutyCycle_v1' */
  real32_T DutyCycle_v2;               /* '<S82>/DutyCycle_v2' */
  real32_T DutyCycle_v3;               /* '<S82>/DutyCycle_v3' */
  real32_T DutyCycle_w1;               /* '<S82>/DutyCycle_w1' */
  real32_T DutyCycle_w2;               /* '<S82>/DutyCycle_w2' */
  real32_T DutyCycle_w3;               /* '<S82>/DutyCycle_w3' */
  real32_T FCF_Cnt;                    /* '<S1>/FCF_Cnt' */
  real32_T Sum_o;                      /* '<S1>/Sum' */
  real32_T MinMax2;                    /* '<S83>/MinMax2' */
  real32_T MinMax3;                    /* '<S83>/MinMax3' */
  real32_T Sum1_o;                     /* '<S83>/Sum1' */
  real32_T Factor;                     /* '<S83>/Factor' */
  real32_T DutyCycle_SuperSinus_1[3];  /* '<S83>/DutyCycle_SuperSinus_1' */
  real32_T MinMax1;                    /* '<S83>/MinMax1' */
  real32_T MinMax4;                    /* '<S83>/MinMax4' */
  real32_T Sum2_i;                     /* '<S83>/Sum2' */
  real32_T Factor1;                    /* '<S83>/Factor1' */
  real32_T DutyCycle_SuperSinus_2[3];  /* '<S83>/DutyCycle_SuperSinus_2' */
  real32_T MinMax5;                    /* '<S83>/MinMax5' */
  real32_T MinMax6;                    /* '<S83>/MinMax6' */
  real32_T Sum3_k;                     /* '<S83>/Sum3' */
  real32_T Factor2;                    /* '<S83>/Factor2' */
  real32_T DutyCycle_SuperSinus_3[3];  /* '<S83>/DutyCycle_SuperSinus_3' */
  real32_T U_DC2;                      /* '<S81>/U_DC//2' */
  real32_T AvoidDivBy0;                /* '<S81>/AvoidDivBy0' */
  real32_T DutyCycle_normed[9];        /* '<S81>/DutyCycle_normalized' */
  real32_T U_DC2_l;                    /* '<S80>/U_DC//2' */
  real32_T AvoidDivBy0_f;              /* '<S80>/AvoidDivBy0' */
  real32_T Square[2];                  /* '<S80>/Square' */
  real32_T Sum_kr;                     /* '<S80>/Sum' */
  real32_T Sqrt;                       /* '<S80>/Sqrt' */
  real32_T Square1[2];                 /* '<S80>/Square1' */
  real32_T Sum1_a;                     /* '<S80>/Sum1' */
  real32_T Sqrt1;                      /* '<S80>/Sqrt1' */
  real32_T Square2[2];                 /* '<S80>/Square2' */
  real32_T Sum2_iq;                    /* '<S80>/Sum2' */
  real32_T Sqrt2;                      /* '<S80>/Sqrt2' */
  real32_T ModInd[3];                  /* '<S80>/Divide3' */
  real32_T Sign;                       /* '<S77>/Sign' */
  real32_T Gain1_o;                    /* '<S77>/Gain1' */
  real32_T Use_If_Starter;             /* '<S1>/Use_If_Starter' */
  real32_T Selectphicalc2;             /* '<S3>/Selectphicalc2' */
  real32_T Switch1_d;                  /* '<S16>/Switch1' */
  real32_T Switch2_f;                  /* '<S16>/Switch2' */
  real32_T Sum3_h;                     /* '<S16>/Sum3' */
  real32_T Sum2_l;                     /* '<S16>/Sum2' */
  real32_T Gain_fw;                    /* '<S78>/Gain' */
  real32_T Sign_p;                     /* '<S78>/Sign' */
  real32_T Abs_d3;                     /* '<S78>/Abs' */
  real32_T Saturation1;                /* '<S78>/Saturation1' */
  real32_T Product_j;                  /* '<S78>/Product' */
  real32_T Sum1_n;                     /* '<S13>/Sum1' */
  real32_T Sum2_d;                     /* '<S13>/Sum2' */
  real32_T Sign_n;                     /* '<S12>/Sign' */
  real32_T Gain1_h;                    /* '<S12>/Gain1' */
  real32_T Sign_d;                     /* '<S47>/Sign' */
  real32_T Gain1_j;                    /* '<S47>/Gain1' */
  real32_T IntegStopSwitch3[2];        /* '<S36>/IntegStopSwitch3' */
  real32_T IntSum2[2];                 /* '<S36>/IntSum2' */
  real32_T FOC_IntegDamp[2];           /* '<S36>/FOC_IntegDamp' */
  real32_T antiWindupProd[2];          /* '<S35>/antiWindupProd' */
  real32_T IntegStopSwitch1[2];        /* '<S36>/IntegStopSwitch1' */
  real32_T Product2_e[2];              /* '<S36>/Product2' */
  real32_T IntSum1[2];                 /* '<S36>/IntSum1' */
  real32_T IntegStopSwitch3_n[2];      /* '<S32>/IntegStopSwitch3' */
  real32_T IntSum2_f[2];               /* '<S32>/IntSum2' */
  real32_T FOC_IntegDamp_g[2];         /* '<S32>/FOC_IntegDamp' */
  real32_T antiWindupProd_d[2];        /* '<S31>/antiWindupProd' */
  real32_T IntegStopSwitch1_g[2];      /* '<S32>/IntegStopSwitch1' */
  real32_T Product2_b[2];              /* '<S32>/Product2' */
  real32_T IntSum1_l[2];               /* '<S32>/IntSum1' */
  real32_T IntegStopSwitch3_h[2];      /* '<S28>/IntegStopSwitch3' */
  real32_T IntSum2_j[2];               /* '<S28>/IntSum2' */
  real32_T FOC_IntegDamp_c[2];         /* '<S28>/FOC_IntegDamp' */
  real32_T antiWindupProd_o[2];        /* '<S27>/antiWindupProd' */
  real32_T IntegStopSwitch1_f[2];      /* '<S28>/IntegStopSwitch1' */
  real32_T Product2_j[2];              /* '<S28>/Product2' */
  real32_T IntSum1_p[2];               /* '<S28>/IntSum1' */
  real32_T Sum3_d;                     /* '<S20>/Sum3' */
  real32_T Sum2_ez;                    /* '<S20>/Sum2' */
  real32_T ASCSwitch[9];               /* '<S2>/ASC Switch' */
  uint8_T Compare;                     /* '<S38>/Compare' */
  uint8_T Compare_k;                   /* '<S37>/Compare' */
  uint8_T Compare_g;                   /* '<S34>/Compare' */
  uint8_T Compare_i;                   /* '<S33>/Compare' */
  uint8_T Compare_o;                   /* '<S30>/Compare' */
  uint8_T Compare_f;                   /* '<S29>/Compare' */
  boolean_T Compare_e;                 /* '<S65>/Compare' */
  boolean_T LogicalOperator2;          /* '<S49>/Logical Operator2' */
  boolean_T LogicalOperator4;          /* '<S49>/Logical Operator4' */
  boolean_T Compare_d;                 /* '<S72>/Compare' */
  boolean_T Uk1;                       /* '<S68>/Delay Input1' */
  boolean_T Selectphicalc3;            /* '<S49>/Selectphicalc3' */
  boolean_T Memory;                    /* '<S69>/Memory' */
  boolean_T Logic[2];                  /* '<S69>/Logic' */
  boolean_T Compare_n;                 /* '<S66>/Compare' */
  boolean_T LogicalOperator3;          /* '<S49>/Logical Operator3' */
  boolean_T Compare_iz;                /* '<S71>/Compare' */
  boolean_T Uk1_m;                     /* '<S67>/Delay Input1' */
  boolean_T Selectphicalc4;            /* '<S49>/Selectphicalc4' */
  boolean_T Memory_o;                  /* '<S70>/Memory' */
  boolean_T Logic_c[2];                /* '<S70>/Logic' */
  boolean_T Compare_j;                 /* '<S50>/Compare' */
  boolean_T LogicalOperator3_i;        /* '<S48>/Logical Operator3' */
  boolean_T Compare_in;                /* '<S55>/Compare' */
  boolean_T Uk1_g;                     /* '<S52>/Delay Input1' */
  boolean_T Selectphicalc2_m;          /* '<S48>/Selectphicalc2' */
  boolean_T Memory_n;                  /* '<S54>/Memory' */
  boolean_T Logic_a[2];                /* '<S54>/Logic' */
  boolean_T I_ph_Overcurrent_Error;    /* '<S48>/Selectphicalc1' */
  boolean_T OC_OV_UV_ERROR;            /* '<S10>/Logical Operator' */
  boolean_T LogicalOperator1;          /* '<S1>/Logical Operator1' */
  boolean_T LogicalOperator;           /* '<S1>/Logical Operator' */
  boolean_T Compare_l;                 /* '<S6>/Compare' */
  boolean_T Sprung;                    /* '<S17>/Sprung?' */
  boolean_T Sprung1;                   /* '<S17>/Sprung?1' */
  boolean_T Compare_c;                 /* '<S73>/Compare' */
  boolean_T LogicalOperator3_p;        /* '<S11>/Logical Operator3' */
  boolean_T Compare_gt;                /* '<S76>/Compare' */
  boolean_T Uk1_h;                     /* '<S74>/Delay Input1' */
  boolean_T Selectphicalc2_d;          /* '<S11>/Selectphicalc2' */
  boolean_T Memory_k;                  /* '<S75>/Memory' */
  boolean_T Logic_e[2];                /* '<S75>/Logic' */
  boolean_T Selectphicalc1;            /* '<S11>/Selectphicalc1' */
  boolean_T LogicalOperator3_pp;       /* '<S7>/Logical Operator3' */
  boolean_T FOC_Enable_PWM;            /* '<S7>/Enable_PWM_' */
  boolean_T FCF_Error;                 /* '<S7>/Logical Operator6' */
  boolean_T Compare_gv[9];             /* '<S51>/Compare' */
  boolean_T Memory_f;                  /* '<S56>/Memory' */
  boolean_T Logic_g[2];                /* '<S56>/Logic' */
  boolean_T Memory_b;                  /* '<S57>/Memory' */
  boolean_T Logic_i[2];                /* '<S57>/Logic' */
  boolean_T Memory_ok;                 /* '<S58>/Memory' */
  boolean_T Logic_b[2];                /* '<S58>/Logic' */
  boolean_T Memory_c;                  /* '<S59>/Memory' */
  boolean_T Logic_p[2];                /* '<S59>/Logic' */
  boolean_T Memory_g;                  /* '<S60>/Memory' */
  boolean_T Logic_d[2];                /* '<S60>/Logic' */
  boolean_T Memory_j;                  /* '<S61>/Memory' */
  boolean_T Logic_ev[2];               /* '<S61>/Logic' */
  boolean_T Memory_nb;                 /* '<S62>/Memory' */
  boolean_T Logic_bw[2];               /* '<S62>/Logic' */
  boolean_T Memory_kp;                 /* '<S63>/Memory' */
  boolean_T Logic_ag[2];               /* '<S63>/Logic' */
  boolean_T Memory_p;                  /* '<S64>/Memory' */
  boolean_T Logic_f[2];                /* '<S64>/Logic' */
  boolean_T FixPtRelationalOperator;   /* '<S74>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_m; /* '<S67>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_j; /* '<S68>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_h; /* '<S52>/FixPt Relational Operator' */
  boolean_T AntiWindupLE;              /* '<S35>/AntiWindupLE' */
  boolean_T AntiWindupOR_q;            /* '<S35>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d;            /* '<S35>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_f;            /* '<S31>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_l;          /* '<S31>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_m;          /* '<S31>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_l;            /* '<S27>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_o;          /* '<S27>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_e;          /* '<S27>/AntiWindupOR_d' */
} B_FOC_FCF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTransferFcn_states; /* '<S13>/Discrete Transfer Fcn' */
  real32_T UnitDelay_DSTATE;           /* '<S77>/Unit Delay' */
  real32_T UnitDelay1_DSTATE;          /* '<S18>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_h;         /* '<S17>/Unit Delay' */
  real32_T UnitDelay3_DSTATE;          /* '<S15>/Unit Delay3' */
  real32_T UnitDelay_DSTATE_p;         /* '<S12>/Unit Delay' */
  real32_T UnitDelay_DSTATE_f;         /* '<S47>/Unit Delay' */
  real32_T IntegDelay1_DSTATE[2];      /* '<S28>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_p[2];    /* '<S32>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_h[2];    /* '<S36>/IntegDelay1' */
  real32_T UnitDelay1_DSTATE_i;        /* '<S19>/Unit Delay1' */
  real32_T DiscreteFIRFilter20thorder_stat[38];
                                    /* '<S24>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_g[38];
                                    /* '<S25>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_p[38];
                                    /* '<S26>/Discrete FIR Filter 20th order' */
  real32_T FCF_Cnt_DSTATE;             /* '<S1>/FCF_Cnt' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S24>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_m;
                                    /* '<S25>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_c;
                                    /* '<S26>/Discrete FIR Filter 20th order' */
  boolean_T DelayInput1_DSTATE;        /* '<S68>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_g;      /* '<S67>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_l;      /* '<S52>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_e;      /* '<S74>/Delay Input1' */
  boolean_T Memory_PreviousInput;      /* '<S69>/Memory' */
  boolean_T Memory_PreviousInput_e;    /* '<S70>/Memory' */
  boolean_T Memory_PreviousInput_j;    /* '<S54>/Memory' */
  boolean_T Memory_PreviousInput_i;    /* '<S75>/Memory' */
  boolean_T Memory_PreviousInput_n;    /* '<S56>/Memory' */
  boolean_T Memory_PreviousInput_o;    /* '<S57>/Memory' */
  boolean_T Memory_PreviousInput_nm;   /* '<S58>/Memory' */
  boolean_T Memory_PreviousInput_ef;   /* '<S59>/Memory' */
  boolean_T Memory_PreviousInput_c;    /* '<S60>/Memory' */
  boolean_T Memory_PreviousInput_d;    /* '<S61>/Memory' */
  boolean_T Memory_PreviousInput_os;   /* '<S62>/Memory' */
  boolean_T Memory_PreviousInput_f;    /* '<S63>/Memory' */
  boolean_T Memory_PreviousInput_b;    /* '<S64>/Memory' */
} DW_FOC_FCF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T U_DC;                       /* '<Root>/U_DC [V]' */
  real32_T I_phA[9];                   /* '<Root>/I_ph [A]' */
  real32_T I_dq_RefA[2];               /* '<Root>/I_dq_Ref [A]' */
  real32_T phi_elrad;                  /* '<Root>/phi_el [rad]' */
  real32_T w_el_Ref_IfStarter;         /* '<Root>/w_el_Ref_IfStarter' */
  real32_T IfStarter_Active;           /* '<Root>/IfStarter_Active' */
  bus_BSW_FCF_t bus_BSW_FCF;           /* '<Root>/bus_BSW_FCF' */
  real32_T SysStateAct;                /* '<Root>/SysStateAct' */
  real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
  real32_T StateFOC;                   /* '<Root>/StateFOC' */
  real32_T FOC_Enable_PWM;             /* '<Root>/FOC_Enable_PWM' */
  real32_T global_reset_errors;        /* '<Root>/global_reset_errors' */
  real32_T SPEED_CTRL_Enable;          /* '<Root>/SPEED_CTRL_Enable' */
} ExtU_FOC_FCF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T DutyCycles01[9];            /* '<Root>/DutyCycles [0..1]' */
  real32_T I_dq_ActA[6];               /* '<Root>/I_dq_Act [A]' */
  real32_T ModInd[3];                  /* '<Root>/ModInd' */
  real32_T w_elrads;                   /* '<Root>/w_el [rad//s]' */
  boolean_T FOC_Error;                 /* '<Root>/FOC_Error' */
} ExtY_FOC_FCF_T;

/* Parameters (default storage) */
struct P_FOC_FCF_T_ {
  real32_T ENABLE_GateDriver_FLT_Error;/* Variable: ENABLE_GateDriver_FLT_Error
                                        * Referenced by: '<S7>/ENABLE_GateDriver_FLT_Error'
                                        */
  real32_T ENABLE_GateDriver_RDY_Error;/* Variable: ENABLE_GateDriver_RDY_Error
                                        * Referenced by: '<S7>/ENABLE_GateDriver_RDY_Error'
                                        */
  real32_T FOC_9ph_AngleShift;         /* Variable: FOC_9ph_AngleShift
                                        * Referenced by:
                                        *   '<S4>/FOC_9ph_AngleShift'
                                        *   '<S5>/FOC_9ph_AngleShift'
                                        *   '<S13>/FOC_9ph_AngleShift'
                                        */
  real32_T FOC_ASC_Mode;               /* Variable: FOC_ASC_Mode
                                        * Referenced by: '<S2>/FOC_AKS_Mode'
                                        */
  real32_T FOC_AngleObs_w_InitVal;     /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S18>/Unit Delay1'
                                        */
  real32_T FOC_AngleObserver_D;        /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S15>/Constant1'
                                        */
  real32_T FOC_AngleObserver_w0;       /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S15>/Constant'
                                        */
  real32_T FOC_ENABLE_Overcurrent_I_uvw;/* Variable: FOC_ENABLE_Overcurrent_I_uvw
                                         * Referenced by: '<S48>/FOC_ENABLE_Overcurrent_I_uvw1'
                                         */
  real32_T FOC_ENABLE_Overspeed;       /* Variable: FOC_ENABLE_Overspeed
                                        * Referenced by: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
                                        */
  real32_T FOC_ENABLE_Overvoltage_U_DC;/* Variable: FOC_ENABLE_Overvoltage_U_DC
                                        * Referenced by: '<S49>/FOC_ENABLE_Overvoltage_U_DC1'
                                        */
  real32_T FOC_ENABLE_Undervoltage_U_DC;/* Variable: FOC_ENABLE_Undervoltage_U_DC
                                         * Referenced by: '<S49>/FOC_ENABLE_Undervoltage_U_DC1'
                                         */
  real32_T FOC_Enable;                 /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
  real32_T FOC_If_f_el;                /* Variable: FOC_If_f_el
                                        * Referenced by: '<S9>/If_f_el'
                                        */
  real32_T FOC_IntegDamp;              /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S28>/FOC_IntegDamp'
                                        *   '<S32>/FOC_IntegDamp'
                                        *   '<S36>/FOC_IntegDamp'
                                        */
  real32_T FOC_KI;                     /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S28>/FOC_KI'
                                        *   '<S32>/FOC_KI'
                                        *   '<S36>/FOC_KI'
                                        */
  real32_T FOC_KP;                     /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S28>/FOC_KP1'
                                        *   '<S32>/FOC_KP1'
                                        *   '<S36>/FOC_KP1'
                                        */
  real32_T FOC_LIMIT_Overcurrent_I_uvw;/* Variable: FOC_LIMIT_Overcurrent_I_uvw
                                        * Referenced by:
                                        *   '<S50>/Constant'
                                        *   '<S51>/Constant'
                                        */
  real32_T FOC_LIMIT_Overvoltage_U_DC; /* Variable: FOC_LIMIT_Overvoltage_U_DC
                                        * Referenced by: '<S66>/Constant'
                                        */
  real32_T FOC_LIMIT_Undervoltage_U_DC;/* Variable: FOC_LIMIT_Undervoltage_U_DC
                                        * Referenced by: '<S65>/Constant'
                                        */
  real32_T FOC_MANUAL_Error;           /* Variable: FOC_MANUAL_Error
                                        * Referenced by: '<S1>/FOC_MANUAL_Error'
                                        */
  real32_T FOC_MANUAL_U_DC;            /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc1'
                                        */
  real32_T FOC_MaxModInd;              /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S27>/FOC_MaxModInd'
                                        *   '<S31>/FOC_MaxModInd'
                                        *   '<S35>/FOC_MaxModInd'
                                        */
  real32_T FOC_Mode_Intern;            /* Variable: FOC_Mode_Intern
                                        * Referenced by: '<S1>/FOC_Mode_Intern'
                                        */
  real32_T FOC_OmegaObs3;              /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S15>/Gain4'
                                        */
  real32_T FOC_PhiSensorTdead;         /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S15>/DeadTimeCompensation'
                                        */
  real32_T FOC_RESET_OC_Error;         /* Variable: FOC_RESET_OC_Error
                                        * Referenced by: '<S48>/Reset_OC_Error'
                                        */
  real32_T FOC_RESET_OS_Error;         /* Variable: FOC_RESET_OS_Error
                                        * Referenced by: '<S11>/Reset_OS_Error'
                                        */
  real32_T FOC_RESET_OV_Error;         /* Variable: FOC_RESET_OV_Error
                                        * Referenced by: '<S49>/Reset_OV_Error'
                                        */
  real32_T FOC_RESET_UV_Error;         /* Variable: FOC_RESET_UV_Error
                                        * Referenced by: '<S49>/Reset_UV_Error'
                                        */
  real32_T FOC_SELECT_Voltage_Assignment_UVW;
                                  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
                                   * Referenced by: '<S82>/Constant6'
                                   */
  real32_T FOC_Uf_U_max;               /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S78>/Saturation1'
                                        */
  real32_T FOC_Uf_U_min;               /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S78>/Saturation1'
                                        */
  real32_T FOC_Uf_Ud;                  /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S13>/Uf_Ud'
                                        */
  real32_T FOC_Uf_f_el;                /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S13>/Uf_w_el'
                                        */
  real32_T FOC_Uf_m;                   /* Variable: FOC_Uf_m
                                        * Referenced by: '<S78>/Gain'
                                        */
  real32_T FOC_output_trafo_delay;     /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S4>/FOC_output_trafo_delay'
                                        */
  real32_T FOC_phi_offset;             /* Variable: FOC_phi_offset
                                        * Referenced by: '<S3>/Constant'
                                        */
  real32_T LIMIT_MAX_Overspeed;        /* Variable: LIMIT_MAX_Overspeed
                                        * Referenced by: '<S73>/Constant'
                                        */
  real32_T enumState_FOC_IF;           /* Variable: enumState_FOC_IF
                                        * Referenced by: '<S6>/Constant'
                                        */
  uint8_T FOC_SELECT_Mode_Intern;      /* Variable: FOC_SELECT_Mode_Intern
                                        * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
                                        */
  uint8_T FOC_SELECT_Modulation;       /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S14>/Enable_SuperSinMod'
                                        */
  uint8_T FOC_SELECT_U_DC_INPUT;       /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
  uint8_T FOC_SELECT_phi;              /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real32_T AntiWindupGT_d_const;       /* Mask Parameter: AntiWindupGT_d_const
                                        * Referenced by: '<S29>/Constant'
                                        */
  real32_T AntiWindupGT_q_const;       /* Mask Parameter: AntiWindupGT_q_const
                                        * Referenced by: '<S30>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_n;     /* Mask Parameter: AntiWindupGT_d_const_n
                                        * Referenced by: '<S33>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_h;     /* Mask Parameter: AntiWindupGT_q_const_h
                                        * Referenced by: '<S34>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_f;     /* Mask Parameter: AntiWindupGT_d_const_f
                                        * Referenced by: '<S37>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_l;     /* Mask Parameter: AntiWindupGT_q_const_l
                                        * Referenced by: '<S38>/Constant'
                                        */
  uint32_T Mask_6Bits_Inv1_FLT_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv1_FLT_BitMask
                                   * Referenced by: '<S8>/Mask_6Bits_Inv1_FLT'
                                   */
  uint32_T MaskBit0_BitMask;           /* Mask Parameter: MaskBit0_BitMask
                                        * Referenced by: '<S41>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask;           /* Mask Parameter: MaskBit1_BitMask
                                        * Referenced by: '<S41>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask;           /* Mask Parameter: MaskBit2_BitMask
                                        * Referenced by: '<S41>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask;           /* Mask Parameter: MaskBit3_BitMask
                                        * Referenced by: '<S41>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask;           /* Mask Parameter: MaskBit4_BitMask
                                        * Referenced by: '<S41>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask;           /* Mask Parameter: MaskBit5_BitMask
                                        * Referenced by: '<S41>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv1_RDY_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv1_RDY_BitMask
                                   * Referenced by: '<S8>/Mask_6Bits_Inv1_RDY'
                                   */
  uint32_T MaskBit0_BitMask_b;         /* Mask Parameter: MaskBit0_BitMask_b
                                        * Referenced by: '<S42>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_j;         /* Mask Parameter: MaskBit1_BitMask_j
                                        * Referenced by: '<S42>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_m;         /* Mask Parameter: MaskBit2_BitMask_m
                                        * Referenced by: '<S42>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_i;         /* Mask Parameter: MaskBit3_BitMask_i
                                        * Referenced by: '<S42>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_d;         /* Mask Parameter: MaskBit4_BitMask_d
                                        * Referenced by: '<S42>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_a;         /* Mask Parameter: MaskBit5_BitMask_a
                                        * Referenced by: '<S42>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv2_FLT_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv2_FLT_BitMask
                                   * Referenced by: '<S8>/Mask_6Bits_Inv2_FLT'
                                   */
  uint32_T MaskBit0_BitMask_g;         /* Mask Parameter: MaskBit0_BitMask_g
                                        * Referenced by: '<S43>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_n;         /* Mask Parameter: MaskBit1_BitMask_n
                                        * Referenced by: '<S43>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_n;         /* Mask Parameter: MaskBit2_BitMask_n
                                        * Referenced by: '<S43>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_c;         /* Mask Parameter: MaskBit3_BitMask_c
                                        * Referenced by: '<S43>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_o;         /* Mask Parameter: MaskBit4_BitMask_o
                                        * Referenced by: '<S43>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_h;         /* Mask Parameter: MaskBit5_BitMask_h
                                        * Referenced by: '<S43>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv2_RDY_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv2_RDY_BitMask
                                   * Referenced by: '<S8>/Mask_6Bits_Inv2_RDY'
                                   */
  uint32_T MaskBit0_BitMask_bn;        /* Mask Parameter: MaskBit0_BitMask_bn
                                        * Referenced by: '<S44>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_a;         /* Mask Parameter: MaskBit1_BitMask_a
                                        * Referenced by: '<S44>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_o;         /* Mask Parameter: MaskBit2_BitMask_o
                                        * Referenced by: '<S44>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_h;         /* Mask Parameter: MaskBit3_BitMask_h
                                        * Referenced by: '<S44>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_e;         /* Mask Parameter: MaskBit4_BitMask_e
                                        * Referenced by: '<S44>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_l;         /* Mask Parameter: MaskBit5_BitMask_l
                                        * Referenced by: '<S44>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv3_FLT_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv3_FLT_BitMask
                                   * Referenced by: '<S8>/Mask_6Bits_Inv3_FLT'
                                   */
  uint32_T MaskBit0_BitMask_m;         /* Mask Parameter: MaskBit0_BitMask_m
                                        * Referenced by: '<S45>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_d;         /* Mask Parameter: MaskBit1_BitMask_d
                                        * Referenced by: '<S45>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_b;         /* Mask Parameter: MaskBit2_BitMask_b
                                        * Referenced by: '<S45>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_l;         /* Mask Parameter: MaskBit3_BitMask_l
                                        * Referenced by: '<S45>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_b;         /* Mask Parameter: MaskBit4_BitMask_b
                                        * Referenced by: '<S45>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_e;         /* Mask Parameter: MaskBit5_BitMask_e
                                        * Referenced by: '<S45>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv3_RDY_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv3_RDY_BitMask
                                   * Referenced by: '<S8>/Mask_6Bits_Inv3_RDY'
                                   */
  uint32_T MaskBit0_BitMask_l;         /* Mask Parameter: MaskBit0_BitMask_l
                                        * Referenced by: '<S46>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_dr;        /* Mask Parameter: MaskBit1_BitMask_dr
                                        * Referenced by: '<S46>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_bx;        /* Mask Parameter: MaskBit2_BitMask_bx
                                        * Referenced by: '<S46>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_it;        /* Mask Parameter: MaskBit3_BitMask_it
                                        * Referenced by: '<S46>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_a;         /* Mask Parameter: MaskBit4_BitMask_a
                                        * Referenced by: '<S46>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_b;         /* Mask Parameter: MaskBit5_BitMask_b
                                        * Referenced by: '<S46>/MaskBit5'
                                        */
  boolean_T SRFlipFlop_initial_condition;
                                 /* Mask Parameter: SRFlipFlop_initial_condition
                                  * Referenced by: '<S69>/Memory'
                                  */
  boolean_T SRFlipFlop1_initial_condition;
                                /* Mask Parameter: SRFlipFlop1_initial_condition
                                 * Referenced by: '<S70>/Memory'
                                 */
  boolean_T SRFlipFlop_initial_condition_d;
                               /* Mask Parameter: SRFlipFlop_initial_condition_d
                                * Referenced by: '<S54>/Memory'
                                */
  boolean_T SRFlipFlop_initial_condition_k;
                               /* Mask Parameter: SRFlipFlop_initial_condition_k
                                * Referenced by: '<S75>/Memory'
                                */
  boolean_T OverTemp_Latching_1_initial_con;
                              /* Mask Parameter: OverTemp_Latching_1_initial_con
                               * Referenced by: '<S56>/Memory'
                               */
  boolean_T OverTemp_Latching_2_initial_con;
                              /* Mask Parameter: OverTemp_Latching_2_initial_con
                               * Referenced by: '<S57>/Memory'
                               */
  boolean_T OverTemp_Latching_3_initial_con;
                              /* Mask Parameter: OverTemp_Latching_3_initial_con
                               * Referenced by: '<S58>/Memory'
                               */
  boolean_T OverTemp_Latching_4_initial_con;
                              /* Mask Parameter: OverTemp_Latching_4_initial_con
                               * Referenced by: '<S59>/Memory'
                               */
  boolean_T OverTemp_Latching_5_initial_con;
                              /* Mask Parameter: OverTemp_Latching_5_initial_con
                               * Referenced by: '<S60>/Memory'
                               */
  boolean_T OverTemp_Latching_6_initial_con;
                              /* Mask Parameter: OverTemp_Latching_6_initial_con
                               * Referenced by: '<S61>/Memory'
                               */
  boolean_T OverTemp_Latching_7_initial_con;
                              /* Mask Parameter: OverTemp_Latching_7_initial_con
                               * Referenced by: '<S62>/Memory'
                               */
  boolean_T OverTemp_Latching_8_initial_con;
                              /* Mask Parameter: OverTemp_Latching_8_initial_con
                               * Referenced by: '<S63>/Memory'
                               */
  boolean_T OverTemp_Latching_9_initial_con;
                              /* Mask Parameter: OverTemp_Latching_9_initial_con
                               * Referenced by: '<S64>/Memory'
                               */
  boolean_T DetectRisePositive1_vinit;
                                    /* Mask Parameter: DetectRisePositive1_vinit
                                     * Referenced by: '<S68>/Delay Input1'
                                     */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S67>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_g;
                                   /* Mask Parameter: DetectRisePositive_vinit_g
                                    * Referenced by: '<S52>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_f;
                                   /* Mask Parameter: DetectRisePositive_vinit_f
                                    * Referenced by: '<S74>/Delay Input1'
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
                                        * Referenced by: '<S17>/Constant5'
                                        */
  real32_T Constant6_Value;            /* Computed Parameter: Constant6_Value
                                        * Referenced by: '<S17>/Constant6'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S17>/Constant2'
                                        */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S17>/Constant4'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S20>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S20>/Constant1'
                                        */
  real32_T Zero_Value;                 /* Computed Parameter: Zero_Value
                                        * Referenced by: '<S28>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold;
                               /* Computed Parameter: IntegStopSwitch3_Threshold
                                * Referenced by: '<S28>/IntegStopSwitch3'
                                */
  real32_T Zero_Value_o;               /* Computed Parameter: Zero_Value_o
                                        * Referenced by: '<S32>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold_a;
                             /* Computed Parameter: IntegStopSwitch3_Threshold_a
                              * Referenced by: '<S32>/IntegStopSwitch3'
                              */
  real32_T Zero_Value_n;               /* Computed Parameter: Zero_Value_n
                                        * Referenced by: '<S36>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold_ad;
                            /* Computed Parameter: IntegStopSwitch3_Threshold_ad
                             * Referenced by: '<S36>/IntegStopSwitch3'
                             */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S47>/Gain1'
                                        */
  real32_T Constant1_Value_c;          /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<S47>/Constant1'
                                        */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S49>/Constant3'
                                        */
  real32_T Constant1_Value_b;          /* Computed Parameter: Constant1_Value_b
                                        * Referenced by: '<S49>/Constant1'
                                        */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S12>/Gain1'
                                        */
  real32_T Constant1_Value_k;          /* Computed Parameter: Constant1_Value_k
                                        * Referenced by: '<S12>/Constant1'
                                        */
  real32_T Constant1_Value_bt;         /* Computed Parameter: Constant1_Value_bt
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S16>/Constant'
                                        */
  real32_T Constant1_Value_g;          /* Computed Parameter: Constant1_Value_g
                                        * Referenced by: '<S16>/Constant1'
                                        */
  real32_T Switch1_Threshold;          /* Computed Parameter: Switch1_Threshold
                                        * Referenced by: '<S16>/Switch1'
                                        */
  real32_T Switch2_Threshold;          /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S16>/Switch2'
                                        */
  real32_T Gain1_Gain_a;               /* Computed Parameter: Gain1_Gain_a
                                        * Referenced by: '<S77>/Gain1'
                                        */
  real32_T Constant1_Value_e;          /* Computed Parameter: Constant1_Value_e
                                        * Referenced by: '<S77>/Constant1'
                                        */
  real32_T Constant2_Value_d;          /* Computed Parameter: Constant2_Value_d
                                        * Referenced by: '<S80>/Constant2'
                                        */
  real32_T U_DC2_Gain;                 /* Computed Parameter: U_DC2_Gain
                                        * Referenced by: '<S80>/U_DC//2'
                                        */
  real32_T Constant2_Value_g;          /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S81>/Constant2'
                                        */
  real32_T U_DC2_Gain_p;               /* Computed Parameter: U_DC2_Gain_p
                                        * Referenced by: '<S81>/U_DC//2'
                                        */
  real32_T Factor_Gain;                /* Computed Parameter: Factor_Gain
                                        * Referenced by: '<S83>/Factor'
                                        */
  real32_T Factor1_Gain;               /* Computed Parameter: Factor1_Gain
                                        * Referenced by: '<S83>/Factor1'
                                        */
  real32_T Factor2_Gain;               /* Computed Parameter: Factor2_Gain
                                        * Referenced by: '<S83>/Factor2'
                                        */
  real32_T Constant_Value_d[6];        /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S84>/Constant'
                                        */
  real32_T Null_Value[9];              /* Computed Parameter: Null_Value
                                        * Referenced by: '<S1>/Null'
                                        */
  real32_T DiscreteTransferFcn_NumCoef;
                              /* Computed Parameter: DiscreteTransferFcn_NumCoef
                               * Referenced by: '<S13>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_DenCoef[2];
                              /* Computed Parameter: DiscreteTransferFcn_DenCoef
                               * Referenced by: '<S13>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_InitialStat;
                          /* Computed Parameter: DiscreteTransferFcn_InitialStat
                           * Referenced by: '<S13>/Discrete Transfer Fcn'
                           */
  real32_T f_2_w_el_Gain;              /* Computed Parameter: f_2_w_el_Gain
                                        * Referenced by: '<S13>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value;           /* Computed Parameter: FOC_T_fast_Value
                                        * Referenced by: '<S77>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S77>/Unit Delay'
                                */
  real32_T TrafoMatrixuvwalphabeta_Gain[6];
                             /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
                              * Referenced by: '<S24>/TrafoMatrix uvw->alphabeta'
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
                              * Referenced by: '<S17>/Unit Delay'
                              */
  real32_T Constant3_Value_l;          /* Computed Parameter: Constant3_Value_l
                                        * Referenced by: '<S17>/Constant3'
                                        */
  real32_T Constant1_Value_ep;         /* Computed Parameter: Constant1_Value_ep
                                        * Referenced by: '<S17>/Constant1'
                                        */
  real32_T UnitDelay3_InitialCondition;
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S15>/Unit Delay3'
                               */
  real32_T FOC_T_fast_Value_d;         /* Computed Parameter: FOC_T_fast_Value_d
                                        * Referenced by: '<S12>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_p;
                             /* Computed Parameter: UnitDelay_InitialCondition_p
                              * Referenced by: '<S12>/Unit Delay'
                              */
  real32_T f_2_w_el_Gain_j;            /* Computed Parameter: f_2_w_el_Gain_j
                                        * Referenced by: '<S9>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value_f;         /* Computed Parameter: FOC_T_fast_Value_f
                                        * Referenced by: '<S47>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_d;
                             /* Computed Parameter: UnitDelay_InitialCondition_d
                              * Referenced by: '<S47>/Unit Delay'
                              */
  real32_T IntegDelay1_InitialCondition;
                             /* Computed Parameter: IntegDelay1_InitialCondition
                              * Referenced by: '<S28>/IntegDelay1'
                              */
  real32_T FOC_T_fast_Value_n;         /* Computed Parameter: FOC_T_fast_Value_n
                                        * Referenced by: '<S28>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_p[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
                            * Referenced by: '<S25>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_m;
                           /* Computed Parameter: IntegDelay1_InitialCondition_m
                            * Referenced by: '<S32>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_e;         /* Computed Parameter: FOC_T_fast_Value_e
                                        * Referenced by: '<S32>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_j[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_j
                            * Referenced by: '<S26>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_p;
                           /* Computed Parameter: IntegDelay1_InitialCondition_p
                            * Referenced by: '<S36>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_er;       /* Computed Parameter: FOC_T_fast_Value_er
                                       * Referenced by: '<S36>/FOC_T_fast'
                                       */
  real32_T FOC_T_fast_Value_m;         /* Computed Parameter: FOC_T_fast_Value_m
                                        * Referenced by: '<S4>/FOC_T_fast'
                                        */
  real32_T Switch1_Threshold_a;       /* Computed Parameter: Switch1_Threshold_a
                                       * Referenced by: '<S20>/Switch1'
                                       */
  real32_T Switch2_Threshold_o;       /* Computed Parameter: Switch2_Threshold_o
                                       * Referenced by: '<S20>/Switch2'
                                       */
  real32_T Gain1_Gain_h[4];            /* Computed Parameter: Gain1_Gain_h
                                        * Referenced by: '<S87>/Gain1'
                                        */
  real32_T Gain_Gain[4];               /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S87>/Gain'
                                        */
  real32_T Constant_Value_g[6];        /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S85>/Constant'
                                        */
  real32_T Gain1_Gain_ck[4];           /* Computed Parameter: Gain1_Gain_ck
                                        * Referenced by: '<S88>/Gain1'
                                        */
  real32_T Gain_Gain_l[4];             /* Computed Parameter: Gain_Gain_l
                                        * Referenced by: '<S88>/Gain'
                                        */
  real32_T Constant_Value_o[6];        /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S86>/Constant'
                                        */
  real32_T Gain1_Gain_k[4];            /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S89>/Gain1'
                                        */
  real32_T Gain_Gain_j[4];             /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S89>/Gain'
                                        */
  real32_T Scale02_Bias;               /* Computed Parameter: Scale02_Bias
                                        * Referenced by: '<S79>/Scale [0..2]'
                                        */
  real32_T Scale01_Gain;               /* Computed Parameter: Scale01_Gain
                                        * Referenced by: '<S79>/Scale  [0..1]'
                                        */
  real32_T Limit01_UpperSat;           /* Computed Parameter: Limit01_UpperSat
                                        * Referenced by: '<S79>/Limit [0..1]'
                                        */
  real32_T Limit01_LowerSat;           /* Computed Parameter: Limit01_LowerSat
                                        * Referenced by: '<S79>/Limit [0..1]'
                                        */
  real32_T FOC_T_fast_Value_df;       /* Computed Parameter: FOC_T_fast_Value_df
                                       * Referenced by: '<S15>/FOC_T_fast'
                                       */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S15>/Gain'
                                        */
  real32_T UnitDelay1_InitialCondition;
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<S19>/Unit Delay1'
                               */
  real32_T FOC_T_fast_Value_c;         /* Computed Parameter: FOC_T_fast_Value_c
                                        * Referenced by: '<S18>/FOC_T_fast'
                                        */
  real32_T FOC_T_fast_Value_k;         /* Computed Parameter: FOC_T_fast_Value_k
                                        * Referenced by: '<S19>/FOC_T_fast'
                                        */
  real32_T Gain1_Gain_kl;              /* Computed Parameter: Gain1_Gain_kl
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real32_T Zero1_Value[2];             /* Computed Parameter: Zero1_Value
                                        * Referenced by: '<S28>/Zero1'
                                        */
  real32_T Gain1_Gain_cs;              /* Computed Parameter: Gain1_Gain_cs
                                        * Referenced by: '<S21>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S21>/Gain2'
                                        */
  real32_T Zero1_Value_l[2];           /* Computed Parameter: Zero1_Value_l
                                        * Referenced by: '<S32>/Zero1'
                                        */
  real32_T Zero1_Value_o[2];           /* Computed Parameter: Zero1_Value_o
                                        * Referenced by: '<S36>/Zero1'
                                        */
  real32_T DiscreteFIRFilter20thorder_Init;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Init
                           * Referenced by: '<S24>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Coef[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
                           * Referenced by: '<S24>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_k;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
                           * Referenced by: '<S25>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_a[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
                           * Referenced by: '<S25>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_n;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_n
                           * Referenced by: '<S26>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_l[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_l
                           * Referenced by: '<S26>/Discrete FIR Filter 20th order'
                           */
  real32_T NO_ERROR_Value;             /* Computed Parameter: NO_ERROR_Value
                                        * Referenced by: '<S7>/NO_ERROR'
                                        */
  real32_T usrpm_Gain;                 /* Computed Parameter: usrpm_Gain
                                        * Referenced by: '<S11>/[1//s] => [rpm]'
                                        */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S47>/Switch'
                                        */
  real32_T Switch_Threshold_b;         /* Computed Parameter: Switch_Threshold_b
                                        * Referenced by: '<S12>/Switch'
                                        */
  real32_T Switch_Threshold_c;         /* Computed Parameter: Switch_Threshold_c
                                        * Referenced by: '<S77>/Switch'
                                        */
  real32_T Gain_Gain_jm;               /* Computed Parameter: Gain_Gain_jm
                                        * Referenced by: '<S14>/Gain'
                                        */
  real32_T Gain1_Gain_e;               /* Computed Parameter: Gain1_Gain_e
                                        * Referenced by: '<S14>/Gain1'
                                        */
  real32_T Gain2_Gain_f;               /* Computed Parameter: Gain2_Gain_f
                                        * Referenced by: '<S14>/Gain2'
                                        */
  real32_T Gain3_Gain;                 /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<S14>/Gain3'
                                        */
  real32_T DutyCycle_u1_Gain;          /* Computed Parameter: DutyCycle_u1_Gain
                                        * Referenced by: '<S82>/DutyCycle_u1'
                                        */
  real32_T DutyCycle_u2_Gain;          /* Computed Parameter: DutyCycle_u2_Gain
                                        * Referenced by: '<S82>/DutyCycle_u2'
                                        */
  real32_T DutyCycle_u3_Gain;          /* Computed Parameter: DutyCycle_u3_Gain
                                        * Referenced by: '<S82>/DutyCycle_u3'
                                        */
  real32_T DutyCycle_v1_Gain;          /* Computed Parameter: DutyCycle_v1_Gain
                                        * Referenced by: '<S82>/DutyCycle_v1'
                                        */
  real32_T DutyCycle_v2_Gain;          /* Computed Parameter: DutyCycle_v2_Gain
                                        * Referenced by: '<S82>/DutyCycle_v2'
                                        */
  real32_T DutyCycle_v3_Gain;          /* Computed Parameter: DutyCycle_v3_Gain
                                        * Referenced by: '<S82>/DutyCycle_v3'
                                        */
  real32_T DutyCycle_w1_Gain;          /* Computed Parameter: DutyCycle_w1_Gain
                                        * Referenced by: '<S82>/DutyCycle_w1'
                                        */
  real32_T DutyCycle_w2_Gain;          /* Computed Parameter: DutyCycle_w2_Gain
                                        * Referenced by: '<S82>/DutyCycle_w2'
                                        */
  real32_T DutyCycle_w3_Gain;          /* Computed Parameter: DutyCycle_w3_Gain
                                        * Referenced by: '<S82>/DutyCycle_w3'
                                        */
  real32_T Counter_Start_Value;       /* Computed Parameter: Counter_Start_Value
                                       * Referenced by: '<S1>/Counter_Start'
                                       */
  real32_T FCF_Cnt_InitialCondition;
                                 /* Computed Parameter: FCF_Cnt_InitialCondition
                                  * Referenced by: '<S1>/FCF_Cnt'
                                  */
  uint32_T Constant_Value_d2;          /* Computed Parameter: Constant_Value_d2
                                        * Referenced by: '<S39>/Constant'
                                        */
  uint32_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S40>/Constant'
                                        */
  boolean_T NoError_Manual_Value;    /* Computed Parameter: NoError_Manual_Value
                                      * Referenced by: '<S7>/NoError_Manual'
                                      */
  boolean_T Constant2_Value_f;         /* Computed Parameter: Constant2_Value_f
                                        * Referenced by: '<S48>/Constant2'
                                        */
  boolean_T Constant1_Value_d;         /* Computed Parameter: Constant1_Value_d
                                        * Referenced by: '<S48>/Constant1'
                                        */
  boolean_T Constant2_Value_c;         /* Computed Parameter: Constant2_Value_c
                                        * Referenced by: '<S49>/Constant2'
                                        */
  boolean_T Constant4_Value_f;         /* Computed Parameter: Constant4_Value_f
                                        * Referenced by: '<S49>/Constant4'
                                        */
  boolean_T Constant2_Value_gw;        /* Computed Parameter: Constant2_Value_gw
                                        * Referenced by: '<S11>/Constant2'
                                        */
  boolean_T Constant1_Value_n;         /* Computed Parameter: Constant1_Value_n
                                        * Referenced by: '<S11>/Constant1'
                                        */
  boolean_T Constant_Value_j;          /* Computed Parameter: Constant_Value_j
                                        * Referenced by: '<S55>/Constant'
                                        */
  boolean_T Constant_Value_dc;         /* Computed Parameter: Constant_Value_dc
                                        * Referenced by: '<S71>/Constant'
                                        */
  boolean_T Constant_Value_eo;         /* Computed Parameter: Constant_Value_eo
                                        * Referenced by: '<S72>/Constant'
                                        */
  boolean_T Constant_Value_ep;         /* Computed Parameter: Constant_Value_ep
                                        * Referenced by: '<S76>/Constant'
                                        */
  boolean_T Logic_table[16];           /* Computed Parameter: Logic_table
                                        * Referenced by: '<S69>/Logic'
                                        */
  boolean_T Logic_table_l[16];         /* Computed Parameter: Logic_table_l
                                        * Referenced by: '<S70>/Logic'
                                        */
  boolean_T Logic_table_o[16];         /* Computed Parameter: Logic_table_o
                                        * Referenced by: '<S54>/Logic'
                                        */
  boolean_T SELECT_DataSource_Value;
                                  /* Computed Parameter: SELECT_DataSource_Value
                                   * Referenced by: '<S7>/SELECT_DataSource'
                                   */
  boolean_T Logic_table_lc[16];        /* Computed Parameter: Logic_table_lc
                                        * Referenced by: '<S75>/Logic'
                                        */
  boolean_T Logic_table_l5[16];        /* Computed Parameter: Logic_table_l5
                                        * Referenced by: '<S56>/Logic'
                                        */
  boolean_T Logic_table_p[16];         /* Computed Parameter: Logic_table_p
                                        * Referenced by: '<S57>/Logic'
                                        */
  boolean_T Logic_table_j[16];         /* Computed Parameter: Logic_table_j
                                        * Referenced by: '<S58>/Logic'
                                        */
  boolean_T Logic_table_o1[16];        /* Computed Parameter: Logic_table_o1
                                        * Referenced by: '<S59>/Logic'
                                        */
  boolean_T Logic_table_i[16];         /* Computed Parameter: Logic_table_i
                                        * Referenced by: '<S60>/Logic'
                                        */
  boolean_T Logic_table_c[16];         /* Computed Parameter: Logic_table_c
                                        * Referenced by: '<S61>/Logic'
                                        */
  boolean_T Logic_table_ij[16];        /* Computed Parameter: Logic_table_ij
                                        * Referenced by: '<S62>/Logic'
                                        */
  boolean_T Logic_table_pd[16];        /* Computed Parameter: Logic_table_pd
                                        * Referenced by: '<S63>/Logic'
                                        */
  boolean_T Logic_table_a[16];         /* Computed Parameter: Logic_table_a
                                        * Referenced by: '<S64>/Logic'
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
 * '<S7>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Error_Handling'
 * '<S8>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status'
 * '<S9>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/I_f'
 * '<S10>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis'
 * '<S11>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis'
 * '<S12>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/SubS_2pi_Integrator'
 * '<S13>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f'
 * '<S14>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output'
 * '<S15>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver'
 * '<S16>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/Modulo2Pi'
 * '<S17>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/2PiKorr'
 * '<S18>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator'
 * '<S19>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator1'
 * '<S20>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Lead/Modulo2Pi'
 * '<S21>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1'
 * '<S22>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2'
 * '<S23>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3'
 * '<S24>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_1'
 * '<S25>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_2'
 * '<S26>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_3'
 * '<S27>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup'
 * '<S28>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/FeedbackPI'
 * '<S29>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_d'
 * '<S30>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_q'
 * '<S31>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup'
 * '<S32>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/FeedbackPI'
 * '<S33>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_d'
 * '<S34>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_q'
 * '<S35>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup'
 * '<S36>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/FeedbackPI'
 * '<S37>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup/AntiWindupGT_d'
 * '<S38>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup/AntiWindupGT_q'
 * '<S39>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Compare To Zero'
 * '<S40>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Compare To Zero1'
 * '<S41>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv1_FLT'
 * '<S42>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv1_RDY'
 * '<S43>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv2_FLT'
 * '<S44>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv2_RDY'
 * '<S45>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv3_FLT'
 * '<S46>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv3_RDY'
 * '<S47>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/I_f/SubS_2pi_Integrator'
 * '<S48>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection'
 * '<S49>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection'
 * '<S50>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Compare To Constant'
 * '<S51>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Compare To Constant1'
 * '<S52>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Detect Rise Positive'
 * '<S53>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching'
 * '<S54>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/S-R Flip-Flop'
 * '<S55>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Detect Rise Positive/Positive'
 * '<S56>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_1'
 * '<S57>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_2'
 * '<S58>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_3'
 * '<S59>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_4'
 * '<S60>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_5'
 * '<S61>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_6'
 * '<S62>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_7'
 * '<S63>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_8'
 * '<S64>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_9'
 * '<S65>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Compare To Constant'
 * '<S66>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Compare To Constant1'
 * '<S67>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive'
 * '<S68>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive1'
 * '<S69>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/S-R Flip-Flop'
 * '<S70>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/S-R Flip-Flop1'
 * '<S71>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive/Positive'
 * '<S72>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive1/Positive'
 * '<S73>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/Compare To Constant1'
 * '<S74>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/Detect Rise Positive'
 * '<S75>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/S-R Flip-Flop'
 * '<S76>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/Detect Rise Positive/Positive'
 * '<S77>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/SubS_2pi_Integrator'
 * '<S78>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/UfKennlinie'
 * '<S79>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Adjust_duty_cycle_range'
 * '<S80>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Calc_Modulation_Index'
 * '<S81>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/NormalizedVoltage'
 * '<S82>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Phase_Assignment'
 * '<S83>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Super_Sinus_Modulation'
 * '<S84>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_1'
 * '<S85>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_2'
 * '<S86>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_3'
 * '<S87>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_1'
 * '<S88>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_2'
 * '<S89>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_3'
 */
#endif                                 /* FOC_FCF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
