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
#include <stddef.h>
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

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void uz_pmsm_cil_reset(void);
static void uz_pmsm_cil_zero_duty_cycles(void);
static void uz_pmsm_cil_run_control_step(void);
static float uz_pmsm_cil_rpm_to_rad_per_sec(float speed_rpm);
static float uz_pmsm_cil_wrap_to_2pi(float angle_rad);
static float uz_pmsm_cil_get_v_dc(void);
static struct uz_pmsm_measurement_values uz_pmsm_cil_make_measurements(uz_3ph_dq_t i_dq_A, uz_3ph_dq_t v_dq_V, float theta_mech_rad, float omega_mech_rad_per_sec, float v_dc_V);
static void uz_pmsm_cil_write_ipcore_actual_values(struct uz_pmsm_measurement_values measurements, struct uz_pmsmModel_outputs_t outputs, uz_3ph_dq_t v_dq_V, float theta_mech_rad, float omega_mech_rad_per_sec);

#define UZ_PMSM_CIL_SEND_FIELD_SPEED_RPM 1U
#define UZ_PMSM_CIL_SEND_FIELD_LOAD_TORQUE_NM 2U
#define UZ_PMSM_CIL_SEND_FIELD_ID_REF_A 3U
#define UZ_PMSM_CIL_SEND_FIELD_IQ_REF_A 4U
#define UZ_PMSM_CIL_SEND_FIELD_V_DC_V 5U

static uz_3ph_dq_t pmsm_cil_swmodel_v_dq_V = {0};
static uz_3ph_dq_t pmsm_cil_ipcore_v_dq_V = {0};
static struct uz_pmsm_swmodel_outputs_t pmsm_cil_swmodel_outputs = {0};
static struct uz_pmsmModel_outputs_t pmsm_cil_ipcore_outputs = {0};
static float pmsm_cil_theta_mech_rad = 0.0f;
static bool pmsm_cil_is_reset = false;

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
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        pmsm_cil_is_reset = false;
        uz_pmsm_cil_run_control_step();
    }
    else
    {
        if (!pmsm_cil_is_reset)
        {
            uz_pmsm_cil_reset();
            pmsm_cil_is_reset = true;
        }
    }

    uz_pmsm_cil_zero_duty_cycles();

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
    
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

static void uz_pmsm_cil_zero_duty_cycles(void)
{
    Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge9DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge10DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge11DutyCycle = 0.0f;
    Global_Data.rasv.halfBridge12DutyCycle = 0.0f;
}

static float uz_pmsm_cil_rpm_to_rad_per_sec(float speed_rpm)
{
    return speed_rpm * 2.0f * (float)M_PI / 60.0f;
}

static float uz_pmsm_cil_wrap_to_2pi(float angle_rad)
{
    const float two_pi = 2.0f * (float)M_PI;
    float wrapped = fmodf(angle_rad, two_pi);
    if (wrapped < 0.0f)
    {
        wrapped += two_pi;
    }
    return wrapped;
}

static float uz_pmsm_cil_get_v_dc(void)
{
    float v_dc_V = Global_Data.av.snd_fld[UZ_PMSM_CIL_SEND_FIELD_V_DC_V];
    if (v_dc_V <= 0.0f)
    {
        v_dc_V = UZ_CIL_PMSM_DEFAULT_V_DC_V;
    }
    return v_dc_V;
}

static struct uz_pmsm_measurement_values uz_pmsm_cil_make_measurements(uz_3ph_dq_t i_dq_A, uz_3ph_dq_t v_dq_V, float theta_mech_rad, float omega_mech_rad_per_sec, float v_dc_V)
{
    const float theta_el_rad = uz_pmsm_cil_wrap_to_2pi(theta_mech_rad * UZ_CIL_PMSM_POLE_PAIRS);
    struct uz_pmsm_measurement_values measurements = {
        .i_abc_in_A = uz_transformation_3ph_dq_to_abc(i_dq_A, theta_el_rad),
        .v_abc_in_V = uz_transformation_3ph_dq_to_abc(v_dq_V, theta_el_rad),
        .v_dc_in_V = v_dc_V,
        .i_dc_in_A = 0.0f,
        .omega_mech_rad_per_sec = omega_mech_rad_per_sec,
        .theta_mech = theta_mech_rad};
    return measurements;
}

