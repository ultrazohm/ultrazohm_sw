#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_mtwister.h"
#include "uz_environment.h"

#define EXPERIENCE_BUFFER_LENGTH 10
#define NUMBEROFOBS 5
#define MINIBATCHSIZE 3

float zerofloat [EXPERIENCE_BUFFER_LENGTH] = {0.0f};
uint32_t zerouint [EXPERIENCE_BUFFER_LENGTH] = {0};
float reward[EXPERIENCE_BUFFER_LENGTH] = {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f};
uint32_t action[EXPERIENCE_BUFFER_LENGTH] = {0,10,20,30,40,50,60,70,80,90};
float q_value[EXPERIENCE_BUFFER_LENGTH] = {-5.0f,5.0f,-50.0f,50.0f,-2.0f,2.0f,-1.0f,1.0f,100.0f,-100.0f};
float observation[NUMBEROFOBS*EXPERIENCE_BUFFER_LENGTH] = {49.6f,35.9f,47.0f,20.7f,46.9f,13.4f,43.4f,-1.5f,29.8f,16.6f,
30.5f,36.2f,46.6f,20.6f,27.3f,9.2f,24.9f,7.1f,49.3f,17.1f,
3.7f,8.5f,6.3f,49.1f,0.3f,4.1f,22.1f,20.2f,50.0f,5.0f,
10.3f,33.9f,47.8f,44.3f,40.1f,18.7f,42.4f,16.0f,5.1f,11.0f,
14.8f,22.0f,45.0f,40.3f,16.7f,4.2f,20.6f,14.7f,15.0f,16.8f
};

float vecobs[NUMBEROFOBS] = {0.0f};

