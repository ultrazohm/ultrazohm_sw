/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Regelung.c
 *
 * Code generated for Simulink model 'Regelung'.
 *
 * Model version                  : 2.26
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Sep 20 14:43:03 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "Regelung.h"

static void MATLABFunction(real32_T rtu_i_im, const real32_T rtu_w[2], boolean_T
  *rty_Betrieb);
static void MATLABFunction_f(real32_T rtu_re, real32_T rtu_U_lim, real32_T
  rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim);
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim);
static void SwitchCaseActionSubsystem(real32_T *rty_a, real32_T *rty_Iref);

/*
 * Output and update for atomic system:
 *    '<S21>/MATLAB Function'
 *    '<S31>/MATLAB Function'
 *    '<S41>/MATLAB Function'
 */
static void MATLABFunction(real32_T rtu_i_im, const real32_T rtu_w[2], boolean_T
  *rty_Betrieb)
{
  int32_T k;
  real32_T b_x[2];
  real32_T x;
  boolean_T exitg1;
  boolean_T y;

  /* MATLAB Function 'Einzelstrangstromregler/MATLAB Function': '<S23>:1' */
  /* '<S23>:1:2' if sign(i_im) == sign(w) */
  if (rtu_i_im < 0.0F) {
    x = -1.0F;
  } else if (rtu_i_im > 0.0F) {
    x = 1.0F;
  } else {
    x = rtu_i_im;
  }

  if (rtu_w[0] < 0.0F) {
    b_x[0] = -1.0F;
  } else if (rtu_w[0] > 0.0F) {
    b_x[0] = 1.0F;
  } else {
    b_x[0] = rtu_w[0];
  }

  if (rtu_w[1] < 0.0F) {
    b_x[1] = -1.0F;
  } else if (rtu_w[1] > 0.0F) {
    b_x[1] = 1.0F;
  } else {
    b_x[1] = rtu_w[1];
  }

  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x != b_x[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    /* '<S23>:1:3' Betrieb = boolean(1); */
    *rty_Betrieb = true;

    /* Motorisch */
  } else {
    /* '<S23>:1:4' else */
    /* '<S23>:1:5' Betrieb = boolean(0); */
    *rty_Betrieb = false;

    /* Generatorisch */
  }
}

/*
 * Output and update for atomic system:
 *    '<S25>/MATLAB Function'
 *    '<S26>/MATLAB Function'
 *    '<S35>/MATLAB Function'
 *    '<S36>/MATLAB Function'
 *    '<S45>/MATLAB Function'
 *    '<S46>/MATLAB Function'
 */
static void MATLABFunction_f(real32_T rtu_re, real32_T rtu_U_lim, real32_T
  rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T U_rel;

  /* MATLAB Function 'resonater-I-Regler/MATLAB Function': '<S28>:1' */
  /* '<S28>:1:2' U_abs = sqrt(re^2+im^2); */
  /* '<S28>:1:3' U_rel = U_abs/U_lim; */
  U_rel = sqrtf(rtu_re * rtu_re + rtu_im * rtu_im) / rtu_U_lim;

  /* '<S28>:1:4' if U_rel>=1 */
  if (U_rel >= 1.0F) {
    /* '<S28>:1:5' re_lim = re/U_rel; */
    *rty_re_lim = rtu_re / U_rel;

    /* '<S28>:1:6' im_lim = im/U_rel; */
    *rty_im_lim = rtu_im / U_rel;
  } else {
    /* '<S28>:1:7' else */
    /* '<S28>:1:8' re_lim = re; */
    *rty_re_lim = rtu_re;

    /* '<S28>:1:9' im_lim = im; */
    *rty_im_lim = rtu_im;
  }
}

/*
 * Output and update for atomic system:
 *    '<S27>/MATLAB Function'
 *    '<S37>/MATLAB Function'
 *    '<S47>/MATLAB Function'
 */
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T re_lim;
  real32_T rtu_im_0;
  real32_T tmp;

  /* MATLAB Function 'resonater-PI-Regler/MATLAB Function': '<S30>:1' */
  /* '<S30>:1:2' if (re^2 + im^2)<=U_lim^2 */
  tmp = rtu_U_lim * rtu_U_lim;
  if (rtu_re * rtu_re + rtu_im * rtu_im <= tmp) {
    /* '<S30>:1:3' re_lim = re; */
    re_lim = rtu_re;

    /* '<S30>:1:4' im_lim = im; */
    rtu_im_0 = rtu_im;
  } else if (!rtu_Betrieb) {
    /* '<S30>:1:5' elseif Betrieb == 0 */
    /* Generator */
    /* '<S30>:1:7' if abs(im)>0.95*U_lim */
    if (fabsf(rtu_im) > 0.95F * rtu_U_lim) {
      /* '<S30>:1:8' im_lim = sign(im)*0.95*U_lim; */
      if (rtu_im < 0.0F) {
        rtu_im_0 = -1.0F;
      } else if (rtu_im > 0.0F) {
        rtu_im_0 = 1.0F;
      } else {
        rtu_im_0 = rtu_im;
      }

      rtu_im_0 = rtu_im_0 * 0.95F * rtu_U_lim;
    } else {
      /* '<S30>:1:9' else */
      /* '<S30>:1:10' im_lim = im; */
      rtu_im_0 = rtu_im;
    }

    /* '<S30>:1:12' re_lim = sign(re)*sqrt(U_lim^2 - im_lim^2); */
    if (rtu_re < 0.0F) {
      re_lim = -1.0F;
    } else if (rtu_re > 0.0F) {
      re_lim = 1.0F;
    } else {
      re_lim = rtu_re;
    }

    re_lim *= sqrtf(tmp - rtu_im_0 * rtu_im_0);
  } else {
    /* '<S30>:1:13' else */
    /* Motor */
    /* '<S30>:1:15' if abs(re)>0.95*U_lim */
    if (fabsf(rtu_re) > 0.95F * rtu_U_lim) {
      /* '<S30>:1:16' re_lim = sign(re)*0.95*U_lim; */
      if (rtu_re < 0.0F) {
        re_lim = -1.0F;
      } else if (rtu_re > 0.0F) {
        re_lim = 1.0F;
      } else {
        re_lim = rtu_re;
      }

      re_lim = re_lim * 0.95F * rtu_U_lim;
    } else {
      /* '<S30>:1:17' else */
      /* '<S30>:1:18' re_lim = re; */
      re_lim = rtu_re;
    }

    /* '<S30>:1:20' im_lim = sign(im)*sqrt(U_lim^2 - re_lim^2); */
    if (rtu_im < 0.0F) {
      rtu_im_0 = -1.0F;
    } else if (rtu_im > 0.0F) {
      rtu_im_0 = 1.0F;
    } else {
      rtu_im_0 = rtu_im;
    }

    rtu_im_0 *= sqrtf(tmp - re_lim * re_lim);
  }

  *rty_re_lim = re_lim;
  *rty_im_lim = rtu_im_0;
}

/*
 * Output and update for action system:
 *    '<S7>/Switch Case Action Subsystem'
 *    '<S7>/Switch Case Action Subsystem1'
 *    '<S7>/Switch Case Action Subsystem2'
 */
static void SwitchCaseActionSubsystem(real32_T *rty_a, real32_T *rty_Iref)
{
  /* SignalConversion generated from: '<S18>/a' incorporates:
   *  Constant: '<S18>/Constant1'
   */
  *rty_a = 0.5F;

  /* SignalConversion generated from: '<S18>/Iref' incorporates:
   *  Constant: '<S18>/Constant2'
   */
  *rty_Iref = 0.0F;
}

