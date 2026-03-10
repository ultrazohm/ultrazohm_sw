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
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include "../include/javascope.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../include/uz_platform_state_machine.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_IM_config/uz_IM_config.h"
#include "../include/measurement_calibration.h"
#include "../include/error_checks.h"
#include "../include/im_observer.h"
#include "../include/im_uf_control.h"
#include "../include/im_foc_control.h"
#include "../include/motor_config.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void isr_init_dc_link_voltage_filter(DS_Data *data);
static void isr_filter_dc_link_voltage(DS_Data *data);
static void isr_update_estimated_power(float u_a, float u_b, float u_c, const im_rotor_flux_observer_output_t *observer_output);

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------

static error_checks_config_t error_checks_config = {
    .vdc_max = MOTOR_Vdc_max_V,
    .iphase_max = MOTOR_Iphase_max_A,
    .max_mechanical_speed_rpm = MOTOR_Speed_max_rpm
};

static uint32_t const measurement_calibration_sample_counter_stop = 10000U;
static float const measurement_calibration_u_dc_offset = 2.5f;
static measurement_calibration_t measurement_calibration_state = {0};

static uz_IIR_Filter_t *dc_link_voltage_filter = NULL;
static float const dc_link_voltage_filter_cutoff_Hz = 2000.0f;

float const duty_offset = 0.5f;

// V/f Control Parameters for 2-pole induction motor (1 pole pair)
float vf_frequency_setpoint_Hz = 20.0f;      // Start frequency (Hz) - start low! (10Hz = 600 RPM sync speed)
float vf_ratio_V_per_Hz = 5.0f;              // V/f ratio - ADJUST FOR YOUR MOTOR (e.g., 400V/50Hz = 8 V/Hz)
float vf_boost_voltage_V = 5.0f;             // Low-frequency boost voltage (V)
float vf_max_frequency_Hz = 50.0f;           // Maximum frequency limit (Hz) - 50Hz = 3000 RPM synchronous speed
float vf_max_voltage_V = 400.0f;             // Maximum voltage limit (V) - should be < DC-link voltage
float vf_frequency_ramp_Hz_per_s = 5.0f;     // Frequency slew rate for enable and setpoint changes
static im_uf_control_state_t uf_control_state = {0};

// Induction machine parameters — change motor_config.h to adapt to a new machine
uz_IM_t IM_config = {
    .Rs_Ohm          = MOTOR_Rs_Ohm,
    .Rr_Ohm          = MOTOR_Rr_Ohm,
    .Lsigma_s_Henry  = MOTOR_Lsigma_s_H,
    .Lsigma_r_Henry  = MOTOR_Lsigma_r_H,
    .Lm_Henry        = MOTOR_Lm_H,
    .polePairs       = MOTOR_PolePairs,
    .J_kg_m_squared  = MOTOR_J_kgm2,
    .I_max_Ampere    = MOTOR_I_max_A,
    .Psi_rated_Vs    = MOTOR_Psi_rated_Vs,
};

static im_rotor_flux_observer_state_t rotor_flux_observer_state = {0};

// Kalman Filter observer — selectable alternative to the rotor flux observer
bool use_kalman_filter = false;
static im_kf_observer_state_t kf_observer_state = {
    .x = {0.0f, 0.0f, 0.0f, 0.0f},
    .P = {{1.0f, 0.0f, 0.0f, 0.0f},
          {0.0f, 1.0f, 0.0f, 0.0f},
          {0.0f, 0.0f, 1.0f, 0.0f},
          {0.0f, 0.0f, 0.0f, 1.0f}}
};
static uz_IM_ss_t im_ss = {0};
static bool im_ss_computed = false;

// Estimated stator current fundamental frequency (Hz)
float stator_current_fundamental_frequency_Hz = 0.0f;
// Observer outputs exposed for fast-data logging
float psi_r_mag_Vs = 0.0f;
float omega_s_rad_s = 0.0f;
// Deterministic observer flux components — diagnostic: check for 257 Hz oscillation in theta
float det_psi_r_alpha = 0.0f;
float det_psi_r_beta  = 0.0f;
// Det observer PLL omega_s — always updated, used for resonant controller frequency.
// Much smoother than KF slip-estimate omega_s (std ≈ 0.056 vs 0.37 rad/s).
float det_omega_s_rad_s = 0.0f;

