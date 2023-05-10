/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_CurrentControl.c
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

#include "FOC_CurrentControl.h"
#include "rtwtypes.h"
#include <math.h>
#include <stddef.h>
#define NumBitsPerChar                 8U
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Exported block signals */
real_T FOC_U_DC;                       /* '<S2>/Switch1' */
real_T FOC_Mode_after_checks;          /* '<S2>/Switch' */
real_T Phi_Observer;                   /* '<S23>/Sum7' */
real_T U_u;                            /* '<S38>/Gain1' */
real_T U_v;                            /* '<S38>/Gain2' */
real_T U_w;                            /* '<S38>/Gain5' */
real_T Mod_Index;                      /* '<S9>/Gain1' */
real_T duty_cycle_u;                   /* '<S35>/Gain1' */
real_T duty_cycle_v;                   /* '<S35>/Gain2' */
real_T duty_cycle_w;                   /* '<S35>/Gain3' */
real_T Phi_el_U_Transformation;        /* '<S5>/dummy_gain2' */
real_T u_d_Integrator;                 /* '<S32>/dummy' */
real_T u_q_Integrator;                 /* '<S32>/dummy1' */
real_T I_d_Ref;                        /* '<S6>/PsiReduceGain3' */
real_T I_q_Ref;                        /* '<S6>/PsiReduceGain4' */
real_T I_q_Act_filt;                   /* '<S30>/Gain6' */
real_T I_q_Act;                        /* '<S30>/Gain1' */
real_T I_d_Act_filt;                   /* '<S30>/Gain5' */
real_T I_d_Act;                        /* '<S30>/Gain' */
real_T Phi_est_error_I_Trafo;          /* '<S5>/dummy_gain4' */
real_T Phi_el_I_Transformation;        /* '<S5>/dummy_gain1' */
real_T Phi_est;                        /* '<S5>/dummy_gain5' */
real_T FOC_AngleEst_w_el;              /* '<S4>/Gain2' */
real_T FOC_AngleEst_Psi_PM_alpha;      /* '<S4>/Gain3' */
real_T FOC_AngleEst_Psi_PM_beta;       /* '<S4>/Gain4' */
real_T IfStarter_process_finished;     /* '<S10>/dummy_gain5' */
real_T w_el;                           /* '<S5>/dummy_gain' */
real_T I_u;                            /* '<S30>/Gain2' */
real_T I_v;                            /* '<S30>/Gain3' */
real_T I_w;                            /* '<S30>/Gain4' */
real_T n_Ref;                          /* '<S61>/Switch2' */
real_T SPEED_CTRL_w_el_err;            /* '<S14>/Add' */
real_T n_Act;                          /* '<S14>/RPM => w_el1' */
real_T SPEED_CTRL_Iq_Ref;              /* '<S14>/dummy_gain5' */
real_T SPEED_CTRL_Integ;               /* '<S14>/dummy_gain1' */
real_T SPEED_CTRL_Prop;                /* '<S14>/dummy_gain3' */
real_T SPEED_CTRL_enable;              /* '<S14>/dummy_gain2' */
real_T u_d;                            /* '<S36>/Gain' */
real_T u_q;                            /* '<S36>/Gain1' */
real_T u_beta;                         /* '<S36>/Add' */
real_T u_alpha;                        /* '<S36>/Subtract' */
real_T u_q_filt;                       /* '<S36>/Gain3' */
real_T u_d_filt;                       /* '<S36>/Gain2' */
real32_T FOC_Overcurrent_I_uvw;        /* '<S11>/Gain1' */
real32_T FOC_Overvoltage_U_DC;         /* '<S12>/Gain2' */
real32_T FOC_Undervoltage_U_DC;        /* '<S12>/Gain1' */
boolean_T i_d_IntegNotStopped;         /* '<S31>/AntiWindupOR_d' */
boolean_T i_q_IntegNotStopped;         /* '<S31>/AntiWindupOR_q' */

/* Exported block parameters */
real_T FOC_AKS_Mode = 1.0;             /* Variable: FOC_AKS_Mode
                                        * Referenced by: '<S3>/FOC_AKS_Mode'
                                        */
real_T FOC_AngleEst_Delay1 = 1.0;      /* Variable: FOC_AngleEst_Delay1
                                        * Referenced by: '<S20>/FOC_AngleEst_Delay1'
                                        */
real_T FOC_AngleEst_Delay2 = 0.0;      /* Variable: FOC_AngleEst_Delay2
                                        * Referenced by: '<S20>/FOC_AngleEst_Delay2'
                                        */
real_T FOC_AngleEst_Komp_KP = 500.0;   /* Variable: FOC_AngleEst_Komp_KP
                                        * Referenced by: '<S4>/komp_kp'
                                        */
real_T FOC_AngleEst_Lq = 0.00034;      /* Variable: FOC_AngleEst_Lq
                                        * Referenced by: '<S4>/FOC_AngleEst_Lq'
                                        */
real_T FOC_AngleEst_Psi_InitVal = 0.0; /* Variable: FOC_AngleEst_Psi_InitVal
                                        * Referenced by: '<S21>/Unit Delay'
                                        */
real_T FOC_AngleEst_Rs = 0.092096;     /* Variable: FOC_AngleEst_Rs
                                        * Referenced by: '<S4>/FOC_AngleEst_Rs'
                                        */
real_T FOC_AngleEst_w_el_filtered_Tau = 0.0005;
                                     /* Variable: FOC_AngleEst_w_el_filtered_Tau
                                      * Referenced by: '<S18>/Tau'
                                      */
real_T FOC_AngleObs_w_InitVal = 0.0;   /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S27>/Unit Delay1'
                                        */
real_T FOC_AngleObserver_D = 1.0;      /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S23>/Constant1'
                                        */
real_T FOC_AngleObserver_w0 = 200.0;   /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S23>/Constant'
                                        */
real_T FOC_ENABLE_IfStarter = 1.0;     /* Variable: FOC_ENABLE_IfStarter
                                        * Referenced by: '<S10>/Enable_If_Starter'
                                        */
real_T FOC_ENABLE_Overcurrent_I_uvw = 0.0;/* Variable: FOC_ENABLE_Overcurrent_I_uvw
                                           * Referenced by: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
                                           */
real_T FOC_ENABLE_Overvoltage_U_DC = 0.0;/* Variable: FOC_ENABLE_Overvoltage_U_DC
                                          * Referenced by: '<S12>/FOC_ENABLE_Overvoltage_U_DC1'
                                          */
real_T FOC_ENABLE_Undervoltage_U_DC = 0.0;/* Variable: FOC_ENABLE_Undervoltage_U_DC
                                           * Referenced by: '<S12>/FOC_ENABLE_Undervoltage_U_DC1'
                                           */
real_T FOC_Enable = 1.0;               /* Variable: FOC_Enable
                                        * Referenced by: '<S2>/Enable'
                                        */
real_T FOC_Id_Ref_constFW_factor = -0.000343;/* Variable: FOC_Id_Ref_constFW_factor
                                              * Referenced by: '<S14>/Constant10'
                                              */
real_T FOC_Id_Ref_constFW_offset = 4.24;/* Variable: FOC_Id_Ref_constFW_offset
                                         * Referenced by: '<S14>/Constant11'
                                         */
real_T FOC_IfStarter_Delta_w = 104.719755;/* Variable: FOC_IfStarter_Delta_w
                                           * Referenced by: '<S10>/Delta_w'
                                           */
real_T FOC_IfStarter_Id_Ref = 30.0;    /* Variable: FOC_IfStarter_Id_Ref
                                        * Referenced by: '<S10>/I_d_Ref'
                                        */
real_T FOC_IfStarter_T_Id_Ramp = 0.2;  /* Variable: FOC_IfStarter_T_Id_Ramp
                                        * Referenced by: '<S10>/T_Id_Ramp'
                                        */
real_T FOC_IfStarter_T_switch = 1.0;   /* Variable: FOC_IfStarter_T_switch
                                        * Referenced by: '<S10>/T_switch'
                                        */
real_T FOC_IfStarter_T_w_Ramp = 1.0;   /* Variable: FOC_IfStarter_T_w_Ramp
                                        * Referenced by: '<S10>/T_w_Ramp'
                                        */
real_T FOC_IfStarter_T_w_Wait = 1.0;   /* Variable: FOC_IfStarter_T_w_Wait
                                        * Referenced by: '<S10>/T_w_Wait'
                                        */
real_T FOC_IfStarter_Trigger = 1.0;    /* Variable: FOC_IfStarter_Trigger
                                        * Referenced by: '<S2>/FOC_IfStarter_Trigger'
                                        */
real_T FOC_IfStarter_w_el_Ref = 1047.197551;/* Variable: FOC_IfStarter_w_el_Ref
                                             * Referenced by: '<S10>/w_el_Ref'
                                             */
real_T FOC_IfStarter_w_min_off = 523.598776;/* Variable: FOC_IfStarter_w_min_off
                                             * Referenced by: '<S10>/w_min_off'
                                             */
real_T FOC_IntegDamp = 0.995;          /* Variable: FOC_IntegDamp
                                        * Referenced by: '<S32>/FOC_IntegDamp'
                                        */
real_T FOC_KI = 150.0;                 /* Variable: FOC_KI
                                        * Referenced by: '<S32>/FOC_KI'
                                        */
real_T FOC_KP = 0.4;                   /* Variable: FOC_KP
                                        * Referenced by: '<S32>/FOC_KP1'
                                        */
real_T FOC_LIMIT_I_PHASE_PEAK_MAX = 240.0;/* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
                                           * Referenced by:
                                           *   '<S14>/limit T1'
                                           *   '<S14>/limit T3'
                                           */
real_T FOC_LIMIT_MAX_Id_Ref_constFW = 0.0;/* Variable: FOC_LIMIT_MAX_Id_Ref_constFW
                                           * Referenced by: '<S14>/Constant8'
                                           */
real_T FOC_LIMIT_MIN_Id_Ref_constFW = -35.0;/* Variable: FOC_LIMIT_MIN_Id_Ref_constFW
                                             * Referenced by: '<S14>/Constant9'
                                             */
real_T FOC_LIMIT_Overcurrent_I_uvw = 240.0;/* Variable: FOC_LIMIT_Overcurrent_I_uvw
                                            * Referenced by: '<S51>/Constant'
                                            */
real_T FOC_LIMIT_Overvoltage_U_DC = 910.0;/* Variable: FOC_LIMIT_Overvoltage_U_DC
                                           * Referenced by: '<S56>/Constant'
                                           */
real_T FOC_LIMIT_Undervoltage_U_DC = 10.0;/* Variable: FOC_LIMIT_Undervoltage_U_DC
                                           * Referenced by: '<S55>/Constant'
                                           */
real_T FOC_LIMIT_n_Ref_SlewRate_Down = -10000.0;
                                      /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
                                       * Referenced by: '<S61>/Constant7'
                                       */
real_T FOC_LIMIT_n_Ref_SlewRate_InitVal = 0.0;
                                   /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
                                    * Referenced by: '<S64>/Delay Input2'
                                    */
real_T FOC_LIMIT_n_Ref_SlewRate_Up = 12000.0;/* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
                                              * Referenced by: '<S61>/Constant6'
                                              */
real_T FOC_MANUAL_Id_Ref_SPEED_CTRL = 0.0;/* Variable: FOC_MANUAL_Id_Ref_SPEED_CTRL
                                           * Referenced by: '<S14>/Constant6'
                                           */
real_T FOC_MANUAL_U_DC = 0.0;          /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S2>/Udc1'
                                        */
real_T FOC_MaxModInd = 1.15;           /* Variable: FOC_MaxModInd
                                        * Referenced by: '<S31>/FOC_MaxModInd'
                                        */
real_T FOC_Mode = 1.0;                 /* Variable: FOC_Mode
                                        * Referenced by: '<S2>/FOC_Mode'
                                        */
real_T FOC_OmegaObs3 = 0.0;            /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S23>/Gain4'
                                        */
real_T FOC_PhiSensorTdead = 0.0;       /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S23>/DeadTimeCompensation'
                                        */
real_T FOC_RESET_OC_Error = 0.0;       /* Variable: FOC_RESET_OC_Error
                                        * Referenced by: '<S11>/Reset_OC_Error'
                                        */
real_T FOC_RESET_OV_Error = 0.0;       /* Variable: FOC_RESET_OV_Error
                                        * Referenced by: '<S12>/Reset_OV_Error'
                                        */
real_T FOC_SELECT_AngleEst_w_el_filtered = 1.0;
                                  /* Variable: FOC_SELECT_AngleEst_w_el_filtered
                                   * Referenced by: '<S4>/useFilteredCorrection'
                                   */
real_T FOC_SELECT_Id_Ref_constFW = 2.0;/* Variable: FOC_SELECT_Id_Ref_constFW
                                        * Referenced by: '<S14>/Constant12'
                                        */
real_T FOC_SELECT_Modulation = 1.0;    /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S9>/modulation'
                                        */
real_T FOC_SELECT_Phase_Assignment_UVW = 1.0;
                                    /* Variable: FOC_SELECT_Phase_Assignment_UVW
                                     * Referenced by: '<S13>/Selektierung Phase'
                                     */
real_T FOC_SELECT_U_DC_INPUT = 1.0;    /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S2>/0: P_Udc 1: Udc_measured'
                                        */
real_T FOC_SELECT_n_Ref_Ramp = 1.0;    /* Variable: FOC_SELECT_n_Ref_Ramp
                                        * Referenced by: '<S61>/Constant5'
                                        */
real_T FOC_SELECT_phi = 2.0;           /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S5>/Constant3'
                                        */
real_T FOC_SELECT_speed_control = 1.0; /* Variable: FOC_SELECT_speed_control
                                        * Referenced by: '<S2>/0: on // 1: off'
                                        */
real_T FOC_T_fast = 4.1666666666666665E-5;/* Variable: FOC_T_fast
                                           * Referenced by: '<S5>/Gain'
                                           */
real_T FOC_Uf_U_max = 0.0;             /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S67>/Saturation1'
                                        */
real_T FOC_Uf_U_min = 0.0;             /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S67>/Saturation1'
                                        */
real_T FOC_Uf_Ud = 0.0;                /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S15>/Uf_Ud'
                                        */
real_T FOC_Uf_f_el = 0.0;              /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S15>/Uf_w_el'
                                        */
real_T FOC_Uf_m = 0.0;                 /* Variable: FOC_Uf_m
                                        * Referenced by: '<S67>/Gain'
                                        */
real_T FOC_f_fastCTRL = 24000.0;       /* Variable: FOC_f_fastCTRL
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
real_T FOC_output_trafo_delay = 1.5;   /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S5>/Gain'
                                        */
real_T FOC_phi_offset = 0.0;           /* Variable: FOC_phi_offset
                                        * Referenced by: '<S5>/Constant'
                                        */
real_T FOC_z_P = 1.0;                  /* Variable: FOC_z_P
                                        * Referenced by:
                                        *   '<S14>/RPM => w_el'
                                        *   '<S14>/RPM => w_el1'
                                        */
real_T Factor_OmegaRot = 1.0;          /* Variable: Factor_OmegaRot
                                        * Referenced by: '<S23>/Gain5'
                                        */