/* Model step function */
void Regelung_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1_n;
  real32_T U_im_a;
  real32_T U_im_c;
  real32_T U_im_g;
  real32_T U_re_k;
  real32_T U_re_ky;
  real32_T rtb_Gain1_b;
  real32_T rtb_Product2_o;
  real32_T y_i;
  int8_T rtAction;
  int8_T rtPrevAction;
  uint8_T error_speed_limit;
  boolean_T rtb_Betrieb_l;

  /* Gain: '<S2>/Gain' incorporates:
   *  Delay: '<S2>/Delay'
   *  Inport: '<Root>/Act_U_ZK'
   *  Sum: '<S2>/Sum'
   */
  rtDW->Gain = rtP.T_R / 0.01F * (rtU->Act_U_ZK - rtDW->Delay_DSTATE);

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  DiscreteTimeIntegrator = 0.5F * rtDW->Gain +
    rtDW->DiscreteTimeIntegrator_DSTATE;

  /* SwitchCase: '<S1>/switch_case_power' incorporates:
   *  Inport: '<Root>/fl_power'
   */
  rtPrevAction = rtDW->switch_case_power_ActiveSubsyst;
  switch (rtU->fl_power) {
   case 1:
   case 2:
   case 3:
    rtAction = 0;
    break;

   default:
    rtAction = 1;
    break;
  }

  rtDW->switch_case_power_ActiveSubsyst = rtAction;
  if ((rtPrevAction != rtAction) && (rtPrevAction == 0)) {
    /* Disable for SwitchCase: '<S3>/Switch Case' */
    rtDW->SwitchCase_ActiveSubsystem = -1;

    /* Disable for SwitchCase: '<S7>/Switch Case' */
    rtDW->SwitchCase_ActiveSubsystem_f = -1;

    /* Disable for SwitchCase: '<S7>/Switch Case1' */
    rtDW->SwitchCase1_ActiveSubsystem = -1;

    /* Disable for SwitchCase: '<S7>/Switch Case2' */
    rtDW->SwitchCase2_ActiveSubsystem = -1;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S1>/Regelung' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* SwitchCase: '<S3>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_control_type'
     */
    rtPrevAction = rtDW->SwitchCase_ActiveSubsystem;
    if (rtU->fl_control_type != 1) {
      rtAction = 1;
    }

    rtDW->SwitchCase_ActiveSubsystem = rtAction;
    if (rtAction == 0) {
      if (0 != rtPrevAction) {
        /* InitializeConditions for IfAction SubSystem: '<S3>/Drehzahlregler' incorporates:
         *  ActionPort: '<S6>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S3>/Switch Case' incorporates:
         *  Delay: '<S11>/Delay'
         *  Delay: '<S6>/Delay'
         *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
         */
        rtDW->Delay_DSTATE_p = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.0F;
        rtDW->Delay_DSTATE_j = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S3>/Drehzahlregler' */
      }

      /* Outputs for IfAction SubSystem: '<S3>/Drehzahlregler' incorporates:
       *  ActionPort: '<S6>/Action Port'
       */
      /* MATLAB Function: '<S6>/function_Eckdrehzahl' incorporates:
       *  Inport: '<Root>/fl_field_weakening'
       */
      /* MATLAB Function 'Regelung-Einzelstrang/Regelung/Drehzahlregler/function_Eckdrehzahl': '<S14>:1' */
      /* '<S14>:1:4' U_FA = 0.95*U_ZK/2; */
      rtDW->U_FA = 0.95F * DiscreteTimeIntegrator / 2.0F;

      /* '<S14>:1:5' a = Psi_PM^2 + (L*i_ref_max)^2; */
      rtDW->a = rtP.L * rtP.i_ref_max;
      rtDW->a = rtP.Psi_PM * rtP.Psi_PM + rtDW->a * rtDW->a;

      /* '<S14>:1:6' b = 2*Psi_PM*R*i_ref_max; */
      rtDW->b = 2.0F * rtP.Psi_PM * rtP.R * rtP.i_ref_max;

      /* '<S14>:1:7' c = (R*i_ref_max)^2 - U_FA^2; */
      rtDW->Gain1 = rtP.R * rtP.i_ref_max;
      rtDW->U_FA = rtDW->Gain1 * rtDW->Gain1 - rtDW->U_FA * rtDW->U_FA;

      /* '<S14>:1:8' if -4*a*c >= single(0) */
      if (-4.0F * rtDW->a * rtDW->U_FA >= 0.0F) {
        /* '<S14>:1:9' n_eck = single(30)/(p*pi) * (-b+sqrt(b^2 -4*a*c))/(2*a); */
        rtDW->U_FA = (sqrtf(rtDW->b * rtDW->b - 4.0F * rtDW->a * rtDW->U_FA) +
                      -rtDW->b) * (30.0F / (rtP.p * 3.14159274F)) / (2.0F *
          rtDW->a);

        /* '<S14>:1:10' error_speed_limit = uint8(0); */
        error_speed_limit = 0U;
      } else {
        /* '<S14>:1:11' else */
        /* '<S14>:1:12' n_eck = single(0); */
        rtDW->U_FA = 0.0F;

        /* '<S14>:1:13' error_speed_limit = uint8(1); */
        error_speed_limit = 1U;
      }

      /* '<S14>:1:15' if (flag_id == 1) && (error_speed_limit == 0) */
      if ((rtU->fl_field_weakening == 1) && (error_speed_limit == 0)) {
        /* '<S14>:1:16' n_sat = min(3*n_eck, n_ref_max); */
        rtDW->a = fminf(3.0F * rtDW->U_FA, rtP.n_ref_max);
      } else {
        /* '<S14>:1:17' else */
        /* '<S14>:1:18' n_sat = min(n_eck, n_ref_max); */
        rtDW->a = fminf(rtDW->U_FA, rtP.n_ref_max);
      }

      /* Outport: '<Root>/error_speed_limit' incorporates:
       *  MATLAB Function: '<S6>/function_Eckdrehzahl'
       */
      rtY->error_speed_limit = error_speed_limit;

      /* MATLAB Function: '<S6>/Function_Feldschwaeche' incorporates:
       *  Constant: '<S6>/Constant'
       *  Inport: '<Root>/Act_n'
       *  Inport: '<Root>/fl_field_weakening'
       *  MATLAB Function: '<S6>/function_Eckdrehzahl'
       */
      /* MATLAB Function 'Regelung-Einzelstrang/Regelung/Drehzahlregler/Function_Feldschwaeche': '<S9>:1' */
      /* '<S9>:1:3' switch flag_id */
      if (rtU->fl_field_weakening == 1) {
        /* '<S9>:1:4' case uint8(1) */
        /* '<S9>:1:5' if n_ist>n_eck */
        if (rtU->Act_n > rtDW->U_FA) {
          /* I_d_soll = (Psi_PM*(n_eck-n_ist))/L_d; */
          /* '<S9>:1:7' I_re_soll = Psi_PM/L * (n_eck/n_ist - single(1)); */
          rtDW->b = (rtDW->U_FA / rtU->Act_n - 1.0F) * (rtP.Psi_PM / rtP.L);
        } else {
          /* '<S9>:1:8' else */
          /* '<S9>:1:9' I_re_soll = single(0); */
          rtDW->b = 0.0F;
        }
      } else {
        /* '<S9>:1:11' otherwise */
        /* '<S9>:1:12' I_re_soll = single(0); */
        rtDW->b = 0.0F;
      }

      /* '<S9>:1:15' if abs(I_re_soll)>= 0.95*I_ref_max */
      if (fabsf(rtDW->b) >= 0.95F * rtP.i_ref_max) {
        /* '<S9>:1:16' I_re_soll = sign(I_re_soll)*0.95*I_ref_max; */
        if (rtDW->b < 0.0F) {
          rtDW->b = -1.0F;
        } else if (rtDW->b > 0.0F) {
          rtDW->b = 1.0F;
        }

        rtDW->b = rtDW->b * 0.95F * rtP.i_ref_max;
      }

      /* '<S9>:1:19' I_im_max = sqrt(I_ref_max^2-I_re_soll^2); */
      rtDW->U_FA = sqrtf(rtP.i_ref_max * rtP.i_ref_max - rtDW->b * rtDW->b);

      /* Merge: '<S3>/Merge' incorporates:
       *  MATLAB Function: '<S6>/Function_Feldschwaeche'
       *  SignalConversion generated from: '<S6>/I_re_soll [A]'
       */
      rtDW->I_re = rtDW->b;

      /* Switch: '<S13>/Switch2' incorporates:
       *  Inport: '<Root>/Ref_n'
       *  RelationalOperator: '<S13>/LowerRelop1'
       */
      if (rtU->Ref_n <= rtDW->a) {
        /* Gain: '<S6>/Gain3' */
        rtDW->a = -rtDW->a;

        /* Switch: '<S13>/Switch' incorporates:
         *  RelationalOperator: '<S13>/UpperRelop'
         */
        if (rtU->Ref_n >= rtDW->a) {
          rtDW->a = rtU->Ref_n;
        }

        /* End of Switch: '<S13>/Switch' */
      }

      /* End of Switch: '<S13>/Switch2' */

      /* Gain: '<S11>/Gain' incorporates:
       *  Delay: '<S11>/Delay'
       *  Sum: '<S11>/Sum'
       */
      rtDW->a = rtP.T_R / rtP.T_VF_n * (rtDW->a - rtDW->Delay_DSTATE_p);

      /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
      rtDW->b = 0.5F * rtDW->a + rtDW->DiscreteTimeIntegrator_DSTATE_a;

      /* Gain: '<S10>/Gain' incorporates:
       *  DataTypeConversion: '<S3>/Data Type Conversion'
       *  Gain: '<S6>/Gain'
       *  Inport: '<Root>/Act_n'
       *  Product: '<S6>/Divide'
       *  Sum: '<S6>/Sum'
       */
      rtDW->Switch2 = (rtDW->b - rtU->Act_n) / (real32_T)rtU->fl_power * 3.0F *
        rtP.Kp_n;

      /* Gain: '<S10>/Gain1' incorporates:
       *  Delay: '<S6>/Delay'
       *  Sum: '<S10>/Sum1'
       */
      rtDW->Gain1 = rtP.T_R * rtP.Kis_n * (rtDW->Switch2 + rtDW->Delay_DSTATE_j);

      /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator' incorporates:
       *  Inport: '<Root>/fl_integrator_reset'
       */
      if (rtU->fl_integrator_reset != 0) {
        rtDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;
      }

      /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
      y_i = 0.5F * rtDW->Gain1 + rtDW->DiscreteTimeIntegrator_DSTATE_d;

      /* Sum: '<S10>/Sum' */
      rtDW->y = rtDW->Switch2 + y_i;

      /* Switch: '<S12>/Switch2' incorporates:
       *  Gain: '<S6>/Gain2'
       *  RelationalOperator: '<S12>/LowerRelop1'
       *  RelationalOperator: '<S12>/UpperRelop'
       *  Switch: '<S12>/Switch'
       */
      if (rtDW->y > rtDW->U_FA) {
        rtDW->Switch2 = rtDW->U_FA;
      } else if (rtDW->y < -rtDW->U_FA) {
        /* Switch: '<S12>/Switch' incorporates:
         *  Gain: '<S6>/Gain2'
         */
        rtDW->Switch2 = -rtDW->U_FA;
      } else {
        rtDW->Switch2 = rtDW->y;
      }

      /* End of Switch: '<S12>/Switch2' */

      /* Merge: '<S3>/Merge1' incorporates:
       *  SignalConversion generated from: '<S6>/I_im_soll [A]'
       */
      rtDW->I_im = rtDW->Switch2;

      /* Update for Delay: '<S11>/Delay' */
      rtDW->Delay_DSTATE_p = rtDW->b;

      /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.5F * rtDW->a + rtDW->b;

      /* Update for Delay: '<S6>/Delay' incorporates:
       *  Sum: '<S6>/Sum1'
       */
      rtDW->Delay_DSTATE_j = rtDW->Switch2 - rtDW->y;

      /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_d = 0.5F * rtDW->Gain1 + y_i;

      /* End of Outputs for SubSystem: '<S3>/Drehzahlregler' */
    } else {
      /* Outputs for IfAction SubSystem: '<S3>/Stromvorgabe_extern' incorporates:
       *  ActionPort: '<S8>/Action Port'
       */
      /* MATLAB Function: '<S8>/Function_I_limit' incorporates:
       *  Constant: '<S8>/Constant'
       *  Inport: '<Root>/Ref_I_im_ext'
       *  Inport: '<Root>/Ref_I_re_ext'
       */
      /* MATLAB Function 'Regelung-Einzelstrang/Regelung/Stromvorgabe_extern/Function_I_limit': '<S51>:1' */
      /* '<S51>:1:4' I_abs_ext = sqrt(I_re_soll_ext^2+I_im_soll_ext^2); */
      /* '<S51>:1:5' if I_abs_ext > I_ref_max */
      if (sqrtf(rtU->Ref_I_re_ext * rtU->Ref_I_re_ext + rtU->Ref_I_im_ext *
                rtU->Ref_I_im_ext) > rtP.i_ref_max) {
        /* '<S51>:1:6' if abs(I_re_soll_ext)>= 0.95*I_ref_max */
        if (fabsf(rtU->Ref_I_re_ext) >= 0.95F * rtP.i_ref_max) {
          /* '<S51>:1:7' I_re_soll = sign(I_re_soll_ext)*0.95*I_ref_max; */
          if (rtU->Ref_I_re_ext < 0.0F) {
            rtDW->U_FA = -1.0F;
          } else if (rtU->Ref_I_re_ext > 0.0F) {
            rtDW->U_FA = 1.0F;
          } else {
            rtDW->U_FA = rtU->Ref_I_re_ext;
          }

          rtDW->b = rtDW->U_FA * 0.95F * rtP.i_ref_max;
        } else {
          /* '<S51>:1:8' else */
          /* '<S51>:1:9' I_re_soll = I_re_soll_ext; */
          rtDW->b = rtU->Ref_I_re_ext;
        }

        /* '<S51>:1:11' I_im_soll = sign(I_im_soll_ext)*sqrt(I_ref_max^2-I_re_soll^2); */
        if (rtU->Ref_I_im_ext < 0.0F) {
          rtDW->U_FA = -1.0F;
        } else if (rtU->Ref_I_im_ext > 0.0F) {
          rtDW->U_FA = 1.0F;
        } else {
          rtDW->U_FA = rtU->Ref_I_im_ext;
        }

        /* Merge: '<S3>/Merge1' */
        rtDW->I_im = sqrtf(rtP.i_ref_max * rtP.i_ref_max - rtDW->b * rtDW->b) *
          rtDW->U_FA;
      } else {
        /* '<S51>:1:12' else */
        /* '<S51>:1:13' I_re_soll = I_re_soll_ext; */
        rtDW->b = rtU->Ref_I_re_ext;

        /* Merge: '<S3>/Merge1' */
        /* '<S51>:1:14' I_im_soll = I_im_soll_ext; */
        rtDW->I_im = rtU->Ref_I_im_ext;
      }

      /* Merge: '<S3>/Merge' incorporates:
       *  MATLAB Function: '<S8>/Function_I_limit'
       *  SignalConversion generated from: '<S8>/I_re_soll'
       */
      rtDW->I_re = rtDW->b;

      /* End of Outputs for SubSystem: '<S3>/Stromvorgabe_extern' */
    }

    /* End of SwitchCase: '<S3>/Switch Case' */

    /* Sum: '<S7>/Add' incorporates:
     *  Constant: '<S7>/Constant'
     *  Gain: '<S7>/Gain'
     *  Inport: '<Root>/Act_theta_u_el'
     *  Inport: '<Root>/Act_w_el'
     *  Product: '<S7>/Product'
     */
    rtDW->U_FA = 1.5F * rtP.T_R * rtU->Act_w_el + rtU->Act_theta_u_el;

    /* SwitchCase: '<S7>/Switch Case' */
    rtPrevAction = rtDW->SwitchCase_ActiveSubsystem_f;
    switch (rtU->fl_power) {
     case 1:
     case 2:
     case 3:
      rtAction = 0;
      break;

     default:
      rtAction = 1;
      break;
    }

    rtDW->SwitchCase_ActiveSubsystem_f = rtAction;
    if (rtAction == 0) {
      if (0 != rtPrevAction) {
        /* InitializeConditions for IfAction SubSystem: '<S7>/Strang U' incorporates:
         *  ActionPort: '<S15>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S7>/Switch Case' incorporates:
         *  Delay: '<S25>/Delay'
         *  Delay: '<S25>/Delay1'
         *  Delay: '<S26>/Delay'
         *  Delay: '<S26>/Delay1'
         *  Delay: '<S27>/Delay'
         *  Delay: '<S27>/Delay1'
         *  DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S25>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S26>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S27>/Discrete-Time Integrator1'
         *  UnitDelay generated from: '<S22>/UD'
         *
         * Block description for UnitDelay generated from '<S22>/UD':
         *
         *  Store in Global RAM
         */
        rtDW->UD_1_DSTATE_c = 0.0F;
        rtDW->UD_2_DSTATE_at = 0.0F;
        rtDW->Delay1_DSTATE_d = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTAT_oq = 0.0F;
        rtDW->Delay_DSTATE_m = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTA_i0 = 0.0F;
        rtDW->Delay1_DSTATE_b = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_n = 0.0F;
        rtDW->Delay_DSTATE_al = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0F;
        rtDW->Delay1_DSTATE_i = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.0F;
        rtDW->Delay_DSTATE_d = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTA_iy = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S7>/Strang U' */
      }

      /* Outputs for IfAction SubSystem: '<S7>/Strang U' incorporates:
       *  ActionPort: '<S15>/Action Port'
       */
      /* Sum: '<S22>/Diff' incorporates:
       *  Inport: '<Root>/Act_theta_u_el'
       *  UnitDelay generated from: '<S22>/UD'
       *
       * Block description for '<S22>/Diff':
       *
       *  Add in CPU
       *
       * Block description for UnitDelay generated from '<S22>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->Diff_i[0] = rtU->Act_theta_u_el - rtDW->UD_1_DSTATE_c;
      rtDW->Diff_i[1] = rtDW->U_FA - rtDW->UD_2_DSTATE_at;

      /* MATLAB Function: '<S21>/MATLAB Function' */
      MATLABFunction(rtDW->I_im, rtDW->Diff_i, &rtb_Betrieb_l);

      /* Trigonometry: '<S24>/Cos' incorporates:
       *  Inport: '<Root>/Act_theta_u_el'
       *  Trigonometry: '<S27>/Cos'
       */
      rtDW->Switch2 = cosf(rtU->Act_theta_u_el);

      /* Gain: '<S24>/Gain' incorporates:
       *  Gain: '<S27>/Gain'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Trigonometry: '<S24>/Cos1'
       */
      rtDW->a = -sinf(rtU->Act_theta_u_el);

      /* Sum: '<S24>/Sum' incorporates:
       *  Gain: '<S24>/Gain'
       *  Product: '<S24>/Product'
       *  Product: '<S24>/Product1'
       *  Trigonometry: '<S24>/Cos'
       */
      rtDW->b = rtDW->I_re * rtDW->Switch2 + rtDW->I_im * rtDW->a;

      /* Sum: '<S21>/Sum' incorporates:
       *  Inport: '<Root>/Act_Iu'
       */
      rtDW->Gain4_i = rtDW->b - rtU->Act_Iu;

      /* Gain: '<S27>/Gain6' */
      rtDW->Gain1 = rtP.Kp * rtDW->Gain4_i;

      /* Product: '<S27>/Product1' */
      y_i = rtDW->Switch2 * rtDW->Gain1;

      /* Gain: '<S27>/Gain1' incorporates:
       *  Delay: '<S27>/Delay1'
       *  Gain: '<S27>/Gain2'
       *  Sum: '<S27>/Sum4'
       */
      rtDW->Gain2_n = rtP.T_R * rtP.K1;
      rtDW->y = rtDW->Gain2_n * (rtDW->Delay1_DSTATE_d + y_i);

      /* DiscreteIntegrator: '<S27>/Discrete-Time Integrator' */
      rtDW->Switch2 = 0.5F * rtDW->y + rtDW->DiscreteTimeIntegrator_DSTAT_oq;

      /* Sum: '<S27>/Sum5' */
      rtDW->U_re_c = rtDW->Switch2 + y_i;

      /* Product: '<S27>/Product' */
      rtDW->Gain1 *= rtDW->a;

      /* Gain: '<S27>/Gain2' incorporates:
       *  Delay: '<S27>/Delay'
       *  Sum: '<S27>/Sum2'
       */
      rtDW->Gain2_n *= rtDW->Gain1 + rtDW->Delay_DSTATE_m;

      /* DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' */
      DiscreteTimeIntegrator1_n = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_DSTA_i0;

      /* Sum: '<S27>/Sum6' */
      rtDW->U_im_g = rtDW->Gain1 + DiscreteTimeIntegrator1_n;

      /* MATLAB Function: '<S27>/MATLAB Function' incorporates:
       *  Constant: '<S27>/Constant2'
       *  Product: '<S27>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_c, 0.425F * DiscreteTimeIntegrator,
                       rtb_Betrieb_l, rtDW->U_im_g, &rtDW->re_lim_d,
                       &rtDW->im_lim_c);

      /* Product: '<S27>/Product3' incorporates:
       *  Product: '<S27>/Product4'
       *  Trigonometry: '<S27>/Cos1'
       */
      rtDW->Product3_fd = cosf(rtDW->U_FA) * rtDW->re_lim_d;

      /* Product: '<S25>/Product4' incorporates:
       *  Constant: '<S25>/Constant1'
       */
      rtDW->Product4_k = rtDW->U_FA * 2.0F;

      /* Product: '<S25>/Product5' incorporates:
       *  Constant: '<S25>/Constant1'
       *  Inport: '<Root>/Act_theta_u_el'
       */
      rtDW->Gain1 = rtU->Act_theta_u_el * 2.0F;

      /* Gain: '<S25>/Gain4' */
      rtDW->a = rtP.K2 * rtDW->Gain4_i;

      /* Gain: '<S25>/Gain1' incorporates:
       *  Delay: '<S25>/Delay1'
       *  Product: '<S25>/Product1'
       *  Sum: '<S25>/Sum4'
       *  Trigonometry: '<S25>/Cos'
       */
      rtDW->Gain1_cp = (cosf(rtDW->Gain1) * rtDW->a + rtDW->Delay1_DSTATE_b) *
        rtP.T_R;

      /* DiscreteIntegrator: '<S25>/Discrete-Time Integrator' */
      U_re_k = 0.5F * rtDW->Gain1_cp + rtDW->DiscreteTimeIntegrator_DSTATE_n;

      /* Gain: '<S25>/Gain2' incorporates:
       *  Delay: '<S25>/Delay'
       *  Gain: '<S25>/Gain'
       *  Product: '<S25>/Product'
       *  Sum: '<S25>/Sum2'
       *  Trigonometry: '<S25>/Sin'
       */
      rtDW->Gain2_i = (rtDW->a * -sinf(rtDW->Gain1) + rtDW->Delay_DSTATE_al) *
        rtP.T_R;

      /* DiscreteIntegrator: '<S25>/Discrete-Time Integrator1' */
      U_im_a = 0.5F * rtDW->Gain2_i + rtDW->DiscreteTimeIntegrator1_DSTAT_k;

      /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
       *  Constant: '<S25>/Constant'
       *  Product: '<S25>/Product6'
       */
      MATLABFunction_f(U_re_k, 0.0025F * DiscreteTimeIntegrator, U_im_a,
                       &rtDW->a, &rtDW->im_lim_b);

      /* Product: '<S25>/Product3' incorporates:
       *  Trigonometry: '<S25>/Cos1'
       */
      rtDW->Product3_b = cosf(rtDW->Product4_k) * rtDW->a;

      /* Product: '<S25>/Product2' incorporates:
       *  Gain: '<S25>/Gain3'
       *  Trigonometry: '<S25>/Sin1'
       */
      rtb_Product2_o = rtDW->im_lim_b * -sinf(rtDW->Product4_k);

      /* Product: '<S26>/Product4' incorporates:
       *  Constant: '<S26>/Constant1'
       */
      rtDW->Product4_k = rtDW->U_FA * 3.0F;

      /* Product: '<S26>/Product5' incorporates:
       *  Constant: '<S26>/Constant1'
       *  Inport: '<Root>/Act_theta_u_el'
       */
      rtDW->Gain1 = rtU->Act_theta_u_el * 3.0F;

      /* Gain: '<S26>/Gain4' */
      rtDW->Gain4_i *= rtP.K3;

      /* Gain: '<S26>/Gain1' incorporates:
       *  Delay: '<S26>/Delay1'
       *  Product: '<S26>/Product1'
       *  Sum: '<S26>/Sum4'
       *  Trigonometry: '<S26>/Cos'
       */
      rtb_Gain1_b = (cosf(rtDW->Gain1) * rtDW->Gain4_i + rtDW->Delay1_DSTATE_i) *
        rtP.T_R;

      /* DiscreteIntegrator: '<S26>/Discrete-Time Integrator' */
      U_re_ky = 0.5F * rtb_Gain1_b + rtDW->DiscreteTimeIntegrator_DSTATE_l;

      /* Delay: '<S26>/Delay' */
      y_i = rtDW->Delay_DSTATE_d;

      /* Gain: '<S26>/Gain2' incorporates:
       *  Delay: '<S26>/Delay'
       *  Gain: '<S26>/Gain'
       *  Product: '<S26>/Product'
       *  Sum: '<S26>/Sum2'
       *  Trigonometry: '<S26>/Sin'
       */
      rtDW->Gain4_i = (rtDW->Gain4_i * -sinf(rtDW->Gain1) + rtDW->Delay_DSTATE_d)
        * rtP.T_R;

      /* DiscreteIntegrator: '<S26>/Discrete-Time Integrator1' */
      U_im_c = 0.5F * rtDW->Gain4_i + rtDW->DiscreteTimeIntegrator1_DSTA_iy;

      /* MATLAB Function: '<S26>/MATLAB Function' incorporates:
       *  Constant: '<S26>/Constant'
       *  Product: '<S26>/Product6'
       */
      MATLABFunction_f(U_re_ky, 0.04F * DiscreteTimeIntegrator, U_im_c, &y_i,
                       &rtDW->Gain1);

      /* Outport: '<Root>/a_U' incorporates:
       *  Constant: '<S15>/Constant1'
       *  Gain: '<S26>/Gain3'
       *  Gain: '<S27>/Gain3'
       *  Product: '<S15>/Divide'
       *  Product: '<S26>/Product2'
       *  Product: '<S26>/Product3'
       *  Product: '<S27>/Product2'
       *  Product: '<S27>/Product4'
       *  Sum: '<S15>/Add'
       *  Sum: '<S21>/Add'
       *  Sum: '<S25>/Sum'
       *  Sum: '<S26>/Sum'
       *  Sum: '<S27>/Sum'
       *  Trigonometry: '<S26>/Cos1'
       *  Trigonometry: '<S26>/Sin1'
       *  Trigonometry: '<S27>/Sin1'
       */
      rtY->a_U = (((rtDW->im_lim_c * -sinf(rtDW->U_FA) + rtDW->Product3_fd) +
                   (rtDW->Product3_b + rtb_Product2_o)) + (cosf(rtDW->Product4_k)
        * y_i + rtDW->Gain1 * -sinf(rtDW->Product4_k))) / DiscreteTimeIntegrator
        + 0.5F;

      /* Merge: '<S7>/Merge3' incorporates:
       *  SignalConversion generated from: '<S15>/Iu_ref'
       */
      rtDW->Merge3 = rtDW->b;

      /* Update for UnitDelay generated from: '<S22>/UD' incorporates:
       *  Inport: '<Root>/Act_theta_u_el'
       *
       * Block description for UnitDelay generated from '<S22>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->UD_1_DSTATE_c = rtU->Act_theta_u_el;

      /* Update for UnitDelay generated from: '<S22>/UD'
       *
       * Block description for UnitDelay generated from '<S22>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->UD_2_DSTATE_at = rtDW->U_FA;

      /* Update for Delay: '<S27>/Delay1' incorporates:
       *  Sum: '<S27>/Sum3'
       */
      rtDW->Delay1_DSTATE_d = rtDW->re_lim_d - rtDW->U_re_c;

      /* Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTAT_oq = 0.5F * rtDW->y + rtDW->Switch2;

      /* Update for Delay: '<S27>/Delay' incorporates:
       *  Sum: '<S27>/Sum1'
       */
      rtDW->Delay_DSTATE_m = rtDW->im_lim_c - rtDW->U_im_g;

      /* Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTA_i0 = 0.5F * rtDW->Gain2_n +
        DiscreteTimeIntegrator1_n;

      /* Update for Delay: '<S25>/Delay1' incorporates:
       *  Sum: '<S25>/Sum3'
       */
      rtDW->Delay1_DSTATE_b = rtDW->a - U_re_k;

      /* Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_n = 0.5F * rtDW->Gain1_cp + U_re_k;

      /* Update for Delay: '<S25>/Delay' incorporates:
       *  Sum: '<S25>/Sum1'
       */
      rtDW->Delay_DSTATE_al = rtDW->im_lim_b - U_im_a;

      /* Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_k = 0.5F * rtDW->Gain2_i + U_im_a;

      /* Update for Delay: '<S26>/Delay1' incorporates:
       *  Sum: '<S26>/Sum3'
       */
      rtDW->Delay1_DSTATE_i = y_i - U_re_ky;

      /* Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.5F * rtb_Gain1_b + U_re_ky;

      /* Update for Delay: '<S26>/Delay' incorporates:
       *  Sum: '<S26>/Sum1'
       */
      rtDW->Delay_DSTATE_d = rtDW->Gain1 - U_im_c;

      /* Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTA_iy = 0.5F * rtDW->Gain4_i + U_im_c;

      /* End of Outputs for SubSystem: '<S7>/Strang U' */
    } else {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* Outport: '<Root>/a_U' */
      SwitchCaseActionSubsystem(&rtY->a_U, &rtDW->Merge3);

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem' */
    }

    /* End of SwitchCase: '<S7>/Switch Case' */

    /* SwitchCase: '<S7>/Switch Case1' */
    rtPrevAction = rtDW->SwitchCase1_ActiveSubsystem;
    switch (rtU->fl_power) {
     case 2:
     case 3:
      rtAction = 0;
      break;

     default:
      rtAction = 1;
      break;
    }

    rtDW->SwitchCase1_ActiveSubsystem = rtAction;
    if (rtAction == 0) {
      if (0 != rtPrevAction) {
        /* InitializeConditions for IfAction SubSystem: '<S7>/Strang V' incorporates:
         *  ActionPort: '<S16>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S7>/Switch Case1' incorporates:
         *  Delay: '<S35>/Delay'
         *  Delay: '<S35>/Delay1'
         *  Delay: '<S36>/Delay'
         *  Delay: '<S36>/Delay1'
         *  Delay: '<S37>/Delay'
         *  Delay: '<S37>/Delay1'
         *  DiscreteIntegrator: '<S35>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S35>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S36>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S36>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S37>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S37>/Discrete-Time Integrator1'
         *  UnitDelay generated from: '<S32>/UD'
         *
         * Block description for UnitDelay generated from '<S32>/UD':
         *
         *  Store in Global RAM
         */
        rtDW->UD_1_DSTATE_i = 0.0F;
        rtDW->UD_2_DSTATE_a = 0.0F;
        rtDW->Delay1_DSTATE_a = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_i = 0.0F;
        rtDW->Delay_DSTATE_g = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_h = 0.0F;
        rtDW->Delay1_DSTATE_k3 = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;
        rtDW->Delay_DSTATE_i = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_e = 0.0F;
        rtDW->Delay1_DSTATE_n = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTAT_a3 = 0.0F;
        rtDW->Delay_DSTATE_gj = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_i = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S7>/Strang V' */
      }

      /* Outputs for IfAction SubSystem: '<S7>/Strang V' incorporates:
       *  ActionPort: '<S16>/Action Port'
       */
      /* Sum: '<S16>/Sum1' incorporates:
       *  Constant: '<S16>/Constant'
       */
      rtDW->a = rtDW->U_FA + rtP.Offset_V;

      /* Sum: '<S16>/Sum' incorporates:
       *  Constant: '<S16>/Constant'
       *  Inport: '<Root>/Act_theta_u_el'
       */
      rtDW->b = rtU->Act_theta_u_el + rtP.Offset_V;

      /* Sum: '<S32>/Diff' incorporates:
       *  UnitDelay generated from: '<S32>/UD'
       *
       * Block description for '<S32>/Diff':
       *
       *  Add in CPU
       *
       * Block description for UnitDelay generated from '<S32>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->Diff_i[0] = rtDW->b - rtDW->UD_1_DSTATE_i;
      rtDW->Diff_i[1] = rtDW->a - rtDW->UD_2_DSTATE_a;

      /* MATLAB Function: '<S31>/MATLAB Function' */
      MATLABFunction(rtDW->I_im, rtDW->Diff_i, &rtb_Betrieb_l);

      /* Sum: '<S34>/Sum' incorporates:
       *  Gain: '<S34>/Gain'
       *  Product: '<S34>/Product'
       *  Product: '<S34>/Product1'
       *  Trigonometry: '<S34>/Cos'
       *  Trigonometry: '<S34>/Cos1'
       */
      y_i = rtDW->I_re * cosf(rtDW->b) + rtDW->I_im * -sinf(rtDW->b);

      /* Sum: '<S31>/Sum' incorporates:
       *  Inport: '<Root>/Act_Iv'
       */
      rtDW->Gain1_cp = y_i - rtU->Act_Iv;

      /* Gain: '<S37>/Gain6' */
      rtDW->y = rtP.Kp * rtDW->Gain1_cp;

      /* Product: '<S37>/Product1' incorporates:
       *  Product: '<S37>/Product5'
       *  Trigonometry: '<S37>/Cos'
       */
      rtDW->Switch2 = cosf(rtDW->b) * rtDW->y;

      /* Gain: '<S37>/Gain1' incorporates:
       *  Delay: '<S37>/Delay1'
       *  Gain: '<S37>/Gain2'
       *  Sum: '<S37>/Sum4'
       */
      rtDW->Gain1 = rtP.T_R * rtP.K1;
      rtDW->U_re_c = rtDW->Gain1 * (rtDW->Delay1_DSTATE_a + rtDW->Switch2);

      /* DiscreteIntegrator: '<S37>/Discrete-Time Integrator' */
      rtDW->Gain2_n = 0.5F * rtDW->U_re_c +
        rtDW->DiscreteTimeIntegrator_DSTATE_i;

      /* Sum: '<S37>/Sum5' */
      DiscreteTimeIntegrator1_n = rtDW->Gain2_n + rtDW->Switch2;

      /* Product: '<S37>/Product' incorporates:
       *  Gain: '<S37>/Gain'
       *  Product: '<S37>/Product5'
       *  Trigonometry: '<S37>/Sin'
       */
      rtDW->y *= -sinf(rtDW->b);

      /* Gain: '<S37>/Gain2' incorporates:
       *  Delay: '<S37>/Delay'
       *  Sum: '<S37>/Sum2'
       */
      rtDW->U_im_g = rtDW->Gain1 * (rtDW->y + rtDW->Delay_DSTATE_g);

      /* DiscreteIntegrator: '<S37>/Discrete-Time Integrator1' */
      rtDW->re_lim_d = 0.5F * rtDW->U_im_g +
        rtDW->DiscreteTimeIntegrator1_DSTAT_h;

      /* Sum: '<S37>/Sum6' */
      rtDW->im_lim_c = rtDW->y + rtDW->re_lim_d;

      /* MATLAB Function: '<S37>/MATLAB Function' incorporates:
       *  Constant: '<S37>/Constant2'
       *  Product: '<S37>/Product6'
       */
      MATLABFunction_a(DiscreteTimeIntegrator1_n, 0.425F *
                       DiscreteTimeIntegrator, rtb_Betrieb_l, rtDW->im_lim_c,
                       &rtDW->Product4_k, &rtDW->Product3_fd);

      /* Product: '<S35>/Product4' incorporates:
       *  Constant: '<S35>/Constant1'
       */
      U_re_k = rtDW->a * 2.0F;

      /* Product: '<S35>/Product5' incorporates:
       *  Constant: '<S35>/Constant1'
       */
      rtDW->y = rtDW->b * 2.0F;

      /* Gain: '<S35>/Gain4' */
      rtDW->Gain1 = rtP.K2 * rtDW->Gain1_cp;

      /* Gain: '<S35>/Gain1' incorporates:
       *  Delay: '<S35>/Delay1'
       *  Product: '<S35>/Product1'
       *  Sum: '<S35>/Sum4'
       *  Trigonometry: '<S35>/Cos'
       */
      rtDW->Gain2_i = (cosf(rtDW->y) * rtDW->Gain1 + rtDW->Delay1_DSTATE_k3) *
        rtP.T_R;

      /* DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
      U_im_a = 0.5F * rtDW->Gain2_i + rtDW->DiscreteTimeIntegrator_DSTATE_g;

      /* Gain: '<S35>/Gain2' incorporates:
       *  Delay: '<S35>/Delay'
       *  Gain: '<S35>/Gain'
       *  Product: '<S35>/Product'
       *  Sum: '<S35>/Sum2'
       *  Trigonometry: '<S35>/Sin'
       */
      rtDW->im_lim_b = (rtDW->Gain1 * -sinf(rtDW->y) + rtDW->Delay_DSTATE_i) *
        rtP.T_R;

      /* DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
      rtDW->Product3_b = 0.5F * rtDW->im_lim_b +
        rtDW->DiscreteTimeIntegrator1_DSTAT_e;

      /* MATLAB Function: '<S35>/MATLAB Function' incorporates:
       *  Constant: '<S35>/Constant'
       *  Product: '<S35>/Product6'
       */
      MATLABFunction_f(U_im_a, 0.0025F * DiscreteTimeIntegrator,
                       rtDW->Product3_b, &rtDW->Gain1, &rtb_Product2_o);

      /* Product: '<S35>/Product3' incorporates:
       *  Trigonometry: '<S35>/Cos1'
       */
      rtb_Gain1_b = cosf(U_re_k) * rtDW->Gain1;

      /* Product: '<S35>/Product2' incorporates:
       *  Gain: '<S35>/Gain3'
       *  Trigonometry: '<S35>/Sin1'
       */
      U_re_ky = rtb_Product2_o * -sinf(U_re_k);

      /* Product: '<S36>/Product4' incorporates:
       *  Constant: '<S36>/Constant1'
       */
      U_re_k = rtDW->a * 3.0F;

      /* Product: '<S36>/Product5' incorporates:
       *  Constant: '<S36>/Constant1'
       */
      rtDW->y = rtDW->b * 3.0F;

      /* Gain: '<S36>/Gain4' */
      rtDW->Gain1_cp *= rtP.K3;

      /* Gain: '<S36>/Gain1' incorporates:
       *  Delay: '<S36>/Delay1'
       *  Product: '<S36>/Product1'
       *  Sum: '<S36>/Sum4'
       *  Trigonometry: '<S36>/Cos'
       */
      rtDW->Gain4_i = (cosf(rtDW->y) * rtDW->Gain1_cp + rtDW->Delay1_DSTATE_n) *
        rtP.T_R;

      /* DiscreteIntegrator: '<S36>/Discrete-Time Integrator' */
      U_im_c = 0.5F * rtDW->Gain4_i + rtDW->DiscreteTimeIntegrator_DSTAT_a3;

      /* Delay: '<S36>/Delay' */
      rtDW->Switch2 = rtDW->Delay_DSTATE_gj;

      /* Gain: '<S36>/Gain2' incorporates:
       *  Delay: '<S36>/Delay'
       *  Gain: '<S36>/Gain'
       *  Product: '<S36>/Product'
       *  Sum: '<S36>/Sum2'
       *  Trigonometry: '<S36>/Sin'
       */
      rtDW->Gain1_cp = (rtDW->Gain1_cp * -sinf(rtDW->y) + rtDW->Delay_DSTATE_gj)
        * rtP.T_R;

      /* DiscreteIntegrator: '<S36>/Discrete-Time Integrator1' */
      U_im_g = 0.5F * rtDW->Gain1_cp + rtDW->DiscreteTimeIntegrator1_DSTAT_i;

      /* MATLAB Function: '<S36>/MATLAB Function' incorporates:
       *  Constant: '<S36>/Constant'
       *  Product: '<S36>/Product6'
       */
      MATLABFunction_f(U_im_c, 0.04F * DiscreteTimeIntegrator, U_im_g,
                       &rtDW->Switch2, &rtDW->y);

      /* Outport: '<Root>/a_V' incorporates:
       *  Constant: '<S16>/Constant1'
       *  Gain: '<S36>/Gain3'
       *  Gain: '<S37>/Gain3'
       *  Product: '<S16>/Divide'
       *  Product: '<S36>/Product2'
       *  Product: '<S36>/Product3'
       *  Product: '<S37>/Product2'
       *  Product: '<S37>/Product3'
       *  Product: '<S37>/Product4'
       *  Sum: '<S16>/Add'
       *  Sum: '<S31>/Add'
       *  Sum: '<S35>/Sum'
       *  Sum: '<S36>/Sum'
       *  Sum: '<S37>/Sum'
       *  Trigonometry: '<S36>/Cos1'
       *  Trigonometry: '<S36>/Sin1'
       *  Trigonometry: '<S37>/Cos1'
       *  Trigonometry: '<S37>/Sin1'
       */
      rtY->a_V = (((cosf(rtDW->a) * rtDW->Product4_k + rtDW->Product3_fd * -sinf
                    (rtDW->a)) + (rtb_Gain1_b + U_re_ky)) + (cosf(U_re_k) *
        rtDW->Switch2 + rtDW->y * -sinf(U_re_k))) / DiscreteTimeIntegrator +
        0.5F;

      /* Merge: '<S7>/Merge4' incorporates:
       *  SignalConversion generated from: '<S16>/Iv_ref'
       */
      rtDW->Merge4 = y_i;

      /* Update for UnitDelay generated from: '<S32>/UD'
       *
       * Block description for UnitDelay generated from '<S32>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->UD_1_DSTATE_i = rtDW->b;

      /* Update for UnitDelay generated from: '<S32>/UD'
       *
       * Block description for UnitDelay generated from '<S32>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->UD_2_DSTATE_a = rtDW->a;

      /* Update for Delay: '<S37>/Delay1' incorporates:
       *  Sum: '<S37>/Sum3'
       */
      rtDW->Delay1_DSTATE_a = rtDW->Product4_k - DiscreteTimeIntegrator1_n;

      /* Update for DiscreteIntegrator: '<S37>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_i = 0.5F * rtDW->U_re_c +
        rtDW->Gain2_n;

      /* Update for Delay: '<S37>/Delay' incorporates:
       *  Sum: '<S37>/Sum1'
       */
      rtDW->Delay_DSTATE_g = rtDW->Product3_fd - rtDW->im_lim_c;

      /* Update for DiscreteIntegrator: '<S37>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_h = 0.5F * rtDW->U_im_g +
        rtDW->re_lim_d;

      /* Update for Delay: '<S35>/Delay1' incorporates:
       *  Sum: '<S35>/Sum3'
       */
      rtDW->Delay1_DSTATE_k3 = rtDW->Gain1 - U_im_a;

      /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.5F * rtDW->Gain2_i + U_im_a;

      /* Update for Delay: '<S35>/Delay' incorporates:
       *  Sum: '<S35>/Sum1'
       */
      rtDW->Delay_DSTATE_i = rtb_Product2_o - rtDW->Product3_b;

      /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_e = 0.5F * rtDW->im_lim_b +
        rtDW->Product3_b;

      /* Update for Delay: '<S36>/Delay1' incorporates:
       *  Sum: '<S36>/Sum3'
       */
      rtDW->Delay1_DSTATE_n = rtDW->Switch2 - U_im_c;

      /* Update for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTAT_a3 = 0.5F * rtDW->Gain4_i + U_im_c;

      /* Update for Delay: '<S36>/Delay' incorporates:
       *  Sum: '<S36>/Sum1'
       */
      rtDW->Delay_DSTATE_gj = rtDW->y - U_im_g;

      /* Update for DiscreteIntegrator: '<S36>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_i = 0.5F * rtDW->Gain1_cp + U_im_g;

      /* End of Outputs for SubSystem: '<S7>/Strang V' */
    } else {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem1' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      /* Outport: '<Root>/a_V' */
      SwitchCaseActionSubsystem(&rtY->a_V, &rtDW->Merge4);

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem1' */
    }

    /* End of SwitchCase: '<S7>/Switch Case1' */

    /* SwitchCase: '<S7>/Switch Case2' */
    rtPrevAction = rtDW->SwitchCase2_ActiveSubsystem;
    if (rtU->fl_power == 3) {
      rtAction = 0;
    } else {
      rtAction = 1;
    }

    rtDW->SwitchCase2_ActiveSubsystem = rtAction;
    if (rtAction == 0) {
      if (0 != rtPrevAction) {
        /* InitializeConditions for IfAction SubSystem: '<S7>/Strang W' incorporates:
         *  ActionPort: '<S17>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S7>/Switch Case2' incorporates:
         *  Delay: '<S45>/Delay'
         *  Delay: '<S45>/Delay1'
         *  Delay: '<S46>/Delay'
         *  Delay: '<S46>/Delay1'
         *  Delay: '<S47>/Delay'
         *  Delay: '<S47>/Delay1'
         *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S46>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S46>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S47>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S47>/Discrete-Time Integrator1'
         *  UnitDelay generated from: '<S42>/UD'
         *
         * Block description for UnitDelay generated from '<S42>/UD':
         *
         *  Store in Global RAM
         */
        rtDW->UD_1_DSTATE = 0.0F;
        rtDW->UD_2_DSTATE = 0.0F;
        rtDW->Delay1_DSTATE = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;
        rtDW->Delay_DSTATE_a = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;
        rtDW->Delay1_DSTATE_k = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.0F;
        rtDW->Delay_DSTATE_ja = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_n = 0.0F;
        rtDW->Delay1_DSTATE_e = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_e = 0.0F;
        rtDW->Delay_DSTATE_c = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_l = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S7>/Strang W' */
      }

      /* Outputs for IfAction SubSystem: '<S7>/Strang W' incorporates:
       *  ActionPort: '<S17>/Action Port'
       */
      /* Sum: '<S17>/Sum1' incorporates:
       *  Constant: '<S17>/Constant'
       */
      rtDW->U_FA += rtP.Offset_W;

      /* Sum: '<S17>/Sum' incorporates:
       *  Constant: '<S17>/Constant'
       *  Inport: '<Root>/Act_theta_u_el'
       */
      rtDW->a = rtU->Act_theta_u_el + rtP.Offset_W;

      /* Sum: '<S42>/Diff' incorporates:
       *  UnitDelay generated from: '<S42>/UD'
       *
       * Block description for '<S42>/Diff':
       *
       *  Add in CPU
       *
       * Block description for UnitDelay generated from '<S42>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->Diff_i[0] = rtDW->a - rtDW->UD_1_DSTATE;
      rtDW->Diff_i[1] = rtDW->U_FA - rtDW->UD_2_DSTATE;

      /* MATLAB Function: '<S41>/MATLAB Function' */
      MATLABFunction(rtDW->I_im, rtDW->Diff_i, &rtb_Betrieb_l);

      /* Sum: '<S44>/Sum' incorporates:
       *  Gain: '<S44>/Gain'
       *  Product: '<S44>/Product'
       *  Product: '<S44>/Product1'
       *  Trigonometry: '<S44>/Cos'
       *  Trigonometry: '<S44>/Cos1'
       */
      rtDW->Gain1 = rtDW->I_re * cosf(rtDW->a) + rtDW->I_im * -sinf(rtDW->a);

      /* Sum: '<S41>/Sum' incorporates:
       *  Inport: '<Root>/Act_Iw'
       */
      U_im_c = rtDW->Gain1 - rtU->Act_Iw;

      /* Gain: '<S47>/Gain6' */
      y_i = rtP.Kp * U_im_c;

      /* Product: '<S47>/Product1' incorporates:
       *  Product: '<S47>/Product5'
       *  Trigonometry: '<S47>/Cos'
       */
      rtDW->y = cosf(rtDW->a) * y_i;

      /* Gain: '<S47>/Gain1' incorporates:
       *  Delay: '<S47>/Delay1'
       *  Gain: '<S47>/Gain2'
       *  Sum: '<S47>/Sum4'
       */
      rtDW->b = rtP.T_R * rtP.K1;
      rtDW->Switch2 = rtDW->b * (rtDW->Delay1_DSTATE + rtDW->y);

      /* DiscreteIntegrator: '<S47>/Discrete-Time Integrator' */
      rtDW->U_re_c = 0.5F * rtDW->Switch2 +
        rtDW->DiscreteTimeIntegrator_DSTATE_o;

      /* Sum: '<S47>/Sum5' */
      rtDW->Gain2_n = rtDW->U_re_c + rtDW->y;

      /* Product: '<S47>/Product' incorporates:
       *  Gain: '<S47>/Gain'
       *  Product: '<S47>/Product5'
       *  Trigonometry: '<S47>/Sin'
       */
      y_i *= -sinf(rtDW->a);

      /* Gain: '<S47>/Gain2' incorporates:
       *  Delay: '<S47>/Delay'
       *  Sum: '<S47>/Sum2'
       */
      DiscreteTimeIntegrator1_n = rtDW->b * (y_i + rtDW->Delay_DSTATE_a);

      /* DiscreteIntegrator: '<S47>/Discrete-Time Integrator1' */
      rtDW->U_im_g = 0.5F * DiscreteTimeIntegrator1_n +
        rtDW->DiscreteTimeIntegrator1_DSTATE;

      /* Sum: '<S47>/Sum6' */
      rtDW->re_lim_d = y_i + rtDW->U_im_g;

      /* MATLAB Function: '<S47>/MATLAB Function' incorporates:
       *  Constant: '<S47>/Constant2'
       *  Product: '<S47>/Product6'
       */
      MATLABFunction_a(rtDW->Gain2_n, 0.425F * DiscreteTimeIntegrator,
                       rtb_Betrieb_l, rtDW->re_lim_d, &rtDW->im_lim_c,
                       &rtDW->Product4_k);

      /* Product: '<S45>/Product4' incorporates:
       *  Constant: '<S45>/Constant1'
       */
      rtDW->Product3_fd = rtDW->U_FA * 2.0F;

      /* Product: '<S45>/Product5' incorporates:
       *  Constant: '<S45>/Constant1'
       */
      y_i = rtDW->a * 2.0F;

      /* Gain: '<S45>/Gain4' */
      rtDW->b = rtP.K2 * U_im_c;

      /* Gain: '<S45>/Gain1' incorporates:
       *  Delay: '<S45>/Delay1'
       *  Product: '<S45>/Product1'
       *  Sum: '<S45>/Sum4'
       *  Trigonometry: '<S45>/Cos'
       */
      U_re_k = (cosf(y_i) * rtDW->b + rtDW->Delay1_DSTATE_k) * rtP.T_R;

      /* DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
      rtDW->Gain2_i = 0.5F * U_re_k + rtDW->DiscreteTimeIntegrator_DSTATE_f;

      /* Gain: '<S45>/Gain2' incorporates:
       *  Delay: '<S45>/Delay'
       *  Gain: '<S45>/Gain'
       *  Product: '<S45>/Product'
       *  Sum: '<S45>/Sum2'
       *  Trigonometry: '<S45>/Sin'
       */
      U_im_a = (rtDW->b * -sinf(y_i) + rtDW->Delay_DSTATE_ja) * rtP.T_R;

      /* DiscreteIntegrator: '<S45>/Discrete-Time Integrator1' */
      rtDW->im_lim_b = 0.5F * U_im_a + rtDW->DiscreteTimeIntegrator1_DSTAT_n;

      /* MATLAB Function: '<S45>/MATLAB Function' incorporates:
       *  Constant: '<S45>/Constant'
       *  Product: '<S45>/Product6'
       */
      MATLABFunction_f(rtDW->Gain2_i, 0.0025F * DiscreteTimeIntegrator,
                       rtDW->im_lim_b, &rtDW->b, &rtDW->Product3_b);

      /* Product: '<S45>/Product3' incorporates:
       *  Trigonometry: '<S45>/Cos1'
       */
      rtb_Product2_o = cosf(rtDW->Product3_fd) * rtDW->b;

      /* Product: '<S45>/Product2' incorporates:
       *  Gain: '<S45>/Gain3'
       *  Trigonometry: '<S45>/Sin1'
       */
      rtb_Gain1_b = rtDW->Product3_b * -sinf(rtDW->Product3_fd);

      /* Product: '<S46>/Product4' incorporates:
       *  Constant: '<S46>/Constant1'
       */
      rtDW->Product3_fd = rtDW->U_FA * 3.0F;

      /* Product: '<S46>/Product5' incorporates:
       *  Constant: '<S46>/Constant1'
       */
      y_i = rtDW->a * 3.0F;

      /* Gain: '<S46>/Gain4' */
      U_im_c *= rtP.K3;

      /* Gain: '<S46>/Gain1' incorporates:
       *  Delay: '<S46>/Delay1'
       *  Product: '<S46>/Product1'
       *  Sum: '<S46>/Sum4'
       *  Trigonometry: '<S46>/Cos'
       */
      U_re_ky = (cosf(y_i) * U_im_c + rtDW->Delay1_DSTATE_e) * rtP.T_R;

      /* DiscreteIntegrator: '<S46>/Discrete-Time Integrator' */
      rtDW->Gain4_i = 0.5F * U_re_ky + rtDW->DiscreteTimeIntegrator_DSTATE_e;

      /* Delay: '<S46>/Delay' */
      rtDW->y = rtDW->Delay_DSTATE_c;

      /* Gain: '<S46>/Gain2' incorporates:
       *  Delay: '<S46>/Delay'
       *  Gain: '<S46>/Gain'
       *  Product: '<S46>/Product'
       *  Sum: '<S46>/Sum2'
       *  Trigonometry: '<S46>/Sin'
       */
      U_im_c = (U_im_c * -sinf(y_i) + rtDW->Delay_DSTATE_c) * rtP.T_R;

      /* DiscreteIntegrator: '<S46>/Discrete-Time Integrator1' */
      rtDW->Gain1_cp = 0.5F * U_im_c + rtDW->DiscreteTimeIntegrator1_DSTAT_l;

      /* MATLAB Function: '<S46>/MATLAB Function' incorporates:
       *  Constant: '<S46>/Constant'
       *  Product: '<S46>/Product6'
       */
      MATLABFunction_f(rtDW->Gain4_i, 0.04F * DiscreteTimeIntegrator,
                       rtDW->Gain1_cp, &rtDW->y, &y_i);

      /* Outport: '<Root>/a_W' incorporates:
       *  Constant: '<S17>/Constant1'
       *  Gain: '<S46>/Gain3'
       *  Gain: '<S47>/Gain3'
       *  Product: '<S17>/Divide'
       *  Product: '<S46>/Product2'
       *  Product: '<S46>/Product3'
       *  Product: '<S47>/Product2'
       *  Product: '<S47>/Product3'
       *  Product: '<S47>/Product4'
       *  Sum: '<S17>/Add'
       *  Sum: '<S41>/Add'
       *  Sum: '<S45>/Sum'
       *  Sum: '<S46>/Sum'
       *  Sum: '<S47>/Sum'
       *  Trigonometry: '<S46>/Cos1'
       *  Trigonometry: '<S46>/Sin1'
       *  Trigonometry: '<S47>/Cos1'
       *  Trigonometry: '<S47>/Sin1'
       */
      rtY->a_W = (((cosf(rtDW->U_FA) * rtDW->im_lim_c + rtDW->Product4_k * -sinf
                    (rtDW->U_FA)) + (rtb_Product2_o + rtb_Gain1_b)) + (cosf
        (rtDW->Product3_fd) * rtDW->y + y_i * -sinf(rtDW->Product3_fd))) /
        DiscreteTimeIntegrator + 0.5F;

      /* Merge: '<S7>/Merge5' incorporates:
       *  SignalConversion generated from: '<S17>/Iw_ref'
       */
      rtDW->Merge5 = rtDW->Gain1;

      /* Update for UnitDelay generated from: '<S42>/UD'
       *
       * Block description for UnitDelay generated from '<S42>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->UD_1_DSTATE = rtDW->a;

      /* Update for UnitDelay generated from: '<S42>/UD'
       *
       * Block description for UnitDelay generated from '<S42>/UD':
       *
       *  Store in Global RAM
       */
      rtDW->UD_2_DSTATE = rtDW->U_FA;

      /* Update for Delay: '<S47>/Delay1' incorporates:
       *  Sum: '<S47>/Sum3'
       */
      rtDW->Delay1_DSTATE = rtDW->im_lim_c - rtDW->Gain2_n;

      /* Update for DiscreteIntegrator: '<S47>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.5F * rtDW->Switch2 +
        rtDW->U_re_c;

      /* Update for Delay: '<S47>/Delay' incorporates:
       *  Sum: '<S47>/Sum1'
       */
      rtDW->Delay_DSTATE_a = rtDW->Product4_k - rtDW->re_lim_d;

      /* Update for DiscreteIntegrator: '<S47>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * DiscreteTimeIntegrator1_n +
        rtDW->U_im_g;

      /* Update for Delay: '<S45>/Delay1' incorporates:
       *  Sum: '<S45>/Sum3'
       */
      rtDW->Delay1_DSTATE_k = rtDW->b - rtDW->Gain2_i;

      /* Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.5F * U_re_k + rtDW->Gain2_i;

      /* Update for Delay: '<S45>/Delay' incorporates:
       *  Sum: '<S45>/Sum1'
       */
      rtDW->Delay_DSTATE_ja = rtDW->Product3_b - rtDW->im_lim_b;

      /* Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_n = 0.5F * U_im_a + rtDW->im_lim_b;

      /* Update for Delay: '<S46>/Delay1' incorporates:
       *  Sum: '<S46>/Sum3'
       */
      rtDW->Delay1_DSTATE_e = rtDW->y - rtDW->Gain4_i;

      /* Update for DiscreteIntegrator: '<S46>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_e = 0.5F * U_re_ky + rtDW->Gain4_i;

      /* Update for Delay: '<S46>/Delay' incorporates:
       *  Sum: '<S46>/Sum1'
       */
      rtDW->Delay_DSTATE_c = y_i - rtDW->Gain1_cp;

      /* Update for DiscreteIntegrator: '<S46>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_l = 0.5F * U_im_c + rtDW->Gain1_cp;

      /* End of Outputs for SubSystem: '<S7>/Strang W' */
    } else {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem2' incorporates:
       *  ActionPort: '<S20>/Action Port'
       */
      /* Outport: '<Root>/a_W' */
      SwitchCaseActionSubsystem(&rtY->a_W, &rtDW->Merge5);

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem2' */
    }

    /* End of SwitchCase: '<S7>/Switch Case2' */
    /* End of Outputs for SubSystem: '<S1>/Regelung' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/aus' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    /* Outport: '<Root>/a_U' incorporates:
     *  Constant: '<S5>/Constant'
     *  SignalConversion generated from: '<S5>/a_U'
     */
    rtY->a_U = 0.5F;

    /* Outport: '<Root>/a_V' incorporates:
     *  Constant: '<S5>/Constant'
     *  SignalConversion generated from: '<S5>/a_V'
     */
    rtY->a_V = 0.5F;

    /* Outport: '<Root>/a_W' incorporates:
     *  Constant: '<S5>/Constant'
     *  SignalConversion generated from: '<S5>/a_W'
     */
    rtY->a_W = 0.5F;

    /* End of Outputs for SubSystem: '<S1>/aus' */
  }

  /* End of SwitchCase: '<S1>/switch_case_power' */

  /* Outport: '<Root>/I_re_Ref' */
  rtY->I_re_Ref = rtDW->I_re;

  /* Outport: '<Root>/I_im_Ref' */
  rtY->I_im_Ref = rtDW->I_im;

  /* Outport: '<Root>/Iu_ref' */
  rtY->Iu_ref = rtDW->Merge3;

  /* Outport: '<Root>/Iv_ref' */
  rtY->Iv_ref = rtDW->Merge4;

  /* Outport: '<Root>/Iw_ref' */
  rtY->Iw_ref = rtDW->Merge5;

  /* Outport: '<Root>/fault_peak_current_u' incorporates:
   *  Abs: '<S4>/Abs'
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/Act_Iu'
   *  RelationalOperator: '<S4>/Smaller'
   */
  rtY->fault_peak_current_u = (rtP.i_max_peak <= fabsf(rtU->Act_Iu));

  /* Math: '<S4>/Square' incorporates:
   *  Inport: '<Root>/Act_Iu'
   */
  rtDW->U_FA = rtU->Act_Iu * rtU->Act_Iu;

  /* DiscreteIntegrator: '<S52>/Accumulator' incorporates:
   *  Delay: '<S52>/Delay'
   *  Sum: '<S52>/Sum'
   */
  rtDW->a = (rtDW->U_FA - rtDW->Delay_DSTATE_k[0]) + rtDW->Accumulator_DSTATE;

  /* Outport: '<Root>/fault_rms_current_u' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Gain: '<S52>/Gain'
   *  RelationalOperator: '<S4>/Smaller1'
   *  Sqrt: '<S4>/Square Root'
   */
  rtY->fault_rms_current_u = (rtP.i_max_rms <= sqrtf(1.0F /
    rtP.max_current_samplenumber * rtDW->a));

  /* Outport: '<Root>/fault_peak_speed' incorporates:
   *  Constant: '<S4>/Constant2'
   *  Inport: '<Root>/Act_n'
   *  RelationalOperator: '<S4>/Smaller2'
   */
  rtY->fault_peak_speed = (rtP.n_max_peak <= rtU->Act_n);

  /* DiscreteIntegrator: '<S53>/Accumulator' incorporates:
   *  Delay: '<S53>/Delay'
   *  Inport: '<Root>/Act_n'
   *  Sum: '<S53>/Sum'
   */
  rtDW->b = (rtU->Act_n - rtDW->Delay_DSTATE_l[0]) + rtDW->Accumulator_DSTATE_k;

  /* Outport: '<Root>/fault_max_speed' incorporates:
   *  Constant: '<S4>/Constant3'
   *  Gain: '<S53>/Gain'
   *  RelationalOperator: '<S4>/Smaller3'
   */
  rtY->fault_max_speed = (rtP.n_max <= 1.0F / rtP.max_speed_samplenumber *
    rtDW->b);

  /* Math: '<S4>/Square1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   */
  rtDW->Gain1 = rtU->Act_Iv * rtU->Act_Iv;

  /* DiscreteIntegrator: '<S54>/Accumulator' incorporates:
   *  Delay: '<S54>/Delay'
   *  Sum: '<S54>/Sum'
   */
  y_i = (rtDW->Gain1 - rtDW->Delay_DSTATE_f[0]) + rtDW->Accumulator_DSTATE_g;

  /* Outport: '<Root>/fault_rms_current_v' incorporates:
   *  Constant: '<S4>/Constant5'
   *  Gain: '<S54>/Gain'
   *  RelationalOperator: '<S4>/Smaller5'
   *  Sqrt: '<S4>/Square Root1'
   */
  rtY->fault_rms_current_v = (rtP.i_max_rms <= sqrtf(1.0F /
    rtP.max_current_samplenumber * y_i));

  /* Math: '<S4>/Square2' incorporates:
   *  Inport: '<Root>/Act_Iw'
   */
  rtDW->y = rtU->Act_Iw * rtU->Act_Iw;

  /* DiscreteIntegrator: '<S55>/Accumulator' incorporates:
   *  Delay: '<S55>/Delay'
   *  Sum: '<S55>/Sum'
   */
  rtDW->Switch2 = (rtDW->y - rtDW->Delay_DSTATE_b[0]) +
    rtDW->Accumulator_DSTATE_f;

  /* Outport: '<Root>/fault_rms_current_w' incorporates:
   *  Constant: '<S4>/Constant7'
   *  Gain: '<S55>/Gain'
   *  RelationalOperator: '<S4>/Smaller7'
   *  Sqrt: '<S4>/Square Root2'
   */
  rtY->fault_rms_current_w = (rtP.i_max_rms <= sqrtf(1.0F /
    rtP.max_current_samplenumber * rtDW->Switch2));

  /* Outport: '<Root>/fault_peak_current_v' incorporates:
   *  Abs: '<S4>/Abs1'
   *  Constant: '<S4>/Constant4'
   *  Inport: '<Root>/Act_Iv'
   *  RelationalOperator: '<S4>/Smaller4'
   */
  rtY->fault_peak_current_v = (rtP.i_max_peak <= fabsf(rtU->Act_Iv));

  /* Outport: '<Root>/fault_peak_current_w' incorporates:
   *  Abs: '<S4>/Abs2'
   *  Constant: '<S4>/Constant6'
   *  Inport: '<Root>/Act_Iw'
   *  RelationalOperator: '<S4>/Smaller6'
   */
  rtY->fault_peak_current_w = (rtP.i_max_peak <= fabsf(rtU->Act_Iw));

  /* Update for Delay: '<S2>/Delay' */
  rtDW->Delay_DSTATE = DiscreteTimeIntegrator;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE = 0.5F * rtDW->Gain +
    DiscreteTimeIntegrator;

  /* Update for Delay: '<S52>/Delay' */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_k[rtDW->idxDelay] = rtDW->Delay_DSTATE_k[rtDW->idxDelay +
      1];
  }

  rtDW->Delay_DSTATE_k[19] = rtDW->U_FA;

  /* End of Update for Delay: '<S52>/Delay' */

  /* Update for DiscreteIntegrator: '<S52>/Accumulator' */
  rtDW->Accumulator_DSTATE = rtDW->a;

  /* Update for Delay: '<S53>/Delay' incorporates:
   *  Inport: '<Root>/Act_n'
   */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 119; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_l[rtDW->idxDelay] = rtDW->Delay_DSTATE_l[rtDW->idxDelay +
      1];
  }

  rtDW->Delay_DSTATE_l[119] = rtU->Act_n;

  /* End of Update for Delay: '<S53>/Delay' */

  /* Update for DiscreteIntegrator: '<S53>/Accumulator' */
  rtDW->Accumulator_DSTATE_k = rtDW->b;

  /* Update for DiscreteIntegrator: '<S54>/Accumulator' */
  rtDW->Accumulator_DSTATE_g = y_i;
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    /* Update for Delay: '<S54>/Delay' */
    rtDW->Delay_DSTATE_f[rtDW->idxDelay] = rtDW->Delay_DSTATE_f[rtDW->idxDelay +
      1];

    /* Update for Delay: '<S55>/Delay' */
    rtDW->Delay_DSTATE_b[rtDW->idxDelay] = rtDW->Delay_DSTATE_b[rtDW->idxDelay +
      1];
  }

  /* Update for Delay: '<S54>/Delay' */
  rtDW->Delay_DSTATE_f[19] = rtDW->Gain1;

  /* Update for Delay: '<S55>/Delay' */
  rtDW->Delay_DSTATE_b[19] = rtDW->y;

  /* Update for DiscreteIntegrator: '<S55>/Accumulator' */
  rtDW->Accumulator_DSTATE_f = rtDW->Switch2;
}

