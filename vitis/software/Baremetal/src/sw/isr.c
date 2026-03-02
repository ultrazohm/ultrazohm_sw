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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_IM_config/uz_IM_config.h"  // uz_IM_t struct only (functions need .c added to build)
#include "../uz/uz_math_constants.h"
#include "../uz/uz_piController/uz_piController.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_pos_to_speed_pll/uz_pos_to_speed_pll.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------

// safety thresholds
float Vdc_max = 1100.0f;
float Iphase_max = 30.0f;

// Error reason bitmask (set in ISR, read from main loop)
volatile uint32_t isr_error_reason = 0U;
#define ERR_OVERVOLTAGE_DC   (1U << 0)
#define ERR_OVERCURRENT_U    (1U << 1)
#define ERR_OVERCURRENT_V    (1U << 2)
#define ERR_OVERCURRENT_W    (1U << 3)
#define ERR_OVERSPEED        (1U << 4)
#define ERR_NAN_OBSERVER     (1U << 5)
#define ERR_NAN_MEASUREMENT  (1U << 6)

float const duty_offset 		=   0.5f;
uz_3ph_abc_t three_phase_sine;

int isr_use_sinwave_gen = 1;

int calibrate_current_measurement_done = 0;
int calibrate_current_measurement_counter = 0;
int calibrate_current_measurement_counter_stop = 1000;

//zeroing for current value 0 (getting rid of the offset)
double totalU = 0;
double totalV = 0;
double totalW = 0;

float I_U_offset;
float I_V_offset;
float I_W_offset;
float U_DC_offset = 2.5f;

// V/f Control Parameters for 2-pole induction motor (1 pole pair)
float vf_frequency_setpoint_Hz = 20.0f;      // Start frequency (Hz) - start low! (10Hz = 600 RPM sync speed)
float vf_ratio_V_per_Hz = 5.0f;              // V/f ratio - ADJUST FOR YOUR MOTOR (e.g., 400V/50Hz = 8 V/Hz)
float vf_boost_voltage_V = 5.0f;             // Low-frequency boost voltage (V)
float vf_max_frequency_Hz = 50.0f;           // Maximum frequency limit (Hz) - 50Hz = 3000 RPM synchronous speed
float vf_max_voltage_V = 400.0f;             // Maximum voltage limit (V) - should be < DC-link voltage
float vf_frequency_ramp_Hz_per_s = 5.0f;     // Frequency slew rate for enable and setpoint changes
static float vf_frequency_command_Hz = 0.0f;
static float vf_electrical_phase_rad = 0.0f;

// Induction machine parameters — set to your motor values!
uz_IM_t IM_config = {
    .Rs_Ohm = 2.1f,
    .Rr_Ohm = 2.4f,
    .Lsigma_s_Henry = 10e-3f,
    .Lsigma_r_Henry = 10e-3f,    // assumed equal to stator leakage
    .Lm_Henry = 340e-3f,
    .polePairs = 1.0f,
    .J_kg_m_squared = 0.01f,
    .I_max_Ampere = 10.0f,
    .Psi_rated_Vs = 0.85f,
};

// Rotor flux observer state (alpha-beta frame)
static float psi_r_alpha = 0.0f;
static float psi_r_beta = 0.0f;
static float theta_flux_rad = 0.0f;
static float psi_r_mag = 0.0f;

// Estimated stator current fundamental frequency (Hz)
float stator_current_fundamental_frequency_Hz = 0.0f;
static uz_pos_to_speed_pll_t* stator_frequency_pll = NULL;