real_T SELECT_SPEED_CTRL_V_R = 2.0;    /* Variable: SELECT_SPEED_CTRL_V_R
                                        * Referenced by: '<S14>/Constant15'
                                        */
real_T SPEED_CTRL_IQ_MAX = 0.0;        /* Variable: SPEED_CTRL_IQ_MAX
                                        * Referenced by: '<S14>/Constant1'
                                        */
real_T SPEED_CTRL_IQ_MIN = 0.0;        /* Variable: SPEED_CTRL_IQ_MIN
                                        * Referenced by: '<S14>/Constant2'
                                        */
real_T SPEED_CTRL_K_AWU = 1.0;         /* Variable: SPEED_CTRL_K_AWU
                                        * Referenced by: '<S14>/Gain1'
                                        */
real_T SPEED_CTRL_LIMIT_n_Ref_MAX = 140000.0;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
                                              * Referenced by: '<S14>/limit T2'
                                              */
real_T SPEED_CTRL_LIMIT_n_Ref_MIN = 0.0;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
                                         * Referenced by: '<S14>/limit T2'
                                         */
real_T SPEED_CTRL_MANUAL_n_RPM = 10000.0;/* Variable: SPEED_CTRL_MANUAL_n_RPM
                                          * Referenced by: '<S14>/OmegaRot2'
                                          */
real_T SPEED_CTRL_SELECT_IfStarter = 1.0;/* Variable: SPEED_CTRL_SELECT_IfStarter
                                          * Referenced by: '<S2>/OmegaRot1'
                                          */
real_T SPEED_CTRL_SELECT_TorqLimit = 1.0;/* Variable: SPEED_CTRL_SELECT_TorqLimit
                                          * Referenced by: '<S14>/OmegaRot3'
                                          */
real_T SPEED_CTRL_SELECT_n_Ref = 1.0;  /* Variable: SPEED_CTRL_SELECT_n_Ref
                                        * Referenced by: '<S14>/OmegaRot1'
                                        */
real_T SPEED_CTRL_TORQLIMNEG = 0.0;    /* Variable: SPEED_CTRL_TORQLIMNEG
                                        * Referenced by: '<S14>/Constant5'
                                        */
real_T SPEED_CTRL_TORQLIMPOS = 0.0;    /* Variable: SPEED_CTRL_TORQLIMPOS
                                        * Referenced by: '<S14>/Constant4'
                                        */
real_T SPEED_CTRL_T_N = 0.6;           /* Variable: SPEED_CTRL_T_N
                                        * Referenced by: '<S14>/Constant'
                                        */
real_T SPEED_CTRL_V_R = 0.01;          /* Variable: SPEED_CTRL_V_R
                                        * Referenced by: '<S14>/Constant14'
                                        */
real32_T FOC_SELECT_Voltage_Assignment_UVW = 1.0F;
                                  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
                                   * Referenced by: '<S35>/Constant6'
                                   */

/* Block signals and states (default storage) */
//DW rtDW;
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
//ExtU rtU;
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
//ExtY rtY;
extern ExtY rtY;

