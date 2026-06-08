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
#include "xparameters.h"

#if defined(XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR)
#define UZ_LINEAR_PMSM_MODEL_BASE_ADDRESS XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR
#elif defined(XPAR_UZ_PMSM_MODEL_0_BASEADDR)
#define UZ_LINEAR_PMSM_MODEL_BASE_ADDRESS XPAR_UZ_PMSM_MODEL_0_BASEADDR
#else
#error "No base address macro found for uz_pmsm_model_0"
#endif

#define UZ_LINEAR_PMSM_MODEL_IP_CORE_FREQUENCY_HZ 100000000U
#define UZ_LINEAR_PMSM_MODEL_R_PH_OHM 0.51f
#define UZ_LINEAR_PMSM_MODEL_LD_HENRY 0.002f
#define UZ_LINEAR_PMSM_MODEL_LQ_HENRY 0.002f
#define UZ_LINEAR_PMSM_MODEL_PSI_PM_VS 0.042f
#define UZ_LINEAR_PMSM_MODEL_J_KG_M_SQUARED 0.000108f
#define UZ_LINEAR_PMSM_MODEL_I_MAX_AMPERE 12.0f
#define UZ_LINEAR_PMSM_MODEL_FRICTION_COEFFICIENT 0.001f
#define UZ_LINEAR_PMSM_MODEL_COULOMB_FRICTION_CONSTANT 0.01f
#define UZ_LINEAR_PMSM_MODEL_POLE_PAIRS 1.0f

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

static const struct uz_pmsm_swmodel_config_t pmsm_swmodel_config = {
    .sample_time = INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE / (UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor),
    .pmsm_parameters = {
        .R_ph_Ohm = UZ_LINEAR_PMSM_MODEL_R_PH_OHM,
        .Ld_Henry = UZ_LINEAR_PMSM_MODEL_LD_HENRY,
        .Lq_Henry = UZ_LINEAR_PMSM_MODEL_LQ_HENRY,
        .Psi_PM_Vs = UZ_LINEAR_PMSM_MODEL_PSI_PM_VS,
        .polePairs = UZ_LINEAR_PMSM_MODEL_POLE_PAIRS,
        .J_kg_m_squared = UZ_LINEAR_PMSM_MODEL_J_KG_M_SQUARED,
        .I_max_Ampere = UZ_LINEAR_PMSM_MODEL_I_MAX_AMPERE}};

static const struct uz_pmsmModel_config_t pmsm_model_config = {
    .base_address = UZ_LINEAR_PMSM_MODEL_BASE_ADDRESS,
    .ip_core_frequency_Hz = UZ_LINEAR_PMSM_MODEL_IP_CORE_FREQUENCY_HZ,
    .simulate_mechanical_system = false,
    .r_1 = UZ_LINEAR_PMSM_MODEL_R_PH_OHM,
    .L_d = UZ_LINEAR_PMSM_MODEL_LD_HENRY,
    .L_q = UZ_LINEAR_PMSM_MODEL_LQ_HENRY,
    .psi_pm = UZ_LINEAR_PMSM_MODEL_PSI_PM_VS,
    .polepairs = UZ_LINEAR_PMSM_MODEL_POLE_PAIRS,
    .inertia = UZ_LINEAR_PMSM_MODEL_J_KG_M_SQUARED,
    .coulomb_friction_constant = UZ_LINEAR_PMSM_MODEL_COULOMB_FRICTION_CONSTANT,
    .friction_coefficient = UZ_LINEAR_PMSM_MODEL_FRICTION_COEFFICIENT};

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
#include "APU_RPU_shared.h"
#include "xil_cache.h"

uint32_t apu_version_final = 0;
uint32_t rpu_version_final = 0;

int main(void)
{
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
            Global_Data.objects.pmsm_swmodel = uz_pmsm_swmodel_init(pmsm_swmodel_config);
            JavaScope_initialize(&Global_Data);
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
            uz_adcLtc2311_ip_core_init();
            Global_Data.objects.pmsm_model = uz_pmsmModel_init(pmsm_model_config);
            Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
            Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
            Global_Data.objects.deadtime_interlock_d1_pin_12_to_17 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17();
            Global_Data.objects.deadtime_interlock_d1_pin_18_to_23 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23();
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, true);
            uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, true);
            Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
            Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
            Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
            Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
            PWM_3L_Initialize(&Global_Data); // three-level modulator
            Global_Data.objects.encoder_D5 = initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
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
