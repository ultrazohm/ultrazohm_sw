#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"

#define EXPERIENCE_BUFFER_LENGTH 5

float reward[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f,4.0f,5.0f};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0,5,10,15,20};
float observation[EXPERIENCE_BUFFER_LENGTH] = {10.0f,1.0f,5.0f,3.0f,2.5f};

struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_observations = UZ_MATRIX_SIZE(observation),
        .length_of_reward = UZ_MATRIX_SIZE(reward),
        .length_of_actions = UZ_MATRIX_SIZE(action),
        .reward = reward,
        .observations = observation,
        .actions = action
};
void setUp(void)
{
}

void tearDown(void)
{
}
void test_uz_dqn_experience_replay_init(void)
{
    uz_dqn_experience_replay_init(configbuffer);  
}

void test_uz_dqn_write_to_buffer(void)
{
    float testfloat = 2.0f;
    float RewardData[3] = {17.0f,18.0f,19.0f};
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer);
    uz_dqn_reset_buffer(buffertesting);
    uz_dqn_push_float_to_buffer(buffertesting,RewardData);
    uz_dqn_get_float_from_buffer(buffertesting, 0, &testfloat);
    TEST_ASSERT_EQUAL_FLOAT(RewardData[0], testfloat);
    uz_dqn_get_float_from_buffer(buffertesting, 1, &testfloat);
    TEST_ASSERT_EQUAL_FLOAT(RewardData[1], testfloat);
    uz_dqn_get_float_from_buffer(buffertesting, 2, &testfloat);
    TEST_ASSERT_EQUAL_FLOAT(RewardData[2], testfloat);
}

void test_uz_dqn_overwrite_zero_value_buffer(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_dqn");
}

void test_uz_dqn_get_from_buffer(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_dqn");
}
#endif // TEST
