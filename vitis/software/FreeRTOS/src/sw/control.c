/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface for control function
 */

#include <stdint.h>
#include <stdbool.h>

#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "../main.h"

#include "xcp/xcp_interface.h"
#include "global_data.h"
#include "bsp_timer/bsp_timer.h"

#include "../globalData.h"
#include "../include/uz_assertion_configuration.h"
#include "../uz/uz_global_configuration.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_hw.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "../include/uz_adcLtc2311_ip_core_init.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

#include "../include/gpio_axi.h"
#include "../include/pwm_3L_driver.h"
#include "../include/encoder.h"
#include "../include/pwm_init.h"
#include "../include/mux_axi.h"
#include "../include/adc.h"
#include "../include/isr.h"

#include "FOC_CodeGen/FOC_fastCTRL.h"
#include "FOC_CodeGen/FOC_slowCTRL.h"
#include "FOC_CodeGen/FOC_Statemachine.h"

//====================================================================
// Type definitions
//====================================================================
typedef struct {
	float duty_cycle_1;
	float duty_cycle_2;
	float duty_cycle_3;
	float duty_cycle_4;
	float duty_cycle_5;
	float duty_cycle_6;
} duty_cycles_t;

typedef struct timing_value_t_ {
	float fast_irq_rate;
	float fast_irq_time;
	float task_fast;
	float task_1ms;
	float task_10ms;
	float config_update;
	float xcp_events;
} timing_value_t;

typedef struct {
	timing_value_t now;
	timing_value_t max;
} timing_t;

typedef struct {
	uint32_t activation_irq_1ms;
	uint32_t activation_irq_fpga;
	uint32_t activation_task_fast;
	uint32_t activation_task_1ms;
	uint32_t activation_task_10ms;
} counter_t;

typedef struct {
	timing_t timing_us;
	counter_t cnt;
	float irq_fpga_freq_kHz;
} sanity_t;

typedef struct {
	struct {
		real_T I_dq_RefA[2];                 /* '<Root>/I_dq_Ref [A]' */
		real_T I_phA[6];                     /* '<Root>/I_ph [A]' */
		real_T U_DCV;                        /* '<Root>/U_DC [V]' */
		real_T phi_elrad;                    /* '<Root>/phi_el [rad]' */
		real_T FOC_Mode;                     /* '<Root>/FOC_Mode' */
		real_T FOC_Enable;                   /* '<Root>/FOC_Enable' */
	} fcf_in;
	struct {
		real_T DutyCycles01[6];              /* '<Root>/DutyCycles [0..1]' */
		real_T I_dq_ActA[4];                 /* '<Root>/I_dq_Act [A]' */
		real_T ModInd[2];                    /* '<Root>/ModInd' */
		real_T w_elrads;                     /* '<Root>/w_el [rad//s]' */
		real_T FOC_Error;                    /* '<Root>/FOC_Error' */
		real_T I_dq_Ref_outA[2];             /* '<Root>/I_dq_Ref_out [A]' */
	} fcf_out;
	struct {
		  real_T U_DCV;                        /* '<Root>/U_DC [V]' */
		  real_T ModInd[2];                    /* '<Root>/ModInd' */
		  real_T w_elrads;                     /* '<Root>/w_el [rad//s]' */
		  real_T MotTempdegC;                  /* '<Root>/MotTemp [degC]' */
		  real_T InvTempdegC;                  /* '<Root>/InvTemp [degC]' */
		  real_T I_dq_ActA[4];                 /* '<Root>/I_dq_Act [A]' */
		  real_T ExtTorqReqNm;                 /* '<Root>/ExtTorqReq [Nm]' */
		  real_T SpeedCtrl_Enable;             /* '<Root>/SpeedCtrl_Enable' */
		  real_T ExtTorqLimNm[2];              /* '<Root>/ExtTorqLim [Nm]' */
		  real_T ExtSpeedReqrpm;               /* '<Root>/ExtSpeedReq [rpm]' */
	} scf_in;
	struct {
		  real_T I_dq_RefA[2];                 /* '<Root>/I_dq_Ref [A]' */
		  real_T TorqueEstNm;                  /* '<Root>/TorqueEst [Nm]' */
		  real_T TorqueRefDeratedNm;           /* '<Root>/TorqueRefDerated [Nm]' */
	} scf_out;
	struct {
		  real_T StateReq;                     /* '<Root>/StateReq' */
		  real_T TorqueReq;                    /* '<Root>/TorqueReq' */
		  real_T SpeedReq;                     /* '<Root>/SpeedReq' */
		  boolean_T FastCtrl_Error;            /* '<Root>/error' */
	} smf_in;
	struct {
		  real_T State;                        /* '<Root>/State' */
		  real_T FOC_Mode;                     /* '<Root>/FOC_Mode' */
		  real_T StateFOC;                     /* '<Root>/StateFOC' */
		  real_T FOC_Enable_PWM;               /* '<Root>/FOC_Enable_PWM' */
		  real_T global_reset_errors;          /* '<Root>/global_reset_errors' */
		  real_T SPEED_CTRL_Enable;            /* '<Root>/SPEED_CTRL_Enable' */
	} smf_out;
} ctrl_data_t;
//====================================================================
// Configuration
//====================================================================
#define BACKGROUND_TASK_STACK_SIZE		(4 * 1024)
// Must be task with highest priority!
#define BACKGROUND_TASK_PRIO_FAST		7
#define BACKGROUND_TASK_PRIO_1MS		(BACKGROUND_TASK_PRIO_FAST - 1)
#define BACKGROUND_TASK_PRIO_10MS		(BACKGROUND_TASK_PRIO_1MS - 1)