// Minimum on-time (duty cycle fraction, 0–0.1) — settable at runtime via Send Field 16.
// Mirrors the hardware PWM IP clamp; also used in the KF voltage model (lines below).
float min_pulse_width = UZ_MIN_PULSE_WIDTH;

// KF tuning — initialized from uz_global_configuration.h and modifiable at runtime
// via send fields 9 (Q_i), 7 (Q_psi), 8 (R_i).
// R_i >> 6th-harmonic current variance (~0.029 A²) so KF trusts model over measurements
// Q_psi << R_i: flux changes slowly (Rr/Lr·Ts ≈ 2.8e-4/step), tau_r = 0.145 s
// Q_i: residual unmodeled current dynamics (e.g. deadtime steps)
float kf_q_i   = MOTOR_KF_Q_i;
float kf_q_psi = MOTOR_KF_Q_psi;
float kf_r_i   = MOTOR_KF_R_i;

// KF diagnostics for JavaScope (populated after each KF step)
float kf_innov_alpha = 0.0f;
float kf_innov_beta  = 0.0f;
float kf_S_00        = 0.0f;
float kf_S_11        = 0.0f;
float kf_K_00        = 0.0f;
float kf_K_11        = 0.0f;

// FOC control mode (false = V/f, true = FOC)
bool use_foc = false;
bool use_speed_control = false;
bool use_resonant_6th = false;
float id_ref_A = 0.0f;
float iq_ref_A = 0.0f;
float speed_ref_rpm = 0.0f;
float RRC_Operating_Point = 1.0f;
float id_cmd = 0.0f;
float iq_cmd = 0.0f;
static im_foc_control_state_t foc_control_state = {0};

// Raw measured dq currents — abc→dq at active flux angle, updated every ISR regardless of mode.
// Used for JavaScope (always shows measured, not observer-estimated) and resonant controller.
float id_meas_raw_dq = 0.0f;
float iq_meas_raw_dq = 0.0f;

// FOC diagnostics — updated each ISR when FOC is active, held at last value otherwise
float ud_pi_V    = 0.0f;   // d-axis PI output (no decoupling): ≈ Rs*id at steady state
float uq_pi_V    = 0.0f;   // q-axis PI output (no decoupling): ≈ Rs*iq at steady state
float ud_decoup_V = 0.0f;  // d-axis feedforward: -omega_s * sigma_ls * iq
float uq_decoup_V = 0.0f;  // q-axis feedforward: omega_s * sigma_ls * id + omega_s*(Lm/Lr)*psi_r
float ud_res_V   = 0.0f;   // d-axis resonant controller output (zero when disabled)
float uq_res_V   = 0.0f;   // q-axis resonant controller output (zero when disabled)
float omega_slip_rad_s_diag = 0.0f;  // slip frequency = omega_s - omega_el (rotor)
float estimated_active_power_W = 0.0f;
float estimated_reactive_power_var = 0.0f;

void Initialize_ISR_Software(DS_Data *data)
{
    uz_assert_not_NULL(data);
    uz_assert(data->av.isr_samplerate_s > 0.0f);

    measurement_calibration_state = measurement_calibration_init(measurement_calibration_sample_counter_stop,
                                                                     measurement_calibration_u_dc_offset);
    im_uf_control_reset(&uf_control_state);
    kf_observer_state = (im_kf_observer_state_t){
        .x = {0.0f, 0.0f, 0.0f, 0.0f},
        .P = {{1.0f, 0.0f, 0.0f, 0.0f},
              {0.0f, 1.0f, 0.0f, 0.0f},
              {0.0f, 0.0f, 1.0f, 0.0f},
              {0.0f, 0.0f, 0.0f, 1.0f}}
    };
    isr_init_dc_link_voltage_filter(data);
    im_ss = uz_IM_ss_compute(IM_config, data->av.isr_samplerate_s);
    im_ss_computed = true;
    id_ref_A = uz_IM_get_id_ref_for_psi_r(IM_config, IM_config.Psi_rated_Vs);
    data->av.snd_fld[2] = id_ref_A;
    im_rotor_flux_observer_init(&IM_config, data->av.isr_samplerate_s, &rotor_flux_observer_state);
    im_foc_control_init(&IM_config, data->av.isr_samplerate_s, &foc_control_state);
    im_foc_control_reset(&foc_control_state);
}