static void uz_pmsm_cil_acknowledge_controller(uz_pmsm_control_t *controller)
{
    if (controller != NULL)
    {
        const struct uz_pmsm_measurement_values reset_measurements = {
            .i_abc_in_A = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
            .v_abc_in_V = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
            .v_dc_in_V = UZ_CIL_PMSM_DEFAULT_V_DC_V,
            .i_dc_in_A = 0.0f,
            .omega_mech_rad_per_sec = 0.0f,
            .theta_mech = 0.0f};
        uz_pmsm_control_enable(controller, false);
        uz_pmsm_control_reset(controller);
        uz_pmsm_control_acknowledge_and_reset_error(controller, reset_measurements);
    }
}

static void uz_pmsm_cil_reset(void)
{
    uz_pmsm_cil_acknowledge_controller(Global_Data.objects.pmsm_control_swmodel);
    uz_pmsm_cil_acknowledge_controller(Global_Data.objects.pmsm_control_ipcore);

    if (Global_Data.objects.pmsm_swmodel != NULL)
    {
        uz_pmsm_swmodel_reset(Global_Data.objects.pmsm_swmodel);
    }
    if (Global_Data.objects.pmsm_model != NULL)
    {
        uz_pmsmModel_reset(Global_Data.objects.pmsm_model);
    }

    pmsm_cil_swmodel_v_dq_V = (uz_3ph_dq_t){0};
    pmsm_cil_ipcore_v_dq_V = (uz_3ph_dq_t){0};
    pmsm_cil_swmodel_outputs = (struct uz_pmsm_swmodel_outputs_t){0};
    pmsm_cil_ipcore_outputs = (struct uz_pmsmModel_outputs_t){0};
    pmsm_cil_theta_mech_rad = 0.0f;
    pmsm_cil_is_reset = true;

    Global_Data.av.I_d = 0.0f;
    Global_Data.av.I_q = 0.0f;
    Global_Data.av.U_d = 0.0f;
    Global_Data.av.U_q = 0.0f;
    Global_Data.av.mechanicalTorque = 0.0f;
    Global_Data.av.mechanicalTorqueObserved = 0.0f;
    Global_Data.av.mechanicalRotorSpeed = 0.0f;
    Global_Data.av.electricalRotorSpeed = 0.0f;
    Global_Data.av.theta_mech = 0.0f;
    Global_Data.av.theta_elec = 0.0f;

    uz_pmsm_cil_zero_duty_cycles();
}

static void uz_pmsm_cil_write_ipcore_actual_values(struct uz_pmsm_measurement_values measurements, struct uz_pmsmModel_outputs_t outputs, uz_3ph_dq_t v_dq_V, float theta_mech_rad, float omega_mech_rad_per_sec)
{
    Global_Data.av.I_U = measurements.i_abc_in_A.a;
    Global_Data.av.I_V = measurements.i_abc_in_A.b;
    Global_Data.av.I_W = measurements.i_abc_in_A.c;
    Global_Data.av.U_U = measurements.v_abc_in_V.a;
    Global_Data.av.U_V = measurements.v_abc_in_V.b;
    Global_Data.av.U_W = measurements.v_abc_in_V.c;
    Global_Data.av.I_d = outputs.i_d_A;
    Global_Data.av.I_q = outputs.i_q_A;
    Global_Data.av.U_d = v_dq_V.d;
    Global_Data.av.U_q = v_dq_V.q;
    Global_Data.av.mechanicalTorque = outputs.torque_Nm;
    Global_Data.av.mechanicalTorqueObserved = outputs.torque_Nm;
    Global_Data.av.mechanicalRotorSpeed = omega_mech_rad_per_sec * 60.0f / (2.0f * (float)M_PI);
    Global_Data.av.electricalRotorSpeed = Global_Data.av.mechanicalRotorSpeed * UZ_CIL_PMSM_POLE_PAIRS;
    Global_Data.av.theta_mech = theta_mech_rad;
    Global_Data.av.theta_elec = uz_pmsm_cil_wrap_to_2pi(theta_mech_rad * UZ_CIL_PMSM_POLE_PAIRS);
}