/* Model initialize function */
void Regelung_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtY *rtY = (ExtY *) rtM->outputs;
  ExtU *rtU = (ExtU *) rtM->inputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));

  /* Start for SwitchCase: '<S1>/switch_case_power' */
  rtDW->switch_case_power_ActiveSubsyst = -1;

  /* SystemInitialize for IfAction SubSystem: '<S1>/Regelung' */
  /* Start for SwitchCase: '<S3>/Switch Case' */
  rtDW->SwitchCase_ActiveSubsystem = -1;

  /* Start for SwitchCase: '<S7>/Switch Case' */
  rtDW->SwitchCase_ActiveSubsystem_f = -1;

  /* Start for SwitchCase: '<S7>/Switch Case1' */
  rtDW->SwitchCase1_ActiveSubsystem = -1;

  /* Start for SwitchCase: '<S7>/Switch Case2' */
  rtDW->SwitchCase2_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: '<S3>/Drehzahlregler' */
  /* InitializeConditions for Delay: '<S11>/Delay' */
  rtDW->Delay_DSTATE_p = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.0F;

  /* InitializeConditions for Delay: '<S6>/Delay' */
  rtDW->Delay_DSTATE_j = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S3>/Drehzahlregler' */

  /* SystemInitialize for Merge: '<S3>/Merge' */
  rtDW->I_re = 0.0F;

  /* SystemInitialize for Merge: '<S3>/Merge1' */
  rtDW->I_im = 0.0F;

  /* SystemInitialize for IfAction SubSystem: '<S7>/Strang U' */
  /* InitializeConditions for UnitDelay generated from: '<S22>/UD'
   *
   * Block description for UnitDelay generated from '<S22>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_1_DSTATE_c = 0.0F;

  /* InitializeConditions for UnitDelay generated from: '<S22>/UD'
   *
   * Block description for UnitDelay generated from '<S22>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_2_DSTATE_at = 0.0F;

  /* InitializeConditions for Delay: '<S27>/Delay1' */
  rtDW->Delay1_DSTATE_d = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTAT_oq = 0.0F;

  /* InitializeConditions for Delay: '<S27>/Delay' */
  rtDW->Delay_DSTATE_m = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTA_i0 = 0.0F;

  /* InitializeConditions for Delay: '<S25>/Delay1' */
  rtDW->Delay1_DSTATE_b = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_n = 0.0F;

  /* InitializeConditions for Delay: '<S25>/Delay' */
  rtDW->Delay_DSTATE_al = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0F;

  /* InitializeConditions for Delay: '<S26>/Delay1' */
  rtDW->Delay1_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.0F;

  /* InitializeConditions for Delay: '<S26>/Delay' */
  rtDW->Delay_DSTATE_d = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTA_iy = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S7>/Strang U' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/Strang V' */
  /* InitializeConditions for UnitDelay generated from: '<S32>/UD'
   *
   * Block description for UnitDelay generated from '<S32>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_1_DSTATE_i = 0.0F;

  /* InitializeConditions for UnitDelay generated from: '<S32>/UD'
   *
   * Block description for UnitDelay generated from '<S32>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_2_DSTATE_a = 0.0F;

  /* InitializeConditions for Delay: '<S37>/Delay1' */
  rtDW->Delay1_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S37>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_i = 0.0F;

  /* InitializeConditions for Delay: '<S37>/Delay' */
  rtDW->Delay_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S37>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_h = 0.0F;

  /* InitializeConditions for Delay: '<S35>/Delay1' */
  rtDW->Delay1_DSTATE_k3 = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;

  /* InitializeConditions for Delay: '<S35>/Delay' */
  rtDW->Delay_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_e = 0.0F;

  /* InitializeConditions for Delay: '<S36>/Delay1' */
  rtDW->Delay1_DSTATE_n = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTAT_a3 = 0.0F;

  /* InitializeConditions for Delay: '<S36>/Delay' */
  rtDW->Delay_DSTATE_gj = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S36>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_i = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S7>/Strang V' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/Strang W' */
  /* InitializeConditions for UnitDelay generated from: '<S42>/UD'
   *
   * Block description for UnitDelay generated from '<S42>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_1_DSTATE = 0.0F;

  /* InitializeConditions for UnitDelay generated from: '<S42>/UD'
   *
   * Block description for UnitDelay generated from '<S42>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_2_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S47>/Delay1' */
  rtDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;

  /* InitializeConditions for Delay: '<S47>/Delay' */
  rtDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S45>/Delay1' */
  rtDW->Delay1_DSTATE_k = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.0F;

  /* InitializeConditions for Delay: '<S45>/Delay' */
  rtDW->Delay_DSTATE_ja = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S45>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_n = 0.0F;

  /* InitializeConditions for Delay: '<S46>/Delay1' */
  rtDW->Delay1_DSTATE_e = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S46>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_e = 0.0F;

  /* InitializeConditions for Delay: '<S46>/Delay' */
  rtDW->Delay_DSTATE_c = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S46>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_l = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S7>/Strang W' */

  /* SystemInitialize for Merge: '<S7>/Merge5' */
  rtDW->Merge5 = 0.0F;

  /* SystemInitialize for Merge: '<S7>/Merge4' */
  rtDW->Merge4 = 0.0F;

  /* SystemInitialize for Merge: '<S7>/Merge3' */
  rtDW->Merge3 = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S1>/Regelung' */

  /* SystemInitialize for Outport: '<Root>/I_re_Ref' */
  rtY->I_re_Ref = rtDW->I_re;

  /* SystemInitialize for Outport: '<Root>/I_im_Ref' */
  rtY->I_im_Ref = rtDW->I_im;

  /* SystemInitialize for Outport: '<Root>/Iu_ref' */
  rtY->Iu_ref = rtDW->Merge3;

  /* SystemInitialize for Outport: '<Root>/Iv_ref' */
  rtY->Iv_ref = rtDW->Merge4;

  /* SystemInitialize for Outport: '<Root>/Iw_ref' */
  rtY->Iw_ref = rtDW->Merge5;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
