/******************************************************************************
 * Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
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

#include "../include/isr.h"
#include "../include/speed_ol_filter.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"
// Modular IM control
#include "../include/motor_config.h"
#include "../include/error_checks.h"
#include "../include/im_observer.h"
#include "../include/im_uf_control.h"
#include "../include/im_foc_control.h"
#include "../uz/uz_IM_config/uz_IM_config.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

#define RR_ID_SCALE 1 // Defines the max points for the paraid in ampere. E.g., if set to 5, the grid is +/- 5A iq and 0 to -5 A ID.
#define RR_IQ_SCALE 1 // Defines the max points for the paraid in ampere.
float id_setpoints[] = {
#include "id_setpoints_rr.csv"
};

float iq_setpoints[] = {
#include "iq_setpoints_rr.csv"
};

float speed_setpoints[] = {
#include "speed_setpoints_rr.csv"
};
#define PROFILE_SETPOINT_DURATION_IN_ISR_TICKS 50000U //5s als test
// theta offset
float IM_theta_el_offset = 0.0f;

// measurement structs for motor control
struct uz_3ph_abc_t i_abc_VA = {0.0f};
struct uz_3ph_dq_t i_dq_VA = {0.0f};
struct uz_3ph_dq_t i_dq_IM = {0.0f};
struct uz_3ph_dq_t i_dq_ref_VA = {0.0f};
struct uz_3ph_dq_t v_dq_ref_VA = {0.0f};
struct uz_3ph_dq_t v_dq_meas_VA = {0.0f};
struct uz_DutyCycle_t dutycyc_VA = {0.0f};
bool enable_controller_VA = false;
bool enable_controller_IM = false;
bool va_use_speed_control = false;
bool  enable_speed_outlier_rejection = false;
float speed_ol_thr_scale             = MOTOR_SPEED_OL_THR_SCALE;
float speed_ol_thr_min_rpm           = MOTOR_SPEED_OL_THR_MIN_RPM;

// V/f control parameters — user-settable (e.g. via JavaScope send fields)
float vf_frequency_setpoint_Hz = 10.0f;
float vf_ratio_V_per_Hz          = MOTOR_UF_ratio_V_per_Hz;
float vf_boost_voltage_V         = MOTOR_UF_boost_voltage_V;
float vf_max_frequency_Hz        = MOTOR_UF_max_frequency_Hz;
float vf_max_voltage_V           = MOTOR_UF_max_voltage_V;
float vf_frequency_ramp_Hz_per_s = MOTOR_UF_frequency_ramp_Hz_per_s;
float vf_voltage_magnitude_V = 0.0f; /* diagnostic: last commanded voltage in RMS L-L */

// FOC / observer mode selection — settable at runtime via JavaScope
bool use_foc = false;
bool use_speed_control = false;

bool use_resonant_6th = false;
bool use_kalman_filter = true;
bool use_deterministic_observer = false;
float id_ref_A = 0.0f;
float iq_ref_A = 0.0f;
float speed_ref_rpm = 0.0f;
float im_speed_pi_kp = MOTOR_Speed_Kp;
float im_speed_pi_ki = MOTOR_Speed_Ki;

// KF tuning — overridable at runtime
float kf_q_i   = MOTOR_KF_Q_i;
float kf_q_psi = MOTOR_KF_Q_psi;
float kf_r_i   = MOTOR_KF_R_i;

// KF diagnostics (populated after each KF step)
float kf_innov_alpha = 0.0f;
float kf_innov_beta  = 0.0f;

// Observer outputs exposed for JavaScope
float psi_r_mag_Vs = 0.0f;
float omega_s_rad_s = 0.0f;
float det_omega_s_rad_s = 0.0f;
float stator_current_fundamental_frequency_Hz = 0.0f;
float electric_torque_estimate_Nm = 0.0f;

float const duty_offset = 0.5f;
float I_U_offset;
float I_V_offset;
float I_W_offset;
float U_DC_offset = 2.5f;

