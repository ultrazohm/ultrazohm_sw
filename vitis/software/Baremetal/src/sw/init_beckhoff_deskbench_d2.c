#include "../include/init_beckhoff_deskbench_d2.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_beckhoff_deskbench_d2 = {
    .current_conversion_factors = {
        .a = D2_A_GAIN,
        .b = D2_B_GAIN,
        .c = D2_C_GAIN},
    .current_offsets = {.a = D2_A_OFFSET, .b = D2_B_OFFSET, .c = D2_C_OFFSET},
    .voltage_conversion_factors = {.a = D2_A_VOLTAGE_GAIN, .b = D2_B_VOLTAGE_GAIN, .c = D2_C_VOLTAGE_GAIN},
    .voltage_offsets = {.a = D2_A_VOLTAGE_OFFSET, .b = D2_B_VOLTAGE_OFFSET, .c = D2_C_VOLTAGE_OFFSET},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 1.56f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = D2_IS_PRIME_MOVER,
    .speed_controller_max_torque = 3.0f,
    .speed_controller_kp = 0.1f,
    .speed_controller_ki = 0.5f,
	//    .current_controller_d_kp = 6.67f, // manual tuning based on 1tau delay
	//    .current_controller_d_ki = 1700.0f,
	//    .current_controller_q_kp = 6.67,
	//    .current_controller_q_ki = 1700.0f,
	    .current_controller_d_kp = 5.8333f,
	    .current_controller_d_ki = 1500.0f,
	    .current_controller_q_kp = 5.8333f,
	    .current_controller_q_ki = 1500.0f,
    .setpoint_lower_bound_i_d_in_A = -10.0f,
    .setpoint_upper_bound_i_d_in_A = 10.0f,
    .setpoint_lower_bound_i_q_in_A = -10.0f,
    .setpoint_upper_bound_i_q_in_A = 10.0f,
    .setpoint_upper_bound_speed_in_rpm = 1100.0f,
    .setpoint_lower_bound_speed_in_rpm = -1100.0f,
    .error_upper_bound_speed_in_rpm = 1500.0f,
    .error_lower_bound_speed_in_rpm = -1500.0f,
    .disturbance_input_lower_bound_in_Nm = -10.0f,
    .disturbance_input_upper_bound_in_Nm = 10.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = PRIME_MOVER_SETPOINT_FILTER_CUTTOFF_FREQUENCY,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .nonlinear_machine = false,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .use_rlcc = false,
    .theta_sampling_compensation=1.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t config_PMSM_beckhoff_deskbench_d2 = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.002f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 20.0f};

struct uz_PMSM_flux_fitting_parameter_config_t beckhoff_fitting_d2 = {0};

#if DUT_MACHINE == BECKHOFF_DESKBENCH_D2
#if AGENT == 215
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
static float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a215_l1_td3_gaussian_beckhoff/best_agent/ac_layer1_weights.csv"
};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a215_l1_td3_gaussian_beckhoff/best_agent/ac_layer1_bias.csv"
};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a215_l1_td3_gaussian_beckhoff/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a215_l1_td3_gaussian_beckhoff/best_agent/ac_layer_out_bias.csv"
};
static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif

#if AGENT == 216
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
static float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a216_sidmoid_td3_gaussian_beckhoff/best_agent/ac_layer1_weights.csv"
};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a216_sidmoid_td3_gaussian_beckhoff/best_agent/ac_layer1_bias.csv"
};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a216_sidmoid_td3_gaussian_beckhoff/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a216_sidmoid_td3_gaussian_beckhoff/best_agent/ac_layer_out_bias.csv"
};
static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif

#if AGENT == 309
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
static float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a309_sigmoid_scaled_0_05_td3_beckhoff_250k_30seeds/best_agent/ac_layer1_weights.csv"
};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a309_sigmoid_scaled_0_05_td3_beckhoff_250k_30seeds/best_agent/ac_layer1_bias.csv"
};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a309_sigmoid_scaled_0_05_td3_beckhoff_250k_30seeds/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a309_sigmoid_scaled_0_05_td3_beckhoff_250k_30seeds/best_agent/ac_layer_out_bias.csv"
};
static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif

#if AGENT == 291
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
static float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a291_sig_td3_int_more_obs_beckhoff_250k_2tau/best_agent/ac_layer1_weights.csv"
};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a291_sig_td3_int_more_obs_beckhoff_250k_2tau/best_agent/ac_layer1_bias.csv"
};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a291_sig_td3_int_more_obs_beckhoff_250k_2tau/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a291_sig_td3_int_more_obs_beckhoff_250k_2tau/best_agent/ac_layer_out_bias.csv"
};
static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif


#if AGENT == 305
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
static float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a305_sigmoid_td3_beckhoff_fixed_para_750k_updates/best_agent/ac_layer1_weights.csv"
};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a305_sigmoid_td3_beckhoff_fixed_para_750k_updates/best_agent/ac_layer1_bias.csv"
};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a305_sigmoid_td3_beckhoff_fixed_para_750k_updates/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a305_sigmoid_td3_beckhoff_fixed_para_750k_updates/best_agent/ac_layer_out_bias.csv"
};
static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif
#if AGENT == 253
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
static float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a253_sidmoid_td3_gaussian_beckhoffe_500k_updates/best_agent/ac_layer1_weights.csv"
};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a253_sidmoid_td3_gaussian_beckhoffe_500k_updates/best_agent/ac_layer1_bias.csv"
};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a253_sidmoid_td3_gaussian_beckhoffe_500k_updates/best_agent/ac_layer_out_weights.csv"
};
static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a253_sidmoid_td3_gaussian_beckhoffe_500k_updates/best_agent/ac_layer_out_bias.csv"
};
static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif

// initialize config struct and activation function
static struct uz_nn_layer_config config_nn[2] = {
    [0] = {
        .activation_function = activation_ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(weights1),
        .length_of_bias = UZ_MATRIX_SIZE(bias1),
        .length_of_output = UZ_MATRIX_SIZE(output1),
        .weights = weights1,
        .bias = bias1,
        .output = output1},
    [1] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER, .length_of_weights = UZ_MATRIX_SIZE(weights2), .length_of_bias = UZ_MATRIX_SIZE(bias2), .length_of_output = UZ_MATRIX_SIZE(output2), .weights = weights2, .bias = bias2, .output = output2}};

static struct uz_rlcc_config_t config_rlc_beckhoff_deskbench_d2 = {
    .ts_in_second = 1.0f / 10000.0f,
    .number_of_observations = 9, // 9
    .max_modulation_index = 1.0f / 1.732050808f,
    .v_dc_rated_V = 48.0f,
    .i_rated_A = 8.0f,
    .speed_rated_rpm = 1000.0f*4.0f,
    .use_ip_core = false};
#endif

void init_beckhoff_deskbench_d2(void)
{
#if DUT_MACHINE == BECKHOFF_DESKBENCH_D2
    Global_Data.dut.pmsm_data = &config_PMSM_beckhoff_deskbench_d2;

    Global_Data.rl_controller = uz_rlcc_init(config_rlc_beckhoff_deskbench_d2,
                                             config_nn,
                                             NUMBER_OF_LAYERS,
                                             &x[0],
                                             UZ_MATRIX_SIZE(x));
    config_beckhoff_deskbench_d2.rlcc = Global_Data.rl_controller;
    Global_Data.objects.d2_controller = uz_pmsm_control_init(config_beckhoff_deskbench_d2, config_PMSM_beckhoff_deskbench_d2, beckhoff_fitting_d2);
    Global_Data.dut.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
    Global_Data.dut.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
    Global_Data.dut.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
    Global_Data.dut.torque_constant = 3.0f / 2.0f * config_PMSM_beckhoff_deskbench_d2.polePairs * config_PMSM_beckhoff_deskbench_d2.Psi_PM_Vs;
    Global_Data.profile.id_scale_in_A = 8.0f / 4.2f;
    Global_Data.profile.iq_scale_in_A = 8.0f;
    Global_Data.profile.speed_scale_in_rpm = 1000.0f;
#else
    Global_Data.objects.d2_controller = uz_pmsm_control_init(config_beckhoff_deskbench_d2, config_PMSM_beckhoff_deskbench_d2, beckhoff_fitting_d2);
    Global_Data.prime_mover.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
    Global_Data.prime_mover.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
    Global_Data.prime_mover.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
#endif
}