#define ACTIVATION_QUEUE_LEN			1
#define ACTIVATION_QUEUE_ITEM_SIZE		1

//====================================================================
// Variables
//====================================================================
// Initialize the global variables
DS_Data Global_Data = {
    .rasv = {
        .halfBridge1DutyCycle = 0.0f,
        .halfBridge2DutyCycle = 0.0f,
        .halfBridge3DutyCycle = 0.0f,
        .halfBridge4DutyCycle = 0.0f,
        .halfBridge5DutyCycle = 0.0f,
        .halfBridge6DutyCycle = 0.0f,
		.halfBridge7DutyCycle = 0.0f,
		.halfBridge8DutyCycle = 0.0f,
		.halfBridge9DutyCycle = 0.0f,
		.halfBridge10DutyCycle = 0.0f,
		.halfBridge11DutyCycle = 0.0f,
		.halfBridge12DutyCycle = 0.0f
    },
	.av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
	.av.deadtime_us = UZ_DEADTIME_US,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};

volatile global_t global = {0};

volatile static sanity_t sanity;

volatile static bool init_done_ = 0;

static QueueHandle_t queue_task_fast;
static QueueHandle_t queue_task_1ms;
static QueueHandle_t queue_task_10ms;

volatile static uint8_t state_control;

static RT_MODEL_FOC_fastCTRL_T FOC_fastCTRL_M_;
static RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_MPtr = &FOC_fastCTRL_M_;/* Real-time model */
static B_FOC_fastCTRL_T FOC_fastCTRL_B;/* Observable signals */
static DW_FOC_fastCTRL_T FOC_fastCTRL_DW;/* Observable states */
static ExtU_FOC_fastCTRL_T FOC_fastCTRL_U;/* External inputs */
static ExtY_FOC_fastCTRL_T FOC_fastCTRL_Y;/* External outputs */

static RT_MODEL_FOC_slowCTRL_T FOC_slowCTRL_M_;
static RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_MPtr = &FOC_slowCTRL_M_;/* Real-time model */
static B_FOC_slowCTRL_T FOC_slowCTRL_B;/* Observable signals */
static DW_FOC_slowCTRL_T FOC_slowCTRL_DW;/* Observable states */
static ExtU_FOC_slowCTRL_T FOC_slowCTRL_U;/* External inputs */
static ExtY_FOC_slowCTRL_T FOC_slowCTRL_Y;/* External outputs */

