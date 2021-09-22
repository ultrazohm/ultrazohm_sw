/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel, Philipp Löhdefink
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#ifndef INCLUDE_JAVASCOPE_H_
#define INCLUDE_JAVASCOPE_H_


#include "ipc_ARM.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"

extern float zerovalue;

// Do not change the first (zero) and last (end) entries.
enum JS_OberservableData {
    JSO_ZEROVALUE=0,
	JSO_iu,
    JSO_iv,
    JSO_iw,
	JSO_iu_ref,
	JSO_iv_ref,
	JSO_iw_ref,
	JSO_au,
	JSO_av,
	JSO_aw,
	JSO_id_ref,
	JSO_iq_ref,
    JSO_Speed_rpm,
	JSO_Speed_ref_rpm,
	JSO_Theta_el,
	JSO_Theta_mech,
	JSO_U_ZK,
	JSO_Speed_rpm_filtered,
	JSO_ISR_ExecutionTime_us,
	JSO_ISR_Period_us,
	JSO_lifecheck,
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
   int i;
   float f;
};


extern float *js_ptr_arr[JSO_ENDMARKER];
extern float *js_ptr[4];	// channel ptr

extern union SlowData js_slowDataArray[JSSD_ENDMARKER];


int JavaScope_initalize(DS_Data* data);
void JavaScope_update(DS_Data* data);

void js_fetchData4CH();



#endif /* INCLUDE_JAVASCOPE_H_ */
