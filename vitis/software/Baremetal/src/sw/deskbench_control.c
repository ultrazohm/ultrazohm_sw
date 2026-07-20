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
#include "../uz/uz_signals/uz_signals.h"

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
    .J_kg_m_squared = 0.000108f};

static struct uz_pmsm_control_configuration_t pmsm_control_am8141_config = {
    .theta_el_offset = 0.0f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = false,
    .speed_controller_kp = 0.01f,
    .speed_controller_ki = 0.05f,
    .current_controller_d_kp = 5.8333f,
    .current_controller_d_ki = 1500.0f,
    .current_controller_q_kp = 5.8333f,
    .current_controller_q_ki = 1500.0f,
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 2.0f, .lower_bound = -2.0f},
        .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .speed_in_rpm = {.upper_bound = 1100.0f, .lower_bound = -1100.0f},
        .disturbance_input_in_Nm = {.upper_bound = 10.0f, .lower_bound = -10.0f}},
    .safe_operating_region = {
    		.speed_in_rpm = {.upper_bound = 1500.0f, .lower_bound = -1500.0f},
			.i_d_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
			.i_q_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
    		.i_abc_in_A = {.upper_bound = 20.0f, .lower_bound = -20.0f},
			.v_dc_in_V = {.upper_bound = 48.0f, .lower_bound = 0.0f},
			.i_dc_in_A = {.upper_bound = 15.0f, .lower_bound = -15.0f}
    },
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.0f,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .theta_sampling_compensation = 0.0f,
    .theta_svm_delay_compensation = 1.5f,
    .voltage_theta_shift = 0.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f}};

static void reset_prime_mover_control(DS_Data *data);
static void reset_dut_control(DS_Data *data);
static void control_dut_pmsm_model(DS_Data *data);
static float mean_inverter_temperature(struct uz_inverter_adapter_outputs_t status);

void deskbench_control_init(DS_Data *data)
{
    struct uz_pmsmModel_config_t dut_pmsm_model_config = {
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
        .simulate_mechanical_system = false};
    struct uz_pmsmModel_config_t prime_mover_pmsm_model_config = {
        .base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_1_BASEADDR,
        .ip_core_frequency_Hz = 100000000U,
        .polepairs = deskbench_beckhoff_am8141.polePairs,
        .r_1 = deskbench_beckhoff_am8141.R_ph_Ohm,
        .L_d = deskbench_beckhoff_am8141.Ld_Henry,
        .L_q = deskbench_beckhoff_am8141.Lq_Henry,
        .psi_pm = deskbench_beckhoff_am8141.Psi_PM_Vs,
        .friction_coefficient = 0.001f,
        .coulomb_friction_constant = 0.0f,
        .inertia = deskbench_beckhoff_am8141.J_kg_m_squared,
        .simulate_mechanical_system = false};
    data->objects.dut_pmsm_model = uz_pmsmModel_init(dut_pmsm_model_config);
    data->objects.prime_mover_pmsm_model = uz_pmsmModel_init(prime_mover_pmsm_model_config);
    uz_pmsmModel_reset(data->objects.dut_pmsm_model);
    uz_pmsmModel_reset(data->objects.prime_mover_pmsm_model);

    data->objects.prime_mover_control = uz_pmsm_control_init(pmsm_control_am8141_config, deskbench_beckhoff_am8141);
    uz_pmsm_control_enable(data->objects.prime_mover_control, true);
    data->objects.prime_mover_measurements = uz_pmsm_control_get_pmsm_measurement_values(data->objects.prime_mover_control);
    data->objects.prime_mover_actual_data = uz_pmsm_control_get_actual_data(data->objects.prime_mover_control);
    data->objects.prime_mover_reference_values = uz_pmsm_control_get_reference_values(data->objects.prime_mover_control);
    uz_pmsm_control_current_control_tune_magnitude_optimum(data->objects.prime_mover_control, 1.5f * pmsm_control_am8141_config.sample_time);
    
    data->objects.dut_control = uz_pmsm_control_init(pmsm_control_am8141_config, deskbench_beckhoff_am8141);
    data->objects.dut_actual_data = uz_pmsm_control_get_actual_data(data->objects.dut_control);
    data->objects.dut_measurements = uz_pmsm_control_get_pmsm_measurement_values(data->objects.dut_control);
    data->objects.dut_reference_values = uz_pmsm_control_get_reference_values(data->objects.dut_control);
    uz_pmsm_control_current_control_tune_magnitude_optimum(data->objects.dut_control, 1.5f * pmsm_control_am8141_config.sample_time);
    uz_pmsm_control_enable(data->objects.dut_control, true);
}

