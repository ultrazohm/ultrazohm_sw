#include "../include/deskbench_control.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_PMSM_config/uz_PMSM_config.h"
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_math_constants.h"
#include "../IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../include/uz_platform_state_machine.h"
#include "xparameters.h"
#include <math.h>

#define DESKBENCH_CURRENT_TO_AMPERE 12.5f
#define DESKBENCH_VOLTAGE_TO_VOLTS 12.0f
#define DESKBENCH_MAX_CURRENT_AMPERE 15.0f
#define DESKBENCH_MAX_INVERTER_TEMP_DEGC 100.0f
#define DESKBENCH_MIN_V_DC_VOLTS 5.0f

static const struct uz_PMSM_t deskbench_beckhoff_am8141 = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.002f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .I_max_Ampere = 12.0f,
    .J_kg_m_squared = 0.000108f
};

static void disable_prime_mover(DS_Data *data);
static void disable_dut(DS_Data *data);
static void reset_prime_mover_control(DS_Data *data);
static void reset_dut_control(DS_Data *data);
static void control_prime_mover(DS_Data *data);
static void control_dut(DS_Data *data);
static void control_dut_pmsm_model(DS_Data *data);
static float mean_inverter_temperature(struct uz_inverter_adapter_outputs_t status);
static void stop_on_safety_limit(DS_Data *data);
static struct uz_CurrentControl_config make_current_control_config(void);

void deskbench_control_init(DS_Data *data)
{
    struct uz_PI_Controller_config speed_config = {
        .type = UZ_PI_PARALLEL,
        .Kp = 0.2f,
        .Ki = 2.0f,
        .samplingTime_sec = 1.0f / UZ_PWM_FREQUENCY,
        .upper_limit = 6.0f,
        .lower_limit = -6.0f
    };
    struct uz_SetPoint_config setpoint_config = {
        .config_PMSM = deskbench_beckhoff_am8141,
        .control_type = FOC,
        .id_ref_Ampere = 0.0f,
        .is_field_weakening_enabled = false,
        .motor_type = SMPMSM,
        .relative_torque_tolerance = 0.01f
    };
    struct uz_SpeedControl_config speed_control_config = {
        .config_controller = speed_config
    };
    struct uz_IIR_Filter_config speed_filter_config = {
        .selection = LowPass_first_order,
        .cutoff_frequency_Hz = 0.5f,
        .sample_frequency_Hz = UZ_PWM_FREQUENCY
    };

    data->av.deskbench_machine_polepairs = deskbench_beckhoff_am8141.polePairs;
    data->objects.deskbench_current_ctrl_prime_mover = uz_CurrentControl_init(make_current_control_config());
    data->objects.deskbench_current_ctrl_dut = uz_CurrentControl_init(make_current_control_config());
#if UZ_DESKBENCH_CONTROL_DUT_PMSM_MODEL_ACTIVE
    struct uz_pmsmModel_config_t pmsm_model_config = {
        .base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
        .ip_core_frequency_Hz = 100000000U,
        .polepairs = deskbench_beckhoff_am8141.polePairs,
        .r_1 = deskbench_beckhoff_am8141.R_ph_Ohm,
        .L_d = deskbench_beckhoff_am8141.Ld_Henry,
        .L_q = deskbench_beckhoff_am8141.Lq_Henry,
        .psi_pm = deskbench_beckhoff_am8141.Psi_PM_Vs,
        .friction_coefficient = 0.001f,
        .coulomb_friction_constant = 0.0f,
        .inertia = deskbench_beckhoff_am8141.J_kg_m_squared,
        .simulate_mechanical_system = false
    };
    data->objects.deskbench_dut_pmsm_model = uz_pmsmModel_init(pmsm_model_config);
    uz_pmsmModel_reset(data->objects.deskbench_dut_pmsm_model);
#endif
    data->objects.deskbench_setpoint_ctrl_prime_mover = uz_SetPoint_init(setpoint_config);
    data->objects.deskbench_speed_ctrl_prime_mover = uz_SpeedControl_init(speed_control_config);
    data->objects.deskbench_speed_filter_prime_mover = uz_signals_IIR_Filter_init(speed_filter_config);
}

