#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "mtwister.h"

#define EXPERIENCE_BUFFER_LENGTH 3
#define NUMBEROFOBS 5
#define MINIBATCHSIZE 2

float zerofloat [EXPERIENCE_BUFFER_LENGTH] = {0.0f};
int32_t zerouint [EXPERIENCE_BUFFER_LENGTH] = {0};
float reward[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f};
int32_t action[EXPERIENCE_BUFFER_LENGTH] = {0,5,50};
float q_value[EXPERIENCE_BUFFER_LENGTH] = {1.4f,12.3f,7.13f};
float observation[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {2.0f,3.0f,6.0f,5.0f,7.0f,12.0f,12.5f,12.75f,12.85f,12.95f,100.0f,200.0f,300.0f,400.0f,500.0f};

float reward_set[EXPERIENCE_BUFFER_LENGTH] = {7.7f,-27.7f,300.0f};
int32_t action_set[EXPERIENCE_BUFFER_LENGTH] = {1,0,-1};
float q_value_set[EXPERIENCE_BUFFER_LENGTH] = {5.3f,6.4f,7.99f};
float observation_set[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {1.1f,2.1f,5.1f,2.1f,0.0f,2.0f,2.1f,5.1f,2.1f,0.0f,2.0f,-1.0f,5.1f,2.1f,0.0f};

struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_buffer = UZ_MATRIX_SIZE(reward),
        .columns_of_observations = NUMBEROFOBS,
        .reward = reward,
        .qvalues =q_value,
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
    uz_dqn_experience_replay_init(configbuffer, EXPERIENCE_BUFFER_LENGTH,0);  
}

void test_uz_dqn_get_from_buffer(void)
{
    float read_reward = 0.0f;
    int32_t read_action = 0;
    float readobs[5] = {0.0f};
    float read_q_value = 0.0f;
    struct uz_matrix_t readobs_matrix = {0};
    uz_matrix_t *obsread = uz_matrix_init(&readobs_matrix, readobs, NUMBEROFOBS, 1, 5);
    uz_dqn_experience_replay_t *bufferread = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH,0);
    uz_dqn_get_from_buffer(bufferread, &read_reward,&read_q_value,&read_action,obsread,2);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, read_reward);
    TEST_ASSERT_EQUAL_FLOAT(7.13f, read_q_value);
    float comparer[5] = {100.0f,200.0f,300.0f,400.0f,500.0f};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(comparer, readobs, NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32(50, read_action);
}

