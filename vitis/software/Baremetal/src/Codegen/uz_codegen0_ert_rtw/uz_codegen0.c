/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 3.5
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Dec  2 15:28:40 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (8), Warning (1), Error (0)
 */

#include "uz_codegen0.h"

/* Forward declaration for local functions */
static real32_T mod(real32_T x);
static void linspace(real32_T d1, real32_T d2, real32_T y[8]);

/* Function for MATLAB Function: '<S1>/MATLAB Function' */
static real32_T mod(real32_T x)
{
  real32_T r;
  if (x == 0.0F) {
    r = 0.0F;
  } else {
    boolean_T rEQ0;
    r = fmodf(x, 6.28318548F);
    rEQ0 = (r == 0.0F);
    if (!rEQ0) {
      real32_T q;
      q = fabsf(x / 6.28318548F);
      rEQ0 = (fabsf(q - floorf(q + 0.5F)) <= 1.1920929E-7F * q);
    }

    if (rEQ0) {
      r = 0.0F;
    } else if (x < 0.0F) {
      r += 6.28318548F;
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S1>/MATLAB Function' */
static void linspace(real32_T d1, real32_T d2, real32_T y[8])
{
  int32_T c_k;
  y[7] = d2;
  y[0] = d1;
  if (d1 == -d2) {
    real32_T delta1;
    delta1 = d2 / 7.0F;
    for (c_k = 0; c_k < 6; c_k++) {
      y[c_k + 1] = (((real32_T)c_k + 2.0F) * 2.0F - 9.0F) * delta1;
    }
  } else if (((d1 < 0.0F) != (d2 < 0.0F)) && ((fabsf(d1) > 1.70141173E+38F) ||
              (fabsf(d2) > 1.70141173E+38F))) {
    real32_T delta1;
    real32_T delta2;
    delta1 = d1 / 7.0F;
    delta2 = d2 / 7.0F;
    for (c_k = 0; c_k < 6; c_k++) {
      y[c_k + 1] = (((real32_T)c_k + 1.0F) * delta2 + d1) - ((real32_T)c_k +
        1.0F) * delta1;
    }
  } else {
    real32_T delta1;
    delta1 = (d2 - d1) / 7.0F;
    for (c_k = 0; c_k < 6; c_k++) {
      y[c_k + 1] = ((real32_T)c_k + 1.0F) * delta1 + d1;
    }
  }
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  int32_T k;
  int32_T rtb_ILR_N_tmp;
  int32_T rtb_ILR_N_tmp_0;
  int32_T rtb_ILR_N_tmp_1;
  real32_T factorL_NL;
  real32_T factorL_NR;
  real32_T iL_NR;
  real32_T iR_NL;
  real32_T iR_NR;
  real32_T rtb_Add_idx_0;
  real32_T rtb_Add_idx_1;
  real32_T rtb_FOC_ENABLE_ILR_switch1;
  real32_T rtb_ILR_N;

  /* Sum: '<S1>/Add' incorporates:
   *  Inport: '<Root>/Id_act'
   *  Inport: '<Root>/Id_ref'
   *  Inport: '<Root>/Iq_act'
   *  Inport: '<Root>/Iq_ref'
   */
  rtb_Add_idx_0 = rtU->Id_ref - rtU->Id_act;
  rtb_Add_idx_1 = rtU->Iq_ref - rtU->Iq_act;

  /* MultiPortSwitch: '<S1>/FOC_ENABLE_ILR_switch1' incorporates:
   *  Constant: '<S1>/LearningFactor'
   *  Constant: '<S1>/LearningFactor0'
   *  Inport: '<Root>/FOC_ENABLE_HC'
   */
  if (!rtU->FOC_ENABLE_HC) {
    rtb_FOC_ENABLE_ILR_switch1 = 0.0F;
  } else {
    rtb_FOC_ENABLE_ILR_switch1 = 0.3F;
  }

  /* End of MultiPortSwitch: '<S1>/FOC_ENABLE_ILR_switch1' */

  /* Product: '<S1>/Divide' incorporates:
   *  Constant: '<S1>/f_ab'
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/omega_el'
   */
  rtb_ILR_N = 10000.0F / (0.159154937F * rtU->omega_el);

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Constant: '<S1>/InvImp_d'
   *  Constant: '<S1>/InvImp_d1'
   *  Constant: '<S1>/NVec'
   *  Constant: '<S1>/unlearnFactor'
   *  Inport: '<Root>/angle'
   */
  /* MATLAB Function 'uz_codegen/MATLAB Function': '<S2>:1' */
  /* '<S2>:1:3' period = single(2*pi); */
  /* '<S2>:1:5' LL = single(7); */
  /* '<S2>:1:6' m = single(3); */
  /*  leading zeros */
  /* n = 4; % following zeros */
  /* InvImp_q = InvImp_d; */
  /* global updateCurve_d; */
  /* global updateCurve_q; */
  /* '<S2>:1:18' if isempty(step) */
  /*  if isempty(oldIndex) */
  /*      oldIndex = ceil(N)+1; */
  /*  end  */
  /* determine position between Ns */
  /* '<S2>:1:29' [~,index_NVec] = min(abs(NVec-N)); */
  for (k = 0; k < 9; k++) {
    rtDW->varargin_1[k] = fabsf(rtConstP.NVec_Value[k] - rtb_ILR_N);
  }

  rtDW->factorNR = rtDW->varargin_1[0];
  k = 0;
  for (rtDW->iL_NVec = 0; rtDW->iL_NVec < 8; rtDW->iL_NVec++) {
    rtDW->NR = rtDW->varargin_1[rtDW->iL_NVec + 1];
    if (rtDW->factorNR > rtDW->NR) {
      rtDW->factorNR = rtDW->NR;
      k = rtDW->iL_NVec + 1;
    }
  }

  /* '<S2>:1:30' minVal = NVec(index_NVec); */
  /* predefinition */
  /* '<S2>:1:32' iL_NVec = index_NVec; */
  rtDW->iL_NVec = k;

  /* '<S2>:1:33' iR_NVec = index_NVec + 1; */
  rtDW->iR_NVec = k + 1;

  /* definition */
  /* '<S2>:1:35' if minVal > N */
  if ((rtConstP.NVec_Value[k] <= rtb_ILR_N) && (rtConstP.NVec_Value[k] <=
       rtb_ILR_N)) {
    /* '<S2>:1:38' elseif minVal <= N */
    /* '<S2>:1:39' iR_NVec = index_NVec; */
    rtDW->iR_NVec = k;

    /* '<S2>:1:40' iL_NVec = index_NVec -1; */
    rtDW->iL_NVec = k - 1;
  } else {
    /* '<S2>:1:36' iL_NVec = index_NVec; */
    /* '<S2>:1:37' iR_NVec = index_NVec + 1; */
  }

  /* '<S2>:1:42' if N >= NVec(1) */
  if (rtb_ILR_N >= 350.0F) {
    /* '<S2>:1:43' iL_NVec = index_NVec; */
    rtDW->iL_NVec = k;

    /* '<S2>:1:44' iR_NVec = index_NVec + 1; */
    rtDW->iR_NVec = k + 1;
  } else if (rtb_ILR_N <= 25.0F) {
    /* '<S2>:1:45' elseif N <= NVec(end) */
    /* '<S2>:1:46' iR_NVec = index_NVec; */
    rtDW->iR_NVec = k;

    /* '<S2>:1:47' iL_NVec = index_NVec -1; */
    rtDW->iL_NVec = k - 1;
  }

  /* '<S2>:1:49' NL = NVec(iL_NVec); */
  rtDW->NL = rtConstP.NVec_Value[rtDW->iL_NVec];

  /* '<S2>:1:50' NR = NVec(iR_NVec); */
  rtDW->NR = rtConstP.NVec_Value[rtDW->iR_NVec];

  /* '<S2>:1:51' diffNLNR = NR-NL; */
  /* '<S2>:1:52' factorNL = 1-(N-NL)/diffNLNR; */
  rtDW->factorNL = 1.0F - (rtb_ILR_N - rtConstP.NVec_Value[rtDW->iL_NVec]) /
    (rtConstP.NVec_Value[rtDW->iR_NVec] - rtConstP.NVec_Value[rtDW->iL_NVec]);

  /* '<S2>:1:53' factorNR = 1-factorNL; */
  rtDW->factorNR = 1.0F - rtDW->factorNL;

  /* in case N is smaller or bigger than the smallest/biggest N in NVec */
  /* '<S2>:1:55' if N <= NVec(end) */
  if (rtb_ILR_N <= 25.0F) {
    /* '<S2>:1:56' NL = NVec(end-1); */
    rtDW->NL = 50.0F;

    /* '<S2>:1:57' NR = NVec(end); */
    rtDW->NR = 25.0F;

    /* '<S2>:1:58' factorNL = single(0); */
    rtDW->factorNL = 0.0F;

    /* '<S2>:1:59' factorNR = single(1); */
    rtDW->factorNR = 1.0F;
  } else if (rtb_ILR_N > 350.0F) {
    /* '<S2>:1:60' elseif N > NVec(1) */
    /* '<S2>:1:61' NL = NVec(1); */
    rtDW->NL = 350.0F;

    /* '<S2>:1:62' NR = NVec(2); */
    rtDW->NR = 300.0F;

    /* '<S2>:1:63' factorNL = single(1); */
    rtDW->factorNL = 1.0F;

    /* '<S2>:1:64' factorNR = single(0); */
    rtDW->factorNR = 0.0F;
  }

  /* determine position in learning curve, prepare interpolation */
  /* '<S2>:1:68' index_NL = mod(angle,period)/period*NL; */
  rtb_ILR_N = mod(rtU->angle);
  rtDW->index_NL = rtb_ILR_N / 6.28318548F * rtDW->NL;

  /* '<S2>:1:69' iL_NL = floor(index_NL); */
  rtDW->iL_NL = floorf(rtDW->index_NL);

  /* '<S2>:1:70' factorL_NL = 1-abs(index_NL-iL_NL); */
  factorL_NL = 1.0F - fabsf(rtDW->index_NL - rtDW->iL_NL);

  /* '<S2>:1:71' if (iL_NL < 1) */
  if (rtDW->iL_NL < 1.0F) {
    /* '<S2>:1:72' iL_NL = NL; */
    rtDW->iL_NL = rtDW->NL;
  }

  /* '<S2>:1:74' if (iL_NL > NL) */
  if (rtDW->iL_NL > rtDW->NL) {
    /* '<S2>:1:75' iL_NL = single(1); */
    rtDW->iL_NL = 1.0F;
  }

  /* '<S2>:1:78' iR_NL = iL_NL+1; */
  iR_NL = rtDW->iL_NL + 1.0F;

  /* '<S2>:1:79' if (iR_NL > NL) */
  if (rtDW->iL_NL + 1.0F > rtDW->NL) {
    /* '<S2>:1:80' iR_NL = single(1); */
    iR_NL = 1.0F;
  }

  /* '<S2>:1:82' factorR_NL = 1-factorL_NL; */
  /* '<S2>:1:84' index_NR = mod(angle,period)/period*NR; */
  rtb_ILR_N = rtb_ILR_N / 6.28318548F * rtDW->NR;

  /* '<S2>:1:85' iL_NR = floor(index_NR); */
  iL_NR = floorf(rtb_ILR_N);

  /* '<S2>:1:86' factorL_NR = 1-abs(index_NR-iL_NR); */
  factorL_NR = 1.0F - fabsf(rtb_ILR_N - iL_NR);

  /* '<S2>:1:87' if (iL_NR < 1) */
  if (iL_NR < 1.0F) {
    /* '<S2>:1:88' iL_NR = NR; */
    iL_NR = rtDW->NR;
  }

  /* '<S2>:1:90' if (iL_NR > NR) */
  if (iL_NR > rtDW->NR) {
    /* '<S2>:1:91' iL_NR = single(1); */
    iL_NR = 1.0F;
  }

  /* '<S2>:1:94' iR_NR = iL_NR+1; */
  iR_NR = iL_NR + 1.0F;

  /* '<S2>:1:95' if (iR_NR > NR) */
  if (iL_NR + 1.0F > rtDW->NR) {
    /* '<S2>:1:96' iR_NR = single(1); */
    iR_NR = 1.0F;
  }

  /* '<S2>:1:98' factorR_NR = 1-factorL_NR; */
  /* '<S2>:1:100' correctionNLd = (correctionCurve_d(iL_NVec,iL_NL)*factorL_NL + correctionCurve_d(iL_NVec,iR_NL)*factorR_NL); */
  /* '<S2>:1:101' correctionNRd = (correctionCurve_d(iR_NVec,iL_NR)*factorL_NR + correctionCurve_d(iR_NVec,iR_NR)*factorR_NR); */
  /* '<S2>:1:102' correctiond = correctionNLd*factorNL + correctionNRd*factorNR; */
  k = ((int32_T)rtDW->iL_NL - 1) * 9 + rtDW->iL_NVec;
  rtb_ILR_N_tmp = ((int32_T)iR_NL - 1) * 9 + rtDW->iL_NVec;
  rtb_ILR_N_tmp_0 = ((int32_T)iL_NR - 1) * 9 + rtDW->iR_NVec;
  rtb_ILR_N_tmp_1 = ((int32_T)iR_NR - 1) * 9 + rtDW->iR_NVec;
  rtb_ILR_N = ((1.0F - factorL_NL) * rtDW->correctionCurve_d[rtb_ILR_N_tmp] +
               rtDW->correctionCurve_d[k] * factorL_NL) * rtDW->factorNL +
    ((1.0F - factorL_NR) * rtDW->correctionCurve_d[rtb_ILR_N_tmp_1] +
     rtDW->correctionCurve_d[rtb_ILR_N_tmp_0] * factorL_NR) * rtDW->factorNR;

  /* '<S2>:1:103' correctionNLq = (correctionCurve_q(iL_NVec,iL_NL)*factorL_NL + correctionCurve_q(iL_NVec,iR_NL)*factorR_NL); */
  /* '<S2>:1:104' correctionNRq = (correctionCurve_q(iR_NVec,iL_NR)*factorL_NR + correctionCurve_q(iR_NVec,iR_NR)*factorR_NR); */
  /* '<S2>:1:105' correctionq = correctionNLq*factorNL + correctionNRq*factorNR; */
  rtDW->index_NL = ((1.0F - factorL_NL) * rtDW->correctionCurve_q[rtb_ILR_N_tmp]
                    + rtDW->correctionCurve_q[k] * factorL_NL) * rtDW->factorNL
    + ((1.0F - factorL_NR) * rtDW->correctionCurve_q[rtb_ILR_N_tmp_1] +
       rtDW->correctionCurve_q[rtb_ILR_N_tmp_0] * factorL_NR) * rtDW->factorNR;

  /*  if (iL == oldIndex) */
  /*      %avoid learning twice if same index is called a second time */
  /*      return */
  /*  end */
  /*  oldIndex = iL; */
  /* '<S2>:1:113' iLrange_NL = zeros(1,LL+1); */
  /* '<S2>:1:114' iRrange_NL = zeros(1,LL+1); */
  /* '<S2>:1:115' iLrange_NR = zeros(1,LL+1); */
  /* '<S2>:1:116' iRrange_NR = zeros(1,LL+1); */
  /*  calculate index ranges, using indices before assignment (subscripting) is */
  /*  necessary for MATLAB2011 precompiler! */
  /*  wegen Laufzeit: statt LL direkt 7, statt m direkt 3 */
  /* '<S2>:1:121' iLrange_NL(1:LL+1) = linspace(iL_NL,(iL_NL+LL),(LL+1))-m; */
  linspace(rtDW->iL_NL, rtDW->iL_NL + 7.0F, rtDW->fv);
  for (k = 0; k < 8; k++) {
    rtDW->iLrange_NL[k] = rtDW->fv[k] - 3.0F;
  }

  /* '<S2>:1:122' iRrange_NL(1:LL+1) = linspace(iR_NL,(iR_NL+LL),(LL+1))-m; */
  linspace(iR_NL, iR_NL + 7.0F, rtDW->fv);
  for (k = 0; k < 8; k++) {
    rtDW->iRrange_NL[k] = rtDW->fv[k] - 3.0F;
  }

  /* '<S2>:1:123' iLrange_NR(1:LL+1) = linspace(iL_NR,(iL_NR+LL),(LL+1))-m; */
  linspace(iL_NR, iL_NR + 7.0F, rtDW->fv);

  /* '<S2>:1:124' iRrange_NR(1:LL+1) = linspace(iR_NR,(iR_NR+LL),(LL+1))-m; */
  linspace(iR_NR, iR_NR + 7.0F, rtDW->fv1);

  /*  wrap all indices smaller 1 or greater N to prevent index exceeds */
  /*  dimensions error */
  /* '<S2>:1:127' iLrange_NL = iLrange_NL + NL*(iLrange_NL<1) - NL*(iLrange_NL>NL); */
  /* '<S2>:1:128' iRrange_NL = iRrange_NL + NL*(iRrange_NL<1) - NL*(iRrange_NL>NL); */
  /* '<S2>:1:129' iLrange_NR = iLrange_NR + NR*(iLrange_NR<1) - NR*(iLrange_NR>NR); */
  /* '<S2>:1:130' iRrange_NR = iRrange_NR + NR*(iRrange_NR<1) - NR*(iRrange_NR>NR); */
  for (k = 0; k < 8; k++) {
    rtDW->iLrange_NR[k] = rtDW->fv[k] - 3.0F;
    rtDW->iRrange_NR = rtDW->fv1[k] - 3.0F;
    rtDW->iLrange_NR_k = rtDW->iLrange_NR[k];
    rtDW->iRrange_NL_c = rtDW->iRrange_NL[k];
    rtDW->iLrange_NL_m = rtDW->iLrange_NL[k];
    rtDW->b_iLrange_NL[k] = ((real32_T)(rtDW->iLrange_NL_m < 1.0) * rtDW->NL +
      (real32_T)rtDW->iLrange_NL_m) - (real32_T)(rtDW->iLrange_NL_m > rtDW->NL) *
      rtDW->NL;
    rtDW->b_iRrange_NL[k] = ((real32_T)(rtDW->iRrange_NL_c < 1.0) * rtDW->NL +
      (real32_T)rtDW->iRrange_NL_c) - (real32_T)(rtDW->iRrange_NL_c > rtDW->NL) *
      rtDW->NL;
    rtDW->b_iLrange_NR[k] = ((real32_T)(rtDW->iLrange_NR_k < 1.0) * rtDW->NR +
      (real32_T)rtDW->iLrange_NR_k) - (real32_T)(rtDW->iLrange_NR_k > rtDW->NR) *
      rtDW->NR;
    rtDW->b_iRrange_NR[k] = ((real32_T)(rtDW->iRrange_NR < 1.0) * rtDW->NR +
      (real32_T)rtDW->iRrange_NR) - (real32_T)(rtDW->iRrange_NR > rtDW->NR) *
      rtDW->NR;
  }

  /* '<S2>:1:132' correctionCurve_d(iL_NVec,iLrange_NL) = correctionCurve_d(iL_NVec,iLrange_NL)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:133'     learnFactor*factorL_NL*(errord)*InvImp_d*factorNL; */
  rtDW->NL = 1.0F - rtb_FOC_ENABLE_ILR_switch1 * 0.001F;
  rtDW->iL_NL = rtb_FOC_ENABLE_ILR_switch1 * factorL_NL;
  rtDW->NR = rtDW->iL_NL * rtb_Add_idx_0;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_d[((int32_T)rtDW->b_iLrange_NL[k] - 1) *
      9 + rtDW->iL_NVec] * rtDW->NL + rtDW->NR * rtConstP.InvImp_d_Value[k] *
      rtDW->factorNL;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_d[rtDW->iL_NVec + 9 * ((int32_T)rtDW->b_iLrange_NL[k]
      - 1)] = rtDW->fv[k];
  }

  /* '<S2>:1:134' correctionCurve_d(iL_NVec,iRrange_NL) = correctionCurve_d(iL_NVec,iRrange_NL)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:135'     learnFactor*factorR_NL*(errord)*InvImp_d*factorNL; */
  factorL_NL = (1.0F - factorL_NL) * rtb_FOC_ENABLE_ILR_switch1;
  rtDW->NR = factorL_NL * rtb_Add_idx_0;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_d[((int32_T)rtDW->b_iRrange_NL[k] - 1) *
      9 + rtDW->iL_NVec] * rtDW->NL + rtDW->NR * rtConstP.InvImp_d_Value[k] *
      rtDW->factorNL;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_d[rtDW->iL_NVec + 9 * ((int32_T)rtDW->b_iRrange_NL[k]
      - 1)] = rtDW->fv[k];
  }

  /* '<S2>:1:136' correctionCurve_d(iR_NVec,iLrange_NR) = correctionCurve_d(iR_NVec,iLrange_NR)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:137'     learnFactor*factorL_NR*(errord)*InvImp_d*factorNR; */
  iR_NL = rtb_FOC_ENABLE_ILR_switch1 * factorL_NR;
  rtDW->NR = iR_NL * rtb_Add_idx_0;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_d[((int32_T)rtDW->b_iLrange_NR[k] - 1) *
      9 + rtDW->iR_NVec] * rtDW->NL + rtDW->NR * rtConstP.InvImp_d_Value[k] *
      rtDW->factorNR;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_d[rtDW->iR_NVec + 9 * ((int32_T)rtDW->b_iLrange_NR[k]
      - 1)] = rtDW->fv[k];
  }

  /* '<S2>:1:138' correctionCurve_d(iR_NVec,iRrange_NR) = correctionCurve_d(iR_NVec,iRrange_NR)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:139'     learnFactor*factorR_NR*(errord)*InvImp_d*factorNR; */
  rtb_FOC_ENABLE_ILR_switch1 *= 1.0F - factorL_NR;
  rtDW->NR = rtb_FOC_ENABLE_ILR_switch1 * rtb_Add_idx_0;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_d[((int32_T)rtDW->b_iRrange_NR[k] - 1) *
      9 + rtDW->iR_NVec] * rtDW->NL + rtDW->NR * rtConstP.InvImp_d_Value[k] *
      rtDW->factorNR;
  }

  /* '<S2>:1:141' correctionCurve_q(iL_NVec,iLrange_NL) = correctionCurve_q(iL_NVec,iLrange_NL)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:142'     learnFactor*factorL_NL*(errorq)*InvImp_q*factorNL; */
  rtDW->NR = rtDW->iL_NL * rtb_Add_idx_1;
  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_d[rtDW->iR_NVec + 9 * ((int32_T)rtDW->b_iRrange_NR[k]
      - 1)] = rtDW->fv[k];
    rtDW->fv1[k] = rtDW->correctionCurve_q[((int32_T)rtDW->b_iLrange_NL[k] - 1) *
      9 + rtDW->iL_NVec] * rtDW->NL + rtDW->NR * rtConstP.InvImp_d1_Value[k] *
      rtDW->factorNL;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_q[rtDW->iL_NVec + 9 * ((int32_T)rtDW->b_iLrange_NL[k]
      - 1)] = rtDW->fv1[k];
  }

  /* '<S2>:1:143' correctionCurve_q(iL_NVec,iRrange_NL) = correctionCurve_q(iL_NVec,iRrange_NL)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:144'     learnFactor*factorR_NL*(errorq)*InvImp_q*factorNL; */
  factorL_NL *= rtb_Add_idx_1;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_q[((int32_T)rtDW->b_iRrange_NL[k] - 1) *
      9 + rtDW->iL_NVec] * rtDW->NL + factorL_NL * rtConstP.InvImp_d1_Value[k] *
      rtDW->factorNL;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_q[rtDW->iL_NVec + 9 * ((int32_T)rtDW->b_iRrange_NL[k]
      - 1)] = rtDW->fv[k];
  }

  /* '<S2>:1:145' correctionCurve_q(iR_NVec,iLrange_NR) = correctionCurve_q(iR_NVec,iLrange_NR)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:146'     learnFactor*factorL_NR*(errorq)*InvImp_q*factorNR; */
  factorL_NL = iR_NL * rtb_Add_idx_1;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_q[((int32_T)rtDW->b_iLrange_NR[k] - 1) *
      9 + rtDW->iR_NVec] * rtDW->NL + factorL_NL * rtConstP.InvImp_d1_Value[k] *
      rtDW->factorNR;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_q[rtDW->iR_NVec + 9 * ((int32_T)rtDW->b_iLrange_NR[k]
      - 1)] = rtDW->fv[k];
  }

  /* '<S2>:1:147' correctionCurve_q(iR_NVec,iRrange_NR) = correctionCurve_q(iR_NVec,iRrange_NR)*(1-learnFactor*unlearnFactor) + ... */
  /* '<S2>:1:148'     learnFactor*factorR_NR*(errorq)*InvImp_q*factorNR; */
  rtb_FOC_ENABLE_ILR_switch1 *= rtb_Add_idx_1;
  for (k = 0; k < 8; k++) {
    rtDW->fv[k] = rtDW->correctionCurve_q[((int32_T)rtDW->b_iRrange_NR[k] - 1) *
      9 + rtDW->iR_NVec] * rtDW->NL + rtb_FOC_ENABLE_ILR_switch1 *
      rtConstP.InvImp_d1_Value[k] * rtDW->factorNR;
  }

  for (k = 0; k < 8; k++) {
    rtDW->correctionCurve_q[rtDW->iR_NVec + 9 * ((int32_T)rtDW->b_iRrange_NR[k]
      - 1)] = rtDW->fv[k];
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function' */

  /* MultiPortSwitch: '<S1>/FOC_ENABLE_ILR_switch' incorporates:
   *  Inport: '<Root>/FOC_ENABLE_HC'
   */
  /*  update correctionCurve with updateCurve */
  /*  update correctionCurve of currently used NL and NR */
  /*  iUpdate_NL = round(iL_NL + NL/2); */
  /*  if iUpdate_NL > NL */
  /*      iUpdate_NL = iUpdate_NL - NL; */
  /*  end */
  /*  % correctionCurve_d(iL_NVec,iUpdate_NL) = updateCurve_d(iL_NVec,iUpdate_NL); */
  /*  correctionCurve_q(iL_NVec,iUpdate_NL) = updateCurve_q(iL_NVec,iUpdate_NL); */
  /*  iUpdate_NR = round(iL_NR + NR/2); */
  /*  if iUpdate_NR > NR */
  /*      iUpdate_NR = iUpdate_NR - NR; */
  /*  end */
  /*  % correctionCurve_d(iR_NVec,iUpdate_NR) = updateCurve_d(iR_NVec,iUpdate_NR); */
  /*  correctionCurve_q(iR_NVec,iUpdate_NR) = updateCurve_q(iR_NVec,iUpdate_NR); */
  /*   */
  /*  % update rest of correctionCurve */
  /*  NVecUp = [1:length(NVec)]; */
  /*  NVecUp = NVecUp(NVecUp~= iL_NVec & NVecUp~= iR_NVec); */
  /*  % correctionCurve_d(NVecUp,:) = updateCurve_d(NVecUp,:); */
  /*  correctionCurve_q(NVecUp,:) = updateCurve_q(NVecUp,:); */
  /* '<S2>:1:172' if reset == 1 */
  /* '<S2>:1:185' if reset == -1 */
  if (!rtU->FOC_ENABLE_HC) {
    /* Outport: '<Root>/Idq_ref_ILR' incorporates:
     *  Inport: '<Root>/Id_ref'
     *  Inport: '<Root>/Iq_ref'
     */
    rtY->Idq_ref_ILR[0] = rtU->Id_ref;
    rtY->Idq_ref_ILR[1] = rtU->Iq_ref;
  } else {
    /* Outport: '<Root>/Idq_ref_ILR' incorporates:
     *  Inport: '<Root>/Id_ref'
     *  Inport: '<Root>/Iq_ref'
     *  Sum: '<S1>/Add1'
     */
    rtY->Idq_ref_ILR[0] = rtU->Id_ref + rtb_ILR_N;
    rtY->Idq_ref_ILR[1] = rtU->Iq_ref + rtDW->index_NL;
  }

  /* End of MultiPortSwitch: '<S1>/FOC_ENABLE_ILR_switch' */

  /* Outport: '<Root>/memoryd' incorporates:
   *  MATLAB Function: '<S1>/Read Memory Function'
   */
  /* MATLAB Function 'uz_codegen/Read Memory Function': '<S3>:1' */
  /* '<S3>:1:8' if isempty(step) */
  /* '<S3>:1:11' if isempty(wait) */
  /* '<S3>:1:15' memoryd = single(0); */
  rtY->memoryd = 0.0F;

  /* Outport: '<Root>/memoryq' incorporates:
   *  MATLAB Function: '<S1>/Read Memory Function'
   */
  /* '<S3>:1:16' memoryq = single(0); */
  rtY->memoryq = 0.0F;

  /* Outport: '<Root>/step_out' incorporates:
   *  MATLAB Function: '<S1>/Read Memory Function'
   */
  /* '<S3>:1:18' step_out = step; */
  rtY->step_out = rtDW->step;

  /* MATLAB Function: '<S1>/Read Memory Function' incorporates:
   *  Constant: '<S1>/NVec'
   *  Inport: '<Root>/FOC_READ_ILR_MEMORY'
   */
  /* '<S3>:1:19' steps_NVec = length(NVec)*max(NVec); */
  rtDW->factorNR = 350.0F;
  for (k = 0; k < 8; k++) {
    rtDW->NR = rtConstP.NVec_Value[k + 1];
    if (rtDW->factorNR < rtDW->NR) {
      rtDW->factorNR = rtDW->NR;
    }
  }

  /* '<S3>:1:21' if enable == 1 */
  if (rtU->FOC_READ_ILR_MEMORY) {
    /* Outport: '<Root>/memoryd' */
    /* '<S3>:1:22' memoryd = correctionCurve_d(step); */
    rtY->memoryd = rtDW->correctionCurve_d[(int32_T)rtDW->step - 1];

    /* Outport: '<Root>/memoryq' */
    /* '<S3>:1:23' memoryq = correctionCurve_q(step); */
    rtY->memoryq = rtDW->correctionCurve_q[(int32_T)rtDW->step - 1];

    /* '<S3>:1:24' if step == steps_NVec */
    if (9.0F * rtDW->factorNR == rtDW->step) {
      /* '<S3>:1:25' step = single(0); */
      rtDW->step = 0.0F;
    }

    /* '<S3>:1:27' if wait == 20 */
    if (rtDW->wait == 20.0F) {
      /* '<S3>:1:28' step = step+1; */
      rtDW->step++;

      /* '<S3>:1:29' wait = single(0); */
      rtDW->wait = 0.0F;
    }

    /* '<S3>:1:31' wait = wait +1; */
    rtDW->wait++;
  }
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
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
  (void)memset(rtY, 0, sizeof(ExtY));

  /* SystemInitialize for MATLAB Function: '<S1>/MATLAB Function' */
  /* '<S2>:1:19' step = single(1); */
  rtDW->step_p = 1.0F;

  /* SystemInitialize for MATLAB Function: '<S1>/Read Memory Function' */
  /* '<S3>:1:9' step = single(1); */
  rtDW->step = 1.0F;

  /* '<S3>:1:12' wait = single(1); */
  rtDW->wait = 1.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