/* Real-time model */
//static RT_MODEL rtM_;
extern RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
static real_T look1_pbinlca(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static real_T look2_binlx(real_T u0, real_T u1, const real_T bp0[], const real_T
  bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

static real_T look1_pbinlca(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T found;
    uint32_T iLeft;
    uint32_T iRght;

    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex;
    frac = 0.0;
  }

  prevIndex[0U] = bpIdx;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

static real_T look2_binlx(real_T u0, real_T u1, const real_T bp0[], const real_T
  bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride)
{
  real_T fractions[2];
  real_T frac;
  real_T yL_0d0;
  real_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T u0_0;
    int32_T u1_0;
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void FOC_CurrentControl_step(void)
{
  real_T rtb_TrafoMatrixuvwalphabeta[2];
  int32_T rowIdx;
  int32_T tmp;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_CurrentControl' */
  /* Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
   *  EnablePort: '<S2>/Enable1'
   */
  /* Inport: '<Root>/Enable' */
  if (rtU.Enable > 0.0) {
    real_T DiscreteTransferFcn_tmp;
    real_T f_2_w_el;
    real_T rtb_Abs_i;
    real_T rtb_Add;
    real_T rtb_Add_h;
    real_T rtb_DiscreteFIRFilter20thorder;
    real_T rtb_Divide1_idx_1;
    real_T rtb_Gain4;
    real_T rtb_IntegEnaSwitch1_idx_1;
    real_T rtb_KPek1_idx_0;
    real_T rtb_KPek1_idx_1;
    real_T rtb_MinMax;
    real_T rtb_MinMax_c;
    real_T rtb_MinMax_l;
    real_T rtb_MultiportSwitch;
    real_T rtb_Product;
    real_T rtb_Product1;
    real_T rtb_Product_b;
    real_T rtb_Product_i;
    real_T rtb_Product_m;
    real_T rtb_SelectVoltCalc_1_idx_0;
    real_T rtb_SelectVoltCalc_1_idx_1;
    real_T rtb_SelectVoltCalc_1_idx_2;
    real_T rtb_Speed_Ctrl_Start_Sequence;
    real_T rtb_Subtract2_p;
    real_T rtb_Sum1_f;
    real_T rtb_Switch2_e;
    real_T rtb_Switch_speed;
    real_T rtb_TorqLimitSource_idx_0;
    real_T rtb_TorqLimitSource_idx_1;
    real_T rtb_TrigonometricFunction;
    real_T rtb_UkYk1;
    real_T rtb_antiWindupProd_idx_0;
    real_T rtb_antiWindupProd_idx_1;
    real_T rtb_phi_U_Trafo_Switch;
    real_T rtb_psi_PM_alphabeta_idx_0;
    real_T rtb_psi_PM_alphabeta_idx_1;
    uint8_T rtb_Compare;
    boolean_T rtb_Compare_g;
    boolean_T rtb_Compare_i;
    boolean_T rtb_Compare_k;
    boolean_T rtb_Compare_l;
    boolean_T rtb_Logic_e_idx_0;
    boolean_T rtb_Logic_e_idx_1;
    boolean_T rtb_Logic_idx_0;
    boolean_T rtb_Logic_idx_1;
    boolean_T rtb_Logic_m_idx_0;
    boolean_T rtb_LogicalOperator2;
    boolean_T rtb_LogicalOperator4;
    boolean_T rtb_LogicalOperator5;

    /* Switch: '<S2>/Switch1' incorporates:
     *  Constant: '<S2>/0: P_Udc 1: Udc_measured'
     */
    if (FOC_SELECT_U_DC_INPUT > rtP.Switch1_Threshold_e) {
      /* Switch: '<S2>/Switch1' incorporates:
       *  Inport: '<Root>/U_DC'
       */
      FOC_U_DC = rtU.U_DC;
    } else {
      /* Switch: '<S2>/Switch1' incorporates:
       *  Constant: '<S2>/Udc1'
       */
      FOC_U_DC = FOC_MANUAL_U_DC;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* MultiPortSwitch: '<S12>/Selectphicalc3' incorporates:
     *  Constant: '<S12>/Constant2'
     *  Constant: '<S12>/FOC_ENABLE_Undervoltage_U_DC1'
     *  Constant: '<S2>/Enable'
     *  Logic: '<S12>/Logical Operator1'
     */
    if ((int32_T)FOC_ENABLE_Undervoltage_U_DC == 0) {
      rtb_LogicalOperator2 = rtP.Constant2_Value_j;
    } else {
      rtb_LogicalOperator2 = !(FOC_Enable != 0.0);
    }

    /* End of MultiPortSwitch: '<S12>/Selectphicalc3' */

    /* CombinatorialLogic: '<S58>/Logic' incorporates:
     *  Constant: '<S2>/Enable'
     *  Constant: '<S55>/Constant'
     *  Logic: '<S12>/Logical Operator2'
     *  Memory: '<S58>/Memory'
     *  RelationalOperator: '<S55>/Compare'
     */
    rowIdx = (int32_T)(((((uint32_T)((FOC_U_DC < FOC_LIMIT_Undervoltage_U_DC) &&
      (FOC_Enable != 0.0)) << 1) + rtb_LogicalOperator2) << 1) +
                       rtDW.Memory_PreviousInput);
    rtb_Logic_idx_0 = rtP.Logic_table[(uint32_T)rowIdx];
    rtb_Logic_idx_1 = rtP.Logic_table[rowIdx + 8U];

    /* RelationalOperator: '<S60>/Compare' incorporates:
     *  Constant: '<S12>/Reset_OV_Error'
     *  Constant: '<S60>/Constant'
     */
    rtb_Compare_k = (FOC_RESET_OV_Error > rtP.Constant_Value_a);

    /* MultiPortSwitch: '<S12>/Selectphicalc4' incorporates:
     *  Constant: '<S12>/Constant4'
     *  Constant: '<S12>/FOC_ENABLE_Overvoltage_U_DC1'
     *  RelationalOperator: '<S57>/FixPt Relational Operator'
     *  UnitDelay: '<S57>/Delay Input1'
     *
     * Block description for '<S57>/Delay Input1':
     *
     *  Store in Global RAM
     */
    if ((int32_T)FOC_ENABLE_Overvoltage_U_DC == 0) {
      rtb_LogicalOperator2 = rtP.Constant4_Value_c;
    } else {
      rtb_LogicalOperator2 = ((int32_T)rtb_Compare_k > (int32_T)
        rtDW.DelayInput1_DSTATE);
    }

    /* End of MultiPortSwitch: '<S12>/Selectphicalc4' */

    /* CombinatorialLogic: '<S59>/Logic' incorporates:
     *  Constant: '<S56>/Constant'
     *  Memory: '<S59>/Memory'
     *  RelationalOperator: '<S56>/Compare'
     */
    rowIdx = (int32_T)(((((uint32_T)(FOC_U_DC > FOC_LIMIT_Overvoltage_U_DC) << 1)
                         + rtb_LogicalOperator2) << 1) +
                       rtDW.Memory_PreviousInput_n);
    rtb_Logic_e_idx_0 = rtP.Logic_table_c[(uint32_T)rowIdx];
    rtb_Logic_e_idx_1 = rtP.Logic_table_c[rowIdx + 8U];

    /* MultiPortSwitch: '<S13>/SelectVoltCalc_1' incorporates:
     *  Constant: '<S13>/Selektierung Phase'
     *  Inport: '<Root>/I_uvw'
     */
    switch ((int32_T)FOC_SELECT_Phase_Assignment_UVW) {
     case 1:
      rtb_SelectVoltCalc_1_idx_0 = rtU.I_uvw[0];
      rtb_SelectVoltCalc_1_idx_1 = rtU.I_uvw[1];
      rtb_SelectVoltCalc_1_idx_2 = rtU.I_uvw[2];
      break;

     case 2:
      rtb_SelectVoltCalc_1_idx_0 = rtU.I_uvw[0];
      rtb_SelectVoltCalc_1_idx_1 = rtU.I_uvw[2];
      rtb_SelectVoltCalc_1_idx_2 = rtU.I_uvw[1];
      break;

     case 3:
      rtb_SelectVoltCalc_1_idx_0 = rtU.I_uvw[1];
      rtb_SelectVoltCalc_1_idx_1 = rtU.I_uvw[0];
      rtb_SelectVoltCalc_1_idx_2 = rtU.I_uvw[2];
      break;

     case 4:
      rtb_SelectVoltCalc_1_idx_0 = rtU.I_uvw[1];
      rtb_SelectVoltCalc_1_idx_1 = rtU.I_uvw[2];
      rtb_SelectVoltCalc_1_idx_2 = rtU.I_uvw[0];
      break;

     case 5:
      rtb_SelectVoltCalc_1_idx_0 = rtU.I_uvw[2];
      rtb_SelectVoltCalc_1_idx_1 = rtU.I_uvw[0];
      rtb_SelectVoltCalc_1_idx_2 = rtU.I_uvw[1];
      break;

     default:
      rtb_SelectVoltCalc_1_idx_0 = rtU.I_uvw[2];
      rtb_SelectVoltCalc_1_idx_1 = rtU.I_uvw[1];
      rtb_SelectVoltCalc_1_idx_2 = rtU.I_uvw[0];
      break;
    }

    /* End of MultiPortSwitch: '<S13>/SelectVoltCalc_1' */

    /* RelationalOperator: '<S54>/Compare' incorporates:
     *  Constant: '<S11>/Reset_OC_Error'
     *  Constant: '<S54>/Constant'
     */
    rtb_Compare_i = (FOC_RESET_OC_Error > rtP.Constant_Value_n);

    /* MultiPortSwitch: '<S11>/Selectphicalc2' incorporates:
     *  Constant: '<S11>/Constant1'
     *  Constant: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
     *  RelationalOperator: '<S52>/FixPt Relational Operator'
     *  UnitDelay: '<S52>/Delay Input1'
     *
     * Block description for '<S52>/Delay Input1':
     *
     *  Store in Global RAM
     */
    if ((int32_T)FOC_ENABLE_Overcurrent_I_uvw == 0) {
      rtb_LogicalOperator2 = rtP.Constant1_Value_g;
    } else {
      rtb_LogicalOperator2 = ((int32_T)rtb_Compare_i > (int32_T)
        rtDW.DelayInput1_DSTATE_e);
    }

    /* End of MultiPortSwitch: '<S11>/Selectphicalc2' */

    /* CombinatorialLogic: '<S53>/Logic' incorporates:
     *  Abs: '<S11>/Abs'
     *  Constant: '<S51>/Constant'
     *  Memory: '<S53>/Memory'
     *  MinMax: '<S11>/MinMax'
     *  RelationalOperator: '<S51>/Compare'
     */
    rowIdx = (int32_T)(((((uint32_T)(fmax(fmax(fabs(rtb_SelectVoltCalc_1_idx_0),
      fabs(rtb_SelectVoltCalc_1_idx_1)), fabs(rtb_SelectVoltCalc_1_idx_2)) >=
      FOC_LIMIT_Overcurrent_I_uvw) << 1) + rtb_LogicalOperator2) << 1) +
                       rtDW.Memory_PreviousInput_f);
    rtb_Logic_m_idx_0 = rtP.Logic_table_k[(uint32_T)rowIdx];

    /* MultiPortSwitch: '<S12>/Selectphicalc1' incorporates:
     *  Constant: '<S12>/Constant3'
     *  Constant: '<S12>/FOC_ENABLE_Undervoltage_U_DC1'
     */
    if ((int32_T)FOC_ENABLE_Undervoltage_U_DC == 0) {
      rtb_Logic_idx_1 = rtP.Constant3_Value_f;
    }

    /* End of MultiPortSwitch: '<S12>/Selectphicalc1' */

    /* MultiPortSwitch: '<S12>/Selectphicalc2' incorporates:
     *  Constant: '<S12>/Constant1'
     *  Constant: '<S12>/FOC_ENABLE_Overvoltage_U_DC1'
     */
    if ((int32_T)FOC_ENABLE_Overvoltage_U_DC == 0) {
      rtb_Logic_e_idx_1 = rtP.Constant1_Value_jr;
    }

    /* End of MultiPortSwitch: '<S12>/Selectphicalc2' */

    /* MultiPortSwitch: '<S11>/Selectphicalc1' incorporates:
     *  CombinatorialLogic: '<S53>/Logic'
     *  Constant: '<S11>/Constant2'
     *  Constant: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
     */
    if ((int32_T)FOC_ENABLE_Overcurrent_I_uvw == 0) {
      rtb_LogicalOperator2 = rtP.Constant2_Value_o;
    } else {
      rtb_LogicalOperator2 = rtP.Logic_table_k[rowIdx + 8U];
    }

    /* End of MultiPortSwitch: '<S11>/Selectphicalc1' */

    /* Switch: '<S2>/Switch' incorporates:
     *  Constant: '<S2>/Enable'
     *  Logic: '<S12>/Logical Operator'
     *  Logic: '<S2>/Logical Operator'
     */
    if (rtb_Logic_idx_1 && rtb_Logic_e_idx_1 && (FOC_Enable != 0.0) &&
        rtb_LogicalOperator2) {
      /* Switch: '<S2>/Switch' incorporates:
       *  Constant: '<S2>/FOC_Mode'
       */
      FOC_Mode_after_checks = FOC_Mode;
    } else {
      /* Switch: '<S2>/Switch' incorporates:
       *  Constant: '<S2>/Constant'
       */
      FOC_Mode_after_checks = rtP.Constant_Value_g;
    }

    /* End of Switch: '<S2>/Switch' */

    /* Gain: '<S15>/f_2_w_el' incorporates:
     *  Constant: '<S15>/Uf_w_el'
     */
    f_2_w_el = rtP.f_2_w_el_Gain * FOC_Uf_f_el;

    /* Product: '<S66>/Product' incorporates:
     *  Constant: '<S66>/FOC_T_fast'
     */
    rtb_Product = 1.0 / FOC_f_fastCTRL * f_2_w_el;

    /* Sum: '<S66>/Add' incorporates:
     *  UnitDelay: '<S66>/Unit Delay'
     */
    rtb_Add = rtb_Product + rtDW.UnitDelay_DSTATE;

    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Constant: '<S7>/Constant'
     */
    rtb_Compare = (uint8_T)(FOC_Mode_after_checks == rtP.CompareToConstant_const);

    /* Gain: '<S30>/TrafoMatrix uvw->alphabeta' */
    for (rowIdx = 0; rowIdx < 2; rowIdx++) {
      rtb_TrafoMatrixuvwalphabeta[rowIdx] =
        (rtP.TrafoMatrixuvwalphabeta_Gain[rowIdx + 2] *
         rtb_SelectVoltCalc_1_idx_1 + rtP.TrafoMatrixuvwalphabeta_Gain[rowIdx] *
         rtb_SelectVoltCalc_1_idx_0) + rtP.TrafoMatrixuvwalphabeta_Gain[rowIdx +
        4] * rtb_SelectVoltCalc_1_idx_2;
    }

    /* End of Gain: '<S30>/TrafoMatrix uvw->alphabeta' */

    /* MinMax: '<S46>/MinMax' incorporates:
     *  Constant: '<S46>/Constant2'
     *  UnitDelay: '<S46>/Unit Delay'
     */
    rtb_MinMax = fmin(rtP.Constant2_Value_l, rtDW.UnitDelay_DSTATE_g);

    /* MinMax: '<S49>/MinMax' incorporates:
     *  Constant: '<S49>/Constant2'
     *  UnitDelay: '<S49>/Unit Delay'
     */
    rtb_MinMax_l = fmin(rtP.Constant2_Value_e, rtDW.UnitDelay_DSTATE_e);

    /* Product: '<S43>/Product1' incorporates:
     *  Constant: '<S10>/w_el_Ref'
     */
    rtb_Abs_i = rtb_MinMax_l * FOC_IfStarter_w_el_Ref;

    /* RelationalOperator: '<S43>/Relational Operator' incorporates:
     *  Constant: '<S10>/w_el_Ref'
     */
    rtb_LogicalOperator2 = (rtb_Abs_i >= FOC_IfStarter_w_el_Ref);

    /* Outport: '<Root>/w_el' incorporates:
     *  Gain: '<S23>/Gain5'
     *  UnitDelay: '<S27>/Unit Delay1'
     */
    rtY.w_el_j = Factor_OmegaRot * rtDW.UnitDelay1_DSTATE;

    /* Logic: '<S10>/Logical Operator4' incorporates:
     *  Constant: '<S10>/w_min_off'
     *  Outport: '<Root>/w_el'
     *  RelationalOperator: '<S10>/w_below_lower_limit'
     */
    rtb_LogicalOperator4 = (rtb_LogicalOperator2 && (rtY.w_el_j <=
      FOC_IfStarter_w_min_off));

    /* RelationalOperator: '<S8>/Compare' incorporates:
     *  Constant: '<S8>/Constant'
     *  Inport: '<Root>/n_Ref'
     */
    rtb_Compare_g = (rtU.n_Ref_i > rtP.Constant_Value_j);

    /* Logic: '<S2>/Logical Operator1' incorporates:
     *  Constant: '<S2>/FOC_IfStarter_Trigger'
     */
    rtb_Logic_idx_1 = ((FOC_IfStarter_Trigger != 0.0) && rtb_Compare_g);

    /* RelationalOperator: '<S44>/Relational Operator2' incorporates:
     *  UnitDelay: '<S44>/Unit Delay'
     */
    rtb_LogicalOperator5 = ((int32_T)rtb_Logic_idx_1 < (int32_T)
      rtDW.UnitDelay_DSTATE_k);

    /* CombinatorialLogic: '<S39>/Logic' incorporates:
     *  Constant: '<S50>/Constant'
     *  Logic: '<S10>/Logical Operator3'
     *  Memory: '<S39>/Memory'
     *  RelationalOperator: '<S50>/Compare'
     */
    rtb_Logic_e_idx_1 = rtP.Logic_table_kz[((((uint32_T)(rtb_MinMax >=
      rtP.CompareToConstant_const_e) << 1) + (rtb_LogicalOperator4 ||
      rtb_LogicalOperator5)) << 1) + rtDW.Memory_PreviousInput_j];

    /* Logic: '<S10>/Logical Operator1' incorporates:
     *  Constant: '<S10>/Enable_If_Starter'
     *  Logic: '<S10>/Logical Operator6'
     */
    rtb_Compare_l = ((!(FOC_ENABLE_IfStarter != 0.0)) || rtb_Logic_e_idx_1);

    /* Sum: '<S4>/Sum1' incorporates:
     *  Constant: '<S4>/FOC_AngleEst_Lq'
     *  Product: '<S4>/Product3'
     *  UnitDelay: '<S21>/Unit Delay'
     */
    rtb_psi_PM_alphabeta_idx_0 = rtDW.UnitDelay_DSTATE_b[0] - FOC_AngleEst_Lq *
      rtb_TrafoMatrixuvwalphabeta[0];
    rtb_psi_PM_alphabeta_idx_1 = rtDW.UnitDelay_DSTATE_b[1] - FOC_AngleEst_Lq *
      rtb_TrafoMatrixuvwalphabeta[1];

    /* Trigonometry: '<S17>/Trigonometric Function' */
    rtb_TrigonometricFunction = rt_atan2d_snf(rtb_psi_PM_alphabeta_idx_1,
      rtb_psi_PM_alphabeta_idx_0);

    /* Switch: '<S17>/Switch_Phi' incorporates:
     *  Constant: '<S17>/Constant'
     *  Sum: '<S17>/Sum1'
     */
    if (!(rtb_TrigonometricFunction > rtP.Switch_Phi_Threshold)) {
      rtb_TrigonometricFunction += rtP.Constant_Value_k;
    }

    /* End of Switch: '<S17>/Switch_Phi' */

    /* DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn' incorporates:
     *  Constant: '<S19>/FOC_f_fastCTRL'
     *  Product: '<S19>/Product'
     */
    DiscreteTransferFcn_tmp = (rtb_TrigonometricFunction * FOC_f_fastCTRL -
      rtP.DiscreteTransferFcn_DenCoef_c[1] * rtDW.DiscreteTransferFcn_states_e) /
      rtP.DiscreteTransferFcn_DenCoef_c[0];
    rtb_Switch_speed = rtP.DiscreteTransferFcn_NumCoef_o[0] *
      DiscreteTransferFcn_tmp + rtP.DiscreteTransferFcn_NumCoef_o[1] *
      rtDW.DiscreteTransferFcn_states_e;

    /* Switch: '<S19>/Switch1' incorporates:
     *  Bias: '<S19>/Bias'
     *  Constant: '<S19>/Constant2'
     *  RelationalOperator: '<S19>/Relational Operator2'
     */
    if (rtb_TrigonometricFunction < rtP.Constant2_Value_k) {
      rtb_Product_m = rtb_TrigonometricFunction;
    } else {
      rtb_Product_m = rtb_TrigonometricFunction + rtP.Bias_Bias;
    }

    /* End of Switch: '<S19>/Switch1' */

    /* DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn1' incorporates:
     *  Constant: '<S19>/FOC_f_fastCTRL1'
     *  Product: '<S19>/Product1'
     */
    rtb_Product_m = (rtb_Product_m * FOC_f_fastCTRL -
                     rtP.DiscreteTransferFcn1_DenCoef[1] *
                     rtDW.DiscreteTransferFcn1_states) /
      rtP.DiscreteTransferFcn1_DenCoef[0];

    /* Switch: '<S19>/Switch_speed' incorporates:
     *  Constant: '<S19>/Constant'
     *  Constant: '<S19>/Constant1'
     *  DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn1'
     *  Logic: '<S19>/Logical Operator'
     *  RelationalOperator: '<S19>/Relational Operator'
     *  RelationalOperator: '<S19>/Relational Operator1'
     */
    if ((!(rtb_TrigonometricFunction < rtP.Constant_Value_lr)) ||
        (!(rtb_TrigonometricFunction > rtP.Constant1_Value_jc))) {
      rtb_Switch_speed = rtP.DiscreteTransferFcn1_NumCoef[0] * rtb_Product_m +
        rtP.DiscreteTransferFcn1_NumCoef[1] * rtDW.DiscreteTransferFcn1_states;
    }

    /* End of Switch: '<S19>/Switch_speed' */

    /* Switch: '<S4>/Switch2' incorporates:
     *  Constant: '<S4>/useFilteredCorrection'
     *  UnitDelay: '<S18>/Unit Delay'
     */
    if (FOC_SELECT_AngleEst_w_el_filtered > rtP.Switch2_Threshold_p) {
      rtb_Sum1_f = rtDW.UnitDelay_DSTATE_m;
    } else {
      rtb_Sum1_f = rtb_Switch_speed;
    }

    /* End of Switch: '<S4>/Switch2' */

    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S4>/Constant1'
     *  Constant: '<S4>/Constant2'
     */
    if (rtb_Sum1_f > rtP.Switch_Threshold_c) {
      rtb_Switch2_e = rtP.Constant1_Value_n;
    } else {
      rtb_Switch2_e = rtP.Constant2_Value_a;
    }

    /* End of Switch: '<S4>/Switch' */

    /* Sum: '<S4>/Sum2' incorporates:
     *  Abs: '<S4>/Abs'
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/komp_kp'
     *  Product: '<S4>/Product'
     *  Product: '<S4>/Product1'
     *  Sum: '<S4>/Sum3'
     *  Trigonometry: '<S4>/Trigonometric Function'
     */
    rtb_Gain4 = rtb_TrigonometricFunction - (rtP.Constant_Value_mh - atan(1.0 /
      FOC_AngleEst_Komp_KP * fabs(rtb_Sum1_f))) * rtb_Switch2_e;

    /* Switch: '<S16>/Switch2' incorporates:
     *  Constant: '<S16>/Constant'
     *  Constant: '<S16>/Constant1'
     */
    if (rtb_Gain4 >= rtP.Switch2_Threshold_f) {
      rtb_TrigonometricFunction = rtP.Constant1_Value;
    } else {
      rtb_TrigonometricFunction = rtP.Constant_Value;
    }

    /* End of Switch: '<S16>/Switch2' */

    /* Switch: '<S16>/Switch1' incorporates:
     *  Constant: '<S16>/Constant2'
     *  Constant: '<S16>/Constant3'
     */
    if (rtb_Gain4 >= rtP.Switch1_Threshold_o) {
      rtb_Sum1_f = rtP.Constant2_Value;
    } else {
      rtb_Sum1_f = rtP.Constant3_Value;
    }

    /* End of Switch: '<S16>/Switch1' */

    /* Sum: '<S16>/Sum1' */
    rtb_Sum1_f += rtb_TrigonometricFunction + rtb_Gain4;

    /* Saturate: '<S5>/ResolverOffsetLimitation' */
    if (FOC_phi_offset > rtP.ResolverOffsetLimitation_UpperS) {
      rtb_TrigonometricFunction = rtP.ResolverOffsetLimitation_UpperS;
    } else if (FOC_phi_offset < rtP.ResolverOffsetLimitation_LowerS) {
      rtb_TrigonometricFunction = rtP.ResolverOffsetLimitation_LowerS;
    } else {
      rtb_TrigonometricFunction = FOC_phi_offset;
    }

    /* End of Saturate: '<S5>/ResolverOffsetLimitation' */

    /* Sum: '<S5>/Sum1' */
    rtb_Product1 = rtb_TrigonometricFunction + rtb_Sum1_f;

    /* Sum: '<S23>/Sum3' incorporates:
     *  Gain: '<S23>/DeadTimeCompensation'
     *  UnitDelay: '<S27>/Unit Delay1'
     */
    rtb_TrigonometricFunction = FOC_PhiSensorTdead * rtDW.UnitDelay1_DSTATE +
      rtb_Product1;

    /* Sum: '<S26>/Sum' incorporates:
     *  UnitDelay: '<S26>/Unit Delay'
     */
    rtb_Switch2_e = rtb_TrigonometricFunction - rtDW.UnitDelay_DSTATE_a;

    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S26>/Constant2'
     *  Constant: '<S26>/Constant3'
     *  Constant: '<S26>/Constant4'
     *  RelationalOperator: '<S26>/Sprung?'
     */
    if (rtb_Switch2_e < rtP.Constant3_Value_d) {
      rtb_antiWindupProd_idx_0 = rtP.Constant2_Value_b;
    } else {
      rtb_antiWindupProd_idx_0 = rtP.Constant4_Value;
    }

    /* End of Switch: '<S26>/Switch' */

    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant1'
     *  Constant: '<S26>/Constant5'
     *  Constant: '<S26>/Constant6'
     *  RelationalOperator: '<S26>/Sprung?1'
     */
    if (rtb_Switch2_e > rtP.Constant1_Value_k) {
      rtb_Switch2_e = rtP.Constant5_Value;
    } else {
      rtb_Switch2_e = rtP.Constant6_Value;
    }

    /* End of Switch: '<S26>/Switch1' */

    /* Sum: '<S23>/Sum7' incorporates:
     *  Sum: '<S26>/Sum2'
     *  UnitDelay: '<S23>/Unit Delay3'
     */
    Phi_Observer = rtDW.UnitDelay3_DSTATE - (rtb_antiWindupProd_idx_0 +
      rtb_Switch2_e);

    /* MultiPortSwitch: '<S5>/Selectphicalc2' incorporates:
     *  Constant: '<S5>/Constant3'
     */
    if ((int32_T)FOC_SELECT_phi != 1) {
      rtb_Product1 = Phi_Observer;
    }

    /* End of MultiPortSwitch: '<S5>/Selectphicalc2' */

    /* Switch: '<S24>/Switch1' incorporates:
     *  Constant: '<S24>/Constant'
     *  Sum: '<S24>/Sum2'
     */
    if (rtb_Product1 > rtP.Switch1_Threshold_n) {
      rtb_Product1 -= rtP.Constant_Value_c;
    }

    /* End of Switch: '<S24>/Switch1' */

    /* Switch: '<S24>/Switch2' incorporates:
     *  Constant: '<S24>/Constant1'
     *  Sum: '<S24>/Sum3'
     */
    if (rtb_Product1 > rtP.Switch2_Threshold_a) {
      rtb_Switch2_e = rtb_Product1;
    } else {
      rtb_Switch2_e = rtb_Product1 + rtP.Constant1_Value_d;
    }

    /* End of Switch: '<S24>/Switch2' */

    /* Product: '<S45>/Product' incorporates:
     *  Constant: '<S45>/FOC_T_fast'
     */
    rtb_Product_i = 1.0 / FOC_f_fastCTRL * rtb_Abs_i;

    /* Sum: '<S45>/Add' incorporates:
     *  UnitDelay: '<S45>/Unit Delay'
     */
    rtb_Add_h = rtb_Product_i + rtDW.UnitDelay_DSTATE_p;

    /* Switch: '<S10>/phi_I_Trafo_Switch' */
    if (rtb_Compare_l) {
      rtb_Gain4 = rtb_Switch2_e;
    } else {
      rtb_Gain4 = rtb_Add_h;
    }

    /* End of Switch: '<S10>/phi_I_Trafo_Switch' */

    /* Trigonometry: '<S30>/Trigonometric Function1' */
    rtb_Product1 = cos(rtb_Gain4);

    /* Trigonometry: '<S30>/Trigonometric Function' */
    rtb_Gain4 = sin(rtb_Gain4);

    /* Sum: '<S30>/TrafoSum' incorporates:
     *  Product: '<S30>/TrafoProd'
     *  Product: '<S30>/TrafoProd3'
     */
    rtDW.TrafoSum = rtb_TrafoMatrixuvwalphabeta[0] * rtb_Product1 + rtb_Gain4 *
      rtb_TrafoMatrixuvwalphabeta[1];

    /* Sum: '<S30>/TrafoSum1' incorporates:
     *  Product: '<S30>/TrafoProd1'
     *  Product: '<S30>/TrafoProd2'
     */
    rtDW.TrafoSum1 = rtb_Product1 * rtb_TrafoMatrixuvwalphabeta[1] -
      rtb_TrafoMatrixuvwalphabeta[0] * rtb_Gain4;

    /* MinMax: '<S48>/MinMax' incorporates:
     *  Constant: '<S48>/Constant2'
     *  UnitDelay: '<S48>/Unit Delay'
     */
    rtb_MinMax_c = fmin(rtP.Constant2_Value_bl, rtDW.UnitDelay_DSTATE_gl);

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S10>/I_d_Ref'
     */
    rtb_Product1 = rtb_MinMax_c * FOC_IfStarter_Id_Ref;

    /* MultiPortSwitch: '<S2>/Speed_Ctrl_Start_Sequence' incorporates:
     *  Constant: '<S2>/0: on // 1: off'
     *  Constant: '<S2>/OmegaRot1'
     *  Logic: '<S2>/Logical Operator3'
     */
    if ((int32_T)SPEED_CTRL_SELECT_IfStarter == 0) {
      rtb_Speed_Ctrl_Start_Sequence = FOC_SELECT_speed_control;
    } else {
      rtb_Speed_Ctrl_Start_Sequence = ((FOC_SELECT_speed_control != 0.0) &&
        rtb_Logic_e_idx_1 && rtb_Compare_g);
    }

    /* End of MultiPortSwitch: '<S2>/Speed_Ctrl_Start_Sequence' */

    /* Outputs for Atomic SubSystem: '<S2>/SPEED_CONTROLLER' */
    /* MultiPortSwitch: '<S14>/TorqLimitSource' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Constant: '<S14>/Constant2'
     *  Constant: '<S14>/Constant4'
     *  Constant: '<S14>/Constant5'
     *  Constant: '<S14>/OmegaRot3'
     *  Constant: '<S14>/RMS Torque constant'
     *  Gain: '<S14>/Gain2'
     *  Product: '<S14>/Product3'
     *  Product: '<S14>/Product4'
     */
    if ((int32_T)SPEED_CTRL_SELECT_TorqLimit == 0) {
      rtb_TorqLimitSource_idx_0 = SPEED_CTRL_IQ_MAX;
      rtb_TorqLimitSource_idx_1 = SPEED_CTRL_IQ_MIN;
    } else {
      rtb_TorqLimitSource_idx_0 = SPEED_CTRL_TORQLIMPOS /
        rtP.RMSTorqueconstant_Value * rtP.Gain2_Gain_b;
      rtb_TorqLimitSource_idx_1 = SPEED_CTRL_TORQLIMNEG /
        rtP.RMSTorqueconstant_Value * rtP.Gain2_Gain_b;
    }

    /* End of MultiPortSwitch: '<S14>/TorqLimitSource' */

    /* Saturate: '<S14>/limit T1' */
    if (rtb_TorqLimitSource_idx_0 > FOC_LIMIT_I_PHASE_PEAK_MAX) {
      rtb_Subtract2_p = FOC_LIMIT_I_PHASE_PEAK_MAX;
    } else if (rtb_TorqLimitSource_idx_0 < rtP.limitT1_LowerSat) {
      rtb_Subtract2_p = rtP.limitT1_LowerSat;
    } else {
      rtb_Subtract2_p = rtb_TorqLimitSource_idx_0;
    }

    /* End of Saturate: '<S14>/limit T1' */

    /* MultiPortSwitch: '<S14>/n_Ref_Source' incorporates:
     *  Constant: '<S14>/OmegaRot1'
     *  Constant: '<S14>/OmegaRot2'
     *  Inport: '<Root>/n_Ref'
     */
    if ((int32_T)SPEED_CTRL_SELECT_n_Ref == 0) {
      rtb_Gain4 = SPEED_CTRL_MANUAL_n_RPM;
    } else {
      rtb_Gain4 = rtU.n_Ref_i;
    }

    /* End of MultiPortSwitch: '<S14>/n_Ref_Source' */

    /* Saturate: '<S14>/limit T2' */
    if (rtb_Gain4 > SPEED_CTRL_LIMIT_n_Ref_MAX) {
      rtb_Gain4 = SPEED_CTRL_LIMIT_n_Ref_MAX;
    } else if (rtb_Gain4 < SPEED_CTRL_LIMIT_n_Ref_MIN) {
      rtb_Gain4 = SPEED_CTRL_LIMIT_n_Ref_MIN;
    }

    /* End of Saturate: '<S14>/limit T2' */

    /* Product: '<S64>/delta rise limit' incorporates:
     *  Constant: '<S61>/Constant6'
     *  Constant: '<S64>/FOC_T_fast'
     */
    rtb_DiscreteFIRFilter20thorder = 1.0 / FOC_f_fastCTRL *
      FOC_LIMIT_n_Ref_SlewRate_Up;

    /* Sum: '<S64>/Difference Inputs1' incorporates:
     *  UnitDelay: '<S64>/Delay Input2'
     *
     * Block description for '<S64>/Difference Inputs1':
     *
     *  Add in CPU
     *
     * Block description for '<S64>/Delay Input2':
     *
     *  Store in Global RAM
     */
    rtb_UkYk1 = rtb_Gain4 - rtDW.DelayInput2_DSTATE;

    /* Switch: '<S65>/Switch2' incorporates:
     *  RelationalOperator: '<S65>/LowerRelop1'
     */
    if (!(rtb_UkYk1 > rtb_DiscreteFIRFilter20thorder)) {
      /* Product: '<S64>/delta fall limit' incorporates:
       *  Constant: '<S61>/Constant7'
       *  Constant: '<S64>/FOC_T_fast'
       */
      rtb_DiscreteFIRFilter20thorder = 1.0 / FOC_f_fastCTRL *
        FOC_LIMIT_n_Ref_SlewRate_Down;

      /* Switch: '<S65>/Switch' incorporates:
       *  RelationalOperator: '<S65>/UpperRelop'
       */
      if (!(rtb_UkYk1 < rtb_DiscreteFIRFilter20thorder)) {
        rtb_DiscreteFIRFilter20thorder = rtb_UkYk1;
      }

      /* End of Switch: '<S65>/Switch' */
    }

    /* End of Switch: '<S65>/Switch2' */

    /* Sum: '<S64>/Difference Inputs2' incorporates:
     *  UnitDelay: '<S64>/Delay Input2'
     *
     * Block description for '<S64>/Difference Inputs2':
     *
     *  Add in CPU
     *
     * Block description for '<S64>/Delay Input2':
     *
     *  Store in Global RAM
     */
    rtb_UkYk1 = rtb_DiscreteFIRFilter20thorder + rtDW.DelayInput2_DSTATE;

    /* Switch: '<S61>/Switch2' incorporates:
     *  Constant: '<S61>/Constant5'
     */
    if (FOC_SELECT_n_Ref_Ramp > rtP.Switch2_Threshold_c) {
      /* Switch: '<S61>/Switch2' */
      n_Ref = rtb_UkYk1;
    } else {
      /* Switch: '<S61>/Switch2' */
      n_Ref = rtb_Gain4;
    }

    /* End of Switch: '<S61>/Switch2' */

    /* Sum: '<S14>/Add' incorporates:
     *  Gain: '<S14>/RPM => w_el'
     *  Outport: '<Root>/w_el'
     */
    SPEED_CTRL_w_el_err = 6.2831853071795862 * FOC_z_P / 60.0 * n_Ref -
      rtY.w_el_j;

    /* Gain: '<S14>/RPM => w_el1' incorporates:
     *  Outport: '<Root>/w_el'
     */
    n_Act = 60.0 / (6.2831853071795862 * FOC_z_P) * rtY.w_el_j;

    /* MultiPortSwitch: '<S14>/Multiport Switch1' incorporates:
     *  Constant: '<S14>/Constant14'
     *  Constant: '<S14>/Constant15'
     */
    if ((int32_T)SELECT_SPEED_CTRL_V_R == 1) {
      rtb_DiscreteFIRFilter20thorder = SPEED_CTRL_V_R;
    } else {
      /* Lookup_n-D: '<S14>/V_R_Scheduling' incorporates:
       *  Gain: '<S14>/RPM => w_el1'
       */
      rtb_DiscreteFIRFilter20thorder = look1_pbinlca(n_Act,
        rtP.V_R_Scheduling_bp01Data, rtP.V_R_Scheduling_tableData,
        &rtDW.m_bpIndex, 4U);
    }

    /* End of MultiPortSwitch: '<S14>/Multiport Switch1' */

    /* Product: '<S14>/Product6' */
    rtb_DiscreteFIRFilter20thorder *= SPEED_CTRL_w_el_err;

    /* Sum: '<S14>/Add2' incorporates:
     *  UnitDelay: '<S14>/Unit Delay'
     */
    rtb_Gain4 = rtb_DiscreteFIRFilter20thorder + rtDW.UnitDelay_DSTATE_pj;

    /* Switch: '<S62>/Switch2' incorporates:
     *  RelationalOperator: '<S62>/LowerRelop1'
     */
    if (!(rtb_Gain4 > rtb_Subtract2_p)) {
      /* Saturate: '<S14>/limit T3' */
      if (rtb_TorqLimitSource_idx_1 > rtP.limitT3_UpperSat) {
        rtb_Subtract2_p = rtP.limitT3_UpperSat;
      } else if (rtb_TorqLimitSource_idx_1 < -FOC_LIMIT_I_PHASE_PEAK_MAX) {
        rtb_Subtract2_p = -FOC_LIMIT_I_PHASE_PEAK_MAX;
      } else {
        rtb_Subtract2_p = rtb_TorqLimitSource_idx_1;
      }

      /* End of Saturate: '<S14>/limit T3' */

      /* Switch: '<S62>/Switch' incorporates:
       *  RelationalOperator: '<S62>/UpperRelop'
       */
      if (!(rtb_Gain4 < rtb_Subtract2_p)) {
        rtb_Subtract2_p = rtb_Gain4;
      }

      /* End of Switch: '<S62>/Switch' */
    }

    /* End of Switch: '<S62>/Switch2' */

    /* Switch: '<S14>/Switch1' incorporates:
     *  Constant: '<S14>/IdqRefZero'
     */
    if (rtb_Speed_Ctrl_Start_Sequence > rtP.Switch1_Threshold) {
      /* MultiPortSwitch: '<S14>/Multiport Switch' incorporates:
       *  Constant: '<S14>/Constant12'
       *  Constant: '<S14>/Constant6'
       *  Constant: '<S14>/IdRefZero1'
       */
      switch ((int32_T)FOC_SELECT_Id_Ref_constFW) {
       case 1:
        rtb_MultiportSwitch = FOC_MANUAL_Id_Ref_SPEED_CTRL;
        break;

       case 2:
        /* Switch: '<S14>/Switch' incorporates:
         *  Constant: '<S14>/Constant10'
         *  Constant: '<S14>/Constant11'
         *  Constant: '<S14>/Constant7'
         *  Product: '<S14>/Product2'
         *  Sum: '<S14>/Sum1'
         */
        if (n_Act > rtP.Switch_Threshold) {
          rtb_MultiportSwitch = FOC_Id_Ref_constFW_factor * n_Act +
            FOC_Id_Ref_constFW_offset;
        } else {
          rtb_MultiportSwitch = rtP.Constant7_Value;
        }

        /* End of Switch: '<S14>/Switch' */
        break;

       case 3:
        /* Switch: '<S14>/Switch2' incorporates:
         *  Constant: '<S14>/Constant13'
         *  Constant: '<S14>/calc_TorqueRef'
         *  Gain: '<S14>/Gain3'
         *  Gain: '<S14>/RPM => w_el1'
         *  Lookup_n-D: '<S14>/Id_Mn_LUT'
         *  Product: '<S14>/Product1'
         */
        if (n_Act > rtP.Switch2_Threshold) {
          rtb_MultiportSwitch = look2_binlx(rtP.Gain3_Gain_f * rtb_Subtract2_p *
            rtP.calc_TorqueRef_Value, n_Act, rtP.Id_Mn_LUT_bp01Data,
            rtP.Id_Mn_LUT_bp02Data, rtP.Id_Mn_LUT_tableData,
            rtP.Id_Mn_LUT_maxIndex, 20U);
        } else {
          rtb_MultiportSwitch = rtP.Constant13_Value;
        }

        /* End of Switch: '<S14>/Switch2' */
        break;

       default:
        rtb_MultiportSwitch = rtP.IdRefZero1_Value;
        break;
      }

      /* End of MultiPortSwitch: '<S14>/Multiport Switch' */

      /* Switch: '<S63>/Switch2' incorporates:
       *  Constant: '<S14>/Constant8'
       *  Constant: '<S14>/Constant9'
       *  RelationalOperator: '<S63>/LowerRelop1'
       *  RelationalOperator: '<S63>/UpperRelop'
       *  Switch: '<S63>/Switch'
       */
      if (rtb_MultiportSwitch > FOC_LIMIT_MAX_Id_Ref_constFW) {
        rtb_MultiportSwitch = FOC_LIMIT_MAX_Id_Ref_constFW;
      } else if (rtb_MultiportSwitch < FOC_LIMIT_MIN_Id_Ref_constFW) {
        /* Switch: '<S63>/Switch' incorporates:
         *  Constant: '<S14>/Constant9'
         */
        rtb_MultiportSwitch = FOC_LIMIT_MIN_Id_Ref_constFW;
      }

      /* End of Switch: '<S63>/Switch2' */
      rtb_TorqLimitSource_idx_0 = rtb_MultiportSwitch;
      rtb_TorqLimitSource_idx_1 = rtb_Subtract2_p;
    } else {
      rtb_TorqLimitSource_idx_0 = rtP.IdqRefZero_Value[0];
      rtb_TorqLimitSource_idx_1 = rtP.IdqRefZero_Value[1];
    }

    /* End of Switch: '<S14>/Switch1' */

    /* Gain: '<S14>/dummy_gain5' */
    SPEED_CTRL_Iq_Ref = rtP.dummy_gain5_Gain * rtb_Subtract2_p;

    /* Gain: '<S14>/dummy_gain1' incorporates:
     *  UnitDelay: '<S14>/Unit Delay'
     */
    SPEED_CTRL_Integ = rtP.dummy_gain1_Gain * rtDW.UnitDelay_DSTATE_pj;

    /* Gain: '<S14>/dummy_gain3' */
    SPEED_CTRL_Prop = rtP.dummy_gain3_Gain * rtb_DiscreteFIRFilter20thorder;

    /* Gain: '<S14>/dummy_gain2' */
    SPEED_CTRL_enable = rtP.dummy_gain2_Gain * rtb_Speed_Ctrl_Start_Sequence;

    /* Update for UnitDelay: '<S64>/Delay Input2'
     *
     * Block description for '<S64>/Delay Input2':
     *
     *  Store in Global RAM
     */
    rtDW.DelayInput2_DSTATE = rtb_UkYk1;

    /* Update for UnitDelay: '<S14>/Unit Delay' incorporates:
     *  Constant: '<S14>/Constant'
     *  Constant: '<S14>/Constant3'
     *  Constant: '<S14>/FOC_T_fast'
     *  Gain: '<S14>/Gain1'
     *  MinMax: '<S14>/avoid_div_by_0'
     *  Product: '<S14>/Divide'
     *  Product: '<S14>/Product'
     *  Product: '<S14>/Product5'
     *  Sum: '<S14>/Add1'
     *  Sum: '<S14>/Subtract'
     *  Sum: '<S14>/Sum'
     */
    rtDW.UnitDelay_DSTATE_pj = (((rtb_Subtract2_p - rtb_Gain4) *
      SPEED_CTRL_K_AWU + rtb_DiscreteFIRFilter20thorder) * (1.0 / FOC_f_fastCTRL)
      / fmax(rtP.Constant3_Value_i, SPEED_CTRL_T_N) + rtDW.UnitDelay_DSTATE_pj) *
      rtb_Speed_Ctrl_Start_Sequence;

    /* End of Outputs for SubSystem: '<S2>/SPEED_CONTROLLER' */

    /* Switch: '<S10>/Idq_Ref_Switch' incorporates:
     *  Constant: '<S42>/Constant'
     */
    if (rtb_Compare_l) {
      /* MultiPortSwitch: '<S2>/Idq_Ref_Switch' incorporates:
       *  Constant: '<S2>/0: on // 1: off'
       *  Inport: '<Root>/Idq_Ref'
       */
      if ((int32_T)FOC_SELECT_speed_control == 0) {
        rtb_TorqLimitSource_idx_0 = rtU.Idq_Ref;
        rtb_TorqLimitSource_idx_1 = rtU.Idq_Ref;
      }

      /* End of MultiPortSwitch: '<S2>/Idq_Ref_Switch' */
    } else {
      rtb_TorqLimitSource_idx_0 = rtb_Product1;
      rtb_TorqLimitSource_idx_1 = rtP.Constant_Value_m;
    }

    /* End of Switch: '<S10>/Idq_Ref_Switch' */

    /* Sum: '<S29>/IdqErr' */
    rtb_antiWindupProd_idx_0 = rtb_TorqLimitSource_idx_0 - rtDW.TrafoSum;
    rtb_antiWindupProd_idx_1 = rtb_TorqLimitSource_idx_1 - rtDW.TrafoSum1;

    /* Product: '<S32>/KP*e[k]1' incorporates:
     *  Constant: '<S32>/FOC_KP1'
     */
    rtb_KPek1_idx_0 = rtb_antiWindupProd_idx_0 * FOC_KP;
    rtb_KPek1_idx_1 = rtb_antiWindupProd_idx_1 * FOC_KP;

    /* Product: '<S32>/Product1' incorporates:
     *  Constant: '<S32>/FOC_KI'
     *  Constant: '<S32>/FOC_T_fast'
     */
    rtb_Speed_Ctrl_Start_Sequence = 1.0 / FOC_f_fastCTRL * FOC_KI;

    /* Sum: '<S5>/Sum' incorporates:
     *  Gain: '<S5>/Gain'
     *  Outport: '<Root>/w_el'
     */
    rtb_UkYk1 = FOC_T_fast * FOC_output_trafo_delay * rtY.w_el_j + rtb_Switch2_e;

    /* Switch: '<S25>/Switch1' incorporates:
     *  Constant: '<S25>/Constant'
     *  Sum: '<S25>/Sum2'
     */
    if (rtb_UkYk1 > rtP.Switch1_Threshold_ep) {
      rtb_UkYk1 -= rtP.Constant_Value_l;
    }

    /* End of Switch: '<S25>/Switch1' */

    /* Switch: '<S25>/Switch2' incorporates:
     *  Constant: '<S25>/Constant1'
     *  Sum: '<S25>/Sum3'
     */
    if (!(rtb_UkYk1 > rtP.Switch2_Threshold_h)) {
      rtb_UkYk1 += rtP.Constant1_Value_m;
    }

    /* End of Switch: '<S25>/Switch2' */

    /* MultiPortSwitch: '<S2>/SelectControlMode' incorporates:
     *  Constant: '<S15>/Uf_Ud'
     *  Constant: '<S2>/Null'
     *  Product: '<S67>/Product'
     */
    switch ((int32_T)FOC_Mode_after_checks) {
     case 1:
      rtb_DiscreteFIRFilter20thorder = rtP.Null_Value[0];
      rtb_Gain4 = rtP.Null_Value[1];
      rtb_MultiportSwitch = rtP.Null_Value[2];
      break;

     case 2:
      /* Gain: '<S67>/Gain' incorporates:
       *  DiscreteTransferFcn: '<S15>/Discrete Transfer Fcn'
       */
      rtb_phi_U_Trafo_Switch = rtP.DiscreteTransferFcn_NumCoef *
        rtDW.DiscreteTransferFcn_states * FOC_Uf_m;
      rtb_DiscreteFIRFilter20thorder = FOC_Uf_Ud;

      /* Abs: '<S67>/Abs' incorporates:
       *  Constant: '<S15>/Uf_Ud'
       */
      rtb_Product_b = fabs(rtb_phi_U_Trafo_Switch);

      /* Saturate: '<S67>/Saturation1' */
      if (rtb_Product_b > FOC_Uf_U_max) {
        rtb_Product_b = FOC_Uf_U_max;
      } else if (rtb_Product_b < FOC_Uf_U_min) {
        rtb_Product_b = FOC_Uf_U_min;
      }

      /* End of Saturate: '<S67>/Saturation1' */

      /* Signum: '<S67>/Sign' */
      if (!rtIsNaN(rtb_phi_U_Trafo_Switch)) {
        if (rtb_phi_U_Trafo_Switch < 0.0) {
          rtb_phi_U_Trafo_Switch = -1.0;
        } else {
          rtb_phi_U_Trafo_Switch = (rtb_phi_U_Trafo_Switch > 0.0);
        }
      }

      /* End of Signum: '<S67>/Sign' */
      rtb_Gain4 = rtb_Product_b * rtb_phi_U_Trafo_Switch;
      rtb_MultiportSwitch = rtb_Add;
      break;

     default:
      /* Switch: '<S32>/IntegEnaSwitch1' incorporates:
       *  Constant: '<S32>/Zero'
       *  Product: '<S32>/Product2'
       *  Sum: '<S32>/IntSum1'
       *  UnitDelay: '<S32>/IntegDelay1'
       */
      if (rtb_Compare != 0) {
        rtb_DiscreteFIRFilter20thorder = rtDW.IntegDelay1_DSTATE[0] *
          rtb_Speed_Ctrl_Start_Sequence + rtb_KPek1_idx_0;
        rtb_Gain4 = rtDW.IntegDelay1_DSTATE[1] * rtb_Speed_Ctrl_Start_Sequence +
          rtb_KPek1_idx_1;
      } else {
        rtb_DiscreteFIRFilter20thorder = rtP.Zero_Value;
        rtb_Gain4 = rtP.Zero_Value;
      }

      /* End of Switch: '<S32>/IntegEnaSwitch1' */

      /* Switch: '<S10>/phi_U_Trafo_Switch' */
      if (rtb_Compare_l) {
        rtb_MultiportSwitch = rtb_UkYk1;
      } else {
        rtb_MultiportSwitch = rtb_Add_h;
      }

      /* End of Switch: '<S10>/phi_U_Trafo_Switch' */
      break;
    }

    /* End of MultiPortSwitch: '<S2>/SelectControlMode' */

    /* Outputs for Atomic SubSystem: '<S9>/SubS_InversePark_dq_alpha_beta' */
    /* Gain: '<S36>/Gain' */
    u_d = rtP.Gain_Gain * rtb_DiscreteFIRFilter20thorder;

    /* Trigonometry: '<S36>/Trigonometric Function2' */
    rtb_DiscreteFIRFilter20thorder = sin(rtb_MultiportSwitch);

    /* Gain: '<S36>/Gain1' */
    u_q = rtP.Gain1_Gain * rtb_Gain4;

    /* Trigonometry: '<S36>/Trigonometric Function3' */
    rtb_Subtract2_p = cos(rtb_MultiportSwitch);

    /* Sum: '<S36>/Add' incorporates:
     *  Product: '<S36>/Ud_sin'
     *  Product: '<S36>/Uq_cos'
     */
    u_beta = u_d * rtb_DiscreteFIRFilter20thorder + u_q * rtb_Subtract2_p;

    /* Sum: '<S36>/Subtract' incorporates:
     *  Product: '<S36>/Ud_cos'
     *  Product: '<S36>/Uq_sin'
     */
    u_alpha = u_d * rtb_Subtract2_p - u_q * rtb_DiscreteFIRFilter20thorder;

    /* DiscreteFir: '<S36>/Discrete FIR Filter 20th order1' */
    rtb_DiscreteFIRFilter20thorder = u_q * rtP.DiscreteFIRFilter20thorder1_Coe[0];
    rowIdx = 1;
    for (tmp = rtDW.DiscreteFIRFilter20thorder1_c_k; tmp < 19; tmp++) {
      rtb_DiscreteFIRFilter20thorder += rtDW.DiscreteFIRFilter20thorder1_s_g[tmp]
        * rtP.DiscreteFIRFilter20thorder1_Coe[rowIdx];
      rowIdx++;
    }

    for (tmp = 0; tmp < rtDW.DiscreteFIRFilter20thorder1_c_k; tmp++) {
      rtb_DiscreteFIRFilter20thorder += rtDW.DiscreteFIRFilter20thorder1_s_g[tmp]
        * rtP.DiscreteFIRFilter20thorder1_Coe[rowIdx];
      rowIdx++;
    }

    /* End of DiscreteFir: '<S36>/Discrete FIR Filter 20th order1' */

    /* Gain: '<S36>/Gain3' */
    u_q_filt = rtP.Gain3_Gain * rtb_DiscreteFIRFilter20thorder;

    /* DiscreteFir: '<S36>/Discrete FIR Filter 20th order' */
    rtb_DiscreteFIRFilter20thorder = u_d * rtP.DiscreteFIRFilter20thorder_Coef[0];
    rowIdx = 1;
    for (tmp = rtDW.DiscreteFIRFilter20thorder_ci_a; tmp < 19; tmp++) {
      rtb_DiscreteFIRFilter20thorder += rtDW.DiscreteFIRFilter20thorder_st_n[tmp]
        * rtP.DiscreteFIRFilter20thorder_Coef[rowIdx];
      rowIdx++;
    }

    for (tmp = 0; tmp < rtDW.DiscreteFIRFilter20thorder_ci_a; tmp++) {
      rtb_DiscreteFIRFilter20thorder += rtDW.DiscreteFIRFilter20thorder_st_n[tmp]
        * rtP.DiscreteFIRFilter20thorder_Coef[rowIdx];
      rowIdx++;
    }

    /* End of DiscreteFir: '<S36>/Discrete FIR Filter 20th order' */

    /* Gain: '<S36>/Gain2' */
    u_d_filt = rtP.Gain2_Gain * rtb_DiscreteFIRFilter20thorder;

    /* Update for DiscreteFir: '<S36>/Discrete FIR Filter 20th order1' */
    /* Update circular buffer index */
    rtDW.DiscreteFIRFilter20thorder1_c_k--;
    if (rtDW.DiscreteFIRFilter20thorder1_c_k < 0) {
      rtDW.DiscreteFIRFilter20thorder1_c_k = 18;
    }

    /* Update circular buffer */
    rtDW.DiscreteFIRFilter20thorder1_s_g[rtDW.DiscreteFIRFilter20thorder1_c_k] =
      u_q;

    /* End of Update for DiscreteFir: '<S36>/Discrete FIR Filter 20th order1' */

    /* Update for DiscreteFir: '<S36>/Discrete FIR Filter 20th order' */
    /* Update circular buffer index */
    rtDW.DiscreteFIRFilter20thorder_ci_a--;
    if (rtDW.DiscreteFIRFilter20thorder_ci_a < 0) {
      rtDW.DiscreteFIRFilter20thorder_ci_a = 18;
    }

    /* Update circular buffer */
    rtDW.DiscreteFIRFilter20thorder_st_n[rtDW.DiscreteFIRFilter20thorder_ci_a] =
      u_d;

    /* End of Update for DiscreteFir: '<S36>/Discrete FIR Filter 20th order' */
    /* End of Outputs for SubSystem: '<S9>/SubS_InversePark_dq_alpha_beta' */

    /* Gain: '<S38>/Gain1' */
    U_u = rtP.Gain1_Gain_g * u_alpha;

    /* Gain: '<S38>/Gain3' */
    rtb_Subtract2_p = rtP.Gain3_Gain_k * u_alpha;

    /* Gain: '<S38>/Gain4' */
    rtb_Gain4 = rtP.Gain4_Gain * u_beta;

    /* Gain: '<S38>/Gain2' incorporates:
     *  Sum: '<S38>/Add1'
     */
    U_v = (rtb_Subtract2_p + rtb_Gain4) * rtP.Gain2_Gain_m;

    /* Gain: '<S38>/Gain5' incorporates:
     *  Sum: '<S38>/Add2'
     */
    U_w = (rtb_Subtract2_p - rtb_Gain4) * rtP.Gain5_Gain;

    /* Product: '<S9>/Divide3' incorporates:
     *  Constant: '<S9>/U_DC_half'
     *  Constant: '<S9>/avoid_div_by_0'
     *  MinMax: '<S9>/max'
     */
    rtb_phi_U_Trafo_Switch = 1.0 / fmax(FOC_U_DC, rtP.avoid_div_by_0_Value) *
      rtP.U_DC_half_Value;

    /* Switch: '<S9>/Switch' incorporates:
     *  Constant: '<S9>/modulation'
     *  Product: '<S9>/Product'
     *  Sum: '<S37>/Subtract'
     *  Sum: '<S37>/Subtract1'
     *  Sum: '<S37>/Subtract2'
     */
    if (FOC_SELECT_Modulation > rtP.Switch_Threshold_o) {
      /* Outputs for Atomic SubSystem: '<S9>/SubS_Modulation' */
      /* Product: '<S37>/Divide' */
      rtb_DiscreteFIRFilter20thorder = U_u * rtb_phi_U_Trafo_Switch;

      /* Product: '<S37>/Divide1' */
      rtb_Gain4 = U_v * rtb_phi_U_Trafo_Switch;

      /* Product: '<S37>/Divide2' */
      rtb_MultiportSwitch = U_w * rtb_phi_U_Trafo_Switch;

      /* Product: '<S37>/Product' incorporates:
       *  Constant: '<S37>/Constant1'
       *  MinMax: '<S37>/MinMax'
       *  MinMax: '<S37>/MinMax1'
       *  Sum: '<S37>/Add'
       */
      rtb_Product_b = (fmax(fmax(rtb_DiscreteFIRFilter20thorder, rtb_Gain4),
                            rtb_MultiportSwitch) + fmin(fmin
        (rtb_DiscreteFIRFilter20thorder, rtb_Gain4), rtb_MultiportSwitch)) *
        rtP.Constant1_Value_o;
      rtb_DiscreteFIRFilter20thorder -= rtb_Product_b;
      rtb_Gain4 -= rtb_Product_b;
      rtb_MultiportSwitch -= rtb_Product_b;

      /* End of Outputs for SubSystem: '<S9>/SubS_Modulation' */
    } else {
      rtb_DiscreteFIRFilter20thorder = U_u * rtb_phi_U_Trafo_Switch;
      rtb_Gain4 = U_v * rtb_phi_U_Trafo_Switch;
      rtb_MultiportSwitch = U_w * rtb_phi_U_Trafo_Switch;
    }

    /* End of Switch: '<S9>/Switch' */

    /* Saturate: '<S35>/Saturation' incorporates:
     *  Constant: '<S35>/Constant4'
     *  Constant: '<S35>/Constant5'
     *  Product: '<S35>/Divide2'
     *  Sum: '<S35>/Add2'
     */
    rtb_DiscreteFIRFilter20thorder = (rtb_DiscreteFIRFilter20thorder +
      rtP.Constant4_Value_i) / rtP.Constant5_Value_m;
    if (rtb_DiscreteFIRFilter20thorder > rtP.Saturation_UpperSat) {
      rtb_DiscreteFIRFilter20thorder = rtP.Saturation_UpperSat;
    } else if (rtb_DiscreteFIRFilter20thorder < rtP.Saturation_LowerSat) {
      rtb_DiscreteFIRFilter20thorder = rtP.Saturation_LowerSat;
    }

    rtb_Gain4 = (rtb_Gain4 + rtP.Constant4_Value_i) / rtP.Constant5_Value_m;
    if (rtb_Gain4 > rtP.Saturation_UpperSat) {
      rtb_Gain4 = rtP.Saturation_UpperSat;
    } else if (rtb_Gain4 < rtP.Saturation_LowerSat) {
      rtb_Gain4 = rtP.Saturation_LowerSat;
    }

    rtb_Product_b = (rtb_MultiportSwitch + rtP.Constant4_Value_i) /
      rtP.Constant5_Value_m;
    if (rtb_Product_b > rtP.Saturation_UpperSat) {
      rtb_Product_b = rtP.Saturation_UpperSat;
    } else if (rtb_Product_b < rtP.Saturation_LowerSat) {
      rtb_Product_b = rtP.Saturation_LowerSat;
    }

    rtb_MultiportSwitch = rtb_Product_b;

    /* End of Saturate: '<S35>/Saturation' */

    /* MultiPortSwitch: '<S35>/SelectVoltCalc_1' incorporates:
     *  Constant: '<S35>/Constant6'
     */
    switch ((int32_T)FOC_SELECT_Voltage_Assignment_UVW) {
     case 1:
      break;

     case 2:
      rtb_MultiportSwitch = rtb_Gain4;
      rtb_Gain4 = rtb_Product_b;
      break;

     case 3:
      rtb_MultiportSwitch = rtb_DiscreteFIRFilter20thorder;
      rtb_DiscreteFIRFilter20thorder = rtb_Gain4;
      rtb_Gain4 = rtb_MultiportSwitch;
      rtb_MultiportSwitch = rtb_Product_b;
      break;

     case 4:
      rtb_MultiportSwitch = rtb_DiscreteFIRFilter20thorder;
      rtb_DiscreteFIRFilter20thorder = rtb_Gain4;
      rtb_Gain4 = rtb_Product_b;
      break;

     case 5:
      rtb_IntegEnaSwitch1_idx_1 = rtb_DiscreteFIRFilter20thorder;
      rtb_MultiportSwitch = rtb_Gain4;
      rtb_DiscreteFIRFilter20thorder = rtb_Product_b;
      rtb_Gain4 = rtb_IntegEnaSwitch1_idx_1;
      break;

     default:
      rtb_MultiportSwitch = rtb_DiscreteFIRFilter20thorder;
      rtb_DiscreteFIRFilter20thorder = rtb_Product_b;
      break;
    }

    /* End of MultiPortSwitch: '<S35>/SelectVoltCalc_1' */

    /* Switch: '<S3>/AKS_Switch' */
    if (FOC_Mode_after_checks > rtP.AKS_Switch_Threshold) {
      /* Outport: '<Root>/DutyCycles' */
      rtY.DutyCycles[0] = rtb_DiscreteFIRFilter20thorder;
      rtY.DutyCycles[1] = rtb_Gain4;
      rtY.DutyCycles[2] = rtb_MultiportSwitch;
    } else {
      /* MultiPortSwitch: '<S3>/AKS Switch' incorporates:
       *  Constant: '<S3>/FOC_AKS_Mode'
       */
      switch ((int32_T)FOC_AKS_Mode) {
       case 1:
        /* Outport: '<Root>/DutyCycles' incorporates:
         *  Constant: '<S3>/AKS_LS'
         */
        rtY.DutyCycles[0] = rtP.AKS_LS_Value[0];
        rtY.DutyCycles[1] = rtP.AKS_LS_Value[1];
        rtY.DutyCycles[2] = rtP.AKS_LS_Value[2];
        break;

       case 2:
        /* Outport: '<Root>/DutyCycles' incorporates:
         *  Constant: '<S3>/AKS_HS'
         */
        rtY.DutyCycles[0] = rtP.AKS_HS_Value[0];
        rtY.DutyCycles[1] = rtP.AKS_HS_Value[1];
        rtY.DutyCycles[2] = rtP.AKS_HS_Value[2];
        break;

       default:
        /* Outport: '<Root>/DutyCycles' incorporates:
         *  Constant: '<S3>/AKS_LSHS'
         */
        rtY.DutyCycles[0] = rtP.AKS_LSHS_Value[0];
        rtY.DutyCycles[1] = rtP.AKS_LSHS_Value[1];
        rtY.DutyCycles[2] = rtP.AKS_LSHS_Value[2];
        break;
      }

      /* End of MultiPortSwitch: '<S3>/AKS Switch' */
    }

    /* End of Switch: '<S3>/AKS_Switch' */

    /* Product: '<S9>/Divide1' */
    rtb_Subtract2_p = u_alpha * u_alpha * rtb_phi_U_Trafo_Switch *
      rtb_phi_U_Trafo_Switch;
    rtb_Divide1_idx_1 = u_beta * u_beta * rtb_phi_U_Trafo_Switch *
      rtb_phi_U_Trafo_Switch;

    /* Switch: '<S20>/Switch4' incorporates:
     *  Constant: '<S20>/FOC_AngleEst_Delay1'
     *  UnitDelay: '<S20>/Unit Delay1'
     */
    if (FOC_AngleEst_Delay1 > rtP.Switch4_Threshold) {
      rtb_Product_b = rtDW.UnitDelay1_DSTATE_m[0];
      rtb_IntegEnaSwitch1_idx_1 = rtDW.UnitDelay1_DSTATE_m[1];
    } else {
      rtb_Product_b = u_alpha;
      rtb_IntegEnaSwitch1_idx_1 = u_beta;
    }

    /* End of Switch: '<S20>/Switch4' */

    /* Product: '<S21>/Product' incorporates:
     *  Constant: '<S21>/FOC_T_fast'
     */
    rtb_phi_U_Trafo_Switch = 1.0 / FOC_f_fastCTRL;

    /* Outport: '<Root>/ModInd' incorporates:
     *  Sqrt: '<S9>/Sqrt'
     *  Sum: '<S9>/Subtract2'
     */
    rtY.ModInd = sqrt(rtb_Subtract2_p + rtb_Divide1_idx_1);

    /* RelationalOperator: '<S31>/AntiWindupLE' incorporates:
     *  Constant: '<S31>/FOC_MaxModInd'
     *  Outport: '<Root>/ModInd'
     */
    rtb_Compare_l = (rtY.ModInd <= FOC_MaxModInd);

    /* Logic: '<S31>/AntiWindupOR_d' incorporates:
     *  Constant: '<S33>/Constant'
     *  Product: '<S31>/antiWindupProd'
     *  RelationalOperator: '<S33>/Compare'
     *  UnitDelay: '<S32>/IntegDelay1'
     */
    i_d_IntegNotStopped = ((rtb_antiWindupProd_idx_0 * rtDW.IntegDelay1_DSTATE[0]
      < rtP.AntiWindupGT_d_const) || rtb_Compare_l);

    /* Logic: '<S31>/AntiWindupOR_q' incorporates:
     *  Constant: '<S34>/Constant'
     *  Product: '<S31>/antiWindupProd'
     *  RelationalOperator: '<S34>/Compare'
     *  UnitDelay: '<S32>/IntegDelay1'
     */
    i_q_IntegNotStopped = (rtb_Compare_l || (rtb_antiWindupProd_idx_1 *
      rtDW.IntegDelay1_DSTATE[1] < rtP.AntiWindupGT_q_const));

    /* Switch: '<S32>/IntegStopSwitch2' incorporates:
     *  Constant: '<S32>/Zero1'
     */
    if (rtb_Compare != 0) {
      /* Switch: '<S32>/IntegStopSwitch3' incorporates:
       *  Constant: '<S32>/Zero1'
       *  UnitDelay: '<S32>/IntegDelay1'
       */
      if (rtb_Speed_Ctrl_Start_Sequence > rtP.IntegStopSwitch3_Threshold) {
        rtb_Subtract2_p = rtDW.IntegDelay1_DSTATE[0];
        rtb_Divide1_idx_1 = rtDW.IntegDelay1_DSTATE[1];
      } else {
        rtb_Subtract2_p = rtP.Zero1_Value[0];
        rtb_Divide1_idx_1 = rtP.Zero1_Value[1];
      }

      /* End of Switch: '<S32>/IntegStopSwitch3' */

      /* Switch: '<S32>/IntegStopSwitch1' incorporates:
       *  Gain: '<S32>/FOC_IntegDamp'
       *  Sum: '<S32>/IntSum2'
       */
      if (i_d_IntegNotStopped) {
        rtb_antiWindupProd_idx_0 = rtb_KPek1_idx_0 + rtb_Subtract2_p;
      } else {
        rtb_antiWindupProd_idx_0 = FOC_IntegDamp * rtb_Subtract2_p;
      }

      if (i_q_IntegNotStopped) {
        rtb_antiWindupProd_idx_1 = rtb_KPek1_idx_1 + rtb_Divide1_idx_1;
      } else {
        rtb_antiWindupProd_idx_1 = FOC_IntegDamp * rtb_Divide1_idx_1;
      }

      /* End of Switch: '<S32>/IntegStopSwitch1' */
    } else {
      rtb_antiWindupProd_idx_0 = rtP.Zero1_Value[0];
      rtb_antiWindupProd_idx_1 = rtP.Zero1_Value[1];
    }

    /* End of Switch: '<S32>/IntegStopSwitch2' */

    /* CombinatorialLogic: '<S40>/Logic' incorporates:
     *  Logic: '<S10>/Logical Operator5'
     *  Memory: '<S40>/Memory'
     *  RelationalOperator: '<S44>/Relational Operator1'
     *  UnitDelay: '<S44>/Unit Delay'
     */
    rtb_LogicalOperator4 = rtP.Logic_table_l[((((uint32_T)((int32_T)
      rtb_Logic_idx_1 > (int32_T)rtDW.UnitDelay_DSTATE_k) << 1) +
      (rtb_LogicalOperator5 || rtb_LogicalOperator4)) << 1) +
      rtDW.Memory_PreviousInput_fu];

    /* Switch: '<S48>/Switch' */
    if (rtb_LogicalOperator4) {
      /* Update for UnitDelay: '<S48>/Unit Delay' incorporates:
       *  Constant: '<S10>/T_Id_Ramp'
       *  Constant: '<S48>/FOC_T_fast'
       *  Product: '<S42>/Product'
       *  Product: '<S48>/Product5'
       *  Sum: '<S48>/Add'
       */
      rtDW.UnitDelay_DSTATE_gl = 1.0 / FOC_IfStarter_T_Id_Ramp * (1.0 /
        FOC_f_fastCTRL) + rtb_MinMax_c;
    } else {
      /* Update for UnitDelay: '<S48>/Unit Delay' incorporates:
       *  Constant: '<S48>/Constant1'
       */
      rtDW.UnitDelay_DSTATE_gl = rtP.Constant1_Value_l;
    }

    /* End of Switch: '<S48>/Switch' */

    /* Gain: '<S9>/Gain1' incorporates:
     *  Outport: '<Root>/ModInd'
     */
    Mod_Index = rtP.Gain1_Gain_d * rtY.ModInd;

    /* Gain: '<S35>/Gain1' */
    duty_cycle_u = rtP.Gain1_Gain_n * rtb_DiscreteFIRFilter20thorder;

    /* Gain: '<S35>/Gain2' */
    duty_cycle_v = rtP.Gain2_Gain_o * rtb_Gain4;

    /* Gain: '<S35>/Gain3' */
    duty_cycle_w = rtP.Gain3_Gain_h * rtb_MultiportSwitch;

    /* Gain: '<S5>/dummy_gain2' */
    Phi_el_U_Transformation = rtP.dummy_gain2_Gain_e * rtb_UkYk1;

    /* Gain: '<S32>/dummy' incorporates:
     *  UnitDelay: '<S32>/IntegDelay1'
     */
    u_d_Integrator = rtP.dummy_Gain * rtDW.IntegDelay1_DSTATE[0];

    /* Gain: '<S32>/dummy1' incorporates:
     *  UnitDelay: '<S32>/IntegDelay1'
     */
    u_q_Integrator = rtP.dummy1_Gain * rtDW.IntegDelay1_DSTATE[1];

    /* Gain: '<S6>/PsiReduceGain3' */
    I_d_Ref = rtP.PsiReduceGain3_Gain * rtb_TorqLimitSource_idx_0;

    /* Gain: '<S6>/PsiReduceGain4' */
    I_q_Ref = rtP.PsiReduceGain4_Gain * rtb_TorqLimitSource_idx_1;

    /* Product: '<S41>/Product1' incorporates:
     *  Constant: '<S10>/I_d_Ref'
     *  Constant: '<S10>/T_w_Wait'
     *  RelationalOperator: '<S42>/Relational Operator'
     */
    rtb_MinMax_c = (real_T)(rtb_Product1 >= FOC_IfStarter_Id_Ref) /
      FOC_IfStarter_T_w_Wait;

    /* MinMax: '<S41>/MinMax' incorporates:
     *  Constant: '<S41>/Constant2'
     *  UnitDelay: '<S41>/Unit Delay'
     */
    rtb_Subtract2_p = fmin(rtP.Constant2_Value_lu, rtDW.UnitDelay_DSTATE_c);

    /* Switch: '<S41>/Switch' */
    if (rtb_MinMax_c > rtP.Switch_Threshold_b) {
      /* Update for UnitDelay: '<S41>/Unit Delay' incorporates:
       *  Constant: '<S41>/FOC_T_fast'
       *  Product: '<S41>/Product5'
       *  Sum: '<S41>/Add'
       */
      rtDW.UnitDelay_DSTATE_c = 1.0 / FOC_f_fastCTRL * rtb_MinMax_c +
        rtb_Subtract2_p;
    } else {
      /* Update for UnitDelay: '<S41>/Unit Delay' incorporates:
       *  Constant: '<S41>/Constant1'
       */
      rtDW.UnitDelay_DSTATE_c = rtP.Constant1_Value_p;
    }

    /* End of Switch: '<S41>/Switch' */

    /* Switch: '<S49>/Switch' incorporates:
     *  Constant: '<S47>/Constant'
     *  RelationalOperator: '<S47>/Compare'
     */
    if (rtb_Subtract2_p >= rtP.CompareToConstant_const_j) {
      /* Update for UnitDelay: '<S49>/Unit Delay' incorporates:
       *  Constant: '<S10>/T_w_Ramp'
       *  Constant: '<S49>/FOC_T_fast'
       *  Product: '<S43>/Product'
       *  Product: '<S49>/Product5'
       *  Sum: '<S49>/Add'
       */
      rtDW.UnitDelay_DSTATE_e = 1.0 / FOC_IfStarter_T_w_Ramp * (1.0 /
        FOC_f_fastCTRL) + rtb_MinMax_l;
    } else {
      /* Update for UnitDelay: '<S49>/Unit Delay' incorporates:
       *  Constant: '<S49>/Constant1'
       */
      rtDW.UnitDelay_DSTATE_e = rtP.Constant1_Value_c;
    }

    /* End of Switch: '<S49>/Switch' */

    /* DiscreteFir: '<S30>/Discrete FIR Filter 20th order1' */
    rtb_Product1 = rtDW.TrafoSum1 * rtP.DiscreteFIRFilter20thorder1_C_l[0];
    rowIdx = 1;
    for (tmp = rtDW.DiscreteFIRFilter20thorder1_cir; tmp < 19; tmp++) {
      rtb_Product1 += rtDW.DiscreteFIRFilter20thorder1_sta[tmp] *
        rtP.DiscreteFIRFilter20thorder1_C_l[rowIdx];
      rowIdx++;
    }

    for (tmp = 0; tmp < rtDW.DiscreteFIRFilter20thorder1_cir; tmp++) {
      rtb_Product1 += rtDW.DiscreteFIRFilter20thorder1_sta[tmp] *
        rtP.DiscreteFIRFilter20thorder1_C_l[rowIdx];
      rowIdx++;
    }

    /* End of DiscreteFir: '<S30>/Discrete FIR Filter 20th order1' */

    /* Gain: '<S30>/Gain6' */
    I_q_Act_filt = rtP.Gain6_Gain * rtb_Product1;

    /* Gain: '<S30>/Gain1' */
    I_q_Act = rtP.Gain1_Gain_h * rtDW.TrafoSum1;

    /* DiscreteFir: '<S30>/Discrete FIR Filter 20th order' */
    rtb_Product1 = rtDW.TrafoSum * rtP.DiscreteFIRFilter20thorder_Co_l[0];
    rowIdx = 1;
    for (tmp = rtDW.DiscreteFIRFilter20thorder_circ; tmp < 19; tmp++) {
      rtb_Product1 += rtDW.DiscreteFIRFilter20thorder_stat[tmp] *
        rtP.DiscreteFIRFilter20thorder_Co_l[rowIdx];
      rowIdx++;
    }

    for (tmp = 0; tmp < rtDW.DiscreteFIRFilter20thorder_circ; tmp++) {
      rtb_Product1 += rtDW.DiscreteFIRFilter20thorder_stat[tmp] *
        rtP.DiscreteFIRFilter20thorder_Co_l[rowIdx];
      rowIdx++;
    }

    /* End of DiscreteFir: '<S30>/Discrete FIR Filter 20th order' */

    /* Gain: '<S30>/Gain5' */
    I_d_Act_filt = rtP.Gain5_Gain_j * rtb_Product1;

    /* Gain: '<S30>/Gain' */
    I_d_Act = rtP.Gain_Gain_g * rtDW.TrafoSum;

    /* Switch: '<S45>/Switch' incorporates:
     *  Abs: '<S45>/Abs'
     *  Constant: '<S45>/Constant1'
     *  Gain: '<S45>/Gain1'
     */
    if (fabs(rtb_Add_h) >= rtP.Switch_Threshold_i) {
      /* Signum: '<S45>/Sign' */
      if (!rtIsNaN(rtb_Product_i)) {
        if (rtb_Product_i < 0.0) {
          rtb_Product_i = -1.0;
        } else {
          rtb_Product_i = (rtb_Product_i > 0.0);
        }
      }

      /* End of Signum: '<S45>/Sign' */
      rtb_Product1 = rtP.Gain1_Gain_c * rtb_Product_i;
    } else {
      rtb_Product1 = rtP.Constant1_Value_lx;
    }

    /* End of Switch: '<S45>/Switch' */

    /* Update for UnitDelay: '<S45>/Unit Delay' incorporates:
     *  Sum: '<S45>/Add1'
     */
    rtDW.UnitDelay_DSTATE_p = rtb_Add_h - rtb_Product1;

    /* Gain: '<S5>/dummy_gain4' incorporates:
     *  Sum: '<S5>/phi_est_error2'
     */
    Phi_est_error_I_Trafo = (rtb_Switch2_e - rtb_Sum1_f) * rtP.dummy_gain4_Gain;

    /* Gain: '<S5>/dummy_gain1' */
    Phi_el_I_Transformation = rtP.dummy_gain1_Gain_j * rtb_Switch2_e;

    /* Sum: '<S23>/Deviation' */
    rtb_Product1 = rtb_TrigonometricFunction - Phi_Observer;

    /* Product: '<S23>/Product' incorporates:
     *  Constant: '<S23>/Constant'
     *  Constant: '<S23>/Constant1'
     *  Constant: '<S23>/FOC_T_fast'
     *  Gain: '<S23>/Gain'
     *  Product: '<S23>/Product2'
     *  Sum: '<S23>/Sum1'
     *  UnitDelay: '<S27>/Unit Delay1'
     */
    rtb_MinMax_l = (FOC_AngleObserver_w0 * FOC_AngleObserver_D * rtb_Product1 *
                    rtP.Gain_Gain_gk + rtDW.UnitDelay1_DSTATE) * (1.0 /
      FOC_f_fastCTRL);

    /* Product: '<S28>/Product' incorporates:
     *  Constant: '<S28>/FOC_T_fast'
     *  Gain: '<S23>/Gain4'
     */
    rtb_Switch2_e = FOC_OmegaObs3 * rtb_Product1 * (1.0 / FOC_f_fastCTRL);

    /* Product: '<S23>/Product1' incorporates:
     *  Constant: '<S23>/Constant'
     */
    rtb_Product_i = FOC_AngleObserver_w0 * FOC_AngleObserver_w0 * rtb_Product1;

    /* Gain: '<S5>/dummy_gain5' */
    Phi_est = rtP.dummy_gain5_Gain_j * rtb_Sum1_f;

    /* Product: '<S18>/T_ab' incorporates:
     *  Constant: '<S18>/Constant'
     *  Constant: '<S18>/FOC_f_fast'
     */
    rtb_Product1 = rtP.Constant_Value_d / FOC_f_fastCTRL;

    /* Product: '<S18>/Product3' incorporates:
     *  Constant: '<S18>/Tau'
     *  Product: '<S18>/Divide2'
     */
    rtb_Add_h = rtb_Product1 / FOC_AngleEst_w_el_filtered_Tau * rtb_Switch_speed;

    /* Product: '<S18>/Divide' incorporates:
     *  Constant: '<S18>/Tau'
     *  Sum: '<S18>/Sum1'
     *  UnitDelay: '<S18>/Unit Delay'
     */
    rtb_MinMax_c = (FOC_AngleEst_w_el_filtered_Tau - rtb_Product1) *
      rtDW.UnitDelay_DSTATE_m / FOC_AngleEst_w_el_filtered_Tau;

    /* Gain: '<S4>/Gain2' */
    FOC_AngleEst_w_el = rtP.Gain2_Gain_k * rtb_Switch_speed;

    /* Gain: '<S4>/Gain3' */
    FOC_AngleEst_Psi_PM_alpha = rtP.Gain3_Gain_b * rtb_psi_PM_alphabeta_idx_0;

    /* Gain: '<S4>/Gain4' */
    FOC_AngleEst_Psi_PM_beta = rtP.Gain4_Gain_j * rtb_psi_PM_alphabeta_idx_1;

    /* Gain: '<S10>/dummy_gain5' */
    IfStarter_process_finished = rtb_Logic_e_idx_1 ? (real_T)
      rtP.dummy_gain5_Gain_m * 0.0078125 : 0.0;

    /* Gain: '<S5>/dummy_gain' incorporates:
     *  Outport: '<Root>/w_el'
     */
    w_el = rtP.dummy_gain_Gain * rtY.w_el_j;

    /* Product: '<S46>/Product1' incorporates:
     *  Abs: '<S10>/Abs'
     *  Constant: '<S10>/Delta_w'
     *  Constant: '<S10>/T_switch'
     *  Logic: '<S10>/Logical Operator2'
     *  Outport: '<Root>/w_el'
     *  RelationalOperator: '<S10>/Relational Operator2'
     *  Sum: '<S10>/Subtract'
     */
    rtb_Switch_speed = (real_T)(rtb_LogicalOperator2 && (fabs(rtb_Abs_i -
      rtY.w_el_j) <= FOC_IfStarter_Delta_w)) / FOC_IfStarter_T_switch;

    /* Switch: '<S46>/Switch' */
    if (rtb_Switch_speed > rtP.Switch_Threshold_k) {
      /* Update for UnitDelay: '<S46>/Unit Delay' incorporates:
       *  Constant: '<S46>/FOC_T_fast'
       *  Product: '<S46>/Product5'
       *  Sum: '<S46>/Add'
       */
      rtDW.UnitDelay_DSTATE_g = 1.0 / FOC_f_fastCTRL * rtb_Switch_speed +
        rtb_MinMax;
    } else {
      /* Update for UnitDelay: '<S46>/Unit Delay' incorporates:
       *  Constant: '<S46>/Constant1'
       */
      rtDW.UnitDelay_DSTATE_g = rtP.Constant1_Value_e;
    }

    /* End of Switch: '<S46>/Switch' */

    /* Switch: '<S66>/Switch' incorporates:
     *  Abs: '<S66>/Abs'
     *  Constant: '<S66>/Constant1'
     *  Gain: '<S66>/Gain1'
     */
    if (fabs(rtb_Add) >= rtP.Switch_Threshold_ks) {
      /* Signum: '<S66>/Sign' */
      if (!rtIsNaN(rtb_Product)) {
        if (rtb_Product < 0.0) {
          rtb_Product = -1.0;
        } else {
          rtb_Product = (rtb_Product > 0.0);
        }
      }

      /* End of Signum: '<S66>/Sign' */
      rtb_Product1 = rtP.Gain1_Gain_j * rtb_Product;
    } else {
      rtb_Product1 = rtP.Constant1_Value_j;
    }

    /* End of Switch: '<S66>/Switch' */

    /* Gain: '<S11>/Gain1' incorporates:
     *  DataTypeConversion: '<S11>/Data Type Conversion'
     */
    FOC_Overcurrent_I_uvw = rtP.Gain1_Gain_m * (real32_T)rtb_Logic_m_idx_0;

    /* Gain: '<S30>/Gain2' */
    I_u = rtP.Gain2_Gain_h * rtb_SelectVoltCalc_1_idx_0;

    /* Gain: '<S30>/Gain3' */
    I_v = rtP.Gain3_Gain_l * rtb_SelectVoltCalc_1_idx_1;

    /* Gain: '<S30>/Gain4' */
    I_w = rtP.Gain4_Gain_g * rtb_SelectVoltCalc_1_idx_2;

    /* Gain: '<S12>/Gain2' incorporates:
     *  DataTypeConversion: '<S12>/Data Type Conversion1'
     */
    FOC_Overvoltage_U_DC = rtP.Gain2_Gain_a * (real32_T)rtb_Logic_e_idx_0;

    /* Gain: '<S12>/Gain1' incorporates:
     *  DataTypeConversion: '<S12>/Data Type Conversion'
     */
    FOC_Undervoltage_U_DC = rtP.Gain1_Gain_mo * (real32_T)rtb_Logic_idx_0;

    /* Update for Memory: '<S58>/Memory' */
    rtDW.Memory_PreviousInput = rtb_Logic_idx_0;

    /* Update for UnitDelay: '<S57>/Delay Input1'
     *
     * Block description for '<S57>/Delay Input1':
     *
     *  Store in Global RAM
     */
    rtDW.DelayInput1_DSTATE = rtb_Compare_k;

    /* Update for Memory: '<S59>/Memory' */
    rtDW.Memory_PreviousInput_n = rtb_Logic_e_idx_0;

    /* Update for UnitDelay: '<S52>/Delay Input1'
     *
     * Block description for '<S52>/Delay Input1':
     *
     *  Store in Global RAM
     */
    rtDW.DelayInput1_DSTATE_e = rtb_Compare_i;

    /* Update for Memory: '<S53>/Memory' */
    rtDW.Memory_PreviousInput_f = rtb_Logic_m_idx_0;

    /* Update for DiscreteTransferFcn: '<S15>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states = (f_2_w_el -
      rtP.DiscreteTransferFcn_DenCoef[1] * rtDW.DiscreteTransferFcn_states) /
      rtP.DiscreteTransferFcn_DenCoef[0];

    /* Update for UnitDelay: '<S66>/Unit Delay' incorporates:
     *  Sum: '<S66>/Add1'
     */
    rtDW.UnitDelay_DSTATE = rtb_Add - rtb_Product1;

    /* Update for UnitDelay: '<S27>/Unit Delay1' incorporates:
     *  Constant: '<S27>/FOC_T_fast'
     *  Product: '<S27>/Product'
     *  Sum: '<S23>/Sum2'
     *  Sum: '<S27>/Sum2'
     *  UnitDelay: '<S28>/Unit Delay1'
     */
    rtDW.UnitDelay1_DSTATE += (rtb_Product_i + rtDW.UnitDelay1_DSTATE_ms) * (1.0
      / FOC_f_fastCTRL);

    /* Update for UnitDelay: '<S44>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_k = rtb_Logic_idx_1;

    /* Update for Memory: '<S39>/Memory' */
    rtDW.Memory_PreviousInput_j = rtb_Logic_e_idx_1;

    /* Switch: '<S20>/Switch3' incorporates:
     *  Constant: '<S20>/FOC_AngleEst_Delay2'
     */
    rtb_LogicalOperator2 = (FOC_AngleEst_Delay2 > rtP.Switch3_Threshold);

    /* Update for UnitDelay: '<S18>/Unit Delay' incorporates:
     *  Sum: '<S18>/Sum'
     */
    rtDW.UnitDelay_DSTATE_m = rtb_Add_h + rtb_MinMax_c;

    /* Update for DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states_e = DiscreteTransferFcn_tmp;

    /* Update for DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states = rtb_Product_m;

    /* Update for UnitDelay: '<S26>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_a = rtb_TrigonometricFunction;

    /* Update for UnitDelay: '<S23>/Unit Delay3' incorporates:
     *  Sum: '<S23>/Sum6'
     */
    rtDW.UnitDelay3_DSTATE = rtb_MinMax_l + Phi_Observer;

    /* Update for UnitDelay: '<S20>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_m[0] = u_alpha;
    rtDW.UnitDelay1_DSTATE_m[1] = u_beta;

    /* Switch: '<S20>/Switch3' incorporates:
     *  UnitDelay: '<S20>/Unit Delay'
     */
    if (rtb_LogicalOperator2) {
      rtb_TrigonometricFunction = rtDW.UnitDelay_DSTATE_ec[0];
    } else {
      rtb_TrigonometricFunction = rtb_Product_b;
    }

    /* Update for UnitDelay: '<S21>/Unit Delay' incorporates:
     *  Constant: '<S4>/FOC_AngleEst_Rs'
     *  Constant: '<S4>/komp_kp'
     *  Product: '<S21>/Product'
     *  Product: '<S22>/Product'
     *  Product: '<S4>/Product2'
     *  Sum: '<S21>/Sum4'
     *  Sum: '<S4>/Sum'
     *  UnitDelay: '<S20>/Unit Delay'
     */
    rtDW.UnitDelay_DSTATE_b[0] += ((rtb_TrigonometricFunction -
      rtb_psi_PM_alphabeta_idx_0 * FOC_AngleEst_Komp_KP) - FOC_AngleEst_Rs *
      rtb_TrafoMatrixuvwalphabeta[0]) * rtb_phi_U_Trafo_Switch;

    /* Update for UnitDelay: '<S32>/IntegDelay1' */
    rtDW.IntegDelay1_DSTATE[0] = rtb_antiWindupProd_idx_0;

    /* Update for UnitDelay: '<S20>/Unit Delay' incorporates:
     *  Switch: '<S20>/Switch3'
     */
    rtDW.UnitDelay_DSTATE_ec[0] = rtb_Product_b;

    /* Switch: '<S20>/Switch3' incorporates:
     *  UnitDelay: '<S20>/Unit Delay'
     */
    if (rtb_LogicalOperator2) {
      rtb_TrigonometricFunction = rtDW.UnitDelay_DSTATE_ec[1];
    } else {
      rtb_TrigonometricFunction = rtb_IntegEnaSwitch1_idx_1;
    }

    /* Update for UnitDelay: '<S21>/Unit Delay' incorporates:
     *  Constant: '<S4>/FOC_AngleEst_Rs'
     *  Constant: '<S4>/komp_kp'
     *  Product: '<S21>/Product'
     *  Product: '<S22>/Product'
     *  Product: '<S4>/Product2'
     *  Sum: '<S21>/Sum4'
     *  Sum: '<S4>/Sum'
     *  UnitDelay: '<S20>/Unit Delay'
     */
    rtDW.UnitDelay_DSTATE_b[1] += ((rtb_TrigonometricFunction -
      rtb_psi_PM_alphabeta_idx_1 * FOC_AngleEst_Komp_KP) - FOC_AngleEst_Rs *
      rtb_TrafoMatrixuvwalphabeta[1]) * rtb_phi_U_Trafo_Switch;

    /* Update for UnitDelay: '<S32>/IntegDelay1' */
    rtDW.IntegDelay1_DSTATE[1] = rtb_antiWindupProd_idx_1;

    /* Update for UnitDelay: '<S20>/Unit Delay' incorporates:
     *  Switch: '<S20>/Switch3'
     */
    rtDW.UnitDelay_DSTATE_ec[1] = rtb_IntegEnaSwitch1_idx_1;

    /* Update for Memory: '<S40>/Memory' */
    rtDW.Memory_PreviousInput_fu = rtb_LogicalOperator4;

    /* Update for DiscreteFir: '<S30>/Discrete FIR Filter 20th order1' */
    /* Update circular buffer index */
    rtDW.DiscreteFIRFilter20thorder1_cir--;
    if (rtDW.DiscreteFIRFilter20thorder1_cir < 0) {
      rtDW.DiscreteFIRFilter20thorder1_cir = 18;
    }

    /* Update circular buffer */
    rtDW.DiscreteFIRFilter20thorder1_sta[rtDW.DiscreteFIRFilter20thorder1_cir] =
      rtDW.TrafoSum1;

    /* End of Update for DiscreteFir: '<S30>/Discrete FIR Filter 20th order1' */

    /* Update for DiscreteFir: '<S30>/Discrete FIR Filter 20th order' */
    /* Update circular buffer index */
    rtDW.DiscreteFIRFilter20thorder_circ--;
    if (rtDW.DiscreteFIRFilter20thorder_circ < 0) {
      rtDW.DiscreteFIRFilter20thorder_circ = 18;
    }

    /* Update circular buffer */
    rtDW.DiscreteFIRFilter20thorder_stat[rtDW.DiscreteFIRFilter20thorder_circ] =
      rtDW.TrafoSum;

    /* End of Update for DiscreteFir: '<S30>/Discrete FIR Filter 20th order' */

    /* Update for UnitDelay: '<S28>/Unit Delay1' incorporates:
     *  Sum: '<S28>/Sum2'
     */
    rtDW.UnitDelay1_DSTATE_ms += rtb_Switch2_e;
  }

  /* End of Inport: '<Root>/Enable' */
  /* End of Outputs for SubSystem: '<S1>/Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/FOC_CurrentControl' */

  /* Outport: '<Root>/Idq_Act' */
  rtY.Idq_Act[0] = rtDW.TrafoSum;
  rtY.Idq_Act[1] = rtDW.TrafoSum1;
}

/* Model initialize function */
void FOC_CurrentControl_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_CurrentControl' */
    /* SystemInitialize for Enabled SubSystem: '<S1>/Subsystem' */
    /* InitializeConditions for Memory: '<S58>/Memory' */
    rtDW.Memory_PreviousInput = rtP.SRFlipFlop_initial_condition;

    /* InitializeConditions for UnitDelay: '<S57>/Delay Input1'
     *
     * Block description for '<S57>/Delay Input1':
     *
     *  Store in Global RAM
     */
    rtDW.DelayInput1_DSTATE = rtP.DetectRisePositive_vinit;

    /* InitializeConditions for Memory: '<S59>/Memory' */
    rtDW.Memory_PreviousInput_n = rtP.SRFlipFlop1_initial_condition;

    /* InitializeConditions for UnitDelay: '<S52>/Delay Input1'
     *
     * Block description for '<S52>/Delay Input1':
     *
     *  Store in Global RAM
     */
    rtDW.DelayInput1_DSTATE_e = rtP.DetectRisePositive_vinit_c;

    /* InitializeConditions for Memory: '<S53>/Memory' */
    rtDW.Memory_PreviousInput_f = rtP.SRFlipFlop_initial_condition_d;

    /* InitializeConditions for DiscreteTransferFcn: '<S15>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states = rtP.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S66>/Unit Delay' */
    rtDW.UnitDelay_DSTATE = rtP.UnitDelay_InitialCondition_o;

    /* InitializeConditions for UnitDelay: '<S46>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_g = rtP.UnitDelay_InitialCondition_i;

    /* InitializeConditions for UnitDelay: '<S49>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_e = rtP.UnitDelay_InitialCondition_i2;

    /* InitializeConditions for UnitDelay: '<S27>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE = FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S44>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_k = rtP.UnitDelay_InitialCondition_hp;

    /* InitializeConditions for Memory: '<S39>/Memory' */
    rtDW.Memory_PreviousInput_j = rtP.If_Start_over_initial_condition;

    /* InitializeConditions for UnitDelay: '<S18>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_m = rtP.UnitDelay_InitialCondition_l;

    /* InitializeConditions for DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states_e = rtP.DiscreteTransferFcn_InitialSt_i;

    /* InitializeConditions for DiscreteTransferFcn: '<S19>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states = rtP.DiscreteTransferFcn1_InitialSta;

    /* InitializeConditions for UnitDelay: '<S26>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_a = rtP.UnitDelay_InitialCondition_lk;

    /* InitializeConditions for UnitDelay: '<S23>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE = rtP.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S45>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_p = rtP.UnitDelay_InitialCondition_d;

    /* InitializeConditions for UnitDelay: '<S48>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_gl = rtP.UnitDelay_InitialCondition_h;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_b[0] = FOC_AngleEst_Psi_InitVal;

    /* InitializeConditions for UnitDelay: '<S32>/IntegDelay1' */
    rtDW.IntegDelay1_DSTATE[0] = rtP.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S20>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_m[0] = rtP.UnitDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S20>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_ec[0] = rtP.UnitDelay_InitialCondition_h3;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_b[1] = FOC_AngleEst_Psi_InitVal;

    /* InitializeConditions for UnitDelay: '<S32>/IntegDelay1' */
    rtDW.IntegDelay1_DSTATE[1] = rtP.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S20>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_m[1] = rtP.UnitDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S20>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_ec[1] = rtP.UnitDelay_InitialCondition_h3;

    /* InitializeConditions for Memory: '<S40>/Memory' */
    rtDW.Memory_PreviousInput_fu = rtP.If_Start_over1_initial_conditio;

    /* InitializeConditions for UnitDelay: '<S41>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_c = rtP.UnitDelay_InitialCondition_f;

    /* InitializeConditions for UnitDelay: '<S28>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_ms = rtP.UnitDelay1_InitialCondition_c;

    /* SystemInitialize for Atomic SubSystem: '<S2>/SPEED_CONTROLLER' */
    /* InitializeConditions for UnitDelay: '<S64>/Delay Input2'
     *
     * Block description for '<S64>/Delay Input2':
     *
     *  Store in Global RAM
     */
    rtDW.DelayInput2_DSTATE = FOC_LIMIT_n_Ref_SlewRate_InitVal;

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_pj = rtP.UnitDelay_InitialCondition;

    /* End of SystemInitialize for SubSystem: '<S2>/SPEED_CONTROLLER' */

    /* SystemInitialize for Atomic SubSystem: '<S9>/SubS_InversePark_dq_alpha_beta' */
    for (i = 0; i < 19; i++) {
      /* InitializeConditions for DiscreteFir: '<S30>/Discrete FIR Filter 20th order1' */
      rtDW.DiscreteFIRFilter20thorder1_sta[i] =
        rtP.DiscreteFIRFilter20thorder1_I_j;

      /* InitializeConditions for DiscreteFir: '<S30>/Discrete FIR Filter 20th order' */
      rtDW.DiscreteFIRFilter20thorder_stat[i] =
        rtP.DiscreteFIRFilter20thorder_In_a;

      /* InitializeConditions for DiscreteFir: '<S36>/Discrete FIR Filter 20th order1' */
      rtDW.DiscreteFIRFilter20thorder1_s_g[i] =
        rtP.DiscreteFIRFilter20thorder1_Ini;

      /* InitializeConditions for DiscreteFir: '<S36>/Discrete FIR Filter 20th order' */
      rtDW.DiscreteFIRFilter20thorder_st_n[i] =
        rtP.DiscreteFIRFilter20thorder_Init;
    }

    /* End of SystemInitialize for SubSystem: '<S9>/SubS_InversePark_dq_alpha_beta' */

    /* SystemInitialize for Outport: '<Root>/DutyCycles' incorporates:
     *  Outport: '<S2>/DutyCycles_OUT'
     */
    rtY.DutyCycles[0] = rtP.DutyCycles_OUT_Y0;
    rtY.DutyCycles[1] = rtP.DutyCycles_OUT_Y0;
    rtY.DutyCycles[2] = rtP.DutyCycles_OUT_Y0;

    /* SystemInitialize for Outport: '<Root>/ModInd' incorporates:
     *  Outport: '<S2>/ModInd'
     */
    rtY.ModInd = rtP.ModInd_Y0;

    /* SystemInitialize for Sum: '<S30>/TrafoSum' incorporates:
     *  Outport: '<S2>/Idq'
     */
    rtDW.TrafoSum = rtP.Idq_Y0;

    /* SystemInitialize for Sum: '<S30>/TrafoSum1' incorporates:
     *  Outport: '<S2>/Idq'
     */
    rtDW.TrafoSum1 = rtP.Idq_Y0;

    /* SystemInitialize for Outport: '<Root>/w_el' incorporates:
     *  Outport: '<S2>/w_el'
     */
    rtY.w_el_j = rtP.w_el_Y0;

    /* End of SystemInitialize for SubSystem: '<S1>/Subsystem' */
    /* End of SystemInitialize for SubSystem: '<Root>/FOC_CurrentControl' */

    /* SystemInitialize for Outport: '<Root>/Idq_Act' incorporates:
     *  Sum: '<S30>/TrafoSum'
     *  Sum: '<S30>/TrafoSum1'
     */
    rtY.Idq_Act[0] = rtDW.TrafoSum;
    rtY.Idq_Act[1] = rtDW.TrafoSum1;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