static RT_MODEL_FOC_Statemachine_T FOC_Statemachine_M_;
static RT_MODEL_FOC_Statemachine_T *const FOC_Statemachine_MPtr =
  &FOC_Statemachine_M_;                /* Real-time model */
static DW_FOC_Statemachine_T FOC_Statemachine_DW;/* Observable states */
static ExtU_FOC_Statemachine_T FOC_Statemachine_U;/* External inputs */
static ExtY_FOC_Statemachine_T FOC_Statemachine_Y;/* External outputs */

volatile static ctrl_data_t ctrl_data;

//====================================================================
// Static functions
//====================================================================
#define TS__(name_, ts_start_, ts_end_) \
	sanity.timing_us.now.name_ = bsp_timer_tsU64_delta_us(ts_start_, ts_end_); \
	if (sanity.timing_us.now.name_ > sanity.timing_us.max.name_) \
	sanity.timing_us.max.name_ = sanity.timing_us.now.name_;

static void fast_ctrl_(void)
{
    ADC_readCardALL(&Global_Data);
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

	static bool pwm_enable_last = 1;
	if (pwm_enable_last != global.ctrl.pwm_enable) {
		if (global.ctrl.pwm_enable) {
			uz_axigpio_enable_pwm_and_power_electronics();
		} else {
			uz_axigpio_disable_pwm_and_power_electronics();
		}
	}
	pwm_enable_last = global.ctrl.pwm_enable;

	if (global.ctrl.ctrl_enable) {
		state_control = 1;

		// TODO Set ADC inputs according to hardware setup
		ctrl_data.fcf_in.U_DCV = Global_Data.aa.A2.me.ADC_A1;
		ctrl_data.fcf_in.I_phA[0] = Global_Data.aa.A1.me.ADC_A1;
		ctrl_data.fcf_in.I_phA[1] = Global_Data.aa.A1.me.ADC_A2;
		ctrl_data.fcf_in.I_phA[2] = Global_Data.aa.A1.me.ADC_A3;
		ctrl_data.fcf_in.I_phA[3] = Global_Data.aa.A1.me.ADC_A4;
		ctrl_data.fcf_in.I_phA[4] = Global_Data.aa.A1.me.ADC_B5;
		ctrl_data.fcf_in.I_phA[5] = Global_Data.aa.A1.me.ADC_B6;

		FOC_fastCTRL_MPtr->inputs->U_DCV = ctrl_data.fcf_in.U_DCV;
		FOC_fastCTRL_MPtr->inputs->I_phA[0] = ctrl_data.fcf_in.I_phA[0];
		FOC_fastCTRL_MPtr->inputs->I_phA[1] = ctrl_data.fcf_in.I_phA[1];
		FOC_fastCTRL_MPtr->inputs->I_phA[2] = ctrl_data.fcf_in.I_phA[2];
		FOC_fastCTRL_MPtr->inputs->I_phA[3] = ctrl_data.fcf_in.I_phA[3];
		FOC_fastCTRL_MPtr->inputs->I_phA[4] = ctrl_data.fcf_in.I_phA[4];
		FOC_fastCTRL_MPtr->inputs->I_phA[5] = ctrl_data.fcf_in.I_phA[5];
		FOC_fastCTRL_MPtr->inputs->I_dq_RefA[0] = ctrl_data.fcf_in.I_dq_RefA[0];
		FOC_fastCTRL_MPtr->inputs->I_dq_RefA[1] = ctrl_data.fcf_in.I_dq_RefA[1];
		FOC_fastCTRL_MPtr->inputs->phi_elrad = ctrl_data.fcf_in.phi_elrad;
		FOC_fastCTRL_MPtr->inputs->FOC_Mode = ctrl_data.fcf_in.FOC_Mode;
		FOC_fastCTRL_MPtr->inputs->FOC_Enable_k = ctrl_data.fcf_in.FOC_Enable;

		FOC_fastCTRL_step(FOC_fastCTRL_MPtr);

		ctrl_data.fcf_out.DutyCycles01[0] = FOC_fastCTRL_MPtr->outputs->DutyCycles01[0];
		ctrl_data.fcf_out.DutyCycles01[1] = FOC_fastCTRL_MPtr->outputs->DutyCycles01[1];
		ctrl_data.fcf_out.DutyCycles01[2] = FOC_fastCTRL_MPtr->outputs->DutyCycles01[2];
		ctrl_data.fcf_out.DutyCycles01[3] = FOC_fastCTRL_MPtr->outputs->DutyCycles01[3];
		ctrl_data.fcf_out.DutyCycles01[4] = FOC_fastCTRL_MPtr->outputs->DutyCycles01[4];
		ctrl_data.fcf_out.DutyCycles01[5] = FOC_fastCTRL_MPtr->outputs->DutyCycles01[5];
		ctrl_data.fcf_out.I_dq_ActA[0] = FOC_fastCTRL_MPtr->outputs->I_dq_ActA[0];
		ctrl_data.fcf_out.I_dq_ActA[1] = FOC_fastCTRL_MPtr->outputs->I_dq_ActA[1];
		ctrl_data.fcf_out.I_dq_ActA[2] = FOC_fastCTRL_MPtr->outputs->I_dq_ActA[2];
		ctrl_data.fcf_out.I_dq_ActA[3] = FOC_fastCTRL_MPtr->outputs->I_dq_ActA[3];
		ctrl_data.fcf_out.ModInd[0] = FOC_fastCTRL_MPtr->outputs->ModInd[0];
		ctrl_data.fcf_out.ModInd[1] = FOC_fastCTRL_MPtr->outputs->ModInd[1];
		ctrl_data.fcf_out.w_elrads = FOC_fastCTRL_MPtr->outputs->w_elrads;
		ctrl_data.fcf_out.FOC_Error = FOC_fastCTRL_MPtr->outputs->FOC_Error;
		ctrl_data.fcf_out.I_dq_Ref_outA[0] = FOC_fastCTRL_MPtr->outputs->I_dq_Ref_outA[0];
		ctrl_data.fcf_out.I_dq_Ref_outA[1] = FOC_fastCTRL_MPtr->outputs->I_dq_Ref_outA[1];

		Global_Data.rasv.halfBridge1DutyCycle = ctrl_data.fcf_out.DutyCycles01[0];
		Global_Data.rasv.halfBridge2DutyCycle = ctrl_data.fcf_out.DutyCycles01[1];
		Global_Data.rasv.halfBridge3DutyCycle = ctrl_data.fcf_out.DutyCycles01[2];
		Global_Data.rasv.halfBridge4DutyCycle = ctrl_data.fcf_out.DutyCycles01[3];
		Global_Data.rasv.halfBridge5DutyCycle = ctrl_data.fcf_out.DutyCycles01[4];
		Global_Data.rasv.halfBridge6DutyCycle = ctrl_data.fcf_out.DutyCycles01[5];
	} else {
		state_control = 0;

		Global_Data.rasv.halfBridge1DutyCycle = 0;
		Global_Data.rasv.halfBridge2DutyCycle = 0;
		Global_Data.rasv.halfBridge3DutyCycle = 0;
		Global_Data.rasv.halfBridge4DutyCycle = 0;
		Global_Data.rasv.halfBridge5DutyCycle = 0;
		Global_Data.rasv.halfBridge6DutyCycle = 0;
		Global_Data.rasv.halfBridge7DutyCycle = 0;
		Global_Data.rasv.halfBridge8DutyCycle = 0;
		Global_Data.rasv.halfBridge9DutyCycle = 0;
		Global_Data.rasv.halfBridge10DutyCycle = 0;
		Global_Data.rasv.halfBridge11DutyCycle = 0;
		Global_Data.rasv.halfBridge12DutyCycle = 0;
	}

	// The function uz_PWM_SS_2L_set_duty_cycle() checks values and throws error! Catch this..
	#define RANGE_CHECK(duty_cycle_, min_, max_) \
	if ((duty_cycle_ < (float)min_) || (duty_cycle_ > (float)max_)) { \
		duty_cycle_ = 0; \
	}
	RANGE_CHECK(Global_Data.rasv.halfBridge1DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge2DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge3DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge4DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge5DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge6DutyCycle, 0, 1);

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    // Currently not used
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Currently not used
    // Set duty cycles for three-level modulator
//    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
//                        Global_Data.rasv.halfBridge2DutyCycle,
//                        Global_Data.rasv.halfBridge3DutyCycle);
}

