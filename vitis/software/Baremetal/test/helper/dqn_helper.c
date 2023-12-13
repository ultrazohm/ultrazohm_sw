#include "dqn_helper.h"

void uz_nn_trained_export(uz_nn_t *self)
{
    char *fname = "test/uz/uz_dqn/trained_layer1_weights.csv";
    uz_nn_layer_matrix_export(uz_nn_get_weight_matrix(self, 1U), fname);
    char *fname1 = "test/uz/uz_dqn/trained_layer2_weights.csv";
    uz_nn_layer_matrix_export(uz_nn_get_weight_matrix(self, 2U), fname1);
    char *fname3 = "test/uz/uz_dqn/trained_layer1_bias.csv";
    uz_nn_layer_matrix_export(uz_nn_get_bias_matrix(self, 1U), fname3);
    char *fname4 = "test/uz/uz_dqn/trained_layer2_bias.csv";
    uz_nn_layer_matrix_export(uz_nn_get_bias_matrix(self, 2U), fname4);
}

void eval_steps_bitflip(uz_dqn_t *dqn, uz_environment_bitflip_t *env, uz_array_float_t reward_log, uint32_t number_of_eval_episodes, uz_prng_t *prng)
{
    assert(dqn != NULL);
    assert(env != NULL);
    assert(reward_log.length == number_of_eval_episodes);

    uz_dqn_set_epsilon(dqn, 0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < number_of_eval_episodes; i++)
    {
        uz_environment_bitflip_reset(env, prng);
        uz_environment_bitflip_step_one_episode(dqn, false, env);
        reward_log.data[i] = uz_environment_bitflip_get_cumulative_reward(env);
    }
}

void train_bitflip(uint32_t number_of_epochs, uz_environment_bitflip_t *env, uz_prng_t *env_prng, uz_dqn_t *dqn, uz_array_float_t episode_loss, uz_array_float_t cumulative_reward, uz_array_float_t global_reward_metric, uz_array_float_t epsilon_per_epsiode)
{

    for (uint32_t epoch = 0; epoch < number_of_epochs; epoch++)
    {
        uz_environment_bitflip_reset(env, env_prng);
        episode_loss.data[epoch] = uz_environment_bitflip_step_one_episode(dqn, true, env);
        cumulative_reward.data[epoch] = uz_environment_bitflip_get_cumulative_reward(env);
        if (epoch == 0)
        {
            global_reward_metric.data[epoch] = uz_environment_bitflip_get_cumulative_reward(env);
        }
        else
        {
            global_reward_metric.data[epoch] = 0.99f * global_reward_metric.data[epoch - 1] + 0.01f * uz_environment_bitflip_get_cumulative_reward(env);
        }
        epsilon_per_epsiode.data[epoch] = uz_dqn_get_epsilon(dqn);
    }
}

void export_abitrary_number_of_arrays(uz_array_float_t **export_array, size_t length_of_export_array, char table_header[], char absolute_path[], uint32_t index)
{
    assert(export_array != NULL);
    for (size_t i = 0; i < length_of_export_array; i++)
    {
        assert(export_array[0]->length == export_array[i]->length);
    }

    char path[1000];
    char str2[1000];
    strcpy(path, absolute_path);

    sprintf(str2, "_%d.csv", index);
    strcat(path, str2);

    char string_buffer[1000] = {0};
    char string_buffer2[1000] = {0};
    char newline[] = "\n";
    char comma[] = ",";

    FILE *file1 = fopen(path, "w");
    if (file1 != NULL)
    {
        // Write header
        fprintf(file1, table_header);
        for (uint32_t i = 0; i < export_array[0]->length; i++)
        {
            // Build full string with all exported arrays
            for (size_t j = 0; j < length_of_export_array; j++)
            {
                sprintf(string_buffer, "%.8f", (double)export_array[j]->data[i]);
                if (j < (length_of_export_array - 1))
                { // No comma in last line
                    strcat(string_buffer, comma);
                }
                strcat(string_buffer2, string_buffer);
            }
            strcat(string_buffer2, newline);
            fprintf(file1, string_buffer2);
            string_buffer2[0] = '\0'; // Resets the string_buffer2 after each line
        }
    }
}


