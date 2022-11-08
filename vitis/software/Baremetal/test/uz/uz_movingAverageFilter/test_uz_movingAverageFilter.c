#ifdef TEST

#include "unity.h"

#include "uz_movingAverageFilter.h"
#include <stdio.h>

struct uz_movingAverageFilter_config config = {0};
void setUp(void){
    config.filterLength = 50;
}

void tearDown(void)
{
}



void test_uz_movingAverageFilter_sample(void){
    float data [51] = {0};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config, circularBuffer);
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

void test_uz_movingAverageFilter_efficient(void){
    float data [51] = {0};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config,circularBuffer);
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
    
    

    uz_movingAverageFilter_reset(filter);
    uz_movingAverageFilter_set_filterLength(filter, 2);
    output = uz_movingAverageFilter_sample(filter,input1);
    TEST_ASSERT_EQUAL_FLOAT(output, (input1)/2.0f);


    output = uz_movingAverageFilter_sample(filter,input2);
    TEST_ASSERT_EQUAL_FLOAT(output, (input1)/2.0f + (input2)/2.0f);


    output = uz_movingAverageFilter_sample(filter,input3);
    TEST_ASSERT_EQUAL_FLOAT(output, (input2)/2.0f + (input3)/2.0f);


}

void test_uz_movingAverageFilter_reset(){
    float data [51] = {0};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config,circularBuffer);
    float input1 = 1.0f;
    float output;

    output = uz_movingAverageFilter_sample(filter,input1);

    uz_movingAverageFilter_reset(filter);

    float input2 = 0.0f;
    output = uz_movingAverageFilter_sample(filter, input2);
    TEST_ASSERT_EQUAL_FLOAT(output, 0.0f);


}


void test_uz_movingAverageFilter_set_filterLength(){
    float data [51] = {0};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    uz_movingAverageFilter_t* filter;
    filter = uz_movingAverageFilter_init(config,circularBuffer);

    uint32_t new_filterLength = 1;
    uz_movingAverageFilter_set_filterLength(filter, new_filterLength);

    float input1 = 1.0f;
    float output;

    output = uz_movingAverageFilter_sample(filter,input1);
    TEST_ASSERT_EQUAL_FLOAT(output, input1);

    float input2 = 1.5f;
    output = uz_movingAverageFilter_sample(filter,input2);
    TEST_ASSERT_EQUAL_FLOAT(output, input2);


    uz_movingAverageFilter_reset(filter);
    new_filterLength = 10;
    uz_movingAverageFilter_set_filterLength(filter, new_filterLength);
    
    input1 = 1.0f;
    output = uz_movingAverageFilter_sample(filter,input1);
    TEST_ASSERT_EQUAL_FLOAT(output, input1/(float)new_filterLength);

    input2 = 1.5f;
    output = uz_movingAverageFilter_sample(filter,input2);
    TEST_ASSERT_EQUAL_FLOAT(output, (input1+input2)/(float)new_filterLength);

}

void test_uz_movingAverageFilter_set_filterLength2(){
    float data [10] = {0};
    float input[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
    float result[10] = {0};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    config.filterLength = 10U;
    result[0] = input[0] / (float)config.filterLength;
    for (uint32_t i = 1; i < config.filterLength; i++) {
        result[i] = result[i-1U] + (input[i] / (float)config.filterLength);
    } 
    uz_movingAverageFilter_t*  filter = uz_movingAverageFilter_init(config,circularBuffer);
    float output;
    for (uint32_t i = 0; i < config.filterLength; i++) {
        output = uz_movingAverageFilter_sample(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }

}

#endif // TEST