static void configuration_update(void)
{
	uint64_t ts_start = bsp_timer_timestamp_u64_get();

	if ((global.ctrl.ctrl_enable == 0)
		&& (global.config.PWM_freq_Hz >= 1e3 && global.config.PWM_freq_Hz <= 100e3)) {
		Global_Data.av.pwm_frequency_hz = global.config.PWM_freq_Hz;
		Global_Data.av.isr_samplerate_s = (1.0f / Global_Data.av.pwm_frequency_hz);
		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_0_to_5,
								  Global_Data.av.pwm_frequency_hz);
		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_6_to_11,
								  Global_Data.av.pwm_frequency_hz);
	    // Currently not used
//		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_12_to_17,
//								  Global_Data.av.pwm_frequency_hz);
//		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_18_to_23,
//								  Global_Data.av.pwm_frequency_hz);
	}

	if ((global.ctrl.ctrl_enable == 0)
		&& (global.config.deadtime_us >= 0 && global.config.deadtime_us <= 100)) {
		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, 0);
		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, 0);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, 0);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, 0);

		Global_Data.av.deadtime_us = global.config.deadtime_us;
		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, Global_Data.av.deadtime_us);
		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, Global_Data.av.deadtime_us);
//		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, Global_Data.av.deadtime_us);
//		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, Global_Data.av.deadtime_us);

		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, 1);
		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, 1);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, 1);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, 1);
	}

	uint64_t ts_now = bsp_timer_timestamp_u64_get();
	TS__(config_update, ts_start, ts_now);
}

