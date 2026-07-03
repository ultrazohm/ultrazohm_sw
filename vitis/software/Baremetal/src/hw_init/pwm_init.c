/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */

#include "../include/pwm_init.h"
#include "../defines.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_private.h"
#include "../IP_Cores/PWM_SS_3L_ip_addr.h"
#include "xil_io.h"
#include "xparameters.h"
#include <math.h>


static struct uz_PWM_SS_2L_config_t project_wizard_pwm_2l_0_config = {
    .base_address = XPAR_UZ_PWM_PWM_2L_PWM_AND_SS_CONTROL_V_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .Tristate_HB1 = false,
    .Tristate_HB2 = false,
    .Tristate_HB3 = false,
    .min_pulse_width_in_microseconds = UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US + UZ_PWM_DEADTIME_IN_US,
    .PWM_freq_Hz = UZ_PWM_FREQUENCY,
    .PWM_mode = normalized_input_via_AXI,
    .PWM_en = true,
    .use_external_counter = true,
    .init_dutyCyc_HB1 = 0.5f,
    .init_dutyCyc_HB2 = 0.5f,
    .init_dutyCyc_HB3 = 0.5f,
    .triangle_shift_HB1 = 0.0f,
    .triangle_shift_HB2 = 0.0f,
    .triangle_shift_HB3 = 0.0f,
    .trigger_source = trigger_at_MIN
};

static uz_interlockDeadtime2L project_wizard_deadtime_2l_0 = {
    .base_address = XPAR_UZ_PWM_PWM_2L_UZ_INTERLOCKDEADTIME_0_BASEADDR,
    .clock_frequency_MHz = 100,
    .deadtime_us = UZ_PWM_DEADTIME_IN_US,
    .inverse_bottom_switch = false
};

uz_PWM_SS_2L_t* initialize_project_wizard_pwm_2l_0(void)
{
    return uz_PWM_SS_2L_init(project_wizard_pwm_2l_0_config);
}

uz_interlockDeadtime2L_handle initialize_project_wizard_deadtime_2l_0(void)
{
    return uz_interlockDeadtime2L_init(&project_wizard_deadtime_2l_0);
}


static struct uz_PWM_SS_2L_config_t project_wizard_pwm_2l_1_config = {
    .base_address = XPAR_UZ_PWM_PWM_2L_PWM_AND_SS_CONTROL_V_1_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .Tristate_HB1 = false,
    .Tristate_HB2 = false,
    .Tristate_HB3 = false,
    .min_pulse_width_in_microseconds = UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US + UZ_PWM_DEADTIME_IN_US,
    .PWM_freq_Hz = UZ_PWM_FREQUENCY,
    .PWM_mode = normalized_input_via_AXI,
    .PWM_en = true,
    .use_external_counter = true,
    .init_dutyCyc_HB1 = 0.5f,
    .init_dutyCyc_HB2 = 0.5f,
    .init_dutyCyc_HB3 = 0.5f,
    .triangle_shift_HB1 = 0.0f,
    .triangle_shift_HB2 = 0.0f,
    .triangle_shift_HB3 = 0.0f,
    .trigger_source = trigger_at_MIN
};

static uz_interlockDeadtime2L project_wizard_deadtime_2l_1 = {
    .base_address = XPAR_UZ_PWM_PWM_2L_UZ_INTERLOCKDEADTIME_1_BASEADDR,
    .clock_frequency_MHz = 100,
    .deadtime_us = UZ_PWM_DEADTIME_IN_US,
    .inverse_bottom_switch = false
};

uz_PWM_SS_2L_t* initialize_project_wizard_pwm_2l_1(void)
{
    return uz_PWM_SS_2L_init(project_wizard_pwm_2l_1_config);
}

uz_interlockDeadtime2L_handle initialize_project_wizard_deadtime_2l_1(void)
{
    return uz_interlockDeadtime2L_init(&project_wizard_deadtime_2l_1);
}



