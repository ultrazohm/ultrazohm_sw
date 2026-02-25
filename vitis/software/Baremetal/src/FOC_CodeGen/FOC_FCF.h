/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.h
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.74
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 25 10:30:19 2026
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
  bus_InvStatus_t bus_InvStatus;       /* '<S9>/Bus Creator' */
  uint32_T Mask_6Bits_Inv1_FLT;        /* '<S9>/Mask_6Bits_Inv1_FLT' */
  uint32_T BitwiseNOT;                 /* '<S49>/Bitwise NOT' */
  uint32_T MaskBit0;                   /* '<S49>/MaskBit0' */
  uint32_T get_U_HS_FLT;               /* '<S49>/get_U_HS_FLT' */
  uint32_T MaskBit1;                   /* '<S49>/MaskBit1' */
  uint32_T get_U_LS_FLT;               /* '<S49>/get_U_LS_FLT' */
  uint32_T MaskBit2;                   /* '<S49>/MaskBit2' */
  uint32_T get_V_HS_FLT;               /* '<S49>/get_V_HS_FLT' */
  uint32_T MaskBit3;                   /* '<S49>/MaskBit3' */
  uint32_T get_V_LS_FLT;               /* '<S49>/get_V_LS_FLT' */
  uint32_T MaskBit4;                   /* '<S49>/MaskBit4' */
  uint32_T get_W_HS_FLT;               /* '<S49>/get_W_HS_FLT' */
  uint32_T MaskBit5;                   /* '<S49>/MaskBit5' */
  uint32_T get_W_LS_FLT;               /* '<S49>/get_W_LS_FLT' */
  uint32_T Mask_6Bits_Inv1_RDY;        /* '<S9>/Mask_6Bits_Inv1_RDY' */
  uint32_T MaskBit0_c;                 /* '<S50>/MaskBit0' */
  uint32_T get_U_HS_RDY;               /* '<S50>/get_U_HS_RDY' */
  uint32_T MaskBit1_b;                 /* '<S50>/MaskBit1' */
  uint32_T get_U_LS_RDY;               /* '<S50>/get_U_LS_RDY' */
  uint32_T MaskBit2_n;                 /* '<S50>/MaskBit2' */
  uint32_T get_V_HS_RDY;               /* '<S50>/get_V_HS_RDY' */
  uint32_T MaskBit3_a;                 /* '<S50>/MaskBit3' */
  uint32_T get_V_LS_RDY;               /* '<S50>/get_V_LS_RDY' */
  uint32_T MaskBit4_c;                 /* '<S50>/MaskBit4' */
  uint32_T get_W_HS_RDY;               /* '<S50>/get_W_HS_RDY' */
  uint32_T MaskBit5_l;                 /* '<S50>/MaskBit5' */
  uint32_T get_W_LS_RDY;               /* '<S50>/get_W_LS_RDY' */
  uint32_T Mask_6Bits_Inv2_FLT;        /* '<S9>/Mask_6Bits_Inv2_FLT' */
  uint32_T BitwiseNOT_j;               /* '<S51>/Bitwise NOT' */
  uint32_T MaskBit0_o;                 /* '<S51>/MaskBit0' */
  uint32_T get_U_HS_FLT_i;             /* '<S51>/get_U_HS_FLT' */
  uint32_T MaskBit1_ba;                /* '<S51>/MaskBit1' */
  uint32_T get_U_LS_FLT_a;             /* '<S51>/get_U_LS_FLT' */
  uint32_T MaskBit2_d;                 /* '<S51>/MaskBit2' */
  uint32_T get_V_HS_FLT_i;             /* '<S51>/get_V_HS_FLT' */
  uint32_T MaskBit3_d;                 /* '<S51>/MaskBit3' */
  uint32_T get_V_LS_FLT_c;             /* '<S51>/get_V_LS_FLT' */
  uint32_T MaskBit4_p;                 /* '<S51>/MaskBit4' */
  uint32_T get_W_HS_FLT_f;             /* '<S51>/get_W_HS_FLT' */
  uint32_T MaskBit5_o;                 /* '<S51>/MaskBit5' */
  uint32_T get_W_LS_FLT_l;             /* '<S51>/get_W_LS_FLT' */
  uint32_T Mask_6Bits_Inv2_RDY;        /* '<S9>/Mask_6Bits_Inv2_RDY' */
  uint32_T MaskBit0_p;                 /* '<S52>/MaskBit0' */
  uint32_T get_U_HS_RDY_i;             /* '<S52>/get_U_HS_RDY' */
  uint32_T MaskBit1_m;                 /* '<S52>/MaskBit1' */
  uint32_T get_U_LS_RDY_f;             /* '<S52>/get_U_LS_RDY' */
  uint32_T MaskBit2_g;                 /* '<S52>/MaskBit2' */
  uint32_T get_V_HS_RDY_j;             /* '<S52>/get_V_HS_RDY' */
  uint32_T MaskBit3_k;                 /* '<S52>/MaskBit3' */
  uint32_T get_V_LS_RDY_a;             /* '<S52>/get_V_LS_RDY' */
  uint32_T MaskBit4_l;                 /* '<S52>/MaskBit4' */
  uint32_T get_W_HS_RDY_n;             /* '<S52>/get_W_HS_RDY' */
  uint32_T MaskBit5_lb;                /* '<S52>/MaskBit5' */
  uint32_T get_W_LS_RDY_l;             /* '<S52>/get_W_LS_RDY' */
  uint32_T Mask_6Bits_Inv3_FLT;        /* '<S9>/Mask_6Bits_Inv3_FLT' */
  uint32_T BitwiseNOT_c;               /* '<S53>/Bitwise NOT' */
  uint32_T MaskBit0_ph;                /* '<S53>/MaskBit0' */
  uint32_T get_U_HS_FLT_m;             /* '<S53>/get_U_HS_FLT' */
  uint32_T MaskBit1_k;                 /* '<S53>/MaskBit1' */
  uint32_T get_U_LS_FLT_h;             /* '<S53>/get_U_LS_FLT' */
  uint32_T MaskBit2_f;                 /* '<S53>/MaskBit2' */
  uint32_T get_V_HS_FLT_h;             /* '<S53>/get_V_HS_FLT' */
  uint32_T MaskBit3_a2;                /* '<S53>/MaskBit3' */
  uint32_T get_V_LS_FLT_g;             /* '<S53>/get_V_LS_FLT' */
  uint32_T MaskBit4_f;                 /* '<S53>/MaskBit4' */
  uint32_T get_W_HS_FLT_m;             /* '<S53>/get_W_HS_FLT' */
  uint32_T MaskBit5_h;                 /* '<S53>/MaskBit5' */
  uint32_T get_W_LS_FLT_g;             /* '<S53>/get_W_LS_FLT' */
  uint32_T Mask_6Bits_Inv3_RDY;        /* '<S9>/Mask_6Bits_Inv3_RDY' */
  uint32_T MaskBit0_k;                 /* '<S54>/MaskBit0' */
  uint32_T get_U_HS_RDY_e;             /* '<S54>/get_U_HS_RDY' */
  uint32_T MaskBit1_o;                 /* '<S54>/MaskBit1' */
  uint32_T get_U_LS_RDY_l;             /* '<S54>/get_U_LS_RDY' */
  uint32_T MaskBit2_a;                 /* '<S54>/MaskBit2' */
  uint32_T get_V_HS_RDY_e;             /* '<S54>/get_V_HS_RDY' */
  uint32_T MaskBit3_kg;                /* '<S54>/MaskBit3' */
  uint32_T get_V_LS_RDY_k;             /* '<S54>/get_V_LS_RDY' */
  uint32_T MaskBit4_ch;                /* '<S54>/MaskBit4' */
  uint32_T get_W_HS_RDY_h;             /* '<S54>/get_W_HS_RDY' */
  uint32_T MaskBit5_p;                 /* '<S54>/MaskBit5' */
  uint32_T get_W_LS_RDY_m;             /* '<S54>/get_W_LS_RDY' */
  real32_T Sum[9];                     /* '<S20>/Sum' */
  real32_T i_uvw_cal[9];               /* '<S20>/i_uvw_cal' */
  real32_T Gain;                       /* '<S20>/Gain' */
  real32_T Gain1;                      /* '<S20>/Gain1' */
  real32_T Gain2;                      /* '<S20>/Gain2' */
  real32_T Select_CurrentSensor_Assignment[3];
                                 /* '<S19>/Select_CurrentSensor_Assignment_1' */
  real32_T Gain3;                      /* '<S20>/Gain3' */
  real32_T Gain4;                      /* '<S20>/Gain4' */
  real32_T Gain5;                      /* '<S20>/Gain5' */
  real32_T Select_CurrentSensor_Assignme_o[3];
                                 /* '<S19>/Select_CurrentSensor_Assignment_2' */
  real32_T Gain6;                      /* '<S20>/Gain6' */
  real32_T Gain7;                      /* '<S20>/Gain7' */
  real32_T Gain8;                      /* '<S20>/Gain8' */
  real32_T Select_CurrentSensor_Assignm_on[3];
                                 /* '<S19>/Select_CurrentSensor_Assignment_3' */
  real32_T I_ph[9];                    /* '<S2>/Gain' */
  real32_T U_DC_fcf;                   /* '<S17>/U_DC_switch' */
  real32_T FOC_Mode_Request;           /* '<S1>/ModeSwitch' */
  real32_T U_DC_Undervoltage_Error;    /* '<S63>/Selectphicalc1' */
  real32_T U_DC_Overvoltage_Error;     /* '<S63>/Selectphicalc2' */
  real32_T Abs[9];                     /* '<S62>/Abs' */
  real32_T MinMax;                     /* '<S62>/MinMax' */
  real32_T FOC_Mode_after_checks;      /* '<S1>/Switch' */
  real32_T DiscreteTransferFcn;        /* '<S14>/Discrete Transfer Fcn' */
  real32_T f_2_w_el;                   /* '<S14>/f_2_w_el' */
  real32_T Product;                    /* '<S91>/Product' */
  real32_T UnitDelay;                  /* '<S91>/Unit Delay' */
  real32_T Add;                        /* '<S91>/Add' */
  real32_T TrafoMatrixuvwalphabeta[2]; /* '<S33>/TrafoMatrix uvw->alphabeta' */
  real32_T ResolverOffsetLimitation;   /* '<S4>/ResolverOffsetLimitation' */
  real32_T Sum1;                       /* '<S4>/Sum1' */
  real32_T w_el;                       /* '<S27>/Unit Delay1' */
  real32_T DeadTimeCompensation;       /* '<S24>/DeadTimeCompensation' */
  real32_T Sum3;                       /* '<S24>/Sum3' */
  real32_T UnitDelay_l;                /* '<S26>/Unit Delay' */
  real32_T Sum_d;                      /* '<S26>/Sum' */
  real32_T Switch;                     /* '<S26>/Switch' */
  real32_T Switch1;                    /* '<S26>/Switch1' */
  real32_T Sum2;                       /* '<S26>/Sum2' */
  real32_T UnitDelay3;                 /* '<S24>/Unit Delay3' */
  real32_T phi_el_observer;            /* '<S24>/Sum7' */
  real32_T Product_e;                  /* '<S13>/Product' */
  real32_T UnitDelay_a;                /* '<S13>/Unit Delay' */
  real32_T Add_m;                      /* '<S13>/Add' */
  real32_T f_2_w_el_b;                 /* '<S10>/f_2_w_el' */
  real32_T Product_h;                  /* '<S61>/Product' */
  real32_T UnitDelay_j;                /* '<S61>/Unit Delay' */
  real32_T Add_mp;                     /* '<S61>/Add' */
  real32_T Use_If_Mode[2];             /* '<S1>/Use_If_Mode' */
  real32_T TrigonometricFunction1;     /* '<S33>/Trigonometric Function1' */
  real32_T TrafoProd;                  /* '<S33>/TrafoProd' */
  real32_T TrigonometricFunction;      /* '<S33>/Trigonometric Function' */
  real32_T TrafoProd3;                 /* '<S33>/TrafoProd3' */
  real32_T I_d1_Act;                   /* '<S33>/I_d1_Act' */
  real32_T TrafoProd1;                 /* '<S33>/TrafoProd1' */
  real32_T TrafoProd2;                 /* '<S33>/TrafoProd2' */
  real32_T I_q1_Act;                   /* '<S33>/I_q1_Act' */
  real32_T TmpSignalConversionAtDiscreteFI[2];
  real32_T IdqErr[2];                  /* '<S30>/IdqErr' */
  real32_T KPek1[2];                   /* '<S37>/KP*e[k]1' */
  real32_T IntegDelay1[2];             /* '<S37>/IntegDelay1' */
  real32_T Product1;                   /* '<S37>/Product1' */
  real32_T IntegEnaSwitch1[2];         /* '<S37>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_h[2];/* '<S34>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum1_d;                     /* '<S6>/Sum1' */
  real32_T TrigonometricFunction1_b;   /* '<S34>/Trigonometric Function1' */
  real32_T TrafoProd_a;                /* '<S34>/TrafoProd' */
  real32_T TrigonometricFunction_l;    /* '<S34>/Trigonometric Function' */
  real32_T TrafoProd3_i;               /* '<S34>/TrafoProd3' */
  real32_T TrafoSum;                   /* '<S34>/TrafoSum' */
  real32_T TrafoProd1_b;               /* '<S34>/TrafoProd1' */
  real32_T TrafoProd2_b;               /* '<S34>/TrafoProd2' */
  real32_T TrafoSum1;                  /* '<S34>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_k[2];
  real32_T IdqErr_l[2];                /* '<S31>/IdqErr' */
  real32_T KPek1_l[2];                 /* '<S41>/KP*e[k]1' */
  real32_T IntegDelay1_o[2];           /* '<S41>/IntegDelay1' */
  real32_T Product1_k;                 /* '<S41>/Product1' */
  real32_T IntegEnaSwitch1_n[2];       /* '<S41>/IntegEnaSwitch1' */
  real32_T TrafoMatrixuvwalphabeta_m[2];/* '<S35>/TrafoMatrix uvw->alphabeta' */
  real32_T Sum2_m;                     /* '<S6>/Sum2' */
  real32_T TrigonometricFunction1_k;   /* '<S35>/Trigonometric Function1' */
  real32_T TrafoProd_n;                /* '<S35>/TrafoProd' */
  real32_T TrigonometricFunction_k;    /* '<S35>/Trigonometric Function' */
  real32_T TrafoProd3_o;               /* '<S35>/TrafoProd3' */
  real32_T TrafoSum_n;                 /* '<S35>/TrafoSum' */
  real32_T TrafoProd1_e;               /* '<S35>/TrafoProd1' */
  real32_T TrafoProd2_h;               /* '<S35>/TrafoProd2' */
  real32_T TrafoSum1_p;                /* '<S35>/TrafoSum1' */
  real32_T TmpSignalConversionAtDiscrete_c[2];
  real32_T IdqErr_e[2];                /* '<S32>/IdqErr' */
  real32_T KPek1_h[2];                 /* '<S45>/KP*e[k]1' */
  real32_T IntegDelay1_d[2];           /* '<S45>/IntegDelay1' */
  real32_T Product1_b;                 /* '<S45>/Product1' */
  real32_T IntegEnaSwitch1_h[2];       /* '<S45>/IntegEnaSwitch1' */
  real32_T Product_c;                  /* '<S5>/Product' */
  real32_T Sum_k;                      /* '<S5>/Sum' */
  real32_T Switch1_k;                  /* '<S29>/Switch1' */
  real32_T Switch2;                    /* '<S29>/Switch2' */
  real32_T Sum2_p;                     /* '<S5>/Sum2' */
  real32_T Sum1_l;                     /* '<S5>/Sum1' */
  real32_T SelectControlMode[9];       /* '<S1>/SelectControlMode' */
  real32_T TrigonometricFunction_n;    /* '<S101>/Trigonometric Function' */
  real32_T Gain1_n[4];                 /* '<S101>/Gain1' */
  real32_T TrigonometricFunction1_j;   /* '<S101>/Trigonometric Function1' */
  real32_T Gain_l[4];                  /* '<S101>/Gain' */
  real32_T Sum1_g[4];                  /* '<S101>/Sum1' */
  real32_T Product_c0[2];              /* '<S101>/Product' */
  real32_T U_uvw1[3];                  /* '<S98>/Product' */
  real32_T TrigonometricFunction_j;    /* '<S102>/Trigonometric Function' */
  real32_T Gain1_i[4];                 /* '<S102>/Gain1' */
  real32_T TrigonometricFunction1_h;   /* '<S102>/Trigonometric Function1' */
  real32_T Gain_f[4];                  /* '<S102>/Gain' */
  real32_T Sum1_f[4];                  /* '<S102>/Sum1' */
  real32_T Product_f[2];               /* '<S102>/Product' */
  real32_T Product_f3[3];              /* '<S99>/Product' */
  real32_T TrigonometricFunction_h;    /* '<S103>/Trigonometric Function' */
  real32_T Gain1_n4[4];                /* '<S103>/Gain1' */
  real32_T TrigonometricFunction1_hh;  /* '<S103>/Trigonometric Function1' */
  real32_T Gain_ld[4];                 /* '<S103>/Gain' */
  real32_T Sum1_lz[4];                 /* '<S103>/Sum1' */
  real32_T Product_i[2];               /* '<S103>/Product' */
  real32_T Product_fb[3];              /* '<S100>/Product' */
  real32_T SelMod_DutyCycles[9];       /* '<S15>/SelectModulation' */
  real32_T Scale02[9];                 /* '<S93>/Scale [0..2]' */
  real32_T Scale01[9];                 /* '<S93>/Scale  [0..1]' */
  real32_T Limit01[9];                 /* '<S93>/Limit [0..1]' */
  real32_T Select_GateDriver_Assignment_1[3];
                                    /* '<S96>/Select_GateDriver_Assignment_1' */
  real32_T Select_GateDriver_Assignment_2[3];
                                    /* '<S96>/Select_GateDriver_Assignment_2' */
  real32_T Select_GateDriver_Assignment_3[3];
                                    /* '<S96>/Select_GateDriver_Assignment_3' */
  real32_T DutyCycles_switch[9];       /* '<S3>/Manual_DutyCycles_switch' */
  real32_T Deviation;                  /* '<S24>/Deviation' */
  real32_T Product2;                   /* '<S24>/Product2' */
  real32_T Gain_g;                     /* '<S24>/Gain' */
  real32_T winkelimpuls;               /* '<S24>/Gain4' */
  real32_T Sum1_g4;                    /* '<S24>/Sum1' */
  real32_T Product_o;                  /* '<S24>/Product' */
  real32_T Product1_bi;                /* '<S24>/Product1' */
  real32_T UnitDelay1;                 /* '<S28>/Unit Delay1' */
  real32_T Sum2_mq;                    /* '<S24>/Sum2' */
  real32_T Sum6;                       /* '<S24>/Sum6' */
  real32_T Product_n;                  /* '<S27>/Product' */
  real32_T Sum2_e;                     /* '<S27>/Sum2' */
  real32_T Product_cd;                 /* '<S28>/Product' */
  real32_T Sum2_j;                     /* '<S28>/Sum2' */
  real32_T phi_el_U_trafo[3];          /* '<S5>/Gain1' */
  real32_T I_dq1_Act_filt[2];       /* '<S33>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder[2];
                                    /* '<S34>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_l[2];
                                    /* '<S35>/Discrete FIR Filter 20th order' */
  real32_T I_dq_Act[6];                /* '<S1>/Current_Controller' */
  real32_T usrpm;                      /* '<S12>/[1//s] => [rpm]' */
  real32_T Abs_d;                      /* '<S12>/Abs' */
  real32_T DataSourceSwitch;           /* '<S8>/DataSourceSwitch' */
  real32_T EN_FLT_Switch_1;            /* '<S48>/EN_FLT_Switch_1' */
  real32_T EN_FLT_Switch_2;            /* '<S48>/EN_FLT_Switch_2' */
  real32_T EN_FLT_Switch_3;            /* '<S48>/EN_FLT_Switch_3' */
  real32_T EN_RDY_Switch_1;            /* '<S48>/EN_RDY_Switch_1' */
  real32_T EN_RDY_Switch_2;            /* '<S48>/EN_RDY_Switch_2' */
  real32_T EN_RDY_Switch_3;            /* '<S48>/EN_RDY_Switch_3' */
  real32_T IntegStopSwitch2[2];        /* '<S37>/IntegStopSwitch2' */
  real32_T U_d1_CC;                    /* '<S30>/Gain1' */
  real32_T U_q1_CC;                    /* '<S30>/Gain2' */
  real32_T IntegStopSwitch2_o[2];      /* '<S41>/IntegStopSwitch2' */
  real32_T IntegStopSwitch2_h[2];      /* '<S45>/IntegStopSwitch2' */
  real32_T Abs_e;                      /* '<S61>/Abs' */
  real32_T Switch_d;                   /* '<S61>/Switch' */
  real32_T Add1;                       /* '<S61>/Add1' */
  real32_T Abs_b;                      /* '<S13>/Abs' */
  real32_T Switch_l;                   /* '<S13>/Switch' */
  real32_T Add1_j;                     /* '<S13>/Add1' */
  real32_T Abs_f;                      /* '<S91>/Abs' */
  real32_T Switch_n;                   /* '<S91>/Switch' */
  real32_T Add1_c;                     /* '<S91>/Add1' */
  real32_T U_d1;                       /* '<S15>/Gain' */
  real32_T U_q1;                       /* '<S15>/Gain1' */
  real32_T U_alpha1;                   /* '<S15>/Gain2' */
  real32_T U_beta1;                    /* '<S15>/Gain3' */
  real32_T DutyCycle_u1;               /* '<S96>/DutyCycle_u1' */
  real32_T DutyCycle_u2;               /* '<S96>/DutyCycle_u2' */
  real32_T DutyCycle_u3;               /* '<S96>/DutyCycle_u3' */
  real32_T DutyCycle_v1;               /* '<S96>/DutyCycle_v1' */
  real32_T DutyCycle_v2;               /* '<S96>/DutyCycle_v2' */
  real32_T DutyCycle_v3;               /* '<S96>/DutyCycle_v3' */
  real32_T DutyCycle_w1;               /* '<S96>/DutyCycle_w1' */
  real32_T DutyCycle_w2;               /* '<S96>/DutyCycle_w2' */
  real32_T DutyCycle_w3;               /* '<S96>/DutyCycle_w3' */
  real32_T FCF_Cnt;                    /* '<S1>/FCF_Cnt' */
  real32_T Sum_o;                      /* '<S1>/Sum' */
  real32_T MinMax2;                    /* '<S97>/MinMax2' */
  real32_T MinMax3;                    /* '<S97>/MinMax3' */
  real32_T Sum1_o;                     /* '<S97>/Sum1' */
  real32_T Factor;                     /* '<S97>/Factor' */
  real32_T DutyCycle_SuperSinus_1[3];  /* '<S97>/DutyCycle_SuperSinus_1' */
  real32_T MinMax1;                    /* '<S97>/MinMax1' */
  real32_T MinMax4;                    /* '<S97>/MinMax4' */
  real32_T Sum2_i;                     /* '<S97>/Sum2' */
  real32_T Factor1;                    /* '<S97>/Factor1' */
  real32_T DutyCycle_SuperSinus_2[3];  /* '<S97>/DutyCycle_SuperSinus_2' */
  real32_T MinMax5;                    /* '<S97>/MinMax5' */
  real32_T MinMax6;                    /* '<S97>/MinMax6' */
  real32_T Sum3_k;                     /* '<S97>/Sum3' */
  real32_T Factor2;                    /* '<S97>/Factor2' */
  real32_T DutyCycle_SuperSinus_3[3];  /* '<S97>/DutyCycle_SuperSinus_3' */
  real32_T U_DC2;                      /* '<S95>/U_DC//2' */
  real32_T AvoidDivBy0;                /* '<S95>/AvoidDivBy0' */
  real32_T DutyCycle_normed[9];        /* '<S95>/DutyCycle_normalized' */
  real32_T U_DC2_l;                    /* '<S94>/U_DC//2' */
  real32_T AvoidDivBy0_f;              /* '<S94>/AvoidDivBy0' */
  real32_T Square[2];                  /* '<S94>/Square' */
  real32_T Sum_kr;                     /* '<S94>/Sum' */
  real32_T Sqrt;                       /* '<S94>/Sqrt' */
  real32_T Square1[2];                 /* '<S94>/Square1' */
  real32_T Sum1_a;                     /* '<S94>/Sum1' */
  real32_T Sqrt1;                      /* '<S94>/Sqrt1' */
  real32_T Square2[2];                 /* '<S94>/Square2' */
  real32_T Sum2_iq;                    /* '<S94>/Sum2' */
  real32_T Sqrt2;                      /* '<S94>/Sqrt2' */
  real32_T ModInd[3];                  /* '<S94>/Divide3' */
  real32_T Sign;                       /* '<S91>/Sign' */
  real32_T Gain1_o;                    /* '<S91>/Gain1' */
  real32_T Use_If_Starter;             /* '<S1>/Use_If_Starter' */
  real32_T Selectphicalc2;             /* '<S4>/Selectphicalc2' */
  real32_T Switch1_d;                  /* '<S25>/Switch1' */
  real32_T Switch2_f;                  /* '<S25>/Switch2' */
  real32_T Sum3_h;                     /* '<S25>/Sum3' */
  real32_T Sum2_l;                     /* '<S25>/Sum2' */
  real32_T Gain_fw;                    /* '<S92>/Gain' */
  real32_T Sign_p;                     /* '<S92>/Sign' */
  real32_T Abs_d3;                     /* '<S92>/Abs' */
  real32_T Saturation1;                /* '<S92>/Saturation1' */
  real32_T Product_j;                  /* '<S92>/Product' */
  real32_T Sum1_n;                     /* '<S14>/Sum1' */
  real32_T Sum2_d;                     /* '<S14>/Sum2' */
  real32_T Sign_n;                     /* '<S13>/Sign' */
  real32_T Gain1_h;                    /* '<S13>/Gain1' */
  real32_T Sign_d;                     /* '<S61>/Sign' */
  real32_T Gain1_j;                    /* '<S61>/Gain1' */
  real32_T IntegStopSwitch3[2];        /* '<S45>/IntegStopSwitch3' */
  real32_T IntSum2[2];                 /* '<S45>/IntSum2' */
  real32_T FOC_IntegDamp[2];           /* '<S45>/FOC_IntegDamp' */
  real32_T antiWindupProd[2];          /* '<S44>/antiWindupProd' */
  real32_T IntegStopSwitch1[2];        /* '<S45>/IntegStopSwitch1' */
  real32_T Product2_e[2];              /* '<S45>/Product2' */
  real32_T IntSum1[2];                 /* '<S45>/IntSum1' */
  real32_T IntegStopSwitch3_n[2];      /* '<S41>/IntegStopSwitch3' */
  real32_T IntSum2_f[2];               /* '<S41>/IntSum2' */
  real32_T FOC_IntegDamp_g[2];         /* '<S41>/FOC_IntegDamp' */
  real32_T antiWindupProd_d[2];        /* '<S40>/antiWindupProd' */
  real32_T IntegStopSwitch1_g[2];      /* '<S41>/IntegStopSwitch1' */
  real32_T Product2_b[2];              /* '<S41>/Product2' */
  real32_T IntSum1_l[2];               /* '<S41>/IntSum1' */
  real32_T IntegStopSwitch3_h[2];      /* '<S37>/IntegStopSwitch3' */
  real32_T IntSum2_j[2];               /* '<S37>/IntSum2' */
  real32_T FOC_IntegDamp_c[2];         /* '<S37>/FOC_IntegDamp' */
  real32_T antiWindupProd_o[2];        /* '<S36>/antiWindupProd' */
  real32_T IntegStopSwitch1_f[2];      /* '<S37>/IntegStopSwitch1' */
  real32_T Product2_j[2];              /* '<S37>/Product2' */
  real32_T IntSum1_p[2];               /* '<S37>/IntSum1' */
  real32_T Sum3_d;                     /* '<S29>/Sum3' */
  real32_T Sum2_ez;                    /* '<S29>/Sum2' */
  real32_T ASCSwitch[9];               /* '<S3>/ASC Switch' */
  real32_T bias_udc;                   /* '<S17>/bias_udc' */
  real32_T gain_udc;                   /* '<S17>/gain_udc' */
  real32_T UnitDelay1_p[9];            /* '<S23>/Unit Delay1' */
  real32_T Gain_a[9];                  /* '<S22>/Gain' */
  real32_T Add_p[9];                   /* '<S22>/Add' */
  real32_T VermeidungDivisionDurchNull;/* '<S22>/VermeidungDivisionDurchNull' */
  real32_T Divide[9];                  /* '<S22>/Divide' */
  real32_T Product_cdf[9];             /* '<S23>/Product' */
  real32_T Sum2_k[9];                  /* '<S23>/Sum2' */
  uint8_T Compare;                     /* '<S47>/Compare' */
  uint8_T Compare_k;                   /* '<S46>/Compare' */
  uint8_T Compare_g;                   /* '<S43>/Compare' */
  uint8_T Compare_i;                   /* '<S42>/Compare' */
  uint8_T Compare_o;                   /* '<S39>/Compare' */
  uint8_T Compare_f;                   /* '<S38>/Compare' */
  boolean_T Compare_e;                 /* '<S79>/Compare' */
  boolean_T LogicalOperator2;          /* '<S63>/Logical Operator2' */
  boolean_T LogicalOperator4;          /* '<S63>/Logical Operator4' */
  boolean_T Compare_d;                 /* '<S86>/Compare' */
  boolean_T Uk1;                       /* '<S82>/Delay Input1' */
  boolean_T Selectphicalc3;            /* '<S63>/Selectphicalc3' */
  boolean_T Memory;                    /* '<S83>/Memory' */
  boolean_T Logic[2];                  /* '<S83>/Logic' */
  boolean_T Compare_n;                 /* '<S80>/Compare' */
  boolean_T LogicalOperator3;          /* '<S63>/Logical Operator3' */
  boolean_T Compare_iz;                /* '<S85>/Compare' */
  boolean_T Uk1_m;                     /* '<S81>/Delay Input1' */
  boolean_T Selectphicalc4;            /* '<S63>/Selectphicalc4' */
  boolean_T Memory_o;                  /* '<S84>/Memory' */
  boolean_T Logic_c[2];                /* '<S84>/Logic' */
  boolean_T Compare_j;                 /* '<S64>/Compare' */
  boolean_T LogicalOperator3_i;        /* '<S62>/Logical Operator3' */
  boolean_T Compare_in;                /* '<S69>/Compare' */
  boolean_T Uk1_g;                     /* '<S66>/Delay Input1' */
  boolean_T Selectphicalc2_m;          /* '<S62>/Selectphicalc2' */
  boolean_T Memory_n;                  /* '<S68>/Memory' */
  boolean_T Logic_a[2];                /* '<S68>/Logic' */
  boolean_T I_ph_Overcurrent_Error;    /* '<S62>/Selectphicalc1' */
  boolean_T OC_OV_UV_ERROR;            /* '<S11>/Logical Operator' */
  boolean_T LogicalOperator2_a;        /* '<S1>/Logical Operator2' */
  boolean_T LogicalOperator1;          /* '<S1>/Logical Operator1' */
  boolean_T LogicalOperator;           /* '<S1>/Logical Operator' */
  boolean_T Compare_l;                 /* '<S7>/Compare' */
  boolean_T Sprung;                    /* '<S26>/Sprung?' */
  boolean_T Sprung1;                   /* '<S26>/Sprung?1' */
  boolean_T LogicalOperator1_h;        /* '<S6>/Logical Operator1' */
  boolean_T LogicalOperator2_n;        /* '<S6>/Logical Operator2' */
  boolean_T LogicalOperator3_e;        /* '<S6>/Logical Operator3' */
  boolean_T Compare_c;                 /* '<S87>/Compare' */
  boolean_T LogicalOperator3_p;        /* '<S12>/Logical Operator3' */
  boolean_T Compare_gt;                /* '<S90>/Compare' */
  boolean_T Uk1_h;                     /* '<S88>/Delay Input1' */
  boolean_T Selectphicalc2_d;          /* '<S12>/Selectphicalc2' */
  boolean_T Memory_k;                  /* '<S89>/Memory' */
  boolean_T Logic_e[2];                /* '<S89>/Logic' */
  boolean_T Overspeed_Error;           /* '<S12>/Selectphicalc1' */
  boolean_T Compare_lv;                /* '<S55>/Compare' */
  boolean_T Compare_fp;                /* '<S56>/Compare' */
  boolean_T Compare_g1;                /* '<S57>/Compare' */
  boolean_T Compare_e0;                /* '<S58>/Compare' */
  boolean_T Compare_nd;                /* '<S59>/Compare' */
  boolean_T Compare_cf;                /* '<S60>/Compare' */
  boolean_T LogicalOperator3_c;        /* '<S48>/Logical Operator3' */
  boolean_T LogicalOperator3_pp;       /* '<S8>/Logical Operator3' */
  boolean_T FOC_Enable_PWM;            /* '<S8>/Enable_PWM_' */
  boolean_T FCF_Error;                 /* '<S8>/Logical Operator6' */
  boolean_T Compare_gv[9];             /* '<S65>/Compare' */
  boolean_T Memory_f;                  /* '<S70>/Memory' */
  boolean_T Logic_g[2];                /* '<S70>/Logic' */
  boolean_T Memory_b;                  /* '<S71>/Memory' */
  boolean_T Logic_i[2];                /* '<S71>/Logic' */
  boolean_T Memory_ok;                 /* '<S72>/Memory' */
  boolean_T Logic_b[2];                /* '<S72>/Logic' */
  boolean_T Memory_c;                  /* '<S73>/Memory' */
  boolean_T Logic_p[2];                /* '<S73>/Logic' */
  boolean_T Memory_g;                  /* '<S74>/Memory' */
  boolean_T Logic_d[2];                /* '<S74>/Logic' */
  boolean_T Memory_j;                  /* '<S75>/Memory' */
  boolean_T Logic_ev[2];               /* '<S75>/Logic' */
  boolean_T Memory_nb;                 /* '<S76>/Memory' */
  boolean_T Logic_bw[2];               /* '<S76>/Logic' */
  boolean_T Memory_kp;                 /* '<S77>/Memory' */
  boolean_T Logic_ag[2];               /* '<S77>/Logic' */
  boolean_T Memory_p;                  /* '<S78>/Memory' */
  boolean_T Logic_f[2];                /* '<S78>/Logic' */
  boolean_T FixPtRelationalOperator;   /* '<S88>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_m; /* '<S81>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_j; /* '<S82>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_h; /* '<S66>/FixPt Relational Operator' */
  boolean_T AntiWindupLE;              /* '<S44>/AntiWindupLE' */
  boolean_T AntiWindupOR_q;            /* '<S44>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d;            /* '<S44>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_f;            /* '<S40>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_l;          /* '<S40>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_m;          /* '<S40>/AntiWindupOR_d' */
  boolean_T AntiWindupLE_l;            /* '<S36>/AntiWindupLE' */
  boolean_T AntiWindupOR_q_o;          /* '<S36>/AntiWindupOR_q' */
  boolean_T AntiWindupOR_d_e;          /* '<S36>/AntiWindupOR_d' */
} B_FOC_FCF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTransferFcn_states; /* '<S14>/Discrete Transfer Fcn' */
  real32_T UnitDelay_DSTATE;           /* '<S91>/Unit Delay' */
  real32_T UnitDelay1_DSTATE;          /* '<S27>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_h;         /* '<S26>/Unit Delay' */
  real32_T UnitDelay3_DSTATE;          /* '<S24>/Unit Delay3' */
  real32_T UnitDelay_DSTATE_p;         /* '<S13>/Unit Delay' */
  real32_T UnitDelay_DSTATE_f;         /* '<S61>/Unit Delay' */
  real32_T IntegDelay1_DSTATE[2];      /* '<S37>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_p[2];    /* '<S41>/IntegDelay1' */
  real32_T IntegDelay1_DSTATE_h[2];    /* '<S45>/IntegDelay1' */
  real32_T UnitDelay1_DSTATE_i;        /* '<S28>/Unit Delay1' */
  real32_T DiscreteFIRFilter20thorder_stat[38];
                                    /* '<S33>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_g[38];
                                    /* '<S34>/Discrete FIR Filter 20th order' */
  real32_T DiscreteFIRFilter20thorder_st_p[38];
                                    /* '<S35>/Discrete FIR Filter 20th order' */
  real32_T FCF_Cnt_DSTATE;             /* '<S1>/FCF_Cnt' */
  real32_T UnitDelay1_DSTATE_c[9];     /* '<S23>/Unit Delay1' */
  int32_T DiscreteFIRFilter20thorder_circ;
                                    /* '<S33>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_m;
                                    /* '<S34>/Discrete FIR Filter 20th order' */
  int32_T DiscreteFIRFilter20thorder_ci_c;
                                    /* '<S35>/Discrete FIR Filter 20th order' */
  boolean_T DelayInput1_DSTATE;        /* '<S82>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_g;      /* '<S81>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_l;      /* '<S66>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_e;      /* '<S88>/Delay Input1' */
  boolean_T Memory_PreviousInput;      /* '<S83>/Memory' */
  boolean_T Memory_PreviousInput_e;    /* '<S84>/Memory' */
  boolean_T Memory_PreviousInput_j;    /* '<S68>/Memory' */
  boolean_T Memory_PreviousInput_i;    /* '<S89>/Memory' */
  boolean_T Memory_PreviousInput_n;    /* '<S70>/Memory' */
  boolean_T Memory_PreviousInput_o;    /* '<S71>/Memory' */
  boolean_T Memory_PreviousInput_nm;   /* '<S72>/Memory' */
  boolean_T Memory_PreviousInput_ef;   /* '<S73>/Memory' */
  boolean_T Memory_PreviousInput_c;    /* '<S74>/Memory' */
  boolean_T Memory_PreviousInput_d;    /* '<S75>/Memory' */
  boolean_T Memory_PreviousInput_os;   /* '<S76>/Memory' */
  boolean_T Memory_PreviousInput_f;    /* '<S77>/Memory' */
  boolean_T Memory_PreviousInput_b;    /* '<S78>/Memory' */
} DW_FOC_FCF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  bus_BSW_FCF_t bus_BSW_FCF;           /* '<Root>/bus_BSW_FCF' */
  bus_SCF_t bus_SCF;                   /* '<Root>/bus_SCF' */
  bus_SMF_t bus_SMF;                   /* '<Root>/bus_SMF' */
} ExtU_FOC_FCF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  bus_FCF_t bus_FCF;                   /* '<Root>/bus_FCF' */
} ExtY_FOC_FCF_T;