void test_uz_dqn_clear_buffer(void)
{
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH,0);
    uz_dqn_reset_buffer(buffertesting);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, q_value, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, observation, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_INT32_ARRAY(zerouint, action, EXPERIENCE_BUFFER_LENGTH);
}
void test_uz_dqn_write_to_buffer(void)
{
    float RewardData1 = 7.7f;
    float QData1 = 5.3f;
    int32_t action1 = 1;
    float ObsData1[5] = {1.1f,2.1f,5.1f,2.1f,0.0f};
    struct uz_matrix_t obs_matrix = {0};
    uz_matrix_t *obs = uz_matrix_init(&obs_matrix, ObsData1, UZ_MATRIX_SIZE(ObsData1), 1, 5);
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH,0);
    uz_dqn_push_to_buffer(buffertesting,&RewardData1,&QData1,&action1,obs);
    ObsData1[0] = 2.0f;
    float RewardData2 = -27.7f;
    float QData2 = 6.4f;
    int32_t action2 = 0;
    uz_dqn_push_to_buffer(buffertesting,&RewardData2,&QData2,&action2,obs);
    ObsData1[1] = -1.0f;
    float RewardData3 = 300.0f;
    float QData3 = 7.99f;
    int32_t action3 = -1;
    uz_dqn_push_to_buffer(buffertesting,&RewardData3,&QData3,&action3,obs);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(reward_set, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(q_value_set, q_value, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(observation_set, observation, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(action_set, action, EXPERIENCE_BUFFER_LENGTH);

}

void test_uz_dqn_overwrite_first_values(void){
    // float data
    float rew[EXPERIENCE_BUFFER_LENGTH] = {-777.7f,-27.7f,300.0f};
    int32_t act[EXPERIENCE_BUFFER_LENGTH] = {777,0,-1};
    float qval[EXPERIENCE_BUFFER_LENGTH] = {543.3f,6.4f,7.99f};
    float obbs[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {7.0f,7.0f,7.0f,7.0f,7.0f,2.0f,2.1f,5.1f,2.1f,0.0f,2.0f,-1.0f,5.1f,2.1f,0.0f};

    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH,EXPERIENCE_BUFFER_LENGTH);
    float RewardData4 = -777.7f;
    int32_t action4 = 777;
    float qval4 = 543.3f;
    float ObsData[5] = {7.0f,7.0f,7.0f,7.0f,7.0f};
    struct uz_matrix_t obs_matrix = {0};
    uz_matrix_t *obs = uz_matrix_init(&obs_matrix, ObsData, UZ_MATRIX_SIZE(ObsData), 1, 5);
    uz_dqn_push_to_buffer(buffertesting,&RewardData4,&qval4,&action4,obs);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(rew, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(qval, q_value, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(obbs, observation, EXPERIENCE_BUFFER_LENGTH*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(act, action, EXPERIENCE_BUFFER_LENGTH);
}


void test_uz_dqn_get_minibatch_from_buffer(void){
    // float data
    float rew2[EXPERIENCE_BUFFER_LENGTH] = {-777.7f,-27.7f,300.0f};
    int32_t act2[EXPERIENCE_BUFFER_LENGTH] = {777,0,-1};
    float qval2[EXPERIENCE_BUFFER_LENGTH] = {543.3f,6.4f,7.99f};
    float obbs2[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {7.0f,7.0f,7.0f,7.0f,7.0f,2.0f,2.1f,5.1f,2.1f,13.0f,2.0f,-1.0f,5.1f,2.1f,3.0f};
    struct uz_dqn_experience_replay_config confbuf = {
        .length_of_buffer = UZ_MATRIX_SIZE(rew2),
        .columns_of_observations = NUMBEROFOBS,
        .reward = rew2,
        .qvalues =qval2,
        .observations = obbs2,
        .actions = act2
    };
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(confbuf,EXPERIENCE_BUFFER_LENGTH,0);
    // test assert wenn testindex 0, muss noch behoben werden
    uint32_t testindizes[MINIBATCHSIZE] = {1,0};
    uint32_t* ind = testindizes;
    float getbackrew[MINIBATCHSIZE]= {0.0f};
    float* r = getbackrew;
    float getbackqval[MINIBATCHSIZE]= {0.0f};
    float* q = getbackqval;
    float getbackqvalplus1[MINIBATCHSIZE]= {0.0f};
    float* qplus1 = getbackqvalplus1;
    int32_t getbackact[MINIBATCHSIZE] = {0};
    int32_t* a = getbackact;
    float getbackobbs[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrix = {0};
    uz_matrix_t *getbackobs = uz_matrix_init(&getbackobs_matrix, getbackobbs, UZ_MATRIX_SIZE(getbackobbs), MINIBATCHSIZE, NUMBEROFOBS);
    uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,qplus1,a,getbackobs,MINIBATCHSIZE,NUMBEROFOBS,ind);
    float testrew[MINIBATCHSIZE] = {-27.7f,-777.7f};
    float testqval[MINIBATCHSIZE] = {6.4f,543.3f};
    float testqvalplus1[MINIBATCHSIZE] = {7.99f,6.4f};
    float testobs[NUMBEROFOBS*MINIBATCHSIZE] = {2.0f,2.1f,5.1f,2.1f,13.0f,7.0f,7.0f,7.0f,7.0f,7.0f};
    int32_t testact[MINIBATCHSIZE] = {0,777};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrew, getbackrew, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqval, getbackqval, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqvalplus1, getbackqvalplus1, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobs, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(testact, getbackact, MINIBATCHSIZE);
}
#endif // TEST