static void task_1ms(void)
{
	Xil_ExceptionDisable();

	// TODO Set ADC inputs according to hardware setup
	ctrl_data.scf_in.U_DCV = Global_Data.aa.A2.me.ADC_A1;

	ctrl_data.scf_in.ModInd[0] = ctrl_data.fcf_out.ModInd[0];
	ctrl_data.scf_in.ModInd[1] = ctrl_data.fcf_out.ModInd[1];
	ctrl_data.scf_in.w_elrads = ctrl_data.fcf_out.w_elrads;

	FOC_slowCTRL_MPtr->inputs->U_DCV = ctrl_data.scf_in.U_DCV;
	FOC_slowCTRL_MPtr->inputs->ModInd[0] = ctrl_data.scf_in.ModInd[0];
	FOC_slowCTRL_MPtr->inputs->ModInd[1] = ctrl_data.scf_in.ModInd[1];
	FOC_slowCTRL_MPtr->inputs->w_elrads = ctrl_data.scf_in.w_elrads;
	FOC_slowCTRL_MPtr->inputs->MotTempdegC = ctrl_data.scf_in.MotTempdegC;
	FOC_slowCTRL_MPtr->inputs->InvTempdegC = ctrl_data.scf_in.InvTempdegC;
	FOC_slowCTRL_MPtr->inputs->I_dq_ActA[0] = ctrl_data.scf_in.I_dq_ActA[0];
	FOC_slowCTRL_MPtr->inputs->I_dq_ActA[1] = ctrl_data.scf_in.I_dq_ActA[1];
	FOC_slowCTRL_MPtr->inputs->I_dq_ActA[2] = ctrl_data.scf_in.I_dq_ActA[2];
	FOC_slowCTRL_MPtr->inputs->I_dq_ActA[3] = ctrl_data.scf_in.I_dq_ActA[3];
	FOC_slowCTRL_MPtr->inputs->ExtTorqReqNm = ctrl_data.scf_in.ExtTorqReqNm;
	FOC_slowCTRL_MPtr->inputs->SpeedCtrl_Enable = ctrl_data.scf_in.SpeedCtrl_Enable;
	FOC_slowCTRL_MPtr->inputs->ExtTorqLimNm[0] = ctrl_data.scf_in.ExtTorqLimNm[0];
	FOC_slowCTRL_MPtr->inputs->ExtTorqLimNm[1] = ctrl_data.scf_in.ExtTorqLimNm[1];
	FOC_slowCTRL_MPtr->inputs->ExtSpeedReqrpm = ctrl_data.scf_in.ExtSpeedReqrpm;

	Xil_ExceptionEnable();

	FOC_slowCTRL_step(FOC_slowCTRL_MPtr);

	Xil_ExceptionDisable();

	ctrl_data.scf_out.I_dq_RefA[0] = FOC_slowCTRL_MPtr->outputs->I_dq_RefA[0];
	ctrl_data.scf_out.I_dq_RefA[1] = FOC_slowCTRL_MPtr->outputs->I_dq_RefA[1];
	ctrl_data.scf_out.TorqueEstNm = FOC_slowCTRL_MPtr->outputs->TorqueEstNm;
	ctrl_data.scf_out.TorqueRefDeratedNm = FOC_slowCTRL_MPtr->outputs->TorqueRefDeratedNm;


    ctrl_data.fcf_in.I_dq_RefA[0] = ctrl_data.scf_out.I_dq_RefA[0];
    ctrl_data.fcf_in.I_dq_RefA[1] = ctrl_data.scf_out.I_dq_RefA[1];

	Xil_ExceptionEnable();
}

