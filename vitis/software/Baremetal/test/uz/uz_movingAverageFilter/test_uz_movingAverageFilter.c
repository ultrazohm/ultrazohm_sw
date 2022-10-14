#ifdef TEST

#include "unity.h"

#include "uz_movingAverageFilter.h"


struct uz_movingAverageFilter_config config = {0};
void setUp(void)
{
    config.filterLength = 50;
}

void tearDown(void)
{
}



void test_uz_movingAverageFilter_sample(){
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config);
    float input1 = 1.0f;
    float output;

    output = uz_movingAverageFilter_sample(filter,input1);
    TEST_ASSERT_EQUAL_FLOAT(output, input1/(float)config.filterLength);

    float input2 = 6.0f;
    output = uz_movingAverageFilter_sample(filter,input2);
    TEST_ASSERT_EQUAL_FLOAT(output, (input1+input2)/(float)config.filterLength);

    float input3 = 3.2f;
    output = uz_movingAverageFilter_sample(filter,input3);
    TEST_ASSERT_EQUAL_FLOAT(output, (input1+input2+input3)/(float)config.filterLength);

}


void test_uz_movingAverageFilter_reset(){
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config);
    float input1 = 1.0f;
    float output;

    output = uz_movingAverageFilter_sample(filter,input1);

    uz_movingAverageFilter_reset(filter);

    float input2 = 0.0f;
    output = uz_movingAverageFilter_sample(filter, input2);
    TEST_ASSERT_EQUAL_FLOAT(output, 0.0f);


}


void test_uz_movingAverageFilter_set_filterLength(){
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config);

    int new_filterLength = 1;
    uz_movingAverageFilter_set_filterLength(filter, new_filterLength);

    float input1 = 1.0f;
    float output;

    output = uz_movingAverageFilter_sample(filter,input1);
    TEST_ASSERT_EQUAL_FLOAT(output, input1);

    float input2 = 1.5f;
    output = uz_movingAverageFilter_sample(filter,input2);
    TEST_ASSERT_EQUAL_FLOAT(output, input2);

}


#endif // TEST
