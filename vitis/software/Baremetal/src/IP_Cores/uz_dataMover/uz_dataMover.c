#include <stdbool.h>
#include <string.h> // for memcpy
#include "../../uz/uz_HAL.h"
#include "uz_dataMover.h" 
#define UZ_DATAMOVER_ARRAY_LENGTH 32 // Number of variables that are written to TCM by the dataMover

// Number of elements in one array
#define R5_0_BTCM_SPLIT_REG	0x20000U // Start of BTCM
static int16_t buffer[UZ_DATAMOVER_ARRAY_LENGTH]={0};

// Tested the following:
// volatile int16_t *ptr_to_btcm=(volatile int16_t *)(0x20000);
// And the version without volatile below with -O2 and there is not difference
// memcpy and the uz_array.data throw a warning that the volatile keyword is lost
// Since I am not sure how far the volatile keyword should be "propagated upwards"
// The version without is used - not sure about it
// cppcheck-suppress misra-c2012-11.4 // this is not allowed since there is no way to know that ptr_to_btcm actually points to int16_t variables - this can only be known be knowing the Vivado project
static int16_t *ptr_to_btcm=(void *)(R5_0_BTCM_SPLIT_REG);

uz_array_int16_t uz_dataMover_get_data_by_pointer(void){
    uz_array_int16_t data_array={
        .length=UZ_ARRAY_SIZE(buffer),
        .data=ptr_to_btcm
    };
    return data_array;
}

uz_array_int16_t uz_dataMover_update_buffer_and_get_data(void){
    uz_dataMover_update_buffer();
    return (uz_dataMover_get_data_from_buffer());
}

void uz_dataMover_update_buffer(void){
    void *ptr_res=memcpy(&buffer, ptr_to_btcm,sizeof(buffer) );
    uz_assert_not_NULL(ptr_res); // checks return value of memcpy to make sure something happend
}

uz_array_int16_t uz_dataMover_get_data_from_buffer(void){
    uz_array_int16_t data_array={
        .length=UZ_ARRAY_SIZE(buffer),
        .data=&buffer[0]
    };
    return data_array;
}
