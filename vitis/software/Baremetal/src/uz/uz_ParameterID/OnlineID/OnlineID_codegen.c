/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OnlineID.c
 *
 * Code generated for Simulink model 'OnlineID'.
 *
 * Model version                  : 2.371
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Dec 20 12:50:35 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#include "OnlineID_codegen.h"

/* Named constants for Chart: '<Root>/OnlineID' */
#define IN_CalcLinearParamsState       ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_OnlineIDSuperState          ((uint8_T)1U)
#define IN_PsiCalcState                ((uint8_T)2U)
#define IN_RefreshDataRegister         ((uint8_T)3U)
#define IN_TempPsiCalcState            ((uint8_T)4U)
#define IN_Waiting                     ((uint8_T)2U)

/* Forward declaration for local functions */
static void InitParams(ExtU_OnlineID_t *rtOnlineID_U, ExtY_OnlineID_t
  *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW);
static void enter_atomic_RefreshDataRegiste(ExtY_OnlineID_t *rtOnlineID_Y,
  DW_OnlineID_t *rtOnlineID_DW);
static void identParams(ExtU_OnlineID_t *rtOnlineID_U, ExtY_OnlineID_t
  *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW);
static void RefreshDataRegister_i1(DW_OnlineID_t *rtOnlineID_DW);
static boolean_T Break(const real32_T iq_reg_alt[50], const real32_T id_reg_alt
  [50], const real32_T om_reg_alt[5], const real32_T iq_reg_neu[10], const
  real32_T id_reg_neu[10], const real32_T om_reg_neu[5], ExtU_OnlineID_t
  *rtOnlineID_U);
static void enter_atomic_PsiCalcState(ExtU_OnlineID_t *rtOnlineID_U,
  ExtY_OnlineID_t *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW);
static void RefreshDataRegister_i(DW_OnlineID_t *rtOnlineID_DW);
static void CheckSteadyState(const real32_T iq_reg_in[50], const real32_T
  id_reg_in[50], const real32_T om_reg_in[5], uint32_T timer, boolean_T
  *allow_measurement, boolean_T *om_con, boolean_T *iq_con, boolean_T *id_con,
  boolean_T *i_val, ExtU_OnlineID_t *rtOnlineID_U);
static void RefreshDataRegister(ExtU_OnlineID_t *rtOnlineID_U, ExtY_OnlineID_t
  *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW);

/*
 * Function for Chart: '<Root>/OnlineID'
 * function InitParams
 * Steady State Detection
 */
