#include "uz_sum.h"

#include "../../uz_global_configuration.h"

#if UZ_SUM_MAX_INSTANCES > 0U

#ifndef TEST
#error DO NOT USE! This function is only exists for demonstration purposes in the How to create framework functions from embedded coder example.
#endif


#include <stdbool.h> 
#include "../../uz_HAL.h"
#include "uz_sum.h" 

#include "uz_codegen0_ert_rtw/uz_codegen0.h"

struct uz_sum_t {
    bool is_ready;
    ExtY output;
    ExtU input;
    DW rtDW;                        /* Observable states */
    RT_MODEL modelData;
    RT_MODEL *PtrToModelData;
};

static uint32_t instance_counter = 0U;
static uz_sum_t instances[UZ_SUM_MAX_INSTANCES] = { 0 };

static uz_sum_t* uz_sum_allocation(void);

static uz_sum_t* uz_sum_allocation(void){
    uz_assert(instance_counter < UZ_SUM_MAX_INSTANCES);
    uz_sum_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_sum_t* uz_sum_init(void) {
    uz_sum_t* self = uz_sum_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->dwork=&self->rtDW;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    return (self);
}

void uz_sum_step(uz_sum_t* self, float a, float b, float c){
    self->input.summand1=a;
    self->input.summand2=b;
    self->input.summand3=c;
    uz_codegen0_step(self->PtrToModelData);
}


float uz_sum_get_sum(uz_sum_t* self){
    return self->output.sum;
}

float uz_sum_get_integral_over_sum(uz_sum_t* self){
    return self->output.IntegrationOfSum;
}

#endif