static void uz_pmsm_cil_run_control_step(void)
{
    const float speed_ref_rpm = Global_Data.av.snd_fld[UZ_PMSM_CIL_SEND_FIELD_SPEED_RPM];
    const float omega_mech_rad_per_sec = uz_pmsm_cil_rpm_to_rad_per_sec(speed_ref_rpm);
    const float load_torque_Nm = Global_Data.av.snd_fld[UZ_PMSM_CIL_SEND_FIELD_LOAD_TORQUE_NM];
    const float v_dc_V = uz_pmsm_cil_get_v_dc();
    const uz_3ph_dq_t reference_currents_A = {
        .d = Global_Data.av.snd_fld[UZ_PMSM_CIL_SEND_FIELD_ID_REF_A],
        .q = Global_Data.av.snd_fld[UZ_PMSM_CIL_SEND_FIELD_IQ_REF_A],
        .zero = 0.0f};

    pmsm_cil_theta_mech_rad = uz_pmsm_cil_wrap_to_2pi(pmsm_cil_theta_mech_rad + (omega_mech_rad_per_sec * Global_Data.av.isr_samplerate_s));

    uz_pmsm_control_enable(Global_Data.objects.pmsm_control_swmodel, true);
    uz_pmsm_control_enable(Global_Data.objects.pmsm_control_ipcore, true);

    struct uz_pmsm_measurement_values swmodel_measurements = uz_pmsm_cil_make_measurements(pmsm_cil_swmodel_outputs.i_dq_A, pmsm_cil_swmodel_v_dq_V, pmsm_cil_theta_mech_rad, omega_mech_rad_per_sec, v_dc_V);
    pmsm_cil_swmodel_v_dq_V = uz_pmsm_control_sample_dq(Global_Data.objects.pmsm_control_swmodel, swmodel_measurements, speed_ref_rpm, reference_currents_A, load_torque_Nm);
    const struct uz_pmsm_swmodel_inputs_t swmodel_inputs = {
        .v_dq_V = pmsm_cil_swmodel_v_dq_V,
        .omega_mech_1_s = omega_mech_rad_per_sec,
        .load_torque = load_torque_Nm};
    pmsm_cil_swmodel_outputs = uz_pmsm_swmodel_step(Global_Data.objects.pmsm_swmodel, swmodel_inputs);

    uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_model);
    uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_model);
    pmsm_cil_ipcore_outputs = uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_model);
    const uz_3ph_dq_t ipcore_i_dq_A = {
        .d = pmsm_cil_ipcore_outputs.i_d_A,
        .q = pmsm_cil_ipcore_outputs.i_q_A,
        .zero = 0.0f};
    struct uz_pmsm_measurement_values ipcore_measurements = uz_pmsm_cil_make_measurements(ipcore_i_dq_A, pmsm_cil_ipcore_v_dq_V, pmsm_cil_theta_mech_rad, omega_mech_rad_per_sec, v_dc_V);
    pmsm_cil_ipcore_v_dq_V = uz_pmsm_control_sample_dq(Global_Data.objects.pmsm_control_ipcore, ipcore_measurements, speed_ref_rpm, reference_currents_A, load_torque_Nm);
    const struct uz_pmsmModel_inputs_t ipcore_inputs = {
        .v_d_V = pmsm_cil_ipcore_v_dq_V.d,
        .v_q_V = pmsm_cil_ipcore_v_dq_V.q,
        .omega_mech_1_s = omega_mech_rad_per_sec,
        .load_torque = load_torque_Nm};
    uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_model, ipcore_inputs);

    Global_Data.av.U_ZK = v_dc_V;
    uz_pmsm_cil_write_ipcore_actual_values(ipcore_measurements, pmsm_cil_ipcore_outputs, pmsm_cil_ipcore_v_dq_V, pmsm_cil_theta_mech_rad, omega_mech_rad_per_sec);
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
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