static void InitParams(ExtU_OnlineID_t *rtOnlineID_U, ExtY_OnlineID_t
  *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW)
{
  int32_T i;
  real32_T tmp;
  real32_T tmp_0;

  /* MATLAB Function 'InitParams': '<S1>:241' */
  /* '<S1>:241:4' vd_sum=single(0); */
  rtOnlineID_DW->vd_sum = 0.0F;

  /* '<S1>:241:5' vq_sum=single(0); */
  rtOnlineID_DW->vq_sum = 0.0F;

  /* '<S1>:241:6' id_sum=single(0); */
  rtOnlineID_DW->id_sum = 0.0F;

  /* '<S1>:241:7' iq_sum=single(0); */
  rtOnlineID_DW->iq_sum = 0.0F;

  /* '<S1>:241:8' omega_sum=single(0); */
  rtOnlineID_DW->omega_sum = 0.0F;

  /* '<S1>:241:9' id_register=single(zeros(50,1)); */
  /* '<S1>:241:10' iq_register=single(zeros(50,1)); */
  /* '<S1>:241:11' vd_register=single(zeros(50,1)); */
  /* '<S1>:241:12' vq_register=single(zeros(50,1)); */
  memset(&rtOnlineID_DW->id_register[0], 0, 50U * sizeof(real32_T));
  memset(&rtOnlineID_DW->iq_register[0], 0, 50U * sizeof(real32_T));
  memset(&rtOnlineID_DW->vd_register[0], 0, 50U * sizeof(real32_T));
  memset(&rtOnlineID_DW->vq_register[0], 0, 50U * sizeof(real32_T));

  /* '<S1>:241:13' id_const=boolean(0); */
  rtOnlineID_DW->id_const = false;

  /* '<S1>:241:14' iq_const=boolean(0); */
  rtOnlineID_DW->iq_const = false;

  /* '<S1>:241:15' omega_const=boolean(0); */
  rtOnlineID_DW->omega_const = false;

  /* Calculation if linearParams will be identified */
  /* '<S1>:241:18' allow_meas=boolean(0); */
  rtOnlineID_DW->allow_meas = false;

  /* '<S1>:241:19' counter_time=uint32(0); */
  rtOnlineID_DW->counter_time = 0U;

  /* '<S1>:241:20' LinPara_ident_outside=boolean(1); */
  rtOnlineID_DW->LinPara_ident_outside = true;

  /* '<S1>:241:21' i_valid=boolean(0); */
  rtOnlineID_DW->i_valid = false;

  /* '<S1>:241:22' counter_ausserhalb=uint16(0); */
  rtOnlineID_DW->counter_ausserhalb = 0U;

  /* '<S1>:241:23' counter_innerhalb=uint16(0); */
  rtOnlineID_DW->counter_innerhalb = 0U;

  /* '<S1>:241:26' iq1counter=single(0); */
  rtOnlineID_DW->iq1counter = 0.0F;

  /* '<S1>:241:27' iq2counter=single(0); */
  rtOnlineID_DW->iq2counter = 0.0F;

  /* '<S1>:241:28' id1counter=single(0); */
  rtOnlineID_DW->id1counter = 0.0F;

  /* '<S1>:241:29' id2counter=single(0); */
  rtOnlineID_DW->id2counter = 0.0F;

  /* '<S1>:241:30' Vd1counter=single(0); */
  rtOnlineID_DW->Vd1counter = 0.0F;

  /* '<S1>:241:31' Vd2counter=single(0); */
  rtOnlineID_DW->Vd2counter = 0.0F;

  /* '<S1>:241:32' omega1counter=single(0); */
  rtOnlineID_DW->omega1counter = 0.0F;

  /* '<S1>:241:33' omega2counter=single(0); */
  rtOnlineID_DW->omega2counter = 0.0F;

  /* '<S1>:241:34' omega_register=single(zeros(5,1)); */
  for (i = 0; i < 5; i++) {
    rtOnlineID_DW->omega_register[i] = 0.0F;
  }

  /* Inport: '<Root>/GlobalConfig' */
  /* Psi Calculation */
  /* '<S1>:241:38' array_counter=uint16(1); */
  /* '<S1>:241:39' psi_d=single(0); */
  /* '<S1>:241:40' psi_q=single(0); */
  /* '<S1>:241:41' R_old=single(GlobalConfig.PMSM_config.R_ph_Ohm); */
  rtOnlineID_DW->R_old = rtOnlineID_U->GlobalConfig_out.PMSM_config.R_ph_Ohm;

  /* '<S1>:241:42' R_veryold=single(GlobalConfig.PMSM_config.R_ph_Ohm); */
  rtOnlineID_DW->R_veryold = rtOnlineID_U->GlobalConfig_out.PMSM_config.R_ph_Ohm;

  /* %% */
  /* '<S1>:241:44' R_old_outside=single(GlobalConfig.PMSM_config.R_ph_Ohm); */
  rtOnlineID_DW->R_old_outside =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.R_ph_Ohm;

  /* '<S1>:241:45' R_veryold_outside=single(GlobalConfig.PMSM_config.R_ph_Ohm); */
  /* '<S1>:241:46' Ld_veryold_outside=single(GlobalConfig.PMSM_config.Psi_PM_Vs); */
  /* '<S1>:241:47' Ld_old_outside=single(GlobalConfig.PMSM_config.Ld_Henry); */
  rtOnlineID_DW->Ld_old_outside =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry;

  /* '<S1>:241:48' Lq_veryold_outside=single(GlobalConfig.PMSM_config.Lq_Henry); */
  /* '<S1>:241:49' Lq_old_outside=single(GlobalConfig.PMSM_config.Lq_Henry); */
  rtOnlineID_DW->Lq_old_outside =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry;

  /* '<S1>:241:50' PsiPm_veryold_outside=single(GlobalConfig.PMSM_config.Psi_PM_Vs); */
  /* '<S1>:241:51' PsiPm_old_outside=single(GlobalConfig.PMSM_config.Psi_PM_Vs); */
  rtOnlineID_DW->PsiPm_old_outside =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs;

  /* %% */
  /* '<S1>:241:53' accel=single(0); */
  /* '<S1>:241:54' i_d_R_online=single(0); */
  rtOnlineID_DW->i_d_R_online = 0.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:55' UpdateFluxFlag=boolean(0); */
  /* '<S1>:241:56' psi_temp_const=single(0.0000001); */
  /* '<S1>:241:57' Wtemp_check=single(0); */
  /* '<S1>:241:58' PsiPm_old=single(GlobalConfig.PMSM_config.Psi_PM_Vs); */
  rtOnlineID_DW->PsiPm_old =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs;

  /* '<S1>:241:59' PsiPm_veryold=single(GlobalConfig.PMSM_config.Psi_PM_Vs); */
  rtOnlineID_DW->PsiPm_veryold =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs;

  /* '<S1>:241:60' Ld_old=single(GlobalConfig.PMSM_config.Ld_Henry); */
  rtOnlineID_DW->Ld_old = rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry;

  /* '<S1>:241:61' Ld_veryold=single(GlobalConfig.PMSM_config.Ld_Henry); */
  rtOnlineID_DW->Ld_veryold =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry;

  /* '<S1>:241:62' Lq_old=single(GlobalConfig.PMSM_config.Lq_Henry); */
  rtOnlineID_DW->Lq_old = rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry;

  /* '<S1>:241:63' Lq_veryold=single(GlobalConfig.PMSM_config.Lq_Henry); */
  rtOnlineID_DW->Lq_veryold =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* Outputs */
  /* '<S1>:241:66' OnlineID_output.id_out                  = single(0.0); */
  rtOnlineID_Y->OnlineID_output.id_out = 0.0F;

  /* '<S1>:241:67' OnlineID_output.Rph_out = single(GlobalConfig.PMSM_config.R_ph_Ohm); */
  rtOnlineID_Y->OnlineID_output.Rph_out =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.R_ph_Ohm;

  /* '<S1>:241:68' OnlineID_output.Wtemp = single(20.0); */
  rtOnlineID_Y->OnlineID_output.Wtemp = 20.0F;

  /* '<S1>:241:69' OnlineID_output.psi_array = single(zeros(6,100)); */
  memset(&rtOnlineID_Y->OnlineID_output.psi_array[0], 0, 600U * sizeof(real32_T));

  /* '<S1>:241:70' OnlineID_output.IdControlFlag= boolean(0); */
  rtOnlineID_Y->OnlineID_output.IdControlFlag = false;

  /* '<S1>:241:71' OnlineID_output.iq_mean_out = single(0.0); */
  rtOnlineID_Y->OnlineID_output.iq_mean_out = 0.0F;

  /* '<S1>:241:72' OnlineID_output.id_mean_out = single(0.0); */
  rtOnlineID_Y->OnlineID_output.id_mean_out = 0.0F;

  /* '<S1>:241:73' OnlineID_output.delta_psi = single(zeros(100,2)); */
  memset(&rtOnlineID_Y->OnlineID_output.delta_psi[0], 0, 200U * sizeof(real32_T));

  /* '<S1>:241:74' OnlineID_output.delta_psi(7,1)=0.07; */
  rtOnlineID_Y->OnlineID_output.delta_psi[6] = 0.07F;

  /* '<S1>:241:75' OnlineID_output.delta_psi(7,2)=1; */
  rtOnlineID_Y->OnlineID_output.delta_psi[106] = 1.0F;

  /* '<S1>:241:76' OnlineID_output.delta_psi(9,1)=0.09; */
  rtOnlineID_Y->OnlineID_output.delta_psi[8] = 0.09F;

  /* '<S1>:241:77' OnlineID_output.delta_psi(9,2)=1; */
  rtOnlineID_Y->OnlineID_output.delta_psi[108] = 1.0F;

  /* '<S1>:241:78' OnlineID_output.activeState =uint16(0); */
  rtOnlineID_Y->OnlineID_output.activeState = 0U;

  /* '<S1>:241:79' OnlineID_output.psi_pm_out = single(GlobalConfig.PMSM_config.Psi_PM_Vs); */
  rtOnlineID_Y->OnlineID_output.psi_pm_out =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs;

  /* '<S1>:241:80' OnlineID_output.Ld_out = single(GlobalConfig.PMSM_config.Ld_Henry); */
  rtOnlineID_Y->OnlineID_output.Ld_out =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry;

  /* '<S1>:241:81' OnlineID_output.Lq_out = single(GlobalConfig.PMSM_config.Lq_Henry); */
  rtOnlineID_Y->OnlineID_output.Lq_out =
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry;

  /* '<S1>:241:82' OnlineID_output.clean_array_flag = boolean(0); */
  rtOnlineID_Y->OnlineID_output.clean_array_flag = false;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:84' OnlineID_output.psi_array(1,array_counter)=single(0.70*GlobalConfig.ratCurrent); */
  tmp = 0.7F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[0] = tmp;

  /* '<S1>:241:85' OnlineID_output.psi_array(2,array_counter)=single(0.7*GlobalConfig.ratCurrent); */
  rtOnlineID_Y->OnlineID_output.psi_array[1] = tmp;

  /* '<S1>:241:86' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[2] = 50.0F;

  /* '<S1>:241:87' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[3] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:88' OnlineID_output.psi_array(5,array_counter)=single(1000*(0.7*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)); */
  rtOnlineID_Y->OnlineID_output.psi_array[4] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:89' OnlineID_output.psi_array(6,array_counter)=single(1000*(0.7*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)); */
  rtOnlineID_Y->OnlineID_output.psi_array[5] = tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:90' array_counter=array_counter+1; */
  /* '<S1>:241:91' OnlineID_output.psi_array(1,array_counter)=single(-0.75*GlobalConfig.ratCurrent); */
  tmp = -0.75F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[6] = tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:92' OnlineID_output.psi_array(2,array_counter)=single(0.75*GlobalConfig.ratCurrent); */
  tmp_0 = 0.75F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[7] = tmp_0;

  /* '<S1>:241:93' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[8] = 50.0F;

  /* '<S1>:241:94' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[9] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:95' OnlineID_output.psi_array(5,array_counter)=single(1000*(-0.75*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)); */
  rtOnlineID_Y->OnlineID_output.psi_array[10] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:96' OnlineID_output.psi_array(6,array_counter)=single(1000*(0.75*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)); */
  rtOnlineID_Y->OnlineID_output.psi_array[11] = tmp_0 *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:97' array_counter=array_counter+1; */
  /* '<S1>:241:98' OnlineID_output.psi_array(1,array_counter)=single(-0.65*GlobalConfig.ratCurrent); */
  tmp = -0.65F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[12] = tmp;

  /* '<S1>:241:99' OnlineID_output.psi_array(2,array_counter)=single(-0.65*GlobalConfig.ratCurrent); */
  rtOnlineID_Y->OnlineID_output.psi_array[13] = tmp;

  /* '<S1>:241:100' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[14] = 50.0F;

  /* '<S1>:241:101' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[15] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:102' OnlineID_output.psi_array(5,array_counter)=single(1000*(-0.65*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)); */
  rtOnlineID_Y->OnlineID_output.psi_array[16] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:103' OnlineID_output.psi_array(6,array_counter)=single(1000*(-0.65*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)); */
  rtOnlineID_Y->OnlineID_output.psi_array[17] = tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:104' array_counter=array_counter+1; */
  /* '<S1>:241:105' OnlineID_output.psi_array(1,array_counter)=single(0.6*GlobalConfig.ratCurrent); */
  tmp = 0.6F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[18] = tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:106' OnlineID_output.psi_array(2,array_counter)=single(-0.6*GlobalConfig.ratCurrent); */
  tmp_0 = -0.6F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[19] = tmp_0;

  /* '<S1>:241:107' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[20] = 50.0F;

  /* '<S1>:241:108' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[21] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:109' OnlineID_output.psi_array(5,array_counter)=single(1000*(0.6*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)); */
  rtOnlineID_Y->OnlineID_output.psi_array[22] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:110' OnlineID_output.psi_array(6,array_counter)=single(1000*(-0.6*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)); */
  rtOnlineID_Y->OnlineID_output.psi_array[23] = tmp_0 *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:111' array_counter=array_counter+1; */
  /*   */
  /* '<S1>:241:113' OnlineID_output.psi_array(1,array_counter)=single(0.30*GlobalConfig.ratCurrent); */
  tmp = 0.3F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[24] = tmp;

  /* '<S1>:241:114' OnlineID_output.psi_array(2,array_counter)=single(0.3*GlobalConfig.ratCurrent); */
  rtOnlineID_Y->OnlineID_output.psi_array[25] = tmp;

  /* '<S1>:241:115' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[26] = 50.0F;

  /* '<S1>:241:116' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[27] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:117' OnlineID_output.psi_array(5,array_counter)=single(0.3*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[28] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:118' OnlineID_output.psi_array(6,array_counter)=single(0.3*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[29] = tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:119' array_counter=array_counter+1; */
  /* '<S1>:241:120' OnlineID_output.psi_array(1,array_counter)=single(-0.35*GlobalConfig.ratCurrent); */
  tmp = -0.35F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[30] = tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:121' OnlineID_output.psi_array(2,array_counter)=single(0.35*GlobalConfig.ratCurrent); */
  tmp_0 = 0.35F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[31] = tmp_0;

  /* '<S1>:241:122' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[32] = 50.0F;

  /* '<S1>:241:123' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[33] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:124' OnlineID_output.psi_array(5,array_counter)=single(-0.35*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[34] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:125' OnlineID_output.psi_array(6,array_counter)=single(0.35*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[35] = tmp_0 *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:126' array_counter=array_counter+1; */
  /* '<S1>:241:127' OnlineID_output.psi_array(1,array_counter)=single(-0.25*GlobalConfig.ratCurrent); */
  tmp = -0.25F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[36] = tmp;

  /* '<S1>:241:128' OnlineID_output.psi_array(2,array_counter)=single(-0.25*GlobalConfig.ratCurrent); */
  rtOnlineID_Y->OnlineID_output.psi_array[37] = tmp;

  /* '<S1>:241:129' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[38] = 50.0F;

  /* '<S1>:241:130' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[39] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:131' OnlineID_output.psi_array(5,array_counter)=single(-0.25*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[40] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:132' OnlineID_output.psi_array(6,array_counter)=single(-0.25*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[41] = tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:133' array_counter=array_counter+1; */
  /* '<S1>:241:134' OnlineID_output.psi_array(1,array_counter)=single(0.2*GlobalConfig.ratCurrent); */
  tmp = 0.2F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[42] = tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:241:135' OnlineID_output.psi_array(2,array_counter)=single(-0.2*GlobalConfig.ratCurrent); */
  tmp_0 = -0.2F * rtOnlineID_U->GlobalConfig_out.ratCurrent;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  rtOnlineID_Y->OnlineID_output.psi_array[43] = tmp_0;

  /* '<S1>:241:136' OnlineID_output.psi_array(3,array_counter)=single(50); */
  rtOnlineID_Y->OnlineID_output.psi_array[44] = 50.0F;

  /* '<S1>:241:137' OnlineID_output.psi_array(4,array_counter)=OnlineIDConfig.Temp_ref; */
  rtOnlineID_Y->OnlineID_output.psi_array[45] =
    rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* '<S1>:241:138' OnlineID_output.psi_array(5,array_counter)=single(0.2*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Ld_Henry+GlobalConfig.PMSM_config.Psi_PM_Vs)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[46] = (tmp *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Ld_Henry +
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * 1000.0F;

  /* '<S1>:241:139' OnlineID_output.psi_array(6,array_counter)=single(-0.2*GlobalConfig.ratCurrent*GlobalConfig.PMSM_config.Lq_Henry)*1000; */
  rtOnlineID_Y->OnlineID_output.psi_array[47] = tmp_0 *
    rtOnlineID_U->GlobalConfig_out.PMSM_config.Lq_Henry * 1000.0F;

  /* '<S1>:241:140' array_counter=array_counter+1; */
}

/* Function for Chart: '<Root>/OnlineID' */
static void enter_atomic_RefreshDataRegiste(ExtY_OnlineID_t *rtOnlineID_Y,
  DW_OnlineID_t *rtOnlineID_DW)
{
  int32_T i;

  /* Outport: '<Root>/OnlineID_output' */
  /* Entry 'RefreshDataRegister': '<S1>:37' */
  /* '<S1>:37:3' OnlineID_output.activeState=uint16(501); */
  rtOnlineID_Y->OnlineID_output.activeState = 501U;

  /* '<S1>:37:4' counter=uint32(1); */
  rtOnlineID_DW->counter = 1U;

  /* '<S1>:37:5' omega_register=single(zeros(5,1)); */
  for (i = 0; i < 5; i++) {
    rtOnlineID_DW->omega_register[i] = 0.0F;
  }

  /* '<S1>:37:6' id_register=single(zeros(50,1)); */
  /* '<S1>:37:7' iq_register=single(zeros(50,1)); */
  /* '<S1>:37:8' vd_register=single(zeros(50,1)); */
  /* '<S1>:37:9' vq_register=single(zeros(50,1)); */
  memset(&rtOnlineID_DW->id_register[0], 0, 50U * sizeof(real32_T));
  memset(&rtOnlineID_DW->iq_register[0], 0, 50U * sizeof(real32_T));
  memset(&rtOnlineID_DW->vd_register[0], 0, 50U * sizeof(real32_T));
  memset(&rtOnlineID_DW->vq_register[0], 0, 50U * sizeof(real32_T));

  /* '<S1>:37:10' iq_const=boolean(0); */
  rtOnlineID_DW->iq_const = false;

  /* '<S1>:37:11' id_const=boolean(0); */
  rtOnlineID_DW->id_const = false;

  /* '<S1>:37:12' omega_const=boolean(0); */
  rtOnlineID_DW->omega_const = false;

  /* '<S1>:37:13' breakback=single(0); */
  rtOnlineID_DW->breakback = 0.0F;
}

/*
 * Function for Chart: '<Root>/OnlineID'
 * function identParams
 *  positive halfperiod
 */
static void identParams(ExtU_OnlineID_t *rtOnlineID_U, ExtY_OnlineID_t
  *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW)
{
  real32_T Ld_check;
  real32_T Ld_veryold_outside;
  real32_T Lq_check;
  real32_T R_check;
  real32_T psipm_check;
	boolean_T tmp;

  /* MATLAB Function 'identParams': '<S1>:101' */
	/* '<S1>:101:4' if(counter <= 12000) */
	if (rtOnlineID_DW->counter <= 12000U) {
    /* Inport: '<Root>/OnlineIDConfig' */
    /* '<S1>:101:5' i_d_R_online = single(+OnlineIDConfig.identRAmp); */
    rtOnlineID_DW->i_d_R_online = rtOnlineID_U->OnlineIDConfig.identRAmp;

		/* '<S1>:101:6' if(counter >= 9999 && counter < 11999) */
		if ((rtOnlineID_DW->counter >= 9999U) && (rtOnlineID_DW->counter < 11999U)) {
			/* Inport: '<Root>/ActualValues' */
			/* '<S1>:101:7' Vd1counter = Vd1counter+ActualValues.v_dq.d; */
			rtOnlineID_DW->Vd1counter += rtOnlineID_U->ActualValues.v_dq.d;

			/* '<S1>:101:8' Vq1counter = Vq1counter+ActualValues.v_dq.q; */
			rtOnlineID_DW->Vq1counter += rtOnlineID_U->ActualValues.v_dq.q;

			/* '<S1>:101:9' id1counter = id1counter+ActualValues.i_dq.d; */
			rtOnlineID_DW->id1counter += rtOnlineID_U->ActualValues.i_dq.d;

			/* '<S1>:101:10' iq1counter = iq1counter+ActualValues.i_dq.q; */
			rtOnlineID_DW->iq1counter += rtOnlineID_U->ActualValues.i_dq.q;

			/* '<S1>:101:11' omega1counter = omega1counter+ActualValues.omega_el; */
			rtOnlineID_DW->omega1counter += rtOnlineID_U->ActualValues.omega_el;
    }
  }

  /*  negative halfperiod        */
	/* '<S1>:101:16' if(counter > 12000 && counter < 24000) */
	if ((rtOnlineID_DW->counter > 12000U) && (rtOnlineID_DW->counter < 24000U)) {
		/* Inport: '<Root>/OnlineIDConfig' */
		/* '<S1>:101:17' i_d_R_online = single(-OnlineIDConfig.identRAmp); */
		rtOnlineID_DW->i_d_R_online = -rtOnlineID_U->OnlineIDConfig.identRAmp;

		/* '<S1>:101:18' if(counter >= 21999 && counter < 23999) */
		if ((rtOnlineID_DW->counter >= 21999U) && (rtOnlineID_DW->counter < 23999U)) {
			/* Inport: '<Root>/ActualValues' */
			/* '<S1>:101:19' Vd2counter = Vd2counter+ActualValues.v_dq.d; */
			rtOnlineID_DW->Vd2counter += rtOnlineID_U->ActualValues.v_dq.d;

			/* '<S1>:101:20' Vq2counter = Vq2counter+ActualValues.v_dq.q; */
			rtOnlineID_DW->Vq2counter += rtOnlineID_U->ActualValues.v_dq.q;

			/* '<S1>:101:21' id2counter = id2counter+ActualValues.i_dq.d; */
			rtOnlineID_DW->id2counter += rtOnlineID_U->ActualValues.i_dq.d;

			/* '<S1>:101:22' iq2counter = iq2counter+ActualValues.i_dq.q; */
			rtOnlineID_DW->iq2counter += rtOnlineID_U->ActualValues.i_dq.q;

			/* '<S1>:101:23' omega2counter= omega2counter+ActualValues.omega_el; */
			rtOnlineID_DW->omega2counter += rtOnlineID_U->ActualValues.omega_el;
    }
  }

  /*     Averaging    halfperiods */
	/* '<S1>:101:28' if(counter == 24000) */
	if (rtOnlineID_DW->counter == 24000U) {
    /* Inport: '<Root>/GlobalConfig' */
    /* '<S1>:101:29' Vq1counter=Vq1counter/(0.1/GlobalConfig.sampleTimeISR); */
    R_check = 0.1F / rtOnlineID_U->GlobalConfig_out.sampleTimeISR;
    rtOnlineID_DW->Vq1counter /= R_check;

    /* '<S1>:101:30' Vq2counter=Vq2counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->Vq2counter /= R_check;

    /* '<S1>:101:31' Vd1counter=Vd1counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->Vd1counter /= R_check;

    /* '<S1>:101:32' Vd2counter=Vd2counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->Vd2counter /= R_check;

    /* '<S1>:101:33' id1counter=id1counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->id1counter /= R_check;

    /* '<S1>:101:34' id2counter=id2counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->id2counter /= R_check;

    /* '<S1>:101:35' iq1counter=iq1counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->iq1counter /= R_check;

    /* '<S1>:101:36' iq2counter=iq2counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->iq2counter /= R_check;

    /* '<S1>:101:37' omega1counter=omega1counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->omega1counter /= R_check;

    /* '<S1>:101:38' omega2counter=omega2counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtOnlineID_DW->omega2counter /= R_check;

    /* Calculation of Parameters             */
    /*      Calculate R               */
    /* '<S1>:101:43' R_check= single(  ( Vd2counter/ (iq2counter*omega2counter) -  Vd1counter/(iq1counter*omega1counter)  )  /... */
    /* '<S1>:101:44'                         (  id2counter/(iq2counter* omega2counter) -   id1counter/ (iq1counter*omega1counter)       )       ); */
    Lq_check = rtOnlineID_DW->iq2counter * rtOnlineID_DW->omega2counter;
    psipm_check = rtOnlineID_DW->iq1counter * rtOnlineID_DW->omega1counter;
    R_check = (rtOnlineID_DW->Vd2counter / Lq_check - rtOnlineID_DW->Vd1counter /
               psipm_check) / (rtOnlineID_DW->id2counter / Lq_check -
      rtOnlineID_DW->id1counter / psipm_check);

    /*      Simplification for small reluctance torque: iq1 ~ iq2 ~ (iq1+iq2)/2 ; omega1~omega2~(omega1+omega2)/2 */
    /*      Calculate Lq  */
    /* '<S1>:101:51' Lq_check=single(Vd1counter*id2counter-Vd2counter*id1counter)/(omega2counter*iq2counter*id1counter-omega1counter*iq1counter*id2counter); */
    Lq_check = (rtOnlineID_DW->Vd1counter * rtOnlineID_DW->id2counter -
                rtOnlineID_DW->Vd2counter * rtOnlineID_DW->id1counter) /
      (Lq_check * rtOnlineID_DW->id1counter - psipm_check *
       rtOnlineID_DW->id2counter);

    /*      Calculate permanent flux  */
    /* '<S1>:101:54' psipm_check=single((Vq1counter-R_check*iq1counter)*id2counter)/(omega1counter*(id2counter-id1counter))-... */
    /* '<S1>:101:55'                             ((Vq2counter-R_check*iq2counter)*id1counter)/(omega2counter*(id2counter-id1counter)); */
    psipm_check = rtOnlineID_DW->id2counter - rtOnlineID_DW->id1counter;
    psipm_check = (rtOnlineID_DW->Vq1counter - R_check *
                   rtOnlineID_DW->iq1counter) * rtOnlineID_DW->id2counter /
      (psipm_check * rtOnlineID_DW->omega1counter) - (rtOnlineID_DW->Vq2counter
      - R_check * rtOnlineID_DW->iq2counter) * rtOnlineID_DW->id1counter /
      (psipm_check * rtOnlineID_DW->omega2counter);

    /*      Calculate Ld  */
    /* '<S1>:101:58' Ld_check=single((Vq2counter-Vq1counter)-(iq2counter-iq1counter)*R_check - psipm_check*(omega2counter - omega1counter))/... */
    /* '<S1>:101:59'                          (id2counter*omega2counter-id1counter*omega1counter); */
    Ld_check = (((rtOnlineID_DW->Vq2counter - rtOnlineID_DW->Vq1counter) -
                 (rtOnlineID_DW->iq2counter - rtOnlineID_DW->iq1counter) *
                 R_check) - (rtOnlineID_DW->omega2counter -
      rtOnlineID_DW->omega1counter) * psipm_check) / (rtOnlineID_DW->id2counter *
      rtOnlineID_DW->omega2counter - rtOnlineID_DW->id1counter *
      rtOnlineID_DW->omega1counter);

    /*      Plausibilty Checks           */
    /* '<S1>:101:63' if(Ld_check>0&&Ld_check<1) */
    if ((Ld_check > 0.0F) && (Ld_check < 1.0F)) {
      /* Inport: '<Root>/OnlineIDConfig' */
      /* '<S1>:101:64' if(OnlineIDConfig.AverageTransParams==1) */
			if (rtOnlineID_U->OnlineIDConfig.AverageTransParams) {
        /* '<S1>:101:65' if(LinPara_ident_outside==1 && counter_ausserhalb==1) */
        if (rtOnlineID_DW->LinPara_ident_outside &&
            (rtOnlineID_DW->counter_ausserhalb == 1)) {
          /* Average over 3 iterations */
          /* '<S1>:101:67' Ld_veryold_outside=Ld_old_outside; */
          Ld_veryold_outside = rtOnlineID_DW->Ld_old_outside;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:68' Ld_old_outside=OnlineID_output.Ld_out; */
          rtOnlineID_DW->Ld_old_outside = rtOnlineID_Y->OnlineID_output.Ld_out;

          /* '<S1>:101:69' OnlineID_output.Ld_out=(Ld_check+Ld_old_outside+Ld_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Ld_out = ((Ld_check +
            rtOnlineID_DW->Ld_old_outside) + Ld_veryold_outside) / 3.0F;
        } else if (rtOnlineID_DW->LinPara_ident_outside &&
                   (rtOnlineID_DW->counter_ausserhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:70' elseif(LinPara_ident_outside==1 && counter_ausserhalb==0) */
          /* '<S1>:101:71' Ld_veryold_outside=Ld_old; */
          /* '<S1>:101:72' Ld_old_outside=OnlineID_output.Ld_out; */
          rtOnlineID_DW->Ld_old_outside = rtOnlineID_Y->OnlineID_output.Ld_out;

          /* '<S1>:101:73' OnlineID_output.Ld_out=(Ld_check+Ld_old_outside+Ld_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Ld_out = ((Ld_check +
            rtOnlineID_DW->Ld_old_outside) + rtOnlineID_DW->Ld_old) / 3.0F;
        }

        /* '<S1>:101:75' if(LinPara_ident_outside==0 && counter_innerhalb==1) */
				tmp = !rtOnlineID_DW->LinPara_ident_outside;
				if (tmp && (rtOnlineID_DW->counter_innerhalb == 1)) {
          /* '<S1>:101:76' Ld_veryold=Ld_old; */
          rtOnlineID_DW->Ld_veryold = rtOnlineID_DW->Ld_old;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:77' Ld_old=OnlineID_output.Ld_out; */
          rtOnlineID_DW->Ld_old = rtOnlineID_Y->OnlineID_output.Ld_out;

          /* '<S1>:101:78' OnlineID_output.Ld_out=(Ld_check+Ld_old+Ld_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Ld_out = ((Ld_check +
            rtOnlineID_DW->Ld_old) + rtOnlineID_DW->Ld_veryold) / 3.0F;
				} else if (tmp && (rtOnlineID_DW->counter_innerhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:79' elseif(LinPara_ident_outside==0 && counter_innerhalb==0) */
          /* '<S1>:101:80' OnlineID_output.Ld_out=(Ld_check+Ld_old+Ld_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Ld_out = ((Ld_check +
            rtOnlineID_DW->Ld_old) + rtOnlineID_DW->Ld_veryold) / 3.0F;
        }
      } else {
        /* Outport: '<Root>/OnlineID_output' */
        /* '<S1>:101:82' else */
        /* '<S1>:101:83' OnlineID_output.Ld_out=Ld_check; */
        rtOnlineID_Y->OnlineID_output.Ld_out = Ld_check;
      }
    }

    /* '<S1>:101:87' if(Lq_check>0&&Lq_check<1) */
    if ((Lq_check > 0.0F) && (Lq_check < 1.0F)) {
      /* Inport: '<Root>/OnlineIDConfig' */
      /* '<S1>:101:88' if(OnlineIDConfig.AverageTransParams==1) */
			if (rtOnlineID_U->OnlineIDConfig.AverageTransParams) {
        /* '<S1>:101:89' if(LinPara_ident_outside==1 && counter_ausserhalb==1) */
        if (rtOnlineID_DW->LinPara_ident_outside &&
            (rtOnlineID_DW->counter_ausserhalb == 1)) {
          /* Average over 3 iterations */
          /* '<S1>:101:91' Lq_veryold_outside=Lq_old_outside; */
          Ld_check = rtOnlineID_DW->Lq_old_outside;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:92' Lq_old_outside=OnlineID_output.Lq_out; */
          rtOnlineID_DW->Lq_old_outside = rtOnlineID_Y->OnlineID_output.Lq_out;

          /* '<S1>:101:93' OnlineID_output.Lq_out=(Lq_check+Lq_old_outside+Lq_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Lq_out = ((Lq_check +
            rtOnlineID_DW->Lq_old_outside) + Ld_check) / 3.0F;
        } else if (rtOnlineID_DW->LinPara_ident_outside &&
                   (rtOnlineID_DW->counter_ausserhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:94' elseif(LinPara_ident_outside==1 && counter_ausserhalb==0) */
          /* '<S1>:101:95' Lq_veryold_outside=Lq_old; */
          /* '<S1>:101:96' Lq_old_outside=OnlineID_output.Lq_out; */
          rtOnlineID_DW->Lq_old_outside = rtOnlineID_Y->OnlineID_output.Lq_out;

          /* '<S1>:101:97' OnlineID_output.Lq_out=(Lq_check+Lq_old_outside+Lq_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Lq_out = ((Lq_check +
            rtOnlineID_DW->Lq_old_outside) + rtOnlineID_DW->Lq_old) / 3.0F;
        }

        /* '<S1>:101:99' if(LinPara_ident_outside==0 && counter_innerhalb==1) */
				tmp = !rtOnlineID_DW->LinPara_ident_outside;
				if (tmp && (rtOnlineID_DW->counter_innerhalb == 1)) {
          /* '<S1>:101:100' Lq_veryold=Lq_old; */
          rtOnlineID_DW->Lq_veryold = rtOnlineID_DW->Lq_old;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:101' Lq_old=OnlineID_output.Lq_out; */
          rtOnlineID_DW->Lq_old = rtOnlineID_Y->OnlineID_output.Lq_out;

          /* '<S1>:101:102' OnlineID_output.Lq_out=(Lq_check+Lq_old+Lq_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Lq_out = ((Lq_check +
            rtOnlineID_DW->Lq_old) + rtOnlineID_DW->Lq_veryold) / 3.0F;
				} else if (tmp && (rtOnlineID_DW->counter_innerhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:103' elseif(LinPara_ident_outside==0 && counter_innerhalb==0) */
          /* '<S1>:101:104' OnlineID_output.Lq_out=(Lq_check+Lq_old+Lq_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Lq_out = ((Lq_check +
            rtOnlineID_DW->Lq_old) + rtOnlineID_DW->Lq_veryold) / 3.0F;
        }
      } else {
        /* Outport: '<Root>/OnlineID_output' */
        /* '<S1>:101:106' else */
        /* '<S1>:101:107' OnlineID_output.Lq_out=Lq_check; */
        rtOnlineID_Y->OnlineID_output.Lq_out = Lq_check;
      }
    }

    /* '<S1>:101:111' if(psipm_check>0&&psipm_check<1) */
    if ((psipm_check > 0.0F) && (psipm_check < 1.0F)) {
      /* Inport: '<Root>/OnlineIDConfig' */
      /* '<S1>:101:112' if(OnlineIDConfig.AverageTransParams==1) */
			if (rtOnlineID_U->OnlineIDConfig.AverageTransParams) {
        /* '<S1>:101:113' if(LinPara_ident_outside==1 && counter_ausserhalb==1) */
        if (rtOnlineID_DW->LinPara_ident_outside &&
            (rtOnlineID_DW->counter_ausserhalb == 1)) {
          /* Average over 3 iterations */
          /* '<S1>:101:115' PsiPm_veryold_outside=PsiPm_old_outside; */
          Lq_check = rtOnlineID_DW->PsiPm_old_outside;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:116' PsiPm_old_outside=OnlineID_output.psi_pm_out; */
          rtOnlineID_DW->PsiPm_old_outside =
            rtOnlineID_Y->OnlineID_output.psi_pm_out;

          /* '<S1>:101:117' OnlineID_output.psi_pm_out=(psipm_check+PsiPm_old_outside+PsiPm_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.psi_pm_out = ((psipm_check +
            rtOnlineID_DW->PsiPm_old_outside) + Lq_check) / 3.0F;
        } else if (rtOnlineID_DW->LinPara_ident_outside &&
                   (rtOnlineID_DW->counter_ausserhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:118' elseif(LinPara_ident_outside==1 && counter_ausserhalb==0) */
          /* '<S1>:101:119' PsiPm_veryold_outside=PsiPm_old; */
          /* '<S1>:101:120' PsiPm_old_outside=OnlineID_output.psi_pm_out; */
          rtOnlineID_DW->PsiPm_old_outside =
            rtOnlineID_Y->OnlineID_output.psi_pm_out;

          /* '<S1>:101:121' OnlineID_output.psi_pm_out=(psipm_check+PsiPm_old_outside+PsiPm_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.psi_pm_out = ((psipm_check +
            rtOnlineID_DW->PsiPm_old_outside) + rtOnlineID_DW->PsiPm_old) / 3.0F;
        }

        /* '<S1>:101:123' if(LinPara_ident_outside==0 && counter_innerhalb==1) */
				tmp = !rtOnlineID_DW->LinPara_ident_outside;
				if (tmp && (rtOnlineID_DW->counter_innerhalb == 1)) {
          /* Average over 3 iterations */
          /* '<S1>:101:125' PsiPm_veryold=PsiPm_old; */
          rtOnlineID_DW->PsiPm_veryold = rtOnlineID_DW->PsiPm_old;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:126' PsiPm_old=OnlineID_output.psi_pm_out; */
          rtOnlineID_DW->PsiPm_old = rtOnlineID_Y->OnlineID_output.psi_pm_out;

          /* '<S1>:101:127' OnlineID_output.psi_pm_out=(psipm_check+PsiPm_old+PsiPm_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.psi_pm_out = ((psipm_check +
            rtOnlineID_DW->PsiPm_old) + rtOnlineID_DW->PsiPm_veryold) / 3.0F;
				} else if (tmp && (rtOnlineID_DW->counter_innerhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:128' elseif(LinPara_ident_outside==0 && counter_innerhalb==0) */
          /* '<S1>:101:129' OnlineID_output.psi_pm_out=(psipm_check+PsiPm_old+PsiPm_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.psi_pm_out = ((psipm_check +
            rtOnlineID_DW->PsiPm_old) + rtOnlineID_DW->PsiPm_veryold) / 3.0F;
        }
      } else {
        /* Outport: '<Root>/OnlineID_output' */
        /* '<S1>:101:131' else */
        /* '<S1>:101:132' OnlineID_output.psi_pm_out=psipm_check; */
        rtOnlineID_Y->OnlineID_output.psi_pm_out = psipm_check;
      }
    }

    /* '<S1>:101:136' if(R_check>0&&R_check<1000) */
    if ((R_check > 0.0F) && (R_check < 1000.0F)) {
      /* Inport: '<Root>/OnlineIDConfig' */
      /* '<S1>:101:137' if(OnlineIDConfig.AverageTransParams==1) */
			if (rtOnlineID_U->OnlineIDConfig.AverageTransParams) {
        /* '<S1>:101:138' if(LinPara_ident_outside==1 && counter_ausserhalb==1) */
        if (rtOnlineID_DW->LinPara_ident_outside &&
            (rtOnlineID_DW->counter_ausserhalb == 1)) {
          /* Average over 3 iterations */
          /* '<S1>:101:140' R_veryold_outside=R_old_outside; */
          psipm_check = rtOnlineID_DW->R_old_outside;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:141' R_old_outside=OnlineID_output.Rph_out; */
          rtOnlineID_DW->R_old_outside = rtOnlineID_Y->OnlineID_output.Rph_out;

          /* '<S1>:101:142' OnlineID_output.Rph_out=(R_check+R_old_outside+R_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Rph_out = ((R_check +
            rtOnlineID_DW->R_old_outside) + psipm_check) / 3.0F;
        } else if (rtOnlineID_DW->LinPara_ident_outside &&
                   (rtOnlineID_DW->counter_ausserhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:143' elseif(LinPara_ident_outside==1 && counter_ausserhalb==0) */
          /* '<S1>:101:144' R_veryold_outside=R_old; */
          /* '<S1>:101:145' R_old_outside=OnlineID_output.Rph_out; */
          rtOnlineID_DW->R_old_outside = rtOnlineID_Y->OnlineID_output.Rph_out;

          /* '<S1>:101:146' OnlineID_output.Rph_out=(R_check+R_old_outside+R_veryold_outside)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Rph_out = ((R_check +
            rtOnlineID_DW->R_old_outside) + rtOnlineID_DW->R_old) / 3.0F;
        }

        /* '<S1>:101:148' if(LinPara_ident_outside==0 && counter_innerhalb==1) */
				tmp = !rtOnlineID_DW->LinPara_ident_outside;
				if (tmp && (rtOnlineID_DW->counter_innerhalb == 1)) {
          /* Average over 3 iterations */
          /* '<S1>:101:150' R_veryold=R_old; */
          rtOnlineID_DW->R_veryold = rtOnlineID_DW->R_old;

          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:151' R_old=OnlineID_output.Rph_out; */
          rtOnlineID_DW->R_old = rtOnlineID_Y->OnlineID_output.Rph_out;

          /* '<S1>:101:152' OnlineID_output.Rph_out=(R_check+R_old+R_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Rph_out = ((R_check +
            rtOnlineID_DW->R_old) + rtOnlineID_DW->R_veryold) / 3.0F;
				} else if (tmp && (rtOnlineID_DW->counter_innerhalb == 0)) {
          /* Outport: '<Root>/OnlineID_output' */
          /* '<S1>:101:153' elseif(LinPara_ident_outside==0 && counter_innerhalb==0) */
          /* '<S1>:101:154' OnlineID_output.Rph_out=(R_check+R_old+R_veryold)/single(3.0); */
          rtOnlineID_Y->OnlineID_output.Rph_out = ((R_check +
            rtOnlineID_DW->R_old) + rtOnlineID_DW->R_veryold) / 3.0F;
        }
      } else {
        /* Outport: '<Root>/OnlineID_output' */
        /* '<S1>:101:156' else */
        /* '<S1>:101:157' OnlineID_output.Rph_out=R_check; */
        rtOnlineID_Y->OnlineID_output.Rph_out = R_check;
      }
    }

    /* '<S1>:101:161' if(LinPara_ident_outside==0) */
    if (!rtOnlineID_DW->LinPara_ident_outside) {
      /* Resets the counter for outside_identification and sets the counter for inside_identification */
      /* '<S1>:101:162' counter_ausserhalb=uint16(0); */
      rtOnlineID_DW->counter_ausserhalb = 0U;

      /* '<S1>:101:163' counter_innerhalb=uint16(1); */
      rtOnlineID_DW->counter_innerhalb = 1U;
    } else {
      /* '<S1>:101:164' elseif(LinPara_ident_outside==1) */
      /* Resets the counter for inside_identification and sets the counter for outside_identification */
      /* '<S1>:101:165' counter_ausserhalb=uint16(1); */
      rtOnlineID_DW->counter_ausserhalb = 1U;

      /* '<S1>:101:166' counter_innerhalb=uint16(0); */
      rtOnlineID_DW->counter_innerhalb = 0U;
    }

    /*    Reset d-current */
    /* '<S1>:101:169' i_d_R_online = single(0); */
    rtOnlineID_DW->i_d_R_online = 0.0F;
  }
}

/*
 * Function for Chart: '<Root>/OnlineID'
 * function RefreshDataRegister
 */
static void RefreshDataRegister_i1(DW_OnlineID_t *rtOnlineID_DW)
{
  uint16_T k;

  /* MATLAB Function 'RefreshDataRegister': '<S1>:383' */
	/* '<S1>:383:3' if(mod(counter,400)==0) */
	if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 400U * 400U == 0U) {
    /* '<S1>:383:4' m=length(omega_register_neu); */
    /* '<S1>:383:5' for k= uint16(0):uint16(m-2) */
    /* '<S1>:383:6' omega_register_neu(m-k)=omega_register_neu(m-(k+1)); */
    rtOnlineID_DW->omega_register_neu[4] = rtOnlineID_DW->omega_register_neu[3];

    /* '<S1>:383:6' omega_register_neu(m-k)=omega_register_neu(m-(k+1)); */
    rtOnlineID_DW->omega_register_neu[3] = rtOnlineID_DW->omega_register_neu[2];

    /* '<S1>:383:6' omega_register_neu(m-k)=omega_register_neu(m-(k+1)); */
    rtOnlineID_DW->omega_register_neu[2] = rtOnlineID_DW->omega_register_neu[1];

    /* '<S1>:383:6' omega_register_neu(m-k)=omega_register_neu(m-(k+1)); */
    rtOnlineID_DW->omega_register_neu[1] = rtOnlineID_DW->omega_register_neu[0];
  }

  /* '<S1>:383:9' m=length(iq_register_neu); */
  /* '<S1>:383:10' for k= uint16(0):uint16(m-2) */
  /* '<S1>:383:14' m=length(id_register_neu); */
  /* '<S1>:383:15' for k= uint16(0):uint16(m-2) */
  for (k = 0; k < 9; k++) {
    /* '<S1>:383:11' iq_register_neu(m-k)=iq_register_neu(m-(k+1)); */
    rtOnlineID_DW->iq_register_neu[9 - k] = rtOnlineID_DW->iq_register_neu[8 - k];

    /* '<S1>:383:16' id_register_neu(m-k)=id_register_neu(m-(k+1)); */
    rtOnlineID_DW->id_register_neu[9 - k] = rtOnlineID_DW->id_register_neu[8 - k];
  }
}

/*
 * Function for Chart: '<Root>/OnlineID'
 * function stop_identParams  = Break(iq_reg_alt,id_reg_alt,om_reg_alt,iq_reg_neu,id_reg_neu,om_reg_neu)
 * calculates the mean of the registers of the new and old values
 */
static boolean_T Break(const real32_T iq_reg_alt[50], const real32_T id_reg_alt
  [50], const real32_T om_reg_alt[5], const real32_T iq_reg_neu[10], const
  real32_T id_reg_neu[10], const real32_T om_reg_neu[5], ExtU_OnlineID_t
  *rtOnlineID_U)
{
  int32_T k;
  real32_T mean_id_alt;
  real32_T mean_id_neu;
  real32_T mean_iq_alt;
  real32_T mean_iq_neu;
  real32_T mean_om_alt;
  real32_T mean_om_neu;
  real32_T tmp;
  boolean_T id_break;
  boolean_T iq_break;
  boolean_T om_break;
  boolean_T stop_identParams;

  /* MATLAB Function 'Break': '<S1>:389' */
  /* '<S1>:389:4' mean_om_alt=mean(om_reg_alt); */
  mean_om_alt = ((((om_reg_alt[0] + om_reg_alt[1]) + om_reg_alt[2]) +
                  om_reg_alt[3]) + om_reg_alt[4]) / 5.0F;

  /* Mittelwert */
  /* '<S1>:389:5' mean_iq_alt=mean(iq_reg_alt); */
  mean_iq_alt = iq_reg_alt[0];

  /* '<S1>:389:6' mean_id_alt=mean(id_reg_alt); */
  mean_id_alt = id_reg_alt[0];
  for (k = 0; k < 49; k++) {
    mean_iq_alt += iq_reg_alt[k + 1];
    mean_id_alt += id_reg_alt[k + 1];
  }

  mean_iq_alt /= 50.0F;
  mean_id_alt /= 50.0F;

  /* '<S1>:389:7' mean_om_neu=mean(om_reg_neu); */
  mean_om_neu = ((((om_reg_neu[0] + om_reg_neu[1]) + om_reg_neu[2]) +
                  om_reg_neu[3]) + om_reg_neu[4]) / 5.0F;

  /* '<S1>:389:8' mean_iq_neu=mean(iq_reg_neu); */
  mean_iq_neu = iq_reg_neu[0];

  /* '<S1>:389:9' mean_id_neu=mean(id_reg_neu); */
  mean_id_neu = id_reg_neu[0];
  for (k = 0; k < 9; k++) {
    mean_iq_neu += iq_reg_neu[k + 1];
    mean_id_neu += id_reg_neu[k + 1];
  }

  mean_iq_neu /= 10.0F;
  mean_id_neu /= 10.0F;

  /* Inport: '<Root>/OnlineIDConfig' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* compares if the new mean iq value is inside the tolerance range of the old */
  /* one */
  /* '<S1>:389:12' if((mean_iq_alt+(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))>=mean_iq_neu && ... */
  /* '<S1>:389:13'         (mean_iq_alt-(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))<= mean_iq_neu) */
  tmp = rtOnlineID_U->OnlineIDConfig.dev_curr *
    rtOnlineID_U->GlobalConfig_out.ratCurrent;
  if ((tmp + mean_iq_alt >= mean_iq_neu) && (mean_iq_alt - tmp <= mean_iq_neu))
  {
    /* '<S1>:389:14' iq_break=boolean(0); */
    iq_break = false;
  } else {
    /* '<S1>:389:15' else */
    /* '<S1>:389:16' iq_break=boolean(1); */
    iq_break = true;
  }

  /* Inport: '<Root>/OnlineIDConfig' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* compares if the new mean iq value is inside the tolerance range of the old */
  /* one */
  /* '<S1>:389:20' if((mean_om_alt+((OnlineIDConfig.dev_omega*GlobalConfig.ratSpeed*2*pi)/60))>=mean_om_neu&&... */
  /* '<S1>:389:21'         (mean_om_alt-((OnlineIDConfig.dev_omega*GlobalConfig.ratSpeed*2*pi)/60))<=mean_om_neu) */
  mean_iq_alt = rtOnlineID_U->OnlineIDConfig.dev_omega *
    rtOnlineID_U->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F / 60.0F;
  if (mean_iq_alt + mean_om_alt >= mean_om_neu) {
    if (mean_om_alt - mean_iq_alt <= mean_om_neu) {
      /* '<S1>:389:22' om_break=boolean(0); */
      om_break = false;
    } else {
      /* '<S1>:389:23' else */
      /* '<S1>:389:24' om_break=boolean(1); */
      om_break = true;
    }
  } else {
    /* '<S1>:389:23' else */
    /* '<S1>:389:24' om_break=boolean(1); */
    om_break = true;
  }

  /* Inport: '<Root>/OnlineIDConfig' */
  /* compares if the new mean id value is inside the tolerance range of the old */
  /* one. Though here the tolerance is bigger than the peak of the id-Step  */
  /* '<S1>:389:29' if((OnlineIDConfig.identRAmp+mean_id_alt+(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))>=mean_id_neu&&... */
  /* '<S1>:389:30'         (-OnlineIDConfig.identRAmp+mean_id_alt-(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))<=mean_id_neu) */
  if (((rtOnlineID_U->OnlineIDConfig.identRAmp + mean_id_alt) + tmp >=
       mean_id_neu) && ((-rtOnlineID_U->OnlineIDConfig.identRAmp + mean_id_alt)
                        - tmp <= mean_id_neu)) {
    /* '<S1>:389:31' id_break=boolean(0); */
    id_break = false;
  } else {
    /* '<S1>:389:32' else */
    /* '<S1>:389:33' id_break=boolean(1); */
    id_break = true;
  }

  /* if either the iq or omega increased too much, it will set the value to 1 */
  /* '<S1>:389:37' if( om_break == 1 || iq_break == 1 || id_break == 1) */
  if (om_break || iq_break || id_break) {
    /* '<S1>:389:38' stop_identParams = boolean(1); */
    stop_identParams = true;
  } else {
    /* '<S1>:389:39' else */
    /* '<S1>:389:40' stop_identParams = boolean(0); */
    stop_identParams = false;
  }

  return stop_identParams;
}

/* Function for Chart: '<Root>/OnlineID' */
static void enter_atomic_PsiCalcState(ExtU_OnlineID_t *rtOnlineID_U,
  ExtY_OnlineID_t *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW)
{
  int32_T i;
  real32_T Wtemp_check;
  real32_T b_x;
  real32_T d_x;
  real32_T e_x;
  real32_T e_x_tmp;
  real32_T g_x;

  /* Outport: '<Root>/OnlineID_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   */
  /* Entry 'PsiCalcState': '<S1>:83' */
  /* '<S1>:83:4' OnlineID_output.activeState=uint16(503); */
  rtOnlineID_Y->OnlineID_output.activeState = 503U;

  /* '<S1>:83:5' Wtemp_check=((single(OnlineID_output.Rph_out)/single(GlobalConfig.PMSM_config.R_ph_Ohm))-single(1))*.... */
  /* '<S1>:83:6'     single(254.453)+single(OnlineIDConfig.Temp_ref); */
  Wtemp_check = (rtOnlineID_Y->OnlineID_output.Rph_out /
                 rtOnlineID_U->GlobalConfig_out.PMSM_config.R_ph_Ohm - 1.0F) *
    254.453F + rtOnlineID_U->OnlineIDConfig.Temp_ref;

  /* . */
  /* '<S1>:83:7' if(Wtemp_check<200&&Wtemp_check>(-100)) */
  if ((Wtemp_check < 200.0F) && (Wtemp_check > -100.0F)) {
    /* Outport: '<Root>/OnlineID_output' */
    /* '<S1>:83:8' OnlineID_output.Wtemp =Wtemp_check; */
    rtOnlineID_Y->OnlineID_output.Wtemp = Wtemp_check;
  }

  /* Inport: '<Root>/array_cleaned_flag' */
  /* '<S1>:83:10' if(array_cleaned_flag==1) */
  if (rtOnlineID_U->array_cleaned_flag) {
    /* Outport: '<Root>/OnlineID_output' incorporates:
     *  Inport: '<Root>/cleaned_psi_array'
     */
    /* '<S1>:83:11' OnlineID_output.psi_array=cleaned_psi_array; */
    memcpy(&rtOnlineID_Y->OnlineID_output.psi_array[0],
           &rtOnlineID_U->psi_array_out[0], 600U * sizeof(real32_T));
  }

  /* End of Inport: '<Root>/array_cleaned_flag' */
  /* '<S1>:83:13' array_counter=uint16(99); */
  /* '<S1>:83:14' psi_d=1000*(mean(vq_register)-OnlineID_output.Rph_out*mean(iq_register))/(mean(omega_register)*GlobalConfig.PMSM_config.polePairs); */
  Wtemp_check = rtOnlineID_DW->vq_register[0];
  b_x = rtOnlineID_DW->iq_register[0];

  /* '<S1>:83:15' psi_q=1000*(-1)*(mean(vd_register)-OnlineID_output.Rph_out*mean(id_register))/(mean(omega_register)*GlobalConfig.PMSM_config.polePairs); */
  d_x = rtOnlineID_DW->vd_register[0];
  e_x = rtOnlineID_DW->id_register[0];

  /* '<S1>:83:16' OnlineID_output.psi_array(1,array_counter)=mean(id_register); */
  g_x = rtOnlineID_DW->id_register[0];
  for (i = 0; i < 49; i++) {
    Wtemp_check += rtOnlineID_DW->vq_register[i + 1];
    b_x += rtOnlineID_DW->iq_register[i + 1];
    d_x += rtOnlineID_DW->vd_register[i + 1];
    e_x_tmp = rtOnlineID_DW->id_register[i + 1];
    e_x += e_x_tmp;
    g_x += e_x_tmp;
  }

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[588] = g_x / 50.0F;

  /* '<S1>:83:17' OnlineID_output.psi_array(2,array_counter)=mean(iq_register); */
  g_x = rtOnlineID_DW->iq_register[0];
  for (i = 0; i < 49; i++) {
    g_x += rtOnlineID_DW->iq_register[i + 1];
  }

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[589] = g_x / 50.0F;

  /* '<S1>:83:18' OnlineID_output.psi_array(3,array_counter)=mean(omega_register); */
  g_x = ((((rtOnlineID_DW->omega_register[0] + rtOnlineID_DW->omega_register[1])
           + rtOnlineID_DW->omega_register[2]) + rtOnlineID_DW->omega_register[3])
         + rtOnlineID_DW->omega_register[4]) / 5.0F;

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[590] = g_x;

  /* '<S1>:83:19' OnlineID_output.psi_array(4,array_counter)=OnlineID_output.Wtemp; */
  rtOnlineID_Y->OnlineID_output.psi_array[591] =
    rtOnlineID_Y->OnlineID_output.Wtemp;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:83:20' OnlineID_output.psi_array(5,array_counter)=psi_d; */
  g_x *= rtOnlineID_U->GlobalConfig_out.PMSM_config.polePairs;

  /* Outport: '<Root>/OnlineID_output' */
  rtOnlineID_Y->OnlineID_output.psi_array[592] = (Wtemp_check / 50.0F - b_x /
    50.0F * rtOnlineID_Y->OnlineID_output.Rph_out) * 1000.0F / g_x;

  /* '<S1>:83:21' OnlineID_output.psi_array(6,array_counter)=psi_q; */
  rtOnlineID_Y->OnlineID_output.psi_array[593] = (d_x / 50.0F - e_x / 50.0F *
    rtOnlineID_Y->OnlineID_output.Rph_out) * -1000.0F / g_x;

  /* '<S1>:83:22' OnlineID_output.clean_array_flag=boolean(1); */
  rtOnlineID_Y->OnlineID_output.clean_array_flag = true;

  /* '<S1>:83:23' breakback=single(1); */
  rtOnlineID_DW->breakback = 1.0F;
}

/*
 * Function for Chart: '<Root>/OnlineID'
 * function RefreshDataRegister
 */
static void RefreshDataRegister_i(DW_OnlineID_t *rtOnlineID_DW)
{
  uint16_T k;

  /* MATLAB Function 'RefreshDataRegister': '<S1>:48' */
	/* '<S1>:48:3' if(mod(counter,2000)==0) */
	if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 2000U * 2000U == 0U) {
    /* '<S1>:48:4' m=length(omega_register); */
    /* '<S1>:48:5' for k= uint16(0):uint16(m-2) */
    /* '<S1>:48:6' omega_register(m-k)=omega_register(m-(k+1)); */
    rtOnlineID_DW->omega_register[4] = rtOnlineID_DW->omega_register[3];

    /* '<S1>:48:6' omega_register(m-k)=omega_register(m-(k+1)); */
    rtOnlineID_DW->omega_register[3] = rtOnlineID_DW->omega_register[2];

    /* '<S1>:48:6' omega_register(m-k)=omega_register(m-(k+1)); */
    rtOnlineID_DW->omega_register[2] = rtOnlineID_DW->omega_register[1];

    /* '<S1>:48:6' omega_register(m-k)=omega_register(m-(k+1)); */
    rtOnlineID_DW->omega_register[1] = rtOnlineID_DW->omega_register[0];
  }

  /* '<S1>:48:9' m=length(iq_register); */
  /* '<S1>:48:10' for k= uint16(0):uint16(m-2) */
  for (k = 0; k < 49; k++) {
    /* '<S1>:48:11' iq_register(m-k)=iq_register(m-(k+1)); */
    rtOnlineID_DW->iq_register[49 - k] = rtOnlineID_DW->iq_register[48 - k];

    /* '<S1>:48:12' id_register(m-k)=id_register(m-(k+1)); */
    rtOnlineID_DW->id_register[49 - k] = rtOnlineID_DW->id_register[48 - k];

    /* '<S1>:48:13' vd_register(m-k)=vd_register(m-(k+1)); */
    rtOnlineID_DW->vd_register[49 - k] = rtOnlineID_DW->vd_register[48 - k];

    /* '<S1>:48:14' vq_register(m-k)=vq_register(m-(k+1)); */
    rtOnlineID_DW->vq_register[49 - k] = rtOnlineID_DW->vq_register[48 - k];
  }
}

/*
 * Function for Chart: '<Root>/OnlineID'
 * function [allow_measurement, om_con,iq_con,id_con,i_val]=CheckSteadyState(iq_reg_in,id_reg_in,om_reg_in,timer)
 */
static void CheckSteadyState(const real32_T iq_reg_in[50], const real32_T
  id_reg_in[50], const real32_T om_reg_in[5], uint32_T timer, boolean_T
  *allow_measurement, boolean_T *om_con, boolean_T *iq_con, boolean_T *id_con,
  boolean_T *i_val, ExtU_OnlineID_t *rtOnlineID_U)
{
	int32_T k;
  real32_T ex;
  real32_T mean_id_reg;
  real32_T mean_iq_reg;
	real32_T mean_iq_reg_tmp;
  real32_T mean_om_reg;
  real32_T tmp;

  /* MATLAB Function 'CheckSteadyState': '<S1>:182' */
  /* '<S1>:182:3' mean_om_reg=mean(om_reg_in); */
  mean_om_reg = ((((om_reg_in[0] + om_reg_in[1]) + om_reg_in[2]) + om_reg_in[3])
                 + om_reg_in[4]) / 5.0F;

  /* '<S1>:182:4' mean_id_reg=mean(id_reg_in); */
  mean_id_reg = id_reg_in[0];

  /* '<S1>:182:5' mean_iq_reg=mean(iq_reg_in); */
  mean_iq_reg = iq_reg_in[0];

	/* '<S1>:182:7' if((mean_iq_reg+(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))>=max(iq_reg_in)... */
	/* '<S1>:182:8'         &&(mean_iq_reg-(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))<=min(iq_reg_in)&&min(iq_reg_in)~=0) */
	ex = iq_reg_in[0];
	for (k = 0; k < 49; k++) {
		mean_id_reg += id_reg_in[k + 1];
		mean_iq_reg_tmp = iq_reg_in[k + 1];
		mean_iq_reg += mean_iq_reg_tmp;
		if (ex < mean_iq_reg_tmp) {
			ex = mean_iq_reg_tmp;
		}
  }

  mean_id_reg /= 50.0F;
  mean_iq_reg /= 50.0F;

  /* Inport: '<Root>/OnlineIDConfig' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
	mean_iq_reg_tmp = rtOnlineID_U->OnlineIDConfig.dev_curr *
    rtOnlineID_U->GlobalConfig_out.ratCurrent;
	if (mean_iq_reg_tmp + mean_iq_reg >= ex) {
		ex = iq_reg_in[0];
		for (k = 0; k < 49; k++) {
			tmp = iq_reg_in[k + 1];
			if (ex > tmp) {
				ex = tmp;
			}
		}

		if (mean_iq_reg - mean_iq_reg_tmp <= ex) {
			ex = iq_reg_in[0];
			for (k = 0; k < 49; k++) {
				tmp = iq_reg_in[k + 1];
				if (ex > tmp) {
					ex = tmp;
				}
			}

      if (ex != 0.0F) {
        /* '<S1>:182:9' iq_con=boolean(1); */
        *iq_con = true;
      } else {
        /* '<S1>:182:10' else */
        /* '<S1>:182:11' iq_con=boolean(0); */
        *iq_con = false;
      }
    } else {
      /* '<S1>:182:10' else */
      /* '<S1>:182:11' iq_con=boolean(0); */
      *iq_con = false;
    }
  } else {
    /* '<S1>:182:10' else */
    /* '<S1>:182:11' iq_con=boolean(0); */
    *iq_con = false;
  }

  /* '<S1>:182:14' if((mean_id_reg+(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))>=max(id_reg_in)... */
  /* '<S1>:182:15'         &&(mean_id_reg-(OnlineIDConfig.dev_curr*GlobalConfig.ratCurrent))<=min(id_reg_in)&&min(id_reg_in)~=0) */
	ex = id_reg_in[0];
	for (k = 0; k < 49; k++) {
		tmp = id_reg_in[k + 1];
		if (ex < tmp) {
			ex = tmp;
		}
	}

	if (mean_iq_reg_tmp + mean_id_reg >= ex) {
		ex = id_reg_in[0];
		for (k = 0; k < 49; k++) {
			tmp = id_reg_in[k + 1];
			if (ex > tmp) {
				ex = tmp;
			}
		}

		if (mean_id_reg - mean_iq_reg_tmp <= ex) {
			ex = id_reg_in[0];
			for (k = 0; k < 49; k++) {
				mean_iq_reg_tmp = id_reg_in[k + 1];
				if (ex > mean_iq_reg_tmp) {
					ex = mean_iq_reg_tmp;
				}
			}

      if (ex != 0.0F) {
        /* '<S1>:182:16' id_con=boolean(1); */
        *id_con = true;
      } else {
        /* '<S1>:182:17' else */
        /* '<S1>:182:18' id_con=boolean(0); */
        *id_con = false;
      }
    } else {
      /* '<S1>:182:17' else */
      /* '<S1>:182:18' id_con=boolean(0); */
      *id_con = false;
    }
  } else {
    /* '<S1>:182:17' else */
    /* '<S1>:182:18' id_con=boolean(0); */
    *id_con = false;
  }

  /* Inport: '<Root>/GlobalConfig' incorporates:
   *  Inport: '<Root>/OnlineIDConfig'
   */
  /* '<S1>:182:21' if(mean_om_reg<((GlobalConfig.ratSpeed*OnlineIDConfig.max_n_ratio*2*pi)/60) && mean_om_reg>((GlobalConfig.ratSpeed*OnlineIDConfig.min_n_ratio*2*pi)/60)) */
  if (mean_om_reg < rtOnlineID_U->GlobalConfig_out.ratSpeed *
      rtOnlineID_U->OnlineIDConfig.max_n_ratio * 2.0F * 3.14159274F / 60.0F) {
    if (mean_om_reg > rtOnlineID_U->GlobalConfig_out.ratSpeed *
        rtOnlineID_U->OnlineIDConfig.min_n_ratio * 2.0F * 3.14159274F / 60.0F) {
      /* Drehzahlgrenzwerte in rad/sec */
      /* '<S1>:182:22' if((mean_om_reg+((OnlineIDConfig.dev_omega*GlobalConfig.ratSpeed*2*pi)/60))>=max(om_reg_in)... */
      /* '<S1>:182:23'         &&(mean_om_reg-((OnlineIDConfig.dev_omega*GlobalConfig.ratSpeed*2*pi)/60))<=min(om_reg_in)&&min(om_reg_in)~=0) */
			ex = om_reg_in[0];
			if (om_reg_in[0] < om_reg_in[1]) {
				ex = om_reg_in[1];
			}

			if (ex < om_reg_in[2]) {
				ex = om_reg_in[2];
      }

			if (ex < om_reg_in[3]) {
				ex = om_reg_in[3];
			}

			if (ex < om_reg_in[4]) {
				ex = om_reg_in[4];
      }

			mean_iq_reg_tmp = rtOnlineID_U->OnlineIDConfig.dev_omega *
        rtOnlineID_U->GlobalConfig_out.ratSpeed * 2.0F * 3.14159274F / 60.0F;
			if (mean_iq_reg_tmp + mean_om_reg >= ex) {
				ex = om_reg_in[0];
				if (om_reg_in[0] > om_reg_in[1]) {
					ex = om_reg_in[1];
				}

				if (ex > om_reg_in[2]) {
					ex = om_reg_in[2];
				}

				if (ex > om_reg_in[3]) {
					ex = om_reg_in[3];
				}

				if (ex > om_reg_in[4]) {
					ex = om_reg_in[4];
				}

				if (mean_om_reg - mean_iq_reg_tmp <= ex) {
					mean_om_reg = om_reg_in[0];
					if (om_reg_in[0] > om_reg_in[1]) {
						mean_om_reg = om_reg_in[1];
					}

					if (mean_om_reg > om_reg_in[2]) {
						mean_om_reg = om_reg_in[2];
					}

					if (mean_om_reg > om_reg_in[3]) {
						mean_om_reg = om_reg_in[3];
					}

					if (mean_om_reg > om_reg_in[4]) {
						mean_om_reg = om_reg_in[4];
					}

					if (mean_om_reg != 0.0F) {
            /* '<S1>:182:24' om_con=boolean(1); */
            *om_con = true;
          } else {
            /* '<S1>:182:25' else */
            /* '<S1>:182:26' om_con=boolean(0); */
            *om_con = false;
          }
        } else {
          /* '<S1>:182:25' else */
          /* '<S1>:182:26' om_con=boolean(0); */
          *om_con = false;
        }
      } else {
        /* '<S1>:182:25' else */
        /* '<S1>:182:26' om_con=boolean(0); */
        *om_con = false;
      }
    } else {
      /* '<S1>:182:28' else */
      /* '<S1>:182:29' om_con=boolean(0); */
      *om_con = false;
    }
  } else {
    /* '<S1>:182:28' else */
    /* '<S1>:182:29' om_con=boolean(0); */
    *om_con = false;
  }

  /* Inport: '<Root>/OnlineIDConfig' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S1>:182:32' if(sqrt(mean_iq_reg^2 + mean_id_reg^2)<OnlineIDConfig.nom_factor*GlobalConfig.ratCurrent) */
  if (sqrtf(mean_iq_reg * mean_iq_reg + mean_id_reg * mean_id_reg) <
      rtOnlineID_U->OnlineIDConfig.nom_factor *
      rtOnlineID_U->GlobalConfig_out.ratCurrent) {
    /* '<S1>:182:33' i_val=boolean(1); */
    *i_val = true;

    /* Checks, if iq- and id-currents are within */
  } else {
    /* '<S1>:182:34' else */
    /* the set limit. The variable nom-factor sets  */
    /* '<S1>:182:35' i_val=boolean(0); */
    *i_val = false;

    /* the range of the allowed limit,  i.e.  */
  }

  /* Inport: '<Root>/GlobalConfig' incorporates:
   *  Inport: '<Root>/OnlineIDConfig'
   */
  /* nominal current or 0.5*nominal current */
  /* If currents are inside this limit, the  */
  /* linear parameters will be measured */
  /* '<S1>:182:40' if(timer>=OnlineIDConfig.Rs_time*(1/GlobalConfig.sampleTimeISR) && i_val==0) */
  if (((real_T)timer >= 1.0F / rtOnlineID_U->GlobalConfig_out.sampleTimeISR *
       rtOnlineID_U->OnlineIDConfig.Rs_time) && (!*i_val)) {
    /* Rs_time in seconds  */
    /* '<S1>:182:41' allow_measurement = boolean(1); */
    *allow_measurement = true;

    /* If the machine operates for a set time outside */
  } else if (*i_val) {
    /* '<S1>:182:42' elseif(i_val==1) */
    /* the current limit, the measurement of the linear */
    /* '<S1>:182:43' allow_measurement = boolean(1); */
    *allow_measurement = true;

    /* parameter start again regardless of the machine state */
  } else {
    /* '<S1>:182:44' else */
    /* '<S1>:182:45' allow_measurement = boolean(0); */
    *allow_measurement = false;
  }
}

/* Function for Chart: '<Root>/OnlineID' */
static void RefreshDataRegister(ExtU_OnlineID_t *rtOnlineID_U, ExtY_OnlineID_t
  *rtOnlineID_Y, DW_OnlineID_t *rtOnlineID_DW)
{
  int32_T i;
	real32_T iq_register_tmp;
  uint32_T qY;
	boolean_T tmp;

  /* During 'RefreshDataRegister': '<S1>:37' */
  /* '<S1>:55:1' sf_internal_predicateOutput = allow_meas==1&&omega_const==1.... */
  /* '<S1>:55:2' &&iq_const==1&&id_const==1; */
  if (rtOnlineID_DW->allow_meas && rtOnlineID_DW->omega_const &&
      rtOnlineID_DW->iq_const && rtOnlineID_DW->id_const) {
    /* Transition: '<S1>:55' */
    rtOnlineID_DW->is_OnlineIDSuperState = IN_CalcLinearParamsState;

    /* Outport: '<Root>/OnlineID_output' */
    /* Entry 'CalcLinearParamsState': '<S1>:106' */
    /* '<S1>:106:3' OnlineID_output.activeState = uint16(502); */
    rtOnlineID_Y->OnlineID_output.activeState = 502U;

		/* '<S1>:106:4' OnlineID_output.IdControlFlag=boolean(1); */
		rtOnlineID_Y->OnlineID_output.IdControlFlag = true;

		/* '<S1>:106:5' iq1counter=single(0); */
    rtOnlineID_DW->iq1counter = 0.0F;

		/* '<S1>:106:6' iq2counter=single(0); */
    rtOnlineID_DW->iq2counter = 0.0F;

		/* '<S1>:106:7' id1counter=single(0); */
    rtOnlineID_DW->id1counter = 0.0F;

		/* '<S1>:106:8' id2counter=single(0); */
    rtOnlineID_DW->id2counter = 0.0F;

		/* '<S1>:106:9' Vd1counter=single(0); */
    rtOnlineID_DW->Vd1counter = 0.0F;

		/* '<S1>:106:10' Vd2counter=single(0); */
    rtOnlineID_DW->Vd2counter = 0.0F;

		/* '<S1>:106:11' Vq1counter=single(0); */
    rtOnlineID_DW->Vq1counter = 0.0F;

		/* '<S1>:106:12' Vq2counter=single(0); */
    rtOnlineID_DW->Vq2counter = 0.0F;

		/* '<S1>:106:13' omega1counter=single(0); */
    rtOnlineID_DW->omega1counter = 0.0F;

		/* '<S1>:106:14' omega2counter=single(0); */
    rtOnlineID_DW->omega2counter = 0.0F;

		/* '<S1>:106:15' stop_ident=boolean(0); */
    rtOnlineID_DW->stop_ident = false;

		/* '<S1>:106:16' omega_sum=single(0); */
    rtOnlineID_DW->omega_sum = 0.0F;

		/* '<S1>:106:17' iq_sum=single(0); */
    rtOnlineID_DW->iq_sum = 0.0F;

		/* '<S1>:106:18' counter=uint32(1); */
    rtOnlineID_DW->counter = 1U;

    /* Inport: '<Root>/OnlineIDConfig' incorporates:
     *  Inport: '<Root>/GlobalConfig'
     */
		/* '<S1>:106:19' if(counter_time>=(OnlineIDConfig.Rs_time/GlobalConfig.sampleTimeISR) && i_valid==0) */
		if ((real_T) rtOnlineID_DW->counter_time >= rtOnlineID_U->OnlineIDConfig.Rs_time / rtOnlineID_U->GlobalConfig_out.sampleTimeISR) {
      if (!rtOnlineID_DW->i_valid) {
        /* Sets variable to 1, if Rs will be identified */
				/* '<S1>:106:20' LinPara_ident_outside=boolean(1); */
        rtOnlineID_DW->LinPara_ident_outside = true;

        /*  outside the valid range */
      } else {
				/* '<S1>:106:21' else */
				/* '<S1>:106:22' LinPara_ident_outside=boolean(0); */
        rtOnlineID_DW->LinPara_ident_outside = false;
      }
    } else {
			/* '<S1>:106:21' else */
			/* '<S1>:106:22' LinPara_ident_outside=boolean(0); */
      rtOnlineID_DW->LinPara_ident_outside = false;
    }

		/* '<S1>:106:24' if(i_valid==1) */
    if (rtOnlineID_DW->i_valid) {
			/* '<S1>:106:25' counter_time=uint32(0); */
      rtOnlineID_DW->counter_time = 0U;

      /* Resets the timer, since the lin.Para. will be identified */
    }

    /* inside the valid range */
		/* '<S1>:106:27' omega_register_alt=omega_register; */
    for (i = 0; i < 5; i++) {
      rtOnlineID_DW->omega_register_alt[i] = rtOnlineID_DW->omega_register[i];
    }

		/* '<S1>:106:28' id_register_alt=id_register; */
		/* '<S1>:106:29' iq_register_alt=iq_register; */
    memcpy(&rtOnlineID_DW->id_register_alt[0], &rtOnlineID_DW->id_register[0],
           50U * sizeof(real32_T));
    memcpy(&rtOnlineID_DW->iq_register_alt[0], &rtOnlineID_DW->iq_register[0],
           50U * sizeof(real32_T));

    /* uses the old values of State501 as starting point */
		/* '<S1>:106:30' omega_register_neu=single(zeros(5,1)); */
    for (i = 0; i < 5; i++) {
      rtOnlineID_DW->omega_register_neu[i] = 0.0F;
    }

		/* '<S1>:106:31' id_register_neu=single(zeros(10,1)); */
		/* '<S1>:106:32' iq_register_neu=single(zeros(10,1)); */
    for (i = 0; i < 10; i++) {
      rtOnlineID_DW->id_register_neu[i] = 0.0F;
      rtOnlineID_DW->iq_register_neu[i] = 0.0F;
    }
  } else {
    /* '<S1>:378:1' sf_internal_predicateOutput = LinPara_ident_outside==0 && OnlineIDConfig.allowPsiCalcOutside==0 .... */
    /* '<S1>:378:2' && allow_meas==0&&omega_const==1&&iq_const==1; */
    /* . */
		tmp = !rtOnlineID_DW->allow_meas;

    /* Inport: '<Root>/OnlineIDConfig' */
    if (((!rtOnlineID_DW->LinPara_ident_outside) &&
         (!rtOnlineID_U->OnlineIDConfig.allowPsiCalcOutside) && tmp &&
         rtOnlineID_DW->omega_const && rtOnlineID_DW->iq_const) ||
        (rtOnlineID_U->OnlineIDConfig.allowPsiCalcOutside && tmp &&
         rtOnlineID_DW->omega_const && rtOnlineID_DW->iq_const)) {
      /* Transition: '<S1>:378' */
      /* Transition: '<S1>:331' */
      rtOnlineID_DW->is_OnlineIDSuperState = IN_PsiCalcState;
      enter_atomic_PsiCalcState(rtOnlineID_U, rtOnlineID_Y, rtOnlineID_DW);
    } else {
      /* '<S1>:331:1' sf_internal_predicateOutput = OnlineIDConfig.allowPsiCalcOutside==1 .... */
      /* '<S1>:331:2' && allow_meas==0&&omega_const==1&&iq_const==1; */
      /* . */
      /* '<S1>:37:15' counter=uint32(counter+1); */
      qY = rtOnlineID_DW->counter + /*MW:OvSatOk*/ 1U;
      if (rtOnlineID_DW->counter + 1U < rtOnlineID_DW->counter) {
        qY = MAX_uint32_T;
      }

      rtOnlineID_DW->counter = qY;

      /* '<S1>:37:16' counter_time=uint32(counter_time+1); */
      qY = rtOnlineID_DW->counter_time + /*MW:OvSatOk*/ 1U;
      if (rtOnlineID_DW->counter_time + 1U < rtOnlineID_DW->counter_time) {
        qY = MAX_uint32_T;
      }

      rtOnlineID_DW->counter_time = qY;

      /* Inport: '<Root>/ActualValues' */
      /* '<S1>:37:17' iq_sum=iq_sum+single(ActualValues.i_dq.q); */
      rtOnlineID_DW->iq_sum += rtOnlineID_U->ActualValues.i_dq.q;

      /* '<S1>:37:18' id_sum=id_sum+single(ActualValues.i_dq.d); */
      rtOnlineID_DW->id_sum += rtOnlineID_U->ActualValues.i_dq.d;

      /* '<S1>:37:19' vd_sum=vd_sum+single(ActualValues.v_dq.d); */
      rtOnlineID_DW->vd_sum += rtOnlineID_U->ActualValues.v_dq.d;

      /* '<S1>:37:20' vq_sum=vq_sum+single(ActualValues.v_dq.q); */
      rtOnlineID_DW->vq_sum += rtOnlineID_U->ActualValues.v_dq.q;

      /* '<S1>:37:21' omega_sum=omega_sum+single(ActualValues.omega_m); */
      rtOnlineID_DW->omega_sum += rtOnlineID_U->ActualValues.omega_m;

			/* '<S1>:37:22' if(mod(counter,200)==0) */
			if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 200U * 200U == 0U) {
        /* '<S1>:37:23' RefreshDataRegister; */
        RefreshDataRegister_i(rtOnlineID_DW);

				/* Inport: '<Root>/GlobalConfig' */
        /* '<S1>:37:24' iq_register(1,1)=iq_sum/(0.01/GlobalConfig.sampleTimeISR); */
				iq_register_tmp = 0.01F / rtOnlineID_U->GlobalConfig_out.sampleTimeISR;
				rtOnlineID_DW->iq_register[0] = rtOnlineID_DW->iq_sum / iq_register_tmp;

        /* '<S1>:37:25' id_register(1,1)=id_sum/(0.01/GlobalConfig.sampleTimeISR); */
				rtOnlineID_DW->id_register[0] = rtOnlineID_DW->id_sum / iq_register_tmp;

        /* '<S1>:37:26' vd_register(1,1)=vd_sum/(0.01/GlobalConfig.sampleTimeISR); */
				rtOnlineID_DW->vd_register[0] = rtOnlineID_DW->vd_sum / iq_register_tmp;

        /* '<S1>:37:27' vq_register(1,1)=vq_sum/(0.01/GlobalConfig.sampleTimeISR); */
				rtOnlineID_DW->vq_register[0] = rtOnlineID_DW->vq_sum / iq_register_tmp;

        /* '<S1>:37:28' iq_sum=single(0); */
        rtOnlineID_DW->iq_sum = 0.0F;

        /* '<S1>:37:29' id_sum=single(0); */
        rtOnlineID_DW->id_sum = 0.0F;

        /* '<S1>:37:30' vd_sum=single(0); */
        rtOnlineID_DW->vd_sum = 0.0F;

        /* '<S1>:37:31' vq_sum=single(0); */
        rtOnlineID_DW->vq_sum = 0.0F;

				/* '<S1>:37:32' if(mod(counter,2000)==0) */
				if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 2000U * 2000U == 0U) {
					/* Inport: '<Root>/GlobalConfig' */
          /* '<S1>:37:33' omega_register(1,1)=omega_sum/(0.1/GlobalConfig.sampleTimeISR); */
					rtOnlineID_DW->omega_register[0] = rtOnlineID_DW->omega_sum / (0.1F / rtOnlineID_U->GlobalConfig_out.sampleTimeISR);

          /* '<S1>:37:34' omega_sum=single(0); */
          rtOnlineID_DW->omega_sum = 0.0F;

					/* '<S1>:37:35' [allow_meas,omega_const,iq_const,id_const,i_valid]=CheckSteadyState(abs(iq_register),abs(id_register),abs(omega_register),counter_time); */
					for (i = 0; i < 50; i++) {
						rtOnlineID_DW->y_m[i] = fabsf(rtOnlineID_DW->iq_register[i]);
						rtOnlineID_DW->b_y_c[i] = fabsf(rtOnlineID_DW->id_register[i]);
          }

					for (i = 0; i < 5; i++) {
						rtOnlineID_DW->c_y_k[i] = fabsf(rtOnlineID_DW->omega_register[i]);
          }

					CheckSteadyState(rtOnlineID_DW->y_m, rtOnlineID_DW->b_y_c, rtOnlineID_DW->c_y_k, rtOnlineID_DW->counter_time, &rtOnlineID_DW->allow_meas,
					                &rtOnlineID_DW->omega_const, &rtOnlineID_DW->iq_const, &rtOnlineID_DW->id_const, &rtOnlineID_DW->i_valid, rtOnlineID_U);
        }
      }
    }
  }
}

/* Model step function */
void OnlineID_step(RT_MODEL_OnlineID_t *const rtOnlineID_M)
{
  DW_OnlineID_t *rtOnlineID_DW = rtOnlineID_M->dwork;
  ExtU_OnlineID_t *rtOnlineID_U = (ExtU_OnlineID_t *) rtOnlineID_M->inputs;
  ExtY_OnlineID_t *rtOnlineID_Y = (ExtY_OnlineID_t *) rtOnlineID_M->outputs;
	int32_T k;
	real32_T temp_diff;
  uint32_T qY;
  boolean_T guard1 = false;
	boolean_T tmp;

  /* Chart: '<Root>/OnlineID' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/OnlineIDConfig'
   *  Outport: '<Root>/OnlineID_output'
   */
  /* Gateway: OnlineID */
  /* During: OnlineID */
  if (rtOnlineID_DW->is_active_c5_OnlineID == 0U) {
    /* Entry: OnlineID */
    rtOnlineID_DW->is_active_c5_OnlineID = 1U;

    /* Entry Internal: OnlineID */
    /* Transition: '<S1>:455' */
    rtOnlineID_DW->is_c5_OnlineID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:452' */
    /* wait for activation of */
    /* OnlineID */
    /* donothing */
  } else if (rtOnlineID_DW->is_c5_OnlineID == IN_OnlineIDSuperState) {
    /* During 'OnlineIDSuperState': '<S1>:39' */
    /* '<S1>:453:1' sf_internal_predicateOutput = ControlFlags.enableOnlineID==0 || GlobalConfig.Reset==1 ||.... */
    /* '<S1>:453:2'  OnlineIDConfig.OnlineID_Reset==1 || GlobalConfig.enableParameterID==0; */
    /* . */
    if ((!rtOnlineID_U->ControlFlags.enableOnlineID) ||
        rtOnlineID_U->GlobalConfig_out.Reset ||
        rtOnlineID_U->OnlineIDConfig.OnlineID_Reset ||
        (!rtOnlineID_U->GlobalConfig_out.enableParameterID)) {
      /* Transition: '<S1>:453' */
      /* '<S1>:453:3' InitParams */
      InitParams(rtOnlineID_U, rtOnlineID_Y, rtOnlineID_DW);

      /* Exit Internal 'OnlineIDSuperState': '<S1>:39' */
      if (rtOnlineID_DW->is_OnlineIDSuperState == IN_CalcLinearParamsState) {
        /* Exit 'CalcLinearParamsState': '<S1>:106' */
				/* '<S1>:106:55' OnlineID_output.id_out=single(0.0); */
        rtOnlineID_Y->OnlineID_output.id_out = 0.0F;

				/* '<S1>:106:56' OnlineID_output.IdControlFlag=boolean(0); */
        rtOnlineID_Y->OnlineID_output.IdControlFlag = false;
        rtOnlineID_DW->is_OnlineIDSuperState = IN_NO_ACTIVE_CHILD;
      } else {
        rtOnlineID_DW->is_OnlineIDSuperState = IN_NO_ACTIVE_CHILD;
      }

      rtOnlineID_DW->is_c5_OnlineID = IN_Waiting;

      /* Entry 'Waiting': '<S1>:452' */
      /* wait for activation of */
      /* OnlineID */
      /* donothing */
    } else {
      guard1 = false;
      switch (rtOnlineID_DW->is_OnlineIDSuperState) {
       case IN_CalcLinearParamsState:
        /* During 'CalcLinearParamsState': '<S1>:106' */
        /* '<S1>:317:1' sf_internal_predicateOutput = stop_ident==1; */
        if (rtOnlineID_DW->stop_ident) {
          /* Transition: '<S1>:317' */
					guard1 = true;
        } else {
					/* '<S1>:113:1' sf_internal_predicateOutput = OnlineIDConfig.allowPsiCalcOutside==1 && counter==24001.... */
          /* '<S1>:113:2'  || LinPara_ident_outside==0 && OnlineIDConfig.allowPsiCalcOutside==0 &&.... */
					/* '<S1>:113:3'  counter==24001; */
          /* . */
					tmp = !rtOnlineID_U->OnlineIDConfig.allowPsiCalcOutside;
					if ((rtOnlineID_U->OnlineIDConfig.allowPsiCalcOutside && (rtOnlineID_DW->counter == 24001U))
					                || ((!rtOnlineID_DW->LinPara_ident_outside) && tmp && (rtOnlineID_DW->counter == 24001U))) {
            /* Transition: '<S1>:113' */
            /* Exit 'CalcLinearParamsState': '<S1>:106' */
						/* '<S1>:106:55' OnlineID_output.id_out=single(0.0); */
            rtOnlineID_Y->OnlineID_output.id_out = 0.0F;

						/* '<S1>:106:56' OnlineID_output.IdControlFlag=boolean(0); */
            rtOnlineID_Y->OnlineID_output.IdControlFlag = false;
            rtOnlineID_DW->is_OnlineIDSuperState = IN_PsiCalcState;
            enter_atomic_PsiCalcState(rtOnlineID_U, rtOnlineID_Y, rtOnlineID_DW);

            /* '<S1>:375:1' sf_internal_predicateOutput = OnlineIDConfig.allowPsiCalcOutside==0 && LinPara_ident_outside==1.... */
						/* '<S1>:375:2'  && counter==24001; */
					} else if (tmp && rtOnlineID_DW->LinPara_ident_outside && (rtOnlineID_DW->counter == 24001U)) {
						/* Transition: '<S1>:375' */
						guard1 = true;
					} else {
						/* '<S1>:106:34' OnlineID_output.id_out=i_d_R_online; */
						rtOnlineID_Y->OnlineID_output.id_out = rtOnlineID_DW->i_d_R_online;

						/* '<S1>:106:35' counter=counter+uint32(1); */
						qY = rtOnlineID_DW->counter + /*MW:OvSatOk*/1U;
						if (rtOnlineID_DW->counter + 1U < rtOnlineID_DW->counter) {
              qY = MAX_uint32_T;
            }

						rtOnlineID_DW->counter = qY;

						/* '<S1>:106:36' identParams; */
						identParams(rtOnlineID_U, rtOnlineID_Y, rtOnlineID_DW);

						/* '<S1>:106:37' iq_sum=iq_sum+single(ActualValues.i_dq.q); */
						rtOnlineID_DW->iq_sum += rtOnlineID_U->ActualValues.i_dq.q;

						/* '<S1>:106:38' id_sum=id_sum+single(ActualValues.i_dq.d); */
						rtOnlineID_DW->id_sum += rtOnlineID_U->ActualValues.i_dq.d;

						/* '<S1>:106:39' omega_sum=omega_sum+single(ActualValues.omega_m); */
						rtOnlineID_DW->omega_sum += rtOnlineID_U->ActualValues.omega_m;

						/* averages iq over 100 and omega over 200 measuring points */
						/* '<S1>:106:40' if(mod(counter,200)==0) */
						if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 200U * 200U == 0U) {
							/* '<S1>:106:41' RefreshDataRegister; */
							RefreshDataRegister_i1(rtOnlineID_DW);

							/* '<S1>:106:42' iq_register_neu(1,1)=iq_sum/(0.01/GlobalConfig.sampleTimeISR); */
							temp_diff = 0.01F / rtOnlineID_U->GlobalConfig_out.sampleTimeISR;
							rtOnlineID_DW->iq_register_neu[0] = rtOnlineID_DW->iq_sum / temp_diff;

							/* '<S1>:106:43' id_register_neu(1,1)=id_sum/(0.01/GlobalConfig.sampleTimeISR); */
							rtOnlineID_DW->id_register_neu[0] = rtOnlineID_DW->id_sum / temp_diff;

							/* '<S1>:106:44' iq_sum=single(0); */
							rtOnlineID_DW->iq_sum = 0.0F;

							/* '<S1>:106:45' id_sum=single(0); */
							rtOnlineID_DW->id_sum = 0.0F;

							/* '<S1>:106:46' if(mod(counter,400)==0) */
							if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 400U * 400U == 0U) {
								/* '<S1>:106:47' omega_register_neu(1,1)=omega_sum/(0.02/GlobalConfig.sampleTimeISR); */
								rtOnlineID_DW->omega_register_neu[0] = rtOnlineID_DW->omega_sum / (0.02F / rtOnlineID_U->GlobalConfig_out.sampleTimeISR);

								/* '<S1>:106:48' omega_sum=single(0); */
								rtOnlineID_DW->omega_sum = 0.0F;
							}

							/* '<S1>:106:50' if(mod(counter,2000)==0) */
							if (rtOnlineID_DW->counter - rtOnlineID_DW->counter / 2000U * 2000U == 0U) {
								/* checks every 0.1s if current omega and iq is too different from the old one */
								/* '<S1>:106:51' [stop_ident] = Break(abs(iq_register_alt),abs(id_register_alt),abs(omega_register_alt),abs(iq_register_neu),abs(id_register_neu),abs(omega_register_neu)); */
								for (k = 0; k < 50; k++) {
									rtOnlineID_DW->y[k] = fabsf(rtOnlineID_DW->iq_register_alt[k]);
									rtOnlineID_DW->b_y[k] = fabsf(rtOnlineID_DW->id_register_alt[k]);
								}

								for (k = 0; k < 5; k++) {
									rtOnlineID_DW->c_y[k] = fabsf(rtOnlineID_DW->omega_register_alt[k]);
								}

								for (k = 0; k < 10; k++) {
									rtOnlineID_DW->d_y[k] = fabsf(rtOnlineID_DW->iq_register_neu[k]);
									rtOnlineID_DW->e_y[k] = fabsf(rtOnlineID_DW->id_register_neu[k]);
								}

								for (k = 0; k < 5; k++) {
									rtOnlineID_DW->f_y[k] = fabsf(rtOnlineID_DW->omega_register_neu[k]);
								}

								rtOnlineID_DW->stop_ident = Break(rtOnlineID_DW->y, rtOnlineID_DW->b_y, rtOnlineID_DW->c_y, rtOnlineID_DW->d_y, rtOnlineID_DW->e_y,
								                rtOnlineID_DW->f_y, rtOnlineID_U);
							}
            }
          }
        }
        break;

       case IN_PsiCalcState:
        /* During 'PsiCalcState': '<S1>:83' */
        /* '<S1>:114:1' sf_internal_predicateOutput = breakback==1; */
        if (rtOnlineID_DW->breakback == 1.0F) {
          /* Transition: '<S1>:114' */
          rtOnlineID_DW->is_OnlineIDSuperState = IN_TempPsiCalcState;

          /* Entry 'TempPsiCalcState': '<S1>:201' */
          /* '<S1>:201:4' OnlineID_output.activeState=uint16(504); */
          rtOnlineID_Y->OnlineID_output.activeState = 504U;

          /* '<S1>:201:5' temp_diff=abs(OnlineID_output.Wtemp-OnlineIDConfig.Temp_ref); */
					temp_diff = fabsf(rtOnlineID_Y->OnlineID_output.Wtemp - rtOnlineID_U->OnlineIDConfig.Temp_ref);

          /* '<S1>:201:6' delta_psi=abs(OnlineID_output.psi_pm_out-GlobalConfig.PMSM_config.Psi_PM_Vs); */
          /* '<S1>:201:7' if(temp_diff>0&&temp_diff<99) */
					if ((temp_diff > 0.0F) && (temp_diff < 99.0F)) {
            /* '<S1>:201:8' OnlineID_output.delta_psi(1+floor(temp_diff),2)= OnlineID_output.delta_psi(1+floor(temp_diff),2)+1; */
						k = (int32_T) floorf(temp_diff);
						rtOnlineID_Y->OnlineID_output.delta_psi[k + 100]++;

            /* '<S1>:201:9' OnlineID_output.delta_psi(1+floor(temp_diff),1)= OnlineID_output.delta_psi(1+floor(temp_diff),1)+delta_psi; */
						rtOnlineID_Y->OnlineID_output.delta_psi[k] += fabsf
              (rtOnlineID_Y->OnlineID_output.psi_pm_out -
               rtOnlineID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs);
          }

          /* '<S1>:201:11' breakback=single(2); */
          rtOnlineID_DW->breakback = 2.0F;
        }
        break;

       case IN_RefreshDataRegister:
        RefreshDataRegister(rtOnlineID_U, rtOnlineID_Y, rtOnlineID_DW);
        break;

       default:
        /* During 'TempPsiCalcState': '<S1>:201' */
        /* '<S1>:209:1' sf_internal_predicateOutput = breakback==2; */
        if (rtOnlineID_DW->breakback == 2.0F) {
          /* Transition: '<S1>:209' */
          rtOnlineID_DW->is_OnlineIDSuperState = IN_RefreshDataRegister;
          enter_atomic_RefreshDataRegiste(rtOnlineID_Y, rtOnlineID_DW);
        }
        break;
      }

			if (guard1) {
        /* Exit 'CalcLinearParamsState': '<S1>:106' */
				/* '<S1>:106:55' OnlineID_output.id_out=single(0.0); */
        rtOnlineID_Y->OnlineID_output.id_out = 0.0F;

				/* '<S1>:106:56' OnlineID_output.IdControlFlag=boolean(0); */
        rtOnlineID_Y->OnlineID_output.IdControlFlag = false;
        rtOnlineID_DW->is_OnlineIDSuperState = IN_RefreshDataRegister;
        enter_atomic_RefreshDataRegiste(rtOnlineID_Y, rtOnlineID_DW);
      }
    }

    /* During 'Waiting': '<S1>:452' */
    /* '<S1>:456:1' sf_internal_predicateOutput = ControlFlags.enableOnlineID==1 && GlobalConfig.Reset==0.... */
    /* '<S1>:456:2' && OnlineIDConfig.OnlineID_Reset==0 &&.... */
    /* '<S1>:456:3'  ControlFlags.finished_all_Offline_states==1; */
    /* . */
  } else if (rtOnlineID_U->ControlFlags.enableOnlineID &&
             (!rtOnlineID_U->GlobalConfig_out.Reset) &&
             (!rtOnlineID_U->OnlineIDConfig.OnlineID_Reset) &&
             rtOnlineID_U->ControlFlags.finished_all_Offline_states) {
    /* Transition: '<S1>:456' */
    rtOnlineID_DW->is_c5_OnlineID = IN_OnlineIDSuperState;

    /* Entry 'OnlineIDSuperState': '<S1>:39' */
    /* '<S1>:39:3' InitParams; */
    InitParams(rtOnlineID_U, rtOnlineID_Y, rtOnlineID_DW);

    /* '<S1>:39:4' OnlineID_output.activeState=uint16(500); */
    rtOnlineID_Y->OnlineID_output.activeState = 500U;

    /* Entry Internal 'OnlineIDSuperState': '<S1>:39' */
    /* Transition: '<S1>:38' */
    rtOnlineID_DW->is_OnlineIDSuperState = IN_RefreshDataRegister;
    enter_atomic_RefreshDataRegiste(rtOnlineID_Y, rtOnlineID_DW);
  }

  /* End of Chart: '<Root>/OnlineID' */
}

