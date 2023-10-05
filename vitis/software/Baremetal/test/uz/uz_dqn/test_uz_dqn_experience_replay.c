#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_mtwister.h"
#include "uz_environment.h"

#define EXPERIENCE_BUFFER_LENGTH 3
#define NUMBEROFOBS 5
#define MINIBATCHSIZE 2

float zerofloat [EXPERIENCE_BUFFER_LENGTH] = {0.0f};
uint32_t zerouint [EXPERIENCE_BUFFER_LENGTH] = {0};
float reward[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0,5,50};
float observation[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {2.0f,3.0f,6.0f,5.0f,7.0f,12.0f,12.5f,12.75f,12.85f,12.95f,100.0f,200.0f,300.0f,400.0f,500.0f};
float observation1[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {2.0f,3.0f,6.0f,5.0f,7.0f,12.0f,12.5f,12.75f,12.85f,12.95f,100.0f,200.0f,300.0f,400.0f,500.0f};

float reward_set[EXPERIENCE_BUFFER_LENGTH] = {7.7f,-27.7f,300.0f};
uint32_t action_set[EXPERIENCE_BUFFER_LENGTH] = {1,0,3};
float observation_set[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {0.1f,1.1f,4.1f,1.1f,-1.0f,1.0f,1.1f,4.1f,1.1f,-1.0f,1.0f,-2.0f,5.1f,2.1f,0.0f};
float observation_set1[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {1.1f,2.1f,5.1f,2.1f,0.0f,2.0f,2.1f,5.1f,2.1f,0.0f,2.0f,-1.0f,5.1f,2.1f,0.0f};

float vecobs[NUMBEROFOBS] = {0.0f};
float vecobs1[NUMBEROFOBS] = {0.0f};
struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_buffer = UZ_MATRIX_SIZE(reward),
        .columns_of_observations = NUMBEROFOBS,
        .reward = reward,
        .observations = observation,
        .observations1 = observation1,
        .obsvec = vecobs,
        .obsvec1 = vecobs1,
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

void test_uz_dqn_get_from_buffer(void)
{
    float read_reward = 0.0f;
    uint32_t read_action = 0;
    float readobs[5] = {0.0f};
    float readobs1[5] = {0.0f};
    struct uz_matrix_t readobs_matrix = {0};
    uz_matrix_t *obsread = uz_matrix_init(&readobs_matrix, readobs, NUMBEROFOBS, 1, 5);
    struct uz_matrix_t readobs_matrix1 = {0};
    uz_matrix_t *obsread1 = uz_matrix_init(&readobs_matrix1, readobs1, NUMBEROFOBS, 1, 5);
    uz_dqn_experience_replay_t *bufferread = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH);
    uz_dqn_get_from_buffer(bufferread, &read_reward,&read_action,obsread,obsread1,2);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, read_reward);
    float comparer[5] = {100.0f,200.0f,300.0f,400.0f,500.0f};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(comparer, readobs, NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(comparer, readobs1, NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32(50, read_action);
}

void test_uz_dqn_clear_buffer(void)
{
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH);
    uz_dqn_reset_buffer(buffertesting);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, observation, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(zerofloat, observation1, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_INT32_ARRAY(zerouint, action, EXPERIENCE_BUFFER_LENGTH);
}

void test_uz_dqn_write_to_buffer(void)
{
    float RewardData1 = 7.7f;
    uint32_t action1 = 1;
    float ObsData[5] = {0.1f,1.1f,4.1f,1.1f,-1.0f};
    struct uz_matrix_t obs_matrix = {0};
    uz_matrix_t *obs = uz_matrix_init(&obs_matrix, ObsData, UZ_MATRIX_SIZE(ObsData), 1, 5);
    float ObsData1[5] = {1.1f,2.1f,5.1f,2.1f,0.0f};
    struct uz_matrix_t obs_matrix1 = {0};
    uz_matrix_t *obs1 = uz_matrix_init(&obs_matrix1, ObsData1, UZ_MATRIX_SIZE(ObsData1), 1, 5);
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH);
    uz_dqn_push_to_buffer(buffertesting,RewardData1,action1,obs,obs1);
    ObsData[0] = 1.0f;
    ObsData1[0] = 2.0f;
    float RewardData2 = -27.7f;
    float QData2 = 6.4f;
    uint32_t action2 = 0;
    uz_dqn_push_to_buffer(buffertesting,RewardData2,action2,obs,obs1);
    ObsData[1] = -2.0f;
    ObsData1[1] = -1.0f;
    float RewardData3 = 300.0f;
    float QData3 = 7.99f;
    uint32_t action3 = 3;
    uz_dqn_push_to_buffer(buffertesting,RewardData3,action3,obs,obs1);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(reward_set, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(observation_set, observation, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(observation_set1, observation1, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(action_set, action, EXPERIENCE_BUFFER_LENGTH);

}

void test_uz_dqn_overwrite_first_values(void){
    // float data
    float rew[EXPERIENCE_BUFFER_LENGTH] = {-777.7f,-27.7f,300.0f};
    uint32_t act[EXPERIENCE_BUFFER_LENGTH] = {777,0,3};
    float obbs[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {7.0f,7.0f,7.0f,7.0f,7.0f,1.0f,1.1f,4.1f,1.1f,-1.0f,1.0f,-2.0f,4.1f,1.1f,-1.0f};
    float obbs1[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {7.0f,7.0f,7.0f,7.0f,7.0f,2.0f,2.1f,5.1f,2.1f,0.0f,2.0f,-1.0f,5.1f,2.1f,0.0f};
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer,EXPERIENCE_BUFFER_LENGTH);
    float RewardData4 = -777.7f;
    uint32_t action4 = 777;
    float ObsData[5] = {7.0f,7.0f,7.0f,7.0f,7.0f};
    struct uz_matrix_t obs_matrix = {0};
    uz_matrix_t *obs = uz_matrix_init(&obs_matrix, ObsData, UZ_MATRIX_SIZE(ObsData), 1, 5);
    float ObsData1[5] = {7.0f,7.0f,7.0f,7.0f,7.0f};
    struct uz_matrix_t obs_matrix1 = {0};
    uz_matrix_t *obs1 = uz_matrix_init(&obs_matrix1, ObsData1, UZ_MATRIX_SIZE(ObsData1), 1, 5);
    uz_dqn_push_to_buffer(buffertesting,RewardData4,action4,obs,obs1);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(rew, reward, EXPERIENCE_BUFFER_LENGTH);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(obbs, observation, EXPERIENCE_BUFFER_LENGTH*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(obbs1, observation1, EXPERIENCE_BUFFER_LENGTH*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(act, action, EXPERIENCE_BUFFER_LENGTH);
}
// void test_uz_dqn_get_minibatch_from_buffer_logic_testing(void){
//     uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer, EXPERIENCE_BUFFER_LENGTH,9); 
//     // buffer init, headind=9 => buffer wurde einmal komplett beschrieben, is aber noch nicht überschrieben
//     //testV1: nur aus buffer herausziehen
//     uint32_t testindizes[MINIBATCHSIZE] = {4,3,8};
//     uint32_t* ind = testindizes;
//     float getbackrew[MINIBATCHSIZE]= {0.0f};
//     float* r = getbackrew;
//     float getbackqval[MINIBATCHSIZE]= {0.0f};
//     float* q = getbackqval;
//     uint32_t getbackact[MINIBATCHSIZE] = {0};
//     uint32_t* a = getbackact;
//     float getbackobbs[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
//     struct uz_matrix_t getbackobs_matrix = {0};
//     uz_matrix_t *getbackobs = uz_matrix_init(&getbackobs_matrix, getbackobbs, UZ_MATRIX_SIZE(getbackobbs), MINIBATCHSIZE, NUMBEROFOBS);
//     float getbackobbspl1[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
//     struct uz_matrix_t getbackobs_matrixpl1 = {0};
//     uz_matrix_t *getbackobspl1 = uz_matrix_init(&getbackobs_matrixpl1, getbackobbspl1, UZ_MATRIX_SIZE(getbackobbspl1), MINIBATCHSIZE, NUMBEROFOBS);
//     uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,ind);
//     float testrew[MINIBATCHSIZE] = {5.0f,4.0f,9.0f};
//     float testqval[MINIBATCHSIZE] = {-2.0f,50.0f,100.0f};
//     float testobs[NUMBEROFOBS*MINIBATCHSIZE] = {3.7f,8.5f,6.3f,49.1f,0.3f,9.2f,24.9f,7.1f,49.3f,17.1f,14.8f,22.0f,45.0f,40.3f,16.7f};
//     float testobsplus1[NUMBEROFOBS*MINIBATCHSIZE] = {4.1f,22.1f,20.2f,50.0f,5.0f,3.7f,8.5f,6.3f,49.1f,0.3f,4.2f,20.6f,14.7f,15.0f,16.8f};
//     uint32_t testact[MINIBATCHSIZE] = {40,30,80};
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrew, getbackrew, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqval, getbackqval, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobs, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_INT32_ARRAY(testact, getbackact, MINIBATCHSIZE);
//     // test funktioniert
//     // testV2:jetz wird index auf 9 gesetzt => headind-1 sollte neuer index werden, wenn die logik passt also wird zeile 8 extrahiert
//     testindizes[2]= 9;// 9 sollte zu 8 korrigiert werden also selbe logik wie oben
//     uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,ind);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrew, getbackrew, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqval, getbackqval, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobs, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_INT32_ARRAY(testact, getbackact, MINIBATCHSIZE);
//     // test funktioniert
//     // testV3: buffer voll auf true setzen und nochmal die Daten extrahieren mit index 9 => 
//     // es sollte für indexplus1 obs die Observation(0) genommen werden
//     buffertesting->is_full = true;
//     buffertesting->counterisfull = 1;
//     uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,ind);
//     // neue float arrays für den test
//     float testrewV3[MINIBATCHSIZE] = {5.0f,4.0f,10.0f};
//     float testqvalV3[MINIBATCHSIZE] = {-2.0f,50.0f,-100.0f};
//     float testobsV3[NUMBEROFOBS*MINIBATCHSIZE] = {3.7f,8.5f,6.3f,49.1f,0.3f,9.2f,24.9f,7.1f,49.3f,17.1f,4.2f,20.6f,14.7f,15.0f,16.8f};
//     float testobsplus1V3[NUMBEROFOBS*MINIBATCHSIZE] = {4.1f,22.1f,20.2f,50.0f,5.0f,3.7f,8.5f,6.3f,49.1f,0.3f,49.6f,35.9f,47.0f,20.7f,46.9f};
//     uint32_t testactV3[MINIBATCHSIZE] = {40,30,90};
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrewV3, getbackrew, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqvalV3, getbackqval, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsV3, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1V3, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_INT32_ARRAY(testactV3, getbackact, MINIBATCHSIZE);
//     //V3 läuft
//     // testV4: jetzt wird headind auf 1 gesetzt, und buffer counterisfull auf 2, is_full auf false setzen, und dann nochmal gleiche prozedur wie vorher
//     buffertesting->is_full = false;
//     buffertesting->counterisfull = 2;
//     uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,ind);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrewV3, getbackrew, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqvalV3, getbackqval, MINIBATCHSIZE);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsV3, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1V3, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
//     TEST_ASSERT_EQUAL_INT32_ARRAY(testactV3, getbackact, MINIBATCHSIZE);
// }
#endif // TEST