void ISR_Control(void *data)
{
    (void)data;
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    measurement_calibration_step(&measurement_calibration_state, &Global_Data.aa, &Global_Data.av);
    isr_filter_dc_link_voltage(&Global_Data);
    error_checks_step(&Global_Data.av, &error_checks_config);

    // Apply runtime-tunable Q/R (overrides values set by uz_IM_ss_compute each ISR)
    if (im_ss_computed) {
        im_ss.Q_diag[0] = kf_q_i;
        im_ss.Q_diag[1] = kf_q_i;
        im_ss.Q_diag[2] = kf_q_psi;
        im_ss.Q_diag[3] = kf_q_psi;
        im_ss.R_diag[0] = kf_r_i;
        im_ss.R_diag[1] = kf_r_i;
    }

    // Phase voltages applied in the previous ISR step (read before control overwrites duty cycles).
    // Apply the same hardware min-pulse-width clamp that the FPGA PWM IP enforces,
    // so the KF voltage model matches the actual inverter output.
    float const u_a = (fmaxf(min_pulse_width, fminf(1.0f - min_pulse_width, Global_Data.rasv.halfBridge1DutyCycle)) - duty_offset) * Global_Data.av.U_DC;
    float const u_b = (fmaxf(min_pulse_width, fminf(1.0f - min_pulse_width, Global_Data.rasv.halfBridge2DutyCycle)) - duty_offset) * Global_Data.av.U_DC;
    float const u_c = (fmaxf(min_pulse_width, fminf(1.0f - min_pulse_width, Global_Data.rasv.halfBridge3DutyCycle)) - duty_offset) * Global_Data.av.U_DC;

    im_observer_result_t const obs = im_observer_step(
        &Global_Data.av, &IM_config, u_a, u_b, u_c,
        im_ss_computed && measurement_calibration_state.done,
        use_kalman_filter,
        &rotor_flux_observer_state, &im_ss, &kf_observer_state);
    im_rotor_flux_observer_output_t const observer_output = obs.output;
    det_psi_r_alpha   = obs.det_psi_r_alpha;
    det_psi_r_beta    = obs.det_psi_r_beta;
    det_omega_s_rad_s = obs.det_omega_s_rad_s;
    kf_innov_alpha    = obs.kf_innov_alpha;
    kf_innov_beta     = obs.kf_innov_beta;
    kf_S_00           = obs.kf_S_00;
    kf_S_11           = obs.kf_S_11;
    kf_K_00           = obs.kf_K_00;
    kf_K_11           = obs.kf_K_11;

    // Raw measured dq: abc measured currents rotated into the active flux frame.
    // Always updated — used for JavaScope display and resonant controller.
    {
        uz_3ph_abc_t const i_abc_raw = {.a = Global_Data.av.I_U,
                                        .b = Global_Data.av.I_V,
                                        .c = Global_Data.av.I_W};
        uz_3ph_dq_t const i_dq_raw = uz_transformation_3ph_abc_to_dq(i_abc_raw, observer_output.theta_flux_rad);
        id_meas_raw_dq = i_dq_raw.d;
        iq_meas_raw_dq = i_dq_raw.q;
    }

    Global_Data.av.I_d        = observer_output.i_d;
    Global_Data.av.I_q        = observer_output.i_q;
    Global_Data.av.theta_elec = observer_output.theta_elec_rad;
    stator_current_fundamental_frequency_Hz = observer_output.stator_current_fundamental_frequency_Hz;
    psi_r_mag_Vs = observer_output.psi_r_mag;
    omega_s_rad_s = 2.0f * (float)M_PI * observer_output.stator_current_fundamental_frequency_Hz;
    omega_slip_rad_s_diag = omega_s_rad_s - observer_output.omega_el_rad_s;
    isr_update_estimated_power(u_a, u_b, u_c, &observer_output);

    // Torque estimation: T_e = 1.5 * p * (Lm/Lr) * |psi_r| * i_q
    {
        float const lr = IM_config.Lsigma_r_Henry + IM_config.Lm_Henry;
        Global_Data.av.mechanicalTorque = 1.5f * IM_config.polePairs
                                        * (IM_config.Lm_Henry / lr)
                                        * observer_output.psi_r_mag * Global_Data.av.I_q;
    }

    platform_state_t current_state = ultrazohm_state_machine_get_state();

    if (current_state == control_state)
    {
        if (use_foc)
        {
            im_foc_control_input_t foc_input = {
                .use_speed_control = use_speed_control,
                .use_resonant_6th = use_resonant_6th,
                .id_ref_A = id_ref_A,
                .iq_ref_A = iq_ref_A,
                .speed_ref_rpm = speed_ref_rpm,
                .id_meas_A = id_meas_raw_dq,
                .iq_meas_A = iq_meas_raw_dq,
                .omega_s_for_resonant_rad_s = det_omega_s_rad_s
            };
            im_foc_control_output_t foc_output = {0};
            im_foc_control_step(&Global_Data.av, &Global_Data.rasv,
                                 &IM_config,
                                 &foc_input,
                                 omega_s_rad_s,  // stator frequency (IM needs omega_s, not omega_r)
                                 observer_output.psi_r_mag,
                                 observer_output.theta_flux_rad,
                                 &foc_control_state,
                                 &foc_output);
            id_cmd = foc_output.id_cmd_A;
            iq_cmd = foc_output.iq_cmd_A;
            ud_pi_V     = foc_output.ud_pi;
            uq_pi_V     = foc_output.uq_pi;
            ud_decoup_V  = foc_output.ud_decoup;
            uq_decoup_V  = foc_output.uq_decoup;
            ud_res_V     = foc_output.ud_res;
            uq_res_V     = foc_output.uq_res;
        }
        else
        {
            id_cmd = 0.0f;
            iq_cmd = 0.0f;
            im_uf_control_config_t vf_config = {
                .frequency_setpoint_Hz = vf_frequency_setpoint_Hz,
                .ratio_V_per_Hz = vf_ratio_V_per_Hz,
                .boost_voltage_V = vf_boost_voltage_V,
                .max_frequency_Hz = vf_max_frequency_Hz,
                .max_voltage_V = vf_max_voltage_V,
                .frequency_ramp_Hz_per_s = vf_frequency_ramp_Hz_per_s
            };
            (void)im_uf_control_step(&Global_Data.av, &Global_Data.rasv, &vf_config, &uf_control_state, duty_offset);
            im_foc_control_reset(&foc_control_state);
        }

        // Enable inverter
        Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    }
    else
    {
        id_cmd = 0.0f;
        iq_cmd = 0.0f;
        im_uf_control_reset(&uf_control_state);
        // Disable PWM outputs when not in control state
        Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge7DutyCycle = 1.0f;

        im_foc_control_reset(&foc_control_state);
    }

    // Store abc duty cycles for JavaScope (JSO_ua/ub/uc)
    Global_Data.av.U_U = Global_Data.rasv.halfBridge1DutyCycle;
    Global_Data.av.U_V = Global_Data.rasv.halfBridge2DutyCycle;
    Global_Data.av.U_W = Global_Data.rasv.halfBridge3DutyCycle;

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);

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

