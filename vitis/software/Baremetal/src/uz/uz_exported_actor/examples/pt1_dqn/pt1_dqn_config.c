/* Generated from manifest.json; do not edit. */
#include "pt1_dqn_config.h"
#include <stddef.h>

_Static_assert(UZ_EXPORTED_ACTOR_ABI == 1U, "Actor adapter ABI mismatch");
static float layer1_weights[64] = {
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
static float layer3_weights[96] = {
#include "layer3_weights.csv"
};
static float layer3_bias[3] = {
#include "layer3_bias.csv"
};
static float layer3_output[3];
static struct uz_nn_layer_config layers[UZ_NN_MAX_LAYER] = {
    {.activation_function=activation_ReLU, .number_of_neurons=32U, .number_of_inputs=2U, .length_of_weights=64U, .length_of_bias=32U, .length_of_output=32U, .weights=layer1_weights, .bias=layer1_bias, .output=layer1_output},
    {.activation_function=activation_ReLU, .number_of_neurons=32U, .number_of_inputs=32U, .length_of_weights=1024U, .length_of_bias=32U, .length_of_output=32U, .weights=layer2_weights, .bias=layer2_bias, .output=layer2_output},
    {.activation_function=activation_linear, .number_of_neurons=3U, .number_of_inputs=32U, .length_of_weights=96U, .length_of_bias=3U, .length_of_output=3U, .weights=layer3_weights, .bias=layer3_bias, .output=layer3_output},
};
static float observations[2];
static void observe(const struct uz_exported_actor_signals *signals, const struct uz_exported_actor_state *state, float *out) {
    (void)state;
    out[0] = signals->output;
    out[1] = signals->reference[0];
}
static void advance(const struct uz_exported_actor_signals *signals, struct uz_exported_actor_state *state, bool saturated) {
    (void)signals; (void)state; (void)saturated;
}
static void map_action(const float *action, float *out) {
    out[0] = (-1.0f + (((action[0] + 1.0f) * 2.0f) / 2.0f));
}
static const float discrete_actions[] = {-1.0f, 0.0f, 1.0f};
const struct uz_exported_actor_config pt1_dqn_config = {
    .abi=1U, .contract_sha256="5651fc5876866f8ef2e6945bc9c7db477be626654cd1a39c59a451d1601997e4",
    .layers=layers, .layer_count=3U, .observations=observations,
    .input_count=2U, .output_count=3U, .command_count=1U,
    .discrete_actions=discrete_actions,
    .control_frequency_hz=10000.0f, .delay_steps=0U,
    .limiter=UZ_ACTOR_NO_LIMITER, .limiter_reference_current=false,
    .voltage_limit=0.0f, .initial_integral={0.0f, 0.0f},
    .observe=observe, .advance=advance, .map_action=map_action
};