/* Parameters (default storage) */
struct P_FOC_FCF_T_ {
  real32_T ENABLE_GateDriver_FLT_Error_Sys1;
                                   /* Variable: ENABLE_GateDriver_FLT_Error_Sys1
                                    * Referenced by: '<S48>/ENABLE_GateDriver_FLT_Error_Sys1'
                                    */
  real32_T ENABLE_GateDriver_FLT_Error_Sys2;
                                   /* Variable: ENABLE_GateDriver_FLT_Error_Sys2
                                    * Referenced by: '<S48>/ENABLE_GateDriver_FLT_Error_Sys2'
                                    */
  real32_T ENABLE_GateDriver_FLT_Error_Sys3;
                                   /* Variable: ENABLE_GateDriver_FLT_Error_Sys3
                                    * Referenced by: '<S48>/ENABLE_GateDriver_FLT_Error_Sys3'
                                    */
  real32_T ENABLE_GateDriver_RDY_Error_Sys1;
                                   /* Variable: ENABLE_GateDriver_RDY_Error_Sys1
                                    * Referenced by: '<S48>/ENABLE_GateDriver_RDY_Error_Sys1'
                                    */
  real32_T ENABLE_GateDriver_RDY_Error_Sys2;
                                   /* Variable: ENABLE_GateDriver_RDY_Error_Sys2
                                    * Referenced by: '<S48>/ENABLE_GateDriver_RDY_Error_Sys2'
                                    */
  real32_T ENABLE_GateDriver_RDY_Error_Sys3;
                                   /* Variable: ENABLE_GateDriver_RDY_Error_Sys3
                                    * Referenced by: '<S48>/ENABLE_GateDriver_RDY_Error_Sys3'
                                    */
  real32_T FOC_9ph_AngleShift;         /* Variable: FOC_9ph_AngleShift
                                        * Referenced by:
                                        *   '<S5>/FOC_9ph_AngleShift'
                                        *   '<S6>/FOC_9ph_AngleShift'
                                        *   '<S14>/FOC_9ph_AngleShift'
                                        */
  real32_T FOC_ASC_Mode;               /* Variable: FOC_ASC_Mode
                                        * Referenced by: '<S3>/FOC_AKS_Mode'
                                        */
  real32_T FOC_AngleObs_w_InitVal;     /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by:
                                        *   '<S27>/Unit Delay1'
                                        *   '<S23>/Unit Delay1'
                                        */
  real32_T FOC_AngleObserver_D;        /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S24>/Constant1'
                                        */
  real32_T FOC_AngleObserver_w0;       /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S24>/Constant'
                                        */
  real32_T FOC_Calibrate_I_ph;         /* Variable: FOC_Calibrate_I_ph
                                        * Referenced by: '<S20>/calibrateSensors'
                                        */
  real32_T FOC_ENABLE_Overcurrent_I_uvw;/* Variable: FOC_ENABLE_Overcurrent_I_uvw
                                         * Referenced by: '<S62>/FOC_ENABLE_Overcurrent_I_uvw1'
                                         */
  real32_T FOC_ENABLE_Overspeed;       /* Variable: FOC_ENABLE_Overspeed
                                        * Referenced by: '<S12>/FOC_ENABLE_Overcurrent_I_uvw1'
                                        */
  real32_T FOC_ENABLE_Overvoltage_U_DC;/* Variable: FOC_ENABLE_Overvoltage_U_DC
                                        * Referenced by: '<S63>/FOC_ENABLE_Overvoltage_U_DC1'
                                        */
  real32_T FOC_ENABLE_Undervoltage_U_DC;/* Variable: FOC_ENABLE_Undervoltage_U_DC
                                         * Referenced by: '<S63>/FOC_ENABLE_Undervoltage_U_DC1'
                                         */
  real32_T FOC_Enable;                 /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
  real32_T FOC_Enable_Sys1;            /* Variable: FOC_Enable_Sys1
                                        * Referenced by: '<S6>/FOC_Enable_Sys1'
                                        */
  real32_T FOC_Enable_Sys2;            /* Variable: FOC_Enable_Sys2
                                        * Referenced by: '<S6>/FOC_Enable_Sys2'
                                        */
  real32_T FOC_Enable_Sys3;            /* Variable: FOC_Enable_Sys3
                                        * Referenced by: '<S6>/FOC_Enable_Sys3'
                                        */
  real32_T FOC_If_f_el;                /* Variable: FOC_If_f_el
                                        * Referenced by: '<S10>/If_f_el'
                                        */
  real32_T FOC_IntegDamp;              /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S37>/FOC_IntegDamp'
                                        *   '<S41>/FOC_IntegDamp'
                                        *   '<S45>/FOC_IntegDamp'
                                        */
  real32_T FOC_KI;                     /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S37>/FOC_KI'
                                        *   '<S41>/FOC_KI'
                                        *   '<S45>/FOC_KI'
                                        */
  real32_T FOC_KP;                     /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S37>/FOC_KP1'
                                        *   '<S41>/FOC_KP1'
                                        *   '<S45>/FOC_KP1'
                                        */
  real32_T FOC_LIMIT_Overcurrent_I_uvw;/* Variable: FOC_LIMIT_Overcurrent_I_uvw
                                        * Referenced by:
                                        *   '<S64>/Constant'
                                        *   '<S65>/Constant'
                                        */
  real32_T FOC_LIMIT_Overvoltage_U_DC; /* Variable: FOC_LIMIT_Overvoltage_U_DC
                                        * Referenced by: '<S80>/Constant'
                                        */
  real32_T FOC_LIMIT_Undervoltage_U_DC;/* Variable: FOC_LIMIT_Undervoltage_U_DC
                                        * Referenced by: '<S79>/Constant'
                                        */
  real32_T FOC_MANUAL_Error;           /* Variable: FOC_MANUAL_Error
                                        * Referenced by: '<S1>/FOC_MANUAL_Error'
                                        */
  real32_T FOC_MANUAL_U_DC;            /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S17>/Udc1'
                                        */
  real32_T FOC_MaxModInd;              /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S36>/FOC_MaxModInd'
                                        *   '<S40>/FOC_MaxModInd'
                                        *   '<S44>/FOC_MaxModInd'
                                        */
  real32_T FOC_Mode_Intern;            /* Variable: FOC_Mode_Intern
                                        * Referenced by: '<S1>/FOC_Mode_Intern'
                                        */
  real32_T FOC_OmegaObs3;              /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S24>/Gain4'
                                        */
  real32_T FOC_PhiSensorTdead;         /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S24>/DeadTimeCompensation'
                                        */
  real32_T FOC_RESET_OC_Error;         /* Variable: FOC_RESET_OC_Error
                                        * Referenced by: '<S62>/Reset_OC_Error'
                                        */
  real32_T FOC_RESET_OS_Error;         /* Variable: FOC_RESET_OS_Error
                                        * Referenced by: '<S12>/Reset_OS_Error'
                                        */
  real32_T FOC_RESET_OV_Error;         /* Variable: FOC_RESET_OV_Error
                                        * Referenced by: '<S63>/Reset_OV_Error'
                                        */
  real32_T FOC_RESET_UV_Error;         /* Variable: FOC_RESET_UV_Error
                                        * Referenced by: '<S63>/Reset_UV_Error'
                                        */
  real32_T FOC_SELECT_Phase_Assignment_UVW;
                                    /* Variable: FOC_SELECT_Phase_Assignment_UVW
                                     * Referenced by: '<S19>/Selektierung Phase'
                                     */
  real32_T FOC_SELECT_Voltage_Assignment_UVW;
                                  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
                                   * Referenced by: '<S96>/Constant6'
                                   */
  real32_T FOC_Uf_U_max;               /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S92>/Saturation1'
                                        */
  real32_T FOC_Uf_U_min;               /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S92>/Saturation1'
                                        */
  real32_T FOC_Uf_Ud;                  /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S14>/Uf_Ud'
                                        */
  real32_T FOC_Uf_f_el;                /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S14>/Uf_w_el'
                                        */
  real32_T FOC_Uf_m;                   /* Variable: FOC_Uf_m
                                        * Referenced by: '<S92>/Gain'
                                        */
  real32_T FOC_output_trafo_delay;     /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S5>/FOC_output_trafo_delay'
                                        */
  real32_T FOC_phi_offset;             /* Variable: FOC_phi_offset
                                        * Referenced by: '<S4>/Constant'
                                        */
  real32_T LIMIT_MAX_Overspeed;        /* Variable: LIMIT_MAX_Overspeed
                                        * Referenced by: '<S87>/Constant'
                                        */
  real32_T enumState_FOC_IF;           /* Variable: enumState_FOC_IF
                                        * Referenced by: '<S7>/Constant'
                                        */
  real32_T gain_current1;              /* Variable: gain_current1
                                        * Referenced by: '<S20>/Gain'
                                        */
  real32_T gain_current2;              /* Variable: gain_current2
                                        * Referenced by: '<S20>/Gain1'
                                        */
  real32_T gain_current3;              /* Variable: gain_current3
                                        * Referenced by: '<S20>/Gain2'
                                        */
  real32_T gain_current4;              /* Variable: gain_current4
                                        * Referenced by: '<S20>/Gain3'
                                        */
  real32_T gain_current5;              /* Variable: gain_current5
                                        * Referenced by: '<S20>/Gain4'
                                        */
  real32_T gain_current6;              /* Variable: gain_current6
                                        * Referenced by: '<S20>/Gain5'
                                        */
  real32_T gain_current7;              /* Variable: gain_current7
                                        * Referenced by: '<S20>/Gain6'
                                        */
  real32_T gain_current8;              /* Variable: gain_current8
                                        * Referenced by: '<S20>/Gain7'
                                        */
  real32_T gain_current9;              /* Variable: gain_current9
                                        * Referenced by: '<S20>/Gain8'
                                        */
  uint8_T FOC_SELECT_MANUAL_DutyCycles;/* Variable: FOC_SELECT_MANUAL_DutyCycles
                                        * Referenced by: '<S3>/FOC_SELECT_MANUAL_DutyCycles'
                                        */
  uint8_T FOC_SELECT_Mode_Intern;      /* Variable: FOC_SELECT_Mode_Intern
                                        * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
                                        */
  uint8_T FOC_SELECT_Modulation;       /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S15>/Enable_SuperSinMod'
                                        */
  uint8_T FOC_SELECT_U_DC_INPUT;       /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S17>/0: P_Udc 1: Udc_measured'
                                        */
  uint8_T FOC_SELECT_phi;              /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S4>/Constant3'
                                        */
  real32_T AntiWindupGT_d_const;       /* Mask Parameter: AntiWindupGT_d_const
                                        * Referenced by: '<S38>/Constant'
                                        */
  real32_T AntiWindupGT_q_const;       /* Mask Parameter: AntiWindupGT_q_const
                                        * Referenced by: '<S39>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_n;     /* Mask Parameter: AntiWindupGT_d_const_n
                                        * Referenced by: '<S42>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_h;     /* Mask Parameter: AntiWindupGT_q_const_h
                                        * Referenced by: '<S43>/Constant'
                                        */
  real32_T AntiWindupGT_d_const_f;     /* Mask Parameter: AntiWindupGT_d_const_f
                                        * Referenced by: '<S46>/Constant'
                                        */
  real32_T AntiWindupGT_q_const_l;     /* Mask Parameter: AntiWindupGT_q_const_l
                                        * Referenced by: '<S47>/Constant'
                                        */
  uint32_T Mask_6Bits_Inv1_FLT_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv1_FLT_BitMask
                                   * Referenced by: '<S9>/Mask_6Bits_Inv1_FLT'
                                   */
  uint32_T MaskBit0_BitMask;           /* Mask Parameter: MaskBit0_BitMask
                                        * Referenced by: '<S49>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask;           /* Mask Parameter: MaskBit1_BitMask
                                        * Referenced by: '<S49>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask;           /* Mask Parameter: MaskBit2_BitMask
                                        * Referenced by: '<S49>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask;           /* Mask Parameter: MaskBit3_BitMask
                                        * Referenced by: '<S49>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask;           /* Mask Parameter: MaskBit4_BitMask
                                        * Referenced by: '<S49>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask;           /* Mask Parameter: MaskBit5_BitMask
                                        * Referenced by: '<S49>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv1_RDY_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv1_RDY_BitMask
                                   * Referenced by: '<S9>/Mask_6Bits_Inv1_RDY'
                                   */
  uint32_T MaskBit0_BitMask_b;         /* Mask Parameter: MaskBit0_BitMask_b
                                        * Referenced by: '<S50>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_j;         /* Mask Parameter: MaskBit1_BitMask_j
                                        * Referenced by: '<S50>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_m;         /* Mask Parameter: MaskBit2_BitMask_m
                                        * Referenced by: '<S50>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_i;         /* Mask Parameter: MaskBit3_BitMask_i
                                        * Referenced by: '<S50>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_d;         /* Mask Parameter: MaskBit4_BitMask_d
                                        * Referenced by: '<S50>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_a;         /* Mask Parameter: MaskBit5_BitMask_a
                                        * Referenced by: '<S50>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv2_FLT_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv2_FLT_BitMask
                                   * Referenced by: '<S9>/Mask_6Bits_Inv2_FLT'
                                   */
  uint32_T MaskBit0_BitMask_g;         /* Mask Parameter: MaskBit0_BitMask_g
                                        * Referenced by: '<S51>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_n;         /* Mask Parameter: MaskBit1_BitMask_n
                                        * Referenced by: '<S51>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_n;         /* Mask Parameter: MaskBit2_BitMask_n
                                        * Referenced by: '<S51>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_c;         /* Mask Parameter: MaskBit3_BitMask_c
                                        * Referenced by: '<S51>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_o;         /* Mask Parameter: MaskBit4_BitMask_o
                                        * Referenced by: '<S51>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_h;         /* Mask Parameter: MaskBit5_BitMask_h
                                        * Referenced by: '<S51>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv2_RDY_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv2_RDY_BitMask
                                   * Referenced by: '<S9>/Mask_6Bits_Inv2_RDY'
                                   */
  uint32_T MaskBit0_BitMask_bn;        /* Mask Parameter: MaskBit0_BitMask_bn
                                        * Referenced by: '<S52>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_a;         /* Mask Parameter: MaskBit1_BitMask_a
                                        * Referenced by: '<S52>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_o;         /* Mask Parameter: MaskBit2_BitMask_o
                                        * Referenced by: '<S52>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_h;         /* Mask Parameter: MaskBit3_BitMask_h
                                        * Referenced by: '<S52>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_e;         /* Mask Parameter: MaskBit4_BitMask_e
                                        * Referenced by: '<S52>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_l;         /* Mask Parameter: MaskBit5_BitMask_l
                                        * Referenced by: '<S52>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv3_FLT_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv3_FLT_BitMask
                                   * Referenced by: '<S9>/Mask_6Bits_Inv3_FLT'
                                   */
  uint32_T MaskBit0_BitMask_m;         /* Mask Parameter: MaskBit0_BitMask_m
                                        * Referenced by: '<S53>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_d;         /* Mask Parameter: MaskBit1_BitMask_d
                                        * Referenced by: '<S53>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_b;         /* Mask Parameter: MaskBit2_BitMask_b
                                        * Referenced by: '<S53>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_l;         /* Mask Parameter: MaskBit3_BitMask_l
                                        * Referenced by: '<S53>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_b;         /* Mask Parameter: MaskBit4_BitMask_b
                                        * Referenced by: '<S53>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_e;         /* Mask Parameter: MaskBit5_BitMask_e
                                        * Referenced by: '<S53>/MaskBit5'
                                        */
  uint32_T Mask_6Bits_Inv3_RDY_BitMask;
                                  /* Mask Parameter: Mask_6Bits_Inv3_RDY_BitMask
                                   * Referenced by: '<S9>/Mask_6Bits_Inv3_RDY'
                                   */
  uint32_T MaskBit0_BitMask_l;         /* Mask Parameter: MaskBit0_BitMask_l
                                        * Referenced by: '<S54>/MaskBit0'
                                        */
  uint32_T MaskBit1_BitMask_dr;        /* Mask Parameter: MaskBit1_BitMask_dr
                                        * Referenced by: '<S54>/MaskBit1'
                                        */
  uint32_T MaskBit2_BitMask_bx;        /* Mask Parameter: MaskBit2_BitMask_bx
                                        * Referenced by: '<S54>/MaskBit2'
                                        */
  uint32_T MaskBit3_BitMask_it;        /* Mask Parameter: MaskBit3_BitMask_it
                                        * Referenced by: '<S54>/MaskBit3'
                                        */
  uint32_T MaskBit4_BitMask_a;         /* Mask Parameter: MaskBit4_BitMask_a
                                        * Referenced by: '<S54>/MaskBit4'
                                        */
  uint32_T MaskBit5_BitMask_b;         /* Mask Parameter: MaskBit5_BitMask_b
                                        * Referenced by: '<S54>/MaskBit5'
                                        */
  uint32_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S56>/Constant'
                                       */
  uint32_T CompareToConstant_const_n;
                                    /* Mask Parameter: CompareToConstant_const_n
                                     * Referenced by: '<S58>/Constant'
                                     */
  uint32_T CompareToConstant_const_h;
                                    /* Mask Parameter: CompareToConstant_const_h
                                     * Referenced by: '<S60>/Constant'
                                     */
  boolean_T SRFlipFlop_initial_condition;
                                 /* Mask Parameter: SRFlipFlop_initial_condition
                                  * Referenced by: '<S83>/Memory'
                                  */
  boolean_T SRFlipFlop1_initial_condition;
                                /* Mask Parameter: SRFlipFlop1_initial_condition
                                 * Referenced by: '<S84>/Memory'
                                 */
  boolean_T SRFlipFlop_initial_condition_d;
                               /* Mask Parameter: SRFlipFlop_initial_condition_d
                                * Referenced by: '<S68>/Memory'
                                */
  boolean_T SRFlipFlop_initial_condition_k;
                               /* Mask Parameter: SRFlipFlop_initial_condition_k
                                * Referenced by: '<S89>/Memory'
                                */
  boolean_T OverTemp_Latching_1_initial_con;
                              /* Mask Parameter: OverTemp_Latching_1_initial_con
                               * Referenced by: '<S70>/Memory'
                               */
  boolean_T OverTemp_Latching_2_initial_con;
                              /* Mask Parameter: OverTemp_Latching_2_initial_con
                               * Referenced by: '<S71>/Memory'
                               */
  boolean_T OverTemp_Latching_3_initial_con;
                              /* Mask Parameter: OverTemp_Latching_3_initial_con
                               * Referenced by: '<S72>/Memory'
                               */
  boolean_T OverTemp_Latching_4_initial_con;
                              /* Mask Parameter: OverTemp_Latching_4_initial_con
                               * Referenced by: '<S73>/Memory'
                               */
  boolean_T OverTemp_Latching_5_initial_con;
                              /* Mask Parameter: OverTemp_Latching_5_initial_con
                               * Referenced by: '<S74>/Memory'
                               */
  boolean_T OverTemp_Latching_6_initial_con;
                              /* Mask Parameter: OverTemp_Latching_6_initial_con
                               * Referenced by: '<S75>/Memory'
                               */
  boolean_T OverTemp_Latching_7_initial_con;
                              /* Mask Parameter: OverTemp_Latching_7_initial_con
                               * Referenced by: '<S76>/Memory'
                               */
  boolean_T OverTemp_Latching_8_initial_con;
                              /* Mask Parameter: OverTemp_Latching_8_initial_con
                               * Referenced by: '<S77>/Memory'
                               */
  boolean_T OverTemp_Latching_9_initial_con;
                              /* Mask Parameter: OverTemp_Latching_9_initial_con
                               * Referenced by: '<S78>/Memory'
                               */
  boolean_T DetectRisePositive1_vinit;
                                    /* Mask Parameter: DetectRisePositive1_vinit
                                     * Referenced by: '<S82>/Delay Input1'
                                     */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S81>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_g;
                                   /* Mask Parameter: DetectRisePositive_vinit_g
                                    * Referenced by: '<S66>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_f;
                                   /* Mask Parameter: DetectRisePositive_vinit_f
                                    * Referenced by: '<S88>/Delay Input1'
                                    */
  real32_T cal_out_Y0;                 /* Computed Parameter: cal_out_Y0
                                        * Referenced by: '<S21>/cal_out'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S22>/Gain'
                                        */
  real32_T FOC_T_fast_Value;           /* Computed Parameter: FOC_T_fast_Value
                                        * Referenced by: '<S23>/FOC_T_fast'
                                        */
  real32_T Tau_Value;                  /* Computed Parameter: Tau_Value
                                        * Referenced by: '<S22>/Tau'
                                        */
  real32_T VermeidungDivisionDurchNull_Upp;
                          /* Computed Parameter: VermeidungDivisionDurchNull_Upp
                           * Referenced by: '<S22>/VermeidungDivisionDurchNull'
                           */
  real32_T VermeidungDivisionDurchNull_Low;
                          /* Computed Parameter: VermeidungDivisionDurchNull_Low
                           * Referenced by: '<S22>/VermeidungDivisionDurchNull'
                           */
  real32_T bias_udc_Bias;              /* Expression: MM_U_DC.OFFSET
                                        * Referenced by: '<S17>/bias_udc'
                                        */
  real32_T gain_udc_Gain;              /* Expression: MM_U_DC.FACTOR
                                        * Referenced by: '<S17>/gain_udc'
                                        */
  real32_T ASC_LS_Value[9];            /* Computed Parameter: ASC_LS_Value
                                        * Referenced by: '<S3>/ASC_LS'
                                        */
  real32_T ASC_HS_Value[9];            /* Computed Parameter: ASC_HS_Value
                                        * Referenced by: '<S3>/ASC_HS'
                                        */
  real32_T ASC_LSHS_Value[9];          /* Computed Parameter: ASC_LSHS_Value
                                        * Referenced by: '<S3>/ASC_LSHS'
                                        */
  real32_T FOC_Manual_DutyCycles_Value[9];
                              /* Computed Parameter: FOC_Manual_DutyCycles_Value
                               * Referenced by: '<S3>/FOC_Manual_DutyCycles'
                               */
  real32_T Constant5_Value;            /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S26>/Constant5'
                                        */
  real32_T Constant6_Value;            /* Computed Parameter: Constant6_Value
                                        * Referenced by: '<S26>/Constant6'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S26>/Constant2'
                                        */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S26>/Constant4'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S29>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S29>/Constant1'
                                        */
  real32_T Zero_Value;                 /* Computed Parameter: Zero_Value
                                        * Referenced by: '<S37>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold;
                               /* Computed Parameter: IntegStopSwitch3_Threshold
                                * Referenced by: '<S37>/IntegStopSwitch3'
                                */
  real32_T Zero_Value_o;               /* Computed Parameter: Zero_Value_o
                                        * Referenced by: '<S41>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold_a;
                             /* Computed Parameter: IntegStopSwitch3_Threshold_a
                              * Referenced by: '<S41>/IntegStopSwitch3'
                              */
  real32_T Zero_Value_n;               /* Computed Parameter: Zero_Value_n
                                        * Referenced by: '<S45>/Zero'
                                        */
  real32_T IntegStopSwitch3_Threshold_ad;
                            /* Computed Parameter: IntegStopSwitch3_Threshold_ad
                             * Referenced by: '<S45>/IntegStopSwitch3'
                             */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S61>/Gain1'
                                        */
  real32_T Constant1_Value_c;          /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<S61>/Constant1'
                                        */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S63>/Constant3'
                                        */
  real32_T Constant1_Value_b;          /* Computed Parameter: Constant1_Value_b
                                        * Referenced by: '<S63>/Constant1'
                                        */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S13>/Gain1'
                                        */
  real32_T Constant1_Value_k;          /* Computed Parameter: Constant1_Value_k
                                        * Referenced by: '<S13>/Constant1'
                                        */
  real32_T Constant1_Value_bt;         /* Computed Parameter: Constant1_Value_bt
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S25>/Constant'
                                        */
  real32_T Constant1_Value_g;          /* Computed Parameter: Constant1_Value_g
                                        * Referenced by: '<S25>/Constant1'
                                        */
  real32_T Switch1_Threshold;          /* Computed Parameter: Switch1_Threshold
                                        * Referenced by: '<S25>/Switch1'
                                        */
  real32_T Switch2_Threshold;          /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S25>/Switch2'
                                        */
  real32_T SMF_IfStarter_Active_Value;
                               /* Computed Parameter: SMF_IfStarter_Active_Value
                                * Referenced by: '<S1>/SMF_IfStarter_Active'
                                */
  real32_T Gain1_Gain_a;               /* Computed Parameter: Gain1_Gain_a
                                        * Referenced by: '<S91>/Gain1'
                                        */
  real32_T Constant1_Value_e;          /* Computed Parameter: Constant1_Value_e
                                        * Referenced by: '<S91>/Constant1'
                                        */
  real32_T Constant2_Value_d;          /* Computed Parameter: Constant2_Value_d
                                        * Referenced by: '<S94>/Constant2'
                                        */
  real32_T U_DC2_Gain;                 /* Computed Parameter: U_DC2_Gain
                                        * Referenced by: '<S94>/U_DC//2'
                                        */
  real32_T Constant2_Value_g;          /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S95>/Constant2'
                                        */
  real32_T U_DC2_Gain_p;               /* Computed Parameter: U_DC2_Gain_p
                                        * Referenced by: '<S95>/U_DC//2'
                                        */
  real32_T Factor_Gain;                /* Computed Parameter: Factor_Gain
                                        * Referenced by: '<S97>/Factor'
                                        */
  real32_T Factor1_Gain;               /* Computed Parameter: Factor1_Gain
                                        * Referenced by: '<S97>/Factor1'
                                        */
  real32_T Factor2_Gain;               /* Computed Parameter: Factor2_Gain
                                        * Referenced by: '<S97>/Factor2'
                                        */
  real32_T Offset_ADC_bits_Ph1_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph1_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph1'
                                 */
  real32_T Offset_ADC_bits_Ph2_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph2_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph2'
                                 */
  real32_T Offset_ADC_bits_Ph3_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph3_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph3'
                                 */
  real32_T Offset_ADC_bits_Ph4_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph4_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph4'
                                 */
  real32_T Offset_ADC_bits_Ph5_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph5_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph5'
                                 */
  real32_T Offset_ADC_bits_Ph6_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph6_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph6'
                                 */
  real32_T Offset_ADC_bits_Ph7_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph7_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph7'
                                 */
  real32_T Offset_ADC_bits_Ph8_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph8_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph8'
                                 */
  real32_T Offset_ADC_bits_Ph9_Value;
                                /* Computed Parameter: Offset_ADC_bits_Ph9_Value
                                 * Referenced by: '<S20>/Offset_ADC_bits_Ph9'
                                 */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S2>/Gain'
                                        */
  real32_T Constant_Value_d[6];        /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S98>/Constant'
                                        */
  real32_T Null_Value[9];              /* Computed Parameter: Null_Value
                                        * Referenced by: '<S1>/Null'
                                        */
  real32_T DiscreteTransferFcn_NumCoef;
                              /* Computed Parameter: DiscreteTransferFcn_NumCoef
                               * Referenced by: '<S14>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_DenCoef[2];
                              /* Computed Parameter: DiscreteTransferFcn_DenCoef
                               * Referenced by: '<S14>/Discrete Transfer Fcn'
                               */
  real32_T DiscreteTransferFcn_InitialStat;
                          /* Computed Parameter: DiscreteTransferFcn_InitialStat
                           * Referenced by: '<S14>/Discrete Transfer Fcn'
                           */
  real32_T f_2_w_el_Gain;              /* Computed Parameter: f_2_w_el_Gain
                                        * Referenced by: '<S14>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value_l;         /* Computed Parameter: FOC_T_fast_Value_l
                                        * Referenced by: '<S91>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S91>/Unit Delay'
                                */
  real32_T TrafoMatrixuvwalphabeta_Gain[6];
                             /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
                              * Referenced by: '<S33>/TrafoMatrix uvw->alphabeta'
                              */
  real32_T ResolverOffsetLimitation_UpperS;
                          /* Computed Parameter: ResolverOffsetLimitation_UpperS
                           * Referenced by: '<S4>/ResolverOffsetLimitation'
                           */
  real32_T ResolverOffsetLimitation_LowerS;
                          /* Computed Parameter: ResolverOffsetLimitation_LowerS
                           * Referenced by: '<S4>/ResolverOffsetLimitation'
                           */
  real32_T UnitDelay_InitialCondition_b;
                             /* Computed Parameter: UnitDelay_InitialCondition_b
                              * Referenced by: '<S26>/Unit Delay'
                              */
  real32_T Constant3_Value_l;          /* Computed Parameter: Constant3_Value_l
                                        * Referenced by: '<S26>/Constant3'
                                        */
  real32_T Constant1_Value_ep;         /* Computed Parameter: Constant1_Value_ep
                                        * Referenced by: '<S26>/Constant1'
                                        */
  real32_T UnitDelay3_InitialCondition;
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S24>/Unit Delay3'
                               */
  real32_T SMF_w_el_Ref_IfStarter_Value;
                             /* Computed Parameter: SMF_w_el_Ref_IfStarter_Value
                              * Referenced by: '<S1>/SMF_w_el_Ref_IfStarter'
                              */
  real32_T FOC_T_fast_Value_d;         /* Computed Parameter: FOC_T_fast_Value_d
                                        * Referenced by: '<S13>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_p;
                             /* Computed Parameter: UnitDelay_InitialCondition_p
                              * Referenced by: '<S13>/Unit Delay'
                              */
  real32_T f_2_w_el_Gain_j;            /* Computed Parameter: f_2_w_el_Gain_j
                                        * Referenced by: '<S10>/f_2_w_el'
                                        */
  real32_T FOC_T_fast_Value_f;         /* Computed Parameter: FOC_T_fast_Value_f
                                        * Referenced by: '<S61>/FOC_T_fast'
                                        */
  real32_T UnitDelay_InitialCondition_d;
                             /* Computed Parameter: UnitDelay_InitialCondition_d
                              * Referenced by: '<S61>/Unit Delay'
                              */
  real32_T IntegDelay1_InitialCondition;
                             /* Computed Parameter: IntegDelay1_InitialCondition
                              * Referenced by: '<S37>/IntegDelay1'
                              */
  real32_T FOC_T_fast_Value_n;         /* Computed Parameter: FOC_T_fast_Value_n
                                        * Referenced by: '<S37>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_p[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
                            * Referenced by: '<S34>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_m;
                           /* Computed Parameter: IntegDelay1_InitialCondition_m
                            * Referenced by: '<S41>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_e;         /* Computed Parameter: FOC_T_fast_Value_e
                                        * Referenced by: '<S41>/FOC_T_fast'
                                        */
  real32_T TrafoMatrixuvwalphabeta_Gain_j[6];
                           /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_j
                            * Referenced by: '<S35>/TrafoMatrix uvw->alphabeta'
                            */
  real32_T IntegDelay1_InitialCondition_p;
                           /* Computed Parameter: IntegDelay1_InitialCondition_p
                            * Referenced by: '<S45>/IntegDelay1'
                            */
  real32_T FOC_T_fast_Value_er;       /* Computed Parameter: FOC_T_fast_Value_er
                                       * Referenced by: '<S45>/FOC_T_fast'
                                       */
  real32_T FOC_T_fast_Value_m;         /* Computed Parameter: FOC_T_fast_Value_m
                                        * Referenced by: '<S5>/FOC_T_fast'
                                        */
  real32_T Switch1_Threshold_a;       /* Computed Parameter: Switch1_Threshold_a
                                       * Referenced by: '<S29>/Switch1'
                                       */
  real32_T Switch2_Threshold_o;       /* Computed Parameter: Switch2_Threshold_o
                                       * Referenced by: '<S29>/Switch2'
                                       */
  real32_T Gain1_Gain_h[4];            /* Computed Parameter: Gain1_Gain_h
                                        * Referenced by: '<S101>/Gain1'
                                        */
  real32_T Gain_Gain_f[4];             /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S101>/Gain'
                                        */
  real32_T Constant_Value_g[6];        /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S99>/Constant'
                                        */
  real32_T Gain1_Gain_ck[4];           /* Computed Parameter: Gain1_Gain_ck
                                        * Referenced by: '<S102>/Gain1'
                                        */
  real32_T Gain_Gain_l[4];             /* Computed Parameter: Gain_Gain_l
                                        * Referenced by: '<S102>/Gain'
                                        */
  real32_T Constant_Value_o[6];        /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S100>/Constant'
                                        */
  real32_T Gain1_Gain_k[4];            /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S103>/Gain1'
                                        */
  real32_T Gain_Gain_j[4];             /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S103>/Gain'
                                        */
  real32_T Scale02_Bias;               /* Computed Parameter: Scale02_Bias
                                        * Referenced by: '<S93>/Scale [0..2]'
                                        */
  real32_T Scale01_Gain;               /* Computed Parameter: Scale01_Gain
                                        * Referenced by: '<S93>/Scale  [0..1]'
                                        */
  real32_T Limit01_UpperSat;           /* Computed Parameter: Limit01_UpperSat
                                        * Referenced by: '<S93>/Limit [0..1]'
                                        */
  real32_T Limit01_LowerSat;           /* Computed Parameter: Limit01_LowerSat
                                        * Referenced by: '<S93>/Limit [0..1]'
                                        */
  real32_T FOC_T_fast_Value_df;       /* Computed Parameter: FOC_T_fast_Value_df
                                       * Referenced by: '<S24>/FOC_T_fast'
                                       */
  real32_T Gain_Gain_kc;               /* Computed Parameter: Gain_Gain_kc
                                        * Referenced by: '<S24>/Gain'
                                        */
  real32_T UnitDelay1_InitialCondition;
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<S28>/Unit Delay1'
                               */
  real32_T FOC_T_fast_Value_c;         /* Computed Parameter: FOC_T_fast_Value_c
                                        * Referenced by: '<S27>/FOC_T_fast'
                                        */
  real32_T FOC_T_fast_Value_k;         /* Computed Parameter: FOC_T_fast_Value_k
                                        * Referenced by: '<S28>/FOC_T_fast'
                                        */
  real32_T Gain1_Gain_kl;              /* Computed Parameter: Gain1_Gain_kl
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real32_T DiscreteFIRFilter20thorder_Init;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Init
                           * Referenced by: '<S33>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Coef[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
                           * Referenced by: '<S33>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_k;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
                           * Referenced by: '<S34>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_a[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
                           * Referenced by: '<S34>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_In_n;
                          /* Computed Parameter: DiscreteFIRFilter20thorder_In_n
                           * Referenced by: '<S35>/Discrete FIR Filter 20th order'
                           */
  real32_T DiscreteFIRFilter20thorder_Co_l[20];
                          /* Computed Parameter: DiscreteFIRFilter20thorder_Co_l
                           * Referenced by: '<S35>/Discrete FIR Filter 20th order'
                           */
  real32_T usrpm_Gain;                 /* Computed Parameter: usrpm_Gain
                                        * Referenced by: '<S12>/[1//s] => [rpm]'
                                        */
  real32_T NO_ERROR_Value;             /* Computed Parameter: NO_ERROR_Value
                                        * Referenced by: '<S48>/NO_ERROR'
                                        */
  real32_T Zero1_Value[2];             /* Computed Parameter: Zero1_Value
                                        * Referenced by: '<S37>/Zero1'
                                        */
  real32_T Gain1_Gain_cs;              /* Computed Parameter: Gain1_Gain_cs
                                        * Referenced by: '<S30>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S30>/Gain2'
                                        */
  real32_T Zero1_Value_l[2];           /* Computed Parameter: Zero1_Value_l
                                        * Referenced by: '<S41>/Zero1'
                                        */
  real32_T Zero1_Value_o[2];           /* Computed Parameter: Zero1_Value_o
                                        * Referenced by: '<S45>/Zero1'
                                        */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S61>/Switch'
                                        */
  real32_T Switch_Threshold_b;         /* Computed Parameter: Switch_Threshold_b
                                        * Referenced by: '<S13>/Switch'
                                        */
  real32_T Switch_Threshold_c;         /* Computed Parameter: Switch_Threshold_c
                                        * Referenced by: '<S91>/Switch'
                                        */
  real32_T Gain_Gain_jm;               /* Computed Parameter: Gain_Gain_jm
                                        * Referenced by: '<S15>/Gain'
                                        */
  real32_T Gain1_Gain_e;               /* Computed Parameter: Gain1_Gain_e
                                        * Referenced by: '<S15>/Gain1'
                                        */
  real32_T Gain2_Gain_f;               /* Computed Parameter: Gain2_Gain_f
                                        * Referenced by: '<S15>/Gain2'
                                        */
  real32_T Gain3_Gain;                 /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<S15>/Gain3'
                                        */
  real32_T DutyCycle_u1_Gain;          /* Computed Parameter: DutyCycle_u1_Gain
                                        * Referenced by: '<S96>/DutyCycle_u1'
                                        */
  real32_T DutyCycle_u2_Gain;          /* Computed Parameter: DutyCycle_u2_Gain
                                        * Referenced by: '<S96>/DutyCycle_u2'
                                        */
  real32_T DutyCycle_u3_Gain;          /* Computed Parameter: DutyCycle_u3_Gain
                                        * Referenced by: '<S96>/DutyCycle_u3'
                                        */
  real32_T DutyCycle_v1_Gain;          /* Computed Parameter: DutyCycle_v1_Gain
                                        * Referenced by: '<S96>/DutyCycle_v1'
                                        */
  real32_T DutyCycle_v2_Gain;          /* Computed Parameter: DutyCycle_v2_Gain
                                        * Referenced by: '<S96>/DutyCycle_v2'
                                        */
  real32_T DutyCycle_v3_Gain;          /* Computed Parameter: DutyCycle_v3_Gain
                                        * Referenced by: '<S96>/DutyCycle_v3'
                                        */
  real32_T DutyCycle_w1_Gain;          /* Computed Parameter: DutyCycle_w1_Gain
                                        * Referenced by: '<S96>/DutyCycle_w1'
                                        */
  real32_T DutyCycle_w2_Gain;          /* Computed Parameter: DutyCycle_w2_Gain
                                        * Referenced by: '<S96>/DutyCycle_w2'
                                        */
  real32_T DutyCycle_w3_Gain;          /* Computed Parameter: DutyCycle_w3_Gain
                                        * Referenced by: '<S96>/DutyCycle_w3'
                                        */
  real32_T Counter_Start_Value;       /* Computed Parameter: Counter_Start_Value
                                       * Referenced by: '<S1>/Counter_Start'
                                       */
  real32_T FCF_Cnt_InitialCondition;
                                 /* Computed Parameter: FCF_Cnt_InitialCondition
                                  * Referenced by: '<S1>/FCF_Cnt'
                                  */
  uint32_T Constant_Value_l;           /* Computed Parameter: Constant_Value_l
                                        * Referenced by: '<S55>/Constant'
                                        */
  uint32_T Constant_Value_eg;          /* Computed Parameter: Constant_Value_eg
                                        * Referenced by: '<S57>/Constant'
                                        */
  uint32_T Constant_Value_f;           /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<S59>/Constant'
                                        */
  boolean_T NoError_Manual_Value;    /* Computed Parameter: NoError_Manual_Value
                                      * Referenced by: '<S8>/NoError_Manual'
                                      */
  boolean_T Constant2_Value_f;         /* Computed Parameter: Constant2_Value_f
                                        * Referenced by: '<S62>/Constant2'
                                        */
  boolean_T Constant1_Value_d;         /* Computed Parameter: Constant1_Value_d
                                        * Referenced by: '<S62>/Constant1'
                                        */
  boolean_T Constant2_Value_c;         /* Computed Parameter: Constant2_Value_c
                                        * Referenced by: '<S63>/Constant2'
                                        */
  boolean_T Constant4_Value_f;         /* Computed Parameter: Constant4_Value_f
                                        * Referenced by: '<S63>/Constant4'
                                        */
  boolean_T Constant2_Value_gw;        /* Computed Parameter: Constant2_Value_gw
                                        * Referenced by: '<S12>/Constant2'
                                        */
  boolean_T Constant1_Value_n;         /* Computed Parameter: Constant1_Value_n
                                        * Referenced by: '<S12>/Constant1'
                                        */
  boolean_T Constant_Value_j;          /* Computed Parameter: Constant_Value_j
                                        * Referenced by: '<S69>/Constant'
                                        */
  boolean_T Constant_Value_dc;         /* Computed Parameter: Constant_Value_dc
                                        * Referenced by: '<S85>/Constant'
                                        */
  boolean_T Constant_Value_eo;         /* Computed Parameter: Constant_Value_eo
                                        * Referenced by: '<S86>/Constant'
                                        */
  boolean_T Constant_Value_ep;         /* Computed Parameter: Constant_Value_ep
                                        * Referenced by: '<S90>/Constant'
                                        */
  boolean_T Logic_table[16];           /* Computed Parameter: Logic_table
                                        * Referenced by: '<S83>/Logic'
                                        */
  boolean_T Logic_table_l[16];         /* Computed Parameter: Logic_table_l
                                        * Referenced by: '<S84>/Logic'
                                        */
  boolean_T Logic_table_o[16];         /* Computed Parameter: Logic_table_o
                                        * Referenced by: '<S68>/Logic'
                                        */
  boolean_T Logic_table_lc[16];        /* Computed Parameter: Logic_table_lc
                                        * Referenced by: '<S89>/Logic'
                                        */
  boolean_T SELECT_DataSource_Value;
                                  /* Computed Parameter: SELECT_DataSource_Value
                                   * Referenced by: '<S8>/SELECT_DataSource'
                                   */
  boolean_T Logic_table_l5[16];        /* Computed Parameter: Logic_table_l5
                                        * Referenced by: '<S70>/Logic'
                                        */
  boolean_T Logic_table_p[16];         /* Computed Parameter: Logic_table_p
                                        * Referenced by: '<S71>/Logic'
                                        */
  boolean_T Logic_table_j[16];         /* Computed Parameter: Logic_table_j
                                        * Referenced by: '<S72>/Logic'
                                        */
  boolean_T Logic_table_o1[16];        /* Computed Parameter: Logic_table_o1
                                        * Referenced by: '<S73>/Logic'
                                        */
  boolean_T Logic_table_i[16];         /* Computed Parameter: Logic_table_i
                                        * Referenced by: '<S74>/Logic'
                                        */
  boolean_T Logic_table_c[16];         /* Computed Parameter: Logic_table_c
                                        * Referenced by: '<S75>/Logic'
                                        */
  boolean_T Logic_table_ij[16];        /* Computed Parameter: Logic_table_ij
                                        * Referenced by: '<S76>/Logic'
                                        */
  boolean_T Logic_table_pd[16];        /* Computed Parameter: Logic_table_pd
                                        * Referenced by: '<S77>/Logic'
                                        */
  boolean_T Logic_table_a[16];         /* Computed Parameter: Logic_table_a
                                        * Referenced by: '<S78>/Logic'
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

/* External data declarations for dependent source files */
extern const bus_FCF_t FOC_FCF_rtZbus_FCF_t;/* bus_FCF_t ground */

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
 * '<S2>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units'
 * '<S3>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ASC_Switch'
 * '<S4>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption'
 * '<S5>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Lead'
 * '<S6>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller'
 * '<S7>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Enable_If_Mode'
 * '<S8>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Error_Handling'
 * '<S9>'   : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status'
 * '<S10>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/I_f'
 * '<S11>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis'
 * '<S12>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis'
 * '<S13>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/SubS_2pi_Integrator'
 * '<S14>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f'
 * '<S15>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output'
 * '<S16>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas'
 * '<S17>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/U_DC_meas'
 * '<S18>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas/PhaseCurrentMeasurement'
 * '<S19>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas/Phase_Assignment'
 * '<S20>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas/PhaseCurrentMeasurement/ADC_bin2ampere'
 * '<S21>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas/PhaseCurrentMeasurement/ADC_bin2ampere/Current_Sensor_Calibration'
 * '<S22>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas/PhaseCurrentMeasurement/ADC_bin2ampere/Current_Sensor_Calibration/LowPass'
 * '<S23>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/ADC_to_SI_units/I_ph_meas/PhaseCurrentMeasurement/ADC_bin2ampere/Current_Sensor_Calibration/LowPass/CurrentSensorAutoCalibration'
 * '<S24>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver'
 * '<S25>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/Modulo2Pi'
 * '<S26>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/2PiKorr'
 * '<S27>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator'
 * '<S28>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Adaption/AngleObserver/integrator1'
 * '<S29>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Angle_Lead/Modulo2Pi'
 * '<S30>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1'
 * '<S31>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2'
 * '<S32>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3'
 * '<S33>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_1'
 * '<S34>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_2'
 * '<S35>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/UVW_DQ_3'
 * '<S36>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup'
 * '<S37>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/FeedbackPI'
 * '<S38>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_d'
 * '<S39>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_1/AntiWindup/AntiWindupGT_q'
 * '<S40>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup'
 * '<S41>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/FeedbackPI'
 * '<S42>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_d'
 * '<S43>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_2/AntiWindup/AntiWindupGT_q'
 * '<S44>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup'
 * '<S45>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/FeedbackPI'
 * '<S46>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup/AntiWindupGT_d'
 * '<S47>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Current_Controller/PI_Controller_3/AntiWindup/AntiWindupGT_q'
 * '<S48>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Error_Handling/Gate_Driver_FLT_RDY_Error'
 * '<S49>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv1_FLT'
 * '<S50>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv1_RDY'
 * '<S51>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv2_FLT'
 * '<S52>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv2_RDY'
 * '<S53>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv3_FLT'
 * '<S54>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv3_RDY'
 * '<S55>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv1_FLT/Compare To Zero'
 * '<S56>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv1_RDY/Compare To Constant'
 * '<S57>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv2_FLT/Compare To Zero'
 * '<S58>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv2_RDY/Compare To Constant'
 * '<S59>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv3_FLT/Compare To Zero'
 * '<S60>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Gate_Driver_Status/Inv3_RDY/Compare To Constant'
 * '<S61>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/I_f/SubS_2pi_Integrator'
 * '<S62>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection'
 * '<S63>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection'
 * '<S64>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Compare To Constant'
 * '<S65>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Compare To Constant1'
 * '<S66>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Detect Rise Positive'
 * '<S67>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching'
 * '<S68>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/S-R Flip-Flop'
 * '<S69>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Detect Rise Positive/Positive'
 * '<S70>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_1'
 * '<S71>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_2'
 * '<S72>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_3'
 * '<S73>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_4'
 * '<S74>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_5'
 * '<S75>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_6'
 * '<S76>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_7'
 * '<S77>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_8'
 * '<S78>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OC_Detection/Overcurrent_Latching/OverTemp_Latching_9'
 * '<S79>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Compare To Constant'
 * '<S80>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Compare To Constant1'
 * '<S81>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive'
 * '<S82>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive1'
 * '<S83>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/S-R Flip-Flop'
 * '<S84>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/S-R Flip-Flop1'
 * '<S85>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive/Positive'
 * '<S86>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/OC_OV_UV_Diagnosis/OV_UV_Detection/Detect Rise Positive1/Positive'
 * '<S87>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/Compare To Constant1'
 * '<S88>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/Detect Rise Positive'
 * '<S89>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/S-R Flip-Flop'
 * '<S90>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Overspeed_Diagnosis/Detect Rise Positive/Positive'
 * '<S91>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/SubS_2pi_Integrator'
 * '<S92>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/U_f/UfKennlinie'
 * '<S93>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Adjust_duty_cycle_range'
 * '<S94>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Calc_Modulation_Index'
 * '<S95>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/NormalizedVoltage'
 * '<S96>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Phase_Assignment'
 * '<S97>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/Super_Sinus_Modulation'
 * '<S98>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_1'
 * '<S99>'  : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_2'
 * '<S100>' : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Clarke-Trafo_3'
 * '<S101>' : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_1'
 * '<S102>' : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_2'
 * '<S103>' : 'MotorControl_HeadModel/Motor_Control_Model/FOC_FCF/Voltage_Output/inverse Park-Trafo_3'
 */
#endif                                 /* FOC_FCF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