static void isr_init_dc_link_voltage_filter(DS_Data *data)
{
    uz_assert_not_NULL(data);
    uz_assert(data->av.isr_samplerate_s > 0.0f);

    if (dc_link_voltage_filter == NULL) {
        struct uz_IIR_Filter_config const filter_config = {
            .selection = LowPass_first_order,
            .cutoff_frequency_Hz = dc_link_voltage_filter_cutoff_Hz,
            .sample_frequency_Hz = 1.0f / data->av.isr_samplerate_s
        };
        dc_link_voltage_filter = uz_signals_IIR_Filter_init(filter_config);
    }
}

static void isr_update_estimated_power(float u_a, float u_b, float u_c, const im_rotor_flux_observer_output_t *observer_output)
{
    uz_assert_not_NULL(observer_output);

    uz_3ph_abc_t const u_abc = {
        .a = u_a,
        .b = u_b,
        .c = u_c
    };
    uz_3ph_dq_t const u_dq = uz_transformation_3ph_abc_to_dq(u_abc, observer_output->theta_flux_rad);

    // Estimate electrical power from the actually applied stator voltage and observer currents.
    estimated_active_power_W = 1.5f * ((u_dq.d * observer_output->i_d) + (u_dq.q * observer_output->i_q));
    estimated_reactive_power_var = 1.5f * ((u_dq.q * observer_output->i_d) - (u_dq.d * observer_output->i_q));
}

static void isr_filter_dc_link_voltage(DS_Data *data)
{
    uz_assert_not_NULL(data);
    uz_assert_not_NULL(dc_link_voltage_filter);
    data->av.U_DC = uz_signals_IIR_Filter_sample(dc_link_voltage_filter, data->av.U_DC);
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



