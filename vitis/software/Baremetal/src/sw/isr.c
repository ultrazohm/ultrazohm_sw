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
#include "../include/adc.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../IP_Cores/uz_JL_invModel_ideal/uz_JL_invModel_ideal.h"
#include "../IP_Cores/uz_JL_pmsmModel/uz_JL_pmsmModel.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../include/SigmaDeltaWandler.h"
#include "../uz/uz_wavegen/uz_wavegen.h"

#define TEST_SINE_AMPLITUDE 1.0f
#define TEST_SINE_FREQUENCY_HZ 25.0f

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;
extern  uz_axi_gpio_t* output_gpio;
extern  uz_axi_gpio_t* input_gpio;

#define PWR_EN_BIT 6
#define BOARD_EN_BIT 8
#define BOARD_RST_BIT 10
#define BOARD_READY_BIT 1
#define IGBT_Desat_BIT 3

uint32_t output_bitmask=0xFFFFFFFF;
bool input_bit=false;
bool output_bit=false;
bool board_ready = false;

uint32_t output_port = 0U;
uint32_t input_port = 0U;

float input_bit_float = 0;
static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);


extern uz_JL_SigmaDelta_Interface_t *Sinc3_Filter;

struct uz_JL_SigmaDelta_Interface_output_t Sinc3_Filter_out = {0};

extern uz_codegen regelung;
Bus_ZM_In struct_ZM_In;

uz_3ph_alphabeta_t  voltages_alphabeta = {0};
float sine = 0.0f;

float theta_el_unwrapped = 0.0f;
int32_t fault = 0;
float fault_f = 0.0f;

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

    board_ready = uz_axi_gpio_read_pin_zero_based(input_gpio, BOARD_READY_BIT);
	Global_Data.av.resolver_pl_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface);

//	theta_el_unwrapped = Global_Data.av.resolver_pl_outputs.position_el_2pi - Global_Data.av.theta_el_offset;
	Global_Data.av.theta_el = uz_signals_wrap(theta_el_unwrapped, 2.0f*UZ_PIf);

//	Global_Data.av.omega_el = Global_Data.av.resolver_pl_outputs.omega_mech_rad_s
//			* (float)uz_resolver_pl_interface_get_machine_polepairs(Global_Data.objects.resolver_pl_interface);

	// fault = uz_resolverIP_getFLTRegister(Global_Data.objects.resolver);
	// uz_resolverIP_setDataModePositionVelocity(Global_Data.objects.resolver); // getFLTRegister() switches the AD2S1210 into Config Mode internally; switch back so resolver_pl_interface keeps receiving valid position/velocity data

    

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    struct_ZM_In.UZ_Platform_State = current_state;
    switch(current_state)
    	{
    		case idle_state:

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
    			// Set Enable Pins
                Sinc3_Filter_out = uz_JL_SigmaDelta_Interface_get_outputs(Sinc3_Filter);
   	            SigmaDeltaWandler_process(Sinc3_Filter_out, &Global_Data.av.Sinc3_Filter);
   	            Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
				Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
   	            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
    			struct_ZM_In.Soll_Drehzahl = 0;
    			struct_ZM_In.Soll_id = 0;
    			struct_ZM_In.Soll_iq = 0;
    			voltages_alphabeta.alpha = 0.0f;
    			voltages_alphabeta.beta = 0.0f;
    			break;
    		case control_state:
                Sinc3_Filter_out = uz_JL_SigmaDelta_Interface_get_outputs(Sinc3_Filter);
   	            SigmaDeltaWandler_process(Sinc3_Filter_out, &Global_Data.av.Sinc3_Filter);
                switch (Global_Data.rasv.ctrl_state)
                {
                    case current_control:
                        struct_ZM_In.Soll_iq = Global_Data.rasv.Soll_iq;
                        struct_ZM_In.Soll_id = Global_Data.rasv.Soll_id;
                        struct_ZM_In.Soll_Drehzahl = 0;
                        struct_ZM_In.Soll_Regelungsart = Strom;
                        if(regelung.output.Bus_Ctrl_Out_e.act_pwm == true && board_ready == true)
                            {

                                Global_Data.rasv.halfBridge1DutyCycle = regelung.output.Bus_Ctrl_Out_e.Dutycycle[0];
                                Global_Data.rasv.halfBridge2DutyCycle = regelung.output.Bus_Ctrl_Out_e.Dutycycle[1];
                                Global_Data.rasv.halfBridge3DutyCycle = regelung.output.Bus_Ctrl_Out_e.Dutycycle[2];
                            }
                        break;
                    case rpm_control:
                        struct_ZM_In.Soll_iq = 0;
                        struct_ZM_In.Soll_id = 0;
                        struct_ZM_In.Soll_Drehzahl = Global_Data.rasv.Soll_Drehzahl;
                        struct_ZM_In.Soll_Regelungsart = Drehzahl;
                        if( regelung.output.Bus_Ctrl_Out_e.act_pwm == true && board_ready == true)
                            {

                                Global_Data.rasv.halfBridge1DutyCycle = regelung.output.Bus_Ctrl_Out_e.Dutycycle[0];
                                Global_Data.rasv.halfBridge2DutyCycle = regelung.output.Bus_Ctrl_Out_e.Dutycycle[1];
                                Global_Data.rasv.halfBridge3DutyCycle = regelung.output.Bus_Ctrl_Out_e.Dutycycle[2];
                            }
                        break;
                    case test_sine:
                        struct_ZM_In.Soll_iq = 0;
                        struct_ZM_In.Soll_id = 0;
                        struct_ZM_In.Soll_Drehzahl = 0;
                        sine = uz_wavegen_sine(TEST_SINE_AMPLITUDE, TEST_SINE_FREQUENCY_HZ);
                        Global_Data.rasv.halfBridge1DutyCycle = sine;
                        Global_Data.rasv.halfBridge2DutyCycle = sine;
                        Global_Data.rasv.halfBridge3DutyCycle = sine;
                        break;

                    default:
                        struct_ZM_In.Soll_iq = 0;
                        struct_ZM_In.Soll_id = 0;
                        struct_ZM_In.Soll_Drehzahl = 0;
                        break;
                }
    		   break;
    		default:
    			break;
    	}
    
    regelung.input.Bus_ZM_In_c = struct_ZM_In;
	uz_codegen_step(&regelung);
	uz_axi_gpio_write_pin_zero_based(output_gpio, PWR_EN_BIT,  (bool)regelung.output.Bus_Ctrl_Out_e.pwr_en);
	uz_axi_gpio_write_pin_zero_based(output_gpio, BOARD_EN_BIT,  (bool)regelung.output.Bus_Ctrl_Out_e.board_en);

	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
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
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