int calibrate_current_measurement_done = 0;
int calibrate_current_measurement_counter = 0;
int calibrate_current_measurement_counter_stop = 1000;

double totalU = 0;
double totalV = 0;
double totalW = 0;

// Induction machine parameters — configured via motor_config.h
static uz_IM_t IM_config = {
    .Rs_Ohm         = MOTOR_Rs_Ohm,
    .Rr_Ohm         = MOTOR_Rr_Ohm,
    .Lsigma_s_Henry = MOTOR_Lsigma_s_H,
    .Lsigma_r_Henry = MOTOR_Lsigma_r_H,
    .Lm_Henry       = MOTOR_Lm_H,
    .polePairs      = MOTOR_PolePairs,
    .J_kg_m_squared = MOTOR_J_kgm2,
    .I_max_Ampere   = MOTOR_Control_current_max_A,
    .Psi_rated_Vs   = MOTOR_Psi_rated_Vs,
};

static error_checks_config_t error_checks_config = {
    .im_vdc_min                  = v_dc_min_v,
    .im_vdc_max                  = vdc_max_v,
    .im_iphase_max               = MOTOR_Protection_phase_max_A,
    .im_max_mechanical_speed_rpm = MOTOR_Speed_max_rpm,
    .va_vdc_max                  = VA_VDC_MAX_V,
    .va_iphase_max               = VA_IPHASE_MAX_A,
};

// IM control module states
static im_uf_control_state_t uf_control_state = {0};
static im_foc_control_state_t foc_control_state = {0};
static im_rotor_flux_observer_state_t rotor_flux_observer_state = {0};
static im_kf_observer_state_t kf_observer_state = {0};
static uz_IM_ss_t im_ss = {0};
static bool im_ss_computed = false;
static bool deterministic_observer_enabled_last = false;

// Measured dq in flux frame — for JavaScope and resonant controller
float id_meas_raw_dq = 0.0f;
float iq_meas_raw_dq = 0.0f;

// FOC diagnostics for JavaScope
float ud_pi_V    = 0.0f;
float uq_pi_V    = 0.0f;
float ud_decoup_V = 0.0f;
float uq_decoup_V = 0.0f;
float ud_res_V   = 0.0f;
float uq_res_V   = 0.0f;
float omega_slip_rad_s_diag = 0.0f;
float slip_pct_diag         = 0.0f;

// Global variable structure
extern DS_Data Global_Data;
extern struct uz_PWM_duty_freq_detection_outputs_t outputs;
extern struct linear_interpolation_parameters_t lin_inter_param;

static void ReadAllADC();
static void im_control();
static void speed_control_VA();
static void current_control_VA();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void calibrate_current_offsets(void);
static void update_measurements_from_adc(void);
static void update_va_current_feedback(void);
static void trip_all_inverters_on_error(void);
void reset_VA(void);
void reset_im(void);
void rr_profile(void);

void set_im_speed_pi_kp(float new_kp)
{
	if (new_kp < 0.0f) {
		return;
	}
	im_speed_pi_kp = new_kp;
	if (foc_control_state.pi_speed != NULL) {
		uz_PI_Controller_set_Kp(foc_control_state.pi_speed, new_kp);
	}
}

void set_im_speed_pi_ki(float new_ki)
{
	if (new_ki < 0.0f) {
		return;
	}
	im_speed_pi_ki = new_ki;
	if (foc_control_state.pi_speed != NULL) {
		uz_PI_Controller_set_Ki(foc_control_state.pi_speed, new_ki);
	}
}

