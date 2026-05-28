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

// Includes from own files
#include "main.h"
#include "Codegen/uz_codegen.h"
#include "xparameters.h"
#include "IP_Cores/uz_JL_invModel_PT1/uz_JL_invModel_PT1.h"
#include "IP_Cores/uz_JL_invModel_ideal/uz_JL_invModel_ideal.h"
#include "APU_RPU_shared.h"
#include "xil_cache.h"
#include "include/javascope.h"
#include "IP_Cores/uz_JL_pmsmModel/uz_JL_pmsmModel.h"
#include "IP_Cores/uz_JL_pmsmModel/uz_JL_pmsmModel_hwAdresse.h"
#include "uz/uz_wavegen/uz_wavegen.h"
#include "uz/uz_signals/uz_signals.h"

uz_JL_invModel_PT1_t *inverter_PT1=NULL;
uz_JL_invModel_ideal_t *inverter_ideal = NULL;
uz_JL_pmsmModel_t *pmsm_PT1 = NULL;
uz_JL_pmsmModel_t *pmsm_ideal = NULL;
uz_IIR_Filter_t *iir_speed = NULL;
uz_IIR_Filter_t *iir_current_a = NULL;
uz_IIR_Filter_t *iir_current_b = NULL;
uz_IIR_Filter_t *iir_current_c = NULL;



extern struct uz_JL_invModel_ideal_output_t ideal_outputs;
extern struct uz_JL_pmsmModel_inputs_t pmsm_pt1_in;
extern struct uz_JL_pmsmModel_inputs_t pmsm_ideal_in;
extern struct uz_JL_invModel_PT1_output_t pt1_outputs;

extern struct uz_JL_pmsmModel_outputs_t pmsm_pt1_out;

struct uz_JL_invModel_ideal_config_t ideal_config ={
		.base_adress = XPAR_UZ_USER_UZ_JL_INVMODEL_IDEAL_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.Udc = 540.0f
};

struct uz_JL_invModel_PT1_config_t PT1_config ={
		.base_adress = XPAR_UZ_USER_UZ_JL_INVMODEL_PT1_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.gain = 1.0f,
		.time_constant = 100000.0f,
};

struct uz_JL_pmsmModel_config_t pmsm_pt1_config = {
		.base_address = XPAR_UZ_USER_UZ_JL_PMSMMODEL_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.mot_J = 0.000875f,
		.mot_p = 4.0f,
		.r_1 = 1.8f,
		.L_d = 0.0072f,
		.L_q = 0.0072f,
		.psi_pm = 0.1423f,
		.mot_F = 0.01f,
		.mot_Fcoeff = 0.001f,
		.M_N = 4.3f,
		.n_N = 5700.0f,
		.i_max = 20.9f,
};

struct uz_JL_pmsmModel_config_t pmsm_ideal_config = {
		.base_address = XPAR_UZ_USER_UZ_JL_PMSMMODEL_1_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.mot_J = 0.000875f,
		.mot_p = 4.0f,
		.r_1 = 1.8f,
		.L_d = 0.0072f,
		.L_q = 0.0072f,
		.psi_pm = 0.1423f,
		.mot_F = 0.01f,
		.mot_Fcoeff = 0.001f,
		.M_N = 4.3f,
		.n_N = 5700.0f,
		.i_max = 20.9f,
};

struct uz_IIR_Filter_config iir_speed_config = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 700.0f,
		.sample_frequency_Hz = 20.0e3f,
};

struct uz_IIR_Filter_config iir_current_config = {
		.selection = LowPass_first_order,
		.cutoff_frequency_Hz = 500.0f,
		.sample_frequency_Hz = 20.0e3f,
};


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
        .halfBridge12DutyCycle = 0.0f},
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / (UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}, .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}}};