static void task_10ms(void)
{

	Xil_ExceptionDisable();

	ctrl_data.smf_in.FastCtrl_Error = ctrl_data.fcf_out.FOC_Error;

	Xil_ExceptionEnable();

	FOC_Statemachine_MPtr->inputs->StateReq = ctrl_data.smf_in.StateReq;
	FOC_Statemachine_MPtr->inputs->TorqueReq = ctrl_data.smf_in.TorqueReq;
	FOC_Statemachine_MPtr->inputs->SpeedReq = ctrl_data.smf_in.SpeedReq;
	FOC_Statemachine_MPtr->inputs->FastCtrl_Error = ctrl_data.smf_in.FastCtrl_Error;

	FOC_Statemachine_step(FOC_Statemachine_MPtr);

	ctrl_data.smf_out.State = FOC_Statemachine_MPtr->outputs->State;
	ctrl_data.smf_out.FOC_Mode = FOC_Statemachine_MPtr->outputs->FOC_Mode;
	ctrl_data.smf_out.StateFOC = FOC_Statemachine_MPtr->outputs->StateFOC;
	ctrl_data.smf_out.FOC_Enable_PWM = FOC_Statemachine_MPtr->outputs->FOC_Enable_PWM;
	ctrl_data.smf_out.global_reset_errors = FOC_Statemachine_MPtr->outputs->global_reset_errors;
	ctrl_data.smf_out.SPEED_CTRL_Enable = FOC_Statemachine_MPtr->outputs->SPEED_CTRL_Enable;

	Xil_ExceptionDisable();

    ctrl_data.fcf_in.FOC_Mode = ctrl_data.smf_out.FOC_Mode;

	Xil_ExceptionEnable();

	// Todo: other background stuff could also be done here
	// control_buttons()
	// control_leds()
}