#define PROJECT_WIZARD_PWM_3L_BASE_ADDRESS XPAR_UZ_PWM_PWM_3L_PWM_SS_3L_IP_0_BASEADDR
#define PROJECT_WIZARD_PWM_3L_REG_RESET (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + IPCore_Reset_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_ENABLE (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + PWM_en_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_MODE (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + Mode_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_COUNTER_MAX (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + PWM_counter_max_value_int_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_MIN_PULSE_WIDTH (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + PWM_min_pulse_width_0to1_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_DUTY_A (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + m_u1_norm_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_DUTY_B (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + m_u2_norm_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_DUTY_C (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + m_u3_norm_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_TRISTATE_A (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + TriState_HB1_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_TRISTATE_B (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + TriState_HB2_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_TRISTATE_C (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + TriState_HB3_AXI_Data_PWM_SS_3L_ip)

static void project_wizard_pwm_3l_set_status(int32_t enable)
{
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_ENABLE, (int32_t)enable);
}

static void project_wizard_pwm_3l_set_mode(int32_t mode)
{
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_MODE, (int32_t)mode);
}

static void project_wizard_pwm_3l_set_carrier_frequency(float pwm_freq_hz)
{
    float switching_period_s = 1.0f / pwm_freq_hz;
    float counter_max_value = switching_period_s * FPGA_100MHz / 2.0f;
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_COUNTER_MAX, (int32_t)counter_max_value);
}

static void project_wizard_pwm_3l_set_minimum_pulse_width(float minimum_pulse_width)
{
    LIMIT(minimum_pulse_width, 0.0f, 1.0f);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_MIN_PULSE_WIDTH, (int32_t)ldexpf(minimum_pulse_width, Q12));
}

static void project_wizard_pwm_3l_set_tristate(int32_t tristate_a, int32_t tristate_b, int32_t tristate_c)
{
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_TRISTATE_A, (int32_t)tristate_a);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_TRISTATE_B, (int32_t)tristate_b);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_TRISTATE_C, (int32_t)tristate_c);
}

static void project_wizard_pwm_3l_set_duty_cycle(float duty_a, float duty_b, float duty_c)
{
    LIMIT(duty_a, -1.0f, 1.0f);
    LIMIT(duty_b, -1.0f, 1.0f);
    LIMIT(duty_c, -1.0f, 1.0f);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_DUTY_A, (int32_t)ldexpf(duty_a, Q12));
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_DUTY_B, (int32_t)ldexpf(duty_b, Q12));
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_DUTY_C, (int32_t)ldexpf(duty_c, Q12));
}

void initialize_project_wizard_pwm_3l(DS_Data* data)
{
    project_wizard_pwm_3l_set_status(1);
    project_wizard_pwm_3l_set_mode(0);
    project_wizard_pwm_3l_set_carrier_frequency(data->av.pwm_frequency_hz);
    project_wizard_pwm_3l_set_minimum_pulse_width(0.01f);
    project_wizard_pwm_3l_set_duty_cycle(
        data->rasv.pwm_3L_0_halfBridgeDutyCycle_1,
        data->rasv.pwm_3L_0_halfBridgeDutyCycle_2,
        data->rasv.pwm_3L_0_halfBridgeDutyCycle_3
    );
    project_wizard_pwm_3l_set_tristate(
        0,
        0,
        0
    );
}


void project_wizard_update_pwm_outputs(DS_Data* data)
{

    uz_PWM_SS_2L_set_duty_cycle(
        data->objects.project_wizard_pwm_2l_0,
        data->rasv.pwm_2L_0_halfBridgeDutyCycle_1,
        data->rasv.pwm_2L_0_halfBridgeDutyCycle_2,
        data->rasv.pwm_2L_0_halfBridgeDutyCycle_3
    );

    uz_PWM_SS_2L_set_duty_cycle(
        data->objects.project_wizard_pwm_2l_1,
        data->rasv.pwm_2L_1_halfBridgeDutyCycle_1,
        data->rasv.pwm_2L_1_halfBridgeDutyCycle_2,
        data->rasv.pwm_2L_1_halfBridgeDutyCycle_3
    );


    project_wizard_pwm_3l_set_duty_cycle(
        data->rasv.pwm_3L_0_halfBridgeDutyCycle_1,
        data->rasv.pwm_3L_0_halfBridgeDutyCycle_2,
        data->rasv.pwm_3L_0_halfBridgeDutyCycle_3
    );

}