/* Model initialize function */
void OnlineID_initialize(RT_MODEL_OnlineID_t *const rtOnlineID_M)
{
  ExtY_OnlineID_t *rtOnlineID_Y = (ExtY_OnlineID_t *) rtOnlineID_M->outputs;

	/* SystemInitialize for Chart: '<Root>/OnlineID' incorporates:
	 *  Outport: '<Root>/OnlineID_output'
	 */
	rtOnlineID_Y->OnlineID_output.id_out = 0.0F;
	rtOnlineID_Y->OnlineID_output.Rph_out = 0.0F;
	rtOnlineID_Y->OnlineID_output.Wtemp = 0.0F;
	memset(&rtOnlineID_Y->OnlineID_output.psi_array[0], 0, 600U * sizeof(real32_T));
	rtOnlineID_Y->OnlineID_output.IdControlFlag = false;
	rtOnlineID_Y->OnlineID_output.iq_mean_out = 0.0F;
	rtOnlineID_Y->OnlineID_output.id_mean_out = 0.0F;
	memset(&rtOnlineID_Y->OnlineID_output.delta_psi[0], 0, 200U * sizeof(real32_T));
	rtOnlineID_Y->OnlineID_output.activeState = 0U;
	rtOnlineID_Y->OnlineID_output.psi_pm_out = 0.0F;
	rtOnlineID_Y->OnlineID_output.Ld_out = 0.0F;
	rtOnlineID_Y->OnlineID_output.Lq_out = 0.0F;
	rtOnlineID_Y->OnlineID_output.clean_array_flag = false;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