static void task_background_fast(void *p)
{
	vPortTaskUsesFPU();

	while (1) {
		/*
		 * Implement simple activation of this task with a queue.
		 * Read blocking from queue. An interrupt will write to the queue
		 * each tick and thus activate this task.
		 */
		uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
		xQueueReceive(queue_task_fast, buf, portMAX_DELAY);

		uint64_t ts_start = bsp_timer_timestamp_u64_get();
	    static uint64_t ts_last = 0;
	    TS__(fast_irq_rate, ts_last, ts_start);
	    sanity.irq_fpga_freq_kHz = (1 / sanity.timing_us.now.fast_irq_rate * (float)1e3);
	    ts_last = ts_start;

		//---------------------
		// Fast control
		sanity.cnt.activation_task_fast++;
		fast_ctrl_();
		uint64_t ts_after_fast_ctrl = bsp_timer_timestamp_u64_get();
		TS__(task_fast, ts_start, ts_after_fast_ctrl);

		//---------------------
		// XCP events
		xcp_event_fast();
		static uint64_t ts_last_activation_1ms = 0;
		const uint64_t TICKS_1MS = (BSP_TIMER_TICKS_PER_SECOND / 1000);
		if ((ts_start - ts_last_activation_1ms) >= TICKS_1MS) {
			ts_last_activation_1ms = ts_start;
			xcp_events_1ms_and_slower();
		}
		uint64_t ts_after_xcp_events = bsp_timer_timestamp_u64_get();
		TS__(xcp_events, ts_after_fast_ctrl, ts_after_xcp_events);

		//---------------------
		// Configuration changes
		if (global.config.config_update) {
			global.config.config_update = 0;
			configuration_update();
		}
	}
}

static void task_background_1ms(void *p)
{
	vPortTaskUsesFPU();

	while (1) {
		/*
		 * Implement simple activation of this task with a queue.
		 * Read blocking from queue. An interrupt will write to the queue
		 * each tick and thus activate this task.
		 */
		uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
		xQueueReceive(queue_task_1ms, buf, portMAX_DELAY);

		uint64_t ts_start = bsp_timer_timestamp_u64_get();
		sanity.cnt.activation_task_1ms++;
		task_1ms();
		uint64_t ts_now = bsp_timer_timestamp_u64_get();
		TS__(task_1ms, ts_start, ts_now);
	}
}

static void task_background_10ms(void *p)
{
	vPortTaskUsesFPU();

	while (1) {
		/*
		 * Implement simple activation of this task with a queue.
		 * Read blocking from queue. An interrupt will write to the queue
		 * each tick and thus activate this task.
		 */
		uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
		xQueueReceive(queue_task_10ms, buf, portMAX_DELAY);

		uint64_t ts_start = bsp_timer_timestamp_u64_get();
		sanity.cnt.activation_task_10ms++;
		task_10ms();
		uint64_t ts_now = bsp_timer_timestamp_u64_get();
		TS__(task_10ms, ts_start, ts_now);
	}
}

//====================================================================
// Global functions
//====================================================================
void timer_irq_callback__(void)
{
	// Wait until queues and other stuff is actually initialized
	if (! init_done_)
		return;

	// Timer irq runs with 1 kHz
	sanity.cnt.activation_irq_1ms++;

	uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
	xQueueSendFromISR(queue_task_1ms, buf, NULL);

	static int div_cnt = 0;
	div_cnt++;
	if (div_cnt >= 10) {
		div_cnt = 0;
		xQueueSendFromISR(queue_task_10ms, buf, NULL);
	}

	// Call scheduler for a task switch
	portYIELD_FROM_ISR(pdTRUE);
}

void irq_fpga(void *data)
{
	// Wait until queues and other stuff is actually initialized
	if (! init_done_)
		return;

	sanity.cnt.activation_irq_fpga++;

	uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
	xQueueSendFromISR(queue_task_fast, buf, NULL);

	// Call scheduler for a task switch
	portYIELD_FROM_ISR(pdTRUE);
}