float dut_theta_mech_rad = 0.0f;
float prime_mover_theta_mech_rad = 0.0f;

void deskbench_update_measurements(DS_Data *data)
{
    if (data->use_cil)
    {
        // read CIL data
        uz_pmsmModel_trigger_output_strobe(data->objects.dut_pmsm_model);
        struct uz_pmsmModel_outputs_t dut_model_outputs = uz_pmsmModel_get_outputs(data->objects.dut_pmsm_model);
        uz_3ph_dq_t dut_model_i_dq_A = {
            .d = dut_model_outputs.i_d_A,
            .q = dut_model_outputs.i_q_A,
            .zero = 0.0f};

        dut_theta_mech_rad = uz_signals_wrap(dut_theta_mech_rad + dut_model_outputs.omega_mech_1_s * 1.0f / 10000.0f, 2.0f * UZ_PIf);
        float dut_theta_el_rad = dut_theta_mech_rad * 4.0f; // pole pairs, get somehow from configuration or move to driver.

        data->av.dut_measurements.i_abc_in_A = uz_transformation_3ph_dq_to_abc(dut_model_i_dq_A, dut_theta_el_rad); // also move this to driver as a dedicated get i_abc function.
        data->av.dut_measurements.v_abc_in_V = uz_transformation_3ph_dq_to_abc(data->objects.dut_reference_values->v_dq_in_V, dut_theta_el_rad);
        data->av.dut_measurements.omega_mech_rad_per_sec = dut_model_outputs.omega_mech_1_s;
        data->av.dut_measurements.theta_mech = dut_theta_mech_rad;
        data->av.dut_measurements.v_dc_in_V = 48.0f;
        data->av.dut_measurements.i_dc_in_A = 0.0f;

        uz_pmsmModel_trigger_output_strobe(data->objects.prime_mover_pmsm_model);
        struct uz_pmsmModel_outputs_t prime_mover_model_outputs = uz_pmsmModel_get_outputs(data->objects.prime_mover_pmsm_model);
        uz_3ph_dq_t prime_mover_model_i_dq_A = {
            .d = prime_mover_model_outputs.i_d_A,
            .q = prime_mover_model_outputs.i_q_A,
            .zero = 0.0f};

        prime_mover_theta_mech_rad = uz_signals_wrap(prime_mover_theta_mech_rad + prime_mover_model_outputs.omega_mech_1_s * 1.0f / 10000.0f, 2.0f * UZ_PIf);
        float prime_mover_theta_el_rad = prime_mover_theta_mech_rad * 4.0f; // pole pairs, get somehow from configuration or move to driver. --> move to uz_pmsmModel_get_theta_el_rad

        data->av.prime_mover_measurements.i_abc_in_A = uz_transformation_3ph_dq_to_abc(prime_mover_model_i_dq_A, prime_mover_theta_el_rad); // also move this to driver as a dedicated get i_abc function.
        data->av.prime_mover_measurements.v_abc_in_V = uz_transformation_3ph_dq_to_abc(data->objects.prime_mover_reference_values->v_dq_in_V, prime_mover_theta_el_rad);
        data->av.prime_mover_measurements.omega_mech_rad_per_sec = prime_mover_model_outputs.omega_mech_1_s;
        data->av.prime_mover_measurements.theta_mech = prime_mover_theta_mech_rad;
        data->av.prime_mover_measurements.v_dc_in_V = 48.0f;
        data->av.prime_mover_measurements.i_dc_in_A = 0.0f;

        // When coupling prime mover and dut in CIL, the torque of the the dut has to be the load torque of the primve mover? Its coupled with infinite stiffness this way, first or second order coupling could be achieved in software by defining a transfer function between the two torque values with damping and stiffness. Coupling would be implemented in isr.c
    }
    else
    {
        data->av.dut_measurements.i_abc_in_A.a = data->av.adc_ltc2311_a1_ch3 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.dut_measurements.i_abc_in_A.b = data->av.adc_ltc2311_a1_ch2 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.dut_measurements.i_abc_in_A.c = data->av.adc_ltc2311_a1_ch1 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.dut_measurements.i_dc_in_A = data->av.adc_ltc2311_a1_ch4 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.dut_measurements.v_abc_in_V.a = data->av.adc_ltc2311_a1_ch7 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.dut_measurements.v_abc_in_V.b = data->av.adc_ltc2311_a1_ch6 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.dut_measurements.v_abc_in_V.c = data->av.adc_ltc2311_a1_ch5 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.dut_measurements.v_dc_in_V = data->av.adc_ltc2311_a1_ch0 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.dut_measurements.omega_mech_rad_per_sec = data->av.resolver_pl_interface_d4_3_omega_mech_rad_s;
        data->av.dut_measurements.theta_mech = data->av.resolver_pl_interface_d4_3_position_mech_2pi;

        data->av.prime_mover_measurements.i_abc_in_A.a = data->av.adc_ltc2311_a2_ch3 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.prime_mover_measurements.i_abc_in_A.b = data->av.adc_ltc2311_a2_ch2 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.prime_mover_measurements.i_abc_in_A.c = data->av.adc_ltc2311_a2_ch1 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.prime_mover_measurements.i_dc_in_A = data->av.adc_ltc2311_a2_ch4 * DESKBENCH_CURRENT_TO_AMPERE;
        data->av.prime_mover_measurements.v_abc_in_V.a = data->av.adc_ltc2311_a2_ch7 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.prime_mover_measurements.v_abc_in_V.b = data->av.adc_ltc2311_a2_ch6 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.prime_mover_measurements.v_abc_in_V.c = data->av.adc_ltc2311_a2_ch5 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.prime_mover_measurements.v_dc_in_V = data->av.adc_ltc2311_a2_ch0 * DESKBENCH_VOLTAGE_TO_VOLTS;
        data->av.prime_mover_measurements.omega_mech_rad_per_sec = data->av.resolver_pl_interface_d4_1_omega_mech_rad_s;
        data->av.prime_mover_measurements.theta_mech = data->av.resolver_pl_interface_d4_1_position_mech_2pi;
    }
    data->av.prime_mover_mean_temp_degC = mean_inverter_temperature(data->av.inverter_adapter_d2);
    data->av.dut_mean_temp_degC = mean_inverter_temperature(data->av.inverter_adapter_d1);
}

