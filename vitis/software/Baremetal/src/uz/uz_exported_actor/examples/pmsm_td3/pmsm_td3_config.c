/* Generated from manifest.json; do not edit. */
#include "pmsm_td3_config.h"
#include <stddef.h>

_Static_assert(UZ_EXPORTED_ACTOR_ABI == 1U, "Actor adapter ABI mismatch");
static float layer1_weights[288] = {
#include "layer1_weights.csv"
};
static float layer1_bias[32] = {
#include "layer1_bias.csv"
};
static float layer1_output[32];
static float layer2_weights[1024] = {
#include "layer2_weights.csv"
};
static float layer2_bias[32] = {
#include "layer2_bias.csv"
};
static float layer2_output[32];
static float layer3_weights[64] = {
#include "layer3_weights.csv"
};
static float layer3_bias[2] = {
#include "layer3_bias.csv"
};
static float layer3_output[2];
static struct uz_nn_layer_config layers[UZ_NN_MAX_LAYER] = {
    {.activation_function=activation_ReLU, .number_of_neurons=32U, .number_of_inputs=9U, .length_of_weights=288U, .length_of_bias=32U, .length_of_output=32U, .weights=layer1_weights, .bias=layer1_bias, .output=layer1_output},
    {.activation_function=activation_ReLU, .number_of_neurons=32U, .number_of_inputs=32U, .length_of_weights=1024U, .length_of_bias=32U, .length_of_output=32U, .weights=layer2_weights, .bias=layer2_bias, .output=layer2_output},
    {.activation_function=activation_tanh, .number_of_neurons=2U, .number_of_inputs=32U, .length_of_weights=64U, .length_of_bias=2U, .length_of_output=2U, .weights=layer3_weights, .bias=layer3_bias, .output=layer3_output},
};
static float observations[9];
static void observe(const struct uz_exported_actor_signals *signals, const struct uz_exported_actor_state *state, float *out) {
    (void)state;
    out[0] = ((signals->reference[0] - signals->current[0]) / 8.0f);
    out[1] = (state->integral[0] * 10000.0f);
    out[2] = ((signals->reference[1] - signals->current[1]) / 8.0f);
    out[3] = (state->integral[1] * 10000.0f);
    out[4] = (signals->current[0] / 8.0f);
    out[5] = (signals->current[1] / 8.0f);
    out[6] = (signals->speed_rpm / 1000.0f);
    out[7] = (signals->applied_voltage[0] / 27.7128124f);
    out[8] = (signals->applied_voltage[1] / 27.7128124f);
}
static void advance(const struct uz_exported_actor_signals *signals, struct uz_exported_actor_state *state, bool saturated) {
    (void)signals; (void)state; (void)saturated;
    if (!saturated) {
        float increment0 = ((9.99999975e-05f * (signals->reference[0] - signals->current[0])) / 8.0f);
        float increment1 = ((9.99999975e-05f * (signals->reference[1] - signals->current[1])) / 8.0f);
        state->integral[0] += increment0;
        state->integral[1] += increment1;
    }
}
static void map_action(const float *action, float *out) {
    out[0] = (action[0] * 27.7128124f);
    out[1] = (action[1] * 27.7128124f);
}
const struct uz_exported_actor_config pmsm_td3_config = {
    .abi=1U, .contract_sha256="b225b44621f04a1faac389d941023f63c76cfb9ab6afce275a55b920a5af6d6f",
    .layers=layers, .layer_count=3U, .observations=observations,
    .input_count=9U, .output_count=2U, .command_count=2U,
    .discrete_actions=NULL,
    .control_frequency_hz=10000.0f, .delay_steps=1U,
    .limiter=UZ_ACTOR_AXIS_PRIORITY, .limiter_reference_current=true,
    .voltage_limit=27.7128124f, .initial_integral={0.0f, 0.0f},
    .observe=observe, .advance=advance, .map_action=map_action
};
