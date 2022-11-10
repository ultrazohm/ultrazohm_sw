#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
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

void test_uz_movingAverageFilter_test_max_Filterlength(){
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

void test_uz_movingAverageFilter_assert_set_filterLength(){
    float data [51] = {0};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    uz_movingAverageFilter_t* filter = uz_movingAverageFilter_init(config,circularBuffer);

    uint32_t new_filterLength = 100U;
    TEST_ASSERT_FAIL_ASSERT(uz_movingAverageFilter_set_filterLength(filter, new_filterLength));

    new_filterLength = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_movingAverageFilter_set_filterLength(filter, new_filterLength));
}

void test_uz_movingAverageFilter_variable_length_test_max_Filterlength(){
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
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }
}

void test_uz_movingAverageFilter_variable_length_test_filterlength_half_of_max_length(){
    float data [20] = {0};
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
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }
}

void test_uz_movingAverageFilter_variable_length_test_filterlength_quarter_of_max(){
    float data [20] = {0};
    float input[20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    //Add the last 5 values together and divide the sum by 5
    float result[20] = {0.2f, 0.6f, 1.2f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    config.filterLength = 5U;
    uz_movingAverageFilter_t*  filter = uz_movingAverageFilter_init(config,circularBuffer);
    float output;
    for (uint32_t i = 0; i < 20U; i++) {
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }
}

void test_uz_movingAverageFilter_variable_length_test_increase_filter_length(){
    float data [20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    float input[20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    //Add the last 5 values together and divide the sum by 5
    float result[20] = {15.0f, 12.0f, 9.0f, 6.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    config.filterLength = 5U;
    uz_movingAverageFilter_t*  filter = uz_movingAverageFilter_init(config,circularBuffer);
    float output;
    for (uint32_t i = 0; i < 10U; i++) {
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }
    config.filterLength = 15U;
    uz_movingAverageFilter_set_filterLength(filter, config.filterLength);
    result[10] = 9.3333f;
    output = uz_movingAverageFilter_sample_variable_length(filter,input[10]);
     TEST_ASSERT_EQUAL_FLOAT(result[10], output);
}

void test_uz_movingAverageFilter_variable_length_test_decrease_filter_length(){
    float data [20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    float input[20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    //Add the last 5 values together and divide the sum by 5
    float result[20] = {12.6667f, 12.3333f, 12.0f, 11.66667f, 11.3333f};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    config.filterLength = 15U;
    uz_movingAverageFilter_t*  filter = uz_movingAverageFilter_init(config,circularBuffer);
    float output;
    for (uint32_t i = 0; i < 5U; i++) {
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }
    config.filterLength = 5U;
    uz_movingAverageFilter_set_filterLength(filter, config.filterLength);
    result[5] = 4.0f;
    output = uz_movingAverageFilter_sample_variable_length(filter,input[5]);
     TEST_ASSERT_EQUAL_FLOAT(result[5], output);
}

void test_uz_movingAverageFilter_variable_length_test_increase_filter_length_by_one(){
    float data [20] = {0};
    float input[20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    //Add the last 5 values together and divide the sum by 5
    float result[20] = {1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 10.0f, 10.5f};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    config.filterLength = 1U;
    uz_movingAverageFilter_t*  filter = uz_movingAverageFilter_init(config,circularBuffer);
    float output;
    //Increase filter length by 1 each loop
    for (uint32_t i = 0; i < 20U; i++) {
        uz_movingAverageFilter_set_filterLength(filter, (i + 1U));
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_EQUAL_FLOAT(result[i], output);
    }
}

void test_uz_movingAverageFilter_variable_length_test_decrease_filter_length_by_one(){
    float data [20] = {0};
    float input[20] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f};
    //Add the last 5 values together and divide the sum by 5
    float result[20] = {10.5f, 10.8947f, 11.16667f, 11.2941f, 11.25f, 11.0f, 10.5f, 9.6923f, 8.5f, 6.81818f, 6.5f, 8.0f, 9.5f, 11.0f, 12.5f, 14.0f, 15.5f, 17.0f, 18.5f, 20.0f};
    uz_array_float_t circularBuffer = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]
    };
    config.filterLength = 20U;
    uz_movingAverageFilter_t*  filter = uz_movingAverageFilter_init(config,circularBuffer);
    float output;
    //Fill ringbuffer with values
    for (uint32_t i = 0; i < 20U; i++) {
        uz_movingAverageFilter_sample_variable_length(filter,input[i]);
    }

    //Decrease filter length by 1 each loop
    for (uint32_t i = 0; i < 10U; i++) {
        uz_movingAverageFilter_set_filterLength(filter, (20U - i));
        output = uz_movingAverageFilter_sample_variable_length(filter,input[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-04f, result[i], output);
    }
}

#endif // TEST