static void control_dut_pmsm_model(DS_Data *data)
{
    //    uz_pmsmModel_trigger_output_strobe(data->objects.dut_pmsm_model);
    //    struct uz_pmsmModel_outputs_t model_outputs = uz_pmsmModel_get_outputs(data->objects.dut_pmsm_model);
    //    data->av.dut_pmsm_model_i_d_A = model_outputs.i_d_A;
    //    data->av.dut_pmsm_model_i_q_A = model_outputs.i_q_A;
    //    data->av.dut_pmsm_model_torque_Nm = model_outputs.torque_Nm;
    //    data->av.dut_pmsm_model_omega_mech_rad_s = model_outputs.omega_mech_1_s;
    //    data->av.dut_i_d_A = model_outputs.i_d_A;
    //    data->av.dut_i_q_A = model_outputs.i_q_A;
    //    data->av.dut_omega_mech_rad_s = model_outputs.omega_mech_1_s;
    //    data->av.dut_speed_rpm = (model_outputs.omega_mech_1_s * 60.0f) / (2.0f * UZ_PIf);
    //    data->av.dut_v_dc_V = UZ_DESKBENCH_DUT_PMSM_MODEL_V_DC;
    //
    //    uz_3ph_dq_t i_actual = {
    //        .d = model_outputs.i_d_A,
    //        .q = model_outputs.i_q_A};
    //    uz_3ph_dq_t v_ref = uz_CurrentControl_sample(
    //        data->objects.deskbench_current_ctrl_dut,
    //        data->rasv.deskbench_dut_i_dq_ref_A,
    //        i_actual,
    //        UZ_DESKBENCH_DUT_PMSM_MODEL_V_DC,
    //        model_outputs.omega_mech_1_s * data->av.machine_polepairs);
    //    data->av.dut_v_d_V = v_ref.d;
    //    data->av.dut_v_q_V = v_ref.q;
    //
}

void disable_prime_mover(DS_Data *data)
{
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_1_d2, true, true, true);
}

void disable_dut(DS_Data *data)
{
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_0_d1, true, true, true);
}

void enable_prime_mover(DS_Data *data)
{
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_1_d2, false, false, false);
}

void enable_dut(DS_Data *data)
{
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_0_d1, false, false, false);
}

static float mean_inverter_temperature(struct uz_inverter_adapter_outputs_t status)
{
    return (status.ChipTempDegreesCelsius_H1 + status.ChipTempDegreesCelsius_L1 +
            status.ChipTempDegreesCelsius_H2 + status.ChipTempDegreesCelsius_L2 +
            status.ChipTempDegreesCelsius_H3 + status.ChipTempDegreesCelsius_L3) /
           6.0f;
}