//==============================================================================================================================================================
//----------------------------------------------------
// Initialize_ISR_Software() — call once from main after isr_samplerate_s is set
//----------------------------------------------------
void Initialize_ISR_Software(DS_Data *data)
{
    uz_assert_not_NULL(data);
    uz_assert(data->av.isr_samplerate_s > 0.0f);

    im_uf_control_reset(&uf_control_state);

    im_rotor_flux_observer_init(&IM_config, data->av.isr_samplerate_s, &rotor_flux_observer_state);

    im_foc_control_init(&IM_config, data->av.isr_samplerate_s, &foc_control_state);
    set_im_speed_pi_kp(im_speed_pi_kp);
    set_im_speed_pi_ki(im_speed_pi_ki);
    im_foc_control_reset(&foc_control_state);

    im_kf_observer_init(&IM_config, data->av.isr_samplerate_s, &kf_observer_state);

    im_ss = uz_IM_ss_compute(IM_config, data->av.isr_samplerate_s);
    im_ss_computed = true;

    id_ref_A = uz_IM_get_id_ref_for_psi_r(IM_config, IM_config.Psi_rated_Vs);
}

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_2(&Global_Data);
//    Global_Data.av.IM_mechanicalRotorSpeed = -1.0f * Global_Data.av.VA_mechanicalRotorSpeed;
    Global_Data.av.IM_mechanicalRotorSpeed = Global_Data.aa.A2.me.ADC_B5;
//    Global_Data.av.IM_mechanicalRotorSpeed = Global_Data.aa.A2.me.ADC_B5;
    {
        float const raw_rpm = Global_Data.av.IM_mechanicalRotorSpeed;
        float const y_prev  = Global_Data.av.IM_mechanicalRotorSpeed_filtered;
        float input;
        if (enable_speed_outlier_rejection) {
            float const thr   = fmaxf(speed_ol_thr_min_rpm,
                                      speed_ol_thr_scale * fabsf(y_prev));
            input = (fabsf(raw_rpm - y_prev) <= thr) ? raw_rpm : y_prev;
        } else {
            input = raw_rpm;
        }
        Global_Data.av.IM_mechanicalRotorSpeed_filtered =
            uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_speed_IM, input);
    }

    calibrate_current_offsets();
    update_measurements_from_adc();
    (void)error_checks_step(&Global_Data.av, &error_checks_config);
    if (error_checks_trip_pending()) {
		trip_all_inverters_on_error();
    }
    update_va_current_feedback();
    platform_state_t current_state = ultrazohm_state_machine_get_state();

    if (current_state == idle_state) {
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    	reset_VA();
    	reset_im();
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);
    	enable_controller_VA = false;
    	enable_controller_IM = false;
    } else if (current_state == running_state) {
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
    } else if (current_state == control_state) {
    	if (enable_controller_VA) {
    		if (va_use_speed_control) {
    			speed_control_VA();
    		} else {
    			current_control_VA();
    		}
    	}
		im_control();
		// RR Profile
		rr_profile();
    }
    if (error_checks_trip_pending()) {
		trip_all_inverters_on_error();
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);


    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}


//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};

static void calibrate_current_offsets(void) {
	if (calibrate_current_measurement_done) {
		return;
	}

	totalU += Global_Data.aa.A1.me.ADC_A1;
	totalV += Global_Data.aa.A1.me.ADC_A2;
	totalW += Global_Data.aa.A1.me.ADC_A3;
	calibrate_current_measurement_counter++;

	if (calibrate_current_measurement_counter == calibrate_current_measurement_counter_stop) {
		I_U_offset = totalU / calibrate_current_measurement_counter_stop;
		I_V_offset = totalV / calibrate_current_measurement_counter_stop;
		I_W_offset = totalW / calibrate_current_measurement_counter_stop;
		calibrate_current_measurement_done = 1;
	}
}