void deskbench_update_measurements(DS_Data *data)
{
    data->av.deskbench_dut_i_a_A = data->av.adc_ltc2311_a1_ch3 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_dut_i_b_A = data->av.adc_ltc2311_a1_ch2 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_dut_i_c_A = data->av.adc_ltc2311_a1_ch1 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_dut_i_dc_A = data->av.adc_ltc2311_a1_ch4 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_dut_v_a_V = data->av.adc_ltc2311_a1_ch7 * DESKBENCH_VOLTAGE_TO_VOLTS;
    data->av.deskbench_dut_v_b_V = data->av.adc_ltc2311_a1_ch6 * DESKBENCH_VOLTAGE_TO_VOLTS;
    data->av.deskbench_dut_v_c_V = data->av.adc_ltc2311_a1_ch5 * DESKBENCH_VOLTAGE_TO_VOLTS;
    data->av.deskbench_dut_v_dc_V = data->av.adc_ltc2311_a1_ch0 * DESKBENCH_VOLTAGE_TO_VOLTS;

    data->av.deskbench_prime_mover_i_a_A = data->av.adc_ltc2311_a2_ch3 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_prime_mover_i_b_A = data->av.adc_ltc2311_a2_ch2 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_prime_mover_i_c_A = data->av.adc_ltc2311_a2_ch1 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_prime_mover_i_dc_A = data->av.adc_ltc2311_a2_ch4 * DESKBENCH_CURRENT_TO_AMPERE;
    data->av.deskbench_prime_mover_v_a_V = data->av.adc_ltc2311_a2_ch7 * DESKBENCH_VOLTAGE_TO_VOLTS;
    data->av.deskbench_prime_mover_v_b_V = data->av.adc_ltc2311_a2_ch6 * DESKBENCH_VOLTAGE_TO_VOLTS;
    data->av.deskbench_prime_mover_v_c_V = data->av.adc_ltc2311_a2_ch5 * DESKBENCH_VOLTAGE_TO_VOLTS;
    data->av.deskbench_prime_mover_v_dc_V = data->av.adc_ltc2311_a2_ch0 * DESKBENCH_VOLTAGE_TO_VOLTS;

    data->av.deskbench_dut_omega_mech_rad_s = data->av.resolver_pl_interface_d4_3_omega_mech_rad_s;
    data->av.deskbench_dut_speed_rpm = data->av.resolver_pl_interface_d4_3_n_mech_rpm;
    data->av.deskbench_dut_theta_el_rad = data->av.resolver_pl_interface_d4_3_position_el_2pi;
    data->av.deskbench_dut_mean_temp_degC = mean_inverter_temperature(data->av.inverter_adapter_d2);

    data->av.deskbench_prime_mover_omega_mech_rad_s = data->av.resolver_pl_interface_d4_1_omega_mech_rad_s;
    data->av.deskbench_prime_mover_speed_rpm = data->av.resolver_pl_interface_d4_1_n_mech_rpm;
    data->av.deskbench_prime_mover_theta_el_rad = data->av.resolver_pl_interface_d4_1_position_el_2pi;
    data->av.deskbench_prime_mover_mean_temp_degC = mean_inverter_temperature(data->av.inverter_adapter_d1);

    uz_3ph_abc_t dut_i_abc = {
        .a = data->av.deskbench_dut_i_a_A,
        .b = data->av.deskbench_dut_i_b_A,
        .c = data->av.deskbench_dut_i_c_A
    };
    uz_3ph_abc_t prime_mover_i_abc = {
        .a = data->av.deskbench_prime_mover_i_a_A,
        .b = data->av.deskbench_prime_mover_i_b_A,
        .c = data->av.deskbench_prime_mover_i_c_A
    };
    uz_3ph_dq_t dut_i_dq = uz_transformation_3ph_abc_to_dq(dut_i_abc, data->av.deskbench_dut_theta_el_rad);
    uz_3ph_dq_t prime_mover_i_dq = uz_transformation_3ph_abc_to_dq(prime_mover_i_abc, data->av.deskbench_prime_mover_theta_el_rad);
    data->av.deskbench_dut_i_d_A = dut_i_dq.d;
    data->av.deskbench_dut_i_q_A = dut_i_dq.q;
    data->av.deskbench_prime_mover_i_d_A = prime_mover_i_dq.d;
    data->av.deskbench_prime_mover_i_q_A = prime_mover_i_dq.q;
}

