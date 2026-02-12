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
float vf_frequency_setpoint_Hz = 5.0f;      // Start frequency (Hz) - start low! (10Hz = 600 RPM sync speed)
float vf_ratio_V_per_Hz = 8.0f;              // V/f ratio - ADJUST FOR YOUR MOTOR (e.g., 400V/50Hz = 8 V/Hz)
float vf_boost_voltage_V = 10.0f;            // Low-frequency voltage boost (V) to overcome stator resistance
float vf_max_frequency_Hz = 50.0f;           // Maximum frequency limit (Hz) - 50Hz = 3000 RPM synchronous speed
float vf_max_voltage_V = 400.0f;             // Maximum voltage limit (V) - should be < DC-link voltage

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
    bool ov_dc  =  Global_Data.av.U_DC          > Vdc_max;     // over-voltage (DC link)
    bool oc_IU  =  fabsf(Global_Data.av.I_U)    > Iphase_max;  // over-current phase U
    bool oc_IV  =  fabsf(Global_Data.av.I_V)    > Iphase_max;  // over-current phase V
    bool oc_IW  =  fabsf(Global_Data.av.I_W)    > Iphase_max;  // over-current phase W

    /* --- act on any error --------------------------------------------------- */
    if (ov_dc || oc_IU || oc_IV || oc_IW) {
        ultrazohm_state_machine_set_error(true);
    }

    /* --- Rotor flux observer (current model, runs every ISR cycle) -------- */
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
        float omega_el = Global_Data.av.mechanicalRotorSpeed * (2.0f * UZ_PIf / 60.0f) * IM_config.polePairs;

        // Forward-Euler integration of rotor flux
        float dpsi_alpha = Lm_over_tau_r * i_ab.alpha - one_over_tau_r * psi_r_alpha - omega_el * psi_r_beta;
        float dpsi_beta  = Lm_over_tau_r * i_ab.beta  - one_over_tau_r * psi_r_beta  + omega_el * psi_r_alpha;
        psi_r_alpha += Ts * dpsi_alpha;
        psi_r_beta  += Ts * dpsi_beta;

        // Rotor flux angle
        float theta_flux = atan2f(psi_r_beta, psi_r_alpha);

        // ABC -> DQ in rotor flux frame
        uz_3ph_dq_t i_dq = uz_transformation_3ph_abc_to_dq(i_abc, theta_flux);
        Global_Data.av.I_d = i_dq.d;
        Global_Data.av.I_q = i_dq.q;
        Global_Data.av.theta_elec = theta_flux;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();

    if(current_state==control_state)
    {
        // V/f Control Algorithm - only active in control state

        // Limit frequency to maximum
        float freq_limited = fminf(vf_frequency_setpoint_Hz, vf_max_frequency_Hz);

        // Calculate voltage magnitude based on V/f ratio with boost
        float voltage_magnitude_V = (vf_ratio_V_per_Hz * freq_limited) + vf_boost_voltage_V;

        // Limit voltage to maximum
        voltage_magnitude_V = fminf(voltage_magnitude_V, vf_max_voltage_V);

        // Normalize voltage to DC-link to get duty cycle amplitude
        // Floor at 1V prevents division by zero during testing with uncharged DC-link
        // Result will saturate and be clamped to valid range by limiter below
        float duty_amplitude_vf = voltage_magnitude_V / fmaxf(Global_Data.av.U_DC, 1.0f);

        // Limit duty cycle amplitude to 0.45 (since offset=0.5, peak will be 0.5+0.45=0.95)
        // This ensures duty cycles stay within valid range [0.0, 1.0]
        duty_amplitude_vf = fminf(duty_amplitude_vf, 0.45f);
        duty_amplitude_vf = fmaxf(duty_amplitude_vf, 0.0f);

        // Generate three-phase sine waves with V/f frequency and calculated amplitude
        three_phase_sine = uz_wavegen_three_phase_sample(duty_amplitude_vf, freq_limited, duty_offset);

        // Set duty cycles
        Global_Data.rasv.halfBridge1DutyCycle = three_phase_sine.a;
        Global_Data.rasv.halfBridge2DutyCycle = three_phase_sine.b;
        Global_Data.rasv.halfBridge3DutyCycle = three_phase_sine.c;

        // Enable inverter (PWM 7 is connected to "inverter_enable" signal to Wolfspeed inverter)
        Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    }
    else
    {
        // Disable PWM outputs when not in control state
        Global_Data.rasv.halfBridge1DutyCycle = 0.5f;  // Neutral duty cycle
        Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
        Global_Data.rasv.halfBridge3DutyCycle = 0.5f;

        // Disable inverter
        Global_Data.rasv.halfBridge7DutyCycle = 1.0f;
    }

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