static void update_measurements_from_adc(void) {
	// IM measurements
	Global_Data.av.IM_vdc = Global_Data.aa.A1.me.ADC_A4 - U_DC_offset;
	Global_Data.av.IM_ia = Global_Data.aa.A1.me.ADC_A1 - I_U_offset;
	Global_Data.av.IM_ib = Global_Data.aa.A1.me.ADC_A2 - I_V_offset;
	Global_Data.av.IM_ic = Global_Data.aa.A1.me.ADC_A3 - I_W_offset;

	// VA measurements
//	Global_Data.av.VA_ia = Global_Data.aa.A2.me.ADC_A4;
//	Global_Data.av.VA_ib = Global_Data.aa.A2.me.ADC_A3;
//	Global_Data.av.VA_ic = Global_Data.aa.A2.me.ADC_A2;
//	Global_Data.av.VA_idc = Global_Data.aa.A2.me.ADC_B5;
//	Global_Data.av.VA_ua = Global_Data.aa.A2.me.ADC_B8;
//	Global_Data.av.VA_ub = Global_Data.aa.A2.me.ADC_B7;
//	Global_Data.av.VA_uc = Global_Data.aa.A2.me.ADC_B6;
//	Global_Data.av.VA_vdc = Global_Data.aa.A2.me.ADC_A1;

	Global_Data.av.VA_vdc = 48.0f;
	Global_Data.av.VA_ia =  0.0f;
	Global_Data.av.VA_ib = 	0.0f;
	Global_Data.av.VA_ic =  0.0f;
	// status, safety and derived values
	Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
	Global_Data.av.mean_temp_inv_d2 =
			(Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1 +
			 Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1 +
			 Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2 +
			 Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2 +
			 Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3 +
			 Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3) * 0.1667f;

	i_abc_VA.a = Global_Data.av.VA_ia;
	i_abc_VA.b = Global_Data.av.VA_ib;
	i_abc_VA.c = Global_Data.av.VA_ic;

}

static void update_va_current_feedback(void) {
	i_dq_VA = uz_transformation_3ph_abc_to_dq(i_abc_VA, Global_Data.av.VA_theta_elec);
	Global_Data.av.VA_I_d = i_dq_VA.d;
	Global_Data.av.VA_I_q = i_dq_VA.q;
}

static void trip_all_inverters_on_error(void) {
	enable_controller_VA = false;
	enable_controller_IM = false;
	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);
	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge4DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge5DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge6DutyCycle = 0.5f;
	ultrazohm_state_machine_set_error(true);
}

void reset_VA(void) {
	uz_CurrentControl_reset(Global_Data.objects.current_ctrl_VA);
	uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_VA);
	Global_Data.rasv.n_ref_VA = 0.0f;
	Global_Data.rasv.n_ref_filt_VA = 0.0f;
	Global_Data.rasv.M_ref_VA = 0.0f;
	Global_Data.rasv.i_dq_ref_VA.d = 0.0f;
	Global_Data.rasv.i_dq_ref_VA.q = 0.0f;
	Global_Data.av.VA_vd = 0.0f;
	Global_Data.av.VA_vq = 0.0f;
	Global_Data.rasv.halfBridge4DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge5DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge6DutyCycle = 0.5f;
}

void reset_im(void) {
	Global_Data.av.IM_I_d = 0.0f;
	Global_Data.av.IM_I_q = 0.0f;
	im_uf_control_reset(&uf_control_state);
	im_foc_control_reset(&foc_control_state);

	// Re-initialize observer states so re-enable starts with a clean flux estimate.
	// Without this, stale psi_r_alpha/beta would give a wrong initial flux angle.
	im_rotor_flux_observer_init(&IM_config, Global_Data.av.isr_samplerate_s, &rotor_flux_observer_state);
	im_kf_observer_init(&IM_config, Global_Data.av.isr_samplerate_s, &kf_observer_state);

	// Clear observer diagnostic outputs
	psi_r_mag_Vs       = 0.0f;
	omega_s_rad_s      = 0.0f;
	det_omega_s_rad_s  = 0.0f;
	electric_torque_estimate_Nm = 0.0f;
	kf_innov_alpha     = 0.0f;
	kf_innov_beta      = 0.0f;
	id_meas_raw_dq     = 0.0f;
	iq_meas_raw_dq     = 0.0f;

	uz_signals_IIR_Filter_reset(Global_Data.objects.iir_filter_speed_IM);
	Global_Data.av.IM_mechanicalRotorSpeed_filtered = 0.0f;
	uz_signals_IIR_Filter_reset(Global_Data.objects.iir_filter_slip_pct);
	slip_pct_diag = 0.0f;

	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
}