void deskbench_enter_idle(DS_Data *data)
{
    disable_prime_mover(data);
    disable_dut(data);
    reset_prime_mover_control(data);
    reset_dut_control(data);
}

void deskbench_enter_running(DS_Data *data)
{
#if UZ_DESKBENCH_CONTROL_DUT_PMSM_MODEL_ACTIVE
    disable_prime_mover(data);
    disable_dut(data);
#else
#if UZ_DESKBENCH_CONTROL_PRIME_MOVER_ACTIVE
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_0, false, false, false);
    uz_inverter_adapter_set_PWM_EN(data->objects.inverter_adapter_d1, true);
#else
    disable_prime_mover(data);
#endif

#if UZ_DESKBENCH_CONTROL_DUT_ACTIVE
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_1, false, false, false);
    uz_inverter_adapter_set_PWM_EN(data->objects.inverter_adapter_d2, true);
#else
    disable_dut(data);
#endif
#endif
}

void deskbench_control_step(DS_Data *data)
{
#if UZ_DESKBENCH_CONTROL_DUT_PMSM_MODEL_ACTIVE
    disable_prime_mover(data);
    disable_dut(data);
    control_dut_pmsm_model(data);
#else
    stop_on_safety_limit(data);
#if UZ_DESKBENCH_CONTROL_PRIME_MOVER_ACTIVE
    control_prime_mover(data);
#else
    disable_prime_mover(data);
#endif

#if UZ_DESKBENCH_CONTROL_DUT_ACTIVE
    control_dut(data);
#else
    disable_dut(data);
#endif
#endif
}

static struct uz_CurrentControl_config make_current_control_config(void)
{
    struct uz_PI_Controller_config id_config = {
        .type = UZ_PI_PARALLEL,
        .Kp = deskbench_beckhoff_am8141.Ld_Henry / (2.0f / UZ_PWM_FREQUENCY),
        .Ki = deskbench_beckhoff_am8141.R_ph_Ohm / (2.0f / UZ_PWM_FREQUENCY),
        .samplingTime_sec = 1.0f / UZ_PWM_FREQUENCY,
        .upper_limit = 48.0f,
        .lower_limit = -48.0f
    };
    struct uz_PI_Controller_config iq_config = {
        .type = UZ_PI_PARALLEL,
        .Kp = deskbench_beckhoff_am8141.Lq_Henry / (2.0f / UZ_PWM_FREQUENCY),
        .Ki = deskbench_beckhoff_am8141.R_ph_Ohm / (2.0f / UZ_PWM_FREQUENCY),
        .samplingTime_sec = 1.0f / UZ_PWM_FREQUENCY,
        .upper_limit = 48.0f,
        .lower_limit = -48.0f
    };
    struct uz_CurrentControl_config config = {
        .config_PMSM = deskbench_beckhoff_am8141,
        .config_id = id_config,
        .config_iq = iq_config,
        .decoupling_select = no_decoupling,
        .max_modulation_index = 0.57735f
    };
    return config;
}

static void control_prime_mover(DS_Data *data)
{
    if (data->av.deskbench_prime_mover_v_dc_V <= DESKBENCH_MIN_V_DC_VOLTS) {
        disable_prime_mover(data);
        return;
    }

    uz_3ph_dq_t i_actual = {
        .d = data->av.deskbench_prime_mover_i_d_A,
        .q = data->av.deskbench_prime_mover_i_q_A
    };
    data->rasv.deskbench_prime_mover_n_ref_rpm_filtered = uz_signals_IIR_Filter_sample(
        data->objects.deskbench_speed_filter_prime_mover,
        data->rasv.deskbench_prime_mover_n_ref_rpm);
    data->rasv.deskbench_prime_mover_M_ref_Nm = uz_SpeedControl_sample(
        data->objects.deskbench_speed_ctrl_prime_mover,
        data->av.deskbench_prime_mover_omega_mech_rad_s,
        data->rasv.deskbench_prime_mover_n_ref_rpm_filtered);
    data->rasv.deskbench_prime_mover_i_dq_ref_A = uz_SetPoint_sample(
        data->objects.deskbench_setpoint_ctrl_prime_mover,
        data->av.deskbench_prime_mover_omega_mech_rad_s,
        data->rasv.deskbench_prime_mover_M_ref_Nm,
        data->av.deskbench_prime_mover_v_dc_V,
        i_actual);
    uz_3ph_dq_t v_ref = uz_CurrentControl_sample(
        data->objects.deskbench_current_ctrl_prime_mover,
        data->rasv.deskbench_prime_mover_i_dq_ref_A,
        i_actual,
        data->av.deskbench_prime_mover_v_dc_V,
        data->av.deskbench_prime_mover_omega_mech_rad_s * data->av.deskbench_machine_polepairs);
    struct uz_DutyCycle_t duty = uz_Space_Vector_Modulation(
        v_ref,
        data->av.deskbench_prime_mover_v_dc_V,
        data->av.deskbench_prime_mover_theta_el_rad);
    data->av.deskbench_prime_mover_v_d_V = v_ref.d;
    data->av.deskbench_prime_mover_v_q_V = v_ref.q;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_1 = duty.DutyCycle_A;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_2 = duty.DutyCycle_B;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_3 = duty.DutyCycle_C;
}