void basis_setup(void *p)
{
	FOC_fastCTRL_MPtr->blockIO = &FOC_fastCTRL_B;
	FOC_fastCTRL_MPtr->dwork = &FOC_fastCTRL_DW;
	FOC_fastCTRL_MPtr->inputs = &FOC_fastCTRL_U;
	FOC_fastCTRL_MPtr->outputs = &FOC_fastCTRL_Y;
	FOC_fastCTRL_initialize(FOC_fastCTRL_MPtr);

	FOC_slowCTRL_MPtr->blockIO = &FOC_slowCTRL_B;
	FOC_slowCTRL_MPtr->dwork = &FOC_slowCTRL_DW;
	FOC_slowCTRL_MPtr->inputs = &FOC_slowCTRL_U;
	FOC_slowCTRL_MPtr->outputs = &FOC_slowCTRL_Y;
	FOC_slowCTRL_initialize(FOC_slowCTRL_MPtr);

	FOC_Statemachine_MPtr->dwork = &FOC_Statemachine_DW;
	FOC_Statemachine_MPtr->inputs = &FOC_Statemachine_U;
	FOC_Statemachine_MPtr->outputs = &FOC_Statemachine_Y;
	FOC_Statemachine_initialize(FOC_Statemachine_MPtr);

	uz_assert_configuration();
	Initialize_AXI_GPIO();
	uz_adcLtc2311_ip_core_init();
    Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
    Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
    Global_Data.objects.deadtime_interlock_d1_pin_12_to_17 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17();
    Global_Data.objects.deadtime_interlock_d1_pin_18_to_23 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23();
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, true);
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, true);
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, true);
	uz_axigpio_disable_pwm_and_power_electronics();

    Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
    Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
    Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
    Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
    Global_Data.objects.mux_axi = initialize_uz_mux_axi();
    // Currently not used
//    PWM_3L_Initialize(&Global_Data); // three-level modulator
    initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
    uz_axigpio_enable_datamover();

    // Set XCP stimuli variables to the currently active values.. so they are correctly viewed in CANape
    global.config.PWM_freq_Hz = Global_Data.av.pwm_frequency_hz;
    global.config.deadtime_us = Global_Data.av.deadtime_us;

	bsp_led_init();


	queue_task_fast = xQueueGenericCreate(ACTIVATION_QUEUE_LEN, ACTIVATION_QUEUE_ITEM_SIZE, 0);
	xTaskCreate(task_background_fast, "fast", BACKGROUND_TASK_STACK_SIZE,
			NULL, BACKGROUND_TASK_PRIO_FAST, NULL);
	queue_task_1ms = xQueueGenericCreate(ACTIVATION_QUEUE_LEN, ACTIVATION_QUEUE_ITEM_SIZE, 0);
	xTaskCreate(task_background_1ms, "backgr1ms", BACKGROUND_TASK_STACK_SIZE,
			NULL, BACKGROUND_TASK_PRIO_1MS, NULL);
	queue_task_10ms = xQueueGenericCreate(ACTIVATION_QUEUE_LEN, ACTIVATION_QUEUE_ITEM_SIZE, 0);
	xTaskCreate(task_background_10ms, "backgr10ms", BACKGROUND_TASK_STACK_SIZE,
			NULL, BACKGROUND_TASK_PRIO_10MS, NULL);

	xil_printf("APU: basis init done\n", __func__);

	global.led.error = 0;
	global.led.ready = 1;
	global.led.running = 0;
	global.led.user = 0;

	init_done_ = 1;

	while (1) {
		static uint8_t cnt = 0;
		cnt++;
		global.led.running = (cnt & 1);

		bsp_led_run();

		vTaskDelay(100 / portTICK_PERIOD_MS);

		// Each 3 seconds
		static int div_cnt = 0;
		div_cnt++;
		if (div_cnt >= 30) {
			div_cnt = 0;

			Xil_ExceptionDisable();
			// Reset values to have the max values of the last 3 seconds
			memset((void *)&sanity.timing_us.max, 0, sizeof(sanity.timing_us.max));
			Xil_ExceptionEnable();
		}
	}

	vTaskDelete(NULL);
}