static void im_control(void) {
    if (use_deterministic_observer && !deterministic_observer_enabled_last) {
        im_rotor_flux_observer_init(&IM_config, Global_Data.av.isr_samplerate_s, &rotor_flux_observer_state);
    }
    deterministic_observer_enabled_last = use_deterministic_observer;

	// Apply runtime-tunable KF noise matrices
	if (im_ss_computed) {
		im_ss.Q_diag[0] = kf_q_i;
		im_ss.Q_diag[1] = kf_q_i;
		im_ss.Q_diag[2] = kf_q_psi;
		im_ss.Q_diag[3] = kf_q_psi;
		im_ss.R_diag[0] = kf_r_i;
		im_ss.R_diag[1] = kf_r_i;
	}

	// Phase voltages applied in the previous ISR step — used by KF voltage model.
	// Apply the same hardware min-pulse-width clamp that the FPGA PWM IP enforces.
	float const u_a = (fmaxf(UZ_MIN_PULSE_WIDTH, fminf(1.0f - UZ_MIN_PULSE_WIDTH, Global_Data.rasv.halfBridge1DutyCycle)) - duty_offset) * Global_Data.av.IM_vdc;
	float const u_b = (fmaxf(UZ_MIN_PULSE_WIDTH, fminf(1.0f - UZ_MIN_PULSE_WIDTH, Global_Data.rasv.halfBridge2DutyCycle)) - duty_offset) * Global_Data.av.IM_vdc;
	float const u_c = (fmaxf(UZ_MIN_PULSE_WIDTH, fminf(1.0f - UZ_MIN_PULSE_WIDTH, Global_Data.rasv.halfBridge3DutyCycle)) - duty_offset) * Global_Data.av.IM_vdc;

	bool const kf_ready = im_ss_computed && (calibrate_current_measurement_done != 0);

	im_observer_result_t const obs = im_observer_step(&Global_Data.av, &IM_config, u_a, u_b, u_c,
	                                                   kf_ready, use_kalman_filter, use_deterministic_observer,
	                                                   &rotor_flux_observer_state, &im_ss, &kf_observer_state);

	im_rotor_flux_observer_output_t const observer_output = obs.output;
	det_omega_s_rad_s = obs.det_omega_s_rad_s;
	electric_torque_estimate_Nm = obs.electric_torque_estimate_Nm;
	kf_innov_alpha    = obs.kf_innov_alpha;
	kf_innov_beta     = obs.kf_innov_beta;

	// Measured dq in flux frame — for JavaScope and resonant controller
	uz_3ph_abc_t const i_abc_raw = {.a = Global_Data.av.IM_ia, .b = Global_Data.av.IM_ib, .c = Global_Data.av.IM_ic};
	uz_3ph_dq_t const i_dq_raw = uz_transformation_3ph_abc_to_dq(i_abc_raw, observer_output.theta_flux_rad);
	id_meas_raw_dq = i_dq_raw.d;
	iq_meas_raw_dq = i_dq_raw.q;

	// Write observer results into global data
	Global_Data.av.IM_I_d        = observer_output.i_d;
	Global_Data.av.IM_I_q        = observer_output.i_q;
	Global_Data.av.IM_theta_elec = observer_output.theta_elec_rad;
	stator_current_fundamental_frequency_Hz = observer_output.stator_current_fundamental_frequency_Hz;
	psi_r_mag_Vs  = observer_output.psi_r_mag;
	omega_s_rad_s = 2.0f * UZ_PIf * observer_output.stator_current_fundamental_frequency_Hz;
	omega_slip_rad_s_diag = omega_s_rad_s - observer_output.omega_r_el_rad_s;
	float const slip_pct_raw = (fabsf(omega_s_rad_s) > 0.1f) ? (omega_slip_rad_s_diag / omega_s_rad_s * 100.0f) : 0.0f;
	slip_pct_diag = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_slip_pct, slip_pct_raw);
	float const omega_s_for_resonant_rad_s = obs.deterministic_observer_active ? det_omega_s_rad_s : omega_s_rad_s;

	// Control law selection
	if (use_foc) {
		im_foc_control_input_t foc_input = {
			.use_speed_control          = use_speed_control,
			.use_resonant_6th           = use_resonant_6th,
			.id_ref_A                   = id_ref_A,
			.iq_ref_A                   = iq_ref_A,
			.speed_ref_rpm              = speed_ref_rpm,
			.id_meas_A                  = id_meas_raw_dq,
			.iq_meas_A                  = iq_meas_raw_dq,
			.omega_s_for_resonant_rad_s = omega_s_for_resonant_rad_s,
		};
		im_foc_control_output_t foc_output = {0};
		im_foc_control_step(&Global_Data.av, &Global_Data.rasv,
		                    &IM_config,
		                    &foc_input,
		                    omega_s_rad_s,
		                    observer_output.psi_r_mag,
		                    observer_output.theta_flux_rad,
		                    &foc_control_state,
		                    &foc_output);
		ud_pi_V      = foc_output.ud_pi;
		uq_pi_V      = foc_output.uq_pi;
		ud_decoup_V  = foc_output.ud_decoup;
		uq_decoup_V  = foc_output.uq_decoup;
		ud_res_V     = foc_output.ud_res;
		uq_res_V     = foc_output.uq_res;
		iq_ref_A     = foc_output.iq_cmd_A;
	} else {
		im_uf_control_config_t vf_config = {
			.frequency_setpoint_Hz   = vf_frequency_setpoint_Hz,
			.ratio_V_per_Hz          = vf_ratio_V_per_Hz,
			.boost_voltage_V         = vf_boost_voltage_V,
			.max_frequency_Hz        = vf_max_frequency_Hz,
			.max_voltage_V           = vf_max_voltage_V,
			.frequency_ramp_Hz_per_s = vf_frequency_ramp_Hz_per_s,
		};
		(void)im_uf_control_step(&Global_Data.av, &Global_Data.rasv, &vf_config, &uf_control_state);
		vf_voltage_magnitude_V = uf_control_state.applied_voltage_magnitude_V;
		im_foc_control_reset(&foc_control_state);
	}
}

