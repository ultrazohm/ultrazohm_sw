/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: foc_ts.c
 *
 * Code generated for Simulink model 'foc_ts'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Oct  1 16:09:58 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Passed (11), Warnings (2), Error (0)
 */

#include "foc_ts.h"
#include "foc_ts_private.h"

real_T rt_modd(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  boolean_T yEq;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else {
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      q = fabs(u0 / u1);
      yEq = (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q);
    }

    if (yEq) {
      y = 0.0;
    } else {
      if ((u0 < 0.0) != (u1 < 0.0)) {
        y += u1;
      }
    }
  }

  return y;
}

/* Model step function */
void foc_ts_step(RT_MODEL_foc_ts_T *const foc_ts_M, real_T foc_ts_U_d_u_dc,
                 real_T foc_ts_U_d_nSoll, real_T foc_ts_U_d_omega_mech, real_T
                 foc_ts_U_d_theta_mech, real_T foc_ts_U_d_i_a, real_T
                 foc_ts_U_d_i_b, real_T foc_ts_U_d_i_c, real_T foc_ts_U_d_K_p_d,
                 real_T foc_ts_U_d_K_i_d, real_T foc_ts_U_d_K_p_q, real_T
                 foc_ts_U_d_K_i_q, real_T foc_ts_U_d_K_p_n, real_T
                 foc_ts_U_d_K_i_n, real_T foc_ts_U_i_d_soll, real_T
                 *foc_ts_Y_d_u_1_nom, real_T *foc_ts_Y_d_u_2_nom, real_T
                 *foc_ts_Y_d_u_3_nom, real_T *foc_ts_Y_d_u_d, real_T
                 *foc_ts_Y_d_u_q, real_T *foc_ts_Y_iqSollFB, real_T
                 *foc_ts_Y_id_ist, real_T *foc_ts_Y_iq_ist, real_T
                 *foc_ts_Y_theta_mech_out)
{
  DW_foc_ts_T *foc_ts_DW = foc_ts_M->dwork;
  real_T rtb_Gain2_a;
  real_T rtb_IProdOut;
  real_T rtb_IProdOut_d;
  real_T rtb_IProdOut_e;
  real_T rtb_Integrator_l;
  real_T rtb_SignPreIntegrator;
  real_T rtb_SignPreSat;
  real_T rtb_SignPreSat_j;
  real_T rtb_u;
  real_T rtb_v;
  int16_T tmp;
  boolean_T rtb_Equal1_j;
  boolean_T rtb_Equal2;
  boolean_T rtb_NotEqual;
  boolean_T rtb_NotEqual_d;
  boolean_T rtb_NotEqual_p;

  /* Outputs for Atomic SubSystem: '<Root>/foc_ts' */
  /* Math: '<S1>/Math Function1' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Polpaarzahl2'
   *  Inport: '<Root>/d_theta_mech'
   */
  *foc_ts_Y_theta_mech_out = rt_modd(4.0 * foc_ts_U_d_theta_mech,
    6.2831853071795862);

  /* Trigonometry: '<S1>/Trigonometric Function' */
  rtb_v = sin(*foc_ts_Y_theta_mech_out);
  rtb_Gain2_a = cos(*foc_ts_Y_theta_mech_out);

  /* Sum: '<S4>/Add3' incorporates:
   *  Gain: '<S4>/Gain'
   *  Gain: '<S4>/Gain1'
   *  Gain: '<S4>/Gain2'
   *  Inport: '<Root>/d_i_a'
   *  Inport: '<Root>/d_i_b'
   *  Inport: '<Root>/d_i_c'
   */
  rtb_Integrator_l = (0.66666666666666663 * foc_ts_U_d_i_a - 0.33333333333333331
                      * foc_ts_U_d_i_b) - 0.33333333333333331 * foc_ts_U_d_i_c;

  /* Sum: '<S4>/Add4' incorporates:
   *  Gain: '<S4>/Gain3'
   *  Gain: '<S4>/Gain4'
   *  Inport: '<Root>/d_i_b'
   *  Inport: '<Root>/d_i_c'
   */
  rtb_IProdOut_d = 0.57735026918962584 * foc_ts_U_d_i_b - 0.57735026918962584 *
    foc_ts_U_d_i_c;

  /* Sum: '<S4>/Add1' incorporates:
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   */
  *foc_ts_Y_id_ist = rtb_Integrator_l * rtb_Gain2_a + rtb_IProdOut_d * rtb_v;

  /* Sum: '<S8>/Sum2' incorporates:
   *  Inport: '<Root>/i_d_soll'
   */
  rtb_IProdOut = foc_ts_U_i_d_soll - *foc_ts_Y_id_ist;

  /* Sum: '<S104>/Sum' incorporates:
   *  DiscreteIntegrator: '<S95>/Integrator'
   *  Inport: '<Root>/d_K_p_d'
   *  Product: '<S100>/PProd Out'
   */
  rtb_SignPreSat = rtb_IProdOut * foc_ts_U_d_K_p_d +
    foc_ts_DW->Integrator_DSTATE;

  /* Saturate: '<S102>/Saturation' */
  if (rtb_SignPreSat > 30.0) {
    /* Saturate: '<S102>/Saturation' */
    *foc_ts_Y_d_u_d = 30.0;
  } else if (rtb_SignPreSat < -30.0) {
    /* Saturate: '<S102>/Saturation' */
    *foc_ts_Y_d_u_d = -30.0;
  } else {
    /* Saturate: '<S102>/Saturation' */
    *foc_ts_Y_d_u_d = rtb_SignPreSat;
  }

  /* End of Saturate: '<S102>/Saturation' */

  /* Sum: '<S7>/Sum5' incorporates:
   *  Gain: '<S3>/Gain2'
   *  Inport: '<Root>/d_nSoll'
   *  Inport: '<Root>/d_omega_mech'
   */
  rtb_IProdOut_e = foc_ts_U_d_nSoll - 0.15915494309189535 *
    foc_ts_U_d_omega_mech;

  /* Product: '<S41>/PProd Out' incorporates:
   *  DiscreteIntegrator: '<S43>/Integrator'
   *  Inport: '<Root>/d_K_p_n'
   *  Sum: '<S52>/Sum'
   */
  rtb_SignPreSat_j = (rtb_IProdOut_e + foc_ts_DW->Integrator_DSTATE_j) *
    foc_ts_U_d_K_p_n;

  /* Saturate: '<S50>/Saturation' */
  if (rtb_SignPreSat_j > 5.0) {
    /* Saturate: '<S50>/Saturation' */
    *foc_ts_Y_iqSollFB = 5.0;
  } else if (rtb_SignPreSat_j < -5.0) {
    /* Saturate: '<S50>/Saturation' */
    *foc_ts_Y_iqSollFB = -5.0;
  } else {
    /* Saturate: '<S50>/Saturation' */
    *foc_ts_Y_iqSollFB = rtb_SignPreSat_j;
  }

  /* End of Saturate: '<S50>/Saturation' */

  /* Sum: '<S4>/Add2' incorporates:
   *  Product: '<S4>/Produc3t'
   *  Product: '<S4>/Product4'
   */
  *foc_ts_Y_iq_ist = rtb_IProdOut_d * rtb_Gain2_a - rtb_Integrator_l * rtb_v;

  /* Sum: '<S8>/Sum3' */
  rtb_IProdOut_d = *foc_ts_Y_iqSollFB - *foc_ts_Y_iq_ist;

  /* Sum: '<S154>/Sum' incorporates:
   *  DiscreteIntegrator: '<S145>/Integrator'
   *  Inport: '<Root>/d_K_p_q'
   *  Product: '<S150>/PProd Out'
   */
  rtb_Integrator_l = rtb_IProdOut_d * foc_ts_U_d_K_p_q +
    foc_ts_DW->Integrator_DSTATE_a;

  /* Saturate: '<S152>/Saturation' incorporates:
   *  DeadZone: '<S138>/DeadZone'
   */
  if (rtb_Integrator_l > 30.0) {
    /* Saturate: '<S152>/Saturation' */
    *foc_ts_Y_d_u_q = 30.0;
    rtb_Integrator_l -= 30.0;
  } else {
    if (rtb_Integrator_l < -30.0) {
      /* Saturate: '<S152>/Saturation' */
      *foc_ts_Y_d_u_q = -30.0;
    } else {
      /* Saturate: '<S152>/Saturation' */
      *foc_ts_Y_d_u_q = rtb_Integrator_l;
    }

    if (rtb_Integrator_l >= -30.0) {
      rtb_Integrator_l = 0.0;
    } else {
      rtb_Integrator_l -= -30.0;
    }
  }

  /* End of Saturate: '<S152>/Saturation' */

  /* Sum: '<S5>/Add5' incorporates:
   *  Product: '<S5>/Product5'
   *  Product: '<S5>/Product6'
   */
  rtb_u = *foc_ts_Y_d_u_d * rtb_Gain2_a - *foc_ts_Y_d_u_q * rtb_v;

  /* Gain: '<S2>/Gain1' */
  rtb_SignPreIntegrator = 0.5 * rtb_u;

  /* Gain: '<S2>/Gain2' incorporates:
   *  Product: '<S5>/Product3'
   *  Product: '<S5>/Product8'
   *  Sum: '<S5>/Add4'
   */
  rtb_Gain2_a = (*foc_ts_Y_d_u_d * rtb_v + *foc_ts_Y_d_u_q * rtb_Gain2_a) *
    0.8660254037844386;

  /* Sum: '<S2>/Add3' */
  rtb_v = rtb_Gain2_a - rtb_SignPreIntegrator;

  /* Sum: '<S2>/Add6' */
  rtb_SignPreIntegrator = (0.0 - rtb_SignPreIntegrator) - rtb_Gain2_a;

  /* Sum: '<S6>/Add2' incorporates:
   *  Constant: '<S6>/Constant8'
   *  Inport: '<Root>/d_u_dc'
   *  Product: '<S6>/Divide'
   */
  *foc_ts_Y_d_u_1_nom = rtb_u / foc_ts_U_d_u_dc + 0.5;
  *foc_ts_Y_d_u_2_nom = rtb_v / foc_ts_U_d_u_dc + 0.5;
  *foc_ts_Y_d_u_3_nom = rtb_SignPreIntegrator / foc_ts_U_d_u_dc + 0.5;

  /* RelationalOperator: '<S136>/NotEqual' */
  rtb_NotEqual = (0.0 != rtb_Integrator_l);

  /* Signum: '<S136>/SignPreSat' */
  if (rtb_Integrator_l < 0.0) {
    rtb_Integrator_l = -1.0;
  } else {
    if (rtb_Integrator_l > 0.0) {
      rtb_Integrator_l = 1.0;
    }
  }

  /* End of Signum: '<S136>/SignPreSat' */

  /* Product: '<S142>/IProd Out' incorporates:
   *  Inport: '<Root>/d_K_i_q'
   */
  rtb_IProdOut_d *= foc_ts_U_d_K_i_q;

  /* DeadZone: '<S36>/DeadZone' */
  if (rtb_SignPreSat_j > 5.0) {
    rtb_SignPreSat_j -= 5.0;
  } else if (rtb_SignPreSat_j >= -5.0) {
    rtb_SignPreSat_j = 0.0;
  } else {
    rtb_SignPreSat_j -= -5.0;
  }

  /* End of DeadZone: '<S36>/DeadZone' */

  /* RelationalOperator: '<S34>/NotEqual' */
  rtb_NotEqual_p = (0.0 != rtb_SignPreSat_j);

  /* Signum: '<S34>/SignPreSat' */
  if (rtb_SignPreSat_j < 0.0) {
    rtb_SignPreSat_j = -1.0;
  } else {
    if (rtb_SignPreSat_j > 0.0) {
      rtb_SignPreSat_j = 1.0;
    }
  }

  /* End of Signum: '<S34>/SignPreSat' */

  /* Product: '<S40>/IProd Out' incorporates:
   *  Inport: '<Root>/d_K_i_n'
   */
  rtb_IProdOut_e *= foc_ts_U_d_K_i_n;

  /* Signum: '<S34>/SignPreIntegrator' */
  if (rtb_IProdOut_e < 0.0) {
    rtb_v = -1.0;
  } else if (rtb_IProdOut_e > 0.0) {
    rtb_v = 1.0;
  } else {
    rtb_v = rtb_IProdOut_e;
  }

  /* End of Signum: '<S34>/SignPreIntegrator' */

  /* RelationalOperator: '<S34>/Equal1' incorporates:
   *  DataTypeConversion: '<S34>/DataTypeConv1'
   *  DataTypeConversion: '<S34>/DataTypeConv2'
   */
  rtb_Equal1_j = ((((int16_T)rtb_SignPreSat_j & 128U) != 0U ? (int16_T)
                   rtb_SignPreSat_j | -128 : (int16_T)rtb_SignPreSat_j & 127) ==
                  (((int16_T)rtb_v & 128U) != 0U ? (int16_T)rtb_v | -128 :
                   (int16_T)rtb_v & 127));

  /* Signum: '<S34>/SignP' incorporates:
   *  Inport: '<Root>/d_K_p_n'
   */
  if (foc_ts_U_d_K_p_n < 0.0) {
    rtb_v = -1.0;
  } else if (foc_ts_U_d_K_p_n > 0.0) {
    rtb_v = 1.0;
  } else {
    rtb_v = foc_ts_U_d_K_p_n;
  }

  /* End of Signum: '<S34>/SignP' */

  /* RelationalOperator: '<S34>/Equal2' incorporates:
   *  DataTypeConversion: '<S34>/DataTypeConv4'
   */
  rtb_Equal2 = ((((int16_T)rtb_v & 128U) != 0U ? (int16_T)rtb_v | -128 :
                 (int16_T)rtb_v & 127) == 1);

  /* DeadZone: '<S88>/DeadZone' */
  if (rtb_SignPreSat > 30.0) {
    rtb_SignPreSat -= 30.0;
  } else if (rtb_SignPreSat >= -30.0) {
    rtb_SignPreSat = 0.0;
  } else {
    rtb_SignPreSat -= -30.0;
  }

  /* End of DeadZone: '<S88>/DeadZone' */

  /* RelationalOperator: '<S86>/NotEqual' */
  rtb_NotEqual_d = (0.0 != rtb_SignPreSat);

  /* Signum: '<S86>/SignPreSat' */
  if (rtb_SignPreSat < 0.0) {
    rtb_SignPreSat = -1.0;
  } else {
    if (rtb_SignPreSat > 0.0) {
      rtb_SignPreSat = 1.0;
    }
  }

  /* End of Signum: '<S86>/SignPreSat' */

  /* Product: '<S92>/IProd Out' incorporates:
   *  Inport: '<Root>/d_K_i_d'
   */
  rtb_IProdOut *= foc_ts_U_d_K_i_d;

  /* Signum: '<S86>/SignPreIntegrator' */
  if (rtb_IProdOut < 0.0) {
    /* DataTypeConversion: '<S86>/DataTypeConv2' */
    tmp = -1;
  } else if (rtb_IProdOut > 0.0) {
    /* DataTypeConversion: '<S86>/DataTypeConv2' */
    tmp = 1;
  } else {
    /* DataTypeConversion: '<S86>/DataTypeConv2' */
    tmp = (int16_T)rtb_IProdOut;
  }

  /* End of Signum: '<S86>/SignPreIntegrator' */

  /* Switch: '<S86>/Switch' incorporates:
   *  Constant: '<S86>/Constant1'
   *  DataTypeConversion: '<S86>/DataTypeConv1'
   *  DataTypeConversion: '<S86>/DataTypeConv2'
   *  Logic: '<S86>/AND3'
   *  RelationalOperator: '<S86>/Equal1'
   */
  if (rtb_NotEqual_d && ((((int16_T)rtb_SignPreSat & 128U) != 0U ? (int16_T)
                          rtb_SignPreSat | -128 : (int16_T)rtb_SignPreSat & 127)
       == ((tmp & 128U) != 0U ? tmp | -128 : tmp & 127))) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S86>/Switch' */

  /* Update for DiscreteIntegrator: '<S95>/Integrator' */
  foc_ts_DW->Integrator_DSTATE += 0.0001 * rtb_IProdOut;

  /* Switch: '<S34>/Switch' incorporates:
   *  Constant: '<S34>/Constant1'
   *  Logic: '<S34>/AND1'
   *  Logic: '<S34>/AND2'
   *  Logic: '<S34>/AND3'
   *  Logic: '<S34>/NOT1'
   *  Logic: '<S34>/NOT2'
   *  Logic: '<S34>/OR1'
   */
  if (rtb_NotEqual_p && ((rtb_Equal1_j && rtb_Equal2) || ((!rtb_Equal1_j) &&
        (!rtb_Equal2)))) {
    rtb_IProdOut_e = 0.0;
  }

  /* End of Switch: '<S34>/Switch' */

  /* Update for DiscreteIntegrator: '<S43>/Integrator' */
  foc_ts_DW->Integrator_DSTATE_j += 0.0001 * rtb_IProdOut_e;

  /* Signum: '<S136>/SignPreIntegrator' */
  if (rtb_IProdOut_d < 0.0) {
    /* DataTypeConversion: '<S136>/DataTypeConv2' */
    tmp = -1;
  } else if (rtb_IProdOut_d > 0.0) {
    /* DataTypeConversion: '<S136>/DataTypeConv2' */
    tmp = 1;
  } else {
    /* DataTypeConversion: '<S136>/DataTypeConv2' */
    tmp = (int16_T)rtb_IProdOut_d;
  }

  /* End of Signum: '<S136>/SignPreIntegrator' */

  /* Switch: '<S136>/Switch' incorporates:
   *  Constant: '<S136>/Constant1'
   *  DataTypeConversion: '<S136>/DataTypeConv1'
   *  DataTypeConversion: '<S136>/DataTypeConv2'
   *  Logic: '<S136>/AND3'
   *  RelationalOperator: '<S136>/Equal1'
   */
  if (rtb_NotEqual && ((((int16_T)rtb_Integrator_l & 128U) != 0U ? (int16_T)
                        rtb_Integrator_l | -128 : (int16_T)rtb_Integrator_l &
                        127) == ((tmp & 128U) != 0U ? tmp | -128 : tmp & 127)))
  {
    rtb_IProdOut_d = 0.0;
  }

  /* End of Switch: '<S136>/Switch' */

  /* Update for DiscreteIntegrator: '<S145>/Integrator' */
  foc_ts_DW->Integrator_DSTATE_a += 0.0001 * rtb_IProdOut_d;

  /* Saturate: '<S6>/Saturation2' */
  if (*foc_ts_Y_d_u_1_nom > 1.0) {
    /* Sum: '<S6>/Add2' incorporates:
     *  Outport: '<Root>/d_u_1_nom'
     */
    *foc_ts_Y_d_u_1_nom = 1.0;
  } else {
    if (*foc_ts_Y_d_u_1_nom < 0.0) {
      /* Sum: '<S6>/Add2' incorporates:
       *  Outport: '<Root>/d_u_1_nom'
       */
      *foc_ts_Y_d_u_1_nom = 0.0;
    }
  }

  if (*foc_ts_Y_d_u_2_nom > 1.0) {
    /* Sum: '<S6>/Add2' incorporates:
     *  Outport: '<Root>/d_u_2_nom'
     */
    *foc_ts_Y_d_u_2_nom = 1.0;
  } else {
    if (*foc_ts_Y_d_u_2_nom < 0.0) {
      /* Sum: '<S6>/Add2' incorporates:
       *  Outport: '<Root>/d_u_2_nom'
       */
      *foc_ts_Y_d_u_2_nom = 0.0;
    }
  }

  if (*foc_ts_Y_d_u_3_nom > 1.0) {
    /* Sum: '<S6>/Add2' incorporates:
     *  Outport: '<Root>/d_u_3_nom'
     */
    *foc_ts_Y_d_u_3_nom = 1.0;
  } else {
    if (*foc_ts_Y_d_u_3_nom < 0.0) {
      /* Sum: '<S6>/Add2' incorporates:
       *  Outport: '<Root>/d_u_3_nom'
       */
      *foc_ts_Y_d_u_3_nom = 0.0;
    }
  }

  /* End of Saturate: '<S6>/Saturation2' */
  /* End of Outputs for SubSystem: '<Root>/foc_ts' */
}