// FOC control mode (false = V/f, true = FOC)
bool use_foc = false;
bool use_speed_control = false;
float id_ref_A = 0.0f;
float iq_ref_A = 0.0f;
float speed_ref_rpm = 0.0f;
float RRC_Operating_Point = 1.0f;
float id_cmd = 0.0f;
float iq_cmd = 0.0f;
static uz_PI_Controller* PI_id = NULL;
static uz_PI_Controller* PI_iq = NULL;
static uz_PI_Controller* PI_speed = NULL;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    if(!calibrate_current_measurement_done)
    {
        totalU += Global_Data.aa.A1.me.ADC_A1;
		totalV += Global_Data.aa.A1.me.ADC_A2;
		totalW += Global_Data.aa.A1.me.ADC_A3;

        calibrate_current_measurement_counter++;
		if(calibrate_current_measurement_counter==calibrate_current_measurement_counter_stop)
		{
			I_U_offset = totalU/calibrate_current_measurement_counter_stop;
			I_V_offset = totalV/calibrate_current_measurement_counter_stop;
			I_W_offset = totalW/calibrate_current_measurement_counter_stop;
			calibrate_current_measurement_done = 1;
		}
	}

    Global_Data.av.U_DC = Global_Data.aa.A1.me.ADC_A4  - U_DC_offset;
    Global_Data.av.I_U  = Global_Data.aa.A1.me.ADC_A1  - I_U_offset; //including adjustment upwards by the offset
    Global_Data.av.I_V  = Global_Data.aa.A1.me.ADC_A2  - I_V_offset; //including adjustment upwards by the offset
    Global_Data.av.I_W  = Global_Data.aa.A1.me.ADC_A3  - I_W_offset; //including adjustment upwards by the offset

    /* --- limit checks ------------------------------------------------------- */
    // NaN defeats float comparisons (NaN > x is always false), so check explicitly
    bool nan_meas = !isfinite(Global_Data.av.U_DC) || !isfinite(Global_Data.av.I_U)
                 || !isfinite(Global_Data.av.I_V) || !isfinite(Global_Data.av.I_W)
                 || !isfinite(Global_Data.av.mechanicalRotorSpeed);
    bool ov_dc  =  Global_Data.av.U_DC          > Vdc_max;     // over-voltage (DC link)
    bool oc_IU  =  fabsf(Global_Data.av.I_U)    > Iphase_max;  // over-current phase U
    bool oc_IV  =  fabsf(Global_Data.av.I_V)    > Iphase_max;  // over-current phase V
    bool oc_IW  =  fabsf(Global_Data.av.I_W)    > Iphase_max;  // over-current phase W
    bool overspeed = fabsf(Global_Data.av.mechanicalRotorSpeed) > 3500.0f; // overspeed (3500 RPM)

    /* --- act on any error --------------------------------------------------- */
    if (ov_dc || oc_IU || oc_IV || oc_IW || overspeed || nan_meas) {
        if (ov_dc)     isr_error_reason |= ERR_OVERVOLTAGE_DC;
        if (oc_IU)     isr_error_reason |= ERR_OVERCURRENT_U;
        if (oc_IV)     isr_error_reason |= ERR_OVERCURRENT_V;
        if (oc_IW)     isr_error_reason |= ERR_OVERCURRENT_W;
        if (overspeed) isr_error_reason |= ERR_OVERSPEED;
        if (nan_meas)  isr_error_reason |= ERR_NAN_MEASUREMENT;
        ultrazohm_state_machine_set_error(true);
    }

    /* --- Rotor flux observer (current model, runs every ISR cycle) -------- */
    float omega_el_rad_s;
    {
        float const Ts = Global_Data.av.isr_samplerate_s;
        float const Lr = IM_config.Lsigma_r_Henry + IM_config.Lm_Henry;
        float const tau_r = Lr / IM_config.Rr_Ohm;
        float const one_over_tau_r = 1.0f / tau_r;
        float const Lm_over_tau_r = IM_config.Lm_Henry * one_over_tau_r;

        // ABC -> alpha-beta (stator currents)
        uz_3ph_abc_t i_abc = {.a = Global_Data.av.I_U, .b = Global_Data.av.I_V, .c = Global_Data.av.I_W};
        uz_3ph_alphabeta_t i_ab = uz_transformation_3ph_abc_to_alphabeta(i_abc);

        // Electrical rotor speed from encoder [RPM -> rad/s electrical]
        omega_el_rad_s = Global_Data.av.mechanicalRotorSpeed * (2.0f * UZ_PIf / 60.0f) * IM_config.polePairs;

        // Forward-Euler integration of rotor flux
        float dpsi_alpha = Lm_over_tau_r * i_ab.alpha - one_over_tau_r * psi_r_alpha - omega_el_rad_s * psi_r_beta;
        float dpsi_beta  = Lm_over_tau_r * i_ab.beta  - one_over_tau_r * psi_r_beta  + omega_el_rad_s * psi_r_alpha;
        psi_r_alpha += Ts * dpsi_alpha;
        psi_r_beta  += Ts * dpsi_beta;

        // Rotor flux angle and magnitude
        theta_flux_rad = atan2f(psi_r_beta, psi_r_alpha);
        psi_r_mag = sqrtf(psi_r_alpha * psi_r_alpha + psi_r_beta * psi_r_beta);

        // NaN/Inf guard: forward Euler can diverge from encoder glitches
        if (!isfinite(psi_r_alpha) || !isfinite(psi_r_beta) ||
            !isfinite(theta_flux_rad) || !isfinite(psi_r_mag)) {
            psi_r_alpha = 0.0f;
            psi_r_beta  = 0.0f;
            theta_flux_rad = 0.0f;
            psi_r_mag = 0.0f;
            isr_error_reason |= ERR_NAN_OBSERVER;
            ultrazohm_state_machine_set_error(true);
        }

        // Estimate stator current fundamental frequency from rotor flux angle via PLL
        if (stator_frequency_pll == NULL) {
            struct uz_pos_to_speed_pll_config_t pll_cfg = {
                .machine_polepairs = fmaxf(IM_config.polePairs, 1.0e-3f),
                .kp_pll = 628.3185f,
                .ki_pll = 98696.0f,
                .sampling_time_in_seconds = fmaxf(Ts, 1.0e-6f),
            };
            stator_frequency_pll = uz_pos_to_speed_pll_init(pll_cfg);
        }
        if (stator_frequency_pll != NULL) {
            float theta_flux_wrapped = theta_flux_rad;
            if (theta_flux_wrapped < 0.0f) {
                theta_flux_wrapped += 2.0f * UZ_PIf;
            }
            theta_flux_wrapped = fminf(fmaxf(theta_flux_wrapped, 0.0f), 2.0f * UZ_PIf);
            uz_pos_to_speed_pll_step(stator_frequency_pll, theta_flux_wrapped);
            float const omega_el_pll_rad_s = uz_pos_to_speed_pll_get_omega_el_si(stator_frequency_pll);
            stator_current_fundamental_frequency_Hz = fabsf(omega_el_pll_rad_s) / (2.0f * UZ_PIf);
            if (!isfinite(stator_current_fundamental_frequency_Hz)) {
                stator_current_fundamental_frequency_Hz = 0.0f;
            }
        }

        // ABC -> DQ in rotor flux frame
        uz_3ph_dq_t i_dq = uz_transformation_3ph_abc_to_dq(i_abc, theta_flux_rad);
        Global_Data.av.I_d = i_dq.d;
        Global_Data.av.I_q = i_dq.q;
        Global_Data.av.theta_elec = theta_flux_rad;
    }

    // Torque estimation: T_e = 1.5 * p * (Lm/Lr) * |psi_r| * i_q
    {
        float Lr = IM_config.Lsigma_r_Henry + IM_config.Lm_Henry;
        Global_Data.av.mechanicalTorque = 1.5f * IM_config.polePairs
                                        * (IM_config.Lm_Henry / Lr)
                                        * psi_r_mag * Global_Data.av.I_q;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    bool const vf_active = (current_state == control_state) && (!use_foc);

    if (!vf_active) {
        // Keep current command through brief non-V/f phases to avoid
        // a drop-before-rise behavior on setpoint changes.
        vf_frequency_command_Hz = fminf(fmaxf(vf_frequency_command_Hz, 0.0f), vf_max_frequency_Hz);
    }

    if(current_state==control_state)
    {
        if (use_foc)
        {
            /* --- FOC current control ---------------------------------------- */

            // Lazy-init PI controllers (once)
            if (PI_id == NULL) {
                float Ls = IM_config.Lsigma_s_Henry + IM_config.Lm_Henry;
                float Lr = IM_config.Lsigma_r_Henry + IM_config.Lm_Henry;
                float sigma = 1.0f - (IM_config.Lm_Henry * IM_config.Lm_Henry) / (Ls * Lr);
                float sigma_Ls = sigma * Ls;
                float Ts = Global_Data.av.isr_samplerate_s;
                // Bandwidth-based tuning: Kp = sigma*Ls / (2*Ts), Ki = Rs / (2*Ts)
                float Kp = sigma_Ls / (2.0f * Ts) * 0.1;
                float Ki = IM_config.Rs_Ohm / (2.0f * Ts) * 0.2;
                struct uz_PI_Controller_config pi_cfg = {
                    .type = UZ_PI_PARALLEL,
                    .Kp = Kp,
                    .Ki = Ki,
                    .samplingTime_sec = Ts,
                    .upper_limit = 400.0f,
                    .lower_limit = -400.0f,
                };
                PI_id = uz_PI_Controller_init(pi_cfg);
                PI_iq = uz_PI_Controller_init(pi_cfg);

                // Speed controller: output is iq reference, limited to I_max
                struct uz_PI_Controller_config speed_cfg = {
                    .type = UZ_PI_PARALLEL,
                    .Kp = 0.05f,
                    .Ki = .50f,
                    .samplingTime_sec = Ts,
                    .upper_limit = IM_config.I_max_Ampere,
                    .lower_limit = -IM_config.I_max_Ampere,
                };
                PI_speed = uz_PI_Controller_init(speed_cfg);
            }

            // Determine iq reference: speed control or direct current control
            id_cmd = id_ref_A;
            if (use_speed_control) {
                iq_cmd = uz_PI_Controller_sample(PI_speed, speed_ref_rpm, Global_Data.av.mechanicalRotorSpeed, false);
            } else {
                iq_cmd = iq_ref_A;
                if (PI_speed != NULL) uz_PI_Controller_reset(PI_speed);
            }

            // PI current controllers
            float ud_pi = uz_PI_Controller_sample(PI_id, id_ref_A, Global_Data.av.I_d, false);
            float uq_pi = uz_PI_Controller_sample(PI_iq, iq_cmd, Global_Data.av.I_q, false);

            // IM decoupling feedforward
            float Ls = IM_config.Lsigma_s_Henry + IM_config.Lm_Henry;
            float Lr = IM_config.Lsigma_r_Henry + IM_config.Lm_Henry;
            float sigma = 1.0f - (IM_config.Lm_Henry * IM_config.Lm_Henry) / (Ls * Lr);
            float sigma_Ls = sigma * Ls;
            float ud_decoup = -omega_el_rad_s * sigma_Ls * Global_Data.av.I_q;
            float uq_decoup =  omega_el_rad_s * sigma_Ls * Global_Data.av.I_d
                              + omega_el_rad_s * (IM_config.Lm_Henry / Lr) * psi_r_mag;

            uz_3ph_dq_t v_dq_ref = {
                .d = ud_pi + ud_decoup,
                .q = uq_pi + uq_decoup,
                .zero = 0.0f
            };

            // Store dq reference voltages
            Global_Data.av.U_d = v_dq_ref.d;
            Global_Data.av.U_q = v_dq_ref.q;

            // SVM: dq → duty cycles
            struct uz_DutyCycle_t duty = uz_Space_Vector_Modulation(v_dq_ref, Global_Data.av.U_DC, theta_flux_rad);
            Global_Data.rasv.halfBridge1DutyCycle = duty.DutyCycle_A;
            Global_Data.rasv.halfBridge2DutyCycle = duty.DutyCycle_B;
            Global_Data.rasv.halfBridge3DutyCycle = duty.DutyCycle_C;

            // Store abc reference voltages for JavaScope (JSO_ua/ub/uc)
//            uz_3ph_abc_t v_abc_ref = uz_transformation_3ph_dq_to_abc(v_dq_ref, theta_flux_rad);
//            Global_Data.av.U_U = v_abc_ref.a;
//            Global_Data.av.U_V = v_abc_ref.b;
//            Global_Data.av.U_W = v_abc_ref.c;
        }
        else
        {
            /* --- V/f open-loop control -------------------------------------- */
            id_cmd = 0.0f;
            iq_cmd = 0.0f;

            // Slew-limited V/f frequency command: used on enable and on setpoint updates
            float const Ts = fmaxf(Global_Data.av.isr_samplerate_s, 1.0e-6f);
            float freq_target_limited = fminf(fmaxf(vf_frequency_setpoint_Hz, 0.0f), vf_max_frequency_Hz);
            float const freq_step_max = fmaxf(vf_frequency_ramp_Hz_per_s, 0.1f) * Ts;
            float const freq_error = freq_target_limited - vf_frequency_command_Hz;
            if (freq_error > freq_step_max) {
                vf_frequency_command_Hz += freq_step_max;
            } else if (freq_error < -freq_step_max) {
                vf_frequency_command_Hz -= freq_step_max;
            } else {
                vf_frequency_command_Hz = freq_target_limited;
            }

            // Limit frequency to maximum
            float freq_limited = vf_frequency_command_Hz;

            // V/f with boost: add boost only when frequency is above standstill
            float boost_voltage_V = (freq_limited > 0.1f) ? vf_boost_voltage_V : 0.0f;
            float voltage_magnitude_V = (vf_ratio_V_per_Hz * freq_limited) + boost_voltage_V;
            voltage_magnitude_V = fminf(voltage_magnitude_V, vf_max_voltage_V);

            // Normalize voltage to DC-link to get duty cycle amplitude
            float duty_amplitude_vf = voltage_magnitude_V / fmaxf(Global_Data.av.U_DC, 1.0f);
            duty_amplitude_vf = fminf(duty_amplitude_vf, 0.45f);
            duty_amplitude_vf = fmaxf(duty_amplitude_vf, 0.0f);

            // Generate three-phase voltage with phase integration.
            // Do not use angle = 2*pi*t*f when f is ramped, because that causes
            // frequency distortion for time-varying f.
            float const omega_cmd_rad_per_s = 2.0f * UZ_PIf * freq_limited;
            vf_electrical_phase_rad += omega_cmd_rad_per_s * Ts;
            vf_electrical_phase_rad = fmodf(vf_electrical_phase_rad, 2.0f * UZ_PIf);
            if (vf_electrical_phase_rad < 0.0f) {
                vf_electrical_phase_rad += 2.0f * UZ_PIf;
            }

            float v1 = duty_amplitude_vf * sinf(vf_electrical_phase_rad) + duty_offset;
            float v2 = duty_amplitude_vf * sinf(vf_electrical_phase_rad - (2.0f * UZ_PIf / 3.0f)) + duty_offset;
            float v3 = duty_amplitude_vf * sinf(vf_electrical_phase_rad - (4.0f * UZ_PIf / 3.0f)) + duty_offset;

            int PWM_mode = 0; // 0 SPWM // 1 Negative-DPWM // 2 Positive-Negative DPWM

            if (PWM_mode == 1) {

            float const cm = fminf(fminf(v1, v2), v3);
            v1 -= cm;
            v2 -= cm;
            v3 -= cm;
            }

            v1 = fminf(fmaxf(v1, 0.0f), 1.0f);
            v2 = fminf(fmaxf(v2, 0.0f), 1.0f);
            v3 = fminf(fmaxf(v3, 0.0f), 1.0f);
            three_phase_sine = (uz_3ph_abc_t){ .a = v1, .b = v2, .c = v3 };

            Global_Data.rasv.halfBridge1DutyCycle = three_phase_sine.a;
            Global_Data.rasv.halfBridge2DutyCycle = three_phase_sine.b;
            Global_Data.rasv.halfBridge3DutyCycle = three_phase_sine.c;

            // Reset PI integrators so FOC starts clean on switch
            if (PI_id != NULL) uz_PI_Controller_reset(PI_id);
            if (PI_iq != NULL) uz_PI_Controller_reset(PI_iq);
            if (PI_speed != NULL) uz_PI_Controller_reset(PI_speed);
        }

        // Enable inverter
        Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    }
    else
    {
        id_cmd = 0.0f;
        iq_cmd = 0.0f;
        vf_frequency_command_Hz = 0.0f;
        vf_electrical_phase_rad = 0.0f;
        // Disable PWM outputs when not in control state
        Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge7DutyCycle = 1.0f;

        // Reset PI integrators
        if (PI_id != NULL) uz_PI_Controller_reset(PI_id);
        if (PI_iq != NULL) uz_PI_Controller_reset(PI_iq);
        if (PI_speed != NULL) uz_PI_Controller_reset(PI_speed);
    }

    // Store abc duty cycles for JavaScope (JSO_ua/ub/uc)
    Global_Data.av.U_U = Global_Data.rasv.halfBridge1DutyCycle;
    Global_Data.av.U_V = Global_Data.rasv.halfBridge2DutyCycle;
    Global_Data.av.U_W = Global_Data.rasv.halfBridge3DutyCycle;

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
 //   PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
 //                       Global_Data.rasv.halfBridge2DutyCycle,
 //                       Global_Data.rasv.halfBridge3DutyCycle);
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