static void current_control_VA() {
	// calculate reference voltages for current control
	v_dq_ref_VA = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_VA, Global_Data.rasv.i_dq_ref_VA, i_dq_VA, Global_Data.av.VA_vdc, Global_Data.av.VA_omega_mech*Global_Data.av.VA_polepairs);
	Global_Data.av.VA_vd = v_dq_ref_VA.d;
	Global_Data.av.VA_vq = v_dq_ref_VA.q;
	Global_Data.av.VA_theta_elec_advanced =  Global_Data.av.VA_theta_elec + (1.5f * (Global_Data.av.VA_omega_mech*Global_Data.av.VA_polepairs) * (1.0f / (UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)));
	dutycyc_VA = uz_Space_Vector_Modulation(v_dq_ref_VA, Global_Data.av.VA_vdc, Global_Data.av.VA_theta_elec_advanced);
	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_VA.DutyCycle_A;
	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_VA.DutyCycle_B;
	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_VA.DutyCycle_C;
};

static void speed_control_VA() {
	// filter speed setpoint signal
	Global_Data.rasv.n_ref_filt_VA = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_VA, Global_Data.rasv.n_ref_VA);
	// calculate reference torque from speed ctrl of VA motor
	Global_Data.rasv.M_ref_VA = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_VA, Global_Data.av.VA_omega_mech, Global_Data.rasv.n_ref_filt_VA);
	// calculate current setpoints i_dq_ref for VA motor
	Global_Data.rasv.i_dq_ref_VA = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_VA, Global_Data.av.VA_omega_mech, Global_Data.rasv.M_ref_VA, Global_Data.av.VA_vdc, i_dq_VA);
	current_control_VA();
};