struct uz_dqn_experience_replay_config configbuffer = {
        .length_of_buffer = UZ_MATRIX_SIZE(reward),
        .columns_of_observations = NUMBEROFOBS,
        .reward = reward,
        .qvalues =q_value,
        .observations = observation,
        .obsvec = vecobs,
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

void test_uz_dqn_get_minibatch_from_buffer_logic_testing_index_0(void){
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer, EXPERIENCE_BUFFER_LENGTH,9); 
    // buffer init, headind=9 => buffer wurde einmal komplett beschrieben, is aber noch nicht überschrieben
    //testV1: nur aus buffer herausziehen
    uint32_t testindizes[MINIBATCHSIZE] = {0,9,0};
    uint32_t* ind = testindizes;
    float getbackrew[MINIBATCHSIZE]= {0.0f};
    float* r = getbackrew;
    float getbackqval[MINIBATCHSIZE]= {0.0f};
    float* q = getbackqval;
    uint32_t getbackact[MINIBATCHSIZE] = {0};
    uint32_t* a = getbackact;
    float getbackobbs[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrix = {0};
    uz_matrix_t *getbackobs = uz_matrix_init(&getbackobs_matrix, getbackobbs, UZ_MATRIX_SIZE(getbackobbs), MINIBATCHSIZE, NUMBEROFOBS);
    float getbackobbspl1[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrixpl1 = {0};
    uz_matrix_t *getbackobspl1 = uz_matrix_init(&getbackobs_matrixpl1, getbackobbspl1, UZ_MATRIX_SIZE(getbackobbspl1), MINIBATCHSIZE, NUMBEROFOBS);
    buffertesting->is_full = true;
    buffertesting->counterisfull = 1;
    uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,getbackobs,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,NUMBEROFOBS,ind);
    float testrew[MINIBATCHSIZE] = {1.0f,10.0f,1.0f};
    float testqval[MINIBATCHSIZE] = {-5.0f,-100.0f,-5.0f};
    float testobs[NUMBEROFOBS*MINIBATCHSIZE] = {49.6f,35.9f,47.0f,20.7f,46.9f,4.2f,20.6f,14.7f,15.0f,16.8f,49.6f,35.9f,47.0f,20.7f,46.9f};
    float testobsplus1[NUMBEROFOBS*MINIBATCHSIZE] = {13.4f,43.4f,-1.5f,29.8f,16.6f,49.6f,35.9f,47.0f,20.7f,46.9f,13.4f,43.4f,-1.5f,29.8f,16.6f};
    uint32_t testact[MINIBATCHSIZE] = {0,90,0};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrew, getbackrew, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqval, getbackqval, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobs, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(testact, getbackact, MINIBATCHSIZE);
}

void test_uz_dqn_get_minibatch_from_buffer_logic_testing(void){
    uz_dqn_experience_replay_t *buffertesting = uz_dqn_experience_replay_init(configbuffer, EXPERIENCE_BUFFER_LENGTH,9); 
    // buffer init, headind=9 => buffer wurde einmal komplett beschrieben, is aber noch nicht überschrieben
    //testV1: nur aus buffer herausziehen
    uint32_t testindizes[MINIBATCHSIZE] = {4,3,8};
    uint32_t* ind = testindizes;
    float getbackrew[MINIBATCHSIZE]= {0.0f};
    float* r = getbackrew;
    float getbackqval[MINIBATCHSIZE]= {0.0f};
    float* q = getbackqval;
    uint32_t getbackact[MINIBATCHSIZE] = {0};
    uint32_t* a = getbackact;
    float getbackobbs[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrix = {0};
    uz_matrix_t *getbackobs = uz_matrix_init(&getbackobs_matrix, getbackobbs, UZ_MATRIX_SIZE(getbackobbs), MINIBATCHSIZE, NUMBEROFOBS);
    float getbackobbspl1[NUMBEROFOBS*MINIBATCHSIZE] = {0.0f};
    struct uz_matrix_t getbackobs_matrixpl1 = {0};
    uz_matrix_t *getbackobspl1 = uz_matrix_init(&getbackobs_matrixpl1, getbackobbspl1, UZ_MATRIX_SIZE(getbackobbspl1), MINIBATCHSIZE, NUMBEROFOBS);
    uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,getbackobs,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,NUMBEROFOBS,ind);
    float testrew[MINIBATCHSIZE] = {5.0f,4.0f,9.0f};
    float testqval[MINIBATCHSIZE] = {-2.0f,50.0f,100.0f};
    float testobs[NUMBEROFOBS*MINIBATCHSIZE] = {3.7f,8.5f,6.3f,49.1f,0.3f,9.2f,24.9f,7.1f,49.3f,17.1f,14.8f,22.0f,45.0f,40.3f,16.7f};
    float testobsplus1[NUMBEROFOBS*MINIBATCHSIZE] = {4.1f,22.1f,20.2f,50.0f,5.0f,3.7f,8.5f,6.3f,49.1f,0.3f,4.2f,20.6f,14.7f,15.0f,16.8f};
    uint32_t testact[MINIBATCHSIZE] = {40,30,80};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrew, getbackrew, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqval, getbackqval, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobs, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(testact, getbackact, MINIBATCHSIZE);
    // test funktioniert
    // testV2:jetz wird index auf 9 gesetzt => headind-1 sollte neuer index werden, wenn die logik passt also wird zeile 8 extrahiert
    testindizes[2]= 9;// 9 sollte zu 8 korrigiert werden also selbe logik wie oben
    uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,getbackobs,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,NUMBEROFOBS,ind);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrew, getbackrew, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqval, getbackqval, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobs, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(testact, getbackact, MINIBATCHSIZE);
    // test funktioniert
    // testV3: buffer voll auf true setzen und nochmal die Daten extrahieren mit index 9 => 
    // es sollte für indexplus1 obs die Observation(0) genommen werden
    buffertesting->is_full = true;
    buffertesting->counterisfull = 1;
    uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,getbackobs,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,NUMBEROFOBS,ind);
    // neue float arrays für den test
    float testrewV3[MINIBATCHSIZE] = {5.0f,4.0f,10.0f};
    float testqvalV3[MINIBATCHSIZE] = {-2.0f,50.0f,-100.0f};
    float testobsV3[NUMBEROFOBS*MINIBATCHSIZE] = {3.7f,8.5f,6.3f,49.1f,0.3f,9.2f,24.9f,7.1f,49.3f,17.1f,4.2f,20.6f,14.7f,15.0f,16.8f};
    float testobsplus1V3[NUMBEROFOBS*MINIBATCHSIZE] = {4.1f,22.1f,20.2f,50.0f,5.0f,3.7f,8.5f,6.3f,49.1f,0.3f,49.6f,35.9f,47.0f,20.7f,46.9f};
    uint32_t testactV3[MINIBATCHSIZE] = {40,30,90};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrewV3, getbackrew, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqvalV3, getbackqval, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsV3, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1V3, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(testactV3, getbackact, MINIBATCHSIZE);
    //V3 läuft
    // testV4: jetzt wird headind auf 1 gesetzt, und buffer counterisfull auf 2, is_full auf false setzen, und dann nochmal gleiche prozedur wie vorher
    buffertesting->is_full = false;
    buffertesting->counterisfull = 2;
    uz_dqn_get_minibatch_from_buffer(buffertesting,r,q,a,getbackobs,buffertesting->vectorforobs,getbackobspl1,MINIBATCHSIZE,NUMBEROFOBS,ind);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testrewV3, getbackrew, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testqvalV3, getbackqval, MINIBATCHSIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsV3, getbackobbs, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(testobsplus1V3, getbackobbspl1, MINIBATCHSIZE*NUMBEROFOBS);
    TEST_ASSERT_EQUAL_INT32_ARRAY(testactV3, getbackact, MINIBATCHSIZE);
}
#endif // TEST