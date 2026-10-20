#ifndef UZ_EXPORTED_ACTOR_H
#define UZ_EXPORTED_ACTOR_H

#include <stdbool.h>
#include <stdint.h>
#include "../uz_nn/uz_nn.h"
#include "../uz_matrix/uz_matrix.h"

#define UZ_EXPORTED_ACTOR_ABI 1U

/* Physical inputs, before this control tick. PT1 uses output and reference[0]. */
struct uz_exported_actor_signals {
    float output;
    float current[2];
    float reference[2];
    float speed_rpm;
    float applied_voltage[2];
};

struct uz_exported_actor_state {
    float integral[2];
    float applied_voltage[2];
    float queue[2][2];
};

enum uz_exported_actor_limiter { UZ_ACTOR_NO_LIMITER, UZ_ACTOR_AXIS_PRIORITY, UZ_ACTOR_RADIAL };

/* Generated configuration: immutable semantics, statically allocated NN buffers. */
struct uz_exported_actor_config {
    uint32_t abi;
    const char *contract_sha256;
    struct uz_nn_layer_config *layers;
    uint32_t layer_count;
    float *observations;
    uint32_t input_count;
    uint32_t output_count;
    uint32_t command_count;
    const float *discrete_actions; /* NULL for continuous; [output_count, command_count] otherwise */
    float control_frequency_hz;
    uint32_t delay_steps;
    enum uz_exported_actor_limiter limiter;
    bool limiter_reference_current;
    float voltage_limit;
    float initial_integral[2];
    void (*observe)(const struct uz_exported_actor_signals *, const struct uz_exported_actor_state *, float *);
    void (*advance)(const struct uz_exported_actor_signals *, struct uz_exported_actor_state *, bool);
    void (*map_action)(const float *, float *);
};

typedef struct {
    const struct uz_exported_actor_config *config;
    uz_nn_t *network;
    struct uz_matrix_t input_matrix;
    struct uz_exported_actor_state state;
    float requested[2];
    float limited[2];
    float applied[2];
    uint32_t action_index;
    bool saturated;
} uz_exported_actor_t;

/* One instance per generated config. Call init once; reset between episodes.
 * actual_frequency_hz is checked against the exported sampling assumption.
 * Calls must be serialized; generated uz_nn output buffers are shared.
 */
void uz_exported_actor_init(uz_exported_actor_t *self, const struct uz_exported_actor_config *config, float actual_frequency_hz);
void uz_exported_actor_reset(uz_exported_actor_t *self, const struct uz_exported_actor_state *initial);
/* Executes observe -> network -> map -> limit -> advance once.
 * applied is the command for THIS plant interval after the configured queue.
 * A hardware scheduler must not add this delay a second time.
 */
void uz_exported_actor_sample(uz_exported_actor_t *self, struct uz_exported_actor_signals signals);
/* Separate actuator operation also supports deterministic limiter conformance tests. */
void uz_exported_actor_limit(const struct uz_exported_actor_config *config,
    const struct uz_exported_actor_signals *signals, const float requested[2], float limited[2], bool *saturated);
#endif
