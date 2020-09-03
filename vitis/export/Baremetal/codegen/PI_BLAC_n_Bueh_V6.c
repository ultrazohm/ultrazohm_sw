/*
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * File: PI_BLAC_n_Bueh_V6.c
 *
 * Code generated for Simulink model 'PI_BLAC_n_Bueh_V6'.
 *
 * Model version                  : 1.2662
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 19 16:27:44 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PI_BLAC_n_Bueh_V6.h"
#include "PI_BLAC_n_Bueh_V6_private.h"

/* Exported block parameters */
real_T Imax_AWUP = 8.0;                /* Variable: Imax_AWUP
                                        * Referenced by:
                                        *   '<S2>/Saturate'
                                        *   '<S3>/DeadZone'
                                        */
real_T T_Rn = 0.0064;                  /* Variable: T_Rn
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
real_T V_Rn = 0.017625;                 /* Variable: V_Rn //SW: 0.57625
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */

/* Model step function */
void PI_BLAC_n_Bueh_V6_step(RT_MODEL_PI_BLAC_n_Bueh_V6_T *const
  PI_BLAC_n_Bueh_V6_M, real_T PI_BLAC_n_Bueh_V6_U_n_ref_rpm, real_T
  PI_BLAC_n_Bueh_V6_U_n_meas_rpm, real_T *PI_BLAC_n_Bueh_V6_Y_iq_ref)
{
  P_PI_BLAC_n_Bueh_V6_T *PI_BLAC_n_Bueh_V6_P = ((P_PI_BLAC_n_Bueh_V6_T *)
    PI_BLAC_n_Bueh_V6_M->defaultParam);
  DW_PI_BLAC_n_Bueh_V6_T *PI_BLAC_n_Bueh_V6_DW = ((DW_PI_BLAC_n_Bueh_V6_T *)
    PI_BLAC_n_Bueh_V6_M->dwork);
  real_T rtb_IntegralGain;
  real_T rtb_SignDeltaU;
  real_T rtb_ZeroGain;
  int8_T tmp;

  /* Sum: '<S1>/Add' incorporates:
   *  Inport: '<Root>/n_meas_rpm'
   *  Inport: '<Root>/n_ref_rpm'
   */
  rtb_IntegralGain = PI_BLAC_n_Bueh_V6_U_n_ref_rpm -
    PI_BLAC_n_Bueh_V6_U_n_meas_rpm;

  /* Sum: '<S2>/Sum' incorporates:
   *  DiscreteIntegrator: '<S2>/Integrator'
   *  Gain: '<S2>/Proportional Gain'
   */
  rtb_SignDeltaU = V_Rn * rtb_IntegralGain +
    PI_BLAC_n_Bueh_V6_DW->Integrator_DSTATE;

  /* Saturate: '<S2>/Saturate' */
  if (rtb_SignDeltaU > Imax_AWUP) {
    /* Outport: '<Root>/iq_ref' */
    *PI_BLAC_n_Bueh_V6_Y_iq_ref = Imax_AWUP;
  } else if (rtb_SignDeltaU < -Imax_AWUP) {
    /* Outport: '<Root>/iq_ref' */
    *PI_BLAC_n_Bueh_V6_Y_iq_ref = -Imax_AWUP;
  } else {
    /* Outport: '<Root>/iq_ref' */
    *PI_BLAC_n_Bueh_V6_Y_iq_ref = rtb_SignDeltaU;
  }

  /* End of Saturate: '<S2>/Saturate' */

  /* Gain: '<S3>/ZeroGain' */
  rtb_ZeroGain = PI_BLAC_n_Bueh_V6_P->ZeroGain_Gain * rtb_SignDeltaU;

  /* DeadZone: '<S3>/DeadZone' */
  if (rtb_SignDeltaU > Imax_AWUP) {
    rtb_SignDeltaU -= Imax_AWUP;
  } else if (rtb_SignDeltaU >= -Imax_AWUP) {
    rtb_SignDeltaU = 0.0;
  } else {
    rtb_SignDeltaU -= -Imax_AWUP;
  }

  /* End of DeadZone: '<S3>/DeadZone' */

  /* RelationalOperator: '<S3>/NotEqual' */
  rtb_ZeroGain = (rtb_ZeroGain != rtb_SignDeltaU);

  /* Signum: '<S3>/SignDeltaU' */
  if (rtb_SignDeltaU < 0.0) {
    rtb_SignDeltaU = -1.0;
  } else {
    if (rtb_SignDeltaU > 0.0) {
      rtb_SignDeltaU = 1.0;
    }
  }

  /* End of Signum: '<S3>/SignDeltaU' */

  /* Gain: '<S2>/Integral Gain' */
  rtb_IntegralGain *= T_Rn;

  /* DataTypeConversion: '<S3>/DataTypeConv1' */
  if (rtb_SignDeltaU < 128.0) {
    tmp = (int8_T)rtb_SignDeltaU;
  } else {
    tmp = MAX_int8_T;
  }

  /* Signum: '<S3>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0) {
    rtb_SignDeltaU = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    rtb_SignDeltaU = 1.0;
  } else {
    rtb_SignDeltaU = rtb_IntegralGain;
  }

  /* End of Signum: '<S3>/SignPreIntegrator' */

  /* DataTypeConversion: '<S3>/DataTypeConv2' */
//  rtb_SignDeltaU = fmod(rtb_SignDeltaU, 256.0);

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant'
   *  DataTypeConversion: '<S3>/DataTypeConv1'
   *  DataTypeConversion: '<S3>/DataTypeConv2'
   *  Logic: '<S3>/AND'
   *  RelationalOperator: '<S3>/Equal'
   */
  if (((rtb_ZeroGain != 0.0) && ((rtb_SignDeltaU < 0.0 ? (int32_T)(int8_T)
         -(int8_T)(uint8_T)-rtb_SignDeltaU : (int32_T)(int8_T)(uint8_T)
         rtb_SignDeltaU) == tmp)) > PI_BLAC_n_Bueh_V6_P->Switch_Threshold) {
    rtb_IntegralGain = PI_BLAC_n_Bueh_V6_P->Constant_Value;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Update for DiscreteIntegrator: '<S2>/Integrator' */
  PI_BLAC_n_Bueh_V6_DW->Integrator_DSTATE +=
    PI_BLAC_n_Bueh_V6_P->Integrator_gainval * rtb_IntegralGain;
}

/* Model initialize function */
void PI_BLAC_n_Bueh_V6_initialize(RT_MODEL_PI_BLAC_n_Bueh_V6_T *const
  PI_BLAC_n_Bueh_V6_M, real_T *PI_BLAC_n_Bueh_V6_U_n_ref_rpm, real_T
  *PI_BLAC_n_Bueh_V6_U_n_meas_rpm, real_T *PI_BLAC_n_Bueh_V6_Y_iq_ref)
{
  P_PI_BLAC_n_Bueh_V6_T *PI_BLAC_n_Bueh_V6_P = ((P_PI_BLAC_n_Bueh_V6_T *)
    PI_BLAC_n_Bueh_V6_M->defaultParam);
  DW_PI_BLAC_n_Bueh_V6_T *PI_BLAC_n_Bueh_V6_DW = ((DW_PI_BLAC_n_Bueh_V6_T *)
    PI_BLAC_n_Bueh_V6_M->dwork);

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)PI_BLAC_n_Bueh_V6_DW, 0,
                sizeof(DW_PI_BLAC_n_Bueh_V6_T));

  /* external inputs */
  *PI_BLAC_n_Bueh_V6_U_n_ref_rpm = 0.0;
  *PI_BLAC_n_Bueh_V6_U_n_meas_rpm = 0.0;

  /* external outputs */
  (*PI_BLAC_n_Bueh_V6_Y_iq_ref) = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  PI_BLAC_n_Bueh_V6_DW->Integrator_DSTATE = PI_BLAC_n_Bueh_V6_P->Integrator_IC;
}

/* Model terminate function */
void PI_BLAC_n_Bueh_V6_terminate(RT_MODEL_PI_BLAC_n_Bueh_V6_T *const
  PI_BLAC_n_Bueh_V6_M)
{
/* (no terminate code required) */ //  UNUSED_PARAMETER(PI_BLAC_n_Bueh_V6_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
