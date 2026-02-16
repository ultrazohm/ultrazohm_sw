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

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);

//Added stuff
#define CURRENT_CONV_HASS_50 40.0f
#define VOLTAGE_2_SI_VOLTS_DHG_CH1 363.6f
#define VOLTAGE_2_SI_VOLTS_DHG_CH2 363.6f
#define VOLTAGE_2_SI_VOLTS_DHG_CH3 37.037f
#define VOLTAGE_2_SI_VOLTS_DHG_CH4 142.3f

#define DC_VOLTAGE 565.0f
#define	MAX_MODULATION_INDEX (1.0f / sqrtf(3.0f))
#define	MAX_VOLTAGE			 (DC_VOLTAGE * MAX_MODULATION_INDEX)

enum ControllerApplication ConApplication;
enum ControllerSelection ConSelection;
float ts = 1.0f/UZ_PWM_FREQUENCY;
float Observation[10] = {0};

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

    switch(ConApplication) {
    case CIL:
    	uz_pmsmModel_trigger_input_strobe(Global_Data.objects.SynRM_Model);
    	uz_pmsmModel_trigger_output_strobe(Global_Data.objects.SynRM_Model);
    	Global_Data.av.SynRM_outputs 		= uz_pmsmModel_get_outputs(Global_Data.objects.SynRM_Model);
    	Global_Data.av.i_dq.d 				= Global_Data.av.SynRM_outputs.i_d_A;
    	Global_Data.av.i_dq.q 				= Global_Data.av.SynRM_outputs.i_q_A;
    	Global_Data.av.omega_mech			= Global_Data.av.SynRM_outputs.omega_mech_1_s;
    	Global_Data.av.Torque				= Global_Data.av.SynRM_outputs.torque_Nm;
    	Global_Data.av.mechanicalRotorSpeed = Global_Data.av.omega_mech * 30.0f / UZ_PIf;
    	Global_Data.av.omega_elec 			= Global_Data.av.omega_mech * Global_Data.av.SynRM_config.polePairs;
    	Global_Data.av.v_dc					= DC_VOLTAGE;
    	Global_Data.av.current_angle		= atan2f(Global_Data.av.i_dq.q,Global_Data.av.i_dq.d)/UZ_PIf * 180.0f;
    	Global_Data.av.Is					= sqrtf((Global_Data.av.i_dq.d * Global_Data.av.i_dq.d) + (Global_Data.av.i_dq.q * Global_Data.av.i_dq.q));
    	break;

    case REAL:
    	update_speed_and_position_of_encoder_on_D5(&Global_Data);//get theta_elec and omega_mech
    	Global_Data.av.theta_elec = Global_Data.av.theta_elec - Global_Data.av.theta_offset;
    	Global_Data.av.theta_mech = Global_Data.av.theta_elec / Global_Data.av.SynRM_config.polePairs;
    	Global_Data.av.omega_elec = Global_Data.av.omega_mech * Global_Data.av.SynRM_config.polePairs;
    	Global_Data.av.mechanicalRotorSpeed = Global_Data.av.omega_mech * 30.0f / UZ_PIf;
    	Global_Data.av.theta_elec_advanced = Global_Data.av.theta_elec + ((1.5f * Global_Data.av.omega_elec) / UZ_PWM_FREQUENCY);
    	//Todo
    	Global_Data.av.current_angle		= atan2f(Global_Data.av.i_dq.q,Global_Data.av.i_dq.d);
    	Global_Data.av.Is					= sqrtf((Global_Data.av.i_dq.d * Global_Data.av.i_dq.d) + (Global_Data.av.i_dq.q * Global_Data.av.i_dq.q));
    	break;
    }


    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // if "STOP"
    if (current_state==idle_state)
    {
    	uz_CurrentControl_reset(Global_Data.objects.CurrentControl);
    	Global_Data.av.n_ref_CIL = 0.0f;
    	switch(ConApplication) {
    	    case CIL:
    	    	uz_pmsmModel_reset(Global_Data.objects.SynRM_Model);
    	    	break;

    	    case REAL:
    	    	// disable inverters
    	    	//Todo
    	    	// write zero dutycycle
    	    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
    	    	break;

    	    default:
    	    	break;
    	}
    }

    // if "ENABLE SYSTEM"
	if (current_state==running_state)
	{
		switch(ConApplication) {
			case CIL:
				//CODE
				break;

			case REAL:
     	    	// enable inverters
				//TODO
     	    	break;

     	    default:
     	    	break;
     	}
    }

    if (current_state==control_state)
    {
        switch(ConSelection) {
        case LUT_FOC:
        	Global_Data.av.flux_approx_real = uz_approximate_flux_step(Global_Data.objects.FluxApproximation, Global_Data.av.i_dq);
        	Global_Data.av.flux_approx_reference = uz_approximate_flux_reference_step(Global_Data.objects.FluxApproximation, Global_Data.av.i_dq_ref, Global_Data.av.i_dq);
        	uz_CurrentControl_set_flux_approx(Global_Data.objects.CurrentControl, Global_Data.av.flux_approx_real, Global_Data.av.flux_approx_reference);
        	uz_CurrentControl_adjust_Kp(Global_Data.objects.CurrentControl, Global_Data.av.i_dq_ref, Global_Data.av.i_dq, BO_FACTOR);
        	Global_Data.av.current_angle_ref = uz_LUT_1D_get_value(Global_Data.objects.LUT_CIL_current_angle, Global_Data.av.Torque_ref);
        	Global_Data.av.Is_ref = uz_LUT_1D_get_value(Global_Data.objects.LUT_CIL_Is, Global_Data.av.Torque_ref);
        	Global_Data.av.i_dq_ref.d = cosf((Global_Data.av.current_angle_ref)/180*UZ_PIf) * Global_Data.av.Is_ref;
        	Global_Data.av.i_dq_ref.q = sinf((Global_Data.av.current_angle_ref)/180*UZ_PIf) * Global_Data.av.Is_ref;
        	Global_Data.av.v_dq_ref = uz_CurrentControl_sample_SynRM(Global_Data.objects.CurrentControl, Global_Data.av.i_dq_ref, Global_Data.av.i_dq, Global_Data.av.v_dc, Global_Data.av.omega_elec);
        	break;

        case RL:
        	break;

        case manual:
        	//Set Global_Data.av.v_dq_ref via GUI
        	break;

        default:
        	break;
        }

    	switch(ConApplication) {
    		case CIL:
    	    	Global_Data.av.SynRM_inputs.v_d_V = Global_Data.av.v_dq_ref.d;
    	    	Global_Data.av.SynRM_inputs.v_q_V = Global_Data.av.v_dq_ref.q;
    	    	Global_Data.av.SynRM_inputs.omega_mech_1_s = Global_Data.av.n_ref_CIL / 30.0f * UZ_PIf;
    	    	uz_pmsmModel_set_inputs(Global_Data.objects.SynRM_Model, Global_Data.av.SynRM_inputs);
    	    	break;

    	    case REAL:
            	Global_Data.av.DutyCycle = uz_Space_Vector_Modulation(Global_Data.av.v_dq_ref, Global_Data.av.v_dc, Global_Data.av.theta_elec_advanced);
    	    	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.DutyCycle.DutyCycle_A;
    	        Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.DutyCycle.DutyCycle_B;
    	        Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.DutyCycle.DutyCycle_C;
    	    	break;

    	    default:
    	    	break;
    	    }
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);


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



