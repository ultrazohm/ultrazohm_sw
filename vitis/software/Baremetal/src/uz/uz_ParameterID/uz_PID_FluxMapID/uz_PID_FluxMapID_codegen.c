/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FluxMapID.c
 *
 * Code generated for Simulink model 'FluxMapID'.
 *
 * Model version                  : 2.134
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Nov 30 14:11:45 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
 */

#include "uz_PID_FluxMapID_codegen.h"
#if UZ_PARAMETERID_ACTIVE > 0U

/* Named constants for Chart: '<Root>/FluxMapID' */
#define IN_AMMcollectData              ((uint8_T)1U)
#define IN_AMMcompleted                ((uint8_T)2U)
#define IN_AMMcooling                  ((uint8_T)3U)
#define IN_AMMheating                  ((uint8_T)4U)
#define IN_AMMnewRef                   ((uint8_T)5U)
#define IN_AMMstate                    ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Waiting                     ((uint8_T)2U)
#define IN_initAMM                     ((uint8_T)6U)
#define IN_waitForCollectToFinish      ((uint8_T)7U)
#define IN_whatsNext                   ((uint8_T)8U)
#define NumBitsPerChar                 8U

/* Forward declaration for local functions */
static void initParams(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y, DW_FluxMapID_t *rtFluxMapID_DW);
static void RefreshDataRegister(DW_FluxMapID_t *rtFluxMapID_DW);
static real32_T identRes(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y, DW_FluxMapID_t *rtFluxMapID_DW);
static void enter_atomic_AMMnewRef(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y, DW_FluxMapID_t *rtFluxMapID_DW);
static void reset_FOC_output(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
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
static real_T rtGetNaN(void) {
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
static real32_T rtGetNaNF(void) {
	IEEESingle nanF = { { 0.0F } };

	nanF.wordL.wordLuint = 0xFFC00000U;
	return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize) {
	(void) (realSize);
	rtNaN = rtGetNaN();
	rtNaNF = rtGetNaNF();
	rtInf = rtGetInf();
	rtInfF = rtGetInfF();
	rtMinusInf = rtGetMinusInf();
	rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value) {
	return (boolean_T) ((value == rtInf || value == rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value) {
	return (boolean_T) (((value) == rtInfF || (value) == rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value) {
	boolean_T result = (boolean_T) 0;
	size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
	if (bitsPerReal == 32U) {
		result = rtIsNaNF((real32_T) value);
	} else {
		union {
			LittleEndianIEEEDouble bitVal;
			real_T fltVal;
		} tmpVal;

		tmpVal.fltVal = value;
		result = (boolean_T) ((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 && ((tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 || (tmpVal.bitVal.words.wordL != 0)));
	}

	return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value) {
	IEEESingle tmp;
	tmp.wordL.wordLreal = value;
	return (boolean_T) ((tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 && (tmp.wordL.wordLuint & 0x007FFFFF) != 0);
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void) {
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
static real32_T rtGetInfF(void) {
	IEEESingle infF;
	infF.wordL.wordLuint = 0x7F800000U;
	return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void) {
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
static real32_T rtGetMinusInfF(void) {
	IEEESingle minfF;
	minfF.wordL.wordLuint = 0xFF800000U;
	return minfF.wordL.wordLreal;
}

/*
 * Function for Chart: '<Root>/FluxMapID'
 * function initParams
 *  initialize variables
 */
static void initParams(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y, DW_FluxMapID_t *rtFluxMapID_DW)
{
	/* MATLAB Function 'initParams': '<S1>:651' */
	/* '<S1>:651:4' vd1_counter 		= single(0.0); */
	rtFluxMapID_DW->vd1_counter = 0.0F;

	/* '<S1>:651:5' id1_counter        	= single(0.0); */
	rtFluxMapID_DW->id1_counter = 0.0F;

	/* '<S1>:651:6' vd2_counter 		= single(0.0); */
	rtFluxMapID_DW->vd2_counter = 0.0F;

	/* '<S1>:651:7' id2_counter        	= single(0.0); */
	rtFluxMapID_DW->id2_counter = 0.0F;

	/* '<S1>:651:8' i_d_R_online        = single(0.0); */
	rtFluxMapID_DW->i_d_R_online = 0.0F;

	/* '<S1>:651:9' i_d_ref_AMM_loc     = single(0.0); */
	rtFluxMapID_DW->i_d_ref_AMM_loc = 0.0F;

	/* '<S1>:651:10' i_q_ref_AMM_loc     = single(0.0); */
	rtFluxMapID_DW->i_q_ref_AMM_loc = 0.0F;

	/* '<S1>:651:11' R_s_array           = single(zeros(50,1)); */
	memset(&rtFluxMapID_DW->R_s_array[0], 0, 50U * sizeof(real32_T));

	/* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
	 *  Inport: '<Root>/GlobalConfig'
	 */
  /* Outputs */
	/* '<S1>:651:13' FluxMapID_FOC_output.n_ref_FOC         	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.n_ref_FOC = 0.0F;

	/* '<S1>:651:14' FluxMapID_FOC_output.PRBS_out         	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.PRBS_out = 0.0F;

	/* '<S1>:651:15' FluxMapID_FOC_output.i_dq_ref.d      	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;

	/* '<S1>:651:16' FluxMapID_FOC_output.i_dq_ref.q       	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;

	/* '<S1>:651:17' FluxMapID_FOC_output.i_dq_ref.zero      = single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.zero = 0.0F;

	/* '<S1>:651:18' FluxMapID_FOC_output.enableFOC_speed   	= boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_speed = false;

	/* '<S1>:651:19' FluxMapID_FOC_output.enableFOC_current  = boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_current = false;

	/* '<S1>:651:20' FluxMapID_FOC_output.VibOn_out       	= boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.VibOn_out = false;

	/* '<S1>:651:21' FluxMapID_FOC_output.VibFreq_out      	= uint16(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.VibFreq_out = 0U;

	/* '<S1>:651:22' FluxMapID_FOC_output.VibAmp_out         = single(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.VibAmp_out = 0.0F;

	/* '<S1>:651:23' FluxMapID_FOC_output.resetIntegrator 	= boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.resetIntegrator = false;

	/* '<S1>:651:24' FluxMapID_FOC_output.Kp_id_out          = single(GlobalConfig.Kp_id); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_id_out = rtFluxMapID_U->GlobalConfig_out.Kp_id;

	/* '<S1>:651:25' FluxMapID_FOC_output.Kp_iq_out         	= single(GlobalConfig.Kp_iq); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_iq_out = rtFluxMapID_U->GlobalConfig_out.Kp_iq;

	/* '<S1>:651:26' FluxMapID_FOC_output.Kp_n_out         	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_n_out = 0.0F;

	/* '<S1>:651:27' FluxMapID_FOC_output.Ki_id_out         	= single(GlobalConfig.Ki_id); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_id_out = rtFluxMapID_U->GlobalConfig_out.Ki_id;

	/* '<S1>:651:28' FluxMapID_FOC_output.Ki_iq_out        	= single(GlobalConfig.Ki_iq); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_iq_out = rtFluxMapID_U->GlobalConfig_out.Ki_iq;

	/* '<S1>:651:29' FluxMapID_FOC_output.Ki_n_out          	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_n_out = 0.0F;

	/* '<S1>:651:30' FluxMapID_FOC_output.activeState        = uint16(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 0U;

	/* Outport: '<Root>/finishedFluxMapID' */
	/* '<S1>:651:31' finishedFluxMapID                       = boolean(0); */
	rtFluxMapID_Y->finishedFluxMapID = false;

	/* Outport: '<Root>/FluxMapID_output' incorporates:
	 *  Inport: '<Root>/FluxMapIDConfig'
	 */
	/* '<S1>:651:33' FluxMapID_output.R_s                    = single(FluxMapIDConfig.R_s_ref); */
	rtFluxMapID_Y->FluxMapID_output.R_s = rtFluxMapID_U->FluxMapIDConfig.R_s_ref;

	/* '<S1>:651:34' FluxMapID_output.WindingTemp            = single(FluxMapIDConfig.Temp_ref); */
	rtFluxMapID_Y->FluxMapID_output.WindingTemp = rtFluxMapID_U->FluxMapIDConfig.Temp_ref;
}

/*
 * Function for Chart: '<Root>/FluxMapID'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW_FluxMapID_t *rtFluxMapID_DW) {
	uint16_T k;

	/* MATLAB Function 'RefreshDataRegister': '<S1>:690' */
	/* '<S1>:690:3' m=length(R_s_array); */
	/* '<S1>:690:4' for k= uint16(0):uint16(m-2) */
	for (k = 0; k < 49; k++) {
		/* '<S1>:690:5' R_s_array(m-k)=R_s_array(m-(k+1)); */
		rtFluxMapID_DW->R_s_array[49 - k] = rtFluxMapID_DW->R_s_array[48 - k];
	}
}

/*
 * Function for Chart: '<Root>/FluxMapID'
 * function fun = identRes
 */
static real32_T identRes(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y, DW_FluxMapID_t *rtFluxMapID_DW)
{
	int32_T k;
	real32_T tmp;
	real32_T vd1_counter_tmp;
	uint32_T qY;

	/* Inport: '<Root>/GlobalConfig' */
	/* MATLAB Function 'identRes': '<S1>:669' */
	/* '<S1>:669:3' if(counter <= uint32(0.2/GlobalConfig.sampleTimeISR)) */
	vd1_counter_tmp = roundf(0.2F / rtFluxMapID_U->GlobalConfig_out.sampleTimeISR);
	if (vd1_counter_tmp < 4.2949673E+9F) {
		if (vd1_counter_tmp >= 0.0F) {
			qY = (uint32_T) vd1_counter_tmp;
		} else {
			qY = 0U;
		}
  } else {
		qY = MAX_uint32_T;
  }

	if (rtFluxMapID_DW->counter <= qY) {
		/* Inport: '<Root>/FluxMapIDConfig' */
		/* meas */
		/* '<S1>:669:4' i_d_R_online = single(-FluxMapIDConfig.identRAmp); */
		rtFluxMapID_DW->i_d_R_online = -rtFluxMapID_U->FluxMapIDConfig.identRAmp;

		/* Inport: '<Root>/GlobalConfig' */
		/* '<S1>:669:5' if(counter >= uint32(0.1/GlobalConfig.sampleTimeISR) && counter < uint32(0.2/GlobalConfig.sampleTimeISR)) */
		tmp = roundf(0.1F / rtFluxMapID_U->GlobalConfig_out.sampleTimeISR);
		if (tmp < 4.2949673E+9F) {
			if (tmp >= 0.0F) {
				qY = (uint32_T) tmp;
			} else {
				qY = 0U;
      }
		} else {
			qY = MAX_uint32_T;
		}

		if (rtFluxMapID_DW->counter >= qY) {
			if (vd1_counter_tmp < 4.2949673E+9F) {
				if (vd1_counter_tmp >= 0.0F) {
					qY = (uint32_T) vd1_counter_tmp;
				} else {
					qY = 0U;
				}
			} else {
				qY = MAX_uint32_T;
      }

			if (rtFluxMapID_DW->counter < qY) {
				/* Inport: '<Root>/ActualValues' */
				/* '<S1>:669:6' vd1_counter = vd1_counter + ActualValues.v_dq.d; */
				rtFluxMapID_DW->vd1_counter += rtFluxMapID_U->ActualValues.v_dq.d;

				/* '<S1>:669:7' id1_counter = id1_counter + ActualValues.i_dq.d; */
				rtFluxMapID_DW->id1_counter += rtFluxMapID_U->ActualValues.i_dq.d;
      }
		}
	}

	/* '<S1>:669:11' if(counter > uint32(0.2/GlobalConfig.sampleTimeISR) && counter <= uint32(0.4/GlobalConfig.sampleTimeISR)) */
	if (vd1_counter_tmp < 4.2949673E+9F) {
		if (vd1_counter_tmp >= 0.0F) {
			qY = (uint32_T) vd1_counter_tmp;
		} else {
			qY = 0U;
		}
	} else {
		qY = MAX_uint32_T;
	}

	if (rtFluxMapID_DW->counter > qY) {
		/* Inport: '<Root>/GlobalConfig' */
		vd1_counter_tmp = roundf(0.4F / rtFluxMapID_U->GlobalConfig_out.sampleTimeISR);
		if (vd1_counter_tmp < 4.2949673E+9F) {
			if (vd1_counter_tmp >= 0.0F) {
				qY = (uint32_T) vd1_counter_tmp;
      } else {
				qY = 0U;
      }
    } else {
			qY = MAX_uint32_T;
    }

		if (rtFluxMapID_DW->counter <= qY) {
			/* Inport: '<Root>/FluxMapIDConfig' */
			/* '<S1>:669:12' i_d_R_online = single(FluxMapIDConfig.identRAmp); */
			rtFluxMapID_DW->i_d_R_online = rtFluxMapID_U->FluxMapIDConfig.identRAmp;

			/* Inport: '<Root>/GlobalConfig' */
			/* '<S1>:669:13' if(counter >= uint32(0.3/GlobalConfig.sampleTimeISR) && counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
			tmp = roundf(0.3F / rtFluxMapID_U->GlobalConfig_out.sampleTimeISR);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
					qY = (uint32_T) tmp;
        } else {
					qY = 0U;
        }
      } else {
				qY = MAX_uint32_T;
      }

			if (rtFluxMapID_DW->counter >= qY) {
				if (vd1_counter_tmp < 4.2949673E+9F) {
					if (vd1_counter_tmp >= 0.0F) {
						qY = (uint32_T) vd1_counter_tmp;
					} else {
						qY = 0U;
					}
        } else {
					qY = MAX_uint32_T;
        }

				if (rtFluxMapID_DW->counter < qY) {
					/* Inport: '<Root>/ActualValues' */
					/* '<S1>:669:14' vd2_counter = vd2_counter + ActualValues.v_dq.d; */
					rtFluxMapID_DW->vd2_counter += rtFluxMapID_U->ActualValues.v_dq.d;

					/* '<S1>:669:15' id2_counter = id2_counter + ActualValues.i_dq.d; */
					rtFluxMapID_DW->id2_counter += rtFluxMapID_U->ActualValues.i_dq.d;
        }
      }
    }
  }

  /* Inport: '<Root>/GlobalConfig' */
	/* '<S1>:669:19' if(counter == uint32(0.4/GlobalConfig.sampleTimeISR + 1) ) */
	vd1_counter_tmp = roundf(0.4F / rtFluxMapID_U->GlobalConfig_out.sampleTimeISR + 1.0F);
	if (vd1_counter_tmp < 4.2949673E+9F) {
		if (vd1_counter_tmp >= 0.0F) {
			qY = (uint32_T) vd1_counter_tmp;
		} else {
			qY = 0U;
		}
  } else {
		qY = MAX_uint32_T;
  }

	if (rtFluxMapID_DW->counter == qY) {
		/* Inport: '<Root>/FluxMapIDConfig' */
		/* '<S1>:669:20' i_d_R_online = single(-FluxMapIDConfig.identRAmp); */
		rtFluxMapID_DW->i_d_R_online = -rtFluxMapID_U->FluxMapIDConfig.identRAmp;

		/* Inport: '<Root>/GlobalConfig' */
		/* '<S1>:669:21' vd1_counter=vd1_counter/(0.1/GlobalConfig.sampleTimeISR); */
		vd1_counter_tmp = 0.1F / rtFluxMapID_U->GlobalConfig_out.sampleTimeISR;
		rtFluxMapID_DW->vd1_counter /= vd1_counter_tmp;

		/* '<S1>:669:22' id1_counter=id1_counter/(0.1/GlobalConfig.sampleTimeISR); */
		rtFluxMapID_DW->id1_counter /= vd1_counter_tmp;

		/* '<S1>:669:23' vd2_counter=vd2_counter/(0.1/GlobalConfig.sampleTimeISR); */
		rtFluxMapID_DW->vd2_counter /= vd1_counter_tmp;

		/* '<S1>:669:24' id2_counter=id2_counter/(0.1/GlobalConfig.sampleTimeISR); */
		rtFluxMapID_DW->id2_counter /= vd1_counter_tmp;

		/* '<S1>:669:25' R_s_array(1,1) = single((vd2_counter-vd1_counter)/(id2_counter-id1_counter)); */
		rtFluxMapID_DW->R_s_array[0] = (rtFluxMapID_DW->vd2_counter - rtFluxMapID_DW->vd1_counter) / (rtFluxMapID_DW->id2_counter - rtFluxMapID_DW->id1_counter);

		/* '<S1>:669:26' RefreshDataRegister; */
		RefreshDataRegister(rtFluxMapID_DW);

		/* '<S1>:669:27' FluxMapID_output.R_s = mean(R_s_array); */
		vd1_counter_tmp = rtFluxMapID_DW->R_s_array[0];
		for (k = 0; k < 49; k++) {
			vd1_counter_tmp += rtFluxMapID_DW->R_s_array[k + 1];
    }

		/* Outport: '<Root>/FluxMapID_output' */
		rtFluxMapID_Y->FluxMapID_output.R_s = vd1_counter_tmp / 50.0F;

		/* '<S1>:669:28' counter = uint32(1); */
		rtFluxMapID_DW->counter = 1U;
  }

	/* '<S1>:669:31' counter = counter + 1; */
	qY = rtFluxMapID_DW->counter + /*MW:OvSatOk*/1U;
	if (rtFluxMapID_DW->counter + 1U < rtFluxMapID_DW->counter) {
		qY = MAX_uint32_T;
  }

	rtFluxMapID_DW->counter = qY;

	/* Outport: '<Root>/FluxMapID_output' */
	/* '<S1>:669:32' fun = single(FluxMapID_output.R_s); */
	return rtFluxMapID_Y->FluxMapID_output.R_s;
}

/* Function for Chart: '<Root>/FluxMapID' */
static void enter_atomic_AMMnewRef(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y, DW_FluxMapID_t *rtFluxMapID_DW)
{
	real32_T q;
	real32_T x;
	real32_T z_tmp;
	uint32_T qY;
	boolean_T rEQ0;

	/* Outport: '<Root>/FluxMapID_FOC_output' */
	/* Entry 'AMMnewRef': '<S1>:583' */
	/* '<S1>:583:4' FluxMapID_FOC_output.activeState = uint16(402); */
	rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 402U;

	/* Inport: '<Root>/FluxMapIDConfig' */
	/* '<S1>:583:5' if((FluxMapIDConfig.IDstart + single(AMMn) * FluxMapIDConfig.IDstepsize) <= FluxMapIDConfig.IDstop) */
	z_tmp = (real32_T) rtFluxMapID_DW->AMMn * rtFluxMapID_U->FluxMapIDConfig.IDstepsize + rtFluxMapID_U->FluxMapIDConfig.IDstart;
	if (z_tmp <= rtFluxMapID_U->FluxMapIDConfig.IDstop) {
		/* '<S1>:583:6' i_d_ref_AMM = single(FluxMapIDConfig.IDstart + single(AMMn) * FluxMapIDConfig.IDstepsize); */
		rtFluxMapID_DW->i_d_ref_AMM = z_tmp;

		/* '<S1>:583:7' if(mod(single(AMMn),((abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart))/FluxMapIDConfig.IDstepsize)+1) == 0) */
		z_tmp = fabsf(rtFluxMapID_U->FluxMapIDConfig.IDstop - rtFluxMapID_U->FluxMapIDConfig.IDstart) / rtFluxMapID_U->FluxMapIDConfig.IDstepsize;
		x = (real32_T) rtFluxMapID_DW->AMMn;
		if (z_tmp + 1.0F == 0.0F) {
			if (rtFluxMapID_DW->AMMn == 0.0F) {
				x = z_tmp + 1.0F;
			}
		} else if (rtIsNaNF(z_tmp + 1.0F)) {
			x = (rtNaNF);
		} else if (rtFluxMapID_DW->AMMn == 0.0F) {
			x = 0.0F / (z_tmp + 1.0F);
		} else if (rtIsInfF(z_tmp + 1.0F)) {
			if (z_tmp + 1.0F < 0.0F) {
				x = z_tmp + 1.0F;
      }
		} else {
			x = fmodf((real32_T) rtFluxMapID_DW->AMMn, z_tmp + 1.0F);
			rEQ0 = (x == 0.0F);
			if ((!rEQ0) && (z_tmp + 1.0F > floorf(z_tmp + 1.0F))) {
				q = fabsf((real32_T) rtFluxMapID_DW->AMMn / (z_tmp + 1.0F));
				rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
      }

			if (rEQ0) {
				x = (z_tmp + 1.0F) * 0.0F;
			} else if (z_tmp + 1.0F < 0.0F) {
				x += z_tmp + 1.0F;
      }
    }

		if (x == 0.0F) {
			/* '<S1>:583:8' if((FluxMapIDConfig.IQstart + single(AMMj) * FluxMapIDConfig.IQstepsize) <= FluxMapIDConfig.IQstop) */
			z_tmp = (real32_T) rtFluxMapID_DW->AMMj * rtFluxMapID_U->FluxMapIDConfig.IQstepsize + rtFluxMapID_U->FluxMapIDConfig.IQstart;
			if (z_tmp <= rtFluxMapID_U->FluxMapIDConfig.IQstop) {
				/* '<S1>:583:9' i_q_ref_AMM = single(FluxMapIDConfig.IQstart + single(AMMj) * FluxMapIDConfig.IQstepsize); */
				rtFluxMapID_DW->i_q_ref_AMM = z_tmp;

				/* '<S1>:583:10' AMMj = AMMj + 1; */
				qY = rtFluxMapID_DW->AMMj + /*MW:OvSatOk*/1U;
				if (rtFluxMapID_DW->AMMj + 1U < rtFluxMapID_DW->AMMj) {
          qY = MAX_uint32_T;
        }

				rtFluxMapID_DW->AMMj = qY;
			} else {
				/* '<S1>:583:11' else */
				/* '<S1>:583:12' i_q_ref_AMM = single(0.0); */
				rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

				/* '<S1>:583:13' i_d_ref_AMM = single(0.0); */
				rtFluxMapID_DW->i_d_ref_AMM = 0.0F;
      }
    }
  }

	/* End of Inport: '<Root>/FluxMapIDConfig' */
}

/*
 * Function for Chart: '<Root>/FluxMapID'
 * function reset_FOC_output
 * Outputs
 */
static void reset_FOC_output(ExtU_FluxMapID_t *rtFluxMapID_U, ExtY_FluxMapID_t *rtFluxMapID_Y) {
	/* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
	 *  Inport: '<Root>/GlobalConfig'
	 */
	/* MATLAB Function 'reset_FOC_output': '<S1>:696' */
	/* '<S1>:696:3' FluxMapID_FOC_output.n_ref_FOC         	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.n_ref_FOC = 0.0F;

	/* '<S1>:696:4' FluxMapID_FOC_output.PRBS_out         	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.PRBS_out = 0.0F;

	/* '<S1>:696:5' FluxMapID_FOC_output.i_dq_ref.d      	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;

	/* '<S1>:696:6' FluxMapID_FOC_output.i_dq_ref.q       	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;

	/* '<S1>:696:7' FluxMapID_FOC_output.i_dq_ref.zero      = single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.zero = 0.0F;

	/* '<S1>:696:8' FluxMapID_FOC_output.enableFOC_speed   	= boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_speed = false;

	/* '<S1>:696:9' FluxMapID_FOC_output.enableFOC_current  = boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_current = false;

	/* '<S1>:696:10' FluxMapID_FOC_output.VibOn_out       	= boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.VibOn_out = false;

	/* '<S1>:696:11' FluxMapID_FOC_output.VibFreq_out      	= uint16(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.VibFreq_out = 0U;

	/* '<S1>:696:12' FluxMapID_FOC_output.VibAmp_out         = single(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.VibAmp_out = 0.0F;

	/* '<S1>:696:13' FluxMapID_FOC_output.resetIntegrator 	= boolean(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.resetIntegrator = false;

	/* '<S1>:696:14' FluxMapID_FOC_output.Kp_id_out          = single(GlobalConfig.Kp_id); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_id_out = rtFluxMapID_U->GlobalConfig_out.Kp_id;

	/* '<S1>:696:15' FluxMapID_FOC_output.Kp_iq_out         	= single(GlobalConfig.Kp_iq); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_iq_out = rtFluxMapID_U->GlobalConfig_out.Kp_iq;

	/* '<S1>:696:16' FluxMapID_FOC_output.Kp_n_out         	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_n_out = 0.0F;

	/* '<S1>:696:17' FluxMapID_FOC_output.Ki_id_out         	= single(GlobalConfig.Ki_id); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_id_out = rtFluxMapID_U->GlobalConfig_out.Ki_id;

	/* '<S1>:696:18' FluxMapID_FOC_output.Ki_iq_out        	= single(GlobalConfig.Ki_iq); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_iq_out = rtFluxMapID_U->GlobalConfig_out.Ki_iq;

	/* '<S1>:696:19' FluxMapID_FOC_output.Ki_n_out          	= single(0.0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_n_out = 0.0F;

	/* '<S1>:696:20' FluxMapID_FOC_output.activeState        = uint16(0); */
	rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 0U;
}

/* Model step function */
void FluxMapID_step(RT_MODEL_FluxMapID_t * const rtFluxMapID_M)
{
	DW_FluxMapID_t *rtFluxMapID_DW = rtFluxMapID_M->dwork;
	ExtU_FluxMapID_t *rtFluxMapID_U = (ExtU_FluxMapID_t *) rtFluxMapID_M->inputs;
	ExtY_FluxMapID_t *rtFluxMapID_Y = (ExtY_FluxMapID_t *) rtFluxMapID_M->outputs;
	uint32_T qY;

	/* Chart: '<Root>/FluxMapID' incorporates:
	 *  Inport: '<Root>/ControlFlags'
	 *  Inport: '<Root>/FluxMapIDConfig'
	 *  Inport: '<Root>/GlobalConfig'
	 *  Outport: '<Root>/FluxMapID_FOC_output'
	 *  Outport: '<Root>/FluxMapID_output'
	 */
	if (rtFluxMapID_DW->temporalCounter_i1 < MAX_uint32_T) {
		rtFluxMapID_DW->temporalCounter_i1++;
	}

	/* Gateway: FluxMapID */
	/* During: FluxMapID */
	if (rtFluxMapID_DW->is_active_c16_FluxMapID == 0U) {
		/* Entry: FluxMapID */
		rtFluxMapID_DW->is_active_c16_FluxMapID = 1U;

		/* Entry Internal: FluxMapID */
		/* Transition: '<S1>:597' */
		rtFluxMapID_DW->is_c16_FluxMapID = IN_Waiting;

		/* Entry 'Waiting': '<S1>:652' */
		/* wait for activation of */
		/* FluxMapID */
		/* donothing */
	} else if (rtFluxMapID_DW->is_c16_FluxMapID == IN_AMMstate) {
		/* During 'AMMstate': '<S1>:590' */
		/* '<S1>:667:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.FluxMapID==0.... */
		/* '<S1>:667:2' || FluxMapIDConfig.start_FM_ID==0 || GlobalConfig.enableParameterID==0; */
		if (rtFluxMapID_U->GlobalConfig_out.Reset || (!rtFluxMapID_U->GlobalConfig_out.FluxMapID) || (!rtFluxMapID_U->FluxMapIDConfig.start_FM_ID)
		                || (!rtFluxMapID_U->GlobalConfig_out.enableParameterID)) {
			/* Outport: '<Root>/enteredFluxMapID' */
			/* Transition: '<S1>:667' */
			/* '<S1>:667:3' enteredFluxMapID=boolean(0); */
			rtFluxMapID_Y->enteredFluxMapID = false;

			/* '<S1>:667:3' initParams; */
			initParams(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);

			/* Exit Internal 'AMMstate': '<S1>:590' */
			switch (rtFluxMapID_DW->is_AMMstate) {
			case IN_AMMcompleted:
				/* Outport: '<Root>/finishedFluxMapID' */
				/* Exit 'AMMcompleted': '<S1>:592' */
				/* '<S1>:592:14' finishedFluxMapID=boolean(1); */
				rtFluxMapID_Y->finishedFluxMapID = true;

				/* Outport: '<Root>/enteredFluxMapID' */
				/* '<S1>:592:15' enteredFluxMapID = boolean(0); */
				rtFluxMapID_Y->enteredFluxMapID = false;

				/* '<S1>:592:16' reset_FOC_output */
				reset_FOC_output(rtFluxMapID_U, rtFluxMapID_Y);
				rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;
				break;

			case IN_AMMcooling:
				/* Exit 'AMMcooling': '<S1>:593' */
				/* '<S1>:593:8' i_d_ref_AMM = i_d_ref_AMM_loc; */
				/* '<S1>:593:9' i_q_ref_AMM = i_q_ref_AMM_loc; */
				rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;
				break;

			case IN_AMMheating:
				/* Exit 'AMMheating': '<S1>:608' */
				/* '<S1>:608:8' i_d_ref_AMM = i_d_ref_AMM_loc; */
				/* '<S1>:608:9' i_q_ref_AMM = i_q_ref_AMM_loc; */
				rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;
				break;

			case IN_waitForCollectToFinish:
				/* Exit 'waitForCollectToFinish': '<S1>:601' */
				rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;
				break;

			default:
				rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;
				break;
			}

			/* Exit 'AMMstate': '<S1>:590' */
			/* '<S1>:590:33' counter = uint32(1); */
			rtFluxMapID_DW->counter = 1U;

			/* '<S1>:590:34' AMMcounter = uint32(0); */
			/* '<S1>:590:35' AMMn = uint32(0); */
			rtFluxMapID_DW->AMMn = 0U;

			/* '<S1>:590:36' AMMj = uint32(0); */
			rtFluxMapID_DW->AMMj = 0U;

			/* '<S1>:590:37' repetitionCounter = uint32(0); */
			rtFluxMapID_DW->repetitionCounter = 0U;

			/* '<S1>:590:38' i_q_ref_AMM = single(0.0); */
			rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

			/* '<S1>:590:39' i_d_ref_AMM = single(0.0); */
			rtFluxMapID_DW->i_d_ref_AMM = 0.0F;
			rtFluxMapID_DW->is_c16_FluxMapID = IN_Waiting;

			/* Entry 'Waiting': '<S1>:652' */
			/* wait for activation of */
			/* FluxMapID */
			/* donothing */
    } else {
			/* '<S1>:590:16' FluxMapID_FOC_output.i_dq_ref.d=i_d_R_online+i_d_ref_AMM; */
			rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.d = rtFluxMapID_DW->i_d_R_online + rtFluxMapID_DW->i_d_ref_AMM;

			/* '<S1>:590:17' FluxMapID_FOC_output.i_dq_ref.q=i_q_ref_AMM; */
			rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.q = rtFluxMapID_DW->i_q_ref_AMM;

			/* '<S1>:590:18' if(FluxMapIDConfig.identR == 1) */
			if (rtFluxMapID_U->FluxMapIDConfig.identR) {
				/* '<S1>:590:19' if(FluxMapID_FOC_output.activeState ~= 403) */
				if (rtFluxMapID_Y->FluxMapID_FOC_output.activeState != 403) {
					/* '<S1>:590:20' FluxMapID_output.R_s = identRes; */
					rtFluxMapID_Y->FluxMapID_output.R_s = identRes(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);
				}

				/* '<S1>:590:22' if(FluxMapIDConfig.R_s_ref ~= 0.0 && FluxMapIDConfig.Temp_ref ~= 0.0) */
				if ((rtFluxMapID_U->FluxMapIDConfig.R_s_ref != 0.0F) && (rtFluxMapID_U->FluxMapIDConfig.Temp_ref != 0.0F)) {
					/* '<S1>:590:23' FluxMapID_output.WindingTemp = ((FluxMapID_output.R_s/FluxMapIDConfig.R_s_ref)-1).... */
					/* '<S1>:590:24'                 *254.453+FluxMapIDConfig.Temp_ref; */
					rtFluxMapID_Y->FluxMapID_output.WindingTemp = (rtFluxMapID_Y->FluxMapID_output.R_s / rtFluxMapID_U->FluxMapIDConfig.R_s_ref - 1.0F) * 254.453F
					                + rtFluxMapID_U->FluxMapIDConfig.Temp_ref;

					/* . */
				}
			}

			/* '<S1>:590:27' if(FluxMapIDConfig.identR == 0) */
			if (!rtFluxMapID_U->FluxMapIDConfig.identR) {
				/* '<S1>:590:28' i_d_R_online = single(0.0); */
				rtFluxMapID_DW->i_d_R_online = 0.0F;

				/* '<S1>:590:29' counter = uint32(1); */
				rtFluxMapID_DW->counter = 1U;

				/* '<S1>:590:30' FluxMapID_output.WindingTemp= single(65); */
				rtFluxMapID_Y->FluxMapID_output.WindingTemp = 65.0F;
			}

			switch (rtFluxMapID_DW->is_AMMstate) {
			case IN_AMMcollectData:
				/* During 'AMMcollectData': '<S1>:607' */
				/* '<S1>:595:1' sf_internal_predicateOutput = after((FluxMapIDConfig.AMMsampleTime),sec); */
				if (rtFluxMapID_DW->temporalCounter_i1 >= (uint32_T) ceil(rtFluxMapID_U->FluxMapIDConfig.AMMsampleTime / 0.0001 - 1.0E-12)) {
					/* Transition: '<S1>:595' */
					rtFluxMapID_DW->is_AMMstate = IN_waitForCollectToFinish;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;

					/* Entry 'waitForCollectToFinish': '<S1>:601' */
					/* '<S1>:601:3' FluxMapID_FOC_output.activeState = uint16(404); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 404U;
				}
				break;

			case IN_AMMcompleted:
				/* During 'AMMcompleted': '<S1>:592' */
				/* '<S1>:674:1' sf_internal_predicateOutput = after(0.1,sec); */
				if (rtFluxMapID_DW->temporalCounter_i1 >= 1000U) {
					/* Outport: '<Root>/finishedFluxMapID' */
					/* Transition: '<S1>:674' */
					/* Exit 'AMMcompleted': '<S1>:592' */
					/* '<S1>:592:14' finishedFluxMapID=boolean(1); */
					rtFluxMapID_Y->finishedFluxMapID = true;

					/* Outport: '<Root>/enteredFluxMapID' */
					/* '<S1>:592:15' enteredFluxMapID = boolean(0); */
					rtFluxMapID_Y->enteredFluxMapID = false;

					/* '<S1>:592:16' reset_FOC_output */
					reset_FOC_output(rtFluxMapID_U, rtFluxMapID_Y);
					rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;

					/* Exit 'AMMstate': '<S1>:590' */
					/* '<S1>:590:33' counter = uint32(1); */
					rtFluxMapID_DW->counter = 1U;

					/* '<S1>:590:34' AMMcounter = uint32(0); */
					/* '<S1>:590:35' AMMn = uint32(0); */
					rtFluxMapID_DW->AMMn = 0U;

					/* '<S1>:590:36' AMMj = uint32(0); */
					rtFluxMapID_DW->AMMj = 0U;

					/* '<S1>:590:37' repetitionCounter = uint32(0); */
					rtFluxMapID_DW->repetitionCounter = 0U;

					/* '<S1>:590:38' i_q_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

					/* '<S1>:590:39' i_d_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_d_ref_AMM = 0.0F;
					rtFluxMapID_DW->is_c16_FluxMapID = IN_Waiting;

					/* Entry 'Waiting': '<S1>:652' */
					/* wait for activation of */
					/* FluxMapID */
					/* donothing */
				} else {
					/* '<S1>:592:12' FluxMapID_FOC_output.resetIntegrator=boolean(1); */
					rtFluxMapID_Y->FluxMapID_FOC_output.resetIntegrator = true;
        }
				break;

			case IN_AMMcooling:
				/* During 'AMMcooling': '<S1>:593' */
				/* '<S1>:604:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp <= 60; */
				if (rtFluxMapID_Y->FluxMapID_output.WindingTemp <= 60.0F) {
					/* Transition: '<S1>:604' */
					/* Exit 'AMMcooling': '<S1>:593' */
					/* '<S1>:593:8' i_d_ref_AMM = i_d_ref_AMM_loc; */
					rtFluxMapID_DW->i_d_ref_AMM = rtFluxMapID_DW->i_d_ref_AMM_loc;

					/* '<S1>:593:9' i_q_ref_AMM = i_q_ref_AMM_loc; */
					rtFluxMapID_DW->i_q_ref_AMM = rtFluxMapID_DW->i_q_ref_AMM_loc;
					rtFluxMapID_DW->is_AMMstate = IN_AMMnewRef;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;
					enter_atomic_AMMnewRef(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);
				}
				break;

			case IN_AMMheating:
				/* During 'AMMheating': '<S1>:608' */
				/* '<S1>:594:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >= 60; */
				if (rtFluxMapID_Y->FluxMapID_output.WindingTemp >= 60.0F) {
					/* Transition: '<S1>:594' */
					/* Exit 'AMMheating': '<S1>:608' */
					/* '<S1>:608:8' i_d_ref_AMM = i_d_ref_AMM_loc; */
					rtFluxMapID_DW->i_d_ref_AMM = rtFluxMapID_DW->i_d_ref_AMM_loc;

					/* '<S1>:608:9' i_q_ref_AMM = i_q_ref_AMM_loc; */
					rtFluxMapID_DW->i_q_ref_AMM = rtFluxMapID_DW->i_q_ref_AMM_loc;
					rtFluxMapID_DW->is_AMMstate = IN_AMMnewRef;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;
					enter_atomic_AMMnewRef(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);
        }
				break;

			case IN_AMMnewRef:
				/* During 'AMMnewRef': '<S1>:583' */
				/* '<S1>:581:1' sf_internal_predicateOutput = after(3.0,sec); */
				if (rtFluxMapID_DW->temporalCounter_i1 >= 30000U) {
					/* Transition: '<S1>:581' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMcollectData;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;

					/* Entry 'AMMcollectData': '<S1>:607' */
					/* '<S1>:607:4' FluxMapID_FOC_output.activeState = uint16(403); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 403U;

					/* '<S1>:607:5' repetitionCounter = repetitionCounter + 1; */
					qY = rtFluxMapID_DW->repetitionCounter + /*MW:OvSatOk*/1U;
					if (rtFluxMapID_DW->repetitionCounter + 1U < rtFluxMapID_DW->repetitionCounter) {
						qY = MAX_uint32_T;
					}

					rtFluxMapID_DW->repetitionCounter = qY;

					/* '<S1>:607:6' i_d_R_online = single(0.0); */
					rtFluxMapID_DW->i_d_R_online = 0.0F;

					/* '<S1>:607:7' if(AMMn >= (NumberOfIDpoints-1)) */
					if ((real_T) rtFluxMapID_DW->AMMn >= rtFluxMapID_DW->NumberOfIDpoints - 1.0F) {
						/* '<S1>:607:8' AMMn = uint32(0); */
						rtFluxMapID_DW->AMMn = 0U;
					} else {
						/* '<S1>:607:9' else */
						/* '<S1>:607:10' AMMn = AMMn + 1; */
						qY = rtFluxMapID_DW->AMMn + /*MW:OvSatOk*/1U;
						if (rtFluxMapID_DW->AMMn + 1U < rtFluxMapID_DW->AMMn) {
							qY = MAX_uint32_T;
						}

						rtFluxMapID_DW->AMMn = qY;
					}
				}
				break;

			case IN_initAMM:
				/* During 'initAMM': '<S1>:600' */
				/* '<S1>:603:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > 70; */
				if (rtFluxMapID_Y->FluxMapID_output.WindingTemp > 70.0F) {
					/* Transition: '<S1>:603' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMcooling;

					/* Entry 'AMMcooling': '<S1>:593' */
					/* '<S1>:593:4' FluxMapID_FOC_output.activeState = uint16(410); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 410U;

					/* '<S1>:593:5' i_q_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

					/* '<S1>:593:6' i_d_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_d_ref_AMM = 0.0F;

					/* '<S1>:596:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < 60; */
				} else if (rtFluxMapID_Y->FluxMapID_output.WindingTemp < 60.0F) {
					/* Transition: '<S1>:596' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMheating;

					/* Entry 'AMMheating': '<S1>:608' */
					/* '<S1>:608:4' FluxMapID_FOC_output.activeState = uint16(420); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 420U;

					/* '<S1>:608:5' i_q_ref_AMM = single(FluxMapIDConfig.IQstop); */
					rtFluxMapID_DW->i_q_ref_AMM = rtFluxMapID_U->FluxMapIDConfig.IQstop;

					/* '<S1>:608:6' i_d_ref_AMM = single(FluxMapIDConfig.IDstart); */
					rtFluxMapID_DW->i_d_ref_AMM = rtFluxMapID_U->FluxMapIDConfig.IDstart;

					/* '<S1>:584:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=60 && .... */
					/* '<S1>:584:2' FluxMapID_output.WindingTemp <=70; */
					/* . */
				} else if ((rtFluxMapID_Y->FluxMapID_output.WindingTemp >= 60.0F) && (rtFluxMapID_Y->FluxMapID_output.WindingTemp <= 70.0F)) {
					/* Transition: '<S1>:584' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMnewRef;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;
					enter_atomic_AMMnewRef(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);
				}
				break;

			case IN_waitForCollectToFinish:
				/* During 'waitForCollectToFinish': '<S1>:601' */
				/* '<S1>:606:1' sf_internal_predicateOutput = after(3.0,sec); */
				if (rtFluxMapID_DW->temporalCounter_i1 >= 30000U) {
					/* Transition: '<S1>:606' */
					/* Exit 'waitForCollectToFinish': '<S1>:601' */
					rtFluxMapID_DW->is_AMMstate = IN_whatsNext;

					/* Entry 'whatsNext': '<S1>:602' */
					/* '<S1>:602:3' i_d_ref_AMM_loc = i_d_ref_AMM; */
					rtFluxMapID_DW->i_d_ref_AMM_loc = rtFluxMapID_DW->i_d_ref_AMM;

					/* '<S1>:602:4' i_q_ref_AMM_loc = i_q_ref_AMM; */
					rtFluxMapID_DW->i_q_ref_AMM_loc = rtFluxMapID_DW->i_q_ref_AMM;
				}
				break;

			default:
				/* During 'whatsNext': '<S1>:602' */
				/* '<S1>:599:1' sf_internal_predicateOutput = repetitionCounter >= NumberOfPoints; */
				if ((real_T) rtFluxMapID_DW->repetitionCounter >= rtFluxMapID_DW->NumberOfPoints) {
					/* Transition: '<S1>:599' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMcompleted;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;

					/* Entry 'AMMcompleted': '<S1>:592' */
					/* '<S1>:592:4' FluxMapID_FOC_output.activeState = uint16(450); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 450U;

					/* '<S1>:592:5' AMMcounter = uint32(0); */
					/* '<S1>:592:6' AMMn = uint32(0); */
					rtFluxMapID_DW->AMMn = 0U;

					/* '<S1>:592:7' AMMj = uint32(0); */
					rtFluxMapID_DW->AMMj = 0U;

					/* '<S1>:592:8' repetitionCounter = uint32(0); */
					rtFluxMapID_DW->repetitionCounter = 0U;

					/* '<S1>:592:9' i_q_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

					/* '<S1>:592:10' i_d_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_d_ref_AMM = 0.0F;

					/* '<S1>:582:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > 70; */
				} else if (rtFluxMapID_Y->FluxMapID_output.WindingTemp > 70.0F) {
					/* Transition: '<S1>:582' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMcooling;

					/* Entry 'AMMcooling': '<S1>:593' */
					/* '<S1>:593:4' FluxMapID_FOC_output.activeState = uint16(410); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 410U;

					/* '<S1>:593:5' i_q_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

					/* '<S1>:593:6' i_d_ref_AMM = single(0.0); */
					rtFluxMapID_DW->i_d_ref_AMM = 0.0F;

					/* '<S1>:598:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < 60; */
				} else if (rtFluxMapID_Y->FluxMapID_output.WindingTemp < 60.0F) {
					/* Transition: '<S1>:598' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMheating;

					/* Entry 'AMMheating': '<S1>:608' */
					/* '<S1>:608:4' FluxMapID_FOC_output.activeState = uint16(420); */
					rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 420U;

					/* '<S1>:608:5' i_q_ref_AMM = single(FluxMapIDConfig.IQstop); */
					rtFluxMapID_DW->i_q_ref_AMM = rtFluxMapID_U->FluxMapIDConfig.IQstop;

					/* '<S1>:608:6' i_d_ref_AMM = single(FluxMapIDConfig.IDstart); */
					rtFluxMapID_DW->i_d_ref_AMM = rtFluxMapID_U->FluxMapIDConfig.IDstart;

					/* '<S1>:605:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=60 && FluxMapID_output.WindingTemp <= 70; */
				} else if ((rtFluxMapID_Y->FluxMapID_output.WindingTemp >= 60.0F) && (rtFluxMapID_Y->FluxMapID_output.WindingTemp <= 70.0F)) {
					/* Transition: '<S1>:605' */
					rtFluxMapID_DW->is_AMMstate = IN_AMMnewRef;
					rtFluxMapID_DW->temporalCounter_i1 = 0U;
					enter_atomic_AMMnewRef(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);
				}
				break;
			}
		}

		/* During 'Waiting': '<S1>:652' */
		/* '<S1>:656:1' sf_internal_predicateOutput = ControlFlags.startFluxMapID==1 && .... */
		/* '<S1>:656:2' GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1 && .... */
		/* '<S1>:656:3' FluxMapIDConfig.start_FM_ID==1; */
		/* . */
    /* . */
	} else if (rtFluxMapID_U->ControlFlags.startFluxMapID && (!rtFluxMapID_U->GlobalConfig_out.Reset) && rtFluxMapID_U->GlobalConfig_out.ACCEPT && rtFluxMapID_U->FluxMapIDConfig.start_FM_ID) {
		/* Transition: '<S1>:656' */
		rtFluxMapID_DW->is_c16_FluxMapID = IN_AMMstate;

		/* Entry 'AMMstate': '<S1>:590' */
		/* '<S1>:590:4' initParams; */
		initParams(rtFluxMapID_U, rtFluxMapID_Y, rtFluxMapID_DW);

		/* Outport: '<Root>/enteredFluxMapID' */
		/* '<S1>:590:5' enteredFluxMapID = boolean(1); */
		rtFluxMapID_Y->enteredFluxMapID = true;

		/* '<S1>:590:6' FluxMapID_FOC_output.enableFOC_current=boolean(1); */
		rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_current = true;

		/* '<S1>:590:7' FluxMapID_FOC_output.activeState = uint16(400); */
		/* '<S1>:590:8' counter = uint32(1); */
		rtFluxMapID_DW->counter = 1U;

		/* '<S1>:590:9' AMMcounter = uint32(0); */
		/* '<S1>:590:10' AMMn = uint32(0); */
		rtFluxMapID_DW->AMMn = 0U;

		/* '<S1>:590:11' AMMj = uint32(0); */
		rtFluxMapID_DW->AMMj = 0U;

		/* '<S1>:590:12' repetitionCounter = uint32(0); */
		/* '<S1>:590:13' i_q_ref_AMM = single(0.0); */
		rtFluxMapID_DW->i_q_ref_AMM = 0.0F;

		/* '<S1>:590:14' i_d_ref_AMM = single(0.0); */
		rtFluxMapID_DW->i_d_ref_AMM = 0.0F;

		/* Entry Internal 'AMMstate': '<S1>:590' */
		/* Transition: '<S1>:666' */
		rtFluxMapID_DW->is_AMMstate = IN_initAMM;

		/* Entry 'initAMM': '<S1>:600' */
		/* '<S1>:600:4' FluxMapID_FOC_output.activeState = uint16(401); */
		rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 401U;

		/* '<S1>:600:5' repetitionCounter = uint32(0); */
		rtFluxMapID_DW->repetitionCounter = 0U;

		/* '<S1>:600:6' NumberOfIDpoints = abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart)/FluxMapIDConfig.IDstepsize+1; */
		rtFluxMapID_DW->NumberOfIDpoints = fabsf(rtFluxMapID_U->FluxMapIDConfig.IDstop - rtFluxMapID_U->FluxMapIDConfig.IDstart) / rtFluxMapID_U->FluxMapIDConfig.IDstepsize + 1.0F;

		/* '<S1>:600:7' NumberOfIQpoints = abs(FluxMapIDConfig.IQstop-FluxMapIDConfig.IQstart)/FluxMapIDConfig.IQstepsize+1; */
		/* '<S1>:600:8' NumberOfPoints = NumberOfIDpoints*NumberOfIQpoints; */
		rtFluxMapID_DW->NumberOfPoints = (fabsf(rtFluxMapID_U->FluxMapIDConfig.IQstop - rtFluxMapID_U->FluxMapIDConfig.IQstart) / rtFluxMapID_U->FluxMapIDConfig.IQstepsize + 1.0F)
		                * rtFluxMapID_DW->NumberOfIDpoints;

		/* '<S1>:680:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
	} else if (rtFluxMapID_U->GlobalConfig_out.Reset) {
		/* Outport: '<Root>/finishedFluxMapID' */
		/* Transition: '<S1>:680' */
		/* '<S1>:680:1' finishedFluxMapID=boolean(0); */
		rtFluxMapID_Y->finishedFluxMapID = false;

		/* Outport: '<Root>/enteredFluxMapID' */
		/* '<S1>:680:2' enteredFluxMapID=boolean(0); */
		rtFluxMapID_Y->enteredFluxMapID = false;
		rtFluxMapID_DW->is_c16_FluxMapID = IN_Waiting;

		/* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
		/* FluxMapID */
    /* donothing */
  }

	/* End of Chart: '<Root>/FluxMapID' */
}

/* Model initialize function */
void FluxMapID_initialize(RT_MODEL_FluxMapID_t * const rtFluxMapID_M)
{
	DW_FluxMapID_t *rtFluxMapID_DW = rtFluxMapID_M->dwork;
	ExtY_FluxMapID_t *rtFluxMapID_Y = (ExtY_FluxMapID_t *) rtFluxMapID_M->outputs;
	ExtU_FluxMapID_t *rtFluxMapID_U = (ExtU_FluxMapID_t *) rtFluxMapID_M->inputs;

  /* Registration code */

	/* initialize non-finites */
	rt_InitInfAndNaN(sizeof(real_T));

  /* states (dwork) */
	(void) memset((void *) rtFluxMapID_DW, 0, sizeof(DW_FluxMapID_t));

  /* external inputs */
	(void) memset(rtFluxMapID_U, 0, sizeof(ExtU_FluxMapID_t));

  /* external outputs */
	(void) memset((void *) rtFluxMapID_Y, 0, sizeof(ExtY_FluxMapID_t));

	/* SystemInitialize for Chart: '<Root>/FluxMapID' */
	rtFluxMapID_DW->is_AMMstate = IN_NO_ACTIVE_CHILD;
	rtFluxMapID_DW->temporalCounter_i1 = 0U;
	rtFluxMapID_DW->is_active_c16_FluxMapID = 0U;
	rtFluxMapID_DW->is_c16_FluxMapID = IN_NO_ACTIVE_CHILD;
	rtFluxMapID_DW->counter = 0U;
	rtFluxMapID_DW->vd2_counter = 0.0F;
	rtFluxMapID_DW->AMMj = 0U;
	rtFluxMapID_DW->AMMn = 0U;
	rtFluxMapID_DW->i_d_ref_AMM = 0.0F;
	rtFluxMapID_DW->i_d_ref_AMM_loc = 0.0F;
	rtFluxMapID_DW->i_q_ref_AMM = 0.0F;
	rtFluxMapID_DW->i_q_ref_AMM_loc = 0.0F;
	rtFluxMapID_DW->NumberOfIDpoints = 0.0F;
	rtFluxMapID_DW->NumberOfPoints = 0.0F;
	rtFluxMapID_DW->i_d_R_online = 0.0F;
	rtFluxMapID_DW->repetitionCounter = 0U;
	rtFluxMapID_DW->id2_counter = 0.0F;
	rtFluxMapID_DW->vd1_counter = 0.0F;
	rtFluxMapID_DW->id1_counter = 0.0F;
	memset(&rtFluxMapID_DW->R_s_array[0], 0, 50U * sizeof(real32_T));

	/* SystemInitialize for Outport: '<Root>/finishedFluxMapID' incorporates:
	 *  Chart: '<Root>/FluxMapID'
	 */
	rtFluxMapID_Y->finishedFluxMapID = false;

	/* SystemInitialize for Outport: '<Root>/enteredFluxMapID' incorporates:
	 *  Chart: '<Root>/FluxMapID'
	 */
	rtFluxMapID_Y->enteredFluxMapID = false;

	/* SystemInitialize for Chart: '<Root>/FluxMapID' incorporates:
	 *  Outport: '<Root>/FluxMapID_FOC_output'
	 *  Outport: '<Root>/FluxMapID_output'
	 */
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.i_dq_ref.zero = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.activeState = 0U;
	rtFluxMapID_Y->FluxMapID_FOC_output.n_ref_FOC = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_speed = false;
	rtFluxMapID_Y->FluxMapID_FOC_output.enableFOC_current = false;
	rtFluxMapID_Y->FluxMapID_FOC_output.VibOn_out = false;
	rtFluxMapID_Y->FluxMapID_FOC_output.VibAmp_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.VibFreq_out = 0U;
	rtFluxMapID_Y->FluxMapID_FOC_output.resetIntegrator = false;
	rtFluxMapID_Y->FluxMapID_FOC_output.PRBS_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_id_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_iq_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.Kp_n_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_id_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_iq_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_FOC_output.Ki_n_out = 0.0F;
	rtFluxMapID_Y->FluxMapID_output.R_s = 0.0F;
	rtFluxMapID_Y->FluxMapID_output.WindingTemp = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