static void control_dut(DS_Data *data)
{
    if (data->av.deskbench_dut_v_dc_V <= DESKBENCH_MIN_V_DC_VOLTS) {
        disable_dut(data);
        return;
    }

    uz_3ph_dq_t i_actual = {
        .d = data->av.deskbench_dut_i_d_A,
        .q = data->av.deskbench_dut_i_q_A
    };
    uz_3ph_dq_t v_ref = uz_CurrentControl_sample(
        data->objects.deskbench_current_ctrl_dut,
        data->rasv.deskbench_dut_i_dq_ref_A,
        i_actual,
        data->av.deskbench_dut_v_dc_V,
        data->av.deskbench_dut_omega_mech_rad_s * data->av.deskbench_machine_polepairs);
    struct uz_DutyCycle_t duty = uz_Space_Vector_Modulation(
        v_ref,
        data->av.deskbench_dut_v_dc_V,
        data->av.deskbench_dut_theta_el_rad);
    data->av.deskbench_dut_v_d_V = v_ref.d;
    data->av.deskbench_dut_v_q_V = v_ref.q;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_1 = duty.DutyCycle_A;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_2 = duty.DutyCycle_B;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_3 = duty.DutyCycle_C;
}

static void control_dut_pmsm_model(DS_Data *data)
{
#if UZ_DESKBENCH_CONTROL_DUT_PMSM_MODEL_ACTIVE
    uz_pmsmModel_trigger_output_strobe(data->objects.deskbench_dut_pmsm_model);
    struct uz_pmsmModel_outputs_t model_outputs = uz_pmsmModel_get_outputs(data->objects.deskbench_dut_pmsm_model);
    data->av.deskbench_dut_pmsm_model_i_d_A = model_outputs.i_d_A;
    data->av.deskbench_dut_pmsm_model_i_q_A = model_outputs.i_q_A;
    data->av.deskbench_dut_pmsm_model_torque_Nm = model_outputs.torque_Nm;
    data->av.deskbench_dut_pmsm_model_omega_mech_rad_s = model_outputs.omega_mech_1_s;
    data->av.deskbench_dut_i_d_A = model_outputs.i_d_A;
    data->av.deskbench_dut_i_q_A = model_outputs.i_q_A;
    data->av.deskbench_dut_omega_mech_rad_s = model_outputs.omega_mech_1_s;
    data->av.deskbench_dut_speed_rpm = (model_outputs.omega_mech_1_s * 60.0f) / (2.0f * UZ_PIf);
    data->av.deskbench_dut_v_dc_V = UZ_DESKBENCH_DUT_PMSM_MODEL_V_DC;

    uz_3ph_dq_t i_actual = {
        .d = model_outputs.i_d_A,
        .q = model_outputs.i_q_A
    };
    uz_3ph_dq_t v_ref = uz_CurrentControl_sample(
        data->objects.deskbench_current_ctrl_dut,
        data->rasv.deskbench_dut_i_dq_ref_A,
        i_actual,
        UZ_DESKBENCH_DUT_PMSM_MODEL_V_DC,
        model_outputs.omega_mech_1_s * data->av.deskbench_machine_polepairs);
    data->av.deskbench_dut_v_d_V = v_ref.d;
    data->av.deskbench_dut_v_q_V = v_ref.q;

    struct uz_pmsmModel_inputs_t model_inputs = {
        .v_d_V = v_ref.d,
        .v_q_V = v_ref.q,
        .omega_mech_1_s = data->rasv.deskbench_prime_mover_n_ref_rpm/60.0f,
        .load_torque = 0.0f};
    uz_pmsmModel_set_inputs(data->objects.deskbench_dut_pmsm_model, model_inputs);
    uz_pmsmModel_trigger_input_strobe(data->objects.deskbench_dut_pmsm_model);
#else
    (void)data;
#endif
}

