/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_komplex.c
 *
 * Code generated for Simulink model 'FOC_komplex'.
 *
 * Model version                  : 2.23
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Aug 24 11:49:34 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "FOC_komplex.h"

/* Model step function */
void FOC_komplex_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T DiscreteTimeIntegrator;
  real32_T rtb_Add1_k;
  real32_T rtb_Cos;
  real32_T rtb_Gain;
  real32_T rtb_Gain1_n;
  real32_T rtb_Gain2_l;
  real32_T rtb_Merge1;
  real32_T rtb_Sin;
  real32_T rtb_Switch2;
  real32_T rtb_alpha_j;
  real32_T rtb_q;
  real32_T rtb_theta_el_verwendet;
  real32_T rtb_u;
  real32_T rtb_y_h;
  real32_T y_i_k;
  int8_T rtAction;
  int8_T rtPrevAction;

  /* Gain: '<S3>/Gain' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Act_U_ZK'
   *  Sum: '<S3>/Sum'
   */
  rtb_Gain = rtP.T_R / 0.01F * (rtU->Act_U_ZK - rtDW->Delay_DSTATE);

  /* DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  DiscreteTimeIntegrator = 0.5F * rtb_Gain + rtDW->DiscreteTimeIntegrator_DSTATE;

  /* Gain: '<S33>/Gain' incorporates:
   *  Gain: '<S33>/Gain2'
   *  Inport: '<Root>/Act_Iu'
   *  Inport: '<Root>/Act_Iv'
   *  Inport: '<Root>/Act_Iw'
   *  Sum: '<S33>/Add'
   */
  rtb_alpha_j = ((2.0F * rtU->Act_Iu - rtU->Act_Iv) - rtU->Act_Iw) *
    0.333333343F;

  /* Trigonometry: '<S34>/Sin' incorporates:
   *  Inport: '<Root>/Act_theta_el'
   */
  rtb_Sin = sinf(rtU->Act_theta_el);

  /* Trigonometry: '<S34>/Cos' incorporates:
   *  Inport: '<Root>/Act_theta_el'
   */
  rtb_Cos = cosf(rtU->Act_theta_el);

  /* Gain: '<S33>/Gain1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   *  Inport: '<Root>/Act_Iw'
   *  Sum: '<S33>/Add1'
   */
  rtb_Add1_k = (rtU->Act_Iv - rtU->Act_Iw) * 0.577350259F;

  /* Sum: '<S34>/Add1' incorporates:
   *  Product: '<S34>/Product2'
   *  Product: '<S34>/Product3'
   */
  rtb_q = rtb_Cos * rtb_Add1_k - rtb_alpha_j * rtb_Sin;

  /* Sum: '<S34>/Add' incorporates:
   *  Product: '<S34>/Product'
   *  Product: '<S34>/Product1'
   */
  rtb_alpha_j = rtb_alpha_j * rtb_Cos + rtb_Sin * rtb_Add1_k;

  /* SwitchCase: '<S1>/switch_case_power' incorporates:
   *  Inport: '<Root>/fl_power'
   */
  rtPrevAction = rtDW->switch_case_power_ActiveSubsyst;
  if (rtU->fl_power == 1) {
    rtAction = 0;
  } else {
    rtAction = 1;
  }

  rtDW->switch_case_power_ActiveSubsyst = rtAction;
  if ((rtPrevAction != rtAction) && (rtPrevAction == 0)) {
    /* Disable for SwitchCase: '<S4>/Switch Case' */
    rtDW->SwitchCase_ActiveSubsystem = -1;
  }

  if (rtAction == 0) {
    if (0 != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/Regelung' incorporates:
       *  ActionPort: '<S4>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/switch_case_power' incorporates:
       *  Delay: '<S4>/Delay'
       *  Delay: '<S9>/Delay'
       *  Delay: '<S9>/Delay1'
       *  DiscreteIntegrator: '<S20>/Discrete-Time Integrator'
       *  DiscreteIntegrator: '<S21>/Discrete-Time Integrator'
       */
      rtDW->Delay_DSTATE_b = 0.0F;
      rtDW->Delay1_DSTATE = 0.0F;
      rtDW->DiscreteTimeIntegrator_DSTATE_k = 0.0F;
      rtDW->Delay_DSTATE_a = 0.0F;
      rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.0F;

      /* End of InitializeConditions for SubSystem: '<S1>/Regelung' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Regelung' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* SwitchCase: '<S4>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_control_type'
     */
    rtPrevAction = rtDW->SwitchCase_ActiveSubsystem;
    if (rtU->fl_control_type != 1) {
      rtAction = 1;
    }

    rtDW->SwitchCase_ActiveSubsystem = rtAction;
    if (rtAction == 0) {
      if (0 != rtPrevAction) {
        /* InitializeConditions for IfAction SubSystem: '<S4>/Drehzahlregler' incorporates:
         *  ActionPort: '<S8>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S4>/Switch Case' incorporates:
         *  Delay: '<S14>/Delay'
         *  Delay: '<S8>/Delay'
         *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator'
         */
        rtDW->Delay_DSTATE_i = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;
        rtDW->Delay_DSTATE_bc = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S4>/Drehzahlregler' */
      }

      /* Outputs for IfAction SubSystem: '<S4>/Drehzahlregler' incorporates:
       *  ActionPort: '<S8>/Action Port'
       */
      /* MATLAB Function: '<S8>/function_Eckdrehzahl' incorporates:
       *  Inport: '<Root>/fl_field_weakening'
       */
      /* MATLAB Function 'FOC_komplex/Regelung/Drehzahlregler/function_Eckdrehzahl': '<S17>:1' */
      /* '<S17>:1:4' U_FA = 0.95*U_ZK/(sqrt(single(3))); */
      rtb_Add1_k = 0.95F * DiscreteTimeIntegrator / 1.73205078F;

      /* '<S17>:1:5' a = Psi_PM^2 + (L_q*i_ref_max)^2; */
      rtb_Sin = rtP.L_q * rtP.i_ref_max;
      rtb_Sin = rtP.Psi_PM * rtP.Psi_PM + rtb_Sin * rtb_Sin;

      /* '<S17>:1:6' b = 2*Psi_PM*R*i_ref_max; */
      rtb_Cos = 2.0F * rtP.Psi_PM * rtP.R * rtP.i_ref_max;

      /* '<S17>:1:7' c = (R*i_ref_max)^2 - U_FA^2; */
      rtb_Gain1_n = rtP.R * rtP.i_ref_max;
      rtb_Add1_k = rtb_Gain1_n * rtb_Gain1_n - rtb_Add1_k * rtb_Add1_k;

      /* '<S17>:1:8' if -4*a*c >= single(0) */
      if (-4.0F * rtb_Sin * rtb_Add1_k >= 0.0F) {
        /* '<S17>:1:9' n_eck = single(30)/(p*pi) * (-b+sqrt(b^2 -4*a*c))/(2*a); */
        rtb_Sin = (sqrtf(rtb_Cos * rtb_Cos - 4.0F * rtb_Sin * rtb_Add1_k) +
                   -rtb_Cos) * (30.0F / (rtP.p * 3.14159274F)) / (2.0F * rtb_Sin);

        /* '<S17>:1:10' error_speed_limit = single(0); */
        rtDW->error_speed_limit = 0;
      } else {
        /* '<S17>:1:11' else */
        /* '<S17>:1:12' n_eck = single(0); */
        rtb_Sin = 0.0F;

        /* '<S17>:1:13' error_speed_limit = single(1); */
        rtDW->error_speed_limit = 1;
      }

      /* '<S17>:1:15' if (flag_id == 1) && (error_speed_limit == 0) */
      if ((rtU->fl_field_weakening == 1) && (rtDW->error_speed_limit == 0)) {
        /* '<S17>:1:16' n_sat = min(3*n_eck, n_ref_max); */
        rtb_Cos = fminf(3.0F * rtb_Sin, rtP.n_ref_max);
      } else {
        /* '<S17>:1:17' else */
        /* '<S17>:1:18' n_sat = min(n_eck, n_ref_max); */
        rtb_Cos = fminf(rtb_Sin, rtP.n_ref_max);
      }

      rtDW->error_speed_limit_h = (real32_T)rtDW->error_speed_limit;

      /* MATLAB Function: '<S8>/Function_Feldschwaeche' incorporates:
       *  Constant: '<S8>/Constant'
       *  Inport: '<Root>/Act_n'
       *  Inport: '<Root>/fl_field_weakening'
       *  MATLAB Function: '<S8>/function_Eckdrehzahl'
       */
      /* MATLAB Function 'FOC_komplex/Regelung/Drehzahlregler/Function_Feldschwaeche': '<S12>:1' */
      /* '<S12>:1:3' switch flag_id */
      if (rtU->fl_field_weakening == 1) {
        /* '<S12>:1:4' case uint8(1) */
        /* '<S12>:1:5' if n_ist>n_eck */
        if (rtU->Act_n > rtb_Sin) {
          /* I_d_soll = (Psi_PM*(n_eck-n_ist))/L_d; */
          /* '<S12>:1:7' I_d_soll = Psi_PM/L_d * (n_eck/n_ist - single(1)); */
          rtb_Add1_k = (rtb_Sin / rtU->Act_n - 1.0F) * (rtP.Psi_PM / rtP.L_d);
        } else {
          /* '<S12>:1:8' else */
          /* '<S12>:1:9' I_d_soll = single(0); */
          rtb_Add1_k = 0.0F;
        }
      } else {
        /* '<S12>:1:11' otherwise */
        /* '<S12>:1:12' I_d_soll = single(0); */
        rtb_Add1_k = 0.0F;
      }

      /* '<S12>:1:15' if abs(I_d_soll)>= 0.95*I_ref_max */
      if (fabsf(rtb_Add1_k) >= 0.95F * rtP.i_ref_max) {
        /* '<S12>:1:16' I_d_soll = sign(I_d_soll)*0.95*I_ref_max; */
        if (rtb_Add1_k < 0.0F) {
          rtb_Add1_k = -1.0F;
        } else if (rtb_Add1_k > 0.0F) {
          rtb_Add1_k = 1.0F;
        }

        rtb_Add1_k = rtb_Add1_k * 0.95F * rtP.i_ref_max;
      }

      /* '<S12>:1:19' I_q_max = sqrt(I_ref_max^2-I_d_soll^2); */
      rtb_Sin = sqrtf(rtP.i_ref_max * rtP.i_ref_max - rtb_Add1_k * rtb_Add1_k);

      /* Merge: '<S4>/Merge' incorporates:
       *  MATLAB Function: '<S8>/Function_Feldschwaeche'
       *  SignalConversion generated from: '<S8>/Id_soll [A]'
       */
      rtDW->Ref_Id = rtb_Add1_k;

      /* Switch: '<S16>/Switch2' incorporates:
       *  Inport: '<Root>/Ref_n'
       *  RelationalOperator: '<S16>/LowerRelop1'
       */
      if (rtU->Ref_n <= rtb_Cos) {
        /* Gain: '<S8>/Gain3' */
        rtb_Cos = -rtb_Cos;

        /* Switch: '<S16>/Switch' incorporates:
         *  RelationalOperator: '<S16>/UpperRelop'
         */
        if (rtU->Ref_n >= rtb_Cos) {
          rtb_Cos = rtU->Ref_n;
        }

        /* End of Switch: '<S16>/Switch' */
      }

      /* End of Switch: '<S16>/Switch2' */

      /* Gain: '<S14>/Gain' incorporates:
       *  Delay: '<S14>/Delay'
       *  Sum: '<S14>/Sum'
       */
      rtb_Cos = rtP.T_R / rtP.T_VF_n * (rtb_Cos - rtDW->Delay_DSTATE_i);

      /* DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
      rtb_Add1_k = 0.5F * rtb_Cos + rtDW->DiscreteTimeIntegrator_DSTATE_o;

      /* Gain: '<S13>/Gain' incorporates:
       *  Inport: '<Root>/Act_n'
       *  Sum: '<S8>/Sum'
       */
      rtb_Switch2 = (rtb_Add1_k - rtU->Act_n) * rtP.Kp_n;

      /* Gain: '<S13>/Gain1' incorporates:
       *  Delay: '<S8>/Delay'
       *  Sum: '<S13>/Sum1'
       */
      rtb_Gain1_n = rtP.T_R * rtP.Kis_n * (rtb_Switch2 + rtDW->Delay_DSTATE_bc);

      /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
       *  Inport: '<Root>/fl_integrator_reset'
       */
      if (rtU->fl_integrator_reset != 0) {
        rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.0F;
      }

      /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
      y_i_k = 0.5F * rtb_Gain1_n + rtDW->DiscreteTimeIntegrator_DSTATE_a;

      /* Sum: '<S13>/Sum' */
      rtb_y_h = rtb_Switch2 + y_i_k;

      /* Switch: '<S15>/Switch2' incorporates:
       *  Gain: '<S8>/Gain2'
       *  RelationalOperator: '<S15>/LowerRelop1'
       *  RelationalOperator: '<S15>/UpperRelop'
       *  Switch: '<S15>/Switch'
       */
      if (rtb_y_h > rtb_Sin) {
        rtb_Switch2 = rtb_Sin;
      } else if (rtb_y_h < -rtb_Sin) {
        /* Switch: '<S15>/Switch' incorporates:
         *  Gain: '<S8>/Gain2'
         */
        rtb_Switch2 = -rtb_Sin;
      } else {
        rtb_Switch2 = rtb_y_h;
      }

      /* End of Switch: '<S15>/Switch2' */

      /* Merge: '<S4>/Merge1' incorporates:
       *  SignalConversion generated from: '<S8>/I_q_soll [A]'
       */
      rtDW->Ref_Iq = rtb_Switch2;

      /* Update for Delay: '<S14>/Delay' */
      rtDW->Delay_DSTATE_i = rtb_Add1_k;

      /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.5F * rtb_Cos + rtb_Add1_k;

      /* Update for Delay: '<S8>/Delay' incorporates:
       *  Delay: '<S4>/Delay'
       *  Product: '<S8>/Product'
       *  Sum: '<S8>/Sum1'
       *  Sum: '<S8>/Sum2'
       *  Sum: '<S8>/Sum3'
       */
      rtDW->Delay_DSTATE_bc = (rtb_q - rtb_Switch2) * rtDW->Delay_DSTATE_b +
        (rtb_Switch2 - rtb_y_h);

      /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.5F * rtb_Gain1_n + y_i_k;

      /* End of Outputs for SubSystem: '<S4>/Drehzahlregler' */
    } else {
      /* Outputs for IfAction SubSystem: '<S4>/Stromvorgabe_extern' incorporates:
       *  ActionPort: '<S10>/Action Port'
       */
      /* MATLAB Function: '<S10>/Function_I_limit' incorporates:
       *  Constant: '<S10>/Constant'
       *  Inport: '<Root>/Ref_Id_ext'
       *  Inport: '<Root>/Ref_Iq_ext'
       */
      /* MATLAB Function 'FOC_komplex/Regelung/Stromvorgabe_extern/Function_I_limit': '<S24>:1' */
      /* '<S24>:1:4' I_abs_ext = sqrt(I_d_soll_ext^2+I_q_soll_ext^2); */
      /* '<S24>:1:5' if I_abs_ext > I_ref_max */
      if (sqrtf(rtU->Ref_Id_ext * rtU->Ref_Id_ext + rtU->Ref_Iq_ext *
                rtU->Ref_Iq_ext) > rtP.i_ref_max) {
        /* '<S24>:1:6' if abs(I_d_soll_ext)>= 0.95*I_ref_max */
        if (fabsf(rtU->Ref_Id_ext) >= 0.95F * rtP.i_ref_max) {
          /* '<S24>:1:7' I_d_soll = sign(I_d_soll_ext)*0.95*I_ref_max; */
          if (rtU->Ref_Id_ext < 0.0F) {
            rtDW->U_q_lim = -1.0F;
          } else if (rtU->Ref_Id_ext > 0.0F) {
            rtDW->U_q_lim = 1.0F;
          } else {
            rtDW->U_q_lim = rtU->Ref_Id_ext;
          }

          rtb_Add1_k = rtDW->U_q_lim * 0.95F * rtP.i_ref_max;
        } else {
          /* '<S24>:1:8' else */
          /* '<S24>:1:9' I_d_soll = I_d_soll_ext; */
          rtb_Add1_k = rtU->Ref_Id_ext;
        }

        /* '<S24>:1:11' I_q_soll = sign(I_q_soll_ext)*sqrt(I_ref_max^2-I_d_soll^2); */
        if (rtU->Ref_Iq_ext < 0.0F) {
          rtDW->U_q_lim = -1.0F;
        } else if (rtU->Ref_Iq_ext > 0.0F) {
          rtDW->U_q_lim = 1.0F;
        } else {
          rtDW->U_q_lim = rtU->Ref_Iq_ext;
        }

        /* Merge: '<S4>/Merge1' */
        rtDW->Ref_Iq = sqrtf(rtP.i_ref_max * rtP.i_ref_max - rtb_Add1_k *
                             rtb_Add1_k) * rtDW->U_q_lim;
      } else {
        /* '<S24>:1:12' else */
        /* '<S24>:1:13' I_d_soll = I_d_soll_ext; */
        rtb_Add1_k = rtU->Ref_Id_ext;

        /* Merge: '<S4>/Merge1' */
        /* '<S24>:1:14' I_q_soll = I_q_soll_ext; */
        rtDW->Ref_Iq = rtU->Ref_Iq_ext;
      }

      /* Merge: '<S4>/Merge' incorporates:
       *  MATLAB Function: '<S10>/Function_I_limit'
       *  SignalConversion generated from: '<S10>/I_d_soll'
       */
      rtDW->Ref_Id = rtb_Add1_k;

      /* End of Outputs for SubSystem: '<S4>/Stromvorgabe_extern' */
    }

    /* End of SwitchCase: '<S4>/Switch Case' */

    /* Outport: '<Root>/error_speed_limit' incorporates:
     *  SignalConversion generated from: '<S4>/InfoOut_Outport_4'
     */
    rtY->error_speed_limit = rtDW->error_speed_limit_h;

    /* Outport: '<Root>/Voltage_Limit' incorporates:
     *  Delay: '<S4>/Delay'
     *  SignalConversion generated from: '<S4>/InfoOut_Outport_4'
     */
    rtY->Voltage_Limit = rtDW->Delay_DSTATE_b;

    /* Gain: '<S20>/Gain' incorporates:
     *  Sum: '<S9>/Sum1'
     */
    rtb_Add1_k = (rtDW->Ref_Id - rtb_alpha_j) * rtP.Kp_id;

    /* Gain: '<S20>/Gain1' incorporates:
     *  Delay: '<S9>/Delay1'
     *  Sum: '<S20>/Sum1'
     */
    rtb_Sin = rtP.T_R * rtP.Kis_id * (rtb_Add1_k + rtDW->Delay1_DSTATE);

    /* DiscreteIntegrator: '<S20>/Discrete-Time Integrator' incorporates:
     *  Inport: '<Root>/fl_integrator_reset'
     */
    if (rtU->fl_integrator_reset != 0) {
      rtDW->DiscreteTimeIntegrator_DSTATE_k = 0.0F;
    }

    /* DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
    rtb_Cos = 0.5F * rtb_Sin + rtDW->DiscreteTimeIntegrator_DSTATE_k;

    /* Sum: '<S20>/Sum' */
    rtb_Gain1_n = rtb_Add1_k + rtb_Cos;

    /* SwitchCase: '<S18>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_decoupling'
     */
    if (rtU->fl_decoupling == 1) {
      /* Outputs for IfAction SubSystem: '<S18>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S22>/Action Port'
       */
      /* Product: '<S22>/Product1' incorporates:
       *  Constant: '<S22>/Constant'
       *  Gain: '<S22>/Gain1'
       *  Inport: '<Root>/Act_w_el'
       *  Sum: '<S22>/Add'
       */
      rtb_Merge1 = (rtP.L_d * rtb_alpha_j + rtP.Psi_PM) * rtU->Act_w_el;

      /* Product: '<S22>/Product' incorporates:
       *  Gain: '<S22>/Gain'
       *  Inport: '<Root>/Act_w_el'
       */
      rtb_Add1_k = rtP.L_q * rtb_q * rtU->Act_w_el;

      /* End of Outputs for SubSystem: '<S18>/Switch Case Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S18>/Switch Case Action Subsystem1' incorporates:
       *  ActionPort: '<S23>/Action Port'
       */
      /* SignalConversion generated from: '<S23>/U_hd_default' incorporates:
       *  Constant: '<S23>/Constant'
       */
      rtb_Add1_k = 0.0F;

      /* SignalConversion generated from: '<S23>/U_hq_default' incorporates:
       *  Constant: '<S23>/Constant1'
       */
      rtb_Merge1 = 0.0F;

      /* End of Outputs for SubSystem: '<S18>/Switch Case Action Subsystem1' */
    }

    /* End of SwitchCase: '<S18>/Switch Case' */

    /* Sum: '<S9>/Sum2' */
    rtb_Gain1_n -= rtb_Add1_k;

    /* Gain: '<S21>/Gain' incorporates:
     *  Sum: '<S9>/Sum'
     */
    rtb_Add1_k = (rtDW->Ref_Iq - rtb_q) * rtP.Kp_iq;

    /* Gain: '<S21>/Gain1' incorporates:
     *  Delay: '<S9>/Delay'
     *  Sum: '<S21>/Sum1'
     */
    y_i_k = rtP.T_R * rtP.Kis_iq * (rtb_Add1_k + rtDW->Delay_DSTATE_a);

    /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator' incorporates:
     *  Inport: '<Root>/fl_integrator_reset'
     */
    if (rtU->fl_integrator_reset != 0) {
      rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.0F;
    }

    /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
    rtb_y_h = 0.5F * y_i_k + rtDW->DiscreteTimeIntegrator_DSTATE_l;

    /* Sum: '<S9>/Sum3' incorporates:
     *  Sum: '<S21>/Sum'
     */
    rtb_Switch2 = (rtb_Add1_k + rtb_y_h) + rtb_Merge1;

    /* MATLAB Function: '<S9>/Function_Spannungsbegrenzung' incorporates:
     *  Inport: '<Root>/fl_voltage_limitation'
     */
    /* Berechnet die Begrenzten Spannungen */
    /* MATLAB Function 'FOC_komplex/Regelung/Stromregler diskret/Function_Spannungsbegrenzung': '<S19>:1' */
    /* '<S19>:1:6' U_FA = 0.95*U_ZK/(sqrt(3)); */
    rtb_Add1_k = 0.95F * DiscreteTimeIntegrator / 1.73205078F;

    /* '<S19>:1:7' switch flag_U_lim */
    switch (rtU->fl_voltage_limitation) {
     case 1U:
      /* '<S19>:1:8' case 1 */
      /* Prio U_d */
      /* '<S19>:1:9' if (U_d^2 + U_q^2)<=U_FA^2 */
      if (rtb_Gain1_n * rtb_Gain1_n + rtb_Switch2 * rtb_Switch2 <= rtb_Add1_k *
          rtb_Add1_k) {
        /* '<S19>:1:10' U_d_lim = U_d; */
        rtb_Merge1 = rtb_Gain1_n;

        /* '<S19>:1:11' U_q_lim = U_q; */
        rtDW->U_q_lim = rtb_Switch2;

        /* Update for Delay: '<S4>/Delay' */
        /* '<S19>:1:12' stat_lim_u = single(0); */
        rtDW->Delay_DSTATE_b = 0.0F;
      } else {
        /* '<S19>:1:13' else */
        /* '<S19>:1:14' if abs(U_d)>0.95*U_FA */
        if (fabsf(rtb_Gain1_n) > 0.95F * rtb_Add1_k) {
          /* '<S19>:1:15' U_d_lim = sign(U_d)*0.95*U_FA; */
          if (rtb_Gain1_n < 0.0F) {
            rtb_Merge1 = -1.0F;
          } else if (rtb_Gain1_n > 0.0F) {
            rtb_Merge1 = 1.0F;
          } else {
            rtb_Merge1 = rtb_Gain1_n;
          }

          rtb_Merge1 = rtb_Merge1 * 0.95F * rtb_Add1_k;
        } else {
          /* '<S19>:1:16' else */
          /* '<S19>:1:17' U_d_lim = U_d; */
          rtb_Merge1 = rtb_Gain1_n;
        }

        /* '<S19>:1:19' U_q_lim = sqrt(U_FA^2 - U_d_lim^2)*sign(U_q); */
        if (rtb_Switch2 < 0.0F) {
          rtDW->U_q_lim = -1.0F;
        } else if (rtb_Switch2 > 0.0F) {
          rtDW->U_q_lim = 1.0F;
        } else {
          rtDW->U_q_lim = rtb_Switch2;
        }

        rtDW->U_q_lim *= sqrtf(rtb_Add1_k * rtb_Add1_k - rtb_Merge1 * rtb_Merge1);

        /* Update for Delay: '<S4>/Delay' */
        /* '<S19>:1:20' stat_lim_u = single(1); */
        rtDW->Delay_DSTATE_b = 1.0F;
      }
      break;

     case 2U:
      /* '<S19>:1:22' case 2 */
      /* Quang 3-Phase-vector-Control 183 */
      /* '<S19>:1:23' if (U_d^2 + U_q^2)<=U_FA^2 */
      if (rtb_Gain1_n * rtb_Gain1_n + rtb_Switch2 * rtb_Switch2 <= rtb_Add1_k *
          rtb_Add1_k) {
        /* '<S19>:1:24' U_d_lim = U_d; */
        rtb_Merge1 = rtb_Gain1_n;

        /* '<S19>:1:25' U_q_lim = U_q; */
        rtDW->U_q_lim = rtb_Switch2;

        /* Update for Delay: '<S4>/Delay' */
        /* '<S19>:1:26' stat_lim_u = single(0); */
        rtDW->Delay_DSTATE_b = 0.0F;
      } else {
        if (rtb_Merge1 < 0.0F) {
          rtb_Merge1 = -1.0F;
        } else if (rtb_Merge1 > 0.0F) {
          rtb_Merge1 = 1.0F;
        }

        if (rtDW->Ref_Iq < 0.0F) {
          rtDW->U_q_lim = -1.0F;
        } else if (rtDW->Ref_Iq > 0.0F) {
          rtDW->U_q_lim = 1.0F;
        } else {
          rtDW->U_q_lim = rtDW->Ref_Iq;
        }

        if (rtb_Merge1 != rtDW->U_q_lim) {
          /* '<S19>:1:27' elseif sign(U_hq) ~= sign(iq_soll) */
          /* Generator */
          /* '<S19>:1:29' if abs(U_q)>0.95*U_FA */
          if (fabsf(rtb_Switch2) > 0.95F * rtb_Add1_k) {
            /* '<S19>:1:30' U_q_lim = sign(U_q)*0.95*U_FA; */
            if (rtb_Switch2 < 0.0F) {
              rtDW->U_q_lim = -1.0F;
            } else if (rtb_Switch2 > 0.0F) {
              rtDW->U_q_lim = 1.0F;
            } else {
              rtDW->U_q_lim = rtb_Switch2;
            }

            rtDW->U_q_lim = rtDW->U_q_lim * 0.95F * rtb_Add1_k;
          } else {
            /* '<S19>:1:31' else */
            /* '<S19>:1:32' U_q_lim = U_q; */
            rtDW->U_q_lim = rtb_Switch2;
          }

          /* '<S19>:1:34' U_d_lim = sign(U_d)*sqrt(U_FA^2 - U_q_lim^2); */
          if (rtb_Gain1_n < 0.0F) {
            rtb_Merge1 = -1.0F;
          } else if (rtb_Gain1_n > 0.0F) {
            rtb_Merge1 = 1.0F;
          } else {
            rtb_Merge1 = rtb_Gain1_n;
          }

          rtb_Merge1 *= sqrtf(rtb_Add1_k * rtb_Add1_k - rtDW->U_q_lim *
                              rtDW->U_q_lim);

          /* Update for Delay: '<S4>/Delay' */
          /* '<S19>:1:35' stat_lim_u = single(1); */
          rtDW->Delay_DSTATE_b = 1.0F;
        } else {
          /* '<S19>:1:36' else */
          /* Motor */
          /* '<S19>:1:38' if abs(U_d)>0.95*U_FA */
          if (fabsf(rtb_Gain1_n) > 0.95F * rtb_Add1_k) {
            /* '<S19>:1:39' U_d_lim = sign(U_d)*0.95*U_FA; */
            if (rtb_Gain1_n < 0.0F) {
              rtb_Merge1 = -1.0F;
            } else if (rtb_Gain1_n > 0.0F) {
              rtb_Merge1 = 1.0F;
            } else {
              rtb_Merge1 = rtb_Gain1_n;
            }

            rtb_Merge1 = rtb_Merge1 * 0.95F * rtb_Add1_k;
          } else {
            /* '<S19>:1:40' else */
            /* '<S19>:1:41' U_d_lim = U_d; */
            rtb_Merge1 = rtb_Gain1_n;
          }

          /* '<S19>:1:43' U_q_lim = sign(U_q)*sqrt(U_FA^2 - U_d_lim^2); */
          if (rtb_Switch2 < 0.0F) {
            rtDW->U_q_lim = -1.0F;
          } else if (rtb_Switch2 > 0.0F) {
            rtDW->U_q_lim = 1.0F;
          } else {
            rtDW->U_q_lim = rtb_Switch2;
          }

          rtDW->U_q_lim *= sqrtf(rtb_Add1_k * rtb_Add1_k - rtb_Merge1 *
            rtb_Merge1);

          /* Update for Delay: '<S4>/Delay' */
          /* '<S19>:1:44' stat_lim_u = single(1); */
          rtDW->Delay_DSTATE_b = 1.0F;
        }
      }
      break;

     default:
      /* '<S19>:1:46' otherwise */
      /* keine Begrenzung */
      /* '<S19>:1:47' U_d_lim = U_d; */
      rtb_Merge1 = rtb_Gain1_n;

      /* '<S19>:1:48' U_q_lim = U_q; */
      rtDW->U_q_lim = rtb_Switch2;

      /* Update for Delay: '<S4>/Delay' */
      /* '<S19>:1:49' stat_lim_u = single(0); */
      rtDW->Delay_DSTATE_b = 0.0F;
      break;
    }

    /* MATLAB Function: '<S11>/Winkelwahl' incorporates:
     *  Inport: '<Root>/Act_theta_el'
     *  Inport: '<Root>/Act_w_el'
     *  Inport: '<Root>/fl_angle_prediction'
     */
    /*  Winkelprädiktion für die nächste Schalperiode, wenn das Flag gesetzt ist */
    /* MATLAB Function 'FOC_komplex/Regelung/Tastgradumwandlung/Winkelwahl': '<S28>:1' */
    /* '<S28>:1:5' if flag_Winkelpraediktion */
    if (rtU->fl_angle_prediction != 0) {
      /* '<S28>:1:6' theta_el_verwendet = theta_el_ist + w_el_ist*1.5*T_R; */
      rtb_theta_el_verwendet = rtU->Act_w_el * 1.5F * rtP.T_R +
        rtU->Act_theta_el;
    } else {
      /* '<S28>:1:7' else */
      /* '<S28>:1:8' theta_el_verwendet = theta_el_ist; */
      rtb_theta_el_verwendet = rtU->Act_theta_el;
    }

    /* End of MATLAB Function: '<S11>/Winkelwahl' */

    /* Trigonometry: '<S30>/Cos' */
    rtb_Add1_k = cosf(rtb_theta_el_verwendet);

    /* Trigonometry: '<S30>/Sin' */
    rtb_theta_el_verwendet = sinf(rtb_theta_el_verwendet);

    /* Gain: '<S29>/Gain' incorporates:
     *  MATLAB Function: '<S9>/Function_Spannungsbegrenzung'
     *  Product: '<S30>/Product'
     *  Product: '<S30>/Product1'
     *  Sum: '<S30>/Add'
     */
    rtb_u = (rtb_Merge1 * rtb_Add1_k - rtDW->U_q_lim * rtb_theta_el_verwendet) *
      0.5F;

    /* Gain: '<S29>/Gain1' incorporates:
     *  MATLAB Function: '<S9>/Function_Spannungsbegrenzung'
     *  Product: '<S30>/Product2'
     *  Product: '<S30>/Product3'
     *  Sum: '<S30>/Add1'
     */
    rtb_Add1_k = (rtb_Merge1 * rtb_theta_el_verwendet + rtDW->U_q_lim *
                  rtb_Add1_k) * 0.866025388F;

    /* Sum: '<S29>/Add' */
    rtb_theta_el_verwendet = rtb_Add1_k - rtb_u;

    /* Sum: '<S29>/Add1' */
    rtb_Add1_k = (0.0F - rtb_u) - rtb_Add1_k;

    /* Gain: '<S29>/Gain2' */
    rtb_u *= 2.0F;

    /* Gain: '<S26>/Gain2' incorporates:
     *  MinMax: '<S26>/Min'
     *  MinMax: '<S26>/Min1'
     *  Sum: '<S26>/Add3'
     */
    rtb_Gain2_l = (fmaxf(fmaxf(rtb_u, rtb_theta_el_verwendet), rtb_Add1_k) +
                   fminf(fminf(rtb_u, rtb_theta_el_verwendet), rtb_Add1_k)) *
      -0.5F;

    /* Outport: '<Root>/a_V' incorporates:
     *  Constant: '<S27>/Constant2'
     *  Product: '<S27>/Divide1'
     *  Sum: '<S26>/Add5'
     *  Sum: '<S27>/Add1'
     */
    rtY->a_V = (rtb_theta_el_verwendet + rtb_Gain2_l) / DiscreteTimeIntegrator +
      0.5F;

    /* Outport: '<Root>/a_U' incorporates:
     *  Constant: '<S27>/Constant1'
     *  Product: '<S27>/Divide'
     *  Sum: '<S26>/Add4'
     *  Sum: '<S27>/Add'
     */
    rtY->a_U = (rtb_u + rtb_Gain2_l) / DiscreteTimeIntegrator + 0.5F;

    /* Outport: '<Root>/a_W' incorporates:
     *  Constant: '<S27>/Constant3'
     *  Product: '<S27>/Divide2'
     *  Sum: '<S26>/Add6'
     *  Sum: '<S27>/Add2'
     */
    rtY->a_W = (rtb_Add1_k + rtb_Gain2_l) / DiscreteTimeIntegrator + 0.5F;

    /* Outport: '<Root>/Ud_Ref' incorporates:
     *  MATLAB Function: '<S9>/Function_Spannungsbegrenzung'
     *  SignalConversion generated from: '<S4>/InfoOut_Outport_4'
     */
    rtY->Ud_Ref = rtb_Merge1;

    /* Outport: '<Root>/Uq_Ref' incorporates:
     *  MATLAB Function: '<S9>/Function_Spannungsbegrenzung'
     *  SignalConversion generated from: '<S4>/InfoOut_Outport_4'
     */
    rtY->Uq_Ref = rtDW->U_q_lim;

    /* Outport: '<Root>/Iq_Ref' incorporates:
     *  SignalConversion generated from: '<S4>/InfoOut_Outport_4'
     */
    rtY->Iq_Ref = rtDW->Ref_Iq;

    /* Outport: '<Root>/Id_Ref' incorporates:
     *  SignalConversion generated from: '<S4>/InfoOut_Outport_4'
     */
    rtY->Id_Ref = rtDW->Ref_Id;

    /* Update for Delay: '<S9>/Delay1' incorporates:
     *  MATLAB Function: '<S9>/Function_Spannungsbegrenzung'
     *  Sum: '<S9>/Sum5'
     */
    rtDW->Delay1_DSTATE = rtb_Merge1 - rtb_Gain1_n;

    /* Update for DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
    rtDW->DiscreteTimeIntegrator_DSTATE_k = 0.5F * rtb_Sin + rtb_Cos;

    /* Update for Delay: '<S9>/Delay' incorporates:
     *  MATLAB Function: '<S9>/Function_Spannungsbegrenzung'
     *  Sum: '<S9>/Sum4'
     */
    rtDW->Delay_DSTATE_a = rtDW->U_q_lim - rtb_Switch2;

    /* Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
    rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.5F * y_i_k + rtb_y_h;

    /* End of Outputs for SubSystem: '<S1>/Regelung' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/aus' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Outport: '<Root>/a_U' incorporates:
     *  Constant: '<S7>/Constant'
     *  SignalConversion generated from: '<S7>/a_U'
     */
    rtY->a_U = 0.5F;

    /* Outport: '<Root>/a_V' incorporates:
     *  Constant: '<S7>/Constant'
     *  SignalConversion generated from: '<S7>/a_V'
     */
    rtY->a_V = 0.5F;

    /* Outport: '<Root>/a_W' incorporates:
     *  Constant: '<S7>/Constant'
     *  SignalConversion generated from: '<S7>/a_W'
     */
    rtY->a_W = 0.5F;

    /* End of Outputs for SubSystem: '<S1>/aus' */
  }

  /* End of SwitchCase: '<S1>/switch_case_power' */

  /* Outport: '<Root>/Id_Act' */
  rtY->Id_Act = rtb_alpha_j;

  /* Sqrt: '<S2>/Square Root' incorporates:
   *  Math: '<S2>/Square'
   *  Math: '<S2>/Square1'
   *  Sum: '<S2>/Add1'
   */
  rtb_alpha_j = sqrtf(rtb_alpha_j * rtb_alpha_j + rtb_q * rtb_q);

  /* Outport: '<Root>/fault_peak_current' incorporates:
   *  Constant: '<S5>/Constant'
   *  DataTypeConversion: '<S5>/Data Type Conversion3'
   *  RelationalOperator: '<S5>/Smaller'
   */
  rtY->fault_peak_current = (real32_T)(rtP.i_max_peak <= rtb_alpha_j);

  /* DiscreteIntegrator: '<S31>/Accumulator' incorporates:
   *  Delay: '<S31>/Delay'
   *  Sum: '<S31>/Sum'
   */
  rtb_Sin = (rtb_alpha_j - rtDW->Delay_DSTATE_j[0]) + rtDW->Accumulator_DSTATE;

  /* Outport: '<Root>/fault_max_current' incorporates:
   *  Constant: '<S5>/Constant1'
   *  DataTypeConversion: '<S5>/Data Type Conversion2'
   *  Gain: '<S31>/Gain'
   *  RelationalOperator: '<S5>/Smaller1'
   */
  rtY->fault_max_current = (real32_T)(rtP.i_max <= 0.0333333351F * rtb_Sin);

  /* Outport: '<Root>/Iq_Act' */
  rtY->Iq_Act = rtb_q;

  /* Abs: '<S5>/Abs' incorporates:
   *  Inport: '<Root>/Act_n'
   */
  rtb_q = fabsf(rtU->Act_n);

  /* Outport: '<Root>/fault_peak_speed' incorporates:
   *  Constant: '<S5>/Constant2'
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  RelationalOperator: '<S5>/Smaller2'
   */
  rtY->fault_peak_speed = (real32_T)(rtP.n_max_peak <= rtb_q);

  /* DiscreteIntegrator: '<S32>/Accumulator' incorporates:
   *  Delay: '<S32>/Delay'
   *  Sum: '<S32>/Sum'
   */
  rtb_Cos = (rtb_q - rtDW->Delay_DSTATE_m[0]) + rtDW->Accumulator_DSTATE_o;

  /* Outport: '<Root>/fault_max_speed' incorporates:
   *  Constant: '<S5>/Constant3'
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   *  Gain: '<S32>/Gain'
   *  RelationalOperator: '<S5>/Smaller3'
   */
  rtY->fault_max_speed = (real32_T)(rtP.n_max <= 0.00666666683F * rtb_Cos);

  /* Update for Delay: '<S3>/Delay' */
  rtDW->Delay_DSTATE = DiscreteTimeIntegrator;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE = 0.5F * rtb_Gain + DiscreteTimeIntegrator;

  /* Update for Delay: '<S31>/Delay' */
  for (rtDW->error_speed_limit = 0; rtDW->error_speed_limit < 29;
       rtDW->error_speed_limit++) {
    rtDW->Delay_DSTATE_j[rtDW->error_speed_limit] = rtDW->Delay_DSTATE_j
      [rtDW->error_speed_limit + 1];
  }

  rtDW->Delay_DSTATE_j[29] = rtb_alpha_j;

  /* End of Update for Delay: '<S31>/Delay' */

  /* Update for DiscreteIntegrator: '<S31>/Accumulator' */
  rtDW->Accumulator_DSTATE = rtb_Sin;

  /* Update for Delay: '<S32>/Delay' */
  for (rtDW->error_speed_limit = 0; rtDW->error_speed_limit < 149;
       rtDW->error_speed_limit++) {
    rtDW->Delay_DSTATE_m[rtDW->error_speed_limit] = rtDW->Delay_DSTATE_m
      [rtDW->error_speed_limit + 1];
  }

  rtDW->Delay_DSTATE_m[149] = rtb_q;

  /* End of Update for Delay: '<S32>/Delay' */

  /* Update for DiscreteIntegrator: '<S32>/Accumulator' */
  rtDW->Accumulator_DSTATE_o = rtb_Cos;
}

/* Model initialize function */
void FOC_komplex_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

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
  /* Start for SwitchCase: '<S4>/Switch Case' */
  rtDW->SwitchCase_ActiveSubsystem = -1;

  /* InitializeConditions for Delay: '<S4>/Delay' */
  rtDW->Delay_DSTATE_b = 0.0F;

  /* InitializeConditions for Delay: '<S9>/Delay1' */
  rtDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_k = 0.0F;

  /* InitializeConditions for Delay: '<S9>/Delay' */
  rtDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_l = 0.0F;

  /* SystemInitialize for IfAction SubSystem: '<S4>/Drehzahlregler' */
  /* InitializeConditions for Delay: '<S14>/Delay' */
  rtDW->Delay_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;

  /* InitializeConditions for Delay: '<S8>/Delay' */
  rtDW->Delay_DSTATE_bc = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_a = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S4>/Drehzahlregler' */

  /* SystemInitialize for Merge: '<S4>/Merge' */
  rtDW->Ref_Id = 0.0F;

  /* SystemInitialize for Merge: '<S4>/Merge1' */
  rtDW->Ref_Iq = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S1>/Regelung' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
