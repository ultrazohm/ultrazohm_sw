#ifdef TEST

#include "unity.h"

#include "uz_rlcc.h"
#include "uz_PMSM_config.h"
#include "uz_Transformation.h"
#include "mock_uz_matrix.h"
#include "mock_uz_nn.h"
#include "mock_uz_space_vector_limitation.h"
#include "mock_uz_mlp_three_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_math_constants.h"


void setUp(void)
{
}

void tearDown(void)
{
}

// configuration of neural network
#define NUMBER_OF_INPUTS 9
#define NUMBER_OF_OUTPUTS 2
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64
#define NUMBER_OF_LAYERS 2

float x[NUMBER_OF_INPUTS] = {0};
static float weights1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float bias1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float output1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
static float weights2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {0};
static float bias2[NUMBER_OF_OUTPUTS] = {0};
static float output2[NUMBER_OF_OUTPUTS] = {0};

// initialize config struct and activation function
struct uz_nn_layer_config config_nn[2] = {
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

// Hoerner machine
struct uz_rlcc_config_t config = {
    .ts_in_second = 1.0f / 10000.0f,
    .number_of_observations = 9, // 9
    .max_modulation_index = 1.0f / 1.732050808f,
    .v_dc_rated_V=48.0f,
    .i_rated_A=15.0f,
    .speed_rated_rpm=1500.0f,
    .use_ip_core=false};

void test_uz_rlcc_NeedToImplement(void)
{
    // uz_rlcc_t *uz_rlcc_init(struct uz_rlcc_config_t config, struct uz_nn_layer_config neural_network_config[UZ_NN_MAX_LAYER], uint32_t number_of_layer, float *input_data, uint32_t length_of_input_data)
    uz_rlcc_t *test_instance = uz_rlcc_init(config,
                                            config_nn,
                                            NUMBER_OF_LAYERS,
                                            &x[0],
                                            UZ_MATRIX_SIZE(x));
}

#endif // TEST