void rr_profile(void)
{
	static uint64_t old_uptime = 0U;
	static bool rr_profile_was_active = false;
	uint32_t active_index = 0U;
	uint32_t setpoint_count = 0U;
	uint64_t current_uptime = 0U;

	if (!Global_Data.rr_profile.select_automatic_idiq) {
		Global_Data.rr_profile.start_marker = 0.0f;
		Global_Data.rr_profile.setpoints_from_javascope = true;
		rr_profile_was_active = false;
		return;
	}

	if (!rr_profile_was_active) {
		Global_Data.rr_profile.setpoint_index = 0U;
		Global_Data.rr_profile.start_marker = 1.0f;
		Global_Data.rr_profile.setpoints_from_javascope = false;
		use_speed_control = true;
		old_uptime = uz_SystemTime_GetInterruptCounter();
		rr_profile_was_active = true;
	}

	if (use_speed_control) {
		setpoint_count = UZ_ARRAY_SIZE(speed_setpoints);
	} else {
		uint32_t const id_count = UZ_ARRAY_SIZE(id_setpoints);
		uint32_t const iq_count = UZ_ARRAY_SIZE(iq_setpoints);
		setpoint_count = (id_count < iq_count) ? id_count : iq_count;
	}

	if (setpoint_count == 0U) {
		Global_Data.rr_profile.select_automatic_idiq = false;
		Global_Data.rr_profile.setpoints_from_javascope = true;
		Global_Data.rr_profile.start_marker = 0.0f;
		Global_Data.rr_profile.dut_reference_currents_in_A.d = 0.0f;
		Global_Data.rr_profile.dut_reference_currents_in_A.q = 0.0f;
		id_ref_A = 0.0f;
		iq_ref_A = 0.0f;
		speed_ref_rpm = 0.0f;
		rr_profile_was_active = false;
		return;
	}

	if (Global_Data.rr_profile.setpoint_index >= setpoint_count) {
		Global_Data.rr_profile.setpoint_index = 0U;
	}
	active_index = Global_Data.rr_profile.setpoint_index;

	if (use_speed_control) {
		speed_ref_rpm = speed_setpoints[active_index];
	} else {
		Global_Data.rr_profile.dut_reference_currents_in_A.d =
			RR_ID_SCALE * id_setpoints[active_index];
		Global_Data.rr_profile.dut_reference_currents_in_A.q =
			RR_IQ_SCALE * iq_setpoints[active_index];
		id_ref_A = Global_Data.rr_profile.dut_reference_currents_in_A.d;
		iq_ref_A = Global_Data.rr_profile.dut_reference_currents_in_A.q;
	}

	current_uptime = uz_SystemTime_GetInterruptCounter();
	if (current_uptime > (old_uptime + PROFILE_SETPOINT_DURATION_IN_ISR_TICKS)) {
		old_uptime = current_uptime;
		Global_Data.rr_profile.setpoint_index++;

		if (Global_Data.rr_profile.setpoint_index >= setpoint_count) {
			Global_Data.rr_profile.setpoint_index = 0U;
			Global_Data.rr_profile.select_automatic_idiq = false;
			Global_Data.rr_profile.setpoints_from_javascope = true;
			Global_Data.rr_profile.start_marker = 0.0f;
			Global_Data.rr_profile.dut_reference_currents_in_A.d = 0.0f;
			Global_Data.rr_profile.dut_reference_currents_in_A.q = 0.0f;
			id_ref_A = 0.0f;
			iq_ref_A = 0.0f;
			speed_ref_rpm = 0.0f;
			ultrazohm_state_machine_set_stop(true);
			rr_profile_was_active = false;
		}
	}
}
static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU GIC: Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}