/* Model initialize function */
void foc_ts_initialize(RT_MODEL_foc_ts_T *const foc_ts_M, real_T
  *foc_ts_U_d_u_dc, real_T *foc_ts_U_d_nSoll, real_T *foc_ts_U_d_omega_mech,
  real_T *foc_ts_U_d_theta_mech, real_T *foc_ts_U_d_i_a, real_T *foc_ts_U_d_i_b,
  real_T *foc_ts_U_d_i_c, real_T *foc_ts_U_d_K_p_d, real_T *foc_ts_U_d_K_i_d,
  real_T *foc_ts_U_d_K_p_q, real_T *foc_ts_U_d_K_i_q, real_T *foc_ts_U_d_K_p_n,
  real_T *foc_ts_U_d_K_i_n, real_T *foc_ts_U_i_d_soll, real_T *foc_ts_U_i_q_soll,
  real_T *foc_ts_Y_d_u_1_nom, real_T *foc_ts_Y_d_u_2_nom, real_T
  *foc_ts_Y_d_u_3_nom, real_T *foc_ts_Y_d_u_d, real_T *foc_ts_Y_d_u_q, real_T
  *foc_ts_Y_iqSollFB, real_T *foc_ts_Y_id_ist, real_T *foc_ts_Y_iq_ist, real_T
  *foc_ts_Y_theta_mech_out)
{
  DW_foc_ts_T *foc_ts_DW = foc_ts_M->dwork;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)foc_ts_DW, 0,
                sizeof(DW_foc_ts_T));

  /* external inputs */
  *foc_ts_U_d_u_dc = 0.0;
  *foc_ts_U_d_nSoll = 0.0;
  *foc_ts_U_d_omega_mech = 0.0;
  *foc_ts_U_d_theta_mech = 0.0;
  *foc_ts_U_d_i_a = 0.0;
  *foc_ts_U_d_i_b = 0.0;
  *foc_ts_U_d_i_c = 0.0;
  *foc_ts_U_d_K_p_d = 0.0;
  *foc_ts_U_d_K_i_d = 0.0;
  *foc_ts_U_d_K_p_q = 0.0;
  *foc_ts_U_d_K_i_q = 0.0;
  *foc_ts_U_d_K_p_n = 0.0;
  *foc_ts_U_d_K_i_n = 0.0;
  *foc_ts_U_i_d_soll = 0.0;
  *foc_ts_U_i_q_soll = 0.0;

  /* external outputs */
  (*foc_ts_Y_d_u_1_nom) = 0.0;
  (*foc_ts_Y_d_u_2_nom) = 0.0;
  (*foc_ts_Y_d_u_3_nom) = 0.0;
  (*foc_ts_Y_d_u_d) = 0.0;
  (*foc_ts_Y_d_u_q) = 0.0;
  (*foc_ts_Y_iqSollFB) = 0.0;
  (*foc_ts_Y_id_ist) = 0.0;
  (*foc_ts_Y_iq_ist) = 0.0;
  (*foc_ts_Y_theta_mech_out) = 0.0;
}

/* Model terminate function */
void foc_ts_terminate(RT_MODEL_foc_ts_T *const foc_ts_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(foc_ts_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
