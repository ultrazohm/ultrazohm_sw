#pragma once

#include "uz_dqn.h"
#include "uz_dqn_expirience_buffer.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_array.h"
#include "uz_matrix.h"
#include "uz_prng.h"
#include "uz_environment_bitflip.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "export_array.h"

#include "uz_prng.h"
#include "../uz_prng_squares/uz_prng_squares.h"
#include "../uz_prng_halton/uz_prng_halton.h"
#include "../uz_prng_mtwister/uz_prng_mtwister.h"
#include "../uz_prng_pcg/uz_prng_pcg.h"
#include "../uz_prng_xoshiro/uz_prng_xoshiro.h"
#include "mt19937.h"
#include "splitmix64.h"
#include "xoshiro128plusplus.h"

#include "uz_environment_pt1.h"

#include <assert.h>

void uz_nn_trained_export(uz_nn_t *self);

void eval_steps_bitflip(uz_dqn_t *dqn, uz_environment_bitflip_t *env, uz_array_float_t reward_log, uint32_t number_of_eval_episodes, uz_prng_t *prng);
void train_bitflip(uint32_t number_of_epochs, uz_environment_bitflip_t *env, uz_prng_t *env_prng, uz_dqn_t *dqn, uz_array_float_t episode_loss, uz_array_float_t cumulative_reward, uz_array_float_t global_reward_metric, uz_array_float_t epsilon_per_epsiode);
void export_abitrary_number_of_arrays(uz_array_float_t **export_array, size_t length_of_export_array, char table_header[], char absolute_path[], uint32_t index);

// PT1
void train_pt1(uint32_t number_of_epochs, uz_environment_pt1_t *env, uz_prng_t *env_prng, uz_dqn_t *dqn, uz_array_float_t episode_loss, uz_array_float_t cumulative_reward, uz_array_float_t global_reward_metric, uz_array_float_t epsilon_per_epsiode, uint32_t steps_per_episode);
void eval_steps_pt1(uz_dqn_t *dqn, uz_environment_pt1_t *env, uz_array_float_t reward_log, uint32_t number_of_eval_episodes, uz_prng_t *prng, uz_array_float_t set_point, uz_array_float_t error, uz_array_float_t input, uz_array_float_t output, uz_array_float_t time_step, uz_array_float_t eval_run_number, uint32_t steps_per_episode);
