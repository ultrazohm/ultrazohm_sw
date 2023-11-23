#ifdef TEST

#include "unity.h"

#include "uz_dqn_reward_scaling.h"
#include "uz_nn_activation_functions.h"
#include "uz_array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dqn_reward_scaling_NeedToImplement(void)
{
    float input_values[11] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    float scaled[11] = {0};

    uz_array_float_t input_array = {
        .length = UZ_ARRAY_SIZE(input_values),
        .data = input_values};

    uz_array_float_t output_array = {
        .length = UZ_ARRAY_SIZE(scaled),
        .data = scaled};

    float x_larget_values = 5.0f;

    for (uint32_t i = 0; i < 11; i++)
    {
        output_array.data[i] = uz_dqn_scaling_log(input_array.data[i], x_larget_values);
    }
}

#endif // TEST