enum init_chain
{
    init_assertions = 0,
    wait_for_apu_handshake,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;


uint32_t apu_version_final = 0;
uint32_t rpu_version_final = 0;

uz_codegen regelung;


int main(void)
{
	regelung.input.Bus_ZM_In_f.Fehlermeldung = false;
	regelung.input.Bus_ZM_In_f.Soll_Drehzahl = 0;
	regelung.input.Bus_ZM_In_f.Soll_Regelungsart = Drehzahl;
	regelung.input.Bus_ZM_In_f.Soll_Status = Ready;
	regelung.input.Bus_ZM_In_f.Soll_id = 0;
	regelung.input.Bus_ZM_In_f.Soll_iq = 0;
	regelung.input.Bus_ZM_In_f.Start_Traj = false;
	regelung.input.Bus_PMSM_Out_e.pmsm_Omega_mech = 0;
	regelung.input.Bus_PMSM_Out_e.pmsm_Iuvw[0] = 0;
	regelung.input.Bus_PMSM_Out_e.pmsm_Iuvw[1] = 0;
	regelung.input.Bus_PMSM_Out_e.pmsm_Iuvw[2] = 0;
	regelung.input.Bus_PMSM_Out_e.pmsm_m_mot = 0;
	regelung.input.Bus_PMSM_Out_e.pmsm_phi_mech = 0;
	regelung.output.Bus_Ctrl_Out_k.Dutycycle[0] = 0.0;
	regelung.output.Bus_Ctrl_Out_k.Dutycycle[1] = 0.0;
	regelung.output.Bus_Ctrl_Out_k.Dutycycle[2] = 0.0;
	regelung.output.Bus_Ctrl_Out_k.ctrl_Ualpha = 0;
	regelung.output.Bus_Ctrl_Out_k.ctrl_Ubeta = 0;
	regelung.output.Bus_Ctrl_Out_k.act_pwm = false;

	int status = UZ_SUCCESS;
    while (1)
    {

        switch (initialization_chain)
        {
        case init_assertions:
            uz_rpu_assert_configuration();
            initialization_chain = wait_for_apu_handshake;
            break;
        case wait_for_apu_handshake:
            write_rpu_version(0U);
            do
            {
                apu_version_final = read_apu_version();
            } while (!(apu_version_final == 257U));
            write_rpu_version(UZ_HARDWARE_VERSION);
            do
            {
                apu_version_final = read_apu_version();
            } while ((apu_version_final == 257U));
            write_rpu_version(apu_version_final);
            initialization_chain = init_gpios;
            break;
        case init_gpios:
        	uz_sleep_seconds(5);
            Initialize_AXI_GPIO();
            uz_assert((apu_version_final > 0U) && (apu_version_final <= UZ_HARDWARE_VERSION_MAX));
            uz_frontpanel_button_and_led_init(apu_version_final);
            ultrazohm_state_machine_init(apu_version_final);
            initialization_chain = init_software;
            break;
        case init_software:
            uz_SystemTime_init();
            JavaScope_initialize(&Global_Data);
            uz_codegen_init(&regelung);

            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();

            inverter_ideal = uz_JL_invModel_ideal_init(ideal_config);
            pmsm_ideal = uz_JL_pmsmModel_init(pmsm_ideal_config);
        	uz_JL_pmsmModel_set_inputs(pmsm_ideal, pmsm_ideal_in);

//            uz_axi_write_bool(XPAR_UZ_USER_UZ_JL_PMSMMODEL_1_BASEADDR + IPCore_Enable_uz_JL_pmsmModel, true);

            inverter_PT1 = uz_JL_invModel_PT1_init(PT1_config);
            pmsm_PT1 = uz_JL_pmsmModel_init(pmsm_pt1_config);

            uz_JL_pmsmModel_set_inputs(pmsm_PT1, pmsm_pt1_in);
            uz_axi_write_bool(XPAR_UZ_USER_UZ_JL_PMSMMODEL_0_BASEADDR + IPCore_Enable_uz_JL_pmsmModel, true);

            iir_speed = uz_signals_IIR_Filter_init(iir_speed_config);
            iir_current_a = uz_signals_IIR_Filter_init(iir_current_config);
            iir_current_b = uz_signals_IIR_Filter_init(iir_current_config);
            iir_current_c = uz_signals_IIR_Filter_init(iir_current_config);
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            uz_printf("RPU: Build Date of main.c: %s at %s,\r\n", __DATE__, __TIME__);
            uz_print_bitstream_timestamp();
            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR();
            Global_Data.objects.mux_axi = initialize_uz_mux_axi(); // Initialize the Interrupt-Mux - last line of code before infinite loop
            initialization_chain = infinite_loop;
            break;
        case infinite_loop:
            ultrazohm_state_machine_step();

            break;
        default:
            break;
        }
    }
    return (status);
}
