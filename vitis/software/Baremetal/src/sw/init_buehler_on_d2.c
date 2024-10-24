#include "../include/init_buehler_on_d2.h"
extern DS_Data Global_Data;

struct uz_pmsm_control_configuration_t config_buehler = {
    .current_conversion_factors = {
        .a = 12.2889f,
        .b = 11.8330f,
        .c = 11.7894f},
    .current_offsets = {.a = 0.0164f, .b = 0.0161f, .c = 0.0184f},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 3.171, // 2.251070, // 2.151070f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = D2_IS_PRIME_MOVER,
    .speed_controller_max_torque = 0.5f,
    .speed_controller_kp = 0.0025f,
    .speed_controller_ki = 0.01f,
    .current_controller_d_kp = 0.83333f,
    .current_controller_d_ki = 283.33f,
    .current_controller_q_kp = 0.83333f,
    .current_controller_q_ki = 283.33f,
    .setpoint_lower_bound_i_d_in_A = -5.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -5.0f,
    .setpoint_upper_bound_i_q_in_A = 5.0f,
    .setpoint_upper_bound_speed_in_rpm = 2500.0f,
    .setpoint_lower_bound_speed_in_rpm = -2500.0f,
    .error_upper_bound_speed_in_rpm = 3500.0f,
    .error_lower_bound_speed_in_rpm = -3500.0f,
    .disturbance_input_lower_bound_in_Nm = -10.0f, // disable disturbance input for now
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
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t config_PMSM_buehler = {
    .R_ph_Ohm = 0.085f,
    .Ld_Henry = 0.00025f,
    .Lq_Henry = 0.00025f,
    .Psi_PM_Vs = 0.006f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 15.0f};

struct uz_PMSM_flux_fitting_parameter_config_t buehler_fitting = {0};


#if DUT_MACHINE == BUEHLER
    #if AGENT == 221
        #define NUMBER_OF_INPUTS 9
        #define NUMBER_OF_OUTPUTS 2
        #define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
        #define NUMBER_OF_LAYERS 2
        static float x[NUMBER_OF_INPUTS] = {0};
        static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
        #include "../experiments/a221_l1_td3_gaussian_buehler/best_agent/ac_layer1_weights.csv"
        };
        static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
        #include "../experiments/a221_l1_td3_gaussian_buehler/best_agent/ac_layer1_bias.csv"
        };
        static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
        static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
        #include "../experiments/a221_l1_td3_gaussian_buehler/best_agent/ac_layer_out_weights.csv"
        };
        static float bias2[NUMBER_OF_OUTPUTS] = {
        #include "../experiments/a221_l1_td3_gaussian_buehler/best_agent/ac_layer_out_bias.csv"
        };
        static float output2[NUMBER_OF_OUTPUTS] = {0};
    #endif
#if AGENT == 234
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
        static float x[NUMBER_OF_INPUTS] = {0};
        static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a234_sigmoid_td3_gaussian_buehler/best_agent/ac_layer1_weights.csv"
        };
        static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a234_sigmoid_td3_gaussian_buehler/best_agent/ac_layer1_bias.csv"
        };
        static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
        static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a234_sigmoid_td3_gaussian_buehler/best_agent/ac_layer_out_weights.csv"
        };
        static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a234_sigmoid_td3_gaussian_buehler/best_agent/ac_layer_out_bias.csv"
        };
        static float output2[NUMBER_OF_OUTPUTS] = {0};
#endif
#if AGENT == 255
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2
        static float x[NUMBER_OF_INPUTS] = {0};
        static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a255_sidmoid_td3_gaussian_buehler_500k_updates/best_agent/ac_layer1_weights.csv"
        };
        static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "../experiments/a255_sidmoid_td3_gaussian_buehler_500k_updates/best_agent/ac_layer1_bias.csv"
        };
        static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
        static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "../experiments/a255_sidmoid_td3_gaussian_buehler_500k_updates/best_agent/ac_layer_out_weights.csv"
        };
        static float bias2[NUMBER_OF_OUTPUTS] = {
#include "../experiments/a255_sidmoid_td3_gaussian_buehler_500k_updates/best_agent/ac_layer_out_bias.csv"
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

        static struct uz_rlcc_config_t config_rlc_buehler = {
            .ts_in_second = 1.0f / 10000.0f,
            .number_of_observations = 9, // 9
            .max_modulation_index = 1.0f / 1.732050808f,
            .v_dc_rated_V = 48.0f,
            .i_rated_A = 8.6f,
            .speed_rated_rpm = 4000.0f,
            .use_ip_core = false};
#endif

        void init_buehler_on_d2(void)
        {
#if DUT_MACHINE == BUEHLER
            Global_Data.rl_controller = uz_rlcc_init(config_rlc_buehler,
                                                     config_nn,
                                                     NUMBER_OF_LAYERS,
                                                     &x[0],
                                                     UZ_MATRIX_SIZE(x));
            config_buehler.rlcc = Global_Data.rl_controller;
            Global_Data.objects.d2_controller = uz_pmsm_control_init(config_buehler, config_PMSM_buehler, buehler_fitting);
            Global_Data.dut.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
            Global_Data.dut.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
            Global_Data.dut.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
            Global_Data.dut.torque_constant = 3.0f / 2.0f * config_PMSM_buehler.polePairs * config_PMSM_buehler.Psi_PM_Vs;
            Global_Data.profile.id_scale_in_A = 1.0f / 4.2f;
            Global_Data.profile.iq_scale_in_A = 1.0f;
            Global_Data.profile.speed_scale_in_rpm = 1000.0f;
#else
    Global_Data.objects.d2_controller = uz_pmsm_control_init(config_buehler, config_PMSM_buehler, buehler_fitting);
    Global_Data.prime_mover.actual_data = uz_pmsm_control_get_actual_data(Global_Data.objects.d2_controller);
    Global_Data.prime_mover.reference_values = uz_pmsm_control_get_reference_values(Global_Data.objects.d2_controller);
    Global_Data.prime_mover.measurement_values = uz_pmsm_control_get_uz_pmsm_measurement_values(Global_Data.objects.d2_controller);
#endif
}
