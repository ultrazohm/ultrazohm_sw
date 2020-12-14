/******************************************************************************
 *
 * javascope.h
 *
 * Copyright (C) 2019 UltraZohm Community, All rights reserved.
 *
 *  Created on: 21.08.2018
 *      Author: Sebastian Wendel (SW) & Philipp Löhdefink (PL)
 *
******************************************************************************/

#ifndef INCLUDE_JAVASCOPE_H_
#define INCLUDE_JAVASCOPE_H_


#include "ipc_ARM.h"

extern float zerovalue;

// Do not change the first (zero) and last (end) entries.
enum JS_OberservableData {
    JSO_ZEROVALUE=0,
	JSO_SineWave1,
    JSO_Sawtooth1,
    JSO_SineWave2,
	JSO_theta_mech,
	JSO_ua,
	JSO_ub,
	JSO_uc,
	JSO_ia,
	JSO_ib,
	JSO_ic,
	JSO_id,
	JSO_iq,
	JSO_ud,
	JSO_uq,
	JSO_Speed_rpm,
	JSO_LoadSpeed_rpm,
	JSO_volt_temp,
	JSO_SoC_init,
	JSO_Theta_el,
	JSO_Theta_mech,
	JSO_LoadTheta_mech,
	JSO_DeltaTheta_mech,
	JSO_Wtemp,
	JSO_Rs_mOhm,
	JSO_Ld_mH,
	JSO_Lq_mH,
	JSO_PsiPM_mVs,
    JSO_ENDMARKER
};

// slowData Naming Convention: Use INT or FLOAT to automatically identify Data Type in Java.
// Do not change the first (zero) and last (end) entries.
enum JS_SlowData {
	JSSD_ZEROVALUE=0,
	JSSD_INT_SecondsSinceSystemStart,
	JSSD_FLOAT_uSecPerIsr,
	JSSD_FLOAT_Sine,
	JSSD_FLOAT_FreqReadback,
	JSSD_INT_Milliseconds,
	JSSD_FLOAT_ADCconvFactorReadback,
	JSSD_FLOAT_Rs_Offline,
	JSSD_FLOAT_Ld_Offline,
	JSSD_FLOAT_Lq_Offline,
	JSSD_FLOAT_PsiPM_Offline,
	JSSD_FLOAT_J,
	JSSD_INT_polePairs,
	JSSD_INT_activeState,
	JSSD_FLOAT_u_d,
	JSSD_FLOAT_u_q,
	JSSD_FLOAT_i_d,
	JSSD_FLOAT_i_q,
	JSSD_FLOAT_speed,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_u_d_ref,
	JSSD_FLOAT_u_q_ref,
	JSSD_FLOAT_ArrayCounter,
	JSSD_FLOAT_measArray,
	JSSD_FLOAT_i_est,
	JSSD_FLOAT_ArrayControl,
	JSSD_FLOAT_Stribtorque,
	JSSD_FLOAT_Coulombtorque,
	JSSD_FLOAT_Viscotorque,
	JSSD_FLOAT_Rs,
	JSSD_FLOAT_PsiPM,
	JSSD_FLOAT_TrainInertia,
	JSSD_FLOAT_LoadInertia,
	JSSD_FLOAT_c_est,
	JSSD_FLOAT_d_est,
	JSSD_FLOAT_c_0,
	JSSD_FLOAT_MapCounter,
	JSSD_FLOAT_psidMap,
	JSSD_FLOAT_psiqMap,
	JSSD_FLOAT_idMap,
	JSSD_FLOAT_iqMap,
	JSSD_FLOAT_psi_array,
	JSSD_FLOAT_FluxTemp,
	JSSD_FLOAT_MapControl,
	JSSD_FLOAT_I_rated,
	JSSD_FLOAT_Wtemp,
	JSSD_FLOAT_FluxTempConst,
	JSSD_FLOAT_FluxTempError,
	JSSD_FLOAT_Ld_Online,
	JSSD_FLOAT_Lq_Online,
	JSSD_FLOAT_PsiPM_Online,
	JSSD_FLOAT_Rs_Online,
	JSSD_FLOAT_n_FluxPoints,
	JSSD_FLOAT_Ld,
	JSSD_FLOAT_Lq,
	JSSD_FLOAT_totalRotorInertia,
	JSSD_ENDMARKER
};


union SlowData {
   Xint32 i;
   Xfloat32 f;
};


extern float *js_ptr_arr[JSO_ENDMARKER];
extern float *js_ptr[4];	// channel ptr

extern union SlowData js_slowDataArray[JSSD_ENDMARKER];


int JavaScope_initalize(DS_Data* data);
void JavaScope_update(DS_Data* data);

void js_fetchData4CH();



#endif /* INCLUDE_JAVASCOPE_H_ */