static void disable_prime_mover(DS_Data *data)
{
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_0, true, true, true);
    uz_inverter_adapter_set_PWM_EN(data->objects.inverter_adapter_d1, false);
}

static void disable_dut(DS_Data *data)
{
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_1, true, true, true);
    uz_inverter_adapter_set_PWM_EN(data->objects.inverter_adapter_d2, false);
}

static void reset_prime_mover_control(DS_Data *data)
{
    uz_CurrentControl_reset(data->objects.deskbench_current_ctrl_prime_mover);
    uz_SpeedControl_reset(data->objects.deskbench_speed_ctrl_prime_mover);
    uz_signals_IIR_Filter_reset(data->objects.deskbench_speed_filter_prime_mover);
    data->rasv.deskbench_prime_mover_n_ref_rpm = 0.0f;
    data->rasv.deskbench_prime_mover_n_ref_rpm_filtered = 0.0f;
    data->rasv.deskbench_prime_mover_M_ref_Nm = 0.0f;
    data->rasv.deskbench_prime_mover_i_dq_ref_A.d = 0.0f;
    data->rasv.deskbench_prime_mover_i_dq_ref_A.q = 0.0f;
    data->av.deskbench_prime_mover_v_d_V = 0.0f;
    data->av.deskbench_prime_mover_v_q_V = 0.0f;
}

static void reset_dut_control(DS_Data *data)
{
    uz_CurrentControl_reset(data->objects.deskbench_current_ctrl_dut);
#if UZ_DESKBENCH_CONTROL_DUT_PMSM_MODEL_ACTIVE
    uz_pmsmModel_reset(data->objects.deskbench_dut_pmsm_model);
#endif
    data->rasv.deskbench_dut_i_dq_ref_A.d = 0.0f;
    data->rasv.deskbench_dut_i_dq_ref_A.q = 0.0f;
    data->av.deskbench_dut_v_d_V = 0.0f;
    data->av.deskbench_dut_v_q_V = 0.0f;
}

static float mean_inverter_temperature(struct uz_inverter_adapter_outputs_t status)
{
    return (status.ChipTempDegreesCelsius_H1 + status.ChipTempDegreesCelsius_L1 +
            status.ChipTempDegreesCelsius_H2 + status.ChipTempDegreesCelsius_L2 +
            status.ChipTempDegreesCelsius_H3 + status.ChipTempDegreesCelsius_L3) / 6.0f;
}

static void stop_on_safety_limit(DS_Data *data)
{
    bool current_limit_exceeded =
        (fabsf(data->av.deskbench_dut_i_a_A) > DESKBENCH_MAX_CURRENT_AMPERE) ||
        (fabsf(data->av.deskbench_dut_i_b_A) > DESKBENCH_MAX_CURRENT_AMPERE) ||
        (fabsf(data->av.deskbench_dut_i_c_A) > DESKBENCH_MAX_CURRENT_AMPERE) ||
        (fabsf(data->av.deskbench_prime_mover_i_a_A) > DESKBENCH_MAX_CURRENT_AMPERE) ||
        (fabsf(data->av.deskbench_prime_mover_i_b_A) > DESKBENCH_MAX_CURRENT_AMPERE) ||
        (fabsf(data->av.deskbench_prime_mover_i_c_A) > DESKBENCH_MAX_CURRENT_AMPERE);
    bool temperature_limit_exceeded =
        (data->av.deskbench_dut_mean_temp_degC > DESKBENCH_MAX_INVERTER_TEMP_DEGC) ||
        (data->av.deskbench_prime_mover_mean_temp_degC > DESKBENCH_MAX_INVERTER_TEMP_DEGC);

    if (current_limit_exceeded || temperature_limit_exceeded) {
        ultrazohm_state_machine_set_stop(true);
    }
}
