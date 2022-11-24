#include "../include/uz_CIL_6ph.h"


uz_pmsm_model6ph_dq_t* cil_pmsm = NULL; 
uz_pmsm6ph_transformation_t* cil_transformation = NULL;
uz_inverter_3ph_t* cil_inverter1 = NULL;
uz_inverter_3ph_t* cil_inverter2 = NULL;
uz_PWM_SS_2L_t* cil_pwm1 = NULL;
uz_PWM_SS_2L_t* cil_pwm2 = NULL;
uz_CIL_objects_t cil_objects = {0};

struct uz_pmsm_model6ph_dq_config_t cil_pmsm_comfig = {
    .base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .polepairs = 3.0f,
    .r_1 = 31.3f,
    .inductance.d = 0.46f,
    .inductance.q = 0.46f,
    .inductance.x = 0.08f,
    .inductance.y = 0.08f,
    .inductance.z1 = 0.08f,
    .inductance.z2 = 0.08f,
    .psi_pm = 0.072f,
    .friction_coefficient = 0.001f,
    .coulomb_friction_constant = 0.001f,
    .inertia = 0.001f,
    .simulate_mechanical_system = false,
    .switch_pspl = false};

struct uz_pmsm6ph_config_t cil_transformation_config = {
    .base_address = XPAR_UZ_USER_UZ_SIXPHASE_VSD_TRAN_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f};

struct uz_inverter_3ph_config_t cil_inverter1_config = {
    .base_address = XPAR_UZ_USER_UZ_INVERTER_3PH_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = 200.0f};

struct uz_inverter_3ph_config_t cil_inverter2_config = {
    .base_address = XPAR_UZ_USER_UZ_INVERTER_3PH_1_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = 200.0f};

struct uz_PWM_SS_2L_config_t cil_pwm1_config = {
        .base_address= XPAR_UZ_USER_PWM_AND_SS_CONTROL_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000.0f,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 10e3f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true
};

struct uz_PWM_SS_2L_config_t cil_pwm2_config = {
        .base_address= XPAR_UZ_USER_PWM_AND_SS_CONTROL_V_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000.0f,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 10e3f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true
};

void init_CIL_6phase(uz_CIL_objects_t* cil_objects)
{
    cil_objects->cil_pmsm = uz_pmsm_model6ph_dq_init(cil_pmsm_comfig);
    cil_objects->cil_transformation = uz_pmsm6ph_transformation_init(cil_transformation_config);
    cil_objects->cil_inverter1 = uz_inverter_3ph_init(cil_inverter1_config);
    cil_objects->cil_inverter2 = uz_inverter_3ph_init(cil_inverter2_config);
}

void init_PWM_CIL_6phase(uz_CIL_objects_t* cil_objects)
{
    cil_objects->cil_pwm1 = uz_PWM_SS_2L_init(cil_pwm1_config);
	cil_objects->cil_pwm2 = uz_PWM_SS_2L_init(cil_pwm2_config);
}
