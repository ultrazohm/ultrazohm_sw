#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_matrix.h"

#define EXPERIENCE_BUFFER_LENGTH 3
#define NUMBEROFOBS 5
float zerofloat [EXPERIENCE_BUFFER_LENGTH] = {0.0f};
uint32_t zerouint [EXPERIENCE_BUFFER_LENGTH] = {0};
float reward[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0,5,50};
float observation[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {0.0f};

struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_buffer = UZ_MATRIX_SIZE(reward),
        .columns_of_observations = NUMBEROFOBS,
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
    uz_dqn_experience_replay_init(configbuffer, EXPERIENCE_BUFFER_LENGTH);  
}

void test_uz_dqn_clear_buffer(void)
{
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH);
    uz_dqn_reset_buffer(buffertesting);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, observation, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(zerouint, action, EXPERIENCE_BUFFER_LENGTH);
}
void test_uz_dqn_write_to_buffer(void)
{
    float RewardData1 = 7.7f;
    uint32_t action1 = 1;
    float ObsData1[5] = {1.1f,2.1f,5.1f,2.1f,0.0f};
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH);
    uz_dqn_push_to_buffer(buffertesting,RewardData1,action1,ObsData1);
    float RewardData2 = 17.7f;
    uint32_t action2 = 5;
    float ObsData2[5] = {6.1f,7.1f,8.1f,9.1f,5.0f};
    uz_dqn_push_to_buffer(buffertesting,RewardData2,action2,ObsData2);
    float RewardData3 = -27.7f;
    uint32_t action3 = 0;
    float ObsData3[5] = {2.0f,2.1f,9.1f,2.1f,7.7f};
    uz_dqn_push_to_buffer(buffertesting,RewardData3,action3,ObsData3);
    // buffer vollgeschrieben, jetz wird wieder ab 0 geschrieben
    float RewardData4 = -300.7f;
    uint32_t action4 = 100;
    float ObsData4[5] = {5.0f,2.8f,9.9999f,0.0f,15.15f};
    uz_dqn_push_to_buffer(buffertesting,RewardData4,action4,ObsData4);
    // checken wie die daten jetzt 
    uz_dqn_reset_buffer(buffertesting);
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
