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
#include "../Codegen/uz_codegen0_ert_rtw/uz_codegen0.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_integrator/uz_integrator.h"
#include "../IP_Cores/uz_JL_invModel_PT1/uz_JL_invModel_PT1.h"
#include "../IP_Cores/uz_JL_invModel_ideal/uz_JL_invModel_ideal.h"
#include "../IP_Cores/uz_JL_pmsmModel/uz_JL_pmsmModel.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../uz/uz_signals/uz_signals.h"

extern uz_JL_invModel_PT1_t *inverter_PT1;
extern uz_JL_invModel_ideal_t *inverter_ideal;
extern uz_JL_pmsmModel_t *pmsm_PT1;
extern uz_JL_pmsmModel_t *pmsm_ideal;
extern uz_IIR_Filter_t *iir_speed;
extern uz_IIR_Filter_t *iir_current_a;
extern uz_IIR_Filter_t *iir_current_b;
extern uz_IIR_Filter_t *iir_current_c;



uz_3ph_alphabeta_t  voltages_alphabeta = {0};
uz_3ph_abc_t three_phase_sine = {0};

struct uz_JL_invModel_PT1_output_t pt1_outputs = {0};
struct uz_JL_invModel_ideal_output_t ideal_outputs = {0};

struct uz_JL_pmsmModel_outputs_t pmsm_pt1_out = {0};
struct uz_JL_pmsmModel_outputs_t pmsm_ideal_out = {0};

struct uz_JL_pmsmModel_inputs_t pmsm_pt1_in = {
		.Last_J = 0.0f,
		.Last_M = 0.0f,
		.bremse = 0.0f,
		.SwitchUabc_dq = false,
		.Ud = 0.0f,
		.Uq = 0.0f,
};

struct uz_JL_pmsmModel_inputs_t pmsm_ideal_in = {
		.Last_J = 0.0f,
		.Last_M = 0.0f,
		.bremse = 0.0f,
		.SwitchUabc_dq = false,
		.Ud = 0.0f,
		.Uq = 0.0f,
};


// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

extern uz_codegen regelung;
Bus_ZM_In struct_ZM_In;
//extern uz_pmsmModel_t *pmsm;

bool timer = false;
float speed_filtered = 0.0f;
float i_a_filt = 0.0f;
float i_b_filt = 0.0f;
float i_c_filt = 0.0f;

float DutA = 0.0f;
float DutB = 0.0f;
float DutC = 0.0f;

static void ReadAllADC();
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
//	uz_JL_invModel_PT1_trigger_output_strobe(inverter_PT1);
//	pt1_outputs = uz_JL_invModel_PT1_get_outputs(inverter_PT1);

//	uz_JL_pmsmModel_trigger_output_strobe(pmsm_PT1);
//	pmsm_pt1_out = uz_JL_pmsmModel_get_outputs(pmsm_PT1);

	uz_JL_invModel_ideal_trigger_output_strobe(inverter_ideal);
	ideal_outputs = uz_JL_invModel_ideal_get_outputs(inverter_ideal);

	uz_JL_pmsmModel_trigger_output_strobe(pmsm_ideal);
	pmsm_ideal_out = uz_JL_pmsmModel_get_outputs(pmsm_ideal);
	speed_filtered = uz_signals_IIR_Filter_sample(iir_speed, pmsm_ideal_out.omega_mech_1_s);
	i_a_filt = uz_signals_IIR_Filter_sample(iir_current_a, pmsm_ideal_out.i_a_A);
	i_b_filt = uz_signals_IIR_Filter_sample(iir_current_b, pmsm_ideal_out.i_b_A);
	i_c_filt = uz_signals_IIR_Filter_sample(iir_current_c, pmsm_ideal_out.i_c_A);

    regelung.input.Bus_PMSM_Out_e.pmsm_Iuvw[0] = pmsm_ideal_out.i_a_A;
	regelung.input.Bus_PMSM_Out_e.pmsm_Iuvw[1] = pmsm_ideal_out.i_b_A;
	regelung.input.Bus_PMSM_Out_e.pmsm_Iuvw[2] = pmsm_ideal_out.i_c_A;
	regelung.input.Bus_PMSM_Out_e.pmsm_Omega_mech = speed_filtered;//pmsm_ideal_out.omega_mech_1_s;
	regelung.input.Bus_PMSM_Out_e.pmsm_phi_mech = pmsm_ideal_out.phi_mech_rad;
	regelung.input.Bus_PMSM_Out_e.pmsm_m_mot = pmsm_ideal_out.torque_Nm;

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    switch(current_state)
	{
		case idle_state:
			struct_ZM_In.Soll_Status = Ready;
			struct_ZM_In.Soll_Drehzahl = 0;
			struct_ZM_In.Soll_id = 0;
			struct_ZM_In.Soll_iq = 0;
			struct_ZM_In.Fehlermeldung = false;
			struct_ZM_In.Start_Traj = false;
			voltages_alphabeta.alpha = 0.0f;
			voltages_alphabeta.beta = 0.0f;
		    Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		    Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		    Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, false);
			break;
		case running_state:
			struct_ZM_In.Soll_Status = Run;
			struct_ZM_In.Soll_Drehzahl = 0;
			struct_ZM_In.Soll_id = 0;
			struct_ZM_In.Soll_iq = 0;
			voltages_alphabeta.alpha = 0.0f;
			voltages_alphabeta.beta = 0.0f;
			break;
		case control_state:
//		    Start: Control algorithm - only if ultrazohm is in control state
			struct_ZM_In.Soll_Status = En;
			struct_ZM_In.Soll_Regelungsart = Drehzahl;
			struct_ZM_In.Soll_Drehzahl = 2000;
//			struct_ZM_In.Soll_iq = 10;
			uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
			regelung.input.Bus_ZM_In_f = struct_ZM_In;
			uz_codegen_step(&regelung);
		    Global_Data.rasv.halfBridge1DutyCycle = regelung.output.Bus_Ctrl_Out_k.Dutycycle[0];
		    Global_Data.rasv.halfBridge2DutyCycle = regelung.output.Bus_Ctrl_Out_k.Dutycycle[1];
		    Global_Data.rasv.halfBridge3DutyCycle = regelung.output.Bus_Ctrl_Out_k.Dutycycle[2];
			voltages_alphabeta.alpha = regelung.PtrToModelData->outputs->Bus_Ctrl_Out_k.ctrl_Ualpha;
			voltages_alphabeta.beta = regelung.PtrToModelData->outputs->Bus_Ctrl_Out_k.ctrl_Ubeta;
		   break;
		default:
			break;
	}


//	uz_JL_invModel_PT1_set_input(inverter_PT1, voltages_alphabeta.alpha, voltages_alphabeta.beta);


	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    JavaScope_update(&Global_Data);

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
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



