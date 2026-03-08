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
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

//defines and limits
#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f
#define		MAX_CURRENT_VA		15.0f
#define		MAX_CURRENT_IM		8.0f
// measurement structs for motor control
struct uz_3ph_abc_t i_abc_VA = {0.0f};
struct uz_3ph_abc_t i_abc_IM = {0.0f};
struct uz_3ph_abc_t v_abc_IM = {0.0f};
struct uz_3ph_dq_t i_dq_VA = {0.0f};
struct uz_3ph_dq_t i_dq_IM = {0.0f};
struct uz_3ph_dq_t i_dq_ref_IM = {0.0f};
struct uz_3ph_dq_t i_dq_ref_VA = {0.0f};
struct uz_3ph_dq_t v_dq_ref_VA = {0.0f};
struct uz_3ph_dq_t v_dq_ref_IM = {0.0f};
struct uz_3ph_dq_t v_dq_meas_IM = {0.0f};
struct uz_3ph_dq_t v_dq_meas_IM_rev_filt = {0.0f};
struct uz_3ph_dq_t v_dq_meas_VA = {0.0f};
struct uz_DutyCycle_t dutycyc_VA = {0.0f};
struct uz_DutyCycle_t dutycyc_IM = {0.0f};


// Global variable structure
extern DS_Data Global_Data;
extern struct uz_PWM_duty_freq_detection_outputs_t outputs;
extern struct linear_interpolation_parameters_t lin_inter_param;
static void ReadAllADC();
static void im_control();
static void speed_control_VA();
static void current_control_VA();
static void safety_check_wolfspeed();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);

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
    // update status of inverter

    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
    safety_check_wolfspeed();

	// assign inverter measurements
	Global_Data.av.VA_ia = Global_Data.aa.A2.me.ADC_A4 * CURRENT_2_SI_AMPERE;
	Global_Data.av.VA_ib = Global_Data.aa.A2.me.ADC_A3 * CURRENT_2_SI_AMPERE;
	Global_Data.av.VA_ic = Global_Data.aa.A2.me.ADC_A2 * CURRENT_2_SI_AMPERE;
	Global_Data.av.VA_idc = Global_Data.aa.A2.me.ADC_B5 * CURRENT_2_SI_AMPERE;
	Global_Data.av.VA_ua = Global_Data.aa.A2.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.VA_ub = Global_Data.aa.A2.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.VA_uc = Global_Data.aa.A2.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.VA_vdc = Global_Data.aa.A2.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

	// assign measurements from global_data to motor control structs
    i_abc_VA.a = Global_Data.av.VA_ia;
    i_abc_VA.b = Global_Data.av.VA_ib;
    i_abc_VA.c = Global_Data.av.VA_ic;

    // check for current limit
    if (fabs(Global_Data.av.VA_ia) > MAX_CURRENT_VA || fabs(Global_Data.av.VA_ib) > MAX_CURRENT_VA || fabs(Global_Data.av.VA_ic) > MAX_CURRENT_VA) {
    	ultrazohm_state_machine_set_stop(true);
    }

    // calculate mean temperature values over all measured temperatures of each inverter
    Global_Data.av.mean_temp_inv_d2 = (Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3) * 0.1667;

    platform_state_t current_state=ultrazohm_state_machine_get_state();

	// park transformation of measured currents
	i_dq_VA = uz_transformation_3ph_abc_to_dq(i_abc_VA, Global_Data.av.VA_theta_elec);
	Global_Data.av.VA_I_d = i_dq_VA.d;
	Global_Data.av.VA_I_q = i_dq_VA.q;

    // if "STOP"
    if (current_state==idle_state)
    {
    	// disable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_VA);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_VA);
		Global_Data.rasv.n_ref_VA = 0.0f;
		Global_Data.rasv.n_ref_filt_VA = 0.0f;

		Global_Data.rasv.M_ref_VA = 0.0f;
		Global_Data.rasv.i_dq_ref_VA.d = 0.0f;
		Global_Data.rasv.i_dq_ref_VA.q = 0.0f;
		// set dutycycle
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);
//		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
//		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
//		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
//		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
//		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
//		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
    }

    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	// enable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    	// reset tristate
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);

    }


    if (current_state==control_state)
    {
    	speed_control_VA();

    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_IM.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_IM.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_IM.DutyCycle_C;
    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_VA.DutyCycle_A;
    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_VA.DutyCycle_B;
    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_VA.DutyCycle_C;
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

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

static void im_control(){

};


static void current_control_VA() {
	// calculate reference voltages for current control
	v_dq_ref_VA = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_VA, Global_Data.rasv.i_dq_ref_VA, i_dq_VA, Global_Data.av.VA_vdc, Global_Data.av.VA_omega_mech*Global_Data.av.VA_polepairs);
	Global_Data.av.VA_vd = v_dq_ref_VA.d;
	Global_Data.av.VA_vq = v_dq_ref_VA.q;
	Global_Data.av.VA_theta_elec_advanced =  Global_Data.av.VA_theta_elec + (1.5f * (Global_Data.av.VA_omega_mech*Global_Data.av.VA_polepairs) * (1.0f / (UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)));
	dutycyc_VA = uz_Space_Vector_Modulation(v_dq_ref_VA, Global_Data.av.VA_vdc, Global_Data.av.VA_theta_elec_advanced);
};

static void safety_check_wolfspeed() {
    //  not used yet = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.d1_gpi_ch15_17,1);
    Global_Data.av.pwm_freq = uz_PWM_duty_freq_detection_get_frequency_in_Hz(Global_Data.objects.PWM_Detect_instance);
    Global_Data.av.duty_cycle = uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(Global_Data.objects.PWM_Detect_instance);
//    Global_Data.av.temp = uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(Global_Data.av.duty_cycle ,lin_inter_param);
    platform_state_t current_state=ultrazohm_state_machine_get_state();
    // test for duty_freq-detect
    Global_Data.av.OCP_INVERTER = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.d1_gpi_ch15_17,0);
    Global_Data.av.FAULT_INVERTER = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.d1_gpi_ch15_17,1);

};

static void speed_control_VA() {
	// filter speed setpoint signal
	Global_Data.rasv.n_ref_filt_VA = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_VA, Global_Data.rasv.n_ref_VA);
	// calculate reference torque from speed ctrl of VA motor
	Global_Data.rasv.M_ref_VA = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_VA, Global_Data.av.VA_omega_mech, Global_Data.rasv.n_ref_filt_VA);
	// calculate current setpoints i_dq_ref for VA motor
	Global_Data.rasv.i_dq_ref_VA = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_VA, Global_Data.av.VA_omega_mech, Global_Data.rasv.M_ref_VA, Global_Data.av.VA_vdc, i_dq_VA);
	//
	current_control_VA();
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
